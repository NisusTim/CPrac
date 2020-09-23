/*
 * track_lib.h
 *
 *  Created on: 2018/08/02
 *      Author: Cubtek
 */

#ifndef __TRACK_LIB_H__
#define __TRACK_LIB_H__

#include "tracking.h"

int track_lib_init(frame_data_t *fdata, const tracking_pars_t *trkp, tracking_pars2_t *trkp2, tracking_ctx_st *ctx);
void app_dcm_data_init(void *data);
int track_lib_frame_rate_set(int rate);
int track_lib_measurement_get_xy(void);
int track_lib_measurement_filtering(void);
int track_lib_target_predict(void);
sorting_st* track_lib_target_sorting(void);
int track_lib_data_association(sorting_st *list);
int track_lib_possible_grouping(sorting_st *list);
int track_lib_alpha_filtering(sorting_st *list);
int track_lib_auto_horizontal_alignment(sorting_st *list);
int track_lib_rcs_evaluation(sorting_st *list);
int track_lib_target_new(target_st *new);
void track_lib_target_guardrail(sorting_st *list);
void track_lib_target_vertical_alignment(sorting_st *list);
void track_lib_target_grouping(sorting_st *list);
int track_lib_possible_new(void);
int track_lib_target_data_update(sorting_st *list);
uint8_t regionQuery(target_st *t, sorting_st *list, uint8_t *cluster_buffer, uint8_t *compare_buffer);
void expandCluster(target_st *t, sorting_st *list, uint8_t neighborPts_cnt, uint8_t *cluster_buffer);
float search_rcs_makeup(uint8_t makeup_type, measure_st *m);
void get_rf_gain(void* data);
float bias_angle_statistics(float* hist_ang, uint16_t hist_ang_num);
float get_std(float* vec, uint16_t num, float mean);
float get_mean(float* vec, uint16_t num);
void auto_calibration_handler(uint8_t op);
int calib_angle_query(float angle, float gate);
uint8_t vert_angle_analysis(float angle, float gate);

#endif /* __TRACK_LIB_H__ */
