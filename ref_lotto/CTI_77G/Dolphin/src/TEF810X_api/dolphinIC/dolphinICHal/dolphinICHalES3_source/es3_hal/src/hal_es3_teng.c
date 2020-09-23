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
* @file hal_es3_teng.c
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

#include <math.h>
#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>

#ifdef READY_INT_CFG
#include "rsys_fsv.h" //This include has the extern declaration for the variable used for ready int
#endif

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_teng_UpdateProfChirpPeriod(uint8_t profID, uint8_t txActiveNum, uint8_t rxSwNum, float tChirp)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

//		uint32_t reg_val = 0x00;
		uint32_t TIMING_CONTROL_3 = 0x00;
		uint32_t tChirpInt = 0x00;
		Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t TETimingCtrl3Profile;

		HAL_GERRCODE_INIT;

		switch (profID)
		{
		case 1:
			TIMING_CONTROL_3 = NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE1_U16;
			break;
		case 2:
			TIMING_CONTROL_3 = NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE2_U16;
			break;
		case 3:
			TIMING_CONTROL_3 = NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE3_U16;
			break;
		default:
		case 0:
			TIMING_CONTROL_3 = NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE0_U16;
			break;
		}

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_3, &TETimingCtrl3Profile.val_u32, NULL);

		//convert us to 25ns base 
		tChirpInt = (uint32_t)(roundf(tChirp * 1000.0 / 25.0));

		DbgInfo("chirp time in double is:%f, chirp time in uint32 is:%d\n", tChirp, tChirpInt);

		TETimingCtrl3Profile.bits_st.Rx1ActiveProfile0 = rxSwNum;
		TETimingCtrl3Profile.bits_st.Rx2ActiveProfile0 = rxSwNum >> 1;
		TETimingCtrl3Profile.bits_st.Rx3ActiveProfile0 = rxSwNum >> 2;
		TETimingCtrl3Profile.bits_st.Rx4ActiveProfile0 = rxSwNum >> 3;
		TETimingCtrl3Profile.bits_st.Tx1ActiveProfile0 = txActiveNum;
		TETimingCtrl3Profile.bits_st.Tx2ActiveProfile0 = txActiveNum >> 1;
		TETimingCtrl3Profile.bits_st.Tx3ActiveProfile0 = txActiveNum >> 2;
		TETimingCtrl3Profile.bits_st.ChirpIntervalTimerProfile0 = tChirpInt;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_3, TETimingCtrl3Profile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_UpdateProfTiming(uint8_t profID, float tDwell, bool txBPSFastSWCtrlPointSettle, float txBPSFastSWTime, uint8_t BPSCtrlBits, uint8_t txControlBits)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

//		uint32_t reg_val = 0x00;
		uint32_t TIMING_CONTROL_1 = 0x00;
		uint32_t tDwellInt = 0x00;
		uint32_t txBPSfastSWTimeInt = 0x00;
		Nxp_Tef810x_Mod04_TimingControl1ProfileUnion_t TETimingCtrl1Profile;

		HAL_GERRCODE_INIT;

		switch (profID)
		{
		case 1:
			TIMING_CONTROL_1 = NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE1_U16;
			break;
		case 2:
			TIMING_CONTROL_1 = NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE2_U16;
			break;
		case 3:
			TIMING_CONTROL_1 = NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE3_U16;
			break;
		default:
		case 0:
			TIMING_CONTROL_1 = NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE0_U16;
			break;
		}

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_1, &TETimingCtrl1Profile.val_u32, NULL);
		//convert us to 25ns base 
		tDwellInt = (uint32_t)(roundf(tDwell * 1000 / 25));
		txBPSfastSWTimeInt = (uint32_t)(roundf(txBPSFastSWTime * 1000 / 25));

		TETimingCtrl1Profile.bits_st.TxBpsControlAndTxEnTimeProfile0 = txBPSFastSWCtrlPointSettle;
		TETimingCtrl1Profile.bits_st.Tx1BinaryPhaseControlProfile0 = BPSCtrlBits;
		TETimingCtrl1Profile.bits_st.Tx2BinaryPhaseControlProfile0 = BPSCtrlBits >> 1;
		TETimingCtrl1Profile.bits_st.Tx3BinaryPhaseControlProfile0 = BPSCtrlBits >> 2;

		TETimingCtrl1Profile.bits_st.Tx1TransmissionEnableProfile0 = txControlBits;
		TETimingCtrl1Profile.bits_st.Tx2TransmissionEnableProfile0 = txControlBits >> 1;
		TETimingCtrl1Profile.bits_st.Tx3TransmissionEnableProfile0 = txControlBits >> 2;
		TETimingCtrl1Profile.bits_st.TxBpsAndTransmissionEnTimeProfile0 = txBPSfastSWTimeInt;
		TETimingCtrl1Profile.bits_st.DwellTimeProfile0 = tDwellInt;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_1, TETimingCtrl1Profile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_UpdateProfADC(uint8_t profID, float tSettle, uint32_t numSample, uint8_t PDCDecimation, bool PDC_bw)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint8_t DecimationSetting = 0;
		uint32_t TIMING_CONTROL_2 = 0x00;
		uint32_t tSettleInt = 0x00;
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_TimingControl2ProfileUnion_t TETimingCtrl2Profile;

		HAL_GERRCODE_INIT;

		switch (profID)
		{
		case 1:
			TIMING_CONTROL_2 = NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE1_U16;
			break;
		case 2:
			TIMING_CONTROL_2 = NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE2_U16;
			break;
		case 3:
			TIMING_CONTROL_2 = NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE3_U16;
			break;
		default:
		case 0:
			TIMING_CONTROL_2 = NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE0_U16;
			break;
		}

		//convert decimation factor to decimation settings in register 
		switch (PDCDecimation)
		{
		case 2:
			DecimationSetting = 1;
			break;
		case 4:
			DecimationSetting = 2;
			break;
		case 8:
			DecimationSetting = 3;
			break;
		case 16:
			DecimationSetting = 4;
			break;
		default:
			DecimationSetting = 0;
			break;
		}

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_2, &TETimingCtrl2Profile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25ns base 
		tSettleInt = (uint32_t)(roundf(tSettle * 1000 / 25));

		TETimingCtrl2Profile.bits_st.SettleTimeProfile0 = tSettleInt;
		//ES2-Variability :: Field name changed from pdc_output_unsigned_profile* to pdc_bw_sel_profile* based on RAD743
		/**
		"This bit is used to select the bandwidth of the decimation filter in the serialiser IP.
		0:   Narrow bandwidth 1:   Large bandwidth"
		*/
		TETimingCtrl2Profile.bits_st.PdcBwSelProfile0 = PDC_bw ? 1:0;
		TETimingCtrl2Profile.bits_st.AdcSamplingFreqProfile0 = DecimationSetting;
		TETimingCtrl2Profile.bits_st.NumberOfAdcSampleProfile0 = numSample*PDCDecimation;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, TIMING_CONTROL_2, TETimingCtrl2Profile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgNumChirpSeq(uint8_t numSeq, uint16_t numChirp)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t	TEChirpSeqCtrl;
		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16, &TEChirpSeqCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TEChirpSeqCtrl.bits_st.NoOfChirpInASequence = numChirp;
		TEChirpSeqCtrl.bits_st.NoOfSequence = numSeq;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16, TEChirpSeqCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgSeqInterval(float tSeqInterval)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t tSeqIntervalInt = 0x00;
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlUnion_t	TEChirpSeqIntvlCtrl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_INTERVAL_CONTROL_U16, &TEChirpSeqIntvlCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25n base 
		tSeqIntervalInt = (uint32_t)(roundf(tSeqInterval * 1000 / 25));

		TEChirpSeqIntvlCtrl.bits_st.ChirpSequenceInterval = tSeqIntervalInt;
		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_SEQUENCE_INTERVAL_CONTROL_U16, TEChirpSeqIntvlCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgChirpProfile(uint8_t profSelect, uint32_t profStayCount, bool profReset)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpGlobalControl_ust.bits_st.ChirpProfileSelect = profSelect;
		ChirpGlobalControl_ust.bits_st.EnableProfileReset = profReset ;
		ChirpGlobalControl_ust.bits_st.ProfileStayCountVal = profStayCount;

		//active_profile bit behavior depends on enable_profile_reset, so ignore this WriteCheck, do write only.
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_StartChirp(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;

//		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t FunctionalResetControl_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;
		Nxp_Tef810x_Mod06_CpRegisterUnion_t CpRegister;

		HAL_GERRCODE_INIT;

#ifdef CASCADE_VAL_BOARD
	uint8_t currentSpi = CURRENT_DEVICE;
	if((currentSpi != 0) && (syncCapture == 1))
			rsys_dio_SPI_SelectTargetDevice(0);	//Not very safe. Set to master
	CHIRP_COUNTER = -1;
#endif //CASCADE_VAL_BOARD

#ifdef READY_INT_CFG
		Nxp_Tef810x_Mod00_IntClrUnion_t IntClr;
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_INT_CLR_U16, &IntClr.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		IntClr.bits_st.EndOfDataTnfrIntClr = 1;
		IntClr.bits_st.EndOfDataAcqIntClr = 1;		//Just for validation, we may change from one to another
		glue_reg_Write(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_INT_CLR_U16, IntClr.val_u32, NULL);
#endif

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//first write chirp enable.
		ChirpGlobalControl_ust.bits_st.ChirpEnable = 1;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//then start a chirp sequence 
		ChirpGlobalControl_ust.bits_st.ChirpStart = 1;
		
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, &CpRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		CpRegister.bits_st.CtlCpReplicaBiasEnSpi = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CpRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

#ifdef DOLPHIN_CFG_HOST_S32R274		//FPGA is slow and does not need this extra delay
			glue_Sleep(CP_REPLICA_DELAY_MS - SPI_WR_MS); //Leave CP replica current disabled for the first 20us after chirp start. 
#endif

		CpRegister.bits_st.CtlCpReplicaBiasEnSpi = 1;
		glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CpRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

#ifdef CASCADE_VAL_BOARD
	if((currentSpi != 0) && (syncCapture == 1))
		rsys_dio_SPI_SelectTargetDevice(currentSpi);	//Not very safe. Return to whatever previous UUT
#endif //CASCADE_VAL_BOARD

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgTJumpBack(float tJumpback)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t tJumpbackInt = 0x00;
		Nxp_Tef810x_Mod04_JumpbackPeriodControlUnion_t	TEJumpBckPeriod;
		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_JUMPBACK_PERIOD_CONTROL_U16, &TEJumpBckPeriod.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//converting from us to 25ns base 
		tJumpbackInt = (uint32_t)(roundf(tJumpback *1000 / 25));
		TEJumpBckPeriod.bits_st.JumpBackTime = tJumpbackInt;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_JUMPBACK_PERIOD_CONTROL_U16, TEJumpBckPeriod.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgDCPowOnDelay(float TEDelay, float ISMDealy)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		uint32_t TEDelayInt = 0x00;
		uint32_t ISMDelayInt = 0x00;
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t TEDcPwrOnDlyCtrl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16, &TEDcPwrOnDlyCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25ns base 
		TEDelayInt = (uint32_t)(roundf(TEDelay * 1000 / 25));
		ISMDelayInt = (uint32_t)(roundf(ISMDealy * 1000 / 25));

		TEDcPwrOnDlyCtrl.bits_st.DcPoweronDelay = TEDelayInt;
		TEDcPwrOnDlyCtrl.bits_st.SafetyMonitorDelay = ISMDelayInt;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16, TEDcPwrOnDlyCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgRXPowOnDelay(float rxDelay)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t rxdelay_int = 0x00;
		Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlUnion_t	TERxDcPwrOnGrpCtrl;
		HAL_GERRCODE_INIT;
		
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_RX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16, &TERxDcPwrOnGrpCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25ns base 
		rxdelay_int = (uint32_t)(roundf(rxDelay *1000 / 25));

		TERxDcPwrOnGrpCtrl.bits_st.RxGroupDelayFromChirpStart = rxdelay_int;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_RX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16, TERxDcPwrOnGrpCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgTXPowOnDelay(float txDelay)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint32_t txdelay_int = 0x00;

		Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlUnion_t TETxDcPwrOnGrpDlyCtrl;
		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16, &TETxDcPwrOnGrpDlyCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25ns base
		txdelay_int = (uint32_t)(roundf(txDelay *1000 / 25));

		TETxDcPwrOnGrpDlyCtrl.bits_st.TxGroupDelayFromChirpStart = txdelay_int;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16, TETxDcPwrOnGrpDlyCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgChirpFastSwitchCtrl(bool enFastSW, float fastResetDuration)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod04_ChirpDynamicPowerControlUnion_t chirpDynPowerControl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_DYNAMIC_POWER_CONTROL_U16, &chirpDynPowerControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//convert us to 25ns base 
		chirpDynPowerControl.bits_st.ChirpFastSwitchDelay = (uint16_t)(roundf(fastResetDuration * 1000 / 25));
		chirpDynPowerControl.bits_st.ChirpFastSwitchEnable = enFastSW;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_DYNAMIC_POWER_CONTROL_U16, chirpDynPowerControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_teng_CfgChirpTriggerMode(uint8_t ReadyIntMode, uint8_t CSI2FrameMode, bool ChirpPowerMode, bool ChirpStartToggleOnChirpLevel, bool SyncExtTrig, bool UseExtTrigger)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t	TEChirpTriggerModeCtrl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16, &TEChirpTriggerModeCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TEChirpTriggerModeCtrl.bits_st.ReadyIntModeSel = ReadyIntMode;
		TEChirpTriggerModeCtrl.bits_st.Csi2FrameModeSel = CSI2FrameMode;
		TEChirpTriggerModeCtrl.bits_st.ChirpPowerMode = ChirpPowerMode;
		TEChirpTriggerModeCtrl.bits_st.SelModeForChirpStartOut = ChirpStartToggleOnChirpLevel;
		TEChirpTriggerModeCtrl.bits_st.ExtTrigType = SyncExtTrig;
		TEChirpTriggerModeCtrl.bits_st.ChirpTriggerMode = UseExtTrigger;

		//write settings to the register.
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16, TEChirpTriggerModeCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//TODO:
		//need to also configure chirp_start as input in the CC, not implemented for now.
		return HAL_GERRCODE;
	}

#ifdef READY_INT_CFG
	DolphinIC_rval_t __attribute__((optimize("O0"))) hal_es3_teng_WaitForReady(void)
	{
		HAL_GERRCODE_INIT;
		while((INTERRUPT_STATUS != 1) && (INTERRUPT_STATUS != 3)){}	//wait for ready int or timeout (1second)
		if(INTERRUPT_STATUS == 1)HAL_GERRCODE = DOLPHINIC_NOERROR;
		else HAL_GERRCODE = DOLPHINIC_EC_CALLTIMEOUT;
		INTERRUPT_STATUS = 0;
		glue_usecSleep(2); //This is added in case of using end of acquisition interrupt instead of end of transfer
		return HAL_GERRCODE;
	}
#else
	DolphinIC_rval_t hal_es3_teng_WaitForReady(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t chirp_global_ctrl;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;

		HAL_GERRCODE_INIT;
		
		do
		{
			glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_Sleep(1);

		} while ((ChirpGlobalControl_ust.bits_st.ChirpStart) == 0x01);
		return HAL_GERRCODE;
	}
#endif

	DolphinIC_rval_t hal_es3_teng_LoadProfile(uint8_t profID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;

		HAL_GERRCODE_INIT;

		//Use chirp_enable as the trigger of loading profiles. 0-1-0 for loading
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32,NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpGlobalControl_ust.bits_st.ChirpProfileSelect = profID;
		ChirpGlobalControl_ust.bits_st.ChirpEnable = 0;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32,NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpGlobalControl_ust.bits_st.ChirpEnable = 1;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpGlobalControl_ust.bits_st.ChirpEnable = 0;

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	
		return HAL_GERRCODE;

	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
