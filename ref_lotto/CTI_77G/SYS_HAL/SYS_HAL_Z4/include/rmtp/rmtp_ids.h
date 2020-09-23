/*
 * rmtp_ids.h
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */

#ifndef _RMTP_IDS_H_
#define _RMTP_IDS_H_

#define OBJ_ID_RADAR_SYSYTEM 				0x00 // index:0
#define OBJ_ID_SYSYTEM_SECURITY 			0x01 // index:1
//#define OBJ_ID_MEASUREMENT_LIST 			0x02 // (X)
#define OBJ_ID_TARGET_LIST 					0x03 // index:2
#define OBJ_ID_RADAR_FIELD_OF_VIEW 			0x04 // index:3
#define OBJ_ID_SIGNAL_PROCESS               0x05 // index:4
#define OBJ_ID_COMMUNICATION_SETTING        0x06 // index:5 
#define OBJ_ID_SIGNAL_PROCESS_PARAMETER 	0x07 // index:6 
#define OBJ_ID_PARAMETER_SETTING            0x08 // index:7 
#define OBJ_ID_FIRMWARE_VERSION 			0x10 // index:8 
#define OBJ_ID_FIRMWARE_UPGRADE 			0x11 // index:9 
#define OBJ_ID_HARDWARE_STATUS 				0x12 // index:10
#define OBJ_ID_RADAR_CALIBRATION 			0x13 // index:11
#define OBJ_ID_SYSTEM_CONFIG 				0x14 // index:12
#define	OBJ_ID_SYSTEM_LOG 					0x15 // index:13
#define OBJ_ID_SELF_DIAGNOSTICS 			0x16 // index:14
#define OBJ_ID_RF_SIGNAL 					0x17 // index:15
#define OBJ_ID_RF_IC_SETTING 				0x18 // index:16
#define OBJ_ID_INNER_SAFETY_MONITOR         0x19 // index:17  
#define OBJ_ID_FCW_WARNING_SETTING 			0x1A // index:18

#define MAX_OBJ_NUM							19   // index:19

#endif /* _RMTP_IDS_H_ */
