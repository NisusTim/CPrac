/*
 * rmtp_obj_radar_signal.c
 *
 *  Created on: 2017/09/27
 *      Author: Benson
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdint.h>
#include "rmtp.h"
#include "rmtp_msg.h"
#include "rmtp_ids.h"
#include "rmtp_hal.h"
#include "rmtp_api.h"

enum {
	DATA_SEND_IDEL			= 0,
	DATA_SEND_NOT_READY		= 1,
	DATA_SEND_READY			= 2,
	DATA_SEND_ACTIVE		= 3,
	DATA_SEND_RESEND		= 4,
	DATA_SEND_PAUSE			= 5,
	DATA_SEND_ABORT			= 6,
	DATA_SEND_DONE			= 7
};

static uint8_t pkt[6]= {0};
static uint8_t rf_tx_testing = 0;
static uint32_t rf_rx_addr = 0;
static uint32_t rf_rx_size = 0;
static uint8_t data_send_state = DATA_SEND_IDEL;
static uint8_t data_send_net_id = RMTP_ITF_UNKNOWN;
static uint32_t data_send_addr_prev = 0;
static uint32_t data_send_addr_cur = 0;
static int data_flow_ctrl_timeout = 0;
static uint8_t cmd_on = 0;
static uint8_t cmd_netId = RMTP_ITF_UNKNOWN;
static uint8_t cmd_blockId = 0;
static uint8_t cmd_timeout = 0;
static uint8_t *cmd_data = NULL;

static const uint8_t attr_access[4] = {
	ATTR_N | ATTR_L,	
	ATTR_W | ATTR_L,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L
};

static void rf_signal_received_done(uint32_t addr, uint32_t size)
{
	if (rf_tx_testing == 1) {
		LOG("[RMTP] RX siganl (addr=%x, size=%d)\n", (UINT)addr, (UINT)size);
		rf_rx_addr = addr;
		rf_rx_size = size;
		data_send_state = DATA_SEND_READY;
		data_send_addr_prev = 0;
		data_send_addr_cur = 0;
		data_flow_ctrl_timeout = 0;
	}	
}

static void reset(void)
{
	if (rf_tx_testing == 1) {
		rf_tx_testing = 0;
		data_send_state = DATA_SEND_IDEL;
		rf_rx_addr = 0;
		rf_rx_size = 0;
		data_send_addr_prev = 0;
		data_send_addr_cur = 0;
		data_flow_ctrl_timeout = 0;
		rmtp_set_timer(OBJ_ID_RF_SIGNAL, TIMER_STOP);
	}
	if (cmd_on == 1) {
		cmd_on = 0;
		cmd_blockId = 0;
		cmd_timeout = 0;
		cmd_data = NULL;
		rmtp_set_timer(OBJ_ID_RF_SIGNAL, TIMER_STOP);
	}
}

static int destroy(void) 
{
	reset();	
	return RES_SUCCESS;
}

static int timeout_handler(void)
{
	int i = 0;
	int new_addr = 0;
	int size = 0;
	uint8_t *data = NULL;
	
	if (rf_tx_testing == 1) {
		switch (data_send_state) {
			case DATA_SEND_IDEL:
			case DATA_SEND_ABORT:
			case DATA_SEND_DONE:
				LOG("[RMTP] RF signal (IDEL/ABORT/DONE prev=%d, cur=%d)\n", (UINT)data_send_addr_prev, (UINT)data_send_addr_cur);
				reset();
				break;
			case DATA_SEND_READY:
				LOG("[RMTP] RF signal (READY)\n");
				data_send_state = DATA_SEND_ACTIVE;
				break;
			case DATA_SEND_ACTIVE:
				LOG("[RMTP] RF signal (ACTIVE)\n");
				data_send_addr_prev = data_send_addr_cur;
				break;
			case DATA_SEND_RESEND:
				LOG("[RMTP] RF signal (RESEND)\n");
				data_send_addr_cur = data_send_addr_prev;
				data_send_state = DATA_SEND_ACTIVE;				
				break;
			case DATA_SEND_PAUSE:
				LOG("[RMTP] RF signal (PAUSE:%d)\n", data_flow_ctrl_timeout);
				data_flow_ctrl_timeout++;	
				if (data_flow_ctrl_timeout >= 35) {
					LOG("[RMTP] RF signal (timeout=%d)\n",  data_flow_ctrl_timeout);
					rmtp_send_alarm_message(data_send_net_id, OBJ_ID_RF_SIGNAL, ALARM_ID_0, NULL, 0);
					reset();
				}
				break;
			default:
				break;
		}
		if (data_send_state == DATA_SEND_ACTIVE) {
			LOG("[RMTP] RF signal (SEND addr=%d)\n", (UINT)data_send_addr_prev);
			for (i = 0; i < 8; i++) {
				if (data_send_addr_cur < rf_rx_size) {
					data = (uint8_t *)(rf_rx_addr + data_send_addr_cur);
					new_addr = data_send_addr_cur + 6;
					if (new_addr <= rf_rx_size) {
						rmtp_send_data_section_message(data_send_net_id, OBJ_ID_RF_SIGNAL, i, data, 6);
						data_send_addr_cur = new_addr;;
					} else {
						size = rf_rx_size - data_send_addr_cur;
						rmtp_send_data_section_message(data_send_net_id, OBJ_ID_RF_SIGNAL, i, data, size);
						data_send_addr_cur += size;
					}
					LOG("[RMTP] RF signal (SEND seqNum=%d prev=%d, cur=%d)\n", i, (UINT)data_send_addr_prev, (UINT)data_send_addr_cur);
				}
			}
			data_flow_ctrl_timeout = 0;
			data_send_state = DATA_SEND_PAUSE;
		}
	}
	if ((cmd_on == 1) && (cmd_timeout > 0)) {
		cmd_timeout--;		
		if (cmd_timeout == 0) {
			reset();
			rmtp_send_err_response_message(cmd_netId, SUB_TYPE_GET, OBJ_ID_RF_SIGNAL, ATTR_ID_3, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
		}
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t res = RES_SUCCESS;
	uint8_t *datap = NULL;
	uint8_t	idx = 0;

	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_3: // Noise base data
			if ((cmd_on == 0) || (data[0] != cmd_blockId)) {
				pkt[0] = data[0];
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_SIGNAL, attrId, RES_CMD_REJECTED, pkt, 6);
				return RES_CMD_REJECTED;
			} else {
				datap = &cmd_data[0];
				if (cmd_blockId == BLOCK_ID_DONE) {
					pkt[0] = data[0];
					reset();
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_SIGNAL, attrId, pkt, 6);
				} else {
					pkt[0] = data[0];
					idx = cmd_blockId * 5;
					if (cmd_blockId == 9) {
						memcpy(&pkt[1], (datap + idx), 3);
					} else {
						memcpy(&pkt[1], (datap + idx), 5);
					}
					cmd_timeout = 15;
					cmd_blockId++;
					if (cmd_blockId == 10) {
						cmd_blockId = BLOCK_ID_DONE;
					}
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_SIGNAL, attrId, pkt, 6);
				}
			}
			return res;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int size = 0;

	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_1: // Signal transmission
			if (data[0] < 3) { // 0:T1, 1:T2, 2:T3
				if ((rf_tx_testing == 0) && (cmd_on == 0)) {
					rf_tx_testing = 1;
					data_send_state = DATA_SEND_NOT_READY;
					data_send_net_id = netId;
					size = rmtp_rf_transmit_signal(data[0], &rf_signal_received_done);
					pkt[0] = (uint8_t)((size & 0xFF00) >> 8);
					pkt[1] = (uint8_t)(size & 0x00FF);
					rmtp_set_timer(OBJ_ID_RF_SIGNAL, TIMER_START);
					return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, pkt, 2);
				} else if (rf_tx_testing == 1) {
					return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, RES_CMD_REJECTED, NULL, 0);
				}
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		case ATTR_ID_2: // Noise base control
			#if RMTP_NOISE_BASE
			if ((rf_tx_testing == 0) && (cmd_on == 0)) {
				cmd_data = rmtp_get_data();
				res = rmtp_get_noise_base(data[0], cmd_data);
				if (res == RES_SUCCESS) {
					cmd_on = 1;
					cmd_netId = netId;
					cmd_blockId = 0;
					cmd_timeout = 25;
					rmtp_set_timer(OBJ_ID_RF_SIGNAL, TIMER_START);
					rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, pkt, 6);
				} else {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, RES_CMD_PROCESS_ERR, NULL, 0);
				}
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_SIGNAL, attrId, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
			#endif
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int report_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	switch (attrId) {
		case ATTR_ID_0: // Flow control
			if (rf_tx_testing == 1) {
				switch (data[0]) {
					case FLOW_CTRL_SEND:
						LOG("[RMTP] RF signal (Flow control: Send next)\n");
						if (data_send_addr_cur >= rf_rx_size) {
							data_send_state = DATA_SEND_DONE;
							rmtp_send_alarm_message(netId, OBJ_ID_RF_SIGNAL, ALARM_ID_1, NULL, 0);
						} else {							
							data_send_state = DATA_SEND_ACTIVE;
						}
						break;
					case FLOW_CTRL_WAIT:
						LOG("[RMTP] RF signal (Flow control: Wait)\n");
						if (data_send_addr_cur >= rf_rx_size) {
							data_send_state = DATA_SEND_DONE;
							rmtp_send_alarm_message(netId, OBJ_ID_RF_SIGNAL, ALARM_ID_1, NULL, 0);
						} else {
							data_send_state = DATA_SEND_PAUSE;
						}
						break;
					case FLOW_CTRL_RESEND:
						LOG("[RMTP] RF signal (Flow control: Resend)\n");
						data_send_state = DATA_SEND_RESEND;
						break;
					case FLOW_CTRL_DONE:
						LOG("[RMTP] RF signal (Flow control: Done)\n");
						data_send_state = DATA_SEND_DONE;
						reset();
						break;
					case FLOW_CTRL_ABORT:
						LOG("[RMTP] RF signal (Flow control: Abort)\n");
						data_send_state = DATA_SEND_ABORT;
						reset();
						break;
				}
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;	
}

const rmtp_obj_t rmtp_obj_rf_signal = {
	OBJ_ID_RF_SIGNAL,				// Object ID
	4,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 	 	// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	report_msg_handler,				// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
