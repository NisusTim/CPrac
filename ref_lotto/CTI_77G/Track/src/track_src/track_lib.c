/*
 * track_lib.c
 *
 *  Created on: 2018/08/02
 *      Author: Cubtek
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "custom_math.h"
#if defined(CTI_Z7_0)
#include "sys_shared.h"
#endif
#include "frame.h"
#include "tracking.h"
#include "track_data.h"
#include "track_lib.h"
#include "tracking.h"
#include "track_simu_interface.h"
#include "alignment_main.h"
#include "linear_regression.h"

typedef enum{
	HORI_ALIGN_NONE = 0,
	HORI_ALIGN_APP_DCM,
	HORI_ALIGN_AUTO_DETECT,
	HORI_ALIGN_ONE_SHOT,
	HORI_ALIGN_AUTO_CONTINUOUS
}HORI_ALIGN_CMD;

typedef enum{
	VERT_ALIGN_NONE = 0,
	VERT_ALIGN_APP_DCM,
	VERT_ALIGN_AUTO_DETECT,
	VERT_ALIGN_ONE_SHOT,
	VERT_ALIGN_AUTO_CONTINUOUS
}VERT_ALIGN_CMD;

typedef struct{
	uint8_t his_cnt;
	uint8_t out_range_cnt;
}vert_angle_history;

typedef struct vert_align_data{
	uint16_t num;
	float sq_sum;
	float sum;
}vert_align_data_t;

static frame_data_t *trkfdata = NULL;
static const tracking_pars_t *trkpars = NULL;
static tracking_pars2_t *trkpars2 = NULL;
#ifndef DEBUG_SIMU
static const frame_info_t* fpars = NULL;
#endif
static tracking_ctx_st *trkctx = NULL;
static alignment_data_t* align_shared_p = NULL;
#ifdef DEBUG_SIMU
static rf_gain_info_t rf_gain_value;
static rf_gain_info_t *rf_gain = &rf_gain_value;
#else
static rf_gain_info_t *rf_gain;
#endif
static uint8_t yaw_stable_cnt = 0;
static uint8_t Is_hori_align_enable = TRUE;

static vert_align_data_t vert_data;
static vert_angle_history vert_his;
static uint8_t Is_vert_align_enable = TRUE;

const float HPF_400_ShortRange_MakeUp[HPF_SR_MAKEUP_SIZE][2] =
{
		{0, -47.4}, {0.99, -35.4}, {1.98, -22.8}, {2.97, -16.4}, {3.96, -12.9}, {4.95, -10.7}, {5.94, -8.4},
		{6.93, -7.1}, {7.92, -5.6}, {8.91, -4.4}, {9.9, -3.4}, {19.8, -1}, {29.7, -0.6}, {39.6, -0.6},
		{49.5, -0.8}, {59.4, -1.4}, {69.3, -2.4}, {79.2, -3.7}, {89.1, -6.6}, {99, -8.9}
};

const float HPF_800_ShortRange_MakeUp[HPF_SR_MAKEUP_SIZE][2] =
{
		{0, -53.2}, {0.99, -40.9}, {1.98, -28.6}, {2.97, -21.9}, {3.96, -17.75}, {4.95, -15.05}, {5.94, -12.5},
		{6.93, -10.75}, {7.92, -9}, {8.91, -7.65}, {9.9, -6.4}, {19.8, -2.15}, {29.7, -1.25}, {39.6, -0.9},
		{49.5, -1}, {59.4, -1.55}, {69.3, -2.45}, {79.2, -3.7}, {89.1, -6.6}, {99, -8.9}
};

const float HPF_1600_ShortRange_MakeUp[HPF_SR_MAKEUP_SIZE][2] =
{
		{0, -58.4}, {0.99, -46.4}, {1.98, -34.4}, {2.97, -27.4}, {3.96, -22.6}, {4.95, -19.4}, {5.94, -16.6},
		{6.93, -14.4}, {7.92, -12.4}, {8.91, -10.9}, {9.9, -9.4}, {19.8, -3.3}, {29.7, -1.9}, {39.6, -1.2},
		{49.5, -1.2}, {59.4, -1.7}, {69.3, -2.5}, {79.2, -3.7}, {89.1, -6.6}, {99, -8.9}
};

const float HPF_400_LongRange_MakeUp[HPF_LR_MAKEUP_SIZE][2] =
{
		{0, -47.4}, {1.98, -35.4}, {3.96, -22.8}, {5.94, -16.4}, {7.92, -12.9}, {9.9, -10.7}, {11.88, -8.4},
		{13.86, -7.1}, {15.84, -5.6}, {17.82, -4.4}, {19.8, -3.4}, {39.6, -1}, {59.4, -0.6}, {79.2, -0.6},
		{99, -0.8}, {118.8, -1.4}, {138.6, -2.4}, {158.4, -3.7}, {178.2, -6.6}, {198, -8.9}
};

const float HPF_800_LongRange_MakeUp[HPF_LR_MAKEUP_SIZE][2] =
{
		{0, -53.2}, {1.98, -40.9}, {3.96, -28.6}, {5.94, -21.9}, {7.92, -17.75}, {9.9, -15.05}, {11.88, -12.5},
		{13.86, -10.75}, {15.84, -9}, {17.82, -7.65}, {19.8, -6.4}, {39.6, -2.15}, {59.4, -1.25}, {79.2, -0.9},
		{99, -1}, {118.8, -1.55}, {138.6, -2.45}, {158.4, -3.7}, {178.2, -6.6}, {198, -8.9}
};

const float HPF_1600_LongRange_MakeUp[HPF_LR_MAKEUP_SIZE][2] =
{
		{0, -58.4}, {1.98, -46.4}, {3.96, -34.4}, {5.94, -27.4}, {7.92, -22.6}, {9.9, -19.4}, {11.88, -16.6},
		{13.86, -14.4}, {15.84, -12.4}, {17.82, -10.9}, {19.8, -9.4}, {39.6, -3.3}, {59.4, -1.9}, {79.2, -1.2},
		{99, -1.2}, {118.8, -1.7}, {138.6, -2.5}, {158.4, -3.7}, {178.2, -6.6}, {198, -8.9}
};

const float Angle_ShortRange_MakeUp[ANGLE_MAKEUP_SIZE][2] =
{
		{-60, -33.37}, {-57, -35.65}, {-54, -35.28}, {-51, -31.46}, {-48, -27.07}, {-45, -20.16}, {-42, -20.65}, {-39, -19.29},
		{-36, -18.68}, {-33, -18.02}, {-30, -16.15}, {-27, -14.83}, {-24, -14.04}, {-21, -12.3}, {-18, -11.42}, {-15, -8.99},
		{-12, -7.94}, {-9, -7.94}, {-6, -6.89}, {-3, -6.98}, {0, -6.09}, {3, -6.97}, {6, -7.18}, {9, -7.21},
		{12, -8.57}, {15, -9.24}, {18, -11.16}, {21, -10.85}, {24, -13.46}, {27, -13.71}, {30, -14.99}, {33, -16.15},
		{36, -19.66}, {39, -20.12}, {42, -21.21}, {45, -24.46}, {48, -24.87}, {51, -29.1}, {54, -34.55}, {57, -34.93},
		{60, -37.67}
};

const float Angle_LongRange_MakeUp[ANGLE_MAKEUP_SIZE][2] =
{
		{-60, -50}, {-57, -46.75}, {-54, -46.09}, {-51, -46.93}, {-48, -40.16}, {-45, -34.83}, {-42, -29.49}, {-39, -26.27},
		{-36, -29.81}, {-33, -23.93}, {-30, -24.79}, {-27, -32.5}, {-24, -30.43}, {-21, -23.75}, {-18, -24.82}, {-15, -16.42},
		{-12, -11.73}, {-9, -6.78}, {-6, -3.86}, {-3, -3.34}, {0, 0}, {3, -1.17}, {6, -3.04}, {9, -5.39},
		{12, -12.8}, {15, -16.06}, {18, -27.42}, {21, -30.03}, {24, -28.47}, {27, -26.01}, {30, -23.62}, {33, -23.93},
		{36, -25.15}, {39, -28.19}, {42, -32.23}, {45, -37.63}, {48, -43.48}, {51, -40.94}, {54, -50}, {57, -55},
		{60, -60}
};

const float Tx_Power_MakeUp[TX_MAKEUP_SIZE][2] =
{
		{0, 0}, {1, -0.67}, {2, 0.4}, {3, 1.29}, {4, 2.27}, {5, 2.7}, {6, 3.02}, {7, 3.28},
		{8, 3.61}, {9, 3.73}, {10, 3.86}, {20, 4.46}, {50, 4.79}, {100, 4.91}, {200, 5.09}, {255, 5.1}
};

const float Rx_Power_MakeUp[RX_MAKEUP_SIZE][2] =
{
		{0, 0}, {1, -15.5}, {2, -12.5}, {3, -9.5}, {4, -7}, {5, -4.5}, {6, -2}, {7, 0.5}
};

static list_st tracking_pars =
{
  	2.5,                // vg_x (x gate)
  	4.0,                // vg_y (y gate)
  	1.5,               	// vg_v (v gate)
  	0.5,				// uw_x (x weighting)
  	1.0,				// uw_y (y weighting)
  	0.06,				// uw_vx (vx weighting)
  	1.0,				// uw_vy (vy weighting)
  	20*TRACKING_SCALE, 	// score upper_bound
  	10*TRACKING_SCALE,	// score zero level
  	100,              	// candidate
  	1*TRACKING_SCALE,  	// added score number for normal case
  	2*TRACKING_SCALE,	// added score number for special case
  	1*TRACKING_SCALE,  	// subtracted score number for normal case
  	2*TRACKING_SCALE  	// subtracted score number for special case
};

static list_st possible_pars =
{
  	3.0,             	// vg_x (x gate)
  	4.0,             	// vg_y (y gate)
  	1.5,                // vg_v (v gate)
	0.5,				// uw_x (x weighting)
  	0.8,              	// uw_y (y weighting)
  	0.02,              	// uw_vx (vx weighting)
  	1.0,              	// uw_vy (vy weighting)
  	15,              	// score upper_bound
  	10,               	// score zero level
  	100,               	// candidate
  	1,                	// added score number for normal case
  	2,                	// added score number for special case
  	1,                 	// subtracted score number for normal case
 	2					// subtracted score number for special case
};

uint8_t cluster_cnt = 0;
float tunnel_standing_num[TUNNEL_FRAME];
uint8_t tunnel_frame_cnt = 0;
uint8_t tunnel_timer = 0;

/*******************************************************************************
*   Internal Function declaration
*******************************************************************************/
void app_dcm_data_init(void *data);
//extern float calib_angle;   //Remove by Wood, in order to fix unused declaration warning

int track_lib_init(frame_data_t *fdata, const tracking_pars_t *trkp, tracking_pars2_t *trkp2, tracking_ctx_st *ctx)
{
	trkfdata = fdata;
	trkpars = trkp;
	trkpars2 = trkp2;
	trkctx = ctx;
#ifndef DEBUG_SIMU
	fpars = (const frame_info_t*)(pars_ctx_get(FRAME_PARS_ID)->info);
#endif
	trkctx->measure_angle = trkpars->info.view_angle + 35.0;
	trkctx->measure_width = trkpars->info.view_width + 3.0;
	memcpy(&trkctx->tracking_pars, &tracking_pars, sizeof(list_st));
	memcpy(&trkctx->possible_pars, &possible_pars, sizeof(list_st));
	
	memset(&vert_data, 0, sizeof(vert_align_data_t));

	return 0;
}

void app_dcm_data_init(void *data){
	if(data == NULL){
		PRINTF("ERR: app dcm shared data are NULL!\n");
		return;
	}
	else{
		PRINTF("app dcm shared data are ready!\n");
	}
	align_shared_p = (alignment_data_t *)data;
	align_shared_p->auto_hori_align_status = ALIGN_STATUS_READY;
	align_shared_p->auto_vert_align_status = ALIGN_STATUS_READY;
}

int track_lib_frame_rate_set(int rate)
{
	trkctx->frame_rate = rate;
	trkctx->frame_slot_sec = 1.0 / (float)trkctx->frame_rate;
	return 0;
}

int track_lib_measurement_get_xy(void)
{
	int idx;
	measure_st *m = NULL;
	float standing_count = 0;

	for (idx = 0; idx < trkctx->measurements_count; idx++) {
		m = &trkctx->measurements[idx];

		// field of view
		if ((ABS(m->angle) > trkctx->measure_angle) || (ABS(m->x) > trkctx->measure_width)) {
			m->score = 1; 	// discard this measurement
		} /* else {
			m->score = 0; 	// accept this measurement
		}*/
		if ((ABS(m->x) <= trkpars->info.tunnel[1]) && (m->vangle >= trkpars->info.tunnel[2]) && (m->vangle != 180) && (ABS(m->vy + trkctx->my_speed) <= 2.0)) {
			standing_count++;
		}
#if defined(DEBUG_CONSOLE_PRINTF)
		PRINTF("-  M(%d) r:%.2f x:%.2f y:%.2f a:%.2f v:%.2f vy:%.2f h:%.2f m:%.2f\n",
			idx, m->range, m->x, m->y, m->angle, m->velocity, m->vy, m->vangle, m->mag);
#endif
  	}
	tunnel_standing_num[tunnel_frame_cnt] = standing_count;
	tunnel_frame_cnt++;
	if (tunnel_frame_cnt >= TUNNEL_FRAME) {
		tunnel_frame_cnt = 0;
	}
	standing_count = 0;
	for (idx = 0; idx < TUNNEL_FRAME; idx++) {
		standing_count += tunnel_standing_num[idx];
	}
	if ((standing_count / TUNNEL_FRAME) >= trkpars->info.tunnel[3] && trkctx->my_speed >= trkpars->info.tunnel[0]) {
		trkctx->tunnel_flag = 1;
		tunnel_timer = 0;
	} else if (trkctx->tunnel_flag == 1) {
		tunnel_timer++;
		if (tunnel_timer >= (TUNNEL_FRAME / 2)) {
			trkctx->tunnel_flag = 0;
			tunnel_timer = 0;
		}
	}
	return 0;
}

int track_lib_measurement_filtering(void)
{
	int idx1, idx2, grouping, harmonic2, harmonic3;
	uint16_t m_diff;
	float a_diff/*, x_diff, v_diff, m_div*/;    //Remove x_diff, v_diff, m_div by Wood, in order to fix set but not used warning

	float dr3, y_diff, r2_diff, r3_diff, v2_diff, v3_diff;
	measure_st *m = NULL;
	measure_st *cmp = NULL;

	for (idx1 = 0; idx1 < (trkctx->measurements_count - 1); idx1++) {
		m = &trkctx->measurements[idx1];
		if (m->score == 1) {
			continue;
		}
		if (ABS(m->x) > 15) {
			m->score = 1;
			continue;
		}

		for (idx2 = (idx1 + 1); idx2 < trkctx->measurements_count; idx2++) {
			cmp = &trkctx->measurements[idx2];
			if (cmp->score == 1) {
				continue;
			}
			if (ABS(cmp->x) > 15) {
				cmp->score = 1;
				continue;
			}
			grouping = 0;
			harmonic2 = 0;
			harmonic3 = 0;
			a_diff = ABS(cmp->angle - m->angle);
//			x_diff = ABS(cmp->x - m->x);
			y_diff = ABS(cmp->y - m->y);
			r2_diff = ABS((cmp->range / 2.0) - m->range);
			dr3 = ((cmp->range / 3.0) - m->range);
			if ((y_diff >= 7.0) && (dr3 >= 0.5)) {
				break;
			}
			r3_diff = ABS(dr3);
//			v_diff = ABS(cmp->velocity - m->velocity);
			v2_diff = ABS((cmp->velocity / 2.0) - m->velocity);
			v3_diff = ABS((cmp->velocity / 3.0) - m->velocity);
			m_diff =  m->mag - cmp->mag;
//			m_div =  (float)m->mag / (float)cmp->mag;
			/*
			if ((x_diff < 1.2) && (y_diff < 2.0) && (v_diff < 0.5) && (m_div > 0.8)) {
				grouping = 1;
				m->x = (m->x + cmp->x) / 2;
				m->y = (m->y + cmp->y) / 2;
				m->velocity = (m->velocity + cmp->velocity) / 2;
			}*/
			if ((cmp->range > 2.0) && (a_diff < 5.0) && (r2_diff < 0.5) && (v2_diff < 0.3) && (m_diff > 0.0)) {
				harmonic2 = 1;
			}
			if ((cmp->range > 3.0) && (cmp->range <= 20.0) && (a_diff < 5.0) && (r3_diff < 0.5) && (v3_diff < 0.3) && (m_diff > 0.0)) {
				harmonic3 = 1;
			}
			if (grouping || harmonic2 || harmonic3) {
				cmp->score = 1;

#if defined(DEBUG_CONSOLE_PRINTF)
				PRINTF("-  M_FILTERING(%d/%d): x:%.2f/%.2f y:%.2f/%.2f r:%.2f/%.2f v:%.2f/%.2f m:%.2f/%.2f flag:%d/%d/%d\n",
					idx1, idx2, m->x, cmp->x, m->y, cmp->y, m->range, cmp->range, m->velocity, cmp->velocity, m->mag, cmp->mag, grouping, harmonic2, harmonic3);
#endif
			}
		}
    }

	return 0;
}

int track_lib_target_predict(void)
{
	int index = 0;
	int max_index = 0;
  	target_st *t = &trkctx->heap[0];

	for (index = 0; index < TARGET_HEAP_SIZE; index++) {
		t = &trkctx->heap[index];
    	if (t->score > 0) {
      		t->x += (t->vx * trkctx->frame_slot_sec);
      		t->y += (t->vy * trkctx->frame_slot_sec);
			t->updated = PREDICTED;
			if ((trkpars->info.mode == TRACKING_MODE_FCW) && (t->y <= 0)) {
        		t->score = ID_DELAY;
			}
#ifdef DEBUG_CONSOLE_PRINTF
			PRINTF("-  P(%d) s:%d d:%d x:%.2f y:%.2f vx:%.2f vy:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vx, t->vy);
#endif
    	} else if (t->score < 0) {
			t->score++;
    	}
    	if (t->score != 0) {
    		if (t->idx > max_index) {
    			max_index = t->idx;
    		}
    	}
  	}
	if (max_index < trkctx->target_max_idx) {
		trkctx->target_max_idx = max_index;
	}

	return 0;
}

sorting_st* track_lib_target_sorting(void)
{
	int index = 0;
	int inserted = 0;
	int sorting_index = 0;
	sorting_st *head = NULL;
	sorting_st *cur = NULL;
	sorting_st *pre = NULL;
	sorting_st *new = NULL;
	target_st *t = NULL;
	
	// insert next target and sorting
	for (index = 0; index <= trkctx->target_max_idx; index++) {
		t = &trkctx->heap[index];
		if (t->score <= 0)
			continue;
		inserted = 0;
		new = &trkctx->sorting[sorting_index];
		memset(new, 0, sizeof(sorting_st));
		new->idx = index;
		new->ry = t->y;
		if (sorting_index == 0) {
			// head
			head = new;
			head->prev = NULL;
			head->next = NULL;
			sorting_index++;
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
	}

	return head;
}

int track_lib_data_association(sorting_st *list)
{
	int idx, mode;
	uint8_t t_idx;
	float gx, gy, gv, ga;
	float dx, dy, dv, da, dr;
	float tv = 0.0;
	float min_value, min_ref, ref_value;
	float longest_gate;
	sorting_st *cur = NULL;
	target_st *t = NULL;
	measure_st *m = NULL;

#ifdef DEBUG_CONSOLE_PRINTF
	PRINTF("[ASSOCIATION]\n");
#endif
	for (idx = 0; idx <= trkctx->target_max_idx; idx++) {
	 	t = &trkctx->heap[idx];
		if (t->score > 0) {
			t->m_idx = 255;
			t->m_min = 1000000.0;
		}
	}	
	// mode: 0(Target), 1(Possible)
	for (mode = 0; mode <= 1; mode++) {
		for (idx = 0; idx < trkctx->measurements_count; idx++) {
			m = &trkctx->measurements[idx];
			if (m->score == 1) {
				continue;
			}
			t_idx = 255;
			min_value = 1000000.0;
			min_ref = 1000000.0;
			cur = list;
			while(cur) {
				t = &trkctx->heap[cur->idx];
				if ((mode == 0) && (t->score < TRACKING_SCALE)) {
					cur = cur->next;
					continue;
				}
				if ((mode == 1) && ((t->score <= 0) || (t->score >= TRACKING_SCALE))) {
					cur = cur->next;
					continue;
				}

				if (trkpars2->info.rcs_gate[0] >= trkpars2->info.rcs_gate[3]) {
					longest_gate = trkpars2->info.rcs_gate[0];
				} else {
					longest_gate = trkpars2->info.rcs_gate[3];
				}

				if (t->y - m->y > longest_gate) {
                    break;
				} else if (m->y - t->y > longest_gate) {
					cur = cur->next;
					continue;
				}
				dx = ABS(t->x - m->x);
				dy = ABS(t->y - m->y);
				dv = ABS(t->vy - m->vy);
				da = ABS(t->angle - m->angle);
				tv = ABS(t->vy + trkctx->my_speed);

				ga = 30.0;

				if (trkctx->my_speed < 2.78) {
				    if (ABS(t->x) <= 1.8) {
				        gx = 1.5 + ABS(t->vx);
				    } else {
				        gx = 2.5 + ABS(t->vx);
				    }
					if (tv < 2.78) {
						if (ABS(t->vx) < 0.4) {
							if ((ABS(t->x) <= 1.8) && (t->y <= 10.0)) {
								gx = 0.8;
							} else if ((t->y >= 100.0)) {
								gx = 1.0 + (t->y / 100.0);
							}
							else {
								gx = 1.2;
							}
						}
						gv = 1.2;
					} else {
						if ((t->vector_angle >= 70 && t->vector_angle <= 110) || (t->vector_angle >= 250 && t->vector_angle <= 290) || t->dyn_status == STANDING) {
							gv = 1.2;
						} else {
							gv = 3.5;
						}
					}
					if (gx > 5.0) {
						gx = 5.0;
					}
					if ((mode == 0) && (ABS(t->accy) > 3.0)) {
						gv = 5.0;
					}
				} else {
					if (t->dyn_status == HIDDEN || t->dyn_status == MOVING || t->dyn_status == ONCOMING) {
						if (t->y <= 10.0) {
							ga = 40.0;
							gx = 1.8;
						} else {
							gx = 2.0 + (t->y / 100.0) * 2;
						}
					} else {
						gx = 1.0 + (t->y / 100.0);
					}

					if (gx > 4.0) {
						gx = 4.0;
					}
					gv = 1.2;
				}

				/*
				if (t->dyn_status == HIDDEN) {
					if (tv <= 1.0) {
						gx = 1.0 + ABS(t->vx) + (t->y / 100.0);
						gv = 1.0 + ABS(t->vx);
					} else {
						gx = 5.0 + ABS(t->vx) + (t->y / 100.0);
						gv = 3.0 + ABS(t->vx);
					}
				} else {
					if (ABS(t->vx) <= 0.4 || t->dyn_status == STANDING) {
						if (t->y <= 5.0 && t->dyn_status == STOPPED) {
							ga = 40.0;
							gx = 1.8;
						} else if (t->dyn_status == MOVING || t->dyn_status == ONCOMING) {
							if (t->y <= 10.0) {
								ga = 40.0;
								gx = 1.8;
							} else {
								gx = 1.0 + (t->y / 100.0) * 2;
							}
						} else {
							gx = 1.0 + (t->y / 100.0);
						}
					} else {
						gx = 5.0 + ABS(t->vx) + (t->y / 100.0);
					}
					gv = 1.2 + ABS(t->vx);
				}

				if (gx > 6.0) {
					gx = 6.0;
				}*/

				if (t->object_type == CAR) {
					gy = trkpars2->info.rcs_gate[1];
				} else if (t->object_type == TRUCK) {
					gy = trkpars2->info.rcs_gate[0];
				} else {
					gy = trkpars2->info.rcs_gate[2];
				}
				if (trkpars2->info.rcs_gate[3] != 0 && t->dyn_status == STANDING) {
					gy = trkpars2->info.rcs_gate[3];
				}
				if (trkpars2->info.rcs_gate[4] != 0 && (t->dyn_status == STANDING || t->dyn_status == STOPPED)) {
					gx = trkpars2->info.rcs_gate[4];
				}

#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("- GATE(M:%d/T:%d) s:%d dx:%.2f dy:%.2f dv:%.2f da:%.2f gx:%.2f gy:%.2f gv:%.2f ga:%.2f vx:%.2f\n",
					idx, t->idx, t->score, dx, dy, dv, da, gx, gy, gv, ga, t->vx);
#endif
				//if (((dx < gx) && (dy < gy) && (dv < gv) && (da < ga)) || ((dx < 3.0) && (dy < 3.0) && (dv < 0.2) && (tv >= 2.78))) {
				if ((dx < 0.8) && (dy < 2.0) && (dv > 2.78 ) && trkpars2->info.rcs_gate[0] >= 6) {
					m->score = 1;
					t_idx = 255;
					break;
				}
                if ((dx < gx) && (dy < gy) && (dv < gv) && (da < ga)) {
					m->score = 1;
					dr = (dx * dx) + (dy * dy);

					/*
					if (t->y <= 10.0) {
						ref_value = 1000 - m->mag;
					} else {
						ref_value = dr;
					}*/
					ref_value = dr;

					if (dr < min_value) {
						t_idx = t->idx;
						min_value = dr;
						min_ref = ref_value;
#ifdef DEBUG_CONSOLE_PRINTF
						PRINTF("- CAND(M:%d/T:%d) s:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f mv:%.2f mr:%.2f\n",
							idx, t->idx, m->score, t->score, m->x, t->x, m->y, t->y, m->vy, t->vy, min_value, min_ref);
#endif
						if (t->m_min <= min_ref) {
							if ((dx <= 1.2) && (dy <= gy) && (dv <= 0.3) && (trkpars2->info.rcs_gate[0] >= 6)) {
								t_idx = 255;
								break;
							}
						}
					}
				}
				cur = cur->next;
			}
			if (t_idx != 255) {
				t = &trkctx->heap[t_idx];
				if (t->m_min > min_ref) {
					t->m_idx = idx;
					t->m_min = min_ref;
#ifdef DEBUG_CONSOLE_PRINTF
					PRINTF("- FOUND(M:%d/T:%d) s:%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
						idx, t->idx, t->score, m->x, t->x, m->y, t->y, m->vy, t->vy);
#endif
				}
			}
		}
	}

	return 0;
}

int track_lib_possible_grouping(sorting_st *list)
{
	float dx, dy; //dv;
	sorting_st *cur = NULL;
	sorting_st *next = NULL;
	target_st *p = NULL;
	target_st *t = NULL;

	if (trkpars2->info.rcs_gate[0] < 6) {
		return 0;
	}

	cur = list;
	while (cur) {
		p = &trkctx->heap[cur->idx];
		// possible will upgrade to target
		if ((p->score != (trkpars->info.possible_upper - 1)) || (p->m_idx == 255)) {
			cur = cur->next;
			continue;
		}
		next = list;
		while (next) {
			t = &trkctx->heap[next->idx];
			if ((t->score < TRACKING_SCALE) || (cur->idx == next->idx)) {
				next = next->next;
				continue;
			}
			dx = ABS(t->x - p->x);
			dy = ABS(t->y - p->y);
			//dv = ABS(t->vy - p->vy);
			if (dy > 10.0) {
				break;
			}
			if ((dx < 1.0) && (dy < 6.0)) {
				//if (dv < 2.0) {
				//	t->m_idx = p->m_idx;
				//}
#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("- P_GROUPING(%d/%d) s:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
					p->idx, t->idx, p->score, t->score, p->x, t->x, p->y, t->y, p->vy, t->vy);
#endif
				p->score = ID_DELAY;
			}
			next = next->next;
		}
		cur = cur->next;
	}

	return 0;
}

static int track_lib_angle_filtering(target_st *t, measure_st *m)
{
    float a, b;
    float sin_value, cos_value;

    if (trkpars->info.angle_IIR[0] > 0) {
        if ((t->y > trkpars->info.angle_IIR[2]) || ((trkctx->my_speed >= trkpars->info.angle_IIR[3]) && (t->dyn_status == MOVING || t->dyn_status == ONCOMING) && (t->y >= 20.0))) {
        	a = trkpars->info.angle_IIR[1];
           	b = 1.0 - a;
        } else {
           	a = (trkpars->info.angle_IIR[1] * (t->y / trkpars->info.angle_IIR[2]));
        	b = 1.0 - a;
        }
    } else {
        if (t->y > trkpars->info.angle_IIR[2]) {
        	a = trkpars->info.angle_IIR[1];
           	b = 1.0 - a;
        } else {
           	a = (trkpars->info.angle_IIR[1] * (t->y / trkpars->info.angle_IIR[2]));
        	b = 1.0 - a;
        }
    }

    t->km_a = t->km_a * a + m->angle * b;
    m->angle = t->km_a;
    m->rad = m->angle * DEGREE_TO_RADIAN;
    sin_value = SIN(m->rad);
    cos_value = COS(m->rad) + 0.000001;
    m->x = sin_value * m->range;
    m->y = cos_value * m->range;
    //m->vy = m->velocity / cos_value;
#ifdef DEBUG_CONSOLE_PRINTF
	PRINTF("- ANGLE_FILTER r:%.2f x:%.2f y:%.2f a:%.2f v:%.2f vy:%.2f h:%.2f m:%.2f\n",
		m->range, m->x, m->y, m->angle, m->velocity, m->vy, m->vangle, m->mag);
#endif

    return 1;
}

static int track_lib_rcs_calc(target_st *t)
{
	float hpfRangeMakeUp;
	float angle1MakeUp;
	float txPowerMakeUp, rxPowerMakeUp;
	uint8_t	object_type_check;
	measure_st *m;

	m = &trkctx->measurements[t->m_idx];

	hpfRangeMakeUp = search_rcs_makeup(HPF_MAKEUP, m);
	angle1MakeUp = search_rcs_makeup(ANGLE_MAKEUP, m);
    m->rad = 2 * m->angle * DEGREE_TO_RADIAN;
	//angle2MakeUp = 20 * ABS(SIN(2 * m->angle * DEGREE_TO_RADIAN)) * trkpars->info.rcs_level[3];
	txPowerMakeUp = search_rcs_makeup(TX_POWER, m);
	rxPowerMakeUp = search_rcs_makeup(RX_POWER, m);
	m->rcs = m->mag + 10 * log10(pow(m->range, 4)) - hpfRangeMakeUp - angle1MakeUp - txPowerMakeUp - rxPowerMakeUp;

#ifdef DEBUG_CONSOLE_PRINTF
    PRINTF("- RCS_CALC rcs:%.2f m->mag:%.2f log:%.2f hpfRangeMakeUp:%.2f angle1MakeUp:%.2f txPowerMakeUp:%.2f rxPowerMakeUp:%.2f\n",
            m->rcs, m->mag, 10 * log10(pow(m->range, 4)), hpfRangeMakeUp, angle1MakeUp, txPowerMakeUp, rxPowerMakeUp);
#endif

	if (t->measured <= 5) {
		t->rcs = t->rcs + m->rcs;
		if (t->measured == 5) {
			t->rcs = t->rcs / 5;
		}
	} else {
		t->rcs = 0.2 * m->rcs + 0.8 * t->rcs;
	}

	if (t->score <= trkctx->tracking_pars.candidate && t->measured >= 5) {
		if (t->rcs > trkpars->info.rcs_level[1]) {
			t->object_type = TRUCK;
		} else if(t->rcs >= trkpars->info.rcs_level[2] && t->rcs <= trkpars->info.rcs_level[1]) {
			t->object_type = CAR;
		} else if(t->rcs >= trkpars->info.rcs_level[3] && t->rcs < trkpars->info.rcs_level[2]) {
			t->object_type = SCOOTER;
		} else {
			t->object_type = PEDESTRIAN;
		}
	} else if (t->score > trkctx->tracking_pars.candidate) {
		if (t->rcs > trkpars->info.rcs_level[1]) {
			object_type_check = TRUCK;
		} else if(t->rcs >= trkpars->info.rcs_level[2] && t->rcs <= trkpars->info.rcs_level[1]) {
			object_type_check = CAR;
		} else if(t->rcs >= trkpars->info.rcs_level[3] && t->rcs < trkpars->info.rcs_level[2]) {
			object_type_check = SCOOTER;
		} else {
			object_type_check = PEDESTRIAN;
		}
		if (object_type_check == t->object_type) {
			t->object_type_counter = 0;
			t->object_type_temp = object_type_check;
		} else {
			if (object_type_check == t->object_type_temp) {
				t->object_type_counter++;
				if (t->object_type_counter >= trkpars->info.rcs_level[7]) {
					t->object_type = object_type_check;
					t->object_type_counter = 0;
				}
			} else {
				t->object_type_counter = 0;
				t->object_type_temp = object_type_check;
			}
		}
	}
	if(t->rcs > trkpars->info.rcs_level[4] && ABS(t->x) <= trkpars->info.rcs_level[5] && t->y <= trkpars->info.rcs_level[6] &&
	   t->dyn_status == NOISE) {
		t->dyn_status = STANDING;
	} else 	if(t->rcs <= trkpars->info.rcs_level[4] && ABS(t->x) <= trkpars->info.rcs_level[5] && t->y <= trkpars->info.rcs_level[6] &&
		t->dyn_status == STANDING) {
		t->dyn_status = NOISE;
	}
	return 0;
}

float search_rcs_makeup(uint8_t makeup_type, measure_st *m)
{
	uint8_t i;
	float *makeup_table = NULL;
	float query_value;
	float result;
	uint8_t makeup_size = 0;
	uint8_t found_flag = 0;

#ifdef DEBUG_SIMU
	rf_gain->lr_rx_gain = 6;
	rf_gain->lr_tx_gain = 240;
	rf_gain->lr_hpf = 400;
	rf_gain->sr_rx_gain = 7;
	rf_gain->sr_tx_gain = 240;
	rf_gain->sr_hpf = 800;
#endif

	if (makeup_type == HPF_MAKEUP) {
		query_value = m->range;
		if (m->vangle == 180) {
			makeup_size = HPF_SR_MAKEUP_SIZE;
            if (rf_gain->sr_hpf == 400) {
                makeup_table = (float *)HPF_400_ShortRange_MakeUp;
            } else if (rf_gain->sr_hpf == 800) {
                makeup_table = (float *)HPF_800_ShortRange_MakeUp;
            } else if (rf_gain->sr_hpf == 1600) {
                makeup_table = (float *)HPF_1600_ShortRange_MakeUp;
            }
		} else {
			makeup_size = HPF_LR_MAKEUP_SIZE;
            if (rf_gain->lr_hpf == 400) {
                makeup_table = (float *)HPF_400_LongRange_MakeUp;
            } else if (rf_gain->lr_hpf == 800) {
                makeup_table = (float *)HPF_800_LongRange_MakeUp;
            } else if (rf_gain->lr_hpf == 1600) {
                makeup_table = (float *)HPF_1600_LongRange_MakeUp;
            }
		}
	} else if (makeup_type == ANGLE_MAKEUP) {
		query_value = m->angle;
		makeup_size = ANGLE_MAKEUP_SIZE;
		if (m->vangle == 180) {
			makeup_table = (float *)Angle_ShortRange_MakeUp;
		} else {
			makeup_table = (float *)Angle_LongRange_MakeUp;
		}
	} else if (makeup_type == TX_POWER) {
		if (m->vangle == 180) {
			query_value = rf_gain->sr_tx_gain;
		} else {
			query_value = rf_gain->lr_tx_gain;
		}
		makeup_size = TX_MAKEUP_SIZE;
		makeup_table = (float *)Tx_Power_MakeUp;
	} else if (makeup_type == RX_POWER) {
		if (m->vangle == 180) {
			query_value = rf_gain->sr_rx_gain;
		} else {
			query_value = rf_gain->lr_rx_gain;
		}
		makeup_size = RX_MAKEUP_SIZE;
		makeup_table = (float *)Rx_Power_MakeUp;
	}

	if (makeup_table == NULL) {
		return 0;
	}

	for (i = 0; i < makeup_size; i++) {
		if (query_value == *(makeup_table + 2 * i)) {
			found_flag = 1;
			break;
		} else if (query_value < *(makeup_table + 2 * i)) {
			found_flag = 2;
			break;
		}
	}
	result = 0;
	if (found_flag == 1) {
		result = *(makeup_table + 2 * i + 1);
	} else if (found_flag == 2 && i != 0) {
		result = (*(makeup_table + 2 * i + 1) - *(makeup_table + 2 * (i - 1) + 1)) * (query_value - *(makeup_table + 2 * (i - 1)));
		result = (result / (*(makeup_table + 2 * i) - *(makeup_table + 2 * (i - 1)))) + *(makeup_table + 2 * (i - 1) + 1);
	}

#ifdef DEBUG_CONSOLE_PRINTF
    PRINTF("- RCS_CALC makeup_type:%d query_value:%.2f m->vangle:%.2f sr_hpf:%d lr_hpf:%d result:%.2f\n", makeup_type, query_value, m->vangle, rf_gain->sr_hpf, rf_gain->lr_hpf, result);
#endif
	return result;
}

int track_lib_alpha_filtering(sorting_st *list)
{
	int mode;
	int i, flyover_cnt;
	int p0, p1;
	float dx, dy, dv, dv_est, dv_lateral;
	float wrx, wry, wvx, wvy, way;
	float std_speed = 0.0, tv;
	float iir_a;
	target_st *t = NULL;
	target_st *near_car_target = NULL;
	measure_st *m = NULL;
	sorting_st *cur = NULL;
	float detect_near_car_distance = 0;
	uint8_t detect_near_car_idx = 255;
	float vector_delta_x;
	float vector_delta_y;

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
	
	// mode: 0(Target), 1(Possible)
	for (mode = 0; mode <= 1; mode++) {
		cur = list;
		while(cur) {
			t = &trkctx->heap[cur->idx];
			if ((mode == 0) && (t->score < TRACKING_SCALE)) {
				cur = cur->next;
				continue;
			}
			if ((mode == 1) && ((t->score <= 0) || (t->score >= TRACKING_SCALE))) {
				cur = cur->next;
				continue;
			}
			p0 = (t->measured + t->missed) % 5;
			p1 = (p0 + 4) % 5;
			if (t->m_idx == 255) {
				t->rad = ATAN2(t->x, t->y);
				t->range = t->y / COS(t->rad);
				t->angle =  t->rad * RADIAN_TO_DEGREE;
                if (mode == 0) {
                    if (t->dyn_status == MOVING || t->dyn_status == STOPPED || (t->dyn_status == STANDING && t->y >= 50)) {
                            t->score -= trkctx->tracking_pars.lose;
                    } else {
                        t->score -= (2 * trkctx->tracking_pars.lose);
                    }
                    if (ABS(t->vx) >= 1.0) {
                        t->score -= (2 * trkctx->tracking_pars.lose);
                    }
                } else if (mode == 1) {
                        t->score -= trkctx->possible_pars.lose;
                    }
                if (t->score <= 0) {
                    t->score = ID_DELAY;
                    continue;
                }
				t->xq[p0] = t->x;
				t->yq[p0] = t->y;
				t->vxq[p0] = t->vx;
				t->vyq[p0] = t->vy;
				t->missed++;
				if (t->standing_cnt > 0) {
					t->standing_cnt--;
				}
				//track_lib_rcs_calc(t);
#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("- MISSED(%d) s:%d d:%d x:%.2f y:%.2f v:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vy);
#endif
				cur = cur->next;
				continue;
			}
			m = &trkctx->measurements[t->m_idx];
			track_lib_angle_filtering(t, m);
			wrx = 0.2;
			wry = 0.2;
			wvx = 0.01;
			wvy = 0.8;
			way = 0.2;
			dv_lateral = ABS(t->xq[p1] - t->xq[p0]) / (ABS(t->yq[p1] - t->yq[p0]) + 0.00000001);
#ifdef DEBUG_CONSOLE_PRINTF
            PRINTF("- LATERAL(%d) dv_lateral:%.2f lateral_cnt:%d XP1:%.2f XP0:%.2f YP1:%.2f YP0:%.2f\n",
				t->idx, dv_lateral, t->lateral_cnt, t->xq[p1], t->xq[p0], t->yq[p1], t->yq[p0]);
#endif
			if (ABS(t->xq[p1] - t->xq[p0]) >= 1.0 && dv_lateral >= 1.732 && t->lateral_cnt < 6) {
				t->lateral_cnt ++;
			} else if (t->lateral_cnt > 0) {
				t->lateral_cnt --;
			}
			if ((trkctx->my_speed == 0.0) && (m->vy == 0.0)) {
				t->lateral_cnt = 0;
			}
			if (mode == 0) {
				if (t->lateral_cnt >= 3) {
					wrx = 0.8;
				} else {
					wrx = 0.2;
				}
				if ((trkctx->my_speed == 0.0) && (m->vy == 0.0)) {
					if ((ABS(t->vx) < 0.8) && (t->lateral_cnt < 3)) {
						wrx = 0.0;
						wry = 0.04;
					}
					if ((ABS(t->vx) > 0.8) && (t->lateral_cnt >= 3)) {
						wvx = 0.11;
					}
				}
			} else if (mode == 1) {
				if ((trkctx->my_speed == 0.0) && (ABS(t->vx) > 0.8) && (t->lateral_cnt >= 3)) {
					wvx = 0.11;
				} else {
					wvx = 0.01;
				}
				wvy = 0.5;
			}
			dx = m->x - t->x;
			dy = m->y - t->y;
			dv = m->vy - t->vy;
			dv_est = m->vy - (t->vy + (t->accy * trkctx->frame_slot_sec));
			t->y = t->y + dy * wry;
			if ((t->lateral_cnt >= 3) && (ABS(t->vx) >= 1.0)) {
			    wrx = 0.8;
			    wvy = 0.5;
			    t->x = t->x + dx * wrx;
				if ((t->vx > 0) && (t->x < t->xq[p1])) {
					t->x = t->xq[p1] + (t->vx * trkctx->frame_slot_sec * 0.5);
				} else if ((t->vx < 0) && (t->x > t->xq[p1])) {
					t->x = t->xq[p1] + (t->vx * trkctx->frame_slot_sec * 0.5);
				}
			} else {
			    t->x = t->x + dx * wrx;
		    }

			t->vx += (dx / trkctx->frame_slot_sec * wvx);
			t->vy += dv * wvy;
			t->accy += (dv_est / trkctx->frame_slot_sec) * way;
			if (mode == 0) {
				if ((trkctx->my_speed == 0.0) && (m->vy == 0.0)) {
					if (ABS(t->vx) < 0.8) {
						t->vx = 0.0;
					}
					t->vy = 0.0;
				}
				t->score += trkctx->tracking_pars.win;
				if (t->dyn_status == STANDING) {
					if (t->score > (trkpars->info.target_score[1] * TRACKING_SCALE)) {
						t->score = trkpars->info.target_score[1] * TRACKING_SCALE;
					}
				} else {
					if (t->score > (trkpars->info.target_score[3] * TRACKING_SCALE)) {
						t->score = trkpars->info.target_score[3] * TRACKING_SCALE;

						if ((t->dyn_status == FLYOVER) && (t->y <= 20.0)) {
							t->dyn_status = STANDING;
						}
					}
				}
			} else if (mode == 1) {
				t->score += trkctx->possible_pars.win;
				if (t->object_type == PEDESTRIAN) {
					if (t->score >= (trkpars->info.possible_upper + 5)) {
						// candidate target
						t->score = trkctx->tracking_pars.candidate;
					}
				} else {
					if (t->score >= trkpars->info.possible_upper) {
						// candidate target
						t->score = trkctx->tracking_pars.candidate;
					}
				}
			}
			t->rad = ATAN2(t->x, t->y);
			t->range = t->y / COS(t->rad);
			t->angle = t->rad * RADIAN_TO_DEGREE;

			if (trkpars2->info.standing_speed[0] != 0 && trkctx->my_speed <= trkpars2->info.standing_speed[0]) {
				if (ABS(t->km_a) <= trkctx->standing_speed_a0) {
					std_speed = trkpars2->info.standing_speed[1];
				} else {
					std_speed = trkpars2->info.standing_speed[2];
				}
				if ((t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER) && (t->y < 30.0)) {
					std_speed = trkpars2->info.standing_speed[2];
				}
			} else if (trkpars2->info.standing_speed[3] != 0 && trkctx->my_speed > trkpars2->info.standing_speed[3]) {
				if (ABS(t->km_a) <= trkctx->standing_speed_a0) {
					std_speed = trkpars2->info.standing_speed[4];
				} else {
					std_speed = trkpars2->info.standing_speed[5];
				}
				if ((t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER) && (t->y < 30.0)) {
					std_speed = trkpars2->info.standing_speed[5];
				}
			} else {
				if (ABS(t->km_a) <= trkctx->standing_speed_a0) {
					std_speed = trkctx->standing_speed_v0;
				} else if ((ABS(t->km_a) > trkctx->standing_speed_a0) && (ABS(t->km_a) <= trkctx->standing_speed_a1)) {
					std_speed = trkctx->standing_speed_v1;
				} else {
					std_speed = trkctx->standing_speed_v2;
				}
				if ((t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER) && (t->y < 30.0)) {
					std_speed = trkctx->standing_speed_v2;
				}
				std_speed += trkpars2->info.uds_speed_makeup[2] * KPH_TO_MS;
			}
			tv = ABS(t->vy + trkctx->my_speed);

			if (t->score >= trkctx->tracking_pars.candidate)
			{
				if (tv <= std_speed) {
					if (t->dyn_status == HIDDEN) {
						t->dyn_status = STANDING;
						t->standing_cnt = 0;
					} else if ((t->dyn_status == STANDING || t->dyn_status == STOPPED || t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER || t->dyn_status == NOISE) && (t->standing_cnt > 0)) {
						t->standing_cnt--;
					} else if ((t->dyn_status != STANDING) && (t->dyn_status != FLYOVER) && (t->dyn_status != DITCHCOVER) && (t->dyn_status != NOISE)) {
				   		t->dyn_status = STOPPED;
					}
				} else if (t->vy < trkctx->my_neg_speed) {
					if (t->dyn_status == STANDING || t->dyn_status == STOPPED || t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER || t->dyn_status == NOISE) {
						t->standing_cnt++;
						if (t->standing_cnt >= 5) {
							t->dyn_status = ONCOMING;
						}
					} else {
						t->dyn_status = ONCOMING;
					}
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
				} else {
					if (t->dyn_status == STANDING || t->dyn_status == STOPPED || t->dyn_status == FLYOVER || t->dyn_status == DITCHCOVER || t->dyn_status == NOISE) {
						t->standing_cnt++;
						if (t->standing_cnt >= 5) {
							t->dyn_status = MOVING;
						}
					} else {
						t->dyn_status = MOVING;
					}
				}
			}
			t->velocity = m->velocity;
			t->vangle = (int16_t)m->vangle;
			t->mag = m->mag;
			t->xq[p0] = t->x;
			t->yq[p0] = t->y;
			t->vxq[p0] = t->vx;
			t->vyq[p0] = t->vy;
			t->updated = MEASURED;
			t->measured++;

			// vangle process
			if (trkpars->info.vangle[0] > 0) {
				if ((((t->dyn_status == HIDDEN) && (tv <= std_speed)) || (t->dyn_status == STANDING)) && (m->vangle != 180) && (ABS(m->vangle) <= 120) && (ABS(t->x) <= trkpars->info.vangle[3]) && (ABS(trkctx->yaw_rate) <= trkpars->info.vangle[4])) {
					iir_a = (float)trkpars->info.vangle[2] / 100;
					t->va_iir = (t->va_iir * (1 - iir_a)) + (m->vangle * iir_a);
					t->vaq[t->vaq_idx % VANGLE_QUEUE_SIZE] = t->va_iir;
					t->vaq_idx++;

					if (t->y >= trkpars->info.vangle[6]) {
						flyover_cnt = 0;
						for (i = 0; i < VANGLE_QUEUE_SIZE; i++) {
							if (t->vaq[i] >= trkpars->info.vangle[5] ) {
								flyover_cnt++;
							}
						}
						if (flyover_cnt >= trkpars->info.vangle[7]) {
							t->dyn_status = FLYOVER;
							//PRINTF("Fly success: id %d x %.3f y %.3f vdist %d d %d t %d [%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\n",t->idx, t->x, t->y, trkpars->info.vangle[2], trkpars->info.vangle[1], trkpars->info.vangle[3], t->vaq[0], t->vaq[1], t->vaq[2], t->vaq[3], t->vaq[4], t->vaq[5], t->vaq[6], t->vaq[7], t->vaq[8], t->vaq[9]);
						} else {
							//PRINTF("Fly: id %d x %.3f y %.3f vdist %d d %d t %d [%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\n",t->idx, t->x, t->y, trkpars->info.vangle[2], trkpars->info.vangle[1], trkpars->info.vangle[3], t->vaq[0], t->vaq[1], t->vaq[2], t->vaq[3], t->vaq[4], t->vaq[5], t->vaq[6], t->vaq[7], t->vaq[8], t->vaq[9]);
						}
					}
					if (t->dyn_status != FLYOVER && t->init_y <= trkpars->info.vangle[9] && t->y <= trkpars->info.vangle[9]) {
						flyover_cnt = 0;
						for (i = 0; i < VANGLE_QUEUE_SIZE; i++) {
							if (t->vaq[i] <= trkpars->info.vangle[8] ) {
								flyover_cnt++;
							}
						}
						if ((flyover_cnt >= trkpars->info.vangle[10]) && (t->mag <= trkpars->info.vangle[11])) {
							t->dyn_status = DITCHCOVER;
							//PRINTF("Fly success: id %d x %.3f y %.3f vdist %d d %d t %d [%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\n",t->idx, t->x, t->y, trkpars->info.vangle[2], trkpars->info.vangle[1], trkpars->info.vangle[3], t->vaq[0], t->vaq[1], t->vaq[2], t->vaq[3], t->vaq[4], t->vaq[5], t->vaq[6], t->vaq[7], t->vaq[8], t->vaq[9]);
						} else {
							//PRINTF("Fly: id %d x %.3f y %.3f vdist %d d %d t %d [%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\n",t->idx, t->x, t->y, trkpars->info.vangle[2], trkpars->info.vangle[1], trkpars->info.vangle[3], t->vaq[0], t->vaq[1], t->vaq[2], t->vaq[3], t->vaq[4], t->vaq[5], t->vaq[6], t->vaq[7], t->vaq[8], t->vaq[9]);
						}
					}
				} else if (((t->dyn_status == HIDDEN) || (t->dyn_status == STANDING)) && (t->y < trkpars->info.vangle[2]) && (ABS(t->x) <= 6)) {
					//PRINTF("Fly: id %d x %.3f y %.3f vdist %d d %d t %d [%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f]\n",t->idx, t->x, t->y, trkpars->info.vangle[2], trkpars->info.vangle[1], trkpars->info.vangle[3], t->vaq[0], t->vaq[1], t->vaq[2], t->vaq[3], t->vaq[4], t->vaq[5], t->vaq[6], t->vaq[7], t->vaq[8], t->vaq[9]);
				}
			}
			// vector angle calculation
			if (t->measured % 10 == 0) {
				vector_delta_x = t->x - t->vector_x;
				vector_delta_y = t->y - t->vector_y;
				t->vector_x = t->x;
				t->vector_y = t->y;
				if (vector_delta_x == 0) {
					vector_delta_x = 0.000001;
				}
				t->vector_angle = ATAN2(ABS(vector_delta_y), ABS(vector_delta_x)) * RADIAN_TO_DEGREE;
				if (vector_delta_x < 0 && vector_delta_y >= 0) {
					t->vector_angle = 180 - t->vector_angle;
				} else if (vector_delta_x >= 0 && vector_delta_y < 0) {
					t->vector_angle = 360 - t->vector_angle;
				} else if (vector_delta_x < 0 && vector_delta_y < 0) {
					t->vector_angle = 180 + t->vector_angle;
				}
			}

#ifdef DEBUG
			PRINTF("- FOUND(%d) s:%d d:%d x:%.2f/%.2f y:%.2f/%.2f vy:%.2f/%.2f vx:%.2f vvx:%.2f vrx:%.2f angle:%.2f\n",
				t->idx, t->score, t->dyn_status, t->x, m->x, t->y, m->y, t->vy, m->vy, t->vx, wvx, wrx, t->km_a);
#endif
			cur = cur->next;
		}
	}

	return 0;
}

static HORI_ALIGN_CMD get_horizontal_alignment_cmd(){
	if( align_shared_p->auto_hori_align_status == ALIGN_STATUS_START ||
		align_shared_p->auto_hori_align_status == ALIGN_STATUS_PROCESS){
		Is_hori_align_enable = FALSE;
		return HORI_ALIGN_APP_DCM;
	}
	else if(trkpars2->info.auto_calib[0] == 0){
		if( Is_hori_align_enable == TRUE &&
			trkpars2->info.align_completed[0] == ALIGN_COMPLETED &&
			align_shared_p->auto_hori_detect_status == DETECT_STATUS_START &&
			trkpars2->info.auto_detect_en[0] == TRUE ){
			return HORI_ALIGN_AUTO_DETECT;
		}
		else{
			return HORI_ALIGN_NONE;
		}
	}
	else if(trkpars2->info.auto_calib[0] == 1 &&
			Is_hori_align_enable == TRUE){
		return HORI_ALIGN_ONE_SHOT;
	}
	else if(trkpars2->info.auto_calib[0] == 2){
		return HORI_ALIGN_AUTO_CONTINUOUS;
	}

	return HORI_ALIGN_NONE;
}

static void hori_alignment_strategy_for_cmd(HORI_ALIGN_CMD cmd, float align_angle){
#ifndef DEBUG_SIMU
    align_shared_p->auto_hori_mount_angle = fpars->aoa_sft[0] + align_angle;
    // hori debug mode
#if defined(DEBUG_CONSOLE_PRINTF) || defined(CTI_Z7_0)
    if( trkpars->info.tracking_dbg == 1){
        PRINTF("[hori_mount] fr:%d, asft:%.2f, align_ang=%.2f\n", trkctx->frame_num, fpars->aoa_sft[0], align_angle);
    }
#endif
#endif
    uint8_t calib_angle_query_status = 0;
    if(cmd == HORI_ALIGN_AUTO_DETECT){
        calib_angle_query_status = calib_angle_query(align_shared_p->auto_hori_mount_angle, HORI_UPPER_ANGLE);
    }
    else{
        calib_angle_query_status = calib_angle_query(trkctx->calib_angle, trkpars2->info.auto_calib[7]);
    }

    // auto_detect mode: finish if satisify one of conditions:
    // 1. calib_angle_query_status == 2
    // 2. trkctx->calib_angle_index == ANGLE_HISTORY_NUM
    if( cmd == HORI_ALIGN_AUTO_DETECT &&
        (calib_angle_query_status == 2 || trkctx->calib_angle_index == ANGLE_HISTORY_NUM )){
        uint8_t status = DETECT_STATUS_PASS;
        Is_hori_align_enable = FALSE;
        if( calib_angle_query_status == 2 ){
            status = DETECT_STATUS_FAIL;
        }

        align_shared_p->auto_hori_detect_mount_angle = align_shared_p->auto_hori_mount_angle;
        align_shared_p->auto_hori_detect_status = status;
        IPC_SEND_MSG_Z40(MSG_AUTO_HORI_DETECT, NULL, 0);
    }

    else if(cmd == HORI_ALIGN_ONE_SHOT){
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_DONE_NOT_SAVE;
        align_shared_p->auto_hori_align_mount_angle = align_shared_p->auto_hori_mount_angle;
        Is_hori_align_enable = FALSE;
    }
    else if( ( cmd == HORI_ALIGN_APP_DCM && (ABSF(align_angle) < trkpars2->info.auto_calib[7])) ||
             ( cmd == HORI_ALIGN_AUTO_CONTINUOUS && calib_angle_query_status == 1 )){
        //alignment result do not over 0.6 degree in eeprom (trkpars2->info.auto_calib[7])
        align_shared_p->auto_hori_align_mount_angle = align_shared_p->auto_hori_mount_angle;
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_DONE_NOT_SAVE;
        IPC_SEND_MSG_Z40(MSG_AUTO_HORI_ALIGN, (void *)(int32_t)(360 * 100), 0);

        if (trkpars2->info.align_result[0] != CALIB_CORRECT) {
            trkpars2->info.align_result[0] = CALIB_CORRECT;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }

        // completed
        if (trkpars2->info.align_completed[0] != ALIGN_COMPLETED) {
            trkpars2->info.align_completed[0] = ALIGN_COMPLETED;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }
    }
    // continuous mode and uds app mode
    else if( (cmd == HORI_ALIGN_AUTO_CONTINUOUS && calib_angle_query_status == 2 ) ||
             (cmd == HORI_ALIGN_APP_DCM && (ABSF(align_angle) >= trkpars2->info.auto_calib[7])) ){

        align_shared_p->auto_hori_align_mount_angle = align_shared_p->auto_hori_mount_angle;

        if ( ABSF( align_shared_p->auto_hori_mount_angle ) <= HORI_UPPER_ANGLE) {
            align_shared_p->auto_hori_align_status = ALIGN_STATUS_DONE_SAVE;
            IPC_SEND_MSG_Z40(MSG_AUTO_HORI_ALIGN, (void *)(int32_t)(align_angle * 100), 0);
            if (trkpars2->info.align_result[0] != CALIB_CORRECT) {
                trkpars2->info.align_result[0] = CALIB_CORRECT;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
            }

            // completed
            if (trkpars2->info.align_completed[0] != ALIGN_COMPLETED) {
                trkpars2->info.align_completed[0] = ALIGN_COMPLETED;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
            }
            memset((void*)trkctx->calib_angle_history, 0, sizeof(trkctx->calib_angle_history));
            trkctx->calib_angle_index = 0;

        } else {
            align_shared_p->auto_hori_align_status = ALIGN_STATUS_ERROR;

            if (trkpars2->info.align_result[0] != CALIB_AOA_ERR) {
                trkpars2->info.align_result[0] = CALIB_AOA_ERR;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
                IPC_SEND_MSG_Z40(MSG_AUTO_HORI_ALIGN, (void *)(int32_t)(360 * 100), 0);  //Need not to save angle
            }
        }
    }

    else{
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_DONE_NOT_SAVE;

        if (trkpars2->info.align_result[0] != CALIB_CORRECT) {
            trkpars2->info.align_result[0] = CALIB_CORRECT;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }
    }

}

int track_lib_auto_horizontal_alignment(sorting_st *list){
    target_st *t = NULL;
    sorting_st *cur = NULL;
    LRModel model = { 0 };
    uint8_t is_yaw_stable = FALSE;

    HORI_ALIGN_CMD cmd =  get_horizontal_alignment_cmd();
    if (cmd == HORI_ALIGN_NONE){
        return 0;
    }

    // return if yaw rate is unavailable
#ifndef DEBUG_SIMU
    if ( get_veh_two_src_filtered_yaw_rate_status() == VEH_STATUS_INVALID ) {
        if(cmd != HORI_ALIGN_AUTO_DETECT){
            align_shared_p->auto_hori_align_status = ALIGN_STATUS_YAW_ERR;

            if (trkpars2->info.align_result[0] != CALIB_YAW_RATE_ERR) {
                trkpars2->info.align_result[0] = CALIB_YAW_RATE_ERR;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
            }
        }
        return 0;
    }
#endif

    if(ABS(trkctx->yaw_rate) <= trkpars2->info.auto_calib[5]){
        yaw_stable_cnt++;
        if( cmd == HORI_ALIGN_APP_DCM || cmd == HORI_ALIGN_AUTO_CONTINUOUS ){
            is_yaw_stable = TRUE;
            yaw_stable_cnt = 1;
        }
        // ensure yaw_rate value keep in setting value(trkpars2->info.auto_calib[5]) every sampling time(trkpars2->info.calib_rule[0])
        else{
            if(yaw_stable_cnt >= trkpars2->info.calib_rule[0]){
                is_yaw_stable = TRUE;
                // limit the upperbound
                yaw_stable_cnt = trkpars2->info.calib_rule[0];
            }
        }
    }
    else{
        yaw_stable_cnt = 0;
        is_yaw_stable = FALSE;
    }

    cur = list;
    while(cur) {
        t = &trkctx->heap[cur->idx];

        // only use track
        if (t->score < TRACKING_SCALE || t->m_idx == 255) {
            cur = cur->next;
            continue;
        }
        // auto_calib[0]:   0: disable,
        //                  1: auto-detect:one-shot mode
        //                  2: continuous mode
        uint8_t total_sample = trkpars2->info.calib_rule[4];
        uint8_t oneside_sample = trkpars2->info.calib_rule[5];

        if ((t->dyn_status == STANDING) && ((t->measured % trkpars2->info.calib_rule[0]) == 0) && (t->auto_calib_counter < trkpars2->info.calib_rule[1])) {

            if ( (ABS(t->x) >= trkpars2->info.auto_calib[1]) &&
                 (ABS(t->x) <= trkpars2->info.auto_calib[2]) &&
                 (t->y >= trkpars2->info.auto_calib[3]) &&
                 (t->y <= trkpars2->info.auto_calib[4]) &&
                 is_yaw_stable == TRUE &&
                 (trkctx->my_speed >= trkpars2->info.auto_calib[6]) &&
                 (t->score >= (trkpars2->info.calib_rule[2] * TRACKING_SCALE))) {

                t->auto_calib_xq[t->auto_calib_counter] = t->x;
                t->auto_calib_yq[t->auto_calib_counter] = t->y;
                t->auto_calib_counter++;

                if ( (t->auto_calib_counter >= trkpars2->info.calib_rule[1]) &&
                     ((trkctx->auto_calib_left_num < oneside_sample && t->x < 0) || (trkctx->auto_calib_right_num < oneside_sample && t->x > 0))) {

#if defined(DEBUG_CONSOLE_PRINTF)
                    for (int i = 0; i < trkpars2->info.calib_rule[1]; i++) {
                        PRINTF("- CALIB(%d) x:%.3f y:%.3f\n", t->idx, t->auto_calib_xq[i], t->auto_calib_yq[i]);
                    }
#endif
                    linear_regression(t->auto_calib_yq, t->auto_calib_xq, trkpars2->info.calib_rule[1], &model);
                    trkctx->auto_calib_angle[trkctx->auto_calib_left_num + trkctx->auto_calib_right_num] = atanf(model.a) * 180.0f / CM_PI;

                    // hori debug mode
#if defined(DEBUG_CONSOLE_PRINTF) || defined(CTI_Z7_0)
                    if( trkpars->info.tracking_dbg == 1){
                        PRINTF("[hori_align] fr:%d, l:%d, r:%d, aoa=%.2f\n", trkctx->frame_num, trkctx->auto_calib_left_num, trkctx->auto_calib_right_num, trkctx->auto_calib_angle[trkctx->auto_calib_left_num + trkctx->auto_calib_right_num]);
                    }
#endif
#if defined(DEBUG_CONSOLE_PRINTF)
                    PRINTF("- CALIB_A(%d) l:%d r:%d a:%.3f\n", t->idx, trkctx->auto_calib_left_num, trkctx->auto_calib_right_num, trkctx->auto_calib_angle[trkctx->auto_calib_left_num + trkctx->auto_calib_right_num]);
#endif
                    if (t->x < 0) {
                        trkctx->auto_calib_left_num++;
                    }
                    else {
                        trkctx->auto_calib_right_num++;
                    }

                    if (align_shared_p->auto_hori_align_status == ALIGN_STATUS_START) {
                        align_shared_p->auto_hori_align_status = ALIGN_STATUS_PROCESS;
                    }

                    if( align_shared_p->auto_hori_align_status == ALIGN_STATUS_PROCESS ){
                        align_shared_p->auto_hori_finished_num = trkctx->auto_calib_left_num + trkctx->auto_calib_right_num;
                    }

                    if ((trkctx->auto_calib_left_num + trkctx->auto_calib_right_num) >= total_sample) {

                        trkctx->calib_angle = bias_angle_statistics(trkctx->auto_calib_angle, total_sample);

                        hori_alignment_strategy_for_cmd(cmd, trkctx->calib_angle);

                        PRINTF("- CALIB_ANGLE %.3f\n", trkctx->calib_angle);

                        trkctx->auto_calib_left_num = 0;
                        trkctx->auto_calib_right_num = 0;
                        memset((void*)trkctx->auto_calib_angle, 0, sizeof(trkctx->auto_calib_angle));
                    }
                }
            }
            else {
                t->auto_calib_counter = 0;
            }
        }
        cur = cur->next;
    }
    return 0;
}

int track_lib_rcs_evaluation(sorting_st *list){
    target_st* t;
    sorting_st* cur;
    uint8_t rcs_enable = trkpars->info.rcs_level[0];

    cur = list;
    while(cur) {
        t = trkctx->heap + cur->idx;
        // include possible and target
        if ( t->score > 0 && t->m_idx != 255) {
            if(rcs_enable == 0){
                t->rcs = 0;
                t->object_type = SCOOTER;
            }
            else{
                track_lib_rcs_calc(t);
            }
        }
        cur = cur->next;
    }
    return 0;
}

int track_lib_target_new(target_st *new)
{
	int idx;
	int rep_idx;
	int max_cnt;
	float max_range;
	target_st *t = NULL;

	rep_idx = -1;
	max_cnt = 0;
	max_range = 0;
	for (idx = 0; idx <= trkctx->target_max_idx; idx++) {
	 	t = &trkctx->heap[idx];
	 	if (t->score >= TRACKING_SCALE) {
			max_cnt++;
			if ((ABS(t->sx) > LANE_TWO_WIDTH) && (t->y > max_range)) {
				max_range = t->y;
				rep_idx = t->idx;
			}
		}
	}
	if (max_cnt >= TARGET_MAX) {
		if (rep_idx >= 0) {
			t = &trkctx->heap[rep_idx];
			t->score = ID_DELAY;
		} else {
#ifdef DEBUG_CONSOLE_PRINTF
			PRINTF("target queue is full!\n");
#endif
			new->score = ID_DELAY;
			return 1;
		}
	}
	if (new->dyn_status == STANDING) {
		new->score = trkpars->info.target_score[0] * TRACKING_SCALE;
	} else {
		new->score = trkpars->info.target_score[2] * TRACKING_SCALE;
	}
	new->updated = NEW_OBJECT;
#ifdef DEBUG_CONSOLE_PRINTF
	PRINTF("- NEW(%d) s:%d d:%d x:%.2f y:%.2f vy:%.2f vx:%.2f angle:%.2f\n", t->idx, t->score, t->dyn_status, t->x, t->y, t->vy,t->vx, t->km_a);
#endif

	return 0;
}

void track_lib_target_guardrail(sorting_st *list)
{
	sorting_st *cur = NULL;
	target_st *t = NULL;
	uint8_t cluster_buffer[100];
	uint8_t compare_buffer[5];
	uint8_t neighborPts_cnt = 0;

	trkctx->guardrail_cluster_cnt = 0;
	memset((void*)cluster_buffer, 0xFF, sizeof(cluster_buffer));
	memset((void*)compare_buffer, 0xFF, sizeof(compare_buffer));
	memset((void*)trkctx->guardrail_lr, 0, sizeof(trkctx->guardrail_lr));
	cluster_cnt = 0;
	cur = list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		t->guardrail_cluster = 0;
		t->guardrail_visit = 0;
		t->guardrail_cnt = 0;
		cur = cur->next;
	}

	if (trkctx->my_speed < trkpars->info.guardrail[0]) {
		return;
	}

	cur = list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		//if ((t->score < TRACKING_SCALE) || (t->y < 5.0) || ((t->dyn_status != STANDING) && (t->dyn_status != FLYOVER)) || (t->guardrail_visit == 1)) {
		if ((t->score < TRACKING_SCALE) || (t->y < 5.0) || (t->dyn_status != STANDING) || (t->guardrail_visit == 1)) {
			cur = cur->next;
			continue;
		}
		t->guardrail_visit = 1;
		neighborPts_cnt = regionQuery(t, list, cluster_buffer, compare_buffer);
		if (neighborPts_cnt >= MINPTS) {
			cluster_cnt++;
			expandCluster(t, list, neighborPts_cnt, cluster_buffer);
		}
		memset((void*)cluster_buffer, 0xFF, sizeof(cluster_buffer));
		memset((void*)compare_buffer, 0xFF, sizeof(compare_buffer));
		cur = cur->next;
	}
}

uint8_t regionQuery(target_st *t, sorting_st *list, uint8_t *cluster_buffer, uint8_t *compare_buffer)
{
	sorting_st *cur = NULL;
	float gx, gy, gv;
	float dx, dy, dv;
	target_st *cmp;
	uint8_t neighborPts_cnt = 0;
	uint8_t exist_flag = 0;
	uint8_t compare_idx = 0;

	cur = list;
	while (cur) {
		cmp = &trkctx->heap[cur->idx];
		if (t->idx == cmp->idx) {
			cur = cur->next;
			break;
		}
		cur = cur->next;
	}
	while (cur) {
		cmp = &trkctx->heap[cur->idx];

		gx = trkpars->info.guardrail[1];
		gy = trkpars->info.guardrail[2];
		gv = 2.0;

		dx = ABS(t->x - cmp->x);
		dy = ABS(t->y - cmp->y);
		dv = ABS(t->vy - cmp->vy);

		if (cmp->y - t->y > gy) {
            break;
		} else if (t->y - cmp->y > gy) {
			cur = cur->next;
			continue;
		}
		if ((cmp->score < TRACKING_SCALE) || (t->y < 5.0) || ((cmp->dyn_status != STANDING) && (cmp->dyn_status != FLYOVER)) || (cmp->guardrail_visit == 1)) {
			cur = cur->next;
			continue;
		}
		if ((dx < gx) && (dy < gy) && (dv < gv)) {
			exist_flag = 0;
			compare_idx = 0;
			while (compare_buffer[compare_idx] != 0xFF) {
				if (compare_buffer[compare_idx] == cmp->idx) {
					exist_flag = 1;
					break;
				}
				compare_idx++;
			}
			if (exist_flag == 0) {
				cluster_buffer[neighborPts_cnt] = cmp->idx;
				neighborPts_cnt++;
			}
		}
		cur = cur->next;
	}
	return neighborPts_cnt;
}

void expandCluster(target_st *t, sorting_st *list, uint8_t neighborPts_cnt, uint8_t *cluster_buffer)
{
	uint8_t cluster_buffer_tmp[100];
	uint8_t neighborPts_cnt_tmp;
	uint8_t i, j;
	target_st *neighborPts;
	float guardrail_xq[30];
	float guardrail_yq[30];
	uint8_t input_size;
	LRModel model = {0};

	t->guardrail_cluster = cluster_cnt;

	for (i = 0; i < neighborPts_cnt; i++) {
		neighborPts = &trkctx->heap[cluster_buffer[i]];
		neighborPts->guardrail_visit = 1;
		neighborPts_cnt_tmp = regionQuery(neighborPts, list, cluster_buffer_tmp, cluster_buffer);

		if (neighborPts_cnt_tmp >= MINPTS) {
			for (j = 0; j < neighborPts_cnt_tmp; j++) {
				cluster_buffer[neighborPts_cnt + j] = cluster_buffer_tmp[j];
			}
			neighborPts_cnt += neighborPts_cnt_tmp;
		}
        if (neighborPts->guardrail_cluster == 0) {
        	neighborPts->guardrail_cluster = cluster_cnt;
        }
	}
	if (neighborPts_cnt >= 1) {
		t->guardrail_cnt = neighborPts_cnt + 1;
		guardrail_xq[0] = t->x;
		guardrail_yq[0] = t->y;
		input_size = 0;
		//PRINTF("Guardrail id:%d cnt:%d cluster:%d\n", t->idx, t->guardrail_cnt, t->guardrail_cluster);
		for (i = 0; i < neighborPts_cnt; i++) {
			neighborPts = &trkctx->heap[cluster_buffer[i]];
			neighborPts->guardrail_cnt = neighborPts_cnt + 1;
			if ((neighborPts->y - guardrail_yq[input_size]) > 0 && (ABS((neighborPts->x - guardrail_xq[input_size])) <=2)) {//lxh old: <= 0.5)) {
				input_size++;
				guardrail_xq[input_size] = neighborPts->x;
				guardrail_yq[input_size] = neighborPts->y;
				//PRINTF("xy %.2f %.2f\n", neighborPts->x, neighborPts->y);
			}
			//PRINTF("Guardrail id:%d cnt:%d cluster:%d\n", neighborPts->idx, neighborPts->guardrail_cnt, neighborPts->guardrail_cluster);
		}

		if ((input_size + 1) >= 3 && ABS(t->x) >= 1.4 && t->y <= 50) {//lxh:old:t->y <= 30
			linear_regression(guardrail_yq, guardrail_xq, input_size + 1, &model);
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].x = t->x;
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y = t->y;
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_a = model.a;
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_b = model.b;
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_near = guardrail_yq[0];			//lxh+
			trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_far = guardrail_yq[input_size-1];
			if (trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_near <50)
				trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_near = 1;
			if (trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_far < 50)
				trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_far = 50;

#ifdef DEBUG_CONSOLE_PRINTF
			PRINTF("Lxx1 a:%.6f b:%.2f y0:%.2f yn:%.2f\n", model.a, model.b, trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_near, trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].y_far); //lxh+ end
#endif
			if (0) {//lxh-
				if (trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_a >= 0) {
					if (trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].x >= 0) {
						trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_b += 15.0;
					}
					else {
						trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_b -= 15.0;
					}
				}
				else {
					if (trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].x >= 0) {
						trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_b -= 15.0;
					}
					else {
						trkctx->guardrail_lr[trkctx->guardrail_cluster_cnt].linear_regression_b += 15.0;
					}
				}
			}//lxh- end
			trkctx->guardrail_cluster_cnt++;
			//PRINTF("Guardrail %.2f %.2f\n", model.a, model.b);
		}
	}
}

static VERT_ALIGN_CMD get_vertical_alignment_cmd(){
	static VERT_ALIGN_CMD cmd_record;
	VERT_ALIGN_CMD tmp_cmd = VERT_ALIGN_NONE;

	if( align_shared_p->auto_vert_align_status == ALIGN_STATUS_START ||
		align_shared_p->auto_vert_align_status == ALIGN_STATUS_PROCESS){
		Is_vert_align_enable = FALSE;
		tmp_cmd = VERT_ALIGN_APP_DCM;
	}

	else if(trkpars2->info.vertical_align[0] == 0){
		// auto-detect
		if( Is_vert_align_enable == TRUE &&
			trkpars2->info.align_completed[1] == ALIGN_COMPLETED &&
			align_shared_p->auto_vert_detect_status == DETECT_STATUS_START &&
			trkpars2->info.auto_detect_en[1] == TRUE ){
			tmp_cmd =  VERT_ALIGN_AUTO_DETECT;
		}
		else{
			tmp_cmd =  VERT_ALIGN_NONE;
		}
	}
	else if(trkpars2->info.vertical_align[0] == 2){
		tmp_cmd = VERT_ALIGN_AUTO_CONTINUOUS;
	}
	else if( trkpars2->info.vertical_align[0] == 1 &&
			Is_vert_align_enable == TRUE ){
		tmp_cmd = VERT_ALIGN_ONE_SHOT;
	}

	if( cmd_record != tmp_cmd){
		memset(&vert_data, 0, sizeof(vert_align_data_t));
		cmd_record = tmp_cmd;
	}

	return cmd_record;
}

static void vertical_detect_fsm(uint8_t *now, uint8_t next){
	if(*now == next){
		return;
	}
	*now = next;
	IPC_SEND_MSG_Z40(MSG_AUTO_VERT_DETECT, NULL, 0);
}

static void vert_alignment_strategy_for_cmd(VERT_ALIGN_CMD cmd){
	align_shared_p->auto_vert_phase_std = SQRTF(ABSF((vert_data.sq_sum - vert_data.sum * vert_data.sum / vert_data.num) / (vert_data.num - 1)));
	align_shared_p->auto_vert_phase = vert_data.sum / vert_data.num;
	align_shared_p->auto_vert_angle = asinf(align_shared_p->auto_vert_phase / (2 * 1.989f * 180.0f)) * RADIAN_TO_DEGREE;

	float mount_phase = align_shared_p->auto_vert_phase;
#ifndef DEBUG_SIMU
	mount_phase = (mount_phase - fpars->hsft) * (-1);
	align_shared_p->auto_vert_mount_angle = asinf(mount_phase / (2 * 1.989f * 180.0f)) * RADIAN_TO_DEGREE;

	// vert debug mode
#if defined(DEBUG_CONSOLE_PRINTF) || defined(CTI_Z7_0)
	if( trkpars->info.tracking_dbg == 1){
		PRINTF("[vert_align] fr:%d, num=%d, sum=%.2f\n", trkctx->frame_num, vert_data.num, vert_data.sum);
		PRINTF("[vert_mount] (-1)*hsft:%.2f, align_phase = %.2f\n", (-1) * fpars->hsft, align_shared_p->auto_vert_phase);
	}
#endif
#endif
	uint8_t ana_result = 0.0;
	if(cmd == VERT_ALIGN_AUTO_DETECT){
		ana_result = vert_angle_analysis( align_shared_p->auto_vert_mount_angle, VERT_UPPER_ANGLE );
	}
	else{
		ana_result = vert_angle_analysis( align_shared_p->auto_vert_angle , trkpars2->info.vertical_align[9]);
	}

	if( cmd == VERT_ALIGN_AUTO_DETECT ){
		align_shared_p->auto_vert_detect_mount_phase = mount_phase;
		if(ana_result == 1){
			vertical_detect_fsm(&align_shared_p->auto_vert_detect_status, DETECT_STATUS_PASS);
			Is_vert_align_enable = FALSE;
		}
		else if(ana_result == 2){
			vertical_detect_fsm(&align_shared_p->auto_vert_detect_status, DETECT_STATUS_FAIL);
			Is_vert_align_enable = FALSE;
		}
	}
	else if(cmd == VERT_ALIGN_ONE_SHOT){
		align_shared_p->auto_vert_align_mount_phase = mount_phase;
		align_shared_p->auto_vert_align_status = ALIGN_STATUS_DONE_NOT_SAVE;
		Is_vert_align_enable = FALSE;
	}
	else if( cmd == VERT_ALIGN_AUTO_CONTINUOUS && (vert_his.his_cnt >= trkpars2->info.vert_rule[1] || ana_result == 1)){
		align_shared_p->auto_vert_align_mount_phase = mount_phase;
        if (trkpars2->info.align_result[1] != ALIGN_STATUS_DONE_NOT_SAVE) {
            trkpars2->info.align_result[1] = ALIGN_STATUS_DONE_NOT_SAVE;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }
    	// set completed!
		if (ABSF( align_shared_p->auto_vert_mount_angle ) < VERT_UPPER_ANGLE) {
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_DONE_NOT_SAVE;
			if (trkpars2->info.align_completed[1] != ALIGN_COMPLETED) {
				trkpars2->info.align_completed[1] = ALIGN_COMPLETED;
				IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
			}
		}
	}
	// continuous mode and uds app mode
	else if( (cmd == VERT_ALIGN_AUTO_CONTINUOUS && ana_result == 2 ) ||
			 (cmd == VERT_ALIGN_APP_DCM) ){
		align_shared_p->auto_vert_align_mount_phase = mount_phase;
		if (ABSF( align_shared_p->auto_vert_mount_angle ) < VERT_UPPER_ANGLE) {
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_DONE_SAVE;
			IPC_SEND_MSG_Z40(MSG_AUTO_VERT_ALIGN, NULL, 0);

            if (trkpars2->info.align_result[1] != ALIGN_STATUS_DONE_SAVE) {
                trkpars2->info.align_result[1] = ALIGN_STATUS_DONE_SAVE;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
            }
        	// set completed!
    		if (trkpars2->info.align_completed[1] != ALIGN_COMPLETED) {
    			trkpars2->info.align_completed[1] = ALIGN_COMPLETED;
    			IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
    		}

		} else {
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_ERROR;
            IPC_SEND_MSG_Z40(MSG_AUTO_VERT_ALIGN, NULL, 0);
            if (trkpars2->info.align_result[1] != ALIGN_STATUS_ERROR) {
                trkpars2->info.align_result[1] = ALIGN_STATUS_ERROR;
                IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
            }
		}
	}
	memset(&vert_data, 0, sizeof(vert_align_data_t));
}

void track_lib_target_vertical_alignment(sorting_st *list){
	sorting_st *cur = NULL;
	target_st *t = NULL;
	measure_st* m = NULL;
	VERT_ALIGN_CMD cmd;
	cur = list;
	cmd = get_vertical_alignment_cmd();
	if ( cmd == VERT_ALIGN_NONE ){
		return;
	}

#ifndef DEBUG_SIMU
	if ( get_veh_two_src_filtered_yaw_rate_status() == VEH_STATUS_INVALID ) {
		if(cmd != VERT_ALIGN_AUTO_DETECT){
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_YAW_ERR;
			if (trkpars2->info.align_result[1] != ALIGN_STATUS_YAW_ERR) {
				trkpars2->info.align_result[1] = ALIGN_STATUS_YAW_ERR;
				IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
			}
		}
		return;
	}

	if ( get_veh_onboard_filtered_acc_z_status() == VEH_STATUS_INVALID ) {
		if(cmd != VERT_ALIGN_AUTO_DETECT){
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_ACCZ_ERR;
			if (trkpars2->info.align_result[1] != ALIGN_STATUS_ACCZ_ERR) {
				trkpars2->info.align_result[1] = ALIGN_STATUS_ACCZ_ERR;
				IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
			}
		}
		return;
	}
#endif
	if( ABSF(trkctx->yaw_rate) >= trkpars2->info.vertical_align[5] ||
		ABSF(trkctx->my_speed) <= trkpars2->info.vertical_align[6] ||
		ABSF(trkctx->acc_z - 1) >= trkpars2->info.vertical_align[8] ){
		return;
	}

	while (cur) {
		t = &trkctx->heap[cur->idx];
		if ( t->dyn_status != STANDING || t->score < TRACKING_SCALE || t->m_idx == 255 || t->guardrail_cnt < 3 ||
			 ABSF(t->x) < trkpars2->info.vertical_align[1] || ABSF(t->x) > trkpars2->info.vertical_align[2] ||
			 ABSF(t->y) < trkpars2->info.vertical_align[3] || ABSF(t->y) > trkpars2->info.vertical_align[4] ) {
			cur = cur->next;
			continue;
		}
		m = &trkctx->measurements[t->m_idx];
		float vangle_shift = m->vangle + trkpars2->info.vert_rule[0];

		if( m->vangle == 180 || ABSF(vangle_shift) > trkpars2->info.vertical_align[7]){
			cur = cur->next;
			continue;
		}
		vert_data.num ++;
		vert_data.sum += vangle_shift;
		vert_data.sq_sum += POWF( vangle_shift, 2 );

		// show on radar tool
		align_shared_p->auto_vert_finished_num = vert_data.num;

		if( cmd == VERT_ALIGN_APP_DCM && align_shared_p->auto_vert_align_status == ALIGN_STATUS_START ){
			align_shared_p->auto_vert_align_status = ALIGN_STATUS_PROCESS;
		}

		if( vert_data.num >= trkpars2->info.vert_rule[2] * VERTICAL_SAMPLE_SCALE ){
			vert_alignment_strategy_for_cmd(cmd);
			break;
		}

		cur = cur->next;
	}
	// output collection data once every frame in vert debug mode
	if( trkpars->info.tracking_dbg == 1){
		PRINTF("[vert_align] fr:%d, num=%d, sum=%.2f\n", trkctx->frame_num, vert_data.num, vert_data.sum);
	}
}

void track_lib_target_grouping(sorting_st *list)
{
	float dy, absx, absy, absvx, absvy;
	sorting_st *cur = NULL;
	sorting_st *next = NULL;
	target_st *t = NULL;
	target_st *cmp = NULL;

	cur = list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (t->score < TRACKING_SCALE) {
			cur = cur->next;
			continue;
		}
		next = cur->next;
		while (next) {
			cmp = &trkctx->heap[next->idx];
			if (cmp->score < TRACKING_SCALE) {
				next = next->next;
				continue;
			}
			dy = cmp->y - t->y;
			if (dy > 20.0) {
				break;
			}
			absx = ABS(cmp->x - t->x);
			absy = ABS(dy);
			absvx = ABS(cmp->vx - t->vx);
			absvy = ABS(cmp->vy - t->vy);
			// grouping
			if ((trkpars->info.grouping_flag == 1) &&
				((((trkctx->my_speed > trkpars->info.grouping_gate[0] && absx <= trkpars->info.grouping_gate[2]) ||
				(trkctx->my_speed > trkpars->info.grouping_gate[1] && trkctx->my_speed <= trkpars->info.grouping_gate[0] && absx <= trkpars->info.grouping_gate[3]) ||
				(trkctx->my_speed <= trkpars->info.grouping_gate[1] && absx <= trkpars->info.grouping_gate[4])) &&
				(absy <= trkpars->info.grouping_gate[5]) && (absvx <= 1.5) && (absvy <= 0.8) && (cmp->y >= 20.0 || ABS(cmp->x) <= LANE_ONE_WIDTH) &&
				(t->dyn_status == MOVING || t->dyn_status == ONCOMING) && (cmp->dyn_status == MOVING || cmp->dyn_status == ONCOMING)) ||
				((absx <= trkpars->info.grouping_gate[6]) && (absy <= trkpars->info.grouping_gate[7]) && (absvx <= 1.5) && (absvy <= 0.8) &&
				(t->dyn_status == STANDING || t->dyn_status == STOPPED) && (cmp->dyn_status == STANDING || cmp->dyn_status == STOPPED)))) {
				if (trkctx->cipv_index != 255 && (t->idx == trkctx->cipv_index || cmp->idx == trkctx->cipv_index)) {
					if (t->idx == trkctx->cipv_index) {
						cmp->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
						PRINTF("-  T_GROUPING1(%d/%d): s:%d/%d d:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
						t->idx, cmp->idx, t->score, cmp->score, t->dyn_status, cmp->dyn_status,
						t->x, cmp->x, t->y, cmp->y, t->vy, cmp->vy);
#endif
					} else {
						t->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
						PRINTF("-  T_GROUPING2(%d/%d): s:%d/%d d:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
							t->idx, cmp->idx, t->score, cmp->score, t->dyn_status, cmp->dyn_status,
							t->x, cmp->x, t->y, cmp->y, t->vy, cmp->vy);
#endif
						break;
					}
				} else {
					cmp->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
					PRINTF("-  T_GROUPING3(%d/%d): s:%d/%d d:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
						t->idx, cmp->idx, t->score, cmp->score, t->dyn_status, cmp->dyn_status,
						t->x, cmp->x, t->y, cmp->y, t->vy, cmp->vy);
#endif
				}
			} else if ((t->dyn_status != STANDING && t->dyn_status != STOPPED) && cmp->dyn_status == STANDING &&
				(absx <= 1.6) && (absy <= 3.0) && (trkctx->my_speed > 13.88)) {
				cmp->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("-  T_GROUPING4(%d/%d): s:%d/%d d:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
					t->idx, cmp->idx, t->score, cmp->score, t->dyn_status, cmp->dyn_status,
					t->x, cmp->x, t->y, cmp->y, t->vy, cmp->vy);
#endif
			} else if (t->dyn_status == STANDING && (cmp->dyn_status != STANDING && cmp->dyn_status != STOPPED) &&
				(absx <= 1.6) && (absy <= 3.0) && (trkctx->my_speed > 13.88)) {
				t->score = ID_DELAY;
#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("-  T_GROUPING5(%d/%d): s:%d/%d d:%d/%d x:%.2f/%.2f y:%.2f/%.2f v:%.2f/%.2f\n",
					t->idx, cmp->idx, t->score, cmp->score, t->dyn_status, cmp->dyn_status,
					t->x, cmp->x, t->y, cmp->y, t->vy, cmp->vy);
#endif
				break;
			}
			next = next->next;
		}
		cur = cur->next;
	}
}

static target_st* track_lib_possible_add(measure_st *m)
{
	int i, idx;
	int new_idx, old_idx, rep_idx;
	float max_range;
	target_st *t = NULL;
	target_st *new = NULL;
	
	new_idx = -1;
	old_idx = -1;
	rep_idx = -1;
	max_range = 0;
	for (idx = 0; idx < TARGET_HEAP_SIZE; idx++) {
	 	t = &trkctx->heap[idx];
		if ((t->score == 0) && (new_idx == -1)) { 
			new_idx = t->idx;
			break;
		} else if ((t->score < 0) && (old_idx == -1)) {
			old_idx = t->idx;
			break;
		} else if ((t->score > 0) && (t->score < TRACKING_SCALE)) {
			if ((ABS(t->sx) > LANE_TWO_WIDTH) && (t->y > max_range)) {
				max_range = t->y;
				rep_idx = t->idx;
			}
		}
	}
	if (new_idx >= 0) {
		new = &trkctx->heap[new_idx];
	} else if (old_idx >= 0) {
		new = &trkctx->heap[old_idx];
	} else if (rep_idx >= 0) {
		if ((ABS(m->x) <= LANE_TWO_WIDTH) || ((ABS(m->x) > LANE_TWO_WIDTH) && (m->y < max_range))) {
			new = &trkctx->heap[rep_idx];
		}
	}
	if (new) {
		idx = new->idx;
		if (idx > trkctx->target_max_idx) {
			trkctx->target_max_idx = idx;
		}
		memset(new, 0, sizeof(target_st));
		new->idx = idx;
		new->range = m->range;
		new->velocity = m->velocity;
		new->angle = m->angle;
		new->rad = m->rad;
		new->mag = m->mag;
		new->x = m->x;
		new->y = m->y;
		new->init_y = m->y;
		new->py = m->y;
		new->vy = m->vy;
		for (i = 0; i < 5; i++) {
			new->xq[i] = new->x;
			new->yq[i] = new->y;
			new->vyq[i] = new->vy;
		}
		new->km_a = m->angle;
		new->cip_acc_flag = 0;
		new->cip_aeb_flag = 0;
		new->cip_warning = 0;
		new->lateral_cnt = 0;
		new->guardrail_visit = 0;
		new->guardrail_cluster = 0;
		new->guardrail_cnt = 0;
		new->rcs = 0;
		new->object_type = OBJECT_UNKNOWN;
		new->va_iir = 0;
		new->auto_calib_counter = 0;
		new->vector_x = m->x;
		new->vector_y = m->y;
		new->vector_angle = 360;
		memset((void*)new->auto_calib_xq, 0, sizeof(new->auto_calib_xq));
		memset((void*)new->auto_calib_yq, 0, sizeof(new->auto_calib_yq));
	}

	return new;
}

int track_lib_possible_new(void)
{
	int idx = 0;
	float std_speed = 0, v = 0, tv = 0;
	measure_st *m = NULL;	
	target_st *t = NULL;

	for (idx = 0; idx < TARGET_HEAP_SIZE; idx++) {
		t = &trkctx->heap[idx];
		if ((t->score > 0) && (t->score < trkctx->possible_pars.zero_level) && ((t->measured + t->missed) >= 5)) {
			t->score = ID_DELAY;
		}
	}

	for (idx = 0; idx < trkctx->measurements_count; idx++) {
		m = &trkctx->measurements[idx];
	   	if (m->score == 0) { // new possible target
			if (trkpars2->info.standing_speed[0] != 0 && trkctx->my_speed <= trkpars2->info.standing_speed[0]) {
				if (ABS(m->angle) <= trkctx->standing_speed_a0) {
					std_speed = trkpars2->info.standing_speed[1];
				} else {
					std_speed = trkpars2->info.standing_speed[2];
				}
			} else if (trkpars2->info.standing_speed[3] != 0 && trkctx->my_speed > trkpars2->info.standing_speed[3]) {
				if (ABS(m->angle) <= trkctx->standing_speed_a0) {
					std_speed = trkpars2->info.standing_speed[4];
				} else {
					std_speed = trkpars2->info.standing_speed[5];
				}
			} else {
				if (ABS(m->angle) <= trkctx->standing_speed_a0) {
					std_speed = trkctx->standing_speed_v0;
				} else if ((ABS(m->angle) > trkctx->standing_speed_a0) && (ABS(m->angle) <= trkctx->standing_speed_a1)) {
					std_speed = trkctx->standing_speed_v1;
				} else {
					std_speed = trkctx->standing_speed_v2;
				}
				std_speed += trkpars2->info.uds_speed_makeup[2] * KPH_TO_MS;
			}
    		v = m->vy;
			tv = ABS(v + trkctx->my_speed);
			if ((tv > std_speed) || (trkctx->standing_flag == 1)) {
              	t = track_lib_possible_add(m);
          		if (!t) {
            		//PRINTF("discard a measurement %d!\n", idx);
            		continue;
          		}
          		t->score = trkctx->possible_pars.zero_level;
          		/*
          		if (tv <= std_speed) {
            		t->dyn_status = STANDING;
          		} else if (v < trkctx->my_neg_speed) {
            		t->dyn_status = ONCOMING;
          		} else {
            		t->dyn_status = MOVING;
        		}*/
#ifdef DEBUG_CONSOLE_PRINTF
				PRINTF("-  N(%d) d:%d x:%.2f y:%.2f v:%.2f\n", t->idx, t->dyn_status, t->x, t->y, t->vy);
#endif
      		}
    	}
	}
	
	return 0;
}

int track_lib_target_data_update(sorting_st *list)
{
	sorting_st *cur = NULL;
	target_st *t = NULL;
	
	cur = list;
	while (cur) {
		t = &trkctx->heap[cur->idx];
		if (t->score > 0) {
			t->sx = t->x + trkpars->info.position_shift[0];
    		t->rad = ATAN2(t->sx, t->y);
    		t->range = t->y / COS(t->rad);
    		t->angle = t->rad * RADIAN_TO_DEGREE;
		}
		cur = cur->next;
	}

	return 0;
}

void get_rf_gain(void* data)
{
	rf_gain = (rf_gain_info_t *)data;
}

float bias_angle_statistics(float* hist_ang, uint16_t hist_ang_num)
{
	float mean = 0.0f;
	float std = 0.0f;
	float sum = 0.0f;
	float avg_bias_ang = 0.0f;
	uint16_t used_num = 0;
	uint16_t idx;

	used_num = hist_ang_num;
	mean = get_mean(hist_ang, hist_ang_num);
	std = get_std(hist_ang, hist_ang_num, mean);

	for (idx = 0; idx < hist_ang_num; idx++)
	{
		if (fabsf(hist_ang[idx] - mean) > std * 1.0f)
		{
			used_num--;
		}
		else
		{
			sum += hist_ang[idx];
		}
	}

	avg_bias_ang = sum / used_num;

	return avg_bias_ang;
}

float get_std(float* vec, uint16_t num, float mean)
{
	float diff = 0.0f;
	float var_sum = 0.0;
	float std = 0.0f;
	uint16_t idx;

	for (idx = 0; idx < num; idx++)
	{
		diff = vec[idx] - mean;
		var_sum += powf(diff, 2);
	}
	var_sum = var_sum / num;
	std = sqrtf(var_sum);

	return std;
}

float get_mean(float* vec, uint16_t num)
{
	float sum = 0.0f;
	float mean = 0.0f;
	uint16_t idx;

	for (idx = 0; idx < num; idx++)
	{
		sum += vec[idx];
	}

	mean = sum / num;

	return mean;
}

void auto_calibration_handler(uint8_t op)
{
    if(1 == op)
    {//process start
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_START;
        align_shared_p->auto_vert_align_status = ALIGN_STATUS_START;
        PRINTF("Auto-align start!\n");
    }
    else if(2 == op)
    {//process timeout
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_TIMEOUT;
        align_shared_p->auto_vert_align_status = ALIGN_STATUS_TIMEOUT;
        PRINTF("Auto-align timeout!\n");

        if (trkpars2->info.align_result[0] != CALIB_TIMEOUT) {
            trkpars2->info.align_result[0] = CALIB_TIMEOUT;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }
        if (trkpars2->info.align_result[1] != ALIGN_STATUS_TIMEOUT) {
            trkpars2->info.align_result[1] = ALIGN_STATUS_TIMEOUT;
            IPC_SEND_MSG_Z40(MSG_PARAMETER_SET, (void *)TRACKING_PARS2_ID, 0);
        }
    }
    else
    {//process stop
        align_shared_p->auto_hori_align_status = ALIGN_STATUS_READY;
        align_shared_p->auto_vert_align_status = ALIGN_STATUS_READY;

        PRINTF("Auto-align stop!\n");
    }

    memset(&vert_data, 0, sizeof(vert_align_data_t));

    trkctx->auto_calib_left_num = 0;
    trkctx->auto_calib_right_num = 0;
    memset((void*)trkctx->auto_calib_angle, 0, sizeof(trkctx->auto_calib_angle));
}

int calib_angle_query(float angle, float angle_gate)
{
	int i;
	float calib_condition;
	uint8_t meet_count = 0;

	if (trkctx->calib_angle_index >= ANGLE_HISTORY_NUM) {
		for (i = 0; i < ANGLE_HISTORY_NUM - 1; i++) {
			trkctx->calib_angle_history[i] = trkctx->calib_angle_history[i + 1];
		}
		trkctx->calib_angle_history[ANGLE_HISTORY_NUM - 1] = angle;
	} else {
		trkctx->calib_angle_history[trkctx->calib_angle_index] = angle;
		trkctx->calib_angle_index++;
	}
#if defined(DEBUG_CONSOLE_PRINTF) || defined(CTI_Z7_0)
	for (i = 0; i < ANGLE_HISTORY_NUM; i++) {
		PRINTF("- CALIB_ANGLE_HISTORY %.3f\n", trkctx->calib_angle_history[i]);
	}
#endif
	if (trkctx->calib_angle_index >= trkpars2->info.calib_rule[3]) {
		if (ABS(angle) > angle_gate) {
			if (angle > angle_gate) {
				calib_condition = angle_gate;
			} else {
				calib_condition = -angle_gate;
			}
			for (i = 0; i < trkctx->calib_angle_index; i++) {
				if (calib_condition > 0 && trkctx->calib_angle_history[i] >= calib_condition) {
					meet_count++;
				} else if (calib_condition < 0 && trkctx->calib_angle_history[i] <= calib_condition) {
					meet_count++;
				}
			}
			if (meet_count >= trkpars2->info.calib_rule[3]) {
				return 2;	// calib done, save
			} else {
				return 1;	// calib done, no save
			}
		} else {
			return 1;	// calib done, no save
		}
	} else {
		return 0;	// calib not finish, no save
	}
}

uint8_t vert_angle_analysis(float angle, float angle_gate){
	vert_his.his_cnt++;

	if( ABSF( angle ) > angle_gate ){
		vert_his.out_range_cnt ++;
	}
	if( vert_his.out_range_cnt >= trkpars2->info.vert_rule[1] ){
		vert_his.his_cnt = 0;
		vert_his.out_range_cnt = 0;
		return 2;
	}
	else if( vert_his.his_cnt >= ANGLE_HISTORY_NUM ){
		vert_his.his_cnt = 0;
		vert_his.out_range_cnt = 0;
		return 1;
	}

	return 0;
}
