/*
 * App_ComTx_Types.h
 *
 *  Created on: 2020/03/18
 *      Author: Cubtek
 */

#ifndef _APP_COMTX_TYPES_H_
#define _APP_COMTX_TYPES_H_

#include "sys_shared.h"
#include "Com_Types.h"

#define APP_COMTX_RMTP_DATA_QUEUE_SIZE		150
#define APP_COMTX_IPDU_DATA_QUEUE_SIZE		250

typedef struct {
	/* Transmission Buffer */
	uint16 			tx_head, tx_tail;
	can_packet_t	can_txque[APP_COMTX_RMTP_DATA_QUEUE_SIZE]; // tx queue
} App_ComTx_RmtpDataType;

typedef struct {
	/* Transmission Buffer */
	uint16 			tx_head, tx_tail;
	uint32			txid[APP_COMTX_IPDU_DATA_QUEUE_SIZE];		 // tx id
	can_packet_t	can_txque[APP_COMTX_IPDU_DATA_QUEUE_SIZE]; // tx queue
} App_ComTx_IpduDataType;

#endif /* _APP_COMTX_TYPES_H_ */
