/*
 * horizontal_alignment_handler.c
 *
 *  Created on: 2020/07/15
 *      Author: HUNGNUNG YANG
 */

#include "horizontal_alignment_handler.h"
#include "sys_shared.h"
#include "customer.h"
#include "can_cubtek.h"
#include "tracking.h"
#include "alignment_main.h"
#include "monitor_task.h"
#include "custom_math.h"

static void auto_hori_detect_handler(void* data);
static void horizontal_alignment_done_handler(void* data);

void horizontal_alignment_init(){
	ipc_reg_msg(MSG_AUTO_HORI_DETECT, "auto_hori_detect", (event_proc_p)auto_hori_detect_handler);
	ipc_reg_msg(MSG_AUTO_HORI_ALIGN, "auto_hori_align",(msg_proc_p)horizontal_alignment_done_handler);
}

uint8_t is_hori_detect_pass(){
	// return true if auto detection is disable
	if(get_trk2_auto_hori_detection_en() == FALSE){
		return TRUE;
	}

	uint8_t bpass = TRUE;

	uint8_t didp_h_angle = *((uint8_t*)(cubtek_faw_did_aligment_auto_detect_h_angle_get()));

	int8_t h_mount_angle = (int8_t)didp_h_angle;
	float h_gate = HORI_UPPER_ANGLE * AUTO_DETECT_HORI_SCALE;

	if( ABSF(h_mount_angle) > ABSF(h_gate) ){
		bpass = FALSE;
	}

	return bpass;
}

static void auto_hori_detect_handler(void* data){
	if(get_auto_detect_hori_status() == DETECT_STATUS_FAIL){

		cubtek_faw_did_aligment_auto_detect_h_angle_set_and_save(get_auto_hori_detect_mount_angle() * AUTO_DETECT_HORI_SCALE);

		hori_vert_detect_check();
	}
}

static void horizontal_alignment_done_handler(void* data){
	uint8_t didp_hangle = 0.0;
	if( get_hori_alignment_status() == ALIGN_STATUS_DONE_SAVE ){
		frame_set_asft(get_auto_hori_align_mount_angle());

		check_radar_alignment_result();
	}
	if( get_hori_alignment_status() == ALIGN_STATUS_DONE_SAVE ||
		get_hori_alignment_status() == ALIGN_STATUS_DONE_NOT_SAVE ){
        // save alignment result
        didp_hangle = (uint8_t)(get_auto_hori_align_mount_angle() * AUTO_ALIGN_HORI_SCALE);
        cubtek_faw_did_aligment_auto_align_h_angle_set_and_save( didp_hangle );

		// clear detection error after alignment done
		cubtek_faw_did_aligment_auto_detect_h_angle_set_and_save( 0 );
		hori_vert_detect_check();
	}
}
