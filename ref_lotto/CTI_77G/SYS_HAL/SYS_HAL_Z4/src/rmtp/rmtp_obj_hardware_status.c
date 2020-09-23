/*
 * rmtp_obj_hardware_status.c
 *
 *  Created on: 2017/09/25
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
	CTRL_DISABLE_TEST			= 0,
	CTRL_ENABLE_TEST			= 1,
	CTRL_NONE					= 255
};

enum {
	ATTR_ID_RF_IC_STATUS		= 1,
	ATTR_ID_MCU_VOLTAGE			= 2,
	ATTR_ID_MCU_TEMPERATURE		= 3
};

enum {
	SERV_CTRL_ENABLE_TEST		= 0,
	SERV_CTRL_DISABLE_TEST		= 1
};

static uint8_t pkt[6]= {0};
static uint8_t serv_ctrl = CTRL_NONE;
static int8_t serv_ctrl_net_id = RMTP_ITF_UNKNOWN;
static uint8_t serv_ctrl_attr_mask = 0;
static int8_t serv_ctrl_cnt = 0;
static uint8_t serv_ctrl_time_interval = 0;
static uint8_t serv_ctrl_tick = 0;
static uint8_t pid = 0;

static const uint8_t attr_access[6] = {
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L
};

static void reset(void)
{
	serv_ctrl = CTRL_NONE;
	serv_ctrl_attr_mask = 0;
	serv_ctrl_cnt = 0;
	rmtp_set_timer(OBJ_ID_HARDWARE_STATUS, TIMER_STOP);
}

static int destroy(void)
{
	if ((serv_ctrl == CTRL_NONE) || (serv_ctrl_cnt == 0)) {
		return RES_SUCCESS;
	}
	reset();
	
	return RES_SUCCESS;
}

static int timeout_handler(void)
{
	pid = product_info_get()->product;
	if ((serv_ctrl == CTRL_NONE) || (serv_ctrl_cnt == 0)) {
		return RES_SUCCESS;
	}

	serv_ctrl_tick++;
	if (serv_ctrl_tick == serv_ctrl_time_interval) {
		if (serv_ctrl_cnt > 0) {
			serv_ctrl_cnt--;
		}
		if (serv_ctrl_attr_mask & ATTR_BIT_MASK_1) { // RF-IC status
			memset(pkt, 0, 6);
			rmtp_get_rf_ic_status(&pkt[0]);
			rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_1, pkt, 1);
		}
		if (serv_ctrl_attr_mask & ATTR_BIT_MASK_2) {
			switch (pid) {
				case PROD_ID_FCW_DUAL:
				case PROD_ID_FCW_2_0_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL:
				case PROD_ID_BSD_Omni_1_0_COMBO:
				case PROD_ID_BSD_2BEAM_DUAL:
				case PROD_ID_BSD_TwoB_2_0_COMBO:
				case PROD_ID_BSD_TwoB_3_1_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL_79G:
					{	// MCU voltage
						memset(pkt, 0, 6);
						pkt[0] = 1;	//Type 1
						rmtp_get_mcu_voltage(&pkt[0]);
						rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_2, pkt, 5);
					}
					break;
				default:
					{	//Voltage
						memset(pkt, 0, 6);
						pkt[0] = 0;	//Type 0
						rmtp_get_power_voltage(&pkt[0]);
						rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_2, pkt, 5);

						memset(pkt, 0, 6);
						pkt[0] = 2;	//Type 2
						rmtp_get_rfic_voltage(&pkt[0]);
						rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_2, pkt, 5);
					}
					break;
			}
		}
		if (serv_ctrl_attr_mask & ATTR_BIT_MASK_3) {
			switch (pid) {
				case PROD_ID_FCW_DUAL:
				case PROD_ID_FCW_2_0_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL:
				case PROD_ID_BSD_Omni_1_0_COMBO:
				case PROD_ID_BSD_2BEAM_DUAL:
				case PROD_ID_BSD_TwoB_2_0_COMBO:
				case PROD_ID_BSD_TwoB_3_1_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL_79G:
					{	// MCU temperature
						memset(pkt, 0, 6);
						rmtp_get_mcu_temperature(&pkt[0]);
						rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_3, pkt, 2);
					}
					break;
				default:
					{	//Temperature
						memset(pkt, 0, 6);
						rmtp_get_temperature(&pkt[0]);
						rmtp_send_report_message(serv_ctrl_net_id, OBJ_ID_HARDWARE_STATUS, ATTR_ID_3, pkt, 3);
					}
					break;
			}
		}
		if (serv_ctrl_attr_mask & ATTR_BIT_MASK_4) { // CAN 0
			pkt[0] = 0x12;
			pkt[1] = 0x34;
			pkt[2] = 0x56;
			pkt[3] = 0x78;
			pkt[4] = 0x9A;
			pkt[5] = 0xBC;
			rmtp_send_report_message(RMTP_ITF_CAN0, OBJ_ID_HARDWARE_STATUS, ATTR_ID_4, pkt, 6);
		}
		if (serv_ctrl_attr_mask & ATTR_BIT_MASK_5) { // CAN 2
			pkt[0] = 0x12;
			pkt[1] = 0x34;
			pkt[2] = 0x56;
			pkt[3] = 0x78;
			pkt[4] = 0x9A;
			pkt[5] = 0xBC;
			rmtp_send_report_message(RMTP_ITF_CAN2, OBJ_ID_HARDWARE_STATUS, ATTR_ID_5, pkt, 6);
		}
		serv_ctrl_tick = 0;
	}
	if (serv_ctrl_cnt == 0) {
		reset();
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	pid = product_info_get()->product;
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_1: // RF-IC status
			rmtp_get_rf_ic_status(&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 1);
		case ATTR_ID_2: // MCU voltage
			switch (pid) {
				case PROD_ID_FCW_DUAL:
				case PROD_ID_FCW_2_0_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL:
				case PROD_ID_BSD_Omni_1_0_COMBO:
				case PROD_ID_BSD_2BEAM_DUAL:
				case PROD_ID_BSD_TwoB_2_0_COMBO:
				case PROD_ID_BSD_TwoB_3_1_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL_79G:
					{	// MCU voltage
						pkt[0] = 1;	//Type 1
						rmtp_get_mcu_voltage(&pkt[0]);
						return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 5);
					}
					break;
				default:
					{	//Voltage
						if(data[0] == 0)
						{
							pkt[0] = 0;	//Type 0
							rmtp_get_power_voltage(&pkt[0]);
							return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 5);
						}
						else if (data[0] == 1)
						{
							pkt[0] = 1;	//Type 1
							rmtp_get_mcu_voltage(&pkt[0]);
							return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 5);
						}
						else if(data[0] == 2)
						{
							pkt[0] = 2;	//Type 2
							rmtp_get_rfic_voltage(&pkt[0]);
							return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 5);
						}
						else
						{
							return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, RES_PARAMETER_ERROR, pkt, 1);
						}
					}
					break;
			}
			break;
		case ATTR_ID_3: // MCU temperature
			switch (pid) {
				case PROD_ID_FCW_DUAL:
				case PROD_ID_FCW_2_0_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL:
				case PROD_ID_BSD_Omni_1_0_COMBO:
				case PROD_ID_BSD_2BEAM_DUAL:
				case PROD_ID_BSD_TwoB_2_0_COMBO:
				case PROD_ID_BSD_TwoB_3_1_COMBO:
				case PROD_ID_BSD_OMMIT_DUAL_79G:
					{	// MCU temperature
						rmtp_get_mcu_temperature(&pkt[0]);
						return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 2);
					}
					break;
				default:
					{	//Temperature
						rmtp_get_temperature(&pkt[0]);
						return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 3);
					}
					break;
			}
			break;
		case ATTR_ID_4: // CAN 0
		case ATTR_ID_5: // CAN 1
			pkt[0] = 0x12;
			pkt[1] = 0x34;
			pkt[2] = 0x56;
			pkt[3] = 0x78;
			pkt[4] = 0x9A;
			pkt[5] = 0xBC;
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_HARDWARE_STATUS, attrId, pkt, 6);	
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Service control			
			if (data[0] == CTRL_DISABLE_TEST) {
				reset();
			} else if (data[0] == CTRL_ENABLE_TEST) {
				serv_ctrl = data[0];
				serv_ctrl_net_id = netId;
				serv_ctrl_attr_mask = data[1];
				if (data[2] == 0) {
					serv_ctrl_cnt = -1;
				} else {
					serv_ctrl_cnt = data[2];
				}
				serv_ctrl_time_interval = data[3];
				LOG("[RMTP] HW servCrtl code=%d mask=0x%.2x cnt=%d intvl=%d\n", serv_ctrl, serv_ctrl_attr_mask, serv_ctrl_cnt, serv_ctrl_time_interval);
				serv_ctrl_tick = 0;
				rmtp_set_timer(OBJ_ID_HARDWARE_STATUS, TIMER_START);
			}
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_HARDWARE_STATUS, attrId, data, 6);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}


const rmtp_obj_t rmtp_obj_hardware_status = {
	OBJ_ID_HARDWARE_STATUS,			// Object ID
	6,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	destroy,						// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 		// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	NULL,							// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
