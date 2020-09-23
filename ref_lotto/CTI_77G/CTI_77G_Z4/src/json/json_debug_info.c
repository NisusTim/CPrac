/*
 * json_debug_info.c
 *
 *  Created on: 2019/7/29
 *      Author: MSN
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_format.h"
#include "json_debug_info.h"
#include "semaphores.h"
#include "z47_ipc.h"
#include "customer.h"

#if JSON_LIST_EN
#define JSON_DBG_INFO_LENGTH	"\t\t\"length\":%d,\n"
#define JSON_DBG_INFO_BASE		"\t\t\t\"%s\":{\"t\":\"%s\",\"o\":%d,\"s\":1,\"u\":\"N/A\"}%s"

typedef struct
{
	char name[MAX_NAME_SIZE];
	char type[3];
	uint32_t value;
}DbgRegInfo;

typedef struct
{
	DbgRegInfo dbg_reg_info[MAX_DBG_DATA_LENGTH];
	int dbg_info_flag;
}DbgInst;

typedef void (*TxFunc)(void);

#if defined(CTI_Z4_0)
static DbgInst __attribute__((section(".json_dbg")))sg_dbg_inst;
#endif
static DbgInst *sg_dbg_inst_p = NULL;
static TxFunc sg_tx_func = NULL;

static void init_dbg_inst(DbgInst *inst);
static int dbg_info_param_data_in_json(char* data);

void init_json_dbg_info(void)
{
#if defined(CTI_Z4_0)
	init_dbg_inst(&sg_dbg_inst);

	memset(sg_dbg_inst_p->dbg_reg_info, 0, sizeof(sg_dbg_inst_p->dbg_reg_info));

	for(uint32_t cnt = 0; cnt < MAX_DBG_DATA_LENGTH; cnt ++)
	{
		strncpy(sg_dbg_inst_p->dbg_reg_info[cnt].name, "default", MAX_NAME_SIZE);
		strncpy(sg_dbg_inst_p->dbg_reg_info[cnt].type, "u32", 3);
	}

	IPC_SEND_MSG_Z70(MSG_JSON_DBG_INFO, sg_dbg_inst_p, 0);
	IPC_SEND_MSG_Z71(MSG_JSON_DBG_INFO, sg_dbg_inst_p, 0);
#elif defined(CTI_Z7_0) || defined(CTI_Z7_1)
	ipc_reg_msg(MSG_JSON_DBG_INFO, "init_json_dbg_info", (msg_proc_p)init_dbg_inst);
#endif
}

static void init_dbg_inst(DbgInst *inst)
{
	sg_dbg_inst_p = inst;
}

static int dbg_info_param_data_in_json(char* data)
{
	int cnt = 0;

	if (data)
	{
		cnt += sprintf(data + cnt, "{\"dbg_info\":{\n");
		cnt += sprintf(data + cnt, "\t\"dbg_info_data\":{\n");
		cnt += sprintf(data + cnt, JSON_DBG_INFO_LENGTH, sizeof(DbgInfo));
		cnt += sprintf(data + cnt, "\t\t\"info\":{\n");
		for(uint32_t idx = 0; idx < MAX_DBG_DATA_LENGTH; idx ++)
		{
			if(idx < (MAX_DBG_DATA_LENGTH - 1))
			{
				cnt += sprintf(data + cnt,
							   JSON_DBG_INFO_BASE,
							   sg_dbg_inst_p->dbg_reg_info[idx].name,
							   sg_dbg_inst_p->dbg_reg_info[idx].type,
							   offsetof(DbgInfo, data[idx]), ",\n");
			}
			else
			{
				cnt += sprintf(data + cnt,
							   JSON_DBG_INFO_BASE,
							   sg_dbg_inst_p->dbg_reg_info[idx].name,
							   sg_dbg_inst_p->dbg_reg_info[idx].type,
							   offsetof(DbgInfo, data[idx]), "\n");
			}
		}
		cnt += sprintf(data + cnt, "\t\t}\n");
		cnt += sprintf(data + cnt, "\t}\n");
		cnt += sprintf(data + cnt, "}}\n");
	}

	return cnt;
}

void set_json_dbg_info_flag(int flag)
{
	sg_dbg_inst_p->dbg_info_flag = flag;
}

int get_json_dbg_info_flag(void)
{
	return sg_dbg_inst_p->dbg_info_flag;
}

void get_json_file_header_of_dbg_info(JsonFileHeader *file_header)
{
	file_header->header.header_1.byte.pcode = CAN_PCODE_JSON_HEADER;
	file_header->data.header_2.byte.pcode = CAN_PCODE_DBG_INFO_JSON;

	file_header->header.offset = offsetof(JsonFileHeader, data.param_data);
	file_header->header.param_data_size = dbg_info_param_data_in_json(file_header->data.param_data);
	file_header->header.file_header_size = (sizeof(file_header->header.file_header_size) +
									sizeof(file_header->header.offset) +
									sizeof(file_header->header.param_data_size) +
									file_header->header.param_data_size);

}

JsonDbgInfoData compose_dbg_info_to_data_of_json_frame_data(void)
{
	JsonDbgInfoData dbg_info_data;

	dbg_info_data.header.byte.pcode = CAN_PCODE_DBG_INFO_DATA;

	for(uint32_t cnt = 0; cnt < MAX_DBG_DATA_LENGTH; cnt ++)
	{
		dbg_info_data.dbg_info.data[cnt] = sg_dbg_inst_p->dbg_reg_info[cnt].value;
	}

	return dbg_info_data;
}

REG_DBG_INFO_STATUS reg_dbg_info(char *name, DBG_INFO_TYPE type)
{
	SEM_GATE_LOCK(SEM_GATE_REG_JSON_DBG);

	for(uint32_t cnt = 0; cnt < MAX_DBG_DATA_LENGTH; cnt ++)
	{
		if((0 == memcmp(sg_dbg_inst_p->dbg_reg_info[cnt].name, "default", strlen("default"))) &&
		   (0 != memcmp(sg_dbg_inst_p->dbg_reg_info[cnt].name, name, strlen(name))))
		{
			strncpy(sg_dbg_inst_p->dbg_reg_info[cnt].name, name, MAX_NAME_SIZE);

			switch(type)
			{
			case DBG_INFO_TYPE_F32:

				strncpy(sg_dbg_inst_p->dbg_reg_info[cnt].type, "f32", 3);

				break;

			case DBG_INFO_TYPE_U32:
			default :

				strncpy(sg_dbg_inst_p->dbg_reg_info[cnt].type, "u32", 3);

				break;
			}

			SEM_GATE_UNLOCK(SEM_GATE_REG_JSON_DBG);

			return RDIS_SUCCESS;
		}
		else if(0 == memcmp(sg_dbg_inst_p->dbg_reg_info[cnt].name, name, strlen(name)))
		{
			SEM_GATE_UNLOCK(SEM_GATE_REG_JSON_DBG);

			return RDIS_REDEFINE;
		}
	}

	SEM_GATE_UNLOCK(SEM_GATE_REG_JSON_DBG);

	return RDIS_BUFFER_FULL;
}

void send_dbg_info(const char *name, const uint32_t *value)
{
	if(true == sg_dbg_inst_p->dbg_info_flag)
	{
		SEM_GATE_LOCK(SEM_GATE_SEND_JSON_DBG);

		for(uint32_t cnt = 0; cnt < MAX_DBG_DATA_LENGTH; cnt ++)
		{
			if(0 == memcmp(sg_dbg_inst_p->dbg_reg_info[cnt].name, name, strlen(name)))
			{
				sg_dbg_inst_p->dbg_reg_info[cnt].value = *value;

				cnt = MAX_DBG_DATA_LENGTH;
			}
		}

		SEM_GATE_UNLOCK(SEM_GATE_SEND_JSON_DBG);

#if defined(CTI_Z4_0)
		if(NULL != sg_tx_func)
		{
			sg_tx_func();
		}
#elif defined(CTI_Z7_0) || defined(CTI_Z7_1)
		IPC_SEND_MSG_Z40(MSG_JSON_DBG_INFO, NULL, 0);
#endif
	}
}

void reg_tx_function(void(*func)(void))
{
	sg_tx_func = func;
}
#endif
