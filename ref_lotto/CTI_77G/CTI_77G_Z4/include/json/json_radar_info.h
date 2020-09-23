/*
 * json_radar_info.h
 *
 *  Created on: 2019/8/21
 *      Author: MSN
 */

#ifndef JSON_JSON_RADAR_INFO_H_
#define JSON_JSON_RADAR_INFO_H_

#include "json_format.h"
#include "customer.h"

typedef struct
{
	float position_shift_x;
	float position_shift_y;
}RadarInfo;

typedef struct
{
	PropertyHeader header;
	RadarInfo radar_info;
}JsonRadarInfo;

#if JSON_LIST_EN
void get_json_file_header_of_radar_info(JsonFileHeader *file_header);
JsonRadarInfo compose_radar_info_to_data_of_json_frame_data(void);
#endif

#endif /* JSON_JSON_RADAR_INFO_H_ */
