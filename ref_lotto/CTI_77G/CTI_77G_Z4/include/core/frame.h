/*
 * frame.h
 *
 *  Created on: 2017�~9��21��
 *      Author: erichu
 */

#ifndef FRAME_H_
#define FRAME_H_

#define MAX_FRAME_RATE					30
#define FRAME_RATE_ONCE					(MAX_FRAME_RATE+1)

typedef enum {
	RADAR_MODE_STANDBY,
	RADAR_MODE_FCW,
	RADAR_MODE_RCW,
	RADAR_MODE_BSD_LCA,
	RADAR_MODE_RCTA,
	RADAR_MODE_DOW,
	RADAR_MODE_INVALID
} RADAR_MODE_E;

#include "track_data.h"
#include "target.h"
#include "spt.h"

#define CORE_DEBUG_ENABLED				1
#if CORE_DEBUG_ENABLED
#define CORE_DEBUG(...)					do { if(MEAS_FLAGS_WR & MEAS_FLAG_CORE_DEBUG) PRINTF(__VA_ARGS__);} while(0)
#else
#define CORE_DEBUG(...)					do { } while(0)
#endif

enum {
	TRK_MEAS_ST_INIT=0,
	TRK_MEAS_ST_READY,
	TRK_MEAS_ST_DONE,
	TRK_MEAS_ST_INVALID
};

typedef enum {
	FRAME_ST_READY,
	FRAME_ST_NEAR,
	FRAME_ST_LONG,
	FRAME_ST_TEF810,
	FRAME_ST_INVALID
}FRAME_STATE_E;

#define FRAME_PARS_ID					FOURCC('f','r','a','m')

#define MAX_COUNT_OF_MEASUREMENTS_PER_FRAME		192
typedef struct {
	measurement_t		measurements[MAX_COUNT_OF_MEASUREMENTS_PER_FRAME];
	uint16_t			mcnt;
	uint8_t				state;
	uint8_t				reserved;
}measurement_group_t, *measurement_group_p;

#define TGGS_BUFF_COUNT	2
typedef struct {
	target_group_t 		tggs_buff[TGGS_BUFF_COUNT][FRAME_CTXS_COUNT];
	target_group_p		tggs;
	tracking_ctx_st 	trkctx;
	measurement_group_t mgrp;
	tracking_group_t	trkgrp;
	uint16_t			counter;
	uint16_t			time;
	RADAR_MODE_E		rmode;
	TRK_CTRL_E			trkctrl;
	float				yaw_msg;
	float				comp_veh_spd;
	float				acc_z;
} frame_data_t, *frame_data_p;

void frame_init(void);
uint16_t frame_play(uint8_t, uint8_t, uint8_t, event_proc_p, event_proc_p);
uint8_t frame_measurements_get_by_rng(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb);
uint8_t frame_measurements_get_by_rng_for_calib(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb);
uint8_t frame_measurements_get_by_rng_for_calib_iron(FRAME_CTX_IDX_E idx, float rng, event_proc_p cb);
measurement_p frame_measurement_get(float, float);
uint32_t frame_number(int32_t);
uint16_t get_frame_counter(void);
uint32_t frame_rate(int32_t fr);
void frame_measurements_rf_cbs_reg(event_proc_p, event_proc_p);
void frame_play_cmd(char**,int);
void frame_new(uint32_t fn);
void frame_pause(char**,int);
void frame_resume(void);
void frame_set_tracking_control(TRK_CTRL_E ctrl);
int frame_ctx_seq_get(void);
void frame_rng_aoa_set(float aoa, float blind, float near_rng, float long_rng, int save);
void frame_rng_set(float blind, float near_end, float long_start, float long_end, int save);
int frame_tgg_in_jsons(target_group_p, char*);
int frame_tggs_in_jsons(char*);
void long_meas_done(target_group_p);
void near_meas_done(target_group_p);

RADAR_MODE_E get_frame_radar_mode(void);
void set_frame_radar_mode(RADAR_MODE_E mode);
float frame_get_acoefs(void);
float frame_get_aoa_shift(uint8_t id);
void frame_set_aoa_shift(uint8_t id, float aoa_shift);
float frame_get_hsft(void);
float frame_get_asft_0(void);
float frame_get_hsft_in_angle(void);
void frame_set_hsft(float hsft, int save);
void frame_set_asft(float asft);
float frame_get_rngs_long_start(void);
void frame_set_rngs_long_start(float rngs_long_start, int save);
FRAME_STATE_E get_frame_state();
void frame_aoa_measument_mode(void);

#endif /* FRAME_H_ */
