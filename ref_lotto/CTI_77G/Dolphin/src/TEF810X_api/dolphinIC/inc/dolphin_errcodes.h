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
* @file dolphin_errcodes.h
*
* @ver vX.Y.Z 
*
* @author
*
* @date
*
* @brief dolphin standard error codes
*
*
******************************************************************************/


#ifndef DOLPHIN_ERRCODES_H
#define DOLPHIN_ERRCODES_H

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <dolphin_cfg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* DEFINES
*******************************************************************************/

//Global error code
extern volatile int32_t g_halerrcode;

typedef int32_t DolphinIC_rval_t;

//General no errors
#define DOLPHINIC_NOERROR 								(0 )

#define DOLPHINIC_EC_CALLFAILED     					(-1)
#define DOLPHINIC_EC_CALLTIMEOUT    					(-2)

//IC to hal layer coupling for 
//different chip variants
#define DOLPHINIC_EC_FUNCNOTEXIST						(-3)

//SPI communication error				
#define DOLPHINIC_EC_SPICRCFAILED						(-4)
#define DOLPHINIC_EC_SPIWRCHKFAILED 					(-5)

//Input paramerter out of range				
#define DOLPHINIC_EC_INPUTOUTOFRANGE					(-6)

//OTP				
#define DOLPHINIC_EC_INVALIDOTP							(-7)
#define DOLPHINIC_EC_OTPNOTREADYTOREAD					(-8)
#define DOLPHINIC_EC_IPNOTACTIVATED     			    (-9)

//Mask version
#define DOLPHINIC_EC_CANNOTGETMASKVERSION				(-10)

//ISM Init errors				
#define DOLPHINIC_EC_INITACT1FAIL						(-11)
#define DOLPHINIC_EC_INITACT2FAIL						(-12)
#define DOLPHINIC_EC_INITACT3FAIL						(-13)
#define DOLPHINIC_EC_INITACT4FAIL						(-14)
#define DOLPHINIC_EC_INITACT5FAIL						(-15)
#define DOLPHINIC_EC_INITACT6FAIL						(-16)
#define DOLPHINIC_EC_INITACT7FAIL						(-17)
#define DOLPHINIC_EC_INITACT8FAIL						(-18)
#define DOLPHINIC_EC_INITACT9FAIL						(-19)
#define DOLPHINIC_EC_INITACT10FAIL						(-20)
#define DOLPHINIC_EC_INITACT11FAIL						(-21)
#define DOLPHINIC_EC_INITACT12FAIL						(-22)
#define DOLPHINIC_EC_INITACT13FAIL						(-23)
#define DOLPHINIC_EC_INITACT14FAIL						(-24)
#define DOLPHINIC_EC_INITACT15FAIL						(-25)
#define DOLPHINIC_EC_INITACT16FAIL						(-26)
#define DOLPHINIC_EC_INITACT17FAIL						(-27)
#define DOLPHINIC_EC_INITACT18FAIL                      (-28)

//ADC
#define DOLPHINIC_EC_ADCPOWERONFAIL						(-29)
#define DOLPHINIC_EC_ADCRECALIBFAIL						(-30)
#define DOLPHINIC_EC_ADCRECALIBTIMEOUT					(-31)

//Data pattern test				
#define DOLPHINIC_EC_DATAPTTRNTESTFAIL					(-32)

//ISM internal FIT				
#define DOLPHINIC_EC_ISMFITFAIL							(-33)

//Calibration Errors				
#define DOLPHINIC_EC_LOGAINCALFAIL						(-34)
#define DOLPHINIC_EC_TXGAINCALFAIL						(-35)

//FIT				
#define DOLPHINIC_EC_TXSENSORFITFAIL					(-36)
#define DOLPHINIC_EC_CAFCMINSENSORFITFAIL				(-37)
#define DOLPHINIC_EC_CAFCUNLOCKSENSORFITFAIL			(-38)

//Recovery
#define DOLPHINIC_EC_STATUSWARNINGRECOVERFAIL			(-39)

//Interface toggeling test
#define DOLPHINIC_EC_INTFTOGGLETESTFAIL					(-40)

//Shadow register check
#define DOLPHINIC_EC_SHDWREGCHECKFAIL					(-41)

//fault injection error
#define DOLPHINIC_EC_FAULTINJECTIONRFAIL			    (-42)

//subband selection
#define DOLPHINIC_EC_SUBBANDSELECT_BS_FAIL				(-43)
#define DOLPHINIC_EC_SUBBANDNOTFOUND                    (-44)

//MCLK
#define DOLPHINIC_EC_MCLKINTEGRITYFAILED				(-45)
#define DOLPHINIC_EC_MCLKRECALIBFAILED					(-46)

//ATB
#define DOLPHINIC_EC_ATBADCREADFAIL						(-47)


//Time out errors
#define DOLPHINIC_EC_CSI2_PLL_LOCK_TIMEOUT				(-48)
#define DOLPHINIC_EC_MCLK_FREQ_CNT_TIMEOUT				(-49)
#define DOLPHINIC_EC_CAFC_FREQ_CNT_TIMEOUT				(-50)


//
#define DOLPHINIC_EC_ERROR_FLAG_MODE                    (-51)

#define DOLPHINIC_SEND_PROFILE2_TEST_FAIL               (-100)
#define DOLPHINIC_SEND_PROFILE01_TEST_FAIL              (-101)
#define DOLPHINIC_SEND_PROFILE3_TEST_FAIL               (-102)

#if defined(DOLPHIN_CFG_CHECK_ERRORCODE)

#define HAL_GERRCODE_INIT (g_halerrcode = DOLPHINIC_NOERROR)

#define HAL_GERRCODE (g_halerrcode)

//Assert, otherwise exit a function with error codes
#define HAL_GEC_ASSERT(__EXP_ERR_CODE__) \
    if( g_halerrcode != __EXP_ERR_CODE__ ) { \
    DbgErr("Err %s:%d ErrCode(%d) \n", __FUNCTION__,__LINE__,g_halerrcode); return HAL_GERRCODE; \
	    }

//Assign error code and exit a function
#define HAL_GEC_FUNEXIT(__ERR_CODE__) \
	    { g_halerrcode = __ERR_CODE__; \
    DbgErr("Err %s:%d ErrCode(%d) \n", __FUNCTION__,__LINE__,g_halerrcode); return HAL_GERRCODE; \
	    }

//Generalize to one simple error, when there can be multiple reasons of errors in a function, and the exact error code is not important.
#define HAL_GEC_CHKFUNEXIT(__EXP_ERR_CODE__) \
	if( g_halerrcode != DOLPHINIC_NOERROR ) { \
	DbgErr("Err %s:%d, actual ErrCode(%d), generalized ErrCode(%d) \n", __FUNCTION__, __LINE__, g_halerrcode, __EXP_ERR_CODE__); return __EXP_ERR_CODE__; \
		}

#else

#define HAL_GERRCODE_INIT (g_halerrcode = DOLPHINIC_NOERROR)

#define HAL_GERRCODE (g_halerrcode)

#define HAL_GEC_HANDLER __SHORT_JUMP_ERR_EXCEPTION__

#define HAL_GEC_ASSERT(__EXP_ERR_CODE__) \
    if( g_halerrcode != __EXP_ERR_CODE__ ) { \
    return HAL_GERRCODE; \
	    }

#define HAL_GEC_FUNEXIT(__ERR_CODE__) \
	    { g_halerrcode = __ERR_CODE__; return HAL_GERRCODE; }

#define HAL_GEC_CHKFUNEXIT(__EXP_ERR_CODE__) \
	if( g_halerrcode != DOLPHINIC_NOERROR ) { \
	 return __EXP_ERR_CODE__; \
			}
#endif



#ifdef __cplusplus
}
#endif

#endif /* DOLPHIN_ERRCODES_H */
