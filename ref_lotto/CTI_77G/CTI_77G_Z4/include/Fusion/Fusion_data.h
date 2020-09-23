/*
 * Fusion_data.h
 *
 *  Created on: 2019¦~12¤ë18¤é
 *      Author: USER
 */

#ifndef FUSION_FUSION_DATA_H_
#define FUSION_FUSION_DATA_H_
#include "typedefs.h"
#include "customer.h"

#ifdef ENABLE_FUSION

typedef enum{
	CAMERA_OBJ_0,			//0
	CAMERA_OBJ_1,			//1
	CAMERA_OBJ_2,			//2
	CAMERA_OBJ_3,			//3
	CAMERA_OBJ_4,			//4
	CAMERA_OBJ_5,			//5
	CAMERA_OBJ_6,			//6
	CAMERA_STATUS,			//7
	CAMREA_LANE_DATA_L,		//8
	CAMERA_LANE_DATA_R,		//9
	FUSION_WARN_INFO,		//10
	FUSION_SETTING_INFO,	//11
	FUS_INVALID				//12

}FUSION_INFO_E;

typedef union Cubtek_Can_Fusion_Camera_Target{
	uint64_t R;
	 struct {
		uint64_t x:8;
		uint64_t y:8;
		uint64_t Vx:8;
		uint64_t Vy:8;
		uint64_t distance:8;
		uint64_t relibility:8;
		uint64_t status:8;
		uint64_t ttc:8;
	  } B;
}CUBTEK_CAN_FUSION_CAMERA_TARGET;

typedef union Cubtek_Can_Fusion_Camera_LD{
	uint64_t R;
	 struct {
		uint64_t Dst_LL:8;
		uint64_t Dst_RL:8;
		uint64_t  :24;
		uint64_t Lane_Stp_ProbOfExist:8;
		uint64_t reserve:1;
		uint64_t Land_V:1;
		uint64_t Land_V1:1;
		uint64_t Land_V2:1;
		uint64_t Lane_Stat:2;
		uint64_t Tend_R:1;
		uint64_t Tend_L:1;
		uint64_t FCW_Act:1;
		uint64_t DSP_Fail:1;
		uint64_t Cam_Fail:1;
		uint64_t LDW_Act:1;
		uint64_t Day_Night_Mode:1;
		uint64_t reserve1:3;
	  } B;
}CUBTEK_CAN_FUSION_CAMERA_LD;

typedef union Cubtek_Can_Fusion_Camera_Lane{
	uint64_t R;
	 struct {
		uint64_t C0_sign :1;
		uint64_t C0_num  :11;
		uint64_t C0_exp  :4;
		uint64_t C1_sign :1;
		uint64_t C1_num  :11;
		uint64_t C1_exp  :4;
		uint64_t C2_sign :1;
		uint64_t C2_num  :11;
		uint64_t C2_exp  :4;
		uint64_t C3_sign :1;
		uint64_t C3_num  :11;
		uint64_t C3_exp  :4;
	  } B;
}CUBTEK_CAN_FUSION_CAMERA_LANE;

typedef struct Cubtek_Fusion_warning_request{
	uint8_t FUS_WARNING_STA:4;
	uint8_t reserve:2;
	uint8_t LD_WARNING_STA:2;
	uint8_t Fatigue_WARNING_STA:4;
	uint8_t UFCW_WARNING_STA:4;
	uint8_t HMW_WARNING_STA:1;
	uint8_t HMW_WARNING_NUM:7;
	uint8_t VB_WARNING_STA:1;
	uint8_t VB_WARNING_NUM:7;
	uint8_t Func_Status:8;
	uint8_t reserve_5;
	uint8_t reserve_6;
	uint8_t reserve_7;
}CUBTEK_FUSION_WARN_REQ;


typedef union Cubtek_Can_Fusion_Setting{
	uint64_t R;
	 struct {
		uint64_t FUS_W_TIME :8;
		uint64_t FUS_PRE_TIME  :8;
		uint64_t FUS_FCW_MODE  :4;
		uint64_t FUS_UFCW_MODE :4;
		uint64_t FUS_HMW_MODE  :4;
		uint64_t FUS_VB_MODE  :4;
		uint64_t FUS_DWS_DURING :8;
		uint64_t FUS_DWS_times :8;
		uint64_t FUS_Radar_log :8;
		uint64_t  :8;
	  } B;
}CUBTEK_CAN_FUSION_SETTING;

typedef union Fusion_items{
	uint64_t R[FUS_INVALID];
	struct {
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_0;	//1
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_1;	//2
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_2;	//3
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_3;	//4
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_4;	//5
		CUBTEK_CAN_FUSION_CAMERA_TARGET CAMERA_obj_5;	//6
		CUBTEK_CAN_FUSION_CAMERA_LD CAMERA_STATUS;		//7
		CUBTEK_CAN_FUSION_CAMERA_LANE CAMERA_LANE_Left;	//8
		CUBTEK_CAN_FUSION_CAMERA_LANE CAMERA_LANE_Right;//9
		CUBTEK_FUSION_WARN_REQ FUSION_WARN_OUTPUT;		//10
		CUBTEK_CAN_FUSION_SETTING FUSION_SETTING_DATA;	//11
	}B;
}Fusion_data_info_t,*Fusion_data_info_p;
#if defined(CTI_Z4_0)
void fusion_data_init();

#elif defined(CTI_Z7_0)
void fusion_usage(Fusion_data_info_p v);
void fusion_data_init(void);
#endif
Fusion_data_info_p Fusion_data_get();

#endif //ENABLE_FUSION
#endif /* FUSION_FUSION_DATA_H_ */
