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
* @NXP_TEF810X_SweepControl.h
*/
#ifndef NXP_TEF810X_SWEEPCONTROL_H
#define NXP_TEF810X_SWEEPCONTROL_H
#include "Std_Types.h"

#define SWEEP_CONTROL_MODULE_ADDRESS 0x05
/**
*NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16
* RegisterName: MOD05_N_start_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x6C000000
*/
#define NXP_TEF810X_MOD05_N_START_RF_PROFILE0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16
* RegisterName: MOD05_DN_chirp_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x000025ED
*/
#define NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE0_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE0_U16
* RegisterName: MOD05_N_step_chirp_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000960
*/
#define NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE0_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16
* RegisterName: MOD05_DN_reset_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x04017B42
*/
#define NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE0_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE0_U16
* RegisterName: MOD05_N_step_reset_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x000000F0
*/
#define NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE0_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE0_U16
* RegisterName: MOD05_Div_update_rf_profile0
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00040005
*/
#define NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE0_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16
* RegisterName: MOD05_N_start_rf_profile1
* AccessMode: WRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x6C000000
*/
#define NXP_TEF810X_MOD05_N_START_RF_PROFILE1_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE1_U16
* RegisterName: MOD05_DN_chirp_rf_profile1
* AccessMode: WRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x000025ED
*/
#define NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE1_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE1_U16
* RegisterName: MOD05_N_step_chirp_rf_profile1
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00000960
*/
#define NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE1_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE1_U16
* RegisterName: MOD05_DN_reset_rf_profile1
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x04017B42
*/
#define NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE1_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE1_U16
* RegisterName: MOD05_N_step_reset_rf_profile1
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x000000F0
*/
#define NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE1_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE1_U16
* RegisterName: MOD05_Div_update_rf_profile1
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00040005
*/
#define NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE1_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD05_N_START_RF_PROFILE2_U16
* RegisterName: MOD05_N_start_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x6C000000
*/
#define NXP_TEF810X_MOD05_N_START_RF_PROFILE2_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE2_U16
* RegisterName: MOD05_DN_chirp_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x000025ED
*/
#define NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE2_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE2_U16
* RegisterName: MOD05_N_step_chirp_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00000960
*/
#define NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE2_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE2_U16
* RegisterName: MOD05_DN_reset_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x04017B42
*/
#define NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE2_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE2_U16
* RegisterName: MOD05_N_step_reset_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x000000F0
*/
#define NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE2_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE2_U16
* RegisterName: MOD05_Div_update_rf_profile2
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00040005
*/
#define NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE2_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD05_N_START_RF_PROFILE3_U16
* RegisterName: MOD05_N_start_rf_profile3
* AccessMode: WRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x6C000000
*/
#define NXP_TEF810X_MOD05_N_START_RF_PROFILE3_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE3_U16
* RegisterName: MOD05_DN_chirp_rf_profile3
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x000025ED
*/
#define NXP_TEF810X_MOD05_DN_CHIRP_RF_PROFILE3_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE3_U16
* RegisterName: MOD05_N_step_chirp_rf_profile3
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000960
*/
#define NXP_TEF810X_MOD05_N_STEP_CHIRP_RF_PROFILE3_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE3_U16
* RegisterName: MOD05_DN_reset_rf_profile3
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x04017B42
*/
#define NXP_TEF810X_MOD05_DN_RESET_RF_PROFILE3_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE3_U16
* RegisterName: MOD05_N_step_reset_rf_profile3
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x000000F0
*/
#define NXP_TEF810X_MOD05_N_STEP_RESET_RF_PROFILE3_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE3_U16
* RegisterName: MOD05_Div_update_rf_profile3
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00040005
*/
#define NXP_TEF810X_MOD05_DIV_UPDATE_RF_PROFILE3_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD05_CHIRPMODE_U16
* RegisterName: MOD05_ChirpMode
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD05_CHIRPMODE_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD05_MODULEID_U16
* RegisterName: MOD05_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00051201
*/
#define NXP_TEF810X_MOD05_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod05_N_START_RF_PROFILEBits_t
* RegisterName: N_start_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: NStartFracRF_profile0
	* Description: Fractional part of the chirp start  frequency(data_acquisition).  
	* Default value to get 77.76GHz
	*/
    uint32 NstartfracrfProfile0: 26;        /*## attribute NstartfracrfProfile0 */
   /**
	* BitsName: NStartIntRF_profile0
	* Description: integer part of the RF chirp start frequency (data_acquisition).  Default value to get 77.76GHz
	*/
    uint32 NstartintrfProfile0: 6;        /*## attribute NstartintrfProfile0 */
}Nxp_Tef810x_Mod05_NStartRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DN_CHIRP_RF_PROFILEBits_t
* RegisterName: DN_chirp_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: DNChirpActive_Reg_profile0
	* Description: Incremental value of frequency divider for each frequency step.
	* Bit 26 is for sign
	* bit 26 = 1'b0 : positive chirp
	* bit 26 = 1;b1 : Negative chirp
	*/
    uint32 DnchirpactiveRegProfile0: 27;        /*## attribute DnchirpactiveRegProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod05_DnChirpRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_N_STEP_CHIRP_RF_PROFILEBits_t
* RegisterName: N_step_chirp_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: NStepChirpActive_Reg_profile0
	* Description: Number of steps  to be programmed in data acquisition chirp. 18bits.  Actual no of steps = programmed value +1
	*/
    uint32 NstepchirpactiveRegProfile0: 18;        /*## attribute NstepchirpactiveRegProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 14;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod05_NStepChirpRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DN_RESET_RF_PROFILEBits_t
* RegisterName: DN_reset_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: DNChirpReset_Reg_profile0
	* Description: Incremental value of frequency divider for each frequency step.
	* Bit 26 is for sign
	* bit 26 = 1'b0 : positive chirp
	* bit 26 = 1;b1 : Negative chirp
	*/
    uint32 DnchirpresetRegProfile0: 27;        /*## attribute DnchirpresetRegProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod05_DnResetRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_N_STEP_RESET_RF_PROFILEBits_t
* RegisterName: N_step_reset_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: NStepChirpReset_Reg_profile0
	* Description: Number of steps in chirp reset mode. 18bits.
	* Actual no of steps = programmed value +1
	*/
    uint32 NstepchirpresetRegProfile0: 18;        /*## attribute NstepchirpresetRegProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 14;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod05_NStepResetRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DIV_UPDATE_RF_PROFILEBits_t
* RegisterName: Div_update_rf_profile
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: DivUpdateRF_profile0
	* Description: Divider value for 480MHz input clock, determines increment frequency of frequency ramp. This should be programmed to one value less than the intended value. For example 0 means divide by 1, 1 means divide by 2 etc.  
	* Use model: For practical purpose the  following O/P frequency can be used.
	* 240 MHz, 160,120 MHz, 96, and 80 MHz
	* 
	* Note: Default is 80 MHz . 80MHz is good enough for normal application, no need to change this default value
	*/
    uint32 DivupdaterfProfile0: 4;        /*## attribute DivupdaterfProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: idiv_blk_cnt_profile0
	* Description: In order to make sure that no glitches are visible on the O/P clock, a  clock blocking logic is used.  this bit filed defines the blocking time at 40 MHz rate. 
	*  The output divider clock will stay high during this period while the input clock changes.
	* Use model : Default value is sufficient for  practical purpose.   A programmable option is only for validation purpose.
	*/
    uint32 IdivBlkCntProfile0: 6;        /*## attribute IdivBlkCntProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_deviation_bits_profile0
	* Description: This value is the deviation value used in the frequency counter in afc to measure sweep control clock and compare against the expected value. 
	* Freq_counter_value+freq_deviation_bits_profile0 and Freq_counter_value-freq_deviation_bits_profile0 is compared against the expected value
	*/
    uint32 FreqDeviationBitsProfile0: 4;        /*## attribute FreqDeviationBitsProfile0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: idiv_rst_profile0
	* Description: Active high soft reset for master clk divider
	*/
    uint32 IdivRstProfile0: 1;        /*## attribute IdivRstProfile0 */
}Nxp_Tef810x_Mod05_DivUpdateRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_CHIRPMODEBits_t
* RegisterName: ChirpMode
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: Sweep_control_mode
	* Description: 0: Sweep control will follow timing engine  trigger point for  chirp reset (l). An end of data acquisition ( base don no of ADC samples programmed in timing engine plus jump back time)  will trigger the chirp reset phase
	* 1: Sweep control will follow the sweep counter value  ( once the sweep control reaches the max accumulated value based on no of steps programmed,  chirp reset start immediately).
	*/
    uint32 SweepControlMode: 1;        /*## attribute SweepControlMode */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: donot_load_accumulator_between_chirp
	* Description: 0: Re Load accumulator between chirps with chirp start frequency value  (Nstart*)
	* 1: Do not load accumulator and the chirps are progressive i.e the next chirp will follow from where the previous chirp resetted and accumulator will not load the base frequency ( useful for progressive chirp)
	*/
    uint32 DonotLoadAccumulatorBetweenChirp: 1;        /*## attribute DonotLoadAccumulatorBetweenChirp */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Pll_reset_disable
	* Description: During chirp reset phase, due to the fast slop of the chirp waveform,  an additional ckt may be necessary to get back the VCO  to the desired end frequency value.  A programmable option is provided here
	* 1:  fast discharge is enabled during chipr reset phase
	* 0: Fast  discharge is disabled during chirp reset
	* Default = 1'b0
	* USe model : Recommended to set this bit to '1' when the chirp reset time is ultra short
	*/
    uint32 PllResetDisable: 1;        /*## attribute PllResetDisable */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod05_ChirpmodeBits_t;
    /**
* Nxp_Tef810x_Mod05_MODULEIDBits_t
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
	* Description: Minor revision number i.e. with no software consequences
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
}Nxp_Tef810x_Mod05_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod05_NStartRfProfileBits_t
* RegisterName: N_start_rf_profile
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x6C000000
*/
typedef struct  {
   /**
	* BitsName: NStartIntRF_profile0
	* Description: integer part of the RF chirp start frequency (data_acquisition).  Default value to get 77.76GHz
	*/
    uint32 NstartintrfProfile0: 6;        /*## attribute NstartintrfProfile0 */
   /**
	* BitsName: NStartFracRF_profile0
	* Description: Fractional part of the chirp start  frequency(data_acquisition).  
	* Default value to get 77.76GHz
	*/
    uint32 NstartfracrfProfile0: 26;        /*## attribute NstartfracrfProfile0 */
}Nxp_Tef810x_Mod05_NStartRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DnChirpRfProfileBits_t
* RegisterName: DN_chirp_rf_profile
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x000025ED
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: DNChirpActive_Reg_profile0
	* Description: Incremental value of frequency divider for each frequency step.
	* Bit 26 is for sign
	* bit 26 = 1'b0 : positive chirp
	* bit 26 = 1;b1 : Negative chirp
	*/
    uint32 DnchirpactiveRegProfile0: 27;        /*## attribute DnchirpactiveRegProfile0 */
}Nxp_Tef810x_Mod05_DnChirpRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_NStepChirpRfProfileBits_t
* RegisterName: N_step_chirp_rf_profile
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000960
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 14;        /*## attribute Reserved0 */
   /**
	* BitsName: NStepChirpActive_Reg_profile0
	* Description: Number of steps  to be programmed in data acquisition chirp. 18bits.  Actual no of steps = programmed value +1
	*/
    uint32 NstepchirpactiveRegProfile0: 18;        /*## attribute NstepchirpactiveRegProfile0 */
}Nxp_Tef810x_Mod05_NStepChirpRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DnResetRfProfileBits_t
* RegisterName: DN_reset_rf_profile
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x04017B42
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: DNChirpReset_Reg_profile0
	* Description: Incremental value of frequency divider for each frequency step.
	* Bit 26 is for sign
	* bit 26 = 1'b0 : positive chirp
	* bit 26 = 1;b1 : Negative chirp
	*/
    uint32 DnchirpresetRegProfile0: 27;        /*## attribute DnchirpresetRegProfile0 */
}Nxp_Tef810x_Mod05_DnResetRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_NStepResetRfProfileBits_t
* RegisterName: N_step_reset_rf_profile
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x000000F0
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 14;        /*## attribute Reserved0 */
   /**
	* BitsName: NStepChirpReset_Reg_profile0
	* Description: Number of steps in chirp reset mode. 18bits.
	* Actual no of steps = programmed value +1
	*/
    uint32 NstepchirpresetRegProfile0: 18;        /*## attribute NstepchirpresetRegProfile0 */
}Nxp_Tef810x_Mod05_NStepResetRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_DivUpdateRfProfileBits_t
* RegisterName: Div_update_rf_profile
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00040005
*/
typedef struct  {
   /**
	* BitsName: idiv_rst_profile0
	* Description: Active high soft reset for master clk divider
	*/
    uint32 IdivRstProfile0: 1;        /*## attribute IdivRstProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: freq_deviation_bits_profile0
	* Description: This value is the deviation value used in the frequency counter in afc to measure sweep control clock and compare against the expected value. 
	* Freq_counter_value+freq_deviation_bits_profile0 and Freq_counter_value-freq_deviation_bits_profile0 is compared against the expected value
	*/
    uint32 FreqDeviationBitsProfile0: 4;        /*## attribute FreqDeviationBitsProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: idiv_blk_cnt_profile0
	* Description: In order to make sure that no glitches are visible on the O/P clock, a  clock blocking logic is used.  this bit filed defines the blocking time at 40 MHz rate. 
	*  The output divider clock will stay high during this period while the input clock changes.
	* Use model : Default value is sufficient for  practical purpose.   A programmable option is only for validation purpose.
	*/
    uint32 IdivBlkCntProfile0: 6;        /*## attribute IdivBlkCntProfile0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 12;        /*## attribute Reserved2 */
   /**
	* BitsName: DivUpdateRF_profile0
	* Description: Divider value for 480MHz input clock, determines increment frequency of frequency ramp. This should be programmed to one value less than the intended value. For example 0 means divide by 1, 1 means divide by 2 etc.  
	* Use model: For practical purpose the  following O/P frequency can be used.
	* 240 MHz, 160,120 MHz, 96, and 80 MHz
	* 
	* Note: Default is 80 MHz . 80MHz is good enough for normal application, no need to change this default value
	*/
    uint32 DivupdaterfProfile0: 4;        /*## attribute DivupdaterfProfile0 */
}Nxp_Tef810x_Mod05_DivUpdateRfProfileBits_t;
    /**
* Nxp_Tef810x_Mod05_ChirpmodeBits_t
* RegisterName: ChirpMode
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: Pll_reset_disable
	* Description: During chirp reset phase, due to the fast slop of the chirp waveform,  an additional ckt may be necessary to get back the VCO  to the desired end frequency value.  A programmable option is provided here
	* 1:  fast discharge is enabled during chipr reset phase
	* 0: Fast  discharge is disabled during chirp reset
	* Default = 1'b0
	* USe model : Recommended to set this bit to '1' when the chirp reset time is ultra short
	*/
    uint32 PllResetDisable: 1;        /*## attribute PllResetDisable */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: donot_load_accumulator_between_chirp
	* Description: 0: Re Load accumulator between chirps with chirp start frequency value  (Nstart*)
	* 1: Do not load accumulator and the chirps are progressive i.e the next chirp will follow from where the previous chirp resetted and accumulator will not load the base frequency ( useful for progressive chirp)
	*/
    uint32 DonotLoadAccumulatorBetweenChirp: 1;        /*## attribute DonotLoadAccumulatorBetweenChirp */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Sweep_control_mode
	* Description: 0: Sweep control will follow timing engine  trigger point for  chirp reset (l). An end of data acquisition ( base don no of ADC samples programmed in timing engine plus jump back time)  will trigger the chirp reset phase
	* 1: Sweep control will follow the sweep counter value  ( once the sweep control reaches the max accumulated value based on no of steps programmed,  chirp reset start immediately).
	*/
    uint32 SweepControlMode: 1;        /*## attribute SweepControlMode */
}Nxp_Tef810x_Mod05_ChirpmodeBits_t;
    /**
* Nxp_Tef810x_Mod05_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00051201
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
	* Description: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod05_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod05_NStartRfProfileUnion_t
* Nxp_Tef810x_Mod05_NStartRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_NStartRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_NStartRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t
* Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_DnChirpRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_NStepChirpRfProfileUnion_t
* Nxp_Tef810x_Mod05_NStepChirpRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_NStepChirpRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_NStepChirpRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t
* Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_DnResetRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_NStepResetRfProfileUnion_t
* Nxp_Tef810x_Mod05_NStepResetRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_NStepResetRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_NStepResetRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_DivUpdateRfProfileUnion_t
* Nxp_Tef810x_Mod05_DivUpdateRfProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_DivUpdateRfProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_DivUpdateRfProfileUnion_t;
/**
* Nxp_Tef810x_Mod05_ChirpmodeUnion_t
* Nxp_Tef810x_Mod05_ChirpmodeUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_ChirpmodeBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_ChirpmodeUnion_t;
/**
* Nxp_Tef810x_Mod05_ModuleidUnion_t
* Nxp_Tef810x_Mod05_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod05_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod05_ModuleidUnion_t;
	/**
* Nxp_Tef810x_Mod05_SweepControlprofile_t
* Nxp_Tef810x_Mod05_SweepControlprofile_t
* Structure for module specific profile management
*/
typedef struct  {
  /**
    * RegisterName: N_start_rf_profile0
    * AddressOffset: 0x000
    * ResetValue: 0x6C000000
    * Description: start-value for the fractional PLL division ratio corresponding to the desired chirp start frequency (data acquisition)
    */
    Nxp_Tef810x_Mod05_NStartRfProfileUnion_t NStartRfProfile0_ust;        /*## attribute NStartRfProfile0_ust */
  /**
    * RegisterName: DN_chirp_rf_profile0
    * AddressOffset: 0x004
    * ResetValue: 0x000025ED
    * Description: The step size of the incremental frequency (data_acquisition))
    */
    Nxp_Tef810x_Mod05_DnChirpRfProfileUnion_t DnChirpRfProfile0_ust;        /*## attribute DnChirpRfProfile0_ust */
  /**
    * RegisterName: N_step_chirp_rf_profile0
    * AddressOffset: 0x008
    * ResetValue: 0x00000960
    * Description: The number of incremental frequency steps which controls the end  frequency of the chirp during the data acquisition
    */
    Nxp_Tef810x_Mod05_NStepChirpRfProfileUnion_t NStepChirpRfProfile0_ust;        /*## attribute NStepChirpRfProfile0_ust */
  /**
    * RegisterName: DN_reset_rf_profile0
    * AddressOffset: 0x00C
    * ResetValue: 0x04017B42
    * Description: The size of the incremental frequency step in chirp reset mode
    */
    Nxp_Tef810x_Mod05_DnResetRfProfileUnion_t DnResetRfProfile0_ust;        /*## attribute DnResetRfProfile0_ust */
  /**
    * RegisterName: N_step_reset_rf_profile0
    * AddressOffset: 0x010
    * ResetValue: 0x000000F0
    * Description: The number of incremental frequencies steps which controls the stop frequency of the chirp during the chirp reset mode
    */
    Nxp_Tef810x_Mod05_NStepResetRfProfileUnion_t NStepResetRfProfile0_ust;        /*## attribute NStepResetRfProfile0_ust */
  /**
    * RegisterName: Div_update_rf_profile0
    * AddressOffset: 0x014
    * ResetValue: 0x00040005
    * Description: Settings for the update rate of the incremental steps in chirp reset mode. Can be used for controlling the chirp slop. Realized through a clock divider.  
	* 
	* Apart from this a part of a freq compare logic also mapped to this address space for functional safety
    */
    Nxp_Tef810x_Mod05_DivUpdateRfProfileUnion_t DivUpdateRfProfile0_ust;        /*## attribute DivUpdateRfProfile0_ust */
}Nxp_Tef810x_Mod05_SweepControlProfile_t;
/**
 * Nxp_Tef810x_Mod05_SweepControlRegister_t
 * Nxp_Tef810x_Mod05_SweepControlRegister_t
 * structure used as shadow register map
 */
typedef struct  {
	/**
    * RegisterName: Nxp_Tef810x_Mod05_SweepControlProfile_t;
    *AddressOffset: 0x000 - 0x05C
    * Description: Structure for module specific profile management.
                       
    */
    Nxp_Tef810x_Mod05_SweepControlProfile_t SweepControlProfile_ast[0x04];        /*## attribute SweepControlProfile_ast */
  /**
    * RegisterName: ChirpMode
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: Sweep control mode setttings
    */
    Nxp_Tef810x_Mod05_ChirpmodeUnion_t Chirpmode_ust;        /*## attribute Chirpmode_ust */

    uint32 gap01_au32[7];        /* gap 1 in register space */  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;

    uint32 gap02_au32[988];        /* gap 2 in register space */  /**
    * RegisterName: Reserved01
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;

    uint32 gap03_au32[1];        /* gap 3 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00051201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod05_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod05_SweepControlRegister_t;

#endif
