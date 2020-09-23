/*

 * isotp_user.c
 *
 *  Created on: 2019/6/5
 *      Author: MSN
 */
#ifndef CTI_UPD
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "isotp_defines.h"
#include "isotp.h"
#include "console_api.h"
#include "console.h"
#include "can_hal.h"
#include "customer.h"

#if ISOTP_EN
extern volatile can_burst_tx_handle_p g_can_handle_p;

static void Can2_Burst_Transmit_64_Trigger(can_burst_tx_handle_p client_handle_p, int ID, uint32_t* data);
static void enqueue_burst_tx_data(can_burst_tx_handle_p cbth_p, int ID, uint32_t* data);
static uint8_t can_burst_tx_ready_st(can_burst_tx_handle_p cbth_p);
static void can2_burst_tx_data_64_trigger(can_burst_tx_handle_p cbth_p);
static void can_burst_tx_data(can_burst_tx_handle_p cbth_p);

/* required, this must send a single CAN message with the given arbitration
 * ID (i.e. the CAN message ID) and data. The size will never be more than 8
 * bytes. */
int isotp_user_send_can(const uint32_t arbitration_id, const uint8_t* data, const uint8_t size)
{
	int ret;

	Can2_Burst_Transmit_64_Trigger(g_can_handle_p, arbitration_id, (uint32_t *)data);

	ret = ISOTP_RET_OK;

	return ret;
}

/* required, return system tick, unit is millisecond */
uint32_t isotp_user_get_ms(void)
{

	uint32_t i = 0;

	return i;
}

/* optional, provide to receive debugging log messages */
void isotp_user_debug(const char* message, ...)
{
	char __line[160];

	va_list vl;
	va_start(vl, message);

	vsnprintf(__line, sizeof(__line)-1, message, vl);
	va_end(vl);

	PRINTF(__line);
	PRINTF("\r\n");
}

/******************************************************************************
 Function : Can2_Burst_Transmit_64_Trigger
 ******************************************************************************/
static void Can2_Burst_Transmit_64_Trigger(can_burst_tx_handle_p client_handle_p, int ID, uint32_t* data)
{
	if(g_can_handle_p == NULL)
	{
		return;
	}

	if(CAN_BURST_TX_ITF_CAN2 == g_can_handle_p->itf)
	{
		if(CAN_BURST_TX_CH_APP == g_can_handle_p->ch)
		{
			return;
		}

		enqueue_burst_tx_data(g_can_handle_p, ID, data);

		if(true == can_burst_tx_ready_st(g_can_handle_p))
		{
			if(g_can_handle_p->tx_head != g_can_handle_p->tx_tail)
			{
				if(1 == get_can2_dlc_status())
				{
					can2_burst_tx_data_64_trigger(g_can_handle_p);
				}
				else
				{
					can_burst_tx_data(g_can_handle_p);
				}
			}
		}
		while( ( ( g_can_handle_p->tx_head - g_can_handle_p->tx_tail ) & ( SIZE_OF_CAN_TX_DATA_TXD - 1 ) ) >= ( SIZE_OF_CAN_TX_DATA_TXD - 9 ) );
	}
}

/******************************************************************************
 Function : put can tracking
 ******************************************************************************/
static void enqueue_burst_tx_data(can_burst_tx_handle_p cbth_p, int ID, uint32_t* data)
{
	g_can_handle_p->txid[g_can_handle_p->tx_head] = ID;
	g_can_handle_p->can_txque[g_can_handle_p->tx_head].w[1] = *(data + 1);
	g_can_handle_p->can_txque[g_can_handle_p->tx_head].w[0] = *data;

	g_can_handle_p->tx_head = (g_can_handle_p->tx_head + 1) % SIZE_OF_CAN_TX_DATA_TXD;
}

/******************************************************************************
 Function : Check CAN Status
 ******************************************************************************/
static uint8_t can_burst_tx_ready_st(can_burst_tx_handle_p cbth_p)
{
	uint8_t can_st = CAN_TX_CODE;

	switch(g_can_handle_p->itf)
	{
		case CAN_BURST_TX_ITF_CAN0:
			can_st = CAN0_GetMBSt(g_can_handle_p->can_mb);
			break;
		case CAN_BURST_TX_ITF_CAN2:
			can_st = CAN2_GetMBSt(g_can_handle_p->can_mb);
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

/******************************************************************************
 Function : can2_burst_tx_data_64_trigger
 ******************************************************************************/
static void can2_burst_tx_data_64_trigger(can_burst_tx_handle_p cbth_p)
{
	uint8_t (*transmit)(uint8_t mb, uint32_t ID, uint32_t* p, uint16_t length) = NULL;

	if( g_can_handle_p->itf == CAN_BURST_TX_ITF_CAN0 )
	{
		return;
	}
	else if(g_can_handle_p->itf == CAN_BURST_TX_ITF_CAN2)
	{
		switch( g_can_handle_p->ch )
		{
//			case CAN_BURST_TX_CH_APP:
//				transmit = Can0TransmitMessageDlc;
//				break;
			case CAN_BURST_TX_CH_RMTP:
				transmit = Can2TransmitMessageDlc;
				break;
			default:
				break;
		}
	}

	if(transmit == NULL)
	{
		return;
	}

	uint16_t item_num;

	if(g_can_handle_p->tx_head >= g_can_handle_p->tx_tail)
	{
		item_num = g_can_handle_p->tx_head - g_can_handle_p->tx_tail;
	}
	else
	{
		item_num = SIZE_OF_CAN_TX_DATA_TXD - g_can_handle_p->tx_tail + g_can_handle_p->tx_head;
	}

	can_packet_t tmp_pkt[8];
	uint16_t tmp_id = g_can_handle_p->txid[g_can_handle_p->tx_tail];
	uint16_t pkt_cnt;
	uint16_t idx = g_can_handle_p->tx_tail;

	for(pkt_cnt = 0; (pkt_cnt < item_num) && (pkt_cnt < 8) && (tmp_id == g_can_handle_p->txid[idx]); pkt_cnt ++)
	{
		idx = (g_can_handle_p->tx_tail + pkt_cnt) % SIZE_OF_CAN_TX_DATA_TXD;

		tmp_pkt[pkt_cnt].dw = g_can_handle_p->can_txque[idx].dw;
	}

	uint8_t mb = g_can_handle_p->can_mb;
	uint8_t send_size = transmit(mb, tmp_id, (uint32_t*)tmp_pkt, pkt_cnt);

	g_can_handle_p->tx_tail = (g_can_handle_p->tx_tail + send_size) % SIZE_OF_CAN_TX_DATA_TXD;
}

/******************************************************************************
 Function : can transmit data
 ******************************************************************************/
static void can_burst_tx_data(can_burst_tx_handle_p cbth_p)
{
	can_packet_p pkt;
	can_tx_state_e tx_state = CAN_TX_INVALID;

	int mb = g_can_handle_p->can_mb;
	int tx_id = g_can_handle_p->txid[g_can_handle_p->tx_tail];
	pkt = &g_can_handle_p->can_txque[g_can_handle_p->tx_tail];

	tx_state = Can2TransmitBurstMessage(mb, tx_id, (uint32_t*) pkt);

	if( CAN_TX_SUCCESS == tx_state )
	{
		g_can_handle_p->tx_tail = (g_can_handle_p->tx_tail + 1) % SIZE_OF_CAN_TX_DATA_TXD;
	}
}

void can2_burst_tx_handler(uint8_t mb)
{
	if(g_can_handle_p->tx_head != g_can_handle_p->tx_tail)
	{
		if(0 == get_can2_dlc_status())
		{
			can_burst_tx_data(g_can_handle_p);
		}
		else
		{
			can2_burst_tx_data_64_trigger(g_can_handle_p);
		}
	}
}
#endif
#endif
