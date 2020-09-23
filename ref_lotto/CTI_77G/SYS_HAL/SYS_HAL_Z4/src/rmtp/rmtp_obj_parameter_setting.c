/*
 * rmtp_obj_system_config.c
 *
 *  Created on: 2017/10/23
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
	ATTR_R | ATTR_W,
	ATTR_R | ATTR_W
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res=RES_SUCCESS;
			
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // trkp
			res = rmtp_get_trkp(data[0],pkt);
			if (res == RES_SUCCESS) {
				rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 2);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;
			
		case ATTR_ID_1: // trk2
		    res = rmtp_get_trk2(data[0],pkt);
		    if (res == RES_SUCCESS) {
				rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 3);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;
			
		case ATTR_ID_2: // Vehp
		    res = rmtp_get_Vehp(data[0],pkt);
		    if (res == RES_SUCCESS) {
				rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 3);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;	
			
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	int16_t temp_int16;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // trkp
			res = rmtp_set_trkp(data[0],data[1]);
			if (res == RES_SUCCESS) {
			    pkt[0]=data[0];
				rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 1);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;
			
	    case ATTR_ID_1: // trk2
	        memcpy(&temp_int16,&data[1],2);
			res = rmtp_set_trk2(data[0],temp_int16);
			if (res == RES_SUCCESS) {
			    pkt[0]=data[0];
				rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 1);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;
			
	    case ATTR_ID_2: // Vehp
	        memcpy(&temp_int16,&data[1],2);
			res = rmtp_set_Vehp(data[0],temp_int16);
			if (res == RES_SUCCESS) {
			    pkt[0]=data[0];
				rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, pkt, 1);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_PARAMETER_SETTING, attrId, res, NULL, 0);
			}
			break;
	    	
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}
	return res;
}


const rmtp_obj_t rmtp_obj_parameter_setting = {
	OBJ_ID_PARAMETER_SETTING,		// Object ID
	3,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	NULL, 						    // Destroy handler
	NULL,				            // Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 	 	// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	NULL,				            // Report message handler
	NULL,							// Alarm message handler
	NULL,		                    // Data section message handler
	NULL,							// Send request message handler
	NULL,							// Send report message handler
	NULL,							// Send alarm message handler
	NULL							// Send data section message handler
};
