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
* @file hal_es3_sctrl.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief Sweep control Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_SCTRL_H
#define HAL_ES3_SCTRL_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	typedef struct hal_es3_sctrl_profileparams
	{
		bool downchirp;       // Active chirp Up/Down ...
		uint32_t N_start_int;          // start frequency (integer part) based on the sub-bands selection
		uint32_t N_start_fract;        // start frequency (fraction part) based on the sub-bands selection
		uint32_t DN_chirp;             // Incremental value of frequency divider for each frequency step.
		uint32_t N_step_chirp;         // Number of steps in data acquisition chirp
		uint32_t DN_reset;             // Incremental value of frequency divider for each frequency step in chirp reset mode.
		uint32_t N_step_reset;         // Number of steps in chirp reset mode
		uint32_t Div_update;
	} hal_es3_sctrl_profileparams_t;

	DolphinIC_rval_t hal_es3_sctrl_UpdateProfFreDiv(uint8_t profID, float fStart, float usedBW, bool downChirp, float tReset, float tRamp);

	DolphinIC_rval_t hal_es3_sctrl_CWMode();

	DolphinIC_rval_t hal_es3_sctrl_CompensateChirpStitching();

	DolphinIC_rval_t hal_es3_sctrl_ZeroRamp(uint8_t profID);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_SCTRL_H */

#endif //DOLPHIN_CFG_ES3

