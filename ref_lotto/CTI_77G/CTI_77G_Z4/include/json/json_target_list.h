/*
 * json_target_list.h
 *
 *  Created on: 2019/8/8
 *      Author: MSN
 */

#ifndef JSON_JSON_TARGET_LIST_H_
#define JSON_JSON_TARGET_LIST_H_

#include <stdbool.h>
#include "json_format.h"
#include "target.h"
#include "frame.h"
#include "customer.h"

typedef struct
{
	uint16_t frame_number;
	uint16_t target_cnt;
	uint16_t time;
	uint8_t left_num;
	uint8_t right_num;
	int16_t	degree;
	uint8_t tunnel_flag;	//0 = inactive, 1 = active
	uint8_t cipv_id;		//invalid = 255
	uint8_t acc_cipv_id;	//invalid = 255
	uint8_t aeb_cipv_id;	//invalid = 255
	uint8_t reserve[2];
}TargetHeader;

typedef struct
{
	PropertyHeader header;
	TargetHeader target_header;
}JsonTargetHeader;

typedef struct
{
	int16_t iso_rx;				//rx scale 0.01
	int16_t iso_ry;				//ry scale 0.01
	int16_t iso_vx;				//vx scale 0.01
	int16_t iso_vy;				//vy scale 0.01
	int16_t iso_abs_vx;			//abs_vx scale 0.01
	int16_t acc_x;				//iso acc x
	int16_t vangle;
//	int16_t mag;				//mag scale 0.01
	uint16_t id;
//	int16_t dx;
//	int16_t dy;
	uint8_t cipv_flag;
	uint8_t acc_cipv_flag;
	uint8_t aeb_cipv_flag;
	uint8_t meas_status;		//0:no onject, 1:new object, 2:object predicted, 3:object measured, 4:invalid
	uint8_t prob_exist;			//0:25%, 1:50%, 2:75%, 3:99%
	uint8_t rcs;				//0:unknown, 1:pedestrian, 2:bike, 3:car, 4:truck
	uint8_t guardrail_cnt;
	uint8_t category;			//0:unknown, 1:boundry, 2:flyover, 3:ditchcover, 4:pedestrian, 5:scooter, 6:car, 7:truck
	uint8_t prev_ver_dynamic;	//0:unclassified, 1:standing, 2:stopped, 3:moving, 4:oncoming, 5:flyover, 6:ditchcover
	uint8_t dynamic_property;	//0:unclassified, 1:standing, 2:stopped, 3:moving, 4:oncoming
	uint8_t reserve[2];
}TargetData;

typedef struct
{
	PropertyHeader header;
	TargetData target[MAX_COUNT_OF_TRACKING];
}JsonTargetData;

#if JSON_LIST_EN
void set_json_target_list_flag(bool flag);
bool get_json_target_list_flag(void);
void get_json_file_header_of_target_list(JsonFileHeader *file_header);
JsonTargetHeader compose_target_list_to_header_of_json_frame_data(frame_data_t* fd);
JsonTargetData compose_target_list_to_data_of_json_frame_data(frame_data_t* fd);
#endif

#endif /* JSON_JSON_TARGET_LIST_H_ */
