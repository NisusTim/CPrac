/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the flash_if manager
 *              module.
 *
 *  \file       bl_flash_if_cfg.c
 *  \ingroup    flash_if_manager_module
 *  \author     haiping.wang <haiping.wang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      02.00.00 | 19/08/2013 | haiping.wang     | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
******************************************************************************/
#include "bl_flash_if_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1531,3211 EOF*/
/*
 * 1531:The object is referenced in only one translation unit.
 * g_BootingCheckerList is a configurations.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Function Macro
 *****************************************************************************/

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

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/** \brief config the physical flash block.*/
const bl_FlashIfBlockInfo_t g_FlashIfBlockList[FLASHIF_NUMBER_OF_BLOCK] =
{
    {
        FLASHIF_BLOCK0_STARTADDRESS,
        FLASHIF_BLOCK0_TOTAL_SIZE,
        FLASHIF_BLOCK0_SECTOR_SIZE,
        FLASHIF_BLOCK0_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK1_STARTADDRESS,
        FLASHIF_BLOCK1_TOTAL_SIZE,
        FLASHIF_BLOCK1_SECTOR_SIZE,
        FLASHIF_BLOCK1_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK2_STARTADDRESS,
        FLASHIF_BLOCK2_TOTAL_SIZE,
        FLASHIF_BLOCK2_SECTOR_SIZE,
        FLASHIF_BLOCK2_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK3_STARTADDRESS,
        FLASHIF_BLOCK3_TOTAL_SIZE,
        FLASHIF_BLOCK3_SECTOR_SIZE,
        FLASHIF_BLOCK3_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK4_STARTADDRESS,
        FLASHIF_BLOCK4_TOTAL_SIZE,
        FLASHIF_BLOCK4_SECTOR_SIZE,
        FLASHIF_BLOCK4_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK5_STARTADDRESS,
        FLASHIF_BLOCK5_TOTAL_SIZE,
        FLASHIF_BLOCK5_SECTOR_SIZE,
        FLASHIF_BLOCK5_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK6_STARTADDRESS,
        FLASHIF_BLOCK6_TOTAL_SIZE,
        FLASHIF_BLOCK6_SECTOR_SIZE,
        FLASHIF_BLOCK6_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK7_STARTADDRESS,
        FLASHIF_BLOCK7_TOTAL_SIZE,
        FLASHIF_BLOCK7_SECTOR_SIZE,
        FLASHIF_BLOCK7_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK8_STARTADDRESS,
        FLASHIF_BLOCK8_TOTAL_SIZE,
        FLASHIF_BLOCK8_SECTOR_SIZE,
        FLASHIF_BLOCK8_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK9_STARTADDRESS,
        FLASHIF_BLOCK9_TOTAL_SIZE,
        FLASHIF_BLOCK9_SECTOR_SIZE,
        FLASHIF_BLOCK9_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK10_STARTADDRESS,
        FLASHIF_BLOCK10_TOTAL_SIZE,
        FLASHIF_BLOCK10_SECTOR_SIZE,
        FLASHIF_BLOCK10_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK11_STARTADDRESS,
        FLASHIF_BLOCK11_TOTAL_SIZE,
        FLASHIF_BLOCK11_SECTOR_SIZE,
        FLASHIF_BLOCK11_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK12_STARTADDRESS,
        FLASHIF_BLOCK12_TOTAL_SIZE,
        FLASHIF_BLOCK12_SECTOR_SIZE,
        FLASHIF_BLOCK12_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK13_STARTADDRESS,
        FLASHIF_BLOCK13_TOTAL_SIZE,
        FLASHIF_BLOCK13_SECTOR_SIZE,
        FLASHIF_BLOCK13_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK14_STARTADDRESS,
        FLASHIF_BLOCK14_TOTAL_SIZE,
        FLASHIF_BLOCK14_SECTOR_SIZE,
        FLASHIF_BLOCK14_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK15_STARTADDRESS,
        FLASHIF_BLOCK15_TOTAL_SIZE,
        FLASHIF_BLOCK15_SECTOR_SIZE,
        FLASHIF_BLOCK15_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK16_STARTADDRESS,
        FLASHIF_BLOCK16_TOTAL_SIZE,
        FLASHIF_BLOCK16_SECTOR_SIZE,
        FLASHIF_BLOCK16_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK17_STARTADDRESS,
        FLASHIF_BLOCK17_TOTAL_SIZE,
        FLASHIF_BLOCK17_SECTOR_SIZE,
        FLASHIF_BLOCK17_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK18_STARTADDRESS,
        FLASHIF_BLOCK18_TOTAL_SIZE,
        FLASHIF_BLOCK18_SECTOR_SIZE,
        FLASHIF_BLOCK18_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK19_STARTADDRESS,
        FLASHIF_BLOCK19_TOTAL_SIZE,
        FLASHIF_BLOCK19_SECTOR_SIZE,
        FLASHIF_BLOCK19_PAGE_SIZE,
    },    
};

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/

