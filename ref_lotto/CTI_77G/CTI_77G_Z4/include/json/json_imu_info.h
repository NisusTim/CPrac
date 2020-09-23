/*
 * json_imu_info.h
 *
 *  Created on: 2019/10/14
 *      Author: Gavin
 */

#ifndef JSON_JSON_IMU_INFO_H_
#define JSON_JSON_IMU_INFO_H_

#include <stdbool.h>
#include "json_format.h"
#include "ism330dlc.h"
#include "customer.h"

typedef struct
{
	uint16_t frame_number;
	float roll_rate;
	float pitch_rate;
	float yaw_rate;
	float acc_x;
	float acc_y;
	float acc_z;
	float temperature;
	int16_t gyro_slope_roll;
	int16_t gyro_slope_pitch;
	int16_t gyro_slope_yaw;
	int16_t gyro_offset_roll;
	int16_t gyro_offset_pitch;
	int16_t gyro_offset_yaw;
	int8_t acc_slope_x;
	int8_t acc_slope_y;
	int8_t acc_slope_z;
	int8_t acc_offset_x;
	int8_t acc_offset_y;
	int8_t acc_offset_z;
	float radius;
	int16_t reserve;
}IMUHeader;

typedef struct
{
	PropertyHeader header;
	IMUHeader imu_header;
}JsonIMUHeader;

#if JSON_LIST_EN
void set_json_imu_info_flag(bool flag);
bool get_json_imu_info_flag(void);
void get_json_file_header_of_imu_info(JsonFileHeader *file_header);
JsonIMUHeader compose_imu_info_to_header_of_json_frame_data(void);
void send_imu_comp_data_to_imu_info(imu_comp_info_t *imu_comp_info);
#endif

#endif /* JSON_JSON_IMU_INFO_H_ */
