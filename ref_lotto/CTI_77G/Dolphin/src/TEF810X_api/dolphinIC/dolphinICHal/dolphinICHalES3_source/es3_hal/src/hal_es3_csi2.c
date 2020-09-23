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
* @file hal_es3_csi2.c
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief CSI2 Low-Level Interface.
*
*
******************************************************************************/

#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_Csi2.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_csi2_Init(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval = 0x00;
//		uint8_t master_idiv_val = 0x00;
		Nxp_Tef810x_Mod02_PdcConfigRegUnion_t PdcConfigReg_ust;
		Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Union_t Csi2Adaptconfigreg1;
		Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t Csi2Adaptconfigreg2;
		Nxp_Tef810x_Mod02_Trimreg0Union_t Trimreg0;
		Nxp_Tef810x_Mod02_Trimreg1Union_t Trimreg1;
		Nxp_Tef810x_Mod02_PllCountRegisterUnion_t PllCountRegister;
		Nxp_Tef810x_Mod02_PhyTinitCountRegisterUnion_t PhyTinitCountRegister;
		Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t Csi2Testmodecontrolreg;

		HAL_GERRCODE_INIT;


		// Assert functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, CSI2_CSI2ADAPTCONFIGREG1_OFFSET, 0x2c, NULL);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG1_U16, &Csi2Adaptconfigreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Csi2Adaptconfigreg1.bits_st.Csi2Packettype = 0x2C;
		Csi2Adaptconfigreg1.bits_st.Csi2Dphyclkmode = 0x1;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG1_U16, Csi2Adaptconfigreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, CSI2_CSI2ADAPTCONFIGREG2_OFFSET, 0x02010000, NULL);
		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, 0x02010000, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, &Csi2Adaptconfigreg2.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x20;
		Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, Csi2Adaptconfigreg2.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, CSI2_TRIMREG0_OFFSET, 0xa040218, NULL);


		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG0_U16, &Trimreg0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
		Trimreg0.bits_st.LptxTrimSlew = 0;
		Trimreg0.bits_st.TrSel = 2;
		Trimreg0.bits_st.Gdefault = 1;
		Trimreg0.bits_st.Gnctrl = 0;
		Trimreg0.bits_st.Rxcksel = 0;
		Trimreg0.bits_st.Rxhsdpol = 0;
		Trimreg0.bits_st.CapenPwl = 1;
		Trimreg0.bits_st.Cdpd = 0;
		Trimreg0.bits_st.HsDcTestEn = 0;
		Trimreg0.bits_st.LpDcTestEn = 0;
		Trimreg0.bits_st.DcTestData = 0;
		Trimreg0.bits_st.TrimBitGlitch = 0;
		Trimreg0.bits_st.Iref20UCpTrim = 0;
		Trimreg0.bits_st.PulserBypass = 1;
		Trimreg0.bits_st.VcoSelection = 0;
		Trimreg0.bits_st.LatchInvDelayCtrl = 0;
		Trimreg0.bits_st.DdrDelaySel = 0;
		
		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG0_U16, Trimreg0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, 0x4db11000, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, &Trimreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Trimreg1.bits_st.Cnta = 3;
		Trimreg1.bits_st.Cntb = 0;
		Trimreg1.bits_st.Dlpf = 0;
		Trimreg1.bits_st.DlpfRegSel = 0;
		Trimreg1.bits_st.RefinSel = 0;
		Trimreg1.bits_st.SpareBits = 1;
		Trimreg1.bits_st.PllLockTrim = 0;
		Trimreg1.bits_st.Bwb = 4;
		Trimreg1.bits_st.Res = 0;
		Trimreg1.bits_st.Plltstcksel = 3;
		Trimreg1.bits_st.Tstodby4 = 0;
		Trimreg1.bits_st.CdhighTrim = 3;
		Trimreg1.bits_st.CdlowTrim = 3;
		Trimreg1.bits_st.TrimHstxLdoPd = 0;
		Trimreg1.bits_st.Rtermctrl = 1;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, Trimreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Do not program, reset value is correct
		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG2_U16, 0x10000000, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Do not program, reset value is correct
		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG3_U16, 0x20c1fc, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PLL_COUNT_REGISTER_U16, 0x00, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PLL_COUNT_REGISTER_U16, &PllCountRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		PllCountRegister.bits_st.PllCnt = 0;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PLL_COUNT_REGISTER_U16, PllCountRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PHY_TINIT_COUNT_REGISTER_U16, 0x00002000, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PHY_TINIT_COUNT_REGISTER_U16, &PhyTinitCountRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		PhyTinitCountRegister.bits_st.TinitTimer = 0x2000;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PHY_TINIT_COUNT_REGISTER_U16, PhyTinitCountRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		// Normal Mode
		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, 0x00, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, &Csi2Testmodecontrolreg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Csi2Testmodecontrolreg.bits_st.Csi2TestmodeDataSel = 0;
		Csi2Testmodecontrolreg.bits_st.Csi2TestmodeEn = 0;
		Csi2Testmodecontrolreg.bits_st.Csi2TestmodeSkipPdc= 0;
		Csi2Testmodecontrolreg.bits_st.Csi2TestmodeTestData = 0;
		
		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, Csi2Testmodecontrolreg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		// Disable transmission. Do not program, reset value is correct.
		//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, 0x00, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Set PDC unsigned
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16, &PdcConfigReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		PdcConfigReg_ust.bits_st.MakeOutputUnsigned = MAKE_CSI2_OUTPUT_UNSIGNED;
		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16, PdcConfigReg_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Release functional reset for Serializer block ...
		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//not needed anymore, this is set in the main programming sequence
		//hal_es3_csi2_Config(64, 0x03, 0x00); // 4-Lanes @ 480Mbps

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_csi2_Config(uint32_t NLanes, hal_es3_csi2_DataRate_t DataRate, bool PDCSyncEnable)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval[10] = { 0xBABAFAFA };

		Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterUnion_t deviceReadyFlag;
		Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t Csi2Adaptconfigreg2;
		Nxp_Tef810x_Mod02_Trimreg1Union_t Trimreg1;
		Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterUnion_t PpiDataLaneSwapRegister_ust;
		Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Union_t DphyDfeDlnRegister0;
		Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Union_t DphyDfeDlnRegister1;
		Nxp_Tef810x_Mod02_DphyDfeClnRegister0Union_t DphyDfeClnRegister0;
		Nxp_Tef810x_Mod02_DphyDfeClnRegister1Union_t DphyDfeClnRegister1;
		Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t Csi2TxnCtrl;
		Nxp_Tef810x_Mod02_AtbSetTrimUnion_t AtbSetTrimUnion_t;

		HAL_GERRCODE_INIT;
		

		DbgInfo("%d, %d \n", NLanes, DataRate);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// Cfg Number of Lanes ...
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PPI_DATA_LANE_SWAP_REGISTER_U16, &PpiDataLaneSwapRegister_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//regval[0x00] &= ~(CSI2_PPI_DATA_LANE_SWAP_REGISTER_NUMBER_OF_LANES_MSK);
		PpiDataLaneSwapRegister_ust.bits_st.NumberOfLanes = NLanes;

		//regval[0x00] |= (NLanes << CSI2_PPI_DATA_LANE_SWAP_REGISTER_NUMBER_OF_LANES_POS);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_PPI_DATA_LANE_SWAP_REGISTER_U16, PpiDataLaneSwapRegister_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_ATB_SET_TRIM_U16, &AtbSetTrimUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		AtbSetTrimUnion_t.bits_st.AtbSetTrimRN = PDCSyncEnable ? 1 : 0;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_ATB_SET_TRIM_U16, AtbSetTrimUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, &Csi2Adaptconfigreg2.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, &Trimreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16, &DphyDfeDlnRegister0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16, &DphyDfeDlnRegister1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16, &DphyDfeClnRegister0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16, &DphyDfeClnRegister1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (DataRate)
		{
		case HAL_ES3_CSI2_DATARATE_480: //480Mbps
		{

			//delay_lut[0] = 0x06810000; delay_lut[1] = 0x03610000; delay_lut[2] = 0x02010000; delay_lut[3] = 0x02010000;

			switch (NLanes)
			{
			case 0:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x78;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 1:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x46;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 2:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x20;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 3:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x30;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			default:
				break;
			}
						
			//0x4db11006
			Trimreg1.bits_st.Rtermctrl = 1;
			Trimreg1.bits_st.TrimHstxLdoPd = 0;
			Trimreg1.bits_st.CdlowTrim = 3;
			Trimreg1.bits_st.CdhighTrim = 3;
			Trimreg1.bits_st.Tstodby4 = 0;
			Trimreg1.bits_st.Plltstcksel = 3;
			Trimreg1.bits_st.Res = 0;
			Trimreg1.bits_st.Bwb = 4;
			Trimreg1.bits_st.PllLockTrim = 0;
			Trimreg1.bits_st.SpareBits = 1;
			Trimreg1.bits_st.RefinSel = 0;
			Trimreg1.bits_st.DlpfRegSel = 0;
			Trimreg1.bits_st.Dlpf = 0;
			Trimreg1.bits_st.Cntb = 0;
			Trimreg1.bits_st.Cnta = 6;
			
			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16, 0x03068309, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeDlnRegister0.bits_st.DfeDlnHsTrial = 3;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsExit = 6;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsPrepare = 0x83;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsZeroCnt = 9;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16, 0x00030e04, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			DphyDfeDlnRegister1.bits_st.DfeDlnLpxHsCnt = 3;
			DphyDfeDlnRegister1.bits_st.DfeDlnSyncCnt = 0xE;
			DphyDfeDlnRegister1.bits_st.DfeDlnRxCnt = 4;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16, 0x0406030e, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			DphyDfeClnRegister0.bits_st.DfeClnHsTrial = 4;
			DphyDfeClnRegister0.bits_st.DfeClnHsExit = 6;
			DphyDfeClnRegister0.bits_st.DfeClnPrepare = 3;
			DphyDfeClnRegister0.bits_st.DfeClnZero = 0xE;
			
			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16, 0x000a0102, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			
			DphyDfeClnRegister1.bits_st.TclkPost = 0xA;
			DphyDfeClnRegister1.bits_st.TclkPre = 1;
			DphyDfeClnRegister1.bits_st.DfeClnLpxHsCnt = 2;
			
		}
		break;

		case HAL_ES3_CSI2_DATARATE_240: //240Mbps
		{
			//delay_lut[0] = 0x0d010000; delay_lut[1] = 0x07C10000; delay_lut[2] = 0x04610000; delay_lut[3] = 0x04610000;

			glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, &Csi2Adaptconfigreg2.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			switch (NLanes)
			{
			case 0:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0xE0;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 1:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x8C;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 2:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x46;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 3:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x56;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			default:
				break;
			}

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, 0x4db11003, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			Trimreg1.bits_st.Rtermctrl = 1;
			Trimreg1.bits_st.TrimHstxLdoPd = 0;
			Trimreg1.bits_st.CdlowTrim = 3;
			Trimreg1.bits_st.CdhighTrim = 3;
			Trimreg1.bits_st.Tstodby4 = 0;
			Trimreg1.bits_st.Plltstcksel = 3;
			Trimreg1.bits_st.Res = 0;
			Trimreg1.bits_st.Bwb = 4;
			Trimreg1.bits_st.PllLockTrim = 0;
			Trimreg1.bits_st.SpareBits = 1;
			Trimreg1.bits_st.RefinSel = 0;
			Trimreg1.bits_st.DlpfRegSel = 0;
			Trimreg1.bits_st.Dlpf = 0;
			Trimreg1.bits_st.Cntb = 0;
			Trimreg1.bits_st.Cnta = 3;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16, 0x01038106, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeDlnRegister0.bits_st.DfeDlnHsTrial = 1;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsExit = 3;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsPrepare = 0x81;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsZeroCnt = 6;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16, 0x00010a03, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeDlnRegister1.bits_st.DfeDlnLpxHsCnt = 3;
			DphyDfeDlnRegister1.bits_st.DfeDlnSyncCnt = 0xA;
			DphyDfeDlnRegister1.bits_st.DfeDlnRxCnt = 4;


			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16, 0x03030106, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeClnRegister0.bits_st.DfeClnHsTrial = 3;
			DphyDfeClnRegister0.bits_st.DfeClnHsExit = 6;
			DphyDfeClnRegister0.bits_st.DfeClnPrepare = 3;
			DphyDfeClnRegister0.bits_st.DfeClnZero = 0xE;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16, 0x00080101, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeClnRegister1.bits_st.TclkPost = 8;
			DphyDfeClnRegister1.bits_st.TclkPre = 1;
			DphyDfeClnRegister1.bits_st.DfeClnLpxHsCnt = 1;
		}
		break;

		case HAL_ES3_CSI2_DATARATE_120: //120 Mbps
		{
			//delay_lut[0] = 0x1A810000; delay_lut[1] = 0x0e810000; delay_lut[2] = 0x07010000; delay_lut[3] = 0x07010000;

			switch (NLanes)
			{
			case 0:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x1B8;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 1:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0xF8;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 2:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0x70;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			case 3:
				Csi2Adaptconfigreg2.bits_st.Csi2Delaycnt = 0xa8;
				Csi2Adaptconfigreg2.bits_st.Csi2Dphyclkdiv = 1;
				break;

			default:
				break;
			}

			//0x4db11041
			Trimreg1.bits_st.Rtermctrl = 1;
			Trimreg1.bits_st.TrimHstxLdoPd = 0;
			Trimreg1.bits_st.CdlowTrim = 3;
			Trimreg1.bits_st.CdhighTrim = 3;
			Trimreg1.bits_st.Tstodby4 = 0;
			Trimreg1.bits_st.Plltstcksel = 3;
			Trimreg1.bits_st.Res = 0;
			Trimreg1.bits_st.Bwb = 4;
			Trimreg1.bits_st.PllLockTrim = 0;
			Trimreg1.bits_st.SpareBits = 1;
			Trimreg1.bits_st.RefinSel = 0;
			Trimreg1.bits_st.DlpfRegSel = 0;
			Trimreg1.bits_st.Dlpf = 0;
			Trimreg1.bits_st.Cntb = 1;
			Trimreg1.bits_st.Cnta = 1;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16, 0x00028004, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeDlnRegister0.bits_st.DfeDlnHsTrial = 1;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsExit = 2;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsPrepare = 0x80;
			DphyDfeDlnRegister0.bits_st.DfeDlnHsZeroCnt = 4;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16, 0x00000803, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeDlnRegister1.bits_st.DfeDlnLpxHsCnt = 0;
			DphyDfeDlnRegister1.bits_st.DfeDlnSyncCnt = 0x8;
			DphyDfeDlnRegister1.bits_st.DfeDlnRxCnt = 3;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16, 0x02024003, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeClnRegister0.bits_st.DfeClnHsTrial = 2;
			DphyDfeClnRegister0.bits_st.DfeClnHsExit = 2;
			DphyDfeClnRegister0.bits_st.DfeClnPrepare = 40;
			DphyDfeClnRegister0.bits_st.DfeClnZero = 0x3;

			//glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16, 0x00070100, NULL);
			//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			DphyDfeClnRegister1.bits_st.TclkPost = 7;
			DphyDfeClnRegister1.bits_st.TclkPre = 1;
			DphyDfeClnRegister1.bits_st.DfeClnLpxHsCnt = 0;
		}
		break;

		default:
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
		}
		break;
		}

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16, Csi2Adaptconfigreg2.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_TRIMREG1_U16, Trimreg1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16, DphyDfeDlnRegister0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16, DphyDfeDlnRegister1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16, DphyDfeClnRegister0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16, DphyDfeClnRegister1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Enable Transmission
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, &Csi2TxnCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		Csi2TxnCtrl.bits_st.Csi2TxnEn = 1;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, Csi2TxnCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_Tic();
		do
		{
			glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_DEVICE_READY_INDICATION_REGISTER_U16, &deviceReadyFlag.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			//timeout
			if (glue_Toc() >= CSI2_PLL_READY_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("CSi2 PLL Locking : it didn't finish within %.2f ms...\n", CSI2_PLL_READY_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_CSI2_PLL_LOCK_TIMEOUT);
			}
		} while (deviceReadyFlag.bits_st.DeviceReady != 1);

		return HAL_GERRCODE;
	}

	// Internal API for Validation ...
	DolphinIC_rval_t hal_es3_csi2_CfgTestMode(bool flag_enable, uint16_t data_pattern, uint8_t test_mode_sel)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t regval = 0x00;
		Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t r_testmodecntrl;

		HAL_GERRCODE_INIT;


		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, true, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, &r_testmodecntrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (flag_enable == true)
		{
			r_testmodecntrl.bits_st.Csi2TestmodeSkipPdc = 0x01;
			r_testmodecntrl.bits_st.Csi2TestmodeTestData = (data_pattern & 0xFFF);
			r_testmodecntrl.bits_st.Csi2TestmodeDataSel = test_mode_sel;
		}

		r_testmodecntrl.bits_st.Csi2TestmodeEn = flag_enable;

		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16, r_testmodecntrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_cctrl_SetPonClkRst(hal_es3_cctrl_FuncRst, false, hal_es3_cctrl_ModID_CSI2);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_csi2_getMCLKOutFrequency(float * p_freqcountrval)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		Nxp_Tef810x_Mod02_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;
		Nxp_Tef810x_Mod02_RefCntrInitUnion_t RefCntrInit_ust;
		Nxp_Tef810x_Mod02_FreqCounterStartUnion_t FreqCounterStart;

		HAL_GERRCODE_INIT;

		*p_freqcountrval = 0.0f;

		//change frequency counter trigger to SPI write to freq_start.
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_FREQ_COUNTER_START_U16, &FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FreqCounterStart.bits_st.FreqCounterTriggerSel = 0;
		FreqCounterStart.bits_st.FreqStart = 0;
		glue_reg_WriteCheck(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//trigger one counter measurement
		FreqCounterStart.bits_st.FreqStart = 1;
		glue_reg_Write(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//wait for counter.
		glue_Tic();
		do
		{
//			reg_val = 0;
			glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//timeout
			if (glue_Toc() >= CSI2_FREQ_CNT_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("CSI2 frequency counting failed: it didn't finish within %.2f ms...\n", CSI2_FREQ_CNT_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_MCLK_FREQ_CNT_TIMEOUT);
			}

		} while (FreqCounterReadValue_ust.bits_st.DoneFlag == 0);


		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_REF_CNTR_INIT_U16, &RefCntrInit_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DbgInfo("RefCNT Init(0x%x) \n", RefCntrInit_ust.val_u32);


		//read out the frequency counter.
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_FREQ_COUNTER_READ_VALUE_U16, &FreqCounterReadValue_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//FreqCounterReadValue_ust.val_u32 = FreqCounterReadValue_ust.val_u32 & CSI2_FREQ_COUNTER_READ_VALUE_FREQ_COUNT_VALUE_MSK;
		//Use the refcnt to scale read result to correct frequency unit,do not assume fixed refcnt.
		*p_freqcountrval = (FreqCounterReadValue_ust.bits_st.FreqCountValue)/((RefCntrInit_ust.bits_st.RefCountValue/40.0f));

		DbgInfo("CSI2 FCNT R-Out(0x%x) \n", *p_freqcountrval);


		return HAL_GERRCODE;
	}
	//The following function is used to disable the clock and  data line toggling while we chirp during LO/TX calibation.
	DolphinIC_rval_t hal_ES3_CSI2_Datatoggle_Disable(void)
	{
		Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t Csi2TxnCtrlUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, &Csi2TxnCtrlUnion_t.val_u32, NULL);
		Csi2TxnCtrlUnion_t.bits_st.Csi2TxnEn = 0;
		
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, Csi2TxnCtrlUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;

	}
	//The following function is used to Enable the clock and  data line toggling after the chirp trigger for LO/TX calibation.
	DolphinIC_rval_t hal_ES3_CSI2_Datatoggle_Enable(void)
	{
		Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t Csi2TxnCtrlUnion_t;
		HAL_GERRCODE_INIT;
		glue_reg_Read(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, &Csi2TxnCtrlUnion_t.val_u32, NULL);
		Csi2TxnCtrlUnion_t.bits_st.Csi2TxnEn = 1;

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Write(CSI2_MODULE_ADDRESS, NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16, Csi2TxnCtrlUnion_t.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;

	}



#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
