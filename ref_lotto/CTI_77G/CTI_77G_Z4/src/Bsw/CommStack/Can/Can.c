/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information
*   contained in this doc should not be reproduced, or used, or disclosed
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can.c
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module Source File
*   Author          : HeYang
********************************************************************************
*   Description     : Implementation of CAN Driver
*
********************************************************************************
*   Limitations     : only used for MPC5xxx FlexCAN moudle
*
********************************************************************************
*
********************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    06/05/2012    HeYang        N/A          Original
*   01.01.00    12/05/2012    NingChen      N/A          first test feed back ;
*   01.02.00    08/07/2013    NingChen      N/A          DPN_CAN_130708_01
*   01.02.01    17/07/2013    NingChen      N/A          DPN_CAN_130717_01
*   01.02.02    15/08/2013    NingChen      N/A          D10_CAN_130815_01
*   01.02.03    12/10/2013    RongJiLuo     N/A          D10_CAN_131012_01
*   01.02.04    25/10/2013    ning.chen     N/A          D10_CAN_131025_01
*   01.03.00    08/01/2014    NingChen      N/A          D10_CAN_140108_01
*   01.03.01    15/09/2015    NingChen      N/A          D10_CAN_150915_01
*   01.03.02    17/11/2015    NingChen      N/A          D10_CAN_151117_01
*   01.03.03    13/12/2016    NingChen      N/A          D10_CAN_161213_01
*   01.03.04    3/2/2018      JunFeiChen     N/A         D10_CAN_180302_01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Can.h"
#include "CanIf_Cbk.h"
#include "S32R274.h" /* include peripheral declarations */
#include "can_hal.h"
#include "compiler_api.h"
#include "Dem_Types.h"
#include "Dem_Lcfg.h"
#include "can_hal.h"

/*CAN390: The Can module shall include the header file EcuM_Cbk.h, in which the
callback functions called by the Can module at the Ecu State Manager module are
declared.*/

/*CAN397: The Can module shall include the header file Os.h file. By this
inclusion,the API to read a free running timer value (GetCounterValue) provided
by the system service shall be included.*/
#if (STD_ON==CAN_DEV_ERROR_DETECT)
    #include "Det.h"
#endif

/*******************************************************************************
*   Macro
*******************************************************************************/

/*******************************************************************************
* PRQA S 3453  MISRA-C:2004 Rule 19.7
* These function-like macros are defined to access can config parameters,which
* can improve the readability of the code.
* This part of code is verified manually and has no impact.
*******************************************************************************/
#define CAN_RX_MB_START(controller)   (CanRxMBStartNum[controller])
#define CAN_RX_MB_SUM(controller)     (CanRxMBSum[controller])
#define CAN_TX_MB_START(controller)   (CanTxMBStartNum[controller])
#define CAN_HOH_ID_REF                (CanHardwareObjectConfig[HohIndex].id)
#define CAN_TX_MB_SUM(controller)     (CanTxMBSum[controller])
#define CAN_HOH_TYPE                 (CanHardwareObjectConfig[HohIndex].hohType)
#define CAN_HOH_FILTERMASK_REF   \
        (CanHardwareObjectConfig[HohIndex].filterRef)

/*******************************************************************************
* PRQA S 3435
* PRQA S 3436
* These function-like macros are defined to access can config parameters,which
* can improve the readability of the code.
* This part of code is verified manually and has no impact.
*******************************************************************************/
#define CAN_RX_MB_END(controller) \
        (CanRxMBStartNum[controller] + CanRxMBSum[controller])
#define CAN_TX_MB_END(controller) \
        (CanTxMBStartNum[controller] + CanTxMBSum[controller])
#define CAN_HOH_CONTROLLER_REF    \
        (CanHardwareObjectConfig[HohIndex].controllerRef)

#if (1 == CAN_USED_CONTROLLER_NUM)
    #define CAN_CONTROLLER_ID           (0)
#else
    #define CAN_CONTROLLER_ID           (Controller)
#endif

/*******************************************************************************
*   Local Data Declaration
*******************************************************************************/
#define CAN_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/* For CAN_DEV_ERROR_DETECT */
#if (CAN_DEV_ERROR_DETECT == STD_ON )
STATIC VAR(Can_StateType, CAN_PRIVATE_DATA)  Can_State[CAN_USED_CONTROLLER_NUM];
STATIC VAR(Can_InitType, CAN_PRIVATE_DATA) Can_DriverInitStatus =
                                                              CAN_UNINITIALIZED;
#endif

/*CAN418: Constants, global data types and functions that are only used by the
Can module internally, are declared in Can.c */
/*******************************************************************************
* PRQA S 3207  "MSRCopyValue is not used "
* This warning can be ignored  because  MSRCopyValue is guaranteed used in this
* file. However it's used in assembler code, which makes the QAC report 3207 by
* mistake.
* This part of code is verified manually and has no impact.
*******************************************************************************/
//STATIC VAR(uint32, CAN_PRIVATE_DATA) MSRCopyValue ;   //Remove by Wood, in order to resolve unused warning
STATIC VAR(uint8, CAN_PRIVATE_DATA) CanGlobalInterruptCount;
STATIC VAR(uint8, CAN_PRIVATE_DATA)
                          CanControllerInterruptCount[CAN_USED_CONTROLLER_NUM];
STATIC VAR(Can_OldIERType, CAN_PRIVATE_DATA)
                          CanControllerOldInterrupReg[CAN_USED_CONTROLLER_NUM];
STATIC VAR(uint8, CAN_PRIVATE_DATA) EmptyFlagForHth[CAN_USED_HOH_NUM];
STATIC VAR(PduIdType, CAN_PRIVATE_DATA)  PduIdForHth[CAN_USED_HOH_NUM];
STATIC VAR(Can_StateTransitionType, CAN_PRIVATE_DATA)
                          Can_ModeMonitor[CAN_USED_CONTROLLER_NUM];
/* CAN Controller Base Address */
STATIC CONST(uint32, CAN_PRIVATE_DATA) CanBasisAddress[TOTAL_CAN_MODULE_NUM]=
{
    CAN_CONTROLLER0_BASE_ADDRESS,
    CAN_CONTROLLER1_BASE_ADDRESS,
    CAN_CONTROLLER2_BASE_ADDRESS
};
uint8 gs_CanBusoffOccur = FALSE;
static VAR(boolean, CAN_PRIVATE_DATA) gs_CanSetBusOffRec = FALSE;
#define CAN_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
*   Local Functions declare
*******************************************************************************/
#define CAN_START_SEC_PRIVATE_CODE
#include "MemMap.h"

STATIC FUNC(void, CAN_PRIVATE_CODE) Can_SetID
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex,
    const Can_IdType  CanId,
    const uint8 Dlc
);
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_ClearIntFlag
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex
);

#if (CAN0_TX_PROCESSING == CAN_POLLING) || (CAN0_RX_PROCESSING == CAN_POLLING)  //Add condition compile by Wood, in order to resolve unused warning
STATIC FUNC(uint8, CAN_PRIVATE_CODE) Can_GetIntFlag
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex
);
#endif
#if (CAN0_TX_PROCESSING == CAN_POLLING) //Add condition compile by Wood, in order to resolve unused warning
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Tx_handler
(
    const uint8 Controller
);
#endif
#if (CAN0_RX_PROCESSING == CAN_POLLING) //Add condition compile by Wood, in order to resolve unused warning
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Rx_handler
(
    const uint8 Controller
);
#endif
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Busoff_handler
(
    const uint8 Controller
);
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_BusoffRecovery
(
    const uint8 phyController
);
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Controller_Transmit_Abort
(
    const uint8 Controller
);
//STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Transmit_Abort        //Remove by Wood, in order to resolve unused warning
//(
//    const uint8 phyController,
//    const Can_HwHandleType phyHth
//);

STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_RxObject_handler
(
    const uint8 Controller,
    const Can_HwHandleType MBIndex
);
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_TxObject_handler
(
    const uint8 Controller,
    const Can_HwHandleType MBIndex
);
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_MB_handler
(
    const uint8 Controller
);
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_GetIntMBNum
(
    const uint8 PhyController
);
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_MBNumToHrh
(
    const uint8 Controller,
    const Can_HwHandleType MBNum
);
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_MBNumToHth
(
    const uint8 Controller,
    const Can_HwHandleType MBNum
);
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_HthToMBNum
(
    const Can_HwHandleType Hth
);


#define CAN_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

/*******************************************************************************
*   Local Functions define
*******************************************************************************/
#define CAN_START_SEC_PRIVATE_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetID
*
* Description:   used to set id register
* Inputs:        PhyController, MBIndex,Id
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_SetID
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex,
    const Can_IdType  CanId,
    const uint8 Dlc
)
{
    uint32 tempId = CanId;
    uint8  MBLength = Dlc;

    if(MBLength > CAN_DATA_DLC)
    {
        MBLength = CAN_DATA_DLC;
    }

    /* Standrad Id */
    if(tempId < CAN_STD_EXT_BOUNDS)
    {
        tempId = tempId << CAN_STD_POS;
        tempId = tempId & CAN_EXTID_MASK;

    }
    /* Extended Id */
    else
    {
        tempId = tempId & CAN_EXTID_MASK;
        MBLength = MBLength|((uint8)(CAN_SRR_MASK|CAN_IDE_MASK));
    }

    CAN_MB(phyController, MBIndex).Id = tempId;
    /* set SRR,IDE,RTR */
    CAN_MB(phyController, MBIndex).Length = MBLength;
}



/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_ClearIntFlag
*
* Description:   used to clear interrupt flags
* Inputs:        PhyController, MBIndex
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_ClearIntFlag
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex
)
{
    uint32 shiftValue = MBIndex;
    const Can_HwHandleType Int1_Num = CAN_MB_NUM_INT1;
    const Can_HwHandleType Int2_Num = CAN_MB_NUM_INT2;
    const Can_HwHandleType Int3_Num = CAN_MB_NUM_INT3;

    if(MBIndex < Int1_Num)
    {
        shiftValue = 0x1UL << shiftValue;
        CAN_INTFLAG1(phyController) = shiftValue;
    }
    else if(MBIndex < Int2_Num)
    {
        shiftValue = shiftValue - Int1_Num;
        shiftValue = 0x1UL << shiftValue;
        CAN_INTFLAG2(phyController) = shiftValue;
    }
    else if(MBIndex < Int3_Num)
    {
    	shiftValue = shiftValue - Int2_Num;
		shiftValue = 0x1UL << shiftValue;
		CAN_INTFLAG3(phyController) = shiftValue;
    }
    else
    {}
}

#if (CAN0_TX_PROCESSING == CAN_POLLING) || (CAN0_RX_PROCESSING == CAN_POLLING)  //Add condition compile by Wood, in order to resolve unused warning
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetIntFlag
*
* Description:   used to get interrupt flags  set or not?
* Inputs:        PhyController, MBIndex
*
* Outputs:       0:the flag is not set
*                1:the flag is set
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(uint8, CAN_PRIVATE_CODE) Can_GetIntFlag
(
    const uint8 phyController,
    const Can_HwHandleType MBIndex
)
{
    uint32 shiftValue;
    uint32 intFlag;
    uint8 retflag = 0;
    const Can_HwHandleType Int1_Num = CAN_MB_NUM_INT1;
	const Can_HwHandleType Int2_Num = CAN_MB_NUM_INT2;
	const Can_HwHandleType Int3_Num = CAN_MB_NUM_INT3;
    shiftValue = MBIndex;
    if(MBIndex < Int1_Num)
    {
        intFlag = CAN_INTFLAG1(phyController);
    }
    else if (MBIndex < Int2_Num)
    {
        shiftValue = shiftValue - Int1_Num;
        intFlag = CAN_INTFLAG2(phyController);
    }
    else if(MBIndex < Int3_Num)
    {
    	shiftValue = shiftValue - Int2_Num;
		intFlag = CAN_INTFLAG3(phyController);
    }
    else
    {}

    intFlag = intFlag >> shiftValue;
    intFlag = intFlag & 0x01UL;
    if(0x01UL == intFlag)
    {
        retflag = 1;
    }

    return retflag;
}
#endif



/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetIntMBNum
*
* Description:   used for confim the smallest MB whose interrupt flag is
*                already set
* Inputs:        PhyController
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_GetIntMBNum
(
    const uint8 PhyController
)
{
    Can_HwHandleType MBIndex ;
    Can_HwHandleType temIndex = CAN_NO_INT_MB;
    uint32 temp;
    uint32 intflag1;
    uint32 intflag2;
    uint32 intflag3;
    const Can_HwHandleType Int1_Num = CAN_MB_NUM_INT1;
	const Can_HwHandleType Int2_Num = CAN_MB_NUM_INT2;
//	const Can_HwHandleType Int3_Num = CAN_MB_NUM_INT3;      //Remove by Wood, in order to resolve unused warning

    intflag1 = CAN_INTFLAG1(PhyController);
    intflag2 = CAN_INTFLAG2(PhyController);
    intflag3 = CAN_INTFLAG3(PhyController);

    if(0x0UL != intflag1)
    {
        for(MBIndex = 0; MBIndex < Int1_Num; MBIndex++)
        {
            temp = MBIndex;
            temp = 0x1UL<<temp;
            temp = temp & intflag1;

            if(0x0UL != temp)
            {
                temIndex = MBIndex;
                break;
            }
        }
    }
    else if(0x0UL != intflag2)
    {
        for(MBIndex = 0; MBIndex < Int1_Num; MBIndex++)
        {
            temp = MBIndex;
            temp = 0x1UL<<temp;
            temp = temp & intflag2;

            if(0x0UL != temp)
            {
                temIndex = MBIndex + Int1_Num;
                break;
            }
        }
    }
    else if(0x0UL != intflag3)
    {
    	for(MBIndex = 0; MBIndex < Int1_Num; MBIndex++)
		{
			temp = MBIndex;
			temp = 0x1UL<<temp;
			temp = temp & intflag3;

			if(0x0UL != temp)
			{
				temIndex = MBIndex + Int2_Num;
				break;
			}
		}
    }
    else
    {
        temIndex = CAN_NO_INT_MB;
    }
    return temIndex;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MBNumToHrh
*
* Description:   used for confim RX hardware object handle from the MB Number
*                and controller ID
* Inputs:        Controller,MBNum
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_MBNumToHrh
(
    const uint8 Controller,
    const Can_HwHandleType MBNum
)
{
    Can_HwHandleType  hrh;

    hrh = (MBNum + CanHohStartNum[CAN_CONTROLLER_ID]) -
                                             CanRxMBStartNum[CAN_CONTROLLER_ID];
    return hrh;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MBNumToHth
*
* Description:   used for confim TX hardware object handle from the MB Number
*                and controller ID
* Inputs:        Controller,MBNum
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_MBNumToHth
(
    const uint8 Controller,
    const Can_HwHandleType MBNum
)
{
    Can_HwHandleType  hth;

    hth = (MBNum + CanHohStartNum[CAN_USED_CONTROLLER_NUM + CAN_CONTROLLER_ID])-
                                             CanTxMBStartNum[CAN_CONTROLLER_ID];
    return hth;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_HthToMBNum
*
* Description:   used for confirm MB Number from the TX hardware object handle
*
* Inputs:        Controller,MBNum
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(Can_HwHandleType, CAN_PRIVATE_CODE) Can_HthToMBNum
(
    const Can_HwHandleType Hth
)
{
    Can_HwHandleType  MBNum ;

    #if (CAN_USED_CONTROLLER_NUM > 1)
    const uint8 Controller = CanHardwareObjectConfig[Hth].controllerRef;
    #endif
    MBNum = (Hth + CanTxMBStartNum[CAN_CONTROLLER_ID]) -
                     CanHohStartNum[CAN_USED_CONTROLLER_NUM + CAN_CONTROLLER_ID];

    return MBNum;

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_BusoffRecovery
*
* Description:   This function is used for bus off recovery
*
* Inputs:        phyController
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
STATIC FUNC(void, CAN_PRIVATE_CODE)  Can_BusoffRecovery
(
    const uint8 phyController
)
{
    uint8 tempCtrl3;

    tempCtrl3 = CAN_CTRL3(phyController);
    tempCtrl3 = tempCtrl3 & (CAN_BOFF_REC_MASK ^ CAN_XOR_VALUE);
    CAN_CTRL3(phyController) = tempCtrl3;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_RxObject_handler
*
* Description:   This function is used for handle the success RX indication
*
* Inputs:        Controller, MBIndex
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_RxObject_handler
(
    const uint8 Controller,
    const Can_HwHandleType MBIndex
)
{
    uint8 temprxbuffer[CAN_DATA_DLC];
    uint8 i;
    uint32 canID;
    uint8 dlc ;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType HrhIndex = Can_MBNumToHrh(CAN_CONTROLLER_ID, MBIndex);
    uint8 tempMBcode;
    uint8 tempLength;
    uint32 dummy;

    tempMBcode = CAN_MB(phyController, MBIndex).Code;
    tempMBcode = tempMBcode & CAN_CODE_MASK;

    if(((CAN_RX_MB_CODE_FULL) == tempMBcode)
      ||((CAN_RX_MB_CODE_OVERRUN) == tempMBcode))
    {
        /*get the HRH from the MB number*/
        tempLength = CAN_MB(phyController,MBIndex).Length;
        dlc = tempLength & CAN_DLC_MASK;

        for(i = 0; i < CAN_DATA_DLC; i++)
        {
            temprxbuffer[i] = CAN_MB(phyController, MBIndex).DataSeg[i];
        }

        canID = CAN_MB(phyController, MBIndex).Id;
        if(0 == (tempLength & CAN_IDE_MASK))
        {
            /*Standard ID*/
            canID = canID >> CAN_STD_POS;
            canID = canID & CAN_STDID_MASK;
        }
        else
        {
            /*Externed ID*/
            canID = canID & CAN_EXTID_MASK;
        }
        #if(CAN_ENABLE_EXTERNED_ID == STD_OFF)
        CanIf_RxIndication(HrhIndex, (Can_IdType)canID, dlc, temprxbuffer) ;
        #else
        CanIf_RxIndication(HrhIndex, canID, dlc, temprxbuffer) ;
        #endif
        /*clear RX interrupt flag*/
        Can_ClearIntFlag(phyController, MBIndex);
    }
    /* Read the timer register to release the MB. This code cannot be removed,
       if removed, the MB cannot receive Msg anymore */

    dummy = CAN_TIMER(phyController);
    dummy = dummy + dummy;      //Add by Wood, in order to solve set but not used warning
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_TxObject_handler
*
* Description:   This function is used for handle the success Tx confirmation
*
* Inputs:        Controller,MBIndex
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_TxObject_handler
(
    const uint8 Controller,
    const Can_HwHandleType MBIndex
)
{
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType HthIndex = Can_MBNumToHth(CAN_CONTROLLER_ID, MBIndex);

    EmptyFlagForHth[HthIndex] = (uint8)TRUE;
    Can_ClearIntFlag(phyController, MBIndex);
    /*the message was sented */
    CanIf_TxConfirmation(PduIdForHth[HthIndex]);
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_MB_handler
*
* Description:   This function is used for handle the MB rx or tx event
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
/*******************************************************************************
* PRQA S 3219  MISRA-C:2004 Rule 14.1
* This function will not be used to when Tx & RX events are config to POLLING
* mode. In POLLING mode, Tx & RX events will use CAN_Controller_Tx_handler and
* CAN_Controller_Rx_handler.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_MB_handler
(
    const uint8 Controller
)
{

    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType MBIndex = Can_GetIntMBNum(phyController);

    if(CAN_NO_INT_MB != MBIndex)
    {
        if((MBIndex >= CAN_RX_MB_START(CAN_CONTROLLER_ID))
        &&(MBIndex < CAN_RX_MB_END(CAN_CONTROLLER_ID)))        /*hrh*/
        {
            /*CANn_RX_PROCESSING==CAN_INTERRUPT*/
            if(0 != (CanIntConfig[CAN_CONTROLLER_ID] & CAN_RX_INT_MASK))
            {
                CAN_RxObject_handler(CAN_CONTROLLER_ID, MBIndex);
            }
        }
        else if((MBIndex >= CAN_TX_MB_START(CAN_CONTROLLER_ID))
                && (MBIndex < CAN_TX_MB_END(CAN_CONTROLLER_ID)))  /*hth*/
        {
             /*CANn_TX_PROCESSING==CAN_INTERRUPT*/
            if(0 != (CanIntConfig[CAN_CONTROLLER_ID] & CAN_TX_INT_MASK))
            {
                CAN_TxObject_handler(CAN_CONTROLLER_ID, MBIndex);
            }
        }
        else
        {
        }
    }
}

#if (CAN0_TX_PROCESSING == CAN_POLLING) //Add condition compile by Wood, in order to resolve unused warning
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Tx_handler
*
* Description:   This function is used for handle the success TX confirmation
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
/*******************************************************************************
* PRQA S 3219  MISRA-C:2004 Rule 14.1
* This function will not be used to when Tx events are config to INTERRUPT
* mode. In INTERRUPT mode, Tx & RX events will use CAN_Controller_MB_handler.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Tx_handler
(
    const uint8 Controller
)
{

    Can_HwHandleType MBIndex;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType MBstart = CAN_TX_MB_START(CAN_CONTROLLER_ID);
    const Can_HwHandleType MBend = CAN_TX_MB_END(CAN_CONTROLLER_ID);
    uint8 tempIntFlag;


    if(CAN_TX_MB_SUM(CAN_CONTROLLER_ID) > 0)  /*has TX MB*/
    {
        /*CANn_TX_PROCESSING==CAN_POLLING*/
        if(0 == (CanIntConfig[CAN_CONTROLLER_ID] & CAN_TX_INT_MASK))
        {
            for(MBIndex = MBstart; MBIndex < MBend; MBIndex++)
            {
                /*MB has sent message succeed*/
                tempIntFlag = Can_GetIntFlag(phyController, MBIndex);
                if(0 != tempIntFlag)
                {
                    /* this function is only called in polling mode
                       so disable all intrrupt here to avoid data unconsistency
                     */
                    CAN_ENTER_CRITICAL_SECTION();
                    CAN_TxObject_handler(CAN_CONTROLLER_ID, MBIndex);
                    CAN_LEAVE_CRITICAL_SECTION();
                }
            }
        }
    }
}
#endif

#if (CAN0_RX_PROCESSING == CAN_POLLING) //Add condition compile by Wood, in order to resolve unused warning
/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Rx_handler
*
* Description:   This function is used for handle the success RX indication
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
/*******************************************************************************
* PRQA S 3219  MISRA-C:2004 Rule 14.1
* This function will not be used to when Tx events are config to INTERRUPT
* mode. In INTERRUPT mode, Tx & RX events will use CAN_Controller_MB_handler.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Rx_handler
(
    const uint8 Controller
)
{
    Can_HwHandleType MBIndex;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    const Can_HwHandleType MBstart = CAN_RX_MB_START(CAN_CONTROLLER_ID);
    const Can_HwHandleType MBend = CAN_RX_MB_END(CAN_CONTROLLER_ID);
    uint8 tempIntFlag;

    if(CAN_RX_MB_SUM(CAN_CONTROLLER_ID) > 0)  /*has RX MB*/
    {
        /*CANn_RX_PROCESSING==CAN_POLLING*/
        if(0 == (CanIntConfig[CAN_CONTROLLER_ID] & CAN_RX_INT_MASK))
        {
            for(MBIndex = MBstart; MBIndex < MBend; MBIndex++)
            {
                /*MB has new received message*/
                tempIntFlag = Can_GetIntFlag(phyController, MBIndex);
                if(0 != tempIntFlag)
                {
                     /* this function is only called in polling mode
                       so disable all intrrupt here to avoid data unconsistency
                     */
                    CAN_ENTER_CRITICAL_SECTION();
                    CAN_RxObject_handler(CAN_CONTROLLER_ID, MBIndex);
                    CAN_LEAVE_CRITICAL_SECTION();
                }
            }
        }
    }
}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_Controller_Busoff_handler
*
* Description:   This function is used for handle the bus off event
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CAN_Controller_Busoff_handler
(
    const uint8 Controller
)
{
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint16 errStatusL;

    errStatusL = CAN_ERRSTATUSL(phyController);
    errStatusL = errStatusL & CAN_BOFF_MASK;

    if(errStatusL == CAN_BOFF_MASK )
    /*this controller has entered the bus off state*/
    {
		gs_CanBusoffOccur = TRUE;
        /*clear the bus off bitmask*/
        CAN_ERRSTATUSL(phyController) = CAN_BOFF_MASK;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Controller_Transmit_Abort
*
* Description:   This function is used for abort all the message in the
*                transmission buffer which is belong to one controller
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3206
* This function will not used the input parameter "Controller" in single channel
* mode. The parameter "Controller" is only used when the can driver is configed
* to use more than 1 channel.
* This part of code is verified manually and has no impact.
*******************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Controller_Transmit_Abort
(
    const uint8 Controller
)
{
    Can_HwHandleType  MBIndex;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];

    for(MBIndex = CAN_TX_MB_START(CAN_CONTROLLER_ID);
                          MBIndex < CAN_TX_MB_END(CAN_CONTROLLER_ID); MBIndex++)
    {
        CAN_MB(phyController, MBIndex).Code = CAN_TX_MB_CODE_ABORT;
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Transmit_Abort
*
* Description:   This function is used for abort 1 message in the
                 transmission buffer which is belong to one hth
*
* Inputs:        phyController,phyHth
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3219  MISRA-C:2004 Rule 14.1
* This function is not used ,just reserved for further version.
* This part of code is verified manually and has no impact.
*******************************************************************************/
//STATIC FUNC(void, CAN_PRIVATE_CODE) Can_Transmit_Abort    //Remove by Wood, in order to resolve unused warning
//(
//    const uint8 phyController,
//    const Can_HwHandleType phyHth
//)
//{
//    CAN_MB(phyController, phyHth).Code = CAN_TX_MB_CODE_ABORT;
//}

#define CAN_STOP_SEC_PRIVATE_CODE
#include "MemMap.h"

/*******************************************************************************
*  PUBLIC Functions define
*******************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_GetVersionInfo
*
* Description:   This function returns the version information of this module.
*
* Inputs:        versioninfo:Pointer to where to store the version information
*                            of this module
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
#if (STD_ON == CAN_VERSION_INFO_API)
FUNC(void, CAN_PUBLIC_CODE) Can_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo
)
{

    #if (STD_ON == CAN_DEV_ERROR_DETECT)
    if(NULL_PTR == versioninfo)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_GETVERSIONINFO_APIID,
                        CAN_E_PARAM_POINTER);
    }
    else
    #endif
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = CAN_VENDOR_ID_VALUE;
        /* Copy the module Id */
        versioninfo->moduleID = CAN_MODULE_ID_VALUE;
         /* Copy the instance Id */
        versioninfo->instanceID = CAN_INSTANCE_ID_VALUE_0;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION_VALUE;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION_VALUE;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION_VALUE;
    }

}
#endif

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Init
*
* Description:   This function initializes the module.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_Init(void)
{

    uint8 ControllerIndex;
    Can_HwHandleType hohIndex;


    #if (STD_ON == CAN_DEV_ERROR_DETECT)
    if(CAN_UNINITIALIZED != Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_INIT_APIID,
                        CAN_E_TRANSITION);
    }
    else
    #endif
    {

        #if (CAN_USED_HOH_NUM > 1)
        for(hohIndex = 0; hohIndex < CAN_USED_HOH_NUM; hohIndex++)
        #else
        hohIndex = 0;
        #endif
        {
            EmptyFlagForHth[hohIndex] = (uint8)TRUE;
            PduIdForHth[hohIndex] = CAN_EMPTY_PDUID;
        }

        #if (CAN_USED_CONTROLLER_NUM > 1)
        for(ControllerIndex = 0; ControllerIndex < CAN_USED_CONTROLLER_NUM;
                                                              ControllerIndex++)
        #else
        ControllerIndex = 0;
        #endif
        {
            CanControllerInterruptCount[ControllerIndex] = 0;
            CanControllerOldInterrupReg[ControllerIndex].oldCanCTRL2 = 0;
            CanControllerOldInterrupReg[ControllerIndex].CanIntMask2 = 0;
            CanControllerOldInterrupReg[ControllerIndex].CanIntMask1 = 0;
            CanControllerOldInterrupReg[ControllerIndex].CanIntMask3 = 0;
            // set the UDS physical request address from canp parameter
            // CanHardwareObjectConfig[0].id = get_uds_physical_request();
            Can_InitController(ControllerIndex, NULL_PTR);
            #if (CAN_DEV_ERROR_DETECT == STD_ON )
            Can_State[ControllerIndex] = CAN_STOPPED;
            #endif
        }
        #if (CAN_DEV_ERROR_DETECT == STD_ON )
        Can_DriverInitStatus = CAN_INITIALIZED;
        #endif
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_InitController
*
* Description:   This function initializes the bit timing related settings
*                of a CAN controller.
*
* Inputs:        Controller:  CAN controller to be initialized
*                config: paramter config pointer
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE)Can_InitController
(
    /* MSG3227 can not add const to this parameter to fufill the AUTOSAR API */
    uint8 Controller,
    P2CONST(Can_ControllerBaudrateConfigType, AUTOMATIC, CAN_CONFIG_CONST)
                                                                          Config
)
{
    Can_HwHandleType HohIndex;
    Can_HwHandleType MBIndex = 0;
    const Can_HwHandleType rxMBstart = CAN_RX_MB_START(CAN_CONTROLLER_ID);
    const Can_HwHandleType rxMBend = CAN_RX_MB_END(CAN_CONTROLLER_ID);
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempRegVal;
	uint16 baudrate = CAN_BR_500K;

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    /* For some reson , the current version SW can not detect the following 2
    DET error,dont remove the code to easy the further update */
    /*
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_INITCONTROLLER_APIID,
                        CAN_E_UNINIT);
    }
    if(Config == NULL_PTR)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_INITCONTROLLER_APIID,
                        CAN_E_PARAM_CONTROLLER);
    }*/
    if(Controller >= ((uint8)CAN_USED_CONTROLLER_NUM))
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_INITCONTROLLER_APIID,
                        CAN_E_PARAM_CONTROLLER);
    }
    else
    #endif
    {
        /*******************************************************************
        * PRQA S 3112   MISRA-C:2004 Rule 14.2
        * Config will be used in further version code. In this version, it's
        * just reversed to fulfill the AUTOSAR API.
        * The "(void)" is to avoid generate warning information.
        * This part of code is verified manually and has no impact.
        *******************************************************************/
        (void)Config;
        Can_BusoffRecovery(phyController);
        /*request enter into freeze mode*/
        CAN_MCR0(phyController) =
                         (uint8)(CAN_FRZ_MASK|CAN_HALT_MASK|CAN_NOT_READY_MASK);

        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
        CAN_LOOP_BEGIN(INIT_ENTER_TIMEOUT);
        #endif

        do
        {
            tempRegVal = CAN_MCR0(phyController);
            tempRegVal = tempRegVal & CAN_FRZ_ACK_MASK;
        }
        while((0 == tempRegVal)
                           && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_ENTER_TIMEOUT)));
        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
        CAN_LOOP_END(INIT_ENTER_TIMEOUT);
        #endif

        tempRegVal = CAN_MCR0(phyController);
        tempRegVal = tempRegVal & CAN_FRZ_ACK_MASK;
        if( 0 != tempRegVal)
        /*already in initialization mode*/
        {
        	/*Error correction configuration register enable*/
        	CAN_CTRL20(phyController) |= CAN_ECRWRE;

        	if(0 == phyController)
        	{
        		/*Error configuration register write enable*/
        		CAN_0.MECR.B.ECRWRDIS = 0;
        		/*Keep normal operation*/
        		CAN_0.MECR.B.NCEFAFRZ = 0;
                /*Error correction configuration register enable*/
                CAN_0.CTRL2.B.ECRWRE = 1;
                /*Enable unrestricted write access to FlexCAN memory*/
                CAN_0.CTRL2.B.WRMFRZ = 1;
                /*Error configuration register write enable*/
                CAN_0.MECR.B.ECRWRDIS = 0;
                /*Disable memory error correction*/
                CAN_0.MECR.B.ECCDIS = 1;
                /*Keep normal operation*/
                CAN_0.MECR.B.NCEFAFRZ = 0;
                /*Error configuration register write disable*/
                CAN_0.MECR.B.ECRWRDIS = 1;
                /*Disable unrestricted write access to FlexCAN memory*/
                CAN_0.CTRL2.B.WRMFRZ = 0;
                /*Error correction configuration register disable*/
                CAN_0.CTRL2.B.ECRWRE = 0;
        	}
        	else
        	{
            	CAN_MECR(phyController) &= 0x7FFFFF7F;	//TODO::
        	}
			/*set the baudrate for CAN0, CAN-FD is unsupported*/
			baudrate = get_can0_br0();
			switch(baudrate)
			{
				case CAN_BR_1M:
					CAN_CTRL0(phyController) = 1u;
					break;
				case CAN_BR_250K:
					CAN_CTRL0(phyController) = 7u;
					break;
				case CAN_BR_100K:
					CAN_CTRL0(phyController) = 19u;
					break;
				case CAN_BR_500K:
				default:
					CAN_CTRL0(phyController) = 3u;
	            	//CAN_CTRL0(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanCTRL0;
					break;
			}
            CAN_CTRL1(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanCTRL1;
            CAN_CTRL2(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanCTRL2;
			if(gs_CanBusoffOccur == FALSE)
        	{
                CAN_CTRL3(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanCTRL3;
			}
			else
			{
				gs_CanBusoffOccur = FALSE;
				gs_CanSetBusOffRec = TRUE;
			}
            CAN_MCR1(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanMCR1;
            CAN_MCR2(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanMCR2;
            CAN_MCR3(phyController) = CanRegInit[CAN_CONTROLLER_ID].CanMCR3;

            CAN_INTMASK1(phyController) =
                                      CanRegInit[CAN_CONTROLLER_ID].CanIntMask1;
            CAN_INTMASK2(phyController) =
                                      CanRegInit[CAN_CONTROLLER_ID].CanIntMask2;
            CAN_INTMASK3(phyController) =
									  CanRegInit[CAN_CONTROLLER_ID].CanIntMask3;
            /*Initialize all message buffers */
            for(MBIndex = 0; MBIndex < CAN_TOTAL_MB_NUM;MBIndex++)//;1 MBIndex++)	CAN_TOTAL_MB_NUM; MBIndex++);//1 MBIndex++)
            {
                if((MBIndex >= rxMBstart) && (MBIndex < rxMBend))   /*RX MB*/
                {
                    HohIndex = Can_MBNumToHrh(CAN_CONTROLLER_ID, MBIndex);
                    /*Receive MB*/
                    CAN_MB(phyController, MBIndex).Code = CAN_RX_MB_CODE_EMPTY;

                    Can_SetID(phyController, MBIndex, CAN_HOH_ID_REF, CAN_DATA_DLC);

                    if(0 !=
                       ((CanRegInit[CAN_CONTROLLER_ID].CanMCR1) & CAN_BCC_MASK))
                    {
                        /*BCC =1 */
                        CAN_RINDIVIMASK(phyController, MBIndex) =
                                    CanHardwareObjectConfig[HohIndex].filterRef;
                    }
                }
                else
                {
                    /* Deactivate all buffers */
                    CAN_MB(phyController, MBIndex).Code =
                                                      CAN_RX_MB_CODE_NOT_ACTIVE;
                }

            }
            if(0 == ((CanRegInit[CAN_CONTROLLER_ID].CanMCR1) & CAN_BCC_MASK))
            {
                /*BCC =0 */
                CAN_GMASK(phyController) =
                                        CanRegInit[CAN_CONTROLLER_ID].CanRGMask;
                CAN_R14MASK(phyController) =
                                       CanRegInit[CAN_CONTROLLER_ID].CanR14Mask;
                CAN_R15MASK(phyController) =
                                       CanRegInit[CAN_CONTROLLER_ID].CanR15Mask;
            }

        }

        #if (CAN_DEV_ERROR_DETECT == STD_ON )
        else
        /*fail to enter into freeze mode*/
        {
            Det_ReportError(CAN_MODULE_ID_VALUE,
                            CAN_INSTANCE_ID_VALUE_0,
                            CAN_INITCONTROLLER_APIID,
                            CAN_PL_INIT_ERROR);
        }
        #endif

        /*leave freeze mode,and enter into disable mode*/
        CAN_MCR0(phyController) = CAN_MDIS_MASK|CAN_NOT_READY_MASK;

        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
        CAN_LOOP_BEGIN(INIT_LEAVE_TIMEOUT);
        #endif

        do
        {
            tempRegVal = CAN_MCR0(phyController);
            tempRegVal = tempRegVal & CAN_FRZ_ACK_MASK;
        }while( (0 != tempRegVal)
                           && (CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT)));

        #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
        CAN_LOOP_END(INIT_LEAVE_TIMEOUT);
        #endif

        #if(CAN_DEV_ERROR_DETECT == STD_ON)
        tempRegVal = CAN_MCR0(phyController);
        tempRegVal = tempRegVal & CAN_FRZ_ACK_MASK;
        if(0 != tempRegVal)
        {
            Det_ReportError(CAN_MODULE_ID_VALUE,
                            CAN_INSTANCE_ID_VALUE_0,
                            CAN_INITCONTROLLER_APIID,
                            CAN_PL_INIT_ERROR);
        }
        Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
        #endif

    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_SetControllerMode
*
* Description:   This function performs software triggered state
*                transitions of the CAN controller State machine.
*
* Inputs:        Controller:CAN controller for which the status
*                           shall be changed
*                Transition:Transition value to request new
*                           CAN controller state
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_SetControllerMode
(
    uint8 Controller,
    Can_StateTransitionType Transition
)
{
    Can_ReturnType ret = CAN_OK;
    Can_HwHandleType  MBIndex;
    Can_HwHandleType  HohIndex;
    const uint8 phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempRegVal;
    uint8 tempMask;
	uint8 tempCtrl3;

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_SETCONTROLLERMODE_APIID,
                        CAN_E_UNINIT);
        ret = CAN_NOT_OK;
    }
    else if(Controller >= ((uint8)CAN_USED_CONTROLLER_NUM))
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_SETCONTROLLERMODE_APIID,
                        CAN_E_PARAM_CONTROLLER);
        ret = CAN_NOT_OK;
    }
    else
    #endif

    {
        switch(Transition)
        {
            case CAN_T_START:
            #if (CAN_DEV_ERROR_DETECT == STD_ON )
            if(Can_State[CAN_CONTROLLER_ID] != CAN_STOPPED)
            {
                ret = CAN_NOT_OK;
                Det_ReportError(CAN_MODULE_ID_VALUE,
                            CAN_INSTANCE_ID_VALUE_0,
                            CAN_SETCONTROLLERMODE_APIID,
                            CAN_E_TRANSITION);
            }
            else
            #endif
            {
                /*leave initialize*/
                for(MBIndex = CAN_TX_MB_START(Controller);
                                 MBIndex < CAN_TX_MB_END(Controller); MBIndex++)
                {
                    HohIndex = Can_MBNumToHth(Controller, MBIndex);
                    EmptyFlagForHth[HohIndex] = (uint8)TRUE;
                    PduIdForHth[HohIndex] = CAN_EMPTY_PDUID;
                }
                /*Enable CAN Module*/
                tempRegVal = CAN_MCR0(phyController);
				tempMask = CAN_MDIS_MASK ^ CAN_XOR_VALUE;

                //tempMask = (CAN_MDIS_MASK|CAN_FRZ_MASK|CAN_HALT_MASK) ^ CAN_XOR_VALUE;	//yanan.zhao1
                tempRegVal = tempRegVal & tempMask;
                CAN_MCR0(phyController) = tempRegVal;

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_BEGIN(INIT_LEAVE_TIMEOUT);
                #endif
            //	CAN_0.MCR.B.FRZ = 0;

            	/*No freeze mode request*/
            //	CAN_0.MCR.B.HALT = 0;

            	//while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY) {} /* Wait to clear */
            			/* Good practice: wait for FRZACK on freeze mode entry/exit */
                do
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                }while((0 != tempRegVal)
                &&(CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT)));


                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_END(INIT_LEAVE_TIMEOUT);
                #endif

				if(gs_CanSetBusOffRec == TRUE)
				{
					gs_CanSetBusOffRec = FALSE;
					tempCtrl3 = CAN_CTRL3(phyController);
					tempCtrl3 = tempCtrl3 | (CanRegInit[Controller].CanCTRL3
                                             & CAN_BOFF_REC_MASK);
					CAN_CTRL3(phyController) = tempCtrl3;
				}
                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                if(0 == tempRegVal)
                {
                    CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                              CANIF_CS_STARTED);
                    #if (CAN_DEV_ERROR_DETECT == STD_ON )
                    Can_State[CAN_CONTROLLER_ID] = CAN_STARTED;
                    #endif
                }
                else
                /*fail to enable can mode*/
                {
                    Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_START;
                }
            }
            break;

            case CAN_T_STOP:
            {
                /*cancel pending messages*/
                Can_Controller_Transmit_Abort(CAN_CONTROLLER_ID) ;
                /*Disable CAN Module,enter CAN_STOP_MODE*/
                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal | CAN_MDIS_MASK;
                CAN_MCR0(phyController) = tempRegVal;

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_BEGIN(INIT_LEAVE_TIMEOUT);
                #endif

                do
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                }while((0 == tempRegVal)
                &&(CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT)));

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_END(INIT_LEAVE_TIMEOUT);
                #endif

                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                if(0 != tempRegVal)
                {
                    CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                              CANIF_CS_STOPPED);
                    #if (CAN_DEV_ERROR_DETECT == STD_ON )
                    Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
                    #endif
                }
                else
                /*fail to enter into disable can module*/
                {
                    Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_STOP;
                }
            }
            break;

            case CAN_T_SLEEP: /* 5744 no sleep mode ,enter stop mode instead*/

            #if (CAN_DEV_ERROR_DETECT == STD_ON )
            if(Can_State[CAN_CONTROLLER_ID] == CAN_STARTED)
            {
                Det_ReportError(CAN_MODULE_ID_VALUE,
                                CAN_INSTANCE_ID_VALUE_0,
                                CAN_SETCONTROLLERMODE_APIID,
                                CAN_E_TRANSITION);
                ret = CAN_NOT_OK;
            }
            else
            #endif
            {
                /*Disable CAN Module,enter CAN_STOP_MODE*/
                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal | CAN_MDIS_MASK;
                CAN_MCR0(phyController) = tempRegVal;

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_BEGIN(INIT_LEAVE_TIMEOUT);
                #endif

                do
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                }while((0 == tempRegVal)
                &&(CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT)));

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_END(INIT_LEAVE_TIMEOUT);
                #endif

                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                if(0 != tempRegVal)
                {
                    CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                                CANIF_CS_SLEEP);
                    #if (CAN_DEV_ERROR_DETECT == STD_ON )
                    Can_State[CAN_CONTROLLER_ID] = CAN_SLEEP;
                    #endif
                }
                else
                /*fail to enter into disable can module*/
                {
                    Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_SLEEP;
                }
            }
            break;


            case CAN_T_WAKEUP:/* from sleep to stop */

            #if (CAN_DEV_ERROR_DETECT == STD_ON )
            if(Can_State[CAN_CONTROLLER_ID] != CAN_SLEEP)
            {
                Det_ReportError(CAN_MODULE_ID_VALUE,
                                CAN_INSTANCE_ID_VALUE_0,
                                CAN_SETCONTROLLERMODE_APIID,
                                CAN_E_TRANSITION);
                ret = CAN_NOT_OK;
            }
            else
            #endif
            {
                /*Disable CAN Module,enter CAN_STOP_MODE*/
                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal | CAN_MDIS_MASK;
                CAN_MCR0(phyController) = tempRegVal;

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_BEGIN(INIT_LEAVE_TIMEOUT);
                #endif

                do
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                }while((0 == tempRegVal)
                &&(CAN_OK != CAN_LOOP_TIMEOUT(INIT_LEAVE_TIMEOUT)));

                #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
                CAN_LOOP_END(INIT_LEAVE_TIMEOUT);
                #endif

                tempRegVal = CAN_MCR0(phyController);
                tempRegVal = tempRegVal & CAN_NOT_READY_MASK;

                if(0 != tempRegVal)
                {
                    CanIf_ControllerModeIndication(CAN_CONTROLLER_ID,
                                                              CANIF_CS_STOPPED);
                    #if (CAN_DEV_ERROR_DETECT == STD_ON )
                    Can_State[CAN_CONTROLLER_ID] = CAN_STOPPED;
                    #endif
                }
                else
                /*fail to enter into disable can module*/
                {
                    Can_ModeMonitor[CAN_CONTROLLER_ID] = CAN_T_WAKEUP;
                }
            }

            break;

            default:
            ret = CAN_NOT_OK;
            break;
        }
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableControllerInterrupts
*
* Description:   This function used to disable all can controller interrupts
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_DisableControllerInterrupts
(
    uint8 Controller
)
{
    const uint8  phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];
    uint8 tempMaskVal;
    uint8 tempCtrl2;
    Can_OldIERType tempIer;

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_DISABLECONTROLLERINTERRUPTS_APIID,
                        CAN_E_UNINIT);
    }
    else if(Controller >= ((uint8)CAN_USED_CONTROLLER_NUM))
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_DISABLECONTROLLERINTERRUPTS_APIID,
                        CAN_E_PARAM_CONTROLLER);

    }
    else
    #endif
    {

        if(0 == (CanControllerInterruptCount[CAN_CONTROLLER_ID]))
        {
            /* use local tempIer to ensure Reentrant*/
            tempIer.oldCanCTRL2 = CAN_CTRL2(phyController);
            tempIer.CanIntMask2 = CAN_INTMASK2(phyController);
            tempIer.CanIntMask1 = CAN_INTMASK1(phyController);
            tempIer.CanIntMask3 = CAN_INTMASK3(phyController);



            tempMaskVal = CAN_BUSOFF_INT_MASK | CAN_ERR_INT_MASK;
            tempMaskVal = tempMaskVal ^ CAN_XOR_VALUE;
            tempCtrl2 = CAN_CTRL2(phyController);
            tempCtrl2 = tempCtrl2 & tempMaskVal;
            CAN_CTRL2(phyController) = tempCtrl2;

            CAN_INTMASK2(phyController) = 0;
            CAN_INTMASK1(phyController) = 0;

            CanControllerOldInterrupReg[CAN_CONTROLLER_ID].oldCanCTRL2 = tempIer.oldCanCTRL2;
            CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask2 = tempIer.CanIntMask2;
            CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask1 = tempIer.CanIntMask1;
            CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask3 = tempIer.CanIntMask3;
        }
        CanControllerInterruptCount[CAN_CONTROLLER_ID]++;
        if(CanControllerInterruptCount[CAN_CONTROLLER_ID] > CAN_INT_NEST_COUNT)
        {
            CanControllerInterruptCount[CAN_CONTROLLER_ID] = CAN_INT_NEST_COUNT;
        }
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableControllerInterrupts
*
* Description:   This function enables all allowed interrupts.
*
* Inputs:        Controller
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE)Can_EnableControllerInterrupts
(
    uint8 Controller
)
{
    const uint8  phyController = CanControllerIDtoPhys[CAN_CONTROLLER_ID];

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_ENABLECONTROLLERINTERRUPTS_APIID,
                        CAN_E_UNINIT);
    }
    else if(Controller >= CAN_USED_CONTROLLER_NUM)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_ENABLECONTROLLERINTERRUPTS_APIID,
                        CAN_E_PARAM_CONTROLLER);
    }
    else
    #endif
    {
        if(CanControllerInterruptCount[CAN_CONTROLLER_ID] > 0)
        {
            (CanControllerInterruptCount[CAN_CONTROLLER_ID])--;
        }
        if(0 == (CanControllerInterruptCount[CAN_CONTROLLER_ID]))
        {
            CAN_CTRL2(phyController) =
                     CanControllerOldInterrupReg[CAN_CONTROLLER_ID].oldCanCTRL2;
            CAN_INTMASK2(phyController) =
                     CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask2;
            CAN_INTMASK1(phyController) =
                     CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask1;
            CAN_INTMASK3(phyController) =
					 CanControllerOldInterrupReg[CAN_CONTROLLER_ID].CanIntMask3;
        }
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_DisableGlobalInterrupt
*
* Description:   This function disables all maskable interrupts
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3006  MISRA-C:2004 Rule 2.1
* PRQA S 1006  MISRA-C:2004 Rule 1.1
* This function is used to disable global interrupts, which need to access or
* save MCU registers. So this code used assembler code.
* This part of code is verified manually and has no impact.
*******************************************************************************/
FUNC(void, CAN_PUBLIC_CODE)Can_DisableGlobalInterrupt(void)
{
    /* user local veriable to avoid reentrant */
    if(0 == CanGlobalInterruptCount)
    {
    	PPCASM(" wrteei 0");
    }
    CanGlobalInterruptCount++;
    if(CanGlobalInterruptCount > CAN_INT_NEST_COUNT)
    {
        CanGlobalInterruptCount = CAN_INT_NEST_COUNT;
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_EnableGlobalInterrupt
*
* Description:   This function enables all maskable interrupts
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*******************************************************************************
* PRQA S 3006  MISRA-C:2004 Rule 2.1
* PRQA S 1006  MISRA-C:2004 Rule 1.1
* This function is used to resume global interrupts, which need to access or
* resume MCU registers. So this code used assembler code.
* This part of code is verified manually and has no impact.
*******************************************************************************/
FUNC(void, CAN_PUBLIC_CODE) Can_EnableGlobalInterrupt(void)
{

    if(CanGlobalInterruptCount > 0)
    {
        CanGlobalInterruptCount--;
    }
    if(0 == CanGlobalInterruptCount)
    {
    	PPCASM(" wrteei 1");
    }

}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Write_Ready_Test
*
* Description:   This function used to test can transmit ready state
*
* Inputs:        Hth:  information which HW-transmit handle shall be used
*                      for transmit. Implicitly this is also the information
*                      about the controller to use because the Hth numbers
*                      are unique inside one hardware unit.
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_Write_Ready_Test
(
        Can_HwHandleType Hth
)
{
    if(((uint8)TRUE) == EmptyFlagForHth[Hth])
    {
        return CAN_OK;
    }

	return CAN_NOT_OK;
}

/*******************************************************************************
*  Services affecting a Hardware Handle
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_Write
*
* Description:   This function used to send 1 can frame
*
* Inputs:        PduInfo:  Pointer to SDU user memory, DLC and Identifier.
*                Hth:  information which HW-transmit handle shall be used
*                      for transmit. Implicitly this is also the information
*                      about the controller to use because the Hth numbers
*                      are unique inside one hardware unit.
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(Can_ReturnType, CAN_PUBLIC_CODE) Can_Write
(
    Can_HwHandleType Hth,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
)
{
    Can_ReturnType ret = CAN_OK;
    uint8 hthmatchflag = CAN_NOT_MATCH;
    uint8 Dlccount;
    uint8 Dlc;
    Can_HwHandleType MBIndex;
    const uint8 Controller = CanHardwareObjectConfig[Hth].controllerRef;
    const uint8 phyController = CanControllerIDtoPhys[Controller];
//    const Can_HwHandleType HohIndex = Hth;    //Remove by Wood, in order to resolve unused warning

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_WRITE_APIID,
                        CAN_E_UNINIT);
        ret =  CAN_NOT_OK ;
    }
    else if(Hth >= CAN_USED_HOH_NUM)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_WRITE_APIID,
                        CAN_E_PARAM_HANDLE);
        ret =  CAN_NOT_OK ;
    }
    else if(NULL_PTR == PduInfo)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_WRITE_APIID,
                        CAN_E_PARAM_POINTER);
        ret =  CAN_NOT_OK ;

    }
    else if((PduInfo->length) > CAN_DATA_DLC)
    {

        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_WRITE_APIID,
                        CAN_E_PARAM_DLC);
        ret =  CAN_NOT_OK ;
    }
    else if(0 == (CAN_HOH_TYPE & (CAN_HOH_TX_MASK))) /* not tx MB */
    {
        ret =  CAN_NOT_OK ;
    }
    else
    #endif

    {
        Dlc = PduInfo->length;

        #if (STD_ON == CAN_MULTIPLEXED_TRANSMISSION)

        #else
        MBIndex = Can_HthToMBNum(Hth);
        if(((uint8)TRUE) == EmptyFlagForHth[Hth])
        {
            hthmatchflag = CAN_MATCH;
        }
        #endif

        if(CAN_MATCH == hthmatchflag)
        /*Hth is empty*/
        {
            PduIdForHth[Hth] = PduInfo->swPduHandle ;
            /*stores the identifier, the control bits, and the data content
            into one of the transmit buffers*/
            /*Identifier Registers*/
            Can_SetID(phyController, MBIndex, PduInfo->id, Dlc);
            /*Data Segment Registers*/
            if(Dlc > CAN_DATA_DLC)
            {
                Dlc = CAN_DATA_DLC;
            }
            for(Dlccount = 0; Dlccount < Dlc; Dlccount++)
            {
                CAN_MB(phyController, MBIndex).DataSeg[Dlccount] =
                                                         PduInfo->sdu[Dlccount];
            }

            EmptyFlagForHth[Hth] = (uint8)FALSE;
            CAN_MB(phyController, MBIndex).Code = CAN_TX_MB_CODE_TRANS;
        }
        else
        /*Hth is full*/
        {
            ret = CAN_BUSY;
        }

    }
    return ret;
}

/*******************************************************************************
*  Scheduled functions
*******************************************************************************/

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Write
*
* Description:   This function performs the polling of TX confirmation
*                when CAN_TX_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Write(void)
{
    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_MAINFUNCTION_WRITE_APIID,
                        CAN_E_UNINIT);
    }
    else
    #endif
    {
        #if (CAN_USED_CONTROLLER_NUM >= 1)
            #if (CAN0_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_0);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 2)
            #if (CAN1_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_1);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 3)
            #if (CAN2_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_2);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 4)
            #if (CAN3_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_3);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 5)
            #if (CAN4_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_4);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM == 6)
            #if (CAN5_TX_PROCESSING == CAN_POLLING)
            CAN_Controller_Tx_handler(CAN_DRIVER_CONTROLLER_ID_5);
            #endif
        #endif
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Read
*
* Description:   This function performs the polling of RX indications
*                when CAN_RX_PROCESSING is set to CAN_POLLING.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Read(void)
{
    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_MAINFUNCTION_READ_APIID,
                        CAN_E_UNINIT);
    }
    else
    #endif
    {
        #if (CAN_USED_CONTROLLER_NUM >= 1)
            #if (CAN0_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_0);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 2)
            #if (CAN1_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_1);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 3)
            #if (CAN2_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_2);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 4)
            #if (CAN3_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_3);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM == 5)
            #if (CAN4_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_4);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM == 6)
            #if (CAN5_RX_PROCESSING == CAN_POLLING)
            CAN_Controller_Rx_handler(CAN_DRIVER_CONTROLLER_ID_5);
            #endif
        #endif
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_BusOff
*
* Description:   This function performs the polling of bus-off events that
*                are configured statically as 'to be polled'.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_BusOff(void)
{
    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_MAINFUNCTION_BUSOFF_APIID,
                        CAN_E_UNINIT);
    }
    else
    #endif
    {
        #if (CAN_USED_CONTROLLER_NUM >= 1)
            #if (CAN0_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_0);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 2)
            #if (CAN1_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_1);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 3)
            #if (CAN2_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_2);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 4)
            #if (CAN3_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_3);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM >= 5)
            #if (CAN4_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_4);
            #endif
        #endif
        #if (CAN_USED_CONTROLLER_NUM == 6)
            #if (CAN5_BUSOFF_PROCESSING == CAN_POLLING)
            CAN_Controller_Busoff_handler(CAN_DRIVER_CONTROLLER_ID_5);
            #endif
        #endif
    }
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: Can_MainFunction_Mode
*
* Description:   This function performs the polling of CAN controller
*                mode transitions.
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
FUNC(void, CAN_PUBLIC_CODE) Can_MainFunction_Mode(void)
{
    uint8 ControllerIndex;
    uint8 phyController;
    uint8 tempRegVal;

    #if (CAN_DEV_ERROR_DETECT == STD_ON )
    if(CAN_UNINITIALIZED == Can_DriverInitStatus)
    {
        Det_ReportError(CAN_MODULE_ID_VALUE,
                        CAN_INSTANCE_ID_VALUE_0,
                        CAN_MAINFUNCTION_MODE_APIID,
                        CAN_E_UNINIT);
    }
    else
    #endif
    {

        #if (CAN_USED_CONTROLLER_NUM > 1)
        for(ControllerIndex = 0; ControllerIndex < CAN_USED_CONTROLLER_NUM;
                                                              ControllerIndex++)
        #else
        ControllerIndex = 0;
        #endif
        {
            phyController = CanControllerIDtoPhys[ControllerIndex];
            switch(Can_ModeMonitor[ControllerIndex])
            {
                case CAN_T_START:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_MDIS_MASK;
                    if(0 == tempRegVal)
                    {
                        CanIf_ControllerModeIndication(ControllerIndex,
                                                              CANIF_CS_STARTED);
                        #if (CAN_DEV_ERROR_DETECT == STD_ON )
                        Can_State[ControllerIndex] = CAN_STARTED;
                        #endif
                        Can_ModeMonitor[ControllerIndex] = CAN_T_NONE;
                    }
                }
                break;
                case CAN_T_STOP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_MDIS_MASK;
                    if(0 != tempRegVal)
                    {
                        CanIf_ControllerModeIndication(ControllerIndex,
                                                              CANIF_CS_STOPPED);
                        #if (CAN_DEV_ERROR_DETECT == STD_ON )
                        Can_State[ControllerIndex] = CAN_STOPPED;
                        #endif
                        Can_ModeMonitor[ControllerIndex] = CAN_T_NONE;
                    }
                }
                break;

                case CAN_T_SLEEP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;
                    if(0 != tempRegVal)
                    {
                        CanIf_ControllerModeIndication(ControllerIndex,
                                                                CANIF_CS_SLEEP);
                        #if (CAN_DEV_ERROR_DETECT == STD_ON )
                        Can_State[ControllerIndex] = CAN_SLEEP;
                        #endif
                        Can_ModeMonitor[ControllerIndex] = CAN_T_NONE;
                    }
                }
                break;

                case CAN_T_WAKEUP:
                {
                    tempRegVal = CAN_MCR0(phyController);
                    tempRegVal = tempRegVal & CAN_NOT_READY_MASK;
                    if(0 != tempRegVal)
                    {
                        CanIf_ControllerModeIndication(ControllerIndex,
                                                              CANIF_CS_STOPPED);

                        #if (CAN_DEV_ERROR_DETECT == STD_ON )
                        Can_State[ControllerIndex] = CAN_STOPPED ;
                        #endif
                        Can_ModeMonitor[ControllerIndex] = CAN_T_NONE;
                    }
                }
                break;
                default:

                break;

            }
        }
    }
}

#define CAN_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"
/*******************************************************************************
*  ISR
*******************************************************************************/
#define CAN_START_SEC_ISR_CODE
#include "MemMap.h"

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: CAN_PHYx_MB_ISR \ CAN_Controller_Busoff_handler
*
* Description:   These functions are ISR for can event
*
* Inputs:        None
*
* Outputs:       None
*
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
/*
  In hardware vector mode,INTC.MCR.B.HVEN = 1;
  user may need to add prefix to ISR
  __declspec(interrupt)
*/

#if (STD_ON == CAN_PHY0_ACTIVATION)
    #if((CAN_INTERRUPT == CAN_PHY0_TX_PROCESSING) \
       ||(CAN_INTERRUPT == CAN_PHY0_RX_PROCESSING))
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY0_MB_ISR(void)
    {
        CAN_Controller_MB_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif

    #if(CAN_INTERRUPT == CAN_PHY0_BUSOFF_PROCESSING)
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY0_Busoff_ISR(void)
    {
        CAN_Controller_Busoff_handler(CAN_PHY0_TO_LOGIC);
    }
    #endif
#endif

#if (STD_ON == CAN_PHY1_ACTIVATION)
    #if((CAN_INTERRUPT == CAN_PHY1_TX_PROCESSING) \
       ||(CAN_INTERRUPT == CAN_PHY1_RX_PROCESSING))
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY1_MB_ISR(void)
    {
        CAN_Controller_MB_handler(CAN_PHY1_TO_LOGIC);
    }
    #endif

    #if(CAN_INTERRUPT == CAN_PHY1_BUSOFF_PROCESSING)
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY1_Busoff_ISR(void)
    {
        CAN_Controller_Busoff_handler(CAN_PHY1_TO_LOGIC);
    }
    #endif
#endif

#if (STD_ON == CAN_PHY2_ACTIVATION)
    #if((CAN_INTERRUPT == CAN_PHY2_TX_PROCESSING) \
       ||(CAN_INTERRUPT == CAN_PHY2_RX_PROCESSING))
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY2_MB_ISR(void)
    {
        CAN_Controller_MB_handler(CAN_PHY2_TO_LOGIC);
    }
    #endif

    #if(CAN_INTERRUPT == CAN_PHY2_BUSOFF_PROCESSING)
    FUNC(void, CAN_PUBLIC_CODE) CAN_PHY2_Busoff_ISR(void)
    {
        CAN_Controller_Busoff_handler(CAN_PHY2_TO_LOGIC);
    }
    #endif
#endif

#define CAN_STOP_SEC_ISR_CODE
#include "MemMap.h"

