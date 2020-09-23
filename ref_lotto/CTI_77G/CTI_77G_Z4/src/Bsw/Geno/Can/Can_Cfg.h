/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Can_Cfg.h
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


#ifndef _CAN_CFG_H_
#define _CAN_CFG_H_
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "ComStack_Types.h"
/*******************************************************************************
*   Common Macro 
*******************************************************************************/
#define CAN_INTERRUPT                       (1U)
#define CAN_POLLING                         (0U)
#define CAN_STANDARD_ID_ONLY                (1U)
#define CAN_EXTERNED_ID_ONLY                (2U)
#define CAN_MIXED_ID                        (3U)

#define CAN_HOH_TX_MASK                     ((uint8)0x01U)
#define CAN_HOH_RX_MASK                     ((uint8)0x00U)
#define CAN_HOH_FULL_MASK                   ((uint8)0x02U)
#define CAN_HOH_BASIC_MASK                  ((uint8)0x00U)

/*******************************************************************************
*   CanGeneral  
*******************************************************************************/
#define CAN_MAIN_FUNCTION_BUS_OFF_PERIOD     (1U)
#define CAN_MAIN_FUNCTION_MODE_PERIOD        (1U)
#define CAN_MAIN_FUNCTION_READ_PERIOD        (1U)
#define CAN_MAIN_FUNCTION_WAKEUP_PERIOD      (1U)
#define CAN_MAIN_FUNCTION_WRITE_PERIOD       (1U)
#define CAN_DEV_ERROR_DETECT                 STD_OFF
#define CAN_HW_TRANSMIT_CANCELLATION         STD_OFF
#define CAN_IDENTICAL_ID_CANCELLATION        STD_OFF
#define CAN_MULTIPLEXED_TRANSMISSION         STD_OFF
#define CAN_TIMEOUT_DURATION                 (100U)
#define CAN_VERSION_INFO_API                 STD_OFF
#define USE_CANIF                            STD_ON 
#define CAN_AUTOSET_INTERRUPT_PRIORITY       STD_OFF
//#define CAN_ID_TYPE_SUPPORT                  CAN_STANDARD_ID_ONLY

#define CAN_USED_CONTROLLER_NUM              (1)
#define CAN_USED_HOH_NUM                     (96)
#define CAN_VENDOR_ID_VALUE                  ((uint16)26)
#define CAN_MODULE_ID_VALUE                  ((uint16)80)
#define CAN_INSTANCE_ID_VALUE_0              ((uint8)0)
#define CAN_SW_MAJOR_VERSION_VALUE           (1)
#define CAN_SW_MINOR_VERSION_VALUE           (3)
#define CAN_SW_PATCH_VERSION_VALUE           (0)

#define Can_EnableGlobalInterrupts           Can_EnableGlobalInterrupt
#define Can_DisableGlobalInterrupts          Can_DisableGlobalInterrupt
#if (CAN_ID_TYPE_SUPPORT == CAN_STANDARD_ID_ONLY)

    #define CAN_ENABLE_EXTERNED_ID           STD_OFF
#else
    #define CAN_ENABLE_EXTERNED_ID           STD_ON
#endif

/*******************************************************************************
*    Special CanController Configuration
*******************************************************************************/

/*******************************************************************************
*    CanController
*******************************************************************************/
#define CAN0_CONTROLLER_ACTIVATION        STD_ON 
#define CAN0_CONTROLLER_BASE_ADDRESS      (0xFFEC0000U)
#define CAN0_CLKSRC_BUSCLK                STD_OFF
#define CAN0_CLOCK_REFERENCE              (40000U)
#define CAN0_CONTROLLER_BAUD_RATE         (500U)
#define CAN0_RX_PROCESSING                CAN_INTERRUPT
#define CAN0_TX_PROCESSING                CAN_INTERRUPT
#define CAN0_BUSOFF_PROCESSING            CAN_INTERRUPT
#define CAN0_BUSOFF_AUTOREC               STD_ON
#define CAN0_BACKWARDS_COMPATIBILITY      STD_OFF

#define CAN_PHY0_ACTIVATION               CAN0_CONTROLLER_ACTIVATION 
#define CAN_PHY0_RX_PROCESSING            CAN0_RX_PROCESSING 
#define CAN_PHY0_TX_PROCESSING            CAN0_TX_PROCESSING 
#define CAN_PHY0_BUSOFF_PROCESSING        CAN0_BUSOFF_PROCESSING 
#define CAN_PHY0_TO_LOGIC                 (0U)

#define CAN_PHY1_ACTIVATION               STD_OFF 
#define CAN_PHY1_RX_PROCESSING            CAN_INTERRUPT 
#define CAN_PHY1_TX_PROCESSING            CAN_INTERRUPT 
#define CAN_PHY1_BUSOFF_PROCESSING        CAN_INTERRUPT 
#define CAN_PHY1_TO_LOGIC                 (0U)

#define CAN_PHY2_ACTIVATION               STD_OFF 
#define CAN_PHY2_RX_PROCESSING            CAN_INTERRUPT 
#define CAN_PHY2_TX_PROCESSING            CAN_INTERRUPT 
#define CAN_PHY2_BUSOFF_PROCESSING        CAN_INTERRUPT 
#define CAN_PHY2_TO_LOGIC                 (0U)


#endif  /* _CAN_CFG_H_ */ 
