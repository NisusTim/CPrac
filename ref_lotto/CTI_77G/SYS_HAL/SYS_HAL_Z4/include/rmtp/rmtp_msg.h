/*
 * rmtp_msg.h
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */

#ifndef _RMTP_MSG_H_
#define _RMTP_MSG_H_

#define MAX_ATTR_NUM			8
#define RFU						0
#define DATA_MAX_SEQ			31
#define DATA_WIN_SIZE			192 // 32*6
#define BLOCK_ID_DONE			255
#define BLOCK_DATA_SIZE			5

enum {
	MSG_TYPE_REQUEST 			= 0,
	MSG_TYPE_RESPONSE			= 1,
	MSG_TYPE_NOTIFY				= 2,
	MSG_TYPE_DATA				= 3
};

enum {
	ACTION_NONE					= 0,
	ACTION_GET 					= 1,
	ACTION_SET					= 2,
	ACTION_REPORT				= 4,
	ACTION_EVET					= 8,
	ACTION_DATA					= 16
};

enum {
	DEV_ID_FRONT				= 0,
	DEV_ID_FRONT_LEFT			= 1,
	DEV_ID_FRONT_RIGHT			= 2,
	DEV_ID_REAR					= 3,
	DEV_ID_REAR_LEFT			= 4,
	DEV_ID_REAR_RIGHT			= 5
};

enum {
	SUB_TYPE_GET				= 0,
	SUB_TYPE_SET				= 1,
	SUB_TYPE_UNKNOWN			= 255
};

enum {
	SUB_TYPE_REPORT				= 0,
	SUB_TYPE_ALARM				= 1
};

enum {
	RESP_FLAG_OK				= 0,
	RESP_FLAG_ERR				= 1
};

enum {
	RES_SUCCESS 				= 0,
	RES_CMD_REJECTED 			= 1,
	RES_CMD_PROCESS_ERR 		= 2,
	RES_CMD_PROCESS_TIMEOUT		= 3,
	RES_CMD_UNSUPPORTED			= 4,
	RES_OBJ_ID_UNSUPPORTED		= 5,
	RES_ATTR_ID_UNSUPPORTED		= 6,
	RES_ALARM_ID_UNSUPPORTED	= 7,
	RES_PARAMETER_ERROR			= 8,
	RES_SYSTEM_ERROR			= 9,
	RES_SYSTEM_BUSY             = 10,
	RES_ERROR 					= 128,
	RES_DROP_MESSAGE			= 129
};

enum {
	ATTR_NONE					= 0x00,
    ATTR_R                		= 0x01,	// Read
    ATTR_W                 		= 0x02, // Write
    ATTR_N               		= 0x04, // Notification
    ATTR_D               		= 0x08, // Data
	ATTR_L						= 0x10 	// Lock
};

enum {
	ATTR_ID_0					= 0,
    ATTR_ID_1               	= 1,
    ATTR_ID_2             		= 2,
    ATTR_ID_3              		= 3,
    ATTR_ID_4             		= 4,
	ATTR_ID_5              		= 5,
    ATTR_ID_6              		= 6,
    ATTR_ID_7               	= 7,
    ATTR_ID_UNKNOWN				= 255
};

enum {
	ATTR_BIT_MASK_0				= 0x01,
	ATTR_BIT_MASK_1        		= 0x02,
	ATTR_BIT_MASK_2         	= 0x04,
	ATTR_BIT_MASK_3         	= 0x08,
	ATTR_BIT_MASK_4       		= 0x10,
	ATTR_BIT_MASK_5         	= 0x20,
	ATTR_BIT_MASK_6         	= 0x40,
	ATTR_BIT_MASK_7         	= 0x80
};

enum {
	ALARM_ID_0					= 0,
	ALARM_ID_1              	= 1,
	ALARM_ID_2             		= 2,
	ALARM_ID_3             		= 3,
	ALARM_ID_4             		= 4,
	ALARM_ID_5            		= 5,
	ALARM_ID_6             		= 6,
	ALARM_ID_7            		= 7
};

enum {
	FLOW_CTRL_SEND				= 0,
	FLOW_CTRL_WAIT          	= 1,
	FLOW_CTRL_RESEND        	= 2,
	FLOW_CTRL_DONE        		= 3,
	FLOW_CTRL_TIMEOUT			= 4,
	FLOW_CTRL_ABORT        		= 5
};

enum {
	TEST_PASS					= 0,
	TEST_FAIL					= 1
};

enum {
	STATUS_NORMAL				= 0,
	STATUS_ABNORMAL				= 1
};

typedef struct {
	uint8_t	obj_id;
	uint8_t attr_num;
	uint8_t *attr_access;
	uint8_t alarmNum;
	int (*init)(void);
	int (*destroy)(void);
	int (*timeout_handler)(void);
	int (*get_request_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t *data);
	int (*set_request_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t *data);
	int (*get_response_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t flag, uint8_t *data);
	int (*set_response_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t flag, uint8_t *data);
	int (*report_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t *data);
	int (*alarm_msg_handler)(uint8_t netId, uint8_t alarmId, uint8_t *data);
	int (*data_section_msg_handler)(uint8_t netId, uint8_t seqNum, uint8_t *data);
	int (*send_request_msg_handler)(uint8_t netId, uint8_t subType, uint8_t attrId, uint8_t *data, uint8_t size);
	int (*send_report_msg_handler)(uint8_t netId, uint8_t attrId, uint8_t *data, uint8_t size);
	int (*send_alarm_msg_handler)(uint8_t netId, uint8_t alarmId, uint8_t *data, uint8_t size);
	int (*send_data_section_msg_handler)(uint8_t netId, uint8_t *data, uint8_t size);
} rmtp_obj_t;

typedef union {
	uint64_t R;
	struct {
		uint8_t msg_type 	: 2;
		uint8_t obj_id   	: 6;
		uint8_t dev_id   	: 3;
		uint8_t sub_type   	: 1;
		uint8_t attr_id   	: 3;
		uint8_t flag   		: 1;
		uint8_t data[6];
	} rmtp;
	struct {
		uint8_t msg_type 	: 2;
		uint8_t obj_id   	: 6;
		uint8_t dev_id   	: 3;
		uint8_t sub_type   	: 1;
		uint8_t attr_id   	: 3;
		uint8_t flag   		: 1;
		uint8_t res_code;
		uint8_t data[5];
	} err;
	struct {
		uint8_t msg_type 	: 2;
		uint8_t obj_id   	: 6;
		uint8_t dev_id   	: 3;
		uint8_t sub_type   	: 1;
		uint8_t alarm_id   	: 3;
		uint8_t flag   		: 1;
		uint8_t data[6];
	} alarm;
	struct {
		uint8_t msg_type 	: 2;
		uint8_t obj_id   	: 6;
		uint8_t dev_id   	: 3;
		uint8_t seqNum   	: 5;
		uint8_t data[6];
	} data;
} rmtp_msg_t;

#endif /* _RMTP_MSG_H_ */
