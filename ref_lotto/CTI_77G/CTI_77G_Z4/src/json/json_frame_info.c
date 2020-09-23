/*
 * json_frame_info.c
 *
 *  Created on: 2019/8/21
 *      Author: MSN
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "json_format.h"
#include "json_frame_info.h"
#include "frame.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_FRAME_INFO_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_FRAME_INFO			"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

JsonFrameInfo info;

static bool sg_json_frame_info_flag = false;

static int frame_info_param_data_in_json(char* data);

static int frame_info_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"frame_info\":{\n");
		cnt += sprintf(data + cnt, "\t\"frame_info_data\":{\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO_LENGTH, sizeof(FrameInfo));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "frame_number", "u16", offsetof(FrameInfo, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "frame_time", "f32", offsetof(FrameInfo, frame_time), 1.0f, "ms", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "long_tx_gain", "u8", offsetof(FrameInfo, long_range_tx_gain), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "long_rx_gain", "u8", offsetof(FrameInfo, long_range_rx_gain), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "short_tx_gain", "u8", offsetof(FrameInfo, short_range_tx_gain), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "short_rx_gain", "u8", offsetof(FrameInfo, short_range_rx_gain), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "long_chirp_time", "f32", offsetof(FrameInfo, long_range_chirp_time), 1.0f, "us", ",\n");
		cnt += sprintf(data + cnt, JSON_FRAME_INFO, "short_chirp_time", "f32", offsetof(FrameInfo, short_range_chirp_time), 1.0f, "us", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_frame_info_flag(bool flag)
{
	sg_json_frame_info_flag = flag;
}

bool get_json_frame_info_flag(void)
{
	return sg_json_frame_info_flag;
}

void get_json_file_header_of_frame_info(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_FRAME_INFO_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = frame_info_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonFrameInfo compose_frame_info_to_data_of_json_frame_data(uint16_t frame_time)
{
	info.header.byte.pcode = CAN_PCODE_FRAME_INFO_DATA;

	info.frame_info.frame_number = get_frame_counter();
	info.frame_info.frame_time = (float)frame_time;

	return info;
}

void send_long_range_rf_data_to_frame_info(uint8_t txgain, uint8_t rxgain, float chirp_time)
{
	info.frame_info.long_range_tx_gain = txgain;
	info.frame_info.long_range_rx_gain = rxgain;
	info.frame_info.long_range_chirp_time = chirp_time;
}

void send_short_range_rf_data_to_frame_info(uint8_t txgain, uint8_t rxgain, float chirp_time)
{
	info.frame_info.short_range_tx_gain = txgain;
	info.frame_info.short_range_rx_gain = rxgain;
	info.frame_info.short_range_chirp_time = chirp_time;
}

#endif
