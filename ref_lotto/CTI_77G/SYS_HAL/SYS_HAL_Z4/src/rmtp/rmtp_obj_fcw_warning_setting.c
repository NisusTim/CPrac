/*
 * rmtp_obj_fcw_warning_setting.c
 *
 *  Created on: 2019/01/24
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

static const uint8_t attr_access[3] = {
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{	
	int res = RES_SUCCESS;
	
	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_0: // Warning flags		
			res = rmtp_get_fcw_warning_flags(pkt);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		case ATTR_ID_1: // Warning speed level
			pkt[0] = data[0];			
			res = rmtp_get_fcw_warning_speed_level(data[0], &pkt[1]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		case ATTR_ID_2: // Warning TTC level
			pkt[0] = data[0];
			pkt[1] = data[1];
			res = rmtp_get_fcw_warning_ttc_level(data[0], data[1], &pkt[2]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{	
	int res = RES_SUCCESS;
	
	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_0: // Warning flags
			res = rmtp_set_fcw_warning_flags(data);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		case ATTR_ID_1: // Warning speed level
			res = rmtp_set_fcw_warning_speed_level(data[0], &data[1]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		case ATTR_ID_2: // Warning TTC level
			res = rmtp_set_fcw_warning_ttc_level(data[0], data[1], &data[2]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, pkt, 6);
			}
			return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_FCW_WARNING_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}
	
	return RES_ERROR;
}

const rmtp_obj_t rmtp_obj_fcw_warning_setting = {
	OBJ_ID_FCW_WARNING_SETTING,		// Object ID
	3,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	NULL,							// Destory handler
	NULL,							// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 		// Set Request message handler
	NULL,							// Get Response message handler
	NULL,							// Set Response message handler
	NULL,							// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};

