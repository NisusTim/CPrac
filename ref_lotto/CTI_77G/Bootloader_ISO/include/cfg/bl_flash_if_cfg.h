/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the flash_if manager module.
 *
 *  \file       bl_flash_if_cfg.h
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
#ifndef _BL_FLASH_IF_CFG_H_
#define _BL_FLASH_IF_CFG_H_
#include "bl_flash_if.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447,3453 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The g_FlashIfBlockList is used in the bl_flash_if.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The g_FlashIfBlockList is declared in the header file.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * the FLASHIF_CONVERTADDRESS have no side-effect.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/*If there is a different between the logical address and the physical address,
  configurate the below macro. The physical is a pointer.*/
#define FLASHIF_CONVERTADDRESS(logical,physical)    ((void)0)


/* publish the erase and write time ,
   if different sector have different time,publish the max one
*/
#define FLASHIF_SECTOR_ERASETIME            (1000)  /*unit ms*/
#define FLASHIF_PAGE_WRITETIME              (1)   /*unit ms*/
/* the max access time ,when time out the hiboot have to send reponse to pc */
#define FLASHIF_ACCESS_TIMELIMITE           (3000UL) /*unit ms*/

/* define the physical flash block num*/
#define FLASHIF_ERASED_VALUE                (0xffu)

/* config order :address low-high*/
/* config block 0 parameter - 0x780000-0x79FFFF */
#define FLASHIF_BLOCK0_STARTADDRESS         (0xf98000UL)
#define FLASHIF_BLOCK0_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK0_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK0_PAGE_SIZE            (8)

/* config block 1 parameter - 0x7A0000-0x7BFFFF */
#define FLASHIF_BLOCK1_STARTADDRESS         (0xf9c000UL)
#define FLASHIF_BLOCK1_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK1_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK1_PAGE_SIZE            (8)

/* config block 2 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK2_STARTADDRESS         (0xFA0000UL)
#define FLASHIF_BLOCK2_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK2_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK2_PAGE_SIZE            (8)

/* config block 3 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK3_STARTADDRESS         (0xFB0000UL)
#define FLASHIF_BLOCK3_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK3_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK3_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK4_STARTADDRESS         (0xFC0000UL)
#define FLASHIF_BLOCK4_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK4_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK4_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK5_STARTADDRESS         (0xFD0000UL)
#define FLASHIF_BLOCK5_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK5_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK5_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK6_STARTADDRESS         (0xFE0000UL)
#define FLASHIF_BLOCK6_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK6_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK6_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK7_STARTADDRESS         (0xFF0000UL)
#define FLASHIF_BLOCK7_TOTAL_SIZE           (0x10000UL)
#define FLASHIF_BLOCK7_SECTOR_SIZE          (0x10000UL)
#define FLASHIF_BLOCK7_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK8_STARTADDRESS         (0x1000000UL)
#define FLASHIF_BLOCK8_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK8_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK8_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK9_STARTADDRESS         (0x1040000UL)
#define FLASHIF_BLOCK9_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK9_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK9_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK10_STARTADDRESS         (0x1080000UL)
#define FLASHIF_BLOCK10_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK10_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK10_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK11_STARTADDRESS         (0x10C0000UL)
#define FLASHIF_BLOCK11_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK11_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK11_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK12_STARTADDRESS         (0x1100000UL)
#define FLASHIF_BLOCK12_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK12_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK12_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK13_STARTADDRESS         (0x1140000UL)
#define FLASHIF_BLOCK13_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK13_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK13_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK14_STARTADDRESS         (0x1180000UL)
#define FLASHIF_BLOCK14_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK14_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK14_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK15_STARTADDRESS         (0x11C0000UL)
#define FLASHIF_BLOCK15_TOTAL_SIZE           (0x40000UL)
#define FLASHIF_BLOCK15_SECTOR_SIZE          (0x40000UL)
#define FLASHIF_BLOCK15_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK16_STARTADDRESS         (0x800000UL)
#define FLASHIF_BLOCK16_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK16_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK16_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK17_STARTADDRESS         (0x804000UL)
#define FLASHIF_BLOCK17_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK17_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK17_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK18_STARTADDRESS         (0x808000UL)
#define FLASHIF_BLOCK18_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK18_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK18_PAGE_SIZE            (8)

/* config block 4 parameter - 0x7C0000-0x7FFFFF */
#define FLASHIF_BLOCK19_STARTADDRESS         (0x80C000UL)
#define FLASHIF_BLOCK19_TOTAL_SIZE           (0x4000UL)
#define FLASHIF_BLOCK19_SECTOR_SIZE          (0x4000UL)
#define FLASHIF_BLOCK19_PAGE_SIZE            (8)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
extern const bl_FlashIfBlockInfo_t g_FlashIfBlockList[FLASHIF_NUMBER_OF_BLOCK];

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif

