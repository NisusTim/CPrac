/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the data of the data manager
 *              module.
 *
 *  \file       bl_data_cfg.h
 *  \ingroup    data_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      04.00.00 | 06/03/2013 | xin.shang        | N/A | Boot040001
 *      04.02.00 | 11/03/2013 | xin.shang        | N/A | Boot040003
 *      04.03.00 | 11/03/2013 | xin.shang        | N/A | Boot040004
 *      04.11.00 | 13/03/2013 | xin.shang        | N/A | Boot040012
 *      04.13.00 | 15/03/2013 | xin.shang        | N/A | Boot040014
 *      04.14.00 | 20/03/2013 | xin.shang        | N/A | Boot040015
 *      04.21.00 | 21/03/2013 | xin.shang        | N/A | Boot040022
 *      04.31.00 | 04/04/2013 | xin.shang        | N/A | Boot040032
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_DATA_CFG_H_
#define _BL_DATA_CFG_H_
#include "bl_data.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/*the memory configurations*/
#define DM_NUMBER_OF_MANAGED_DATA   (8)

/*reprogram requirement flag*/
#define DM_DATA_0_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_0_MEMID             (2)
#define DM_DATA_0_LOCAL_ADDR        (0x00808000UL)
#define DM_DATA_0_SIZE              (4UL)
#define DM_DATA_0_DDP               (&gs_defaultDataList[0])

/*reset requirement flag*/
#define DM_DATA_1_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_1_MEMID             (0)
#define DM_DATA_1_LOCAL_ADDR        (0x00003FFCUL)
#define DM_DATA_1_SIZE              (4UL)
#define DM_DATA_1_DDP               (&gs_defaultDataList[4])

/*application valid flag*/
#define DM_DATA_2_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_2_MEMID             (1)
#define DM_DATA_2_LOCAL_ADDR        (0x0117FFF0UL)
#define DM_DATA_2_SIZE              (4UL)
#define DM_DATA_2_DDP               (&gs_defaultDataList[4])

/*finger print information APP*/
#define DM_DATA_3_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_3_MEMID             (1)
#define DM_DATA_3_LOCAL_ADDR        (0x0117FFE0UL)
#define DM_DATA_3_SIZE              (9UL)
#define DM_DATA_3_DDP               BL_NULL_PTR

/*caldata valid flag*/
#define DM_DATA_4_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_4_MEMID             (2)
#define DM_DATA_4_LOCAL_ADDR        (0x0080C000UL)
#define DM_DATA_4_SIZE              (4UL)
#define DM_DATA_4_DDP               (&gs_defaultDataList[8])

/*finger print information CAL*/
#define DM_DATA_5_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_5_MEMID             (2)
#define DM_DATA_5_LOCAL_ADDR        (0x0080C010UL)
#define DM_DATA_5_SIZE              (9UL)
#define DM_DATA_5_DDP               BL_NULL_PTR

/*header information APP*/
#define DM_DATA_6_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_6_MEMID             (1)
#define DM_DATA_6_LOCAL_ADDR        (0x00800008UL)
#define DM_DATA_6_SIZE              (8UL)
#define DM_DATA_6_DDP               BL_NULL_PTR

/*27 security access delay flag*/
#define DM_DATA_7_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_7_MEMID             (2)
#define DM_DATA_7_LOCAL_ADDR        (0x00808078UL)
#define DM_DATA_7_SIZE              (4UL)
#define DM_DATA_7_DDP               (&gs_defaultDataList[12])

#define DM_MAX_DATA_SIZE            DM_DATA_3_SIZE

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief The data informations list.*/
extern const bl_DataInfoList_t g_DataInfoList;
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif

