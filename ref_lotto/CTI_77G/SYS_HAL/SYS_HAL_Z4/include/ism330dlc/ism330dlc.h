/**
* @file    ism330dlc.h
* @author  msn
* @version 1.0.0
* @date    2018/2/9
* @brief   --
* 
* @note    --
*/
#ifndef __ISM330DLC_H
#define __ISM330DLC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sys_shared.h"

/* Transformation of coordinate system
 * Vehicle			IC
 * coordinate		coordinate
 *
 *					Dir = 0:		Dir = 1:		Dir = 2:		Dir = 3:		Dir = 4:		Dir = 5:
 *
 *	   Z			 Y				   X			X<-@Z			Z@->Y			 Z				Y@->X
 *	   ^			 ^				   ^			   |			 |				 ^				 |
 *	   |			 |				   |			   V			 V				 |				 V
 *	Y<-*X			Z@->X			Y<-@Z			   Y			 X				Y*->X			 Z
 */

#define ISM330DLC_PARS_ID		FOURCC('i','m','u','p')

typedef union Can_Acceration_Format {
  uint64_t R;
  struct {
	  int16_t Xaxis:16;
	  int16_t Yaxis:16;
	  int16_t Zaxis:16;
	  int16_t radar_raw_yawrate:16;
  } B;
} CAN_ACCELERATION_FORMAT;

typedef union Can_YawRate_Format {
  uint64_t R;
  struct {
	  int16_t vehicle_yawrate;
	  int16_t radar_pitchrate;	//Unit: 10^-2 dps.
	  int16_t radar_rollrate;	//Unit: 10^-2 dps.
	  int16_t radar_yawrate;	//Unit: 10^-2 dps.
  } B;
} CAN_YAWRATE_FORMAT;

typedef struct {
	uint8_t		enable_imu;				//0: Off.			1: On.
	uint8_t		send_can_msg;			//0: Off.			1: On.
	uint8_t		yaw_onboard;			//0: OBD's yaw.		1: IMU's yaw.
	uint8_t		debug_mode;				//0: Off.			1: On.	2:More detail info about yaw.
	uint8_t		gy_HPF_LPF1_mode;
	uint8_t		gy_LPF2_mode;
	uint8_t		enable_auto_calib;		//0: Disable.		1: Enable.
	uint8_t		filter_mode;			//0:1st order		1:2nd order
	uint8_t		filter_coef[2];			//0: 10^-2 dps		1: imu bw filter
	uint8_t		mthld;
	uint8_t		yaw_rate_thld[4];		//[spd(kph), yaw(10^-1 dps), laneW(10^-1 m), laneL(m)]
	uint16_t	calib_flag;
	int8_t		calib_temp[16];			//0: -40, 1: -30, ..., 13: 90, 14: 100, 15: 110. interval 10 degC
	int8_t		zero_g[3][16];			//[axis][temp], unit: mg.
	int16_t		zrl[3][16];				//[axis][temp], unit: mdps.
	float		ar_gain[3];				//angular rate gain
	uint8_t		dir;
	uint8_t		reserve[2];
}ism330dlc_info_t, *ism330dlc_info_p;

typedef struct {
	pars_header_t		hdr;
	ism330dlc_info_t	info;
}ism330dlc_pars_t, *ism330dlc_pars_p;

typedef enum {
	Xaxis	=  0,
	Yaxis	=  1,
	Zaxis	=  2,
} ism330dlc_xl_coord_t;

typedef enum {
	Pitchaxis	=  0,
	Yawaxis		=  1,
	Rollaxis	=  2,
} ism330dlc_gy_coord_t;

typedef struct {
	int8_t	calib_temp;				//temperature, degC
	int8_t	zero_g[3];				//[axis][temp], unit: mg.
	float	zrl[3];					//[axis][temp], unit: mdps.
	uint8_t result;					//0: Success, 1: ERROR
	uint8_t reserve[3];
}imu_calib_result_t, *imu_calib_result_p;

typedef struct {
	int8_t	acc_slope_table[3][15];		//unit: 100 * mg/temp
	int8_t	acc_offset_table[3][15];	//unit: mg
	int16_t	gyro_slope_table[3][15];	//unit: 100 * mdps/temp
	int16_t	gyro_offset_table[3][15];	//unit: mdps
	int8_t	acc_slope[3];				//unit: 100 * mg/temp
	int8_t	acc_offset[3];				//unit: mg
	int16_t	gyro_slope[3];				//unit: 100 * mdps/temp
	int16_t	gyro_offset[3];				//unit: mdps
}imu_comp_info_t, *imu_comp_info_p;

typedef void (*imu_self_test_cb)(int res);
typedef void (*imu_self_calib_cb)(imu_calib_result_p res);

extern void init_ism330dlc(void);
//extern void read_ism330dlc_angular_rate(void);
extern void ism330dlc_timer_enable(void);
extern void ism330dlc_timer_disable(void);
extern uint8_t ism330dlc_self_calibration_by_RMTP(imu_self_calib_cb cb);
extern uint8_t imu_self_test_by_RMTP(imu_self_test_cb cb);
extern ism330dlc_info_p ism330dlc_get_IMU_info(void);
extern void ism330dlc_set_IMU_calib_value(ism330dlc_info_p imu_info);

#ifdef __cplusplus
}
#endif

#endif
