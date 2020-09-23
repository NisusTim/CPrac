/*
 * rmtp_obj_system_log.c
 *
 *  Created on: 2017/11/08
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

static const uint8_t attr_access[3] = {
	ATTR_N,
	ATTR_N,
	ATTR_N
};

static int send_alarm_data(uint8_t netId, uint8_t alarmId, uint8_t *data, uint8_t size)
{
	uint8_t *dataPtr = data;
	uint8_t dataSize = size;
	uint8_t outSize = 0;
	
	while (dataSize) {
		if (dataSize >= 6) {
			outSize = 6;
		} else {
			outSize = dataSize;
		}	
		rmtp_send_alarm_message(netId, OBJ_ID_SYSTEM_LOG, alarmId, dataPtr, outSize);
		dataPtr += outSize;
	 	dataSize -= outSize;		
	}

	return RES_SUCCESS;
}	
	 
static int send_alarm_msg_handler(uint8_t netId, uint8_t alarmId, uint8_t *data, uint8_t size)
{
 	switch (alarmId) {
	 	case ALARM_ID_0: // RF IC status
	 	case ALARM_ID_1: // FCCU status
	 	case ALARM_ID_2: // Stack dump
			return send_alarm_data(netId, alarmId, data, size);
		default:
			return RES_ALARM_ID_UNSUPPORTED;	
	}
	 
	return RES_ERROR;
}
	 
const rmtp_obj_t rmtp_obj_system_log = {
	OBJ_ID_SYSTEM_LOG,	// Object ID
	3, 							 	// Attribute number
	(uint8_t*)&attr_access,		 	// Attribute access
	3, 							 	// Alarm number
	NULL,							// Initialize handler
	NULL,							// Destroy handler
	NULL,							// Timeout handler
	NULL,							// Get request message handler
	NULL,							// Set request message handler
	NULL,							// Get response message handler
	NULL,							// Set response message handler
	NULL,			 				// Report message handler
	NULL,							// Alarm message handler
	NULL,							// Data section message handler
	NULL,							// Send request message handler
	NULL,		 					// Send report message handler
	send_alarm_msg_handler,			// Send alarm message handler
	NULL							// Send data section message handler
};
