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
* @file hal_es3_OTP.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief OTP Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_OTP_H
#define HAL_ES3_OTP_H

#include <es3/NXP_TEF810X_Otp.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

	//device OTP size
#define ES3_DEV_OTP_LUT_SIZE (32)
#define ES3_DEV_OTP_START_OFFSET (NXP_TEF810X_MOD17_OTP_DATA_RD_REG_U16)

	//emulated OTP size
#define ES3_DEV_OTP_EMU_SIZE (29)

#define OTP_CRC32_COMPU_START_OFF_ES3 ((0x21C - ES3_DEV_OTP_START_OFFSET) / sizeof(uint32_t)) //0x1C/4 = 7
#define OTP_CRC32_COMPU_LEN_ES3 ( 24 )
#define OTP_CRC32_COMPU_CRCOFF_ES3 ((0x27C - ES3_DEV_OTP_START_OFFSET)  / sizeof(uint32_t) )
#define OTP_CRC32_MAGIC_CONST_ES3 (0x2144DF1CU)

	//OTP table description type define
	typedef struct otptablediscpES3
	{
		uint32_t  src_off;
		uint32_t  src_pos;
		uint32_t  src_msk;
		uint32_t  dst_mod;
		uint32_t  dst_reg;
		uint32_t  dst_pos;
		uint32_t  dst_msk;
		uint32_t  n_bits;
	}OtpTableDiscpES3_t;

	//OTP table entry type define
	typedef struct hal_es3_ism_OtpLUTValuePair
	{
		uint32_t offset;         // OTP Src Off
		uint32_t value;          // OTP Value
	} hal_es3_ism_OtpLUTValuePair_t;

	typedef struct sampleInfo
	{
		uint32_t maskVersion;
		uint32_t tpMajor_ft;         // OTP Src Off
		uint32_t tpMinor_ft;          // OTP Value
		uint32_t tpMajor_wt;         // OTP Src Off
		uint32_t tpMinor_wt;          // OTP Value
		uint32_t wtYear;          // OTP Value
		uint32_t wtMonth;          // OTP Value
		uint32_t wtDay;          // OTP Value
	} sampleInfo_t;

	//OTP table descriptions, for each OTP address.
	//Note: specifying size of the arrays is necessary since sizeof operator is used on these arrays.
	extern const OtpTableDiscpES3_t reg_21C_cat1_ES3[31];
	extern const OtpTableDiscpES3_t reg_220_cat1_ES3[2];
	extern const OtpTableDiscpES3_t reg_220_cat2_ES3[1];
	extern const OtpTableDiscpES3_t reg_234_cat1_ES3[2];
	extern const OtpTableDiscpES3_t reg_23C_cat1_ES3[10];
	extern const OtpTableDiscpES3_t reg_240_cat2_ES3[3];
	extern const OtpTableDiscpES3_t reg_244_cat1_ES3[12];
	extern const OtpTableDiscpES3_t reg_244_cat2_ES3[1];
	extern const OtpTableDiscpES3_t reg_248_cat1_ES3[5];
	extern const OtpTableDiscpES3_t reg_248_cat2_ES3[5];
	extern const OtpTableDiscpES3_t reg_24C_cat1_ES3[17];
	extern const OtpTableDiscpES3_t reg_24C_cat2_ES3[3];
	extern const OtpTableDiscpES3_t reg_264_cat1_ES3[4];
	extern const OtpTableDiscpES3_t reg_26C_cat1_ES3[4];
	extern const OtpTableDiscpES3_t reg_270_cat1_ES3[3];

	//default OTP values (used when OTP is empty)
	extern hal_es3_ism_OtpLUTValuePair_t g_DefaultEmuValueES3[ES3_DEV_OTP_EMU_SIZE];

	//OTP LUT to store readout value
	// extern uint32_t g_aOtpLUT_ES3[ES3_DEV_OTP_LUT_SIZE + 0x01]; // Added 0x01, since Index-0 is Invalid ...
	extern uint32_t * g_OTPShadowLUT_ES3;



	/**
	@brief Checks wheter the module accessed for SPI operation is enabled by OTP
	**/
	DolphinIC_rval_t hal_es3_OTP_checkValidIP(uint32_t mod_add, uint32_t * PON_mask, uint32_t *FIT_mask);

	/**
	@brief Burst-reads all the OTP values and saves it in memory of host (PC or MCU)
	**/
	DolphinIC_rval_t hal_es3_OTP_Load(void);

	/**
	@brief Parses and stores OTP values to the corresponding registers
	**/
	// DolphinIC_rval_t hal_es3_OTP_LoadFromGlobal(const OtpTableDiscpES3_t * tbl_base, uint32_t tbl_size);
	DolphinIC_rval_t hal_es3_OTP_LoadFromGlobal(const OtpTableDiscpES3_t * tbl_base, uint32_t tbl_size, uint32_t IP_PON_Mask);

	/**
	@brief Parses the OTP ID information, compensates for known test program artifacts accordingly.
	**/
	DolphinIC_rval_t hal_es3_OTP_CompensateOTP(double effFC, bool applyOverFreq);

	/**
	@brief Corrects the temperature sensor threshold values
	**/
	DolphinIC_rval_t hal_es3_OTP_CorrectTempSensor(uint16_t moduleID, uint16_t offset);

	/**
	@brief Corrects the LOx3 gain from OTP
	**/
	DolphinIC_rval_t hal_es3_OTP_CorrectLOx3Gain(uint16_t moduleID, uint16_t TXprofile, uint16_t offset, uint32_t artfID, double effFC, bool applyOverFreq);

	DolphinIC_rval_t hal_es3_OTP_GetChipInfo(sampleInfo_t *pChipInfo);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif //OTPTABLE_H
#endif //DOLPHIN_CFG_ES3