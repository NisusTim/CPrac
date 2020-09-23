/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the watchdog module for MPC5744P.
 *
 *  \file       bl_watchdog.h
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

#ifndef COP_H
#define COP_H

#include "bl_rte_funcfg.h"
#include "Typedefs.h"

#if (RTE_FUN_EXTERNAL_WATCHDOG == BL_FUN_ON)
#define BOARD_TYPE_VCU 0UL
#define BOARD_TYPE_BMS 1UL

/* board type define */
#define BOARD_TYPE  BOARD_TYPE_VCU
#endif/*RTE_FUN_EXTERNAL_WATCHDOG*/

/*Function declaration */
extern void FCCU_Init(void);
extern void FCCU_clear_faults(void);

extern void Wdg_Init(void);
extern void Wdg_FastReset(void);
extern void Wdg_Deinit(void);
extern void Wdg_Feed(void);
#endif




