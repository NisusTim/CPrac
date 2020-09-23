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
* @file hal_es3_cafc.h
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

#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_CAFC_H
#define HAL_ES3_CAFC_H


#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */


#define NUM_SUBBANDS_ES3 128
#define LOOP_BW_MIN_ES3 300000u //hz
#define LOOP_BW_MAX_ES3 1400000u //hz
#define LOOP_BW_INC_ES3 50000u //hz
#define NUM_ITEM_VCO_FILTER_LUT_ES3 23u

	// at which RF frequency the loop BW table is generated.
	// This is also used to do the VCO gain compensation
#define REF_RF_FREQ_ES3 76.0e9f
//minimum current per VCO current slice for stability
#define MIN_SLICE_CURRENT_ES3 62.5f

#define SB_MARGIN_ES3 ((uint8_t)20)
#define FREQ_CNT_PERIOD_ES3 (10)

	///Struct for VCO and Filter setting LUT
	typedef struct VCO_FILTER_LUT_ES3
	{
		float loopBW;
		uint8_t LPF_C1;
		uint8_t LPF_C2;
		uint8_t LPF_C3;
		uint8_t CP_SLICE_EN;
		uint8_t IBIAS_CP_150U;
	} VCO_FILTER_LUT_ES3_t;

	//VCO table item struct
	typedef struct VCOTableItemES3
	{
		float fBegin;
		float fEnd;
		float BW;
		bool   dirty;
	} VCOTableItemES3_t;

#ifndef SB_BINARYSEARCH_ENABLE
	//VCO table global variable
	//Narrow Band VCO table
	extern VCOTableItemES3_t VCOTableNBES3[128];
	//Wide Band VCO table
	extern VCOTableItemES3_t VCOTableWBES3[128];
#endif

	//profile based configurations
	DolphinIC_rval_t hal_es3_cafc_ProfileConfig(int ProfileNum, bool narrowBand, bool downChirp, int subband, float loopBW, float usedBW, double effFc, float tSettle, float tSample, float tJumpback);

	DolphinIC_rval_t hal_es3_cafc_VCOFreqMeasure(int subband, bool lowerBound, bool narrowBand, float * p_freqmesval, unsigned int countPeriod, uint8_t iVCOFine);

#ifndef SB_BINARYSEARCH_ENABLE
	DolphinIC_rval_t hal_es3_cafc_VCOFreqCalibrate(bool narrowBand, uint8_t startSB, int numPoints);

	DolphinIC_rval_t hal_es3_cafc_GetVCOTable(bool narrowTable, float fBegin[128], float fEnd[128], float BW[128]);

	DolphinIC_rval_t hal_es3_cafc_SetVCOTable(bool narrowTable, int num, float fBegin, float fEnd, float BW);
#endif

	DolphinIC_rval_t hal_es3_cafc_EnableVCO(void);

	DolphinIC_rval_t hal_es3_cafc_EnableLDO(void);

	DolphinIC_rval_t hal_es3_cafc_CalAmplitude(uint8_t nprofile);
	DolphinIC_rval_t hal_es3_cafc_CalAmplitude_InjectRecovery(uint8_t nprofile);

	DolphinIC_rval_t hal_es3_cafc_SubBandSelectBinarySearch(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_CAFC_H */

#endif //DOLPHIN_CFG_ES3

