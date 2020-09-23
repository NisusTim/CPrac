/*
 * rmtp_obj_signal_process_parameter.c
 *
 *  Created on: 2019/07/23
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

#define ATTRIBUTE_NUMBER 4

static uint8_t pkt[6]= {0};

//static uint8_t moduleAddr = 0xFF;
//static uint16_t regAddr = 0;

static const uint8_t attr_access[ATTRIBUTE_NUMBER] = {
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
	 	
		case ATTR_ID_0: // spt aoa shift
			res = (int16_t)rmtp_get_spt_aoa_shift(data[0],pkt);
			if (res == RES_SUCCESS) {
				rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 3);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
			}
			break;
			
		case ATTR_ID_1: //calibration mode
		        pkt[0]=rmtp_get_calib_mode();
		        rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		    break;
		
		case ATTR_ID_2: //calibration coefficients
		    pkt[0]=data[0];
		    if(pkt[0]==255){
		        rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		    }else{
		        res= rmtp_get_calib_coef(data[0],&pkt[1]);
		        if (res == RES_SUCCESS) {
		            rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 6);
		        }else{
                    rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);		        
		        }
		    }
		    break;
		
		case ATTR_ID_3: //get zero angle calibration bandwidth
		{
			uint16_t temp_data = 0;
		    res = rmtp_get_calib_bandwidth((uint16_t*)(&temp_data));    //get bandwidth value (each unit = 1MHz)
		    if (res == RES_SUCCESS) {
		    	pkt[0] = (uint8_t)(temp_data / 10);                     //convert bandwidth value unit (each unit = 10MHz)
		    	rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		    }else{
		    	rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
		    }
		    break;
		}

		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	int16_t value;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		
		case ATTR_ID_0: // spt aoa shift
		    memcpy(&value,&data[1],sizeof(int16_t));
			res = rmtp_set_spt_aoa_shift(data[0],value);
			if (res == RES_SUCCESS) {
				rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, NULL, 0);
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
			}
			break;
		
		case ATTR_ID_1: //calibration mode
		    res=rmtp_set_calib_mode(data[0]);
		    if (res == RES_SUCCESS) {
		        rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, NULL, 0);
		    }else{
		        rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
		    }
		    break;
		
		case ATTR_ID_2: //calibration coefficients
		    pkt[0]=data[0];
		    if(pkt[0]==255){
		        rmtp_save_calib_coef();
		        rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		    }else{
		        res=rmtp_set_calib_coef(data[0],&data[1]);
		        if (res == RES_SUCCESS) {
		            rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		        }else{
		            rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
		        }
		    }
		    break;
		
		case ATTR_ID_3: //set zero angle calibration bandwidth
		    res = rmtp_set_calib_bandwidth((uint16_t)(data[0] * 10));    //input bandwidth value (each unit = 10MHz)
		    if (res == RES_SUCCESS) {
		    	rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, pkt, 1);
		    }else{
		    	rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SIGNAL_PROCESS_PARAMETER, attrId, res, NULL, 0);
		    }
		    break;

		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

const rmtp_obj_t rmtp_obj_signal_process_parameter = {
	OBJ_ID_SIGNAL_PROCESS_PARAMETER,// Object ID
	ATTRIBUTE_NUMBER, 				// Attribute number
	(uint8_t*)&attr_access,		 	// Attribute access
	0, 								// Alarm number
	NULL,							// Initialize handler
	NULL,							// Destroy handler
	NULL,							// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler,		// Set request message handler
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


