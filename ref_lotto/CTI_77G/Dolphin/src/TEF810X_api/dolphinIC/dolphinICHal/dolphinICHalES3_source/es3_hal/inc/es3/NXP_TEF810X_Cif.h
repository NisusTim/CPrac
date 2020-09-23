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
* @NXP_TEF810X_Cif.h
*/
#ifndef NXP_TEF810X_CIF_H
#define NXP_TEF810X_CIF_H
#include "Std_Types.h"

#define CIF_MODULE_ADDRESS 0x03
/**
*NXP_TEF810X_MOD03_CIFCONFIGREG_U16
* RegisterName: MOD03_CifConfigReg
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x80000000
*/
#define NXP_TEF810X_MOD03_CIFCONFIGREG_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD03_CIFLINECNTREG_U16
* RegisterName: MOD03_CifLineCntReg
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD03_CIFLINECNTREG_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD03_CIF_CRC_CTRL1_U16
* RegisterName: MOD03_cif_crc_ctrl1
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD03_CIF_CRC_CTRL1_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD03_CIF_CRC_CTRL2_U16
* RegisterName: MOD03_cif_crc_ctrl2
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD03_CIF_CRC_CTRL2_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD03_CIF_CRC_CTRL3_U16
* RegisterName: MOD03_cif_crc_ctrl3
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000110
*/
#define NXP_TEF810X_MOD03_CIF_CRC_CTRL3_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD03_CIF_OUTPUT_INVERT_CTRL_U16
* RegisterName: MOD03_cif_output_invert_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_CIF_OUTPUT_INVERT_CTRL_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD03_PDC_CONFIG_REG_U16
* RegisterName: MOD03_pdc_config_reg
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00A9A700
*/
#define NXP_TEF810X_MOD03_PDC_CONFIG_REG_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD03_CIF_TXN_CTRL_U16
* RegisterName: MOD03_cif_txn_ctrl
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_CIF_TXN_CTRL_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD03_CIF_SEL_SACK_REG_U16
* RegisterName: MOD03_cif_sel_sack_reg
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00003FFF
*/
#define NXP_TEF810X_MOD03_CIF_SEL_SACK_REG_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD03_CIF_GLOBAL_MFIO_CTRL_U16
* RegisterName: MOD03_cif_global_mfio_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD03_CIF_GLOBAL_MFIO_CTRL_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL1_U16
* RegisterName: MOD03_cif_mfio_ctrl1
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL1_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL2_U16
* RegisterName: MOD03_cif_mfio_ctrl2
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL2_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL3_U16
* RegisterName: MOD03_cif_mfio_ctrl3
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL3_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL4_U16
* RegisterName: MOD03_cif_mfio_ctrl4
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL4_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL5_U16
* RegisterName: MOD03_cif_mfio_ctrl5
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL5_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL6_U16
* RegisterName: MOD03_cif_mfio_ctrl6
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL6_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD03_CIF_MFIO_CTRL7_U16
* RegisterName: MOD03_cif_mfio_ctrl7
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00131131
*/
#define NXP_TEF810X_MOD03_CIF_MFIO_CTRL7_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16
* RegisterName: MOD03_CifTestModeControlReg
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x00000FFF
*/
#define NXP_TEF810X_MOD03_CIFTESTMODECONTROLREG_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16
* RegisterName: MOD03_WindowActiveSel
* AccessMode: READWRITE
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_WINDOWACTIVESEL_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD03_MASTER_IDIV_CTRL_U16
* RegisterName: MOD03_master_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x000400B0
*/
#define NXP_TEF810X_MOD03_MASTER_IDIV_CTRL_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD03_PDC_SHIFT_REG_IDIV_CTRL_U16
* RegisterName: MOD03_pdc_shift_reg_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x00000002
*/
#define NXP_TEF810X_MOD03_PDC_SHIFT_REG_IDIV_CTRL_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD03_REF_CNTR_INIT_U16
* RegisterName: MOD03_ref_cntr_init
* AccessMode: READWRITE
* AddressRange: 0x0078 - 0x007C
* ResetValue: 0x01E00028
*/
#define NXP_TEF810X_MOD03_REF_CNTR_INIT_U16 (uint16)0x0078
/**
*NXP_TEF810X_MOD03_FREQ_COUNTER_START_U16
* RegisterName: MOD03_freq_counter_start
* AccessMode: READWRITE
* AddressRange: 0x007C - 0x0080
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD03_FREQ_COUNTER_START_U16 (uint16)0x007C
/**
*NXP_TEF810X_MOD03_FREQ_COUNTER_READ_VALUE_U16
* RegisterName: MOD03_freq_counter_read_value
* AccessMode: READ
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_FREQ_COUNTER_READ_VALUE_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD03_REF_COUNTER_READ_VALUE_U16
* RegisterName: MOD03_ref_counter_read_value
* AccessMode: READ
* AddressRange: 0x0084 - 0x0088
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_REF_COUNTER_READ_VALUE_U16 (uint16)0x0084
/**
*NXP_TEF810X_MOD03_ATB_SET_TRIM_U16
* RegisterName: MOD03_atb_set_trim
* AccessMode: READWRITE
* AddressRange: 0x0094 - 0x0098
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD03_ATB_SET_TRIM_U16 (uint16)0x0094
/**
*NXP_TEF810X_MOD03_MODULEID_U16
* RegisterName: MOD03_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00033301
*/
#define NXP_TEF810X_MOD03_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod03_CIFCONFIGREGBits_t
* RegisterName: CifConfigReg
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: Packet_format_enable
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the CIF interface)
	*/
    uint32 PacketFormatEnable: 1;        /*## attribute PacketFormatEnable */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: Clock_data_relation
	* Description: 0 -  12 bit parallel data is rise edge aligned  with o/p cif clock
	* 1 -  data is fall edge aligned with o/p clock.
	*/
    uint32 ClockDataRelation: 1;        /*## attribute ClockDataRelation */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: CIF_CRC_control
	* Description: This bit enables the 32-bit CRC engine and append the CRC output in the packet footer.32 -bit CRC is send as three seperated 12 bit in the packet.  
	* 1= enable CIF CRC
	* 0= disable CIF CRC
	*/
    uint32 CifCrcControl: 1;        /*## attribute CifCrcControl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: CifDataMode
	* Description: 1= 4 data chunk mode(4 consecutive samples of ADC1,4 consecutive samples of ADC2,4 consecutive samples of ADC3, 4 consecutive samples of ADC4,4 consecutive samples of ADC1 so on)
	* 0= 1 data  mode (1 sample of ADC1,1 sample of ADC2,1 sample of ADC3,1 sample of ADC4,1 sample of ADC1 so on)
	*/
    uint32 Cifdatamode: 1;        /*## attribute Cifdatamode */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: AdcChannelDisable
	* Description: Only for internal validation and debug purpose.Individual ADC channel can be disabled.So in this case instead of scaling down the clock,Dolphin send a known data in this disabled ADC slot.
	* 
	* [0] ->  1 :  disable  adc channel 1 & 0 : enable adc channel 1
	* [1] ->  1 :  disable  adc channel 2 & 0 : enable adc channel 2
	* [2] ->  1 :  disable  adc channel 3 & 0 : enable adc channel 3
	* [3] ->  1 :  disable  adc channel 4 & 0 : enable adc channel 4
	*/
    uint32 Adcchanneldisable: 4;        /*## attribute Adcchanneldisable */
   /**
	* BitsName: ChannelDisableDataSel
	* Description: Only for internal validation and debug purpose.
	* 0 : when adc channel is disabled, send zero data 
	* 1 : when adc channel is disabled, send Test data programmed in CifTestModeControlReg
	*/
    uint32 Channeldisabledatasel: 1;        /*## attribute Channeldisabledatasel */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: single_adc_data_mode_en
	* Description: Debug Feature : only for internal validation and debug purpose.Since CIF mode does not support PDC in bypass(supports only by2,by4,by8 and by 16 modes), this debug mode can be used to get the direct data (PDC bypass) at CIF o/p  from any one of the selected ADC data channel.Along with register forced window_active, this mode can be used for ADC validation.
	*/
    uint32 SingleAdcDataModeEn: 1;        /*## attribute SingleAdcDataModeEn */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: single_adc_data_mode_channel_sel
	* Description: Debug Feature : only for internal validation and debug purpose
	* ADC channel selection in single adc data mode.
	* 00 - select ADC channel 1
	* 01 - select ADC channel 2
	* 10 - select ADC channel 3
	* 11 - select ADC channel 4
	*/
    uint32 SingleAdcDataModeChannelSel: 2;        /*## attribute SingleAdcDataModeChannelSel */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats.
	* Leave as reset if not needed explicitly.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
}Nxp_Tef810x_Mod03_CifconfigregBits_t;
    /**
* Nxp_Tef810x_Mod03_CIFLINECNTREGBits_t
* RegisterName: CifLineCntReg
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: Line_Count_Value
	* Description: Applicable only when Header (Packet_format_enable = ?1?) is enabled. 
	* This value is loaded to the counter which keep track of the current chirp number. Current chip number will be sent as a part of the packet header.Chirp no increments from 1 ,once it reaches the regiter value it wiil get re-initialised to 1.
	*/
    uint32 LineCountValue: 12;        /*## attribute LineCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod03_CiflinecntregBits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_CRC_CTRL1Bits_t
* RegisterName: cif_crc_ctrl1
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod03_CifCrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_CRC_CTRL2Bits_t
* RegisterName: cif_crc_ctrl2
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC output is XOR ed with this value.It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod03_CifCrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_CRC_CTRL3Bits_t
* RegisterName: cif_crc_ctrl3
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: crc_endianness
	* Description: Enable/Disable CRC data Swapping :
	* Dolphin uses 32-bit CRC engine. So input data to be con-catinated.  After con-catination 32 bit data is swapped before inputting the date to the CRC engine
	* 0 : Swapping enable 
	* 1 : Swapping disable
	*/
    uint32 CrcEndianness: 1;        /*## attribute CrcEndianness */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: reflect_input
	* Description: Reflecting the bits of the input 32-bit data around the middle. 
	* 0: No swapping
	* 1: Bit order is swapped around the middle of the input 32 bit data(default)It is a CRC Engine configuration parameter
	*/
    uint32 ReflectInput: 1;        /*## attribute ReflectInput */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: reflect_output
	* Description: For reflecting the final CRC ouput bits before final XOR .
	* 0 : No swapping 
	* 1 : Bit order is swapped around the middle of the CRC result.(default)
	* It is a CRC Engine configuration parameter
	*/
    uint32 ReflectOutput: 1;        /*## attribute ReflectOutput */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: dummy_zero_position
	* Description: CRC is calculated using a 32-bit input CRC engine.Two consecutive adc samples con-catinated [data1,4'b0000 : data0,4'b0000] and given to the engine.Zero padding can be done at LSB side or MSB side.
	* 
	* 0: Zero padding at LSB position (default)
	* 1: Zero padding at MSB position
	*/
    uint32 DummyZeroPosition: 1;        /*## attribute DummyZeroPosition */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod03_CifCrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_OUTPUT_INVERT_CTRLBits_t
* RegisterName: cif_output_invert_ctrl
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: invert_cif_data
	* Description: Invert option for cif data
	* 0: No invert 
	* 1: Invert 
	* [0]- > cif_data[0]
	* .
	* .
	* [11] -> cif_data[11]
	*/
    uint32 InvertCifData: 12;        /*## attribute InvertCifData */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: invert_cif_hsync
	* Description: Invert option for cif hsync.
	* 0: No invert 
	* 1: Invert
	*/
    uint32 InvertCifHsync: 1;        /*## attribute InvertCifHsync */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 15;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod03_CifOutputInvertCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_PDC_CONFIG_REGBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: make_output_unsigned
	* Description: Signed or Unsigned 12 bits.
	* 0: PDC output is Signed 12 bit
	* 1: PDC output is UnSigned 12 bit
	* Leave as reset if not needed explicitly.
	*/
    uint32 MakeOutputUnsigned: 1;        /*## attribute MakeOutputUnsigned */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: mask_input_w_WA
	* Description: 0: always process input data.PDC will process all the input samples irrespective of the window active
	* 1: PDC will only process the valid samples within the window active
	*/
    uint32 MaskInputWWa: 1;        /*## attribute MaskInputWWa */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: WA_delay_decimation_mode1
	* Description: window active delay value for decimation mode 1(by 2  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 2 clocks
	* default  value of Delay = 7x2 = 14 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode1: 4;        /*## attribute WaDelayDecimationMode1 */
   /**
	* BitsName: WA_delay_decimation_mode2
	* Description: window active delay value for decimation mode 2(by 4  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 4 clocks
	* default  value of Delay = 10x4 = 40 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode2: 4;        /*## attribute WaDelayDecimationMode2 */
   /**
	* BitsName: WA_delay_decimation_mode3
	* Description: window active delay value for decimation mode 3(by 8  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 8 clocks
	* default  value of Delay = 9x8 = 72 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode3: 4;        /*## attribute WaDelayDecimationMode3 */
   /**
	* BitsName: WA_delay_decimation_mode4
	* Description: window active delay value for decimation mode 4(by 16  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 16 clocks
	* default  value of Delay = 10x16 = 160 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode4: 4;        /*## attribute WaDelayDecimationMode4 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 8;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod03_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_TXN_CTRLBits_t
* RegisterName: cif_txn_ctrl
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: cif_txn_en
	* Description: Transmision enable for Cif.This should be the last register to be programmed(enabled) during configuration.
	* 0: Transmission is disabled
	* 1: Transmission is enabled
	*/
    uint32 CifTxnEn: 1;        /*## attribute CifTxnEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod03_CifTxnCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_SEL_SACK_REGBits_t
* RegisterName: cif_sel_sack_reg
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: cif_sel_sack
	* Description: MFIO PAD Selection register.Always keep the default value of 0x3FFF for proper opration.
	*/
    uint32 CifSelSack: 14;        /*## attribute CifSelSack */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 15;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod03_CifSelSackRegBits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_GLOBAL_MFIO_CTRLBits_t
* RegisterName: cif_global_mfio_ctrl
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: cif_global_mfio_en
	* Description: Global MFIO active low enable(E) for 14 mfio pads.
	* 1: All the mfio pads in High Impedance state
	* 0: All the mfio pads in Functional o/p mode.
	*/
    uint32 CifGlobalMfioEn: 1;        /*## attribute CifGlobalMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod03_CifGlobalMfioCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL1Bits_t
* RegisterName: cif_mfio_ctrl1
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: cif_d0_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD0MfioEn: 1;        /*## attribute CifD0MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d0_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD0MfioEnzi: 1;        /*## attribute CifD0MfioEnzi */
   /**
	* BitsName: cif_d0_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD0MfioEpun: 1;        /*## attribute CifD0MfioEpun */
   /**
	* BitsName: cif_d0_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD0MfioEpd: 1;        /*## attribute CifD0MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d0_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD0MfioEhs0: 1;        /*## attribute CifD0MfioEhs0 */
   /**
	* BitsName: cif_d0_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD0MfioEhs1: 1;        /*## attribute CifD0MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d1_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD1MfioEn: 1;        /*## attribute CifD1MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d1_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD1MfioEnzi: 1;        /*## attribute CifD1MfioEnzi */
   /**
	* BitsName: cif_d1_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD1MfioEpun: 1;        /*## attribute CifD1MfioEpun */
   /**
	* BitsName: cif_d1_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD1MfioEpd: 1;        /*## attribute CifD1MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d1_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD1MfioEhs0: 1;        /*## attribute CifD1MfioEhs0 */
   /**
	* BitsName: cif_d1_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	* Leave as reset if not needed explicitly.
	*/
    uint32 CifD1MfioEhs1: 1;        /*## attribute CifD1MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL2Bits_t
* RegisterName: cif_mfio_ctrl2
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: cif_d2_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD2MfioEn: 1;        /*## attribute CifD2MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d2_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD2MfioEnzi: 1;        /*## attribute CifD2MfioEnzi */
   /**
	* BitsName: cif_d2_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD2MfioEpun: 1;        /*## attribute CifD2MfioEpun */
   /**
	* BitsName: cif_d2_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD2MfioEpd: 1;        /*## attribute CifD2MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d2_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD2MfioEhs0: 1;        /*## attribute CifD2MfioEhs0 */
   /**
	* BitsName: cif_d2_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD2MfioEhs1: 1;        /*## attribute CifD2MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d3_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD3MfioEn: 1;        /*## attribute CifD3MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d3_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD3MfioEnzi: 1;        /*## attribute CifD3MfioEnzi */
   /**
	* BitsName: cif_d3_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD3MfioEpun: 1;        /*## attribute CifD3MfioEpun */
   /**
	* BitsName: cif_d3_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD3MfioEpd: 1;        /*## attribute CifD3MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d3_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD3MfioEhs0: 1;        /*## attribute CifD3MfioEhs0 */
   /**
	* BitsName: cif_d3_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD3MfioEhs1: 1;        /*## attribute CifD3MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL3Bits_t
* RegisterName: cif_mfio_ctrl3
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: cif_d4_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD4MfioEn: 1;        /*## attribute CifD4MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d4_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD4MfioEnzi: 1;        /*## attribute CifD4MfioEnzi */
   /**
	* BitsName: cif_d4_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD4MfioEpun: 1;        /*## attribute CifD4MfioEpun */
   /**
	* BitsName: cif_d4_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD4MfioEpd: 1;        /*## attribute CifD4MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d4_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD4MfioEhs0: 1;        /*## attribute CifD4MfioEhs0 */
   /**
	* BitsName: cif_d4_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD4MfioEhs1: 1;        /*## attribute CifD4MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d5_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD5MfioEn: 1;        /*## attribute CifD5MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d5_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD5MfioEnzi: 1;        /*## attribute CifD5MfioEnzi */
   /**
	* BitsName: cif_d5_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD5MfioEpun: 1;        /*## attribute CifD5MfioEpun */
   /**
	* BitsName: cif_d5_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD5MfioEpd: 1;        /*## attribute CifD5MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d5_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD5MfioEhs0: 1;        /*## attribute CifD5MfioEhs0 */
   /**
	* BitsName: cif_d5_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD5MfioEhs1: 1;        /*## attribute CifD5MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL4Bits_t
* RegisterName: cif_mfio_ctrl4
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: cif_d6_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD6MfioEn: 1;        /*## attribute CifD6MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d6_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD6MfioEnzi: 1;        /*## attribute CifD6MfioEnzi */
   /**
	* BitsName: cif_d6_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD6MfioEpun: 1;        /*## attribute CifD6MfioEpun */
   /**
	* BitsName: cif_d6_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD6MfioEpd: 1;        /*## attribute CifD6MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d6_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD6MfioEhs0: 1;        /*## attribute CifD6MfioEhs0 */
   /**
	* BitsName: cif_d6_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD6MfioEhs1: 1;        /*## attribute CifD6MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d7_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD7MfioEn: 1;        /*## attribute CifD7MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d7_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD7MfioEnzi: 1;        /*## attribute CifD7MfioEnzi */
   /**
	* BitsName: cif_d7_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD7MfioEpun: 1;        /*## attribute CifD7MfioEpun */
   /**
	* BitsName: cif_d7_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD7MfioEpd: 1;        /*## attribute CifD7MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d7_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD7MfioEhs0: 1;        /*## attribute CifD7MfioEhs0 */
   /**
	* BitsName: cif_d7_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD7MfioEhs1: 1;        /*## attribute CifD7MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl4Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL5Bits_t
* RegisterName: cif_mfio_ctrl5
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: cif_d8_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD8MfioEn: 1;        /*## attribute CifD8MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d8_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD8MfioEnzi: 1;        /*## attribute CifD8MfioEnzi */
   /**
	* BitsName: cif_d8_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD8MfioEpun: 1;        /*## attribute CifD8MfioEpun */
   /**
	* BitsName: cif_d8_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD8MfioEpd: 1;        /*## attribute CifD8MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d8_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD8MfioEhs0: 1;        /*## attribute CifD8MfioEhs0 */
   /**
	* BitsName: cif_d8_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD8MfioEhs1: 1;        /*## attribute CifD8MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d9_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD9MfioEn: 1;        /*## attribute CifD9MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d9_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD9MfioEnzi: 1;        /*## attribute CifD9MfioEnzi */
   /**
	* BitsName: cif_d9_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD9MfioEpun: 1;        /*## attribute CifD9MfioEpun */
   /**
	* BitsName: cif_d9_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD9MfioEpd: 1;        /*## attribute CifD9MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d9_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD9MfioEhs0: 1;        /*## attribute CifD9MfioEhs0 */
   /**
	* BitsName: cif_d9_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD9MfioEhs1: 1;        /*## attribute CifD9MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl5Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL6Bits_t
* RegisterName: cif_mfio_ctrl6
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: cif_d10_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD10MfioEn: 1;        /*## attribute CifD10MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d10_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD10MfioEnzi: 1;        /*## attribute CifD10MfioEnzi */
   /**
	* BitsName: cif_d10_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD10MfioEpun: 1;        /*## attribute CifD10MfioEpun */
   /**
	* BitsName: cif_d10_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD10MfioEpd: 1;        /*## attribute CifD10MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d10_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD10MfioEhs0: 1;        /*## attribute CifD10MfioEhs0 */
   /**
	* BitsName: cif_d10_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD10MfioEhs1: 1;        /*## attribute CifD10MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d11_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD11MfioEn: 1;        /*## attribute CifD11MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d11_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD11MfioEnzi: 1;        /*## attribute CifD11MfioEnzi */
   /**
	* BitsName: cif_d11_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD11MfioEpun: 1;        /*## attribute CifD11MfioEpun */
   /**
	* BitsName: cif_d11_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD11MfioEpd: 1;        /*## attribute CifD11MfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d11_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD11MfioEhs0: 1;        /*## attribute CifD11MfioEhs0 */
   /**
	* BitsName: cif_d11_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD11MfioEhs1: 1;        /*## attribute CifD11MfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl6Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIF_MFIO_CTRL7Bits_t
* RegisterName: cif_mfio_ctrl7
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: lvds_cif_datavalid_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	* Leave as reset if not needed explicitly.
	*/
    uint32 LvdsCifDatavalidMfioEn: 1;        /*## attribute LvdsCifDatavalidMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 LvdsCifDatavalidMfioEnzi: 1;        /*## attribute LvdsCifDatavalidMfioEnzi */
   /**
	* BitsName: lvds_cif_datavalid_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 LvdsCifDatavalidMfioEpun: 1;        /*## attribute LvdsCifDatavalidMfioEpun */
   /**
	* BitsName: lvds_cif_datavalidmfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 LvdsCifDatavalidmfioEpd: 1;        /*## attribute LvdsCifDatavalidmfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 LvdsCifDatavalidMfioEhs0: 1;        /*## attribute LvdsCifDatavalidMfioEhs0 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 LvdsCifDatavalidMfioEhs1: 1;        /*## attribute LvdsCifDatavalidMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_clk_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifClkMfioEn: 1;        /*## attribute CifClkMfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_clk_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifClkMfioEnzi: 1;        /*## attribute CifClkMfioEnzi */
   /**
	* BitsName: cif_clk_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifClkMfioEpun: 1;        /*## attribute CifClkMfioEpun */
   /**
	* BitsName: cif_clk_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifClkMfioEpd: 1;        /*## attribute CifClkMfioEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_clk_mfio_ehs0
	* Description: MFIO pad Speed Selection.  
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifClkMfioEhs0: 1;        /*## attribute CifClkMfioEhs0 */
   /**
	* BitsName: cif_clk_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifClkMfioEhs1: 1;        /*## attribute CifClkMfioEhs1 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 10;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod03_CifMfioCtrl7Bits_t;
    /**
* Nxp_Tef810x_Mod03_CIFTESTMODECONTROLREGBits_t
* RegisterName: CifTestModeControlReg
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: cif_testmode_test_data
	* Description: Debug Feature :
	* 12 bit Debug Data to be send in Test Mode.
	*/
    uint32 CifTestmodeTestData: 12;        /*## attribute CifTestmodeTestData */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_testmode_en
	* Description: Debug Feature :
	* 0: PDC functional data as input to CIF
	* 1: Test data as input to CIF
	*/
    uint32 CifTestmodeEn: 1;        /*## attribute CifTestmodeEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_testmode_data_sel
	* Description: Debug Feature :
	* 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 CifTestmodeDataSel: 2;        /*## attribute CifTestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_testmode_skip_pdc
	* Description: Debug Feature :
	* 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 CifTestmodeSkipPdc: 1;        /*## attribute CifTestmodeSkipPdc */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 7;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod03_CiftestmodecontrolregBits_t;
    /**
* Nxp_Tef810x_Mod03_WINDOWACTIVESELBits_t
* RegisterName: WindowActiveSel
* 
* AddressRange: 0xREADWRITE - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: window_active_sel
	* Description: Debug Feature :
	* This bit acts as the internal window _active for serialiser in CIF mode.
	* 0: register forced window active set to '0'
	* 1: register forced window active set to '1'
	*/
    uint32 WindowActiveSel: 1;        /*## attribute WindowActiveSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: window_active_reg_control
	* Description: Debug Feature :
	* For debug pupose window_active can be forced from a register.This bit selects b/w window active from chirp and window_active from Register.
	* 0: Window active is from Chirp engine
	* 1: window active is from register
	*/
    uint32 WindowActiveRegControl: 1;        /*## attribute WindowActiveRegControl */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod03_WindowactiveselBits_t;
    /**
* Nxp_Tef810x_Mod03_MASTER_IDIV_CTRLBits_t
* RegisterName: master_idiv_ctrl
* 
* AddressRange: 0xREADWRITE - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: master_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for master clk divider when cif is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 MasterIdivRst: 1;        /*## attribute MasterIdivRst */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: master_idiv_value
	* Description: Input clock to the divider is  480 MHz.
	* O/P frequency = 480MHz/ (1+master_idiv_value)
	* 
	* By default cif o/p clock is set to 40 MHz.Software can use this field for getting the desired cif clock at the o/p before the correct decimation factor comes from chirp.After the first profile load, the design will  always selects idiv from LUT based on decimation
	* Note: CIF is a parallel interface 12-bit per clock.   
	* 
	* Note: Maximum supported clock frequency at CIF interface is 80MHz. So other higher O/P values (idiv values less than 1010 ) not to be used  for this interface
	*/
    uint32 MasterIdivValue: 6;        /*## attribute MasterIdivValue */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: This bit can be used to tune the coif o/p clock to required frequency before the first Profile Load Signal or required Decimation factor comes from Chirp. After the first profile load, the design will override this selection and always selects div. from LUT based on decimation.
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the register.
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser,the internal mux will again select the idiv value from register till the next profile load comes.
	*/
    uint32 MasterIdivSelRegLut: 1;        /*## attribute MasterIdivSelRegLut */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: master_idiv_blk_cnt
	* Description: Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz.
	*/
    uint32 MasterIdivBlkCnt: 6;        /*## attribute MasterIdivBlkCnt */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 10;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod03_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_PDC_SHIFT_REG_IDIV_CTRLBits_t
* RegisterName: pdc_shift_reg_idiv_ctrl
* 
* AddressRange: 0xREADWRITE - 0x070
* ResetValue: 0x00000074
*/
typedef struct  {
   /**
	* BitsName: adc_data_sampling_point
	* Description: ADC Data Capturing :After the sampling pulse generation ,the idea is to position the sampling pulse in the middle of the ADC data window.The pulse can be moved to the right in steps of 480 MHz clock using this register field.
	* 000: sampling pulse is right shifted by two 480/600 clks (double-sync) from the selected adc_clk edge 
	* 001:sampling pulse is right shifted by three 480/600 clks
	* 010:sampling pulse is right shifted by four 480/600 clks
	* ?.
	* ?.
	* 111: sampling pulse is right shifted by nine 480/600 clks
	*/
    uint32 AdcDataSamplingPoint: 3;        /*## attribute AdcDataSamplingPoint */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: adc_clk_edge_sel
	* Description: ADC data is sampled on serialiser 480MHz clock using a clock aligner logic.Sampling pulse  is generated with an edge detector in adc clock path.
	* 0: Detect adc clk pos edge for generating the sampling pulse
	* 1: Detect adc clk neg edge
	*/
    uint32 AdcClkEdgeSel: 1;        /*## attribute AdcClkEdgeSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: adc_clock_select
	* Description: ADC clock selection logic. The selected ADC clock is used as data_valid to sample the ADC data.
	* 000 : All the ADC clocks are OR ed together (default )
	* 001 : Select adc1 clock
	* 010 : Select adc2 clock
	* 011 : Select adc3 clock
	* 100 : Select adc4 clock
	* 101 : OR adc1 & adc3 clock
	* 110 : OR adc2 & adc4 clock
	* 111 : OR adc1 & adc4 clock.
	*/
    uint32 AdcClockSelect: 3;        /*## attribute AdcClockSelect */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 21;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_REF_CNTR_INITBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0xREADWRITE - 0x078
* ResetValue: 0x0000007C
*/
typedef struct  {
   /**
	* BitsName: ref_count_value
	* Description: value for the reference count time (40 MHz= 25 ns base time) default is d'40. This is used as reference count in both spi triggered mode and window_active triggered mode
	*/
    uint32 RefCountValue: 16;        /*## attribute RefCountValue */
   /**
	* BitsName: ideal_480_count_value
	* Description: This is applicable when the freq counter trigger is based on  window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
}Nxp_Tef810x_Mod03_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod03_FREQ_COUNTER_STARTBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0xREADWRITE - 0x07C
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle, 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: freq_counter_deviation
	* Description: Number of lsb bits to be ignored while comparing the final freq counter read value. This is required incase of frequency counter trigger is based on window_active  for functional safety. The hardware then compares the value measured by frequency counter against ideal_480_count_value ignoring the lsb bits. 
	* 0001: Zeroth bit is ignored from comparison
	* 0011: Zeroth & first bits are ignored from comparison
	* 0111: Zeroth & first & second bits are ignored from comparison
	* 1111: Zeroth & first & second & third bits are ignored from comparison
	*/
    uint32 FreqCounterDeviation: 4;        /*## attribute FreqCounterDeviation */
   /**
	* BitsName: freq_counter_trigger_sel
	* Description: By default, the frequency counter is triggered based on window_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	*/
    uint32 FreqCounterTriggerSel: 1;        /*## attribute FreqCounterTriggerSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod03_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod03_FREQ_COUNTER_READ_VALUEBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0xREAD - 0x080
* ResetValue: 0x00000084
*/
typedef struct  {
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq count value = reported value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq count value = (reported value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start reg will clear this bit
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 11;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod03_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod03_REF_COUNTER_READ_VALUEBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0xREAD - 0x084
* ResetValue: 0x00000088
*/
typedef struct  {
   /**
	* BitsName: counter_read_value
	* Description: Reference count value
	*/
    uint32 CounterReadValue: 16;        /*## attribute CounterReadValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod03_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod03_ATB_SET_TRIMBits_t
* RegisterName: atb_set_trim
* 
* AddressRange: 0xREADWRITE - 0x094
* ResetValue: 0x00000098
*/
typedef struct  {
   /**
	* BitsName: atb_set_trim_r_n
	* Description: atb_set_trim_r_n [5:1]  : Spare bits
	* 
	* atb_set_trim_r_n [0]  -  Enable or disable PDC sync(applly PDC reset on Line active pos edge)
	*                                           : 0 -> PDC Sync is disabled.
	*                                           : 1 -> PDC Sync is enabled.
	*/
    uint32 AtbSetTrimRN: 6;        /*## attribute AtbSetTrimRN */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod03_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod03_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: Aperture
	* Description: Aperture: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Major_revision
	* Description: Major revision: Major revision i.e. implies software modifications.
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Identifier
	* Description: Identifier value. This is the unique identifier of the module. In case of cif it is 0x03.
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod03_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod03_CifconfigregBits_t
* RegisterName: CifConfigReg
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x80000000
*/
typedef struct  {
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats.
	* Leave as reset if not needed explicitly.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: single_adc_data_mode_channel_sel
	* Description: Debug Feature : only for internal validation and debug purpose
	* ADC channel selection in single adc data mode.
	* 00 - select ADC channel 1
	* 01 - select ADC channel 2
	* 10 - select ADC channel 3
	* 11 - select ADC channel 4
	*/
    uint32 SingleAdcDataModeChannelSel: 2;        /*## attribute SingleAdcDataModeChannelSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: single_adc_data_mode_en
	* Description: Debug Feature : only for internal validation and debug purpose.Since CIF mode does not support PDC in bypass(supports only by2,by4,by8 and by 16 modes), this debug mode can be used to get the direct data (PDC bypass) at CIF o/p  from any one of the selected ADC data channel.Along with register forced window_active, this mode can be used for ADC validation.
	*/
    uint32 SingleAdcDataModeEn: 1;        /*## attribute SingleAdcDataModeEn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ChannelDisableDataSel
	* Description: Only for internal validation and debug purpose.
	* 0 : when adc channel is disabled, send zero data 
	* 1 : when adc channel is disabled, send Test data programmed in CifTestModeControlReg
	*/
    uint32 Channeldisabledatasel: 1;        /*## attribute Channeldisabledatasel */
   /**
	* BitsName: AdcChannelDisable
	* Description: Only for internal validation and debug purpose.Individual ADC channel can be disabled.So in this case instead of scaling down the clock,Dolphin send a known data in this disabled ADC slot.
	* 
	* [0] ->  1 :  disable  adc channel 1 & 0 : enable adc channel 1
	* [1] ->  1 :  disable  adc channel 2 & 0 : enable adc channel 2
	* [2] ->  1 :  disable  adc channel 3 & 0 : enable adc channel 3
	* [3] ->  1 :  disable  adc channel 4 & 0 : enable adc channel 4
	*/
    uint32 Adcchanneldisable: 4;        /*## attribute Adcchanneldisable */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: CifDataMode
	* Description: 1= 4 data chunk mode(4 consecutive samples of ADC1,4 consecutive samples of ADC2,4 consecutive samples of ADC3, 4 consecutive samples of ADC4,4 consecutive samples of ADC1 so on)
	* 0= 1 data  mode (1 sample of ADC1,1 sample of ADC2,1 sample of ADC3,1 sample of ADC4,1 sample of ADC1 so on)
	*/
    uint32 Cifdatamode: 1;        /*## attribute Cifdatamode */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: CIF_CRC_control
	* Description: This bit enables the 32-bit CRC engine and append the CRC output in the packet footer.32 -bit CRC is send as three seperated 12 bit in the packet.  
	* 1= enable CIF CRC
	* 0= disable CIF CRC
	*/
    uint32 CifCrcControl: 1;        /*## attribute CifCrcControl */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: Clock_data_relation
	* Description: 0 -  12 bit parallel data is rise edge aligned  with o/p cif clock
	* 1 -  data is fall edge aligned with o/p clock.
	*/
    uint32 ClockDataRelation: 1;        /*## attribute ClockDataRelation */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: Packet_format_enable
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the CIF interface)
	*/
    uint32 PacketFormatEnable: 1;        /*## attribute PacketFormatEnable */
}Nxp_Tef810x_Mod03_CifconfigregBits_t;
    /**
* Nxp_Tef810x_Mod03_CiflinecntregBits_t
* RegisterName: CifLineCntReg
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: Line_Count_Value
	* Description: Applicable only when Header (Packet_format_enable = ?1?) is enabled. 
	* This value is loaded to the counter which keep track of the current chirp number. Current chip number will be sent as a part of the packet header.Chirp no increments from 1 ,once it reaches the regiter value it wiil get re-initialised to 1.
	*/
    uint32 LineCountValue: 12;        /*## attribute LineCountValue */
}Nxp_Tef810x_Mod03_CiflinecntregBits_t;
    /**
* Nxp_Tef810x_Mod03_CifCrcCtrl1Bits_t
* RegisterName: cif_crc_ctrl1
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod03_CifCrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifCrcCtrl2Bits_t
* RegisterName: cif_crc_ctrl2
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC output is XOR ed with this value.It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod03_CifCrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifCrcCtrl3Bits_t
* RegisterName: cif_crc_ctrl3
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00000110
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: dummy_zero_position
	* Description: CRC is calculated using a 32-bit input CRC engine.Two consecutive adc samples con-catinated [data1,4'b0000 : data0,4'b0000] and given to the engine.Zero padding can be done at LSB side or MSB side.
	* 
	* 0: Zero padding at LSB position (default)
	* 1: Zero padding at MSB position
	*/
    uint32 DummyZeroPosition: 1;        /*## attribute DummyZeroPosition */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: reflect_output
	* Description: For reflecting the final CRC ouput bits before final XOR .
	* 0 : No swapping 
	* 1 : Bit order is swapped around the middle of the CRC result.(default)
	* It is a CRC Engine configuration parameter
	*/
    uint32 ReflectOutput: 1;        /*## attribute ReflectOutput */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: reflect_input
	* Description: Reflecting the bits of the input 32-bit data around the middle. 
	* 0: No swapping
	* 1: Bit order is swapped around the middle of the input 32 bit data(default)It is a CRC Engine configuration parameter
	*/
    uint32 ReflectInput: 1;        /*## attribute ReflectInput */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: crc_endianness
	* Description: Enable/Disable CRC data Swapping :
	* Dolphin uses 32-bit CRC engine. So input data to be con-catinated.  After con-catination 32 bit data is swapped before inputting the date to the CRC engine
	* 0 : Swapping enable 
	* 1 : Swapping disable
	*/
    uint32 CrcEndianness: 1;        /*## attribute CrcEndianness */
}Nxp_Tef810x_Mod03_CifCrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifOutputInvertCtrlBits_t
* RegisterName: cif_output_invert_ctrl
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: invert_cif_hsync
	* Description: Invert option for cif hsync.
	* 0: No invert 
	* 1: Invert
	*/
    uint32 InvertCifHsync: 1;        /*## attribute InvertCifHsync */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: invert_cif_data
	* Description: Invert option for cif data
	* 0: No invert 
	* 1: Invert 
	* [0]- > cif_data[0]
	* .
	* .
	* [11] -> cif_data[11]
	*/
    uint32 InvertCifData: 12;        /*## attribute InvertCifData */
}Nxp_Tef810x_Mod03_CifOutputInvertCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_PdcConfigRegBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00A9A700
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: WA_delay_decimation_mode4
	* Description: window active delay value for decimation mode 4(by 16  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 16 clocks
	* default  value of Delay = 10x16 = 160 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode4: 4;        /*## attribute WaDelayDecimationMode4 */
   /**
	* BitsName: WA_delay_decimation_mode3
	* Description: window active delay value for decimation mode 3(by 8  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 8 clocks
	* default  value of Delay = 9x8 = 72 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode3: 4;        /*## attribute WaDelayDecimationMode3 */
   /**
	* BitsName: WA_delay_decimation_mode2
	* Description: window active delay value for decimation mode 2(by 4  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 4 clocks
	* default  value of Delay = 10x4 = 40 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode2: 4;        /*## attribute WaDelayDecimationMode2 */
   /**
	* BitsName: WA_delay_decimation_mode1
	* Description: window active delay value for decimation mode 1(by 2  decimation factor).The delay b/w the input and output window active of PDC.The output data_valid will also be delayed by the same factor.Since PDC is running at 40 MHz,Delay measured in clocks of 40 MHz.
	* Delay= register value x 2 clocks
	* default  value of Delay = 7x2 = 14 clocks of 40MHz.
	*/
    uint32 WaDelayDecimationMode1: 4;        /*## attribute WaDelayDecimationMode1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: mask_input_w_WA
	* Description: 0: always process input data.PDC will process all the input samples irrespective of the window active
	* 1: PDC will only process the valid samples within the window active
	*/
    uint32 MaskInputWWa: 1;        /*## attribute MaskInputWWa */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: make_output_unsigned
	* Description: Signed or Unsigned 12 bits.
	* 0: PDC output is Signed 12 bit
	* 1: PDC output is UnSigned 12 bit
	* Leave as reset if not needed explicitly.
	*/
    uint32 MakeOutputUnsigned: 1;        /*## attribute MakeOutputUnsigned */
}Nxp_Tef810x_Mod03_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod03_CifTxnCtrlBits_t
* RegisterName: cif_txn_ctrl
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_txn_en
	* Description: Transmision enable for Cif.This should be the last register to be programmed(enabled) during configuration.
	* 0: Transmission is disabled
	* 1: Transmission is enabled
	*/
    uint32 CifTxnEn: 1;        /*## attribute CifTxnEn */
}Nxp_Tef810x_Mod03_CifTxnCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_CifSelSackRegBits_t
* RegisterName: cif_sel_sack_reg
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x00003FFF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_sel_sack
	* Description: MFIO PAD Selection register.Always keep the default value of 0x3FFF for proper opration.
	*/
    uint32 CifSelSack: 14;        /*## attribute CifSelSack */
}Nxp_Tef810x_Mod03_CifSelSackRegBits_t;
    /**
* Nxp_Tef810x_Mod03_CifGlobalMfioCtrlBits_t
* RegisterName: cif_global_mfio_ctrl
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_global_mfio_en
	* Description: Global MFIO active low enable(E) for 14 mfio pads.
	* 1: All the mfio pads in High Impedance state
	* 0: All the mfio pads in Functional o/p mode.
	*/
    uint32 CifGlobalMfioEn: 1;        /*## attribute CifGlobalMfioEn */
}Nxp_Tef810x_Mod03_CifGlobalMfioCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl1Bits_t
* RegisterName: cif_mfio_ctrl1
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d1_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	* Leave as reset if not needed explicitly.
	*/
    uint32 CifD1MfioEhs1: 1;        /*## attribute CifD1MfioEhs1 */
   /**
	* BitsName: cif_d1_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD1MfioEhs0: 1;        /*## attribute CifD1MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d1_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD1MfioEpd: 1;        /*## attribute CifD1MfioEpd */
   /**
	* BitsName: cif_d1_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD1MfioEpun: 1;        /*## attribute CifD1MfioEpun */
   /**
	* BitsName: cif_d1_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD1MfioEnzi: 1;        /*## attribute CifD1MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d1_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD1MfioEn: 1;        /*## attribute CifD1MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d0_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD0MfioEhs1: 1;        /*## attribute CifD0MfioEhs1 */
   /**
	* BitsName: cif_d0_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD0MfioEhs0: 1;        /*## attribute CifD0MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d0_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD0MfioEpd: 1;        /*## attribute CifD0MfioEpd */
   /**
	* BitsName: cif_d0_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD0MfioEpun: 1;        /*## attribute CifD0MfioEpun */
   /**
	* BitsName: cif_d0_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD0MfioEnzi: 1;        /*## attribute CifD0MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d0_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD0MfioEn: 1;        /*## attribute CifD0MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl2Bits_t
* RegisterName: cif_mfio_ctrl2
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d3_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD3MfioEhs1: 1;        /*## attribute CifD3MfioEhs1 */
   /**
	* BitsName: cif_d3_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD3MfioEhs0: 1;        /*## attribute CifD3MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d3_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD3MfioEpd: 1;        /*## attribute CifD3MfioEpd */
   /**
	* BitsName: cif_d3_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD3MfioEpun: 1;        /*## attribute CifD3MfioEpun */
   /**
	* BitsName: cif_d3_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD3MfioEnzi: 1;        /*## attribute CifD3MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d3_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD3MfioEn: 1;        /*## attribute CifD3MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d2_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD2MfioEhs1: 1;        /*## attribute CifD2MfioEhs1 */
   /**
	* BitsName: cif_d2_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD2MfioEhs0: 1;        /*## attribute CifD2MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d2_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD2MfioEpd: 1;        /*## attribute CifD2MfioEpd */
   /**
	* BitsName: cif_d2_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD2MfioEpun: 1;        /*## attribute CifD2MfioEpun */
   /**
	* BitsName: cif_d2_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD2MfioEnzi: 1;        /*## attribute CifD2MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d2_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD2MfioEn: 1;        /*## attribute CifD2MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl3Bits_t
* RegisterName: cif_mfio_ctrl3
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d5_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD5MfioEhs1: 1;        /*## attribute CifD5MfioEhs1 */
   /**
	* BitsName: cif_d5_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD5MfioEhs0: 1;        /*## attribute CifD5MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d5_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD5MfioEpd: 1;        /*## attribute CifD5MfioEpd */
   /**
	* BitsName: cif_d5_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD5MfioEpun: 1;        /*## attribute CifD5MfioEpun */
   /**
	* BitsName: cif_d5_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD5MfioEnzi: 1;        /*## attribute CifD5MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d5_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD5MfioEn: 1;        /*## attribute CifD5MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d4_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD4MfioEhs1: 1;        /*## attribute CifD4MfioEhs1 */
   /**
	* BitsName: cif_d4_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD4MfioEhs0: 1;        /*## attribute CifD4MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d4_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD4MfioEpd: 1;        /*## attribute CifD4MfioEpd */
   /**
	* BitsName: cif_d4_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD4MfioEpun: 1;        /*## attribute CifD4MfioEpun */
   /**
	* BitsName: cif_d4_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD4MfioEnzi: 1;        /*## attribute CifD4MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d4_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD4MfioEn: 1;        /*## attribute CifD4MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl4Bits_t
* RegisterName: cif_mfio_ctrl4
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d7_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD7MfioEhs1: 1;        /*## attribute CifD7MfioEhs1 */
   /**
	* BitsName: cif_d7_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD7MfioEhs0: 1;        /*## attribute CifD7MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d7_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD7MfioEpd: 1;        /*## attribute CifD7MfioEpd */
   /**
	* BitsName: cif_d7_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD7MfioEpun: 1;        /*## attribute CifD7MfioEpun */
   /**
	* BitsName: cif_d7_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD7MfioEnzi: 1;        /*## attribute CifD7MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d7_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD7MfioEn: 1;        /*## attribute CifD7MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d6_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD6MfioEhs1: 1;        /*## attribute CifD6MfioEhs1 */
   /**
	* BitsName: cif_d6_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD6MfioEhs0: 1;        /*## attribute CifD6MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d6_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD6MfioEpd: 1;        /*## attribute CifD6MfioEpd */
   /**
	* BitsName: cif_d6_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD6MfioEpun: 1;        /*## attribute CifD6MfioEpun */
   /**
	* BitsName: cif_d6_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD6MfioEnzi: 1;        /*## attribute CifD6MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d6_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD6MfioEn: 1;        /*## attribute CifD6MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl4Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl5Bits_t
* RegisterName: cif_mfio_ctrl5
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d9_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD9MfioEhs1: 1;        /*## attribute CifD9MfioEhs1 */
   /**
	* BitsName: cif_d9_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD9MfioEhs0: 1;        /*## attribute CifD9MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d9_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD9MfioEpd: 1;        /*## attribute CifD9MfioEpd */
   /**
	* BitsName: cif_d9_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD9MfioEpun: 1;        /*## attribute CifD9MfioEpun */
   /**
	* BitsName: cif_d9_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD9MfioEnzi: 1;        /*## attribute CifD9MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d9_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD9MfioEn: 1;        /*## attribute CifD9MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d8_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD8MfioEhs1: 1;        /*## attribute CifD8MfioEhs1 */
   /**
	* BitsName: cif_d8_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD8MfioEhs0: 1;        /*## attribute CifD8MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d8_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD8MfioEpd: 1;        /*## attribute CifD8MfioEpd */
   /**
	* BitsName: cif_d8_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD8MfioEpun: 1;        /*## attribute CifD8MfioEpun */
   /**
	* BitsName: cif_d8_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD8MfioEnzi: 1;        /*## attribute CifD8MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d8_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD8MfioEn: 1;        /*## attribute CifD8MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl5Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl6Bits_t
* RegisterName: cif_mfio_ctrl6
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_d11_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD11MfioEhs1: 1;        /*## attribute CifD11MfioEhs1 */
   /**
	* BitsName: cif_d11_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD11MfioEhs0: 1;        /*## attribute CifD11MfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_d11_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD11MfioEpd: 1;        /*## attribute CifD11MfioEpd */
   /**
	* BitsName: cif_d11_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD11MfioEpun: 1;        /*## attribute CifD11MfioEpun */
   /**
	* BitsName: cif_d11_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD11MfioEnzi: 1;        /*## attribute CifD11MfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_d11_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD11MfioEn: 1;        /*## attribute CifD11MfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_d10_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifD10MfioEhs1: 1;        /*## attribute CifD10MfioEhs1 */
   /**
	* BitsName: cif_d10_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifD10MfioEhs0: 1;        /*## attribute CifD10MfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: cif_d10_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifD10MfioEpd: 1;        /*## attribute CifD10MfioEpd */
   /**
	* BitsName: cif_d10_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifD10MfioEpun: 1;        /*## attribute CifD10MfioEpun */
   /**
	* BitsName: cif_d10_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifD10MfioEnzi: 1;        /*## attribute CifD10MfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cif_d10_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifD10MfioEn: 1;        /*## attribute CifD10MfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl6Bits_t;
    /**
* Nxp_Tef810x_Mod03_CifMfioCtrl7Bits_t
* RegisterName: cif_mfio_ctrl7
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00131131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_clk_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 CifClkMfioEhs1: 1;        /*## attribute CifClkMfioEhs1 */
   /**
	* BitsName: cif_clk_mfio_ehs0
	* Description: MFIO pad Speed Selection.  
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 CifClkMfioEhs0: 1;        /*## attribute CifClkMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_clk_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 CifClkMfioEpd: 1;        /*## attribute CifClkMfioEpd */
   /**
	* BitsName: cif_clk_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 CifClkMfioEpun: 1;        /*## attribute CifClkMfioEpun */
   /**
	* BitsName: cif_clk_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 CifClkMfioEnzi: 1;        /*## attribute CifClkMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_clk_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	*/
    uint32 CifClkMfioEn: 1;        /*## attribute CifClkMfioEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs1
	* Description: MFIO pad Speed Selection bit ehs0.Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 LvdsCifDatavalidMfioEhs1: 1;        /*## attribute LvdsCifDatavalidMfioEhs1 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs0
	* Description: MFIO pad Speed Selection. 
	* [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz
	*/
    uint32 LvdsCifDatavalidMfioEhs0: 1;        /*## attribute LvdsCifDatavalidMfioEhs0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_cif_datavalidmfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 LvdsCifDatavalidmfioEpd: 1;        /*## attribute LvdsCifDatavalidmfioEpd */
   /**
	* BitsName: lvds_cif_datavalid_mfio_epun
	* Description: Enable weak pull-up (Active Low)
	* 1: weak pull-up Disabled
	* 0: weak pull-up Enabled
	*/
    uint32 LvdsCifDatavalidMfioEpun: 1;        /*## attribute LvdsCifDatavalidMfioEpun */
   /**
	* BitsName: lvds_cif_datavalid_mfio_enzi
	* Description: Receiver Enable (Active Low)
	* 1: Receiver Disabled
	* 0: Receiver Enabled
	* 
	* ENZI    EPUN  EPD    Mode
	* 
	* 0          0           0       Plain input with weak pull-up 
	* 0          0           1       Plain input with repeater (bus keeper)
	* 0          1           0       Plain input
	* 0          1           1       Plain input with weak pull-down
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	*/
    uint32 LvdsCifDatavalidMfioEnzi: 1;        /*## attribute LvdsCifDatavalidMfioEnzi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_en
	* Description: Disable Output Driver(Active Hig)
	* 0 : Pad enabled (normal operation)
	* 1 : Pad disabled
	* Leave as reset if not needed explicitly.
	*/
    uint32 LvdsCifDatavalidMfioEn: 1;        /*## attribute LvdsCifDatavalidMfioEn */
}Nxp_Tef810x_Mod03_CifMfioCtrl7Bits_t;
    /**
* Nxp_Tef810x_Mod03_CiftestmodecontrolregBits_t
* RegisterName: CifTestModeControlReg
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x00000FFF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: cif_testmode_skip_pdc
	* Description: Debug Feature :
	* 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 CifTestmodeSkipPdc: 1;        /*## attribute CifTestmodeSkipPdc */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: cif_testmode_data_sel
	* Description: Debug Feature :
	* 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 CifTestmodeDataSel: 2;        /*## attribute CifTestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: cif_testmode_en
	* Description: Debug Feature :
	* 0: PDC functional data as input to CIF
	* 1: Test data as input to CIF
	*/
    uint32 CifTestmodeEn: 1;        /*## attribute CifTestmodeEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: cif_testmode_test_data
	* Description: Debug Feature :
	* 12 bit Debug Data to be send in Test Mode.
	*/
    uint32 CifTestmodeTestData: 12;        /*## attribute CifTestmodeTestData */
}Nxp_Tef810x_Mod03_CiftestmodecontrolregBits_t;
    /**
* Nxp_Tef810x_Mod03_WindowactiveselBits_t
* RegisterName: WindowActiveSel
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: window_active_reg_control
	* Description: Debug Feature :
	* For debug pupose window_active can be forced from a register.This bit selects b/w window active from chirp and window_active from Register.
	* 0: Window active is from Chirp engine
	* 1: window active is from register
	*/
    uint32 WindowActiveRegControl: 1;        /*## attribute WindowActiveRegControl */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: window_active_sel
	* Description: Debug Feature :
	* This bit acts as the internal window _active for serialiser in CIF mode.
	* 0: register forced window active set to '0'
	* 1: register forced window active set to '1'
	*/
    uint32 WindowActiveSel: 1;        /*## attribute WindowActiveSel */
}Nxp_Tef810x_Mod03_WindowactiveselBits_t;
    /**
* Nxp_Tef810x_Mod03_MasterIdivCtrlBits_t
* RegisterName: master_idiv_ctrl
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x000400B0
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: master_idiv_blk_cnt
	* Description: Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz.
	*/
    uint32 MasterIdivBlkCnt: 6;        /*## attribute MasterIdivBlkCnt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: This bit can be used to tune the coif o/p clock to required frequency before the first Profile Load Signal or required Decimation factor comes from Chirp. After the first profile load, the design will override this selection and always selects div. from LUT based on decimation.
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the register.
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser,the internal mux will again select the idiv value from register till the next profile load comes.
	*/
    uint32 MasterIdivSelRegLut: 1;        /*## attribute MasterIdivSelRegLut */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: master_idiv_value
	* Description: Input clock to the divider is  480 MHz.
	* O/P frequency = 480MHz/ (1+master_idiv_value)
	* 
	* By default cif o/p clock is set to 40 MHz.Software can use this field for getting the desired cif clock at the o/p before the correct decimation factor comes from chirp.After the first profile load, the design will  always selects idiv from LUT based on decimation
	* Note: CIF is a parallel interface 12-bit per clock.   
	* 
	* Note: Maximum supported clock frequency at CIF interface is 80MHz. So other higher O/P values (idiv values less than 1010 ) not to be used  for this interface
	*/
    uint32 MasterIdivValue: 6;        /*## attribute MasterIdivValue */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: master_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for master clk divider when cif is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 MasterIdivRst: 1;        /*## attribute MasterIdivRst */
}Nxp_Tef810x_Mod03_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlBits_t
* RegisterName: pdc_shift_reg_idiv_ctrl
* 
* AddressRange: 0x070 - 0x074
* ResetValue: 0x00000002
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 21;        /*## attribute Reserved0 */
   /**
	* BitsName: adc_clock_select
	* Description: ADC clock selection logic. The selected ADC clock is used as data_valid to sample the ADC data.
	* 000 : All the ADC clocks are OR ed together (default )
	* 001 : Select adc1 clock
	* 010 : Select adc2 clock
	* 011 : Select adc3 clock
	* 100 : Select adc4 clock
	* 101 : OR adc1 & adc3 clock
	* 110 : OR adc2 & adc4 clock
	* 111 : OR adc1 & adc4 clock.
	*/
    uint32 AdcClockSelect: 3;        /*## attribute AdcClockSelect */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: adc_clk_edge_sel
	* Description: ADC data is sampled on serialiser 480MHz clock using a clock aligner logic.Sampling pulse  is generated with an edge detector in adc clock path.
	* 0: Detect adc clk pos edge for generating the sampling pulse
	* 1: Detect adc clk neg edge
	*/
    uint32 AdcClkEdgeSel: 1;        /*## attribute AdcClkEdgeSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: adc_data_sampling_point
	* Description: ADC Data Capturing :After the sampling pulse generation ,the idea is to position the sampling pulse in the middle of the ADC data window.The pulse can be moved to the right in steps of 480 MHz clock using this register field.
	* 000: sampling pulse is right shifted by two 480/600 clks (double-sync) from the selected adc_clk edge 
	* 001:sampling pulse is right shifted by three 480/600 clks
	* 010:sampling pulse is right shifted by four 480/600 clks
	* ?.
	* ?.
	* 111: sampling pulse is right shifted by nine 480/600 clks
	*/
    uint32 AdcDataSamplingPoint: 3;        /*## attribute AdcDataSamplingPoint */
}Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod03_RefCntrInitBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0x078 - 0x07C
* ResetValue: 0x01E00028
*/
typedef struct  {
   /**
	* BitsName: ideal_480_count_value
	* Description: This is applicable when the freq counter trigger is based on  window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
   /**
	* BitsName: ref_count_value
	* Description: value for the reference count time (40 MHz= 25 ns base time) default is d'40. This is used as reference count in both spi triggered mode and window_active triggered mode
	*/
    uint32 RefCountValue: 16;        /*## attribute RefCountValue */
}Nxp_Tef810x_Mod03_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod03_FreqCounterStartBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0x07C - 0x080
* ResetValue: 0x00000100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: freq_counter_trigger_sel
	* Description: By default, the frequency counter is triggered based on window_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	*/
    uint32 FreqCounterTriggerSel: 1;        /*## attribute FreqCounterTriggerSel */
   /**
	* BitsName: freq_counter_deviation
	* Description: Number of lsb bits to be ignored while comparing the final freq counter read value. This is required incase of frequency counter trigger is based on window_active  for functional safety. The hardware then compares the value measured by frequency counter against ideal_480_count_value ignoring the lsb bits. 
	* 0001: Zeroth bit is ignored from comparison
	* 0011: Zeroth & first bits are ignored from comparison
	* 0111: Zeroth & first & second bits are ignored from comparison
	* 1111: Zeroth & first & second & third bits are ignored from comparison
	*/
    uint32 FreqCounterDeviation: 4;        /*## attribute FreqCounterDeviation */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle, 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
}Nxp_Tef810x_Mod03_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod03_FreqCounterReadValueBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0x080 - 0x084
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start reg will clear this bit
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq count value = reported value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq count value = (reported value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
}Nxp_Tef810x_Mod03_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod03_RefCounterReadValueBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0x084 - 0x088
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: counter_read_value
	* Description: Reference count value
	*/
    uint32 CounterReadValue: 16;        /*## attribute CounterReadValue */
}Nxp_Tef810x_Mod03_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod03_AtbSetTrimBits_t
* RegisterName: atb_set_trim
* 
* AddressRange: 0x094 - 0x098
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: atb_set_trim_r_n
	* Description: atb_set_trim_r_n [5:1]  : Spare bits
	* 
	* atb_set_trim_r_n [0]  -  Enable or disable PDC sync(applly PDC reset on Line active pos edge)
	*                                           : 0 -> PDC Sync is disabled.
	*                                           : 1 -> PDC Sync is enabled.
	*/
    uint32 AtbSetTrimRN: 6;        /*## attribute AtbSetTrimRN */
}Nxp_Tef810x_Mod03_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod03_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00033301
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: Identifier value. This is the unique identifier of the module. In case of cif it is 0x03.
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
   /**
	* BitsName: Major_revision
	* Description: Major revision: Major revision i.e. implies software modifications.
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Aperture
	* Description: Aperture: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod03_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod03_CifconfigregUnion_t
* Nxp_Tef810x_Mod03_CifconfigregUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifconfigregBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifconfigregUnion_t;
/**
* Nxp_Tef810x_Mod03_CiflinecntregUnion_t
* Nxp_Tef810x_Mod03_CiflinecntregUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CiflinecntregBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CiflinecntregUnion_t;
/**
* Nxp_Tef810x_Mod03_CifCrcCtrl1Union_t
* Nxp_Tef810x_Mod03_CifCrcCtrl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifCrcCtrl1Union_t;
/**
* Nxp_Tef810x_Mod03_CifCrcCtrl2Union_t
* Nxp_Tef810x_Mod03_CifCrcCtrl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifCrcCtrl2Union_t;
/**
* Nxp_Tef810x_Mod03_CifCrcCtrl3Union_t
* Nxp_Tef810x_Mod03_CifCrcCtrl3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifCrcCtrl3Union_t;
/**
* Nxp_Tef810x_Mod03_CifOutputInvertCtrlUnion_t
* Nxp_Tef810x_Mod03_CifOutputInvertCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifOutputInvertCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifOutputInvertCtrlUnion_t;
/**
* Nxp_Tef810x_Mod03_PdcConfigRegUnion_t
* Nxp_Tef810x_Mod03_PdcConfigRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_PdcConfigRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_PdcConfigRegUnion_t;
/**
* Nxp_Tef810x_Mod03_CifTxnCtrlUnion_t
* Nxp_Tef810x_Mod03_CifTxnCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifTxnCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifTxnCtrlUnion_t;
/**
* Nxp_Tef810x_Mod03_CifSelSackRegUnion_t
* Nxp_Tef810x_Mod03_CifSelSackRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifSelSackRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifSelSackRegUnion_t;
/**
* Nxp_Tef810x_Mod03_CifGlobalMfioCtrlUnion_t
* Nxp_Tef810x_Mod03_CifGlobalMfioCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifGlobalMfioCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifGlobalMfioCtrlUnion_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl1Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl1Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl2Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl2Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl3Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl3Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl4Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl4Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl4Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl4Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl5Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl5Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl5Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl5Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl6Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl6Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl6Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl6Union_t;
/**
* Nxp_Tef810x_Mod03_CifMfioCtrl7Union_t
* Nxp_Tef810x_Mod03_CifMfioCtrl7Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl7Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CifMfioCtrl7Union_t;
/**
* Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t
* Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_CiftestmodecontrolregBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t;
/**
* Nxp_Tef810x_Mod03_WindowactiveselUnion_t
* Nxp_Tef810x_Mod03_WindowactiveselUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_WindowactiveselBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_WindowactiveselUnion_t;
/**
* Nxp_Tef810x_Mod03_MasterIdivCtrlUnion_t
* Nxp_Tef810x_Mod03_MasterIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_MasterIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_MasterIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlUnion_t
* Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod03_RefCntrInitUnion_t
* Nxp_Tef810x_Mod03_RefCntrInitUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_RefCntrInitBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_RefCntrInitUnion_t;
/**
* Nxp_Tef810x_Mod03_FreqCounterStartUnion_t
* Nxp_Tef810x_Mod03_FreqCounterStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_FreqCounterStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_FreqCounterStartUnion_t;
/**
* Nxp_Tef810x_Mod03_FreqCounterReadValueUnion_t
* Nxp_Tef810x_Mod03_FreqCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_FreqCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_FreqCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod03_RefCounterReadValueUnion_t
* Nxp_Tef810x_Mod03_RefCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_RefCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_RefCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod03_AtbSetTrimUnion_t
* Nxp_Tef810x_Mod03_AtbSetTrimUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_AtbSetTrimBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_AtbSetTrimUnion_t;
/**
* Nxp_Tef810x_Mod03_ModuleidUnion_t
* Nxp_Tef810x_Mod03_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod03_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod03_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod03_CifRegister_t
 * Nxp_Tef810x_Mod03_CifRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: CifConfigReg
    * AddressOffset: 0x000
    * ResetValue: 0x80000000
    * Description: Configuration register for CIF(data mode,packet,crc enable etc).
    */
    Nxp_Tef810x_Mod03_CifconfigregUnion_t Cifconfigreg_ust;        /*## attribute Cifconfigreg_ust */
  /**
    * RegisterName: CifLineCntReg
    * AddressOffset: 0x004
    * ResetValue: 0x00000001
    * Description: Line Count register which holds the maximum no of Chirps in a Chirp Sequence.
    */
    Nxp_Tef810x_Mod03_CiflinecntregUnion_t Ciflinecntreg_ust;        /*## attribute Ciflinecntreg_ust */
  /**
    * RegisterName: cif_crc_ctrl1
    * AddressOffset: 0x008
    * ResetValue: 0xFFFFFFFF
    * Description: CRC 32 control register
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl1Union_t CifCrcCtrl1_ust;        /*## attribute CifCrcCtrl1_ust */
  /**
    * RegisterName: cif_crc_ctrl2
    * AddressOffset: 0x00C
    * ResetValue: 0xFFFFFFFF
    * Description: CRC 32 control register
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl2Union_t CifCrcCtrl2_ust;        /*## attribute CifCrcCtrl2_ust */
  /**
    * RegisterName: cif_crc_ctrl3
    * AddressOffset: 0x010
    * ResetValue: 0x00000110
    * Description: CRC 32 control register.32 bit input to the CRC engine is formed by con-catinating two ADC samples of 12 bit and filling zeros in the remaining space.32 bit input -> [data1,4'b0000 : data0,4'b0000]
    */
    Nxp_Tef810x_Mod03_CifCrcCtrl3Union_t CifCrcCtrl3_ust;        /*## attribute CifCrcCtrl3_ust */
  /**
    * RegisterName: cif_output_invert_ctrl
    * AddressOffset: 0x014
    * ResetValue: 0x00000000
    * Description: Invert option for CIF o/p signals.only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_CifOutputInvertCtrlUnion_t CifOutputInvertCtrl_ust;        /*## attribute CifOutputInvertCtrl_ust */
  /**
    * RegisterName: pdc_config_reg
    * AddressOffset: 0x018
    * ResetValue: 0x00A9A700
    * Description: PDC data valid deley control
    */
    Nxp_Tef810x_Mod03_PdcConfigRegUnion_t PdcConfigReg_ust;        /*## attribute PdcConfigReg_ust */
  /**
    * RegisterName: cif_txn_ctrl
    * AddressOffset: 0x01C
    * ResetValue: 0x00000000
    * Description: Transmission enable for CIF.
    */
    Nxp_Tef810x_Mod03_CifTxnCtrlUnion_t CifTxnCtrl_ust;        /*## attribute CifTxnCtrl_ust */
  /**
    * RegisterName: cif_sel_sack_reg
    * AddressOffset: 0x020
    * ResetValue: 0x00003FFF
    * Description: Not to be changed.Always keep the deafult value for proper operation. 
	* MFIO Pad Selection register.
    */
    Nxp_Tef810x_Mod03_CifSelSackRegUnion_t CifSelSackReg_ust;        /*## attribute CifSelSackReg_ust */
  /**
    * RegisterName: cif_global_mfio_ctrl
    * AddressOffset: 0x024
    * ResetValue: 0x00000001
    * Description: Global Pad Control For Cif MFIO Pads.By default all the PADS are in High Impedance and Disabled  State.
	* Using this register all pads can be simultaneously enabled .  Override the individual  pad  enable bits
    */
    Nxp_Tef810x_Mod03_CifGlobalMfioCtrlUnion_t CifGlobalMfioCtrl_ust;        /*## attribute CifGlobalMfioCtrl_ust */
  /**
    * RegisterName: cif_mfio_ctrl1
    * AddressOffset: 0x028
    * ResetValue: 0x00131131
    * Description: CIF Pad Control register.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl1Union_t CifMfioCtrl1_ust;        /*## attribute CifMfioCtrl1_ust */
  /**
    * RegisterName: cif_mfio_ctrl2
    * AddressOffset: 0x02C
    * ResetValue: 0x00131131
    * Description: CIF mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl2Union_t CifMfioCtrl2_ust;        /*## attribute CifMfioCtrl2_ust */
  /**
    * RegisterName: cif_mfio_ctrl3
    * AddressOffset: 0x030
    * ResetValue: 0x00131131
    * Description: mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl3Union_t CifMfioCtrl3_ust;        /*## attribute CifMfioCtrl3_ust */
  /**
    * RegisterName: cif_mfio_ctrl4
    * AddressOffset: 0x034
    * ResetValue: 0x00131131
    * Description: mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl4Union_t CifMfioCtrl4_ust;        /*## attribute CifMfioCtrl4_ust */
  /**
    * RegisterName: cif_mfio_ctrl5
    * AddressOffset: 0x038
    * ResetValue: 0x00131131
    * Description: mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl5Union_t CifMfioCtrl5_ust;        /*## attribute CifMfioCtrl5_ust */
  /**
    * RegisterName: cif_mfio_ctrl6
    * AddressOffset: 0x03C
    * ResetValue: 0x00131131
    * Description: mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl6Union_t CifMfioCtrl6_ust;        /*## attribute CifMfioCtrl6_ust */
  /**
    * RegisterName: cif_mfio_ctrl7
    * AddressOffset: 0x040
    * ResetValue: 0x00131131
    * Description: mfio pad control.By default all the PADS are in High Impedance and Disabled  State.
    */
    Nxp_Tef810x_Mod03_CifMfioCtrl7Union_t CifMfioCtrl7_ust;        /*## attribute CifMfioCtrl7_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x044
    * ResetValue: 0x00000001
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x048
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x04C
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x050
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x054
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x058
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x05C
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x060
    * ResetValue: 0x04010401
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: CifTestModeControlReg
    * AddressOffset: 0x064
    * ResetValue: 0x00000FFF
    * Description: Used for Testing purpose.Only for internal validation and debug purpose.
    */
    Nxp_Tef810x_Mod03_CiftestmodecontrolregUnion_t Ciftestmodecontrolreg_ust;        /*## attribute Ciftestmodecontrolreg_ust */
  /**
    * RegisterName: WindowActiveSel
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: used for Tesing purpose.only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_WindowactiveselUnion_t Windowactivesel_ust;        /*## attribute Windowactivesel_ust */
  /**
    * RegisterName: master_idiv_ctrl
    * AddressOffset: 0x06C
    * ResetValue: 0x000400B0
    * Description: Serialiser clock divider control.
	* As part of  CIF  interface initialisation, the O/P frequency need to be set  and interface enabled . This register can be used for setting the O/P clock to the desired value.  
	* 
	* Dolphin allows dynamic decimation at individual chirp level over LVDS and CIF interface.  this means,  the O/P frequency of the interface and teh decimation values are coming from chirp.  However the values from chirp module will take efefct only when the chirp engine is triggered for data acquisition. till such time  the O/P frequncy control is driven from this register.  Please make sure that the first profile values used from chirp engine and the  IDIV setting are matched. to avoid  sudden frequency changes at the O/P
    */
    Nxp_Tef810x_Mod03_MasterIdivCtrlUnion_t MasterIdivCtrl_ust;        /*## attribute MasterIdivCtrl_ust */
  /**
    * RegisterName: pdc_shift_reg_idiv_ctrl
    * AddressOffset: 0x070
    * ResetValue: 0x00000002
    * Description: ADC data sampling control
    */
    Nxp_Tef810x_Mod03_PdcShiftRegIdivCtrlUnion_t PdcShiftRegIdivCtrl_ust;        /*## attribute PdcShiftRegIdivCtrl_ust */
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x074
    * ResetValue: 0x00000110
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: ref_cntr_init
    * AddressOffset: 0x078
    * ResetValue: 0x01E00028
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_RefCntrInitUnion_t RefCntrInit_ust;        /*## attribute RefCntrInit_ust */
  /**
    * RegisterName: freq_counter_start
    * AddressOffset: 0x07C
    * ResetValue: 0x00000100
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_FreqCounterStartUnion_t FreqCounterStart_ust;        /*## attribute FreqCounterStart_ust */
  /**
    * RegisterName: freq_counter_read_value
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;        /*## attribute FreqCounterReadValue_ust */
  /**
    * RegisterName: ref_counter_read_value
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600MHz frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod03_RefCounterReadValueUnion_t RefCounterReadValue_ust;        /*## attribute RefCounterReadValue_ust */
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x088
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: atb_set_trim
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: PDC Sync enable /disable
    */
    Nxp_Tef810x_Mod03_AtbSetTrimUnion_t AtbSetTrim_ust;        /*## attribute AtbSetTrim_ust */
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x098
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x09C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;
  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0x0A4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;
  /**
    * RegisterName: Reserved10
    * AddressOffset: 0x0A8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved10;

    uint32 gap01_au32[978];        /* gap 1 in register space */  /**
    * RegisterName: Reserved11
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved11;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00033301
    * Description: Module ID register
    */
    Nxp_Tef810x_Mod03_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod03_CifRegister_t;

#endif
