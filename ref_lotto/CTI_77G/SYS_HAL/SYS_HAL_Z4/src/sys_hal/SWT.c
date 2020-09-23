/*
 * SWT.c
 *
 *  Created on: 2017/07/04
 *      Author: Bruce Chang
 */

#include "sys_shared.h"

#ifndef CTI_Z4_0
void save_stack_info(void);
extern void __SP_INIT(void);
stack_info_t __attribute__((section(".stack_info")))stkinfo_data;
#endif


/*******************************************************************************
Function Name : SWT0_Init
Engineer      : b21190
Date          : MAR-17-2015
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initialize SWT
Issues        : NONE
*******************************************************************************/
#if defined(CTI_Z4_0)
void SWT0_Init(void)
{
    /* Provide a Key to unlock SWT configuraiton registers */
    SWT_0.SR.R = 0xC520;
    SWT_0.SR.R = 0xD928;

    /* Wait for self-lock bit */
    while (SWT_0.CR.B.SLK == 0x1);
    /* Enable SWT_0 */
    SWT_0.CR.B.WEN = 0x1;
    /* Set SWT timeout */
    //SWT_0.CR.R = 0xFF00010A;
    SWT_0.TO.R = 0x008FFFFF;
    SWT_0.CR.R = 0xFF00010B;
}

#elif defined(CTI_Z7_0)
/*******************************************************************************
Function Name : SWT1_Init
Engineer      : b21190
Date          : MAR-17-2015
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initialize SWT
Issues        : NONE
*******************************************************************************/
void SWT1_Init(void)
{
    /* Provide a Key to unlock SWT configuraiton registers */
    SWT_1.SR.R = 0xC520;
    SWT_1.SR.R = 0xD928;

    /* register interrupt handler */
    INTC.PSR[33].R = Interrput_Core_Selected| 0x0006;
    /* Wait for solf-lock bit */
    while (SWT_1.CR.B.SLK == 0x1);
    /* Enable SWT_1 */
    SWT_1.CR.B.WEN = 0x1;
    /* Set SWT timeout */
    SWT_1.TO.R = 0x007FFFFF;
    SWT_1.CR.R = 0xFF00010B;

    stkinfo_data.z70_start_addr = (uint32_t)__SP_INIT;
    stkinfo_data.z70_stack_head = (uint32_t)__builtin_frame_address(1);

    SWT_1.CR.B.ITR = 0x1;
}

#elif defined(CTI_Z7_1)
/*******************************************************************************
Function Name : SWT1_Init
Engineer      : b21190
Date          : MAR-17-2015
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initialize SWT
Issues        : NONE
*******************************************************************************/
void SWT2_Init(void)
{
    /* Provide a Key to unlock SWT configuraiton registers */
    SWT_2.SR.R = 0xC520;
    SWT_2.SR.R = 0xD928;

    /* register interrupt handler */
    INTC.PSR[34].R = Interrput_Core_Selected| 0x0006;
    /* Wait for solf-lock bit */
    while (SWT_2.CR.B.SLK == 0x1);
    /* Enable SWT_2 */
    SWT_2.CR.B.WEN = 0x1;
    /* Set SWT timeout */
    SWT_2.TO.R = 0x001FFFFF;
    SWT_2.CR.R = 0xFF00010B;

    stkinfo_data.z71_start_addr = (uint32_t)__SP_INIT;
    stkinfo_data.z71_stack_head = (uint32_t)__builtin_frame_address(1);

    SWT_2.CR.B.ITR = 0x1;
}
#endif
/*******************************************************************************
Function Name : clear_watchdog_counter
Engineer      : Bruce Chang
Date          : 06-28-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : check to reset the watch-dog time out counter
Issues        : NONE
*******************************************************************************/
#if defined(CTI_Z4_0)
void clear_SWT0_counter(void)
{
	SWT_0.SR.R = 0xA602;
	SWT_0.SR.R = 0xB480;
}
#elif defined(CTI_Z7_0)
void clear_SWT1_counter(void)
{
	SWT_1.SR.R = 0xA602;
	SWT_1.SR.R = 0xB480;
}
#elif defined(CTI_Z7_1)
void clear_SWT2_counter(void)
{
	SWT_2.SR.R = 0xA602;
	SWT_2.SR.R = 0xB480;
}
#endif

#if defined(CTI_Z7_0)
void SWT1_Timeout_ISR(void)
{
	/* Clear timeout interrupt flag */
	SWT_1.IR.B.TIF = 0x1;
	save_stack_info();
}

void save_stack_info(void)
{
	/* Write stack information into shared memory */
	stkinfo_data.z70_start_addr  = (uint32_t)__SP_INIT;
	stkinfo_data.z70_stack_head = (uint32_t)__builtin_frame_address(1);
	stkinfo_data.z70_sync = 1;  //set sync success flag
}
#elif defined(CTI_Z7_1)
void SWT2_Timeout_ISR(void)
{
	/* Clear timeout interrupt flag */
	SWT_2.IR.B.TIF = 0x1;
	save_stack_info();
}

void save_stack_info(void)
{
	/* Write stack information into shared memory */
	stkinfo_data.z71_start_addr  = (uint32_t)__SP_INIT;
	stkinfo_data.z71_stack_head = (uint32_t)__builtin_frame_address(1);
	stkinfo_data.z71_sync = 1;  //set sync success flag
}
#endif

void reset_system(void)
{
    MC_ME.MCTL.R = 0x00005AF0;      //Target mode set to RESET mode (0000), Key: 5AF0
    MC_ME.MCTL.R = 0x0000A50F;      //Target mode set to RESET mode (0000), Key: A50F
}

