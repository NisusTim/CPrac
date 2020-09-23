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
* @NXP_TEF810X_TimingEngine.h
*/
#ifndef NXP_TEF810X_TIMINGENGINE_H
#define NXP_TEF810X_TIMINGENGINE_H
#include "Std_Types.h"

#define TIMING_ENGINE_MODULE_ADDRESS 0x04
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE0_U16
* RegisterName: MOD04_Timing_control_1_profile0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x4000400A
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE0_U16
* RegisterName: MOD04_Timing_control_2_profile0
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00A00080
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE0_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE0_U16
* RegisterName: MOD04_Timing_control_3_profile0
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000200
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE0_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE1_U16
* RegisterName: MOD04_Timing_control_1_profile1
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x4000400A
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE1_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE1_U16
* RegisterName: MOD04_Timing_control_2_profile1
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00A00080
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE1_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE1_U16
* RegisterName: MOD04_Timing_control_3_profile1
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000200
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE1_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE2_U16
* RegisterName: MOD04_Timing_control_1_profile2
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x4000400A
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE2_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE2_U16
* RegisterName: MOD04_Timing_control_2_profile2
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00A00080
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE2_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE2_U16
* RegisterName: MOD04_Timing_control_3_profile2
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00000200
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE2_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE3_U16
* RegisterName: MOD04_Timing_control_1_profile3
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x4000400A
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_1_PROFILE3_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE3_U16
* RegisterName: MOD04_Timing_control_2_profile3
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00A00080
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_2_PROFILE3_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE3_U16
* RegisterName: MOD04_Timing_control_3_profile3
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000200
*/
#define NXP_TEF810X_MOD04_TIMING_CONTROL_3_PROFILE3_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16
* RegisterName: MOD04_Chirp_sequence_control
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00010020
*/
#define NXP_TEF810X_MOD04_CHIRP_SEQUENCE_CONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD04_CHIRP_SEQUENCE_INTERVAL_CONTROL_U16
* RegisterName: MOD04_chirp_sequence_interval_control
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD04_CHIRP_SEQUENCE_INTERVAL_CONTROL_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16
* RegisterName: MOD04_Chirp_trigger_mode_control
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD04_JUMPBACK_PERIOD_CONTROL_U16
* RegisterName: MOD04_jumpback_period_control
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000004
*/
#define NXP_TEF810X_MOD04_JUMPBACK_PERIOD_CONTROL_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16
* RegisterName: MOD04_dc_power_on_delay_control
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00FF4E20
*/
#define NXP_TEF810X_MOD04_DC_POWER_ON_DELAY_CONTROL_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD04_FORCE_DC_POWERON_CONTROL_U16
* RegisterName: MOD04_force_dc_poweron_control
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD04_FORCE_DC_POWERON_CONTROL_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD04_TX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16
* RegisterName: MOD04_tx_dc_power_on_group_delay_control
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD04_TX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD04_RX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16
* RegisterName: MOD04_rx_dc_power_on_group_delay_control
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD04_RX_DC_POWER_ON_GROUP_DELAY_CONTROL_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD04_CHIRP_DYNAMIC_POWER_CONTROL_U16
* RegisterName: MOD04_chirp_dynamic_power_control
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00010200
*/
#define NXP_TEF810X_MOD04_CHIRP_DYNAMIC_POWER_CONTROL_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD04_TX_RX_DC_POWER_ON_DELAY_FINE_CONTROL_U16
* RegisterName: MOD04_tx_rx_dc_power_on_delay_fine_control
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0xFF7F3F00
*/
#define NXP_TEF810X_MOD04_TX_RX_DC_POWER_ON_DELAY_FINE_CONTROL_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16
* RegisterName: MOD04_chirp_global_control
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00010000
*/
#define NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD04_MODULEID_U16
* RegisterName: MOD04_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00042201
*/
#define NXP_TEF810X_MOD04_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod04_TIMING_CONTROL_1_PROFILEBits_t
* RegisterName: Timing_control_1_profile
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: dwell_time_profile0
	* Description: Internal circuit stabilization time required before starting a chirp sequence. Two use scenario.
	* 
	* Normal chirp mode.  In this mode,  dwell_timer starts at the end of "dc_poweron_delay"".
	* Power save chirp mode: In this mode this timer starts  on chirp_start trigger. In this case the dc_power_delay is assumed to be covered by the dwell_timer.
	* In power save chirp mode, a minimum value of 10 us need to be considered  (considering the minimum dc_power_on_delay)
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x010 to 0xFFE
	* 3. Useful values : Based on application 
	* 3.a Dynamic power is controlled at chirp sequence level  from central controller controlled by central_controller.dynamic_power_control_enable(0x044)  ) : minimum vale = 400 ns
	* 3.b  chirp level power  is controlled by timing engine ( TX & RX power is  controlled at individual chirp level controlled by timing_engine. Chirp_trigger_mode_control (addr 0x038) chirp_power_mode (bit 9)) : minimum vale = 10 us
	* 
	* 
	* Important note: 16 clock cycle is the mininum  time required for the clock  dividers  within sweep control.  
	* 
	* Dwell time expressed in 25 ns time base (40 MHz clock)
	*/
    uint32 DwellTimeProfile0: 12;        /*## attribute DwellTimeProfile0 */
   /**
	* BitsName: tx_bps_and_transmission_en_time_profile0
	* Description: Transmission on delay from timing reference point ("tx_bps_control_and_tx_en_time_profile0") 
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x002 to Tdwell or Tsettle  ( depends on the enable point)
	* 3. Useful values :  less than or equal to Tdwell incase of control point is Tdwell or less than safety_monitor_delay incase of control point is Tsettle 
	* 
	* Applicable for   enable transmission  and transmission phase shift control.
	* This fine control is provided for fine control of the exact position at  the transmission is enabled. ( possibility to enable transmission within  Tdwell or Tsettle window). If the control point is settle and this delay is more than or equal to safety monitor delay, this results in stuckat error from chirp. This means tx,rx parameters to be set correctly well before safety monitor window is enabled. 
	* 
	* Application use model (recommendation)  : Set this bit to 0x002
	*/
    uint32 TxBpsAndTransmissionEnTimeProfile0: 12;        /*## attribute TxBpsAndTransmissionEnTimeProfile0 */
   /**
	* BitsName: tx1_transmission_enable_profile0
	* Description: TX1 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx1TransmissionEnableProfile0: 1;        /*## attribute Tx1TransmissionEnableProfile0 */
   /**
	* BitsName: tx2_transmission_enable_profile0
	* Description: TX2 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx2TransmissionEnableProfile0: 1;        /*## attribute Tx2TransmissionEnableProfile0 */
   /**
	* BitsName: tx3_transmission_enable_profile0
	* Description: TX3 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* 
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx3TransmissionEnableProfile0: 1;        /*## attribute Tx3TransmissionEnableProfile0 */
   /**
	* BitsName: tx1_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase  control
	* TX1 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx1BinaryPhaseControlProfile0: 1;        /*## attribute Tx1BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx2_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase control
	* TX2 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx2BinaryPhaseControlProfile0: 1;        /*## attribute Tx2BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx3_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase  control
	* TX3 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx3BinaryPhaseControlProfile0: 1;        /*## attribute Tx3BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx_bps_control_and_tx_en_time_profile0
	* Description: Controls the trigger point for start of the tx_bps_and_transmission_en_time_profile0 timer.
	* Use scenario: From application point of view,  a provision is added to start transmission and bps switching  either anywhere within dwell timer window or settle timer window.  By using this bit this can be controlled.
	* 
	* 
	* 
	* '0' : Trigger  point is start of Tdwell(T1) .. Position bps control and tx enable within Tdwell time
	* '1' :  Trigger  point is start of Tsettle(T2) Position bps control and tx enable within Tsettle time
	* 
	* Application use model (recommendation)  : Set this bit to 1'b0
	*/
    uint32 TxBpsControlAndTxEnTimeProfile0: 1;        /*## attribute TxBpsControlAndTxEnTimeProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_TimingControl1ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_TIMING_CONTROL_2_PROFILEBits_t
* RegisterName: Timing_control_2_profile
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: number_of_adc_sample_profile0
	* Description: Number of ADC samples in a chirp  before decimation
	* This bit field along with adc_sampling_frequency shall be used together to determine the actual number of samples at the O/P of data interface.
	* Note: Only 13..0 is used in implementation. Upper two bits are ignored
	* 
	* Example: 
	* 
	* If the value programmed is 512 and adc_samplig frequency is 20 MHz, then the no of valid samples send over  the O/P data interface is =256.
	*/
    uint32 NumberOfAdcSampleProfile0: 16;        /*## attribute NumberOfAdcSampleProfile0 */
   /**
	* BitsName: adc_sampling_freq_profile0
	* Description: Controls the decimation chain O/P sampling frequency
	* 
	* 000: 40 MHz (decimation bypass)
	* 001: 20 MHz 
	* 010: 10 MHz 
	* 011: 5 MHz 
	* 100: 2.5 MHz  
	* 
	* Note: This bit field controls the  decimation factor of the decimation chain witthin the serializer  IP.  Please note that   the setting in this register is active only when a chirp is triggered.   Till such time the   decimation factor is controlled by the  serializer itslef.
	*/
    uint32 AdcSamplingFreqProfile0: 3;        /*## attribute AdcSamplingFreqProfile0 */
   /**
	* BitsName: pdc_bw_sel_profile0
	* Description: This bit is used to select the bandwidth of the decimation filter in the serialiser IP.
	* 0:   Narrow bandwidth
	*  1:   Large bandwidth
	*/
    uint32 PdcBwSelProfile0: 1;        /*## attribute PdcBwSelProfile0 */
   /**
	* BitsName: settle_time_profile0
	* Description: Once the chirp engine is started, a minimum time is required for the chirp ckt to stabilize and to  reach the linear FM transmission point.  Only after this time ADC samples can be captured. A programmable timer is provided for this purpose. This timer start  on expiry of dwell_timer.
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x001 to 0xFFE
	* 3. Useful values : TBD based on application (typical values may be 0 to 10 us). 
	* 
	* 
	* From an application point of view it is recommended to use a value of 2.5 us minimum
	*/
    uint32 SettleTimeProfile0: 12;        /*## attribute SettleTimeProfile0 */
}Nxp_Tef810x_Mod04_TimingControl2ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_TIMING_CONTROL_3_PROFILEBits_t
* RegisterName: Timing_control_3_profile
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: chirp_Interval_timer_profile0
	* Description: Chirp micro cycle (interval) timer. 
	* Consists of Tdwell+ Tsettle+ TNoOfADCSamples+TJumpBack+Treset
	* This timer starts upon receiving a chirp trigger. On expiry of timer the timer is re-triggered till  the no  of programmed chirp  in a sequence is  generated.
	* 
	* A value of '5' programmed  means five clock cycle delay
	* 
	* Use model:   The chrip  interval timer has to be more than or equal to Tdwell+ Tsettle+ TNoOfADCSamples+TJumpBack+Treset. 
	* 
	* 
	* Please not that the Treset is not separately programmable within the timing engine register space. The value of Treset is decided by the reset slop of the chirp  programmed within the sweep control moule, and have a dependency on the sweep control modes selected.
	* 
	* 
	* Typical values depended on the application profile 
	* 
	* Chirp period expressed in 25ns time base (40 MHz).
	*/
    uint32 ChirpIntervalTimerProfile0: 22;        /*## attribute ChirpIntervalTimerProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: rx1_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver  1 is enabled or disabled  for current chirp
	* 0: RX1 is disabled 
	* 1: RX1 is enabled
	*/
    uint32 Rx1ActiveProfile0: 1;        /*## attribute Rx1ActiveProfile0 */
   /**
	* BitsName: rx2_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver  2 is enabled or disabled  for current chirp
	* 0: RX2 is disabled 
	* 1: RX2 is enabled
	*/
    uint32 Rx2ActiveProfile0: 1;        /*## attribute Rx2ActiveProfile0 */
   /**
	* BitsName: rx3_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* Receiver  3 is enabled or disabled  for current chirp
	* 0: RX3 is disabled 
	* 1: RX3 is enabled
	*/
    uint32 Rx3ActiveProfile0: 1;        /*## attribute Rx3ActiveProfile0 */
   /**
	* BitsName: rx4_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver 4 is enabled or disabled  for current chirp
	* 0: RX4 is disabled 
	* 1: RX4 is enabled
	*/
    uint32 Rx4ActiveProfile0: 1;        /*## attribute Rx4ActiveProfile0 */
   /**
	* BitsName: tx1_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 1 is enabled or disabled  for current chirp
	* 0: TX1 is disabled 
	* 1: TX1 is enabled
	*/
    uint32 Tx1ActiveProfile0: 1;        /*## attribute Tx1ActiveProfile0 */
   /**
	* BitsName: tx2_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 2 is enabled or disabled  for current chirp
	* 0: TX2 is disabled 
	* 1: TX2 is enabled
	*/
    uint32 Tx2ActiveProfile0: 1;        /*## attribute Tx2ActiveProfile0 */
   /**
	* BitsName: tx3_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 3 is enabled or disabled  for current chirp
	* 0: TX3 is disabled 
	* 1: TX3 is enabled
	*/
    uint32 Tx3ActiveProfile0: 1;        /*## attribute Tx3ActiveProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod04_TimingControl3ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_CHIRP_SEQUENCE_CONTROLBits_t
* RegisterName: Chirp_sequence_control
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: no_of_chirp_in_a_sequence
	* Description: Controls number  of chirps within a chirp sequence
	* Allowed values  : 0x0001 to 0xFFFE
	*/
    uint32 NoOfChirpInASequence: 16;        /*## attribute NoOfChirpInASequence */
   /**
	* BitsName: no_of_sequence
	* Description: Control the no of chirp sequence in case of burst of chirp sequence.  
	* A chirp sequence is repeated for  the value programmed
	* Allowed values  : 0x01 to 0xFE
	* Use model
	* A value programmed to a value '6' means six chirp sequence after a chirp start trigger is received
	* 
	* For normal   radar data acquisition program this register to 0x01 ( means at  teh end of one acquistion the timing engin ewait for another trigger from MCU to start acquisition again)
	*/
    uint32 NoOfSequence: 8;        /*## attribute NoOfSequence */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_ChirpSequenceControlBits_t;
    /**
* Nxp_Tef810x_Mod04_CHIRP_SEQUENCE_INTERVAL_CONTROLBits_t
* RegisterName: chirp_sequence_interval_control
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: chirp_sequence_interval
	* Description: Values to be programmed  to be aligned with radar system cycle
	* Allowed values  : 0x00000001 to 0xFFFFFFFE
	* 
	* 
	* Note:  If t the no_of_sequence is set to 0x01,   then  program this register with a value 0x01 . in this case thsi timer will reamin expired  and the chirp trigger can be totally under the control of the user.
	*/
    uint32 ChirpSequenceInterval: 32;        /*## attribute ChirpSequenceInterval */
}Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlBits_t;
    /**
* Nxp_Tef810x_Mod04_CHIRP_TRIGGER_MODE_CONTROLBits_t
* RegisterName: Chirp_trigger_mode_control
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: chirp_trigger_mode
	* Description: 1?b1 : 
	* ext. trigger mode : Chirp_start_trigger is coming from another Dolphin  or from an interfacing MCU. Please look at ext_trig_type for more details on use.
	* 
	* 1?b0: 
	* SPI trigger mode: In this mode the timing engine can be triggered through a SPI write. Please note that when configured in SPI trigger node, the chirp timing engine can also generate a chirp_start signal which can be routed to an external pin. This can be used either to trigger other Dolphin IC?s   on same PCB or can be used by MCU for timing engine status (busy) monitoring.
	* 
	* In this mode the following delay shall be considered ( 56 SPI clock  +  four 40 MHz clock cycle +- one MHz clock uncertainty)
	* 
	* 
	* Note:  if ext trigger mode is selected, then, chirp_start_pad need to be configured to I/P mode  in CC module  to get the signal into   Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 ChirpTriggerMode: 1;        /*## attribute ChirpTriggerMode */
   /**
	* BitsName: ext_trig_type
	* Description: In external trigger mode the timing engine can be triggered through an external pin driven chirp start. Here there could be two possibilities
	* 1'b0 : Synchronous chirp start 1. Chirp start is coming from another Dolphin or from a MCU using Dolphin 40 MHz clock as a source to drive chirp_start)
	* 1'b1 : Asynchronous chirp start trigger (chirp start is coming from and asynchronous source  such as MCU with an independent clock)               
	* 
	* Note:  chirp_start_pad need to be configured to I/P mode  in CC module  to get the signal into   Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 ExtTrigType: 1;        /*## attribute ExtTrigType */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_mode_for_chirp_start_out
	* Description: If the  Dolphin is configured for SPI trigger mode,  then a chirp_start signal can be made available  at a Dolphin pin  ( can be used  for triggering another Dolphin). Two modes supported 
	* 
	* 0: Mode 1:  upon receipt of SPI initiated trigger to the chirp engine, the chirp start is asserted on same clock edge. The chirp start is asserted at the end of programmed chirp sequence along with ready interrupt assertion.  This type of signal will be useful to MCU to track the data acquisition cycle as a whole (chirp engine busy flag)
	* 
	* 1: Mode 2: Here the chirp start get de-asserted along with the individual chirp reset, and get asserted again at exact time point where in the next chirp is started. This type of waveform will be useful to MCU to track the individual chirp   at each timing reference points. This will be useful to identify the silent periods within a chirp to initiate a SPI sequence to aid dynamic chirp waveform (based on a bank of profile registers available within chirp engine)
	* 
	* 
	* Note:  chirp_start_pad need to be configured to O/P mode  in CC module  to get the signal out of Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 SelModeForChirpStartOut: 1;        /*## attribute SelModeForChirpStartOut */
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
	* BitsName: chirp_power_mode
	* Description: Dynamic power control to TX and RX unit at individial chirp level
	* 
	* 0: No dynamic control  
	* 1: Dynamic power control active (controlled at individual chirp level). This bit set to '1' is valid only when dynamic power down mode is set from  CC.  
	* 
	* Note: If dc_enabled_per_chirp is set in the register, please ensure value of TDwell is more than 10 us
	*/
    uint32 ChirpPowerMode: 1;        /*## attribute ChirpPowerMode */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 14;        /*## attribute Reserved3 */
   /**
	* BitsName: csi2_frame_mode_sel
	* Description: In CSI2 mode,  a ready_int form TE may not be available at interface level.  In this case a frame interrupt from CSI2 RX can be used  by the micro controller.
	* USe model  is similar to the ready_int.
	* 
	* 00: csi2 frame deactivation at end of a  sequence.
	* 01: Reserved
	* 10: csi2 frame deactivation at end of every chirp
	* 11: Reserved
	*/
    uint32 Csi2FrameModeSel: 2;        /*## attribute Csi2FrameModeSel */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 4;        /*## attribute Reserved4 */
   /**
	* BitsName: ready_int_mode_sel
	* Description: Many possibility for generation of end of chirp interrupt (ready_int)
	* 
	* 00: ready interrupt at end of a  sequence (standard use case).  The MCU need memory to store  a complete chirp sequence data in its buffer and wait for ready Interrupt to start processing data
	* 01: Interrupt at end of expiry of the chirp_sequence_interval_timer (radar system cycle).. IF chirp  sequence interval is less than  data acquistion time, then do not use this option
	* 10: Interrupt at end of every chirp (typically useful in power save mode or systems interested in real time processing or systems with less memory. Process the received data as it is being received)
	*/
    uint32 ReadyIntModeSel: 2;        /*## attribute ReadyIntModeSel */
}Nxp_Tef810x_Mod04_ChirpTriggerModeControlBits_t;
    /**
* Nxp_Tef810x_Mod04_JUMPBACK_PERIOD_CONTROLBits_t
* RegisterName: jumpback_period_control
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: jump_back_time
	* Description: At the end of active ADC sample acquisition, a small time (typically 400 ns)  can be considered before resetting the chirp.  
	* Only for flexibility and fine tuning . 
	* Allowed values: 0x01 to 0xFE
	* 
	* In most use cases, no harm in going with the default values. 
	* 
	* The  value of this register need to be carefully considered for progressive chirp modes  ( see sweep control  regsiters.. sweep_control(mod addr 0x05 ) chirpmode(reg addr 0x60))
	*/
    uint32 JumpBackTime: 8;        /*## attribute JumpBackTime */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_JumpbackPeriodControlBits_t;
    /**
* Nxp_Tef810x_Mod04_DC_POWER_ON_DELAY_CONTROLBits_t
* RegisterName: dc_power_on_delay_control
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: dc_poweron_delay
	* Description: In normal chirp mode, once a chirp trigger is received,    the DC power to TX, RX and chirp analog ckt is enabled before initiating the first chirp (controlled by dc_power_on_delay). In this case  a  waiting is required before starting actual chirp ( stabilization time for the analog ckt, and minimum value is 10 us)   
	* 
	* In power save mode  this timer is not used, but  the  value is considered within the e Dwell time. This mean in power save mode the Dwell time has to be minimum 10 us.
	* 
	* 
	* Allowed values: minimum value  to 0xFFFE
	* Minimum value : 10 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case)
	* 
	* 
	* 
	* 
	* Normal mode = 10 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case) ( max time coming from chirp module)
	* power save mode =  50 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case) 
	* 
	* Normal chirp mode :  All modules are always powerd on  barring TX and RX units.  RX and RX units  are powerd on by timing engine at chirp sequence level. Once powered on  the modules reamin powered on tilll end  of chirp sequence
	* 
	* Extended normal  mode : This is an extension of normal chirp mode, where in   teh TX and RX unit power is controlled at individual  chirp level
	* 
	* Power save mode : The following modules (under software control)  are powerd off outside chirp sequence active  ( TX,RX, ADC, LO, Chirp analog)
	*/
    uint32 DcPoweronDelay: 16;        /*## attribute DcPoweronDelay */
   /**
	* BitsName: safety_monitor_delay
	* Description: Safety monitoring has to be enabled before capturing valid ADC data samples. .However if   it is enabled, much before  sampling adc_data,  there is a chance that some of the sensors may throw an error ( typically example is the chirp vco level).  A timer is  provided to fine tune the activation of safety monitoring based on application profile and validation results.
	* The timer starts along with the settle timer. It is possible to position the safety monitoring start anywhere within settle timer.
	* Allowed values : 0x001 to 0xFFE
	* Useful values : Less than or equal to Settle time.
	* If a value more than settle time is programmed, then  on expiry of settle timer,  safety monitoring will be initiated. 
	* 
	* In an application context, this register to be programmed with maximum value. With this max value programmed, irrespective of the profiles used with different settle timer value, the safety monitoring always active with actual ADC acquisition window.
	*/
    uint32 SafetyMonitorDelay: 12;        /*## attribute SafetyMonitorDelay */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_DcPowerOnDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_FORCE_DC_POWERON_CONTROLBits_t
* RegisterName: force_dc_poweron_control
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: force_dc_poweron
	* Description: 1'b1 : All units (TX and RX) are always on
	* 1'b0: normal mode of operation
	* 
	* Set this bit to always '0' in an application context
	*/
    uint32 ForceDcPoweron: 1;        /*## attribute ForceDcPoweron */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_ForceDcPoweronControlBits_t;
    /**
* Nxp_Tef810x_Mod04_TX_DC_POWER_ON_GROUP_DELAY_CONTROLBits_t
* RegisterName: tx_dc_power_on_group_delay_control
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: tx_group_delay_from_chirp_start
	* Description: Fine control on TX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of Transmitter group( All TX together) can be controlled  from the chirp_start trigger. The value has to be less than or equal to the  dc_power_on delay
	* Allowed values: 0x0001 to less than dc_power_delay programmed
	* Minimum value : 0x0001
	* 
	* Note:  Upon expiry of this programmed delay value, a timing reference point is generated for the entire TX units as a group.  From this point a staggered delay timer is started to control the DC power on point of individual transmit units
	* 
	* For practical application  use a value 0x01
	*/
    uint32 TxGroupDelayFromChirpStart: 16;        /*## attribute TxGroupDelayFromChirpStart */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_RX_DC_POWER_ON_GROUP_DELAY_CONTROLBits_t
* RegisterName: rx_dc_power_on_group_delay_control
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: rx_group_delay_from_chirp_start
	* Description: Fine control on RX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of receiver  group( All RX together) can be controlled  from the chirp_start trigger. The value has to be less than or equal to the  dc_power_on delay.
	* Allowed values: 0x0001 to less than dc_power_delay programmed
	* Minimum value : 0x0001
	* 
	* Note:  Upon expiry of this programmed delay value, a timing reference point is generated for the entire RX units as a group.  From this point a staggered delay timer is started to control the DC power on point of individual receive  units
	* 
	* For practical application  use   a value 1us
	*/
    uint32 RxGroupDelayFromChirpStart: 16;        /*## attribute RxGroupDelayFromChirpStart */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_CHIRP_DYNAMIC_POWER_CONTROLBits_t
* RegisterName: chirp_dynamic_power_control
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: chirp_fast_switch_delay
	* Description: Controls the duration of fast switch.  Typical value is around 6 us. 
	* A programmable time option is provided so that based on validation, actual value can be programmed (flexibility)
	* 
	* Chirp fast switch delay timer used during dynamic power down scenario. The timer is triggered as soon as the chirp_start is triggered and stays for the delay timer and then DE asserted based on which chirp analog is powered up
	* Use model: The value to be programmed shall be  used based on validation results.
	*/
    uint32 ChirpFastSwitchDelay: 16;        /*## attribute ChirpFastSwitchDelay */
   /**
	* BitsName: chirp_fast_switch_enable
	* Description: Enable bit for chirp fast switch for charging
	* 0: Fast switch is not used
	* 1: Fast switching is enabled
	*/
    uint32 ChirpFastSwitchEnable: 1;        /*## attribute ChirpFastSwitchEnable */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod04_ChirpDynamicPowerControlBits_t;
    /**
* Nxp_Tef810x_Mod04_TX_RX_DC_POWER_ON_DELAY_FINE_CONTROLBits_t
* RegisterName: tx_rx_dc_power_on_delay_fine_control
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: tx_rx_dc_power_on_delay_fine_control
	* Description: The delay to enable the TX and ax in staggered way to control the power fluctuations.
	* The timer starts  on expiry of respective _group_delay_timer. 
	* On expiry of this timer, individual TX & RX units are powered on. 
	* 
	* For example TX1, RX1 is controlled by 8 LSB  bits of the register, down counted starting at respective group_delay_timer expiry till the count reaches '0'. Each count step is equal to 25 ns which is one cycle of xtal clock
	* 
	* staggered_en_cotrol_global[7:0]: The delay to enable TX1, RX1
	* staggered_en_cotrol_global[15:8]: The delay to enable TX2, RX2
	* staggered_en_cotrol_global[23:16]: The delay to enable TX3, RX3
	* staggered_en_cotrol_global[31:24]: The delay to enable RX4
	* 
	* 
	* For application the following values are recommended :  (example).. TX group delay = 0 , RX group delay = 1 us.
	* 
	* TX1,RX1 : 0x00  ( TX1 switched on at 0 us and RX1 at 1 us)
	* TX2,RX2 : 0x1F  ( TX2 switched on at 0.8 us and RX2 at 1.8 us)
	* TX3,RX3 : 0x3F  ( TX3 switched on at 1.6 us and RX3 at 2.6 us)
	* TX4,RX4 : 0x7F  ( TX4 switched on at 3.2 us and RX4 at 4.2 us)
	*/
    uint32 TxRxDcPowerOnDelayFineControl: 32;        /*## attribute TxRxDcPowerOnDelayFineControl */
}Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlBits_t;
    /**
* Nxp_Tef810x_Mod04_CHIRP_GLOBAL_CONTROLBits_t
* RegisterName: chirp_global_control
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: chirp_start
	* Description: SPI trigger to chirp start. Once written, this register on read indicates the busy status of the timing engine
	* 0: Timing engine free
	* 1: Timing engine busy
	*/
    uint32 ChirpStart: 1;        /*## attribute ChirpStart */
   /**
	* BitsName: chirp_enable
	* Description: Usemodel 1:
	* Enable chirp. This bit need to  be set (global enable for chirp digital). 
	* 0: The chirp engine is inactive and all circuits are clock gated
	* 1: Chirp engine is enabled and ready to take  a start chirp commands. This bit is set to '1' in normal chirping mode
	* 
	* Usemodel 2:
	* This bit can also be used for loading the profile registers (of timing engine, sweep control, chirp_afc) without actually triggering the chirp i.e without chirp_start being set. This bit requires pattern of 0-1-0 (toggle) to load the profile registers after the selecting the right profile (chirp_profile_select bits restricted to 3?b000, 3?b001, 3?b010, 3?b011 in this use mode). One example of this use mode, is continuous wave (CW) triggering with fixed frequency
	*/
    uint32 ChirpEnable: 1;        /*## attribute ChirpEnable */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: chirp_profile_select
	* Description: Control  the  profiles to be used  within a given chirp sequence  
	* 3?b000 : All chirp in a sequence based on profile  ?0?
	* 3?b001 :Profile 1
	* 3?b010 : Profile 2
	* 3'b011: profile 3
	* 3'b100: profile 0 -1 -0-1
	* 3'b101: profile 0-1-2-0-1-2
	* 3'b110: profile 0-1-2-3-0-1-2-3
	* 
	* Others : not used
	*/
    uint32 ChirpProfileSelect: 3;        /*## attribute ChirpProfileSelect */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 5;        /*## attribute Reserved1 */
   /**
	* BitsName: enable_profile_reset
	* Description: After an acquisition cycle, theer could be two scenarios
	* 1. Always start with  the first profile for a neq acquisition 
	* 2. Start from  the last active profile
	* Thsi register can be used to  select between this option.
	* 
	* 
	* 0x0: : Continue from where  left 
	* 0x1: For a new sequence always start afresh (Reset the profile at start of the new chirp sequence)
	* 
	* Note: This register must be set to '0' when  "chirp_profile_select" is set for individual profiles ( values less than or equal to 3'b011)
	*/
    uint32 EnableProfileReset: 1;        /*## attribute EnableProfileReset */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: profile_stay_count_val
	* Description: Four profile registers are provided for controlling the chirp parameters. The profile registers can be configured in different sequence (see chirp_profile_select).  By using this register, a given profile is repeated  a number of times (based on value programmed) before moving to the next profile  in the sequence.
	* 0x01 : Profile repeated one time
	* 0x02 : Profile repeated two  time
	* ............
	*/
    uint32 ProfileStayCountVal: 7;        /*## attribute ProfileStayCountVal */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod04_ChirpGlobalControlBits_t;
    /**
* Nxp_Tef810x_Mod04_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets Reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
   /**
	* BitsName: minor_revision
	* Description: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod04_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod04_TimingControl1ProfileBits_t
* RegisterName: Timing_control_1_profile
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x4000400A
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: tx_bps_control_and_tx_en_time_profile0
	* Description: Controls the trigger point for start of the tx_bps_and_transmission_en_time_profile0 timer.
	* Use scenario: From application point of view,  a provision is added to start transmission and bps switching  either anywhere within dwell timer window or settle timer window.  By using this bit this can be controlled.
	* 
	* 
	* 
	* '0' : Trigger  point is start of Tdwell(T1) .. Position bps control and tx enable within Tdwell time
	* '1' :  Trigger  point is start of Tsettle(T2) Position bps control and tx enable within Tsettle time
	* 
	* Application use model (recommendation)  : Set this bit to 1'b0
	*/
    uint32 TxBpsControlAndTxEnTimeProfile0: 1;        /*## attribute TxBpsControlAndTxEnTimeProfile0 */
   /**
	* BitsName: tx3_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase  control
	* TX3 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx3BinaryPhaseControlProfile0: 1;        /*## attribute Tx3BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx2_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase control
	* TX2 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx2BinaryPhaseControlProfile0: 1;        /*## attribute Tx2BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx1_binary_phase_control_profile0
	* Description: Transmission O/P waveform phase  control
	* TX1 output phase shift 
	* '0': in phase
	* '1': Out of phase (180 deg)
	*/
    uint32 Tx1BinaryPhaseControlProfile0: 1;        /*## attribute Tx1BinaryPhaseControlProfile0 */
   /**
	* BitsName: tx3_transmission_enable_profile0
	* Description: TX3 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* 
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx3TransmissionEnableProfile0: 1;        /*## attribute Tx3TransmissionEnableProfile0 */
   /**
	* BitsName: tx2_transmission_enable_profile0
	* Description: TX2 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx2TransmissionEnableProfile0: 1;        /*## attribute Tx2TransmissionEnableProfile0 */
   /**
	* BitsName: tx1_transmission_enable_profile0
	* Description: TX1 transmission control
	* '0': Transmission disabled
	* '1': Transmission enabled during chirp
	* This also controls the  Transmitter fast  charging switch
	*/
    uint32 Tx1TransmissionEnableProfile0: 1;        /*## attribute Tx1TransmissionEnableProfile0 */
   /**
	* BitsName: tx_bps_and_transmission_en_time_profile0
	* Description: Transmission on delay from timing reference point ("tx_bps_control_and_tx_en_time_profile0") 
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x002 to Tdwell or Tsettle  ( depends on the enable point)
	* 3. Useful values :  less than or equal to Tdwell incase of control point is Tdwell or less than safety_monitor_delay incase of control point is Tsettle 
	* 
	* Applicable for   enable transmission  and transmission phase shift control.
	* This fine control is provided for fine control of the exact position at  the transmission is enabled. ( possibility to enable transmission within  Tdwell or Tsettle window). If the control point is settle and this delay is more than or equal to safety monitor delay, this results in stuckat error from chirp. This means tx,rx parameters to be set correctly well before safety monitor window is enabled. 
	* 
	* Application use model (recommendation)  : Set this bit to 0x002
	*/
    uint32 TxBpsAndTransmissionEnTimeProfile0: 12;        /*## attribute TxBpsAndTransmissionEnTimeProfile0 */
   /**
	* BitsName: dwell_time_profile0
	* Description: Internal circuit stabilization time required before starting a chirp sequence. Two use scenario.
	* 
	* Normal chirp mode.  In this mode,  dwell_timer starts at the end of "dc_poweron_delay"".
	* Power save chirp mode: In this mode this timer starts  on chirp_start trigger. In this case the dc_power_delay is assumed to be covered by the dwell_timer.
	* In power save chirp mode, a minimum value of 10 us need to be considered  (considering the minimum dc_power_on_delay)
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x010 to 0xFFE
	* 3. Useful values : Based on application 
	* 3.a Dynamic power is controlled at chirp sequence level  from central controller controlled by central_controller.dynamic_power_control_enable(0x044)  ) : minimum vale = 400 ns
	* 3.b  chirp level power  is controlled by timing engine ( TX & RX power is  controlled at individual chirp level controlled by timing_engine. Chirp_trigger_mode_control (addr 0x038) chirp_power_mode (bit 9)) : minimum vale = 10 us
	* 
	* 
	* Important note: 16 clock cycle is the mininum  time required for the clock  dividers  within sweep control.  
	* 
	* Dwell time expressed in 25 ns time base (40 MHz clock)
	*/
    uint32 DwellTimeProfile0: 12;        /*## attribute DwellTimeProfile0 */
}Nxp_Tef810x_Mod04_TimingControl1ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_TimingControl2ProfileBits_t
* RegisterName: Timing_control_2_profile
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00A00080
*/
typedef struct  {
   /**
	* BitsName: settle_time_profile0
	* Description: Once the chirp engine is started, a minimum time is required for the chirp ckt to stabilize and to  reach the linear FM transmission point.  Only after this time ADC samples can be captured. A programmable timer is provided for this purpose. This timer start  on expiry of dwell_timer.
	* 
	* Use model:  
	* 1. A value of '5' programmed means five  clock cycle delay 
	* 2. Allowed values 0x001 to 0xFFE
	* 3. Useful values : TBD based on application (typical values may be 0 to 10 us). 
	* 
	* 
	* From an application point of view it is recommended to use a value of 2.5 us minimum
	*/
    uint32 SettleTimeProfile0: 12;        /*## attribute SettleTimeProfile0 */
   /**
	* BitsName: pdc_bw_sel_profile0
	* Description: This bit is used to select the bandwidth of the decimation filter in the serialiser IP.
	* 0:   Narrow bandwidth
	*  1:   Large bandwidth
	*/
    uint32 PdcBwSelProfile0: 1;        /*## attribute PdcBwSelProfile0 */
   /**
	* BitsName: adc_sampling_freq_profile0
	* Description: Controls the decimation chain O/P sampling frequency
	* 
	* 000: 40 MHz (decimation bypass)
	* 001: 20 MHz 
	* 010: 10 MHz 
	* 011: 5 MHz 
	* 100: 2.5 MHz  
	* 
	* Note: This bit field controls the  decimation factor of the decimation chain witthin the serializer  IP.  Please note that   the setting in this register is active only when a chirp is triggered.   Till such time the   decimation factor is controlled by the  serializer itslef.
	*/
    uint32 AdcSamplingFreqProfile0: 3;        /*## attribute AdcSamplingFreqProfile0 */
   /**
	* BitsName: number_of_adc_sample_profile0
	* Description: Number of ADC samples in a chirp  before decimation
	* This bit field along with adc_sampling_frequency shall be used together to determine the actual number of samples at the O/P of data interface.
	* Note: Only 13..0 is used in implementation. Upper two bits are ignored
	* 
	* Example: 
	* 
	* If the value programmed is 512 and adc_samplig frequency is 20 MHz, then the no of valid samples send over  the O/P data interface is =256.
	*/
    uint32 NumberOfAdcSampleProfile0: 16;        /*## attribute NumberOfAdcSampleProfile0 */
}Nxp_Tef810x_Mod04_TimingControl2ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_TimingControl3ProfileBits_t
* RegisterName: Timing_control_3_profile
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000200
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: tx3_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 3 is enabled or disabled  for current chirp
	* 0: TX3 is disabled 
	* 1: TX3 is enabled
	*/
    uint32 Tx3ActiveProfile0: 1;        /*## attribute Tx3ActiveProfile0 */
   /**
	* BitsName: tx2_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 2 is enabled or disabled  for current chirp
	* 0: TX2 is disabled 
	* 1: TX2 is enabled
	*/
    uint32 Tx2ActiveProfile0: 1;        /*## attribute Tx2ActiveProfile0 */
   /**
	* BitsName: tx1_active_profile0
	* Description: Feature to enable or disable a particular TX module in an active chirp
	* 
	* Transmitter 1 is enabled or disabled  for current chirp
	* 0: TX1 is disabled 
	* 1: TX1 is enabled
	*/
    uint32 Tx1ActiveProfile0: 1;        /*## attribute Tx1ActiveProfile0 */
   /**
	* BitsName: rx4_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver 4 is enabled or disabled  for current chirp
	* 0: RX4 is disabled 
	* 1: RX4 is enabled
	*/
    uint32 Rx4ActiveProfile0: 1;        /*## attribute Rx4ActiveProfile0 */
   /**
	* BitsName: rx3_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* Receiver  3 is enabled or disabled  for current chirp
	* 0: RX3 is disabled 
	* 1: RX3 is enabled
	*/
    uint32 Rx3ActiveProfile0: 1;        /*## attribute Rx3ActiveProfile0 */
   /**
	* BitsName: rx2_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver  2 is enabled or disabled  for current chirp
	* 0: RX2 is disabled 
	* 1: RX2 is enabled
	*/
    uint32 Rx2ActiveProfile0: 1;        /*## attribute Rx2ActiveProfile0 */
   /**
	* BitsName: rx1_active_profile0
	* Description: Feature to enable or disable a particular RX module in an active chirp
	* 
	* Receiver  1 is enabled or disabled  for current chirp
	* 0: RX1 is disabled 
	* 1: RX1 is enabled
	*/
    uint32 Rx1ActiveProfile0: 1;        /*## attribute Rx1ActiveProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: chirp_Interval_timer_profile0
	* Description: Chirp micro cycle (interval) timer. 
	* Consists of Tdwell+ Tsettle+ TNoOfADCSamples+TJumpBack+Treset
	* This timer starts upon receiving a chirp trigger. On expiry of timer the timer is re-triggered till  the no  of programmed chirp  in a sequence is  generated.
	* 
	* A value of '5' programmed  means five clock cycle delay
	* 
	* Use model:   The chrip  interval timer has to be more than or equal to Tdwell+ Tsettle+ TNoOfADCSamples+TJumpBack+Treset. 
	* 
	* 
	* Please not that the Treset is not separately programmable within the timing engine register space. The value of Treset is decided by the reset slop of the chirp  programmed within the sweep control moule, and have a dependency on the sweep control modes selected.
	* 
	* 
	* Typical values depended on the application profile 
	* 
	* Chirp period expressed in 25ns time base (40 MHz).
	*/
    uint32 ChirpIntervalTimerProfile0: 22;        /*## attribute ChirpIntervalTimerProfile0 */
}Nxp_Tef810x_Mod04_TimingControl3ProfileBits_t;
    /**
* Nxp_Tef810x_Mod04_ChirpSequenceControlBits_t
* RegisterName: Chirp_sequence_control
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00010020
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: no_of_sequence
	* Description: Control the no of chirp sequence in case of burst of chirp sequence.  
	* A chirp sequence is repeated for  the value programmed
	* Allowed values  : 0x01 to 0xFE
	* Use model
	* A value programmed to a value '6' means six chirp sequence after a chirp start trigger is received
	* 
	* For normal   radar data acquisition program this register to 0x01 ( means at  teh end of one acquistion the timing engin ewait for another trigger from MCU to start acquisition again)
	*/
    uint32 NoOfSequence: 8;        /*## attribute NoOfSequence */
   /**
	* BitsName: no_of_chirp_in_a_sequence
	* Description: Controls number  of chirps within a chirp sequence
	* Allowed values  : 0x0001 to 0xFFFE
	*/
    uint32 NoOfChirpInASequence: 16;        /*## attribute NoOfChirpInASequence */
}Nxp_Tef810x_Mod04_ChirpSequenceControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlBits_t
* RegisterName: chirp_sequence_interval_control
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: chirp_sequence_interval
	* Description: Values to be programmed  to be aligned with radar system cycle
	* Allowed values  : 0x00000001 to 0xFFFFFFFE
	* 
	* 
	* Note:  If t the no_of_sequence is set to 0x01,   then  program this register with a value 0x01 . in this case thsi timer will reamin expired  and the chirp trigger can be totally under the control of the user.
	*/
    uint32 ChirpSequenceInterval: 32;        /*## attribute ChirpSequenceInterval */
}Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ChirpTriggerModeControlBits_t
* RegisterName: Chirp_trigger_mode_control
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x00000100
*/
typedef struct  {
   /**
	* BitsName: ready_int_mode_sel
	* Description: Many possibility for generation of end of chirp interrupt (ready_int)
	* 
	* 00: ready interrupt at end of a  sequence (standard use case).  The MCU need memory to store  a complete chirp sequence data in its buffer and wait for ready Interrupt to start processing data
	* 01: Interrupt at end of expiry of the chirp_sequence_interval_timer (radar system cycle).. IF chirp  sequence interval is less than  data acquistion time, then do not use this option
	* 10: Interrupt at end of every chirp (typically useful in power save mode or systems interested in real time processing or systems with less memory. Process the received data as it is being received)
	*/
    uint32 ReadyIntModeSel: 2;        /*## attribute ReadyIntModeSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: csi2_frame_mode_sel
	* Description: In CSI2 mode,  a ready_int form TE may not be available at interface level.  In this case a frame interrupt from CSI2 RX can be used  by the micro controller.
	* USe model  is similar to the ready_int.
	* 
	* 00: csi2 frame deactivation at end of a  sequence.
	* 01: Reserved
	* 10: csi2 frame deactivation at end of every chirp
	* 11: Reserved
	*/
    uint32 Csi2FrameModeSel: 2;        /*## attribute Csi2FrameModeSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 14;        /*## attribute Reserved1 */
   /**
	* BitsName: chirp_power_mode
	* Description: Dynamic power control to TX and RX unit at individial chirp level
	* 
	* 0: No dynamic control  
	* 1: Dynamic power control active (controlled at individual chirp level). This bit set to '1' is valid only when dynamic power down mode is set from  CC.  
	* 
	* Note: If dc_enabled_per_chirp is set in the register, please ensure value of TDwell is more than 10 us
	*/
    uint32 ChirpPowerMode: 1;        /*## attribute ChirpPowerMode */
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
	* BitsName: sel_mode_for_chirp_start_out
	* Description: If the  Dolphin is configured for SPI trigger mode,  then a chirp_start signal can be made available  at a Dolphin pin  ( can be used  for triggering another Dolphin). Two modes supported 
	* 
	* 0: Mode 1:  upon receipt of SPI initiated trigger to the chirp engine, the chirp start is asserted on same clock edge. The chirp start is asserted at the end of programmed chirp sequence along with ready interrupt assertion.  This type of signal will be useful to MCU to track the data acquisition cycle as a whole (chirp engine busy flag)
	* 
	* 1: Mode 2: Here the chirp start get de-asserted along with the individual chirp reset, and get asserted again at exact time point where in the next chirp is started. This type of waveform will be useful to MCU to track the individual chirp   at each timing reference points. This will be useful to identify the silent periods within a chirp to initiate a SPI sequence to aid dynamic chirp waveform (based on a bank of profile registers available within chirp engine)
	* 
	* 
	* Note:  chirp_start_pad need to be configured to O/P mode  in CC module  to get the signal out of Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 SelModeForChirpStartOut: 1;        /*## attribute SelModeForChirpStartOut */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: ext_trig_type
	* Description: In external trigger mode the timing engine can be triggered through an external pin driven chirp start. Here there could be two possibilities
	* 1'b0 : Synchronous chirp start 1. Chirp start is coming from another Dolphin or from a MCU using Dolphin 40 MHz clock as a source to drive chirp_start)
	* 1'b1 : Asynchronous chirp start trigger (chirp start is coming from and asynchronous source  such as MCU with an independent clock)               
	* 
	* Note:  chirp_start_pad need to be configured to I/P mode  in CC module  to get the signal into   Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 ExtTrigType: 1;        /*## attribute ExtTrigType */
   /**
	* BitsName: chirp_trigger_mode
	* Description: 1?b1 : 
	* ext. trigger mode : Chirp_start_trigger is coming from another Dolphin  or from an interfacing MCU. Please look at ext_trig_type for more details on use.
	* 
	* 1?b0: 
	* SPI trigger mode: In this mode the timing engine can be triggered through a SPI write. Please note that when configured in SPI trigger node, the chirp timing engine can also generate a chirp_start signal which can be routed to an external pin. This can be used either to trigger other Dolphin IC?s   on same PCB or can be used by MCU for timing engine status (busy) monitoring.
	* 
	* In this mode the following delay shall be considered ( 56 SPI clock  +  four 40 MHz clock cycle +- one MHz clock uncertainty)
	* 
	* 
	* Note:  if ext trigger mode is selected, then, chirp_start_pad need to be configured to I/P mode  in CC module  to get the signal into   Dolphin (central_control (mod addr 0x00) . chirp_start_pad_control( reg_addr 0x004)
	*/
    uint32 ChirpTriggerMode: 1;        /*## attribute ChirpTriggerMode */
}Nxp_Tef810x_Mod04_ChirpTriggerModeControlBits_t;
    /**
* Nxp_Tef810x_Mod04_JumpbackPeriodControlBits_t
* RegisterName: jumpback_period_control
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: jump_back_time
	* Description: At the end of active ADC sample acquisition, a small time (typically 400 ns)  can be considered before resetting the chirp.  
	* Only for flexibility and fine tuning . 
	* Allowed values: 0x01 to 0xFE
	* 
	* In most use cases, no harm in going with the default values. 
	* 
	* The  value of this register need to be carefully considered for progressive chirp modes  ( see sweep control  regsiters.. sweep_control(mod addr 0x05 ) chirpmode(reg addr 0x60))
	*/
    uint32 JumpBackTime: 8;        /*## attribute JumpBackTime */
}Nxp_Tef810x_Mod04_JumpbackPeriodControlBits_t;
    /**
* Nxp_Tef810x_Mod04_DcPowerOnDelayControlBits_t
* RegisterName: dc_power_on_delay_control
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00FF4E20
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: safety_monitor_delay
	* Description: Safety monitoring has to be enabled before capturing valid ADC data samples. .However if   it is enabled, much before  sampling adc_data,  there is a chance that some of the sensors may throw an error ( typically example is the chirp vco level).  A timer is  provided to fine tune the activation of safety monitoring based on application profile and validation results.
	* The timer starts along with the settle timer. It is possible to position the safety monitoring start anywhere within settle timer.
	* Allowed values : 0x001 to 0xFFE
	* Useful values : Less than or equal to Settle time.
	* If a value more than settle time is programmed, then  on expiry of settle timer,  safety monitoring will be initiated. 
	* 
	* In an application context, this register to be programmed with maximum value. With this max value programmed, irrespective of the profiles used with different settle timer value, the safety monitoring always active with actual ADC acquisition window.
	*/
    uint32 SafetyMonitorDelay: 12;        /*## attribute SafetyMonitorDelay */
   /**
	* BitsName: dc_poweron_delay
	* Description: In normal chirp mode, once a chirp trigger is received,    the DC power to TX, RX and chirp analog ckt is enabled before initiating the first chirp (controlled by dc_power_on_delay). In this case  a  waiting is required before starting actual chirp ( stabilization time for the analog ckt, and minimum value is 10 us)   
	* 
	* In power save mode  this timer is not used, but  the  value is considered within the e Dwell time. This mean in power save mode the Dwell time has to be minimum 10 us.
	* 
	* 
	* Allowed values: minimum value  to 0xFFFE
	* Minimum value : 10 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case)
	* 
	* 
	* 
	* 
	* Normal mode = 10 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case) ( max time coming from chirp module)
	* power save mode =  50 us + tx_group_delay_from_chirp_start + tx_rx_dc_power_on_delay_fine_control (worst case) 
	* 
	* Normal chirp mode :  All modules are always powerd on  barring TX and RX units.  RX and RX units  are powerd on by timing engine at chirp sequence level. Once powered on  the modules reamin powered on tilll end  of chirp sequence
	* 
	* Extended normal  mode : This is an extension of normal chirp mode, where in   teh TX and RX unit power is controlled at individual  chirp level
	* 
	* Power save mode : The following modules (under software control)  are powerd off outside chirp sequence active  ( TX,RX, ADC, LO, Chirp analog)
	*/
    uint32 DcPoweronDelay: 16;        /*## attribute DcPoweronDelay */
}Nxp_Tef810x_Mod04_DcPowerOnDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ForceDcPoweronControlBits_t
* RegisterName: force_dc_poweron_control
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
	* BitsName: force_dc_poweron
	* Description: 1'b1 : All units (TX and RX) are always on
	* 1'b0: normal mode of operation
	* 
	* Set this bit to always '0' in an application context
	*/
    uint32 ForceDcPoweron: 1;        /*## attribute ForceDcPoweron */
}Nxp_Tef810x_Mod04_ForceDcPoweronControlBits_t;
    /**
* Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlBits_t
* RegisterName: tx_dc_power_on_group_delay_control
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: tx_group_delay_from_chirp_start
	* Description: Fine control on TX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of Transmitter group( All TX together) can be controlled  from the chirp_start trigger. The value has to be less than or equal to the  dc_power_on delay
	* Allowed values: 0x0001 to less than dc_power_delay programmed
	* Minimum value : 0x0001
	* 
	* Note:  Upon expiry of this programmed delay value, a timing reference point is generated for the entire TX units as a group.  From this point a staggered delay timer is started to control the DC power on point of individual transmit units
	* 
	* For practical application  use a value 0x01
	*/
    uint32 TxGroupDelayFromChirpStart: 16;        /*## attribute TxGroupDelayFromChirpStart */
}Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlBits_t
* RegisterName: rx_dc_power_on_group_delay_control
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: rx_group_delay_from_chirp_start
	* Description: Fine control on RX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of receiver  group( All RX together) can be controlled  from the chirp_start trigger. The value has to be less than or equal to the  dc_power_on delay.
	* Allowed values: 0x0001 to less than dc_power_delay programmed
	* Minimum value : 0x0001
	* 
	* Note:  Upon expiry of this programmed delay value, a timing reference point is generated for the entire RX units as a group.  From this point a staggered delay timer is started to control the DC power on point of individual receive  units
	* 
	* For practical application  use   a value 1us
	*/
    uint32 RxGroupDelayFromChirpStart: 16;        /*## attribute RxGroupDelayFromChirpStart */
}Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ChirpDynamicPowerControlBits_t
* RegisterName: chirp_dynamic_power_control
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00010200
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: chirp_fast_switch_enable
	* Description: Enable bit for chirp fast switch for charging
	* 0: Fast switch is not used
	* 1: Fast switching is enabled
	*/
    uint32 ChirpFastSwitchEnable: 1;        /*## attribute ChirpFastSwitchEnable */
   /**
	* BitsName: chirp_fast_switch_delay
	* Description: Controls the duration of fast switch.  Typical value is around 6 us. 
	* A programmable time option is provided so that based on validation, actual value can be programmed (flexibility)
	* 
	* Chirp fast switch delay timer used during dynamic power down scenario. The timer is triggered as soon as the chirp_start is triggered and stays for the delay timer and then DE asserted based on which chirp analog is powered up
	* Use model: The value to be programmed shall be  used based on validation results.
	*/
    uint32 ChirpFastSwitchDelay: 16;        /*## attribute ChirpFastSwitchDelay */
}Nxp_Tef810x_Mod04_ChirpDynamicPowerControlBits_t;
    /**
* Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlBits_t
* RegisterName: tx_rx_dc_power_on_delay_fine_control
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0xFF7F3F00
*/
typedef struct  {
   /**
	* BitsName: tx_rx_dc_power_on_delay_fine_control
	* Description: The delay to enable the TX and ax in staggered way to control the power fluctuations.
	* The timer starts  on expiry of respective _group_delay_timer. 
	* On expiry of this timer, individual TX & RX units are powered on. 
	* 
	* For example TX1, RX1 is controlled by 8 LSB  bits of the register, down counted starting at respective group_delay_timer expiry till the count reaches '0'. Each count step is equal to 25 ns which is one cycle of xtal clock
	* 
	* staggered_en_cotrol_global[7:0]: The delay to enable TX1, RX1
	* staggered_en_cotrol_global[15:8]: The delay to enable TX2, RX2
	* staggered_en_cotrol_global[23:16]: The delay to enable TX3, RX3
	* staggered_en_cotrol_global[31:24]: The delay to enable RX4
	* 
	* 
	* For application the following values are recommended :  (example).. TX group delay = 0 , RX group delay = 1 us.
	* 
	* TX1,RX1 : 0x00  ( TX1 switched on at 0 us and RX1 at 1 us)
	* TX2,RX2 : 0x1F  ( TX2 switched on at 0.8 us and RX2 at 1.8 us)
	* TX3,RX3 : 0x3F  ( TX3 switched on at 1.6 us and RX3 at 2.6 us)
	* TX4,RX4 : 0x7F  ( TX4 switched on at 3.2 us and RX4 at 4.2 us)
	*/
    uint32 TxRxDcPowerOnDelayFineControl: 32;        /*## attribute TxRxDcPowerOnDelayFineControl */
}Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ChirpGlobalControlBits_t
* RegisterName: chirp_global_control
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00010000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: profile_stay_count_val
	* Description: Four profile registers are provided for controlling the chirp parameters. The profile registers can be configured in different sequence (see chirp_profile_select).  By using this register, a given profile is repeated  a number of times (based on value programmed) before moving to the next profile  in the sequence.
	* 0x01 : Profile repeated one time
	* 0x02 : Profile repeated two  time
	* ............
	*/
    uint32 ProfileStayCountVal: 7;        /*## attribute ProfileStayCountVal */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: enable_profile_reset
	* Description: After an acquisition cycle, theer could be two scenarios
	* 1. Always start with  the first profile for a neq acquisition 
	* 2. Start from  the last active profile
	* Thsi register can be used to  select between this option.
	* 
	* 
	* 0x0: : Continue from where  left 
	* 0x1: For a new sequence always start afresh (Reset the profile at start of the new chirp sequence)
	* 
	* Note: This register must be set to '0' when  "chirp_profile_select" is set for individual profiles ( values less than or equal to 3'b011)
	*/
    uint32 EnableProfileReset: 1;        /*## attribute EnableProfileReset */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 5;        /*## attribute Reserved4 */
   /**
	* BitsName: chirp_profile_select
	* Description: Control  the  profiles to be used  within a given chirp sequence  
	* 3?b000 : All chirp in a sequence based on profile  ?0?
	* 3?b001 :Profile 1
	* 3?b010 : Profile 2
	* 3'b011: profile 3
	* 3'b100: profile 0 -1 -0-1
	* 3'b101: profile 0-1-2-0-1-2
	* 3'b110: profile 0-1-2-3-0-1-2-3
	* 
	* Others : not used
	*/
    uint32 ChirpProfileSelect: 3;        /*## attribute ChirpProfileSelect */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 6;        /*## attribute Reserved5 */
   /**
	* BitsName: chirp_enable
	* Description: Usemodel 1:
	* Enable chirp. This bit need to  be set (global enable for chirp digital). 
	* 0: The chirp engine is inactive and all circuits are clock gated
	* 1: Chirp engine is enabled and ready to take  a start chirp commands. This bit is set to '1' in normal chirping mode
	* 
	* Usemodel 2:
	* This bit can also be used for loading the profile registers (of timing engine, sweep control, chirp_afc) without actually triggering the chirp i.e without chirp_start being set. This bit requires pattern of 0-1-0 (toggle) to load the profile registers after the selecting the right profile (chirp_profile_select bits restricted to 3?b000, 3?b001, 3?b010, 3?b011 in this use mode). One example of this use mode, is continuous wave (CW) triggering with fixed frequency
	*/
    uint32 ChirpEnable: 1;        /*## attribute ChirpEnable */
   /**
	* BitsName: chirp_start
	* Description: SPI trigger to chirp start. Once written, this register on read indicates the busy status of the timing engine
	* 0: Timing engine free
	* 1: Timing engine busy
	*/
    uint32 ChirpStart: 1;        /*## attribute ChirpStart */
}Nxp_Tef810x_Mod04_ChirpGlobalControlBits_t;
    /**
* Nxp_Tef810x_Mod04_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00042201
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
   /**
	* BitsName: major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: minor_revision
	* Description: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets Reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod04_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod04_TimingControl1ProfileUnion_t
* Nxp_Tef810x_Mod04_TimingControl1ProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_TimingControl1ProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_TimingControl1ProfileUnion_t;
/**
* Nxp_Tef810x_Mod04_TimingControl2ProfileUnion_t
* Nxp_Tef810x_Mod04_TimingControl2ProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_TimingControl2ProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_TimingControl2ProfileUnion_t;
/**
* Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t
* Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_TimingControl3ProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t;
/**
* Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t
* Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ChirpSequenceControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlUnion_t
* Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t
* Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ChirpTriggerModeControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t;
/**
* Nxp_Tef810x_Mod04_JumpbackPeriodControlUnion_t
* Nxp_Tef810x_Mod04_JumpbackPeriodControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_JumpbackPeriodControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_JumpbackPeriodControlUnion_t;
/**
* Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t
* Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_DcPowerOnDelayControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ForceDcPoweronControlUnion_t
* Nxp_Tef810x_Mod04_ForceDcPoweronControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ForceDcPoweronControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ForceDcPoweronControlUnion_t;
/**
* Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlUnion_t
* Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlUnion_t;
/**
* Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlUnion_t
* Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ChirpDynamicPowerControlUnion_t
* Nxp_Tef810x_Mod04_ChirpDynamicPowerControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ChirpDynamicPowerControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ChirpDynamicPowerControlUnion_t;
/**
* Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlUnion_t
* Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t
* Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ChirpGlobalControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t;
/**
* Nxp_Tef810x_Mod04_ModuleidUnion_t
* Nxp_Tef810x_Mod04_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod04_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod04_ModuleidUnion_t;
	/**
* Nxp_Tef810x_Mod04_TimingEngineprofile_t
* Nxp_Tef810x_Mod04_TimingEngineprofile_t
* Structure for module specific profile management
*/
typedef struct  {
  /**
    * RegisterName: Timing_control_1_profile0
    * AddressOffset: 0x000
    * ResetValue: 0x4000400A
    * Description: A number of important informations are combined into a single register, so that the interfacing MCU can do an update with a single write  (useful for dynamic profile updates)
    */
    Nxp_Tef810x_Mod04_TimingControl1ProfileUnion_t TimingControl1Profile0_ust;        /*## attribute TimingControl1Profile0_ust */
  /**
    * RegisterName: Timing_control_2_profile0
    * AddressOffset: 0x004
    * ResetValue: 0x00A00080
    * Description: This register contain information about  acquistion sampling   timing   ( settle time, number  of ADC samples  plus the ADC decimation factor)
    */
    Nxp_Tef810x_Mod04_TimingControl2ProfileUnion_t TimingControl2Profile0_ust;        /*## attribute TimingControl2Profile0_ust */
  /**
    * RegisterName: Timing_control_3_profile0
    * AddressOffset: 0x008
    * ResetValue: 0x00000200
    * Description: Chirp level enable or disable of individual transmit or receive function.  If disabled power to the corresponding TX or RX is controlled at profile level. 
	* 
	*  A use case scenario. 
	* 1. Application  use profile 0-1-2 in a round robin manner
	* 2. TX1 is enabled  in profile 0 and profile 2 only
	* 3. In thsi case for first and third chirp TX1 is enabled, and  chirp '2' TX1 is disabled.
	* Please note that in such scenario, the Tdwell for chirp '3' to be set to minimum 10 us to allow enough settle time fo rthe TX to stabilize
    */
    Nxp_Tef810x_Mod04_TimingControl3ProfileUnion_t TimingControl3Profile0_ust;        /*## attribute TimingControl3Profile0_ust */
}Nxp_Tef810x_Mod04_TimingEngineProfile_t;
/**
 * Nxp_Tef810x_Mod04_TimingEngineRegister_t
 * Nxp_Tef810x_Mod04_TimingEngineRegister_t
 * structure used as shadow register map
 */
typedef struct  {
	/**
    * RegisterName: Nxp_Tef810x_Mod04_TimingEngineProfile_t;
    *AddressOffset: 0x000 - 0x02C
    * Description: Structure for module specific profile management.
                       
    */
    Nxp_Tef810x_Mod04_TimingEngineProfile_t TimingEngineProfile_ast[0x04];        /*## attribute TimingEngineProfile_ast */
  /**
    * RegisterName: Chirp_sequence_control
    * AddressOffset: 0x030
    * ResetValue: 0x00010020
    * Description: Control the no of chirp  sequences  and  number of chirp within  a sequence  .
    */
    Nxp_Tef810x_Mod04_ChirpSequenceControlUnion_t ChirpSequenceControl_ust;        /*## attribute ChirpSequenceControl_ust */
  /**
    * RegisterName: chirp_sequence_interval_control
    * AddressOffset: 0x034
    * ResetValue: 0xFFFFFFFF
    * Description: A timer to control the gap between chirp sequence (system cycle).
	* Controls the gap between two chirp sequence ( data acquisition)  if the no_of_sequence is more than one
    */
    Nxp_Tef810x_Mod04_ChirpSequenceIntervalControlUnion_t ChirpSequenceIntervalControl_ust;        /*## attribute ChirpSequenceIntervalControl_ust */
  /**
    * RegisterName: Chirp_trigger_mode_control
    * AddressOffset: 0x038
    * ResetValue: 0x00000100
    * Description: Control register for different chipr mode and  interfacing options.
    */
    Nxp_Tef810x_Mod04_ChirpTriggerModeControlUnion_t ChirpTriggerModeControl_ust;        /*## attribute ChirpTriggerModeControl_ust */
  /**
    * RegisterName: jumpback_period_control
    * AddressOffset: 0x03C
    * ResetValue: 0x00000004
    * Description: At the end of active ADC sample acquisition, a small time (typically 400 ns)  can be considered before resetting the chirp.   The purpose of this register is to avoid any un necessary  disturbance to the actual data acquisition due to  sudden chnages in the chirp ramp  ( fast chirp reset)
    */
    Nxp_Tef810x_Mod04_JumpbackPeriodControlUnion_t JumpbackPeriodControl_ust;        /*## attribute JumpbackPeriodControl_ust */
  /**
    * RegisterName: dc_power_on_delay_control
    * AddressOffset: 0x040
    * ResetValue: 0x00FF4E20
    * Description: Two registers are combined here. DC power on delay and safety monitor activation delay
    */
    Nxp_Tef810x_Mod04_DcPowerOnDelayControlUnion_t DcPowerOnDelayControl_ust;        /*## attribute DcPowerOnDelayControl_ust */
  /**
    * RegisterName: force_dc_poweron_control
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: Manual override for DC power control to TX and RX.   Normally [ower to  TX and RX is controlled by timing engine. Based on chirp sequence active.  By using this register  an over ride is possible . . Thia register is only for debugging or validation reason
    */
    Nxp_Tef810x_Mod04_ForceDcPoweronControlUnion_t ForceDcPoweronControl_ust;        /*## attribute ForceDcPoweronControl_ust */
  /**
    * RegisterName: tx_dc_power_on_group_delay_control
    * AddressOffset: 0x048
    * ResetValue: 0x00000000
    * Description: A provision provided to  control the transmitter units ( all TX )  power on point from teh chirp_start trigger point.
	* 
	* Fine control on TX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of Transmitter group( All TX together) can be controlled  from the chirp_start trigger. 
	* 
	* The value has to be less than or equal to the dc_power_on delay
    */
    Nxp_Tef810x_Mod04_TxDcPowerOnGroupDelayControlUnion_t TxDcPowerOnGroupDelayControl_ust;        /*## attribute TxDcPowerOnGroupDelayControl_ust */
  /**
    * RegisterName: rx_dc_power_on_group_delay_control
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: A provision provided to  control the transmitter units ( all RX )  power on point from teh chirp_start trigger point.
	* 
	* Fine control on RX DC power on   w.r.t chirp_start trigger.   Using this  delay,  the DC power on point  of  receiver  group( All RX together) can be controlled  from the chirp_start trigger. 
	* 
	* The value has to be less than or equal to the dc_power_on delay
    */
    Nxp_Tef810x_Mod04_RxDcPowerOnGroupDelayControlUnion_t RxDcPowerOnGroupDelayControl_ust;        /*## attribute RxDcPowerOnGroupDelayControl_ust */
  /**
    * RegisterName: chirp_dynamic_power_control
    * AddressOffset: 0x050
    * ResetValue: 0x00010200
    * Description: In power save mode, it is possible to  enable/disable DC power to chirp analog part.  When power is disabled,  then a fast charging ckt  shall be used to initialize the chirp ckt  before using  it for chirp. If fast charging Is not used, it may take around 500 us time for the chirp analog ckt to stabilize. With fast charging  it would be less than 5 us.
	* During actual chirping, this switch  shall be in open position, and this is taken care by the chirp digital ckt
    */
    Nxp_Tef810x_Mod04_ChirpDynamicPowerControlUnion_t ChirpDynamicPowerControl_ust;        /*## attribute ChirpDynamicPowerControl_ust */
  /**
    * RegisterName: tx_rx_dc_power_on_delay_fine_control
    * AddressOffset: 0x054
    * ResetValue: 0xFF7F3F00
    * Description: This timer is provide  to provide flexibility in switching on  individual TX & RX unit at different time  from a timing reference point.  This is provided to avoid large current drain from LDO, when individual TX and RX units are powered on simultaneously.
    */
    Nxp_Tef810x_Mod04_TxRxDcPowerOnDelayFineControlUnion_t TxRxDcPowerOnDelayFineControl_ust;        /*## attribute TxRxDcPowerOnDelayFineControl_ust */
  /**
    * RegisterName: chirp_global_control
    * AddressOffset: 0x058
    * ResetValue: 0x00010000
    * Description: Global control register to control chirp parameters
    */
    Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t ChirpGlobalControl_ust;        /*## attribute ChirpGlobalControl_ust */

    uint32 gap01_au32[998];        /* gap 1 in register space */  /**
    * RegisterName: Reserved00
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00042201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod04_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod04_TimingEngineRegister_t;

#endif
