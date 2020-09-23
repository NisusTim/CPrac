/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the watchdog module for MPC5744P.
 *
 *  \file       bl_watchdog.c
 *  \ingroup    driver_module
 *  \author     jun.li <jun.li3@hirain.com>
 *
 *  \version    1.0.0
 *  \date       16/08/2016
 *
 *  \par        Changelist
 *      Version    | Date       | Authors          | CR# | Descriptions
 *      --------   | ---------- | ---------------- | --- | -------------
 *      01.00.00   | 12/08/2016 | jun.li           | N/A | BootDrv010001
 *
 *****************************************************************************/
#include "bl_watchdog.h"
#include "S32R274.h"
#include "bl_typedefs.h "
#include "Typedefs.h"
#include "bl_can.h"

#define     WDG_TIMEOUT_VALUE  0x007A1200/* 16M internal RC,500ms */

#define     WDG_EN      0x01ul/* WDG enable bit*/
#define     WDG_FRZ     0x02ul/* wdg stop in debug mode*/
#define     WDG_STP     0x04ul/* wdg stop in stop mode*/
#define     WDG_WND   0x80ul/* window watchdog enable*/
#define     WDG_ITR     0x40ul/* wdg interrupt enable*/
#define     WDG_HLK     0x20ul/* hardware lock bit */
#define     WDG_SLK     0x10ul/* software lock bit */
#define     WDG_RIA     0x100ul/* Reset on Invalid Access */


static void Wdg_Start(void);

#if (RTE_FUN_EXTERNAL_WATCHDOG == BL_FUN_ON)
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_InitExt
*
* Description   : Init watchdog module.
*
* Inputs        :   None
*
* Outputs       :  None
*
* Limitations   : Timeout: n ms
*
************************************************************************************************
END_FUNCTION_HDR */
static void WDog_InitExt(void)
{

}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_FeedExt
*
* Description   : Init watchdog module.
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : Timeout: n ms
*
************************************************************************************************
END_FUNCTION_HDR */
static void WDog_FeedExt(void)
{
}

#endif/*RTE_FUN_EXTERNAL_WATCHDOG*/

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_Init
*
* Description   : Init watchdog module.
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : Timeout: n ms
*
************************************************************************************************
END_FUNCTION_HDR */
void FCCU_Init(void)
{
    /* Unlock configuration */    
    FCCU.TRANS_LOCK.B.TRANSKEY = 0xBC;    
    
    /* provide Config state key */    
    FCCU.CTRLK.R = 0x913756AF;    

    /* enter config state - OP1 */    
    FCCU.CTRL.R = 0x1;    

    /* Verify if state change was successful */    
    while (FCCU.CTRL.B.OPS != 0x3);    //operation status successful    

    /* Configure FCCU to react on NCF with short reset */
    FCCU.NCFS_CFG[0].B.NCFSC14 = 0x1;    

    /* Configure FCCU for ex_watchdog */
    FCCU.CFG.R = 0x01000000;
    FCCU.CFG.B.FOM = 0x02;


    //set up the NOMAL mode of FCCU    
    FCCU.CTRLK.R = 0x825A132B;        //key for OP2    
    FCCU.CTRL.R = 0x2;            //set the OP2 - set up FCCU into the NORMAL mode    
    while (FCCU.CTRL.B.OPS != 0x3);    //operational status successful
}
/**********************************************************************************************
* This function clear all FCCU_NCF_S0/1/2 bits by writing key to FCCU.NCFK.R register.
* And will store the updated FCCU_NCF_S0/1/2 bits into the parameter pu32Status
* Return 0 if all FCCU errors were cleared; otherwise return 1;
**********************************************************************************************/
void  FCCU_clear_faults(void)
{
    /* 1. Write the proper key into the FCCU_NCFK register */
    //Non-critical fault key = AB34_98FEh
    FCCU.NCFK.R = 0xAB3498FE;
    
    /* 2. Clear the status (flag) bit NCFSx => the opcode OP12 is automatically set into the FCCU_CTRL.OPR field */
    /* Read all NCFS registers to clear all faults.*/
    /* For details which faults can be cleared see Table 7-36. FCCU Non-Critical Faults Mapping in RM */
    FCCU.NCF_S[0].R = 0xFFFFFFFF;      // read FCCU.NCF_S0 register
    
    /* Verify if state change was successful */
    while (FCCU.CTRL.B.OPS != 0x3);   //operation status successful
    
    /* NCFS_1 register clear */
    FCCU.NCFK.R = 0xAB3498FE;      //Non-critical fault key = AB34_98FEh
    FCCU.NCF_S[1].R = 0xFFFFFFFF;      // clear FCCU.NCF_S1 register
    /* Verify if state change was successful */
    while (FCCU.CTRL.B.OPS != 0x3);   //operation status successful
    
    /* NCFS_2 register clear */
    FCCU.NCFK.R = 0xAB3498FE;      //Non-critical fault key = AB34_98FEh
    FCCU.NCF_S[2].R = 0xFFFFFFFF;      // clear FCCU.NCF_S2 register
    /* Verify if state change was successful */
    while (FCCU.CTRL.B.OPS != 0x3);   //operation status successful
}

static void Wdg_Start(void)
{
    SWT_0.SR.R = 0xC520;
    SWT_0.SR.R = 0xD928;/* Unlock Sequence */
    SWT_0.CR.R= (0xFF000000u|WDG_SLK|WDG_RIA|WDG_STP);/* init and lock */

//#if (RTE_FUN_EXTERNAL_WATCHDOG == BL_FUN_ON)
  //    WDog_InitExt();
//#endif

}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_Start
*
* Description   : start watchdog timer.
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : None
*
************************************************************************************************
END_FUNCTION_HDR */

void Wdg_Init(void)
{
    /*FCCU_clear_faults();
    FCCU_Init();*/

    Wdg_Start();

    SWT_0.SR.R = 0xC520;
    SWT_0.SR.R = 0xD928;/* Unlock Sequence */
    SWT_0.TO.R = WDG_TIMEOUT_VALUE;
    SWT_0.CR.B.WEN = 1;

    SWT_0.CR.B.SLK = 1;/* software lock*/
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_ResetMCU
*
* Description   : wait forever to reset the mcu
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : None
*
************************************************************************************************
END_FUNCTION_HDR */
void Wdg_FastReset(void)
{
    /* invalid unlock sequence*/
#if 0    
    SWT_0.SR.R = 0xA601;
    SWT_0.SR.R = 0xB422;

    while(1)
    {

    }
#endif

    MC_ME.MCTL.R = 0x00005AF0;
    MC_ME.MCTL.R = 0x0000A50F;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_DeInit
*
* Description   : DeInit watchdog module.
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : None
*
************************************************************************************************
END_FUNCTION_HDR */
void Wdg_Deinit(void)
{
    SWT_0.SR.R = 0xC520;
    SWT_0.SR.R = 0xD928;    /* Unlock Sequence */
    SWT_0.TO.R = 0x0005FCD0;    /* reset value*/
    SWT_0.CR.R = 0xFF00010A;  /* reset value */
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : WDog_Feed
*
* Description   : feed mcu watchdog
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : None
*
************************************************************************************************
END_FUNCTION_HDR */

void Wdg_Feed(void)
{
    SWT_0.SR.R = 0xA602;
    SWT_0.SR.R = 0xB480;
}

