/*
 * can_tracking.c
 *
 *  Created on: 2018�~6��19��
 *      Author: user
 */

#include "can_tracking.h"
static tracking_data_handle_t tracking_data = {0};
static tracking_data_handle_p tracking=&tracking_data;

typedef can_tx_state_e (*can_send_proc_p)(int mb, int ID, uint32_t* p);
static can_send_proc_p can_send_tracking_data_p = NULL;
static uint8_t on_off_rmtp_tx_target_list;
void enqueue_tracking_data(int ID, uint32_t* p);
void can_tracking_tx_handler(void);
void can_tx_tracking_data();

/******************************************************************************
Function :  initialization
******************************************************************************/

void can_tx_tracking_init(TRACKING_INTERFACE_E itf)
{
	int i;
//	tracking->need_trigger_tx = TRUE;
	tracking->tx_head = 0;
	tracking->tx_tail = 0;
	tracking->itf = itf;
	for(i = 0 ; i < SIZE_OF_CAN_TRACKING_DATA_TXD ; i++)
	{
		tracking->can_txque[i].dw = 0;
	}

	if(TRACKING_ITF_CAN0 == itf)
	{
#ifdef USING_CUBTEK_CAN_0
		can_send_tracking_data_p = (can_send_proc_p)CanTransmitBurstMessage;
		tracking->can_mb = can_tx_burst_data_register("tracking", (event_proc_p)can_tracking_tx_handler);
#endif
	}
	else if(TRACKING_ITF_CAN2 == itf)
	{
		can_send_tracking_data_p = (can_send_proc_p)Can2TransmitBurstMessage;
		tracking->can_mb = can2_tx_burst_data_register("tracking", (event_proc_p)can_tracking_tx_handler, 0);
	}
	else
	{
#ifdef USING_CUBTEK_CAN_0
		can_send_tracking_data_p = (can_send_proc_p)CanTransmitBurstMessage;
		tracking->can_mb = can_tx_burst_data_register("tracking", (event_proc_p)can_tracking_tx_handler);
#else
		can_send_tracking_data_p = (can_send_proc_p)Can2TransmitBurstMessage;
		tracking->can_mb = can2_tx_burst_data_register("tracking", (event_proc_p)can_tracking_tx_handler, 0);
#endif
	}
}

/******************************************************************************
Function :  initialization
******************************************************************************/

void can_tx_tracking_state_init(void)
{
	int i;
//	tracking->need_trigger_tx = TRUE;
	tracking->tx_head = 0;
	tracking->tx_tail = 0;
	for(i = 0 ; i < SIZE_OF_CAN_TRACKING_DATA_TXD ; i++)
	{
		tracking->can_txque[i].dw = 0;
	}
}

/******************************************************************************
Function : can tx
******************************************************************************/
void can_tracking_tx(int ID, uint32_t* p)
{
	enqueue_tracking_data(ID,p);

	if(TRUE == can_tracking_tx_ready_st(tracking->itf))
	{
		if(tracking->tx_head != tracking->tx_tail)
		{
			can_tx_tracking_data();
		}
	}

	while(((tracking->tx_head - tracking->tx_tail) & (SIZE_OF_CAN_TRACKING_DATA_TXD-1)) >= (SIZE_OF_CAN_TRACKING_DATA_TXD-2));
}

/******************************************************************************
Function : put can tracking
******************************************************************************/
void enqueue_tracking_data(int ID, uint32_t* p)
{
	tracking->txid[tracking->tx_head] = ID;
	tracking->can_txque[tracking->tx_head].w[1] = *(p+1);
	tracking->can_txque[tracking->tx_head].w[0] = *p;

	if (tracking->tx_head == (SIZE_OF_CAN_TRACKING_DATA_TXD-1))
		tracking->tx_head = 0;
	else
		tracking->tx_head++;
}
/******************************************************************************
Function Name : can_console_pkg_handler
******************************************************************************/
void can_tracking_tx_handler(void)
{
	if(tracking->tx_head != tracking->tx_tail)
	{
		can_tx_tracking_data();
	}
}

/******************************************************************************
Function : can transmit data
******************************************************************************/
void can_tx_tracking_data()
{
	can_packet_p pkt;
	can_tx_state_e tx_state;
	int mb = tracking->can_mb;
	int tx_id = tracking->txid[tracking->tx_tail];
	pkt = &tracking->can_txque[tracking->tx_tail];

	tx_state = can_send_tracking_data_p(mb, tx_id, (uint32_t*)pkt);

	if(CAN_TX_SUCCESS == tx_state)
	{
		if(tracking->tx_tail == (SIZE_OF_CAN_TRACKING_DATA_TXD-1))
			tracking->tx_tail = 0;
		else
			tracking->tx_tail++;
	}
}

/******************************************************************************
Function : Check CAN Status
******************************************************************************/
uint8_t can_tracking_tx_ready_st(TRACKING_INTERFACE_E itf)
{
    uint8_t can_st = FALSE;
	
    switch(itf)
    {
        case TRACKING_ITF_CAN0:
                can_st = CAN0_GetMBSt(tracking->can_mb);
            break;
        case TRACKING_ITF_CAN2:
                can_st = CAN2_GetMBSt(tracking->can_mb);
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

    return FALSE;
}

uint8_t get_tx_target_list_flag()
{
	return on_off_rmtp_tx_target_list;
}

void set_tx_target_list_flag(uint8_t op)
{
	on_off_rmtp_tx_target_list = op;
}
