/*
 * rmtp_obj_radar_field_of_view.c
 *
 *  Created on: 2018/08/24
 *      Author: Cubtek
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

static const uint8_t attr_access[6] = {
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // FOV width
			rmtp_get_field_of_view_width((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
		case ATTR_ID_1: // FOV range
			rmtp_get_field_of_view_range((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
		case ATTR_ID_2: // FOV angle
			rmtp_get_field_of_view_angle((uint8_t *)&pkt[0]);			
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
		case ATTR_ID_3: // AOA shift
			rmtp_get_aoa_shift((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
		case ATTR_ID_4: // Position shift
			rmtp_get_lateral_shift((uint8_t *)&pkt[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
		case ATTR_ID_5: // View zone
			pkt[0] = data[0]; // index
			res = rmtp_get_view_zone_value(data[0], (uint8_t *)&pkt[1]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, res, NULL, 0);
			}
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // FOV width
			rmtp_set_field_of_view_width((uint8_t *)&data[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, NULL, 0);
		case ATTR_ID_1: // FOV range
			rmtp_set_field_of_view_range((uint8_t *)&data[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, NULL, 0);
		case ATTR_ID_2: // FOV angle
			rmtp_set_field_of_view_angle((uint8_t *)&data[0]);			
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, NULL, 0);
		case ATTR_ID_3: // AOA shift
			rmtp_set_aoa_shift((uint8_t *)&data[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, NULL, 0);
		case ATTR_ID_4: // Position shift
			rmtp_set_lateral_shift((uint8_t *)&data[0]);
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, NULL, 0);
		case ATTR_ID_5: // View zone
			pkt[0] = data[0]; // index
			res = rmtp_set_view_zone_value(data[0], (uint8_t *)&data[1]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, pkt, 1);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_FIELD_OF_VIEW, attrId, res, pkt, 1);
			}
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_radar_field_of_view = {
	OBJ_ID_RADAR_FIELD_OF_VIEW,		// Object ID
	6,								// Attribute number
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
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
