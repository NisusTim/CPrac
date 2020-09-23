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
* @NXP_TEF810X_GlobalLdo.h
*/
#ifndef NXP_TEF810X_GLOBALLDO_H
#define NXP_TEF810X_GLOBALLDO_H
#include "Std_Types.h"

#define GLOBAL_LDO_MODULE_ADDRESS 0x15
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_TOP_CONTROL_U16
* RegisterName: MOD15_gldo1v1_sns_low_top_control
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_TOP_CONTROL_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16
* RegisterName: MOD15_gldo1v1_sns_low_config
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CONFIG_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_TOP_CONTROL_U16
* RegisterName: MOD15_gldo1v1_sns_high_top_control
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_TOP_CONTROL_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16
* RegisterName: MOD15_gldo1v1_sns_high_config
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000011
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CONFIG_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_TOP_CONTROL_U16
* RegisterName: MOD15_gldo1v8_sns_low_top_control
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_TOP_CONTROL_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16
* RegisterName: MOD15_gldo1v8_sns_low_config
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00000003
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CONFIG_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_TOP_CONTROL_U16
* RegisterName: MOD15_gldo1v8_sns_high_top_control
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_TOP_CONTROL_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16
* RegisterName: MOD15_gldo1v8_sns_high_config
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00000013
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CONFIG_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_U16
* RegisterName: MOD15_gldo_bg_ref_config
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00001F00
*/
#define NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD15_GLDO_BG_REF_STATUS_U16
* RegisterName: MOD15_gldo_bg_ref_status
* AccessMode: READ
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000011
*/
#define NXP_TEF810X_MOD15_GLDO_BG_REF_STATUS_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_EXT_U16
* RegisterName: MOD15_gldo_bg_ref_config_ext
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x0000043F
*/
#define NXP_TEF810X_MOD15_GLDO_BG_REF_CONFIG_EXT_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD15_TEST_ERROR_FLAG_STATUS_U16
* RegisterName: MOD15_test_error_flag_status
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD15_TEST_ERROR_FLAG_STATUS_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16
* RegisterName: MOD15_gldo1v1_sns_low_cal_reg
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x0000003F
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_LOW_CAL_REG_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16
* RegisterName: MOD15_gldo1v1_sns_high_cal_reg
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x0000003F
*/
#define NXP_TEF810X_MOD15_GLDO1V1_SNS_HIGH_CAL_REG_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16
* RegisterName: MOD15_gldo1v8_sns_low_cal_reg
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x0000003F
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_LOW_CAL_REG_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16
* RegisterName: MOD15_gldo1v8_sns_high_cal_reg
* AccessMode: READWRITE
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x0000003F
*/
#define NXP_TEF810X_MOD15_GLDO1V8_SNS_HIGH_CAL_REG_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD15_MODULEID_U16
* RegisterName: MOD15_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00153301
*/
#define NXP_TEF810X_MOD15_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_LOW_TOP_CONTROLBits_t
* RegisterName: gldo1v1_sns_low_top_control
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: sns_1v1_low_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied
	*/
    uint32 Sns1V1LowReset: 1;        /*## attribute Sns1V1LowReset */
   /**
	* BitsName: sns_1v1_low_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	*/
    uint32 Sns1V1LowPd: 1;        /*## attribute Sns1V1LowPd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_LOW_CONFIGBits_t
* RegisterName: gldo1v1_sns_low_config
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: sns_1v1_low_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "001" in an application context. Other values not to be used
	*/
    uint32 Sns1V1LowVmonSel: 3;        /*## attribute Sns1V1LowVmonSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v1_low_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V1LowPeakDipSel: 1;        /*## attribute Sns1V1LowPeakDipSel */
   /**
	* BitsName: sns_1v1_low_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +10% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 01 => +5% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 10 => +0% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 11 => -5% of Vmon will trigger dip detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V1LowThreshSel: 2;        /*## attribute Sns1V1LowThreshSel */
   /**
	* BitsName: sns_1v1_low_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V1LowDlySel: 2;        /*## attribute Sns1V1LowDlySel */
   /**
	* BitsName: sns_1v1_low_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will never get  triggered )
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V1LowSelExtVref: 1;        /*## attribute Sns1V1LowSelExtVref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_HIGH_TOP_CONTROLBits_t
* RegisterName: gldo1v1_sns_high_top_control
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: sns_1v1_high_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied
	*/
    uint32 Sns1V1HighReset: 1;        /*## attribute Sns1V1HighReset */
   /**
	* BitsName: sns_1v1_high_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	*/
    uint32 Sns1V1HighPd: 1;        /*## attribute Sns1V1HighPd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_HIGH_CONFIGBits_t
* RegisterName: gldo1v1_sns_high_config
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: sns_1v1_high_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "001" in an application context. Other values not to be used
	*/
    uint32 Sns1V1HighVmonSel: 3;        /*## attribute Sns1V1HighVmonSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v1_high_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* 
	* Set this bit to '1' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V1HighPeakDipSel: 1;        /*## attribute Sns1V1HighPeakDipSel */
   /**
	* BitsName: sns_1v1_high_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +5% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 01 => +10% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 10 => +15% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 11 => +20% of Vmon will trigger peak detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V1HighThreshSel: 2;        /*## attribute Sns1V1HighThreshSel */
   /**
	* BitsName: sns_1v1_high_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V1HighDlySel: 2;        /*## attribute Sns1V1HighDlySel */
   /**
	* BitsName: sns_1v1_high_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will be triggered always)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V1HighSelExtVref: 1;        /*## attribute Sns1V1HighSelExtVref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_LOW_TOP_CONTROLBits_t
* RegisterName: gldo1v8_sns_low_top_control
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: sns_1v8_low_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowReset: 1;        /*## attribute Sns1V8LowReset */
   /**
	* BitsName: sns_1v8_low_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowPd: 1;        /*## attribute Sns1V8LowPd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_LOW_CONFIGBits_t
* RegisterName: gldo1v8_sns_low_config
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: sns_1v8_low_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "011" in an application context. Other values not to be used
	*/
    uint32 Sns1V8LowVmonSel: 3;        /*## attribute Sns1V8LowVmonSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_low_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* Set this bit to '0'
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowPeakDipSel: 1;        /*## attribute Sns1V8LowPeakDipSel */
   /**
	* BitsName: sns_1v8_low_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +10% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 01 => +5% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 10 => +0% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 11 => -5% of Vmon will trigger dip detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V8LowThreshSel: 2;        /*## attribute Sns1V8LowThreshSel */
   /**
	* BitsName: sns_1v8_low_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V8LowDlySel: 2;        /*## attribute Sns1V8LowDlySel */
   /**
	* BitsName: sns_1v8_low_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will vener get triggered)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V8LowSelExtVref: 1;        /*## attribute Sns1V8LowSelExtVref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_HIGH_TOP_CONTROLBits_t
* RegisterName: gldo1v8_sns_high_top_control
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: sns_1v8_high_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8HighReset: 1;        /*## attribute Sns1V8HighReset */
   /**
	* BitsName: sns_1v8_high_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8HighPd: 1;        /*## attribute Sns1V8HighPd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_HIGH_CONFIGBits_t
* RegisterName: gldo1v8_sns_high_config
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: sns_1v8_high_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "011" in an application context. Other values not to be used
	*/
    uint32 Sns1V8HighVmonSel: 3;        /*## attribute Sns1V8HighVmonSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_high_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* Set this bit to '1
	*/
    uint32 Sns1V8HighPeakDipSel: 1;        /*## attribute Sns1V8HighPeakDipSel */
   /**
	* BitsName: sns_1v8_high_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +5% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 01 => +10% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 10 => +15% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 11 => +20% of Vmon will trigger peak detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V8HighThreshSel: 2;        /*## attribute Sns1V8HighThreshSel */
   /**
	* BitsName: sns_1v8_high_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V8HighDlySel: 2;        /*## attribute Sns1V8HighDlySel */
   /**
	* BitsName: sns_1v8_high_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will be triggered always)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V8HighSelExtVref: 1;        /*## attribute Sns1V8HighSelExtVref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO_BG_REF_CONFIGBits_t
* RegisterName: gldo_bg_ref_config
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 4;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 6;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: sel_vref
	* Description: Reset value set to 0 to select noisy bangap voltage reference for safe start-up.
	* 0:  internal BG is used ( may be more noisy)
	* 1: Calibarated low-noise refernce is used
	* 
	* As part of start up procedure this bit is set to '1'to ensure low noise performance of the supply
	*/
    uint32 SelVref: 1;        /*## attribute SelVref */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 15;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod15_GldoBgRefConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO_BG_REF_STATUSBits_t
* RegisterName: gldo_bg_ref_status
* 
* AddressRange: 0xREAD - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: bg_ok
	* Description: Band gap  setting OK
	* 0: Nok OK
	* 1: OK
	*/
    uint32 BgOk: 1;        /*## attribute BgOk */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ref_ok
	* Description: Reference setting OK
	* 0: Nok OK
	* 1: OK
	*/
    uint32 RefOk: 1;        /*## attribute RefOk */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_GldoBgRefStatusBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO_BG_REF_CONFIG_EXTBits_t
* RegisterName: gldo_bg_ref_config_ext
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: ref_set_dc
	* Description: Reset value is set to the middle of the control range for low-noise reference to start nominally at 900mV in case of sel_vref  toggles by accident before calibrating ref_set_dc.
	* 
	* Trim code 7b?0000000 leads to maximum value and 7b?1111111 to minimum value of ref0v9 output voltage. Trimming step size depends on set_curve[2:0] and varies from 5mV (set_curve=7) to 7.8mV (set_curve=0) at nominal corner. The default dc trim step size at set_curve=4 is 6mV at nominal corner.
	* 
	* As part of calibaration this value is replaced with a calibrated value from OTP (ref_set_dc is form OTP ( 0x3C bits 31..25))
	* 
	* Note1: . A 6mV step with the ?ref_set_dc? (*) leads to 12mV step in the 1v8 and 7.33mV step in 1v1.
	* Note that higher code leads to lower output voltage.
	* 
	* Note2: both 1v1 and 1v8; not independent
	*/
    uint32 RefSetDc: 7;        /*## attribute RefSetDc */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ref_set_curve
	* Description: Reset value is set to the middle of the control range for low-noise reference to start with zero Temperature Coefficient in silicon.
	* Set this to value  always to "100" in an application context
	*/
    uint32 RefSetCurve: 3;        /*## attribute RefSetCurve */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 21;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod15_GldoBgRefConfigExtBits_t;
    /**
* Nxp_Tef810x_Mod15_TEST_ERROR_FLAG_STATUSBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: supply_1v1_low_error_flag
	* Description: 1V1 LOW SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V1LowErrorFlag: 1;        /*## attribute Supply1V1LowErrorFlag */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_1v1_high_error_flag
	* Description: 1V1 high SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V1HighErrorFlag: 1;        /*## attribute Supply1V1HighErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: supply_1v8_low_error_flag
	* Description: 1V8 LOW SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V8LowErrorFlag: 1;        /*## attribute Supply1V8LowErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_1v8_high_error_flag
	* Description: 1V8 high SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V8HighErrorFlag: 1;        /*## attribute Supply1V8HighErrorFlag */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod15_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_LOW_CAL_REGBits_t
* RegisterName: gldo1v1_sns_low_cal_reg
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: gldo1v1_sns_low_cal
	* Description: Select 1.1V dip supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets dip supply threshold to -3%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_low_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_low_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v1_low_thresh_sel=00 -> att_SNS=1.1
	* sns_1v1_low_thresh_sel=01 -> att_SNS=1.05
	* sns_1v1_low_thresh_sel=10 -> att_SNS=1
	* sns_1v1_low_thresh_sel=11 -> att_SNS=0.95
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v1_sns_low_cal = 6'b111111, sns1v1_low_cal[63]=1 sns1v1_low_cal[62:0]=0 
	* gldo1v1_sns_low_cal = 6'b000000, sns1v1_low_cal[0]=1 sns1v1_low_cal[63:1]=0
	*/
    uint32 Gldo1V1SnsLowCal: 6;        /*## attribute Gldo1V1SnsLowCal */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V1_SNS_HIGH_CAL_REGBits_t
* RegisterName: gldo1v1_sns_high_cal_reg
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: gldo1v1_sns_high_cal
	* Description: Select 1.1V peak supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets peak supply threshold to +8%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_high_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_high_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v1_high_thresh_sel=00 -> att_SNS=1.05
	* sns_1v1_high_thresh_sel=01 -> att_SNS=1.1
	* sns_1v1_high_thresh_sel=10 -> att_SNS=1.15
	* sns_1v1_high_thresh_sel=11 -> att_SNS=1.2
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v1_sns_high_cal = 6'b111111, sns1v1_high_cal[63]=1 sns1v1_high_cal[62:0]=0 
	* gldo1v1_sns_high_cal = 6'b000000, sns1v1_high_cal[0]=1 sns1v1_high_cal[63:1]=0
	*/
    uint32 Gldo1V1SnsHighCal: 6;        /*## attribute Gldo1V1SnsHighCal */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_LOW_CAL_REGBits_t
* RegisterName: gldo1v8_sns_low_cal_reg
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: gldo1v8_sns_low_cal
	* Description: Select 1.8V dip supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets dip supply threshold to -3%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_low_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_low_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v8_low_thresh_sel=00 -> att_SNS=1.1
	* sns_1v8_low_thresh_sel=01 -> att_SNS=1.05
	* sns_1v8_low_thresh_sel=10 -> att_SNS=1
	* sns_1v8_low_thresh_sel=11 -> att_SNS=0.95
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v8_sns_low_cal = 6'b111111, sns1v8_low_cal[63]=1 sns1v8_low_cal[62:0]=0 
	* gldo1v8_sns_low_cal = 6'b000000, sns1v8_low_cal[0]=1 sns1v8_low_cal[63:1]=0
	*/
    uint32 Gldo1V8SnsLowCal: 6;        /*## attribute Gldo1V8SnsLowCal */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_GLDO1V8_SNS_HIGH_CAL_REGBits_t
* RegisterName: gldo1v8_sns_high_cal_reg
* 
* AddressRange: 0xREADWRITE - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: gldo1v8_sns_high_cal
	* Description: Select 1.8V peak supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets peak supply threshold to +8%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_high_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_high_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v8_high_thresh_sel=00 -> att_SNS=1.05
	* sns_1v8_high_thresh_sel=01 -> att_SNS=1.1
	* sns_1v8_high_thresh_sel=10 -> att_SNS=1.15
	* sns_1v8_high_thresh_sel=11 -> att_SNS=1.2
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v8_sns_high_cal = 6'b111111, sns1v8_high_cal[63]=1 sns1v8_high_cal[62:0]=0 
	* gldo1v8_sns_high_cal = 6'b000000, sns1v8_high_cal[0]=1 sns1v8_high_cal[63:1]=0
	*/
    uint32 Gldo1V8SnsHighCal: 6;        /*## attribute Gldo1V8SnsHighCal */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: APPERURE
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Apperure: 8;        /*## attribute Apperure */
   /**
	* BitsName: MINOR_RIVISION
	* Description: Minor revision numer i.e. with no software consequences
	*/
    uint32 MinorRivision: 4;        /*## attribute MinorRivision */
   /**
	* BitsName: MAJOR_RIVISION
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRivision: 4;        /*## attribute MajorRivision */
   /**
	* BitsName: IDENTIFIER
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod15_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlBits_t
* RegisterName: gldo1v1_sns_low_top_control
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
	* BitsName: sns_1v1_low_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	*/
    uint32 Sns1V1LowPd: 1;        /*## attribute Sns1V1LowPd */
   /**
	* BitsName: sns_1v1_low_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied
	*/
    uint32 Sns1V1LowReset: 1;        /*## attribute Sns1V1LowReset */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigBits_t
* RegisterName: gldo1v1_sns_low_config
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v1_low_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will never get  triggered )
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V1LowSelExtVref: 1;        /*## attribute Sns1V1LowSelExtVref */
   /**
	* BitsName: sns_1v1_low_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V1LowDlySel: 2;        /*## attribute Sns1V1LowDlySel */
   /**
	* BitsName: sns_1v1_low_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +10% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 01 => +5% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 10 => +0% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 11 => -5% of Vmon will trigger dip detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V1LowThreshSel: 2;        /*## attribute Sns1V1LowThreshSel */
   /**
	* BitsName: sns_1v1_low_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V1LowPeakDipSel: 1;        /*## attribute Sns1V1LowPeakDipSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: sns_1v1_low_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "001" in an application context. Other values not to be used
	*/
    uint32 Sns1V1LowVmonSel: 3;        /*## attribute Sns1V1LowVmonSel */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlBits_t
* RegisterName: gldo1v1_sns_high_top_control
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v1_high_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	*/
    uint32 Sns1V1HighPd: 1;        /*## attribute Sns1V1HighPd */
   /**
	* BitsName: sns_1v1_high_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied
	*/
    uint32 Sns1V1HighReset: 1;        /*## attribute Sns1V1HighReset */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigBits_t
* RegisterName: gldo1v1_sns_high_config
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00000011
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v1_high_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will be triggered always)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V1HighSelExtVref: 1;        /*## attribute Sns1V1HighSelExtVref */
   /**
	* BitsName: sns_1v1_high_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V1HighDlySel: 2;        /*## attribute Sns1V1HighDlySel */
   /**
	* BitsName: sns_1v1_high_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +5% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 01 => +10% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 10 => +15% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 11 => +20% of Vmon will trigger peak detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V1HighThreshSel: 2;        /*## attribute Sns1V1HighThreshSel */
   /**
	* BitsName: sns_1v1_high_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* 
	* Set this bit to '1' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V1HighPeakDipSel: 1;        /*## attribute Sns1V1HighPeakDipSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: sns_1v1_high_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "001" in an application context. Other values not to be used
	*/
    uint32 Sns1V1HighVmonSel: 3;        /*## attribute Sns1V1HighVmonSel */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlBits_t
* RegisterName: gldo1v8_sns_low_top_control
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_low_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowPd: 1;        /*## attribute Sns1V8LowPd */
   /**
	* BitsName: sns_1v8_low_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowReset: 1;        /*## attribute Sns1V8LowReset */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigBits_t
* RegisterName: gldo1v8_sns_low_config
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x00000003
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_low_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will vener get triggered)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V8LowSelExtVref: 1;        /*## attribute Sns1V8LowSelExtVref */
   /**
	* BitsName: sns_1v8_low_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V8LowDlySel: 2;        /*## attribute Sns1V8LowDlySel */
   /**
	* BitsName: sns_1v8_low_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +10% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 01 => +5% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 10 => +0% of Vmon will trigger dip detect signal
	* thresh_sel<1:0> = 11 => -5% of Vmon will trigger dip detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V8LowThreshSel: 2;        /*## attribute Sns1V8LowThreshSel */
   /**
	* BitsName: sns_1v8_low_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* Set this bit to '0'
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8LowPeakDipSel: 1;        /*## attribute Sns1V8LowPeakDipSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: sns_1v8_low_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "011" in an application context. Other values not to be used
	*/
    uint32 Sns1V8LowVmonSel: 3;        /*## attribute Sns1V8LowVmonSel */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlBits_t
* RegisterName: gldo1v8_sns_high_top_control
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_high_pd
	* Description: Power down supply low sensor
	* 0: Normal operation
	* 1: Supply monitor powered down
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8HighPd: 1;        /*## attribute Sns1V8HighPd */
   /**
	* BitsName: sns_1v8_high_reset
	* Description: Reset (high) signal of LDO SM
	* 0: No action
	* 1: Reset is applied 
	* 
	* Set this bit to '0' for this insatance.. Other values are not permited
	*/
    uint32 Sns1V8HighReset: 1;        /*## attribute Sns1V8HighReset */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigBits_t
* RegisterName: gldo1v8_sns_high_config
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00000013
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_1v8_high_sel_ext_vref
	* Description: Selects the reference to external VREF from ext_vref pin and compares with input supply. Peak or dip comparison is dependent on  status of peak_dip_sel.
	* Only  for validation.
	* 0: Internal reference is used
	* 1: Not to be used in a functional context ( vref is tied to GND .. if this  bit is set to '1' then error flag will be triggered always)
	* 
	* Always set this bit to  '0' in an application context. Other values not permitted.
	*/
    uint32 Sns1V8HighSelExtVref: 1;        /*## attribute Sns1V8HighSelExtVref */
   /**
	* BitsName: sns_1v8_high_dly_sel
	* Description: Selects the time of pulse width the supply has to stay HIGHER / LOWER than the peak / dip threshold selected to trigger the output.
	* Dly_sel<1:0> = 00, 5ns 
	* dly_sel<1:0> = 01, 10ns
	* dly_sel<1:0> = 10 , 20ns 
	* dly_sel<1:0> = 11 , not_used
	* dly_sel<1:0> = 11 , not_used
	* 
	* Set this value to value "10" in an application context. Other values not to be used
	*/
    uint32 Sns1V8HighDlySel: 2;        /*## attribute Sns1V8HighDlySel */
   /**
	* BitsName: sns_1v8_high_thresh_sel
	* Description: selects supply noise threshold (coarse setting):
	* thresh_sel<1:0> = 00 => +5% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 01 => +10% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 10 => +15% of Vmon will trigger peak detect signal
	* thresh_sel<1:0> = 11 => +20% of Vmon will trigger peak detect signal
	* 
	* Value to be trimmed during testing.
	*/
    uint32 Sns1V8HighThreshSel: 2;        /*## attribute Sns1V8HighThreshSel */
   /**
	* BitsName: sns_1v8_high_peak_dip_sel
	* Description: Select bit peak detection or dip detection: IF peak_dip_sel = 1, peak will be detected. IF peak_dip_sel = 0, dip will be detect
	* 0: monitor trigger if the monitored voltage is below this threshold
	* 1: monitor trigger if the monitored voltage is above  this threshold
	* Set this bit to '1
	*/
    uint32 Sns1V8HighPeakDipSel: 1;        /*## attribute Sns1V8HighPeakDipSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: sns_1v8_high_vmon_sel
	* Description: Digital bits for selecting power supply domain to be monitored.
	* Vmon_sel<2:0> =  000, 0.9V supply
	* Vmon_sel<2:0> =  001, 1.1V supply
	* Vmon_sel<2:0> =  010, 1.2V supply
	* Vmon_sel<2:0> =  011, 1.8V supply
	* Vmon_sel<2:0> =  100, 2.5V supply
	* Vmon_sel<2:0> =  101, 3.3V supply
	* Vmon_sel<2:0> =  110, not_used
	* Vmon_sel<2:0> =  111, not_used
	* 
	* Set this value to value "011" in an application context. Other values not to be used
	*/
    uint32 Sns1V8HighVmonSel: 3;        /*## attribute Sns1V8HighVmonSel */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GldoBgRefConfigBits_t
* RegisterName: gldo_bg_ref_config
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00001F00
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_vref
	* Description: Reset value set to 0 to select noisy bangap voltage reference for safe start-up.
	* 0:  internal BG is used ( may be more noisy)
	* 1: Calibarated low-noise refernce is used
	* 
	* As part of start up procedure this bit is set to '1'to ensure low noise performance of the supply
	*/
    uint32 SelVref: 1;        /*## attribute SelVref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 6;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod15_GldoBgRefConfigBits_t;
    /**
* Nxp_Tef810x_Mod15_GldoBgRefStatusBits_t
* RegisterName: gldo_bg_ref_status
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000011
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: ref_ok
	* Description: Reference setting OK
	* 0: Nok OK
	* 1: OK
	*/
    uint32 RefOk: 1;        /*## attribute RefOk */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: bg_ok
	* Description: Band gap  setting OK
	* 0: Nok OK
	* 1: OK
	*/
    uint32 BgOk: 1;        /*## attribute BgOk */
}Nxp_Tef810x_Mod15_GldoBgRefStatusBits_t;
    /**
* Nxp_Tef810x_Mod15_GldoBgRefConfigExtBits_t
* RegisterName: gldo_bg_ref_config_ext
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x0000043F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 21;        /*## attribute Reserved0 */
   /**
	* BitsName: ref_set_curve
	* Description: Reset value is set to the middle of the control range for low-noise reference to start with zero Temperature Coefficient in silicon.
	* Set this to value  always to "100" in an application context
	*/
    uint32 RefSetCurve: 3;        /*## attribute RefSetCurve */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: ref_set_dc
	* Description: Reset value is set to the middle of the control range for low-noise reference to start nominally at 900mV in case of sel_vref  toggles by accident before calibrating ref_set_dc.
	* 
	* Trim code 7b?0000000 leads to maximum value and 7b?1111111 to minimum value of ref0v9 output voltage. Trimming step size depends on set_curve[2:0] and varies from 5mV (set_curve=7) to 7.8mV (set_curve=0) at nominal corner. The default dc trim step size at set_curve=4 is 6mV at nominal corner.
	* 
	* As part of calibaration this value is replaced with a calibrated value from OTP (ref_set_dc is form OTP ( 0x3C bits 31..25))
	* 
	* Note1: . A 6mV step with the ?ref_set_dc? (*) leads to 12mV step in the 1v8 and 7.33mV step in 1v1.
	* Note that higher code leads to lower output voltage.
	* 
	* Note2: both 1v1 and 1v8; not independent
	*/
    uint32 RefSetDc: 7;        /*## attribute RefSetDc */
}Nxp_Tef810x_Mod15_GldoBgRefConfigExtBits_t;
    /**
* Nxp_Tef810x_Mod15_TestErrorFlagStatusBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_1v8_high_error_flag
	* Description: 1V8 high SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V8HighErrorFlag: 1;        /*## attribute Supply1V8HighErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: supply_1v8_low_error_flag
	* Description: 1V8 LOW SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V8LowErrorFlag: 1;        /*## attribute Supply1V8LowErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_1v1_high_error_flag
	* Description: 1V1 high SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V1HighErrorFlag: 1;        /*## attribute Supply1V1HighErrorFlag */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: supply_1v1_low_error_flag
	* Description: 1V1 LOW SNS error flag.
	* 
	* When Read
	* 0 = No error from Analogue Module
	* 1 = Error set from Analogue Module
	* 
	* Write
	* 0 = No error set to Inner Safety Monitor
	* 1 = Error set to Inner Safety Monitor
	*/
    uint32 Supply1V1LowErrorFlag: 1;        /*## attribute Supply1V1LowErrorFlag */
}Nxp_Tef810x_Mod15_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegBits_t
* RegisterName: gldo1v1_sns_low_cal_reg
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x0000003F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: gldo1v1_sns_low_cal
	* Description: Select 1.1V dip supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets dip supply threshold to -3%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_low_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_low_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v1_low_thresh_sel=00 -> att_SNS=1.1
	* sns_1v1_low_thresh_sel=01 -> att_SNS=1.05
	* sns_1v1_low_thresh_sel=10 -> att_SNS=1
	* sns_1v1_low_thresh_sel=11 -> att_SNS=0.95
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v1_sns_low_cal = 6'b111111, sns1v1_low_cal[63]=1 sns1v1_low_cal[62:0]=0 
	* gldo1v1_sns_low_cal = 6'b000000, sns1v1_low_cal[0]=1 sns1v1_low_cal[63:1]=0
	*/
    uint32 Gldo1V1SnsLowCal: 6;        /*## attribute Gldo1V1SnsLowCal */
}Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegBits_t
* RegisterName: gldo1v1_sns_high_cal_reg
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x0000003F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: gldo1v1_sns_high_cal
	* Description: Select 1.1V peak supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets peak supply threshold to +8%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_high_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v1_sns_high_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v1_high_thresh_sel=00 -> att_SNS=1.05
	* sns_1v1_high_thresh_sel=01 -> att_SNS=1.1
	* sns_1v1_high_thresh_sel=10 -> att_SNS=1.15
	* sns_1v1_high_thresh_sel=11 -> att_SNS=1.2
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v1_sns_high_cal = 6'b111111, sns1v1_high_cal[63]=1 sns1v1_high_cal[62:0]=0 
	* gldo1v1_sns_high_cal = 6'b000000, sns1v1_high_cal[0]=1 sns1v1_high_cal[63:1]=0
	*/
    uint32 Gldo1V1SnsHighCal: 6;        /*## attribute Gldo1V1SnsHighCal */
}Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegBits_t
* RegisterName: gldo1v8_sns_low_cal_reg
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x0000003F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: gldo1v8_sns_low_cal
	* Description: Select 1.8V dip supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets dip supply threshold to -3%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_low_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_low_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v8_low_thresh_sel=00 -> att_SNS=1.1
	* sns_1v8_low_thresh_sel=01 -> att_SNS=1.05
	* sns_1v8_low_thresh_sel=10 -> att_SNS=1
	* sns_1v8_low_thresh_sel=11 -> att_SNS=0.95
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v8_sns_low_cal = 6'b111111, sns1v8_low_cal[63]=1 sns1v8_low_cal[62:0]=0 
	* gldo1v8_sns_low_cal = 6'b000000, sns1v8_low_cal[0]=1 sns1v8_low_cal[63:1]=0
	*/
    uint32 Gldo1V8SnsLowCal: 6;        /*## attribute Gldo1V8SnsLowCal */
}Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegBits_t
* RegisterName: gldo1v8_sns_high_cal_reg
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x0000003F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: gldo1v8_sns_high_cal
	* Description: Select 1.8V peak supply noise threshold (fine setting)
	* 
	* Value to be trimmed during testing and read from OTP before operation, sets peak supply threshold to +8%
	* 
	* For simulation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_high_cal_reg-55) x 0.002] x att_SNS
	* For validation: Vthreshold = Vnominal x [1 + (gldo1v8_sns_high_cal_reg-63) x 0.002] x att_SNS
	* 
	* sns_1v8_high_thresh_sel=00 -> att_SNS=1.05
	* sns_1v8_high_thresh_sel=01 -> att_SNS=1.1
	* sns_1v8_high_thresh_sel=10 -> att_SNS=1.15
	* sns_1v8_high_thresh_sel=11 -> att_SNS=1.2
	* 
	* The register value is converted into corresponding one hot encoded value and driven to signal sns1v1_low_cal [63:0]
	* 
	* ie if gldo1v8_sns_high_cal = 6'b111111, sns1v8_high_cal[63]=1 sns1v8_high_cal[62:0]=0 
	* gldo1v8_sns_high_cal = 6'b000000, sns1v8_high_cal[0]=1 sns1v8_high_cal[63:1]=0
	*/
    uint32 Gldo1V8SnsHighCal: 6;        /*## attribute Gldo1V8SnsHighCal */
}Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegBits_t;
    /**
* Nxp_Tef810x_Mod15_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00153301
*/
typedef struct  {
   /**
	* BitsName: IDENTIFIER
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
   /**
	* BitsName: MAJOR_RIVISION
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRivision: 4;        /*## attribute MajorRivision */
   /**
	* BitsName: MINOR_RIVISION
	* Description: Minor revision numer i.e. with no software consequences
	*/
    uint32 MinorRivision: 4;        /*## attribute MinorRivision */
   /**
	* BitsName: APPERURE
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Apperure: 8;        /*## attribute Apperure */
}Nxp_Tef810x_Mod15_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t;
/**
* Nxp_Tef810x_Mod15_GldoBgRefConfigUnion_t
* Nxp_Tef810x_Mod15_GldoBgRefConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_GldoBgRefConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_GldoBgRefConfigUnion_t;
/**
* Nxp_Tef810x_Mod15_GldoBgRefStatusUnion_t
* Nxp_Tef810x_Mod15_GldoBgRefStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_GldoBgRefStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_GldoBgRefStatusUnion_t;
/**
* Nxp_Tef810x_Mod15_GldoBgRefConfigExtUnion_t
* Nxp_Tef810x_Mod15_GldoBgRefConfigExtUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_GldoBgRefConfigExtBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_GldoBgRefConfigExtUnion_t;
/**
* Nxp_Tef810x_Mod15_TestErrorFlagStatusUnion_t
* Nxp_Tef810x_Mod15_TestErrorFlagStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_TestErrorFlagStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_TestErrorFlagStatusUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegUnion_t
* Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegUnion_t;
/**
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegUnion_t
* Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegUnion_t;
/**
* Nxp_Tef810x_Mod15_ModuleidUnion_t
* Nxp_Tef810x_Mod15_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod15_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod15_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod15_GlobalLdoRegister_t
 * Nxp_Tef810x_Mod15_GlobalLdoRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x000
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: gldo1v1_sns_low_top_control
    * AddressOffset: 0x004
    * ResetValue: 0x00000000
    * Description: 1V1 supply low sensor control
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowTopControlUnion_t Gldo1V1SnsLowTopControl_ust;        /*## attribute Gldo1V1SnsLowTopControl_ust */
  /**
    * RegisterName: gldo1v1_sns_low_config
    * AddressOffset: 0x008
    * ResetValue: 0x00000001
    * Description: 1V1 supply low sensor configuration
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowConfigUnion_t Gldo1V1SnsLowConfig_ust;        /*## attribute Gldo1V1SnsLowConfig_ust */
  /**
    * RegisterName: gldo1v1_sns_high_top_control
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: 1V1 supply high  sensor control
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighTopControlUnion_t Gldo1V1SnsHighTopControl_ust;        /*## attribute Gldo1V1SnsHighTopControl_ust */
  /**
    * RegisterName: gldo1v1_sns_high_config
    * AddressOffset: 0x010
    * ResetValue: 0x00000011
    * Description: 1V1 supply high  sensor configuration
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighConfigUnion_t Gldo1V1SnsHighConfig_ust;        /*## attribute Gldo1V1SnsHighConfig_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x014
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: gldo1v8_sns_low_top_control
    * AddressOffset: 0x018
    * ResetValue: 0x00000000
    * Description: 1V8 supply low  sensor control
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowTopControlUnion_t Gldo1V8SnsLowTopControl_ust;        /*## attribute Gldo1V8SnsLowTopControl_ust */
  /**
    * RegisterName: gldo1v8_sns_low_config
    * AddressOffset: 0x01C
    * ResetValue: 0x00000003
    * Description: 1V8 supply low  sensor configuration
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowConfigUnion_t Gldo1V8SnsLowConfig_ust;        /*## attribute Gldo1V8SnsLowConfig_ust */
  /**
    * RegisterName: gldo1v8_sns_high_top_control
    * AddressOffset: 0x020
    * ResetValue: 0x00000000
    * Description: 1V1 supply high  sensor control
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighTopControlUnion_t Gldo1V8SnsHighTopControl_ust;        /*## attribute Gldo1V8SnsHighTopControl_ust */
  /**
    * RegisterName: gldo1v8_sns_high_config
    * AddressOffset: 0x024
    * ResetValue: 0x00000013
    * Description: 1V1 supply high  sensor configuration
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighConfigUnion_t Gldo1V8SnsHighConfig_ust;        /*## attribute Gldo1V8SnsHighConfig_ust */
  /**
    * RegisterName: gldo_bg_ref_config
    * AddressOffset: 0x028
    * ResetValue: 0x00001F00
    * Description: Global LDO reference settings
    */
    Nxp_Tef810x_Mod15_GldoBgRefConfigUnion_t GldoBgRefConfig_ust;        /*## attribute GldoBgRefConfig_ust */
  /**
    * RegisterName: gldo_bg_ref_status
    * AddressOffset: 0x02C
    * ResetValue: 0x00000011
    * Description: Global LDO reference status checK
    */
    Nxp_Tef810x_Mod15_GldoBgRefStatusUnion_t GldoBgRefStatus_ust;        /*## attribute GldoBgRefStatus_ust */
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x030
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x034
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x038
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x03C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x040
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: gldo_bg_ref_config_ext
    * AddressOffset: 0x044
    * ResetValue: 0x0000043F
    * Description: not used
    */
    Nxp_Tef810x_Mod15_GldoBgRefConfigExtUnion_t GldoBgRefConfigExt_ust;        /*## attribute GldoBgRefConfigExt_ust */
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x048
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: test_error_flag_status
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Registers for validation purposes. This will help to read error from SSB Analogue Module. Also to set error towards central controller. (Categorised as special R/W register)
    */
    Nxp_Tef810x_Mod15_TestErrorFlagStatusUnion_t TestErrorFlagStatus_ust;        /*## attribute TestErrorFlagStatus_ust */
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: gldo1v1_sns_low_cal_reg
    * AddressOffset: 0x05C
    * ResetValue: 0x0000003F
    * Description: This register is used to tune the threshold voltage. Value to be used comes from OTP
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsLowCalRegUnion_t Gldo1V1SnsLowCalReg_ust;        /*## attribute Gldo1V1SnsLowCalReg_ust */
  /**
    * RegisterName: gldo1v1_sns_high_cal_reg
    * AddressOffset: 0x060
    * ResetValue: 0x0000003F
    * Description: This register is used to tune the threshold voltage. Value to be used comes from OTP
    */
    Nxp_Tef810x_Mod15_Gldo1V1SnsHighCalRegUnion_t Gldo1V1SnsHighCalReg_ust;        /*## attribute Gldo1V1SnsHighCalReg_ust */
  /**
    * RegisterName: gldo1v8_sns_low_cal_reg
    * AddressOffset: 0x064
    * ResetValue: 0x0000003F
    * Description: This register is used to tune the threshold voltage. Value to be used comes from OTP
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsLowCalRegUnion_t Gldo1V8SnsLowCalReg_ust;        /*## attribute Gldo1V8SnsLowCalReg_ust */
  /**
    * RegisterName: gldo1v8_sns_high_cal_reg
    * AddressOffset: 0x068
    * ResetValue: 0x0000003F
    * Description: This register is used to tune the threshold voltage. Value to be used comes from OTP
    */
    Nxp_Tef810x_Mod15_Gldo1V8SnsHighCalRegUnion_t Gldo1V8SnsHighCalReg_ust;        /*## attribute Gldo1V8SnsHighCalReg_ust */

    uint32 gap01_au32[994];        /* gap 1 in register space */  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00153301
    * Description: Register with details of Module ID and Version number
    */
    Nxp_Tef810x_Mod15_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod15_GlobalLdoRegister_t;

#endif
