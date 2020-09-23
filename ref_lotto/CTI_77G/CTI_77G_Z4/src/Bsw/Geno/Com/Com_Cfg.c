/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Cfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Com module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Com module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.02    12/11/2018     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com.h"

#if(COM_TXIPDUNUM >= 1u)

/*******************************************************************************
*   Tx Msg Buffer 
*******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 
VAR(IpduRadar_Sta_bufType, COM_PRIVATE_DATA) TxIpduRadar_Sta;
#define COM_STOP_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

/*******************************************************************************
*   for Tx Message and Signals 
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

CONST(IpduRadar_Sta_bufType, COM_CONFIG_CONST) TxIpduRadar_StaDefaultValue =
{
	{
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	}
};

CONST(PduInfoType, COM_CONFIG_CONST) Com_TxIpduInitTable[COM_TXIPDUNUM] = 
{
	{TxIpduRadar_Sta._c, 8U},
	{TxIpduRadar_Sta._c, 8U} //Only for initialization.
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduSigNum[COM_TXIPDUNUM] = 
{
	26U,
	0U
};

CONST(Com_TxSigTableType, COM_CONFIG_CONST) Com_TxSigTable[COM_TXSIGNUM] = 
{
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0},
	{1U, COM_NOSENDTYPE, (Com_SigInActiveType*)0}
};

CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST ) Com_TxIpduDefaultValue[COM_TXIPDUNUM] = 
{
	TxIpduRadar_StaDefaultValue._c,
	TxIpduRadar_StaDefaultValue._c//Only for initialization.
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduTable[COM_TXIPDUNUM] = 
{
	(COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
	COM_NOSENDTYPE
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduCycleTable[COM_TXIPDUNUM] = 
{
	50U,
	0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduFastCycleTable[COM_TXIPDUNUM] =
{
    0U,
	0U
};

CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_TxSigOffsetTable[COM_TXIPDUNUM] = 
{
    0U,
	0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTdelayTable[COM_TXIPDUNUM] = 
{
	0U,
	0U
};

CONST(uint8, COM_CONFIG_CONST) Com_TxIpduRepNumTable[COM_TXIPDUNUM] = 
{
	0U,
	0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTimeOutTable[COM_TXIPDUNUM] = 
{
    0U,
	0U
};

CONST(uint16, COM_CONFIG_CONST) Com_TxIpduOffsetTable[COM_TXIPDUNUM] = 
{
    0U,
	0U
};

#ifdef COM_ENABLE_TXTOINDFUN
CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_TxIpduTOIndicationTable[COM_TXIPDUNUM] = 
{
    &AppIpduHeader_TxTOIndication,
	&AppIpduRadar_Sta_TxTOIndication
};
#endif

#ifdef COM_ENABLE_TXCONFIRMATIONFUN
CONST(Com_TxConfirmationType, COM_CONFIG_CONST) Com_TxIpduConfirmTable[COM_TXIPDUNUM] = 
{
    &AppIpduHeader_Conf,
	&AppIpduRadar_Sta_Conf
};
#endif

CONST(PduIdType, COM_CONFIG_CONST) Com_TxIpduIdMapTable[COM_TXIPDUNUM]=
{
	RADAR_STA_TXPDUID,
	IPDU_DATA_TXPDUID
};
 
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
 
#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM >= 1u)

/*******************************************************************************
*   Rx Msg Buffer
*******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 
VAR(IpduVehInfo1_bufType, COM_PRIVATE_DATA) RxIpduVehInfo1;
VAR(IpduVehInfo2_bufType, COM_PRIVATE_DATA) RxIpduVehInfo2;
#define COM_STOP_SEC_VAR_UNSPECIFIED 
#include "MemMap.h" 

/*******************************************************************************
*   for Rx Message and Signals 
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"

CONST(IpduVehInfo1_bufType, COM_CONFIG_CONST) RxIpduVehInfo1_DefaultValue =
{
//    {
//        0,0,0,0,0,0,0,0,0
//    }
        .Raw = 0            //Modified by Wood, in order to fix near initialization warning
};

CONST(IpduVehInfo2_bufType, COM_CONFIG_CONST) RxIpduVehInfo2_DefaultValue =
{
//    {
//        0,0,0,0,0,0,0,0,0,0
//    }
        .Raw = 0            //Modified by Wood, in order to fix near initialization warning
};

CONST(PduInfoType, COM_CONFIG_CONST) Com_RxIpduInitTable[COM_RXIPDUNUM] = 
{
	{RxIpduVehInfo1._c, 8U},
	{RxIpduVehInfo2._c, 8U}
};

CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST ) Com_RxIpduDefaultValue[COM_RXIPDUNUM] = 
{
   RxIpduVehInfo1_DefaultValue._c,
   RxIpduVehInfo2_DefaultValue._c
};

CONST(PduLengthType, COM_CONFIG_CONST) Com_RxIpduBufferSize[COM_RXIPDUNUM]=
{
    COM_RXIPDUVehInfo1_BUFFER_SIZE,
	COM_RXIPDUVehInfo2_BUFFER_SIZE
};

CONST(uint8, COM_CONFIG_CONST) Com_RxIpduSigNum[COM_RXIPDUNUM] = 
{
    4U,
	2U
};

CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_RxSigOffsetTable[COM_RXIPDUNUM] = 
{
	4U,
	2U
};

CONST(Com_RxSigTableType, COM_CONFIG_CONST) Com_RxSigTable[COM_RXSIGNUM] = 
{

};

CONST(Com_RxIpduTableType, COM_CONFIG_CONST) Com_RxIpduTable[COM_RXIPDUNUM] = 
{
    {COM_RXTIMEOUTMONITOR_YES, 10U},
	{COM_RXTIMEOUTMONITOR_YES, 100U}
};

#ifdef COM_ENABLE_RXINDICATIONFUN
CONST(Com_RxIndicationType, COM_CONFIG_CONST) Com_RxIpduIndicationTable[COM_RXIPDUNUM] = 
{
    &AppIpduVehInfo1_Ind,
	&AppIpduVehInfo2_Ind
};
#endif

#ifdef COM_ENABLE_RXTOINDFUN
CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_RxIpduTOIndicationTable[COM_RXIPDUNUM] = 
{
    &AppRxIpduVehInfo1_TimeOutInd,
	&AppRxIpduVehInfo2_TimeOutInd
};
#endif
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif /*#if(COM_RXIPDUNUM>=1)*/

#ifdef COM_ENABLE_ROUTESIGNAL

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))
CONST(Com_SignalGatewayTableType, COM_CONFIG_CONST) Com_SignalGatewayTable[COM_GWSIGNUM]=
{
};

CONST(Com_SignalGatewayIpduTableType, COM_CONFIG_CONST) Com_SignalGatewayIpduTable[COM_GWIPDUNUM]=
{
};
#endif/*#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))*/

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif/*#ifdef COM_ENABLE_ROUTESIGNAL*/

#if(COM_GROUPIPDUNUM >= 1)
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

CONST(Com_GroupIpduTableType, COM_CONFIG_CONST) Com_GroupIpduTable[COM_GROUPIPDUNUM]=
{
    {0U, COM_DIRECTION_TX},
    {0U, COM_DIRECTION_RX},
    {1U, COM_DIRECTION_RX},
    {2U, COM_DIRECTION_RX},
    {3U, COM_DIRECTION_RX},
    {4U, COM_DIRECTION_RX},
    {5U, COM_DIRECTION_RX},
    {6U, COM_DIRECTION_RX},
    {7U, COM_DIRECTION_RX},
};

CONST(Com_IpduGroupTableType, COM_CONFIG_CONST) Com_IpduGroupTable[COM_IPDUGROUPNUM]=
{
    {0, 1},
    {1, 8},
};

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#endif
