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
* @NXP_TEF810X_LoInterface.h
*/
#ifndef NXP_TEF810X_LOINTERFACE_H
#define NXP_TEF810X_LOINTERFACE_H
#include "Std_Types.h"

#define LO_INTERFACE_MODULE_ADDRESS 0x0A
/**
*NXP_TEF810X_MOD0A_BBD_CONFIG_U16
* RegisterName: MOD0A_bbd_config
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD0A_BBD_CONFIG_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16
* RegisterName: MOD0A_lo_interface_control
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00110000
*/
#define NXP_TEF810X_MOD0A_LO_INTERFACE_CONTROL_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16
* RegisterName: MOD0A_lo_interface_gain_control
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x0000000F
*/
#define NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD0A_MODULEID_U16
* RegisterName: MOD0A_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x000A2201
*/
#define NXP_TEF810X_MOD0A_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod0A_BBD_CONFIGBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: bb_grounded_spi
	* Description: Balun grounded. 
	* 0 = not grounded 
	* 1 = grounded
	*/
    uint32 BbGroundedSpi: 1;        /*## attribute BbGroundedSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_idetect_spi
	* Description: Ball break current detection. 
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
	* Description: Ball break detector enable. By default it is enabled
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 BbEnSpi: 1;        /*## attribute BbEnSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod0A_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod0A_LO_INTERFACE_CONTROLBits_t
* RegisterName: lo_interface_control
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: gain_b2_set_spi
	* Description: Thermo code selection vector.The 4 bit thermo code and corresponding 8 bit analog code (Expected power) is listed below.
	* 0000  :   1111 0001 : Really low
	* 0001   :   0100 0001 -18dBm
	* 0011    :   0001 0001 -15dBm
	* 0111    :   0000 0001 -13dBm
	* 1111     :   0000 0100 -10dBm
	*/
    uint32 GainB2SetSpi: 4;        /*## attribute GainB2SetSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: cntr_mux_lo_spi
	* Description: "Select the LO source for the core IP's (RX/TX/RFbist). 
	* 0=lo_out 
	* 1=lo_in"
	*/
    uint32 CntrMuxLoSpi: 1;        /*## attribute CntrMuxLoSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_rterm_loio
	* Description: not_used
	*/
    uint32 EnRtermLoio: 1;        /*## attribute EnRtermLoio */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_b1
	* Description: en_b1 Description: 
	* "Enable buffer b1. This buffer connects internal Chirp signal to the LO pads and the core IP's (RX/TX/RFbist). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable" M50
	*/
    uint32 EnB1: 1;        /*## attribute EnB1 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: en_b2
	* Description: "Enable buffer b2. This buffer connects the LO signal either external or internal to the core IP's (RX/TX/RFbist). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB2: 1;        /*## attribute EnB2 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_b3
	* Description: "Enable buffer b3. Connect external LO signal comming from lo_inout to the core IP's (RX/TX/RFbist). 
	* This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB3: 1;        /*## attribute EnB3 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: en_b4
	* Description: "Enable buffer b4. Connect Chirp signal to lo_inout (to send external to chip). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB4: 1;        /*## attribute EnB4 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: pon_ls_spi
	* Description: This bit controls the level shifter. This is used for validation purpose only. In the functional context, the central control pon register is used for enabling the level shifter
	* 1 = pon enable for the level shifter
	* 0 = pon disable for the level shifter
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: en_lo
	* Description: 1= enable lo
	* 0 =disable lo
	*/
    uint32 EnLo: 1;        /*## attribute EnLo */
}Nxp_Tef810x_Mod0A_LoInterfaceControlBits_t;
    /**
* Nxp_Tef810x_Mod0A_LO_INTERFACE_GAIN_CONTROLBits_t
* RegisterName: lo_interface_gain_control
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: gain_code_sel
	* Description: Gain code selection  vector and corresponding gain code is listed below.
	* 5'b00000: gain_code = 8'b11110001;  //-24.1 dBm
	* 5'b00001: gain_code = 8'b11110001;  //-24.1 dBm
	* 5'b00010: gain_code = 8'b11100001;  // -23.9 dBm
	* 5'b00011: gain_code = 8'b11010001;  // -23.6 dBm
	* 5'b00100: gain_code = 8'b11000001;  // -23.3 dBm
	* 5'b00101: gain_code = 8'b10110001;  // -23.0 dBm
	* 5'b00110: gain_code = 8'b10100001;  // -22.6 dBm
	* 5'b00111: gain_code = 8'b10010001;  // -22.2 dBm
	* 5'b01000: gain_code = 8'b10000001;  // -21.7 dBm
	* 5'b01001: gain_code = 8'b01110001;  // -21.2 dBm
	* 5'b01010: gain_code = 8'b01100001;  // -20.5 dBm
	* 5'b01011: gain_code = 8'b01010001;  // -19.7 dBm
	* 5'b01100: gain_code = 8'b01000001;  // -18.8 dBm
	* 5'b01101: gain_code = 8'b00110001;  // -17.7 dBm
	* 5'b01110: gain_code = 8'b00100001;  // -16.4 dBm
	* 5'b01111: gain_code = 8'b00010001;  // -14.9 dBm
	* 5'b10000: gain_code = 8'b00000001;  //-13.1dBm
	* 5'b10001: gain_code = 8'b00000010;  //-11.8dBm
	* 5'b10010: gain_code = 8'b00000100;  //-10.7dBm
	* 5'b10011: gain_code = 8'b00001000;  //-8.9dBm
	* 5'b10100: gain_code = 8'b00000011;  //-7.6dBm
	* 5'b10101: gain_code = 8'b00000101;  //-7.0dBm
	* 5'b10110: gain_code = 8'b00000110;  //-6.6dBm
	* 5'b10111: gain_code = 8'b00001001;  //-6.1dBm
	* 5'b11000: gain_code = 8'b00001010;  //-5.7dBm
	* 5'b11001: gain_code = 8'b00001100;  //-5.4dBm
	* 5'b11010: gain_code = 8'b00000111;  //-4.8dBm
	* 5'b11011: gain_code = 8'b00001011;  //-4.2dBm
	* 5'b11100: gain_code = 8'b00001101;  //-4.0dBm
	* 5'b11101: gain_code = 8'b00001110;  // -3.8 dBm
	* 5'b11110: gain_code = 8'b00001111;  //-3.0 dBm
	* 5'b11111: gain_code = 8'b00001111;  //-3.0 dBm
	*/
    uint32 GainCodeSel: 5;        /*## attribute GainCodeSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: gain_thermo_lut_sel
	* Description: Selection bit between  Thermo LUT or Gain LUT 
	* 
	* 0 : (default) :   Thermo code LUT output comes out of  lo_interface_control (0x018)  bits 3..0 (gain_b2_set_spi) register  ( reflect the ES1 settings)
	* 
	* 1 :  Gain Code LUT output comes out of  lo_interface_gain_control (0x040) bits 4..0 ( gain_code_sel).
	* The second option  ( seting this bit to '1')  provides more fine control  of the gain  and is required in a  master slave configuration
	*/
    uint32 GainThermoLutSel: 1;        /*## attribute GainThermoLutSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod0A_LoInterfaceGainControlBits_t;
    /**
* Nxp_Tef810x_Mod0A_MODULEIDBits_t
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
}Nxp_Tef810x_Mod0A_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod0A_BbdConfigBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0x000 - 0x004
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
	* Description: Ball break detector enable. By default it is enabled
	* 1: Enabled
	* 0: Disabled
	*/
    uint32 BbEnSpi: 1;        /*## attribute BbEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: bb_idetect_spi
	* Description: Ball break current detection. 
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
	* Description: Balun grounded. 
	* 0 = not grounded 
	* 1 = grounded
	*/
    uint32 BbGroundedSpi: 1;        /*## attribute BbGroundedSpi */
}Nxp_Tef810x_Mod0A_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod0A_LoInterfaceControlBits_t
* RegisterName: lo_interface_control
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00110000
*/
typedef struct  {
   /**
	* BitsName: en_lo
	* Description: 1= enable lo
	* 0 =disable lo
	*/
    uint32 EnLo: 1;        /*## attribute EnLo */
   /**
	* BitsName: pon_ls_spi
	* Description: This bit controls the level shifter. This is used for validation purpose only. In the functional context, the central control pon register is used for enabling the level shifter
	* 1 = pon enable for the level shifter
	* 0 = pon disable for the level shifter
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: en_b4
	* Description: "Enable buffer b4. Connect Chirp signal to lo_inout (to send external to chip). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB4: 1;        /*## attribute EnB4 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_b3
	* Description: "Enable buffer b3. Connect external LO signal comming from lo_inout to the core IP's (RX/TX/RFbist). 
	* This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB3: 1;        /*## attribute EnB3 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_b2
	* Description: "Enable buffer b2. This buffer connects the LO signal either external or internal to the core IP's (RX/TX/RFbist). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable"
	*/
    uint32 EnB2: 1;        /*## attribute EnB2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: en_b1
	* Description: en_b1 Description: 
	* "Enable buffer b1. This buffer connects internal Chirp signal to the LO pads and the core IP's (RX/TX/RFbist). This bit also needs to be set when doing the loop back test. 
	* 0=Disable 
	* 1=Enable" M50
	*/
    uint32 EnB1: 1;        /*## attribute EnB1 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_rterm_loio
	* Description: not_used
	*/
    uint32 EnRtermLoio: 1;        /*## attribute EnRtermLoio */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: cntr_mux_lo_spi
	* Description: "Select the LO source for the core IP's (RX/TX/RFbist). 
	* 0=lo_out 
	* 1=lo_in"
	*/
    uint32 CntrMuxLoSpi: 1;        /*## attribute CntrMuxLoSpi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 4;        /*## attribute Reserved6 */
   /**
	* BitsName: gain_b2_set_spi
	* Description: Thermo code selection vector.The 4 bit thermo code and corresponding 8 bit analog code (Expected power) is listed below.
	* 0000  :   1111 0001 : Really low
	* 0001   :   0100 0001 -18dBm
	* 0011    :   0001 0001 -15dBm
	* 0111    :   0000 0001 -13dBm
	* 1111     :   0000 0100 -10dBm
	*/
    uint32 GainB2SetSpi: 4;        /*## attribute GainB2SetSpi */
}Nxp_Tef810x_Mod0A_LoInterfaceControlBits_t;
    /**
* Nxp_Tef810x_Mod0A_LoInterfaceGainControlBits_t
* RegisterName: lo_interface_gain_control
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x0000000F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: gain_thermo_lut_sel
	* Description: Selection bit between  Thermo LUT or Gain LUT 
	* 
	* 0 : (default) :   Thermo code LUT output comes out of  lo_interface_control (0x018)  bits 3..0 (gain_b2_set_spi) register  ( reflect the ES1 settings)
	* 
	* 1 :  Gain Code LUT output comes out of  lo_interface_gain_control (0x040) bits 4..0 ( gain_code_sel).
	* The second option  ( seting this bit to '1')  provides more fine control  of the gain  and is required in a  master slave configuration
	*/
    uint32 GainThermoLutSel: 1;        /*## attribute GainThermoLutSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: gain_code_sel
	* Description: Gain code selection  vector and corresponding gain code is listed below.
	* 5'b00000: gain_code = 8'b11110001;  //-24.1 dBm
	* 5'b00001: gain_code = 8'b11110001;  //-24.1 dBm
	* 5'b00010: gain_code = 8'b11100001;  // -23.9 dBm
	* 5'b00011: gain_code = 8'b11010001;  // -23.6 dBm
	* 5'b00100: gain_code = 8'b11000001;  // -23.3 dBm
	* 5'b00101: gain_code = 8'b10110001;  // -23.0 dBm
	* 5'b00110: gain_code = 8'b10100001;  // -22.6 dBm
	* 5'b00111: gain_code = 8'b10010001;  // -22.2 dBm
	* 5'b01000: gain_code = 8'b10000001;  // -21.7 dBm
	* 5'b01001: gain_code = 8'b01110001;  // -21.2 dBm
	* 5'b01010: gain_code = 8'b01100001;  // -20.5 dBm
	* 5'b01011: gain_code = 8'b01010001;  // -19.7 dBm
	* 5'b01100: gain_code = 8'b01000001;  // -18.8 dBm
	* 5'b01101: gain_code = 8'b00110001;  // -17.7 dBm
	* 5'b01110: gain_code = 8'b00100001;  // -16.4 dBm
	* 5'b01111: gain_code = 8'b00010001;  // -14.9 dBm
	* 5'b10000: gain_code = 8'b00000001;  //-13.1dBm
	* 5'b10001: gain_code = 8'b00000010;  //-11.8dBm
	* 5'b10010: gain_code = 8'b00000100;  //-10.7dBm
	* 5'b10011: gain_code = 8'b00001000;  //-8.9dBm
	* 5'b10100: gain_code = 8'b00000011;  //-7.6dBm
	* 5'b10101: gain_code = 8'b00000101;  //-7.0dBm
	* 5'b10110: gain_code = 8'b00000110;  //-6.6dBm
	* 5'b10111: gain_code = 8'b00001001;  //-6.1dBm
	* 5'b11000: gain_code = 8'b00001010;  //-5.7dBm
	* 5'b11001: gain_code = 8'b00001100;  //-5.4dBm
	* 5'b11010: gain_code = 8'b00000111;  //-4.8dBm
	* 5'b11011: gain_code = 8'b00001011;  //-4.2dBm
	* 5'b11100: gain_code = 8'b00001101;  //-4.0dBm
	* 5'b11101: gain_code = 8'b00001110;  // -3.8 dBm
	* 5'b11110: gain_code = 8'b00001111;  //-3.0 dBm
	* 5'b11111: gain_code = 8'b00001111;  //-3.0 dBm
	*/
    uint32 GainCodeSel: 5;        /*## attribute GainCodeSel */
}Nxp_Tef810x_Mod0A_LoInterfaceGainControlBits_t;
    /**
* Nxp_Tef810x_Mod0A_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x000A2201
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
}Nxp_Tef810x_Mod0A_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod0A_BbdConfigUnion_t
* Nxp_Tef810x_Mod0A_BbdConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0A_BbdConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0A_BbdConfigUnion_t;
/**
* Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t
* Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0A_LoInterfaceControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t;
/**
* Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t
* Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0A_LoInterfaceGainControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t;
/**
* Nxp_Tef810x_Mod0A_ModuleidUnion_t
* Nxp_Tef810x_Mod0A_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0A_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0A_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod0A_LoInterfaceRegister_t
 * Nxp_Tef810x_Mod0A_LoInterfaceRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: bbd_config
    * AddressOffset: 0x000
    * ResetValue: 0x00000100
    * Description: This register is used to set the controls for the ball break detector
    */
    Nxp_Tef810x_Mod0A_BbdConfigUnion_t BbdConfig_ust;        /*## attribute BbdConfig_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x004
    * ResetValue: 0x00140000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x008
    * ResetValue: 0x00140000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x00C
    * ResetValue: 0x00140000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x010
    * ResetValue: 0x00140000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x014
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: lo_interface_control
    * AddressOffset: 0x018
    * ResetValue: 0x00110000
    * Description: LO control settings register. Please refer LO interface specification to get the better understanding of the control bits
    */
    Nxp_Tef810x_Mod0A_LoInterfaceControlUnion_t LoInterfaceControl_ust;        /*## attribute LoInterfaceControl_ust */
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x01C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x020
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x024
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x028
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x02C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x034
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x038
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x03C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: lo_interface_gain_control
    * AddressOffset: 0x040
    * ResetValue: 0x0000000F
    * Description: Lo Gain control register
    */
    Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t LoInterfaceGainControl_ust;        /*## attribute LoInterfaceGainControl_ust */

    uint32 gap01_au32[1004];        /* gap 1 in register space */  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x000A2201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod0A_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod0A_LoInterfaceRegister_t;

#endif
