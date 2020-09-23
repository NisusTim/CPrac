/*
 * rmtp_obj_firmware_upgrade.c
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
	DATA_RECV_IDEL			= 0,
	DATA_RECV_ACTIVE		= 1,
	DATA_RECV_DONE			= 2
};

static uint8_t pkt[6]= {0};
static uint8_t data_recv_state = DATA_RECV_IDEL;
static uint8_t data_recv_net_id = RMTP_ITF_UNKNOWN;
static uint32_t data_image_size = 0;
static uint32_t data_cur_size = 0;
static uint32_t data_next_seq_cnt = 0;
static uint32_t data_recv_offset = 0;
static uint32_t data_recv_seq_mask = 0;
static uint16_t data_recv_cnt = 0;
static uint16_t data_recv_retry = 0;
static int16_t data_recv_seq_num = -1;
static uint16_t data_recv_timeout = 0;

static const uint8_t attr_access[8] = {
	ATTR_W,
	ATTR_R,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_NONE,
	ATTR_NONE,
	ATTR_NONE,
	ATTR_R | ATTR_W | ATTR_L
};

static void data_download_reset(void)
{
	data_recv_state = DATA_RECV_IDEL;
	data_image_size = 0;
	data_cur_size = 0;
	data_next_seq_cnt = 0;
	data_recv_offset = 0;
	data_recv_seq_mask = 0;
	data_recv_seq_num = -1;
	data_recv_cnt = 0;
	data_recv_retry = 0;
	data_recv_timeout = 0;
	rmtp_set_timer(OBJ_ID_FIRMWARE_UPGRADE, TIMER_STOP);
}

static int destroy(void) 
{
	if (data_recv_state == DATA_RECV_ACTIVE) {
		data_download_reset();
	}
	
	return RES_SUCCESS;
}
static int check_seq_num(uint8_t seqNum)
{
	uint32_t seq_mask;
	data_recv_seq_mask += 1;
	seq_mask = 1 << (seqNum + 1);
	if (data_recv_seq_mask != seq_mask) {
		DBG("[RMTP] check seqNum ERR: mask:0x%x:0x%x seqNum:%u size:%u:%u\n", data_recv_seq_mask, seq_mask, seqNum, data_cur_size, data_image_size);
		return RES_PARAMETER_ERROR;
	}
	DBG("[RMTP] check seqNum OK: size:%u:%u\n", data_cur_size, data_image_size);

	return RES_SUCCESS;
}

static void check_section_window(uint8_t isOK) 
{
	uint32_t next_cnt;

	memset(pkt, 0, 6);
	if (data_cur_size < data_image_size) {				
		if (isOK == RES_SUCCESS) {
			data_recv_seq_num = -1;
			data_recv_seq_mask = 0;
			data_recv_cnt = 0;
			data_recv_offset += DATA_WIN_SIZE; 
			next_cnt = (data_image_size - data_cur_size - 1) / 6;
			if (next_cnt > DATA_MAX_SEQ) {
				next_cnt = DATA_MAX_SEQ;
			}
			data_next_seq_cnt = next_cnt + 1;
			pkt[0] = FLOW_CTRL_SEND;
			DBG("[RMTP] FlowCtrl: SEND (szie:%u/%u)\n", data_cur_size, data_image_size);
		} else {
			data_recv_seq_num = -1;
			data_recv_seq_mask = 0;
			data_recv_cnt = 0;
			pkt[0] = FLOW_CTRL_RESEND;
			DBG("[RMTP] FlowCtrl: RESEND (szie:%u/%u)\n", data_cur_size, data_image_size);
		}
		rmtp_send_report_message(data_recv_net_id, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
	} else if (data_cur_size == data_image_size) {
		if (isOK == RES_SUCCESS) {
			pkt[0] = FLOW_CTRL_DONE;
			DBG("[RMTP] FlowCtrl: DONE\n");
			rmtp_fw_upgrade_write_image_done(data_cur_size);
			data_download_reset();
		} else {
			data_recv_seq_num = -1;
			data_recv_seq_mask = 0;
			data_recv_cnt = 0;
			pkt[0] = FLOW_CTRL_RESEND;
			DBG("[RMTP] FlowCtrl: RESEND (szie:%u/%u)\n", data_cur_size, data_image_size);
		}
		rmtp_send_report_message(data_recv_net_id, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
	} else {
		data_download_reset();
		rmtp_fw_upgrade_write_image_done(data_cur_size);
		pkt[0] = FLOW_CTRL_ABORT;
		DBG("[RMTP] FlowCtrl: ABORT\n");
		rmtp_send_report_message(data_recv_net_id, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
	}

	return; 
}

static int timeout_handler(void)
{
	if (data_recv_state == DATA_RECV_ACTIVE) {
		memset(pkt, 0, 6);
		data_recv_timeout++;
		if (data_recv_timeout >= 10) {
			if (data_recv_cnt == data_next_seq_cnt) {
				check_section_window(check_seq_num(data_recv_seq_num));
			} else {
				if (data_recv_retry <= 2) {
					data_recv_seq_num = -1;
					data_recv_seq_mask = 0;
					data_recv_cnt = 0;
					data_recv_retry++;
					pkt[0] = FLOW_CTRL_RESEND;
					DBG("[RMTP] FlowCtrl: RESEND (timeout retry: %d) (szie:%u/%u)\n", data_recv_retry, data_cur_size, data_image_size);
					rmtp_send_report_message(data_recv_net_id, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
				} else {	
					data_download_reset();
					pkt[0] = FLOW_CTRL_TIMEOUT;
					DBG("[RMTP] FlowCtrl: TIMEOUT\n");
					rmtp_send_report_message(data_recv_net_id, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
				}
			}	
		}
	} else {
		data_download_reset();
	}
	
	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{	
	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_1: // Prepare state			
			pkt[0] = rmtp_get_fw_upgrade_prepare_state();
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_UPGRADE, attrId, pkt, 1);
		case ATTR_ID_3: // Upgrade status
			pkt[0] = rmtp_get_fw_upgrade_status(data[0]);
			if (pkt[0] == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_UPGRADE, attrId, pkt, 1);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_UPGRADE, attrId, RES_CMD_PROCESS_ERR, pkt, 1);
			}	
		case ATTR_ID_7: // Lock JTAG
			pkt[0] = rmtp_get_jtag_lock_state();
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_UPGRADE, attrId, pkt, 1);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int size = 0;
	uint8_t res = RES_SUCCESS;
	uint32_t next_cnt;

	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_2: // Upgrade request
			if (data_recv_state == DATA_RECV_IDEL) {
				pkt[0] = data[0];
				size = (int)(data[1] << 16) + (int)(data[2] << 8) + (int)data[3];
				if (size == 0) {
					return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, RES_CMD_PROCESS_ERR, pkt, 1);
				}
				LOG("[RMTP] upgrade request: imgNo:%d size:%d\n", data[0], size);
				if (rmtp_set_fw_upgrade_reguest(data[0], size) == RES_SUCCESS) {
					data_recv_state = DATA_RECV_ACTIVE;
					data_recv_net_id = netId;
					data_image_size = size;
					data_cur_size = 0;
					data_recv_offset = 0;
					data_recv_seq_num = -1;
					data_recv_seq_mask = 0;
					data_recv_timeout = 0;
					data_recv_cnt = 0;
					data_recv_retry = 0;
					if (data_image_size >= DATA_WIN_SIZE) {
						next_cnt = DATA_MAX_SEQ;
					} else {
						next_cnt = ((data_image_size - 1) / 6);
					}
					data_next_seq_cnt = next_cnt + 1;
					rmtp_set_timer(OBJ_ID_FIRMWARE_UPGRADE, TIMER_START);
					return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, pkt, 1);
				} else {
					return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, RES_CMD_REJECTED, pkt, 1);
				}
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, RES_CMD_REJECTED, pkt, 1);
			}	
			break;
		case ATTR_ID_7: // Lock JTAG
			res = rmtp_set_jtag_lock_state(data[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FIRMWARE_UPGRADE, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int event_msg_handler(uint8_t netId, uint8_t evtId, uint8_t *data)
{
	switch (evtId) {
		case ALARM_ID_0: // Flow control message timeout event
			LOG("[RMTP] objId(0x%.2x) flow contrl msg timeout\n", OBJ_ID_FIRMWARE_UPGRADE);
			break;
		default:
			return RES_ALARM_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

static int data_section_msg_handler(uint8_t netId, uint8_t seqNum, uint8_t *data)
{
	uint8_t tmp;
	uint32_t size = 0;
	uint32_t cur_size = 0;
	uint32_t offset = 0;
	uint8_t *ciphertext = NULL;

	memset(pkt, 0, 6);
	if (data_recv_state == DATA_RECV_ACTIVE) {
		data_recv_seq_mask |= (1 << seqNum);
		offset = data_recv_offset + (seqNum * 6);
		size = data_image_size - offset;
		// swap
		tmp = data[0];
		data[0] = data[5];
		data[5] = tmp;
		tmp = data[1];
		data[1] = data[4];
		data[4] = tmp;
		tmp = data[2];
		data[2] = data[3];
		data[3] = tmp;	
		// recovery: xor with ciphertext
		ciphertext = rmtp_get_ciphertext();
		data[0] = data[0] ^ ciphertext[0];
		data[1] = data[1] ^ ciphertext[1];
		data[2] = data[2] ^ ciphertext[2];
		data[3] = data[3] ^ ciphertext[3];
		data[4] = data[4] ^ ciphertext[4];
		data[5] = data[5] ^ ciphertext[5];
		if (size >= 6) {
			cur_size = offset + 6;
			size = 6;
		} else {
			cur_size = data_image_size;
			size = data_image_size - offset;
		}
		rmtp_fw_upgrade_write_image(offset, data, size);
		if (data_recv_seq_num < seqNum) {
			data_recv_seq_num = seqNum;
		}
		if (data_cur_size < cur_size) {
			data_cur_size = cur_size;
		}
		data_recv_timeout = 0;
		data_recv_retry = 0;
		data_recv_cnt++;
		DBG("[RMTP] recv data: seqNum:%d cnt:%d/%d\n", seqNum, data_recv_cnt, data_next_seq_cnt);
		if (data_recv_cnt == data_next_seq_cnt) {
			if (check_seq_num(seqNum) == RES_SUCCESS) {
				check_section_window(RES_SUCCESS);
			} else {
				data_recv_seq_num = -1;
				data_recv_seq_mask = 0;
				data_recv_cnt = 0;
				pkt[0] = FLOW_CTRL_RESEND;
				DBG("[RMTP] FlowCtrl: RESEND (szie:%u/%u)\n", data_cur_size, data_image_size);
				rmtp_send_report_message(netId, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
			}
		}	
	} else {
		pkt[0] = FLOW_CTRL_ABORT;
		DBG("[RMTP] FlowCtrl: ABORT\n");
		rmtp_send_report_message(netId, OBJ_ID_FIRMWARE_UPGRADE, ATTR_ID_0, pkt, 1);
	}	

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_firmware_upgrade = {
	OBJ_ID_FIRMWARE_UPGRADE,		// Object ID
	8,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	destroy,						// Destory handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 		// Set Request message handler
	NULL,							// Get Response message handler
	NULL,							// Set Response message handler
	NULL,							// Report message handler
	event_msg_handler,				// Alarm message handler
	data_section_msg_handler,		// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
