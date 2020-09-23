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
* @file hal_es3_tx.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief TX Low-Level Interface.
*
*
******************************************************************************/

#include <hal_es3.h>
#include <hal_es3_ctrl.h>
#include <math.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_Tx.h>
#include <es3/NXP_TEF810X_ISM.h>
#include <es3/NXP_TEF810X_TimingEngine.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	uint8_t txGainTemperatureBin = 1;

	DolphinIC_rval_t hal_es3_tx_Control(int TXNum, bool BPSExtControlEn, bool SPI_BPSEn, bool SPI_SWEn, bool SPI_TXEn)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod11_TxControlUnion_t TxControl_ust;

		HAL_GERRCODE_INIT;

		//select Tx channel.
		switch (TXNum)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_TX_CONTROL_U16, &TxControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TxControl_ust.bits_st.EnPsExtSpi = BPSExtControlEn;
		TxControl_ust.bits_st.EnTxViaSpi = SPI_TXEn;
		TxControl_ust.bits_st.SwTxViaSpi = SPI_SWEn;
		TxControl_ust.bits_st.PsTxViaSpi = SPI_BPSEn;

		glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_TX_CONTROL_U16, TxControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_tx_CorrectThresholdsParp(int TXNum, uint8_t typeTh, float targetParp)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
//		Nxp_Tef810x_Mod11_TxControlUnion_t TxControl_ust;

		HAL_GERRCODE_INIT;
		
		//select Tx channel.
		switch (TXNum)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		if (typeTh == 0)
		{
		
			FuncsafeMonLevelRf.bits_st.LevelRfMinSpi = 1;
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		else if (typeTh == 1)
		{
			
			FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = hal_es3_tx_CalculateThreshold(targetParp);
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}

		else if (typeTh == 2)
		{

			FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = hal_es3_tx_CalculateThreshold(targetParp);
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}

		else if (typeTh == 3)
		{
			glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			FuncsafeMonLevelRf.bits_st.LevelRfMaxSpi = hal_es3_tx_CalculateThreshold(targetParp);
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}

		else HAL_GEC_ASSERT(DOLPHINIC_EC_INPUTOUTOFRANGE);



		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_tx_CorrectThresholdsTemperature(int TXNum, uint8_t typeTh, float temp, double effFc)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		//frequency table, 1 row per TX (currently all the same)
		const float effFcBoundary[3][5] = {
			{ 77e9f, 78e9f, 79e9f, 80e9f, 81e9f },
			{ 77e9f, 78e9f, 79e9f, 80e9f, 81e9f },
			{ 77e9f, 78e9f, 79e9f, 80e9f, 81e9f } };

		const uint8_t numFreqSections = sizeof(effFcBoundary[0])/sizeof(effFcBoundary[0][0]);

		//TX RF level high compensation LUT, 5freq*3TX = 15rows, 3 temperatures
		const int8_t TXRFLowComp[15][3] = { 
			{ -3, -2, -1 },
			{ -3, -1, -1 },
			{ -2, -1,  0 },
			{ -2, -1,  0 },
			{ -2, -1,  1 },
			{ -3, -2, -1 },
			{ -3, -2, -1 },
			{ -2, -1,  0 },
			{ -3, -2,  0 },
			{ -3, -1,  0 },
			{ -2, -3, -2 },
			{ -2, -2, -1 },
			{ -2, -2, -1 },
			{ -2, -2, -1 },
			{ -1, -1,  0 } };
		//TX RF level high compensation LUT
		const int8_t TXRFHighComp[15][3] = { 
			{ -3, -2, -1},
			{ -3, -2, -1},
			{ -2, -1,  0},
			{ -2, -1,  0},
			{ -2, -1,  1},
			{ -3, -2, -1},
			{ -3, -2, -1},
			{ -3, -2,  0},
			{ -4, -2,  0},
			{ -3, -2,  0},
			{ -3, -3, -2},
			{ -3, -3, -1},
			{ -2, -2, -1},
			{ -3, -3, -1},
			{ -2, -2,  0} };

		int8_t RFLevelCorrected = 0;

		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
//		Nxp_Tef810x_Mod11_TxControlUnion_t TxControl_ust;
		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
	
		int row = 0;
		int col = 0;

		HAL_GERRCODE_INIT;

		//select Tx channel.
		switch (TXNum)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		// Select the row offset according to frequency
		for (int j = 0; j < numFreqSections; j++)
		{
			if (effFc <= effFcBoundary[TXNum - 1][j])
			{
				row = numFreqSections * (TXNum - 1) + j;
				break;
			}
		}

		// Select the column offset according to temperature
		if (temp < 25)
		{
			col = 0;
		}
		else if (temp < 90)
		{
			col = 1;
		}
		else if (temp <= 135)
		{
			col = 2;
		}
		else
		{
			col = 2;
			DbgErr("Temperature input is higher than 135 degC!\n");
		}

		// read out TX RF level thresholds
		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//compensate chosen RF level threshold
		if (typeTh == 1) //level low
		{
			RFLevelCorrected = FuncsafeMonLevelRf.bits_st.LevelRfLowSpi + TXRFLowComp[row][col];

			//clipping
			FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = RFLevelCorrected < 0 ? 0 : RFLevelCorrected;
			//level low is 6bit, but only lowest 4bits are used.
			FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = RFLevelCorrected > 15 ? 15 : RFLevelCorrected;

			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		else if (typeTh == 2) //level high
		{
			RFLevelCorrected = FuncsafeMonLevelRf.bits_st.LevelRfHighSpi + TXRFHighComp[row][col];

			//clipping
			FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = RFLevelCorrected < 0 ? 0 : RFLevelCorrected;
			//level high is 6bits, but only lowest 4bits are used.
			FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = RFLevelCorrected > 15 ? 15 : RFLevelCorrected;

			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		else
		{
			DbgInfo("Chosen TX RF Min or Max threshold doesn't need any compensation!\n");
		}

		return HAL_GERRCODE;
	}
	DolphinIC_rval_t hal_es3_tx_fPCtrl_CalibTxGain(uint8_t txNumb)
	{
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust;
//		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
		bool TxHighFlag = false;

		HAL_GERRCODE_INIT;
		switch (txNumb)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, &GTxGainProfile_ust.val_u32, NULL);
		GTxGainProfile_ust.bits_st.GTxGainProfile0 = 0;

		do {
			
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, GTxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			switch (txNumb)
			{
			case 2:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
				break;
			case 3:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
				break;
			default:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
				break;
			}

			GTxGainProfile_ust.bits_st.GTxGainProfile0++;

		} while ((TxHighFlag == false) && (GTxGainProfile_ust.bits_st.GTxGainProfile0 < 0x80)); 
		
		
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_CalibTxGain_Cubtek(bool txOn[3], uint8_t profile, uint8_t gain_count[3])
	{
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust;
	//	Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			globalCtrl;
		bool TxHighFlag = false;

		uint32_t	gain_profileReg;
//		uint32_t	globalCtrlbackup;
		uint8_t		tx_index;

		HAL_GERRCODE_INIT;

		switch (profile)
		{
		case 0x00:
			gain_profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		case 0x01:
			gain_profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
			break;
		case 0x02:
			gain_profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
			break;
		case 0x03:
			gain_profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
			break;
		default:
			gain_profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		}

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
//		globalCtrlbackup = globalCtrl.val_u32;

		// change current mode to single profile mode for TX gain calib
		globalCtrl.bits_st.ChirpProfileSelect = profile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, &GTxGainProfile_ust.val_u32, NULL);
		GTxGainProfile_ust.bits_st.GTxGainProfile0 = 0;

		for (tx_index = 0x00; tx_index < 0x03; tx_index++)
		{
			if (txOn[tx_index] == false)
				continue;
			switch (tx_index)
			{
			case 1:
				TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
				break;
			case 2:
				TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
				break;
			default:
			    TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
				break;
			}

		do {
			gain_count[tx_index] = (uint8_t)GTxGainProfile_ust.bits_st.GTxGainProfile0;
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, gain_profileReg, GTxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			switch (tx_index)
			{
			case 1:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
				break;
			case 2:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
				break;
			default:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
				break;
			}

			GTxGainProfile_ust.bits_st.GTxGainProfile0++;

		} while ((TxHighFlag == false) && (GTxGainProfile_ust.bits_st.GTxGainProfile0 < 0xFF));

		}
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_CorrectTxGain_Cubtek(uint8_t txNumb, bool txsw[4][3], uint8_t gain_count[4][3])
	{
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
		bool TxHighFlag = false;
		uint8_t profile = 0;
		uint16_t profileReg = 0x00;


		HAL_GERRCODE_INIT;
		if (txNumb > 3)
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
		//loop through TX_profile
		for (profile = 0x00; profile < 0x04; profile++)
		{
			if(txsw[profile][txNumb-1])
			{
				switch (profile)
				{
				case 0x00:
					profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
					break;
				case 0x01:
					profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
					break;
				case 0x02:
					profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
					break;
				case 0x03:
					profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
					break;
				default:
					profileReg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
					break;
				}

				switch (txNumb)
				{
				case 2:
					TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
					break;
				case 3:
					TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
					break;
				default:
					TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
					break;
				}

				glue_reg_Read(TX_MODULE_ADDRESS, profileReg, &GTxGainProfile_ust.val_u32, NULL);

				glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				switch (txNumb)
				{
				case 2:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					break;
				case 3:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					break;
				default:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					break;
				}

				if (TxHighFlag == false)
				{
					if (GTxGainProfile_ust.bits_st.GTxGainProfile0 < 0xFF)
					{
						GTxGainProfile_ust.bits_st.GTxGainProfile0++;
						glue_reg_WriteCheck(TX_MODULE_ADDRESS, profileReg, GTxGainProfile_ust.val_u32, NULL);
						HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					}
					else
					{
						/*max TX gain reached*/
					}
				}
				else
				{
					if (GTxGainProfile_ust.bits_st.GTxGainProfile0 > 0x00)
					{
						GTxGainProfile_ust.bits_st.GTxGainProfile0--;
						glue_reg_WriteCheck(TX_MODULE_ADDRESS, profileReg, GTxGainProfile_ust.val_u32, NULL);
						HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					}
					else
					{
						/*min TX gain reached*/
					}
				}
			}
		}
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_CorrectTxGain(uint8_t txNumb)
	{
		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust;
//		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
		bool TxHighFlag = false;

		HAL_GERRCODE_INIT;
		switch (txNumb)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, &GTxGainProfile_ust.val_u32, NULL);

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (txNumb)
		{
		case 2:
			TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
			break;
		case 3:
			TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
			break;
		default:
			TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
			break;
		}

		if (TxHighFlag == false)
		{
			if (GTxGainProfile_ust.bits_st.GTxGainProfile0 < 0x80)
			{
				GTxGainProfile_ust.bits_st.GTxGainProfile0++;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, GTxGainProfile_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}
			else
			{
				/*max TX gain reached*/
			}
		}
		else
		{
			if (GTxGainProfile_ust.bits_st.GTxGainProfile0 > 0x00)
			{
				GTxGainProfile_ust.bits_st.GTxGainProfile0--;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, GTxGainProfile_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}
			else
			{
				/*min TX gain reached*/
			}
		}


		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_SetHighThreshold_CubTek(uint8_t txNumb, uint16_t txGain, uint8_t txProfile, uint8_t *txLevel) {

			uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			uint16_t TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			bool TxHighFlag = false;
			Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_temp, ChirpGlobalControl_ust;
			Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_temp, GTxGainProfile_ust;
			Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf_temp, FuncsafeMonLevelRf;
			Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;

			HAL_GERRCODE_INIT;
			switch (txNumb)
			{
			case 2:
				TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
				break;
			case 3:
				TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
				break;
			default:
				TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
				break;
			}

			switch (txProfile)
			{
			case 0x00:
				TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
				break;
			case 0x01:
				TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
				break;
			case 0x02:
				TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
				break;
			case 0x03:
				TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
				break;
			default:
				TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
				break;
			}

			glue_reg_Read(TX_MODULE_ADDRESS, TX_PROFILE_REG_ADDRESS, &GTxGainProfile_ust.val_u32, NULL);  //set tx gain code.
			GTxGainProfile_temp.val_u32 = GTxGainProfile_ust.val_u32;  //store value for recover

			GTxGainProfile_ust.bits_st.GTxGainProfile0 = txGain;
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, TX_PROFILE_REG_ADDRESS, GTxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
			ChirpGlobalControl_temp.val_u32 = ChirpGlobalControl_ust.val_u32;  //store value for recover

			ChirpGlobalControl_ust.bits_st.ChirpProfileSelect = txProfile;  //set chirp profile.
			ChirpGlobalControl_ust.bits_st.ProfileStayCountVal = 64;  //set repeat time value.

			glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);  //get tx level code.
			FuncsafeMonLevelRf_temp.val_u32 = FuncsafeMonLevelRf.val_u32;  //store value for recover

			//set the HIGH threshold to max value
			FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = 0x0;

			do {

				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);

				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_teng_StartChirp();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();

				glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				switch (txNumb)
				{
				case 2:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					break;
				case 3:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					break;
				default:
					TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					break;
				}
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi++;
			} while ((TxHighFlag == true) && (FuncsafeMonLevelRf.bits_st.LevelRfHighSpi < 0xF));

			*txLevel = (uint8_t)FuncsafeMonLevelRf.bits_st.LevelRfHighSpi;  //save found tx high level code.

			//recover value.
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf_temp.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_temp.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_WriteCheck(TX_MODULE_ADDRESS, TX_PROFILE_REG_ADDRESS, GTxGainProfile_temp.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;

		}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_SetHighThreshold(uint8_t txNumb, uint16_t txGain) {

		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
//		uint16_t TX_PROFILE_REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
		bool TxHighFlag = false;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust; 
		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;
		switch (txNumb)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, &GTxGainProfile_ust.val_u32, NULL);

		GTxGainProfile_ust.bits_st.GTxGainProfile0 = txGain;
		glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, GTxGainProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);

		//set the HIGH threshold to max value
		FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = 0x0;

		do {
			
			glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);

			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			switch (txNumb)
			{
			case 2:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
				break;
			case 3:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
				break;
			default:
				TxHighFlag = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
				break;
			}
			FuncsafeMonLevelRf.bits_st.LevelRfHighSpi++;
		} while ((TxHighFlag == true) && (FuncsafeMonLevelRf.bits_st.LevelRfHighSpi < 0xF));

		return HAL_GERRCODE;

	}

	DolphinIC_rval_t hal_es3_tx_fPCtrl_AdjustHighThreshold(uint8_t txNumb, float temperature) {

		uint8_t TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
//		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile_ust;
		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;
//		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
		uint8_t temperatureBin = 1;

		HAL_GERRCODE_INIT;
		switch (txNumb)
		{
		case 2:
			TX_MODULE_ADDRESS = TX2_MODULE_ADDRESS;
			break;
		case 3:
			TX_MODULE_ADDRESS = TX3_MODULE_ADDRESS;
			break;
		default:
			TX_MODULE_ADDRESS = TX1_MODULE_ADDRESS;
			break;
		}
		
		if (temperature < 25)
			temperatureBin = 0;
		else if (temperature < 90)
			temperatureBin = 1;
		else
		{
			temperatureBin = 2;
		}

		glue_reg_Read(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);

		switch (txGainTemperatureBin)
		{
		case 0:
			if (temperatureBin == 0)
			{
			}
			else if (temperatureBin == 1)
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi++;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			
			}
			else
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi+=3;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			}

				break;
		case 1:
			if (temperatureBin == 0) 
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi--;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			}
			else if (temperatureBin == 1)
			{
			}
			else
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi +=2;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			}

			break;
		case 2:
			if (temperatureBin == 0)
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi-=3;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			}
			else if (temperatureBin == 1)
			{
				FuncsafeMonLevelRf.bits_st.LevelRfHighSpi -=2;
				glue_reg_WriteCheck(TX_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
			}
			else
			{
				
			}

			break;
		default:
			break;
		}
		
		txGainTemperatureBin = temperatureBin;
		return HAL_GERRCODE;
	}
	

	

	int hal_es3_tx_CalculateThreshold(float targetParp)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t OTP_24C = g_OTPShadowLUT_ES3[19];

		HAL_GERRCODE_INIT;
		int threshold = 0;
		uint16_t OTP_max = (OTP_24C >> 28) & 0xF;

		OTP_max = hal_es3_bit_flip(OTP_max, 4);
		
		threshold = roundf((3.5f + OTP_max) * powf(10, (targetParp - 12.5f) / 20) - 3.5f);

		return threshold;
	}
#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
