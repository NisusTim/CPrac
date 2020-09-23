/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2017                                                   */
/*                                                                              */
/* All rights are reserved. Reproduction in whole or in part is prohibited      */
/* without the prior written consent of the copy-right owner.                   */
/* This source code and any compilation or derivative thereof is the sole       */
/* property of NXP B.V. and is provided pursuant to a Software License          */
/* Agreement. This code is the proprietary information of NXP B.V. and          */
/* is confidential in nature. Its use and dissemination by any party other      */
/* than NXP B.V. is strictly limited by the confidential information            */
/* provisions of the agreement referenced above.                                */
/*                                                                              */
/* Right to make changes                                                        */
/* NXP reserves the right to make changes without notice at any time.           */
/*                                                                              */
/* Content correctness                                                          */
/* NXP guaratee the  correctness of this  header  file  against  the reference  */
/* TEF810x_Registermap_v28.xlsx. This header file correctness is guaranteed      */
/* through a header file validation approach. The methods used and the          */
/* validation results will be shared  to the customer to use it as an evidence  */
/* in their safety case                                                         */
/*------------------------------------------------------------------------------*/
/**
* @NXP_TEF810X_Tx.h
*/
#ifndef NXP_TEF810X_TX_H
#define NXP_TEF810X_TX_H
#include "Std_Types.h"

#define TX1_MODULE_ADDRESS 0x11
#define TX2_MODULE_ADDRESS 0x12
#define TX3_MODULE_ADDRESS 0x13
/**
*NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16
* RegisterName: MOD11_g_tx_gain_profile0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000080
*/
#define NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE0_U16
* RegisterName: MOD11_g_lox3_gain_profile0
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x000000A8
*/
#define NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE0_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16
* RegisterName: MOD11_g_tx_gain_profile1
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000080
*/
#define NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE1_U16
* RegisterName: MOD11_g_lox3_gain_profile1
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x000000A8
*/
#define NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE1_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16
* RegisterName: MOD11_g_tx_gain_profile2
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000080
*/
#define NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE2_U16
* RegisterName: MOD11_g_lox3_gain_profile2
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x000000A8
*/
#define NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE2_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16
* RegisterName: MOD11_g_tx_gain_profile3
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000080
*/
#define NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE3_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE3_U16
* RegisterName: MOD11_g_lox3_gain_profile3
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x000000A8
*/
#define NXP_TEF810X_MOD11_G_LOX3_GAIN_PROFILE3_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16
* RegisterName: MOD11_funcsafe_mon_level_rf
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x0F0C0800
*/
#define NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD11_BBD_CONFIG_U16
* RegisterName: MOD11_bbd_config
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD11_BBD_CONFIG_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD11_TS_SEL_U16
* RegisterName: MOD11_ts_sel
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_TS_SEL_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD11_RMS_CONTROL_U16
* RegisterName: MOD11_rms_control
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000010
*/
#define NXP_TEF810X_MOD11_RMS_CONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD11_TX_CONTROL_U16
* RegisterName: MOD11_tx_control
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_TX_CONTROL_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD11_SNS_TOP_CONTROL_U16
* RegisterName: MOD11_sns_top_control
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_SNS_TOP_CONTROL_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD11_TS_PD_U16
* RegisterName: MOD11_ts_pd
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_TS_PD_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD11_RMS_CAL_U16
* RegisterName: MOD11_rms_cal
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x10000000
*/
#define NXP_TEF810X_MOD11_RMS_CAL_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD11_DEBUG_TEST_U16
* RegisterName: MOD11_debug_test
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000CAA
*/
#define NXP_TEF810X_MOD11_DEBUG_TEST_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD11_PHASESHIFTER_STATUS_U16
* RegisterName: MOD11_phaseshifter_status
* AccessMode: READ
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000003
*/
#define NXP_TEF810X_MOD11_PHASESHIFTER_STATUS_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD11_ATB_DELAY_TIMER_U16
* RegisterName: MOD11_atb_delay_timer
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00001F1F
*/
#define NXP_TEF810X_MOD11_ATB_DELAY_TIMER_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD11_ATB1_U16
* RegisterName: MOD11_atb1
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_ATB1_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD11_ATB2_U16
* RegisterName: MOD11_atb2
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_ATB2_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD11_TEST_ERROR_FLAG_STATUS_U16
* RegisterName: MOD11_test_error_flag_status
* AccessMode: READ
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD11_TEST_ERROR_FLAG_STATUS_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD11_MODULEID_U16
* RegisterName: MOD11_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00112201
*/
#define NXP_TEF810X_MOD11_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN
/**
* Nxp_Tef810x_Mod11_G_TX_GAIN_PROFILEBits_t
* RegisterName: g_tx_gain_profile
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: g_tx_gain_profile0
	* Description: TX gain control for profile0
	*/
    uint32 GTxGainProfile0: 8;        /*## attribute GTxGainProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_GTxGainProfileBits_t;
    /**
* Nxp_Tef810x_Mod11_G_LOX3_GAIN_PROFILEBits_t
* RegisterName: g_lox3_gain_profile
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: g_lox3_gain_profile0
	* Description: Bias calibration control into the LOx3 for profile 0
	* <7:4> : PTAT control
	* <3:0> : BG control
	*/
    uint32 GLox3GainProfile0: 8;        /*## attribute GLox3GainProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_GLox3GainProfileBits_t;
    /**
* Nxp_Tef810x_Mod11_FUNCSAFE_MON_LEVEL_RFBits_t
* RegisterName: funcsafe_mon_level_rf
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: level_rf_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage), only lower 4 bits are used: 
	* V_thresh = 139mV + Bitcode*39.8mV
	* This value comes from OTP
	*/
    uint32 LevelRfMinSpi: 6;        /*## attribute LevelRfMinSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: level_rf_low_spi
	* Description: Low trigger level for Gain Control, only lower 4 bits are used: V_thresh = 139mV + Bitcode*39.8mV
	*/
    uint32 LevelRfLowSpi: 6;        /*## attribute LevelRfLowSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: level_rf_high_spi
	* Description: High trigger level for Gain Control, only lower 4 bits are used: V_thresh = 139mV + Bitcode*39.8mV
	*/
    uint32 LevelRfHighSpi: 6;        /*## attribute LevelRfHighSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: level_rf_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage), only lower 4 bits are used: 
	* V_thresh = 139mV + Bitcode*39.8mV
	* This value comes from OTP
	*/
    uint32 LevelRfMaxSpi: 6;        /*## attribute LevelRfMaxSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod11_FuncsafeMonLevelRfBits_t;
    /**
* Nxp_Tef810x_Mod11_BBD_CONFIGBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: bb_grounded_spi
	* Description: Balun grounded control. 
	* 0 = not grounded
	* 1 = grounded
	* Set this based on Balun type
	* Leave as reset if not needed explicitly.
	*/
    uint32 BbGroundedSpi: 1;        /*## attribute BbGroundedSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_idetect_spi
	* Description: Ball break current detection limit. 
	* 1=normal sensitivity (50uA test) 
	* 0=high sensitivity for long differential antenna feed-lines (500uA)
	* Leave as reset if not needed explicitly.
	*/
    uint32 BbIdetectSpi: 1;        /*## attribute BbIdetectSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: bb_en_spi
	* Description: Ball break detector enable. Default is enabled
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 BbEnSpi: 1;        /*## attribute BbEnSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod11_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod11_TS_SELBits_t
* RegisterName: ts_sel
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: ts_sel_spi
	* Description: Temperature threshold selection control. 
	* Inputs to 6x64 decoder
	* sel[5:0] = ?00_0001?
	* => lowest temp. threshold selected
	* sel[5:0] = ?11_1111? =>
	* highest temp. threshold selected
	*/
    uint32 TsSelSpi: 6;        /*## attribute TsSelSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ts_buf_gain_ctrl_spi
	* Description: This control is used to switch the polarity of the temperature sensor buffer.
	*/
    uint32 TsBufGainCtrlSpi: 1;        /*## attribute TsBufGainCtrlSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod11_TsSelBits_t;
    /**
* Nxp_Tef810x_Mod11_RMS_CONTROLBits_t
* RegisterName: rms_control
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: level_rf_enable_spi
	* Description: Enable lo level detector
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 LevelRfEnableSpi: 1;        /*## attribute LevelRfEnableSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 27;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod11_RmsControlBits_t;
    /**
* Nxp_Tef810x_Mod11_TX_CONTROLBits_t
* RegisterName: tx_control
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: en_tx_via_spi
	* Description: Control for Enabling TX. 0=off, 1=on.
	*/
    uint32 EnTxViaSpi: 1;        /*## attribute EnTxViaSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: sw_tx_via_spi
	* Description: Control TX switch by writing the register bit. 0=off, 1=on.
	*/
    uint32 SwTxViaSpi: 1;        /*## attribute SwTxViaSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ps_tx_via_spi
	* Description: Control TX phase by writing the register bit. 0=0? , 1=180?.
	*/
    uint32 PsTxViaSpi: 1;        /*## attribute PsTxViaSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_ps_ext_spi
	* Description: Enable external control(MCU) for phase shifter control
	* 0=disable
	* 1=enable
	* This bit is logical ored with the control from timing engine and the direct control from the IC pin (connected via central control)
	*/
    uint32 EnPsExtSpi: 1;        /*## attribute EnPsExtSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: pon_ls_spi
	* Description: This control bit is used for validation only. Functionally, the pon from central control is used to control the analog level shifters.
	* Leave as reset if not needed explicitly.
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 15;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod11_TxControlBits_t;
    /**
* Nxp_Tef810x_Mod11_SNS_TOP_CONTROLBits_t
* RegisterName: sns_top_control
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: sns_low_pd_spi
	* Description: Powerdown bit of the supply sensor.  0 = normal operation, 1 = powerdown
	* 
	* Set this to '0' always in application
	*/
    uint32 SnsLowPdSpi: 1;        /*## attribute SnsLowPdSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_SnsTopControlBits_t;
    /**
* Nxp_Tef810x_Mod11_TS_PDBits_t
* RegisterName: ts_pd
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: ts_pd_spi
	* Description: Power down control for temperature sensor
	* pd = ?0? => Sensor active
	* pd = ?1? => Sensor in power down
	*/
    uint32 TsPdSpi: 1;        /*## attribute TsPdSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_TsPdBits_t;
    /**
* Nxp_Tef810x_Mod11_RMS_CALBits_t
* RegisterName: rms_cal
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 6;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 2;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 1;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 3;        /*## attribute Reserved9 */
   /**
	* BitsName: level_rf_meas_in_out_spi
	* Description: Select input or output of power detector. 
	* 0=input (DAC), 1=output (RMS detector).
	*/
    uint32 LevelRfMeasInOutSpi: 1;        /*## attribute LevelRfMeasInOutSpi */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 3;        /*## attribute Reserved10 */
}Nxp_Tef810x_Mod11_RmsCalBits_t;
    /**
* Nxp_Tef810x_Mod11_DEBUG_TESTBits_t
* RegisterName: debug_test
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: debug_ibias_pa1_spi
	* Description: Tune the bias current of the PA output stage1
	*/
    uint32 DebugIbiasPa1Spi: 4;        /*## attribute DebugIbiasPa1Spi */
   /**
	* BitsName: debug_ibias_pa2_spi
	* Description: Tune the bias current of the PA output stage2
	*/
    uint32 DebugIbiasPa2Spi: 4;        /*## attribute DebugIbiasPa2Spi */
   /**
	* BitsName: debug_ibias_pa3_spi
	* Description: Tune the bias current of the PA output stage3
	*/
    uint32 DebugIbiasPa3Spi: 4;        /*## attribute DebugIbiasPa3Spi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_DebugTestBits_t;
    /**
* Nxp_Tef810x_Mod11_PHASESHIFTER_STATUSBits_t
* RegisterName: phaseshifter_status
* 
* AddressRange: 0xREAD - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: ps_b1_b0_rb
	* Description: Read back of internal Phase Shifter cascode voltage
	* 
	* off: b0=b1=0 => "00"
	* 0deg: b0=0, b1=1 => "10"
	* 180deg: b0=1, b1=0 => "01"
	*/
    uint32 PsB1B0Rb: 2;        /*## attribute PsB1B0Rb */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_PhaseshifterStatusBits_t;
    /**
* Nxp_Tef810x_Mod11_ATB_DELAY_TIMERBits_t
* RegisterName: atb_delay_timer
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: atb1_counter
	* Description: Timer to implement break before make delay for atb1
	*/
    uint32 Atb1Counter: 8;        /*## attribute Atb1Counter */
   /**
	* BitsName: atb2_counter
	* Description: Timer to implement break before make delay for atb2
	*/
    uint32 Atb2Counter: 8;        /*## attribute Atb2Counter */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_AtbDelayTimerBits_t;
    /**
* Nxp_Tef810x_Mod11_ATB1Bits_t
* RegisterName: atb1
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: atb1_set
	* Description: "Select signal to be measured: 
	* vdda_1v8=8'h1 
	* vdda_1v1=8'h2 
	* vdda_1v1_fs=8'h3 
	* level_pa=8'hd 
	* level_temp=8'he 
	* vref_temp=8'hf 
	* vcas_lox3_1v8=8'h10 
	* vcas_patop_1=8'h12 
	* vcas_patop_2=8'h13 
	* vcas_patop_3=8'h14 
	* vcas_pabot_1=8'h16 
	* vcas_pabot_2=8'h17 
	* vcas_pabot_3=8'h18 
	* vcas_pabot_vref=8'h19 
	* vgg_vga=8'h1b 
	* vgg_ps=8'h1c 
	* vgg_pa1=8'h1d 
	* vgg_pa2=8'h1e 
	* vgg_pa3=8'h1f 
	* ibias_bgr=8'h20 
	* ibias_ptat=8'h21 
	* ibias_bg=8'h22"
	*/
    uint32 Atb1Set: 8;        /*## attribute Atb1Set */
   /**
	* BitsName: atb1_en
	* Description: Enable DC Test Bus
	*/
    uint32 Atb1En: 1;        /*## attribute Atb1En */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_Atb1Bits_t;
    /**
* Nxp_Tef810x_Mod11_ATB2Bits_t
* RegisterName: atb2
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: atb2_set
	* Description: vdda_1v8=8'h1 
	* vdda_1v1=8'h2 
	* vdda_1v1_fs=8'h3 
	* vref_pa_min=8'h9 
	* vref_pa_low=8'ha 
	* vref_pa_high=8'hb 
	* vref_pa_max=8'hc 
	* level_pa=8'hd 
	* level_temp=8'he 
	* vref_temp=8'hf 
	* vcas_lox3_1v8=8'h10 
	* vcas_patop_1=8'h12 
	* vcas_patop_2=8'h13 
	* vcas_patop_3=8'h14 
	* vcas_pabot_1=8'h16 
	* vcas_pabot_2=8'h17 
	* vcas_pabot_3=8'h18 
	* vcas_pabot_vref=8'h19 
	* vgg_vga=8'h1b 
	* vgg_ps=8'h1c 
	* vgg_pa1=8'h1d 
	* vgg_pa2=8'h1e 
	* vgg_pa3=8'h1f 
	* ibias_bgr=8'h20 
	* ibias_ptat=8'h21 
	* ibias_bg=8'h22"
	*/
    uint32 Atb2Set: 8;        /*## attribute Atb2Set */
   /**
	* BitsName: atb2_en
	* Description: Enable DC Test Bus
	*/
    uint32 Atb2En: 1;        /*## attribute Atb2En */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod11_Atb2Bits_t;
    /**
* Nxp_Tef810x_Mod11_TEST_ERROR_FLAG_STATUSBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0xREAD - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_error_flag
	* Description: rf error status = {reliability, level high, level low,  ISM error}
	*/
    uint32 RfErrorFlag: 4;        /*## attribute RfErrorFlag */
   /**
	* BitsName: bbd_error_flag
	* Description: ball break error status
	*/
    uint32 BbdErrorFlag: 1;        /*## attribute BbdErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: temp_error_flag
	* Description: temp error status
	*/
    uint32 TempErrorFlag: 1;        /*## attribute TempErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_low_error_flag
	* Description: supply error status
	*/
    uint32 SupplyLowErrorFlag: 1;        /*## attribute SupplyLowErrorFlag */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 15;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod11_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod11_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision numer i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 8;        /*## attribute Identifier */
}Nxp_Tef810x_Mod11_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod11_GTxGainProfileBits_t
* RegisterName: g_tx_gain_profile
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: g_tx_gain_profile0
	* Description: TX gain control for profile0
	*/
    uint32 GTxGainProfile0: 8;        /*## attribute GTxGainProfile0 */
}Nxp_Tef810x_Mod11_GTxGainProfileBits_t;
    /**
* Nxp_Tef810x_Mod11_GLox3GainProfileBits_t
* RegisterName: g_lox3_gain_profile
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x000000A8
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: g_lox3_gain_profile0
	* Description: Bias calibration control into the LOx3 for profile 0
	* <7:4> : PTAT control
	* <3:0> : BG control
	*/
    uint32 GLox3GainProfile0: 8;        /*## attribute GLox3GainProfile0 */
}Nxp_Tef810x_Mod11_GLox3GainProfileBits_t;
    /**
* Nxp_Tef810x_Mod11_FuncsafeMonLevelRfBits_t
* RegisterName: funcsafe_mon_level_rf
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x0F0C0800
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: level_rf_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage), only lower 4 bits are used: 
	* V_thresh = 139mV + Bitcode*39.8mV
	* This value comes from OTP
	*/
    uint32 LevelRfMaxSpi: 6;        /*## attribute LevelRfMaxSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: level_rf_high_spi
	* Description: High trigger level for Gain Control, only lower 4 bits are used: V_thresh = 139mV + Bitcode*39.8mV
	*/
    uint32 LevelRfHighSpi: 6;        /*## attribute LevelRfHighSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: level_rf_low_spi
	* Description: Low trigger level for Gain Control, only lower 4 bits are used: V_thresh = 139mV + Bitcode*39.8mV
	*/
    uint32 LevelRfLowSpi: 6;        /*## attribute LevelRfLowSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: level_rf_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage), only lower 4 bits are used: 
	* V_thresh = 139mV + Bitcode*39.8mV
	* This value comes from OTP
	*/
    uint32 LevelRfMinSpi: 6;        /*## attribute LevelRfMinSpi */
}Nxp_Tef810x_Mod11_FuncsafeMonLevelRfBits_t;
    /**
* Nxp_Tef810x_Mod11_BbdConfigBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00000100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_en_spi
	* Description: Ball break detector enable. Default is enabled
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 BbEnSpi: 1;        /*## attribute BbEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: bb_idetect_spi
	* Description: Ball break current detection limit. 
	* 1=normal sensitivity (50uA test) 
	* 0=high sensitivity for long differential antenna feed-lines (500uA)
	* Leave as reset if not needed explicitly.
	*/
    uint32 BbIdetectSpi: 1;        /*## attribute BbIdetectSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: bb_grounded_spi
	* Description: Balun grounded control. 
	* 0 = not grounded
	* 1 = grounded
	* Set this based on Balun type
	* Leave as reset if not needed explicitly.
	*/
    uint32 BbGroundedSpi: 1;        /*## attribute BbGroundedSpi */
}Nxp_Tef810x_Mod11_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod11_TsSelBits_t
* RegisterName: ts_sel
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ts_buf_gain_ctrl_spi
	* Description: This control is used to switch the polarity of the temperature sensor buffer.
	*/
    uint32 TsBufGainCtrlSpi: 1;        /*## attribute TsBufGainCtrlSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ts_sel_spi
	* Description: Temperature threshold selection control. 
	* Inputs to 6x64 decoder
	* sel[5:0] = ?00_0001?
	* => lowest temp. threshold selected
	* sel[5:0] = ?11_1111? =>
	* highest temp. threshold selected
	*/
    uint32 TsSelSpi: 6;        /*## attribute TsSelSpi */
}Nxp_Tef810x_Mod11_TsSelBits_t;
    /**
* Nxp_Tef810x_Mod11_RmsControlBits_t
* RegisterName: rms_control
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: level_rf_enable_spi
	* Description: Enable lo level detector
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 LevelRfEnableSpi: 1;        /*## attribute LevelRfEnableSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod11_RmsControlBits_t;
    /**
* Nxp_Tef810x_Mod11_TxControlBits_t
* RegisterName: tx_control
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: pon_ls_spi
	* Description: This control bit is used for validation only. Functionally, the pon from central control is used to control the analog level shifters.
	* Leave as reset if not needed explicitly.
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_ps_ext_spi
	* Description: Enable external control(MCU) for phase shifter control
	* 0=disable
	* 1=enable
	* This bit is logical ored with the control from timing engine and the direct control from the IC pin (connected via central control)
	*/
    uint32 EnPsExtSpi: 1;        /*## attribute EnPsExtSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ps_tx_via_spi
	* Description: Control TX phase by writing the register bit. 0=0? , 1=180?.
	*/
    uint32 PsTxViaSpi: 1;        /*## attribute PsTxViaSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: sw_tx_via_spi
	* Description: Control TX switch by writing the register bit. 0=off, 1=on.
	*/
    uint32 SwTxViaSpi: 1;        /*## attribute SwTxViaSpi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_tx_via_spi
	* Description: Control for Enabling TX. 0=off, 1=on.
	*/
    uint32 EnTxViaSpi: 1;        /*## attribute EnTxViaSpi */
}Nxp_Tef810x_Mod11_TxControlBits_t;
    /**
* Nxp_Tef810x_Mod11_SnsTopControlBits_t
* RegisterName: sns_top_control
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_low_pd_spi
	* Description: Powerdown bit of the supply sensor.  0 = normal operation, 1 = powerdown
	* 
	* Set this to '0' always in application
	*/
    uint32 SnsLowPdSpi: 1;        /*## attribute SnsLowPdSpi */
}Nxp_Tef810x_Mod11_SnsTopControlBits_t;
    /**
* Nxp_Tef810x_Mod11_TsPdBits_t
* RegisterName: ts_pd
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: ts_pd_spi
	* Description: Power down control for temperature sensor
	* pd = ?0? => Sensor active
	* pd = ?1? => Sensor in power down
	*/
    uint32 TsPdSpi: 1;        /*## attribute TsPdSpi */
}Nxp_Tef810x_Mod11_TsPdBits_t;
    /**
* Nxp_Tef810x_Mod11_RmsCalBits_t
* RegisterName: rms_cal
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x10000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: level_rf_meas_in_out_spi
	* Description: Select input or output of power detector. 
	* 0=input (DAC), 1=output (RMS detector).
	*/
    uint32 LevelRfMeasInOutSpi: 1;        /*## attribute LevelRfMeasInOutSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 6;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 1;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 2;        /*## attribute Reserved9 */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 6;        /*## attribute Reserved10 */
}Nxp_Tef810x_Mod11_RmsCalBits_t;
    /**
* Nxp_Tef810x_Mod11_DebugTestBits_t
* RegisterName: debug_test
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000CAA
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: debug_ibias_pa3_spi
	* Description: Tune the bias current of the PA output stage3
	*/
    uint32 DebugIbiasPa3Spi: 4;        /*## attribute DebugIbiasPa3Spi */
   /**
	* BitsName: debug_ibias_pa2_spi
	* Description: Tune the bias current of the PA output stage2
	*/
    uint32 DebugIbiasPa2Spi: 4;        /*## attribute DebugIbiasPa2Spi */
   /**
	* BitsName: debug_ibias_pa1_spi
	* Description: Tune the bias current of the PA output stage1
	*/
    uint32 DebugIbiasPa1Spi: 4;        /*## attribute DebugIbiasPa1Spi */
}Nxp_Tef810x_Mod11_DebugTestBits_t;
    /**
* Nxp_Tef810x_Mod11_PhaseshifterStatusBits_t
* RegisterName: phaseshifter_status
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000003
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: ps_b1_b0_rb
	* Description: Read back of internal Phase Shifter cascode voltage
	* 
	* off: b0=b1=0 => "00"
	* 0deg: b0=0, b1=1 => "10"
	* 180deg: b0=1, b1=0 => "01"
	*/
    uint32 PsB1B0Rb: 2;        /*## attribute PsB1B0Rb */
}Nxp_Tef810x_Mod11_PhaseshifterStatusBits_t;
    /**
* Nxp_Tef810x_Mod11_AtbDelayTimerBits_t
* RegisterName: atb_delay_timer
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00001F1F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: atb2_counter
	* Description: Timer to implement break before make delay for atb2
	*/
    uint32 Atb2Counter: 8;        /*## attribute Atb2Counter */
   /**
	* BitsName: atb1_counter
	* Description: Timer to implement break before make delay for atb1
	*/
    uint32 Atb1Counter: 8;        /*## attribute Atb1Counter */
}Nxp_Tef810x_Mod11_AtbDelayTimerBits_t;
    /**
* Nxp_Tef810x_Mod11_Atb1Bits_t
* RegisterName: atb1
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: atb1_en
	* Description: Enable DC Test Bus
	*/
    uint32 Atb1En: 1;        /*## attribute Atb1En */
   /**
	* BitsName: atb1_set
	* Description: "Select signal to be measured: 
	* vdda_1v8=8'h1 
	* vdda_1v1=8'h2 
	* vdda_1v1_fs=8'h3 
	* level_pa=8'hd 
	* level_temp=8'he 
	* vref_temp=8'hf 
	* vcas_lox3_1v8=8'h10 
	* vcas_patop_1=8'h12 
	* vcas_patop_2=8'h13 
	* vcas_patop_3=8'h14 
	* vcas_pabot_1=8'h16 
	* vcas_pabot_2=8'h17 
	* vcas_pabot_3=8'h18 
	* vcas_pabot_vref=8'h19 
	* vgg_vga=8'h1b 
	* vgg_ps=8'h1c 
	* vgg_pa1=8'h1d 
	* vgg_pa2=8'h1e 
	* vgg_pa3=8'h1f 
	* ibias_bgr=8'h20 
	* ibias_ptat=8'h21 
	* ibias_bg=8'h22"
	*/
    uint32 Atb1Set: 8;        /*## attribute Atb1Set */
}Nxp_Tef810x_Mod11_Atb1Bits_t;
    /**
* Nxp_Tef810x_Mod11_Atb2Bits_t
* RegisterName: atb2
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: atb2_en
	* Description: Enable DC Test Bus
	*/
    uint32 Atb2En: 1;        /*## attribute Atb2En */
   /**
	* BitsName: atb2_set
	* Description: vdda_1v8=8'h1 
	* vdda_1v1=8'h2 
	* vdda_1v1_fs=8'h3 
	* vref_pa_min=8'h9 
	* vref_pa_low=8'ha 
	* vref_pa_high=8'hb 
	* vref_pa_max=8'hc 
	* level_pa=8'hd 
	* level_temp=8'he 
	* vref_temp=8'hf 
	* vcas_lox3_1v8=8'h10 
	* vcas_patop_1=8'h12 
	* vcas_patop_2=8'h13 
	* vcas_patop_3=8'h14 
	* vcas_pabot_1=8'h16 
	* vcas_pabot_2=8'h17 
	* vcas_pabot_3=8'h18 
	* vcas_pabot_vref=8'h19 
	* vgg_vga=8'h1b 
	* vgg_ps=8'h1c 
	* vgg_pa1=8'h1d 
	* vgg_pa2=8'h1e 
	* vgg_pa3=8'h1f 
	* ibias_bgr=8'h20 
	* ibias_ptat=8'h21 
	* ibias_bg=8'h22"
	*/
    uint32 Atb2Set: 8;        /*## attribute Atb2Set */
}Nxp_Tef810x_Mod11_Atb2Bits_t;
    /**
* Nxp_Tef810x_Mod11_TestErrorFlagStatusBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag
	* Description: supply error status
	*/
    uint32 SupplyLowErrorFlag: 1;        /*## attribute SupplyLowErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: temp_error_flag
	* Description: temp error status
	*/
    uint32 TempErrorFlag: 1;        /*## attribute TempErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: bbd_error_flag
	* Description: ball break error status
	*/
    uint32 BbdErrorFlag: 1;        /*## attribute BbdErrorFlag */
   /**
	* BitsName: rf_error_flag
	* Description: rf error status = {reliability, level high, level low,  ISM error}
	*/
    uint32 RfErrorFlag: 4;        /*## attribute RfErrorFlag */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod11_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod11_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00112201
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 8;        /*## attribute Identifier */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: Major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision numer i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod11_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod11_GTxGainProfileUnion_t
* Nxp_Tef810x_Mod11_GTxGainProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_GTxGainProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_GTxGainProfileUnion_t;
/**
* Nxp_Tef810x_Mod11_GLox3GainProfileUnion_t
* Nxp_Tef810x_Mod11_GLox3GainProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_GLox3GainProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_GLox3GainProfileUnion_t;
/**
* Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t
* Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_FuncsafeMonLevelRfBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t;
/**
* Nxp_Tef810x_Mod11_BbdConfigUnion_t
* Nxp_Tef810x_Mod11_BbdConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_BbdConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_BbdConfigUnion_t;
/**
* Nxp_Tef810x_Mod11_TsSelUnion_t
* Nxp_Tef810x_Mod11_TsSelUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_TsSelBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_TsSelUnion_t;
/**
* Nxp_Tef810x_Mod11_RmsControlUnion_t
* Nxp_Tef810x_Mod11_RmsControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_RmsControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_RmsControlUnion_t;
/**
* Nxp_Tef810x_Mod11_TxControlUnion_t
* Nxp_Tef810x_Mod11_TxControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_TxControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_TxControlUnion_t;
/**
* Nxp_Tef810x_Mod11_SnsTopControlUnion_t
* Nxp_Tef810x_Mod11_SnsTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_SnsTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_SnsTopControlUnion_t;
/**
* Nxp_Tef810x_Mod11_TsPdUnion_t
* Nxp_Tef810x_Mod11_TsPdUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_TsPdBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_TsPdUnion_t;
/**
* Nxp_Tef810x_Mod11_RmsCalUnion_t
* Nxp_Tef810x_Mod11_RmsCalUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_RmsCalBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_RmsCalUnion_t;
/**
* Nxp_Tef810x_Mod11_DebugTestUnion_t
* Nxp_Tef810x_Mod11_DebugTestUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_DebugTestBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_DebugTestUnion_t;
/**
* Nxp_Tef810x_Mod11_PhaseshifterStatusUnion_t
* Nxp_Tef810x_Mod11_PhaseshifterStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_PhaseshifterStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_PhaseshifterStatusUnion_t;
/**
* Nxp_Tef810x_Mod11_AtbDelayTimerUnion_t
* Nxp_Tef810x_Mod11_AtbDelayTimerUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_AtbDelayTimerBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_AtbDelayTimerUnion_t;
/**
* Nxp_Tef810x_Mod11_Atb1Union_t
* Nxp_Tef810x_Mod11_Atb1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_Atb1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_Atb1Union_t;
/**
* Nxp_Tef810x_Mod11_Atb2Union_t
* Nxp_Tef810x_Mod11_Atb2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_Atb2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_Atb2Union_t;
/**
* Nxp_Tef810x_Mod11_TestErrorFlagStatusUnion_t
* Nxp_Tef810x_Mod11_TestErrorFlagStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_TestErrorFlagStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_TestErrorFlagStatusUnion_t;
/**
* Nxp_Tef810x_Mod11_ModuleidUnion_t
* Nxp_Tef810x_Mod11_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod11_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod11_ModuleidUnion_t;
	/**
* Nxp_Tef810x_Mod11_Txprofile_t
* Nxp_Tef810x_Mod11_Txprofile_t
* Structure for module specific profile management
*/
typedef struct  {
  /**
    * RegisterName: g_tx_gain_profile0
    * AddressOffset: 0x000
    * ResetValue: 0x00000080
    * Description: This register is used to set the transmitter gain control for profile0
    */
    Nxp_Tef810x_Mod11_GTxGainProfileUnion_t GTxGainProfile0_ust;        /*## attribute GTxGainProfile0_ust */
  /**
    * RegisterName: g_lox3_gain_profile0
    * AddressOffset: 0x004
    * ResetValue: 0x000000A8
    * Description: Used for TX DC calibration which is done in the production test and should be copied from the OTP
    */
    Nxp_Tef810x_Mod11_GLox3GainProfileUnion_t GLox3GainProfile0_ust;        /*## attribute GLox3GainProfile0_ust */
}Nxp_Tef810x_Mod11_TxProfile_t;
/**
 * Nxp_Tef810x_Mod11_TxRegister_t
 * Nxp_Tef810x_Mod11_TxRegister_t
 * structure used as shadow register map
 */
typedef struct  {
	/**
    * RegisterName: Nxp_Tef810x_Mod11_TxProfile_t;
    *AddressOffset: 0x000 - 0x01C
    * Description: Structure for module specific profile management.
                       
    */
    Nxp_Tef810x_Mod11_TxProfile_t TxProfile_ast[0x04];        /*## attribute TxProfile_ast */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x020
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: funcsafe_mon_level_rf
    * AddressOffset: 0x024
    * ResetValue: 0x0F0C0800
    * Description: This register is used to set the threshold (max, high, low, min) for rf level monitor
    */
    Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf_ust;        /*## attribute FuncsafeMonLevelRf_ust */
  /**
    * RegisterName: bbd_config
    * AddressOffset: 0x028
    * ResetValue: 0x00000100
    * Description: This register is used to set the controls for the ball break detector
    */
    Nxp_Tef810x_Mod11_BbdConfigUnion_t BbdConfig_ust;        /*## attribute BbdConfig_ust */
  /**
    * RegisterName: ts_sel
    * AddressOffset: 0x02C
    * ResetValue: 0x00000000
    * Description: This register is used to set the controls for the temperature sensor
    */
    Nxp_Tef810x_Mod11_TsSelUnion_t TsSel_ust;        /*## attribute TsSel_ust */
  /**
    * RegisterName: rms_control
    * AddressOffset: 0x030
    * ResetValue: 0x00000010
    * Description: This register is used to enable the rf level detectors
    */
    Nxp_Tef810x_Mod11_RmsControlUnion_t RmsControl_ust;        /*## attribute RmsControl_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x034
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x038
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: tx_control
    * AddressOffset: 0x03C
    * ResetValue: 0x00000000
    * Description: control settings for the transmitter. This includes controlling the dynamic switching of the transmitter per chirp, phase shift control internal/external per chirp and enable the transmitter .
	* 
	* Only for validation and debugging
    */
    Nxp_Tef810x_Mod11_TxControlUnion_t TxControl_ust;        /*## attribute TxControl_ust */
  /**
    * RegisterName: sns_top_control
    * AddressOffset: 0x040
    * ResetValue: 0x00000000
    * Description: supply sensor control bits
    */
    Nxp_Tef810x_Mod11_SnsTopControlUnion_t SnsTopControl_ust;        /*## attribute SnsTopControl_ust */
  /**
    * RegisterName: ts_pd
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: temperature sensor powerdown control bits
    */
    Nxp_Tef810x_Mod11_TsPdUnion_t TsPd_ust;        /*## attribute TsPd_ust */
  /**
    * RegisterName: rms_cal
    * AddressOffset: 0x048
    * ResetValue: 0x10000000
    * Description: calibration control setting for the rms detector
    */
    Nxp_Tef810x_Mod11_RmsCalUnion_t RmsCal_ust;        /*## attribute RmsCal_ust */
  /**
    * RegisterName: debug_test
    * AddressOffset: 0x04C
    * ResetValue: 0x00000CAA
    * Description: Control settings for the bias current for the different PA stages.
	* The values to be used  shall be  decided after validation.
    */
    Nxp_Tef810x_Mod11_DebugTestUnion_t DebugTest_ust;        /*## attribute DebugTest_ust */
  /**
    * RegisterName: phaseshifter_status
    * AddressOffset: 0x050
    * ResetValue: 0x00000003
    * Description: This register indicates read back status of the phaseshifter control bits
    */
    Nxp_Tef810x_Mod11_PhaseshifterStatusUnion_t PhaseshifterStatus_ust;        /*## attribute PhaseshifterStatus_ust */
  /**
    * RegisterName: atb_delay_timer
    * AddressOffset: 0x054
    * ResetValue: 0x00001F1F
    * Description: This register implements the delay between the atb value changes to avoid the misuse of ATB and thereby avoid switch shorts
    */
    Nxp_Tef810x_Mod11_AtbDelayTimerUnion_t AtbDelayTimer_ust;        /*## attribute AtbDelayTimer_ust */
  /**
    * RegisterName: atb1
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: ATB1 bus settings
    */
    Nxp_Tef810x_Mod11_Atb1Union_t Atb1_ust;        /*## attribute Atb1_ust */
  /**
    * RegisterName: atb2
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: ATB2 bus settings
    */
    Nxp_Tef810x_Mod11_Atb2Union_t Atb2_ust;        /*## attribute Atb2_ust */
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: test_error_flag_status
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: This register is kept for validation and not to be used in the functional context. 
	* In actual application use the registers available in ISM space
    */
    Nxp_Tef810x_Mod11_TestErrorFlagStatusUnion_t TestErrorFlagStatus_ust;        /*## attribute TestErrorFlagStatus_ust */
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x06C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x070
    * ResetValue: 0x0000000F
    * Description: 	nan
    */
    uint32 Reserved06;

    uint32 gap01_au32[992];        /* gap 1 in register space */  /**
    * RegisterName: Reserved07
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00112201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod11_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod11_TxRegister_t;

#endif
