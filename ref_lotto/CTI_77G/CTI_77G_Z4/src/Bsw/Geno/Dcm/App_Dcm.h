/*
 * App_Dcm.h
 *
 *  Created on: 2019/10/8/
 *      Author: WoodLiu
 */

#ifndef BSW_GENO_DCM_APP_DCM_H_
#define BSW_GENO_DCM_APP_DCM_H_

#include "Dcm.h"
#include "parameters.h"

#define ADPT_F180_SIZE         			(16u)
#define ADPT_F187_SIZE         			(10u)
#define ADPT_F18C_SIZE         			(10u)
#define ADPT_F193_SIZE         			(15u)
#define ADPT_F198_SIZE         			(10u)
#define ADPT_F199_SIZE         			(4u)

typedef union {
	uint64 Raw;
	uint8 Byte[8];
	struct{
		uint16 RF_Voltage1_too_low:1; 				//Byte 0 bit 7, bit 7       ,63
		uint16 RF_Voltage1_too_high:1; 				//Byte 0 bit 6, bit 6       ,62
		uint16 MCU_Voltage_too_low:1; 				//Byte 0 bit 5, bit 5       ,61
		uint16 MCU_Voltage_too_high:1; 				//Byte 0 bit 4, bit 4       ,60
		uint16 MCU_Temperature_too_low:1; 			//Byte 0 bit 3, bit 3       ,59
		uint16 MCU_Temperature_too_high:1; 			//Byte 0 bit 2, bit 2       ,58
		uint16 Lost_Communication_With_Camera:1; 	//Byte 0 bit 1, bit 1       ,57
		uint16 Communication_Bus_OFF:1; 			//Byte 0 bit 0, bit 0       ,56
		uint16 Invalid_Vehicle_Speed_signal:1; 		//Byte 1 bit 7, bit 15      ,55
		uint16 Missing_Calibration:1; 				//Byte 1 bit 6, bit 14      ,54
		uint16 RF_Temperature_too_low:1; 			//Byte 1 bit 5, bit 13      ,53
		uint16 RF_Temperature_too_high:1; 			//Byte 1 bit 4, bit 12      ,52
		uint16 Battery_Voltage_too_low:1; 			//Byte 1 bit 3, bit 11      ,51
		uint16 Battery_Voltage_too_high:1; 			//Byte 1 bit 2, bit 10      ,50
		uint16 RF_Voltage2_too_low:1; 				//Byte 1 bit 1, bit 9       ,49
		uint16 RF_Voltage2_too_high:1; 				//Byte 1 bit 0, bit 8       ,48
		uint16 :1; 									//Byte 2 bit 7, bit 23      ,47
		uint16 :1; 									//Byte 2 bit 6, bit 22      ,46
		uint16 Radar_Mount_Position_Shift_Error:1; 	//Byte 2 bit 5, bit 21      ,45
		uint16 Radar_block:1;						//Byte 2 bit 4, bit 20      ,44
		uint16 Invalid_IGN_Sta_signal:1; 			//Byte 2 bit 3, bit 19      ,43
		uint16 Invalid_Gear_position_signal:1; 		//Byte 2 bit 2, bit 18      ,42
		uint16 Invalid_Steering_Angle_signal:1; 	//Byte 2 bit 1, bit 17      ,41
		uint16 Invalid_Yaw_Rate_signal:1; 			//Byte 2 bit 0, bit 16      ,40
		uint16 unused1:6;							//Byte 3 bit 7~2, bit 31~26 ,39~34
		uint16 :1; 									//Byte 3 bit 1, bit 25      ,33
		uint16 :1; 									//Byte 3 bit 0, bit 24      ,32
		uint16 unused2;								//Byte 4~5                  ,31~16
		uint16 unused3;								//Byte 6~7                  ,15~0
	};
}RadarFailsafeState_t, *RadarFailsafeState_p;

typedef union {
	uint64 Raw;
	uint8 Byte[8];
	struct{
		uint16 :1; 									//Byte 0 bit 7, bit 7
		uint16 :1; 									//Byte 0 bit 6, bit 6
		uint16 :1; 									//Byte 0 bit 5, bit 5
		uint16 RF_Sensor_fault:1; 					//Byte 0 bit 4, bit 4
		uint16 G_Sensor_fault:1; 					//Byte 0 bit 3, bit 3
		uint16 MCU_Memory_Error:1; 					//Byte 0 bit 2, bit 2
		uint16 MCU_Error:1; 						//Byte 0 bit 1, bit 1
		uint16 MCU_Master_Clock_Error:1; 			//Byte 0 bit 0, bit 0
		uint16 unused1:8;							//Byte 1
		uint16 unused2;								//Byte 2~3
		uint16 unused3;								//Byte 4~5
		uint16 unused4;								//Byte 6~7
	};
}RadarMalfunctionErrorReason_t, *RadarMalfunctionErrorReason_p;

extern FUNC(Std_ReturnType, DCM_CODE) get_rmtp_hcan_config_status(void);

#endif /* BSW_GENO_DCM_APP_DCM_H_ */
