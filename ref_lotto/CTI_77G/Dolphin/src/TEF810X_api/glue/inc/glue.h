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
* @file glue.h
*
* @Dolphin Low Level APIs - GLUE/Wrapper abstraction layer to interface with external Platform APIs.
*
******************************************************************************/

#ifndef __GLUE_H__
#define __GLUE_H__

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <dolphinIC.h>
#include <dolphin_errcodes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/******************************************************************************
* DEFINES
*******************************************************************************/
DolphinIC_rval_t glue_reg_ProbeSPIWrite( void * pv_arg1 );

DolphinIC_rval_t glue_reg_Write(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReturnedData);

DolphinIC_rval_t glue_reg_BurstWrite(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData);

DolphinIC_rval_t glue_reg_Read(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint32_t *ReturnedData);

DolphinIC_rval_t glue_reg_BurstRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData);

DolphinIC_rval_t glue_reg_WriteCheck(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, const uint32_t * ExpData);

DolphinIC_rval_t glue_reg_WriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReadData, bool CS_Mode, uint32_t *ReturnedData);

DolphinIC_rval_t glue_reg_BurstWriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint32_t *ReadData, uint8_t NumWords, bool CS_Mode, bool SR_Mode, bool LoopBack, uint32_t *ReturnedData);

void glue_Sleep( float ticksInMilliSec );
void glue_SetGPIO( dolphin_ExtPinID_t en_pid , bool val );
void glue_GetGPIO( dolphin_ExtPinID_t en_pid , bool * val );

DolphinIC_rval_t glue_SystemReset( void );

void glue_CaptureHostTrigger( void );
bool glue_CaptureTestPattern( void );
bool glue_CheckTestPattern( void );

// function to record a start time reference point. To be used in pairs with glue_Toc(). Do not use in nested way.
void glue_Tic();
// function to record a stop time ref point, and return the duration between start and stop point. To be used in pairs with glue_Tic(). Do not use in nested way.
float glue_Toc();


#ifdef DOLPHIN_CFG_HOST_OPALKELLY
void CfgChirping(uint8_t n_partcycles, uint16_t *n_chirps, uint32_t *cycleDelayMilliSec);
void CfgFPGASPICmdMode();
uint32_t DataCapture_Mem(uint32_t * p_rawframebuff, uint16_t * p_decframebuff, uint32_t number_of_chirps, uint32_t samples_per_chirp);
void setCSI2_OK(uint16_t numLanes);
void DataCapture_Start(void);
#else
	void glue_usecSleep( uint32_t ticksInUSec );
#endif // DOLPHIN_CFG_HOST_OPALKELLY

#if defined(__cplusplus)
}
#endif

#endif /* __GLUE_H__ */
