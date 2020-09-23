/*
 * rmtp_obj_system_security.c
 *
 *  Created on: 2017/09/26
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

static const uint8_t attr_access[5] = {
	ATTR_R,
	ATTR_W,
	ATTR_N,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_N | ATTR_L
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
 	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_3: // Target information report setting
			rmtp_api_get_target_info_report_setting(&pkt[0], &pkt[1]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_TARGET_LIST, attrId, pkt, 1);	
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_3: // Target information report setting
			rmtp_api_set_target_info_report_setting(data[0], data[1]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_TARGET_LIST, attrId, NULL, 0);			
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int send_report_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data, uint8_t size)
{
 	switch (attrId) {
	 	case ALARM_ID_4: // Target information
			return rmtp_send_report_message(netId, OBJ_ID_TARGET_LIST, attrId, data, size);
		default:
			return RES_ALARM_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

const rmtp_obj_t rmtp_obj_target_list = {
	OBJ_ID_TARGET_LIST,				// Object ID
	5,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	NULL, 							// Destroy handler
	NULL,							// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 		// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	NULL,							// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	send_report_msg_handler,		// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
