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
* @file hal_es3_lointf.h
*
* @ver v5.3.0  
*
* @author
*
* @date
*
* @brief LO Interface Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_LOINTF_H
#define HAL_ES3_LOINTF_H

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */


	typedef enum
	{
		hal_es3_lointf_Mode_NORMAL = 0x1,  // MUX=0|B1=1|B2=1|B3=0|B4=0
		hal_es3_lointf_Mode_LOOPTHRU = 0x2,  // MUX=1|B1=1|B2=1|B3=1|B4=1
		hal_es3_lointf_Mode_EXTLOOUT = 0x3,  // MUX=0|B1=1|B2=1|B3=0|B4=1
		hal_es3_lointf_Mode_EXTLOIN = 0x4   // MUX=1|B1=0|B2=1|B3=1|B4=0
	} hal_es3_lointf_ModeID_t;

	DolphinIC_rval_t hal_es3_lointf_CfgMode(int mode, uint8_t b2gain);

	DolphinIC_rval_t hal_es3_lointf_EnableLo(bool benable);

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_LOINTF_H */

#endif //DOLPHIN_CFG_ES3

