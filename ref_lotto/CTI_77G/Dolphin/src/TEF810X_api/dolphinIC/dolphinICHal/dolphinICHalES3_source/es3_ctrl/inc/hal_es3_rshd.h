/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016                                                   */
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

/**
*
* @file hal_es3_rshd.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief Dolphin ES3 shadow register implementation

******************************************************************************/
#include "dolphin_errcodes.h"

#ifdef DOLPHIN_CFG_ES3

#ifndef __HAL_ES3_RSHD_H__
#define __HAL_ES3_RSHD_H__

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */


	void hal_es3_rshd_Init(void);

	void hal_es3_rshd_UpDateShadow(uint8_t moduleaddress, uint16_t regaddress, uint32_t writedata);

	DolphinIC_rval_t hal_es3_rshd_updateFromDev(uint8_t moduleaddress);

	DolphinIC_rval_t hal_es3_rshd_checkRegPage(uint8_t moduleaddress);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* __HAL_ES3_RSHD_H__ */

#endif //DOLPHIN_CFG_ES3


