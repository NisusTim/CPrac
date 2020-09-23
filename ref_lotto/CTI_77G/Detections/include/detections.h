/*
 * detections.h
 *
 *  Created on: Feb 16, 2019
 *      Author: erichu
 */

#ifndef DETECTIONS_DETECTIONS_H_
#define DETECTIONS_DETECTIONS_H_

#include "typedefs.h"

#define LIGHT_SPEED						299792458	// mm/s
#define PI 								(3.14159265359)
#define DEGREE_OF_RADIAN(_x_)			((_x_)*(180/PI))
#define RADIAN_OF_DEGREE(_r_)			((_r_)*(PI/180))
#define DELTA(_a,_b)					(((_a)>=(_b))?((_a)-(_b)):((_b)-(_a)))

#define SAMPLES_PER_CHIRP				512	// number of samples per chirp -> has to be integer dividable by CHIRPS_PER_CTE_TT
#define CHIRPS_PER_FRAME				128	// number of chirps per frame
#define FFT3D_BINS						16
#define RX_ACTIVES						4		// number of active RX channels
#define TOTAL_RX_ACTIVES				(RX_ACTIVES*2)
#define BINS_OF_AOA_FFT					1024

#define FRAME_FLAG_TRACK_ENABLED		0x80
#define FRAME_FLAG_LOG_MEASUREMENTS		0x40
#define FRAME_FLAG_HIST_THLD_PEAK		0x20
#define FRAME_FLAG_STANDING_LSR			0x08
#define FRAME_FLAG_LR_SP_VELO_EXPAND	0x04
#define FRAME_FLAG_LR_VELO_EXPAND		0x02
#define FRAME_FLAG_SR_VELO_EXPAND		0x01

#define MEAS_FLAG_FROM_RAWS				0x01
#define MEAS_FLAG_CORE_DEBUG			0x02
#define MEAS_FLAG_LR_SP_VELO_EXPAND		0x04
#define MEAS_FLAG_LOG_MEASUREMENTS		0x08
#define MEAS_FLAG_LR_VELO_EXPAND		0x10
#define MEAS_FLAG_SR_VELO_EXPAND		0x20
#define MEAS_FLAG_AOA_DEBUG				0x40
#define MEAS_FLAG_FFT3D_DEBUG			0x80
#define MEAS_FLAG_ASSO_DEBUG			0x100
#define MEAS_FLAG_MUSIC_DEBUG			0x200

#define MEAS_MOD_WR						SPT.WR_R45_RE.R
#define MEAS_FLAGS_WR					SPT.WR_R45_IM.R
#define SPT_FBMS_STATE_WR				SPT.WR_R46_RE.R
#define MEAS_STATE_WR					SPT.WR_R46_IM.R
//#define MEAS_SHIFTS_WR					SPT.WR_R44_IM.R

typedef enum {
	FRAME_CTX_IDX_NEAR = 0,
	FRAME_CTX_IDX_LONG = 1,
	FRAME_CTXS_COUNT,
} FRAME_CTX_IDX_E;

#endif /* DETECTIONS_DETECTIONS_H_ */
