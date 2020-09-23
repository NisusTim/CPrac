/*
 * json_warning_msg.h
 *
 *  Created on: 2019/8/8
 *      Author: MSN
 */

#ifndef JSON_JSON_WARNING_MSG_H_
#define JSON_JSON_WARNING_MSG_H_

#include "json_format.h"
#include "target.h"
#include "customer.h"

typedef struct
{
	uint16_t frame_number;
	uint8_t warn_lvl_fcw;
	uint8_t warn_lvl_rcw;
	uint8_t warn_lvl_cvw;
	uint8_t warn_lvl_bsd;
	uint8_t warn_lvl_lca;
	uint8_t warn_lvl_dow;
	uint8_t warn_lvl_rcta;
	uint8_t warn_lvl_fcta;
	uint8_t warn_lvl_turn;
	uint8_t mode_fcw;
	uint8_t mode_rcw;
	uint8_t mode_cvw;
	uint8_t mode_bsd;
	uint8_t mode_lca;
	uint8_t mode_dow;
	uint8_t mode_rcta;
	uint8_t mode_fcta;
	uint8_t mode_turn;
}WarnData;

typedef struct
{
	PropertyHeader header;
	WarnData warn;
}JsonWarnData;

#if JSON_LIST_EN
void set_json_warn_msg_flag(bool flag);
bool get_json_warn_msg_flag(void);
void get_json_file_header_of_warn_msg(JsonFileHeader *file_header);
JsonWarnData compose_warn_msg_to_data_of_json_frame_data(tracking_group_t *target_group);
#endif

#endif /* JSON_JSON_WARNING_MSG_H_ */
