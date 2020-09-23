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
* @NXP_TEF810X_Rx.h
*/
#ifndef NXP_TEF810X_RX_H
#define NXP_TEF810X_RX_H
#include "Std_Types.h"

#define RX1_MODULE_ADDRESS 0x0D
#define RX2_MODULE_ADDRESS 0x0E
#define RX3_MODULE_ADDRESS 0x0F
#define RX4_MODULE_ADDRESS 0x10
/**
*NXP_TEF810X_MOD0D_G_RX_SET_PROFILE0_U16
* RegisterName: MOD0D_g_rx_set_profile0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000007
*/
#define NXP_TEF810X_MOD0D_G_RX_SET_PROFILE0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE0_U16
* RegisterName: MOD0D_hpf_rx_set_profile0
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE0_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE0_U16
* RegisterName: MOD0D_lpf_rx_set_profile0
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE0_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD0D_G_RX_SET_PROFILE1_U16
* RegisterName: MOD0D_g_rx_set_profile1
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000007
*/
#define NXP_TEF810X_MOD0D_G_RX_SET_PROFILE1_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE1_U16
* RegisterName: MOD0D_hpf_rx_set_profile1
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE1_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE1_U16
* RegisterName: MOD0D_lpf_rx_set_profile1
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE1_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD0D_G_RX_SET_PROFILE2_U16
* RegisterName: MOD0D_g_rx_set_profile2
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000007
*/
#define NXP_TEF810X_MOD0D_G_RX_SET_PROFILE2_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE2_U16
* RegisterName: MOD0D_hpf_rx_set_profile2
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE2_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE2_U16
* RegisterName: MOD0D_lpf_rx_set_profile2
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE2_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16
* RegisterName: MOD0D_g_rx_set_profile3
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000007
*/
#define NXP_TEF810X_MOD0D_G_RX_SET_PROFILE3_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE3_U16
* RegisterName: MOD0D_hpf_rx_set_profile3
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_HPF_RX_SET_PROFILE3_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16
* RegisterName: MOD0D_lpf_rx_set_profile3
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_LPF_RX_SET_PROFILE3_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16
* RegisterName: MOD0D_funcsafe_mon_level_lo
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_FUNCSAFE_MON_LEVEL_LO_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD0D_RMS_CONTROL_U16
* RegisterName: MOD0D_rms_control
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_RMS_CONTROL_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD0D_BBD_CONFIG_U16
* RegisterName: MOD0D_bbd_config
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD0D_BBD_CONFIG_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD0D_RX_CONTROL_U16
* RegisterName: MOD0D_rx_control
* AccessMode: READWRITE
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_RX_CONTROL_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD0D_RMS_CAL_U16
* RegisterName: MOD0D_rms_cal
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_RMS_CAL_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD0D_RC_RX_TRIM_U16
* RegisterName: MOD0D_rc_rx_trim
* AccessMode: READWRITE
* AddressRange: 0x0094 - 0x0098
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD0D_RC_RX_TRIM_U16 (uint16)0x0094
/**
*NXP_TEF810X_MOD0D_MODULEID_U16
* RegisterName: MOD0D_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x000D3301
*/
#define NXP_TEF810X_MOD0D_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod0D_G_RX_SET_PROFILEBits_t
* RegisterName: g_rx_set_profile
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: gain_rx_set_profile0
	* Description: RX Gain Control. Control Receiver Gain:
	* 0001 = 27dB
	* 0010 = 30dB
	* 0011 = 33dB
	* 0100 = 36dB
	* 0101 = 39dB
	* 0110 = 42dB
	* 0111 = 45dB
	* (Accuracy +/-3dB; Gain increased for MRA2 by ?4dB; RAD580)
	* 
	* Note: Other values not to be used.
	*/
    uint32 GainRxSetProfile0: 4;        /*## attribute GainRxSetProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0D_GRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_HPF_RX_SET_PROFILEBits_t
* RegisterName: hpf_rx_set_profile
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: hpf_rx_set_profile0
	* Description: The -6dB HPF corner setting (HPF) in kHz
	* 000 = 100
	* 001 = 200
	* 010 = 300
	* 011 = 400
	* 100 = 800
	* 101 = 1600
	* 110 (reserved for future)
	* 111 (reserved for future)
	*/
    uint32 HpfRxSetProfile0: 3;        /*## attribute HpfRxSetProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 29;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0D_HpfRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_LPF_RX_SET_PROFILEBits_t
* RegisterName: lpf_rx_set_profile
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: lpf_rx_set_profile0
	* Description: The LSB bit for this control (lpf_rx_set<2:0>) is used for wideband LPF corner. 
	* 
	* xx0 =Narrow band mode
	* 
	* xx1 = wideband (fLPF > 25MHz)
	* 
	* note: Bits 2..1 are dont care (not used)
	*/
    uint32 LpfRxSetProfile0: 3;        /*## attribute LpfRxSetProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: lpf_rx_fine_set_profile0
	* Description: Fine setting for the  cut off frequency in non wideband mode: 
	* 
	* Reduces the low-pass filter corner cut-off frequency in  fine steps according to the equation:
	* fLPF_reduced = fLPF/(1+ lpf_rx_fine_set_profileX /16)   [X=0..3]
	*/
    uint32 LpfRxFineSetProfile0: 4;        /*## attribute LpfRxFineSetProfile0 */
   /**
	* BitsName: lpf_rx_corner_set_profile0
	* Description: Coarse cut off frequency setting for non wideband mode: 
	* 
	* The -6dB LPF corner setting (fLPF) in MHz 
	*  (when lpf_rx_fine_set_profileX = 0; X=0..3)
	* 00 = 7.5
	* 01 = 10
	* 10 = 12.5
	* 11 = 15
	*/
    uint32 LpfRxCornerSetProfile0: 2;        /*## attribute LpfRxCornerSetProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod0D_LpfRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_FUNCSAFE_MON_LEVEL_LOBits_t
* RegisterName: funcsafe_mon_level_lo
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: level_lo_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage), only lower 4 bits are used
	* 
	* This value comes from OTP
	*  V_thresh = 117+19.53*Code
	*/
    uint32 LevelLoMinSpi: 6;        /*## attribute LevelLoMinSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: level_lo_low_spi
	* Description: Low trigger level for  LO level  monitor, only lower 4 bits are used
	* 
	* Based on application .
	*  V_thresh = 117+19.53*Code
	*/
    uint32 LevelLoLowSpi: 6;        /*## attribute LevelLoLowSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: level_lo_high_spi
	* Description: High trigger level for LO level  monitor, only lower 4 bits are used
	* 
	* Based on application .
	*  V_thresh = 527+19.53*Code
	*/
    uint32 LevelLoHighSpi: 6;        /*## attribute LevelLoHighSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: level_lo_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage), only lower 4 bits are used
	* 
	* This value comes from OTP
	* 
	*  V_thresh = 527+19.53*Code
	*/
    uint32 LevelLoMaxSpi: 6;        /*## attribute LevelLoMaxSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoBits_t;
    /**
* Nxp_Tef810x_Mod0D_RMS_CONTROLBits_t
* RegisterName: rms_control
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: sel_rx_bist_in_spi
	* Description: Select RX BIST input
	* 00: disabled
	* 01: LNA Input 
	* 10: Mixer Input
	*/
    uint32 SelRxBistInSpi: 2;        /*## attribute SelRxBistInSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: level_lo_en_spi
	* Description: Enable lo level detector
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 LevelLoEnSpi: 1;        /*## attribute LevelLoEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod0D_RmsControlBits_t;
    /**
* Nxp_Tef810x_Mod0D_BBD_CONFIGBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
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
	* 1=50uA
	* 0=500uA (det 100Ohm)
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
}Nxp_Tef810x_Mod0D_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod0D_RX_CONTROLBits_t
* RegisterName: rx_control
* 
* AddressRange: 0xREADWRITE - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: en_rx_via_spi
	* Description: Enable receiver. This spi control is logically ored with the rx_en coming from timing engine 
	* 0=off
	* 1=on.
	* Leave as reset if not needed explicitly.
	*/
    uint32 EnRxViaSpi: 1;        /*## attribute EnRxViaSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: en_lna_via_spi
	* Description: Enable lna:This spi control is logically ored with the rx_en coming from timing engine 
	* 0=off 
	* 1=on.
	* Leave as reset if not needed explicitly.
	*/
    uint32 EnLnaViaSpi: 1;        /*## attribute EnLnaViaSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: pon_ls_spi
	* Description: This control bit is used for validation only. Functionally, the pon from central control is used to control the analog level shifters.
	* Leave as reset if not needed explicitly.
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod0D_RxControlBits_t;
    /**
* Nxp_Tef810x_Mod0D_RMS_CALBits_t
* RegisterName: rms_cal
* 
* AddressRange: 0xREADWRITE - 0x06C
* ResetValue: 0x00000070
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
	* BitsName: meas_in_out_lo_det_spi
	* Description: Select input or output of power detector. 
	* 0=input
	* 1=output
	* 
	* Set this bit to '1' in application
	*/
    uint32 MeasInOutLoDetSpi: 1;        /*## attribute MeasInOutLoDetSpi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 19;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod0D_RmsCalBits_t;
    /**
* Nxp_Tef810x_Mod0D_RC_RX_TRIMBits_t
* RegisterName: rc_rx_trim
* 
* AddressRange: 0xREADWRITE - 0x094
* ResetValue: 0x00000098
*/
typedef struct  {
   /**
	* BitsName: rc_rx_trim_set
	* Description: OTP register rc_rx_trim, trims the -6dB LPF/HPF corners against process variations of RC time constant as described by equations below:
	* 
	* fHPF=fHPF_uncal/(0.5 + rc_rx_trim /16);
	* fLPF=fLPF_uncal/(0.5 + rc_rx_trim /16);
	* [For nominal process rc_rx_trim=8; fHPF=fHPF_uncal;  fLPF=fLPF_uncal]
	* 
	* The low-pass corner can be further reduced by using lpf_rx_fine_set_profileX (X=0..3) as below:
	* fLPF_reduced = fLPF_uncal/(0.5 + rc_rx_trim /16 + lpf_rx_fine_set /16)
	*  ? fLPF/(1+ lpf_rx_fine_set /16)
	* [For nominal process rc_rx_trim=8; 
	* fLPF_reduced = fLPF/(1+ lpf_rx_fine_set /16)]
	*/
    uint32 RcRxTrimSet: 4;        /*## attribute RcRxTrimSet */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod0D_RcRxTrimBits_t;
    /**
* Nxp_Tef810x_Mod0D_MODULEIDBits_t
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
	* BitsName: mod_id
	* Description: This is the address assigned to the module
	*/
    uint32 ModId: 8;        /*## attribute ModId */
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 8;        /*## attribute Identifier */
}Nxp_Tef810x_Mod0D_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod0D_GRxSetProfileBits_t
* RegisterName: g_rx_set_profile
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000007
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: gain_rx_set_profile0
	* Description: RX Gain Control. Control Receiver Gain:
	* 0001 = 27dB
	* 0010 = 30dB
	* 0011 = 33dB
	* 0100 = 36dB
	* 0101 = 39dB
	* 0110 = 42dB
	* 0111 = 45dB
	* (Accuracy +/-3dB; Gain increased for MRA2 by ?4dB; RAD580)
	* 
	* Note: Other values not to be used.
	*/
    uint32 GainRxSetProfile0: 4;        /*## attribute GainRxSetProfile0 */
}Nxp_Tef810x_Mod0D_GRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_HpfRxSetProfileBits_t
* RegisterName: hpf_rx_set_profile
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 29;        /*## attribute Reserved0 */
   /**
	* BitsName: hpf_rx_set_profile0
	* Description: The -6dB HPF corner setting (HPF) in kHz
	* 000 = 100
	* 001 = 200
	* 010 = 300
	* 011 = 400
	* 100 = 800
	* 101 = 1600
	* 110 (reserved for future)
	* 111 (reserved for future)
	*/
    uint32 HpfRxSetProfile0: 3;        /*## attribute HpfRxSetProfile0 */
}Nxp_Tef810x_Mod0D_HpfRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_LpfRxSetProfileBits_t
* RegisterName: lpf_rx_set_profile
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: lpf_rx_corner_set_profile0
	* Description: Coarse cut off frequency setting for non wideband mode: 
	* 
	* The -6dB LPF corner setting (fLPF) in MHz 
	*  (when lpf_rx_fine_set_profileX = 0; X=0..3)
	* 00 = 7.5
	* 01 = 10
	* 10 = 12.5
	* 11 = 15
	*/
    uint32 LpfRxCornerSetProfile0: 2;        /*## attribute LpfRxCornerSetProfile0 */
   /**
	* BitsName: lpf_rx_fine_set_profile0
	* Description: Fine setting for the  cut off frequency in non wideband mode: 
	* 
	* Reduces the low-pass filter corner cut-off frequency in  fine steps according to the equation:
	* fLPF_reduced = fLPF/(1+ lpf_rx_fine_set_profileX /16)   [X=0..3]
	*/
    uint32 LpfRxFineSetProfile0: 4;        /*## attribute LpfRxFineSetProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: lpf_rx_set_profile0
	* Description: The LSB bit for this control (lpf_rx_set<2:0>) is used for wideband LPF corner. 
	* 
	* xx0 =Narrow band mode
	* 
	* xx1 = wideband (fLPF > 25MHz)
	* 
	* note: Bits 2..1 are dont care (not used)
	*/
    uint32 LpfRxSetProfile0: 3;        /*## attribute LpfRxSetProfile0 */
}Nxp_Tef810x_Mod0D_LpfRxSetProfileBits_t;
    /**
* Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoBits_t
* RegisterName: funcsafe_mon_level_lo
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: level_lo_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage), only lower 4 bits are used
	* 
	* This value comes from OTP
	* 
	*  V_thresh = 527+19.53*Code
	*/
    uint32 LevelLoMaxSpi: 6;        /*## attribute LevelLoMaxSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: level_lo_high_spi
	* Description: High trigger level for LO level  monitor, only lower 4 bits are used
	* 
	* Based on application .
	*  V_thresh = 527+19.53*Code
	*/
    uint32 LevelLoHighSpi: 6;        /*## attribute LevelLoHighSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: level_lo_low_spi
	* Description: Low trigger level for  LO level  monitor, only lower 4 bits are used
	* 
	* Based on application .
	*  V_thresh = 117+19.53*Code
	*/
    uint32 LevelLoLowSpi: 6;        /*## attribute LevelLoLowSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: level_lo_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage), only lower 4 bits are used
	* 
	* This value comes from OTP
	*  V_thresh = 117+19.53*Code
	*/
    uint32 LevelLoMinSpi: 6;        /*## attribute LevelLoMinSpi */
}Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoBits_t;
    /**
* Nxp_Tef810x_Mod0D_RmsControlBits_t
* RegisterName: rms_control
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: level_lo_en_spi
	* Description: Enable lo level detector
	* 1: Enable
	* 0: Disable
	* 
	* Set this to '1'  always in application
	*/
    uint32 LevelLoEnSpi: 1;        /*## attribute LevelLoEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: sel_rx_bist_in_spi
	* Description: Select RX BIST input
	* 00: disabled
	* 01: LNA Input 
	* 10: Mixer Input
	*/
    uint32 SelRxBistInSpi: 2;        /*## attribute SelRxBistInSpi */
}Nxp_Tef810x_Mod0D_RmsControlBits_t;
    /**
* Nxp_Tef810x_Mod0D_BbdConfigBits_t
* RegisterName: bbd_config
* 
* AddressRange: 0x058 - 0x05C
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
	* 1=50uA
	* 0=500uA (det 100Ohm)
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
}Nxp_Tef810x_Mod0D_BbdConfigBits_t;
    /**
* Nxp_Tef810x_Mod0D_RxControlBits_t
* RegisterName: rx_control
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
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
	* BitsName: en_lna_via_spi
	* Description: Enable lna:This spi control is logically ored with the rx_en coming from timing engine 
	* 0=off 
	* 1=on.
	* Leave as reset if not needed explicitly.
	*/
    uint32 EnLnaViaSpi: 1;        /*## attribute EnLnaViaSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: en_rx_via_spi
	* Description: Enable receiver. This spi control is logically ored with the rx_en coming from timing engine 
	* 0=off
	* 1=on.
	* Leave as reset if not needed explicitly.
	*/
    uint32 EnRxViaSpi: 1;        /*## attribute EnRxViaSpi */
}Nxp_Tef810x_Mod0D_RxControlBits_t;
    /**
* Nxp_Tef810x_Mod0D_RmsCalBits_t
* RegisterName: rms_cal
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
	* BitsName: meas_in_out_lo_det_spi
	* Description: Select input or output of power detector. 
	* 0=input
	* 1=output
	* 
	* Set this bit to '1' in application
	*/
    uint32 MeasInOutLoDetSpi: 1;        /*## attribute MeasInOutLoDetSpi */
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
}Nxp_Tef810x_Mod0D_RmsCalBits_t;
    /**
* Nxp_Tef810x_Mod0D_RcRxTrimBits_t
* RegisterName: rc_rx_trim
* 
* AddressRange: 0x094 - 0x098
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 28;        /*## attribute Reserved0 */
   /**
	* BitsName: rc_rx_trim_set
	* Description: OTP register rc_rx_trim, trims the -6dB LPF/HPF corners against process variations of RC time constant as described by equations below:
	* 
	* fHPF=fHPF_uncal/(0.5 + rc_rx_trim /16);
	* fLPF=fLPF_uncal/(0.5 + rc_rx_trim /16);
	* [For nominal process rc_rx_trim=8; fHPF=fHPF_uncal;  fLPF=fLPF_uncal]
	* 
	* The low-pass corner can be further reduced by using lpf_rx_fine_set_profileX (X=0..3) as below:
	* fLPF_reduced = fLPF_uncal/(0.5 + rc_rx_trim /16 + lpf_rx_fine_set /16)
	*  ? fLPF/(1+ lpf_rx_fine_set /16)
	* [For nominal process rc_rx_trim=8; 
	* fLPF_reduced = fLPF/(1+ lpf_rx_fine_set /16)]
	*/
    uint32 RcRxTrimSet: 4;        /*## attribute RcRxTrimSet */
}Nxp_Tef810x_Mod0D_RcRxTrimBits_t;
    /**
* Nxp_Tef810x_Mod0D_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x000D3301
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 8;        /*## attribute Identifier */
   /**
	* BitsName: mod_id
	* Description: This is the address assigned to the module
	*/
    uint32 ModId: 8;        /*## attribute ModId */
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
}Nxp_Tef810x_Mod0D_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t
* Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_GRxSetProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t;
/**
* Nxp_Tef810x_Mod0D_HpfRxSetProfileUnion_t
* Nxp_Tef810x_Mod0D_HpfRxSetProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_HpfRxSetProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_HpfRxSetProfileUnion_t;
/**
* Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t
* Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_LpfRxSetProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t;
/**
* Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t
* Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t;
/**
* Nxp_Tef810x_Mod0D_RmsControlUnion_t
* Nxp_Tef810x_Mod0D_RmsControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_RmsControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_RmsControlUnion_t;
/**
* Nxp_Tef810x_Mod0D_BbdConfigUnion_t
* Nxp_Tef810x_Mod0D_BbdConfigUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_BbdConfigBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_BbdConfigUnion_t;
/**
* Nxp_Tef810x_Mod0D_RxControlUnion_t
* Nxp_Tef810x_Mod0D_RxControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_RxControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_RxControlUnion_t;
/**
* Nxp_Tef810x_Mod0D_RmsCalUnion_t
* Nxp_Tef810x_Mod0D_RmsCalUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_RmsCalBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_RmsCalUnion_t;
/**
* Nxp_Tef810x_Mod0D_RcRxTrimUnion_t
* Nxp_Tef810x_Mod0D_RcRxTrimUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_RcRxTrimBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_RcRxTrimUnion_t;
/**
* Nxp_Tef810x_Mod0D_ModuleidUnion_t
* Nxp_Tef810x_Mod0D_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod0D_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod0D_ModuleidUnion_t;
	/**
* Nxp_Tef810x_Mod0D_Rxprofile_t
* Nxp_Tef810x_Mod0D_Rxprofile_t
* Structure for module specific profile management
*/
typedef struct  {
  /**
    * RegisterName: g_rx_set_profile0
    * AddressOffset: 0x000
    * ResetValue: 0x00000007
    * Description: Receiver gain control register
    */
    Nxp_Tef810x_Mod0D_GRxSetProfileUnion_t GRxSetProfile0_ust;        /*## attribute GRxSetProfile0_ust */
  /**
    * RegisterName: hpf_rx_set_profile0
    * AddressOffset: 0x004
    * ResetValue: 0x00000000
    * Description: High Pass Filter settings register
    */
    Nxp_Tef810x_Mod0D_HpfRxSetProfileUnion_t HpfRxSetProfile0_ust;        /*## attribute HpfRxSetProfile0_ust */
  /**
    * RegisterName: lpf_rx_set_profile0
    * AddressOffset: 0x008
    * ResetValue: 0x00000000
    * Description: This register is used for low pass filter settings .
    */
    Nxp_Tef810x_Mod0D_LpfRxSetProfileUnion_t LpfRxSetProfile0_ust;        /*## attribute LpfRxSetProfile0_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x010
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
}Nxp_Tef810x_Mod0D_RxProfile_t;
/**
 * Nxp_Tef810x_Mod0D_RxRegister_t
 * Nxp_Tef810x_Mod0D_RxRegister_t
 * structure used as shadow register map
 */
typedef struct  {
	/**
    * RegisterName: Nxp_Tef810x_Mod0D_RxProfile_t;
    *AddressOffset: 0x000 - 0x04C
    * Description: Structure for module specific profile management.
                       
    */
    Nxp_Tef810x_Mod0D_RxProfile_t RxProfile_ast[0x04];        /*## attribute RxProfile_ast */
  /**
    * RegisterName: funcsafe_mon_level_lo
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: LO level  sensor settings
    */
    Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t FuncsafeMonLevelLo_ust;        /*## attribute FuncsafeMonLevelLo_ust */
  /**
    * RegisterName: rms_control
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: This register is used to enable the LO level detectors at various points
    */
    Nxp_Tef810x_Mod0D_RmsControlUnion_t RmsControl_ust;        /*## attribute RmsControl_ust */
  /**
    * RegisterName: bbd_config
    * AddressOffset: 0x058
    * ResetValue: 0x00000100
    * Description: This register is used to set the controls for the ball break detector
    */
    Nxp_Tef810x_Mod0D_BbdConfigUnion_t BbdConfig_ust;        /*## attribute BbdConfig_ust */
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: rx_control
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: control settings for the receiver This includes controlling of the receiver and LNA per chirp basis.
	* 
	* In actual application the function is controlled   by timing engine.  This bits are provided only for  validation purpose.
    */
    Nxp_Tef810x_Mod0D_RxControlUnion_t RxControl_ust;        /*## attribute RxControl_ust */
  /**
    * RegisterName: rms_cal
    * AddressOffset: 0x06C
    * ResetValue: 0x00000000
    * Description: calibration control setting for the rms detector
    */
    Nxp_Tef810x_Mod0D_RmsCalUnion_t RmsCal_ust;        /*## attribute RmsCal_ust */
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x070
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x074
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x078
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0x07C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;
  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;
  /**
    * RegisterName: Reserved10
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved10;
  /**
    * RegisterName: Reserved11
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved11;
  /**
    * RegisterName: Reserved12
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved12;
  /**
    * RegisterName: Reserved13
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved13;
  /**
    * RegisterName: rc_rx_trim
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: This register is kept for trim settings for process variation ( Value comes from OTP)
    */
    Nxp_Tef810x_Mod0D_RcRxTrimUnion_t RcRxTrim_ust;        /*## attribute RcRxTrim_ust */

    uint32 gap01_au32[983];        /* gap 1 in register space */  /**
    * RegisterName: Reserved14
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved14;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x000D3301
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod0D_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod0D_RxRegister_t;

#endif
