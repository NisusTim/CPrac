/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the timer module for MPC5744P.
 *
 *  \file       bl_timer.c
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
#include "bl_timer.h"
#include "S32R274.h"

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
 
 /* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : TIM_Init
*
* Description   : Init Timer Module
*
* Inputs        : none
*
* Outputs       : none
* 
* Limitations   : Only for HiBoot
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Tim_Init(void)
{    
	PIT_0.MCR.B.MDIS = 0;               //Enable PIT_0 timers
	PIT_0.TIMER[0].LDVAL.R = 60000-1;   // setup timer 0 for 1sec period	//1000 ticks per second
	PIT_0.TIMER[0].TCTRL.B.TIE = 1;     // Timer interrupt enable
	PIT_0.TIMER[0].TCTRL.B.TEN = 1;     // start Timer
	PIT_0.TIMER[0].TCTRL.B.TEN = 1;

    // Start STM in free running
    STM_0.CHANNEL[0].CCR.R = 0x1; 	        // Channel enable CH0
    STM_0.CNT.R = 0;            			// Clear counter.
    STM_0.CR.R = 0x00000001;		        // Divide system clock by 1 & enable timer

	//test======Start=======>>
	PIT_0.MCR.B.FRZ = 1;               //
}


/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : TIM_DeInit
*
* Description   : Deinit all Timer related registers if necessary
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : 
*                 
************************************************************************************************
END_FUNCTION_HDR */

 void Tim_Deinit(void)
{    

	PIT_0.MCR.B.MDIS = 0;               //Enable PIT_0 timers
	PIT_0.TIMER[0].LDVAL.R = 0;   // setup timer 0 for 1sec period
	PIT_0.TIMER[0].TCTRL.B.TIE = 0;     // Timer interrupt enable
	PIT_0.TIMER[0].TCTRL.B.TEN = 0;     // start Timer

	PIT_0.MCR.B.FRZ = 0;
} 
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : TIM_IsTimeout
*
* Description   : Check timer value is achived or not.
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : 
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t Tim_IsTimeout(void)
{
    bl_Return_t timeout;


    timeout = BL_ERR_NOT_OK;
    if(1 == PIT_0.TIMER[0].TFLG.B.TIF)
    {
    	timeout = BL_ERR_OK;
        PIT_0.TIMER[0].TCTRL.B.TEN = 1;     // stop PIT_0 Timer
        PIT_0.TIMER[0].TFLG.B.TIF = 1;     // Clear PIT_0 interrupt flag
        PIT_0.TIMER[0].TCTRL.B.TEN = 1;     // sart PIT_0 Timer
    }
    return timeout;
}









