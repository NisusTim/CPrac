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
* @file hal_es3_teng.h
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief Timing Engine Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_TENG_H
#define HAL_ES3_TENG_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */


	/**
	@brief Configures TE profiles with chirp info (based on mission profile)
	**/
	DolphinIC_rval_t hal_es3_teng_UpdateProfChirpPeriod(uint8_t profID, uint8_t txActiveNum, uint8_t rxSwNum, float tChirp);

	/**
	@brief Configures TE profiles with timing info (based on mission profile)
	**/
	DolphinIC_rval_t hal_es3_teng_UpdateProfTiming(uint8_t profID, float tDwell, bool txBPSFastSWCtrlPointSettle, float txBPSFastSWTime, uint8_t BPSCtrlBits, uint8_t txControlBits);

	/**
	@brief Configures profiles with ADC related settings (based on mission profile)
	**/
	DolphinIC_rval_t hal_es3_teng_UpdateProfADC(uint8_t profID, float tSettle,	uint32_t numSample,	uint8_t PDCDecimation, bool PDC_bw);

	/**
	@brief Configures the jumpback time
	**/
	DolphinIC_rval_t hal_es3_teng_CfgTJumpBack(float tJumpback);

	/**
	@brief Configures number of chirps per sequence and number of sequences
	**/
	DolphinIC_rval_t hal_es3_teng_CfgNumChirpSeq(uint8_t numSeq, uint16_t numChirp);

	/**
	@brief Configures the chirp sequence interval
	**/
	DolphinIC_rval_t hal_es3_teng_CfgSeqInterval(float tseqinterval);

	/**
	@brief Configures chirp profile in Timing Engine
	**/
	DolphinIC_rval_t hal_es3_teng_CfgChirpProfile(uint8_t profselect, uint32_t profstaycount, bool profReset);

	/**
	@brief see chip_TE_ChirpTrigMode
	**/
	DolphinIC_rval_t hal_es3_teng_CfgChirpTriggerMode(uint8_t ReadyIntMode, uint8_t CSI2FrameMode, bool ChirpPowerMode, bool ChirpStartToggleOnChirpLevel, bool SyncExtTrig, bool UseExtTrigger);

	/**
	@brief see chip_TE_ChirpStart
	**/
	DolphinIC_rval_t hal_es3_teng_StartChirp(void);

	/**
	@brief Configures ISM active and DC power-on delays
	**/
	DolphinIC_rval_t hal_es3_teng_CfgDCPowOnDelay(float TEDelay, float ISMDealy);

	/**
	@brief Configures RX power on delay
	**/
	DolphinIC_rval_t hal_es3_teng_CfgRXPowOnDelay(float rxDelay);

	/**
	@brief Configures TX power on delay
	**/
	DolphinIC_rval_t hal_es3_teng_CfgTXPowOnDelay(float txDelay);

	/**
	@brief Configures TX fast switch
	**/
	DolphinIC_rval_t hal_es3_teng_CfgChirpFastSwitchCtrl(bool enFastSW, float fastResetDuration);

	DolphinIC_rval_t hal_es3_teng_WaitForReady(void);

	/**
	@brief Configures load profile
	**/

	DolphinIC_rval_t hal_es3_teng_LoadProfile(uint8_t profID);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_TENG_H */

#endif //DOLPHIN_CFG_ES3

