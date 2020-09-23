/*
 * rmtp_api.h
 *
 *  Created on: 2017/09/22
 *      Author: Benson
 */

#ifndef _RMTP_API_H_
#define _RMTP_API_H_

#include "can_api.h"

//#define RMTP_PKT 		1
//#define RMTP_LOG 		1
//#define RMTP_DBG 		1

#ifdef RMTP_PKT
	#define PKT(...) 	PRINTF(__VA_ARGS__)
#else
	#define PKT(...)
#endif

#ifdef RMTP_LOG
	#define LOG(...) 	PRINTF(__VA_ARGS__)
#else
	#define LOG(...)
#endif

#ifdef RMTP_DBG
	#define DBG(...) 	PRINTF(__VA_ARGS__)
#else
	#define DBG(...)
#endif

#define RMTP_NOISE_BASE 0

typedef unsigned int 	UINT;

#define SIZE_OF_RMTP_DATA_TXD				4096
#define SIZE_OF_CAN_RMTP_DATA_TXD			(SIZE_OF_RMTP_DATA_TXD/8)

typedef enum {
	RMTP_ITF_UART = 0,
	RMTP_ITF_ENET,
	RMTP_ITF_CAN0,
	RMTP_ITF_CAN2,
	RMTP_ITF_UNKNOWN,
} RMTP_INTERFACE_E;

typedef struct {
	/*General CAN Format*/
	RMTP_INTERFACE_E 	itf;									//interface
	uint8_t				can0_mb;								//can0 mailbox (if need)
	uint8_t				can2_mb;								//can2 mailbox (if need)
	uint16_t 			tx_head, tx_tail;

	/* Transmission Buffer */
	uint16_t			txid[SIZE_OF_CAN_RMTP_DATA_TXD];		//Console tx id (if need)
	can_packet_t		can_txque[SIZE_OF_CAN_RMTP_DATA_TXD];	//can tx queue
} rmtp_data_handle_t, *rmtp_data_handle_p;

void rmtp_api_init(uint8_t devId, int can0TxId, int can2TxId, int can2BypassId);
uint8_t* rmtp_get_data();
void rmtp_set_ciphertext(uint8_t *cipher);
uint8_t* rmtp_get_ciphertext(void);
int rmtp_api_get_target_info_report_setting(uint8_t *active, uint8_t *canPort);
int rmtp_api_set_target_info_report_setting(uint8_t active, uint8_t canPort);

// CAN HAL
void rmtp_send_message(uint8_t netId);
void rmtp_bypass_message(uint8_t netId, uint8_t *data);

// APIs for managed objects
int rmtp_send_request_message(uint8_t netId, uint8_t subType, uint8_t devId, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size);
int rmtp_send_ok_response_message(uint8_t netId, uint8_t subType, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size);
int rmtp_send_err_response_message(uint8_t netId, uint8_t subType, uint8_t objId, uint8_t attrId, uint8_t resCode, uint8_t *data, uint8_t size);
int rmtp_send_report_message(uint8_t netId, uint8_t objId, uint8_t attrId, uint8_t *data, uint8_t size);
int rmtp_send_alarm_message(uint8_t netId, uint8_t objId, uint8_t evtId, uint8_t *data, uint8_t size);
int rmtp_send_data_section_message(uint8_t netId, uint8_t objId, uint8_t seqNum, uint8_t *data, uint8_t size);

// APIs for other software modules
int rmtp_send_rf_ic_status_message(uint8_t *data, uint8_t size);
int rmtp_send_fccu_status_message(uint8_t *data, uint8_t size);
int rmtp_send_stack_dump_message(uint8_t *data, uint8_t size);
//int rmtp_send_measurement_list_report(uint8_t *data, uint8_t size);
//int rmtp_send_measurement_list_data(uint8_t seqNum, uint8_t *data, uint8_t size);
//int rmtp_send_target_list_report(uint8_t *data, uint8_t size);
//int rmtp_send_target_list_data(uint8_t seqNum, uint8_t *data, uint8_t size);

//API RMTP CAN TX
void can0_rmtp_tx_init(void);
void can2_rmtp_tx_init(void);
void rmtp_can_tx_init(RMTP_INTERFACE_E rmtp_itf);
void can0_tx_rmtp(int ID, uint32_t* p);
void can2_tx_rmtp(int ID, uint32_t* p);
void put_can_rmtp(int ID, uint32_t* p,rmtp_data_handle_p rmtp);
void can0_rmtp_tx_handler(void);
void can2_rmtp_tx_handler(void);
void can_tx_rmtp_data(RMTP_INTERFACE_E itf,rmtp_data_handle_p rmtp);
uint8_t can_rmtp_tx_ready_st(RMTP_INTERFACE_E itf);

#endif /* _RMTP_API_H_ */
