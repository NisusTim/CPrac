/*
 * json_frame_info.h
 *
 *  Created on: 2019/8/21
 *      Author: MSN
 */

#ifndef JSON_JSON_FRAME_INFO_H_
#define JSON_JSON_FRAME_INFO_H_

#include "json_format.h"
#include "customer.h"

typedef struct
{
	uint16_t frame_number;
	float frame_time;
	uint8_t long_range_tx_gain;
	uint8_t long_range_rx_gain;
	uint8_t short_range_tx_gain;
	uint8_t short_range_rx_gain;
	float long_range_chirp_time;
	float short_range_chirp_time;
	uint16_t reverve;
}FrameInfo;

typedef struct
{
	PropertyHeader header;
	FrameInfo frame_info;
}JsonFrameInfo;

#if JSON_LIST_EN
void set_json_frame_info_flag(bool flag);
bool get_json_frame_info_flag(void);
void get_json_file_header_of_frame_info(JsonFileHeader *file_header);
JsonFrameInfo compose_frame_info_to_data_of_json_frame_data(uint16_t frame_time);
void send_long_range_rf_data_to_frame_info(uint8_t txgain, uint8_t rxgain, float chirp_time);
void send_short_range_rf_data_to_frame_info(uint8_t txgain, uint8_t rxgain, float chirp_time);
#endif

#endif /* JSON_JSON_FRAME_INFO_H_ */
