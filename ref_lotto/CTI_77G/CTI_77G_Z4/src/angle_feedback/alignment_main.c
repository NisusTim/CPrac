/*
 * alignment.c
 *
 *  Created on: 2020/7/23
 *      Author: HUNGNUNG YANG
 */

#include "custom_math.h"
#include "can_cubtek.h"
#include "sys_shared.h"
#include "alignment_main.h"
#include "horizontal_alignment_handler.h"
#include "vertical_alignment_handler.h"

alignment_data_t 	__attribute__((section(".align_data"))) align_data;

void alignment_init(){
	memset(&align_data, 0, sizeof(alignment_data_t));
	IPC_SEND_MSG_Z70(MSG_APP_DCM_DATA, (void*)&align_data, 0);

	// initialize status
	set_auto_detect_hori_status(DETECT_STATUS_READY);
	set_auto_detect_vert_status(DETECT_STATUS_READY);

	horizontal_alignment_init();
	vertical_alignment_init();

	if(hori_vert_detect_check() == TRUE && is_enable_auto_detect_by_cus() == AD_ENABLE){
		set_auto_detect_hori_status(DETECT_STATUS_START);
		set_auto_detect_vert_status(DETECT_STATUS_START);
	}
}

uint8_t hori_vert_detect_check(){

	uint8_t is_hori_pass = is_hori_detect_pass();
	uint8_t is_vert_pass = is_vert_detect_pass();

	if(is_hori_pass == TRUE && is_vert_pass== TRUE){
		set_monitoring_result_by_id(MONITOR_ID_RADAR_MOUNT_POSITION_SHIFT, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
		return TRUE;
	}
	else{
		set_monitoring_result_by_id(MONITOR_ID_RADAR_MOUNT_POSITION_SHIFT, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
		return FALSE;
	}
}

uint8_t get_hori_alignment_status(){
	return align_data.auto_hori_align_status;
}

uint8_t get_hori_finished_num(){
	return align_data.auto_hori_finished_num;
}

uint8_t get_vert_alignment_status(){
	return align_data.auto_vert_align_status;
}

uint16_t get_vert_finished_num(){
	return align_data.auto_vert_finished_num;
}

void clear_hori_finished_num(){
	align_data.auto_hori_finished_num = 0;
}

void clear_vert_finished_num(){
	align_data.auto_vert_finished_num = 0;
}

void set_auto_detect_hori_status(uint8_t status){
	align_data.auto_hori_detect_status = status;
}

void set_auto_detect_vert_status(uint8_t status){
	align_data.auto_vert_detect_status = status;
}

uint8_t get_auto_detect_hori_status(void){
	return align_data.auto_hori_detect_status;
}

uint8_t get_auto_detect_vert_status(void){
	return align_data.auto_vert_detect_status;
}

float get_auto_hori_mount_angle(void){
	return align_data.auto_hori_mount_angle;
}

float get_auto_hori_align_mount_angle(void){
	return align_data.auto_hori_align_mount_angle;
}

float get_auto_hori_detect_mount_angle(void){
	return align_data.auto_hori_detect_mount_angle;
}

float get_auto_vert_align_mount_phase(void){
	return align_data.auto_vert_align_mount_phase;
}

float get_auto_vert_align_mount_angle(void){
	return asinf(align_data.auto_vert_align_mount_phase / (2 * 1.989f * 180.0f)) * RADIAN_TO_DEGREE;;
}

float get_auto_vert_angle(void){
	return align_data.auto_vert_angle;
}

float get_auto_vert_mount_angle(void){
	return align_data.auto_vert_mount_angle;
}

float get_auto_vert_detect_mount_angle(void){
	return asinf(align_data.auto_vert_detect_mount_phase / (2 * 1.989f * 180.0f)) * RADIAN_TO_DEGREE;
}
