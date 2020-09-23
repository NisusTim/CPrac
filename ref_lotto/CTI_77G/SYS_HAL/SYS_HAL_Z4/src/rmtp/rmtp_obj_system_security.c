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
static uint8_t admin_state = ADMIN_LOCK;
static uint8_t plaintext[6] = {0};
static uint8_t key[6] = {0};

static const uint8_t attr_access[4] = {
	ATTR_R,
	ATTR_W,
	ATTR_W,
	ATTR_W
};
	 
static int create_key(void)
{
	uint32_t r;
		
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[0] = key[0] = r % 0x100;
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[1] = key[1] = r % 0x100;
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[2] = key[2] = r % 0x100;
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[3] = key[3] = r % 0x100;
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[4] = key[4] = r % 0x100;
	srand(rmtp_get_rand_seed());
	r = rand();
	pkt[5] = key[5] = r % 0x100;
	 
	return 0;
}
	 
static int verify_ciphertext(uint8_t *text, uint8_t action)
{
	uint8_t ciphertext[6] = {0};
	
	ciphertext[0] =  (((plaintext[0] + 15) % 26) ^ key[0]);
	ciphertext[1] =  (((plaintext[1] + 15) % 26) ^ key[1]);
	ciphertext[2] =  (((plaintext[2] + 15) % 26) ^ key[2]);
	ciphertext[3] =  (((plaintext[3] + 15) % 26) ^ key[3]);
	ciphertext[4] =  (((plaintext[4] + 15) % 26) ^ key[4]);
	ciphertext[5] =  (((plaintext[5] + 15) % 26) ^ key[5]);
	rmtp_set_ciphertext(ciphertext);
	LOG("[RMTP] plaintext: %.2x %.2x %.2x %.2x %.2x %.2x\n", plaintext[0], plaintext[1], plaintext[2], plaintext[3], plaintext[4], plaintext[5]);
	LOG("[RMTP] key: %.2x %.2x %.2x %.2x %.2x %.2x\n", key[0], key[1], key[2], key[3], key[4], key[5]);
	LOG("[RMTP] ciphertext(in): %.2x %.2x %.2x %.2x %.2x %.2x\n", text[0], text[1], text[2], text[3], text[4], text[5]);
	LOG("[RMTP] ciphertext(my): %.2x %.2x %.2x %.2x %.2x %.2x\n", ciphertext[0], ciphertext[1], ciphertext[2], ciphertext[3], ciphertext[4], ciphertext[5]);
	PRINTF("[RMTP] admin action:%d\n", action);
	if (memcmp(ciphertext, text, 6) == 0) {
		admin_state = action;
		PRINTF("[RMTP] admin state:%d matched!\n", admin_state);
		rmtp_set_admin_state(admin_state);
		return RES_SUCCESS;
	}
	admin_state = ADMIN_LOCK;
	PRINTF("[RMTP] Lock => unmatched\n");
	rmtp_set_admin_state(admin_state);
	
	return RES_ERROR;
}

static int init(void)
{
	admin_state = rmtp_get_admin_state();	
	return RES_SUCCESS;
}
	 
static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
 	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_0: // Administrative state
			pkt[0] = admin_state;
			return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_SYSYTEM_SECURITY, attrId, pkt, 1);
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_ERROR;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
 	uint8_t res = RES_SUCCESS;

	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_1: // System administrative key
			memcpy(plaintext, data, 6);
			create_key();
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSYTEM_SECURITY, attrId, pkt, 6);
		case ATTR_ID_2: // System unlock
			res = verify_ciphertext(data, ADMIN_UNLOCK);
			pkt[0] = admin_state;
			if (res != RES_SUCCESS) {
				res = rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSYTEM_SECURITY, attrId, RES_PARAMETER_ERROR, pkt, 6);
			} else {
				res = rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSYTEM_SECURITY, attrId, pkt, 6);
			}
			return res;
		case ATTR_ID_3: // System lock
			res = verify_ciphertext(data, ADMIN_LOCK);
			pkt[0] = admin_state;
			if (res != RES_SUCCESS) {
				res = rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSYTEM_SECURITY, attrId, RES_PARAMETER_ERROR, pkt, 6);
			} else {
				res = rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_SYSYTEM_SECURITY, attrId, pkt, 6);
			}
			return res;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}
	 
	return RES_ERROR;
}

const rmtp_obj_t rmtp_obj_system_security = {
	OBJ_ID_SYSYTEM_SECURITY,		// Object ID
	4,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	init,							// Initialize handler
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
