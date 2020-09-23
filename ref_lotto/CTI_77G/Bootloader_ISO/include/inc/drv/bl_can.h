/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can module.
 *
 *  \file       bl_can.h
 *  \ingroup    driver_module
 *  \author     jun.li <jun.li3@hirain.com>
 *
 *  \version    1.0.0
 *  \date      20/08/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 20/08/2016 | jun.li      | N/A | BootDrv010001
 *****************************************************************************/
#ifndef _CAN_H_
#define _CAN_H_

#ifndef CAN_DRV_C
#define CAN_DRV_EXT extern
#else
#define CAN_DRV_EXT
#endif
#include "bl_can_if.h"

/*************************************************************************
*                           �궨��                                       *
**************************************************************************/

#define HARD_TYPE_VCU 0UL
#define HARD_TYPE_BCU 1UL

#define MCU_TYPE_S32R274  0UL
#define MCU_TYPE_MPC5746  1UL
#define MCU_TYPE_MPC5604  2UL
#define MCU_TYPE_MPC5606  3UL

/* board type define */
#define HARD_TYPE  HARD_TYPE_BCU

#define  MCU_TYPE  MCU_TYPE_S32R274

#define CAN_CONTROLLER_A                        0
#define CAN_CONTROLLER_B                        1
#define CAN_CONTROLLER_C                        2
#define CAN_CONTROLLER_D                        3

#define CAN_CONTROLLER_USED   CAN_CONTROLLER_A

#if(MCU_TYPE==MCU_TYPE_S32R274)
#if(CAN_CONTROLLER_USED==CAN_CONTROLLER_A)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFEC0000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_B)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFEC4000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_C)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFBEC0000UL)
#endif
#elif(MCU_TYPE==MCU_TYPE_MPC5746)
#if(CAN_CONTROLLER_USED==CAN_CONTROLLER_A)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFEB0000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_B)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFBEB4000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_C)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFEB8000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_D)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFBEBC000UL)
#endif
#elif(MCU_TYPE==MCU_TYPE_MPC5604)
#if(CAN_CONTROLLER_USED==CAN_CONTROLLER_A)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC0000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_B)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC4000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_C)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC8000UL)
#endif
#elif(MCU_TYPE==MCU_TYPE_MPC5606)
#if(CAN_CONTROLLER_USED==CAN_CONTROLLER_A)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC0000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_B)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC4000UL)
#elif(CAN_CONTROLLER_USED==CAN_CONTROLLER_C)
#define FLEXCAN(controller)     (*(volatile struct CAN_tag *) 0xFFFC8000UL)
#endif
#endif



#define CAN_CONTROLLER_TOTAL_MB                 0x64U

#define CAN_TX_MB_CODE_INACTIVE                 0x8u    /*0b1000U*/
#define CAN_TX_MB_CODE_ABORT                    0x9u    /*0b1001U*/
#define CAN_TX_MB_CODE_TRANS                    0xcu    /*0b1100U*/
#define CAN_TX_MB_CODE_TRANSED_REMOTE           0x4u    /*0b0100U*/
#define CAN_TX_MB_CODE_TRANS_RESPOND_REMOTE     0xau    /*0b1010U*/
#define CAN_TX_MB_CODE_TRANS_RESPONDING_REMOTE  0xeu    /*0b1110U*/

#define CAN_RX_MB_CODE_INACTIVE                 0x0    /*0b0000U*/
#define CAN_RX_MB_CODE_EMPTY                    0x4u    /*0b0100U*/
#define CAN_RX_MB_CODE_FULL                     0x2u    /*0b0010U*/
#define CAN_RX_MB_CODE_OVERRUN                  0x6u    /*0b0110U*/
#define CAN_RX_MB_CODE_BUSY_TO_EMPTY            0x3u    /*0b0011U*/
#define CAN_RX_MB_CODE_BUSY_TO_NOTEMP           0x7u    /*0b0111U*/

#define CAN_TX_OK                            0
#define CAN_TX_FAILED                        1
/*��������ķ�����Ķ���*/


/*--------------------------------MCR���--------------------------------------*/

#define ConfigMaxNumMB(CanMod,Num)          do{FLEXCAN((CanMod)).MCR.B.MAXMB = (Num);}while(0)

/*--------------------------------CR���--------------------------------------*/
#define ConfigPrescalerDiv(CanMod,Num)      do{FLEXCAN((CanMod)).CTRL1.B.PRESDIV = (Num);}while(0)
#define ConfigResyncWid(CanMod,Num)         do{FLEXCAN((CanMod)).CTRL1.B.RJW = (Num);}while(0)
#define ConfigPhaseSeg1(CanMod,Num)         do{FLEXCAN((CanMod)).CTRL1.B.PSEG1 = (Num);}while(0)
#define ConfigPhaseSeg2(CanMod,Num)         do{FLEXCAN((CanMod)).CTRL1.B.PSEG2 = (Num);}while(0)
#define ConfigSamples(CanMod,Num)           do{FLEXCAN((CanMod)).CTRL1.B.SMP = (Num);}while(0)
#define ConfigPropagationSeg(CanMod,Num)    do{FLEXCAN((CanMod)).CTRL1.B.PROPSEG = (Num);}while(0)

#define DisableBusOffIrq(CanMod)            do{FLEXCAN((CanMod)).CTRL1.B.BOFFMSK = 0;}while(0)
#define EnableBusOffIrq(CanMod)             do{FLEXCAN((CanMod)).CTRL1.B.BOFFMSK = 1;}while(0)

#define DisableErrIrq(CanMod)               do{FLEXCAN((CanMod)).CTRL1.B.ERRMSK = 0;}while(0)
#define EnableErrIrq(CanMod)                do{FLEXCAN((CanMod)).CTRL1.B.ERRMSK = 1;}while(0)

#define DisableLoopBack(CanMod)             do{FLEXCAN((CanMod)).CTRL1.B.LPB = 0;}while(0)
#define EnableLoopBack(CanMod)              do{FLEXCAN((CanMod)).CTRL1.B.LPB = 1;}while(0)

#define DisableBusOffRecovery(CanMod)       do{FLEXCAN((CanMod)).CTRL1.B.BOFFREC = 1;}while(0)
#define EnableBusOffRecovery(CanMod)        do{FLEXCAN((CanMod)).CTRL1.B.BOFFREC = 0;}while(0)

#define DisableTimerSync(CanMod)            do{FLEXCAN((CanMod)).CTRL1.B.TSYN = 0;}while(0)
#define EnableTimerSync(CanMod)             do{FLEXCAN((CanMod)).CTRL1.B.TSYN = 1;}while(0)

#define DisableLowestBufTFirst(CanMod)      do{FLEXCAN((CanMod)).CTRL1.B.LBUF = 0;}while(0)
#define EnableLowestBufTFirst(CanMod)       do{FLEXCAN((CanMod)).CTRL1.B.LBUF = 1;}while(0)

#define DisableListenOnly(CanMod)           do{FLEXCAN((CanMod)).CTRL1.B.LOM = 0;}while(0)
#define EnableListenOnly(CanMod)            do{FLEXCAN((CanMod)).CTRL1.B.LOM = 1;}while(0)

#define CAN_A_HALT                          0x1000UL
#define CAN_C_HALT                          0x4000UL


#define GetRxCode(MBx)                      (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.CODE)
#define GetRxIDStd(MBx)                     (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].ID.B.ID_STD)
#define GetRxDataAddress(MBx)               (&(FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].DATA.B[0]))
#define GetRxSRR(MBx)                       (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.SRR)
#define GetRxIDE(MBx)                       (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.IDE)
#define GetRxRTR(MBx)                       (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.RTR)
#define GetRxDLC(MBx)                       (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.DLC)
#define GetRxTimer(MBx)                     (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.TIMESTAMP)
#define GetCanTimer(CanMod)                 (FLEXCAN(CAN_CONTROLLER_USED).TIMER.R)

#define GetIntFlag(MBx)                     (((FLEXCAN(CAN_CONTROLLER_USED).IFLAG1.R)>>(MBx))&0x01)
#define ClearIntFlag(MBx)                   (FLEXCAN(CAN_CONTROLLER_USED).IFLAG1.R = (0x01<<(MBx)))

#define GetNotReady(MBx)                    (FLEXCAN(CAN_CONTROLLER_USED).MCR.B.NOTRDY)
#define GetTxCode(MBx)                      (FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.CODE)

#define CopyTxIDExt(IDExt,MBx)              do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].ID.R = ((IDExt)&0x1FFFFFFF);}while(0)
#define CopyTxIDStd(IDStd,MBx)              do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].ID.B.ID_STD = (IDStd);}while(0)
#define CopyTxDLC(DLC1,MBx)                  do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.DLC = (DLC1);}while(0)

#define TxStdIDIDE(MBx)                     do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.IDE = 0;}while(0)
#define TxExtIDIDE(MBx)                     do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.IDE = 1;}while(0)

#define TxStdIDSRR(MBx)                     do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.SRR = 0;}while(0)
#define TxExtIDSRR(MBx)                     do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.SRR = 1;}while(0)

#define TxDataIDRTR(MBx)                    do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.RTR = 0;}while(0)
#define TxRemoteIDRTR(MBx)                  do{FLEXCAN(CAN_CONTROLLER_USED).MB[(MBx)].CS.B.RTR = 1;}while(0)
/*************************************************************************
*                           ���ݽṹ                                     *
**************************************************************************/

/*************************************************************************
*                           ��������                                     *
**************************************************************************/
extern bl_u32_t g_dummy;

/*************************************************************************
*                           ��������                                     *
**************************************************************************/

/* Initialize CAN interface */
extern bl_Return_t Can_Init(void);
extern bl_Return_t Can_Deinit(void);
extern bl_Return_t Can_Read(bl_CanRxPdu_t *PduInfo);
extern bl_Return_t Can_Write(const bl_CanTxPdu_t *PduInfo);
extern bl_u8_t Can_CheckTxStatus(bl_u8_t handle);
/** \brief Check can controller busoff.*/
extern void Can_BusOff_Check(void);


#endif/* ifdef _CAN_DRIVER_H_ */
