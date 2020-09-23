/*
 * rmtp_obj_firmware_version.c
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

static uint8_t fw_on = 0;
static uint8_t fw_net_id = RMTP_ITF_UNKNOWN;
static uint8_t fw_timeout = 0;
static uint8_t *fw_data = NULL;

static uint8_t pkt[6]= {0};

static const uint8_t attr_access[5] = {
	ATTR_R,
	ATTR_R,
	ATTR_R,
	ATTR_R,
	ATTR_R
};

static int reset(void)
{
	fw_on = 0;
	fw_net_id = RMTP_ITF_UNKNOWN;
	fw_timeout = 0;
	fw_data = NULL;

	return RES_SUCCESS;
}

static int destroy(void) 
{
	if (fw_on == 1) {
		rmtp_set_timer(OBJ_ID_FIRMWARE_VERSION, TIMER_STOP);
		reset();
	}

	return RES_SUCCESS;
}

static int timeout_handler(void)
{	
	if ((fw_on == 1) && (fw_timeout > 0)) {
		fw_timeout--;
		if (fw_timeout == 0) {
			LOG("[RMTP] firmware version: timeout!\n");
			rmtp_set_timer(OBJ_ID_FIRMWARE_VERSION, TIMER_STOP);
			reset();
			rmtp_send_err_response_message(fw_net_id, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, ATTR_ID_4, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
			return RES_SUCCESS;
		}
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t res = RES_SUCCESS;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Bootloader version
		case ATTR_ID_1: // Z4 firmware version
		case ATTR_ID_2: // Z7-0 firmware version
		case ATTR_ID_3: // Z7-1 firmware version
			res = rmtp_get_firmware_version(attrId, (uint8_t*)&pkt);			
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, RES_PARAMETER_ERROR, NULL, 0);
			}
			break;
		case ATTR_ID_4: // Firmware revision
			pkt[0] = data[0]; // blockId
			if ((fw_on == 0) && (data[0] == 0)) {
				fw_data = rmtp_get_data();
				rmtp_get_firmware_version(FW_REVISION, fw_data);
				if (fw_data != NULL) {
					fw_on = 1;
					fw_net_id = netId;
					fw_timeout = 10;
					memcpy(&pkt[1], fw_data, 5);
					return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, pkt, 6);
				}
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, RES_CMD_PROCESS_ERR, NULL, 0);
			} else if ((fw_on == 1) && (data[0] > 0)) {
				if (data[0] < 6) {
					fw_net_id = netId;
					fw_timeout = 10;
					memcpy(&pkt[1], fw_data + (data[0] * 5), 5);
				} else if (data[0] == 6) {
					fw_net_id = netId;
					fw_timeout = 10;
					memcpy(&pkt[1], fw_data + (data[0] * 5), 2);
					rmtp_set_timer(OBJ_ID_SYSTEM_CONFIG, TIMER_STOP);
					reset();
				} else {
					return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, RES_PARAMETER_ERROR, NULL, 0);
				}
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, pkt, 6);
			}
			rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FIRMWARE_VERSION, attrId, RES_CMD_REJECTED, NULL, 0);
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

const rmtp_obj_t rmtp_obj_firmware_version = {
	OBJ_ID_FIRMWARE_VERSION,		// Object ID
	5,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	destroy, 						// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	NULL, 							// Set request message handler
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
