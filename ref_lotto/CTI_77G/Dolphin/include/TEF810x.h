/*
 * TEF810x.h
 *
 *  Created on: 2016/12/12
 *      Author: user
 */

#ifndef TEF810X_H_
#define TEF810X_H_

#include "typedefs.h"

/*******************************************************************************************
* Define the TEF810x Module ID
*
*       Module Name                       ID
*******************************************************************************************/

#define CENTRAL_CTRL_MOUDLE              0x00
#define LVDS_TX_MODULE                   0x01
#define CSI2_TX_MODULE                   0x02
#define CIF_TX_MODULE                    0x03
#define TIMING_ENGINE_MODULE             0x04
#define SWEEP_CTRL_MODULE                0x05
#define CHIRP_AFC_MODULE                 0x06
#define ADC_12_MODULE                    0x07
#define ADC_34_MODULE                    0x08
#define GLOBAL_BIAS_MODULE               0x09
#define LO_INTERFACE_MODULE              0x0A
#define MASTER_CLOCK_MODULE              0x0C
#define RX1_MODULE                       0x0D
#define RX2_MODULE                       0x0E
#define RX3_MODULE                       0x0F
#define RX4_MODULE                       0x10
#define TX1_MODULE                       0x11
#define TX2_MODULE                       0x12
#define TX3_MODULE                       0x13
#define SSBMOD_MODULE                    0x14
#define GLOBAL_LDO_MODULE                0x15
#define ATB_MODULE                       0x16
#define OPT_MOUDULE                      0x17
#define ISM_MODULE                       0x18
#define DUMMY_MOUDLE                     0xFF


/*******************************************************************************************
* Define the CENTRAL_CTRL_MOUDLE
*
*       Register Name                   Offset
*******************************************************************************************/

#define ReadyInt_PadControl              0x00
#define Chirp_Start_PadControl           0x04
#define Error_n_PadControl               0x08
#define Error_Reset_PadControl           0x0C
#define TX1_PadControl                   0x10
#define TX2_PadControl                   0x14
#define TX3_PadControl                   0x18
#define MISO_padControl                  0x1C
#define Ldo_Serialiser_Ser_Control       0x20
#define Ldo_Serialiser_csi2_Control      0x24
#define Ldo_Adc_Control                  0x28
#define Ldo_Ssbmod_Control               0x2C
//#define Reserved                       0x30
#define ATB1_en_register                 0x34
#define ATB1_ac_en_register              0x38
//#define Reserved                       0x3C
//#define Reserved                       0x40
#define dynamic_power_control_enable     0x44
#define dynamic_power_control_delay      0x48
#define serialiser_mode_sel              0x4C
#define Ready_Int_Control                0x50
#define INT_ENABLE                       0x54
#define INT_CLR                          0x58
#define INT_SET                          0x5C
//#define Reserved                       0x60
#define ip_level_clock_enable            0x64
#define ip_level_pon_enable              0x68
#define reset_control                    0x6C
#define functional_reset_control         0x70
//#define Reserved                       0x74
#define INT_RAW_STATUS                   0x78
#define INT_MASKED_STATUS                0x7C
#define scratch_register1                0x80

#define loop_back_test                   0xFA0
#define ModuleID                         0xFFC


/*******************************************************************************************
* Define the LVDS_TX_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define Ch0_control                      0x00
#define Ch1_control                      0x04
#define Ch2_control                      0x08
#define Ch3_control                      0x0C
#define Clk_channel_data                 0x10
#define Scrambler_init_value             0x14
#define Idle_pattern                     0x18
//#define Reserved                       0x1C
//#define Reserved                       0x20
#define ClockChTxdata12x1                0x24
//#define AdcDebugMode                     0x28
#define TransmitPhaseControl             0x2C
#define MsbLsbControl                    0x30
#define LvdsConfigReg                    0x34
#define lvds_crc_ctrl1                   0x38
#define lvds_crc_ctrl2                   0x3C
#define lvds_crc_ctrl3                   0x40
#define LVDS_pdc_config_reg              0x44
#define lvds_output_invert_ctrl          0x48
#define Lvds_tx_control                  0x4C
#define lvds_ser_global_pad_ctrl         0x50
#define lvds_ser_pad_ctrl1               0x54
#define lvds_ser_pad_ctrl2               0x58
#define lvds_ser_pad_ctrl3               0x5C
#define ADCTestDataMux                   0x60
#define LVDS_WindowActiveSel             0x64

#define LVDS_master_idiv_ctrl            0x6C
#define LVDS_pdc_shift_reg_idiv_ctrl     0x70
#define LVDS_sns_top_control             0x74
#define LVDS_ref_cntr_init               0x78
#define LVDS_freq_counter_start          0x7C
#define LVDS_freq_counter_read_value     0x80
#define LVDS_ref_counter_read_value      0x84


/*******************************************************************************************
* Define the CSI2_TX_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define TrimReg0                         0x00
#define TrimReg1                         0x04
#define TrimReg2                         0x08
#define TrimReg3                         0x0C
#define DPHY_DFE_DLN_Register_0          0x20
#define DPHY_DFE_DLN_Register_1          0x24
#define DPHY_DFE_CLN_Register_0          0x28
#define DPHY_DFE_CLN_Register_1          0x2C
#define DPHY_lane_polarity_swap_register 0x30
#define PPI_Data_Lane_Swap_Register      0x34
#define FIFO_status_Register             0x38
#define USD_Pixel_Mode_Control_Register  0x3C
#define YUV_Pixel_Mode_Control_Register  0x40
#define RAW_Pixel_Mode_Control_Register  0x44
#define PHY_TINIT_Count_Register         0x48
#define VC0_compression_Prediction_Scheme_Register_1 0x4C
#define VC0_compression_Prediction_Scheme_Register_2 0x50
#define VC1_compression_Prediction_Scheme_Register_1 0x54
#define VC1_compression_Prediction_Scheme_Register_2 0x58
#define VC2_compression_Prediction_Scheme_Register_1 0x5C
#define VC2_compression_Prediction_Scheme_Register_2 0x60
#define VC3_compression_Prediction_Scheme_Register_1 0x64
#define VC3_compression_Prediction_Scheme_Register_2 0x68
#define PLL_Count_Register               0x6C
#define Device_Ready_Indication_Register 0x70
#define Csi2AdaptConfigReg1              0x80
#define Csi2AdaptConfigReg2              0x84
#define Csi2AdaptConfigReg3              0x88
#define csi2_crc_ctrl1                   0x8C
#define csi2_crc_ctrl2                   0x90
#define csi2_crc_ctrl3                   0x94
#define csi2_pdc_config_reg              0x98
#define csi2_txn_ctrl                    0x9C
#define Csi2TestModeControlReg           0xA0
#define Csi2master_idiv_ctrl             0xA4
#define Csi2pdc_shift_reg_idiv_ctrl      0xAC
#define Csi2ABistCntrlOutPutReg          0xB4
#define Csi2sns_top_control              0xB8
#define Csi2ref_cntr_init                0xBC
#define Csi2freq_counter_start           0xC0
#define Csi2freq_counter_read_value      0xC4
#define Csi2ref_counter_read_value       0xC8


/*******************************************************************************************
* Define the CIF_TX_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define CifConfigReg                     0x00
#define CifLineCntReg                    0x04
#define cif_crc_ctrl1                    0x08
#define cif_crc_ctrl2                    0x0C
#define cif_crc_ctrl3                    0x10
#define cif_output_invert_ctrl           0x14
#define cif_pdc_config_reg               0x18
#define cif_txn_ctr                      0x1C
#define cif_sel_sack_reg                 0x20
#define cif_global_mfio_ctrl             0x24
#define cif_mfio_ctrl1                   0x28
#define cif_mfio_ctrl2                   0x2C
#define cif_mfio_ctrl3                   0x30
#define cif_mfio_ctrl4                   0x34
#define cif_mfio_ctrl5                   0x38
#define cif_mfio_ctrl6                   0x3C
#define cif_mfio_ctrl7                   0x40
#define cif_global_vgio_ctrl             0x44
#define cif_vgio_ctrl1                   0x48
#define cif_vgio_ctrl2                   0x4C
#define cif_vgio_ctrl3                   0x50
#define cif_vgio_ctrl4                   0x54
#define cif_vgio_ctrl5                   0x58
#define cif_vgio_ctrl6                   0x5C
#define cif_vgio_ctrl7                   0x60
#define CifTestModeControlReg            0x64
#define cif_WindowActiveSel              0x68
#define cif_master_idiv_ctrl             0x6C
#define cif_pdc_shift_reg_idiv_ctrl      0x70
#define cif_sns_top_control              0x74
#define cif_ref_cntr_init                0x78
#define cif_freq_counter_start           0x7C
#define cif_freq_counter_read_value      0x80
#define cif_ref_counter_read_value       0x84


/*******************************************************************************************
* Define the TIMING_ENGINE_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define Timing_control_1_profile0        0x00
#define Timing_control_2_profile0        0x04
#define Timing_control_3_profile0        0x08
#define Timing_control_1_profile1        0x0C
#define Timing_control_2_profile1        0x10
#define Timing_control_3_profile1        0x14
#define Timing_control_1_profile2        0x18
#define Timing_control_2_profile2        0x1C
#define Timing_control_3_profile2        0x20
#define Timing_control_1_profile3        0x24
#define Timing_control_2_profile3        0x28
#define Timing_control_3_profile3        0x2C
#define Chirp_sequence_control           0x30
#define chirp_sequence_interval_control  0x34
#define Chirp_trigger_mode_control       0x38
#define jumpback_period_control          0x3C
#define dc_power_on_delay_control        0x40
#define force_dc_poweron_control         0x44
#define tx_dc_power_on_group_delay_control   0x48
#define rx_dc_power_on_group_delay_control   0x4C
#define chirp_dynamic_power_control      0x50
#define tx_rx_dc_power_on_delay_fine_control 0x54
#define chirp_global_control             0x58


/*******************************************************************************************
* Define the SWEEP_CTRL_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define N_start_rf_profile0              0x00
#define DN_chirp_rf_profile0             0x04
#define N_step_chirp_rf_profile0         0x08
#define DN_reset_rf_profile0             0x0C
#define N_step_reset_rf_profile0         0x10
#define Div_update_rf_profile0           0x14
#define N_start_rf_profile1              0x18
#define DN_chirp_rf_profile1             0x1C
#define N_step_chirp_rf_profile1         0x20
#define DN_reset_rf_profile1             0x24
#define N_step_reset_rf_profile1         0x28
#define Div_update_rf_profile1           0x2C
#define N_start_rf_profile2              0x30
#define DN_chirp_rf_profile2             0x34
#define N_step_chirp_rf_profile2         0x38
#define DN_reset_rf_profile2             0x3C
#define N_step_reset_rf_profile2         0x40
#define Div_update_rf_profile2           0x44
#define N_start_rf_profile3              0x48
#define DN_chirp_rf_profile3             0x4C
#define N_step_chirp_rf_profile3         0x50
#define DN_reset_rf_profile3             0x54
#define N_step_reset_rf_profile3         0x58
#define Div_update_rf_profile3           0x5C
#define ChirpMode                        0x60
#define Cwmode                           0x80


/*******************************************************************************************
* Define the CHIRP_AFC_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define filter_register_profile0         0x00
#define filter_par_register_profile0     0x04
#define vco_register_profile0            0x08
#define filter_register_profile1         0x0C
#define filter_par_register_profile1     0x10
#define vco_register_profile1            0x14
#define filter_register_profile2         0x18
#define filter_par_register_profile2     0x1C
#define vco_register_profile2            0x20
#define filter_register_profile3         0x24
#define filter_par_register_profile3     0x28
#define vco_register_profile3            0x2C
#define cp_register                      0x30
#define vco_buffer_ldo_register          0x34
#define cppfd_ldo_register               0x38
#define divider_ldo_register             0x3C
#define bias_block_register              0x40
#define buffer_register                  0x44
#define divide_force_register            0x48
#define loop_dynamic_reg_0               0x4C
#define lpf_vtune_vco_status             0x50
#define funcsafe_mon_vtune_vco           0x54
#define funcsafe_mon_unlock_vco          0x58
#define funcsafe_mon_level_vco           0x5C
#define funcsafe_mon_temperature_vco     0x60
#define level_shifter_control            0x64
#define control_spare                    0x6C
#define cal_lo_det                       0x70
#define CHIRP_AFC_sns_top_control        0x74
#define CHIRP_AFC_ts_pd                  0x78
#define CHIRP_AFC_ref_cntr_init          0x7C
#define CHIRP_AFC_freq_counter_start     0x80
#define CHIRP_AFC_freq_counter_read_value 0x84
#define CHIRP_AFC_ref_counter_read_value 0x88
#define atb                              0x98
#define trim                             0x9C
#define test_error_flag_status           0xA8
#define divide_freq_counter_start        0xBC
#define divide_freq_counter_read_value   0xC0



/*******************************************************************************************
* Define the ADC_12_MODULE & ADC_34_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define adc_pon                          0x00
#define calibration_status               0x04
#define calibration_start                0x08
#define clipping_detect_control          0x14
#define dither_control                   0x44
#define outputmux                        0x8C
#define cal_monitor_status               0xA0
#define cal_monitor_max_error            0xA4
#define bias_source_follower             0x30C


/*******************************************************************************************
* Define the GLOBAL_BIAS_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define globbias_tx1                     0x00
#define globbias_tx2                     0x04
#define globbias_tx3                     0x08
#define globbias_rx1                     0x0C
#define globbias_rx2                     0x10
#define globbias_rx3                     0x14
#define globbias_rx4                     0x18
#define globbias_masterclk               0x1C
#define globbias_chirpgen                0x20
#define globbias_lo_interfac             0x24
#define globbias_adc12                   0x28
#define globbias_adc34                   0x2C
#define globbias_atbip                   0x30
#define globbias_ssbmod                  0x34
#define globbias_bbd                     0x38
#define globbias_clockpll                0x3C
#define globbias_lotripler               0x40
#define globbias_sns                     0x44
#define globbias_local_ldo               0x48
#define globbias_reference               0x50
#define globbias_test_bgr                0x54
#define globbias_test_ptat               0x58
#define globbias_ptat_offset_calib       0x5C
#define globbias_pon_local_ldo           0x60
#define globbias_pon1v8                  0x64
#define globbias_sns_low_top_control     0x68
#define globbias_atb_delay_timer         0x6C
#define globbias_atb                     0x70



/*******************************************************************************************
* Define the LO_INTERFACE_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define lo_interface_bbd_config          0x00
#define lo_interface_control             0x18
#define lo_interface_sns_low_top_control 0x1C



/*******************************************************************************************
* Define the MASTER_CLOCK_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define ibias_control                    0x00
#define pll_ldo_control                  0x04
#define ldo_control                      0x08
#define pfd_control                      0x0C
#define cp_control                       0x10
#define output_clock_skew_control        0x14
#define loop_filter_control              0x18
#define lock_control                     0x1C
#define xo_ldo_control                   0x20
#define clock_buffer_control             0x2C
#define ref_clock_delay_control          0x30
#define calibration_vco_control          0x34
#define calibration_aac_control          0x38
#define calibration_afc_control1         0x3C
#define calibration_afc_control2         0x40
#define glitch_filter                    0x4C
#define vco_control                      0x54
#define start_calibration_counter        0x58
#define reset_calibration                0x5C
#define master_clock_sns_low_top_control 0x60
#define calibration_status1              0x64
#define calibration_status2              0x68
#define lock_status                      0x6C
#define test_force_error                 0x88
#define test_reset_error                 0x8C
#define mclk_test_error_flag_status      0x90



/*******************************************************************************************
* Define the RX1, RX2, RX3, RX4 MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define g_rx_set_profile0                0x00
#define lpf_rx_set_profile0              0x08
#define lo_gain_profile0                 0x0C
#define hpf_rx_direct_set_profile0       0x10
#define g_rx_set_profile1                0x14
#define lpf_rx_set_profile1              0x1C
#define lo_gain_profile1                 0x20
#define hpf_rx_direct_set_profile1       0x24
#define g_rx_set_profile2                0x28
#define lpf_rx_set_profile2              0x30
#define lo_gain_profile2                 0x34
#define hpf_rx_direct_set_profile2       0x38
#define g_rx_set_profile3                0x3C
#define lpf_rx_set_profile3              0x44
#define lo_gain_profile3                 0x48
#define hpf_rx_direct_set_profile3       0x4C
#define funcsafe_mon_level_lo            0x50
#define rx_rms_control                   0x54
#define rx_bbd_config                    0x58
#define rx_if_buf_control                0x5C
#define rx_rms_detector_settings         0x60
#define rx_control                       0x68
#define rx_rms_cal                       0x6C
#define rx_sns_low_top_control           0x70



/*******************************************************************************************
* Define the TX1, TX2, TX3 MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define g_tx_gain_profile0               0x00
#define g_lox3_gain_profile0             0x04
#define g_tx_gain_profile1               0x08
#define g_lox3_gain_profile1             0x0C
#define g_tx_gain_profile2               0x10
#define g_lox3_gain_profile2             0x14
#define g_tx_gain_profile3               0x18
#define g_lox3_gain_profile3             0x1C
#define funcsafe_mon_level_rf            0x24
#define tx_bbd_config                    0x28
#define ts_sel                           0x2C
#define tx_rms_control                   0x30
#define tx_rms_detector_settings         0x34
#define tx_control                       0x3C
#define tx_sns_top_control               0x40
#define tx_ts_pd                         0x44
#define tx_rms_cal                       0x48
#define debug_test                       0x4C
#define phaseshifter_status              0x50
#define tx_atb_delay_timer               0x54
#define tx_atb1                          0x58
#define tx_atb2                          0x5C
#define tx_test_error_flag_status        0x68



/*******************************************************************************************
* Define the SSBMOD_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define SSBmod_control                   0x00
#define LEVEL_set                        0x08
#define CAL_det                          0x0C
#define ssb_idiv_ctrl                    0x14
#define sns_top_control                  0x100
#define sns_config                       0x104



/*******************************************************************************************
* Define the GLOBAL_LDO_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define gldo1v1_sns_low_top_control      0x04
#define gldo1v1_sns_low_config           0x08
#define gldo1v1_sns_high_top_control     0x0C
#define gldo1v1_sns_high_config          0x10
#define gldo1v8_sns_low_top_control      0x18
#define gldo1v8_sns_low_config           0x1C
#define gldo1v8_sns_high_top_control     0x20
#define gldo1v8_sns_high_config          0x24
#define gldo_bg_ref_config               0x28
#define gldo_bg_ref_status               0x2C
#define gldo_test_force_error            0x48
#define gldo_test_reset_error            0x4C
#define gldo_test_error_flag_status      0x50



/*******************************************************************************************
* Define the ATB_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define atb_control_register             0x00
#define atb_data_register                0x08
#define atb1_config_register             0x0C
#define atb2_config_register             0x10
#define ldo_atb_control                  0x30
#define atb1                             0x50
#define atb2                             0x54
#define atb_delay_timer                  0x60
#define adc_buf1_control_reg             0x100
#define adc_buf2_control_reg             0x104



/*******************************************************************************************
* Define the OPT_MOUDULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define OTP_STATUS                       0x40
#define OTP_DATA_RD_REG                  0x200



/*******************************************************************************************
* Define the ISM_MODULE
*
*       Register Name                   Offset
*******************************************************************************************/

#define status_ftti_wdt_cntrl            0x00
#define ftti_wdt_count_value             0x04
#define status_wdt_count_value           0x08
#define ftti_wdt_rd_value                0x0C
#define status_wdt_rd_value              0x10
#define MCU_startup_status_control       0x14
#define ADC_status_monitoring_control    0x18
#define RTM_safety_error_control_and_status    0x1C
#define supply_error_mask_reg            0x24
#define tx_error_mask_reg                0x28
#define rx_error_mask_reg                0x2C
#define chirp_error_mask_reg             0x30
#define mc_lo_error_mask_reg             0x34
#define adc_error_mask_reg               0x38
#define rf_power_down_control            0x3C
#define ISM_FIT_test_reg                 0x40
#define master_error_flag_raw_status     0x44
#define supply_error_flag_raw_status     0x48
#define tx_error_flag_raw_status         0x4C
#define rx_error_flag_raw_status         0x50
#define chirp_error_flag_raw_status      0x54
#define mc_lo_error_flag_raw_status      0x58
#define adc_error_flag_raw_status        0x5C
#define rf_power_down_error_flag_raw_status    0x60
#define master_error_flag_masked_status  0x64
#define supply_error_flag_masked_status  0x68
#define tx_error_flag_masked_status      0x6C
#define rx_error_flag_masked_status      0x70
#define chirp_error_flag_masked_status   0x74
#define mc_lo_error_flag_masked_status   0x78
#define adc_error_flag_masked_status     0x7C
#define rf_power_down_error_flag_masked_status 0x80
#define fit_status_supply_reg            0x84
#define fit_status_tx_reg                0x88
#define fit_status_rx_reg                0x8C
#define fit_status_chirp_reg             0x90
#define fit_status_mc_lo_reg             0x94
#define fit_status_adc_reg               0x98
#define ADC_status_error_flag_count      0xA4
#define status_monitoring_flag           0xA8
#define ISM_error_status_and_mcu_reset   0xAC
#define supply_error_mon_reg             0xBC
#define tx_error_mon_reg                 0xC0
#define rx_error_mon_reg                 0xC4
#define chirp_error_mon_reg              0xC8
#define mc_lo_error_mon_reg              0xCC
#define adc_error_mon_reg                0xD0


typedef enum tef810x_status
{
	TEF810X_OK,
    TEF810X_FAIL
}tef810x_status_t;

typedef enum tef810x_interface
{
	TEF810X_CSI2,
	TEF810X_LVDS,
    TEF810X_CIF
}tef810x_interface_t;

typedef enum tef810x_profile
{
    TEF810X_T2 = 0,
    TEF810X_T3,
    TEF810X_T1,
    TEF810X_RSSI,
    TEF810X_T2T3,
    TEF810X_T2T3T1,
    TEF810X_PROFILE0123
}tef810x_profile_t;

typedef enum rmtp_rf_data
{
    RF_INIT_STATUS = 0,
    RF_VCO_STATUS,
    RF_MCLK_STATUS,
    RF_ADC_STATUS,
}rmtp_rf_data_t;

typedef enum tef810x_vco_msg
{
    VCO_NO_SUBBAND = 0,
    VCO_CALIB_CHIRP_ERR,
    VCO_CALIB_MCLK_ERR,
    VCO_CALIB_TEMP_CHG,
}tef810x_vco_msg_t;

typedef enum add_time_type
{
    ADD_DWELL_TIME = 0,
	ADD_SETTLE_TIME,
	ADD_IDLE_TIME,
}tef810x_add_time_t;

typedef enum tef810x_production_mode
{
	kNORMAL_MODE,
	kPRODUCTION_MODE
}tef810x_production_mode_t;

typedef enum tef810x_selftest_message
{
    MCLK_CHECK_FAIL,
    NORMAL_TX_P0_CHECK_FAIL,
	NORMAL_TX_P1_CHECK_FAIL,
	NORMAL_TX_P2_CHECK_FAIL,
	NORMAL_TX_P3_CHECK_FAIL,
	NORMAL_CHIRP_P0_CHECK_FAIL,
	NORMAL_CHIRP_P1_CHECK_FAIL,
	NORMAL_CHIRP_P2_CHECK_FAIL,
	NORMAL_CHIRP_P3_CHECK_FAIL,
	NORMAL_SEND_CHIRP_CHECK_FAIL,
	NORMAL_SEND_CHIRP_SHORT_MSG,
	NORMAL_SEND_CHIRP_LONG_MSG,
	NORMAL_SEND_CHIRP_P3_MSG,
	_100M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_100M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	_200M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_200M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	_400M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_400M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	_600M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_600M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	_1000M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_1000M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	_1100M_BANDWIDTH_CHIRP_CHECK_FAIL,
	_1100M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL,
	END_OF_MESSAGE
}tef810x_selftest_msg_e;

typedef struct rf_configs
{
	double   freq;            // RF current frequency
	double   bw;              // RF current bandwidth
	uint8_t  txgain;          // RF current TX gain
	uint8_t  rxgain;          // RF current RX gain
	double   chirp_time;      // RF current one chirp time
}rf_configs_t;

typedef struct sctrl_profiletiming
{
	double  freq;
	double  bandwidth;
	double  tReset;
	double  chirp_period;
	double  hpf;
	double  lpf;
	double  loopBW;
	uint8_t txgain;
	uint8_t rxgain;
}sctrl_profiletiming_t;

typedef struct sctrl_profiletiming1
{
	uint16_t freq;
	uint16_t bandwidth;
	uint16_t tReset;
	uint16_t chirp_period;
	uint16_t hpf;
	uint16_t lpf;
	uint16_t loopBW;
	uint16_t txrxgain;
}sctrl_profiletiming1_t;

typedef struct {
	uint16_t profile1_config[8];           // data define as the sctrl_profiletiming1_t structure
	uint16_t profile2_config[8];           // data define as the sctrl_profiletiming1_t structure
	uint16_t profile3_config[8];           // data define as the sctrl_profiletiming1_t structure
	uint16_t profile4_config[8];           // data define as the sctrl_profiletiming1_t structure
	uint16_t dwell;
	uint16_t settle;
	uint16_t jumpback;
	uint8_t	 txpon[4][3];
	uint8_t	 txsw[4][3];
	uint8_t  agc_profile;
	uint8_t  agc_default_gain;
	uint8_t  narrow_band;
	uint8_t  adc_recalibration;
	uint8_t  tx_calibration ;
	uint8_t  reserved[1];
	uint16_t vco_cal_frame_time;
	uint16_t tidle[4];
	uint8_t  rx_gain[4][4];
	uint8_t  tx_gain[4][3];
	uint8_t  tx_level_code[3][2];
	int16_t  tx_level_table[14][2];
	uint8_t  reserved2[2];
	uint8_t  lock_freq_time;
	uint8_t  lock_freq_tx;
	uint16_t lock_freq;
	uint8_t  tef_dbg;
}tef810x_info_t, *tef810x_info_p;

typedef struct {
	pars_header_t	hdr;
	tef810x_info_t  info;
}tef810x_pars_t, *tef810x_pars_p;

typedef struct
{
	uint16_t  data_type;
	short     message_ID;
}rmtp_rf_ic_status_t;

typedef struct {
	uint16_t center_freq;
	uint16_t hpf;
	uint16_t lpf;
	uint8_t	 txpon[3];
	uint8_t	 txsw[3];
	uint8_t  rxgain[4];
	uint8_t	 txgain[3];
}rmtp_rf_profile_gain_info_t;

typedef struct
{
	uint8_t narrowband             : 1;  /*  */
    uint8_t mclk_recal_flag        : 1;  /*  */
    uint8_t pdc_bwwide             : 1;  /*  */
    uint8_t lock_freq_mode         : 1;  /*  */
    uint8_t re_init_flag           : 1;  /*  */
	uint8_t bit5                   : 1;  /*  */
	uint8_t bit6                   : 1;  /*  */
    uint8_t bit7                   : 1;  /*  */

} dolphin_flag_type;

typedef struct TEF810x_Die_ID
{
	uint8_t Chip_Version;
	uint8_t LOT_ID[8];
	uint8_t wtYear;
	uint8_t wtMonth;
	uint8_t wtDay;
	uint8_t Die_x;
	uint8_t Die_y;
	uint8_t maskVersion;
	uint8_t Die_number;
	uint8_t tpMajor_wt;
	uint8_t tpMinor_wt;
	uint8_t tpMajor_ft;
	uint8_t tpMinor_ft;
} TEF810xDieId_t;

void write_TEF810x_Reg(uint8_t module_id, uint16_t register_addr, uint32_t reg_data);
uint32_t read_TEF810x_Reg(uint8_t module_id, uint16_t register_addr);
void burst_read_TEF810x_Reg(void);
void init_TEF810x(void);
void chip_vco_calibration_and_chip_setup(bool_t calibrate_vco, bool_t setup_freq, bool_t setup_txrx, uint8_t deci);
void chip_setup(void);
uint8_t TEF810x_chirp_start(tef810x_profile_t send_profile, uint16_t chirp_num, uint16_t profile_repeat_num);
int  get_tef810x_init_status(void);
void chg_Tef810x_profile_dwell_time(int ProfileNum, int add_dwell_t);
void chg_Tef810x_profile_settle_time(int ProfileNum, int add_settle_t);
void chg_Tef810x_profile_idle_time(int ProfileNum, int add_idle_t);
void get_rf_config(rf_configs_t *  rf_setting);
void get_rf_profile_config(tef810x_profile_t, rf_configs_t *  rf_setting);
void get_tef810x_info(char** args, int count);
void tef_safety_check(char** args, int count);
void tef_vco_check(void);
void tef_vco_cal_freq_get(void);
bool_t tef_check_adc_cal_done(void);
void set_default_rf_parameters(bool_t er_eeprom_flag);
bool_t rmtp_get_rf_profile_gain_info(uint8_t get_profile, rmtp_rf_profile_gain_info_t  *rf_profile_gain_info);
bool_t rmtp_set_rf_profile_gain_setting(uint8_t set_profile, rmtp_rf_profile_gain_info_t  *rf_profile_gain_info);
tef810x_status_t set_tef810x_long_profile(sctrl_profiletiming_t* config);
tef810x_status_t unset_tef810x_long_profile(void);

/*void print_TEF810x_cenetral_control_reg(void);
void print_TEF810x_csi2l_reg(void);
void print_TEF810x_timing_reg(void);
void print_TEF810x_seep_ctrl_reg(void);
void print_TEF810x_chirp_afc_reg(void);
void print_TEF810x_adc12_reg(void);
void print_TEF810x_adc34_reg(void);
void print_TEF810x_global_bias_reg(void);
void print_TEF810x_lo_interface_reg(void);
void print_TEF810x_master_clock_reg(void);
void print_TEF810x_rx1_reg(void);
void print_TEF810x_rx2_reg(void);
void print_TEF810x_rx3_reg(void);
void print_TEF810x_rx4_reg(void);
void print_TEF810x_tx1_reg(void);
void print_TEF810x_tx2_reg(void);
void print_TEF810x_tx3_reg(void);
void print_TEF810x_ssbmod_reg(void);
void print_TEF810x_global_ldo_reg(void);
void print_TEF810x_atb_reg(void);
void print_TEF810x_opt_reg(void);
void print_TEF810x_ism_reg(void);
void print_TEF810x_all(void);*/
void tef_clipping_check(void*);
void tef_zero_calibration(uint8_t mode, uint16_t bandwidth);
void tef_reg_blobk_read(uint8_t module_addr, uint16_t reg_addr, uint16_t size, uint32_t* data_block);
uint32_t tef_reg_read(uint8_t module_addr, uint16_t reg_addr);
void tef_reg_write(uint8_t module_addr, uint16_t reg_addr, uint32_t write_data);
uint8_t rmtp_tef810x_txid_to_profile(uint8_t txid);
void tef_all_HPF100(void);
void chg_tef810x_lock_freq_cb(uint8_t time, uint8_t tx, uint16_t cwfreq);
void chg_TEF810x_banwith_cb(uint8_t chgprofile, uint16_t effc_bandwith);
void chg_tef810x_filter_cb(uint8_t chgprofile, uint16_t setHPF, uint16_t setLPF);
void re_init_TEF810x_cb(uint8_t defalut_disable);
void TEF810x_save_cb();
void chg_tef810x_txgain_cb(uint8_t chgprofile, uint8_t tx1gain, uint8_t tx2gain, uint8_t tx3gain);
void chg_tef810x_rxgain_cb(uint8_t chgprofile, uint8_t rx1gain, uint8_t rx2gain, uint8_t rx3gain, uint8_t rx4gain);
uint8_t rmtp_get_tx_high_level(uint8_t txNum);
uint8_t rmtp_find_tx_high_level(uint8_t txNum, uint16_t txGain);
void set_tef810x_production_mode(tef810x_production_mode_t);
float get_tef810x_temperature(void);    //temperature min:-40 max:135
tef810x_status_t rmtp_get_tef810x_chip_info(TEF810xDieId_t* DieInfo);
tef810x_status_t rmtp_rf_selftest(uint32_t* data, uint32_t size, bool_t* selftest_result);

void get_Dolphin_Lib_version(char* ver32b);

#define TEF_PARS_ID									FOURCC('t','e','f','p')
#define tef_pars_info_get(_ver,_size)				pars_info_get(TEF_PARS_ID, _ver,_size)
#define tef_pars_info_set(_data,_cnt)				pars_info_set(TEF_PARS_ID, _data, _cnt)
#define RF_TX_HIGH_LEVEL_THLD   6
#define RF_TX_LOW_LEVEL_THLD    3

#endif /* TEF810X_H_ */
