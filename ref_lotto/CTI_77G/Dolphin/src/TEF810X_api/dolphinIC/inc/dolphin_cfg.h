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
* @file dolphin_cfg.h
*
* @ver vX.Y.Z 
*
* @author
*
* @date
*
* @brief dolphinIC configuration
*
*
******************************************************************************/


#ifndef DOLPHIN_CFG_H
#define DOLPHIN_CFG_H

/******************************************************************************
* INCLUDES
*****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* DEFINES
*******************************************************************************/

//Enable one or both option.
//When only one is enabled, only one Dolphin variant is supported.
//When both are enabled, the API will detect Dolphin variant automatically and do the initialization accordingly.
//#define DOLPHIN_CFG_ES2
#define DOLPHIN_CFG_ES3


#if defined(S32R274) || defined(S32R372)
#define DOLPHIN_CFG_HOST_S32R274
// #ifdef C2_MODULE     //Customer 2 module configuration
// #define NO_DEBUG_PRINTS
// #else
// #define READY_INT_CFG		//Added define for using Ready Int interrupt
// #endif
#define ADC_CAL_TIMEOUT_MS (6.0f)
//numbers depend on SPI speed and actual loop condition.
//0.1ms works with 10MHz SPI speed with NXP SPI glue driver.
#define CSI2_PLL_READY_TIMEOUT_MS (0.6f)	//Needs to be rechecked as it seems to change from sample to sample
#define CAFC_FREQ_CNT_TIMEOUT_MS (0.1f)
#define CSI2_FREQ_CNT_TIMEOUT_MS (0.1f)
#define LVDS_FREQ_CNT_TIMEOUT_MS (0.1f)
#define CIF_FREQ_CNT_TIMEOUT_MS  (0.1f)
#define CP_REPLICA_DELAY_MS (0.02f)		//Necessary time for the CP replica current to be disabled at chirp start. DO NOT change
#define SPI_WR_MS (0.007f)				//Time that it takes to execute a single spi_wr with current spi_driver. Modify according to your driver.
#else
#define DOLPHIN_CFG_HOST_OPALKELLY
#define ADC_CAL_TIMEOUT_MS (20.0f)
#define CSI2_PLL_READY_TIMEOUT_MS (20.0f)

//frequency counter timeouts are made very large for OK platform
//since repeated read can reduce FPGA+PC SPI speed.
#define CAFC_FREQ_CNT_TIMEOUT_MS (100.0f)
#define CSI2_FREQ_CNT_TIMEOUT_MS (100.0f)
#define LVDS_FREQ_CNT_TIMEOUT_MS (100.0f)
#define CIF_FREQ_CNT_TIMEOUT_MS (100.0f)
#endif


#if defined(DOLPHIN_CFG_ES3)
#define DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE
#endif

#define DOLPHIN_CFG_CHECK_ERRORCODE (1)

// use binary search for subband caliration and selection or not
//#define SB_BINARYSEARCH_ENABLE    //uncomment this line if want to use Binary search for subband selection [not yet working on RR platform!]

// 1: CSI_2 output unsigned; 0: output signed
// for NXP varioius demos, unsigned is used.
#define MAKE_CSI2_OUTPUT_UNSIGNED (0)
// #define MAKE_CSI2_OUTPUT_UNSIGNED (1)

//=========================================== FSM Defaults ====================================================

#if defined( DOLPHIN_CFG_HOST_S32R274 )

//Enable this when building for RR-Ultra Host ...
#define NXP_TEF810X_CPU_BIG_ENDIAN (0x01)

//--------------------------------------------- Should Match with Host CSI-2 RX Cfg----------------------------
#define DOLPHIN_CFG_FSM_CSI2_NLANES         ( 0x01 )   // == MIPI_NUM_LANES MIPI_LANE2 ( RR-Host )
#define DOLPHIN_CFG_FSM_CSI2_DATARATE       ( 0x01 )   // == MIPI_DATA_RATE MBITS_240
//#define DOLPHIN_CFG_FSM_CSI2_NLANES         ( 0x03 )   // == MIPI_NUM_LANES MIPI_LANE2 ( RR-Host )
//#define DOLPHIN_CFG_FSM_CSI2_DATARATE       ( 0x00 )   // == MIPI_DATA_RATE MBITS_240
#define DOLPHIN_CFG_FSM_CSI2_DATAPATTERN    ( 0x5AB )  // Test Data Pattern

#define DOLPHIN_CFG_FSM_TESTPROF3           ( 0x03 )  // Test Mode profile = 0x03
#define DOLPHIN_CFG_FSM_PROF3_NCHIRPS       ( 64 )    // Number of Chirps
#define DOLPHIN_CFG_FSM_PROF3_NSAMPLES      ( 2048 )  // Number of Samples
#define DOLPHIN_CFG_FSM_PROF3_DEC_FACT      ( 4 )     // Decimation factor 2^2 = 4 (2014/4) = 512

//------------------------------ Chirp Timing params ----------------------------------------------------------
#define DOLPHIN_CFG_FSM_PROF3_NSEQ          (1)       // Number of Sequence
#define DOLPHIN_CFG_FSM_PROF3_SEQINTVL      (1)       // Sequence interval
#define DOLPHIN_CFG_FSM_PROF3_JUMPBACKTIME  (0.25)    // JumpBack time
#define DOLPHIN_CFG_FSM_PROF3_DWELLTIME     (10)
#define DOLPHIN_CFG_FSM_PROF3_RESETTIME     (5)
#define DOLPHIN_CFG_FSM_PROF3_SETTLETIME    (10)
#define DOLPHIN_CFG_FSM_PROF3_TXPON         (0x01)
#define DOLPHIN_CFG_FSM_PROF3_TXSW          (0x01)
#define DOLPHIN_CFG_FSM_PROF3_TXBPS         (0x00)
#define DOLPHIN_CFG_FSM_PROF3_RXPON         (0x04)

#elif defined( DOLPHIN_CFG_HOST_OPALKELLY )

//Enable this when building for Windows/OK Host ...
#define NXP_TEF810X_CPU_LITTLE_ENDIAN (0x01)

//--------------------------------------------- Should Match with Host CSI-2 RX Cfg----------------------------
#define DOLPHIN_CFG_FSM_CSI2_NLANES         ( 0x03 ) // 4-Lanes
#define DOLPHIN_CFG_FSM_CSI2_DATARATE       ( 0x01 ) // 480Mbps
#define DOLPHIN_CFG_FSM_CSI2_DATAPATTERN    ( 0x5AB )

#define DOLPHIN_CFG_FSM_TESTPROF3           ( 0x03 )
#define DOLPHIN_CFG_FSM_PROF3_NCHIRPS       ( 64 )
#define DOLPHIN_CFG_FSM_PROF3_NSAMPLES      ( 2048 )
#define DOLPHIN_CFG_FSM_PROF3_DEC_FACT      ( 4 )

#define DOLPHIN_CFG_FSM_PROF3_NSEQ          (1)
#define DOLPHIN_CFG_FSM_PROF3_SEQINTVL      (1)
#define DOLPHIN_CFG_FSM_PROF3_JUMPBACKTIME  (0.25)
#define DOLPHIN_CFG_FSM_PROF3_DWELLTIME     (10)
#define DOLPHIN_CFG_FSM_PROF3_RESETTIME     (5)
#define DOLPHIN_CFG_FSM_PROF3_SETTLETIME    (10)
#define DOLPHIN_CFG_FSM_PROF3_TXPON         (0x01)
#define DOLPHIN_CFG_FSM_PROF3_TXSW          (0x01)
#define DOLPHIN_CFG_FSM_PROF3_TXBPS         (0x00)
#define DOLPHIN_CFG_FSM_PROF3_RXPON         (0x04)

#endif

//--------------------------------------------- Register Shadow Enable/Diable ----------------------------

// #define DOLPHIN_CFG_FSM_RSHD_CCTRL  (0x01)
// #define DOLPHIN_CFG_FSM_RSHD_LVDS   (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_CSI2   (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_CIF    (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_TENG   (0x01)
// #define DOLPHIN_CFG_FSM_RSHD_SCTRL  (0x01)
// #define DOLPHIN_CFG_FSM_RSHD_CAFC   (0x01)
// #define DOLPHIN_CFG_FSM_RSHD_ADC    (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_GBIAS  (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_LOINTF (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_MCLK   (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_RX     (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_TX     (0x01)
// #define DOLPHIN_CFG_FSM_RSHD_SSBMOD (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_GLDO   (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_ATB    (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_OTP    (0x00)
// #define DOLPHIN_CFG_FSM_RSHD_ISM    (0x01)
#define DOLPHIN_CFG_FSM_RSHD_CCTRL  (0x00)
#define DOLPHIN_CFG_FSM_RSHD_LVDS   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_CSI2   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_CIF    (0x00)
#define DOLPHIN_CFG_FSM_RSHD_TENG   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_SCTRL  (0x00)
#define DOLPHIN_CFG_FSM_RSHD_CAFC   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_ADC    (0x00)
#define DOLPHIN_CFG_FSM_RSHD_GBIAS  (0x00)
#define DOLPHIN_CFG_FSM_RSHD_LOINTF (0x00)
#define DOLPHIN_CFG_FSM_RSHD_MCLK   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_RX     (0x00)
#define DOLPHIN_CFG_FSM_RSHD_TX     (0x00)
#define DOLPHIN_CFG_FSM_RSHD_SSBMOD (0x00)
#define DOLPHIN_CFG_FSM_RSHD_GLDO   (0x00)
#define DOLPHIN_CFG_FSM_RSHD_ATB    (0x00)
#define DOLPHIN_CFG_FSM_RSHD_OTP    (0x00)
#define DOLPHIN_CFG_FSM_RSHD_ISM    (0x00)

//=========================================== End (FSM Defaults)===============================================


#ifdef __cplusplus
}
#endif

#endif /* DOLPHIN_CFG_H */
