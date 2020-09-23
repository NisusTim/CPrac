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
* @file hal_es3_rx.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief RX Low-Level Interface.
*
*
******************************************************************************/
#include <math.h>
#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_Rx.h>

#if defined(__cplusplus)
extern "C"
{
#endif

	DolphinIC_rval_t hal_es3_rx_ProfileConfig(int RXNum, int ProfileNum, uint8_t rxGain, float LPF6dBCutOffHz, float HPF6dBCutOffHz, bool RMSDetOn)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t RX_MODULE_ADDRESS = RX1_MODULE_ADDRESS;
		uint16_t G_RX_SET_PROFILE = 0x00;
		uint16_t LPF_RX_SET_PROFILE = 0x00;
		uint16_t HPF_RX_SET_PROFILE = 0x00;

//		uint32_t reg_val = 0x00;
		uint32_t LPF_RX_FINE_SET = 0;
		uint32_t LPF_RX_CORNER_SET = 0x03;
		uint32_t LPF_RX_SET = 0;

		float HPFConvertedHz;
		uint32_t HPF_RX_SET;
		Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t		RXgSet;
		Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t	RXLpfSet;
		Nxp_Tef810x_Mod0D_HpfRxSetProfileUnion_t	RXHpfSet;
		Nxp_Tef810x_Mod0D_RmsControlUnion_t			RXRmsCtrl;
//		Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t FuncsafeMonLevelLo;

		HAL_GERRCODE_INIT;

		//select Rx channel.
		switch (RXNum)
		{
		case 2:
			RX_MODULE_ADDRESS = RX2_MODULE_ADDRESS;
			break;
		case 3:
			RX_MODULE_ADDRESS = RX3_MODULE_ADDRESS;
			break;
		case 4:
			RX_MODULE_ADDRESS = RX4_MODULE_ADDRESS;
			break;
		default:
			RX_MODULE_ADDRESS = RX1_MODULE_ADDRESS;
			break;
		}

		switch (ProfileNum)
		{
		case 1:
			G_RX_SET_PROFILE = NXP_TEF810X_MOD0D_G_RX_SET_PROFILE1_U16;
			LPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE1_U16;
			HPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE1_U16;
			break;
		case 2:
			G_RX_SET_PROFILE = NXP_TEF810X_MOD0D_G_RX_SET_PROFILE2_U16;
			LPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE2_U16;
			HPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE2_U16;
			break;
		case 3:
			G_RX_SET_PROFILE = NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16;
			LPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16;
			HPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE3_U16;
			break;
		default:
			G_RX_SET_PROFILE = NXP_TEF810X_MOD0D_G_RX_SET_PROFILE0_U16;
			LPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE0_U16;
			HPF_RX_SET_PROFILE = NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE0_U16;
			break;
		}

		// Rx Gain setting
		// Rd-Mod-Wr
		glue_reg_Read(RX_MODULE_ADDRESS, G_RX_SET_PROFILE, &RXgSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RXgSet.bits_st.GainRxSetProfile0 = rxGain;

		glue_reg_WriteCheck(RX_MODULE_ADDRESS, G_RX_SET_PROFILE, RXgSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// LPF settings
		if (LPF6dBCutOffHz <= 3.75e6f)
		{
			// set to minimal cutoff, 3.75MHz
			//choose narrow band
			LPF_RX_SET = 0x00;
			//choose rough corner
			LPF_RX_CORNER_SET = 0x00;
			//fine control
			LPF_RX_FINE_SET = 0xF;
		}
		else if ((LPF6dBCutOffHz > 3.75e6f && LPF6dBCutOffHz <= 7.5e6f))
		{
			//choose narrow band
			LPF_RX_SET = 0x00;
			//choose rough corner
			LPF_RX_CORNER_SET = 0x00;
			//fine control
			//Note: cutoff frequency in the middle (with fineset tuning) is not validated. (only when fineset = 0 is calibrated with RCTrim)
			LPF_RX_FINE_SET = (uint32_t)(roundf((7.5e6f / LPF6dBCutOffHz - 1) * 16));
		}
		else if ((LPF6dBCutOffHz > 7.5e6f && LPF6dBCutOffHz <= 10e6f))
		{
			//choose narrow band
			LPF_RX_SET = 0x00;
			//choose rough corner
			LPF_RX_CORNER_SET = 0x01;
			//fine control
			//Note: cutoff frequency in the middle (with fineset tuning) is not validated. (only when fineset = 0 is calibrated with RCTrim)
			LPF_RX_FINE_SET = (uint32_t)(roundf((10.0e6f / LPF6dBCutOffHz - 1) * 16));
		}
		else if ((LPF6dBCutOffHz > 10.0e6f && LPF6dBCutOffHz <= 12.5e6f))
		{
			//choose narrow band
			LPF_RX_SET = 0x00;
			//choose rough corner
			LPF_RX_CORNER_SET = 0x02; //10b
			//fine control
			//Note: cutoff frequency in the middle (with fineset tuning) is not validated. (only when fineset = 0 is calibrated with RCTrim)
			LPF_RX_FINE_SET = (uint32_t)(roundf((12.5e6f / LPF6dBCutOffHz - 1) * 16));
		}
		else if ((LPF6dBCutOffHz > 12.5e6f && LPF6dBCutOffHz <= 15e6f))
		{
			//choose narrow band
			LPF_RX_SET = 0x00;
			//choose rough corner
			LPF_RX_CORNER_SET = 0x03; //11b
			//fine control
			//Note: cutoff frequency in the middle (with fineset tuning) is not validated. (only when fineset = 0 is calibrated with RCTrim)
			LPF_RX_FINE_SET = (uint32_t)(roundf((15.0e6f / LPF6dBCutOffHz - 1) * 16));
		}
		else
		{
			//choose wide band
			LPF_RX_SET = 0x01;
			LPF_RX_CORNER_SET = 0;
			LPF_RX_FINE_SET = 0xF;
		}

		//Rd-Mod-Wr
		glue_reg_Read(RX_MODULE_ADDRESS, LPF_RX_SET_PROFILE, &RXLpfSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RXLpfSet.bits_st.LpfRxSetProfile0 = LPF_RX_SET;
		RXLpfSet.bits_st.LpfRxCornerSetProfile0 = LPF_RX_CORNER_SET;
		RXLpfSet.bits_st.LpfRxFineSetProfile0 = LPF_RX_FINE_SET;

		//write LPF settings
		glue_reg_WriteCheck(RX_MODULE_ADDRESS, LPF_RX_SET_PROFILE, RXLpfSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//****HPF settings****************************************************
		//convert input to integer multiples of 100kHz
		//The following way of implementation is to keep the API signature compatible to ES1
		//since for ES1, the HPF is set using direct fine setting, but ES2 uses a limited list of settings.
		HPFConvertedHz = roundf(HPF6dBCutOffHz / 100e3f) * 100e3f;
		HPF_RX_SET = 0x00;
		if (HPFConvertedHz <= 100e3f)
		{
			//for ( ,150)kHz HPF6dBCutOffHz
			HPF_RX_SET = 0;
		}
		else if (HPFConvertedHz <= 400e3f)
		{
			//for [150,450kHz) HPF6dBCutOffHz, calculate setting
			HPF_RX_SET = (uint32_t)HPFConvertedHz / (uint32_t)100e3f - 1;
		}
		else if (HPFConvertedHz <= 600e3f)
		{
			//for [450,650) kHz HPF6dBCutOffHz, set to 400KHz cutoff.
			HPF_RX_SET = 3;
		}
		else if (HPFConvertedHz <= 1200e3f)
		{
			//for [650,1250) kHz HPF6dBCutOffHz, set to 800KHz cutoff.
			HPF_RX_SET = 4;
		}
		else
		{
			//for 1250kHz and higher HPF6dBCutOffHz, set to 1600KHz cutoff.
			HPF_RX_SET = 5;
		}

		//Rd-Mod-Wr
		glue_reg_Read(RX_MODULE_ADDRESS, HPF_RX_SET_PROFILE, &RXHpfSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RXHpfSet.bits_st.HpfRxSetProfile0 = HPF_RX_SET;
		//write HPF setting
		glue_reg_WriteCheck(RX_MODULE_ADDRESS, HPF_RX_SET_PROFILE, RXHpfSet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//RMS detector setting
		//Rd-Mod-Wr
		glue_reg_Read(RX_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, &RXRmsCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RXRmsCtrl.bits_st.LevelLoEnSpi = RMSDetOn;
		glue_reg_WriteCheck(RX_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, RXRmsCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_rx_SetLoLevel(double effFc)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t RX_MODULE_ADDRESS = RX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t FuncsafeMonLevelLo;

		int RXNum = 1;

		HAL_GERRCODE_INIT;

		for (RXNum = 1; RXNum < 5; RXNum++)
		{
			//select Rx channel.
			switch (RXNum)
			{
			case 1:
				RX_MODULE_ADDRESS = RX1_MODULE_ADDRESS;
				break;
			case 2:
				RX_MODULE_ADDRESS = RX2_MODULE_ADDRESS;
				break;
			case 3:
				RX_MODULE_ADDRESS = RX3_MODULE_ADDRESS;
				break;
			case 4:
				RX_MODULE_ADDRESS = RX4_MODULE_ADDRESS;
				break;
			default:
				RX_MODULE_ADDRESS = RX1_MODULE_ADDRESS;
				break;
			}


			glue_reg_Read(RX_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, &FuncsafeMonLevelLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//set LO monitor levels
			FuncsafeMonLevelLo.bits_st.LevelLoMinSpi = 0x1;
			if (effFc > 76e9f && effFc <= 78e9f)
				FuncsafeMonLevelLo.bits_st.LevelLoLowSpi = 0xA;
			else if (effFc > 78e9f && effFc < 81e9f)
				FuncsafeMonLevelLo.bits_st.LevelLoLowSpi = 0x7;
			FuncsafeMonLevelLo.bits_st.LevelLoHighSpi = 0x0;
			FuncsafeMonLevelLo.bits_st.LevelLoMaxSpi = 0x8;

			glue_reg_WriteCheck(RX_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, FuncsafeMonLevelLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			
		}

		return HAL_GERRCODE;
	}

#if defined(__cplusplus)
}
#endif

#endif //DOLPHIN_CFG_ES3
