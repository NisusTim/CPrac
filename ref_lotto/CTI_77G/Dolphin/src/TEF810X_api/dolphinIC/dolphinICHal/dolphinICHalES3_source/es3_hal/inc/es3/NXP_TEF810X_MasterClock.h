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
* @NXP_TEF810X_MasterClock.h
*/
#ifndef NXP_TEF810X_MASTERCLOCK_H
#define NXP_TEF810X_MASTERCLOCK_H
#include "Std_Types.h"

#define MASTER_CLOCK_MODULE_ADDRESS 0x0C
/**
*NXP_TEF810X_MOD0C_IBIAS_CONTROL_U16
* RegisterName: MOD0C_ibias_control
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0xB0186444
*/
#define NXP_TEF810X_MOD0C_IBIAS_CONTROL_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD0C_PLL_LDO_CONTROL_U16
* RegisterName: MOD0C_pll_ldo_control
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x910F0F0F
*/
#define NXP_TEF810X_MOD0C_PLL_LDO_CONTROL_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD0C_LDO_CONTROL_U16
* RegisterName: MOD0C_ldo_control
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x0000000F
*/
#define NXP_TEF810X_MOD0C_LDO_CONTROL_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD0C_PFD_CONTROL_U16
* RegisterName: MOD0C_pfd_control
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_PFD_CONTROL_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD0C_CP_CONTROL_U16
* RegisterName: MOD0C_cp_control
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x000001FE
*/
#define NXP_TEF810X_MOD0C_CP_CONTROL_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD0C_OUTPUT_CLOCK_SKEW_CONTROL_U16
* RegisterName: MOD0C_output_clock_skew_control
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_OUTPUT_CLOCK_SKEW_CONTROL_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD0C_LOOP_FILTER_CONTROL_U16
* RegisterName: MOD0C_loop_filter_control
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x000010C7
*/
#define NXP_TEF810X_MOD0C_LOOP_FILTER_CONTROL_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD0C_LOCK_CONTROL_U16
* RegisterName: MOD0C_lock_control
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x000001C4
*/
#define NXP_TEF810X_MOD0C_LOCK_CONTROL_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD0C_XO_LDO_CONTROL_U16
* RegisterName: MOD0C_xo_ldo_control
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00000F0F
*/
#define NXP_TEF810X_MOD0C_XO_LDO_CONTROL_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD0C_CLOCK_BUFFER_CONTROL_U16
* RegisterName: MOD0C_clock_buffer_control
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_CLOCK_BUFFER_CONTROL_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD0C_REF_CLOCK_DELAY_CONTROL_U16
* RegisterName: MOD0C_ref_clock_delay_control
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_REF_CLOCK_DELAY_CONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD0C_CALIBRATION_VCO_CONTROL_U16
* RegisterName: MOD0C_calibration_vco_control
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x001A8188
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_VCO_CONTROL_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16
* RegisterName: MOD0C_calibration_aac_control
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x90471400
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_AAC_CONTROL_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD0C_CALIBRATION_AFC_CONTROL1_U16
* RegisterName: MOD0C_calibration_afc_control1
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x07805A00
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_AFC_CONTROL1_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD0C_CALIBRATION_AFC_CONTROL2_U16
* RegisterName: MOD0C_calibration_afc_control2
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x01067372
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_AFC_CONTROL2_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD0C_VCO_CONTROL_U16
* RegisterName: MOD0C_vco_control
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000110
*/
#define NXP_TEF810X_MOD0C_VCO_CONTROL_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16
* RegisterName: MOD0C_start_calibration_counter
* AccessMode: WRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD0C_RESET_CALIBRATION_U16
* RegisterName: MOD0C_reset_calibration
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_RESET_CALIBRATION_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD0C_SNS_LOW_TOP_CONTROL_U16
* RegisterName: MOD0C_sns_low_top_control
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_SNS_LOW_TOP_CONTROL_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD0C_CALIBRATION_STATUS1_U16
* RegisterName: MOD0C_calibration_status1
* AccessMode: READ
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x3E110101
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_STATUS1_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD0C_CALIBRATION_STATUS2_U16
* RegisterName: MOD0C_calibration_status2
* AccessMode: READ
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x000000FF
*/
#define NXP_TEF810X_MOD0C_CALIBRATION_STATUS2_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD0C_LOCK_STATUS_U16
* RegisterName: MOD0C_lock_status
* AccessMode: READ
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0C_LOCK_STATUS_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD0C_MODULEID_U16
* RegisterName: MOD0C_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x000C2201
*/
#define NXP_TEF810X_MOD0C_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod0C_IBIAS_CONTROLBits_t
* RegisterName: ibias_control
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: ctl_vcom_2G4_predriv
	* Description: PLL4G8 common mode voltage 2.4GHz pre driver trim value
	*/
    uint32 CtlVcom2G4Predriv: 3;        /*## attribute CtlVcom2G4Predriv */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ibias_2G4_predriv_200u
	* Description: PLL4G8 ibias 2.4GHz pre driver trim value
	*/
    uint32 CtlIbias2G4Predriv200U: 3;        /*## attribute CtlIbias2G4Predriv200U */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ibias_2G4buf_350u
	* Description: PLL4G8 ibias 2.4GHz output buffer trim value
	*/
    uint32 CtlIbias2G4Buf350U: 3;        /*## attribute CtlIbias2G4Buf350U */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_bias_opamp_100u
	* Description: PLL4G8 ibias opamp (inside charge pump) trim value
	*/
    uint32 CtlBiasOpamp100U: 3;        /*## attribute CtlBiasOpamp100U */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_bias_cp_100u
	* Description: PLL4G8 ibias charge pump trim value
	*/
    uint32 CtlBiasCp100U: 5;        /*## attribute CtlBiasCp100U */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: sel_iref_bias
	* Description: PLL4G8 internal current source trim value
	*/
    uint32 SelIrefBias: 5;        /*## attribute SelIrefBias */
   /**
	* BitsName: sel_globalref
	* Description: Selects the reference current source of the bias currents used in the PLL4G8 (100uA).
	* 0: selects the reference current source in the PLL4G8  
	* 1: selects the reference current source in the Global Bias
	*/
    uint32 SelGlobalref: 1;        /*## attribute SelGlobalref */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: en_iref_bias
	* Description: PLL4G8 internal current source enable
	* 1: Enable
	* 0: Disable
	*/
    uint32 EnIrefBias: 1;        /*## attribute EnIrefBias */
}Nxp_Tef810x_Mod0C_IbiasControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_PLL_LDO_CONTROLBits_t
* RegisterName: pll_ldo_control
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: vout_ldo1
	* Description: set output voltage of PLL4G8 LDO1.
	*/
    uint32 VoutLdo1: 5;        /*## attribute VoutLdo1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: vout_ldo2
	* Description: set output voltage of PLL4G8 LDO2.
	*/
    uint32 VoutLdo2: 5;        /*## attribute VoutLdo2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vout_ldo3
	* Description: set output voltage of PLL4G8 LDO3.
	*/
    uint32 VoutLdo3: 5;        /*## attribute VoutLdo3 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ena_ldo1
	* Description: enable PLL4G8 LDO1 (Divider)
	* 1: Enable LDO1
	* 0: Disable LDO1
	*/
    uint32 EnaLdo1: 1;        /*## attribute EnaLdo1 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ena_ldo2
	* Description: enable PLL4G8 LDO2 (Charge pump, PFD, Low-pass filterm PLL glue logic)
	* 1: Enable LDO2
	* 0: Disable LDO2
	*/
    uint32 EnaLdo2: 1;        /*## attribute EnaLdo2 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: ena_ldo3
	* Description: enable PLL4G8 LDO3 (VCO, peak detector for calibration, first stage divider, 2G4 I/O)
	* 1: Enable LDO3
	* 0: Disable LDO3
	*/
    uint32 EnaLdo3: 1;        /*## attribute EnaLdo3 */
}Nxp_Tef810x_Mod0C_PllLdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LDO_CONTROLBits_t
* RegisterName: ldo_control
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: ldo_sel_vout
	* Description: set output voltage of Master clock LDO
	* The values to be set will be coming from the calibration procedure ( OTP).
	*/
    uint32 LdoSelVout: 5;        /*## attribute LdoSelVout */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_en
	* Description: Master clock LDO enable (buffers, XO functional safety)
	* 1: Enable LDO
	* 0: Disable LDO
	*/
    uint32 LdoEn: 1;        /*## attribute LdoEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod0C_LdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_PFD_CONTROLBits_t
* RegisterName: pfd_control
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: pfd_force_down
	* Description: force pfd down
	* 1: Decrease current
	* 0: no effect
	*/
    uint32 PfdForceDown: 1;        /*## attribute PfdForceDown */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: pfd_force_up
	* Description: force pfd up
	* 1: Increase current
	* 0: no effect
	*/
    uint32 PfdForceUp: 1;        /*## attribute PfdForceUp */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: pfd_del
	* Description: pfd reset delay control
	*/
    uint32 PfdDel: 2;        /*## attribute PfdDel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: pfd_rst
	* Description: overrule reset pfd
	*/
    uint32 PfdRst: 1;        /*## attribute PfdRst */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod0C_PfdControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CP_CONTROLBits_t
* RegisterName: cp_control
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: cp_slice_ena
	* Description: set charge pump current per slice
	* Each bit controls one slice
	*/
    uint32 CpSliceEna: 8;        /*## attribute CpSliceEna */
   /**
	* BitsName: cp_ena
	* Description: enable charge pump
	* 1: Enable
	* 0: Disable
	*/
    uint32 CpEna: 1;        /*## attribute CpEna */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_CpControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_OUTPUT_CLOCK_SKEW_CONTROLBits_t
* RegisterName: output_clock_skew_control
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: output_clk_skew
	* Description: fine pitch 600MHz output clock skew 0 to -15/16.T
	*/
    uint32 OutputClkSkew: 4;        /*## attribute OutputClkSkew */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_OutputClockSkewControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LOOP_FILTER_CONTROLBits_t
* RegisterName: loop_filter_control
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: lpf_C1
	* Description: LPF set C1 value
	*/
    uint32 LpfC1: 4;        /*## attribute LpfC1 */
   /**
	* BitsName: lpf_C2
	* Description: LPF set C2 value
	*/
    uint32 LpfC2: 4;        /*## attribute LpfC2 */
   /**
	* BitsName: lpf_R2
	* Description: LPF set R2 value
	*/
    uint32 LpfR2: 5;        /*## attribute LpfR2 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_LoopFilterControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LOCK_CONTROLBits_t
* RegisterName: lock_control
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: lock_det_mode_ctrl
	* Description: lock detector mode control (7:6=anl, 4:0=dig)
	*/
    uint32 LockDetModeCtrl: 8;        /*## attribute LockDetModeCtrl */
   /**
	* BitsName: lock_det_enable
	* Description: lock detector enable
	* 1: Enable
	* 0: Disable
	*/
    uint32 LockDetEnable: 1;        /*## attribute LockDetEnable */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: lock_det_force_rst
	* Description: lock detector force reset condition
	*/
    uint32 LockDetForceRst: 1;        /*## attribute LockDetForceRst */
}Nxp_Tef810x_Mod0C_LockControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_XO_LDO_CONTROLBits_t
* RegisterName: xo_ldo_control
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: xo_ldo_vout
	* Description: ldo output voltage selection inputs(1.8v)
	* .
	*/
    uint32 XoLdoVout: 5;        /*## attribute XoLdoVout */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: xo_ldo_iref
	* Description: internal ldo reference current selection inputs(1.8v)
	*/
    uint32 XoLdoIref: 5;        /*## attribute XoLdoIref */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: xo_en_iref_ext
	* Description: external ldo reference current selection input (1.8v). Presently not used bit
	*/
    uint32 XoEnIrefExt: 1;        /*## attribute XoEnIrefExt */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 15;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod0C_XoLdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CLOCK_BUFFER_CONTROLBits_t
* RegisterName: clock_buffer_control
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: en_clk_chirp_480
	* Description: Enable 480MHz chirp clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkChirp480: 1;        /*## attribute EnClkChirp480 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: en_clk_ser_480_600
	* Description: Enable 480_600MHz SER clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkSer480600: 1;        /*## attribute EnClkSer480600 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_clk_adc_600
	* Description: Enable 600MHz ADC clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkAdc600: 1;        /*## attribute EnClkAdc600 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_clk_ssbmod_600
	* Description: Enable 600MHz SSBmod clock buffer 0 = disable
	* 1 = enable
	*/
    uint32 EnClkSsbmod600: 1;        /*## attribute EnClkSsbmod600 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: en_clk_adc_40
	* Description: Enable 40MHz ADC clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkAdc40: 1;        /*## attribute EnClkAdc40 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_clk_chirp_dft_480_600
	* Description: Enable 480_600MHz Chirp DFT clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkChirpDft480600: 1;        /*## attribute EnClkChirpDft480600 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: en_clk_adc_dft_600
	* Description: Enable 600MHz ADC DFT clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkAdcDft600: 1;        /*## attribute EnClkAdcDft600 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 7;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod0C_ClockBufferControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_REF_CLOCK_DELAY_CONTROLBits_t
* RegisterName: ref_clock_delay_control
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: sel_delay_clk40
	* Description: Select reference clock delay factor N
	* Delay = N. (1/600MHz). N=0?14
	*/
    uint32 SelDelayClk40: 4;        /*## attribute SelDelayClk40 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_RefClockDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_VCO_CONTROLBits_t
* RegisterName: calibration_vco_control
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: vco_level_func_safety
	* Description: VCO level comparator window for functional safety
	*/
    uint32 VcoLevelFuncSafety: 4;        /*## attribute VcoLevelFuncSafety */
   /**
	* BitsName: vco_level_recalib_window
	* Description: VCO level comparator window for recalibration
	*/
    uint32 VcoLevelRecalibWindow: 4;        /*## attribute VcoLevelRecalibWindow */
   /**
	* BitsName: vco_level_comp_ena
	* Description: VCO level comparator enable
	* 1: Comparator enabled
	* 0: Comparator disabled
	*/
    uint32 VcoLevelCompEna: 1;        /*## attribute VcoLevelCompEna */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: vtune_recalib_window
	* Description: Vtune voltage comparator window for recalibration
	*/
    uint32 VtuneRecalibWindow: 4;        /*## attribute VtuneRecalibWindow */
   /**
	* BitsName: vtune_override_delay
	* Description: manual VCO tuning voltage override delay
	*/
    uint32 VtuneOverrideDelay: 4;        /*## attribute VtuneOverrideDelay */
   /**
	* BitsName: vco_freq_comp_ena
	* Description: VCO tuning voltage comparator enable
	* 1: Comparator enabled
	* 0: Comparator disabled
	*/
    uint32 VcoFreqCompEna: 1;        /*## attribute VcoFreqCompEna */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vtune_override_in
	* Description: manual VCO tuning voltage override
	* 1: tune voltage manually set
	* 0: Manual control will not affect
	*/
    uint32 VtuneOverrideIn: 1;        /*## attribute VtuneOverrideIn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 7;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod0C_CalibrationVcoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_AAC_CONTROLBits_t
* RegisterName: calibration_aac_control
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: aac_ictrl_min
	* Description: minimum amplitude loop setting
	*/
    uint32 AacIctrlMin: 6;        /*## attribute AacIctrlMin */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: aac_ictrl_init
	* Description: initial amplitude loop setting (manual mode)
	*/
    uint32 AacIctrlInit: 6;        /*## attribute AacIctrlInit */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: aac_lock_ctrl
	* Description: amplitude loop lock control criterium
	*/
    uint32 AacLockCtrl: 3;        /*## attribute AacLockCtrl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: aac_ki
	* Description: amplitude control loop Ki value
	*/
    uint32 AacKi: 3;        /*## attribute AacKi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: aac_ades_in
	* Description: amplitude control desired value
	*/
    uint32 AacAdesIn: 5;        /*## attribute AacAdesIn */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: aac_manual
	* Description: amplitude control loop manual mode
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AacManual: 1;        /*## attribute AacManual */
   /**
	* BitsName: aac_enable
	* Description: automatic amplitude control loop enable
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AacEnable: 1;        /*## attribute AacEnable */
}Nxp_Tef810x_Mod0C_CalibrationAacControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_AFC_CONTROL1Bits_t
* RegisterName: calibration_afc_control1
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: afc_fsel_min
	* Description: minimum frequency loop setting
	*/
    uint32 AfcFselMin: 8;        /*## attribute AfcFselMin */
   /**
	* BitsName: afc_fsel_init
	* Description: initial frequency loop setting (manual mode)
	*/
    uint32 AfcFselInit: 8;        /*## attribute AfcFselInit */
   /**
	* BitsName: afc_mdes
	* Description: frequency loop desired Mvalue
	*/
    uint32 AfcMdes: 12;        /*## attribute AfcMdes */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_CalibrationAfcControl1Bits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_AFC_CONTROL2Bits_t
* RegisterName: calibration_afc_control2
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: afc_lock_ctrl1
	* Description: frequency loop lock control criterium 1
	*/
    uint32 AfcLockCtrl1: 3;        /*## attribute AfcLockCtrl1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: afc_lock_ctrl2
	* Description: frequency loop lock control criterium 2
	*/
    uint32 AfcLockCtrl2: 3;        /*## attribute AfcLockCtrl2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: afc_step_limit
	* Description: frequency loop integrator step limiter
	*/
    uint32 AfcStepLimit: 3;        /*## attribute AfcStepLimit */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: afc_ki
	* Description: initial frequency loop setting (manual mode)
	*/
    uint32 AfcKi: 3;        /*## attribute AfcKi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: afc_fref_sel
	* Description: frequency loop fref select
	*/
    uint32 AfcFrefSel: 3;        /*## attribute AfcFrefSel */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: afc_manual
	* Description: frequency control loop manual mode
	* 1: Manual mode Enabled
	* 0: Disabled
	*/
    uint32 AfcManual: 1;        /*## attribute AfcManual */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: afc_enable
	* Description: automatic frequency control loop enable
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AfcEnable: 1;        /*## attribute AfcEnable */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 7;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod0C_CalibrationAfcControl2Bits_t;
    /**
* Nxp_Tef810x_Mod0C_VCO_CONTROLBits_t
* RegisterName: vco_control
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: vco_Rset
	* Description: vco current control resistor value (internally this delayed by pon_counter cycles)
	*/
    uint32 VcoRset: 5;        /*## attribute VcoRset */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: vco_en
	* Description: enable vco (internally this delayed by pon_counter cycles)
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 VcoEn: 1;        /*## attribute VcoEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: pon_ls_spi
	* Description: This bit is used for validation purpose only. The pon from Central control is used to control the level shifters and vco enabling. By default the xtal oscillator circuit pon is enabled
	* 1: Enabled (permenant)
	* 0: No effect
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 19;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod0C_VcoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_START_CALIBRATION_COUNTERBits_t
* RegisterName: start_calibration_counter
* 
* AddressRange: 0xWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: start_calibration_counter
	* Description: Once this register is programmed (non-zero), start calibration bit towards analog will be set and start calibration bit will get cleared after the programmed number of 40mhz clock cycles (programmed in this register) expires
	*/
    uint32 StartCalibrationCounter: 4;        /*## attribute StartCalibrationCounter */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_StartCalibrationCounterBits_t;
    /**
* Nxp_Tef810x_Mod0C_RESET_CALIBRATIONBits_t
* RegisterName: reset_calibration
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: rst_an
	* Description: reset all calibration and lock detect logic, active low
	* 0: Apply reset
	* 1: Normal operation
	*/
    uint32 RstAn: 1;        /*## attribute RstAn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_ResetCalibrationBits_t;
    /**
* Nxp_Tef810x_Mod0C_SNS_LOW_TOP_CONTROLBits_t
* RegisterName: sns_low_top_control
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: sns_low_pd
	* Description: This bit drives the input port Power down bit of supply monitor. 
	* 1 : will disable  Supply monitor
	* 0: Normal operation
	*/
    uint32 SnsLowPd: 1;        /*## attribute SnsLowPd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_STATUS1Bits_t
* RegisterName: calibration_status1
* 
* AddressRange: 0xREAD - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: vco_recalibrate
	* Description: vco recalibration indicator flag
	* 1: Recalibration required
	* 0: Recalibration not required
	*/
    uint32 VcoRecalibrate: 1;        /*## attribute VcoRecalibrate */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: vco_freq_recalib
	* Description: tuning voltage recalibration comparator output
	* 1: Freq recalibration required
	* 0: Freq recalibration not required
	*/
    uint32 VcoFreqRecalib: 1;        /*## attribute VcoFreqRecalib */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vco_level_recalibrate
	* Description: vco level recalibration comparator output
	* 1: Level recalibration required
	* 0: Level recalibration not required
	*/
    uint32 VcoLevelRecalibrate: 1;        /*## attribute VcoLevelRecalibrate */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: vco_level_error
	* Description: vco level detect output (before func safety latch)
	* 1: VCO level error
	* 0: No VCO level error
	*/
    uint32 VcoLevelError: 1;        /*## attribute VcoLevelError */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: vco_level_comp
	* Description: vco amplitude comparator output
	*/
    uint32 VcoLevelComp: 1;        /*## attribute VcoLevelComp */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: vtune_override_out
	* Description: VCO tuning voltage override by calibration controller
	* 1: Override
	* 0: No override
	*/
    uint32 VtuneOverrideOut: 1;        /*## attribute VtuneOverrideOut */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: aac_ictrl_mon
	* Description: vco current control monitor. Updated the reset value based on the wreal model
	*/
    uint32 AacIctrlMon: 6;        /*## attribute AacIctrlMon */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod0C_CalibrationStatus1Bits_t;
    /**
* Nxp_Tef810x_Mod0C_CALIBRATION_STATUS2Bits_t
* RegisterName: calibration_status2
* 
* AddressRange: 0xREAD - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: afc_fsel_out
	* Description: vco coarse frequency tuning
	*/
    uint32 AfcFselOut: 8;        /*## attribute AfcFselOut */
   /**
	* BitsName: afc_m
	* Description: frequency loop actual Mvalue
	*/
    uint32 AfcM: 12;        /*## attribute AfcM */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0C_CalibrationStatus2Bits_t;
    /**
* Nxp_Tef810x_Mod0C_LOCK_STATUSBits_t
* RegisterName: lock_status
* 
* AddressRange: 0xREAD - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: aafc_lock
	* Description: amplitude & frequency loop lock indicator
	* 1: Both freq and Amplitude lock established
	* 0: Error in  the lock
	*/
    uint32 AafcLock: 1;        /*## attribute AafcLock */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: afc_lock
	* Description: frequency loop lock indicator
	* 1: Frequency lock established
	* 0: Frequency lock not established
	*/
    uint32 AfcLock: 1;        /*## attribute AfcLock */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: aac_lock
	* Description: amplitude loop lock indicator
	* 1: Amplitude lock established
	* 0: Amplitude lock not established
	*/
    uint32 AacLock: 1;        /*## attribute AacLock */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ana_lock
	* Description: flag to indicate analog lock time after digital calibration
	* 1: Analog lock in progress
	* 0: Analog lock done
	*/
    uint32 AnaLock: 1;        /*## attribute AnaLock */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod0C_LockStatusBits_t;
    /**
* Nxp_Tef810x_Mod0C_MODULEIDBits_t
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
}Nxp_Tef810x_Mod0C_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod0C_IbiasControlBits_t
* RegisterName: ibias_control
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0xB0186444
*/
typedef struct  {
   /**
	* BitsName: en_iref_bias
	* Description: PLL4G8 internal current source enable
	* 1: Enable
	* 0: Disable
	*/
    uint32 EnIrefBias: 1;        /*## attribute EnIrefBias */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_globalref
	* Description: Selects the reference current source of the bias currents used in the PLL4G8 (100uA).
	* 0: selects the reference current source in the PLL4G8  
	* 1: selects the reference current source in the Global Bias
	*/
    uint32 SelGlobalref: 1;        /*## attribute SelGlobalref */
   /**
	* BitsName: sel_iref_bias
	* Description: PLL4G8 internal current source trim value
	*/
    uint32 SelIrefBias: 5;        /*## attribute SelIrefBias */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_bias_cp_100u
	* Description: PLL4G8 ibias charge pump trim value
	*/
    uint32 CtlBiasCp100U: 5;        /*## attribute CtlBiasCp100U */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_bias_opamp_100u
	* Description: PLL4G8 ibias opamp (inside charge pump) trim value
	*/
    uint32 CtlBiasOpamp100U: 3;        /*## attribute CtlBiasOpamp100U */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_ibias_2G4buf_350u
	* Description: PLL4G8 ibias 2.4GHz output buffer trim value
	*/
    uint32 CtlIbias2G4Buf350U: 3;        /*## attribute CtlIbias2G4Buf350U */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_ibias_2G4_predriv_200u
	* Description: PLL4G8 ibias 2.4GHz pre driver trim value
	*/
    uint32 CtlIbias2G4Predriv200U: 3;        /*## attribute CtlIbias2G4Predriv200U */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_vcom_2G4_predriv
	* Description: PLL4G8 common mode voltage 2.4GHz pre driver trim value
	*/
    uint32 CtlVcom2G4Predriv: 3;        /*## attribute CtlVcom2G4Predriv */
}Nxp_Tef810x_Mod0C_IbiasControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_PllLdoControlBits_t
* RegisterName: pll_ldo_control
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x910F0F0F
*/
typedef struct  {
   /**
	* BitsName: ena_ldo3
	* Description: enable PLL4G8 LDO3 (VCO, peak detector for calibration, first stage divider, 2G4 I/O)
	* 1: Enable LDO3
	* 0: Disable LDO3
	*/
    uint32 EnaLdo3: 1;        /*## attribute EnaLdo3 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ena_ldo2
	* Description: enable PLL4G8 LDO2 (Charge pump, PFD, Low-pass filterm PLL glue logic)
	* 1: Enable LDO2
	* 0: Disable LDO2
	*/
    uint32 EnaLdo2: 1;        /*## attribute EnaLdo2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ena_ldo1
	* Description: enable PLL4G8 LDO1 (Divider)
	* 1: Enable LDO1
	* 0: Disable LDO1
	*/
    uint32 EnaLdo1: 1;        /*## attribute EnaLdo1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: vout_ldo3
	* Description: set output voltage of PLL4G8 LDO3.
	*/
    uint32 VoutLdo3: 5;        /*## attribute VoutLdo3 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: vout_ldo2
	* Description: set output voltage of PLL4G8 LDO2.
	*/
    uint32 VoutLdo2: 5;        /*## attribute VoutLdo2 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: vout_ldo1
	* Description: set output voltage of PLL4G8 LDO1.
	*/
    uint32 VoutLdo1: 5;        /*## attribute VoutLdo1 */
}Nxp_Tef810x_Mod0C_PllLdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LdoControlBits_t
* RegisterName: ldo_control
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x0000000F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_en
	* Description: Master clock LDO enable (buffers, XO functional safety)
	* 1: Enable LDO
	* 0: Disable LDO
	*/
    uint32 LdoEn: 1;        /*## attribute LdoEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_sel_vout
	* Description: set output voltage of Master clock LDO
	* The values to be set will be coming from the calibration procedure ( OTP).
	*/
    uint32 LdoSelVout: 5;        /*## attribute LdoSelVout */
}Nxp_Tef810x_Mod0C_LdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_PfdControlBits_t
* RegisterName: pfd_control
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: pfd_rst
	* Description: overrule reset pfd
	*/
    uint32 PfdRst: 1;        /*## attribute PfdRst */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: pfd_del
	* Description: pfd reset delay control
	*/
    uint32 PfdDel: 2;        /*## attribute PfdDel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: pfd_force_up
	* Description: force pfd up
	* 1: Increase current
	* 0: no effect
	*/
    uint32 PfdForceUp: 1;        /*## attribute PfdForceUp */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: pfd_force_down
	* Description: force pfd down
	* 1: Decrease current
	* 0: no effect
	*/
    uint32 PfdForceDown: 1;        /*## attribute PfdForceDown */
}Nxp_Tef810x_Mod0C_PfdControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CpControlBits_t
* RegisterName: cp_control
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x000001FE
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: cp_ena
	* Description: enable charge pump
	* 1: Enable
	* 0: Disable
	*/
    uint32 CpEna: 1;        /*## attribute CpEna */
   /**
	* BitsName: cp_slice_ena
	* Description: set charge pump current per slice
	* Each bit controls one slice
	*/
    uint32 CpSliceEna: 8;        /*## attribute CpSliceEna */
}Nxp_Tef810x_Mod0C_CpControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_OutputClockSkewControlBits_t
* RegisterName: output_clock_skew_control
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: output_clk_skew
	* Description: fine pitch 600MHz output clock skew 0 to -15/16.T
	*/
    uint32 OutputClkSkew: 4;        /*## attribute OutputClkSkew */
}Nxp_Tef810x_Mod0C_OutputClockSkewControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LoopFilterControlBits_t
* RegisterName: loop_filter_control
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x000010C7
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: lpf_R2
	* Description: LPF set R2 value
	*/
    uint32 LpfR2: 5;        /*## attribute LpfR2 */
   /**
	* BitsName: lpf_C2
	* Description: LPF set C2 value
	*/
    uint32 LpfC2: 4;        /*## attribute LpfC2 */
   /**
	* BitsName: lpf_C1
	* Description: LPF set C1 value
	*/
    uint32 LpfC1: 4;        /*## attribute LpfC1 */
}Nxp_Tef810x_Mod0C_LoopFilterControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_LockControlBits_t
* RegisterName: lock_control
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x000001C4
*/
typedef struct  {
   /**
	* BitsName: lock_det_force_rst
	* Description: lock detector force reset condition
	*/
    uint32 LockDetForceRst: 1;        /*## attribute LockDetForceRst */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: lock_det_enable
	* Description: lock detector enable
	* 1: Enable
	* 0: Disable
	*/
    uint32 LockDetEnable: 1;        /*## attribute LockDetEnable */
   /**
	* BitsName: lock_det_mode_ctrl
	* Description: lock detector mode control (7:6=anl, 4:0=dig)
	*/
    uint32 LockDetModeCtrl: 8;        /*## attribute LockDetModeCtrl */
}Nxp_Tef810x_Mod0C_LockControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_XoLdoControlBits_t
* RegisterName: xo_ldo_control
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x00000F0F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: xo_en_iref_ext
	* Description: external ldo reference current selection input (1.8v). Presently not used bit
	*/
    uint32 XoEnIrefExt: 1;        /*## attribute XoEnIrefExt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: xo_ldo_iref
	* Description: internal ldo reference current selection inputs(1.8v)
	*/
    uint32 XoLdoIref: 5;        /*## attribute XoLdoIref */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: xo_ldo_vout
	* Description: ldo output voltage selection inputs(1.8v)
	* .
	*/
    uint32 XoLdoVout: 5;        /*## attribute XoLdoVout */
}Nxp_Tef810x_Mod0C_XoLdoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_ClockBufferControlBits_t
* RegisterName: clock_buffer_control
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: en_clk_adc_dft_600
	* Description: Enable 600MHz ADC DFT clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkAdcDft600: 1;        /*## attribute EnClkAdcDft600 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_clk_chirp_dft_480_600
	* Description: Enable 480_600MHz Chirp DFT clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkChirpDft480600: 1;        /*## attribute EnClkChirpDft480600 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_clk_adc_40
	* Description: Enable 40MHz ADC clock buffer
	* 0 = disable
	* 1 = enable
	*/
    uint32 EnClkAdc40: 1;        /*## attribute EnClkAdc40 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: en_clk_ssbmod_600
	* Description: Enable 600MHz SSBmod clock buffer 0 = disable
	* 1 = enable
	*/
    uint32 EnClkSsbmod600: 1;        /*## attribute EnClkSsbmod600 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_clk_adc_600
	* Description: Enable 600MHz ADC clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkAdc600: 1;        /*## attribute EnClkAdc600 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: en_clk_ser_480_600
	* Description: Enable 480_600MHz SER clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkSer480600: 1;        /*## attribute EnClkSer480600 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: en_clk_chirp_480
	* Description: Enable 480MHz chirp clock buffer 
	* 0 = disable 
	* 1 = enable
	*/
    uint32 EnClkChirp480: 1;        /*## attribute EnClkChirp480 */
}Nxp_Tef810x_Mod0C_ClockBufferControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_RefClockDelayControlBits_t
* RegisterName: ref_clock_delay_control
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_delay_clk40
	* Description: Select reference clock delay factor N
	* Delay = N. (1/600MHz). N=0?14
	*/
    uint32 SelDelayClk40: 4;        /*## attribute SelDelayClk40 */
}Nxp_Tef810x_Mod0C_RefClockDelayControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationVcoControlBits_t
* RegisterName: calibration_vco_control
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x001A8188
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: vtune_override_in
	* Description: manual VCO tuning voltage override
	* 1: tune voltage manually set
	* 0: Manual control will not affect
	*/
    uint32 VtuneOverrideIn: 1;        /*## attribute VtuneOverrideIn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vco_freq_comp_ena
	* Description: VCO tuning voltage comparator enable
	* 1: Comparator enabled
	* 0: Comparator disabled
	*/
    uint32 VcoFreqCompEna: 1;        /*## attribute VcoFreqCompEna */
   /**
	* BitsName: vtune_override_delay
	* Description: manual VCO tuning voltage override delay
	*/
    uint32 VtuneOverrideDelay: 4;        /*## attribute VtuneOverrideDelay */
   /**
	* BitsName: vtune_recalib_window
	* Description: Vtune voltage comparator window for recalibration
	*/
    uint32 VtuneRecalibWindow: 4;        /*## attribute VtuneRecalibWindow */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: vco_level_comp_ena
	* Description: VCO level comparator enable
	* 1: Comparator enabled
	* 0: Comparator disabled
	*/
    uint32 VcoLevelCompEna: 1;        /*## attribute VcoLevelCompEna */
   /**
	* BitsName: vco_level_recalib_window
	* Description: VCO level comparator window for recalibration
	*/
    uint32 VcoLevelRecalibWindow: 4;        /*## attribute VcoLevelRecalibWindow */
   /**
	* BitsName: vco_level_func_safety
	* Description: VCO level comparator window for functional safety
	*/
    uint32 VcoLevelFuncSafety: 4;        /*## attribute VcoLevelFuncSafety */
}Nxp_Tef810x_Mod0C_CalibrationVcoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationAacControlBits_t
* RegisterName: calibration_aac_control
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x90471400
*/
typedef struct  {
   /**
	* BitsName: aac_enable
	* Description: automatic amplitude control loop enable
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AacEnable: 1;        /*## attribute AacEnable */
   /**
	* BitsName: aac_manual
	* Description: amplitude control loop manual mode
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AacManual: 1;        /*## attribute AacManual */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: aac_ades_in
	* Description: amplitude control desired value
	*/
    uint32 AacAdesIn: 5;        /*## attribute AacAdesIn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: aac_ki
	* Description: amplitude control loop Ki value
	*/
    uint32 AacKi: 3;        /*## attribute AacKi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: aac_lock_ctrl
	* Description: amplitude loop lock control criterium
	*/
    uint32 AacLockCtrl: 3;        /*## attribute AacLockCtrl */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: aac_ictrl_init
	* Description: initial amplitude loop setting (manual mode)
	*/
    uint32 AacIctrlInit: 6;        /*## attribute AacIctrlInit */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: aac_ictrl_min
	* Description: minimum amplitude loop setting
	*/
    uint32 AacIctrlMin: 6;        /*## attribute AacIctrlMin */
}Nxp_Tef810x_Mod0C_CalibrationAacControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationAfcControl1Bits_t
* RegisterName: calibration_afc_control1
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x07805A00
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: afc_mdes
	* Description: frequency loop desired Mvalue
	*/
    uint32 AfcMdes: 12;        /*## attribute AfcMdes */
   /**
	* BitsName: afc_fsel_init
	* Description: initial frequency loop setting (manual mode)
	*/
    uint32 AfcFselInit: 8;        /*## attribute AfcFselInit */
   /**
	* BitsName: afc_fsel_min
	* Description: minimum frequency loop setting
	*/
    uint32 AfcFselMin: 8;        /*## attribute AfcFselMin */
}Nxp_Tef810x_Mod0C_CalibrationAfcControl1Bits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationAfcControl2Bits_t
* RegisterName: calibration_afc_control2
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x01067372
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: afc_enable
	* Description: automatic frequency control loop enable
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 AfcEnable: 1;        /*## attribute AfcEnable */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: afc_manual
	* Description: frequency control loop manual mode
	* 1: Manual mode Enabled
	* 0: Disabled
	*/
    uint32 AfcManual: 1;        /*## attribute AfcManual */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: afc_fref_sel
	* Description: frequency loop fref select
	*/
    uint32 AfcFrefSel: 3;        /*## attribute AfcFrefSel */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: afc_ki
	* Description: initial frequency loop setting (manual mode)
	*/
    uint32 AfcKi: 3;        /*## attribute AfcKi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: afc_step_limit
	* Description: frequency loop integrator step limiter
	*/
    uint32 AfcStepLimit: 3;        /*## attribute AfcStepLimit */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: afc_lock_ctrl2
	* Description: frequency loop lock control criterium 2
	*/
    uint32 AfcLockCtrl2: 3;        /*## attribute AfcLockCtrl2 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: afc_lock_ctrl1
	* Description: frequency loop lock control criterium 1
	*/
    uint32 AfcLockCtrl1: 3;        /*## attribute AfcLockCtrl1 */
}Nxp_Tef810x_Mod0C_CalibrationAfcControl2Bits_t;
    /**
* Nxp_Tef810x_Mod0C_VcoControlBits_t
* RegisterName: vco_control
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000110
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: pon_ls_spi
	* Description: This bit is used for validation purpose only. The pon from Central control is used to control the level shifters and vco enabling. By default the xtal oscillator circuit pon is enabled
	* 1: Enabled (permenant)
	* 0: No effect
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vco_en
	* Description: enable vco (internally this delayed by pon_counter cycles)
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 VcoEn: 1;        /*## attribute VcoEn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: vco_Rset
	* Description: vco current control resistor value (internally this delayed by pon_counter cycles)
	*/
    uint32 VcoRset: 5;        /*## attribute VcoRset */
}Nxp_Tef810x_Mod0C_VcoControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_StartCalibrationCounterBits_t
* RegisterName: start_calibration_counter
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: start_calibration_counter
	* Description: Once this register is programmed (non-zero), start calibration bit towards analog will be set and start calibration bit will get cleared after the programmed number of 40mhz clock cycles (programmed in this register) expires
	*/
    uint32 StartCalibrationCounter: 4;        /*## attribute StartCalibrationCounter */
}Nxp_Tef810x_Mod0C_StartCalibrationCounterBits_t;
    /**
* Nxp_Tef810x_Mod0C_ResetCalibrationBits_t
* RegisterName: reset_calibration
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: rst_an
	* Description: reset all calibration and lock detect logic, active low
	* 0: Apply reset
	* 1: Normal operation
	*/
    uint32 RstAn: 1;        /*## attribute RstAn */
}Nxp_Tef810x_Mod0C_ResetCalibrationBits_t;
    /**
* Nxp_Tef810x_Mod0C_SnsLowTopControlBits_t
* RegisterName: sns_low_top_control
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: sns_low_pd
	* Description: This bit drives the input port Power down bit of supply monitor. 
	* 1 : will disable  Supply monitor
	* 0: Normal operation
	*/
    uint32 SnsLowPd: 1;        /*## attribute SnsLowPd */
}Nxp_Tef810x_Mod0C_SnsLowTopControlBits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationStatus1Bits_t
* RegisterName: calibration_status1
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x3E110101
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: aac_ictrl_mon
	* Description: vco current control monitor. Updated the reset value based on the wreal model
	*/
    uint32 AacIctrlMon: 6;        /*## attribute AacIctrlMon */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vtune_override_out
	* Description: VCO tuning voltage override by calibration controller
	* 1: Override
	* 0: No override
	*/
    uint32 VtuneOverrideOut: 1;        /*## attribute VtuneOverrideOut */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: vco_level_comp
	* Description: vco amplitude comparator output
	*/
    uint32 VcoLevelComp: 1;        /*## attribute VcoLevelComp */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: vco_level_error
	* Description: vco level detect output (before func safety latch)
	* 1: VCO level error
	* 0: No VCO level error
	*/
    uint32 VcoLevelError: 1;        /*## attribute VcoLevelError */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: vco_level_recalibrate
	* Description: vco level recalibration comparator output
	* 1: Level recalibration required
	* 0: Level recalibration not required
	*/
    uint32 VcoLevelRecalibrate: 1;        /*## attribute VcoLevelRecalibrate */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: vco_freq_recalib
	* Description: tuning voltage recalibration comparator output
	* 1: Freq recalibration required
	* 0: Freq recalibration not required
	*/
    uint32 VcoFreqRecalib: 1;        /*## attribute VcoFreqRecalib */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: vco_recalibrate
	* Description: vco recalibration indicator flag
	* 1: Recalibration required
	* 0: Recalibration not required
	*/
    uint32 VcoRecalibrate: 1;        /*## attribute VcoRecalibrate */
}Nxp_Tef810x_Mod0C_CalibrationStatus1Bits_t;
    /**
* Nxp_Tef810x_Mod0C_CalibrationStatus2Bits_t
* RegisterName: calibration_status2
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x000000FF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: afc_m
	* Description: frequency loop actual Mvalue
	*/
    uint32 AfcM: 12;        /*## attribute AfcM */
   /**
	* BitsName: afc_fsel_out
	* Description: vco coarse frequency tuning
	*/
    uint32 AfcFselOut: 8;        /*## attribute AfcFselOut */
}Nxp_Tef810x_Mod0C_CalibrationStatus2Bits_t;
    /**
* Nxp_Tef810x_Mod0C_LockStatusBits_t
* RegisterName: lock_status
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ana_lock
	* Description: flag to indicate analog lock time after digital calibration
	* 1: Analog lock in progress
	* 0: Analog lock done
	*/
    uint32 AnaLock: 1;        /*## attribute AnaLock */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: aac_lock
	* Description: amplitude loop lock indicator
	* 1: Amplitude lock established
	* 0: Amplitude lock not established
	*/
    uint32 AacLock: 1;        /*## attribute AacLock */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: afc_lock
	* Description: frequency loop lock indicator
	* 1: Frequency lock established
	* 0: Frequency lock not established
	*/
    uint32 AfcLock: 1;        /*## attribute AfcLock */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: aafc_lock
	* Description: amplitude & frequency loop lock indicator
	* 1: Both freq and Amplitude lock established
	* 0: Error in  the lock
	*/
    uint32 AafcLock: 1;        /*## attribute AafcLock */
}Nxp_Tef810x_Mod0C_LockStatusBits_t;
    /**
* Nxp_Tef810x_Mod0C_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x000C2201
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
}Nxp_Tef810x_Mod0C_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod0C_IbiasControlUnion_t
* Nxp_Tef810x_Mod0C_IbiasControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_IbiasControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_IbiasControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_PllLdoControlUnion_t
* Nxp_Tef810x_Mod0C_PllLdoControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_PllLdoControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_PllLdoControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_LdoControlUnion_t
* Nxp_Tef810x_Mod0C_LdoControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_LdoControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_LdoControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_PfdControlUnion_t
* Nxp_Tef810x_Mod0C_PfdControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_PfdControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_PfdControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_CpControlUnion_t
* Nxp_Tef810x_Mod0C_CpControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CpControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CpControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_OutputClockSkewControlUnion_t
* Nxp_Tef810x_Mod0C_OutputClockSkewControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_OutputClockSkewControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_OutputClockSkewControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_LoopFilterControlUnion_t
* Nxp_Tef810x_Mod0C_LoopFilterControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_LoopFilterControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_LoopFilterControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_LockControlUnion_t
* Nxp_Tef810x_Mod0C_LockControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_LockControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_LockControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_XoLdoControlUnion_t
* Nxp_Tef810x_Mod0C_XoLdoControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_XoLdoControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_XoLdoControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_ClockBufferControlUnion_t
* Nxp_Tef810x_Mod0C_ClockBufferControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_ClockBufferControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_ClockBufferControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_RefClockDelayControlUnion_t
* Nxp_Tef810x_Mod0C_RefClockDelayControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_RefClockDelayControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_RefClockDelayControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t
* Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationVcoControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationAacControlUnion_t
* Nxp_Tef810x_Mod0C_CalibrationAacControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationAacControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationAacControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationAfcControl1Union_t
* Nxp_Tef810x_Mod0C_CalibrationAfcControl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationAfcControl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationAfcControl1Union_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationAfcControl2Union_t
* Nxp_Tef810x_Mod0C_CalibrationAfcControl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationAfcControl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationAfcControl2Union_t;
/**
* Nxp_Tef810x_Mod0C_VcoControlUnion_t
* Nxp_Tef810x_Mod0C_VcoControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_VcoControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_VcoControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t
* Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_StartCalibrationCounterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t;
/**
* Nxp_Tef810x_Mod0C_ResetCalibrationUnion_t
* Nxp_Tef810x_Mod0C_ResetCalibrationUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_ResetCalibrationBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_ResetCalibrationUnion_t;
/**
* Nxp_Tef810x_Mod0C_SnsLowTopControlUnion_t
* Nxp_Tef810x_Mod0C_SnsLowTopControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_SnsLowTopControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_SnsLowTopControlUnion_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationStatus1Union_t
* Nxp_Tef810x_Mod0C_CalibrationStatus1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationStatus1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationStatus1Union_t;
/**
* Nxp_Tef810x_Mod0C_CalibrationStatus2Union_t
* Nxp_Tef810x_Mod0C_CalibrationStatus2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_CalibrationStatus2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_CalibrationStatus2Union_t;
/**
* Nxp_Tef810x_Mod0C_LockStatusUnion_t
* Nxp_Tef810x_Mod0C_LockStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_LockStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_LockStatusUnion_t;
/**
* Nxp_Tef810x_Mod0C_ModuleidUnion_t
* Nxp_Tef810x_Mod0C_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0C_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0C_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod0C_MasterClockRegister_t
 * Nxp_Tef810x_Mod0C_MasterClockRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: ibias_control
    * AddressOffset: 0x000
    * ResetValue: 0xB0186444
    * Description: Bias control settings
    */
    Nxp_Tef810x_Mod0C_IbiasControlUnion_t IbiasControl_ust;        /*## attribute IbiasControl_ust */
  /**
    * RegisterName: pll_ldo_control
    * AddressOffset: 0x004
    * ResetValue: 0x910F0F0F
    * Description: Ldo control settings for the PLL.
	* All LDO's to eb enabed for the PLL to work.
    */
    Nxp_Tef810x_Mod0C_PllLdoControlUnion_t PllLdoControl_ust;        /*## attribute PllLdoControl_ust */
  /**
    * RegisterName: ldo_control
    * AddressOffset: 0x008
    * ResetValue: 0x0000000F
    * Description: Master clock local Ldo control settings
    */
    Nxp_Tef810x_Mod0C_LdoControlUnion_t LdoControl_ust;        /*## attribute LdoControl_ust */
  /**
    * RegisterName: pfd_control
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: Phase Frequency Detector control settings for 4.8GHz PLL
	* .
    */
    Nxp_Tef810x_Mod0C_PfdControlUnion_t PfdControl_ust;        /*## attribute PfdControl_ust */
  /**
    * RegisterName: cp_control
    * AddressOffset: 0x010
    * ResetValue: 0x000001FE
    * Description: Charge pump control settings
	* .
    */
    Nxp_Tef810x_Mod0C_CpControlUnion_t CpControl_ust;        /*## attribute CpControl_ust */
  /**
    * RegisterName: output_clock_skew_control
    * AddressOffset: 0x014
    * ResetValue: 0x00000000
    * Description: In applications where two Dolphin IC?s have to work together, the phases of the 600MHz
	* clocks in both ICs have to be aligned within a tight tolerance. In this case one of the ICs
	* works as master, the other one as slave. Only the master will use the xtal oscillator, while
	* the slave receives its 40MHz reference clock from the master.
	* Obviously the slave reference clock will always be delayed by a few nanoseconds with
	* respect to the master reference clock. To compensate for this delay, the PLL has two
	* provisions: fine pitch output clock skew and ADC reference clock re-clocking
	* 
	* Fine pitch output clock skew :
	* 
	* The PLL feedback divide chain implements two cascaded dividers; a divide-by-8 and a
	* divide-by-15 circuit. The output signal of this divide-by-8 circuit is 600MHz.
	* This divider is synchronized to a second divide-by-8 circuit, which delivers the 600MHz
	* output clock, for clocking the Dolphin ADC. However the exact phase relation between
	* these two divide-by-8 circuits is made adjustable. The 600MHz output of the first divider
	* can be delayed from 0 to15/16.T600M, in steps of 1/16.T600M (approx. 104ps nom.).
	* Since the first divide-by-8 is part of the feedback divider chain, the phase relation between
	* its 600MHz output clock and the 40MHz feedback clock is automatically fixed; their rising
	* edges will always coincide. When, as described, the 600MHz clock in the feedback path is
	* delayed for a part of its period, the 600MHz output clock for the ADC becomes advanced
	* with respect to the 40MHz input clock of the PLL
    */
    Nxp_Tef810x_Mod0C_OutputClockSkewControlUnion_t OutputClockSkewControl_ust;        /*## attribute OutputClockSkewControl_ust */
  /**
    * RegisterName: loop_filter_control
    * AddressOffset: 0x018
    * ResetValue: 0x000010C7
    * Description: Loop filter control settings.
	* .
    */
    Nxp_Tef810x_Mod0C_LoopFilterControlUnion_t LoopFilterControl_ust;        /*## attribute LoopFilterControl_ust */
  /**
    * RegisterName: lock_control
    * AddressOffset: 0x01C
    * ResetValue: 0x000001C4
    * Description: PLL un Lock detector control settings. This is a functional safety control register
    */
    Nxp_Tef810x_Mod0C_LockControlUnion_t LockControl_ust;        /*## attribute LockControl_ust */
  /**
    * RegisterName: xo_ldo_control
    * AddressOffset: 0x020
    * ResetValue: 0x00000F0F
    * Description: Ldo control settings for the oscillator
    */
    Nxp_Tef810x_Mod0C_XoLdoControlUnion_t XoLdoControl_ust;        /*## attribute XoLdoControl_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x024
    * ResetValue: 0x00010012
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x028
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: clock_buffer_control
    * AddressOffset: 0x02C
    * ResetValue: 0x00000000
    * Description: Clock output buffer control
    */
    Nxp_Tef810x_Mod0C_ClockBufferControlUnion_t ClockBufferControl_ust;        /*## attribute ClockBufferControl_ust */
  /**
    * RegisterName: ref_clock_delay_control
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: In applications where two Dolphin IC?s have to work together, the phases of the 600MHz
	* clocks in both ICs have to be aligned within a tight tolerance. In this case one of the ICs
	* works as master, the other one as slave. Only the master will use the xtal oscillator, while
	* the slave receives its 40MHz reference clock from the master.
	* Obviously the slave reference clock will always be delayed by a few nanoseconds with
	* respect to the master reference clock. To compensate for this delay, the PLL has two
	* provisions: fine pitch output clock skew and ADC reference clock re-clocking.
	* 
	* ADC reference clock re-clocking:
	* 
	* PLL reference clock delay between master and slave IC can be more
	* than one period of the 600MHz clock. Obviously we can?t advance the 600MHz clock for
	* more than a single period w.r.t. the 40MHz input clock. However the
	* 40MHz clock that goes to the ADC can be manipulated, as a reference for the sampling time point. By shifting
	* this ADC reference clock over a number of periods of the 600MHz clock, it is possible to
	* compensate for any amount of delay (as long as it is less than the 40MHz clock period).
    */
    Nxp_Tef810x_Mod0C_RefClockDelayControlUnion_t RefClockDelayControl_ust;        /*## attribute RefClockDelayControl_ust */
  /**
    * RegisterName: calibration_vco_control
    * AddressOffset: 0x034
    * ResetValue: 0x001A8188
    * Description: VCO calibration settings
	* .
    */
    Nxp_Tef810x_Mod0C_CalibrationVcoControlUnion_t CalibrationVcoControl_ust;        /*## attribute CalibrationVcoControl_ust */
  /**
    * RegisterName: calibration_aac_control
    * AddressOffset: 0x038
    * ResetValue: 0x90471400
    * Description: Automatic amplitude calibration settings
    */
    Nxp_Tef810x_Mod0C_CalibrationAacControlUnion_t CalibrationAacControl_ust;        /*## attribute CalibrationAacControl_ust */
  /**
    * RegisterName: calibration_afc_control1
    * AddressOffset: 0x03C
    * ResetValue: 0x07805A00
    * Description: Automatic frequency calibration settings1
    */
    Nxp_Tef810x_Mod0C_CalibrationAfcControl1Union_t CalibrationAfcControl1_ust;        /*## attribute CalibrationAfcControl1_ust */
  /**
    * RegisterName: calibration_afc_control2
    * AddressOffset: 0x040
    * ResetValue: 0x01067372
    * Description: Automatic frequency calibration settings2
    */
    Nxp_Tef810x_Mod0C_CalibrationAfcControl2Union_t CalibrationAfcControl2_ust;        /*## attribute CalibrationAfcControl2_ust */
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x048
    * ResetValue: 0x0000002B
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x04C
    * ResetValue: 0x00000003
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: vco_control
    * AddressOffset: 0x054
    * ResetValue: 0x00000110
    * Description: VCO control settings
    */
    Nxp_Tef810x_Mod0C_VcoControlUnion_t VcoControl_ust;        /*## attribute VcoControl_ust */
  /**
    * RegisterName: start_calibration_counter
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: The register keep the start calibration signal to '1' till the programmed value becomes 0
    */
    Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t StartCalibrationCounter_ust;        /*## attribute StartCalibrationCounter_ust */
  /**
    * RegisterName: reset_calibration
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: Calibration logic is reset
    */
    Nxp_Tef810x_Mod0C_ResetCalibrationUnion_t ResetCalibration_ust;        /*## attribute ResetCalibration_ust */
  /**
    * RegisterName: sns_low_top_control
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: supply monitor  control bits
    */
    Nxp_Tef810x_Mod0C_SnsLowTopControlUnion_t SnsLowTopControl_ust;        /*## attribute SnsLowTopControl_ust */
  /**
    * RegisterName: calibration_status1
    * AddressOffset: 0x064
    * ResetValue: 0x3E110101
    * Description: Calibration status1
    */
    Nxp_Tef810x_Mod0C_CalibrationStatus1Union_t CalibrationStatus1_ust;        /*## attribute CalibrationStatus1_ust */
  /**
    * RegisterName: calibration_status2
    * AddressOffset: 0x068
    * ResetValue: 0x000000FF
    * Description: Calibration status2
    */
    Nxp_Tef810x_Mod0C_CalibrationStatus2Union_t CalibrationStatus2_ust;        /*## attribute CalibrationStatus2_ust */
  /**
    * RegisterName: lock_status
    * AddressOffset: 0x06C
    * ResetValue: 0x00000000
    * Description: Lock status bits
    */
    Nxp_Tef810x_Mod0C_LockStatusUnion_t LockStatus_ust;        /*## attribute LockStatus_ust */
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x070
    * ResetValue: 0x0000001F
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x074
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x078
    * ResetValue: 0x0000001F
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x07C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;
  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;
  /**
    * RegisterName: Reserved10
    * AddressOffset: 0x098
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved10;
  /**
    * RegisterName: Reserved11
    * AddressOffset: 0x09C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved11;
  /**
    * RegisterName: Reserved12
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved12;

    uint32 gap01_au32[980];        /* gap 1 in register space */  /**
    * RegisterName: Reserved13
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved13;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x000C2201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod0C_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod0C_MasterClockRegister_t;

#endif
