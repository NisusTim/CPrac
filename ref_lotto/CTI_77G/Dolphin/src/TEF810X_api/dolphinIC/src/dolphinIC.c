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

/*
*
* @file dolphinIC.c
*
* @author
*
* @ver v5.3.0 
*
* @date 04/02/2016
*
* @brief dolphinIC Top level API.
*
*
******************************************************************************/

#include <dolphinIC.h>

//Hardware Abstraction Layer includes

#ifdef DOLPHIN_CFG_ES2
#include <hal_es2_ctrl.h>
#include "hal_es2_rshd.h"
#include "hal_es2.h"
#endif

#ifdef DOLPHIN_CFG_ES3
#include <hal_es3_ctrl.h>
#include <hal_es3_rshd.h>
#include <hal_es3.h>
#include <es3/NXP_TEF810X_CentralControl.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

//global variable 
//global variable of Dolphin error codes
volatile int32_t g_halerrcode;
//chip mask version
uint8_t chipMaskVersion = 0;

//Chip mask version independent API!
DolphinIC_rval_t chip_CC_GetMaskVersion(uint8_t *MaskVersion)
{
	uint32_t ModuleID;
	uint8_t Major;
	uint8_t Minor;

	HAL_GERRCODE_INIT;

	//This is an exception to use numeric value of register addr and module addr
	//to make it chip mask version independent!
	//It is forbidden to use numeric addr in any other place!!!
	glue_reg_Read(0x00, 0xFFC, &ModuleID, NULL);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	//This is an exception to use numeric value of bit field position.
	//This is fobidden in any other place!!
	Major = (ModuleID >> 12) & 0xF;
	Minor = (ModuleID >> 8) & 0xF;

	if (Major == 1)
	{
		*MaskVersion = 1;
	}
	else if (Major == 2)
	{
		if (Minor == 2)
		{
			*MaskVersion = 2;
		}
		else if (Minor == 3)
		{
			*MaskVersion = 3;
		}
		else
		{
			DbgInfo("Illegal value for Minor version\n");
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_CANNOTGETMASKVERSION);
		}
	}
	else
	{
		DbgInfo("Illegal value for Major version\n");
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_CANNOTGETMASKVERSION);
	}

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_Init(int32_t modeSelect, uint8_t deci, uint32_t IP_PON_Mask)
{
	HAL_GERRCODE_INIT;

	DbgInfo("%s Enter ...\n", __FUNCTION__);

	/*----------------------------------------------------------------------------*/
	/*--------ChipMaskVersion and Master/Slave Independent Section: START---------*/
	/*----------------------------------------------------------------------------*/

	// judge if only 1 chirp variant MARCO or both MARCOs are enabled
	// if both are enabled, use es3 version (anyway, in this section, they are the same)
#ifdef DOLPHIN_CFG_ES2
#ifdef DOLPHIN_CFG_ES3
	//FSM v2.1 section 6.9.3.1 - Application reset
	hal_es3_ISM_Init_Act_1();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT1FAIL);

#ifdef DOLPHIN_CFG_HOST_OPALKELLY
	//FSM v2.1 section 6.9.3.2 - SPI interface integrity check (SPI Loopback Test)
	hal_es3_ISM_Init_Act_2();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT2FAIL);
#endif

	//FSM v2.1 section 6.9.3.3 - SPI access check (scratch register)
	hal_es3_ISM_Init_Act_3();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT3FAIL);
#else
	//FSM v2.1 section 6.9.3.1 - Application reset
	hal_es2_ISM_Init_Act_1();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT1FAIL);

#ifdef DOLPHIN_CFG_HOST_OPALKELLY
	//FSM v2.1 section 6.9.3.2 - SPI interface integrity check (SPI Loopback Test)
	hal_es2_ISM_Init_Act_2();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT2FAIL);
#endif

	//FSM v2.1 section 6.9.3.3 - SPI access check (scratch register)
	hal_es2_ISM_Init_Act_3();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT3FAIL);
#endif
#else 
#ifdef DOLPHIN_CFG_ES3
	//FSM v2.1 section 6.9.3.1 - Application reset
	hal_es3_ISM_Init_Act_1();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT1FAIL);

#ifdef DOLPHIN_CFG_HOST_OPALKELLY
	//FSM v2.1 section 6.9.3.2 - SPI interface integrity check (SPI Loopback Test)
	hal_es3_ISM_Init_Act_2();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT2FAIL);
#endif

	//FSM v2.1 section 6.9.3.3 - SPI access check (scratch register)
	hal_es3_ISM_Init_Act_3();
	HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT3FAIL);
#else
	DbgInfo("No DOLPHIN_CFG is defined! API cannot work and will exit");
	HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
#endif
#endif
	/*----------------------------------------------------------------------------*/
	/*--------ChipMaskVersion and Master/Slave Independent Section: END-----------*/
	/*----------------------------------------------------------------------------*/


	/*--------some more checks----------*/
//get mask version for later use
	chip_CC_GetMaskVersion(&chipMaskVersion);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	//check if a ES1 chip is wrongly used
	if (chipMaskVersion == 1)
	{
		DbgInfo("A ES1 chip is detected! This API does not support ES1!\n");
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}

	//if only a single CFG is defined, check if the correct chip is used.
#ifdef DOLPHIN_CFG_ES2
#ifndef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		DbgInfo("Only DOLPHIN_CFG_ES2 is defined but an ES3 chip is detected!\n");
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif
#endif

#ifdef DOLPHIN_CFG_ES3
#ifndef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		DbgInfo("Only DOLPHIN_CFG_ES3 is defined but an ES2 chip is detected!\n");
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif
#endif


	/*----------------------------------------------------------------------------*/
	/*--------ChipMaskVersion and Master/Slave Dependent Section: START-----------*/
	/*----------------------------------------------------------------------------*/
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_rshd_Init();

		//FSM v2.1 section 6.9.3.4 - OTP Read and OTP data integrity check
		hal_es2_ISM_Init_Act_4();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT4FAIL);

		//FSM v2.1 section 6.9.3.5 - Main LDO Switching
		hal_es2_ISM_Init_Act_5();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT5FAIL);

		//FSM v2.1 section 6.9.3.6 - Configure global bias
		hal_es2_ISM_Init_Act_6();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT6FAIL);

		//FSM v2.1 section 6.9.3.7 - Configure local LDOs
		hal_es2_ISM_Init_Act_7(modeSelect);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT7FAIL);

		//FSM v2.1 section 6.9.3.8 - Enable clock and release reset
		hal_es2_ISM_Init_Act_8();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT8FAIL);

		//FSM v2.1 section 6.9.3.9 - IC Calibration
		hal_es2_ISM_Init_Act_9();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT9FAIL);

		//FSM v2.1 section 6.9.3.10 - Configure local bias settings
		hal_es2_ISM_Init_Act_10();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT10FAIL);

		//FSM v2.1 section 6.9.3.11 - Configure master clock
		hal_es2_ISM_Init_Act_11(modeSelect);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT11FAIL);

		//FSM v2.1 section 6.9.3.12 - Module power up (all IPs)
		hal_es2_ISM_Init_Act_12();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT12FAIL);

		//FSM v2.1 section 6.9.3.13 - Configure ADC
		hal_es2_ISM_Init_Act_13();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT13FAIL);

		//FSM v2.1 section 6.9.3.14 - Safety sensor configuration
		hal_es2_ISM_Init_Act_14();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT14FAIL);

		//FSM v2.1 section 6.9.3.15 - Interface toggle test
		hal_es2_ISM_Init_Act_15();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT15FAIL);

		//FSM v2.1 section 6.9.3.16 - Data interface test
		hal_es2_ISM_Init_Act_16(modeSelect, deci);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT16FAIL);

		//FSM v2.1 section 6.9.3.17 - ISM FIT Test (ISM Integrity Check)
		hal_es2_ISM_Init_Act_17(modeSelect);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT17FAIL);
	}
#endif

	// API support for master slave configuration is only implemented for ES3!
#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_rshd_Init();

		//FSM v2.1 section 6.9.3.4 - OTP Read and OTP data integrity check
		hal_es3_ISM_Init_Act_4();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT4FAIL);

		//FSM v2.1 section 6.9.3.5 - Main LDO Switching
		hal_es3_ISM_Init_Act_5(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT5FAIL);

		//FSM v2.1 section 6.9.3.6 - Configure global bias
		hal_es3_ISM_Init_Act_6(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT6FAIL);

		//FSM v2.1 section 6.9.3.7 - Configure local LDOs
		hal_es3_ISM_Init_Act_7(modeSelect, IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT7FAIL);

		//FSM v2.1 section 6.9.3.8 - Enable clock and release reset and func reset
		hal_es3_ISM_Init_Act_8(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT8FAIL);

		//FSM v2.1 section 6.9.3.9 - IC Calibration
		hal_es3_ISM_Init_Act_9(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT9FAIL);

		//FSM v2.1 section 6.9.3.10 - Configure local bias settings
		hal_es3_ISM_Init_Act_10();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT10FAIL);

		//FSM v2.1 section 6.9.3.11 - Configure master clock
		hal_es3_ISM_Init_Act_11(modeSelect);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT11FAIL);

		//FSM v2.1 section 6.9.3.12 - Module power up (all IPs)
		hal_es3_ISM_Init_Act_12(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT12FAIL);

		//FSM v2.1 section 6.9.3.13 - Configure ADC
		hal_es3_ISM_Init_Act_13();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT13FAIL);

		//FSM v2.1 section 6.9.3.14 - Safety sensor configuration
		hal_es3_ISM_Init_Act_14(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT14FAIL);

		//FSM v2.1 section 6.9.3.15 - Interface toggle test
		hal_es3_ISM_Init_Act_15(IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT15FAIL);

		//FSM v2.1 section 6.9.3.16 - Data interface test
		hal_es3_ISM_Init_Act_16(modeSelect, deci, IP_PON_Mask);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT16FAIL);

		//FSM v2.1 section 6.9.3.17 - ISM FIT Test (ISM Integrity Check)
		hal_es3_ISM_Init_Act_17(modeSelect);
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT17FAIL);

		//FSM v2.1 section 6.9.3.xx - ISM GLDO SNS CHECK 
		hal_es3_ISM_Init_Act_18();
		HAL_GEC_CHKFUNEXIT(DOLPHINIC_EC_INITACT18FAIL);

	}

#endif
	/*----------------------------------------------------------------------------*/
	/*--------ChipMaskVersion and Master/Slave Dependent Section: END  -----------*/
	/*----------------------------------------------------------------------------*/
	DbgInfo("System is properly initialized !!! \n");

	return HAL_GERRCODE;
}

/*----------------------------------------------------------------------------*/
/*--------RFBIST Test assumes that only profile3 is used for this purpose  ---*/
/*----------------------------------------------------------------------------*/


DolphinIC_rval_t chip_ISM_RFBIST()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion==2)
	{
		hal_es2_ISM_RFBIST_Static_config();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es2_ISM_RFBIST_LnaTest();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es2_ISM_RFBIST_MixerTest();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es2_ISM_Recover_RfBist_changes();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_RFBIST_Static_config();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_sctrl_ZeroRamp(0x3);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_RFBIST_LnaTest();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_RFBIST_MixerTest();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_ISM_Recover_RfBist_changes();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_CalibrateAmplitude(uint8_t profile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion==2)
	{
		hal_es2_atb_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es2_cafc_CalAmplitude(false, 480, profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_CalAmplitude(profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif
	
	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_CalibrateAmplitude_InjectRecovery(uint8_t profile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_CalAmplitude_InjectRecovery(profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_EnableVCO()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cafc_EnableVCO();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_EnableVCO();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

int chip_CTRL_SubBandSelect(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand)
{
	//this is only for interfacing ES2 API with double types (ES3 has float type only)
#ifdef DOLPHIN_CFG_ES2
	double effFcT = *effFc;
	double fStartT = *fStart;
	double fStopT = *fStop;
	double usedBWT = *usedBW;
#endif

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		//subband selection algorithm for ES1
		int ret = hal_es2_ctrl_SelectSubBand(&effFcT, effBW, tSettle, tSample, tJumpback, &fStartT, &fStopT, downChirp, &usedBWT, narrowBand, subBand);

		//returning float from double
		*effFc = (float)effFcT;
		*fStart = (float)fStartT;
		*fStop = (float)fStopT;
		*usedBW = (float)usedBWT;

		return ret;
#else
		return -1;//TODO: moved to stardard Error codes
#endif
	}
#endif


#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		//subband selection algorithm for ES1
		return hal_es3_ctrl_SelectSubBand(effFc, effBW, tSettle, tSample, tJumpback, fStart, fStop, downChirp, usedBW, narrowBand, subBand);
#else
		return -1;//TODO: moved to stardard Error codes
#endif
	}
#endif

//default
	return -1;
}

DolphinIC_rval_t chip_CAFC_GetVCOTable(bool narrowTable, float *fBegin, float *fEnd, float *BW)
{
	//this is only for interfacing ES2 API with double types (ES3 has float type only)
#ifdef DOLPHIN_CFG_ES2
	double fBeginT[128] = { 0 };
	double fEndT[128] = { 0 };
	double BWT[128] = { 0 };
#endif

	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es2_cafc_GetVCOTable(narrowTable, fBeginT, fEndT, BWT);

		// return float array from double array
		for (int loop0 = 0; loop0 < 128; loop0++)
		{
			fBegin[loop0] = (float)fBeginT[loop0];
			fEnd[loop0] = (float)fEndT[loop0];
			BW[loop0] = (float)BWT[loop0];
		}
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es3_cafc_GetVCOTable(narrowTable, fBegin, fEnd, BW);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_SetVCOTable(bool narrowTable, int num, float fBegin, float fEnd, float BW)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es2_cafc_SetVCOTable(narrowTable, num, fBegin, fEnd, BW);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if(chipMaskVersion == 3)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es3_cafc_SetVCOTable(narrowTable, num, fBegin, fEnd, BW);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_IPClockEnable(bool Enable, uint32_t modlist)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// enable clock ...
		hal_es2_cctrl_SetPonClkRst(1, Enable, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		// enable clock ...
		hal_es3_cctrl_SetPonClkRst(1, Enable, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_IPPowerOn(bool PowerOn, uint32_t modlist)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// Power ON ALL IPs
		hal_es2_cctrl_SetPonClkRst(0, PowerOn, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		// Power ON ALL IPs
		hal_es3_cctrl_SetPonClkRst(0, PowerOn, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_IPReset(bool OutOfReset, uint32_t modlist)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cctrl_SetPonClkRst(2, OutOfReset, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cctrl_SetPonClkRst(2, OutOfReset, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_IPFuncReset(bool OutOfReset, uint32_t modlist)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cctrl_SetPonClkRst(3, OutOfReset, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cctrl_SetPonClkRst(3, OutOfReset, modlist);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif 

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_SerializerInterfaceSet(int32_t mode, float init_out_clk_freq )
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cctrl_SetSerialiserMode(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (mode)
		{
		case 1:
			hal_es2_csi2_Init();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			hal_es2_lvds_Init(init_out_clk_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			hal_es2_cif_Init(init_out_clk_freq, mode);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 4:
			hal_es2_cif_Init(init_out_clk_freq, mode);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		}
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cctrl_SetSerialiserMode(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		switch (mode)
		{
		case 1:
			hal_es3_csi2_Init();
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 2:
			hal_es3_lvds_Init(init_out_clk_freq);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		case 3:
			hal_es3_cif_Init(init_out_clk_freq, mode);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;

		case 4:
			hal_es3_cif_Init(init_out_clk_freq, mode);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			break;
		}
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CC_SetDynamicPowerMode(uint32_t mode, bool setTx, bool setRx, bool setLo, bool setAdc, bool setChirp, bool setSerializer)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d",chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cctrl_SetDynamicPowerMode(mode, setTx, setRx, setLo, setAdc, setChirp, setSerializer);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_LVDS_CfgMode(bool bit_clk_phase, bool frame_clk_phase, bool msb_first)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_lvds_CfgMode(bit_clk_phase, frame_clk_phase, msb_first);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES2

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_lvds_CfgMode(bit_clk_phase, frame_clk_phase, msb_first, true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_LVDS_CfgTestMode(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_lvds_CfgTestMode();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_lvds_CfgTestMode();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3
	
	return HAL_GERRCODE;
}

void chip_LVDS_CfgWindowActSel( bool act_high )
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_lvds_CfgWindowActSel(act_high);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_lvds_CfgWindowActSel(act_high);
	}
#endif //DOLPHIN_CFG_ES3
}

DolphinIC_rval_t chip_CSI2_Config(uint32_t NChirps, uint32_t NLanes, uint32_t DataRate)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_csi2_Config(NLanes, DataRate);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_csi2_Config(NLanes, DataRate, true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CSI2_CfgTestMode(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_csi2_CfgTestMode(true, 0xBF5);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		// 0x00:Register data, 0x01:Sine pattern, 0x02:Incremnet pattern
		hal_es3_csi2_CfgTestMode(true, 0xBF5,0x00);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ADC_Recalibrate(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_adc_recalibrate();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_adc_recalibrate_1();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TE_StaticConfig(uint16_t NumChirp, float SeqInterval, float tJumpback, int32_t profSelect, \
	uint32_t profileStayCnt, bool ProfileResetEn, float PONDelay, float ISMDelay, float TXPonGroupDelay, float RXPonGroupDelay)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		//configure number of chirps in a sequence
		hal_es2_teng_CfgNumChirpSeq(1, NumChirp);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure sequence internal, normally keep it 1(25ns)
		hal_es2_teng_CfgSeqInterval(SeqInterval);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure jumpback time.
		hal_es2_teng_CfgTJumpBack(tJumpback);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure chirp profile.
		hal_es2_teng_CfgChirpProfile(profSelect, profileStayCnt, ProfileResetEn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure power on delay
		hal_es2_teng_CfgDCPowOnDelay(PONDelay, ISMDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//group pon delays
		hal_es2_teng_CfgTXPowOnDelay(TXPonGroupDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es2_teng_CfgRXPowOnDelay(RXPonGroupDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		//configure number of chirps in a sequence
		hal_es3_teng_CfgNumChirpSeq(1, NumChirp);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure sequence internal, normally keep it 1(25ns)
		hal_es3_teng_CfgSeqInterval(SeqInterval);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure jumpback time.
		hal_es3_teng_CfgTJumpBack(tJumpback);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure chirp profile.
		hal_es3_teng_CfgChirpProfile(profSelect, profileStayCnt, ProfileResetEn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//configure power on delay
		hal_es3_teng_CfgDCPowOnDelay(PONDelay, ISMDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		//configure CAFC fast switch pulse duration to 2.5us and enable it(in ver 5.3.0 value is 5us)
		hal_es3_teng_CfgChirpFastSwitchCtrl(true, 2.5);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//group pon delays
		hal_es3_teng_CfgTXPowOnDelay(TXPonGroupDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		hal_es3_teng_CfgRXPowOnDelay(RXPonGroupDelay);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TE_ProfileConfig(int ProfileNum, float DwellTime, float SettleTime, uint16_t NumSamples,\
	uint8_t Decimation, bool PDCBWWide, float ChirpPeriod, bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4])
{
	//TX/RX active bits
    uint8_t     txActiveNum = ( ((uint8_t)TxPON[2]) << 0x02 ) | ( ((uint8_t)TxPON[1]) << 0x01 ) | ( ((uint8_t)TxPON[0]) );
    uint8_t     rxActiveNum = ( ((uint8_t)RxPON[3]) << 0x03 ) | ( ((uint8_t)RxPON[2]) << 0x02 ) | ( ((uint8_t)RxPON[1]) << 0x01 ) | ( ((uint8_t)RxPON[0]) );
    uint8_t     bps_control_bits = ( ((uint8_t)BPSControl[2]) << 0x02 ) | ( ((uint8_t)BPSControl[1]) << 0x01 ) | ( ((uint8_t)BPSControl[0]) );
    uint8_t     tx_control_bits = ( ((uint8_t)TxSW[2]) << 0x02 ) | ( ((uint8_t)TxSW[1]) << 0x01 ) | ( ((uint8_t)TxSW[0]) );

	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		//Configure Control3 register in Timing Engine
		hal_es2_teng_UpdateProfChirpPeriod(ProfileNum, txActiveNum, rxActiveNum, ChirpPeriod);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//timing_profile
		hal_es2_teng_UpdateProfTiming(ProfileNum,
			DwellTime, false, 75e-3, bps_control_bits, tx_control_bits);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//adc_profile
		hal_es2_teng_UpdateProfADC(ProfileNum,
			SettleTime,
			NumSamples,
			Decimation,
			PDCBWWide); //PDC_BW changed for ES2
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		//Configure Control3 register in Timing Engine
		hal_es3_teng_UpdateProfChirpPeriod(ProfileNum, txActiveNum, rxActiveNum, ChirpPeriod);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//timing_profile
		hal_es3_teng_UpdateProfTiming(ProfileNum,
			DwellTime, false, 75e-3f, bps_control_bits, tx_control_bits);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//adc_profile
		hal_es3_teng_UpdateProfADC(ProfileNum,
			SettleTime,
			NumSamples,
			Decimation,
			PDCBWWide); //PDC_BW changed for ES2
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TE_ChirpTrigMode(uint8_t ReadyIntMode, uint8_t CSI2FrameMode, bool ChirpPowerMode, bool ChirpStartToggleOnChirpLevel, bool SyncExtTrig, bool UseExtTrigger)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_teng_CfgChirpTriggerMode(ReadyIntMode, CSI2FrameMode, ChirpPowerMode, ChirpStartToggleOnChirpLevel, SyncExtTrig, UseExtTrigger);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_teng_CfgChirpTriggerMode(ReadyIntMode, CSI2FrameMode, ChirpPowerMode, ChirpStartToggleOnChirpLevel, SyncExtTrig, UseExtTrigger);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TE_ChirpStart(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_teng_StartChirp();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

void chip_TE_WaitForReady(void)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_teng_WaitForReady();
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_teng_WaitForReady();
	}
#endif //DOLPHIN_CFG_ES3
}

DolphinIC_rval_t chip_TE_LoadProfile(uint8_t profID)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_teng_LoadProfile(profID);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif//DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}


DolphinIC_rval_t chip_SC_ProfileConfig(int ProfileNum, float fStart, float usedBW, float tSettle, float tSample, float tJumpback, float tReset, bool downChirp)
{
	float tramp = tSample + tSettle + tJumpback;

	HAL_GERRCODE_INIT;
	
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_sctrl_UpdateProfFreDiv(ProfileNum, fStart, usedBW, downChirp, tReset, tramp);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		return HAL_GERRCODE;
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_sctrl_UpdateProfFreDiv(ProfileNum, fStart, usedBW, downChirp, tReset, tramp);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

int chip_Chirp_Program(
	int ProfileNum,
	bool narrowBand, bool downChirp,
	double* effFc, float effBW, float loopBW,
	float tDwell, float tSettle, float tJumpback, float tReset,
	uint16_t NumSamples, uint8_t Decimation,
	bool PDCBWWide,
	bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4],
	float tidle)
{

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		float fStart, fStop, usedBW = 0;
		uint8_t subband = 0;

		float tSample = NumSamples * 25.0f / 1000.0f;

		//try to select a suitable subband.
#ifndef SB_BINARYSEARCH_ENABLE
		int SBSelStatus = chip_CTRL_SubBandSelect(effFc, effBW, tSettle, tSample, tJumpback, &fStart, &fStop, downChirp, &usedBW, narrowBand, &subband);
#else
		int SBSelStatus = chip_CAFC_SubBandSelectBinarySearch(effFc, effBW, tSettle, tSample, tJumpback, &fStart, &fStop, downChirp, &usedBW, narrowBand, &subband);
#endif

		if (SBSelStatus < 0)
		{
			//no suitable subband found.
			DbgErr("No suitable subband found!!! effFC(%e), effBW(%e) \n", *effFc, effBW);
			return -1;
		}
		else
		{
			//setup the Chirp AFC profile
			chip_CAFC_ProfileConfig(ProfileNum, narrowBand, downChirp, subband, loopBW, usedBW, *effFc, tSettle, tSample, tJumpback);

			//setup the Timing Engine profile
			chip_TE_ProfileConfig(ProfileNum, tDwell, tSettle, NumSamples, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset, BPSControl, TxSW, TxPON, RxPON);

			//setup the Sweep Control profile
			chip_SC_ProfileConfig(ProfileNum, fStart, usedBW, tSettle, tSample, tJumpback, tReset, downChirp);

			//success
			return 0;
		}
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		float fStart, fStop, usedBW = 0;
		uint8_t subband = 0;

		float tSample = NumSamples * 25.0f / 1000.0f * Decimation;

		//try to select a suitable subband.
#ifndef SB_BINARYSEARCH_ENABLE
		int SBSelStatus = chip_CTRL_SubBandSelect(effFc, effBW, tSettle, tSample, tJumpback, &fStart, &fStop, downChirp, &usedBW, narrowBand, &subband);
#else
		int SBSelStatus = chip_CAFC_SubBandSelectBinarySearch(effFc, effBW, tSettle, tSample, tJumpback, &fStart, &fStop, downChirp, &usedBW, narrowBand, &subband);
#endif

		if (SBSelStatus < 0)
		{
			//no suitable subband found.
			DbgErr("No suitable subband found!!! effFC(%e), effBW(%e) \n", *effFc, effBW);
			return -1;
		}
		else
		{
			//setup the Chirp AFC profile
			chip_CAFC_ProfileConfig(ProfileNum, narrowBand, downChirp, subband, loopBW, usedBW, *effFc, tSettle, tSample, tJumpback);

			//setup the Timing Engine profile
			chip_TE_ProfileConfig(ProfileNum, tDwell, tSettle, NumSamples, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset + tidle, BPSControl, TxSW, TxPON, RxPON);

			//setup the Sweep Control profile
			chip_SC_ProfileConfig(ProfileNum, fStart, usedBW, tSettle, tSample, tJumpback, tReset, downChirp);

			//set LO level control
			hal_es3_rx_SetLoLevel(*effFc);

			//success
			return  (int) subband;
		}
	}
#endif //DOLPHIN_CFG_ES3


	//default, return failure
	return -1;
}

DolphinIC_rval_t chip_Chirp_CWMode(uint8_t profID, bool narrowBand, double CWFreq, uint16_t NumSamples, float loopBW, uint8_t Decimation, float tidle)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		float effBandwidth = 600e6f;
		float chirpSlope = effBandwidth / ((NumSamples / 40 ) * Decimation); // Hertz/us
		float SettleTime = 5.0f;
		float DwellTime = 4.0f;
		float JumpbackTime = 0.4f;
		float ResetTime = 4.0f;

		//TX Bipolar Phase Shift array (4 profiles, 3 TXs)
		bool TXBPS[3] = {false, false, false };

		//TX DC power on in TE (4 profiles, 3 TXs)
		//!!for normal power mode:
		//!!TODO: to validate if this is still true to ES3
		//Need to switch DC on for all used TXs in profile 0
		//(even they are not transmitting used in profile0)!!
		bool SetTXPowerOn[3] = { 0, 0, 0  };

		//TX RF switch in TE (4 profiles, 3 TXs)
		bool SetTXSwitch[3] = { 0, 0, 0 };

		//RX DC power on in TE (4 profiles, 4 RXs)
		bool SetRXPowerOn[4][4] = {
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 } };

		int errorCode = 0;

	//calculate effFC based on desired CWFreq
		double effFC = CWFreq + chirpSlope*SettleTime + effBandwidth / 2;
		errorCode=chip_Chirp_Program(profID, narrowBand, false, &effFC, effBandwidth, loopBW, DwellTime, SettleTime, JumpbackTime, ResetTime, NumSamples, Decimation, false, TXBPS, SetTXPowerOn, SetTXSwitch, SetRXPowerOn[profID], tidle);
		if (errorCode != 0)
		{
			HAL_GEC_FUNEXIT(DOLPHINIC_EC_SUBBANDNOTFOUND);
		}
		// set incremental value for each frequency step to 0 
		hal_es3_sctrl_ZeroRamp(profID);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//load profile across modules
		chip_TE_LoadProfile(profID);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		
	}
#endif	//DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

int chip_Chirp_ProgramStitch(
	bool narrowBand, bool downChirp,
	double effFc0, double effBW0, float loopBW,
	float tDwell, float tSettle, float tJumpback, float tReset,
	uint16_t NumSamplesPerProfile, uint8_t Decimation,
	bool PDCBWWide,
	bool BPSControl[3], bool TxSW[3], bool TxPON[3], bool RxPON[4], bool comp1StepEn)
{

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		//TODO: unified error code

		float fStart1, fStop1, usedBW1 = 0;
		float fStart2, fStop2, usedBW2 = 0;

		uint8_t subband1 = 0;
		uint8_t subband2 = 0;

		float effBW = 0.5f*effBW0;

		double effFc1 = effFc0 - 0.5f*effBW;
		double effFc2 = effFc0 + 0.5f*effBW;

		float tSample = NumSamplesPerProfile * 25.0f / 1000.0f;

		//try to select a suitable subband.
		//try to select a suitable subband.
#ifndef SB_BINARYSEARCH_ENABLE
		int SBSelStatus1 = chip_CTRL_SubBandSelect(&effFc1, effBW, tSettle, tSample, tJumpback, &fStart1, &fStop1, downChirp, &usedBW1, narrowBand, &subband1);
		int SBSelStatus2 = chip_CTRL_SubBandSelect(&effFc2, effBW, tSettle, tSample, tJumpback, &fStart2, &fStop2, downChirp, &usedBW2, narrowBand, &subband2);
#else
		int SBSelStatus1 = chip_CAFC_SubBandSelectBinarySearch(&effFc1, effBW, tSettle, tSample, tJumpback, &fStart1, &fStop1, downChirp, &usedBW1, narrowBand, &subband1);
		int SBSelStatus2 = chip_CAFC_SubBandSelectBinarySearch(&effFc2, effBW, tSettle, tSample, tJumpback, &fStart2, &fStop2, downChirp, &usedBW2, narrowBand, &subband2);
#endif


		if (SBSelStatus1 < 0 || SBSelStatus2<0)
		{
			//no suitable subband found.
			//In chirp stitching mode, no subband shift is allowed due to strict alignment of RF freqeuncies.
			DbgErr("Subband search failed for chirp stitching \n");
			return -1;
		}
		else
		{
			//setup the Chirp AFC profile 0-1
			chip_CAFC_ProfileConfig(0, narrowBand, downChirp, subband1, loopBW, usedBW1, effFc1, tSettle, tSample, tJumpback);
			chip_CAFC_ProfileConfig(1, narrowBand, downChirp, subband1, loopBW, usedBW2, effFc2, tSettle, tSample, tJumpback);

			//setup the Timing Engine profile 0-1
			chip_TE_ProfileConfig(0, tDwell, tSettle, NumSamplesPerProfile, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset, BPSControl, TxSW, TxPON, RxPON);
			chip_TE_ProfileConfig(1, tDwell, tSettle, NumSamplesPerProfile, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset, BPSControl, TxSW, TxPON, RxPON);

			//setup the Sweep Control profile 0-1
			chip_SC_ProfileConfig(0, fStart1, usedBW1, tSettle, tSample, tJumpback, tReset, downChirp);
			chip_SC_ProfileConfig(1, fStart2, usedBW2, tSettle, tSample, tJumpback, tReset, downChirp);

			if (comp1StepEn)
			{
				hal_es2_cafc_CompensateChirpStitching();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			//success
			return 0;
		}
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		//TODO: unified error code

		float fStart1, fStop1, usedBW1 = 0;
		float fStart2, fStop2, usedBW2 = 0;

		uint8_t subband1 = 0;
		uint8_t subband2 = 0;

		double effBW = 0.5f*effBW0;

		double effFc1 = effFc0 - 0.5f*effBW;
		double effFc2 = effFc0 + 0.5f*effBW;

		float tSample = NumSamplesPerProfile * 25.0f / 1000.0f * Decimation;

		//try to select a suitable subband.
		//try to select a suitable subband.
#ifndef SB_BINARYSEARCH_ENABLE
		int SBSelStatus1 = chip_CTRL_SubBandSelect(&effFc1, effBW, tSettle, tSample, tJumpback, &fStart1, &fStop1, downChirp, &usedBW1, narrowBand, &subband1);
		int SBSelStatus2 = chip_CTRL_SubBandSelect(&effFc2, effBW, tSettle, tSample, tJumpback, &fStart2, &fStop2, downChirp, &usedBW2, narrowBand, &subband2);
#else
		int SBSelStatus1 = chip_CAFC_SubBandSelectBinarySearch(&effFc1, effBW, tSettle, tSample, tJumpback, &fStart1, &fStop1, downChirp, &usedBW1, narrowBand, &subband1);
		int SBSelStatus2 = chip_CAFC_SubBandSelectBinarySearch(&effFc2, effBW, tSettle, tSample, tJumpback, &fStart2, &fStop2, downChirp, &usedBW2, narrowBand, &subband2);
#endif


		if (SBSelStatus1 < 0 || SBSelStatus2 < 0)
		{
			//no suitable subband found.
			//In chirp stitching mode, no subband shift is allowed due to strict alignment of RF freqeuncies.
			DbgErr("Subband search failed for chirp stitching \n");
			return -1;
		}
		else
		{
			//setup the Chirp AFC profile 0-1
			chip_CAFC_ProfileConfig(0, narrowBand, downChirp, subband1, loopBW, usedBW1, effFc1, tSettle, tSample, tJumpback);
			chip_CAFC_ProfileConfig(1, narrowBand, downChirp, subband2, loopBW, usedBW2, effFc2, tSettle, tSample, tJumpback);

			//setup the Timing Engine profile 0-1
			chip_TE_ProfileConfig(0, tDwell, tSettle, NumSamplesPerProfile, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset, BPSControl, TxSW, TxPON, RxPON);
			chip_TE_ProfileConfig(1, tDwell, tSettle, NumSamplesPerProfile, Decimation, PDCBWWide, tDwell + tSettle + tSample + tJumpback + tReset, BPSControl, TxSW, TxPON, RxPON);

			//setup the Sweep Control profile 0-1
			chip_SC_ProfileConfig(0, fStart1, usedBW1, tSettle, tSample, tJumpback, tReset, downChirp);
			chip_SC_ProfileConfig(1, fStart2, usedBW2, tSettle, tSample, tJumpback, tReset, downChirp);

			if (comp1StepEn)
			{
				hal_es3_sctrl_CompensateChirpStitching();
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			//success
			return 0;
		}

	}
#endif // DOLPHIN_CFG_ES3
	return DOLPHINIC_EC_FUNCNOTEXIST;

}


DolphinIC_rval_t chip_CAFC_ProfileConfig(int ProfileNum, bool narrowBand, bool downChirp, int subband, float loopBW, float usedBW, double effFc, float tSettle, float tSample, float tJumpback)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cafc_ProfileConfig(ProfileNum, narrowBand, downChirp, subband, loopBW, usedBW, effFc, tSettle, tSample, tJumpback);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_ProfileConfig(ProfileNum, narrowBand, downChirp, subband, loopBW, usedBW, effFc, tSettle, tSample, tJumpback);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_VCOFreqMeasure(int subband, bool lowerBound, bool narrowBand, float *freqMeas, unsigned int countPeriod, uint8_t iVCOFineOTP76G)
{
	//this is only for interfacing ES2 API with double types (ES3 has float type only)
#ifdef DOLPHIN_CFG_ES2
	double freqMeasT = *freqMeas;
#endif

	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cafc_VCOFreqMeasure(subband, lowerBound, narrowBand, &freqMeasT, countPeriod);

		//returning float value from double
		*freqMeas = (float)freqMeasT;
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_VCOFreqMeasure(subband, lowerBound, narrowBand, freqMeas, countPeriod, iVCOFineOTP76G);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_VCOFreqCalibrate(bool narrowBand, uint8_t startSB, int numPoints)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es2_cafc_VCOFreqCalibrate(narrowBand, startSB, numPoints);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
#ifndef SB_BINARYSEARCH_ENABLE
		hal_es3_cafc_VCOFreqCalibrate(narrowBand, startSB, numPoints);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
#endif
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CAFC_SubBandSelectBinarySearch(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand)
{
	//this is only for interfacing ES2 API with double types (ES3 has float type only)
#ifdef DOLPHIN_CFG_ES2
	double effFcT = *effFc;
	double fStartT = *fStart;
	double fStopT = *fStop;
	double usedBWT = *usedBW;
#endif

	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cafc_SubBandSelectBinarySearch(&effFcT, effBW, tSettle, tSample, tJumpback, &fStartT, &fStopT, downChirp, &usedBWT, narrowBand, subBand);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		//assign output
		*effFc = (float)effFcT;
		*fStart = (float)fStartT;
		*fStop = (float)fStopT;
		*usedBW = (float)usedBWT;
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cafc_SubBandSelectBinarySearch(effFc, effBW, tSettle, tSample, tJumpback, fStart, fStop, downChirp, usedBW, narrowBand, subBand);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CIF_CfgTestMode(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cif_CfgTestMode();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cif_CfgTestMode();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_CIF_Config(bool PacketHeaderEnable, bool CRCEnable, bool NegEdgeEnable)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_cif_Config(PacketHeaderEnable, CRCEnable, NegEdgeEnable);

		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_cif_Config(PacketHeaderEnable, CRCEnable, NegEdgeEnable, true);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_MCLK_Config()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_mclk_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_mclk_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_MCLK_Recalibrate(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_mclk_Recalibrate();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_mclk_Recalibrate();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
	
#endif //DOLPHIN_CFG_ES3
	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TX_Control(int TXNum, bool BPSExtControlEn, bool SPI_BPSEn, bool SPI_SWEn, bool SPI_TXEn)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_tx_Control(TXNum, BPSExtControlEn, SPI_BPSEn, SPI_SWEn, SPI_TXEn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_tx_Control(TXNum, BPSExtControlEn, SPI_BPSEn, SPI_SWEn, SPI_TXEn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
	
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_LO_Control(int mode, uint8_t b2gain)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_lointf_CfgMode(mode, b2gain);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_lointf_CfgMode(mode, b2gain);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_RX_ProfileConfig(int RXNum, int ProfileNum, uint8_t rxGain, float LPF6dBCutOffHz, float HPF6dBCutOffHz, bool RMSDetOn)
{
	HAL_GERRCODE_INIT;
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_rx_ProfileConfig(RXNum, ProfileNum, rxGain, LPF6dBCutOffHz, HPF6dBCutOffHz, RMSDetOn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_rx_ProfileConfig(RXNum, ProfileNum, rxGain, LPF6dBCutOffHz, HPF6dBCutOffHz, RMSDetOn);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}



DolphinIC_rval_t chip_FS_IntegrityCheckMClk(int32_t mode, float refFreq)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MCLKIntegrityCheck(mode, refFreq);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MCLKIntegrityCheck(mode, refFreq);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_lointf_GainCalibration(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_lointf_GainCalibration();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_lointf_GainCalibration();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_lointf_GainCalibration_Mode(int32_t mode)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_lointf_GainCalibration_Mode(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_tx_GainCalibration(bool txOn[3], uint8_t profile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_tx_GainCalibration(txOn, profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_tx_GainCalibration(txOn, profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_tx_GainCalibration_Mode(bool txOn[3], uint8_t profile, int32_t mode)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_tx_GainCalibration_Mode(txOn, profile, mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ATB_Init()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_atb_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_atb_Init();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif 

	return HAL_GERRCODE;
}

float chip_ATB_ReadTemp(uint8_t _chooseATB, uint16_t _chooseIP)
{
	float tempReadOut = 0;
	float (* p_TempReadOut) = 0;
	p_TempReadOut = & tempReadOut;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_atb_TempReadout(_chooseATB, _chooseIP, p_TempReadOut);
		return tempReadOut;
	}
#endif
#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_atb_TempReadout(_chooseATB, _chooseIP, p_TempReadOut);
		return tempReadOut;
	}
#endif //DOLPHIN_CFG_ES

	//default: return unreasonably low temperature
	return -100000;
}


DolphinIC_rval_t chip_reg_ProbeSPIWrite( void * pv_arg1 )
{
    return( glue_reg_ProbeSPIWrite( pv_arg1 ) );
}

DolphinIC_rval_t chip_reg_Write(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReturnedData)
{
    return( glue_reg_Write( ModuleAddress, RegAddress, WriteData, ReturnedData) );
}

DolphinIC_rval_t chip_reg_BurstWrite(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData)
{
    return ( glue_reg_BurstWrite( ModuleAddress, RegAddress, WriteData, NumWords, SR_Mode, ReturnedData) );
}

DolphinIC_rval_t chip_reg_Read(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint32_t *ReturnedData)
{
    return( glue_reg_Read( ModuleAddress, RegAddress, ReadData, ReturnedData ) );
}

DolphinIC_rval_t chip_reg_BurstRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData)
{
    return( glue_reg_BurstRead( ModuleAddress, RegAddress, ReadData, NumWords, SR_Mode, ReturnedData ) );
}

DolphinIC_rval_t chip_reg_WriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReadData, bool CS_Mode, uint32_t *ReturnedData)
{
    return( glue_reg_WriteRead( ModuleAddress, RegAddress, WriteData, ReadData, CS_Mode, ReturnedData ));
}

DolphinIC_rval_t chip_reg_BurstWriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint32_t *ReadData, uint8_t NumWords, bool CS_Mode, bool SR_Mode, bool LoopBack, uint32_t *ReturnedData)
{
    return( glue_reg_BurstWriteRead( ModuleAddress, RegAddress, WriteData, ReadData, NumWords, CS_Mode, SR_Mode, LoopBack, ReturnedData ));
}

DolphinIC_rval_t chip_ISM_InterfaceToggleTest(dolphin_ExtPinID_t en_pid)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_InterfaceToggleTest(en_pid);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_InterfaceToggleTest(en_pid);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

void chip_ISM_MaskSupplyError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskSupplyError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskSupplyError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskSupplyError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskSupplyError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskSupplyError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_MaskTxError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskTxError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskTxError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskTxError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskTxError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskTxError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_MaskRxError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskRxError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskRxError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskRxError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskRxError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskRxError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_MaskChirpError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskChirpError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskChirpError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskChirpError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskChirpError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskChirpError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_MaskMCLOError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskMCLOError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskMCLOError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskMCLOError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskMCLOError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskMCLOError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_MaskADCError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_MaskADCError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_MaskADCError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

void chip_ISM_UnMaskADCError(uint32_t arg_mask)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMaskADCError(arg_mask);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMaskADCError(arg_mask);
	}
#endif //DOLPHIN_CFG_ES3
}

uint32_t chip_ISM_GetRawMasterErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawMasterErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawMasterErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawSupplyErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawSupplyErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawSupplyErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawTxErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawTxErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawTxErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawRxErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawRxErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawRxErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawChirpErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawChirpErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawChirpErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawMCLOErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawMCLOErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawMCLOErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawADCErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawADCErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawADCErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRawRFPowDwnErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawRFPowDwnErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawRFPowDwnErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetMasterErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetMasterErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetMasterErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetSupplyErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetSupplyErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetSupplyErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetTxErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetTxErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetTxErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetTxRawErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRawTxErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRawTxErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRxErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRxErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRxErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetChirpErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetChirpErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetChirpErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetMCLOErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetMCLOErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetMCLOErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetADCErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetADCErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetADCErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetRFPowDwnErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetRFPowDwnErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetRFPowDwnErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

uint32_t chip_ISM_GetISMErrorStatus(void)
{
	uint32_t rval_status;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_GetISMErrorStatus(&rval_status);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_GetISMErrorStatus(&rval_status);
	}
#endif //DOLPHIN_CFG_ES3
	return rval_status;
}

DolphinIC_rval_t chip_ISM_SetMCUReset(void)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_SetMCUReset();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif //DOLPHIN_CFG_ES3

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_FIT(int32_t mode)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_FIT(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_FIT(mode);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}


uint32_t chip_CTRL_ComputeCRC32(const void * Crc_DataPtr, uint32_t Crc_Length, uint32_t Crc_StartValue32)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		return hal_es2_CRC_ComputeCRC32(Crc_DataPtr, Crc_Length, Crc_StartValue32);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		return hal_es3_CRC_ComputeCRC32(Crc_DataPtr, Crc_Length, Crc_StartValue32);
	}
#endif

	return 0;
}

DolphinIC_rval_t chip_ISM_SWTXFit(uint8_t fitProfile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_SwTXFit(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_SwTXFit(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif
	
	return HAL_GERRCODE;
}


DolphinIC_rval_t chip_ISM_SWChirpFit(uint8_t fitProfile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_SwChirp_Min_error(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es2_ISM_SwChirp_Unlock_error(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_SwChirp_Min_error(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		hal_es3_ISM_SwChirp_Unlock_error(fitProfile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_Sw_FIT(uint8_t fitProfile, bool TxPON[3])
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		// this function does not exist for ES2
		DbgWar("This function does NOT exist for ES %d", chipMaskVersion);
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_Sw_FIT(fitProfile, TxPON);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

void chip_rshd_updateFromDev(uint8_t moduleaddress)
{
#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_rshd_updateFromDev(moduleaddress);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_rshd_updateFromDev(moduleaddress);
	}
#endif
}

DolphinIC_rval_t chip_rshd_checkRegPage(uint8_t moduleaddress)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_rshd_checkRegPage(moduleaddress);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_rshd_checkRegPage(moduleaddress);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_StatusCheckAndRecover()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_StatusCheckAndRecover();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_StatusCheckAndRecover();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

void chip_ISM_SetGPIO(uint32_t en_pid, bool on_off)
{
	glue_SetGPIO(en_pid, on_off);
}

bool chip_ISM_GetGPIO(uint32_t en_pid)
{
	bool pin_status;

	glue_GetGPIO(en_pid, &pin_status);

	return pin_status;
}

DolphinIC_rval_t chip_ISM_Inject_error(uint32_t Error_ID, uint8_t Profile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_Inject_error(Error_ID, Profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_Inject_error(Error_ID, Profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_UnMask_All_error()
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_UnMask_All_error();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_UnMask_All_error();
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_Recover_error_FunRst(uint32_t Error_ID)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_Recover_error_FunRst(Error_ID);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_Recover_error_FunRst(Error_ID);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_ISM_Recover_error(uint32_t Error_ID, uint8_t Profile)
{
	HAL_GERRCODE_INIT;

#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		hal_es2_ISM_Recover_error(Error_ID, Profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_ISM_Recover_error(Error_ID, Profile);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TX_CorrectLevelMonThresholds(int txNum, uint8_t typeTh, float Parp, bool readTemp, int temperature, float effFc)
{
	float tempReadOut = 0;
	HAL_GERRCODE_INIT;


#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		HAL_GEC_ASSERT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		hal_es3_tx_CorrectThresholdsParp(txNum, typeTh, Parp);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

		if (readTemp)
		{
			hal_es3_atb_TempReadout(1, (txNum + 16), &tempReadOut);
			HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
		else
			tempReadOut = temperature;

		hal_es3_tx_CorrectThresholdsTemperature(txNum, typeTh, tempReadOut, effFc);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
		}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TX_SetAllMonitorThresholds(float ParpMin, float ParpLow, float ParpHigh, float ParpMax, float effFc, bool applyOverFreq)
{
	HAL_GERRCODE_INIT;


#ifdef DOLPHIN_CFG_ES2
	if (chipMaskVersion == 2)
	{
		HAL_GEC_ASSERT(DOLPHINIC_EC_FUNCNOTEXIST);
	}
#endif

#ifdef DOLPHIN_CFG_ES3
	if (chipMaskVersion == 3)
	{
		chip_ATB_Init();
		//Correct/compensate OTP values for early ES3 samples
		hal_es3_OTP_CompensateOTP(effFc, applyOverFreq);
		for (int indx = 1; indx < 4; indx++)
		{
			if (hal_es3_OTP_checkValidIP(0x10 + indx, NULL, NULL) != DOLPHINIC_EC_IPNOTACTIVATED) {
				if (ParpMin != 0.0f) chip_TX_CorrectLevelMonThresholds(indx, 0, ParpMin, true, 0, effFc);
				if (ParpLow != 0.0f) chip_TX_CorrectLevelMonThresholds(indx, 1, ParpLow, true, 0, effFc);
				if (ParpHigh != 0.0f) chip_TX_CorrectLevelMonThresholds(indx, 2, ParpHigh, true, 0, effFc);
				if (ParpMax != 0.0f) chip_TX_CorrectLevelMonThresholds(indx, 3, ParpMax, true, 0, effFc);
			}
		}

		
	}
#endif

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TX_fPCtrl_SetHighThreshold(uint8_t txNumb, uint16_t txGain)
{
	hal_es3_tx_fPCtrl_SetHighThreshold(txNumb, txGain);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	return HAL_GERRCODE;
}

DolphinIC_rval_t chip_TX_fPCtrl_CorrPout(uint8_t txNumb, bool isFullCalib)
{
	float tempReadOut = 0;
	HAL_GERRCODE_INIT;

	//read temperature
	hal_es3_atb_TempReadout(1, (txNumb + 16), &tempReadOut);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	//adjust the high threshold if necessary
	hal_es3_tx_fPCtrl_AdjustHighThreshold(txNumb, tempReadOut);
	HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	if (isFullCalib)
	{
		//adjust Tx Gain code
		hal_es3_tx_fPCtrl_CalibTxGain(txNumb);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}
	else
	{
		hal_es3_tx_fPCtrl_CorrectTxGain(txNumb);
		HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	}

	return HAL_GERRCODE;
}




#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */
