/*  BEGIN_FILE_HDR
***********************************************************************************************
*   NOTICE
*   This software is the property of HiRain Technologies. Any information contained in this
*   doc should not be reproduced, or used, or disclosed without the written authorization from
*   HiRain Technologies.
***********************************************************************************************
*   File Name       : Can_Type.h
***********************************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module type definitions head File
*   Author          : HeYang
***********************************************************************************************
*   Description     : The header file Can_Type.h contains the  common type definitions of
*                     the module Can Driver
***********************************************************************************************
*   Limitations     :
*
***********************************************************************************************
*
***********************************************************************************************
*   Revision History:
*
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   1.0         2012/5/6       HeYang       N/A          Original
*
***********************************************************************************************
* END_FILE_HDR*/
#ifndef _CAN_TYPE_H_
#define _CAN_TYPE_H_

/*CAN429:
Name: Can_HwHandleType
Type: bl_u8_t , bl_u16_t
Range: Standard 0..0x0FF
       Extended 0..0xFFFF
Description:    Represents the hardware object handles of a CAN hardware unit. For CAN
                hardware units with more than 255 HW objects use extended range.
*/
typedef bl_u16_t Can_HwHandleType;

 /*CAN416:
Name:   Can_IdType
Type:   bl_u16_t, bl_u32_t
Range:  Standard 0..0x7FF
        Extended 0..0xFFFFFFFF
Description:
Represents the Identifier of an L-PDU. For extended IDs the most significant
bit is set.
*/
#if (STD_ON == CAN_ENABLE_EXTENDED_ID)
    typedef bl_u32_t Can_IdType;
#else
    typedef bl_u16_t Can_IdType;
#endif/* #if (STD_ON == CAN_ENABLE_EXTENDED_ID)  */

/*CAN039:
Name:  Can_ReturnType
Enumeration  Type:
Range:
CAN_OK  success
CAN_NOT_OK  error occurred or wakeup event occurred during sleep transition
CAN_BUSY  transmit request could not be processed because no transmit object was available
Description:  Return values of CAN driver API .
*/
typedef enum
{
    CAN_OK = 0,
    CAN_NOT_OK,
    CAN_BUSY
}Can_ReturnType;


#if (CAN_DEV_ERROR_DETECT == STD_ON )
  typedef enum
  {
      CAN_UNINT = 0,
      CAN_STOPPED,
      CAN_STARTED,
      CAN_SLEEP
  }Can_StateType;
#endif


/* CAN417:
Name:  Can_StateTransitionType
Type:  Enumeration
Range:
CAN_T_START  CAN controller transition value to request state STARTED.
CAN_T_STOP  CAN controller transition value to request state STOPPED.
CAN_T_SLEEP  CAN controller transition value to request state SLEEP.
CAN_T_WAKEUP  CAN controller transition value to request state STOPPED from state SLEEP.
Description:  State transitions that are used by the function CAN_SetControllerMode
*/
typedef enum
{
    CAN_T_NONE = 0,
    CAN_T_START = 1,
    CAN_T_STOP = 2,
    CAN_T_SLEEP = 3,
    CAN_T_WAKEUP =4
}Can_StateTransitionType;


 /* CAN413:
Name:  Can_ConfigType
Type:  Structure
Range: Implementation specific.
Description:This is the type of the external data structure containing
the overall initialization data for the CAN driver and SFR settings
affecting all controllers. Furthermore it contains pointers to controller
configuration structures. The contents of the initialization data structure
are CAN hardware specific.
*/

typedef struct
{

    bl_u8_t   CanControllerNum;
}Can_ConfigType;

/*CAN414:
Name:     Can_ControllerConfigType
Type:     Structure
Range:    Implementation specific.
Description: This is the type of the external data structure containing
the bit timing related initialization data for one CAN controller.
The contents of the initialization data structure are CAN hardware specific.
*/
typedef struct
{
    bl_u8_t    CanCtrl0;
    bl_u8_t    CanCtrl1;
}Can_ControllerConfigType;

/*CAN415:
Name: Can_PduType
Type: Structure
Description:
This type is used to provide ID, DLC and SDU from CAN interface
to CAN driver.
*/
/* Added by junfei.chen */
/*The size of this global type depends on the maximum number of PDUs used
within one software module.*/
typedef bl_u16_t       PduIdType;

typedef struct
{
    bl_u8_t      controllerRef;  /*logic controller*/
   Can_IdType    id;             /*CAN ID*/
   bl_u8_t       hohType;        /*hohType  bit0:0-receive,1-transmit;bit1:0-basic ,1-full*/
   bl_u32_t      filterRef;      /*value of Rx Individual Mask Registers,when BCC=1*/
}Can_HardwareObjectConfigType;

typedef enum
{
   CAN_UNINITIALIZED=0,
   CAN_INITIALIZED=1
}Can_InitType;

typedef bl_u16_t Can_BaudrateType;

#if (CANIF_FUN_DYNAMIC_CANID == BL_FUN_ON)
typedef struct
{
    Can_IdType rxid1;
    Can_IdType rxid2;
    Can_IdType txid;
    Can_BaudrateType brp;
}Can_ParameterType;

#define CAN_RATE_1000          ((Can_BaudrateType)1000U)/* when baudrate == 1Mbps */
#define CAN_RATE_500           ((Can_BaudrateType)500U) /* when baudrate == 500kbps */
#define CAN_RATE_250           ((Can_BaudrateType)250U) /* when baudrate == 250kbps */
#define CAN_RATE_125           ((Can_BaudrateType)125U) /* when baudrate == 125kbps */
#define CAN_RATE_100           ((Can_BaudrateType)100U) /* when baudrate == 100kbps */
#endif

typedef enum
{
    CanStatus_UnInit =0,
    CanStatus_Init = 1
}CanInitType;

#endif /*CAN_TYPE_H_*/

