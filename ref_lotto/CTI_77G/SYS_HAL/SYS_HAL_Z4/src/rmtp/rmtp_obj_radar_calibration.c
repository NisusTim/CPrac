/*
 * rmtp_obj_radar_calibration.c
 *
 *  Created on: 2017/09/27
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

enum {
	CMD_CALIBRATION			= 0,
	CMD_MEASUREMENT			= 1
};

static uint8_t pkt[6]= {0};
static uint8_t cmd_on = 0;
static uint8_t cmd_done = 0;
static uint8_t cmd_netId = RMTP_ITF_UNKNOWN;
static uint8_t cmd_attrId = 0;
static uint8_t cmd_blockId = 0;
static uint8_t cmd_timeout = 0;
static uint8_t cmd_data[20] = {0};
static uint8_t *doppler = NULL;
static uint8_t *measure = NULL;

static const uint8_t attr_access[8] = {
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L,
	ATTR_W | ATTR_L,
	ATTR_R | ATTR_L
};

static int reset(void)
{
	cmd_on = 0;
	cmd_done = 0;
	cmd_attrId = 0;
	cmd_blockId = 0;
	cmd_timeout = 0;
	memset(&cmd_data[0], 0, 20);
	doppler = NULL;
	measure = NULL;
	
	return RES_SUCCESS;
}

static void calibration_done(uint8_t res, float angle, float range, float velocity, float mag, float vangle)
{
	const uint16_t data_size = 20;
	
	memset(&cmd_data[0], 0, 20);
	memset(pkt, 0, 6);
	if ((res == RES_SUCCESS) && (cmd_on == 1)) {
		memcpy(&cmd_data[0], &angle, sizeof(float));
		memcpy(&cmd_data[4], &range, sizeof(float));
		memcpy(&cmd_data[8], &velocity, sizeof(float));
		memcpy(&cmd_data[12], &mag, sizeof(float));
		memcpy(&cmd_data[16], &vangle, sizeof(float));
		cmd_done = 1;
		cmd_timeout = 15;
		memcpy(pkt, (uint8_t *)&data_size, 2);
		rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_0, pkt, 2);
	} else {
		reset();
		rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);		
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_0, RES_CMD_PROCESS_ERR, NULL, 0);
	}	
}	

static void doppler_done(uint8_t res, uint8_t *data)
{
	const uint16_t data_size = 72;

	memset(pkt, 0, 6);
	if ((res == RES_SUCCESS) && (cmd_on == 1)) {
		cmd_done = 1;
		cmd_timeout = 15;
		doppler = data;
		memcpy(pkt, (uint8_t *)&data_size, 2);	//Total 72 Bytes, 15 Blocks See <<Radar Management and Transport Protocol>>
		rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_2, pkt, 6);
	} else {
		reset();
		rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);		
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_2, RES_CMD_PROCESS_ERR, NULL, 0);
	}	
}	

static void measure_done(uint8_t res, uint8_t *data)
{
	const uint16_t data_size = 20;

	memset(pkt, 0, 6);
	if ((res == RES_SUCCESS) && (cmd_on == 1)) {
		cmd_done = 1;
		cmd_timeout = 15;
		measure = data;
		memcpy(pkt, (uint8_t *)&data_size, 2);
		rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_4, pkt, 6);
	} else {
		reset();
		rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_4, RES_CMD_PROCESS_ERR, NULL, 0);
	}
}

static void imu_calib_selftest_done(uint8_t res)
{
	if (cmd_on == 1) {
		memset(pkt, 0, 6);
		if (res == RES_SUCCESS) {
			pkt[0] = 0; // success
			rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, pkt, 6);
		} else {
			pkt[0] = 1; // fail
			rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, pkt, 6);
		}
	} else {
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, RES_CMD_PROCESS_ERR, NULL, 0);
	}
	reset();
	rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
}

static void imu_calib_static_done(uint8_t res, uint8_t *data)
{
	const uint16_t data_size = 16;
	
	memset(&cmd_data[0], 0, 20);
	memset(pkt, 0, 6);
	if (cmd_on == 1) {
		if (res == RES_SUCCESS) {
			memcpy(&cmd_data[0], data, data_size);
			cmd_done = 1;
			cmd_timeout = 15;
			pkt[0] = 0; // success
			memcpy(&pkt[1], (uint8_t *)&data_size, 2);
			rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, pkt, 6);
			return;
		} else {
			pkt[0] = 1; // fail
			rmtp_send_ok_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, pkt, 6);
		}
	} else {
		rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, RES_CMD_PROCESS_ERR, NULL, 0);
	}
	reset();
	rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
}

static int timeout_handler(void)
{	
	if ((cmd_on == 1) && (cmd_timeout > 0)) {
		cmd_timeout--;		
		if (cmd_timeout == 0) {
			reset();
			rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
			if (cmd_attrId == ATTR_ID_0) {
				if (cmd_done == 0) {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_0, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				} else {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_1, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				}
			} else if (cmd_attrId == ATTR_ID_2) {
				if (cmd_done == 0) {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_2, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				} else {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_3, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				}
			} else if (cmd_attrId == ATTR_ID_4) {
				if (cmd_done == 0) {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_4, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				} else {
					rmtp_send_err_response_message(cmd_netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_5, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
				}
			} else if (cmd_attrId == ATTR_ID_6) {
				rmtp_send_err_response_message(cmd_netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, RES_CMD_PROCESS_TIMEOUT, NULL, 0);
			}
			return RES_CMD_PROCESS_TIMEOUT;
		}
	}

	return RES_SUCCESS;
}

static int get_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t res = RES_SUCCESS;
	uint8_t *datap = NULL;
	uint8_t	idx = 0;

	memset(pkt, 0, 6);
	switch (attrId) {		
		case ATTR_ID_1: // Calibration result
			if ((cmd_on == 0) || (cmd_done != 1) || (data[0] != cmd_blockId)|| (cmd_attrId != ATTR_ID_0)) {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_1, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			} else {
				datap = &cmd_data[0];
				if (cmd_blockId == BLOCK_ID_DONE) {
					pkt[0] = cmd_blockId;
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_1, pkt, 1);
					reset();
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
				} else {					
					pkt[0] = cmd_blockId;
					idx = cmd_blockId * 5;
					memcpy(&pkt[1], (datap + idx), 5);
					cmd_timeout = 15;
					cmd_blockId++;
					if (cmd_blockId == 4) {
						cmd_blockId = BLOCK_ID_DONE;
					}
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_1, pkt, 6);
				}
			}	
			return res;
		case ATTR_ID_3: // Doppler result
			if ((cmd_on == 0) || (cmd_done != 1) || (data[0] != cmd_blockId)|| (cmd_attrId != ATTR_ID_2) || (doppler == NULL)) {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_3, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			} else {
				if (cmd_blockId == BLOCK_ID_DONE) {
					pkt[0] = cmd_blockId;
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_3, pkt, 1);
					reset();
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
				} else {					
					pkt[0] = cmd_blockId;
					res = rmtp_get_doppler_data(pkt[0], (uint8_t *)&pkt[1], doppler);
					if (res == RES_SUCCESS) {
						cmd_timeout = 15;
						cmd_blockId++;
						if (cmd_blockId == 15) {
							cmd_blockId = BLOCK_ID_DONE;
						}
						rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_3, pkt, 6);
					} else {
						pkt[0] = cmd_blockId;
						rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_3, res, NULL, 1);
						reset();
						rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
					}
				}
			}	
			return res;	
		case ATTR_ID_5: // Measurement result
			if ((cmd_on == 0) || (cmd_done != 1) || (data[0] != cmd_blockId) || (cmd_attrId != ATTR_ID_4) || (measure == NULL)) {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, attrId, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			} else {
				if (cmd_blockId == BLOCK_ID_DONE) {
					pkt[0] = cmd_blockId;
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, attrId, pkt, 1);
					reset();
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
				} else {
					pkt[0] = cmd_blockId;
					res = rmtp_get_measurement_data(pkt[0], (uint8_t *)&pkt[1], measure);
					if (res == RES_SUCCESS) {
						cmd_timeout = 15;
						cmd_blockId++;
						if (cmd_blockId == 4) {
							cmd_blockId = BLOCK_ID_DONE;
						}
						rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, attrId, pkt, 6);
					} else {
						pkt[0] = cmd_blockId;
						rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, attrId, res, NULL, 1);
						reset();
						rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
					}
				}
			}
			return res;
		case ATTR_ID_7:
			if ((cmd_on == 0) || (cmd_done != 1) || (data[0] != cmd_blockId)|| (cmd_attrId != ATTR_ID_6)) {
				rmtp_send_err_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_7, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			} else {
				datap = &cmd_data[0];
				if (cmd_blockId == BLOCK_ID_DONE) {
					pkt[0] = cmd_blockId;
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_7, pkt, 1);
					reset();
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
				} else {
					pkt[0] = cmd_blockId;
					idx = cmd_blockId * 5;
					memcpy(&pkt[1], (datap + idx), 5);
					cmd_timeout = 15;
					cmd_blockId++;
					if (cmd_blockId == 4) {
						cmd_blockId = BLOCK_ID_DONE;
					}
					rmtp_send_ok_response_message(netId, SUB_TYPE_GET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_7, pkt, 6);
				}
			}
			return res;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

static int set_request_msg_handler(uint8_t netId, uint8_t attrId, uint8_t *data)
{
	uint8_t res = RES_ERROR;
	float range;
	int16_t angle;

	switch (attrId) {
		case ATTR_ID_0: // Calibration control
			if (cmd_on == 0) {
				memcpy(&range, &data[0], sizeof(float));
				memcpy(&angle, &data[4], sizeof(int16_t));
				res = rmtp_calibration_control(range, angle, calibration_done);
				if (res == RES_SUCCESS) {
					cmd_on = 1;
					cmd_done = 0;
					cmd_netId = netId;
					cmd_attrId = ATTR_ID_0;
					cmd_blockId = 0;
					cmd_timeout = 25;
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_START);
				} else {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_0, RES_CMD_PROCESS_ERR, NULL, 0);
				}
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_0, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
		case ATTR_ID_2: // Doppler control
			if (cmd_on == 0) {
				memcpy(&range, &data[1], sizeof(float));
				res = rmtp_doppler_control(data[0], range, doppler_done);
				if (res == RES_SUCCESS) {
					cmd_on = 1;
					cmd_done = 0;
					cmd_netId = netId;
					cmd_attrId = ATTR_ID_2;
					cmd_blockId = 0;
					cmd_timeout = 25;
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_START);
				} else {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_2, RES_CMD_PROCESS_ERR, NULL, 0);
				}	
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_2, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
		case ATTR_ID_4: // Measurement control
			if (cmd_on == 0) {
				memcpy(&range, &data[1], sizeof(float));
				res = rmtp_measurement_control(data[0], range, measure_done);
				if (res == RES_SUCCESS) {
					cmd_on = 1;
					cmd_done = 0;
					cmd_netId = netId;
					cmd_attrId = ATTR_ID_4;
					cmd_blockId = 0;
					cmd_timeout = 25;
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_START);
				} else {
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_4, RES_CMD_PROCESS_ERR, NULL, 0);
				}
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_4, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
		case ATTR_ID_6: // IMU calibration control
			if (cmd_on == 0) {
				if (data[0] <= 1) {
					cmd_on = 1;
					cmd_done = 0;
					cmd_netId = netId;
					cmd_attrId = ATTR_ID_6;
					cmd_blockId = 0;
					cmd_timeout = 50;
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_START);
					if (data[0] == 0) { // self-test
						res = rmtp_imu_calib_selftest_control(imu_calib_selftest_done);
					} else if (data[0] == 1) { // static calibration
						res = rmtp_imu_calib_static_control(imu_calib_static_done);
					}
				} else {
					res = RES_PARAMETER_ERROR;
					rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, RES_PARAMETER_ERROR, NULL, 0);
				}
				if (res == RES_CMD_UNSUPPORTED) {
					res = RES_SUCCESS;
					reset();
					rmtp_set_timer(OBJ_ID_RADAR_CALIBRATION, TIMER_STOP);
					memset(pkt, 0, 6);
					pkt[0] = 2; // unsupported
					rmtp_send_ok_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, pkt, 6);					
				}
			} else {
				rmtp_send_err_response_message(netId, SUB_TYPE_SET, OBJ_ID_RADAR_CALIBRATION, ATTR_ID_6, RES_CMD_REJECTED, NULL, 0);
				return RES_CMD_REJECTED;
			}
			break;
		default:
			return RES_ATTR_ID_UNSUPPORTED;
	}

	return res;
}

const rmtp_obj_t rmtp_obj_radar_calibration = {
	OBJ_ID_RADAR_CALIBRATION,		// Object ID
	8,								// Attribute number
	(uint8_t*)&attr_access, 		// Attribute access
	0,								// Alarm number
	NULL,							// Initialize handler
	NULL, 							// Destroy handler
	timeout_handler,				// Timeout handler
	get_request_msg_handler,		// Get request message handler
	set_request_msg_handler, 	 	// Set request message handler
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
