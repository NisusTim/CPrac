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
* @file hal_es3_cctrl.c
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

#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_Ism.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	DolphinIC_rval_t hal_es3_cctrl_SetPonClkRst(int reg, bool set, uint32_t modList)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint16_t regAddr = 0;
		Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t IpLevelPonEnable_ust;

		HAL_GERRCODE_INIT;

		switch (reg)
		{
		case hal_es3_cctrl_Pon:
			//PON
			regAddr = NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16;
			break;
		case hal_es3_cctrl_ClkEn:
			//Clk
			regAddr = NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16;
			break;
		case hal_es3_cctrl_Rst:
			//Reset
			regAddr = NXP_TEF810X_MOD00_RESET_CONTROL_U16;
			set = !(set);
			break;
		case hal_es3_cctrl_FuncRst:
			//functional reset
			regAddr = NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16;
			set = !(set);
			break;
		default:
			//no operation will be done.
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
		}

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, regAddr, &IpLevelPonEnable_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (set)
		{
			// set bits
			IpLevelPonEnable_ust.val_u32 |= modList;
		}
		else
		{
			// clear bits
			IpLevelPonEnable_ust.val_u32 &= ~(modList);
		}

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, regAddr, IpLevelPonEnable_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cctrl_SetLdoSSBMod(bool enable, uint32_t vout)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t LdoSsbmodControl_ust;

		HAL_GERRCODE_INIT;

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16, &LdoSsbmodControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		LdoSsbmodControl_ust.bits_st.LdoSelVoutSsbmod = vout;
		LdoSsbmodControl_ust.bits_st.LdoEnSsbmod = enable;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16, LdoSsbmodControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cctrl_SetSerialiserMode(int mode)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t SerialiserModeSel_ust;

		HAL_GERRCODE_INIT;

		//1: CSI2, 2:LVDS, 3:CIF
		mode = (mode >= 3) ? (3) : (mode);

		//Rd-Mod-Wr
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16, &SerialiserModeSel_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SerialiserModeSel_ust.bits_st.SwCtrlSerModeSel = mode;

		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16, SerialiserModeSel_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cctrl_SetATB1MasterSwitch(uint32_t regval)
	{
		///* DECLARE LOCAL VARIABLES HERE *///

		HAL_GERRCODE_INIT;
		//glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, CCTRL_ATB1_AC_EN_REGISTER_OFFSET, regval, NULL);
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_ATB1_AC_EN_REGISTER_U16, regval, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cctrl_SetDynamicPowerMode(int mode, bool setTx, bool setRx, bool setLo, bool setAdc, bool setChirp, bool setSerializer)
	{

		Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t DynamicPowerControlEnable;
		Nxp_Tef810x_Mod00_ScratchRegister8Union_t ScratchRegister8;
		Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t ChirpTriggerModeControl;
		Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t RfPowerDownControl;

		HAL_GERRCODE_INIT;

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_ENABLE_U16, &DynamicPowerControlEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		DynamicPowerControlEnable.bits_st.DyPowerModeSel = mode < hal_es3_cctrl_PerChirp ? 0 : 1;

		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER8_U16, &ScratchRegister8.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16, &ChirpTriggerModeControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RF_POWER_DOWN_CONTROL_U16, &RfPowerDownControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpTriggerModeControl.bits_st.ChirpPowerMode = mode < hal_es3_cctrl_PerChirp ? 0 : 1;
		//for dynamic power mode per chirp, the chirp start has to be set to per chirp toggle mode.
		ChirpTriggerModeControl.bits_st.SelModeForChirpStartOut = mode < hal_es3_cctrl_PerChirp ? 0 : 1;
		ScratchRegister8.bits_st.OverrideChirpLevelDynamicPowerAdc = 1;
		RfPowerDownControl.bits_st.RfPowerDownCountThreshold = setChirp && (mode > 0);

		switch (mode) {
		case hal_es3_cctrl_PerChirp:
			ScratchRegister8.bits_st.OverrideChirpLevelDynamicPowerAdc = !setChirp;
		case hal_es3_cctrl_PerSequence:
			if (setChirp) {
				//TODO: set chirp_fast_switch_delay to 0x100
			}
			DynamicPowerControlEnable.bits_st.Tx1DyPowerControl = setTx;
			DynamicPowerControlEnable.bits_st.Tx2DyPowerControl = setTx;
			DynamicPowerControlEnable.bits_st.Tx3DyPowerControl = setTx;
			DynamicPowerControlEnable.bits_st.Rx1DyPowerControl = setRx;
			DynamicPowerControlEnable.bits_st.Rx2DyPowerControl = setRx;
			DynamicPowerControlEnable.bits_st.Rx3DyPowerControl = setRx;
			DynamicPowerControlEnable.bits_st.Rx4DyPowerControl = setRx;
			DynamicPowerControlEnable.bits_st.LoInterfaceDyPowerControl = setLo;
			DynamicPowerControlEnable.bits_st.AdcDyPowerControl = setAdc;
			DynamicPowerControlEnable.bits_st.ChirpDyPowerControl = setChirp;
			DynamicPowerControlEnable.bits_st.SerDyClockControl = setSerializer;
			DynamicPowerControlEnable.bits_st.SerDyPowerControl = setSerializer;
			break;
		case hal_es3_cctrl_None:
			DynamicPowerControlEnable.bits_st.Tx1DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Tx2DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Tx3DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Rx1DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Rx2DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Rx3DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.Rx4DyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.LoInterfaceDyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.AdcDyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.ChirpDyPowerControl = 0;
			DynamicPowerControlEnable.bits_st.SerDyClockControl = 0;
			DynamicPowerControlEnable.bits_st.SerDyPowerControl = 0;
			break;
		}
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_ENABLE_U16, DynamicPowerControlEnable.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_SCRATCH_REGISTER8_U16, ScratchRegister8.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16, ChirpTriggerModeControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_RF_POWER_DOWN_CONTROL_U16, RfPowerDownControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3

