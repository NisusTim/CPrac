/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : App_boot.h
************************************************************************************************
*   Project/Product : Bootloader
*   Title           : Timer module Source File
*   Author          : Na.hu
************************************************************************************************
*   Description     : This file is used to implement the callback function.
*
************************************************************************************************
*   Limitations     : Only for HiBoot
*
************************************************************************************************
*
************************************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#                    Descriptions
*   ---------   ----------    ------------  ----------             ---------------
*   1.0         2012/10/4    Na.hu        N/A                    Original
*
************************************************************************************************
* END_FILE_HDR*/
#ifndef __APP_BOOT_H__
#define __APP_BOOT_H__

/*****************************************************************************
 * Macro Definitions
 *****************************************************************************/
#define FLAG_REPROGRAM_ID       (0x01u)
#define FLAG_REPROGRAM_ADDR     (0x00808000UL)
#define FLAG_DID_ADDR           (0x00808008UL)
#define FLAG_REPROGRAM_DATA     (0xA5A5A5A5UL)
#define FLAG_REPROGRAM_SIZE     (0x08u)
#define FLAG_WRITE_SIZE         (0x10u)

#define APP_FUN_OFF             (0)
#define APP_FUN_ON              (1)

/*****************************************************************************
 * Macro Configuration
 *****************************************************************************/
#define APP_FUN_FILE_HEADER         APP_FUN_OFF

/*****************************************************************************
  *  External Function Prototype Declarations
 *****************************************************************************/
extern void Boot_ReprogramCallBack(void);

#endif /* __APP_BOOT_H__ */
