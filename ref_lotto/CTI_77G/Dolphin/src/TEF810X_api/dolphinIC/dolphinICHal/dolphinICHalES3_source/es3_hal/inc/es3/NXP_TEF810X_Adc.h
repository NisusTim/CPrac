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
* @NXP_TEF810X_Adc.h
*/
#ifndef NXP_TEF810X_ADC_H
#define NXP_TEF810X_ADC_H
#include "Std_Types.h"

#define ADC12_MODULE_ADDRESS 0x07
#define ADC34_MODULE_ADDRESS 0x08
/**
*NXP_TEF810X_MOD07_PON_U16
* RegisterName: MOD07_pon
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_PON_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD07_CALIBRATION_STATUS_U16
* RegisterName: MOD07_calibration_status
* AccessMode: READ
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_CALIBRATION_STATUS_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD07_CALIBRATION_START_U16
* RegisterName: MOD07_calibration_start
* AccessMode: WRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_CALIBRATION_START_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD07_OUTPUT_POLARITY_CONTROL_U16
* RegisterName: MOD07_output_polarity_control
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_OUTPUT_POLARITY_CONTROL_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD07_CLIPPING_DETECT_CONTROL_U16
* RegisterName: MOD07_clipping_detect_control
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x07330600
*/
#define NXP_TEF810X_MOD07_CLIPPING_DETECT_CONTROL_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD07_SAFETY_FLAGS_STATUS_U16
* RegisterName: MOD07_safety_flags_status
* AccessMode: READ
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_SAFETY_FLAGS_STATUS_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD07_POWERSAVE_CONTROL_U16
* RegisterName: MOD07_powersave_control
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD07_POWERSAVE_CONTROL_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD07_CALIBRATION_CONTROL_U16
* RegisterName: MOD07_calibration_control
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x0000011F
*/
#define NXP_TEF810X_MOD07_CALIBRATION_CONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD07_CALIBRATION_PROGRAM_TIMING_5_0_U16
* RegisterName: MOD07_calibration_program_timing_5_0
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x1C842100
*/
#define NXP_TEF810X_MOD07_CALIBRATION_PROGRAM_TIMING_5_0_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD07_INPUTMUX_U16
* RegisterName: MOD07_inputmux
* AccessMode: READWRITE
* AddressRange: 0x0078 - 0x007C
* ResetValue: 0x00000024
*/
#define NXP_TEF810X_MOD07_INPUTMUX_U16 (uint16)0x0078
/**
*NXP_TEF810X_MOD07_OUTPUTMUX_U16
* RegisterName: MOD07_outputmux
* AccessMode: READWRITE
* AddressRange: 0x008C - 0x0090
* ResetValue: 0x5CE20030
*/
#define NXP_TEF810X_MOD07_OUTPUTMUX_U16 (uint16)0x008C
/**
*NXP_TEF810X_MOD07_OUTPUTMUX_DATA_ADC1_U16
* RegisterName: MOD07_outputmux_data_adc1
* AccessMode: READWRITE
* AddressRange: 0x0090 - 0x0094
* ResetValue: 0x00005CE2
*/
#define NXP_TEF810X_MOD07_OUTPUTMUX_DATA_ADC1_U16 (uint16)0x0090
/**
*NXP_TEF810X_MOD07_CAL_MONITOR_STATUS_U16
* RegisterName: MOD07_cal_monitor_status
* AccessMode: READ
* AddressRange: 0x00A0 - 0x00A4
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD07_CAL_MONITOR_STATUS_U16 (uint16)0x00A0
/**
*NXP_TEF810X_MOD07_BIAS_MAINDAC_U16
* RegisterName: MOD07_bias_maindac
* AccessMode: READWRITE
* AddressRange: 0x0304 - 0x0308
* ResetValue: 0x00000077
*/
#define NXP_TEF810X_MOD07_BIAS_MAINDAC_U16 (uint16)0x0304
/**
*NXP_TEF810X_MOD07_BIAS_SOURCE_FOLLOWER_U16
* RegisterName: MOD07_bias_source_follower
* AccessMode: READWRITE
* AddressRange: 0x030C - 0x0310
* ResetValue: 0x00000277
*/
#define NXP_TEF810X_MOD07_BIAS_SOURCE_FOLLOWER_U16 (uint16)0x030C
/**
*NXP_TEF810X_MOD07_MODULEID_U16
* RegisterName: MOD07_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00072201
*/
#define NXP_TEF810X_MOD07_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod07_PONBits_t
* RegisterName: pon
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: pon
	* Description: master PON
	* 0: module is powered down
	* 1: Module is powered on
	* 
	* Use model : This bit must be set high  in a functional use case.. Before seting this bit high, the PON from CC shall be set to high and the functional reset from CC shall be released.  Under the above condition, a rising edge of this bit  triggers a start up calibaration of the module.
	*/
    uint32 Pon: 1;        /*## attribute Pon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_PonBits_t;
    /**
* Nxp_Tef810x_Mod07_CALIBRATION_STATUSBits_t
* RegisterName: calibration_status
* 
* AddressRange: 0xREAD - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: calibration_busy
	* Description: 0: Calibaration not active
	* 1: Calibration is active
	*/
    uint32 CalibrationBusy: 1;        /*## attribute CalibrationBusy */
   /**
	* BitsName: calibration_launched_okay
	* Description: 0:  start could not be performed
	*  1:  The calibration was started,
	*/
    uint32 CalibrationLaunchedOkay: 1;        /*## attribute CalibrationLaunchedOkay */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_CalibrationStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_CALIBRATION_STARTBits_t
* RegisterName: calibration_start
* 
* AddressRange: 0xWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: start_calibration
	* Description: 0: No action
	* 1 starts a calibration
	*/
    uint32 StartCalibration: 1;        /*## attribute StartCalibration */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_CalibrationStartBits_t;
    /**
* Nxp_Tef810x_Mod07_OUTPUT_POLARITY_CONTROLBits_t
* RegisterName: output_polarity_control
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: invert_output_polarity
	* Description: 0: No action
	* 1: Invert the polarity of the ADC outputs
	*/
    uint32 InvertOutputPolarity: 2;        /*## attribute InvertOutputPolarity */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_OutputPolarityControlBits_t;
    /**
* Nxp_Tef810x_Mod07_CLIPPING_DETECT_CONTROLBits_t
* RegisterName: clipping_detect_control
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: adc_cliplevel75
	* Description: ADC output level (code) that triggers the 75% of full scale clipping detector
	*/
    uint32 AdcCliplevel75: 11;        /*## attribute AdcCliplevel75 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: adc_cliplevel90
	* Description: ADC output level (code) that triggers the 90% of full scale clipping detector
	*/
    uint32 AdcCliplevel90: 11;        /*## attribute AdcCliplevel90 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 5;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod07_ClippingDetectControlBits_t;
    /**
* Nxp_Tef810x_Mod07_SAFETY_FLAGS_STATUSBits_t
* RegisterName: safety_flags_status
* 
* AddressRange: 0xREAD - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: cal_error_flag_persistent_status
	* Description: persistent calibration error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 CalErrorFlagPersistentStatus: 2;        /*## attribute CalErrorFlagPersistentStatus */
   /**
	* BitsName: near_clipping_error_flag_persistent_status
	* Description: persistent near clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 NearClippingErrorFlagPersistentStatus: 2;        /*## attribute NearClippingErrorFlagPersistentStatus */
   /**
	* BitsName: clipping_error_flag_persistent_status
	* Description: persistent clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 ClippingErrorFlagPersistentStatus: 2;        /*## attribute ClippingErrorFlagPersistentStatus */
   /**
	* BitsName: hard_clipping_error_flag_persistent_status
	* Description: persistent hard clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 HardClippingErrorFlagPersistentStatus: 2;        /*## attribute HardClippingErrorFlagPersistentStatus */
   /**
	* BitsName: near_clipping_error_flag_status
	* Description: near clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 NearClippingErrorFlagStatus: 2;        /*## attribute NearClippingErrorFlagStatus */
   /**
	* BitsName: clipping_error_flag_status
	* Description: clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 ClippingErrorFlagStatus: 2;        /*## attribute ClippingErrorFlagStatus */
   /**
	* BitsName: hard_clipping_error_flag_status
	* Description: hard clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 HardClippingErrorFlagStatus: 2;        /*## attribute HardClippingErrorFlagStatus */
   /**
	* BitsName: supply_low_error_flag_status
	* Description: 0: No Error
	* 1: supply low sensor error
	*/
    uint32 SupplyLowErrorFlagStatus: 1;        /*## attribute SupplyLowErrorFlagStatus */
   /**
	* BitsName: bgcal_error_flag_status
	* Description: 0: No Error
	* 1: Background calibration aborted (not ready before pon goes high again)
	*/
    uint32 BgcalErrorFlagStatus: 1;        /*## attribute BgcalErrorFlagStatus */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_SafetyFlagsStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_POWERSAVE_CONTROLBits_t
* RegisterName: powersave_control
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: pon_powersave_enable
	* Description: 0: pon always triggers calibration
	* 1: pon only triggers calibation once
	*/
    uint32 PonPowersaveEnable: 1;        /*## attribute PonPowersaveEnable */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_PowersaveControlBits_t;
    /**
* Nxp_Tef810x_Mod07_CALIBRATION_CONTROLBits_t
* RegisterName: calibration_control
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: auto_calibrate_at_pon
	* Description: 0: no action
	* 1: automatically calibrate the ADC after power-on
	*/
    uint32 AutoCalibrateAtPon: 1;        /*## attribute AutoCalibrateAtPon */
   /**
	* BitsName: auto_sync_sequencer_after_calibration
	* Description: 0: no action
	* 1: automatically synchronize sequencer with other dual ADC after calibration
	*/
    uint32 AutoSyncSequencerAfterCalibration: 1;        /*## attribute AutoSyncSequencerAfterCalibration */
   /**
	* BitsName: calibrate_lsb_weights
	* Description: 0: no action
	* 1:  enable calibration of LSBs that are not part of the DEM array
	*/
    uint32 CalibrateLsbWeights: 1;        /*## attribute CalibrateLsbWeights */
   /**
	* BitsName: enable_interleaved_calibration
	* Description: 0: simultaneous calibration (MRA1 mode)
	* 1: interleaved operation during calibration
	*/
    uint32 EnableInterleavedCalibration: 1;        /*## attribute EnableInterleavedCalibration */
   /**
	* BitsName: enable_powersave_bg_calibration
	* Description: 0: power-save background calibration disabled
	* 1: power-save background calibration enabled
	*/
    uint32 EnablePowersaveBgCalibration: 1;        /*## attribute EnablePowersaveBgCalibration */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: powersave_bg_calibration_nweights
	* Description: number of weights to calibrate per power-save background calibration cycle
	* 1 : default, 
	* 5 : recommended
	*/
    uint32 PowersaveBgCalibrationNweights: 4;        /*## attribute PowersaveBgCalibrationNweights */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 20;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod07_CalibrationControlBits_t;
    /**
* Nxp_Tef810x_Mod07_CALIBRATION_PROGRAM_TIMING_5_0Bits_t
* RegisterName: calibration_program_timing_5_0
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: calibration_program_timing_0
	* Description: NA (max #integrations for startup (FG): 20)
	*/
    uint32 CalibrationProgramTiming0: 5;        /*## attribute CalibrationProgramTiming0 */
   /**
	* BitsName: calibration_program_timing_1
	* Description: default 8 => 0.09ms
	*/
    uint32 CalibrationProgramTiming1: 5;        /*## attribute CalibrationProgramTiming1 */
   /**
	* BitsName: calibration_program_timing_2
	* Description: default 8 => 0.19ms
	*/
    uint32 CalibrationProgramTiming2: 5;        /*## attribute CalibrationProgramTiming2 */
   /**
	* BitsName: calibration_program_timing_3
	* Description: default 8 => 0.38ms
	*/
    uint32 CalibrationProgramTiming3: 5;        /*## attribute CalibrationProgramTiming3 */
   /**
	* BitsName: calibration_program_timing_4
	* Description: default 8 => 0.09ms
	*/
    uint32 CalibrationProgramTiming4: 5;        /*## attribute CalibrationProgramTiming4 */
   /**
	* BitsName: calibration_program_timing_5
	* Description: default 14 => 10.94ms, recommended 11 => 1.38ms
	*/
    uint32 CalibrationProgramTiming5: 5;        /*## attribute CalibrationProgramTiming5 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_CalibrationProgramTiming50Bits_t;
    /**
* Nxp_Tef810x_Mod07_INPUTMUXBits_t
* RegisterName: inputmux
* 
* AddressRange: 0xREADWRITE - 0x078
* ResetValue: 0x0000007C
*/
typedef struct  {
   /**
	* BitsName: inputmux_statusmapping_0
	* Description: Lookup table to map the INTERNAL input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping0: 2;        /*## attribute InputmuxStatusmapping0 */
   /**
	* BitsName: inputmux_statusmapping_1
	* Description: Lookup table to map the EXTERNAL input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping1: 2;        /*## attribute InputmuxStatusmapping1 */
   /**
	* BitsName: inputmux_statusmapping_2
	* Description: Lookup table to map the REFERENCE input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping2: 2;        /*## attribute InputmuxStatusmapping2 */
   /**
	* BitsName: inputmux_mode
	* Description: Set the input mux of adc0+adc1/adc0 (splitmode=0/1) or only to: 00: normal operation (calibration engine controlled), 01: fixed internal input, 10: fixed external input, 11: fixed reference input
	*/
    uint32 InputmuxMode: 2;        /*## attribute InputmuxMode */
   /**
	* BitsName: inputmux_mode_adc1
	* Description: When splitmode=0: ignored, otherwise set the input mux of adc1 to: 00: normal operation (calibration engine controlled), 01: fixed internal input, 10: fixed external input, 11: fixed reference input
	*/
    uint32 InputmuxModeAdc1: 2;        /*## attribute InputmuxModeAdc1 */
   /**
	* BitsName: inputmux_mode_splitmode
	* Description: 0: legacy mode where inputmux_mode controls both ADCs, 1: separate control of the input muxs.
	*/
    uint32 InputmuxModeSplitmode: 1;        /*## attribute InputmuxModeSplitmode */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 21;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_InputmuxBits_t;
    /**
* Nxp_Tef810x_Mod07_OUTPUTMUXBits_t
* RegisterName: outputmux
* 
* AddressRange: 0xREADWRITE - 0x08C
* ResetValue: 0x00000090
*/
typedef struct  {
   /**
	* BitsName: outputmux_mode_adc0
	* Description: 0: normal output mode (binary output, extra LSB+clip+chop), 1: debug output mode (quantizer decisions), 2: debug output mode (constant), 3:counter on data output
	*/
    uint32 OutputmuxModeAdc0: 2;        /*## attribute OutputmuxModeAdc0 */
   /**
	* BitsName: outputmux_mode_adc1
	* Description: 0: normal output mode (binary output, extra LSB+clip+chop), 1: debug output mode (quantizer decisions), 2: debug output mode (constant), 3:counter on data output
	*/
    uint32 OutputmuxModeAdc1: 2;        /*## attribute OutputmuxModeAdc1 */
   /**
	* BitsName: outputmux_invclk
	* Description: For each ADC: 0: normal output clock, 1: inverted output clock
	*/
    uint32 OutputmuxInvclk: 2;        /*## attribute OutputmuxInvclk */
   /**
	* BitsName: outputmux_force_output_clk
	* Description: force activation of the output clk
	*/
    uint32 OutputmuxForceOutputClk: 1;        /*## attribute OutputmuxForceOutputClk */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 9;        /*## attribute Reserved0 */
   /**
	* BitsName: outputmux_debug_constant_data
	* Description: constant debug value on data output
	*/
    uint32 OutputmuxDebugConstantData: 12;        /*## attribute OutputmuxDebugConstantData */
   /**
	* BitsName: outputmux_debug_constant_debug
	* Description: constant debug value on debug output
	*/
    uint32 OutputmuxDebugConstantDebug: 3;        /*## attribute OutputmuxDebugConstantDebug */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod07_OutputmuxBits_t;
    /**
* Nxp_Tef810x_Mod07_OUTPUTMUX_DATA_ADC1Bits_t
* RegisterName: outputmux_data_adc1
* 
* AddressRange: 0xREADWRITE - 0x090
* ResetValue: 0x00000094
*/
typedef struct  {
   /**
	* BitsName: outputmux_debug_constant_data_adc1
	* Description: constant debug value on data output
	*/
    uint32 OutputmuxDebugConstantDataAdc1: 12;        /*## attribute OutputmuxDebugConstantDataAdc1 */
   /**
	* BitsName: outputmux_debug_constant_debug_adc1
	* Description: constant debug value on debug output
	*/
    uint32 OutputmuxDebugConstantDebugAdc1: 3;        /*## attribute OutputmuxDebugConstantDebugAdc1 */
   /**
	* BitsName: outputmux_debug_splitmode
	* Description: 0: outputmux debug data is same for both ADCs, 1: data for adc1 is from this register
	*/
    uint32 OutputmuxDebugSplitmode: 1;        /*## attribute OutputmuxDebugSplitmode */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_OutputmuxDataAdc1Bits_t;
    /**
* Nxp_Tef810x_Mod07_CAL_MONITOR_STATUSBits_t
* RegisterName: cal_monitor_status
* 
* AddressRange: 0xREAD - 0x0A0
* ResetValue: 0x000000A4
*/
typedef struct  {
   /**
	* BitsName: cal_monitor_calibration_check_done
	* Description: 1 indicates the calibration monitor has been executed
	*/
    uint32 CalMonitorCalibrationCheckDone: 1;        /*## attribute CalMonitorCalibrationCheckDone */
   /**
	* BitsName: cal_monitor_calibration_okay
	* Description: 1 indicates the calibration has been succesful (bit per ADC)
	*/
    uint32 CalMonitorCalibrationOkay: 2;        /*## attribute CalMonitorCalibrationOkay */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 29;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_CalMonitorStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_BIAS_MAINDACBits_t
* RegisterName: bias_maindac
* 
* AddressRange: 0xREADWRITE - 0x304
* ResetValue: 0x00000308
*/
typedef struct  {
   /**
	* BitsName: bias_maindac_currentsource
	* Description: 500uA to 1250uA in 50uA steps (default=850uA)
	*/
    uint32 BiasMaindacCurrentsource: 4;        /*## attribute BiasMaindacCurrentsource */
   /**
	* BitsName: bias_maindac_cascode
	* Description: 200uA to 575uA in 25uA steps (default=375uA)
	*/
    uint32 BiasMaindacCascode: 4;        /*## attribute BiasMaindacCascode */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_BiasMaindacBits_t;
    /**
* Nxp_Tef810x_Mod07_BIAS_SOURCE_FOLLOWERBits_t
* RegisterName: bias_source_follower
* 
* AddressRange: 0xREADWRITE - 0x30C
* ResetValue: 0x00000310
*/
typedef struct  {
   /**
	* BitsName: bias_SF_aux_SF1
	* Description: Aux SF2 bias. Current values 6uA + n x 1uA. (ibias_auxSF_BG10u)
	*/
    uint32 BiasSfAuxSf1: 4;        /*## attribute BiasSfAuxSf1 */
   /**
	* BitsName: bias_SF_aux_SF2
	* Description: Aux SF1 bias. Current values 6uA + n x 1uA. (ibias_auxSF_BG10u_2)
	*/
    uint32 BiasSfAuxSf2: 4;        /*## attribute BiasSfAuxSf2 */
   /**
	* BitsName: bias_SF_main_SF
	* Description: Main SF bias. Current values 200uA + n x 20uA. (ibias_Sfbuffer)
	*/
    uint32 BiasSfMainSf: 4;        /*## attribute BiasSfMainSf */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod07_BiasSourceFollowerBits_t;
    /**
* Nxp_Tef810x_Mod07_MODULEIDBits_t
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
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod07_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod07_PonBits_t
* RegisterName: pon
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: pon
	* Description: master PON
	* 0: module is powered down
	* 1: Module is powered on
	* 
	* Use model : This bit must be set high  in a functional use case.. Before seting this bit high, the PON from CC shall be set to high and the functional reset from CC shall be released.  Under the above condition, a rising edge of this bit  triggers a start up calibaration of the module.
	*/
    uint32 Pon: 1;        /*## attribute Pon */
}Nxp_Tef810x_Mod07_PonBits_t;
    /**
* Nxp_Tef810x_Mod07_CalibrationStatusBits_t
* RegisterName: calibration_status
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: calibration_launched_okay
	* Description: 0:  start could not be performed
	*  1:  The calibration was started,
	*/
    uint32 CalibrationLaunchedOkay: 1;        /*## attribute CalibrationLaunchedOkay */
   /**
	* BitsName: calibration_busy
	* Description: 0: Calibaration not active
	* 1: Calibration is active
	*/
    uint32 CalibrationBusy: 1;        /*## attribute CalibrationBusy */
}Nxp_Tef810x_Mod07_CalibrationStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_CalibrationStartBits_t
* RegisterName: calibration_start
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: start_calibration
	* Description: 0: No action
	* 1 starts a calibration
	*/
    uint32 StartCalibration: 1;        /*## attribute StartCalibration */
}Nxp_Tef810x_Mod07_CalibrationStartBits_t;
    /**
* Nxp_Tef810x_Mod07_OutputPolarityControlBits_t
* RegisterName: output_polarity_control
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: invert_output_polarity
	* Description: 0: No action
	* 1: Invert the polarity of the ADC outputs
	*/
    uint32 InvertOutputPolarity: 2;        /*## attribute InvertOutputPolarity */
}Nxp_Tef810x_Mod07_OutputPolarityControlBits_t;
    /**
* Nxp_Tef810x_Mod07_ClippingDetectControlBits_t
* RegisterName: clipping_detect_control
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x07330600
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: adc_cliplevel90
	* Description: ADC output level (code) that triggers the 90% of full scale clipping detector
	*/
    uint32 AdcCliplevel90: 11;        /*## attribute AdcCliplevel90 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 5;        /*## attribute Reserved1 */
   /**
	* BitsName: adc_cliplevel75
	* Description: ADC output level (code) that triggers the 75% of full scale clipping detector
	*/
    uint32 AdcCliplevel75: 11;        /*## attribute AdcCliplevel75 */
}Nxp_Tef810x_Mod07_ClippingDetectControlBits_t;
    /**
* Nxp_Tef810x_Mod07_SafetyFlagsStatusBits_t
* RegisterName: safety_flags_status
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: bgcal_error_flag_status
	* Description: 0: No Error
	* 1: Background calibration aborted (not ready before pon goes high again)
	*/
    uint32 BgcalErrorFlagStatus: 1;        /*## attribute BgcalErrorFlagStatus */
   /**
	* BitsName: supply_low_error_flag_status
	* Description: 0: No Error
	* 1: supply low sensor error
	*/
    uint32 SupplyLowErrorFlagStatus: 1;        /*## attribute SupplyLowErrorFlagStatus */
   /**
	* BitsName: hard_clipping_error_flag_status
	* Description: hard clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 HardClippingErrorFlagStatus: 2;        /*## attribute HardClippingErrorFlagStatus */
   /**
	* BitsName: clipping_error_flag_status
	* Description: clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 ClippingErrorFlagStatus: 2;        /*## attribute ClippingErrorFlagStatus */
   /**
	* BitsName: near_clipping_error_flag_status
	* Description: near clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 NearClippingErrorFlagStatus: 2;        /*## attribute NearClippingErrorFlagStatus */
   /**
	* BitsName: hard_clipping_error_flag_persistent_status
	* Description: persistent hard clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 HardClippingErrorFlagPersistentStatus: 2;        /*## attribute HardClippingErrorFlagPersistentStatus */
   /**
	* BitsName: clipping_error_flag_persistent_status
	* Description: persistent clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 ClippingErrorFlagPersistentStatus: 2;        /*## attribute ClippingErrorFlagPersistentStatus */
   /**
	* BitsName: near_clipping_error_flag_persistent_status
	* Description: persistent near clipping error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 NearClippingErrorFlagPersistentStatus: 2;        /*## attribute NearClippingErrorFlagPersistentStatus */
   /**
	* BitsName: cal_error_flag_persistent_status
	* Description: persistent calibration error flag status readout
	* 00: No error
	* 01: ADC0  error
	* 10: ADC1 error
	* 11: ADC0 & ADC1 error
	*/
    uint32 CalErrorFlagPersistentStatus: 2;        /*## attribute CalErrorFlagPersistentStatus */
}Nxp_Tef810x_Mod07_SafetyFlagsStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_PowersaveControlBits_t
* RegisterName: powersave_control
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: pon_powersave_enable
	* Description: 0: pon always triggers calibration
	* 1: pon only triggers calibation once
	*/
    uint32 PonPowersaveEnable: 1;        /*## attribute PonPowersaveEnable */
}Nxp_Tef810x_Mod07_PowersaveControlBits_t;
    /**
* Nxp_Tef810x_Mod07_CalibrationControlBits_t
* RegisterName: calibration_control
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x0000011F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: powersave_bg_calibration_nweights
	* Description: number of weights to calibrate per power-save background calibration cycle
	* 1 : default, 
	* 5 : recommended
	*/
    uint32 PowersaveBgCalibrationNweights: 4;        /*## attribute PowersaveBgCalibrationNweights */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: enable_powersave_bg_calibration
	* Description: 0: power-save background calibration disabled
	* 1: power-save background calibration enabled
	*/
    uint32 EnablePowersaveBgCalibration: 1;        /*## attribute EnablePowersaveBgCalibration */
   /**
	* BitsName: enable_interleaved_calibration
	* Description: 0: simultaneous calibration (MRA1 mode)
	* 1: interleaved operation during calibration
	*/
    uint32 EnableInterleavedCalibration: 1;        /*## attribute EnableInterleavedCalibration */
   /**
	* BitsName: calibrate_lsb_weights
	* Description: 0: no action
	* 1:  enable calibration of LSBs that are not part of the DEM array
	*/
    uint32 CalibrateLsbWeights: 1;        /*## attribute CalibrateLsbWeights */
   /**
	* BitsName: auto_sync_sequencer_after_calibration
	* Description: 0: no action
	* 1: automatically synchronize sequencer with other dual ADC after calibration
	*/
    uint32 AutoSyncSequencerAfterCalibration: 1;        /*## attribute AutoSyncSequencerAfterCalibration */
   /**
	* BitsName: auto_calibrate_at_pon
	* Description: 0: no action
	* 1: automatically calibrate the ADC after power-on
	*/
    uint32 AutoCalibrateAtPon: 1;        /*## attribute AutoCalibrateAtPon */
}Nxp_Tef810x_Mod07_CalibrationControlBits_t;
    /**
* Nxp_Tef810x_Mod07_CalibrationProgramTiming50Bits_t
* RegisterName: calibration_program_timing_5_0
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x1C842100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: calibration_program_timing_5
	* Description: default 14 => 10.94ms, recommended 11 => 1.38ms
	*/
    uint32 CalibrationProgramTiming5: 5;        /*## attribute CalibrationProgramTiming5 */
   /**
	* BitsName: calibration_program_timing_4
	* Description: default 8 => 0.09ms
	*/
    uint32 CalibrationProgramTiming4: 5;        /*## attribute CalibrationProgramTiming4 */
   /**
	* BitsName: calibration_program_timing_3
	* Description: default 8 => 0.38ms
	*/
    uint32 CalibrationProgramTiming3: 5;        /*## attribute CalibrationProgramTiming3 */
   /**
	* BitsName: calibration_program_timing_2
	* Description: default 8 => 0.19ms
	*/
    uint32 CalibrationProgramTiming2: 5;        /*## attribute CalibrationProgramTiming2 */
   /**
	* BitsName: calibration_program_timing_1
	* Description: default 8 => 0.09ms
	*/
    uint32 CalibrationProgramTiming1: 5;        /*## attribute CalibrationProgramTiming1 */
   /**
	* BitsName: calibration_program_timing_0
	* Description: NA (max #integrations for startup (FG): 20)
	*/
    uint32 CalibrationProgramTiming0: 5;        /*## attribute CalibrationProgramTiming0 */
}Nxp_Tef810x_Mod07_CalibrationProgramTiming50Bits_t;
    /**
* Nxp_Tef810x_Mod07_InputmuxBits_t
* RegisterName: inputmux
* 
* AddressRange: 0x078 - 0x07C
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 21;        /*## attribute Reserved0 */
   /**
	* BitsName: inputmux_mode_splitmode
	* Description: 0: legacy mode where inputmux_mode controls both ADCs, 1: separate control of the input muxs.
	*/
    uint32 InputmuxModeSplitmode: 1;        /*## attribute InputmuxModeSplitmode */
   /**
	* BitsName: inputmux_mode_adc1
	* Description: When splitmode=0: ignored, otherwise set the input mux of adc1 to: 00: normal operation (calibration engine controlled), 01: fixed internal input, 10: fixed external input, 11: fixed reference input
	*/
    uint32 InputmuxModeAdc1: 2;        /*## attribute InputmuxModeAdc1 */
   /**
	* BitsName: inputmux_mode
	* Description: Set the input mux of adc0+adc1/adc0 (splitmode=0/1) or only to: 00: normal operation (calibration engine controlled), 01: fixed internal input, 10: fixed external input, 11: fixed reference input
	*/
    uint32 InputmuxMode: 2;        /*## attribute InputmuxMode */
   /**
	* BitsName: inputmux_statusmapping_2
	* Description: Lookup table to map the REFERENCE input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping2: 2;        /*## attribute InputmuxStatusmapping2 */
   /**
	* BitsName: inputmux_statusmapping_1
	* Description: Lookup table to map the EXTERNAL input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping1: 2;        /*## attribute InputmuxStatusmapping1 */
   /**
	* BitsName: inputmux_statusmapping_0
	* Description: Lookup table to map the INTERNAL input setting of the mux to control bits.
	*/
    uint32 InputmuxStatusmapping0: 2;        /*## attribute InputmuxStatusmapping0 */
}Nxp_Tef810x_Mod07_InputmuxBits_t;
    /**
* Nxp_Tef810x_Mod07_OutputmuxBits_t
* RegisterName: outputmux
* 
* AddressRange: 0x08C - 0x090
* ResetValue: 0x5CE20030
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: outputmux_debug_constant_debug
	* Description: constant debug value on debug output
	*/
    uint32 OutputmuxDebugConstantDebug: 3;        /*## attribute OutputmuxDebugConstantDebug */
   /**
	* BitsName: outputmux_debug_constant_data
	* Description: constant debug value on data output
	*/
    uint32 OutputmuxDebugConstantData: 12;        /*## attribute OutputmuxDebugConstantData */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 9;        /*## attribute Reserved1 */
   /**
	* BitsName: outputmux_force_output_clk
	* Description: force activation of the output clk
	*/
    uint32 OutputmuxForceOutputClk: 1;        /*## attribute OutputmuxForceOutputClk */
   /**
	* BitsName: outputmux_invclk
	* Description: For each ADC: 0: normal output clock, 1: inverted output clock
	*/
    uint32 OutputmuxInvclk: 2;        /*## attribute OutputmuxInvclk */
   /**
	* BitsName: outputmux_mode_adc1
	* Description: 0: normal output mode (binary output, extra LSB+clip+chop), 1: debug output mode (quantizer decisions), 2: debug output mode (constant), 3:counter on data output
	*/
    uint32 OutputmuxModeAdc1: 2;        /*## attribute OutputmuxModeAdc1 */
   /**
	* BitsName: outputmux_mode_adc0
	* Description: 0: normal output mode (binary output, extra LSB+clip+chop), 1: debug output mode (quantizer decisions), 2: debug output mode (constant), 3:counter on data output
	*/
    uint32 OutputmuxModeAdc0: 2;        /*## attribute OutputmuxModeAdc0 */
}Nxp_Tef810x_Mod07_OutputmuxBits_t;
    /**
* Nxp_Tef810x_Mod07_OutputmuxDataAdc1Bits_t
* RegisterName: outputmux_data_adc1
* 
* AddressRange: 0x090 - 0x094
* ResetValue: 0x00005CE2
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: outputmux_debug_splitmode
	* Description: 0: outputmux debug data is same for both ADCs, 1: data for adc1 is from this register
	*/
    uint32 OutputmuxDebugSplitmode: 1;        /*## attribute OutputmuxDebugSplitmode */
   /**
	* BitsName: outputmux_debug_constant_debug_adc1
	* Description: constant debug value on debug output
	*/
    uint32 OutputmuxDebugConstantDebugAdc1: 3;        /*## attribute OutputmuxDebugConstantDebugAdc1 */
   /**
	* BitsName: outputmux_debug_constant_data_adc1
	* Description: constant debug value on data output
	*/
    uint32 OutputmuxDebugConstantDataAdc1: 12;        /*## attribute OutputmuxDebugConstantDataAdc1 */
}Nxp_Tef810x_Mod07_OutputmuxDataAdc1Bits_t;
    /**
* Nxp_Tef810x_Mod07_CalMonitorStatusBits_t
* RegisterName: cal_monitor_status
* 
* AddressRange: 0x0A0 - 0x0A4
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 29;        /*## attribute Reserved0 */
   /**
	* BitsName: cal_monitor_calibration_okay
	* Description: 1 indicates the calibration has been succesful (bit per ADC)
	*/
    uint32 CalMonitorCalibrationOkay: 2;        /*## attribute CalMonitorCalibrationOkay */
   /**
	* BitsName: cal_monitor_calibration_check_done
	* Description: 1 indicates the calibration monitor has been executed
	*/
    uint32 CalMonitorCalibrationCheckDone: 1;        /*## attribute CalMonitorCalibrationCheckDone */
}Nxp_Tef810x_Mod07_CalMonitorStatusBits_t;
    /**
* Nxp_Tef810x_Mod07_BiasMaindacBits_t
* RegisterName: bias_maindac
* 
* AddressRange: 0x304 - 0x308
* ResetValue: 0x00000077
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: bias_maindac_cascode
	* Description: 200uA to 575uA in 25uA steps (default=375uA)
	*/
    uint32 BiasMaindacCascode: 4;        /*## attribute BiasMaindacCascode */
   /**
	* BitsName: bias_maindac_currentsource
	* Description: 500uA to 1250uA in 50uA steps (default=850uA)
	*/
    uint32 BiasMaindacCurrentsource: 4;        /*## attribute BiasMaindacCurrentsource */
}Nxp_Tef810x_Mod07_BiasMaindacBits_t;
    /**
* Nxp_Tef810x_Mod07_BiasSourceFollowerBits_t
* RegisterName: bias_source_follower
* 
* AddressRange: 0x30C - 0x310
* ResetValue: 0x00000277
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: bias_SF_main_SF
	* Description: Main SF bias. Current values 200uA + n x 20uA. (ibias_Sfbuffer)
	*/
    uint32 BiasSfMainSf: 4;        /*## attribute BiasSfMainSf */
   /**
	* BitsName: bias_SF_aux_SF2
	* Description: Aux SF1 bias. Current values 6uA + n x 1uA. (ibias_auxSF_BG10u_2)
	*/
    uint32 BiasSfAuxSf2: 4;        /*## attribute BiasSfAuxSf2 */
   /**
	* BitsName: bias_SF_aux_SF1
	* Description: Aux SF2 bias. Current values 6uA + n x 1uA. (ibias_auxSF_BG10u)
	*/
    uint32 BiasSfAuxSf1: 4;        /*## attribute BiasSfAuxSf1 */
}Nxp_Tef810x_Mod07_BiasSourceFollowerBits_t;
    /**
* Nxp_Tef810x_Mod07_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00072201
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
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
}Nxp_Tef810x_Mod07_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod07_PonUnion_t
* Nxp_Tef810x_Mod07_PonUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_PonBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_PonUnion_t;
/**
* Nxp_Tef810x_Mod07_CalibrationStatusUnion_t
* Nxp_Tef810x_Mod07_CalibrationStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_CalibrationStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_CalibrationStatusUnion_t;
/**
* Nxp_Tef810x_Mod07_CalibrationStartUnion_t
* Nxp_Tef810x_Mod07_CalibrationStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_CalibrationStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_CalibrationStartUnion_t;
/**
* Nxp_Tef810x_Mod07_OutputPolarityControlUnion_t
* Nxp_Tef810x_Mod07_OutputPolarityControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_OutputPolarityControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_OutputPolarityControlUnion_t;
/**
* Nxp_Tef810x_Mod07_ClippingDetectControlUnion_t
* Nxp_Tef810x_Mod07_ClippingDetectControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_ClippingDetectControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_ClippingDetectControlUnion_t;
/**
* Nxp_Tef810x_Mod07_SafetyFlagsStatusUnion_t
* Nxp_Tef810x_Mod07_SafetyFlagsStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_SafetyFlagsStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_SafetyFlagsStatusUnion_t;
/**
* Nxp_Tef810x_Mod07_PowersaveControlUnion_t
* Nxp_Tef810x_Mod07_PowersaveControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_PowersaveControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_PowersaveControlUnion_t;
/**
* Nxp_Tef810x_Mod07_CalibrationControlUnion_t
* Nxp_Tef810x_Mod07_CalibrationControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_CalibrationControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_CalibrationControlUnion_t;
/**
* Nxp_Tef810x_Mod07_CalibrationProgramTiming50Union_t
* Nxp_Tef810x_Mod07_CalibrationProgramTiming50Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_CalibrationProgramTiming50Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_CalibrationProgramTiming50Union_t;
/**
* Nxp_Tef810x_Mod07_InputmuxUnion_t
* Nxp_Tef810x_Mod07_InputmuxUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_InputmuxBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_InputmuxUnion_t;
/**
* Nxp_Tef810x_Mod07_OutputmuxUnion_t
* Nxp_Tef810x_Mod07_OutputmuxUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_OutputmuxBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_OutputmuxUnion_t;
/**
* Nxp_Tef810x_Mod07_OutputmuxDataAdc1Union_t
* Nxp_Tef810x_Mod07_OutputmuxDataAdc1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_OutputmuxDataAdc1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_OutputmuxDataAdc1Union_t;
/**
* Nxp_Tef810x_Mod07_CalMonitorStatusUnion_t
* Nxp_Tef810x_Mod07_CalMonitorStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_CalMonitorStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_CalMonitorStatusUnion_t;
/**
* Nxp_Tef810x_Mod07_BiasMaindacUnion_t
* Nxp_Tef810x_Mod07_BiasMaindacUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_BiasMaindacBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_BiasMaindacUnion_t;
/**
* Nxp_Tef810x_Mod07_BiasSourceFollowerUnion_t
* Nxp_Tef810x_Mod07_BiasSourceFollowerUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_BiasSourceFollowerBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_BiasSourceFollowerUnion_t;
/**
* Nxp_Tef810x_Mod07_ModuleidUnion_t
* Nxp_Tef810x_Mod07_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod07_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod07_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod07_AdcRegister_t
 * Nxp_Tef810x_Mod07_AdcRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: pon
    * AddressOffset: 0x000
    * ResetValue: 0x00000000
    * Description: ADC pon control
    */
    Nxp_Tef810x_Mod07_PonUnion_t Pon_ust;        /*## attribute Pon_ust */
  /**
    * RegisterName: calibration_status
    * AddressOffset: 0x004
    * ResetValue: 0x00000000
    * Description: ADC calibration status
    */
    Nxp_Tef810x_Mod07_CalibrationStatusUnion_t CalibrationStatus_ust;        /*## attribute CalibrationStatus_ust */
  /**
    * RegisterName: calibration_start
    * AddressOffset: 0x008
    * ResetValue: 0x00000000
    * Description: Manual calibration start control
    */
    Nxp_Tef810x_Mod07_CalibrationStartUnion_t CalibrationStart_ust;        /*## attribute CalibrationStart_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: output_polarity_control
    * AddressOffset: 0x010
    * ResetValue: 0x00000000
    * Description: Output polarity control
    */
    Nxp_Tef810x_Mod07_OutputPolarityControlUnion_t OutputPolarityControl_ust;        /*## attribute OutputPolarityControl_ust */
  /**
    * RegisterName: clipping_detect_control
    * AddressOffset: 0x014
    * ResetValue: 0x07330600
    * Description: Clipping detection level control
    */
    Nxp_Tef810x_Mod07_ClippingDetectControlUnion_t ClippingDetectControl_ust;        /*## attribute ClippingDetectControl_ust */
  /**
    * RegisterName: safety_flags_status
    * AddressOffset: 0x018
    * ResetValue: 0x00000000
    * Description: Status of function safety flags
    */
    Nxp_Tef810x_Mod07_SafetyFlagsStatusUnion_t SafetyFlagsStatus_ust;        /*## attribute SafetyFlagsStatus_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x01C
    * ResetValue: 0x0003FFFF
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x020
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;

    uint32 gap01_au32[2];        /* gap 1 in register space */  /**
    * RegisterName: powersave_control
    * AddressOffset: 0x02C
    * ResetValue: 0x00000001
    * Description: Power save (startup calibration) control
    */
    Nxp_Tef810x_Mod07_PowersaveControlUnion_t PowersaveControl_ust;        /*## attribute PowersaveControl_ust */
  /**
    * RegisterName: calibration_control
    * AddressOffset: 0x030
    * ResetValue: 0x0000011F
    * Description: Calibration settings
    */
    Nxp_Tef810x_Mod07_CalibrationControlUnion_t CalibrationControl_ust;        /*## attribute CalibrationControl_ust */
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x034
    * ResetValue: 0x0000FFFF
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x038
    * ResetValue: 0x1907007A
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x03C
    * ResetValue: 0x0000001F
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x040
    * ResetValue: 0x00000001
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x044
    * ResetValue: 0x0000003F
    * Description: 	nan
    */
    uint32 Reserved07;

    uint32 gap02_au32[2];        /* gap 2 in register space */  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x050
    * ResetValue: 0x3F711888
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x054
    * ResetValue: 0x00007FFF
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: calibration_program_timing_5_0
    * AddressOffset: 0x058
    * ResetValue: 0x1C842100
    * Description: Calibration timing 0..5
    */
    Nxp_Tef810x_Mod07_CalibrationProgramTiming50Union_t CalibrationProgramTiming50_ust;        /*## attribute CalibrationProgramTiming50_ust */
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x05C
    * ResetValue: 0x0000014A
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x064
    * ResetValue: 0x00007FB0
    * Description: 	nan
    */
    uint32 Reserved0C;

    uint32 gap03_au32[2];        /* gap 3 in register space */  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x070
    * ResetValue: 0x00000003
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0x074
    * ResetValue: 0x00008A9C
    * Description: 	nan
    */
    uint32 Reserved0E;
  /**
    * RegisterName: inputmux
    * AddressOffset: 0x078
    * ResetValue: 0x00000024
    * Description: Input mux control
    */
    Nxp_Tef810x_Mod07_InputmuxUnion_t Inputmux_ust;        /*## attribute Inputmux_ust */
  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0x07C
    * ResetValue: 0x00004020
    * Description: 	nan
    */
    uint32 Reserved0F;
  /**
    * RegisterName: Reserved10
    * AddressOffset: 0x080
    * ResetValue: 0x0000201D
    * Description: 	nan
    */
    uint32 Reserved10;
  /**
    * RegisterName: Reserved11
    * AddressOffset: 0x084
    * ResetValue: 0x0002467D
    * Description: 	nan
    */
    uint32 Reserved11;
  /**
    * RegisterName: Reserved12
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved12;
  /**
    * RegisterName: outputmux
    * AddressOffset: 0x08C
    * ResetValue: 0x5CE20030
    * Description: Output mux control
    */
    Nxp_Tef810x_Mod07_OutputmuxUnion_t Outputmux_ust;        /*## attribute Outputmux_ust */
  /**
    * RegisterName: outputmux_data_adc1
    * AddressOffset: 0x090
    * ResetValue: 0x00005CE2
    * Description: Output mux debug data control
    */
    Nxp_Tef810x_Mod07_OutputmuxDataAdc1Union_t OutputmuxDataAdc1_ust;        /*## attribute OutputmuxDataAdc1_ust */
  /**
    * RegisterName: Reserved13
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved13;

    uint32 gap04_au32[2];        /* gap 4 in register space */  /**
    * RegisterName: cal_monitor_status
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000000
    * Description: Calibration monitor status
    */
    Nxp_Tef810x_Mod07_CalMonitorStatusUnion_t CalMonitorStatus_ust;        /*## attribute CalMonitorStatus_ust */
  /**
    * RegisterName: Reserved14
    * AddressOffset: 0x0A4
    * ResetValue: 0x01000040
    * Description: 	nan
    */
    uint32 Reserved14;
  /**
    * RegisterName: Reserved15
    * AddressOffset: 0x0A8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved15;
  /**
    * RegisterName: Reserved16
    * AddressOffset: 0x0AC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved16;
  /**
    * RegisterName: Reserved17
    * AddressOffset: 0x0B0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved17;
  /**
    * RegisterName: Reserved18
    * AddressOffset: 0x0B4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved18;
  /**
    * RegisterName: Reserved19
    * AddressOffset: 0x0B8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved19;
  /**
    * RegisterName: Reserved1A
    * AddressOffset: 0x0BC
    * ResetValue: 0x0000ACA9
    * Description: 	nan
    */
    uint32 Reserved1A;
  /**
    * RegisterName: Reserved1B
    * AddressOffset: 0x0C0
    * ResetValue: 0x291B2509
    * Description: 	nan
    */
    uint32 Reserved1B;

    uint32 gap05_au32[15];        /* gap 5 in register space */  /**
    * RegisterName: Reserved1C
    * AddressOffset: 0x100
    * ResetValue: 0x20040100
    * Description: 	nan
    */
    uint32 Reserved1C;
  /**
    * RegisterName: Reserved1D
    * AddressOffset: 0x104
    * ResetValue: 0x08010040
    * Description: 	nan
    */
    uint32 Reserved1D;
  /**
    * RegisterName: Reserved1E
    * AddressOffset: 0x108
    * ResetValue: 0xC0080080
    * Description: 	nan
    */
    uint32 Reserved1E;
  /**
    * RegisterName: Reserved1F
    * AddressOffset: 0x10C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved1F;
  /**
    * RegisterName: Reserved20
    * AddressOffset: 0x110
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved20;
  /**
    * RegisterName: Reserved21
    * AddressOffset: 0x114
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved21;
  /**
    * RegisterName: Reserved22
    * AddressOffset: 0x118
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved22;
  /**
    * RegisterName: Reserved23
    * AddressOffset: 0x11C
    * ResetValue: 0x00C00800
    * Description: 	nan
    */
    uint32 Reserved23;
  /**
    * RegisterName: Reserved24
    * AddressOffset: 0x120
    * ResetValue: 0x090708F8
    * Description: 	nan
    */
    uint32 Reserved24;
  /**
    * RegisterName: Reserved25
    * AddressOffset: 0x124
    * ResetValue: 0x20040100
    * Description: 	nan
    */
    uint32 Reserved25;
  /**
    * RegisterName: Reserved26
    * AddressOffset: 0x128
    * ResetValue: 0x08010040
    * Description: 	nan
    */
    uint32 Reserved26;
  /**
    * RegisterName: Reserved27
    * AddressOffset: 0x12C
    * ResetValue: 0xC0080080
    * Description: 	nan
    */
    uint32 Reserved27;
  /**
    * RegisterName: Reserved28
    * AddressOffset: 0x130
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved28;
  /**
    * RegisterName: Reserved29
    * AddressOffset: 0x134
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved29;
  /**
    * RegisterName: Reserved2A
    * AddressOffset: 0x138
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved2A;
  /**
    * RegisterName: Reserved2B
    * AddressOffset: 0x13C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved2B;
  /**
    * RegisterName: Reserved2C
    * AddressOffset: 0x140
    * ResetValue: 0x00C00800
    * Description: 	nan
    */
    uint32 Reserved2C;
  /**
    * RegisterName: Reserved2D
    * AddressOffset: 0x144
    * ResetValue: 0x090708F8
    * Description: 	nan
    */
    uint32 Reserved2D;

    uint32 gap06_au32[46];        /* gap 6 in register space */  /**
    * RegisterName: Reserved2E
    * AddressOffset: 0x200
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved2E;
  /**
    * RegisterName: Reserved2F
    * AddressOffset: 0x204
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved2F;
  /**
    * RegisterName: Reserved30
    * AddressOffset: 0x208
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved30;
  /**
    * RegisterName: Reserved31
    * AddressOffset: 0x20C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved31;
  /**
    * RegisterName: Reserved32
    * AddressOffset: 0x210
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved32;
  /**
    * RegisterName: Reserved33
    * AddressOffset: 0x214
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved33;
  /**
    * RegisterName: Reserved34
    * AddressOffset: 0x218
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved34;
  /**
    * RegisterName: Reserved35
    * AddressOffset: 0x21C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved35;
  /**
    * RegisterName: Reserved36
    * AddressOffset: 0x220
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved36;
  /**
    * RegisterName: Reserved37
    * AddressOffset: 0x224
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved37;
  /**
    * RegisterName: Reserved38
    * AddressOffset: 0x228
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved38;
  /**
    * RegisterName: Reserved39
    * AddressOffset: 0x22C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved39;
  /**
    * RegisterName: Reserved3A
    * AddressOffset: 0x230
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3A;
  /**
    * RegisterName: Reserved3B
    * AddressOffset: 0x234
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3B;
  /**
    * RegisterName: Reserved3C
    * AddressOffset: 0x238
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3C;
  /**
    * RegisterName: Reserved3D
    * AddressOffset: 0x23C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3D;
  /**
    * RegisterName: Reserved3E
    * AddressOffset: 0x240
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3E;
  /**
    * RegisterName: Reserved3F
    * AddressOffset: 0x244
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved3F;

    uint32 gap07_au32[46];        /* gap 7 in register space */  /**
    * RegisterName: Reserved40
    * AddressOffset: 0x300
    * ResetValue: 0x00007777
    * Description: 	nan
    */
    uint32 Reserved40;
  /**
    * RegisterName: bias_maindac
    * AddressOffset: 0x304
    * ResetValue: 0x00000077
    * Description: Bias setting main DAC
    */
    Nxp_Tef810x_Mod07_BiasMaindacUnion_t BiasMaindac_ust;        /*## attribute BiasMaindac_ust */
  /**
    * RegisterName: Reserved41
    * AddressOffset: 0x308
    * ResetValue: 0x00000007
    * Description: 	nan
    */
    uint32 Reserved41;
  /**
    * RegisterName: bias_source_follower
    * AddressOffset: 0x30C
    * ResetValue: 0x00000277
    * Description: Bias setting source follower
    */
    Nxp_Tef810x_Mod07_BiasSourceFollowerUnion_t BiasSourceFollower_ust;        /*## attribute BiasSourceFollower_ust */
  /**
    * RegisterName: Reserved42
    * AddressOffset: 0x310
    * ResetValue: 0x00007777
    * Description: 	nan
    */
    uint32 Reserved42;
  /**
    * RegisterName: Reserved43
    * AddressOffset: 0x314
    * ResetValue: 0x00000077
    * Description: 	nan
    */
    uint32 Reserved43;
  /**
    * RegisterName: Reserved44
    * AddressOffset: 0x318
    * ResetValue: 0x00000007
    * Description: 	nan
    */
    uint32 Reserved44;

    uint32 gap08_au32[1];        /* gap 8 in register space */  /**
    * RegisterName: Reserved45
    * AddressOffset: 0x320
    * ResetValue: 0x00000007
    * Description: 	nan
    */
    uint32 Reserved45;

    uint32 gap09_au32[119];        /* gap 9 in register space */  /**
    * RegisterName: Reserved46
    * AddressOffset: 0x500
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved46;
  /**
    * RegisterName: Reserved47
    * AddressOffset: 0x504
    * ResetValue: 0x00000020
    * Description: 	nan
    */
    uint32 Reserved47;

    uint32 gap0A_au32[62];        /* gap 10 in register space */  /**
    * RegisterName: Reserved48
    * AddressOffset: 0x600
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved48;
  /**
    * RegisterName: Reserved49
    * AddressOffset: 0x604
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved49;

    uint32 gap0B_au32[635];        /* gap 11 in register space */  /**
    * RegisterName: Reserved4A
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved4A;

    uint32 gap0C_au32[1];        /* gap 12 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00072201
    * Description: Module identifier
    */
    Nxp_Tef810x_Mod07_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod07_AdcRegister_t;

#endif
