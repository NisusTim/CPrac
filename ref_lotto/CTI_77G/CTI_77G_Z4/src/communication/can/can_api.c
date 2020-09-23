/*
 * can_api.c
 *
 *  Created on: 2018/06/15
 *      Author: WoodLiu
 */
#include "sys_shared.h" /* include peripheral declarations */
/*******************************************************************************
* Constants and macros
*******************************************************************************/
#define MAX_IDX_TO_STATISTICS				0x100

typedef struct {
	uint32_t	rx;
	uint32_t	tx;
}can_idx_stat_t,*can_idx_stat_p;


#ifdef USING_CUBTEK_CAN_0

static can_rx_handle_t can_rx_handle = {.msg=can_rx_handle.que,
										.ids={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN0_MB}}}, *can_rx=&can_rx_handle;
static can_tx_handle_t can_tx_handle = {.txidx = TX_MB_START,
										.mbs={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN0_MB}}}, *can_tx=&can_tx_handle;
static can_dlc_tx_handle_t can_dlc_tx_handle = {.txidx = TX_BURST_MB_DLC64_START,
										       	.mbs={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN0_MB,0,FALSE}}}, *can_dlc_tx=&can_dlc_tx_handle;
#endif
static can_rx_handle_t can2_rx_handle = {.msg=can2_rx_handle.que,
										 .ids={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN2_MB}}}, *can2_rx=&can2_rx_handle;
static can_tx_handle_t can2_tx_handle = {.txidx = TX_MB_START,
										 .mbs={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN2_MB}}}, *can2_tx=&can2_tx_handle;
static can_dlc_tx_handle_t can2_dlc_tx_handle = {.txidx = TX2_BURST_MB_DLC64_START,
											     .mbs={{NULL,NULL,0,(uint16_t)CAN_STD_ID_MASK_FULL,INVALID_CAN2_MB,0,FALSE}}}, *can2_dlc_tx=&can2_dlc_tx_handle;

#ifdef USING_CUBTEK_CAN_0
static can_idx_stat_t can_idx_stats[MAX_IDX_TO_STATISTICS] = {{.rx=0,.tx=0}};
static uint8_t can_api_ide0, can_api_br0;
#endif
static uint8_t can_api_ide2, can_api_br2;

#ifdef USING_CUBTEK_CAN_0
/******************************************************************************
 Function Name : CAN_0_Transmit_InterruptHandler
 Date          : Jun-06-2018
 Parameters    : NONE
 Modifies      : NONE
 Returns       : NONE
 Notes         : Interrupt handler for CAN_0 only
 Issues        : NONE
 ******************************************************************************/
void CAN_0_Transmit_InterruptHandler(void)
{
	//MB12 ~ MB15
	vuint32_t flag = CAN_0.IFLAG1.R & CAN0_TX_ISR_MASK;
	vuint32_t imask1_temp = CAN_0.IMASK1.R & CAN0_TX_ISR_MASK;
	can_register_p cp = can_tx->mbs;
	uint8_t findout = FALSE;
	uint8_t i;


	for(i = TX_BURST_MB_START; (i <= TX_BURST_MB_END) && (findout == FALSE) ; i++)
	{
		if((flag>>i) & 0x01 && ((imask1_temp >> i) & 0x01))	//Check which mailboxes triggered interrupt
		{
			while((cp < &can_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED]) && (findout == FALSE)){
				if(cp->mb == i){
					if(cp->clear_isr_flag == 0)
						CAN_0.IFLAG1.R = 0x01 << i;
					if(cp->proc != NULL)
						cp->proc(NULL);					
					findout = TRUE;
				}
				cp++;
			}
		}
	}
}
#endif
/******************************************************************************
Function Name : CAN_2_Transmit_InterruptHandler
Date          : Jun-06-2018
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Interrupt handler for CAN_0 only
Issues        : NONE
******************************************************************************/
void CAN_2_Transmit_InterruptHandler(void)
{
	//MB12 ~ MB15
	vuint32_t flag = CAN_2.IFLAG1.R & CAN2_TX_ISR_MASK;
	vuint32_t imask1_temp = CAN_2.IMASK1.R & CAN2_TX_ISR_MASK;
	can_register_p cp = can2_tx->mbs;
	uint8_t findout = FALSE;
	uint8_t i;


	for(i = TX2_BURST_MB_START; (i <= TX2_BURST_MB_END) && (findout == FALSE) ; i++)
	{
		if(((flag >> i) & 0x01) && ((imask1_temp >> i) & 0x01))	//Check which mailboxes triggered interrupt
		{
			while((cp < &can2_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED]) && (findout == FALSE)){
				if(cp->mb == i){
					if(cp->clear_isr_flag == 0)
						CAN_2.IFLAG1.R = 0x01 << i;
					if(cp->proc != NULL)
						cp->proc(NULL);					
					findout = TRUE;
				}
				cp++;
			}
		}
	}
}

void enable_can2_console_mask(uint8_t select_mb)
{
	if(select_mb >= 0 && select_mb <= 31)
	CAN_2.IMASK1.R |= (0x1 << select_mb);
	else if(select_mb >= RAM_BLOCK1_START_MB && select_mb <= RAM_BLOCK1_START_MB + 31)
		CAN_2.IMASK2.R |= (0x1 << (select_mb - RAM_BLOCK1_START_MB));
	else if(select_mb >= RAM_BLOCK2_START_MB && select_mb <= RAM_BLOCK2_START_MB + 31)
		CAN_2.IMASK3.R |= (0x1 << (select_mb - RAM_BLOCK2_START_MB));
}

void disable_can2_console_mask(uint8_t select_mb)
{
	if(select_mb >= 0 && select_mb <= 31)
	CAN_2.IMASK1.R &= ~(0x1 << select_mb);
	else if(select_mb >= RAM_BLOCK1_START_MB && select_mb <= RAM_BLOCK1_START_MB + 31)
		CAN_2.IMASK2.R &= ~(0x1 << (select_mb - RAM_BLOCK1_START_MB));
	else if(select_mb >= RAM_BLOCK2_START_MB && select_mb <= RAM_BLOCK2_START_MB + 31)
		CAN_2.IMASK3.R &= ~(0x1 << (select_mb - RAM_BLOCK2_START_MB));
}

void clear_can2_console_flags(uint8_t select_mb)
{
	if(select_mb >= 0 && select_mb <= 31)
	CAN_2.IFLAG1.R |= (0x1 << select_mb);
	else if(select_mb >= RAM_BLOCK1_START_MB && select_mb <= RAM_BLOCK1_START_MB + 31)
		CAN_2.IFLAG2.R |= (0x1 << (select_mb - RAM_BLOCK1_START_MB));
	else if(select_mb >= RAM_BLOCK2_START_MB && select_mb <= RAM_BLOCK2_START_MB + 31)
		CAN_2.IFLAG3.R |= (0x1 << (select_mb - RAM_BLOCK2_START_MB));
}

#ifdef USING_CUBTEK_CAN_0
/******************************************************************************
 Function Name : CAN_0_Transmit_InterruptHandler_531
 Date          : Jun-06-2018
 Parameters    : NONE
 Modifies      : NONE
 Returns       : NONE
 Notes         : Interrupt handler for CAN_0 only
 Issues        : NONE
 ******************************************************************************/
void CAN_0_Transmit_InterruptHandler_531(void)      //MB64 ~ MB79
{
	vuint32_t flag = CAN_0.IFLAG3.R & CAN0_TX_DLC_ISR_MASK;
	vuint32_t imask_temp = CAN_0.IMASK3.R & CAN0_TX_DLC_ISR_MASK;
	can_register_p cp = can_dlc_tx->mbs;
	uint8_t findout = FALSE;
	uint8_t i;


	CAN_0.CTRL1.B.ERRMSK = 1;

	for(i=0; (i <MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED) && (findout == FALSE) ; i++)
	{
		if(((flag >> i) & 0x01)  && ((imask_temp >> i) & 0x01))	//Check which mailboxes triggered interrupt
		{
			while((cp < &can_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]) && (findout == FALSE)){
                if(cp->mb ==i+TX_BURST_MB_DLC64_START){
					if(cp->clear_isr_flag == 0)
						CAN_0.IFLAG3.R = 0x01 << i;		
					if(cp->proc != NULL)
						cp->proc((void*)cp->mb);
					findout = TRUE;
				}
				cp++;
			}
		}
	}
}
#endif

#ifdef CTI_Z4_0
/******************************************************************************
Function Name : CAN_2_Transmit_InterruptHandler_557
Date          : Jun-06-2018
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Interrupt handler for CAN_2 only
Issues        : NONE
******************************************************************************/
void CAN_2_Transmit_InterruptHandler_557(void)          //MB64 ~ MB79
{
	vuint32_t flag = CAN_2.IFLAG3.R & CAN2_TX_DLC_ISR_MASK;
	vuint32_t imask_temp = CAN_2.IMASK3.R & CAN2_TX_DLC_ISR_MASK;
	can_register_p cp = can2_dlc_tx->mbs;
	uint8_t findout = FALSE;
	uint8_t i;


	CAN_2.CTRL1.B.ERRMSK = 1;

    for(i=0; (i <MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED) && (findout == FALSE) ; i++)
	{
		if(((flag >> i) & 0x01)  && ((imask_temp >> i) & 0x01))	//Check which mailboxes triggered interrupt
		{
			while((cp < &can2_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]) && (findout == FALSE)){
				if(cp->mb ==i+TX2_BURST_MB_DLC64_START){
					if(cp->clear_isr_flag == 0)
						CAN_2.IFLAG3.R = 0x01 << i;
					if(cp->proc != NULL)					
						cp->proc((void*)&cp->mb);
					findout = TRUE;
				}
				cp++;
			}
		}
	}
}
#endif

#ifdef USING_CUBTEK_CAN_0
/******************************************************************************
Function Name : CAN_0_Receive_InterruptHandler
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Interrupt handler for CAN_0  only
Issues        : NONE
******************************************************************************/
void CAN_0_Receive_InterruptHandler(void)
{
	//MB0 ~ MB11
	uint32_t canid;
	uint8_t dlc;
	can_register_p cp = can_rx->ids;
	vuint32_t flag = CAN_0.IFLAG1.R & CAN0_RX_ISR_MASK;
	uint8_t findout = FALSE;
	uint8_t i;
	vuint32_t temp;      /* temporary and volatile 32bit */

	CAN_0.IFLAG1.R = flag;	/*Clear interrupt flag*/


	for(i = RX_MB_START; (i <= RX_MB_END) && (findout == FALSE) ; i++)
	{
		if((flag>>i) & 0x01)	//Check which mailbox triggered interrupt
		{
			/* mandatory - read control/status word - lock the MB */
			temp = CAN_0.MB[i].CS.R;

			can_rx->msg->pkg.dw = *(uint64_t*)(CAN_0.MB[i].DATA.W);

			if(CAN_0.MB[i].CS.B.IDE == 1)
			{
				canid = CAN_0.MB[i].ID.R;
			}
			else
			{
				canid = CAN_0.MB[i].ID.B.ID_STD;
			}

			dlc = CAN_0.MB[i].CS.B.DLC;

			can_rx->msg->id = canid;
			can_rx->msg->dlc = dlc;

			if (canid < MAX_IDX_TO_STATISTICS)
				can_idx_stats[canid].rx++;

			while((cp < &can_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]) && (findout == FALSE)){
				if(cp->id == 0){
					findout = TRUE;
				}
				if((cp->id & cp->mask) == (canid & cp->mask))
				{
					put_event(cp->name, cp->proc, (void*)can_rx->msg);
					findout = TRUE;
				}
				cp++;
			}

			if (can_rx->msg == &can_rx->que[SIZE_OF_CAN_PACKET_QUE-1])
				can_rx->msg = can_rx->que;
			else
				can_rx->msg++;

			/* release the internal lock for all Rx MBs
			 * by reading the TIMER */
			temp = CAN_0.TIMER.R;
		}
	}
}
#endif

/******************************************************************************
Function Name : CAN_2_Receive_InterruptHandler
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Interrupt handler for CAN_2
  only
Issues        : NONE
******************************************************************************/
void CAN_2_Receive_InterruptHandler(void)
{
	//MB0 ~ MB11

	uint32_t canid;
	uint8_t dlc;
	can_register_p cp = can2_rx->ids;
	vuint32_t flag = CAN_2.IFLAG1.R & CAN2_RX_ISR_MASK;
	uint8_t i;
	uint8_t findout = FALSE;
	vuint32_t temp;      /* temporary and volatile 32bit */

	CAN_2.IFLAG1.R = flag;	/*Clear interrupt flag*/

	for(i = RX2_MB_START ; (i <= RX2_MB_END) && (findout == FALSE) ; i++)
	{
		if((flag>>i) & 0x01)	//Check which mailbox triggered interrupt
		{
			/* mandatory - read control/status word - lock the MB */
			temp = CAN_2.MB[i].CS.R;
			/* check the ID field */
			/* not really needed in this example */
			/* useful in case when multiple IDs are received
			 * by one message buffer (Rx mask feature) */

			can2_rx->msg->pkg.dw = *(uint64_t*)(CAN_2.MB[i].DATA.W);

			if(CAN_2.MB[i].CS.B.IDE == 1)
			{
				canid = CAN_2.MB[i].ID.R;
			}
			else
			{
				canid = CAN_2.MB[i].ID.B.ID_STD;
			}

			dlc = CAN_2.MB[i].CS.B.DLC;

			can2_rx->msg->id = canid;
			can2_rx->msg->dlc = dlc;

			while((cp < &can2_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]) && (findout == FALSE)){
				if(cp->id == 0){
					findout = TRUE;
				}

				if((cp->id & cp->mask) == (canid & cp->mask))
				{
					put_event(cp->name, cp->proc, (void*)can2_rx->msg);
					findout = TRUE;
				}
				cp++;
			}

			if (can2_rx->msg == &can2_rx->que[SIZE_OF_CAN_PACKET_QUE-1])
				can2_rx->msg = can2_rx->que;
			else
				can2_rx->msg++;

			/* release the internal lock for all Rx MBs
			 * by reading the TIMER */
			temp = CAN_2.TIMER.R;
		}
	}
	if(temp)
		temp = 0;
}

#ifdef USING_CUBTEK_CAN_0
/******************************************************************************
Function Name : CanTransmitMessage
Engineer      :
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : modify for use multi MB to send
Issues        : NONE
******************************************************************************/
can_tx_state_e CanTransmitMessage(uint32_t ID, uint32_t* p)
{
	if(CAN_0.MB[can_tx->txidx].CS.B.CODE & 0x04)  //drop for non blocking
	{
		return CAN_TX_FAIL_MB_BUSY;
	}

	if(ID < MAX_IDX_TO_STATISTICS)
		can_idx_stats[ID].tx++;

	CAN_0.MB[can_tx->txidx].CS.B.CODE = 0x8;          //MB TX inactive

	if(can_api_ide0)
	{
		CAN_0.MB[can_tx->txidx].CS.B.IDE = 1;			  //extended bit enabled
		CAN_0.MB[can_tx->txidx].ID.R = ID;	      		//set message EX ID
	}
	else
	{
		CAN_0.MB[can_tx->txidx].CS.B.IDE = 0;	  		//extended bit disable
		CAN_0.MB[can_tx->txidx].ID.B.ID_STD = ID;	      //set message STD ID
	}

	CAN_0.MB[can_tx->txidx].DATA.W[1] = *(p+1);	  	//data1 set
	CAN_0.MB[can_tx->txidx].DATA.W[0] = *p;	  		//data0 set
	CAN_0.MB[can_tx->txidx].CS.B.DLC = 8;			  //message length 8 bytes
	CAN_0.MB[can_tx->txidx].CS.B.RTR = 0;			  //remote frame disable
//	CAN_0.MB[can_tx->txidx].CS.B.SRR = 0;			  //not used with STD_ID
    if(can_api_br0>=CAN_FD_500K_2M)
    {
        CAN_0.MB[can_tx->txidx].CS.B.EDL = 1;
        CAN_0.MB[can_tx->txidx].CS.B.BRS = 1;
        CAN_0.MB[can_tx->txidx].CS.B.ESI = 0;
    }

	CAN_0.MB[can_tx->txidx].CS.B.CODE = 0xC;		  	//MB once transmit data

	can_tx->txidx = can_tx->txidx == (TX_MB_END) ?  TX_MB_START : can_tx->txidx+1;

	return CAN_TX_SUCCESS;
}
#endif

can_tx_state_e Can2TransmitMessage(uint32_t ID, uint32_t* p)
{
	if(CAN_2.MB[can2_tx->txidx].CS.B.CODE & 0x04)  //drop for non blocking
	{
		return CAN_TX_FAIL_MB_BUSY;
	}
	CAN_2.MB[can2_tx->txidx].CS.B.CODE = 0x8;          //MB TX inactive

	if(can_api_ide2)
	{
		CAN_2.MB[can2_tx->txidx].CS.B.IDE = 1;			  //extended bit enabled
		CAN_2.MB[can2_tx->txidx].ID.R = ID;	      		//set message EX ID
	}
	else
	{
		CAN_2.MB[can2_tx->txidx].CS.B.IDE = 0;	  		//extended bit disable
		CAN_2.MB[can2_tx->txidx].ID.B.ID_STD = ID;	      //set message STD ID
	}

	CAN_2.MB[can2_tx->txidx].DATA.W[1] = *(p+1);	  	//data1 set
	CAN_2.MB[can2_tx->txidx].DATA.W[0] = *p;	  		//data0 set
	CAN_2.MB[can2_tx->txidx].CS.B.DLC = 8;			  //message length 8 bytes
	CAN_2.MB[can2_tx->txidx].CS.B.RTR = 0;			  //remote frame disable
	//	CAN_2.MB[can2_tx->txidx].CS.B.SRR = 0;			  //not used with STD_ID
	if(can_api_br2>=CAN_FD_500K_2M)
    {
        CAN_2.MB[can2_tx->txidx].CS.B.EDL = 1;
        CAN_2.MB[can2_tx->txidx].CS.B.BRS = 1;
        CAN_2.MB[can2_tx->txidx].CS.B.ESI = 0;
    }
	CAN_2.MB[can2_tx->txidx].CS.B.CODE = 0xC;		  	//MB once transmit data

	can2_tx->txidx = can2_tx->txidx == (TX2_MB_END-1) ?  TX2_MB_START : can2_tx->txidx+1;

	return CAN_TX_SUCCESS;
}

#ifdef USING_CUBTEK_CAN_0
can_tx_state_e CanTransmitBurstMessage(uint8_t mb, uint32_t ID, uint32_t* p)
{
	//Transmit can data by mailbox
	uint8_t start 	= TX_BURST_MB_START;
	uint8_t end 	= TX_BURST_MB_END;

	if(CAN_0.MB[mb].CS.B.CODE & 0x04)  //drop for non blocking
	{
		return CAN_TX_FAIL_MB_BUSY;
	}

	if(start <= mb && mb <= end)
	{
		CAN_0.MB[mb].CS.B.CODE = 0x8;		//MB TX inactive
		if(can_api_ide0)
		{
			CAN_0.MB[mb].CS.B.IDE = 1;			//extended bit enable
			CAN_0.MB[mb].ID.R = ID;		//set message EX ID
		}
		else
		{
			CAN_0.MB[mb].CS.B.IDE = 0;			//extended bit disable
			CAN_0.MB[mb].ID.B.ID_STD = ID;		//set message STD ID
		}

		CAN_0.MB[mb].DATA.W[1] = *(p+1);	//data1 set
		CAN_0.MB[mb].DATA.W[0] = *p;	  	//data0 set
		CAN_0.MB[mb].CS.B.DLC = 8;			//message length 8 bytes
		CAN_0.MB[mb].CS.B.RTR = 0;			//remote frame disable
        if(can_api_br0>=CAN_FD_500K_2M)
        {
            CAN_0.MB[mb].CS.B.EDL = 1;
            CAN_0.MB[mb].CS.B.BRS = 1;
            CAN_0.MB[mb].CS.B.ESI = 0;
        }
		CAN_0.MB[mb].CS.B.CODE = 0xC;		//MB once transmit data

		return CAN_TX_SUCCESS;
	}
	else
	{
		return CAN_TX_FAIL_OUT_OF_MB_RANGE;
	}
}
#endif

can_tx_state_e Can2TransmitBurstMessage(uint8_t mb, uint32_t ID, uint32_t* p)
{
	//Transmit can data by mailbox
	uint8_t start 	= TX_BURST_MB_START;
	uint8_t end 	= TX_BURST_MB_END;

	if(CAN_2.MB[mb].CS.B.CODE & 0x04)  //drop for non blocking
	{
		return CAN_TX_FAIL_MB_BUSY;
	}

	if(start <= mb && mb <= end)
	{
		CAN_2.MB[mb].CS.B.CODE = 0x8;		//MB TX inactive

		if(can_api_ide2)
		{
			CAN_2.MB[mb].CS.B.IDE = 1;			//extended bit enable
			CAN_2.MB[mb].ID.R = ID;		//set message EX ID
		}
		else
		{
			CAN_2.MB[mb].CS.B.IDE = 0;			//extended bit disable
			CAN_2.MB[mb].ID.B.ID_STD = ID;		//set message STD ID
		}

		CAN_2.MB[mb].DATA.W[1] = *(p+1);	//data1 set
		CAN_2.MB[mb].DATA.W[0] = *p;	  	//data0 set
		CAN_2.MB[mb].CS.B.DLC = 8;			//message length 8 bytes
		CAN_2.MB[mb].CS.B.RTR = 0;			//remote frame disable
		if(can_api_br2>=CAN_FD_500K_2M)
        {
            CAN_2.MB[mb].CS.B.EDL = 1;
            CAN_2.MB[mb].CS.B.BRS = 1;
            CAN_2.MB[mb].CS.B.ESI = 0;
        }
		CAN_2.MB[mb].CS.B.CODE = 0xC;		//MB once transmit data

		return CAN_TX_SUCCESS;
	}
	else
	{
		return CAN_TX_FAIL_OUT_OF_MB_RANGE;
	}
}

#ifdef USING_CUBTEK_CAN_0
uint8_t Can0TransmitMessageDlc(uint8_t mb, uint32_t ID, uint32_t* p, uint16_t remain_size)
{
	uint8_t i;
    uint8_t dlc_temp;
    uint8_t tx_size;
    uint8_t DLC_mb;

    if(mb<TX_BURST_MB_DLC64_START||mb>TX_BURST_MB_DLC64_END){
        return 0;
    }else{
        DLC_mb=mb-RAM_BLOCK2_START_MB;
    }
        
    if(can_api_br0<CAN_FD_500K_2M){
        return 0;
    }

	if(CAN_0_DLC.MB[DLC_mb].CS.B.CODE & 0x04){       //drop for non blocking
		return 0;
	}

	CAN_0_DLC.MB[DLC_mb].CS.B.CODE = 0x8;		    //MB TX inactive

	if(can_api_ide0){
		CAN_0_DLC.MB[DLC_mb].CS.B.IDE = 1;			//extended bit enable
		CAN_0_DLC.MB[DLC_mb].ID.R = ID;		        //set message EX ID
	}else{
		CAN_0_DLC.MB[DLC_mb].CS.B.IDE = 0;			//extended bit disable
		CAN_0_DLC.MB[DLC_mb].ID.B.ID_STD = ID;		//set message STD ID
	}

    if(remain_size>=8){
        dlc_temp=15;
        tx_size=8;
    }else if(remain_size>=6){
        dlc_temp=14;
        tx_size=6;
    }else if(remain_size>=4){
        dlc_temp=13;
        tx_size=4;
    }else if(remain_size>=3){
        dlc_temp=12;
        tx_size=3;
    }else if(remain_size>=2){
        dlc_temp=10;
        tx_size=2;
    }else if(remain_size>=1){
        dlc_temp=8;
        tx_size=1;
    }else{
        dlc_temp=0;
        tx_size=0;
    }

    for(i=0;i<tx_size*2;i++){
        CAN_0_DLC.MB[DLC_mb].DATA.W[i] = *p;
        p++;
    }
    CAN_0_DLC.MB[DLC_mb].CS.B.DLC = dlc_temp;		//message length 8 bytes
	CAN_0_DLC.MB[DLC_mb].CS.B.RTR = 0;			    //remote frame disable
    CAN_0_DLC.MB[DLC_mb].CS.B.EDL = 1;
    CAN_0_DLC.MB[DLC_mb].CS.B.BRS = 1;
    CAN_0_DLC.MB[DLC_mb].CS.B.ESI = 0;
    CAN_0_DLC.MB[DLC_mb].CS.B.CODE = 0xC;		//MB once transmit data

	return tx_size;
}
#endif

uint8_t Can2TransmitMessageDlc(uint8_t mb, uint32_t ID, uint32_t* p, uint16_t remain_size)
{
	uint8_t i;
    uint8_t dlc_temp;
    uint8_t tx_size;
    uint8_t DLC_mb;
    
    if(mb<TX2_BURST_MB_DLC64_START||mb>TX2_BURST_MB_DLC64_END){
        return 0;
    }else{
        DLC_mb=mb-RAM_BLOCK2_START_MB;
    }

    if(can_api_br2<CAN_FD_500K_2M){
        return 0;
    }

	if(CAN_2_DLC.MB[DLC_mb].CS.B.CODE & 0x04){       //drop for non blocking
		return 0;
	}

	CAN_2_DLC.MB[DLC_mb].CS.B.CODE = 0x8;		    //MB TX inactive

	if(can_api_ide2){
		CAN_2_DLC.MB[DLC_mb].CS.B.IDE = 1;			//extended bit enable
		CAN_2_DLC.MB[DLC_mb].ID.R = ID;		        //set message EX ID
	}else{
		CAN_2_DLC.MB[DLC_mb].CS.B.IDE = 0;			//extended bit disable
		CAN_2_DLC.MB[DLC_mb].ID.B.ID_STD = ID;		//set message STD ID
	}

    if(remain_size>=8){
        dlc_temp=15;
        tx_size=8;
    }else if(remain_size>=6){
        dlc_temp=14;
        tx_size=6;
    }else if(remain_size>=4){
        dlc_temp=13;
        tx_size=4;
    }else if(remain_size>=3){
        dlc_temp=12;
        tx_size=3;
    }else if(remain_size>=2){
        dlc_temp=10;
        tx_size=2;
    }else if(remain_size>=1){
        dlc_temp=8;
        tx_size=1;
    }else{
        dlc_temp=0;
        tx_size=0;
    }

    for(i=0;i<tx_size*2;i++){
        CAN_2_DLC.MB[DLC_mb].DATA.W[i] = *p;
        p++;
    }
    CAN_2_DLC.MB[DLC_mb].CS.B.DLC = dlc_temp;		//message length 8 bytes
	CAN_2_DLC.MB[DLC_mb].CS.B.RTR = 0;			    //remote frame disable
    CAN_2_DLC.MB[DLC_mb].CS.B.EDL = 1;
    CAN_2_DLC.MB[DLC_mb].CS.B.BRS = 1;
    CAN_2_DLC.MB[DLC_mb].CS.B.ESI = 0;
    CAN_2_DLC.MB[DLC_mb].CS.B.CODE = 0xC;		//MB once transmit data

	return tx_size;
}

#ifdef USING_CUBTEK_CAN_0
void can_tester(char** args, int count)
{
	if(count > 1){
		can_register_p cp;
		if(!strcmp(args[1],"regs")){
			cp = can_rx->ids;
			while(cp < &can_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]){
				if(cp->id != 0)
					PRINTF("can rx: mb %02d regs %04X %s %p\n",cp->mb, cp->id, cp->name, cp->proc);
				else
					break;
				cp++;
			}

			cp = can_tx->mbs;
			while(cp < &can_tx->mbs[MAX_COUNT_OF_RX_CANID_REGISTERED]){
				if(cp->mb != INVALID_CAN0_MB)
					PRINTF("can tx: mb %02d regs %s %p\n",cp->mb, cp->name, cp->proc);
				else
					break;
				cp++;
			}

			cp = can_dlc_tx->mbs;
			while(cp < &can_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]){
				if(cp->mb != INVALID_CAN0_MB)
					PRINTF("can dlc tx: mb %02d regs %s %p\n",cp->mb, cp->name, cp->proc);
				else
					break;
				cp++;
			}
		}
		else if(!strcmp(args[1], "stat")) {
			uint16_t idx = 0;
			if(count > 2 && !strcmp(args[2],"rst")){
				while(idx < MAX_IDX_TO_STATISTICS){
					can_idx_stats[idx].tx = 0;
					can_idx_stats[idx].rx = 0;
					idx++;
				}
			}
			else {
				PRINTF("can rx: packets statistic devid=%04X\n", product_info_get()->device_id);
				while(idx < MAX_IDX_TO_STATISTICS){
					if(can_idx_stats[idx].rx > 0)
						PRINTF("can rx: stats rx[%xh]=%ld\n",idx, can_idx_stats[idx].rx);

					if(can_idx_stats[idx].tx > 0)
						PRINTF("can tx: stats tx[%xh]=%ld\n",idx, can_idx_stats[idx].tx);
					idx++;
				}
			}
		}
	}
}
#endif

void can2_tester(char** args, int count)
{
	if(count > 1){
		can_register_p cp;
		if(!strcmp(args[1],"regs")){
			cp = can2_rx->ids;
			while(cp < &can2_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]){
				if(cp->id != 0)
					PRINTF("can2 rx: mb %02d regs %08lX %s %p\n",cp->mb, cp->id, cp->name, cp->proc);
				else
					break;
				cp++;
			}

			cp = can2_tx->mbs;
			while(cp < &can2_tx->mbs[MAX_COUNT_OF_RX_CANID_REGISTERED]){
				if(cp->mb != INVALID_CAN2_MB)
					PRINTF("can2 tx: mb %02d regs %s %p\n",cp->mb, cp->name, cp->proc);
				else
					break;
				cp++;
			}

			cp = can2_dlc_tx->mbs;
			while(cp < &can2_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]){
				if(cp->mb != INVALID_CAN2_MB)
					PRINTF("can2 dlc tx: mb %02d regs %s %p\n",cp->mb, cp->name, cp->proc);
				else
					break;
				cp++;
			}
		}
	}
}

#ifdef USING_CUBTEK_CAN_0
uint8_t can_tx_burst_data_register(char* name, event_proc_p proc, uint8_t clear_isr_flag)
{
	can_register_p cp = can_tx->mbs;
	static uint8_t mailbox_id = TX_BURST_MB_START;
	uint8_t rtval = INVALID_CAN0_MB;
	while(cp < &can_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED]){
		if(cp->mb == INVALID_CAN0_MB){
			cp->mb = mailbox_id;
			cp->proc = proc;
			rtval = mailbox_id;
			if(name)
				cp->name = name;
			else
				cp->name = "cantx";
			cp->clear_isr_flag = clear_isr_flag;

			PRINTF("can tx:%s(mb %d)\n",name, mailbox_id);

			mailbox_id++;

			if(cp < &can_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED-1]){
				cp++;
				cp->mb = INVALID_CAN0_MB;
			}

			return rtval;
		}
		cp++;
	}
	PRINTF("can: tx mb register failed, que full already!\n");
	return -1;
}
#endif

uint8_t can2_tx_burst_data_register(char* name, event_proc_p proc, uint8_t clear_isr_flag)
{
	can_register_p cp = can2_tx->mbs;
	static uint8_t mailbox_id = TX2_BURST_MB_START;
	uint8_t rtval = INVALID_CAN2_MB;
	while(cp < &can2_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED]){
		if(cp->mb == INVALID_CAN2_MB){
			cp->mb = mailbox_id;
			cp->proc = proc;
			rtval = mailbox_id;
			if(name)
				cp->name = name;
			else
				cp->name = "cantx";
			cp->clear_isr_flag = clear_isr_flag;

			PRINTF("can2 tx:%s(mb %d)\n",name, mailbox_id);

			mailbox_id++;

			if(cp < &can2_tx->mbs[MAX_COUNT_OF_TX_BURST_CANID_REGISTERED-1]){
				cp++;
				cp->mb = INVALID_CAN2_MB;
			}

			return rtval;
		}
		cp++;
	}
	PRINTF("can2: tx mb register failed, que full already!\n");
	return -1;
}

#ifdef USING_CUBTEK_CAN_0
uint8_t can_tx_burst_data_register_dlc64(char* name, event_proc_p proc, uint8_t clear_isr_flag)
{
	can_register_p cp = can_dlc_tx->mbs;
	static uint8_t mailbox_id = TX_BURST_MB_DLC64_START;
	uint8_t rtval = INVALID_CAN0_MB;
	while(cp < &can_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]){
		if(cp->mb == INVALID_CAN0_MB){
			cp->mb = mailbox_id;
			cp->proc = proc;
			rtval = mailbox_id;
			if(name)
				cp->name = name;
			else
				cp->name = "cantx";
			cp->clear_isr_flag = clear_isr_flag;

			PRINTF("can dlc tx:%s(mb %d)\n",name, mailbox_id);

			mailbox_id++;

			if(cp < &can_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED-1]){
				cp++;
				cp->mb = INVALID_CAN0_MB;
			}

			return rtval;
		}
		cp++;
	}
	PRINTF("can: tx mb register failed, que full already!\n");
	return -1;
}
#endif

uint8_t can2_tx_burst_data_register_dlc64(char* name, event_proc_p proc, uint8_t clear_isr_flag)
{
	can_register_p cp = can2_dlc_tx->mbs;
	static uint8_t mailbox_id = TX2_BURST_MB_DLC64_START;
	uint8_t rtval = INVALID_CAN2_MB;
	while(cp < &can2_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED]){
		if(cp->mb == INVALID_CAN2_MB){
			cp->mb = mailbox_id;
			cp->proc = proc;
			rtval = mailbox_id;
			if(name)
				cp->name = name;
			else
				cp->name = "cantx";
			cp->clear_isr_flag = clear_isr_flag;

			PRINTF("can2 dlc tx:%s(mb %d)\n",name, mailbox_id);

			mailbox_id++;

			if(cp < &can2_dlc_tx->mbs[MAX_COUNT_OF_TX_BURST_DLC64_CANID_REGISTERED-1]){
				cp++;
				cp->mb = INVALID_CAN2_MB;
			}

			return rtval;
		}
		cp++;
	}
	PRINTF("can2: tx mb register failed, que full already!\n");
	return -1;
}

#ifdef USING_CUBTEK_CAN_0
void can_rx_id_register(uint32_t id, uint32_t mask, char* name, event_proc_p proc)
{
	can_register_p cp = can_rx->ids;
	static uint8_t mailbox_id = RX_MB_START;

	while(cp < &can_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]){
		if(cp->id == 0){
			cp->mb = mailbox_id;
			cp->id = id;
			cp->mask = mask;
			cp->proc = proc;

			SettingCAN_0_MailBoxCanId(mailbox_id, id, mask);

			if(name)
				cp->name = name;
			else
				cp->name = "can";
			PRINTF("can rx:%s(%04X)\n",name, id);

			mailbox_id++;

			if(cp < &can_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED-1]){
				cp++;
				cp->id = 0;
			}

			return;
		}
		else if(cp->id == id){
			PRINTF("can rx:%s(%04X) reg already!\n", name, id);
			return;
		}
		cp++;
	}
	PRINTF("can: rx id register failed, que full already!\n");
}

void can_rx_id_register_again_by_name(uint32_t id, uint32_t mask, char* name, event_proc_p proc)
{
	can_register_p cp = can_rx->ids;
	can_register_t temp_cp;
	uint8_t i = 0;

	if(name != NULL)
	{
		while(cp < &can_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED])
		{
				if(cp->name == name)
				{
					temp_cp = can_rx->ids[i];
					if(id != NULL)
					{
						temp_cp.id = id;
					}
					if(mask != NULL)
					{
						temp_cp.mask = mask;
					}
					if(proc != NULL)
					{
						temp_cp.proc = proc;
					}
					SettingCAN_0_MailBoxCanId(temp_cp.mb, id, mask);
					return;
				}
				i++;
		}
	}
	else
	{
		PRINTF("Name is null!\n");
	}
}
#endif

void can2_rx_id_register(uint32_t id, uint32_t mask, char* name, event_proc_p proc)
{
	can_register_p cp = can2_rx->ids;
	static uint8_t mailbox_id = RX2_MB_START;

	while(cp < &can2_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED]){
		if(cp->id == 0){
			cp->mb = mailbox_id;
			cp->id = id;
			cp->mask = mask;
			cp->proc = proc;

			SettingCAN_2_MailBoxCanId(mailbox_id, id, mask);

			if(name)
				cp->name = name;
			else
				cp->name = "can";
			PRINTF("can2 rx:%s(%08lX)\n",name, id);

			mailbox_id++;

			if(cp < &can2_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED-1]){
				cp++;
				cp->id = 0;
			}

			return;
		}
		else if(cp->id == id){
			PRINTF("can2 rx:%s(%08lX) reg already!\n", name, id);
			return;
		}
		cp++;
	}
	PRINTF("can2: rx id register failed, que full already!\n");
}

void can2_rx_id_register_again_by_name(uint32_t id, uint32_t mask, char* name, event_proc_p proc)
{
	can_register_p cp = can2_rx->ids;
	can_register_t temp_cp;
	uint8_t i = 0;
	if(name != NULL)
	{
		while(cp < &can2_rx->ids[MAX_COUNT_OF_RX_CANID_REGISTERED])
		{
			if(cp->name == name)
			{
				temp_cp = can2_rx->ids[i];
				if(id != NULL)
				{
					temp_cp.id = id;
				}
				if(mask != NULL)
				{
					temp_cp.mask = mask;
				}
				if(proc != NULL)
				{
					temp_cp.proc = proc;
				}
				SettingCAN_2_MailBoxCanId(temp_cp.mb, id, mask);
				return;
			}
		}
	}
	else
	{
		PRINTF("Name is null!\n");
	}
}

void can_api_init(void)
{
#ifdef USING_CUBTEK_CAN_0
	can_api_ide0 = get_can0_ide();
	can_api_br0 = get_can0_br();
#endif
	can_api_ide2 = get_can2_ide();
	can_api_br2 = get_can2_br();
}

