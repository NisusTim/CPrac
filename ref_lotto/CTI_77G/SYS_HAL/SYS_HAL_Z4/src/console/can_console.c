/*
 * can_console.c
 *
 *  Created on: 2018/05/08
 *      Author: WoodLiu
 */

#include "sys_shared.h" /* include peripheral declarations */

static console_data_handle_p console=&console_data;

#ifdef USING_CUBTEK_CAN_0
static uint8_t can0_dlc_register;
#endif
static uint8_t can2_dlc_register;

static void send_can_console_dlc(void);
static void can_force_put_ch(char ch);
static void can_force_tx_data(CONSOLE_INTERFACE_E itf);

#if defined(CTI_Z4_0)
/******************************************************************************
Function : console initialization
******************************************************************************/

void can_console_init(void)
{
	HW_VER_E hw_ver;
	hw_ver = get_hw_ver();

	if(HW_DUAL_BOARD == hw_ver)
	{
#ifdef USING_CUBTEK_CAN_0
		can_rx_id_register(console->rxid, CAN_STD_ID_MASK_FULL, "cnsl", (event_proc_p)can_console_rx_handler);
		if(0==get_can0_dlc_status()){
			console->can0_mb = can_tx_burst_data_register("cnsl", (event_proc_p)can_console_tx_handler);
			can0_dlc_register=0;
		}else{
			console->can0_mb = can_tx_burst_data_register_dlc64("cnsl", (event_proc_p)can_console_tx_handler);
			can0_dlc_register=1;
		}
#endif
	}
	else
	{
#ifdef USING_CUBTEK_CAN_0
        can_rx_id_register(console->rxid, CAN_STD_ID_MASK_FULL, "cnsl", (event_proc_p)can_console_rx_handler);
        if(0==get_can0_dlc_status()){
            console->can0_mb = can_tx_burst_data_register("cnsl", (event_proc_p)can_console_tx_handler);
            can0_dlc_register=0;
        }else{
            console->can0_mb = can_tx_burst_data_register_dlc64("cnsl", (event_proc_p)can_console_tx_handler);
            can0_dlc_register=1;
        }
#endif
        can2_rx_id_register(console->rxid, CAN_STD_ID_MASK_FULL, "cnsl", (event_proc_p)can2_console_rx_handler);
        if(0==get_can2_dlc_status()){
            console->can2_mb = can2_tx_burst_data_register("cnsl", (event_proc_p)can_console_tx_handler, 1);
            can2_dlc_register=0;
        }else{
            console->can2_mb = can2_tx_burst_data_register_dlc64("cnsl", (event_proc_p)can_console_tx_handler, 1);
            can2_dlc_register=1;
        }

	}
}

/******************************************************************************
Function Name : can_console_pkg_handler
******************************************************************************/
void can_console_tx_handler(uint8_t* data)
{
	if(console->tx_head != console->tx_tail)
	{
		switch(console->itf)
		{
#ifdef USING_CUBTEK_CAN_0
		case CNSL_ITF_CAN0:
//			clear_can0_console_flags(console->can2_mb);
			break;
#endif
		case CNSL_ITF_CAN2:
			clear_can2_console_flags(console->can2_mb);
			break;
		default:
			break;
		}
		can_tx_data(console->itf);
	}
	else
	{
		switch(console->itf)
		{
#ifdef USING_CUBTEK_CAN_0
		case CNSL_ITF_CAN0:
//			disable_can0_console_mask(console->can2_mb);
			break;
#endif
		case CNSL_ITF_CAN2:
			disable_can2_console_mask(console->can2_mb);
			break;
		default:
			break;
		}
	}
}

/******************************************************************************
Function Name : can_console_pkg_handler
******************************************************************************/
void can_console_rx_handler(can_message_p msg)
{
	char ch;
	uint8_t data[8] = {0};
	int i = 0;

	memcpy(data, msg->pkg.b, 8);

	do
	{
		ch = data[i];
		if(ch == CH_LF || ch == CH_CR){
			console->rxque[console->rx_head] = '\0';
			console->rx_head = 0;
			console_proc(NULL);
			console_itf_check_change(CNSL_ITF_CAN0);

		}
		else if (ch < 0x20){
			console_err((uint32_t)ch);
		}
		else {
			console->rxque[console->rx_head++] = ch;
			if(console->rx_head == (SIZE_OF_CAN_CONSOLE_DATA_RXD-1)){
				console->rxque[console->rx_head] = '\0';
				console->rx_head = 0;
				console_proc((void*)console->rxque);
			}
		}
		i++;

	}while(ch != CH_LF && ch != CH_CR && i < 8);
}

/******************************************************************************
Function Name : can_console_pkg_handler
******************************************************************************/
void can2_console_rx_handler(can_message_p msg)
{
	char ch;
	uint8_t data[8] = {0};
	int i = 0;

	memcpy(data, msg->pkg.b, 8);

	do
	{
		ch = data[i];
		if(ch == CH_LF || ch == CH_CR){
			console->rxque[console->rx_head] = '\0';
			console->rx_head = 0;
			console_proc(NULL);
			console_itf_check_change(CNSL_ITF_CAN2);

		}
		else if (ch < 0x20){
			console_err((uint32_t)ch);
		}
		else {
			console->rxque[console->rx_head++] = ch;
			if(console->rx_head == (SIZE_OF_CAN_CONSOLE_DATA_RXD-1)){
				console->rxque[console->rx_head] = '\0';
				console->rx_head = 0;
				console_proc((void*)console->rxque);
			}
		}
		i++;

	}while(ch != CH_LF && ch != CH_CR && i < 8);
}
#endif

/******************************************************************************
Function : put string
******************************************************************************/
void can_put_string(char *str)
{
	while(*str)
		can_put_ch(*str++);

	#ifdef CTI_Z4_0
    if(TRUE == can_console_tx_ready_st(console->itf))
	{
		if(console->tx_head != console->tx_tail)
		{
			can_tx_data(console->itf);
		}
	}
	#endif
}

/******************************************************************************
Function : can put char
******************************************************************************/
void can_put_ch(char ch)
{
	console->can_txque[console->tx_head].b[console->each_data_position]	= ch;

	console->each_data_position++;

	if(console->each_data_position == 8 || ch == '\n')
	{
		if (console->tx_head == (SIZE_OF_CAN_CONSOLE_DATA_TXD-1))
			console->tx_head = 0;
		else
		{
			console->tx_head++;
		}
		switch(console->itf)
		{
		#ifdef USING_CUBTEK_CAN_0
			case CNSL_ITF_CAN0:
			    //enable_can0_console_mask(console->can2_mb);
				break;
			#endif
			case CNSL_ITF_CAN2:
				enable_can2_console_mask(console->can2_mb);
				break;
			default:
				break;
		}

		console->each_data_position = 0;
		console->can_txque[console->tx_head].dw = 0;
	}

#ifdef CTI_Z4_0
	if(TRUE == can_console_tx_ready_st(console->itf))
	{
		if(console->tx_head != console->tx_tail)
		{
			can_tx_data(console->itf);
		}
	}
#endif
//	while(((console->tx_head - console->tx_tail) & (SIZE_OF_CAN_CONSOLE_DATA_TXD-1)) >= (SIZE_OF_CAN_CONSOLE_DATA_TXD-2));
}

/******************************************************************************
Function : can transmit data
******************************************************************************/
void can_tx_data(CONSOLE_INTERFACE_E itf)
{
	can_packet_p pkt;
	can_tx_state_e tx_state;

	pkt = &console->can_txque[console->tx_tail];

	switch(itf)
	{
#ifdef USING_CUBTEK_CAN_0
		case CNSL_ITF_CAN0:
			if(can0_dlc_register==0){
				tx_state = CanTransmitBurstMessage(console->can0_mb, console->txid, (uint32_t*)pkt);
			}else{
				send_can_console_dlc();
				return;
			}
			break;
#endif
		case CNSL_ITF_CAN2:
			if(can2_dlc_register==0){
				tx_state = Can2TransmitBurstMessage(console->can2_mb, console->txid, (uint32_t*)pkt);
			}else{
				send_can_console_dlc();
				return;
			}
			break;
		default:
#ifdef USING_CUBTEK_CAN_0
			if(can0_dlc_register==0){
				tx_state = CanTransmitBurstMessage(console->can0_mb, console->txid, (uint32_t*)pkt);
			}else{
				send_can_console_dlc();
				return;
			}
#else
			if(can2_dlc_register==0){
				tx_state = Can2TransmitBurstMessage(console->can2_mb, console->txid, (uint32_t*)pkt);
			}else{
				send_can_console_dlc();
				return;
			}
#endif
			break;
	}

	if(CAN_TX_SUCCESS == tx_state)
	{
		if(console->tx_tail == (SIZE_OF_CAN_CONSOLE_DATA_TXD-1))
			console->tx_tail = 0;
		else
			console->tx_tail++;
	}
}

/******************************************************************************
Function : Check CAN Status
******************************************************************************/
uint8_t can_console_tx_ready_st(CONSOLE_INTERFACE_E itf)
{
    uint8_t can_st = FALSE;
    switch(itf)
    {
        case CNSL_ITF_CAN0:
                can_st = CAN0_GetMBSt(console->can0_mb);
            break;
        case CNSL_ITF_CAN2:
                can_st = CAN2_GetMBSt(console->can2_mb);
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



/****************************************************************************
Function : force print
*****************************************************************************/
void can_console_force(char *str)
{
	console->tx_head = console->tx_tail; //Discard buffer data
	while(*str)
		can_force_put_ch(*str++);

    can_console_flush();
}

/******************************************************************************
Function : can put char
******************************************************************************/
static void can_force_put_ch(char ch)
{
	static uint8_t can_data_position = 0;

	console->can_txque[console->force_tx_head].b[can_data_position]	= ch;

	can_data_position++;

	if(can_data_position == 8 || ch == '\n')
	{
		if (console->force_tx_head == (SIZE_OF_CAN_CONSOLE_DATA_TXD-1))
			console->force_tx_head = 0;
		else
			console->force_tx_head++;

		can_data_position = 0;
		console->can_txque[console->force_tx_head].dw = 0;
	}

}

/******************************************************************************
Function : can transmit data
******************************************************************************/
void can_force_tx_data(CONSOLE_INTERFACE_E itf)
{
	can_packet_p pkt;
	can_tx_state_e tx_state;
	uint8_t tx_size;
	uint16_t remain_size;

	pkt = &console->can_txque[console->force_tx_tail];

	switch(itf)
	{
#ifdef USING_CUBTEK_CAN_0
		case CNSL_ITF_CAN0:
			clear_can0_console_flags(console->can0_mb);
			if(can0_dlc_register==0){
				tx_state = CanTransmitBurstMessage(console->can0_mb, console->txid, (uint32_t*)pkt);
			}else{
				if(console->force_tx_head >= console->tx_tail){
					remain_size= console->force_tx_head - console->force_tx_tail;
				}else{
					remain_size= SIZE_OF_CAN_CONSOLE_DATA_TXD- console->force_tx_tail;
				}
				tx_size=Can0TransmitMessageDlc(console->can0_mb, console->txid, (uint32_t*)pkt,remain_size );
				console->force_tx_tail+=tx_size;
				if(console->force_tx_tail==SIZE_OF_CAN_CONSOLE_DATA_TXD){
					console->force_tx_tail = 0;
				}
				return;
			}
			break;
#endif
		case CNSL_ITF_CAN2:
			clear_can2_console_flags(console->can2_mb);
			if(can2_dlc_register==0){
				tx_state = Can2TransmitBurstMessage(console->can2_mb, console->txid, (uint32_t*)pkt);
			}else{
				if(console->force_tx_head >= console->force_tx_tail){
					remain_size= console->force_tx_head - console->force_tx_tail;
				}else{
					remain_size= SIZE_OF_CAN_CONSOLE_DATA_TXD- console->force_tx_tail;
				}
				tx_size=Can2TransmitMessageDlc(console->can2_mb, console->txid, (uint32_t*)pkt,remain_size );
				console->force_tx_tail+=tx_size;
				if(console->force_tx_tail==SIZE_OF_CAN_CONSOLE_DATA_TXD){
					console->force_tx_tail = 0;
				}
				return;
			}
			break;
		default:
#ifdef USING_CUBTEK_CAN_0
			clear_can0_console_flags(console->can0_mb);
			if(can0_dlc_register==0){
				tx_state = CanTransmitBurstMessage(console->can0_mb, console->txid, (uint32_t*)pkt);
			}else{
				if(console->force_tx_head >= console->force_tx_tail){
					remain_size= console->force_tx_head - console->force_tx_tail;
				}else{
					remain_size= SIZE_OF_CAN_CONSOLE_DATA_TXD- console->force_tx_tail;
				}
				tx_size=Can0TransmitMessageDlc(console->can0_mb, console->txid, (uint32_t*)pkt,remain_size );
				console->force_tx_tail+=tx_size;
				if(console->force_tx_tail==SIZE_OF_CAN_CONSOLE_DATA_TXD){
					console->force_tx_tail = 0;
				}
				return;
			}
#else
			clear_can2_console_flags(console->can2_mb);
			if(can2_dlc_register==0){
				tx_state = Can2TransmitBurstMessage(console->can2_mb, console->txid, (uint32_t*)pkt);
			}else{
				if(console->force_tx_head >= console->force_tx_tail){
					remain_size= console->force_tx_head - console->force_tx_tail;
				}else{
					remain_size= SIZE_OF_CAN_CONSOLE_DATA_TXD- console->force_tx_tail;
				}
				tx_size=Can2TransmitMessageDlc(console->can2_mb, console->txid, (uint32_t*)pkt,remain_size );
				console->force_tx_tail+=tx_size;
				if(console->force_tx_tail==SIZE_OF_CAN_CONSOLE_DATA_TXD){
					console->force_tx_tail = 0;
				}
				return;
			}
#endif
			break;
	}

	if(CAN_TX_SUCCESS == tx_state)
	{
		if(console->force_tx_tail == (SIZE_OF_CAN_CONSOLE_DATA_TXD-1))
			console->force_tx_tail = 0;
		else
			console->force_tx_tail++;
	}
}

static void send_can_console_dlc(void)
{
	uint16_t item_num;
	uint16_t curr_head = console->tx_head, curr_tail = console->tx_tail;
	CONSOLE_INTERFACE_E temp_itf = console->itf;

	if(curr_head >= curr_tail)
	{
		item_num = curr_head - curr_tail;
	}
	else
	{
		item_num = SIZE_OF_CAN_CONSOLE_DATA_TXD - curr_tail + curr_head;
	}

	can_packet_t tmp_pkt[8];
	uint16_t tmp_id = console->txid;
	uint16_t pkt_cnt;
	uint16_t idx = curr_tail;

	for(pkt_cnt = 0; (pkt_cnt < item_num) && (pkt_cnt < 8); pkt_cnt ++)
	{
		idx = (curr_tail + pkt_cnt) % SIZE_OF_CAN_CONSOLE_DATA_TXD;

		tmp_pkt[pkt_cnt].dw = console->can_txque[idx].dw;
	}

	uint8_t mb;
	uint8_t send_size;
	
	switch(temp_itf)
	{
	#ifdef USING_CUBTEK_CAN_0
	case CNSL_ITF_CAN0:
		mb = console->can0_mb;
		send_size = Can0TransmitMessageDlc(mb, tmp_id, (uint32_t*)tmp_pkt, pkt_cnt );
		break;
	#endif
	case CNSL_ITF_CAN2:
		mb = console->can2_mb;
		send_size = Can2TransmitMessageDlc(mb, tmp_id, (uint32_t*)tmp_pkt, pkt_cnt );
		break;
	default:
		break;
	}
	console->tx_tail = (curr_tail + send_size) % SIZE_OF_CAN_CONSOLE_DATA_TXD;
}

void can_console_flush(void)
{
    uint8_t flag;
    if(console->force_tx_head == console->force_tx_tail){
		flag=0;
	}else if(console->force_tx_head > console->force_tx_tail){
	    flag=1;
	}else{
	    flag=2;
	}
    
    while (1){
        if(TRUE == can_console_tx_ready_st(console->itf))
	    {
		    switch(flag){
		        case 0:
		            if(console->tx_head != console->tx_tail){
		                can_tx_data(console->itf);
		            }else{
		                return;
		            }
		            break;
		            
		         case 1:
		            if(console->force_tx_head > console->force_tx_tail){
		                can_force_tx_data(console->itf);
		            }else{
		                return;
		            }
		            break;
		         
		         case 2:
		            if(console->force_tx_head < console->force_tx_tail){
		                can_force_tx_data(console->itf);
		            }else{
		                return;
		            }
		            break;     
		    }
	        #ifdef ENABLE_SWT
		    clear_SWT0_counter();
            #endif
		    #if defined(CTI_Z4_0)
		    fs8x_wd_handle(fs8xNormal);
		    #endif
	    }
	}
}

