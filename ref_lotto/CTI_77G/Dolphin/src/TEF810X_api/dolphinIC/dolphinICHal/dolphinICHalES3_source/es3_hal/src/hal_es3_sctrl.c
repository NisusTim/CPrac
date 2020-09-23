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
* @file hal_es3_sctrl.c
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief Sweep Control Low-Level Interface.
*
*
******************************************************************************/

#include <math.h>
#include <hal_es3.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_SweepControl.h>
#include <es3/NXP_TEF810X_TimingEngine.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

#ifdef DOLPHIN_CFG_HOST_S32R274
	int HAL_ES3_SC_UPDATE_DIV = 6;
#endif

	static void hal_es3_sctrl_calcsweepctrlprofilecfg(float fStart, float usedBW, bool downchirp, float treset, float tramp, hal_es3_sctrl_profileparams_t * p_sctrl_prof)
	{
		float startDiv0 = 0.0f;
		float NStart = 0.0f;
		float NStart_frac = 0.0f;

		//----------------NStart setting---------------------------------
		startDiv0 = fStart / (HAL_ES3_SC_REF_FREQ * HAL_ES3_SC_PRESCALER * HAL_ES3_SC_MULTIPLIER);
		//C99: float modff (float x, float* intpart); //Breaks x into an integral and a fractional part.
		NStart_frac = modff(startDiv0, &NStart);

		//no problem for type casting here, since NStart must be an integer after modf()
		p_sctrl_prof->N_start_int = (uint32_t)NStart;
		p_sctrl_prof->N_start_fract = (uint32_t)(roundf(NStart_frac * (double)(1 << 26)));
		DbgInfo("(%lf) :: NStart I(%u) F(%u) \n", startDiv0, p_sctrl_prof->N_start_int, p_sctrl_prof->N_start_fract);

		//-----------Chirpping Active data period-----------------------------------------------
		float StepsInChirp = tramp * (HAL_ES3_SC_REF_FREQ/HAL_ES3_SC_UPDATE_DIV/1e6f);
		float ChirpFreqStepSize = usedBW / StepsInChirp;

		//N_STEP_CHIRP_PROFILE[x] of n means n+1 steps in ramp
		p_sctrl_prof->N_step_chirp = ((uint32_t)(roundf(StepsInChirp))) - 1;
		DbgInfo("calculated N step is:%x\n", p_sctrl_prof->N_step_chirp);

		p_sctrl_prof->DN_chirp = (uint32_t)(roundf(ChirpFreqStepSize*HAL_ES3_SC_FREQ2DIV));
		DbgInfo("calculated DNChirp is:%x\n", p_sctrl_prof->DN_chirp);

		//-----------Chirpping Reset period-----------------------------------------------
		float StepsInReset = treset * (HAL_ES3_SC_REF_FREQ/HAL_ES3_SC_UPDATE_DIV/1e6f);
		float ResetDIVStepSize = (p_sctrl_prof->DN_chirp)*StepsInChirp / StepsInReset;

		//N_STEP_RESET_RF_PROFILE[x] of n means n+1 steps in reset
		p_sctrl_prof->N_step_reset = (uint32_t)(roundf(StepsInReset)) - 1;
		p_sctrl_prof->DN_reset = (uint32_t)(roundf(ResetDIVStepSize));

		//-----------other settings-----------------------------------------------
		p_sctrl_prof->downchirp = downchirp;
		p_sctrl_prof->Div_update = HAL_ES3_SC_UPDATE_DIV - 0x01; //less one than programmed to make 3020 compatible divider
	}


	DolphinIC_rval_t hal_es3_sctrl_UpdateProfFreDiv(uint8_t profID, float fStart, float usedBW, bool downChirp, float tReset, float tRamp)
	{
		hal_es3_sctrl_profileparams_t profileParam = { 0x00 };

		Nxp_Tef810x_Mod05_NStartRfProfileUnion_t NStartRfProfile_ust;
		Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t DnChirpRfProfile_ust;
		Nxp_Tef810x_Mod05_NStepChirpRfProfileUnion_t NStepChirpRfProfile_ust;
		Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t DnResetRfProfile_ust;
		Nxp_Tef810x_Mod05_NStepResetRfProfileUnion_t NStepResetRfProfile_ust;
		Nxp_Tef810x_Mod05_DivUpdateRfProfileUnion_t DivUpdateRfProfile_ust;

		uint16_t NStartProfile = NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16;
		uint16_t DNChirpProfile = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16;
		uint16_t NStepChirpProfile = NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE0_U16;
		uint16_t DNResetProfile = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16;
		uint16_t NStepResetProfile = NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE0_U16;
		uint16_t DivUpdateProfile = NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE0_U16;

		HAL_GERRCODE_INIT;

		hal_es3_sctrl_calcsweepctrlprofilecfg(fStart, usedBW, downChirp, tReset, tRamp, &profileParam);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (profID)
		{
		case 1:
			NStartProfile = NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16;
			DNChirpProfile = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE1_U16;
			NStepChirpProfile = NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE1_U16;
			DNResetProfile = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE1_U16;
			NStepResetProfile = NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE1_U16;
			DivUpdateProfile = NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE1_U16;
			break;
		case 2:
			NStartProfile = NXP_TEF810X_MOD05_N_START_RF_PROFILE2_U16;
			DNChirpProfile = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE2_U16;
			NStepChirpProfile = NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE2_U16;
			DNResetProfile = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE2_U16;
			NStepResetProfile = NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE2_U16;
			DivUpdateProfile = NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE2_U16;
			break;
		case 3:
			NStartProfile = NXP_TEF810X_MOD05_N_START_RF_PROFILE3_U16;
			DNChirpProfile = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE3_U16;
			NStepChirpProfile = NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE3_U16;
			DNResetProfile = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE3_U16;
			NStepResetProfile = NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE3_U16;
			DivUpdateProfile = NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE3_U16;
			break;
		default:
			NStartProfile = NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16;
			DNChirpProfile = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16;
			NStepChirpProfile = NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE0_U16;
			DNResetProfile = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16;
			NStepResetProfile = NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE0_U16;
			DivUpdateProfile = NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE0_U16;
			break;
		}

		//No need to Read here, this register is consist of only the two following fields
		//Mod-Wr
		NStartRfProfile_ust.val_u32 = 0;
		NStartRfProfile_ust.bits_st.NstartfracrfProfile0 = profileParam.N_start_fract;
		NStartRfProfile_ust.bits_st.NstartintrfProfile0 = profileParam.N_start_int;
		DbgInfo("NStart:%x\n", NStartRfProfile_ust.val_u32);

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NStartProfile, NStartRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		if (profileParam.downchirp == true)
		{
			profileParam.DN_chirp |= (1 << 26);
		}
		else
		{
			profileParam.DN_reset |= (1 << 26);
		}

		// step size during chirp active period
		// No need to Read here, this register is consist of only the following fields
		// Mod-Wr
		DnChirpRfProfile_ust.val_u32 = 0;
		DnChirpRfProfile_ust.bits_st.DnchirpactiveRegProfile0 = profileParam.DN_chirp;

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, DNChirpProfile, DnChirpRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// number of chirp step  during chirp active period
		// No need to Read here, this register is consist of only the two following fields
		// Mod-Wr
		NStepChirpRfProfile_ust.val_u32 = 0;
		NStepChirpRfProfile_ust.bits_st.NstepchirpactiveRegProfile0 = profileParam.N_step_chirp;

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NStepChirpProfile, NStepChirpRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Reset chirp step size during chirp reset period
		// No need to Read here, this register is consist of only the two following fields
		// Mod-Wr
		DnResetRfProfile_ust.val_u32 = 0;
		DnResetRfProfile_ust.bits_st.DnchirpresetRegProfile0 = profileParam.DN_reset;

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS,DNResetProfile, DnResetRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// number of steps in chirp reset period
		// No need to Read here, this register is consist of only the two following fields
		// Mod-Wr
		NStepResetRfProfile_ust.val_u32 = 0;
		NStepResetRfProfile_ust.bits_st.NstepchirpresetRegProfile0 = profileParam.N_step_reset;

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NStepResetProfile,NStepResetRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// DivUpdateRF_profile0
		// Rd-Mod-Wr
		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, DivUpdateProfile, &DivUpdateRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DbgInfo("DIV update read value:%x\n", DivUpdateRfProfile_ust.val_u32);
		DivUpdateRfProfile_ust.bits_st.FreqDeviationBitsProfile0 = 0x3; //fixed ISM_ERROR vco_freq_480_error_flag_chirp.
		DivUpdateRfProfile_ust.bits_st.DivupdaterfProfile0 = profileParam.Div_update;

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, DivUpdateProfile, DivUpdateRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_sctrl_CWMode()//CHANGED TO PERFORM COMPENSATION ONLY
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		
		uint16_t N_START_RF_PROFILE;
		uint32_t NStartFracRF;

		Nxp_Tef810x_Mod05_NStartRfProfileUnion_t NStartRfProfile_ust;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;

		HAL_GERRCODE_INIT;

		//user wants to operate in CWMode
		//The following implements UM 2.2.3.3 Continuous Wave Mode for details
		uint32_t chirpProfileConf = 0;
		//get current chirp_profile_select setting from TE
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DbgInfo("current chirp profile:%d\n", ChirpGlobalControl_ust.bits_st.ChirpProfileSelect);

		//choose N_START_PROFILE based on chirp profile used in TE
		N_START_RF_PROFILE = 0x00;
		switch (chirpProfileConf)
		{
		case 0:
			N_START_RF_PROFILE = NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16;
			break;
		case 1:
			N_START_RF_PROFILE = NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16;
			break;
		case 2:
			N_START_RF_PROFILE = NXP_TEF810X_MOD05_N_START_RF_PROFILE2_U16;
			break;
		case 3:
			N_START_RF_PROFILE = NXP_TEF810X_MOD05_N_START_RF_PROFILE3_U16;
			break;
		default:
			N_START_RF_PROFILE = NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16;
			break;
		}

		//read back current N_START_RF_PROFILE settings
		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, N_START_RF_PROFILE, &NStartRfProfile_ust.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		NStartFracRF = NStartRfProfile_ust.bits_st.NstartfracrfProfile0;

		if (NStartFracRF != 0)
		{
			DbgInfo("Adjusting NStartFracRF for CWMode...\n");
			DbgInfo("Old NStartFracRF is:%x\n", NStartFracRF);
			NStartFracRF |= 0x01;
			DbgInfo("New NStartFracRF is:%x\n", NStartFracRF);

			glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, N_START_RF_PROFILE, &NStartRfProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			NStartRfProfile_ust.bits_st.NstartfracrfProfile0 = NStartFracRF;

			glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, N_START_RF_PROFILE, NStartRfProfile_ust.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_sctrl_ZeroRamp(uint8_t profID)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t DnChirpRfProfile;
		Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t DnResetRfProfile;
		uint16_t NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16;
		uint16_t NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16;


		HAL_GERRCODE_INIT;

		switch (profID)
		{
		case 0:
			NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16;
			NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16;
				
			break;
		case 1:

			NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE1_U16;
			NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE1_U16;

			break;
		case 2:
			NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE2_U16;
			NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE2_U16;
			
			break;
		case 3:
			NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE3_U16;
			NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE3_U16;
			
			break;
		default:
			NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16;
			NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16 = NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16;
			
			break;
		}

		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16, &DnChirpRfProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		DnChirpRfProfile.bits_st.DnchirpactiveRegProfile0 = 0;
		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE_U16, DnChirpRfProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16, &DnResetRfProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		DnResetRfProfile.bits_st.DnchirpresetRegProfile0 = 0;
		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE_U16, DnResetRfProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_sctrl_CompensateChirpStitching()
	{
		Nxp_Tef810x_Mod05_NStartRfProfileUnion_t NStartRFProfile1;
		Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t DnChirpProfile1;

		HAL_GERRCODE_INIT;

		//Do the "1-step higher" compensation for chirp stitching
		//Chirp stitching is done in the API using profile0 and profile1
		//So here profile1 is compensated to be "1-step higher"
		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16, &NStartRFProfile1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE1_U16, &DnChirpProfile1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		DbgInfo("NStart frac part before 1-step comp:\t0x%x\n", NStartRFProfile1.bits_st.NstartfracrfProfile0);

		NStartRFProfile1.bits_st.NstartfracrfProfile0 += DnChirpProfile1.bits_st.DnchirpactiveRegProfile0;

		DbgInfo("NStart frac part after 1-step comp:\t0x%x\n", NStartRFProfile1.bits_st.NstartfracrfProfile0);

		glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16, NStartRFProfile1.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
