/*
 * json_imu_info.c
 *
 *  Created on: 2019/10/14
 *      Author: Gavin
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vehicle.h"
#include "json_format.h"
#include "json_imu_info.h"
#include "frame.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_IMU_HDR_LENGTH		"\t\t\"length\":%d,\n"
#define JSON_IMU_DATA_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_IMU				"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

static bool sg_json_imu_info_flag = false;
JsonIMUHeader imu_header = {};

static int imu_info_param_data_in_json(char* data);

static int imu_info_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"imu_info\":{\n");
		cnt += sprintf(data + cnt, "\t\"imu_info_data\":{\n");
		cnt += sprintf(data + cnt, JSON_IMU_HDR_LENGTH, sizeof(IMUHeader));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_IMU, "frame_number", "u16", offsetof(IMUHeader, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "roll_rate", "f32", offsetof(IMUHeader, roll_rate), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "pitch_rate", "f32", offsetof(IMUHeader, pitch_rate), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "yaw_rate", "f32", offsetof(IMUHeader, yaw_rate), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_x", "f32", offsetof(IMUHeader, acc_x), 0.001f, "g", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_y", "f32", offsetof(IMUHeader, acc_y), 0.001f, "g", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_z", "f32", offsetof(IMUHeader, acc_z), 0.001f, "g", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "temperature", "f32", offsetof(IMUHeader, temperature), 1.0f, "deg", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_slope_roll", "i16", offsetof(IMUHeader, gyro_slope_roll), 0.001f, "mdps/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_slope_pitch", "i16", offsetof(IMUHeader, gyro_slope_pitch), 0.001f, "mdps/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_slope_yaw", "i16", offsetof(IMUHeader, gyro_slope_yaw), 0.001f, "mdps/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_offset_roll", "i16", offsetof(IMUHeader, gyro_offset_roll), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_offset_pitch", "i16", offsetof(IMUHeader, gyro_offset_pitch), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "gyro_offset_yaw", "i16", offsetof(IMUHeader, gyro_offset_yaw), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_slope_x", "i8", offsetof(IMUHeader, acc_slope_x), 0.01f, "mg/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_slope_y", "i8", offsetof(IMUHeader, acc_slope_y), 0.01f, "mg/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_slope_z", "i8", offsetof(IMUHeader, acc_slope_z), 0.01f, "mg/temp", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_offset_x", "i8", offsetof(IMUHeader, acc_offset_x), 1.0f, "mg", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_offset_y", "i8", offsetof(IMUHeader, acc_offset_y), 1.0f, "mg", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "acc_offset_z", "i8", offsetof(IMUHeader, acc_offset_z), 1.0f, "mg", ",\n");
		cnt += sprintf(data + cnt, JSON_IMU, "radius", "f32", offsetof(IMUHeader, radius), 1.0f, "m", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_imu_info_flag(bool flag)
{
	sg_json_imu_info_flag = flag;
}

bool get_json_imu_info_flag(void)
{
	return sg_json_imu_info_flag;
}

void get_json_file_header_of_imu_info(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_IMU_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = imu_info_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonIMUHeader compose_imu_info_to_header_of_json_frame_data(void)
{
//	imu_header.header.byte.pcode = CAN_PCODE_IMU_INFO_HEADER;
	imu_header.header.byte.pcode = CAN_PCODE_IMU_DATA;

	imu_header.imu_header.frame_number = get_frame_counter();
	imu_header.imu_header.roll_rate = (VEH_STATUS_VALID == get_veh_onboard_filtered_roll_rate_status()) ?
			get_veh_onboard_filtered_roll_rate_value() : 0.0f;
	imu_header.imu_header.pitch_rate = (VEH_STATUS_VALID == get_veh_onboard_filtered_pitch_rate_status()) ?
			get_veh_onboard_filtered_pitch_rate_value() : 0.0f;
	imu_header.imu_header.yaw_rate = (VEH_STATUS_VALID == get_veh_onboard_filtered_yaw_rate_status()) ?
			get_veh_onboard_filtered_yaw_rate_value() : 0.0f;
	imu_header.imu_header.acc_x = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_x_status()) ?
			get_veh_onboard_filtered_acc_x_value() : 0.0f;
	imu_header.imu_header.acc_y = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_y_status()) ?
			get_veh_onboard_filtered_acc_y_value() : 0.0f;
	imu_header.imu_header.acc_z = (VEH_STATUS_VALID == get_veh_onboard_filtered_acc_z_status()) ?
			get_veh_onboard_filtered_acc_z_value() : 0.0f;
	imu_header.imu_header.temperature = (VEH_STATUS_VALID == get_veh_onboard_temperature_status()) ?
			get_veh_onboard_temperature_value() : 0.0f;
	imu_header.imu_header.radius = (VEH_STATUS_VALID == get_veh_onboard_radius_status()) ?
			get_veh_onboard_radius_value() : 0.0f;

	return imu_header;
}

void send_imu_comp_data_to_imu_info(imu_comp_info_t *imu_comp_info)
{
	imu_header.imu_header.gyro_slope_roll = imu_comp_info->gyro_slope[Rollaxis];
	imu_header.imu_header.gyro_slope_pitch = imu_comp_info->gyro_slope[Pitchaxis];
	imu_header.imu_header.gyro_slope_yaw = imu_comp_info->gyro_slope[Yawaxis];
	imu_header.imu_header.gyro_offset_roll = imu_comp_info->gyro_offset[Rollaxis];
	imu_header.imu_header.gyro_offset_pitch = imu_comp_info->gyro_offset[Pitchaxis];
	imu_header.imu_header.gyro_offset_yaw = imu_comp_info->gyro_offset[Yawaxis];
	imu_header.imu_header.acc_slope_x = imu_comp_info->acc_slope[Xaxis];
	imu_header.imu_header.acc_slope_y = imu_comp_info->acc_slope[Yaxis];
	imu_header.imu_header.acc_slope_z = imu_comp_info->acc_slope[Zaxis];
	imu_header.imu_header.acc_offset_x = imu_comp_info->acc_offset[Xaxis];
	imu_header.imu_header.acc_offset_y = imu_comp_info->acc_offset[Yaxis];
	imu_header.imu_header.acc_offset_z = imu_comp_info->acc_offset[Zaxis];
}

#endif
