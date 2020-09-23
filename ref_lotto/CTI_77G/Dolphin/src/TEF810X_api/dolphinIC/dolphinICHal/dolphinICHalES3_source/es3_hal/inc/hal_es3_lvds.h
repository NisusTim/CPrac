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
* @file hal_es3_lvds.h
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief LVDS Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_LVDS_H
#define HAL_ES3_LVDS_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_lvds_Init(float initOutClkFreq);

	DolphinIC_rval_t hal_es3_lvds_CfgMode(bool SyncToPosEdgeBitClk, bool SyncToNegEdgeFrameClk, bool msbFirst, bool PDCSyncEnable);

	DolphinIC_rval_t hal_es3_lvds_CfgTestMode(void);

	DolphinIC_rval_t hal_es3_lvds_CfgWindowActSel(bool SetToActive);

	DolphinIC_rval_t hal_es3_lvds_getMCLKOutFrequency(float * p_freqcountrval);
	DolphinIC_rval_t hal_ES3_LVDS_Datatoggle_Disable(void);
	DolphinIC_rval_t hal_ES3_LVDS_Datatoggle_Enable(void);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_LVDS_H */

#endif //DOLPHIN_CFG_ES3
