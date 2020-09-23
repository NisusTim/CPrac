/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016													*/
/*																				*/
/* All rights are reserved. Reproduction in whole or in part is prohibited		*/
/* without the prior written consent of the copy-right owner.					*/
/* This source code and any compilation or derivative thereof is the sole		*/
/* property of NXP B.V. and is provided pursuant to a Software License			*/
/* Agreement. This code is the proprietary information of NXP B.V. and			*/
/* is confidential in nature. Its use and dissemination by any party other		*/
/* than NXP B.V. is strictly limited by the confidential information			*/
/* provisions of the agreement referenced above.								*/
/*																				*/
/* NXP reserves the right to make changes without notice at any time.			*/
/* NXP makes no warranty, expressed, implied or statutory, including but		*/
/* not limited to any implied warranty of merchantability or fitness for any	*/
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage		*/
/* arising from its use.														*/
/*------------------------------------------------------------------------------*/

/**
*
* @file hal_es3.h
*
* @ver vX.Y.Z 
*
* @author
*
* @date
*
* @brief
*
*
******************************************************************************/


#ifndef HAL_ES3_H
#define HAL_ES3_H

#include <dolphin_cfg.h>

#ifdef DOLPHIN_CFG_ES3

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <dbgprintf.h>

#include <dolphin_errcodes.h>
#include <glue.h>

#define HAL_ES3_PROFILEID_LUT_MAX (0x04)

///Sweep Control input reference clock
#define HAL_ES3_SC_REF_FREQ     (480.0e6f)

///Sweep Control divider for setting the update rate of the accumulator
#ifdef DOLPHIN_CFG_HOST_S32R274
extern int HAL_ES3_SC_UPDATE_DIV;
#else
#define HAL_ES3_SC_UPDATE_DIV   (6.0f)
#endif

///fixed freqeuncy divider in the feedback loop of PLL
#define HAL_ES3_SC_PRESCALER    (2.0f)

///frequency trippler after the output of LO
#define HAL_ES3_SC_MULTIPLIER   (3.0f)

///the ratio to convert RF freqeuncy to PLL divider value
#define HAL_ES3_SC_FREQ2DIV ( ((float)(1<<26)) / HAL_ES3_SC_REF_FREQ / HAL_ES3_SC_PRESCALER / HAL_ES3_SC_MULTIPLIER)


extern bool g_DbgYieldFlag;

#include <hal_es3_cctrl.h>
#include <hal_es3_atb.h>
#include <hal_es3_gbias.h>
#include <hal_es3_gldo.h>
#include <hal_es3_mclk.h>
#include <hal_es3_lointf.h>
#include <hal_es3_adc.h>
#include <hal_es3_lvds.h>
#include <hal_es3_cif.h>
#include <hal_es3_cafc.h>
#include <hal_es3_sctrl.h>
#include <hal_es3_teng.h>
#include <hal_es3_tx.h>
#include <hal_es3_rx.h>
#include <hal_es3_csi2.h>
#include <hal_es3_ISM.h>
#include <hal_es3_OTP.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */


#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3

#endif /* HAL_ES3_H */


