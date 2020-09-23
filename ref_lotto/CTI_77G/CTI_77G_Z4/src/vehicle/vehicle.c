/*
 * vehicle.c
 *
 *  Created on: 2018�~6��26��
 *      Author: user
 */
#include "sys_shared.h"
#include "vehicle.h"
#include "can_format.h"


#if defined(CTI_Z4_0)

vehicle_data_info_t __attribute__((section(".vehicle_data"))) vehicle_data_info;
static vehicle_data_info_p vehicle_info=&vehicle_data_info;

static void _vehicle_list(char** args, int count);
void set_vehicle_info(VEHICLE_INFO_E v_info ,int32_t data);

void vehicle_list_init()
{
	VEHICLE_INFO_E cnt = 0;
	while(cnt < INVALID)
	{
		set_vehicle_info(cnt, VEH_INIT_DATA_STATUS);
		cnt++;
	}
}

void vehicle_init()
{
	vehicle_list_init();
	IPC_SEND_MSG_Z70(MSG_VEHICLE_DATA, (void*)vehicle_info, 0);
	IPC_SEND_MSG_Z71(MSG_VEHICLE_DATA, (void*)vehicle_info, 0);

	console_command_reg("veh", _vehicle_list);
}

#else
static vehicle_data_info_p vehicle_info = NULL;

void vehicle_usage(vehicle_data_info_p v)
{
	vehicle_info = v;
}

void vehicle_init(void)
{
	ipc_reg_msg(MSG_VEHICLE_DATA, "vdata", (msg_proc_p)vehicle_usage);
}
#endif
//=================================================================
//when get,you maybe use it


int32_t get_vehicle_info(VEHICLE_INFO_E v_info)
{
	return vehicle_info->R[v_info];
}

VEHICLE_STATUS_E check_data_status(int32_t data)
{
	data &= VEH_VALID_STATUS_MASK;

	if(VEH_INIT_DATA_STATUS & data)
	{
		return VEH_STATUS_NOT_GET_DATA;
	}
	else if(VEH_INVALID_DATA_STATUS & data)
	{
		return 	VEH_STATUS_INVALID;
	}
	else if(VEH_VALID_DATA_STATUS == data)
	{
		return VEH_STATUS_VALID;
	}
	else
	{
		return VEH_STATUS_UNKNOWN;
	}
}

float get_eps_speed_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_EPS_SPEED);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_EPS_SPEED_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_eps_speed_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_EPS_SPEED);

	return check_data_status(i_var_32);
}

float get_dashboard_speed_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_DASHBOARD_SPEED);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_DASHBOARD_SPEED_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_dashboard_speed_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DASHBOARD_SPEED);

	return check_data_status(i_var_32);
}

float get_north_speed_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_NORTH_SPEED);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_3D_SPEED_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_north_speed_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_NORTH_SPEED);

	return check_data_status(i_var_32);
}

float get_east_speed_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_EAST_SPEED);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_3D_SPEED_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_east_speed_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_EAST_SPEED);

	return check_data_status(i_var_32);
}

float get_up_speed_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_UP_SPEED);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_3D_SPEED_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_up_speed_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_UP_SPEED);

	return check_data_status(i_var_32);
}

float get_yaw_angle_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_YAW_ANGLE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ATTITUDE_ANGLE_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_yaw_angle_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_YAW_ANGLE);

	return check_data_status(i_var_32);
}

float get_pitch_angle_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_PITCH_ANGLE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ATTITUDE_ANGLE_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_pitch_angle_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_PITCH_ANGLE);

	return check_data_status(i_var_32);
}

float get_roll_angle_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ROLL_ANGLE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ATTITUDE_ANGLE_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_roll_angle_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ROLL_ANGLE);

	return check_data_status(i_var_32);
}

float get_yaw_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_VEHICLE_YAW_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_yaw_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_VEHICLE_YAW_RATE);

	return check_data_status(i_var_32);
}

float get_steering_angle_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_STEERING_ANGLE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_STEERING_ANGLE_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_steering_angle_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_STEERING_ANGLE);

	return check_data_status(i_var_32);
}

VEH_GEAR_E judge_gear_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_GEAR_P_ON_MASK)
		return VEH_GEAR_P;
	else if(real_data & VEH_GEAR_R_ON_MASK)
		return VEH_GEAR_R;
	else if(real_data & VEH_GEAR_N_ON_MASK)
		return VEH_GEAR_N;
	else if(real_data & VEH_GEAR_D_ON_MASK)
		return VEH_GEAR_D;
	else if(real_data & VEH_GEAR_S_ON_MASK)
		return VEH_GEAR_S;
	else
		return VEH_GEAR_UNKNOWN;
}


VEH_GEAR_E get_gear_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_GEAR);

	return judge_gear_value(i_var_32);;
}

VEHICLE_STATUS_E get_gear_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_GEAR);

	return check_data_status(i_var_32);
}

VEH_IGN_E judge_ign_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_IGN_ACC_MASK)
		return VEH_IGN_ACC;
	else if(real_data & VEH_IGN_ON_MASK)
		return VEH_IGN_ON;
	else if(real_data & VEH_IGN_CRACK_MASK)
		return VEH_IGN_CRACK;
	else if(real_data == VEH_VALID_DATA_OFF)
		return VEH_IGN_OFF;
	else
		return VEH_IGN_UNKNOWN;
}

VEH_IGN_E get_ign_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_IGN);

	return judge_ign_value(i_var_32);
}

VEHICLE_STATUS_E get_ign_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_IGN);

	return check_data_status(i_var_32);
}

VEH_TURN_INDICATOR_E judge_turn_indicator_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_TURN_INDICATOR_RIGHT_ON_MASK)
		return VEH_TRUN_INDICATOR_RIGHT_ON;
	else if(real_data & VEH_TURN_INDICATOR_LEFT_ON_MASK)
		return VEH_TRUN_INDICATOR_LEFT_ON;
	else if(real_data == VEH_VALID_DATA_OFF)
		return VEH_TRUN_INDICATOR_ALL_OFF;
	else
		return VEH_TRUN_INDICATOR_UNKNOWN;
}

VEH_TURN_INDICATOR_E get_turn_indicator_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_TRUN_INDICATOR);

	return judge_turn_indicator_value(i_var_32);;
}

VEHICLE_STATUS_E get_turn_indicator_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_TRUN_INDICATOR);

	return check_data_status(i_var_32);
}

uint8_t is_door_front_right_on_value(int32_t data)
{
	if(data & VEH_DOOR_FRONT_RIGHT_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_rear_right_on_value(int32_t data)
{
	if(data & VEH_DOOR_REAR_RIGHT_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_front_left_on_value(int32_t data)
{
	if(data & VEH_DOOR_FRONT_LEFT_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_rear_left_on_value(int32_t data)
{
	if(data & VEH_DOOR_REAR_LEFT_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_trunk_on_value(int32_t data)
{
	if(data & VEH_DOOR_TRUNK_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_sunroof_on_value(int32_t data)
{
	if(data & VEH_DOOR_SUNROOF_ON_MASK)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

uint8_t is_door_all_off_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data == VEH_VALID_DATA_OFF)
		return VEH_DOOR_STATUS_OPEN;
	else
		return VEH_DOOR_STATUS_CLOSE;
}

VEH_DOOR_STATUS_E get_door_value(VEH_DOOR_E door)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR);
	switch(door)
	{
		case VEH_DOOR_FRONT_RIGHT:
			return is_door_front_right_on_value(i_var_32);
			break;
		case VEH_DOOR_REAR_RIGHT:
			return is_door_rear_right_on_value(i_var_32);
			break;
		case VEH_DOOR_FRONT_LEFT:
			return is_door_front_left_on_value(i_var_32);
			break;
		case VEH_DOOR_REAR_LEFT:
			return is_door_rear_left_on_value(i_var_32);
			break;
		case VEH_DOOR_TRUNK:
			return is_door_trunk_on_value(i_var_32);
			break;
		case VEH_DOOR_SUNROOF:
			return is_door_sunroof_on_value(i_var_32);
			break;
		default:
			return 0;
			break;
	}
}

VEHICLE_STATUS_E get_door_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR);

	return check_data_status(i_var_32);
}

VEH_PARKING_BRAKE_LEVER_E judge_parking_brake_lever_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_PARKING_BRAKE_LEVER_ON_MASK)
		return VEH_PARKING_BRAKE_LEVER_ON;
	else if(real_data == VEH_VALID_DATA_OFF)
		return VEH_PARKING_BRAKE_LEVER_OFF;
	else
		return VEH_PARKING_BRAKE_LEVER_UNKNOWN;
}

VEH_PARKING_BRAKE_LEVER_E get_parking_brake_lever_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_PARKING_BRAKE_LEVER);

	return judge_parking_brake_lever_value(i_var_32);;
}

VEHICLE_STATUS_E get_parking_brake_lever_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_PARKING_BRAKE_LEVER);

	return check_data_status(i_var_32);
}

VEH_HEADLAMP_E judge_headlamp_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_HEADLAMP_LOW_ON_MASK)
		return VEH_HEADLAMP_LOW;
	else if(real_data == VEH_HEADLAMP_HIGH_ON_MASK)
		return VEH_HEADLAMP_HIGH;
	else if(real_data == VEH_VALID_DATA_OFF)
		return VEH_HEADLAMP_OFF;
	else
		return VEH_HEADLAMP_UNKNOWN;
}

VEH_HEADLAMP_E get_headlamp_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_HEADLAMP);

	return judge_headlamp_value(i_var_32);;
}

VEHICLE_STATUS_E get_headlamp_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_HEADLAMP);

	return check_data_status(i_var_32);
}

VEH_WIPER_E judge_wiper_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_WIPER_INT_MASK)
		return VEH_WIPER_INT;
	else if(real_data == VEH_WIPER_LOW_MASK)
		return VEH_WIPER_LOW;
	else if(real_data == VEH_WIPER_HIGH_MASK)
		return VEH_WIPER_HIGH;
	else if(real_data == VEH_VALID_DATA_OFF)
		return VEH_WIPER_OFF;
	else
		return VEH_WIPER_UNKNOWN;
}

VEH_WIPER_E get_wiper_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_WIPER);

	return judge_wiper_value(i_var_32);;
}

VEHICLE_STATUS_E get_wiper_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_WIPER);

	return check_data_status(i_var_32);
}

VEH_PEPS_E judge_peps_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data == VEH_PEPS_UNLOCK_MASK)
		return VEH_PEPS_UNLOCK;
	else if(real_data == VEH_PEPS_LOCK_MASK)
		return VEH_PEPS_LOCK;
	else
		return VEH_WIPER_UNKNOWN;
}

VEH_PEPS_E get_peps_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_PEPS);

	return judge_wiper_value(i_var_32);;
}

VEHICLE_STATUS_E get_peps_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_PEPS);

	return check_data_status(i_var_32);
}

uint8_t is_door_lock_left_value(int32_t data)
{
	if(data & VEH_DOOR_LOCK_LEFT_MASK)
		return VEH_DOOR_LOCK_STATUS_UNLOCK;
	else
		return VEH_DOOR_LOCK_STATUS_LOCK;
}

uint8_t is_door_lock_right_value(int32_t data)
{

	if(data & VEH_DOOR_LOCK_RIGHT_MASK)
		return VEH_DOOR_LOCK_STATUS_UNLOCK;
	else
		return VEH_DOOR_LOCK_STATUS_LOCK;
}

VEH_DOOR_LOCK_STATUS_E get_door_lock_value(VEH_DOOR_LOCK_E door_lock)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR_LOCK);
	switch(door_lock)
	{
		case VEH_DOOR_LOCK_LEFT:
			return is_door_lock_left_value(i_var_32);
			break;
		case VEH_DOOR_LOCK_RIGHT:
			return is_door_lock_right_value(i_var_32);
			break;

		default:
			return 0;
			break;
	}
}

VEHICLE_STATUS_E get_door_lock_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR_LOCK);

	return check_data_status(i_var_32);
}

float get_veh_onboard_raw_roll_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ROLL_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_roll_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ROLL_RATE);

	return check_data_status(i_var_32);
}
float get_veh_onboard_raw_pitch_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_PITCH_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_pitch_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_PITCH_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_raw_yaw_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_YAW_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_yaw_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_YAW_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_roll_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ROLL_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_roll_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ROLL_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_pitch_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_PITCH_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_pitch_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_PITCH_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_yaw_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_YAW_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_yaw_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_YAW_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_raw_acc_x_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_X);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_acc_x_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_X);

	return check_data_status(i_var_32);
}

float get_veh_onboard_raw_acc_y_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_Y);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_acc_y_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_Y);

	return check_data_status(i_var_32);
}

float get_veh_onboard_raw_acc_z_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_Z);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_raw_acc_z_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RAW_ACC_Z);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_acc_x_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_X);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_acc_x_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_X);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_acc_y_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Y);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_acc_y_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Y);

	return check_data_status(i_var_32);
}

float get_veh_onboard_filtered_acc_z_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Z);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_filtered_acc_z_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Z);

	return check_data_status(i_var_32);
}

float get_veh_onboard_temperature_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_TEMPERATURE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_IMU_TEMPERATURE_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_temperature_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_TEMPERATURE);

	return check_data_status(i_var_32);
}

float get_veh_radius_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_RADIUS);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_RADIUS_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_raduis_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_RADIUS);

	return check_data_status(i_var_32);
}

float get_veh_filtered_yaw_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_FILTERED_YAW_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_filtered_yaw_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_FILTERED_YAW_RATE);

	return check_data_status(i_var_32);
}

float get_veh_onboard_radius_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RADIUS);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_RADIUS_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_onboard_radius_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_ONBOARD_RADIUS);

	return check_data_status(i_var_32);
}

float get_veh_two_src_filtered_yaw_rate_value(void)
{
	int32_t i_var_32;
	int16_t i_var_16;
	float f_var;
	i_var_32 = get_vehicle_info(VEH_TWO_SRC_FILTERED_YAW_RATE);
	i_var_16 = i_var_32 & VEH_VALID_DATA_MASK;
	f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
	return f_var;
}

VEHICLE_STATUS_E get_veh_two_src_filtered_yaw_rate_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_TWO_SRC_FILTERED_YAW_RATE);

	return check_data_status(i_var_32);
}

VEHICLE_MOTION_E judge_motion_value(int32_t data)
{
	int32_t real_data = data & VEH_VALID_DATA_MASK;
	if(real_data & VEH_MOTION_STATIONARY_MASK)
		return VEH_MOTION_STATUS_STATIONARY;
	else if(real_data & VEH_MOTION_MOVING_MASK)
		return VEH_MOTION_STATUS_MOVING;
	else
		return VEH_MOTION_STATUS_UNKNOWN;
}

VEHICLE_MOTION_E get_veh_motion_value(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_MOTION);

	return judge_motion_value(i_var_32);
}

VEHICLE_STATUS_E get_veh_motion_status(void)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_MOTION);

	return check_data_status(i_var_32);
}

#if defined(CTI_Z4_0)
//=================================================================
//=================================================================
//when set,you maybe use it

void set_vehicle_info(VEHICLE_INFO_E v_info ,int32_t data)
{
	if(VEH_INVALID_DATA_STATUS == data)
	{
		vehicle_info->R[v_info] = (VEH_INVALID_DATA_STATUS | (vehicle_info->R[v_info] & VEH_VALID_DATA_MASK));
	}
	else
	{
		vehicle_info->R[v_info] = data;
	}
}

void set_veh_eps_speed_value(float real_speed)
{
	uint16_t veh_speed;
	int32_t speed_value_and_status;
	veh_speed = (uint16_t)(real_speed * VEH_EPS_SPEED_FACTOR);
	speed_value_and_status = (int32_t)veh_speed & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_EPS_SPEED,speed_value_and_status);
}

void set_veh_eps_speed_invalid_value(void)
{
	set_vehicle_info(VEH_EPS_SPEED, VEH_INVALID_DATA_STATUS);
}

void set_veh_eps_speed_not_get_value(void)
{
	set_vehicle_info(VEH_EPS_SPEED, VEH_INIT_DATA_STATUS);
}

void set_veh_dashboard_speed_value(float real_speed)
{
	uint16_t veh_speed;
	int32_t speed_value_and_status;
	veh_speed = (uint16_t)(real_speed * VEH_EPS_SPEED_FACTOR);
	speed_value_and_status = (int32_t)veh_speed & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_DASHBOARD_SPEED,speed_value_and_status);
}

void set_veh_dashboard_speed_invalid_value(void)
{
	set_vehicle_info(VEH_DASHBOARD_SPEED, VEH_INVALID_DATA_STATUS);
}

void set_veh_dashboard_speed_not_get_value(void)
{
	set_vehicle_info(VEH_DASHBOARD_SPEED, VEH_INIT_DATA_STATUS);
}

void set_veh_north_speed_value(float north_speed)
{
	int16_t n_speed;
	int32_t speed_value_and_status;
	n_speed = (int16_t)(north_speed * VEH_3D_SPEED_FACTOR);
	speed_value_and_status = (int32_t)n_speed & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_NORTH_SPEED,speed_value_and_status);
}

void set_veh_north_speed_invalid_value(void)
{
	set_vehicle_info(VEH_NORTH_SPEED, VEH_INVALID_DATA_STATUS);
}

void set_veh_north_speed_not_get_value(void)
{
	set_vehicle_info(VEH_NORTH_SPEED, VEH_INIT_DATA_STATUS);
}

void set_veh_east_speed_value(float east_speed)
{
	int16_t e_speed;
	int32_t speed_value_and_status;
	e_speed = (int16_t)(east_speed * VEH_3D_SPEED_FACTOR);
	speed_value_and_status = (int32_t)e_speed & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_EAST_SPEED,speed_value_and_status);
}

void set_veh_east_speed_invalid_value(void)
{
	set_vehicle_info(VEH_EAST_SPEED, VEH_INVALID_DATA_STATUS);
}

void set_veh_east_speed_not_get_value(void)
{
	set_vehicle_info(VEH_EAST_SPEED, VEH_INIT_DATA_STATUS);
}

void set_veh_up_speed_value(float up_speed)
{
	int16_t u_speed;
	int32_t speed_value_and_status;
	u_speed = (int16_t)(up_speed * VEH_3D_SPEED_FACTOR);
	speed_value_and_status = (int32_t)u_speed & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_UP_SPEED,speed_value_and_status);
}

void set_veh_up_speed_invalid_value(void)
{
	set_vehicle_info(VEH_UP_SPEED, VEH_INVALID_DATA_STATUS);
}

void set_veh_up_speed_not_get_value(void)
{
	set_vehicle_info(VEH_UP_SPEED, VEH_INIT_DATA_STATUS);
}

void set_veh_steering_angle_value(float real_steering_angle)
{
	int16_t veh_steering_angle;
	int32_t steering_angle_value_and_status;
	veh_steering_angle = (int16_t)(real_steering_angle * VEH_STEERING_ANGLE_FACTOR);
	steering_angle_value_and_status = (int32_t)veh_steering_angle & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_STEERING_ANGLE,steering_angle_value_and_status);
}

void set_veh_steering_angle_invalid_value(void)
{
	set_vehicle_info(VEH_STEERING_ANGLE, VEH_INVALID_DATA_STATUS);
}

void set_veh_steering_angle_not_get_value(void)
{
	set_vehicle_info(VEH_STEERING_ANGLE, VEH_INIT_DATA_STATUS);
}

void set_veh_yaw_angle_value(float real_yaw_angle)
{
	int16_t veh_yaw_angle;
	int32_t yaw_angle_value_and_status;
	veh_yaw_angle = (int16_t)(real_yaw_angle * VEH_ATTITUDE_ANGLE_FACTOR);
	yaw_angle_value_and_status = (int32_t)veh_yaw_angle & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_YAW_ANGLE, yaw_angle_value_and_status);
}

void set_veh_yaw_angle_invalid_value(void)
{
	set_vehicle_info(VEH_YAW_ANGLE, VEH_INVALID_DATA_STATUS);
}

void set_veh_yaw_angle_not_get_value(void)
{
	set_vehicle_info(VEH_YAW_ANGLE, VEH_INIT_DATA_STATUS);
}

void set_veh_pitch_angle_value(float real_pitch_angle)
{
	int16_t veh_pitch_angle;
	int32_t pitch_angle_value_and_status;
	veh_pitch_angle = (int16_t)(real_pitch_angle * VEH_ATTITUDE_ANGLE_FACTOR);
	pitch_angle_value_and_status = (int32_t)veh_pitch_angle & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_PITCH_ANGLE, pitch_angle_value_and_status);
}

void set_veh_pitch_angle_invalid_value(void)
{
	set_vehicle_info(VEH_PITCH_ANGLE, VEH_INVALID_DATA_STATUS);
}

void set_veh_pitch_angle_not_get_value(void)
{
	set_vehicle_info(VEH_PITCH_ANGLE, VEH_INIT_DATA_STATUS);
}

void set_veh_roll_angle_value(float real_roll_angle)
{
	int16_t veh_roll_angle;
	int32_t roll_angle_value_and_status;
	veh_roll_angle = (int16_t)(real_roll_angle * VEH_ATTITUDE_ANGLE_FACTOR);
	roll_angle_value_and_status = (int32_t)veh_roll_angle & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ROLL_ANGLE, roll_angle_value_and_status);
}

void set_veh_roll_angle_invalid_value(void)
{
	set_vehicle_info(VEH_ROLL_ANGLE, VEH_INVALID_DATA_STATUS);
}

void set_veh_roll_angle_not_get_value(void)
{
	set_vehicle_info(VEH_ROLL_ANGLE, VEH_INIT_DATA_STATUS);
}

void set_veh_yaw_rate_value(float real_yawrate)
{
	int16_t veh_yawrate;
	int32_t yawrate_value_and_status;
	veh_yawrate = (int16_t)(real_yawrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	yawrate_value_and_status = (int32_t)veh_yawrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_VEHICLE_YAW_RATE,yawrate_value_and_status);
}

void set_veh_yaw_rate_invalid_value(void)
{
	set_vehicle_info(VEH_VEHICLE_YAW_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_yaw_rate_not_get_value(void)
{
	set_vehicle_info(VEH_VEHICLE_YAW_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_gear_p_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_P_ON_MASK);
}

void set_veh_gear_r_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_R_ON_MASK);
}

void set_veh_gear_n_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_N_ON_MASK);
}

void set_veh_gear_d_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_D_ON_MASK);
}

void set_veh_gear_s_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_S_ON_MASK);
}

void set_veh_gear_p_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_P_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_gear_r_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_R_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_gear_n_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_N_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_gear_d_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_D_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}
void set_veh_gear_s_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_GEAR_S_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_gear_invalid_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_INVALID_DATA_STATUS);
}

void set_veh_gear_not_get_value(void)
{
	set_vehicle_info(VEH_GEAR, VEH_INIT_DATA_STATUS);
}

void set_veh_ign_off_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_VALID_DATA_OFF);
}

void set_veh_ign_acc_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_ACC_MASK);
}

void set_veh_ign_on_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_ON_MASK);
}

void set_veh_ign_crack_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_CRACK_MASK);
}

void set_veh_ign_acc_invalid_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_ACC_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_ign_on_invalid_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_ON_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_ign_crack_invalid_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_IGN_CRACK_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_ign_invalid_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_INVALID_DATA_STATUS);
}

void set_veh_ign_not_get_value(void)
{
	set_vehicle_info(VEH_IGN, VEH_INIT_DATA_STATUS);
}

void set_veh_turn_indicator_off_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_VALID_DATA_OFF);
}

void set_veh_turn_indicator_right_on_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_TURN_INDICATOR_RIGHT_ON_MASK);
}

void set_veh_turn_indicator_left_on_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_TURN_INDICATOR_LEFT_ON_MASK);
}

void set_veh_turn_indicator_invalid_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_INVALID_DATA_STATUS);
}

void set_veh_turn_indicator_not_get_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_INIT_DATA_STATUS);
}

void set_veh_turn_indicator_right_on_invalid_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_TURN_INDICATOR_RIGHT_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_turn_indicator_left_on_invalid_value(void)
{
	set_vehicle_info(VEH_TRUN_INDICATOR, VEH_TURN_INDICATOR_LEFT_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_door_status_value_open(VEH_DOOR_E door)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR);
	switch(door)
	{
		case VEH_DOOR_FRONT_RIGHT:
			i_var_32 |= VEH_DOOR_FRONT_RIGHT_ON_MASK;
			break;
		case VEH_DOOR_REAR_RIGHT:
			i_var_32 |= VEH_DOOR_REAR_RIGHT_ON_MASK;
			break;
		case VEH_DOOR_FRONT_LEFT:
			i_var_32 |= VEH_DOOR_FRONT_LEFT_ON_MASK;
			break;
		case VEH_DOOR_REAR_LEFT:
			i_var_32 |= VEH_DOOR_REAR_LEFT_ON_MASK;
			break;
		case VEH_DOOR_TRUNK:
			i_var_32 |= VEH_DOOR_TRUNK_ON_MASK;
			break;
		case VEH_DOOR_SUNROOF:
			i_var_32 |= VEH_DOOR_SUNROOF_ON_MASK;
			break;
		default:
			break;
	}
	set_vehicle_info(VEH_DOOR, i_var_32);
}

void clear_veh_door_status_value_open(VEH_DOOR_E door)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR);
	switch(door)
	{
		case VEH_DOOR_FRONT_RIGHT:
			i_var_32 &= (0xFF^VEH_DOOR_FRONT_RIGHT_ON_MASK);
			break;
		case VEH_DOOR_REAR_RIGHT:
			i_var_32 &= (0xFF^VEH_DOOR_REAR_RIGHT_ON_MASK);
			break;
		case VEH_DOOR_FRONT_LEFT:
			i_var_32 &= (0xFF^VEH_DOOR_FRONT_LEFT_ON_MASK);
			break;
		case VEH_DOOR_REAR_LEFT:
			i_var_32 &= (0xFF^VEH_DOOR_REAR_LEFT_ON_MASK);
			break;
		case VEH_DOOR_TRUNK:
			i_var_32 &= (0xFF^VEH_DOOR_TRUNK_ON_MASK);
			break;
		case VEH_DOOR_SUNROOF:
			i_var_32 &= (0xFF^VEH_DOOR_SUNROOF_ON_MASK);
			break;
		default:
			break;
	}
	set_vehicle_info(VEH_DOOR, i_var_32);
}

void set_veh_door_status_invalid_value(void)
{
	set_vehicle_info(VEH_DOOR, VEH_INVALID_DATA_STATUS);
}

void set_veh_door_status_not_get_value(void)
{
	set_vehicle_info(VEH_DOOR, VEH_INIT_DATA_STATUS);
}

void set_veh_parking_brake_level_off_value(void)
{
	set_vehicle_info(VEH_PARKING_BRAKE_LEVER, VEH_VALID_DATA_OFF);
}

void set_veh_parking_brake_level_on_value(void)
{
	set_vehicle_info(VEH_PARKING_BRAKE_LEVER, VEH_PARKING_BRAKE_LEVER_ON_MASK);
}

void set_veh_parking_brake_level_invalid_value(void)
{
	set_vehicle_info(VEH_PARKING_BRAKE_LEVER, VEH_PARKING_BRAKE_LEVER_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_parking_brake_level_not_get_value(void)
{
	set_vehicle_info(VEH_PARKING_BRAKE_LEVER, VEH_INIT_DATA_STATUS);
}


void set_veh_headlamp_off_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_VALID_DATA_OFF);
}

void set_veh_headlamp_low_on_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_HEADLAMP_LOW_ON_MASK);
}

void set_veh_headlamp_high_on_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_HEADLAMP_HIGH_ON_MASK);
}

void set_veh_headlamp_invalid_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_INVALID_DATA_STATUS);
}

void set_veh_headlamp_not_get_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_INIT_DATA_STATUS);
}

void set_veh_headlamp_low_on_invalid_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_HEADLAMP_LOW_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_headlamp_high_on_invalid_value(void)
{
	set_vehicle_info(VEH_HEADLAMP, VEH_HEADLAMP_HIGH_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_wiper_off_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_VALID_DATA_OFF);
}

void set_veh_wiper_int_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_INT_MASK);
}

void set_veh_wiper_low_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_LOW_MASK);
}

void set_veh_wiper_high_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_HIGH_MASK);
}

void set_veh_wiper_invalid_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_INVALID_DATA_STATUS);
}

void set_veh_wiper_not_get_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_INIT_DATA_STATUS);
}

void set_veh_wiper_int_invalid_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_INT_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_wiper_low_invalid_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_LOW_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_wiper_high_invalid_value(void)
{
	set_vehicle_info(VEH_WIPER, VEH_WIPER_HIGH_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_peps_lock_value(void)
{
	set_vehicle_info(VEH_PEPS, VEH_PEPS_LOCK_MASK);
}

void set_veh_peps_unlock_value(void)
{
	set_vehicle_info(VEH_PEPS, VEH_PEPS_UNLOCK_MASK);
}

void set_veh_peps_invalid_value(void)
{
	set_vehicle_info(VEH_PEPS, VEH_INVALID_DATA_STATUS);
}

void set_veh_peps_not_get_value(void)
{
	set_vehicle_info(VEH_PEPS, VEH_INIT_DATA_STATUS);
}

void set_veh_door_lock_status_value_unlock(VEH_DOOR_LOCK_E door_lock)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR_LOCK);
	switch(door_lock)
	{
		case VEH_DOOR_LOCK_LEFT:
			i_var_32 |= VEH_DOOR_LOCK_LEFT_MASK;
			break;
		case VEH_DOOR_LOCK_RIGHT:
			i_var_32 |= VEH_DOOR_LOCK_RIGHT_MASK;
			break;

		default:
			break;
	}
	i_var_32 = i_var_32 & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_DOOR_LOCK, i_var_32);
}

void clear_veh_door_lock_status_value_unlock(VEH_DOOR_LOCK_E door_lock)
{
	int32_t i_var_32;
	i_var_32 = get_vehicle_info(VEH_DOOR_LOCK);
	switch(door_lock)
	{
		case VEH_DOOR_LOCK_LEFT:
			i_var_32 &= (0xFF^VEH_DOOR_LOCK_LEFT_MASK);
			break;
		case VEH_DOOR_LOCK_RIGHT:
			i_var_32 &= (0xFF^VEH_DOOR_LOCK_RIGHT_MASK);
			break;

		default:
			break;
	}
	i_var_32 = i_var_32 & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_DOOR_LOCK, i_var_32);
}

void set_veh_door_lock_status_invalid_value(void)
{
	set_vehicle_info(VEH_DOOR_LOCK, VEH_INVALID_DATA_STATUS);
}

void set_veh_door_lock_status_not_get_value(void)
{
	set_vehicle_info(VEH_DOOR_LOCK, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_roll_rate_value(float real_rollrate)
{
	int16_t veh_rollrate;
	int32_t rollrate_value_and_status;
	veh_rollrate = (int16_t)(real_rollrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	rollrate_value_and_status = (int32_t)veh_rollrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_ROLL_RATE, rollrate_value_and_status);
}

void set_veh_onboard_raw_roll_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ROLL_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_roll_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ROLL_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_pitch_rate_value(float real_pitchrate)
{
	int16_t veh_pitchrate;
	int32_t picthrate_value_and_status;
	veh_pitchrate = (int16_t)(real_pitchrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	picthrate_value_and_status = (int32_t)veh_pitchrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_PITCH_RATE,picthrate_value_and_status);
}

void set_veh_onboard_raw_pitch_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_PITCH_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_pitch_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_PITCH_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_yaw_rate_value(float real_yawrate)
{
	int16_t veh_yawrate;
	int32_t yawrate_value_and_status;
	veh_yawrate = (int16_t)(real_yawrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	yawrate_value_and_status = (int32_t)veh_yawrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_YAW_RATE,yawrate_value_and_status);
}

void set_veh_onboard_raw_yaw_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_YAW_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_yaw_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_YAW_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_roll_rate_value(float real_rollrate)
{
	int16_t veh_rollrate;
	int32_t rollrate_value_and_status;
	veh_rollrate = (int16_t)(real_rollrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	rollrate_value_and_status = (int32_t)veh_rollrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_ROLL_RATE, rollrate_value_and_status);
}

void set_veh_onboard_filtered_roll_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ROLL_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_roll_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ROLL_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_pitch_rate_value(float real_pitchrate)
{
	int16_t veh_pitchrate;
	int32_t picthrate_value_and_status;
	veh_pitchrate = (int16_t)(real_pitchrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	picthrate_value_and_status = (int32_t)veh_pitchrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_PITCH_RATE,picthrate_value_and_status);
}

void set_veh_onboard_filtered_pitch_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_PITCH_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_pitch_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_PITCH_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_yaw_rate_value(float real_yawrate)
{
	int16_t veh_yawrate;
	int32_t yawrate_value_and_status;
	veh_yawrate = (int16_t)(real_yawrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	yawrate_value_and_status = (int32_t)veh_yawrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_YAW_RATE,yawrate_value_and_status);
}

void set_veh_onboard_filtered_yaw_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_YAW_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_yaw_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_YAW_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_acc_x_value(float real_acc_x)
{
	int16_t veh_acc_x;
	int32_t acc_x_value_and_status;
	veh_acc_x = (int16_t)(real_acc_x * VEH_ACC_XYZ_FACTOR);
	acc_x_value_and_status = (int32_t)veh_acc_x & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_X, acc_x_value_and_status);
}

void set_veh_onboard_raw_acc_x_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_X, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_acc_x_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_X, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_acc_y_value(float real_acc_y)
{
	int16_t veh_acc_y;
	int32_t acc_y_value_and_status;
	veh_acc_y = (int16_t)(real_acc_y * VEH_ACC_XYZ_FACTOR);
	acc_y_value_and_status = (int32_t)veh_acc_y & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Y, acc_y_value_and_status);
}

void set_veh_onboard_raw_acc_y_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Y, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_acc_y_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Y, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_raw_acc_z_value(float real_acc_z)
{
	int16_t veh_acc_z;
	int32_t acc_z_value_and_status;
	veh_acc_z = (int16_t)(real_acc_z * VEH_ACC_XYZ_FACTOR);
	acc_z_value_and_status = (int32_t)veh_acc_z & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Z, acc_z_value_and_status);
}

void set_veh_onboard_raw_acc_z_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Z, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_raw_acc_z_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RAW_ACC_Z, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_x_value(float real_acc_x)
{
	int16_t veh_acc_x;
	int32_t acc_x_value_and_status;
	veh_acc_x = (int16_t)(real_acc_x * VEH_ACC_XYZ_FACTOR);
	acc_x_value_and_status = (int32_t)veh_acc_x & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_X, acc_x_value_and_status);
}

void set_veh_onboard_filtered_acc_x_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_X, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_x_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_X, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_y_value(float real_acc_y)
{
	int16_t veh_acc_y;
	int32_t acc_y_value_and_status;
	veh_acc_y = (int16_t)(real_acc_y * VEH_ACC_XYZ_FACTOR);
	acc_y_value_and_status = (int32_t)veh_acc_y & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Y, acc_y_value_and_status);
}

void set_veh_onboard_filtered_acc_y_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Y, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_y_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Y, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_z_value(float real_acc_z)
{
	int16_t veh_acc_z;
	int32_t acc_z_value_and_status;
	veh_acc_z = (int16_t)(real_acc_z * VEH_ACC_XYZ_FACTOR);
	acc_z_value_and_status = (int32_t)veh_acc_z & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Z, acc_z_value_and_status);
}

void set_veh_onboard_filtered_acc_z_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Z, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_filtered_acc_z_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_FILTERED_ACC_Z, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_temperature_value(float real_temperature)
{
	int16_t veh_onboard_temperature;
	int32_t temperature_value_and_status;
	veh_onboard_temperature = (int16_t)(real_temperature * VEH_IMU_TEMPERATURE_FACTOR);
	temperature_value_and_status = (int32_t)veh_onboard_temperature & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_TEMPERATURE,temperature_value_and_status);
}

void set_veh_onboard_temperature_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_TEMPERATURE, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_temperature_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_TEMPERATURE, VEH_INIT_DATA_STATUS);
}

void set_veh_radius_value(float radius)
{
	int16_t veh_radius;
	int32_t radius_value_and_status;
	veh_radius = (int16_t)(radius * VEH_RADIUS_FACTOR);
	radius_value_and_status = (int32_t)veh_radius & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_RADIUS,radius_value_and_status);
}

void set_veh_radius_status_invalid_value(void)
{
	set_vehicle_info(VEH_RADIUS, VEH_INVALID_DATA_STATUS);
}

void set_veh_radius_status_not_get_value(void)
{
	set_vehicle_info(VEH_RADIUS, VEH_INIT_DATA_STATUS);
}

void set_veh_filtered_yaw_rate_value(float real_yawrate)
{
	int16_t veh_yawrate;
	int32_t yawrate_value_and_status;
	veh_yawrate = (int16_t)(real_yawrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	yawrate_value_and_status = (int32_t)veh_yawrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_FILTERED_YAW_RATE,yawrate_value_and_status);
}

void set_veh_filtered_yaw_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_FILTERED_YAW_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_filtered_yaw_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_FILTERED_YAW_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_onboard_radius_value(float radius)
{
	int16_t veh_radius;
	int32_t radius_value_and_status;
	veh_radius = (int16_t)(radius * VEH_RADIUS_FACTOR);
	radius_value_and_status = (int32_t)veh_radius & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_ONBOARD_RADIUS,radius_value_and_status);
}

void set_veh_onboard_radius_status_invalid_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RADIUS, VEH_INVALID_DATA_STATUS);
}

void set_veh_onboard_radius_status_not_get_value(void)
{
	set_vehicle_info(VEH_ONBOARD_RADIUS, VEH_INIT_DATA_STATUS);
}

void set_veh_two_src_filtered_yaw_rate_value(float real_yawrate)
{
	int16_t veh_yawrate;
	int32_t yawrate_value_and_status;
	veh_yawrate = (int16_t)(real_yawrate * VEH_GY_ROLL_PITCH_YAW_FACTOR);
	yawrate_value_and_status = (int32_t)veh_yawrate & VEH_VALID_DATA_MASK;
	set_vehicle_info(VEH_TWO_SRC_FILTERED_YAW_RATE,yawrate_value_and_status);
}

void set_veh_two_src_filtered_yaw_rate_status_invalid_value(void)
{
	set_vehicle_info(VEH_TWO_SRC_FILTERED_YAW_RATE, VEH_INVALID_DATA_STATUS);
}

void set_veh_two_src_filtered_yaw_rate_status_not_get_value(void)
{
	set_vehicle_info(VEH_TWO_SRC_FILTERED_YAW_RATE, VEH_INIT_DATA_STATUS);
}

void set_veh_motion_status_stationary_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_MOTION_STATIONARY_MASK);
}

void set_veh_motion_status_moving_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_MOTION_MOVING_MASK);
}

void set_veh_motion_status_stationary_invalid_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_MOTION_STATIONARY_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_motion_status_moving_invalid_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_MOTION_MOVING_INVALID_MASK | VEH_INVALID_DATA_STATUS);
}

void set_veh_motion_status_invalid_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_INVALID_DATA_STATUS);
}

void set_veh_motion_status_not_get_value(void)
{
	set_vehicle_info(VEH_MOTION, VEH_INIT_DATA_STATUS);
}
//====================================================================================

static void get_str_gear(VEHICLE_STATUS_E gear,char output[])
{
	char *str_gear[VEH_GEAR_UNKNOWN + 1] = {"P","R","N","D","S","Unknown"};
	sprintf(output,str_gear[gear]);
}
static void get_str_ign(VEH_IGN_E ign,char output[])
{
	char *str_ign[VEH_IGN_UNKNOWN + 1] = {"OFF","ACC","ON","CRACK","Unknown"};
	sprintf(output,str_ign[ign]);
}

static void get_str_turn_indicator(VEH_TURN_INDICATOR_E turn_indicator,char output[])
{
	char *str_turn_indicator[VEH_TRUN_INDICATOR_UNKNOWN + 1] = {"OFF","Right ON","Left ON","Unknown"};
	sprintf(output,str_turn_indicator[turn_indicator]);
}

static void get_str_parking_brake_lever(VEH_PARKING_BRAKE_LEVER_E parking_brake_lever,char output[])
{
	char *str_parking_brake_lever[VEH_PARKING_BRAKE_LEVER_UNKNOWN + 1] = {"OFF","ON","Unknown"};
	sprintf(output,str_parking_brake_lever[parking_brake_lever]);
}
static void get_str_headlamp(VEH_HEADLAMP_E headlamp,char output[])
{
	char *str_headlamp[VEH_HEADLAMP_UNKNOWN + 1] = {"OFF","LOW","HIGH","Unknown"};
	sprintf(output,str_headlamp[headlamp]);
}

static void get_str_wiper(VEH_WIPER_E wiper,char output[])
{
	char *str_wiper[VEH_WIPER_UNKNOWN + 1] = {"OFF","INT","LOW","HIGH","Unknown"};
	sprintf(output,str_wiper[wiper]);
}

static void get_str_door(int32_t value,char output[])
{
	char temp_str[] = "";

	if(0 == (value & VEH_VALID_DATA_MASK))
	{
		strcat(temp_str,"Door OFF ");
	}
	else
	{
		if(is_door_front_right_on_value(value))
			strcat(temp_str,"FR:ON\t");
		else
			strcat(temp_str,"FR:OFF\t");
		if(is_door_rear_right_on_value(value))
			strcat(temp_str,"RR:ON\t");
		else
			strcat(temp_str,"RR:OFF\t");
		if(is_door_front_left_on_value(value))
			strcat(temp_str,"FL:ON\t");
		else
			strcat(temp_str,"FL:OFF\t");
		if(is_door_rear_left_on_value(value))
			strcat(temp_str,"RL:ON\t");
		else
			strcat(temp_str,"RL:OFF\t");
		if(is_door_trunk_on_value(value))
			strcat(temp_str,"Trunk ON\t");
		if(is_door_sunroof_on_value(value))
			strcat(temp_str,"Sunroof ON\t");
	}
	sprintf(output,temp_str);

}

static void get_str_peps(VEH_PEPS_E peps,char output[])
{
	char *str_peps[VEH_PEPS_UNKNOWN + 1] = {"Lock","Unlock","Unknown"};
	sprintf(output,str_peps[peps]);
}

static void get_str_door_lock(int32_t value,char output[])
{
	char temp_str[] = "";


	if(is_door_lock_left_value(value))
		strcat(temp_str,"L:Unlock\t");
	else
		strcat(temp_str,"L:Lock\t");
	if(is_door_lock_right_value(value))
		strcat(temp_str,"R:Unlock\t");
	else
		strcat(temp_str,"R:Lock\t");

	sprintf(output,temp_str);

}

static void get_str_motion(VEHICLE_MOTION_E motion_status,char output[])
{
	char *str_motion_status[VEH_MOTION_STATUS_UNKNOWN + 1] = {"Stationary","Moving","Unknown"};
	sprintf(output,str_motion_status[motion_status]);
}

static void get_str_vehicle_value(VEHICLE_INFO_E v_info,char output[])
{
	float f_var = 0.0;
	int32_t i_var_32 = 0;
	int16_t i_var_16 = 0;
	switch(v_info)
	{
		case VEH_EPS_SPEED:
			f_var = ((float)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_EPS_SPEED_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_DASHBOARD_SPEED:
			f_var = ((float)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_DASHBOARD_SPEED_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_VEHICLE_YAW_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_STEERING_ANGLE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_STEERING_ANGLE_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_GEAR:
			i_var_32 = get_vehicle_info(v_info);
			get_str_gear(judge_gear_value(i_var_32),output);
			break;

		case VEH_IGN:
			i_var_32 = get_vehicle_info(v_info);
			get_str_ign(judge_ign_value(i_var_32),output);
			break;

		case VEH_TRUN_INDICATOR:
			i_var_32 = get_vehicle_info(v_info);
			get_str_turn_indicator(judge_turn_indicator_value(i_var_32),output);
			break;

		case VEH_DOOR:
			i_var_32 = get_vehicle_info(v_info);
			get_str_door(i_var_32,output);
			break;

		case VEH_PARKING_BRAKE_LEVER:
			i_var_32 = get_vehicle_info(v_info);
			get_str_parking_brake_lever(judge_parking_brake_lever_value(i_var_32),output);
			break;

		case VEH_HEADLAMP:
			i_var_32 = get_vehicle_info(v_info);
			get_str_headlamp(judge_headlamp_value(i_var_32),output);
			break;

		case VEH_WIPER:
			i_var_32 = get_vehicle_info(v_info);
			get_str_wiper(judge_wiper_value(i_var_32),output);
			break;

		case VEH_NORTH_SPEED:
			f_var = ((float)(int16_t)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_3D_SPEED_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_EAST_SPEED:
			f_var = ((float)(int16_t)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_3D_SPEED_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_UP_SPEED:
			f_var = ((float)(int16_t)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_3D_SPEED_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_YAW_ANGLE:
			f_var = ((float)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_ATTITUDE_ANGLE_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_PITCH_ANGLE:
			f_var = ((float)(int16_t)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_ATTITUDE_ANGLE_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ROLL_ANGLE:
			f_var = ((float)(int16_t)(get_vehicle_info(v_info) & VEH_VALID_DATA_MASK)/VEH_ATTITUDE_ANGLE_FACTOR);
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_PEPS:
			i_var_32 = get_vehicle_info(v_info);
			get_str_peps(judge_peps_value(i_var_32),output);
			break;

		case VEH_DOOR_LOCK:
			i_var_32 = get_vehicle_info(v_info);
			get_str_door_lock(i_var_32,output);
			break;

		case VEH_ONBOARD_RAW_ROLL_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_RAW_PITCH_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_RAW_YAW_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_ROLL_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_PITCH_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_YAW_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_RAW_ACC_X:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_RAW_ACC_Y:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_RAW_ACC_Z:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_ACC_X:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_ACC_Y:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_FILTERED_ACC_Z:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_ACC_XYZ_FACTOR;
			sprintf(output, "%.3f", f_var);
			break;

		case VEH_ONBOARD_TEMPERATURE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_IMU_TEMPERATURE_FACTOR;
			sprintf(output, "%.1f", f_var);
			break;

		case VEH_RADIUS:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
//			f_var = (float)i_var_16/VEH_RADIUS_FACTOR;
			sprintf(output, "%d", i_var_16);
			break;

		case VEH_FILTERED_YAW_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_ONBOARD_RADIUS:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
//			f_var = (float)i_var_16/VEH_RADIUS_FACTOR;
			sprintf(output, "%d", i_var_16);
			break;

		case VEH_TWO_SRC_FILTERED_YAW_RATE:
			i_var_32 = get_vehicle_info(v_info);
			i_var_16 = (int16_t)(i_var_32 & VEH_VALID_DATA_MASK);
			f_var = (float)i_var_16/VEH_GY_ROLL_PITCH_YAW_FACTOR;
			sprintf(output, "%.2f", f_var);
			break;

		case VEH_MOTION:
			i_var_32 = get_vehicle_info(v_info);
			get_str_motion(judge_motion_value(i_var_32),output);
			break;

		default:
			sprintf(output, "Invalid");
			break;
	}
}

static void get_str_status(VEHICLE_STATUS_E s,char* output)
{
	switch(s)
	{
	case VEH_STATUS_VALID:
		sprintf(output,"Valid");
		break;
	case VEH_STATUS_INVALID:
		sprintf(output,"Invalid");
		break;
	case VEH_STATUS_NOT_GET_DATA:
		sprintf(output,"Not get data");
		break;
	case VEH_STATUS_UNKNOWN:
		sprintf(output,"Unknown");
		break;
	}
}

static void get_str_vehicle_status(VEHICLE_INFO_E v_info,char* output)
{
	VEHICLE_STATUS_E status;
	status = check_data_status(get_vehicle_info(v_info) & VEH_VALID_STATUS_MASK);
	get_str_status(status,output);
}

static void _vehicle_list(char** args, int count)
{
		char value[40];
		char status[40];

		if((count > 1))
		{
			if(!strcmp(args[1],"speed"))
			{
				if(count > 2){
					float spd = strtof(args[2], NULL);
					set_veh_eps_speed_value(spd);
				}
				PRINTF("EPS Speed:\t\t%f\t\n" ,get_eps_speed_value());
				PRINTF("Dashboard Speed:\t\t%f\t\n" ,get_dashboard_speed_value());
			}
			else if(!strcmp(args[1],"yawrate"))
			{
				PRINTF("Yawrate:\t\t%f\t\n" ,get_yaw_rate_value());
			}
		}
		else
		{
			memset(value, 0, 40);
			get_str_vehicle_value(VEH_EPS_SPEED,value);
			get_str_vehicle_status(VEH_EPS_SPEED,status);
			PRINTF("EPS Speed:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_DASHBOARD_SPEED,value);
			get_str_vehicle_status(VEH_DASHBOARD_SPEED,status);
			PRINTF("Dashboard Speed:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_VEHICLE_YAW_RATE,value);
			get_str_vehicle_status(VEH_VEHICLE_YAW_RATE,status);
			PRINTF("Vehicle Yaw Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_STEERING_ANGLE,value);
			get_str_vehicle_status(VEH_STEERING_ANGLE,status);
			PRINTF("Streeing Angle:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_GEAR,value);
			get_str_vehicle_status(VEH_GEAR,status);
			PRINTF("Gear:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_IGN,value);
			get_str_vehicle_status(VEH_IGN,status);
			PRINTF("Ign:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_TRUN_INDICATOR,value);
			get_str_vehicle_status(VEH_TRUN_INDICATOR,status);
			PRINTF("Turn Indicator:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_DOOR,value);
			get_str_vehicle_status(VEH_DOOR,status);
			PRINTF("Door:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_PARKING_BRAKE_LEVER,value);
			get_str_vehicle_status(VEH_PARKING_BRAKE_LEVER,status);
			PRINTF("Parking Brake Lever:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_HEADLAMP,value);
			get_str_vehicle_status(VEH_HEADLAMP,status);
			PRINTF("Headlamp:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_WIPER,value);
			get_str_vehicle_status(VEH_WIPER,status);
			PRINTF("Wiper:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_NORTH_SPEED,value);
			get_str_vehicle_status(VEH_NORTH_SPEED,status);
			PRINTF("North Speed:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_EAST_SPEED,value);
			get_str_vehicle_status(VEH_EAST_SPEED,status);
			PRINTF("East Speed:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_UP_SPEED,value);
			get_str_vehicle_status(VEH_UP_SPEED,status);
			PRINTF("Up Speed:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_YAW_ANGLE,value);
			get_str_vehicle_status(VEH_YAW_ANGLE,status);
			PRINTF("Yaw Angle:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_PITCH_ANGLE,value);
			get_str_vehicle_status(VEH_PITCH_ANGLE,status);
			PRINTF("Pitch Angle:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ROLL_ANGLE,value);
			get_str_vehicle_status(VEH_ROLL_ANGLE,status);
			PRINTF("Roll Angle:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_PEPS,value);
			get_str_vehicle_status(VEH_PEPS,status);
			PRINTF("PEPS:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_DOOR_LOCK,value);
			get_str_vehicle_status(VEH_DOOR_LOCK,status);
			PRINTF("Door Lock:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_ROLL_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_ROLL_RATE,status);
			PRINTF("OnBoard Raw Roll Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_PITCH_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_PITCH_RATE,status);
			PRINTF("OnBoard Raw Pitch Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_YAW_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_YAW_RATE,status);
			PRINTF("OnBoard Raw Yaw Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_ROLL_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_ROLL_RATE,status);
			PRINTF("OnBoard Filtered Roll Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_PITCH_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_PITCH_RATE,status);
			PRINTF("OnBoard Filtered Pitch Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_YAW_RATE,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_YAW_RATE,status);
			PRINTF("OnBoard Filtered Yaw Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_ACC_X,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_ACC_X,status);
			PRINTF("OnBoard Raw Acc X:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_ACC_Y,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_ACC_Y,status);
			PRINTF("OnBoard Raw Acc Y:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RAW_ACC_Z,value);
			get_str_vehicle_status(VEH_ONBOARD_RAW_ACC_Z,status);
			PRINTF("OnBoard Raw Acc Z:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_ACC_X,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_ACC_X,status);
			PRINTF("OnBoard Filtered Acc X:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_ACC_Y,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_ACC_Y,status);
			PRINTF("OnBoard Filtered Acc Y:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_FILTERED_ACC_Z,value);
			get_str_vehicle_status(VEH_ONBOARD_FILTERED_ACC_Z,status);
			PRINTF("OnBoard Filtered Acc Z:\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_TEMPERATURE,value);
			get_str_vehicle_status(VEH_ONBOARD_TEMPERATURE,status);
			PRINTF("OnBoard Temperature:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_RADIUS,value);
			get_str_vehicle_status(VEH_RADIUS,status);
			PRINTF("Radius:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_FILTERED_YAW_RATE,value);
			get_str_vehicle_status(VEH_FILTERED_YAW_RATE,status);
			PRINTF("Filter Yaw Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_ONBOARD_RADIUS,value);
			get_str_vehicle_status(VEH_ONBOARD_RADIUS,status);
			PRINTF("OnBoard Radius:\t\t\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_TWO_SRC_FILTERED_YAW_RATE,value);
			get_str_vehicle_status(VEH_TWO_SRC_FILTERED_YAW_RATE,status);
			PRINTF("Two Source Filtered Yaw Rate:\t%s\t,Status:\t%s\n" ,value,status);

			memset(value, 0, 40);
			get_str_vehicle_value(VEH_MOTION,value);
			get_str_vehicle_status(VEH_MOTION,status);
			PRINTF("Motion:\t\t\t%s\t,Status:\t%s\n" ,value,status);
		}

}
#endif
