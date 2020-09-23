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
* @file hal_es3_mclk.c
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief Master Clock Low-Level Interface.
*
*
******************************************************************************/

#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_MasterClock.h>
#include <es3/NXP_TEF810X_ATB.h>
#include <es3/NXP_TEF810X_ISM.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_mclk_Init(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod0C_LockControlUnion_t			mclkLockControl;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t		CcIpPON;
		Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t	mclkCalibVcoCtrl;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t CcFuncReset;
		Nxp_Tef810x_Mod0C_ResetCalibrationUnion_t		mclkRstCalib;
//		Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus;
		Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t		McLoErrorMonReg;
		Nxp_Tef810x_Mod0C_ClockBufferControlUnion_t		mclkClkBuffCtrl;
//		Nxp_Tef810x_Mod0C_LockStatusUnion_t				LockStatus;
		Nxp_Tef810x_Mod0C_CalibrationStatus1Union_t		CalibrationStatus1;
		Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t StartCalibrationCounter;

//		int count;
//		int delay_count;
		HAL_GERRCODE_INIT;

		//Enable continuous monitoring for MC calibration error
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16, &McLoErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		McLoErrorMonReg.bits_st.McPllFreqCalFlagMon = 1;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16, McLoErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure and enable lock control
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_LOCK_CONTROL_U16, &mclkLockControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		mclkLockControl.bits_st.LockDetEnable = 1;

		glue_reg_WriteCheck(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_LOCK_CONTROL_U16, mclkLockControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//enable VCO calibration level monitor
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_VCO_CONTROL_U16, &mclkCalibVcoCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		mclkCalibVcoCtrl.bits_st.VcoLevelCompEna = 1;
		//Hardcoded value, based on validation
		mclkCalibVcoCtrl.bits_st.VtuneRecalibWindow = 0xB;

		glue_reg_WriteCheck(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_VCO_CONTROL_U16, mclkCalibVcoCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//enable the PON for master clock
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &CcIpPON.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CcIpPON.bits_st.PonMasterClk = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, CcIpPON.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//release the func release for master clock
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &CcFuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CcFuncReset.bits_st.FnResetMasterClk = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, CcFuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//wait for 10ms - add this - simulation results, for PLL bias - there is no flag to check this one
		glue_Sleep(10);


		//reset calibration 
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_RESET_CALIBRATION_U16, &mclkRstCalib.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		mclkRstCalib.bits_st.RstAn = 1;

		glue_reg_WriteCheck(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_RESET_CALIBRATION_U16, mclkRstCalib.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Fix from Marcello to the problems during Initial Reset and Calibration
		for (int i = 0; i < 2; i++) {
			glue_Sleep(5);
			glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, &StartCalibrationCounter.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			StartCalibrationCounter.bits_st.StartCalibrationCounter = 1;
			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, StartCalibrationCounter.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		glue_Sleep(0.5); //Less waiting but necessary to allow stabilization before ADC calibration

		
		//check level errors
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_STATUS1_U16, &CalibrationStatus1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if(CalibrationStatus1.bits_st.VcoLevelError !=0) HAL_GEC_FUNEXIT(DOLPHINIC_EC_INITACT11FAIL);


		//enable clock buffers
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CLOCK_BUFFER_CONTROL_U16, &mclkClkBuffCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		mclkClkBuffCtrl.bits_st.EnClkChirp480 = 1;
		mclkClkBuffCtrl.bits_st.EnClkSer480600 = 1;
		mclkClkBuffCtrl.bits_st.EnClkAdc600 = 1;
		mclkClkBuffCtrl.bits_st.EnClkSsbmod600 = 1;
		mclkClkBuffCtrl.bits_st.EnClkAdc40 = 1;

		glue_reg_WriteCheck(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CLOCK_BUFFER_CONTROL_U16, mclkClkBuffCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Disable the continuous monitoring of MC calibration error set at the begining (will be enabled again at step 14 of initialization)
		McLoErrorMonReg.bits_st.McPllFreqCalFlagMon = 0;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16, McLoErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_mclk_Recalibrate(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t readData = 0xFF;
		Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t mclkStartCalibCounter;
		Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus;
//		uint32_t counter = 0;


		HAL_GERRCODE_INIT;
		//trigger a calibration

		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, &mclkStartCalibCounter.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		mclkStartCalibCounter.bits_st.StartCalibrationCounter = 1;

		glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, mclkStartCalibCounter.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//poll recalib flag to confirm successful calibration
		glue_Sleep(0.5);
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SetMCUReset();
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if(McLoErrorFlagMaskedStatus.bits_st.McPllLockErrorFlag == 1 || McLoErrorFlagMaskedStatus.bits_st.McPllLevelErrorFlag == 1)
			HAL_GEC_ASSERT(DOLPHINIC_EC_MCLKRECALIBFAILED);

		return HAL_GERRCODE;
	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
