#ifndef __ISOTP_H__
#define __ISOTP_H__

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "isotp_defines.h"
#include "isotp_config.h"
#include "isotp_user.h"
#include "can_api.h"
#include "typedefs.h"
#include "customer.h"

#if ISOTP_EN
#define ISOTP_BUFSIZE 2048

typedef struct {
    /* sender paramters */
    uint32_t                    send_arbitration_id; /* used to reply consecutive frame */
    /* message buffer */
    uint8_t                     *send_buffer;
    uint16_t                    send_buf_size;
    uint16_t                    send_size;
    uint16_t                    send_offset;
    /* multi-frame flags */
    uint8_t                     send_sn;
    uint16_t                    send_bs_remain; /* Remain block size */
    uint8_t                     send_st_min;    /* Separation Time between consecutive frames, unit msec */
    uint8_t                     send_wtf_count; /* Maximum number of FC.Wait frame transmissions  */
    uint32_t                    send_timer_st;  /* Last time send consecutive frame */
    uint32_t                    send_timer_bs;  /* Time until reception of the next FlowControl N_PDU
                                                   start at sending FF, CF, receive FC
                                                   end at receive FC */
    int                         send_protocol_resault;
    uint8_t                     send_status;

    /* receiver paramters */
    uint32_t                    receive_arbitration_id;
    /* message buffer */
    uint8_t                     *receive_buffer;
    uint16_t                    recevie_buf_size;
    uint16_t                    receive_size;
    uint16_t                    receive_offset;
    /* multi-frame control */
    uint8_t                     receive_sn;
    uint8_t                     receive_bs_count; /* Maximum number of FC.Wait frame transmissions  */
    uint32_t                    receive_timer_cr; /* Time until transmission of the next ConsecutiveFrame N_PDU
                                                     start at sending FC, receive CF
                                                     end at receive FC */
    int                         receive_protocol_resault;
    uint8_t                     receive_status;
}IsoTpLink;

typedef void (*recv_event_p)(IsoTpLink*);

typedef union{
	vuint8_t BYTE;
	struct {     /* Error and Status 1 register */
    vuint8_t CAN0_APP_TX_ENABLE:1;          /*Can0_App_Tx*/
    vuint8_t CAN0_RMTP_TX_ENABLE:1;         /*Can0_Rmtp_Tx*/
    vuint8_t CAN2_APP_TX_ENABLE:1;          /*Can2_App_Tx*/
    vuint8_t CAN2_RMTP_TX_ENABLE:1;         /*Can2_Rmtp_Tx*/
    vuint8_t :0;
	}BIT;
} CAN_STATUS_TAG;

typedef enum{
	CAN_BURST_TX_CH_APP = 0,
	CAN_BURST_TX_CH_RMTP,
	CAN_BURST_TX_CH_COUNT,
	CAN_BURST_TX_CH_UNKNOWN
} CAN_TX_CHANNEL_E;

typedef enum {
	CAN_BURST_TX_ITF_CAN0 = 0,
	CAN_BURST_TX_ITF_CAN2,
	CAN_BURST_TX_ITF_COUNT,
	CAN_BURST_TX_ITF_UNKNOWN
} CAN_TX_INTERFACE_E;

#define SIZE_OF_TX_DATA_TXD				2048
#define SIZE_OF_CAN_TX_DATA_TXD			(SIZE_OF_TX_DATA_TXD/8)

struct can_burst_tx_handle
{
	/*General Console Format*/
	char name[20];
	CAN_TX_CHANNEL_E ch;
	CAN_TX_INTERFACE_E itf;
	uint8_t can_mb;				//Console can mailbox (if need)
	uint16_t tx_head, tx_tail;

	/* Transmission Buffer */
	uint16_t txid[SIZE_OF_CAN_TX_DATA_TXD];		//Console tx id (if need)
	can_packet_t can_txque[SIZE_OF_CAN_TX_DATA_TXD];		//can tx queue
};

typedef struct can_burst_tx_handle can_burst_tx_handle_t;
typedef struct can_burst_tx_handle *can_burst_tx_handle_p;

#define CAN_TX_CODE                     0x07
#define CAN_TX_CODE_INACTIVE            0x00
#define CAN_TX_CODE_DATA                0x04

extern void isotp_init_link(void);
extern void isotp_rx_id_register(uint32_t id, uint32_t mask, char* name, recv_event_p event);
extern void isotp_just_send(uint32_t id, const uint8_t payload[], uint16_t size);
extern void isotp_custom_send(uint32_t id, const uint8_t *header, uint16_t header_size, const uint8_t *data, uint16_t data_size);
extern IsoTpLink* get_isotp_link(void);

#endif

#ifdef __cplusplus
}
#endif

#endif // __ISOTP_H__

