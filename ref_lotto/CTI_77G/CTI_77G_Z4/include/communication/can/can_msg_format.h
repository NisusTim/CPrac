/*
 * can_msg_format.h
 *
 *  Created on: 2018/11/22
 *      Author: WoodLiu
 */

#ifndef COMMUNICATION_CAN_CAN_MSG_FORMAT_H_
#define COMMUNICATION_CAN_CAN_MSG_FORMAT_H_

#include <stdint.h>

#if 0
#define	CAN_CMD_L_TRACKING_DATA			0x47
#define	CAN_CMD_R_TRACKING_DATA 		0xE7
#define CAN_CMD_WARNING_MSG				0x48

typedef enum
{
	ADI_RADAR_MODE_STANDBY 	= 0,
	ADI_RADAR_MODE_BSD 		= 1,
	ADI_RADAR_MODE_CTA 		= 2,
	ADI_RADAR_MODE_DOW 		= 4,
	ADI_RADAR_MODE_RCW 		= 8
}ADI_WARNING_MODE_E;

typedef enum
{
	WARNING_DEMO_TYPE_STANDBY 	= 0x00,
	WARNING_DEMO_TYPE_BSD		= 0x01,
	WARNING_DEMO_TYPE_LCA		= 0x02,
	WARNING_DEMO_TYPE_DOW 		= 0x03,
	WARNING_DEMO_TYPE_RCTA 		= 0x04,
	WARNING_DEMO_TYPE_RCW	 	= 0x05,
} CNR_WARNING_TYPE_E;

typedef enum
{
	TARGET_TYPE_GUARDRAIL 		= 0,
	TARGET_TYPE_VEHICLE 		= 1
} CNR_TG_TYPE_E;

typedef enum
{
	MEAS_NO_OBJECT				= 0,
	MEAS_TG_PREDICTED			= 1,
	MEAS_TG_MEASURED			= 2,
	MEAS_INVALID				= 4
} CNR_MEAS_STAT_E;

typedef enum
{
	DYN_UNCLASSIFIED			= 0,
	DYN_STANDING				= 1,
	DYN_STOPPED					= 2,
	DYN_APPROACHING				= 3,
	DYN_LEAVING					= 4
}CNR_DYN_STAT_E;

typedef union CNR_Can_Message {

	uint64_t 	Raw;
	uint8_t		Byte[8];

	struct
	{
		uint64_t veh_speed:11;
		uint64_t veh_speed_v:1;
		uint64_t yawrate_v:1;
		uint64_t ign_state:1;
		uint64_t ign_state_v:1;
		uint64_t str_angle_v:1;
		uint64_t yawrate:16;
		uint64_t str_angle:16;
		uint64_t gear_sta :3;
		uint64_t gear_sta_v:1;
		uint64_t :4;
		uint64_t door_fl_sta:1;
		uint64_t door_fr_sta:1;
		uint64_t door_rl_sta:1;
		uint64_t door_rr_sta:1;
		uint64_t door_sta_v:1;
		uint64_t turn_sta:2;
		uint64_t turn_sta_v:1;
	}VehicleInfo;

	struct
	{
		uint64_t Num_tg:6;
		uint64_t :2;
		uint64_t warn_mode:4;
		uint64_t warn_level:2;
		uint64_t :18;
		uint64_t longitudinal_shift:8;
		uint64_t lateral_shift:8;
		uint64_t frame_cnt:16;
	}TargetHeader;

	struct
	{
		uint64_t tg_pos_x:11;
		uint64_t tg_pos_y:10;
		uint64_t tg_type:3;
		uint64_t tg_vel_x:10;
		uint64_t tg_id:6;
		uint64_t tg_dyn_stat:3;
		uint64_t tg_meas_stat:3;
		uint64_t tg_accel_x:10;
		uint64_t tg_vel_y:8;
	}TargetList;

}CnrCanMessage_t,*CnrCanMessage_p;

typedef union ADI_Can_Message {
	uint64_t 	Raw;
	uint8_t		Byte[8];

	struct {
		uint64_t cmd_type		:8;
		uint64_t t_cnt			:8;
		uint64_t  				:32;
		uint64_t v_sequence		:16;
	} TargetListHeader;

	struct {
		uint64_t cmd_type		:8;
		uint64_t is_guail		:1;
		uint64_t target_num		:7;
		uint64_t x_range		:16;
		uint64_t y_range		:16;
		uint64_t velocity		:16;
	} TargetList;

	struct {
		uint64_t cmd_type:8;			//B0:b0~b7
		uint64_t  :2;					//B1:b6~b7
		uint64_t danger_rear:1;			//B1:b5
		uint64_t danger_left:1;			//B1:b4
		uint64_t danger_right:1;		//B1:b3
		uint64_t object_rear:1;			//B1:b2
		uint64_t object_left:1;			//B1:b1
		uint64_t object_right:1;		//B1:b0
		uint64_t  :2;					//B2:b6~b7
		uint64_t danger_lvl_rear:2;		//B2:b5~b4
		uint64_t danger_lvl_left:2;		//B2:b3~b2
		uint64_t danger_lvl_right:2;	//B2:b1~b0
		uint64_t  :4;					//B3:b4~b7
		uint64_t wmode:4;				//B3:b3~b0
		uint64_t  :24;
		uint64_t seq_number:8;			//B7
	} WarningMsg;

	struct {
		uint64_t cmd_type	:8;			//B0:b0~b7
		uint64_t device		:8;			//B1:b0~b7
		uint64_t door_rr	:1;			//B2:b7
		uint64_t door_rl	:1;			//B2:b6
		uint64_t door_fr	:1;			//B2:b5
		uint64_t door_fl	:1;			//B2:b4
		uint64_t gear_d		:1;			//B2:b3
		uint64_t gear_n		:1;			//B2:b2
		uint64_t gear_r		:1;			//B2:b1
		uint64_t gear_p		:1;			//B2:b0
		uint64_t 			:5;			//B3:b7~b3
		uint64_t headlight	:1;			//B3:b2
		uint64_t turn_ind_r	:1;			//B3:b1
		uint64_t turn_ind_l	:1;			//B3:b0
		uint64_t speed		:8;			//B4:b7~b0
		uint64_t 			:16;		//B5~B6
		uint64_t seq_number	:8;			//B7:b7~b0
	}VehicleInfo1;

	struct {
		uint64_t cmd_type			:8;
		uint64_t frame_rate			:16;	//Add frame rate
		uint64_t frame_cnt			:16;	//Add frame counter because there is no StartScan message
		uint64_t					:24;
	}FinishedScanReq;

	struct {
		uint64_t cmd_type			:8;
		uint64_t frame_rate			:16;
		uint64_t frame_cnt			:16;
		uint64_t ack				:8;
		uint64_t					:16;
	}FinishedScanRes;

}AdiCanMessage_t, *AdiCanMessage_p;

typedef union ST_Can_Message{
	uint64_t 	Raw;
	uint8_t		Byte[8];

	struct {
		uint64_t command_id		:8;
		uint64_t v_sequence		:8;
		uint64_t t_cnt			:8;
		uint64_t reserved		:40;
	} TargetListHeader;

	struct
	{
		uint64_t velocity_sign:1;		//B7(bit7)
		uint64_t velocity:9;			//B6(bit7~6)~B7(bit6~0)
		uint64_t y_range_sign:1;		//B6(bit5)
		uint64_t y_range:10;			//B5(bit7~3)~B6(bit4~0)
		uint64_t x_range_sign:1;		//B5(bit2)
		uint64_t x_range:10;			//B4(bit7~0)~B5(bit1~0)
		uint64_t reserved1:4;			//B3(bit7~4)
		uint64_t status:3;				//B3(bit3~1)
		uint64_t warning_trigger:1;		//B3(bit0)
		uint64_t score:8;				//B2(bit7~0)
		uint64_t type:1;				//B1(bit7)
		uint64_t category:1;			//B1(bit6)
		uint64_t target_sequence:6;		//B1(bit5~0)
		uint64_t command_id:8;			//B0(bit7~0)
	}TargetList;//Intel format

}StCanMessage_t,*StCanMessage_p;
#endif

typedef union Cubtek_Can_Vehicle_information {
  uint64_t R;
  struct {
	  uint64_t speed_inv :1;
	  uint64_t speed :11;
	  uint64_t yaw_rate_inv:1;
	  uint64_t :2;
	  uint64_t str_angle_v:1;
	  uint64_t yaw_rate:16;
	  uint64_t str_angle :16;
	  uint64_t  :16;
  } B;
} CUBTEK_CAN_VEHCLE_INFO;

typedef union Cubtek_Can_Vehicle_information2 {
  uint64_t R;
  struct {
	  uint64_t peps_sta:1;
	  uint64_t gear_state:3;
	  uint64_t gear_state_inv:1;
	  uint64_t :5;
	  uint64_t ign_state_V:1;
	  uint64_t ign_state:1;
	  uint64_t door_lock_left:1;
	  uint64_t door_lock_right:1;
	  uint64_t turn_indicator :2;
	  uint64_t door_fl:1;
	  uint64_t door_fr:1;
	  uint64_t door_rl:1;
	  uint64_t door_rr:1;
	  uint64_t  :44;
  } B;
} CUBTEK_CAN_VEHCLE_INFO2;

#endif /* COMMUNICATION_CAN_CAN_MSG_FORMAT_H_ */
