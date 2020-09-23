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
* @file hal_es3_ctrl.h
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief This files contains all the algorithms used in the Dolphin API

******************************************************************************/

#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_CTRL_H
#define HAL_ES3_CTRL_H


#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

#ifndef SB_BINARYSEARCH_ENABLE
	int hal_es3_ctrl_SelectSubBand(double *effFc, float effBW, float tSettle, float tSample, float tJumpback, float *fStart, float *fStop, bool downChirp, float *usedBW, bool narrowBand, uint8_t *subBand);
#endif


	/*********************************************** 
	CRC32 calculation in terms of bytes
	"Reflected" Tabel Driven Implementation of CRC
	Reference: Dilip V. Sarwate
	
	for fresh calculation, previousCRC32 should be 0.
	
	Unit Test:
	
	
	#include <iostream>
	#include <iomanip>
	
	void unitTest()
	{
		//ref:https://pycrc.org/models.html
		//see crc-32 Check value
		char input[] = "123456789";
		const uint32_t Check = 0xcbf43926;
	
		uint32_t CRCVal = 0;
		CRCVal = hal_es3_CRC_ComputeCRC32(input, 9, 0);
	
		std::cout << "CRC value is:" << std::hex << CRCVal << std::endl;
		std::cout << "Test " << (CRCVal == 0xcbf43926 ? "passed" : "failed") << "!" << std::endl;
	
		system("pause");
	}
	************************************************/
	uint32_t hal_es3_CRC_ComputeCRC32(const void* data, unsigned int len, uint32_t previousCRC32);

	int hal_es3_2sComplement(uint32_t inp, int no_bits);

	uint32_t hal_es3_bit_flip(uint32_t n, uint32_t bits);



	void hal_es3_ctrl_CfgChirpTestDefault(void);

	void hal_es3_ctrl_CfgSerializerDefault(int32_t mode);

	void hal_es3_ctrl_SetSerializerTestMode(int32_t mode, bool flag_enable, uint8_t test_mode_sel);

	DolphinIC_rval_t hal_es3_comparePON_OTP_forIPEn(uint32_t IP_PON_Mask);

	DolphinIC_rval_t hal_es3_CheckUserPONEn(uint32_t IP_PON_Mask, uint16_t mod_addr);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_CTRL_H */

#endif //DOLPHIN_CFG_ES3
