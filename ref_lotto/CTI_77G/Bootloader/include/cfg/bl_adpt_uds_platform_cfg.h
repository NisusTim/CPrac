/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the head file to configurate the adapter module based
 *              on uds platform.
 *
 *  \file       bl_adpt_uds_platform_cfg.h
 *  \ingroup    communication_protocol_stack_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *              heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.02.00 | 27/09/2011 | mingqing.tang    | N/A | Boot030003
 *      03.03.00 | 29/09/2011 | mingqing.tang    | N/A | Boot030004
 *      03.05.00 | 12/10/2011 | mingqing.tang    | N/A | Boot030006
 *      04.00.00 | 10/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.02.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040003
 *      04.04.00 | 18/07/2012 | mingqing.tang    | N/A | Boot040005
 *      04.06.00 | 31/07/2012 | mingqing.tang    | N/A | Boot040007
 *      04.10.00 | 07/08/2012 | mingqing.tang    | N/A | Boot040011
 *      04.11.00 | 15/08/2012 | mingqing.tang    | N/A | Boot040012
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_ADPT_UDS_PLATFORM_CFG_H_
#define _BL_ADPT_UDS_PLATFORM_CFG_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief the 11 service save the reset flag.*/
#define ADPT_FINGERPRINT_F15A_FLAGID    (0x03u)
#define ADPT_FINGERPRINT_F15B_FLAGID    (0x05u)
#define ADPT_LATEST_UPDATED_BLOCKID     (0x06u)


#define ADPT_F180_SIZE         			(16u)
#define ADPT_F187_SIZE         			(10u)
#define ADPT_F18C_SIZE         			(10u)
#define ADPT_F193_SIZE         			(15u)
#define ADPT_F198_SIZE         			(10u)
#define ADPT_F199_SIZE         			(4u)


#define ADPT_SESSION_RESPONSE_LEN       (0x04u)

#define ADPT_COMMCONTROLTYPE_DATA       (0x03u)

#define ADPT_MAXNUM_OF_BLOCKLENGTH      (0x202u)
#define ADPT_MAXNUM_OF_TRANS_DATA       (ADPT_MAXNUM_OF_BLOCKLENGTH - 2)

#define ADPT_UDS_TX_HANDLE              (0)
#define ADPT_UDS_TX_TIMEOUT             (200000UL)

#define ADPT_UDS_COMOPS_HANDLE          BL_ERROR_ID_16BIT
#define ADPT_UDS_NUMBER_OF_GATEWAY      (0x01u)
#define ADPT_UDS_CONVERSION_DATA_LENGTH (0x02u)

#define ADPT_STAY_IN_BOOT_RESPONSE_HID  (0xF5u)
#define ADPT_STAY_IN_BOOT_RESPONSE_LID  (0x18u)

#define ADPT_MAX_FRAME_SIZE				8

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

#endif

