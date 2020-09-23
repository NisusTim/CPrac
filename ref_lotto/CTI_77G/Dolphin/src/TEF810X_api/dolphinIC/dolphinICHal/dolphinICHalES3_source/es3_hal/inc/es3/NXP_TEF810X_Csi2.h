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
* @NXP_TEF810X_Csi2.h
*/
#ifndef NXP_TEF810X_CSI2_H
#define NXP_TEF810X_CSI2_H
#include "Std_Types.h"

#define CSI2_MODULE_ADDRESS 0x02
/**
*NXP_TEF810X_MOD02_TRIMREG0_U16
* RegisterName: MOD02_TrimReg0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x0A040218
*/
#define NXP_TEF810X_MOD02_TRIMREG0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD02_TRIMREG1_U16
* RegisterName: MOD02_TrimReg1
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x4DB1100F
*/
#define NXP_TEF810X_MOD02_TRIMREG1_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD02_TRIMREG2_U16
* RegisterName: MOD02_TrimReg2
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x10000000
*/
#define NXP_TEF810X_MOD02_TRIMREG2_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD02_TRIMREG3_U16
* RegisterName: MOD02_TrimReg3
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x0020C1FC
*/
#define NXP_TEF810X_MOD02_TRIMREG3_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16
* RegisterName: MOD02_DPHY_DFE_DLN_Register_0
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x0A0D0716
*/
#define NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_0_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16
* RegisterName: MOD02_DPHY_DFE_DLN_Register_1
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00061E07
*/
#define NXP_TEF810X_MOD02_DPHY_DFE_DLN_REGISTER_1_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16
* RegisterName: MOD02_DPHY_DFE_CLN_Register_0
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x080D0521
*/
#define NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_0_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16
* RegisterName: MOD02_DPHY_DFE_CLN_Register_1
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000006
*/
#define NXP_TEF810X_MOD02_DPHY_DFE_CLN_REGISTER_1_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD02_PPI_DATA_LANE_SWAP_REGISTER_U16
* RegisterName: MOD02_PPI_Data_Lane_Swap_Register
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x00000300
*/
#define NXP_TEF810X_MOD02_PPI_DATA_LANE_SWAP_REGISTER_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD02_FIFO_STATUS_REGISTER_U16
* RegisterName: MOD02_FIFO_status_Register
* AccessMode: READ
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_FIFO_STATUS_REGISTER_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD02_USD_PIXEL_MODE_CONTROL_REGISTER_U16
* RegisterName: MOD02_USD_Pixel_Mode_Control_Register
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_USD_PIXEL_MODE_CONTROL_REGISTER_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD02_YUV_PIXEL_MODE_CONTROL_REGISTER_U16
* RegisterName: MOD02_YUV_Pixel_Mode_Control_Register
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_YUV_PIXEL_MODE_CONTROL_REGISTER_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD02_RAW_PIXEL_MODE_CONTROL_REGISTER_U16
* RegisterName: MOD02_RAW_Pixel_Mode_Control_Register
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_RAW_PIXEL_MODE_CONTROL_REGISTER_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD02_PHY_TINIT_COUNT_REGISTER_U16
* RegisterName: MOD02_PHY_TINIT_Count_Register
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x0000FFFF
*/
#define NXP_TEF810X_MOD02_PHY_TINIT_COUNT_REGISTER_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16
* RegisterName: MOD02_VC0_compression_Prediction_Scheme_Register_1
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16
* RegisterName: MOD02_VC0_compression_Prediction_Scheme_Register_2
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16
* RegisterName: MOD02_VC1_compression_Prediction_Scheme_Register_1
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16
* RegisterName: MOD02_VC1_compression_Prediction_Scheme_Register_2
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16
* RegisterName: MOD02_VC2_compression_Prediction_Scheme_Register_1
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16
* RegisterName: MOD02_VC2_compression_Prediction_Scheme_Register_2
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16
* RegisterName: MOD02_VC3_compression_Prediction_Scheme_Register_1
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_1_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16
* RegisterName: MOD02_VC3_compression_Prediction_Scheme_Register_2
* AccessMode: READWRITE
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_2_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD02_PLL_COUNT_REGISTER_U16
* RegisterName: MOD02_PLL_Count_Register
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x00004E20
*/
#define NXP_TEF810X_MOD02_PLL_COUNT_REGISTER_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD02_DEVICE_READY_INDICATION_REGISTER_U16
* RegisterName: MOD02_Device_Ready_Indication_Register
* AccessMode: READ
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_DEVICE_READY_INDICATION_REGISTER_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG1_U16
* RegisterName: MOD02_Csi2AdaptConfigReg1
* AccessMode: READWRITE
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x0000002C
*/
#define NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG1_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16
* RegisterName: MOD02_Csi2AdaptConfigReg2
* AccessMode: READWRITE
* AddressRange: 0x0084 - 0x0088
* ResetValue: 0x0C810000
*/
#define NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG2_U16 (uint16)0x0084
/**
*NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG3_U16
* RegisterName: MOD02_Csi2AdaptConfigReg3
* AccessMode: READWRITE
* AddressRange: 0x0088 - 0x008C
* ResetValue: 0x00000001
*/
#define NXP_TEF810X_MOD02_CSI2ADAPTCONFIGREG3_U16 (uint16)0x0088
/**
*NXP_TEF810X_MOD02_CSI2_CRC_CTRL1_U16
* RegisterName: MOD02_csi2_crc_ctrl1
* AccessMode: READWRITE
* AddressRange: 0x008C - 0x0090
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD02_CSI2_CRC_CTRL1_U16 (uint16)0x008C
/**
*NXP_TEF810X_MOD02_CSI2_CRC_CTRL2_U16
* RegisterName: MOD02_csi2_crc_ctrl2
* AccessMode: READWRITE
* AddressRange: 0x0090 - 0x0094
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD02_CSI2_CRC_CTRL2_U16 (uint16)0x0090
/**
*NXP_TEF810X_MOD02_CSI2_CRC_CTRL3_U16
* RegisterName: MOD02_csi2_crc_ctrl3
* AccessMode: READWRITE
* AddressRange: 0x0094 - 0x0098
* ResetValue: 0x00000110
*/
#define NXP_TEF810X_MOD02_CSI2_CRC_CTRL3_U16 (uint16)0x0094
/**
*NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16
* RegisterName: MOD02_pdc_config_reg
* AccessMode: READWRITE
* AddressRange: 0x0098 - 0x009C
* ResetValue: 0x00A9A700
*/
#define NXP_TEF810X_MOD02_PDC_CONFIG_REG_U16 (uint16)0x0098
/**
*NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16
* RegisterName: MOD02_csi2_txn_ctrl
* AccessMode: READWRITE
* AddressRange: 0x009C - 0x00A0
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_CSI2_TXN_CTRL_U16 (uint16)0x009C
/**
*NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16
* RegisterName: MOD02_Csi2TestModeControlReg
* AccessMode: READWRITE
* AddressRange: 0x00A0 - 0x00A4
* ResetValue: 0x00000FFF
*/
#define NXP_TEF810X_MOD02_CSI2TESTMODECONTROLREG_U16 (uint16)0x00A0
/**
*NXP_TEF810X_MOD02_MASTER_IDIV_CTRL_U16
* RegisterName: MOD02_master_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x00A4 - 0x00A8
* ResetValue: 0x040400B0
*/
#define NXP_TEF810X_MOD02_MASTER_IDIV_CTRL_U16 (uint16)0x00A4
/**
*NXP_TEF810X_MOD02_PDC_SHIFT_REG_IDIV_CTRL_U16
* RegisterName: MOD02_pdc_shift_reg_idiv_ctrl
* AccessMode: READWRITE
* AddressRange: 0x00AC - 0x00B0
* ResetValue: 0x00000002
*/
#define NXP_TEF810X_MOD02_PDC_SHIFT_REG_IDIV_CTRL_U16 (uint16)0x00AC
/**
*NXP_TEF810X_MOD02_REF_CNTR_INIT_U16
* RegisterName: MOD02_ref_cntr_init
* AccessMode: READWRITE
* AddressRange: 0x00BC - 0x00C0
* ResetValue: 0x01E00028
*/
#define NXP_TEF810X_MOD02_REF_CNTR_INIT_U16 (uint16)0x00BC
/**
*NXP_TEF810X_MOD02_FREQ_COUNTER_START_U16
* RegisterName: MOD02_freq_counter_start
* AccessMode: READWRITE
* AddressRange: 0x00C0 - 0x00C4
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD02_FREQ_COUNTER_START_U16 (uint16)0x00C0
/**
*NXP_TEF810X_MOD02_FREQ_COUNTER_READ_VALUE_U16
* RegisterName: MOD02_freq_counter_read_value
* AccessMode: READ
* AddressRange: 0x00C4 - 0x00C8
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_FREQ_COUNTER_READ_VALUE_U16 (uint16)0x00C4
/**
*NXP_TEF810X_MOD02_REF_COUNTER_READ_VALUE_U16
* RegisterName: MOD02_ref_counter_read_value
* AccessMode: READ
* AddressRange: 0x00C8 - 0x00CC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_REF_COUNTER_READ_VALUE_U16 (uint16)0x00C8
/**
*NXP_TEF810X_MOD02_ATB_SET_TRIM_U16
* RegisterName: MOD02_atb_set_trim
* AccessMode: READWRITE
* AddressRange: 0x00D8 - 0x00DC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD02_ATB_SET_TRIM_U16 (uint16)0x00D8
/**
*NXP_TEF810X_MOD02_MODULEID_U16
* RegisterName: MOD02_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00023301
*/
#define NXP_TEF810X_MOD02_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod02_TRIMREG0Bits_t
* RegisterName: TrimReg0
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: lptx_trim_slew
	* Description: trim control for lp slew rate
	*/
    uint32 LptxTrimSlew: 2;        /*## attribute LptxTrimSlew */
   /**
	* BitsName: tr_sel
	* Description: Rise time and fall time trimming
	* for predriver
	*/
    uint32 TrSel: 2;        /*## attribute TrSel */
   /**
	* BitsName: gdefault
	* Description: trim gain for front-end amplifier
	*/
    uint32 Gdefault: 1;        /*## attribute Gdefault */
   /**
	* BitsName: gnctrl
	* Description: trim gain for front-end amplifier
	*/
    uint32 Gnctrl: 2;        /*## attribute Gnctrl */
   /**
	* BitsName: rxcksel
	* Description: trim delay control for receiver
	* data lane 0
	*/
    uint32 Rxcksel: 1;        /*## attribute Rxcksel */
   /**
	* BitsName: rxhsdpol
	* Description: Change polarity of high speed
	* receive data
	*/
    uint32 Rxhsdpol: 1;        /*## attribute Rxhsdpol */
   /**
	* BitsName: capen_pwl
	* Description: trim capacitor for pulse-rejection
	*/
    uint32 CapenPwl: 2;        /*## attribute CapenPwl */
   /**
	* BitsName: cdpd
	* Description: Contention detection power
	* down
	*/
    uint32 Cdpd: 1;        /*## attribute Cdpd */
   /**
	* BitsName: HS_DC_test_en
	* Description: HS enable trim for testing DC
	* characteristics of the HS driver
	*/
    uint32 HsDcTestEn: 1;        /*## attribute HsDcTestEn */
   /**
	* BitsName: LP_DC_test_en
	* Description: LP enable trim for testing DC
	* characteristics of the LP driver
	*/
    uint32 LpDcTestEn: 1;        /*## attribute LpDcTestEn */
   /**
	* BitsName: DC_test_data
	* Description: Test data for DC in LP and Hsmode
	*/
    uint32 DcTestData: 1;        /*## attribute DcTestData */
   /**
	* BitsName: trim_bit_glitch
	* Description: input selection trimbit(Comp_out
	* or vdd)
	*/
    uint32 TrimBitGlitch: 1;        /*## attribute TrimBitGlitch */
   /**
	* BitsName: iref_20u_cp_trim
	* Description: glitch removal ckt current trim
	*/
    uint32 Iref20UCpTrim: 2;        /*## attribute Iref20UCpTrim */
   /**
	* BitsName: pulser_bypass
	* Description: trim control for pulse rejection
	* bypass
	*/
    uint32 PulserBypass: 1;        /*## attribute PulserBypass */
   /**
	* BitsName: vco_selection
	* Description: Vco selection control
	*/
    uint32 VcoSelection: 1;        /*## attribute VcoSelection */
   /**
	* BitsName: latch_inv_delay_ctrl
	* Description: trim delay in latch block
	*/
    uint32 LatchInvDelayCtrl: 3;        /*## attribute LatchInvDelayCtrl */
   /**
	* BitsName: ddr_delay_sel
	* Description: DDR delay trim control
	* Leave as reset if not needed explicitly.
	*/
    uint32 DdrDelaySel: 2;        /*## attribute DdrDelaySel */
   /**
	* BitsName: trim_imp
	* Description: Tx Impedance Control
	*/
    uint32 TrimImp: 2;        /*## attribute TrimImp */
   /**
	* BitsName: trim_ff_bypass
	* Description: trim to bypass flip-flop for LPTX
	* in clock lane and data lanes 1,2
	* and 3
	*/
    uint32 TrimFfBypass: 1;        /*## attribute TrimFfBypass */
   /**
	* BitsName: ext_high_vco_en
	* Description: External trim bit control to enable
	* the high vco
	*/
    uint32 ExtHighVcoEn: 1;        /*## attribute ExtHighVcoEn */
   /**
	* BitsName: ext_low_vco_en
	* Description: External trim bit control to enable
	* the low vco
	*/
    uint32 ExtLowVcoEn: 1;        /*## attribute ExtLowVcoEn */
   /**
	* BitsName: hs_rx_fixed_delay_enable
	* Description: Fix delay enable control for Rx
	*/
    uint32 HsRxFixedDelayEnable: 1;        /*## attribute HsRxFixedDelayEnable */
   /**
	* BitsName: hs_tx_fixed_delay_enable
	* Description: Fix delay enable control for Tx.
	*/
    uint32 HsTxFixedDelayEnable: 1;        /*## attribute HsTxFixedDelayEnable */
}Nxp_Tef810x_Mod02_Trimreg0Bits_t;
    /**
* Nxp_Tef810x_Mod02_TRIMREG1Bits_t
* RegisterName: TrimReg1
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: cnta
	* Description: Divider ratio Counter A
	*/
    uint32 Cnta: 6;        /*## attribute Cnta */
   /**
	* BitsName: cntb
	* Description: Dphy PLL divider value.Combination of cnta and cntb determines the PLL o/p frequency.
	* Need to be changed for different decimation factors and different no of lanes .Divider ratio Counter B
	*/
    uint32 Cntb: 1;        /*## attribute Cntb */
   /**
	* BitsName: dlpf
	* Description: Discharge lpf capacitor to zero
	*/
    uint32 Dlpf: 1;        /*## attribute Dlpf */
   /**
	* BitsName: dlpf_reg_sel
	* Description: Discharge lpf register bit select
	*/
    uint32 DlpfRegSel: 1;        /*## attribute DlpfRegSel */
   /**
	* BitsName: refin_sel
	* Description: Reference clock signal control
	*/
    uint32 RefinSel: 3;        /*## attribute RefinSel */
   /**
	* BitsName: spare_bits
	* Description: spare_bits
	*/
    uint32 SpareBits: 1;        /*## attribute SpareBits */
   /**
	* BitsName: pll_lock_trim
	* Description: External trim bit control to enable
	* pll lock
	*/
    uint32 PllLockTrim: 1;        /*## attribute PllLockTrim */
   /**
	* BitsName: bwb
	* Description: Chargepump current tunability
	*/
    uint32 Bwb: 3;        /*## attribute Bwb */
   /**
	* BitsName: res
	* Description: LPF Resistor tunability
	*/
    uint32 Res: 3;        /*## attribute Res */
   /**
	* BitsName: Plltstcksel
	* Description: PLL Test clock selection control
	*/
    uint32 Plltstcksel: 2;        /*## attribute Plltstcksel */
   /**
	* BitsName: tstodby4
	* Description: PLL Test output selection (div4/
	* div8)
	*/
    uint32 Tstodby4: 1;        /*## attribute Tstodby4 */
   /**
	* BitsName: cdhigh_trim
	* Description: trim control for CD high resistor
	* control
	*/
    uint32 CdhighTrim: 3;        /*## attribute CdhighTrim */
   /**
	* BitsName: cdlow_trim
	* Description: trim control for CD low resistor
	* control
	*/
    uint32 CdlowTrim: 3;        /*## attribute CdlowTrim */
   /**
	* BitsName: trim_hstx_ldo_pd
	* Description: power down register to control
	* the hstx ldo
	*/
    uint32 TrimHstxLdoPd: 1;        /*## attribute TrimHstxLdoPd */
   /**
	* BitsName: rtermctrl
	* Description: termination resistance control
	*/
    uint32 Rtermctrl: 2;        /*## attribute Rtermctrl */
}Nxp_Tef810x_Mod02_Trimreg1Bits_t;
    /**
* Nxp_Tef810x_Mod02_TRIMREG2Bits_t
* RegisterName: TrimReg2
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: rstn_reg_en
	* Description: Enable Reset input through register
	*/
    uint32 RstnRegEn: 1;        /*## attribute RstnRegEn */
   /**
	* BitsName: rstn_reg
	* Description: Reset input through register
	*/
    uint32 RstnReg: 1;        /*## attribute RstnReg */
   /**
	* BitsName: pllpd_reg
	* Description: Power down for pll
	*/
    uint32 PllpdReg: 1;        /*## attribute PllpdReg */
   /**
	* BitsName: pllpden
	* Description: Register control enable for pll
	* power down
	*/
    uint32 Pllpden: 1;        /*## attribute Pllpden */
   /**
	* BitsName: pllrst_reg
	* Description: Pll reset
	*/
    uint32 PllrstReg: 1;        /*## attribute PllrstReg */
   /**
	* BitsName: txhsen_reg_ck
	* Description: Enable register control for HSTX clk
	*/
    uint32 TxhsenRegCk: 1;        /*## attribute TxhsenRegCk */
   /**
	* BitsName: txhsen_reg_d3_d0
	* Description: Enable register control for HSTX data line
	*/
    uint32 TxhsenRegD3D0: 4;        /*## attribute TxhsenRegD3D0 */
   /**
	* BitsName: reg_ctrl_hstx_en
	* Description: Register control enable for lane
	* HSTX enables
	*/
    uint32 RegCtrlHstxEn: 1;        /*## attribute RegCtrlHstxEn */
   /**
	* BitsName: txlpen_reg_ck
	* Description: 1 in lp mode and 0 in hs  clock lane
	*/
    uint32 TxlpenRegCk: 1;        /*## attribute TxlpenRegCk */
   /**
	* BitsName: txlpen_reg_d3_d0
	* Description: 1 in lp mode and 0 in hs mode data lane
	*/
    uint32 TxlpenRegD3D0: 4;        /*## attribute TxlpenRegD3D0 */
   /**
	* BitsName: reg_ctrl_lptx_en
	* Description: Register control enable for lane
	* lptx enables
	*/
    uint32 RegCtrlLptxEn: 1;        /*## attribute RegCtrlLptxEn */
   /**
	* BitsName: txpd_reg_ck
	* Description: Power down bit for Txlane of Clk Lane
	*/
    uint32 TxpdRegCk: 1;        /*## attribute TxpdRegCk */
   /**
	* BitsName: txpd_reg_d3_d0
	* Description: Power down bit for Txlane
	*/
    uint32 TxpdRegD3D0: 4;        /*## attribute TxpdRegD3D0 */
   /**
	* BitsName: reg_ctrl_tx_pd
	* Description: Register control enable for tx
	* lane power down
	*/
    uint32 RegCtrlTxPd: 1;        /*## attribute RegCtrlTxPd */
   /**
	* BitsName: rxhsen_reg_ck
	* Description: Enable register control for HSRX
	* clk
	*/
    uint32 RxhsenRegCk: 1;        /*## attribute RxhsenRegCk */
   /**
	* BitsName: rxhsen_reg_d3_d0
	* Description: Enable register control for HSRX
	*/
    uint32 RxhsenRegD3D0: 4;        /*## attribute RxhsenRegD3D0 */
   /**
	* BitsName: reg_ctrl_hsrx_en
	* Description: Register control enable for lane
	* HSRX enables
	*/
    uint32 RegCtrlHsrxEn: 1;        /*## attribute RegCtrlHsrxEn */
   /**
	* BitsName: rxlpen_reg_ck
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegCk: 1;        /*## attribute RxlpenRegCk */
   /**
	* BitsName: rxlpen_reg_d0
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD0: 1;        /*## attribute RxlpenRegD0 */
   /**
	* BitsName: rxlpen_reg_d1
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD1: 1;        /*## attribute RxlpenRegD1 */
}Nxp_Tef810x_Mod02_Trimreg2Bits_t;
    /**
* Nxp_Tef810x_Mod02_TRIMREG3Bits_t
* RegisterName: TrimReg3
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: rxlpen_reg_d3_d2
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD3D2: 2;        /*## attribute RxlpenRegD3D2 */
   /**
	* BitsName: reg_ctrl_lprx_en
	* Description: Register control enable for lane
	* lprx enables
	*/
    uint32 RegCtrlLprxEn: 1;        /*## attribute RegCtrlLprxEn */
   /**
	* BitsName: rxpd_reg_ck
	* Description: Power down bit for Rxlane of Clk Lane
	*/
    uint32 RxpdRegCk: 1;        /*## attribute RxpdRegCk */
   /**
	* BitsName: rxpd_reg_d3_d0
	* Description: Power down bit for data Rxlane
	*/
    uint32 RxpdRegD3D0: 4;        /*## attribute RxpdRegD3D0 */
   /**
	* BitsName: reg_ctrl_rx_pd
	* Description: Register control enable for rx
	* lane power down
	*/
    uint32 RegCtrlRxPd: 1;        /*## attribute RegCtrlRxPd */
   /**
	* BitsName: rtermen_reg_ck
	* Description: Register control for termination
	* enable clk
	*/
    uint32 RtermenRegCk: 1;        /*## attribute RtermenRegCk */
   /**
	* BitsName: rtermen_reg_d3_d0
	* Description: Register control for termination
	* enable data
	*/
    uint32 RtermenRegD3D0: 4;        /*## attribute RtermenRegD3D0 */
   /**
	* BitsName: rterm_reg_en
	* Description: Register control enable for termination
	*/
    uint32 RtermRegEn: 1;        /*## attribute RtermRegEn */
   /**
	* BitsName: trim_ff_bypass
	* Description: trim to bypass flip-flop for LPTX
	* in data lanes 0
	*/
    uint32 TrimFfBypass: 1;        /*## attribute TrimFfBypass */
   /**
	* BitsName: V2Ipd_BGPD
	* Description: Power down selection for BG,
	* bias(v2i)
	*/
    uint32 V2IpdBgpd: 1;        /*## attribute V2IpdBgpd */
   /**
	* BitsName: BW_res_sel
	* Description: PLL BW resistor selection control
	*/
    uint32 BwResSel: 1;        /*## attribute BwResSel */
   /**
	* BitsName: trim_s3_s0
	* Description: Common mode voltage control
	* for TX
	*/
    uint32 TrimS3S0: 4;        /*## attribute TrimS3S0 */
   /**
	* BitsName: bist_lane_trim_3_0
	* Description: Enable Bandgap offset cancellation
	* circuit
	*/
    uint32 BistLaneTrim30: 4;        /*## attribute BistLaneTrim30 */
   /**
	* BitsName: clk_pol_sel_ck
	* Description: trim control for clock polarity
	* selection of clk
	*/
    uint32 ClkPolSelCk: 1;        /*## attribute ClkPolSelCk */
   /**
	* BitsName: clk_pol_sel_d3_d0
	* Description: trim control for clock polarity
	* selection of data lane
	*/
    uint32 ClkPolSelD3D0: 4;        /*## attribute ClkPolSelD3D0 */
   /**
	* BitsName: vbg_sel
	* Description: Bandgap selection control
	*/
    uint32 VbgSel: 1;        /*## attribute VbgSel */
}Nxp_Tef810x_Mod02_Trimreg3Bits_t;
    /**
* Nxp_Tef810x_Mod02_DPHY_DFE_DLN_REGISTER_0Bits_t
* RegisterName: DPHY_DFE_DLN_Register_0
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: DFE_DLN_HS_ZERO_CNT
	* Description: This parameter specifies the number of byte clocks cycles the data lane shall wait to complete the HS-ZERO time
	*/
    uint32 DfeDlnHsZeroCnt: 8;        /*## attribute DfeDlnHsZeroCnt */
   /**
	* BitsName: DFE_DLN_HS_PREPARE
	* Description: This parameter specifies the number of clock cycles the data lane shall wait to complete the HS PREPARE time
	* [13:8]   -> In Byte Clock Cycles 
	* [15:14] -> In DDR Clock Cyles s
	*/
    uint32 DfeDlnHsPrepare: 8;        /*## attribute DfeDlnHsPrepare */
   /**
	* BitsName: DFE_DLN_HS_EXIT
	* Description: This parameter specifies the number of byte clock cycles the data lane shall wait to complete the HS-EXIT time
	*/
    uint32 DfeDlnHsExit: 8;        /*## attribute DfeDlnHsExit */
   /**
	* BitsName: DFE_DLN_HS_TRIAL
	* Description: This parameter specifies the number of byte clock cycles the data lane shall wait to complete the HS TRIAL time
	*/
    uint32 DfeDlnHsTrial: 8;        /*## attribute DfeDlnHsTrial */
}Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Bits_t;
    /**
* Nxp_Tef810x_Mod02_DPHY_DFE_DLN_REGISTER_1Bits_t
* RegisterName: DPHY_DFE_DLN_Register_1
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: DFE_DLN_RX_CNT
	* Description: This parameter specifies the number of byte clocks cycles the data lane shall wait before enabling the HS receiver
	*/
    uint32 DfeDlnRxCnt: 8;        /*## attribute DfeDlnRxCnt */
   /**
	* BitsName: DFE_DLN_SYNC_CNT
	* Description: This parameter specifies the number of byte clock cycles the
	* data lane shall wait before announcing an error on the
	* timeout of the SYNC pattern
	*/
    uint32 DfeDlnSyncCnt: 8;        /*## attribute DfeDlnSyncCnt */
   /**
	* BitsName: DFE_DLN_LPX_HS_CNT
	* Description: This parameter specifies the number of byte clock cycles required to accommodate an LP- xx state on the data lane
	*/
    uint32 DfeDlnLpxHsCnt: 8;        /*## attribute DfeDlnLpxHsCnt */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_DPHY_DFE_CLN_REGISTER_0Bits_t
* RegisterName: DPHY_DFE_CLN_Register_0
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: DFE_CLN_ZERO
	* Description: This parameter specifies the number of byte clocks cycles the clock lane transmitter module shall wait during the HS-ZERO sequence of the high speed clock transmission
	*/
    uint32 DfeClnZero: 8;        /*## attribute DfeClnZero */
   /**
	* BitsName: DFE_CLN_PREPARE
	* Description: This parameter specifies the number of  clock cycles the clock lane transmitter module shall wait during the prepare sequence of the high speed clock transmission
	* [13:8]   -> In Byte Clock Cycles 
	* [15:14] -> In DDR Clock Cyles s
	*/
    uint32 DfeClnPrepare: 8;        /*## attribute DfeClnPrepare */
   /**
	* BitsName: DFE_CLN_HS_EXIT
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait during the exit sequence of the high speed clock transmission
	*/
    uint32 DfeClnHsExit: 8;        /*## attribute DfeClnHsExit */
   /**
	* BitsName: DFE_CLN_HS_TRIAL
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait during the TRIAL sequence of the high speed clock transmission
	*/
    uint32 DfeClnHsTrial: 8;        /*## attribute DfeClnHsTrial */
}Nxp_Tef810x_Mod02_DphyDfeClnRegister0Bits_t;
    /**
* Nxp_Tef810x_Mod02_DPHY_DFE_CLN_REGISTER_1Bits_t
* RegisterName: DPHY_DFE_CLN_Register_1
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: DFE_CLN_LPX_HS_CNT
	* Description: This parameter specifies the number of byte clocks required to accommodate an LP-xx stat on the clock lane
	*/
    uint32 DfeClnLpxHsCnt: 8;        /*## attribute DfeClnLpxHsCnt */
   /**
	* BitsName: TCLK_PRE
	* Description: This parameter specifies that the HS clock shall be driven by the transmitter prior to any associated data lane beginning the transition from LP to HS mode. The parameter is in terms of number of TxByteClkHS
	*/
    uint32 TclkPre: 8;        /*## attribute TclkPre */
   /**
	* BitsName: TCLK_POST
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait before removing the clock lane request after the last associated data lane has transitioned to LP mode
	*/
    uint32 TclkPost: 8;        /*## attribute TclkPost */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_DphyDfeClnRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_PPI_DATA_LANE_SWAP_REGISTERBits_t
* RegisterName: PPI_Data_Lane_Swap_Register
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: SWAP_LANE0
	* Description: Set by the processor to enable the Lane-0 swapping. When enable the LANE0 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane0 : Lane0
	*  When ?01? : Swap : Lane0 : Lane1
	*  When ?10 : Swap : Lane0 : Lane2 
	* When ?11 : Swap : Lane0 : Lane3
	*/
    uint32 SwapLane0: 2;        /*## attribute SwapLane0 */
   /**
	* BitsName: SWAP_LANE1
	* Description: Set by the processor to enable the Lane-1 swapping. When enable the LANE1 PPI interface signal of Controller is driven on to respective Lane on the DPHY
	*  When ?00? : No Swap : Lane1 : Lane1 
	* When ?01? : Swap : Lane1 : Lane0 
	* When ?10 : Swap : Lane1 : Lane2 
	* When ?11 : Swap : Lane1 : Lane3
	*/
    uint32 SwapLane1: 2;        /*## attribute SwapLane1 */
   /**
	* BitsName: SWAP_LANE2
	* Description: Set by the processor to enable the Lane-2 swapping. When enable the LANE2 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane2 : Lane2
	*  When ?01? : Swap : Lane2 : Lane0 
	* When ?10 : Swap : Lane2 : Lane1 
	* When ?11 : Swap : Lane2 : Lane3
	*/
    uint32 SwapLane2: 2;        /*## attribute SwapLane2 */
   /**
	* BitsName: SWAP_LANE3
	* Description: Set by the processor to enable the Lane-3 swapping. When enable the LANE3 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane3 : Lane3 
	* When ?01? : Swap : Lane3 : Lane0 
	* When ?10 : Swap : Lane3 : Lane1
	*  When ?11 : Swap : Lane3 : Lane2
	*/
    uint32 SwapLane3: 2;        /*## attribute SwapLane3 */
   /**
	* BitsName: Number_of_Lanes
	* Description: Default: - 4-Lanes. Set by the processor to configure the number of PPI lanes 
	* When ?00? : One Lane Enabled (Lane-0) 
	* When ?01? : Two Lane Enabled (Lane-0,1) 
	* When ?10? : Three Lane Enabled( Lane-0,1,2) 
	* When ?11? : Four Lane Enabled( Lane-0,1,2,3)
	*/
    uint32 NumberOfLanes: 2;        /*## attribute NumberOfLanes */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_FIFO_STATUS_REGISTERBits_t
* RegisterName: FIFO_status_Register
* 
* AddressRange: 0xREAD - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: SENSOR_FIFO_EMPTY
	* Description: Indicates the SENSOR FIFO empty status
	*/
    uint32 SensorFifoEmpty: 1;        /*## attribute SensorFifoEmpty */
   /**
	* BitsName: SENSOR_FIFO_ALMOST_FULL
	* Description: Indicates the SENSOR FIFO threshold full status
	*/
    uint32 SensorFifoAlmostFull: 1;        /*## attribute SensorFifoAlmostFull */
   /**
	* BitsName: SENSOR_FIFO_FULL
	* Description: Indicates the SENSOR FIFO full status
	*/
    uint32 SensorFifoFull: 1;        /*## attribute SensorFifoFull */
   /**
	* BitsName: CSI_FIFO_EMPTY
	* Description: Indicates the CSI FIFO empty status
	*/
    uint32 CsiFifoEmpty: 1;        /*## attribute CsiFifoEmpty */
   /**
	* BitsName: CSI_FIFO_FULL
	* Description: Indicates the CSI FIFO threshold full status
	*/
    uint32 CsiFifoFull: 1;        /*## attribute CsiFifoFull */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_FifoStatusRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_USD_PIXEL_MODE_CONTROL_REGISTERBits_t
* RegisterName: USD_Pixel_Mode_Control_Register
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: USD_DATA_TYPE1_EN
	* Description: Set by the processor to configure the USD data_type1 one/two/three/four pixel mode
	*  ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType1En: 2;        /*## attribute UsdDataType1En */
   /**
	* BitsName: USD_DATA_TYPE2_EN
	* Description: Set by the processor to configure the USD data_type2 one/two/three/four pixel mode ?00? : One pixel mode configured ?01? : Two pixel mode configured ?10? : Three pixel mode configured ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType2En: 2;        /*## attribute UsdDataType2En */
   /**
	* BitsName: USD_DATA_TYPE3_EN
	* Description: Set by the processor to configure the USD data_type3 one/two/three/four pixel mode 
	* ?00? :One pixel mode configured 
	* ?01? :Two pixel mode configured
	*  ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType3En: 2;        /*## attribute UsdDataType3En */
   /**
	* BitsName: USD_DATA_TYPE4_EN
	* Description: Set by the processor to configure the USD data_type4 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11?: Four pixel mode configured
	*/
    uint32 UsdDataType4En: 2;        /*## attribute UsdDataType4En */
   /**
	* BitsName: USD_DATA_TYPE5_EN
	* Description: Set by the processor to configure the USD data_type5 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured
	*  ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType5En: 2;        /*## attribute UsdDataType5En */
   /**
	* BitsName: USD_DATA_TYPE6_EN
	* Description: Set by the processor to configure the USD data_type6 one/two/three/four pixel mode
	*  ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType6En: 2;        /*## attribute UsdDataType6En */
   /**
	* BitsName: USD_DATA_TYPE7_EN
	* Description: Set by the processor to configure the USD data_type7 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType7En: 2;        /*## attribute UsdDataType7En */
   /**
	* BitsName: USD_DATA_TYPE8_EN
	* Description: Set by the processor to configure the USD data_type8 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType8En: 2;        /*## attribute UsdDataType8En */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_YUV_PIXEL_MODE_CONTROL_REGISTERBits_t
* RegisterName: YUV_Pixel_Mode_Control_Register
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: YUV422_8BIT_EN
	* Description: Set by the processor to configure the YUV422 8-bit one/two pixel mode ?00? : One pixel mode configured ?01? : Two pixel mode configured ?10? : NA ?11? : NA
	*/
    uint32 Yuv4228BitEn: 2;        /*## attribute Yuv4228BitEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 10;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_RAW_PIXEL_MODE_CONTROL_REGISTERBits_t
* RegisterName: RAW_Pixel_Mode_Control_Register
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: RAW8_EN
	* Description: Set by the processor to configure RAW8 one/two/three/four pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 Raw8En: 2;        /*## attribute Raw8En */
   /**
	* BitsName: RAW10_EN
	* Description: Set by the processor to configure RAW10 one/two/three pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : NA
	*/
    uint32 Raw10En: 2;        /*## attribute Raw10En */
   /**
	* BitsName: RAW12_EN
	* Description: Set by the processor to configure RAW12 one/two pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : NA 
	* ?11? : NA
	*/
    uint32 Raw12En: 2;        /*## attribute Raw12En */
   /**
	* BitsName: RAW14_EN
	* Description: Set by the processor to configure RAW14 one/two pixel mode ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : NA
	*  ?11? : NA
	*/
    uint32 Raw14En: 2;        /*## attribute Raw14En */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 20;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod02_RawPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_PHY_TINIT_COUNT_REGISTERBits_t
* RegisterName: PHY_TINIT_Count_Register
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: TINIT_TIMER
	* Description: This parameter specifies the number of txbyte clocks cycles the CSI-2 controller should wait to start accepting the data from the sensor interface.
	*/
    uint32 TinitTimer: 32;        /*## attribute TinitTimer */
}Nxp_Tef810x_Mod02_PhyTinitCountRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_1Bits_t
* RegisterName: VC0_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction1
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction1: 32;        /*## attribute CpmpressionPrediction1 */
}Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC0_COMPRESSION_PREDICTION_SCHEME_REGISTER_2Bits_t
* RegisterName: VC0_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction2
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction2: 32;        /*## attribute CpmpressionPrediction2 */
}Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_1Bits_t
* RegisterName: VC1_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction3
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction3: 32;        /*## attribute CpmpressionPrediction3 */
}Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC1_COMPRESSION_PREDICTION_SCHEME_REGISTER_2Bits_t
* RegisterName: VC1_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction4
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction4: 32;        /*## attribute CpmpressionPrediction4 */
}Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_1Bits_t
* RegisterName: VC2_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction5
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction5: 32;        /*## attribute CpmpressionPrediction5 */
}Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC2_COMPRESSION_PREDICTION_SCHEME_REGISTER_2Bits_t
* RegisterName: VC2_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction6
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction6: 32;        /*## attribute CpmpressionPrediction6 */
}Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_1Bits_t
* RegisterName: VC3_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction7
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction7: 32;        /*## attribute CpmpressionPrediction7 */
}Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_VC3_COMPRESSION_PREDICTION_SCHEME_REGISTER_2Bits_t
* RegisterName: VC3_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0xREADWRITE - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction8
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction8: 32;        /*## attribute CpmpressionPrediction8 */
}Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_PLL_COUNT_REGISTERBits_t
* RegisterName: PLL_Count_Register
* 
* AddressRange: 0xREADWRITE - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: PLL_CNT
	* Description: Programmed by the processor. Default time period is set for 1ms. This is set in terms of txbyteclkhs
	*/
    uint32 PllCnt: 16;        /*## attribute PllCnt */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_PllCountRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_DEVICE_READY_INDICATION_REGISTERBits_t
* RegisterName: Device_Ready_Indication_Register
* 
* AddressRange: 0xREAD - 0x070
* ResetValue: 0x00000074
*/
typedef struct  {
   /**
	* BitsName: Device_Ready
	* Description: When ?0? : Indicates that CSI-2 controller is not ready to accept packet information from external sensor When ?1?: Indicates that CSI-2 controller is ready to accept packet information from external sensor.Chrp should be enabled only after this bit goes high.
	*/
    uint32 DeviceReady: 1;        /*## attribute DeviceReady */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2ADAPTCONFIGREG1Bits_t
* RegisterName: Csi2AdaptConfigReg1
* 
* AddressRange: 0xREADWRITE - 0x080
* ResetValue: 0x00000084
*/
typedef struct  {
   /**
	* BitsName: Csi2PacketType
	* Description: Dolphin supports only RAW12 (RAW12 -> 0x2C. So use 0x2C as default value)
	*/
    uint32 Csi2Packettype: 6;        /*## attribute Csi2Packettype */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: Csi2VirtualChannelSelect
	* Description: Indicates the virtual channel for which the packet needs to be transmitted 
	* 00 : Virtual Channel-0 
	* 01 : Virtual Channel-1 
	* 10 : Virtual Channel-2 
	* 11 : Virtual Channel-3
	*/
    uint32 Csi2Virtualchannelselect: 2;        /*## attribute Csi2Virtualchannelselect */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Csi2DphyClkMode
	* Description: When ?0? : Continuous Clock Mode When ?1? : Non Continuous Clock Mode This is configured by the application based on the mode in which MIPI PHY clock lane need to operate
	*/
    uint32 Csi2Dphyclkmode: 1;        /*## attribute Csi2Dphyclkmode */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Csi2LoopBackModeEnable
	* Description: Note Used
	*/
    uint32 Csi2Loopbackmodeenable: 1;        /*## attribute Csi2Loopbackmodeenable */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: Csi2Txulpsesc
	* Description: This signal indicates if the DPHY has to initiates the ULPS sequence. If this is asserted high the CSI-2 Tx will drive ULPS entry enable for D-PHY(Clock and Data Lanes) This is configured by application for driving the D-PHY to ULPS mode
	*/
    uint32 Csi2Txulpsesc: 1;        /*## attribute Csi2Txulpsesc */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Csi2Txulpsexit
	* Description: This signal indicates if the DPHY has to exit out of a ULPS state. If this is asserted high the CSI-2 Tx will drive ULPS exit enable for D-PHY(Clock and Data lanes) This is configured by the application to exit the DPHY from ULPS mode
	*/
    uint32 Csi2Txulpsexit: 1;        /*## attribute Csi2Txulpsexit */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 7;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Bits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2ADAPTCONFIGREG2Bits_t
* RegisterName: Csi2AdaptConfigReg2
* 
* AddressRange: 0xREADWRITE - 0x084
* ResetValue: 0x00000088
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
	* BitsName: Csi2PacketEnable
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the CSI2 interface)
	*/
    uint32 Csi2Packetenable: 1;        /*## attribute Csi2Packetenable */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Csi2DataGrpModeSelect
	* Description: 1= 4 data chunk mode(4 consecutive samples of ADC1,4 consecutive samples of ADC2,4 consecutive samples of ADC3, 4 consecutive samples of ADC4,4 consecutive samples of ADC1 so on)
	* 0= 1 data  mode (1 sample of ADC1,1 sample of ADC2,1 sample of ADC3,1 sample of ADC4,1 sample of ADC1 so on)
	*/
    uint32 Csi2Datagrpmodeselect: 1;        /*## attribute Csi2Datagrpmodeselect */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: Csi2CrcControl
	* Description: Packet footer :This bit enables the 32-bit CRC engine and append the CRC output in the packet footer.32 -bit CRC is send as three seperated 12 bit in the packet.  
	* 1= enable CRC
	* 0= disable CRC
	*/
    uint32 Csi2Crccontrol: 1;        /*## attribute Csi2Crccontrol */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Csi2DphyClkDiv
	* Description: Refrece clock generationor the PLL inside DPHY.Default = 20MHz.Input to the clock divider is 40MHz XTAL clock
	* 
	* ?01? - Divide by 2  (40/2 = 20 MHz)
	* ?10? - Divide by 3 (40/3 = 13.33 MHz)
	* ?11? - Divide by 4 (40/4 = 10 MHz)
	*/
    uint32 Csi2Dphyclkdiv: 2;        /*## attribute Csi2Dphyclkdiv */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
   /**
	* BitsName: Csi2DelayCnt
	* Description: An internal delay generator which delays the incoming  line active,frame_active signals from chirp So that the delay requirement b/w sensor signals FS,LS,LE,FE is met.Counter running at 40 MHz.The delay value varies with the decimation and no of DPHY lanes enabled (csi_clk). Need  feedback from validation to fix the delay for various decimations
	*/
    uint32 Csi2Delaycnt: 12;        /*## attribute Csi2Delaycnt */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Bits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2ADAPTCONFIGREG3Bits_t
* RegisterName: Csi2AdaptConfigReg3
* 
* AddressRange: 0xREADWRITE - 0x088
* ResetValue: 0x0000008C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
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
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 4;        /*## attribute Reserved2 */
   /**
	* BitsName: ChannelDisableDataSel
	* Description: Individual ADC channel can de disabled or enabled.
	* 0 : when adc channel is disabled send zero data 
	* 1: when adc channel is disabled send Test data programmed in Csi2TestModeControlReg
	*/
    uint32 Channeldisabledatasel: 1;        /*## attribute Channeldisabledatasel */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Bits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2_CRC_CTRL1Bits_t
* RegisterName: csi2_crc_ctrl1
* 
* AddressRange: 0xREADWRITE - 0x08C
* ResetValue: 0x00000090
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod02_Csi2CrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2_CRC_CTRL2Bits_t
* RegisterName: csi2_crc_ctrl2
* 
* AddressRange: 0xREADWRITE - 0x090
* ResetValue: 0x00000094
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC output is XOR ed with this value.It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod02_Csi2CrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2_CRC_CTRL3Bits_t
* RegisterName: csi2_crc_ctrl3
* 
* AddressRange: 0xREADWRITE - 0x094
* ResetValue: 0x00000098
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
}Nxp_Tef810x_Mod02_Csi2CrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod02_PDC_CONFIG_REGBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0xREADWRITE - 0x098
* ResetValue: 0x0000009C
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
	* Leave as reset if not needed explicitly.
	*/
    uint32 WaDelayDecimationMode4: 4;        /*## attribute WaDelayDecimationMode4 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 8;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod02_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2_TXN_CTRLBits_t
* RegisterName: csi2_txn_ctrl
* 
* AddressRange: 0xREADWRITE - 0x09C
* ResetValue: 0x000000A0
*/
typedef struct  {
   /**
	* BitsName: csi2_txn_en
	* Description: Transmision enable for Csi2.This should be the last register to be programmed(enabled) during configuration.
	* 0: Transmission is disabled
	* 1: Transmission is enabled
	*/
    uint32 Csi2TxnEn: 1;        /*## attribute Csi2TxnEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod02_Csi2TxnCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_CSI2TESTMODECONTROLREGBits_t
* RegisterName: Csi2TestModeControlReg
* 
* AddressRange: 0xREADWRITE - 0x0A0
* ResetValue: 0x000000A4
*/
typedef struct  {
   /**
	* BitsName: csi2_testmode_test_data
	* Description: Debug Data to be send in Debug Mode
	*/
    uint32 Csi2TestmodeTestData: 12;        /*## attribute Csi2TestmodeTestData */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: csi2_testmode_en
	* Description: 0: PDC functional data asinput to csi2
	* 1: Test data is input to csi2
	*/
    uint32 Csi2TestmodeEn: 1;        /*## attribute Csi2TestmodeEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: csi2_testmode_data_sel
	* Description: 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 Csi2TestmodeDataSel: 2;        /*## attribute Csi2TestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: csi2_testmode_skip_pdc
	* Description: 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 Csi2TestmodeSkipPdc: 1;        /*## attribute Csi2TestmodeSkipPdc */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 7;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod02_Csi2TestmodecontrolregBits_t;
    /**
* Nxp_Tef810x_Mod02_MASTER_IDIV_CTRLBits_t
* RegisterName: master_idiv_ctrl
* 
* AddressRange: 0xREADWRITE - 0x0A4
* ResetValue: 0x000000A8
*/
typedef struct  {
   /**
	* BitsName: master_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for master clk divider when csi2 is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.This reset is not auto clearing.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 MasterIdivRst: 1;        /*## attribute MasterIdivRst */
   /**
	* BitsName: dphy_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for dphy clk divider when csi2 is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.This reset is not auto clearing.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 DphyIdivRst: 1;        /*## attribute DphyIdivRst */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
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
	*/
    uint32 MasterIdivValue: 6;        /*## attribute MasterIdivValue */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: Divider value selection logic 
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the master_idiv_value register.
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
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: dphy_idiv_blk_cnt
	* Description: Clock divider for generating internal DPHY pll reference clock :Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz.
	*/
    uint32 DphyIdivBlkCnt: 6;        /*## attribute DphyIdivBlkCnt */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod02_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_PDC_SHIFT_REG_IDIV_CTRLBits_t
* RegisterName: pdc_shift_reg_idiv_ctrl
* 
* AddressRange: 0xREADWRITE - 0x0AC
* ResetValue: 0x000000B0
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
}Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_REF_CNTR_INITBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0xREADWRITE - 0x0BC
* ResetValue: 0x000000C0
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
}Nxp_Tef810x_Mod02_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod02_FREQ_COUNTER_STARTBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0xREADWRITE - 0x0C0
* ResetValue: 0x000000C4
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
}Nxp_Tef810x_Mod02_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod02_FREQ_COUNTER_READ_VALUEBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0xREAD - 0x0C4
* ResetValue: 0x000000C8
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
}Nxp_Tef810x_Mod02_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod02_REF_COUNTER_READ_VALUEBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0xREAD - 0x0C8
* ResetValue: 0x000000CC
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
}Nxp_Tef810x_Mod02_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod02_ATB_SET_TRIMBits_t
* RegisterName: atb_set_trim
* 
* AddressRange: 0xREADWRITE - 0x0D8
* ResetValue: 0x000000DC
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
}Nxp_Tef810x_Mod02_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod02_MODULEIDBits_t
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
	* Description: Identifier value. This is the unique identifier of the module. In case of csi2 it is 0x02.
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod02_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod02_Trimreg0Bits_t
* RegisterName: TrimReg0
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x0A040218
*/
typedef struct  {
   /**
	* BitsName: hs_tx_fixed_delay_enable
	* Description: Fix delay enable control for Tx.
	*/
    uint32 HsTxFixedDelayEnable: 1;        /*## attribute HsTxFixedDelayEnable */
   /**
	* BitsName: hs_rx_fixed_delay_enable
	* Description: Fix delay enable control for Rx
	*/
    uint32 HsRxFixedDelayEnable: 1;        /*## attribute HsRxFixedDelayEnable */
   /**
	* BitsName: ext_low_vco_en
	* Description: External trim bit control to enable
	* the low vco
	*/
    uint32 ExtLowVcoEn: 1;        /*## attribute ExtLowVcoEn */
   /**
	* BitsName: ext_high_vco_en
	* Description: External trim bit control to enable
	* the high vco
	*/
    uint32 ExtHighVcoEn: 1;        /*## attribute ExtHighVcoEn */
   /**
	* BitsName: trim_ff_bypass
	* Description: trim to bypass flip-flop for LPTX
	* in clock lane and data lanes 1,2
	* and 3
	*/
    uint32 TrimFfBypass: 1;        /*## attribute TrimFfBypass */
   /**
	* BitsName: trim_imp
	* Description: Tx Impedance Control
	*/
    uint32 TrimImp: 2;        /*## attribute TrimImp */
   /**
	* BitsName: ddr_delay_sel
	* Description: DDR delay trim control
	* Leave as reset if not needed explicitly.
	*/
    uint32 DdrDelaySel: 2;        /*## attribute DdrDelaySel */
   /**
	* BitsName: latch_inv_delay_ctrl
	* Description: trim delay in latch block
	*/
    uint32 LatchInvDelayCtrl: 3;        /*## attribute LatchInvDelayCtrl */
   /**
	* BitsName: vco_selection
	* Description: Vco selection control
	*/
    uint32 VcoSelection: 1;        /*## attribute VcoSelection */
   /**
	* BitsName: pulser_bypass
	* Description: trim control for pulse rejection
	* bypass
	*/
    uint32 PulserBypass: 1;        /*## attribute PulserBypass */
   /**
	* BitsName: iref_20u_cp_trim
	* Description: glitch removal ckt current trim
	*/
    uint32 Iref20UCpTrim: 2;        /*## attribute Iref20UCpTrim */
   /**
	* BitsName: trim_bit_glitch
	* Description: input selection trimbit(Comp_out
	* or vdd)
	*/
    uint32 TrimBitGlitch: 1;        /*## attribute TrimBitGlitch */
   /**
	* BitsName: DC_test_data
	* Description: Test data for DC in LP and Hsmode
	*/
    uint32 DcTestData: 1;        /*## attribute DcTestData */
   /**
	* BitsName: LP_DC_test_en
	* Description: LP enable trim for testing DC
	* characteristics of the LP driver
	*/
    uint32 LpDcTestEn: 1;        /*## attribute LpDcTestEn */
   /**
	* BitsName: HS_DC_test_en
	* Description: HS enable trim for testing DC
	* characteristics of the HS driver
	*/
    uint32 HsDcTestEn: 1;        /*## attribute HsDcTestEn */
   /**
	* BitsName: cdpd
	* Description: Contention detection power
	* down
	*/
    uint32 Cdpd: 1;        /*## attribute Cdpd */
   /**
	* BitsName: capen_pwl
	* Description: trim capacitor for pulse-rejection
	*/
    uint32 CapenPwl: 2;        /*## attribute CapenPwl */
   /**
	* BitsName: rxhsdpol
	* Description: Change polarity of high speed
	* receive data
	*/
    uint32 Rxhsdpol: 1;        /*## attribute Rxhsdpol */
   /**
	* BitsName: rxcksel
	* Description: trim delay control for receiver
	* data lane 0
	*/
    uint32 Rxcksel: 1;        /*## attribute Rxcksel */
   /**
	* BitsName: gnctrl
	* Description: trim gain for front-end amplifier
	*/
    uint32 Gnctrl: 2;        /*## attribute Gnctrl */
   /**
	* BitsName: gdefault
	* Description: trim gain for front-end amplifier
	*/
    uint32 Gdefault: 1;        /*## attribute Gdefault */
   /**
	* BitsName: tr_sel
	* Description: Rise time and fall time trimming
	* for predriver
	*/
    uint32 TrSel: 2;        /*## attribute TrSel */
   /**
	* BitsName: lptx_trim_slew
	* Description: trim control for lp slew rate
	*/
    uint32 LptxTrimSlew: 2;        /*## attribute LptxTrimSlew */
}Nxp_Tef810x_Mod02_Trimreg0Bits_t;
    /**
* Nxp_Tef810x_Mod02_Trimreg1Bits_t
* RegisterName: TrimReg1
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x4DB1100F
*/
typedef struct  {
   /**
	* BitsName: rtermctrl
	* Description: termination resistance control
	*/
    uint32 Rtermctrl: 2;        /*## attribute Rtermctrl */
   /**
	* BitsName: trim_hstx_ldo_pd
	* Description: power down register to control
	* the hstx ldo
	*/
    uint32 TrimHstxLdoPd: 1;        /*## attribute TrimHstxLdoPd */
   /**
	* BitsName: cdlow_trim
	* Description: trim control for CD low resistor
	* control
	*/
    uint32 CdlowTrim: 3;        /*## attribute CdlowTrim */
   /**
	* BitsName: cdhigh_trim
	* Description: trim control for CD high resistor
	* control
	*/
    uint32 CdhighTrim: 3;        /*## attribute CdhighTrim */
   /**
	* BitsName: tstodby4
	* Description: PLL Test output selection (div4/
	* div8)
	*/
    uint32 Tstodby4: 1;        /*## attribute Tstodby4 */
   /**
	* BitsName: Plltstcksel
	* Description: PLL Test clock selection control
	*/
    uint32 Plltstcksel: 2;        /*## attribute Plltstcksel */
   /**
	* BitsName: res
	* Description: LPF Resistor tunability
	*/
    uint32 Res: 3;        /*## attribute Res */
   /**
	* BitsName: bwb
	* Description: Chargepump current tunability
	*/
    uint32 Bwb: 3;        /*## attribute Bwb */
   /**
	* BitsName: pll_lock_trim
	* Description: External trim bit control to enable
	* pll lock
	*/
    uint32 PllLockTrim: 1;        /*## attribute PllLockTrim */
   /**
	* BitsName: spare_bits
	* Description: spare_bits
	*/
    uint32 SpareBits: 1;        /*## attribute SpareBits */
   /**
	* BitsName: refin_sel
	* Description: Reference clock signal control
	*/
    uint32 RefinSel: 3;        /*## attribute RefinSel */
   /**
	* BitsName: dlpf_reg_sel
	* Description: Discharge lpf register bit select
	*/
    uint32 DlpfRegSel: 1;        /*## attribute DlpfRegSel */
   /**
	* BitsName: dlpf
	* Description: Discharge lpf capacitor to zero
	*/
    uint32 Dlpf: 1;        /*## attribute Dlpf */
   /**
	* BitsName: cntb
	* Description: Dphy PLL divider value.Combination of cnta and cntb determines the PLL o/p frequency.
	* Need to be changed for different decimation factors and different no of lanes .Divider ratio Counter B
	*/
    uint32 Cntb: 1;        /*## attribute Cntb */
   /**
	* BitsName: cnta
	* Description: Divider ratio Counter A
	*/
    uint32 Cnta: 6;        /*## attribute Cnta */
}Nxp_Tef810x_Mod02_Trimreg1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Trimreg2Bits_t
* RegisterName: TrimReg2
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x10000000
*/
typedef struct  {
   /**
	* BitsName: rxlpen_reg_d1
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD1: 1;        /*## attribute RxlpenRegD1 */
   /**
	* BitsName: rxlpen_reg_d0
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD0: 1;        /*## attribute RxlpenRegD0 */
   /**
	* BitsName: rxlpen_reg_ck
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegCk: 1;        /*## attribute RxlpenRegCk */
   /**
	* BitsName: reg_ctrl_hsrx_en
	* Description: Register control enable for lane
	* HSRX enables
	*/
    uint32 RegCtrlHsrxEn: 1;        /*## attribute RegCtrlHsrxEn */
   /**
	* BitsName: rxhsen_reg_d3_d0
	* Description: Enable register control for HSRX
	*/
    uint32 RxhsenRegD3D0: 4;        /*## attribute RxhsenRegD3D0 */
   /**
	* BitsName: rxhsen_reg_ck
	* Description: Enable register control for HSRX
	* clk
	*/
    uint32 RxhsenRegCk: 1;        /*## attribute RxhsenRegCk */
   /**
	* BitsName: reg_ctrl_tx_pd
	* Description: Register control enable for tx
	* lane power down
	*/
    uint32 RegCtrlTxPd: 1;        /*## attribute RegCtrlTxPd */
   /**
	* BitsName: txpd_reg_d3_d0
	* Description: Power down bit for Txlane
	*/
    uint32 TxpdRegD3D0: 4;        /*## attribute TxpdRegD3D0 */
   /**
	* BitsName: txpd_reg_ck
	* Description: Power down bit for Txlane of Clk Lane
	*/
    uint32 TxpdRegCk: 1;        /*## attribute TxpdRegCk */
   /**
	* BitsName: reg_ctrl_lptx_en
	* Description: Register control enable for lane
	* lptx enables
	*/
    uint32 RegCtrlLptxEn: 1;        /*## attribute RegCtrlLptxEn */
   /**
	* BitsName: txlpen_reg_d3_d0
	* Description: 1 in lp mode and 0 in hs mode data lane
	*/
    uint32 TxlpenRegD3D0: 4;        /*## attribute TxlpenRegD3D0 */
   /**
	* BitsName: txlpen_reg_ck
	* Description: 1 in lp mode and 0 in hs  clock lane
	*/
    uint32 TxlpenRegCk: 1;        /*## attribute TxlpenRegCk */
   /**
	* BitsName: reg_ctrl_hstx_en
	* Description: Register control enable for lane
	* HSTX enables
	*/
    uint32 RegCtrlHstxEn: 1;        /*## attribute RegCtrlHstxEn */
   /**
	* BitsName: txhsen_reg_d3_d0
	* Description: Enable register control for HSTX data line
	*/
    uint32 TxhsenRegD3D0: 4;        /*## attribute TxhsenRegD3D0 */
   /**
	* BitsName: txhsen_reg_ck
	* Description: Enable register control for HSTX clk
	*/
    uint32 TxhsenRegCk: 1;        /*## attribute TxhsenRegCk */
   /**
	* BitsName: pllrst_reg
	* Description: Pll reset
	*/
    uint32 PllrstReg: 1;        /*## attribute PllrstReg */
   /**
	* BitsName: pllpden
	* Description: Register control enable for pll
	* power down
	*/
    uint32 Pllpden: 1;        /*## attribute Pllpden */
   /**
	* BitsName: pllpd_reg
	* Description: Power down for pll
	*/
    uint32 PllpdReg: 1;        /*## attribute PllpdReg */
   /**
	* BitsName: rstn_reg
	* Description: Reset input through register
	*/
    uint32 RstnReg: 1;        /*## attribute RstnReg */
   /**
	* BitsName: rstn_reg_en
	* Description: Enable Reset input through register
	*/
    uint32 RstnRegEn: 1;        /*## attribute RstnRegEn */
}Nxp_Tef810x_Mod02_Trimreg2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Trimreg3Bits_t
* RegisterName: TrimReg3
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x0020C1FC
*/
typedef struct  {
   /**
	* BitsName: vbg_sel
	* Description: Bandgap selection control
	*/
    uint32 VbgSel: 1;        /*## attribute VbgSel */
   /**
	* BitsName: clk_pol_sel_d3_d0
	* Description: trim control for clock polarity
	* selection of data lane
	*/
    uint32 ClkPolSelD3D0: 4;        /*## attribute ClkPolSelD3D0 */
   /**
	* BitsName: clk_pol_sel_ck
	* Description: trim control for clock polarity
	* selection of clk
	*/
    uint32 ClkPolSelCk: 1;        /*## attribute ClkPolSelCk */
   /**
	* BitsName: bist_lane_trim_3_0
	* Description: Enable Bandgap offset cancellation
	* circuit
	*/
    uint32 BistLaneTrim30: 4;        /*## attribute BistLaneTrim30 */
   /**
	* BitsName: trim_s3_s0
	* Description: Common mode voltage control
	* for TX
	*/
    uint32 TrimS3S0: 4;        /*## attribute TrimS3S0 */
   /**
	* BitsName: BW_res_sel
	* Description: PLL BW resistor selection control
	*/
    uint32 BwResSel: 1;        /*## attribute BwResSel */
   /**
	* BitsName: V2Ipd_BGPD
	* Description: Power down selection for BG,
	* bias(v2i)
	*/
    uint32 V2IpdBgpd: 1;        /*## attribute V2IpdBgpd */
   /**
	* BitsName: trim_ff_bypass
	* Description: trim to bypass flip-flop for LPTX
	* in data lanes 0
	*/
    uint32 TrimFfBypass: 1;        /*## attribute TrimFfBypass */
   /**
	* BitsName: rterm_reg_en
	* Description: Register control enable for termination
	*/
    uint32 RtermRegEn: 1;        /*## attribute RtermRegEn */
   /**
	* BitsName: rtermen_reg_d3_d0
	* Description: Register control for termination
	* enable data
	*/
    uint32 RtermenRegD3D0: 4;        /*## attribute RtermenRegD3D0 */
   /**
	* BitsName: rtermen_reg_ck
	* Description: Register control for termination
	* enable clk
	*/
    uint32 RtermenRegCk: 1;        /*## attribute RtermenRegCk */
   /**
	* BitsName: reg_ctrl_rx_pd
	* Description: Register control enable for rx
	* lane power down
	*/
    uint32 RegCtrlRxPd: 1;        /*## attribute RegCtrlRxPd */
   /**
	* BitsName: rxpd_reg_d3_d0
	* Description: Power down bit for data Rxlane
	*/
    uint32 RxpdRegD3D0: 4;        /*## attribute RxpdRegD3D0 */
   /**
	* BitsName: rxpd_reg_ck
	* Description: Power down bit for Rxlane of Clk Lane
	*/
    uint32 RxpdRegCk: 1;        /*## attribute RxpdRegCk */
   /**
	* BitsName: reg_ctrl_lprx_en
	* Description: Register control enable for lane
	* lprx enables
	*/
    uint32 RegCtrlLprxEn: 1;        /*## attribute RegCtrlLprxEn */
   /**
	* BitsName: rxlpen_reg_d3_d2
	* Description: 1 in lp mode and 0 in hs mode
	*/
    uint32 RxlpenRegD3D2: 2;        /*## attribute RxlpenRegD3D2 */
}Nxp_Tef810x_Mod02_Trimreg3Bits_t;
    /**
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Bits_t
* RegisterName: DPHY_DFE_DLN_Register_0
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x0A0D0716
*/
typedef struct  {
   /**
	* BitsName: DFE_DLN_HS_TRIAL
	* Description: This parameter specifies the number of byte clock cycles the data lane shall wait to complete the HS TRIAL time
	*/
    uint32 DfeDlnHsTrial: 8;        /*## attribute DfeDlnHsTrial */
   /**
	* BitsName: DFE_DLN_HS_EXIT
	* Description: This parameter specifies the number of byte clock cycles the data lane shall wait to complete the HS-EXIT time
	*/
    uint32 DfeDlnHsExit: 8;        /*## attribute DfeDlnHsExit */
   /**
	* BitsName: DFE_DLN_HS_PREPARE
	* Description: This parameter specifies the number of clock cycles the data lane shall wait to complete the HS PREPARE time
	* [13:8]   -> In Byte Clock Cycles 
	* [15:14] -> In DDR Clock Cyles s
	*/
    uint32 DfeDlnHsPrepare: 8;        /*## attribute DfeDlnHsPrepare */
   /**
	* BitsName: DFE_DLN_HS_ZERO_CNT
	* Description: This parameter specifies the number of byte clocks cycles the data lane shall wait to complete the HS-ZERO time
	*/
    uint32 DfeDlnHsZeroCnt: 8;        /*## attribute DfeDlnHsZeroCnt */
}Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Bits_t;
    /**
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Bits_t
* RegisterName: DPHY_DFE_DLN_Register_1
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00061E07
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: DFE_DLN_LPX_HS_CNT
	* Description: This parameter specifies the number of byte clock cycles required to accommodate an LP- xx state on the data lane
	*/
    uint32 DfeDlnLpxHsCnt: 8;        /*## attribute DfeDlnLpxHsCnt */
   /**
	* BitsName: DFE_DLN_SYNC_CNT
	* Description: This parameter specifies the number of byte clock cycles the
	* data lane shall wait before announcing an error on the
	* timeout of the SYNC pattern
	*/
    uint32 DfeDlnSyncCnt: 8;        /*## attribute DfeDlnSyncCnt */
   /**
	* BitsName: DFE_DLN_RX_CNT
	* Description: This parameter specifies the number of byte clocks cycles the data lane shall wait before enabling the HS receiver
	*/
    uint32 DfeDlnRxCnt: 8;        /*## attribute DfeDlnRxCnt */
}Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_DphyDfeClnRegister0Bits_t
* RegisterName: DPHY_DFE_CLN_Register_0
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x080D0521
*/
typedef struct  {
   /**
	* BitsName: DFE_CLN_HS_TRIAL
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait during the TRIAL sequence of the high speed clock transmission
	*/
    uint32 DfeClnHsTrial: 8;        /*## attribute DfeClnHsTrial */
   /**
	* BitsName: DFE_CLN_HS_EXIT
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait during the exit sequence of the high speed clock transmission
	*/
    uint32 DfeClnHsExit: 8;        /*## attribute DfeClnHsExit */
   /**
	* BitsName: DFE_CLN_PREPARE
	* Description: This parameter specifies the number of  clock cycles the clock lane transmitter module shall wait during the prepare sequence of the high speed clock transmission
	* [13:8]   -> In Byte Clock Cycles 
	* [15:14] -> In DDR Clock Cyles s
	*/
    uint32 DfeClnPrepare: 8;        /*## attribute DfeClnPrepare */
   /**
	* BitsName: DFE_CLN_ZERO
	* Description: This parameter specifies the number of byte clocks cycles the clock lane transmitter module shall wait during the HS-ZERO sequence of the high speed clock transmission
	*/
    uint32 DfeClnZero: 8;        /*## attribute DfeClnZero */
}Nxp_Tef810x_Mod02_DphyDfeClnRegister0Bits_t;
    /**
* Nxp_Tef810x_Mod02_DphyDfeClnRegister1Bits_t
* RegisterName: DPHY_DFE_CLN_Register_1
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000006
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: TCLK_POST
	* Description: This parameter specifies the number of byte clock cycles the clock lane transmitter module shall wait before removing the clock lane request after the last associated data lane has transitioned to LP mode
	*/
    uint32 TclkPost: 8;        /*## attribute TclkPost */
   /**
	* BitsName: TCLK_PRE
	* Description: This parameter specifies that the HS clock shall be driven by the transmitter prior to any associated data lane beginning the transition from LP to HS mode. The parameter is in terms of number of TxByteClkHS
	*/
    uint32 TclkPre: 8;        /*## attribute TclkPre */
   /**
	* BitsName: DFE_CLN_LPX_HS_CNT
	* Description: This parameter specifies the number of byte clocks required to accommodate an LP-xx stat on the clock lane
	*/
    uint32 DfeClnLpxHsCnt: 8;        /*## attribute DfeClnLpxHsCnt */
}Nxp_Tef810x_Mod02_DphyDfeClnRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterBits_t
* RegisterName: PPI_Data_Lane_Swap_Register
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x00000300
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: Number_of_Lanes
	* Description: Default: - 4-Lanes. Set by the processor to configure the number of PPI lanes 
	* When ?00? : One Lane Enabled (Lane-0) 
	* When ?01? : Two Lane Enabled (Lane-0,1) 
	* When ?10? : Three Lane Enabled( Lane-0,1,2) 
	* When ?11? : Four Lane Enabled( Lane-0,1,2,3)
	*/
    uint32 NumberOfLanes: 2;        /*## attribute NumberOfLanes */
   /**
	* BitsName: SWAP_LANE3
	* Description: Set by the processor to enable the Lane-3 swapping. When enable the LANE3 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane3 : Lane3 
	* When ?01? : Swap : Lane3 : Lane0 
	* When ?10 : Swap : Lane3 : Lane1
	*  When ?11 : Swap : Lane3 : Lane2
	*/
    uint32 SwapLane3: 2;        /*## attribute SwapLane3 */
   /**
	* BitsName: SWAP_LANE2
	* Description: Set by the processor to enable the Lane-2 swapping. When enable the LANE2 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane2 : Lane2
	*  When ?01? : Swap : Lane2 : Lane0 
	* When ?10 : Swap : Lane2 : Lane1 
	* When ?11 : Swap : Lane2 : Lane3
	*/
    uint32 SwapLane2: 2;        /*## attribute SwapLane2 */
   /**
	* BitsName: SWAP_LANE1
	* Description: Set by the processor to enable the Lane-1 swapping. When enable the LANE1 PPI interface signal of Controller is driven on to respective Lane on the DPHY
	*  When ?00? : No Swap : Lane1 : Lane1 
	* When ?01? : Swap : Lane1 : Lane0 
	* When ?10 : Swap : Lane1 : Lane2 
	* When ?11 : Swap : Lane1 : Lane3
	*/
    uint32 SwapLane1: 2;        /*## attribute SwapLane1 */
   /**
	* BitsName: SWAP_LANE0
	* Description: Set by the processor to enable the Lane-0 swapping. When enable the LANE0 PPI interface signal of Controller is driven on to respective Lane on the DPHY 
	* When ?00? : No Swap : Lane0 : Lane0
	*  When ?01? : Swap : Lane0 : Lane1
	*  When ?10 : Swap : Lane0 : Lane2 
	* When ?11 : Swap : Lane0 : Lane3
	*/
    uint32 SwapLane0: 2;        /*## attribute SwapLane0 */
}Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_FifoStatusRegisterBits_t
* RegisterName: FIFO_status_Register
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: CSI_FIFO_FULL
	* Description: Indicates the CSI FIFO threshold full status
	*/
    uint32 CsiFifoFull: 1;        /*## attribute CsiFifoFull */
   /**
	* BitsName: CSI_FIFO_EMPTY
	* Description: Indicates the CSI FIFO empty status
	*/
    uint32 CsiFifoEmpty: 1;        /*## attribute CsiFifoEmpty */
   /**
	* BitsName: SENSOR_FIFO_FULL
	* Description: Indicates the SENSOR FIFO full status
	*/
    uint32 SensorFifoFull: 1;        /*## attribute SensorFifoFull */
   /**
	* BitsName: SENSOR_FIFO_ALMOST_FULL
	* Description: Indicates the SENSOR FIFO threshold full status
	*/
    uint32 SensorFifoAlmostFull: 1;        /*## attribute SensorFifoAlmostFull */
   /**
	* BitsName: SENSOR_FIFO_EMPTY
	* Description: Indicates the SENSOR FIFO empty status
	*/
    uint32 SensorFifoEmpty: 1;        /*## attribute SensorFifoEmpty */
}Nxp_Tef810x_Mod02_FifoStatusRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterBits_t
* RegisterName: USD_Pixel_Mode_Control_Register
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: USD_DATA_TYPE8_EN
	* Description: Set by the processor to configure the USD data_type8 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType8En: 2;        /*## attribute UsdDataType8En */
   /**
	* BitsName: USD_DATA_TYPE7_EN
	* Description: Set by the processor to configure the USD data_type7 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType7En: 2;        /*## attribute UsdDataType7En */
   /**
	* BitsName: USD_DATA_TYPE6_EN
	* Description: Set by the processor to configure the USD data_type6 one/two/three/four pixel mode
	*  ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType6En: 2;        /*## attribute UsdDataType6En */
   /**
	* BitsName: USD_DATA_TYPE5_EN
	* Description: Set by the processor to configure the USD data_type5 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured
	*  ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType5En: 2;        /*## attribute UsdDataType5En */
   /**
	* BitsName: USD_DATA_TYPE4_EN
	* Description: Set by the processor to configure the USD data_type4 one/two/three/four pixel mode 
	* ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11?: Four pixel mode configured
	*/
    uint32 UsdDataType4En: 2;        /*## attribute UsdDataType4En */
   /**
	* BitsName: USD_DATA_TYPE3_EN
	* Description: Set by the processor to configure the USD data_type3 one/two/three/four pixel mode 
	* ?00? :One pixel mode configured 
	* ?01? :Two pixel mode configured
	*  ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType3En: 2;        /*## attribute UsdDataType3En */
   /**
	* BitsName: USD_DATA_TYPE2_EN
	* Description: Set by the processor to configure the USD data_type2 one/two/three/four pixel mode ?00? : One pixel mode configured ?01? : Two pixel mode configured ?10? : Three pixel mode configured ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType2En: 2;        /*## attribute UsdDataType2En */
   /**
	* BitsName: USD_DATA_TYPE1_EN
	* Description: Set by the processor to configure the USD data_type1 one/two/three/four pixel mode
	*  ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : Four pixel mode configured
	*/
    uint32 UsdDataType1En: 2;        /*## attribute UsdDataType1En */
}Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterBits_t
* RegisterName: YUV_Pixel_Mode_Control_Register
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: YUV422_8BIT_EN
	* Description: Set by the processor to configure the YUV422 8-bit one/two pixel mode ?00? : One pixel mode configured ?01? : Two pixel mode configured ?10? : NA ?11? : NA
	*/
    uint32 Yuv4228BitEn: 2;        /*## attribute Yuv4228BitEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 20;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_RawPixelModeControlRegisterBits_t
* RegisterName: RAW_Pixel_Mode_Control_Register
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 20;        /*## attribute Reserved0 */
   /**
	* BitsName: RAW14_EN
	* Description: Set by the processor to configure RAW14 one/two pixel mode ?00? : One pixel mode configured
	*  ?01? : Two pixel mode configured 
	* ?10? : NA
	*  ?11? : NA
	*/
    uint32 Raw14En: 2;        /*## attribute Raw14En */
   /**
	* BitsName: RAW12_EN
	* Description: Set by the processor to configure RAW12 one/two pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : NA 
	* ?11? : NA
	*/
    uint32 Raw12En: 2;        /*## attribute Raw12En */
   /**
	* BitsName: RAW10_EN
	* Description: Set by the processor to configure RAW10 one/two/three pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured 
	* ?11? : NA
	*/
    uint32 Raw10En: 2;        /*## attribute Raw10En */
   /**
	* BitsName: RAW8_EN
	* Description: Set by the processor to configure RAW8 one/two/three/four pixel mode ?00? : One pixel mode configured 
	* ?01? : Two pixel mode configured 
	* ?10? : Three pixel mode configured
	*  ?11? : Four pixel mode configured
	*/
    uint32 Raw8En: 2;        /*## attribute Raw8En */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod02_RawPixelModeControlRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_PhyTinitCountRegisterBits_t
* RegisterName: PHY_TINIT_Count_Register
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x0000FFFF
*/
typedef struct  {
   /**
	* BitsName: TINIT_TIMER
	* Description: This parameter specifies the number of txbyte clocks cycles the CSI-2 controller should wait to start accepting the data from the sensor interface.
	*/
    uint32 TinitTimer: 32;        /*## attribute TinitTimer */
}Nxp_Tef810x_Mod02_PhyTinitCountRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Bits_t
* RegisterName: VC0_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction1
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction1: 32;        /*## attribute CpmpressionPrediction1 */
}Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Bits_t
* RegisterName: VC0_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction2
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction2: 32;        /*## attribute CpmpressionPrediction2 */
}Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Bits_t
* RegisterName: VC1_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction3
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction3: 32;        /*## attribute CpmpressionPrediction3 */
}Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Bits_t
* RegisterName: VC1_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction4
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction4: 32;        /*## attribute CpmpressionPrediction4 */
}Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Bits_t
* RegisterName: VC2_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction5
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction5: 32;        /*## attribute CpmpressionPrediction5 */
}Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Bits_t
* RegisterName: VC2_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction6
	* Description: Since Dolphin does not support any Prediction or Compression write ZERO
	*/
    uint32 CpmpressionPrediction6: 32;        /*## attribute CpmpressionPrediction6 */
}Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Bits_t
* RegisterName: VC3_compression_Prediction_Scheme_Register_1
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction7
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction7: 32;        /*## attribute CpmpressionPrediction7 */
}Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Bits_t
* RegisterName: VC3_compression_Prediction_Scheme_Register_2
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Cpmpression_Prediction8
	* Description: Since Dolphin does not support any Prediction or Compression keep defualt value
	*/
    uint32 CpmpressionPrediction8: 32;        /*## attribute CpmpressionPrediction8 */
}Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Bits_t;
    /**
* Nxp_Tef810x_Mod02_PllCountRegisterBits_t
* RegisterName: PLL_Count_Register
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x00004E20
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: PLL_CNT
	* Description: Programmed by the processor. Default time period is set for 1ms. This is set in terms of txbyteclkhs
	*/
    uint32 PllCnt: 16;        /*## attribute PllCnt */
}Nxp_Tef810x_Mod02_PllCountRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterBits_t
* RegisterName: Device_Ready_Indication_Register
* 
* AddressRange: 0x070 - 0x074
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: Device_Ready
	* Description: When ?0? : Indicates that CSI-2 controller is not ready to accept packet information from external sensor When ?1?: Indicates that CSI-2 controller is ready to accept packet information from external sensor.Chrp should be enabled only after this bit goes high.
	*/
    uint32 DeviceReady: 1;        /*## attribute DeviceReady */
}Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterBits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Bits_t
* RegisterName: Csi2AdaptConfigReg1
* 
* AddressRange: 0x080 - 0x084
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: Csi2Txulpsexit
	* Description: This signal indicates if the DPHY has to exit out of a ULPS state. If this is asserted high the CSI-2 Tx will drive ULPS exit enable for D-PHY(Clock and Data lanes) This is configured by the application to exit the DPHY from ULPS mode
	*/
    uint32 Csi2Txulpsexit: 1;        /*## attribute Csi2Txulpsexit */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Csi2Txulpsesc
	* Description: This signal indicates if the DPHY has to initiates the ULPS sequence. If this is asserted high the CSI-2 Tx will drive ULPS entry enable for D-PHY(Clock and Data Lanes) This is configured by application for driving the D-PHY to ULPS mode
	*/
    uint32 Csi2Txulpsesc: 1;        /*## attribute Csi2Txulpsesc */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Csi2LoopBackModeEnable
	* Description: Note Used
	*/
    uint32 Csi2Loopbackmodeenable: 1;        /*## attribute Csi2Loopbackmodeenable */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: Csi2DphyClkMode
	* Description: When ?0? : Continuous Clock Mode When ?1? : Non Continuous Clock Mode This is configured by the application based on the mode in which MIPI PHY clock lane need to operate
	*/
    uint32 Csi2Dphyclkmode: 1;        /*## attribute Csi2Dphyclkmode */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: Csi2VirtualChannelSelect
	* Description: Indicates the virtual channel for which the packet needs to be transmitted 
	* 00 : Virtual Channel-0 
	* 01 : Virtual Channel-1 
	* 10 : Virtual Channel-2 
	* 11 : Virtual Channel-3
	*/
    uint32 Csi2Virtualchannelselect: 2;        /*## attribute Csi2Virtualchannelselect */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
   /**
	* BitsName: Csi2PacketType
	* Description: Dolphin supports only RAW12 (RAW12 -> 0x2C. So use 0x2C as default value)
	*/
    uint32 Csi2Packettype: 6;        /*## attribute Csi2Packettype */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Bits_t
* RegisterName: Csi2AdaptConfigReg2
* 
* AddressRange: 0x084 - 0x088
* ResetValue: 0x0C810000
*/
typedef struct  {
   /**
	* BitsName: Csi2DelayCnt
	* Description: An internal delay generator which delays the incoming  line active,frame_active signals from chirp So that the delay requirement b/w sensor signals FS,LS,LE,FE is met.Counter running at 40 MHz.The delay value varies with the decimation and no of DPHY lanes enabled (csi_clk). Need  feedback from validation to fix the delay for various decimations
	*/
    uint32 Csi2Delaycnt: 12;        /*## attribute Csi2Delaycnt */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: Csi2DphyClkDiv
	* Description: Refrece clock generationor the PLL inside DPHY.Default = 20MHz.Input to the clock divider is 40MHz XTAL clock
	* 
	* ?01? - Divide by 2  (40/2 = 20 MHz)
	* ?10? - Divide by 3 (40/3 = 13.33 MHz)
	* ?11? - Divide by 4 (40/4 = 10 MHz)
	*/
    uint32 Csi2Dphyclkdiv: 2;        /*## attribute Csi2Dphyclkdiv */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Csi2CrcControl
	* Description: Packet footer :This bit enables the 32-bit CRC engine and append the CRC output in the packet footer.32 -bit CRC is send as three seperated 12 bit in the packet.  
	* 1= enable CRC
	* 0= disable CRC
	*/
    uint32 Csi2Crccontrol: 1;        /*## attribute Csi2Crccontrol */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Csi2DataGrpModeSelect
	* Description: 1= 4 data chunk mode(4 consecutive samples of ADC1,4 consecutive samples of ADC2,4 consecutive samples of ADC3, 4 consecutive samples of ADC4,4 consecutive samples of ADC1 so on)
	* 0= 1 data  mode (1 sample of ADC1,1 sample of ADC2,1 sample of ADC3,1 sample of ADC4,1 sample of ADC1 so on)
	*/
    uint32 Csi2Datagrpmodeselect: 1;        /*## attribute Csi2Datagrpmodeselect */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: Csi2PacketEnable
	* Description: Packet Header Enable :
	* 0: no Packet Header on transmitted data Packet.
	* 1: Packet Header is appended to the  Data Packet.
	* Note:Packet header contains Chirp No and Sample Count(no of ADC samples sent over the CSI2 interface)
	*/
    uint32 Csi2Packetenable: 1;        /*## attribute Csi2Packetenable */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Bits_t
* RegisterName: Csi2AdaptConfigReg3
* 
* AddressRange: 0x088 - 0x08C
* ResetValue: 0x00000001
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: packet_endianness
	* Description: 0: Sends MS first in Packet Header and Packet Footer(crc)
	* 1: Send LS first in Packet Header and Packet Footer(crc)
	* Note: This is only applicable to Packet Header and Packet Footer not for Data
	* 
	* Note: CRC is 32 bit and WordCunt is 14 bit so this needs to be splitted into MS and LS formats.
	*/
    uint32 PacketEndianness: 1;        /*## attribute PacketEndianness */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ChannelDisableDataSel
	* Description: Individual ADC channel can de disabled or enabled.
	* 0 : when adc channel is disabled send zero data 
	* 1: when adc channel is disabled send Test data programmed in Csi2TestModeControlReg
	*/
    uint32 Channeldisabledatasel: 1;        /*## attribute Channeldisabledatasel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 4;        /*## attribute Reserved2 */
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
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 12;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Bits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl1Bits_t
* RegisterName: csi2_crc_ctrl1
* 
* AddressRange: 0x08C - 0x090
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_init_value
	* Description: Initial value of the CRC polynomial register register..It is a CRC Engine configuration parameter
	*/
    uint32 CrcInitValue: 32;        /*## attribute CrcInitValue */
}Nxp_Tef810x_Mod02_Csi2CrcCtrl1Bits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl2Bits_t
* RegisterName: csi2_crc_ctrl2
* 
* AddressRange: 0x090 - 0x094
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: crc_xor_out_value
	* Description: Final CRC output is XOR ed with this value.It is a CRC Engine configuration parameter
	*/
    uint32 CrcXorOutValue: 32;        /*## attribute CrcXorOutValue */
}Nxp_Tef810x_Mod02_Csi2CrcCtrl2Bits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl3Bits_t
* RegisterName: csi2_crc_ctrl3
* 
* AddressRange: 0x094 - 0x098
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
}Nxp_Tef810x_Mod02_Csi2CrcCtrl3Bits_t;
    /**
* Nxp_Tef810x_Mod02_PdcConfigRegBits_t
* RegisterName: pdc_config_reg
* 
* AddressRange: 0x098 - 0x09C
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
	* Leave as reset if not needed explicitly.
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
}Nxp_Tef810x_Mod02_PdcConfigRegBits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2TxnCtrlBits_t
* RegisterName: csi2_txn_ctrl
* 
* AddressRange: 0x09C - 0x0A0
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 31;        /*## attribute Reserved0 */
   /**
	* BitsName: csi2_txn_en
	* Description: Transmision enable for Csi2.This should be the last register to be programmed(enabled) during configuration.
	* 0: Transmission is disabled
	* 1: Transmission is enabled
	*/
    uint32 Csi2TxnEn: 1;        /*## attribute Csi2TxnEn */
}Nxp_Tef810x_Mod02_Csi2TxnCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_Csi2TestmodecontrolregBits_t
* RegisterName: Csi2TestModeControlReg
* 
* AddressRange: 0x0A0 - 0x0A4
* ResetValue: 0x00000FFF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: csi2_testmode_skip_pdc
	* Description: 0: test data inserted at the input side of PDC
	* 1: test data inserted at the o/p side of PDC
	*/
    uint32 Csi2TestmodeSkipPdc: 1;        /*## attribute Csi2TestmodeSkipPdc */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: csi2_testmode_data_sel
	* Description: 00 : regiser data as test data   
	* 01: Sinewave as test data   
	* 10: Incremental Pattern as test data    
	* 11: Incremental Pattern as test data
	*/
    uint32 Csi2TestmodeDataSel: 2;        /*## attribute Csi2TestmodeDataSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: csi2_testmode_en
	* Description: 0: PDC functional data asinput to csi2
	* 1: Test data is input to csi2
	*/
    uint32 Csi2TestmodeEn: 1;        /*## attribute Csi2TestmodeEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: csi2_testmode_test_data
	* Description: Debug Data to be send in Debug Mode
	*/
    uint32 Csi2TestmodeTestData: 12;        /*## attribute Csi2TestmodeTestData */
}Nxp_Tef810x_Mod02_Csi2TestmodecontrolregBits_t;
    /**
* Nxp_Tef810x_Mod02_MasterIdivCtrlBits_t
* RegisterName: master_idiv_ctrl
* 
* AddressRange: 0x0A4 - 0x0A8
* ResetValue: 0x040400B0
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: dphy_idiv_blk_cnt
	* Description: Clock divider for generating internal DPHY pll reference clock :Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz.
	*/
    uint32 DphyIdivBlkCnt: 6;        /*## attribute DphyIdivBlkCnt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: master_idiv_blk_cnt
	* Description: Output clock is blocked to avoid the propagation of glitches during clock switching. This register is used for configuring the output clock blocking time. This register value need not change for the normal use cases. Counter running at 40 MHz.
	*/
    uint32 MasterIdivBlkCnt: 6;        /*## attribute MasterIdivBlkCnt */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: master_idiv_sel_reg_lut
	* Description: Divider value selection logic 
	* 0 : select idiv value from the LUT based on decimation
	* 1 : select idiv value from the master_idiv_value register.
	*/
    uint32 MasterIdivSelRegLut: 1;        /*## attribute MasterIdivSelRegLut */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
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
	*/
    uint32 MasterIdivValue: 6;        /*## attribute MasterIdivValue */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: dphy_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for dphy clk divider when csi2 is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.This reset is not auto clearing.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 DphyIdivRst: 1;        /*## attribute DphyIdivRst */
   /**
	* BitsName: master_idiv_rst
	* Description: Debug Feature :
	* Active high soft reset for master clk divider when csi2 is selected.This reset is only to the clock divider and has no effect on other blocks such as  PDC,CRC etc.This reset is not auto clearing.
	* 0: No reset
	* 1: Assert reset to the clock divider.
	*/
    uint32 MasterIdivRst: 1;        /*## attribute MasterIdivRst */
}Nxp_Tef810x_Mod02_MasterIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlBits_t
* RegisterName: pdc_shift_reg_idiv_ctrl
* 
* AddressRange: 0x0AC - 0x0B0
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
}Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlBits_t;
    /**
* Nxp_Tef810x_Mod02_RefCntrInitBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0x0BC - 0x0C0
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
}Nxp_Tef810x_Mod02_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod02_FreqCounterStartBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0x0C0 - 0x0C4
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
}Nxp_Tef810x_Mod02_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod02_FreqCounterReadValueBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0x0C4 - 0x0C8
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
}Nxp_Tef810x_Mod02_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod02_RefCounterReadValueBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0x0C8 - 0x0CC
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
}Nxp_Tef810x_Mod02_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod02_AtbSetTrimBits_t
* RegisterName: atb_set_trim
* 
* AddressRange: 0x0D8 - 0x0DC
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
}Nxp_Tef810x_Mod02_AtbSetTrimBits_t;
    /**
* Nxp_Tef810x_Mod02_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00023301
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: Identifier value. This is the unique identifier of the module. In case of csi2 it is 0x02.
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
}Nxp_Tef810x_Mod02_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod02_Trimreg0Union_t
* Nxp_Tef810x_Mod02_Trimreg0Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Trimreg0Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Trimreg0Union_t;
/**
* Nxp_Tef810x_Mod02_Trimreg1Union_t
* Nxp_Tef810x_Mod02_Trimreg1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Trimreg1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Trimreg1Union_t;
/**
* Nxp_Tef810x_Mod02_Trimreg2Union_t
* Nxp_Tef810x_Mod02_Trimreg2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Trimreg2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Trimreg2Union_t;
/**
* Nxp_Tef810x_Mod02_Trimreg3Union_t
* Nxp_Tef810x_Mod02_Trimreg3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Trimreg3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Trimreg3Union_t;
/**
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Union_t
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Union_t;
/**
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Union_t
* Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_DphyDfeClnRegister0Union_t
* Nxp_Tef810x_Mod02_DphyDfeClnRegister0Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_DphyDfeClnRegister0Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_DphyDfeClnRegister0Union_t;
/**
* Nxp_Tef810x_Mod02_DphyDfeClnRegister1Union_t
* Nxp_Tef810x_Mod02_DphyDfeClnRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_DphyDfeClnRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_DphyDfeClnRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterUnion_t
* Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_FifoStatusRegisterUnion_t
* Nxp_Tef810x_Mod02_FifoStatusRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_FifoStatusRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_FifoStatusRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterUnion_t
* Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterUnion_t
* Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_RawPixelModeControlRegisterUnion_t
* Nxp_Tef810x_Mod02_RawPixelModeControlRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_RawPixelModeControlRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_RawPixelModeControlRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_PhyTinitCountRegisterUnion_t
* Nxp_Tef810x_Mod02_PhyTinitCountRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_PhyTinitCountRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_PhyTinitCountRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Union_t
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Union_t
* Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Union_t;
/**
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Union_t
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Union_t
* Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Union_t;
/**
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Union_t
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Union_t
* Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Union_t;
/**
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Union_t
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Union_t;
/**
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Union_t
* Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Union_t;
/**
* Nxp_Tef810x_Mod02_PllCountRegisterUnion_t
* Nxp_Tef810x_Mod02_PllCountRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_PllCountRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_PllCountRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterUnion_t
* Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterUnion_t;
/**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Union_t
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Union_t;
/**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t;
/**
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Union_t
* Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Union_t;
/**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl1Union_t
* Nxp_Tef810x_Mod02_Csi2CrcCtrl1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2CrcCtrl1Union_t;
/**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl2Union_t
* Nxp_Tef810x_Mod02_Csi2CrcCtrl2Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl2Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2CrcCtrl2Union_t;
/**
* Nxp_Tef810x_Mod02_Csi2CrcCtrl3Union_t
* Nxp_Tef810x_Mod02_Csi2CrcCtrl3Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl3Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2CrcCtrl3Union_t;
/**
* Nxp_Tef810x_Mod02_PdcConfigRegUnion_t
* Nxp_Tef810x_Mod02_PdcConfigRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_PdcConfigRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_PdcConfigRegUnion_t;
/**
* Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t
* Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2TxnCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t;
/**
* Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t
* Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_Csi2TestmodecontrolregBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t;
/**
* Nxp_Tef810x_Mod02_MasterIdivCtrlUnion_t
* Nxp_Tef810x_Mod02_MasterIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_MasterIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_MasterIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlUnion_t
* Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlUnion_t;
/**
* Nxp_Tef810x_Mod02_RefCntrInitUnion_t
* Nxp_Tef810x_Mod02_RefCntrInitUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_RefCntrInitBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_RefCntrInitUnion_t;
/**
* Nxp_Tef810x_Mod02_FreqCounterStartUnion_t
* Nxp_Tef810x_Mod02_FreqCounterStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_FreqCounterStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_FreqCounterStartUnion_t;
/**
* Nxp_Tef810x_Mod02_FreqCounterReadValueUnion_t
* Nxp_Tef810x_Mod02_FreqCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_FreqCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_FreqCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod02_RefCounterReadValueUnion_t
* Nxp_Tef810x_Mod02_RefCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_RefCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_RefCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod02_AtbSetTrimUnion_t
* Nxp_Tef810x_Mod02_AtbSetTrimUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_AtbSetTrimBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_AtbSetTrimUnion_t;
/**
* Nxp_Tef810x_Mod02_ModuleidUnion_t
* Nxp_Tef810x_Mod02_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod02_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod02_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod02_Csi2Register_t
 * Nxp_Tef810x_Mod02_Csi2Register_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: TrimReg0
    * AddressOffset: 0x000
    * ResetValue: 0x0A040218
    * Description: Dphy Trim Register0. 
	* Always keep the default value = 0x0A040218 for all modes of operation.
    */
    Nxp_Tef810x_Mod02_Trimreg0Union_t Trimreg0_ust;        /*## attribute Trimreg0_ust */
  /**
    * RegisterName: TrimReg1
    * AddressOffset: 0x004
    * ResetValue: 0x4DB1100F
    * Description: Dphy Trim Register1. 
	* Should be programmed to  
	* 
	* = 0x4DB11041  ->  120 Mbps Per Lane Mode.
	* = 0x4DB11003   -> 240 Mbps Per Lane Mode.
	* = 0x4DB11006   -> 480 Mbps Per Lane Mode.
    */
    Nxp_Tef810x_Mod02_Trimreg1Union_t Trimreg1_ust;        /*## attribute Trimreg1_ust */
  /**
    * RegisterName: TrimReg2
    * AddressOffset: 0x008
    * ResetValue: 0x10000000
    * Description: Dphy Trim Register2. 
	* Always keep the default value of 0x10000000 for all modes of operation.
    */
    Nxp_Tef810x_Mod02_Trimreg2Union_t Trimreg2_ust;        /*## attribute Trimreg2_ust */
  /**
    * RegisterName: TrimReg3
    * AddressOffset: 0x00C
    * ResetValue: 0x0020C1FC
    * Description: Dphy Trim Register3. 
	* Always keep the default value of 0x0020C1FC for all modes of operation.
    */
    Nxp_Tef810x_Mod02_Trimreg3Union_t Trimreg3_ust;        /*## attribute Trimreg3_ust */

    uint32 gap01_au32[4];        /* gap 1 in register space */  /**
    * RegisterName: DPHY_DFE_DLN_Register_0
    * AddressOffset: 0x020
    * ResetValue: 0x0A0D0716
    * Description: DLN_REG0 
	* Should be programmed to  
	* 0x03068309 -> 480 Mbps per Lane
	* 0x01038106 -> 240 Mbps per Lane
	* 0x01028004 -> 120 Mbps per Lane
    */
    Nxp_Tef810x_Mod02_DphyDfeDlnRegister0Union_t DphyDfeDlnRegister0_ust;        /*## attribute DphyDfeDlnRegister0_ust */
  /**
    * RegisterName: DPHY_DFE_DLN_Register_1
    * AddressOffset: 0x024
    * ResetValue: 0x00061E07
    * Description: DLN_REG1 
	* Should be programmed to  
	* 0x00030E04 -> 480 Mbps per Lane mode
	* 0x00010A03 -> 240 Mbps per Lane mode
	* 0x00000803 -> 120 Mbps per Lane mode
    */
    Nxp_Tef810x_Mod02_DphyDfeDlnRegister1Union_t DphyDfeDlnRegister1_ust;        /*## attribute DphyDfeDlnRegister1_ust */
  /**
    * RegisterName: DPHY_DFE_CLN_Register_0
    * AddressOffset: 0x028
    * ResetValue: 0x080D0521
    * Description: CLN_REG0
	* Should be programmed to  
	* 0x0406030E -> 480 Mbps per Lane mode
	* 0x03030106 -> 240 Mbps per Lane mode
	* 0x02024003 -> 120 Mbps per Lane mode
    */
    Nxp_Tef810x_Mod02_DphyDfeClnRegister0Union_t DphyDfeClnRegister0_ust;        /*## attribute DphyDfeClnRegister0_ust */
  /**
    * RegisterName: DPHY_DFE_CLN_Register_1
    * AddressOffset: 0x02C
    * ResetValue: 0x00000006
    * Description: CLN_REG1
	* Should be programmed to  
	* 0x000A0102 -> 480 Mbps per Lane mode
	* 0x00080101 -> 240 Mbps per Lane mode
	* 0x00070100 -> 120 Mbps per Lane mode
    */
    Nxp_Tef810x_Mod02_DphyDfeClnRegister1Union_t DphyDfeClnRegister1_ust;        /*## attribute DphyDfeClnRegister1_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: PPI_Data_Lane_Swap_Register
    * AddressOffset: 0x034
    * ResetValue: 0x00000300
    * Description: Set Number of DPHY Lanes
    */
    Nxp_Tef810x_Mod02_PpiDataLaneSwapRegisterUnion_t PpiDataLaneSwapRegister_ust;        /*## attribute PpiDataLaneSwapRegister_ust */
  /**
    * RegisterName: FIFO_status_Register
    * AddressOffset: 0x038
    * ResetValue: 0x00000000
    * Description: Sensor FIFO Status register
    */
    Nxp_Tef810x_Mod02_FifoStatusRegisterUnion_t FifoStatusRegister_ust;        /*## attribute FifoStatusRegister_ust */
  /**
    * RegisterName: USD_Pixel_Mode_Control_Register
    * AddressOffset: 0x03C
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_UsdPixelModeControlRegisterUnion_t UsdPixelModeControlRegister_ust;        /*## attribute UsdPixelModeControlRegister_ust */
  /**
    * RegisterName: YUV_Pixel_Mode_Control_Register
    * AddressOffset: 0x040
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_YuvPixelModeControlRegisterUnion_t YuvPixelModeControlRegister_ust;        /*## attribute YuvPixelModeControlRegister_ust */
  /**
    * RegisterName: RAW_Pixel_Mode_Control_Register
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_RawPixelModeControlRegisterUnion_t RawPixelModeControlRegister_ust;        /*## attribute RawPixelModeControlRegister_ust */
  /**
    * RegisterName: PHY_TINIT_Count_Register
    * AddressOffset: 0x048
    * ResetValue: 0x0000FFFF
    * Description: PHY Init Time control. (After the PLL Lock , the Clock Lane remains in the LP state till this counter is expired).Program a value of 0x00002000 (recommended ) for fast lock after reset release .
    */
    Nxp_Tef810x_Mod02_PhyTinitCountRegisterUnion_t PhyTinitCountRegister_ust;        /*## attribute PhyTinitCountRegister_ust */
  /**
    * RegisterName: VC0_compression_Prediction_Scheme_Register_1
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister1Union_t Vc0CompressionPredictionSchemeRegister1_ust;        /*## attribute Vc0CompressionPredictionSchemeRegister1_ust */
  /**
    * RegisterName: VC0_compression_Prediction_Scheme_Register_2
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc0CompressionPredictionSchemeRegister2Union_t Vc0CompressionPredictionSchemeRegister2_ust;        /*## attribute Vc0CompressionPredictionSchemeRegister2_ust */
  /**
    * RegisterName: VC1_compression_Prediction_Scheme_Register_1
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister1Union_t Vc1CompressionPredictionSchemeRegister1_ust;        /*## attribute Vc1CompressionPredictionSchemeRegister1_ust */
  /**
    * RegisterName: VC1_compression_Prediction_Scheme_Register_2
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc1CompressionPredictionSchemeRegister2Union_t Vc1CompressionPredictionSchemeRegister2_ust;        /*## attribute Vc1CompressionPredictionSchemeRegister2_ust */
  /**
    * RegisterName: VC2_compression_Prediction_Scheme_Register_1
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister1Union_t Vc2CompressionPredictionSchemeRegister1_ust;        /*## attribute Vc2CompressionPredictionSchemeRegister1_ust */
  /**
    * RegisterName: VC2_compression_Prediction_Scheme_Register_2
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc2CompressionPredictionSchemeRegister2Union_t Vc2CompressionPredictionSchemeRegister2_ust;        /*## attribute Vc2CompressionPredictionSchemeRegister2_ust */
  /**
    * RegisterName: VC3_compression_Prediction_Scheme_Register_1
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister1Union_t Vc3CompressionPredictionSchemeRegister1_ust;        /*## attribute Vc3CompressionPredictionSchemeRegister1_ust */
  /**
    * RegisterName: VC3_compression_Prediction_Scheme_Register_2
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: Keep reset value
    */
    Nxp_Tef810x_Mod02_Vc3CompressionPredictionSchemeRegister2Union_t Vc3CompressionPredictionSchemeRegister2_ust;        /*## attribute Vc3CompressionPredictionSchemeRegister2_ust */
  /**
    * RegisterName: PLL_Count_Register
    * AddressOffset: 0x06C
    * ResetValue: 0x00004E20
    * Description: Program a value of 0x00000000 (recommended ) for fast lock after reset release .
    */
    Nxp_Tef810x_Mod02_PllCountRegisterUnion_t PllCountRegister_ust;        /*## attribute PllCountRegister_ust */
  /**
    * RegisterName: Device_Ready_Indication_Register
    * AddressOffset: 0x070
    * ResetValue: 0x00000000
    * Description: Device ready Indication register
    */
    Nxp_Tef810x_Mod02_DeviceReadyIndicationRegisterUnion_t DeviceReadyIndicationRegister_ust;        /*## attribute DeviceReadyIndicationRegister_ust */

    uint32 gap02_au32[3];        /* gap 2 in register space */  /**
    * RegisterName: Csi2AdaptConfigReg1
    * AddressOffset: 0x080
    * ResetValue: 0x0000002C
    * Description: CSI2 Adapter configuration register.
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg1Union_t Csi2Adaptconfigreg1_ust;        /*## attribute Csi2Adaptconfigreg1_ust */
  /**
    * RegisterName: Csi2AdaptConfigReg2
    * AddressOffset: 0x084
    * ResetValue: 0x0C810000
    * Description: CSI2 Adapter configuration register.
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg2Union_t Csi2Adaptconfigreg2_ust;        /*## attribute Csi2Adaptconfigreg2_ust */
  /**
    * RegisterName: Csi2AdaptConfigReg3
    * AddressOffset: 0x088
    * ResetValue: 0x00000001
    * Description: CSI2 Adapter configuration register.
    */
    Nxp_Tef810x_Mod02_Csi2Adaptconfigreg3Union_t Csi2Adaptconfigreg3_ust;        /*## attribute Csi2Adaptconfigreg3_ust */
  /**
    * RegisterName: csi2_crc_ctrl1
    * AddressOffset: 0x08C
    * ResetValue: 0xFFFFFFFF
    * Description: CRC 32- control
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl1Union_t Csi2CrcCtrl1_ust;        /*## attribute Csi2CrcCtrl1_ust */
  /**
    * RegisterName: csi2_crc_ctrl2
    * AddressOffset: 0x090
    * ResetValue: 0xFFFFFFFF
    * Description: CRC 32- control
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl2Union_t Csi2CrcCtrl2_ust;        /*## attribute Csi2CrcCtrl2_ust */
  /**
    * RegisterName: csi2_crc_ctrl3
    * AddressOffset: 0x094
    * ResetValue: 0x00000110
    * Description: CRC 32- control.CRC is calculated using a 32-bit input CRC engine.Two consecutive adc samples con-catinated [data1,4'b0000 : data0,4'b0000] and given to the engine.
    */
    Nxp_Tef810x_Mod02_Csi2CrcCtrl3Union_t Csi2CrcCtrl3_ust;        /*## attribute Csi2CrcCtrl3_ust */
  /**
    * RegisterName: pdc_config_reg
    * AddressOffset: 0x098
    * ResetValue: 0x00A9A700
    * Description: PDC data valid delay con trol
    */
    Nxp_Tef810x_Mod02_PdcConfigRegUnion_t PdcConfigReg_ust;        /*## attribute PdcConfigReg_ust */
  /**
    * RegisterName: csi2_txn_ctrl
    * AddressOffset: 0x09C
    * ResetValue: 0x00000000
    * Description: CSI2 Transmission Enable register
    */
    Nxp_Tef810x_Mod02_Csi2TxnCtrlUnion_t Csi2TxnCtrl_ust;        /*## attribute Csi2TxnCtrl_ust */
  /**
    * RegisterName: Csi2TestModeControlReg
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000FFF
    * Description: only for internal validation and debug purpose.Keep default value for functional use case
    */
    Nxp_Tef810x_Mod02_Csi2TestmodecontrolregUnion_t Csi2Testmodecontrolreg_ust;        /*## attribute Csi2Testmodecontrolreg_ust */
  /**
    * RegisterName: master_idiv_ctrl
    * AddressOffset: 0x0A4
    * ResetValue: 0x040400B0
    * Description: Clock divider configuration.only for internal validation and debug purpose.Keep default value
    */
    Nxp_Tef810x_Mod02_MasterIdivCtrlUnion_t MasterIdivCtrl_ust;        /*## attribute MasterIdivCtrl_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x0A8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: pdc_shift_reg_idiv_ctrl
    * AddressOffset: 0x0AC
    * ResetValue: 0x00000002
    * Description: ADC data Sampling control register
    */
    Nxp_Tef810x_Mod02_PdcShiftRegIdivCtrlUnion_t PdcShiftRegIdivCtrl_ust;        /*## attribute PdcShiftRegIdivCtrl_ust */
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x0B0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x0B4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x0B8
    * ResetValue: 0x00000110
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: ref_cntr_init
    * AddressOffset: 0x0BC
    * ResetValue: 0x01E00028
    * Description: Frequency counter used for counting 480/600 MHz clock
    */
    Nxp_Tef810x_Mod02_RefCntrInitUnion_t RefCntrInit_ust;        /*## attribute RefCntrInit_ust */
  /**
    * RegisterName: freq_counter_start
    * AddressOffset: 0x0C0
    * ResetValue: 0x00000100
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod02_FreqCounterStartUnion_t FreqCounterStart_ust;        /*## attribute FreqCounterStart_ust */
  /**
    * RegisterName: freq_counter_read_value
    * AddressOffset: 0x0C4
    * ResetValue: 0x00000000
    * Description: Frequency Counter : Used for measuring Serialiser Clock 480/600 frequency..only for internal validation and debug purpose
    */
    Nxp_Tef810x_Mod02_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;        /*## attribute FreqCounterReadValue_ust */
  /**
    * RegisterName: ref_counter_read_value
    * AddressOffset: 0x0C8
    * ResetValue: 0x00000000
    * Description: Frequency counter used for counting 480/600 MHz clock
    */
    Nxp_Tef810x_Mod02_RefCounterReadValueUnion_t RefCounterReadValue_ust;        /*## attribute RefCounterReadValue_ust */
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x0CC
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x0D0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x0D4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: atb_set_trim
    * AddressOffset: 0x0D8
    * ResetValue: 0x00000000
    * Description: PDC Sync Enable or Disable
    */
    Nxp_Tef810x_Mod02_AtbSetTrimUnion_t AtbSetTrim_ust;        /*## attribute AtbSetTrim_ust */
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x0DC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x0E0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x0E4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x0E8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x0EC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;

    uint32 gap03_au32[961];        /* gap 3 in register space */  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;

    uint32 gap04_au32[1];        /* gap 4 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00023301
    * Description: Module ID register
    */
    Nxp_Tef810x_Mod02_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod02_Csi2Register_t;

#endif
