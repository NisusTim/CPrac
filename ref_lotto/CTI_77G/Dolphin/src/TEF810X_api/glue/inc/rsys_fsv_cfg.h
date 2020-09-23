/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2017                                                   */
/*                                                                              */
/* All rights are reserved. Reproduction in whole or in part is prohibited      */
/* without the prior written consent of the copy-right owner.                   */
/* This source code and any compilation or derivative thereof is the sole       */
/* property of NXP B.V. and is provided pursuant to a Software License          */
/* Agreement. This code is the proprietary information of NXP B.V. and          */
/* is confidential in nature. Its use and dissemination by any party other      */
/* than NXP B.V. is strictly limited by the confidential information            */
/* provisions of the agreement referenced above.                                */
/*                                                                              */
/* NXP reserves the right to make changes without notice at any time.           */
/* NXP makes no warranty, expressed, implied or statutory, including but        */
/* not limited to any implied warranty of merchantability or fitness for any    */
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage        */
/* arising from its use.                                                        */
/*------------------------------------------------------------------------------*/

#ifndef __RSYS_FSV_CFG_H__
#define __RSYS_FSV_CFG_H__

/******************************************************************************
* INCLUDES
*****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* DEFINES
*******************************************************************************/

#define RSYS_CFG_GPIO_ERROR_RESET (77)   //error_reset <- GPIO[77]
#define RSYS_CFG_GPIO_READYINT    (43)   //ready_int -> GPIO[43]
#define RSYS_CFG_GPIO_TX1_PS      (6)    //TX1_PS <- GPIO[6]
#define RSYS_CFG_GPIO_TX2_PS      (7)    //TX2_PS <- GPIO[7]
#define RSYS_CFG_GPIO_TX3_PS      (8)    //TX3_PS <- GPIO[8]
#define RSYS_CFG_GPIO_CHIRP_START (42)   //chirp_start <-> GPIO[42]
#define RSYS_CFG_GPIO_ERROR_N     (80)   //error_n <-> GPIO[80]

#ifdef __cplusplus
}
#endif

#endif /* __RSYS_FSV_CFG_H__ */

