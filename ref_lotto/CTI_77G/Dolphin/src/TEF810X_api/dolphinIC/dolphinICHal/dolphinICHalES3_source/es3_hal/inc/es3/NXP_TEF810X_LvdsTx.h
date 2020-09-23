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
* @NXP_TEF810X_LvdsTx.h
*/
#ifndef NXP_TEF810X_LVDSTX_H
#define NXP_TEF810X_LVDSTX_H
#include "Std_Types.h"

#define LVDS_TX_MODULE_ADDRESS 0x01
/**
*NXP_TEF810X_MOD01_CLK_CHANNEL_DATA_U16
* RegisterName: MOD01_Clk_channel_data
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x000003E0
*/
#define NXP_TEF810X_MOD01_CLK_CHANNEL_DATA_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD01_IDLE_PATTERN_U16
* RegisterName: MOD01_Idle_pattern
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x000002AB
*/
#define NXP_TEF810X_MOD01_IDLE_PATTERN_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD01_CLOCKCHTXDATA12X1_U16
* RegisterName: MOD01_ClockChTxdata12x1
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00000FC0
*/
#define NXP_TEF810X_MOD01_CLOCKCHTXDATA12X1_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD01_ADCDEBUGMODE_U16
* RegisterName: MOD01_AdcDebugMode
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD01_ADCDEBUGMODE_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD01_TRANSMITPHASECONTROL_U16
* RegisterName: MOD01_TransmitPhaseControl
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000011
*/
#define NXP_TEF810X_MOD01_TRANSMITPHASECONTROL_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD01_MSBLSBCONTROL_U16
* RegisterName: MOD01_MsbLsbControl
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD01_MSBLSBCONTROL_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD01_LVDSCONFIGREG_U16
* RegisterName: MOD01_LvdsConfigReg
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x10000100
*/
#define NXP_TEF810X_MOD01_LVDSCONFIGREG_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD01_LVDS_CRC_CTRL1_U16
* RegisterName: MOD01_lvds_crc_ctrl1
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD01_LVDS_CRC_CTRL1_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD01_LVDS_CRC_CTRL2_U16
* RegisterName: MOD01_lvds_crc_ctrl2
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD01_LVDS_CRC_CTRL2_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD01_LVDS_CRC_CTRL3_U16
* RegisterName: MOD01_lvds_crc_ctrl3
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x0FF00110
*/
#define NXP_TEF810X_MOD01_LVDS_CRC_CTRL3_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD01_PDC_CONFIG_REG_U16
* RegisterName: MOD01_pdc_config_reg
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00A9A700
*/
#define NXP_TEF810X_MOD01_PDC_CONFIG_REG_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD01_LVDS_OUTPUT_INVERT_CTRL_U16
* RegisterName: MOD01_lvds_output_invert_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_LVDS_OUTPUT_INVERT_CTRL_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16
* RegisterName: MOD01_Lvds_tx_control
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_LVDS_TX_CONTROL_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD01_LVDS_SER_GLOBAL_PAD_CTRL_U16
* RegisterName: MOD01_lvds_ser_global_pad_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00001000
*/
#define NXP_TEF810X_MOD01_LVDS_SER_GLOBAL_PAD_CTRL_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL1_U16
* RegisterName: MOD01_lvds_ser_pad_ctrl1
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL1_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL2_U16
* RegisterName: MOD01_lvds_ser_pad_ctrl2
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL2_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL3_U16
* RegisterName: MOD01_lvds_ser_pad_ctrl3
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000131
*/
#define NXP_TEF810X_MOD01_LVDS_SER_PAD_CTRL3_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD01_ADCTESTDATAMUX_U16
* RegisterName: MOD01_ADCTestDataMux
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00007FFF
*/
#define NXP_TEF810X_MOD01_ADCTESTDATAMUX_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16
* RegisterName: MOD01_WindowActiveSel
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_WINDOWACTIVESEL_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD01_MASTER_IDIV_CTRL_U16
* RegisterName: MOD01_master_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x000400B0
*/
#define NXP_TEF810X_MOD01_MASTER_IDIV_CTRL_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD01_PDC_SHIFT_REG_IDIV_CTRL_U16
* RegisterName: MOD01_pdc_shift_reg_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x00000002
*/
#define NXP_TEF810X_MOD01_PDC_SHIFT_REG_IDIV_CTRL_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD01_REF_CNTR_INIT_U16
* RegisterName: MOD01_ref_cntr_init
* AccessMode: READWRITE
* AddressRange: 0x0078 - 0x007C
* ResetValue: 0x01E00028
*/
#define NXP_TEF810X_MOD01_REF_CNTR_INIT_U16 (uint16)0x0078
/**
*NXP_TEF810X_MOD01_FREQ_COUNTER_START_U16
* RegisterName: MOD01_freq_counter_start
* AccessMode: READWRITE
* AddressRange: 0x007C - 0x0080
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD01_FREQ_COUNTER_START_U16 (uint16)0x007C
/**
*NXP_TEF810X_MOD01_FREQ_COUNTER_READ_VALUE_U16
* RegisterName: MOD01_freq_counter_read_value
* AccessMode: READ
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_FREQ_COUNTER_READ_VALUE_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD01_REF_COUNTER_READ_VALUE_U16
* RegisterName: MOD01_ref_counter_read_value
* AccessMode: READ
* AddressRange: 0x0084 - 0x0088
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_REF_COUNTER_READ_VALUE_U16 (uint16)0x0084
/**
*NXP_TEF810X_MOD01_ATB_SET_TRIM_U16
* RegisterName: MOD01_atb_set_trim
* AccessMode: READWRITE
* AddressRange: 0x0094 - 0x0098
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD01_ATB_SET_TRIM_U16 (uint16)0x0094
/**
*NXP_TEF810X_MOD01_MODULEID_U16
* RegisterName: MOD01_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00013301
*/
#define NXP_TEF810X_MOD01_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod01_CLK_CHANNEL_DATABits_t
* RegisterName: Clk_channel_data
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: ClockChTxdata
	* Description: Frame Clock pattern to be send  on LVDS clock channel in 8b10b mode.
	*/
    uint32 Clockchtxdata: 10;        /*## attribute Clockchtxdata */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod01_ClkChannelDataBits_t;
    /**
* Nxp_Tef810x_Mod01_IDLE_PATTERNBits_t
* RegisterName: Idle_pattern
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: IdlePattern
	* Description: Idle pattern send in RAW  mode outside the valid data window. The last 10 bits are also used for Bypass 8b10b mode for clock-data recovery(only for internal validation and debug purpose)
	*/
    uint32 Idlepattern: 12;        /*## attribute Idlepattern */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod01_IdlePatternBits_t;
    /**
* Nxp_Tef810x_Mod01_CLOCKCHTXDATA12X1Bits_t
* RegisterName: ClockChTxdata12x1
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: ClockChTxdata12x1
	* Description: Frame Clock pattern to be send  on LVDS clock channel  in RAW mode.
	*/
    uint32 Clockchtxdata12X1: 12;        /*## attribute Clockchtxdata12X1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_lane_calibration_en
	* Description: Calibration Mode : When set , this bit ensures that all the LVDS lines start from zero irrespective of the frame_clock/bit_clock phase.Also enables the toggling frame_clock to appear on the output line even in frame_clock gated mode.
	* 0: Normal mode of opeartion.
	* 1: All LVDS Lines start from zero + disable the window_active based frame_clock gating
	*/
    uint32 LvdsLaneCalibrationEn: 1;        /*## attribute LvdsLaneCalibrationEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 15;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod01_Clockchtxdata12X1Bits_t;
    /**
* Nxp_Tef810x_Mod01_ADCDEBUGMODEBits_t
* RegisterName: AdcDebugMode
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: adc_debug_mode
	* Description: 0: LVDS in 8b10b mode
	* 1: LVDS in RAW mode(default)
	*/
    uint32 AdcDebugMode: 1;        /*## attribute AdcDebugMode */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 27;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod01_AdcdebugmodeBits_t;
    /**
* Nxp_Tef810x_Mod01_TRANSMITPHASECONTROLBits_t
* RegisterName: TransmitPhaseControl
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: bit_clk_phase
	* Description: Within a frame boundary
	* 0:  first serial bit starts with bit_clk Fall edge
	* 1: first serial bit starts with bit_clk rise edge.
	*/
    uint32 BitClkPhase: 1;        /*## attribute BitClkPhase */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: frame_clk_phase
	* Description: Within a frame boundary
	* 0: Serial bit starts from Rise edge of frame_clk
	* 1: Serial bit starts from Fall edge of frame clk.
	*/
    uint32 FrameClkPhase: 1;        /*## attribute FrameClkPhase */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod01_TransmitphasecontrolBits_t;
    /**
* Nxp_Tef810x_Mod01_MSBLSBCONTROLBits_t
* RegisterName: MsbLsbControl
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: msb_first
	* Description: LSB/MSB of the Parallel word send fisrt:
	* 0:LSB first
	* 1: MSB first
	*/
    uint32 MsbFirst: 1;        /*## attribute MsbFirst */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod01_MsblsbcontrolBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDSCONFIGREGBits_t
* RegisterName: LvdsConfigReg
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: lvds_crc_control
	* Description: 00 = no CRC,No packet footer.
	* 01 = normal 12x1 crc and resulting crc appended to packet Footer.
	* 10 = 16x1 crc and and resulting crc appended to packet Footer. 
	* 11 = 16x1 crc and and resulting crc appended to packet Footer.
	*/
    uint32 LvdsCrcControl: 2;        /*## attribute LvdsCrcControl */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: PacketEn
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data
	* Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the LVDS Link)
	*/
    uint32 Packeten: 1;        /*## attribute Packeten */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: LvdsLineCntReg
	* Description: Applicable only when Header (PacketEN = ?1?) is enabled. 
	* This value is loaded to the counter which keep track of the current chirp number. Current chip number will be sent as a part of the packet header.Chirp no increments from 1 ,once it reaches the regiter value it wiil get re-initialised to 1.
	* Leave as reset if not needed explicitly.
	*/
    uint32 Lvdslinecntreg: 12;        /*## attribute Lvdslinecntreg */
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats before parallel to serial conversion.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: data_valid_delay_ctrl
	* Description: Data valid signals comes through an MFIO pad.We can delay the data valid w.r.t to internal bit clock. 
	* 00 : No delay
	* 01 : 1 clk delay
	* 10 : 2 clock delay
	* 11 :3 clock delay
	* Internal bit clock sclaes with different decimation factor.(eg : 480/240/120/60 MHz for RAW mode and 600/300/150/75/37.5 MHz for 8b10b mode)
	* For practical purpose, reset value is OK
	*/
    uint32 DataValidDelayCtrl: 2;        /*## attribute DataValidDelayCtrl */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: frame_clk_gating
	* Description: Frame clock can be gated outside the valid data window.
	* 0: frame_clk is always free running 
	* 1: frame_clk is gated outside data_valid.
	*/
    uint32 FrameClkGating: 1;        /*## attribute FrameClkGating */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod01_LvdsconfigregBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_CRC_CTRL1Bits_t
* RegisterName: lvds_crc_ctrl1
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod01_LvdsCrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_CRC_CTRL2Bits_t
* RegisterName: lvds_crc_ctrl2
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC is EX-OR ed with this value..It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod01_LvdsCrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_CRC_CTRL3Bits_t
* RegisterName: lvds_crc_ctrl3
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
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
	* 1: Bit order is swapped around the middle of the input 32 bit data(default)..It is a CRC Engine configuration parameter
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
	* 1 : Bit order is swapped around the middle of the CRC result.(default)..It is a CRC Engine configuration parameter
	*/
    uint32 ReflectOutput: 1;        /*## attribute ReflectOutput */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: crc_16x1_frame_patttern
	* Description: 32 bit CRC can be send as
	* a) three 12x1 formatb) two 16x1 format.This register holds the frame clock pattern(duty cycle) while sending crc in 16x1 format
	*/
    uint32 Crc16X1FramePatttern: 16;        /*## attribute Crc16X1FramePatttern */
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
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod01_LvdsCrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod01_PDC_CONFIG_REGBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: make_output_unsigned
	* Description: 0: PDC output is Signed 12 bit
	* 1: PDC output is UnSigned 12 bit
	*/
    uint32 MakeOutputUnsigned: 1;        /*## attribute MakeOutputUnsigned */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: mask_input_w_WA
	* Description: 0: always process input data.PDC will process all the input samples irrespective of the window active from timing engine
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
}Nxp_Tef810x_Mod01_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_OUTPUT_INVERT_CTRLBits_t
* RegisterName: lvds_output_invert_ctrl
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: invert_lvds_outputs
	* Description: [6] : Invert bit_clk  -> 0 : no invert & 1 : invert 
	* [5]: Invert frame_clk  -> 0 : no invert & 1 : invert 
	* [4]: Invert ser3          -> 0 : no invert & 1 : invert 
	* [3]: Invert ser2           -> 0 : no invert & 1 : invert 
	* [2]: Invert ser1           -> 0 : no invert & 1 : invert 
	* [1]: Invert ser0           -> 0 : no invert & 1 : invert 
	* [0]: Invert data_valid    -> 0 : no invert & 1 : invert
	*/
    uint32 InvertLvdsOutputs: 7;        /*## attribute InvertLvdsOutputs */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_TX_CONTROLBits_t
* RegisterName: Lvds_tx_control
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: SerialiserTxEn
	* Description: Transmission Enable for  LVDS Channels 
	* [0] : ch0 enable: 1- enable & 0 - disable
	* [1] : ch1 enable: 1- enable & 0 - disable
	* [2] : ch2 enable: 1- enable & 0 - disable
	* [3] : ch3 enable: 1- enable & 0 - disable
	*/
    uint32 Serialisertxen: 4;        /*## attribute Serialisertxen */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod01_LvdsTxControlBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_SER_GLOBAL_PAD_CTRLBits_t
* RegisterName: lvds_ser_global_pad_ctrl
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
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
	* BitsName: lvds_ser_global_pad_epwr
	* Description: Global LVDS driver  Power down (Applicable for all pads)
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerGlobalPadEpwr: 1;        /*## attribute LvdsSerGlobalPadEpwr */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_ser_global_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerGlobalPadEpd: 1;        /*## attribute LvdsSerGlobalPadEpd */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_ser_global_mfio_pad_en
	* Description: Global pad enable/disable for  LVDS data interface
	* 
	* 0: Pad enabled
	* 1: Pad disabled.
	*/
    uint32 LvdsSerGlobalMfioPadEn: 1;        /*## attribute LvdsSerGlobalMfioPadEn */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 19;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_SER_PAD_CTRL1Bits_t
* RegisterName: lvds_ser_pad_ctrl1
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
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
	* BitsName: lvds_ser_adc1_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc1DataPadEpwr: 1;        /*## attribute LvdsSerAdc1DataPadEpwr */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_ser_adc1_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc1DataPadEpd: 1;        /*## attribute LvdsSerAdc1DataPadEpd */
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
	* BitsName: lvds_ser_adc2_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc2DataPadEpwr: 1;        /*## attribute LvdsSerAdc2DataPadEpwr */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: lvds_ser_adc2_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc2DataPadEpd: 1;        /*## attribute LvdsSerAdc2DataPadEpd */
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
    uint32 Reserved9: 3;        /*## attribute Reserved9 */
   /**
	* BitsName: lvds_ser_adc3_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc3DataPadEpwr: 1;        /*## attribute LvdsSerAdc3DataPadEpwr */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 2;        /*## attribute Reserved10 */
   /**
	* BitsName: lvds_ser_adc3_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc3DataPadEpd: 1;        /*## attribute LvdsSerAdc3DataPadEpd */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_SER_PAD_CTRL2Bits_t
* RegisterName: lvds_ser_pad_ctrl2
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
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
	* BitsName: lvds_ser_adc4_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc4DataPadEpwr: 1;        /*## attribute LvdsSerAdc4DataPadEpwr */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_ser_adc4_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc4DataPadEpd: 1;        /*## attribute LvdsSerAdc4DataPadEpd */
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
	* BitsName: lvds_bit_clk_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsBitClkPadEpwr: 1;        /*## attribute LvdsBitClkPadEpwr */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: lvds_bit_clk_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsBitClkPadEpd: 1;        /*## attribute LvdsBitClkPadEpd */
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
    uint32 Reserved9: 3;        /*## attribute Reserved9 */
   /**
	* BitsName: lvds_frame_clk_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsFrameClkPadEpwr: 1;        /*## attribute LvdsFrameClkPadEpwr */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 2;        /*## attribute Reserved10 */
   /**
	* BitsName: lvds_frame_clk_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsFrameClkPadEpd: 1;        /*## attribute LvdsFrameClkPadEpd */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod01_LVDS_SER_PAD_CTRL3Bits_t
* RegisterName: lvds_ser_pad_ctrl3
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: lvds_cif_datavalid_mfio_en
	* Description: Data valid(mfio) pad enable/disable:
	* Disable Output Driver(Active High)
	* 0: Pad enabled
	* 1: Pad disabled.
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
	* 0          1           1       
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	* Leave as reset if not needed explicitly.
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
	* BitsName: lvds_cif_datavalid_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 LvdsCifDatavalidMfioEpd: 1;        /*## attribute LvdsCifDatavalidMfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs0
	* Description: speed selection bit 0
	*/
    uint32 LvdsCifDatavalidMfioEhs0: 1;        /*## attribute LvdsCifDatavalidMfioEhs0 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs1
	* Description: MFIO Speed Selection [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz"
	*/
    uint32 LvdsCifDatavalidMfioEhs1: 1;        /*## attribute LvdsCifDatavalidMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_vref_eprbias
	* Description: LVDS pad Voltage Reference Circuit enable/disable
	* 0: Disable reference voltge generator.
	* 1: Enable reference voltge generator.
	*/
    uint32 LvdsVrefEprbias: 1;        /*## attribute LvdsVrefEprbias */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_set_trim_r_n
	* Description: This is to program the reference voltage (common mode LVDS voltage)  generator inside serialiser ana, which generates lvds_vra (1.2 v common mode voltage )  for the  LVDS pads.
	* To generate 1.2V  lvds_set_trim_r_n  should be  0x1F
	*/
    uint32 LvdsSetTrimRN: 6;        /*## attribute LvdsSetTrimRN */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_cntrl
	* Description: lvds_cntrl[0] -> LPWR of all LVDS Pads. Enable Low power LVDS operation(active high).
	* 
	* lvds_cntrl[3] -> adc_data_streaming mode enable:Used for ADC validation
	* 0: IDLE pattern is send outside the valid data window
	* 1:ADC data is send outside the valid data window.
	* 
	* lvds_cntrl[2:1] -> Spare bits
	* Leave as reset if not needed explicitly.
	*/
    uint32 LvdsCntrl: 4;        /*## attribute LvdsCntrl */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod01_ADCTESTDATAMUXBits_t
* RegisterName: ADCTestDataMux
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: lvds_testmode_test_data
	* Description: Test data input to LVDS buffer
	*/
    uint32 LvdsTestmodeTestData: 15;        /*## attribute LvdsTestmodeTestData */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_testmode_en
	* Description: 0: PDC functional data as input to LVDS Channel
	* 1: Test data is input to LVDS Channel
	*/
    uint32 LvdsTestmodeEn: 1;        /*## attribute LvdsTestmodeEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_testmode_data_sel
	* Description: 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 LvdsTestmodeDataSel: 2;        /*## attribute LvdsTestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_testmode_skip_pdc
	* Description: 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 LvdsTestmodeSkipPdc: 1;        /*## attribute LvdsTestmodeSkipPdc */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod01_AdctestdatamuxBits_t;
    /**
* Nxp_Tef810x_Mod01_WINDOWACTIVESELBits_t
* RegisterName: WindowActiveSel
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: window_active_sel
	* Description: 0: window active from register set to '0'
	* 1: window active from register set to '1'
	*/
    uint32 WindowActiveSel: 1;        /*## attribute WindowActiveSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: window_active_reg_control
	* Description: 0: Window active is from timing engine
	* 1: window active from register filed.
	*/
    uint32 WindowActiveRegControl: 1;        /*## attribute WindowActiveRegControl */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod01_WindowactiveselBits_t;
    /**
* Nxp_Tef810x_Mod01_MASTER_IDIV_CTRLBits_t
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
	* Valid combination are given below.
	* ?00_0000? ? Bypass        o/p clock = 480 MHz
	* ?00_0001? ? Divide by 2   o/p clock = 240 MHz
	* ?00_0010? ? Divide by 3   o/p clock = 160 MHz
	* ?00_0011? ? Divide by 4   o/p clock = 120 MHz
	* ?.
	* ?11_1111? ? Divide by 64
	* By defualt LVDS o/p clock is set to 40 MHz.Software can use this field for getting the desired bit  clock at the o/p before the correct decimation factor comes from chirp.After the first profile load, the design will  always selects idiv from LUT based on decimation
	* 
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser,the internal mux will again select the idiv value from register till the next profile load comes.
	*/
    uint32 MasterIdivValue: 6;        /*## attribute MasterIdivValue */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: This bit can be used to tune the LVDS o/p clock to required frequency before the first Profile Load Signal or required Decimation factor comes from Chirp.After the first profile load, the design will overide this selection and always selects idiv from LUT based on decimation.
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the register.
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser, the internal mux will again select the idiv value from register till the next profile load comes.
	*/
    uint32 MasterIdivSelRegLut: 1;        /*## attribute MasterIdivSelRegLut */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: master_idiv_blk_cnt
	* Description: Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz
	*/
    uint32 MasterIdivBlkCnt: 6;        /*## attribute MasterIdivBlkCnt */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 10;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod01_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_PDC_SHIFT_REG_IDIV_CTRLBits_t
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
	* 
	* Use model:  The value to be used has to come form Validation . The end user can use  the proposed value from validation
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
	* 1: Detect adc clk neg edge  for generating the sampling pulse
	* 
	* 
	* Use model:  The value to be used has to come form Validation . The end user can use  the proposed value from validation
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
}Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_REF_CNTR_INITBits_t
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
	* Description: This is applicable when the freq counter trigger is based on window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
}Nxp_Tef810x_Mod01_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod01_FREQ_COUNTER_STARTBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0xREADWRITE - 0x07C
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: freq_start
	* Description: Trigger  frequency counter
	* 0 = idle, 1 = Trigger frequency counter
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
}Nxp_Tef810x_Mod01_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod01_FREQ_COUNTER_READ_VALUEBits_t
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
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 11;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod01_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod01_REF_COUNTER_READ_VALUEBits_t
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
}Nxp_Tef810x_Mod01_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod01_ATB_SET_TRIMBits_t
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
}Nxp_Tef810x_Mod01_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod01_MODULEIDBits_t
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
}Nxp_Tef810x_Mod01_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod01_ClkChannelDataBits_t
* RegisterName: Clk_channel_data
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x000003E0
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: ClockChTxdata
	* Description: Frame Clock pattern to be send  on LVDS clock channel in 8b10b mode.
	*/
    uint32 Clockchtxdata: 10;        /*## attribute Clockchtxdata */
}Nxp_Tef810x_Mod01_ClkChannelDataBits_t;
    /**
* Nxp_Tef810x_Mod01_IdlePatternBits_t
* RegisterName: Idle_pattern
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x000002AB
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: IdlePattern
	* Description: Idle pattern send in RAW  mode outside the valid data window. The last 10 bits are also used for Bypass 8b10b mode for clock-data recovery(only for internal validation and debug purpose)
	*/
    uint32 Idlepattern: 12;        /*## attribute Idlepattern */
}Nxp_Tef810x_Mod01_IdlePatternBits_t;
    /**
* Nxp_Tef810x_Mod01_Clockchtxdata12X1Bits_t
* RegisterName: ClockChTxdata12x1
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00000FC0
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_lane_calibration_en
	* Description: Calibration Mode : When set , this bit ensures that all the LVDS lines start from zero irrespective of the frame_clock/bit_clock phase.Also enables the toggling frame_clock to appear on the output line even in frame_clock gated mode.
	* 0: Normal mode of opeartion.
	* 1: All LVDS Lines start from zero + disable the window_active based frame_clock gating
	*/
    uint32 LvdsLaneCalibrationEn: 1;        /*## attribute LvdsLaneCalibrationEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: ClockChTxdata12x1
	* Description: Frame Clock pattern to be send  on LVDS clock channel  in RAW mode.
	*/
    uint32 Clockchtxdata12X1: 12;        /*## attribute Clockchtxdata12X1 */
}Nxp_Tef810x_Mod01_Clockchtxdata12X1Bits_t;
    /**
* Nxp_Tef810x_Mod01_AdcdebugmodeBits_t
* RegisterName: AdcDebugMode
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: adc_debug_mode
	* Description: 0: LVDS in 8b10b mode
	* 1: LVDS in RAW mode(default)
	*/
    uint32 AdcDebugMode: 1;        /*## attribute AdcDebugMode */
}Nxp_Tef810x_Mod01_AdcdebugmodeBits_t;
    /**
* Nxp_Tef810x_Mod01_TransmitphasecontrolBits_t
* RegisterName: TransmitPhaseControl
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
	* BitsName: frame_clk_phase
	* Description: Within a frame boundary
	* 0: Serial bit starts from Rise edge of frame_clk
	* 1: Serial bit starts from Fall edge of frame clk.
	*/
    uint32 FrameClkPhase: 1;        /*## attribute FrameClkPhase */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: bit_clk_phase
	* Description: Within a frame boundary
	* 0:  first serial bit starts with bit_clk Fall edge
	* 1: first serial bit starts with bit_clk rise edge.
	*/
    uint32 BitClkPhase: 1;        /*## attribute BitClkPhase */
}Nxp_Tef810x_Mod01_TransmitphasecontrolBits_t;
    /**
* Nxp_Tef810x_Mod01_MsblsbcontrolBits_t
* RegisterName: MsbLsbControl
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: msb_first
	* Description: LSB/MSB of the Parallel word send fisrt:
	* 0:LSB first
	* 1: MSB first
	*/
    uint32 MsbFirst: 1;        /*## attribute MsbFirst */
}Nxp_Tef810x_Mod01_MsblsbcontrolBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsconfigregBits_t
* RegisterName: LvdsConfigReg
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x10000100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: frame_clk_gating
	* Description: Frame clock can be gated outside the valid data window.
	* 0: frame_clk is always free running 
	* 1: frame_clk is gated outside data_valid.
	*/
    uint32 FrameClkGating: 1;        /*## attribute FrameClkGating */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: data_valid_delay_ctrl
	* Description: Data valid signals comes through an MFIO pad.We can delay the data valid w.r.t to internal bit clock. 
	* 00 : No delay
	* 01 : 1 clk delay
	* 10 : 2 clock delay
	* 11 :3 clock delay
	* Internal bit clock sclaes with different decimation factor.(eg : 480/240/120/60 MHz for RAW mode and 600/300/150/75/37.5 MHz for 8b10b mode)
	* For practical purpose, reset value is OK
	*/
    uint32 DataValidDelayCtrl: 2;        /*## attribute DataValidDelayCtrl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats before parallel to serial conversion.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
   /**
	* BitsName: LvdsLineCntReg
	* Description: Applicable only when Header (PacketEN = ?1?) is enabled. 
	* This value is loaded to the counter which keep track of the current chirp number. Current chip number will be sent as a part of the packet header.Chirp no increments from 1 ,once it reaches the regiter value it wiil get re-initialised to 1.
	* Leave as reset if not needed explicitly.
	*/
    uint32 Lvdslinecntreg: 12;        /*## attribute Lvdslinecntreg */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: PacketEn
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data
	* Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the LVDS Link)
	*/
    uint32 Packeten: 1;        /*## attribute Packeten */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_crc_control
	* Description: 00 = no CRC,No packet footer.
	* 01 = normal 12x1 crc and resulting crc appended to packet Footer.
	* 10 = 16x1 crc and and resulting crc appended to packet Footer. 
	* 11 = 16x1 crc and and resulting crc appended to packet Footer.
	*/
    uint32 LvdsCrcControl: 2;        /*## attribute LvdsCrcControl */
}Nxp_Tef810x_Mod01_LvdsconfigregBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl1Bits_t
* RegisterName: lvds_crc_ctrl1
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod01_LvdsCrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl2Bits_t
* RegisterName: lvds_crc_ctrl2
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC is EX-OR ed with this value..It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod01_LvdsCrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl3Bits_t
* RegisterName: lvds_crc_ctrl3
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x0FF00110
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: dummy_zero_position
	* Description: CRC is calculated using a 32-bit input CRC engine.Two consecutive adc samples con-catinated [data1,4'b0000 : data0,4'b0000] and given to the engine.Zero padding can be done at LSB side or MSB side.
	* 
	* 0: Zero padding at LSB position (default)
	* 1: Zero padding at MSB position
	*/
    uint32 DummyZeroPosition: 1;        /*## attribute DummyZeroPosition */
   /**
	* BitsName: crc_16x1_frame_patttern
	* Description: 32 bit CRC can be send as
	* a) three 12x1 formatb) two 16x1 format.This register holds the frame clock pattern(duty cycle) while sending crc in 16x1 format
	*/
    uint32 Crc16X1FramePatttern: 16;        /*## attribute Crc16X1FramePatttern */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: reflect_output
	* Description: For reflecting the final CRC ouput bits before final XOR .
	* 0 : No swapping 
	* 1 : Bit order is swapped around the middle of the CRC result.(default)..It is a CRC Engine configuration parameter
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
	* 1: Bit order is swapped around the middle of the input 32 bit data(default)..It is a CRC Engine configuration parameter
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
}Nxp_Tef810x_Mod01_LvdsCrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod01_PdcConfigRegBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0x044 - 0x048
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
	* Description: 0: always process input data.PDC will process all the input samples irrespective of the window active from timing engine
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
	* Description: 0: PDC output is Signed 12 bit
	* 1: PDC output is UnSigned 12 bit
	*/
    uint32 MakeOutputUnsigned: 1;        /*## attribute MakeOutputUnsigned */
}Nxp_Tef810x_Mod01_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlBits_t
* RegisterName: lvds_output_invert_ctrl
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: invert_lvds_outputs
	* Description: [6] : Invert bit_clk  -> 0 : no invert & 1 : invert 
	* [5]: Invert frame_clk  -> 0 : no invert & 1 : invert 
	* [4]: Invert ser3          -> 0 : no invert & 1 : invert 
	* [3]: Invert ser2           -> 0 : no invert & 1 : invert 
	* [2]: Invert ser1           -> 0 : no invert & 1 : invert 
	* [1]: Invert ser0           -> 0 : no invert & 1 : invert 
	* [0]: Invert data_valid    -> 0 : no invert & 1 : invert
	*/
    uint32 InvertLvdsOutputs: 7;        /*## attribute InvertLvdsOutputs */
}Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsTxControlBits_t
* RegisterName: Lvds_tx_control
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: SerialiserTxEn
	* Description: Transmission Enable for  LVDS Channels 
	* [0] : ch0 enable: 1- enable & 0 - disable
	* [1] : ch1 enable: 1- enable & 0 - disable
	* [2] : ch2 enable: 1- enable & 0 - disable
	* [3] : ch3 enable: 1- enable & 0 - disable
	*/
    uint32 Serialisertxen: 4;        /*## attribute Serialisertxen */
}Nxp_Tef810x_Mod01_LvdsTxControlBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlBits_t
* RegisterName: lvds_ser_global_pad_ctrl
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_ser_global_mfio_pad_en
	* Description: Global pad enable/disable for  LVDS data interface
	* 
	* 0: Pad enabled
	* 1: Pad disabled.
	*/
    uint32 LvdsSerGlobalMfioPadEn: 1;        /*## attribute LvdsSerGlobalMfioPadEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_ser_global_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerGlobalPadEpd: 1;        /*## attribute LvdsSerGlobalPadEpd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_ser_global_pad_epwr
	* Description: Global LVDS driver  Power down (Applicable for all pads)
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerGlobalPadEpwr: 1;        /*## attribute LvdsSerGlobalPadEpwr */
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
}Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Bits_t
* RegisterName: lvds_ser_pad_ctrl1
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: lvds_ser_adc3_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc3DataPadEpd: 1;        /*## attribute LvdsSerAdc3DataPadEpd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_ser_adc3_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc3DataPadEpwr: 1;        /*## attribute LvdsSerAdc3DataPadEpwr */
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
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_ser_adc2_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc2DataPadEpd: 1;        /*## attribute LvdsSerAdc2DataPadEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_ser_adc2_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc2DataPadEpwr: 1;        /*## attribute LvdsSerAdc2DataPadEpwr */
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
	* BitsName: lvds_ser_adc1_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc1DataPadEpd: 1;        /*## attribute LvdsSerAdc1DataPadEpd */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 3;        /*## attribute Reserved8 */
   /**
	* BitsName: lvds_ser_adc1_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc1DataPadEpwr: 1;        /*## attribute LvdsSerAdc1DataPadEpwr */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 3;        /*## attribute Reserved9 */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 1;        /*## attribute Reserved10 */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Bits_t
* RegisterName: lvds_ser_pad_ctrl2
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: lvds_frame_clk_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsFrameClkPadEpd: 1;        /*## attribute LvdsFrameClkPadEpd */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_frame_clk_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsFrameClkPadEpwr: 1;        /*## attribute LvdsFrameClkPadEpwr */
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
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_bit_clk_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsBitClkPadEpd: 1;        /*## attribute LvdsBitClkPadEpd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_bit_clk_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsBitClkPadEpwr: 1;        /*## attribute LvdsBitClkPadEpwr */
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
	* BitsName: lvds_ser_adc4_data_pad_epd
	* Description: Not Used
	*/
    uint32 LvdsSerAdc4DataPadEpd: 1;        /*## attribute LvdsSerAdc4DataPadEpd */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 3;        /*## attribute Reserved8 */
   /**
	* BitsName: lvds_ser_adc4_data_pad_epwr
	* Description: Transmitter Power down. 
	* 1: normal operation;
	* 0: powered down.
	*/
    uint32 LvdsSerAdc4DataPadEpwr: 1;        /*## attribute LvdsSerAdc4DataPadEpwr */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 3;        /*## attribute Reserved9 */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 1;        /*## attribute Reserved10 */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Bits_t
* RegisterName: lvds_ser_pad_ctrl3
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000131
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_cntrl
	* Description: lvds_cntrl[0] -> LPWR of all LVDS Pads. Enable Low power LVDS operation(active high).
	* 
	* lvds_cntrl[3] -> adc_data_streaming mode enable:Used for ADC validation
	* 0: IDLE pattern is send outside the valid data window
	* 1:ADC data is send outside the valid data window.
	* 
	* lvds_cntrl[2:1] -> Spare bits
	* Leave as reset if not needed explicitly.
	*/
    uint32 LvdsCntrl: 4;        /*## attribute LvdsCntrl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_set_trim_r_n
	* Description: This is to program the reference voltage (common mode LVDS voltage)  generator inside serialiser ana, which generates lvds_vra (1.2 v common mode voltage )  for the  LVDS pads.
	* To generate 1.2V  lvds_set_trim_r_n  should be  0x1F
	*/
    uint32 LvdsSetTrimRN: 6;        /*## attribute LvdsSetTrimRN */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_vref_eprbias
	* Description: LVDS pad Voltage Reference Circuit enable/disable
	* 0: Disable reference voltge generator.
	* 1: Enable reference voltge generator.
	*/
    uint32 LvdsVrefEprbias: 1;        /*## attribute LvdsVrefEprbias */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs1
	* Description: MFIO Speed Selection [ehs1 ehs0] :
	* [0         0] : 20 MHz
	* [0         1] : 40 MHz
	* [1         0] : 85 MHz
	* [1         1] : 125 MHz"
	*/
    uint32 LvdsCifDatavalidMfioEhs1: 1;        /*## attribute LvdsCifDatavalidMfioEhs1 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_ehs0
	* Description: speed selection bit 0
	*/
    uint32 LvdsCifDatavalidMfioEhs0: 1;        /*## attribute LvdsCifDatavalidMfioEhs0 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_epd
	* Description: Enable weak pull-down(active high)
	* 1: weak pull-down Enabled
	* 0: weak pull-down Disabled
	*/
    uint32 LvdsCifDatavalidMfioEpd: 1;        /*## attribute LvdsCifDatavalidMfioEpd */
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
	* 0          1           1       
	* 
	* 1          0           0       Weak pull-up
	* 1          0           1       Weak pull-down
	* 1          1           0       High impedance (Analog I/O)
	* 1          1           1       Weak pull-down
	* Leave as reset if not needed explicitly.
	*/
    uint32 LvdsCifDatavalidMfioEnzi: 1;        /*## attribute LvdsCifDatavalidMfioEnzi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: lvds_cif_datavalid_mfio_en
	* Description: Data valid(mfio) pad enable/disable:
	* Disable Output Driver(Active High)
	* 0: Pad enabled
	* 1: Pad disabled.
	*/
    uint32 LvdsCifDatavalidMfioEn: 1;        /*## attribute LvdsCifDatavalidMfioEn */
}Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod01_AdctestdatamuxBits_t
* RegisterName: ADCTestDataMux
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00007FFF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: lvds_testmode_skip_pdc
	* Description: 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 LvdsTestmodeSkipPdc: 1;        /*## attribute LvdsTestmodeSkipPdc */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: lvds_testmode_data_sel
	* Description: 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 LvdsTestmodeDataSel: 2;        /*## attribute LvdsTestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: lvds_testmode_en
	* Description: 0: PDC functional data as input to LVDS Channel
	* 1: Test data is input to LVDS Channel
	*/
    uint32 LvdsTestmodeEn: 1;        /*## attribute LvdsTestmodeEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 5;        /*## attribute Reserved3 */
   /**
	* BitsName: lvds_testmode_test_data
	* Description: Test data input to LVDS buffer
	*/
    uint32 LvdsTestmodeTestData: 15;        /*## attribute LvdsTestmodeTestData */
}Nxp_Tef810x_Mod01_AdctestdatamuxBits_t;
    /**
* Nxp_Tef810x_Mod01_WindowactiveselBits_t
* RegisterName: WindowActiveSel
* 
* AddressRange: 0x064 - 0x068
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
	* Description: 0: Window active is from timing engine
	* 1: window active from register filed.
	*/
    uint32 WindowActiveRegControl: 1;        /*## attribute WindowActiveRegControl */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: window_active_sel
	* Description: 0: window active from register set to '0'
	* 1: window active from register set to '1'
	*/
    uint32 WindowActiveSel: 1;        /*## attribute WindowActiveSel */
}Nxp_Tef810x_Mod01_WindowactiveselBits_t;
    /**
* Nxp_Tef810x_Mod01_MasterIdivCtrlBits_t
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
	* Description: Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz
	*/
    uint32 MasterIdivBlkCnt: 6;        /*## attribute MasterIdivBlkCnt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: This bit can be used to tune the LVDS o/p clock to required frequency before the first Profile Load Signal or required Decimation factor comes from Chirp.After the first profile load, the design will overide this selection and always selects idiv from LUT based on decimation.
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the register.
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser, the internal mux will again select the idiv value from register till the next profile load comes.
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
	* Valid combination are given below.
	* ?00_0000? ? Bypass        o/p clock = 480 MHz
	* ?00_0001? ? Divide by 2   o/p clock = 240 MHz
	* ?00_0010? ? Divide by 3   o/p clock = 160 MHz
	* ?00_0011? ? Divide by 4   o/p clock = 120 MHz
	* ?.
	* ?11_1111? ? Divide by 64
	* By defualt LVDS o/p clock is set to 40 MHz.Software can use this field for getting the desired bit  clock at the o/p before the correct decimation factor comes from chirp.After the first profile load, the design will  always selects idiv from LUT based on decimation
	* 
	* Note : When a soft reset or functional(from cc) reset is applied to the serialiser,the internal mux will again select the idiv value from register till the next profile load comes.
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
}Nxp_Tef810x_Mod01_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlBits_t
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
	* 1: Detect adc clk neg edge  for generating the sampling pulse
	* 
	* 
	* Use model:  The value to be used has to come form Validation . The end user can use  the proposed value from validation
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
	* 
	* Use model:  The value to be used has to come form Validation . The end user can use  the proposed value from validation
	*/
    uint32 AdcDataSamplingPoint: 3;        /*## attribute AdcDataSamplingPoint */
}Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod01_RefCntrInitBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0x078 - 0x07C
* ResetValue: 0x01E00028
*/
typedef struct  {
   /**
	* BitsName: ideal_480_count_value
	* Description: This is applicable when the freq counter trigger is based on window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
   /**
	* BitsName: ref_count_value
	* Description: value for the reference count time (40 MHz= 25 ns base time) default is d'40. This is used as reference count in both spi triggered mode and window_active triggered mode
	*/
    uint32 RefCountValue: 16;        /*## attribute RefCountValue */
}Nxp_Tef810x_Mod01_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod01_FreqCounterStartBits_t
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
	* Description: Trigger  frequency counter
	* 0 = idle, 1 = Trigger frequency counter
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
}Nxp_Tef810x_Mod01_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod01_FreqCounterReadValueBits_t
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
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
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
}Nxp_Tef810x_Mod01_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod01_RefCounterReadValueBits_t
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
}Nxp_Tef810x_Mod01_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod01_AtbSetTrimBits_t
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
}Nxp_Tef810x_Mod01_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod01_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00013301
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
}Nxp_Tef810x_Mod01_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod01_ClkChannelDataUnion_t
* Nxp_Tef810x_Mod01_ClkChannelDataUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_ClkChannelDataBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_ClkChannelDataUnion_t;
/**
* Nxp_Tef810x_Mod01_IdlePatternUnion_t
* Nxp_Tef810x_Mod01_IdlePatternUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_IdlePatternBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_IdlePatternUnion_t;
/**
* Nxp_Tef810x_Mod01_Clockchtxdata12X1Union_t
* Nxp_Tef810x_Mod01_Clockchtxdata12X1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_Clockchtxdata12X1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_Clockchtxdata12X1Union_t;
/**
* Nxp_Tef810x_Mod01_AdcdebugmodeUnion_t
* Nxp_Tef810x_Mod01_AdcdebugmodeUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_AdcdebugmodeBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_AdcdebugmodeUnion_t;
/**
* Nxp_Tef810x_Mod01_TransmitphasecontrolUnion_t
* Nxp_Tef810x_Mod01_TransmitphasecontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_TransmitphasecontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_TransmitphasecontrolUnion_t;
/**
* Nxp_Tef810x_Mod01_MsblsbcontrolUnion_t
* Nxp_Tef810x_Mod01_MsblsbcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_MsblsbcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_MsblsbcontrolUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsconfigregUnion_t
* Nxp_Tef810x_Mod01_LvdsconfigregUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsconfigregBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsconfigregUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl1Union_t
* Nxp_Tef810x_Mod01_LvdsCrcCtrl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsCrcCtrl1Union_t;
/**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl2Union_t
* Nxp_Tef810x_Mod01_LvdsCrcCtrl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsCrcCtrl2Union_t;
/**
* Nxp_Tef810x_Mod01_LvdsCrcCtrl3Union_t
* Nxp_Tef810x_Mod01_LvdsCrcCtrl3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsCrcCtrl3Union_t;
/**
* Nxp_Tef810x_Mod01_PdcConfigRegUnion_t
* Nxp_Tef810x_Mod01_PdcConfigRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_PdcConfigRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_PdcConfigRegUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlUnion_t
* Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsTxControlUnion_t
* Nxp_Tef810x_Mod01_LvdsTxControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsTxControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsTxControlUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlUnion_t
* Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlUnion_t;
/**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Union_t
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Union_t;
/**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Union_t
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Union_t;
/**
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Union_t
* Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Union_t;
/**
* Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t
* Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_AdctestdatamuxBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t;
/**
* Nxp_Tef810x_Mod01_WindowactiveselUnion_t
* Nxp_Tef810x_Mod01_WindowactiveselUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_WindowactiveselBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_WindowactiveselUnion_t;
/**
* Nxp_Tef810x_Mod01_MasterIdivCtrlUnion_t
* Nxp_Tef810x_Mod01_MasterIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_MasterIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_MasterIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlUnion_t
* Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod01_RefCntrInitUnion_t
* Nxp_Tef810x_Mod01_RefCntrInitUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_RefCntrInitBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_RefCntrInitUnion_t;
/**
* Nxp_Tef810x_Mod01_FreqCounterStartUnion_t
* Nxp_Tef810x_Mod01_FreqCounterStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_FreqCounterStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_FreqCounterStartUnion_t;
/**
* Nxp_Tef810x_Mod01_FreqCounterReadValueUnion_t
* Nxp_Tef810x_Mod01_FreqCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_FreqCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_FreqCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod01_RefCounterReadValueUnion_t
* Nxp_Tef810x_Mod01_RefCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_RefCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_RefCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod01_AtbSetTrimUnion_t
* Nxp_Tef810x_Mod01_AtbSetTrimUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_AtbSetTrimBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_AtbSetTrimUnion_t;
/**
* Nxp_Tef810x_Mod01_ModuleidUnion_t
* Nxp_Tef810x_Mod01_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod01_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod01_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod01_LvdsTxRegister_t
 * Nxp_Tef810x_Mod01_LvdsTxRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x000
    * ResetValue: 0x05C5C000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x004
    * ResetValue: 0x05C5C000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x008
    * ResetValue: 0x05C5C000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x00C
    * ResetValue: 0x05C5C000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Clk_channel_data
    * AddressOffset: 0x010
    * ResetValue: 0x000003E0
    * Description: This register is used for 8b10b mode for controlling Frame clock pattern (duty cycle) send over LVDS Link
    */
    Nxp_Tef810x_Mod01_ClkChannelDataUnion_t ClkChannelData_ust;        /*## attribute ClkChannelData_ust */
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x014
    * ResetValue: 0x0000FFFF
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Idle_pattern
    * AddressOffset: 0x018
    * ResetValue: 0x000002AB
    * Description: This register is used for RAW and Bypass 8b10b mode.
    */
    Nxp_Tef810x_Mod01_IdlePatternUnion_t IdlePattern_ust;        /*## attribute IdlePattern_ust */
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x01C
    * ResetValue: 0x00000333
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x020
    * ResetValue: 0x000000CC
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: ClockChTxdata12x1
    * AddressOffset: 0x024
    * ResetValue: 0x00000FC0
    * Description: This register is used for RAW mode for controlling Frame clock pattern (duty cycle) send over LVDS Link.
    */
    Nxp_Tef810x_Mod01_Clockchtxdata12X1Union_t Clockchtxdata12X1_ust;        /*## attribute Clockchtxdata12X1_ust */
  /**
    * RegisterName: AdcDebugMode
    * AddressOffset: 0x028
    * ResetValue: 0x00000001
    * Description: This register is used for LVDS Mode Selecton
    */
    Nxp_Tef810x_Mod01_AdcdebugmodeUnion_t Adcdebugmode_ust;        /*## attribute Adcdebugmode_ust */
  /**
    * RegisterName: TransmitPhaseControl
    * AddressOffset: 0x02C
    * ResetValue: 0x00000011
    * Description: This register is common for all the modes.Used for controlling phase of bit_clk and frame_clk sent over LVDS link.
    */
    Nxp_Tef810x_Mod01_TransmitphasecontrolUnion_t Transmitphasecontrol_ust;        /*## attribute Transmitphasecontrol_ust */
  /**
    * RegisterName: MsbLsbControl
    * AddressOffset: 0x030
    * ResetValue: 0x00000001
    * Description: This register is common for all the modes.In serial to parallel conversion this register determines whether MSB/LSB of the parallal word sent first.
    */
    Nxp_Tef810x_Mod01_MsblsbcontrolUnion_t Msblsbcontrol_ust;        /*## attribute Msblsbcontrol_ust */
  /**
    * RegisterName: LvdsConfigReg
    * AddressOffset: 0x034
    * ResetValue: 0x10000100
    * Description: This register is common for all the modes.
    */
    Nxp_Tef810x_Mod01_LvdsconfigregUnion_t Lvdsconfigreg_ust;        /*## attribute Lvdsconfigreg_ust */
  /**
    * RegisterName: lvds_crc_ctrl1
    * AddressOffset: 0x038
    * ResetValue: 0xFFFFFFFF
    * Description: CRC-32 control register
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl1Union_t LvdsCrcCtrl1_ust;        /*## attribute LvdsCrcCtrl1_ust */
  /**
    * RegisterName: lvds_crc_ctrl2
    * AddressOffset: 0x03C
    * ResetValue: 0xFFFFFFFF
    * Description: CRC-32 control register
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl2Union_t LvdsCrcCtrl2_ust;        /*## attribute LvdsCrcCtrl2_ust */
  /**
    * RegisterName: lvds_crc_ctrl3
    * AddressOffset: 0x040
    * ResetValue: 0x0FF00110
    * Description: CRC-32 control register
    */
    Nxp_Tef810x_Mod01_LvdsCrcCtrl3Union_t LvdsCrcCtrl3_ust;        /*## attribute LvdsCrcCtrl3_ust */
  /**
    * RegisterName: pdc_config_reg
    * AddressOffset: 0x044
    * ResetValue: 0x00A9A700
    * Description: PDC Config register
    */
    Nxp_Tef810x_Mod01_PdcConfigRegUnion_t PdcConfigReg_ust;        /*## attribute PdcConfigReg_ust */
  /**
    * RegisterName: lvds_output_invert_ctrl
    * AddressOffset: 0x048
    * ResetValue: 0x00000000
    * Description: Invert LVDS output  Lines Control. Can be used for  inverting th eO/P polarity of the LVDS lanes
    */
    Nxp_Tef810x_Mod01_LvdsOutputInvertCtrlUnion_t LvdsOutputInvertCtrl_ust;        /*## attribute LvdsOutputInvertCtrl_ust */
  /**
    * RegisterName: Lvds_tx_control
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: Transmission enable for All LVDS Channels
    */
    Nxp_Tef810x_Mod01_LvdsTxControlUnion_t LvdsTxControl_ust;        /*## attribute LvdsTxControl_ust */
  /**
    * RegisterName: lvds_ser_global_pad_ctrl
    * AddressOffset: 0x050
    * ResetValue: 0x00001000
    * Description: Global Pad Control Register,by default all the LVDS and mfio pads are in Cell power-down, high impedance state.
    */
    Nxp_Tef810x_Mod01_LvdsSerGlobalPadCtrlUnion_t LvdsSerGlobalPadCtrl_ust;        /*## attribute LvdsSerGlobalPadCtrl_ust */
  /**
    * RegisterName: lvds_ser_pad_ctrl1
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: LVDS Pad control register.By default all the LVDS pads are in Cell power-down, high impedance state.
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl1Union_t LvdsSerPadCtrl1_ust;        /*## attribute LvdsSerPadCtrl1_ust */
  /**
    * RegisterName: lvds_ser_pad_ctrl2
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: LVDS Pad control register.By default all the LVDS pads are in Cell power-down, high impedance state.
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl2Union_t LvdsSerPadCtrl2_ust;        /*## attribute LvdsSerPadCtrl2_ust */
  /**
    * RegisterName: lvds_ser_pad_ctrl3
    * AddressOffset: 0x05C
    * ResetValue: 0x00000131
    * Description: LVDS Spare register +PAD control
    */
    Nxp_Tef810x_Mod01_LvdsSerPadCtrl3Union_t LvdsSerPadCtrl3_ust;        /*## attribute LvdsSerPadCtrl3_ust */
  /**
    * RegisterName: ADCTestDataMux
    * AddressOffset: 0x060
    * ResetValue: 0x00007FFF
    * Description: This register is used for Testing Purpose. (only for internal validation and debug purpose)
    */
    Nxp_Tef810x_Mod01_AdctestdatamuxUnion_t Adctestdatamux_ust;        /*## attribute Adctestdatamux_ust */
  /**
    * RegisterName: WindowActiveSel
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: This register is used for Testing Purpose.
	* By using this register, the external data_valid can be forced  through register. Can be used for testing the interface along with ADCTestDataMux register ( 060)
    */
    Nxp_Tef810x_Mod01_WindowactiveselUnion_t Windowactivesel_ust;        /*## attribute Windowactivesel_ust */
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: master_idiv_ctrl
    * AddressOffset: 0x06C
    * ResetValue: 0x000400B0
    * Description: Serialiser clock divider control.
	* As part of  LVDS interface initialisation, the O/P frequency need to be set  and interface enabled . This register can be used for setting the O/P clock to the desired value.  
	* 
	* Dolphin allows dynamic decimation at individual chirp level over LVDS and CIF interface.  this means,  the O/P frequency of the interface and teh decimation values are coming from chirp.  However the values from chirp module will take efefct only when the chirp engine is triggered for data acquisition. till such time  the O/P frequncy control is driven from this register.  Please make sure that the first profile values used from chirp engine and the  IDIV setting are matched. to avoid  sudden frequency changes at the O/P
    */
    Nxp_Tef810x_Mod01_MasterIdivCtrlUnion_t MasterIdivCtrl_ust;        /*## attribute MasterIdivCtrl_ust */
  /**
    * RegisterName: pdc_shift_reg_idiv_ctrl
    * AddressOffset: 0x070
    * ResetValue: 0x00000002
    * Description: ADC Data Sampling Control
    */
    Nxp_Tef810x_Mod01_PdcShiftRegIdivCtrlUnion_t PdcShiftRegIdivCtrl_ust;        /*## attribute PdcShiftRegIdivCtrl_ust */
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
    * Description: Functional safety related sensor logic
	* Frequency Counter : Used for measuring Serialiser Clock 480MHz/600MHz )frequency
    */
    Nxp_Tef810x_Mod01_RefCntrInitUnion_t RefCntrInit_ust;        /*## attribute RefCntrInit_ust */
  /**
    * RegisterName: freq_counter_start
    * AddressOffset: 0x07C
    * ResetValue: 0x00000100
    * Description: Functional safety related sensor logic
	* Frequency Counter : Used for measuring the input clcok 480/600 MHz to the serialzier .
	* The input clock is coming from the master clock block
	* 480/600  mode selection also done within master clock based on the serailzier mode (raw data or 8b10b data) configuration
    */
    Nxp_Tef810x_Mod01_FreqCounterStartUnion_t FreqCounterStart_ust;        /*## attribute FreqCounterStart_ust */
  /**
    * RegisterName: freq_counter_read_value
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 MHz )frequency
    */
    Nxp_Tef810x_Mod01_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;        /*## attribute FreqCounterReadValue_ust */
  /**
    * RegisterName: ref_counter_read_value
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 MHz )frequency
    */
    Nxp_Tef810x_Mod01_RefCounterReadValueUnion_t RefCounterReadValue_ust;        /*## attribute RefCounterReadValue_ust */
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
    Nxp_Tef810x_Mod01_AtbSetTrimUnion_t AtbSetTrim_ust;        /*## attribute AtbSetTrim_ust */
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
    * ResetValue: 0x00013301
    * Description: Module ID register
    */
    Nxp_Tef810x_Mod01_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod01_LvdsTxRegister_t;

#endif
