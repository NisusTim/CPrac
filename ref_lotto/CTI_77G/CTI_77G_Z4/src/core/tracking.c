/*
 * tracking.c
 *
 *  Created on: 2017/05/21
 *      Author: Benson
 */
#include "sys_shared.h"
#include "tracking_set.h"
#include "alignment_main.h"
#include "custom_math.h"

tracking_pars_t __attribute__((section(".trackpars"))) tracking_pars;
tracking_pars2_t __attribute__((section(".trackpars2"))) tracking_pars2;
tracking_warn_t __attribute__((section(".trackwarn"))) tracking_warn;

static tracking_pars_p trkpars = &tracking_pars;
static tracking_pars2_p trkpars2 = &tracking_pars2;
static fcw_warn_p fcwwarn = (fcw_warn_t *)&tracking_warn;

// tracking information in JSON
#define JSON_MODE 					"\t\t\"mode\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_MAX_CNT 				"\t\t\"max_cnt\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_DYN_STATUS 			"\t\t\"dynamic_status\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_TRACKING_DBG			"\t\t\"tracking_dbg\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_OPER_SPEED				"\t\t\"oper_speed\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_STANDING_ON_OFF		"\t\t\"standing_on_off\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_VIEW_WIDTH				"\t\t\"view_width\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_VIEW_RANGE				"\t\t\"view_range\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_VIEW_ANGLE				"\t\t\"view_angle\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_VIEW_ZONE				"\t\t\"view_zone\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_LANE_WIDTH				"\t\t\"lane_width\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_BODY_WIDTH				"\t\t\"body_width\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_AOA_SHIFT				"\t\t\"aoa_shift\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_POSITION_SHIFT			"\t\t\"position_shift\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_STEERING_RATIO			"\t\t\"steering_ratio\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_GROUPING_FLAG 			"\t\t\"grouping_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_MEASUREMENT_LIMIT		"\t\t\"measurement_limit\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_WARNING_MSG_FLAG		"\t\t\"warning_msg_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_YAW_SENSOR_MSG_FAG		"\t\t\"yaw_sensor_msg_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_RESERVED				"\t\t\"reserved\":{\"t\":\"u8\",\"o\":%d,\"v\":[0,0,0,0,0,0,0,0]},\n"
#define JSON_GROUPING_GATE			"\t\t\"grouping_gate\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_CHASSIS_GATE			"\t\t\"chassis_gate\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_ANGLE_IIR				"\t\t\"angle_IIR\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_GUARDRAIL				"\t\t\"guardrail\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_TUNNEL					"\t\t\"tunnel\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_DITCHCOVER_FILTER		"\t\t\"ditchcover_filter\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_VANGLE				    "\t\t\"vangle\":{\"t\":\"i8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_DOOR_CLOSE_TIME		"\t\t\"door_close_time\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_CIPV					"\t\t\"cipv\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_TARGET_SCORE			"\t\t\"target_score\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_RCS_LEVEL				"\t\t\"rcs_level\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_POSSIBLE_UPPER			"\t\t\"possible_upper\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_FRAME_MAKEUP			"\t\t\"frame_makeup\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_MEASUREMENT_DISPLAY	"\t\t\"measurement_display\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_EX_LANE_WIDTH_COEF		"\t\t\"extend_lane_width_coef\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_INIT_FLAG				"\t\t\"init_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d}\n"

// tracking information 2 in JSON
#define JSON_PCIPV_ENABLE           "\t\t\"pcipv_enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ACC_AEB				"\t\t\"acc_aeb\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_RCS_GATE				"\t\t\"rcs_gate\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MIRROR					"\t\t\"mirror\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_AUTO_CALIB             "\t\t\"auto_calib\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_ALIGN_COMPLETED   		"\t\t\"auto_calib_completed\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_ALIGN_RES         		"\t\t\"auto_calib_result\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_STANDING_SPEED         "\t\t\"standing_speed\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_UDS_SPEED_MAKEUP       "\t\t\"uds_speed_makeup\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f]},\n"
#define JSON_CALIB_RULE		        "\t\t\"calib_rule\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d]},\n"
#define JSON_VERT_ALIGN		        "\t\t\"vert_align\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_VERT_RULE		        "\t\t\"vert_rule\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d]},\n"
#define JSON_AUTO_DETECT_EN	        "\t\t\"detect_en\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]}\n"

// FCW warning information in JSON
#define JSON_WARN_DYN_STATUS 		"\t\t\"dynamic_status\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_PRE_WARNING_STATUS		"\t\t\"pre_warning_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_WARNING_STATUS			"\t\t\"warning_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_EMG_WARNING_STATUS		"\t\t\"emg_warning_flag\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_WARNING_TTC_V			"\t\t\"warning_ttc_v\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_PRE_WARNING_TTC		"\t\t\"pre_warning_ttc\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_WARNING_TTC			"\t\t\"warning_ttc\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_EMG_WARNING_TTC		"\t\t\"emg_warning_ttc\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_WARNING_ATV			"\t\t\"warning_atv\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_WARNING_FACTOR			"\t\t\"warning_factor\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_WARNING_MIN			"\t\t\"warning_min\":{\"t\":\"f32\",\"o\":%d,\"v\":%.2f},\n"
#define JSON_WARNING_DELAY			"\t\t\"warning_delay\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f]},\n"
#define JSON_STRAIGHT_PATH			"\t\t\"straight_path\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f]},\n"
#define JSON_INWARD_PATH			"\t\t\"inward_path\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_WARNING_PATH			"\t\t\"warning_path\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f]},\n"
#define JSON_SPEED_FACTOR			"\t\t\"speed_factor\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f]},\n"
#define JSON_PATH_SCORE				"\t\t\"path_score\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_WARNING_SCORE			"\t\t\"warning_score\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_FCW_RESERVED			"\t\t\"reserved\":{\"t\":\"u8\",\"o\":%d,\"v\":[0,0,0,0]}\n"

static void tracking_pars_dump(void);
static void tracking_pars2_dump(void);
static void fcw_warn_dump(void);

static void trk2_pars_check_and_limitation();

static const tracking_pars_t default_trkpars = {
	.hdr = {
		.base = (uint32_t)&tracking_pars,
		.version = 0x0300,
		.size = sizeof(tracking_pars_t),
		.id = TRACKING_PARS_ID,
		.chksum = 0,
		.mask = 0
	},

	.info = {
		.mode = TRACKING_MODE_FCW,
		.max_cnt = 16,
		.dynamic_status = DYNAMIC_STATUS_ALL,
		.tracking_dbg = 0,
		.oper_speed = {0.0, 83.334},
		.standing_on_off = 41.667,
		.view_width = 12.0,
		.view_range = 200.0,
		.view_angle = 45.0,
		.view_zone = {-25.0, 25.0, 0.0, 200.0},
		.lane_width = {NCOMING_LANE_WIDTH, COMING_LANE_WIDTH},
		.body_width = 1.9,
		.aoa_shift = 0.0,
		.position_shift = {0.0, 0.0},
		.steering_ratio	= 15.0,
		.grouping_flag = 0,
		.measurement_limit = 150,
		.warning_message_flag = 0,
		.yaw_sensor_message_flag = 2, // For HiRain
		.reserved = {0, 0, 0, 0, 0, 0, 0, 0},
		.grouping_gate = {16.67, 8.33, 2.5, 1.5, 0.8, 10.0, 1.0, 5.0},
		.chassis_gate = 0.13,
		.angle_IIR = {1.0, 0.85, 100.0, 16.67},
		.guardrail = {11.11, 3.0, 20.0, 6.0},
		.tunnel = {42, 6.0, 30.0, 4.0},
		.ditchcover_filter = {5.55, 2.0, 1.8, 30.0, 6.0, 20.0},
		.vangle = {1, 1, 10, 6, 7, 14, 50, 3, -44, 35, 5, 110},
		.door_close_time = 35,
		.cipv = {30, 20, 15, 20},
		.target_score = {20, 30, 20, 30},
		.rcs_level = {1, CAR_MAX_RCS, CAR_MIN_RCS, SCOOTER_MIN_RCS, 0, 2, 15, 100},
		.possible_upper = 17,
		.frame_makeup = {0, 10},
		.measurement_display = 0,
		.extend_lane_width_coef = {5, 10, 50, 110},
		.init_flag = 0
	}
};

static const tracking_pars2_t default_trkpars2 = {
	.hdr = {
		.base = (uint32_t)&tracking_pars2,
		.version = 0x0600,
		.size = sizeof(tracking_pars2_t),
		.id = TRACKING_PARS2_ID,
		.chksum = 0,
		.mask = 0
	},

	.info = {
		.pcipv_enable = 0,
		.acc_aeb = {5.55, 50},
		.rcs_gate = {9.0, 7.0, 6.0, 6.0, 0.0},
		.mirror = {5.55, 5.55, 15.0, 1.6, 1.8, 5.0},
		.auto_calib = {0.0, 0.1, 12.0, 10.0, 50.0, 0.12, 6.9, 0.6, 0},
		.align_completed = {ALIGN_NOT_COMPLETED, ALIGN_NOT_COMPLETED},
		.align_result = {CALIB_PROCESSING, ALIGN_STATUS_PROCESS},
		.standing_speed = {0.0, 0.86, 1.4, 0.0, 0.86, 1.4},
		.uds_speed_makeup = {1.0, 0.0, 0.0},
		.calib_rule = {2, 6, 25, 4, 100, 100},
		.vertical_align = {0, 0.1, 12.0, 20.0, 40.0, 0.1, 11.11, 100, 0.15, 1.0},
		.vert_rule = {-8, 4, VERTICAL_SAMPLE_UPBOUND},
		.auto_detect_en = { 0, 0 },
	}
};

static const fcw_warn_t default_fcwwarn = {
	.hdr = {
		.base = (uint32_t)&tracking_warn,
		.version = 0x0100,
		.size = sizeof(fcw_warn_t),
		.id = FCWWARN_PARS_ID,
		.chksum = 0,
		.mask = 0
	},

	.info = {
		.dynamic_status = X_DYNAMIC_STATUS_ALL,
		.pre_warning_flag = 1,
		.warning_flag = 1,
		.emg_warning_flag = 1,
		.warning_ttc_v = {8.334, 13.89},
		.pre_warning_ttc = {3.0, 3.0},
		.warning_ttc = {2.0, 2.0},
		.emg_warning_ttc = {1.0, 1.0},
		.warning_atv = 3.0,
		.warning_factor = 0.0,
		.warning_min = 2.0,
		.warning_delay = {300, 2.5, 2.6},
		.straight_path = {0.8, 60.0, 15.0},
		.inward_path = {1.5, 15.0},
		.warning_path = {2.2, 2.4, 150.0},
		.speed_factor = {32.0, 4.0},
		.path_score = {8, 16},
		.warning_score = {3, 6}
	}
};

static char* get_activity_state(uint8_t activity)
{
	switch (activity) {
		case 0:
			return "OFF";
		case 1:
			return "ON";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_tracking_mode(uint8_t mode)
{
	switch (mode) {
		case TRACKING_MODE_FCW:
			return "FCW";
		case TRACKING_MODE_RCW:
			return "RCW";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_dynamic_status(uint8_t mode)
{
	switch (mode) {
		case DYNAMIC_STATUS_ALL:
			return "All";
		case DYNAMIC_STATUS_ONCOMING_ONLY:
			return "Oncoming only";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static char* get_warning_dyn_status(uint8_t mode)
{
	switch (mode) {
		case X_DYNAMIC_STATUS_ALL:
			return "All";
		case X_DYNAMIC_STATUS_ONCOMING_WO:
			return "W/O oncoming";
		default:
			return "Unknown";
	}

	return "Unknown";
}

static void tracking_pars_dump(void)
{	
	float v0, v1;

	PRINTF("Tracking setting:\n");
	PRINTF("- tracking mode(tmode): %s (0:FCW, 1:BSD, 2:RCW, 3:PDS, 4:ODS)\n", get_tracking_mode(trkpars->info.mode));
	PRINTF("- target maximum count(tcnt): %d\n", trkpars->info.max_cnt);
	PRINTF("- dynamic status(dynst): %s\n", get_dynamic_status(trkpars->info.dynamic_status));	
	PRINTF("- tracking debug(debug): %d\n", trkpars->info.tracking_dbg);
	v0 = trkpars->info.oper_speed[0] * MS_TO_KPH;
	v1 = trkpars->info.oper_speed[1] * MS_TO_KPH;
	PRINTF("- operating speed(opspd): %.2f ~ %.2f km/h\n", v0, v1);
	v0 = trkpars->info.standing_on_off * MS_TO_KPH;
	PRINTF("- standing ON/OFF(stdspd): %.2f km/h\n", v0);
	PRINTF("- view width(vwdh): %.2f m\n", trkpars->info.view_width);
	PRINTF("- view range(vrng): %.2f m\n", trkpars->info.view_range);
	PRINTF("- view angle(vang): %.2f degree\n", trkpars->info.view_angle);
	PRINTF("- view zone(vzone): X(%.2f ~ %.2f) Y(%.2f ~ %.2f) m\n", trkpars->info.view_zone[0], trkpars->info.view_zone[1],
		trkpars->info.view_zone[2], trkpars->info.view_zone[3]);
	PRINTF("- lane width(lane): [%.2f %.2f] m\n", trkpars->info.lane_width[0], trkpars->info.lane_width[1]);
	PRINTF("- body width(bwdh): %.2f m\n", trkpars->info.body_width);
	PRINTF("- aoa shift(aoa): %.2f degree\n", trkpars->info.aoa_shift);
	PRINTF("- position shift(pshift): [%.2f %.2f] m [lateral, longitudinal]\n", trkpars->info.position_shift[0], trkpars->info.position_shift[1]);
	PRINTF("- steering ratio(strgr): %.2f\n", trkpars->info.steering_ratio);
	PRINTF("- grouping flag(tgrp): %s\n", get_activity_state(trkpars->info.grouping_flag));
	PRINTF("- measurement limit(mlimit): %d\n", trkpars->info.measurement_limit);
	PRINTF("- warning message flag(wmsg): %d\n", trkpars->info.warning_message_flag);
	PRINTF("- yaw sensor message(ymsg): %d\n", trkpars->info.yaw_sensor_message_flag);
	PRINTF("- grouping gate(ggate): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] m\n", trkpars->info.grouping_gate[0], trkpars->info.grouping_gate[1],
		trkpars->info.grouping_gate[2], trkpars->info.grouping_gate[3], trkpars->info.grouping_gate[4], trkpars->info.grouping_gate[5],
		trkpars->info.grouping_gate[6], trkpars->info.grouping_gate[7]);
	PRINTF("- chassis gate(cgate): %.2f m\n", trkpars->info.chassis_gate);
	PRINTF("- angle IIR (aiir): [%.2f %.2f %.2f %.2f]\n", trkpars->info.angle_IIR[0], trkpars->info.angle_IIR[1],
		trkpars->info.angle_IIR[2], trkpars->info.angle_IIR[3]);
	PRINTF("- guardrail (gdl): [%.2f %.2f %.2f %.2f] [speed, gx, gy, yaw]\n", trkpars->info.guardrail[0], trkpars->info.guardrail[1],
		trkpars->info.guardrail[2], trkpars->info.guardrail[3]);
	PRINTF("- tunnel detection(tunnel): [%.2f %.2f %.2f %.2f] [speed, x, angle, average]\n", trkpars->info.tunnel[0], trkpars->info.tunnel[1],
		trkpars->info.tunnel[2], trkpars->info.tunnel[3]);
	PRINTF("- ditchcover filter(dfilter): [%.2f %.2f %.2f %.2f %.2f %.2f] [speed, ttc, x, y, yaw, frame]\n", trkpars->info.ditchcover_filter[0], trkpars->info.ditchcover_filter[1],
		trkpars->info.ditchcover_filter[2], trkpars->info.ditchcover_filter[3], trkpars->info.ditchcover_filter[4], trkpars->info.ditchcover_filter[5]);
	PRINTF("- vertical angle filter(vangle): [%d %d %d %d %d %d %d %d %d %d %d %d] [enable, display, IIR, width, yaw, degree, dist, times, degree, dist, times, mag]\n",
		trkpars->info.vangle[0], trkpars->info.vangle[1], trkpars->info.vangle[2], trkpars->info.vangle[3], trkpars->info.vangle[4], trkpars->info.vangle[5],
		trkpars->info.vangle[6], trkpars->info.vangle[7], trkpars->info.vangle[8], trkpars->info.vangle[9], trkpars->info.vangle[10], trkpars->info.vangle[11]);
	PRINTF("- cipv setting(cipv): [%d %d %d %d] [standing generate frame, standing disappear frame, dynamic generate frame, dynamic disappear frame]\n",
		trkpars->info.cipv[0], trkpars->info.cipv[1], trkpars->info.cipv[2], trkpars->info.cipv[3]);
	PRINTF("- target score(tscore): [%d %d %d %d] [standing min score, standing max score, dynamic min score, dynamic max score]\n",
		trkpars->info.target_score[0], trkpars->info.target_score[1], trkpars->info.target_score[2], trkpars->info.target_score[3]);
	PRINTF("- rcs level(rcs): [%d %d %d %d %d %d %d %d] [rcs enable, truck min rcs, car min rcs, scooter min rcs, rcs filter, x, y, frame]\n",
		trkpars->info.rcs_level[0], trkpars->info.rcs_level[1], trkpars->info.rcs_level[2], trkpars->info.rcs_level[3],
		trkpars->info.rcs_level[4], trkpars->info.rcs_level[5], trkpars->info.rcs_level[6], trkpars->info.rcs_level[7]);
	PRINTF("- possible upper bound(pub): %d\n", trkpars->info.possible_upper);
	PRINTF("- frame make up(fmakeup): %s %d\n", get_activity_state(trkpars->info.frame_makeup[0]), trkpars->info.frame_makeup[1]);
	PRINTF("- door close time(door): %d frames\n", trkpars->info.door_close_time);
	PRINTF("- measurement display(mplay): %s\n", get_activity_state(trkpars->info.measurement_display));
	PRINTF("- extend lane width coef(exlwc): %d %d %d %d\n", trkpars->info.extend_lane_width_coef[0], trkpars->info.extend_lane_width_coef[1],
			trkpars->info.extend_lane_width_coef[2], trkpars->info.extend_lane_width_coef[3]);
	PRINTF("- init flag(init): %d\n", trkpars->info.init_flag);
}

static int tracking_info_in_jsons(char* data)
{
	int cnt = 0;
	
	if (data) {
		cnt = sprintf(data,"{\n");
		cnt += sprintf(data + cnt, JSON_PARS_HDR_ID, (char)(TRACKING_PARS_ID >> 24), (char)(TRACKING_PARS_ID >> 16), (char)(TRACKING_PARS_ID >> 8), (char)(TRACKING_PARS_ID));
		cnt += sprintf(data + cnt, JSON_PARS_HDR_VERSION, default_trkpars.hdr.version);
		cnt += sprintf(data + cnt, JSON_PARS_HDR_SIZE, default_trkpars.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(data + cnt, "\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_MODE, offsetof(tracking_info_t, mode), trkpars->info.mode);
		cnt += sprintf(data + cnt, JSON_MAX_CNT, offsetof(tracking_info_t, max_cnt), trkpars->info.max_cnt);
		cnt += sprintf(data + cnt, JSON_DYN_STATUS, offsetof(tracking_info_t, dynamic_status), trkpars->info.dynamic_status);
		cnt += sprintf(data + cnt, JSON_TRACKING_DBG, offsetof(tracking_info_t, tracking_dbg), trkpars->info.tracking_dbg);
		cnt += sprintf(data + cnt, JSON_OPER_SPEED, offsetof(tracking_info_t, oper_speed), trkpars->info.oper_speed[0], trkpars->info.oper_speed[1]);
		cnt += sprintf(data + cnt, JSON_STANDING_ON_OFF, offsetof(tracking_info_t, standing_on_off), trkpars->info.standing_on_off);
		cnt += sprintf(data + cnt, JSON_VIEW_WIDTH, offsetof(tracking_info_t, view_width), trkpars->info.view_width);
		cnt += sprintf(data + cnt, JSON_VIEW_RANGE, offsetof(tracking_info_t, view_range), trkpars->info.view_range);
		cnt += sprintf(data + cnt, JSON_VIEW_ANGLE, offsetof(tracking_info_t, view_angle), trkpars->info.view_angle);
		cnt += sprintf(data + cnt, JSON_VIEW_ZONE, offsetof(tracking_info_t, view_zone), trkpars->info.view_zone[0], trkpars->info.view_zone[1], trkpars->info.view_zone[2], trkpars->info.view_zone[3]);
		cnt += sprintf(data + cnt, JSON_LANE_WIDTH, offsetof(tracking_info_t, lane_width), trkpars->info.lane_width[0], trkpars->info.lane_width[1]);
		cnt += sprintf(data + cnt, JSON_BODY_WIDTH, offsetof(tracking_info_t, body_width), trkpars->info.body_width);
		cnt += sprintf(data + cnt, JSON_AOA_SHIFT, offsetof(tracking_info_t, aoa_shift), trkpars->info.aoa_shift);
		cnt += sprintf(data + cnt, JSON_POSITION_SHIFT, offsetof(tracking_info_t, position_shift), trkpars->info.position_shift[0], trkpars->info.position_shift[1]);
		cnt += sprintf(data + cnt, JSON_STEERING_RATIO, offsetof(tracking_info_t, steering_ratio), trkpars->info.steering_ratio);
		cnt += sprintf(data + cnt, JSON_GROUPING_FLAG, offsetof(tracking_info_t, grouping_flag), trkpars->info.grouping_flag);
		cnt += sprintf(data + cnt, JSON_MEASUREMENT_LIMIT, offsetof(tracking_info_t, measurement_limit), trkpars->info.measurement_limit);
		cnt += sprintf(data + cnt, JSON_WARNING_MSG_FLAG, offsetof(tracking_info_t, warning_message_flag), trkpars->info.warning_message_flag);
		cnt += sprintf(data + cnt, JSON_YAW_SENSOR_MSG_FAG, offsetof(tracking_info_t, yaw_sensor_message_flag), trkpars->info.yaw_sensor_message_flag);
		cnt += sprintf(data + cnt, JSON_RESERVED, offsetof(tracking_info_t, reserved));
		cnt += sprintf(data + cnt, JSON_GROUPING_GATE, offsetof(tracking_info_t, grouping_gate), trkpars->info.grouping_gate[0], trkpars->info.grouping_gate[1], trkpars->info.grouping_gate[2], trkpars->info.grouping_gate[3],
				trkpars->info.grouping_gate[4], trkpars->info.grouping_gate[5], trkpars->info.grouping_gate[6], trkpars->info.grouping_gate[7]);
		cnt += sprintf(data + cnt, JSON_CHASSIS_GATE, offsetof(tracking_info_t, chassis_gate), trkpars->info.chassis_gate);
		cnt += sprintf(data + cnt, JSON_ANGLE_IIR, offsetof(tracking_info_t, angle_IIR), trkpars->info.angle_IIR[0], trkpars->info.angle_IIR[1], trkpars->info.angle_IIR[2], trkpars->info.angle_IIR[3]);
		cnt += sprintf(data + cnt, JSON_GUARDRAIL, offsetof(tracking_info_t, guardrail), trkpars->info.guardrail[0], trkpars->info.guardrail[1], trkpars->info.guardrail[2], trkpars->info.guardrail[3]);
		cnt += sprintf(data + cnt, JSON_TUNNEL, offsetof(tracking_info_t, tunnel), trkpars->info.tunnel[0], trkpars->info.tunnel[1], trkpars->info.tunnel[2], trkpars->info.tunnel[3]);
		cnt += sprintf(data + cnt, JSON_DITCHCOVER_FILTER, offsetof(tracking_info_t, ditchcover_filter), trkpars->info.ditchcover_filter[0], trkpars->info.ditchcover_filter[1], trkpars->info.ditchcover_filter[2],
				trkpars->info.ditchcover_filter[3], trkpars->info.ditchcover_filter[4], trkpars->info.ditchcover_filter[5]);
		cnt += sprintf(data + cnt, JSON_VANGLE, offsetof(tracking_info_t, vangle), trkpars->info.vangle[0], trkpars->info.vangle[1], trkpars->info.vangle[2], trkpars->info.vangle[3], trkpars->info.vangle[4],
				trkpars->info.vangle[5], trkpars->info.vangle[6], trkpars->info.vangle[7], trkpars->info.vangle[8], trkpars->info.vangle[9], trkpars->info.vangle[10], trkpars->info.vangle[11]);
		cnt += sprintf(data + cnt, JSON_DOOR_CLOSE_TIME, offsetof(tracking_info_t, door_close_time), trkpars->info.door_close_time);
		cnt += sprintf(data + cnt, JSON_CIPV, offsetof(tracking_info_t, cipv), trkpars->info.cipv[0], trkpars->info.cipv[1], trkpars->info.cipv[2], trkpars->info.cipv[3]);
		cnt += sprintf(data + cnt, JSON_TARGET_SCORE, offsetof(tracking_info_t, target_score), trkpars->info.target_score[0], trkpars->info.target_score[1], trkpars->info.target_score[2], trkpars->info.target_score[3]);
		cnt += sprintf(data + cnt, JSON_RCS_LEVEL, offsetof(tracking_info_t, rcs_level), trkpars->info.rcs_level[0], trkpars->info.rcs_level[1], trkpars->info.rcs_level[2], trkpars->info.rcs_level[3],
				trkpars->info.rcs_level[4], trkpars->info.rcs_level[5], trkpars->info.rcs_level[6], trkpars->info.rcs_level[7]);
		cnt += sprintf(data + cnt, JSON_POSSIBLE_UPPER, offsetof(tracking_info_t, possible_upper), trkpars->info.possible_upper);
		cnt += sprintf(data + cnt, JSON_FRAME_MAKEUP, offsetof(tracking_info_t, frame_makeup), trkpars->info.frame_makeup[0], trkpars->info.frame_makeup[1]);
		cnt += sprintf(data + cnt, JSON_MEASUREMENT_DISPLAY, offsetof(tracking_info_t, measurement_display), trkpars->info.measurement_display);
		cnt += sprintf(data + cnt, JSON_EX_LANE_WIDTH_COEF, offsetof(tracking_info_t, extend_lane_width_coef), trkpars->info.extend_lane_width_coef[0], trkpars->info.extend_lane_width_coef[1], trkpars->info.extend_lane_width_coef[2], trkpars->info.extend_lane_width_coef[3]);
		cnt += sprintf(data + cnt, JSON_INIT_FLAG, offsetof(tracking_info_t, init_flag), trkpars->info.init_flag);
		cnt += sprintf(data + cnt, "\t}\n}\n");
	}

	return cnt;
}

static void tracking_pars2_dump(void)
{
	PRINTF("Tracking setting 2:\n");
	PRINTF("- potential cipv enable(pcipv): %d\n", trkpars2->info.pcipv_enable);
	PRINTF("- acc aeb setting (accaeb): [%.2f %.2f] [speed, range]\n", trkpars2->info.acc_aeb[0], trkpars2->info.acc_aeb[1]);
	PRINTF("- rcs gate setting (rcsgate): [%.2f %.2f %.2f %.2f %.2f] [truck, car, scooter, standing, x gate in standing]\n", trkpars2->info.rcs_gate[0], trkpars2->info.rcs_gate[1], trkpars2->info.rcs_gate[2], trkpars2->info.rcs_gate[3], trkpars2->info.rcs_gate[4]);
	PRINTF("- mirror setting (mirror): [%.2f %.2f %.2f %.2f %.2f %.2f] [my speed, front car speed, y, x, dist multiple, short dist]\n", trkpars2->info.mirror[0], trkpars2->info.mirror[1], trkpars2->info.mirror[2], trkpars2->info.mirror[3], trkpars2->info.mirror[4], trkpars2->info.mirror[5]);
    PRINTF("- auto calib (calib): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, |ang|, output]\n", trkpars2->info.auto_calib[0], trkpars2->info.auto_calib[1], trkpars2->info.auto_calib[2], trkpars2->info.auto_calib[3], trkpars2->info.auto_calib[4], trkpars2->info.auto_calib[5],
            trkpars2->info.auto_calib[6], trkpars2->info.auto_calib[7], trkpars2->info.auto_calib[8]);
    PRINTF("- align completed (agncom): [%X %X]\n", trkpars2->info.align_completed[0], trkpars2->info.align_completed[1]);
    PRINTF("- align result: [%X %X]\n", trkpars2->info.align_result[0], trkpars2->info.align_result[1]);
    PRINTF("- standing speed (sspeed): [%.2f %.2f %.2f %.2f %.2f %.2f] [low speed, 5 degree speed, 60 degree speed, high speed, 5 degree speed, 60 degree speed]\n", trkpars2->info.standing_speed[0], trkpars2->info.standing_speed[1], trkpars2->info.standing_speed[2], trkpars2->info.standing_speed[3], trkpars2->info.standing_speed[4], trkpars2->info.standing_speed[5]);
    PRINTF("- uds speed makeup (uspeed): [%.2f %.2f %.2f] [slope a, intercept b, speed makeup]\n", trkpars2->info.uds_speed_makeup[0], trkpars2->info.uds_speed_makeup[1], trkpars2->info.uds_speed_makeup[2]);
    PRINTF("- calib rule (crule): [%d %d %d %d %d %d] [mod, counter, score, times, totalsample(min:10,max:100), oneside_sample]\n", trkpars2->info.calib_rule[0], trkpars2->info.calib_rule[1], trkpars2->info.calib_rule[2], trkpars2->info.calib_rule[3], trkpars2->info.calib_rule[4], trkpars2->info.calib_rule[5]);
    PRINTF("- vertical align(valign): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, vang, accz, ang]\n", trkpars2->info.vertical_align[0], trkpars2->info.vertical_align[1], trkpars2->info.vertical_align[2], trkpars2->info.vertical_align[3], trkpars2->info.vertical_align[4], trkpars2->info.vertical_align[5], trkpars2->info.vertical_align[6],
    		trkpars2->info.vertical_align[7], trkpars2->info.vertical_align[8], trkpars2->info.vertical_align[9]);
    PRINTF("- vertical rule(vrule): [%d %d %d] [vasft, times, samplenum]\n", trkpars2->info.vert_rule[0], trkpars2->info.vert_rule[1], trkpars2->info.vert_rule[2] * VERTICAL_SAMPLE_SCALE);
    PRINTF("- auto-detect enable(aten): [%d %d] [horizontal, vertical]\n", trkpars2->info.auto_detect_en[0], trkpars2->info.auto_detect_en[1]);
}

static int tracking_info2_in_jsons(char* data)
{
	int cnt = 0;

	if (data) {
		cnt = sprintf(data,"{\n");
		cnt += sprintf(data + cnt, JSON_PARS_HDR_ID, (char)(TRACKING_PARS2_ID >> 24), (char)(TRACKING_PARS2_ID >> 16), (char)(TRACKING_PARS2_ID >> 8), (char)(TRACKING_PARS2_ID));
		cnt += sprintf(data + cnt, JSON_PARS_HDR_VERSION, default_trkpars2.hdr.version);
		cnt += sprintf(data + cnt, JSON_PARS_HDR_SIZE, default_trkpars2.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(data + cnt, "\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_PCIPV_ENABLE, offsetof(tracking_info2_t, pcipv_enable), trkpars2->info.pcipv_enable);
		cnt += sprintf(data + cnt, JSON_ACC_AEB, offsetof(tracking_info2_t, acc_aeb), trkpars2->info.acc_aeb[0], trkpars2->info.acc_aeb[1]);
		cnt += sprintf(data + cnt, JSON_RCS_GATE, offsetof(tracking_info2_t, rcs_gate), trkpars2->info.rcs_gate[0], trkpars2->info.rcs_gate[1], trkpars2->info.rcs_gate[2], trkpars2->info.rcs_gate[3], trkpars2->info.rcs_gate[4]);
		cnt += sprintf(data + cnt, JSON_MIRROR, offsetof(tracking_info2_t, mirror), trkpars2->info.mirror[0], trkpars2->info.mirror[1], trkpars2->info.mirror[2], trkpars2->info.mirror[3], trkpars2->info.mirror[4], trkpars2->info.mirror[5]);
        cnt += sprintf(data + cnt, JSON_AUTO_CALIB, offsetof(tracking_info2_t, auto_calib), trkpars2->info.auto_calib[0], trkpars2->info.auto_calib[1], trkpars2->info.auto_calib[2], trkpars2->info.auto_calib[3], trkpars2->info.auto_calib[4], trkpars2->info.auto_calib[5], trkpars2->info.auto_calib[6], trkpars2->info.auto_calib[7],
        		trkpars2->info.auto_calib[8]);
        cnt += sprintf(data + cnt, JSON_ALIGN_COMPLETED, offsetof(tracking_info2_t, align_completed), trkpars2->info.align_completed[0], trkpars2->info.align_completed[1]);
        cnt += sprintf(data + cnt, JSON_ALIGN_RES, offsetof(tracking_info2_t, align_result), trkpars2->info.align_result[0], trkpars2->info.align_result[1]);
        cnt += sprintf(data + cnt, JSON_STANDING_SPEED, offsetof(tracking_info2_t, standing_speed), trkpars2->info.standing_speed[0], trkpars2->info.standing_speed[1], trkpars2->info.standing_speed[2], trkpars2->info.standing_speed[3], trkpars2->info.standing_speed[4], trkpars2->info.standing_speed[5]);
        cnt += sprintf(data + cnt, JSON_UDS_SPEED_MAKEUP, offsetof(tracking_info2_t, uds_speed_makeup), trkpars2->info.uds_speed_makeup[0], trkpars2->info.uds_speed_makeup[1], trkpars2->info.uds_speed_makeup[2]);
        cnt += sprintf(data + cnt, JSON_CALIB_RULE, offsetof(tracking_info2_t, calib_rule), trkpars2->info.calib_rule[0], trkpars2->info.calib_rule[1], trkpars2->info.calib_rule[2], trkpars2->info.calib_rule[3], trkpars2->info.calib_rule[4], trkpars2->info.calib_rule[5]);
        cnt += sprintf(data + cnt, JSON_VERT_ALIGN, offsetof(tracking_info2_t, vertical_align), trkpars2->info.vertical_align[0], trkpars2->info.vertical_align[1], trkpars2->info.vertical_align[2], trkpars2->info.vertical_align[3], trkpars2->info.vertical_align[4], trkpars2->info.vertical_align[5], trkpars2->info.vertical_align[6], trkpars2->info.vertical_align[7],
        		trkpars2->info.vertical_align[8], trkpars2->info.vertical_align[9]);
        cnt += sprintf(data + cnt, JSON_VERT_RULE, offsetof(tracking_info2_t, vert_rule), trkpars2->info.vert_rule[0], trkpars2->info.vert_rule[1], trkpars2->info.vert_rule[2]);
        cnt += sprintf(data + cnt, JSON_AUTO_DETECT_EN, offsetof(tracking_info2_t, auto_detect_en), trkpars2->info.auto_detect_en[0], trkpars2->info.auto_detect_en[1]);
        cnt += sprintf(data + cnt, "\t}\n}\n");
	}

	return cnt;
}

static void fcw_warn_dump(void)
{	
	float v0, v1;

	PRINTF("FCW/RCW warning setting:\n");
	PRINTF("- warning dynamic status(xdynst): %s (0:All, 1:W/O oncoming)\n", get_warning_dyn_status(fcwwarn->info.dynamic_status));
	PRINTF("- pre_warning flag(pwarn): %s\n", get_activity_state(fcwwarn->info.pre_warning_flag));
	PRINTF("- warning flag(warn): %s\n", get_activity_state(fcwwarn->info.warning_flag));
	PRINTF("- emergency warning flag(ewarn): %s\n", get_activity_state(fcwwarn->info.emg_warning_flag));
	v0 = fcwwarn->info.warning_ttc_v[0] * MS_TO_KPH;
	v1 = fcwwarn->info.warning_ttc_v[1] * MS_TO_KPH;
	PRINTF("- warning TTC_V(xttcv): [%.2f %.2f] km/h\n", v0, v1);
	PRINTF("- pre-warning TTC(xpttc): [%.2f %.2f] s\n", fcwwarn->info.pre_warning_ttc[0], fcwwarn->info.pre_warning_ttc[1]);
	PRINTF("- warning TTC(xttc): [%.2f %.2f] s\n", fcwwarn->info.warning_ttc[0] , fcwwarn->info.warning_ttc[1]);
	PRINTF("- emergency warning TTC(xettc): [%.2f %.2f] s\n", fcwwarn->info.emg_warning_ttc[0] , fcwwarn->info.emg_warning_ttc[1]);
	PRINTF("- warning distance Atv(xatv): %.2f m/s/s\n", fcwwarn->info.warning_atv);
	PRINTF("- warning distance scaling factor(xsfc): %.2f\n", fcwwarn->info.warning_factor);
	PRINTF("- warning distance minimum(xmin): %.2f m\n", fcwwarn->info.warning_min);	
	PRINTF("- warning delay time(xdelay): [%.2fms %.2fs %.2fs]\n", fcwwarn->info.warning_delay[0], fcwwarn->info.warning_delay[1], fcwwarn->info.warning_delay[2]);
	PRINTF("- straight path(spath): [%.2f %.2f %.2f] m\n", fcwwarn->info.straight_path[0], fcwwarn->info.straight_path[1], fcwwarn->info.straight_path[2]);
	PRINTF("- inward path(ipath): [%.2f %.2f] m\n", fcwwarn->info.inward_path[0], fcwwarn->info.inward_path[1]);
	PRINTF("- warning path(wpath): [%.2f %.2f %.2f] m\n", fcwwarn->info.warning_path[0], fcwwarn->info.warning_path[1], fcwwarn->info.warning_path[2]);
	PRINTF("- speed factor(spdfc): [%.2f %.2f]\n", fcwwarn->info.speed_factor[0], fcwwarn->info.speed_factor[1]);
	PRINTF("- path score(pscore): [%d %d]\n", fcwwarn->info.path_score[0], fcwwarn->info.path_score[1]);
	PRINTF("- warning score(wscore): [%d %d]\n", fcwwarn->info.warning_score[0], fcwwarn->info.warning_score[1]);
}

static int fcw_warn_info_in_jsons(char* data)
{
	int cnt = 0;
	
	if (data) {
		cnt = sprintf(data,"{\n");
		cnt += sprintf(data + cnt, JSON_PARS_HDR_ID, (char)(FCWWARN_PARS_ID >> 24), (char)(FCWWARN_PARS_ID >> 16), (char)(FCWWARN_PARS_ID >> 8), (char)(FCWWARN_PARS_ID));
		cnt += sprintf(data + cnt, JSON_PARS_HDR_VERSION, default_fcwwarn.hdr.version);
		cnt += sprintf(data + cnt, JSON_PARS_HDR_SIZE, default_fcwwarn.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(data + cnt, "\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_WARN_DYN_STATUS, offsetof(fcw_warn_info_t, dynamic_status), fcwwarn->info.dynamic_status);
		cnt += sprintf(data + cnt, JSON_PRE_WARNING_STATUS, offsetof(fcw_warn_info_t, pre_warning_flag), fcwwarn->info.pre_warning_flag);
		cnt += sprintf(data + cnt, JSON_WARNING_STATUS, offsetof(fcw_warn_info_t, warning_flag), fcwwarn->info.warning_flag);
		cnt += sprintf(data + cnt, JSON_EMG_WARNING_STATUS, offsetof(fcw_warn_info_t, emg_warning_flag), fcwwarn->info.emg_warning_flag);
		cnt += sprintf(data + cnt, JSON_WARNING_TTC_V, offsetof(fcw_warn_info_t, warning_ttc_v), fcwwarn->info.warning_ttc_v[0], fcwwarn->info.warning_ttc_v[1]);
		cnt += sprintf(data + cnt, JSON_PRE_WARNING_TTC, offsetof(fcw_warn_info_t, pre_warning_ttc), fcwwarn->info.pre_warning_ttc[0], fcwwarn->info.pre_warning_ttc[1]);
		cnt += sprintf(data + cnt, JSON_WARNING_TTC, offsetof(fcw_warn_info_t, warning_ttc), fcwwarn->info.warning_ttc[0], fcwwarn->info.warning_ttc[1]);
		cnt += sprintf(data + cnt, JSON_EMG_WARNING_TTC, offsetof(fcw_warn_info_t, emg_warning_ttc), fcwwarn->info.emg_warning_ttc[0], fcwwarn->info.emg_warning_ttc[1]);
		cnt += sprintf(data + cnt, JSON_WARNING_ATV, offsetof(fcw_warn_info_t, warning_atv), fcwwarn->info.warning_atv);
		cnt += sprintf(data + cnt, JSON_WARNING_FACTOR, offsetof(fcw_warn_info_t, warning_factor), fcwwarn->info.warning_factor);
		cnt += sprintf(data + cnt, JSON_WARNING_MIN, offsetof(fcw_warn_info_t, warning_min), fcwwarn->info.warning_min);
		cnt += sprintf(data + cnt, JSON_WARNING_DELAY, offsetof(fcw_warn_info_t, warning_delay), fcwwarn->info.warning_delay[0], fcwwarn->info.warning_delay[1], fcwwarn->info.warning_delay[2]);
		cnt += sprintf(data + cnt, JSON_STRAIGHT_PATH, offsetof(fcw_warn_info_t, straight_path), fcwwarn->info.straight_path[0], fcwwarn->info.straight_path[1], fcwwarn->info.straight_path[2]);
		cnt += sprintf(data + cnt, JSON_INWARD_PATH, offsetof(fcw_warn_info_t, inward_path), fcwwarn->info.inward_path[0], fcwwarn->info.inward_path[1]);
		cnt += sprintf(data + cnt, JSON_WARNING_PATH, offsetof(fcw_warn_info_t, warning_path), fcwwarn->info.warning_path[0], fcwwarn->info.warning_path[1], fcwwarn->info.warning_path[2]);
		cnt += sprintf(data + cnt, JSON_SPEED_FACTOR, offsetof(fcw_warn_info_t, speed_factor), fcwwarn->info.speed_factor[0], fcwwarn->info.speed_factor[1]);
		cnt += sprintf(data + cnt, JSON_PATH_SCORE, offsetof(fcw_warn_info_t, path_score), fcwwarn->info.path_score[0], fcwwarn->info.path_score[1]);
		cnt += sprintf(data + cnt, JSON_WARNING_SCORE, offsetof(fcw_warn_info_t, warning_score), fcwwarn->info.warning_score[0], fcwwarn->info.warning_score[1]);
		cnt += sprintf(data + cnt, "\t}\n}\n");
	}

	return cnt;	
}

static void tracking_parameter_setting(char** args, int count)
{
	if (count > 2) {
		if (!strcmp(args[1], "tmode")) {
			set_tracking_mode(args, count);
		} else if (!strcmp(args[1], "tcnt")) {
			set_target_max_cnt(args, count);
		} else if (!strcmp(args[1], "dynst")) {
			set_target_dynamic_status(args, count);
		} else if (!strcmp(args[1], "debug")) {
			set_tracking_debug(args, count);
		} else if (!strcmp(args[1], "opspd")) {
			set_operating_speed(args, count);
		} else if (!strcmp(args[1], "stdspd")) {
			set_standing_on_off(args, count);
		} else if (!strcmp(args[1], "vwdh")) {
			set_view_width(args, count);
		} else if (!strcmp(args[1], "vrng")) {
			set_view_range(args, count);
		} else if (!strcmp(args[1], "vang")) {
			set_view_angle(args, count);
		} else if (!strcmp(args[1], "vzone")) {
			set_view_zone(args, count);	
		} else if (!strcmp(args[1], "lane")) {
			set_lane_width(args, count);
		} else if (!strcmp(args[1], "bwdh")) {
			set_body_width(args, count);
		} else if (!strcmp(args[1], "aoa")) {
			set_radar_aoa_shift(args, count);
		} else if (!strcmp(args[1], "pshift")) {
			set_radar_position_shift(args, count);
		} else if (!strcmp(args[1], "svwdh")) {
			set_body_width(args, count);
		} else if (!strcmp(args[1], "strgr")) {
			set_steering_ratio(args, count);
		} else if (!strcmp(args[1], "tgrp")) {
			set_target_grouping_flag(args, count);
		} else if (!strcmp(args[1], "mlimit")) {
			set_measurement_limit(args, count);
		} else if (!strcmp(args[1], "door")) {
			set_door_close_time(args, count);
		} else if (!strcmp(args[1], "wmsg")) {
			set_warning_message_flag(args, count);
		} else if (!strcmp(args[1], "ymsg")) {
			set_yaw_sensor_message_flag(args, count);	
		} else if (!strcmp(args[1], "ggate")) {
			set_grouping_gate(args, count);
		} else if (!strcmp(args[1], "cgate")) {
			set_chassis_gate(args, count);
		} else if (!strcmp(args[1], "aiir")) {
			set_angle_IIR(args, count);
		} else if (!strcmp(args[1], "gdl")) {
			set_guardrail(args, count);
		} else if (!strcmp(args[1], "tunnel")) {
			set_tunnel(args, count);
		} else if (!strcmp(args[1], "dfilter")) {
			set_ditchcover_filter(args, count);
		} else if (!strcmp(args[1], "vangle")) {
			set_vangle(args, count);
		} else if (!strcmp(args[1], "cipv")) {
			set_cipv(args, count);
		} else if (!strcmp(args[1], "tscore")) {
			set_target_score(args, count);
		} else if (!strcmp(args[1], "rcs")) {
			set_rcs_level(args, count);
		} else if (!strcmp(args[1], "pub")) {
			set_possible_upper_bound(args, count);
		} else if (!strcmp(args[1], "fmakeup")) {
			set_frame_makeup(args, count);
		} else if (!strcmp(args[1], "mplay")) {
			set_measurement_display(args, count);
		} else if(!strcmp(args[1], "exlwc")){
			set_ex_lane_width_coef(args, count);
		} else if (!strcmp(args[1], "init")) {
			set_init_flag(args, count);
		}
	} else {
		tracking_pars_dump();
	}
}

static void tracking_parameter2_setting(char** args, int count)
{
	if (count > 2) {
		if (!strcmp(args[1], "pcipv")) {
			set_pcipv_enable(args, count);
		} else if (!strcmp(args[1], "accaeb")) {
			set_acc_aeb(args, count);
		} else if (!strcmp(args[1], "rcsgate")) {
			set_rcs_gate(args, count);
		} else if (!strcmp(args[1], "mirror")) {
			set_mirror(args, count);
		} else if (!strcmp(args[1], "calib")) {
			set_auto_calib(args, count);
		} else if(!strcmp(args[1], "agncom")) {
			set_align_compeleted(args, count);
		} else if (!strcmp(args[1], "sspeed")) {
			set_standing_speed(args, count);
		} else if (!strcmp(args[1], "uspeed")) {
			set_uds_speed_makeup(args, count);
		} else if (!strcmp(args[1], "crule")) {
			set_calib_rule(args, count);
		} else if (!strcmp(args[1], "valign")) {
			set_valignment_alignment(args, count);
		} else if (!strcmp(args[1], "vrule")) {
			set_valignment_rule(args, count);
		} else if (!strcmp(args[1], "aten")){
			set_auto_detect_enable(args, count);
		}
	} else {
		tracking_pars2_dump();
	}
}

static void fcw_warning_setting(char** args, int count)
{
	if (count > 2) {
		if (!strcmp(args[1], "xdynst")) {
			set_warning_dynamic_status(args, count);
		} else if (!strcmp(args[1], "pwarn")) {
			set_pre_warning_flag(args, count);
		} else if (!strcmp(args[1], "warn")) {
			set_warning_flag(args, count);
		} else if (!strcmp(args[1], "ewarn")) {
			set_emg_warning_flag(args, count);
		} else if (!strcmp(args[1], "stdspd")) {
			set_standing_on_off(args, count);
		} else if (!strcmp(args[1], "xttcv")) {
			set_warning_ttc_v(args, count);
		} else if (!strcmp(args[1], "xpttc")) {
			set_pre_warning_ttc(args, count);
		} else if (!strcmp(args[1], "xttc")) {
			set_warning_ttc(args, count);
		} else if (!strcmp(args[1], "xettc")) {
			set_emg_warning_ttc(args, count);
		} else if (!strcmp(args[1], "xatv")) {
			set_warning_atv(args, count);
		} else if (!strcmp(args[1], "xsfc")) {
			set_warning_factor(args, count);
		} else if (!strcmp(args[1], "xmin")) {
			set_warning_min(args, count);
		} else if (!strcmp(args[1], "xdelay")) {
			set_warning_delay(args, count);
		} else if (!strcmp(args[1], "spath")) {
			set_straight_path(args, count);
		} else if (!strcmp(args[1], "ipath")) {
			set_inward_path(args, count);
		} else if (!strcmp(args[1], "wpath")) {
			set_warning_path(args, count);
		} else if (!strcmp(args[1], "spdfc")) {
			set_speed_factor(args, count);
		} else if (!strcmp(args[1], "pscore")) {
			set_path_score(args, count);
		} else if (!strcmp(args[1], "wscore")) {
			set_warning_score(args, count);
		} 	
	} else {
		fcw_warn_dump();
	}
}

void tracking_device_id_reset(void)
{
	trkpars->info.init_flag = 0;
	pars_set((pars_ctx_p)trkpars);
	return;
}

void tracking_init(void)
{
	uint16_t pid;
	uint16_t cusid;
	static uint16_t inited = 0;
	if (inited)
		return;

	const product_info_t* prod = product_info_get();

	pid = prod->product;
	cusid = prod->customer;
	memcpy(trkpars, (void*)&default_trkpars, sizeof(default_trkpars));
	memcpy(trkpars2, (void*)&default_trkpars2, sizeof(default_trkpars2));
	switch (pid) {
		case PROD_ID_FCW_DUAL:
			trkpars->info.mode = TRACKING_MODE_RCW;
			break;
		default:
			break;
	}
	pars_get((pars_ctx_p)trkpars, tracking_pars_dump, tracking_info_in_jsons);
	pars_get((pars_ctx_p)trkpars2, tracking_pars2_dump, tracking_info2_in_jsons);

	// trk2 minor difference handle
	if( ( trkpars2->hdr.version & 0xFF ) != ( default_trkpars.hdr.version & 0xFF) ){
		trk2_pars_check_and_limitation();
		pars_set((pars_ctx_p)trkpars2);
	}
	//IPC_SEND_MSG_Z70(MSG_TRACK_PARS, (void*)trkpars, 0);
	//IPC_SEND_MSG_Z70(MSG_TRACK_PARS2, (void*)trkpars2, 0);
	console_command_reg("trkp", tracking_parameter_setting);
	console_command_reg("trk2", tracking_parameter2_setting);
	if ((trkpars->info.mode == TRACKING_MODE_FCW) || (trkpars->info.mode == TRACKING_MODE_RCW)) {
		memcpy(fcwwarn, (void*)&default_fcwwarn, sizeof(default_fcwwarn));
		pars_get((pars_ctx_p)fcwwarn, fcw_warn_dump, fcw_warn_info_in_jsons);
		//IPC_SEND_MSG_Z70(MSG_TRACK_WARN, (void*)fcwwarn, 0);
		console_command_reg("warn", fcw_warning_setting);
	}
	if (trkpars->info.init_flag == 0) {
		switch (cusid) {
//			case CUSTOM_ID_FENIEX:
//				feniex_tracking_pars_set(trkpars, fcwwarn);
//				break;
//			case CUSTOM_ID_HPB:
//				hpb_tracking_pars_set(trkpars, fcwwarn);
//				break;
			default:
				break;
		}
	}
}

void set_tracking_mode(char** args, int count)
{
	if (count == 3) {
		trkpars->info.mode = (uint8_t)atoi(args[2]);
		if (trkpars->info.mode >= TRACKING_MODE_MAX) {
			trkpars->info.mode = TRACKING_MODE_MAX;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("tracking mode: %s (0:FCW, 1:BSD, 2:RCW, 3:PDS, 4:ODS)\n", get_tracking_mode(trkpars->info.mode));
}

static void trk2_pars_calib_rule_check(){
	if (trkpars2->info.calib_rule[1] >= AUTO_CALIB_QUEUE_SIZE) {
		trkpars2->info.calib_rule[1] = AUTO_CALIB_QUEUE_SIZE;
	}
	if (trkpars2->info.calib_rule[3] >= 5) {
		trkpars2->info.calib_rule[3] = 5;
	}
	// total sample num range check and limitation
	if( trkpars2->info.calib_rule[4] < 10 ||  trkpars2->info.calib_rule[4] > 100 ){
		trkpars2->info.calib_rule[4] = default_trkpars2.info.calib_rule[4];
	}

	// one-side sample num check and limitation
	if( trkpars2->info.calib_rule[5] > trkpars2->info.calib_rule[4] ){
		trkpars2->info.calib_rule[5] = default_trkpars2.info.calib_rule[5];
	}
	else if( trkpars2->info.calib_rule[5] < (uint8_t)((trkpars2->info.calib_rule[4] + 1) / 2) ){
		trkpars2->info.calib_rule[5] = (uint8_t)((trkpars2->info.calib_rule[4] + 1) / 2);
	}
}

static void trk2_pars_vertical_related_rule_check(){
	if( trkpars2->info.vertical_align[9] > 2.5 ){
		trkpars2->info.vertical_align[9] = default_trkpars2.info.vertical_align[0];
	}

	if(trkpars2->info.vert_rule[1] < 0 || trkpars2->info.vert_rule[1] > ANGLE_HISTORY_NUM ){
		trkpars2->info.vert_rule[1] = default_trkpars2.info.vert_rule[1];
	}

	if( trkpars2->info.vert_rule[2] < VERTICAL_SAMPLE_LOWBOUND ||
		trkpars2->info.vert_rule[2] > VERTICAL_SAMPLE_UPBOUND){
		trkpars2->info.vert_rule[2] = VERTICAL_SAMPLE_UPBOUND;
	}
}

static void trk2_pars_check_and_limitation(){

	trk2_pars_calib_rule_check();
	trk2_pars_vertical_related_rule_check();
}

void set_target_max_cnt(char** args, int count)
{
	if (count == 3) {
		trkpars->info.max_cnt = (uint8_t)atoi(args[2]);
		if (trkpars->info.max_cnt > TARGET_MAX) {
			trkpars->info.max_cnt = TARGET_MAX;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("maximum count: %d\n", trkpars->info.max_cnt);
}

void set_target_dynamic_status(char** args, int count)
{
	if (count == 3) {
		trkpars->info.dynamic_status = (uint8_t)atoi(args[2]);
		if (trkpars->info.dynamic_status >= DYNAMIC_STATUS_UNKNOWN) {
			trkpars->info.dynamic_status = DYNAMIC_STATUS_ALL;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("dynamic status: %s (0:All, 1:Oncoming only)\n", get_dynamic_status(trkpars->info.dynamic_status));
}

void set_tracking_debug(char** args, int count)
{
	if (count == 3) {
		trkpars->info.tracking_dbg = (uint8_t)atoi(args[2]);
		if (trkpars->info.tracking_dbg > 1) {
			trkpars->info.tracking_dbg = 1;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("tracking debug: %s\n", get_activity_state(trkpars->info.tracking_dbg));
}

void set_operating_speed(char** args, int count)
{
	float v_min, v_max;

	if (count == 4) {
		v_min = (float)atof(args[2]);
		v_max = (float)atof(args[3]);
		if (v_min < 0.0) {
			v_min = 0.0;
		}
		if (v_min > 200.0) {
			v_min = 200.0;
		}
		if (v_max <= v_min) {
			v_max = v_min + 1;
		}
		if (v_max > 300.0) {
			v_max = 300.0;
		}
		trkpars->info.oper_speed[0] = v_min * KPH_TO_MS;
		trkpars->info.oper_speed[1] = v_max * KPH_TO_MS;
		pars_set((pars_ctx_p)trkpars);
	}
	v_min = trkpars->info.oper_speed[0] * MS_TO_KPH;
	v_max = trkpars->info.oper_speed[1] * MS_TO_KPH;
	PRINTF("operating speed: %.2f ~ %.2f km/h\n", v_min, v_max);
}

void set_standing_on_off(char** args, int count)
{
	float v0;

	if (count == 3) {
		v0 = (float)atof(args[2]);
		if (v0 < 0.0) {
			v0 = 0.0;
		}
		trkpars->info.standing_on_off = v0 * KPH_TO_MS;
		pars_set((pars_ctx_p)trkpars);
	}
	v0 = trkpars->info.standing_on_off * KPH_TO_MS;
	PRINTF("standing ON/OFF(stdspd): %.2f km/h\n", v0);
}

void set_view_width(char** args, int count)
{
	if (count == 3) {
		trkpars->info.view_width = (float)atof(args[2]);
		if (trkpars->info.view_width < 0.0) {
			trkpars->info.view_width = 0.0;
		}
		if (trkpars->info.view_width > 100.0) {
			trkpars->info.view_width = 100.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("view width: %.2f m\n", trkpars->info.view_width);
}

void set_view_range(char** args, int count)
{
	if (count == 3) {
		trkpars->info.view_range = (float)atof(args[2]);
		if (trkpars->info.view_range < 0.0) {
			trkpars->info.view_range = 0.0;
		}
		if (trkpars->info.view_range > 500.0) {
			trkpars->info.view_range = 500.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("view range: %.2f m\n", trkpars->info.view_range);
}

void set_view_angle(char** args, int count)
{
	if (count == 3) {
		trkpars->info.view_angle = (float)atof(args[2]);
		if (trkpars->info.view_angle < 0.0) {
			trkpars->info.view_angle = 0.0;
		}
		if (trkpars->info.view_angle > 180.0) {
			trkpars->info.view_angle = 180.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("view angle: %.2f degree\n", trkpars->info.view_angle);
}

void set_view_zone(char** args, int count)
{
	if (count == 6) {
		trkpars->info.view_zone[0] = (float)atof(args[2]);
		trkpars->info.view_zone[1] = (float)atof(args[3]);
		trkpars->info.view_zone[2] = (float)atof(args[4]);
		trkpars->info.view_zone[3] = (float)atof(args[5]);
		if (trkpars->info.view_zone[1] < trkpars->info.view_zone[0]) {
			trkpars->info.view_zone[1] = trkpars->info.view_zone[0];
		}
		if (trkpars->info.view_zone[3] < trkpars->info.view_zone[2]) {
			trkpars->info.view_zone[3] = trkpars->info.view_zone[2];
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("view zone: X(%.2f ~ %.2f) Y(%.2f ~ %.2f) m\n", trkpars->info.view_zone[0], trkpars->info.view_zone[1],
		trkpars->info.view_zone[2], trkpars->info.view_zone[3]);
}

void set_lane_width(char** args, int count)
{
	if (count == 4) {
		trkpars->info.lane_width[0] = (float)atof(args[2]);
		trkpars->info.lane_width[1] = (float)atof(args[3]);
		if (trkpars->info.lane_width[0] < 0.0) {
			trkpars->info.lane_width[0] = 0.0;
		}
		if (trkpars->info.lane_width[0] > 5.0) {
			trkpars->info.lane_width[0] = 5.0;
		}
		if (trkpars->info.lane_width[1] < 0.0) {
			trkpars->info.lane_width[1] = 0.0;
		}
		if (trkpars->info.lane_width[1] > 5.0) {
			trkpars->info.lane_width[1] = 5.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("lane width: [%.2f %.2f] m [Non-coming, Oncoming]\n", trkpars->info.lane_width[0], trkpars->info.lane_width[1]);
}

void set_body_width(char** args, int count)
{
	if (count == 3) {
		trkpars->info.body_width = (float)atof(args[2]);
		if (trkpars->info.body_width < 0.5) {
			trkpars->info.body_width = 0.5;
		}
		if (trkpars->info.body_width > 3.0) {
			trkpars->info.body_width = 3.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("body width: %.2f m\n", trkpars->info.body_width);
}

void set_radar_aoa_shift(char** args, int count)
{
	if (count == 3) {
		trkpars->info.aoa_shift = (float)atof(args[2]);
		if (trkpars->info.aoa_shift < -90.0) {
			trkpars->info.aoa_shift = -90.0;
		}
		if (trkpars->info.aoa_shift > 90.0) {
			trkpars->info.aoa_shift = 90.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("aoa shift: %.2f\n", trkpars->info.aoa_shift);
}

void set_radar_position_shift(char** args, int count)
{
	if (count == 4) {
		trkpars->info.position_shift[0] = (float)atof(args[2]);
		trkpars->info.position_shift[1] = (float)atof(args[3]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("position shift: [%.2f %.2f] m [lateral, longitudinal]\n", trkpars->info.position_shift[0], trkpars->info.position_shift[1]);
}

void set_steering_ratio(char** args, int count)
{
	if (count == 3) {
		trkpars->info.steering_ratio = (float)atof(args[2]);
		if (trkpars->info.steering_ratio < 5.0) {
			trkpars->info.steering_ratio = 5.0;
		}
		if (trkpars->info.steering_ratio > 25.0) {
			trkpars->info.steering_ratio = 25.0;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("steering ratio: %.2f\n", trkpars->info.steering_ratio);
}

void set_target_grouping_flag(char** args, int count)
{
	if (count == 3) {
		trkpars->info.grouping_flag = (uint8_t)atoi(args[2]);
		if (trkpars->info.grouping_flag > 1) {
			trkpars->info.grouping_flag = 1;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("grouping flag: %s\n", get_activity_state(trkpars->info.grouping_flag));
}

void set_measurement_limit(char** args, int count)
{
	if (count == 3) {
		trkpars->info.measurement_limit = (uint8_t)atoi(args[2]);
		if (trkpars->info.measurement_limit >= 255) {
			trkpars->info.measurement_limit = 255;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("measurement limit: %d\n", trkpars->info.measurement_limit);
}

void set_warning_message_flag(char** args, int count)
{
	if (count == 3) {
		trkpars->info.warning_message_flag = (uint8_t)atoi(args[2]);
		if (trkpars->info.warning_message_flag >= 1) {
			trkpars->info.warning_message_flag = 1;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("warning message flag: %d\n", trkpars->info.warning_message_flag);
}

void set_yaw_sensor_message_flag(char** args, int count)
{
	if (count == 3) {
		trkpars->info.yaw_sensor_message_flag = (uint8_t)atoi(args[2]);
		if (trkpars->info.yaw_sensor_message_flag >= 2) {
			trkpars->info.yaw_sensor_message_flag = 2;
		}
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("yaw sensor message flag: %d\n", trkpars->info.yaw_sensor_message_flag);
}

void set_vangle(char** args, int count)
{
	if (count == 14) {
		trkpars->info.vangle[0] = (uint8_t)atof(args[2]);
		trkpars->info.vangle[1] = (uint8_t)atof(args[3]);
		trkpars->info.vangle[2] = (uint8_t)atof(args[4]);
		trkpars->info.vangle[3] = (uint8_t)atof(args[5]);
		trkpars->info.vangle[4] = (uint8_t)atof(args[6]);
		trkpars->info.vangle[5] = (uint8_t)atof(args[7]);
		trkpars->info.vangle[6] = (uint8_t)atof(args[8]);
		trkpars->info.vangle[7] = (uint8_t)atof(args[9]);
		trkpars->info.vangle[8] = (uint8_t)atof(args[10]);
		trkpars->info.vangle[9] = (uint8_t)atof(args[11]);
		trkpars->info.vangle[10] = (uint8_t)atof(args[12]);
		trkpars->info.vangle[11] = (uint8_t)atof(args[13]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("vangle: [%d %d %d %d %d %d %d %d %d %d %d %d] [enable, display, IIR, width, yaw, degree, dist, times, degree, dist, times, mag]\n",
		trkpars->info.vangle[0], trkpars->info.vangle[1], trkpars->info.vangle[2], trkpars->info.vangle[3], trkpars->info.vangle[4], trkpars->info.vangle[5],
		trkpars->info.vangle[6], trkpars->info.vangle[7], trkpars->info.vangle[8], trkpars->info.vangle[9], trkpars->info.vangle[10], trkpars->info.vangle[11]);
}

void set_angle_IIR(char** args, int count)
{
	if (count == 6) {
		trkpars->info.angle_IIR[0] = (float)atof(args[2]);
		trkpars->info.angle_IIR[1] = (float)atof(args[3]);
		trkpars->info.angle_IIR[2] = (float)atof(args[4]);
		trkpars->info.angle_IIR[3] = (float)atof(args[5]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("angle_IIR: [%.2f %.2f %.2f %.2f] \n", trkpars->info.angle_IIR[0], trkpars->info.angle_IIR[1],
		trkpars->info.angle_IIR[2], trkpars->info.angle_IIR[3]);
}

void set_guardrail(char** args, int count)
{
	if (count == 6) {
		trkpars->info.guardrail[0] = (float)atof(args[2]);
		trkpars->info.guardrail[1] = (float)atof(args[3]);
		trkpars->info.guardrail[2] = (float)atof(args[4]);
		trkpars->info.guardrail[3] = (float)atof(args[5]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("guardrail (gdl): [%.2f %.2f %.2f %.2f] [speed, gx, gy, yaw]\n", trkpars->info.guardrail[0], trkpars->info.guardrail[1],
		trkpars->info.guardrail[2], trkpars->info.guardrail[3]);
}

void set_tunnel(char** args, int count)
{
	if (count == 6) {
		trkpars->info.tunnel[0] = (float)atof(args[2]);
		trkpars->info.tunnel[1] = (float)atof(args[3]);
		trkpars->info.tunnel[2] = (float)atof(args[4]);
		trkpars->info.tunnel[3] = (float)atof(args[5]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("tunnel detection(tunnel): [%.2f %.2f %.2f %.2f] [speed, x, angle, average]\n", trkpars->info.tunnel[0], trkpars->info.tunnel[1],
		trkpars->info.tunnel[2], trkpars->info.tunnel[3]);
}

void set_ditchcover_filter(char** args, int count)
{
	if (count == 8) {
		trkpars->info.ditchcover_filter[0] = (float)atof(args[2]);
		trkpars->info.ditchcover_filter[1] = (float)atof(args[3]);
		trkpars->info.ditchcover_filter[2] = (float)atof(args[4]);
		trkpars->info.ditchcover_filter[3] = (float)atof(args[5]);
		trkpars->info.ditchcover_filter[4] = (float)atof(args[6]);
		trkpars->info.ditchcover_filter[5] = (float)atof(args[7]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("ditchcover filter: [%.2f %.2f %.2f %.2f %.2f %.2f] [speed, ttc, x, y, yaw, frame]\n", trkpars->info.ditchcover_filter[0], trkpars->info.ditchcover_filter[1],
		trkpars->info.ditchcover_filter[2], trkpars->info.ditchcover_filter[3], trkpars->info.ditchcover_filter[4], trkpars->info.ditchcover_filter[5]);
}

void set_door_close_time(char** args, int count)
{
	if (count == 3) {
		trkpars->info.door_close_time = (uint8_t)atoi(args[2]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("door close time: %d frames\n", trkpars->info.door_close_time);
}

void set_grouping_gate(char** args, int count)
{
	if (count == 10) {
		trkpars->info.grouping_gate[0] = (float)atof(args[2]);
		trkpars->info.grouping_gate[1] = (float)atof(args[3]);
		trkpars->info.grouping_gate[2] = (float)atof(args[4]);
		trkpars->info.grouping_gate[3] = (float)atof(args[5]);
		trkpars->info.grouping_gate[4] = (float)atof(args[6]);
		trkpars->info.grouping_gate[5] = (float)atof(args[7]);
		trkpars->info.grouping_gate[6] = (float)atof(args[8]);
		trkpars->info.grouping_gate[7] = (float)atof(args[9]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("grouping gate: [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] m\n", trkpars->info.grouping_gate[0], trkpars->info.grouping_gate[1],
		trkpars->info.grouping_gate[2], trkpars->info.grouping_gate[3], trkpars->info.grouping_gate[4], trkpars->info.grouping_gate[5],
		trkpars->info.grouping_gate[6], trkpars->info.grouping_gate[7]);
}

void set_chassis_gate(char** args, int count)
{
	if (count == 3) {
		trkpars->info.chassis_gate = (float)atof(args[2]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("chassis gate: %.2f m\n", trkpars->info.chassis_gate);
}

void set_cipv(char** args, int count)
{
	if (count == 6) {
		trkpars->info.cipv[0] = (uint8_t)atof(args[2]);
		trkpars->info.cipv[1] = (uint8_t)atof(args[3]);
		trkpars->info.cipv[2] = (uint8_t)atof(args[4]);
		trkpars->info.cipv[3] = (uint8_t)atof(args[5]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("cipv: [%d %d %d %d]\n", trkpars->info.cipv[0], trkpars->info.cipv[1], trkpars->info.cipv[2], trkpars->info.cipv[3]);
}

void set_target_score(char** args, int count)
{
	if (count == 6) {
		trkpars->info.target_score[0] = (uint8_t)atof(args[2]);
		trkpars->info.target_score[1] = (uint8_t)atof(args[3]);
		trkpars->info.target_score[2] = (uint8_t)atof(args[4]);
		trkpars->info.target_score[3] = (uint8_t)atof(args[5]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("target score: [%d %d %d %d]\n", trkpars->info.target_score[0], trkpars->info.target_score[1], trkpars->info.target_score[2], trkpars->info.target_score[3]);
}

void set_rcs_level(char** args, int count)
{
	if (count == 10) {
		trkpars->info.rcs_level[0] = (uint8_t)atof(args[2]);
		trkpars->info.rcs_level[1] = (uint8_t)atof(args[3]);
		trkpars->info.rcs_level[2] = (uint8_t)atof(args[4]);
		trkpars->info.rcs_level[3] = (uint8_t)atof(args[5]);
		trkpars->info.rcs_level[4] = (uint8_t)atof(args[6]);
		trkpars->info.rcs_level[5] = (uint8_t)atof(args[7]);
		trkpars->info.rcs_level[6] = (uint8_t)atof(args[8]);
		trkpars->info.rcs_level[7] = (uint8_t)atof(args[9]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("rcs level: [%d %d %d %d %d %d %d %d]\n", trkpars->info.rcs_level[0], trkpars->info.rcs_level[1], trkpars->info.rcs_level[2], trkpars->info.rcs_level[3],
		trkpars->info.rcs_level[4], trkpars->info.rcs_level[5], trkpars->info.rcs_level[6], trkpars->info.rcs_level[7]);
}

void set_possible_upper_bound(char** args, int count)
{
	if (count == 3) {
		trkpars->info.possible_upper = (uint8_t)atoi(args[2]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("possible upper bound: %d\n", trkpars->info.possible_upper);
}

void set_frame_makeup(char** args, int count)
{
	if (count == 4) {
		trkpars->info.frame_makeup[0] = (uint8_t)atoi(args[2]);
		trkpars->info.frame_makeup[1] = (uint8_t)atoi(args[3]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("frame make up(fmakeup): %s %d\n", get_activity_state(trkpars->info.frame_makeup[0]), trkpars->info.frame_makeup[1]);
}

void set_measurement_display(char** args, int count)
{
	if (count == 3) {
		trkpars->info.measurement_display = (uint8_t)atoi(args[2]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("measurement display: %s\n", get_activity_state(trkpars->info.measurement_display));
}

void set_ex_lane_width_coef(char** args, int count)
{
	uint8_t coef_0, coef_1, coef_2, coef_3;
	if (count == 6) {
		coef_0 = (uint8_t)atoi(args[2]);// unit: 10^-1 m
		coef_1 = (uint8_t)atoi(args[3]);// unit: 10^-1 m
		coef_2 = (uint8_t)atoi(args[4]);// unit: m
		coef_3 = (uint8_t)atoi(args[5]);// unit: m
		if((coef_1 > coef_0) && (coef_3 > coef_2) && (coef_2 > 0) && (coef_0 >= 0)){
			trkpars->info.extend_lane_width_coef[0] = coef_0;
			trkpars->info.extend_lane_width_coef[1] = coef_1;
			trkpars->info.extend_lane_width_coef[2] = coef_2;
			trkpars->info.extend_lane_width_coef[3] = coef_3;
			pars_set((pars_ctx_p)trkpars);
		}
	}
	PRINTF("extend lane width coef: [%d, %d, %d, %d]\n", trkpars->info.extend_lane_width_coef[0],
			trkpars->info.extend_lane_width_coef[1], trkpars->info.extend_lane_width_coef[2], trkpars->info.extend_lane_width_coef[3]);
}

void set_init_flag(char** args, int count)
{
	if (count == 3) {
		trkpars->info.init_flag = (uint8_t)atoi(args[2]);
		pars_set((pars_ctx_p)trkpars);
	}
	PRINTF("init flag: %d\n", trkpars->info.init_flag);
}

void set_pcipv_enable(char** args, int count)
{
	if (count == 3) {
		trkpars2->info.pcipv_enable = (uint8_t)atoi(args[2]);
		pars_set((pars_ctx_p)trkpars2);
	}
	PRINTF("pcipv enable: %d\n", trkpars2->info.pcipv_enable);
}

void set_acc_aeb(char** args, int count)
{
	if (count == 4) {
		trkpars2->info.acc_aeb[0] = (float)atof(args[2]);
		trkpars2->info.acc_aeb[1] = (float)atof(args[3]);
		pars_set((pars_ctx_p)trkpars2);
	}
	PRINTF("acc aeb setting: [%.2f %.2f] [speed, range]\n", trkpars2->info.acc_aeb[0], trkpars2->info.acc_aeb[1]);
}

void set_rcs_gate(char** args, int count)
{
	if (count == 7) {
		trkpars2->info.rcs_gate[0] = (float)atof(args[2]);
		trkpars2->info.rcs_gate[1] = (float)atof(args[3]);
		trkpars2->info.rcs_gate[2] = (float)atof(args[4]);
		trkpars2->info.rcs_gate[3] = (float)atof(args[5]);
		trkpars2->info.rcs_gate[4] = (float)atof(args[6]);
		pars_set((pars_ctx_p)trkpars2);
	}
	PRINTF("rcs gate setting: [%.2f %.2f %.2f %.2f %.2f] [truck, car, scooter, standing, x gate in standing]\n", trkpars2->info.rcs_gate[0], trkpars2->info.rcs_gate[1], trkpars2->info.rcs_gate[2], trkpars2->info.rcs_gate[3], trkpars2->info.rcs_gate[4]);
}

void set_mirror(char** args, int count)
{
	if (count == 8) {
		trkpars2->info.mirror[0] = (float)atof(args[2]);
		trkpars2->info.mirror[1] = (float)atof(args[3]);
		trkpars2->info.mirror[2] = (float)atof(args[4]);
		trkpars2->info.mirror[3] = (float)atof(args[5]);
		trkpars2->info.mirror[4] = (float)atof(args[6]);
		trkpars2->info.mirror[5] = (float)atof(args[7]);
		pars_set((pars_ctx_p)trkpars2);
	}
	PRINTF("mirror setting: [%.2f %.2f %.2f %.2f %.2f %.2f] [my speed, front car speed, y, x, dist multiple, short dist]\n", trkpars2->info.mirror[0], trkpars2->info.mirror[1], trkpars2->info.mirror[2], trkpars2->info.mirror[3], trkpars2->info.mirror[4], trkpars2->info.mirror[5]);
}

void set_auto_calib(char** args, int count)
{
    if (count == 11) {
		trkpars2->info.auto_calib[0] = (float)atof(args[2]);
		trkpars2->info.auto_calib[1] = (float)atof(args[3]);
		trkpars2->info.auto_calib[2] = (float)atof(args[4]);
		trkpars2->info.auto_calib[3] = (float)atof(args[5]);
		trkpars2->info.auto_calib[4] = (float)atof(args[6]);
		trkpars2->info.auto_calib[5] = (float)atof(args[7]);
		trkpars2->info.auto_calib[6] = (float)atof(args[8]);
        trkpars2->info.auto_calib[7] = ABS((float)atof(args[9]));
		trkpars2->info.auto_calib[8] = (float)atof(args[10]);
		pars_set((pars_ctx_p)trkpars2);
	}
    PRINTF("auto calib: [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, |ang|, output]\n", trkpars2->info.auto_calib[0], trkpars2->info.auto_calib[1], trkpars2->info.auto_calib[2], trkpars2->info.auto_calib[3], trkpars2->info.auto_calib[4], trkpars2->info.auto_calib[5], trkpars2->info.auto_calib[6],
    		trkpars2->info.auto_calib[7], trkpars2->info.auto_calib[8]);
}

void set_align_compeleted(char** args, int count)
{
    if (count == 4)
    {
        trkpars2->info.align_completed[0] = (uint8_t)atoi(args[2]);
        trkpars2->info.align_completed[1] = (uint8_t)atoi(args[3]);
        pars_set((pars_ctx_p)trkpars2);
    }
    PRINTF("- align completed (agncom): [%X %X]\n", trkpars2->info.align_completed[0], trkpars2->info.align_completed[1]);
}

void set_standing_speed(char** args, int count)
{
    if (count == 8) {
		trkpars2->info.standing_speed[0] = (float)atof(args[2]);
		trkpars2->info.standing_speed[1] = (float)atof(args[3]);
		trkpars2->info.standing_speed[2] = (float)atof(args[4]);
		trkpars2->info.standing_speed[3] = (float)atof(args[5]);
		trkpars2->info.standing_speed[4] = (float)atof(args[6]);
		trkpars2->info.standing_speed[5] = (float)atof(args[7]);
		pars_set((pars_ctx_p)trkpars2);
	}
    PRINTF("standing speed: [%.2f %.2f %.2f %.2f %.2f %.2f] [low speed, 5 degree speed, 60 degree speed, high speed, 5 degree speed, 60 degree speed]\n", trkpars2->info.standing_speed[0], trkpars2->info.standing_speed[1], trkpars2->info.standing_speed[2], trkpars2->info.standing_speed[3], trkpars2->info.standing_speed[4], trkpars2->info.standing_speed[5]);
}

void set_uds_speed_makeup(char** args, int count)
{
    if (count == 5) {
        if((float)atof(args[2]) > 0)
        {
            trkpars2->info.uds_speed_makeup[0] = (float)atof(args[2]);
            trkpars2->info.uds_speed_makeup[1] = (float)atof(args[3]);
            trkpars2->info.uds_speed_makeup[2] = (float)atof(args[4]);
            pars_set((pars_ctx_p)trkpars2);
        }
        else
        {
            PRINTF("uds speed slope a must be greater than 0\n");
        }
	}
    PRINTF("uds speed makeup: [%.2f %.2f %.2f] [slope a, intercept b, speed makeup]\n", trkpars2->info.uds_speed_makeup[0], trkpars2->info.uds_speed_makeup[1], trkpars2->info.uds_speed_makeup[2]);
}

void set_calib_rule(char** args, int count)
{
    if (count == 8) {
		trkpars2->info.calib_rule[0] = (uint8_t)atof(args[2]);
		trkpars2->info.calib_rule[1] = (uint8_t)atof(args[3]);
		trkpars2->info.calib_rule[2] = (uint8_t)atof(args[4]);
		trkpars2->info.calib_rule[3] = (uint8_t)atof(args[5]);
		trkpars2->info.calib_rule[4] = (uint8_t)atof(args[6]);
		trkpars2->info.calib_rule[5] = (uint8_t)atof(args[7]);

		trk2_pars_calib_rule_check();
		pars_set((pars_ctx_p)trkpars2);
	}

    PRINTF("calib rule: [%d %d %d %d %d %d] [mod, counter, score, times, totalsample(min:10,max:100), oneside_sample]\n", trkpars2->info.calib_rule[0], trkpars2->info.calib_rule[1], trkpars2->info.calib_rule[2], trkpars2->info.calib_rule[3], trkpars2->info.calib_rule[4], trkpars2->info.calib_rule[5]);
}

void set_valignment_alignment(char** args, int count)
{
    if (count == 12) {
		trkpars2->info.vertical_align[0] = ABS((float)atof(args[2]));
		trkpars2->info.vertical_align[1] = ABS((float)atof(args[3]));
		trkpars2->info.vertical_align[2] = ABS((float)atof(args[4]));
		trkpars2->info.vertical_align[3] = ABS((float)atof(args[5]));
		trkpars2->info.vertical_align[4] = ABS((float)atof(args[6]));
		trkpars2->info.vertical_align[5] = ABS((float)atof(args[7]));
		trkpars2->info.vertical_align[6] = ABS((float)atof(args[8]));
        trkpars2->info.vertical_align[7] = ABS((float)atof(args[9]));
		trkpars2->info.vertical_align[8] = ABS((float)atof(args[10]));
		trkpars2->info.vertical_align[9] = ABS((float)atof(args[11]));
		pars_set((pars_ctx_p)trkpars2);
	}
    PRINTF("- vertical align(valign): [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f] [enable, x min, x max, y min, y max, yaw, speed, vang, accz, ang]\n", trkpars2->info.vertical_align[0], trkpars2->info.vertical_align[1], trkpars2->info.vertical_align[2], trkpars2->info.vertical_align[3], trkpars2->info.vertical_align[4], trkpars2->info.vertical_align[5], trkpars2->info.vertical_align[6],
    		trkpars2->info.vertical_align[7], trkpars2->info.vertical_align[8], trkpars2->info.vertical_align[9]);
}

void set_valignment_rule(char** args, int count)
{
    if (count == 5) {
		trkpars2->info.vert_rule[0] = (int8_t)atoi(args[2]);
		trkpars2->info.vert_rule[1] = (int8_t)atoi(args[3]);
		trkpars2->info.vert_rule[2] = (int8_t)(atoi(args[4]) / VERTICAL_SAMPLE_SCALE);
		trk2_pars_vertical_related_rule_check();
		pars_set((pars_ctx_p)trkpars2);
	}
    PRINTF("- vertical rule(vrule): [%d %d %d] [vasft, times, samplenum]\n", trkpars2->info.vert_rule[0], trkpars2->info.vert_rule[1], trkpars2->info.vert_rule[2] * VERTICAL_SAMPLE_SCALE);
}

void set_auto_detect_enable(char** args, int count){
    if (count == 4) {
		trkpars2->info.auto_detect_en[0] = (uint8_t)atoi(args[2]);
		trkpars2->info.auto_detect_en[1] = (uint8_t)atoi(args[3]);
		pars_set((pars_ctx_p)trkpars2);
	}

    PRINTF("- auto-detect enable(aten): [%d %d] [horizontal, vertical]\n", trkpars2->info.auto_detect_en[0], trkpars2->info.auto_detect_en[1]);
}

void set_warning_dynamic_status(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.dynamic_status = (uint8_t)atoi(args[2]);
		if (fcwwarn->info.dynamic_status >= DYNAMIC_STATUS_UNKNOWN) {
			fcwwarn->info.dynamic_status = DYNAMIC_STATUS_ALL;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning dynamic status: %s (0:All, 1:W/O oncoming)\n", get_warning_dyn_status(fcwwarn->info.dynamic_status));
}

void set_pre_warning_flag(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.pre_warning_flag = (uint8_t)atoi(args[2]);
		if (fcwwarn->info.pre_warning_flag > 1) {
			fcwwarn->info.pre_warning_flag = 1;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("pre_warning flag: %s\n", get_activity_state(fcwwarn->info.pre_warning_flag));
}

void set_warning_flag(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.warning_flag = (uint8_t)atoi(args[2]);
		if (fcwwarn->info.warning_flag > 1) {
			fcwwarn->info.warning_flag = 1;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning flag: %s\n", get_activity_state(fcwwarn->info.warning_flag));
}

void set_emg_warning_flag(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.emg_warning_flag = (uint8_t)atoi(args[2]);
		if (fcwwarn->info.emg_warning_flag > 1) {
			fcwwarn->info.emg_warning_flag = 1;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("emergency warning flag: %s\n", get_activity_state(fcwwarn->info.emg_warning_flag));
}

void set_warning_ttc_v(char** args, int count)
{
	float v0, v1;
	
	if (count == 4) {
		v0 = (float)atof(args[2]);
		if (v0 < 0.0) {
			v0 = 0.0;
		}
		if (v0 > 200.0) {
			v0 = 200.0;
		}
		fcwwarn->info.warning_ttc_v[0] = v0 * KPH_TO_MS;
		v1 = (float)atof(args[3]);
		if (v1 < 0.0) {
			v1 = 0.0;
		}
		if (v1 > 200.0) {
			v1 = 200.0;
		}
		fcwwarn->info.warning_ttc_v[1] = v1 * KPH_TO_MS;
		pars_set((pars_ctx_p)fcwwarn);
	} else {
		v0 = fcwwarn->info.warning_ttc_v[0] * MS_TO_KPH;
		v1 = fcwwarn->info.warning_ttc_v[1] * MS_TO_KPH;
	}
	PRINTF("warning TTC_V: [%.2f %.2f] km/h\n", v0, v1);
}

void set_warning_ttc0(char** args, int count)
{
	float speed, ttc;
	
	if (count == 4) {
		speed = (float)atof(args[2]);
		if (speed < 0.0) {
			speed = 0.0;
		}
		if (speed > 200.0) {
			speed = 200.0;
		}
		fcwwarn->info.warning_ttc_v[0] = speed * KPH_TO_MS;
		ttc = (float)atof(args[3]);
		if (ttc < 0.0) {
			ttc = 0.0;
		}
		if (ttc > 10.0) {
			ttc = 10.0;
		}
		fcwwarn->info.warning_ttc[0] = ttc;
		pars_set((pars_ctx_p)fcwwarn);
	} else {
		speed = fcwwarn->info.warning_ttc_v[0] * MS_TO_KPH;
		ttc = fcwwarn->info.warning_ttc[0];
	}
	PRINTF("warning V0/TTC0: %.2f km/h, %.2f s\n", speed, ttc);
}

void set_warning_ttc1(char** args, int count)
{
	float speed, ttc;
		
	if (count == 4) {
		speed = (float)atof(args[2]);
		if (speed < 0.0) {
			speed = 0.0;
		}
		if (speed > 200.0) {
			speed = 200.0;
		}
		fcwwarn->info.warning_ttc_v[1] = speed * KPH_TO_MS;
		ttc = (float)atof(args[3]);
		if (ttc < 0.0) {
			ttc = 0.0;
		}
		if (ttc > 10.0) {
			ttc = 10.0;
		}
		fcwwarn->info.warning_ttc[1] = ttc;
		pars_set((pars_ctx_p)fcwwarn);
	} else {	
		speed = fcwwarn->info.warning_ttc_v[1] * MS_TO_KPH;
		ttc = fcwwarn->info.warning_ttc[1];
	}
	PRINTF("warning V1/TTC1: %.2f km/h, %.2f s\n", speed, ttc);
}

void set_pre_warning_ttc(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.pre_warning_ttc[0] = (float)atof(args[2]);
		if (fcwwarn->info.pre_warning_ttc[0] < fcwwarn->info.warning_ttc[0]) {
			fcwwarn->info.pre_warning_ttc[0] = fcwwarn->info.warning_ttc[0];
		}	
		fcwwarn->info.pre_warning_ttc[1] = (float)atof(args[3]);
		if (fcwwarn->info.pre_warning_ttc[1] < fcwwarn->info.warning_ttc[1]) {
			fcwwarn->info.pre_warning_ttc[1] = fcwwarn->info.warning_ttc[1];
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("pre-warning TTC [%.2f %.2f] s\n", fcwwarn->info.pre_warning_ttc[0], fcwwarn->info.pre_warning_ttc[1]);
}

void set_warning_ttc(char** args, int count)
{	
	if (count == 4) {
		fcwwarn->info.warning_ttc[0] = (float)atof(args[2]);
		if (fcwwarn->info.warning_ttc[0] < 0.0) {
			fcwwarn->info.warning_ttc[0] = 0.0;
		}
		if (fcwwarn->info.warning_ttc[0] > 10.0) {
			fcwwarn->info.warning_ttc[0] = 10.0;
		}
		fcwwarn->info.warning_ttc[1] = (float)atof(args[3]);
		if (fcwwarn->info.warning_ttc[1] < 0.0) {
			fcwwarn->info.warning_ttc[1] = 0.0;
		}
		if (fcwwarn->info.warning_ttc[1] > 10.0) {
			fcwwarn->info.warning_ttc[1] = 10.0;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning TTC: [%.2f %.2f] s\n", fcwwarn->info.warning_ttc[0], fcwwarn->info.warning_ttc[1]);
}

void set_emg_warning_ttc(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.emg_warning_ttc[0] = (float)atof(args[2]);
		if (fcwwarn->info.emg_warning_ttc[0] < 0.0) {
			fcwwarn->info.emg_warning_ttc[0] = 0.0;
		}
		if (fcwwarn->info.emg_warning_ttc[0] > fcwwarn->info.warning_ttc[0]) {
			fcwwarn->info.emg_warning_ttc[0] = fcwwarn->info.warning_ttc[0];
		}
		fcwwarn->info.emg_warning_ttc[1] = (float)atof(args[3]);
		if (fcwwarn->info.emg_warning_ttc[1] < 0.0) {
			fcwwarn->info.emg_warning_ttc[1] = 0.0;
		}
		if (fcwwarn->info.emg_warning_ttc[1] > fcwwarn->info.warning_ttc[1]) {
			fcwwarn->info.emg_warning_ttc[1] = fcwwarn->info.warning_ttc[1];
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("emergency warning TTC [%.2f %.2f] s\n", fcwwarn->info.emg_warning_ttc[0], fcwwarn->info.emg_warning_ttc[1]);
}

void set_warning_atv(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.warning_atv= (float)atof(args[2]);
		if (fcwwarn->info.warning_atv < 0) {
			fcwwarn->info.warning_atv = 0;
		}
		if (fcwwarn->info.warning_atv > 6.65) {
			fcwwarn->info.warning_atv = 6.65;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning distance Atv: %.2f m/s/s\n", fcwwarn->info.warning_atv);
}

void set_warning_factor(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.warning_factor = (float)atof(args[2]);
		if (fcwwarn->info.warning_factor < 0.0) {
			fcwwarn->info.warning_factor = 0.0;
		}
		if (fcwwarn->info.warning_factor > 5.0) {
			fcwwarn->info.warning_factor = 5.0;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning distance scaling factor: %.2f\n", fcwwarn->info.warning_factor);
}

void set_warning_min(char** args, int count)
{
	if (count == 3) {
		fcwwarn->info.warning_min = (float)atof(args[2]);
		if (fcwwarn->info.warning_min < 0.0) {
			fcwwarn->info.warning_min = 0.0;
		}
		if (fcwwarn->info.warning_min > 25.0) {
			fcwwarn->info.warning_min = 25.0;
		}
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning distance minimum: %.2f m\n", fcwwarn->info.warning_min);
}

void set_warning_delay(char** args, int count)
{
	if (count == 5) {
		fcwwarn->info.warning_delay[0]= (float)atof(args[2]);
		fcwwarn->info.warning_delay[1]= (float)atof(args[3]);
		fcwwarn->info.warning_delay[2]= (float)atof(args[4]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning delay time: [%.2fms %.2fs %.2fs]\n", fcwwarn->info.warning_delay[0], fcwwarn->info.warning_delay[1], fcwwarn->info.warning_delay[2]);
}

void set_straight_path(char** args, int count)
{
	if (count == 5) {
		fcwwarn->info.straight_path[0]= (float)atof(args[2]);
		fcwwarn->info.straight_path[1]= (float)atof(args[3]);
		fcwwarn->info.straight_path[2]= (float)atof(args[4]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("straight path: [%.2f %.2f %.2f] m\n", fcwwarn->info.straight_path[0], fcwwarn->info.straight_path[1], fcwwarn->info.straight_path[2]);
}

void set_inward_path(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.inward_path[0]= (float)atof(args[2]);
		fcwwarn->info.inward_path[1]= (float)atof(args[3]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("inward path: [%.2f %.2f] m\n", fcwwarn->info.inward_path[0], fcwwarn->info.inward_path[1]);
}

void set_warning_path(char** args, int count)
{
	if (count == 5) {
		fcwwarn->info.warning_path[0]= (float)atof(args[2]);
		fcwwarn->info.warning_path[1]= (float)atof(args[3]);
		fcwwarn->info.warning_path[2]= (float)atof(args[4]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning path: [%.2f %.2f %.2f] m\n", fcwwarn->info.warning_path[0], fcwwarn->info.warning_path[1],	fcwwarn->info.warning_path[2]);
}

void set_speed_factor(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.speed_factor[0]= (float)atof(args[2]);
		fcwwarn->info.speed_factor[1]= (float)atof(args[3]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("speed factor: [%.2f %.2f]\n", fcwwarn->info.speed_factor[0], fcwwarn->info.speed_factor[1]);
}

void set_path_score(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.path_score[0]= (uint8_t)atof(args[2]);
		fcwwarn->info.path_score[1]= (uint8_t)atof(args[3]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("path score: [%d %d]\n", fcwwarn->info.path_score[0], fcwwarn->info.path_score[1]);
}

void set_warning_score(char** args, int count)
{
	if (count == 4) {
		fcwwarn->info.warning_score[0]= (uint8_t)atof(args[2]);
		fcwwarn->info.warning_score[1]= (uint8_t)atof(args[3]);
		pars_set((pars_ctx_p)fcwwarn);
	}
	PRINTF("warning score: [%d %d]\n", fcwwarn->info.warning_score[0], fcwwarn->info.warning_score[1]);
}

void set_flyover_v_phase_threshold(int8_t thres)
{
    trkpars->info.vangle[5] = thres;
    pars_set((pars_ctx_p)trkpars);
}

void set_ditch_cover_v_phase_threshold(int8_t thres)
{
    trkpars->info.vangle[8] = thres;
    pars_set((pars_ctx_p)trkpars);
}

int8_t get_flyover_v_phase_threshold()
{
    return trkpars->info.vangle[5];
}

int8_t get_ditch_cover_v_phase_threshold()
{
    return trkpars->info.vangle[8];
}


float tracking_field_of_view_width_get(void)
{
	return trkpars->info.view_width;
}

int tracking_field_of_view_width_set(float value)
{
	trkpars->info.view_width = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_field_of_view_range_get(void)
{
	return trkpars->info.view_range;
}

int tracking_field_of_view_range_set(float value)
{
	trkpars->info.view_range = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_field_of_view_angle_get(void)
{
	return trkpars->info.view_angle;
}

int tracking_field_of_view_angle_set(float value)
{
	trkpars->info.view_angle = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_view_zone_value_get(uint8_t index)
{
	if (index >= 4) {
		return 0.0;
	}
	return trkpars->info.view_zone[index];
}

int tracking_view_zone_value_set(uint8_t index, float value)
{
	if (index >= 4) {
		return 1;
	}
	trkpars->info.view_zone[index] = value;
	if (index == 3) {
		pars_set((pars_ctx_p)trkpars);
	}
	return 0;
}

float tracking_aoa_shift_get(void)
{
	return trkpars->info.aoa_shift;
}

int tracking_aoa_shift_set(float value)
{
	if ((value < -90.0) || (value > 90.0)) {
		return 1;
	}	
	trkpars->info.aoa_shift = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_lateral_shift_get(void)
{
	return trkpars->info.position_shift[0];
}

int tracking_lateral_shift_set(float value)
{
	trkpars->info.position_shift[0] = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_longitudinal_shift_get(void)
{
	return trkpars->info.position_shift[1];
}

int tracking_longitudinal_shift_set(float value)
{
	trkpars->info.position_shift[1] = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

float tracking_radar_hight_get(void)
{
	return trkpars->info.position_shift[1];
}

int tracking_radar_hight_set(float value)
{
	trkpars->info.position_shift[1] = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

uint8_t tracking_warning_message_flag_get(void)
{
	return trkpars->info.warning_message_flag;	
}

uint8_t tracking_yaw_sensor_message_flag_get(void)
{
	return trkpars->info.yaw_sensor_message_flag;	
}

int tracking_fcw_warning_flags_get(uint8_t *flags)
{
	flags[0] = fcwwarn->info.pre_warning_flag;
	flags[1] = fcwwarn->info.warning_flag;
	flags[2] = fcwwarn->info.emg_warning_flag;
	return 0;

}

int tracking_fcw_warning_flags_set(uint8_t *flags)
{
	if ((flags[0] > 1) || (flags[1] > 1) || (flags[2] > 1)) {
		return 1;
	}	
	fcwwarn->info.pre_warning_flag = flags[0];
	fcwwarn->info.warning_flag = flags[1];
	fcwwarn->info.emg_warning_flag = flags[2];
	pars_set((pars_ctx_p)fcwwarn);
	return 0;
}


int tracking_fcw_warning_speed_level_get(uint8_t level, float *speed)
{
	if (level > 1) {
		return 1;
	}
	if (level == 0) {
		*speed = fcwwarn->info.warning_ttc_v[0] * MS_TO_KPH;
		return 0;		
	} else if (level == 1) {	
		*speed = fcwwarn->info.warning_ttc_v[1] * MS_TO_KPH;
		return 0;
	}
	return 1;

}

int tracking_fcw_warning_speed_level_set(uint8_t level, float speed)
{
	if (level > 1) {
		return 1;
	}
	if (level == 0) {
		fcwwarn->info.warning_ttc_v[0] = speed * KPH_TO_MS;
	} else if (level == 1) {	
		fcwwarn->info.warning_ttc_v[1] = speed * KPH_TO_MS;
	}
	pars_set((pars_ctx_p)fcwwarn);
	return 0;

}


int tracking_fcw_warning_speed_ttc_get(uint8_t type, uint8_t level, float *ttc)
{
	if ((type > 2) || (level > 1)) {
		return 1;
	}
	switch (type) {
		case 0: // pre-warning
			switch (level) {
				case 0: // level-low
					*ttc = fcwwarn->info.pre_warning_ttc[0];					
					break;
				case 1: // level-high
					*ttc = fcwwarn->info.pre_warning_ttc[1];
					break;
				default:
					return 1;
			}
			break;
		case 1: // warning
			switch (level) {
				case 0: // level-low
					*ttc = fcwwarn->info.warning_ttc[0];					
					break;
				case 1: // level-high
					*ttc = fcwwarn->info.warning_ttc[1];
					break;
				default:
					return 1;
			}
			break;
		case 2: // emergency warning
			switch (level) {
				case 0: // level-low
					*ttc = fcwwarn->info.emg_warning_ttc[0];					
					break;
				case 1: // level-high
					*ttc = fcwwarn->info.emg_warning_ttc[1];
					break;
				default:
					return 1;
			}
			break;
		default:
			return 1;
	}
	return 0;

}

int tracking_fcw_warning_speed_ttc_set(uint8_t type, uint8_t level, float ttc)
{
	if ((type > 2) || (level > 1)) {
		return 1;
	}
	switch (type) {
		case 0: // pre-warning
			switch (level) {
				case 0: // level-low
					fcwwarn->info.pre_warning_ttc[0] = ttc;
					break;
				case 1: // level-high
					fcwwarn->info.pre_warning_ttc[1] = ttc;
					break;
				default:
					return 1;
			}
			break;
		case 1: // warning
			switch (level) {
				case 0: // level-low
					fcwwarn->info.warning_ttc[0] = ttc; 				
					break;
				case 1: // level-high
					fcwwarn->info.warning_ttc[1] = ttc;
					break;
				default:
					return 1;
			}
			break;
		case 2: // emergency warning
			switch (level) {
				case 0: // level-low
					fcwwarn->info.emg_warning_ttc[0] = ttc; 				
					break;
				case 1: // level-high
					fcwwarn->info.emg_warning_ttc[1] = ttc;
					break;
				default:
					return 1;
			}
			break;
		default:
			return 1;
	}
	return 0;
}

uint8_t tracking_coordinate_axis_rotation_get(void)
{
	return trkpars->info.tracking_dbg;
}

int tracking_coordinate_axis_rotation_set(uint8_t value)
{
	if (value > AXIS_ROTATION_180) {
		return 1;
	}
	trkpars->info.tracking_dbg = value;
	pars_set((pars_ctx_p)trkpars);
	return 0;
}

uint8_t get_hori_alignment_total_num(){
	return trkpars2->info.calib_rule[4];
}

uint8_t get_hori_alignment_result(void)
{
	return trkpars2->info.align_result[0];
}

uint8_t get_hori_alignment_completed(void)
{
    return trkpars2->info.align_completed[0];
}

uint16_t get_vert_alignment_total_num(){
	return trkpars2->info.vert_rule[2] * VERTICAL_SAMPLE_SCALE;
}

uint8_t get_vert_alignment_result(void){
	return trkpars2->info.align_result[1];
}

uint8_t get_vert_alignment_completed(void){
	return trkpars2->info.align_completed[1];
}

void set_trk2_uds_speed_makeup(float speed_filter_a, float speed_filter_b, float stationary)
{
	if(speed_filter_a>=0.0f){
	    trkpars2->info.uds_speed_makeup[0] = speed_filter_a;
	}
	if(speed_filter_b>=0.0f){
        trkpars2->info.uds_speed_makeup[1] = speed_filter_b;
    }
    if(stationary>=0.0f){
	    trkpars2->info.uds_speed_makeup[2] = stationary;
	}
	pars_set((pars_ctx_p)trkpars2);
    PRINTF("uds speed makeup: [%.2f %.2f %.2f] [slope a, intercept b, speed makeup]\n", trkpars2->info.uds_speed_makeup[0], trkpars2->info.uds_speed_makeup[1], trkpars2->info.uds_speed_makeup[2]);
}

void get_trk2_uds_speed_makeup(float* Pspeed_filter_a, float* Pspeed_filter_b, float* Pstationary)
{
    if(Pspeed_filter_a!=NULL){
        * Pspeed_filter_a = trkpars2->info.uds_speed_makeup[0];
    }
    
    if(Pspeed_filter_b!=NULL){
        * Pspeed_filter_b = trkpars2->info.uds_speed_makeup[1];
    }
    
    if(Pstationary!=NULL){
        * Pstationary     = trkpars2->info.uds_speed_makeup[2];
    }
}

uint8_t get_trk2_auto_hori_detection_en(){
	return trkpars2->info.auto_detect_en[0];
}

uint8_t get_trk2_auto_vert_detection_en(){
	return trkpars2->info.auto_detect_en[1];
}



