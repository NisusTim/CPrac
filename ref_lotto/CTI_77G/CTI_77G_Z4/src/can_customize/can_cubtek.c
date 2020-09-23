/*
 * can_haitec.c
 *
 *  Created on: 2017/6/5
 *      Author: user
 */
#include "sys_shared.h" /* include peripheral declarations */
#include "can_cubtek.h"
#include "can_tracking.h"
#include "can_msg_format.h"
#include "Com.h"
#include "Dem.h"
#include "Dem_Lcfg.h"
#include "Dcm.h"
#include "App_Dcm.h"
#include "App_ComTx.h"
#include "vertical_feedback_proxy.h"
#include "static_vertical_feedback.h"
#include "alignment_main.h"

#define MAX_ERROR_CNT			(10)
#define MAX_PASS_CNT			(10)

#define DISPLAY_FOLDING_ANNOTATION(...)	1

typedef void (*can_send_proc_p)(int ID, uint32_t* p);

static uint8_t func_status = CAN_STATUS_NORMAL;

#ifdef ENABLE_BSW_UDS_NM

static uint8_t ds_1s_delay_ok = FALSE;

static uint8_t ds_communication_bus_off = FALSE;
static uint8_t ds_can_comm_lost_after_wakeup_ok = FALSE;

static uint8_t ds_ready_to_sleep_flag = FALSE;

static uint8_t ds_can_status = CAN_EnRx_EnTx;

static uint8_t target_list_tx_enable = TRUE;
static uint8_t target_list_tx_header_only = FALSE;

static ad_en_status is_enable_ad = AD_BY_CUSTOMER;
static progress_bar_t is_enable_pb = PB_BY_CUSTOMER;

faw_did_pars_t __attribute__((section(".uds_did"))) faw_did_pars;

#define faw_did_pars_info_get(_ver, _size)		pars_info_get(FAW_DID_PARS_ID, _ver, _size)
#define faw_did_pars_info_set(_data, _cnt)		pars_info_set(FAW_DID_PARS_ID, _data, _cnt)

#define JSON_CONFIG_INFO 					"\t\t\"configInfo\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_VIN 							"\t\t\"vin\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_ALIGNMENT_AUTO_DETECT_H_ANGLE 	"\t\t\"alignmentAutoDetectHAngle\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ALIGNMENT_AUTO_DETECT_V_ANGLE 	"\t\t\"alignmentAutoDetectVAngle\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ALIGNMENT_AUTO_RESULT_H_ANGLE 	"\t\t\"alignmentAutoResultHAngle\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ALIGNMENT_AUTO_RESULT_V_ANGLE 	"\t\t\"alignmentAutoResultVAngle\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ALIGNMENT_H_ANGLE_OFFSET 		"\t\t\"alignmentHAngleOffset\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_TESTER_SERIES_NUMBER			"\t\t\"testerSeriesNumber\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_GSECURITY_ACESS_ATTEMP_NUMBER	"\t\t\"gSecurityAcessAttempNumber\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ECU_INSTALLATION_DATE			"\t\t\"ecuInstallationDate\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_RADAR_MANUFACTURE_DATE			"\t\t\"radarManufactureData\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_IS_DID_300_301_WRITTEN         "\t\t\"is_did_300_301_written\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_IS_RID_201_ENABLE_PB           "\t\t\"is_rid_0201_enable_pb\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_IS_AUTO_DETECT_BY_CUS			"\t\t\"is_autodetect_en_by_cus\":{\"t\":\"u8\",\"o\":%d,\"v\":%d}\n"

static faw_did_pars_p didpars = &faw_did_pars;
static void faw_did_pars_dump(void);
static int faw_did_pars_in_jsons(char* data);
static void faw_did_pars_setting(char** args, int count);
static void dtc_tester(char** args, int count);
static void cubtek_dtc_dbg(uint8_t is_pass);
static inline const char *string_of_enable_pb(progress_bar_t pbno);
void progress_bar_setting_update();

static const faw_did_pars_t default_didpars = {
	.hdr = {
		.base = (uint32_t)&faw_did_pars,
		.version = 0x0500,
		.size = sizeof(faw_did_pars_t),
		.id = FAW_DID_PARS_ID,
		.chksum = 0,
		.mask = 0
	},

	.info = {
		.configInfo = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.vin = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.alignmentAutoDetectHAngle = 0,
		.alignmentAutoDetectVAngle = 0,
		.gSecurityAcessAttempNumber = 3,
		.ecuInstallationDate = {0, 0, 0, 0},
		.radarManufactureData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.is_did_300_301_written = 0,
		.is_rid_0201_enable_pb = 0,
		.is_autodetect_en_by_cus = 0,
		.reserved1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		.reserved2 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	}
};
#endif

#ifdef ENABLE_BSW_UDS_NM
void cubtek_can_vehcle_info2_proc(uint64_t data)
#else
void cubtek_can_vehcle_info2_proc(can_message_p msg)
#endif
{
#ifdef ENABLE_BSW_UDS_NM
	CUBTEK_CAN_VEHCLE_INFO2 inf = {.R = data};
#else
	CUBTEK_CAN_VEHCLE_INFO2 inf = {.R = msg->pkg.dw};
#endif

	static uint8_t invalid_gear_cnt = 0;
	static uint8_t invalid_ign_cnt = 0;

	static uint16_t Invalid_Gear_position_signal = 0;
	static uint16_t Invalid_IGN_Sta_signal = 0;

	if(!inf.B.gear_state_inv)
	{
		if(inf.B.gear_state == 7)
			set_veh_gear_r_value();
		else if(inf.B.gear_state == 0)
			set_veh_gear_p_value();
		else
			set_veh_gear_d_value();

		invalid_gear_cnt = 0;

		if (Invalid_Gear_position_signal != 0)
		{	
			Invalid_Gear_position_signal = 0;
			put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950381_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
		}
	}
	else
	{
		invalid_gear_cnt++;

		if(MAX_ERROR_CNT < invalid_gear_cnt)
		{
			if (Invalid_Gear_position_signal != 1)
			{			
				Invalid_Gear_position_signal = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950381_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}		
			invalid_gear_cnt = 0;
		}

		set_veh_gear_invalid_value();
	}

	Com_SendSignal(COM_TXSIG_INVALID_GEAR_POSITION_SIGNAL, &Invalid_Gear_position_signal);

	if(!inf.B.ign_state_V)
	{
		if(0 == inf.B.ign_state)
		{
			set_veh_ign_off_value();			
		}
		else
		{
			set_veh_ign_on_value();
		}

		invalid_ign_cnt = 0;
		if(Invalid_IGN_Sta_signal != 0)
		{
			Invalid_IGN_Sta_signal = 0;
			put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950481_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
		}
	}
	else
	{
		invalid_ign_cnt++;

		if(MAX_ERROR_CNT < invalid_ign_cnt)
		{
			if(Invalid_IGN_Sta_signal != 1)
			{			
				Invalid_IGN_Sta_signal = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950481_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
			invalid_ign_cnt = 0;
		}

		set_veh_ign_invalid_value();
	}

	Com_SendSignal(COM_TXSIG_INVALID_IGN_STA_SIGNAL, &Invalid_IGN_Sta_signal);

	cubtek_did_can_config_handler();
#if 0
	if(1 == inf.B.turn_indicator)
	{
		set_veh_turn_indicator_right_on_value();
	}
	else if(2 == inf.B.turn_indicator)
	{
		set_veh_turn_indicator_left_on_value();
	}
	else
	{
		set_veh_turn_indicator_off_value();
	}

	if(1 == inf.B.door_fl)
	{
		set_veh_door_status_value_open(VEH_DOOR_FRONT_LEFT);
	}
	else
	{
		clear_veh_door_status_value_open(VEH_DOOR_FRONT_LEFT);
	}

	if(1 == inf.B.door_fr)
	{
		set_veh_door_status_value_open(VEH_DOOR_FRONT_RIGHT);
	}
	else
	{
		clear_veh_door_status_value_open(VEH_DOOR_FRONT_RIGHT);
	}

	if(1 == inf.B.door_rl)
	{
		set_veh_door_status_value_open(VEH_DOOR_REAR_LEFT);
	}
	else
	{
		clear_veh_door_status_value_open(VEH_DOOR_REAR_LEFT);
	}

	if(1 == inf.B.door_rr)
	{
		set_veh_door_status_value_open(VEH_DOOR_REAR_RIGHT);
	}
	else
	{
		clear_veh_door_status_value_open(VEH_DOOR_REAR_RIGHT);
	}
#endif	
}

#ifdef ENABLE_BSW_UDS_NM
void cubtek_can_info_proc(uint64_t data)
#else
void cubtek_can_info_proc(can_message_p msg)
#endif
{
#ifdef ENABLE_BSW_UDS_NM
	CUBTEK_CAN_VEHCLE_INFO inf = {.R = data};
#else
	CUBTEK_CAN_VEHCLE_INFO inf = {.R = msg->pkg.dw};
#endif
	float real_speed;
	float real_yaw_rate;
	float real_steering_angle;

	static uint8_t invalid_speed_cnt = 0;
	static uint8_t invalid_yaw_rate_cnt = 0;
	static uint8_t invalid_str_cnt = 0;

	static uint16_t Invalid_Vehicle_Speed_signal = 0;
	static uint16_t Invalid_Yaw_Rate_signal = 0;
	static uint16_t Invalid_Steering_Angle_signal = 0;

	static float speed_a;
	static float speed_b;

	if(!inf.B.speed_inv)
	{
		if(inf.B.speed < 2048)
		{
			real_speed =  (float)inf.B.speed * 0.125;
            get_trk2_uds_speed_makeup(&speed_a, &speed_b, 0);

            if(real_speed > 0 && speed_a > 0)
            {
                real_speed = speed_a * real_speed + speed_b;
            }

			set_veh_eps_speed_value(real_speed);
			set_veh_dashboard_speed_value(real_speed);

			invalid_speed_cnt = 0;
			if(Invalid_Vehicle_Speed_signal != 0)
			{
				Invalid_Vehicle_Speed_signal = 0;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950081_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
			}
		}
		else
		{
			set_veh_eps_speed_invalid_value();
			set_veh_dashboard_speed_invalid_value();
		}
	}
	else
	{
		invalid_speed_cnt++;

		if(MAX_ERROR_CNT < invalid_speed_cnt)
		{
			if(Invalid_Vehicle_Speed_signal != 1)
			{
				Invalid_Vehicle_Speed_signal = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950081_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
			invalid_speed_cnt = 0;
		}

		set_veh_eps_speed_invalid_value();
		set_veh_dashboard_speed_invalid_value();
	}

	Com_SendSignal(COM_TXSIG_INVALID_VEHICLE_SPEED_SIGNAL, &Invalid_Vehicle_Speed_signal);

	if(!inf.B.yaw_rate_inv)
	{
		if(inf.B.yaw_rate < 2001)
		{
			real_yaw_rate = (float)(inf.B.yaw_rate - 1000) * 0.1;
			set_veh_yaw_rate_value(real_yaw_rate);

			invalid_yaw_rate_cnt = 0;
			if(Invalid_Yaw_Rate_signal != 0)
			{
				Invalid_Yaw_Rate_signal = 0;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950181_INDEX<<8) | DEM_EVENT_STATUS_PASSED));			
			}
		}
		else
		{
			set_veh_yaw_rate_invalid_value();
		}
	}
	else
	{
		invalid_yaw_rate_cnt++;

		if(MAX_ERROR_CNT < invalid_yaw_rate_cnt)
		{
			if(Invalid_Yaw_Rate_signal != 0)
			{	
				Invalid_Yaw_Rate_signal = 0;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950181_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
			invalid_yaw_rate_cnt = 0;
		}

		set_veh_yaw_rate_invalid_value();
	}

	Com_SendSignal(COM_TXSIG_INVALID_YAW_RATE_SIGNAL, &Invalid_Yaw_Rate_signal);

	if(!inf.B.str_angle_v)
	{
		if (inf.B.str_angle != 65535)
		{
			real_steering_angle = (float)(-9000 + inf.B.str_angle) * 0.1;
			set_veh_steering_angle_value(real_steering_angle);

			invalid_str_cnt = 0;
			if(Invalid_Steering_Angle_signal != 0)
			{
				Invalid_Steering_Angle_signal = 0;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950281_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
			}
		}
		else
		{
			set_veh_steering_angle_invalid_value();
		}
	}
	else
	{
		invalid_str_cnt++;

		if(MAX_ERROR_CNT < invalid_str_cnt)
		{
			if(Invalid_Steering_Angle_signal != 1)
			{	
				Invalid_Steering_Angle_signal = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950281_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
			invalid_str_cnt = 0;
		}

		set_veh_steering_angle_invalid_value();
	}

	Com_SendSignal(COM_TXSIG_INVALID_STEERING_ANGLE_SIGNAL, &Invalid_Steering_Angle_signal);
}

void can_send_alarm(int warning)
{
	CUBTEK_FCW_WARN_REQ warn = {0};
	
//	if(can_alarm_mode)
	{
		warn.B.pre_warning  = 0;
		warn.B.warning  = 0;
		warn.B.emg_warning  = 0;

		if(warning == 1)
			warn.B.warning  = 1;
		else if(warning == 2)
			warn.B.pre_warning  = 1;
		else if(warning == 3)
			warn.B.emg_warning  = 1;

#ifdef ENABLE_BSW_UDS_NM
		if(TRUE == product_en_radar_fcw_out_flag_get())
		{
			App_ComTx_IpduData_Transmit(CAN_ID_CUBTEK_FCW_WARNING_REQ, warn.R);
		}	
#else
		if(TRUE == product_en_radar_fcw_out_flag_get())
		{
			can_tracking_tx(CAN_ID_CUBTEK_FCW_WARNING_REQ, (uint32_t*)&warn);
		}		
#endif
	}
}

static cub_dvtf get_cub_dvtf(void)
{
  cub_dvtf result = {0};

  result.B.sampling_cnt = get_vert_finished_num();
  result.B.max_sampling_cnt = get_vert_alignment_total_num();
  result.B.pitch_ang = get_auto_vert_mount_angle();

  return result;
}

static void _cubtek_targets_send(tracking_group_p tkg)
{
	int16_t	rx;
	int16_t	ry;
	int16_t	vx;
	int16_t	vy;
	int16_t	ax;
	tracking_p tg = tkg->targets;
	cub_obj_list_info info;
	cub_auto_calib_info calib;
	cub_obj_list0 obj1st;
	cub_obj_list1 obj2nd;
	uint32_t tran_id = CAN_ID_CUBTEK_TRACKING_START;
	int send_alarm = 0;
	int cnt = 0;
	uint8_t cip_id = 255;
	uint8_t cip_acc_id = 255;
	uint8_t cip_aeb_id = 255;

	// Blackbox_Record(tkg);

	if(FALSE == target_list_tx_enable)
	    return;

	if(TRUE == target_list_tx_header_only)
	    info.B.num = 0;
	else
	    info.B.num =  tkg->tcnt;

	info.B.tunnel_flag = tkg->tunnel_flag;
	info.B.func_status = func_status;
	info.B.reserved1 = 0;
	info.B.reserved2 = 0;
	info.B.cnt =  tkg->frame_num;
	func_status = CAN_STATUS_NORMAL;

	for (cnt = 0; cnt < tkg->tcnt; cnt++)
	{
		if(tg->cip) {
			cip_id = tg->tracking_id;
		}

		if(tg->cip_acc) {
			cip_acc_id = tg->tracking_id;
		}

		if(tg->cip_aeb) {
			cip_aeb_id = tg->tracking_id;
		}
		tg++;
	}
	info.B.cip_id = cip_id;
	info.B.cip_acc_id = cip_acc_id;
	info.B.cip_aeb_id = cip_aeb_id;
#ifdef ENABLE_BSW_UDS_NM
	if(TRUE == product_en_pcan_out_flag_get()) {
		can_tracking_tx(CAN_ID_CUBTEK_NUM_OF_OBJ, (uint32_t*)&info);
	}else{
		App_ComTx_IpduData_Transmit(CAN_ID_CUBTEK_NUM_OF_OBJ, info.R);
	}
	if (tkg->auto_calib_flag == 1) {
		calib.B.auto_calib_left_num = tkg->auto_calib_left_num;
		calib.B.auto_calib_right_num = tkg->auto_calib_right_num;
		calib.B.calib_angle = get_auto_hori_mount_angle() * -1.0; // (-1) convert to UDS format
		App_ComTx_IpduData_Transmit(CAN_ID_CUBTEK_AUTO_CALIB, calib.R);
	}
	if (tkg->auto_calib_flag == 1) {
	  cub_dvtf cub_dvtf;
	  cub_dvtf = get_cub_dvtf();
	  App_ComTx_IpduData_Transmit(CAN_ID_CUBTEK_DVTF, cub_dvtf.R);
	}
#else
	can_tracking_tx(CAN_ID_CUBTEK_NUM_OF_OBJ, (uint32_t*)&info);
	if (tkg->auto_calib_flag == 1) {
		calib.B.auto_calib_left_num = tkg->auto_calib_left_num;
		calib.B.auto_calib_right_num = tkg->auto_calib_right_num;
		calib.B.calib_angle = tkg->calib_angle;
		can_tracking_tx(CAN_ID_CUBTEK_AUTO_CALIB, (uint32_t*)&calib);
	}
#endif

	if(TRUE == target_list_tx_header_only)
	    return;

	tg = tkg->targets;
	cnt = 0;
	while(cnt < tkg->tcnt)
	{
		rx = (int16_t)(tg->rx * 8.0);
		ry = (int16_t)((tg->ry + 128.0) * 8.0);
		vx = (int16_t)((tg->vx + 102.0) * 20.0);
		vy = (int16_t)((tg->vy + 102.0) * 20.0);
		ax = (int16_t)((tg->ax + 40.0) * 25.0);
		obj1st.B.cnt = info.B.cnt;
		obj1st.B.obj_id = tg->tracking_id;
		obj1st.B.pos_x = rx;
		obj1st.B.pos_y = ry;
		obj1st.B.vel_x = vx;
		obj1st.B.vel_y = vy;
		if(tg->cip)	{
			obj1st.B.cip = 1;
			if(tg->cip == 3)
			{
				obj1st.B.pre_warn = 1;
				send_alarm = 2;
			}
			else
			{
				obj1st.B.pre_warn = 0;
			}
			if(tg->cip == 5)
			{
				obj1st.B.warn_dist = 1;
				send_alarm = 1;
			}
			else
			{
				obj1st.B.warn_dist = 0;
			}
			if(tg->cip == 9)
			{
				obj1st.B.emergency_warn = 1;
				send_alarm = 3;
			}
			else
			{
				obj1st.B.emergency_warn = 0;
			}
		} else {
			obj1st.B.cip = 0;
		}

		if(tg->cip_acc) {
			obj1st.B.cip_acc = 1;
		} else {
			obj1st.B.cip_acc = 0;
		}

		if(tg->cip_aeb) {
			obj1st.B.cip_aeb = 1;
		} else {
			obj1st.B.cip_aeb = 0;
		}

#ifdef ENABLE_BSW_UDS_NM
		if(TRUE == product_en_pcan_out_flag_get()){
			can_tracking_tx(tran_id, (uint32_t*)&obj1st);
		}else{
			App_ComTx_IpduData_Transmit(tran_id, obj1st.R);
		}
#else
		can_tracking_tx(tran_id, (uint32_t*)&obj1st);
#endif

		tran_id++;
		obj2nd.B.cnt = info.B.cnt;
		obj2nd.B.obj_id = tg->tracking_id;
		obj2nd.B.acc_x = ax;
		obj2nd.B.status = tg->status;
		obj2nd.B.reserved1 = 0;
		obj2nd.B.Dynamic = tg->dynamic_property;
		obj2nd.B.vangle = tg->vangle;
		obj2nd.B.probability = tg->probability;
		obj2nd.B.rcs_type = tg->rcs_type;
		obj2nd.B.guardrail_cnt = tg->guardrail_cnt;
		
#ifdef ENABLE_BSW_UDS_NM
		if(TRUE == product_en_pcan_out_flag_get()){
			can_tracking_tx(tran_id, (uint32_t*)&obj2nd);
		}else{
			App_ComTx_IpduData_Transmit(tran_id, obj2nd.R);
		}
#else
		can_tracking_tx(tran_id, (uint32_t*)&obj2nd);
#endif

#ifdef BLACKBOX_DEBUG
    extern bool BBOX_SYNC_CONSOLE;
    if (cnt < 3 && BBOX_SYNC_CONSOLE) {
      PRINTF("can_cub: %02d rX:%d, rY:%d, vX:%d, vY:%d, state:%d\n",
             cnt, obj1st.B.pos_x, obj1st.B.pos_y,
             obj1st.B.vel_x, obj1st.B.vel_y, obj2nd.B.status);
    }
#endif

		tran_id++;
		tg++;
		cnt++;
	}
	can_send_alarm(send_alarm);
}

void cubtek_init(void)
{
#ifndef ENABLE_BSW_UDS_NM
	can_rx_id_register(CAN_ID_VEHICLE_INFO1, CAN_STD_ID_MASK_FULL, "veh1", (event_proc_p)cubtek_can_info_proc);
	can_rx_id_register(CAN_ID_VEHICLE_INFO2, CAN_STD_ID_MASK_FULL, "veh2", (event_proc_p)cubtek_can_vehcle_info2_proc);
	can_tx_tracking_init(TRACKING_ITF_CAN0);
/*#else
	can2_rx_id_register(CAN_ID_VEHICLE_INFO1, CAN_STD_ID_MASK_FULL, "veh1", (event_proc_p)cubtek_can_info_proc);
	can2_rx_id_register(CAN_ID_VEHICLE_INFO2, CAN_STD_ID_MASK_FULL, "veh2", (event_proc_p)cubtek_can_vehcle_info2_proc);
	can_tx_tracking_init(TRACKING_ITF_CAN2);*/
#else
	memcpy(didpars, (void*)&default_didpars, sizeof(default_didpars));
	pars_get((pars_ctx_p)didpars, faw_did_pars_dump, faw_did_pars_in_jsons);
	console_command_reg("didp", faw_did_pars_setting);
	console_command_reg("dtctest", dtc_tester);
	cubtek_did_can_config_handler();
	if(TRUE == product_en_pcan_out_flag_get()){
		can_tx_tracking_init(TRACKING_ITF_CAN2);
	}else{
		can_tx_tracking_init(TRACKING_ITF_CAN0);
	}	
#endif
	ipc_reg_msg(MSG_TARGETS_LIST, "ctktgs", (event_proc_p)_cubtek_targets_send);

	// update detection setting and initialize alignment and detection
	auto_detect_en_by_cus_setting_update();
	alignment_init();

	vtfb_init();
	progress_bar_setting_update();
}

void cubtek_did_init(void)
{
	memcpy(didpars, (void*)&default_didpars, sizeof(default_didpars));
	pars_get((pars_ctx_p)didpars, faw_did_pars_dump, NULL);
}

#ifdef ENABLE_BSW_UDS_NM
static inline const char *string_of_enable_pb(progress_bar_t pbno)
{
    static const char *pb_list[] = {
        "PB_BY_CUSTOMER",
        "PB_DISABLE",
        "PB_ENABLE",
        "PB_INVALID"
    };

    return pb_list[pbno];
}

static inline const char *string_of_enable_ad(ad_en_status adno)
{
    static const char *ad_list[] = {
        "AD_BY_CUSTOMER",
        "AD_DISABLE",
        "AD_ENABLE",
        "AD_INVALID"
    };

    return ad_list[adno];
}

static void faw_did_pars_dump(void)
{
	PRINTF("FAW DID parameters:\n");
	PRINTF("- Configuration information (cfginfo): %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
		didpars->info.configInfo[0], didpars->info.configInfo[1], didpars->info.configInfo[2], didpars->info.configInfo[3],
		didpars->info.configInfo[4], didpars->info.configInfo[5], didpars->info.configInfo[6], didpars->info.configInfo[7],
		didpars->info.configInfo[8], didpars->info.configInfo[9], didpars->info.configInfo[10], didpars->info.configInfo[11],
		didpars->info.configInfo[12], didpars->info.configInfo[13], didpars->info.configInfo[14], didpars->info.configInfo[15]);
	PRINTF("- VIN (vin): %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
		didpars->info.vin[0], didpars->info.vin[1], didpars->info.vin[2], didpars->info.vin[3],	didpars->info.vin[4],
		didpars->info.vin[5], didpars->info.vin[6], didpars->info.vin[7], didpars->info.vin[8], didpars->info.vin[9],
		didpars->info.vin[10], didpars->info.vin[11], didpars->info.vin[12], didpars->info.vin[13], didpars->info.vin[14],
		didpars->info.vin[15], didpars->info.vin[16]);
	PRINTF("- Radar auto-alignment detect horizontal angle (autohdet): %.2f\n", (float)((int8_t)didpars->info.alignmentAutoDetectHAngle) * 0.1);
	PRINTF("- Radar auto-alignment detect vertical angle (autovdet): %.2f\n", (float)((int8_t)didpars->info.alignmentAutoDetectVAngle) * 0.1);
	PRINTF("- Radar auto-alignment result horizontal angle (autohang): %.2f\n", (float)(int8_t)didpars->info.alignmentAutoAlignHAngle * 0.1);
	PRINTF("- Radar auto-alignment result vertical angle (autovang): %.2f\n", (float)(int8_t)didpars->info.alignmentAutoAlignVAngle * 0.1);
    PRINTF("- gSecurity acess attemp number (gsaanum): %d\n", didpars->info.gSecurityAcessAttempNumber);
	PRINTF("- ECU installation date (ecudate): %.2x %.2x %.2x %.2x\n",
		didpars->info.ecuInstallationDate[0], didpars->info.ecuInstallationDate[1], didpars->info.ecuInstallationDate[2], didpars->info.ecuInstallationDate[3]);
	PRINTF("- Radar manufacture data (mfrdata): %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
		didpars->info.radarManufactureData[0], didpars->info.radarManufactureData[1], didpars->info.radarManufactureData[2], didpars->info.radarManufactureData[3],
		didpars->info.radarManufactureData[4], didpars->info.radarManufactureData[5], didpars->info.radarManufactureData[6], didpars->info.radarManufactureData[7],
		didpars->info.radarManufactureData[8], didpars->info.radarManufactureData[9], didpars->info.radarManufactureData[10], didpars->info.radarManufactureData[11]);
	PRINTF("- Is DID300, 301 wirtten (is_did_300_301_written): %.2x\n", didpars->info.is_did_300_301_written);
	PRINTF("- Enable progress bar (enpb): %d (0: by customer (%s), 1: disable, 2: enable)\n", didpars->info.is_rid_0201_enable_pb, string_of_enable_pb(CUSTOMER_DEFAULT_PB_FUNCTION));
	PRINTF("- Enable autodetect by cus (enad): %d (0: by customer (%s), 1: disable, 2: enable)\n", didpars->info.is_autodetect_en_by_cus , string_of_enable_ad(CUSTOMER_DEFAULT_AD_FUNCTION));
}


static int faw_did_pars_in_jsons(char* data)
{
	int cnt = 0;

	if (data) {
		cnt = sprintf(data,"{\n");
		cnt += sprintf(data + cnt, JSON_PARS_HDR_ID, (char)(FAW_DID_PARS_ID >> 24), (char)(FAW_DID_PARS_ID >> 16), (char)(FAW_DID_PARS_ID >> 8), (char)(FAW_DID_PARS_ID));
		cnt += sprintf(data + cnt, JSON_PARS_HDR_VERSION, didpars->hdr.version);
		cnt += sprintf(data + cnt, JSON_PARS_HDR_SIZE, didpars->hdr.size - sizeof(pars_header_t));

		cnt += sprintf(data + cnt, "\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_CONFIG_INFO, offsetof(faw_did_info_t, configInfo),
			didpars->info.configInfo[0], didpars->info.configInfo[1], didpars->info.configInfo[2], didpars->info.configInfo[3],
			didpars->info.configInfo[4], didpars->info.configInfo[5], didpars->info.configInfo[6], didpars->info.configInfo[7],
			didpars->info.configInfo[8], didpars->info.configInfo[9], didpars->info.configInfo[10], didpars->info.configInfo[11],
			didpars->info.configInfo[12], didpars->info.configInfo[13], didpars->info.configInfo[14], didpars->info.configInfo[15]);
		cnt += sprintf(data + cnt, JSON_VIN, offsetof(faw_did_info_t, vin),
			didpars->info.vin[0], didpars->info.vin[1], didpars->info.vin[2], didpars->info.vin[3],	didpars->info.vin[4],
			didpars->info.vin[5], didpars->info.vin[6], didpars->info.vin[7], didpars->info.vin[8], didpars->info.vin[9],
			didpars->info.vin[10], didpars->info.vin[11], didpars->info.vin[12], didpars->info.vin[13], didpars->info.vin[14],
			didpars->info.vin[15], didpars->info.vin[16]);
		cnt += sprintf(data + cnt, JSON_ALIGNMENT_AUTO_DETECT_H_ANGLE, offsetof(faw_did_info_t, alignmentAutoDetectHAngle), didpars->info.alignmentAutoDetectHAngle);
		cnt += sprintf(data + cnt, JSON_ALIGNMENT_AUTO_DETECT_V_ANGLE, offsetof(faw_did_info_t, alignmentAutoDetectVAngle), didpars->info.alignmentAutoDetectVAngle);
		cnt += sprintf(data + cnt, JSON_ALIGNMENT_AUTO_RESULT_H_ANGLE, offsetof(faw_did_info_t, alignmentAutoAlignHAngle), didpars->info.alignmentAutoAlignHAngle);
		cnt += sprintf(data + cnt, JSON_ALIGNMENT_AUTO_RESULT_V_ANGLE, offsetof(faw_did_info_t, alignmentAutoAlignVAngle), didpars->info.alignmentAutoAlignVAngle);
        cnt += sprintf(data + cnt, JSON_GSECURITY_ACESS_ATTEMP_NUMBER, offsetof(faw_did_info_t, gSecurityAcessAttempNumber), didpars->info.gSecurityAcessAttempNumber);
		cnt += sprintf(data + cnt, JSON_ECU_INSTALLATION_DATE, offsetof(faw_did_info_t, ecuInstallationDate),
			didpars->info.ecuInstallationDate[0], didpars->info.ecuInstallationDate[1], didpars->info.ecuInstallationDate[2], didpars->info.ecuInstallationDate[3]);
		cnt += sprintf(data + cnt, JSON_RADAR_MANUFACTURE_DATE, offsetof(faw_did_info_t, radarManufactureData),
			didpars->info.radarManufactureData[0], didpars->info.radarManufactureData[1], didpars->info.radarManufactureData[2], didpars->info.radarManufactureData[3],
			didpars->info.radarManufactureData[4], didpars->info.radarManufactureData[5], didpars->info.radarManufactureData[6], didpars->info.radarManufactureData[7],
			didpars->info.radarManufactureData[8], didpars->info.radarManufactureData[9], didpars->info.radarManufactureData[10], didpars->info.radarManufactureData[11]);
		cnt += sprintf(data + cnt, JSON_IS_DID_300_301_WRITTEN, offsetof(faw_did_info_t, is_did_300_301_written), didpars->info.alignmentAutoAlignVAngle);
		cnt += sprintf(data + cnt, JSON_IS_RID_201_ENABLE_PB, offsetof(faw_did_info_t, is_rid_0201_enable_pb), didpars->info.is_rid_0201_enable_pb);
		cnt += sprintf(data + cnt, JSON_IS_AUTO_DETECT_BY_CUS, offsetof(faw_did_info_t, is_autodetect_en_by_cus), didpars->info.is_autodetect_en_by_cus);
		cnt += sprintf(data + cnt, "\t}\n}\n");
	}

	return cnt;
}


static void set_config_info(char** args, int count)
{
	if (count == 18) {
		didpars->info.configInfo[0] = (uint8_t)atof(args[2]);
		didpars->info.configInfo[1] = (uint8_t)atof(args[3]);
		didpars->info.configInfo[2] = (uint8_t)atof(args[4]);
		didpars->info.configInfo[3] = (uint8_t)atof(args[5]);
		didpars->info.configInfo[4] = (uint8_t)atof(args[6]);
		didpars->info.configInfo[5] = (uint8_t)atof(args[7]);
		didpars->info.configInfo[6] = (uint8_t)atof(args[8]);
		didpars->info.configInfo[7] = (uint8_t)atof(args[9]);
		didpars->info.configInfo[8] = (uint8_t)atof(args[10]);
		didpars->info.configInfo[9] = (uint8_t)atof(args[11]);
		didpars->info.configInfo[10] = (uint8_t)atof(args[12]);
		didpars->info.configInfo[11] = (uint8_t)atof(args[13]);
		didpars->info.configInfo[12] = (uint8_t)atof(args[14]);
		didpars->info.configInfo[13] = (uint8_t)atof(args[15]);
		didpars->info.configInfo[14] = (uint8_t)atof(args[16]);
		didpars->info.configInfo[15] = (uint8_t)atof(args[17]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_vin(char** args, int count)
{
	if (count == 19) {
		didpars->info.vin[0] = (uint8_t)atof(args[2]);
		didpars->info.vin[1] = (uint8_t)atof(args[3]);
		didpars->info.vin[2] = (uint8_t)atof(args[4]);
		didpars->info.vin[3] = (uint8_t)atof(args[5]);
		didpars->info.vin[4] = (uint8_t)atof(args[6]);
		didpars->info.vin[5] = (uint8_t)atof(args[7]);
		didpars->info.vin[6] = (uint8_t)atof(args[8]);
		didpars->info.vin[7] = (uint8_t)atof(args[9]);
		didpars->info.vin[8] = (uint8_t)atof(args[10]);
		didpars->info.vin[9] = (uint8_t)atof(args[11]);
		didpars->info.vin[10] = (uint8_t)atof(args[12]);
		didpars->info.vin[11] = (uint8_t)atof(args[13]);
		didpars->info.vin[12] = (uint8_t)atof(args[14]);
		didpars->info.vin[13] = (uint8_t)atof(args[15]);
		didpars->info.vin[14] = (uint8_t)atof(args[16]);
		didpars->info.vin[15] = (uint8_t)atof(args[17]);
		didpars->info.vin[16] = (uint8_t)atof(args[18]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_aligment_auto_detect_h_angle(char** args, int count)
{
	if (count == 3) {
		didpars->info.alignmentAutoDetectHAngle = (uint8_t)((float)atof(args[2]) * 10.0);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_aligment_auto_detect_v_angle(char** args, int count)
{
	if (count == 3) {
		didpars->info.alignmentAutoDetectVAngle = (uint8_t)((float)atof(args[2]) * 10.0);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_aligment_auto_align_h_angle(char** args, int count)
{
	if (count == 3) {
		didpars->info.alignmentAutoAlignHAngle = (uint8_t)((float)atof(args[2]) * 10.0);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_aligment_auto_align_v_angle(char** args, int count)
{
	if (count == 3) {
		didpars->info.alignmentAutoAlignVAngle = (uint8_t)((float)atof(args[2]) * 10.0);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_ecu_installation_date(char** args, int count)
{
	if (count == 6) {
		didpars->info.ecuInstallationDate[0] = (uint8_t)atof(args[2]);
		didpars->info.ecuInstallationDate[1] = (uint8_t)atof(args[3]);
		didpars->info.ecuInstallationDate[2] = (uint8_t)atof(args[4]);
		didpars->info.ecuInstallationDate[3] = (uint8_t)atof(args[5]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_radar_manufacture_data(char** args, int count)
{
	if (count == 14) {
		didpars->info.radarManufactureData[0] = (uint8_t)atof(args[2]);
		didpars->info.radarManufactureData[1] = (uint8_t)atof(args[3]);
		didpars->info.radarManufactureData[2] = (uint8_t)atof(args[4]);
		didpars->info.radarManufactureData[3] = (uint8_t)atof(args[5]);
		didpars->info.radarManufactureData[4] = (uint8_t)atof(args[6]);
		didpars->info.radarManufactureData[5] = (uint8_t)atof(args[7]);
		didpars->info.radarManufactureData[6] = (uint8_t)atof(args[8]);
		didpars->info.radarManufactureData[7] = (uint8_t)atof(args[9]);
		didpars->info.radarManufactureData[8] = (uint8_t)atof(args[10]);
		didpars->info.radarManufactureData[9] = (uint8_t)atof(args[11]);
		didpars->info.radarManufactureData[10] = (uint8_t)atof(args[12]);
		didpars->info.radarManufactureData[11] = (uint8_t)atof(args[13]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_is_300_301_written(char** args, int count)
{
	if (count == 3) {
		didpars->info.is_did_300_301_written = (uint8_t)((float)atof(args[2]));
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_is_enable_pb(char** args, int count)
{
    uint8_t is_enable = 0;
    if (count == 3) {
        is_enable = (uint8_t)(atoi(args[2]));

        if(is_enable <= PB_BY_CUSTOMER || is_enable >= PB_INVALID)
            is_enable = PB_BY_CUSTOMER;

        didpars->info.is_rid_0201_enable_pb = is_enable;
        pars_set((pars_ctx_p)didpars);

        progress_bar_setting_update();
    }
    faw_did_pars_dump();
}

static void set_is_enable_ad_by_user(char** args, int count)
{
    uint8_t is_enable = 0;
    if (count == 3) {
        is_enable = (uint8_t)(atoi(args[2]));

        if(is_enable <= AD_BY_CUSTOMER || is_enable >= AD_INVALID)
            is_enable = AD_BY_CUSTOMER;

        didpars->info.is_autodetect_en_by_cus = is_enable;
        auto_detect_en_by_cus_setting_update();
        pars_set((pars_ctx_p)didpars);

    }
    faw_did_pars_dump();
}

static void set_reserved_1(char** args, int count)
{
	if (count == 17) {
		didpars->info.reserved1[0] = (uint8_t)atof(args[2]);
		didpars->info.reserved1[1] = (uint8_t)atof(args[3]);
		didpars->info.reserved1[2] = (uint8_t)atof(args[4]);
		didpars->info.reserved1[3] = (uint8_t)atof(args[5]);
		didpars->info.reserved1[4] = (uint8_t)atof(args[6]);
		didpars->info.reserved1[5] = (uint8_t)atof(args[7]);
		didpars->info.reserved1[6] = (uint8_t)atof(args[8]);
		didpars->info.reserved1[7] = (uint8_t)atof(args[9]);
		didpars->info.reserved1[8] = (uint8_t)atof(args[10]);
		didpars->info.reserved1[9] = (uint8_t)atof(args[11]);
		didpars->info.reserved1[10] = (uint8_t)atof(args[12]);
		didpars->info.reserved1[11] = (uint8_t)atof(args[13]);
		didpars->info.reserved1[12] = (uint8_t)atof(args[14]);
		didpars->info.reserved1[13] = (uint8_t)atof(args[15]);
		didpars->info.reserved1[14] = (uint8_t)atof(args[16]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_reserved_2(char** args, int count)
{
	if (count == 18) {
		didpars->info.reserved2[0] = (uint8_t)atof(args[2]);
		didpars->info.reserved2[1] = (uint8_t)atof(args[3]);
		didpars->info.reserved2[2] = (uint8_t)atof(args[4]);
		didpars->info.reserved2[3] = (uint8_t)atof(args[5]);
		didpars->info.reserved2[4] = (uint8_t)atof(args[6]);
		didpars->info.reserved2[5] = (uint8_t)atof(args[7]);
		didpars->info.reserved2[6] = (uint8_t)atof(args[8]);
		didpars->info.reserved2[7] = (uint8_t)atof(args[9]);
		didpars->info.reserved2[8] = (uint8_t)atof(args[10]);
		didpars->info.reserved2[9] = (uint8_t)atof(args[11]);
		didpars->info.reserved2[10] = (uint8_t)atof(args[12]);
		didpars->info.reserved2[11] = (uint8_t)atof(args[13]);
		didpars->info.reserved2[12] = (uint8_t)atof(args[14]);
		didpars->info.reserved2[13] = (uint8_t)atof(args[15]);
		didpars->info.reserved2[14] = (uint8_t)atof(args[16]);
		didpars->info.reserved2[15] = (uint8_t)atof(args[17]);
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void set_gsecurity_acess_attemp_number(char** args, int count)
{
	if (count == 3) {
		didpars->info.gSecurityAcessAttempNumber = (uint8_t)(atoi(args[2]));
		pars_set((pars_ctx_p)didpars);
	}
	faw_did_pars_dump();
}

static void faw_did_pars_setting(char** args, int count)
{
	if (count > 2) {
		if (!strcmp(args[1], "cfginfo")) {
			set_config_info(args, count);
		} else if (!strcmp(args[1], "vin")) {
			set_vin(args, count);
		} else if (!strcmp(args[1], "autohdet")) {
			set_aligment_auto_detect_h_angle(args, count);
		} else if (!strcmp(args[1], "autovdet")) {
			set_aligment_auto_detect_v_angle(args, count);
		} else if (!strcmp(args[1], "autohang")) {
			set_aligment_auto_align_h_angle(args, count);
		} else if (!strcmp(args[1], "autovang")) {
			set_aligment_auto_align_v_angle(args, count);
		} else if (!strcmp(args[1], "ecudate")) {
			set_ecu_installation_date(args, count);
		} else if (!strcmp(args[1], "mfrdata")) {
			set_radar_manufacture_data(args, count);
		} else if (!strcmp(args[1], "is_did_300_301_written")) {
			set_is_300_301_written(args, count);
        } else if (!strcmp(args[1], "enpb")) {
            set_is_enable_pb(args, count);
        } else if (!strcmp(args[1], "enad")) {
            set_is_enable_ad_by_user(args, count);
		} else if (!strcmp(args[1], "rsvd1")) {
			set_reserved_1(args, count);
		} else if (!strcmp(args[1], "rsvd2")) {
			set_reserved_2(args, count);
		} else if (!strcmp(args[1], "gsaanum")) {
			set_gsecurity_acess_attemp_number(args, count);
		}
	} else {
		faw_did_pars_dump();
	}
}

static void dtc_tester(char** args, int count)
{
    if (count == 2)
    {

        if(!strcmp(args[1], "demdown"))
        {
            PRINTF("Diagnostic event manager Shout down\n");
            Dem_Shutdown();
        }
    }
    else if (count == 3) {
        if(!strcmp(args[1], "dtc"))
        {
            uint8_t onoff = strtoul(args[2], NULL, 10);

            if(onoff == 1)
            {
                PRINTF("DEM_CYCLE_STATE_START\n");
                Dem_SetOperationCycleState(DEM_OPCYC_IGNITION,DEM_CYCLE_STATE_START);   //DEM start
            }
            else
            {
                PRINTF("DEM_CYCLE_STATE_END\n");
                Dem_SetOperationCycleState(DEM_OPCYC_IGNITION,DEM_CYCLE_STATE_END); //DEM end
            }
        }
        else if(!strcmp(args[1], "dtcdbg"))
        {
            uint8_t is_pass = strtoul(args[2], NULL, 10);
            cubtek_dtc_dbg(is_pass);
        }
        else if(!strcmp(args[1], "sleep"))
        {
            uint8_t onoff = strtoul(args[2], NULL, 10);

            if(onoff == 0)
            {
                process_cmd_sleep();
            }
            else if(onoff == 1)
            {
                FS8x_power_down();
            }
            else
            {
                process_cmd_sleep();
                FS8x_power_down();
            }
        }
    }
}

static void cubtek_dtc_dbg(uint8_t is_pass)
{
    if(TRUE == is_pass)
    {
        PRINTF("DTC Passed\n");

        for(int i = 0 ; i < DEM_NUMBER_OF_DTC ; i++)
        {
            Dem_SetEventStatus(i,DEM_EVENT_STATUS_PASSED);  //Passed
        }
    }
    else
    {
        PRINTF("DTC Failed\n");

        for(int i = 0 ; i < DEM_NUMBER_OF_DTC ; i++)
        {
            Dem_SetEventStatus(i,DEM_EVENT_STATUS_FAILED);  //Failed
        }
    }
}

uint8_t* cubtek_faw_did_config_info_get()
{
	return (uint8_t *)&didpars->info.configInfo[0];
}

uint8_t* cubtek_faw_did_vin_get()
{
	return (uint8_t *)&didpars->info.vin[0];
}

uint8_t* cubtek_faw_did_aligment_auto_detect_h_angle_get()
{
	return (uint8_t *)&didpars->info.alignmentAutoDetectHAngle;
}

uint8_t* cubtek_faw_did_aligment_auto_detect_v_angle_get()
{
	return (uint8_t *)&didpars->info.alignmentAutoDetectVAngle;
}

uint8_t* cubtek_faw_did_aligment_auto_align_h_angle_get()
{
	return (uint8_t *)&didpars->info.alignmentAutoAlignHAngle;
}

uint8_t* cubtek_faw_did_aligment_auto_align_v_angle_get()
{
	return (uint8_t *)&didpars->info.alignmentAutoAlignVAngle;
}

void cubtek_faw_did_aligment_auto_detect_h_angle_set_and_save(uint8_t value)
{
	didpars->info.alignmentAutoDetectHAngle = value;
	pars_set((pars_ctx_p)didpars);
}

void cubtek_faw_did_aligment_auto_detect_v_angle_set_and_save(uint8_t value)
{
	didpars->info.alignmentAutoDetectVAngle = value;
	pars_set((pars_ctx_p)didpars);
}

void cubtek_faw_did_aligment_auto_align_h_angle_set_and_save(uint8_t value)
{
	didpars->info.alignmentAutoAlignHAngle = value;
	pars_set((pars_ctx_p)didpars);
}

void cubtek_faw_did_aligment_auto_align_v_angle_set_and_save(uint8_t value)
{
	didpars->info.alignmentAutoAlignVAngle = value;
	pars_set((pars_ctx_p)didpars);
}

uint8_t* cubtek_faw_did_ecu_installation_date_get()
{
	return (uint8_t *)&didpars->info.ecuInstallationDate[0];
}

uint8_t* cubtek_faw_did_radar_manufacture_data_get()
{
	return (uint8_t *)&didpars->info.radarManufactureData[0];
}

uint8_t* cubtek_faw_did_reserved_1_get()
{
	return (uint8_t *)&didpars->info.reserved1[0];
}

uint8_t* cubtek_faw_did_reserved_2_get()
{
	return (uint8_t *)&didpars->info.reserved2[0];
}

uint8_t* cubtek_faw_did_g_security_acess_attemp_number_get()
{
	return (uint8_t *)&didpars->info.gSecurityAcessAttempNumber;
}

uint8_t* cubtek_faw_did_is_300_301_written_get()
{
	return (uint8_t *)&didpars->info.is_did_300_301_written;
}

void cubtek_faw_did_pars_save_fun()
{
	pars_set((pars_ctx_p)didpars);
}

void cubtek_faw_did_pars_save(uint8_t status)
{

	if(DIDPARS_SAVE_DIRECT == status)
	{
		cubtek_faw_did_pars_save_fun();
	}
	else
	{
		put_event("did_pars_save", (event_proc_p)cubtek_faw_did_pars_save_fun, NULL);
	}	
}

uint8_t cubtek_faw_did_ds_1s_delay_status_get()
{
	return ds_1s_delay_ok;
}

void cubtek_faw_did_ds_1s_delay_status_set(uint8_t status)
{
	ds_1s_delay_ok = status;
}

uint8_t cubtek_faw_did_ds_communication_bus_off_status_get()
{
	return ds_communication_bus_off;
}

void cubtek_faw_did_ds_communication_bus_off_status_set(uint8_t status)
{
	ds_communication_bus_off = status;
}

uint8_t cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_get()
{
	return ds_can_comm_lost_after_wakeup_ok;
}

void cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_set(uint8_t status)
{
	ds_can_comm_lost_after_wakeup_ok = status;
}

uint8_t cubtek_faw_did_ds_ready_to_sleep_status_get()
{
	return ds_ready_to_sleep_flag;
}

void cubtek_faw_did_ds_ready_to_sleep_status_set(uint8_t status)
{
	ds_ready_to_sleep_flag = status;
}

uint8_t cubtek_faw_did_ds_can_status_get()
{
	return ds_can_status;
}

void cubtek_faw_did_ds_can_status_set(uint8_t status)
{
	ds_can_status = status;
}

void cubtek_did_can_config_handler(void)
{
	uint32_t ign_status = 0;
	uint32_t ign_val = 0;

    if (TRUE == product_dis_sleep_flag_get())	
    {
		if( (CAN_DisRx_DisTx == cubtek_faw_did_ds_can_status_get()) 
			|| (CAN_EnRx_DisTx == cubtek_faw_did_ds_can_status_get()) ) 			
		{
			AppComTxRx_Start();
		}
    }
    else
    {
		ign_status = get_ign_status();
		ign_val = get_ign_value();

		if ( (VEH_STATUS_VALID == ign_status) || (VEH_STATUS_NOT_GET_DATA == ign_status) )
		{
			if (VEH_IGN_ON == ign_val)
			{
				if( (CAN_DisRx_DisTx == cubtek_faw_did_ds_can_status_get()) 
				|| (CAN_EnRx_DisTx == cubtek_faw_did_ds_can_status_get()) ) 					
				{
					AppComTxRx_Start();
				}
			}			
			else
			{
				if( CAN_EnRx_EnTx == cubtek_faw_did_ds_can_status_get() ) 	
				{
					AppCom_DisTx_EnRx();
				}
			}

		}		
    }
}

void check_radar_alignment_result()
{
    bool is_iron_calib_completed = CALIB_IRON_COMPLETED == get_calib_iron_alignment_completion_flag();
    bool is_hori_completed = ALIGN_COMPLETED == get_hori_alignment_completed();
    bool is_vtfb_completed = kVtfbCompleted == svtf_eeprom_complete_state_get();
    bool is_dvtf_completed = ALIGN_COMPLETED == get_vert_alignment_completed();

    if(true == is_iron_calib_completed)
    {
        set_monitoring_result_by_id(MONITOR_ID_RADAR_ALIGNMENT, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
    }
    else if( true == is_hori_completed && ( true == is_vtfb_completed || true == is_dvtf_completed ) )
    {
        // auto_calibration     => horizontal angle only
        // vertical_alignmnet   => vertical angle only, including static alignment or dynamic alignment
        set_monitoring_result_by_id(MONITOR_ID_RADAR_ALIGNMENT, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
    }
    else
    {
        set_monitoring_result_by_id(MONITOR_ID_RADAR_ALIGNMENT, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
    }
}

void progress_bar_setting_update()
{
    is_enable_pb = didpars->info.is_rid_0201_enable_pb;

    switch(is_enable_pb)
    {
        case PB_BY_CUSTOMER:
            is_enable_pb = CUSTOMER_DEFAULT_PB_FUNCTION;
            PRINTF("[PROGRESS BAR]: Setting by customer (%s)\n", string_of_enable_pb(CUSTOMER_DEFAULT_PB_FUNCTION));
            break;
        case PB_DISABLE:
            is_enable_pb = PB_DISABLE;
            PRINTF("[PROGRESS BAR]: Set Disable\n");
            break;
        case PB_ENABLE:
            is_enable_pb = PB_ENABLE;
            PRINTF("[PROGRESS BAR]: Set Enable\n");
            break;
        default:
            is_enable_pb = CUSTOMER_DEFAULT_PB_FUNCTION;
            PRINTF("[PROGRESS BAR]: Setting by customer (%s)\n", string_of_enable_pb(CUSTOMER_DEFAULT_PB_FUNCTION));
            break;
    }
}

progress_bar_t is_enable_RID_0201_progress_bar(void)
{
    return is_enable_pb;
}

ad_en_status is_enable_auto_detect_by_cus(void)
{
    return is_enable_ad;
}

void auto_detect_en_by_cus_setting_update()
{
	is_enable_ad = didpars->info.is_autodetect_en_by_cus;

    switch(is_enable_ad)
    {
        case AD_BY_CUSTOMER:
        	is_enable_ad = CUSTOMER_DEFAULT_AD_FUNCTION;
            PRINTF("[AUTODETECT]: Setting by customer (%s)\n", string_of_enable_ad(CUSTOMER_DEFAULT_AD_FUNCTION) );
            break;
        case AD_DISABLE:
        	is_enable_ad = AD_DISABLE;
            break;
        case AD_ENABLE:
        	is_enable_ad = AD_ENABLE;
            break;
        default:
        	is_enable_ad = CUSTOMER_DEFAULT_AD_FUNCTION;
            break;
    }
}

void target_list_trasmit_enable(void)
{
    target_list_tx_enable = TRUE;
}

void target_list_trasmit_disable(void)
{
    target_list_tx_enable = FALSE;
}

void set_target_list_tx_header_only(uint8_t op)
{
    target_list_tx_header_only = op;
}

#endif // ENABLE_BSW_UDS_NM
