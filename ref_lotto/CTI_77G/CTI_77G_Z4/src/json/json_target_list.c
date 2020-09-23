/*
 * json_target_list.c
 *
 *  Created on: 2019/8/8
 *      Author: MSN
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "json_format.h"
#include "json_target_list.h"
#include "target.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_TARGET_HDR_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_TARGET_DATA_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_TARGET				"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

enum TARGET_SHAPE_IN_RADAR_TOOL
{
	SHAPE_CIRCLE					= 0,
	SHAPE_CROSS						= 1,
	SHAPE_SQUARE					= 2,
	SHAPE_TRIANGLE					= 3,
	SHAPE_INVERTED_TRIANGLE			= 4
};

enum TARGET_CATEGORY_IN_RADAR_TOOL
{
	CATEGORY_UNKNOWN				= 0,
	CATEGORY_BOUNDRY				= 1,
	CATEGORY_FLYOVER				= 2,
	CATEGORY_DITCHCOVER				= 3,
	CATEGORY_PEDESTRIAN				= 4,
	CATEGORY_SCOOTER				= 5,
	CATEGORY_CAR					= 6,
	CATEGORY_TRUCK					= 7
};

static bool sg_json_target_list_flag = false;

static int target_list_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"target_list\":{\n");
		cnt += sprintf(data + cnt, "\t\"target_header\":{\n");
		cnt += sprintf(data + cnt, JSON_TARGET_HDR_LENGTH, sizeof(TargetHeader));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "frame_number", "u16", offsetof(TargetHeader, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "target_cnt", "u16", offsetof(TargetHeader, target_cnt), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "target_time", "u16", offsetof(TargetHeader, time), 1.0f, "us", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "left_num", "u8", offsetof(TargetHeader, left_num), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "right_num", "u8", offsetof(TargetHeader, right_num), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "degree", "i16", offsetof(TargetHeader, degree), 0.01f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "tunnel_flag", "u8", offsetof(TargetHeader,	tunnel_flag), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "cipv_id", "u8", offsetof(TargetHeader, cipv_id), 1.0f, "N/A", ",\n");
//		cnt += sprintf(data + cnt, JSON_TARGET, "acc_cipv_id", "u8", offsetof(TargetHeader, acc_cipv_id), 1.0f, "N/A", ",\n");
//		cnt += sprintf(data + cnt, JSON_TARGET, "aeb_cipv_id", "u8", offsetof(TargetHeader, aeb_cipv_id), 1.0f, "N/A", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t},\n");
		cnt += sprintf(data + cnt, "\t\"target_data\":{\n");
		cnt += sprintf(data + cnt, JSON_TARGET_DATA_LENGTH, sizeof(TargetData));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "rx", "i16", offsetof(TargetData, iso_rx), 0.01f, "m", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "ry", "i16", offsetof(TargetData, iso_ry), 0.01f, "m", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "vx", "i16", offsetof(TargetData, iso_vx), 0.01f, "m/s", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "vy", "i16", offsetof(TargetData, iso_vy), 0.01f, "m/s", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "absvx", "i16", offsetof(TargetData, iso_abs_vx), 0.01f, "m/s", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "acc_x", "i16", offsetof(TargetData, acc_x), 0.01f, "m/s^2", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "vangle", "i16", offsetof(TargetData, vangle), 0.01f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "id", "u16", offsetof(TargetData, id), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "cip_status", "u8", offsetof(TargetData, cipv_flag), 1.0f, "N/A", ",\n");
//		cnt += sprintf(data + cnt, JSON_TARGET, "acc_cip_status", "u8", offsetof(TargetData, acc_cipv_flag), 1.0f, "N/A", ",\n");
//		cnt += sprintf(data + cnt, JSON_TARGET, "aeb_cip_status", "u8", offsetof(TargetData, aeb_cipv_flag), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "status", "u8", offsetof(TargetData, meas_status), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "prob_exist", "u8", offsetof(TargetData, prob_exist), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "rcs", "u8", offsetof(TargetData, rcs), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "guardrail", "u8", offsetof(TargetData, guardrail_cnt), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "category", "u8", offsetof(TargetData, category), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "prev_ver_dynamic", "u8", offsetof(TargetData, prev_ver_dynamic), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_TARGET, "dynamic_property", "u8", offsetof(TargetData, dynamic_property), 1.0f, "N/A", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_target_list_flag(bool flag)
{
	sg_json_target_list_flag = flag;
}

bool get_json_target_list_flag(void)
{
	return sg_json_target_list_flag;
}

void get_json_file_header_of_target_list(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_TARGET_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = target_list_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonTargetHeader compose_target_list_to_header_of_json_frame_data(frame_data_t* fd)
{
	tracking_group_t *target_group = &fd->trkgrp;
	JsonTargetHeader target_header;

	target_header.header.byte.pcode = CAN_PCODE_TARGET_HEADER;

	target_header.target_header.frame_number = get_frame_counter();
	target_header.target_header.target_cnt = target_group->tcnt;
	target_header.target_header.time = 0; //target_group->time;

	target_header.target_header.left_num = target_group->auto_calib_left_num;
	target_header.target_header.right_num = target_group->auto_calib_right_num;
	target_header.target_header.degree = (int16_t)(target_group->calib_angle*100);
	target_header.target_header.tunnel_flag = target_group->tunnel_flag;

	if(target_group->targets[0].cip)
		target_header.target_header.cipv_id = target_group->targets[0].tracking_id;
	else
		target_header.target_header.cipv_id = 255;

	if(target_group->targets[0].cip_acc)
		target_header.target_header.acc_cipv_id = target_group->targets[0].tracking_id;
	else
		target_header.target_header.acc_cipv_id = 255;

	if(target_group->targets[0].cip_aeb)
		target_header.target_header.aeb_cipv_id = target_group->targets[0].tracking_id;
	else
		target_header.target_header.aeb_cipv_id = 255;

	return target_header;
}

JsonTargetData compose_target_list_to_data_of_json_frame_data(frame_data_t* fd)
{
	tracking_group_t* target_group = &fd->trkgrp;
	JsonTargetData target_data;

	target_data.header.byte.pcode = CAN_PCODE_TARGET_DATA;

	for(uint16_t cnt = 0; cnt < target_group->tcnt; cnt ++)
	{
		target_data.target[cnt].iso_rx = (int16_t)(target_group->targets[cnt].rx * 100);
		target_data.target[cnt].iso_ry = (int16_t)(target_group->targets[cnt].ry * 100);
		target_data.target[cnt].iso_vx = (int16_t)(target_group->targets[cnt].vx * 100);
		target_data.target[cnt].iso_vy = (int16_t)(target_group->targets[cnt].vy * 100);
		target_data.target[cnt].iso_abs_vx = (int16_t)((target_group->targets[cnt].vx + fd->comp_veh_spd) * 100);
		target_data.target[cnt].acc_x = (int16_t)(target_group->targets[cnt].ax * 100);
		target_data.target[cnt].vangle = (int16_t)(target_group->targets[cnt].vangle * 100);
		target_data.target[cnt].id = (uint16_t)target_group->targets[cnt].tracking_id;
		target_data.target[cnt].cipv_flag = target_group->targets[cnt].cip;
		target_data.target[cnt].acc_cipv_flag = target_group->targets[cnt].cip_acc;
		target_data.target[cnt].aeb_cipv_flag = target_group->targets[cnt].cip_aeb;
		target_data.target[cnt].meas_status = target_group->targets[cnt].status;
		target_data.target[cnt].prob_exist = target_group->targets[cnt].probability;
		target_data.target[cnt].rcs = target_group->targets[cnt].rcs_type;
		target_data.target[cnt].guardrail_cnt = target_group->targets[cnt].guardrail_cnt;

		//category
		switch(target_group->targets[cnt].rcs_type)
		{
		case PEDESTRIAN:
			target_data.target[cnt].category = CATEGORY_PEDESTRIAN;
			break;
		case SCOOTER:
			target_data.target[cnt].category = CATEGORY_SCOOTER;
			break;
		case CAR:
			target_data.target[cnt].category = CATEGORY_CAR;
			break;
		case TRUCK:
			target_data.target[cnt].category = CATEGORY_TRUCK;
			break;
		default:
			target_data.target[cnt].category = CATEGORY_UNKNOWN;
		}

		target_data.target[cnt].prev_ver_dynamic = target_group->targets[cnt].dynamic_property;

		//dynamic property: to change target's shape
		switch((int8_t)target_group->targets[cnt].dynamic_property)
		{
		case STANDING:
			target_data.target[cnt].dynamic_property = SHAPE_SQUARE;
			if(target_group->targets[cnt].guardrail_cnt >= 3)
				target_data.target[cnt].category = CATEGORY_BOUNDRY;
			break;
		case STOPPED:
			target_data.target[cnt].dynamic_property = SHAPE_SQUARE;
			break;
		case MOVING:
			target_data.target[cnt].dynamic_property = SHAPE_TRIANGLE;
			break;
		case ONCOMING:
			target_data.target[cnt].dynamic_property = SHAPE_INVERTED_TRIANGLE;
			break;
		case FLYOVER:
			target_data.target[cnt].dynamic_property = SHAPE_SQUARE;
			target_data.target[cnt].category = CATEGORY_FLYOVER;
			break;
		case DITCHCOVER:
			target_data.target[cnt].dynamic_property = SHAPE_SQUARE;
			target_data.target[cnt].category = CATEGORY_DITCHCOVER;
			break;
		default:
			target_data.target[cnt].dynamic_property = SHAPE_CROSS;
			target_data.target[cnt].category = CATEGORY_UNKNOWN;
		}
	}

	return target_data;
}
#endif
