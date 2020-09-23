/*
 * json_radar_info.c
 *
 *  Created on: 2019/8/21
 *      Author: MSN
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "json_format.h"
#include "json_radar_info.h"
#include "tracking.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_RADAR_INFO_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_RADAR_INFO			"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

static int radar_info_param_data_in_json(char* data);

static int radar_info_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"radar_info\":{\n");
		cnt += sprintf(data + cnt, "\t\"radar_info_data\":{\n");
		cnt += sprintf(data + cnt, JSON_RADAR_INFO_LENGTH, sizeof(RadarInfo));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_RADAR_INFO, "position_shift_x", "f32", offsetof(RadarInfo, position_shift_x), 1.0f, "m", ",\n");
		cnt += sprintf(data + cnt, JSON_RADAR_INFO, "position_shift_y", "f32", offsetof(RadarInfo, position_shift_y), 1.0f, "m", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void get_json_file_header_of_radar_info(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_RADAR_INFO_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = radar_info_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonRadarInfo compose_radar_info_to_data_of_json_frame_data(void)
{
	JsonRadarInfo info;

	info.header.byte.pcode = CAN_PCODE_RADAR_INFO_DATA;

	info.radar_info.position_shift_x = tracking_lateral_shift_get();
	info.radar_info.position_shift_y = tracking_longitudinal_shift_get();

	return info;
}
#endif
