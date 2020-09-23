/*
 * cfar.h
 *
 *  Created on: 2017
 *      Author: erichu
 */


#ifndef TARGET_H_
#define TARGET_H_

#include "typedefs.h"

#define MAX_COMPLEXES_CAN_GET	40
#define MAX_COUNT_OF_TARGET		(MAX_COMPLEXES_CAN_GET*3)
typedef struct target_point{
	int16_t				velocity;
	int16_t				range;
	int16_t				aoaidx;
	uint16_t			mag_log2;
	int16_t				vangle;
	int16_t				pos;
	complex24_t  		cmplx[8];
}target_t, *target_p;

typedef enum {
	TGG_ST_READY = 0,
	TGG_ST_FFTS,
	TGG_ST_FFTS_DONE,
	TGG_ST_COMPLEX,
	TGG_ST_AOA,
	TGG_ST_PARSING,
	TGG_ST_INVALID
}TGG_STATE_E;

typedef enum {
	TRK_CTRL_NORMAL				= 0,
	TRK_CTRL_POSITIONING		= 1,
	TRK_CTRL_CALIBRATION 		= 2,
	TRK_CTRL_POWER_DOWN 		= 3,
	TRK_CTRL_INVALID    		= 255
} TRK_CTRL_E;

typedef enum {
	TRK_CTRL_STATUS_OK			= 0,
	TRK_CTRL_STATUS_ONGOING 	= 1,
	TRK_CTRL_STATUS_DISABLED	= 2,
	TRK_CTRL_STATUS_FAIL		= 3,
	TRK_CTRL_STATUS_INVALID		= 255
}TRK_CTRL_STATUS_E;

typedef struct _target_group {
	target_t			targets[MAX_COUNT_OF_TARGET];
	void				(*done)(void*);
	float				vunit;
	float				runit;
	struct _target_group *x;
	uint32_t			time;
	uint16_t			vbins;
	uint16_t			rbins;
	uint16_t			start;
	uint16_t			end;
	uint8_t				tcnt;
	uint8_t				idx;
	uint8_t				rcnt;
	uint8_t				state;
}target_group_t, *target_group_p;

#define MAX_COUNT_OF_TRACKING		0x20
typedef struct tracked_point{
	uint8_t				id;
	uint8_t				cip;
	uint8_t				cip_acc;
	uint8_t				cip_aeb;
	float				rx;
	float				ry;
	float 				range;
	float 				angle;
	float				vx;
	float 				vy;	
	float				ax;				// y axis acceleration
	uint8_t				tracking_id;
	uint8_t				status;
	uint8_t				dynamic_property;
	uint8_t				probability;
	uint16_t			ittc;
	int16_t				vangle;			// vertical angle
	uint8_t				rcs_type;
	uint8_t				guardrail_cnt;
	uint8_t				reserved[3];
}tracking_t, *tracking_p;

typedef struct {
	tracking_t			targets[MAX_COUNT_OF_TRACKING];
	uint16_t			tcnt;
	uint8_t				tunnel_flag;
	uint8_t				auto_calib_flag;
	uint8_t         	auto_calib_left_num;
	uint8_t         	auto_calib_right_num;
	float 				calib_angle;
	TRK_CTRL_E			ctrl;
	TRK_CTRL_STATUS_E	status;
	uint16_t 			frame_num;
}tracking_group_t, *tracking_group_p;

#endif /* TARGET_H_ */
