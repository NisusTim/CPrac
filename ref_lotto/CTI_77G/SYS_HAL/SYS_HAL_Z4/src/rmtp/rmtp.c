/*
 * rmtp.c
 *
 *  Created on: 2017/10/17
 *      Author: Benson
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "console.h"
#include "sys_shared.h"
#include "rmtp_msg.h"
#include "rmtp_ids.h"
#include "rmtp_objs.h"
#include "rmtp_hal.h"
#include "rmtp_api.h"
#include "cubtek_monitor_handler.h"

#ifdef USING_UDS_NM_CAN_0
#include "Bsw_Common.h"
#include "ComStack_Types.h"
#include "App_Dcm.h"
#endif

static void rmtp_rx_handle(uint8_t netId, uint8_t *data);
static void rmtp_product_init(void);

static uint8_t dev_id;
static uint8_t ext_dev_id;
static uint8_t customer;
static uint8_t product;

void rmtp_init()
{
	uint8_t pkt[6] = {0};

	dev_id = product_info_get()->device_id % 0x08;
	ext_dev_id = product_info_get()->device_id / 0x08;
	product = product_info_get()->product;
	customer = product_info_get()->customer;
	rmtp_hal_init();
	LOG("[RMTP] devId = 0x%.2x\n", dev_id);
	rmtp_obj_init();
	rmtp_product_init();
	pkt[0] = (product & 0xFF00) >> 8;
	pkt[1] = (product & 0x00FF);
	pkt[2] = (customer & 0xFF00) >> 8;
	pkt[3] = (customer & 0x00FF);
	pkt[4] = (product_info_get()->device_id & 0xFF00) >> 8;
	pkt[5] = (product_info_get()->device_id & 0x00FF);
#ifdef USING_CUBTEK_CAN_0
	rmtp_send_alarm_message(RMTP_ITF_CAN0, OBJ_ID_RADAR_SYSYTEM, ALARM_ID_0, pkt, 6);
#else
	rmtp_send_alarm_message(RMTP_ITF_CAN2, OBJ_ID_RADAR_SYSYTEM, ALARM_ID_0, pkt, 6);
#endif
}

static int rmtp_handle_request_message(uint8_t netId, rmtp_msg_t *msg)
{
	uint8_t admin_state = ADMIN_LOCK;
	rmtp_obj_t *obj = NULL;
	
	if (msg->rmtp.dev_id != dev_id) {
		LOG("[RMTP] devId 0x%.2x unmatched!\n", msg->rmtp.dev_id);
		return RES_DROP_MESSAGE;
	}
	obj = rmtp_get_obj(msg->rmtp.obj_id);
	if (obj == NULL) {
		rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_OBJ_ID_UNSUPPORTED, NULL, 0);
		LOG("[RMTP] objId 0x%.2x unsupported!\n", msg->rmtp.obj_id);
		return RES_OBJ_ID_UNSUPPORTED;
	}
	if (msg->rmtp.attr_id >= obj->attr_num) {
		rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_ATTR_ID_UNSUPPORTED, NULL, 0);
		LOG("[RMTP] attrId 0x%.2x unsupported!\n", msg->rmtp.attr_id);
		return RES_ATTR_ID_UNSUPPORTED;
	}
	admin_state = rmtp_get_admin_state();
	if ((obj->attr_access[msg->rmtp.attr_id] & ATTR_L) && (admin_state == ADMIN_LOCK)) {
		rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_CMD_REJECTED, NULL, 0);
		LOG("[RMTP] attribute access LOCK!\n");
		return RES_CMD_REJECTED;
	}
	if ((msg->rmtp.sub_type == SUB_TYPE_GET) && ((obj->attr_access[msg->rmtp.attr_id] & ATTR_R) == 0)) {
		rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_PARAMETER_ERROR, NULL, 0);
		LOG("[RMTP] no GET Request access!\n");
		return RES_CMD_UNSUPPORTED;
	} else if ((msg->rmtp.sub_type == SUB_TYPE_SET) && ((obj->attr_access[msg->rmtp.attr_id] & ATTR_W) == 0)) {
		rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_PARAMETER_ERROR, NULL, 0);
		LOG("[RMTP] no SET Request access!\n");
		return RES_CMD_UNSUPPORTED;
	}
	if (msg->rmtp.sub_type == SUB_TYPE_GET) {
		if (obj->get_request_msg_handler == NULL) {
			rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_CMD_PROCESS_ERR, NULL, 0);
			LOG("[RMTP] GET Request handler is NULL!\n");
			return RES_SYSTEM_ERROR;
		} else {
			return obj->get_request_msg_handler(netId, msg->rmtp.attr_id, msg->rmtp.data);
		}
	} else if (msg->rmtp.sub_type == SUB_TYPE_SET) {
		if (obj->set_request_msg_handler == NULL) {
			rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_CMD_PROCESS_ERR, NULL, 0);
			LOG("[RMTP] SET Request handler is NULL!\n");
			return RES_SYSTEM_ERROR;
		} else {
			return obj->set_request_msg_handler(netId, msg->rmtp.attr_id, msg->rmtp.data);
		}
	}

	return RES_PARAMETER_ERROR;
}

static int rmtp_handle_response_message(uint8_t netId, rmtp_msg_t *msg)
{
	rmtp_obj_t *obj = NULL;
	
	obj = rmtp_get_obj(msg->rmtp.obj_id);
	if (obj == NULL) {
		LOG("[RMTP] objId 0x%.2x unsupported!\n", msg->rmtp.obj_id);
		return RES_OBJ_ID_UNSUPPORTED;
	}
	if (msg->rmtp.attr_id >= obj->attr_num) {
		LOG("[RMTP] attrId 0x%.2x unsupported!\n", msg->rmtp.attr_id);
		return RES_ATTR_ID_UNSUPPORTED;
	}
	if (msg->rmtp.sub_type == SUB_TYPE_GET) {
		if (obj->get_response_msg_handler == NULL) {
			rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_CMD_PROCESS_ERR, NULL, 0);
			LOG("[RMTP] GET Response handler is NULL!\n");
			return RES_SYSTEM_ERROR;
		} else {
			return obj->get_response_msg_handler(netId, msg->rmtp.attr_id, msg->rmtp.flag, msg->rmtp.data);
		}
	} else if (msg->rmtp.sub_type == SUB_TYPE_SET) {
		if (obj->set_response_msg_handler == NULL) {
			rmtp_send_err_response_message(netId, msg->rmtp.sub_type, msg->rmtp.obj_id, msg->rmtp.attr_id, RES_CMD_PROCESS_ERR, NULL, 0);
			LOG("[RMTP] SET Response handler is NULL!\n");
			return RES_SYSTEM_ERROR;
		} else {
			return obj->set_response_msg_handler(netId, msg->rmtp.attr_id, msg->rmtp.flag, msg->rmtp.data);
		}
	}

	return RES_PARAMETER_ERROR;
}

static int rmtp_handle_notify_message(uint8_t netId, rmtp_msg_t *msg)
{
	rmtp_obj_t *obj = NULL;
	
	obj = rmtp_get_obj(msg->rmtp.obj_id);
	if (obj == NULL) {
		LOG("[RMTP] objId 0x%.2x unsupported!\n", msg->rmtp.obj_id);
		return RES_OBJ_ID_UNSUPPORTED;
	}
	if (msg->rmtp.flag == SUB_TYPE_REPORT) {
		if (msg->rmtp.attr_id >= obj->attr_num) {
			LOG("[RMTP] attrId 0x%.2x unsupported!\n", msg->rmtp.attr_id);
			return RES_ATTR_ID_UNSUPPORTED;
		}
		if (obj->report_msg_handler == NULL) {
			LOG("[RMTP] REPORT handler is NULL!\n");
			return RES_CMD_UNSUPPORTED;
		} else {
			return obj->report_msg_handler(netId, msg->rmtp.attr_id, msg->rmtp.data);
		}
	} else if (msg->rmtp.flag == SUB_TYPE_ALARM) {
		if (msg->alarm.alarm_id >= obj->alarmNum) {
			LOG("[RMTP] evtId 0x%.2x unsupported!\n", msg->alarm.alarm_id);
			return RES_ALARM_ID_UNSUPPORTED;
		}
		if (obj->alarm_msg_handler == NULL) {
			LOG("[RMTP] ALARM handler is NULL!\n");
			return RES_CMD_UNSUPPORTED;
		} else {
			return obj->alarm_msg_handler(netId, msg->alarm.alarm_id, msg->rmtp.data);
		}
	}

	return RES_PARAMETER_ERROR;
}

static int rmtp_handle_data_message(uint8_t netId, rmtp_msg_t *msg)
{
	rmtp_obj_t *obj = NULL;
	
	obj = rmtp_get_obj(msg->rmtp.obj_id);
	if (msg->rmtp.dev_id != dev_id) {
		LOG("[RMTP] devId 0x%.2x unmatched!\n", msg->rmtp.dev_id);
		return RES_DROP_MESSAGE;
	}
	if (obj == NULL) {
		LOG("[RMTP] objId 0x%.2x unsupported!\n", msg->rmtp.obj_id);
		return RES_OBJ_ID_UNSUPPORTED;
	}
	if (obj->data_section_msg_handler == NULL) {
		LOG("[RMTP] DATA handler is NULL!\n");
		return RES_CMD_UNSUPPORTED;
	} else {
		return obj->data_section_msg_handler(netId, msg->data.seqNum, msg->rmtp.data);
	}

	return RES_PARAMETER_ERROR;
}

static void rmtp_rx_handle(uint8_t netId, uint8_t *data)
{
	uint8_t admin_state = ADMIN_LOCK;
	rmtp_msg_t *msg = NULL;

	if (data == NULL) {
		LOG("[RMTP] CAN data is NULL!\n");
		return;
	}
	msg = (rmtp_msg_t *)data;
	if (msg->rmtp.dev_id != dev_id) {
		PKT("[RMTP] devId 0x%.2x unmatched!\n", msg->rmtp.dev_id);
		return;
	}
	admin_state = rmtp_get_admin_state();	
	PKT("[RMTP] RX(%d):\n", (netId - RMTP_ITF_CAN0));
	PKT("  - RMTP header: mt=0x%.2x did=0x%.2x oid=0x%.2x ", msg->rmtp.msg_type, msg->rmtp.dev_id, msg->rmtp.obj_id);
	if (msg->rmtp.msg_type == MSG_TYPE_DATA) {
		PKT("seqNum=0x%.2x\n", msg->data.seqNum);
	} else {
		PKT("st=0x%.2x aid=0x%.2x flag=0x%.2x\n", msg->rmtp.sub_type, msg->rmtp.attr_id, msg->rmtp.flag);
		PKT("  - Data: 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n", msg->rmtp.data[0], msg->rmtp.data[1], msg->rmtp.data[2], msg->rmtp.data[3], msg->rmtp.data[4], msg->rmtp.data[5]);
	}
	switch (msg->rmtp.msg_type) {
		case MSG_TYPE_REQUEST:
			rmtp_handle_request_message(netId, msg);
			return;
		case MSG_TYPE_RESPONSE:
			if (admin_state == ADMIN_UNLOCK) {
				rmtp_handle_response_message(netId, msg);
			}
			return;
		case MSG_TYPE_NOTIFY:
			if (admin_state == ADMIN_UNLOCK) {
				rmtp_handle_notify_message(netId, msg);
			}
			return;
		case MSG_TYPE_DATA:
			if (admin_state == ADMIN_UNLOCK) {
				rmtp_handle_data_message(netId, msg);
			}
			return;
		default:
			return;
	}

	return;
}

#ifdef USING_CUBTEK_CAN_0
static void rmtp_can0_rx_handle(can_message_p can_msg)
{
	uint8_t data[8] = {0};
	memcpy(data, can_msg->pkg.b, 8);
	rmtp_rx_handle(RMTP_ITF_CAN0, data);
	return;
}
#endif
#ifdef USING_UDS_NM_CAN_0
FUNC(void, COM_PUBLIC_CODE) rmtp_can0_rx_handle
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, COM_APPL_DATA, COM_AUTOMOTIVE) PduInfoPtr
)
{
    Std_ReturnType ret = E_OK;
    uint8_t data[8] = {0};
    memcpy(data, PduInfoPtr->SduDataPtr, 8);
    ret = get_rmtp_hcan_config_status();
    if(E_OK == ret )
    {
        rmtp_rx_handle(RMTP_ITF_CAN0, data);
    }
    else
    {
        ret = E_NOT_OK;
    }	
    
    return;
}
#endif

static void rmtp_can2_rx_handle(can_message_p can_msg)
{
	uint8_t data[8] = {0};
	memcpy(data, can_msg->pkg.b, 8);

	//Monitor go to develop mode in force
	monitor_set_develop_mode();

	rmtp_rx_handle(RMTP_ITF_CAN2, data);
	return;
}

static void rmtp_product_init(void)
{
	// CAN0: PC=>0x70=>Radar, Radar=>0x71=>PC (DevID: 0~7)
	// CAN2: PC=>0x80=>Radar, Radar=>0x81=>PC (DevID: 0~7)

    rmtp_api_init(dev_id, CAN_ID_CUBTEK_RMTP_TX_71, CAN_ID_CUBTEK_RMTP_TX_81, 0);
    rmtp_can_tx_init(RMTP_ITF_CAN0);
#ifdef USING_CUBTEK_CAN_0
    can_rx_id_register(CAN_ID_CUBTEK_RMTP_RX_70, CAN_STD_ID_MASK_FULL, "rmtp", (event_proc_p)rmtp_can0_rx_handle);
#endif
    rmtp_can_tx_init(RMTP_ITF_CAN2);
    can2_rx_id_register(CAN_ID_CUBTEK_RMTP_RX_80, CAN_STD_ID_MASK_FULL, "rmtp2", (event_proc_p)rmtp_can2_rx_handle);
}

