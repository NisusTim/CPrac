/*
 * json_meas_list.c
 *
 *  Created on: 2019/5/27
 *      Author: MSN
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "json_meas_list.h"
#include "json_format.h"
#include "target.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_MEAS_HDR_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_MEAS_DATA_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_MEAS_INFO			"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":%.4f,\"u\":\"%s\"}%s"

static bool sg_json_meas_list_flag = false;
static frame_data_p fdata = NULL;
JsonMeasHeader meas_header = {};

JsonMeasData meas_data = {};
static int meas_list_param_data_in_json(char* data);

static int meas_list_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"meas_list\":{\n");
		cnt += sprintf(data + cnt, "\t\"meas_header\":{\n");
		cnt += sprintf(data + cnt, JSON_MEAS_HDR_LENGTH, sizeof(MeasHeader));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "time", "u32", offsetof(MeasHeader, time), 1.0f, "ms", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "vunit", "f32", offsetof(MeasHeader, vunit), 1.0f, "mps", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "runit", "f32", offsetof(MeasHeader, runit), 1.0f, "m", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "vbins", "u16", offsetof(MeasHeader, vbins), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "rbins", "u16", offsetof(MeasHeader, rbins), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "start", "u16", offsetof(MeasHeader, start), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "end", "u16", offsetof(MeasHeader, end), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "frame_number", "u16", offsetof(MeasHeader, frame_number), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "cnt_of_multichirps", "u16", offsetof(MeasHeader, cnt_of_multichirps), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "meas_cnt", "u8", offsetof(MeasHeader, meas_cnt), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "yaw", "f32", offsetof(MeasHeader, yaw_rate), 1.0f, "dps", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "accz", "f32", offsetof(MeasHeader, acc_z), 1.0f, "g", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "veh_spd", "f32", offsetof(MeasHeader, comp_veh_spd), 1.0f, "m/s", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "ctx_idx", "u8", offsetof(MeasHeader, ctx_idx), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "rcnt", "u8", offsetof(MeasHeader, rcnt), 1.0f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "state", "u8", offsetof(MeasHeader, state), 1.0f, "N/A", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t},\n");
		cnt += sprintf(data + cnt, "\t\"meas_data\":{\n");
		cnt += sprintf(data + cnt, JSON_MEAS_DATA_LENGTH, sizeof(MeasData));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "iso_angle", "f32", offsetof(MeasData, iso_angle), 0.01f, "deg", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "v_idx", "i16", offsetof(MeasData, v_idx), 0.1f, "m/s", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "r_idx", "i16", offsetof(MeasData, r_idx), 0.1f, "m", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "mag", "i16", offsetof(MeasData, mag), 0.01f, "N/A", ",\n");
		cnt += sprintf(data + cnt, JSON_MEAS_INFO, "vangle", "i16", offsetof(MeasData, vangle), 0.01f, "deg", "\n");
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_meas_list_flag(bool flag)
{
	sg_json_meas_list_flag = flag;
}

bool get_json_meas_list_flag(void)
{
	return sg_json_meas_list_flag;
}

void get_json_file_header_of_meas_list(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_MEAS_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = meas_list_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);
}

JsonMeasHeader compose_meas_list_to_header_of_json_frame_data(frame_data_p fd)
{
	fdata = fd;
	target_group_t *meas_group = fdata->tggs;

	meas_header.header.byte.pcode = CAN_PCODE_MEAS_HEADER;
//	meas_header.meas_header.time = meas_group->time;
	meas_header.meas_header.frame_number = get_frame_counter();
//	meas_header.meas_header.cnt_of_multichirps = meas_group->cnt_of_mchpt;
	meas_header.meas_header.meas_cnt = (uint8_t)(fdata->mgrp.mcnt);
	meas_header.meas_header.ctx_idx = meas_group->idx;
//	meas_header.meas_header.rcnt = meas_group->rxcnt;
	meas_header.meas_header.state = meas_group->state;
	meas_header.meas_header.yaw_rate = fdata->yaw_msg;
	meas_header.meas_header.acc_z = fdata->acc_z;
	meas_header.meas_header.comp_veh_spd = fdata->comp_veh_spd;

	return meas_header;
}

JsonMeasData compose_meas_list_to_data_of_json_frame_data(uint16_t *mcnt)
{
	meas_data.header.byte.pcode = CAN_PCODE_MEAS_DATA;

	measurement_group_p curr_mgrp = &fdata->mgrp;
	measurement_p mp = curr_mgrp->measurements;
	*mcnt = curr_mgrp->mcnt;

	for(uint16_t cnt = 0; cnt < curr_mgrp->mcnt; cnt++)
	{
		int16_t tmp_v_idx = (int16_t)(mp->velocity *10 / fdata->tggs->vunit);
		int16_t tmp_r_idx = (int16_t)(mp->range *10 / fdata->tggs->runit);
		// Front Radar need transfer radar angle to iso angle by multiple (-1)
		meas_data.meas[cnt].iso_angle = (-1) * mp->angle * 100;
		meas_data.meas[cnt].v_idx = tmp_v_idx;
		meas_data.meas[cnt].r_idx = tmp_r_idx;
		meas_data.meas[cnt].mag = (int16_t)(mp->mag * 100);
		meas_data.meas[cnt].vangle = (int16_t)(mp->vangle * 100);
		mp++;
	}

	return meas_data;
}

void send_short_range_rf_data_to_meas_list(target_group_t *meas_group)
{
	meas_header.meas_header.vunit = meas_group->vunit;
	meas_header.meas_header.runit = meas_group->runit;
	meas_header.meas_header.vbins = meas_group->vbins;
	meas_header.meas_header.rbins = meas_group->rbins;
	meas_header.meas_header.start = meas_group->start;
	meas_header.meas_header.end = meas_group->end;
}

//void clear_json_meas_regs()
//{
//	memset(&meas_data, 0, sizeof(JsonMeasData));
//	memset(&meas_header, 0, sizeof(JsonMeasHeader));
//}
#endif
