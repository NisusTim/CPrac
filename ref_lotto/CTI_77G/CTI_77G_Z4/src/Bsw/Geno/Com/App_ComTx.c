/*
 * App_ComTx.c
 *
 *  Created on: 2020/03/18
 *      Author: Cubtek
 */

#include "Com_Cfg.h"
#include "App_ComTx_Types.h"
#include "App_ComTx.h"
#include "can_cubtek.h"

STATIC VAR(App_ComTx_RmtpDataType, COM_PRIVATE_DATA) RmtpDataBuffer = {0};
STATIC P2VAR(App_ComTx_RmtpDataType, AUTOMATIC, COM_PRIVATE_DATA) RmtpDataBufferPtr = &RmtpDataBuffer;
STATIC VAR(App_ComTx_IpduDataType, COM_PRIVATE_DATA) IpduDataBuffer = {0};
STATIC P2VAR(App_ComTx_IpduDataType, AUTOMATIC, COM_PRIVATE_DATA) IpduDataBufferPtr = &IpduDataBuffer;

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Init
(
	void
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Enqueue
(
	uint64 Data
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Write
(
	void
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Init
(
	void
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Enqueue
(
	uint32 Id,
	uint64 Data
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Write
(
	void
);

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Init
(
	void
)
{
	int i;
		 
	RmtpDataBufferPtr->tx_head = 0;
	RmtpDataBufferPtr->tx_tail = 0;
	for(i = 0; i < APP_COMTX_RMTP_DATA_QUEUE_SIZE; i++)
	{
		RmtpDataBufferPtr->can_txque[i].dw = 0;
	}
}

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Enqueue
(
	uint64 data
)
{
	RmtpDataBufferPtr->can_txque[RmtpDataBufferPtr->tx_head].dw = data;	 
	if (RmtpDataBufferPtr->tx_head == (APP_COMTX_RMTP_DATA_QUEUE_SIZE-1))
		RmtpDataBufferPtr->tx_head = 0;
	else
		RmtpDataBufferPtr->tx_head++;
}
	 
STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_RmtpData_Write(void)
{
	can_packet_p pkt;
	PduInfoType temp;
	Std_ReturnType ret = E_NOT_OK;

	if(E_OK == CanIf_Transmit_Ready_Test(RMTP_DATA_TXPDUID))
	{
		if(RmtpDataBufferPtr->tx_head != RmtpDataBufferPtr->tx_tail)
		{	 
			pkt = &RmtpDataBufferPtr->can_txque[RmtpDataBufferPtr->tx_tail];		 
			temp.SduLength = 8;
			temp.SduDataPtr = (uint8 *)&pkt->dw;
			ret = CanIf_Transmit(RMTP_DATA_TXPDUID, &temp);
			if(ret == E_OK)
			{
				if(RmtpDataBufferPtr->tx_tail == (APP_COMTX_RMTP_DATA_QUEUE_SIZE-1))
					RmtpDataBufferPtr->tx_tail = 0;
				else
					RmtpDataBufferPtr->tx_tail++;
			}
		}	
	}	
}

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Init
(
	void
)
{
	int i;
	 
	IpduDataBufferPtr->tx_head = 0;
	IpduDataBufferPtr->tx_tail = 0;
	for(i = 0 ; i < APP_COMTX_IPDU_DATA_QUEUE_SIZE; i++)
	{
		IpduDataBufferPtr->can_txque[i].dw = 0;
	}
}

STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Enqueue
(
	uint32 Id, 
	uint64 Data
)
{
	IpduDataBufferPtr->txid[IpduDataBufferPtr->tx_head] = Id;
	IpduDataBufferPtr->can_txque[IpduDataBufferPtr->tx_head].dw = Data;
	if (IpduDataBufferPtr->tx_head == (APP_COMTX_IPDU_DATA_QUEUE_SIZE-1))
		IpduDataBufferPtr->tx_head = 0;
	else
		IpduDataBufferPtr->tx_head++;
}
	 
STATIC FUNC(void, COM_PRIVATE_CODE) App_ComTx_IpduData_Write
(
	void
)
{
	uint32_t id;
	can_packet_p pkt;
	PduInfoType temp;
	Std_ReturnType ret = E_NOT_OK;

	if(IpduDataBufferPtr->tx_head != IpduDataBufferPtr->tx_tail)
	{
		id = IpduDataBufferPtr->txid[IpduDataBufferPtr->tx_tail];
		pkt = &IpduDataBufferPtr->can_txque[IpduDataBufferPtr->tx_tail];		 
		temp.SduLength = 8;
		temp.SduDataPtr = (uint8 *)&pkt->dw;
		CanIf_SetDynamicTxId(IPDU_DATA_TXPDUID, id);
		ret = CanIf_Transmit(IPDU_DATA_TXPDUID, &temp);
		if(ret == E_OK)
		{
			if(IpduDataBufferPtr->tx_tail == (APP_COMTX_IPDU_DATA_QUEUE_SIZE-1))
				IpduDataBufferPtr->tx_tail = 0;
			else
				IpduDataBufferPtr->tx_tail++;
		}
	}
}

FUNC(void, COM_PUBLIC_CODE) App_ComTx_Init
(
	void
)
{
	App_ComTx_RmtpData_Init();
	App_ComTx_IpduData_Init();
}

FUNC(Std_ReturnType, COM_PRIVATE_CODE) App_ComTx_RmtpData_Transmit
(
	uint64 Data
)
{
	App_ComTx_RmtpData_Enqueue(Data);
	if(E_OK == CanIf_Transmit_Ready_Test(RMTP_DATA_TXPDUID))
	{
		App_ComTx_RmtpData_Write();
	}

	return E_OK;
}

FUNC(Std_ReturnType, COM_PRIVATE_CODE) App_ComTx_IpduData_Transmit
(
	uint32 Id,
	uint64 Data
)
{
	if(CAN_EnRx_EnTx == cubtek_faw_did_ds_can_status_get())
	{
		App_ComTx_IpduData_Enqueue(Id, Data);
		if(E_OK == CanIf_Transmit_Ready_Test(IPDU_DATA_TXPDUID))
		{
			App_ComTx_IpduData_Write();
		}
		return E_OK;
	}
	 
	return E_NOT_OK;
}

FUNC(void, COM_PUBLIC_CODE) App_ComTx_Confirmation
(
	PduIdType PduId
)
{
	if(RMTP_DATA_TXPDUID == PduId)
	{
		App_ComTx_RmtpData_Write();
	}
	else if(IPDU_DATA_TXPDUID == PduId)
	{
		if(CAN_EnRx_EnTx == cubtek_faw_did_ds_can_status_get())
		{
			App_ComTx_IpduData_Write();
		}
	}
}

