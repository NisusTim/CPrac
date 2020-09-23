/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
************************************************************************************************
*   File Name       : App_boot.c
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
#include "App_boot.h"
#include "ComStack_Types.h"
#include "S32R274.h"
#include "App_flash.h"
#include "fbl_parameter.h"

/*****************************************************************************
 *  Internal Type Declarations
 *****************************************************************************/
typedef unsigned char bl_u8_t;      /**< This is a unsigned type for 8 bits.*/
typedef unsigned short bl_u16_t;    /**< This is a unsigned type for 16 bits.*/
typedef unsigned long bl_u32_t;     /**< This is a unsigned type for 32 bits.*/
#define BL_NULL_PTR     ((void *)0)

#if(APP_FUN_FILE_HEADER == APP_FUN_ON)
/*****************************************************************************
 *  File Header Definitions
 *****************************************************************************/

#endif

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void Boot_SetFlag(bl_u8_t flagId);
static void Boot_Reset(void);
//static void Boot_MemSet(bl_u32_t * des, bl_u32_t src);    //Remove by Wood, in order to resolve unused warning

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_ReprogramCallBack
*
* Description   : Set the reprogramming flag and reset the ECU.
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   : Only for Bootloader
*
************************************************************************************************
END_FUNCTION_HDR */
void Boot_ReprogramCallBack(void)
{

    /*set reprogram flag*/
    Boot_SetFlag(FLAG_REPROGRAM_ID);
    /*reset ECU*/
    Boot_Reset();
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_SetFlag
*
* Description   : Set the reprogramming flag.
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   : Only for Bootloader
*
************************************************************************************************
END_FUNCTION_HDR */
static void Boot_SetFlag(bl_u8_t flagId)
{
	set_reporgram_flag();
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_MemSet
* Description   : This function is used for copying data.
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   :
*
************************************************************************************************
END_FUNCTION_HDR */
//static void Boot_MemSet(bl_u32_t * des, bl_u32_t src)     //Remove by Wood, in order to resolve unused warning
//{
//    if (des != BL_NULL_PTR)
//    {
//        *des = src;
//    }
//
//    return;
//}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Boot_Reset
*
* Description   : Reset the ECU.
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   : Only for Bootloader
*
************************************************************************************************
END_FUNCTION_HDR */
static void Boot_Reset(void)
{
	MC_ME.MCTL.R = 0x00005AF0;
	MC_ME.MCTL.R = 0x0000A50F;
    for(;;)
    {

    }
}

