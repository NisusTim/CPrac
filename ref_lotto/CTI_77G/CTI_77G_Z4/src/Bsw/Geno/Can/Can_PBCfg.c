/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_PBcfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Can module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Can module configuration File
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
#include "Can.h"

/*******************************************************************************
*   Config Parameters  
*******************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h" 

CONST(uint8, CAN_CONFIG_CONST) CanControllerIDtoPhys[CAN_USED_CONTROLLER_NUM]=
{
    #if (CAN_USED_CONTROLLER_NUM >= 1)
    0,
    #endif 
};

CONST(Can_RegInitType, CAN_CONFIG_CONST) CanRegInit[CAN_USED_CONTROLLER_NUM] =
{
    #if (CAN_USED_CONTROLLER_NUM >= 1)
    {
        ((uint8)0x00U),
        ((uint8)0x82U|CAN0_BCC_CFG),
        ((uint8)0x00U),
        ((uint8)0x5FU),
        ((uint8)0x3U),
        ((uint8)0x33U),
        (CAN0_BUSOFF_INT_CFG|CAN0_CLKSRC_CFG), 
        ((uint8)0x7U|CAN0_BUSOFF_RECCFG),
        0x1fffffffUL,
        0x1fffffffUL,
        0x1fffffffUL,
        0xffffffffUL,
        0xffffffffUL,
		0xffffffffUL
    },
    #endif 
};

VAR(Can_HardwareObjectConfigType, CAN_PRIVATE_DATA) 
                                      CanHardwareObjectConfig[CAN_USED_HOH_NUM] = 
{
    {
        /* CanObjectId0*/
        0,
        0x7a0, /*Diagnostic physical addressing receive ID*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId1*/
        0,
        0x7b0, /*Diagnostic physical addressing receive ID*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },	
    {
        /* CanObjectId2*/
        0,
        0x7df,/*Diagnostic functional addressing receive ID*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId3*/
        0,
        0x300, /*Vehicle physical value*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId4*/
        0,
		0x301,/*Vehicle status value*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId5*/
        0,
        0x70,/*RMTP receive ID*/
        CAN_HOH_RX_MASK|CAN_HOH_FULL_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId6*/
        0,
		0x1CECFFE0,/*J1939 TP.BAM message ID*/
		CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId7*/
        0,
		0x7a8,/*Diagnostic response ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId8*/
        0,
		0x501,/*Radar_Sta ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId9*/
        0,
		0x1CEBFFE0,/*TP_DT ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId10*/
        0,
		0x18FECAE0,/*DM1 ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId11*/
        0,
		0x71,/*RMTP transimit ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    },
    {
        /* CanObjectId12*/
        0,
		0x500,/*Target list ID*/
        CAN_HOH_TX_MASK,
        0x1fffffff,
    }
};

CONST(uint8, CAN_CONFIG_CONST) 
                                 CanIntConfig[CAN_USED_CONTROLLER_NUM] = 
{
    (CAN0_BUSOFF_INT_CFG|CAN0_RX_INT_CFG|CAN0_TX_INT_CFG), 
};

CONST(Can_HwHandleType, CAN_CONFIG_CONST) 
                                 CanRxMBStartNum[CAN_USED_CONTROLLER_NUM] = 
{
    0,
};

CONST(Can_HwHandleType, CAN_CONFIG_CONST) 
                                 CanRxMBSum[CAN_USED_CONTROLLER_NUM] = 
{
    6,
};

CONST(Can_HwHandleType, CAN_CONFIG_CONST) 
                                 CanTxMBStartNum[CAN_USED_CONTROLLER_NUM] = 
{
    6,
};

CONST(Can_HwHandleType, CAN_CONFIG_CONST) 
                                 CanTxMBSum[CAN_USED_CONTROLLER_NUM] = 
{
    90,
};

CONST(Can_HwHandleType, CAN_CONFIG_CONST) 
                                 CanHohStartNum[2*CAN_USED_CONTROLLER_NUM] = 
{
    0,
    6,
};
#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED 
#include "MemMap.h"
