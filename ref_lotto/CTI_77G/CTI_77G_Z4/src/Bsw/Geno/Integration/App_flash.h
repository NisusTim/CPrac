/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the flash module.
 *
 *  \file       App_flash.h
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
#include "S32R274.h"

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
#define CFLS_ADDRESS_END_B6              (bl_u32_t)0x011BFFFFUL       /*256KB Code Flash block6*/
#define CFLS_ADDRESS_END_B7              (bl_u32_t)0x011FFFFFUL       /*256KB Code Flash block7*/

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

#define FLASH_LOW_BLOCK                   (bl_u8_t)0x0
#define FLASH_MID_BLOCK                    (bl_u8_t)0x1
#define FLASH_HIGH_BLOCK                  (bl_u8_t)0x2
#define FLASH_MH_BLOCK                     (bl_u8_t)0x3


#define FLASH_DRIVER_VERSION_TYPE          (0x8001u)
#define FLASH_DRIVER_VERSION_INDEX        (0x0000u)
#define FLASH_DRIVER_VERSION_MAGIC        (0x58455031ul)
#define FLASH_DRIVER_VERSION_VERSION    (0x00010300UL)

#define FLASH_START_ADRESS                       (0x00800000UL)
#define FLASH_END_ADRESS                           (0x00818000UL)

#define FLASH_ERASE_SIZE                            (0x800u)
#define FLASH_ERASE_VALUE                         (0x00u)

#define FLASH_RESET_TIME_CNT                   (0)
#define FLASH_OVER_TIME_CNT                    (0x10000u)

#define FLASH_DRIVER_INIT_OFFSET             (0x0Cu)
#define FLASH_DRIVER_DEINIT_OFFSET         (0x10u)
#define FLASH_DRIVER_ERASE_OFFSET          (0x14u)
#define FLASH_DRIVER_WRITE_OFFSET         (0x18u)

#define FLASH_DRIVER_INIT(sa, pp)              (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_INIT_OFFSET))(pp)
#define FLASH_DRIVER_DEINIT(sa, pp)          (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_DEINIT_OFFSET))(pp)
#define FLASH_DRIVER_ERASE(sa, pp)           (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_ERASE_OFFSET))(pp)
#define FLASH_DRIVER_WRITE(sa, pp)          (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_WRITE_OFFSET))(pp)

typedef unsigned char bl_u8_t;      /**< This is a unsigned type for 8 bits.*/
typedef unsigned short bl_u16_t;    /**< This is a unsigned type for 16 bits.*/
typedef unsigned long bl_u32_t;     /**< This is a unsigned type for 32 bits.*/
typedef unsigned long long bl_u64_t;/**< This is a unsigned type for 64 bits.*/
typedef bl_u32_t bl_Address_t;      /**< The address of the memory.*/
typedef bl_u32_t bl_Size_t;         /**< The size of the memory.*/
typedef bl_u8_t bl_Buffer_t;        /**< The type for buffer.*/
typedef enum _tag_Return
{
    /** Indicate that a function was successfully processed.*/
    BL_ERR_OK = 0,
    /** Indicate that a function was NOT successfully processed.*/
    BL_ERR_NOT_OK = 1,
    /** A debug assert failure is caused by the parameters of a function.*/
    BL_ERR_ASSERT_CONFIGURATION = 2,
    /** A debug assert failure is caused by the parameters of a function.*/
    BL_ERR_ASSERT_PARAMETERS = 3,
    /** A debug assert is failure.*/
    BL_ERR_ASSERT_FAILURE = 4,
    /** The buffer is busy*/
    BL_ERR_BUFFER_BUSY = 5,
    /** The size greater than the size of buffer*/
    BL_ERR_BUFFER_OVERFLOW = 6,
    BL_ERR_INVALID_FS = 7,
    BL_ERR_WRONG_SN = 8,
    BL_ERR_UNEXPECTED_FRAME = 9,
    /** The timerA used to cantp module is timeout*/
    BL_ERR_TIMEROUT_A = 10,
    /** The timerBs used to cantp module is timeout*/
    BL_ERR_TIMEROUT_BS = 11,
    /** The timerCr used to cantp module is timeout*/
    BL_ERR_TIMEROUT_CR = 12,
    /** The address or size is out of range for logical block*/
    BL_ERR_LB_OUTOFRANGE = 13,
    /** The error codes defined by user is not smaller than this macro.*/
    BL_ERR_SYSTEM_LIMIT = 99,
    /**
     *  A error code, named '01', is used by user. It is only used for the
     *  internal interface of a module.
     */
    BL_ERR_USER_CODE_01 = 100,
    /** A error code, named '02', is used by user.*/
    BL_ERR_USER_CODE_02 = 101,
    /** A error code, named '03', is used by user.*/
    BL_ERR_USER_CODE_03 = 102,
    /** A error code, named '04', is used by user.*/
    BL_ERR_USER_CODE_04 = 103,
    /** A error code, named '05', is used by user.*/
    BL_ERR_USER_CODE_05 = 104,
    /** A error code, named '06', is used by user.*/
    BL_ERR_USER_CODE_06 = 105,
    /** A error code, named '07', is used by user.*/
    BL_ERR_USER_CODE_07 = 106
} bl_Return_t;  /**< Some values from a called function.*/

#define FLASHIF_DRIVER_FUN_POS
#define FLASHIF_DRIVER_FUNPTR_POS
/** \brief A alias of the struct _tag_FlashDrvParam_t.*/
typedef struct _tag_FlashDrvParam bl_FlashDrvParam_t;
/** \brief A alias of the struct _tag_FlashDrvHeader.*/
typedef struct _tag_FlashDrvHeader bl_FlashDrvHeader_t;
/** \brief A pointer point to the operations function of flash driver.*/
typedef void
    (FLASHIF_DRIVER_FUN_POS * FLASHIF_DRIVER_FUNPTR_POS bl_FlashDrvFun_t)
    (bl_FlashDrvParam_t *par);


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

struct _tag_FlashDrvParam
{
    bl_u8_t type;           /**< the type*/
    bl_Return_t errCode;    /**< the result of a flash operation*/
#if (FLASHIF_FUN_ERASE_BY_BLOCKID == BL_FUN_ON)
    bl_u16_t phyBlockId;    /**< the physical block id.*/
#endif
    bl_Address_t address;   /**< the start address of a flash operation.*/
    bl_Size_t size;         /**< the size of a flash operation.*/
    bl_Buffer_t *buffer;    /**< the contents of data of a flash operation.*/
    bl_u64_t    wrdata;     /* write 64bits data to flash */
    void (*FeedDog)(void);  /**< the feed watchdog interface.*/
};

struct _tag_FlashDrvHeader
{
    bl_u16_t type;          /**< The type of the flash driver.*/
    bl_u16_t index;         /**< The index of the flash driver.*/
    bl_u32_t magic;         /**< The magic value of the flash driver*/
    bl_u32_t version;       /**< The current of the flash driver.*/
    bl_FlashDrvFun_t Init;  /**< Initialize the flash drvier.*/
    bl_FlashDrvFun_t Deinit;/**< Deinitialize the flash drvier*/
    bl_FlashDrvFun_t Erase; /**< Erase a block of the flash device.*/
    bl_FlashDrvFun_t Write; /**< Write data to the flash device.*/
};


/*****************************************************************************
 * Type Declarations
 *****************************************************************************/

/*****************************************************************************
 * External Function Prototype Declarations
 *****************************************************************************/
extern void FlashInit(bl_FlashDrvParam_t *par);
extern void FlashDeinit(bl_FlashDrvParam_t *par);
extern void FlashWrite(bl_FlashDrvParam_t *par);
extern void FlashErase(bl_FlashDrvParam_t *par);

extern void Flash_Read(bl_Address_t address,bl_Size_t size,bl_Buffer_t *buffer);

#endif/*BL_FLASH_H*/

