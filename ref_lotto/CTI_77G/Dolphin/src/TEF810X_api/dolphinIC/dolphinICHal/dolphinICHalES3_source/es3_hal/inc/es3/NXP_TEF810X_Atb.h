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
* @NXP_TEF810X_Atb.h
*/
#ifndef NXP_TEF810X_ATB_H
#define NXP_TEF810X_ATB_H
#include "Std_Types.h"

#define ATB_MODULE_ADDRESS 0x16
/**
*NXP_TEF810X_MOD16_ATB_CONTROL_REGISTER_U16
* RegisterName: MOD16_atb_control_register
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB_CONTROL_REGISTER_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD16_ATB_DATA_REGISTER_U16
* RegisterName: MOD16_atb_data_register
* AccessMode: READ
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB_DATA_REGISTER_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD16_ATB1_CONFIG_REGISTER_U16
* RegisterName: MOD16_atb1_config_register
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB1_CONFIG_REGISTER_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD16_ATB2_CONFIG_REGISTER_U16
* RegisterName: MOD16_atb2_config_register
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB2_CONFIG_REGISTER_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD16_LDO_ATB_CONTROL_U16
* RegisterName: MOD16_ldo_atb_control
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_LDO_ATB_CONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD16_ATB1_U16
* RegisterName: MOD16_atb1
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB1_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD16_ATB2_U16
* RegisterName: MOD16_atb2
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ATB2_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD16_ATB_DELAY_TIMER_U16
* RegisterName: MOD16_atb_delay_timer
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00001F1F
*/
#define NXP_TEF810X_MOD16_ATB_DELAY_TIMER_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD16_ADC_BUF1_CONTROL_REG_U16
* RegisterName: MOD16_adc_buf1_control_reg
* AccessMode: READWRITE
* AddressRange: 0x0100 - 0x0104
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ADC_BUF1_CONTROL_REG_U16 (uint16)0x0100
/**
*NXP_TEF810X_MOD16_ADC_BUF2_CONTROL_REG_U16
* RegisterName: MOD16_adc_buf2_control_reg
* AccessMode: READWRITE
* AddressRange: 0x0104 - 0x0108
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD16_ADC_BUF2_CONTROL_REG_U16 (uint16)0x0104
/**
*NXP_TEF810X_MOD16_MODULEID_U16
* RegisterName: MOD16_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00161101
*/
#define NXP_TEF810X_MOD16_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod16_ATB_CONTROL_REGISTERBits_t
* RegisterName: atb_control_register
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: cntr_preload
	* Description: Configure the trigger within repeated read cycle in case of clocked mode (number of 25ns clocks); 
	* n: 0 ? 15 (dec); 
	* default = 4
	*/
    uint32 CntrPreload: 6;        /*## attribute CntrPreload */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: en_adc_clk
	* Description: Enables ADC clocking by SPI read operation
	* 0 -> trigger forced low 
	* 1 -> trigger controlled by 1st read bit clock
	*/
    uint32 EnAdcClk: 1;        /*## attribute EnAdcClk */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: pon_ls
	* Description: Indicates the power on level shifters (required to control the Analogue IP)
	*  0 -> off
	*  1 -> on
	*  This can be alternatively switched on from Central COntroller also
	*/
    uint32 PonLs: 1;        /*## attribute PonLs */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: adc1_mode
	* Description: This bit selects the mode of ADC1 
	* 0 -> clock-less mode of triggering 
	* 1 -> clocked mode of triggering
	*/
    uint32 Adc1Mode: 1;        /*## attribute Adc1Mode */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: adc1_fs
	* Description: This bit is used as ADC1 single trigger bit (fs) in clockless mode. 
	* 1 -> ADC1 is triggered
	* 0 -> ADC1 is not triggered
	*/
    uint32 Adc1Fs: 1;        /*## attribute Adc1Fs */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: adc2_mode
	* Description: This bit selects the mode of ADC2 
	* 0 -> clock-less mode of triggering 
	* 1 -> clocked mode of triggering
	*/
    uint32 Adc2Mode: 1;        /*## attribute Adc2Mode */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: adc2_fs
	* Description: This bit is used as ADC2 single trigger bit (fs) in clockless mode. 
	* 1 -> ADC2 is triggered
	* 0 -> ADC2 is not triggered
	* Leave as reset if not needed explicitly.
	*/
    uint32 Adc2Fs: 1;        /*## attribute Adc2Fs */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod16_AtbControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_ATB_DATA_REGISTERBits_t
* RegisterName: atb_data_register
* 
* AddressRange: 0xREAD - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: adc1_data
	* Description: BISTADC1 data (10 bit), conversion result (data) is the latched data when adc1_ready is 1. Refer to the user manual to calculate raw data to voltage by use of OTP content
	*/
    uint32 Adc1Data: 10;        /*## attribute Adc1Data */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: adc1_ready
	* Description: Ready bit of BISTADC1 (1=ready, resets with next trigger)
	*/
    uint32 Adc1Ready: 1;        /*## attribute Adc1Ready */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: adc2_data
	* Description: BISTADC2 data (10 bit), conversion result (data) is the latched data when adc2_ready is 1. Refer to the user manual to calculate raw data to voltage by use of OTP content
	*/
    uint32 Adc2Data: 10;        /*## attribute Adc2Data */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: adc2_ready
	* Description: Ready bit of BISTADC2 (1=ready, resets with next trigger)
	*/
    uint32 Adc2Ready: 1;        /*## attribute Adc2Ready */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod16_AtbDataRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_ATB1_CONFIG_REGISTERBits_t
* RegisterName: atb1_config_register
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: set_atb1_rtrim_rn
	* Description: Resistor calibration: setting of RCM (target = 5.24k;
	* MSB not used; straight binary coded: 3.5k + n * 109)
	*/
    uint32 SetAtb1RtrimRn: 6;        /*## attribute SetAtb1RtrimRn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: en_atb1_rtrim_n
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	* (not a typo, same functionality as ?en_atb1_rtrim_rn_gnd? but not the same switch!)
	*/
    uint32 EnAtb1RtrimN: 1;        /*## attribute EnAtb1RtrimN */
   /**
	* BitsName: set_atb1_rtrim_rp
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb1RtrimRp: 6;        /*## attribute SetAtb1RtrimRp */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb1_rtrim_p
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to DC_int_ATB1_0
	*/
    uint32 EnAtb1RtrimP: 1;        /*## attribute EnAtb1RtrimP */
   /**
	* BitsName: set_atb1_rtrim
	* Description: Resistor calibration: setting of Rtrim (target = 2.06k;
	* MSB not used; straight binary coded: 1.37k + n * 42)
	*/
    uint32 SetAtb1Rtrim: 6;        /*## attribute SetAtb1Rtrim */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb1_rtrim_rn_gnd
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	*/
    uint32 EnAtb1RtrimRnGnd: 1;        /*## attribute EnAtb1RtrimRnGnd */
   /**
	* BitsName: en_atb1_rtrim_rp_gnd
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to GND
	*/
    uint32 EnAtb1RtrimRpGnd: 1;        /*## attribute EnAtb1RtrimRpGnd */
   /**
	* BitsName: en_atb1_adc_n_gnd
	* Description: Connects BISTADC1 n-input to GND
	*/
    uint32 EnAtb1AdcNGnd: 1;        /*## attribute EnAtb1AdcNGnd */
   /**
	* BitsName: en_atb1_adc_p_gnd
	* Description: Connects BISTADC1 p-input to GND
	*/
    uint32 EnAtb1AdcPGnd: 1;        /*## attribute EnAtb1AdcPGnd */
   /**
	* BitsName: en_atb1_read_rtrim_n
	* Description: Connects DC_int_ATB1_180 to DC_int_ATB2_180
	*/
    uint32 EnAtb1ReadRtrimN: 1;        /*## attribute EnAtb1ReadRtrimN */
   /**
	* BitsName: en_atb1_read_rtrim_p
	* Description: Connects DC_int_ATB1_0 to DC_int_ATB2_0
	*/
    uint32 EnAtb1ReadRtrimP: 1;        /*## attribute EnAtb1ReadRtrimP */
   /**
	* BitsName: en_atb1_adc_swn
	* Description: Connects BISTADC1 n-input to DC_int_ATB1_180
	*/
    uint32 EnAtb1AdcSwn: 1;        /*## attribute EnAtb1AdcSwn */
   /**
	* BitsName: en_atb1_adc_swp
	* Description: Connects BISTADC1 p-input to DC_int_ATB1_0
	*/
    uint32 EnAtb1AdcSwp: 1;        /*## attribute EnAtb1AdcSwp */
}Nxp_Tef810x_Mod16_Atb1ConfigRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_ATB2_CONFIG_REGISTERBits_t
* RegisterName: atb2_config_register
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: set_atb2_rtrim_rn
	* Description: Resistor calibration: setting of RCM (target = 5.24k;
	* MSB not used; straight binary coded: 3.5k + n * 109)
	*/
    uint32 SetAtb2RtrimRn: 6;        /*## attribute SetAtb2RtrimRn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: en_atb2_rtrim_n
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	* (not a typo, same as ?en_atb1_rtrim_rn_gnd? but not the same switch!)
	*/
    uint32 EnAtb2RtrimN: 1;        /*## attribute EnAtb2RtrimN */
   /**
	* BitsName: set_atb2_rtrim_rp
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb2RtrimRp: 6;        /*## attribute SetAtb2RtrimRp */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb2_rtrim_p
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to DC_int_ATB2_0
	*/
    uint32 EnAtb2RtrimP: 1;        /*## attribute EnAtb2RtrimP */
   /**
	* BitsName: set_atb2_rtrim
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb2Rtrim: 6;        /*## attribute SetAtb2Rtrim */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb2_rtrim_rn_gnd
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	*/
    uint32 EnAtb2RtrimRnGnd: 1;        /*## attribute EnAtb2RtrimRnGnd */
   /**
	* BitsName: en_atb2_rtrim_rp_gnd
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to GND
	*/
    uint32 EnAtb2RtrimRpGnd: 1;        /*## attribute EnAtb2RtrimRpGnd */
   /**
	* BitsName: en_atb2_adc_n_gnd
	* Description: Connects BISTADC2 n-input to GND
	*/
    uint32 EnAtb2AdcNGnd: 1;        /*## attribute EnAtb2AdcNGnd */
   /**
	* BitsName: en_atb2_adc_p_gnd
	* Description: Connects BISTADC2 p-input to GND
	*/
    uint32 EnAtb2AdcPGnd: 1;        /*## attribute EnAtb2AdcPGnd */
   /**
	* BitsName: en_atb2_read_rtrim_n
	* Description: Connects DC_int_ATB2_180 to DC_int_ATB1_180
	*/
    uint32 EnAtb2ReadRtrimN: 1;        /*## attribute EnAtb2ReadRtrimN */
   /**
	* BitsName: en_atb2_read_rtrim_p
	* Description: Connects DC_int_ATB2_0 to DC_int_ATB1_0
	*/
    uint32 EnAtb2ReadRtrimP: 1;        /*## attribute EnAtb2ReadRtrimP */
   /**
	* BitsName: en_atb2_adc_swn
	* Description: Connects BISTADC2 n-input to DC_int_ATB2_180
	*/
    uint32 EnAtb2AdcSwn: 1;        /*## attribute EnAtb2AdcSwn */
   /**
	* BitsName: en_atb2_adc_swp
	* Description: Connects BISTADC2 p-input to DC_int_ATB2_0
	*/
    uint32 EnAtb2AdcSwp: 1;        /*## attribute EnAtb2AdcSwp */
}Nxp_Tef810x_Mod16_Atb2ConfigRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_LDO_ATB_CONTROLBits_t
* RegisterName: ldo_atb_control
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: ldo_en_atb
	* Description: enable local LDO (this LDO supplies BISTADCs and their buffers)
	*/
    uint32 LdoEnAtb: 1;        /*## attribute LdoEnAtb */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_atb
	* Description: set output voltage of local LDO
	*/
    uint32 LdoSelVoutAtb: 5;        /*## attribute LdoSelVoutAtb */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod16_LdoAtbControlBits_t;
    /**
* Nxp_Tef810x_Mod16_ATB1Bits_t
* RegisterName: atb1
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: atb1_set
	* Description: Select signal to be measured:
	* 
	* atb1_vdda_1v8=8'h1
	* atb1_vdda_1v1=8'h2
	* atb1_vddd_safety_1v1=8'h3
	* atb1_iref_bg=8'h4
	* atb1_iref_bgr_1=8'h5
	* atb1_iref_bgr_2=8'h6
	* atb1_iref_local_ldo=8'h7
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
}Nxp_Tef810x_Mod16_Atb1Bits_t;
    /**
* Nxp_Tef810x_Mod16_ATB2Bits_t
* RegisterName: atb2
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: atb2_set
	* Description: Select signal to be measured:
	* 
	* atb2_vdda_1v8=8'h1
	* atb2_vdda_1v1=8'h2
	* atb2_vddd_safety_1v1=8'h3
	* atb2_iref_bg=8'h4
	* atb2_iref_bgr_1=8'h5
	* atb2_iref_bgr_2=8'h6
	* atb2_iref_local_ldo=8'h7
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
}Nxp_Tef810x_Mod16_Atb2Bits_t;
    /**
* Nxp_Tef810x_Mod16_ATB_DELAY_TIMERBits_t
* RegisterName: atb_delay_timer
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
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
}Nxp_Tef810x_Mod16_AtbDelayTimerBits_t;
    /**
* Nxp_Tef810x_Mod16_ADC_BUF1_CONTROL_REGBits_t
* RegisterName: adc_buf1_control_reg
* 
* AddressRange: 0xREADWRITE - 0x100
* ResetValue: 0x00000104
*/
typedef struct  {
   /**
	* BitsName: en_adcbuf1
	* Description: Enables the BISTADC1 buffer
	*/
    uint32 EnAdcbuf1: 1;        /*## attribute EnAdcbuf1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_gain_adcbuf1
	* Description: Gain control:
	* MSB not used; [0] = 0: gain = 0.5; [0] = 1: gain = 1
	*/
    uint32 SelGainAdcbuf1: 2;        /*## attribute SelGainAdcbuf1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: pol_adcbuf1
	* Description: Toggles polarity of buffer input
	*/
    uint32 PolAdcbuf1: 1;        /*## attribute PolAdcbuf1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod16_AdcBuf1ControlRegBits_t;
    /**
* Nxp_Tef810x_Mod16_ADC_BUF2_CONTROL_REGBits_t
* RegisterName: adc_buf2_control_reg
* 
* AddressRange: 0xREADWRITE - 0x104
* ResetValue: 0x00000108
*/
typedef struct  {
   /**
	* BitsName: en_adcbuf2
	* Description: Enables the BISTADC2 buffer
	*/
    uint32 EnAdcbuf2: 1;        /*## attribute EnAdcbuf2 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: sel_gain_adcbuf2
	* Description: Gain control:
	* MSB not used; [0] = 0: gain = 0.5; [0] = 1: gain = 1
	*/
    uint32 SelGainAdcbuf2: 2;        /*## attribute SelGainAdcbuf2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: pol_adcbuf2
	* Description: Toggles polarity of buffer input
	*/
    uint32 PolAdcbuf2: 1;        /*## attribute PolAdcbuf2 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod16_AdcBuf2ControlRegBits_t;
    /**
* Nxp_Tef810x_Mod16_MODULEIDBits_t
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
}Nxp_Tef810x_Mod16_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod16_AtbControlRegisterBits_t
* RegisterName: atb_control_register
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: adc2_fs
	* Description: This bit is used as ADC2 single trigger bit (fs) in clockless mode. 
	* 1 -> ADC2 is triggered
	* 0 -> ADC2 is not triggered
	* Leave as reset if not needed explicitly.
	*/
    uint32 Adc2Fs: 1;        /*## attribute Adc2Fs */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: adc2_mode
	* Description: This bit selects the mode of ADC2 
	* 0 -> clock-less mode of triggering 
	* 1 -> clocked mode of triggering
	*/
    uint32 Adc2Mode: 1;        /*## attribute Adc2Mode */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: adc1_fs
	* Description: This bit is used as ADC1 single trigger bit (fs) in clockless mode. 
	* 1 -> ADC1 is triggered
	* 0 -> ADC1 is not triggered
	*/
    uint32 Adc1Fs: 1;        /*## attribute Adc1Fs */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: adc1_mode
	* Description: This bit selects the mode of ADC1 
	* 0 -> clock-less mode of triggering 
	* 1 -> clocked mode of triggering
	*/
    uint32 Adc1Mode: 1;        /*## attribute Adc1Mode */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: pon_ls
	* Description: Indicates the power on level shifters (required to control the Analogue IP)
	*  0 -> off
	*  1 -> on
	*  This can be alternatively switched on from Central COntroller also
	*/
    uint32 PonLs: 1;        /*## attribute PonLs */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: en_adc_clk
	* Description: Enables ADC clocking by SPI read operation
	* 0 -> trigger forced low 
	* 1 -> trigger controlled by 1st read bit clock
	*/
    uint32 EnAdcClk: 1;        /*## attribute EnAdcClk */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
   /**
	* BitsName: cntr_preload
	* Description: Configure the trigger within repeated read cycle in case of clocked mode (number of 25ns clocks); 
	* n: 0 ? 15 (dec); 
	* default = 4
	*/
    uint32 CntrPreload: 6;        /*## attribute CntrPreload */
}Nxp_Tef810x_Mod16_AtbControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_AtbDataRegisterBits_t
* RegisterName: atb_data_register
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: adc2_ready
	* Description: Ready bit of BISTADC2 (1=ready, resets with next trigger)
	*/
    uint32 Adc2Ready: 1;        /*## attribute Adc2Ready */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: adc2_data
	* Description: BISTADC2 data (10 bit), conversion result (data) is the latched data when adc2_ready is 1. Refer to the user manual to calculate raw data to voltage by use of OTP content
	*/
    uint32 Adc2Data: 10;        /*## attribute Adc2Data */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: adc1_ready
	* Description: Ready bit of BISTADC1 (1=ready, resets with next trigger)
	*/
    uint32 Adc1Ready: 1;        /*## attribute Adc1Ready */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: adc1_data
	* Description: BISTADC1 data (10 bit), conversion result (data) is the latched data when adc1_ready is 1. Refer to the user manual to calculate raw data to voltage by use of OTP content
	*/
    uint32 Adc1Data: 10;        /*## attribute Adc1Data */
}Nxp_Tef810x_Mod16_AtbDataRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_Atb1ConfigRegisterBits_t
* RegisterName: atb1_config_register
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: en_atb1_adc_swp
	* Description: Connects BISTADC1 p-input to DC_int_ATB1_0
	*/
    uint32 EnAtb1AdcSwp: 1;        /*## attribute EnAtb1AdcSwp */
   /**
	* BitsName: en_atb1_adc_swn
	* Description: Connects BISTADC1 n-input to DC_int_ATB1_180
	*/
    uint32 EnAtb1AdcSwn: 1;        /*## attribute EnAtb1AdcSwn */
   /**
	* BitsName: en_atb1_read_rtrim_p
	* Description: Connects DC_int_ATB1_0 to DC_int_ATB2_0
	*/
    uint32 EnAtb1ReadRtrimP: 1;        /*## attribute EnAtb1ReadRtrimP */
   /**
	* BitsName: en_atb1_read_rtrim_n
	* Description: Connects DC_int_ATB1_180 to DC_int_ATB2_180
	*/
    uint32 EnAtb1ReadRtrimN: 1;        /*## attribute EnAtb1ReadRtrimN */
   /**
	* BitsName: en_atb1_adc_p_gnd
	* Description: Connects BISTADC1 p-input to GND
	*/
    uint32 EnAtb1AdcPGnd: 1;        /*## attribute EnAtb1AdcPGnd */
   /**
	* BitsName: en_atb1_adc_n_gnd
	* Description: Connects BISTADC1 n-input to GND
	*/
    uint32 EnAtb1AdcNGnd: 1;        /*## attribute EnAtb1AdcNGnd */
   /**
	* BitsName: en_atb1_rtrim_rp_gnd
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to GND
	*/
    uint32 EnAtb1RtrimRpGnd: 1;        /*## attribute EnAtb1RtrimRpGnd */
   /**
	* BitsName: en_atb1_rtrim_rn_gnd
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	*/
    uint32 EnAtb1RtrimRnGnd: 1;        /*## attribute EnAtb1RtrimRnGnd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: set_atb1_rtrim
	* Description: Resistor calibration: setting of Rtrim (target = 2.06k;
	* MSB not used; straight binary coded: 1.37k + n * 42)
	*/
    uint32 SetAtb1Rtrim: 6;        /*## attribute SetAtb1Rtrim */
   /**
	* BitsName: en_atb1_rtrim_p
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to DC_int_ATB1_0
	*/
    uint32 EnAtb1RtrimP: 1;        /*## attribute EnAtb1RtrimP */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: set_atb1_rtrim_rp
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb1RtrimRp: 6;        /*## attribute SetAtb1RtrimRp */
   /**
	* BitsName: en_atb1_rtrim_n
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	* (not a typo, same functionality as ?en_atb1_rtrim_rn_gnd? but not the same switch!)
	*/
    uint32 EnAtb1RtrimN: 1;        /*## attribute EnAtb1RtrimN */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: set_atb1_rtrim_rn
	* Description: Resistor calibration: setting of RCM (target = 5.24k;
	* MSB not used; straight binary coded: 3.5k + n * 109)
	*/
    uint32 SetAtb1RtrimRn: 6;        /*## attribute SetAtb1RtrimRn */
}Nxp_Tef810x_Mod16_Atb1ConfigRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_Atb2ConfigRegisterBits_t
* RegisterName: atb2_config_register
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: en_atb2_adc_swp
	* Description: Connects BISTADC2 p-input to DC_int_ATB2_0
	*/
    uint32 EnAtb2AdcSwp: 1;        /*## attribute EnAtb2AdcSwp */
   /**
	* BitsName: en_atb2_adc_swn
	* Description: Connects BISTADC2 n-input to DC_int_ATB2_180
	*/
    uint32 EnAtb2AdcSwn: 1;        /*## attribute EnAtb2AdcSwn */
   /**
	* BitsName: en_atb2_read_rtrim_p
	* Description: Connects DC_int_ATB2_0 to DC_int_ATB1_0
	*/
    uint32 EnAtb2ReadRtrimP: 1;        /*## attribute EnAtb2ReadRtrimP */
   /**
	* BitsName: en_atb2_read_rtrim_n
	* Description: Connects DC_int_ATB2_180 to DC_int_ATB1_180
	*/
    uint32 EnAtb2ReadRtrimN: 1;        /*## attribute EnAtb2ReadRtrimN */
   /**
	* BitsName: en_atb2_adc_p_gnd
	* Description: Connects BISTADC2 p-input to GND
	*/
    uint32 EnAtb2AdcPGnd: 1;        /*## attribute EnAtb2AdcPGnd */
   /**
	* BitsName: en_atb2_adc_n_gnd
	* Description: Connects BISTADC2 n-input to GND
	*/
    uint32 EnAtb2AdcNGnd: 1;        /*## attribute EnAtb2AdcNGnd */
   /**
	* BitsName: en_atb2_rtrim_rp_gnd
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to GND
	*/
    uint32 EnAtb2RtrimRpGnd: 1;        /*## attribute EnAtb2RtrimRpGnd */
   /**
	* BitsName: en_atb2_rtrim_rn_gnd
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	*/
    uint32 EnAtb2RtrimRnGnd: 1;        /*## attribute EnAtb2RtrimRnGnd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: set_atb2_rtrim
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb2Rtrim: 6;        /*## attribute SetAtb2Rtrim */
   /**
	* BitsName: en_atb2_rtrim_p
	* Description: Resistor calibration:
	* Connects ?hot? end of Rtrim to DC_int_ATB2_0
	*/
    uint32 EnAtb2RtrimP: 1;        /*## attribute EnAtb2RtrimP */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: set_atb2_rtrim_rp
	* Description: not used, keep ?0?
	*/
    uint32 SetAtb2RtrimRp: 6;        /*## attribute SetAtb2RtrimRp */
   /**
	* BitsName: en_atb2_rtrim_n
	* Description: Resistor calibration:
	* Connects ?cold? end of RCM to GND
	* (not a typo, same as ?en_atb1_rtrim_rn_gnd? but not the same switch!)
	*/
    uint32 EnAtb2RtrimN: 1;        /*## attribute EnAtb2RtrimN */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: set_atb2_rtrim_rn
	* Description: Resistor calibration: setting of RCM (target = 5.24k;
	* MSB not used; straight binary coded: 3.5k + n * 109)
	*/
    uint32 SetAtb2RtrimRn: 6;        /*## attribute SetAtb2RtrimRn */
}Nxp_Tef810x_Mod16_Atb2ConfigRegisterBits_t;
    /**
* Nxp_Tef810x_Mod16_LdoAtbControlBits_t
* RegisterName: ldo_atb_control
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_atb
	* Description: set output voltage of local LDO
	*/
    uint32 LdoSelVoutAtb: 5;        /*## attribute LdoSelVoutAtb */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_en_atb
	* Description: enable local LDO (this LDO supplies BISTADCs and their buffers)
	*/
    uint32 LdoEnAtb: 1;        /*## attribute LdoEnAtb */
}Nxp_Tef810x_Mod16_LdoAtbControlBits_t;
    /**
* Nxp_Tef810x_Mod16_Atb1Bits_t
* RegisterName: atb1
* 
* AddressRange: 0x050 - 0x054
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
	* Description: Select signal to be measured:
	* 
	* atb1_vdda_1v8=8'h1
	* atb1_vdda_1v1=8'h2
	* atb1_vddd_safety_1v1=8'h3
	* atb1_iref_bg=8'h4
	* atb1_iref_bgr_1=8'h5
	* atb1_iref_bgr_2=8'h6
	* atb1_iref_local_ldo=8'h7
	*/
    uint32 Atb1Set: 8;        /*## attribute Atb1Set */
}Nxp_Tef810x_Mod16_Atb1Bits_t;
    /**
* Nxp_Tef810x_Mod16_Atb2Bits_t
* RegisterName: atb2
* 
* AddressRange: 0x054 - 0x058
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
	* Description: Select signal to be measured:
	* 
	* atb2_vdda_1v8=8'h1
	* atb2_vdda_1v1=8'h2
	* atb2_vddd_safety_1v1=8'h3
	* atb2_iref_bg=8'h4
	* atb2_iref_bgr_1=8'h5
	* atb2_iref_bgr_2=8'h6
	* atb2_iref_local_ldo=8'h7
	*/
    uint32 Atb2Set: 8;        /*## attribute Atb2Set */
}Nxp_Tef810x_Mod16_Atb2Bits_t;
    /**
* Nxp_Tef810x_Mod16_AtbDelayTimerBits_t
* RegisterName: atb_delay_timer
* 
* AddressRange: 0x060 - 0x064
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
}Nxp_Tef810x_Mod16_AtbDelayTimerBits_t;
    /**
* Nxp_Tef810x_Mod16_AdcBuf1ControlRegBits_t
* RegisterName: adc_buf1_control_reg
* 
* AddressRange: 0x100 - 0x104
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: pol_adcbuf1
	* Description: Toggles polarity of buffer input
	*/
    uint32 PolAdcbuf1: 1;        /*## attribute PolAdcbuf1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: sel_gain_adcbuf1
	* Description: Gain control:
	* MSB not used; [0] = 0: gain = 0.5; [0] = 1: gain = 1
	*/
    uint32 SelGainAdcbuf1: 2;        /*## attribute SelGainAdcbuf1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_adcbuf1
	* Description: Enables the BISTADC1 buffer
	*/
    uint32 EnAdcbuf1: 1;        /*## attribute EnAdcbuf1 */
}Nxp_Tef810x_Mod16_AdcBuf1ControlRegBits_t;
    /**
* Nxp_Tef810x_Mod16_AdcBuf2ControlRegBits_t
* RegisterName: adc_buf2_control_reg
* 
* AddressRange: 0x104 - 0x108
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: pol_adcbuf2
	* Description: Toggles polarity of buffer input
	*/
    uint32 PolAdcbuf2: 1;        /*## attribute PolAdcbuf2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: sel_gain_adcbuf2
	* Description: Gain control:
	* MSB not used; [0] = 0: gain = 0.5; [0] = 1: gain = 1
	*/
    uint32 SelGainAdcbuf2: 2;        /*## attribute SelGainAdcbuf2 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_adcbuf2
	* Description: Enables the BISTADC2 buffer
	*/
    uint32 EnAdcbuf2: 1;        /*## attribute EnAdcbuf2 */
}Nxp_Tef810x_Mod16_AdcBuf2ControlRegBits_t;
    /**
* Nxp_Tef810x_Mod16_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00161101
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
}Nxp_Tef810x_Mod16_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t
* Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_AtbControlRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t;
/**
* Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t
* Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_AtbDataRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t;
/**
* Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t
* Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_Atb1ConfigRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t;
/**
* Nxp_Tef810x_Mod16_Atb2ConfigRegisterUnion_t
* Nxp_Tef810x_Mod16_Atb2ConfigRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_Atb2ConfigRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_Atb2ConfigRegisterUnion_t;
/**
* Nxp_Tef810x_Mod16_LdoAtbControlUnion_t
* Nxp_Tef810x_Mod16_LdoAtbControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_LdoAtbControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_LdoAtbControlUnion_t;
/**
* Nxp_Tef810x_Mod16_Atb1Union_t
* Nxp_Tef810x_Mod16_Atb1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_Atb1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_Atb1Union_t;
/**
* Nxp_Tef810x_Mod16_Atb2Union_t
* Nxp_Tef810x_Mod16_Atb2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_Atb2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_Atb2Union_t;
/**
* Nxp_Tef810x_Mod16_AtbDelayTimerUnion_t
* Nxp_Tef810x_Mod16_AtbDelayTimerUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_AtbDelayTimerBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_AtbDelayTimerUnion_t;
/**
* Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t
* Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_AdcBuf1ControlRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t;
/**
* Nxp_Tef810x_Mod16_AdcBuf2ControlRegUnion_t
* Nxp_Tef810x_Mod16_AdcBuf2ControlRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_AdcBuf2ControlRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_AdcBuf2ControlRegUnion_t;
/**
* Nxp_Tef810x_Mod16_ModuleidUnion_t
* Nxp_Tef810x_Mod16_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod16_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod16_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod16_AtbRegister_t
 * Nxp_Tef810x_Mod16_AtbRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: atb_control_register
    * AddressOffset: 0x000
    * ResetValue: 0x00000000
    * Description: Register which controls the triggering of ADC Data. Depeding on the programmed value it can be either clockless mode or clocked mode.
    */
    Nxp_Tef810x_Mod16_AtbControlRegisterUnion_t AtbControlRegister_ust;        /*## attribute AtbControlRegister_ust */

    uint32 gap01_au32[1];        /* gap 1 in register space */  /**
    * RegisterName: atb_data_register
    * AddressOffset: 0x008
    * ResetValue: 0x00000000
    * Description: This register is used to read the ADC data and status.
    */
    Nxp_Tef810x_Mod16_AtbDataRegisterUnion_t AtbDataRegister_ust;        /*## attribute AtbDataRegister_ust */
  /**
    * RegisterName: atb1_config_register
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: Settings for ATB1
    */
    Nxp_Tef810x_Mod16_Atb1ConfigRegisterUnion_t Atb1ConfigRegister_ust;        /*## attribute Atb1ConfigRegister_ust */
  /**
    * RegisterName: atb2_config_register
    * AddressOffset: 0x010
    * ResetValue: 0x00000000
    * Description: Settings for ATB2
    */
    Nxp_Tef810x_Mod16_Atb2ConfigRegisterUnion_t Atb2ConfigRegister_ust;        /*## attribute Atb2ConfigRegister_ust */

    uint32 gap02_au32[7];        /* gap 2 in register space */  /**
    * RegisterName: ldo_atb_control
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: This registers control local LDO settings
    */
    Nxp_Tef810x_Mod16_LdoAtbControlUnion_t LdoAtbControl_ust;        /*## attribute LdoAtbControl_ust */

    uint32 gap03_au32[7];        /* gap 3 in register space */  /**
    * RegisterName: atb1
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Select ATB1 Parameters
    */
    Nxp_Tef810x_Mod16_Atb1Union_t Atb1_ust;        /*## attribute Atb1_ust */
  /**
    * RegisterName: atb2
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: Select ATB2 Parameters
    */
    Nxp_Tef810x_Mod16_Atb2Union_t Atb2_ust;        /*## attribute Atb2_ust */

    uint32 gap04_au32[2];        /* gap 4 in register space */  /**
    * RegisterName: atb_delay_timer
    * AddressOffset: 0x060
    * ResetValue: 0x00001F1F
    * Description: Delay Timer Register to program make and break interval between ATB1 and ATB2 selection logic. (The delay is programmed values *25ns)
    */
    Nxp_Tef810x_Mod16_AtbDelayTimerUnion_t AtbDelayTimer_ust;        /*## attribute AtbDelayTimer_ust */

    uint32 gap05_au32[39];        /* gap 5 in register space */  /**
    * RegisterName: adc_buf1_control_reg
    * AddressOffset: 0x100
    * ResetValue: 0x00000000
    * Description: adc_buf1 Settings
    */
    Nxp_Tef810x_Mod16_AdcBuf1ControlRegUnion_t AdcBuf1ControlReg_ust;        /*## attribute AdcBuf1ControlReg_ust */
  /**
    * RegisterName: adc_buf2_control_reg
    * AddressOffset: 0x104
    * ResetValue: 0x00000000
    * Description: adc_buf2 Settings
    */
    Nxp_Tef810x_Mod16_AdcBuf2ControlRegUnion_t AdcBuf2ControlReg_ust;        /*## attribute AdcBuf2ControlReg_ust */

    uint32 gap06_au32[62];        /* gap 6 in register space */  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x200
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;

    uint32 gap07_au32[892];        /* gap 7 in register space */  /**
    * RegisterName: Reserved01
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;

    uint32 gap08_au32[1];        /* gap 8 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00161101
    * Description: Register with details of Module ID and Version number
    */
    Nxp_Tef810x_Mod16_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod16_AtbRegister_t;

#endif
