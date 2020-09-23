/*
 * json_meas_list.h
 *
 *  Created on: 2019/5/27
 *      Author: MSN
 */

#ifndef __JSON_MEAS_LIST_H_
#define __JSON_MEAS_LIST_H_

#include <stdint.h>
#include <stdbool.h>
#include "sys_shared.h"
#include "json_format.h"
#include "target.h"
#include "customer.h"

#define JSON_MEAS_MEMBER	\
	float iso_angle;		\
	int16_t v_idx;			\
	int16_t r_idx;			\
	int16_t mag;			\
	int16_t vangle;

typedef struct
{
	uint32_t time;
	float vunit;
	float runit;
	uint16_t vbins;
	uint16_t rbins;
	uint16_t start;
	uint16_t end;
	uint16_t frame_number;
	uint16_t cnt_of_multichirps;
	uint8_t meas_cnt;
	float	yaw_rate;
	float	acc_z;
	float	comp_veh_spd;
	uint8_t ctx_idx;
	uint8_t rcnt;
	uint8_t state;
}MeasHeader;

typedef struct
{
	PropertyHeader header;
	MeasHeader meas_header;
}JsonMeasHeader;

typedef struct
{
	JSON_MEAS_MEMBER
}MeasData;

typedef struct
{
	PropertyHeader header;
	MeasData meas[MAX_COUNT_OF_MEASUREMENTS_PER_FRAME];
}JsonMeasData;

#if JSON_LIST_EN
void set_json_meas_list_flag(bool flag);
bool get_json_meas_list_flag(void);
void get_json_file_header_of_meas_list(JsonFileHeader *file_header);
JsonMeasHeader compose_meas_list_to_header_of_json_frame_data(frame_data_p fd);
JsonMeasData compose_meas_list_to_data_of_json_frame_data(uint16_t *mcnt);
void send_short_range_rf_data_to_meas_list(target_group_t *meas_group);
//void clear_json_meas_regs();
#endif

#endif
