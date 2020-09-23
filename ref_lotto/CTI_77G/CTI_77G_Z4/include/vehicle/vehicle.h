/*
 * vehicle.h
 *
 *  Created on: 2018/6/26
 *      Author: user
 */

#ifndef VEHICLE_VEHICLE_H_
#define VEHICLE_VEHICLE_H_

//================================================================
//STATUS MASK
#define VEH_INIT_DATA_STATUS					0x80000000
#define	VEH_INVALID_DATA_STATUS					0x40000000
#define VEH_VALID_DATA_STATUS					0x00000000

//DATA MASK
#define VEH_VALID_DATA_OFF						0x00000000
//EPS SPEED
//DASHBOARD SPEED
//YAWRATE
//STEERING ANGLE
//GEAR
#define VEH_GEAR_P_ON_MASK						0x00000001
#define VEH_GEAR_R_ON_MASK						0x00000002
#define VEH_GEAR_N_ON_MASK						0x00000004
#define VEH_GEAR_D_ON_MASK						0x00000008
#define VEH_GEAR_S_ON_MASK						0x00000010
#define VEH_GEAR_P_INVALID_MASK					0x00010000
#define VEH_GEAR_R_INVALID_MASK					0x00020000
#define VEH_GEAR_N_INVALID_MASK					0x00040000
#define VEH_GEAR_D_INVALID_MASK					0x00080000
#define VEH_GEAR_S_INVALID_MASK					0x00100000
//IGN
#define VEH_IGN_ACC_MASK						0x00000001
#define VEH_IGN_ON_MASK							0x00000002
#define VEH_IGN_CRACK_MASK						0x00000004
#define VEH_IGN_ACC_INVALID_MASK				0x00010000
#define VEH_IGN_ON_INVALID_MASK					0x00020000
#define VEH_IGN_CRACK_INVALID_MASK				0x00040000
//TURN INDICATOR
#define VEH_TURN_INDICATOR_RIGHT_ON_MASK		0x00000001
#define VEH_TURN_INDICATOR_LEFT_ON_MASK			0x00000002
#define VEH_TURN_INDICATOR_RIGHT_INVALID_MASK	0x00010000
#define VEH_TURN_INDICATOR_LEFT_INVALID_MASK	0x00020000
//DOOR
#define VEH_DOOR_FRONT_RIGHT_ON_MASK			0x00000001
#define VEH_DOOR_REAR_RIGHT_ON_MASK				0x00000002
#define VEH_DOOR_FRONT_LEFT_ON_MASK				0x00000004
#define VEH_DOOR_REAR_LEFT_ON_MASK				0x00000008
#define VEH_DOOR_TRUNK_ON_MASK					0x00000010
#define VEH_DOOR_SUNROOF_ON_MASK				0x00000020
#define VEH_DOOR_FRONT_RIGHT_INVALID_MASK		0x00010000
#define VEH_DOOR_REAR_RIGHT_INVALID_MASK		0x00020000
#define VEH_DOOR_FRONT_LEFT_INVALID_MASK		0x00040000
#define VEH_DOOR_REAR_LEFT_INVALID_MASK			0x00080000
#define VEH_DOOR_TRUNK_INVALID_MASK				0x00100000
#define VEH_DOOR_SUNROOF_INVALID_MASK			0x00200000
///PARKING BRAKE LEVER
#define VEH_PARKING_BRAKE_LEVER_ON_MASK			0x00000001
#define VEH_PARKING_BRAKE_LEVER_INVALID_MASK	0x00010000
///HEADLAMP
#define VEH_HEADLAMP_LOW_ON_MASK				0x00000001
#define VEH_HEADLAMP_HIGH_ON_MASK				0x00000002
#define VEH_HEADLAMP_LOW_INVALID_MASK			0x00010000
#define VEH_HEADLAMP_HIGH_INVALID_MASK			0x00020000
///WIPER
#define VEH_WIPER_INT_MASK						0x00000001
#define VEH_WIPER_LOW_MASK						0x00000002
#define VEH_WIPER_HIGH_MASK						0x00000004
#define VEH_WIPER_INT_INVALID_MASK				0x00010000
#define VEH_WIPER_LOW_INVALID_MASK				0x00020000
#define VEH_WIPER_HIGH_INVALID_MASK				0x00040000
//PEPS
#define VEH_PEPS_LOCK_MASK						0x00000000
#define VEH_PEPS_UNLOCK_MASK					0x00000001
//DOOR LOCK
#define VEH_DOOR_LOCK_LEFT_MASK					0x00000001
#define VEH_DOOR_LOCK_RIGHT_MASK				0x00000002
//MOTION
#define VEH_MOTION_STATIONARY_MASK				0x00000001
#define VEH_MOTION_MOVING_MASK					0x00000002
#define VEH_MOTION_STATIONARY_INVALID_MASK		0x00010000
#define VEH_MOTION_MOVING_INVALID_MASK			0x00020000
//ALL MASK
#define VEH_VALID_DATA_MASK						0x0000FFFF
#define VEH_VALID_STATUS_MASK					0xFFFF0000
//================================================================
//================================================================
//SHIFT POSITITON
//GEAR
#define VEH_GEAR_P_ON_SHIFT							0
#define VEH_GEAR_R_ON_SHIFT							1
#define VEH_GEAR_N_ON_SHIFT							1
#define VEH_GEAR_D_ON_SHIFT							3
#define VEH_GEAR_S_ON_SHIFT							4
#define VEH_GEAR_P_INVALID_SHIFT					16
#define VEH_GEAR_R_INVALID_SHIFT					17
#define VEH_GEAR_N_INVALID_SHIFT					18
#define VEH_GEAR_D_INVALID_SHIFT					19
#define VEH_GEAR_S_INVALID_SHIFT					20
//IGN
#define VEH_IGN_ACC_SHIFT							0
#define VEH_IGN_ON_SHIFT							1
#define VEH_IGN_CRACK_SHIFT							2
#define VEH_IGN_ACC_INVALID_SHIFT					16
#define VEH_IGN_ON_INVALID_SHIFT					17
#define VEH_IGN_CRACK_INVALID_SHIFT					18
//TURN INDICATOR
#define VEH_TURN_INDICATOR_RIGHT_ON_SHIFT			0
#define VEH_TURN_INDICATOR_LEFT_ON_SHIFT			1
#define VEH_TURN_INDICATOR_RIGHT_INVALID_SHIFT		16
#define VEH_TURN_INDICATOR_LEFT_INVALID_SHIFT		17
//DOOR
#define VEH_DOOR_FORNT_RIGHT_ON_SHIFT				0
#define VEH_DOOR_REAR_RIGHT_ON_SHIFT				1
#define VEH_DOOR_FORNT_LEFT_ON_SHIFT				2
#define VEH_DOOR_REAR_LEFT_ON_SHIFT					3
#define VEH_DOOR_TRUNK_ON_SHIFT						4
#define VEH_DOOR_SUNROOF_ON_SHIFT					5
#define VEH_DOOR_FORNT_RIGHT_INVALID_SHIFT			16
#define VEH_DOOR_REAR_RIGHT_INVALID_SHIFT			17
#define VEH_DOOR_FORNT_LEFT_INVALID_SHIFT			18
#define VEH_DOOR_REAR_LEFT_INVALID_SHIFT			19
#define VEH_DOOR_TRUNK_INVALID_SHIFT				20
#define VEH_DOOR_SUNROOF_INVALID_SHIFT				21
///PARKING BRAKE LEVER
#define VEH_PARKING_BRAKE_LEVER_ON_SHIFT			0
#define VEH_PARKING_BRAKE_LEVER_ON_INVALID_SHIFT	16
///HEADLAMP
#define VEH_HEADLAMP_LOW_ON_SHIFT					0
#define VEH_HEADLAMP_HIGH_ON_SHIFT					1
#define VEH_HEADLAMP_LOW_ON_INVALID_SHIFT			16
#define VEH_HEADLAMP_HIGH_ON_INVALID_SHIFT			17
///WIPER
#define VEH_WIPER_INT_SHIFT							0
#define VEH_WIPER_LOW_SHIFT							1
#define VEH_WIPER_HIGH_SHIFT						2
#define VEH_WIPER_INT_INVALID_SHIFT					16
#define VEH_WIPER_LOW_INVALID_SHIFT					17
#define VEH_WIPER_HIGH_INVALID_SHIFT				18
//DOOR LOCK
#define VEH_DOOR_LOCK_LEFT_SHIFT					0
#define VEH_DOOR_LOCK_RIGHT_SHIFT					1
//MOTION
#define VEH_MOTION_STATIONARY_SHIFT					0
#define VEH_MOTION_MOVING_SHIFT						1
#define VEH_MOTION_STATIONARY_INVALID_SHIFT			16
#define VEH_MOTION_MOVING_INVALID_SHIFT				17
//=====================================================================
//PARAMETER
#define VEH_EPS_SPEED_FACTOR						100
#define VEH_DASHBOARD_SPEED_FACTOR					100
#define VEH_GY_ROLL_PITCH_YAW_FACTOR				100
#define VEH_ACC_XYZ_FACTOR							1
#define VEH_IMU_TEMPERATURE_FACTOR					10
#define VEH_RADIUS_FACTOR							1
#define VEH_STEERING_ANGLE_FACTOR					10
#define VEH_3D_SPEED_FACTOR							100
#define VEH_ATTITUDE_ANGLE_FACTOR					100

typedef enum{
	VEH_STATUS_VALID = 0,
	VEH_STATUS_INVALID = 1,
	VEH_STATUS_NOT_GET_DATA = 2,
	VEH_STATUS_UNKNOWN
}VEHICLE_STATUS_E;

typedef enum{
	VEH_GEAR_P = 0,
	VEH_GEAR_R = 1,
	VEH_GEAR_N = 2,
	VEH_GEAR_D = 3,
	VEH_GEAR_S = 4,
	VEH_GEAR_UNKNOWN
}VEH_GEAR_E;

typedef enum{
	VEH_IGN_OFF = 0,
	VEH_IGN_ACC = 1,
	VEH_IGN_ON = 2,
	VEH_IGN_CRACK = 3,
	VEH_IGN_UNKNOWN
}VEH_IGN_E;

typedef enum{
	VEH_TRUN_INDICATOR_ALL_OFF = 0,
	VEH_TRUN_INDICATOR_RIGHT_ON = 1,
	VEH_TRUN_INDICATOR_LEFT_ON = 2,
	VEH_TRUN_INDICATOR_UNKNOWN
}VEH_TURN_INDICATOR_E;

typedef enum{
	VEH_DOOR_FRONT_RIGHT = 0,
	VEH_DOOR_REAR_RIGHT = 1,
	VEH_DOOR_FRONT_LEFT = 2,
	VEH_DOOR_REAR_LEFT = 3,
	VEH_DOOR_TRUNK = 4,
	VEH_DOOR_SUNROOF = 5,
	VEH_DOOR_UNKNOWN
}VEH_DOOR_E;

typedef enum{
	VEH_DOOR_STATUS_CLOSE = 0,
	VEH_DOOR_STATUS_OPEN = 1
}VEH_DOOR_STATUS_E;

typedef enum{
	VEH_PARKING_BRAKE_LEVER_OFF = 0,
	VEH_PARKING_BRAKE_LEVER_ON = 1,
	VEH_PARKING_BRAKE_LEVER_UNKNOWN
}VEH_PARKING_BRAKE_LEVER_E;

typedef enum{
	VEH_HEADLAMP_OFF = 0,
	VEH_HEADLAMP_LOW = 1,
	VEH_HEADLAMP_HIGH = 2,
	VEH_HEADLAMP_UNKNOWN
}VEH_HEADLAMP_E;

typedef enum{
	VEH_WIPER_OFF = 0,
	VEH_WIPER_INT = 1,
	VEH_WIPER_LOW = 2,
	VEH_WIPER_HIGH = 3,
	VEH_WIPER_UNKNOWN
}VEH_WIPER_E;

typedef enum{
	VEH_PEPS_LOCK = 0,
	VEH_PEPS_UNLOCK = 1,
	VEH_PEPS_UNKNOWN
}VEH_PEPS_E;

typedef enum{
	VEH_DOOR_LOCK_LEFT = 0,
	VEH_DOOR_LOCK_RIGHT = 1,
	VEH_DOOR_LOCK_UNKNOWN
}VEH_DOOR_LOCK_E;

typedef enum{
	VEH_DOOR_LOCK_STATUS_LOCK = 0,
	VEH_DOOR_LOCK_STATUS_UNLOCK = 1
}VEH_DOOR_LOCK_STATUS_E;

typedef enum{
	VEH_MOTION_STATUS_STATIONARY = 0,
	VEH_MOTION_STATUS_MOVING = 1,
	VEH_MOTION_STATUS_UNKNOWN
}VEHICLE_MOTION_E;

typedef enum {
	VEH_EPS_SPEED = 0,
	VEH_DASHBOARD_SPEED = 1,
	VEH_VEHICLE_YAW_RATE = 2,
	VEH_STEERING_ANGLE = 3,
	VEH_GEAR = 4,
	VEH_IGN = 5,
	VEH_TRUN_INDICATOR = 6,
	VEH_DOOR = 7,
	VEH_PARKING_BRAKE_LEVER = 8,
	VEH_HEADLAMP = 9,
	VEH_WIPER = 10,
	VEH_NORTH_SPEED = 11,
	VEH_EAST_SPEED = 12,
	VEH_UP_SPEED = 13,
	VEH_YAW_ANGLE = 14,
	VEH_PITCH_ANGLE = 15,
	VEH_ROLL_ANGLE = 16,
	VEH_PEPS	= 17,
	VEH_DOOR_LOCK	= 18,
	VEH_ONBOARD_RAW_ROLL_RATE = 19,
	VEH_ONBOARD_RAW_PITCH_RATE = 20,
	VEH_ONBOARD_RAW_YAW_RATE = 21,
	VEH_ONBOARD_FILTERED_ROLL_RATE = 22,
	VEH_ONBOARD_FILTERED_PITCH_RATE = 23,
	VEH_ONBOARD_FILTERED_YAW_RATE = 24,
	VEH_ONBOARD_RAW_ACC_X = 25,
	VEH_ONBOARD_RAW_ACC_Y = 26,
	VEH_ONBOARD_RAW_ACC_Z = 27,
	VEH_ONBOARD_FILTERED_ACC_X = 28,
	VEH_ONBOARD_FILTERED_ACC_Y = 29,
	VEH_ONBOARD_FILTERED_ACC_Z = 30,
	VEH_ONBOARD_TEMPERATURE = 31,
	VEH_RADIUS = 32,
	VEH_FILTERED_YAW_RATE = 33,
	VEH_ONBOARD_RADIUS = 34,
	VEH_TWO_SRC_FILTERED_YAW_RATE = 35,
	VEH_MOTION = 36,
	INVALID
}VEHICLE_INFO_E;

typedef union vehicle_item{
	int32_t R[INVALID];
	struct {
		int32_t  eps_speed;				//0
		int32_t  dashboard_speed;		//1
		int32_t  yaw_rate;				//2
		int32_t  steering_angle;		//3
		int32_t  gear;					//4
		int32_t  ign;					//5
		int32_t  turn_indicator;		//6
		int32_t  door;					//7
		int32_t	 parking_brake_lever;	//8
		int32_t	 headlamp;				//9
		int32_t	 wiper;					//10
		int32_t  north_speed;			//11
		int32_t	 east_speed;			//12
		int32_t  up_speed;				//13
		int32_t  yaw_angle;				//14
		int32_t  pitch_angle;			//15
		int32_t  roll_angle;			//16
		int32_t	 peps;					//17
		int32_t  door_lock;				//18
		int32_t  onboard_raw_roll_rate;	//19
		int32_t  onboard_raw_pitch_rate;//20
		int32_t  onboard_raw_yaw_rate;	//21
		int32_t  onboard_filtered_roll_rate;	//22
		int32_t  onboard_filtered_pitch_rate;	//23
		int32_t  onboard_filtered_yaw_rate;		//24
		int32_t  onboard_raw_acc_x;		//25
		int32_t  onboard_raw_acc_y;		//26
		int32_t  onboard_raw_acc_z;		//27
		int32_t  onboard_filtered_acc_x;//28
		int32_t  onboard_filtered_acc_y;//29
		int32_t  onboard_filtered_acc_z;//30
		int32_t  onboard_temperature;	//31
		int32_t  radius;				//32
		int32_t  filtered_yaw;			//33
		int32_t  onboard_radius;		//34
		int32_t  two_src_filtered_yaw;	//35
		int32_t  motion;				//36
		}B;
}vehicle_data_info_t, *vehicle_data_info_p;
#endif /* VEHICLE_VEHICLE_H_ */
//========================================================
//Function
void vehicle_init();
//get function
//eps speed
float get_eps_speed_value(void);
VEHICLE_STATUS_E get_eps_speed_status(void);
//dashboard speed
float get_dashboard_speed_value(void);
VEHICLE_STATUS_E get_dashboard_speed_status(void);
//3D speed
float get_north_speed_value(void);
VEHICLE_STATUS_E get_north_speed_status(void);
float get_east_speed_value(void);
VEHICLE_STATUS_E get_east_speed_status(void);
float get_up_speed_value(void);
VEHICLE_STATUS_E get_up_speed_status(void);
//Attitude Angle
float get_yaw_angle_value(void);
VEHICLE_STATUS_E get_yaw_angle_status(void);
float get_pitch_angle_value(void);
VEHICLE_STATUS_E get_pitch_angle_status(void);
float get_roll_angle_value(void);
VEHICLE_STATUS_E get_roll_angle_status(void);
//yawrate
float get_yaw_rate_value(void);
VEHICLE_STATUS_E get_yaw_rate_status(void);
//steering angle
float get_steering_angle_value(void);
VEHICLE_STATUS_E get_steering_angle_status(void);
//gear
VEH_GEAR_E get_gear_value(void);
VEHICLE_STATUS_E get_gear_status(void);
//ign
VEH_IGN_E get_ign_value(void);
VEHICLE_STATUS_E get_ign_status(void);
//turn indicator
VEH_TURN_INDICATOR_E get_turn_indicator_value(void);
VEHICLE_STATUS_E get_turn_indicator_status(void);
//door
VEH_DOOR_STATUS_E get_door_value(VEH_DOOR_E door);
VEHICLE_STATUS_E get_door_status(void);
//parking brake lever
VEH_PARKING_BRAKE_LEVER_E get_parking_brake_lever_value(void);
VEHICLE_STATUS_E get_parking_brake_lever_status(void);
//head lamp
VEH_HEADLAMP_E get_headlamp_value(void);
VEHICLE_STATUS_E get_headlamp_status(void);
//wiper
VEH_WIPER_E get_wiper_value(void);
VEHICLE_STATUS_E get_wiper_status(void);
//peps
VEH_PEPS_E judge_peps_value(int32_t data);
VEH_PEPS_E get_peps_value(void);
VEHICLE_STATUS_E get_peps_status(void);
//door lock
VEH_DOOR_LOCK_STATUS_E get_door_lock_value(VEH_DOOR_LOCK_E door_lock);
VEHICLE_STATUS_E get_door_lock_status(void);
//onboard raw roll rate
float get_veh_onboard_raw_roll_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_roll_rate_status(void);
//onboard raw pitch rate
float get_veh_onboard_raw_pitch_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_pitch_rate_status(void);
//onboard raw yaw rate
float get_veh_onboard_raw_yaw_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_yaw_rate_status(void);
//onboard filtered roll rate
float get_veh_onboard_filtered_roll_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_roll_rate_status(void);
//onboard filtered pitch rate
float get_veh_onboard_filtered_pitch_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_pitch_rate_status(void);
//onboard filtered yaw rate
float get_veh_onboard_filtered_yaw_rate_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_yaw_rate_status(void);
//onboard raw acc x
float get_veh_onboard_raw_acc_x_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_acc_x_status(void);
//onboard raw acc y
float get_veh_onboard_raw_acc_y_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_acc_y_status(void);
//onboard raw acc z
float get_veh_onboard_raw_acc_z_value(void);
VEHICLE_STATUS_E get_veh_onboard_raw_acc_z_status(void);
//onboard filtered acc x
float get_veh_onboard_filtered_acc_x_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_acc_x_status(void);
//onboard filtered acc y
float get_veh_onboard_filtered_acc_y_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_acc_y_status(void);
//onboard filtered acc z
float get_veh_onboard_filtered_acc_z_value(void);
VEHICLE_STATUS_E get_veh_onboard_filtered_acc_z_status(void);
//onboard temperature
float get_veh_onboard_temperature_value(void);
VEHICLE_STATUS_E get_veh_onboard_temperature_status(void);
//radius
float get_veh_radius_value(void);
VEHICLE_STATUS_E get_veh_raduis_status(void);
//filtered yawrate
float get_veh_filtered_yaw_rate_value(void);
VEHICLE_STATUS_E get_veh_filtered_yaw_rate_status(void);
//onboard radius
float get_veh_onboard_radius_value(void);
VEHICLE_STATUS_E get_veh_onboard_radius_status(void);
//two source filtered yawrate
float get_veh_two_src_filtered_yaw_rate_value(void);
VEHICLE_STATUS_E get_veh_two_src_filtered_yaw_rate_status(void);
//motion
VEHICLE_MOTION_E get_veh_motion_value(void);
VEHICLE_STATUS_E get_veh_motion_status(void);
#if defined(CTI_Z4_0)
//set function
//eps speed
void set_veh_eps_speed_value(float real_speed);
void set_veh_eps_speed_invalid_value(void);
void set_veh_eps_speed_not_get_value(void);
//dashboard speed
void set_veh_dashboard_speed_value(float real_speed);
void set_veh_dashboard_speed_invalid_value(void);
void set_veh_dashboard_speed_not_get_value(void);
//3D speed
void set_veh_north_speed_value(float north_speed);
void set_veh_north_speed_invalid_value(void);
void set_veh_north_speed_not_get_value(void);
void set_veh_east_speed_value(float east_speed);
void set_veh_east_speed_invalid_value(void);
void set_veh_east_speed_not_get_value(void);
void set_veh_up_speed_value(float up_speed);
void set_veh_up_speed_invalid_value(void);
void set_veh_up_speed_not_get_value(void);
//steering angle
void set_veh_steering_angle_value(float real_steering_angle);
void set_veh_steering_angle_invalid_value(void);
void set_veh_steering_angle_not_get_value(void);
//Attitude Angle
void set_veh_yaw_angle_value(float real_yaw_angle);
void set_veh_yaw_angle_invalid_value(void);
void set_veh_yaw_angle_not_get_value(void);
void set_veh_pitch_angle_value(float real_pitch_angle);
void set_veh_pitch_angle_invalid_value(void);
void set_veh_pitch_angle_not_get_value(void);
void set_veh_roll_angle_value(float real_roll_angle);
void set_veh_roll_angle_invalid_value(void);
void set_veh_roll_angle_not_get_value(void);
//yawrate
void set_veh_yaw_rate_value(float real_yawrate);
void set_veh_yaw_rate_invalid_value(void);
void set_veh_yaw_rate_not_get_value(void);
//gear
void set_veh_gear_p_value(void);
void set_veh_gear_r_value(void);
void set_veh_gear_n_value(void);
void set_veh_gear_d_value(void);
void set_veh_gear_s_value(void);
void set_veh_gear_p_invalid_value(void);
void set_veh_gear_r_invalid_value(void);
void set_veh_gear_n_invalid_value(void);
void set_veh_gear_d_invalid_value(void);
void set_veh_gear_s_invalid_value(void);
void set_veh_gear_invalid_value(void);
void set_veh_gear_not_get_value(void);
//ign
void set_veh_ign_off_value(void);
void set_veh_ign_acc_value(void);
void set_veh_ign_on_value(void);
void set_veh_ign_crack_value(void);
void set_veh_ign_acc_invalid_value(void);
void set_veh_ign_on_invalid_value(void);
void set_veh_ign_crack_invalid_value(void);
void set_veh_ign_invalid_value(void);
void set_veh_ign_not_get_value(void);
//turn indicator
void set_veh_turn_indicator_off_value(void);
void set_veh_turn_indicator_right_on_value(void);
void set_veh_turn_indicator_left_on_value(void);
void set_veh_turn_indicator_invalid_value(void);
void set_veh_turn_indicator_not_get_value(void);
void set_veh_turn_indicator_right_on_invalid_value(void);
void set_veh_turn_indicator_left_on_invalid_value(void);
//door
void set_veh_door_status_value_open(VEH_DOOR_E door);
void clear_veh_door_status_value_open(VEH_DOOR_E door);
void set_veh_door_status_invalid_value(void);
void set_veh_door_status_not_get_value(void);
//parking brake level
void set_veh_parking_brake_level_off_value(void);
void set_veh_parking_brake_level_on_value(void);
void set_veh_parking_brake_level_invalid_value(void);
void set_veh_parking_brake_level_not_get_value(void);
//headlamp
void set_veh_headlamp_off_value(void);
void set_veh_headlamp_low_on_value(void);
void set_veh_headlamp_high_on_value(void);
void set_veh_headlamp_invalid_value(void);
void set_veh_headlamp_not_get_value(void);
void set_headlamp_low_on_invalid_value(void);
void set_headlamp_high_on_invalid_value(void);
//wiper
void set_wiper_off_value(void);
void set_veh_wiper_int_value(void);
void set_veh_wiper_low_value(void);
void set_veh_wiper_high_value(void);
void set_veh_wiper_invalid_value(void);
void set_veh_wiper_not_get_value(void);
void set_veh_wiper_int_invalid_value(void);
void set_veh_wiper_low_invalid_value(void);
void set_veh_wiper_high_invalid_value(void);
//peps
void set_veh_peps_lock_value(void);
void set_veh_peps_unlock_value(void);
void set_veh_peps_invalid_value(void);
void set_veh_peps_not_get_value(void);
//door lock
void set_veh_door_lock_status_value_unlock(VEH_DOOR_LOCK_E door_lock);
void clear_veh_door_lock_status_value_unlock(VEH_DOOR_LOCK_E door_lock);
void set_veh_door_lock_status_invalid_value(void);
void set_veh_door_lock_status_not_get_value(void);
//onboard raw roll rate
void set_veh_onboard_raw_roll_rate_value(float real_rollrate);
void set_veh_onboard_raw_roll_rate_status_invalid_value(void);
void set_veh_onboard_raw_roll_rate_status_not_get_value(void);
//onboard raw pitch rate
void set_veh_onboard_raw_pitch_rate_value(float real_pitchrate);
void set_veh_onboard_raw_pitch_rate_status_invalid_value(void);
void set_veh_onboard_raw_pitch_rate_status_not_get_value(void);
//onboard raw yaw rate
void set_veh_onboard_raw_yaw_rate_value(float real_yawrate);
void set_veh_onboard_raw_yaw_rate_status_invalid_value(void);
void set_veh_onboard_raw_yaw_rate_status_not_get_value(void);
//onboard filtered roll rate
void set_veh_onboard_filtered_roll_rate_value(float real_rollrate);
void set_veh_onboard_filtered_roll_rate_status_invalid_value(void);
void set_veh_onboard_filtered_roll_rate_status_not_get_value(void);
//onboard filtered pitch rate
void set_veh_onboard_filtered_pitch_rate_value(float real_pitchrate);
void set_veh_onboard_filtered_pitch_rate_status_invalid_value(void);
void set_veh_onboard_filtered_pitch_rate_status_not_get_value(void);
//onboard filtered yaw rate
void set_veh_onboard_filtered_yaw_rate_value(float real_yawrate);
void set_veh_onboard_filtered_yaw_rate_status_invalid_value(void);
void set_veh_onboard_filtered_yaw_rate_status_not_get_value(void);
//onboard raw acc x
void set_veh_onboard_raw_acc_x_value(float real_acc_x);
void set_veh_onboard_raw_acc_x_status_invalid_value(void);
void set_veh_onboard_raw_acc_x_status_not_get_value(void);
//onboard raw acc y
void set_veh_onboard_raw_acc_y_value(float real_acc_y);
void set_veh_onboard_raw_acc_y_status_invalid_value(void);
void set_veh_onboard_raw_acc_y_status_not_get_value(void);
//onboard raw acc z
void set_veh_onboard_raw_acc_z_value(float real_acc_z);
void set_veh_onboard_raw_acc_z_status_invalid_value(void);
void set_veh_onboard_raw_acc_z_status_not_get_value(void);
//onboard filtered acc x
void set_veh_onboard_filtered_acc_x_value(float real_acc_x);
void set_veh_onboard_filtered_acc_x_status_invalid_value(void);
void set_veh_onboard_filtered_acc_x_status_not_get_value(void);
//onboard filtered acc y
void set_veh_onboard_filtered_acc_y_value(float real_acc_y);
void set_veh_onboard_filtered_acc_y_status_invalid_value(void);
void set_veh_onboard_filtered_acc_y_status_not_get_value(void);
//onboard filtered acc z
void set_veh_onboard_filtered_acc_z_value(float real_acc_z);
void set_veh_onboard_filtered_acc_z_status_invalid_value(void);
void set_veh_onboard_filtered_acc_z_status_not_get_value(void);
//onboard temperature
void set_veh_onboard_temperature_value(float real_temperature);
void set_veh_onboard_temperature_status_invalid_value(void);
void set_veh_onboard_temperature_status_not_get_value(void);
//radius
void set_veh_radius_value(float radius);
void set_veh_radius_status_invalid_value(void);
void set_veh_radius_status_not_get_value(void);
//filtered yawrate
void set_veh_filtered_yaw_rate_value(float real_yawrate);
void set_veh_filtered_yaw_rate_status_invalid_value(void);
void set_veh_filtered_yaw_rate_status_not_get_value(void);
//onboard radius
void set_veh_onboard_radius_value(float radius);
void set_veh_onboard_radius_status_invalid_value(void);
void set_veh_onboard_radius_status_not_get_value(void);
//two source filtered yaw rate
void set_veh_two_src_filtered_yaw_rate_value(float real_yawrate);
void set_veh_two_src_filtered_yaw_rate_status_invalid_value(void);
void set_veh_two_src_filtered_yaw_rate_status_not_get_value(void);
//motion
void set_veh_motion_status_stationary_value(void);
void set_veh_motion_status_moving_value(void);
void set_veh_motion_status_stationary_invalid_value(void);
void set_veh_motion_status_moving_invalid_value(void);
void set_veh_motion_status_invalid_value(void);
void set_veh_motion_status_not_get_value(void);
#else
void vehicle_usage(vehicle_data_info_p v);
#endif
//=========================================================
//Index = 0
//EPS Speed Format
//EPS speed resolution = 0.01
//EPS speed offset = 0
//EPS speed range = 0~65535 km/h
//Real speed range = 0~655.35 km/h
//EPS speed init value = 0x80000000
//EPS speed invalid value = 0x40000000
//=========================================================
//Index = 1
//Dash board Speed Format
//Dash board speed resolution = 0.01
//Dash board speed offset = 0
//Dash board speed range = 0~32767
//Real speed range = 0~327.67 km/h
//Dash board speed init value = 0x80000000
//Dash board speed invalid value = 0x40000000
//=========================================================
//Index = 2(left positive,right negative)
//Yaw rate Format
//Yaw rate resolution = 0.01
//Yaw rate offset = 0
//Yaw rate range = -30000~30000
//Real Yawrate range = -300.00~300.00 deg/s
//Yaw rate init value = 0x80000000
//Yaw rate invalid value = 0x40000000
//=========================================================
//Index = 3(left negative,right positive)
//steering_angle Format
//steering_angle resolution = 0.1
//steering_angle offset = 0
//steering_angle range = -20000~20000
//Real steering_angle range = -2000.0~2000.0 deg
//steering_angle init value = 0x80000000
//steering_angle invalid value = 0x40000000
//=========================================================
//Index = 4
//Gear Format
//Gear resolution = 1
//Gear offset = 0
//Gear P = 0x00000001(bit)
//Gear R = 0x00000002(bit)
//Gear N = 0x00000004(bit)
//Gear D = 0x00000008(bit)
//Gear S = 0x00000010(bit)
//Gear init value = 0x80000000
//Gear invalid value = 0x40000000
//Gear P invalid = 0x00010000(bit)
//Gear R invalid = 0x00020000(bit)
//Gear N invalid = 0x00040000(bit)
//Gear D invalid = 0x00080000(bit)
//Gear S invalid = 0x00100000(bit)
//=========================================================
//Index = 5
//IGN Format
//IGN resolution = 1
//IGN offset = 0
//IGN OFF = 0x00000000(bit)
//IGN ACC = 0x00000001(bit)
//IGN ON = 0x00000002(bit)
//IGN Crack = 0x00000004(bit)
//IGN init value = 0x80000000
//IGN invalid value = 0x40000000
//IGN ACC invalid = 0x00010000(bit)
//IGN ON invalid = 0x00020000(bit)
//IGN Crack invalid = 0x00040000(bit)
//=========================================================
//Index = 6
//Turn Indicator Format
//Turn Indicator resolution = 1
//Turn Indicator offset = 0
//Turn Indicator right on = 0x00000001(bit)
//Turn Indicator left on = 0x00000002(bit)
//Turn Indicator init value = 0x80000000
//Turn Indicator invalid value = 0x40000000
//Turn Indicator right invalid = 0x00010000(bit)
//Turn Indicator left invalid = 0x00020000(bit)
//=========================================================
//Index = 7
//Door Format
//Door resolution = 1
//Door offset = 0
//Door front right on = 0x00000001(bit)
//Door rear right on = 0x00000002(bit)
//Door front left on = 0x00000004(bit)
//Door rear left on = 0x00000008(bit)
//Door trunk on = 0x00000010(bit)
//Door sunroof on = 0x00000020(bit)
//Door init value = 0x80000000
//Door invalid value = 0x40000000
//Door front right invalid = 0x00010000(bit)
//Door rear right invalid = 0x00020000(bit)
//Door front left invalid = 0x00040000(bit)
//Door rear left invalid = 0x00080000(bit)
//Door trunk invalid = 0x00100000(bit)
//Door sunroof invalid = 0x00200000(bit)
//=========================================================
//Index = 8
//Parking brake lever Format
//Parking brake lever resolution = 1
//Parking brake lever offset = 0
//Parking brake lever OFF = 0x00000000(bit)
//Parking brake lever ON = 0x00000001(bit)
//Parking brake lever init value = 0x80000000
//Parking brake lever invalid value = 0x40000000
//Parking brake lever ON invalid = 0x00010000(bit)
//=========================================================
//Index = 9
//Head lamp Format
//Head lamp resolution = 1
//Head lamp offset = 0
//Head lamp OFF = 0x00000000(bit)
//Head lamp Low beam = 0x00000001(bit)
//Head lamp High beam = 0x00000002(bit)
//Head lamp init value = 0x80000000
//Head lamp invalid value = 0x40000000
//Head lamp Low beam invalid = 0x00010000(bit)
//Head lamp High beam invalid = 0x00020000(bit)

//=========================================================
//Index = 10
//Wiper Format
//Wiper resolution = 1
//Wiper offset = 0
//Wiper OFF = 0x00000000(bit)
//Wiper INT = 0x00000001(bit)
//Wiper Lo = 0x00000002(bit)
//Wiper High = 0x00000004(bit)
//Wiper init value = 0x80000000
//Wiper invalid value = 0x40000000
//Wiper INT invalid = 0x00010000(bit)
//Wiper Lo invalid = 0x00020000(bit)
//Wiper High invalid = 0x00040000(bit)
//=========================================================
//Index = 11
//North Speed Format
//North speed resolution = 0.01
//North speed offset = 0
//North speed range = -32768~32767 m/s
//Real North speed range = -327.68~327.67 m/s
//North speed init value = 0x80000000
//North speed invalid value = 0x40000000
//=========================================================
//Index = 12
//East Speed Format
//East speed resolution = 0.01
//East speed offset = 0
//East speed range = -32768~32767 m/s
//Real east speed range = -327.68~327.67 m/s
//East speed init value = 0x80000000
//East speed invalid value = 0x40000000
//=========================================================
//Index = 13
//Up Speed Format
//Up speed resolution = 0.01
//Up speed offset = 0
//Up speed range = -32768~32767 m/s
//Real up speed range = -327.68~327.67 m/s
//Up speed init value = 0x80000000
//Up speed invalid value = 0x40000000
//=========================================================
//Index = 14
//Yaw angle Format
//Yaw angle resolution = 0.01
//Yaw angle offset = 0
//Yaw angle range = 0~36000 deg
//Real Yaw angle range = 0~360.00 deg
//Yaw angle init value = 0x80000000
//Yaw angle invalid value = 0x40000000
//=========================================================
//Index = 15
//Pitch angle Format
//Pitch angle resolution = 0.01
//Pitch angle offset = 0
//Pitch angle range = -9000~9000 deg
//Real Pitch angle range = -90.00~90.00 deg
//Pitch angle init value = 0x80000000
//Pitch angle invalid value = 0x40000000
//=========================================================
//Index = 16
//Roll angle Format
//Roll angle resolution = 0.01
//Roll angle offset = 0
//Roll angle range = -18000~18000 deg
//Real Roll angle range = -180.00~180.00 deg
//Roll angle init value = 0x80000000
//Roll angle invalid value = 0x40000000
//=========================================================
//Index = 17
//PEPS Format
//PEPS resolution = 1
//PEPS offset = 0
//PEPS lock = 0x00000000
//PEPS unlock = 0x00000001
//PEPS init value = 0x80000000
//PEPS invalid value = 0x40000000
//=========================================================
//Index = 18
//Door Lock Format
//Door Lock resolution = 1
//Door Lock offset = 0
//Door Lock None = 0x00000000
//Door Lock Left = 0x00000001(bit)
//Door Lock Right= 0x00000002(bit)
//Door Lock init value = 0x80000000
//Door Lock invalid value = 0x40000000
//=========================================================
//Index = 19(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Raw Roll rate Format
//OnBoard Raw Roll rate resolution = 0.01
//OnBoard Raw Roll rate offset = 0
//OnBoard Raw Roll rate range = -30000~30000
//OnBoard Real Raw Roll rate range = -300.00~300.00 deg/s
//OnBoard Raw Roll rate init value = 0x80000000
//OnBoard Raw Roll rate invalid value = 0x40000000
//=========================================================
//Index = 20(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Raw Pitch rate Format
//OnBoard Raw Pitch rate resolution = 0.01
//OnBoard Raw Pitch rate offset = 0
//OnBoard Raw Pitch rate range = -30000~30000
//OnBoard Real Raw Pitch rate range = -300.00~300.00 deg/s
//OnBoard Raw Pitch rate init value = 0x80000000
//OnBoard Raw Pitch rate invalid value = 0x40000000
//=========================================================
//Index = 21(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Raw Yaw rate Format
//OnBoard Raw Yaw rate resolution = 0.01
//OnBoard Raw Yaw rate offset = 0
//OnBoard Raw Yaw rate range = -30000~30000
//OnBoard Real Raw Yaw rate range = -300.00~300.00 deg/s
//OnBoard Raw Yaw rate init value = 0x80000000
//OnBoard Raw Yaw rate invalid value = 0x40000000
//=========================================================
//Index = 22(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Filtered Roll rate Format
//OnBoard Filtered Roll rate resolution = 0.01
//OnBoard Filtered Roll rate offset = 0
//OnBoard Filtered Roll rate range = -30000~30000
//OnBoard Real Filtered Roll rate range = -300.00~300.00 deg/s
//OnBoard Filtered Roll rate init value = 0x80000000
//OnBoard Filtered Roll rate invalid value = 0x40000000
//=========================================================
//Index = 23(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Filtered Pitch rate Format
//OnBoard Filtered Pitch rate resolution = 0.01
//OnBoard Filtered Pitch rate offset = 0
//OnBoard Filtered Pitch rate range = -30000~30000
//OnBoard Real Filtered Pitch rate range = -300.00~300.00 deg/s
//OnBoard Filtered Pitch rate init value = 0x80000000
//OnBoard Filtered Pitch rate invalid value = 0x40000000
//=========================================================
//Index = 24(Counterclockwise: Positive, Clockwise: Negative)
//OnBoard Filtered Yaw rate Format
//OnBoard Filtered Yaw rate resolution = 0.01
//OnBoard Filtered Yaw rate offset = 0
//OnBoard Filtered Yaw rate range = -30000~30000
//OnBoard Real Filtered Yaw rate range = -300.00~300.00 deg/s
//OnBoard Filtered Yaw rate init value = 0x80000000
//OnBoard Filtered Yaw rate invalid value = 0x40000000
//=========================================================
//Index = 25(Forward: Positive, Backward: Negative)
//OnBoard Raw Acc X Format
//OnBoard Raw Acc X resolution = 0.001
//OnBoard Raw Acc X offset = 0
//OnBoard Raw Acc X range = -16000 ~ 16000
//OnBoard Real Raw Acc X range =  -16.00 ~ 16.00 g
//OnBoard Raw Acc X init value = 0x80000000
//OnBoard Raw Acc X invalid value = 0x40000000
//=========================================================
//Index = 26(Forward: Positive, Backward: Negative)
//OnBoard Raw Acc Y Format
//OnBoard Raw Acc Y resolution = 0.001
//OnBoard Raw Acc Y offset = 0
//OnBoard Raw Acc Y range = -16000 ~ 16000
//OnBoard Real Raw Acc Y range =  -16.00 ~ 16.00 g
//OnBoard Raw Acc Y init value = 0x80000000
//OnBoard Raw Acc Y invalid value = 0x40000000
//=========================================================
//Index = 27(Forward: Positive, Backward: Negative)
//OnBoard Raw Acc Z Format
//OnBoard Raw Acc Z resolution = 0.001
//OnBoard Raw Acc Z offset = 0
//OnBoard Raw Acc Z range = -16000 ~ 16000
//OnBoard Real Raw Acc Z range =  -16.00 ~ 16.00 g
//OnBoard Raw Acc Z init value = 0x80000000
//OnBoard Raw Acc Z invalid value = 0x40000000
//=========================================================
//Index = 28(Forward: Positive, Backward: Negative)
//OnBoard Filtered Acc X Format
//OnBoard Filtered Acc X resolution = 0.001
//OnBoard Filtered Acc X offset = 0
//OnBoard Filtered Acc X range = -16000 ~ 16000
//OnBoard Real Filtered Acc X range =  -16.00 ~ 16.00 g
//OnBoard Filtered Acc X init value = 0x80000000
//OnBoard Filtered Acc X invalid value = 0x40000000
//=========================================================
//Index = 29(Forward: Positive, Backward: Negative)
//OnBoard Filtered Acc Y Format
//OnBoard Filtered Acc Y resolution = 0.001
//OnBoard Filtered Acc Y offset = 0
//OnBoard Filtered Acc Y range = -16000 ~ 16000
//OnBoard Real Filtered Acc Y range =  -16.00 ~ 16.00 g
//OnBoard Filtered Acc Y init value = 0x80000000
//OnBoard Filtered Acc Y invalid value = 0x40000000
//=========================================================
//Index = 30(Forward: Positive, Backward: Negative)
//OnBoard Filtered Acc Z Format
//OnBoard Filtered Acc Z resolution = 0.001
//OnBoard Filtered Acc Z offset = 0
//OnBoard Filtered Acc Z range = -16000 ~ 16000
//OnBoard Real Filtered Acc Z range =  -16.00 ~ 16.00 g
//OnBoard Filtered Acc Z init value = 0x80000000
//OnBoard Filtered Acc Z invalid value = 0x40000000
//=========================================================
//Index = 31
//OnBoard Temperture Format
//OnBoard Temperture resolution = 1
//OnBoard Temperture offset = 0
//OnBoard Temperture range = -40 ~ 85
//OnBoard Real Temperture range =  -40 ~ 85 deg
//OnBoard Temperture init value = 0x80000000
//OnBoard Temperture invalid value = 0x40000000
//=========================================================
//Index = 32(left positive,right negative)
//Radius Format
//Radius resolution = 1
//Radius offset = 0
//Radius range = -32768~32767
//Radius real range = -32768~32767 m
//Radius init value = 0x80000000
//Radius invalid value = 0x40000000
//=========================================================
//Index = 33(Counterclockwise: Positive, Clockwise: Negative)
//Filtered Yaw rate Format
//Filtered Yaw rate resolution = 0.01
//Filtered Yaw rate offset = 0
//Filtered Yaw rate range = -30000~30000
//Real Filtered Yaw rate range = -300.00~300.00 deg/s
//Filtered Yaw rate init value = 0x80000000
//Filtered Yaw rate invalid value = 0x40000000
//=========================================================
//Index = 34(left positive,right negative)
//Radius Format
//Radius resolution = 1
//Radius offset = 0
//Radius range = -32768~32767
//Radius real range = -32768~32767 m
//Radius init value = 0x80000000
//Radius invalid value = 0x40000000
//=========================================================
//Index = 35(Counterclockwise: Positive, Clockwise: Negative)
//Two Source Filtered Yaw rate Format
//Two Source Filtered Yaw rate resolution = 0.01
//Two Source Filtered Yaw rate offset = 0
//Two Source Filtered Yaw rate range = -30000~30000
//Two Source Real Filtered Yaw rate range = -300.00~300.00 deg/s
//Two Source Filtered Yaw rate init value = 0x80000000
//Two Source Filtered Yaw rate invalid value = 0x40000000
//=========================================================
//Index = 36
//Motion Format
//Motion resolution = 1
//Motion offset = 0
//Motion moving = 0x00000001(bit)
//Motion stationary = 0x00000002(bit)
//Motion init value = 0x80000000
//Motion invalid value = 0x40000000
//Motion moving invalid = 0x00010000(bit)
//Motion stationary invalid = 0x00020000(bit)
//=========================================================
