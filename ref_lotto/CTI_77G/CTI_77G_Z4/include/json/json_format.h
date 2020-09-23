/*
 * json_format.h
 *
 *  Created on: 2019/5/27
 *      Author: MSN
 */

#ifndef __JSON_FORMAT_H_
#define __JSON_FORMAT_H_

#include <stdint.h>

typedef enum
{
	CAN_PCODE_NULL,
	CAN_PCODE_MEMWR,
	CAN_PCODE_MEMRD,
	CAN_PCODE_STRING,
	CAN_PCODE_EXT_BEGIN,

	CAN_PCODE_JSON_HEADER,

	CAN_PCODE_MEAS,
	CAN_PCODE_MEAS_JSON,
	CAN_PCODE_MEAS_HEADER,
	CAN_PCODE_MEAS_DATA,

	CAN_PCODE_VEH_INFO,
	CAN_PCODE_VEH_INFO_JSON,
	CAN_PCODE_VEH_INFO_DATA,

	CAN_PCODE_DBG_INFO,
	CAN_PCODE_DBG_INFO_JSON,
	CAN_PCODE_DBG_INFO_DATA,

	CAN_PCODE_TARGET,
	CAN_PCODE_TARGET_JSON,
	CAN_PCODE_TARGET_HEADER,
	CAN_PCODE_TARGET_DATA,

	CAN_PCODE_WARN,
	CAN_PCODE_WARN_JSON,
	CAN_PCODE_WARN_DATA,

	CAN_PCODE_RADAR_INFO,
	CAN_PCODE_RADAR_INFO_JSON,
	CAN_PCODE_RADAR_INFO_DATA,

	CAN_PCODE_FRAME_INFO,
	CAN_PCODE_FRAME_INFO_JSON,
	CAN_PCODE_FRAME_INFO_DATA,

	CAN_PCODE_NOISE_BASE_INFO,
	CAN_PCODE_NOISE_BASE_INFO_JSON,
	CAN_PCODE_NOISE_BASE_INFO_HEADER,
	CAN_PCODE_NOISE_BASE_INFO_DATA,

	CAN_PCODE_WARN_HEADER,

	CAN_PCODE_IMU_INFO,
	CAN_PCODE_IMU_JSON,
	CAN_PCODE_IMU_DATA,

	CAN_PCODE_END = 0xFF,
}CAN_PCODE_E;

typedef union
{
	uint8_t all_bytes[4];

	struct
	{
		uint8_t pcode;
		uint8_t rsvd_1;
		uint8_t rsvd_2;
		uint8_t rsvd_3;
	}byte;
}PropertyHeader;

typedef struct
{
	struct
	{
		PropertyHeader header_1;
		uint32_t file_header_size;
		uint32_t offset;
		uint32_t param_data_size;
	}header;

	struct
	{
		PropertyHeader header_2;
		char param_data[1500];
	}data;
}JsonFileHeader;

#endif
