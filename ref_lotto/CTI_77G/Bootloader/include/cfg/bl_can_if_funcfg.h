/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the can_if module.
 *
 *  \file       bl_can_if_cfg.h
 *  \ingroup    flash_if_manager_module
 *  \author     haiping.wang <haiping.wang@hirain.com>
 *
 *  \version    5.2.1
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      02.00.00 | 20/08/2013 | haiping.wang     | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *      05.02.01 | 21/08/2014 | mingqing.tang    | N/A | BootSpec050002
 *
******************************************************************************/
#ifndef _BL_CAN_IF_FUNCFG_H_
#define _BL_CAN_IF_FUNCFG_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief The canid can be set by other module.*/
#define CANIF_FUN_DYNAMIC_CANID             BL_FUN_ON

#if !defined(OPTION_CUSTOMER_ID)
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_ON
#elif (OPTION_CUSTOMER_ID == 0)   //Hirain-FAW, need compatible with Neusoft
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_ON
#elif (OPTION_CUSTOMER_ID == 1)   //Neusoft, need compatible with Hirain
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_ON
#elif (OPTION_CUSTOMER_ID == 3)   //Hirain-CNHTC, need compatible with Hirain
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_ON
#elif (OPTION_CUSTOMER_ID == 4)   //TSINTEL-CNHTC
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_OFF
#else
#define CANIF_FUN_CANID_IN_PARAMETERS       BL_FUN_ON
#endif

/** \brief The can controller is full can.*/
#define CANIF_FUN_FULL_CAN_CONTROLLER       BL_FUN_OFF
/** \brief The can transeciver whether need be initialized.*/
#define CANIF_FUN_INIT_TRANSCEIVER          BL_FUN_ON
/** \brief The can IF whether use 29bits id*/
#define CANIF_FUN_EXTERNED_ID               BL_FUN_OFF
/** \brief The number of controller used by can IF module.*/
#define CANIF_USED_CONTROLLER_NUM           (0x01u)

#define CANIF_PHY_RX_HANDLE                 (0x00u)
#define CANIF_TX_HANDLE                     (0x00u)

#if !defined(OPTION_CUSTOMER_ID)
#define CANIF_PHY_M_RX_CANID                (0x7a0UL)
#define CANIF_PHY_M_TX_CANID                (0x7a8UL)
#define CANIF_PHY_C_RX_CANID                (0x7b0UL)
#define CANIF_PHY_C_TX_CANID                (0x7b8UL)
#elif (OPTION_CUSTOMER_ID == 0)   //Hirain-FAW, need compatible with Neusoft
#define CANIF_PHY_M_RX_CANID                (0x7a0UL)
#define CANIF_PHY_M_TX_CANID                (0x7a8UL)
#define CANIF_PHY_C_RX_CANID                (0x7b0UL)
#define CANIF_PHY_C_TX_CANID                (0x7b8UL)
#elif (OPTION_CUSTOMER_ID == 1)   //Neusoft, need compatible with Hirain
#define CANIF_PHY_M_RX_CANID                (0x7b0UL)
#define CANIF_PHY_M_TX_CANID                (0x7b8UL)
#define CANIF_PHY_C_RX_CANID                (0x7a0UL)
#define CANIF_PHY_C_TX_CANID                (0x7a8UL)
#elif (OPTION_CUSTOMER_ID == 3)   //Hirain-CNHTC, need compatible with Hirain
#define CANIF_PHY_M_RX_CANID                (0x7a0UL)
#define CANIF_PHY_M_TX_CANID                (0x7a8UL)
#define CANIF_PHY_C_RX_CANID                (0x7b0UL)
#define CANIF_PHY_C_TX_CANID                (0x7b8UL)
#elif (OPTION_CUSTOMER_ID == 4)   //TSINTEL-CNHTC
#define CANIF_PHY_M_RX_CANID                (0x7c1UL)
#define CANIF_PHY_M_TX_CANID                (0x7c9UL)
#define CANIF_PHY_C_RX_CANID                (0x7c1UL)
#define CANIF_PHY_C_TX_CANID                (0x7c9UL)
#else
#define CANIF_PHY_M_RX_CANID                (0x7a0UL)
#define CANIF_PHY_M_TX_CANID                (0x7a8UL)
#define CANIF_PHY_C_RX_CANID                (0x7b0UL)
#define CANIF_PHY_C_TX_CANID                (0x7b8UL)
#endif

#define CANIF_FUN_RX_CANID                  (0x7dfUL)

#endif

