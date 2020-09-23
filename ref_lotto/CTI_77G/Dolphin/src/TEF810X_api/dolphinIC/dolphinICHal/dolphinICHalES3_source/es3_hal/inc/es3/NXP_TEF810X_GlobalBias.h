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
* @NXP_TEF810X_GlobalBias.h
*/
#ifndef NXP_TEF810X_GLOBALBIAS_H
#define NXP_TEF810X_GLOBALBIAS_H
#include "Std_Types.h"

#define GLOBAL_BIAS_MODULE_ADDRESS 0x09
/**
*NXP_TEF810X_MOD09_GLOBBIAS_TX1_U16
* RegisterName: MOD09_globbias_tx1
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00002828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_TX1_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD09_GLOBBIAS_TX2_U16
* RegisterName: MOD09_globbias_tx2
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00002828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_TX2_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD09_GLOBBIAS_TX3_U16
* RegisterName: MOD09_globbias_tx3
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00002828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_TX3_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD09_GLOBBIAS_RX1_U16
* RegisterName: MOD09_globbias_rx1
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_RX1_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD09_GLOBBIAS_RX2_U16
* RegisterName: MOD09_globbias_rx2
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_RX2_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD09_GLOBBIAS_RX3_U16
* RegisterName: MOD09_globbias_rx3
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_RX3_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD09_GLOBBIAS_RX4_U16
* RegisterName: MOD09_globbias_rx4
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_RX4_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD09_GLOBBIAS_MASTERCLK_U16
* RegisterName: MOD09_globbias_masterclk
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_MASTERCLK_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD09_GLOBBIAS_CHIRPGEN_U16
* RegisterName: MOD09_globbias_chirpgen
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00002828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_CHIRPGEN_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD09_GLOBBIAS_LO_INTERFACE_U16
* RegisterName: MOD09_globbias_lo_interface
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00002828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_LO_INTERFACE_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD09_GLOBBIAS_ADC12_U16
* RegisterName: MOD09_globbias_adc12
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_ADC12_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD09_GLOBBIAS_ADC34_U16
* RegisterName: MOD09_globbias_adc34
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_ADC34_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD09_GLOBBIAS_ATBIP_U16
* RegisterName: MOD09_globbias_atbip
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_ATBIP_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD09_GLOBBIAS_SSBMOD_U16
* RegisterName: MOD09_globbias_ssbmod
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x00282828
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_SSBMOD_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD09_GLOBBIAS_BBD_U16
* RegisterName: MOD09_globbias_bbd
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_BBD_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD09_GLOBBIAS_CLOCKPLL_U16
* RegisterName: MOD09_globbias_clockpll
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_CLOCKPLL_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD09_GLOBBIAS_LOTRIPLER_U16
* RegisterName: MOD09_globbias_lotripler
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_LOTRIPLER_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD09_GLOBBIAS_SNS_U16
* RegisterName: MOD09_globbias_sns
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_SNS_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD09_GLOBBIAS_LOCAL_LDO_U16
* RegisterName: MOD09_globbias_local_ldo
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x0000000D
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_LOCAL_LDO_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD09_GLOBBIAS_REFERENCE_U16
* RegisterName: MOD09_globbias_reference
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_REFERENCE_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD09_GLOBBIAS_TEST_BGR_U16
* RegisterName: MOD09_globbias_test_bgr
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_TEST_BGR_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD09_GLOBBIAS_TEST_PTAT_U16
* RegisterName: MOD09_globbias_test_ptat
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000028
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_TEST_PTAT_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD09_GLOBBIAS_PTAT_OFFSET_CALIB_U16
* RegisterName: MOD09_globbias_ptat_offset_calib
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_PTAT_OFFSET_CALIB_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD09_GLOBBIAS_PON_LOCAL_LDO_U16
* RegisterName: MOD09_globbias_pon_local_ldo
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_PON_LOCAL_LDO_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD09_GLOBBIAS_PON1V8_U16
* RegisterName: MOD09_globbias_pon1v8
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD09_GLOBBIAS_PON1V8_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD09_MODULEID_U16
* RegisterName: MOD09_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00092201
*/
#define NXP_TEF810X_MOD09_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod09_GLOBBIAS_TX1Bits_t
* RegisterName: globbias_tx1
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_tx1_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx1Bg: 6;        /*## attribute CtrlIrefTx1Bg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx1_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx1Ptat: 6;        /*## attribute CtrlIrefTx1Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 18;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasTx1Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_TX2Bits_t
* RegisterName: globbias_tx2
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_tx2_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx2Bg: 6;        /*## attribute CtrlIrefTx2Bg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx2_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx2Ptat: 6;        /*## attribute CtrlIrefTx2Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 18;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasTx2Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_TX3Bits_t
* RegisterName: globbias_tx3
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_tx3_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx3Bg: 6;        /*## attribute CtrlIrefTx3Bg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx3_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx3Ptat: 6;        /*## attribute CtrlIrefTx3Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 18;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasTx3Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_RX1Bits_t
* RegisterName: globbias_rx1
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_rx1_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx1Ptat: 6;        /*## attribute CtrlIrefRx1Ptat */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasRx1Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_RX2Bits_t
* RegisterName: globbias_rx2
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_rx2_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx2Ptat: 6;        /*## attribute CtrlIrefRx2Ptat */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasRx2Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_RX3Bits_t
* RegisterName: globbias_rx3
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_rx3_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx3Ptat: 6;        /*## attribute CtrlIrefRx3Ptat */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasRx3Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_RX4Bits_t
* RegisterName: globbias_rx4
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_rx4_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx4Ptat: 6;        /*## attribute CtrlIrefRx4Ptat */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasRx4Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_MASTERCLKBits_t
* RegisterName: globbias_masterclk
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_masterclk_bgr
	* Description: Buffers BG:
	* Control  bias BG untrimmed current for master clock. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefMasterclkBgr: 6;        /*## attribute CtrlIrefMasterclkBgr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasMasterclkBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_CHIRPGENBits_t
* RegisterName: globbias_chirpgen
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_chirpgen_bg
	* Description: Control BG   bias current for chirp generator. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefChirpgenBg: 6;        /*## attribute CtrlIrefChirpgenBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_chirpgen_bgr
	* Description: Control BGR bias current for chirp generator. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefChirpgenBgr: 6;        /*## attribute CtrlIrefChirpgenBgr */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 18;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasChirpgenBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_LO_INTERFACEBits_t
* RegisterName: globbias_lo_interface
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_interface_bg
	* Description: Control BG bias current for interface. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefInterfaceBg: 6;        /*## attribute CtrlIrefInterfaceBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_interface_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefInterfacePtat: 6;        /*## attribute CtrlIrefInterfacePtat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 18;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasLoInterfaceBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_ADC12Bits_t
* RegisterName: globbias_adc12
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_adc12_bgr
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAdc12Bgr: 6;        /*## attribute CtrlIrefAdc12Bgr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasAdc12Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_ADC34Bits_t
* RegisterName: globbias_adc34
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_adc34_bgr
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAdc34Bgr: 6;        /*## attribute CtrlIrefAdc34Bgr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasAdc34Bits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_ATBIPBits_t
* RegisterName: globbias_atbip
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_atbip_bgr
	* Description: Control BGR test  current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAtbipBgr: 6;        /*## attribute CtrlIrefAtbipBgr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasAtbipBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_SSBMODBits_t
* RegisterName: globbias_ssbmod
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_ssbmod_bg
	* Description: Control BG bias current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSsbmodBg: 6;        /*## attribute CtrlIrefSsbmodBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_ssbmod_bgr
	* Description: Control BGR test  current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSsbmodBgr: 6;        /*## attribute CtrlIrefSsbmodBgr */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_ssbmod_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefSsbmodPtat: 6;        /*## attribute CtrlIrefSsbmodPtat */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 10;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod09_GlobbiasSsbmodBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_BBDBits_t
* RegisterName: globbias_bbd
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_ballbreakdet_bg
	* Description: Control bias BG current for ball break detector. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefBallbreakdetBg: 6;        /*## attribute CtrlIrefBallbreakdetBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasBbdBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_CLOCKPLLBits_t
* RegisterName: globbias_clockpll
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_clockpll_bg
	* Description: Control bias current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefClockpllBg: 6;        /*## attribute CtrlIrefClockpllBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasClockpllBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_LOTRIPLERBits_t
* RegisterName: globbias_lotripler
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_lotripler_bg
	* Description: Control bias BG current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefLotriplerBg: 6;        /*## attribute CtrlIrefLotriplerBg */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasLotriplerBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_SNSBits_t
* RegisterName: globbias_sns
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_sns_bgr
	* Description: Control BGR bias current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSnsBgr: 6;        /*## attribute CtrlIrefSnsBgr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasSnsBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_LOCAL_LDOBits_t
* RegisterName: globbias_local_ldo
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_local_ldo
	* Description: Control bias current for ldo1v1. 5 bits control, range 5?A-40?A, step 1,167?A
	*/
    uint32 CtrlIrefLocalLdo: 5;        /*## attribute CtrlIrefLocalLdo */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasLocalLdoBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_REFERENCEBits_t
* RegisterName: globbias_reference
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: en_ptat_ext
	* Description: Select internal PTAT or external reference current. If 1, external reference current is used for biasing
	*/
    uint32 EnPtatExt: 1;        /*## attribute EnPtatExt */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: en_bgr_ext
	* Description: Select internal BGR  or external reference current. If 1, external reference current is used for biasing
	*/
    uint32 EnBgrExt: 1;        /*## attribute EnBgrExt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod09_GlobbiasReferenceBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_TEST_BGRBits_t
* RegisterName: globbias_test_bgr
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_bgr_test
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefBgrTest: 6;        /*## attribute CtrlIrefBgrTest */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasTestBgrBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_TEST_PTATBits_t
* RegisterName: globbias_test_ptat
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: ctrl_iref_ptat_test
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C?
	*/
    uint32 CtrlIrefPtatTest: 6;        /*## attribute CtrlIrefPtatTest */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasTestPtatBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_PTAT_OFFSET_CALIBBits_t
* RegisterName: globbias_ptat_offset_calib
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: ptat_offset_calib_ctrl
	* Description: Based on the 6th bit, the interface controls ctrl_ptat_offset_bg_p<5:0>, ctrl_ptat_offset_bg_n<5:0> will be driven towards bias analog
	* 1. if reg<6>=0 then ctrl_ptat_offset_bg_p<5:0>= NOT(reg<5:0>) & ctrl_ptat_offset_bg_n<5:0>=0
	* 2. if reg<6>=1 then ctrl_ptat_offset_bg_p<5:0>=111111 & ctrl_ptat_offset_bg_n<5:0>=reg<5:0>
	*/
    uint32 PtatOffsetCalibCtrl: 7;        /*## attribute PtatOffsetCalibCtrl */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_PON_LOCAL_LDOBits_t
* RegisterName: globbias_pon_local_ldo
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: pon_local_ldo
	* Description: power on local ldo supply
	*/
    uint32 PonLocalLdo: 1;        /*## attribute PonLocalLdo */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoBits_t;
    /**
* Nxp_Tef810x_Mod09_GLOBBIAS_PON1V8Bits_t
* RegisterName: globbias_pon1v8
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: pon1v8_int
	* Description: Enables the level shifter of the analog IP. OR-gated with pon-bit from central control. 
	* In application central control will control the level shifter. So pon1v8_int is kept for internal validation only
	*/
    uint32 Pon1V8Int: 1;        /*## attribute Pon1V8Int */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod09_GlobbiasPon1V8Bits_t;
    /**
* Nxp_Tef810x_Mod09_MODULEIDBits_t
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
}Nxp_Tef810x_Mod09_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod09_GlobbiasTx1Bits_t
* RegisterName: globbias_tx1
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00002828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 18;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx1_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx1Ptat: 6;        /*## attribute CtrlIrefTx1Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_tx1_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx1Bg: 6;        /*## attribute CtrlIrefTx1Bg */
}Nxp_Tef810x_Mod09_GlobbiasTx1Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasTx2Bits_t
* RegisterName: globbias_tx2
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00002828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 18;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx2_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx2Ptat: 6;        /*## attribute CtrlIrefTx2Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_tx2_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx2Bg: 6;        /*## attribute CtrlIrefTx2Bg */
}Nxp_Tef810x_Mod09_GlobbiasTx2Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasTx3Bits_t
* RegisterName: globbias_tx3
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00002828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 18;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_tx3_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefTx3Ptat: 6;        /*## attribute CtrlIrefTx3Ptat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_tx3_bg
	* Description: Control BG bias current for TX3. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefTx3Bg: 6;        /*## attribute CtrlIrefTx3Bg */
}Nxp_Tef810x_Mod09_GlobbiasTx3Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasRx1Bits_t
* RegisterName: globbias_rx1
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_rx1_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx1Ptat: 6;        /*## attribute CtrlIrefRx1Ptat */
}Nxp_Tef810x_Mod09_GlobbiasRx1Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasRx2Bits_t
* RegisterName: globbias_rx2
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_rx2_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx2Ptat: 6;        /*## attribute CtrlIrefRx2Ptat */
}Nxp_Tef810x_Mod09_GlobbiasRx2Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasRx3Bits_t
* RegisterName: globbias_rx3
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_rx3_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx3Ptat: 6;        /*## attribute CtrlIrefRx3Ptat */
}Nxp_Tef810x_Mod09_GlobbiasRx3Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasRx4Bits_t
* RegisterName: globbias_rx4
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_rx4_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefRx4Ptat: 6;        /*## attribute CtrlIrefRx4Ptat */
}Nxp_Tef810x_Mod09_GlobbiasRx4Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasMasterclkBits_t
* RegisterName: globbias_masterclk
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_masterclk_bgr
	* Description: Buffers BG:
	* Control  bias BG untrimmed current for master clock. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefMasterclkBgr: 6;        /*## attribute CtrlIrefMasterclkBgr */
}Nxp_Tef810x_Mod09_GlobbiasMasterclkBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasChirpgenBits_t
* RegisterName: globbias_chirpgen
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x00002828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 18;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_chirpgen_bgr
	* Description: Control BGR bias current for chirp generator. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefChirpgenBgr: 6;        /*## attribute CtrlIrefChirpgenBgr */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_chirpgen_bg
	* Description: Control BG   bias current for chirp generator. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefChirpgenBg: 6;        /*## attribute CtrlIrefChirpgenBg */
}Nxp_Tef810x_Mod09_GlobbiasChirpgenBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasLoInterfaceBits_t
* RegisterName: globbias_lo_interface
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00002828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 18;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_interface_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefInterfacePtat: 6;        /*## attribute CtrlIrefInterfacePtat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_interface_bg
	* Description: Control BG bias current for interface. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefInterfaceBg: 6;        /*## attribute CtrlIrefInterfaceBg */
}Nxp_Tef810x_Mod09_GlobbiasLoInterfaceBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasAdc12Bits_t
* RegisterName: globbias_adc12
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_adc12_bgr
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAdc12Bgr: 6;        /*## attribute CtrlIrefAdc12Bgr */
}Nxp_Tef810x_Mod09_GlobbiasAdc12Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasAdc34Bits_t
* RegisterName: globbias_adc34
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_adc34_bgr
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAdc34Bgr: 6;        /*## attribute CtrlIrefAdc34Bgr */
}Nxp_Tef810x_Mod09_GlobbiasAdc34Bits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasAtbipBits_t
* RegisterName: globbias_atbip
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_atbip_bgr
	* Description: Control BGR test  current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefAtbipBgr: 6;        /*## attribute CtrlIrefAtbipBgr */
}Nxp_Tef810x_Mod09_GlobbiasAtbipBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasSsbmodBits_t
* RegisterName: globbias_ssbmod
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x00282828
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_ssbmod_ptat
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C
	*/
    uint32 CtrlIrefSsbmodPtat: 6;        /*## attribute CtrlIrefSsbmodPtat */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctrl_iref_ssbmod_bgr
	* Description: Control BGR test  current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSsbmodBgr: 6;        /*## attribute CtrlIrefSsbmodBgr */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ctrl_iref_ssbmod_bg
	* Description: Control BG bias current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSsbmodBg: 6;        /*## attribute CtrlIrefSsbmodBg */
}Nxp_Tef810x_Mod09_GlobbiasSsbmodBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasBbdBits_t
* RegisterName: globbias_bbd
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_ballbreakdet_bg
	* Description: Control bias BG current for ball break detector. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefBallbreakdetBg: 6;        /*## attribute CtrlIrefBallbreakdetBg */
}Nxp_Tef810x_Mod09_GlobbiasBbdBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasClockpllBits_t
* RegisterName: globbias_clockpll
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_clockpll_bg
	* Description: Control bias current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefClockpllBg: 6;        /*## attribute CtrlIrefClockpllBg */
}Nxp_Tef810x_Mod09_GlobbiasClockpllBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasLotriplerBits_t
* RegisterName: globbias_lotripler
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_lotripler_bg
	* Description: Control bias BG current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefLotriplerBg: 6;        /*## attribute CtrlIrefLotriplerBg */
}Nxp_Tef810x_Mod09_GlobbiasLotriplerBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasSnsBits_t
* RegisterName: globbias_sns
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_sns_bgr
	* Description: Control BGR bias current for pll. 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefSnsBgr: 6;        /*## attribute CtrlIrefSnsBgr */
}Nxp_Tef810x_Mod09_GlobbiasSnsBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasLocalLdoBits_t
* RegisterName: globbias_local_ldo
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x0000000D
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_local_ldo
	* Description: Control bias current for ldo1v1. 5 bits control, range 5?A-40?A, step 1,167?A
	*/
    uint32 CtrlIrefLocalLdo: 5;        /*## attribute CtrlIrefLocalLdo */
}Nxp_Tef810x_Mod09_GlobbiasLocalLdoBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasReferenceBits_t
* RegisterName: globbias_reference
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: en_bgr_ext
	* Description: Select internal BGR  or external reference current. If 1, external reference current is used for biasing
	*/
    uint32 EnBgrExt: 1;        /*## attribute EnBgrExt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_ptat_ext
	* Description: Select internal PTAT or external reference current. If 1, external reference current is used for biasing
	*/
    uint32 EnPtatExt: 1;        /*## attribute EnPtatExt */
}Nxp_Tef810x_Mod09_GlobbiasReferenceBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasTestBgrBits_t
* RegisterName: globbias_test_bgr
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_bgr_test
	* Description: Control BGR test current: 6 bits control, range 0-157.5uA, step 2.5uA
	*/
    uint32 CtrlIrefBgrTest: 6;        /*## attribute CtrlIrefBgrTest */
}Nxp_Tef810x_Mod09_GlobbiasTestBgrBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasTestPtatBits_t
* RegisterName: globbias_test_ptat
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: ctrl_iref_ptat_test
	* Description: Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA? to ?Control PTAT test current: 6 bits control, range 0-157.5uA, step 2.5uA, @25C?
	*/
    uint32 CtrlIrefPtatTest: 6;        /*## attribute CtrlIrefPtatTest */
}Nxp_Tef810x_Mod09_GlobbiasTestPtatBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibBits_t
* RegisterName: globbias_ptat_offset_calib
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: ptat_offset_calib_ctrl
	* Description: Based on the 6th bit, the interface controls ctrl_ptat_offset_bg_p<5:0>, ctrl_ptat_offset_bg_n<5:0> will be driven towards bias analog
	* 1. if reg<6>=0 then ctrl_ptat_offset_bg_p<5:0>= NOT(reg<5:0>) & ctrl_ptat_offset_bg_n<5:0>=0
	* 2. if reg<6>=1 then ctrl_ptat_offset_bg_p<5:0>=111111 & ctrl_ptat_offset_bg_n<5:0>=reg<5:0>
	*/
    uint32 PtatOffsetCalibCtrl: 7;        /*## attribute PtatOffsetCalibCtrl */
}Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoBits_t
* RegisterName: globbias_pon_local_ldo
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
	* BitsName: pon_local_ldo
	* Description: power on local ldo supply
	*/
    uint32 PonLocalLdo: 1;        /*## attribute PonLocalLdo */
}Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoBits_t;
    /**
* Nxp_Tef810x_Mod09_GlobbiasPon1V8Bits_t
* RegisterName: globbias_pon1v8
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: pon1v8_int
	* Description: Enables the level shifter of the analog IP. OR-gated with pon-bit from central control. 
	* In application central control will control the level shifter. So pon1v8_int is kept for internal validation only
	*/
    uint32 Pon1V8Int: 1;        /*## attribute Pon1V8Int */
}Nxp_Tef810x_Mod09_GlobbiasPon1V8Bits_t;
    /**
* Nxp_Tef810x_Mod09_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00092201
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
}Nxp_Tef810x_Mod09_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod09_GlobbiasTx1Union_t
* Nxp_Tef810x_Mod09_GlobbiasTx1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasTx1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasTx1Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasTx2Union_t
* Nxp_Tef810x_Mod09_GlobbiasTx2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasTx2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasTx2Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasTx3Union_t
* Nxp_Tef810x_Mod09_GlobbiasTx3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasTx3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasTx3Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasRx1Union_t
* Nxp_Tef810x_Mod09_GlobbiasRx1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasRx1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasRx1Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasRx2Union_t
* Nxp_Tef810x_Mod09_GlobbiasRx2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasRx2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasRx2Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasRx3Union_t
* Nxp_Tef810x_Mod09_GlobbiasRx3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasRx3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasRx3Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasRx4Union_t
* Nxp_Tef810x_Mod09_GlobbiasRx4Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasRx4Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasRx4Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasMasterclkUnion_t
* Nxp_Tef810x_Mod09_GlobbiasMasterclkUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasMasterclkBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasMasterclkUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasChirpgenUnion_t
* Nxp_Tef810x_Mod09_GlobbiasChirpgenUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasChirpgenBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasChirpgenUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasLoInterfaceUnion_t
* Nxp_Tef810x_Mod09_GlobbiasLoInterfaceUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasLoInterfaceBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasLoInterfaceUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasAdc12Union_t
* Nxp_Tef810x_Mod09_GlobbiasAdc12Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasAdc12Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasAdc12Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasAdc34Union_t
* Nxp_Tef810x_Mod09_GlobbiasAdc34Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasAdc34Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasAdc34Union_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasAtbipUnion_t
* Nxp_Tef810x_Mod09_GlobbiasAtbipUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasAtbipBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasAtbipUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasSsbmodUnion_t
* Nxp_Tef810x_Mod09_GlobbiasSsbmodUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasSsbmodBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasSsbmodUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasBbdUnion_t
* Nxp_Tef810x_Mod09_GlobbiasBbdUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasBbdBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasBbdUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasClockpllUnion_t
* Nxp_Tef810x_Mod09_GlobbiasClockpllUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasClockpllBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasClockpllUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasLotriplerUnion_t
* Nxp_Tef810x_Mod09_GlobbiasLotriplerUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasLotriplerBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasLotriplerUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasSnsUnion_t
* Nxp_Tef810x_Mod09_GlobbiasSnsUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasSnsBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasSnsUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasLocalLdoUnion_t
* Nxp_Tef810x_Mod09_GlobbiasLocalLdoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasLocalLdoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasLocalLdoUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasReferenceUnion_t
* Nxp_Tef810x_Mod09_GlobbiasReferenceUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasReferenceBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasReferenceUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasTestBgrUnion_t
* Nxp_Tef810x_Mod09_GlobbiasTestBgrUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasTestBgrBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasTestBgrUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasTestPtatUnion_t
* Nxp_Tef810x_Mod09_GlobbiasTestPtatUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasTestPtatBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasTestPtatUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibUnion_t
* Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoUnion_t
* Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoUnion_t;
/**
* Nxp_Tef810x_Mod09_GlobbiasPon1V8Union_t
* Nxp_Tef810x_Mod09_GlobbiasPon1V8Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_GlobbiasPon1V8Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_GlobbiasPon1V8Union_t;
/**
* Nxp_Tef810x_Mod09_ModuleidUnion_t
* Nxp_Tef810x_Mod09_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod09_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod09_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod09_GlobalBiasRegister_t
 * Nxp_Tef810x_Mod09_GlobalBiasRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: globbias_tx1
    * AddressOffset: 0x000
    * ResetValue: 0x00002828
    * Description: TX1 bias current settings.
    */
    Nxp_Tef810x_Mod09_GlobbiasTx1Union_t GlobbiasTx1_ust;        /*## attribute GlobbiasTx1_ust */
  /**
    * RegisterName: globbias_tx2
    * AddressOffset: 0x004
    * ResetValue: 0x00002828
    * Description: TX2 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasTx2Union_t GlobbiasTx2_ust;        /*## attribute GlobbiasTx2_ust */
  /**
    * RegisterName: globbias_tx3
    * AddressOffset: 0x008
    * ResetValue: 0x00002828
    * Description: TX3 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasTx3Union_t GlobbiasTx3_ust;        /*## attribute GlobbiasTx3_ust */
  /**
    * RegisterName: globbias_rx1
    * AddressOffset: 0x00C
    * ResetValue: 0x00000028
    * Description: RX1 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasRx1Union_t GlobbiasRx1_ust;        /*## attribute GlobbiasRx1_ust */
  /**
    * RegisterName: globbias_rx2
    * AddressOffset: 0x010
    * ResetValue: 0x00000028
    * Description: RX2 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasRx2Union_t GlobbiasRx2_ust;        /*## attribute GlobbiasRx2_ust */
  /**
    * RegisterName: globbias_rx3
    * AddressOffset: 0x014
    * ResetValue: 0x00000028
    * Description: RX3 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasRx3Union_t GlobbiasRx3_ust;        /*## attribute GlobbiasRx3_ust */
  /**
    * RegisterName: globbias_rx4
    * AddressOffset: 0x018
    * ResetValue: 0x00000028
    * Description: RX4 bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasRx4Union_t GlobbiasRx4_ust;        /*## attribute GlobbiasRx4_ust */
  /**
    * RegisterName: globbias_masterclk
    * AddressOffset: 0x01C
    * ResetValue: 0x00000028
    * Description: Master clock bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasMasterclkUnion_t GlobbiasMasterclk_ust;        /*## attribute GlobbiasMasterclk_ust */
  /**
    * RegisterName: globbias_chirpgen
    * AddressOffset: 0x020
    * ResetValue: 0x00002828
    * Description: Chirpgen bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasChirpgenUnion_t GlobbiasChirpgen_ust;        /*## attribute GlobbiasChirpgen_ust */
  /**
    * RegisterName: globbias_lo_interface
    * AddressOffset: 0x024
    * ResetValue: 0x00002828
    * Description: Lo interface bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasLoInterfaceUnion_t GlobbiasLoInterface_ust;        /*## attribute GlobbiasLoInterface_ust */
  /**
    * RegisterName: globbias_adc12
    * AddressOffset: 0x028
    * ResetValue: 0x00000028
    * Description: ADC12  bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasAdc12Union_t GlobbiasAdc12_ust;        /*## attribute GlobbiasAdc12_ust */
  /**
    * RegisterName: globbias_adc34
    * AddressOffset: 0x02C
    * ResetValue: 0x00000028
    * Description: ADC34  bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasAdc34Union_t GlobbiasAdc34_ust;        /*## attribute GlobbiasAdc34_ust */
  /**
    * RegisterName: globbias_atbip
    * AddressOffset: 0x030
    * ResetValue: 0x00000028
    * Description: ATB  bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasAtbipUnion_t GlobbiasAtbip_ust;        /*## attribute GlobbiasAtbip_ust */
  /**
    * RegisterName: globbias_ssbmod
    * AddressOffset: 0x034
    * ResetValue: 0x00282828
    * Description: RFBIST  bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasSsbmodUnion_t GlobbiasSsbmod_ust;        /*## attribute GlobbiasSsbmod_ust */
  /**
    * RegisterName: globbias_bbd
    * AddressOffset: 0x038
    * ResetValue: 0x00000028
    * Description: Ball break detector  bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasBbdUnion_t GlobbiasBbd_ust;        /*## attribute GlobbiasBbd_ust */
  /**
    * RegisterName: globbias_clockpll
    * AddressOffset: 0x03C
    * ResetValue: 0x00000028
    * Description: PLL bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasClockpllUnion_t GlobbiasClockpll_ust;        /*## attribute GlobbiasClockpll_ust */
  /**
    * RegisterName: globbias_lotripler
    * AddressOffset: 0x040
    * ResetValue: 0x00000028
    * Description: LO tripler bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasLotriplerUnion_t GlobbiasLotripler_ust;        /*## attribute GlobbiasLotripler_ust */
  /**
    * RegisterName: globbias_sns
    * AddressOffset: 0x044
    * ResetValue: 0x00000028
    * Description: Supply noise sensor bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasSnsUnion_t GlobbiasSns_ust;        /*## attribute GlobbiasSns_ust */
  /**
    * RegisterName: globbias_local_ldo
    * AddressOffset: 0x048
    * ResetValue: 0x0000000D
    * Description: Local ldo bias current settings
    */
    Nxp_Tef810x_Mod09_GlobbiasLocalLdoUnion_t GlobbiasLocalLdo_ust;        /*## attribute GlobbiasLocalLdo_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x04C
    * ResetValue: 0x0000002B
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: globbias_reference
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Control settings reference current
    */
    Nxp_Tef810x_Mod09_GlobbiasReferenceUnion_t GlobbiasReference_ust;        /*## attribute GlobbiasReference_ust */
  /**
    * RegisterName: globbias_test_bgr
    * AddressOffset: 0x054
    * ResetValue: 0x00000028
    * Description: Control settings for the bgr test current
    */
    Nxp_Tef810x_Mod09_GlobbiasTestBgrUnion_t GlobbiasTestBgr_ust;        /*## attribute GlobbiasTestBgr_ust */
  /**
    * RegisterName: globbias_test_ptat
    * AddressOffset: 0x058
    * ResetValue: 0x00000028
    * Description: Control settings for the ptat test current
    */
    Nxp_Tef810x_Mod09_GlobbiasTestPtatUnion_t GlobbiasTestPtat_ust;        /*## attribute GlobbiasTestPtat_ust */
  /**
    * RegisterName: globbias_ptat_offset_calib
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: Control settings for the ptat calibration
    */
    Nxp_Tef810x_Mod09_GlobbiasPtatOffsetCalibUnion_t GlobbiasPtatOffsetCalib_ust;        /*## attribute GlobbiasPtatOffsetCalib_ust */
  /**
    * RegisterName: globbias_pon_local_ldo
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: Power on control settings for local ldo
    */
    Nxp_Tef810x_Mod09_GlobbiasPonLocalLdoUnion_t GlobbiasPonLocalLdo_ust;        /*## attribute GlobbiasPonLocalLdo_ust */
  /**
    * RegisterName: globbias_pon1v8
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: Power on control settings for 1v8 supply
    */
    Nxp_Tef810x_Mod09_GlobbiasPon1V8Union_t GlobbiasPon1V8_ust;        /*## attribute GlobbiasPon1V8_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x06C
    * ResetValue: 0x0000001F
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x070
    * ResetValue: 0x000000FF
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x074
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x078
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x07C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x088
    * ResetValue: 0x28282828
    * Description: 	nan
    */
    uint32 Reserved09;

    uint32 gap01_au32[986];        /* gap 1 in register space */  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00092201
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod09_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod09_GlobalBiasRegister_t;

#endif
