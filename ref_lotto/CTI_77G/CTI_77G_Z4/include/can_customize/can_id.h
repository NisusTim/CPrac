/*
 * can_id.h
 *
 *  Created on: 2017��9��14��
 *      Author: user
 */

#ifndef CAN_ID_H_
#define CAN_ID_H_


/*************************************************************************************************
 * can id for transmiting
 *************************************************************************************************/
enum {
	CAN_ID_COMMAND_REPLY			=0x008,
	CAN_ID_CUBTEK_M_TO_S_CMD		=0x060,
	CAN_ID_CUBTEK_REPLY				=0x061,
	CAN_ID_CUBTEK_RMTP_TX_70		=0x070,
	CAN_ID_CUBTEK_RMTP_TX_71		=0x071,
	CAN_ID_CUBTEK_RMTP_TX_72		=0x072,
	CAN_ID_CUBTEK_RMTP_TX_73		=0x073,
	CAN_ID_CUBTEK_RMTP_TX_80		=0x080,
	CAN_ID_CUBTEK_RMTP_TX_81		=0x081,
	CAN_ID_CUBTEK_RMTP_TX_82		=0x082,
	CAN_ID_CUBTEK_RMTP_TX_83		=0x083,
	CAN_ID_DIPPER_OBJS_BASE			=0x100,
	CAN_ID_CUBTEK_TRACKING_OBJ 		=0x123,

	CAN_ID_CUBTEK_AUTO_CALIB		=0x304,
	CAN_ID_CUBTEK_DVTF 				=0x305,
	CAN_ID_CUBTEK_FEEDBACK_VEH      =0x306,
	CAN_ID_HAITEC_AEB_WARNING_REQ	=0x43A,
	CAN_ID_CUBTEK_FCW_WARNING_REQ	=0x43B,
	CAN_ID_CUBTEK_FUS_WARNING_REQ	=0x43C,
	CAN_ID_CUBTEK_NUM_OF_OBJ 		=0x500,
	CAN_ID_CUBTEK_TRACKING_START 	=0x503,

	CNA_ID_CUBTEK_ST_REAR_RIGHT_TRACK = 0xA4,
	CNA_ID_CUBTEK_ST_REAR_LEFT_TRACK = 0xB4,
	CNA_ID_CUBTEK_ST_FRONT_RIGHT_TRACK = 0xC4,
	CNA_ID_CUBTEK_ST_FRONT_LEFT_TRACK = 0xD4,
	CAN_ID_ERROR					=0xE00
};

/*************************************************************************************************
 * can for Min An transmitting
 *************************************************************************************************/
enum {
	CAN_ID_MIN_AN_NM_SOD_L			= 0x40A,
	CAN_ID_MIN_AN_SOD_L_1			= 0x179,
	CAN_ID_MIN_AN_SOD_L_DIAG_RESP	= 0x78A,
};

/*************************************************************************************************
 * can id for receiving
 *************************************************************************************************/
enum {
	CAN_ID_COMMAND 					=0x007,
	CAN_ID_FRAME_SYNC				=0x008,
	CAN_ID_RECEIVE 					=0x009,
	CAN_ID_SEND 					=0x00A,
	CAN_ID_CUBTEK_CMD				=0x060,
	CAN_ID_CUBTEK_RMTP_RX_70		=0x070,
	CAN_ID_CUBTEK_RMTP_RX_71		=0x071,
	CAN_ID_CUBTEK_RMTP_RX_72		=0x072,
	CAN_ID_CUBTEK_RMTP_RX_73		=0x073,
	CAN_ID_CUBTEK_RMTP_RX_80		=0x080,
	CAN_ID_CUBTEK_RMTP_RX_81		=0x081,
	CAN_ID_CUBTEK_RMTP_RX_82		=0x082,
	CAN_ID_CUBTEK_RMTP_RX_83		=0x083,
	CAN_ID_VEHICLE_INFO1			=0x300,
	CAN_ID_VEHICLE_INFO2			=0x301,
	CAN_ID_IMU_INFO1				=0x302,
	CAN_ID_IMU_INFO2				=0x303,
	CAN_ID_U6_GEAR					= 0x340,
	CAN_ID_U6_SPEED					= 0x360
};

/*************************************************************************************************
 * can for Min An receiving
 *************************************************************************************************/
enum {
	CAN_ID_MIN_AN_SOD_L_DIAG_REQ		= 0x70A,
	CAN_ID_MIN_AN_GW_INFO_ABS 			= 0x75,
	CAN_ID_MIN_AN_GW_INFO_EPS_EPB		= 0x77,
	CAN_ID_MIN_AN_GW_INFO_VCU_MCU		= 0x7B,
	CAN_ID_MIN_AN_IHU_9_SET				= 0x91,
	CAN_ID_MIN_AN_FUNC_DIAG_REQ			= 0x7DF,
	CAN_ID_MIN_AN_GW_INFO_BCM_1			= 0x243,
	CAN_ID_MIN_AN_GW_INFO_BCM_4			= 0x245,
	CAN_ID_MIN_AN_ICU_1					= 0x253,
	CAN_ID_MIN_AN_GW_INFO_PWM_1_PEPS_1 	= 0x263,
	CAN_ID_MIN_AN_NM_BASE				= 0x400,

	/*For slave device receiving*/
	CAN_ID_MIN_AN_NM_SOD_R			= 0x40A,
	CAN_ID_MIN_AN_SOD_R_1			= 0x178,
	CAN_ID_MIN_AN_SYSTEM_MONITOR	= 0x666
};

/*************************************************************************************************
 * can for DEMO transmitting
 *************************************************************************************************/
enum
{
	CAN_ID_DEMO_MASTER_TARGET_HEADER = 0x401,
	CAN_ID_DEMO_MASTER_OUTPUT_VEHICLE = 0x402,
	CAN_ID_DEMO_SLAVE_TARGET_HEADER = 0x403,
	CAN_ID_DEMO_SLAVER_OUTPUT_VEHICLE = 0x404,
	CAN_ID_DEMO_FRONT_MASTER_TARGET_HEADER = 0x405,
	CAN_ID_DEMO_FRONT_MASTER_OUTPUT_VEHICLE = 0x406,
	CAN_ID_DEMO_FRONT_SLAVE_TARGET_HEADER = 0x407,
	CAN_ID_DEMO_FRONT_SLAVER_OUTPUT_VEHICLE = 0x408,
	CAN_ID_DEMO_MASTER_TARGET_LIST_START = 0x410,
	CAN_ID_DEMO_MASTER_TARGET_LIST_END = 0x42F,
	CAN_ID_DEMO_SLAVE_TARGET_LIST_START = 0x430,
	CAN_ID_DEMO_SLAVE_TARGET_LIST_END = 0x44F,
	CAN_ID_DEMO_FRONT_MASTER_TARGET_LIST_START = 0x450,
	CAN_ID_DEMO_FRONT_MASTER_TARGET_LIST_END = 0x46F,
	CAN_ID_DEMO_FRONT_SLAVE_TARGET_LIST_START = 0x470,
	CAN_ID_DEMO_FRONT_SLAVE_TARGET_LIST_END = 0x48F,
};

/*************************************************************************************************
 * can id for isotp
 *
 * DSP---ICI_TX_ID-->BUS
 * DSP<--ICI_RX_ID---BUS
 *
 *************************************************************************************************/
typedef enum
{
    ICI_RX_ID = 0x200,
    ICI_TX_ID = 0x210,
}ISOTP_CAN_ID;

#endif /* CAN_ID_H_ */
