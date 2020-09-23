/*
 * tracking.h
 *
 *  Created on: 2017/05/21
 *      Author: Benson
 */

#ifndef __TRACKING_H__
#define __TRACKING_H__

#include "parameters.h"

#define TRACKING_PARS_ID								FOURCC('t','r','k','p')
#define tracking_pars_info_get(_ver,_size)				pars_info_get(TRACKING_PARS_ID, _ver,_size)
#define tracking_pars_info_set(_data, _cnt)				pars_info_set(TRACKING_PARS_ID, _data, _cnt)
#define TRACKING_PARS2_ID								FOURCC('t','r','k','2')
#define tracking_pars2_info_get(_ver,_size)				pars_info_get(TRACKING_PARS2_ID, _ver,_size)
#define tracking_pars2_info_set(_data, _cnt)			pars_info_set(TRACKING_PARS2_ID, _data, _cnt)
#define FCWWARN_PARS_ID									FOURCC('f','c','w','w')
#define fcw_warn_info_get(_ver,_size)					pars_info_get(FCWWARN_PARS_ID, _ver,_size)
#define fcw_warn_info_set(_data, _cnt)					pars_info_set(FCWWARN_PARS_ID, _data, _cnt)

#define NCOMING_LANE_WIDTH      2.8
#define COMING_LANE_WIDTH       2.6
#define CAR_MAX_RCS                 128
#define CAR_MIN_RCS                 115
#define SCOOTER_MIN_RCS             100
#define OBJECT_FILTER_RCS           99

enum {
	TRACKING_MODE_FCW 				= 0,
	TRACKING_MODE_RCW				= 1,
	TRACKING_MODE_MAX				= 2,
	TRACKING_MODE_UNKNOWN   		= 255
};

enum {
	AXIS_ROTATION_0 				= 0,
	AXIS_ROTATION_180 				= 1
};

enum {
	DYNAMIC_STATUS_ALL 				= 0,
	DYNAMIC_STATUS_ONCOMING_ONLY	= 1,
	DYNAMIC_STATUS_UNKNOWN			= 255
};

enum {
	X_DYNAMIC_STATUS_ALL 			= 0,
	X_DYNAMIC_STATUS_ONCOMING_WO	= 1,
	X_DYNAMIC_STATUS_UNKNOWN 		= 255
};

enum {
	TEST_MODE_OFF 					= 0,
	TEST_MODE_ON					= 1,
	TEST_MODE_ON_SIMULATION			= 2,
	TEST_MODE_ON_INTEGRATION		= 4,
};

typedef struct {
	// tracking setting data
	uint8_t 		mode;
	uint8_t 		max_cnt;
	uint8_t 		dynamic_status;
	uint8_t			tracking_dbg;	   			// 0: off, 1: on
	float 			oper_speed[2]; 				// unit: m/s
	float 			standing_on_off;			// unit: m/s
	float 			view_width; 				// unit: m
	float			view_range;					// unit: m
	float 			view_angle;					// unit: degree
	float			view_zone[4];				// unit: m, [x-min, x-max, y-min, y-max]
	float			lane_width[2];				// unit: m
	float 			body_width;					// unit: m
	float 			aoa_shift;					// unit: degree
	float 			position_shift[2];			// unit: x:m y:m
	float			steering_ratio;
	uint8_t			grouping_flag;				// 0: off, 1: on
	uint8_t			measurement_limit;			// measurement limit
	uint8_t			warning_message_flag;
	uint8_t			yaw_sensor_message_flag;
	uint8_t			reserved[8];
	float			grouping_gate[8];			// unit: m
	float 			chassis_gate;				// unit: m
	float			angle_IIR[4];
	float			guardrail[4];
	float			tunnel[4];
	float			ditchcover_filter[6];
	int8_t			vangle[12];					// vangle on/off, degree, distance, times, display
	uint8_t			door_close_time;
	uint8_t 		cipv[4];					// score threshold, buffer width(cm), near width(cm), near range(m)
	uint8_t			target_score[4];
	uint8_t			rcs_level[8];
	uint8_t			possible_upper;
	uint8_t			frame_makeup[2];
	uint8_t			measurement_display;
	uint8_t			extend_lane_width_coef[4];
	uint8_t 		init_flag;
} tracking_info_t, *tracking_info_p;

typedef struct {
	pars_header_t	hdr;
	tracking_info_t info;
} tracking_pars_t, *tracking_pars_p;

typedef struct {
    // tracking setting data
    uint8_t         pcipv_enable;
    float			acc_aeb[2];
    float			rcs_gate[5];
    float			mirror[6];
    float			auto_calib[9];          //[0] => enable
                                            //[1] => x min
                                            //[2] => x max
                                            //[3] => y min
                                            //[4] => y max
                                            //[5] => yaw
                                            //[6] => speed
                                            //[7] => |ang|
                                            //[8] => output
    uint8_t         align_completed[2];		// 0:horizontal, 1:vertical
    uint8_t         align_result[2];		// 0:horizontal, 1:vertical
    float			standing_speed[6];
    float			uds_speed_makeup[3];
    uint8_t 		calib_rule[6];
    // 0:mod, 1:counter, 2:score, 3:times, 4:totalsample, 5:oneside_sample
    float			vertical_align[10];
    // 0:enable, 1:x_min, 2:x_max, 3:y_min, 4:y_max, 5:yaw, 6:speed, 7:vangle, 8:accz, 9:|ang|
    int8_t			vert_rule[3];
    // 0:vangle_shift, 1:times, 2:samplenum
    uint8_t			auto_detect_en[2];
    // 0:horizontal, 1:vertical

} tracking_info2_t, *tracking_info2_p;

typedef struct {
    pars_header_t    hdr;
    tracking_info2_t info;
} tracking_pars2_t, *tracking_pars2_p;

typedef struct {
	pars_header_t	hdr;
	uint8_t			info[SIZE_OF_PARS_CTX_DATA];
} tracking_warn_t, *tracking_warn_p;

typedef struct {
	// FCW/RCW warning setting data
	uint8_t 		dynamic_status;
	uint8_t			pre_warning_flag;			// 0: off, 1: on
	uint8_t			warning_flag;				// 0: off, 1: on
	uint8_t 		emg_warning_flag;			// 0: off, 1: on
	float			warning_ttc_v[2];			// unit: m/s
	float			pre_warning_ttc[2]; 		// unit: s
	float			warning_ttc[2];				// unit: s
	float			emg_warning_ttc[2]; 		// unit: s
	float			warning_atv;				// unit: m/s/s
	float			warning_factor;
	float			warning_min;				// unit: m	
	float			warning_delay[3];			// unit: ms/s/s
	float 			straight_path[3];			// uint: m
	float 			inward_path[2]; 			// uint: m
	float 			warning_path[3]; 			// uint: m
	float			speed_factor[2];
	uint8_t			path_score[2];
	uint8_t			warning_score[2];
} fcw_warn_info_t, *fcw_warn_info_p;

typedef struct {
	pars_header_t	hdr;
	fcw_warn_info_t info;
} fcw_warn_t, *fcw_warn_p;

typedef struct {
	uint8_t			lr_rx_gain;
	uint8_t			lr_tx_gain;
    uint16_t        lr_hpf;
	uint8_t			sr_rx_gain;
	uint8_t			sr_tx_gain;
    uint16_t        sr_hpf;
} rf_gain_info_t;

void tracking_init(void);
void tracking_device_id_reset(void);

void set_tracking_mode(char** args, int count);
void set_target_max_cnt(char** args, int count);
void set_target_dynamic_status(char** args, int count);
void set_tracking_debug(char** args, int count);
void set_operating_speed(char** args, int count);
void set_standing_on_off(char** args, int count);
void set_view_width(char** args, int count);
void set_view_range(char** args, int count);
void set_view_angle(char** args, int count);
void set_view_zone(char** args, int count);
void set_lane_width(char** args, int count);
void set_body_width(char** args, int count);
void set_radar_aoa_shift(char** args, int count);
void set_radar_position_shift(char** args, int count);
void set_steering_ratio(char** args, int count);
void set_target_grouping_flag(char** args, int count);
void set_measurement_limit(char** args, int count);
void set_warning_message_flag(char** args, int count);
void set_yaw_sensor_message_flag(char** args, int count);
void set_door_close_time(char** args, int count);
void set_grouping_gate(char** args, int count);
void set_chassis_gate(char** args, int count);
void set_angle_IIR(char** args, int count);
void set_guardrail(char** args, int count);
void set_tunnel(char** args, int count);
void set_ditchcover_filter(char** args, int count);
void set_vangle(char** args, int count);
void set_cipv(char** args, int count);
void set_target_score(char** args, int count);
void set_rcs_level(char** args, int count);
void set_possible_upper_bound(char** args, int count);
void set_frame_makeup(char** args, int count);
void set_measurement_display(char** args, int count);
void set_ex_lane_width_coef(char** args, int count);
void set_init_flag(char** args, int count);
void set_pcipv_enable(char** args, int count);
void set_acc_aeb(char** args, int count);
void set_rcs_gate(char** args, int count);
void set_align_compeleted(char** args, int count);
void set_mirror(char** args, int count);
void set_auto_calib(char** args, int count);
void set_standing_speed(char** args, int count);
void set_uds_speed_makeup(char** args, int count);
void set_calib_rule(char** args, int count);

void set_warning_dynamic_status(char** args, int count);
void set_pre_warning_flag(char** args, int count);
void set_warning_flag(char** args, int count);
void set_emg_warning_flag(char** args, int count);
void set_pre_warning_ttc(char** args, int count);
void set_valignment_alignment(char** args, int count);
void set_valignment_rule(char** args, int count);
void set_auto_detect_enable(char** args, int count);
void set_warning_ttc(char** args, int count);
void set_emg_warning_ttc(char** args, int count);
void set_warning_ttc_v(char** args, int count);
void set_warning_atv(char** args, int count);
void set_warning_factor(char** args, int count);
void set_warning_min(char** args, int count);
void set_warning_delay(char** args, int count);
void set_straight_path(char** args, int count);
void set_inward_path(char** args, int count);
void set_warning_path(char** args, int count);
void set_speed_factor(char** args, int count);
void set_path_score(char** args, int count);
void set_warning_score(char** args, int count);
void set_flyover_v_phase_threshold(int8_t thres);
void set_ditch_cover_v_phase_threshold(int8_t thres);
int8_t get_flyover_v_phase_threshold();
int8_t get_ditch_cover_v_phase_threshold();

uint8_t tracking_detection_mode_get(void);
int tracking_detection_mode_set(uint8_t mode);
float tracking_field_of_view_width_get(void);
int tracking_field_of_view_width_set(float value);
float tracking_field_of_view_range_get(void);
int tracking_field_of_view_range_set(float value);
float tracking_field_of_view_angle_get(void);
int tracking_field_of_view_angle_set(float value);
float tracking_view_zone_value_get(uint8_t index);
int tracking_view_zone_value_set(uint8_t index, float value);
float tracking_aoa_shift_get(void);
int tracking_aoa_shift_set(float value);
float tracking_lateral_shift_get(void);
int tracking_lateral_shift_set(float value);
float tracking_longitudinal_shift_get(void);
int tracking_longitudinal_shift_set(float value);
float tracking_radar_hight_get(void);
int tracking_radar_hight_set(float value);
uint8_t tracking_warning_message_flag_get(void);
uint8_t tracking_yaw_sensor_message_flag_get(void);
int tracking_fcw_warning_flags_get(uint8_t *flags);
int tracking_fcw_warning_flags_set(uint8_t *flags);
int tracking_fcw_warning_speed_level_get(uint8_t level, float *speed);
int tracking_fcw_warning_speed_level_set(uint8_t level, float speed);
int tracking_fcw_warning_speed_ttc_get(uint8_t type, uint8_t level, float *ttc);
int tracking_fcw_warning_speed_ttc_set(uint8_t type, uint8_t level, float ttc);

uint8_t get_hori_alignment_total_num();
uint8_t get_hori_alignment_result(void);
uint8_t get_hori_alignment_completed(void);
uint16_t get_vert_alignment_total_num();
uint8_t get_vert_alignment_result(void);
uint8_t get_vert_alignment_completed(void);
uint8_t get_trk2_auto_hori_detection_en();
uint8_t get_trk2_auto_vert_detection_en();

void set_trk2_uds_speed_makeup(float speed_filter_a, float speed_filter_b, float stationary);
void get_trk2_uds_speed_makeup(float* Pspeed_filter_a, float* Pspeed_filter_b, float* Pstationary);

#endif /* TRACKING_H_ */

