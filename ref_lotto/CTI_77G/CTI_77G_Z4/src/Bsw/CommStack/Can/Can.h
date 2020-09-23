/*  BEGIN_FILE_HDR
 ********************************************************************************
 *   NOTICE
 *   This software is the property of HiRain Technologies. Any information
 *   contained in this doc should not be reproduced, or used, or disclosed
 *   without the written authorization from HiRain Technologies.
 ********************************************************************************
 *   File Name       : Can.h
 ********************************************************************************
 *   Project/Product : AUTOSAR 4.0
 *   Title           : CAN Driver module head File
 *   Author          : HeYang
 ********************************************************************************
 *   Description     : The header file Can.h contains the declaration of the Can
 *                     module API;contains 'extern' declarations of constants,
 *                     global data,type definitions and services that are
 *                     specified in the Can module SWS.
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
 ********************************************************************************
 * END_FILE_HDR*/
#ifndef _CAN_H_
#define _CAN_H_

/*******************************************************************************
 *   Includes
 *******************************************************************************/
#include "Can_Type.h"
#include "Can_Pl.h"

/*******************************************************************************
 *   Macro
 *******************************************************************************/
#define CAN_EMPTY_PDUID            ((PduIdType)(~(0x0U)))
#define CAN_NO_INT_MB              ((Can_HwHandleType)(~(0x0U)))
#define CAN_DATA_DLC               ((uint8)0x08U)
#define CAN_INT_NEST_COUNT         ((uint8)250U)
#define CAN_STD_EXT_BOUNDS         (0x800UL)

/*CAN104: The Can module shall be able to detect the following errors and
 exceptions depending on its configuration (development/production)*/
#if (CAN_DEV_ERROR_DETECT == STD_ON )
/*API Service called with wrong parameter;Development*/
#define  CAN_E_PARAM_POINTER      (0x01U)
/*API Service called with wrong parameter;Development*/
#define  CAN_E_PARAM_HANDLE       (0x02U)
/*API Service called with wrong parameter;Development*/
#define  CAN_E_PARAM_DLC          (0x03U)
/*API Service called with wrong parameter;Development*/
#define  CAN_E_PARAM_CONTROLLER   (0x04U)
/*API Service used without initialization;Development*/
#define  CAN_E_UNINIT             (0x05U)
/*Invalid transition for the current mode;Development*/
#define  CAN_E_TRANSITION         (0x06U)
/*Received CAN message is lost;Development*/
#define  CAN_E_DATALOST           (0x07U)
/*CAN can't enter into initialize mode or leave initialize mode*/
#define  CAN_PL_INIT_ERROR        (0x08U)

#define  CAN_INIT_APIID                                 (0x00U)
#define  CAN_MAINFUNCTION_WRITE_APIID                   (0x01U)
#define  CAN_INITCONTROLLER_APIID                       (0x02U)
#define  CAN_SETCONTROLLERMODE_APIID                    (0x03U)
#define  CAN_DISABLECONTROLLERINTERRUPTS_APIID          (0x04U)
#define  CAN_ENABLECONTROLLERINTERRUPTS_APIID           (0x05U)
#define  CAN_WRITE_APIID                                (0x06U)
#define  CAN_GETVERSIONINFO_APIID                       (0x07U)
#define  CAN_MAINFUNCTION_READ_APIID                    (0x08U)
#define  CAN_MAINFUNCTION_BUSOFF_APIID                  (0x09U)
#define  CAN_MAINFUNCTION_WAKEUP_APIID                  (0x0aU)
#define  CAN_MAINFUNCTION_MODE_APIID                    (0x0cU)
#endif

/*******************************************************************************
 *   CanController
 *******************************************************************************/
/*CAN316_Conf    :This parameter rovides the controller ID which is unique in a
 given CAN Driver. The value for this parameter starts with 0
 and continue without any gaps*/
#if (CAN_USED_CONTROLLER_NUM >= 1)
#define CAN_DRIVER_CONTROLLER_ID_0  (0U)
#endif
#if (CAN_USED_CONTROLLER_NUM >= 2)
#define CAN_DRIVER_CONTROLLER_ID_1  (1U)
#endif
#if (CAN_USED_CONTROLLER_NUM >= 3)
#define CAN_DRIVER_CONTROLLER_ID_2  (2U)
#endif
#if (CAN_USED_CONTROLLER_NUM >= 4)
#define CAN_DRIVER_CONTROLLER_ID_3  (3U)
#endif
#if (CAN_USED_CONTROLLER_NUM >= 5)
#define CAN_DRIVER_CONTROLLER_ID_4  (4U)
#endif
#if (CAN_USED_CONTROLLER_NUM == 6)
#define CAN_DRIVER_CONTROLLER_ID_5  (5U)
#endif
#if (CAN_USED_CONTROLLER_NUM > 6)
#error "!!!ERROR FOR CAN_USED_CONTROLLER_NUM!!!"
#endif

/*******************************************************************************
 *   Global Data Declaration
 *******************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
 * PRQA S 3684   MISRA-C:2004 Rule 8.12
 * The following arrays are configurable parameters, they are declared without
 * any size to ensure that users can config these parameters even in lib code.
 * This part of code is verified manually and has no impact.
 *******************************************************************************/
extern CONST(uint8, CAN_CONFIG_CONST)
CanControllerIDtoPhys[];
extern CONST(Can_RegInitType, CAN_CONFIG_CONST)
CanRegInit[];
extern VAR(Can_HardwareObjectConfigType, CAN_PRIVATE_DATA)
CanHardwareObjectConfig[];
extern CONST(uint8, CAN_CONFIG_CONST)
CanIntConfig[];
extern CONST(Can_HwHandleType, CAN_CONFIG_CONST)
CanRxMBStartNum[];
extern CONST(Can_HwHandleType, CAN_CONFIG_CONST)
CanRxMBSum[];
extern CONST(Can_HwHandleType, CAN_CONFIG_CONST)
CanTxMBStartNum[];
extern CONST(Can_HwHandleType, CAN_CONFIG_CONST)
CanTxMBSum[];
extern CONST(Can_HwHandleType, CAN_CONFIG_CONST)
CanHohStartNum[];
extern uint8 gs_CanBusoffOccur;

#define CAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
 *   Global Function Declaration
 *******************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "MemMap.h"

#if (STD_ON == CAN_VERSION_INFO_API)
extern FUNC(void, CAN_PUBLIC_CODE)
Can_GetVersionInfo
(
        P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) versioninfo
);
#endif

extern FUNC(void, CAN_PUBLIC_CODE)
Can_Init(void);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_InitController
(
        uint8 Controller,
        P2CONST(Can_ControllerBaudrateConfigType, AUTOMATIC, CAN_CONFIG_CONST)
        Config
);

extern FUNC(Can_ReturnType, CAN_PUBLIC_CODE)
Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_DisableControllerInterrupts(uint8 Controller);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_EnableControllerInterrupts(uint8 Controller);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_DisableGlobalInterrupt(void);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_EnableGlobalInterrupt(void);

extern FUNC(Can_ReturnType, CAN_PUBLIC_CODE)
Can_Write_Ready_Test
(
        Can_HwHandleType Hth
);

extern FUNC(Can_ReturnType, CAN_PUBLIC_CODE)
Can_Write
(
        Can_HwHandleType Hth,
        P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo
);

/* Scheduled functions */
extern FUNC(void, CAN_PUBLIC_CODE)
Can_MainFunction_Write(void);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_MainFunction_Read(void);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_MainFunction_BusOff(void);

extern FUNC(void, CAN_PUBLIC_CODE)
Can_MainFunction_Mode(void);

#define CAN_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

/* Application Call back function */
#define CAN_START_SEC_APPL_CODE
#include "MemMap.h"

#if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
extern FUNC(void, CAN_APPL_CODE)
ApplTimerBegin(uint8 LoopReason);
extern FUNC(Can_ReturnType, CAN_APPL_CODE)
ApplTimerOutCheck(uint8 LoopReason);
extern FUNC(void, CAN_APPL_CODE)
ApplTimerEnd(uint8 LoopReason);
#endif/* #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)  */

#define CAN_STOP_SEC_APPL_CODE
#include "MemMap.h"

/* ISR */
#define CAN_START_SEC_ISR_CODE
#include "MemMap.h"

extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY0_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY0_Busoff_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY1_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY1_Busoff_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY2_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY2_Busoff_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY3_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY3_Busoff_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY4_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY4_Busoff_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY5_MB_ISR(void);
extern FUNC(void, CAN_PUBLIC_CODE)
CAN_PHY5_Busoff_ISR(void);

#define CAN_STOP_SEC_ISR_CODE
#include "MemMap.h"

#endif /* _CAN_H_ */

