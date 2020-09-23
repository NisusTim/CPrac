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
* @file hal_es3_cctrl.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief Central control Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_CCTRL_H
#define HAL_ES3_CCTRL_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	enum hal_es3_cctrl_modID
	{
		// hal_es3_cctrl_ModID_CCTRL      = 0x0,
		hal_es3_cctrl_ModID_LVDS = 0x2,
		hal_es3_cctrl_ModID_CSI2 = 0x2,
		hal_es3_cctrl_ModID_CIF = 0x2,
		hal_es3_cctrl_ModID_TENG = 0x40,
		hal_es3_cctrl_ModID_SCTRL = 0x40,
		hal_es3_cctrl_ModID_CAFC = 0x40,
		hal_es3_cctrl_ModID_ADC12 = 0x80,
		hal_es3_cctrl_ModID_ADC34 = 0x100,
		hal_es3_cctrl_ModID_GBIAS = 0x200,
		hal_es3_cctrl_ModID_LOINTF = 0x400,
		hal_es3_cctrl_ModID_MCLK = 0x1000,
		hal_es3_cctrl_ModID_RX1 = 0x2000,
		hal_es3_cctrl_ModID_RX2 = 0x4000,
		hal_es3_cctrl_ModID_RX3 = 0x8000,
		hal_es3_cctrl_ModID_RX4 = 0x10000,
		hal_es3_cctrl_ModID_TX1 = 0x20000,
		hal_es3_cctrl_ModID_TX2 = 0x40000,
		hal_es3_cctrl_ModID_TX3 = 0x80000,
		hal_es3_cctrl_ModID_SSBMOD = 0x100000,
		hal_es3_cctrl_ModID_GLDO = 0x200000,
		hal_es3_cctrl_ModID_ATB = 0x400000,
		hal_es3_cctrl_ModID_OTP = 0x800000,
		hal_es3_cctrl_ModID_ISM = 0x1000000,
		hal_es3_cctrl_ModID_ALL = 0xFFFFFFFF
	};
	typedef int32_t hal_es3_cctrl_modID_t;

	enum hal_es3_cctrl_PonClkRst
	{
		hal_es3_cctrl_Pon = 0x00,
		hal_es3_cctrl_ClkEn = 0x01,
		hal_es3_cctrl_Rst = 0x02,
		hal_es3_cctrl_FuncRst = 0x03
	};

	enum hal_es3_cctrl_DynamicPowerMode
	{
		hal_es3_cctrl_None = 0x00,
		hal_es3_cctrl_PerSequence = 0x01,
		hal_es3_cctrl_PerChirp = 0x02,
	};

	DolphinIC_rval_t hal_es3_cctrl_SetPonClkRst(int reg, bool set, uint32_t modList);

	DolphinIC_rval_t hal_es3_cctrl_SetLdoSSBMod(bool enable, uint32_t vout);

	DolphinIC_rval_t hal_es3_cctrl_SetSerialiserMode(int mode);

	DolphinIC_rval_t hal_es3_cctrl_SetATB1MasterSwitch(uint32_t regval);

	DolphinIC_rval_t hal_es3_cctrl_SetDynamicPowerMode(int mode, bool setTx, bool setRx, bool setLo, bool setAdc, bool setChirp, bool setSerializer);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_CCTRL_H */

#endif //DOLPHIN_CFG_ES3
