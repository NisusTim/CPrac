/*
 * json_debug_info.h
 *
 *  Created on: 2019/7/29
 *      Author: MSN
 */

#ifndef JSON_JSON_DEBUG_INFO_H_
#define JSON_JSON_DEBUG_INFO_H_

#include <stdbool.h>
#include "json_format.h"
#include "customer.h"

#define MAX_DBG_DATA_LENGTH	10
#define MAX_NAME_SIZE		10

typedef enum
{
	DBG_INFO_TYPE_F32,
	DBG_INFO_TYPE_U32,
}DBG_INFO_TYPE;

typedef enum
{
	RDIS_SUCCESS,
	RDIS_REDEFINE,
	RDIS_BUFFER_FULL,
}REG_DBG_INFO_STATUS;

typedef struct
{
	uint32_t data[MAX_DBG_DATA_LENGTH];
}DbgInfo;

typedef struct
{
	PropertyHeader header;
	DbgInfo dbg_info;
}JsonDbgInfoData;

#if JSON_LIST_EN
void init_json_dbg_info(void);
void set_json_dbg_info_flag(int flag);
int get_json_dbg_info_flag(void);
void get_json_file_header_of_dbg_info(JsonFileHeader *file_header);
JsonDbgInfoData compose_dbg_info_to_data_of_json_frame_data(void);
REG_DBG_INFO_STATUS reg_dbg_info(char *name, DBG_INFO_TYPE type);
void send_dbg_info(const char *name, const uint32_t *value);
void reg_tx_function(void(*func)(void));
#endif

#endif /* JSON_JSON_DEBUG_INFO_H_ */
