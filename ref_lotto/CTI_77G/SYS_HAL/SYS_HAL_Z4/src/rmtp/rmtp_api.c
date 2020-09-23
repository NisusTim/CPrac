/*
 * rmtp_api.c
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "rmtp_msg.h"
#include "rmtp_ids.h"
#include "rmtp_hal.h"
#include "rmtp_api.h"
#include "rmtp_objs.h"
#include "sys_shared.h"
#include "App_ComTx.h"
#include "App_Dcm.h"

static uint8_t 			rmtp_data[MAX_PARS_CONTEXTS*4]= {0};
static uint8_t			rmtp_dev_id = 0;
static int 				rmtp_can0_tx_id = 0;
static int 				rmtp_can2_tx_id = 0;
static int 				rmtp_can2_bypass_id = 0;
static uint64_t 		can_packet = 0;
static rmtp_msg_t 		*msg = (rmtp_msg_t *)&can_packet;
static uint8_t 			ciphertext[6] = {0};
static uint8_t			target_info_report_flag = 0;
static uint8_t			target_info_report_can = RMTP_ITF_CAN2;

#ifdef USING_CUBTEK_CAN_0
static rmtp_data_handle_t can0_rmtp_tx_data = {0};
static rmtp_data_handle_p can0_rmtp_tx = &can0_rmtp_tx_data;
#endif
static rmtp_data_handle_t can2_rmtp_tx_data = {0};
static rmtp_data_handle_p can2_rmtp_tx = &can2_rmtp_tx_data;

static void rmtp_api_send_target_info(tracking_group_p tkg);
	
void rmtp_api_init(uint8_t devId, int can0TxId, int can2TxId, int can2BypassId)
{
	rmtp_dev_id = devId;
	rmtp_can0_tx_id = can0TxId;
	rmtp_can2_tx_id = can2TxId;
	rmtp_can2_bypass_id = can2BypassId;
	ipc_reg_msg(MSG_TARGETS_INFO, "tgtinfo", (event_proc_p)rmtp_api_send_target_info);
}

uint8_t* rmtp_get_data()
{
	memset(rmtp_data, 0, MAX_PARS_CONTEXTS*4);
	return (uint8_t *)&rmtp_data[0];
}

void rmtp_set_ciphertext(uint8_t *cipher)
{
	memcpy(ciphertext, cipher, 6);
}

uint8_t* rmtp_get_ciphertext(void)
{
	return ciphertext;
}

int rmtp_api_get_target_info_report_setting(uint8_t *active, uint8_t *canPort)
{
	*active = target_info_report_flag;
	*canPort = target_info_report_can;
	return RES_SUCCESS;
}

int rmtp_api_set_target_info_report_setting(uint8_t active, uint8_t canPort)
{
	target_info_report_flag = active;
	if (canPort == 0) {
		target_info_report_can = RMTP_ITF_CAN0; // HMI-CAN 
	} else if (canPort == 1) {
		target_info_report_can = RMTP_ITF_CAN2; // P-CAN 
	} else {
		return RES_PARAMETER_ERROR;
	}
	return RES_SUCCESS;
}

void rmtp_bypass_message(uint8_t netId, uint8_t *data)
{
	if (netId == RMTP_ITF_CAN0) { // CAN 0
#ifdef USING_UDS_NM_CAN_0
	    if(E_OK == get_rmtp_hcan_config_status())
	    {
	        App_ComTx_RmtpData_Transmit((uint64_t)data[0]);
	    }
#else
		can0_tx_rmtp(rmtp_can0_tx_id, (uint32_t*)data);
#endif
	} else if (netId == RMTP_ITF_CAN2) { // CAN 2
		can2_tx_rmtp(rmtp_can2_bypass_id, (uint32_t*)data);
	} else {
		DBG("Bypass CAN ID %d Error", netId);
	}
}

void rmtp_send_message(uint8_t netId)
{
	PKT("[RMTP] TX(%d):\n", (netId - RMTP_ITF_CAN0));
	PKT("  - RMTP header: mt=0x%.2x did=0x%.2x oid=0x%.2x ", msg->rmtp.msg_type, msg->rmtp.dev_id, msg->rmtp.obj_id);
	if (msg->rmtp.msg_type == MSG_TYPE_DATA) {
		PKT("seqNum=0x%.2x\n", msg->data.seqNum);
	} else {
		PKT("st=0x%.2x aid=0x%.2x flag=0x%.2x\n", msg->rmtp.sub_type, msg->rmtp.attr_id, msg->rmtp.flag);
		PKT("  - Data: 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x\n", msg->rmtp.data[0], msg->rmtp.data[1], msg->rmtp.data[2], msg->rmtp.data[3], msg->rmtp.data[4], msg->rmtp.data[5]);
	}
	if (netId == RMTP_ITF_CAN0) { // CAN 0
#ifdef USING_UDS_NM_CAN_0
	    if(E_OK == get_rmtp_hcan_config_status())
	    {
	        App_ComTx_RmtpData_Transmit(msg->R);
	    }
#else
		can0_tx_rmtp(rmtp_can0_tx_id, (uint32_t*)msg);
#endif
	} else if (netId == RMTP_ITF_CAN2) { // can 2
		can2_tx_rmtp(rmtp_can2_tx_id, (uint32_t*)msg);
	} else {
		DBG("Bypass CAN %d Index Error", netId);
	}
}

int rmtp_send_request_message(uint8_t netId, uint8_t subType, uint8_t devId, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));
	msg->rmtp.msg_type = MSG_TYPE_REQUEST;
	msg->rmtp.dev_id = rmtp_dev_id;
	msg->rmtp.obj_id = objId;
	msg->rmtp.sub_type = subType;
	msg->rmtp.attr_id = attrId;
	msg->rmtp.flag = RFU;
	if (data && (size > 0)) {
		memcpy(msg->rmtp.data, data, size);
	}
	rmtp_send_message(netId);
	
	return RES_SUCCESS;
}

int rmtp_send_ok_response_message(uint8_t netId, uint8_t subType, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));
	msg->rmtp.msg_type = MSG_TYPE_RESPONSE;
	msg->rmtp.dev_id = rmtp_dev_id;
	msg->rmtp.obj_id = objId;
	msg->rmtp.sub_type = subType;
	msg->rmtp.attr_id = attrId;
	msg->rmtp.flag = RESP_FLAG_OK;
	if (data && (size > 0)) {
		memcpy(msg->rmtp.data, data, size);
	}
	rmtp_send_message(netId);

	return RES_SUCCESS;
}

int rmtp_send_err_response_message(uint8_t netId, uint8_t subType, uint8_t objId, uint8_t attrId, uint8_t resCode, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));
	msg->rmtp.msg_type = MSG_TYPE_RESPONSE;
	msg->rmtp.dev_id = rmtp_dev_id;
	msg->rmtp.obj_id = objId;
	msg->rmtp.sub_type = subType;
	msg->rmtp.attr_id = attrId;
	msg->rmtp.flag = RESP_FLAG_ERR;
	msg->rmtp.data[0] = resCode;
	if (data && (size > 0)) {
		memcpy(&msg->rmtp.data[1], data, size);
	}
	rmtp_send_message(netId);

	return RES_SUCCESS;
}

int rmtp_send_report_message(uint8_t netId, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));	
	msg->rmtp.msg_type = MSG_TYPE_NOTIFY;
	msg->rmtp.dev_id = rmtp_dev_id;
	msg->rmtp.obj_id = objId;
	msg->rmtp.sub_type = SUB_TYPE_REPORT;
	msg->rmtp.attr_id = attrId;
	msg->rmtp.flag = RFU;
	if (data && (size > 0)) {
		memcpy(msg->rmtp.data, data, size);
	}
	rmtp_send_message(netId);
	
	return RES_SUCCESS;
}

int rmtp_send_alarm_message(uint8_t netId, uint8_t objId, uint8_t alarmId, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));	
	msg->alarm.msg_type = MSG_TYPE_NOTIFY;
	msg->alarm.dev_id = rmtp_dev_id;
	msg->alarm.obj_id = objId;
	msg->alarm.sub_type = SUB_TYPE_ALARM;
	msg->alarm.alarm_id = alarmId;
	msg->alarm.flag = RFU;
	if (data && (size > 0)) {
		memcpy(msg->rmtp.data, data, size);
	}
	rmtp_send_message(netId);
	
	return RES_SUCCESS;
}

int rmtp_send_data_section_message(uint8_t netId, uint8_t objId, uint8_t seqNum, uint8_t *data, uint8_t size)
{
	memset(msg, 0, sizeof(uint64_t));	
	msg->data.msg_type = MSG_TYPE_DATA;
	msg->data.dev_id = rmtp_dev_id;
	msg->data.obj_id = objId;
	msg->data.seqNum = seqNum;
	if (data && (size > 0)) {
		memcpy(msg->rmtp.data, data, size);
	}
	rmtp_send_message(netId);
	
	return RES_SUCCESS;
}

static int rmtp_obj_send_report_message(uint8_t netId, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size)
{	
	int res;
	rmtp_obj_t *obj = NULL;
	
	obj = rmtp_get_obj(objId);
	if (obj == NULL) {
		LOG("[RMTP] send report msg: obj(0x%.2x) is NULL\n", objId);
		return RES_OBJ_ID_UNSUPPORTED;
	}	
	if (obj->send_report_msg_handler == NULL) {
		LOG("[RMTP] send report msg: obj(0x%.2x) handler is NULL\n", objId);
		return RES_CMD_UNSUPPORTED;
	}
	res = obj->send_report_msg_handler(netId, attrId, data, size);

	return res;
}

static int rmtp_obj_send_alarm_message(uint8_t netId, uint8_t objId, uint8_t alarmId, uint8_t *data, uint8_t size)
{	
	int res;
	rmtp_obj_t *obj = NULL;
	
	obj = rmtp_get_obj(objId);
	if (obj == NULL) {
		LOG("[RMTP] send alarm msg: obj(0x%.2x) is NULL\n", objId);
		return RES_OBJ_ID_UNSUPPORTED;
	}	
	if (obj->send_alarm_msg_handler == NULL) {
		LOG("[RMTP] send alarm msg: obj(0x%.2x) handler is NULL\n", objId);
		return RES_CMD_UNSUPPORTED;
	}
	res = obj->send_alarm_msg_handler(netId, alarmId, data, size);

	return res;
}

/*static int rmtp_obj_send_data_section_message(uint8_t netId, uint8_t objId, uint8_t alarmId, uint8_t *data, uint8_t size)
{
	int res;
	rmtp_obj_t *obj = NULL;

	obj = rmtp_get_obj(objId);
	if (obj == NULL) {
		LOG("[RMTP] send data section msg: obj(0x%.2x) is NULL\n", objId);
		return RES_OBJ_ID_UNSUPPORTED;
	}
	if (obj->send_data_section_msg_handler == NULL) {
		LOG("[RMTP] send data section msg: obj(0x%.2x) handler is NULL\n", objId);
		return RES_CMD_UNSUPPORTED;
	}
	res = obj->send_data_section_msg_handler(netId, data, size);

	return res;
}*/

int rmtp_send_rf_ic_status_message(uint8_t *data, uint8_t size)
{
	if ((data == NULL) || (size > 6)) {
		LOG("[RMTP] rf ic status data is NULL or size(%d) > 6\n", size);
		return RES_PARAMETER_ERROR;
	}
#ifdef USING_CUBTEK_CAN_0
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN0, OBJ_ID_SYSTEM_LOG, ALARM_ID_0, data, size);
#else
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN2, OBJ_ID_SYSTEM_LOG, ALARM_ID_0, data, size);
#endif
}

int rmtp_send_fccu_status_message(uint8_t *data, uint8_t size)
{
	if (data == NULL) {
		LOG("[RMTP] fccu status data is NULL\n");
		return RES_PARAMETER_ERROR;
	}
#ifdef USING_CUBTEK_CAN_0
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN0, OBJ_ID_SYSTEM_LOG, ALARM_ID_1, data, size);
#else
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN2, OBJ_ID_SYSTEM_LOG, ALARM_ID_1, data, size);
#endif
}

int rmtp_send_stack_dump_message(uint8_t *data, uint8_t size)
{
	if (data == NULL) {
		LOG("[RMTP] stack dump data is NULL\n");
		return RES_PARAMETER_ERROR;
	}
#ifdef USING_CUBTEK_CAN_0
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN0, OBJ_ID_SYSTEM_LOG, ALARM_ID_2, data, size);
#else
	return rmtp_obj_send_alarm_message(RMTP_ITF_CAN2, OBJ_ID_SYSTEM_LOG, ALARM_ID_2, data, size);
#endif
}

#if 0
int rmtp_send_measurement_list_report(uint8_t *data, uint8_t size)
{
	return rmtp_send_report_message(RMTP_ITF_CAN0, OBJ_ID_MEASUREMENT_LIST, ATTR_ID_2, data, size);
}

int rmtp_send_measurement_list_data(uint8_t seqNum, uint8_t *data, uint8_t size)
{
	return rmtp_send_data_section_message(RMTP_ITF_CAN0, OBJ_ID_MEASUREMENT_LIST, seqNum, data, size);
}

int rmtp_send_target_list_report(uint8_t *data, uint8_t size)
{
	return rmtp_send_report_message(RMTP_ITF_CAN0, OBJ_ID_TARGET_LIST, ATTR_ID_2, data, size);
}

int rmtp_send_target_list_data(uint8_t seqNum, uint8_t *data, uint8_t size)
{
	return rmtp_send_data_section_message(RMTP_ITF_CAN0, OBJ_ID_TARGET_LIST, seqNum, data, size);
}
#endif

static void rmtp_api_send_target_info(tracking_group_p tkg)
{
	uint8_t pkt[6]= {0};
	uint16_t frame_num = 0;

	frame_num = get_frame_counter();
	memcpy(&pkt[0], &frame_num, sizeof(uint32_t));
	memcpy(&pkt[4], &tkg->tcnt, sizeof(uint16_t));
	if (target_info_report_flag == 1) {
		rmtp_obj_send_report_message(target_info_report_can, OBJ_ID_TARGET_LIST, ATTR_ID_4, pkt, 6);
	}
	return;
}

/******************************************************************************
Function :  initialization
******************************************************************************/
#ifdef USING_CUBTEK_CAN_0
void can0_rmtp_tx_init(void)
{
	int i;

	can0_rmtp_tx->tx_head = 0;
	can0_rmtp_tx->tx_tail = 0;
	can0_rmtp_tx->itf = RMTP_ITF_CAN0;
	for (i = 0; i < SIZE_OF_CAN_RMTP_DATA_TXD; i++) {
		can0_rmtp_tx->can_txque[i].dw = 0;
	}
}
#endif

void can2_rmtp_tx_init(void)
{
	int i;
	
	can2_rmtp_tx->tx_head = 0;
	can2_rmtp_tx->tx_tail = 0;
	can2_rmtp_tx->itf = RMTP_ITF_CAN2;
	for (i = 0; i < SIZE_OF_CAN_RMTP_DATA_TXD; i++)	{
		can2_rmtp_tx->can_txque[i].dw = 0;
	}
}

void rmtp_can_tx_init(RMTP_INTERFACE_E rmtp_itf)
{
	switch (rmtp_itf) {
		case RMTP_ITF_CAN0:
#ifdef USING_CUBTEK_CAN_0
			can0_rmtp_tx_init();
			can0_rmtp_tx->can0_mb = can_tx_burst_data_register("can0_rmtp_tx", (event_proc_p)can0_rmtp_tx_handler);
#endif
			break;
		case RMTP_ITF_CAN2:
			can2_rmtp_tx_init();
			can2_rmtp_tx->can2_mb = can2_tx_burst_data_register("can2_rmtp_tx", (event_proc_p)can2_rmtp_tx_handler, 0);
			break;
		default:
			break;
	}
}


/******************************************************************************
Function : can tx
******************************************************************************/
#ifdef USING_CUBTEK_CAN_0
void can0_tx_rmtp(int ID, uint32_t* p)
{
	put_can_rmtp(ID, p, can0_rmtp_tx);
	if(TRUE == can_rmtp_tx_ready_st(can0_rmtp_tx->itf))
	{
		if (can0_rmtp_tx->tx_head != can0_rmtp_tx->tx_tail)
		{
			can_tx_rmtp_data(can0_rmtp_tx->itf, can0_rmtp_tx);
		}
	}
}
#endif

void can2_tx_rmtp(int ID, uint32_t* p)
{
	put_can_rmtp(ID, p, can2_rmtp_tx);
	if(TRUE == can_rmtp_tx_ready_st(can2_rmtp_tx->itf))
	{
		if (can2_rmtp_tx->tx_head != can2_rmtp_tx->tx_tail)
		{
			can_tx_rmtp_data(can2_rmtp_tx->itf, can2_rmtp_tx);
		}
	}
}

/******************************************************************************
Function : put can tracking
******************************************************************************/
void put_can_rmtp(int ID, uint32_t* p,rmtp_data_handle_p rmtp)
{
	rmtp->txid[rmtp->tx_head] = ID;
	rmtp->can_txque[rmtp->tx_head].w[1] = *(p+1);
	rmtp->can_txque[rmtp->tx_head].w[0] = *p;
	if (rmtp->tx_head == (SIZE_OF_CAN_RMTP_DATA_TXD-1)) {
		rmtp->tx_head = 0;
	} else {
		rmtp->tx_head++;
	}
}

/******************************************************************************
Function Name : can_console_pkg_handler
******************************************************************************/
#ifdef USING_CUBTEK_CAN_0
void can0_rmtp_tx_handler(void)
{
	if (can0_rmtp_tx->tx_head != can0_rmtp_tx->tx_tail)
	{
		can_tx_rmtp_data(can0_rmtp_tx->itf, can0_rmtp_tx);
	}
}
#endif

void can2_rmtp_tx_handler(void)
{
	if (can2_rmtp_tx->tx_head != can2_rmtp_tx->tx_tail)
	{
		can_tx_rmtp_data(can2_rmtp_tx->itf, can2_rmtp_tx);
	}
}

/******************************************************************************
Function : can transmit data
******************************************************************************/
void can_tx_rmtp_data(RMTP_INTERFACE_E itf, rmtp_data_handle_p rmtp)
{
	can_packet_p pkt;
	can_tx_state_e tx_state;
	int tx_id = rmtp->txid[rmtp->tx_tail];
	pkt = &rmtp->can_txque[rmtp->tx_tail];

	switch (itf)	{
#ifdef USING_CUBTEK_CAN_0
		case RMTP_ITF_CAN0:
			tx_state = CanTransmitBurstMessage(rmtp->can0_mb, tx_id, (uint32_t*)pkt);
			break;
#endif
		case RMTP_ITF_CAN2:
			tx_state = Can2TransmitBurstMessage(rmtp->can2_mb, tx_id, (uint32_t*)pkt);
			break;
		default:
#ifdef USING_CUBTEK_CAN_0
			tx_state = CanTransmitBurstMessage(rmtp->can0_mb, tx_id, (uint32_t*)pkt);
#else
			tx_state = Can2TransmitBurstMessage(rmtp->can0_mb, tx_id, (uint32_t*)pkt);
#endif
			break;
	}
	if (CAN_TX_SUCCESS == tx_state)	{

		if(rmtp->tx_tail == (SIZE_OF_CAN_RMTP_DATA_TXD-1))
			rmtp->tx_tail = 0;
		else
			rmtp->tx_tail++;
	}
}

/******************************************************************************
Function : Check CAN Status
******************************************************************************/
uint8_t can_rmtp_tx_ready_st(RMTP_INTERFACE_E itf)
{
    uint8_t can_st = CAN_TX_CODE;
    switch(itf)
    {
        case RMTP_ITF_CAN0:
#ifdef USING_CUBTEK_CAN_0
          	can_st = CAN0_GetMBSt(can0_rmtp_tx->can0_mb);
#endif
            break;
        case RMTP_ITF_CAN2:
                can_st = CAN2_GetMBSt(can2_rmtp_tx->can2_mb);
            break;
        default:

            break;
    }
    if((can_st & CAN_TX_CODE_DATA) == CAN_TX_CODE_INACTIVE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
