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
* @file hal_es3_adc.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief ADC Low-Level Interface.
*
*
******************************************************************************/

#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_Adc.h>
#include <es3/NXP_TEF810X_ISM.h>
#include <es3/NXP_TEF810X_MasterClock.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_adc_PowerOn()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		bool isSucces = false;
		int numRecalib = 3;

		Nxp_Tef810x_Mod07_CalibrationProgramTiming50Union_t CalibrationProgTiming_5_0;
		Nxp_Tef810x_Mod07_CalibrationControlUnion_t CalibrationControl;
		Nxp_Tef810x_Mod07_PonUnion_t				ADC12Pon;
		Nxp_Tef810x_Mod07_PonUnion_t				ADC34Pon;
		Nxp_Tef810x_Mod07_BiasMaindacUnion_t		BiasMaindac;

		HAL_GERRCODE_INIT;

		//func reset is released in hal_es3_ISM_Init_Act_8

		/**********Change of calibration settings to speed up startup and fixing artf506247*********/
		//change of calibration accuracy
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_PROGRAM_TIMING_5_0_U16, &CalibrationProgTiming_5_0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		CalibrationProgTiming_5_0.bits_st.CalibrationProgramTiming5 = 0xB;

		glue_reg_WriteCheck(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_PROGRAM_TIMING_5_0_U16, CalibrationProgTiming_5_0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//same setting for ADC34
		glue_reg_WriteCheck(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_PROGRAM_TIMING_5_0_U16, CalibrationProgTiming_5_0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//change the number of weights per back-ground calibration cycle
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_CONTROL_U16, &CalibrationControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		CalibrationControl.bits_st.PowersaveBgCalibrationNweights = 5;

		glue_reg_WriteCheck(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_CONTROL_U16, CalibrationControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//same setting for ADC34
		glue_reg_WriteCheck(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_CONTROL_U16, CalibrationControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//change the default bias mainDAC cascode
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_BIAS_MAINDAC_U16, &BiasMaindac.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		BiasMaindac.bits_st.BiasMaindacCascode = 3;

		glue_reg_WriteCheck(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_BIAS_MAINDAC_U16, BiasMaindac.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//same setting for ADC34
		glue_reg_WriteCheck(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_BIAS_MAINDAC_U16, BiasMaindac.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Fix for PDC synchronization across multiple samples (cascaded)
		Nxp_Tef810x_Mod0C_RefClockDelayControlUnion_t RefClockDelayControl;
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_REF_CLOCK_DELAY_CONTROL_U16, &RefClockDelayControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		RefClockDelayControl.bits_st.SelDelayClk40 = 0x6;	//Best setting from validation
		glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_REF_CLOCK_DELAY_CONTROL_U16, RefClockDelayControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//power on the ADCs
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_PON_U16, &ADC12Pon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ADC12Pon.bits_st.Pon = 1;
		glue_reg_WriteCheck(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_PON_U16, ADC12Pon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		glue_reg_Read(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_PON_U16, &ADC34Pon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ADC34Pon.bits_st.Pon = 1;
		glue_reg_WriteCheck(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_PON_U16, ADC34Pon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		// check calibration result
		if (hal_es3_adc_checkCalResult()==DOLPHINIC_NOERROR)
		{
			return HAL_GERRCODE;
		}
		else
		{
			//init calibration is not successful, redo it numRecalib times
			do {
				DbgInfo("Trying ADC recalibration, %d chances remaining before failure\n", numRecalib-1);
				if (hal_es3_adc_recalibrate() == DOLPHINIC_NOERROR) //recalib succeeds
					return HAL_GERRCODE;

			} while (--numRecalib);

			// after max num of trials, no success, throw error code.
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ADCPOWERONFAIL);
		}

		// initial power on and retrys both fails, return error code
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_ADCPOWERONFAIL);
	}


	DolphinIC_rval_t hal_es3_adc_recalibrate()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod07_CalibrationStartUnion_t	ADC12CalibrationStrt;
		Nxp_Tef810x_Mod07_CalibrationStartUnion_t	ADC34CalibrationStrt;

		HAL_GERRCODE_INIT;

		//manually start ADC calibration for ADC12
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, &ADC12CalibrationStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ADC12CalibrationStrt.bits_st.StartCalibration = 1;
		glue_reg_Write(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, ADC12CalibrationStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//manually start ADC calibration for ADC34
		glue_reg_Read(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, &ADC34CalibrationStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ADC34CalibrationStrt.bits_st.StartCalibration = 1;
		glue_reg_Write(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, ADC34CalibrationStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		hal_es3_adc_checkCalResult();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_adc_checkCalResult()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod07_CalMonitorStatusUnion_t	CalMonitorStatus;
		Nxp_Tef810x_Mod07_CalibrationStatusUnion_t	CalibrationStatus;

		//status variables
		uint32_t cal1 = 0x00;
		uint32_t cal2 = 0x00;
		uint32_t busy1 = 0x00;
		uint32_t busy2 = 0x00;

		uint8_t calMonStatus1_2 = 0;
		uint8_t calMonStatus3_4 = 0;

		HAL_GERRCODE_INIT;

		// 1. poll on CalibrationStatus
		glue_Tic();
		do {
			CalibrationStatus.val_u32 = 0x00;
			glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_STATUS_U16, &CalibrationStatus.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			cal1 = CalibrationStatus.bits_st.CalibrationLaunchedOkay;
			busy1 = CalibrationStatus.bits_st.CalibrationBusy;
			DbgInfo("Polling ADC12 cal status:%x\n", cal1);

			CalibrationStatus.val_u32 = 0x00;
			glue_reg_Read(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_STATUS_U16, &CalibrationStatus.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			cal2 = CalibrationStatus.bits_st.CalibrationLaunchedOkay;
			busy2 = CalibrationStatus.bits_st.CalibrationBusy;
			DbgInfo("Polling ADC34 cal status:%x\n", cal2);

			//timeout
			if (glue_Toc() >= ADC_CAL_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("ADC power-on failed: it didn't finish within %.2f ms...\n", ADC_CAL_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_ADCRECALIBTIMEOUT);
			}
		} while (!(cal1 && cal2) || (busy1 || busy2)); //one or more ADC cal didn't start OR one or more calibration is still busy

		// 2. check cal_monitor_status for detailed status
		//check calibration status 1 2 (this is finer status than CALIBRATION_STATUS)
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CAL_MONITOR_STATUS_U16, &CalMonitorStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		calMonStatus1_2 = CalMonitorStatus.val_u32;
		DbgInfo("ADC12 calMonStatus:%x\n", calMonStatus1_2);

		//check calibration status 3 4
		CalMonitorStatus.val_u32 = 0;
		glue_reg_Read(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CAL_MONITOR_STATUS_U16, &CalMonitorStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		calMonStatus3_4 = CalMonitorStatus.val_u32;
		DbgInfo("ADC34 calMonStatus:%x\n", calMonStatus3_4);

		if (calMonStatus1_2 == 0x07 && calMonStatus3_4 == 0x07)
		{
			//calibration succeeded
			return HAL_GERRCODE;
		}
		else
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ADCRECALIBFAIL);
	}


	void hal_es3_adc_recalibrate_1(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod07_CalibrationStartUnion_t	ADC12CalibrationStrt;
		Nxp_Tef810x_Mod07_CalibrationStartUnion_t	ADC34CalibrationStrt;

		HAL_GERRCODE_INIT;

		//manually start ADC calibration
		glue_reg_Read(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, &ADC12CalibrationStrt.val_u32, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ADC12CalibrationStrt.bits_st.StartCalibration = 1;

		glue_reg_Write(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, ADC12CalibrationStrt.val_u32, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, &ADC34CalibrationStrt.val_u32, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ADC34CalibrationStrt.bits_st.StartCalibration = 1;

		glue_reg_Write(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_CALIBRATION_START_U16, ADC34CalibrationStrt.val_u32, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
