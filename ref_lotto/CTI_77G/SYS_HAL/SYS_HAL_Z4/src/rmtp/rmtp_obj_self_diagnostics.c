/*
 * rmtp_obj_self_diagnostics.c
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

static uint8_t pkt[6]= {0};

static const uint8_t attr_access[1] = {
	ATTR_R | ATTR_L
};

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Test result
			pkt[0] = TEST_PASS;
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SELF_DIAGNOSTICS, attrId, pkt, 1);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

const rmtp_obj_t rmtp_obj_self_diagnostics = {
	OBJ_ID_SELF_DIAGNOSTICS,		// Object ID
	1,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	NULL, 							// Destroy handler
	NULL,							// Timeout handler
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
