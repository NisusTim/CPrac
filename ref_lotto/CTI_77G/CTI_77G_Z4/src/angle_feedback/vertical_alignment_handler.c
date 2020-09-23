/*
 * vertical_alignment_handler.c
 *
 *  Created on: 2020/7/21
 *      Author: HUNGNUNG YANG
 */
#include "vertical_alignment_handler.h"
#include "sys_shared.h"
#include "customer.h"
#include "can_cubtek.h"
#include "tracking.h"
#include "alignment_main.h"
#include "monitor_task.h"
#include "frame.h"
#include "custom_math.h"

static void auto_detect_vert_handler(void* data);
static void vertical_alignment_done_handler(void* data);

void vertical_alignment_init(){
	ipc_reg_msg(MSG_AUTO_VERT_DETECT, "auto_detect_vert", (event_proc_p)auto_detect_vert_handler);
    ipc_reg_msg(MSG_AUTO_VERT_ALIGN, "vert_align", (msg_proc_p)vertical_alignment_done_handler);
}

uint8_t is_vert_detect_pass(){
	// return true if auto detection is disable
	if(get_trk2_auto_vert_detection_en() == FALSE){
		return TRUE;
	}

	uint8_t bpass = TRUE;

	uint8_t didp_v_angle = *((uint8_t*)(cubtek_faw_did_aligment_auto_detect_v_angle_get()));

	int8_t v_mount_angle = (int8_t)didp_v_angle;
	float v_gate = VERT_UPPER_ANGLE * AUTO_DETECT_VERT_SCALE;

	if( ABSF(v_mount_angle) > ABSF(v_gate) ){
		bpass = FALSE;
	}

	return bpass;
}

static void auto_detect_vert_handler(void* data){
	if( get_auto_detect_vert_status() == DETECT_STATUS_FAIL){
		cubtek_faw_did_aligment_auto_detect_v_angle_set_and_save( get_auto_vert_detect_mount_angle() * AUTO_DETECT_VERT_SCALE);

		hori_vert_detect_check();
	}
}

static void vertical_alignment_done_handler(void* data){
	uint8_t didp_vangle = 0.0;
	if( get_vert_alignment_status() == ALIGN_STATUS_DONE_SAVE ){
		frame_set_hsft(get_auto_vert_align_mount_phase(), 1);

		check_radar_alignment_result();
	}

	if( get_vert_alignment_status() == ALIGN_STATUS_DONE_SAVE ||
		get_vert_alignment_status() == ALIGN_STATUS_DONE_NOT_SAVE ){
        // save alignment result
        didp_vangle = (uint8_t)(get_auto_vert_align_mount_angle() * AUTO_ALIGN_VERT_SCALE);
        cubtek_faw_did_aligment_auto_align_v_angle_set_and_save( didp_vangle );

		// clear detection error after alignment done
		cubtek_faw_did_aligment_auto_detect_v_angle_set_and_save( 0 );
		hori_vert_detect_check();
	}
}
