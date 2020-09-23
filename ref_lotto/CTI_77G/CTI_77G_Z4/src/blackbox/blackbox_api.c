/*
 * blackbox_api.c
 *
 *  Created on: 2019/10/28
 *      Author: jacklee
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "blackbox_api.h"
#include "timer.h"
#include "sbc_fs8x.h"
#include "SWT.h"
#include "parameters.h"
#include "vehicle.h"
#include "console.h"
#include "console_cmd.h"
#include "console_api.h"



#ifdef BLACKBOX_DEBUG
#undef BLACKBOX_DEBUG
#endif
#ifndef	BLACKBOX_DEBUG
#define BLACKBOX_DEBUG		1
#endif

#if BLACKBOX_DEBUG
bool BBOX_SYNC_CONSOLE = false;
#endif

#define FRAME_DATA_OBJECT_NUM	3

typedef enum _BBoxApiState {
  BLACKBOX_API_INIT = 0,		//0
  BLACKBOX_API_READY,			//1
  BLACKBOX_API_RECORD,			//2
  BLACKBOX_API_RECORD_TO_READY,	//3
  BLACKBOX_API_EVENT,			//4
  BLACKBOX_API_EVENT_TO_READY	//5
} bbox_if_st;

void Blackbox_Init(void);
void Blackbox_Record(tracking_group_p tkg);

static void Record_Frame_Data(tracking_group_p tkg);
static void Copy_Tracking_Objects_List(frm_t *frame_data, uint8_t pick_num);
static uint8_t Select_Tracking_Objects(tracking_group_p tkg);
void Get_Vehicle_Data(frm_t *frm_data);
void Change_Blackbox_Status(bbox_if_st bbox_status);
#if BLACKBOX_DEBUG
static void Blackbox_Testing(char** args, int count);
#endif

#define BLACKBOX_PARS_ID FOURCC('b','b','o','x')

#define JSON_BBOX_PROFILE_CONFIG 	"\t\t\"profile%d\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_GEAR_MODE_ENABLE		"\t\t\"gear_mode_enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_PROFILE_SELECT			"\t\t\"profile_select\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_DBG_ENABLE				"\t\t\"dbg_enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"

typedef struct {
	uint8_t  start_speed;
	uint8_t  pause_speed;
	uint8_t  pause_continued_time;	//pause continue every ?seconds
	uint8_t  resume_speed;
	uint8_t  resume_continued_time;	//resume continue every ?seconds
	uint8_t  countdown_delta_xacc;	//unit of 10cm/s2
	uint8_t  countdown_sleep_time;
	uint8_t  every_frame_recording;
}blackbox_profile_t, *blackbox_profile_p;

typedef struct {
	uint8_t profile_select;
	uint8_t gear_mode_enable;
	blackbox_profile_t profile[4];
	uint8_t bbox_dbg;
}blackbox_info_t, *blackbox_info_p;

typedef struct {
	pars_header_t	hdr;
	blackbox_info_t  info;
}blackbox_pars_t, *blackbox_pars_p;

typedef struct _BlackBoxIf {
	BlackBox blackbox;
	BlackBox *bkackbox_p;
	bbox_if_st bbox_if_status;
	blackbox_info_p bbox_if_info;
	uint32_t frame_num;
	uint32_t curr_event_update_time;
	tracking_t bbox_targt_list[MAX_COUNT_OF_TRACKING];
	float prev_x_acc;
	float curr_x_acc;
	float prev_speed;
	float curr_speed;
	uint8_t curr_gear;
	uint8_t prev_gear;
} BlackBoxIf_t,*BlackBoxIf_p;

static BlackBoxIf_t BlackBoxIf;
blackbox_pars_t __attribute__((section(".bboxpars"))) blackbox_parameters;

const blackbox_pars_t default_blackbox_p = {
	.hdr={
		.base = (uint32_t)&blackbox_parameters,
		.version = 0x0200,
		.size = sizeof(blackbox_pars_t),
		.id=BLACKBOX_PARS_ID,
		.chksum = 0,
		.mask = 0
	},
	.info = {
		.profile_select = 0,
		.gear_mode_enable = 0,
		.bbox_dbg = 0,
		.profile = {
		{
			.start_speed = 255,
			.pause_speed = 0,
			.pause_continued_time = 1,
			.resume_speed = 255,
			.resume_continued_time = 10,
			.countdown_delta_xacc = 15,
			.countdown_sleep_time = 60,
			.every_frame_recording = 255},
		{
			.start_speed = 10,
			.pause_speed = 0,
			.pause_continued_time = 10,
			.resume_speed = 30,
			.resume_continued_time = 30,
			.countdown_delta_xacc = 25,
			.countdown_sleep_time = 60,
			.every_frame_recording = 5	},
		{
			.start_speed = 10,
			.pause_speed = 0,
			.pause_continued_time = 10,
			.resume_speed = 30,
			.resume_continued_time = 20,
			.countdown_delta_xacc = 10,
			.countdown_sleep_time = 60,
			.every_frame_recording = 16	},
		{
			.start_speed = 10,
			.pause_speed = 0,
			.pause_continued_time = 10,
			.resume_speed = 30,
			.resume_continued_time = 60,
			.countdown_delta_xacc = 49,
			.countdown_sleep_time = 60,
			.every_frame_recording = 5	}
		}
	}
};

static int blackbox_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(BLACKBOX_PARS_ID>>24),(char)(BLACKBOX_PARS_ID>>16),(char)(BLACKBOX_PARS_ID>>8),(char)(BLACKBOX_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, blackbox_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, blackbox_parameters.hdr.size  - sizeof(pars_header_t));
		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt, JSON_PROFILE_SELECT, offsetof(blackbox_info_t, profile_select), BlackBoxIf.bbox_if_info->profile_select);
		cnt += sprintf(ws+cnt, JSON_GEAR_MODE_ENABLE, offsetof(blackbox_info_t, gear_mode_enable), BlackBoxIf.bbox_if_info->gear_mode_enable);
		cnt += sprintf(ws+cnt, JSON_DBG_ENABLE, offsetof(blackbox_info_t, bbox_dbg), BlackBoxIf.bbox_if_info->bbox_dbg);
		for(uint8_t i = 0; i < 4; i++){
			cnt += sprintf(ws+cnt, JSON_BBOX_PROFILE_CONFIG, i, offsetof(blackbox_info_t, profile[i]),
					BlackBoxIf.bbox_if_info->profile[i].start_speed,
					BlackBoxIf.bbox_if_info->profile[i].pause_speed, BlackBoxIf.bbox_if_info->profile[i].pause_continued_time,
					BlackBoxIf.bbox_if_info->profile[i].resume_speed, BlackBoxIf.bbox_if_info->profile[i].resume_continued_time,
					BlackBoxIf.bbox_if_info->profile[i].countdown_delta_xacc, BlackBoxIf.bbox_if_info->profile[i].countdown_sleep_time,
					BlackBoxIf.bbox_if_info->profile[i].every_frame_recording);
		}
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

/******************************************************************************
Function Name : save TEF810x system parameters from data buffer
******************************************************************************/
static void blackbox_pars_dump(void)
{
	uint8_t i;
	PRINTF("<BlackBox> -ver:(%d) -size:(%d)\n", blackbox_parameters.hdr.version, sizeof(blackbox_pars_t));
	PRINTF("-select profile: %d\n", BlackBoxIf.bbox_if_info->profile_select);
	PRINTF("-gear_enable: %d\n", BlackBoxIf.bbox_if_info->gear_mode_enable);
	PRINTF("-dbg: %d\n", BlackBoxIf.bbox_if_info->bbox_dbg);
	for(i = 0; i < 4; i++)
	{
		PRINTF("-profile(%d): \n", i);
		PRINTF("  start_speed: %d\n", BlackBoxIf.bbox_if_info->profile[i].start_speed);
		PRINTF("  pause_speed: %d\n", BlackBoxIf.bbox_if_info->profile[i].pause_speed);
		PRINTF("  pause_continued_time: %d\n", BlackBoxIf.bbox_if_info->profile[i].pause_continued_time);
		PRINTF("  resume_speed: %d\n", BlackBoxIf.bbox_if_info->profile[i].resume_speed);
		PRINTF("  resume_continued_time: %d\n", BlackBoxIf.bbox_if_info->profile[i].resume_continued_time);
		PRINTF("  countdown_delta_xacc: %d\n", BlackBoxIf.bbox_if_info->profile[i].countdown_delta_xacc);
		PRINTF("  countdown_sleep_time: %d\n", BlackBoxIf.bbox_if_info->profile[i].countdown_sleep_time);
		PRINTF("  every_frame_recording: %d\n", BlackBoxIf.bbox_if_info->profile[i].every_frame_recording);
	}
}

/******************************************************************************
Function Name : Blackbox_Init
caution : this function initialize the blackbox modules
******************************************************************************/
void Blackbox_Init(void)
{
	uint16_t err_msg;

	BlackBoxIf.bbox_if_info = &blackbox_parameters.info;
	BlackBoxIf.bkackbox_p = &BlackBoxIf.blackbox;
	InitBlackBox(BlackBoxIf.bkackbox_p, 0);

	BlackBoxIf.curr_event_update_time = time_get();
	BlackBoxIf.frame_num = 0;

	BlackBoxIf.curr_x_acc = get_veh_onboard_filtered_acc_x_value();
	BlackBoxIf.prev_x_acc = BlackBoxIf.curr_x_acc;

	BlackBoxIf.curr_speed = get_dashboard_speed_value();
	BlackBoxIf.prev_speed = BlackBoxIf.curr_speed;

	BlackBoxIf.curr_gear = get_gear_value();
	BlackBoxIf.prev_gear = BlackBoxIf.curr_gear;

	switch (BlackBoxIf.bkackbox_p->curr_state)
	{
	case kBBoxReady:
	case kBBoxRecording:
		Change_Blackbox_Status(BLACKBOX_API_READY);
		break;
	case kBBoxCountdown:
	case kBBoxSleeping:
		Change_Blackbox_Status(BLACKBOX_API_EVENT);
		break;
	}

	memcpy((void*)&blackbox_parameters, (void*)&default_blackbox_p, sizeof(blackbox_pars_t));
	err_msg = pars_get((pars_ctx_p)&blackbox_parameters, blackbox_pars_dump, blackbox_info_in_jsons);
	if(err_msg == -1)
	{
		PRINTF("Blackbox get_pars error.\n");
	}

	#if BLACKBOX_DEBUG
	console_command_reg("bbox", Blackbox_Testing);
	#endif
}

void Blackbox_Record(tracking_group_p tkg)
{
	vuint32_t now_time = time_get();
	BlackBoxIf.frame_num++;
	BlackBoxIf.prev_speed = BlackBoxIf.curr_speed;
	BlackBoxIf.curr_speed = get_dashboard_speed_value();
	BlackBoxIf.prev_x_acc = BlackBoxIf.curr_x_acc;
	BlackBoxIf.curr_x_acc = get_veh_onboard_filtered_acc_x_value();
	BlackBoxIf.prev_gear = BlackBoxIf.curr_gear;
	BlackBoxIf.curr_gear = get_gear_value();


	#if BLACKBOX_DEBUG
	if(BlackBoxIf.bbox_if_info->bbox_dbg)
		PRINTF("BBox--XAcc_Dif %.3f, Speed: %.2f, Gear: %d, st:%d--\n",  BlackBoxIf.curr_x_acc - BlackBoxIf.prev_x_acc, BlackBoxIf.curr_speed, BlackBoxIf.curr_gear, BlackBoxIf.bbox_if_status);
	#endif

	switch (BlackBoxIf.bbox_if_status)
	{
	case BLACKBOX_API_INIT:
		Blackbox_Init();
		switch (BlackBoxIf.bkackbox_p->curr_state)
		{
		case kBBoxReady:
		case kBBoxRecording:
			BlackBoxIf.bbox_if_status = BLACKBOX_API_READY;
			break;
		case kBBoxCountdown:
		case kBBoxSleeping:
			BlackBoxIf.bbox_if_status = BLACKBOX_API_EVENT;
			break;
		}
		break;
	case BLACKBOX_API_READY:
		if(BlackBoxIf.curr_speed > BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].start_speed
			|| (BlackBoxIf.curr_gear == VEH_GEAR_D && BlackBoxIf.bbox_if_info->gear_mode_enable))
		{
			Change_Blackbox_Status(BLACKBOX_API_RECORD);
		}
		break;
	case BLACKBOX_API_RECORD:
		if ((BlackBoxIf.curr_x_acc - BlackBoxIf.prev_x_acc) > BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_delta_xacc * 10
			|| (BlackBoxIf.curr_x_acc - BlackBoxIf.prev_x_acc) < -(BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_delta_xacc * 10))
		{
			Change_Blackbox_Status(BLACKBOX_API_EVENT);
			BlackBoxIf.bkackbox_p->Countdown(BlackBoxIf.bkackbox_p, BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_sleep_time); //API_Countdown 10s
		}
		if ((BlackBoxIf.bbox_if_info->gear_mode_enable == 0 &&
			 BlackBoxIf.curr_speed == BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].pause_speed &&
			 BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].pause_continued_time != 0)
			|| (BlackBoxIf.bbox_if_info->gear_mode_enable == 1 && (BlackBoxIf.curr_gear == VEH_GEAR_P || BlackBoxIf.curr_gear == VEH_GEAR_N )))
		{
			Change_Blackbox_Status(BLACKBOX_API_RECORD_TO_READY);
		}		
		Record_Frame_Data(tkg);
		break;
	case BLACKBOX_API_RECORD_TO_READY:
		if ((BlackBoxIf.curr_x_acc - BlackBoxIf.prev_x_acc) > BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_delta_xacc * 10
			|| (BlackBoxIf.curr_x_acc - BlackBoxIf.prev_x_acc) < -(BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_delta_xacc * 10))
		{
			Change_Blackbox_Status(BLACKBOX_API_EVENT);
			BlackBoxIf.bkackbox_p->Countdown(BlackBoxIf.bkackbox_p, BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].countdown_sleep_time); //API_Countdown 10s
		}
		if(BlackBoxIf.curr_speed > BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].start_speed)
		{
			Change_Blackbox_Status(BLACKBOX_API_RECORD);
		}
		if((now_time-BlackBoxIf.curr_event_update_time) * 4.17 >= (BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].pause_continued_time * 1000)
				|| (BlackBoxIf.curr_gear == VEH_GEAR_P && BlackBoxIf.bbox_if_info->gear_mode_enable))
		{
			Change_Blackbox_Status(BLACKBOX_API_READY);
		}
		Record_Frame_Data(tkg);
		break;
	case BLACKBOX_API_EVENT:
		if(BlackBoxIf.curr_speed > BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].resume_speed
				&& BlackBoxIf.bkackbox_p->curr_state == kBBoxSleeping)
		{
			Change_Blackbox_Status(BLACKBOX_API_EVENT_TO_READY);
		}
		Record_Frame_Data(tkg);
		break;
	case BLACKBOX_API_EVENT_TO_READY:
		if(BlackBoxIf.curr_speed < BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].resume_speed)
		{
			Change_Blackbox_Status(BLACKBOX_API_EVENT);
		}
		if((now_time-BlackBoxIf.curr_event_update_time) * 4.17 >= (BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].resume_continued_time * 1000)
				&& BlackBoxIf.bkackbox_p->curr_state == kBBoxSleeping)
		{
			Change_Blackbox_Status(BLACKBOX_API_READY);
			BlackBoxIf.bkackbox_p->ResetCountdown(BlackBoxIf.bkackbox_p);
		}
		break;
	default:
		break;
	}
}

static void Record_Frame_Data(tracking_group_p tkg)
{
	page_t *page_buff = (page_t *)&BlackBoxIf.blackbox.page_buff;
	frm_t *frame_data = (frm_t *)page_buff->reserved;
	uint8_t pick_num;

	switch(BlackBoxIf.bkackbox_p->curr_state)
		{
		case kBBoxSleeping:
			return;
			break;
		}

	pick_num = Select_Tracking_Objects(tkg);

	if(BlackBoxIf.frame_num % BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].every_frame_recording == 0)
	{
		Get_Vehicle_Data(frame_data);
#if BLACKBOX_DEBUG
		if(BlackBoxIf.bbox_if_info->bbox_dbg && BlackBoxIf.bkackbox_p->curr_state != kBBoxBusyErasing)
		{
			PRINTF("BBox:F_Data(%d-%d)\n", pick_num, tkg->tcnt);
			PRINTF("ACC x:%.2f y:%.2f z:%.2f\n", BlackBoxIf.curr_x_acc, get_veh_onboard_filtered_acc_y_value(), get_veh_onboard_filtered_acc_z_value());
			PRINTF("Speed:%03d, ", frame_data->speed);
			PRINTF("Yaw:%03d, ", frame_data->yaw_rate);
			PRINTF("Gear:%03d, Turn:%03d\n", frame_data->gear_turn.B.gear, frame_data->gear_turn.B.turn);
      BBOX_SYNC_CONSOLE = true;
		}
#endif
		Copy_Tracking_Objects_List(frame_data, pick_num);
		BlackBoxIf.bbox_targt_list[0].cip = 0;		//reset_targt_cip flags.
	}
#if BLACKBOX_DEBUG
  else
    BBOX_SYNC_CONSOLE = false;
#endif
}

static uint8_t Select_Tracking_Objects(tracking_group_p tkg)
{
	uint8_t pick_num = FRAME_DATA_OBJECT_NUM;
	uint8_t is_find_cip = 0;
	uint8_t i;

	for(i = 0; i < MAX_COUNT_OF_TRACKING; i++)
	{
		if(tkg->targets[i].cip == 1)
		{
			BlackBoxIf.bbox_targt_list[0] = tkg->targets[i];
			is_find_cip = 1;
			break;
		}
	}

	if (tkg->tcnt > FRAME_DATA_OBJECT_NUM)
		pick_num = FRAME_DATA_OBJECT_NUM;
	else
		pick_num = tkg->tcnt;

	if(BlackBoxIf.frame_num % BlackBoxIf.bbox_if_info->profile[BlackBoxIf.bbox_if_info->profile_select].every_frame_recording == 0)
	{
		if(is_find_cip == 1)
		{
			memcpy(&BlackBoxIf.bbox_targt_list[1], &tkg->targets[1], sizeof(tracking_t) * (pick_num - 1));
		}
		else
		{
			if(BlackBoxIf.bbox_targt_list[0].cip == 1)
			{
					memcpy(&BlackBoxIf.bbox_targt_list[1], &tkg->targets[0], sizeof(tracking_t) * (pick_num - 1));
			}
			else
			{
					memcpy(&BlackBoxIf.bbox_targt_list[0], &tkg->targets[0], sizeof(tracking_t) * (pick_num));
			}
		}
	}

	return pick_num;
}

static void Copy_Tracking_Objects_List(frm_t *frame_data, uint8_t pick_num)
{
	uint8_t i, j;
	uint8_t pick_time;
	uint32_t *p = (uint32_t *)&BlackBoxIf.blackbox.page_buff;

	pick_time = (pick_num + (FRAME_DATA_OBJECT_NUM - 1)) /  FRAME_DATA_OBJECT_NUM;

	if(pick_num == 0)
		pick_time = 1;

	for (i = 0; i < pick_time; i++)
	{
		for (j = 0; j < FRAME_DATA_OBJECT_NUM; j++)
		{
			if (i * FRAME_DATA_OBJECT_NUM + j >= pick_num)
			{
				memset(&frame_data->objects[j], 0, sizeof(obj_t));
			}
			else
			{
				frame_data->objects[j].vel_x = (int16_t)BlackBoxIf.bbox_targt_list[j].vx;
				frame_data->objects[j].vel_y = (int16_t)BlackBoxIf.bbox_targt_list[j].vy;
				frame_data->objects[j].x = (int16_t)BlackBoxIf.bbox_targt_list[j].rx;
				frame_data->objects[j].y = (int16_t)BlackBoxIf.bbox_targt_list[j].ry;
				frame_data->objects[j].state = (uint8_t)BlackBoxIf.bbox_targt_list[j].status;
			}

			#if BLACKBOX_DEBUG
			if(BlackBoxIf.bbox_if_info->bbox_dbg && BlackBoxIf.bkackbox_p->curr_state != kBBoxBusyErasing && j < pick_num)
			{
				#ifdef ENABLE_SWT
				clear_SWT0_counter();
				#endif
				fs8x_wd_handle(fs8xNormal);

				PRINTF("%02d rX:%d, rY:%d, vX:%d, vY:%d, state:%d\n", i*FRAME_DATA_OBJECT_NUM +j, frame_data->objects[j].x, frame_data->objects[j].y,
						frame_data->objects[j].vel_x, frame_data->objects[j].vel_y, frame_data->objects[j].state);
				PRINTF("bbox_api: %02d rX:%d, rY:%d, vX:%d, vY:%d, state:%d\n",
				       i*FRAME_DATA_OBJECT_NUM +j,
				       (int16_t)(BlackBoxIf.bbox_targt_list[j].rx * 8.0),
				       (int16_t)((BlackBoxIf.bbox_targt_list[j].ry + 128.0) * 8.0),
				       (int16_t)((BlackBoxIf.bbox_targt_list[j].vx + 102.0) * 20.0),
				       (int16_t)((BlackBoxIf.bbox_targt_list[j].vy + 102.0) * 20.0),
				       (uint8_t)(BlackBoxIf.bbox_targt_list[j].status));
			}
			#endif
		}		

		#if BLACKBOX_DEBUG
		if(BlackBoxIf.bbox_if_info->bbox_dbg)
		{
			PRINTF("%08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX--%02d,%ld\n",
			        p[0] & 0x00FFFFFF, p[1], p[2], p[3], p[4], p[5], p[6], p[7] & 0xFFFF0000,
					BlackBoxIf.bkackbox_p->curr_state, BlackBoxIf.frame_num);
		}		
		#endif

		if(i == 0)
			BlackBoxIf.bkackbox_p->Record(BlackBoxIf.bkackbox_p, 1, kFrame);
		else
			BlackBoxIf.bkackbox_p->Record(BlackBoxIf.bkackbox_p, 0, kFrame);
	}
}

void Get_Vehicle_Data(frm_t *frm_data)
{
	frm_data->speed = (uint16_t)BlackBoxIf.curr_speed;
	frm_data->yaw_rate = get_veh_onboard_filtered_yaw_rate_value();
	frm_data->gear_turn.B.gear = (uint8_t)BlackBoxIf.curr_gear;
	frm_data->gear_turn.B.turn = (uint8_t)get_turn_indicator_value();
}

void Change_Blackbox_Status(bbox_if_st bbox_status)
{
	BlackBoxIf.curr_event_update_time = time_get();
	BlackBoxIf.bbox_if_status = bbox_status;
}

#if BLACKBOX_DEBUG
static void Blackbox_Testing(char** args, int count)
{
	if (count > 2)
	{
		if(!strcmp(args[1], "dbg"))
		{
			uint8_t temp;
			temp = (uint8_t)atoi(args[2]);

			if(temp >= 0 || temp <= 1)
			{
				BlackBoxIf.bbox_if_info->bbox_dbg = temp;
				PRINTF("dbg = %d\n", BlackBoxIf.bbox_if_info->bbox_dbg);
			}
			else
				PRINTF("dbg must between 0~1\n");
		}
		if(!strcmp(args[1], "select"))
		{
			uint8_t profile_temp;
			profile_temp = (uint8_t)atoi(args[2]);

			if(profile_temp >= 0 || profile_temp <= 3)
			{
				BlackBoxIf.bbox_if_info->profile_select = profile_temp;
				PRINTF("select profile = %d\n", BlackBoxIf.bbox_if_info->profile_select);
			}
			else
				PRINTF("select profile must between 0~3\n");
		}
		if(!strcmp(args[1], "gear"))
		{
			uint8_t temp;
			temp = (int8_t)atoi(args[2]);

			if(temp >= 0 || temp <= 1)
			{
				BlackBoxIf.bbox_if_info->gear_mode_enable = temp;
				PRINTF("gear enable = %d\n", BlackBoxIf.bbox_if_info->gear_mode_enable);
			}
			else
				PRINTF("gear enable must between 0~1\n");
		}
		if(!strcmp(args[1], "profile"))
		{
			int8_t profile_temp;
			uint16_t data_temp;
			profile_temp = (uint8_t)atoi(args[2]);
			if(profile_temp >= 0 || profile_temp <= 3)
			{
				for(uint8_t i = 3; i < count; i++)
				{
					data_temp = (uint16_t)atoi(args[i]);
					switch(i)
					{
					case 3:
						BlackBoxIf.bbox_if_info->profile[profile_temp].start_speed = (uint8_t)data_temp;
						break;
					case 4:
						BlackBoxIf.bbox_if_info->profile[profile_temp].pause_speed = (uint8_t)data_temp;
						break;
					case 5:
						BlackBoxIf.bbox_if_info->profile[profile_temp].pause_continued_time = (uint8_t)data_temp;
						break;
					case 6:
						BlackBoxIf.bbox_if_info->profile[profile_temp].resume_speed = (uint8_t)data_temp;
						break;
					case 7:
						BlackBoxIf.bbox_if_info->profile[profile_temp].resume_continued_time = (uint8_t)data_temp;
						break;
					case 8:
						BlackBoxIf.bbox_if_info->profile[profile_temp].countdown_delta_xacc = (uint8_t)data_temp;
						break;
					case 9:
						BlackBoxIf.bbox_if_info->profile[profile_temp].countdown_sleep_time = (uint8_t)data_temp;
						break;
					case 10:
						BlackBoxIf.bbox_if_info->profile[profile_temp].every_frame_recording = (uint8_t)data_temp;
						break;
					default:
						break;
					}
				}
				PRINTF("-profile(%d): \n", profile_temp);
				PRINTF("  start_speed: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].start_speed);
				PRINTF("  pause_speed: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].pause_speed);
				PRINTF("  pause_continued_time: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].pause_continued_time);
				PRINTF("  resume_speed: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].resume_speed);
				PRINTF("  resume_continued_time: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].resume_continued_time);
				PRINTF("  countdown_delta_xacc: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].countdown_delta_xacc);
				PRINTF("  countdown_sleep_time: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].countdown_sleep_time);
				PRINTF("  every_frame_recording: %d\n", BlackBoxIf.bbox_if_info->profile[profile_temp].every_frame_recording);
			}
			else
				PRINTF("profile select must between 0~3\n");
		}
	}
	else if (count > 1)
	{
		if(!strcmp(args[1], "info"))
			blackbox_pars_dump();
		else if(!strcmp(args[1], "save"))
			pars_set((pars_ctx_p)&blackbox_parameters);
	}
	else
	{
		PRINTF("\n---Blackbox API---\n");
		PRINTF("info	BBox information\n");
		PRINTF("dbg     [0/1] Debug enable\n");
		PRINTF("gear    [0/1] Gear mode enable\n");
		PRINTF("select  [0-3] Select profile num\n");
		PRINTF("profile [0-3, start_speed, pause_speed, pause_continued_time\n");
		PRINTF("\t\t resume_speed, resume_continued_time\n");
		PRINTF("\t\t countdown_delta_xacc, countdown_sleep_time\n");
		PRINTF("\t\t every_frame_recording] Set profile\n");
	}
}
#endif

