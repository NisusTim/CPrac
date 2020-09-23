/*
 * json_veh_info.c
 *
 *  Created on: 2019/7/26
 *      Author: MSN
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "json_veh_info.h"
#include "vehicle.h"
#include "frame.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_VEH_INFO_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_VEH_INFO			"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

static bool sg_json_veh_info_flag = false;

static int veh_info_param_data_in_json(char* data);

static int veh_info_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"veh_info\":{\n");
		cnt += sprintf(data + cnt, "\t\"veh_info_data\":{\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO_LENGTH, sizeof(VehInfo));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "frame_number", "u16", offsetof(VehInfo, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "speed", "f32", offsetof(VehInfo, speed), 1.0f, "km/h", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "turn", "u32", offsetof(VehInfo, turn), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "gear", "u32", offsetof(VehInfo, gear), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "yaw_rate", "f32", offsetof(VehInfo, yaw_rate), 1.0f, "deg/s", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "door_front_right", "u32", offsetof(VehInfo, door_front_right), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "door_front_left", "u32", offsetof(VehInfo, door_front_left), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "door_rear_right", "u32", offsetof(VehInfo, door_rear_right), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "door_rear_left", "u32", offsetof(VehInfo, door_rear_left), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "steering_angle", "f32", offsetof(VehInfo, steering_angle), 1.0f, "deg", ",\n");
		cnt += sprintf(data + cnt, JSON_VEH_INFO, "radius", "f32", offsetof(VehInfo, radius), 1.0f, "m", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_veh_info_flag(bool flag)
{
	sg_json_veh_info_flag = flag;
}

bool get_json_veh_info_flag(void)
{
	return sg_json_veh_info_flag;
}

void get_json_file_header_of_veh_info(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_VEH_INFO_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = veh_info_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);

}

JsonVehInfoData compose_veh_info_to_data_of_json_frame_data(void)
{
	JsonVehInfoData veh_info_data;

	veh_info_data.header.byte.pcode = CAN_PCODE_VEH_INFO_DATA;

	veh_info_data.veh_info.frame_number = get_frame_counter();
	veh_info_data.veh_info.speed = (VEH_STATUS_VALID == get_eps_speed_status()) ?
			get_eps_speed_value() : 0.0f;
	veh_info_data.veh_info.turn = (VEH_STATUS_VALID == get_turn_indicator_status()) ?
			get_turn_indicator_value() : VEH_TRUN_INDICATOR_ALL_OFF;
	veh_info_data.veh_info.gear = (VEH_STATUS_VALID == get_gear_status()) ?
			get_gear_value() : VEH_GEAR_UNKNOWN;
	veh_info_data.veh_info.yaw_rate = (VEH_STATUS_VALID == get_yaw_rate_status()) ?
			get_yaw_rate_value() : 0.0f;
	veh_info_data.veh_info.door_front_right = (VEH_STATUS_VALID == get_door_status()) ?
			get_door_value(VEH_DOOR_FRONT_RIGHT) : VEH_DOOR_STATUS_CLOSE;
	veh_info_data.veh_info.door_front_left = (VEH_STATUS_VALID == get_door_status()) ?
			get_door_value(VEH_DOOR_FRONT_LEFT) : VEH_DOOR_STATUS_CLOSE;
	veh_info_data.veh_info.door_rear_right = (VEH_STATUS_VALID == get_door_status()) ?
			get_door_value(VEH_DOOR_REAR_RIGHT) : VEH_DOOR_STATUS_CLOSE;
	veh_info_data.veh_info.door_rear_left = (VEH_STATUS_VALID == get_door_status()) ?
			get_door_value(VEH_DOOR_REAR_LEFT) : VEH_DOOR_STATUS_CLOSE;
	veh_info_data.veh_info.steering_angle = (VEH_STATUS_VALID == get_steering_angle_status()) ?
			get_steering_angle_value() : 0.0f;
	veh_info_data.veh_info.radius = (VEH_STATUS_VALID == get_veh_raduis_status()) ?
			get_veh_radius_value() : 0.0f;

	return veh_info_data;
}
#endif
