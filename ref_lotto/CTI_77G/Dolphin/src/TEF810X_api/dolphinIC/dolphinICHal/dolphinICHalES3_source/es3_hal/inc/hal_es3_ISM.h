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
* @file hal_es3_ISM.h
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief ISM Low-Level Interface.
*
*
******************************************************************************/
#ifdef DOLPHIN_CFG_ES3

#ifndef HAL_ES3_ISM_H
#define HAL_ES3_ISM_H

//****************Error ID for fault injection*******************
#define supply_high_error_global_ldo_1v1 0x14000000
#define supply_low_error_global_ldo_1v1  0x12000000
#define supply_high_error_global_ldo_1v8 0x11000000
#define supply_low_error_global_ldo_1v8  0x10800000
#define supply_low_error_chirp_dig_1v1   0x10400000
#define supply_low_error_chirp_vco_1v8   0x10200000
#define supply_low_error_chirp_pll_1v8   0x10100000
#define supply_low_error_ser_1v8         0x10080000
#define supply_low_error_csi2_1v1        0x10040000
#define supply_low_error_ser_1v1         0x10020000
#define supply_low_error_global_bias_1v8 0x10010000
#define supply_low_error_ssb_mod_1v8     0x10008000
#define supply_low_error_interface_1v1   0x10004000
#define supply_low_error_adc34_1v1       0x10002000
#define supply_low_error_adc12_1v1       0x10001000
#define supply_low_error_mc_1v8          0x10000800
#define supply_low_error_rx4_1v8         0x10000400
#define supply_low_error_rx3_1v8         0x10000200
#define supply_low_error_rx2_1v8         0x10000100
#define supply_low_error_rx1_1v8         0x10000080
#define supply_low_error_rx4_1v1         0x10000040
#define supply_low_error_rx3_1v1         0x10000020
#define supply_low_error_rx2_1v1         0x10000010
#define supply_low_error_rx1_1v1         0x10000008
#define supply_low_error_tx3_1v8         0x10000004
#define supply_low_error_tx2_1v8         0x10000002
#define supply_low_error_tx1_1v8         0x10000001

#define rf_max_error_tx3                 0x20020000
#define rf_max_error_tx2                 0x20010000
#define rf_max_error_tx1                 0x20008000
#define rf_high_error_tx3                0x20004000
#define rf_high_error_tx2                0x20002000
#define rf_high_error_tx1                0x20001000
#define rf_low_error_tx3                 0x20000800
#define rf_low_error_tx2                 0x20000400
#define rf_low_error_tx1                 0x20000200
#define rf_min_error_tx3                 0x20000100
#define rf_min_error_tx2                 0x20000080
#define rf_min_error_tx1                 0x20000040
#define temp_error_tx3                   0x20000020
#define temp_error_tx2                   0x20000010
#define temp_error_tx1                   0x20000008
#define bb_error_tx3                     0x20000004
#define bb_error_tx2                     0x20000002
#define bb_error_tx1                     0x20000001

#define lo_max_error_rx4                0x30080000
#define lo_max_error_rx3                0x30040000
#define lo_max_error_rx2                0x30020000
#define lo_max_error_rx1                0x30010000
#define lo_high_error_rx4               0x30008000
#define lo_high_error_rx3               0x30004000
#define lo_high_error_rx2               0x30002000
#define lo_high_error_rx1               0x30001000
#define lo_low_error_rx4                0x30000800
#define lo_low_error_rx3                0x30000400
#define lo_low_error_rx2                0x30000200
#define lo_low_error_rx1                0x30000100
#define lo_min_error_rx4                0x30000080
#define lo_min_error_rx3                0x30000040
#define lo_min_error_rx2                0x30000020
#define lo_min_error_rx1                0x30000010
#define bb_error_rx4                    0x30000008
#define bb_error_rx3                    0x30000004
#define bb_error_rx2                    0x30000002
#define bb_error_rx1                    0x30000001

#define interface_stuck_chirp         0x40002000
#define vco_freq_480_error_chirp      0x40000200
#define level_max_error_chirp         0x40000100
#define level_min_error_chirp         0x40000080
#define level_high_error_chirp        0x40000040
#define level_low_error_chirp         0x40000020
#define vtune_high_error_chirp        0x40000010
#define vtune_low_error_chirp         0x40000008
#define max_temp_error_chirp          0x40000004
#define unlock_error_chirp            0x40000002
#define lock_step_error_chirp         0x40000001

#define rd_crc                       0x50020000
#define wr_crc                       0x50010000
#define jtag_active_set              0x50001000
#define bb_error_interface           0x50000100
#define dig_freq_error_masterclk     0x50000008
#define mc_pll_lock_error            0x50000004
#define mc_pll_level_error           0x50000002
#define mc_pll_freq_cal              0x5_0000001


#define adc4_hard_clipping_error           0x68000000
#define adc3_hard_clipping_error           0x64000000
#define adc2_hard_clipping_error           0x62000000
#define adc1_hard_clipping_error           0x61000000
#define adc4_hard_clipping_persistent      0x60800000
#define adc3_hard_clipping_persistent      0x60400000
#define adc2_hard_clipping_persistent      0x60200000
#define adc1_hard_clipping_persistent      0x60100000
#define adc4_clipping                      0x60080000
#define adc3_clipping                      0x60040000
#define adc2_clipping                      0x60020000
#define adc1_clipping                      0x60010000
#define adc4_clipping_persistent           0x60008000
#define adc3_clipping_persistent           0x60004000
#define adc2_clipping_persistent           0x60002000
#define adc1_clipping_persistent           0x60001000
#define adc4_near_clipping                 0x60000800
#define adc3_near_clipping                 0x60000400
#define adc2_near_clipping                 0x60000200
#define adc1_near_clipping                 0x60000100
#define adc4_near_clipping_persistent      0x60000080
#define adc3_near_clipping_persistent      0x60000040
#define adc2_near_clipping_persistent      0x60000020
#define adc1_near_clipping_persistent      0x60000010
#define adc4_cal_error_persistent          0x60000008
#define adc3_cal_error_persistent          0x60000004
#define adc2_cal_error_persistent          0x60000002
#define adc1_cal_error_persistent          0x60000001


/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdint.h>


#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

/******************************************************************************
* DEFINES
*******************************************************************************/

/**
@brief This API executes Fault Injection Test for the ISM module itself
**/
DolphinIC_rval_t hal_es3_ISM_FIT(int32_t mode);

/**
@brief This API configures all related IPs and executes the data pattern test
**/
DolphinIC_rval_t hal_es3_ISM_DataPatternTest(uint16_t patternData, int32_t mode, uint8_t deci);

/**
@brief This API checks the expected output frequency of MCLK
**/
DolphinIC_rval_t hal_es3_ISM_MCLKIntegrityCheck(int32_t mode, float refFreq);

/**
@brief Application reset as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_1( void );

/**
@brief SPI interface integrity check (SPI Loopback Test) as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_2( void );

/**
@brief SPI access test (scratch register) as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_3( void );

/**
@brief OTP Read and check data integrity as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_4( void );

/**
@brief Global LDO Switching as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_5( void );
DolphinIC_rval_t hal_es3_ISM_Init_Act_5(uint32_t IP_PON_Mask);

/**
@brief Turn on and calibrate Global Bias per IP as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_6( void );
DolphinIC_rval_t hal_es3_ISM_Init_Act_6(uint32_t IP_PON_Mask);

/**
@brief Configure local LDOs as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_7(int32_t mode);
DolphinIC_rval_t hal_es3_ISM_Init_Act_7(int32_t mode, uint32_t IP_PON_Mask);

/**
@brief Enable clock and release reset as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_8( void );
DolphinIC_rval_t hal_es3_ISM_Init_Act_8(uint32_t IP_PON_Mask);

/**
@brief IC Calibration as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_9( void );
DolphinIC_rval_t hal_es3_ISM_Init_Act_9(uint32_t IP_PON_Mask);

/**
@brief Configure local bias settings as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_10( void );

/**
@brief Set up Master Clock as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_11(int32_t mode);

/**
@brief Power up all the IPs from PON of CC as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_12( void );
DolphinIC_rval_t hal_es3_ISM_Init_Act_12(uint32_t IP_PON_Mask);

/**
@brief ADC configuration as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_13( void );

/**
@brief Safety sensor configuration as a part of initialization
**/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_14();
DolphinIC_rval_t hal_es3_ISM_Init_Act_14(uint32_t IP_PON_Mask);

/**
@brief Interface toggle test as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_15(uint32_t IP_PON_Mask);


/**
@brief Data interface test part of ISM init

## 1, Init & Cfg the choosed Selializer ( CSI-2 | LVDS | CIF ).
## 2, Call hal_es3_ISM_DataInterfaceTest() internally.

@param[in] mode Serializer Mode ( CSI-2 = 1 | LVDS = 2 | CIF = 3 ).
@param[in] deci Decimation factor ( 1, 2, 4, 8, 16 ).

@retval DolphinIC_rval_t

Note :: 1. Serializer RX of Host needs to be configured before calling this API.
		2. State of TENG register affected.
		3. Data Frame buffer gets over written by Test pattern data.
*/
// DolphinIC_rval_t hal_es3_ISM_Init_Act_16(int32_t mode, uint8_t deci);
DolphinIC_rval_t hal_es3_ISM_Init_Act_16(int32_t mode, uint8_t deci, uint32_t IP_PON_Mask);

/**
@brief ISM FIT Test as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_17(int32_t mode);
/**
@brief ISM GLDO SNS Test as a part of initialization
**/
DolphinIC_rval_t hal_es3_ISM_Init_Act_18();

/**
@brief To AutoCorrect or Calibrate the LO interface B2 gain based on LOW and HIGH status flag
events detected by Status Monitor during active chirp period.

@param[in] None

@return DolphinIC_rval_t
*/
DolphinIC_rval_t hal_es3_ISM_lointf_GainCalibration(void);

/**
@brief To AutoCorrect or Calibrate the LO interface B2 gain based on LOW and HIGH status flag
events detected by Status Monitor during active chirp period and interface Clk/data is disabled from toggling.

@param[in] None
@param[in] mode - 1:CSI-2, 2:LVDS, 3:CIF-MFIO
@return DolphinIC_rval_t
*/
DolphinIC_rval_t hal_es3_ISM_lointf_GainCalibration_Mode(int32_t mode);

/**
@brief To AutoCorrect or Calibrate the TX gain LOW and HIGH
events detected by Status Monitor during active chirp period.

@param[in] txOn - ON/OFF status of TX[0-3], array size should be 0x03.

@return DolphinIC_rval_t
*/
DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration(bool txOn[3], uint8_t profile);
DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration_Cubtek(bool txOn[3], uint8_t profile, uint8_t gain_count[3]);
/**
@brief To AutoCorrect or Calibrate the TX gain LOW and HIGH
events detected by Status Monitor during active chirp period and interface clk/ data is disabled from toggling.

@param[in] txOn - ON/OFF status of TX[0-3], array size should be 0x03.
@param[in] mode - 1:CSI-2, 2:LVDS, 3:CIF-MFIO

@return DolphinIC_rval_t
*/
DolphinIC_rval_t hal_es3_ISM_tx_GainCalibration_Mode(bool txOn[3], uint8_t profile, int32_t mode);

/**
@brief Loopback test on Dolphin Interface PINS.

@param[in] en_pid Interface PIN ID
0x100 : DOLPHIN_EXTPIO_CHIRPSTART
0x200 : DOLPHIN_EXTPO_READYINT
0x300 : DOLPHIN_EXTPO_ERRORN
0x400 : DOLPHIN_EXTPO_ERRORRESET
0x500 : DOLPHIN_PI_TX1PS
0x600 : DOLPHIN_PI_TX2PS
0x700 : DOLPHIN_PI_TX3PS

@return DolphinIC_rval_t
*/
DolphinIC_rval_t hal_es3_ISM_InterfaceToggleTest(int32_t en_pid);


//functions for setting mask and unmask for error sources
DolphinIC_rval_t hal_es3_ISM_MaskSupplyError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskSupplyError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_MaskTxError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskTxError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_MaskRxError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskRxError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_MaskChirpError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskChirpError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_MaskMCLOError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskMCLOError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_MaskADCError( uint32_t arg_mask );
DolphinIC_rval_t hal_es3_ISM_UnMaskADCError( uint32_t arg_mask );

//functions for gettting raw error flags
DolphinIC_rval_t hal_es3_ISM_GetRawMasterErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawSupplyErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawTxErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawRxErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawChirpErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawMCLOErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawADCErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRawRFPowDwnErrorStatus( uint32_t * p_status );

//functions for gettting raw error flags
DolphinIC_rval_t hal_es3_ISM_GetMasterErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetSupplyErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetTxErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRxErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetChirpErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetMCLOErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetADCErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetRFPowDwnErrorStatus( uint32_t * p_status );
DolphinIC_rval_t hal_es3_ISM_GetISMErrorStatus( uint32_t * p_status );

DolphinIC_rval_t hal_es3_ISM_SetMCUReset( void );

//sensor fault injection tests
DolphinIC_rval_t hal_es3_ISM_SwTXFit(uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_Sw_FIT(uint8_t fitProfile, bool TxPON[3]);
DolphinIC_rval_t hal_es3_ISM_SwChirp_Min_error(uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_SwChirp_Unlock_error(uint8_t fitProfile);

//status warning recovery functions
DolphinIC_rval_t hal_es3_ISM_Recover_Tx_Low_Status(uint8_t TX_numb, uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_Tx_High_Status(uint8_t TX_numb, uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_Rx_Low_Status();
DolphinIC_rval_t hal_es3_ISM_Recover_Rx_High_Status();
DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVtune_Low_Status(uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVtune_High_Status(uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVco_Low_Status(uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_ChirpVco_High_Status(uint8_t profile_num);
DolphinIC_rval_t hal_es3_ISM_Recover_Chirp_MaxTemp_Status(uint32_t Cool_time);
DolphinIC_rval_t hal_es3_ISM_Recover_Tx_MaxTemp_Status(uint8_t TX_numb, uint32_t Cool_time);

DolphinIC_rval_t hal_es3_ISM_StatusCheckAndRecover();

//RFBIST
DolphinIC_rval_t hal_es3_ISM_RFBIST_Static_config();
DolphinIC_rval_t hal_es3_ISM_RFBIST_LnaTest();
DolphinIC_rval_t hal_es3_ISM_RFBIST_MixerTest();
DolphinIC_rval_t hal_es3_ISM_Recover_RfBist_changes();

DolphinIC_rval_t hal_es3_ISM_InjectChirp_Unlock_Vco480_error(uint32_t Error_ID ,uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_InjectChirp_Min_DigLockStep_error(uint32_t Error_ID, uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_InjectChirp_Max_error(uint8_t fitProfile);

DolphinIC_rval_t hal_es3_ISM_InjectTX_Max_error(uint8_t Module_ID,uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_InjectTX_Min_error(uint8_t Module_ID,uint8_t fitProfile);

DolphinIC_rval_t hal_es3_ISM_Inject_Rx_Min_error(uint8_t Module_ID);
DolphinIC_rval_t hal_es3_ISM_Inject_Rx_Max_error(uint8_t Module_ID);

DolphinIC_rval_t hal_es3_ISM_Inject_MC_PllLock_PllLevel_error(uint32_t Error_ID);

DolphinIC_rval_t hal_es3_ISM_Inject_error(uint32_t Error_ID, uint8_t fitProfile);

DolphinIC_rval_t hal_es3_ISM_UnMask_All_error();

DolphinIC_rval_t hal_es3_ISM_Recover_error_FunRst(uint32_t Error_ID);
DolphinIC_rval_t hal_es3_ISM_Recover_error(uint32_t Error_ID, uint8_t fitProfile);
DolphinIC_rval_t hal_es3_ISM_Init_FlagMonitoring();
DolphinIC_rval_t hal_es3_ISM_GLDO_SNS();

DolphinIC_rval_t hal_es3_ISM_MaskErrPONDisabledModule(uint32_t IP_PON_Mask);


#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* HAL_ES3_CCTRL_H */

#endif //DOLPHIN_CFG_ES3

