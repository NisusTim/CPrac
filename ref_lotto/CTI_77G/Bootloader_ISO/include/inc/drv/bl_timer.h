/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the timer module for mpc5744p.
 *
 *  \file       bl_timer.h
 *  \ingroup    driver_module
 *  \author     jun.li <jun.li3@hirain.com>
 *
 *  \version    1.0.0
 *  \date       29/06/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 12/08/2016 | jun.li           | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef TIMER_H
#define TIMER_H
#include "bl_typedefs.h"

/* global variable declaration */
#define STM_CMP                             /*0x7d00*/(0x000186A0ul>>0)  /* 1ms @ 50MHz */
#define STM_CNT_CLEAR                       (0x00000000ul)
/*function declaration */
extern void Tim_Init(void);  
extern void Tim_Deinit(void);
extern bl_Return_t Tim_IsTimeout(void);


#endif/* TIMER_H */




