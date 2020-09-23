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
* @file hal_es3_csi2.h
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief CIF Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_CSI2_H
#define HAL_ES3_CSI2_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	enum hal_es3_csi2_datarate
	{
		HAL_ES3_CSI2_DATARATE_480,     // "00" : 480 Mbps
		HAL_ES3_CSI2_DATARATE_240,     // "01" : 240 Mbps
		HAL_ES3_CSI2_DATARATE_120     //  "10" : 120 Mbps
	};

	typedef uint32_t hal_es3_csi2_DataRate_t;


	DolphinIC_rval_t hal_es3_csi2_Init(void);
	
	/**
	@brief This API configures the CSI-2 interface based on mission profile
	**/
	DolphinIC_rval_t hal_es3_csi2_Config(uint32_t NLanes, hal_es3_csi2_DataRate_t DataRate, bool PDCSyncEnable);

	/**
	@brief see chip_CSI2_CfgTestMode
	@param[in] flag_enable - 0x01 Enable Test mode, 0x00 Disable Test Mode
	@param[in] data_pattern - 0x0000 - 0x0FFF // Fixed pattern
	0x01 // Sine wave as test pattern
	0x02 // Incremental Pattern as test data
	0x03 // Incremental Pattern as test data
	**/
	DolphinIC_rval_t hal_es3_csi2_CfgTestMode(bool flag_enable, uint16_t data_pattern, uint8_t test_mode_sel);
	DolphinIC_rval_t hal_es3_csi2_getMCLKOutFrequency(float * p_freqcountrval);
	DolphinIC_rval_t hal_ES3_CSI2_Datatoggle_Disable(void);
	DolphinIC_rval_t hal_ES3_CSI2_Datatoggle_Enable(void);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_CSI2_H */

#endif //DOLPHIN_CFG_ES3

