/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can module.
 *
 *  \file       bl_can.c
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
#include "S32R274.h"
#include "bl_typedefs.h"
#include "bl_can_if.h"
#include "bl_can_if_funcfg.h"
#include "bl_can_if_cfg.h"
#include "bl_can_type.h"
#include "bl_can.h"
#include "bl_system.h"


/****************************************************************************
* macro define*
*****************************************************************************/

#define HARDWARE_FLEXCAN       /* MCU with CAN controller */

/* #define CAN_DISABLE_EXTENDED_ID */
#define CAN_DISABLE_REMOTE_FRAME

#define CAN_CONTROLLER_MAXMB                    0x3UL

#define CAN_BTR_125K                            0UL
#define CAN_BTR_250K                            1UL
#define CAN_BTR_500K                            2UL
#define CAN_BTR_1M                              3UL

/* bit rate=f(canclk)/((presdiv+1)*(1+propseg+pseg1+2+pseg2+1)) */
#define CAN_COTROLLER_BTR                       CAN_BTR_500K

#if(SYS_OSC_CLOCK_FREQ == 8000)
#if (CAN_COTROLLER_BTR == CAN_BTR_125K)
#define CAN_CONTROLLER_PRESDIV                    0x03UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x04UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x05UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_250K)
#define CAN_CONTROLLER_PRESDIV                    0x01UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x07UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x02UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_500K)
#define CAN_CONTROLLER_PRESDIV                    0x00UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x05UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x04UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_1M)
#define CAN_CONTROLLER_PRESDIV                    0x00UL
#define CAN_CONTROLLER_RJW                        0x01UL
#define CAN_CONTROLLER_PSEG1                      0x02UL
#define CAN_CONTROLLER_PSEG2                      0x01UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x01UL
#else
#error "This baudrate is not supportted!"
#endif
#elif(SYS_OSC_CLOCK_FREQ == 12000)
#if (CAN_COTROLLER_BTR == CAN_BTR_125K)
#define CAN_CONTROLLER_PRESDIV                    0x07UL
#define CAN_CONTROLLER_RJW                        0x00UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x02UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_250K)
#define CAN_CONTROLLER_PRESDIV                    0x03UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x02UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_500K)
#define CAN_CONTROLLER_PRESDIV                    0x01UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x02UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_1M)
#define CAN_CONTROLLER_PRESDIV                    0x00UL
#define CAN_CONTROLLER_RJW                        0x00UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x02UL
#else
#error "This baudrate is not supportted!"
#endif
#elif(SYS_OSC_CLOCK_FREQ == 16000)
#if (CAN_COTROLLER_BTR == CAN_BTR_125K)
#define CAN_CONTROLLER_PRESDIV                    0x07UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_250K)
#define CAN_CONTROLLER_PRESDIV                    0x03UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_500K)
#define CAN_CONTROLLER_PRESDIV                    0x01UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_1M)
#define CAN_CONTROLLER_PRESDIV                    0x00UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x03UL
#define CAN_CONTROLLER_PSEG2                      0x03UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#else
#error "This baudrate is not supportted!"
#endif
#elif(SYS_OSC_CLOCK_FREQ == 20000)
#if (CAN_COTROLLER_BTR == CAN_BTR_125K)
#define CAN_CONTROLLER_PRESDIV                    0x07UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x04UL
#define CAN_CONTROLLER_PSEG2                      0x06UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_250K)
#define CAN_CONTROLLER_PRESDIV                    0x04UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x04UL
#define CAN_CONTROLLER_PSEG2                      0x04UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x04UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_500K)
#define CAN_CONTROLLER_PRESDIV                    0x01UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x04UL
#define CAN_CONTROLLER_PSEG2                      0x06UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_1M)
#define CAN_CONTROLLER_PRESDIV                    0x00UL
#define CAN_CONTROLLER_RJW                        0x03UL
#define CAN_CONTROLLER_PSEG1                      0x04UL
#define CAN_CONTROLLER_PSEG2                      0x06UL
#define CAN_CONTROLLER_SMP                        0x00UL
#define CAN_CONTROLLER_PROPSEG                    0x06UL
#else
#error "This baudrate is not supportted!"
#endif
#elif(SYS_OSC_CLOCK_FREQ == 40000)
#if (CAN_COTROLLER_BTR == CAN_BTR_125K)
#define CAN_CONTROLLER_PRESDIV                    0x0FUL
#define CAN_CONTROLLER_RJW                           0x03UL
#define CAN_CONTROLLER_PSEG1                       0x04UL
#define CAN_CONTROLLER_PSEG2                       0x06UL
#define CAN_CONTROLLER_SMP                           0x00UL
#define CAN_CONTROLLER_PROPSEG                   0x06UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_250K)
#define CAN_CONTROLLER_PRESDIV                    0x09UL
#define CAN_CONTROLLER_RJW                           0x03UL
#define CAN_CONTROLLER_PSEG1                       0x04UL
#define CAN_CONTROLLER_PSEG2                       0x04UL
#define CAN_CONTROLLER_SMP                           0x00UL
#define CAN_CONTROLLER_PROPSEG                   0x04UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_500K)
#define CAN_CONTROLLER_PRESDIV                    0x03UL
#define CAN_CONTROLLER_RJW                           0x03UL
#define CAN_CONTROLLER_PSEG1                       0x06UL
#define CAN_CONTROLLER_PSEG2                       0x03UL
#define CAN_CONTROLLER_SMP                           0x00UL
#define CAN_CONTROLLER_PROPSEG                   0x07UL
#elif (CAN_COTROLLER_BTR == CAN_BTR_1M)
#define CAN_CONTROLLER_PRESDIV                    0x01UL
#define CAN_CONTROLLER_RJW                           0x03UL
#define CAN_CONTROLLER_PSEG1                       0x04UL
#define CAN_CONTROLLER_PSEG2                       0x06UL
#define CAN_CONTROLLER_SMP                           0x00UL
#define CAN_CONTROLLER_PROPSEG                   0x06UL
#else
#error "This baudrate is not supportted!"
#endif
#else
#error "The osc clock is error."
#endif


#define CAN_TX_MB0                  0x0U
#define CAN_RX_MB0                  0x1U
#define CAN_RX_MB1                  0x2U

#define CAN_RX_ID0                  0x01
#define CAN_RX_ID1                  0x02

/* define types of Can ID*/
#define CAN_STANDARD                (0x00u)
#define CAN_EXTERNED                (0x01u)

static CanInitType CanInitStatus = CanStatus_UnInit;
bl_u32_t g_dummy;
/****************************************************************************
* FUNCTION :    CANMemCpy
*
* DESCRIPTION : This function is used to copy data
* CALLS :
* INPUTS :      --dest: destination address
*               --source: source address
*               --size: the number of data to copy
* OUTPUTS       none
*****************************************************************************/
void CANMemCpy(vuint8_t* dest, vuint8_t* source, uint32_t size)
{

    volatile uint8_t* sd  = dest;
    volatile uint8_t* ss  = source;

    while (size > 0)
    {
        *sd++ = *ss++;
        size--;
    }

}

/* BEGIN_FUNCTION_HDR
***********************************************************************************************
CAN223:
Service name:         Can_Init
Syntax:                   uint8 Can_Init( void )
Service ID[hex]:      0x00
Sync/Async:            Synchronous
Reentrancy:             Non Reentrant
Parameters (in):       None
Parameters (inout):   None
Parameters (out):     None
Return value:           None
Description:             This function initializes the module.
***********************************************************************************************
 END_FUNCTION_HDR*/

bl_Return_t Can_Init(void)
{
    bl_Return_t retval = BL_ERR_OK;
    vuint16_t i = 0;
    vuint16_t j = 0;


    if(CanStatus_UnInit == CanInitStatus)
   {

          /*----step 1 Put the Flexcan2 into freeze mode-----------------------------*/
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.MDIS = 0;
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZ = 1;
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.HALT = 1;
        while(FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZACK!= 1)
        {
     }

        /*----step 2    Initialize MCR on FREEZE MODE------------------------------*/

        ConfigMaxNumMB(CAN_CONTROLLER_USED,(CAN_CONTROLLER_MAXMB-1));

        /*----step 3  Initialize MCR on FREEZE MODE ---------------------------------
       CAN Engine Clock Source select oscillator clock,CLKSRC value is reset value*/

        ConfigPropagationSeg(CAN_CONTROLLER_USED,CAN_CONTROLLER_PROPSEG);
        ConfigPhaseSeg1(CAN_CONTROLLER_USED,CAN_CONTROLLER_PSEG1);
        ConfigPhaseSeg2(CAN_CONTROLLER_USED,CAN_CONTROLLER_PSEG2);
        ConfigResyncWid(CAN_CONTROLLER_USED,CAN_CONTROLLER_RJW);
        ConfigPrescalerDiv(CAN_CONTROLLER_USED,CAN_CONTROLLER_PRESDIV);
        ConfigSamples(CAN_CONTROLLER_USED,CAN_CONTROLLER_SMP);
        DisableLowestBufTFirst(CAN_CONTROLLER_USED);

        DisableLoopBack(CAN_CONTROLLER_USED);
        EnableBusOffRecovery(CAN_CONTROLLER_USED);
        DisableTimerSync(CAN_CONTROLLER_USED);
        DisableListenOnly(CAN_CONTROLLER_USED);

    	/*Self reception disabled*/
		CAN_0.MCR.B.SRXDIS = 1;

		/*Bus off interrupt enable*/
		CAN_0.CTRL1.B.BOFFMSK = 1;

		/*Automatic recovering from Bus Off state disabled*/
		CAN_0.CTRL1.B.BOFFREC = 1;

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

        /*----step 4 Initialize MBs on FREEZE MODE---------------------------------------*/
        for (i = 0; i < CAN_CONTROLLER_MAXMB; i++)
        {
                /* Deactivate all buffers */
             FLEXCAN(CAN_CONTROLLER_USED).MB[i].CS.R= 0x00000000U;

             FLEXCAN(CAN_CONTROLLER_USED).MB[i].ID.R= 0x00000000U;

          for (j = 0; j < 8; j++)
          {
            FLEXCAN(CAN_CONTROLLER_USED).MB[i].DATA.B[j]= 0x00U;
          }

        }

        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_TX_MB0].CS.B.CODE = CAN_TX_MB_CODE_INACTIVE;


        #if 1
        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.CODE = CAN_RX_MB_CODE_INACTIVE;

         if(g_CanIfRxPduCfg.rxList[0].id  <= 0x7ffu) /* standard ID */
         {
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].ID.B.ID_STD = g_CanIfRxPduCfg.rxList[0].id;
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.IDE = 0;
         }
         else /* extened ID */
         {
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].ID.R = g_CanIfRxPduCfg.rxList[0].id;
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.IDE = 1;
         }

        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.CODE = CAN_RX_MB_CODE_EMPTY;
        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.CODE = CAN_RX_MB_CODE_INACTIVE;

         if(g_CanIfRxPduCfg.rxList[1].id <= 0x7ffu)  /* standard ID */
         {
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].ID.B.ID_STD = g_CanIfRxPduCfg.rxList[1].id;
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.IDE = 0;

         }
         else /* extened ID */
         {
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].ID.R = g_CanIfRxPduCfg.rxList[1].id;//CAN_RX_ID1;
             FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.IDE = 1;
         }

         #endif

        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.CODE = CAN_RX_MB_CODE_EMPTY;


        /*----step 5  Initialize Rx  Mask Registers on FREEZE MODE----------------
        The mcu support individual RX Mask Register,*/

        FLEXCAN(CAN_CONTROLLER_USED).RXMGMASK.R = 0x1FFFFFFFUL;
        FLEXCAN(CAN_CONTROLLER_USED).RX14MASK.R = 0x1FFFFFFFUL;
        FLEXCAN(CAN_CONTROLLER_USED).RX15MASK.R = 0x1FFFFFFFUL;


        /*----step 5 ��FREEZE MODE��set required interrupt mask bit(IMASK/CR/MCR)---
                              disable all interrupts*/

        FLEXCAN(CAN_CONTROLLER_USED).IMASK1.R = 0x0UL;
        DisableBusOffIrq(CAN_CONTROLLER_USED);
        DisableErrIrq(CAN_CONTROLLER_USED);

        /*----step 6 Negate the HALT BIT,enter NORMAL MODE-----------------*/
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.SRXDIS = 1;
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.HALT = 0;
        FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZ = 0;
        while(FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZACK!= 0)
        {
     }
        /* configure CAN0TX and CAN0RX pin functions */
//        SIUL2.MSCR[16].B.SSS = 1;     /* Pad PB0: Source signal is CAN0_TX  */
//        SIUL2.MSCR[16].B.OBE = 1;     /* Pad PB0: Output Buffer Enable */
//        SIUL2.MSCR[16].B.SRC = 3;     /* Pad PB0: Maximum slew rate */
//        SIUL2.MSCR[17].B.IBE = 1;      /* Pad PB1: Enable pad for input - CAN0_RX */
//        SIUL2.IMCR[32].B.SSS = 2;      /* CAN0_RX: connected to pad PB1 */

    	/*Initial CAN 0 I/O Settings*/
    	SIUL2.MSCR[16].B.SSS = 1;    /* Pad L15: Source signal is CAN0_TX */
    	SIUL2.MSCR[16].B.OBE = 1;    /* Pad L15: Output Buffer Enable */
    	SIUL2.MSCR[16].B.SRC = 3;    /* Pad L15: Maximum slew rate */

    	SIUL2.MSCR[15].B.IBE = 1;    /* Pad L16: Enable pad for input - CAN0_RXD */
    	SIUL2.IMCR[0].B.SSS = 1;     /* Pad L16: Source signal is CAN0_RXD */

    	/*Initial CAN 2 I/O Settings*/
    	SIUL2.MSCR[0].B.SSS = 0;    /* Pad A11: Source signal is DSP_CAN2_STB,GPO*/
    	SIUL2.MSCR[0].B.OBE = 1;    /* Pad A11: Output Buffer Enable */
    	SIUL2.MSCR[0].B.SRC = 3;    /* Pad A11: Slew Rate Control => Full drive strength without slew rate control */
    	SIUL2.GPDO[0].B.PDO_4n = 0;	/* Set CAN2 Transceiver to Normal mode ( output low ) */

        CanInitStatus = CanStatus_Init;

    }


    return retval;

}

bl_Return_t Can_Deinit(void)
{
    bl_Return_t ret;

    CanInitStatus = CanStatus_UnInit;

    FLEXCAN(CAN_CONTROLLER_USED).MCR.B.MDIS = 0;
    FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZ = 1;
    FLEXCAN(CAN_CONTROLLER_USED).MCR.B.HALT = 1;
    while(FLEXCAN(CAN_CONTROLLER_USED).MCR.B.FRZACK!= 1)
    {
    }
    FLEXCAN(CAN_CONTROLLER_USED).CTRL1.R  = 0;
    FLEXCAN(CAN_CONTROLLER_USED).ECR.R  = 0;
    FLEXCAN(CAN_CONTROLLER_USED).MCR.B.MDIS = 1;

    ret = BL_ERR_OK;

    return ret;
}

/* BEGIN_FUNCTION_HDR
***********************************************************************************************
Service name:    Can_Write
Syntax:              Can_ReturnType Can_Write(
                         const Can_PduType* PduInfo
                        )
Sync/Async:        Synchronous
Reentrancy:         Reentrant (thread-safe)
Parameters (in):    PduInfo:  Pointer to SDU user memory, DLC and Identifier.
Parameters (inout): None
Parameters (out):   None
Return value:         Can_ReturnType  CAN_OK: Write command has been accepted
                                                       CAN_NOT_OK: development error occurred
                                                       CAN_BUSY: No TX hardware buffer available or pre-emptive call
                                              of Can_Write that can't be implemented re-entrant
Description:        --
***********************************************************************************************
 END_FUNCTION_HDR*/
bl_Return_t Can_Write(const bl_CanTxPdu_t* PduInfo)
{
    bl_Return_t ret = BL_ERR_OK;

    if(1==GetNotReady(CAN_CONTROLLER_USED))
    {
        ret = BL_ERR_NOT_OK;
    }
    else if(CAN_TX_MB_CODE_INACTIVE != GetTxCode(CAN_TX_MB0))
    {
        ret= BL_ERR_NOT_OK;
    }
    else
    {
        /*----step 2 Write the ID word--------------------------------------------------*/

        if(g_CanIfTxPduCfg.txList[0].id <= 0x7ffu) /* standard ID */
        {
            CopyTxIDStd(PduInfo->canId,CAN_TX_MB0);
        }
        else /* extened ID */
        {
            CopyTxIDExt(PduInfo->canId,CAN_TX_MB0);
        }

        /*----step 3 Write the data bytes-----------------------------------------------*/

        CANMemCpy((&(FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_TX_MB0].DATA.B[0]))
                , (volatile unsigned char *)PduInfo->frame
                , 8);
        /*----step 4 Write the length----------------------------------------------------*/

        CopyTxDLC((PduInfo->dlc),CAN_TX_MB0);
        /*----step 5 Write the control fields of the control and Status word-------------*/

        if(g_CanIfTxPduCfg.txList[0].id <= 0x7ffu) /* standard ID */
        {
            TxStdIDIDE(CAN_TX_MB0);
            TxStdIDSRR(CAN_TX_MB0);
        }
        else
        {
            TxExtIDIDE(CAN_TX_MB0);
            TxExtIDSRR(CAN_TX_MB0);
        }

        #ifdef CAN_DISABLE_REMOTE_FRAME
        TxDataIDRTR(CAN_TX_MB0);
        #endif /*ifdef CAN_DISABLE_REMOTE_FRAME*/

        /*----step 6 Write the CODE fields of the control and Status word,Active the MB---*/
        FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_TX_MB0].CS.B.CODE = CAN_TX_MB_CODE_TRANS;

    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
***********************************************************************************************
Service name:       Can_MainFunction_Read
Syntax:             void Can_MainFunction_Read(
                                               void
                                              )
Timing:             FIXED_CYCLIC
Description:        This function performs the polling of RX indications when
                    CAN_RX_PROCESSING is set to POLLING.
***********************************************************************************************
 END_FUNCTION_HDR*/

bl_Return_t Can_Read(bl_CanRxPdu_t *PduInfo)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_u32_t tempCanID;

    if (1 == GetIntFlag(CAN_RX_MB0))
    {
        if(((FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.CODE ==CAN_RX_MB_CODE_FULL)
            ||(FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].CS.B.CODE==CAN_RX_MB_CODE_OVERRUN)))
        {
            ClearIntFlag(CAN_RX_MB0);

            tempCanID = (FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB0].ID.R)&0x1FFFFFFF;
            if(g_CanIfRxPduCfg.rxList[0].type == CAN_STANDARD)
            {
                PduInfo->canId = tempCanID>>18U;
            }
            else
            {
                PduInfo->canId = tempCanID;
            }
            PduInfo->dlc = GetRxDLC(CAN_RX_MB0);
            PduInfo->handle = 0U;
            CANMemCpy(PduInfo->frame, GetRxDataAddress(CAN_RX_MB0), 8);

            ret = BL_ERR_OK;
        }
        g_dummy = GetCanTimer(CAN_CONTROLLER_USED);
    }
    if (1 == GetIntFlag(CAN_RX_MB1))
    {
        if(((FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.CODE ==CAN_RX_MB_CODE_FULL)
            ||(FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].CS.B.CODE==CAN_RX_MB_CODE_OVERRUN)))
        {
            ClearIntFlag(CAN_RX_MB1);

            tempCanID = (FLEXCAN(CAN_CONTROLLER_USED).MB[CAN_RX_MB1].ID.R)&0x1FFFFFFF;
            if(g_CanIfRxPduCfg.rxList[0].type == CAN_STANDARD)
            {
                PduInfo->canId = tempCanID>>18U;
            }
            else
            {
                PduInfo->canId = tempCanID;
            }

            PduInfo->dlc = GetRxDLC(CAN_RX_MB1);
            PduInfo->handle = 0U;
            CANMemCpy(PduInfo->frame, GetRxDataAddress(CAN_RX_MB1), 8);

            ret = BL_ERR_OK;
        }
        g_dummy = GetCanTimer(CAN_CONTROLLER_USED);
    }

    return ret;
}
/**************************************************************************//**
 *
 *  \details Check can transmit status.
 *
 *  \param[in] handle  - the index of a frame pdu list.
 *
 *  \return If the can message is transmited successfully return
 *          BL_ERR_OK. otherwise return BL_ERR_CONTOLLER_NOT_BUSY.
 *
 *  \retval BL_ERR_OK                 - can driver is initialized successfully.
 *  \retval BL_ERR_CONTOLLER_NOT_BUSY - can driver is not busy.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_u8_t Can_CheckTxStatus(bl_u8_t handle)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if(1 == GetIntFlag(CAN_TX_MB0))
    {
        ret = BL_ERR_OK;
        ClearIntFlag(CAN_TX_MB0);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check can busoff.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Can_BusOff_Check(void)
{

}



