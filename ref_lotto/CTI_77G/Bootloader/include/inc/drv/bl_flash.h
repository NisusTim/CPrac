/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the flash module.
 *
 *  \file       bl_flash.h
 *  \ingroup    driver_module
 *  \author     sijia.hao <sijia.hao@hirain.com>
 *
 *  \version    1.3.0
 *  \date       05/08/2013
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 17/03/2010 | he.yang          | N/A | BootDrv010001
 *      01.01.00 | 21/02/2011 | ning.chen        | N/A | BootDrv010002
 *      01.02.00 | 05/08/2013 | sijia.hao        | N/A | BootDrv010003
 *      01.03.00 | 20/03/2014 | sijia.hao        | N/A | BootDrv010004
 *
 *****************************************************************************/
#ifndef _BL_FLASH_H_
#define _BL_FLASH_H_
#include "bl_typedefs.h"
#include "S32R274.h"
#include "bl_flash_if.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447,3453 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define FLS_MCR_EHV                             0x01u
#define FLS_MCR_ESUS                           0x02u
#define FLS_MCR_ERS                             0x04u
#define FLS_MCR_PSUS                           0x08u
#define FLS_MCR_PGM                            0x10u
#define FLS_MCR_PEG                             0x200u
#define FLS_MCR_DONE                          0x400u
#define FLS_MCR_PEAS                           0x800u

/* command */
#define C55FMC_MCR_DONE                    0x00000400     /* State Machine Status */
#define C55FMC_MCR_PEG                      0x00000200     /* Program/Erase Good */
#define C55FMC_MCR_PGM                     0x00000010     /* Program */
#define C55FMC_MCR_ERS                      0x00000004     /* Erase */
#define C55FMC_MCR_EHV                      0x00000001     /* Enable High Voltage */


/* Offsets of C90LC Control Registers*/
#define C55FMC_C_MCR                          0x0000         /* Module Configuration Register */
#define C55FMC_C_LOCK0                       0x0010         /* Low/Mid Address Sapce Block Locking Register */
#define C55FMC_C_LOCK1                       0x0014         /* High Address Sapce Block Locking Register */
#define C55FMC_C_LOCK2                       0x0018         /* 256K Address Sapce Block Locking Register */
#define C55FMC_C_LOCK3                       0x001C         /* 256K Address Sapce Block Locking Register */
#define C55FMC_C_SEL0                          0x0038         /*  LMS Low/Mid Address Space Block Select Register */
#define C55FMC_C_SEL1                          0x003C         /*HBS  High Address Space Block Select Register */
#define C55FMC_C_SEL2                          0x0040         /*256K Address Space Block Select Register */
#define C55FMC_C_SEL3                          0x0044         /*256K Address Space Block Select Register */

#define WRITE32(address, value)             (*(volatile bl_u32_t*)(address) = (value))
#define READ32(address)                         ((bl_u32_t)(*(volatile bl_u32_t*)(address)))
#define SET32(address, value)                  (*(volatile bl_u32_t*)(address) |= (value))
#define CLEAR32(address, value)              (*(volatile bl_u32_t*)(address) &= ~(value))

#define WRITE64(address, value)             (*(volatile bl_u64_t*)(address) = (value))
#define READ64(address)                         ((bl_u64_t)(*(volatile bl_u64_t*)(address)))
#define SET64(address, value)                  (*(volatile bl_u64_t*)(address) |= (value))
#define CLEAR64(address, value)              (*(volatile bl_u64_t*)(address) &= ~(value))

#define FLS_BASE_ADDRESS                     (bl_u32_t)0xFFFE0000  /*Flash Main control registers*/

#define FLS_SECTOR_MAX_NUM               4U

#define DFLS_ADDRESS_START_L0           (bl_u32_t)0x00800000UL       /*16KB EEPROM block0*/
#define DFLS_ADDRESS_START_L1           (bl_u32_t)0x00804000UL       /*16KB EEPROM block2*/
#define DFLS_ADDRESS_START_L2			(bl_u32_t)0x00808000UL       /*16KB EEPROM block1*/
#define DFLS_ADDRESS_START_L3          	(bl_u32_t)0x0080C000UL       /*16KB EEPROM block3*/


#define CFLS_ADDRESS_START_H0           (bl_u32_t)0x00FA0000UL       /*64KB Code Flash block0*/
#define CFLS_ADDRESS_START_H1           (bl_u32_t)0x00FB0000UL       /*64KB Code Flash block1*/
#define CFLS_ADDRESS_START_H2           (bl_u32_t)0x00FC0000UL       /*64KB Code Flash block2*/
#define CFLS_ADDRESS_START_H3           (bl_u32_t)0x00FD0000UL       /*64KB Code Flash block3*/
#define CFLS_ADDRESS_START_H4           (bl_u32_t)0x00FE0000UL       /*64KB Code Flash block4*/
#define CFLS_ADDRESS_START_H5           (bl_u32_t)0x00FF0000UL       /*64KB Code Flash block5*/

#define CFLS_ADDRESS_START_B0           (bl_u32_t)0x01000000UL       /*256KB Code Flash block0*/
#define CFLS_ADDRESS_START_B1           (bl_u32_t)0x01040000UL       /*256KB Code Flash block1*/
#define CFLS_ADDRESS_START_B2           (bl_u32_t)0x01080000UL       /*256KB Code Flash block2*/
#define CFLS_ADDRESS_START_B3           (bl_u32_t)0x010C0000UL       /*256KB Code Flash block3*/
#define CFLS_ADDRESS_START_B4           (bl_u32_t)0x01100000UL       /*256KB Code Flash block4*/
#define CFLS_ADDRESS_START_B5           (bl_u32_t)0x01140000UL       /*256KB Code Flash block5*/
#define CFLS_ADDRESS_START_B6           (bl_u32_t)0x01180000UL       /*256KB Code Flash block6*/
#define CFLS_ADDRESS_START_B7           (bl_u32_t)0x011C0000UL       /*256KB Code Flash block7*/

#define DFLS_ADDRESS_END_L0				(bl_u32_t)0x00803FFFUL       /*16KB EEPROM block0*/
#define DFLS_ADDRESS_END_L1				(bl_u32_t)0x00807FFFUL       /*16KB EEPROM block2*/
#define DFLS_ADDRESS_END_L2				(bl_u32_t)0x0080BFFFUL       /*16KB EEPROM block1*/
#define DFLS_ADDRESS_END_L3				(bl_u32_t)0x0080FFFFUL       /*16KB EEPROM block3*/


#define CFLS_ADDRESS_END_H0              (bl_u32_t)0x00FAFFFFUL       /*64KB Code Flash block0*/
#define CFLS_ADDRESS_END_H1              (bl_u32_t)0x00FBFFFFUL       /*64KB Code Flash block1*/
#define CFLS_ADDRESS_END_H2              (bl_u32_t)0x00FCFFFFUL       /*64KB Code Flash block2*/
#define CFLS_ADDRESS_END_H3              (bl_u32_t)0x00FDFFFFUL       /*64KB Code Flash block3*/
#define CFLS_ADDRESS_END_H4              (bl_u32_t)0x00FEFFFFUL       /*64KB Code Flash block4*/
#define CFLS_ADDRESS_END_H5              (bl_u32_t)0x00FFFFFFUL       /*64KB Code Flash block5*/

#define CFLS_ADDRESS_END_B0              (bl_u32_t)0x0103FFFFUL       /*256KB Code Flash block0*/
#define CFLS_ADDRESS_END_B1              (bl_u32_t)0x0107FFFFUL       /*256KB Code Flash block1*/
#define CFLS_ADDRESS_END_B2              (bl_u32_t)0x010BFFFFUL       /*256KB Code Flash block2*/
#define CFLS_ADDRESS_END_B3              (bl_u32_t)0x010FFFFFUL       /*256KB Code Flash block3*/
#define CFLS_ADDRESS_END_B4              (bl_u32_t)0x0113FFFFUL       /*256KB Code Flash block4*/
#define CFLS_ADDRESS_END_B5              (bl_u32_t)0x0117FFFFUL       /*256KB Code Flash block5*/

#define DFLS_SECTOR0_L0					(bl_u32_t)0x10000           /*16KB EEPROM block0*/
#define DFLS_SECTOR1_L1					(bl_u32_t)0x20000           /*16KB EEPROM block0*/
#define DFLS_SECTOR2_L2					(bl_u32_t)0x40000			/*16KB  EEPROM block0*/
#define DFLS_SECTOR3_L3					(bl_u32_t)0x80000			/*16KB  EEPROM block1*/


#define CFLS_SECTOR6_H0                     (bl_u32_t)0x1               /*64KB Code Flash block0*/
#define CFLS_SECTOR7_H1                     (bl_u32_t)0x2               /*64KB Code Flash block1*/
#define CFLS_SECTOR8_H2                     (bl_u32_t)0x4               /*64KB Code Flash block2*/
#define CFLS_SECTOR9_H3                     (bl_u32_t)0x8               /*64KB Code Flash block3*/
#define CFLS_SECTOR10_H4                   (bl_u32_t)0x10              /*64KB Code Flash block4*/
#define CFLS_SECTOR11_H5                   (bl_u32_t)0x20              /*64KB Code Flash block5*/


#define CFLS_SECTOR12_B0                   (bl_u32_t)0x1          /*256KB Code Flash block0*/
#define CFLS_SECTOR13_B1                   (bl_u32_t)0x2          /*256KB Code Flash block1*/
#define CFLS_SECTOR14_B2                   (bl_u32_t)0x4          /*256KB Code Flash block2*/
#define CFLS_SECTOR15_B3                   (bl_u32_t)0x8          /*256KB Code Flash block3*/
#define CFLS_SECTOR16_B4                   (bl_u32_t)0x10         /*256KB Code Flash block4*/
#define CFLS_SECTOR17_B5                   (bl_u32_t)0x20         /*256KB Code Flash block5*/
#define CFLS_SECTOR18_B6                   (bl_u32_t)0x40         /*256KB Code Flash block6*/
#define CFLS_SECTOR19_B7                   (bl_u32_t)0x80         /*256KB Code Flash block7*/

#define FLASH_LOW_BLOCK                    (bl_u8_t)0x0
#define FLASH_MID_BLOCK                    (bl_u8_t)0x1
#define FLASH_HIGH_BLOCK                   (bl_u8_t)0x2
#define FLASH_MH_BLOCK                     (bl_u8_t)0x3


#define FLASH_DRIVER_VERSION_TYPE          (0x8001u)
#define FLASH_DRIVER_VERSION_INDEX         (0x0000u)
#define FLASH_DRIVER_VERSION_MAGIC         (0x58455031ul)
#define FLASH_DRIVER_VERSION_VERSION       (0x00010300UL)

#define FLASH_START_ADRESS                 (0x00800000UL)
#define FLASH_END_ADRESS                   (0x00810000UL)

#define FLASH_ERASE_SIZE                   (0x800u)
#define FLASH_ERASE_VALUE                  (0xFFu)

#define FLASH_RESET_TIME_CNT               (0)
#define FLASH_OVER_TIME_CNT                (0x10000u)

#define FLASH_DRIVER_INIT_OFFSET           (0x0Cu)
#define FLASH_DRIVER_DEINIT_OFFSET         (0x10u)
#define FLASH_DRIVER_ERASE_OFFSET          (0x14u)
#define FLASH_DRIVER_WRITE_OFFSET          (0x18u)

#define FLASH_DRIVER_INIT(sa, pp)           (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_INIT_OFFSET))(pp)
#define FLASH_DRIVER_DEINIT(sa, pp)         (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_DEINIT_OFFSET))(pp)
#define FLASH_DRIVER_ERASE(sa, pp)          (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_ERASE_OFFSET))(pp)
#define FLASH_DRIVER_WRITE(sa, pp)          (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_WRITE_OFFSET))(pp)


/****************************************************************************/

#define FLSDRI_SECTOR_MAX_NUM				14U

#define DFLSDRI_ADDRESS_START_L0           (bl_u32_t)0x00800000UL       /*16KB EEPROM block0*/
#define DFLSDRI_ADDRESS_START_L1           (bl_u32_t)0x00804000UL       /*16KB EEPROM block1*/
#define DFLSDRI_ADDRESS_START_M0          (bl_u32_t)0x00808000UL       /*32KB EEPROM block0*/
#define DFLSDRI_ADDRESS_START_M1          (bl_u32_t)0x00810000UL       /*32KB EEPROM block1*/
#define CFLSDRI_ADDRESS_START_L2           (bl_u32_t)0x00F98000UL       /*16KB Code Flash block2*/
#define CFLSDRI_ADDRESS_START_L3           (bl_u32_t)0x00F9c000UL       /*16KB Code Flash block3*/

#define CFLSDRI_ADDRESS_START_H0           (bl_u32_t)0x00FA0000UL       /*64KB Code Flash block0*/
#define CFLSDRI_ADDRESS_START_H1           (bl_u32_t)0x00FB0000UL       /*64KB Code Flash block1*/
#define CFLSDRI_ADDRESS_START_H2           (bl_u32_t)0x00FC0000UL       /*64KB Code Flash block2*/
#define CFLSDRI_ADDRESS_START_H3           (bl_u32_t)0x00FD0000UL       /*64KB Code Flash block3*/
#define CFLSDRI_ADDRESS_START_H4           (bl_u32_t)0x00FE0000UL       /*64KB Code Flash block4*/
#define CFLSDRI_ADDRESS_START_H5           (bl_u32_t)0x00FF0000UL       /*64KB Code Flash block5*/

#define CFLSDRI_ADDRESS_START_B0           (bl_u32_t)0x01000000UL       /*256KB Code Flash block0*/
#define CFLSDRI_ADDRESS_START_B1           (bl_u32_t)0x01040000UL       /*256KB Code Flash block1*/
#define CFLSDRI_ADDRESS_START_B2           (bl_u32_t)0x01080000UL       /*256KB Code Flash block2*/
#define CFLSDRI_ADDRESS_START_B3           (bl_u32_t)0x010C0000UL       /*256KB Code Flash block3*/
#define CFLSDRI_ADDRESS_START_B4           (bl_u32_t)0x01100000UL       /*256KB Code Flash block4*/
#define CFLSDRI_ADDRESS_START_B5           (bl_u32_t)0x01140000UL       /*256KB Code Flash block5*/
#define CFLSDRI_ADDRESS_START_B6           (bl_u32_t)0x01180000UL       /*256KB Code Flash block6*/
#define CFLSDRI_ADDRESS_START_B7           (bl_u32_t)0x011C0000UL       /*256KB Code Flash block7*/

#define DFLSDRI_ADDRESS_END_L0               (bl_u32_t)0x00803FFFUL       /*16KB EEPROM block0*/
#define DFLSDRI_ADDRESS_END_L1               (bl_u32_t)0x00807FFFUL       /*16KB EEPROM block1*/
#define DFLSDRI_ADDRESS_END_M0              (bl_u32_t)0x0080FFFFUL       /*32KB EEPROM block0*/
#define DFLSDRI_ADDRESS_END_M1              (bl_u32_t)0x00817FFFUL       /*32KB EEPROM block1*/
#define CFLSDRI_ADDRESS_END_L2               (bl_u32_t)0x00F9BFFFUL       /*16KB Code Flash block2*/
#define CFLSDRI_ADDRESS_END_L3               (bl_u32_t)0x00F9FFFFUL       /*16KB Code Flash block3*/

#define CFLSDRI_ADDRESS_END_H0              (bl_u32_t)0x00FAFFFFUL       /*64KB Code Flash block0*/
#define CFLSDRI_ADDRESS_END_H1              (bl_u32_t)0x00FBFFFFUL       /*64KB Code Flash block1*/
#define CFLSDRI_ADDRESS_END_H2              (bl_u32_t)0x00FCFFFFUL       /*64KB Code Flash block2*/
#define CFLSDRI_ADDRESS_END_H3              (bl_u32_t)0x00FDFFFFUL       /*64KB Code Flash block3*/
#define CFLSDRI_ADDRESS_END_H4              (bl_u32_t)0x00FEFFFFUL       /*64KB Code Flash block4*/
#define CFLSDRI_ADDRESS_END_H5              (bl_u32_t)0x00FFFFFFUL       /*64KB Code Flash block5*/

#define CFLSDRI_ADDRESS_END_B0              (bl_u32_t)0x0103FFFFUL       /*256KB Code Flash block0*/
#define CFLSDRI_ADDRESS_END_B1              (bl_u32_t)0x0107FFFFUL       /*256KB Code Flash block1*/
#define CFLSDRI_ADDRESS_END_B2              (bl_u32_t)0x010BFFFFUL       /*256KB Code Flash block2*/
#define CFLSDRI_ADDRESS_END_B3              (bl_u32_t)0x010FFFFFUL       /*256KB Code Flash block3*/
#define CFLSDRI_ADDRESS_END_B4              (bl_u32_t)0x0113FFFFUL       /*256KB Code Flash block4*/
#define CFLSDRI_ADDRESS_END_B5              (bl_u32_t)0x0117FFFFUL       /*256KB Code Flash block5*/
#define CFLSDRI_ADDRESS_END_B6              (bl_u32_t)0x011BFFFFUL       /*256KB Code Flash block6*/
#define CFLSDRI_ADDRESS_END_B7              (bl_u32_t)0x011FFFFFUL       /*256KB Code Flash block7*/

#define DFLSDRI_SECTOR0_L0						(bl_u32_t)0x10000           /*16KB EEPROM block0*/
#define DFLSDRI_SECTOR1_L1						(bl_u32_t)0x20000           /*16KB EEPROM block0*/
#define DFLSDRI_SECTOR2_M0                     (bl_u32_t)0x1               /*32KB EEPROM block0*/
#define DFLSDRI_SECTOR3_M1                     (bl_u32_t)0x2               /*32KB EEPROM block1*/
#define CFLSDRI_SECTOR4_L2						(bl_u32_t)0x40000           /*16KB Code Flash block2*/
#define CFLSDRI_SECTOR5_L3						(bl_u32_t)0x80000           /*16KB Code Flash block3*/

#define CFLSDRI_SECTOR6_H0                     (bl_u32_t)0x4//1               /*64KB Code Flash block0*/
#define CFLSDRI_SECTOR7_H1                     (bl_u32_t)0x8//2               /*64KB Code Flash block1*/
#define CFLSDRI_SECTOR8_H2                     (bl_u32_t)0x10//4               /*64KB Code Flash block2*/
#define CFLSDRI_SECTOR9_H3                     (bl_u32_t)0x20//8               /*64KB Code Flash block3*/
#define CFLSDRI_SECTOR10_H4                   (bl_u32_t)0x40//10              /*64KB Code Flash block4*/
#define CFLSDRI_SECTOR11_H5                   (bl_u32_t)0x80//20              /*64KB Code Flash block5*/


#define CFLSDRI_SECTOR12_B0                   (bl_u32_t)0x1          /*256KB Code Flash block0*/
#define CFLSDRI_SECTOR13_B1                   (bl_u32_t)0x2          /*256KB Code Flash block1*/
#define CFLSDRI_SECTOR14_B2                   (bl_u32_t)0x4          /*256KB Code Flash block2*/
#define CFLSDRI_SECTOR15_B3                   (bl_u32_t)0x8          /*256KB Code Flash block3*/
#define CFLSDRI_SECTOR16_B4                   (bl_u32_t)0x10         /*256KB Code Flash block4*/
#define CFLSDRI_SECTOR17_B5                   (bl_u32_t)0x20         /*256KB Code Flash block5*/
#define CFLSDRI_SECTOR18_B6                   (bl_u32_t)0x40         /*256KB Code Flash block6*/
#define CFLSDRI_SECTOR19_B7                   (bl_u32_t)0x80         /*256KB Code Flash block7*/

#define FLASHDRI_LOW_BLOCK                   (bl_u8_t)0x0
#define FLASHDRI_MID_BLOCK                    (bl_u8_t)0x1
#define FLASHDRI_HIGH_BLOCK                  (bl_u8_t)0x2
#define FLASHDRI_MH_BLOCK                     (bl_u8_t)0x3


#define FLASHDRI_DRIVER_VERSION_TYPE          (0x8001u)
#define FLASHDRI_DRIVER_VERSION_INDEX         (0x0000u)
#define FLASHDRI_DRIVER_VERSION_MAGIC         (0x58455031ul)
#define FLASHDRI_DRIVER_VERSION_VERSION       (0x00010300UL)

#define FLASHDRI_START_ADRESS					(0x00F98000UL)
#define FLASHDRI_END_ADRESS					(0x01180000UL)

#define FLASHDRI_ERASE_SIZE                            (0x800u)
#define FLASHDRI_ERASE_VALUE                         (0x00u)


typedef struct SECTOR_INFO
{
    bl_u32_t BlockAddressStart;
    bl_u32_t BlockAddressEnd;
    bl_u32_t SectorId;
    bl_u8_t Blocktype;
}Fls_SectorInfoType;

typedef struct
{
    bl_u32_t SectorId;
    bl_u8_t Blocktype;
}Fls_SectorSlecType;


/*****************************************************************************
 * Type Declarations
 *****************************************************************************/

extern bl_FlashDrvHeader_t g_FlashHeader;

/*****************************************************************************
 * External Function Prototype Declarations
 *****************************************************************************/
extern bl_Return_t DFlashInit(void);
extern bl_Return_t DFlashDeinit(void);
extern void DFlashWrite(bl_FlashDrvParam_t *par);
extern void DFlashErase(bl_FlashDrvParam_t *par);

extern void FlashDriInit(bl_FlashDrvParam_t *par);
extern void FlashDriDeinit(bl_FlashDrvParam_t *par);
extern void FlashDriWrite(bl_FlashDrvParam_t *par);
extern void FlashDriErase(bl_FlashDrvParam_t *par);

extern void Flash_Read(bl_FlashDrvParam_t *par);

#endif/*BL_FLASH_H*/

