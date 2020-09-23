/*
 * rmtp_obj_radar_system.c
 *
 *  Created on: 2017/09/22
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

static uint8_t pkt[6]= {0};
static uint8_t check_spt_state = 0;
static uint8_t check_spt_state_cnt = 0;
static uint8_t check_spt_state_net_id = RMTP_ITF_UNKNOWN;

static const uint8_t attr_access[8] = {
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_NONE,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_W | ATTR_L
};

static int destroy(void) 
{
	if (check_spt_state == 1) {
		check_spt_state = 0;
		check_spt_state_cnt = 0;
		rmtp_set_timer(OBJ_ID_RADAR_SYSYTEM, TIMER_STOP);
	}
	
	return RES_SUCCESS;
}

static int timeout_handler(void)
{	
	if (check_spt_state == 1) {
		if (rmtp_get_operational_state() == OPEAR_STATE_PAUSE) {
			rmtp_send_ok_response_message(check_spt_state_net_id, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, ATTR_ID_1, NULL, 0);
			check_spt_state = 0;
			check_spt_state_cnt = 0;
			LOG("[RMTP] SPT pause ready!\n");
			rmtp_set_timer(OBJ_ID_RADAR_SYSYTEM, TIMER_STOP);
			return RES_SUCCESS;
		}
		check_spt_state_cnt--;
		if (check_spt_state_cnt == 0) {
			rmtp_send_err_response_message(check_spt_state_net_id, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, ATTR_ID_1, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
			check_spt_state = 0;
			check_spt_state_cnt = 0;
			LOG("[RMTP] SPT pause not-ready: timeout!\n");
			rmtp_set_timer(OBJ_ID_RADAR_SYSYTEM, TIMER_STOP);
			return RES_SUCCESS;
		}
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Serial number
			if (data[0] <= 3) {
				pkt[0] = data[0]; // block number
				rmtp_get_serial_number(data[0], (uint8_t *)&pkt[1]);
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		case ATTR_ID_1: // Operational state
			pkt[0] = rmtp_get_operational_state();
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 1);
		case ATTR_ID_2: // Product ID
			rmtp_get_product_id((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 2);
		case ATTR_ID_3: // Customer ID
			rmtp_get_customer_id((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 2);
		case ATTR_ID_4: // Device ID
			rmtp_get_device_id((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 2);
		case ATTR_ID_6: // System information
			if ((data[0] == 3) && (data[1]) == 0) { // Manufacture date
				pkt[0] = data[0];
				pkt[1] = data[1];
				rmtp_get_manufacture_date((uint8_t *)&pkt[2]);
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_CMD_UNSUPPORTED, NULL, 0);
			}
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t state = OPEAR_STATE_UNKNOWN;
	uint16_t id;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Serial number
			if (data[0] <= 3) {
				pkt[0] = data[0]; // block number
				rmtp_set_serial_number(data[0], (uint8_t *)&data[1]);
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		case ATTR_ID_1: // Operational state
			if ((data[0] == OPEAR_STATE_ACTIVE) || (data[0] == OPEAR_STATE_PAUSE)) {
				if (check_spt_state == 1) {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_CMD_REJECTED, NULL, 0);
					return RES_CMD_REJECTED;
				}
				state = rmtp_get_operational_state();
				if (state != data[0]) {
					rmtp_set_operational_state(data[0]);
				}	
				if (data[0] == OPEAR_STATE_PAUSE) {
					check_spt_state = 1;
					check_spt_state_cnt = 10;
					check_spt_state_net_id = netId;
					rmtp_set_timer(OBJ_ID_RADAR_SYSYTEM, TIMER_START);
				} else {
					rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, NULL, 0);
				}
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		case ATTR_ID_4: // Device ID
			id = (data[0] << 8) + data[1];
			rmtp_set_device_id(id);
			rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, NULL, 0);
			break;
		case ATTR_ID_6: // System information
			if ((data[0] == 3) && (data[1]) == 0) { // Manufacture date
				pkt[0] = data[0];
				pkt[1] = data[1];
				rmtp_set_manufacture_date((uint8_t *)&data[2]);
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, RES_CMD_UNSUPPORTED, NULL, 0);
			}
		case ATTR_ID_7: // System reset
			rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_SYSYTEM, attrId, NULL, 0);
			rmtp_system_reset(data[0]);
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_radar_system = {
	OBJ_ID_RADAR_SYSYTEM,			// Object ID
	8,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	1,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
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
