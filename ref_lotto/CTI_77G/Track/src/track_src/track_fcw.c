/*
 * track_fcw.c
 *
 *  Created on: 2017/08/23
 *      Author: Benson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#if defined(CTI_Z7_0)
#include "sys_shared.h"
#endif
#include "product.h"
#include "frame.h"
#include "tracking.h"
#include "track_data.h"
#include "track_lib.h"
#include "track_fcw.h"
#include "track_warning.h"

#ifdef USING_FCW_MODE

static frame_data_t *trkfdata = NULL;
static const tracking_pars_t *trkpars = NULL;
static const tracking_pars2_t *trkpars2 = NULL;
static const fcw_warn_t *trkwarn = NULL;
static tracking_ctx_st *trkctx = NULL;
static int cipv_score_pthld = 0;
static float cipv_near_range = 0.0;
static double lane_width_near;
static double lane_width_far_in, lane_width_inc_in;
static double lane_width_far_out, lane_width_inc_out;
static double lane_width2_far_in, lane_width2_inc_in;
static double lane_width2_far_out, lane_width2_inc_out;
static double extend_lane_width_min, extend_lane_width_max;
static double radius_threshold_min, radius_threshold_max;
static uint8_t pcipv_enable;
#ifndef DEBUG_SIMU
static const product_info_t* prod = NULL;
#endif

typedef enum {
	DIR_Null	= 0,
	GoStraight	= 1,
	TurnRight	= 2,
	TurnLeft	= 3,
} vehicle_direction_t;

int track_fcw_init(frame_data_t *fdata, const tracking_pars_t *trkp, const tracking_pars2_t *trkp2, const void *warn, tracking_ctx_st *ctx)
{
	int index = 0;
	float cipv_buf_width;
	float cipv_near_width;
	PRINTF("TRACKING: FCW\n");
#ifndef DEBUG_SIMU
	prod = product_info_get();
#endif
	trkfdata = fdata;
	trkpars = trkp;
	trkpars2 = trkp2;
	trkwarn = (const fcw_warn_t *)warn;
	trkctx = ctx;
	trkctx->frame_cnt = 0;
	trkctx->target_list = NULL;
	trkctx->target_max_idx = 0;
	trkctx->standing_speed_v0 = 0.86;
	trkctx->standing_speed_a0 = 5.0;
	trkctx->standing_speed_v1 = 1.4;
	trkctx->standing_speed_a1 = 60.0;
	trkctx->standing_speed_v2 = 1.8;
	trkctx->weight_y_range = 50.0;
	trkctx->weight_x_near = 0.5;
	trkctx->weight_x_far = 0.2;
	trkctx->cipv_index = 255;
	trkctx->cipv_acc_index = 255;
	trkctx->cipv_aeb_index = 255;
	trkctx->cipv_losing_time = 0;
	trkctx->cipv_acc_losing_time = 0;
	trkctx->cipv_aeb_losing_time = 0;
	trkctx->tunnel_flag = 0;
	trkctx->dfilter_frame_cnt = 0;
	trkctx->auto_calib_left_num = 0;
	trkctx->auto_calib_right_num = 0;
	trkctx->calib_angle = 0;
	trkctx->target_get_max_step = 6;
	trkctx->target_get_xy[0][0] = LANE_ONE_WIDTH;
	trkctx->target_get_xy[0][1] = VIEW_NEAR_RANGE;
	trkctx->target_get_xy[1][0] = LANE_TWO_WIDTH;
	trkctx->target_get_xy[1][1] = VIEW_NEAR_RANGE;
	trkctx->target_get_xy[2][0] = LANE_ONE_WIDTH;
	trkctx->target_get_xy[2][1] = VIEW_HALF_RANGE;
	trkctx->target_get_xy[3][0] = LANE_TWO_WIDTH;
	trkctx->target_get_xy[3][1] = VIEW_HALF_RANGE;
	trkctx->target_get_xy[4][0] = LANE_TWO_WIDTH;
	trkctx->target_get_xy[4][1] = trkpars->info.view_range;
	trkctx->target_get_xy[5][0] = trkpars->info.view_width;
	trkctx->target_get_xy[5][1] = trkpars->info.view_range;
	cipv_score_pthld = trkpars->info.cipv[0];
	cipv_buf_width = (float)(trkpars->info.cipv[1]) / 100.0;
	cipv_near_width = (float)trkpars->info.cipv[2] / 100.0;
	cipv_near_range = (float)trkpars->info.cipv[3];
	lane_width_near = (double)trkpars->info.body_width + (double)cipv_near_width;
	lane_width_far_in = (double)trkpars->info.lane_width[0] - (double)(cipv_buf_width * 2.0);
	lane_width_inc_in = (lane_width_far_in - lane_width_near) / (double)cipv_near_range;
	lane_width_far_out = (double)trkpars->info.lane_width[0] + (double)(cipv_buf_width * 2.0);
	lane_width_inc_out = (lane_width_far_out - lane_width_near) / (double)cipv_near_range;
	lane_width2_far_in = (double)trkpars->info.lane_width[1] - (double)(cipv_buf_width * 2.0);
	lane_width2_inc_in = (lane_width2_far_in - lane_width_near) / (double)cipv_near_range;
	lane_width2_far_out = (double)trkpars->info.lane_width[1] + (double)(cipv_buf_width * 2.0);
	lane_width2_inc_out = (lane_width2_far_out - lane_width_near) / (double)cipv_near_range;
	extend_lane_width_min = (double)trkpars->info.extend_lane_width_coef[0]/10.0;
	extend_lane_width_max = (double)trkpars->info.extend_lane_width_coef[1]/10.0;
	radius_threshold_min = (double)trkpars->info.extend_lane_width_coef[2];
	radius_threshold_max = (double)trkpars->info.extend_lane_width_coef[3];
	pcipv_enable = trkpars2->info.pcipv_enable;

  	while (index < TARGET_HEAP_SIZE) {
  		trkctx->heap[index].idx = index; // 0:no object, 128: invalid
    	index++;
  	}
  	memset((void*)trkctx->auto_calib_angle, 0, sizeof(trkctx->auto_calib_angle));
	memset((void*)trkctx->guardrail_lr, 0, sizeof(trkctx->guardrail_lr));
	trkctx->guardrail_cluster_cnt = 0;
    memset((void*)trkctx->calib_angle_history, 0, sizeof(trkctx->calib_angle_history));
    trkctx->calib_angle_index = 0;
	return 0;
}

int track_fcw_target_dump(void)
{
	int index = 0;
	target_st *t = NULL;

	PRINTF("<MODE: FCW>\n");
	PRINTF("[TARGET]\n");
	for (index = 0; index < TARGET_HEAP_SIZE; index++) {
		t = &trkctx->heap[index];
		if (t->score != 0)  {
			PRINTF("-  T(%d) s:%d d:%d x:%.2f y:%.2f vx:%.2f vy:%.2f a:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vx, t->vy, t->angle);
		}
	}
	return 0;
}

static int track_fcw_taget_new_filtering(sorting_st *list)
{
	target_st *t = NULL;
	target_st *near_car_target = NULL;
	sorting_st *cur = NULL;
	float filter_range;
	float tv = 0.0;
	float detect_near_car_distance = 0;
	uint8_t detect_near_car_idx = 255;

	if (ABS(trkctx->yaw_rate) >= trkpars->info.ditchcover_filter[4]) {
		trkctx->dfilter_frame_cnt = trkpars->info.ditchcover_filter[5];
	} else if (trkctx->dfilter_frame_cnt > 0) {
		trkctx->dfilter_frame_cnt--;
	}

	cur = list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (t->score < TRACKING_SCALE) {
			cur = cur->next;
			continue;
		}
		// detect near car distance
		if ((t->y <= trkpars2->info.mirror[2]) && (ABS(t->x) <= trkpars2->info.mirror[3])) {
			if (detect_near_car_distance == 0 || t->y < detect_near_car_distance) {
				detect_near_car_idx = t->idx;
				detect_near_car_distance = t->y;
			}
		}
		cur = cur->next;
	}

	cur = list;
	while(cur) {
		t = &trkctx->heap[cur->idx];
		if (t->score != trkctx->tracking_pars.candidate) {
			cur = cur->next;
			continue;
		}
		// filtering
		if (((t->dyn_status > STANDING) && (t->dyn_status != FLYOVER) && (t->dyn_status != DITCHCOVER)) || trkctx->standing_flag) {
			// filter mirror for front near car
			if (detect_near_car_idx != 255) {
				near_car_target = &trkctx->heap[detect_near_car_idx];
				tv = ABS(near_car_target->vy + trkctx->my_speed);
				if ((trkctx->my_speed <= trkpars2->info.mirror[0]) && (tv <= trkpars2->info.mirror[1])) {
					if (((near_car_target->y <= trkpars2->info.mirror[5]) || (t->y > (near_car_target->y * trkpars2->info.mirror[4]))) &&
					   (t->idx != detect_near_car_idx) && (t->dyn_status == ONCOMING)) {
						t->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
						PRINTF("-  T_MIRROR(%d): s:%d d:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n",	t->idx, t->score, t->dyn_status, t->x, t->y, t->vx, t->vy);
#endif
						continue;
					}
				}
			}
			// filter out ditch cover
			filter_range = trkpars->info.ditchcover_filter[1] * ABS(t->vy);
			if (filter_range > trkpars->info.ditchcover_filter[3]) {
				filter_range = trkpars->info.ditchcover_filter[3];
			}
			if (((trkctx->my_speed >= trkpars->info.ditchcover_filter[0]) && (t->y <= filter_range) && (ABS(t->x) <= trkpars->info.ditchcover_filter[2]) &&
				(trkctx->dfilter_frame_cnt == 0)) && (t->dyn_status == STANDING || t->dyn_status == NOISE)) {
				t->dyn_status = DITCHCOVER;
			}
			// new target
			track_lib_target_new(t);
		} else if (t->dyn_status == STANDING) {
			t->score = ID_DELAY;
		}
		cur = cur->next;
	}

	return 0;
}

static int track_fcw_per_frame(void)
{
	sorting_st *head = NULL;

#ifdef DEBUG_PERFORMANCE
	uint32_t time = STM_0.CNT.R;
	PRINTF("[MEASUREMENT]\n");
#endif
	track_lib_measurement_get_xy();
	//track_lib_measurement_filtering();
#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: xy=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
	PRINTF("[PREDICTION]\n");
#endif
	track_lib_target_predict();

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: predict=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
	PRINTF("[TRACKING]\n");
#endif
	head = track_lib_target_sorting();

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: sort=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_data_association(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: asso=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_possible_grouping(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: pgrp=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_alpha_filtering(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: fltr=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_auto_horizontal_alignment(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: auto_horizontal_align=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_rcs_evaluation(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: rcs_cal=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_fcw_taget_new_filtering(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: nfltr=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_target_guardrail(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: guardrail=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_target_vertical_alignment(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: vertical alignment=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_target_grouping(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: tggrp=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
#endif

	track_lib_target_data_update(head);

#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: upd=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	time = STM_0.CNT.R;
	PRINTF("[NEW]\n");
#endif

	track_lib_possible_new();
#ifdef DEBUG_PERFORMANCE
	PRINTF("fcw: psnew=%.1fus\n", (STM_0.CNT.R - time)*0.016667f);
	PRINTF("[DONE]\n");
#endif	

	trkfdata->mgrp.state = TRK_MEAS_ST_DONE;
#ifdef DEBUG_CONSOLE_PRINTF
  	track_fcw_target_dump();
#endif
  	return 1;
}

int track_fcw_frame_init(uint16_t frame, float speed, float yaw, float radius, uint8_t gear, uint8_t door, float acc_z)
{
	trkctx->frame_cnt++;
	trkctx->my_speed = speed;
	trkctx->my_neg_speed = speed * -1.0;
	trkctx->yaw_rate = yaw;
	trkctx->acc_z = acc_z;
	trkctx->turn_radius = radius;
	trkctx->door_status = door;
	trkctx->frame_num = frame;
	if (!(trkctx->frame_cnt % trkctx->frame_rate)) {
		trkctx->my_accel = (trkctx->my_speed - trkctx->my_pre_speed);
		trkctx->my_pre_speed = trkctx->my_speed;
	}
	trkctx->measurements_count = trkfdata->mgrp.mcnt > trkpars->info.measurement_limit ? trkpars->info.measurement_limit : trkfdata->mgrp.mcnt;
	trkctx->measurements = trkfdata->mgrp.measurements;

	return 0;
}

int track_fcw_frame(void)
{
	float std_on_speed = 0;

	// standing on/off
	std_on_speed = trkpars->info.standing_on_off;
	if ((std_on_speed == 0) || ((std_on_speed > 0) && (trkctx->my_speed > std_on_speed))) {
		trkctx->standing_flag = 0;
	} else if ((std_on_speed > 0) && (trkctx->my_speed <= std_on_speed)) {
		trkctx->standing_flag = 1;
	}
#ifdef DEBUG_CONSOLE_PRINTF
	PRINTF("========>FCW FRAME(%d): speed:%.2f\n", trkctx->frame_num, trkctx->my_speed);
#endif
	track_fcw_per_frame();
	return 0;
}

static void track_fcw_search_my_lane(void)
{
	float cipv_range, cipv_acc_range, cipv_aeb_range;
	double rc; //radius of curvature
	double outer_lane, inner_lane, car_to_rc;
	double extend_lane_width = 0;
	uint8_t min_cipv, new_cipv;
	uint8_t min_cipv_acc, new_cipv_acc;
	uint8_t min_cipv_aeb, new_cipv_aeb;
	uint8_t vehicle_direction = DIR_Null;
	uint8_t cip_score;
	uint8_t cipv_losing_time;
	uint8_t check_cipv_flag;

	target_st *t = NULL;
	target_st *new_cipv_target = NULL;
	target_st *cipv_target = NULL;
	sorting_st *cur = NULL;

	// find CIP
	cipv_range = 1000.0;
	cipv_acc_range = 1000.0;
	cipv_aeb_range = 1000.0;
	min_cipv = 255;
	min_cipv_acc = 255;
	min_cipv_aeb = 255;
	new_cipv = 255;
	new_cipv_acc = 255;
	new_cipv_aeb = 255;

	if (trkctx->my_speed < 2.78)
	{
		rc = - 1000000;
	} else {
		rc = (double)trkctx->turn_radius;
	}
	check_cipv_flag = 0;
	cur = trkctx->target_list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (t->idx == trkctx->cipv_index ) {
			check_cipv_flag = 1;
			break;
		}
		cur = cur->next;
	}
	if (check_cipv_flag == 0) {
	    trkctx->cipv_index = 255;
	    trkctx->cipv_losing_time = 0;
	    trkctx->potential_cipv_index = 255;
	}
	cur = trkctx->target_list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (((trkwarn->info.dynamic_status == X_DYNAMIC_STATUS_ONCOMING_WO) && (t->dyn_status == ONCOMING)) || (t->dyn_status == FLYOVER) ||
			(t->dyn_status == DITCHCOVER) || (t->dyn_status == NOISE) || (t->guardrail_cnt >= 3) ||
			(ABS(trkctx->yaw_rate) >= trkpars->info.guardrail[3] && t->dyn_status == STANDING)) {
			// without oncoming and flyover
			if (trkctx->cipv_index == t->idx) {
			    trkctx->cipv_index = 255;
			    trkctx->cipv_losing_time = 0;
			    trkctx->potential_cipv_index = 255;//add
			    t->cip_score = 0;
			    t->cip_warning = NO_WARNING;
			    t->warning_score = 0;
		    }
			if (trkctx->cipv_acc_index == t->idx) {
			    trkctx->cipv_acc_index = 255;
			    trkctx->cipv_acc_losing_time = 0;
			    t->cip_acc_score = 0;
		    }
			if (trkctx->cipv_aeb_index == t->idx) {
			    trkctx->cipv_aeb_index = 255;
			    trkctx->cipv_aeb_losing_time = 0;
			    t->cip_aeb_score = 0;
		    }
			cur = cur->next;
			continue;
		}

		if (t->cip_score > 0) {
			t->cip_score --;
		}
		if (t->cip_acc_score > 0) {
			t->cip_acc_score --;
		}
		if (t->cip_aeb_score > 0) {
			t->cip_aeb_score --;
		}

		if(ABS(rc) > radius_threshold_max){ //go straight.
			vehicle_direction = GoStraight;
		} else if((rc >= 0)&&(rc <= radius_threshold_max)){ //Turn right
			vehicle_direction = TurnRight;
		} else if((rc < 0)&&(rc >= (-1)*radius_threshold_max)){ //Turn left
			vehicle_direction = TurnLeft;
		}

		if(ABS(rc) <= radius_threshold_min){
			extend_lane_width = extend_lane_width_max;
		} else if((radius_threshold_min < ABS(rc)) && (ABS(rc)<=radius_threshold_max)){
			double coef_a, coef_b;
			coef_a = (extend_lane_width_max - extend_lane_width_min)/(radius_threshold_max - radius_threshold_min);
			coef_b = extend_lane_width_max + radius_threshold_min*coef_a;
			if(vehicle_direction == TurnRight){
				extend_lane_width = -coef_a*rc + coef_b;
			}else if(vehicle_direction == TurnLeft){
				extend_lane_width = coef_a*rc + coef_b;
			}
		} else {
			extend_lane_width = 0.0;
		}

		if(vehicle_direction == TurnRight)
		{
			outer_lane = pow((double)(rc + (double)(trkpars->info.lane_width[0]/2) ), 2);
			inner_lane = pow((double)(rc - (double)(trkpars->info.lane_width[0]/2) - extend_lane_width), 2);
		}
		else if(vehicle_direction == TurnLeft)
		{
			outer_lane = pow((double)(rc + (double)(trkpars->info.lane_width[0]/2) + extend_lane_width), 2);
			inner_lane = pow((double)(rc - (double)(trkpars->info.lane_width[0]/2)), 2);
		}
		else // Go straight
		{
			outer_lane = pow((double)(rc + (double)(trkpars->info.lane_width[0]/2)), 2);
			inner_lane = pow((double)(rc - (double)(trkpars->info.lane_width[0]/2)), 2);
		}

		car_to_rc = pow((double)(t->sx - rc), 2) + pow((double)t->y, 2);

		if (((rc < 0.0) && (outer_lane < car_to_rc) && (car_to_rc < inner_lane)) ||
			((rc >= 0.0) && (inner_lane < car_to_rc) && (car_to_rc < outer_lane))) {
			if (t->y < cipv_range) {
				cipv_range = t->y;
				min_cipv = t->idx;
			}
			if ((t->dyn_status != ONCOMING) && (t->y < cipv_acc_range)) {
				if ((trkctx->my_speed < trkpars2->info.acc_aeb[0] && t->dyn_status == STANDING) || (t->dyn_status != STANDING)) {
					cipv_acc_range = t->y;
					min_cipv_acc = t->idx;
				}
			}
			if (t->y < cipv_aeb_range) {
				if ((t->y <= trkpars2->info.acc_aeb[1] && t->dyn_status == STANDING) || (t->dyn_status != STANDING)) {
					cipv_aeb_range = t->y;
					min_cipv_aeb = t->idx;
				}
			}
		}
		cur = cur->next;
	}

	// CIPV
	if (min_cipv != 255) {
		t = &trkctx->heap[min_cipv];
		t->cip_score = t->cip_score + 2;
		if (t->dyn_status == STANDING) {
			cip_score = trkpars->info.cipv[0];
		} else {
			cip_score = trkpars->info.cipv[2];
		}
		if (t->cip_score >= cip_score) {
			new_cipv = min_cipv;
		}
	}
	if (new_cipv != 255) {
		if (trkctx->cipv_index != 255) {
			cipv_target = &trkctx->heap[trkctx->cipv_index];
			if (cipv_target->score >= TRACKING_SCALE) {
				new_cipv_target = &trkctx->heap[new_cipv];
				if (ABS(cipv_target->y - new_cipv_target->y) < 2.5 && ABS(cipv_target->sx - new_cipv_target->sx) < 1.5 && ABS(cipv_target->vy - new_cipv_target->vy) < 1) {
					new_cipv_target->cip_score = 0;
					new_cipv = trkctx->cipv_index;
				}
			}
		}
		trkctx->cipv_index = new_cipv;
		cipv_target = &trkctx->heap[trkctx->cipv_index];
		cipv_target->cip_score = 1;

		if (cipv_target->cip_warning == NO_WARNING) {
			cipv_target->cip_warning = CIP_WARNING;
			cipv_target->warning_score = 0;
		}
	}
	if (trkctx->cipv_index != 255) {
		cipv_target = &trkctx->heap[trkctx->cipv_index];
		if (cipv_target->score >= TRACKING_SCALE) {
			if (cipv_target->cip_score == 0) {
				trkctx->cipv_losing_time ++;
			} else {
				cipv_target->cip_score = 1;
				trkctx->cipv_losing_time = 0;
			}
			if (t->dyn_status == STANDING) {
				cipv_losing_time = trkpars->info.cipv[1];
			} else {
				cipv_losing_time = trkpars->info.cipv[3];
			}
			if (trkctx->cipv_losing_time >= cipv_losing_time) {
				trkctx->cipv_index = 255;
				cipv_target->cip_warning = NO_WARNING;
				cipv_target->warning_score = 0;
			}
		} else {
			trkctx->cipv_index = 255;
			trkctx->cipv_losing_time = 0;
			cipv_target->cip_score = 0;
			cipv_target->cip_warning = NO_WARNING;
			cipv_target->warning_score = 0;
		}
	}

	// ACC CIPV
	if (min_cipv_acc != 255) {
		t = &trkctx->heap[min_cipv_acc];
		t->cip_acc_score = t->cip_acc_score + 2;
		if (t->dyn_status == STANDING) {
			cip_score = trkpars->info.cipv[0];
		} else {
			cip_score = trkpars->info.cipv[2];
		}
		if (t->cip_acc_score >= cip_score) {
			new_cipv_acc = min_cipv_acc;
		}
	}
	if (new_cipv_acc != 255) {
		if (trkctx->cipv_acc_index != 255) {
			cipv_target = &trkctx->heap[trkctx->cipv_acc_index];
			if (cipv_target->score >= TRACKING_SCALE) {
				new_cipv_target = &trkctx->heap[new_cipv_acc];
				if (ABS(cipv_target->y - new_cipv_target->y) < 2.5 && ABS(cipv_target->sx - new_cipv_target->sx) < 1.5 && ABS(cipv_target->vy - new_cipv_target->vy) < 1) {
					new_cipv_target->cip_acc_score = 0;
					new_cipv_acc = trkctx->cipv_acc_index;
				}
			}
		}
		trkctx->cipv_acc_index = new_cipv_acc;
		cipv_target = &trkctx->heap[trkctx->cipv_acc_index];
		cipv_target->cip_acc_score = 1;
	}
	if (trkctx->cipv_acc_index != 255) {
		cipv_target = &trkctx->heap[trkctx->cipv_acc_index];
		if (cipv_target->score >= TRACKING_SCALE) {
			if (cipv_target->cip_acc_score == 0) {
				trkctx->cipv_acc_losing_time ++;
			} else {
				cipv_target->cip_acc_score = 1;
				trkctx->cipv_acc_losing_time = 0;
			}
			if (t->dyn_status == STANDING) {
				cipv_losing_time = trkpars->info.cipv[1];
			} else {
				cipv_losing_time = trkpars->info.cipv[3];
			}
			if (trkctx->cipv_acc_losing_time >= cipv_losing_time) {
				trkctx->cipv_acc_index = 255;
			}
		} else {
			trkctx->cipv_acc_index = 255;
			trkctx->cipv_acc_losing_time = 0;
			cipv_target->cip_acc_score = 0;
		}
	}

	// AEB CIPV
	if (min_cipv_aeb != 255) {
		t = &trkctx->heap[min_cipv_aeb];
		t->cip_aeb_score = t->cip_aeb_score + 2;
		if (t->dyn_status == STANDING) {
			cip_score = trkpars->info.cipv[0];
		} else {
			cip_score = trkpars->info.cipv[2];
		}
		if (t->cip_aeb_score >= cip_score) {
			new_cipv_aeb = min_cipv_aeb;
		}
	}
	if (new_cipv_aeb != 255) {
		if (trkctx->cipv_aeb_index != 255) {
			cipv_target = &trkctx->heap[trkctx->cipv_aeb_index];
			if (cipv_target->score >= TRACKING_SCALE) {
				new_cipv_target = &trkctx->heap[new_cipv_aeb];
				if (ABS(cipv_target->y - new_cipv_target->y) < 2.5 && ABS(cipv_target->sx - new_cipv_target->sx) < 1.5 && ABS(cipv_target->vy - new_cipv_target->vy) < 1) {
					new_cipv_target->cip_aeb_score = 0;
					new_cipv_aeb = trkctx->cipv_aeb_index;
				}
			}
		}
		trkctx->cipv_aeb_index = new_cipv_aeb;
		cipv_target = &trkctx->heap[trkctx->cipv_aeb_index];
		cipv_target->cip_aeb_score = 1;
	}
	if (trkctx->cipv_aeb_index != 255) {
		cipv_target = &trkctx->heap[trkctx->cipv_aeb_index];
		if (cipv_target->score >= TRACKING_SCALE) {
			if (cipv_target->cip_aeb_score == 0) {
				trkctx->cipv_aeb_losing_time ++;
			} else {
				cipv_target->cip_aeb_score = 1;
				trkctx->cipv_aeb_losing_time = 0;
			}
			if (t->dyn_status == STANDING) {
				cipv_losing_time = trkpars->info.cipv[1];
			} else {
				cipv_losing_time = trkpars->info.cipv[3];
			}
			if (trkctx->cipv_aeb_losing_time >= cipv_losing_time) {
				trkctx->cipv_aeb_index = 255;
			}
		} else {
			trkctx->cipv_aeb_index = 255;
			trkctx->cipv_aeb_losing_time = 0;
			cipv_target->cip_aeb_score = 0;
		}
	}

	return;
}

float usingMySpeedToGetMinimumPathRadius(float mySpeed) {
	mySpeed = mySpeed * 0.65f; //Speeding.
	return (mySpeed * mySpeed) / (3 - 0.03f * mySpeed);
}

float myLocationToPotentialCIPVRadius(float x, float y) {
	if(x == 0)
		return 1024;
	else
		return (x * x + y * y) / (2 * x);
}

static void track_cipv_when_turning()
{
	target_st *t = NULL;
	sorting_st *cur = NULL;
	target_st *cipv_target = NULL;
	trkctx->potential_cipv_index = 255;

	cur = trkctx->target_list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (t->dyn_status == MOVING)
		{
			if (t->cip_turnright_score > 0) {
				t->cip_turnright_score--;
			}
			else if (t->cip_turnleft_score > 0) {
				t->cip_turnleft_score--;
			}
			else if (t->cip_go_straight_score > 0) {
				t->cip_go_straight_score--;
			}

			// Potential CIPV become CIPV, or clear potential_cip_flag.
			if (t->potential_cip_flag == 1) {
				trkctx->potential_cipv_index = t->idx;
				if (t->cipvTurningLocation > 0)
					t->cipvTurningLocation = t->cipvTurningLocation - trkctx->my_speed / (float)trkctx->frame_rate;
				if (t->cipvTurningLocation > 0 && t->cipvTurningLocation < 10) {
					// My vehicle & CIPV both right turn.
					if (trkctx->yaw_rate <= -1 && t->potentialCIPVDirection == TurnRight) {
						trkctx->cipv_index = t->idx;
						t->cip_warning = CIP_WARNING;
						t->warning_score = 0;
						trkctx->cipv_losing_time = 0;
						t->potential_cip_flag = 1;//Hold the cipv on.
						t->cip_score = 1;
						t->cipvTurningLocation = 0;
					} // My vehicle & CIPV both left turn.
					else if (trkctx->yaw_rate >= 1 && t->potentialCIPVDirection == TurnLeft) {
						trkctx->cipv_index = t->idx;
						t->cip_warning = CIP_WARNING;
						t->warning_score = 0;
						trkctx->cipv_losing_time = 0;
						t->potential_cip_flag = 1;//Hold the cipv on.
						t->cip_score = 1;
						t->cipvTurningLocation = 0;
					}
				}

				// My vehicle & CIPV run in different directions.
				/*if ((trkctx->yaw_rate <= -1 && t->potentialCIPVDirection == TurnLeft) ||
					(trkctx->yaw_rate >= 1 && t->potentialCIPVDirection == TurnRight)) {
					//TODO: score mechanism.
					t->potential_cip_flag = 0;
					t->cipvTurningLocation = 0;
				}*/

				// My vehicle & CIPV both go straight, and in same lane, clear pCIPV status.
				if (trkctx->yaw_rate == 0 && ABS(t->vx) <= 0.5 && ABS(t->x) <= 2) {
					t->cip_go_straight_score += 2;
					if (t->cip_go_straight_score > 4) {
						t->potential_cip_flag = 0;
						t->cip_go_straight_score = 0;
						t->potentialCIPVDirection = GoStraight;
						trkctx->potential_cipv_index = 255;
					}
				}// My vehicle & CIPV both go straight, and in different lane.
				else if (trkctx->yaw_rate == 0 && ABS(t->vx) <= 0.5 && ABS(t->x) > 2) {
					t->cip_go_straight_score += 2;
					if (t->cip_go_straight_score > 4) {
						t->potential_cip_flag = 0;
						t->cip_turnleft_score = 0;
						t->cip_turnright_score = 0;
						t->cip_go_straight_score = 0;
						t->cipvTurningLocation = 0;
						t->potentialCIPVDirection = GoStraight;
						trkctx->potential_cipv_index = 255;
					}
				}
			}
		}
		//Delete or keep potential CIPV
		if (usingMySpeedToGetMinimumPathRadius(trkctx->my_speed) > ABS(myLocationToPotentialCIPVRadius(t->x, t->y)))
		{
			//t->cip_score = 0;
			//t->cip_warning = NO_WARNING;
			t->potentialCIPVDirection = DIR_Null;
			t->potential_cip_flag = 0;
		}
		cur = cur->next;
	}

	// When CIPV is turning, Track it. 
	if (trkctx->cipv_index != 255) {
		cipv_target = &trkctx->heap[trkctx->cipv_index];
		if (cipv_target->score >= TRACKING_SCALE && cipv_target->dyn_status == MOVING) {
			// CIPV is turning, and my car is go straight or a little turning.
			if (ABS(cipv_target->vx) >= 0.5 && ABS(trkctx->yaw_rate) <= 2.5 && trkctx->my_speed != 0 && ABS(cipv_target->x) <= 2.5) {
				if (cipv_target->vx >= 0.5)
					cipv_target->cip_turnright_score += 2;
				else if (cipv_target->vx <= -0.5)
					cipv_target->cip_turnleft_score += 2;
			}// CIPV is turning, and my car is turning.
			else if (ABS(cipv_target->vx) >= 1 && ABS(trkctx->yaw_rate) > 2.5 && trkctx->my_speed != 0 && ABS(cipv_target->x) > 2.5) {
				if (cipv_target->vx >= 1)
					cipv_target->cip_turnright_score += 2;
				else if (cipv_target->vx <= -1)
					cipv_target->cip_turnleft_score += 2;
			}

			if (cipv_target->cip_turnright_score > 4) {
				trkctx->potential_cipv_index = cipv_target->idx;
				cipv_target->cip_turnright_score = 0;
				cipv_target->potential_cip_flag = 1;
				cipv_target->potentialCIPVDirection = TurnRight;
				cipv_target->cipvTurningLocation = cipv_target->y;
				//cipv_target->myVehicleTurningAfterAFewFrame = trkctx->frame_rate * cipv_target->y / (trkctx->my_speed * 1000 / 3600);
			}
			else if (cipv_target->cip_turnleft_score > 4) {
				trkctx->potential_cipv_index = cipv_target->idx;
				cipv_target->cip_turnleft_score = 0;
				cipv_target->potential_cip_flag = 1;
				cipv_target->potentialCIPVDirection = TurnLeft;
				cipv_target->cipvTurningLocation = cipv_target->y;
				//cipv_target->myVehicleTurningAfterAFewFrame = trkctx->frame_rate * cipv_target->y / (trkctx->my_speed * 1000 / 3600);
			}
		}
	}

	//If doesn't exist CIPV, and exist potential CIPV, then set pCIPV on.
	if (trkctx->cipv_index == 255 && trkctx->potential_cipv_index != 255) {
		target_st *tempTarget = &trkctx->heap[trkctx->potential_cipv_index];
		tempTarget->cip_warning = CIP_WARNING;
		trkctx->cipv_index = trkctx->potential_cipv_index;
		trkctx->cipv_losing_time = 0;
		//TODO: Lock min distance pCIPV.
	}

	return;
}

int track_fcw_target_filtering(void)
{
	int index = 0, p, p0, p1, p2, p3, p4;
	int inserted = 0;
	int sorting_index = 0;
	float vx, tv = 0.0;
	float left_or_right;
	uint8_t i;
	sorting_st *head = NULL;
	sorting_st *cur = NULL;
	sorting_st *pre = NULL;
	sorting_st *new = NULL;
	target_st *t = NULL;
#ifdef DEBUG_CONSOLE_PRINTF
	PRINTF("[OUTPUT]\n");
#endif
	// reset target search info
	trkctx->target_cnt = 0;
	trkctx->target_list = NULL;
	trkctx->target_get_step	= 255;
	trkctx->target_get_status = 0;
	// FCW minimum and maximum operating speed
	if ((trkctx->my_speed >= 0) && ((trkctx->my_speed < trkpars->info.oper_speed[0]) ||  (trkctx->my_speed > trkpars->info.oper_speed[1]))) {
		return 0; // FCW inactive
	}
	for (index = 0; index <= trkctx->target_max_idx; index++) {
		t = &trkctx->heap[index];
		if (t->score > 0) {
			p = t->measured + t->missed;
			p0 = (p - 1) % 5;
			p1 = (p0 + 4) % 5;
			p2 = (p0 + 3) % 5;
			p3 = (p0 + 2) % 5;
			p4 = (p0 + 1) % 5;
			if (p == 1) {
				t->pvx = t->vx;
			} else if (p >= 5) {
				vx = (t->vxq[p0] * 0.6) + (t->vxq[p1] * 0.2) + (t->vxq[p2] * 0.1) + (t->vxq[p3] * 0.1);
				if ((p % trkctx->frame_rate) == 0) {
					t->accx = (vx - t->pvx);
					t->pvx = vx;
				}
			}
			// smooth y velocity
			t->svyq[p0] = (t->vyq[p0] * 0.2625) + (t->vyq[p1] * 0.1546) + (t->vyq[p2] * 0.1658) + (t->vyq[p3] * 0.1546) + (t->vyq[p4] * 0.2625);
			// acceleration calculation
			if (p >= 5) {
				t->accy = (t->svyq[p0] - t->svyq[p4]) / (trkctx->frame_slot_sec * 4);
				t->accyq[p0] = (t->accy * 0.2625) + (t->accyq[p1] * 0.1546) + (t->accyq[p2] * 0.1658) + (t->accyq[p3] * 0.1546) + (t->accyq[p4] * 0.2625);
			} else if (p == 4) {
				t->accy = (t->svyq[p0] - t->svyq[p3]) / (trkctx->frame_slot_sec * 3);
				t->accyq[p0] = (t->accy * 0.3178) + (t->accyq[p1] * 0.1822) + (t->accyq[p2] * 0.1822) + (t->accyq[p3] * 0.3178);
			} else if (p >= 3) {
				t->accy = (t->svyq[p0] - t->svyq[p2]) / (trkctx->frame_slot_sec * 2);
				t->accyq[p0] = (t->accy * 0.3906) + (t->accyq[p1] * 0.2188) + (t->accyq[p2] * 0.3906);
			} else if (p == 2) {
				t->accy = (t->svyq[p0] - t->svyq[p1]) / trkctx->frame_slot_sec;
				t->accyq[p0] = (t->accy * 0.5) + (t->accyq[p1] * 0.5);
			}
			t->accy = (t->accyq[p0] * 0.6) + (t->accyq[p1] * 0.2) + (t->accyq[p2] * 0.1) + (t->accyq[p3] * 0.1);
		}
		if (t->score < TRACKING_SCALE) {
			continue;
		}
		// field of view
		if ((ABS(t->angle) > trkpars->info.view_angle) || (ABS(t->sx) > trkpars->info.view_width) || (t->y > trkpars->info.view_range)) {
			continue;
		}
		// filter out standing targets
		if ((!trkctx->standing_flag || trkctx->tunnel_flag) && (t->dyn_status == STANDING)) {
			continue;
		}
		tv = t->vy + trkctx->my_speed;
		// supported dynamic status filtering
		if ((trkpars->info.dynamic_status == DYNAMIC_STATUS_ONCOMING_ONLY) && ((t->dyn_status != ONCOMING) || ((t->dyn_status == ONCOMING) && (tv > -2.78)))) {
			continue;
		}
		// flyover filter
		if ((trkpars->info.vangle[1] == 0) && ((t->dyn_status == FLYOVER) || (t->dyn_status == DITCHCOVER) || (t->dyn_status == NOISE))) {
			if (trkctx->cipv_index == t->idx) {
			    trkctx->cipv_index = 255;
			    trkctx->cipv_losing_time = 0;
			    trkctx->potential_cipv_index = 255;//add
			    t->cip_score = 0;
			    t->cip_warning = NO_WARNING;
			    t->warning_score = 0;
		    }
			if (trkctx->cipv_acc_index == t->idx) {
			    trkctx->cipv_acc_index = 255;
			    trkctx->cipv_acc_losing_time = 0;
			    t->cip_acc_score = 0;
		    }
			if (trkctx->cipv_aeb_index == t->idx) {
			    trkctx->cipv_aeb_index = 255;
			    trkctx->cipv_aeb_losing_time = 0;
			    t->cip_aeb_score = 0;
		    }
			continue;
		}
		// guardrail dynamic filter
		if (t->dyn_status == MOVING && t->y <= 50 && tv <= 8.33) {//lxh:old:t->y <= 30
			for (i = 0; i < trkctx->guardrail_cluster_cnt; i++) {
					//x=ay+b	//lxh+
					if((t->y >= trkctx->guardrail_lr[i].y_near) && (t->y <= trkctx->guardrail_lr[i].y_far))
					{ 
						left_or_right = trkctx->guardrail_lr[i].linear_regression_a * t->y + trkctx->guardrail_lr[i].linear_regression_b; 
						if (trkctx->guardrail_lr[i].x >= 0) 
							left_or_right =  t->x - left_or_right;
						else
							left_or_right = left_or_right - t->x;

						if (left_or_right >= -0.4) {
							t->score = ID_DELAY;
#ifdef DEBUG_GUARDRAIL
							PRINTF("-  GUARDRAIL1(%d): lr1:%.2f score:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n", t->idx, left_or_right, t->score, t->x, t->y, t->vx, t->vy);
#endif
							break;
						}
#ifdef DEBUG_GUARDRAIL
						else
							PRINTF("-  GUARDRAIL1(%d): lr0:%.2f score:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n", t->idx, left_or_right, t->score, t->x, t->y, t->vx, t->vy);
#endif

					
					} else {
#ifdef DEBUG_GUARDRAIL
						PRINTF("- I_GUARDRAIL(%d): s:%d d:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vx, t->vy);
#endif
					}//lxh+ end
				}
			if (t->score == ID_DELAY) {
				continue;
			}
		}
		//RCS filter
		if (t->object_type == PEDESTRIAN && t->dyn_status == ONCOMING) {
			continue;
		}

#ifdef DEBUG_CONSOLE_PRINTF
		PRINTF("-  T(%d) s:%d d:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vx, t->vy);
#endif
		inserted = 0;
		new = &trkctx->sorting[sorting_index];
		memset(new, 0, sizeof(sorting_st));
		new->idx = index;
		new->used = 0;
		new->ry = t->y;
		if (sorting_index == 0) {
			// head
			head = new;
			head->prev = NULL;
			head->next = NULL;
			sorting_index++;
			trkctx->target_cnt++;
			continue;
		}
		cur = head;
		while (cur) {
			// insert
			if (new->ry < cur->ry) {
				pre = cur->prev;
				new->next = cur;
				cur->prev = new;
				if (pre) {
					pre->next = new;
					new->prev = pre;
				}
				if (cur == head)
					head = new;
				inserted = 1;
				break;
			}
			pre = cur;
			cur = cur->next;
		}
		// add to tail;
		if (inserted == 0) {
			if (pre == NULL)
				pre = head;
			pre->next = new;
			new->prev = pre;
			new->next = NULL;
		}
		sorting_index++;
		trkctx->target_cnt++;
	}
	trkctx->target_list = head;

	if(pcipv_enable >= 1) {
		track_fcw_search_my_lane();
		track_cipv_when_turning();
	}
	return trkctx->target_cnt;
}

int track_fcw_target_get(target_st *output)
{
	uint8_t dyn_status = 0;
	float x = 0, y = 0;
	sorting_st *curList = NULL;
	target_st *t = NULL;
	
	if (trkctx->target_cnt == 0) {
		output = NULL;
		return 0; // (0) target list is NULL
	}
	// check if the CIP found
	if ((trkctx->target_get_step == 255) && (trkctx->cipv_index == 255)) {
		trkctx->target_get_step = 0;
	}
	// get CIP target first
	if ((trkctx->target_get_step == 255) && (trkctx->cipv_index != 255)) {
		t = &trkctx->heap[trkctx->cipv_index];
//		if(prod->customer == CUSTOM_ID_CONDI)
//		{
//			track_condi_warning_get(t);
//		}
//		else
//		{
//			track_fcw_warning_get(t);
//		}
		track_fcw_warning_get(t);
		memcpy(output, t, sizeof(target_st));
		output->x = output->sx;
//		if (prod->customer == CUSTOM_ID_YUTONG || prod->customer == CUSTOM_ID_ECAR) {
//	    	if (t->score == trkctx->tracking_pars.win && t->dyn_status == STOPPED && output->y <= 5.0 && ABS(output->x) <= 1.8) {
//	    		if (output->angle > 25.5) {
//	    			output->angle = 25;
//	    		} else if (output->angle < -25.6) {
//	    			output->angle = -25;
//	    		}
//	    	}
//		}
		output->cip_acc_flag = 0;
		output->cip_aeb_flag = 0;
		if (trkctx->cipv_index == trkctx->cipv_acc_index) {
			output->cip_acc_flag = 1;
		}
		if (trkctx->cipv_index == trkctx->cipv_aeb_index) {
			output->cip_aeb_flag = 1;
		}
		// predict real position
		if (trkpars->info.frame_makeup[0] != 0) {
			output->x += (output->vx * trkctx->frame_slot_sec * ((float)trkpars->info.frame_makeup[1] / 10.0f));
			output->y += (output->vy * trkctx->frame_slot_sec * ((float)trkpars->info.frame_makeup[1] / 10.0f));
		}
		trkctx->target_get_step = 0;
		return 2; // (2) CIPV target
	} else {
		while (trkctx->target_get_status < MAX_DYN_STATUS) {
			switch (trkctx->target_get_status) {
				case 0:
					dyn_status = ONCOMING;
					break;
				case 1:
					dyn_status = MOVING;
					break;
				case 2:
					dyn_status = STOPPED;
					break;
				case 3:
					dyn_status = STANDING;
					break;
				case 4:
					dyn_status = FLYOVER;
					break;
				case 5:
					dyn_status = DITCHCOVER;
					break;
				case 6:
					dyn_status = NOISE;
					break;
				default:
					dyn_status = MAX_DYN_STATUS;
					break;
			}
			while (trkctx->target_get_step < trkctx->target_get_max_step) {
				x = trkctx->target_get_xy[trkctx->target_get_step][0];
				y = trkctx->target_get_xy[trkctx->target_get_step][1];
				curList = trkctx->target_list;
				while (curList) {
					if (curList->used || (curList->idx == trkctx->cipv_index)) {
						curList = curList->next;
						continue;
					}
					t = &trkctx->heap[curList->idx];
					if ((t->y <= y) && (ABS(t->sx) <= x) && (t->dyn_status == dyn_status)) {
						memcpy(output, t, sizeof(target_st));
						output->x = output->sx;
//						if (prod->customer == CUSTOM_ID_YUTONG || prod->customer == CUSTOM_ID_ECAR) {
//					    	if (t->score == trkctx->tracking_pars.win && t->dyn_status == STOPPED && output->y <= 5.0 && ABS(output->x) <= 1.8) {
//					    		if (output->angle > 25.5) {
//					    			output->angle = 25.0;
//					    		} else if (output->angle < -25.6) {
//					    			output->angle = -25.0;
//					    		}
//					    	}
//						}
						output->cip_warning = NO_WARNING;
						output->cip_acc_flag = 0;
						output->cip_aeb_flag = 0;
						if (curList->idx == trkctx->cipv_acc_index) {
							output->cip_acc_flag = 1;
						}
						if (curList->idx == trkctx->cipv_aeb_index) {
							output->cip_aeb_flag = 1;
						}
						// predict real position
						if (trkpars->info.frame_makeup[0] != 0) {
							output->x += (output->vx * trkctx->frame_slot_sec * ((float)trkpars->info.frame_makeup[1] / 10.0f));
							output->y += (output->vy * trkctx->frame_slot_sec * ((float)trkpars->info.frame_makeup[1] / 10.0f));
						}
						curList->used = 1;
						curList = curList->next;
						return 1; // (1) normal target
					}
					curList = curList->next;
				}
				trkctx->target_get_step++;
			}
			trkctx->target_get_status++;
			trkctx->target_get_step = 0;
		}
    }
	
  	return 0; // (0) target list is NULL
}
#endif // USING_FCW_MODE
