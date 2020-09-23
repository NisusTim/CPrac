/*
 * rmtp_obj_rf_ic_setting.c
 *
 *  Created on: 2018/09/12
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
static uint8_t moduleAddr = 0xFF;
static uint16_t regAddr = 0;

static const uint8_t attr_access[7] = {
 	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
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
	 	case ATTR_ID_0: // Register
	 		moduleAddr = data[0];
			regAddr = (data[1] << 8) + data[2];
			res = rmtp_get_rf_ic_register(moduleAddr, regAddr, &pkt[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_1: // Frequency
			res = rmtp_get_rf_ic_frequency(rmtp_tef810x_txid_to_profile(data[0]), &pkt[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_2: // TX operational state
	 		res = rmtp_get_rf_ic_operational_state(data[0], &pkt[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_3: // TX gain
            pkt[0]=data[0];
            res = rmtp_get_rf_ic_tx_gain(rmtp_tef810x_txid_to_profile(data[0]), &pkt[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 2);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_4: // RX gain
            res = rmtp_get_rf_ic_rx_gain(rmtp_tef810x_txid_to_profile(data[0]), &pkt[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 6);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_5: // CW mode
		    res = rmtp_get_rf_ic_cw_tx_gain(&pkt[0]);
		    if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 3);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_6: // Tx High Level
		    res=rmtp_get_Tx_High_Level(data[0],&pkt[0],&pkt[1]);
		    if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 2);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	int res = RES_SUCCESS;
	uint32_t value;
	uint16_t value16;
	
	memset(pkt, 0, 6);
	switch (attrId) {
		case ATTR_ID_0: // Register
			if (data[0] == 0) { // Header
				moduleAddr = data[1];
				regAddr = (data[2] << 8) + data[3];
			} else if (data[0] == 1) { // Data
				if (moduleAddr == 255) {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, RES_CMD_PROCESS_ERR, NULL, 0);
				} else {
					memcpy(&value, &data[1], sizeof(uint32_t));
					rmtp_set_rf_ic_register(moduleAddr, regAddr, value);
				}
			}
			return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, NULL, 0);
		case ATTR_ID_1: // Frequency
			memcpy(&value16, &data[1], sizeof(uint16_t));
			res = rmtp_set_rf_ic_frequency(rmtp_tef810x_txid_to_profile(data[0]), value16);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_3: // TX gain
            res = rmtp_set_rf_ic_tx_gain(rmtp_tef810x_txid_to_profile(data[0]), &data[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_4: // RX gain
            res = rmtp_set_rf_ic_rx_gain(rmtp_tef810x_txid_to_profile(data[0]), &data[1]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
			break;
		case ATTR_ID_5: // CW mode
		    res = rmtp_set_rf_ic_cw_tx_gain(&data[0]);
			if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, NULL, 0);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
		    break;	
		case ATTR_ID_6: // Tx High Level
		    res = rmtp_set_Tx_High_Level(data[0],data[1],&pkt[0],&pkt[1]);
		    if (res == RES_SUCCESS) {
				return rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, pkt, 2);
			} else {
				return rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RF_IC_SETTING, attrId, res, NULL, 0);
			}
		    break;    
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return RES_SUCCESS;
}

const rmtp_obj_t rmtp_obj_rf_ic_setting = {
	OBJ_ID_RF_IC_SETTING, 			// Object ID
	7, 								// Attribute number
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


