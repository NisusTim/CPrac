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
* @NXP_TEF810X_Ism.h
*/
#ifndef NXP_TEF810X_ISM_H
#define NXP_TEF810X_ISM_H
#include "Std_Types.h"

#define ISM_MODULE_ADDRESS 0x18
/**
*NXP_TEF810X_MOD18_STATUS_FTTI_WDT_CNTRL_U16
* RegisterName: MOD18_status_ftti_wdt_cntrl
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_STATUS_FTTI_WDT_CNTRL_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD18_FTTI_WDT_COUNT_VALUE_U16
* RegisterName: MOD18_ftti_wdt_count_value
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD18_FTTI_WDT_COUNT_VALUE_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD18_STATUS_WDT_COUNT_VALUE_U16
* RegisterName: MOD18_status_wdt_count_value
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD18_STATUS_WDT_COUNT_VALUE_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD18_FTTI_WDT_RD_VALUE_U16
* RegisterName: MOD18_ftti_wdt_rd_value
* AccessMode: READ
* AddressRange: 0x000C - 0x0010
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD18_FTTI_WDT_RD_VALUE_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD18_STATUS_WDT_RD_VALUE_U16
* RegisterName: MOD18_status_wdt_rd_value
* AccessMode: READ
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0xFFFFFFFF
*/
#define NXP_TEF810X_MOD18_STATUS_WDT_RD_VALUE_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16
* RegisterName: MOD18_MCU_startup_status_control
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MCU_STARTUP_STATUS_CONTROL_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD18_ADC_STATUS_MONITORING_CONTROL_U16
* RegisterName: MOD18_ADC_status_monitoring_control
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_STATUS_MONITORING_CONTROL_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD18_RTM_SAFETY_ERROR_CONTROL_AND_STATUS_U16
* RegisterName: MOD18_RTM_safety_error_control_and_status
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x80000700
*/
#define NXP_TEF810X_MOD18_RTM_SAFETY_ERROR_CONTROL_AND_STATUS_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16
* RegisterName: MOD18_supply_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_SUPPLY_ERROR_MASK_REG_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16
* RegisterName: MOD18_tx_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_TX_ERROR_MASK_REG_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16
* RegisterName: MOD18_rx_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RX_ERROR_MASK_REG_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16
* RegisterName: MOD18_chirp_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CHIRP_ERROR_MASK_REG_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16
* RegisterName: MOD18_mc_lo_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MC_LO_ERROR_MASK_REG_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16
* RegisterName: MOD18_adc_error_mask_reg
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_ERROR_MASK_REG_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD18_RF_POWER_DOWN_CONTROL_U16
* RegisterName: MOD18_rf_power_down_control
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x87000000
*/
#define NXP_TEF810X_MOD18_RF_POWER_DOWN_CONTROL_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16
* RegisterName: MOD18_ISM_FIT_test_reg
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ISM_FIT_TEST_REG_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_master_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_supply_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD18_TX_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_tx_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_TX_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD18_RX_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_rx_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RX_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_chirp_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_mc_lo_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD18_ADC_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_adc_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_RAW_STATUS_U16
* RegisterName: MOD18_rf_power_down_error_flag_raw_status
* AccessMode: READ
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_RAW_STATUS_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_master_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MASTER_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_supply_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_SUPPLY_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_tx_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_TX_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_rx_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RX_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_chirp_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0074 - 0x0078
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CHIRP_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0074
/**
*NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_mc_lo_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0078 - 0x007C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0078
/**
*NXP_TEF810X_MOD18_ADC_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_adc_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x007C - 0x0080
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x007C
/**
*NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_MASKED_STATUS_U16
* RegisterName: MOD18_rf_power_down_error_flag_masked_status
* AccessMode: READ
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RF_POWER_DOWN_ERROR_FLAG_MASKED_STATUS_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD18_FIT_STATUS_SUPPLY_REG_U16
* RegisterName: MOD18_fit_status_supply_reg
* AccessMode: READ
* AddressRange: 0x0084 - 0x0088
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_SUPPLY_REG_U16 (uint16)0x0084
/**
*NXP_TEF810X_MOD18_FIT_STATUS_TX_REG_U16
* RegisterName: MOD18_fit_status_tx_reg
* AccessMode: READ
* AddressRange: 0x0088 - 0x008C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_TX_REG_U16 (uint16)0x0088
/**
*NXP_TEF810X_MOD18_FIT_STATUS_RX_REG_U16
* RegisterName: MOD18_fit_status_rx_reg
* AccessMode: READ
* AddressRange: 0x008C - 0x0090
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_RX_REG_U16 (uint16)0x008C
/**
*NXP_TEF810X_MOD18_FIT_STATUS_CHIRP_REG_U16
* RegisterName: MOD18_fit_status_chirp_reg
* AccessMode: READ
* AddressRange: 0x0090 - 0x0094
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_CHIRP_REG_U16 (uint16)0x0090
/**
*NXP_TEF810X_MOD18_FIT_STATUS_MC_LO_REG_U16
* RegisterName: MOD18_fit_status_mc_lo_reg
* AccessMode: READ
* AddressRange: 0x0094 - 0x0098
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_MC_LO_REG_U16 (uint16)0x0094
/**
*NXP_TEF810X_MOD18_FIT_STATUS_ADC_REG_U16
* RegisterName: MOD18_fit_status_adc_reg
* AccessMode: READ
* AddressRange: 0x0098 - 0x009C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_FIT_STATUS_ADC_REG_U16 (uint16)0x0098
/**
*NXP_TEF810X_MOD18_ADC_STATUS_ERROR_FLAG_COUNT_U16
* RegisterName: MOD18_ADC_status_error_flag_count
* AccessMode: READ
* AddressRange: 0x00A4 - 0x00A8
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_STATUS_ERROR_FLAG_COUNT_U16 (uint16)0x00A4
/**
*NXP_TEF810X_MOD18_STATUS_MONITORING_FLAG_U16
* RegisterName: MOD18_status_monitoring_flag
* AccessMode: READ
* AddressRange: 0x00A8 - 0x00AC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_STATUS_MONITORING_FLAG_U16 (uint16)0x00A8
/**
*NXP_TEF810X_MOD18_ISM_ERROR_STATUS_AND_MCU_RESET_U16
* RegisterName: MOD18_ISM_error_status_and_mcu_reset
* AccessMode: READWRITE
* AddressRange: 0x00AC - 0x00B0
* ResetValue: 0x00880000
*/
#define NXP_TEF810X_MOD18_ISM_ERROR_STATUS_AND_MCU_RESET_U16 (uint16)0x00AC
/**
*NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16
* RegisterName: MOD18_loop_back_test_reg
* AccessMode: READWRITE
* AddressRange: 0x00B8 - 0x00BC
* ResetValue: 0x80007F00
*/
#define NXP_TEF810X_MOD18_LOOP_BACK_TEST_REG_U16 (uint16)0x00B8
/**
*NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16
* RegisterName: MOD18_supply_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00BC - 0x00C0
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_SUPPLY_ERROR_MON_REG_U16 (uint16)0x00BC
/**
*NXP_TEF810X_MOD18_TX_ERROR_MON_REG_U16
* RegisterName: MOD18_tx_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00C0 - 0x00C4
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_TX_ERROR_MON_REG_U16 (uint16)0x00C0
/**
*NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16
* RegisterName: MOD18_rx_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00C4 - 0x00C8
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_RX_ERROR_MON_REG_U16 (uint16)0x00C4
/**
*NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16
* RegisterName: MOD18_chirp_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00C8 - 0x00CC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CHIRP_ERROR_MON_REG_U16 (uint16)0x00C8
/**
*NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16
* RegisterName: MOD18_mc_lo_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00CC - 0x00D0
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_MC_LO_ERROR_MON_REG_U16 (uint16)0x00CC
/**
*NXP_TEF810X_MOD18_ADC_ERROR_MON_REG_U16
* RegisterName: MOD18_adc_error_mon_reg
* AccessMode: READWRITE
* AddressRange: 0x00D0 - 0x00D4
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_ADC_ERROR_MON_REG_U16 (uint16)0x00D0
/**
*NXP_TEF810X_MOD18_CRC_STATUS_WR_REG_U16
* RegisterName: MOD18_crc_status_wr_reg
* AccessMode: READWRITE
* AddressRange: 0x00D4 - 0x00D8
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CRC_STATUS_WR_REG_U16 (uint16)0x00D4
/**
*NXP_TEF810X_MOD18_CRC_STATUS_RD_REG_U16
* RegisterName: MOD18_crc_status_rd_reg
* AccessMode: READWRITE
* AddressRange: 0x00D8 - 0x00DC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD18_CRC_STATUS_RD_REG_U16 (uint16)0x00D8
/**
*NXP_TEF810X_MOD18_MODULEID_U16
* RegisterName: MOD18_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00182301
*/
#define NXP_TEF810X_MOD18_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod18_STATUS_FTTI_WDT_CNTRLBits_t
* RegisterName: status_ftti_wdt_cntrl
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: ftti_wdt_en
	* Description: Enable  FTTI WDT
	* 0: WDT is disabled
	* 1: WDT is enabled and start running
	* Once enabled,  the timer will wait for a chirp sequence start trigger to start the timer.
	* Once a FIT is triggered or if the timer is  resetted by MCU,  then the timer will wait for next chirp sequence active to start again (provided the WDT is configured in continuous mode)
	*/
    uint32 FttiWdtEn: 1;        /*## attribute FttiWdtEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ftti_wdt_active
	* Description: 0: Indicates timer is not active
	* 1: Indicates timer is active and running
	*/
    uint32 FttiWdtActive: 1;        /*## attribute FttiWdtActive */
   /**
	* BitsName: ftti_wdt_mode
	* Description: FTTI WDT mode
	* 0: Moonshot Mode
	* 1: Continuous Mode
	* Preferred use model : Continuous mode  to reduce programming overhead
	*/
    uint32 FttiWdtMode: 1;        /*## attribute FttiWdtMode */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: ftti_wdt_count_base
	* Description: Base counter for FTTI WDT
	* 0000: Timer runs at 40 MHz time base
	* 0001: 20 MHz time base
	* 0010: (40/3) MHz
	* 0011: (40/4)MHz.
	* etc.?
	* Use model: Time base value depends on the  FTTI interval
	*/
    uint32 FttiWdtCountBase: 4;        /*## attribute FttiWdtCountBase */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 4;        /*## attribute Reserved2 */
   /**
	* BitsName: status_wdt_en
	* Description: Enable and start trigger  for status WDT
	* 0: WDT is disabled
	* 1: WDT is enabled and start running
	*/
    uint32 StatusWdtEn: 1;        /*## attribute StatusWdtEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: status_wdt_active
	* Description: 0: Indicates timer is not active (expired)
	* 1: Indicates timer is active and running
	*/
    uint32 StatusWdtActive: 1;        /*## attribute StatusWdtActive */
   /**
	* BitsName: status_wdt_mode
	* Description: Mode control for status WDT
	* 0: Moonshot Mode
	* 1: Continuous Mode
	* Preferred use model is to use in continuous mode to generate  a heart beat interrupt to MCU at regular interval.
	*/
    uint32 StatusWdtMode: 1;        /*## attribute StatusWdtMode */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 4;        /*## attribute Reserved4 */
   /**
	* BitsName: status_wdt_count_base
	* Description: Base counter for status WDT
	* 0000: Timer runs at 40 MHz time base
	* 0001: 20 MHz time base
	* 0010: (40/3) MHz
	* 0011: (40/4)MHz.
	* etc.?
	* Use model: time base value depends on the  duration between  heartbeat interrupt.
	*/
    uint32 StatusWdtCountBase: 4;        /*## attribute StatusWdtCountBase */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_StatusFttiWdtCntrlBits_t;
    /**
* Nxp_Tef810x_Mod18_FTTI_WDT_COUNT_VALUEBits_t
* RegisterName: ftti_wdt_count_value
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: ftti_wdt_count_value
	* Description: The value to be programmed to be used along with the base count value  to  calculate the actual  timer interval. The counter is decremented  at an interval defined by the _wdt_count_base  frequency
	*/
    uint32 FttiWdtCountValue: 31;        /*## attribute FttiWdtCountValue */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FttiWdtCountValueBits_t;
    /**
* Nxp_Tef810x_Mod18_STATUS_WDT_COUNT_VALUEBits_t
* RegisterName: status_wdt_count_value
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: status_wdt_count_value
	* Description: Status WDT watchdog timer interval value
	* The value to be programmed to be used along with the base count value  to  calculate the actual  timer interval
	*/
    uint32 StatusWdtCountValue: 31;        /*## attribute StatusWdtCountValue */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_StatusWdtCountValueBits_t;
    /**
* Nxp_Tef810x_Mod18_FTTI_WDT_RD_VALUEBits_t
* RegisterName: ftti_wdt_rd_value
* 
* AddressRange: 0xREAD - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: ftti_wdt_rd_value
	* Description: ftti_wdt_rd_value ( current value of the timer)
	* Indicates the running status of the  timer.
	*/
    uint32 FttiWdtRdValue: 31;        /*## attribute FttiWdtRdValue */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FttiWdtRdValueBits_t;
    /**
* Nxp_Tef810x_Mod18_STATUS_WDT_RD_VALUEBits_t
* RegisterName: status_wdt_rd_value
* 
* AddressRange: 0xREAD - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: status_wdt_rd_value
	* Description: status_wdt_rd_value ( current value of the timer)
	* Indicates the running status of the  timer.
	*/
    uint32 StatusWdtRdValue: 31;        /*## attribute StatusWdtRdValue */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_StatusWdtRdValueBits_t;
    /**
* Nxp_Tef810x_Mod18_MCU_STARTUP_STATUS_CONTROLBits_t
* RegisterName: MCU_startup_status_control
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: spi_access_check_done_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 SpiAccessCheckDoneOk: 1;        /*## attribute SpiAccessCheckDoneOk */
   /**
	* BitsName: main_ldo_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 MainLdoConfigOk: 1;        /*## attribute MainLdoConfigOk */
   /**
	* BitsName: gobal_bias_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 GobalBiasConfigOk: 1;        /*## attribute GobalBiasConfigOk */
   /**
	* BitsName: local_ldo_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 LocalLdoConfigOk: 1;        /*## attribute LocalLdoConfigOk */
   /**
	* BitsName: IC_calibration_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 IcCalibrationOk: 1;        /*## attribute IcCalibrationOk */
   /**
	* BitsName: local_bias_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 LocalBiasConfigOk: 1;        /*## attribute LocalBiasConfigOk */
   /**
	* BitsName: pll4g_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 Pll4GConfigOk: 1;        /*## attribute Pll4GConfigOk */
   /**
	* BitsName: Sensor_configuration_done
	* Description: 0: Not verified
	* 1: All FS sensors are configured  &  configurations are verified
	*/
    uint32 SensorConfigurationDone: 1;        /*## attribute SensorConfigurationDone */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_McuStartupStatusControlBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_STATUS_MONITORING_CONTROLBits_t
* RegisterName: ADC_status_monitoring_control
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: status_monitoring_set_spi
	* Description: Select the Status monitoring window 
	* 
	* 0: ADC monitoring happens only during safety monitor window 
	* 1:  ADC monitoring happens all the time as long as  it is enabled
	*/
    uint32 StatusMonitoringSetSpi: 1;        /*## attribute StatusMonitoringSetSpi */
   /**
	* BitsName: status_monitoring_reset_spi
	* Description: Resets ADC Status Monitoring Counter in register 0XA4. Auto clearing Bit.
	* 
	* Note:  If  the counter reaches  maximum, it will automatically rollover to 0
	*/
    uint32 StatusMonitoringResetSpi: 1;        /*## attribute StatusMonitoringResetSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: status_monitoring_en
	* Description: Enable status monitoring
	* 0: If ADC status monitoring disabled
	* 1: If ADC status monitoring enabled
	*/
    uint32 StatusMonitoringEn: 1;        /*## attribute StatusMonitoringEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 7;        /*## attribute Reserved1 */
   /**
	* BitsName: ADC_error_count_sel
	* Description: Selects the ADC error flag to be monitored
	* 0: adc_hard_clipping_error_flag 
	* 1: adc_clipping_error_flag 
	* 2: adc_near_clipping_error_flag  
	* Others : adc_hard_clipping_error_flag
	*/
    uint32 AdcErrorCountSel: 2;        /*## attribute AdcErrorCountSel */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 6;        /*## attribute Reserved2 */
   /**
	* BitsName: status_error_poll_count_value
	* Description: Controls the duration of ADC error flags polling. Higher the value lesser the polling. This is primarily valid for the ADC error flag counter. This timer runs on a 40 MHz time base (25 ns)
	* 0000  Status polled on every 100ns  (4 Clock cycle)
	* 0001  Status polled at 125 ns (4 Clock cycle + 1 Clock cycle)
	* 0010  Status polled at 150 ns (4 Clock cycle + 2 Clock cycle)
	* Appication recommendation:  use value '0
	*/
    uint32 StatusErrorPollCountValue: 7;        /*## attribute StatusErrorPollCountValue */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcStatusMonitoringControlBits_t;
    /**
* Nxp_Tef810x_Mod18_RTM_SAFETY_ERROR_CONTROL_AND_STATUSBits_t
* RegisterName: RTM_safety_error_control_and_status
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: rtm_error_safety_count_max_value
	* Description: This can be used to  to  count the number of a time an error is geting asserted, before  issuing an error indication to MCU (error_n) .  The logic is active if a value other than '0'is programmed in this register.  if a non zero value is programmed, then based on the   ""rt_error_poll_count_value"" value  the error  input is polled  a number of ttimes (based on the value programmed)  before asserting  error_n
	* 
	* 
	* 
	* Based on validation is it found that  a value other than 0x0  shall not be used by end application.
	*/
    uint32 RtmErrorSafetyCountMaxValue: 8;        /*## attribute RtmErrorSafetyCountMaxValue */
   /**
	* BitsName: rt_error_poll_count_value
	* Description: Once an error  is reported to ISM, it is reporetd immediately to the error_n pin and.. However  the state machine need a minimum turn around  time to  poll for any new error.    This is defined by the minimum  value  programmed into this register. 
	* 
	* 
	* 
	* From an application context a value other than 'F' shall not be used ( value based on  simulation )"to be updated
	*/
    uint32 RtErrorPollCountValue: 8;        /*## attribute RtErrorPollCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: safety_err_count_reset_en
	* Description: A set of counters are provided in registers RTM_safety_errorr_count_1 (0x9C) and RTM_safety_errorr_count_2 (0xA0)  for diagnostic purpose.  ( The count is incremented based each time an error is reported ). The counter  can be resetted by MCU. Two options are available
	* 
	* 0:  Safety error count is  resetted explicitly through MCU ( error reset)
	* 1: If this bit is enabled,  the safety error count is resetted  before starting a chirp sequence
	* Please note that this is not part of the safety monitoring net.
	* Details are in rtm_safety_error_count_1 and rtm_safety_error_count_2.
	*/
    uint32 SafetyErrCountResetEn: 1;        /*## attribute SafetyErrCountResetEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SUPPLY_ERROR_MASK_REGBits_t
* RegisterName: supply_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_mask
	* Description: Supply 1V8 low sensor  for TX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx11V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx11V8Mask */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_mask
	* Description: Supply 1V8 low sensor  for TX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx21V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx21V8Mask */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_mask
	* Description: Supply 1V8 low sensor  for TX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx31V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx31V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_mask
	* Description: Supply 1V1 low sensor  for RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx11V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx11V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_mask
	* Description: Supply 1V1 low sensor  for RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx21V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx21V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_mask
	* Description: Supply 1V1 low sensor  for RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx31V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx31V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_mask
	* Description: Supply 1V1 low sensor  for RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx41V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx41V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_mask
	* Description: Supply 1V8 low sensor  for RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx11V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx11V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_mask
	* Description: Supply 1V8 low sensor  for RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx21V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx21V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_mask
	* Description: Supply 1V8 low sensor  for RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx31V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx31V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_mask
	* Description: Supply 1V8 low sensor  for RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx41V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx41V8Mask */
   /**
	* BitsName: supply_low_error_flag_mc_1v8_mask
	* Description: Supply 1V8 low sensor  for master clock ( ( cover pin failure))
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagMc1V8Mask: 1;        /*## attribute SupplyLowErrorFlagMc1V8Mask */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_mask
	* Description: Supply 1V8 low sensor  for ADC12
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagAdc121V8Mask: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Mask */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_mask
	* Description: Supply 1V8 low sensor  for ADC34
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagAdc341V8Mask: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Mask */
   /**
	* BitsName: supply_low_error_flag_interface_1v1_mask
	* Description: Supply 1V8 low sensor  for LO interface
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagInterface1V1Mask: 1;        /*## attribute SupplyLowErrorFlagInterface1V1Mask */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8_mask
	* Description: Supply 1V8 low sensor  for SSB MOD
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8Mask: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8Mask */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8_mask
	* Description: Supply 1V8 low sensor  for global bias
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8Mask */
   /**
	* BitsName: supply_low_error_flag_ser_1v1_mask
	* Description: Supply 1V1 low sensor  for serializer LVDS
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSer1V1Mask: 1;        /*## attribute SupplyLowErrorFlagSer1V1Mask */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1_mask
	* Description: Supply 1V1 low sensor  for serializer CSI2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagCsi21V1Mask: 1;        /*## attribute SupplyLowErrorFlagCsi21V1Mask */
   /**
	* BitsName: supply_low_error_flag_ser_1v8_mask
	* Description: Supply 1V8 low sensor  for serializer
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSer1V8Mask: 1;        /*## attribute SupplyLowErrorFlagSer1V8Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8_mask
	* Description: Supply 1V8  low sensor  for chirp PLL ( cover pin failure)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8Mask: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8_mask
	* Description: Supply 1V8  low sensor  for chirp VCO ( cover pin failure)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8Mask: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1_mask
	* Description: Supply 1V1  low sensor  for chirp digital
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1Mask: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1Mask */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8_mask
	* Description: Global 1V8LDO supply low  sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8Mask */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8_mask
	* Description: Global 1V8LDO supply high sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8Mask: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8Mask */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1_mask
	* Description: Global 1V1LDO supply low  sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1Mask */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1_mask
	* Description: Global 1V1LDO supply high sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1Mask: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1Mask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_SupplyErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_TX_ERROR_MASK_REGBits_t
* RegisterName: tx_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_tx1_mask
	* Description: Functional safety error flag
	* 
	* TX1 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx1Mask: 1;        /*## attribute BbErrorFlagTx1Mask */
   /**
	* BitsName: bb_error_flag_tx2_mask
	* Description: Functional safety error flag
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx2Mask: 1;        /*## attribute BbErrorFlagTx2Mask */
   /**
	* BitsName: bb_error_flag_tx3_mask
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx3Mask: 1;        /*## attribute BbErrorFlagTx3Mask */
   /**
	* BitsName: temp_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx1Mask: 1;        /*## attribute TempErrorFlagTx1Mask */
   /**
	* BitsName: temp_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx2Mask: 1;        /*## attribute TempErrorFlagTx2Mask */
   /**
	* BitsName: temp_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx3Mask: 1;        /*## attribute TempErrorFlagTx3Mask */
   /**
	* BitsName: rf_min_error_flag_tx1_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx1Mask: 1;        /*## attribute RfMinErrorFlagTx1Mask */
   /**
	* BitsName: rf_min_error_flag_tx2_mask
	* Description: Functional safety error flag
	* 
	* TX2 Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx2Mask: 1;        /*## attribute RfMinErrorFlagTx2Mask */
   /**
	* BitsName: rf_min_error_flag_tx3_mask
	* Description: Functional safety error flag
	* 
	* TX3 Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx3Mask: 1;        /*## attribute RfMinErrorFlagTx3Mask */
   /**
	* BitsName: rf_low_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx1Mask: 1;        /*## attribute RfLowErrorFlagTx1Mask */
   /**
	* BitsName: rf_low_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx2Mask: 1;        /*## attribute RfLowErrorFlagTx2Mask */
   /**
	* BitsName: rf_low_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx3Mask: 1;        /*## attribute RfLowErrorFlagTx3Mask */
   /**
	* BitsName: rf_high_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx1Mask: 1;        /*## attribute RfHighErrorFlagTx1Mask */
   /**
	* BitsName: rf_high_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx2Mask: 1;        /*## attribute RfHighErrorFlagTx2Mask */
   /**
	* BitsName: rf_high_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx3Mask: 1;        /*## attribute RfHighErrorFlagTx3Mask */
   /**
	* BitsName: rf_max_error_flag_tx1_mask
	* Description: Reliability flag
	* 
	* TX1 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx1Mask: 1;        /*## attribute RfMaxErrorFlagTx1Mask */
   /**
	* BitsName: rf_max_error_flag_tx2_mask
	* Description: Reliability flag
	* 
	* TX2 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx2Mask: 1;        /*## attribute RfMaxErrorFlagTx2Mask */
   /**
	* BitsName: rf_max_error_flag_tx3_mask
	* Description: Reliability flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx3Mask: 1;        /*## attribute RfMaxErrorFlagTx3Mask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_TxErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RX_ERROR_MASK_REGBits_t
* RegisterName: rx_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_rx1_mask
	* Description: Functional safety error flag
	* 
	* RX1  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx1Mask: 1;        /*## attribute BbErrorFlagRx1Mask */
   /**
	* BitsName: bb_error_flag_rx2_mask
	* Description: Functional safety error flag
	* 
	* RX2  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx2Mask: 1;        /*## attribute BbErrorFlagRx2Mask */
   /**
	* BitsName: bb_error_flag_rx3_mask
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx3Mask: 1;        /*## attribute BbErrorFlagRx3Mask */
   /**
	* BitsName: bb_error_flag_rx4_mask
	* Description: Functional safety error flag
	* 
	* RX4  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx4Mask: 1;        /*## attribute BbErrorFlagRx4Mask */
   /**
	* BitsName: lo_min_error_flag_rx1_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx1Mask: 1;        /*## attribute LoMinErrorFlagRx1Mask */
   /**
	* BitsName: lo_min_error_flag_rx2_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx2Mask: 1;        /*## attribute LoMinErrorFlagRx2Mask */
   /**
	* BitsName: lo_min_error_flag_rx3_mask
	* Description: Functional safety error flag  
	* 
	* Functional safety error in RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx3Mask: 1;        /*## attribute LoMinErrorFlagRx3Mask */
   /**
	* BitsName: lo_min_error_flag_rx4_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx4Mask: 1;        /*## attribute LoMinErrorFlagRx4Mask */
   /**
	* BitsName: lo_low_error_flag_rx1_mask
	* Description: Status monitoring error flag 
	* 
	* RX1 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx1Mask: 1;        /*## attribute LoLowErrorFlagRx1Mask */
   /**
	* BitsName: lo_low_error_flag_rx2_mask
	* Description: Status monitoring error flag 
	* RX2 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx2Mask: 1;        /*## attribute LoLowErrorFlagRx2Mask */
   /**
	* BitsName: lo_low_error_flag_rx3_mask
	* Description: Status monitoring error flag 
	* 
	* RX3 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx3Mask: 1;        /*## attribute LoLowErrorFlagRx3Mask */
   /**
	* BitsName: lo_low_error_flag_rx4_mask
	* Description: Status monitoring error flag 
	* 
	* RX4 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4Mask: 1;        /*## attribute LoLowErrorFlagRx4Mask */
   /**
	* BitsName: lo_high_error_flag_rx1_mask
	* Description: Status monitoring error flag 
	* 
	* RX1 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx1Mask: 1;        /*## attribute LoHighErrorFlagRx1Mask */
   /**
	* BitsName: lo_high_error_flag_rx2_mask
	* Description: Status monitoring error flag 
	* 
	* RX2 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx2Mask: 1;        /*## attribute LoHighErrorFlagRx2Mask */
   /**
	* BitsName: lo_high_error_flag_rx3_mask
	* Description: Status monitoring error flag 
	* 
	* RX3 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx3Mask: 1;        /*## attribute LoHighErrorFlagRx3Mask */
   /**
	* BitsName: lo_high_error_flag_rx4_mask
	* Description: Status monitoring error flag 
	* 
	* RX4 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx4Mask: 1;        /*## attribute LoHighErrorFlagRx4Mask */
   /**
	* BitsName: lo_max_error_flag_rx1_mask
	* Description: Relaibility error flag
	* 
	* RX1 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx1Mask: 1;        /*## attribute LoMaxErrorFlagRx1Mask */
   /**
	* BitsName: lo_max_error_flag_rx2_mask
	* Description: Relaibility error flag
	* 
	* RX2 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx2Mask: 1;        /*## attribute LoMaxErrorFlagRx2Mask */
   /**
	* BitsName: lo_max_error_flag_rx3_mask
	* Description: Relaibility error flag
	* 
	* RX3 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx3Mask: 1;        /*## attribute LoMaxErrorFlagRx3Mask */
   /**
	* BitsName: lo_max_error_flag_rx4_mask
	* Description: Relaibility error flag
	* 
	* RX4 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx4Mask: 1;        /*## attribute LoMaxErrorFlagRx4Mask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RxErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CHIRP_ERROR_MASK_REGBits_t
* RegisterName: chirp_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: lock_step_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LockStepErrorFlagChirpMask: 1;        /*## attribute LockStepErrorFlagChirpMask */
   /**
	* BitsName: unlock_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 UnlockErrorFlagChirpMask: 1;        /*## attribute UnlockErrorFlagChirpMask */
   /**
	* BitsName: max_temp_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 MaxTempErrorFlagChirpMask: 1;        /*## attribute MaxTempErrorFlagChirpMask */
   /**
	* BitsName: vtune_low_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VtuneLowErrorFlagChirpMask: 1;        /*## attribute VtuneLowErrorFlagChirpMask */
   /**
	* BitsName: vtune_high_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VtuneHighErrorFlagChirpMask: 1;        /*## attribute VtuneHighErrorFlagChirpMask */
   /**
	* BitsName: level_low_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	*  Chirp VCO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelLowErrorFlagChirpMask: 1;        /*## attribute LevelLowErrorFlagChirpMask */
   /**
	* BitsName: level_high_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp VCO level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelHighErrorFlagChirpMask: 1;        /*## attribute LevelHighErrorFlagChirpMask */
   /**
	* BitsName: level_min_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp VCO/PLL not operational
	* Functional safety error in Chirp
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelMinErrorFlagChirpMask: 1;        /*## attribute LevelMinErrorFlagChirpMask */
   /**
	* BitsName: level_max_error_flag_chirp_mask
	* Description: Reliability  safety error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelMaxErrorFlagChirpMask: 1;        /*## attribute LevelMaxErrorFlagChirpMask */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter operates within the data acquisition window  ( programmable window within data acquistion)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VcoFreq480ErrorFlagChirpMask: 1;        /*## attribute VcoFreq480ErrorFlagChirpMask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: Error not masked
	* 1: Error Masked
	*/
    uint32 InterfaceStuckFlagChirpMask: 1;        /*## attribute InterfaceStuckFlagChirpMask */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 17;        /*## attribute Reserved1 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_ChirpErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_MC_LO_ERROR_MASK_REGBits_t
* RegisterName: mc_lo_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: mc_pll_freq_cal_flag_mask
	* Description: Status monitoring flag mask
	*  
	* Main pll (4.8GHz) calibration issues ( out of calibration)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllFreqCalFlagMask: 1;        /*## attribute McPllFreqCalFlagMask */
   /**
	* BitsName: mc_pll_level_error_flag_mask
	* Description: Functional safety error flag 
	* 
	* Main PLL (4.8GHz) O/P  level is too low or too high
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllLevelErrorFlagMask: 1;        /*## attribute McPllLevelErrorFlagMask */
   /**
	* BitsName: mc_pll_lock_error_flag_mask
	* Description: Functional safety error flag 
	* 
	* Main PLL (4.8GHz) in un lock condition
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllLockErrorFlagMask: 1;        /*## attribute McPllLockErrorFlagMask */
   /**
	* BitsName: dig_freq_error_flag_masterclk_mask
	* Description: Functional safety error flag 
	* 
	* The O/P frequency from master clock is not within tolerable limits (480/.600 MHz digital clock)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 DigFreqErrorFlagMasterclkMask: 1;        /*## attribute DigFreqErrorFlagMasterclkMask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface_mask
	* Description: Functional safety error flag 
	* 
	* RF port connectivity issues reported in LO interface  block 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagInterfaceMask: 1;        /*## attribute BbErrorFlagInterfaceMask */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: jtag_active_set_mask
	* Description: Functional safety error flag 
	* 
	* Dolphin IC SPI interface can also work in JTAG mode for test access.
	* In an functional safety application context, the interface has to eb sued only in SPI mode.  If by accident or due to a stuck at issues within Dolphin, if the interface mode is changed,  then no more SPI access is possible.  In this case  the error_n pin is asserted to indicate a functional safety issue in Dolphin
	* 
	* SPI interface moved to test mode (JTAG mode). Indicate a functional failure.  If this failure happens,, then SPI interface is not accessible any more. This register can be accessed only in JTAG mode.    In  a functional safety application context, this error has to be enabled always.
	* 
	* 
	* 0: Error not masked
	* 1: Error masked
	* 
	* Note: The mask feature here is only for validation
	*/
    uint32 JtagActiveSetMask: 1;        /*## attribute JtagActiveSetMask */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: wr_crc_mask
	* Description: CRC Write error flag
	* CRC Write Error Mask
	* 0 : Error not masked
	* 1 : Error masked
	*/
    uint32 WrCrcMask: 1;        /*## attribute WrCrcMask */
   /**
	* BitsName: rd_crc_mask
	* Description: CRC Read error flag
	* CRC Read Error Mask
	* 0 : Error not masked
	* 1 : Error masked
	*/
    uint32 RdCrcMask: 1;        /*## attribute RdCrcMask */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 13;        /*## attribute Reserved3 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_McLoErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_ERROR_MASK_REGBits_t
* RegisterName: adc_error_mask_reg
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: adc1_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC1
	* Indicate a calibaration error within ADC 1
	* 
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1CalErrorMaskPersistent: 1;        /*## attribute Adc1CalErrorMaskPersistent */
   /**
	* BitsName: adc2_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC2
	* Indicate a calibaration error within ADC 2
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2CalErrorMaskPersistent: 1;        /*## attribute Adc2CalErrorMaskPersistent */
   /**
	* BitsName: adc3_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC3
	* Indicate a calibaration error within ADC 3
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3CalErrorMaskPersistent: 1;        /*## attribute Adc3CalErrorMaskPersistent */
   /**
	* BitsName: adc4_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC4
	* Indicate a calibaration error within ADC 4
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4CalErrorMaskPersistent: 1;        /*## attribute Adc4CalErrorMaskPersistent */
   /**
	* BitsName: adc1_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1NearClippingMaskPersistent: 1;        /*## attribute Adc1NearClippingMaskPersistent */
   /**
	* BitsName: adc2_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2NearClippingMaskPersistent: 1;        /*## attribute Adc2NearClippingMaskPersistent */
   /**
	* BitsName: adc3_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3NearClippingMaskPersistent: 1;        /*## attribute Adc3NearClippingMaskPersistent */
   /**
	* BitsName: adc4_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4NearClippingMaskPersistent: 1;        /*## attribute Adc4NearClippingMaskPersistent */
   /**
	* BitsName: adc1_near_clipping_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1NearClippingMask: 1;        /*## attribute Adc1NearClippingMask */
   /**
	* BitsName: adc2_near_clipping_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2NearClippingMask: 1;        /*## attribute Adc2NearClippingMask */
   /**
	* BitsName: adc3_near_clipping_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3NearClippingMask: 1;        /*## attribute Adc3NearClippingMask */
   /**
	* BitsName: adc4_near_clipping_mask
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4NearClippingMask: 1;        /*## attribute Adc4NearClippingMask */
   /**
	* BitsName: adc1_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1ClippingMaskPersistent: 1;        /*## attribute Adc1ClippingMaskPersistent */
   /**
	* BitsName: adc2_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2ClippingMaskPersistent: 1;        /*## attribute Adc2ClippingMaskPersistent */
   /**
	* BitsName: adc3_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3ClippingMaskPersistent: 1;        /*## attribute Adc3ClippingMaskPersistent */
   /**
	* BitsName: adc4_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4ClippingMaskPersistent: 1;        /*## attribute Adc4ClippingMaskPersistent */
   /**
	* BitsName: adc1_clipping_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1ClippingMask: 1;        /*## attribute Adc1ClippingMask */
   /**
	* BitsName: adc2_clipping_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2ClippingMask: 1;        /*## attribute Adc2ClippingMask */
   /**
	* BitsName: adc3_clipping_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3ClippingMask: 1;        /*## attribute Adc3ClippingMask */
   /**
	* BitsName: adc4_clipping_mask
	* Description: Status monitoring flag
	* ADC4
	*  0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4ClippingMask: 1;        /*## attribute Adc4ClippingMask */
   /**
	* BitsName: adc1_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1HardClippingMaskPersistent: 1;        /*## attribute Adc1HardClippingMaskPersistent */
   /**
	* BitsName: adc2_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2HardClippingMaskPersistent: 1;        /*## attribute Adc2HardClippingMaskPersistent */
   /**
	* BitsName: adc3_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3HardClippingMaskPersistent: 1;        /*## attribute Adc3HardClippingMaskPersistent */
   /**
	* BitsName: adc4_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4HardClippingMaskPersistent: 1;        /*## attribute Adc4HardClippingMaskPersistent */
   /**
	* BitsName: adc1_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1HardClippingErrorMask: 1;        /*## attribute Adc1HardClippingErrorMask */
   /**
	* BitsName: adc2_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2HardClippingErrorMask: 1;        /*## attribute Adc2HardClippingErrorMask */
   /**
	* BitsName: adc3_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3HardClippingErrorMask: 1;        /*## attribute Adc3HardClippingErrorMask */
   /**
	* BitsName: adc4_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC4
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4HardClippingErrorMask: 1;        /*## attribute Adc4HardClippingErrorMask */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RF_POWER_DOWN_CONTROLBits_t
* RegisterName: rf_power_down_control
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_power_down_count_threshold
	* Description: This can be used to  to  count the number of a time an error is geting asserted, before  issuing an error indication to MCU (error_n) .  The logic is active if a value other than '0'is programmed in thsi register.  if a non zero value is programmed, then based on the   "rf_power_down_flag_poll_count_value" value  the error  input is polled  a number of ttimes (based on the value programmed)  before asserting  error_n
	* 
	* 
	* 
	* Based on validation is it found that  a value other than 0x0  shall not be used by end application.
	*/
    uint32 RfPowerDownCountThreshold: 4;        /*## attribute RfPowerDownCountThreshold */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: rf_power_down_flag_poll_count_value
	* Description: Once an error  is reported to ISM, it is reporetd immediately to the error_n pin and a RF power down is initiated.. However  the state machine need a minimum turn around  time to  poll for any new error.    This is defined by the minimum  value  programmed into this register. 
	* 
	* 
	* 
	* From an application context a value other than 'F' shall not be used ( value based on  simulation )
	*/
    uint32 RfPowerDownFlagPollCountValue: 4;        /*## attribute RfPowerDownFlagPollCountValue */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RfPowerDownControlBits_t;
    /**
* Nxp_Tef810x_Mod18_ISM_FIT_TEST_REGBits_t
* RegisterName: ISM_FIT_test_reg
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: ism_test_complete
	* Description: ISM test complete
	* 0: Test ongoing
	* 1: Indicate test complete, stay here at till a new test is triggered or till reset
	*/
    uint32 IsmTestComplete: 1;        /*## attribute IsmTestComplete */
   /**
	* BitsName: fit_status_rtm_0
	* Description: RTM (error_n pin) fit status on ISM and error_n
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRtm0: 1;        /*## attribute FitStatusRtm0 */
   /**
	* BitsName: fit_status_rtm_1
	* Description: At the end of test, the status of internal ISM is tracked through this register.
	* RTM (error_n pin) fit status on ISM and error_n ( redundant module)
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRtm1: 1;        /*## attribute FitStatusRtm1 */
   /**
	* BitsName: fit_status_rf_powerdown_0
	* Description: RF power down ISM (error_n pin) fit status on ISM and error_n
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRfPowerdown0: 1;        /*## attribute FitStatusRfPowerdown0 */
   /**
	* BitsName: fit_status_rf_powerdown_1
	* Description: At the end of test, the status of internal ISM is tracked through this register.
	* RF power down ISM  (error_n pin) fit status on ISM and error_n ( redundant module)
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRfPowerdown1: 1;        /*## attribute FitStatusRfPowerdown1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ism_osm_test_force_error
	* Description: MCU can use this bit to start a FIT test on ISM (force error)
	* 0: No impact
	* 1:  Internal ISM self test begins including force error assertion to  internal functional safety sensor.  Once  force error is asserted,  error_n should go low and all internal sensors also should report an error  ( MCU to poll the error_n pin. Internal error reported from sensor status is tracked through a FIT status register)
	* Once in reset  error state  a reset  error is asserted on all internal sensors, and  this also should result in error_n pin going high ( as long as this signal is asserted) . MCU shall assert the force error for at least one us 
	* Note: While operating in dynamic power down mode/power save mode especially with chirp in power save mode, FIT test (setting this bit to 1) should be for the minimum period of 60 us before checking the status flags as the vco_480 clock to test the lockstep path is available only after this time because of the vco powerup time in the non-chirping mode.   In non powersave mode, there is no such strict timing requirements as the vco_480 clock is always available.
	*/
    uint32 IsmOsmTestForceError: 1;        /*## attribute IsmOsmTestForceError */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 7;        /*## attribute Reserved1 */
   /**
	* BitsName: ism_osm_test_reset_error
	* Description: MCU can use this bit to start a FIT test on ISM ( reset error). 
	* 0: No impact
	* 1:  at the end of a force error cycle, a reset error is  issued my MCU. This shall result in error_n pin to  in a de-asserted state ( error_n goes high) . All internal error reported from sensor also should be in a de-asserted state.   The internal error reported from sensor status is tracked through a FIT status register. At the and of test all enabled FIT status register shall be set indicating a successful completion of fault injection test. 
	* The reset error must be asserted by MCU for a minimum duration of one micro second
	*/
    uint32 IsmOsmTestResetError: 1;        /*## attribute IsmOsmTestResetError */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: mc_clk_fit_test_en
	* Description: This bit is used to initiate MCU FIT test on mc_xo_no_clk_error_flag.
	* During the regular FIT test, the effect of mc_xo_no_error_flag is not analysed. To test the proper working of mc_xo_no_error_flag this test shall be initiated by MCU seperately.
	* This function shall be used  by MCU to test the functional safety logic related to no clock error from Dolphin.  To test this feature it is recommended to mask other errors  within Dolphin  or make sure that no error is present in Dolphin when conducting this test
	* 0: Release force_error on xo no clock  ( forced error condition is removed)
	* 1: Initiate force error on mc_xo_no_error_flag error is propagated to error_n pin) no action is taken with Dolphin .
	*/
    uint32 McClkFitTestEn: 1;        /*## attribute McClkFitTestEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ISM_test_CurrentState
	* Description: Reflect the current state of the ISM during a FIT test
	* 00: IDLE
	* 01 : ISM in force error state
	* 10: ISM in reset error state
	* 11: ISM test complete
	*/
    uint32 IsmTestCurrentstate: 2;        /*## attribute IsmTestCurrentstate */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 5;        /*## attribute Reserved4 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_IsmFitTestRegBits_t;
    /**
* Nxp_Tef810x_Mod18_MASTER_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: master_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_to_mcu
	* Description: Combined supply low error from all local supply monitoring
	* 0: No error
	* 1: Error
	*/
    uint32 SupplyLowErrorToMcu: 1;        /*## attribute SupplyLowErrorToMcu */
   /**
	* BitsName: global_ldo_1v8_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1HighErrorFlagToMcu */
   /**
	* BitsName: chirp_dig_lock_step_error_flag
	* Description: Stuck at issue in Chirp digital (lock step mode)
	* 0: No error
	* 1: Lock step out of sync possibly due to a stuck at error
	*/
    uint32 ChirpDigLockStepErrorFlag: 1;        /*## attribute ChirpDigLockStepErrorFlag */
   /**
	* BitsName: unlock_error_flag_chirp_to_mcu
	* Description: Chirp  PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 UnlockErrorFlagChirpToMcu: 1;        /*## attribute UnlockErrorFlagChirpToMcu */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_to_mcu
	* Description: Chirp O/P frequency not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 VcoFreq480ErrorFlagChirpToMcu: 1;        /*## attribute VcoFreq480ErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vco_level_fs_error_flag_to_mcu
	* Description: Chirp VCO level error
	* 0: No error
	* 1: VCO O/P level not OK
	*/
    uint32 ChirpVcoLevelFsErrorFlagToMcu: 1;        /*## attribute ChirpVcoLevelFsErrorFlagToMcu */
   /**
	* BitsName: adc_cal_error_flag_persistent_to_mcu
	* Description: Main ADC calibration out of Sync ( in one of the  ADC unit)
	* 0: No error
	* 1: Calibration issue in main ADC
	*/
    uint32 AdcCalErrorFlagPersistentToMcu: 1;        /*## attribute AdcCalErrorFlagPersistentToMcu */
   /**
	* BitsName: mc_pll_level_error_flag_to_mcu
	* Description: The main 4.8GHz PLL O/P level not OK i.e either too low or too high
	* 0: No error
	* 1: Pll level not OK
	*/
    uint32 McPllLevelErrorFlagToMcu: 1;        /*## attribute McPllLevelErrorFlagToMcu */
   /**
	* BitsName: mc_pll_lock_error_flag_to_mcu
	* Description: The main 4.8GHz PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 McPllLockErrorFlagToMcu: 1;        /*## attribute McPllLockErrorFlagToMcu */
   /**
	* BitsName: mc_pll_dig_freq_error_flag_to_mcu
	* Description: The O/P frequency from main 4.8GHz PLL ( 600/480 MHz) not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 McPllDigFreqErrorFlagToMcu: 1;        /*## attribute McPllDigFreqErrorFlagToMcu */
   /**
	* BitsName: bb_error_flag_interface_to_mcu
	* Description: RF Ball break detected  in   LO interface
	* 0: No error
	* 1: Ball break error
	*/
    uint32 BbErrorFlagInterfaceToMcu: 1;        /*## attribute BbErrorFlagInterfaceToMcu */
   /**
	* BitsName: tx_rf_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from one of TX unit PA
	* 0: No error
	* 1: TX PA error
	*/
    uint32 TxRfLevelFsErrorFlagToMcu: 1;        /*## attribute TxRfLevelFsErrorFlagToMcu */
   /**
	* BitsName: tx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the TX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 TxBbErrorFlagToMcu: 1;        /*## attribute TxBbErrorFlagToMcu */
   /**
	* BitsName: rx_lo_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from RX LO
	* 0: No error
	* 1: LO FS error
	*/
    uint32 RxLoLevelFsErrorFlagToMcu: 1;        /*## attribute RxLoLevelFsErrorFlagToMcu */
   /**
	* BitsName: rx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the RX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 RxBbErrorFlagToMcu: 1;        /*## attribute RxBbErrorFlagToMcu */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SUPPLY_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: supply_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_flag_tx1_1v8
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8: 1;        /*## attribute SupplyLowErrorFlagTx11V8 */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8
	* Description: TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8: 1;        /*## attribute SupplyLowErrorFlagTx21V8 */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8
	* Description: TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8: 1;        /*## attribute SupplyLowErrorFlagTx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: RX1  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: RX2  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: RX3  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: RX4  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: RX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: RX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: RX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: RX4  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Master clock  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8
	* Description: ADC12  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagAdc121V8: 1;        /*## attribute SupplyLowErrorFlagAdc121V8 */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8
	* Description: ADC34  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagAdc341V8: 1;        /*## attribute SupplyLowErrorFlagAdc341V8 */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: LO interface  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8
	* Description: SSB mode supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8 */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8
	* Description: Global bias supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8 */
   /**
	* BitsName: supply_low_error_flag_ser_1v1
	* Description: Serializer 1v1 (CIF & LVDS) supply low error. Valid only if CIF or LVDS function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSer1V1: 1;        /*## attribute SupplyLowErrorFlagSer1V1 */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1
	* Description: Serializer 1v1 (CSI2) supply low error. Valid only CSI2 function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagCsi21V1: 1;        /*## attribute SupplyLowErrorFlagCsi21V1 */
   /**
	* BitsName: supply_low_error_flag_ser_1v8
	* Description: Serializer 1v8 (CIF & LVDS) supply low error. Valid only if CIF or LVDS function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSer1V8: 1;        /*## attribute SupplyLowErrorFlagSer1V8 */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8
	* Description: Chirp PLL 1v8 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8 */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8
	* Description: Chirp VCO 1v8 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8 */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1
	* Description: Chirp digital 1v1 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1 */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8
	* Description: Global 1V8 LDO supply low error 
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8
	* Description: Global 1V8 LDO supply high error 
	* 0: Supply OK
	* 1: latched Supply high error
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8 */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1
	* Description: Global 1V1 LDO supply low error 
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1
	* Description: Global 1V1 LDO supply high error 
	* 0: Supply OK
	* 1: latched Supply high error
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_TX_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: tx_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: tx1_bb_error_raw
	* Description: Functional safety error flag
	* 
	* TX1  RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1BbErrorRaw: 1;        /*## attribute Tx1BbErrorRaw */
   /**
	* BitsName: tx2_bb_error_raw
	* Description: Functional safety error flag
	* 
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2BbErrorRaw: 1;        /*## attribute Tx2BbErrorRaw */
   /**
	* BitsName: tx3_bb_error_raw
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3BbErrorRaw: 1;        /*## attribute Tx3BbErrorRaw */
   /**
	* BitsName: tx1_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1TempErrorRaw: 1;        /*## attribute Tx1TempErrorRaw */
   /**
	* BitsName: tx2_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2TempErrorRaw: 1;        /*## attribute Tx2TempErrorRaw */
   /**
	* BitsName: tx3_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3TempErrorRaw: 1;        /*## attribute Tx3TempErrorRaw */
   /**
	* BitsName: tx1_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX1  TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelFsErrorRaw: 1;        /*## attribute Tx1RfLevelFsErrorRaw */
   /**
	* BitsName: tx2_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX2 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelFsErrorRaw: 1;        /*## attribute Tx2RfLevelFsErrorRaw */
   /**
	* BitsName: tx3_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX3 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelFsErrorRaw: 1;        /*## attribute Tx3RfLevelFsErrorRaw */
   /**
	* BitsName: tx1_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelLowErrorRaw: 1;        /*## attribute Tx1RfLevelLowErrorRaw */
   /**
	* BitsName: tx2_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelLowErrorRaw: 1;        /*## attribute Tx2RfLevelLowErrorRaw */
   /**
	* BitsName: tx3_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelLowErrorRaw: 1;        /*## attribute Tx3RfLevelLowErrorRaw */
   /**
	* BitsName: tx1_rf_level_high_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelHighErrorRaw: 1;        /*## attribute Tx1RfLevelHighErrorRaw */
   /**
	* BitsName: tx2_rf_level_high_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelHighErrorRaw: 1;        /*## attribute Tx2RfLevelHighErrorRaw */
   /**
	* BitsName: tx3_rf_level_high_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX3  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelHighErrorRaw: 1;        /*## attribute Tx3RfLevelHighErrorRaw */
   /**
	* BitsName: tx1_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX1  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx1RfReliabilityLevelErrorRaw */
   /**
	* BitsName: tx2_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX2  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx2RfReliabilityLevelErrorRaw */
   /**
	* BitsName: tx3_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx3RfReliabilityLevelErrorRaw */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error_raw
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx11V8ErrorRaw */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error flag
	* 
	* TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx21V8ErrorRaw */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error_raw
	* Description: Functional safety error flag
	* 
	* TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx31V8ErrorRaw */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_TxErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RX_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: rx_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_rx1
	* Description: Functional safety error flag
	* 
	* RX1 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx1: 1;        /*## attribute BbErrorFlagRx1 */
   /**
	* BitsName: bb_error_flag_rx2
	* Description: Functional safety error flag
	* 
	* RX2 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx2: 1;        /*## attribute BbErrorFlagRx2 */
   /**
	* BitsName: bb_error_flag_rx3
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx3: 1;        /*## attribute BbErrorFlagRx3 */
   /**
	* BitsName: bb_error_flag_rx4
	* Description: Functional safety error flag
	* 
	* RX4 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx4: 1;        /*## attribute BbErrorFlagRx4 */
   /**
	* BitsName: lo_min_error_flag_rx1
	* Description: Functional safety error flag
	* 
	* RX1 LO level too low
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx1: 1;        /*## attribute LoMinErrorFlagRx1 */
   /**
	* BitsName: lo_min_error_flag_rx2
	* Description: Functional safety error flag
	* 
	* RX2 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx2: 1;        /*## attribute LoMinErrorFlagRx2 */
   /**
	* BitsName: lo_min_error_flag_rx3
	* Description: Functional safety error flag
	* 
	* RX3 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx3: 1;        /*## attribute LoMinErrorFlagRx3 */
   /**
	* BitsName: lo_min_error_flag_rx4
	* Description: Functional safety error flag
	* 
	* Functional safety error in receiver
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx4: 1;        /*## attribute LoMinErrorFlagRx4 */
   /**
	* BitsName: lo_low_error_flag_rx1
	* Description: Status monitoring error flag
	* 
	* Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. RX1  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx1: 1;        /*## attribute LoLowErrorFlagRx1 */
   /**
	* BitsName: lo_low_error_flag_rx2
	* Description: Status monitoring error flag
	* 
	* RX2 Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx2: 1;        /*## attribute LoLowErrorFlagRx2 */
   /**
	* BitsName: lo_low_error_flag_rx3
	* Description: Status monitoring error flag
	* 
	* RX3 Lo level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx3: 1;        /*## attribute LoLowErrorFlagRx3 */
   /**
	* BitsName: lo_low_error_flag_rx4
	* Description: Status monitoring error flag
	* 
	* RX4 LO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level low
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4: 1;        /*## attribute LoLowErrorFlagRx4 */
   /**
	* BitsName: lo_high_error_flag_rx1
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX1  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx1: 1;        /*## attribute LoHighErrorFlagRx1 */
   /**
	* BitsName: lo_high_error_flag_rx2
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx2: 1;        /*## attribute LoHighErrorFlagRx2 */
   /**
	* BitsName: lo_high_error_flag_rx3
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx3: 1;        /*## attribute LoHighErrorFlagRx3 */
   /**
	* BitsName: lo_high_error_flag_rx4
	* Description: Status monitoring error flag
	* 
	*  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx4: 1;        /*## attribute LoHighErrorFlagRx4 */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX1  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX2 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX3  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX4 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RxErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_CHIRP_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: chirp_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp digital portion
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. Indicate a functional safety error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 MaxTempErrorFlagChirpSync: 1;        /*## attribute MaxTempErrorFlagChirpSync */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level  reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* 
	* Functional safety error in Chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter op
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VcoFreq480ErrorFlagChirpSync: 1;        /*## attribute VcoFreq480ErrorFlagChirpSync */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v1) to digital logic error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to VCO error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to PLL error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_MC_LO_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: mc_lo_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: mc_freq_calib_error_flag
	* Description: MC PLL calibration error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McFreqCalibErrorFlag: 1;        /*## attribute McFreqCalibErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: PLL level  is too low or too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Pll in un lock condition
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: MC digital O.P frequency not in range
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Supply error form MC (1V8)
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: RF connectivity issues in LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: Supply low error from LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 13;        /*## attribute Reserved2 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: adc_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: adc1_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1CalErrorFlagPersistent: 1;        /*## attribute Adc1CalErrorFlagPersistent */
   /**
	* BitsName: adc2_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2CalErrorFlagPersistent: 1;        /*## attribute Adc2CalErrorFlagPersistent */
   /**
	* BitsName: adc3_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3CalErrorFlagPersistent: 1;        /*## attribute Adc3CalErrorFlagPersistent */
   /**
	* BitsName: adc4_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4CalErrorFlagPersistent: 1;        /*## attribute Adc4CalErrorFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagPersistent: 1;        /*## attribute Adc1NearClippingFlagPersistent */
   /**
	* BitsName: adc2_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagPersistent: 1;        /*## attribute Adc2NearClippingFlagPersistent */
   /**
	* BitsName: adc3_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagPersistent: 1;        /*## attribute Adc3NearClippingFlagPersistent */
   /**
	* BitsName: adc4_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagPersistent: 1;        /*## attribute Adc4NearClippingFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlag: 1;        /*## attribute Adc1NearClippingFlag */
   /**
	* BitsName: adc2_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlag: 1;        /*## attribute Adc2NearClippingFlag */
   /**
	* BitsName: adc3_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlag: 1;        /*## attribute Adc3NearClippingFlag */
   /**
	* BitsName: adc4_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlag: 1;        /*## attribute Adc4NearClippingFlag */
   /**
	* BitsName: adc1_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagPersistent: 1;        /*## attribute Adc1ClippingFlagPersistent */
   /**
	* BitsName: adc2_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagPersistent: 1;        /*## attribute Adc2ClippingFlagPersistent */
   /**
	* BitsName: adc3_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagPersistent: 1;        /*## attribute Adc3ClippingFlagPersistent */
   /**
	* BitsName: adc4_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagPersistent: 1;        /*## attribute Adc4ClippingFlagPersistent */
   /**
	* BitsName: adc1_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	*  0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlag: 1;        /*## attribute Adc1ClippingFlag */
   /**
	* BitsName: adc2_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlag: 1;        /*## attribute Adc2ClippingFlag */
   /**
	* BitsName: adc3_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlag: 1;        /*## attribute Adc3ClippingFlag */
   /**
	* BitsName: adc4_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlag: 1;        /*## attribute Adc4ClippingFlag */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingFlagPersistent: 1;        /*## attribute Adc1HardClippingFlagPersistent */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingFlagPersistent: 1;        /*## attribute Adc2HardClippingFlagPersistent */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingFlagPersistent: 1;        /*## attribute Adc3HardClippingFlagPersistent */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingFlagPersistent: 1;        /*## attribute Adc4HardClippingFlagPersistent */
   /**
	* BitsName: adc1_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingErrorFlag: 1;        /*## attribute Adc1HardClippingErrorFlag */
   /**
	* BitsName: adc2_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingErrorFlag: 1;        /*## attribute Adc2HardClippingErrorFlag */
   /**
	* BitsName: adc3_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingErrorFlag: 1;        /*## attribute Adc3HardClippingErrorFlag */
   /**
	* BitsName: adc4_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingErrorFlag: 1;        /*## attribute Adc4HardClippingErrorFlag */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC12
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc121V8: 1;        /*## attribute SupplyLowErrorFlagAdc121V8 */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC34
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc341V8: 1;        /*## attribute SupplyLowErrorFlagAdc341V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RF_POWER_DOWN_ERROR_FLAG_RAW_STATUSBits_t
* RegisterName: rf_power_down_error_flag_raw_status
* 
* AddressRange: 0xREAD - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability error in RX1 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability error in RX2 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability error in RX3 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability error in RX4 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: rf_max_error_flag_tx1
	* Description: Reliability error in TX1 PA
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 RfMaxErrorFlagTx1: 1;        /*## attribute RfMaxErrorFlagTx1 */
   /**
	* BitsName: rf_max_error_flag_tx2
	* Description: Reliability error in TX32PA
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 RfMaxErrorFlagTx2: 1;        /*## attribute RfMaxErrorFlagTx2 */
   /**
	* BitsName: rf_max_error_flag_tx3
	* Description: Reliability error in TX3 PA
	* 0: no error
	* 1: error reported from sensor.
	*/
    uint32 RfMaxErrorFlagTx3: 1;        /*## attribute RfMaxErrorFlagTx3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 19;        /*## attribute Reserved4 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_MASTER_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: master_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_to_mcu
	* Description: Combined supply low error from all local supply monitoring ( supply low indication primarily cover pin failures or local LDO failures, barring chirp and master clock and SSB mod) 
	* 0: No error
	* 1: Error
	*/
    uint32 SupplyLowErrorToMcu: 1;        /*## attribute SupplyLowErrorToMcu */
   /**
	* BitsName: global_ldo_1v8_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1HighErrorFlagToMcu */
   /**
	* BitsName: chirp_dig_lock_step_error_flag
	* Description: Stuck at issue in Chirp digital (lock step mode)
	* 0: No error
	* 1: Lock step out of sync possibly due to a stuck at error
	*/
    uint32 ChirpDigLockStepErrorFlag: 1;        /*## attribute ChirpDigLockStepErrorFlag */
   /**
	* BitsName: unlock_error_flag_chirp_to_mcu
	* Description: Chirp  PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 UnlockErrorFlagChirpToMcu: 1;        /*## attribute UnlockErrorFlagChirpToMcu */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_to_mcu
	* Description: Chirp O/P frequency not OK ( freq deviation in chirp digital portion) 
	* 0: No error
	* 1: Frequency error
	*/
    uint32 VcoFreq480ErrorFlagChirpToMcu: 1;        /*## attribute VcoFreq480ErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vco_level_fs_error_flag_to_mcu
	* Description: Chirp VCO level error ( Chirp VCO level is too low) 
	* 0: No error
	* 1: VCO O/P level not OK
	*/
    uint32 ChirpVcoLevelFsErrorFlagToMcu: 1;        /*## attribute ChirpVcoLevelFsErrorFlagToMcu */
   /**
	* BitsName: adc_cal_error_flag_persistent_to_mcu
	* Description: Main ADC calibration out of Sync ( calibaration issue in ADC)
	* 0: No error
	* 1: Calibration issue in main ADC
	*/
    uint32 AdcCalErrorFlagPersistentToMcu: 1;        /*## attribute AdcCalErrorFlagPersistentToMcu */
   /**
	* BitsName: mc_pll_level_error_flag_to_mcu
	* Description: The main 4.8GHz PLL O/P level not OK ( PLL /VCO level is too low or too high) 
	* 0: No error
	* 1: Pll level not OK
	*/
    uint32 McPllLevelErrorFlagToMcu: 1;        /*## attribute McPllLevelErrorFlagToMcu */
   /**
	* BitsName: mc_pll_lock_error_flag_to_mcu
	* Description: The main 4.8GHz PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 McPllLockErrorFlagToMcu: 1;        /*## attribute McPllLockErrorFlagToMcu */
   /**
	* BitsName: mc_pll_dig_freq_error_flag_to_mcu
	* Description: The O/P frequency from main 4.8GHz PLL ( 600/480 MHz) not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 McPllDigFreqErrorFlagToMcu: 1;        /*## attribute McPllDigFreqErrorFlagToMcu */
   /**
	* BitsName: bb_error_flag_interface_to_mcu
	* Description: RF Ball break detected  in one of the  LO interface
	* 0: No error
	* 1: Ball break error
	*/
    uint32 BbErrorFlagInterfaceToMcu: 1;        /*## attribute BbErrorFlagInterfaceToMcu */
   /**
	* BitsName: tx_rf_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from TX PA (TX PA level is too low) 
	* 0: No error
	* 1: TX PA error
	*/
    uint32 TxRfLevelFsErrorFlagToMcu: 1;        /*## attribute TxRfLevelFsErrorFlagToMcu */
   /**
	* BitsName: tx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the TX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 TxBbErrorFlagToMcu: 1;        /*## attribute TxBbErrorFlagToMcu */
   /**
	* BitsName: rx_lo_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from RX LO ( RX LO level too low) 
	* 0: No error
	* 1: LO FS error
	*/
    uint32 RxLoLevelFsErrorFlagToMcu: 1;        /*## attribute RxLoLevelFsErrorFlagToMcu */
   /**
	* BitsName: rx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the RX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 RxBbErrorFlagToMcu: 1;        /*## attribute RxBbErrorFlagToMcu */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SUPPLY_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: supply_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_flag_tx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx1Sync: 1;        /*## attribute SupplyLowErrorFlagTx1Sync */
   /**
	* BitsName: supply_low_error_flag_tx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx2Sync: 1;        /*## attribute SupplyLowErrorFlagTx2Sync */
   /**
	* BitsName: supply_low_error_flag_tx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx3Sync: 1;        /*## attribute SupplyLowErrorFlagTx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx4_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx4_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx4Sync */
   /**
	* BitsName: mc_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Mc1V8SupplyLowErrorFlagSync: 1;        /*## attribute Mc1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_low_error_flag_adc12_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagAdc12Sync: 1;        /*## attribute SupplyLowErrorFlagAdc12Sync */
   /**
	* BitsName: supply_low_error_flag_adc34_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagAdc34Sync: 1;        /*## attribute SupplyLowErrorFlagAdc34Sync */
   /**
	* BitsName: supply_low_error_flag_interface_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagInterfaceSync: 1;        /*## attribute SupplyLowErrorFlagInterfaceSync */
   /**
	* BitsName: ssb_mod_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SsbMod1V8SupplyLowErrorFlagSync: 1;        /*## attribute SsbMod1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: global_bias_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalBiasSupplyLowErrorFlagSync: 1;        /*## attribute GlobalBiasSupplyLowErrorFlagSync */
   /**
	* BitsName: ser_1v1_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Ser1V1SupplyLowErrorFlagSync: 1;        /*## attribute Ser1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: csi2_1v1_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Csi21V1LowErrorFlagSync: 1;        /*## attribute Csi21V1LowErrorFlagSync */
   /**
	* BitsName: ser_1v8_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Ser1V8LowErrorFlagSync: 1;        /*## attribute Ser1V8LowErrorFlagSync */
   /**
	* BitsName: supply_pll_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyPllErrorFlagChirpSync: 1;        /*## attribute SupplyPllErrorFlagChirpSync */
   /**
	* BitsName: supply_vco_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyVcoErrorFlagChirpSync: 1;        /*## attribute SupplyVcoErrorFlagChirpSync */
   /**
	* BitsName: supply_dig_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyDigErrorFlagChirpSync: 1;        /*## attribute SupplyDigErrorFlagChirpSync */
   /**
	* BitsName: global_ldo_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V8SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_high_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V8SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V1SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_high_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V1SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyHighErrorFlagSync */
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
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_TX_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: tx_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: tx1_bb_error
	* Description: Functional safety error flag
	* 
	* TX1  RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1BbError: 1;        /*## attribute Tx1BbError */
   /**
	* BitsName: tx2_bb_error
	* Description: Functional safety error flag
	* 
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2BbError: 1;        /*## attribute Tx2BbError */
   /**
	* BitsName: tx3_bb_error
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3BbError: 1;        /*## attribute Tx3BbError */
   /**
	* BitsName: tx1_temp_error
	* Description: Status monitoring error flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1TempError: 1;        /*## attribute Tx1TempError */
   /**
	* BitsName: tx2_temp_error
	* Description: Status monitoring error flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2TempError: 1;        /*## attribute Tx2TempError */
   /**
	* BitsName: tx3_temp_error
	* Description: Status monitoring error flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3TempError: 1;        /*## attribute Tx3TempError */
   /**
	* BitsName: tx1_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX1  TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelFsError: 1;        /*## attribute Tx1RfLevelFsError */
   /**
	* BitsName: tx2_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX2 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelFsError: 1;        /*## attribute Tx2RfLevelFsError */
   /**
	* BitsName: tx3_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX3. TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelFsError: 1;        /*## attribute Tx3RfLevelFsError */
   /**
	* BitsName: tx1_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelLowError: 1;        /*## attribute Tx1RfLevelLowError */
   /**
	* BitsName: tx2_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelLowError: 1;        /*## attribute Tx2RfLevelLowError */
   /**
	* BitsName: tx3_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelLowError: 1;        /*## attribute Tx3RfLevelLowError */
   /**
	* BitsName: tx1_rf_level_high_error
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelHighError: 1;        /*## attribute Tx1RfLevelHighError */
   /**
	* BitsName: tx2_rf_level_high_error
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelHighError: 1;        /*## attribute Tx2RfLevelHighError */
   /**
	* BitsName: tx3_rf_level_high_error
	* Description: Reliability  monitoring error flag
	* 
	* TX3  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelHighError: 1;        /*## attribute Tx3RfLevelHighError */
   /**
	* BitsName: tx1_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX1  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfReliabilityLevelError: 1;        /*## attribute Tx1RfReliabilityLevelError */
   /**
	* BitsName: tx2_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX2  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfReliabilityLevelError: 1;        /*## attribute Tx2RfReliabilityLevelError */
   /**
	* BitsName: tx3_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfReliabilityLevelError: 1;        /*## attribute Tx3RfReliabilityLevelError */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8Error: 1;        /*## attribute SupplyLowErrorFlagTx11V8Error */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error
	* Description: Functional safety error flag
	* 
	* Functional safety error flag
	* 
	* TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8Error: 1;        /*## attribute SupplyLowErrorFlagTx21V8Error */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error
	* Description: Functional safety error flag
	* 
	* TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8Error: 1;        /*## attribute SupplyLowErrorFlagTx31V8Error */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RX_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: rx_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x070
* ResetValue: 0x00000074
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_rx1_masked
	* Description: Functional safety error flag
	* 
	* RX1 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx1Masked: 1;        /*## attribute BbErrorFlagRx1Masked */
   /**
	* BitsName: bb_error_flag_rx2_masked
	* Description: Functional safety error flag
	* 
	* RX2 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx2Masked: 1;        /*## attribute BbErrorFlagRx2Masked */
   /**
	* BitsName: bb_error_flag_rx3_masked
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx3Masked: 1;        /*## attribute BbErrorFlagRx3Masked */
   /**
	* BitsName: bb_error_flag_rx4_masked
	* Description: Functional safety error flag
	* 
	* RX4 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx4Masked: 1;        /*## attribute BbErrorFlagRx4Masked */
   /**
	* BitsName: lo_min_error_flag_rx1_masked
	* Description: Functional safety error flag
	* 
	* RX1 LO level too low
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx1Masked: 1;        /*## attribute LoMinErrorFlagRx1Masked */
   /**
	* BitsName: lo_min_error_flag_rx2_masked
	* Description: Functional safety error flag
	* 
	* RX2 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx2Masked: 1;        /*## attribute LoMinErrorFlagRx2Masked */
   /**
	* BitsName: lo_min_error_flag_rx3_masked
	* Description: Functional safety error flag
	* 
	* RX3 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx3Masked: 1;        /*## attribute LoMinErrorFlagRx3Masked */
   /**
	* BitsName: lo_min_error_flag_rx4_masked
	* Description: Functional safety error flag
	* 
	* Functional safety error in receiver
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx4Masked: 1;        /*## attribute LoMinErrorFlagRx4Masked */
   /**
	* BitsName: lo_low_error_flag_rx1_masked
	* Description: Status monitoring error flag
	* 
	* Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. RX1  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx1Masked: 1;        /*## attribute LoLowErrorFlagRx1Masked */
   /**
	* BitsName: lo_low_error_flag_rx2_masked
	* Description: Status monitoring error flag
	* 
	* RX2 Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx2Masked: 1;        /*## attribute LoLowErrorFlagRx2Masked */
   /**
	* BitsName: lo_low_error_flag_rx3_masked
	* Description: Status monitoring error flag
	* 
	* RX3 Lo level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx3Masked: 1;        /*## attribute LoLowErrorFlagRx3Masked */
   /**
	* BitsName: lo_low_error_flag_rx4_masked
	* Description: Status monitoring error flag
	* 
	* RX4 LO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level low
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4Masked: 1;        /*## attribute LoLowErrorFlagRx4Masked */
   /**
	* BitsName: lo_high_error_flag_rx1_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX1  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx1Masked: 1;        /*## attribute LoHighErrorFlagRx1Masked */
   /**
	* BitsName: lo_high_error_flag_rx2_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx2Masked: 1;        /*## attribute LoHighErrorFlagRx2Masked */
   /**
	* BitsName: lo_high_error_flag_rx3_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx3Masked: 1;        /*## attribute LoHighErrorFlagRx3Masked */
   /**
	* BitsName: lo_high_error_flag_rx4_masked
	* Description: Status monitoring error flag
	* 
	*  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx4Masked: 1;        /*## attribute LoHighErrorFlagRx4Masked */
   /**
	* BitsName: lo_max_error_flag_rx1_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX1  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1Masked: 1;        /*## attribute LoMaxErrorFlagRx1Masked */
   /**
	* BitsName: lo_max_error_flag_rx2_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX2 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2Masked: 1;        /*## attribute LoMaxErrorFlagRx2Masked */
   /**
	* BitsName: lo_max_error_flag_rx3_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX3  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3Masked: 1;        /*## attribute LoMaxErrorFlagRx3Masked */
   /**
	* BitsName: lo_max_error_flag_rx4_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX14 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4Masked: 1;        /*## attribute LoMaxErrorFlagRx4Masked */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx11V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx21V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx31V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx41V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx11V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx21V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx31V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx41V8Masked */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_CHIRP_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: chirp_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x074
* ResetValue: 0x00000078
*/
typedef struct  {
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp digital portion
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. Indicate a functional safety error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp
	* Description: Status monitoring error flag
	* 
	* Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 MaxTempErrorFlagChirp: 1;        /*## attribute MaxTempErrorFlagChirp */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level  reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* 
	* Functional safety error in Chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter op
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VcoFreq480ErrorFlagChirp: 1;        /*## attribute VcoFreq480ErrorFlagChirp */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v1) to digital logic error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to VCO error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to PLL error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_MC_LO_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: mc_lo_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x078
* ResetValue: 0x0000007C
*/
typedef struct  {
   /**
	* BitsName: mc_pll_freq_error_flag
	* Description: MC PLL calibration error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllFreqErrorFlag: 1;        /*## attribute McPllFreqErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: PLL level  is too low or too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Pll in un lock condition
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: MC digital O.P frequency not in range
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Supply error form MC (1V8)
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: RF connectivity issues in LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: Supply low error from LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 13;        /*## attribute Reserved2 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: adc_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x07C
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: adc1_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1CalErrorFlagPersistentMasked: 1;        /*## attribute Adc1CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc2_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2CalErrorFlagPersistentMasked: 1;        /*## attribute Adc2CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc3_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3CalErrorFlagPersistentMasked: 1;        /*## attribute Adc3CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc4_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4CalErrorFlagPersistentMasked: 1;        /*## attribute Adc4CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc1_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagPersistentMasked: 1;        /*## attribute Adc1NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagPersistentMasked: 1;        /*## attribute Adc2NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagPersistentMasked: 1;        /*## attribute Adc3NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagPersistentMasked: 1;        /*## attribute Adc4NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagMasked: 1;        /*## attribute Adc1NearClippingFlagMasked */
   /**
	* BitsName: adc2_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagMasked: 1;        /*## attribute Adc2NearClippingFlagMasked */
   /**
	* BitsName: adc3_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagMasked: 1;        /*## attribute Adc3NearClippingFlagMasked */
   /**
	* BitsName: adc4_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagMasked: 1;        /*## attribute Adc4NearClippingFlagMasked */
   /**
	* BitsName: adc1_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagPersistentMasked: 1;        /*## attribute Adc1ClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagPersistentMasked: 1;        /*## attribute Adc2ClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagPersistentMasked: 1;        /*## attribute Adc3ClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagPersistentMasked: 1;        /*## attribute Adc4ClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	*  0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagMasked: 1;        /*## attribute Adc1ClippingFlagMasked */
   /**
	* BitsName: adc2_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagMasked: 1;        /*## attribute Adc2ClippingFlagMasked */
   /**
	* BitsName: adc3_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagMasked: 1;        /*## attribute Adc3ClippingFlagMasked */
   /**
	* BitsName: adc4_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagMasked: 1;        /*## attribute Adc4ClippingFlagMasked */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingFlagPersistentMasked: 1;        /*## attribute Adc1HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingFlagPersistentMasked: 1;        /*## attribute Adc2HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingFlagPersistentMasked: 1;        /*## attribute Adc3HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingFlagPersistentMasked: 1;        /*## attribute Adc4HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingErrorFlagMasked: 1;        /*## attribute Adc1HardClippingErrorFlagMasked */
   /**
	* BitsName: adc2_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingErrorFlagMasked: 1;        /*## attribute Adc2HardClippingErrorFlagMasked */
   /**
	* BitsName: adc3_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingErrorFlagMasked: 1;        /*## attribute Adc3HardClippingErrorFlagMasked */
   /**
	* BitsName: adc4_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingErrorFlagMasked: 1;        /*## attribute Adc4HardClippingErrorFlagMasked */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_masked
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC12
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc121V8Masked: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Masked */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_masked
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC34
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc341V8Masked: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Masked */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RF_POWER_DOWN_ERROR_FLAG_MASKED_STATUSBits_t
* RegisterName: rf_power_down_error_flag_masked_status
* 
* AddressRange: 0xREAD - 0x080
* ResetValue: 0x00000084
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability issue in Chirp
	* 0: No error
	* 1: Error
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability issue in RX1
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability issue in RX2
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability issue in RX3
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability issue in RX4
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: rf_max_error_flag_tx1
	* Description: Reliability issue in TX1
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx1: 1;        /*## attribute RfMaxErrorFlagTx1 */
   /**
	* BitsName: rf_max_error_flag_tx2
	* Description: Reliability issue in TX2
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx2: 1;        /*## attribute RfMaxErrorFlagTx2 */
   /**
	* BitsName: rf_max_error_flag_tx3
	* Description: Reliability issue in TX3
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx3: 1;        /*## attribute RfMaxErrorFlagTx3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 19;        /*## attribute Reserved4 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_SUPPLY_REGBits_t
* RegisterName: fit_status_supply_reg
* 
* AddressRange: 0xREAD - 0x084
* ResetValue: 0x00000088
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_flag_tx1_sync
	* Description: TX1 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx1Sync: 1;        /*## attribute SupplyLowErrorFlagTx1Sync */
   /**
	* BitsName: supply_low_error_flag_tx2_sync
	* Description: TX2 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx2Sync: 1;        /*## attribute SupplyLowErrorFlagTx2Sync */
   /**
	* BitsName: supply_low_error_flag_tx3_sync
	* Description: TX3 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx3Sync: 1;        /*## attribute SupplyLowErrorFlagTx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx1_sync
	* Description: RX1 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx2_sync
	* Description: RX2 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx3_sync
	* Description: RX3 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx4_sync
	* Description: RX4 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx1_sync
	* Description: RX1 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx2_sync
	* Description: RX2 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx3_sync
	* Description: RX3 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx4_sync
	* Description: RX4 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx4Sync */
   /**
	* BitsName: mc_1v8_supply_low_error_flag_sync
	* Description: Master controller supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Mc1V8SupplyLowErrorFlagSync: 1;        /*## attribute Mc1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_low_error_flag_adc12_sync
	* Description: ADC 12 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc12Sync: 1;        /*## attribute SupplyLowErrorFlagAdc12Sync */
   /**
	* BitsName: supply_low_error_flag_adc34_sync
	* Description: ADC34 Supply low sensor  status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc34Sync: 1;        /*## attribute SupplyLowErrorFlagAdc34Sync */
   /**
	* BitsName: supply_low_error_flag_interface_sync
	* Description: LO interface Supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagInterfaceSync: 1;        /*## attribute SupplyLowErrorFlagInterfaceSync */
   /**
	* BitsName: ssb_mod_1v8_supply_low_error_flag_sync
	* Description: SSB mod supply low sensor error status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SsbMod1V8SupplyLowErrorFlagSync: 1;        /*## attribute SsbMod1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: global_bias_supply_low_error_flag_sync
	* Description: Global bias supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalBiasSupplyLowErrorFlagSync: 1;        /*## attribute GlobalBiasSupplyLowErrorFlagSync */
   /**
	* BitsName: ser_1v1_supply_low_error_flag_sync
	* Description: Serializer digital   supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Ser1V1SupplyLowErrorFlagSync: 1;        /*## attribute Ser1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: csi2_1v1_low_error_flag_sync
	* Description: Serializer CSI2  supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Csi21V1LowErrorFlagSync: 1;        /*## attribute Csi21V1LowErrorFlagSync */
   /**
	* BitsName: ser_1v8_low_error_flag_sync
	* Description: Serializer 1V8  supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Ser1V8LowErrorFlagSync: 1;        /*## attribute Ser1V8LowErrorFlagSync */
   /**
	* BitsName: supply_pll_error_flag_chirp_sync
	* Description: Chirp PLL   supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyPllErrorFlagChirpSync: 1;        /*## attribute SupplyPllErrorFlagChirpSync */
   /**
	* BitsName: supply_vco_error_flag_chirp_sync
	* Description: Chirp VCO   supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyVcoErrorFlagChirpSync: 1;        /*## attribute SupplyVcoErrorFlagChirpSync */
   /**
	* BitsName: supply_dig_error_flag_chirp_sync
	* Description: Chirp digital  supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyDigErrorFlagChirpSync: 1;        /*## attribute SupplyDigErrorFlagChirpSync */
   /**
	* BitsName: global_ldo_1v8_supply_low_error_flag_sync
	* Description: Global LDO 1V8 supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V8SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_high_error_flag_sync
	* Description: Global LDO 1V8 supply  high sensor  status
	* 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V8SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_low_error_flag_sync
	* Description: Global LDO 1V1 supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V1SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_high_error_flag_sync
	* Description: Global LDO 1V1 supply  high sensor  status
	* 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V1SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyHighErrorFlagSync */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusSupplyRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_TX_REGBits_t
* RegisterName: fit_status_tx_reg
* 
* AddressRange: 0xREAD - 0x088
* ResetValue: 0x0000008C
*/
typedef struct  {
   /**
	* BitsName: tx1_bb_error
	* Description: TX BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1BbError: 1;        /*## attribute Tx1BbError */
   /**
	* BitsName: tx2_bb_error
	* Description: TX2 BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2BbError: 1;        /*## attribute Tx2BbError */
   /**
	* BitsName: tx3_bb_error
	* Description: TX3  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3BbError: 1;        /*## attribute Tx3BbError */
   /**
	* BitsName: tx1_temp_error
	* Description: TX1 temperature sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1TempError: 1;        /*## attribute Tx1TempError */
   /**
	* BitsName: tx2_temp_error
	* Description: TX2 temperature sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2TempError: 1;        /*## attribute Tx2TempError */
   /**
	* BitsName: tx3_temp_error
	* Description: TX3  temperature   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3TempError: 1;        /*## attribute Tx3TempError */
   /**
	* BitsName: tx1_rf_level_fs_error
	* Description: TX1 level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelFsError: 1;        /*## attribute Tx1RfLevelFsError */
   /**
	* BitsName: tx2_rf_level_fs_error
	* Description: TX2  level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelFsError: 1;        /*## attribute Tx2RfLevelFsError */
   /**
	* BitsName: tx3_rf_level_fs_error
	* Description: TX3 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelFsError: 1;        /*## attribute Tx3RfLevelFsError */
   /**
	* BitsName: tx1_rf_level_low_error
	* Description: TX1 level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelLowError: 1;        /*## attribute Tx1RfLevelLowError */
   /**
	* BitsName: tx2_rf_level_low_error
	* Description: TX2  level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelLowError: 1;        /*## attribute Tx2RfLevelLowError */
   /**
	* BitsName: tx3_rf_level_low_error
	* Description: TX3 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelLowError: 1;        /*## attribute Tx3RfLevelLowError */
   /**
	* BitsName: tx1_rf_level_high_error
	* Description: TX1 level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelHighError: 1;        /*## attribute Tx1RfLevelHighError */
   /**
	* BitsName: tx2_rf_level_high_error
	* Description: TX2  level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelHighError: 1;        /*## attribute Tx2RfLevelHighError */
   /**
	* BitsName: tx3_rf_level_high_error
	* Description: TX3 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelHighError: 1;        /*## attribute Tx3RfLevelHighError */
   /**
	* BitsName: tx1_rf_reliability_level_error
	* Description: TX1 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfReliabilityLevelError: 1;        /*## attribute Tx1RfReliabilityLevelError */
   /**
	* BitsName: tx2_rf_reliability_level_error
	* Description: TX2 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfReliabilityLevelError: 1;        /*## attribute Tx2RfReliabilityLevelError */
   /**
	* BitsName: tx3_rf_reliability_level_error
	* Description: TX3 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfReliabilityLevelError: 1;        /*## attribute Tx3RfReliabilityLevelError */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error
	* Description: TX1 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx11V8Error: 1;        /*## attribute SupplyLowErrorFlagTx11V8Error */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error
	* Description: TX2 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx21V8Error: 1;        /*## attribute SupplyLowErrorFlagTx21V8Error */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error
	* Description: TX3 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx31V8Error: 1;        /*## attribute SupplyLowErrorFlagTx31V8Error */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusTxRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_RX_REGBits_t
* RegisterName: fit_status_rx_reg
* 
* AddressRange: 0xREAD - 0x08C
* ResetValue: 0x00000090
*/
typedef struct  {
   /**
	* BitsName: rx1_bb_error
	* Description: RX1  BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1BbError: 1;        /*## attribute Rx1BbError */
   /**
	* BitsName: rx2_bb_error
	* Description: RX2 BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2BbError: 1;        /*## attribute Rx2BbError */
   /**
	* BitsName: rx3_bb_error
	* Description: RX3  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3BbError: 1;        /*## attribute Rx3BbError */
   /**
	* BitsName: rx4_bb_error
	* Description: RX4  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4BbError: 1;        /*## attribute Rx4BbError */
   /**
	* BitsName: rx1_lo_level_fs_error
	* Description: RX1 level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelFsError: 1;        /*## attribute Rx1LoLevelFsError */
   /**
	* BitsName: rx2_lo_level_fs_error
	* Description: RX2  level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelFsError: 1;        /*## attribute Rx2LoLevelFsError */
   /**
	* BitsName: rx3_lo_level_fs_error
	* Description: RX3 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelFsError: 1;        /*## attribute Rx3LoLevelFsError */
   /**
	* BitsName: rx4_lo_level_fs_error
	* Description: RX4 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelFsError: 1;        /*## attribute Rx4LoLevelFsError */
   /**
	* BitsName: rx1_lo_level_low_error
	* Description: RX1 level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelLowError: 1;        /*## attribute Rx1LoLevelLowError */
   /**
	* BitsName: rx2_lo_level_low_error
	* Description: RX2  level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelLowError: 1;        /*## attribute Rx2LoLevelLowError */
   /**
	* BitsName: rx3_lo_level_low_error
	* Description: RX3 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelLowError: 1;        /*## attribute Rx3LoLevelLowError */
   /**
	* BitsName: rx4_lo_level_low_error
	* Description: RX4 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelLowError: 1;        /*## attribute Rx4LoLevelLowError */
   /**
	* BitsName: rx1_lo_level_high_error
	* Description: RX1 level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelHighError: 1;        /*## attribute Rx1LoLevelHighError */
   /**
	* BitsName: rx2_lo_level_high_error
	* Description: RX2  level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelHighError: 1;        /*## attribute Rx2LoLevelHighError */
   /**
	* BitsName: rx3_lo_level_high_error
	* Description: RX3 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelHighError: 1;        /*## attribute Rx3LoLevelHighError */
   /**
	* BitsName: rx4_lo_level_high_error
	* Description: RX4 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelHighError: 1;        /*## attribute Rx4LoLevelHighError */
   /**
	* BitsName: rx1_lo_reliability_level_error
	* Description: RX1 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoReliabilityLevelError: 1;        /*## attribute Rx1LoReliabilityLevelError */
   /**
	* BitsName: rx2_lo_reliability_level_error
	* Description: RX2 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoReliabilityLevelError: 1;        /*## attribute Rx2LoReliabilityLevelError */
   /**
	* BitsName: rx3_lo_reliability_level_error
	* Description: RX3 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoReliabilityLevelError: 1;        /*## attribute Rx3LoReliabilityLevelError */
   /**
	* BitsName: rx4_lo_reliability_level_error
	* Description: RX4 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoReliabilityLevelError: 1;        /*## attribute Rx4LoReliabilityLevelError */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: RX1 supply 1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: RX2 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: RX3 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: RX4 supply 1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: RX1 supply 1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: RX2 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: RX3 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: RX4 supply 1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusRxRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_CHIRP_REGBits_t
* RegisterName: fit_status_chirp_reg
* 
* AddressRange: 0xREAD - 0x090
* ResetValue: 0x00000094
*/
typedef struct  {
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Chirp lock step digital interface status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Chirp PLL un lock sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp_sync
	* Description: Chirp temp sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 MaxTempErrorFlagChirpSync: 1;        /*## attribute MaxTempErrorFlagChirpSync */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Chirp Vtune level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Chirp Vtune level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Chirp level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Chirp level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Chirp functional safety sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Chirp reliability sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp
	* Description: Chirp freq counter sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VcoFreq480ErrorFlagChirp: 1;        /*## attribute VcoFreq480ErrorFlagChirp */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Chirp digital  supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Chirp VCO supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Chirp PLL supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_start, chirp_seq_active, safety_monitoring, window_active is monitored from CC to make sure that the main control signals from chirp is working properly. The value
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusChirpRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_MC_LO_REGBits_t
* RegisterName: fit_status_mc_lo_reg
* 
* AddressRange: 0xREAD - 0x094
* ResetValue: 0x00000098
*/
typedef struct  {
   /**
	* BitsName: mc_pll_freq_error_flag
	* Description: Master clock pll freq error   detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllFreqErrorFlag: 1;        /*## attribute McPllFreqErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: Master clock pll level  detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Master clock pll unlock detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: Master clock freq counter sensor status ( only interface covered). Any variation in Master clock frequency, during chirping is measured and indicated by serialiser throught this flag.
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: master clock supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: LO interface ball break sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: LO interface supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read  
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 13;        /*## attribute Reserved2 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusMcLoRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FIT_STATUS_ADC_REGBits_t
* RegisterName: fit_status_adc_reg
* 
* AddressRange: 0xREAD - 0x098
* ResetValue: 0x0000009C
*/
typedef struct  {
   /**
	* BitsName: adc1_cal_error_flag_persistent
	* Description: ADC1 calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1CalErrorFlagPersistent: 1;        /*## attribute Adc1CalErrorFlagPersistent */
   /**
	* BitsName: adc2_cal_error_flag_persistent
	* Description: ADC2  calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2CalErrorFlagPersistent: 1;        /*## attribute Adc2CalErrorFlagPersistent */
   /**
	* BitsName: adc3_cal_error_flag_persistent
	* Description: ADC3  calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3CalErrorFlagPersistent: 1;        /*## attribute Adc3CalErrorFlagPersistent */
   /**
	* BitsName: adc4_cal_error_flag_persistent
	* Description: ADC4  calibaration  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4CalErrorFlagPersistent: 1;        /*## attribute Adc4CalErrorFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag_persistent
	* Description: ADC1 near  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1NearClippingFlagPersistent: 1;        /*## attribute Adc1NearClippingFlagPersistent */
   /**
	* BitsName: adc2_near_clipping_flag_persistent
	* Description: ADC2  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2NearClippingFlagPersistent: 1;        /*## attribute Adc2NearClippingFlagPersistent */
   /**
	* BitsName: adc3_near_clipping_flag_persistent
	* Description: ADC3  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3NearClippingFlagPersistent: 1;        /*## attribute Adc3NearClippingFlagPersistent */
   /**
	* BitsName: adc4_near_clipping_flag_persistent
	* Description: ADC4  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4NearClippingFlagPersistent: 1;        /*## attribute Adc4NearClippingFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag
	* Description: ADC1  near clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1NearClippingFlag: 1;        /*## attribute Adc1NearClippingFlag */
   /**
	* BitsName: adc2_near_clipping_flag
	* Description: ADC2  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2NearClippingFlag: 1;        /*## attribute Adc2NearClippingFlag */
   /**
	* BitsName: adc3_near_clipping_flag
	* Description: ADC3  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3NearClippingFlag: 1;        /*## attribute Adc3NearClippingFlag */
   /**
	* BitsName: adc4_near_clipping_flag
	* Description: ADC4  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4NearClippingFlag: 1;        /*## attribute Adc4NearClippingFlag */
   /**
	* BitsName: adc1_clipping_flag_persistent
	* Description: ADC1  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1ClippingFlagPersistent: 1;        /*## attribute Adc1ClippingFlagPersistent */
   /**
	* BitsName: adc2_clipping_flag_persistent
	* Description: ADC2  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2ClippingFlagPersistent: 1;        /*## attribute Adc2ClippingFlagPersistent */
   /**
	* BitsName: adc3_clipping_flag_persistent
	* Description: ADC3  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3ClippingFlagPersistent: 1;        /*## attribute Adc3ClippingFlagPersistent */
   /**
	* BitsName: adc4_clipping_flag_persistent
	* Description: ADC4  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4ClippingFlagPersistent: 1;        /*## attribute Adc4ClippingFlagPersistent */
   /**
	* BitsName: adc1_clipping_flag
	* Description: ADC1  clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1ClippingFlag: 1;        /*## attribute Adc1ClippingFlag */
   /**
	* BitsName: adc2_clipping_flag
	* Description: ADC2  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2ClippingFlag: 1;        /*## attribute Adc2ClippingFlag */
   /**
	* BitsName: adc3_clipping_flag
	* Description: ADC3  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3ClippingFlag: 1;        /*## attribute Adc3ClippingFlag */
   /**
	* BitsName: adc4_clipping_flag
	* Description: ADC4  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4ClippingFlag: 1;        /*## attribute Adc4ClippingFlag */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent
	* Description: ADC1 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1HardClippingFlagPersistent: 1;        /*## attribute Adc1HardClippingFlagPersistent */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent
	* Description: ADC2 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2HardClippingFlagPersistent: 1;        /*## attribute Adc2HardClippingFlagPersistent */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent
	* Description: ADC3 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3HardClippingFlagPersistent: 1;        /*## attribute Adc3HardClippingFlagPersistent */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent
	* Description: ADC4 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4HardClippingFlagPersistent: 1;        /*## attribute Adc4HardClippingFlagPersistent */
   /**
	* BitsName: adc1_hard_clipping_error_flag
	* Description: ADC1 hard clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1HardClippingErrorFlag: 1;        /*## attribute Adc1HardClippingErrorFlag */
   /**
	* BitsName: adc2_hard_clipping_error_flag
	* Description: ADC2 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2HardClippingErrorFlag: 1;        /*## attribute Adc2HardClippingErrorFlag */
   /**
	* BitsName: adc3_hard_clipping_error_flag
	* Description: ADC3 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3HardClippingErrorFlag: 1;        /*## attribute Adc3HardClippingErrorFlag */
   /**
	* BitsName: adc4_hard_clipping_error_flag
	* Description: ADC4 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4HardClippingErrorFlag: 1;        /*## attribute Adc4HardClippingErrorFlag */
   /**
	* BitsName: supply_low_error_flag_adc12
	* Description: ADC12 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc12: 1;        /*## attribute SupplyLowErrorFlagAdc12 */
   /**
	* BitsName: supply_low_error_flag_adc34
	* Description: ADC34 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc34: 1;        /*## attribute SupplyLowErrorFlagAdc34 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_FitStatusAdcRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_STATUS_ERROR_FLAG_COUNTBits_t
* RegisterName: ADC_status_error_flag_count
* 
* AddressRange: 0xREAD - 0x0A4
* ResetValue: 0x000000A8
*/
typedef struct  {
   /**
	* BitsName: adc_status_error_count
	* Description: Error flag count for the selected ADC error .  This register can be resetted only through MCU 
	* Count is incremented at a rate programmed in register ADC_status_monitoring_control (0x18) status_error_poll_count_value bit 
	* 
	* Reset through  the following
	* 
	* 
	* ISM_error_status_and_mcu_reset 0x0AC ( bit 1: reset_error_count_mcu_spi)
	* ADC_status_monitoring_control 0x018 (bi 1 : status_monitoring_reset_spi)
	*/
    uint32 AdcStatusErrorCount: 31;        /*## attribute AdcStatusErrorCount */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountBits_t;
    /**
* Nxp_Tef810x_Mod18_STATUS_MONITORING_FLAGBits_t
* RegisterName: status_monitoring_flag
* 
* AddressRange: 0xREAD - 0x0A8
* ResetValue: 0x000000AC
*/
typedef struct  {
   /**
	* BitsName: chirp_vco_level_low_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco level is getting  low
	* In next system idle cycle this level need to be adjusted
	*/
    uint32 ChirpVcoLevelLowErrorFlagChirpToMcu: 1;        /*## attribute ChirpVcoLevelLowErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vco_level_high_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco level is getting high
	* In next system idle cycle this level need to be adjusted. Otherwise this may result in a reliability issue
	*/
    uint32 ChirpVcoLevelHighErrorFlagChirpToMcu: 1;        /*## attribute ChirpVcoLevelHighErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vtune_low_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco vtune level is getting  low
	*/
    uint32 ChirpVtuneLowErrorFlagChirpToMcu: 1;        /*## attribute ChirpVtuneLowErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vtune_high_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco vtune level is getting high.
	* In next system idle cycle this level need to be adjusted
	*/
    uint32 ChirpVtuneHighErrorFlagChirpToMcu: 1;        /*## attribute ChirpVtuneHighErrorFlagChirpToMcu */
   /**
	* BitsName: rx1_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX1 module  RF level is going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx1LoLowErrorFlag: 1;        /*## attribute Rx1LoLowErrorFlag */
   /**
	* BitsName: rx2_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX2 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx2LoLowErrorFlag: 1;        /*## attribute Rx2LoLowErrorFlag */
   /**
	* BitsName: rx3_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX3 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx3LoLowErrorFlag: 1;        /*## attribute Rx3LoLowErrorFlag */
   /**
	* BitsName: rx4_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX4 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx4LoLowErrorFlag: 1;        /*## attribute Rx4LoLowErrorFlag */
   /**
	* BitsName: rx1_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX1 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx1LoHighErrorFlag: 1;        /*## attribute Rx1LoHighErrorFlag */
   /**
	* BitsName: rx2_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX2 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx2LoHighErrorFlag: 1;        /*## attribute Rx2LoHighErrorFlag */
   /**
	* BitsName: rx3_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX3 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx3LoHighErrorFlag: 1;        /*## attribute Rx3LoHighErrorFlag */
   /**
	* BitsName: rx4_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX4 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx4LoHighErrorFlag: 1;        /*## attribute Rx4LoHighErrorFlag */
   /**
	* BitsName: tx1_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX1 module  RF level is going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits. Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx1PaLowErrorFlag: 1;        /*## attribute Tx1PaLowErrorFlag */
   /**
	* BitsName: tx2_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX2 module  RF level is login low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits. Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx2PaLowErrorFlag: 1;        /*## attribute Tx2PaLowErrorFlag */
   /**
	* BitsName: tx3_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX3 module  RF level is  going low
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx3PaLowErrorFlag: 1;        /*## attribute Tx3PaLowErrorFlag */
   /**
	* BitsName: tx1_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX1 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx1PaHighErrorFlag: 1;        /*## attribute Tx1PaHighErrorFlag */
   /**
	* BitsName: tx2_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX2 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx2PaHighErrorFlag: 1;        /*## attribute Tx2PaHighErrorFlag */
   /**
	* BitsName: tx3_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX3 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx3PaHighErrorFlag: 1;        /*## attribute Tx3PaHighErrorFlag */
   /**
	* BitsName: mc_pll_freq_calib_error_flag
	* Description: 0: No issues
	* 1: Main PLL need re-calibration
	* if this bit is set , then a recalibration of mail PLL has to be initiated in next system IDLE cycle.   procedure for re calibration TBD
	*/
    uint32 McPllFreqCalibErrorFlag: 1;        /*## attribute McPllFreqCalibErrorFlag */
   /**
	* BitsName: temp_error_flag_tx1
	* Description: 0: No issues
	* 1: Issue in tx1 temp
	*/
    uint32 TempErrorFlagTx1: 1;        /*## attribute TempErrorFlagTx1 */
   /**
	* BitsName: temp_error_flag_tx2
	* Description: 0: No issues
	* 1: Issue in tx2 temp
	*/
    uint32 TempErrorFlagTx2: 1;        /*## attribute TempErrorFlagTx2 */
   /**
	* BitsName: temp_error_flag_tx3
	* Description: 0: No issues
	* 1: Issue in tx3 temp
	*/
    uint32 TempErrorFlagTx3: 1;        /*## attribute TempErrorFlagTx3 */
   /**
	* BitsName: max_temp_error_flag_chirp
	* Description: 0: No issues
	* 1: Issue in chirp temp
	*/
    uint32 MaxTempErrorFlagChirp: 1;        /*## attribute MaxTempErrorFlagChirp */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_StatusMonitoringFlagBits_t;
    /**
* Nxp_Tef810x_Mod18_ISM_ERROR_STATUS_AND_MCU_RESETBits_t
* RegisterName: ISM_error_status_and_mcu_reset
* 
* AddressRange: 0xREADWRITE - 0x0AC
* ResetValue: 0x000000B0
*/
typedef struct  {
   /**
	* BitsName: reset_error_mcu_spi
	* Description: Reset all ISM error in Dolphin 
	* 0: no action
	* 1: reset all errors
	* 
	* A reset will clear error only if the underlying errir is not present any more
	*/
    uint32 ResetErrorMcuSpi: 1;        /*## attribute ResetErrorMcuSpi */
   /**
	* BitsName: reset_error_count_mcu_spi
	* Description: Reset all   error count register
	* 0: no action
	* 1: reset all counters except crc good, bad debug counters
	*/
    uint32 ResetErrorCountMcuSpi: 1;        /*## attribute ResetErrorCountMcuSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: reset_error_ftti_wdt
	* Description: Auto clear bit. Writing 1 will reset the FTTI WDT
	*/
    uint32 ResetErrorFttiWdt: 1;        /*## attribute ResetErrorFttiWdt */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: reset_error_status_wdt
	* Description: Auto clear bit. Writing 1 will reset the Status WDT
	*/
    uint32 ResetErrorStatusWdt: 1;        /*## attribute ResetErrorStatusWdt */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: rtm_error
	* Description: 0: No issues
	* 1: real time monitoring error reported by ISM
	*/
    uint32 RtmError: 1;        /*## attribute RtmError */
   /**
	* BitsName: rf_power_down_error
	* Description: 0: No issues
	* 1:  Reliability issues reported in Dolphin possibly leading to an RF power down of modules within Dolphin
	*/
    uint32 RfPowerDownError: 1;        /*## attribute RfPowerDownError */
   /**
	* BitsName: ftti_error
	* Description: 0: No issues
	* 1: FTTI WDT timer expired
	*/
    uint32 FttiError: 1;        /*## attribute FttiError */
   /**
	* BitsName: start_up_check_error
	* Description: 0: No issues
	* 1: Error in start_up check
	*/
    uint32 StartUpCheckError: 1;        /*## attribute StartUpCheckError */
   /**
	* BitsName: rtm_error_red
	* Description: 0: No issues
	* 1: real time monitoring error reported by ISM indication from redundant ISM
	*/
    uint32 RtmErrorRed: 1;        /*## attribute RtmErrorRed */
   /**
	* BitsName: rf_power_down_error_red
	* Description: 0: No issues
	* 1:  Reliability issues reported in Dolphin possibly leading to an RF power down of modules within Dolphin indication from redundant ISM
	*/
    uint32 RfPowerDownErrorRed: 1;        /*## attribute RfPowerDownErrorRed */
   /**
	* BitsName: ftti_error_red
	* Description: 0: No issues
	* 1: FTTI WDT timer expired indication from redundant ISM
	*/
    uint32 FttiErrorRed: 1;        /*## attribute FttiErrorRed */
   /**
	* BitsName: start_up_check_error_red
	* Description: Redundant module for start up check.  
	* 0: No issues
	* 1: Error in startup check
	*/
    uint32 StartUpCheckErrorRed: 1;        /*## attribute StartUpCheckErrorRed */
   /**
	* BitsName: crc_error
	* Description: Indicates CRC error status  
	* 0: No issues
	* 1: Error in CRC mosi lane
	*/
    uint32 CrcError: 1;        /*## attribute CrcError */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 6;        /*## attribute Reserved3 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetBits_t;
    /**
* Nxp_Tef810x_Mod18_LOOP_BACK_TEST_REGBits_t
* RegisterName: loop_back_test_reg
* 
* AddressRange: 0xREADWRITE - 0x0B8
* ResetValue: 0x000000BC
*/
typedef struct  {
   /**
	* BitsName: chirp_start_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ChirpStartDataOut: 1;        /*## attribute ChirpStartDataOut */
   /**
	* BitsName: ready_int_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ReadyIntDataOut: 1;        /*## attribute ReadyIntDataOut */
   /**
	* BitsName: error_n_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ErrorNDataOut: 1;        /*## attribute ErrorNDataOut */
   /**
	* BitsName: error_reset_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ErrorResetDataOut: 1;        /*## attribute ErrorResetDataOut */
   /**
	* BitsName: tx1_ps_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx1PsDataOut: 1;        /*## attribute Tx1PsDataOut */
   /**
	* BitsName: tx2_ps_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx2PsDataOut: 1;        /*## attribute Tx2PsDataOut */
   /**
	* BitsName: tx3_ps_data_out
	* Description: If loop back dir. is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx3PsDataOut: 1;        /*## attribute Tx3PsDataOut */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: chirp_start_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ChirpStartDir: 1;        /*## attribute ChirpStartDir */
   /**
	* BitsName: ready_int_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ReadyIntDir: 1;        /*## attribute ReadyIntDir */
   /**
	* BitsName: error_n_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ErrorNDir: 1;        /*## attribute ErrorNDir */
   /**
	* BitsName: error_reset_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ErrorResetDir: 1;        /*## attribute ErrorResetDir */
   /**
	* BitsName: tx1_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx1PsDir: 1;        /*## attribute Tx1PsDir */
   /**
	* BitsName: tx2_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx2PsDir: 1;        /*## attribute Tx2PsDir */
   /**
	* BitsName: tx3_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx3PsDir: 1;        /*## attribute Tx3PsDir */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: loop_back_test_en
	* Description: 0: IO's are in normal functional mode
	* 1: I/O's configured for loop back test
	*/
    uint32 LoopBackTestEn: 1;        /*## attribute LoopBackTestEn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 14;        /*## attribute Reserved2 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_LoopBackTestRegBits_t;
    /**
* Nxp_Tef810x_Mod18_SUPPLY_ERROR_MON_REGBits_t
* RegisterName: supply_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0BC
* ResetValue: 0x000000C0
*/
typedef struct  {
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_mon
	* Description: Supply 1V8 low sensor  for TX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx11V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx11V8Mon */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_mon
	* Description: Supply 1V8 low sensor  for TX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx21V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx21V8Mon */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_mon
	* Description: Supply 1V8 low sensor  for TX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx31V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx31V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_mon
	* Description: Supply 1V1 low sensor  for RX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx11V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx11V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_mon
	* Description: Supply 1V1 low sensor  for RX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx21V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx21V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_mon
	* Description: Supply 1V1 low sensor  for RX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx31V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx31V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_mon
	* Description: Supply 1V1 low sensor  for RX4
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx41V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx41V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_mon
	* Description: Supply 1V8 low sensor  for RX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx11V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx11V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_mon
	* Description: Supply 1V8 low sensor  for RX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx21V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx21V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_mon
	* Description: Supply 1V8 low sensor  for RX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx31V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx31V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_mon
	* Description: Supply 1V8 low sensor  for RX4
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx41V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx41V8Mon */
   /**
	* BitsName: supply_low_error_flag_mc_1v8_mon
	* Description: Supply 1V8 low sensor  for master clock ( ( cover pin failure))
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagMc1V8Mon: 1;        /*## attribute SupplyLowErrorFlagMc1V8Mon */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_mon
	* Description: Supply 1V8 low sensor  for ADC12
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagAdc121V8Mon: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Mon */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_mon
	* Description: Supply 1V8 low sensor  for ADC34
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagAdc341V8Mon: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Mon */
   /**
	* BitsName: supply_low_error_flag_interface_1v1_mon
	* Description: Supply 1V8 low sensor  for LO interface
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagInterface1V1Mon: 1;        /*## attribute SupplyLowErrorFlagInterface1V1Mon */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8_mon
	* Description: Supply 1V8 low sensor  for SSB MOD
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8Mon: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8Mon */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8_mon
	* Description: Supply 1V8 low sensor  for global bias
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8Mon */
   /**
	* BitsName: supply_low_error_flag_ser_1v1_mon
	* Description: Supply 1V1 low sensor  for serializer LVDS
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSer1V1Mon: 1;        /*## attribute SupplyLowErrorFlagSer1V1Mon */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1_mon
	* Description: Supply 1V1 low sensor  for serializer CSI2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagCsi21V1Mon: 1;        /*## attribute SupplyLowErrorFlagCsi21V1Mon */
   /**
	* BitsName: supply_low_error_flag_ser_1v8_mon
	* Description: Supply 1V8 low sensor  for serializer
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSer1V8Mon: 1;        /*## attribute SupplyLowErrorFlagSer1V8Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8_mon
	* Description: Supply 1V8  low sensor  for chirp PLL ( cover pin failure)
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8Mon: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8_mon
	* Description: Supply 1V8  low sensor  for chirp VCO ( cover pin failure)
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8Mon: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1_mon
	* Description: Supply 1V1  low sensor  for chirp digital
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1Mon: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1Mon */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8_mon
	* Description: Global 1V8LDO supply low  sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8Mon */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8_mon
	* Description: Global 1V8LDO supply high sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8Mon: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8Mon */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1_mon
	* Description: Global 1V1LDO supply low  sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1Mon */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1_mon
	* Description: Global 1V1LDO supply high sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1Mon: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1Mon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_SupplyErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_TX_ERROR_MON_REGBits_t
* RegisterName: tx_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0C0
* ResetValue: 0x000000C4
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_tx1_mon
	* Description: Functional safety error flag
	* 
	* TX1 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx1Mon: 1;        /*## attribute BbErrorFlagTx1Mon */
   /**
	* BitsName: bb_error_flag_tx2_mon
	* Description: Functional safety error flag
	* 
	* TX2 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx2Mon: 1;        /*## attribute BbErrorFlagTx2Mon */
   /**
	* BitsName: bb_error_flag_tx3_mon
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx3Mon: 1;        /*## attribute BbErrorFlagTx3Mon */
   /**
	* BitsName: temp_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx1Mon: 1;        /*## attribute TempErrorFlagTx1Mon */
   /**
	* BitsName: temp_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx2Mon: 1;        /*## attribute TempErrorFlagTx2Mon */
   /**
	* BitsName: temp_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx3Mon: 1;        /*## attribute TempErrorFlagTx3Mon */
   /**
	* BitsName: rf_min_error_flag_tx1_mon
	* Description: Functional safety error flag
	* 
	* Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx1Mon: 1;        /*## attribute RfMinErrorFlagTx1Mon */
   /**
	* BitsName: rf_min_error_flag_tx2_mon
	* Description: Functional safety error flag
	* 
	* TX2 Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx2Mon: 1;        /*## attribute RfMinErrorFlagTx2Mon */
   /**
	* BitsName: rf_min_error_flag_tx3_mon
	* Description: Functional safety error flag
	* 
	* TX3 Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx3Mon: 1;        /*## attribute RfMinErrorFlagTx3Mon */
   /**
	* BitsName: rf_low_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx1Mon: 1;        /*## attribute RfLowErrorFlagTx1Mon */
   /**
	* BitsName: rf_low_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx2Mon: 1;        /*## attribute RfLowErrorFlagTx2Mon */
   /**
	* BitsName: rf_low_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx3Mon: 1;        /*## attribute RfLowErrorFlagTx3Mon */
   /**
	* BitsName: rf_high_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx1Mon: 1;        /*## attribute RfHighErrorFlagTx1Mon */
   /**
	* BitsName: rf_high_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx2Mon: 1;        /*## attribute RfHighErrorFlagTx2Mon */
   /**
	* BitsName: rf_high_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx3Mon: 1;        /*## attribute RfHighErrorFlagTx3Mon */
   /**
	* BitsName: rf_max_error_flag_tx1_mon
	* Description: Reliability flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx1Mon: 1;        /*## attribute RfMaxErrorFlagTx1Mon */
   /**
	* BitsName: rf_max_error_flag_tx2_mon
	* Description: Reliability flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx2Mon: 1;        /*## attribute RfMaxErrorFlagTx2Mon */
   /**
	* BitsName: rf_max_error_flag_tx3_mon
	* Description: Reliability flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx3Mon: 1;        /*## attribute RfMaxErrorFlagTx3Mon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_TxErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RX_ERROR_MON_REGBits_t
* RegisterName: rx_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0C4
* ResetValue: 0x000000C8
*/
typedef struct  {
   /**
	* BitsName: bb_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx1Mon: 1;        /*## attribute BbErrorFlagRx1Mon */
   /**
	* BitsName: bb_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx2Mon: 1;        /*## attribute BbErrorFlagRx2Mon */
   /**
	* BitsName: bb_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx3Mon: 1;        /*## attribute BbErrorFlagRx3Mon */
   /**
	* BitsName: bb_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx4Mon: 1;        /*## attribute BbErrorFlagRx4Mon */
   /**
	* BitsName: lo_min_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx1Mon: 1;        /*## attribute LoMinErrorFlagRx1Mon */
   /**
	* BitsName: lo_min_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx2Mon: 1;        /*## attribute LoMinErrorFlagRx2Mon */
   /**
	* BitsName: lo_min_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx3Mon: 1;        /*## attribute LoMinErrorFlagRx3Mon */
   /**
	* BitsName: lo_min_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx4Mon: 1;        /*## attribute LoMinErrorFlagRx4Mon */
   /**
	* BitsName: lo_low_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx1Mon: 1;        /*## attribute LoLowErrorFlagRx1Mon */
   /**
	* BitsName: lo_low_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx2Mon: 1;        /*## attribute LoLowErrorFlagRx2Mon */
   /**
	* BitsName: lo_low_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx3Mon: 1;        /*## attribute LoLowErrorFlagRx3Mon */
   /**
	* BitsName: lo_low_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx4Mon: 1;        /*## attribute LoLowErrorFlagRx4Mon */
   /**
	* BitsName: lo_high_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx1Mon: 1;        /*## attribute LoHighErrorFlagRx1Mon */
   /**
	* BitsName: lo_high_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx2Mon: 1;        /*## attribute LoHighErrorFlagRx2Mon */
   /**
	* BitsName: lo_high_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx3Mon: 1;        /*## attribute LoHighErrorFlagRx3Mon */
   /**
	* BitsName: lo_high_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx4Mon: 1;        /*## attribute LoHighErrorFlagRx4Mon */
   /**
	* BitsName: lo_max_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx1Mon: 1;        /*## attribute LoMaxErrorFlagRx1Mon */
   /**
	* BitsName: lo_max_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx2Mon: 1;        /*## attribute LoMaxErrorFlagRx2Mon */
   /**
	* BitsName: lo_max_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx3Mon: 1;        /*## attribute LoMaxErrorFlagRx3Mon */
   /**
	* BitsName: lo_max_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx4Mon: 1;        /*## attribute LoMaxErrorFlagRx4Mon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_RxErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CHIRP_ERROR_MON_REGBits_t
* RegisterName: chirp_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0C8
* ResetValue: 0x000000CC
*/
typedef struct  {
   /**
	* BitsName: lock_step_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LockStepErrorFlagChirpMon: 1;        /*## attribute LockStepErrorFlagChirpMon */
   /**
	* BitsName: unlock_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 UnlockErrorFlagChirpMon: 1;        /*## attribute UnlockErrorFlagChirpMon */
   /**
	* BitsName: max_temp_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 MaxTempErrorFlagChirpMon: 1;        /*## attribute MaxTempErrorFlagChirpMon */
   /**
	* BitsName: vtune_low_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VtuneLowErrorFlagChirpMon: 1;        /*## attribute VtuneLowErrorFlagChirpMon */
   /**
	* BitsName: vtune_high_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VtuneHighErrorFlagChirpMon: 1;        /*## attribute VtuneHighErrorFlagChirpMon */
   /**
	* BitsName: level_low_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelLowErrorFlagChirpMon: 1;        /*## attribute LevelLowErrorFlagChirpMon */
   /**
	* BitsName: level_high_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelHighErrorFlagChirpMon: 1;        /*## attribute LevelHighErrorFlagChirpMon */
   /**
	* BitsName: level_min_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelMinErrorFlagChirpMon: 1;        /*## attribute LevelMinErrorFlagChirpMon */
   /**
	* BitsName: level_max_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelMaxErrorFlagChirpMon: 1;        /*## attribute LevelMaxErrorFlagChirpMon */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VcoFreq480ErrorFlagChirpMon: 1;        /*## attribute VcoFreq480ErrorFlagChirpMon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 InterfaceStuckFlagChirpMon: 1;        /*## attribute InterfaceStuckFlagChirpMon */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 17;        /*## attribute Reserved1 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_ChirpErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_MC_LO_ERROR_MON_REGBits_t
* RegisterName: mc_lo_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0CC
* ResetValue: 0x000000D0
*/
typedef struct  {
   /**
	* BitsName: mc_pll_freq_cal_flag_mon
	* Description: Status monitoring flag
	*  
	* Main pll (4.8GHz) calibration issues ( out of calibration)
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllFreqCalFlagMon: 1;        /*## attribute McPllFreqCalFlagMon */
   /**
	* BitsName: mc_pll_level_error_flag_mon
	* Description: Functional safety error flag
	* 
	* Main PLL (4.8GHz) O/P  level is too low or too high
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllLevelErrorFlagMon: 1;        /*## attribute McPllLevelErrorFlagMon */
   /**
	* BitsName: mc_pll_lock_error_flag_mon
	* Description: Functional safety error flag
	* 
	* Main PLL (4.8GHz) in un lock condition
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllLockErrorFlagMon: 1;        /*## attribute McPllLockErrorFlagMon */
   /**
	* BitsName: dig_freq_error_flag_masterclk_mon
	* Description: Functional safety error flag
	* 
	* The O/P frequency from master clock is not within tolerable limits (480/.600 MHz digital clock)
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 DigFreqErrorFlagMasterclkMon: 1;        /*## attribute DigFreqErrorFlagMasterclkMon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface_mon
	* Description: Functional safety error flag
	* 
	* RF port connectivity issues reported in LO interface  block 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagInterfaceMon: 1;        /*## attribute BbErrorFlagInterfaceMon */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 22;        /*## attribute Reserved1 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_McLoErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ADC_ERROR_MON_REGBits_t
* RegisterName: adc_error_mon_reg
* 
* AddressRange: 0xREADWRITE - 0x0D0
* ResetValue: 0x000000D4
*/
typedef struct  {
   /**
	* BitsName: adc1_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC1
	* Indicate a calibaration error within ADC 1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1CalErrorMonPersistent: 1;        /*## attribute Adc1CalErrorMonPersistent */
   /**
	* BitsName: adc2_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC2
	* Indicate a calibaration error within ADC 2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2CalErrorMonPersistent: 1;        /*## attribute Adc2CalErrorMonPersistent */
   /**
	* BitsName: adc3_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC3
	* Indicate a calibaration error within ADC 3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3CalErrorMonPersistent: 1;        /*## attribute Adc3CalErrorMonPersistent */
   /**
	* BitsName: adc4_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC4
	* Indicate a calibaration error within ADC 4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4CalErrorMonPersistent: 1;        /*## attribute Adc4CalErrorMonPersistent */
   /**
	* BitsName: adc1_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1NearClippingMonPersistent: 1;        /*## attribute Adc1NearClippingMonPersistent */
   /**
	* BitsName: adc2_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2NearClippingMonPersistent: 1;        /*## attribute Adc2NearClippingMonPersistent */
   /**
	* BitsName: adc3_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3NearClippingMonPersistent: 1;        /*## attribute Adc3NearClippingMonPersistent */
   /**
	* BitsName: adc4_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4NearClippingMonPersistent: 1;        /*## attribute Adc4NearClippingMonPersistent */
   /**
	* BitsName: adc1_near_clipping_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1NearClippingMon: 1;        /*## attribute Adc1NearClippingMon */
   /**
	* BitsName: adc2_near_clipping_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2NearClippingMon: 1;        /*## attribute Adc2NearClippingMon */
   /**
	* BitsName: adc3_near_clipping_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3NearClippingMon: 1;        /*## attribute Adc3NearClippingMon */
   /**
	* BitsName: adc4_near_clipping_mon
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4NearClippingMon: 1;        /*## attribute Adc4NearClippingMon */
   /**
	* BitsName: adc1_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1ClippingMonPersistent: 1;        /*## attribute Adc1ClippingMonPersistent */
   /**
	* BitsName: adc2_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2ClippingMonPersistent: 1;        /*## attribute Adc2ClippingMonPersistent */
   /**
	* BitsName: adc3_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3ClippingMonPersistent: 1;        /*## attribute Adc3ClippingMonPersistent */
   /**
	* BitsName: adc4_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4ClippingMonPersistent: 1;        /*## attribute Adc4ClippingMonPersistent */
   /**
	* BitsName: adc1_clipping_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1ClippingMon: 1;        /*## attribute Adc1ClippingMon */
   /**
	* BitsName: adc2_clipping_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2ClippingMon: 1;        /*## attribute Adc2ClippingMon */
   /**
	* BitsName: adc3_clipping_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3ClippingMon: 1;        /*## attribute Adc3ClippingMon */
   /**
	* BitsName: adc4_clipping_mon
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4ClippingMon: 1;        /*## attribute Adc4ClippingMon */
   /**
	* BitsName: adc1_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1HardClippingMonPersistent: 1;        /*## attribute Adc1HardClippingMonPersistent */
   /**
	* BitsName: adc2_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2HardClippingMonPersistent: 1;        /*## attribute Adc2HardClippingMonPersistent */
   /**
	* BitsName: adc3_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3HardClippingMonPersistent: 1;        /*## attribute Adc3HardClippingMonPersistent */
   /**
	* BitsName: adc4_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4HardClippingMonPersistent: 1;        /*## attribute Adc4HardClippingMonPersistent */
   /**
	* BitsName: adc1_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1HardClippingErrorMon: 1;        /*## attribute Adc1HardClippingErrorMon */
   /**
	* BitsName: adc2_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2HardClippingErrorMon: 1;        /*## attribute Adc2HardClippingErrorMon */
   /**
	* BitsName: adc3_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3HardClippingErrorMon: 1;        /*## attribute Adc3HardClippingErrorMon */
   /**
	* BitsName: adc4_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC4
	* 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4HardClippingErrorMon: 1;        /*## attribute Adc4HardClippingErrorMon */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_AdcErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CRC_STATUS_WR_REGBits_t
* RegisterName: crc_status_wr_reg
* 
* AddressRange: 0xREADWRITE - 0x0D4
* ResetValue: 0x000000D8
*/
typedef struct  {
   /**
	* BitsName: crc_wr_good_count
	* Description: Indicates the number of good write into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcWrGoodCount: 15;        /*## attribute CrcWrGoodCount */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_wr_bad_count
	* Description: Indicates the number of bad write into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcWrBadCount: 15;        /*## attribute CrcWrBadCount */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_CrcStatusWrRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CRC_STATUS_RD_REGBits_t
* RegisterName: crc_status_rd_reg
* 
* AddressRange: 0xREADWRITE - 0x0D8
* ResetValue: 0x000000DC
*/
typedef struct  {
   /**
	* BitsName: crc_rd_good_count
	* Description: Indicates the number of good read into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcRdGoodCount: 15;        /*## attribute CrcRdGoodCount */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_rd_bad_count
	* Description: Indicates the number of bad read into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcRdBadCount: 15;        /*## attribute CrcRdBadCount */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_CrcStatusRdRegBits_t;
    /**
* Nxp_Tef810x_Mod18_MODULEIDBits_t
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
    uint32 Identifier: 15;        /*## attribute Identifier */
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
}Nxp_Tef810x_Mod18_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod18_StatusFttiWdtCntrlBits_t
* RegisterName: status_ftti_wdt_cntrl
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: status_wdt_count_base
	* Description: Base counter for status WDT
	* 0000: Timer runs at 40 MHz time base
	* 0001: 20 MHz time base
	* 0010: (40/3) MHz
	* 0011: (40/4)MHz.
	* etc.?
	* Use model: time base value depends on the  duration between  heartbeat interrupt.
	*/
    uint32 StatusWdtCountBase: 4;        /*## attribute StatusWdtCountBase */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: status_wdt_mode
	* Description: Mode control for status WDT
	* 0: Moonshot Mode
	* 1: Continuous Mode
	* Preferred use model is to use in continuous mode to generate  a heart beat interrupt to MCU at regular interval.
	*/
    uint32 StatusWdtMode: 1;        /*## attribute StatusWdtMode */
   /**
	* BitsName: status_wdt_active
	* Description: 0: Indicates timer is not active (expired)
	* 1: Indicates timer is active and running
	*/
    uint32 StatusWdtActive: 1;        /*## attribute StatusWdtActive */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: status_wdt_en
	* Description: Enable and start trigger  for status WDT
	* 0: WDT is disabled
	* 1: WDT is enabled and start running
	*/
    uint32 StatusWdtEn: 1;        /*## attribute StatusWdtEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: ftti_wdt_count_base
	* Description: Base counter for FTTI WDT
	* 0000: Timer runs at 40 MHz time base
	* 0001: 20 MHz time base
	* 0010: (40/3) MHz
	* 0011: (40/4)MHz.
	* etc.?
	* Use model: Time base value depends on the  FTTI interval
	*/
    uint32 FttiWdtCountBase: 4;        /*## attribute FttiWdtCountBase */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 4;        /*## attribute Reserved4 */
   /**
	* BitsName: ftti_wdt_mode
	* Description: FTTI WDT mode
	* 0: Moonshot Mode
	* 1: Continuous Mode
	* Preferred use model : Continuous mode  to reduce programming overhead
	*/
    uint32 FttiWdtMode: 1;        /*## attribute FttiWdtMode */
   /**
	* BitsName: ftti_wdt_active
	* Description: 0: Indicates timer is not active
	* 1: Indicates timer is active and running
	*/
    uint32 FttiWdtActive: 1;        /*## attribute FttiWdtActive */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: ftti_wdt_en
	* Description: Enable  FTTI WDT
	* 0: WDT is disabled
	* 1: WDT is enabled and start running
	* Once enabled,  the timer will wait for a chirp sequence start trigger to start the timer.
	* Once a FIT is triggered or if the timer is  resetted by MCU,  then the timer will wait for next chirp sequence active to start again (provided the WDT is configured in continuous mode)
	*/
    uint32 FttiWdtEn: 1;        /*## attribute FttiWdtEn */
}Nxp_Tef810x_Mod18_StatusFttiWdtCntrlBits_t;
    /**
* Nxp_Tef810x_Mod18_FttiWdtCountValueBits_t
* RegisterName: ftti_wdt_count_value
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: ftti_wdt_count_value
	* Description: The value to be programmed to be used along with the base count value  to  calculate the actual  timer interval. The counter is decremented  at an interval defined by the _wdt_count_base  frequency
	*/
    uint32 FttiWdtCountValue: 31;        /*## attribute FttiWdtCountValue */
}Nxp_Tef810x_Mod18_FttiWdtCountValueBits_t;
    /**
* Nxp_Tef810x_Mod18_StatusWdtCountValueBits_t
* RegisterName: status_wdt_count_value
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: status_wdt_count_value
	* Description: Status WDT watchdog timer interval value
	* The value to be programmed to be used along with the base count value  to  calculate the actual  timer interval
	*/
    uint32 StatusWdtCountValue: 31;        /*## attribute StatusWdtCountValue */
}Nxp_Tef810x_Mod18_StatusWdtCountValueBits_t;
    /**
* Nxp_Tef810x_Mod18_FttiWdtRdValueBits_t
* RegisterName: ftti_wdt_rd_value
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: ftti_wdt_rd_value
	* Description: ftti_wdt_rd_value ( current value of the timer)
	* Indicates the running status of the  timer.
	*/
    uint32 FttiWdtRdValue: 31;        /*## attribute FttiWdtRdValue */
}Nxp_Tef810x_Mod18_FttiWdtRdValueBits_t;
    /**
* Nxp_Tef810x_Mod18_StatusWdtRdValueBits_t
* RegisterName: status_wdt_rd_value
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0xFFFFFFFF
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: status_wdt_rd_value
	* Description: status_wdt_rd_value ( current value of the timer)
	* Indicates the running status of the  timer.
	*/
    uint32 StatusWdtRdValue: 31;        /*## attribute StatusWdtRdValue */
}Nxp_Tef810x_Mod18_StatusWdtRdValueBits_t;
    /**
* Nxp_Tef810x_Mod18_McuStartupStatusControlBits_t
* RegisterName: MCU_startup_status_control
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: Sensor_configuration_done
	* Description: 0: Not verified
	* 1: All FS sensors are configured  &  configurations are verified
	*/
    uint32 SensorConfigurationDone: 1;        /*## attribute SensorConfigurationDone */
   /**
	* BitsName: pll4g_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 Pll4GConfigOk: 1;        /*## attribute Pll4GConfigOk */
   /**
	* BitsName: local_bias_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 LocalBiasConfigOk: 1;        /*## attribute LocalBiasConfigOk */
   /**
	* BitsName: IC_calibration_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 IcCalibrationOk: 1;        /*## attribute IcCalibrationOk */
   /**
	* BitsName: local_ldo_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 LocalLdoConfigOk: 1;        /*## attribute LocalLdoConfigOk */
   /**
	* BitsName: gobal_bias_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 GobalBiasConfigOk: 1;        /*## attribute GobalBiasConfigOk */
   /**
	* BitsName: main_ldo_config_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 MainLdoConfigOk: 1;        /*## attribute MainLdoConfigOk */
   /**
	* BitsName: spi_access_check_done_ok
	* Description: 0: Not verified
	* 1: Configured and verified
	*/
    uint32 SpiAccessCheckDoneOk: 1;        /*## attribute SpiAccessCheckDoneOk */
}Nxp_Tef810x_Mod18_McuStartupStatusControlBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcStatusMonitoringControlBits_t
* RegisterName: ADC_status_monitoring_control
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: status_error_poll_count_value
	* Description: Controls the duration of ADC error flags polling. Higher the value lesser the polling. This is primarily valid for the ADC error flag counter. This timer runs on a 40 MHz time base (25 ns)
	* 0000  Status polled on every 100ns  (4 Clock cycle)
	* 0001  Status polled at 125 ns (4 Clock cycle + 1 Clock cycle)
	* 0010  Status polled at 150 ns (4 Clock cycle + 2 Clock cycle)
	* Appication recommendation:  use value '0
	*/
    uint32 StatusErrorPollCountValue: 7;        /*## attribute StatusErrorPollCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: ADC_error_count_sel
	* Description: Selects the ADC error flag to be monitored
	* 0: adc_hard_clipping_error_flag 
	* 1: adc_clipping_error_flag 
	* 2: adc_near_clipping_error_flag  
	* Others : adc_hard_clipping_error_flag
	*/
    uint32 AdcErrorCountSel: 2;        /*## attribute AdcErrorCountSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 7;        /*## attribute Reserved1 */
   /**
	* BitsName: status_monitoring_en
	* Description: Enable status monitoring
	* 0: If ADC status monitoring disabled
	* 1: If ADC status monitoring enabled
	*/
    uint32 StatusMonitoringEn: 1;        /*## attribute StatusMonitoringEn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 6;        /*## attribute Reserved2 */
   /**
	* BitsName: status_monitoring_reset_spi
	* Description: Resets ADC Status Monitoring Counter in register 0XA4. Auto clearing Bit.
	* 
	* Note:  If  the counter reaches  maximum, it will automatically rollover to 0
	*/
    uint32 StatusMonitoringResetSpi: 1;        /*## attribute StatusMonitoringResetSpi */
   /**
	* BitsName: status_monitoring_set_spi
	* Description: Select the Status monitoring window 
	* 
	* 0: ADC monitoring happens only during safety monitor window 
	* 1:  ADC monitoring happens all the time as long as  it is enabled
	*/
    uint32 StatusMonitoringSetSpi: 1;        /*## attribute StatusMonitoringSetSpi */
}Nxp_Tef810x_Mod18_AdcStatusMonitoringControlBits_t;
    /**
* Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusBits_t
* RegisterName: RTM_safety_error_control_and_status
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x80000700
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: safety_err_count_reset_en
	* Description: A set of counters are provided in registers RTM_safety_errorr_count_1 (0x9C) and RTM_safety_errorr_count_2 (0xA0)  for diagnostic purpose.  ( The count is incremented based each time an error is reported ). The counter  can be resetted by MCU. Two options are available
	* 
	* 0:  Safety error count is  resetted explicitly through MCU ( error reset)
	* 1: If this bit is enabled,  the safety error count is resetted  before starting a chirp sequence
	* Please note that this is not part of the safety monitoring net.
	* Details are in rtm_safety_error_count_1 and rtm_safety_error_count_2.
	*/
    uint32 SafetyErrCountResetEn: 1;        /*## attribute SafetyErrCountResetEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 8;        /*## attribute Reserved1 */
   /**
	* BitsName: rt_error_poll_count_value
	* Description: Once an error  is reported to ISM, it is reporetd immediately to the error_n pin and.. However  the state machine need a minimum turn around  time to  poll for any new error.    This is defined by the minimum  value  programmed into this register. 
	* 
	* 
	* 
	* From an application context a value other than 'F' shall not be used ( value based on  simulation )"to be updated
	*/
    uint32 RtErrorPollCountValue: 8;        /*## attribute RtErrorPollCountValue */
   /**
	* BitsName: rtm_error_safety_count_max_value
	* Description: This can be used to  to  count the number of a time an error is geting asserted, before  issuing an error indication to MCU (error_n) .  The logic is active if a value other than '0'is programmed in this register.  if a non zero value is programmed, then based on the   ""rt_error_poll_count_value"" value  the error  input is polled  a number of ttimes (based on the value programmed)  before asserting  error_n
	* 
	* 
	* 
	* Based on validation is it found that  a value other than 0x0  shall not be used by end application.
	*/
    uint32 RtmErrorSafetyCountMaxValue: 8;        /*## attribute RtmErrorSafetyCountMaxValue */
}Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SupplyErrorMaskRegBits_t
* RegisterName: supply_error_mask_reg
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1_mask
	* Description: Global 1V1LDO supply high sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1Mask: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1Mask */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1_mask
	* Description: Global 1V1LDO supply low  sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1Mask */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8_mask
	* Description: Global 1V8LDO supply high sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8Mask: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8Mask */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8_mask
	* Description: Global 1V8LDO supply low  sensor
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1_mask
	* Description: Supply 1V1  low sensor  for chirp digital
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1Mask: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8_mask
	* Description: Supply 1V8  low sensor  for chirp VCO ( cover pin failure)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8Mask: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8Mask */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8_mask
	* Description: Supply 1V8  low sensor  for chirp PLL ( cover pin failure)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8Mask: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8Mask */
   /**
	* BitsName: supply_low_error_flag_ser_1v8_mask
	* Description: Supply 1V8 low sensor  for serializer
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSer1V8Mask: 1;        /*## attribute SupplyLowErrorFlagSer1V8Mask */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1_mask
	* Description: Supply 1V1 low sensor  for serializer CSI2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagCsi21V1Mask: 1;        /*## attribute SupplyLowErrorFlagCsi21V1Mask */
   /**
	* BitsName: supply_low_error_flag_ser_1v1_mask
	* Description: Supply 1V1 low sensor  for serializer LVDS
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSer1V1Mask: 1;        /*## attribute SupplyLowErrorFlagSer1V1Mask */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8_mask
	* Description: Supply 1V8 low sensor  for global bias
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8Mask: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8Mask */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8_mask
	* Description: Supply 1V8 low sensor  for SSB MOD
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8Mask: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8Mask */
   /**
	* BitsName: supply_low_error_flag_interface_1v1_mask
	* Description: Supply 1V8 low sensor  for LO interface
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagInterface1V1Mask: 1;        /*## attribute SupplyLowErrorFlagInterface1V1Mask */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_mask
	* Description: Supply 1V8 low sensor  for ADC34
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagAdc341V8Mask: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Mask */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_mask
	* Description: Supply 1V8 low sensor  for ADC12
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagAdc121V8Mask: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Mask */
   /**
	* BitsName: supply_low_error_flag_mc_1v8_mask
	* Description: Supply 1V8 low sensor  for master clock ( ( cover pin failure))
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagMc1V8Mask: 1;        /*## attribute SupplyLowErrorFlagMc1V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_mask
	* Description: Supply 1V8 low sensor  for RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx41V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx41V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_mask
	* Description: Supply 1V8 low sensor  for RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx31V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx31V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_mask
	* Description: Supply 1V8 low sensor  for RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx21V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx21V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_mask
	* Description: Supply 1V8 low sensor  for RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx11V8Mask: 1;        /*## attribute SupplyLowErrorFlagRx11V8Mask */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_mask
	* Description: Supply 1V1 low sensor  for RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx41V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx41V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_mask
	* Description: Supply 1V1 low sensor  for RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx31V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx31V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_mask
	* Description: Supply 1V1 low sensor  for RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx21V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx21V1Mask */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_mask
	* Description: Supply 1V1 low sensor  for RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagRx11V1Mask: 1;        /*## attribute SupplyLowErrorFlagRx11V1Mask */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_mask
	* Description: Supply 1V8 low sensor  for TX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx31V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx31V8Mask */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_mask
	* Description: Supply 1V8 low sensor  for TX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx21V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx21V8Mask */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_mask
	* Description: Supply 1V8 low sensor  for TX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 SupplyLowErrorFlagTx11V8Mask: 1;        /*## attribute SupplyLowErrorFlagTx11V8Mask */
}Nxp_Tef810x_Mod18_SupplyErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_TxErrorMaskRegBits_t
* RegisterName: tx_error_mask_reg
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_max_error_flag_tx3_mask
	* Description: Reliability flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx3Mask: 1;        /*## attribute RfMaxErrorFlagTx3Mask */
   /**
	* BitsName: rf_max_error_flag_tx2_mask
	* Description: Reliability flag
	* 
	* TX2 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx2Mask: 1;        /*## attribute RfMaxErrorFlagTx2Mask */
   /**
	* BitsName: rf_max_error_flag_tx1_mask
	* Description: Reliability flag
	* 
	* TX1 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMaxErrorFlagTx1Mask: 1;        /*## attribute RfMaxErrorFlagTx1Mask */
   /**
	* BitsName: rf_high_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx3Mask: 1;        /*## attribute RfHighErrorFlagTx3Mask */
   /**
	* BitsName: rf_high_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx2Mask: 1;        /*## attribute RfHighErrorFlagTx2Mask */
   /**
	* BitsName: rf_high_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfHighErrorFlagTx1Mask: 1;        /*## attribute RfHighErrorFlagTx1Mask */
   /**
	* BitsName: rf_low_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx3Mask: 1;        /*## attribute RfLowErrorFlagTx3Mask */
   /**
	* BitsName: rf_low_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx2Mask: 1;        /*## attribute RfLowErrorFlagTx2Mask */
   /**
	* BitsName: rf_low_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfLowErrorFlagTx1Mask: 1;        /*## attribute RfLowErrorFlagTx1Mask */
   /**
	* BitsName: rf_min_error_flag_tx3_mask
	* Description: Functional safety error flag
	* 
	* TX3 Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx3Mask: 1;        /*## attribute RfMinErrorFlagTx3Mask */
   /**
	* BitsName: rf_min_error_flag_tx2_mask
	* Description: Functional safety error flag
	* 
	* TX2 Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx2Mask: 1;        /*## attribute RfMinErrorFlagTx2Mask */
   /**
	* BitsName: rf_min_error_flag_tx1_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in transmitter.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 RfMinErrorFlagTx1Mask: 1;        /*## attribute RfMinErrorFlagTx1Mask */
   /**
	* BitsName: temp_error_flag_tx3_mask
	* Description: Status monitoring flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx3Mask: 1;        /*## attribute TempErrorFlagTx3Mask */
   /**
	* BitsName: temp_error_flag_tx2_mask
	* Description: Status monitoring flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx2Mask: 1;        /*## attribute TempErrorFlagTx2Mask */
   /**
	* BitsName: temp_error_flag_tx1_mask
	* Description: Status monitoring flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  This flag is meant only for status monitoring. Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 TempErrorFlagTx1Mask: 1;        /*## attribute TempErrorFlagTx1Mask */
   /**
	* BitsName: bb_error_flag_tx3_mask
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx3Mask: 1;        /*## attribute BbErrorFlagTx3Mask */
   /**
	* BitsName: bb_error_flag_tx2_mask
	* Description: Functional safety error flag
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx2Mask: 1;        /*## attribute BbErrorFlagTx2Mask */
   /**
	* BitsName: bb_error_flag_tx1_mask
	* Description: Functional safety error flag
	* 
	* TX1 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagTx1Mask: 1;        /*## attribute BbErrorFlagTx1Mask */
}Nxp_Tef810x_Mod18_TxErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RxErrorMaskRegBits_t
* RegisterName: rx_error_mask_reg
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: lo_max_error_flag_rx4_mask
	* Description: Relaibility error flag
	* 
	* RX4 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx4Mask: 1;        /*## attribute LoMaxErrorFlagRx4Mask */
   /**
	* BitsName: lo_max_error_flag_rx3_mask
	* Description: Relaibility error flag
	* 
	* RX3 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx3Mask: 1;        /*## attribute LoMaxErrorFlagRx3Mask */
   /**
	* BitsName: lo_max_error_flag_rx2_mask
	* Description: Relaibility error flag
	* 
	* RX2 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx2Mask: 1;        /*## attribute LoMaxErrorFlagRx2Mask */
   /**
	* BitsName: lo_max_error_flag_rx1_mask
	* Description: Relaibility error flag
	* 
	* RX1 LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMaxErrorFlagRx1Mask: 1;        /*## attribute LoMaxErrorFlagRx1Mask */
   /**
	* BitsName: lo_high_error_flag_rx4_mask
	* Description: Status monitoring error flag 
	* 
	* RX4 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx4Mask: 1;        /*## attribute LoHighErrorFlagRx4Mask */
   /**
	* BitsName: lo_high_error_flag_rx3_mask
	* Description: Status monitoring error flag 
	* 
	* RX3 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx3Mask: 1;        /*## attribute LoHighErrorFlagRx3Mask */
   /**
	* BitsName: lo_high_error_flag_rx2_mask
	* Description: Status monitoring error flag 
	* 
	* RX2 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx2Mask: 1;        /*## attribute LoHighErrorFlagRx2Mask */
   /**
	* BitsName: lo_high_error_flag_rx1_mask
	* Description: Status monitoring error flag 
	* 
	* RX1 LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoHighErrorFlagRx1Mask: 1;        /*## attribute LoHighErrorFlagRx1Mask */
   /**
	* BitsName: lo_low_error_flag_rx4_mask
	* Description: Status monitoring error flag 
	* 
	* RX4 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4Mask: 1;        /*## attribute LoLowErrorFlagRx4Mask */
   /**
	* BitsName: lo_low_error_flag_rx3_mask
	* Description: Status monitoring error flag 
	* 
	* RX3 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx3Mask: 1;        /*## attribute LoLowErrorFlagRx3Mask */
   /**
	* BitsName: lo_low_error_flag_rx2_mask
	* Description: Status monitoring error flag 
	* RX2 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx2Mask: 1;        /*## attribute LoLowErrorFlagRx2Mask */
   /**
	* BitsName: lo_low_error_flag_rx1_mask
	* Description: Status monitoring error flag 
	* 
	* RX1 LO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx1Mask: 1;        /*## attribute LoLowErrorFlagRx1Mask */
   /**
	* BitsName: lo_min_error_flag_rx4_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx4Mask: 1;        /*## attribute LoMinErrorFlagRx4Mask */
   /**
	* BitsName: lo_min_error_flag_rx3_mask
	* Description: Functional safety error flag  
	* 
	* Functional safety error in RX3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx3Mask: 1;        /*## attribute LoMinErrorFlagRx3Mask */
   /**
	* BitsName: lo_min_error_flag_rx2_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx2Mask: 1;        /*## attribute LoMinErrorFlagRx2Mask */
   /**
	* BitsName: lo_min_error_flag_rx1_mask
	* Description: Functional safety error flag
	* 
	* Functional safety error in RX1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoMinErrorFlagRx1Mask: 1;        /*## attribute LoMinErrorFlagRx1Mask */
   /**
	* BitsName: bb_error_flag_rx4_mask
	* Description: Functional safety error flag
	* 
	* RX4  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx4Mask: 1;        /*## attribute BbErrorFlagRx4Mask */
   /**
	* BitsName: bb_error_flag_rx3_mask
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx3Mask: 1;        /*## attribute BbErrorFlagRx3Mask */
   /**
	* BitsName: bb_error_flag_rx2_mask
	* Description: Functional safety error flag
	* 
	* RX2  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx2Mask: 1;        /*## attribute BbErrorFlagRx2Mask */
   /**
	* BitsName: bb_error_flag_rx1_mask
	* Description: Functional safety error flag
	* 
	* RX1  RF connectivity to  external antenna port is  not working.
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagRx1Mask: 1;        /*## attribute BbErrorFlagRx1Mask */
}Nxp_Tef810x_Mod18_RxErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ChirpErrorMaskRegBits_t
* RegisterName: chirp_error_mask_reg
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: Error not masked
	* 1: Error Masked
	*/
    uint32 InterfaceStuckFlagChirpMask: 1;        /*## attribute InterfaceStuckFlagChirpMask */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter operates within the data acquisition window  ( programmable window within data acquistion)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VcoFreq480ErrorFlagChirpMask: 1;        /*## attribute VcoFreq480ErrorFlagChirpMask */
   /**
	* BitsName: level_max_error_flag_chirp_mask
	* Description: Reliability  safety error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelMaxErrorFlagChirpMask: 1;        /*## attribute LevelMaxErrorFlagChirpMask */
   /**
	* BitsName: level_min_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp VCO/PLL not operational
	* Functional safety error in Chirp
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelMinErrorFlagChirpMask: 1;        /*## attribute LevelMinErrorFlagChirpMask */
   /**
	* BitsName: level_high_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp VCO level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelHighErrorFlagChirpMask: 1;        /*## attribute LevelHighErrorFlagChirpMask */
   /**
	* BitsName: level_low_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	*  Chirp VCO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LevelLowErrorFlagChirpMask: 1;        /*## attribute LevelLowErrorFlagChirpMask */
   /**
	* BitsName: vtune_high_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VtuneHighErrorFlagChirpMask: 1;        /*## attribute VtuneHighErrorFlagChirpMask */
   /**
	* BitsName: vtune_low_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 VtuneLowErrorFlagChirpMask: 1;        /*## attribute VtuneLowErrorFlagChirpMask */
   /**
	* BitsName: max_temp_error_flag_chirp_mask
	* Description: Status monitoring error flag
	* 
	* Chirp temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 MaxTempErrorFlagChirpMask: 1;        /*## attribute MaxTempErrorFlagChirpMask */
   /**
	* BitsName: unlock_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 UnlockErrorFlagChirpMask: 1;        /*## attribute UnlockErrorFlagChirpMask */
   /**
	* BitsName: lock_step_error_flag_chirp_mask
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LockStepErrorFlagChirpMask: 1;        /*## attribute LockStepErrorFlagChirpMask */
}Nxp_Tef810x_Mod18_ChirpErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_McLoErrorMaskRegBits_t
* RegisterName: mc_lo_error_mask_reg
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rd_crc_mask
	* Description: CRC Read error flag
	* CRC Read Error Mask
	* 0 : Error not masked
	* 1 : Error masked
	*/
    uint32 RdCrcMask: 1;        /*## attribute RdCrcMask */
   /**
	* BitsName: wr_crc_mask
	* Description: CRC Write error flag
	* CRC Write Error Mask
	* 0 : Error not masked
	* 1 : Error masked
	*/
    uint32 WrCrcMask: 1;        /*## attribute WrCrcMask */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: jtag_active_set_mask
	* Description: Functional safety error flag 
	* 
	* Dolphin IC SPI interface can also work in JTAG mode for test access.
	* In an functional safety application context, the interface has to eb sued only in SPI mode.  If by accident or due to a stuck at issues within Dolphin, if the interface mode is changed,  then no more SPI access is possible.  In this case  the error_n pin is asserted to indicate a functional safety issue in Dolphin
	* 
	* SPI interface moved to test mode (JTAG mode). Indicate a functional failure.  If this failure happens,, then SPI interface is not accessible any more. This register can be accessed only in JTAG mode.    In  a functional safety application context, this error has to be enabled always.
	* 
	* 
	* 0: Error not masked
	* 1: Error masked
	* 
	* Note: The mask feature here is only for validation
	*/
    uint32 JtagActiveSetMask: 1;        /*## attribute JtagActiveSetMask */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: bb_error_flag_interface_mask
	* Description: Functional safety error flag 
	* 
	* RF port connectivity issues reported in LO interface  block 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 BbErrorFlagInterfaceMask: 1;        /*## attribute BbErrorFlagInterfaceMask */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: dig_freq_error_flag_masterclk_mask
	* Description: Functional safety error flag 
	* 
	* The O/P frequency from master clock is not within tolerable limits (480/.600 MHz digital clock)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 DigFreqErrorFlagMasterclkMask: 1;        /*## attribute DigFreqErrorFlagMasterclkMask */
   /**
	* BitsName: mc_pll_lock_error_flag_mask
	* Description: Functional safety error flag 
	* 
	* Main PLL (4.8GHz) in un lock condition
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllLockErrorFlagMask: 1;        /*## attribute McPllLockErrorFlagMask */
   /**
	* BitsName: mc_pll_level_error_flag_mask
	* Description: Functional safety error flag 
	* 
	* Main PLL (4.8GHz) O/P  level is too low or too high
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllLevelErrorFlagMask: 1;        /*## attribute McPllLevelErrorFlagMask */
   /**
	* BitsName: mc_pll_freq_cal_flag_mask
	* Description: Status monitoring flag mask
	*  
	* Main pll (4.8GHz) calibration issues ( out of calibration)
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 McPllFreqCalFlagMask: 1;        /*## attribute McPllFreqCalFlagMask */
}Nxp_Tef810x_Mod18_McLoErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcErrorMaskRegBits_t
* RegisterName: adc_error_mask_reg
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: adc4_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC4
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4HardClippingErrorMask: 1;        /*## attribute Adc4HardClippingErrorMask */
   /**
	* BitsName: adc3_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3HardClippingErrorMask: 1;        /*## attribute Adc3HardClippingErrorMask */
   /**
	* BitsName: adc2_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2HardClippingErrorMask: 1;        /*## attribute Adc2HardClippingErrorMask */
   /**
	* BitsName: adc1_hard_clipping_error_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1HardClippingErrorMask: 1;        /*## attribute Adc1HardClippingErrorMask */
   /**
	* BitsName: adc4_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4HardClippingMaskPersistent: 1;        /*## attribute Adc4HardClippingMaskPersistent */
   /**
	* BitsName: adc3_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3HardClippingMaskPersistent: 1;        /*## attribute Adc3HardClippingMaskPersistent */
   /**
	* BitsName: adc2_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2HardClippingMaskPersistent: 1;        /*## attribute Adc2HardClippingMaskPersistent */
   /**
	* BitsName: adc1_hard_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1HardClippingMaskPersistent: 1;        /*## attribute Adc1HardClippingMaskPersistent */
   /**
	* BitsName: adc4_clipping_mask
	* Description: Status monitoring flag
	* ADC4
	*  0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4ClippingMask: 1;        /*## attribute Adc4ClippingMask */
   /**
	* BitsName: adc3_clipping_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3ClippingMask: 1;        /*## attribute Adc3ClippingMask */
   /**
	* BitsName: adc2_clipping_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2ClippingMask: 1;        /*## attribute Adc2ClippingMask */
   /**
	* BitsName: adc1_clipping_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1ClippingMask: 1;        /*## attribute Adc1ClippingMask */
   /**
	* BitsName: adc4_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4ClippingMaskPersistent: 1;        /*## attribute Adc4ClippingMaskPersistent */
   /**
	* BitsName: adc3_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3ClippingMaskPersistent: 1;        /*## attribute Adc3ClippingMaskPersistent */
   /**
	* BitsName: adc2_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2ClippingMaskPersistent: 1;        /*## attribute Adc2ClippingMaskPersistent */
   /**
	* BitsName: adc1_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1ClippingMaskPersistent: 1;        /*## attribute Adc1ClippingMaskPersistent */
   /**
	* BitsName: adc4_near_clipping_mask
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4NearClippingMask: 1;        /*## attribute Adc4NearClippingMask */
   /**
	* BitsName: adc3_near_clipping_mask
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3NearClippingMask: 1;        /*## attribute Adc3NearClippingMask */
   /**
	* BitsName: adc2_near_clipping_mask
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2NearClippingMask: 1;        /*## attribute Adc2NearClippingMask */
   /**
	* BitsName: adc1_near_clipping_mask
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1NearClippingMask: 1;        /*## attribute Adc1NearClippingMask */
   /**
	* BitsName: adc4_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4NearClippingMaskPersistent: 1;        /*## attribute Adc4NearClippingMaskPersistent */
   /**
	* BitsName: adc3_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3NearClippingMaskPersistent: 1;        /*## attribute Adc3NearClippingMaskPersistent */
   /**
	* BitsName: adc2_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2NearClippingMaskPersistent: 1;        /*## attribute Adc2NearClippingMaskPersistent */
   /**
	* BitsName: adc1_near_clipping_mask_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1NearClippingMaskPersistent: 1;        /*## attribute Adc1NearClippingMaskPersistent */
   /**
	* BitsName: adc4_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC4
	* Indicate a calibaration error within ADC 4
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc4CalErrorMaskPersistent: 1;        /*## attribute Adc4CalErrorMaskPersistent */
   /**
	* BitsName: adc3_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC3
	* Indicate a calibaration error within ADC 3
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc3CalErrorMaskPersistent: 1;        /*## attribute Adc3CalErrorMaskPersistent */
   /**
	* BitsName: adc2_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC2
	* Indicate a calibaration error within ADC 2
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc2CalErrorMaskPersistent: 1;        /*## attribute Adc2CalErrorMaskPersistent */
   /**
	* BitsName: adc1_cal_error_mask_persistent
	* Description: Functional safety error flag..
	* ADC1
	* Indicate a calibaration error within ADC 1
	* 
	* 
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 Adc1CalErrorMaskPersistent: 1;        /*## attribute Adc1CalErrorMaskPersistent */
}Nxp_Tef810x_Mod18_AdcErrorMaskRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RfPowerDownControlBits_t
* RegisterName: rf_power_down_control
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x87000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_power_down_flag_poll_count_value
	* Description: Once an error  is reported to ISM, it is reporetd immediately to the error_n pin and a RF power down is initiated.. However  the state machine need a minimum turn around  time to  poll for any new error.    This is defined by the minimum  value  programmed into this register. 
	* 
	* 
	* 
	* From an application context a value other than 'F' shall not be used ( value based on  simulation )
	*/
    uint32 RfPowerDownFlagPollCountValue: 4;        /*## attribute RfPowerDownFlagPollCountValue */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: rf_power_down_count_threshold
	* Description: This can be used to  to  count the number of a time an error is geting asserted, before  issuing an error indication to MCU (error_n) .  The logic is active if a value other than '0'is programmed in thsi register.  if a non zero value is programmed, then based on the   "rf_power_down_flag_poll_count_value" value  the error  input is polled  a number of ttimes (based on the value programmed)  before asserting  error_n
	* 
	* 
	* 
	* Based on validation is it found that  a value other than 0x0  shall not be used by end application.
	*/
    uint32 RfPowerDownCountThreshold: 4;        /*## attribute RfPowerDownCountThreshold */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 16;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod18_RfPowerDownControlBits_t;
    /**
* Nxp_Tef810x_Mod18_IsmFitTestRegBits_t
* RegisterName: ISM_FIT_test_reg
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 5;        /*## attribute Reserved0 */
   /**
	* BitsName: ISM_test_CurrentState
	* Description: Reflect the current state of the ISM during a FIT test
	* 00: IDLE
	* 01 : ISM in force error state
	* 10: ISM in reset error state
	* 11: ISM test complete
	*/
    uint32 IsmTestCurrentstate: 2;        /*## attribute IsmTestCurrentstate */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: mc_clk_fit_test_en
	* Description: This bit is used to initiate MCU FIT test on mc_xo_no_clk_error_flag.
	* During the regular FIT test, the effect of mc_xo_no_error_flag is not analysed. To test the proper working of mc_xo_no_error_flag this test shall be initiated by MCU seperately.
	* This function shall be used  by MCU to test the functional safety logic related to no clock error from Dolphin.  To test this feature it is recommended to mask other errors  within Dolphin  or make sure that no error is present in Dolphin when conducting this test
	* 0: Release force_error on xo no clock  ( forced error condition is removed)
	* 1: Initiate force error on mc_xo_no_error_flag error is propagated to error_n pin) no action is taken with Dolphin .
	*/
    uint32 McClkFitTestEn: 1;        /*## attribute McClkFitTestEn */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ism_osm_test_reset_error
	* Description: MCU can use this bit to start a FIT test on ISM ( reset error). 
	* 0: No impact
	* 1:  at the end of a force error cycle, a reset error is  issued my MCU. This shall result in error_n pin to  in a de-asserted state ( error_n goes high) . All internal error reported from sensor also should be in a de-asserted state.   The internal error reported from sensor status is tracked through a FIT status register. At the and of test all enabled FIT status register shall be set indicating a successful completion of fault injection test. 
	* The reset error must be asserted by MCU for a minimum duration of one micro second
	*/
    uint32 IsmOsmTestResetError: 1;        /*## attribute IsmOsmTestResetError */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 7;        /*## attribute Reserved3 */
   /**
	* BitsName: ism_osm_test_force_error
	* Description: MCU can use this bit to start a FIT test on ISM (force error)
	* 0: No impact
	* 1:  Internal ISM self test begins including force error assertion to  internal functional safety sensor.  Once  force error is asserted,  error_n should go low and all internal sensors also should report an error  ( MCU to poll the error_n pin. Internal error reported from sensor status is tracked through a FIT status register)
	* Once in reset  error state  a reset  error is asserted on all internal sensors, and  this also should result in error_n pin going high ( as long as this signal is asserted) . MCU shall assert the force error for at least one us 
	* Note: While operating in dynamic power down mode/power save mode especially with chirp in power save mode, FIT test (setting this bit to 1) should be for the minimum period of 60 us before checking the status flags as the vco_480 clock to test the lockstep path is available only after this time because of the vco powerup time in the non-chirping mode.   In non powersave mode, there is no such strict timing requirements as the vco_480 clock is always available.
	*/
    uint32 IsmOsmTestForceError: 1;        /*## attribute IsmOsmTestForceError */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: fit_status_rf_powerdown_1
	* Description: At the end of test, the status of internal ISM is tracked through this register.
	* RF power down ISM  (error_n pin) fit status on ISM and error_n ( redundant module)
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRfPowerdown1: 1;        /*## attribute FitStatusRfPowerdown1 */
   /**
	* BitsName: fit_status_rf_powerdown_0
	* Description: RF power down ISM (error_n pin) fit status on ISM and error_n
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRfPowerdown0: 1;        /*## attribute FitStatusRfPowerdown0 */
   /**
	* BitsName: fit_status_rtm_1
	* Description: At the end of test, the status of internal ISM is tracked through this register.
	* RTM (error_n pin) fit status on ISM and error_n ( redundant module)
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRtm1: 1;        /*## attribute FitStatusRtm1 */
   /**
	* BitsName: fit_status_rtm_0
	* Description: RTM (error_n pin) fit status on ISM and error_n
	* 0: Indicate failure in  FIT test ( at end of test)
	* 1: FIT test successful
	*/
    uint32 FitStatusRtm0: 1;        /*## attribute FitStatusRtm0 */
   /**
	* BitsName: ism_test_complete
	* Description: ISM test complete
	* 0: Test ongoing
	* 1: Indicate test complete, stay here at till a new test is triggered or till reset
	*/
    uint32 IsmTestComplete: 1;        /*## attribute IsmTestComplete */
}Nxp_Tef810x_Mod18_IsmFitTestRegBits_t;
    /**
* Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusBits_t
* RegisterName: master_error_flag_raw_status
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: rx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the RX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 RxBbErrorFlagToMcu: 1;        /*## attribute RxBbErrorFlagToMcu */
   /**
	* BitsName: rx_lo_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from RX LO
	* 0: No error
	* 1: LO FS error
	*/
    uint32 RxLoLevelFsErrorFlagToMcu: 1;        /*## attribute RxLoLevelFsErrorFlagToMcu */
   /**
	* BitsName: tx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the TX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 TxBbErrorFlagToMcu: 1;        /*## attribute TxBbErrorFlagToMcu */
   /**
	* BitsName: tx_rf_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from one of TX unit PA
	* 0: No error
	* 1: TX PA error
	*/
    uint32 TxRfLevelFsErrorFlagToMcu: 1;        /*## attribute TxRfLevelFsErrorFlagToMcu */
   /**
	* BitsName: bb_error_flag_interface_to_mcu
	* Description: RF Ball break detected  in   LO interface
	* 0: No error
	* 1: Ball break error
	*/
    uint32 BbErrorFlagInterfaceToMcu: 1;        /*## attribute BbErrorFlagInterfaceToMcu */
   /**
	* BitsName: mc_pll_dig_freq_error_flag_to_mcu
	* Description: The O/P frequency from main 4.8GHz PLL ( 600/480 MHz) not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 McPllDigFreqErrorFlagToMcu: 1;        /*## attribute McPllDigFreqErrorFlagToMcu */
   /**
	* BitsName: mc_pll_lock_error_flag_to_mcu
	* Description: The main 4.8GHz PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 McPllLockErrorFlagToMcu: 1;        /*## attribute McPllLockErrorFlagToMcu */
   /**
	* BitsName: mc_pll_level_error_flag_to_mcu
	* Description: The main 4.8GHz PLL O/P level not OK i.e either too low or too high
	* 0: No error
	* 1: Pll level not OK
	*/
    uint32 McPllLevelErrorFlagToMcu: 1;        /*## attribute McPllLevelErrorFlagToMcu */
   /**
	* BitsName: adc_cal_error_flag_persistent_to_mcu
	* Description: Main ADC calibration out of Sync ( in one of the  ADC unit)
	* 0: No error
	* 1: Calibration issue in main ADC
	*/
    uint32 AdcCalErrorFlagPersistentToMcu: 1;        /*## attribute AdcCalErrorFlagPersistentToMcu */
   /**
	* BitsName: chirp_vco_level_fs_error_flag_to_mcu
	* Description: Chirp VCO level error
	* 0: No error
	* 1: VCO O/P level not OK
	*/
    uint32 ChirpVcoLevelFsErrorFlagToMcu: 1;        /*## attribute ChirpVcoLevelFsErrorFlagToMcu */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_to_mcu
	* Description: Chirp O/P frequency not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 VcoFreq480ErrorFlagChirpToMcu: 1;        /*## attribute VcoFreq480ErrorFlagChirpToMcu */
   /**
	* BitsName: unlock_error_flag_chirp_to_mcu
	* Description: Chirp  PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 UnlockErrorFlagChirpToMcu: 1;        /*## attribute UnlockErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_dig_lock_step_error_flag
	* Description: Stuck at issue in Chirp digital (lock step mode)
	* 0: No error
	* 1: Lock step out of sync possibly due to a stuck at error
	*/
    uint32 ChirpDigLockStepErrorFlag: 1;        /*## attribute ChirpDigLockStepErrorFlag */
   /**
	* BitsName: global_ldo_1v1_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8LowErrorFlagToMcu */
   /**
	* BitsName: supply_low_error_to_mcu
	* Description: Combined supply low error from all local supply monitoring
	* 0: No error
	* 1: Error
	*/
    uint32 SupplyLowErrorToMcu: 1;        /*## attribute SupplyLowErrorToMcu */
}Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusBits_t
* RegisterName: supply_error_flag_raw_status
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1
	* Description: Global 1V1 LDO supply high error 
	* 0: Supply OK
	* 1: latched Supply high error
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1 */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1
	* Description: Global 1V1 LDO supply low error 
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8
	* Description: Global 1V8 LDO supply high error 
	* 0: Supply OK
	* 1: latched Supply high error
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8 */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8
	* Description: Global 1V8 LDO supply low error 
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8 */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1
	* Description: Chirp digital 1v1 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1 */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8
	* Description: Chirp VCO 1v8 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8 */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8
	* Description: Chirp PLL 1v8 supply low error
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8 */
   /**
	* BitsName: supply_low_error_flag_ser_1v8
	* Description: Serializer 1v8 (CIF & LVDS) supply low error. Valid only if CIF or LVDS function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSer1V8: 1;        /*## attribute SupplyLowErrorFlagSer1V8 */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1
	* Description: Serializer 1v1 (CSI2) supply low error. Valid only CSI2 function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagCsi21V1: 1;        /*## attribute SupplyLowErrorFlagCsi21V1 */
   /**
	* BitsName: supply_low_error_flag_ser_1v1
	* Description: Serializer 1v1 (CIF & LVDS) supply low error. Valid only if CIF or LVDS function is enabled
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSer1V1: 1;        /*## attribute SupplyLowErrorFlagSer1V1 */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8
	* Description: Global bias supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8 */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8
	* Description: SSB mode supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8 */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: LO interface  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8
	* Description: ADC34  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagAdc341V8: 1;        /*## attribute SupplyLowErrorFlagAdc341V8 */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8
	* Description: ADC12  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagAdc121V8: 1;        /*## attribute SupplyLowErrorFlagAdc121V8 */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Master clock  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: RX4  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: RX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: RX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: RX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: RX4  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: RX3  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: RX2  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: RX1  supply low error (1V1)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8
	* Description: TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8: 1;        /*## attribute SupplyLowErrorFlagTx31V8 */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8
	* Description: TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8: 1;        /*## attribute SupplyLowErrorFlagTx21V8 */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8: 1;        /*## attribute SupplyLowErrorFlagTx11V8 */
}Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_TxErrorFlagRawStatusBits_t
* RegisterName: tx_error_flag_raw_status
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error_raw
	* Description: Functional safety error flag
	* 
	* TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx31V8ErrorRaw */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error flag
	* 
	* TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx21V8ErrorRaw */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error_raw
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8ErrorRaw: 1;        /*## attribute SupplyLowErrorFlagTx11V8ErrorRaw */
   /**
	* BitsName: tx3_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx3RfReliabilityLevelErrorRaw */
   /**
	* BitsName: tx2_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX2  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx2RfReliabilityLevelErrorRaw */
   /**
	* BitsName: tx1_rf_reliability_level_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX1  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfReliabilityLevelErrorRaw: 1;        /*## attribute Tx1RfReliabilityLevelErrorRaw */
   /**
	* BitsName: tx3_rf_level_high_error_raw
	* Description: Reliability  monitoring error flag
	* 
	* TX3  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelHighErrorRaw: 1;        /*## attribute Tx3RfLevelHighErrorRaw */
   /**
	* BitsName: tx2_rf_level_high_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelHighErrorRaw: 1;        /*## attribute Tx2RfLevelHighErrorRaw */
   /**
	* BitsName: tx1_rf_level_high_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelHighErrorRaw: 1;        /*## attribute Tx1RfLevelHighErrorRaw */
   /**
	* BitsName: tx3_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelLowErrorRaw: 1;        /*## attribute Tx3RfLevelLowErrorRaw */
   /**
	* BitsName: tx2_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelLowErrorRaw: 1;        /*## attribute Tx2RfLevelLowErrorRaw */
   /**
	* BitsName: tx1_rf_level_low_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelLowErrorRaw: 1;        /*## attribute Tx1RfLevelLowErrorRaw */
   /**
	* BitsName: tx3_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX3 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelFsErrorRaw: 1;        /*## attribute Tx3RfLevelFsErrorRaw */
   /**
	* BitsName: tx2_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX2 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelFsErrorRaw: 1;        /*## attribute Tx2RfLevelFsErrorRaw */
   /**
	* BitsName: tx1_rf_level_fs_error_raw
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX1  TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelFsErrorRaw: 1;        /*## attribute Tx1RfLevelFsErrorRaw */
   /**
	* BitsName: tx3_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3TempErrorRaw: 1;        /*## attribute Tx3TempErrorRaw */
   /**
	* BitsName: tx2_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2TempErrorRaw: 1;        /*## attribute Tx2TempErrorRaw */
   /**
	* BitsName: tx1_temp_error_raw
	* Description: Status monitoring error flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1TempErrorRaw: 1;        /*## attribute Tx1TempErrorRaw */
   /**
	* BitsName: tx3_bb_error_raw
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3BbErrorRaw: 1;        /*## attribute Tx3BbErrorRaw */
   /**
	* BitsName: tx2_bb_error_raw
	* Description: Functional safety error flag
	* 
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2BbErrorRaw: 1;        /*## attribute Tx2BbErrorRaw */
   /**
	* BitsName: tx1_bb_error_raw
	* Description: Functional safety error flag
	* 
	* TX1  RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1BbErrorRaw: 1;        /*## attribute Tx1BbErrorRaw */
}Nxp_Tef810x_Mod18_TxErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RxErrorFlagRawStatusBits_t
* RegisterName: rx_error_flag_raw_status
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX4 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX3  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX2 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX1  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: lo_high_error_flag_rx4
	* Description: Status monitoring error flag
	* 
	*  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx4: 1;        /*## attribute LoHighErrorFlagRx4 */
   /**
	* BitsName: lo_high_error_flag_rx3
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx3: 1;        /*## attribute LoHighErrorFlagRx3 */
   /**
	* BitsName: lo_high_error_flag_rx2
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx2: 1;        /*## attribute LoHighErrorFlagRx2 */
   /**
	* BitsName: lo_high_error_flag_rx1
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX1  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx1: 1;        /*## attribute LoHighErrorFlagRx1 */
   /**
	* BitsName: lo_low_error_flag_rx4
	* Description: Status monitoring error flag
	* 
	* RX4 LO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level low
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4: 1;        /*## attribute LoLowErrorFlagRx4 */
   /**
	* BitsName: lo_low_error_flag_rx3
	* Description: Status monitoring error flag
	* 
	* RX3 Lo level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx3: 1;        /*## attribute LoLowErrorFlagRx3 */
   /**
	* BitsName: lo_low_error_flag_rx2
	* Description: Status monitoring error flag
	* 
	* RX2 Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx2: 1;        /*## attribute LoLowErrorFlagRx2 */
   /**
	* BitsName: lo_low_error_flag_rx1
	* Description: Status monitoring error flag
	* 
	* Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. RX1  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx1: 1;        /*## attribute LoLowErrorFlagRx1 */
   /**
	* BitsName: lo_min_error_flag_rx4
	* Description: Functional safety error flag
	* 
	* Functional safety error in receiver
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx4: 1;        /*## attribute LoMinErrorFlagRx4 */
   /**
	* BitsName: lo_min_error_flag_rx3
	* Description: Functional safety error flag
	* 
	* RX3 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx3: 1;        /*## attribute LoMinErrorFlagRx3 */
   /**
	* BitsName: lo_min_error_flag_rx2
	* Description: Functional safety error flag
	* 
	* RX2 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx2: 1;        /*## attribute LoMinErrorFlagRx2 */
   /**
	* BitsName: lo_min_error_flag_rx1
	* Description: Functional safety error flag
	* 
	* RX1 LO level too low
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx1: 1;        /*## attribute LoMinErrorFlagRx1 */
   /**
	* BitsName: bb_error_flag_rx4
	* Description: Functional safety error flag
	* 
	* RX4 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx4: 1;        /*## attribute BbErrorFlagRx4 */
   /**
	* BitsName: bb_error_flag_rx3
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx3: 1;        /*## attribute BbErrorFlagRx3 */
   /**
	* BitsName: bb_error_flag_rx2
	* Description: Functional safety error flag
	* 
	* RX2 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx2: 1;        /*## attribute BbErrorFlagRx2 */
   /**
	* BitsName: bb_error_flag_rx1
	* Description: Functional safety error flag
	* 
	* RX1 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx1: 1;        /*## attribute BbErrorFlagRx1 */
}Nxp_Tef810x_Mod18_RxErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusBits_t
* RegisterName: chirp_error_flag_raw_status
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to PLL error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to VCO error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v1) to digital logic error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter op
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VcoFreq480ErrorFlagChirpSync: 1;        /*## attribute VcoFreq480ErrorFlagChirpSync */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* 
	* Functional safety error in Chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level  reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 MaxTempErrorFlagChirpSync: 1;        /*## attribute MaxTempErrorFlagChirpSync */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. Indicate a functional safety error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp digital portion
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
}Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusBits_t
* RegisterName: mc_lo_error_flag_raw_status
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: Supply low error from LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: RF connectivity issues in LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Supply error form MC (1V8)
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: MC digital O.P frequency not in range
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Pll in un lock condition
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: PLL level  is too low or too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_freq_calib_error_flag
	* Description: MC PLL calibration error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McFreqCalibErrorFlag: 1;        /*## attribute McFreqCalibErrorFlag */
}Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusBits_t
* RegisterName: adc_error_flag_raw_status
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC34
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc341V8: 1;        /*## attribute SupplyLowErrorFlagAdc341V8 */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC12
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc121V8: 1;        /*## attribute SupplyLowErrorFlagAdc121V8 */
   /**
	* BitsName: adc4_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingErrorFlag: 1;        /*## attribute Adc4HardClippingErrorFlag */
   /**
	* BitsName: adc3_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingErrorFlag: 1;        /*## attribute Adc3HardClippingErrorFlag */
   /**
	* BitsName: adc2_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingErrorFlag: 1;        /*## attribute Adc2HardClippingErrorFlag */
   /**
	* BitsName: adc1_hard_clipping_error_flag
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingErrorFlag: 1;        /*## attribute Adc1HardClippingErrorFlag */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingFlagPersistent: 1;        /*## attribute Adc4HardClippingFlagPersistent */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingFlagPersistent: 1;        /*## attribute Adc3HardClippingFlagPersistent */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingFlagPersistent: 1;        /*## attribute Adc2HardClippingFlagPersistent */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingFlagPersistent: 1;        /*## attribute Adc1HardClippingFlagPersistent */
   /**
	* BitsName: adc4_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlag: 1;        /*## attribute Adc4ClippingFlag */
   /**
	* BitsName: adc3_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlag: 1;        /*## attribute Adc3ClippingFlag */
   /**
	* BitsName: adc2_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlag: 1;        /*## attribute Adc2ClippingFlag */
   /**
	* BitsName: adc1_clipping_flag
	* Description: ADC status monitoring error flag
	* Clipping detected 
	*  0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlag: 1;        /*## attribute Adc1ClippingFlag */
   /**
	* BitsName: adc4_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagPersistent: 1;        /*## attribute Adc4ClippingFlagPersistent */
   /**
	* BitsName: adc3_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagPersistent: 1;        /*## attribute Adc3ClippingFlagPersistent */
   /**
	* BitsName: adc2_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagPersistent: 1;        /*## attribute Adc2ClippingFlagPersistent */
   /**
	* BitsName: adc1_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagPersistent: 1;        /*## attribute Adc1ClippingFlagPersistent */
   /**
	* BitsName: adc4_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlag: 1;        /*## attribute Adc4NearClippingFlag */
   /**
	* BitsName: adc3_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlag: 1;        /*## attribute Adc3NearClippingFlag */
   /**
	* BitsName: adc2_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlag: 1;        /*## attribute Adc2NearClippingFlag */
   /**
	* BitsName: adc1_near_clipping_flag
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlag: 1;        /*## attribute Adc1NearClippingFlag */
   /**
	* BitsName: adc4_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagPersistent: 1;        /*## attribute Adc4NearClippingFlagPersistent */
   /**
	* BitsName: adc3_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagPersistent: 1;        /*## attribute Adc3NearClippingFlagPersistent */
   /**
	* BitsName: adc2_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagPersistent: 1;        /*## attribute Adc2NearClippingFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag_persistent
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagPersistent: 1;        /*## attribute Adc1NearClippingFlagPersistent */
   /**
	* BitsName: adc4_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4CalErrorFlagPersistent: 1;        /*## attribute Adc4CalErrorFlagPersistent */
   /**
	* BitsName: adc3_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3CalErrorFlagPersistent: 1;        /*## attribute Adc3CalErrorFlagPersistent */
   /**
	* BitsName: adc2_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2CalErrorFlagPersistent: 1;        /*## attribute Adc2CalErrorFlagPersistent */
   /**
	* BitsName: adc1_cal_error_flag_persistent
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1CalErrorFlagPersistent: 1;        /*## attribute Adc1CalErrorFlagPersistent */
}Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusBits_t
* RegisterName: rf_power_down_error_flag_raw_status
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_max_error_flag_tx3
	* Description: Reliability error in TX3 PA
	* 0: no error
	* 1: error reported from sensor.
	*/
    uint32 RfMaxErrorFlagTx3: 1;        /*## attribute RfMaxErrorFlagTx3 */
   /**
	* BitsName: rf_max_error_flag_tx2
	* Description: Reliability error in TX32PA
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 RfMaxErrorFlagTx2: 1;        /*## attribute RfMaxErrorFlagTx2 */
   /**
	* BitsName: rf_max_error_flag_tx1
	* Description: Reliability error in TX1 PA
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 RfMaxErrorFlagTx1: 1;        /*## attribute RfMaxErrorFlagTx1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability error in RX4 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability error in RX3 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability error in RX2 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability error in RX1 LO
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusBits_t
* RegisterName: master_error_flag_masked_status
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 12;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: rx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the RX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 RxBbErrorFlagToMcu: 1;        /*## attribute RxBbErrorFlagToMcu */
   /**
	* BitsName: rx_lo_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from RX LO ( RX LO level too low) 
	* 0: No error
	* 1: LO FS error
	*/
    uint32 RxLoLevelFsErrorFlagToMcu: 1;        /*## attribute RxLoLevelFsErrorFlagToMcu */
   /**
	* BitsName: tx_bb_error_flag_to_mcu
	* Description: RF Ball break detected  in one of the TX 
	* 0: No error
	* 1: Ball break error
	*/
    uint32 TxBbErrorFlagToMcu: 1;        /*## attribute TxBbErrorFlagToMcu */
   /**
	* BitsName: tx_rf_level_fs_error_flag_to_mcu
	* Description: Functional safety error reported from TX PA (TX PA level is too low) 
	* 0: No error
	* 1: TX PA error
	*/
    uint32 TxRfLevelFsErrorFlagToMcu: 1;        /*## attribute TxRfLevelFsErrorFlagToMcu */
   /**
	* BitsName: bb_error_flag_interface_to_mcu
	* Description: RF Ball break detected  in one of the  LO interface
	* 0: No error
	* 1: Ball break error
	*/
    uint32 BbErrorFlagInterfaceToMcu: 1;        /*## attribute BbErrorFlagInterfaceToMcu */
   /**
	* BitsName: mc_pll_dig_freq_error_flag_to_mcu
	* Description: The O/P frequency from main 4.8GHz PLL ( 600/480 MHz) not OK
	* 0: No error
	* 1: Frequency error
	*/
    uint32 McPllDigFreqErrorFlagToMcu: 1;        /*## attribute McPllDigFreqErrorFlagToMcu */
   /**
	* BitsName: mc_pll_lock_error_flag_to_mcu
	* Description: The main 4.8GHz PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 McPllLockErrorFlagToMcu: 1;        /*## attribute McPllLockErrorFlagToMcu */
   /**
	* BitsName: mc_pll_level_error_flag_to_mcu
	* Description: The main 4.8GHz PLL O/P level not OK ( PLL /VCO level is too low or too high) 
	* 0: No error
	* 1: Pll level not OK
	*/
    uint32 McPllLevelErrorFlagToMcu: 1;        /*## attribute McPllLevelErrorFlagToMcu */
   /**
	* BitsName: adc_cal_error_flag_persistent_to_mcu
	* Description: Main ADC calibration out of Sync ( calibaration issue in ADC)
	* 0: No error
	* 1: Calibration issue in main ADC
	*/
    uint32 AdcCalErrorFlagPersistentToMcu: 1;        /*## attribute AdcCalErrorFlagPersistentToMcu */
   /**
	* BitsName: chirp_vco_level_fs_error_flag_to_mcu
	* Description: Chirp VCO level error ( Chirp VCO level is too low) 
	* 0: No error
	* 1: VCO O/P level not OK
	*/
    uint32 ChirpVcoLevelFsErrorFlagToMcu: 1;        /*## attribute ChirpVcoLevelFsErrorFlagToMcu */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_to_mcu
	* Description: Chirp O/P frequency not OK ( freq deviation in chirp digital portion) 
	* 0: No error
	* 1: Frequency error
	*/
    uint32 VcoFreq480ErrorFlagChirpToMcu: 1;        /*## attribute VcoFreq480ErrorFlagChirpToMcu */
   /**
	* BitsName: unlock_error_flag_chirp_to_mcu
	* Description: Chirp  PLL in unlock situation
	* 0: No error
	* 1: Unlock  error
	*/
    uint32 UnlockErrorFlagChirpToMcu: 1;        /*## attribute UnlockErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_dig_lock_step_error_flag
	* Description: Stuck at issue in Chirp digital (lock step mode)
	* 0: No error
	* 1: Lock step out of sync possibly due to a stuck at error
	*/
    uint32 ChirpDigLockStepErrorFlag: 1;        /*## attribute ChirpDigLockStepErrorFlag */
   /**
	* BitsName: global_ldo_1v1_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v1_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.1V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V1LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V1LowErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_high_error_flag_to_mcu
	* Description: Supply low high  in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8HighErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8HighErrorFlagToMcu */
   /**
	* BitsName: global_ldo_1v8_low_error_flag_to_mcu
	* Description: Supply low Error in global LDO 1.8V
	* 0: No error
	* 1: Error
	*/
    uint32 GlobalLdo1V8LowErrorFlagToMcu: 1;        /*## attribute GlobalLdo1V8LowErrorFlagToMcu */
   /**
	* BitsName: supply_low_error_to_mcu
	* Description: Combined supply low error from all local supply monitoring ( supply low indication primarily cover pin failures or local LDO failures, barring chirp and master clock and SSB mod) 
	* 0: No error
	* 1: Error
	*/
    uint32 SupplyLowErrorToMcu: 1;        /*## attribute SupplyLowErrorToMcu */
}Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusBits_t
* RegisterName: supply_error_flag_masked_status
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
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
	* BitsName: global_ldo_1v1_supply_high_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V1SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V1SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_high_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V8SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalLdo1V8SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_dig_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyDigErrorFlagChirpSync: 1;        /*## attribute SupplyDigErrorFlagChirpSync */
   /**
	* BitsName: supply_vco_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyVcoErrorFlagChirpSync: 1;        /*## attribute SupplyVcoErrorFlagChirpSync */
   /**
	* BitsName: supply_pll_error_flag_chirp_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyPllErrorFlagChirpSync: 1;        /*## attribute SupplyPllErrorFlagChirpSync */
   /**
	* BitsName: ser_1v8_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Ser1V8LowErrorFlagSync: 1;        /*## attribute Ser1V8LowErrorFlagSync */
   /**
	* BitsName: csi2_1v1_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Csi21V1LowErrorFlagSync: 1;        /*## attribute Csi21V1LowErrorFlagSync */
   /**
	* BitsName: ser_1v1_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Ser1V1SupplyLowErrorFlagSync: 1;        /*## attribute Ser1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_bias_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 GlobalBiasSupplyLowErrorFlagSync: 1;        /*## attribute GlobalBiasSupplyLowErrorFlagSync */
   /**
	* BitsName: ssb_mod_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SsbMod1V8SupplyLowErrorFlagSync: 1;        /*## attribute SsbMod1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_low_error_flag_interface_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagInterfaceSync: 1;        /*## attribute SupplyLowErrorFlagInterfaceSync */
   /**
	* BitsName: supply_low_error_flag_adc34_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagAdc34Sync: 1;        /*## attribute SupplyLowErrorFlagAdc34Sync */
   /**
	* BitsName: supply_low_error_flag_adc12_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagAdc12Sync: 1;        /*## attribute SupplyLowErrorFlagAdc12Sync */
   /**
	* BitsName: mc_1v8_supply_low_error_flag_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Mc1V8SupplyLowErrorFlagSync: 1;        /*## attribute Mc1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx4_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V8LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx4_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 Supply1V1LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_low_error_flag_tx3_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx3Sync: 1;        /*## attribute SupplyLowErrorFlagTx3Sync */
   /**
	* BitsName: supply_low_error_flag_tx2_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx2Sync: 1;        /*## attribute SupplyLowErrorFlagTx2Sync */
   /**
	* BitsName: supply_low_error_flag_tx1_sync
	* Description: 0: no error reported
	* 1: error reported
	*/
    uint32 SupplyLowErrorFlagTx1Sync: 1;        /*## attribute SupplyLowErrorFlagTx1Sync */
}Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusBits_t
* RegisterName: tx_error_flag_masked_status
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error
	* Description: Functional safety error flag
	* 
	* TX3  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx31V8Error: 1;        /*## attribute SupplyLowErrorFlagTx31V8Error */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error
	* Description: Functional safety error flag
	* 
	* Functional safety error flag
	* 
	* TX2  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx21V8Error: 1;        /*## attribute SupplyLowErrorFlagTx21V8Error */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error
	* Description: TX1  supply low error (1V8)
	* 0: Supply OK
	* 1: latched Supply low error
	*/
    uint32 SupplyLowErrorFlagTx11V8Error: 1;        /*## attribute SupplyLowErrorFlagTx11V8Error */
   /**
	* BitsName: tx3_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX3 RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfReliabilityLevelError: 1;        /*## attribute Tx3RfReliabilityLevelError */
   /**
	* BitsName: tx2_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX2  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfReliabilityLevelError: 1;        /*## attribute Tx2RfReliabilityLevelError */
   /**
	* BitsName: tx1_rf_reliability_level_error
	* Description: Reliability  monitoring error flag
	* 
	* TX1  RF level reached beyond reliability limits  If the value is above this limit, a transmitter power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfReliabilityLevelError: 1;        /*## attribute Tx1RfReliabilityLevelError */
   /**
	* BitsName: tx3_rf_level_high_error
	* Description: Reliability  monitoring error flag
	* 
	* TX3  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelHighError: 1;        /*## attribute Tx3RfLevelHighError */
   /**
	* BitsName: tx2_rf_level_high_error
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelHighError: 1;        /*## attribute Tx2RfLevelHighError */
   /**
	* BitsName: tx1_rf_level_high_error
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelHighError: 1;        /*## attribute Tx1RfLevelHighError */
   /**
	* BitsName: tx3_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX3 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelLowError: 1;        /*## attribute Tx3RfLevelLowError */
   /**
	* BitsName: tx2_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX2 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelLowError: 1;        /*## attribute Tx2RfLevelLowError */
   /**
	* BitsName: tx1_rf_level_low_error
	* Description: Status monitoring error flag
	* 
	* TX1 RF level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for transmitter status and set the power level to acceptable limits. Not part of functional safety
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelLowError: 1;        /*## attribute Tx1RfLevelLowError */
   /**
	* BitsName: tx3_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX3. TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3RfLevelFsError: 1;        /*## attribute Tx3RfLevelFsError */
   /**
	* BitsName: tx2_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX2 TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2RfLevelFsError: 1;        /*## attribute Tx2RfLevelFsError */
   /**
	* BitsName: tx1_rf_level_fs_error
	* Description: Functional safety error flag
	* 
	* Functional safety error in TX1  TX PA level too low
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1RfLevelFsError: 1;        /*## attribute Tx1RfLevelFsError */
   /**
	* BitsName: tx3_temp_error
	* Description: Status monitoring error flag
	* 
	* TX3 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3TempError: 1;        /*## attribute Tx3TempError */
   /**
	* BitsName: tx2_temp_error
	* Description: Status monitoring error flag
	* 
	* TX2 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2TempError: 1;        /*## attribute Tx2TempError */
   /**
	* BitsName: tx1_temp_error
	* Description: Status monitoring error flag
	* 
	* TX1 Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.  If this flag is set high, then an automatic shutdown of transmitter is initiated by Dolphin./
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1TempError: 1;        /*## attribute Tx1TempError */
   /**
	* BitsName: tx3_bb_error
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx3BbError: 1;        /*## attribute Tx3BbError */
   /**
	* BitsName: tx2_bb_error
	* Description: Functional safety error flag
	* 
	* 
	* TX2 RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx2BbError: 1;        /*## attribute Tx2BbError */
   /**
	* BitsName: tx1_bb_error
	* Description: Functional safety error flag
	* 
	* TX1  RF connectivity to  external antenna port is  not working.
	* 0: No error
	* 1: Error
	*/
    uint32 Tx1BbError: 1;        /*## attribute Tx1BbError */
}Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusBits_t
* RegisterName: rx_error_flag_masked_status
* 
* AddressRange: 0x070 - 0x074
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx41V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx31V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx21V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v8 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V8Masked: 1;        /*## attribute SupplyLowErrorFlagRx11V8Masked */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx41V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx41V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX3
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx31V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx31V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX2
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx21V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx21V1Masked */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_masked
	* Description: Functional safety error flag
	* 
	* Supply 1v1 low error RX1
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagRx11V1Masked: 1;        /*## attribute SupplyLowErrorFlagRx11V1Masked */
   /**
	* BitsName: lo_max_error_flag_rx4_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX14 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx4Masked: 1;        /*## attribute LoMaxErrorFlagRx4Masked */
   /**
	* BitsName: lo_max_error_flag_rx3_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX3  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx3Masked: 1;        /*## attribute LoMaxErrorFlagRx3Masked */
   /**
	* BitsName: lo_max_error_flag_rx2_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX2 LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx2Masked: 1;        /*## attribute LoMaxErrorFlagRx2Masked */
   /**
	* BitsName: lo_max_error_flag_rx1_masked
	* Description: Reliability monitoring error flag
	* 
	* LO  level reached beyond reliability limits  If the value is above this limit, a receiver  power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* RX1  LO level too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMaxErrorFlagRx1Masked: 1;        /*## attribute LoMaxErrorFlagRx1Masked */
   /**
	* BitsName: lo_high_error_flag_rx4_masked
	* Description: Status monitoring error flag
	* 
	*  RF level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx4Masked: 1;        /*## attribute LoHighErrorFlagRx4Masked */
   /**
	* BitsName: lo_high_error_flag_rx3_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx3Masked: 1;        /*## attribute LoHighErrorFlagRx3Masked */
   /**
	* BitsName: lo_high_error_flag_rx2_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx2Masked: 1;        /*## attribute LoHighErrorFlagRx2Masked */
   /**
	* BitsName: lo_high_error_flag_rx1_masked
	* Description: Status monitoring error flag
	* 
	* LO level reached beyond a programmed high level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX1  LO level going high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoHighErrorFlagRx1Masked: 1;        /*## attribute LoHighErrorFlagRx1Masked */
   /**
	* BitsName: lo_low_error_flag_rx4_masked
	* Description: Status monitoring error flag
	* 
	* RX4 LO level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX4  LO level low
	* 0: Error not masked
	* 1: Error masked
	*/
    uint32 LoLowErrorFlagRx4Masked: 1;        /*## attribute LoLowErrorFlagRx4Masked */
   /**
	* BitsName: lo_low_error_flag_rx3_masked
	* Description: Status monitoring error flag
	* 
	* RX3 Lo level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX3  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx3Masked: 1;        /*## attribute LoLowErrorFlagRx3Masked */
   /**
	* BitsName: lo_low_error_flag_rx2_masked
	* Description: Status monitoring error flag
	* 
	* RX2 Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. Not part of functional safety
	* RX2  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx2Masked: 1;        /*## attribute LoLowErrorFlagRx2Masked */
   /**
	* BitsName: lo_low_error_flag_rx1_masked
	* Description: Status monitoring error flag
	* 
	* Lo level  reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for receiver  status and set the power level to acceptable limits. RX1  LO level low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoLowErrorFlagRx1Masked: 1;        /*## attribute LoLowErrorFlagRx1Masked */
   /**
	* BitsName: lo_min_error_flag_rx4_masked
	* Description: Functional safety error flag
	* 
	* Functional safety error in receiver
	* Supply 1v1 low error RX4
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx4Masked: 1;        /*## attribute LoMinErrorFlagRx4Masked */
   /**
	* BitsName: lo_min_error_flag_rx3_masked
	* Description: Functional safety error flag
	* 
	* RX3 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx3Masked: 1;        /*## attribute LoMinErrorFlagRx3Masked */
   /**
	* BitsName: lo_min_error_flag_rx2_masked
	* Description: Functional safety error flag
	* 
	* RX2 LO level too low
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx2Masked: 1;        /*## attribute LoMinErrorFlagRx2Masked */
   /**
	* BitsName: lo_min_error_flag_rx1_masked
	* Description: Functional safety error flag
	* 
	* RX1 LO level too low
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LoMinErrorFlagRx1Masked: 1;        /*## attribute LoMinErrorFlagRx1Masked */
   /**
	* BitsName: bb_error_flag_rx4_masked
	* Description: Functional safety error flag
	* 
	* RX4 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx4Masked: 1;        /*## attribute BbErrorFlagRx4Masked */
   /**
	* BitsName: bb_error_flag_rx3_masked
	* Description: Functional safety error flag
	* 
	* RX3 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx3Masked: 1;        /*## attribute BbErrorFlagRx3Masked */
   /**
	* BitsName: bb_error_flag_rx2_masked
	* Description: Functional safety error flag
	* 
	* RX2 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx2Masked: 1;        /*## attribute BbErrorFlagRx2Masked */
   /**
	* BitsName: bb_error_flag_rx1_masked
	* Description: Functional safety error flag
	* 
	* RX1 RF connectivity to  external antenna port is  not working.
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagRx1Masked: 1;        /*## attribute BbErrorFlagRx1Masked */
}Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusBits_t
* RegisterName: chirp_error_flag_masked_status
* 
* AddressRange: 0x074 - 0x078
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_seq_active, safety_monitoring, window_active detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to PLL error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v8) to VCO error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* Supply low (1v1) to digital logic error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* VCO O/P frequency to the chirp digital logic is beyond programmable limits.   This is an average frequency counter.  The  frequency counter op
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VcoFreq480ErrorFlagChirp: 1;        /*## attribute VcoFreq480ErrorFlagChirp */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability error flag
	* 
	* VCO O/P  level reached beyond reliability limits  If the value is above this limit, a chirp   power down is initiated by the Dolphin hardware.  This flag is not considered for functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Functional safety error flag
	* 
	* 
	* Functional safety error in Chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level  reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp   status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* VCO level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached above  a programmed high   level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Status monitoring error flag
	* 
	* Vtune level reached below  a programmed low  level  limits This flag is meant for status monitoring.  Once this level is reached  an action is expected from MCU to check for chirp  status and set the power level to acceptable limits. Not part of functional safety
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp
	* Description: Status monitoring error flag
	* 
	* Temperature is too high if operation continue, then this may result in reliability issue.  Programmable threshold  through SPI.
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 MaxTempErrorFlagChirp: 1;        /*## attribute MaxTempErrorFlagChirp */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp PLL in un lock condition. Indicate a functional safety error in chirp
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Functional safety error flag
	* 
	* Chirp digital logic stuck at or transient logic failure. Indicate a functional safety error in chirp digital portion
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
}Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusBits_t
* RegisterName: mc_lo_error_flag_masked_status
* 
* AddressRange: 0x078 - 0x07C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write Error 
	* 0 : No Error
	* 1 : Error reported
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: Supply low error from LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: RF connectivity issues in LO interface
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: Supply error form MC (1V8)
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: MC digital O.P frequency not in range
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Pll in un lock condition
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: PLL level  is too low or too high
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_pll_freq_error_flag
	* Description: MC PLL calibration error
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 McPllFreqErrorFlag: 1;        /*## attribute McPllFreqErrorFlag */
}Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusBits_t
* RegisterName: adc_error_flag_masked_status
* 
* AddressRange: 0x07C - 0x080
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_masked
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC34
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc341V8Masked: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Masked */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_masked
	* Description: Functional safety related error
	* 
	* Supply low (1v8) ADC12
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 SupplyLowErrorFlagAdc121V8Masked: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Masked */
   /**
	* BitsName: adc4_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingErrorFlagMasked: 1;        /*## attribute Adc4HardClippingErrorFlagMasked */
   /**
	* BitsName: adc3_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingErrorFlagMasked: 1;        /*## attribute Adc3HardClippingErrorFlagMasked */
   /**
	* BitsName: adc2_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingErrorFlagMasked: 1;        /*## attribute Adc2HardClippingErrorFlagMasked */
   /**
	* BitsName: adc1_hard_clipping_error_flag_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingErrorFlagMasked: 1;        /*## attribute Adc1HardClippingErrorFlagMasked */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4HardClippingFlagPersistentMasked: 1;        /*## attribute Adc4HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3HardClippingFlagPersistentMasked: 1;        /*## attribute Adc3HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2HardClippingFlagPersistentMasked: 1;        /*## attribute Adc2HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Hard clipping detected and stays 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1HardClippingFlagPersistentMasked: 1;        /*## attribute Adc1HardClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagMasked: 1;        /*## attribute Adc4ClippingFlagMasked */
   /**
	* BitsName: adc3_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagMasked: 1;        /*## attribute Adc3ClippingFlagMasked */
   /**
	* BitsName: adc2_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagMasked: 1;        /*## attribute Adc2ClippingFlagMasked */
   /**
	* BitsName: adc1_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* Clipping detected 
	*  0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagMasked: 1;        /*## attribute Adc1ClippingFlagMasked */
   /**
	* BitsName: adc4_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4ClippingFlagPersistentMasked: 1;        /*## attribute Adc4ClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3ClippingFlagPersistentMasked: 1;        /*## attribute Adc3ClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2ClippingFlagPersistentMasked: 1;        /*## attribute Adc2ClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* Clipping detected and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1ClippingFlagPersistentMasked: 1;        /*## attribute Adc1ClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagMasked: 1;        /*## attribute Adc4NearClippingFlagMasked */
   /**
	* BitsName: adc3_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagMasked: 1;        /*## attribute Adc3NearClippingFlagMasked */
   /**
	* BitsName: adc2_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagMasked: 1;        /*## attribute Adc2NearClippingFlagMasked */
   /**
	* BitsName: adc1_near_clipping_flag_masked
	* Description: ADC status monitoring error flag
	* near clipping detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagMasked: 1;        /*## attribute Adc1NearClippingFlagMasked */
   /**
	* BitsName: adc4_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4NearClippingFlagPersistentMasked: 1;        /*## attribute Adc4NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc3_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3NearClippingFlagPersistentMasked: 1;        /*## attribute Adc3NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc2_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2NearClippingFlagPersistentMasked: 1;        /*## attribute Adc2NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc1_near_clipping_flag_persistent_masked
	* Description: ADC status monitoring error flag
	* near clipping detected  and persistent
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1NearClippingFlagPersistentMasked: 1;        /*## attribute Adc1NearClippingFlagPersistentMasked */
   /**
	* BitsName: adc4_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc4CalErrorFlagPersistentMasked: 1;        /*## attribute Adc4CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc3_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc3CalErrorFlagPersistentMasked: 1;        /*## attribute Adc3CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc2_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc2CalErrorFlagPersistentMasked: 1;        /*## attribute Adc2CalErrorFlagPersistentMasked */
   /**
	* BitsName: adc1_cal_error_flag_persistent_masked
	* Description: Functional safety error flag
	* Calibaration error detected 
	* 0: no error
	* 1: error reported from sensor
	*/
    uint32 Adc1CalErrorFlagPersistentMasked: 1;        /*## attribute Adc1CalErrorFlagPersistentMasked */
}Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusBits_t
* RegisterName: rf_power_down_error_flag_masked_status
* 
* AddressRange: 0x080 - 0x084
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_max_error_flag_tx3
	* Description: Reliability issue in TX3
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx3: 1;        /*## attribute RfMaxErrorFlagTx3 */
   /**
	* BitsName: rf_max_error_flag_tx2
	* Description: Reliability issue in TX2
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx2: 1;        /*## attribute RfMaxErrorFlagTx2 */
   /**
	* BitsName: rf_max_error_flag_tx1
	* Description: Reliability issue in TX1
	* 0: No error
	* 1: Error
	*/
    uint32 RfMaxErrorFlagTx1: 1;        /*## attribute RfMaxErrorFlagTx1 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: lo_max_error_flag_rx4
	* Description: Reliability issue in RX4
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx4: 1;        /*## attribute LoMaxErrorFlagRx4 */
   /**
	* BitsName: lo_max_error_flag_rx3
	* Description: Reliability issue in RX3
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx3: 1;        /*## attribute LoMaxErrorFlagRx3 */
   /**
	* BitsName: lo_max_error_flag_rx2
	* Description: Reliability issue in RX2
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx2: 1;        /*## attribute LoMaxErrorFlagRx2 */
   /**
	* BitsName: lo_max_error_flag_rx1
	* Description: Reliability issue in RX1
	* 0: No error
	* 1: Error
	*/
    uint32 LoMaxErrorFlagRx1: 1;        /*## attribute LoMaxErrorFlagRx1 */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Reliability issue in Chirp
	* 0: No error
	* 1: Error
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusSupplyRegBits_t
* RegisterName: fit_status_supply_reg
* 
* AddressRange: 0x084 - 0x088
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: global_ldo_1v1_supply_high_error_flag_sync
	* Description: Global LDO 1V1 supply  high sensor  status
	* 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V1SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v1_supply_low_error_flag_sync
	* Description: Global LDO 1V1 supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V1SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_high_error_flag_sync
	* Description: Global LDO 1V8 supply  high sensor  status
	* 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V8SupplyHighErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyHighErrorFlagSync */
   /**
	* BitsName: global_ldo_1v8_supply_low_error_flag_sync
	* Description: Global LDO 1V8 supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalLdo1V8SupplyLowErrorFlagSync: 1;        /*## attribute GlobalLdo1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_dig_error_flag_chirp_sync
	* Description: Chirp digital  supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyDigErrorFlagChirpSync: 1;        /*## attribute SupplyDigErrorFlagChirpSync */
   /**
	* BitsName: supply_vco_error_flag_chirp_sync
	* Description: Chirp VCO   supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyVcoErrorFlagChirpSync: 1;        /*## attribute SupplyVcoErrorFlagChirpSync */
   /**
	* BitsName: supply_pll_error_flag_chirp_sync
	* Description: Chirp PLL   supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyPllErrorFlagChirpSync: 1;        /*## attribute SupplyPllErrorFlagChirpSync */
   /**
	* BitsName: ser_1v8_low_error_flag_sync
	* Description: Serializer 1V8  supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Ser1V8LowErrorFlagSync: 1;        /*## attribute Ser1V8LowErrorFlagSync */
   /**
	* BitsName: csi2_1v1_low_error_flag_sync
	* Description: Serializer CSI2  supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Csi21V1LowErrorFlagSync: 1;        /*## attribute Csi21V1LowErrorFlagSync */
   /**
	* BitsName: ser_1v1_supply_low_error_flag_sync
	* Description: Serializer digital   supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Ser1V1SupplyLowErrorFlagSync: 1;        /*## attribute Ser1V1SupplyLowErrorFlagSync */
   /**
	* BitsName: global_bias_supply_low_error_flag_sync
	* Description: Global bias supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 GlobalBiasSupplyLowErrorFlagSync: 1;        /*## attribute GlobalBiasSupplyLowErrorFlagSync */
   /**
	* BitsName: ssb_mod_1v8_supply_low_error_flag_sync
	* Description: SSB mod supply low sensor error status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SsbMod1V8SupplyLowErrorFlagSync: 1;        /*## attribute SsbMod1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_low_error_flag_interface_sync
	* Description: LO interface Supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagInterfaceSync: 1;        /*## attribute SupplyLowErrorFlagInterfaceSync */
   /**
	* BitsName: supply_low_error_flag_adc34_sync
	* Description: ADC34 Supply low sensor  status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc34Sync: 1;        /*## attribute SupplyLowErrorFlagAdc34Sync */
   /**
	* BitsName: supply_low_error_flag_adc12_sync
	* Description: ADC 12 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc12Sync: 1;        /*## attribute SupplyLowErrorFlagAdc12Sync */
   /**
	* BitsName: mc_1v8_supply_low_error_flag_sync
	* Description: Master controller supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Mc1V8SupplyLowErrorFlagSync: 1;        /*## attribute Mc1V8SupplyLowErrorFlagSync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx4_sync
	* Description: RX4 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx3_sync
	* Description: RX3 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx2_sync
	* Description: RX2 supply1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v8_low_error_flag_rx1_sync
	* Description: RX1 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V8LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V8LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx4_sync
	* Description: RX4 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx4Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx4Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx3_sync
	* Description: RX3 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx3Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx3Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx2_sync
	* Description: RX2 supply1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx2Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx2Sync */
   /**
	* BitsName: supply_1v1_low_error_flag_rx1_sync
	* Description: RX1 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Supply1V1LowErrorFlagRx1Sync: 1;        /*## attribute Supply1V1LowErrorFlagRx1Sync */
   /**
	* BitsName: supply_low_error_flag_tx3_sync
	* Description: TX3 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx3Sync: 1;        /*## attribute SupplyLowErrorFlagTx3Sync */
   /**
	* BitsName: supply_low_error_flag_tx2_sync
	* Description: TX2 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx2Sync: 1;        /*## attribute SupplyLowErrorFlagTx2Sync */
   /**
	* BitsName: supply_low_error_flag_tx1_sync
	* Description: TX1 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx1Sync: 1;        /*## attribute SupplyLowErrorFlagTx1Sync */
}Nxp_Tef810x_Mod18_FitStatusSupplyRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusTxRegBits_t
* RegisterName: fit_status_tx_reg
* 
* AddressRange: 0x088 - 0x08C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_error
	* Description: TX3 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx31V8Error: 1;        /*## attribute SupplyLowErrorFlagTx31V8Error */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_error
	* Description: TX2 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx21V8Error: 1;        /*## attribute SupplyLowErrorFlagTx21V8Error */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_error
	* Description: TX1 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagTx11V8Error: 1;        /*## attribute SupplyLowErrorFlagTx11V8Error */
   /**
	* BitsName: tx3_rf_reliability_level_error
	* Description: TX3 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfReliabilityLevelError: 1;        /*## attribute Tx3RfReliabilityLevelError */
   /**
	* BitsName: tx2_rf_reliability_level_error
	* Description: TX2 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfReliabilityLevelError: 1;        /*## attribute Tx2RfReliabilityLevelError */
   /**
	* BitsName: tx1_rf_reliability_level_error
	* Description: TX1 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfReliabilityLevelError: 1;        /*## attribute Tx1RfReliabilityLevelError */
   /**
	* BitsName: tx3_rf_level_high_error
	* Description: TX3 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelHighError: 1;        /*## attribute Tx3RfLevelHighError */
   /**
	* BitsName: tx2_rf_level_high_error
	* Description: TX2  level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelHighError: 1;        /*## attribute Tx2RfLevelHighError */
   /**
	* BitsName: tx1_rf_level_high_error
	* Description: TX1 level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelHighError: 1;        /*## attribute Tx1RfLevelHighError */
   /**
	* BitsName: tx3_rf_level_low_error
	* Description: TX3 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelLowError: 1;        /*## attribute Tx3RfLevelLowError */
   /**
	* BitsName: tx2_rf_level_low_error
	* Description: TX2  level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelLowError: 1;        /*## attribute Tx2RfLevelLowError */
   /**
	* BitsName: tx1_rf_level_low_error
	* Description: TX1 level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelLowError: 1;        /*## attribute Tx1RfLevelLowError */
   /**
	* BitsName: tx3_rf_level_fs_error
	* Description: TX3 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3RfLevelFsError: 1;        /*## attribute Tx3RfLevelFsError */
   /**
	* BitsName: tx2_rf_level_fs_error
	* Description: TX2  level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2RfLevelFsError: 1;        /*## attribute Tx2RfLevelFsError */
   /**
	* BitsName: tx1_rf_level_fs_error
	* Description: TX1 level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1RfLevelFsError: 1;        /*## attribute Tx1RfLevelFsError */
   /**
	* BitsName: tx3_temp_error
	* Description: TX3  temperature   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3TempError: 1;        /*## attribute Tx3TempError */
   /**
	* BitsName: tx2_temp_error
	* Description: TX2 temperature sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2TempError: 1;        /*## attribute Tx2TempError */
   /**
	* BitsName: tx1_temp_error
	* Description: TX1 temperature sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1TempError: 1;        /*## attribute Tx1TempError */
   /**
	* BitsName: tx3_bb_error
	* Description: TX3  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx3BbError: 1;        /*## attribute Tx3BbError */
   /**
	* BitsName: tx2_bb_error
	* Description: TX2 BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx2BbError: 1;        /*## attribute Tx2BbError */
   /**
	* BitsName: tx1_bb_error
	* Description: TX BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Tx1BbError: 1;        /*## attribute Tx1BbError */
}Nxp_Tef810x_Mod18_FitStatusTxRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusRxRegBits_t
* RegisterName: fit_status_rx_reg
* 
* AddressRange: 0x08C - 0x090
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8
	* Description: RX4 supply 1v8 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx41V8: 1;        /*## attribute SupplyLowErrorFlagRx41V8 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8
	* Description: RX3 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx31V8: 1;        /*## attribute SupplyLowErrorFlagRx31V8 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8
	* Description: RX2 supply1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx21V8: 1;        /*## attribute SupplyLowErrorFlagRx21V8 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8
	* Description: RX1 supply 1v8  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx11V8: 1;        /*## attribute SupplyLowErrorFlagRx11V8 */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1
	* Description: RX4 supply 1v1 low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx41V1: 1;        /*## attribute SupplyLowErrorFlagRx41V1 */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1
	* Description: RX3 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx31V1: 1;        /*## attribute SupplyLowErrorFlagRx31V1 */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1
	* Description: RX2 supply1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx21V1: 1;        /*## attribute SupplyLowErrorFlagRx21V1 */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1
	* Description: RX1 supply 1v1  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagRx11V1: 1;        /*## attribute SupplyLowErrorFlagRx11V1 */
   /**
	* BitsName: rx4_lo_reliability_level_error
	* Description: RX4 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoReliabilityLevelError: 1;        /*## attribute Rx4LoReliabilityLevelError */
   /**
	* BitsName: rx3_lo_reliability_level_error
	* Description: RX3 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoReliabilityLevelError: 1;        /*## attribute Rx3LoReliabilityLevelError */
   /**
	* BitsName: rx2_lo_reliability_level_error
	* Description: RX2 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoReliabilityLevelError: 1;        /*## attribute Rx2LoReliabilityLevelError */
   /**
	* BitsName: rx1_lo_reliability_level_error
	* Description: RX1 reliability level sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoReliabilityLevelError: 1;        /*## attribute Rx1LoReliabilityLevelError */
   /**
	* BitsName: rx4_lo_level_high_error
	* Description: RX4 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelHighError: 1;        /*## attribute Rx4LoLevelHighError */
   /**
	* BitsName: rx3_lo_level_high_error
	* Description: RX3 level high   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelHighError: 1;        /*## attribute Rx3LoLevelHighError */
   /**
	* BitsName: rx2_lo_level_high_error
	* Description: RX2  level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelHighError: 1;        /*## attribute Rx2LoLevelHighError */
   /**
	* BitsName: rx1_lo_level_high_error
	* Description: RX1 level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelHighError: 1;        /*## attribute Rx1LoLevelHighError */
   /**
	* BitsName: rx4_lo_level_low_error
	* Description: RX4 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelLowError: 1;        /*## attribute Rx4LoLevelLowError */
   /**
	* BitsName: rx3_lo_level_low_error
	* Description: RX3 level low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelLowError: 1;        /*## attribute Rx3LoLevelLowError */
   /**
	* BitsName: rx2_lo_level_low_error
	* Description: RX2  level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelLowError: 1;        /*## attribute Rx2LoLevelLowError */
   /**
	* BitsName: rx1_lo_level_low_error
	* Description: RX1 level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelLowError: 1;        /*## attribute Rx1LoLevelLowError */
   /**
	* BitsName: rx4_lo_level_fs_error
	* Description: RX4 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4LoLevelFsError: 1;        /*## attribute Rx4LoLevelFsError */
   /**
	* BitsName: rx3_lo_level_fs_error
	* Description: RX3 level too low   sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3LoLevelFsError: 1;        /*## attribute Rx3LoLevelFsError */
   /**
	* BitsName: rx2_lo_level_fs_error
	* Description: RX2  level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2LoLevelFsError: 1;        /*## attribute Rx2LoLevelFsError */
   /**
	* BitsName: rx1_lo_level_fs_error
	* Description: RX1 level too low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1LoLevelFsError: 1;        /*## attribute Rx1LoLevelFsError */
   /**
	* BitsName: rx4_bb_error
	* Description: RX4  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx4BbError: 1;        /*## attribute Rx4BbError */
   /**
	* BitsName: rx3_bb_error
	* Description: RX3  BB detect    sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx3BbError: 1;        /*## attribute Rx3BbError */
   /**
	* BitsName: rx2_bb_error
	* Description: RX2 BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx2BbError: 1;        /*## attribute Rx2BbError */
   /**
	* BitsName: rx1_bb_error
	* Description: RX1  BB detect sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Rx1BbError: 1;        /*## attribute Rx1BbError */
}Nxp_Tef810x_Mod18_FitStatusRxRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusChirpRegBits_t
* RegisterName: fit_status_chirp_reg
* 
* AddressRange: 0x090 - 0x094
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp
	* Description: Functional safety error flag
	* 
	* Stuck on chirp_start, chirp_seq_active, safety_monitoring, window_active is monitored from CC to make sure that the main control signals from chirp is working properly. The value
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 InterfaceStuckFlagChirp: 1;        /*## attribute InterfaceStuckFlagChirp */
   /**
	* BitsName: supply_pll_error_flag_chirp
	* Description: Chirp PLL supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyPllErrorFlagChirp: 1;        /*## attribute SupplyPllErrorFlagChirp */
   /**
	* BitsName: supply_vco_error_flag_chirp
	* Description: Chirp VCO supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyVcoErrorFlagChirp: 1;        /*## attribute SupplyVcoErrorFlagChirp */
   /**
	* BitsName: supply_dig_error_flag_chirp
	* Description: Chirp digital  supply  low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyDigErrorFlagChirp: 1;        /*## attribute SupplyDigErrorFlagChirp */
   /**
	* BitsName: vco_freq_480_error_flag_chirp
	* Description: Chirp freq counter sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VcoFreq480ErrorFlagChirp: 1;        /*## attribute VcoFreq480ErrorFlagChirp */
   /**
	* BitsName: level_max_error_flag_chirp
	* Description: Chirp reliability sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelMaxErrorFlagChirp: 1;        /*## attribute LevelMaxErrorFlagChirp */
   /**
	* BitsName: level_min_error_flag_chirp
	* Description: Chirp functional safety sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelMinErrorFlagChirp: 1;        /*## attribute LevelMinErrorFlagChirp */
   /**
	* BitsName: level_high_error_flag_chirp_sync
	* Description: Chirp level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelHighErrorFlagChirpSync: 1;        /*## attribute LevelHighErrorFlagChirpSync */
   /**
	* BitsName: level_low_error_flag_chirp_sync
	* Description: Chirp level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LevelLowErrorFlagChirpSync: 1;        /*## attribute LevelLowErrorFlagChirpSync */
   /**
	* BitsName: vtune_high_error_flag_chirp_sync
	* Description: Chirp Vtune level high sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VtuneHighErrorFlagChirpSync: 1;        /*## attribute VtuneHighErrorFlagChirpSync */
   /**
	* BitsName: vtune_low_error_flag_chirp_sync
	* Description: Chirp Vtune level low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 VtuneLowErrorFlagChirpSync: 1;        /*## attribute VtuneLowErrorFlagChirpSync */
   /**
	* BitsName: max_temp_error_flag_chirp_sync
	* Description: Chirp temp sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 MaxTempErrorFlagChirpSync: 1;        /*## attribute MaxTempErrorFlagChirpSync */
   /**
	* BitsName: unlock_error_flag_chirp_sync
	* Description: Chirp PLL un lock sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 UnlockErrorFlagChirpSync: 1;        /*## attribute UnlockErrorFlagChirpSync */
   /**
	* BitsName: lock_step_error_flag_chirp_sync
	* Description: Chirp lock step digital interface status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 LockStepErrorFlagChirpSync: 1;        /*## attribute LockStepErrorFlagChirpSync */
}Nxp_Tef810x_Mod18_FitStatusChirpRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusMcLoRegBits_t
* RegisterName: fit_status_mc_lo_reg
* 
* AddressRange: 0x094 - 0x098
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rd_crc_error_flag
	* Description: CRC Read  
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 RdCrcErrorFlag: 1;        /*## attribute RdCrcErrorFlag */
   /**
	* BitsName: wr_crc_error_flag
	* Description: CRC Write 
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 WrCrcErrorFlag: 1;        /*## attribute WrCrcErrorFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: supply_low_error_flag_interface_1v1
	* Description: LO interface supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagInterface1V1: 1;        /*## attribute SupplyLowErrorFlagInterface1V1 */
   /**
	* BitsName: bb_error_flag_interface
	* Description: LO interface ball break sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 BbErrorFlagInterface: 1;        /*## attribute BbErrorFlagInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: supply_low_error_flag_mc_1v8
	* Description: master clock supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagMc1V8: 1;        /*## attribute SupplyLowErrorFlagMc1V8 */
   /**
	* BitsName: dig_freq_error_flag_masterclk
	* Description: Master clock freq counter sensor status ( only interface covered). Any variation in Master clock frequency, during chirping is measured and indicated by serialiser throught this flag.
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 DigFreqErrorFlagMasterclk: 1;        /*## attribute DigFreqErrorFlagMasterclk */
   /**
	* BitsName: mc_pll_lock_error_flag
	* Description: Master clock pll unlock detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllLockErrorFlag: 1;        /*## attribute McPllLockErrorFlag */
   /**
	* BitsName: mc_pll_level_error_flag
	* Description: Master clock pll level  detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllLevelErrorFlag: 1;        /*## attribute McPllLevelErrorFlag */
   /**
	* BitsName: mc_pll_freq_error_flag
	* Description: Master clock pll freq error   detection sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 McPllFreqErrorFlag: 1;        /*## attribute McPllFreqErrorFlag */
}Nxp_Tef810x_Mod18_FitStatusMcLoRegBits_t;
    /**
* Nxp_Tef810x_Mod18_FitStatusAdcRegBits_t
* RegisterName: fit_status_adc_reg
* 
* AddressRange: 0x098 - 0x09C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_low_error_flag_adc34
	* Description: ADC34 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc34: 1;        /*## attribute SupplyLowErrorFlagAdc34 */
   /**
	* BitsName: supply_low_error_flag_adc12
	* Description: ADC12 supply low sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 SupplyLowErrorFlagAdc12: 1;        /*## attribute SupplyLowErrorFlagAdc12 */
   /**
	* BitsName: adc4_hard_clipping_error_flag
	* Description: ADC4 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4HardClippingErrorFlag: 1;        /*## attribute Adc4HardClippingErrorFlag */
   /**
	* BitsName: adc3_hard_clipping_error_flag
	* Description: ADC3 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3HardClippingErrorFlag: 1;        /*## attribute Adc3HardClippingErrorFlag */
   /**
	* BitsName: adc2_hard_clipping_error_flag
	* Description: ADC2 hard clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2HardClippingErrorFlag: 1;        /*## attribute Adc2HardClippingErrorFlag */
   /**
	* BitsName: adc1_hard_clipping_error_flag
	* Description: ADC1 hard clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1HardClippingErrorFlag: 1;        /*## attribute Adc1HardClippingErrorFlag */
   /**
	* BitsName: adc4_hard_clipping_flag_persistent
	* Description: ADC4 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4HardClippingFlagPersistent: 1;        /*## attribute Adc4HardClippingFlagPersistent */
   /**
	* BitsName: adc3_hard_clipping_flag_persistent
	* Description: ADC3 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3HardClippingFlagPersistent: 1;        /*## attribute Adc3HardClippingFlagPersistent */
   /**
	* BitsName: adc2_hard_clipping_flag_persistent
	* Description: ADC2 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2HardClippingFlagPersistent: 1;        /*## attribute Adc2HardClippingFlagPersistent */
   /**
	* BitsName: adc1_hard_clipping_flag_persistent
	* Description: ADC1 hard clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1HardClippingFlagPersistent: 1;        /*## attribute Adc1HardClippingFlagPersistent */
   /**
	* BitsName: adc4_clipping_flag
	* Description: ADC4  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4ClippingFlag: 1;        /*## attribute Adc4ClippingFlag */
   /**
	* BitsName: adc3_clipping_flag
	* Description: ADC3  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3ClippingFlag: 1;        /*## attribute Adc3ClippingFlag */
   /**
	* BitsName: adc2_clipping_flag
	* Description: ADC2  clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2ClippingFlag: 1;        /*## attribute Adc2ClippingFlag */
   /**
	* BitsName: adc1_clipping_flag
	* Description: ADC1  clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1ClippingFlag: 1;        /*## attribute Adc1ClippingFlag */
   /**
	* BitsName: adc4_clipping_flag_persistent
	* Description: ADC4  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4ClippingFlagPersistent: 1;        /*## attribute Adc4ClippingFlagPersistent */
   /**
	* BitsName: adc3_clipping_flag_persistent
	* Description: ADC3  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3ClippingFlagPersistent: 1;        /*## attribute Adc3ClippingFlagPersistent */
   /**
	* BitsName: adc2_clipping_flag_persistent
	* Description: ADC2  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2ClippingFlagPersistent: 1;        /*## attribute Adc2ClippingFlagPersistent */
   /**
	* BitsName: adc1_clipping_flag_persistent
	* Description: ADC1  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1ClippingFlagPersistent: 1;        /*## attribute Adc1ClippingFlagPersistent */
   /**
	* BitsName: adc4_near_clipping_flag
	* Description: ADC4  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4NearClippingFlag: 1;        /*## attribute Adc4NearClippingFlag */
   /**
	* BitsName: adc3_near_clipping_flag
	* Description: ADC3  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3NearClippingFlag: 1;        /*## attribute Adc3NearClippingFlag */
   /**
	* BitsName: adc2_near_clipping_flag
	* Description: ADC2  near clipping sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2NearClippingFlag: 1;        /*## attribute Adc2NearClippingFlag */
   /**
	* BitsName: adc1_near_clipping_flag
	* Description: ADC1  near clipping  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1NearClippingFlag: 1;        /*## attribute Adc1NearClippingFlag */
   /**
	* BitsName: adc4_near_clipping_flag_persistent
	* Description: ADC4  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4NearClippingFlagPersistent: 1;        /*## attribute Adc4NearClippingFlagPersistent */
   /**
	* BitsName: adc3_near_clipping_flag_persistent
	* Description: ADC3  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3NearClippingFlagPersistent: 1;        /*## attribute Adc3NearClippingFlagPersistent */
   /**
	* BitsName: adc2_near_clipping_flag_persistent
	* Description: ADC2  near clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2NearClippingFlagPersistent: 1;        /*## attribute Adc2NearClippingFlagPersistent */
   /**
	* BitsName: adc1_near_clipping_flag_persistent
	* Description: ADC1 near  clipping persistent sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1NearClippingFlagPersistent: 1;        /*## attribute Adc1NearClippingFlagPersistent */
   /**
	* BitsName: adc4_cal_error_flag_persistent
	* Description: ADC4  calibaration  sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc4CalErrorFlagPersistent: 1;        /*## attribute Adc4CalErrorFlagPersistent */
   /**
	* BitsName: adc3_cal_error_flag_persistent
	* Description: ADC3  calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc3CalErrorFlagPersistent: 1;        /*## attribute Adc3CalErrorFlagPersistent */
   /**
	* BitsName: adc2_cal_error_flag_persistent
	* Description: ADC2  calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc2CalErrorFlagPersistent: 1;        /*## attribute Adc2CalErrorFlagPersistent */
   /**
	* BitsName: adc1_cal_error_flag_persistent
	* Description: ADC1 calibaration sensor status
	* 1: FIT successful
	* 0: Fit error
	*/
    uint32 Adc1CalErrorFlagPersistent: 1;        /*## attribute Adc1CalErrorFlagPersistent */
}Nxp_Tef810x_Mod18_FitStatusAdcRegBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountBits_t
* RegisterName: ADC_status_error_flag_count
* 
* AddressRange: 0x0A4 - 0x0A8
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: adc_status_error_count
	* Description: Error flag count for the selected ADC error .  This register can be resetted only through MCU 
	* Count is incremented at a rate programmed in register ADC_status_monitoring_control (0x18) status_error_poll_count_value bit 
	* 
	* Reset through  the following
	* 
	* 
	* ISM_error_status_and_mcu_reset 0x0AC ( bit 1: reset_error_count_mcu_spi)
	* ADC_status_monitoring_control 0x018 (bi 1 : status_monitoring_reset_spi)
	*/
    uint32 AdcStatusErrorCount: 31;        /*## attribute AdcStatusErrorCount */
}Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountBits_t;
    /**
* Nxp_Tef810x_Mod18_StatusMonitoringFlagBits_t
* RegisterName: status_monitoring_flag
* 
* AddressRange: 0x0A8 - 0x0AC
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: max_temp_error_flag_chirp
	* Description: 0: No issues
	* 1: Issue in chirp temp
	*/
    uint32 MaxTempErrorFlagChirp: 1;        /*## attribute MaxTempErrorFlagChirp */
   /**
	* BitsName: temp_error_flag_tx3
	* Description: 0: No issues
	* 1: Issue in tx3 temp
	*/
    uint32 TempErrorFlagTx3: 1;        /*## attribute TempErrorFlagTx3 */
   /**
	* BitsName: temp_error_flag_tx2
	* Description: 0: No issues
	* 1: Issue in tx2 temp
	*/
    uint32 TempErrorFlagTx2: 1;        /*## attribute TempErrorFlagTx2 */
   /**
	* BitsName: temp_error_flag_tx1
	* Description: 0: No issues
	* 1: Issue in tx1 temp
	*/
    uint32 TempErrorFlagTx1: 1;        /*## attribute TempErrorFlagTx1 */
   /**
	* BitsName: mc_pll_freq_calib_error_flag
	* Description: 0: No issues
	* 1: Main PLL need re-calibration
	* if this bit is set , then a recalibration of mail PLL has to be initiated in next system IDLE cycle.   procedure for re calibration TBD
	*/
    uint32 McPllFreqCalibErrorFlag: 1;        /*## attribute McPllFreqCalibErrorFlag */
   /**
	* BitsName: tx3_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX3 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx3PaHighErrorFlag: 1;        /*## attribute Tx3PaHighErrorFlag */
   /**
	* BitsName: tx2_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX2 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx2PaHighErrorFlag: 1;        /*## attribute Tx2PaHighErrorFlag */
   /**
	* BitsName: tx1_pa_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX1 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Tx1PaHighErrorFlag: 1;        /*## attribute Tx1PaHighErrorFlag */
   /**
	* BitsName: tx3_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX3 module  RF level is  going low
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx3PaLowErrorFlag: 1;        /*## attribute Tx3PaLowErrorFlag */
   /**
	* BitsName: tx2_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX2 module  RF level is login low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits. Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx2PaLowErrorFlag: 1;        /*## attribute Tx2PaLowErrorFlag */
   /**
	* BitsName: tx1_pa_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin TX1 module  RF level is going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits. Otherwise this may  lead to a functional safety issue
	* Procedure TBD
	*/
    uint32 Tx1PaLowErrorFlag: 1;        /*## attribute Tx1PaLowErrorFlag */
   /**
	* BitsName: rx4_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX4 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx4LoHighErrorFlag: 1;        /*## attribute Rx4LoHighErrorFlag */
   /**
	* BitsName: rx3_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX3 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx3LoHighErrorFlag: 1;        /*## attribute Rx3LoHighErrorFlag */
   /**
	* BitsName: rx2_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX2 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx2LoHighErrorFlag: 1;        /*## attribute Rx2LoHighErrorFlag */
   /**
	* BitsName: rx1_lo_high_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX1 module  RF level is getting  high
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx1LoHighErrorFlag: 1;        /*## attribute Rx1LoHighErrorFlag */
   /**
	* BitsName: rx4_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX4 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits.  Otherwise this may result in a reliability issue
	* Procedure TBD
	*/
    uint32 Rx4LoLowErrorFlag: 1;        /*## attribute Rx4LoLowErrorFlag */
   /**
	* BitsName: rx3_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX3 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx3LoLowErrorFlag: 1;        /*## attribute Rx3LoLowErrorFlag */
   /**
	* BitsName: rx2_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX2 module  RF level is  going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx2LoLowErrorFlag: 1;        /*## attribute Rx2LoLowErrorFlag */
   /**
	* BitsName: rx1_lo_low_error_flag
	* Description: 0: No issues
	* 1: Dolphin RX1 module  RF level is going low 
	* A logic one indicates that the TX PA level is going high. In next system IDLE cycle  the transmitter   level shall  be adjusted  to keep it within limits
	* Procedure TBD
	*/
    uint32 Rx1LoLowErrorFlag: 1;        /*## attribute Rx1LoLowErrorFlag */
   /**
	* BitsName: chirp_vtune_high_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco vtune level is getting high.
	* In next system idle cycle this level need to be adjusted
	*/
    uint32 ChirpVtuneHighErrorFlagChirpToMcu: 1;        /*## attribute ChirpVtuneHighErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vtune_low_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco vtune level is getting  low
	*/
    uint32 ChirpVtuneLowErrorFlagChirpToMcu: 1;        /*## attribute ChirpVtuneLowErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vco_level_high_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco level is getting high
	* In next system idle cycle this level need to be adjusted. Otherwise this may result in a reliability issue
	*/
    uint32 ChirpVcoLevelHighErrorFlagChirpToMcu: 1;        /*## attribute ChirpVcoLevelHighErrorFlagChirpToMcu */
   /**
	* BitsName: chirp_vco_level_low_error_flag_chirp_to_mcu
	* Description: 0: No issues
	* 1: Dolphin chirp vco level is getting  low
	* In next system idle cycle this level need to be adjusted
	*/
    uint32 ChirpVcoLevelLowErrorFlagChirpToMcu: 1;        /*## attribute ChirpVcoLevelLowErrorFlagChirpToMcu */
}Nxp_Tef810x_Mod18_StatusMonitoringFlagBits_t;
    /**
* Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetBits_t
* RegisterName: ISM_error_status_and_mcu_reset
* 
* AddressRange: 0x0AC - 0x0B0
* ResetValue: 0x00880000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error
	* Description: Indicates CRC error status  
	* 0: No issues
	* 1: Error in CRC mosi lane
	*/
    uint32 CrcError: 1;        /*## attribute CrcError */
   /**
	* BitsName: start_up_check_error_red
	* Description: Redundant module for start up check.  
	* 0: No issues
	* 1: Error in startup check
	*/
    uint32 StartUpCheckErrorRed: 1;        /*## attribute StartUpCheckErrorRed */
   /**
	* BitsName: ftti_error_red
	* Description: 0: No issues
	* 1: FTTI WDT timer expired indication from redundant ISM
	*/
    uint32 FttiErrorRed: 1;        /*## attribute FttiErrorRed */
   /**
	* BitsName: rf_power_down_error_red
	* Description: 0: No issues
	* 1:  Reliability issues reported in Dolphin possibly leading to an RF power down of modules within Dolphin indication from redundant ISM
	*/
    uint32 RfPowerDownErrorRed: 1;        /*## attribute RfPowerDownErrorRed */
   /**
	* BitsName: rtm_error_red
	* Description: 0: No issues
	* 1: real time monitoring error reported by ISM indication from redundant ISM
	*/
    uint32 RtmErrorRed: 1;        /*## attribute RtmErrorRed */
   /**
	* BitsName: start_up_check_error
	* Description: 0: No issues
	* 1: Error in start_up check
	*/
    uint32 StartUpCheckError: 1;        /*## attribute StartUpCheckError */
   /**
	* BitsName: ftti_error
	* Description: 0: No issues
	* 1: FTTI WDT timer expired
	*/
    uint32 FttiError: 1;        /*## attribute FttiError */
   /**
	* BitsName: rf_power_down_error
	* Description: 0: No issues
	* 1:  Reliability issues reported in Dolphin possibly leading to an RF power down of modules within Dolphin
	*/
    uint32 RfPowerDownError: 1;        /*## attribute RfPowerDownError */
   /**
	* BitsName: rtm_error
	* Description: 0: No issues
	* 1: real time monitoring error reported by ISM
	*/
    uint32 RtmError: 1;        /*## attribute RtmError */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: reset_error_status_wdt
	* Description: Auto clear bit. Writing 1 will reset the Status WDT
	*/
    uint32 ResetErrorStatusWdt: 1;        /*## attribute ResetErrorStatusWdt */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: reset_error_ftti_wdt
	* Description: Auto clear bit. Writing 1 will reset the FTTI WDT
	*/
    uint32 ResetErrorFttiWdt: 1;        /*## attribute ResetErrorFttiWdt */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 6;        /*## attribute Reserved3 */
   /**
	* BitsName: reset_error_count_mcu_spi
	* Description: Reset all   error count register
	* 0: no action
	* 1: reset all counters except crc good, bad debug counters
	*/
    uint32 ResetErrorCountMcuSpi: 1;        /*## attribute ResetErrorCountMcuSpi */
   /**
	* BitsName: reset_error_mcu_spi
	* Description: Reset all ISM error in Dolphin 
	* 0: no action
	* 1: reset all errors
	* 
	* A reset will clear error only if the underlying errir is not present any more
	*/
    uint32 ResetErrorMcuSpi: 1;        /*## attribute ResetErrorMcuSpi */
}Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetBits_t;
    /**
* Nxp_Tef810x_Mod18_LoopBackTestRegBits_t
* RegisterName: loop_back_test_reg
* 
* AddressRange: 0x0B8 - 0x0BC
* ResetValue: 0x80007F00
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 14;        /*## attribute Reserved0 */
   /**
	* BitsName: loop_back_test_en
	* Description: 0: IO's are in normal functional mode
	* 1: I/O's configured for loop back test
	*/
    uint32 LoopBackTestEn: 1;        /*## attribute LoopBackTestEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: tx3_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx3PsDir: 1;        /*## attribute Tx3PsDir */
   /**
	* BitsName: tx2_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx2PsDir: 1;        /*## attribute Tx2PsDir */
   /**
	* BitsName: tx1_ps_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 Tx1PsDir: 1;        /*## attribute Tx1PsDir */
   /**
	* BitsName: error_reset_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ErrorResetDir: 1;        /*## attribute ErrorResetDir */
   /**
	* BitsName: error_n_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ErrorNDir: 1;        /*## attribute ErrorNDir */
   /**
	* BitsName: ready_int_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ReadyIntDir: 1;        /*## attribute ReadyIntDir */
   /**
	* BitsName: chirp_start_dir
	* Description: Loop back test direction
	* 0:  O/P mode
	* 1: input mode
	*/
    uint32 ChirpStartDir: 1;        /*## attribute ChirpStartDir */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: tx3_ps_data_out
	* Description: If loop back dir. is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx3PsDataOut: 1;        /*## attribute Tx3PsDataOut */
   /**
	* BitsName: tx2_ps_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx2PsDataOut: 1;        /*## attribute Tx2PsDataOut */
   /**
	* BitsName: tx1_ps_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 Tx1PsDataOut: 1;        /*## attribute Tx1PsDataOut */
   /**
	* BitsName: error_reset_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ErrorResetDataOut: 1;        /*## attribute ErrorResetDataOut */
   /**
	* BitsName: error_n_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ErrorNDataOut: 1;        /*## attribute ErrorNDataOut */
   /**
	* BitsName: ready_int_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ReadyIntDataOut: 1;        /*## attribute ReadyIntDataOut */
   /**
	* BitsName: chirp_start_data_out
	* Description: If loop back dir is out, this register specified the output data to be send
	* if loop back dir is IN. Then this register reflect the input data
	*/
    uint32 ChirpStartDataOut: 1;        /*## attribute ChirpStartDataOut */
}Nxp_Tef810x_Mod18_LoopBackTestRegBits_t;
    /**
* Nxp_Tef810x_Mod18_SupplyErrorMonRegBits_t
* RegisterName: supply_error_mon_reg
* 
* AddressRange: 0x0BC - 0x0C0
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v1_mon
	* Description: Global 1V1LDO supply high sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V1Mon: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V1Mon */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v1_mon
	* Description: Global 1V1LDO supply low  sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V1Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V1Mon */
   /**
	* BitsName: supply_high_error_flag_global_ldo_1v8_mon
	* Description: Global 1V8LDO supply high sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyHighErrorFlagGlobalLdo1V8Mon: 1;        /*## attribute SupplyHighErrorFlagGlobalLdo1V8Mon */
   /**
	* BitsName: supply_low_error_flag_global_ldo_1v8_mon
	* Description: Global 1V8LDO supply low  sensor
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalLdo1V8Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalLdo1V8Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_dig_1v1_mon
	* Description: Supply 1V1  low sensor  for chirp digital
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpDig1V1Mon: 1;        /*## attribute SupplyLowErrorFlagChirpDig1V1Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_vco_1v8_mon
	* Description: Supply 1V8  low sensor  for chirp VCO ( cover pin failure)
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpVco1V8Mon: 1;        /*## attribute SupplyLowErrorFlagChirpVco1V8Mon */
   /**
	* BitsName: supply_low_error_flag_chirp_pll_1v8_mon
	* Description: Supply 1V8  low sensor  for chirp PLL ( cover pin failure)
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagChirpPll1V8Mon: 1;        /*## attribute SupplyLowErrorFlagChirpPll1V8Mon */
   /**
	* BitsName: supply_low_error_flag_ser_1v8_mon
	* Description: Supply 1V8 low sensor  for serializer
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSer1V8Mon: 1;        /*## attribute SupplyLowErrorFlagSer1V8Mon */
   /**
	* BitsName: supply_low_error_flag_csi2_1v1_mon
	* Description: Supply 1V1 low sensor  for serializer CSI2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagCsi21V1Mon: 1;        /*## attribute SupplyLowErrorFlagCsi21V1Mon */
   /**
	* BitsName: supply_low_error_flag_ser_1v1_mon
	* Description: Supply 1V1 low sensor  for serializer LVDS
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSer1V1Mon: 1;        /*## attribute SupplyLowErrorFlagSer1V1Mon */
   /**
	* BitsName: supply_low_error_flag_global_bias_1v8_mon
	* Description: Supply 1V8 low sensor  for global bias
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagGlobalBias1V8Mon: 1;        /*## attribute SupplyLowErrorFlagGlobalBias1V8Mon */
   /**
	* BitsName: supply_low_error_flag_ssb_mod_1v8_mon
	* Description: Supply 1V8 low sensor  for SSB MOD
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagSsbMod1V8Mon: 1;        /*## attribute SupplyLowErrorFlagSsbMod1V8Mon */
   /**
	* BitsName: supply_low_error_flag_interface_1v1_mon
	* Description: Supply 1V8 low sensor  for LO interface
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagInterface1V1Mon: 1;        /*## attribute SupplyLowErrorFlagInterface1V1Mon */
   /**
	* BitsName: supply_low_error_flag_adc34_1v8_mon
	* Description: Supply 1V8 low sensor  for ADC34
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagAdc341V8Mon: 1;        /*## attribute SupplyLowErrorFlagAdc341V8Mon */
   /**
	* BitsName: supply_low_error_flag_adc12_1v8_mon
	* Description: Supply 1V8 low sensor  for ADC12
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagAdc121V8Mon: 1;        /*## attribute SupplyLowErrorFlagAdc121V8Mon */
   /**
	* BitsName: supply_low_error_flag_mc_1v8_mon
	* Description: Supply 1V8 low sensor  for master clock ( ( cover pin failure))
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagMc1V8Mon: 1;        /*## attribute SupplyLowErrorFlagMc1V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx4_1v8_mon
	* Description: Supply 1V8 low sensor  for RX4
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx41V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx41V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx3_1v8_mon
	* Description: Supply 1V8 low sensor  for RX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx31V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx31V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx2_1v8_mon
	* Description: Supply 1V8 low sensor  for RX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx21V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx21V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx1_1v8_mon
	* Description: Supply 1V8 low sensor  for RX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx11V8Mon: 1;        /*## attribute SupplyLowErrorFlagRx11V8Mon */
   /**
	* BitsName: supply_low_error_flag_rx4_1v1_mon
	* Description: Supply 1V1 low sensor  for RX4
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx41V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx41V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx3_1v1_mon
	* Description: Supply 1V1 low sensor  for RX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx31V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx31V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx2_1v1_mon
	* Description: Supply 1V1 low sensor  for RX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx21V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx21V1Mon */
   /**
	* BitsName: supply_low_error_flag_rx1_1v1_mon
	* Description: Supply 1V1 low sensor  for RX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagRx11V1Mon: 1;        /*## attribute SupplyLowErrorFlagRx11V1Mon */
   /**
	* BitsName: supply_low_error_flag_tx3_1v8_mon
	* Description: Supply 1V8 low sensor  for TX3
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx31V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx31V8Mon */
   /**
	* BitsName: supply_low_error_flag_tx2_1v8_mon
	* Description: Supply 1V8 low sensor  for TX2
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx21V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx21V8Mon */
   /**
	* BitsName: supply_low_error_flag_tx1_1v8_mon
	* Description: Supply 1V8 low sensor  for TX1
	* 0: Error monitored during safety monitoring period
	* 1: Error monitored through out
	*/
    uint32 SupplyLowErrorFlagTx11V8Mon: 1;        /*## attribute SupplyLowErrorFlagTx11V8Mon */
}Nxp_Tef810x_Mod18_SupplyErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_TxErrorMonRegBits_t
* RegisterName: tx_error_mon_reg
* 
* AddressRange: 0x0C0 - 0x0C4
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 13;        /*## attribute Reserved0 */
   /**
	* BitsName: rf_max_error_flag_tx3_mon
	* Description: Reliability flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx3Mon: 1;        /*## attribute RfMaxErrorFlagTx3Mon */
   /**
	* BitsName: rf_max_error_flag_tx2_mon
	* Description: Reliability flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx2Mon: 1;        /*## attribute RfMaxErrorFlagTx2Mon */
   /**
	* BitsName: rf_max_error_flag_tx1_mon
	* Description: Reliability flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMaxErrorFlagTx1Mon: 1;        /*## attribute RfMaxErrorFlagTx1Mon */
   /**
	* BitsName: rf_high_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx3Mon: 1;        /*## attribute RfHighErrorFlagTx3Mon */
   /**
	* BitsName: rf_high_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx2Mon: 1;        /*## attribute RfHighErrorFlagTx2Mon */
   /**
	* BitsName: rf_high_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfHighErrorFlagTx1Mon: 1;        /*## attribute RfHighErrorFlagTx1Mon */
   /**
	* BitsName: rf_low_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx3Mon: 1;        /*## attribute RfLowErrorFlagTx3Mon */
   /**
	* BitsName: rf_low_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx2Mon: 1;        /*## attribute RfLowErrorFlagTx2Mon */
   /**
	* BitsName: rf_low_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 RF level monitor bit
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfLowErrorFlagTx1Mon: 1;        /*## attribute RfLowErrorFlagTx1Mon */
   /**
	* BitsName: rf_min_error_flag_tx3_mon
	* Description: Functional safety error flag
	* 
	* TX3 Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx3Mon: 1;        /*## attribute RfMinErrorFlagTx3Mon */
   /**
	* BitsName: rf_min_error_flag_tx2_mon
	* Description: Functional safety error flag
	* 
	* TX2 Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx2Mon: 1;        /*## attribute RfMinErrorFlagTx2Mon */
   /**
	* BitsName: rf_min_error_flag_tx1_mon
	* Description: Functional safety error flag
	* 
	* Functional monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 RfMinErrorFlagTx1Mon: 1;        /*## attribute RfMinErrorFlagTx1Mon */
   /**
	* BitsName: temp_error_flag_tx3_mon
	* Description: Status monitoring flag
	* 
	* TX3 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx3Mon: 1;        /*## attribute TempErrorFlagTx3Mon */
   /**
	* BitsName: temp_error_flag_tx2_mon
	* Description: Status monitoring flag
	* 
	* TX2 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx2Mon: 1;        /*## attribute TempErrorFlagTx2Mon */
   /**
	* BitsName: temp_error_flag_tx1_mon
	* Description: Status monitoring flag
	* 
	* TX1 Temperature monitor bit. 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 TempErrorFlagTx1Mon: 1;        /*## attribute TempErrorFlagTx1Mon */
   /**
	* BitsName: bb_error_flag_tx3_mon
	* Description: Functional safety error flag
	* 
	* TX3 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx3Mon: 1;        /*## attribute BbErrorFlagTx3Mon */
   /**
	* BitsName: bb_error_flag_tx2_mon
	* Description: Functional safety error flag
	* 
	* TX2 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx2Mon: 1;        /*## attribute BbErrorFlagTx2Mon */
   /**
	* BitsName: bb_error_flag_tx1_mon
	* Description: Functional safety error flag
	* 
	* TX1 RF connectivity monitor bit.
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagTx1Mon: 1;        /*## attribute BbErrorFlagTx1Mon */
}Nxp_Tef810x_Mod18_TxErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_RxErrorMonRegBits_t
* RegisterName: rx_error_mon_reg
* 
* AddressRange: 0x0C4 - 0x0C8
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: lo_max_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx4Mon: 1;        /*## attribute LoMaxErrorFlagRx4Mon */
   /**
	* BitsName: lo_max_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx3Mon: 1;        /*## attribute LoMaxErrorFlagRx3Mon */
   /**
	* BitsName: lo_max_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx2Mon: 1;        /*## attribute LoMaxErrorFlagRx2Mon */
   /**
	* BitsName: lo_max_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMaxErrorFlagRx1Mon: 1;        /*## attribute LoMaxErrorFlagRx1Mon */
   /**
	* BitsName: lo_high_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx4Mon: 1;        /*## attribute LoHighErrorFlagRx4Mon */
   /**
	* BitsName: lo_high_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx3Mon: 1;        /*## attribute LoHighErrorFlagRx3Mon */
   /**
	* BitsName: lo_high_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx2Mon: 1;        /*## attribute LoHighErrorFlagRx2Mon */
   /**
	* BitsName: lo_high_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoHighErrorFlagRx1Mon: 1;        /*## attribute LoHighErrorFlagRx1Mon */
   /**
	* BitsName: lo_low_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx4Mon: 1;        /*## attribute LoLowErrorFlagRx4Mon */
   /**
	* BitsName: lo_low_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx3Mon: 1;        /*## attribute LoLowErrorFlagRx3Mon */
   /**
	* BitsName: lo_low_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx2Mon: 1;        /*## attribute LoLowErrorFlagRx2Mon */
   /**
	* BitsName: lo_low_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoLowErrorFlagRx1Mon: 1;        /*## attribute LoLowErrorFlagRx1Mon */
   /**
	* BitsName: lo_min_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx4Mon: 1;        /*## attribute LoMinErrorFlagRx4Mon */
   /**
	* BitsName: lo_min_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx3Mon: 1;        /*## attribute LoMinErrorFlagRx3Mon */
   /**
	* BitsName: lo_min_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx2Mon: 1;        /*## attribute LoMinErrorFlagRx2Mon */
   /**
	* BitsName: lo_min_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LoMinErrorFlagRx1Mon: 1;        /*## attribute LoMinErrorFlagRx1Mon */
   /**
	* BitsName: bb_error_flag_rx4_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx4Mon: 1;        /*## attribute BbErrorFlagRx4Mon */
   /**
	* BitsName: bb_error_flag_rx3_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx3Mon: 1;        /*## attribute BbErrorFlagRx3Mon */
   /**
	* BitsName: bb_error_flag_rx2_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx2Mon: 1;        /*## attribute BbErrorFlagRx2Mon */
   /**
	* BitsName: bb_error_flag_rx1_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagRx1Mon: 1;        /*## attribute BbErrorFlagRx1Mon */
}Nxp_Tef810x_Mod18_RxErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ChirpErrorMonRegBits_t
* RegisterName: chirp_error_mon_reg
* 
* AddressRange: 0x0C8 - 0x0CC
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 17;        /*## attribute Reserved0 */
   /**
	* BitsName: interface_stuck_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 InterfaceStuckFlagChirpMon: 1;        /*## attribute InterfaceStuckFlagChirpMon */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: vco_freq_480_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VcoFreq480ErrorFlagChirpMon: 1;        /*## attribute VcoFreq480ErrorFlagChirpMon */
   /**
	* BitsName: level_max_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelMaxErrorFlagChirpMon: 1;        /*## attribute LevelMaxErrorFlagChirpMon */
   /**
	* BitsName: level_min_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelMinErrorFlagChirpMon: 1;        /*## attribute LevelMinErrorFlagChirpMon */
   /**
	* BitsName: level_high_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelHighErrorFlagChirpMon: 1;        /*## attribute LevelHighErrorFlagChirpMon */
   /**
	* BitsName: level_low_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LevelLowErrorFlagChirpMon: 1;        /*## attribute LevelLowErrorFlagChirpMon */
   /**
	* BitsName: vtune_high_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VtuneHighErrorFlagChirpMon: 1;        /*## attribute VtuneHighErrorFlagChirpMon */
   /**
	* BitsName: vtune_low_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 VtuneLowErrorFlagChirpMon: 1;        /*## attribute VtuneLowErrorFlagChirpMon */
   /**
	* BitsName: max_temp_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 MaxTempErrorFlagChirpMon: 1;        /*## attribute MaxTempErrorFlagChirpMon */
   /**
	* BitsName: unlock_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 UnlockErrorFlagChirpMon: 1;        /*## attribute UnlockErrorFlagChirpMon */
   /**
	* BitsName: lock_step_error_flag_chirp_mon
	* Description: 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 LockStepErrorFlagChirpMon: 1;        /*## attribute LockStepErrorFlagChirpMon */
}Nxp_Tef810x_Mod18_ChirpErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_McLoErrorMonRegBits_t
* RegisterName: mc_lo_error_mon_reg
* 
* AddressRange: 0x0CC - 0x0D0
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: bb_error_flag_interface_mon
	* Description: Functional safety error flag
	* 
	* RF port connectivity issues reported in LO interface  block 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 BbErrorFlagInterfaceMon: 1;        /*## attribute BbErrorFlagInterfaceMon */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: dig_freq_error_flag_masterclk_mon
	* Description: Functional safety error flag
	* 
	* The O/P frequency from master clock is not within tolerable limits (480/.600 MHz digital clock)
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 DigFreqErrorFlagMasterclkMon: 1;        /*## attribute DigFreqErrorFlagMasterclkMon */
   /**
	* BitsName: mc_pll_lock_error_flag_mon
	* Description: Functional safety error flag
	* 
	* Main PLL (4.8GHz) in un lock condition
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllLockErrorFlagMon: 1;        /*## attribute McPllLockErrorFlagMon */
   /**
	* BitsName: mc_pll_level_error_flag_mon
	* Description: Functional safety error flag
	* 
	* Main PLL (4.8GHz) O/P  level is too low or too high
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllLevelErrorFlagMon: 1;        /*## attribute McPllLevelErrorFlagMon */
   /**
	* BitsName: mc_pll_freq_cal_flag_mon
	* Description: Status monitoring flag
	*  
	* Main pll (4.8GHz) calibration issues ( out of calibration)
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 McPllFreqCalFlagMon: 1;        /*## attribute McPllFreqCalFlagMon */
}Nxp_Tef810x_Mod18_McLoErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_AdcErrorMonRegBits_t
* RegisterName: adc_error_mon_reg
* 
* AddressRange: 0x0D0 - 0x0D4
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: adc4_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC4
	* 
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4HardClippingErrorMon: 1;        /*## attribute Adc4HardClippingErrorMon */
   /**
	* BitsName: adc3_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3HardClippingErrorMon: 1;        /*## attribute Adc3HardClippingErrorMon */
   /**
	* BitsName: adc2_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2HardClippingErrorMon: 1;        /*## attribute Adc2HardClippingErrorMon */
   /**
	* BitsName: adc1_hard_clipping_error_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1HardClippingErrorMon: 1;        /*## attribute Adc1HardClippingErrorMon */
   /**
	* BitsName: adc4_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4HardClippingMonPersistent: 1;        /*## attribute Adc4HardClippingMonPersistent */
   /**
	* BitsName: adc3_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3HardClippingMonPersistent: 1;        /*## attribute Adc3HardClippingMonPersistent */
   /**
	* BitsName: adc2_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2HardClippingMonPersistent: 1;        /*## attribute Adc2HardClippingMonPersistent */
   /**
	* BitsName: adc1_hard_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1HardClippingMonPersistent: 1;        /*## attribute Adc1HardClippingMonPersistent */
   /**
	* BitsName: adc4_clipping_mon
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4ClippingMon: 1;        /*## attribute Adc4ClippingMon */
   /**
	* BitsName: adc3_clipping_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3ClippingMon: 1;        /*## attribute Adc3ClippingMon */
   /**
	* BitsName: adc2_clipping_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2ClippingMon: 1;        /*## attribute Adc2ClippingMon */
   /**
	* BitsName: adc1_clipping_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1ClippingMon: 1;        /*## attribute Adc1ClippingMon */
   /**
	* BitsName: adc4_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4ClippingMonPersistent: 1;        /*## attribute Adc4ClippingMonPersistent */
   /**
	* BitsName: adc3_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3ClippingMonPersistent: 1;        /*## attribute Adc3ClippingMonPersistent */
   /**
	* BitsName: adc2_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2ClippingMonPersistent: 1;        /*## attribute Adc2ClippingMonPersistent */
   /**
	* BitsName: adc1_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1ClippingMonPersistent: 1;        /*## attribute Adc1ClippingMonPersistent */
   /**
	* BitsName: adc4_near_clipping_mon
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4NearClippingMon: 1;        /*## attribute Adc4NearClippingMon */
   /**
	* BitsName: adc3_near_clipping_mon
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3NearClippingMon: 1;        /*## attribute Adc3NearClippingMon */
   /**
	* BitsName: adc2_near_clipping_mon
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2NearClippingMon: 1;        /*## attribute Adc2NearClippingMon */
   /**
	* BitsName: adc1_near_clipping_mon
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1NearClippingMon: 1;        /*## attribute Adc1NearClippingMon */
   /**
	* BitsName: adc4_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4NearClippingMonPersistent: 1;        /*## attribute Adc4NearClippingMonPersistent */
   /**
	* BitsName: adc3_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3NearClippingMonPersistent: 1;        /*## attribute Adc3NearClippingMonPersistent */
   /**
	* BitsName: adc2_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2NearClippingMonPersistent: 1;        /*## attribute Adc2NearClippingMonPersistent */
   /**
	* BitsName: adc1_near_clipping_mon_persistent
	* Description: Status monitoring flag
	* ADC1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1NearClippingMonPersistent: 1;        /*## attribute Adc1NearClippingMonPersistent */
   /**
	* BitsName: adc4_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC4
	* Indicate a calibaration error within ADC 4
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc4CalErrorMonPersistent: 1;        /*## attribute Adc4CalErrorMonPersistent */
   /**
	* BitsName: adc3_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC3
	* Indicate a calibaration error within ADC 3
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc3CalErrorMonPersistent: 1;        /*## attribute Adc3CalErrorMonPersistent */
   /**
	* BitsName: adc2_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC2
	* Indicate a calibaration error within ADC 2
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc2CalErrorMonPersistent: 1;        /*## attribute Adc2CalErrorMonPersistent */
   /**
	* BitsName: adc1_cal_error_mon_persistent
	* Description: Functional safety error flag..
	* ADC1
	* Indicate a calibaration error within ADC 1
	* 0: Error monitored during safety monitoring period only
	* 1: Error monitored through out
	*/
    uint32 Adc1CalErrorMonPersistent: 1;        /*## attribute Adc1CalErrorMonPersistent */
}Nxp_Tef810x_Mod18_AdcErrorMonRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CrcStatusWrRegBits_t
* RegisterName: crc_status_wr_reg
* 
* AddressRange: 0x0D4 - 0x0D8
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: crc_wr_bad_count
	* Description: Indicates the number of bad write into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcWrBadCount: 15;        /*## attribute CrcWrBadCount */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_wr_good_count
	* Description: Indicates the number of good write into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcWrGoodCount: 15;        /*## attribute CrcWrGoodCount */
}Nxp_Tef810x_Mod18_CrcStatusWrRegBits_t;
    /**
* Nxp_Tef810x_Mod18_CrcStatusRdRegBits_t
* RegisterName: crc_status_rd_reg
* 
* AddressRange: 0x0D8 - 0x0DC
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: crc_rd_bad_count
	* Description: Indicates the number of bad read into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcRdBadCount: 15;        /*## attribute CrcRdBadCount */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_rd_good_count
	* Description: Indicates the number of good read into Dolphin when CRC is enabled. This register requires explicit clearing by writing  '0'
	*/
    uint32 CrcRdGoodCount: 15;        /*## attribute CrcRdGoodCount */
}Nxp_Tef810x_Mod18_CrcStatusRdRegBits_t;
    /**
* Nxp_Tef810x_Mod18_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00182301
*/
typedef struct  {
   /**
	* BitsName: parity_bit
	* Description: Parity bit (XOR of bit 30..0)
	*/
    uint32 ParityBit: 1;        /*## attribute ParityBit */
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 15;        /*## attribute Identifier */
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
}Nxp_Tef810x_Mod18_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod18_StatusFttiWdtCntrlUnion_t
* Nxp_Tef810x_Mod18_StatusFttiWdtCntrlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_StatusFttiWdtCntrlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_StatusFttiWdtCntrlUnion_t;
/**
* Nxp_Tef810x_Mod18_FttiWdtCountValueUnion_t
* Nxp_Tef810x_Mod18_FttiWdtCountValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FttiWdtCountValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FttiWdtCountValueUnion_t;
/**
* Nxp_Tef810x_Mod18_StatusWdtCountValueUnion_t
* Nxp_Tef810x_Mod18_StatusWdtCountValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_StatusWdtCountValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_StatusWdtCountValueUnion_t;
/**
* Nxp_Tef810x_Mod18_FttiWdtRdValueUnion_t
* Nxp_Tef810x_Mod18_FttiWdtRdValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FttiWdtRdValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FttiWdtRdValueUnion_t;
/**
* Nxp_Tef810x_Mod18_StatusWdtRdValueUnion_t
* Nxp_Tef810x_Mod18_StatusWdtRdValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_StatusWdtRdValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_StatusWdtRdValueUnion_t;
/**
* Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t
* Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_McuStartupStatusControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcStatusMonitoringControlUnion_t
* Nxp_Tef810x_Mod18_AdcStatusMonitoringControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcStatusMonitoringControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcStatusMonitoringControlUnion_t;
/**
* Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusUnion_t
* Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_SupplyErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_TxErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RxErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_ChirpErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_McLoErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t
* Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcErrorMaskRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t;
/**
* Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t
* Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RfPowerDownControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t;
/**
* Nxp_Tef810x_Mod18_IsmFitTestRegUnion_t
* Nxp_Tef810x_Mod18_IsmFitTestRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_IsmFitTestRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_IsmFitTestRegUnion_t;
/**
* Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_TxErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_TxErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_TxErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_TxErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_RxErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_RxErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RxErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RxErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusUnion_t
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t
* Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusSupplyRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusSupplyRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusSupplyRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusSupplyRegUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusTxRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusTxRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusTxRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusTxRegUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusRxRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusRxRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusRxRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusRxRegUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusChirpRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusChirpRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusChirpRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusChirpRegUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusMcLoRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusMcLoRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusMcLoRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusMcLoRegUnion_t;
/**
* Nxp_Tef810x_Mod18_FitStatusAdcRegUnion_t
* Nxp_Tef810x_Mod18_FitStatusAdcRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_FitStatusAdcRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_FitStatusAdcRegUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountUnion_t
* Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountUnion_t;
/**
* Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t
* Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_StatusMonitoringFlagBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t;
/**
* Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t
* Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t;
/**
* Nxp_Tef810x_Mod18_LoopBackTestRegUnion_t
* Nxp_Tef810x_Mod18_LoopBackTestRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_LoopBackTestRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_LoopBackTestRegUnion_t;
/**
* Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_SupplyErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_TxErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_TxErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_TxErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_TxErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_RxErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_ChirpErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_McLoErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_AdcErrorMonRegUnion_t
* Nxp_Tef810x_Mod18_AdcErrorMonRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_AdcErrorMonRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_AdcErrorMonRegUnion_t;
/**
* Nxp_Tef810x_Mod18_CrcStatusWrRegUnion_t
* Nxp_Tef810x_Mod18_CrcStatusWrRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_CrcStatusWrRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_CrcStatusWrRegUnion_t;
/**
* Nxp_Tef810x_Mod18_CrcStatusRdRegUnion_t
* Nxp_Tef810x_Mod18_CrcStatusRdRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_CrcStatusRdRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_CrcStatusRdRegUnion_t;
/**
* Nxp_Tef810x_Mod18_ModuleidUnion_t
* Nxp_Tef810x_Mod18_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod18_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod18_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod18_IsmRegister_t
 * Nxp_Tef810x_Mod18_IsmRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: status_ftti_wdt_cntrl
    * AddressOffset: 0x000
    * ResetValue: 0x00000000
    * Description: Status WDT: To assist the status monitoring within Dolphin at regular interval,  a programmable timer with interrupt functionality is incorporated within Dolphin.  This timer can be programmed by MCU with typical interval upto 100 ms. At the end of time out the timer can generate a timer interrupt.   Upon receiving an interrupt, MCU can perform a check on all relevant parameters of Dolphin  over SPI. Preferred use model is to use this WDT as a heartbeat timer  ( Interrupt at regular interval)
	* 
	* 
	* FTTI WDT:  In order to assist realizing a FTTI interval  ( once within FTTI a fault injection test has to be performed  within Dolphin )  Once the FTTI WDT is enabled, the timer will wait for a   chirp sequence start trigger from timing engine to start running.  Before expiry of the  timer, a FIT test is performed by the MCU, then the FTTI timer get resetted, and it will wait for next chirp sequence start to start again. If an FIT is not triggered, then a watchdog expiry will trigger an interrupt and error_n pin (safety error)  is asserted.
    */
    Nxp_Tef810x_Mod18_StatusFttiWdtCntrlUnion_t StatusFttiWdtCntrl_ust;        /*## attribute StatusFttiWdtCntrl_ust */
  /**
    * RegisterName: ftti_wdt_count_value
    * AddressOffset: 0x004
    * ResetValue: 0xFFFFFFFF
    * Description: FTTI WDT watchdog timer interval load value
    */
    Nxp_Tef810x_Mod18_FttiWdtCountValueUnion_t FttiWdtCountValue_ust;        /*## attribute FttiWdtCountValue_ust */
  /**
    * RegisterName: status_wdt_count_value
    * AddressOffset: 0x008
    * ResetValue: 0xFFFFFFFF
    * Description: Status  WDT watchdog timer interval load value
    */
    Nxp_Tef810x_Mod18_StatusWdtCountValueUnion_t StatusWdtCountValue_ust;        /*## attribute StatusWdtCountValue_ust */
  /**
    * RegisterName: ftti_wdt_rd_value
    * AddressOffset: 0x00C
    * ResetValue: 0xFFFFFFFF
    * Description: Current snapshot of the FTTI WDT  timer register
    */
    Nxp_Tef810x_Mod18_FttiWdtRdValueUnion_t FttiWdtRdValue_ust;        /*## attribute FttiWdtRdValue_ust */
  /**
    * RegisterName: status_wdt_rd_value
    * AddressOffset: 0x010
    * ResetValue: 0xFFFFFFFF
    * Description: Current snapshot of the status  WDT  timer register
    */
    Nxp_Tef810x_Mod18_StatusWdtRdValueUnion_t StatusWdtRdValue_ust;        /*## attribute StatusWdtRdValue_ust */
  /**
    * RegisterName: MCU_startup_status_control
    * AddressOffset: 0x014
    * ResetValue: 0x00000000
    * Description: As part of startup once the Dolphin in power up state, the following actions has to be completed by the MCU in the following order to promote the Dolphin IC to a  operational safe state. Till such time, the error_reset_n pin will be in an asserted state by the Dolphin IC. At the end of each action, the corresponding bit need to be set  in order (one by one)  to move the Dolphin to a operational safe state. If the order is broken, then error_n pin will be never de-asserted.
	* The bist must be set with follwoing order
	* 1. spi_access_check_done_ok ( set bit 0 'to '1')
	* 2. main_ldo_config_ok ( set bit 0 and '1''to '1')
	* 3. gobal_bias_config_ok ( set bit 0, 1,2  'to '1')
	* 4. local_ldo_config_ok ( set bit 0, 1,2, 3  'to '1')
	* 5. IC_calibration_ok ( set bit 0, 1,2,3,4 'to '1')
	* 6. local_bias_config_ok( set bit 0, 1,2,3,4, 5 'to '1')
	* 7. pll4g_config_ok( set bit 0, 1,2,3,4, 5, 6 'to '1')
	* 8. Sensor_configuration_done 0, 1,2,3,4, 5, 6, 7 'to '1')
	* 
	* 
	* Till the above steps are completed,  the error_n  pill be in asserted state.
	* 
	* On completion of above steps  the MCU also need to prepare the Dolphin for its functional use ( enable power to analog  modules, enable clocks, release reset etc.)
	* Once the IC is configured for functional use  all the safety sensors  also need to be configured before using Dolphin . Once completed set bit '7
    */
    Nxp_Tef810x_Mod18_McuStartupStatusControlUnion_t McuStartupStatusControl_ust;        /*## attribute McuStartupStatusControl_ust */
  /**
    * RegisterName: ADC_status_monitoring_control
    * AddressOffset: 0x018
    * ResetValue: 0x00000000
    * Description: A status monitoring feature is available for  to check  the O/P of ADC  against received signal  strength , such as  near clipping, clipping, and hard clipping.  Only one error can be monitored at a time
	* 
	* Two configuration possible
	* 1. Monitor status only during active ADC data acquisition
	* 2. Force enable  status monitoring  all the time
	* 
	* A status counting also available to see how many times  the  selected events  happened within the monitoring window  The status is checked  based on a status_error_poll_count_value"
	* 
	* Status monitoring is not part of functional safety ( no error_n assertion) based on the information presented here.
    */
    Nxp_Tef810x_Mod18_AdcStatusMonitoringControlUnion_t AdcStatusMonitoringControl_ust;        /*## attribute AdcStatusMonitoringControl_ust */
  /**
    * RegisterName: RTM_safety_error_control_and_status
    * AddressOffset: 0x01C
    * ResetValue: 0x80000700
    * Description: Real time monitoring window is controlled by timing engine ( safety monitoring active).   For all practical purpose, the real time monitoring is set active when active data acquisition is on within Dolphin sensor.
	* 
	* 
	* A set of counters are also available here ( only for diagnostics and  debugging) and not part of actual functional safety.
    */
    Nxp_Tef810x_Mod18_RtmSafetyErrorControlAndStatusUnion_t RtmSafetyErrorControlAndStatus_ust;        /*## attribute RtmSafetyErrorControlAndStatus_ust */

    uint32 gap01_au32[1];        /* gap 1 in register space */  /**
    * RegisterName: supply_error_mask_reg
    * AddressOffset: 0x024
    * ResetValue: 0x00000000
    * Description: Mask register to mask supply related   functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
	* In a functional safety context  it is not recommended to mask supply related errors
    */
    Nxp_Tef810x_Mod18_SupplyErrorMaskRegUnion_t SupplyErrorMaskReg_ust;        /*## attribute SupplyErrorMaskReg_ust */
  /**
    * RegisterName: tx_error_mask_reg
    * AddressOffset: 0x028
    * ResetValue: 0x00000000
    * Description: Mask register to mask Transmit unit ( all three TX)  functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
	* Ina functional safety context  all functional safety related errors has to be enabled
    */
    Nxp_Tef810x_Mod18_TxErrorMaskRegUnion_t TxErrorMaskReg_ust;        /*## attribute TxErrorMaskReg_ust */
  /**
    * RegisterName: rx_error_mask_reg
    * AddressOffset: 0x02C
    * ResetValue: 0x00000000
    * Description: Mask register to mask RX  functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
    */
    Nxp_Tef810x_Mod18_RxErrorMaskRegUnion_t RxErrorMaskReg_ust;        /*## attribute RxErrorMaskReg_ust */
  /**
    * RegisterName: chirp_error_mask_reg
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: Mask register to mask chirp functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
	* All functional safety related error has to be enabled  in a functional safety application context
    */
    Nxp_Tef810x_Mod18_ChirpErrorMaskRegUnion_t ChirpErrorMaskReg_ust;        /*## attribute ChirpErrorMaskReg_ust */
  /**
    * RegisterName: mc_lo_error_mask_reg
    * AddressOffset: 0x034
    * ResetValue: 0x00000000
    * Description: Mask register to mask Master clock   and LO interface   functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
    */
    Nxp_Tef810x_Mod18_McLoErrorMaskRegUnion_t McLoErrorMaskReg_ust;        /*## attribute McLoErrorMaskReg_ust */
  /**
    * RegisterName: adc_error_mask_reg
    * AddressOffset: 0x038
    * ResetValue: 0x00000000
    * Description: Mask register to mask ADC  functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
    */
    Nxp_Tef810x_Mod18_AdcErrorMaskRegUnion_t AdcErrorMaskReg_ust;        /*## attribute AdcErrorMaskReg_ust */
  /**
    * RegisterName: rf_power_down_control
    * AddressOffset: 0x03C
    * ResetValue: 0x87000000
    * Description: Register to control the RF power down monitoring FSM
	* RF power down is primarily  to take care of any reliability issues within Dolphin.   So strictly speaking  not part of the functional safety monitoring. However if a sensor is reporting a  reliability isse, then  a RF power down is initiated to modules reporting  the issue.  Under this scenario,  the error_n pin is also  asserted indicating a failure within Dolphin.
    */
    Nxp_Tef810x_Mod18_RfPowerDownControlUnion_t RfPowerDownControl_ust;        /*## attribute RfPowerDownControl_ust */
  /**
    * RegisterName: ISM_FIT_test_reg
    * AddressOffset: 0x040
    * ResetValue: 0x00000000
    * Description: This register is used for controlling the fault injection testing .
	* The fault injection test is initiated and controlled by the interfacing MCU.  During testing a complete coverage of internal ISM plus integrity check towards individual sensing elements are performed. A set of fault injection test registers are provided to indicate pass or fail of the  FIT .
    */
    Nxp_Tef810x_Mod18_IsmFitTestRegUnion_t IsmFitTestReg_ust;        /*## attribute IsmFitTestReg_ust */
  /**
    * RegisterName: master_error_flag_raw_status
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: Un masked error status indication to MC&U
	* 
	* All important errors are combined to create a reduced set of events that can be used for real time safety monitoring.  The reduced ( combined) set is used to provide a one shot information to MCU on the fault condition within Dolphin ( in case of real time monitoring error)
    */
    Nxp_Tef810x_Mod18_MasterErrorFlagRawStatusUnion_t MasterErrorFlagRawStatus_ust;        /*## attribute MasterErrorFlagRawStatus_ust */
  /**
    * RegisterName: supply_error_flag_raw_status
    * AddressOffset: 0x048
    * ResetValue: 0x00000000
    * Description: Unmasked  Raw error status for all supply errors . Individual supply error reported from sensor before masking
    */
    Nxp_Tef810x_Mod18_SupplyErrorFlagRawStatusUnion_t SupplyErrorFlagRawStatus_ust;        /*## attribute SupplyErrorFlagRawStatus_ust */
  /**
    * RegisterName: tx_error_flag_raw_status
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: Raw error status  for Transmit  function from individual sensors before masking
	* Contain functional safety related, reliability related and status monitoring related  information
    */
    Nxp_Tef810x_Mod18_TxErrorFlagRawStatusUnion_t TxErrorFlagRawStatus_ust;        /*## attribute TxErrorFlagRawStatus_ust */
  /**
    * RegisterName: rx_error_flag_raw_status
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Raw error status from individual  RX unit sensors before masking
	* Contain reliability related, functional safety related and status monitoring related information
    */
    Nxp_Tef810x_Mod18_RxErrorFlagRawStatusUnion_t RxErrorFlagRawStatus_ust;        /*## attribute RxErrorFlagRawStatus_ust */
  /**
    * RegisterName: chirp_error_flag_raw_status
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: Raw error status from  chirp  module  (individual sensors before masking
	* Contain reliability, functional safety and status monitoring flags.
    */
    Nxp_Tef810x_Mod18_ChirpErrorFlagRawStatusUnion_t ChirpErrorFlagRawStatus_ust;        /*## attribute ChirpErrorFlagRawStatus_ust */
  /**
    * RegisterName: mc_lo_error_flag_raw_status
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: Raw error status  for master clock and LO interface block.
	* All bit fields are related with functional safety
    */
    Nxp_Tef810x_Mod18_McLoErrorFlagRawStatusUnion_t McLoErrorFlagRawStatus_ust;        /*## attribute McLoErrorFlagRawStatus_ust */
  /**
    * RegisterName: adc_error_flag_raw_status
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: Raw error status from  dual ADC ( ADC12 & ADC 34) . individual sensor information  before masking
	* Contain both functional  safety related error as well as status error flags
    */
    Nxp_Tef810x_Mod18_AdcErrorFlagRawStatusUnion_t AdcErrorFlagRawStatus_ust;        /*## attribute AdcErrorFlagRawStatus_ust */
  /**
    * RegisterName: rf_power_down_error_flag_raw_status
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: A consolidated set of  status errors related to  power down of modules . This register indicates the RAW status .
	* In case of serious reliability issues are reported, then respective modules are powered down.
    */
    Nxp_Tef810x_Mod18_RfPowerDownErrorFlagRawStatusUnion_t RfPowerDownErrorFlagRawStatus_ust;        /*## attribute RfPowerDownErrorFlagRawStatus_ust */
  /**
    * RegisterName: master_error_flag_masked_status
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: A consolidated list of errors  related to real time monitoring. The status indications are  captured after the masking.
	* Ina functional safety application masking  these   errors are not recommended ( mask provision added only for validation purpose).  
	* If an error is ported in any one of this bit fields  then the error_n pin is asserted.
	* MCU need to access this register only for diagnostics
    */
    Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t MasterErrorFlagMaskedStatus_ust;        /*## attribute MasterErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: supply_error_flag_masked_status
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: Masked error status for  individual supply sensors. MCU need to access this register only for diagnostics
    */
    Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t SupplyErrorFlagMaskedStatus_ust;        /*## attribute SupplyErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: tx_error_flag_masked_status
    * AddressOffset: 0x06C
    * ResetValue: 0x00000000
    * Description: Masked  status  for Transmit  function from individual sensors after  masking
	* Contain functional safety related, reliability related and status monitoring related  information
    */
    Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t TxErrorFlagMaskedStatus_ust;        /*## attribute TxErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: rx_error_flag_masked_status
    * AddressOffset: 0x070
    * ResetValue: 0x00000000
    * Description: Masked  error status from individual  RX unit sensors after  masking
	* Contain reliability related, functional safety related and status monitoring related information
    */
    Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t RxErrorFlagMaskedStatus_ust;        /*## attribute RxErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: chirp_error_flag_masked_status
    * AddressOffset: 0x074
    * ResetValue: 0x00000000
    * Description: Masked  error status from  chirp  module  
	* Contain reliability, functional safety and status monitoring flags.
    */
    Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t ChirpErrorFlagMaskedStatus_ust;        /*## attribute ChirpErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: mc_lo_error_flag_masked_status
    * AddressOffset: 0x078
    * ResetValue: 0x00000000
    * Description: masked  error status  of master clock and LO interface block 
	* All bit fields are related with functional safety
    */
    Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus_ust;        /*## attribute McLoErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: adc_error_flag_masked_status
    * AddressOffset: 0x07C
    * ResetValue: 0x00000000
    * Description: Masked  error status from  dual ADC ( ADC12 & ADC 34) . 
	* Contain both functional  safety related error as well as status error flags
    */
    Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t AdcErrorFlagMaskedStatus_ust;        /*## attribute AdcErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: rf_power_down_error_flag_masked_status
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: Masked error status for the consolidated  error flagsa that can lead to a power down of Dolphin modules.
	* Example: If bit '1'is set, then the chirp module power is disabled. Once set, the underlying fault condition at soucre has to be removed  .  The user may start with masking the set error flag to poll the internal status of teh IP or the corresponding level detector. In a worst case scenario, a functional reset or full  reset  may be issued to the IP to start with a  known default status
    */
    Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t RfPowerDownErrorFlagMaskedStatus_ust;        /*## attribute RfPowerDownErrorFlagMaskedStatus_ust */
  /**
    * RegisterName: fit_status_supply_reg
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: Detailed  supply sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusSupplyRegUnion_t FitStatusSupplyReg_ust;        /*## attribute FitStatusSupplyReg_ust */
  /**
    * RegisterName: fit_status_tx_reg
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: Detailed  TX  functional safety  sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusTxRegUnion_t FitStatusTxReg_ust;        /*## attribute FitStatusTxReg_ust */
  /**
    * RegisterName: fit_status_rx_reg
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: Detailed  RX  functional safety  sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusRxRegUnion_t FitStatusRxReg_ust;        /*## attribute FitStatusRxReg_ust */
  /**
    * RegisterName: fit_status_chirp_reg
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: Detailed  Chirp   functional safety  sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusChirpRegUnion_t FitStatusChirpReg_ust;        /*## attribute FitStatusChirpReg_ust */
  /**
    * RegisterName: fit_status_mc_lo_reg
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: Detailed  MC & LO    functional safety  sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusMcLoRegUnion_t FitStatusMcLoReg_ust;        /*## attribute FitStatusMcLoReg_ust */
  /**
    * RegisterName: fit_status_adc_reg
    * AddressOffset: 0x098
    * ResetValue: 0x00000000
    * Description: Detailed  ADC    functional safety  sensor   fault injection test status register.  During a FIT test, MCU initiate force_error  assertion followed with a reset_error assertion.
	* Once force _error is asserted,  this  FIT status register must be read  (individual bit fields)  as '0' .  At the end of FIOT ( at the end of reset_error), this register must be read as '1' . A " zero"  to  " one"  toggle indicate a successful FIT.
	* Please note that  the FIT covers only the interface  connection with Dolphin  and may not cover the complete sensor functionality
    */
    Nxp_Tef810x_Mod18_FitStatusAdcRegUnion_t FitStatusAdcReg_ust;        /*## attribute FitStatusAdcReg_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x09C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: ADC_status_error_flag_count
    * AddressOffset: 0x0A4
    * ResetValue: 0x00000000
    * Description: Once the status monitoring is enabled, then two configuration option is available
	* 1. selected clipping event status is monitored only during acquisition
	* 2. selected clipping event status is monitored always
	* 
	* Bit to set : ADC_status_monitoring_control 0x018 (bi 0 : status_monitoring_set_spi)
    */
    Nxp_Tef810x_Mod18_AdcStatusErrorFlagCountUnion_t AdcStatusErrorFlagCount_ust;        /*## attribute AdcStatusErrorFlagCount_ust */
  /**
    * RegisterName: status_monitoring_flag
    * AddressOffset: 0x0A8
    * ResetValue: 0x00000000
    * Description: Status monitoring is an important concept for Dolphin.  The status flags need to be polled by MCU at regular interval. To assist this a configurable status WDT timer I provided, which can create interrupts towards MCU at regular intervals.  On reception of this interrupt, all the status flags to be checked by MCU, if set necessary action must be taken by MCU  to make sure that the  Dolphin IC is functionally safe operational profile.
	* If any status monitoring flags (set) are processed within reasonable time may lead to a functional safety issues, and this will be reported through assertion of error_n pin.   In case of a functional safety error, the MCU need to perform  more actions  to bring back Dolphin to an operational state. This may reduce the availability of Dolphin as sensor. 
	* By working on the status register availability of Dolphin Sensor is improved.
    */
    Nxp_Tef810x_Mod18_StatusMonitoringFlagUnion_t StatusMonitoringFlag_ust;        /*## attribute StatusMonitoringFlag_ust */
  /**
    * RegisterName: ISM_error_status_and_mcu_reset
    * AddressOffset: 0x0AC
    * ResetValue: 0x00880000
    * Description: Some module are maintained with redundancy within ISM  so some of the bit fields  are duplicated here.
	* This register provide the  status of the ISM module.
	* Once an error is reported, it is latched and the error get cleared only through a reset and if the underlying error is not present any more ( total reset  or ISM reset)
    */
    Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t IsmErrorStatusAndMcuReset_ust;        /*## attribute IsmErrorStatusAndMcuReset_ust */
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
    * RegisterName: loop_back_test_reg
    * AddressOffset: 0x0B8
    * ResetValue: 0x80007F00
    * Description: Loop back test register to assist interface toggle test.
    */
    Nxp_Tef810x_Mod18_LoopBackTestRegUnion_t LoopBackTestReg_ust;        /*## attribute LoopBackTestReg_ust */
  /**
    * RegisterName: supply_error_mon_reg
    * AddressOffset: 0x0BC
    * ResetValue: 0x00000000
    * Description: Monitor register to decide the monitoring time period of functional safety errors.
	* Depending on the application specific requirement some of the errors are monitored through out and some only during safety monitoring period.
    */
    Nxp_Tef810x_Mod18_SupplyErrorMonRegUnion_t SupplyErrorMonReg_ust;        /*## attribute SupplyErrorMonReg_ust */
  /**
    * RegisterName: tx_error_mon_reg
    * AddressOffset: 0x0C0
    * ResetValue: 0x00000000
    * Description: Monitor register to decide the monitoring time period of Transmit unit ( all three TX)  functional safety errors.
	* Depending on the application specific requirement some of the errors are monitored through out and some only during safety monitoring period.
    */
    Nxp_Tef810x_Mod18_TxErrorMonRegUnion_t TxErrorMonReg_ust;        /*## attribute TxErrorMonReg_ust */
  /**
    * RegisterName: rx_error_mon_reg
    * AddressOffset: 0x0C4
    * ResetValue: 0x00000000
    * Description: Monitor  register to decide the monitoring time period of RX  functional safety errors.
	* Depending on the application specific requirement some of the errors are monitored through out and some only during safety monitoring period.
    */
    Nxp_Tef810x_Mod18_RxErrorMonRegUnion_t RxErrorMonReg_ust;        /*## attribute RxErrorMonReg_ust */
  /**
    * RegisterName: chirp_error_mon_reg
    * AddressOffset: 0x0C8
    * ResetValue: 0x00000000
    * Description: Monitor register to decide the monitoring time period of chirp functional safety errors.
	* Depending on the application specific requirement some of the errors are monitored through out and some only during safety monitoring period.
    */
    Nxp_Tef810x_Mod18_ChirpErrorMonRegUnion_t ChirpErrorMonReg_ust;        /*## attribute ChirpErrorMonReg_ust */
  /**
    * RegisterName: mc_lo_error_mon_reg
    * AddressOffset: 0x0CC
    * ResetValue: 0x00000000
    * Description: Monitor register to decide the monitoring time period of  Master clock   and LO interface   functional safety errors.
	* Depending on the application specific requirement some of the errors are monitored through out and some only during safety monitoring period.
    */
    Nxp_Tef810x_Mod18_McLoErrorMonRegUnion_t McLoErrorMonReg_ust;        /*## attribute McLoErrorMonReg_ust */
  /**
    * RegisterName: adc_error_mon_reg
    * AddressOffset: 0x0D0
    * ResetValue: 0x00000000
    * Description: Mask register to mask ADC  functional safety errors.
	* Mask options are primarily given  for validation and debugging. Not to be used in a functional safety context ( sensors marked for functional safety)
    */
    Nxp_Tef810x_Mod18_AdcErrorMonRegUnion_t AdcErrorMonReg_ust;        /*## attribute AdcErrorMonReg_ust */
  /**
    * RegisterName: crc_status_wr_reg
    * AddressOffset: 0x0D4
    * ResetValue: 0x00000000
    * Description: This register indicates the status of the SPI writes into Dolphin chip with CRC  enabled
    */
    Nxp_Tef810x_Mod18_CrcStatusWrRegUnion_t CrcStatusWrReg_ust;        /*## attribute CrcStatusWrReg_ust */
  /**
    * RegisterName: crc_status_rd_reg
    * AddressOffset: 0x0D8
    * ResetValue: 0x00000000
    * Description: This register indicates the status of the SPI reads into Dolphin chip with CRC  enabled
    */
    Nxp_Tef810x_Mod18_CrcStatusRdRegUnion_t CrcStatusRdReg_ust;        /*## attribute CrcStatusRdReg_ust */
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x0DC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x0E0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x0E4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x0E8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x0EC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x0F0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x0F4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x0F8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x0FC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x100
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0x104
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;
  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0x108
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;
  /**
    * RegisterName: Reserved10
    * AddressOffset: 0x10C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved10;

    uint32 gap02_au32[955];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00182301
    * Description: Register with details of Module ID and Version number
    */
    Nxp_Tef810x_Mod18_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod18_IsmRegister_t;

#endif
