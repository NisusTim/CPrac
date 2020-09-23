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
* @file hal_es3_cafc.c
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief Chirp AFC Low-Level Interface.
*
*
******************************************************************************/

#define _USE_MATH_DEFINES

#include <hal_es3.h>
#include <hal_es3_ctrl.h>
#include <math.h>

#ifdef DOLPHIN_CFG_ES3

#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_Ism.h>
#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_Atb.h>

#ifndef M_PI
// Source: http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
#define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406f
#endif

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

#ifndef SB_BINARYSEARCH_ENABLE
	//Global VCO tables
	//Narrow Band VCO table
	VCOTableItemES3_t VCOTableNBES3[128];
	//Wide Band VCO table
	VCOTableItemES3_t VCOTableWBES3[128];
#endif

	//both tables are calculated with fc = 76GHz, loop gain compensation should use this value.
	///1GHz mode, settings related to loop BW PM = 50
	static const VCO_FILTER_LUT_ES3_t CAFC_1G_LUT[NUM_ITEM_VCO_FILTER_LUT_ES3] = {
			{ 300e3f, 20, 31, 31, 2, 20},
			{ 350e3f, 16, 31, 31, 2, 24 },
			{ 400e3f, 13, 31, 31, 2, 27 },
			{ 450e3f, 10, 29, 28, 3, 20 },
			{ 500e3f, 9, 25, 24, 3, 23 },
			{ 550e3f, 7, 22, 21, 3, 25 },
			{ 600e3f, 6, 19, 19, 4, 20 },
			{ 650e3f, 5, 17, 17, 4, 22 },
			{ 700e3f, 4, 15, 15, 4, 24 },
			{ 750e3f, 3, 14, 13, 5, 20 },
			{ 800e3f, 2, 13, 12, 5, 22 },
			{ 850e3f, 2, 11, 11, 5, 23 },
			{ 900e3f, 1, 10, 10, 6, 20 },
			{ 950e3f, 1, 9, 9, 6, 22 },
			{ 1000e3f, 0, 8, 8, 6, 23 },
			{ 1050e3f, 0, 8, 7, 7, 20 },
			{ 1100e3f, 0, 7, 7, 7, 21 },
			{ 1150e3f, 0, 6, 6, 7, 22 },
			{ 1200e3f, 0, 6, 5, 8, 20 },
			{ 1250e3f, 0, 5, 5, 8, 21 },
			{ 1300e3f, 0, 5, 4, 8, 20 },
			{ 1350e3f, 0, 4, 4, 8, 20 },
			{ 1400e3f, 0, 4, 3, 8, 21 } };


	///2GHz mode, settings related to loop BW PM = 50
	static const VCO_FILTER_LUT_ES3_t CAFC_2G_LUT[NUM_ITEM_VCO_FILTER_LUT_ES3] = {
			{ 300e3f, 20, 31, 31, 0, 18},
			{ 350e3f, 16, 31, 31, 1, 22},
			{ 400e3f, 13, 31, 31, 1, 25},
			{ 450e3f, 10, 29, 28, 1, 29},
			{ 500e3f, 9, 25, 24, 1, 32},
			{ 550e3f, 7, 22, 21, 1, 35},
			{ 600e3f, 6, 19, 19, 1, 38},
			{ 650e3f, 5, 17, 17, 2, 21},
			{ 700e3f, 4, 15, 15, 2, 22},
			{ 750e3f, 3, 14, 13, 2, 24},
			{ 800e3f, 2, 13, 12, 2, 25},
			{ 850e3f, 2, 11, 11, 2, 27},
			{ 900e3f, 1, 10, 10, 2, 29},
			{ 950e3f, 1, 9, 9, 3, 20},
			{ 1000e3f, 0, 8, 8, 3, 21},
			{ 1050e3f, 0, 8, 7, 3, 22},
			{ 1100e3f, 0, 7, 7, 3, 23},
			{ 1150e3f, 0, 6, 6, 3, 24},
			{ 1200e3f, 0, 6, 5, 3, 25},
			{ 1250e3f, 0, 5, 5, 4, 20},
			{ 1300e3f, 0, 5, 4, 4, 21},
			{ 1350e3f, 0, 4, 4, 4, 21},
			{ 1400e3f, 0, 4, 3, 4, 22 } };

	//helper function, should not be used directly.
	//set the CAFC registers
	/**
	@brief configures the VCO filters per profile
	**/
	DolphinIC_rval_t hal_es3_cafc_VCO_Filter_Config(int ProfileNum, const VCO_FILTER_LUT_ES3_t *LUT, int index, bool narrowBand, int subband, bool downChirp, double effFc)
	{
		//choose register address based on profile number.
		///* DECLARE LOCAL VARIABLES HERE *///
		uint16_t	VCO_REG_PROFILE = 0x00;
		uint16_t	FILTER_REG_PROFILE = 0x00;
		uint16_t	FILTER_PAR_REG_PROFILE = 0x00;
		uint8_t		bin2Thermal;
//		uint8_t		CPSliceEnThermalmeterCode;
		uint8_t		newCPSliceEnDec;
		uint8_t		newCPSliceEnThermalmeterCode;
		uint8_t		newIBiasCP150u;
		float		VCOGainCorr;
		float		IcpCompensated;

		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			VCOProfile;
		Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t		FilterProfile;
		Nxp_Tef810x_Mod06_CpRegisterUnion_t					CPReg;
		Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t	FilterParProfile;
		Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t		FSMonUnlockVCO;
		///* ---------------- *///

		HAL_GERRCODE_INIT;
		switch (ProfileNum)
		{
		case 1:
		{
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			FILTER_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE1_U16;
			FILTER_PAR_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE1_U16;
			break;
		}
		case 2:
		{
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			FILTER_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE2_U16;
			FILTER_PAR_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE2_U16;
			break;
		}
		case 3:
		{
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			FILTER_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16;
			FILTER_PAR_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE3_U16;
			break;
		}
		default:
		{
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			FILTER_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16;
			FILTER_PAR_REG_PROFILE = NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE0_U16;
			break;
		}
		}

		//***compose value for VCO_REG_PROFILE

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//VCO enabled later in the main programming sequence
		//(optinal) this could be one optimization point: turn on the VCO now, later no need to use EnableVCO API and wait
		VCOProfile.bits_st.CtlVcoEnSpiProfile0 = 0;
		//note: narrowBand logic inverted,
		VCOProfile.bits_st.CtlVcoBandwidthSpiProfile0 = (narrowBand ? 0 : 1);
		//program subband
		VCOProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//***compose value for FILTER_REG_PROFILE

		FilterProfile.val_u32 = 0;
		//enable internal loop filter.
		FilterProfile.bits_st.CtlLpfIntEnSpiProfile0 = 1;

		//convert binary to thermalmeter code
		bin2Thermal = 0xff;
//		CPSliceEnThermalmeterCode = bin2Thermal >> (8 - LUT[index].CP_SLICE_EN);
		DbgInfo("Uncompensated CP_SLICE_EN binary:%d, converted to thermalmeter code:%d\n", LUT[index].CP_SLICE_EN, CPSliceEnThermalmeterCode);


		//Do VCO gain compensation
		VCOGainCorr = 1 - (effFc - REF_RF_FREQ_ES3) * 20.7f / 5e9f / 100;
		DbgInfo("VCO gain correction factor:%f\n", VCOGainCorr);

		//compensated Icp     = comp factor *  programmable bias level  *3.125uA/level  *  num of slices
		IcpCompensated = VCOGainCorr * LUT[index].IBIAS_CP_150U * 3.125f * LUT[index].CP_SLICE_EN;
		// distribute Icp current on several slices
		newCPSliceEnDec = floorf(IcpCompensated / MIN_SLICE_CURRENT_ES3);
		newCPSliceEnThermalmeterCode = bin2Thermal >> (8 - newCPSliceEnDec);
		DbgInfo("Compensated CP_SLICE_EN binary:%d, converted to thermalmeter code:%d\n", newCPSliceEnDec, newCPSliceEnThermalmeterCode);

		newIBiasCP150u = roundf(IcpCompensated / newCPSliceEnDec / 3.125f);
		DbgInfo("Uncompensated IBiasCP150u:%d\n", LUT[index].IBIAS_CP_150U);
		DbgInfo("Compensated IBiasCP150u:%d\n", newIBiasCP150u);

		//program the compensated values for KVCO
		FilterProfile.bits_st.CtlCpSliceEnSpiProfile0 = newCPSliceEnThermalmeterCode;
		FilterProfile.bits_st.CtlIbiasCp150USpiProfile0 = newIBiasCP150u;
		//set CtlLpfExtEnSpiProfile0 to 1 ONLY in test and validation to observe vtune.
		FilterProfile.bits_st.CtlLpfExtEnSpiProfile0 = 0;

		// The following commented-out lines are uncompensated values.
		//FilterProfile.bits_st.CtlCpSliceEnSpiProfile0 = CPSliceEnThermalmeterCode;
		//FilterProfile.bits_st.CtlIbiasCp150USpiProfile0 = LUT[index].IBIAS_CP_150U;


		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, FILTER_REG_PROFILE, FilterProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//***compose value for FILTER_PAR_REG_PROFILE

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, FILTER_PAR_REG_PROFILE, &FilterParProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		DbgInfo("LPF setting: %d, %d, %d\n", LUT[index].LPF_C1, LUT[index].LPF_C2, LUT[index].LPF_C3);

		//R1 R2 values depends on calibration.
		FilterParProfile.bits_st.CtlLpfC1SpiProfile0 = LUT[index].LPF_C1;
		FilterParProfile.bits_st.CtlLpfC2SpiProfile0 = LUT[index].LPF_C2;
		FilterParProfile.bits_st.CtlLpfC3SpiProfile0 = LUT[index].LPF_C3;
		FilterParProfile.bits_st.CtlLpfVtuneMonitorEnSpiProfile0 = 1;

		DbgInfo("FILTER_PAR setting: %x\n", FilterParProfile.val_u32);
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, FILTER_PAR_REG_PROFILE, FilterParProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//!The following configurations are not profile based!

		//***compose value for CP_REGISTER
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, &CPReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//preserve ioffset and set other settings.
		CPReg.bits_st.CtlCpReplicaBiasEnSpi = 1;
		CPReg.bits_st.CtlCpEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CPReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//***set up lock detector
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16, &FSMonUnlockVCO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//clear pol bit
		FSMonUnlockVCO.bits_st.CtlLdPolSpi = downChirp;
		//enable LD, already done as a part of init
		//FSMonUnlockVCO.bits_st.CtlLdEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16, FSMonUnlockVCO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cafc_ProfileConfig(int ProfileNum, bool narrowBand, bool downChirp, int subband, float loopBW, float usedBW, double effFc, float tSettle, float tSample, float tJumpback)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		float	loopBWInt = 0;
		int		index;

		HAL_GERRCODE_INIT;
		Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t       CAFCFSMonUnlockVco;

		//Program the CP_Ioffset
		//hal_es3_cafc_CP_IOFFSET_Config(tSettle + tSample + tJumpback, usedBW, loopBW, narrowBand);

		//Unlock Monitor - change LD_WINDOW_DELTA to 0xF if condition is true
		if (((usedBW/(tSample+tSettle+tJumpback)) < (float)(15.0 * 1.0e6)) && (loopBW > (float)300000.0))
		{
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16,&CAFCFSMonUnlockVco.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			CAFCFSMonUnlockVco.bits_st.CtlLdWindowDeltaSpi = 0xFU;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16,CAFCFSMonUnlockVco.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		//decision based on narrowBand
		if (narrowBand)
		{
			if (loopBW < LOOP_BW_MIN_ES3) //too small loopBW, use the smallest BW
			{
				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_1G_LUT, 0, narrowBand, subband, downChirp, effFc);
			}
			else if (loopBW > LOOP_BW_MAX_ES3) //too big loopBW, use the largest possible
			{
				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_1G_LUT, NUM_ITEM_VCO_FILTER_LUT_ES3 - 1, narrowBand, subband, downChirp, effFc);
			}
			else //within LUT loopBW range.
			{
				//search for nearest loopBW in the table.
				loopBWInt = loopBW - ((int)loopBW % LOOP_BW_INC_ES3);
				index = (int)((loopBWInt - LOOP_BW_MIN_ES3) / LOOP_BW_INC_ES3);

				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_1G_LUT, index, narrowBand, subband, downChirp, effFc);
			}
		}
		else //2GHz bands
		{
			if (loopBW < LOOP_BW_MIN_ES3) //too small loopBW, use the smallest BW
			{
				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_2G_LUT, 0, narrowBand, subband, downChirp, effFc);
			}
			else if (loopBW > LOOP_BW_MAX_ES3) //too big loopBW, use the largest possible
			{
				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_2G_LUT, NUM_ITEM_VCO_FILTER_LUT_ES3 - 1, narrowBand, subband, downChirp, effFc);
			}
			else //within LUT loopBW range.
			{
				loopBWInt = loopBW - ((int)loopBW % LOOP_BW_INC_ES3);
				index = (int)((loopBWInt - LOOP_BW_MIN_ES3) / LOOP_BW_INC_ES3);

				hal_es3_cafc_VCO_Filter_Config(ProfileNum, CAFC_2G_LUT, index, narrowBand, subband, downChirp, effFc);
			}
		}

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cafc_VCOFreqMeasure(int subband, bool lowerBound, bool narrowBand, float * p_freqmesval, unsigned int countPeriod, uint8_t iVCOFine)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
//		uint32_t reg_val = 0x00;
		uint32_t ref_counter_val = 0;

		Nxp_Tef810x_Mod06_CpRegisterUnion_t				CPReg;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t		VCORegProfile;
		Nxp_Tef810x_Mod06_RefCntrInitUnion_t			VCORefCntr;
		Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t	FreqReadValue;
		Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t	DivideForce;
		Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t		CAFCFilter;
		Nxp_Tef810x_Mod06_FreqCounterStartUnion_t	CAFCFreqCountStrt;

		HAL_GERRCODE_INIT;

		//Force a divider to 27.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivideForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivideForce.bits_st.CtlForceDivider = 1;
		DivideForce.bits_st.CtlDivForce = 0x1B;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivideForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, &CAFCFilter.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//other settings are erased, not important in VCO frequency measurement
		if (lowerBound)
			//approx. 155mV
			CAFCFilter.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x12;
		else
			//approx. 945mV
			CAFCFilter.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x6E;

		CAFCFilter.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
		CAFCFilter.bits_st.CtlIbiasCp150USpiProfile0 = 0;
		CAFCFilter.bits_st.CtlCpSliceEnSpiProfile0 = 0;
		CAFCFilter.bits_st.CtlLpfIntEnSpiProfile0 = 0;
		CAFCFilter.bits_st.CtlLpfExtEnSpiProfile0 = 0;
		CAFCFilter.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
		//disconnect loop filter, set force vtune to value 12(~180mV) or 69(~900mV)
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, CAFCFilter.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//turn off the CP
		// this SPI setting is redundant, can be removed for timing optimization, since CtlCpSliceEnSpiProfile0 is set to 0 already.
		// here it is kept just for reference.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, &CPReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CPReg.bits_st.CtlCpEnSpi = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CPReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//select narrow/wide band, and user input subband number.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCORegProfile.bits_st.CtlVcoEnSpiProfile0 = 1;
		VCORegProfile.bits_st.CtlVcoIvcoFineSpiProfile0 = iVCOFine;
		VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband;
		VCORegProfile.bits_st.CtlVcoBandwidthSpiProfile0 = narrowBand ? 0 : 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, VCORegProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//program the reference counter value to input param
		ref_counter_val = countPeriod * 40; //us to clk cycles.


		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, &VCORefCntr.val_u32, NULL);

		VCORefCntr.bits_st.RefCountValue = ref_counter_val;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, VCORefCntr.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//change frequency counter trigger to SPI write to freq_start filed.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, &CAFCFreqCountStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CAFCFreqCountStrt.bits_st.EnableFuncSafetyFreqMea = 0;
		CAFCFreqCountStrt.bits_st.NumLsbbitsIgnored = 0;
		CAFCFreqCountStrt.bits_st.FreqStart = 0;

		glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, CAFCFreqCountStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//trigger one counter measurement
		CAFCFreqCountStrt.bits_st.FreqStart = 1;

		glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, CAFCFreqCountStrt.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_Tic();
		do
		{
			FreqReadValue.val_u32 = 0;
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//timeout
			if (glue_Toc() >= CAFC_FREQ_CNT_TIMEOUT_MS * 1000 * 1000)
			{
				DbgInfo("CAFC frequency counting failed: it didn't finish within %.2f ms...\n", CAFC_FREQ_CNT_TIMEOUT_MS);
				HAL_GEC_FUNEXIT(DOLPHINIC_EC_CAFC_FREQ_CNT_TIMEOUT);
			}
		} while (FreqReadValue.bits_st.DoneFlag == 0);

		FreqReadValue.val_u32 = 0;
		//read out the frequency counter.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//return the value in Hz
		if (p_freqmesval != NULL)
		{
			*p_freqmesval = ((float)FreqReadValue.bits_st.FreqCountValue / countPeriod * 27 * 2 * 3 * 1e6f);
		}

		return HAL_GERRCODE;
	}

#ifndef SB_BINARYSEARCH_ENABLE
	DolphinIC_rval_t hal_es3_cafc_VCOFreqCalibrate(bool narrowBand, uint8_t startSB, int numPoints)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		float fBegin = 0;
		float fEnd = 0;
		float BW = 0;
		int loopStart = 0;
		int loopStop;
//		const int numContextReg = 7;
		const uint16_t contextRegAddr[] = {
			NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16,
			NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16,
			NXP_TEF810X_MOD06_CP_REGISTER_U16,
			NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16,
			NXP_TEF810X_MOD06_REF_CNTR_INIT_U16,
			NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16,
			NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16 };

		uint32_t reg_val[7];
		uint32_t *pReg = reg_val;
		const uint16_t *pAddr = contextRegAddr;
		int loop0;
		int OTP_220_f76sub;
		uint8_t iVCOFineOTP76G = 0;

		Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t		CAFCFSMonLvlVco;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			TEChirpGlblCtrl;
		Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t		DivForce;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			VCORegisterProfile0;
		Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t		filterRegisterProfile0;

		HAL_GERRCODE_INIT;

		//compute proper loopStart and loopEnd for positive and negative numSteps input
		loopStop = startSB + numPoints;
		if (numPoints < 0)
		{
			loopStart = loopStop + 1;
			loopStop = startSB + 1;
			//saturate loopStart to 0 (non-negative)
			loopStart = (loopStart > 0) ? loopStart : 0;
		}
		else
		{
			//saturate loopStart to NUM_SUBBANDS_ES3
			loopStop = (loopStop <= NUM_SUBBANDS_ES3) ? loopStop : NUM_SUBBANDS_ES3;
		}


		//Save context.
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, *(pAddr++), pReg++, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//The below 4 local modification of registers will be restored by the above saved values in the end of this function.


		//disabled VCO mon level to avoid failure during calibration
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, &CAFCFSMonLvlVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CAFCFSMonLvlVco.bits_st.CtlLevelVcoAmpMonitorEnSpi = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, CAFCFSMonLvlVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//disconnect loop filter, disable CpSlice, force a constant vtune
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, &filterRegisterProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//force to approx. 155mV
		filterRegisterProfile0.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x12;
		filterRegisterProfile0.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
		filterRegisterProfile0.bits_st.CtlIbiasCp150USpiProfile0 = 0;
		filterRegisterProfile0.bits_st.CtlCpSliceEnSpiProfile0 = 0;
		filterRegisterProfile0.bits_st.CtlLpfIntEnSpiProfile0 = 0;
		filterRegisterProfile0.bits_st.CtlLpfExtEnSpiProfile0 = 0;
		filterRegisterProfile0.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
		//disconnect loop filter, set force vtune to value 12(~180mV) or 69(~900mV)
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, filterRegisterProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		// configure temporarily OTP value of subband number for 76GHz at 125C
		//parse the OTP value for 76GHz subband at 125C
		OTP_220_f76sub = (g_OTPShadowLUT_ES3[8] >> 9) & 0x7F;
		OTP_220_f76sub = hal_es3_bit_flip(OTP_220_f76sub, 7);
		DbgInfo("OTP stored subband for 76GHz at 125C is:%d\n", OTP_220_f76sub);

		//select narrow/wide band, and OTP subband number, enable VCO.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegisterProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCORegisterProfile0.bits_st.CtlVcoEnSpiProfile0 = 1;
		VCORegisterProfile0.bits_st.CtlVcoIvcoFineSpiProfile0 = 0x0; //temporarily set to 0, just soon after it will be calibrated.
		VCORegisterProfile0.bits_st.CtlVcoCoarseTuningSpiProfile0 = (OTP_220_f76sub - 20 >= 0) ? (OTP_220_f76sub - 20) : 0;
		VCORegisterProfile0.bits_st.CtlVcoBandwidthSpiProfile0 = narrowBand ? 0 : 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, VCORegisterProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Force timing engine to use Profile-0 for VCO cal
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &TEChirpGlblCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		TEChirpGlblCtrl.bits_st.ChirpEnable = 1;
		TEChirpGlblCtrl.bits_st.ChirpProfileSelect = 0;
		TEChirpGlblCtrl.bits_st.ChirpStart = 0;
		TEChirpGlblCtrl.bits_st.EnableProfileReset = 0;
		TEChirpGlblCtrl.bits_st.ProfileStayCountVal = 0;

		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, TEChirpGlblCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		// calibrate CAFC amplitude in open loop condition (prepared in code above)
		hal_es3_cafc_CalAmplitude(0);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegisterProfile0.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		iVCOFineOTP76G = VCORegisterProfile0.bits_st.CtlVcoIvcoFineSpiProfile0;
		DbgInfo("Calibrate iVCO is: 0x%x at subband:%d\n", iVCOFineOTP76G, VCORegisterProfile0.bits_st.CtlVcoCoarseTuningSpiProfile0);


		if (narrowBand)
		{
			//narrow bands
			for (loop0 = loopStop - 1; loop0 >= loopStart; loop0--)
			{
				hal_es3_cafc_VCOFreqMeasure(loop0, true, true, &fBegin, 10, iVCOFineOTP76G);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_cafc_VCOFreqMeasure(loop0, false, true, &fEnd, 10, iVCOFineOTP76G);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				BW = fEnd - fBegin;
				hal_es3_cafc_SetVCOTable(true, loop0, fBegin, fEnd, BW);
				//if (fBegin < 75 * 1e9)
					//break;
			}
		}
		else
		{
			//wide bands
			for (loop0 = loopStop - 1; loop0 >= loopStart; loop0--)
			{
				hal_es3_cafc_VCOFreqMeasure(loop0, true, false, &fBegin, 10, iVCOFineOTP76G);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				hal_es3_cafc_VCOFreqMeasure(loop0, false, false, &fEnd, 10, iVCOFineOTP76G);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				BW = fEnd - fBegin;
				hal_es3_cafc_SetVCOTable(false, loop0, fBegin, fEnd, BW);
			}
		}

		//pop context back.
		//restore VCO monitor levels
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_WriteCheck(TIMING_ENGINE_MODULE_ADDRESS, *(--pAddr), *(--pReg), NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//disable force divider
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivForce.bits_st.CtlForceDivider = 0;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	//get frequency table.
	DolphinIC_rval_t hal_es3_cafc_GetVCOTable(bool narrowTable, float fBegin[128], float fEnd[128], float BW[128])
	{
		const VCOTableItemES3_t *table;
		int loop0;
		HAL_GERRCODE_INIT;

		//choose a global VCO table

		if (narrowTable)
			table = VCOTableNBES3;
		else
			table = VCOTableWBES3;

		for (loop0 = 0; loop0 < NUM_SUBBANDS_ES3; loop0++)
		{
			fBegin[loop0] = table[loop0].fBegin;
			fEnd[loop0] = table[loop0].fEnd;
			BW[loop0] = table[loop0].BW;
		}

		return HAL_GERRCODE;
	}

	//set the frequnecy table.
	DolphinIC_rval_t hal_es3_cafc_SetVCOTable(bool narrowTable, int num, float fBegin, float fEnd, float BW)
	{
		VCOTableItemES3_t *table;
		HAL_GERRCODE_INIT;

		//choose a global VCO table

		if (narrowTable)
			table = VCOTableNBES3;
		else
			table = VCOTableWBES3;

		table[num].fBegin = fBegin;
		table[num].fEnd = fEnd;
		table[num].BW = BW;
		table[num].dirty = false;

		return HAL_GERRCODE;
	}
#endif

	DolphinIC_rval_t hal_es3_cafc_EnableLDO(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod06_DividerLdoRegisterUnion_t		DivLDO;
		Nxp_Tef810x_Mod06_VcoBufferLdoRegisterUnion_t	VCOBufferLDO;
		Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t		CPPFDLDO;

		HAL_GERRCODE_INIT;

		//turn on LDOs

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDER_LDO_REGISTER_U16, &DivLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivLDO.bits_st.CtlLdoDividerEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDER_LDO_REGISTER_U16, DivLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_BUFFER_LDO_REGISTER_U16, &VCOBufferLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOBufferLDO.bits_st.CtlLdoVcoEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_BUFFER_LDO_REGISTER_U16, VCOBufferLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16, &CPPFDLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CPPFDLDO.bits_st.CtlLdoCppfdEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16, CPPFDLDO.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}

	DolphinIC_rval_t hal_es3_cafc_EnableVCO(void)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t DivForce;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t VCOReg;
		Nxp_Tef810x_Mod06_FreqCounterStartUnion_t FreqCounterStart;

		HAL_GERRCODE_INIT;

		//To allow for two bit tolerance in the vco 480 clk
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, &FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FreqCounterStart.bits_st.NumLsbbitsIgnored = 3; //0b11, ignore 2 bits

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//cancel force divider
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivForce.bits_st.CtlForceDivider = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivForce.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Enable VCO in the end.

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoEnSpiProfile0 = 1;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.val_u32 = 0;
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoEnSpiProfile0 = 1;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.val_u32 = 0;
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoEnSpiProfile0 = 1;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.val_u32 = 0;
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoEnSpiProfile0 = 1;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//100us is good, here due to API restriction, min delay is 1ms.
		glue_Sleep(1);

		return HAL_GERRCODE;
	}

	//Assumes LDO of the ATBs are powered up
	DolphinIC_rval_t hal_es3_cafc_CalAmplitude(uint8_t nprofile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint16_t low_amp_val = 0x00;
//		uint32_t cafc_amp = 0x00;
		uint32_t VCO_REG_PROFILE = 0x0;
//		uint32_t ATB_readout = 0x00;
		uint32_t currentIVCOVal;
//		int ATB_signed = 0x00;
//		int diff;
//		int indx;
		bool fT;

		//Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t	CAFCTestErrorFlags;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		contextSaveChirpGlobalCtrl;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		ChirpGlobalCtrl;
		Nxp_Tef810x_Mod06_CalLoDetUnion_t				CalLODet;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t		VCOReg;
//		Nxp_Tef810x_Mod06_AtbUnion_t					CAFCATBReg;
//		Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t			ATBEnReg;
//		Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t		ADCBuf1Ctrl;
//		Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t	FSMonLevelVCO;
//		Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t		ATBData;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t FuncReset;
//		Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t	testErrorFlag;
//		Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t		CCAtbAcEn;
//		Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t		ATBConfg;
//		Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t		ATBCtrl;
		Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t		ChirpErrorMonReg;
		Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t		SaveStateChirpErrorMonReg;

		HAL_GERRCODE_INIT;

		//Set High flag always monitoring
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, &ChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SaveStateChirpErrorMonReg.val_u32 = ChirpErrorMonReg.val_u32;
		ChirpErrorMonReg.bits_st.LevelHighErrorFlagChirpMon = 1;
		ChirpErrorMonReg.bits_st.LevelLowErrorFlagChirpMon = 1;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, ChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//save the current status of TE CHIRP_GLOBAL_CONTROL register
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &contextSaveChirpGlobalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//new configuration of TE for CAFC amplitude calibration
		ChirpGlobalCtrl.val_u32 = contextSaveChirpGlobalCtrl.val_u32;

		switch (nprofile)
		{
		case 1:
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
			ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 1;
			break;
		case 2:
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
			ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 2;
			break;
		case 3:
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
			ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 3;
			break;
		default:
			VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
			ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 0;
		}

		fT = true;
		//enable rms detector and choose output as monitoring value (set bits 12 and 16)

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, &CalLODet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CalLODet.bits_st.CtlRmsEnSpi = 1;
		CalLODet.bits_st.CtlRmsMeasInOutSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, CalLODet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currentIVCOVal = 0;

		//select the profile from the timing engine
		ChirpGlobalCtrl.bits_st.ChirpEnable = 1;
		ChirpGlobalCtrl.bits_st.EnableProfileReset = 0;

		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//program the minimum value to the VCO fine current
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//issue an error reset
		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//read-out local error flags to see level warnings
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ChirpErrorFlagMaskedStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//continue trying if we don't see any high or max error
		while (ChirpErrorFlagMaskedStatus.bits_st.LevelHighErrorFlagChirpSync == 0)
		{
			//find the minimum value that does not trigger any level errors
			if ((ChirpErrorFlagMaskedStatus.bits_st.LevelLowErrorFlagChirpSync == 0) && \
				(fT == true))
			{
				low_amp_val = currentIVCOVal;
				fT = false;
			}

			//read and store the current iVCO value
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			currentIVCOVal = VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0;

			// maximum iVCO value check
			if (currentIVCOVal >= 0x1F)
				break;

			//increase iVCO current and find the minimum value that triggers a high error
			currentIVCOVal += 1;
			VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = currentIVCOVal;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//Issue a reset from ISM and check if there are no errors
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//readout test-error flag
			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ChirpErrorFlagMaskedStatus.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		//calculate the middle point and set the current
		currentIVCOVal = (uint32_t)((currentIVCOVal + low_amp_val - 1) / 2);
		VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = currentIVCOVal;

		DbgInfo("CtlVcoIvcoFineSpiProfile is set to:0x%x\n", currentIVCOVal);
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		//reload the pre-saved status of TE CHIRP_GLOBAL_CONTROL register
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, contextSaveChirpGlobalCtrl.val_u32, NULL);

		//issue a functional reset to CAFC
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FuncReset.bits_st.FnResetChirp = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		FuncReset.bits_st.FnResetChirp = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Issue a reset from ISM and check if there are no errors
		hal_es3_ISM_SetMCUReset();
		
		//Read out local error register to confirm no errors

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ChirpErrorFlagMaskedStatus.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Restore original settings for Chirp Monitoring
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, SaveStateChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if ((ChirpErrorFlagMaskedStatus.bits_st.LevelHighErrorFlagChirpSync != 0) && \
			(ChirpErrorFlagMaskedStatus.bits_st.LevelLowErrorFlagChirpSync != 0))
		{
			DbgInfo("Chirp Amplitude Calibration Failed! ISM Chirp Err Flag Raw: 0x%x \n", ChirpErrorFlagMaskedStatus.bits_st);
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
		}
		else
		{
			DbgInfo("Chirp Amplitude Calibration Succesfull!  \n");
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		return HAL_GERRCODE;
	}

	//Assumes LDO of the ATBs are powered up
	DolphinIC_rval_t hal_es3_cafc_CalAmplitude_InjectRecovery(uint8_t nprofile)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		uint16_t low_amp_val = 0x00;
//		uint32_t cafc_amp = 0x00;
		uint32_t VCO_REG_PROFILE = 0x0;
//		uint32_t ATB_readout = 0x00;
		uint32_t currentIVCOVal;
//		int ATB_signed = 0x00;
//		int diff;
//		int indx;
//		bool fT;

		//Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t	CAFCTestErrorFlags;
		Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t	ISMChirpFlagMasked;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		contextSaveChirpGlobalCtrl;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t		ChirpGlobalCtrl;
		Nxp_Tef810x_Mod06_CalLoDetUnion_t				CalLODet;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t		VCOReg;
//		Nxp_Tef810x_Mod06_AtbUnion_t					CAFCATBReg;
//		Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t			ATBEnReg;
//		Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t		ADCBuf1Ctrl;
//		Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t	FSMonLevelVCO;
//		Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t		ATBData;
		Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t FuncReset;
//		Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t	testErrorFlag;
//		Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t		CCAtbAcEn;
//		Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t		ATBConfg;
//		Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t		ATBCtrl;
		Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t		ChirpErrorMonReg;
		Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t		SaveStateChirpErrorMonReg;

		HAL_GERRCODE_INIT;

		//Disable Max flag always monitoring
		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, &ChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		SaveStateChirpErrorMonReg.val_u32 = ChirpErrorMonReg.val_u32;
		ChirpErrorMonReg.bits_st.LevelMaxErrorFlagChirpMon = 0;
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, ChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_SetMCUReset(); //Reset ISM in case any previous acumulated errors

								   //save the current status of TE CHIRP_GLOBAL_CONTROL register

		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &contextSaveChirpGlobalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//new configuration of TE for CAFC amplitude calibration

		ChirpGlobalCtrl.val_u32 = contextSaveChirpGlobalCtrl.val_u32;

		switch (nprofile)
		{
			case 1:
			{
				VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16;
				ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 1;
				break;
			}
			case 2:
			{
				VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16;
				ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 2;
				break;
			}
			case 3:
			{
				VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16;
				ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 3;
				break;
			}
			default:
			{
				VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
				ChirpGlobalCtrl.bits_st.ChirpProfileSelect = 0;
			}
		}

		//enable rms detector and choose output as monitoring value (set bits 12 and 16)

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, &CalLODet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		CalLODet.bits_st.CtlRmsEnSpi = 1;
		CalLODet.bits_st.CtlRmsMeasInOutSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CAL_LO_DET_U16, CalLODet.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currentIVCOVal = 0;

		//select the profile from the timing engine
		ChirpGlobalCtrl.bits_st.ChirpEnable = 1;
		ChirpGlobalCtrl.bits_st.EnableProfileReset = 0;

		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalCtrl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//hal_es3_sctrl_CWMode(true, true);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//program the minimum value to the VCO fine current

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		do {

			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// maximum iVCO value check
			if (currentIVCOVal >= 0x1F)
				break;

			currentIVCOVal += 1;

			VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = currentIVCOVal;
			low_amp_val = currentIVCOVal;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ISMChirpFlagMasked.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		} while (ISMChirpFlagMasked.bits_st.LevelHighErrorFlagChirpSync == 0);

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = 0x1f;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		do {

			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			// minimum iVCO value check
			if (currentIVCOVal <= 0)
				break;

			currentIVCOVal -= 1;
			VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = currentIVCOVal;
			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_ISM_SetMCUReset();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			hal_es3_teng_StartChirp();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			chip_TE_WaitForReady();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ISMChirpFlagMasked.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		} while (ISMChirpFlagMasked.bits_st.LevelLowErrorFlagChirpSync == 0);

		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, &VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		currentIVCOVal = (uint32_t)(((currentIVCOVal - 1) + (low_amp_val - 1)) / 2);
		VCOReg.bits_st.CtlVcoIvcoFineSpiProfile0 = currentIVCOVal;

		DbgInfo("CtlVcoIvcoFineSpiProfile is set to:0x%x\n", currentIVCOVal);
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCOReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);



		//reload the pre-saved status of TE CHIRP_GLOBAL_CONTROL register
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, contextSaveChirpGlobalCtrl.val_u32, NULL);

		//issue a functional reset to CAFC
		glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, &FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		FuncReset.bits_st.FnResetChirp = 0;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		FuncReset.bits_st.FnResetChirp = 1;
		glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16, FuncReset.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Issue a reset from ISM and check if there are no errors
		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		chip_TE_WaitForReady();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16, &ISMChirpFlagMasked.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//Restore original settings for Chirp Monitoring
		glue_reg_WriteCheck(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16, SaveStateChirpErrorMonReg.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if ((ISMChirpFlagMasked.bits_st.LevelHighErrorFlagChirpSync != 0) && \
			(ISMChirpFlagMasked.bits_st.LevelMaxErrorFlagChirp != 0) && \
			(ISMChirpFlagMasked.bits_st.LevelLowErrorFlagChirpSync != 0) && \
			(ISMChirpFlagMasked.bits_st.LevelMinErrorFlagChirp != 0))
		{
			DbgInfo("Chirp Amplitude Calibration Failed! ISM Chirp Err Flag Masked: 0x%x \n", ISMChirpFlagMasked.bits_st);
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CALLFAILED);
		}
		else
		{
			DbgInfo("Chirp Amplitude Calibration Succesfull!  \n");
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		return HAL_GERRCODE;
	}

	//double *effFc, double effBW, double tSettle, double tSample, double tJumpback, double *fStart, double *fStop, bool downChirp, double *usedBW, bool narrowBand, uint8_t *subBand

	DolphinIC_rval_t hal_es3_cafc_SubBandSelectBinarySearch(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand)
	{
		///* DECLARE LOCAL VARIABLES HERE *///
		// success flags
		bool fStartSearchSuccess = false;
		bool BWCheckSuccess = false;

		float fBegin;
		float fEnd;
		float slopeSign;
		float fSlope;
		float tmpFStart;
		float tmpFStop;
		float tmpUsedBW;
		float FLow;
		float FHigh;

		int loop0;

		uint8_t lowerBound;
		uint8_t upperBound = NUM_SUBBANDS_ES3;
		uint8_t cursor;
		uint8_t iterations = 0;

		//use profile 0 always, since this function does not program subband in profiles in the end.
		const uint16_t VCO_REG_PROFILE = NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16;
		//number of context registers to save
		const int numContextReg = 7;
		const uint16_t contextModAddr[] = {
			TIMING_ENGINE_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS,
			CHIRP_AFC_MODULE_ADDRESS };
		const uint16_t contextRegAddr[] = {
			NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16,
			NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16,
			NXP_TEF810X_MOD06_CP_REGISTER_U16,
			NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16,
			NXP_TEF810X_MOD06_REF_CNTR_INIT_U16,
			NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16,
			NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16 };
		//backup space
		uint32_t backupStorage[] = { 0,0,0,0,0,0,0 };

		uint32_t *pReg = backupStorage;
		const uint16_t *pAddr = contextRegAddr;
		const uint16_t *pMod = contextModAddr;

		uint32_t OTP_220_f76sub;

		Nxp_Tef810x_Mod06_RefCntrInitUnion_t VCORefCntr;
		Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t VCORegProfile;
		Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t FreqReadValue;
		Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t FuncsafeMonLevelVco;
		Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl;
		Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t DivideForceRegister;
		Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t FilterRegisterProfile;
		Nxp_Tef810x_Mod06_CpRegisterUnion_t CpRegister;
		Nxp_Tef810x_Mod06_FreqCounterStartUnion_t FreqCounterStart;


		HAL_GERRCODE_INIT;


		//sign of the slope according to downChirp
		slopeSign = downChirp ? -1 : 1;
		//chirp slope
		fSlope = slopeSign * effBW / tSample;

		//temp frequency parameters
		//depending on downChirp, FStart can be lower or higher than FStop.
		tmpFStart = *effFc - slopeSign * effBW / 2 - tSettle * fSlope;
		tmpFStop = *effFc + slopeSign * effBW / 2 + tJumpback * fSlope;
		tmpUsedBW = fabsf(tmpFStop - tmpFStart);

		//work with low/high frequency rather than tmpFStart and tmpFStop, this simplifies the implementation to support both upchirp and downchirp.
		FLow = downChirp ? tmpFStop : tmpFStart;
		FHigh = downChirp ? tmpFStart : tmpFStop;

		//subband boundaries for current measurement
		fBegin = 0;
		fEnd = 0;
		cursor = 0;
		lowerBound = 0;



		//save context registers in backup space
		for (loop0 = 0; loop0 < numContextReg; loop0++)
		{
			//Save context.
			glue_reg_Read(*(pMod++), *(pAddr++), pReg++, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		//disabled VCO mon level to avoid failure during calibration
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, &FuncsafeMonLevelVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		FuncsafeMonLevelVco.bits_st.CtlLevelVcoAmpMonitorEnSpi = 0;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, FuncsafeMonLevelVco.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//disconnect loop filter, set force vtune to value 12(~180mV) or 69(~900mV)
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, &FilterRegisterProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		FilterRegisterProfile.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
		FilterRegisterProfile.bits_st.CtlCpSliceEnSpiProfile0 = 0;
		FilterRegisterProfile.bits_st.CtlIbiasCp150USpiProfile0 = 0;
		FilterRegisterProfile.bits_st.CtlLpfExtEnSpiProfile0 = 0;
		FilterRegisterProfile.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
		FilterRegisterProfile.bits_st.CtlLpfIntEnSpiProfile0 = 0;
		FilterRegisterProfile.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x12;


		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, FilterRegisterProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//Force timing engine to use Profile-0 for VCO cal
		glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &ChirpGlobalControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		ChirpGlobalControl.bits_st.ChirpEnable = 0x1;
		ChirpGlobalControl.bits_st.ChirpProfileSelect = 0;
		ChirpGlobalControl.bits_st.ChirpStart = 0;
		ChirpGlobalControl.bits_st.EnableProfileReset = 0;
		ChirpGlobalControl.bits_st.ProfileStayCountVal = 0;
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, ChirpGlobalControl.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//parse the OTP value for 76GHz subband at 125C
		OTP_220_f76sub = (g_OTPShadowLUT_ES3[8] >> 9) & 0x7F;
		OTP_220_f76sub = hal_es3_bit_flip(OTP_220_f76sub, 7);

		//reassign search lowerBound if lowerBound is high enough
		if (OTP_220_f76sub - SB_MARGIN_ES3 > 0)
			lowerBound = OTP_220_f76sub - SB_MARGIN_ES3;

		// init cursor value for binary search
		cursor = (lowerBound + upperBound) / 2;


		//Force a divider to 27.
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivideForceRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivideForceRegister.bits_st.CtlDivForce = 0x1B;
		DivideForceRegister.bits_st.CtlEnRfDivSpi = 0;
		DivideForceRegister.bits_st.CtlForceDivider = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivideForceRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//disable charge pump
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, &CpRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		CpRegister.bits_st.CtlCpEnSpi = 0;
		CpRegister.bits_st.CtlCpForceDnSpi = 0;
		CpRegister.bits_st.CtlCpForceUpSpi = 0;
		CpRegister.bits_st.CtlCpReplicaBiasEnSpi = 1;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CpRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		//program the reference counter value to FREQ_CNT_PERIOD_ES3 us
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, &VCORefCntr.val_u32, NULL);

		VCORefCntr.bits_st.RefCountValue = FREQ_CNT_PERIOD_ES3 * 40; //us to clk cycles.
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, VCORefCntr.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//compose value for VCO_REGISTER_PROFILE to use in following freq measurements
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		VCORegProfile.bits_st.CtlVcoEnSpiProfile0 = 1;
		VCORegProfile.bits_st.CtlVcoIvcoFineSpiProfile0 = 0x0;
		VCORegProfile.bits_st.CtlVcoBandwidthSpiProfile0 = narrowBand ? 0 : 1;
		VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = (OTP_220_f76sub - 20 >= 0) ? (OTP_220_f76sub - 20) : 0;
		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, VCORegProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);


		// calibrate CAFC amplitude in open loop condition (prepared in code above)
		// Here, this is done every time when hal_es3_cafc_SubBandSelectBinarySearch is called, but can be done only once. 
		hal_es3_cafc_CalAmplitude(0);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegProfile.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DbgInfo("Calibrate iVCO is: 0x%x at subband:%d\n", VCORegProfile.bits_st.CtlVcoIvcoFineSpiProfile0, VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0);


#ifdef DOLPHIN_CFG_HOST_S32R274
		//In faster hosts it is necessary to wait ~500us after enabling VCO
		glue_Sleep(1);
#endif

		do {
			iterations += 1;
			VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = cursor;

			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, VCORegProfile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//trigger frequency counter measurement
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, &FreqCounterStart.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			FreqCounterStart.bits_st.EnableFuncSafetyFreqMea = 0;
			FreqCounterStart.bits_st.FreqStart = 1;
			FreqCounterStart.bits_st.NumLsbbitsIgnored = 0;

			glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			glue_Tic();
			do
			{
				FreqReadValue.val_u32 = 0;
				glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

				//timeout
				if (glue_Toc() >= CAFC_FREQ_CNT_TIMEOUT_MS * 1000 * 1000)
				{
					DbgInfo("CAFC frequency counting failed: it didn't finish within %.2f ms...\n", CAFC_FREQ_CNT_TIMEOUT_MS);
					HAL_GEC_FUNEXIT(DOLPHINIC_EC_CAFC_FREQ_CNT_TIMEOUT);
				}
			} while (FreqReadValue.bits_st.DoneFlag == 0);

			fBegin = ((float)FreqReadValue.bits_st.FreqCountValue / FREQ_CNT_PERIOD_ES3 * 27 * 2 * 3 * 1e6f);

			if (FLow > fBegin)
			{
				if (FLow <= fBegin + 150e6)
				{
					//search for fStart succeed, program cursor to subband field
					VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = cursor;
					glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, VCO_REG_PROFILE, VCORegProfile.val_u32, NULL);
					HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

					fStartSearchSuccess = true;
					break;
				}
				else lowerBound = cursor;
			}
			else upperBound = cursor;

			cursor = (lowerBound + upperBound) / 2;
		} while ((upperBound != cursor) && (lowerBound != cursor));

		//search for tempFStart is successful, then continue to check for if the found SB can suit usedBW
		if (fStartSearchSuccess)
		{
			//disconnect loop filter, set force vtune to value 69(~900mV)
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, &FilterRegisterProfile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			FilterRegisterProfile.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
			FilterRegisterProfile.bits_st.CtlCpSliceEnSpiProfile0 = 0;
			FilterRegisterProfile.bits_st.CtlIbiasCp150USpiProfile0 = 0;
			FilterRegisterProfile.bits_st.CtlLpfExtEnSpiProfile0 = 1;
			FilterRegisterProfile.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
			FilterRegisterProfile.bits_st.CtlLpfIntEnSpiProfile0 = 0;
			FilterRegisterProfile.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x69;


			glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16, FilterRegisterProfile.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			//trigger frequency counter measurement
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, &FreqCounterStart.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			FreqCounterStart.bits_st.EnableFuncSafetyFreqMea = 0;
			FreqCounterStart.bits_st.FreqStart = 1;
			FreqCounterStart.bits_st.NumLsbbitsIgnored = 0;

			glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, FreqCounterStart.val_u32, NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

			do
			{
				FreqReadValue.val_u32 = 0;
				glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			} while (FreqReadValue.bits_st.DoneFlag == 0);

			//fEnd of selected subband
			fEnd = ((float)FreqReadValue.bits_st.FreqCountValue / FREQ_CNT_PERIOD_ES3 * 27 * 2 * 3 * 1e6f);

			if (FHigh < fEnd)
				BWCheckSuccess = true;
		}

		//disable force divider
		//glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, 0x00000000, NULL);
		//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivideForceRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		DivideForceRegister.bits_st.CtlDivForce = 0;
		DivideForceRegister.bits_st.CtlEnRfDivSpi = 0;
		DivideForceRegister.bits_st.CtlForceDivider = 0;

		glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivideForceRegister.val_u32, NULL);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//restore context registers
		for (loop0 = 0; loop0 < numContextReg; loop0++)
		{
			glue_reg_WriteCheck(*(--pMod), *(--pAddr), *(--pReg), NULL);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}

		// assign outputs
		if (fStartSearchSuccess && BWCheckSuccess)
		{
			*subBand = cursor;
			*fStart = tmpFStart;
			*fStop = tmpFStop;
			*usedBW = tmpUsedBW;
			DbgInfo("Selected subband is:%d, fStart:%f, fStop:%f,usedBW:%f, 26GFreq:%f\n", *subBand, *fStart, *fStop, *usedBW, (*fStart + (*usedBW) / 2) / 3);
			DbgInfo("Subband fBegin:%f, fEnd:%f\n", fBegin, fEnd);
		}
		else
		{
			DbgInfo("Binary search failed at subband:%d\n", cursor);
			*subBand = -1;
			*fStart = -1;
			*fStop = -1;
			*usedBW = -1;
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_SUBBANDSELECT_BS_FAIL);
		}

		return HAL_GERRCODE;
	}

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //DOLPHIN_CFG_ES3
