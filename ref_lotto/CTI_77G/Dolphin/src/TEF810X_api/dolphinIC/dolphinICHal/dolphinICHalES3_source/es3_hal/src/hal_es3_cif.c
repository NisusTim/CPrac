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
* @file hal_es3_cif.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
*
******************************************************************************/

#include <math.h>
#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_Cif.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_cif_Init(float initOutClkFreq, uint32_t mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval = 0x00;
		uint8_t master_idiv_val = 0x00;
		Nxp_Tef810x_Mod03_CifSelSackRegUnion_t			CIFSelSack;
		Nxp_Tef810x_Mod03_CifGlobalMfioCtrlUnion_t		CIFGlblMfioCtrl;
		Nxp_Tef810x_Mod03_CifconfigregUnion_t			CIFConfg;
		Nxp_Tef810x_Mod03_MasterIdivCtrlUnion_t			CIFMasterIdivCtrl;
//		Nxp_Tef810x_Mod03_CifMfioCtrl1Union_t		CIFMfioCtrl1;
//		Nxp_Tef810x_Mod03_CifMfioCtrl2Union_t		CIFMfioCtrl2;
//		Nxp_Tef810x_Mod03_CifMfioCtrl3Union_t		CIFMfioCtrl3;
//		Nxp_Tef810x_Mod03_CifMfioCtrl4Union_t		CIFMfioCtrl4;
//		Nxp_Tef810x_Mod03_CifMfioCtrl5Union_t		CIFMfioCtrl5;
//		Nxp_Tef810x_Mod03_CifMfioCtrl6Union_t		CIFMfioCtrl6;
//		Nxp_Tef810x_Mod03_CifMfioCtrl7Union_t		CIFMfioCtrl7;
		Nxp_Tef810x_Mod03_PdcConfigRegUnion_t	CIFPdcConfg;
		Nxp_Tef810x_Mod03_CifTxnCtrlUnion_t		CIFTxnCtrl;
			
		HAL_GERRCODE_INIT;


		// Assert functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (mode == 3)
		{
			//select MFIO mode for CIF pads.
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_SEL_SACK_REG_U16, &CIFSelSack.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CIFSelSack.bits_st.CifSelSack = 0x3FFF;	//UTB 0x3FF

			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_SEL_SACK_REG_U16, CIFSelSack.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			//Enable all MFIO pads.
			//glue_reg_WriteCheck(CIF_MODULE_ADDRESS, CIF_CIF_GLOBAL_MFIO_CTRL_OFFSET, 0x00, NULL);
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_GLOBAL_MFIO_CTRL_U16, &CIFGlblMfioCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CIFGlblMfioCtrl.bits_st.CifGlobalMfioEn = 0x0;	//UTB 0

			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_GLOBAL_MFIO_CTRL_U16, CIFGlblMfioCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			//doesn't matter when not using headers.
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFCONFIGREG_U16, &CIFConfg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//glue_reg_WriteCheck(CIF_MODULE_ADDRESS, CIF_CIFLINECNTREG_OFFSET, 0x08,NULL);

			//LSB first, 1 data mode: (1 sample of ADC1,1 sample of ADC2,1 sample of ADC3,1 sample of ADC4,1 sample of ADC1 so on)
			//UTB CIFConfg.bits_st.PacketEndianness = 1;
			//UTB CIFConfg.bits_st.CifCrcControl = 1;
			CIFConfg.bits_st.ClockDataRelation = 1;

			
			//glue_reg_WriteCheck(CIF_MODULE_ADDRESS, CIF_CIFCONFIGREG_OFFSET, regval, NULL);
			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFCONFIGREG_U16, CIFConfg.val_u32, NULL);
			
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//force cif clock to 40MHz (decimation by 4 setting, 10MHz eff sampling rate)
			master_idiv_val = (uint8_t)(roundf((480e6 / initOutClkFreq) - 1));

			DbgInfo("master_idiv_val = 0x%2x \n", master_idiv_val);

			//regval = 0x3F10B0;

			//regval &= ~(CIF_MASTER_IDIV_CTRL_MASTER_IDIV_VALUE_MSK);
			//regval |= (master_idiv_val << CIF_MASTER_IDIV_CTRL_MASTER_IDIV_VALUE_POS);
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_MASTER_IDIV_CTRL_U16, &CIFMasterIdivCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CIFMasterIdivCtrl.bits_st.MasterIdivRst = 0;
			CIFMasterIdivCtrl.bits_st.MasterIdivValue = master_idiv_val;
			CIFMasterIdivCtrl.bits_st.MasterIdivSelRegLut = 1;
			CIFMasterIdivCtrl.bits_st.MasterIdivBlkCnt = 0x3F;

			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_MASTER_IDIV_CTRL_U16, CIFMasterIdivCtrl.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_PDC_CONFIG_REG_U16, &CIFPdcConfg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			CIFPdcConfg.bits_st.MakeOutputUnsigned = 1;
			CIFPdcConfg.bits_st.MaskInputWWa = 0;
			CIFPdcConfg.bits_st.WaDelayDecimationMode1 = 7;
			CIFPdcConfg.bits_st.WaDelayDecimationMode2 = 0xA;
			CIFPdcConfg.bits_st.WaDelayDecimationMode3 = 0x9;
			CIFPdcConfg.bits_st.WaDelayDecimationMode4 = 0xA;

			glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_PDC_CONFIG_REG_U16, CIFPdcConfg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		}

		else
		{
			//VGIO is no longer a valid option for TEF810x.
		}

		
		//Enable transmission.
		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_TXN_CTRL_U16, &CIFTxnCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CIFTxnCtrl.bits_st.CifTxnEn = 1;

		glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIF_TXN_CTRL_U16, CIFTxnCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Release functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//hal_es3_cif_Config(true, false, true);
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cif_CfgTestMode(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval = 0x00;
		Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t		CIFTstModeCtrl;
		HAL_GERRCODE_INIT;

		

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16, &CIFTstModeCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CIFTstModeCtrl.bits_st.CifTestmodeTestData = 0x214;
		CIFTstModeCtrl.bits_st.CifTestmodeEn = 1;
		CIFTstModeCtrl.bits_st.CifTestmodeDataSel = 0;
		CIFTstModeCtrl.bits_st.CifTestmodeSkipPdc = 1;

		glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16, CIFTstModeCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cif_Config(bool PacketHeaderEnable, bool CRCEnable, bool NegEdgeEnable, bool PDCSync)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval[10] = { 0xBABAFAFA };
		HAL_GERRCODE_INIT;
		Nxp_Tef810x_Mod03_CifconfigregUnion_t Cifconfigreg_ust;
		

		DbgInfo("%d, %d, %d \n", PacketHeaderEnable, CRCEnable, NegEdgeEnable);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFCONFIGREG_U16, &Cifconfigreg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//regval[0x00] &= ~(CIF_CIFCONFIGREG_PACKET_FORMAT_ENABLE_MSK | CIF_CIFCONFIGREG_CIF_CRC_CONTROL_MSK | CIF_CIFCONFIGREG_CLOCK_DATA_RELATION_MSK);

		if (PacketHeaderEnable == true)
		{
			//regval[0x00] |= ((uint32_t)PacketHeaderEnable << CIF_CIFCONFIGREG_PACKET_FORMAT_ENABLE_POS);
			Cifconfigreg_ust.bits_st.PacketFormatEnable = PacketHeaderEnable;
		}

		if (CRCEnable == true)
		{
			//regval[0x00] |= ((uint32_t)CRCEnable << CIF_CIFCONFIGREG_CIF_CRC_CONTROL_POS);
			Cifconfigreg_ust.bits_st.CifCrcControl = CRCEnable;
		}

		if (NegEdgeEnable == true)
		{
			//regval[0x00] |= ((uint32_t)NegEdgeEnable << CIF_CIFCONFIGREG_CLOCK_DATA_RELATION_POS);
			Cifconfigreg_ust.bits_st.ClockDataRelation = NegEdgeEnable;
		}

		glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_CIFCONFIGREG_U16, Cifconfigreg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CIF);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}


	DolphinIC_rval_t hal_es3_cif_getMCLKOutFrequency(float * p_freqcountrval)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod03_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;
		Nxp_Tef810x_Mod03_RefCntrInitUnion_t RefCntrInit_ust;
		Nxp_Tef810x_Mod03_FreqCounterStartUnion_t	CIFFreqCntrStart;
		
		HAL_GERRCODE_INIT;

		*p_freqcountrval = 0.0f;

		//change frequency counter trigger to SPI write to freq_start.
		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_FREQ_COUNTER_START_U16, &CIFFreqCntrStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CIFFreqCntrStart.bits_st.FreqCounterDeviation = 0;
		CIFFreqCntrStart.bits_st.FreqCounterTriggerSel = 0;
		CIFFreqCntrStart.bits_st.FreqStart = 0;

		glue_reg_WriteCheck(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_FREQ_COUNTER_START_U16, CIFFreqCntrStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		CIFFreqCntrStart.bits_st.FreqStart = 1;
		//trigger one counter measurement
		glue_reg_Write(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_FREQ_COUNTER_START_U16, CIFFreqCntrStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//wait for counter.
		glue_Tic();
		do
		{
//			reg_val = 0;
			glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//timeout
			if (glue_Toc() >= CIF_FREQ_CNT_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("CSI2 frequency counting failed: it didn't finish within %.2f ms...\n", CIF_FREQ_CNT_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_MCLK_FREQ_CNT_TIMEOUT);
			}
		} while (FreqCounterReadValue_ust.bits_st.DoneFlag == 0);

		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_REF_CNTR_INIT_U16, &RefCntrInit_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DbgInfo("RefCNT Init(0x%x) \n", RefCntrInit_ust);

		//read out the frequency counter.
		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//FreqCounterReadValue_ust.val_u32 = FreqCounterReadValue_ust.val_u32 & CIF_FREQ_COUNTER_READ_VALUE_FREQ_COUNT_VALUE_MSK;
		//Use the refcnt to scale read result to correct frequency unit,do not assume fixed refcnt.
		*p_freqcountrval = FreqCounterReadValue_ust.bits_st.FreqCountValue/(RefCntrInit_ust.bits_st.RefCountValue/40.0f);

		DbgInfo("CIF FCNT R-Out(0x%x) \n", *p_freqcountrval);

		

		return HAL_GERRCODE;
	}

	//The following function is used to disable the clock and  data line toggling while we chirp during LO/TX calibation.
	DolphinIC_rval_t hal_ES3_CIF_Datatoggle_Disable(void)
	{
		Nxp_Tef810x_Mod03_WindowactiveselUnion_t WindowactiveselUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16, &WindowactiveselUnion_t.val_u32, NULL);
		WindowactiveselUnion_t.bits_st.WindowActiveRegControl = 1;
		WindowactiveselUnion_t.bits_st.WindowActiveSel = 0;

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16, WindowactiveselUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;

	}
	//The following function is used to Enable the clock and  data line toggling after the chirp trigger for LO/TX calibation.
	DolphinIC_rval_t hal_ES3_CIF_Datatoggle_Enable(void)
	{
		Nxp_Tef810x_Mod03_WindowactiveselUnion_t WindowactiveselUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16, &WindowactiveselUnion_t.val_u32, NULL);
		WindowactiveselUnion_t.bits_st.WindowActiveRegControl = 0;
		WindowactiveselUnion_t.bits_st.WindowActiveSel = 0;

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(CIF_MODULE_ADDRESS, NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16, WindowactiveselUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;

	}
#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
