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
* @file hal_es3_lvds.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief LVDS Low-Level Interface.
*
*
******************************************************************************/

#include <math.h>
#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_lvdsTx.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_lvds_Init(float initOutClkFreq)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		uint8_t master_idiv_val = 0x00;

		Nxp_Tef810x_Mod01_PdcConfigRegUnion_t PdcConfigReg_ust;
		Nxp_Tef810x_Mod01_LvdsconfigregUnion_t LVDSConfigReg;
		Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlUnion_t LvdsSerGlobalPadCtrl_ust;
		Nxp_Tef810x_Mod01_MasterIdivCtrlUnion_t MasterIdivCtrl_ust;
//		Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Union_t LVDSSerPadCtrl1;
//		Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Union_t LVDSSerPadCtrl2;
		Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Union_t LVDSSerPadCtrl3;
//		Nxp_Tef810x_Mod01_AdcdebugmodeUnion_t ADCDebugMode;
		Nxp_Tef810x_Mod01_LvdsTxControlUnion_t LVDSTxCtrl;

		HAL_GERRCODE_INIT;
		
		// Assert functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//put LVDS driver to normal operation state
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_SER_GLOBAL_PAD_CTRL_U16, &LvdsSerGlobalPadCtrl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//using global pad control here, no need to set individual pad control in LVDS_SER_PAD_CTRL1 and LVDS_SER_PAD_CTRL2
		LvdsSerGlobalPadCtrl_ust.bits_st.LvdsSerGlobalPadEpwr = 0x01; //1: enabled, 0:disabled
		LvdsSerGlobalPadCtrl_ust.bits_st.LvdsSerGlobalMfioPadEn = 0x0; //0: enabled, 1: disabled

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_SER_GLOBAL_PAD_CTRL_U16, LvdsSerGlobalPadCtrl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Rd-Mod-Wr
		//This read is a must! Because lvds_set_trim_r_n is from OTP, not from user input nor fixed setting.
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL3_U16, &LVDSSerPadCtrl3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Note active levels are different in different bits
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEn = 0;//0: enabled
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEnzi = 1; //1: LVDS receiver disabled
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEpun = 1; //weak pullup disabled
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEpd = 0; //weak pulldown disabled
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEhs0 = 0;
		LVDSSerPadCtrl3.bits_st.LvdsCifDatavalidMfioEhs1 = 0;
		LVDSSerPadCtrl3.bits_st.LvdsVrefEprbias = 1;
		//LVDSSerPadCtrl3.bits_st.LvdsSetTrimRN = DO NOT SET HERE (from OTP)
		LVDSSerPadCtrl3.bits_st.LvdsCntrl = 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL3_U16, LVDSSerPadCtrl3.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Mod-Wr
		LVDSConfigReg.val_u32 = 0;
		LVDSConfigReg.bits_st.FrameClkGating = 0;
		LVDSConfigReg.bits_st.DataValidDelayCtrl = 0;
		LVDSConfigReg.bits_st.PacketEndianness = 0;
		LVDSConfigReg.bits_st.Lvdslinecntreg = 0;
		LVDSConfigReg.bits_st.Packeten = 0; //0: no packet header
		LVDSConfigReg.bits_st.LvdsCrcControl = 1; //1: enable CRC for LVDS

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDSCONFIGREG_U16, LVDSConfigReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		master_idiv_val = (uint8_t)(roundf((480e6 / (initOutClkFreq * 2)) - 1));
		DbgInfo("master_idiv_val = 0x%2x \n", master_idiv_val);

		//No need to read, all fields are covered below
		//Mod-Wr
		MasterIdivCtrl_ust.bits_st.MasterIdivBlkCnt = 0x3F;
		MasterIdivCtrl_ust.bits_st.MasterIdivSelRegLut = 1; //1: select idiv value from the below field
		MasterIdivCtrl_ust.bits_st.MasterIdivValue = master_idiv_val;
		MasterIdivCtrl_ust.bits_st.MasterIdivRst = 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_MASTER_IDIV_CTRL_U16, MasterIdivCtrl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rd-Mod-Wr
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_PDC_CONFIG_REG_U16, &PdcConfigReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		PdcConfigReg_ust.bits_st.MakeOutputUnsigned = 1; //1: unsigned

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_PDC_CONFIG_REG_U16, PdcConfigReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_lvds_CfgMode(false, true, true, true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Release functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//No need to read, all fields are covered below
		//Mod-Wr
		//enable transmission
		LVDSTxCtrl.val_u32 = 0;
		LVDSTxCtrl.bits_st.Serialisertxen = 0xF;
		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, LVDSTxCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_lvds_CfgMode(bool SyncToPosEdgeBitClk, bool SyncToNegEdgeFrameClk, bool msbFirst, bool PDCSyncEnable)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
//		uint32_t regval = 0x00;
		
		HAL_GERRCODE_INIT;
		Nxp_Tef810x_Mod01_TransmitphasecontrolUnion_t Transmitphasecontrol_ust;
		Nxp_Tef810x_Mod01_MsblsbcontrolUnion_t Msblsbcontrol_ust;
		Nxp_Tef810x_Mod01_AtbSetTrimUnion_t ATBSetTrim;
		Nxp_Tef810x_Mod01_LvdsTxControlUnion_t LVDSTXControl;

		//first stop transmission
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, &LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LVDSTXControl.bits_st.Serialisertxen = 0;
		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Assert functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rd-Mod-Wr
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_TRANSMITPHASECONTROL_U16, &Transmitphasecontrol_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Transmitphasecontrol_ust.bits_st.BitClkPhase = SyncToPosEdgeBitClk ? 1 : 0;
		Transmitphasecontrol_ust.bits_st.FrameClkPhase = SyncToNegEdgeFrameClk ? 1 : 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_TRANSMITPHASECONTROL_U16, Transmitphasecontrol_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rd-Mod-Wr
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_MSBLSBCONTROL_U16, &Msblsbcontrol_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		Msblsbcontrol_ust.bits_st.MsbFirst = msbFirst ? 1 : 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_MSBLSBCONTROL_U16, Msblsbcontrol_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Rd-Mod-Wr
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_ATB_SET_TRIM_U16, &ATBSetTrim.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ATBSetTrim.bits_st.AtbSetTrimRN = PDCSyncEnable ? 1 : 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_ATB_SET_TRIM_U16, ATBSetTrim.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Release functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//in the end restore transmission
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, &LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LVDSTXControl.bits_st.Serialisertxen = 0xF;
		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_lvds_CfgTestMode(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t ADCTestDataMux;
		Nxp_Tef810x_Mod01_LvdsTxControlUnion_t LVDSTXControl;

		HAL_GERRCODE_INIT;

		//first stop transmission
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, &LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LVDSTXControl.bits_st.Serialisertxen = 0;
		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//then assert func reset
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//No need to read, all fields are covered below
		//Mod-Wr
		ADCTestDataMux.val_u32 = 0;
		ADCTestDataMux.bits_st.LvdsTestmodeSkipPdc = 1; //1: test data is inserted at the output side of the PDC
		ADCTestDataMux.bits_st.LvdsTestmodeDataSel = 0; //0: test data from register field.
		ADCTestDataMux.bits_st.LvdsTestmodeEn = 1; //1: test mode enabled
		ADCTestDataMux.bits_st.LvdsTestmodeTestData = 0x214; // test pattern.

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_ADCTESTDATAMUX_U16, ADCTestDataMux.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//then restore transmission
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, &LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LVDSTXControl.bits_st.Serialisertxen = 0x0F;
		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16, LVDSTXControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_lvds_CfgWindowActSel(bool SetToActive)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		Nxp_Tef810x_Mod01_WindowactiveselUnion_t Windowactivesel_ust;

		HAL_GERRCODE_INIT;

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Rd-Mod-Wr
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, &Windowactivesel_ust.val_u32, NULL);	
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Windowactivesel_ust.bits_st.WindowActiveSel = 1;
		Windowactivesel_ust.bits_st.WindowActiveRegControl = SetToActive ? 1 : 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, Windowactivesel_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_LVDS);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_lvds_getMCLKOutFrequency(float * p_freqcountrval)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod01_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;
		Nxp_Tef810x_Mod01_FreqCounterStartUnion_t FreqCounterStart;
		Nxp_Tef810x_Mod01_RefCntrInitUnion_t RefCntrInit;
		*p_freqcountrval = 0.0f;

		HAL_GERRCODE_INIT;
		
		//No need to read, all fields are covered below
		//Mod-Wr
		//change frequency counter trigger to SPI write to freq_start.
		FreqCounterStart.val_u32 = 0;
		FreqCounterStart.bits_st.FreqCounterTriggerSel = 0;//0: trigger from writing to this register
		FreqCounterStart.bits_st.FreqCounterDeviation = 0;
		FreqCounterStart.bits_st.FreqStart = 0;

		glue_reg_WriteCheck(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//No need to read, all fields are not changed from above value except the following fileds
		//Mod-Wr
		FreqCounterStart.bits_st.FreqStart = 1; //1: trigger one measurement.
		glue_reg_Write(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//wait for counter.
		glue_Tic();
		do
		{
			glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			//timeout
			if (glue_Toc() >= LVDS_FREQ_CNT_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("LVDS frequency counting failed: it didn't finish within %.2f ms...\n", LVDS_FREQ_CNT_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_MCLK_FREQ_CNT_TIMEOUT);
			}
		} while (FreqCounterReadValue_ust.bits_st.DoneFlag == 0);

		//read ref count
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_REF_CNTR_INIT_U16, &RefCntrInit.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//read out the frequency counter.
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//TODO: add REF_CNTR_INIT.ref_count_value into consideration for frequency calculation 
		*p_freqcountrval = FreqCounterReadValue_ust.bits_st.FreqCountValue/(RefCntrInit.bits_st.RefCountValue/40.0f);

		return HAL_GERRCODE;
	}
	//The following function is used to disable the clock and  data line toggling while we chirp during LO/TX calibation.
	DolphinIC_rval_t hal_ES3_LVDS_Datatoggle_Disable(void)
	{
		Nxp_Tef810x_Mod01_WindowactiveselUnion_t WindowactiveselUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, &WindowactiveselUnion_t.val_u32, NULL);
		WindowactiveselUnion_t.bits_st.WindowActiveRegControl = 1;
		WindowactiveselUnion_t.bits_st.WindowActiveSel= 0;

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, WindowactiveselUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
		
	}
	//The following function is used to Enable the clock and  data line toggling after the chirp trigger for LO/TX calibation.
	DolphinIC_rval_t hal_ES3_LVDS_Datatoggle_Enable(void)
	{
		Nxp_Tef810x_Mod01_WindowactiveselUnion_t WindowactiveselUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, &WindowactiveselUnion_t.val_u32, NULL);
		WindowactiveselUnion_t.bits_st.WindowActiveRegControl = 0;
		WindowactiveselUnion_t.bits_st.WindowActiveSel = 0;

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(LVDS_TX_MODULE_ADDRESS, NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16, WindowactiveselUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;

	}


#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
