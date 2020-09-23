//*------------------------------------------------------------------------------*/
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
* @file hal_es3_ISM.c
*
* @ver v5.3.2  
*
* @author Baris Can Kara
*
* @date 11/11/2016
*
* @brief Functional Safety Manual compliant initialization functions
*
*
******************************************************************************/

#include <hal_es3.h>
#include <hal_es3_ctrl.h>
#include "console_api.h"

#ifdef DOLPHIN_CFG_ES3

//new style register header
#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_GlobalLDO.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_Tx.h>
#include <es3/NXP_TEF810X_Rx.h>
#include <es3/NXP_TEF810X_Ism.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_Ssbmod.h>
#include <es3/NXP_TEF810X_SweepControl.h>
#include <es3/NXP_TEF810X_LoInterface.h>
#include <es3/NXP_TEF810X_MasterClock.h>
#include <es3/NXP_TEF810X_Csi2.h>
#include <es3/NXP_TEF810X_LvdsTx.h>
#include <es3/NXP_TEF810X_Cif.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_GlobalBias.h>
#include <es3/NXP_TEF810X_Adc.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_ISM_FIT(int32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		bool errorPin = false;
//		Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t			CCErrNPinCtrl;
		Nxp_Tef810x_Mod18_IsmFitTestRegUnion_t				ISMFitTst;
		Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t			CCErrNPadCtrl;
		Nxp_Tef810x_Mod18_FitStatusSupplyRegUnion_t			ISMFITStatusSupply;
		Nxp_Tef810x_Mod18_FitStatusTxRegUnion_t				ISMFITStatusTx;
		Nxp_Tef810x_Mod18_FitStatusRxRegUnion_t				ISMFitStatusRx;
		Nxp_Tef810x_Mod18_FitStatusChirpRegUnion_t			ISMFITStatusChirp;
		Nxp_Tef810x_Mod18_FitStatusMcLoRegUnion_t			ISMFITStatusMcLo;
		Nxp_Tef810x_Mod18_FitStatusAdcRegUnion_t			ISMFITStatusADC;
		uint32_t											masks[3];	//Array of masks for OTP disabled samples
		Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t		ChirpSequenceControl;
		Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t		ChirpSequenceControl_backup;
//		uint32_t											chirp_global_ctrl;
//		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGlobalControl_ust;
		Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t		DcPowerOnDelayControl;
		Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t		DcPowerOnDelayControl_backup;
		Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t	DynamicPowerControlEnable;
		ChirpSequenceControl_backup.val_u32 = 0x00;
		DcPowerOnDelayControl_backup.val_u32 = 0x00;


		HAL_GERRCODE_INIT;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, 0x38000, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_ERROR_N_PADCONTROL_U16, &CCErrNPadCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCErrNPadCtrl.bits_st.ErrorNMfioEn = 0;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_ERROR_N_PADCONTROL_U16, CCErrNPadCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
#ifdef DOLPHIN_CFG_HOST_S32R274		//Test Digital ErrorN Pin High
		glue_GetGPIO(DOLPHIN_EXTPO_ERRORN, &errorPin);
		if ((errorPin != 1) && (mode == 1)) HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL); //Extra condition to only fail for CSI2, this is only due to the validation setup for LVDS/CIF
#endif

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, &ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Test: When using dynamic power down it may take a while for some samples to charge the CHIRP capacitors and this can create some problems
		//To solve this a dummy chirp is triggered so the fast charge is enabled during the FIT error force
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_ENABLE_U16, &DynamicPowerControlEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

#ifdef DOLPHIN_CFG_HOST_S32R274 //Especial sequence for corners
		if (DynamicPowerControlEnable.bits_st.ChirpDyPowerControl == 1) {
			//Disable data transmission
			switch (mode)
			{
			case 1:
				hal_ES3_CSI2_Datatoggle_Disable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			case 2:
				hal_ES3_LVDS_Datatoggle_Disable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			case 3:
				hal_ES3_CIF_Datatoggle_Disable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			default:
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
				break;
			}
			glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16, &ChirpSequenceControl.val_u32, NULL);
			ChirpSequenceControl_backup.val_u32 = ChirpSequenceControl.val_u32;
			ChirpSequenceControl.bits_st.NoOfChirpInASequence = 1;
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16, ChirpSequenceControl.val_u32, NULL);
			glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16, &DcPowerOnDelayControl.val_u32, NULL);
			DcPowerOnDelayControl_backup.val_u32 = DcPowerOnDelayControl.val_u32;
			DcPowerOnDelayControl.bits_st.DcPoweronDelay = 0x200; //Match the default time that the fast switch is on
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16, DcPowerOnDelayControl.val_u32, NULL);
			chip_TE_ChirpStart();	//Trigger dummy chirp
			//By default fast switch is enabled during 12.8us
			//By default DC_power on should be 50us
		}
#endif

		//initiate ISM_OSM_TEST_FORCE_ERROR
		ISMFitTst.bits_st.IsmOsmTestForceError = 1;
		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		

#ifdef DOLPHIN_CFG_HOST_S32R274		//Test Digital ErrorN Pin Low
		glue_GetGPIO(DOLPHIN_EXTPO_ERRORN, &errorPin);
		if (errorPin != 0) HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
#endif

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, &ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ISMFitTst.bits_st.IsmTestCurrentstate != 1)
		{
			DbgInfo("FIT has failed! : Unexpected state\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

#ifdef DOLPHIN_CFG_HOST_S32R274
		//Undo the changes for the fast-switch-enabling dummy chirp
		if (DynamicPowerControlEnable.bits_st.ChirpDyPowerControl == 1) {

#ifdef READY_INT_CFG
			//Instead of the loop below chip_TE_WaitForReady() could be used when enabling ready Int, but for that the interrupt enabled should be 
			//'end_of_data_acq_int_en' instead of 'end_of_data_tnfr_int_en' as the last won't be triggered when disabling data transmission. 
			//In this demo code is not worth doing the change as the 3 SPI operations (read, write, restore) needed to temporarily change the 
			//interrupt type would take longer than the expected delay introduced by the polling below
			do
			{
				glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			} while ((ChirpGlobalControl_ust.bits_st.ChirpStart) == 0x01);
#else
			chip_TE_WaitForReady();
#endif
			//Reenable data transimission
			switch (mode)
			{
			case 1:
				hal_ES3_CSI2_Datatoggle_Enable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			case 2:
				hal_ES3_LVDS_Datatoggle_Enable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			case 3:
				hal_ES3_CIF_Datatoggle_Enable();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				break;
			default:
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
				break;
			}
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16, ChirpSequenceControl_backup.val_u32, NULL);
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16, DcPowerOnDelayControl_backup.val_u32, NULL);
		}
		else {
			glue_Sleep(0.060); //This is still needed for the FIT at startup...
		}
#else
		glue_Sleep(0.110);
#endif
		//clear ism_OSM_test_force_error & initiate ism_OSM_test_reset_error
		ISMFitTst.bits_st.IsmOsmTestForceError = 0;
		ISMFitTst.bits_st.IsmOsmTestResetError = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, &ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ISMFitTst.bits_st.IsmTestCurrentstate != 2)
		{
			DbgInfo("FIT has failed! : Unexpected state\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		//Clear all
		ISMFitTst.bits_st.IsmOsmTestForceError = 0;
		ISMFitTst.bits_st.IsmOsmTestResetError = 0;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16, &ISMFitTst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ISMFitTst.bits_st.IsmTestComplete != 1 || \
			ISMFitTst.bits_st.FitStatusRtm0 != 1 || \
			ISMFitTst.bits_st.FitStatusRtm1 != 1 || \
			ISMFitTst.bits_st.FitStatusRfPowerdown0 != 1 || \
			ISMFitTst.bits_st.FitStatusRfPowerdown1 != 1 || \
			ISMFitTst.bits_st.IsmTestCurrentstate != 3
			)
		{
			DbgInfo("FIT Init has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		//check if all supply status' are passed FIT (SSBMOD is not powered up at this stage)
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_SUPPLY_REG_U16 , &ISMFITStatusSupply.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//For OTP disabled samples mask the read value so the FIT will ignore errors from disabled IPs
		hal_es3_OTP_checkValidIP(0x18, NULL, masks);
		ISMFITStatusSupply.val_u32 = ISMFITStatusSupply.val_u32 | masks[0];

		if (ISMFITStatusSupply.bits_st.SupplyLowErrorFlagTx1Sync == 0 || \
			ISMFITStatusSupply.bits_st.SupplyLowErrorFlagTx2Sync == 0 || \
			ISMFITStatusSupply.bits_st.SupplyLowErrorFlagTx3Sync == 0)
		{
			DbgInfo("0[IF]FIT TX Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		if (ISMFITStatusSupply.bits_st.Supply1V1LowErrorFlagRx1Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V1LowErrorFlagRx2Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V1LowErrorFlagRx3Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V1LowErrorFlagRx4Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V8LowErrorFlagRx1Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V8LowErrorFlagRx2Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V8LowErrorFlagRx3Sync == 0 || \
			ISMFITStatusSupply.bits_st.Supply1V8LowErrorFlagRx4Sync == 0)
		{
			DbgInfo("0[IF]FIT RX Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		if (ISMFITStatusSupply.bits_st.Mc1V8SupplyLowErrorFlagSync == 0)
		{
			DbgInfo("0[IF]FIT MCLK Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		if (ISMFITStatusSupply.bits_st.SupplyLowErrorFlagAdc12Sync == 0 || \
			ISMFITStatusSupply.bits_st.SupplyLowErrorFlagAdc34Sync == 0)
		{
			DbgInfo("0[IF]FIT ADC Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		if (ISMFITStatusSupply.bits_st.SupplyLowErrorFlagInterfaceSync == 0)
		{
			DbgInfo("0[IF]FIT Interface Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		//Do not check SSBMOD, since it is not initialized in the regular sequence
		/*if (ISMFITStatusSupply.bits_st.SsbMod1V8SupplyLowErrorFlagSync == 0)
		{
			DbgInfo("0[IF]FIT SSBMOD Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}*/

		if (ISMFITStatusSupply.bits_st.GlobalBiasSupplyLowErrorFlagSync == 0)
		{
			DbgInfo("0[IF]FIT GBias Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusSupply.bits_st.Ser1V1SupplyLowErrorFlagSync == 0 || \
			ISMFITStatusSupply.bits_st.Ser1V8LowErrorFlagSync == 0)
		{
			DbgInfo("0[IF]FIT Serialiser Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (mode == 1) {

			if (ISMFITStatusSupply.bits_st.Csi21V1LowErrorFlagSync == 0)
			{
				DbgInfo("0[IF]FIT CSI-2 Supply step has failed!\n");
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
			}
		}
		if (ISMFITStatusSupply.bits_st.SupplyPllErrorFlagChirpSync == 0 || \
			ISMFITStatusSupply.bits_st.SupplyVcoErrorFlagChirpSync == 0 || \
			ISMFITStatusSupply.bits_st.SupplyDigErrorFlagChirpSync == 0)
		{
			DbgInfo("0[IF]FIT Chirp Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusSupply.bits_st.GlobalLdo1V1SupplyHighErrorFlagSync == 0 || \
			ISMFITStatusSupply.bits_st.GlobalLdo1V1SupplyLowErrorFlagSync == 0  || \
			ISMFITStatusSupply.bits_st.GlobalLdo1V8SupplyHighErrorFlagSync == 0 || \
			ISMFITStatusSupply.bits_st.GlobalLdo1V8SupplyLowErrorFlagSync == 0)
		{
			DbgInfo("0[IF]FIT GLDO Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}


		//check if all TX sensors status' are passed
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_TX_REG_U16, &ISMFITStatusTx.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMFITStatusTx.val_u32 = ISMFITStatusTx.val_u32 | masks[1];	//For OTP disabled samples

		if (ISMFITStatusTx.bits_st.Tx1BbError == 0 || \
			ISMFITStatusTx.bits_st.Tx1TempError == 0 || \
			ISMFITStatusTx.bits_st.Tx1RfLevelFsError == 0 || \
			ISMFITStatusTx.bits_st.Tx1RfLevelLowError == 0 || \
			/*ISMFITStatusTx.bits_st.Tx1RfReliabilityLevelError == 0 || \*/
			ISMFITStatusTx.bits_st.SupplyLowErrorFlagTx11V8Error == 0)
		{
			DbgInfo("0[IF]FIT TX1 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusTx.bits_st.Tx2BbError == 0 || \
			ISMFITStatusTx.bits_st.Tx2TempError == 0 || \
			ISMFITStatusTx.bits_st.Tx2RfLevelFsError == 0 || \
			ISMFITStatusTx.bits_st.Tx2RfLevelLowError == 0 || \
			/*ISMFITStatusTx.bits_st.Tx2RfReliabilityLevelError == 0 || \*/
			ISMFITStatusTx.bits_st.SupplyLowErrorFlagTx21V8Error == 0)
		{
			DbgInfo("0[IF]FIT TX2 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusTx.bits_st.Tx3BbError == 0 || \
			ISMFITStatusTx.bits_st.Tx3TempError == 0 || \
			ISMFITStatusTx.bits_st.Tx3RfLevelFsError == 0 || \
			ISMFITStatusTx.bits_st.Tx3RfLevelLowError == 0 || \
			/*ISMFITStatusTx.bits_st.Tx3RfReliabilityLevelError == 0 || \*/
			ISMFITStatusTx.bits_st.SupplyLowErrorFlagTx31V8Error == 0)
		{
			DbgInfo("0[IF]FIT TX3 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		

		//check if all RX sensors status' are passed
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_RX_REG_U16, &ISMFitStatusRx.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMFitStatusRx.val_u32 = ISMFitStatusRx.val_u32 | masks[2]; //For OTP disabled samples

		if (ISMFitStatusRx.bits_st.Rx1BbError == 0 || \
			ISMFitStatusRx.bits_st.Rx1LoLevelFsError == 0 || \
			ISMFitStatusRx.bits_st.Rx1LoLevelHighError == 0 || \
			ISMFitStatusRx.bits_st.Rx1LoLevelLowError == 0 || \
			ISMFitStatusRx.bits_st.Rx1LoReliabilityLevelError == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx11V1 == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx11V8 == 0)
		{
			DbgInfo("0[IF]FIT RX1 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFitStatusRx.bits_st.Rx3BbError == 0 || \
			ISMFitStatusRx.bits_st.Rx3LoLevelFsError == 0 || \
			ISMFitStatusRx.bits_st.Rx3LoLevelHighError == 0 || \
			ISMFitStatusRx.bits_st.Rx3LoLevelLowError == 0 || \
			ISMFitStatusRx.bits_st.Rx3LoReliabilityLevelError == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx31V1 == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx31V8 == 0)
		{
			DbgInfo("0[IF]FIT RX3 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFitStatusRx.bits_st.Rx2BbError == 0 || \
			ISMFitStatusRx.bits_st.Rx2LoLevelFsError == 0 || \
			ISMFitStatusRx.bits_st.Rx2LoLevelHighError == 0 || \
			ISMFitStatusRx.bits_st.Rx2LoLevelLowError == 0 || \
			ISMFitStatusRx.bits_st.Rx2LoReliabilityLevelError == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx21V1 == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx21V8 == 0)
		{
			DbgInfo("FIT RX2 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFitStatusRx.bits_st.Rx4BbError == 0 || \
			ISMFitStatusRx.bits_st.Rx4LoLevelFsError == 0 || \
			ISMFitStatusRx.bits_st.Rx4LoLevelHighError == 0 || \
			ISMFitStatusRx.bits_st.Rx4LoLevelLowError == 0 || \
			ISMFitStatusRx.bits_st.Rx4LoReliabilityLevelError == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx41V1 == 0 || \
			ISMFitStatusRx.bits_st.SupplyLowErrorFlagRx41V8 == 0)
		{
			DbgInfo("FIT RX4 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		//check if all chirp sensors status' are passed
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_CHIRP_REG_U16, &ISMFITStatusChirp.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ISMFITStatusChirp.bits_st.LockStepErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.UnlockErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.MaxTempErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.VtuneHighErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.VtuneLowErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.LevelLowErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.LevelHighErrorFlagChirpSync == 0 || \
			ISMFITStatusChirp.bits_st.LevelMaxErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.LevelMinErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.VcoFreq480ErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.SupplyDigErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.SupplyVcoErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.SupplyPllErrorFlagChirp == 0 || \
			ISMFITStatusChirp.bits_st.InterfaceStuckFlagChirp == 0)
		{
			DbgInfo("FIT Chirp step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		//check if all MCLK sensors status' are passed
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_MC_LO_REG_U16, &ISMFITStatusMcLo.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (ISMFITStatusMcLo.bits_st.McPllFreqErrorFlag == 0 || \
			ISMFITStatusMcLo.bits_st.McPllLevelErrorFlag == 0 || \
			ISMFITStatusMcLo.bits_st.McPllLockErrorFlag == 0 || \
			ISMFITStatusMcLo.bits_st.DigFreqErrorFlagMasterclk == 0 || \
			ISMFITStatusMcLo.bits_st.SupplyLowErrorFlagMc1V8 == 0
			)
		{
			DbgInfo("FIT MCLK step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusMcLo.bits_st.BbErrorFlagInterface == 0 || \
			ISMFITStatusMcLo.bits_st.SupplyLowErrorFlagInterface1V1 == 0
			)
		{
			DbgInfo("FIT LOInterface step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		
		//check if all ADC sensors status' are passed (persistent flags are exempt from check, errata artf620106)
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_FIT_STATUS_ADC_REG_U16, &ISMFITStatusADC.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		if (
			/*ISMFITStatusADC.bits_st.Adc1CalErrorFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc1ClippingFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc1ClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc1HardClippingErrorFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc1HardClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc1NearClippingFlag == 0
			/*ISMFITStatusADC.bits_st.Adc1NearClippingFlagPersistent == 0*/
			)
		{
			DbgInfo("FIT ADC1 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (
			/*ISMFITStatusADC.bits_st.Adc2CalErrorFlagPersistent == 0 || */
			ISMFITStatusADC.bits_st.Adc2ClippingFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc2ClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc2HardClippingErrorFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc2HardClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc2NearClippingFlag == 0
			/*ISMFITStatusADC.bits_st.Adc2NearClippingFlagPersistent == 0*/
			)
		{
			DbgInfo("FIT ADC2 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (
			/*ISMFITStatusADC.bits_st.Adc3CalErrorFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc3ClippingFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc3ClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc3HardClippingErrorFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc3HardClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc3NearClippingFlag == 0
			/*ISMFITStatusADC.bits_st.Adc3NearClippingFlagPersistent == 0*/
			)
		{
			DbgInfo("FIT ADC3 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (
			/*ISMFITStatusADC.bits_st.Adc4CalErrorFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc4ClippingFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc4ClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc4HardClippingErrorFlag == 0 || \
			/*ISMFITStatusADC.bits_st.Adc4HardClippingFlagPersistent == 0 || \*/
			ISMFITStatusADC.bits_st.Adc4NearClippingFlag == 0
			/*ISMFITStatusADC.bits_st.Adc4NearClippingFlagPersistent == 0*/
			)
		{
			DbgInfo("FIT ADC4 step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}
		if (ISMFITStatusADC.bits_st.SupplyLowErrorFlagAdc12 == 0 || \
			ISMFITStatusADC.bits_st.SupplyLowErrorFlagAdc34 == 0 
			)
		{
			DbgInfo("FIT ADC-Supply step has failed!\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_ISMFITFAIL);
		}

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	};

	DolphinIC_rval_t hal_es3_ISM_MCLKIntegrityCheck(int32_t mode, float refFreq)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t Pon_bit		= 0x0;
		uint8_t funcRst_bit = 0x0;
//		bool	rval		= false;
		float	meas_freq	= 0.0f;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t		ponCtrl;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t CcFuncRst;

		HAL_GERRCODE_INIT;

		//save the status of PON bit of serialiser, and temporarily release the PON for serialiser
		
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &ponCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Pon_bit = ponCtrl.bits_st.PonSer;
		ponCtrl.bits_st.PonSer = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, ponCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//save the status of func. reset bit of serialiser, and temporarily release the func. reset for serialiser
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &CcFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		funcRst_bit = CcFuncRst.bits_st.FnResetSer;
		CcFuncRst.bits_st.FnResetSer = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, CcFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		switch (mode)
		{
		case 1:
		{
			hal_es3_csi2_getMCLKOutFrequency(&meas_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case 2:
		{
			hal_es3_lvds_getMCLKOutFrequency(&meas_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case 3:
		default:
		{
			hal_es3_cif_getMCLKOutFrequency(&meas_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;
		}

		//Load the status of func. reset bit of serialiser
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &CcFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CcFuncRst.bits_st.FnResetSer = funcRst_bit;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, CcFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Load the status of PON bit of serialiser
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &ponCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ponCtrl.bits_st.PonSer = Pon_bit;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, ponCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		if (meas_freq == refFreq)
		{
			DbgInfo("MClk Integrity OK(%d, %f) \n", mode, meas_freq);
			return HAL_GERRCODE;
		}
		else
		{
			DbgInfo("Deviation in Measured Clock M(%d) Act(%f) Exp(%f) \n", mode, meas_freq, refFreq);
			return DOLPHINIC_EC_MCLKINTEGRITYFAILED;
		}
	}

	DolphinIC_rval_t hal_es3_ISM_DataPatternTest(uint16_t patternData, int32_t mode, uint8_t deci)
	{

		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t readData[2] = { 0x00 };
//		uint8_t moduleAdd = 0x00;
//		uint16_t regAdd = 0x00;
//		uint32_t regval = 0x00;

		int ProfileNum = 0;

		//fixed chrip profile for data pattern test
		uint16_t NumSamples = 1024;
		uint16_t NumChirps = 16;

		double DwellTime = 5;
		double ResetTime = 5;
		double JumpbackTime = 1;
		double SettleTime = 10;
		double ChirpPeriod = DwellTime + SettleTime + (NumSamples*0.025) + JumpbackTime + ResetTime;

		bool PDCBWWide = false;

		bool BPSControl[3] = { false, false, false };
		bool TxSW[3] = { 0, 0, 0 };
		bool TxPON[3] = { 0, 0, 0 };

		bool RxPON[4] = { 0, 0, 0, 0 };
//		uint32_t	memData[1024 * 16 * 4 * 12 / 32 + 1];
//		uint16_t	decodedData[1024 * 16 * 4];
		//TX/RX active bits
		uint8_t     txActiveNum = (((uint8_t)TxPON[2]) << 0x02) | (((uint8_t)TxPON[1]) << 0x01) | (((uint8_t)TxPON[0]));
		uint8_t     rxActiveNum = (((uint8_t)RxPON[3]) << 0x03) | (((uint8_t)RxPON[2]) << 0x02) | (((uint8_t)RxPON[1]) << 0x01) | (((uint8_t)RxPON[0]));
		uint8_t     bps_control_bits = (((uint8_t)BPSControl[2]) << 0x02) | (((uint8_t)BPSControl[1]) << 0x01) | (((uint8_t)BPSControl[0]));
		uint8_t     tx_control_bits = (((uint8_t)TxSW[2]) << 0x02) | (((uint8_t)TxSW[1]) << 0x01) | (((uint8_t)TxSW[0]));
//		uint32_t	dataRate;
//		uint32_t	numLanes;
		uint32_t	DF_reg;
//		uint32_t	cycleDelay;
//		int			indx;
//		bool		PDCsync = true;
//		Nxp_Tef810x_Mod02_PdcConfigRegUnion_t			Csi2pdcConfg;
		Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t	CafcDivForce;
//		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		TEChirpGlblCtrl;
		HAL_GERRCODE_INIT;
		
#ifdef DOLPHIN_CFG_HOST_OPALKELLY

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_teng_CfgChirpTriggerMode(0, 0, false, true, false, false);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure number of chirps in a sequence
		hal_es3_teng_CfgNumChirpSeq(1, NumChirps);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure sequence internal, normally keep it 1(25ns)
		hal_es3_teng_CfgSeqInterval(1);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure jumpback time.
		hal_es3_teng_CfgTJumpBack(JumpbackTime);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure chirp profile.
		hal_es3_teng_CfgChirpProfile(0, 1, true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure power on delay
		hal_es3_teng_CfgDCPowOnDelay(15, SettleTime);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//group pon delays
		hal_es3_teng_CfgRXPowOnDelay(2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		//Configure Control3 register in Timing Engine
		hal_es3_teng_UpdateProfChirpPeriod(ProfileNum, txActiveNum, rxActiveNum, ChirpPeriod);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//timing_profile
		hal_es3_teng_UpdateProfTiming(ProfileNum, DwellTime, false, 75e-3, bps_control_bits, tx_control_bits);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//adc_profile
		hal_es3_teng_UpdateProfADC(ProfileNum, SettleTime, NumSamples, deci, PDCBWWide);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Only for CSI2
		if (mode == 1)
		{
			//set output as signed for test purposes
			glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16, &Csi2pdcConfg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			regval = Csi2pdcConfg.val_u32;
			Csi2pdcConfg.bits_st.MakeOutputUnsigned = 0;

			glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16, Csi2pdcConfg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//choose num of lanes and data rate based on decimation
			dataRate = 0x00;
			numLanes = 0x03;
			switch (deci)
			{
			case 1:
			{
				dataRate = 0;
				numLanes = 3;
				break;
			}
			case 2:
			{
				dataRate = 1;
				numLanes = 3;
				break;
			}
			case 4:
			{
				dataRate = 1;
				numLanes = 1;
				break;
			}
			case 8:
			{
				dataRate = 2;
				numLanes = 1;
				break;
			}
			case 16:
			{
				dataRate = 2;
				numLanes = 0;
				break;
			}
			default:
			{
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
				break;
			}
			}

			hal_es3_csi2_Config(numLanes, dataRate, PDCsync); // 4-Lanes @ 480Mbps
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//set FPGA number of lanes
			setCSI2_OK(numLanes);
		}

		//Disable divide_force register in CAFC before chirp trigger
		DF_reg = 0x00;
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &CafcDivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		DF_reg = CafcDivForce.val_u32;
		CafcDivForce.bits_st.CtlForceDivider = 0;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, CafcDivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//FPGA-specific capture configuration
		cycleDelay = 2;
		CfgChirping(1, &NumChirps, &cycleDelay);
		CfgFPGASPICmdMode();
		//FPGA data capture start
		DataCapture_Start();

		//trigger a chirp
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Capture the data and save it in the stack
		DataCapture_Mem(memData, decodedData, NumChirps, NumSamples / deci);

		//compare the received ADC data with pattern data, return false if not the same
		//skip the first 2 data which has a chance to be be corrupted in FPGA in the very first capture.
		//Note: artf564386, data check can be replaced by checking the CRCs and frame clk counts.
		for (indx = 2; indx < 16; indx++)
		{
			if (decodedData[indx] != patternData)
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_DATAPTTRNTESTFAIL);
		}

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DF_reg, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (mode == 1)
		{
			//unset signed output data bit
			glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16, regval, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		return HAL_GERRCODE;
#endif

#ifdef DOLPHIN_CFG_HOST_S32R274

//		double init_out_clk_freq = (mode >= 3) ? (160e6 / deci) : (240e6 / deci);
//		uint32_t chirp_global_ctrl;
		HAL_GERRCODE_INIT;

		if (mode == 1) {
			//configure output clock frenquency


			// Cfg the serializer for the default ...
			hal_es3_ctrl_CfgSerializerDefault(mode);

			// Enable the test Mode ...
			hal_es3_ctrl_SetSerializerTestMode(mode, true, 0);

			// Cfg the Chirp parameters for Test Mode
			hal_es3_ctrl_CfgChirpTestDefault();

			// Trigger the Host & Teng for chirping ...
			glue_CaptureHostTrigger();

			hal_es3_teng_WaitForReady();

			// Check for data in the frame ...
			if (glue_CaptureTestPattern() == true)
			{
				if (glue_CheckTestPattern() == true)
				{
					// Disable the test Mode ...
					hal_es3_ctrl_SetSerializerTestMode(mode, false, 0);
					hal_es3_ISM_SetMCUReset();
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				}
				else
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_DATAPTTRNTESTFAIL);
			}
			else
			{
				// Disable the test Mode ...
				hal_es3_ctrl_SetSerializerTestMode(mode, false, 0);
				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				HAL_GEC_FUNEXIT(DOLPHINIC_EC_DATAPTTRNTESTFAIL);
			}
		}
		else {
		//For LVDS/CIF only run configuration
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_CfgChirpTriggerMode(0, 0, false, true, false, false);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//configure number of chirps in a sequence
			hal_es3_teng_CfgNumChirpSeq(1, NumChirps);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//configure sequence internal, normally keep it 1(25ns)
			hal_es3_teng_CfgSeqInterval(1);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//configure jumpback time.
			hal_es3_teng_CfgTJumpBack(JumpbackTime);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//configure chirp profile.
			hal_es3_teng_CfgChirpProfile(0, 1, true);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//configure power on delay
			hal_es3_teng_CfgDCPowOnDelay(15, SettleTime);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//group pon delays
			hal_es3_teng_CfgRXPowOnDelay(2);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



			//Configure Control3 register in Timing Engine
			hal_es3_teng_UpdateProfChirpPeriod(ProfileNum, txActiveNum, rxActiveNum, ChirpPeriod);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//timing_profile
			hal_es3_teng_UpdateProfTiming(ProfileNum, DwellTime, false, 75e-3, bps_control_bits, tx_control_bits);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//adc_profile
			hal_es3_teng_UpdateProfADC(ProfileNum, SettleTime, NumSamples, deci, PDCBWWide);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Disable divide_force register in CAFC before chirp trigger
			DF_reg = 0x00;
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &CafcDivForce.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			DF_reg = CafcDivForce.val_u32;
			CafcDivForce.bits_st.CtlForceDivider = 0;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, CafcDivForce.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//FPGA-specific capture configuration
			//cycleDelay = 2;
			//CfgChirping(1, &NumChirps, &cycleDelay);
			//CfgFPGASPICmdMode();
			//FPGA data capture start
			//DataCapture_Start();

			//trigger a chirp
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//Capture the data and save it in the stack
			//DataCapture_Mem(memData, decodedData, NumChirps, NumSamples / deci);

			//compare the received ADC data with pattern data, return false if not the same
			//skip the first 2 data which has a chance to be be corrupted in FPGA in the very first capture.

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DF_reg, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}

		return HAL_GERRCODE;
#endif
	};

	//FSM v2.1 section 6.9.3.1 - Application reset
	DolphinIC_rval_t hal_es3_ISM_Init_Act_1(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		glue_SystemReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.2 - SPI interface integrity check (SPI Loopback Test)
	DolphinIC_rval_t hal_es3_ISM_Init_Act_2(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		//reference test pattern
		uint32_t reftstpattern = 0xFEEDBABE;

		//in total 64bits on mosi line
		uint32_t mosi1, mosi2 = 0x00;
		//in total 64bits on miso line
		uint32_t miso1, miso2 = 0x00;

		Nxp_Tef810x_Mod18_CrcStatusRdRegUnion_t ISMCrcStatusRdReg;
		Nxp_Tef810x_Mod18_CrcStatusWrRegUnion_t ISMCrcStatusWrReg;

		HAL_GERRCODE_INIT;


		//generate expected value from module,reg addresses, command settings and reftstpattern data
		mosi1 = 0x80300000 + ((CENTRAL_CONTROL_MODULE_ADDRESS & 0x7F) << 24) + ((NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16 & 0xFFF) << 8) + ((reftstpattern >> 24) & 0xFF);
		mosi2 = (reftstpattern & 0x00FFFFFF) << 8;

		// write reftstpattern with loopback enabled
		glue_reg_BurstWriteRead(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16, &reftstpattern, &miso2, 0x01, false, true, true, &miso1);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//check received data with expected value
		if  ((mosi1 != miso1) || (mosi2 != miso2))
		{
			DbgErr("Err SPI Loopback test failed Act(0x%x), (0x%x); Exp(0x%x), (0x%x)\n", miso1, miso2, mosi1, mosi2);
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
		}

		// clear CRC error counts.
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CRC_STATUS_RD_REG_U16, &ISMCrcStatusRdReg.val_u32, NULL);
		ISMCrcStatusRdReg.bits_st.CrcRdBadCount = 0;
		ISMCrcStatusRdReg.bits_st.CrcRdGoodCount = 0;
		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CRC_STATUS_RD_REG_U16, ISMCrcStatusRdReg.val_u32, NULL);


		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CRC_STATUS_WR_REG_U16, &ISMCrcStatusWrReg.val_u32, NULL);
		ISMCrcStatusWrReg.bits_st.CrcWrBadCount = 0;
		ISMCrcStatusWrReg.bits_st.CrcWrGoodCount = 0;
		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CRC_STATUS_WR_REG_U16, ISMCrcStatusWrReg.val_u32, NULL);

		return HAL_GERRCODE;
	}


	//FSM v2.1 section 6.9.3.3 - SPI access check (scratch register)
	DolphinIC_rval_t hal_es3_ISM_Init_Act_3(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t reftstpattern = 0xFEEDBABE;
		uint32_t reftstpattern_2 = 0x11223344;
		uint32_t readBack = 0x00;
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		HAL_GERRCODE_INIT;
		
		//DO NOT use scracth register 8, which has functional bits.

		glue_reg_Write(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16, reftstpattern, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16, &readBack, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (reftstpattern != readBack)
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INITACT3FAIL);
		
		//updated based on artf587169
		glue_reg_Write(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16, reftstpattern_2, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16, &readBack, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (reftstpattern_2 != readBack)
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INITACT3FAIL);

		//if the test is passsed, mark the status in ISM
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.SpiAccessCheckDoneOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		return HAL_GERRCODE;
	};

	//FSM v2.1 section 6.9.3.4 - OTP Read and OTP data integrity check
	DolphinIC_rval_t hal_es3_ISM_Init_Act_4(void)
	{

		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		// The maximum allowed speed for the OTP burst read is 20MHz
		hal_es3_OTP_Load();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return DOLPHINIC_NOERROR;
	}

	//FSM v2.1 section 6.9.3.5 - Main LDO Switching
	DolphinIC_rval_t hal_es3_ISM_Init_Act_5(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regValue = 0x00;
		Nxp_Tef810x_Mod15_GldoBgRefConfigUnion_t		GLDO_bgRef;
		Nxp_Tef810x_Mod00_ResetControlUnion_t			CCRstCtrl;
		Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t		CCIPClkEn;	
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t	CCFuncRst;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t CCIPLevelPon;

		HAL_GERRCODE_INIT;

		//GLDO
		//a.	Configure global LDO  module from OTP
		// Release reset and enable clock for global LDO
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, &CCRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		CCRstCtrl.bits_st.ResetLglobalLdo = 1;
		
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, CCRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, &CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		CCIPClkEn.bits_st.Clk40GlobalLdo = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_23C_cat1_ES3[0x09], 1, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		//set reference to a calibrated low noise reference
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_U16, &GLDO_bgRef.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		GLDO_bgRef.bits_st.SelVref = 1;

		glue_reg_WriteCheck(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_U16, GLDO_bgRef.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//power on GLDO
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &CCIPLevelPon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCIPLevelPon.bits_st.PonGlobalLdo = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, CCIPLevelPon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//release func rest of GLDO
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &CCFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCFuncRst.bits_st.FnResetLglobalLdo = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, CCFuncRst.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// wait 500us as specified in FSM
		glue_Sleep(0.5);
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.MainLdoConfigOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.6 - Configure global bias
	DolphinIC_rval_t hal_es3_ISM_Init_Act_6(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regValue = 0x00;
		Nxp_Tef810x_Mod00_ResetControlUnion_t				CCRstCtrl;
		Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t			CCIPClkEn;
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t			CCIPLvlPonEn;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t		CCFuncRstCtrl;
//		Nxp_Tef810x_Mod09_GlobbiasPon1V8Union_t				gBiasPON1v8;
		Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoUnion_t		gBiasPONLocalLDO;

		HAL_GERRCODE_INIT;
		
		// a.	Configure global bias module  with OTP values
		//// Release reset and enable clock for Global Bias

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, &CCRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCRstCtrl.bits_st.ResetGlobalBias = 1;
		//regValue |= 0x200;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, CCRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, &CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCIPClkEn.bits_st.Clk40GlobalBias = 1;
		//regValue |= 0x200;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		hal_es3_OTP_LoadFromGlobal(&reg_21C_cat1_ES3[0x00], 11, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_21C_cat1_ES3[0x0D], 17, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// b.	 Power on global bias module and configure.
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &CCIPLvlPonEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCIPLvlPonEn.bits_st.PonGlobalBias = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS,   NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, CCIPLvlPonEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		//Release functional reset
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &CCFuncRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCFuncRstCtrl.bits_st.FnResetGlobalBias = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, CCFuncRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		//c.	Wait 250 us for circuit to stabilize
		glue_Sleep(0.25);
		// d.	Configure module level parameters
		
		glue_reg_Read(GLOBAL_BIAS_MODULE_ADDRESS, NXP_TEF810X_MOD09_GLOBBIAS_PON_LOCAL_LDO_U16, &gBiasPONLocalLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		gBiasPONLocalLDO.bits_st.PonLocalLdo = 1;

		glue_reg_WriteCheck(GLOBAL_BIAS_MODULE_ADDRESS, NXP_TEF810X_MOD09_GLOBBIAS_PON_LOCAL_LDO_U16, gBiasPONLocalLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.GobalBiasConfigOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.7 - Configure local LDOs
	DolphinIC_rval_t hal_es3_ISM_Init_Act_7(int32_t mode, uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regValue = 0x00;
		int mode2init;
		Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t			CCSerModeSel;
		Nxp_Tef810x_Mod00_ResetControlUnion_t				CCRstCtrl;
		Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t			CCIPClkEn;
		Nxp_Tef810x_Mod00_LdoSerialiserSerControlUnion_t	CCLDOSerCtrl;
		Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlUnion_t	CCLDOCSI2Ctrl;
//		Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t			CCLDOSSBMODCtrl;
		Nxp_Tef810x_Mod00_LdoAdcControlUnion_t				CCLDOADCCtrl;
		Nxp_Tef810x_Mod0C_LdoControlUnion_t					MCLKLdoCtrl;
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t			CppfdLdoRegister;

		HAL_GERRCODE_INIT;

		//choose interface in CCTRL
		mode2init = (mode >= 3) ? (3) : (mode);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16, &CCSerModeSel.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		CCSerModeSel.bits_st.SwCtrlSerModeSel = mode2init;
		
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16, CCSerModeSel.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//TODO : OTP values for CC
		//a.	Configure local LDO  module  (values  from OTP bits 8..4 of control register. The code below only for reference)

		//Configure local LDO of the Serialiser and enable LDO
		hal_es3_OTP_LoadFromGlobal(&reg_264_cat1_ES3[0x01], 1, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SERIALISER_SER_CONTROL_U16, &CCLDOSerCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCLDOSerCtrl.bits_st.LdoEnSerialiserSer = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SERIALISER_SER_CONTROL_U16, CCLDOSerCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (mode == 0x01)
		{

			//Configure local LDO of the CSI2
			hal_es3_OTP_LoadFromGlobal(&reg_270_cat1_ES3[0x00], 1, IP_PON_Mask);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SERIALISER_CSI2_CONTROL_U16, &CCLDOCSI2Ctrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CCLDOCSI2Ctrl.bits_st.LdoEnSerialiserCsi2 = 1;

			glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SERIALISER_CSI2_CONTROL_U16, CCLDOCSI2Ctrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
		}
		
		//Configure local LDO of the ADC and enable
		hal_es3_OTP_LoadFromGlobal(&reg_264_cat1_ES3[0x02], 1, IP_PON_Mask);

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_ADC_CONTROL_U16, &CCLDOADCCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCLDOADCCtrl.bits_st.LdoEnAdc = 1;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_ADC_CONTROL_U16, CCLDOADCCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Configure local LDO of the SSBMOD
		hal_es3_OTP_LoadFromGlobal(&reg_264_cat1_ES3[0x03], 1, IP_PON_Mask);

		// Release reset and enable clock for MCLK and CAFC
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, &CCRstCtrl.val_u32 , NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCRstCtrl.bits_st.ResetMasterClk = 1;
		CCRstCtrl.bits_st.ResetChirp = 1;
		//regValue |= 0x1040;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_RESET_CONTROL_U16, CCRstCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, &CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CCIPClkEn.bits_st.Clk40MasterClk = 1;
		CCIPClkEn.bits_st.Clk40Chirp = 1;
		//regValue |= 0x1040;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16, CCIPClkEn.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Calibrate CAFC LDO
		hal_es3_OTP_LoadFromGlobal(&reg_23C_cat1_ES3[0x01], 3, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//correction for artf592264
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16, &CppfdLdoRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		CppfdLdoRegister.bits_st.CtlLdoCppfdSelVoutSpi +=1 ;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16, CppfdLdoRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		// Enable CAFC LDOs
		hal_es3_cafc_EnableLDO();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Calibrate MCLK LDO
		hal_es3_OTP_LoadFromGlobal(&reg_23C_cat1_ES3[0x04], 4, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_21C_cat1_ES3[0x0B], 2, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		hal_es3_OTP_LoadFromGlobal(&reg_264_cat1_ES3[0x00], 1, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rd-Mod-Wr: enable MCLK LDO 
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_LDO_CONTROL_U16, &MCLKLdoCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		MCLKLdoCtrl.bits_st.LdoEn = 1;

		glue_reg_WriteCheck(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_LDO_CONTROL_U16, MCLKLdoCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Wait for 50 us is specified in FSM - confirmed by Marcello on 04-10-2018 artf564377
		glue_Sleep(0.05);
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.LocalLdoConfigOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.8 - Enable clock and release reset
	DolphinIC_rval_t hal_es3_ISM_Init_Act_8(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;
		//check if all user requested IP are OTP enabled
		if (hal_es3_comparePON_OTP_forIPEn(IP_PON_Mask) == DOLPHINIC_NOERROR)
		{
			//enable register clock to all modules  -- 01FFF7C2
			// OR with 0x01800000 to also enable ISM and OTP
			hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_ClkEn, true, 0x01FFF7C2);
			//hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_ClkEn, true, (IP_PON_Mask|0x01800000));
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//put all modules out of reset (for register access) - 017FF7C2
			// OR IP_PON_Mask with 0x01000000 to also enable ISM
			hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_Rst, false, 0x017FF7C2);
			//hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_Rst, false, (IP_PON_Mask | 0x01000000));
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		else
			HAL_GEC_ASSERT(hal_es3_comparePON_OTP_forIPEn(IP_PON_Mask));
		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.9 - IC Calibration
	DolphinIC_rval_t hal_es3_ISM_Init_Act_9(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		HAL_GERRCODE_INIT;

		// The rest of OTP values (except interface related ones) are loaded

		hal_es3_OTP_LoadFromGlobal(&reg_220_cat1_ES3[0x00], (sizeof(reg_220_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_220_cat2_ES3[0x00], (sizeof(reg_220_cat2_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_234_cat1_ES3[0x00], (sizeof(reg_234_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_23C_cat1_ES3[0x00], 1, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_240_cat2_ES3[0x00], (sizeof(reg_240_cat2_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_244_cat1_ES3[0x00], (sizeof(reg_244_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_244_cat2_ES3[0x00], (sizeof(reg_244_cat2_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_248_cat1_ES3[0x00], (sizeof(reg_248_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_248_cat2_ES3[0x00], (sizeof(reg_248_cat2_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_24C_cat1_ES3[0x00], (sizeof(reg_24C_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_24C_cat2_ES3[0x00], (sizeof(reg_24C_cat2_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_26C_cat1_ES3[0x00], (sizeof(reg_26C_cat1_ES3) / sizeof(OtpTableDiscpES3_t)), IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_OTP_LoadFromGlobal(&reg_270_cat1_ES3[0x01], 2, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.IcCalibrationOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.10 - Configure local bias settings
	DolphinIC_rval_t hal_es3_ISM_Init_Act_10()
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		Nxp_Tef810x_Mod06_BiasBlockRegisterUnion_t			CAFCBiasBlockReg;
		HAL_GERRCODE_INIT;

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_BIAS_BLOCK_REGISTER_U16, &CAFCBiasBlockReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		CAFCBiasBlockReg.bits_st.CtlIbiasEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasTvn20UEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasVam100UEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasLd10UEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasCpOpamp100UEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasBistDac200UEnSpi = 1;
		CAFCBiasBlockReg.bits_st.CtlIbiasDiv350UEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_BIAS_BLOCK_REGISTER_U16, CAFCBiasBlockReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Leave the ADC bias source follower as default
		//glue_reg_WriteCheck(ADC12_MODULE_ADDRESS, NXP_TEF810X_MOD07_BIAS_SOURCE_FOLLOWER_U16, 0x277, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//
		//glue_reg_WriteCheck(ADC34_MODULE_ADDRESS, NXP_TEF810X_MOD07_BIAS_SOURCE_FOLLOWER_U16, 0x277, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.LocalBiasConfigOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.11 - Configure master clock
	DolphinIC_rval_t hal_es3_ISM_Init_Act_11(int32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regVal = 0x0;
//		uint32_t regVal_Pon = 0x0;
//		uint32_t regVal_FuncReset = 0x0;
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;

		HAL_GERRCODE_INIT;

		//Initialize MC
		hal_es3_mclk_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		hal_es3_ISM_MCLKIntegrityCheck(mode, 480.0);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.Pll4GConfigOk = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.12 - Module power up (all IPs) and release functional reset
	DolphinIC_rval_t hal_es3_ISM_Init_Act_12(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		//PON enable IPs from CC
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_Pon, true, IP_PON_Mask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Release Functional reset of all modules
		//put all modules out of reset (for register access)
		// OR IP_PON_Mask with 0x01000000 to also release functional reset for ISM
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, (IP_PON_Mask | 0x01000000));
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.13 - Configure ADC
	DolphinIC_rval_t hal_es3_ISM_Init_Act_13(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		hal_es3_adc_PowerOn();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.14 - Safety sensor configuration
	DolphinIC_rval_t hal_es3_ISM_Init_Act_14(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t regValue = 0x00;
//		int idx1 = 0;
//		Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t		mclkVcoCtrl;
		Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t		cafc_LevelMon;
		Nxp_Tef810x_Mod06_CalLoDetUnion_t					CafcCalLo;
		Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t	CafcFltrPar;
		Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t			RXFuncSafeMonLvlLo;
		Nxp_Tef810x_Mod0D_RmsCalUnion_t						RXRmsCal;
		Nxp_Tef810x_Mod11_RmsControlUnion_t					TXRmsCtrl;
//		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t			TXFuncSafeMonLvlRf;
		Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t	ISMMcuStrtupStat;
		Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t		CAFCFSMonUnlockVco;
//		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t			SupplyErrorMaskReg;
		Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t				TxErrorMaskReg;
		Nxp_Tef810x_Mod11_TsSelUnion_t						TsSel;
		Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t			AdcErrorMaskReg;
		Nxp_Tef810x_Mod18_AdcStatusMonitoringControlUnion_t AdcStatusMonitoringControl;
		Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t FuncsafeMonTemperatureVco;
		Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t Gldo1V1SnsLowConfig;
		Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t Gldo1V1SnsHighConfig;
		Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t Gldo1V8SnsLowConfig;
		Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t Gldo1V8SnsHighConfig;

		HAL_GERRCODE_INIT;

		//First mask all errors from PON disabled IPs
		hal_es3_ISM_MaskErrPONDisabledModule(IP_PON_Mask);


		/***************    CAFC   *************/
		// i . Level Monitor ( Min/Max and High/Low values are coming from OTP)

		//Enable rms detector and set output power as input parameter
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, &CafcCalLo.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CafcCalLo.bits_st.CtlRmsMeasInOutSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, CafcCalLo.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Enable level monitor

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, &cafc_LevelMon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		cafc_LevelMon.bits_st.CtlLevelVcoAmpMonitorEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, cafc_LevelMon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		
		// ii. Vtune Monitor ( Threshold values are coming from OTP)
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE0_U16, &CafcFltrPar.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CafcFltrPar.bits_st.CtlLpfVtuneMonitorEnSpiProfile0 = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE0_U16, CafcFltrPar.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		

		// iii. Unlock Monitor ( The default values require update as follows & Enable )
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16, &CAFCFSMonUnlockVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CAFCFSMonUnlockVco.bits_st.CtlLdEnSpi = 1;
		//change lock detector offset
		//change lock offset to F according to artf722847
		CAFCFSMonUnlockVco.bits_st.CtlLdWindowOffsetSpi = 0xF;
		CAFCFSMonUnlockVco.bits_st.CtlLdWindowDeltaSpi = 0xF;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16, CAFCFSMonUnlockVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		
		//glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, CAFC_FUNCSAFE_MON_UNLOCK_VCO_OFFSET, 0x00100120, NULL);
		// iv. Temperature sensor ( Threshold value is coming from the OTP )

		/***************    RX   *************/
		// i. LO Level Monitor ( M/M from OTP, calibrate L/H values )
		//Information on LO monitor levels:
		//Max/High=527+Code*19.53 
		//Min/Low =117+Code*19.5
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX1_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, &RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			RXFuncSafeMonLvlLo.bits_st.LevelLoMinSpi = 0x1;
			RXFuncSafeMonLvlLo.bits_st.LevelLoLowSpi = 0xA;
			RXFuncSafeMonLvlLo.bits_st.LevelLoHighSpi = 0;
			RXFuncSafeMonLvlLo.bits_st.LevelLoMaxSpi = 0x8;
			glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//Configure RMS detector output as input to level monitor for all RXs
			glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, &RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXRmsCal.bits_st.MeasInOutLoDetSpi = 1;
			glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX2_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, &RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXFuncSafeMonLvlLo.bits_st.LevelLoMinSpi = 0x1;
			RXFuncSafeMonLvlLo.bits_st.LevelLoLowSpi = 0xA;
			RXFuncSafeMonLvlLo.bits_st.LevelLoHighSpi = 0;
			RXFuncSafeMonLvlLo.bits_st.LevelLoMaxSpi = 0x8;
			glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//Configure RMS detector output as input to level monitor for all RXs
			glue_reg_Read(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, &RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXRmsCal.bits_st.MeasInOutLoDetSpi = 1;
			glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX3_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, &RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXFuncSafeMonLvlLo.bits_st.LevelLoMinSpi = 0x1;
			RXFuncSafeMonLvlLo.bits_st.LevelLoLowSpi = 0xA;
			RXFuncSafeMonLvlLo.bits_st.LevelLoHighSpi = 0;
			RXFuncSafeMonLvlLo.bits_st.LevelLoMaxSpi = 0x8;
			glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//Configure RMS detector output as input to level monitor for all RXs
			glue_reg_Read(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, &RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXRmsCal.bits_st.MeasInOutLoDetSpi = 1;
			glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX4_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, &RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXFuncSafeMonLvlLo.bits_st.LevelLoMinSpi = 0x1;
			RXFuncSafeMonLvlLo.bits_st.LevelLoLowSpi = 0xA;
			RXFuncSafeMonLvlLo.bits_st.LevelLoHighSpi = 0;
			RXFuncSafeMonLvlLo.bits_st.LevelLoMaxSpi = 0x8;
			glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16, RXFuncSafeMonLvlLo.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//Configure RMS detector output as input to level monitor for all RXs
			glue_reg_Read(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, &RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			RXRmsCal.bits_st.MeasInOutLoDetSpi = 1;
			glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CAL_U16, RXRmsCal.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		// ii. Temperature Sensor ( Set by OTP )


		/***************    TX   *************/
		//i. Set high and low for the RF level monitor
		//Handled as a part of calibrations


		// ii. RF Level Monitor ( M/M from OTP, H/L to be decided ). Read each TX in case 1 of them is disabled
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX1_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, &TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TXRmsCtrl.bits_st.LevelRfEnableSpi = 1;
			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Temperature Max thresholds loaded from OTP are for 125 degrees, as per user manual increase 3 units to set to 135
			glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			TsSel.bits_st.TsSelSpi = TsSel.bits_st.TsSelSpi + 3;
			//save this to paste to TX2 and 3 in case samples are tested with TP version smaller than v6.xx
			regValue = TsSel.bits_st.TsSelSpi;
			glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}



		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX2_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, &TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TXRmsCtrl.bits_st.LevelRfEnableSpi = 1;
			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//if the OTP has non-zero values, it is ok to use it. If OTP has '0', copy the value from TX1.
			if (TsSel.bits_st.TsSelSpi != 0)
				TsSel.bits_st.TsSelSpi = TsSel.bits_st.TsSelSpi + 3;
			else
				TsSel.bits_st.TsSelSpi = regValue;
			glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX3_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, &TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			TXRmsCtrl.bits_st.LevelRfEnableSpi = 1;
			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_RMS_CONTROL_U16, TXRmsCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, &TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//if the OTP has non-zero values, it is ok to use it. If OTP has '0', copy the value from TX1.
			if (TsSel.bits_st.TsSelSpi != 0)
				TsSel.bits_st.TsSelSpi = TsSel.bits_st.TsSelSpi + 3;
			else
				TsSel.bits_st.TsSelSpi = regValue;
			glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_TS_SEL_U16, TsSel.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		// iii. Temperature Sensor ( Set by OTP )

		/************ Masking of unnecessary flags *****/
		// SSB-MOD low supply, as SSB-MOD is not initialized during the init, it can be ignored until it is activated.
		
				
		//Masking all tx reliablity flag as they are no anymore part of the FS manual
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, &TxErrorMaskReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX1_MODULE_ADDRESS) == DOLPHINIC_NOERROR)
			TxErrorMaskReg.bits_st.RfMaxErrorFlagTx1Mask = 1;
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX2_MODULE_ADDRESS) == DOLPHINIC_NOERROR)
			TxErrorMaskReg.bits_st.RfMaxErrorFlagTx2Mask = 1;
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX3_MODULE_ADDRESS) == DOLPHINIC_NOERROR)
			TxErrorMaskReg.bits_st.RfMaxErrorFlagTx3Mask = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, TxErrorMaskReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Monitoring mode(always/real time) and masking of safety sensors
		hal_es3_ISM_Init_FlagMonitoring();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, &FuncsafeMonTemperatureVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		FuncsafeMonTemperatureVco.bits_st.CtlTempSensorMaxTempThresholdSelSpi = FuncsafeMonTemperatureVco.bits_st.CtlTempSensorMaxTempThresholdSelSpi + 3;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16, FuncsafeMonTemperatureVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		/*****GLDO****/
		//Set SNS delays to maximum

		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, &Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		Gldo1V1SnsLowConfig.bits_st.Sns1V1LowDlySel = 2;
		glue_reg_WriteCheck(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, &Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		Gldo1V1SnsHighConfig.bits_st.Sns1V1HighDlySel = 2;
		glue_reg_WriteCheck(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, &Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		Gldo1V8SnsLowConfig.bits_st.Sns1V8LowDlySel = 2;
		glue_reg_WriteCheck(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, &Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		Gldo1V8SnsHighConfig.bits_st.Sns1V8HighDlySel = 2;
		glue_reg_WriteCheck(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		//Mask all ADC persistent clipping flags (artf620106)
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, &AdcErrorMaskReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AdcErrorMaskReg.bits_st.Adc4NearClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc3NearClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc2NearClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc1NearClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc4ClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc3ClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc2ClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc1ClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc4HardClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc3HardClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc2HardClippingMaskPersistent = 1;
		AdcErrorMaskReg.bits_st.Adc1HardClippingMaskPersistent = 1;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, AdcErrorMaskReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Enable the counter for status monitoring, use hard-clipping errors as input to the counter (artf620106)
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_STATUS_MONITORING_CONTROL_U16, &AdcStatusMonitoringControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		AdcStatusMonitoringControl.bits_st.StatusMonitoringEn = 1;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_STATUS_MONITORING_CONTROL_U16, AdcStatusMonitoringControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Mark the successful sensor configuration in the ISM start-up status register
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, &ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ISMMcuStrtupStat.bits_st.SensorConfigurationDone = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16, ISMMcuStrtupStat.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.15 - Interface toggle test
	DolphinIC_rval_t hal_es3_ISM_Init_Act_15(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		//Requires MCU - GPIO to perform
#ifdef DOLPHIN_CFG_HOST_S32R274
		chip_ISM_InterfaceToggleTest(DOLPHIN_EXTPIO_CHIRPSTART); //Chirp Start 
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_ISM_InterfaceToggleTest(DOLPHIN_EXTPO_READYINT); //Ready Int
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_ISM_InterfaceToggleTest(DOLPHIN_EXTPO_ERRORN); //ErrorN 
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_ISM_InterfaceToggleTest(DOLPHIN_EXTPO_ERRORRESET); //Error Reset 
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX1_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			chip_ISM_InterfaceToggleTest(DOLPHIN_PI_TX1PS); //TX1 Phase Shift
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX2_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			chip_ISM_InterfaceToggleTest(DOLPHIN_PI_TX2PS); //TX2 Phase Shift
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX3_MODULE_ADDRESS) == DOLPHINIC_NOERROR) {
			chip_ISM_InterfaceToggleTest(DOLPHIN_PI_TX3PS); //TX3 Phase Shift
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}	
#endif

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.16 - Data interface test
	DolphinIC_rval_t hal_es3_ISM_Init_Act_16(int32_t mode, uint8_t deci, uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		int modeInt = (mode >= 3) ? (3) : (mode);
		//configure output clock frenquency
		double		init_out_clk_freq	= (mode >= 3) ? (160e6 / deci) : (240e6 / deci);
		uint32_t	intfContextStore	= 0;
		Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t		CSI2TstModeCtrl;
		Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t				LVDSAdcTstDataMux;
		Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t		CIFTstModeCtrl;

		HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_HOST_S32R274
		/* Combo mode to test RR + LVDS/CIF
		if (modeInt != 1)
		{
			DbgInfo("CSI-2 is not chosen! Forcing to use CSI-2 on RR!\n");
			modeInt = 1;
		}
		*/

# ifdef READY_INT_CFG //This block is optional when using S32R274 and used to enable chirp_start and ready_int for validation

		//Enable Ready Int Output Pad
		Nxp_Tef810x_Mod00_ReadyintPadcontrolUnion_t ReadyintPadcontrol;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_READYINT_PADCONTROL_U16, &ReadyintPadcontrol.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ReadyintPadcontrol.bits_st.ReadyintMfioEn = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_READYINT_PADCONTROL_U16, ReadyintPadcontrol.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Enable Chirp Start Output (for measurements)
		Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t ChirpStartPadcontrol;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16, &ChirpStartPadcontrol.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ChirpStartPadcontrol.bits_st.ChirpstartMfioEn = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16, ChirpStartPadcontrol.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Route End of data transfer to interrupt pin
		Nxp_Tef810x_Mod00_IntEnableUnion_t IntEnable;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_INT_ENABLE_U16, &IntEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		IntEnable.bits_st.EndOfDataTnfrIntEn = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_INT_ENABLE_U16, IntEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Configure Ready Int to edge and active at rising edge
		Nxp_Tef810x_Mod00_ReadyIntControlUnion_t ReadyIntControl;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_READY_INT_CONTROL_U16, &ReadyIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		ReadyIntControl.bits_st.InterruptPolarity = 1;
		ReadyIntControl.bits_st.InterruptLevelOrPulse = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_READY_INT_CONTROL_U16, ReadyIntControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

# endif
#endif

		switch (modeInt)
		{
		case 1:
			hal_es3_csi2_Init();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// save the status and configure pattern test with 0x214 fixed pattern value
			glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, &CSI2TstModeCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			intfContextStore = CSI2TstModeCtrl.val_u32;
			//Test data Mode 0x00:Fixed data from Register  0x01:Sinewave pattern  0x2: Increment pattern
			hal_es3_csi2_CfgTestMode(true, 0x214,0x00);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//pattern test
			if (hal_es3_ISM_DataPatternTest(0x214, modeInt, deci) != DOLPHINIC_NOERROR)
			{
				DbgInfo("[IF]Pattern test has failed - CSI2!\n");
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, intfContextStore, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			//configure lvds for pattern test
			hal_es3_OTP_LoadFromGlobal(&reg_23C_cat1_ES3[0x08], 1, IP_PON_Mask);
			//hal_es3_OTP_LoadFromGlobal(&reg_24C_cat1_ES3[0x12], 1);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// select LVDS as interface
			hal_es3_lvds_Init(init_out_clk_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// save the status and configure pattern test with 0x214 fixed pattern value
			glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_ADCTESTDATAMUX_U16, &LVDSAdcTstDataMux.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			intfContextStore = LVDSAdcTstDataMux.val_u32;

			hal_es3_lvds_CfgTestMode();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			if (hal_es3_ISM_DataPatternTest(0x214, modeInt, deci) != DOLPHINIC_NOERROR)
			{
				DbgInfo("[IF]Pattern test has failed - LVDS!\n");
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			//load the original status before handing over to the functional confg.
			glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_ADCTESTDATAMUX_U16, intfContextStore, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			//select CIF-MFIO as interface
			hal_es3_cif_Init(init_out_clk_freq, modeInt);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// save the status and configure pattern test with 0x214 fixed pattern value
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16, &CIFTstModeCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			intfContextStore = CIFTstModeCtrl.val_u32;
			//pattern test
			hal_es3_cif_CfgTestMode();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			if (hal_es3_ISM_DataPatternTest(0x214, modeInt, deci) != DOLPHINIC_NOERROR)
			{
				DbgInfo("[IF]Pattern test has failed - CIF!\n");
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16, intfContextStore, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		}

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//FSM v2.1 section 6.9.3.17 - ISM FIT Test (ISM Integrity Check)
	DolphinIC_rval_t hal_es3_ISM_Init_Act_17(int32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		//call FIT function
		hal_es3_ISM_FIT(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}
	//FSM v2.1 section 6.9.3.xx - ISM GLDO SNS Check 
	DolphinIC_rval_t hal_es3_ISM_Init_Act_18()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		HAL_GERRCODE_INIT;

		//call GLDO SNS CHECK function
		hal_es3_ISM_GLDO_SNS();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_Init_FlagMonitoring()
	{

		Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t SupplyErrorMonRegBits_ust;
		Nxp_Tef810x_Mod18_TxErrorMonRegUnion_t    TxErrorMonRegBits_ust;
		Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t    RxErrorMonRegBits_ust;
		Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t ChirpErrorMonRegBits_ust;
		Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t  McLoErrorMonRegBits_ust;
		Nxp_Tef810x_Mod18_AdcErrorMonRegUnion_t AdcErrorMonRegBits_ust;
//		Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t RfPowerDownControl;

		//uint32_t always_mon_flag[] = { 2147483650, 15, 125829120, 229383, 983055, 2147483904 };
		HAL_GERRCODE_INIT;
		
		//All MC erros are always monitoring Mode
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16, &McLoErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		McLoErrorMonRegBits_ust.bits_st.McPllLevelErrorFlagMon = 1;
		McLoErrorMonRegBits_ust.bits_st.McPllLockErrorFlagMon = 1;
		McLoErrorMonRegBits_ust.bits_st.McPllFreqCalFlagMon = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16, McLoErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//ADC Calibaration Errors
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MON_REG_U16, &AdcErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AdcErrorMonRegBits_ust.bits_st.Adc1CalErrorMonPersistent = 1;
		AdcErrorMonRegBits_ust.bits_st.Adc2CalErrorMonPersistent = 1;
		AdcErrorMonRegBits_ust.bits_st.Adc3CalErrorMonPersistent = 1;
		AdcErrorMonRegBits_ust.bits_st.Adc4CalErrorMonPersistent = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MON_REG_U16, AdcErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//All Supply Errors Except SSB (and PON disabled)
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, &SupplyErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SupplyErrorMonRegBits_ust.bits_st.SupplyHighErrorFlagGlobalLdo1V1Mon = 1;
		//SupplyErrorMonRegBits_ust.bits_st.SupplyHighErrorFlagGlobalLdo1V8Mon = 1;
		//SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagGlobalLdo1V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagGlobalLdo1V1Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagAdc121V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagAdc341V8Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagChirpDig1V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagChirpPll1V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagChirpVco1V8Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagGlobalBias1V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagInterface1V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagMc1V8Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx11V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx11V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx21V1Mon = 1;
		
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx21V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx31V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx31V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx41V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagRx41V8Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagSer1V1Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagSer1V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagCsi21V1Mon = 1;

		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagTx11V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagTx21V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagTx31V8Mon = 1;
		SupplyErrorMonRegBits_ust.bits_st.SupplyLowErrorFlagSsbMod1V8Mon = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, SupplyErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// All Tx Reliabilty and Tempearture Errors

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MON_REG_U16, &TxErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TxErrorMonRegBits_ust.bits_st.TempErrorFlagTx1Mon = 1;
		TxErrorMonRegBits_ust.bits_st.TempErrorFlagTx2Mon = 1;
		TxErrorMonRegBits_ust.bits_st.TempErrorFlagTx3Mon = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MON_REG_U16, TxErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//// All RX Reliabilty Errors
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, &RxErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RxErrorMonRegBits_ust.bits_st.LoMaxErrorFlagRx1Mon = 1;
		RxErrorMonRegBits_ust.bits_st.LoMaxErrorFlagRx2Mon = 1;
		RxErrorMonRegBits_ust.bits_st.LoMaxErrorFlagRx3Mon = 1;
		RxErrorMonRegBits_ust.bits_st.LoMaxErrorFlagRx4Mon = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, RxErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Chirp Reliabilty and Temperature Error
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, &ChirpErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//ChirpErrorMonRegBits_ust.bits_st.LevelMaxErrorFlagChirpMon = 1;
		ChirpErrorMonRegBits_ust.bits_st.MaxTempErrorFlagChirpMon = 1;
		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, ChirpErrorMonRegBits_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_lointf_GainCalibration(void)
	{
		/* DECLARE LOCAL VARIABLES HERE *///
		bool high_flags = 0x0;
		bool low_flags = 0x0;
		uint32_t count = 0x0;
		uint32_t low_threshold = 0;
		uint32_t high_threshold = 0;

		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t		LoInterfaceGainControl;
		Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t	RxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t				RxErrorMonReg;
		Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t				SaveStateRxErrorMonReg;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, &RxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		SaveStateRxErrorMonReg.val_u32 = RxErrorMonReg.val_u32;	//Save copy to restore later
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx4Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx3Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx2Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx1Mon = 0;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, RxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		do {
			glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &LoInterfaceGainControl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			LoInterfaceGainControl.bits_st.GainCodeSel = count;

			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, LoInterfaceGainControl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16, &RxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			high_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx4Masked);

			low_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx4Masked);

			if (high_flags && (LoInterfaceGainControl.bits_st.GainCodeSel == 0x0))
			{
				if (low_flags)
				{
					//Restore Monitoring Flags
					glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, SaveStateRxErrorMonReg.val_u32, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
				}
				else
				{
					break;
				}
			}
			else if (!low_flags)
			{
				low_threshold = count;
			}
			else
			{
				count++;
			}
		} while ((low_flags == 1) && (count != 0x1f));

		DbgInfo("low_threshold is:%d\n", low_threshold);

		do {

			if (high_flags && (LoInterfaceGainControl.bits_st.GainCodeSel == 0x0))
			{
				break;
			}

			low_flags = 0;
			high_flags = 0;

			glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &LoInterfaceGainControl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			LoInterfaceGainControl.bits_st.GainCodeSel = count;

			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, LoInterfaceGainControl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16, &RxErrorFlagMaskedStatus_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			high_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx4Masked);


			low_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx4Masked);


			if (low_flags && (LoInterfaceGainControl.bits_st.GainCodeSel == 0x1f))

			{
				if (high_flags)
				{
					//Restore Monitoring Flags
					glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, SaveStateRxErrorMonReg.val_u32, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
				}
				else
				{
					break;
				}

			}

			else
			{
				count++;
			}
		} while ((high_flags == 0) && (count != 0x1f));

		high_threshold = count - 1;

		DbgInfo("high_threshold is:%d\n", high_threshold);

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &LoInterfaceGainControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		LoInterfaceGainControl.bits_st.GainCodeSel = ((high_threshold + low_threshold) / 2);

		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, LoInterfaceGainControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Restore Monitoring Flags
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, SaveStateRxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}
	DolphinIC_rval_t hal_es3_ISM_lointf_GainCalibration_Mode(int32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		bool high_flags = 0x0;
		bool low_flags = 0x0;
		uint32_t count = 0x0;

		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t		r_LoInterfaceGainControlUnion_t_ust;
		Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t	RxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t				RxErrorMonReg;
		Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t				SaveStateRxErrorMonReg;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, &RxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SaveStateRxErrorMonReg.val_u32 = RxErrorMonReg.val_u32;	//Save copy to restore later
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx4Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx3Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx2Mon = 0;
		RxErrorMonReg.bits_st.LoMaxErrorFlagRx1Mon = 0;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, RxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (mode)
		{
		case 1:
			hal_ES3_CSI2_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		break;
		case 2:
			hal_ES3_LVDS_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		break;
		case 3:
			hal_ES3_CIF_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		break;
		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
		break;
		}
	
		do {


			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			chip_TE_WaitForReady();

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16, &RxErrorFlagMaskedStatus_ust.val_u32, NULL);
			hal_es3_ISM_GetRxErrorStatus(&RxErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			high_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoHighErrorFlagRx4Masked);


			low_flags = (RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx1Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx2Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx3Masked | \
				RxErrorFlagMaskedStatus_ust.bits_st.LoLowErrorFlagRx4Masked);


			glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			if (!(low_flags | high_flags))
			{
				//flag = 1;
				//count = 0x20;
				break;

			}
			else if (high_flags && (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel != 0x0))
			{
				r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel - 1;

			}
			else if (low_flags && (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel != 0x1F))
			{
				r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel + 1;

			}

			else

			{
				//Restore Monitoring Flags
				glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, SaveStateRxErrorMonReg.val_u32, NULL);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);

			}

			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			high_flags = 0x0;
			low_flags = 0x0;
			count++;
		} while (count < 0x20);
		DbgInfo("LO count @ code 0x%x \n", count);
		DbgInfo("Gain code value @ code 0x%x \n", r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel);

		//Restore Monitoring Flags
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16, SaveStateRxErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_ES3_LVDS_Datatoggle_Enable();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (mode)
		{
		case 1:
			hal_ES3_CSI2_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			hal_ES3_LVDS_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			hal_ES3_CIF_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
			break;
		}

		return HAL_GERRCODE;
	}
	DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration(bool txOn[3], uint8_t profile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t				GTxGainProfileBits_t_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			globalCtrl;

		uint8_t  	count = 0x00;
		uint32_t	gain_profileReg;
		uint32_t	TX_moduleID = 0x00;
		uint32_t	globalCtrlbackup;
		uint8_t		tx_id;

		bool error_low = 0;
		bool error_high = 0;
		uint8_t low_threshold = 0;
		uint8_t high_threshold = 0;

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
		// read and save current sequencing mode

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		globalCtrlbackup = globalCtrl.val_u32;

		// change current mode to single profile mode for TX gain calib
		globalCtrl.bits_st.ChirpProfileSelect = profile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//loop through TXs
		for (tx_id = 0x00; tx_id < 0x03; tx_id++)
		{
			//Reset gain counter
			count = 0; 
			//skip unused TXs
			if (txOn[tx_id] == false)
				continue;
			//Select Module ID
			switch (tx_id)
			{
			case 0x00:
				TX_moduleID = TX1_MODULE_ADDRESS;
				break;
			case 0x01:
				TX_moduleID = TX2_MODULE_ADDRESS;
				break;
			case 0x02:
				TX_moduleID = TX3_MODULE_ADDRESS;
				break;
			default:
				break;
			}

			//Find out the Low threshold
			do
			{
				error_low = 0;
				error_high = 0;
				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = count;

				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_teng_StartChirp(); //Neede to update flags, otherwise calibration never happens if part of configuration
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();

				//read TX masked error status
				hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// extract error on certain TX
				switch (tx_id)
				{
				case 0x00:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					break;
				case 0x01:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					break;
				case 0x02:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					break;
				default:
					break;
				}
				//DbgSpecial("Tx%d gain %d h %d l %d L\n", tx_id, count, error_high, error_low);
				if (!error_low)
				{
					low_threshold = count;
					if (error_high)
					{
						//Calibration fails if high latched and low not latched @ very small gain factor.
						HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
					}
				}
				else
				{
					count++;
				}
			} while ((error_low == 1) && (count != 0xff));
			DbgInfo("low_threshold for profile:%d-tx[%d] is:%d\n",profile, tx_id, low_threshold);

			if ((count == 0xff))
			{
				//Calibration fails if low error present @ maximum possible gain factor
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
			}
			//Find out the High threshold

			do
			{
				error_high = 0;
				error_low = 0;
				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = count;

				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


				hal_es3_teng_StartChirp(); //Neede to update flags, otherwise calibration never happens if part of configuration
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();

				//read TX masked error status
				hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// extract error on certain TX
				switch (tx_id)
				{
				case 0x00:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
					break;
				case 0x01:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
					break;
				case 0x02:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
					break;
				default:
					break;
				}

				//DbgSpecial("Tx%d gain %d h %d l %d H\n", tx_id, count, error_high, error_low);
				if (error_high)
				{
					
					if (error_low)
					{
						////Calibration fails if high and low happen at same time.
						HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
					}
				}
				else
				{
					count++;
				}
			} while ((error_high == 0) && (count != 0xff));

			high_threshold = count - 1;

			DbgInfo("high_threshold for profile:%d-tx[%d] is:%d\n", profile, tx_id, high_threshold);

			//Select the midpoint of Low threshold and High Threshold
			glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = (uint32_t)((high_threshold + low_threshold) / 2);

			glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			count = 0;
		}

		// restore saved sequencing mode. .
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrlbackup, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);	

		return HAL_GERRCODE;
	}
	
	DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration_Cubtek(bool txOn[3], uint8_t profile, uint8_t gain_count[3])
	{
//		RTE_services_P rte_srv = get_RTE_Handler();
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t				GTxGainProfileBits_t_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			globalCtrl;

		uint8_t  	count = 0x00;
		uint32_t	gain_profileReg;
		uint32_t	TX_moduleID = 0x00;
		uint32_t	globalCtrlbackup;
		uint32_t    temp_gain;
		uint8_t		tx_id;

		bool error_low = 0;
		bool error_high = 0;
		uint8_t low_threshold = 0;
		uint8_t high_threshold = 0;

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
		// read and save current sequencing mode

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		globalCtrlbackup = globalCtrl.val_u32;

		// change current mode to single profile mode for TX gain calib
		globalCtrl.bits_st.ChirpProfileSelect = profile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//loop through TXs
		for (tx_id = 0x00; tx_id < 0x03; tx_id++)
		{
			//Reset gain counter
			count = 1;
			//skip unused TXs
			if (txOn[tx_id] == false)
				continue;
			//Select Module ID
			switch (tx_id)
			{
			case 0x00:
				TX_moduleID = TX1_MODULE_ADDRESS;
				break;
			case 0x01:
				TX_moduleID = TX2_MODULE_ADDRESS;
				break;
			case 0x02:
				TX_moduleID = TX3_MODULE_ADDRESS;
				break;
			default:
				break;
			}

			//Find out the Low threshold
			do
			{
				error_low = 0;
				error_high = 0;
				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = count;

				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_teng_StartChirp(); //Neede to update flags, otherwise calibration never happens if part of configuration
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();

				//read TX masked error status
				hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// extract error on certain TX
				switch (tx_id)
				{
				case 0x00:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					break;
				case 0x01:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					break;
				case 0x02:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					break;
				default:
					break;
				}
				//DbgSpecial("Tx%d gain %d h %d l %d L\n", tx_id, count, error_high, error_low);
				if (!error_low)
				{
					low_threshold = count;
					if (error_high)
					{
						//Calibration fails if high latched and low not latched @ very small gain factor.
						HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
					}
				}
				else
				{
					count++;
				}			
			} while ((error_low == 1) && (count != 0xff));
			PRINTF("low_threshold for profile:%d-tx[%d] is:%d\n",profile, tx_id, low_threshold);

			if ((count == 0xff))
			{
				//Calibration fails if low error present @ maximum possible gain factor
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
				PRINTF("Can't find the low threshold\n");
			}
			//Find out the High threshold

			do
			{
				error_high = 0;
				error_low = 0;
				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = count;

				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


				hal_es3_teng_StartChirp(); //Neede to update flags, otherwise calibration never happens if part of configuration
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();

				//read TX masked error status
				hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// extract error on certain TX
				switch (tx_id)
				{
				case 0x00:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
					break;
				case 0x01:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
					break;
				case 0x02:
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
					break;
				default:
					break;
				}

				//DbgSpecial("Tx%d gain %d h %d l %d H\n", tx_id, count, error_high, error_low);
				if (error_high)
				{

					if (error_low)
					{
						////Calibration fails if high and low happen at same time.
						HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
					}
				}
				else
				{
					count++;
				}
			} while ((error_high == 0) && (count != 0xff));

			high_threshold = count - 1;

			//DbgInfo("high_threshold for profile:%d-tx[%d] is:%d\n", profile, tx_id, high_threshold);
			PRINTF("high_threshold for profile:%d-tx[%d] is:%d\n", profile, tx_id, high_threshold);

			//Select the midpoint of Low threshold and High Threshold
			glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//*gain_count = (high_threshold + low_threshold) / 2;
			temp_gain  = (high_threshold + low_threshold) / 2;
			if(temp_gain == 0)
				temp_gain = 1;

			if(TX_moduleID > 0)
				gain_count[TX_moduleID-TX1_MODULE_ADDRESS] = temp_gain;
			GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = temp_gain;

			glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			count = 0;
		}

		// restore saved sequencing mode. .
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrlbackup, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}
	
	DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration_Mode(bool txOn[3], uint8_t profile, int32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t				GTxGainProfileBits_t_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			globalCtrl;

		uint32_t	count = 0x0;
		uint32_t	gain_profileReg;
		uint32_t	TX_moduleID = 0x00;
		uint32_t	globalCtrlbackup;
		uint8_t		tx_id;

		bool error_low = 0;
		bool error_high = 0;
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

		switch (mode)
		{
		case 1:
			hal_ES3_CSI2_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			hal_ES3_LVDS_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			hal_ES3_CIF_Datatoggle_Disable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
			break;
		}



		// read and save current sequencing mode

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		globalCtrlbackup = globalCtrl.val_u32;

		// change current mode to single profile mode for TX gain calib
		globalCtrl.bits_st.ChirpProfileSelect = profile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//loop through TXs
		for (tx_id = 0x00; tx_id < 0x03; tx_id++)
		{
			//skip unused TXs
			if (txOn[tx_id] == false)
				continue;

			do
			{
				error_low = 0;
				error_high = 0;

				hal_es3_ISM_SetMCUReset();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_teng_StartChirp(); //Neede to update flags, otherwise calibration never happens if part of configuration
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				chip_TE_WaitForReady();
#ifdef READY_INT_CFG
				//TODO: debug why this delay is necessary when using ready int in previous function
				glue_Sleep(2);
#endif
				//read TX masked error status
				hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				// extract error on certain TX
				switch (tx_id)
				{
				case 0x00:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
					TX_moduleID = TX1_MODULE_ADDRESS;
					break;
				case 0x01:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
					TX_moduleID = TX2_MODULE_ADDRESS;
					break;
				case 0x02:
					error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
					error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
					TX_moduleID = TX3_MODULE_ADDRESS;
					break;
				default:
					break;
				}

				//read current gain
				//TODO: optimize this part, no need to read everytime, keep a local variable to keep track of gain increasing/decreasing since SPI is slow!
				glue_reg_Read(TX_moduleID, gain_profileReg, &GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				if (error_high && (GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 != 0x00))
				{
					GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 - 1;
				}
				else if (error_low && (GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 != 0xFF))
				{
					GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 + 1;
				}
				else if (!(error_high | error_low))
				{
					//succeed
					break;
				}
				else
				{
					//fail and set gain to 0
					glue_reg_WriteCheck(TX_moduleID, gain_profileReg, 0x00, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					// restore saved sequencing mode
					glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrlbackup, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

					HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
				}

				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, GTxGainProfileBits_t_ust.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				count++;
				DbgInfo("TX count @ code 0x%x \n", count);
			} while (count < 0xff);

			if (count >= 0xff)
			{
				//fail and set gain to 0
				glue_reg_WriteCheck(TX_moduleID, gain_profileReg, 0x00, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				// restore saved sequencing mode
				glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrlbackup, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXGAINCALFAIL);
			}

			DbgInfo("tx err is %x\n", TxErrorFlagMaskedStatus_ust.val_u32);
			count = 0x0;
		}

		// restore saved sequencing mode
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, globalCtrlbackup, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		switch (mode)
		{
		case 1:
			hal_ES3_CSI2_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			hal_ES3_LVDS_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			hal_ES3_CIF_Datatoggle_Enable();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_LOGAINCALFAIL);
			break;
		}
		

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_InterfaceToggleTest(int32_t en_pid)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_LoopBackTestRegUnion_t		ISMLoopBackTst;
//		uint32_t reg_loopback = 0x00;
		bool rval = false;
		bool r_h = false, r_l = false;
		bool pin_status;

		HAL_GERRCODE_INIT;

		switch (en_pid)
		{
		case DOLPHIN_EXTPO_ERRORRESET:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN error_reset to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;
			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.ErrorResetDir = 1;

			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			
			// Set the PIN to High ...
			glue_SetGPIO(en_pid, 0x01);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);

			r_h = (ISMLoopBackTst.bits_st.ErrorResetDataOut != 0);

			// Set the PIN to Low ...
			glue_SetGPIO(en_pid, 0x00);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_l = (ISMLoopBackTst.bits_st.ErrorResetDataOut == 0);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;

			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case DOLPHIN_PI_TX1PS:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN tx1_ps to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.Tx1PsDir = 1;

			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// Set the PIN to High ...
			glue_SetGPIO(en_pid, 0x01);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_h = ((ISMLoopBackTst.bits_st.Tx1PsDataOut) != 0x00);


			// Set the PIN to Low ...
			glue_SetGPIO(en_pid, 0x00);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_l = ((ISMLoopBackTst.bits_st.Tx1PsDataOut) == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;

			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case DOLPHIN_PI_TX2PS:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN tx2_ps to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.Tx2PsDir = 1;

			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// Set the PIN to High ...
			glue_SetGPIO(en_pid, 0x01);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_h = ((ISMLoopBackTst.bits_st.Tx2PsDataOut) != 0x00);

			// Set the PIN to Low ...
			glue_SetGPIO(en_pid, 0x00);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_l = ((ISMLoopBackTst.bits_st.Tx2PsDataOut) == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;

			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case DOLPHIN_PI_TX3PS:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN tx3_ps to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.Tx3PsDir = 1;

			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);

			// Set the PIN to High ...
			glue_SetGPIO(en_pid, 0x01);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_h = ((ISMLoopBackTst.bits_st.Tx3PsDataOut) != 0x00);

			// Set the PIN to Low ...
			glue_SetGPIO(en_pid, 0x00);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_l = ((ISMLoopBackTst.bits_st.Tx3PsDataOut) == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;
			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		case DOLPHIN_EXTPO_ERRORN:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN READY_INT to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.ErrorNDir = 0;

			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// Set the PIN to High ...
			ISMLoopBackTst.bits_st.ErrorNDataOut = 1;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_GetGPIO(en_pid, &pin_status);

			r_h = (pin_status != 0x00);

			// Set the PIN to Low ...
			ISMLoopBackTst.bits_st.ErrorNDataOut = 0;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_GetGPIO(en_pid, &pin_status);

			r_l = (pin_status == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;

			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		break;

		// Checking all out PINS from Dolphin ...


		case DOLPHIN_EXTPO_READYINT:
		{
			//Enable the loopback test on central control,
			//Cfg the PIN READY_INT to Input direction ...
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.ReadyIntDir = 0;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);

			// Set the PIN to High ...
			//ISMLoopBackTst.val_u32 |=  ( 0x01 << ISM_LOOP_BACK_TEST_REG_READY_INT_DATA_OUT_POS );
			ISMLoopBackTst.bits_st.ReadyIntDataOut = 1;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);

			glue_Sleep(0.001);

			glue_GetGPIO(en_pid, &pin_status);

			r_h = (pin_status != 0x00);

			// Set the PIN to Low ...
			ISMLoopBackTst.bits_st.ReadyIntDataOut = 0;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);

			glue_Sleep(0.001);

			glue_GetGPIO(en_pid, &pin_status);

			r_l = (pin_status == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;

			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);

		}
		break;

		case DOLPHIN_EXTPIO_CHIRPSTART:
		{
			// Dolphin.ChirpStart <- RR.GPIO[80], Working ...
			//Enable the loopback test on central control,
			ISMLoopBackTst.val_u32 = 0x00;

			ISMLoopBackTst.bits_st.LoopBackTestEn = 1;
			ISMLoopBackTst.bits_st.ChirpStartDir = 1;
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// Set the PIN to High ...
			glue_SetGPIO(en_pid, 0x01);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_h = (ISMLoopBackTst.bits_st.ChirpStartDataOut != 0x00);

			// Set the PIN to Low ...
			glue_SetGPIO(en_pid, 0x00);
			chip_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, &ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_l = (ISMLoopBackTst.bits_st.ChirpStartDataOut == 0x00);

			rval = (r_h & r_l);

			ISMLoopBackTst.val_u32 = 0x00;
			// Restore to initial/Entry state ...
			chip_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16, ISMLoopBackTst.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		break;


		}

		if (rval)
			return HAL_GERRCODE;
		else
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INTFTOGGLETESTFAIL);
	}

	DolphinIC_rval_t hal_es3_ISM_MaskSupplyError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg_ust;

		HAL_GERRCODE_INIT;
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		SupplyErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_UnMaskSupplyError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		SupplyErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_MaskTxError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t TxErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, &TxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		TxErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, TxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_UnMaskTxError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t TxErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, &TxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TxErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16, TxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_MaskRxError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t RxErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16, &RxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RxErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16, RxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_UnMaskRxError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t RxErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16, &RxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RxErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16, RxErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_MaskChirpError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t ChirpErrorMaskReg_ust;

		HAL_GERRCODE_INIT;
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16, &ChirpErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16, ChirpErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_UnMaskChirpError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t ChirpErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16, &ChirpErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16, ChirpErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_MaskMCLOError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t McLoErrorMaskReg_ust;

		HAL_GERRCODE_INIT;
		glue_reg_Read(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16, &McLoErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		McLoErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_Write(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16, McLoErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_UnMaskMCLOError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t McLoErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16, &McLoErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		McLoErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16, McLoErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_MaskADCError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t AdcErrorMaskReg_ust;

		HAL_GERRCODE_INIT;
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, &AdcErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AdcErrorMaskReg_ust.val_u32 |= arg_mask;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, AdcErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_UnMaskADCError(uint32_t arg_mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t AdcErrorMaskReg_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, &AdcErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AdcErrorMaskReg_ust.val_u32 &= ~(arg_mask);

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16, AdcErrorMaskReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetRawMasterErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusUnion_t MasterErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;
		
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_RAW_STATUS_U16, &MasterErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		if (p_status != NULL){ *p_status = MasterErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetRawSupplyErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusUnion_t SupplyErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_RAW_STATUS_U16, &SupplyErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = SupplyErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetRawTxErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_TxErrorFlagRawStatusUnion_t TxErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_RAW_STATUS_U16, &TxErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = TxErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRawRxErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_RxErrorFlagRawStatusUnion_t RxErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_FLAG_RAW_STATUS_U16, &RxErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = RxErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRawChirpErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusUnion_t ChirpErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_RAW_STATUS_U16, &ChirpErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = ChirpErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRawMCLOErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusUnion_t McLoErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_RAW_STATUS_U16, &McLoErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = McLoErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRawADCErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusUnion_t AdcErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_FLAG_RAW_STATUS_U16, &AdcErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = AdcErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRawRFPowDwnErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusUnion_t RfPowerDownErrorFlagRawStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_RAW_STATUS_U16, &RfPowerDownErrorFlagRawStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = RfPowerDownErrorFlagRawStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetMasterErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t MasterErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_MASKED_STATUS_U16, &MasterErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = MasterErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetSupplyErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t SupplyErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_MASKED_STATUS_U16, &SupplyErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = SupplyErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetTxErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16, &TxErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = TxErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetRxErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t RxErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16, &RxErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = RxErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetChirpErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ChirpErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = ChirpErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GetMCLOErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = McLoErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetADCErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t AdcErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_FLAG_MASKED_STATUS_U16, &AdcErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = AdcErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetRFPowDwnErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t RfPowerDownErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_MASKED_STATUS_U16, &RfPowerDownErrorFlagMaskedStatus_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (p_status != NULL){ *p_status = RfPowerDownErrorFlagMaskedStatus_ust.val_u32; }

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_GetISMErrorStatus(uint32_t * p_status)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t IsmErrorStatusAndMcuReset_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ISM_ERROR_STATUS_AND_MCU_RESET_U16, &IsmErrorStatusAndMcuReset_ust.val_u32, NULL);
	
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (p_status != NULL){ *p_status = IsmErrorStatusAndMcuReset_ust.val_u32; }

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_SetMCUReset(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t IsmErrorStatusAndMcuReset_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_ISM_ERROR_STATUS_AND_MCU_RESET_U16, &IsmErrorStatusAndMcuReset_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		IsmErrorStatusAndMcuReset_ust.bits_st.ResetErrorCountMcuSpi = 0x01;
		IsmErrorStatusAndMcuReset_ust.bits_st.ResetErrorMcuSpi = 0x01;

		glue_reg_Write(ISM_MODULE_ADDRESS,   NXP_TEF810X_MOD18_ISM_ERROR_STATUS_AND_MCU_RESET_U16, IsmErrorStatusAndMcuReset_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_SwTXFit(uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		bool bfunrval = false;
		bool bexpErrTrue = false;
		bool bexpErrFalse = false;
		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;

		uint32_t currChirpProfileSetting;

		HAL_GERRCODE_INIT;

		// Step 1: Make sure error_n pin is active high. Otherwise do the recovery actions.

		// Step 2: Disble LO (Reg Addr -0x018 offset 31).
		hal_es3_lointf_EnableLo(false);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		////this is needed for TX_RF_MIN
		//glue_reg_Write(0x18, 0xE4, 0xffffffff, NULL);

		//preserve current profile setting
		
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Step 3: Do dummy trigger and error_n should low.
		//hal_es3_ctrl_CfgChirpTestDefault();
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		chip_TE_WaitForReady();

		// Step 4: Read Ism reg 0x06C offset [9:7]. Make sure these bits are set.
		hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		bexpErrTrue = (TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelFsError | \
			TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelFsError | \
			TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelFsError);

		if (bexpErrTrue == true)
		{
			// Step 5: Enable LO (Reg Addr -0x018 offset 31).
			hal_es3_lointf_EnableLo(true);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Step 6: Clear the Masked status of FS error ...
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			////this is needed for TX_RF_MIN
			//chip_reg_Write(0x18, 0xE4, 0xffffffff, NULL);

			//Needed dwell time for LO to initialize
			glue_Sleep(1);

			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();

			hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			bexpErrFalse = (TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelFsError | \
				TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelFsError | \
				TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelFsError);

			if (bexpErrFalse == false)
			{
				bfunrval = true;
			}
			else
			{
				bfunrval = false;
			}
		}
		else
		{
			hal_es3_lointf_EnableLo(true);
			bfunrval = false;
		}

		//restore chirp profile setting
		ChirpGCon.bits_st.ChirpProfileSelect = currChirpProfileSetting;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);


		if (bfunrval)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_TXSENSORFITFAIL);
		}
	}
	DolphinIC_rval_t hal_es3_ISM_Sw_FIT(uint8_t fitProfile, bool TxPON[3])
		{
			HAL_GERRCODE_INIT;

			//bool bfunrval = false;
			bool bexpErrTrue = false;
			bool tx1_temp = false;
			bool tx2_temp = false;
			bool tx3_temp = false;
			//bool bexpErrFalse = false;
			uint8_t ivco_current;
			uint8_t subband_current;
			//uint32_t regValue;
			uint32_t vco_register;

			Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_vcoregisterprofile;
			Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
			Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;
			Nxp_Tef810x_Mod06_ControlSpareUnion_t				ControlSpare;
			Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t	funcReset;
			Nxp_Tef810x_Mod06_ControlSpareUnion_t	ctrlSpareBackup;

			switch (fitProfile){
			case 0:
			{
				vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
				break;
			}
			case 1:
			{
				vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
				break;
			}
			case 2:
			{
				vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
				break;
			}
			case 3:
			{
				vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
				break;
			}
			default:
			{
				vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
				break;
			}
			}

			//enable auto CAFC func reset
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, &ControlSpare.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//save original setting
			ctrlSpareBackup = ControlSpare;

			ControlSpare.bits_st.DisableHardFuncReset = 0;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, ControlSpare.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Disble LO (Reg Addr -0x018 offset 31).
			hal_es3_lointf_EnableLo(false);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Read current ivco and subband value in the chirp vco register profile_x//
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Store ivco value and subband value locally//
			ivco_current    = r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0;
			subband_current = r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0;

			//Inject error//
			r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = 0;
			r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 - 0x1D;

			//Rewrite VCO reg value//
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//preserve current profile setting in TE
			Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGCon;
			glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			uint32_t currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
			//change it to using fitProfile
			ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
			ChirpGCon.bits_st.ChirpStart = 0;	//Ensure we don't trigger a chirp
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL); //Cannot be writeCheck as register value changes
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Dummy chirp with profile_x// Expecting a chirp min error
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();

			//Without it during tests the read ISM values were not correct.
			glue_Sleep(0.04);

			//Read TX masked status in ISM;
			hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Read chirp masked status in ISM;
			hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Extract chirp min/unlock and Tx min;
			tx1_temp = TxPON[0] ? TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelFsError : 1;
			tx2_temp = TxPON[1] ? TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelFsError : 1;
			tx3_temp = TxPON[2] ? TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelFsError : 1;

			bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMinErrorFlagChirp & ChirpErrorFlagMaskedStatus_ust.bits_st.UnlockErrorFlagChirpSync &
				          (tx1_temp & tx2_temp & tx3_temp);
			

           //Re cofig the settings
			 r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = ivco_current;
			 r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband_current;
			 hal_es3_lointf_EnableLo(true);

		   //Register re write;
			 glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			 HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			 //if in normal chirp configuration, user disabled auto CAFC func reset
			 if (ctrlSpareBackup.bits_st.DisableHardFuncReset == 1)
			 {
				 // toggle CAFC func reset manually to restore from lock step error
				 glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &funcReset.val_u32, NULL);
				 HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
				 funcReset.bits_st.FnResetChirp = 0;

				 glue_reg_Write(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, funcReset.val_u32, NULL);
				 HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				 funcReset.bits_st.FnResetChirp = 1;
				 glue_reg_Write(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, funcReset.val_u32, NULL);
				 HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			 }

			//ISM Reset
			 hal_es3_ISM_SetMCUReset();
			 HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			//restore chirp profile setting
			ChirpGCon.bits_st.ChirpProfileSelect = currChirpProfileSetting;
			ChirpGCon.bits_st.ChirpStart = 0; //Ensure we don't trigger a chirp
			glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL); //Cannot be writeCheck as register value changes
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//restore original auto CAFC func reset setting
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, ctrlSpareBackup.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			if (bexpErrTrue)
			{
				return HAL_GERRCODE;
			}
			else
			{
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_CAFCMINSENSORFITFAIL);

			}
		}

	DolphinIC_rval_t hal_es3_ISM_SwChirp_Min_error(uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		bool bfunrval = false;
		bool bexpErrTrue = false;
		bool bexpErrFalse = false;
		uint8_t		ivco_current;
//		uint32_t	regValue;
		uint32_t	vco_register = 0x00;
		uint32_t	currChirpProfileSetting; 
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			r_vcoregisterprofile;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;
		Nxp_Tef810x_Mod06_ControlSpareUnion_t				ControlSpare;
		uint32_t	ctrlSpareBackup;

		HAL_GERRCODE_INIT;

		switch (fitProfile){
		case 0:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		}
		case 1:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		}
		case 2:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		}
		case 3:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		}
		}

		//enable auto CAFC func reset
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, &ControlSpare.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//save original setting
		ctrlSpareBackup = ControlSpare.val_u32;

		ControlSpare.bits_st.DisableHardFuncReset = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, ControlSpare.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 1:Read current ivco in the chirp vco register profile0//
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 2:Store ivco value locally//
		ivco_current = r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0;

		//Step 3:Decrease ivco value to inject chirp min error//
		r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = 0;

		//Step 4:Rewrite VCO reg value//
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve current profile setting

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 5:Dummy chirp with profile0// Expecting a chirp min error
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();

		//Step 6:Read chirp masked status in ISM;
		hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 7:Extract only chirp min error;

		bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMinErrorFlagChirp;

		//check
		if (bexpErrTrue == true)//Test pass
		{
			//Step 8:Reconfig ivco;
			r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = ivco_current;

			//Step 9:Register re write;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//step 9.1 clear min error and low error
			hal_es3_ISM_SetMCUReset();
			//glue_reg_WriteCheck(ISM_MODULE_ADDRESS, ISM_CHIRP_ERROR_CLR_REG_OFFSET, 0xFFFFFFFF,NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Step 10:Dummy trigger with profile0;
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();

			//Step 11:Read chrip masked status;
			hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Step 12:Extract chirp min error;
			bexpErrFalse = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMinErrorFlagChirp;
			//check
			if (bexpErrFalse == false)//Test pass
				bfunrval = true;
			else
				bfunrval = false;
		}
		else
		{
			//restore ivco setting
			r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = ivco_current;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			bfunrval = false;
		}

		//restore chirp profile setting
		ChirpGCon.bits_st.ChirpProfileSelect = currChirpProfileSetting;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//restore original auto CAFC func reset setting
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CONTROL_SPARE_U16, ctrlSpareBackup, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (bfunrval)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CAFCMINSENSORFITFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_SwChirp_Unlock_error(uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		bool bfunrval = false;
		bool bexpErrTrue = false;
		bool bexpErrFalse = false;
		uint8_t subband_current;
//		uint32_t regValue;
		uint32_t vco_register = 0x00;
		uint32_t currChirpProfileSetting;

		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			r_vcoregisterprofile;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;

		HAL_GERRCODE_INIT;

		switch (fitProfile){
		case 0:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		}
		case 1:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		}
		case 2:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		}
		case 3:
		{
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		}
		}

		//Step 1:Read current ivco in the chirp vco register profile0//
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 2:Store ivco value locally//
		subband_current = r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0;

		//Step 3:Decrease ivco value to inject chirp min error//
		r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 - 0x1D;

		//Step 4:Rewrite VCO reg value//
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve current profile setting
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Step 5:Dummy chirp with profileX// Expecting a chirp min error
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();

		//Step 6:Read chirp masked status in ISM;
		hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 7:Extract only chirp min error;
		bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.UnlockErrorFlagChirpSync;

		//check
		if (bexpErrTrue == true)//Test pass
		{
			//Step 8:Reconfig ivco;
			r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband_current;

			//Step 9:Register re write;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//step 9.1 clear unlock error
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//glue_reg_Write(ISM_MODULE_ADDRESS, ISM_CHIRP_ERROR_CLR_REG_OFFSET, 0xFFFFFFFF,NULL);

			//Step 10:Dummy trigger with profile0;
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();

			//Step 11:Read chirp masked status;
			hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Step 12:Extract chirp min error;
			bexpErrFalse = ChirpErrorFlagMaskedStatus_ust.bits_st.UnlockErrorFlagChirpSync;

			//check
			if (bexpErrFalse == false)//Test pass
			{
				bfunrval = true;
			}
			else
			{
				bfunrval = false;
			}
		}
		else
		{
			r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband_current;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			bfunrval = false;
		}

		//restore chirp profile setting
		ChirpGCon.bits_st.ChirpProfileSelect = currChirpProfileSetting;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (bfunrval)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CAFCUNLOCKSENSORFITFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Tx_Low_Status(uint8_t TX_numb, uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t TX_ADDRESS = 0x00;
		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
//		uint32_t MSK;
//		uint32_t POS;

		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t r_TxGainProfile_ust;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s tx %d profile %d\n", __FUNCTION__, TX_numb, profile_num);

		//Select the TX
		switch (TX_numb)
		{
		case 1:
		{
			TX_ADDRESS = TX1_MODULE_ADDRESS;

			break;
		}
		case 2:
		{
			TX_ADDRESS = TX2_MODULE_ADDRESS;

			break;
		}
		case 3:
		{
			TX_ADDRESS = TX3_MODULE_ADDRESS;

			break;
		}
		default:
			break;
		}
		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
			break;
		default:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		}
		//step 1: Read current Tx gain
		glue_reg_Read(TX_ADDRESS, REG_ADDRESS, &r_TxGainProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//step 2:Increase tx gain
		if (r_TxGainProfile_ust.bits_st.GTxGainProfile0 != 0xff) //Check for max gain
		{
			r_TxGainProfile_ust.bits_st.GTxGainProfile0 = r_TxGainProfile_ust.bits_st.GTxGainProfile0 + 0x1;
			glue_reg_WriteCheck(TX_ADDRESS, REG_ADDRESS, r_TxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Tx_High_Status(uint8_t TX_numb, uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t TX_ADDRESS = 0x00;
		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
//		uint32_t MSK;
//		uint32_t POS;

		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t r_TxGainProfile_ust;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s tx %d profile %d\n", __FUNCTION__, TX_numb, profile_num);

		//Select the TX
		switch (TX_numb)
		{
		case 1:
		{
			TX_ADDRESS = TX1_MODULE_ADDRESS;

			break;
		}
		case 2:
		{
			TX_ADDRESS = TX2_MODULE_ADDRESS;

			break;
		}
		case 3:
		{
			TX_ADDRESS = TX3_MODULE_ADDRESS;

			break;
		}
		default:
			break;
		}

		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
			break;
		default:
			//REG_ADDRESS = TX_G_TX_GAIN_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		}
		//step 1: Read current Tx gain
		glue_reg_Read(TX_ADDRESS, REG_ADDRESS, &r_TxGainProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//step 2:Decrease tx gain
		if (r_TxGainProfile_ust.bits_st.GTxGainProfile0 != 0x00)
		{
			r_TxGainProfile_ust.bits_st.GTxGainProfile0 = r_TxGainProfile_ust.bits_st.GTxGainProfile0 - 0x1;
			glue_reg_WriteCheck(TX_ADDRESS, REG_ADDRESS, r_TxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//glue_reg_Read(TX_ADDRESS, REG_ADDRESS, r_TxGainProfile_ust.val_u32, NULL);

			glue_reg_Read(TX_ADDRESS, REG_ADDRESS, &r_TxGainProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);




			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Rx_Low_Status()
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t r_LoInterfaceGainControlUnion_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		if (r_LoInterfaceGainControlUnion_ust.bits_st.GainCodeSel != 0x1f)
		{
			r_LoInterfaceGainControlUnion_ust.bits_st.GainCodeSel++;
			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Rx_High_Status()
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t r_LoInterfaceGainControlUnion_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_LoInterfaceGainControlUnion_ust.bits_st.GainCodeSel != 0x0)
		{
			r_LoInterfaceGainControlUnion_ust.bits_st.GainCodeSel--;
			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}


	DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVtune_Low_Status(uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_ChirpVCOProfile_ust;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s profile %d\n", __FUNCTION__, profile_num);

		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		default:

			break;
		}
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, &r_ChirpVCOProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 != 0x00)
		{
			r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 = r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 - 0x1;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, r_ChirpVCOProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVtune_High_Status(uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_ChirpVCOProfile_ust;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s profile %d\n", __FUNCTION__, profile_num);

		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		default:

			break;
		}
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, &r_ChirpVCOProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 != 0x7f)
		{
			r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 = r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0 + 0x1;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, r_ChirpVCOProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVco_Low_Status(uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_ChirpVCOProfile_ust;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s profile %d\n", __FUNCTION__, profile_num);

		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		default:

			break;
		}
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, &r_ChirpVCOProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 != 0x1f)
		{
			r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 = r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 + 0x1;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, r_ChirpVCOProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
		}
	}


	DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVco_High_Status(uint8_t profile_num)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		int16_t REG_ADDRESS = 0x00;
//		uint32_t regValue;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_ChirpVCOProfile_ust;
		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s profile %d\n", __FUNCTION__, profile_num);

		//Select the profile
		switch (profile_num)
		{
		case 0:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE0_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE1_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE2_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			//REG_ADDRESS = CAFC_VCO_REGISTER_PROFILE3_OFFSET;
			REG_ADDRESS = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		
		default:
			break;
		}


		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, &r_ChirpVCOProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		if (r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 != 0x00)
		{
			r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 = r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0 - 0x1;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, REG_ADDRESS, r_ChirpVCOProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);

		}
		
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Chirp_MaxTemp_Status(uint32_t Cool_time)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

//		uint32_t regValue;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s time %d\n", __FUNCTION__, Cool_time);

		// //step 1:Give cool time and clear the error;
		// glue_Sleep(Cool_time);


		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_Tx_MaxTemp_Status(uint8_t TX_numb, uint32_t Cool_time)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

//		uint32_t MSK;
//		uint32_t POS;
//		uint32_t regValue;

		HAL_GERRCODE_INIT;

		DbgInfo("Called recovery function %s tx %d time %d\n", __FUNCTION__, TX_numb, Cool_time);
		//TODO: fix for ES3, internal bits
		//Select the TX
		switch (TX_numb)
		{
		case 1:
		{
//			MSK = 0x8;
//			POS = 0x3;
		}
		break;
		case 2:
		{
			//MSK = ISM_TX_ERROR_CLR_REG_TEMP_ERROR_FLAG_TX2_CLR_MSK;
			//POS = ISM_TX_ERROR_CLR_REG_TEMP_ERROR_FLAG_TX2_CLR_POS;
//			MSK = 0x10;
//			POS = 0x04;
		}
		break;

		default:
		case 3:
		{
			//MSK = ISM_TX_ERROR_CLR_REG_TEMP_ERROR_FLAG_TX3_CLR_MSK;
			//POS = ISM_TX_ERROR_CLR_REG_TEMP_ERROR_FLAG_TX3_CLR_POS;
//			MSK = 0x20;
//			POS = 0x5;
		}
		break;
		}

		//step 1:Give cool time
		glue_Sleep(Cool_time);

		//step 2:Clear the status bit

		return HAL_GERRCODE;
	}

	//DolphinIC_rval_t hal_es3_ISM_StatusCheckAndRecover()
	//{
	//	///* DECLARE LOCAL VARIABLES HERE *///

	//	uint32_t regValue = 0;
	//	uint8_t errorBit = 0;
	//	DolphinIC_rval_t result = DOLPHINIC_NOERROR;
	//	uint8_t startProfile = 0;
	//	uint8_t profile = 0;
	//	uint8_t nProfiles = 1;
	//	bool rx_fixed = false;
	//	Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		r_globalcontrol;
	//	Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t	ISMStatusMonFlg;
	//	HAL_GERRCODE_INIT;

	//	glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &r_globalcontrol.val_u32, NULL);
	//	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	//	
	//	startProfile = (r_globalcontrol.bits_st.ChirpProfileSelect < 4) ? r_globalcontrol.bits_st.ChirpProfileSelect : 0;
	//	nProfiles = (r_globalcontrol.bits_st.ChirpProfileSelect >= 4) ? r_globalcontrol.bits_st.ChirpProfileSelect - 2 : 1;

	//	glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_STATUS_MONITORING_FLAG_U16, &ISMStatusMonFlg.val_u32, NULL);
	//	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	//	regValue = ISMStatusMonFlg.val_u32;	
	//	for (errorBit = 0; (errorBit < 23) && (regValue != 0x0); errorBit++){
	//		if ((regValue & 0x1) == 1){
	//			for (profile = startProfile; profile < (nProfiles + startProfile); profile++){
	//				DbgInfo("Recover for bit: %d profile: %d\n", errorBit, profile);
	//				switch (errorBit){
	//				case 0:
	//					//chirp_vco_level_low_error_flag_chirp_to_mcu
	//					result += hal_es3_ISM_Recover_ChirpVco_Low_Status(profile);
	//					break;
	//				case 1:
	//					//chirp_vco_level_high_error_flag_chirp_to_mcu
	//					result += hal_es3_ISM_Recover_ChirpVco_High_Status(profile);
	//					break;
	//				case 2:
	//					//chirp_vtune_low_error_flag_chirp_to_mcu
	//					result += hal_es3_ISM_Recover_ChirpVtune_Low_Status(profile);
	//					break;
	//				case 3:
	//					//chirp_vtune_high_error_flag_chirp_to_mcu
	//					result += hal_es3_ISM_Recover_ChirpVtune_High_Status(profile);
	//					break;
	//				case 4:
	//					//rx1_lo_low_error_flag
	//				case 5:
	//					//rx2_lo_low_error_flag
	//				case 6:
	//					//rx3_lo_low_error_flag
	//				case 7:
	//					//rx4_lo_low_error_flag
	//					if (!rx_fixed){
	//						result += hal_es3_ISM_Recover_Rx_Low_Status();
	//						rx_fixed = true;
	//					}
	//					break;
	//				case 8:
	//					//rx1_lo_high_error_flag
	//				case 9:
	//					//rx2_lo_high_error_flag
	//				case 10:
	//					//rx3_lo_high_error_flag
	//				case 11:
	//					//rx4_lo_high_error_flag
	//					if (!rx_fixed){
	//						result += hal_es3_ISM_Recover_Rx_High_Status();
	//						rx_fixed = true;
	//					}
	//					break;
	//				case 12:
	//					//tx1_pa_low_error_flag
	//				case 13:
	//					//tx2_pa_low_error_flag
	//				case 14:
	//					//tx3_pa_low_error_flag
	//					if (!rx_fixed){
	//						result += hal_es3_ISM_Recover_Tx_Low_Status(errorBit - 11, profile);
	//					}
	//					break;
	//				case 15:
	//					//tx1_pa_high_error_flag
	//				case 16:
	//					//tx2_pa_high_error_flag
	//				case 17:
	//					//tx3_pa_high_error_flag
	//					if (!rx_fixed){
	//						result += hal_es3_ISM_Recover_Tx_High_Status(errorBit - 14, profile);
	//					}
	//					break;
	//				case 18:
	//					//mc_pll_freq_calib_error_flag
	//					result += hal_es3_mclk_Recalibrate();
	//					break;
	//				case 19:
	//					//temp_error_flag_tx1
	//				case 20:
	//					//temp_error_flag_tx2
	//				case 21:
	//					//temp_error_flag_tx3
	//					result += hal_es3_ISM_Recover_Tx_MaxTemp_Status(errorBit - 18, 10);
	//					break;
	//				case 22:
	//					//max_temp_error_flag_chirp
	//					result += hal_es3_ISM_Recover_Chirp_MaxTemp_Status(10);
	//					break;
	//				}
	//			}
	//		}
	//		regValue >>= 1;
	//	}

	//	if (result == 0)
	//		return HAL_GERRCODE;
	//	else
	//		HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
	//}

//The below function is implemented with the following assumptions
//1. This function is guaranteed only for single profile case.
//2. This function assumes that if low flag is set then the high flag will not set and viceversa.
//3. For Multiprofile case we cannot the gurantee that this function can recover because of step 2. In multiprofile case low flag can set from
// one profile and high flag from other profile. In Multiporfile case a Debug Info will pop up.

DolphinIC_rval_t hal_es3_ISM_StatusCheckAndRecover()
{
	///* DECLARE LOCAL VARIABLES HERE *///

//	uint32_t regValue = 0;
	uint8_t errorBit = 0;
	DolphinIC_rval_t result = DOLPHINIC_NOERROR;
	uint8_t startProfile = 0;
	uint8_t profile = 0;
	uint8_t nProfiles = 1;
//	bool rx_fixed = false;
	Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		r_globalcontrol;
	Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t	ISMStatusMonFlg;
	Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t AdcErrorFlagMaskedStatus;
	Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountUnion_t AdcStatusErrorFlagCount;
	HAL_GERRCODE_INIT;

	glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &r_globalcontrol.val_u32, NULL);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	startProfile = (r_globalcontrol.bits_st.ChirpProfileSelect < 4) ? r_globalcontrol.bits_st.ChirpProfileSelect : 0;
	nProfiles = (r_globalcontrol.bits_st.ChirpProfileSelect >= 4) ? r_globalcontrol.bits_st.ChirpProfileSelect - 2 : 1;

	if (r_globalcontrol.bits_st.ChirpProfileSelect >= 4)
	{
		DbgInfo("Status Recovery For Multiprofile is initiated!");
	}


	glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_STATUS_MONITORING_FLAG_U16, &ISMStatusMonFlg.val_u32, NULL);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
//	regValue = ISMStatusMonFlg.val_u32;

	//Read ADC clipping flags seperately, since not a part of the status monitoring flag register (artf620106)
	glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_ERROR_FLAG_MASKED_STATUS_U16, &AdcErrorFlagMaskedStatus.val_u32, NULL);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


	if (ISMStatusMonFlg.val_u32 == 0)
	{
		return HAL_GERRCODE;
	}
	else if (ISMStatusMonFlg.bits_st.MaxTempErrorFlagChirp |
		ISMStatusMonFlg.bits_st.TempErrorFlagTx1 |
		ISMStatusMonFlg.bits_st.TempErrorFlagTx2 |
		ISMStatusMonFlg.bits_st.TempErrorFlagTx3)
	{
		glue_Sleep(10);
		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}
	else if (ISMStatusMonFlg.bits_st.McPllFreqCalibErrorFlag)
	{
		hal_es3_mclk_Recalibrate();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}
	else
	{
		for (errorBit = 5; errorBit < 17; errorBit++)
		{
			for (profile = startProfile; profile < (nProfiles + startProfile); profile++)
			{
				switch (errorBit)
				{
				case 5:
					//chirp_vtune_low_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.ChirpVtuneLowErrorFlagChirpToMcu)
					{
						if (ISMStatusMonFlg.bits_st.ChirpVtuneHighErrorFlagChirpToMcu)
						{
							DbgErr("Vtune Low and Vtune High occured at the same time!");
							HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
						}
												
						result += hal_es3_ISM_Recover_ChirpVtune_Low_Status(profile);
						//errorBit++; //If vtune low is set no need to check vtune high.
					}
					break;
				case 6:
					//chirp_vtune_High_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.ChirpVtuneHighErrorFlagChirpToMcu)
					{
						result += hal_es3_ISM_Recover_ChirpVtune_High_Status(profile);

					}
					break;
				case 7:
					//chirp_VCO_low_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.ChirpVcoLevelLowErrorFlagChirpToMcu)
					{
						if (ISMStatusMonFlg.bits_st.ChirpVcoLevelHighErrorFlagChirpToMcu)
						{
							DbgErr("VCO Low and VCO High occured at the same time!");
							HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
						}


						result += hal_es3_ISM_Recover_ChirpVco_Low_Status(profile);
						//errorBit++; //If VCO low is set no need to check vtune high.
					}
					break;
				case 8:
					//chirp_VCO_High_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.ChirpVcoLevelHighErrorFlagChirpToMcu)
					{
						result += hal_es3_ISM_Recover_ChirpVco_High_Status(profile);

					}
					break;
				case 9:
					//RX_High_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.Rx1LoHighErrorFlag |
						ISMStatusMonFlg.bits_st.Rx2LoHighErrorFlag |
						ISMStatusMonFlg.bits_st.Rx3LoHighErrorFlag |
						ISMStatusMonFlg.bits_st.Rx4LoHighErrorFlag)
					{
						result += hal_es3_ISM_Recover_Rx_High_Status();
						//errorBit++;
					}


					break;

				case 10:
					//RX_Low_error_flag_chirp_to_mcu
					if (ISMStatusMonFlg.bits_st.Rx1LoLowErrorFlag |
						ISMStatusMonFlg.bits_st.Rx2LoLowErrorFlag |
						ISMStatusMonFlg.bits_st.Rx3LoLowErrorFlag |
						ISMStatusMonFlg.bits_st.Rx4LoLowErrorFlag)
					{
						result += hal_es3_ISM_Recover_Rx_Low_Status();
					}

					break;

				case 11:
					//Tx1_High_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx1PaHighErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_High_Status(1, profile);
//						//errorBit++;
//					}
					break;
				case 12:
//					//Tx1_Low_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx1PaLowErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_Low_Status(1, profile);
//						//errorBit++;
//					}
					break;
				case 13:
					//Tx2_High_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx2PaHighErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_High_Status(2, profile);
//						//errorBit++;
//					}
					break;
				case 14:
					//Tx2_Low_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx2PaLowErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_Low_Status(2, profile);
//						//errorBit++;
//					}
					break;

				case 15:
					//Tx3_High_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx3PaHighErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_High_Status(3, profile);
//						//errorBit++;
//					}
					break;
				case 16:
					//Tx3_Low_error_flag_chirp_to_mcu
//					if (ISMStatusMonFlg.bits_st.Tx3PaLowErrorFlag)
//					{
//						result += hal_es3_ISM_Recover_Tx_Low_Status(3, profile);
//						//errorBit++;
//					}
					break;
				}


				if (AdcErrorFlagMaskedStatus.bits_st.Adc1HardClippingErrorFlagMasked || AdcErrorFlagMaskedStatus.bits_st.Adc2HardClippingErrorFlagMasked
					|| AdcErrorFlagMaskedStatus.bits_st.Adc3HardClippingErrorFlagMasked || AdcErrorFlagMaskedStatus.bits_st.Adc4HardClippingErrorFlagMasked)
				{
					glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_ADC_STATUS_ERROR_FLAG_COUNT_U16, &AdcStatusErrorFlagCount.val_u32, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
					//set a treshold here depending on the purpose of using the flag
					if(AdcStatusErrorFlagCount.val_u32 > 128)
						DbgErr("Hard clipping of one or more ADC channels is detected!");
					//no action is taken by the Dolphin at this point.
					//action to be taken depends on the failure scenario that the system integrator is focusing on and how they want to avoid it.
				}


				

			}

		}


		//hal_es3_ISM_SetMCUReset();
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (result == 0)
			return HAL_GERRCODE;
		else
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL);
	}
}


	DolphinIC_rval_t hal_es3_ISM_RFBIST_Static_config()
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		//**********This API assume that profile 3 is used only as test profile so changes doing here may not be reconfigured.*********//

		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t		IpLevelPonEnable;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t		FunctionalResetControl;
		Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t		ssb_ldo_u;
		Nxp_Tef810x_Mod14_SsbmodControlUnion_t			SsbmodControlBits_u;
		Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t	TimingControl3ProfileUnion_u;
		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg_u;

		HAL_GERRCODE_INIT;
		//Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t DnChirpRfProfileUnion_u;
		//Enable SSBMOD LDO
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16, &ssb_ldo_u.val_u32, NULL); //ldo_en_ssbmod=1;ldo_sel_vout_ssbmod=B;
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		ssb_ldo_u.bits_st.LdoEnSsbmod = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16, ssb_ldo_u.val_u32, NULL); //ldo_en_ssbmod=1;ldo_sel_vout_ssbmod=B;
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Unmask SSB Supply Error
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SupplyErrorMaskReg_u.bits_st.SupplyLowErrorFlagSsbMod1V8Mask = 0;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		// cc Tx_pon off
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &IpLevelPonEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		IpLevelPonEnable.bits_st.PonSsbmod = 1;
		IpLevelPonEnable.bits_st.PonTx1 = 0;
		IpLevelPonEnable.bits_st.PonTx2 = 0;
		IpLevelPonEnable.bits_st.PonTx3 = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, IpLevelPonEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// cc SSBMOD out frst
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &FunctionalResetControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FunctionalResetControl.bits_st.FnResetSsbmod = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FunctionalResetControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//ssb
		glue_reg_Read(SSBMOD_MODULE_ADDRESS, NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16, &SsbmodControlBits_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SsbmodControlBits_u.bits_st.Clk600En = 1;
		SsbmodControlBits_u.bits_st.PonLsSpi = 1;
		SsbmodControlBits_u.bits_st.Div2Set = 1;
		SsbmodControlBits_u.bits_st.Div1Set = 0xE;
		SsbmodControlBits_u.bits_st.SsbmodEn = 1;
		glue_reg_WriteCheck(SSBMOD_MODULE_ADDRESS, NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16, SsbmodControlBits_u.val_u32, NULL);//clk_600_en=1 ,div 1 = 15 div 2=4;
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//sweep control
		//glue_reg_Write (SWEEP_CONTROL_MODULE_ADDRESS,SCTRL_DN_CHIRP_RF_PROFILE3_OFFSET,0x00000000, NULL); //Disable DN_Frequncy increment
		//glue_reg_Write (SWEEP_CONTROL_MODULE_ADDRESS,SCTRL_N_STEP_CHIRP_RF_PROFILE3_OFFSET,0x00000000, NULL); //Disable DN_Step increment
		//glue_reg_Write (SWEEP_CONTROL_MODULE_ADDRESS,SCTRL_N_STEP_RESET_RF_PROFILE3_OFFSET,0x00000000, NULL); //Disable DN_Reset_Frequncy increment
		//glue_reg_Write (SWEEP_CONTROL_MODULE_ADDRESS,SCTRL_DIV_UPDATE_RF_PROFILE3_OFFSET,0x00000000, NULL); //Disable DN_Reset_Step increment

		//Rx
		//Set Rx gain to Max
		Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t GRxSetProfile3;
		glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16, &GRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		GRxSetProfile3.bits_st.GainRxSetProfile0 = 0x7;
		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16, GRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16, GRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16, GRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16, GRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rx1 LPF ctrl to max: wideband mode
		Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t LpfRxSetProfile3;
		glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16, &LpfRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		LpfRxSetProfile3.bits_st.LpfRxCornerSetProfile0 = 1;
		LpfRxSetProfile3.bits_st.LpfRxFineSetProfile0 = 0xF;
		LpfRxSetProfile3.bits_st.LpfRxSetProfile0 = 0;
		
		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16, LpfRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16, LpfRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16, LpfRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16, LpfRxSetProfile3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE3_U16, &TimingControl3ProfileUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TimingControl3ProfileUnion_u.bits_st.Rx1ActiveProfile0 = 0;
		TimingControl3ProfileUnion_u.bits_st.Rx2ActiveProfile0 = 0;
		TimingControl3ProfileUnion_u.bits_st.Rx3ActiveProfile0 = 0;
		TimingControl3ProfileUnion_u.bits_st.Rx4ActiveProfile0 = 0;
		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE3_U16, TimingControl3ProfileUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_RFBIST_LnaTest()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		Nxp_Tef810x_Mod0D_RxControlUnion_t RxControlUnion_u;
		Nxp_Tef810x_Mod0D_RmsControlUnion_t RmsControl;
		
		HAL_GERRCODE_INIT;

		glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, &RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		RxControlUnion_u.bits_st.EnRxViaSpi = 1;//Enable Rx as we are disabling RxActiveProfile from TE.
		RxControlUnion_u.bits_st.EnLnaViaSpi = 1;//Enable LNA as we are disabling RxActiveProfile from TE.

		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		//LNA input Test
		//exception: no need to read before write, setting all fields in this reg
		RmsControl.val_u32 = 0;
		RmsControl.bits_st.LevelLoEnSpi = 1;
		RmsControl.bits_st.SelRxBistInSpi = 1; //connect ssb to LNA input

		glue_reg_WriteCheck(RX1_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, RmsControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, RmsControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, RmsControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, RmsControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_RFBIST_MixerTest()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		

		//**********This API assume that profile 3 is used only as test profile so changes doing here may not be reconfigured.*********//
		//Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t TimingControl3ProfileUnion_u;
		Nxp_Tef810x_Mod0D_RxControlUnion_t RxControlUnion_u;
		//Disable rx_active ORed with en_lna;
		//glue_reg_Read (TIMING_ENGINE_MODULE_ADDRESS, TENG_TIMING_CONTROL_3_PROFILE3_OFFSET, &TimingControl3ProfileUnion_u.val_u32, NULL);
		//TimingControl3ProfileUnion_u.bits_st.Rx1ActiveProfile0 = 0;
		//TimingControl3ProfileUnion_u.bits_st.Rx2ActiveProfile0 = 0;
		//TimingControl3ProfileUnion_u.bits_st.Rx3ActiveProfile0 = 0;
		//TimingControl3ProfileUnion_u.bits_st.Rx4ActiveProfile0 = 0;
		//glue_reg_Write (TIMING_ENGINE_MODULE_ADDRESS, TENG_TIMING_CONTROL_3_PROFILE3_OFFSET, TimingControl3ProfileUnion_u.val_u32, NULL);

		HAL_GERRCODE_INIT;

		//Disable lna and Enable Rx via spi otherwise Rx will not get power ;
		glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, &RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RxControlUnion_u.bits_st.EnRxViaSpi = 1;//Enable Rx as we are disabling RxActiveProfile from TE.
		RxControlUnion_u.bits_st.EnLnaViaSpi = 0;

		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Mixer input Mux selection
		glue_reg_WriteCheck(RX1_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000012, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000012, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000012, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS,   NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000012, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_Recover_RfBist_changes()
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		//**********This API assume that profile 3 is used only as test profile so changes doing here may not be reconfigured.*********//
		Nxp_Tef810x_Mod0D_RxControlUnion_t			RxControlUnion_u;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t	IpLevelPonEnable;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t		FunctionalResetControl;
		Nxp_Tef810x_Mod14_SsbmodControlUnion_t		SsbmodControl;
		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg_u;

		HAL_GERRCODE_INIT;
		//Mask SSB Supply Error
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SupplyErrorMaskReg_u.bits_st.SupplyLowErrorFlagSsbMod1V8Mask = 1;

		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, &RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		RxControlUnion_u.bits_st.EnRxViaSpi = 0;
		RxControlUnion_u.bits_st.EnLnaViaSpi = 0;
		RxControlUnion_u.bits_st.PonLsSpi = 0;

		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RX_CONTROL_U16, RxControlUnion_u.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Normal Test
		glue_reg_WriteCheck(RX1_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000010, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX2_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000010, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX3_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000010, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(RX4_MODULE_ADDRESS, NXP_TEF810X_MOD0D_RMS_CONTROL_U16, 0x00000010, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// cc SSBMOD in frst
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &FunctionalResetControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FunctionalResetControl.bits_st.FnResetSsbmod = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FunctionalResetControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// cc Tx_pon on
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, &IpLevelPonEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		IpLevelPonEnable.bits_st.PonSsbmod = 0;
		IpLevelPonEnable.bits_st.PonTx1 = 1;
		IpLevelPonEnable.bits_st.PonTx2 = 1;
		IpLevelPonEnable.bits_st.PonTx3 = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16, IpLevelPonEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(SSBMOD_MODULE_ADDRESS, NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16, &SsbmodControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		SsbmodControl.bits_st.PonLsSpi = 0;
		SsbmodControl.bits_st.SsbmodEn = 0;

		glue_reg_WriteCheck(SSBMOD_MODULE_ADDRESS, NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16, SsbmodControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_ISM_InjectChirp_Unlock_Vco480_error(uint32_t Error_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		bool bexpErrTrue = false;
		uint32_t vco_register = 0x00;

		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_vcoregisterprofile;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGCon;

		HAL_GERRCODE_INIT;

		switch (fitProfile)
		{
		case 0:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		}

		//Step 1:Read current ivco in the chirp vco register profile0//
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 2:Store ivco value locally//
		//subband_current = r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0;

		//Step 3:Decrease ivco value to inject chirp min error//
		r_vcoregisterprofile.bits_st.CtlVcoCoarseTuningSpiProfile0 = 0x2;

		//Step 4:Rewrite VCO reg value//
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve current profile setting
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//uint32_t currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 5:Dummy chirp with profileX// Expecting a chirp min error
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Step 6:Read chirp masked status in ISM;

		hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 7:Extract only chirp min error;
		if (Error_ID == unlock_error_chirp)
		{
			bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.UnlockErrorFlagChirpSync;
		}
		else if (vco_freq_480_error_chirp)
		{
			bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.VcoFreq480ErrorFlagChirp;
			
		}
		else
		{
			bexpErrTrue = 0;

		}

		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}

	}
	DolphinIC_rval_t hal_es3_ISM_InjectChirp_Min_DigLockStep_error(uint32_t Error_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		bool bexpErrTrue = false;
		uint32_t vco_register = 0x00;

		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_vcoregisterprofile;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGCon;

		HAL_GERRCODE_INIT;

		switch (fitProfile)
		{
		case 0:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		}

		//Step 1:Read current ivco in the chirp vco register profile0//
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 2:Store ivco value locally//
		//ivco_current = r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0;

		//Step 3:Decrease ivco value to inject chirp min error//
		r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = 0;

		//Step 4:Rewrite VCO reg value//
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve current profile setting
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//uint32_t currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 5:Dummy chirp with profile0// Expecting a chirp min error
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Step 6:Read chirp masked status in ISM;

		hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 7:Extract only chirp min error;

		bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMinErrorFlagChirp;

		if (Error_ID == level_min_error_chirp)
		{
			bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMinErrorFlagChirp;
		}
		else if (Error_ID == lock_step_error_chirp)
		{
			bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LockStepErrorFlagChirpSync;
		}
		else
		{
			bexpErrTrue = 0;

		}

		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}
	}

	DolphinIC_rval_t hal_es3_ISM_InjectChirp_Max_error(uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		bool bexpErrTrue = false;
		uint32_t vco_register = 0x00;

		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			r_vcoregisterprofile;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;
		HAL_GERRCODE_INIT;

		switch (fitProfile)
		{
		case 0:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			break;
		case 1:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			break;
		case 2:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			break;
		case 3:
			vco_register = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			break;
		}

		//Step 1:Read current ivco in the chirp vco register profile0//
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, vco_register, &r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 2:Store ivco value locally//
		//ivco_current = r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0;

		//Step 3:Increase ivco value to inject chirp max error//
		r_vcoregisterprofile.bits_st.CtlVcoIvcoFineSpiProfile0 = 0x1F;

		//Step 4:Rewrite VCO reg value//
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, vco_register, r_vcoregisterprofile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve current profile setting
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//uint32_t currChirpProfileSetting = ChirpGCon.bits_st.ChirpProfileSelect;
		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 5:Dummy chirp with profile0// Expecting a chirp min error
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//Step 6:Read chirp masked status in ISM;
		hal_es3_ISM_GetChirpErrorStatus(&ChirpErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Step 7:Extract only chirp max error;

		bexpErrTrue = ChirpErrorFlagMaskedStatus_ust.bits_st.LevelMaxErrorFlagChirp;
	
		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}
	}

	DolphinIC_rval_t hal_es3_ISM_InjectTX_Max_error(uint8_t Module_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t TXGain_profile_Reg = 0x00;
		bool bexpErrTrue = false;

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t				GTxGainProfileBits_t_ust;
		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t		r_LoInterfaceGainControlUnion_t_ust;

		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (fitProfile)
		{
		case 0:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		case 1:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
			break;
		case 2:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
			break;
		case 3:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
			break;
		}

		glue_reg_Read(Module_ID, TXGain_profile_Reg, &GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = 0x0ff;

		glue_reg_WriteCheck(Module_ID, TXGain_profile_Reg, GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel > 0x10 && r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel < 0x1B)
		{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel + 4;

		}
		else if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel < 0x10 && r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel < 0x4)
		{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel + 0xA;

		}
		else
		{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel + 0x14;

		}
		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Step 3: Do dummy trigger and error_n should low.

		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Step 4: Read Ism reg 0x06C offset [9:7]. Make sure these bits are set.

		hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		switch (Module_ID)
		{
		case 0x11:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfReliabilityLevelError;
			break;
		case 0x12:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfReliabilityLevelError;
			break;
		case 0x13:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfReliabilityLevelError;
			break;

		}

		glue_reg_Read(Module_ID, TXGain_profile_Reg, &GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = 0x01;

		glue_reg_WriteCheck(Module_ID, TXGain_profile_Reg, GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}
	}

	DolphinIC_rval_t hal_es3_ISM_InjectTX_Min_error(uint8_t Module_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t TXGain_profile_Reg = 0x00;
		bool bexpErrTrue = false;

		Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
		Nxp_Tef810x_Mod11_GTxGainProfileUnion_t				GTxGainProfileBits_t_ust;
		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t		r_LoInterfaceGainControlUnion_t_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			ChirpGCon;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//change it to using fitProfile
		ChirpGCon.bits_st.ChirpProfileSelect = fitProfile;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGCon.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (fitProfile)
		{
		case 0:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16;
			break;
		case 1:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16;
			break;
		case 2:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16;
			break;
		case 3:
			TXGain_profile_Reg = NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16;
			break;
		}

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel > 0x04 && r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel < 0xA)
		//{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = 1;

		//}
		//else if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel >= 0xA && r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel <= 0x10)
		//{
		//	r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel - 0xA;

		//}
		//else

		//{
		//	r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel - 0x19;

		//}
		glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		glue_reg_Read(Module_ID, TXGain_profile_Reg, &GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = 0x00;

		glue_reg_WriteCheck(Module_ID, TXGain_profile_Reg, GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		// Step 3: Do dummy trigger and error_n should low.

		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Step 4: Read Ism reg 0x06C offset [9:7]. Make sure these bits are set.
		hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (Module_ID)
		{
		case 0x11:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelFsError;
			break;
		case 0x12:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelFsError;
			break;
		case 0x13:
			bexpErrTrue = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelFsError;
			break;

		}

		glue_reg_Read(Module_ID, TXGain_profile_Reg, &GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		GTxGainProfileBits_t_ust.bits_st.GTxGainProfile0 = 0x01;

		glue_reg_WriteCheck(Module_ID, TXGain_profile_Reg, GTxGainProfileBits_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}

	}

	DolphinIC_rval_t hal_es3_ISM_Inject_Rx_Min_error(uint8_t Module_ID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t r_LoInterfaceGainControlUnion_t_ust;
		Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t RxErrorFlagMaskedStatus_ust;
		bool bexpErrTrue = false;

		HAL_GERRCODE_INIT;

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel != 0x00)
		{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = 0x00;
			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_GetRxErrorStatus(&RxErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			switch (Module_ID)
			{
			case 0x0D:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMinErrorFlagRx1Masked;
				break;
			case 0X0E:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMinErrorFlagRx2Masked;
				break;
			case 0X0F:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMinErrorFlagRx3Masked;
				break;
			case 0X10:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMinErrorFlagRx4Masked;
				break;

			}

			if (bexpErrTrue)
			{
				return HAL_GERRCODE;
			}
			else
			{
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

			}
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Inject_Rx_Max_error(uint8_t Module_ID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t r_LoInterfaceGainControlUnion_t_ust;
		Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t RxErrorFlagMaskedStatus_ust;
		bool bexpErrTrue = false;
		HAL_GERRCODE_INIT;

		glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		if (r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel != 0x1f)
		{
			r_LoInterfaceGainControlUnion_t_ust.bits_st.GainCodeSel = 0x1f;
			glue_reg_WriteCheck(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, r_LoInterfaceGainControlUnion_t_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_GetRxErrorStatus(&RxErrorFlagMaskedStatus_ust.val_u32);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			switch (Module_ID)
			{
			case 0x0D:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMaxErrorFlagRx1Masked;
				break;
			case 0X0E:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMaxErrorFlagRx2Masked;
				break;
			case 0X0F:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMaxErrorFlagRx3Masked;
				break;
			case 0X10:
				bexpErrTrue = RxErrorFlagMaskedStatus_ust.bits_st.LoMaxErrorFlagRx4Masked;
				break;

			}
			if (bexpErrTrue)
			{
				return HAL_GERRCODE;
			}
			else
			{
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

			}
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
		}
	}

	DolphinIC_rval_t hal_es3_ISM_Inject_MC_PllLock_PllLevel_error(uint32_t Error_ID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		bool bexpErrTrue;
		Nxp_Tef810x_Mod0C_CalibrationAacControlUnion_t r_CalibrationAacControlUnion_t_ust;
		Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, &r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		r_CalibrationAacControlUnion_t_ust.bits_st.AacManual = 1;
		glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, &r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (r_CalibrationAacControlUnion_t_ust.bits_st.AacIctrlInit <= 0x20)
		{
			r_CalibrationAacControlUnion_t_ust.bits_st.AacIctrlInit = r_CalibrationAacControlUnion_t_ust.bits_st.AacIctrlInit + 0x14;
		}


		else
		{
			r_CalibrationAacControlUnion_t_ust.bits_st.AacIctrlInit = r_CalibrationAacControlUnion_t_ust.bits_st.AacIctrlInit - 0x14;
		}

		glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		////Reconfig the Manual control to auto mode
		glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, &r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		r_CalibrationAacControlUnion_t_ust.bits_st.AacManual = 0;
		glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16, r_CalibrationAacControlUnion_t_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_GetMCLOErrorStatus(&McLoErrorFlagMaskedStatus_ust.val_u32);

		if (Error_ID == mc_pll_lock_error)
		{
			bexpErrTrue = McLoErrorFlagMaskedStatus_ust.bits_st.McPllLockErrorFlag;
			
		}
		else if (Error_ID == mc_pll_level_error)
		{
			bexpErrTrue = McLoErrorFlagMaskedStatus_ust.bits_st.McPllLevelErrorFlag;
			

		}
		else
		{
			bexpErrTrue = 0;

		}

		if (bexpErrTrue)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);

		}
	}

	DolphinIC_rval_t hal_es3_ISM_Inject_error(uint32_t Error_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		uint32_t tem_error_id = 0;
		uint8_t temp_1 = 0x0;
		uint32_t supply_error;
		uint32_t tx_error;
		uint32_t rx_error;
		uint32_t chirp_error;
		uint32_t mc_lo_error;
		uint32_t adc_error;

		HAL_GERRCODE_INIT;

		tem_error_id = (Error_ID << 4) >> 4;

		//supply_error = (tem_error_id & ISM_SUPPLY_ERROR_MASK_REG_RW_MSK) ^ ISM_SUPPLY_ERROR_MASK_REG_RW_MSK;
		//tx_error = (tem_error_id & 0x8003FFFF) ^ 0x8003FFFF;
		//rx_error = (tem_error_id & ISM_RX_ERROR_MASK_REG_RW_MSK) ^ ISM_RX_ERROR_MASK_REG_RW_MSK;
		//chirp_error = (tem_error_id & 0x800023FF) ^ ISM_CHIRP_ERROR_MASK_REG_RW_MSK;
		//mc_lo_error = (tem_error_id & ISM_MC_LO_ERROR_MASK_REG_RW_MSK) ^ ISM_MC_LO_ERROR_MASK_REG_RW_MSK;
		//adc_error = (tem_error_id & ISM_ADC_ERROR_MASK_REG_RW_MSK) ^ ISM_ADC_ERROR_MASK_REG_RW_MSK;

		supply_error = (tem_error_id & 0x87FFFFFF) ^ 0x87FFFFFF;
		tx_error     = (tem_error_id & 0x8003FFFF) ^ 0x8003FFFF;
		rx_error     = (tem_error_id & 0x800FFFFF) ^ 0x800FFFFF;
		chirp_error  = (tem_error_id & 0x800023FF) ^ 0x800023FF;
		mc_lo_error  = (tem_error_id & 0x8003110F) ^ 0x8003110F;
		adc_error    = (tem_error_id & 0x8FFFFFFF) ^ 0x8FFFFFFF;
		
		temp_1 = (temp_1 | (Error_ID >> 28));

		switch (temp_1)
		{
		case 0x01:
			hal_es3_ISM_MaskSupplyError(supply_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(0x8003FFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(0x800FFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(0x800023FF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(0x8003110F);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(0x8FFFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case 0x02:
			hal_es3_ISM_MaskSupplyError(0x87FFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(tx_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(0x800FFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(0x800023FF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(0x8003110F);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(0x8FFFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 0x03:
			hal_es3_ISM_MaskSupplyError(0x87FFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(0x8003FFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(rx_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(0x800023FF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(0x8003110F);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(0x8FFFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case 0x04:

			hal_es3_ISM_MaskSupplyError(0x87FFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(0x8003FFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(0x800FFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(chirp_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(0x8003110F);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(0x8FFFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case 0x05:

			hal_es3_ISM_MaskSupplyError(0x87FFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(0x8003FFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(0x800FFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(0x800023FF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(mc_lo_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(0x8FFFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case 0x06:

			hal_es3_ISM_MaskSupplyError(0x87FFFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskTxError(0x8003FFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskRxError(0x800FFFFF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskChirpError(0x800023FF);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskMCLOError(0x8003110F);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_MaskADCError(adc_error);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
			break;
		}


		switch (Error_ID)
		{
		case unlock_error_chirp://chirp unlock

			hal_es3_ISM_InjectChirp_Unlock_Vco480_error(Error_ID, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			break;
		case vco_freq_480_error_chirp://chip vco_480
			hal_es3_ISM_InjectChirp_Unlock_Vco480_error(Error_ID, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case level_min_error_chirp://chip min
			hal_es3_ISM_InjectChirp_Min_DigLockStep_error(Error_ID, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case lock_step_error_chirp://chip lock step

			hal_es3_ISM_InjectChirp_Min_DigLockStep_error(Error_ID, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case level_max_error_chirp://chip max

			hal_es3_ISM_InjectChirp_Max_error(fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

			//////////////Tx Errors////////////////
		case rf_max_error_tx1://tx1 max

			hal_es3_ISM_InjectTX_Max_error(TX1_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_max_error_tx2://tx2 max

			hal_es3_ISM_InjectTX_Max_error(TX2_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_max_error_tx3://tx2 max

			hal_es3_ISM_InjectTX_Max_error(TX3_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_min_error_tx1://tx1 min

			hal_es3_ISM_InjectTX_Min_error(TX1_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_min_error_tx2://tx2 min

			hal_es3_ISM_InjectTX_Min_error(TX2_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_min_error_tx3://tx3 min

			hal_es3_ISM_InjectTX_Min_error(TX3_MODULE_ADDRESS, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

			//////////////Rx Errors////////////////


		case lo_max_error_rx1://rx1 max

			hal_es3_ISM_Inject_Rx_Max_error(RX1_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_max_error_rx2://rx2 max

			hal_es3_ISM_Inject_Rx_Max_error(RX2_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_max_error_rx3://rx3 max

			hal_es3_ISM_Inject_Rx_Max_error(RX3_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_max_error_rx4://rx4 max

			hal_es3_ISM_Inject_Rx_Max_error(RX4_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case lo_min_error_rx1://rx1 min

			hal_es3_ISM_Inject_Rx_Min_error(RX1_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_min_error_rx2:////rx2 min

			hal_es3_ISM_Inject_Rx_Min_error(RX2_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case lo_min_error_rx3:////rx3 min

			hal_es3_ISM_Inject_Rx_Min_error(RX3_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_min_error_rx4:////rx4 min

			hal_es3_ISM_Inject_Rx_Min_error(RX4_MODULE_ADDRESS);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case mc_pll_lock_error:
		case mc_pll_level_error:

			hal_es3_ISM_Inject_MC_PllLock_PllLevel_error(Error_ID);


			break;


		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
			break;

		}

		return HAL_GERRCODE;

	}

	DolphinIC_rval_t hal_es3_ISM_UnMask_All_error()
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		

		uint32_t supply_error_unmask = 0x87FFFFFF ^ 0x8000;
		HAL_GERRCODE_INIT;

		hal_es3_ISM_UnMaskSupplyError(supply_error_unmask);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_UnMaskTxError(0x8003FFFF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_UnMaskRxError(0x800FFFFF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_UnMaskChirpError(0x800023FF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_UnMaskMCLOError(0x8003110F);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_UnMaskADCError(0x8FFFFFFF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;

	}

	DolphinIC_rval_t hal_es3_ISM_Recover_error_FunRst(uint32_t Error_ID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t r_FunctionalResetControlUnion_ust;
		HAL_GERRCODE_INIT;

		switch (Error_ID)
		{
		case unlock_error_chirp://chirp unlock
		case vco_freq_480_error_chirp://chip vco_480
		case level_min_error_chirp://chip min
		case lock_step_error_chirp://chip lock step
		case level_max_error_chirp://chip max

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetChirp = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetChirp = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_max_error_tx1:
		case rf_min_error_tx1:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx1 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx1 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case rf_min_error_tx2:
		case rf_max_error_tx2:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx2 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx2 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_max_error_tx3:
		case rf_min_error_tx3:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx3 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetTx3 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case lo_max_error_rx1:
		case lo_min_error_rx1:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx1 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx1 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			break;
		case lo_max_error_rx2:
		case lo_min_error_rx2:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx2 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx2 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;
		case lo_max_error_rx3:
		case lo_min_error_rx3:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx3 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx3 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			break;

			break;
		case lo_max_error_rx4:
		case lo_min_error_rx4:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx4 = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetRx4 = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case mc_pll_lock_error:
		case mc_pll_level_error:

			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetMasterClk = 0;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			r_FunctionalResetControlUnion_ust.bits_st.FnResetMasterClk = 1;

			glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, r_FunctionalResetControlUnion_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


			break;


		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
			break;


		}
		return HAL_GERRCODE;

	}
	DolphinIC_rval_t hal_es3_ISM_Recover_error(uint32_t Error_ID, uint8_t fitProfile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		bool tx_on[3] = { 1, 1, 1 };
		HAL_GERRCODE_INIT;

		switch (Error_ID)
		{
		case unlock_error_chirp://chirp unlock
		case vco_freq_480_error_chirp://chip vco_480
			//Reconfig Subband VI is executed from Test stand

		break;
		case level_min_error_chirp://chip min
		case lock_step_error_chirp://chip lock step
		case level_max_error_chirp://chip max

			//hal_es3_cafc_CalAmplitude(fitProfile);
			hal_es3_cafc_CalAmplitude_InjectRecovery(fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case rf_min_error_tx1:
		case rf_max_error_tx1:

		case rf_min_error_tx2:
		case rf_max_error_tx2:

		case rf_max_error_tx3:
		case rf_min_error_tx3:

		case lo_max_error_rx4:
		case lo_max_error_rx3:
		case lo_max_error_rx2:
		case lo_max_error_rx1:

		case lo_min_error_rx4:
		case lo_min_error_rx3:
		case lo_min_error_rx2:
		case lo_min_error_rx1:

			hal_es3_ISM_lointf_GainCalibration();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_tx_GainCalibration(tx_on, fitProfile);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			break;

		case mc_pll_lock_error:
		case mc_pll_level_error:
			hal_es3_mclk_Recalibrate();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			break;


		default:
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_FAULTINJECTIONRFAIL);
			break;


		}
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_ISM_GLDO_SNS()
	{
		Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegUnion_t Gldo1V1SnsLowCal;
		Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegUnion_t Gldo1V1SnsHighCal;
		Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegUnion_t Gldo1V8SnsLowCal;
		Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegUnion_t Gldo1V8SnsHighCal;
		Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t SupplyErrorFlagMaskedStatus;

		Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t Gldo1V1SnsLowConfig;
		Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t Gldo1V1SnsHighConfig;
		Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t Gldo1V8SnsHighConfig;
		Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t Gldo1V8SnsLowConfig;
		Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t SupplyErrorMonReg;

		uint8_t temp1;
		uint8_t temp2;
		uint8_t temp3;
		uint8_t temp4;

		uint8_t temp1_Course_thresold;
		uint8_t temp2_Course_thresold;
		uint8_t temp3_Course_thresold;
		uint8_t temp4_Course_thresold;

		
		bool v11_low_status_temp;
		bool v11_high_status_temp;
		bool v18_low_status_temp;
		bool v18_high_status_temp;

		bool error_check = false;

		HAL_GERRCODE_INIT;


		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, &SupplyErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		v11_low_status_temp  = SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V1Mon;
		v11_high_status_temp = SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V1Mon;
		v18_low_status_temp = SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V8Mon;
		v18_high_status_temp = SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V8Mon;

		SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V1Mon = 1;
		SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V1Mon = 1;
		SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V8Mon = 1;
		SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V8Mon = 1;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, SupplyErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, &Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, &Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, &Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, &Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		temp1_Course_thresold = Gldo1V1SnsLowConfig.bits_st.Sns1V1LowThreshSel;
		temp2_Course_thresold = Gldo1V1SnsHighConfig.bits_st.Sns1V1HighThreshSel;
		temp3_Course_thresold = Gldo1V8SnsLowConfig.bits_st.Sns1V8LowThreshSel;
		temp4_Course_thresold = Gldo1V8SnsHighConfig.bits_st.Sns1V8HighThreshSel;


		Gldo1V1SnsLowConfig.bits_st.Sns1V1LowThreshSel = 0;
		Gldo1V1SnsHighConfig.bits_st.Sns1V1HighThreshSel = 0;
		Gldo1V8SnsLowConfig.bits_st.Sns1V8LowThreshSel = 0;
		Gldo1V8SnsHighConfig.bits_st.Sns1V8HighThreshSel = 0;


		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16, &Gldo1V1SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16, &Gldo1V1SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16, &Gldo1V8SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16, &Gldo1V8SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		temp1 = Gldo1V1SnsLowCal.bits_st.Gldo1V1SnsLowCal;
		temp2 = Gldo1V1SnsHighCal.bits_st.Gldo1V1SnsHighCal;
		temp3 = Gldo1V8SnsLowCal.bits_st.Gldo1V8SnsLowCal;
		temp4 = Gldo1V8SnsHighCal.bits_st.Gldo1V8SnsHighCal;

		Gldo1V1SnsLowCal.bits_st.Gldo1V1SnsLowCal = 0x3f;
		Gldo1V1SnsHighCal.bits_st.Gldo1V1SnsHighCal = 0;
		Gldo1V8SnsLowCal.bits_st.Gldo1V8SnsLowCal = 0x3f;
		Gldo1V8SnsHighCal.bits_st.Gldo1V8SnsHighCal = 0;

		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16, Gldo1V1SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16, Gldo1V1SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16, Gldo1V8SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16, Gldo1V8SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_MASKED_STATUS_U16, &SupplyErrorFlagMaskedStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		error_check = SupplyErrorFlagMaskedStatus.bits_st.GlobalLdo1V1SupplyHighErrorFlagSync &
			SupplyErrorFlagMaskedStatus.bits_st.GlobalLdo1V1SupplyLowErrorFlagSync &
			SupplyErrorFlagMaskedStatus.bits_st.GlobalLdo1V8SupplyHighErrorFlagSync &
			SupplyErrorFlagMaskedStatus.bits_st.GlobalLdo1V8SupplyLowErrorFlagSync;




		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, &SupplyErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V1Mon = v11_low_status_temp;
		SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V1Mon = v11_high_status_temp;
		SupplyErrorMonReg.bits_st.SupplyLowErrorFlagGlobalLdo1V8Mon = v18_low_status_temp;
		SupplyErrorMonReg.bits_st.SupplyHighErrorFlagGlobalLdo1V8Mon = v18_high_status_temp;

		glue_reg_Write(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16, SupplyErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);




		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, &Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, &Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, &Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, &Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Gldo1V1SnsLowConfig.bits_st.Sns1V1LowThreshSel = temp1_Course_thresold;
		Gldo1V1SnsHighConfig.bits_st.Sns1V1HighThreshSel = temp2_Course_thresold;
		Gldo1V8SnsLowConfig.bits_st.Sns1V8LowThreshSel = temp3_Course_thresold;
		Gldo1V8SnsHighConfig.bits_st.Sns1V8HighThreshSel = temp4_Course_thresold;


		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16, Gldo1V1SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16, Gldo1V1SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16, Gldo1V8SnsLowConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16, Gldo1V8SnsHighConfig.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16, &Gldo1V1SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16, &Gldo1V1SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16, &Gldo1V8SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16, &Gldo1V8SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Gldo1V1SnsLowCal.bits_st.Gldo1V1SnsLowCal = temp1;
		Gldo1V1SnsHighCal.bits_st.Gldo1V1SnsHighCal = temp2;
		Gldo1V8SnsLowCal.bits_st.Gldo1V8SnsLowCal = temp3;
		Gldo1V8SnsHighCal.bits_st.Gldo1V8SnsHighCal = temp4;

		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16, Gldo1V1SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16, Gldo1V1SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16, Gldo1V8SnsLowCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(GLOBAL_LDO_MODULE_ADDRESS, NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16, Gldo1V8SnsHighCal.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		if (error_check)
		{
			return HAL_GERRCODE;
		}
		else
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_INITACT18FAIL);

		}
	}

	DolphinIC_rval_t hal_es3_ISM_MaskErrPONDisabledModule(uint32_t IP_PON_Mask)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg;
		HAL_GERRCODE_INIT;

		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX1_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{
			
			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx11V8Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx11V1Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX2_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx21V8Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx21V1Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX3_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx31V8Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx31V1Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, RX4_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx41V8Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagRx41V1Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX1_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagTx11V8Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX2_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagTx21V8Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, TX3_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagTx31V8Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
		if (hal_es3_CheckUserPONEn(IP_PON_Mask, CHIRP_AFC_MODULE_ADDRESS) == DOLPHINIC_EC_IPNOTACTIVATED)
		{

			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, &SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagChirpPll1V8Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagChirpDig1V1Mask = 1;
			SupplyErrorMaskReg.bits_st.SupplyLowErrorFlagChirpVco1V8Mask = 1;
			glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16, SupplyErrorMaskReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}
	
		return HAL_GERRCODE;

	}


#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
