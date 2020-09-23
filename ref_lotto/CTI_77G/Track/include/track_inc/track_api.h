/*
 * track_api.h
 *
 *  Created on: 2017/08/23
 *      Author: benson
 */

#ifndef __TRACK_API_H__
#define __TRACK_API_H__

#include "track_data.h"
#include "tracking.h"

enum {
	CMD_STANDING_OBJS 	= 0,
	CMD_CALIBRATION 	= 1,
	CMD_TRACKING_STOP	= 2
};

typedef void (*track_api_service_control_cb)(uint8_t cmd, uint8_t *data);

typedef struct _tracking_api_st {
	int (*track_frame_rate_set)(int rate);
	int (*track_frame_init)(uint16_t frame, float speed, float yaw, float radius, uint8_t gear, uint8_t door, float acc_z);
	int (*track_frame)(void);
	int (*track_target_filtering)(void);
	int (*track_target_get)(target_st *output);
	int (*track_ipc_handler)(uint8_t msg, void *data);
	int (*track_target_dump)(void);
} tracking_api_st;

tracking_api_st* track_api_init(frame_data_t *fdata, const tracking_pars_t *trkp, tracking_pars2_t *trkp2, const void *warn);
void Get_Track_Lib_Version(void *data);

#endif /* __TRACK_API_H__ */
