/*
 * json_veh_info.h
 *
 *  Created on: 2019/7/29
 *      Author: MSN
 */

#ifndef JSON_JSON_VEH_INFO_H_
#define JSON_JSON_VEH_INFO_H_

#include <stdbool.h>
#include "json_format.h"
#include "customer.h"

typedef struct
{
	uint16_t frame_number;
	float speed;
	uint32_t turn;
	uint32_t gear;
	float yaw_rate;
	uint32_t door_front_right;
	uint32_t door_front_left;
	uint32_t door_rear_right;
	uint32_t door_rear_left;
	float steering_angle;
	float radius;
	uint16_t reverve;
}VehInfo;

typedef struct
{
	PropertyHeader header;
	VehInfo veh_info;
}JsonVehInfoData;

#if JSON_LIST_EN
void set_json_veh_info_flag(bool flag);
bool get_json_veh_info_flag(void);
void get_json_file_header_of_veh_info(JsonFileHeader *file_header);
JsonVehInfoData compose_veh_info_to_data_of_json_frame_data(void);
#endif

#endif /* JSON_JSON_VEH_INFO_H_ */
