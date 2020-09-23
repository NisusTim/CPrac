/*
 * json_warning_msg.c
 *
 *  Created on: 2019/8/8
 *      Author: MSN
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "json_format.h"
#include "json_warning_msg.h"
#include "frame.h"
#include "target.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_WARN_MSG_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_WARN_MSG	"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

static bool sg_json_warn_msg_flag = false;

static int warn_msg_param_data_in_json(char* data);

static int warn_msg_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"warning_msg\":{\n");
		cnt += sprintf(data + cnt, "\t\"warning_msg_data\":{\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG_LENGTH, sizeof(WarnData));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "frame_number", "u16", offsetof(WarnData, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_fcw", "u8", offsetof(WarnData, warn_lvl_fcw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_rcw", "u8", offsetof(WarnData, warn_lvl_rcw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_cvw", "u8", offsetof(WarnData, warn_lvl_cvw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_bsd", "u8", offsetof(WarnData, warn_lvl_bsd), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_lca", "u8", offsetof(WarnData, warn_lvl_lca), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_dow", "u8", offsetof(WarnData, warn_lvl_dow), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_rcta", "u8", offsetof(WarnData, warn_lvl_rcta), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_fcta", "u8", offsetof(WarnData, warn_lvl_fcta), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "warn_lvl_turn", "u8", offsetof(WarnData, warn_lvl_turn), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_fcw", "u8", offsetof(WarnData, mode_fcw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_rcw", "u8", offsetof(WarnData, mode_rcw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_cvw", "u8", offsetof(WarnData, mode_cvw), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_bsd", "u8", offsetof(WarnData, mode_bsd), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_lca", "u8", offsetof(WarnData, mode_lca), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_dow", "u8", offsetof(WarnData, mode_dow), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_rcta", "u8", offsetof(WarnData, mode_rcta), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_fcta", "u8", offsetof(WarnData, mode_fcta), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_WARN_MSG, "mode_turn", "u8", offsetof(WarnData, mode_turn), 1.0f, "N/A", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_warn_msg_flag(bool flag)
{
	sg_json_warn_msg_flag = flag;
}

bool get_json_warn_msg_flag(void)
{
	return sg_json_warn_msg_flag;
}

void get_json_file_header_of_warn_msg(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_WARN_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = warn_msg_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonWarnData compose_warn_msg_to_data_of_json_frame_data(tracking_group_t *target_group)
{
	JsonWarnData warn_data;

	warn_data.header.byte.pcode = CAN_PCODE_WARN_DATA;

	warn_data.warn.frame_number = get_frame_counter();

	uint8_t fcw_warn = 0;

	for(uint16_t cnt = 0; cnt < target_group->tcnt; cnt ++)
	{
		if(target_group->targets[cnt].cip > fcw_warn)
		{
			fcw_warn = target_group->targets[cnt].cip;
		}
	}

	warn_data.warn.warn_lvl_fcw = fcw_warn;
	warn_data.warn.warn_lvl_rcw = 0;
	warn_data.warn.warn_lvl_cvw = 0;
	warn_data.warn.warn_lvl_bsd = 0;
	warn_data.warn.warn_lvl_lca = 0;
	warn_data.warn.warn_lvl_dow = 0;
	warn_data.warn.warn_lvl_rcta = 0;
	warn_data.warn.warn_lvl_fcta = 0;
	warn_data.warn.warn_lvl_turn = 0;
	warn_data.warn.mode_fcw = 1;
	warn_data.warn.mode_rcw = 0;
	warn_data.warn.mode_cvw = 0;
	warn_data.warn.mode_bsd = 0;
	warn_data.warn.mode_lca = 0;
	warn_data.warn.mode_dow = 0;
	warn_data.warn.mode_rcta = 0;
	warn_data.warn.mode_fcta = 0;
	warn_data.warn.mode_turn = 0;

	return warn_data;
}
#endif
