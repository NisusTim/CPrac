/*
 * can_tracking.h
 *
 *  Created on: 2018�~6��19��
 *      Author: user
 */

#ifndef CAN_CUSTOMIZE_CAN_TRACKING_H_
#define CAN_CUSTOMIZE_CAN_TRACKING_H_

#include "sys_shared.h"

#define SIZE_OF_TRACKING_DATA_TXD				4096
#define SIZE_OF_CAN_TRACKING_DATA_TXD			(SIZE_OF_TRACKING_DATA_TXD/8)

#define TARGET_LIST_OFF					0
#define TARGET_LIST_ON					1

typedef enum {
	TRACKING_ITF_UART = 0,
	TRACKING_ITF_ENET,
	TRACKING_ITF_CAN0,
	TRACKING_ITF_CAN2,
	TRACKING_ITF_UNKNOWN,
}TRACKING_INTERFACE_E;

typedef struct {
	/*General Console Format*/
	TRACKING_INTERFACE_E itf;								//Console interface
	uint8_t				can_mb;								//Console can mailbox (if need)
	uint16_t 			tx_head, tx_tail;

	/* Transmission Buffer */
	uint32_t			txid[SIZE_OF_CAN_TRACKING_DATA_TXD];	//Console tx id (if need)
	can_packet_t	can_txque[SIZE_OF_CAN_TRACKING_DATA_TXD];	//can tx queue

} tracking_data_handle_t, *tracking_data_handle_p;

void can_tx_tracking_init(TRACKING_INTERFACE_E itf);
void can_tx_tracking_state_init(void);
void can_tracking_tx(int ID, uint32_t* p);
uint8_t can_tracking_tx_ready_st(TRACKING_INTERFACE_E itf);
uint8_t get_tx_target_list_flag();
void set_tx_target_list_flag(uint8_t op);

#endif /* CAN_CUSTOMIZE_CAN_TRACKING_H_ */
