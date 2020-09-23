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
* @file hal_es3_tx.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief Transmitters Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_TX_H
#define HAL_ES3_TX_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	//temperature information for TX gain calibration: 0: COLD (<25C), 1: ROOM (25C< & <90C), 2: HOT (90C<)
	extern uint8_t txGainTemperatureBin;

	DolphinIC_rval_t hal_es3_tx_Control(int TXNum, bool BPSExtControlEn, bool SPI_BPSEn, bool SPI_SWEn, bool SPI_TXEn);

	/**
	@brief	Function to correct the TX level monitor thresholds based on desired Parp
			If threshold to be corrected is Min, always writes '1'.
			This function re-calculates the threshold values from the original OTP max threshold value everytime it is called.

	@param[in] TXNum : TX#, 1,2 or 3
	@param[in] typeTh : Threshold types: 0:Min, 1:Low, 2:High, 3:Max
	@param[in] targetParp : Desired output at antenna reference plane
	**/
	DolphinIC_rval_t hal_es3_tx_CorrectThresholdsParp(int TXNum, uint8_t typeTh, float targetParp);

	/**
	@brief	Function to correct the TX level monitor thresholds based on the desired temperature of operation
	If threshold to be corrected is Min, no effect.

	@param[in] TXNum : TX#, 1,2 or 3
	@param[in] typeTh : Threshold types: 0:Min, 1:Low, 2:High, 3:Max
	@param[in] temp : Operation temperature that the thresholds will be corrected 
	@param[in] effFC : effective center frequency of a chirp (Hz)
	**/
	DolphinIC_rval_t hal_es3_tx_CorrectThresholdsTemperature(int TXNum, uint8_t typeTh, float temp, double effFc);

	int hal_es3_tx_CalculateThreshold(float targetParp);

	DolphinIC_rval_t hal_es3_tx_fPCtrl_CorrectTxGain(uint8_t txNumb);
	DolphinIC_rval_t hal_es3_tx_fPCtrl_CorrectTxGain_Cubtek(uint8_t txNumb, bool txsw[4][3], uint8_t gain_count[4][3]);

	//initial calibration of high threshold
	DolphinIC_rval_t hal_es3_tx_fPCtrl_SetHighThreshold_CubTek(uint8_t txNumb, uint16_t txGain, uint8_t txProfile, uint8_t *txLevel);
	DolphinIC_rval_t hal_es3_tx_fPCtrl_SetHighThreshold(uint8_t txNumb, uint16_t txGain);

	DolphinIC_rval_t hal_es3_tx_fPCtrl_AdjustHighThreshold(uint8_t txNumb, float temperature);

	DolphinIC_rval_t hal_es3_tx_fPCtrl_CalibTxGain(uint8_t txNumb);
	DolphinIC_rval_t hal_es3_tx_fPCtrl_CalibTxGain_Cubtek(bool txOn[3], uint8_t profile, uint8_t gain_count[3]);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_TX_H */

#endif //DOLPHIN_CFG_ES3

