/*
 * rmtp_obj_communication_setting.c
 *
 *  Created on: 2019/6/10
 *      Author: WoodLiu
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
	ATTR_R | ATTR_W,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_2: // Can Baud Rate 
		    pkt[0] = data[0];
		    res = rmtp_get_can_baud_rate(data[0],&pkt[1]);
		    if(RES_SUCCESS==res){
		        rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_COMMUNICATION_SETTING, attrId, pkt, 2);         
		    }else{
		        rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_COMMUNICATION_SETTING, attrId, RES_PARAMETER_ERROR, NULL, 0);
		    }
		    break;
		    
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_2: // Can Baud Rate 
			res=rmtp_set_can_baud_rate(data[0],data[1]);
			if(RES_SUCCESS==res){
			    rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_COMMUNICATION_SETTING, attrId, NULL, 0);
			}else{
			    rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_COMMUNICATION_SETTING, attrId, res, NULL, 0);
			}
			break;
			
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_communication_setting = {
	OBJ_ID_COMMUNICATION_SETTING,	// Object ID
	3,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	NULL,							// Alarm number
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
