/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file to configurate the process driver
 *              module.
 *
 *  \file       bl_process_driver_cfg.c
 *  \ingroup    process_driver_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      04.00.00 | 12/03/2012 | mingqing.tang    | N/A | Boot040001
 *      04.03.00 | 22/03/2012 | mingqing.tang    | N/A | Boot040004
 *      04.07.00 | 18/04/2012 | mingqing.tang    | N/A | Boot040008
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_process_driver_cfg.h"
#include "bl_proc_passive_schedule.h"
#include "bl_adpt_uds_platform.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1257,1533,3211 EOF*/
/*
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1533:The object is referenced in only one translation unit.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
/**************************************************************************//**
 *  \details The process driver info.
 *****************************************************************************/
static const bl_ProcessDriver_t gs_ProcessDriver[PROC_NUMBER_OF_DRIVER] =
{
    {
        PROC_DRIVER_0_TYPE, PROC_DRIVER_0_INDEX, PROC_DRIVER_0_ADAPTER,
        PROC_DRIVER_0_SCHEDULER
    },
};

/*****************************************************************************
 *  External Variable Definitions
 *****************************************************************************/
/**************************************************************************//**
 *  \details The process driver list, including all process driver info.
 *****************************************************************************/
const bl_ProcessDriverList_t g_ProcessDriverList =
{
    PROC_NUMBER_OF_DRIVER, gs_ProcessDriver,
};


