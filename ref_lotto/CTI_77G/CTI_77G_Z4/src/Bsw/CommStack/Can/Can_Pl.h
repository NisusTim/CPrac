/*  BEGIN_FILE_HDR
 ********************************************************************************
 *   NOTICE
 *   This software is the property of HiRain Technologies. Any information
 *   contained in this doc should not be reproduced, or used, or disclosed
 *   without the written authorization from HiRain Technologies.
 ********************************************************************************
 *   File Name       : Can_Pl.h
 ********************************************************************************
 *   Project/Product : AUTOSAR 4.0
 *   Title           : CAN Driver platform head File
 *   Author          : HeYang
 ********************************************************************************
 *   Description     : The header file Can_Pl.h contains type definitions and
 *                      macros which relate to specific MCU .
 *
 ********************************************************************************
 *   Limitations     : only used for MPC5604B/C
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
#ifndef _CAN_PL_H_
#define _CAN_PL_H_

/*******************************************************************************
 *   Includes
 *******************************************************************************/
#include "Can_Cfg.h"

/*******************************************************************************
 *   Macro
 *******************************************************************************/
#define CAN_HARDWARE_TIMEOUT_CHECK      STD_OFF
#define CAN_ENTER_CRITICAL_SECTION()    Can_DisableGlobalInterrupt()
#define CAN_LEAVE_CRITICAL_SECTION()    Can_EnableGlobalInterrupt()
#define CAN_NOT_MATCH                   ((uint8)0x0U)
#define CAN_MATCH                       ((uint8)0x1U)
#define CAN_CONTROLLER_NOT_HOH          (0xffU)
#define CAN_TOTAL_MB_NUM                ((Can_HwHandleType)0x60U)
#define TOTAL_CAN_MODULE_NUM            (0x3U)
#define CAN_MB_NUM_INT1                  ((Can_HwHandleType)32U)
#define CAN_MB_NUM_INT2                  ((Can_HwHandleType)64U)
#define CAN_MB_NUM_INT3                  ((Can_HwHandleType)96U)
#define CAN_STD_POS                     (18U)
#define CAN_EXTID_MASK                  (0x1fffffffUL)
#define CAN_STDID_MASK                  (0x7ffUL)
#define CAN_XOR_VALUE                   ((uint8)0xffU)

/*******************************************************************************
 *   ISR enroll related & vetor numbers
 *******************************************************************************/
#define VECTOR_NUM_FlexCAN0_BUSOFF      (66U)
#define VECTOR_NUM_FlexCAN0_BUF_00_03   (68U)
#define VECTOR_NUM_FlexCAN0_BUF_04_07   (69U)
#define VECTOR_NUM_FlexCAN0_BUF_08_11   (70U)
#define VECTOR_NUM_FlexCAN0_BUF_12_15   (71U)
#define VECTOR_NUM_FlexCAN0_BUF_16_31   (72U)
#define VECTOR_NUM_FlexCAN0_BUF_32_63   (73U)

#define VECTOR_NUM_FlexCAN1_BUSOFF      (86U)
#define VECTOR_NUM_FlexCAN1_BUF_00_03   (88U)
#define VECTOR_NUM_FlexCAN1_BUF_04_07   (89U)
#define VECTOR_NUM_FlexCAN1_BUF_08_11   (90U)
#define VECTOR_NUM_FlexCAN1_BUF_12_15   (91U)
#define VECTOR_NUM_FlexCAN1_BUF_16_31   (92U)
#define VECTOR_NUM_FlexCAN1_BUF_32_63   (93U)

#define VECTOR_NUM_FlexCAN2_BUSOFF      (106U)
#define VECTOR_NUM_FlexCAN2_BUF_00_03   (108U)
#define VECTOR_NUM_FlexCAN2_BUF_04_07   (109U)
#define VECTOR_NUM_FlexCAN2_BUF_08_11   (110U)
#define VECTOR_NUM_FlexCAN2_BUF_12_15   (111U)
#define VECTOR_NUM_FlexCAN2_BUF_16_31   (112U)
#define VECTOR_NUM_FlexCAN2_BUF_32_63   (113U)

#define VECTOR_NUM_FlexCAN3_BUSOFF      (174U)
#define VECTOR_NUM_FlexCAN3_BUF_00_03   (176U)
#define VECTOR_NUM_FlexCAN3_BUF_04_07   (177U)
#define VECTOR_NUM_FlexCAN3_BUF_08_11   (178U)
#define VECTOR_NUM_FlexCAN3_BUF_12_15   (179U)
#define VECTOR_NUM_FlexCAN3_BUF_16_31   (180U)
#define VECTOR_NUM_FlexCAN3_BUF_32_63   (181U)

#define VECTOR_NUM_FlexCAN4_BUSOFF      (191U)
#define VECTOR_NUM_FlexCAN4_BUF_00_03   (193U)
#define VECTOR_NUM_FlexCAN4_BUF_04_07   (194U)
#define VECTOR_NUM_FlexCAN4_BUF_08_11   (195U)
#define VECTOR_NUM_FlexCAN4_BUF_12_15   (196U)
#define VECTOR_NUM_FlexCAN4_BUF_16_31   (197U)
#define VECTOR_NUM_FlexCAN4_BUF_32_63   (198U)

#define VECTOR_NUM_FlexCAN5_BUSOFF      (203U)
#define VECTOR_NUM_FlexCAN5_BUF_00_03   (205U)
#define VECTOR_NUM_FlexCAN5_BUF_04_07   (206U)
#define VECTOR_NUM_FlexCAN5_BUF_08_11   (207U)
#define VECTOR_NUM_FlexCAN5_BUF_12_15   (208U)
#define VECTOR_NUM_FlexCAN5_BUF_16_31   (209U)
#define VECTOR_NUM_FlexCAN5_BUF_32_63   (210U)

/*******************************************************************************
 *   Can Controller Base Address
 *******************************************************************************/
#define CAN_CONTROLLER0_BASE_ADDRESS    (0xffec0000UL)
#define CAN_CONTROLLER1_BASE_ADDRESS    (0xffec4000UL)
#define CAN_CONTROLLER2_BASE_ADDRESS    (0xfBEC0000UL)//(0xffec8000UL)//yanan.zhao1

/*******************************************************************************
 *   Typedef
 *******************************************************************************/
/*******************************************************************************
 * PRQA S 3132
 * Hard coded 'magic' number used in Can_RegType and Can_MsgBufType.
 * These numbers are only used once in this file and they are used to define
 * hw registers, so its not necessary to use macro.
 * This part of code is verified manually and has no impact.
 *******************************************************************************/
typedef struct {
    volatile uint8 Code; /* Message Buffer Code                */
    volatile uint8 Length; /* SRR,IDE,RTR,LENGTH              */
    volatile uint16 TimeStamp; /* Identifier Register 0,1            */
    volatile uint32 Id; /* Identifier Register 0,1            */
    volatile uint8 DataSeg[8]; /* Data 0 .. 7                        */
} Can_MsgBufType;

typedef struct {
    volatile uint8 CanMCR0;			//0xFFEC0000
    volatile uint8 CanMCR1;			//0xFFEC0001
    volatile uint8 CanMCR2;			//0xFFEC0002
    volatile uint8 CanMCR3;			//0xFFEC0003
    volatile uint8 CanCTRL0;		//0xFFEC0004
    volatile uint8 CanCTRL1;		//0xFFEC0005
    volatile uint8 CanCTRL2;		//0xFFEC0006
    volatile uint8 CanCTRL3;		//0xFFEC0007
    volatile uint8 CanReserved1[2];	//0xFFEC0008
    volatile uint16 CanTimer;		//0xFFEC000A
    volatile uint8 CanReserved2[4];	//0xFFEC000C
    volatile uint32 CanGMask;		//0xFFEC0010
    volatile uint32 CanR14Mask; 	//0xFFEC0014
    volatile uint32 CanR15Mask; 	//0xFFEC0018
    volatile uint8 CanReserved3[2]; //0xFFEC0019
    volatile uint8 CanRxErrCount; 	//0xFFEC001B
    volatile uint8 CanTxErrCount; 	//0xFFEC001C
    volatile uint16 CanErrStatusH; 	//0xFFEC0020
    volatile uint16 CanErrStatusL; 	//0xFFEC0022
    volatile uint32 CanIntMask2; 	//0xFFEC0024
    volatile uint32 CanIntMask1; 	//0xFFEC0028
    volatile uint32 CanIntFlag2; 	//0xFFEC002C
    volatile uint32 CanIntFlag1; 	//0xFFEC0030
    volatile uint8 CanCTRL20; 		//0xFFEC0034
    volatile uint8 CanCTRL21; 		//0xFFEC0035
    volatile uint8 CanCTRL22; 		//0xFFEC0036
    volatile uint8 CanCTRL23; 		//0xFFEC0037
    volatile uint8 CanReserved4[52];//0xFFEC0038 - 0xFFEC006B
    volatile uint32 CanIntMask3; 	//0xFFEC006C
    volatile uint32 CanReserved7;	//0xFFEC0070
    volatile uint32 CanIntFlag3; 	//0xFFEC0074
    volatile uint8 CanReserved6[8]; //0xFFEC0078
    Can_MsgBufType CanMB[96];		//total 96*16 = 1536 , 0xFFEC0080 - 0xFFEC067F
    volatile uint8 CanReserved5[512]; 	//0xFFEC0680 - 0xFFEC087F
    volatile uint32 CanRIndiviMask[96];	//0xFFEC0880-
    volatile uint32 CanMECR;
} Can_RegType;

typedef struct {
    uint8 CanMCR0;
    uint8 CanMCR1;
    uint8 CanMCR2;
    uint8 CanMCR3;
    uint8 CanCTRL0;
    uint8 CanCTRL1;
    uint8 CanCTRL2;
    uint8 CanCTRL3;
    uint32 CanRGMask;
    uint32 CanR14Mask;
    uint32 CanR15Mask;
    uint32 CanIntMask2;
    uint32 CanIntMask1;
    uint32 CanIntMask3;
} Can_RegInitType;

typedef struct {
    uint8 oldCanCTRL2;
    uint32 CanIntMask2;
    uint32 CanIntMask1;
    uint32 CanIntMask3;
} Can_OldIERType;

/*******************************************************************************
 *  Register definitions
 *******************************************************************************/

/*******************************************************************************
 * PRQA S 3453  MISRA-C:2004 Rule 19.7
 * These function-like macros are defined to access can hw registers, which can
 * improve the readability of the code.
 * This part of code is verified manually and has no impact.
 *******************************************************************************/
#define CAN_CONTROLLER_BASIS_ADR(phyController)     \
                               ((Can_RegType *)(CanBasisAddress[phyController]))

#define CAN_MCR0(phyController)                     \
                              (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR0)

#define CAN_MCR1(phyController)                     \
                              (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR1)

#define CAN_MCR2(phyController)                     \
                              (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR2)

#define CAN_MCR3(phyController)                     \
                              (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMCR3)

#define CAN_CTRL0(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL0)

#define CAN_CTRL1(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL1)

#define CAN_CTRL2(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL2)

#define CAN_CTRL3(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL3)
#define CAN_CTRL20(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanCTRL20)
#define CAN_TIMER(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanTimer)

#define CAN_GMASK(phyController)                    \
                             (CAN_CONTROLLER_BASIS_ADR(phyController)->CanGMask)

#define CAN_R14MASK(phyController)                  \
                           (CAN_CONTROLLER_BASIS_ADR(phyController)->CanR14Mask)

#define CAN_R15MASK(phyController)                  \
                           (CAN_CONTROLLER_BASIS_ADR(phyController)->CanR15Mask)

#define CAN_RXERRCOUNT(phyController)               \
                        (CAN_CONTROLLER_BASIS_ADR(phyController)->CanRxErrCount)

#define CAN_TXERRCOUNT(phyController)               \
                        (CAN_CONTROLLER_BASIS_ADR(phyController)->CanTxErrCount)

#define CAN_ERRSTATUSH(phyController)               \
                        (CAN_CONTROLLER_BASIS_ADR(phyController)->CanErrStatusH)

#define CAN_ERRSTATUSL(phyController)               \
                        (CAN_CONTROLLER_BASIS_ADR(phyController)->CanErrStatusL)

#define CAN_INTMASK2(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntMask2)

#define CAN_INTMASK1(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntMask1)

#define CAN_INTFLAG2(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntFlag2)

#define CAN_INTFLAG1(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntFlag1)

#define CAN_INTMASK3(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntMask3)

#define CAN_INTFLAG3(phyController)                 \
                          (CAN_CONTROLLER_BASIS_ADR(phyController)->CanIntFlag3)

#define CAN_MB(phyController,MBNum)                 \
                       ((CAN_CONTROLLER_BASIS_ADR(phyController)->CanMB)[MBNum])

#define CAN_RINDIVIMASK(phyController,MBNum)        \
              ((CAN_CONTROLLER_BASIS_ADR(phyController)->CanRIndiviMask)[MBNum])
#define CAN_MECR(phyController)        			\
              	  	  	  	  (CAN_CONTROLLER_BASIS_ADR(phyController)->CanMECR)
#define CAN_INTC_EOIR   (*(volatile uint32*)0xFC040030UL)

/*******************************************************************************
 *  Register Mask Value define
 *******************************************************************************/
#define CAN_CODE_MASK                               ((uint8)0x0fU)

#define CAN_TX_MB_CODE_INACTIVE                     ((uint8)0x08U)
#define CAN_TX_MB_CODE_ABORT                        ((uint8)0x09U)
#define CAN_TX_MB_CODE_TRANS                        ((uint8)0x0CU)
#define CAN_TX_MB_CODE_TRANSED_REMOTE               ((uint8)0x04U)
#define CAN_TX_MB_CODE_TRANS_RESPOND_REMOTE         ((uint8)0x0AU)
#define CAN_TX_MB_CODE_TRANS_RESPONDING_REMOTE      ((uint8)0x0EU)

#define CAN_RX_MB_CODE_NOT_ACTIVE                   ((uint8)0x00U)
#define CAN_RX_MB_CODE_EMPTY                        ((uint8)0x04U)
#define CAN_RX_MB_CODE_FULL                         ((uint8)0x02U)
#define CAN_RX_MB_CODE_OVERRUN                      ((uint8)0x06U)
#define CAN_RX_MB_CODE_BUSY_TO_EMPTY                ((uint8)0x03U)
#define CAN_RX_MB_CODE_BUSY_TO_NOTEMP               ((uint8)0x07U)

/* Bitmask of CanMCR0*/
#define CAN_FRZ_ACK_MASK    ((uint8)0x01U)    /* Freeze Mode Acknowledge    */
#define CAN_SOFT_RST_MASK   ((uint8)0x02U)    /* Soft Reset                 */
#define CAN_NOT_READY_MASK  ((uint8)0x08U)    /* FlexCAN Not Ready          */
#define CAN_HALT_MASK       ((uint8)0x10U)    /* Halt FlexCAN               */
#define CAN_FEN_MASK        ((uint8)0x20U)    /* FIFO Enable                */
#define CAN_FRZ_MASK        ((uint8)0x40U)    /* Freeze Enable              */
#define CAN_MDIS_MASK        ((uint8)0x80U)    /* Module Disable             */

/* Bitmask of CanCTRL3*/
#define CAN_BOFF_REC_MASK   ((uint8)0x40U)
/* Bitmask of CanCTRL20*/
#define CAN_ECRWRE   		((uint8)0x20U)
/* Bitmask of CanMCR1*/
#define CAN_BCC_MASK        ((uint8)0x01U)    /*Backwards Compatibility
                                                              Configuration*/

/*Bitmask of CanMB.Length*/
#define CAN_SRR_MASK        ((uint8)0x40U)
#define CAN_IDE_MASK        ((uint8)0x20U)
#define CAN_RTR_MASK        ((uint8)0x10U)
#define CAN_DLC_MASK        ((uint8)0x0fU)

/*Bitmask of CanESRL*/
#define CAN_BOFF_MASK       ((uint16)0x04U)

#define CAN_TX_INT_MASK            ((uint8)0x01U)
#define CAN_RX_INT_MASK            ((uint8)0x02U)
#define CAN_BUSOFF_INT_MASK        ((uint8)0x80U)
#define CAN_ERR_INT_MASK           ((uint8)0x40U)

/*******************************************************************************
 *  Controller related
 *******************************************************************************/
#if (CAN_USED_CONTROLLER_NUM >= 1)
#if (CAN0_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN0_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN0_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN0_BUSOFF_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN0_BUSOFF_CFG!!!"
#endif

#if (CAN0_TX_PROCESSING == CAN_INTERRUPT)
#define CAN0_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN0_TX_PROCESSING == CAN_POLLING)
#define CAN0_TX_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN0_TX_CFG!!!"
#endif

#if (CAN0_RX_PROCESSING == CAN_INTERRUPT)
#define CAN0_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN0_RX_PROCESSING == CAN_POLLING)
#define CAN0_RX_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN0_RX_CFG!!!"
#endif

#if (CAN0_BUSOFF_AUTOREC == STD_ON)
#define CAN0_BUSOFF_RECCFG  ((uint8)0x0U)
#elif (CAN0_BUSOFF_AUTOREC == STD_OFF)
#define CAN0_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN0_CLKSRC_CFG!!!"
#endif

#if (CAN0_CLKSRC_BUSCLK == STD_ON)
#define CAN0_CLKSRC_CFG  ((uint8)0x20U)
#elif (CAN0_CLKSRC_BUSCLK == STD_OFF)
#define CAN0_CLKSRC_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN0_CLKSRC_CFG!!!"
#endif

#if (CAN0_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN0_BCC_CFG     ((uint8)0x00U)
#elif (CAN0_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN0_BCC_CFG     (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN0_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM>=1) */

#if (CAN_USED_CONTROLLER_NUM >= 2)
#if (CAN1_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN1_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN1_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN1_BUSOFF_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN1_BUSOFF_CFG!!!"
#endif

#if (CAN1_TX_PROCESSING == CAN_INTERRUPT)
#define CAN1_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN1_TX_PROCESSING == CAN_POLLING)
#define CAN1_TX_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN1_TX_CFG!!!"
#endif

#if (CAN1_RX_PROCESSING == CAN_INTERRUPT)
#define CAN1_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN1_RX_PROCESSING == CAN_POLLING)
#define CAN1_RX_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN1_RX_CFG!!!"
#endif

#if (CAN1_BUSOFF_AUTOREC == STD_ON)
#define CAN1_BUSOFF_RECCFG  ((uint8)0x0U)
#elif (CAN1_BUSOFF_AUTOREC == STD_OFF)
#define CAN1_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN1_CLKSRC_CFG!!!"
#endif

#if (CAN1_CLKSRC_BUSCLK == STD_ON)
#define CAN1_CLKSRC_CFG  ((uint8)0x20U)
#elif (CAN1_CLKSRC_BUSCLK == STD_OFF)
#define CAN1_CLKSRC_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN1_CLKSRC_CFG!!!"
#endif

#if (CAN1_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN1_BCC_CFG     ((uint8)0x00U)
#elif (CAN1_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN1_BCC_CFG     (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN1_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM>=2) */

#if (CAN_USED_CONTROLLER_NUM >= 3)
#if (CAN2_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN2_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN2_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN2_BUSOFF_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN2_BUSOFF_CFG!!!"
#endif

#if (CAN2_TX_PROCESSING == CAN_INTERRUPT)
#define CAN2_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN2_TX_PROCESSING == CAN_POLLING)
#define CAN2_TX_INT_CFG  ((uint8)0x0U)
#else
#error "!!!ERROR FOR CAN2_TX_CFG!!!"
#endif

#if (CAN2_RX_PROCESSING == CAN_INTERRUPT)
#define CAN2_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN2_RX_PROCESSING == CAN_POLLING)
#define CAN2_RX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN2_RX_CFG!!!"
#endif

#if (CAN2_BUSOFF_AUTOREC == STD_ON)
#define CAN2_BUSOFF_RECCFG  (0x0U)
#elif (CAN2_BUSOFF_AUTOREC == STD_OFF)
#define CAN2_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN2_CLKSRC_CFG!!!"
#endif

#if (CAN2_CLKSRC_BUSCLK == STD_ON)
#define CAN2_CLKSRC_CFG  (0x20U)
#elif (CAN2_CLKSRC_BUSCLK == STD_OFF)
#define CAN2_CLKSRC_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN2_CLKSRC_CFG!!!"
#endif

#if (CAN2_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN2_BCC_CFG     (0x0U)
#elif (CAN2_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN2_BCC_CFG     (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN2_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM>=3) */

#if (CAN_USED_CONTROLLER_NUM >= 4)
#if (CAN3_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN3_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN3_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN3_BUSOFF_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN3_BUSOFF_CFG!!!"
#endif

#if (CAN3_TX_PROCESSING == CAN_INTERRUPT)
#define CAN3_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN3_TX_PROCESSING == CAN_POLLING)
#define CAN3_TX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN3_TX_CFG!!!"
#endif

#if (CAN3_RX_PROCESSING == CAN_INTERRUPT)
#define CAN3_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN3_RX_PROCESSING == CAN_POLLING)
#define CAN3_RX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN3_RX_CFG!!!"
#endif

#if (CAN3_BUSOFF_AUTOREC == STD_ON)
#define CAN3_BUSOFF_RECCFG  (0x0U)
#elif (CAN3_BUSOFF_AUTOREC == STD_OFF)
#define CAN3_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN3_CLKSRC_CFG!!!"
#endif

#if (CAN3_CLKSRC_BUSCLK == STD_ON)
#define CAN3_CLKSRC_CFG  (0x20U)
#elif (CAN3_CLKSRC_BUSCLK == STD_OFF)
#define CAN3_CLKSRC_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN3_CLKSRC_CFG!!!"
#endif

#if (CAN3_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN3_BCC_CFG     (0x0U)
#elif (CAN3_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN3_BCC_CFG     (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN3_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM>=4) */

#if (CAN_USED_CONTROLLER_NUM >= 5)
#if (CAN4_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN4_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN4_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN4_BUSOFF_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN4_BUSOFF_CFG!!!"
#endif

#if (CAN4_TX_PROCESSING == CAN_INTERRUPT)
#define CAN4_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN4_TX_PROCESSING == CAN_POLLING)
#define CAN4_TX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN4_TX_CFG!!!"
#endif

#if (CAN4_RX_PROCESSING == CAN_INTERRUPT)
#define CAN4_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN4_RX_PROCESSING == CAN_POLLING)
#define CAN4_RX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN4_RX_CFG!!!"
#endif

#if (CAN4_BUSOFF_AUTOREC == STD_ON)
#define CAN4_BUSOFF_RECCFG  (0x0U)
#elif (CAN4_BUSOFF_AUTOREC == STD_OFF)
#define CAN4_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN4_CLKSRC_CFG!!!"
#endif

#if (CAN4_CLKSRC_BUSCLK == STD_ON)
#define CAN4_CLKSRC_CFG  (0x20U)
#elif (CAN4_CLKSRC_BUSCLK == STD_OFF)
#define CAN4_CLKSRC_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN4_CLKSRC_CFG!!!"
#endif

#if (CAN4_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN4_BCC_CFG    (0x0U)
#elif (CAN4_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN4_BCC_CFG    (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN4_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM>=5) */

#if (CAN_USED_CONTROLLER_NUM == 6)
#if (CAN5_BUSOFF_PROCESSING == CAN_INTERRUPT)
#define CAN5_BUSOFF_INT_CFG  CAN_BUSOFF_INT_MASK
#elif (CAN5_BUSOFF_PROCESSING == CAN_POLLING)
#define CAN5_BUSOFF_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN5_BUSOFF_CFG!!!"
#endif

#if (CAN5_TX_PROCESSING == CAN_INTERRUPT)
#define CAN5_TX_INT_CFG  CAN_TX_INT_MASK
#elif (CAN5_TX_PROCESSING == CAN_POLLING)
#define CAN5_TX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN5_TX_CFG!!!"
#endif

#if (CAN5_RX_PROCESSING == CAN_INTERRUPT)
#define CAN5_RX_INT_CFG  CAN_RX_INT_MASK
#elif (CAN5_RX_PROCESSING == CAN_POLLING)
#define CAN5_RX_INT_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN5_RX_CFG!!!"
#endif

#if (CAN5_BUSOFF_AUTOREC == STD_ON)
#define CAN5_BUSOFF_RECCFG  (0x0U)
#elif (CAN5_BUSOFF_AUTOREC == STD_OFF)
#define CAN5_BUSOFF_RECCFG  CAN_BOFF_REC_MASK
#else
#error "!!!ERROR FOR CAN5_CLKSRC_CFG!!!"
#endif

#if (CAN5_CLKSRC_BUSCLK == STD_ON)
#define CAN5_CLKSRC_CFG  (0x20U)
#elif (CAN5_CLKSRC_BUSCLK == STD_OFF)
#define CAN5_CLKSRC_CFG  (0x0U)
#else
#error "!!!ERROR FOR CAN5_CLKSRC_CFG!!!"
#endif

#if (CAN5_BACKWARDS_COMPATIBILITY == STD_ON)
#define CAN5_BCC_CFG    (0x0U)
#elif (CAN5_BACKWARDS_COMPATIBILITY == STD_OFF)
#define CAN5_BCC_CFG    (CAN_BCC_MASK)
#else
#error "!!!ERROR FOR CAN5_BCC_CFG!!!"
#endif
#endif/* #if (CAN_USED_CONTROLLER_NUM==6) */

/*******************************************************************************
 *   Loop timer define
 *******************************************************************************/
#if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK)
#define CAN_LOOP_BEGIN(i)      ApplTimerBegin(i)
#define CAN_LOOP_TIMEOUT(i)    ApplTimerOutCheck(i)
#define CAN_LOOP_END(i)        ApplTimerEnd(i)
#else
#define CAN_LOOP_TIMEOUT(i)    CAN_NOT_OK
#endif/* #if (STD_ON == CAN_HARDWARE_TIMEOUT_CHECK) */

#define INIT_ENTER_TIMEOUT        (0x0U)
#define INIT_LEAVE_TIMEOUT        (0x1U)
#define SLEEP_ENTER_TIMEOUT       (0x2U)
#define SLEEP_LEAVE_TIMEOUT       (0x3U)

#endif/* _CAN_PL_H_*/
