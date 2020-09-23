/*
 * TEF810x.c
 *
 *  Created on: 2016/12/12
 *      Author: Bruce Chang
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LibVer.h"
#include "sys_shared.h"
#include "coefs.h"
#include "dolphinIC.h"
#include "can_cubtek.h"
#include "rmtp_api.h"
#include "rmtp_msg.h"
#include "rmtp_hal.h"
#include <hal_es3.h>
#include <hal_es3_ctrl.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_Ism.h>
#include <es3/NXP_TEF810X_SweepControl.h>
#include <es3/NXP_TEF810X_MasterClock.h>
#include <es3/NXP_TEF810X_Rx.h>
#include <es3/NXP_TEF810X_Tx.h>
#include <es3/NXP_TEF810X_Adc.h>
#include <es3/NXP_TEF810X_LoInterface.h>
#include <es3/NXP_TEF810X_CentralControl.h>

//#define TEF810X_INSERT_TEST
#define TEF810X_LOG
//#define TEF810X_DBG
//#define TEF810x_TEST_MODE
#define T1_DEFAULT_RX_GAIN   5
//#define SAMPLE_TIME          12.8

#define BANDWIDTH_TEST_NUM 6
#define PROFILE_NUM 4

#define CAL_VCO_TEMPERATURE  5.0
#define SEARCH_VCO_RANGE     5

#define MCLK_MAX_ERROR_TIMES 3
#define VCO_MAX_ERROR_TIMES  3

#define VCO_CALIBRATION_MASK_FLAG    0x1
#define ADC_CALIBRATION_MASK_FLAG    0x2

#define DEFAULT_CAL_FUNC_NUM 100

#define VCO_CAL_OFF          65535

#define TEF810X_FRE_MAX         800
#define TEF810X_FRE_MIN         720
#define TEF810X_BW_MAX          1000
#define TEF810X_BW_MIN          100
#define TEF810X_LBW_MAX         1400
#define TEF810X_LBW_MIN         100
#define TEF810X_RESET_T_MAX     100
#define TEF810X_RESET_T_MIN     0
#define TEF810X_DWELL_T_MAX     50
#define TEF810X_DWELL_T_MIN     0
#define TEF810X_SETTLE_T_MAX    100
#define TEF810X_SETTLE_T_MIN    0
#define TEF810X_JUMPBACK_T_MAX  20
#define TEF810X_JUMPBACK_T_MIN  0
#define TEF810X_IDLE_T_MAX      100
#define TEF810X_IDLE_T_MIN      0
#define TEF810X_HP_MAX          1600
#define TEF810X_HP_MIN          100
#define TEF810X_LP_MAX          15
#define TEF810X_LP_MIN          7

/******************************************************************************
* INTERNAL TYPE DEFINITIONS
*****************************************************************************/

const LIBS_VER_T __attribute__((section(".library_version"))) Dolphin_version =  {
		.id =          VER_ID          (DOLPHIN_LIB_VER),
		.major =       VER_MAJOR       (3),
		.minor =       VER_MINOR       (6),
		.build =       VER_BUILD       (Lib_BUILD_RELEASE),
		.maintenance = VER_MAINTENANCE (0)
};

typedef enum vco_state_data
{
	TEF_VCO_CAL_IDLE = 0,
	TEF_VCO_CAL_RF_BEGIN,
	TEF_VCO_CAL_RF_END,
	TEF_VCO_CALIBRATION,
	TEF_VCO_CAL_END
}tef_vco_state_t;

tef810x_pars_t __attribute__((section(".tefpars"))) tef810x_parameters;

const tef810x_pars_t default_tefp = {
	.hdr={
		.base = (uint32_t)&tef810x_parameters,
		.version = 0x0200,
		.size = sizeof(tef810x_pars_t),
		.id=TEF_PARS_ID,
		.chksum = 0,
		.mask = 0
	},
	.info = {
			.profile1_config={765, 150, 50, 263,  400, 15, 600, 20 << 8 | 7},
			.profile2_config={765, 150, 50, 263,  400, 15, 600, 20 << 8 | 7},
			.profile3_config={765, 450, 60, 323,  800, 15, 600, 20 << 8 | 7},
			.profile4_config={765, 300, 50, 263,  800, 20, 600, 20 << 8 | 7},
			.dwell=15,
			.settle=65,
			.jumpback=5,
			.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
			.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
			.agc_profile = 7,
			.agc_default_gain = 4,
			.narrow_band = true,
			.adc_recalibration = 2,
			.tx_calibration = 2,
			.reserved = {0},
			.vco_cal_frame_time = 3000,
			.tidle = {0,0,50,0},
			.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
			.tx_gain = {{1,8,1},{8,1,1},{1,1,8},{0,0,0}},
			.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
							  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
							  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
			.tx_level_table = {{-5,0}, {5,0}, {10,0}, {20,0}, {30,0}, {40,0}, {50,0},
							   {60,0}, {70,0}, {80,0}, {90,0}, {100,0}, {110,0}, {120,0}},
			.reserved2 = {0, 0},
			.lock_freq_time = 0,
			.lock_freq_tx = 0,
			.lock_freq = 0,
			.tef_dbg = 0
	}
};

/*
const tef810x_info_t tef810x_fcw_info = {
	.profile1_config={765, 150, 50, 263,  400, 15, 600, 20 << 8 | 7},
	.profile2_config={765, 150, 50, 263,  400, 15, 600, 20 << 8 | 7},
	.profile3_config={765, 450, 60, 323,  800, 15, 600, 20 << 8 | 7},
	.profile4_config={765, 300, 10, 205,  800, 20, 400,  0 << 8 | 7},
	.dwell=15,
	.settle=65,
	.jumpback=5,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 2,
	.reserved = {0},
	.vco_cal_frame_time = 3000,
	.tidle = {0,0,50,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{1,8,1},{8,1,1},{1,1,8},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,0}, {5,0}, {10,0}, {20,0}, {30,0}, {40,0}, {50,0},
					   {60,0}, {70,0}, {80,0}, {90,0}, {100,0}, {110,0}, {120,0}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_fcw_combo_info = {
	.profile1_config={765, 150, 10, 205, 400, 20, 1400, 220 << 8 | 7},
	.profile2_config={765, 150, 10, 205, 400, 20, 1400, 220 << 8 | 7},
	.profile3_config={765, 300, 10, 205, 800, 20, 1400, 220 << 8 | 7},
	.profile4_config={765, 300, 10, 205, 800, 20, 1400, 220 << 8 | 7},
	.dwell=1,
	.settle=65,
	.jumpback=1,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = false,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{0,220,0},{220,0,0},{0,0,220},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};


const tef810x_info_t tef810x_bsd_info = {
	.profile1_config={765, 600, 150, 400, 400, 20, 1400, 240 << 8 | 5},
	.profile2_config={765, 600, 150, 400, 400, 20, 1400, 240 << 8 | 5},
	.profile3_config={765, 600, 150, 400, 400, 20, 1400, 240 << 8 | 5},
	.profile4_config={765, 600, 150, 400, 400, 20, 1400, 240 << 8 | 5},
	.dwell=20,
	.settle=100,
	.jumpback=2,
	.txpon={{0,1,1},{0,1,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{0,1,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 3,
	.narrow_band = false,
	.adc_recalibration = false,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{5,5,5,5},{5,5,5,5},{5,5,5,5},{5,5,5,5}},
	.tx_gain = {{0,0,240},{0,240,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_tbb_info = {
	.profile1_config={765, 600, 50, 300, 400, 20, 400, 192 << 8 | 6},
	.profile2_config={765, 600, 50, 300, 400, 20, 400, 192 << 8 | 6},
	.profile3_config={765, 600, 50, 300, 400, 20, 400, 192 << 8 | 6},
	.profile4_config={765, 600, 50, 300, 400, 20, 400, 192 << 8 | 6},
	.dwell=20,
	.settle=100,
	.jumpback=2,
	.txpon={{0,1,1},{0,1,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{0,1,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 3,
	.narrow_band = true,
	.adc_recalibration = false,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{6,6,6,6},{6,6,6,6},{6,6,6,6},{6,6,6,6}},
	.tx_gain = {{0,0,192},{0,192,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_bsd_omni_info = {
	.profile1_config={765, 600, 132, 300, 800, 15, 600, 192 << 8 | 6},
	.profile2_config={765, 600, 132, 300, 800, 15, 600, 192 << 8 | 6},
	.profile3_config={765, 600, 132, 300, 800, 15, 600, 192 << 8 | 6},
	.profile4_config={765, 600, 132, 300, 800, 15, 600, 192 << 8 | 6},
	.dwell=4,
	.settle=35,
	.jumpback=1,
	.txpon={{1,0,1},{1,0,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{1,0,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 3,
	.narrow_band = true,
	.adc_recalibration = false,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{6,6,6,6},{6,6,6,6},{6,6,6,6},{6,6,6,6}},
	.tx_gain = {{0,0,192},{0,192,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_bsd_two_beam_m_info = {
	.profile1_config={765, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 0 	//T2
	.profile2_config={765, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 1		//T1
	.profile3_config={765, 150, 10, 250, 400, 20, 1400, 255 << 8 | 6},	//Profile 2		//T3
	.profile4_config={765, 150, 10, 250, 400, 20, 1400, 255 << 8 | 6},	//Profile 3
	.dwell=45,
	.settle=65,
	.jumpback=2,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{6,6,6,6},{6,6,6,6},{6,6,6,6},{6,6,6,6}},
	.tx_gain = {{0,240,0},{240,0,0},{0,0,255},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_bsd_two_beam_s_info = {
	.profile1_config={767, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 0 	//T2
	.profile2_config={767, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 1		//T1
	.profile3_config={767, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 2		//T3
	.profile4_config={767, 150, 10, 250, 400, 20, 1400, 240 << 8 | 6},	//Profile 3
	.dwell=45,
	.settle=65,
	.jumpback=2,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{6,6,6,6},{6,6,6,6},{6,6,6,6},{6,6,6,6}},
	.tx_gain = {{0,240,0},{240,0,0},{0,0,240},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_trh1_bsd_info = {
	.profile1_config={785, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 0 	//T2
	.profile2_config={785, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 1		//T1
	.profile3_config={785, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 2		//T3
	.profile4_config={785, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 3
	.dwell=20,
	.settle=100,
	.jumpback=2,
	.txpon={{0,1,1},{0,1,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{0,1,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{0,0,10},{0,10,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
			  	  	   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_trh2_bsd_info = {
	.profile1_config={795, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 0 	//T2
	.profile2_config={795, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 1		//T1
	.profile3_config={795, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 2		//T3
	.profile4_config={795, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 3
	.dwell=20,
	.settle=100,
	.jumpback=2,
	.txpon={{0,1,1},{0,1,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{0,1,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{0,0,10},{0,10,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_trv1_bsd_info = {
	.profile1_config={805, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 0 	//T2
	.profile2_config={805, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 1		//T1
	.profile3_config={805, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 2		//T3
	.profile4_config={805, 600, 50, 300, 800, 20, 1400, 255 << 8 | 7},	//Profile 3
	.dwell=20,
	.settle=100,
	.jumpback=2,
	.txpon={{0,1,1},{0,1,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{0,1,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{0,0,10},{0,10,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_tr_fcw_info = {
	.profile1_config={775, 150, 30, 210, 1600, 20, 400, 192 << 8 | 6},
	.profile2_config={775, 150, 30, 210, 1600, 20, 400, 192 << 8 | 6},
	.profile3_config={775, 300, 30, 210, 1600, 20, 400, 192 << 8 | 6},
	.profile4_config={775, 300, 30, 210, 1600, 20, 400, 192 << 8 | 6},
	.dwell=5,
	.settle=35,
	.jumpback=2,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{6,6,6,6},{6,6,6,6},{6,6,6,6},{6,6,6,6}},
	.tx_gain = {{0,192,0},{192,0,0},{0,0,192},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_topxgun_fcw_info = {
	.profile1_config={765, 600, 10, 210,  400, 20, 1400, 240 << 8 | 7},
	.profile2_config={765, 600, 10, 210,  400, 20, 1400, 240 << 8 | 7},
	.profile3_config={765, 300, 10, 210,  400, 20, 1400, 240 << 8 | 7},
	.profile4_config={765, 300, 10, 210,  400, 20, 1400, 240 << 8 | 7},
	.dwell=5,
	.settle=65,
	.jumpback=2,
	.txpon={{0,0,0},{0,0,0},{0,0,1},{0,0,0}},
	.txsw={{0,0,0},{0,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = false,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{7,7,7,7}},
	.tx_gain = {{0,0,0},{0,0,0},{0,0,240},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_topxgun_vcw_info = {
	.profile1_config={765, 600,  20, 250,  100, 20, 1400, 5 << 8 | 7},
	.profile2_config={765, 600,  20, 250,  100, 20, 1400, 5 << 8 | 7},
	.profile3_config={765, 600,  20, 250,  100, 20, 1400, 5 << 8 | 0},
	.profile4_config={765, 600,  20, 250,  100, 20, 1400, 5 << 8 | 0},
	.dwell=35,
	.settle=65,
	.jumpback=2,
	.txpon={{0,0,0},{0,0,0},{0,0,1},{0,0,0}},
	.txsw={{0,0,0},{0,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = false,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{0,0,0,0},{0,0,0,0}},
	.tx_gain = {{0,0,0},{0,0,0},{0,0,5},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_bsd_omni_m_info = {
	.profile1_config={765, 150, 1, 196, 400, 20, 1400, 255 << 8 | 7},	//Profile 0 	//T3
	.profile2_config={765, 150, 1, 196, 400, 20, 1400, 255 << 8 | 7},	//Profile 1		//T1
	.profile3_config={765, 150, 1, 196, 400, 20, 1400,   0 << 8 | 0},	//Profile 2
	.profile4_config={765, 150, 1, 196, 400, 20, 1400,   0 << 8 | 0},	//Profile 3
	.dwell=1,
	.settle=65,
	.jumpback=1,
	.txpon={{1,0,1},{1,0,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{1,0,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{0,0,0,0},{0,0,0,0}},
	.tx_gain = {{0,0,255},{255,0,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};

const tef810x_info_t tef810x_bsd_omni_s_info = {
	.profile1_config={767, 150, 1, 196, 400, 20, 1400, 255 << 8 | 7},	//Profile 0 	//T3
	.profile2_config={767, 150, 1, 196, 400, 20, 1400, 255 << 8 | 7},	//Profile 1		//T1
	.profile3_config={767, 150, 1, 196, 400, 20, 1400,   0 << 8 | 0},	//Profile 2
	.profile4_config={767, 150, 1, 196, 400, 20, 1400,   0 << 8 | 0},	//Profile 3
	.dwell=1,
	.settle=65,
	.jumpback=1,
	.txpon={{1,0,1},{1,0,1},{0,0,0},{0,0,0}},
	.txsw={{0,0,1},{1,0,0},{0,0,0},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 960,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{0,0,0,0},{0,0,0,0}},
	.tx_gain = {{0,0,255},{255,0,0},{0,0,0},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0

};

const tef810x_info_t tef810x_fenix_rcw_info = {
	.profile1_config={765, 150, 30, 200, 1600, 20, 400, 220 << 8 | 7},
	.profile2_config={765, 150, 30, 200, 1600, 20, 400, 220 << 8 | 7},
	.profile3_config={765, 300, 30, 200, 1600, 20, 400, 220 << 8 | 7},
	.profile4_config={765, 300, 30, 200, 1600, 20, 400, 220 << 8 | 7},
	.dwell=5,
	.settle=35,
	.jumpback=2,
	.txpon={{1,1,0},{1,1,0},{0,0,1},{0,0,0}},
	.txsw={{0,1,0},{1,0,0},{0,0,1},{0,0,0}},
	.agc_profile = 7,
	.agc_default_gain = 4,
	.narrow_band = true,
	.adc_recalibration = true,
	.tx_calibration = 0,
	.reserved = {0},
	.vco_cal_frame_time = 65535,
	.tidle = {0,0,0,0},
	.rx_gain = {{7,7,7,7},{7,7,7,7},{7,7,7,7},{0,0,0,0}},
	.tx_gain = {{0,220,0},{220,0,0},{0,0,220},{0,0,0}},
	.tx_level_code = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
	                  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
					  {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}},
	.tx_level_table = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
					   {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}},
	.reserved2 = {0, 0},
	.lock_freq_time = 0,
	.lock_freq_tx = 0,
	.lock_freq = 0,
	.tef_dbg = 0
};
*/
#define BOUNDARY_GAP 3.0f
#define BOUNDARY 5.0f
static uint8_t tx_level_status = 0;
int16_t TX_HIGH_LEVEL_TABLE[14][2] = {{-5,3}, {5,3}, {10,3}, {20,2}, {30,0}, {40,1}, {50,3},
		   	   	   	   	   	   	   	  {60,1}, {70,2}, {80,2}, {90,2}, {100,6}, {110,6}, {120,6}};

#define JSON_PROFILE1_CONFIG 	"\t\t\"profile1_config\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_PROFILE2_CONFIG 	"\t\t\"profile2_config\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_PROFILE3_CONFIG 	"\t\t\"profile3_config\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_PROFILE4_CONFIG 	"\t\t\"profile4_config\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_DWELL_TIME		 	"\t\t\"dwell\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_SETTLE_TIME		"\t\t\"settle\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_JUMPBACK_TIME 		"\t\t\"jumpback\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_TX_POW				"\t\t\"txpon\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_TX_SW		 		"\t\t\"txsw\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_AGC_PROFILE		"\t\t\"agc_profile\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_AGC_DEF_GAIN		"\t\t\"agc_default_gain\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_NARROW_BAND 		"\t\t\"narrow_band\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_ADC_CALIBRATION	"\t\t\"adc_recalibration\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_TX_CALIBRATION		"\t\t\"tx_calibration\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_RESERVER			"\t\t\"reserved\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_VCO_CAL_TIME		"\t\t\"vco_cal_frame_time\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_IDLE_TIME			"\t\t\"tidle\":{\"t\":\"u16\",\"o\":%d,\"v\":[%d,%d,%d,%d]},\n"
#define JSON_RX_GAIN			"\t\t\"rx_gain\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_TX_GAIN			"\t\t\"tx_gain\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_TX_LEVEL			"\t\t\"tx_level\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d]},\n"
#define JSON_TX_LEVEL_TABLE 	"\t\t\"tx_level_table\":{\"t\":\"i16\",\"o\":%d,\"v\":[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]},\n"
#define JSON_RESERVER2			"\t\t\"reserved2\":{\"t\":\"u8\",\"o\":%d,\"v\":[%d,%d]},\n"
#define JSON_LOCK_FREQ_TIME     "\t\t\"lock_freq_time\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_LOCK_FREQ_TX       "\t\t\"lock_freq_tx\":{\"t\":\"u8\",\"o\":%d,\"v\":%d},\n"
#define JSON_LOCK_FREQ          "\t\t\"lock_freq\":{\"t\":\"u16\",\"o\":%d,\"v\":%d},\n"
#define JSON_TEF_DBG          	"\t\t\"tef_dbg\":{\"t\":\"u8\",\"o\":%d,\"v\":%d}\n"

static void tef810x_debug_log(void);
static void tef_tx_check(void);
static void set_tef_dbg_flag(char** args, int count);
static void tef_set_tx_table(char** args, int count);
uint8_t rmtp_get_tx_high_level(uint8_t txNum);
uint8_t rmtp_find_tx_high_level(uint8_t txNum, uint16_t txGain);
static void find_tx_high_level_code_test(char** args, int count);
static uint8_t find_tx_high_level_code(uint8_t txNum, uint16_t txGain);
static void send_chirp_test(char** args, int count);
static void send_chirp(uint8_t proileNum, uint16_t chirpNum, uint32_t repeatNum);
static void tef_console_commands_reg(void);
static void tef_pars_dump(void);
static void tef_cal_freq_start(uint8_t subband, uint8_t vco_state, bool narrow_Band);
static void tef_cal_freq_end(void);
static void tef_mclk_recal(void);
static void update_vco_profile_suband(void);
static void push_vco_register_for_vco_cal(void);
static int tef810x_info_in_jsons(char* ws);
static void TEF810x_save(void);
static void set_tef810x_min_gain(uint8_t mode);
static void get_TEF810x_temperature(void);
float get_tef810x_temperature(void);    //temperature min:-40 max:135
//static int get_tef810x_profile0_temperature(float *get_temp);
static void set_tef810x_tx_gain_code(void);
static void cubtek_profile_tx_gain_calibration(uint8_t profile);
void set_tef810x_production_mode(tef810x_production_mode_t production_mode);
//static void check_adc_status(void);

static void chip_lock_freq_mode(uint8_t deci);
//static void chg_tef810x_lock_freq_time(char** args, int count);
static void chip_lock_freq_done(void);
static void callback_test(char** args, int count);
static void error_inject_test(char** args, int count);
static void update_tef810x_status(uint8_t msgId, uint8_t msgSta, uint8_t msgStaCode);
tef810x_status_t set_tef810x_long_profile(sctrl_profiletiming_t* config);
tef810x_status_t unset_tef810x_long_profile(void);
static void set_tef810x_long_profile_test(char** args, int count);
static void tef810x_chip_info(void);
tef810x_status_t rmtp_rf_selftest(uint32_t* data, uint32_t size, bool_t* selftest_result);
static bool_t tef810x_self_test(DolphinIC_rval_t* error_code, uint32_t size);
static DolphinIC_rval_t normal_send_test(uint32_t* ism_message, uint8_t size);
static DolphinIC_rval_t hal_es3_OTP_GetChipInfo_Cubtek(TEF810xDieId_t *pChipInfo);
/******************************************************************************
* EXPORTED VARIABLES
*****************************************************************************/

static tef810x_info_p tef810x_info = &tef810x_parameters.info;
static sctrl_profiletiming_t rf_config[4];
static uint8_t TEF810x_b2_gain;
static uint8_t TEF810x_lox3_gain;
static uint8_t AGC_default_rx_gain = T1_DEFAULT_RX_GAIN;

static tef810x_profile_t TEF810x_profile;
static uint16_t TEF810x_chirp;
static uint16_t TEF810x_repeat;
static int      TEF810x_error_status = 0;
static uint16_t calibrate_ADC_cnt = 0;
static uint8_t  vco_error_cnt = 0;
static uint8_t  mclk_error_cnt = 0;
static uint8_t	tx_default_level_code[3][2] = {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
										       {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
										       {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}};
static uint8_t	tx_cal_level_code[3][2] =     {{RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
										       {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD},
										       {RF_TX_HIGH_LEVEL_THLD, RF_TX_LOW_LEVEL_THLD}};
static int      old_tsen0, old_tsen1;

static double tDwell = 5.0;
static double tSettle = 3.0;
static double var_tDwell[4] = { 0, 0, 0, 0};
static double var_tSettle[4] = { 0, 0, 0, 0};
static double var_idle[4] = { 0, 0, 0, 0};
static double tJumpback = 0.4;
static double sample_time = 12.8;
static float t_idle[4] = {0, 0, 0, 0};
static uint8_t add_time_type = ADD_DWELL_TIME;
static uint8_t cur_agc_profile = 7;
//static bool narrowBand = true;
static uint8_t adc_recalibration = false;
static uint8_t tx_calibration = false;
static int vco_start_subband = 0;
static int vco_stop_subband = 127;
static int vco_current_subband[4] = {0, 0 , 0 , 0};
static rf_gain_info_t rf_gain;
static rf_gain_info_t *rf_gain_p = &rf_gain;
//static bool mclk_recal_flag = false;
//static bool pdc_bwwide = true;
//static bool lock_freq_mode = false;
//static bool re_init_flag = false;
static bool txpon[4][3] = {
	{ 0, 1, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 1 },
	{ 0, 0, 1 }
};

static bool txsw[4][3] = {
	{ 0, 1, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 1 },
	{ 0, 0, 1 }
};

//TX bipolar phase shift
static bool bps[4][3] = {
	{ false, false, false },
	{ false, false, false },
	{ false, false, false },
	{ false, false, false } };

static 	bool rxpon[4][4] = {
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 }
};

static uint8_t tx_gain[4][3] = {
		{255,255,255},
		{255,255,255},
		{255,255,255},
		{255,255,255}
};

static uint8_t rx_gain[4][4] = {
		{7,7,7,7},
		{7,7,7,7},
		{7,7,7,7},
		{7,7,7,7}
};

static uint8_t lock_freq_time = 0;
static uint8_t lock_freq_tx = 0;
static uint16_t lock_freq = 0;

static uint8_t calibrate_vco_state = TEF_VCO_CAL_IDLE;
static uint8_t cur_vco_subband = 0;
static float  cur_vco_start_freq = 0;
static float  cur_vco_end_freq = 0;
static float  cur_vco_bw_freq = 0;

static uint8_t tef_Caliration_status = 0;       // Bit0: 1 ==> during VCO calibration
                                                // Bit1: 1 ==> during ADC calibration
static uint16_t vco_cal_frame_time = 0;
static uint16_t vco_cal_frame_counter = 0;
static uint16_t short_frame_counter = 0;
static float Rf_Temp = 0;
static uint8_t tef_dbg_flag = 0;
static uint8_t production_line_mode = 0;
#ifdef TEF810X_LOG
static uint64_t frame_counter = 0;
#endif
static uint8_t error_inject = 0;
static uint8_t error_table[2][3] = {\
		{MONITOR_ID_MCLK, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED}, \
		{MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED}};
static uint8_t error_inject_table[2][3] = {\
		{MONITOR_ID_MCLK, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED}, \
		{MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED}};
static sctrl_profiletiming_t profile_recover[2] = {{.freq = 0}, {.freq = 0}};
const uint8_t deci_table[4][3] = {{4, 8, 16}, {4, 8, 16}, {2, 4, 8}, {1, 2, 4}};

#ifdef TEF810X_INSERT_TEST
static float Rf_Temp_V = 65.0;
#endif

static dolphin_flag_type dolphin_flag = {
	.narrowband        = true,
    .mclk_recal_flag   = false,
    .pdc_bwwide        = true,
    .lock_freq_mode    = false,
    .re_init_flag      = false,
    .bit5              = false,
    .bit6              = false,
    .bit7              = false
};

//=============================================================================
//Reset Tef810x Functions
//=============================================================================
static void reset_tef810x_chip(void)
{
	uint32_t temp_reg_value;

	temp_reg_value =  SIUL2.GPDO[32].R ;
	SIUL2.GPDO[32].R =  temp_reg_value | 0x01000000;
	Delay_ms(1);
    SIUL2.GPDO[32].R =  temp_reg_value & 0x00FFFFFF;
	Delay_ms(2);
	SIUL2.GPDO[32].R =  temp_reg_value | 0x01000000;
	Delay_ms(1);

}

static void chip_lock_freq_done(void)
{
	pars_ctx_p ret;

    rmtp_lock_frequency_mode_done(tef810x_info->lock_freq_tx>>2);
	tef810x_info->lock_freq_time = 0;
	tef810x_info->lock_freq_tx = 0;
	tef810x_info->lock_freq = 0;
	lock_freq_time = tef810x_info->lock_freq_time;
    lock_freq_tx = tef810x_info->lock_freq_tx;
	lock_freq = tef810x_info->lock_freq;

    ret = pars_set((pars_ctx_p)&tef810x_parameters);

	if (ret == NULL)
		PRINTF("TEF810X lock_freq is error\n");
	else
		PRINTF("TEF810X lock_freq is successful\n");

	dolphin_flag.lock_freq_mode = false;

	reset_system();
}

static void chip_lock_freq_mode(uint8_t deci)
{
	uint16_t NumChirp;
	uint16_t NumSample;
	float SeqInterval = 0.025;
	int profModeSel = 0;
	bool profReset = true;
	float powerOnDelay = 72;
	double CWFrequency = 77e9f;
	int loop0;
//	Nxp_Tef810x_Mod05_ChirpmodeUnion_t Chirpmode_ust;
	uint32_t freqCountSetting;

	dolphin_flag.lock_freq_mode = true;
	NumChirp  = CHIRPS_PER_FRAME;
	NumSample = SAMPLES_PER_CHIRP;

	if (lock_freq != 0)
		CWFrequency = (double)lock_freq * 100000000;
	else
		CWFrequency = rf_config[0].freq;

	chip_CAFC_VCOFreqCalibrate(dolphin_flag.narrowband, vco_start_subband, (vco_stop_subband-vco_start_subband)+1);
	chip_TE_ChirpTrigMode(0, 0, false, false, false, false);
	chip_TE_StaticConfig(NumChirp, SeqInterval, tJumpback, profModeSel, 1, profReset, powerOnDelay, tSettle, 1, 2);
	glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TX_RX_DC_POWER_ON_DELAY_FINE_CONTROL_U16, 0xBF7F3F00, NULL);
	chip_Chirp_CWMode(0, dolphin_flag.narrowband, CWFrequency, NumSample, (float)rf_config[0].loopBW, deci, t_idle[0]);
	// LO setting
	chip_LO_Control(0x01, TEF810x_b2_gain);
	for(loop0=0; loop0<4; loop0++)
	{
		switch(lock_freq_tx)
		{
			case 2:
				chip_reg_Write(TX2_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][1], NULL);
				break;
			case 3:
				chip_reg_Write(TX3_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][2], NULL);
				break;
			default:
				chip_reg_Write(TX1_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][0], NULL);
				break;
		}
	}

	switch(lock_freq_tx)
	{
		case 2:
			chip_TX_Control(2, TRUE, TRUE, TRUE, TRUE);
			break;
		case 3:
			chip_TX_Control(3, TRUE, TRUE, TRUE, TRUE);
			break;
		default:
			chip_TX_Control(1, TRUE, TRUE, TRUE, TRUE);
			break;
	}
	/*******************************************************
	Chip poweron
	Serializer left in functional reset
	*******************************************************/
	chip_CAFC_EnableVCO();

	chip_ATB_Init();
	//Addon to allow for two bit tolerance in the vco 480 clk
	chip_reg_Read(0x06, 0x080, &freqCountSetting, NULL);
	chip_reg_Write(0x06, 0x080, freqCountSetting | 00000030, NULL);
	chip_MCLK_Recalibrate();
	for(loop0 = 0; loop0 < 4; loop0++)
	{
		chip_CAFC_CalibrateAmplitude(loop0);
	}
	chip_ISM_lointf_GainCalibration();

	timer_set("lockfreq", (int16_t) DEFAULT_TICKS_PER_SECOND * lock_freq_time, 1, (event_proc_p)chip_lock_freq_done, NULL);
}


/*******************************************************************************
According Customer ID, product ID and Device id to set default RF parameters
*******************************************************************************/
void set_default_rf_parameters(bool_t er_eeprom_flag)
{
//	uint16_t prod = product_info_get()->product;
//	uint16_t cusid = product_info_get()->customer;
//	uint16_t devid = product_info_get()->device_id;
	memcpy((void*)&tef810x_parameters, (void*)&default_tefp, sizeof(tef810x_pars_t));
/*
	switch(prod)
	{
		case PROD_ID_FCW_2_0_COMBO:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_fcw_combo_info, sizeof(tef810x_fcw_info));
			break;
		case PROD_ID_BSD_2BEAM_DUAL:
		case PROD_ID_BSD_TwoB_2_0_COMBO:
		case PROD_ID_BSD_TwoB_3_1_COMBO:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_bsd_two_beam_m_info, sizeof(tef810x_bsd_two_beam_m_info));
			break;
		case PROD_ID_BSD_OMMIT_DUAL:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_tbb_info, sizeof(tef810x_tbb_info));
			break;
		case PROD_ID_BSD_OMMIT_DUAL_79G:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_bsd_info, sizeof(tef810x_bsd_info));
			break;
		case PROD_ID_BSD_Omni_Master_3p1_COMBO:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_bsd_omni_m_info, sizeof(tef810x_tbb_info));
			break;
		case PROD_ID_BSD_Omni_Slave_1p1_COMBO:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_bsd_omni_s_info, sizeof(tef810x_tbb_info));
			break;
		case PROD_ID_FCW_DUAL:
			if((cusid == CUSTOM_ID_FENIEX) || (cusid == CUSTOM_ID_HPB))
			{
				if((cusid == CUSTOM_ID_FENIEX) || (cusid == CUSTOM_ID_HPB))
					memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_fenix_rcw_info, sizeof(tef810x_fenix_rcw_info));
				else
					memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_tr_fcw_info, sizeof(tef810x_tr_fcw_info));
			}
			else
			{
				memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_fcw_info, sizeof(tef810x_fcw_info));
			}
			break;
		case PROD_ID_FCW_ANT_4_COMBO:
        case PROD_ID_93G003_Combo_Front_Radar_BV3p3:
        case PROD_ID_93G014_MRR_BV1_0_FOR_Hirain:
        case PROD_ID_93G003_Combo_Front_Radar_BV3p4:
		default:
			memcpy((void*)&tef810x_parameters.info, (void*)&tef810x_fcw_info, sizeof(tef810x_fcw_info));
			break;
	}
*/
	if(er_eeprom_flag == TRUE)
		pars_set((pars_ctx_p)&tef810x_parameters);

}

/*******************************************************************************
Function Name : Init_TEF810x
Engineer      : Bruce Chang
Date          : 2016-12-09
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initial TEF810x Function
Issues        : NONE
*******************************************************************************/
void  init_TEF810x(void)
{
	rmtp_rf_ic_status_t rf_status;
	int     rmtp_return, ret;
	uint8_t deci = 1;                   // Sample rate = 40MHz
	uint8_t i,j;
    int16_t pars_get_return;

	TEF810x_b2_gain   = 0x12;
	TEF810x_lox3_gain = 0x11;
	TEF810x_profile   = TEF810X_T2T3;
	TEF810x_chirp     = CHIRPS_PER_FRAME *2;
	TEF810x_repeat    = 1;

	Delay_us(500);

	//reset_tef810x_chip();
	if (dolphin_flag.re_init_flag == false)
	{
		set_default_rf_parameters(FALSE);
		pars_get_return = pars_get((pars_ctx_p)&tef810x_parameters, tef_pars_dump, tef810x_info_in_jsons);
	}
	else
		pars_get_return = 0;
	
	if(pars_get_return != -1)
	{
		rf_config[0].freq         = (double)tef810x_info->profile1_config[0] * 100000000;
		rf_config[0].bandwidth    = (double)tef810x_info->profile1_config[1] * 1000000;
		rf_config[0].tReset       = (double)tef810x_info->profile1_config[2] / 10;
		//rf_config[0].chirp_period = (double)tef810x_info->profile1_config[3] / 10;
		rf_config[0].hpf          = (double)tef810x_info->profile1_config[4] * 1000;
		rf_config[0].lpf          = (double)tef810x_info->profile1_config[5] * 1000000;
		rf_config[0].loopBW       = (double)tef810x_info->profile1_config[6] * 1000;
		rf_config[0].txgain       = (uint8_t)(tef810x_info->profile1_config[7] >> 8);
		rf_config[0].rxgain       = (uint8_t)tef810x_info->profile1_config[7] & 0xFF;
		rf_config[1].freq         = (double)tef810x_info->profile2_config[0] * 100000000;
		rf_config[1].bandwidth    = (double)tef810x_info->profile2_config[1] * 1000000;
		rf_config[1].tReset       = (double)tef810x_info->profile2_config[2] / 10;
		//rf_config[1].chirp_period = (double)tef810x_info->profile2_config[3] / 10;
		rf_config[1].hpf          = (double)tef810x_info->profile2_config[4] * 1000;
		rf_config[1].lpf          = (double)tef810x_info->profile1_config[5] * 1000000;
		rf_config[1].loopBW       = (double)tef810x_info->profile2_config[6] * 1000;
		rf_config[1].txgain       = (uint8_t)(tef810x_info->profile2_config[7] >> 8);
		rf_config[1].rxgain       = (uint8_t)tef810x_info->profile2_config[7] & 0xFF;
		rf_config[2].freq         = (double)tef810x_info->profile3_config[0] * 100000000;
		rf_config[2].bandwidth    = (double)tef810x_info->profile3_config[1] * 1000000;
		rf_config[2].tReset       = (double)tef810x_info->profile3_config[2] / 10;
		//rf_config[2].chirp_period = (double)tef810x_info->profile3_config[3] / 10;
		rf_config[2].hpf          = (double)tef810x_info->profile3_config[4] * 1000;
		rf_config[2].lpf          = (double)tef810x_info->profile3_config[5] * 1000000;
		rf_config[2].loopBW       = (double)tef810x_info->profile3_config[6] * 1000;
		rf_config[2].txgain       = (uint8_t)(tef810x_info->profile3_config[7] >> 8);
		rf_config[2].rxgain       = (uint8_t)tef810x_info->profile3_config[7] & 0xFF;
		rf_config[3].freq         = (double)tef810x_info->profile4_config[0] * 100000000;
		rf_config[3].bandwidth    = (double)tef810x_info->profile4_config[1] * 1000000;
		rf_config[3].tReset       = (double)tef810x_info->profile4_config[2] / 10;
		//rf_config[3].chirp_period = (double)tef810x_info->profile4_config[3] / 10;
		rf_config[3].hpf          = (double)tef810x_info->profile4_config[4] * 1000;
		rf_config[3].lpf          = (double)tef810x_info->profile4_config[5] * 1000000;
		rf_config[3].loopBW       = (double)tef810x_info->profile4_config[6] * 1000;
		rf_config[3].txgain       = (uint8_t)(tef810x_info->profile4_config[7] >> 8);
		rf_config[3].rxgain       = (uint8_t)tef810x_info->profile4_config[7] & 0x7;

		tDwell = (double)tef810x_info->dwell /10;
		tSettle = (double)tef810x_info->settle /10;
		tJumpback = (double)tef810x_info->jumpback /10;
        lock_freq_time = tef810x_info->lock_freq_time;
		lock_freq_tx = tef810x_info->lock_freq_tx & 0x03;
		lock_freq = tef810x_info->lock_freq;

		if(MIPI_NUM_LANES == 4)
		{
			if(MIPI_DATA_RATE == MBITS_480)
				deci = 1;                             // Sample rate = 40MHz/1 = 40 MHz
			else if(MIPI_DATA_RATE == MBITS_240)
				deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
			else
				deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
		}
		else if(MIPI_NUM_LANES == 2)
		{
			if(MIPI_DATA_RATE == MBITS_480)
				deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
			else if(MIPI_DATA_RATE == MBITS_240)
				deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
			else
				deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
		}
		else
		{
			if(MIPI_DATA_RATE == MBITS_480)
				deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
			else if(MIPI_DATA_RATE == MBITS_240)
				deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
			else
				deci = 16;                            // Sample rate = 40MHz/16 = 2.5 MHz
		}
		sample_time = SAMPLES_PER_CHIRP * deci / 40.0f;
		//PRINTF("Profile-0 freq = %lf\n", rf_config[0].freq);
		//PRINTF("Profile-1 freq = %lf\n", rf_config[1].freq);
		//PRINTF("Profile-2 freq = %lf\n", rf_config[2].freq);
		//PRINTF("Profile-3 freq = %lf\n", rf_config[3].freq);
		//memcpy(txpon,&tef810x_info->txpon, sizeof(bool)*12);
		//memcpy(txsw,&tef810x_info->txsw, sizeof(bool)*12);
		for(i=0; i< 4; i++)
		{
			t_idle[i]  =  (float)tef810x_info->tidle[i] /10;
			rf_config[i].chirp_period = tDwell+ tSettle + tJumpback + rf_config[i].tReset + sample_time + t_idle[i];

			for(j=0; j<3; j++)
			{
				txpon[i][j] = (bool) tef810x_info->txpon[i][j];
				txsw[i][j]  = (bool) tef810x_info->txsw[i][j];

				tx_gain[i][j] =  tef810x_info->tx_gain[i][j];
			}

			for(j=0;j<4; j++)
			{
				rx_gain[i][j] =  tef810x_info->rx_gain[i][j] & 0x7;
			}
		}

		cur_agc_profile = (uint8_t)tef810x_info->agc_profile;
		AGC_default_rx_gain = (uint8_t)tef810x_info->agc_default_gain;
		dolphin_flag.narrowband = (bool)tef810x_info->narrow_band;
		adc_recalibration = tef810x_info->adc_recalibration;
		tx_calibration = tef810x_info->tx_calibration;
		vco_cal_frame_time = tef810x_info->vco_cal_frame_time;

		for(i=0; i<3; i++)
		{
			tx_default_level_code[i][0] = tef810x_info->tx_level_code[i][0];
			tx_default_level_code[i][1] = tef810x_info->tx_level_code[i][1];
		}

		for(i=0; i<14; i++)
		{
			TX_HIGH_LEVEL_TABLE[i][0] = tef810x_info->tx_level_table[i][0];
			TX_HIGH_LEVEL_TABLE[i][1] = tef810x_info->tx_level_table[i][1];
		}
		tef_dbg_flag = tef810x_info->tef_dbg;

		rf_gain.lr_rx_gain = tef810x_info->rx_gain[0][0];
		rf_gain.sr_rx_gain = tef810x_info->rx_gain[2][0];

		for (i = 0; i < 3; i++)
		{
			if (tef810x_info->txsw[0][i] != 0) {
				rf_gain.lr_tx_gain = tef810x_info->tx_gain[0][i];
			}
			if (tef810x_info->txsw[2][i] != 0) {
				rf_gain.sr_tx_gain = tef810x_info->tx_gain[2][i];
			}
		}
        rf_gain.lr_hpf = tef810x_info->profile1_config[4];
        rf_gain.sr_hpf = tef810x_info->profile3_config[4];
		IPC_SEND_MSG_Z70(MSG_RF_GAIN_PARS, (void *)rf_gain_p, 0);
	}


	//fs8x_wd_handle(fs8xNormal);
	reset_tef810x_chip();
	rf_status.data_type  = RF_INIT_STATUS;
	rf_status.message_ID = (short) chip_ISM_Init( 0x01, deci, 0x006FF7C2);	//Select data interface. 1:CSI-2, 2:LVDS, 3:CIF-MFIO, 4:CIF-VGIO
	fs8x_wd_handle(fs8xNormal);

	if(adc_recalibration == 2)
	{
		ret = chip_CC_SetDynamicPowerMode(1,0,0,0,1,0,0);
		if (ret != 0) PRINTF("chip_CC_SetDynamicPowerMode failed!(%d)\n", ret);
	}
	else if(adc_recalibration == 1)
	{
		ret = chip_CC_SetDynamicPowerMode(0,0,0,0,0,0,0);
		if (ret != 0) PRINTF("chip_CC_SetDynamicPowerMode failed!(%d)\n", ret);
	}

	if(rf_status.message_ID < 0)
	{
		PRINTF("ISM init error and error no. = %d\n", rf_status.message_ID);
		rmtp_return = rmtp_send_rf_ic_status_message((uint8_t *) &rf_status, sizeof(rf_status));

		update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
		if(rmtp_return == RES_PARAMETER_ERROR)
		PRINTF("Send rmtp message error\n");
	}
	else
	{
		update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
	}

	// Select CSI2 as serializer
	chip_CC_SerializerInterfaceSet(0x1, 480e6);
    #ifdef TEF810x_TEST_MODE
	chip_CSI2_CfgTestMode();
    #endif
	// Configure CSI2
    ret = chip_CSI2_Config(TEF810x_chirp, MIPI_NUM_LANES-1, MIPI_DATA_RATE);
	fs8x_wd_handle(fs8xNormal);


	//chip_CC_IPFuncReset(false, 0x012013C0);

	#ifdef TEST_GPIO
	if(SIUL2.GPDO[0].R & 0x00FF0000)
		SIUL2.GPDO[0].R = SIUL2.GPDO[0].R & 0xFF000000;
	else
		SIUL2.GPDO[0].R = SIUL2.GPDO[0].R | 0x00010101;
	#endif
	if (lock_freq_time !=0)
		chip_lock_freq_mode(deci);
	else
		chip_vco_calibration_and_chip_setup(TRUE, TRUE, TRUE, deci);
	#ifdef TEST_GPIO
	if(SIUL2.GPDO[0].R & 0x00FF0000)
		SIUL2.GPDO[0].R = SIUL2.GPDO[0].R & 0xFF000000;
	else
		SIUL2.GPDO[0].R = SIUL2.GPDO[0].R | 0x00010101;
	#endif

    //chip_reg_Read(CHIRP_AFC_MODULE, cp_register, &regval, NULL);
	//chip_reg_Write(CHIRP_AFC_MODULE, cp_register, regval & 0xFFFFF8FF, NULL);

	// Get temperature at initial status //
	old_tsen0 = -100;
	old_tsen1 = -100;
	calibrate_ADC_cnt = 0;

	tef_console_commands_reg();
}

/*******************************************************************************
Function Name : chip_vco_calibration_and_chip_setup
Engineer      : Bruce Chang
Date          : 2016-12-28
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Calibration chip VCO and setup the TEF810x
Issues        : NONE
*******************************************************************************/
void chip_vco_calibration_and_chip_setup(bool_t calibrate_vco, bool_t setup_freq, bool_t setup_txrx, uint8_t deci)
{
	rmtp_rf_ic_status_t rf_status;
	int      rmtp_return;

	uint16_t NumSample = SAMPLES_PER_CHIRP;//512;
	uint16_t NumChirp = 10;//128;

	/*******************************************************
	User Input Parameters
	*******************************************************/
	//down chirp or up chirp
	bool downChirp = false;

	//bool narrowBand = false;

	//Do CW mode or not. Set desired CW mode frequency.
	bool  CW_Mode = false;
	double CWFrequency = 77e9f;
	int   CW_tx =1;
	int   i;

	double effFc = 76.5e9;
	//Timings (us), tCIF must be a integer multiple of 25ns*deci

	float powerOnDelay = 72;
	//float ISMDelay = 1;
	//float TXPonGroupDelay = 1;
	//float RXPonGroupDelay = 2;


	//Profile sequencing reset after sequence
	bool profReset = true;
	//Profile sequenceing mode, 0-6
	int profModeSel = 0;

	float SeqInterval = 0.025;
	//uint32_t profileStayCnt = 1;
	int    max_cur_subband, min_cur_subband;

	//TX bipolar phase shift
	//bool bps[3] = { false, false, false };

	//TX DC power in TE for 4 profiles
	//for normal power mode:
	//Need to switch DC on for all used TXs in profile 0
	//(even they are not transmitting used in profile0)!!
/*	bool txpon[4][3] = {
		{ 0, 1, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
	};

	//TX SW in TE
	bool txsw[4][3] = {
		{ 0, 1, 0 },
		{ 1, 0, 0 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	};


	//RX DC power in TEu
	bool rxpon[4][4] = {
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	};*/

	int ret;
	int loop0;
	//uint8_t tx_gain;
	Nxp_Tef810x_Mod05_ChirpmodeUnion_t Chirpmode_ust;

//	NumSample = SAMPLES_PER_CHIRP;
//	NumChirp  = CHIRPS_PER_FRAME;

	#ifdef TEF810X_DBG
	float fBegin[128];
	float fEnd[128];
	float BW[128];
	#endif

	//chip_CC_IPFuncReset(false, 0x012013C0);

	/*******************************************************
	VCO calibration
	*******************************************************/
	if(calibrate_vco == TRUE)
	{
		chip_CAFC_VCOFreqCalibrate(true, vco_start_subband, (vco_stop_subband-vco_start_subband)+1);    //serch subband in narrow_band mode
		chip_CAFC_VCOFreqCalibrate(false, vco_start_subband, (vco_stop_subband-vco_start_subband)+1);   //serch subband in wide_band mode
	}

	/*******************************************************
	Chip programming
	*******************************************************/
	if(setup_freq == TRUE)
	{

		for(i=0; i<3; i++)
		{
			if(rf_config[i].bandwidth == 0)
			{
				CW_Mode = true;
				CWFrequency = rf_config[i].freq;
				CW_tx = i+1;
				i=4;                           // exit
			}
		}
		#ifdef TEF810X_DBG
		//get VCO tables to variables
		chip_CAFC_GetVCOTable(dolphin_flag.narrowband, fBegin, fEnd, BW);

		PRINTF("  No.      Fstart              Fstop               BW\n");
		PRINTF("************************************************************\n");
		for(i=0; i<128; i++)
		{
			PRINTF(" %03d  %9.5f  %0.5f  %9.5f\n", i, fBegin[i], fEnd[i], BW[i]);
		}
    	#endif

		//chip_TE_ChirpTrigMode(0, 0, false, true, false, false);
		//chip_TE_StaticConfig(NumChirp, SeqInterval, tJumpback, profModeSel, profileStayCnt, profReset, powerOnDelay, ISMDelay, TXPonGroupDelay, RXPonGroupDelay);
		chip_TE_ChirpTrigMode(0, 0, false, false, false, false);
		chip_TE_StaticConfig(NumChirp, SeqInterval, tJumpback, profModeSel, 1, profReset, powerOnDelay, tSettle, 1, 2);
		// Cubtek force TIMING_ENGINE_MODULE_ADDRESS 0x54 register to 0xBF7F3F00 //
		glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_TX_RX_DC_POWER_ON_DELAY_FINE_CONTROL_U16, 0xBF7F3F00, NULL);

		if (CW_Mode)
		{
			chip_Chirp_CWMode(0, dolphin_flag.narrowband, CWFrequency, NumSample, (float)rf_config[0].loopBW, deci, t_idle[0]);
		}
		else
		{
			// profile settings, system level chirp program
			// profile 0
			effFc = rf_config[0].freq;
			vco_current_subband[0] = chip_Chirp_Program(0, dolphin_flag.narrowband, downChirp, &effFc,(float) rf_config[0].bandwidth, (float)rf_config[0].loopBW, (float)tDwell, (float)tSettle, (float)tJumpback, \
													(float)rf_config[0].tReset, NumSample, deci, dolphin_flag.pdc_bwwide, bps[0], txsw[0], txpon[0], rxpon[0], t_idle[0]);
			#ifdef TEF810X_DBG
			PRINTF("Profile-0 subband = %d\n", vco_current_subband[0]);
			#endif

			max_cur_subband = vco_current_subband[0];
			min_cur_subband = vco_current_subband[0];

			//profile 1
			effFc = rf_config[1].freq;
			vco_current_subband[1] = chip_Chirp_Program(1, dolphin_flag.narrowband, downChirp, &effFc, (float)rf_config[1].bandwidth, (float)rf_config[1].loopBW, (float)tDwell, (float)tSettle, (float)tJumpback, \
													(float)rf_config[1].tReset, NumSample, deci, dolphin_flag.pdc_bwwide, bps[1], txsw[1], txpon[1], rxpon[1], t_idle[1]);
			#ifdef TEF810X_DBG
			PRINTF("Profile-1 subband = %d\n", vco_current_subband[1]);
			#endif

			if(vco_current_subband[1] > max_cur_subband)
				max_cur_subband = vco_current_subband[1];

			if(vco_current_subband[1] < min_cur_subband)
				min_cur_subband = vco_current_subband[1];

			//profile 2
			effFc = rf_config[2].freq;
			vco_current_subband[2] = chip_Chirp_Program(2, dolphin_flag.narrowband, downChirp, &effFc, (float)rf_config[2].bandwidth, (float)rf_config[2].loopBW, (float)tDwell, (float)tSettle, (float)tJumpback, \
													(float)rf_config[2].tReset, NumSample, deci, dolphin_flag.pdc_bwwide, bps[2], txsw[2], txpon[2], rxpon[2], t_idle[2]);
			#ifdef TEF810X_DBG
			PRINTF("Profile-2 subband = %d\n", vco_current_subband[2]);
			#endif

			if(vco_current_subband[2] > max_cur_subband)
				max_cur_subband = vco_current_subband[2];

			if(vco_current_subband[2] < min_cur_subband)
				min_cur_subband = vco_current_subband[2];

			//profile 3
			effFc = rf_config[3].freq;
			vco_current_subband[3] = chip_Chirp_Program(3, dolphin_flag.narrowband, downChirp, &effFc, (float)rf_config[3].bandwidth, (float)rf_config[3].loopBW, (float)tDwell, (float)tSettle, (float)tJumpback, \
													(float)rf_config[3].tReset, NumSample, deci, dolphin_flag.pdc_bwwide, bps[3], txsw[3], txpon[3], rxpon[3], t_idle[3]);
			#ifdef TEF810X_DBG
			PRINTF("Profile-3 subband = %d\n", vco_current_subband[3]);
			#endif

			if(vco_current_subband[3] > max_cur_subband)
				max_cur_subband = vco_current_subband[3];

			if(vco_current_subband[3] < min_cur_subband)
				min_cur_subband = vco_current_subband[3];

			if(min_cur_subband < 0)
			{
				min_cur_subband = 0;
				TEF810x_error_status++;
				PRINTF("Can not find the subband\n");

				rf_status.data_type = RF_VCO_STATUS;
				rf_status.message_ID = VCO_NO_SUBBAND;
				rmtp_return = rmtp_send_rf_ic_status_message((uint8_t *) &rf_status, sizeof(rf_status));

				update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);

				if(rmtp_return == RES_PARAMETER_ERROR)
					PRINTF("Send rmtp message error\n");

				vco_start_subband = 0;
				vco_stop_subband = SEARCH_VCO_RANGE;
			}
			else
			{
				vco_start_subband = min_cur_subband - SEARCH_VCO_RANGE;
				if(vco_start_subband < 0)
					vco_start_subband = 0;

				vco_stop_subband  = max_cur_subband + SEARCH_VCO_RANGE;
				if(vco_stop_subband > 127)
					vco_stop_subband = 127;

				update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
			}
		}

		calibrate_vco_state   = TEF_VCO_CAL_IDLE;
		tef_Caliration_status = 0;
		vco_cal_frame_counter = 0;
		short_frame_counter   = 0;

		cur_vco_subband = vco_start_subband;
	}

	// Disable PLL reset - add by Cubtek Bruce 2018-12-13 //
	glue_reg_Read(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_CHIRPMODE_U16, &Chirpmode_ust.val_u32, NULL);
	Chirpmode_ust.bits_st.PllResetDisable = 1;
	glue_reg_WriteCheck(SWEEP_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD05_CHIRPMODE_U16, Chirpmode_ust.val_u32, NULL);

	// LO setting
	chip_LO_Control(0x01, TEF810x_b2_gain);

	if(setup_txrx == TRUE)
	{
		for(loop0=0; loop0<4; loop0++)
		{
			if(tx_calibration == true)
			{
				// Initial Three Tx gain status when tx auto calibration = true
				if(txsw[loop0][0] == 1)
					tx_gain[loop0][0] = 0xFF;
				else
					tx_gain[loop0][0] = 0x1;

				if(txsw[loop0][1] == 1)
					tx_gain[loop0][1] = 0xFF;
				else
					tx_gain[loop0][1] = 0x1;

				if(txsw[loop0][2] == 1)
					tx_gain[loop0][2] = 0xFF;
				else
					tx_gain[loop0][2] = 0x1;

			}
			chip_reg_Write(TX1_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][0], NULL);

			chip_reg_Write(TX2_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][1], NULL);

			chip_reg_Write(TX3_MODULE, 0x0 + (loop0 * 8), tx_gain[loop0][2], NULL);

			chip_RX_ProfileConfig(1, loop0, rx_gain[loop0][0], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
			chip_RX_ProfileConfig(2, loop0, rx_gain[loop0][1], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
			chip_RX_ProfileConfig(3, loop0, rx_gain[loop0][2], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
			chip_RX_ProfileConfig(4, loop0, rx_gain[loop0][3], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		}

		if (CW_Mode)
		{
			chip_TX_Control(CW_tx, TRUE, TRUE, TRUE, TRUE);
		}
		else
		{
			chip_TX_Control(1, FALSE, FALSE, FALSE, FALSE);
			chip_TX_Control(2, FALSE, FALSE, FALSE, FALSE);
			chip_TX_Control(3, FALSE, FALSE, FALSE, FALSE);
		}
	}

	/*******************************************************
	Chip poweron
	Serializer left in functional reset
	*******************************************************/
	chip_CAFC_EnableVCO();
	//chip_CC_IPFuncReset(false, 0x017FF7C2);

	// Select CSI2 as serializer
	//chip_CC_SerializerInterfaceSet(0x1, 480e6);
	// Configure CSI2
	//chip_CSI2_Config(TEF810x_chirp, 0x03, MIPI_DATA_RATE);

	// Turn off continuous wave mode
	//chip_SC_CWMode(false);
	//chip_SC_CWMode(true);

	ret = chip_ATB_Init();
	if(ret != 0) PRINTF("Init ATB Failed!\n");

	#ifdef DOLPHIN_CFG_ES2
		uint8_t mVer = 0;
		chip_CC_GetMaskVersion(&mVer);
		if (mVer == 2)
		{
			uint32_t freqCountSetting;
			//Addon to allow for two bit tolerance in the vco 480 clk
			chip_reg_Read(0x06, 0x080, &freqCountSetting, NULL);
			chip_reg_Write(0x06, 0x080, freqCountSetting | 0x00000030, NULL);
		}
	#endif

	/*********************************************************
	Calibrations and integrity checks befor chirp
	**********************************************************/
	#ifdef ENABLE_SWT
	clear_SWT0_counter();
	#endif
	fs8x_wd_handle(fs8xNormal);

	PRINTF("MCLK Recalibration...\n");
	ret=chip_MCLK_Recalibrate();
	if (ret != 0) PRINTF("MCLK Recalibration failed!\n");

	PRINTF("Chirp VCO Amplitude Calibration...\n");
	for(loop0 = 0; loop0 < 4; loop0++)
	{
		ret = chip_CAFC_CalibrateAmplitude(loop0);
		if (ret != 0) PRINTF("VCO profile %x Amplitude Calibration Failed!\n", loop0);
	}

	PRINTF("LO Calibration...\n");
	ret = chip_ISM_lointf_GainCalibration();
	if (ret != 0) PRINTF("LO calibration failed!\n");

	Rf_Temp = chip_ATB_ReadTemp(0x1, TX1_MODULE);
	#ifdef TEF810X_INSERT_TEST
	Rf_Temp = Rf_Temp_V;
	#endif

	hal_es3_OTP_CompensateOTP(rf_config[0].freq, 0);

	switch(tx_calibration)
	{
	case 2:
		PRINTF("TX Calibration 2...\n");

		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf[3];
		uint8_t tx_level_status_temp = 0;
		int8_t change_level_val = (int8_t)TX_HIGH_LEVEL_TABLE[0][1];

		glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[0].val_u32, NULL);
		glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[1].val_u32, NULL);
		glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[2].val_u32, NULL);

		for (uint8_t loop = 0; loop < 14; loop++)
		{
			if (Rf_Temp >= ((float)TX_HIGH_LEVEL_TABLE[loop][0] + BOUNDARY))
			{
				if(tx_level_status_temp < 13)
					tx_level_status_temp = loop + 1;
				change_level_val = (int8_t)TX_HIGH_LEVEL_TABLE[tx_level_status_temp][1];
			}
		}

		tx_level_status = tx_level_status_temp;

		FuncsafeMonLevelRf[0].bits_st.LevelRfMinSpi = 0x0;
		FuncsafeMonLevelRf[1].bits_st.LevelRfMinSpi = 0x0;
		FuncsafeMonLevelRf[2].bits_st.LevelRfMinSpi = 0x0;

		FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = tx_default_level_code[0][0] + change_level_val;
		if(FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = 0xF;
		if(FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi < 0x1) FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = 0x1;
		FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = tx_default_level_code[1][0] + change_level_val;
		if(FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = 0xF;
		if(FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi < 0x1) FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = 0x1;
		FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = tx_default_level_code[2][0] + change_level_val;
		if(FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = 0xF;
		if(FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi < 0x1) FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = 0x1;
		FuncsafeMonLevelRf[0].bits_st.LevelRfLowSpi  = 0x0;
		FuncsafeMonLevelRf[1].bits_st.LevelRfLowSpi  = 0x0;
		FuncsafeMonLevelRf[2].bits_st.LevelRfLowSpi  = 0x0;
		glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[0].val_u32, NULL);
		glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[1].val_u32, NULL);
		glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[2].val_u32, NULL);

		if(production_line_mode == kNORMAL_MODE)
		{
			for(loop0 = 0; loop0 < 4; loop0++)
			{
				fs8x_wd_handle(fs8xNormal);
				Delay_us(1);
				#ifdef ENABLE_SWT
				clear_SWT0_counter();
				#endif
				hal_es3_tx_fPCtrl_CalibTxGain_Cubtek(txsw[loop0], loop0, tx_gain[loop0]);
			}
		}

		break;
	case 1:
		PRINTF("TX Calibration 1...\n");
		set_tef810x_tx_gain_code();
		for(loop0 = 0; loop0 < 4; loop0++)
		{
			fs8x_wd_handle(fs8xNormal);
			Delay_us(1);
			#ifdef ENABLE_SWT
			clear_SWT0_counter();
			#endif
//			ret = chip_ISM_tx_GainCalibration(txsw[loop0], loop0);
//			if (ret != 0) PRINTF("Profile %x TX calibration failed!\n", loop0);
			ret = hal_es3_ISM_tx_GainCalibration_Cubtek(txsw[loop0], loop0, tx_gain[loop0]);
			if (ret != 0) PRINTF("Profile %d TX calibration failed!\n", loop0);
		}
		break;
	default:
		set_tef810x_tx_gain_code();
		break;
	}

	#ifdef ENABLE_SWT
	clear_SWT0_counter();
	#endif
	//fs8x_wd_handle(fs8xNormal);

	PRINTF("MCLK integrity check...\n");
	ret = chip_FS_IntegrityCheckMClk(0x1, 480.0);
	if (ret != 0) PRINTF("MCLK integrity check failed!\n");

	PRINTF("TX integrity check...\n");
	ret = chip_ISM_SWTXFit(0);
	if (ret != 0) PRINTF("TX integrity check failed!\n");

	for(uint8_t profile = 0; profile < PROFILE_NUM; profile++)
	{
		DolphinIC_rval_t error_msg;
		if(txsw[profile][0] + txsw[profile][1] + txsw[profile][2])
			PRINTF("TX %d integrity check...", profile);
		else
			continue;
		error_msg = chip_ISM_SWTXFit(profile);
		if (error_msg != DOLPHINIC_NOERROR)
			PRINTF(" failed(%ld)!\n", error_msg);
		else
			PRINTF(" passed!\n");
	}

	for(uint8_t profile = 0; profile < PROFILE_NUM; profile++)
	{
		DolphinIC_rval_t error_msg;
		PRINTF("Chirp %d integrity check ", profile);
		error_msg = chip_ISM_SWChirpFit(profile);
		if(error_msg != DOLPHINIC_NOERROR)
			PRINTF(" failed(%ld)!\n", error_msg);
		else
			PRINTF(" passed!\n");
	}

	fs8x_wd_handle(fs8xNormal);
}

/*******************************************************************************
Function Name : TEF810x_chirp_start
Engineer      : Bruce Chang
Date          : 2016-12-29
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : chirp start by using SPI trigger
Issues        : NONE
*******************************************************************************/
uint8_t TEF810x_chirp_start(tef810x_profile_t send_profile, uint16_t chirp_num, uint16_t profile_repeat_num)
{
	uint32_t get_tef810x_data, repeat_num;
    #ifdef TEF810X_DEBUG
	uint32_t timeout = 3600000;                                       // ~30ms timeout at 120 MHz core clock

	clear_shared_ram();
    #endif

    if (dolphin_flag.lock_freq_mode == TRUE)
	{
		PRINTF("[TEF810x]: Skip the chirp because during in CW mode\n");
		return NULL;
	}
	if(	tef_Caliration_status)
	{
		if(tef_Caliration_status & VCO_CALIBRATION_MASK_FLAG)
		{
			// recover the VCO calibration push register if system is during VCO calibration status
			tef_cal_freq_end();
			calibrate_vco_state   = TEF_VCO_CAL_IDLE;
			vco_cal_frame_counter = 0;
			short_frame_counter   = 0;
			tef_Caliration_status &= ~VCO_CALIBRATION_MASK_FLAG;
		}

		PRINTF("[TEF810x]: Skip the chirp because during in calibration =%x\n", tef_Caliration_status);
		//return tef_Caliration_status;
	}

	TEF810x_profile = send_profile;
	TEF810x_chirp   = chirp_num;
	TEF810x_repeat  = profile_repeat_num;

	//MIPI_CSI2_cfg(MIPI_NUM_LANES, MIPI_DATA_RATE, chirp_num);
	MIPICSI2.PHYC.B.PDRX = 1;                                         // power-down receiver
	MIPICSI2.RXEN.R = 0;                                              // Diable RX
	MIPICSI2.EXPCTDL.R = chirp_num;									  // set expected number of lines in a frame to chirps per frame
	SPT.GBL_CTRL.B.ACQ_EN = 0;
    #ifdef TEF810X_DEBUG
	SPT.SDMA_CTRL1.B.SDMA_BUF_LEN = chirp_num;                        // SDMA buffer length
    #endif
	SPT.ACQ_GBL_CTRL_1.B.NUM_CHRP = chirp_num;                        // number of chirps per frame
	SPT.GBL_CTRL.B.ACQ_EN = 1;
	MIPICSI2.PHYC.B.PDRX = 0;                                         // power-up receiver
	MIPICSI2.RXEN.R = 1;                                              // enable RX

	//chip_CC_IPFuncReset(FALSE, 0x22);

	if(profile_repeat_num <= 1)
		repeat_num = 0x01000000;
	else
		repeat_num = (profile_repeat_num & 0x7F) << 24;

	// XXX TODO Execute IP func reset before chirp start
	chip_reg_Read(CENTRAL_CTRL_MOUDLE, functional_reset_control, &get_tef810x_data, NULL);

	//get_tef810x_data &= ~0x1C0U;
	get_tef810x_data &= ~0x40U;
	chip_reg_Write(CENTRAL_CTRL_MOUDLE, functional_reset_control, get_tef810x_data, NULL);

	//get_tef810x_data |= 0x1C0U;
	get_tef810x_data |= 0x40U;
	chip_reg_Write(CENTRAL_CTRL_MOUDLE, functional_reset_control, get_tef810x_data, NULL);

    //chip_CC_IPFuncReset(TRUE, 0x22);
	//chip_reg_Write(ISM_MODULE, ISM_error_status_and_mcu_reset, 0x00000003, NULL);*/

    #ifdef TEF810x_TEST_MODE
	//write_TEF810x_Reg(CSI2_TX_MODULE, Csi2AdaptConfigReg3, 0x010F0000 | chirp_num);
	//chip_reg_Write(CSI2_MODULE_ADDRESS, CSI2_CSI2ADAPTCONFIGREG3_OFFSET, 0x010F0000 | chirp_num, NULL);
	chip_reg_Write(CSI2_TX_MODULE, Csi2AdaptConfigReg3, 0x010F0000 | chirp_num, NULL);
    #else
	//write_TEF810x_Reg(CSI2_TX_MODULE, Csi2AdaptConfigReg3, 0x00000000 | chirp_num);
	//chip_reg_Write(CSI2_MODULE_ADDRESS, CSI2_CSI2ADAPTCONFIGREG3_OFFSET, 0x00000000 | chirp_num, NULL);
	chip_reg_Write(CSI2_TX_MODULE, Csi2AdaptConfigReg3, 0x00000000, NULL);
    #endif

	//write_TEF810x_Reg(TIMING_ENGINE_MODULE, Chirp_sequence_control, 0x00010000 | chirp_num);
	//chip_reg_Write(TIMING_ENGINE_MODULE, Chirp_sequence_control, 0x00010000 | chirp_num, NULL);
	chip_reg_Read(TIMING_ENGINE_MODULE, Chirp_sequence_control, &get_tef810x_data, NULL);
	get_tef810x_data &= 0xFFFF0000;
	get_tef810x_data |= chirp_num;
	chip_reg_Write(TIMING_ENGINE_MODULE, Chirp_sequence_control, get_tef810x_data, NULL);

//	chip_ISM_SetMCUReset();

	//get_tef810x_data = read_TEF810x_Reg(TIMING_ENGINE_MODULE, chirp_global_control);
	//chip_reg_Read(TENG_MODULE_ADDRESS, TENG_CHIRP_GLOBAL_CONTROL_OFFSET, &get_tef810x_data, NULL);
	chip_reg_Read(TIMING_ENGINE_MODULE, chirp_global_control, &get_tef810x_data, NULL);
	//get_tef810x_data &= 0x80310000;
    get_tef810x_data &= 0x80FFF8FC;
	//first write chirp enable.
	//get_tef810x_data = 0x00010002;
	get_tef810x_data |= (send_profile << 8);
	get_tef810x_data |= repeat_num;
	get_tef810x_data |= (0x01 << 1);
	//write_TEF810x_Reg(TIMING_ENGINE_MODULE, chirp_global_control, get_tef810x_data);     // chirp enable
	//chip_reg_Write(TENG_MODULE_ADDRESS, TENG_CHIRP_GLOBAL_CONTROL_OFFSET, get_tef810x_data, NULL);
	chip_reg_Write(TIMING_ENGINE_MODULE, chirp_global_control, get_tef810x_data, NULL);

	//then write chirp start.
	get_tef810x_data |= 0x01;
	//write_TEF810x_Reg(TIMING_ENGINE_MODULE, chirp_global_control, get_tef810x_data);     // chirp start
	//chip_reg_Write(TENG_MODULE_ADDRESS, TENG_CHIRP_GLOBAL_CONTROL_OFFSET, get_tef810x_data, NULL);
	chip_reg_Write(TIMING_ENGINE_MODULE, chirp_global_control, get_tef810x_data, NULL);

/*	#ifdef TEF810X_DEBUG
	while((!SPT.GBL_STATUS.B.FRM_ACQ_DONE) && (timeout>0)) timeout--; // wait for all the chirps to be acquired
	SPT.GBL_STATUS.R = 0x7;                                           // clear status
	#endif

	#ifdef TEF810X_DEBUG
	if(timeout == 0)
		PRINTF("Get CSi2 data time out\n");

	PRINTF("Send profile%d %d chirps\n", send_profile, chirp_num);
	#endif
	PRINTF("Send profile%d %d chirps\n", send_profile, chirp_num);
*/
	return 1;//tef_Caliration_status;

}

void clear_shared_ram(void)
{
	uint32_t   i;
	uint32_t   *Ram_addr;

	Ram_addr = (void *) 0x40000000;
	for(i=0; i<(256*1024); i++)
		*(Ram_addr+i) = 0;
}


/******************************************************************************
Function Name : get TEF810x initial status
       Return : error code or success(0)
******************************************************************************/
int get_tef810x_init_status(void)
{
	return TEF810x_error_status;
}
/******************************************************************************
Function Name : change frequency and bandwidth with calibrate VCO/not
******************************************************************************/
void get_rf_config(rf_configs_t *  rf_setting)
{
	if(TEF810x_profile < 4)
	{
		rf_setting->freq       = rf_config[TEF810x_profile].freq;
		rf_setting->bw         = rf_config[TEF810x_profile].bandwidth;
		rf_setting->txgain     = rf_config[TEF810x_profile].txgain;
		rf_setting->rxgain     = rf_config[TEF810x_profile].rxgain;
		if(add_time_type == ADD_DWELL_TIME)
			rf_setting->chirp_time = rf_config[TEF810x_profile].chirp_period + var_tDwell[TEF810x_profile];
		else if (add_time_type == ADD_SETTLE_TIME)
			rf_setting->chirp_time = rf_config[TEF810x_profile].chirp_period + var_tSettle[TEF810x_profile];
		else
			rf_setting->chirp_time = rf_config[TEF810x_profile].chirp_period + var_idle[TEF810x_profile];
	}
	else
	{
		if(TEF810x_profile == TEF810X_T2T3)
		{
			rf_setting->freq       = rf_config[TEF810X_T2].freq;
			rf_setting->bw         = rf_config[TEF810X_T2].bandwidth;
			rf_setting->txgain     = rf_config[TEF810X_T2].txgain;
			rf_setting->rxgain     = rf_config[TEF810X_T2].rxgain;
			if(add_time_type == ADD_DWELL_TIME)
				rf_setting->chirp_time = rf_config[TEF810X_T2].chirp_period + var_tDwell[TEF810X_T2];
			else if (add_time_type == ADD_SETTLE_TIME)
				rf_setting->chirp_time = rf_config[TEF810X_T2].chirp_period + var_tSettle[TEF810X_T2];
			else
				rf_setting->chirp_time = rf_config[TEF810X_T2].chirp_period + var_idle[TEF810X_T2];
		}
	}
}

void get_rf_profile_config(tef810x_profile_t pf, rf_configs_t *  rf_setting)
{
	if(pf < 4)
	{
		rf_setting->freq       = rf_config[pf].freq;
		rf_setting->bw         = rf_config[pf].bandwidth;
		rf_setting->txgain     = rf_config[pf].txgain;
		rf_setting->rxgain     = rf_config[pf].rxgain;
		rf_setting->chirp_time = rf_config[pf].chirp_period;
	}
	else
	{
		if(pf == TEF810X_T2T3)
		{
			rf_setting->freq       = rf_config[TEF810X_T2].freq;
			rf_setting->bw         = rf_config[TEF810X_T2].bandwidth;
			rf_setting->txgain     = rf_config[TEF810X_T2].txgain;
			rf_setting->rxgain     = rf_config[TEF810X_T2].rxgain;
			rf_setting->chirp_time = rf_config[TEF810X_T2].chirp_period;
		}
	}
}

/**********************************************************************************
Function Name : chg_Tef810x_profile_dwell_time - Change chirp idle time in running
***********************************************************************************/
void chg_Tef810x_profile_dwell_time(int ProfileNum, int add_dwell_t)
{
    //TX/RX active bits
    uint8_t     txActiveNum;
    uint8_t     rxActiveNum;
    uint8_t     bps_control_bits;
    uint8_t     tx_control_bits;
	int         temp_dwell_time;

    if(ProfileNum < 4 && ProfileNum >= 0)
    {
    	txActiveNum = (((uint8_t)txpon[ProfileNum][2]) << 0x2) | (((uint8_t)txpon[ProfileNum][1]) << 0x01 ) | (uint8_t)txpon[ProfileNum][0];
    	rxActiveNum = (((uint8_t)rxpon[ProfileNum][3]) << 0x03 ) |  (((uint8_t)rxpon[ProfileNum][2]) << 0x02 ) | (((uint8_t)rxpon[ProfileNum][1]) << 0x01 ) | ((uint8_t)rxpon[ProfileNum][0]);
    	tx_control_bits = (((uint8_t)txsw[ProfileNum][2]) << 0x2) | (((uint8_t)txsw[ProfileNum][1]) << 0x01 ) | (uint8_t)txsw[ProfileNum][0];
    	bps_control_bits = ( ((uint8_t)bps[ProfileNum][2]) << 0x02 ) | ( ((uint8_t)bps[ProfileNum][1]) << 0x01 ) | ( ((uint8_t)bps[ProfileNum][0]) );

		temp_dwell_time = tDwell + add_dwell_t;
		if (temp_dwell_time < 0)      //minimum limited protection
			var_tDwell[ProfileNum] = 0 - tDwell;
		else
			var_tDwell[ProfileNum] = (double)add_dwell_t;

    	//Configure Control3 register in Timing Engine
    	hal_es3_teng_UpdateProfChirpPeriod( ProfileNum, txActiveNum, rxActiveNum, (float)(rf_config[ProfileNum].chirp_period+var_tDwell[ProfileNum]));

    	//timing_profile
    	hal_es3_teng_UpdateProfTiming( ProfileNum,
    			(float)(tDwell+var_tDwell[ProfileNum]), false, 75e-3, bps_control_bits, tx_control_bits );

    	add_time_type = ADD_DWELL_TIME;
    }
}

/************************************************************************************
Function Name : chg_Tef810x_profile_settle_time - Change chirp settle time in running
**************************************************************************************/
void chg_Tef810x_profile_settle_time(int ProfileNum, int add_settle_t)
{
	double effFc;
	float  fStart, fStop, usedBW = 0;
	uint8_t subband = 0;
	float  tSample;
	int    SBSelStatus, deci;
	int    temp_settle_time;

    if(ProfileNum < 4 && ProfileNum >= 0)
    {
    	if(MIPI_NUM_LANES == 4)
    	{
    		if(MIPI_DATA_RATE == MBITS_480)
    			deci = 1;                             // Sample rate = 40MHz/1 = 40 MHz
    		else if(MIPI_DATA_RATE == MBITS_240)
    			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
    		else
    			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
    	}
    	else if(MIPI_NUM_LANES == 2)
    	{
    		if(MIPI_DATA_RATE == MBITS_480)
    			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
    		else if(MIPI_DATA_RATE == MBITS_240)
    			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
    		else
    			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
    	}
    	else
    	{
    		if(MIPI_DATA_RATE == MBITS_480)
    			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
    		else if(MIPI_DATA_RATE == MBITS_240)
    			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
    		else
    			deci = 16;                            // Sample rate = 40MHz/16 = 2.5 MHz
    	}

    	tSample = (SAMPLES_PER_CHIRP  * deci * 25.0) / 1000.0;
		temp_settle_time = tSettle + add_settle_t;
		if (temp_settle_time < 0)     //minimum limited protection
			var_tSettle[ProfileNum] = 0 - tSettle;
		else
    		var_tSettle[ProfileNum] = (double)add_settle_t;
    	effFc = rf_config[ProfileNum].freq;
    	subband = 0;
		#ifdef TEF810X_DBG
    	PRINTF(" effFc[%x] = %f\n", ProfileNum, effFc);
		#endif

#ifdef DOLPHIN_CFG_ES3
	#ifndef SB_BINARYSEARCH_ENABLE
			SBSelStatus = chip_CTRL_SubBandSelect(&effFc, (float)rf_config[ProfileNum].bandwidth, (float)(tSettle+var_tSettle[ProfileNum]), tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
	#else
			SBSelStatus = chip_CAFC_SubBandSelectBinarySearch((&effFc, (float)rf_config[i].bandwidth, (float)(tSettle+var_tSettle[ProfileNum]), tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
	#endif
#else
        SBSelStatus = chip_CAFC_SubBandSelect(&effFc, (float)rf_config[ProfileNum].bandwidth, (float)(tSettle+var_tSettle[ProfileNum]), tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
#endif

		#ifdef TEF810X_DBG
		PRINTF("Profile %x, subband = %d\n", ProfileNum, subband);
		#endif
		if(SBSelStatus >= 0)
		{
			//configure power on delay
			hal_es3_teng_CfgDCPowOnDelay(72, (float)(tSettle+var_tSettle[ProfileNum]));

#ifdef DOLPHIN_CFG_ES3
			chip_CAFC_ProfileConfig(ProfileNum, dolphin_flag.narrowband, false, subband, (float)rf_config[ProfileNum].loopBW, usedBW, rf_config[ProfileNum].freq, (float)(tSettle+var_tSettle[ProfileNum]), tSample, (float)tJumpback);
#else
			chip_CAFC_ProfileConfig(ProfileNum, dolphin_flag.narrowband, false, subband, (float)rf_config[ProfileNum].loopBW, usedBW, (float)(tSettle+add_settle_t), tSample, (float)tJumpback);
#endif

			//setup the Timing Engine profile
			chip_TE_ProfileConfig(ProfileNum, (float)tDwell, (float)(tSettle+var_tSettle[ProfileNum]), SAMPLES_PER_CHIRP, deci, dolphin_flag.pdc_bwwide, (float)tDwell + (float)(tSettle+var_tSettle[ProfileNum]) + tSample + (float)tJumpback + (float)rf_config[ProfileNum].tReset + t_idle[ProfileNum],
									bps[ProfileNum], txsw[ProfileNum], txpon[ProfileNum], rxpon[ProfileNum]);

			//setup the Sweep Control profile
			chip_SC_ProfileConfig(ProfileNum, fStart, usedBW, (float)(tSettle+var_tSettle[ProfileNum]), tSample, (float)tJumpback, (float)rf_config[ProfileNum].tReset, false);

			if(ProfileNum == 0)
			{

		    	var_tSettle[1] = (double)add_settle_t;
#ifdef DOLPHIN_CFG_ES3
				chip_CAFC_ProfileConfig(1, dolphin_flag.narrowband, false, subband, (float)rf_config[1].loopBW, usedBW, rf_config[1].freq, (float)(tSettle+var_tSettle[1]), tSample, (float)tJumpback);
#else
				chip_CAFC_ProfileConfig(1, dolphin_flag.narrowband, false, subband, (float)rf_config[1].loopBW, usedBW, (float)(tSettle+add_settle_t), tSample, (float)tJumpback);
#endif

				//setup the Timing Engine profile
				chip_TE_ProfileConfig(1, (float)tDwell, (float)(tSettle+var_tSettle[1]), SAMPLES_PER_CHIRP, deci, false, (float)tDwell + (float)(tSettle+var_tSettle[1]) + tSample + (float)tJumpback + (float)rf_config[1].tReset + t_idle[1],
										bps[1], txsw[1], txpon[1], rxpon[1]);

				//setup the Sweep Control profile
				chip_SC_ProfileConfig(1, fStart, usedBW, (float)(tSettle+var_tSettle[1]), tSample, (float)tJumpback, (float)rf_config[1].tReset, false);

			}

			//set LO level control
			hal_es3_rx_SetLoLevel(effFc);

			hal_es3_cafc_EnableVCO();
		}
		else
		{
			PRINTF("Select subband Failed!!\n");
		}

		add_time_type = ADD_SETTLE_TIME;
	}
}

/******************************************************************************
Function Name : chg_Tef810x_profile_idle_time - Change chirp idle time in running
******************************************************************************/
void chg_Tef810x_profile_idle_time(int ProfileNum, int add_idle_t)
{
    //TX/RX active bits
    uint8_t     txActiveNum;
    uint8_t     rxActiveNum;
	int         temp_idle_time;
//    uint8_t     bps_control_bits;
//    uint8_t     tx_control_bits;

    if(ProfileNum < 4 && ProfileNum >= 0)
    {
    	txActiveNum = (((uint8_t)txpon[ProfileNum][2]) << 0x2) | (((uint8_t)txpon[ProfileNum][1]) << 0x01 ) | (uint8_t)txpon[ProfileNum][0];
    	rxActiveNum = (((uint8_t)rxpon[ProfileNum][3]) << 0x03 ) |  (((uint8_t)rxpon[ProfileNum][2]) << 0x02 ) | (((uint8_t)rxpon[ProfileNum][1]) << 0x01 ) | ((uint8_t)rxpon[ProfileNum][0]);
 //   	tx_control_bits = (((uint8_t)txsw[ProfileNum][2]) << 0x2) | (((uint8_t)txsw[ProfileNum][1]) << 0x01 ) | (uint8_t)txsw[ProfileNum][0];
 //   	bps_control_bits = ( ((uint8_t)bps[ProfileNum][2]) << 0x02 ) | ( ((uint8_t)bps[ProfileNum][1]) << 0x01 ) | ( ((uint8_t)bps[ProfileNum][0]) );
 		temp_idle_time = t_idle[ProfileNum] + add_idle_t;
 		if (temp_idle_time < 0)  //minimum limited protection
	 		var_idle[ProfileNum] = 0 - t_idle[ProfileNum];
		else
 			var_idle[ProfileNum] = (double)add_idle_t;

    	//Configure Control3 register in Timing Engine
    	hal_es3_teng_UpdateProfChirpPeriod( ProfileNum, txActiveNum, rxActiveNum, (float)(rf_config[ProfileNum].chirp_period+var_idle[ProfileNum]));

		add_time_type = ADD_IDLE_TIME;
    }
}

/******************************************************************************
Function Name : change frequency and bandwidth with calibrate VCO/not
******************************************************************************/
static void chg_TEF810x_freq(char** args, int count)
{
	uint16_t chgprofile, reset_t, chirp_p;
	double   effc_freq, effc_bandwith, effc_loopbw;
    uint8_t  i = 0, narrow_band_temp = true;

	if (count > 2)
	{
	chgprofile    = (uint16_t)atoi(args[2]);
	chgprofile    = chgprofile & 0x3;
		PRINTF("change profile = %x\n", chgprofile);
		if(chgprofile == 0)
		{
			if (count > 3)
			{
	effc_freq     = (uint16_t)atoi(args[3]);
				if (effc_freq > TEF810X_FRE_MAX) effc_freq = TEF810X_FRE_MAX;
				else if (effc_freq < TEF810X_FRE_MIN) effc_freq = TEF810X_FRE_MIN;
				tef810x_info->profile1_config[0] = effc_freq;
				rf_config[chgprofile].freq       = effc_freq * 100000000;
				PRINTF("effc_freq = %f\n", rf_config[chgprofile].freq);
			}
			if (count > 4)	
			{
	effc_bandwith = (uint16_t)atoi(args[4]);
				if (effc_bandwith > TEF810X_BW_MAX) effc_bandwith = TEF810X_BW_MAX;
				else if (effc_bandwith < TEF810X_BW_MIN) effc_bandwith = TEF810X_BW_MIN;
				tef810x_info->profile1_config[1] = effc_bandwith;
				rf_config[chgprofile].bandwidth  = effc_bandwith * 1000000;
				PRINTF("effc_bandwith = %f\n", rf_config[chgprofile].bandwidth);
				for (i = 0; i < 4; i++)
				{
					if (rf_config[i].bandwidth >= 1000000000)  //auto setting narrow_band = false if bandwith > 1GHz 
						narrow_band_temp = false;
				}
				if (tef810x_info->narrow_band != (bool)narrow_band_temp)
				{
					tef810x_info->narrow_band = (bool)narrow_band_temp;
					dolphin_flag.narrowband = (bool) tef810x_info->narrow_band;
					PRINTF("/*protection*/ auto setting narrowband = %d\n", narrow_band_temp);
				}
			}
			if (count > 5)
			{
	effc_loopbw   = (uint16_t)atoi(args[5]);
				if (effc_loopbw > TEF810X_LBW_MAX) effc_loopbw = TEF810X_LBW_MAX;
				else if (effc_loopbw < TEF810X_LBW_MIN) effc_loopbw = TEF810X_LBW_MIN;
				tef810x_info->profile1_config[6] = effc_loopbw;
				rf_config[chgprofile].loopBW	 = effc_loopbw;
				PRINTF("effc_loopbw = %f\n", rf_config[chgprofile].loopBW);
			}
			if (count > 6)
	{
				reset_t       = (uint16_t)atoi(args[6]);
				if (reset_t > TEF810X_RESET_T_MAX) reset_t = TEF810X_RESET_T_MAX;
				else if (reset_t < TEF810X_RESET_T_MIN) reset_t = TEF810X_RESET_T_MIN;
		tef810x_info->profile1_config[2] = reset_t;
				rf_config[chgprofile].tReset     = (double) reset_t / 10;
				PRINTF("reset time = %f\n", rf_config[chgprofile].tReset);
			}
			if (count > 7)
			{
				chirp_p       = (uint16_t)atoi(args[7]);
		tef810x_info->profile1_config[3] = chirp_p;
				rf_config[chgprofile].chirp_period = tDwell+ tSettle + tJumpback + rf_config[chgprofile].tReset + sample_time + t_idle[chgprofile];
				PRINTF("chirp period = %f\n", rf_config[chgprofile].chirp_period);
	}
		}
	else if(chgprofile == 1)
	{
			if (count > 3)
			{
				effc_freq     = (uint16_t)atoi(args[3]);
				if (effc_freq > TEF810X_FRE_MAX) effc_freq = TEF810X_FRE_MAX;
				else if (effc_freq < TEF810X_FRE_MIN) effc_freq = TEF810X_FRE_MIN;
		tef810x_info->profile2_config[0] = effc_freq;
				rf_config[chgprofile].freq       = effc_freq * 100000000;
				PRINTF("effc_freq = %f\n", rf_config[chgprofile].freq);
			}
			if (count > 4)	
			{
				effc_bandwith = (uint16_t)atoi(args[4]);
				if (effc_bandwith > TEF810X_BW_MAX) effc_bandwith = TEF810X_BW_MAX;
				else if (effc_bandwith < TEF810X_BW_MIN) effc_bandwith = TEF810X_BW_MIN;
		tef810x_info->profile2_config[1] = effc_bandwith;
				rf_config[chgprofile].bandwidth  = effc_bandwith * 1000000;
				PRINTF("effc_bandwith = %f\n", rf_config[chgprofile].bandwidth);
				for (i = 0; i < 4; i++)
				{
					if (rf_config[i].bandwidth >= 1000000000)  //auto setting narrow_band = false if bandwith > 1GHz 
						narrow_band_temp = false;
				}
				if (tef810x_info->narrow_band != (bool)narrow_band_temp)
				{
					tef810x_info->narrow_band = (bool)narrow_band_temp;
					dolphin_flag.narrowband = (bool) tef810x_info->narrow_band;
					PRINTF("/*protection*/ auto setting narrowband = %d\n", narrow_band_temp);
				}
			}
			if (count > 5)
			{
				effc_loopbw   = (uint16_t)atoi(args[5]);
				if (effc_loopbw > TEF810X_LBW_MAX) effc_loopbw = TEF810X_LBW_MAX;
				else if (effc_loopbw < TEF810X_LBW_MIN) effc_loopbw = TEF810X_LBW_MIN;
				tef810x_info->profile2_config[6] = effc_loopbw;
				rf_config[chgprofile].loopBW	 = effc_loopbw;
				PRINTF("effc_loopbw = %f\n", rf_config[chgprofile].loopBW);
			}
			if (count > 6)
			{
				reset_t       = (uint16_t)atoi(args[6]);
				if (reset_t > TEF810X_RESET_T_MAX) reset_t = TEF810X_RESET_T_MAX;
				else if (reset_t < TEF810X_RESET_T_MIN) reset_t = TEF810X_RESET_T_MIN;
		tef810x_info->profile2_config[2] = reset_t;
				rf_config[chgprofile].tReset     = (double) reset_t / 10;
				PRINTF("reset time = %f\n", rf_config[chgprofile].tReset);
			}
			if (count > 7)
			{
				chirp_p       = (uint16_t)atoi(args[7]);
		tef810x_info->profile2_config[3] = chirp_p;
				rf_config[chgprofile].chirp_period = tDwell+ tSettle + tJumpback + rf_config[chgprofile].tReset + sample_time + t_idle[chgprofile];
				PRINTF("chirp period = %f\n", rf_config[chgprofile].chirp_period);
	}
		}
	else if(chgprofile == 2)
	{
			if (count > 3)
			{
				effc_freq     = (uint16_t)atoi(args[3]);
				if (effc_freq > TEF810X_FRE_MAX) effc_freq = TEF810X_FRE_MAX;
				else if (effc_freq < TEF810X_FRE_MIN) effc_freq = TEF810X_FRE_MIN;
		tef810x_info->profile3_config[0] = effc_freq;
				rf_config[chgprofile].freq       = effc_freq * 100000000;
				PRINTF("effc_freq = %f\n", rf_config[chgprofile].freq);
			}
			if (count > 4)	
			{
				effc_bandwith = (uint16_t)atoi(args[4]);
				if (effc_bandwith > TEF810X_BW_MAX) effc_bandwith = TEF810X_BW_MAX;
				else if (effc_bandwith < TEF810X_BW_MIN) effc_bandwith = TEF810X_BW_MIN;
		tef810x_info->profile3_config[1] = effc_bandwith;
				rf_config[chgprofile].bandwidth  = effc_bandwith * 1000000;
				PRINTF("effc_bandwith = %f\n", rf_config[chgprofile].bandwidth);
				for (i = 0; i < 4; i++)
				{
					if (rf_config[i].bandwidth >= 1000000000)  //auto setting narrow_band = false if bandwith > 1GHz 
						narrow_band_temp = false;
				}
				if (tef810x_info->narrow_band != (bool)narrow_band_temp)
				{
					tef810x_info->narrow_band = (bool)narrow_band_temp;
					dolphin_flag.narrowband = (bool) tef810x_info->narrow_band;
					PRINTF("/*protection*/ auto setting narrowband = %d\n", narrow_band_temp);
				}
			}
			if (count > 5)
			{
				effc_loopbw   = (uint16_t)atoi(args[5]);
				if (effc_loopbw > TEF810X_LBW_MAX) effc_loopbw = TEF810X_LBW_MAX;
				else if (effc_loopbw < TEF810X_LBW_MIN) effc_loopbw = TEF810X_LBW_MIN;
				tef810x_info->profile3_config[6] = effc_loopbw;
				rf_config[chgprofile].loopBW	 = effc_loopbw;
				PRINTF("effc_loopbw = %f\n", rf_config[chgprofile].loopBW);
			}
			if (count > 6)
			{
				reset_t       = (uint16_t)atoi(args[6]);
				if (reset_t > TEF810X_RESET_T_MAX) reset_t = TEF810X_RESET_T_MAX;
				else if (reset_t < TEF810X_RESET_T_MIN) reset_t = TEF810X_RESET_T_MIN;
		tef810x_info->profile3_config[2] = reset_t;
				rf_config[chgprofile].tReset     = (double) reset_t / 10;
				PRINTF("reset time = %f\n", rf_config[chgprofile].tReset);
			}
			if (count > 7)
			{
				chirp_p       = (uint16_t)atoi(args[7]);
		tef810x_info->profile3_config[3] = chirp_p;
				rf_config[chgprofile].chirp_period = tDwell+ tSettle + tJumpback + rf_config[chgprofile].tReset + sample_time + t_idle[chgprofile];
				PRINTF("chirp period = %f\n", rf_config[chgprofile].chirp_period);
	}
		}
		else if(chgprofile == 3)
	{
			if (count > 3)
			{
				effc_freq     = (uint16_t)atoi(args[3]);
				if (effc_freq > TEF810X_FRE_MAX) effc_freq = TEF810X_FRE_MAX;
				else if (effc_freq < TEF810X_FRE_MIN) effc_freq = TEF810X_FRE_MIN;
		tef810x_info->profile4_config[0] = effc_freq;
				rf_config[chgprofile].freq       = effc_freq * 100000000;
				PRINTF("effc_freq = %f\n", rf_config[chgprofile].freq);
			}
			if (count > 4)	
			{
				effc_bandwith = (uint16_t)atoi(args[4]);
				if (effc_bandwith > TEF810X_BW_MAX) effc_bandwith = TEF810X_BW_MAX;
				else if (effc_bandwith < TEF810X_BW_MIN) effc_bandwith = TEF810X_BW_MIN;
		tef810x_info->profile4_config[1] = effc_bandwith;
				rf_config[chgprofile].bandwidth  = effc_bandwith * 1000000;
				PRINTF("effc_bandwith = %f\n", rf_config[chgprofile].bandwidth);
				for (i = 0; i < 4; i++)
				{
					if (rf_config[i].bandwidth >= 1000000000)  //auto setting narrow_band = false if bandwith > 1GHz 
						narrow_band_temp = false;
				}
				if (tef810x_info->narrow_band != (bool)narrow_band_temp)
				{
					tef810x_info->narrow_band = (bool)narrow_band_temp;
					dolphin_flag.narrowband = (bool) tef810x_info->narrow_band;
					PRINTF("/*protection*/ auto setting narrowband = %d\n", narrow_band_temp);
				}
			}
			if (count > 5)
			{
				effc_loopbw   = (uint16_t)atoi(args[5]);
				if (effc_loopbw > TEF810X_LBW_MAX) effc_loopbw = TEF810X_LBW_MAX;
				else if (effc_loopbw < TEF810X_LBW_MIN) effc_loopbw = TEF810X_LBW_MIN;
		tef810x_info->profile4_config[6] = effc_loopbw;
				rf_config[chgprofile].loopBW	 = effc_loopbw;
				PRINTF("effc_loopbw = %f\n", rf_config[chgprofile].loopBW);
	}
			if (count > 6)
			{
				reset_t       = (uint16_t)atoi(args[6]);
				if (reset_t > TEF810X_RESET_T_MAX) reset_t = TEF810X_RESET_T_MAX;
				else if (reset_t < TEF810X_RESET_T_MIN) reset_t = TEF810X_RESET_T_MIN;
				tef810x_info->profile4_config[2] = reset_t;
	rf_config[chgprofile].tReset       = (double) reset_t / 10;
				PRINTF("reset time = %f\n", rf_config[chgprofile].tReset);
			}
			if (count > 7)
			{
				chirp_p       = (uint16_t)atoi(args[7]);
				tef810x_info->profile4_config[3] = chirp_p;
	rf_config[chgprofile].chirp_period = tDwell+ tSettle + tJumpback + rf_config[chgprofile].tReset + sample_time + t_idle[chgprofile];

	PRINTF("chirp period = %f\n", rf_config[chgprofile].chirp_period);
			}
		}
	}
}

/******************************************************************************
Function Name : change tx gain, rx gain and HPF
******************************************************************************/
/*static void chg_TEF810x_gain(char** args, int count)
{
	uint8_t  set_rx_gain, chgprofile;
	double   setHPF, setLPF;

	chgprofile        = (uint8_t)atoi(args[1]);
	chgprofile        = chgprofile & 0x3;
	rf_config[chgprofile].txgain = (uint8_t)atoi(args[2]);
	set_rx_gain       = (uint8_t)atoi(args[3]);
	rf_config[chgprofile].rxgain = set_rx_gain & 0x7;
	if(chgprofile == 0)
	{
		tef810x_info->profile1_config[4] =  (uint16_t)atoi(args[4]);
		tef810x_info->profile1_config[5] =  (uint16_t)atoi(args[5]);
		tef810x_info->profile1_config[7] = (uint16_t) (rf_config[chgprofile].txgain << 8) | rf_config[chgprofile].rxgain;
	}
	else if(chgprofile == 1)
	{
		tef810x_info->profile2_config[4] =  (uint16_t)atoi(args[4]);
		tef810x_info->profile2_config[5] =  (uint16_t)atoi(args[5]);
		tef810x_info->profile2_config[7] = (uint16_t) (rf_config[chgprofile].txgain << 8) | rf_config[chgprofile].rxgain;
	}
	else if(chgprofile == 2)
	{
		tef810x_info->profile3_config[4] =  (uint16_t)atoi(args[4]);
		tef810x_info->profile3_config[5] =  (uint16_t)atoi(args[5]);
		tef810x_info->profile3_config[7] = (uint16_t) (rf_config[chgprofile].txgain << 8) | rf_config[chgprofile].rxgain;
	}
	else
	{
		tef810x_info->profile4_config[4] =  (uint16_t)atoi(args[4]);
		tef810x_info->profile4_config[5] =  (uint16_t)atoi(args[5]);
		tef810x_info->profile4_config[7] = (uint16_t) (rf_config[chgprofile].txgain << 8) | rf_config[chgprofile].rxgain;
	}

	setHPF                    = (double)atoi(args[4]);
	rf_config[chgprofile].hpf = setHPF * 1000;
	setLPF                    = (double)atoi(args[5]);
	rf_config[chgprofile].lpf = setLPF * 1000000;

	//change_tef810x_gain();

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("TX gain= %x\n", rf_config[chgprofile].txgain);
	PRINTF("RX gain= %x\n", rf_config[chgprofile].rxgain);
	PRINTF("HPF = %f\n", rf_config[chgprofile].hpf);
	PRINTF("LPF = %f\n", rf_config[chgprofile].lpf);
}*/

/******************************************************************************
Function Name : change tx gain setting(need to store with tefsave command)
******************************************************************************/
static void chg_tef810x_txgain(char** args, int count)
{
	uint8_t  chgprofile;

	chgprofile        = (uint8_t)atoi(args[2]);
	chgprofile        = chgprofile & 0x3;

	if(count > 3)
	{
		tx_gain[chgprofile][0]               = (uint8_t)atoi(args[3]);
		tef810x_info->tx_gain[chgprofile][0] = tx_gain[chgprofile][0];
	}
	if(count > 4)
	{
		tx_gain[chgprofile][1]               = (uint8_t)atoi(args[4]);
		tef810x_info->tx_gain[chgprofile][1] = tx_gain[chgprofile][1];
	}
	if(count > 5)
	{
		tx_gain[chgprofile][2]               = (uint8_t)atoi(args[5]);
		tef810x_info->tx_gain[chgprofile][2] = tx_gain[chgprofile][2];
	}

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("TX gain= {%d,%d,%d}\n", tx_gain[chgprofile][0], tx_gain[chgprofile][1], tx_gain[chgprofile][2]);

}

/******************************************************************************
Function Name : change rx gain setting (need to store with tefsave command)
******************************************************************************/
static void chg_tef810x_rxgain(char** args, int count)
{
	uint8_t  chgprofile;

	chgprofile        = (uint8_t)atoi(args[2]);
	chgprofile        = chgprofile & 0x3;

	if(count > 3)
	{
		rx_gain[chgprofile][0]               = (uint8_t)atoi(args[3]) & 0x7;
		tef810x_info->rx_gain[chgprofile][0] = rx_gain[chgprofile][0];
	}
	if(count > 4)
	{
		rx_gain[chgprofile][1]               = (uint8_t)atoi(args[4]) & 0x7;
		tef810x_info->rx_gain[chgprofile][1] = rx_gain[chgprofile][1];
	}
	if(count > 5)
	{
		rx_gain[chgprofile][2]               = (uint8_t)atoi(args[5]) & 0x7;
		tef810x_info->rx_gain[chgprofile][2] = rx_gain[chgprofile][2];
	}
	if(count > 6)
	{
		rx_gain[chgprofile][3]               = (uint8_t)atoi(args[6]) & 0x7;
		tef810x_info->rx_gain[chgprofile][3] = rx_gain[chgprofile][3];
	}

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("RX gain= {%d,%d,%d,%d}\n", rx_gain[chgprofile][0], rx_gain[chgprofile][1], rx_gain[chgprofile][2], rx_gain[chgprofile][3]);

}

/******************************************************************************
Function Name : change HPF LPF setting
******************************************************************************/
static void chg_tef810x_filter(char** args, int count)
{
	uint8_t  chgprofile;
	double   setHPF, setLPF;
	uint16_t *profile_HPF_config, *profile_LPF_config;

	chgprofile        = (uint8_t)atoi(args[2]);
	chgprofile        = chgprofile & 0x3;

	if(chgprofile == 0)
	{
		profile_HPF_config = tef810x_info->profile1_config+4;
		profile_LPF_config = tef810x_info->profile1_config+5;
	}
	else if(chgprofile == 1)
	{
		profile_HPF_config = tef810x_info->profile2_config+4;
		profile_LPF_config = tef810x_info->profile2_config+5;
	}
	else if(chgprofile == 2)
	{
		profile_HPF_config = tef810x_info->profile3_config+4;
		profile_LPF_config = tef810x_info->profile3_config+5;
	}
	else
	{
		profile_HPF_config = tef810x_info->profile4_config+4;
		profile_LPF_config = tef810x_info->profile4_config+5;
	}

	if(count > 3)
	{
		setHPF                    = (double)atoi(args[3]);
		if (setHPF > TEF810X_HP_MAX) setHPF = TEF810X_HP_MAX;
		else if (setHPF < TEF810X_HP_MIN) setHPF = TEF810X_HP_MIN;
		*profile_HPF_config       = setHPF;
		rf_config[chgprofile].hpf = setHPF * 1000;
	}
	if(count > 4)
	{
		setLPF                    = (double)atoi(args[4]);
		if (setLPF > TEF810X_LP_MAX) setLPF = TEF810X_LP_MAX;
		else if (setLPF < TEF810X_LP_MIN) setLPF = TEF810X_LP_MIN;
		*profile_LPF_config       = setLPF;
		rf_config[chgprofile].lpf = setLPF * 1000000;
	}

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("HPF = %f\n", rf_config[chgprofile].hpf);
	PRINTF("LPF = %f\n", rf_config[chgprofile].lpf);
}

/******************************************************************************
Function Name : change TEF810x basic wave form
******************************************************************************/
static void chg_TEF810x_chirp(char** args, int count)
{
	uint16_t dwell_temp;
	uint16_t settle_temp;
	uint16_t jumpback_temp;
	uint16_t tidle_temp;
	uint8_t  i = 0, narrow_band_temp = false;
	if(count > 2)
	{
		dwell_temp = (uint16_t) atoi(args[2]);
		if (dwell_temp > TEF810X_DWELL_T_MAX) dwell_temp = TEF810X_DWELL_T_MAX;
		else if (dwell_temp < TEF810X_DWELL_T_MIN) dwell_temp = TEF810X_DWELL_T_MIN;
		tef810x_info->dwell = dwell_temp;
		tDwell    = (double) tef810x_info->dwell / 10;
	}
	if(count > 3)
	{
		settle_temp = (uint16_t) atoi(args[3]);
		if (settle_temp > TEF810X_SETTLE_T_MAX) settle_temp = TEF810X_SETTLE_T_MAX;
		else if (settle_temp < TEF810X_SETTLE_T_MIN) settle_temp = TEF810X_SETTLE_T_MIN;		
		tef810x_info->settle = settle_temp;
		tSettle   = (double) tef810x_info->settle / 10;
	}
	if(count > 4)
	{
		jumpback_temp = (uint16_t) atoi(args[4]);
		if (jumpback_temp > TEF810X_JUMPBACK_T_MAX) jumpback_temp = TEF810X_JUMPBACK_T_MAX;
		else if (jumpback_temp < TEF810X_JUMPBACK_T_MIN) jumpback_temp = TEF810X_JUMPBACK_T_MIN;			
		tef810x_info->jumpback = jumpback_temp;
		tJumpback = (double) tef810x_info->jumpback / 10;
	}
	if(count > 5)
	{
		tef810x_info->agc_profile = (uint8_t) atoi(args[5]) & 0x7;
		cur_agc_profile = tef810x_info->agc_profile;
	}
	if(count > 6)
	{
		narrow_band_temp = (uint8_t) atoi(args[6]) & 0x1;
		if (narrow_band_temp == true)
		{
			for (i = 0; i < 4; i++)
			{
				if (rf_config[i].bandwidth >= 1000000000)  //auto setting narrow_band = false if bandwith > 1GHz 
					narrow_band_temp = false;
			}
		    if (narrow_band_temp == false)
				PRINTF("/*protection*/ auto setting narrowband = %d\n", narrow_band_temp);
		}
		tef810x_info->narrow_band = (bool)narrow_band_temp;
		dolphin_flag.narrowband = (bool) tef810x_info->narrow_band;
	}
	if(count > 7)
	{
		tidle_temp = (uint16_t) atoi(args[7]);
		if (tidle_temp > TEF810X_IDLE_T_MAX) tidle_temp = TEF810X_IDLE_T_MAX;
		else if (tidle_temp < TEF810X_IDLE_T_MIN) tidle_temp = TEF810X_IDLE_T_MIN;			
		tef810x_info->tidle[0] = tidle_temp;
		t_idle[0]   = (float) tef810x_info->tidle[0] / 10;
	}
	if(count > 8)
	{
		tidle_temp = (uint16_t) atoi(args[8]);
		if (tidle_temp > TEF810X_IDLE_T_MAX) tidle_temp = TEF810X_IDLE_T_MAX;
		else if (tidle_temp < TEF810X_IDLE_T_MIN) tidle_temp = TEF810X_IDLE_T_MIN;		
		tef810x_info->tidle[1] = tidle_temp;
		t_idle[1]   = (float) tef810x_info->tidle[1] / 10;
	}
	if(count > 9)
	{
		tidle_temp = (uint16_t) atoi(args[9]);
		if (tidle_temp > TEF810X_IDLE_T_MAX) tidle_temp = TEF810X_IDLE_T_MAX;
		else if (tidle_temp < TEF810X_IDLE_T_MIN) tidle_temp = TEF810X_IDLE_T_MIN;	
		tef810x_info->tidle[2] = tidle_temp;
		t_idle[2]   = (float) tef810x_info->tidle[2] / 10;
	}	
	if(count > 10)
	{
		tidle_temp = (uint16_t) atoi(args[10]);
		if (tidle_temp > TEF810X_IDLE_T_MAX) tidle_temp = TEF810X_IDLE_T_MAX;
		else if (tidle_temp < TEF810X_IDLE_T_MIN) tidle_temp = TEF810X_IDLE_T_MIN;	
		tef810x_info->tidle[3] = tidle_temp;
		t_idle[3]   = (float) tef810x_info->tidle[3] / 10;
	}



	rf_config[0].chirp_period = tDwell+ tSettle + tJumpback + rf_config[0].tReset + sample_time + t_idle[0];
	rf_config[1].chirp_period = tDwell+ tSettle + tJumpback + rf_config[1].tReset + sample_time + t_idle[1];
	rf_config[2].chirp_period = tDwell+ tSettle + tJumpback + rf_config[2].tReset + sample_time + t_idle[2];
	rf_config[3].chirp_period = tDwell+ tSettle + tJumpback + rf_config[3].tReset + sample_time + t_idle[3];

	PRINTF("tDwell = %f\n", tDwell);
	PRINTF("tSettle = %f\n", tSettle);
	PRINTF("tJumpback = %f\n", tJumpback);
	PRINTF("cur_agc_profile = %x\n", cur_agc_profile);

	if(dolphin_flag.narrowband)
	    PRINTF("narrowband = TRUE\n");
	else
	    PRINTF("narrowband = FALSE\n");

	PRINTF("profile t_idle = [%f, %f, %f, %f]\n", t_idle[0], t_idle[1], t_idle[2], t_idle[3]);
}

/******************************************************************************
Function Name : change TEF810x 4 profile's TX power and switch
******************************************************************************/
static void chg_TEF810x_switch(char** args, int count)
{
	if(count > 2)
	{
		tef810x_info->txsw[0][0] = (uint8_t) strtoul(args[2],NULL, 16) & 0x1;
		txsw[0][0] = tef810x_info->txsw[0][0];
	}
	if(count > 3)
	{
		tef810x_info->txsw[0][1] = (uint8_t) strtoul(args[3],NULL, 16) & 0x1;
		txsw[0][1] = tef810x_info->txsw[0][1];
	}
	if(count > 4)
	{
		tef810x_info->txsw[0][2] = (uint8_t) strtoul(args[4],NULL, 16) & 0x1;
		txsw[0][2] = tef810x_info->txsw[0][2];
	}
	if(count > 5)
	{
		tef810x_info->txsw[1][0] = (uint8_t) strtoul(args[5],NULL, 16) & 0x1;
		txsw[1][0] = tef810x_info->txsw[1][0];
	}
	if(count > 6)
	{
		tef810x_info->txsw[1][1] = (uint8_t) strtoul(args[6],NULL, 16) & 0x1;
		txsw[1][1] = tef810x_info->txsw[1][1];
	}
	if(count > 7)
	{
		tef810x_info->txsw[1][2] = (uint8_t) strtoul(args[7],NULL, 16) & 0x1;
		txsw[1][2] = tef810x_info->txsw[1][2];
	}
	if(count > 8)
	{
		tef810x_info->txsw[2][0] = (uint8_t) strtoul(args[8],NULL, 16) & 0x1;
		txsw[2][0] = tef810x_info->txsw[2][0];
	}
	if(count > 9)
	{
		tef810x_info->txsw[2][1] = (uint8_t) strtoul(args[9],NULL, 16) & 0x1;
		txsw[2][1] = tef810x_info->txsw[2][1];
	}
	if(count > 10)
	{
		tef810x_info->txsw[2][2] = (uint8_t) strtoul(args[10],NULL, 16) & 0x1;
		txsw[2][2] = tef810x_info->txsw[2][2];
	}
	if(count > 11)
	{
		tef810x_info->txsw[3][0] = (uint8_t) strtoul(args[11],NULL, 16) & 0x1;
		txsw[3][0] = tef810x_info->txsw[3][0];
	}
	if(count > 12)
	{
		tef810x_info->txsw[3][1] = (uint8_t) strtoul(args[12],NULL, 16) & 0x1;
		txsw[3][1] = tef810x_info->txsw[3][1];
	}
	if(count > 13)
	{
		tef810x_info->txsw[3][2] = (uint8_t) strtoul(args[13],NULL, 16) & 0x1;
		txsw[3][2] = tef810x_info->txsw[3][2];
	}

	PRINTF("TX switch={{%x,%x,%x},", txsw[0][0],  txsw[0][1],  txsw[0][2]);
	PRINTF("{%x,%x,%x},", txsw[1][0],  txsw[1][1],  txsw[1][2]);
	PRINTF("{%x,%x,%x},", txsw[2][0],  txsw[2][1],  txsw[2][2]);
	PRINTF("{%x,%x,%x}}\n", txsw[3][0],  txsw[3][1],  txsw[3][2]);
}

/******************************************************************************
Function Name : change TEF810x 4 profile's TX power and switch
******************************************************************************/
static void chg_TEF810x_enable(char** args, int count)
{
	if(count > 2)
	{
		tef810x_info->txpon[0][0] = (uint8_t) strtoul(args[2],NULL, 16) & 0x1;
		txpon[0][0] = (bool) tef810x_info->txpon[0][0];
	}
	if(count > 3)
	{
		tef810x_info->txpon[0][1] = (uint8_t) strtoul(args[3],NULL, 16) & 0x1;
		txpon[0][1] = (bool) tef810x_info->txpon[0][1];
	}
	if(count > 4)
	{
		tef810x_info->txpon[0][2] = (uint8_t) strtoul(args[4],NULL, 16) & 0x1;
		txpon[0][2] = (bool) tef810x_info->txpon[0][2];
	}
	if(count > 5)
	{
		tef810x_info->txpon[1][0] = (uint8_t) strtoul(args[5],NULL, 16) & 0x1;
		txpon[1][0] = (bool) tef810x_info->txpon[1][0];
	}
	if(count > 6)
	{
		tef810x_info->txpon[1][1] = (uint8_t) strtoul(args[6],NULL, 16) & 0x1;
		txpon[1][1] = (bool) tef810x_info->txpon[1][1];
	}
	if(count > 7)
	{
		tef810x_info->txpon[1][2] = (uint8_t) strtoul(args[7],NULL, 16) & 0x1;
		txpon[1][2] = (bool) tef810x_info->txpon[1][2];
	}
	if(count > 8)
	{
		tef810x_info->txpon[2][0] = (uint8_t) strtoul(args[8],NULL, 16) & 0x1;
		txpon[2][0] = (bool) tef810x_info->txpon[2][0];
	}
	if(count > 9)
	{
		tef810x_info->txpon[2][1] = (uint8_t) strtoul(args[9],NULL, 16) & 0x1;
		txpon[2][1] = (bool) tef810x_info->txpon[2][1];
	}
	if(count > 10)
	{
		tef810x_info->txpon[2][2] = (uint8_t) strtoul(args[10],NULL, 16) & 0x1;
		txpon[2][2] = (bool) tef810x_info->txpon[2][2];
	}
	if(count > 11)
	{
		tef810x_info->txpon[3][0] = (uint8_t) strtoul(args[11],NULL, 16) & 0x1;
		txpon[3][0] = (bool) tef810x_info->txpon[3][0];
	}
	if(count > 12)
	{
		tef810x_info->txpon[3][1] = (uint8_t) strtoul(args[12],NULL, 16) & 0x1;
		txpon[3][1] = (bool) tef810x_info->txpon[3][1];
	}
	if(count > 13)
	{
		tef810x_info->txpon[3][2] = (uint8_t) strtoul(args[13],NULL, 16) & 0x1;
		txpon[3][2] = (bool) tef810x_info->txpon[3][2];
	}

	PRINTF("TX power={{%x,%x,%x},", txpon[0][0],  txpon[0][1],  txpon[0][2]);
	PRINTF("{%x,%x,%x},", txpon[1][0],  txpon[1][1],  txpon[1][2]);
	PRINTF("{%x,%x,%x},", txpon[2][0],  txpon[2][1],  txpon[2][2]);
	PRINTF("{%x,%x,%x}}\n", txpon[3][0],  txpon[3][1],  txpon[3][2]);
}

/******************************************************************************
Function Name : change TEF810x ADC re-calibration function status
******************************************************************************/
static void chg_TEF810x_adc_recalibration_flag(char** args, int count)
{
	if(count > 2)
	{
		uint8_t temp_flag = (uint8_t)atoi(args[2]);
		if (temp_flag < 0 || temp_flag > 2)
		{
			PRINTF("ADC Cal Flag must between 0~2\n");
			return;
		}
		tef810x_info->adc_recalibration = temp_flag;
		adc_recalibration = temp_flag;
	}
	PRINTF("ADC recalibration function = %d-",adc_recalibration);
	if(adc_recalibration == 2)
		PRINTF("Background_Cal\n");
	else if(adc_recalibration == 1)
		PRINTF("Manual_Cal\n");
	else
		PRINTF("Disable\n");
}

/******************************************************************************
Function Name : change TEF810x TX init-calibration function status
******************************************************************************/
static void chg_TEF810x_tx_calibration_flag(char** args, int count)
{
	if(count > 2)
	{
		tef810x_info->tx_calibration = (uint8_t)atoi(args[2]);
		tx_calibration = tef810x_info->tx_calibration;

		if (tx_calibration > 2)
		{
			PRINTF("Tx_Cal Invalid\n");
			return;
		}

		PRINTF("TX calibration function = %d-", tx_calibration);
		if(tx_calibration == 2)
			PRINTF("Track_High_Level\n");
		else if(tx_calibration == 1)
			PRINTF("Interval_Low & High\n");
	else
			PRINTF("Disable\n");
}
}

/******************************************************************************
Function Name : save TEF810x system parameters
******************************************************************************/
static void TEF810x_save(void)
{
	pars_set((pars_ctx_p)&tef810x_parameters);
	get_tef810x_info(NULL, 0);
}

/******************************************************************************
Function Name : save TEF810x system parameters from data buffer
******************************************************************************/
static void tef_pars_dump(void)
{
	PRINTF("<TEF810X>\n- version: %d \n- size: %d\n", tef810x_parameters.hdr.version, sizeof(tef810x_pars_t));
	PRINTF("- profile1: {%d,%d,%d,%d,%d,%d,%d,%d}\n",
		tef810x_info->profile1_config[0], tef810x_info->profile1_config[1], tef810x_info->profile1_config[2],
		tef810x_info->profile1_config[3], tef810x_info->profile1_config[4], tef810x_info->profile1_config[5],
		tef810x_info->profile1_config[6], tef810x_info->profile1_config[7]);
	PRINTF("- profile2: {%d,%d,%d,%d,%d,%d,%d,%d}\n",
		tef810x_info->profile2_config[0], tef810x_info->profile2_config[1], tef810x_info->profile2_config[2],
		tef810x_info->profile2_config[3], tef810x_info->profile2_config[4], tef810x_info->profile2_config[5],
		tef810x_info->profile2_config[6], tef810x_info->profile2_config[7]);
	PRINTF("- profile3: {%d,%d,%d,%d,%d,%d,%d,%d}\n",
		tef810x_info->profile3_config[0], tef810x_info->profile3_config[1], tef810x_info->profile3_config[2],
		tef810x_info->profile3_config[3], tef810x_info->profile3_config[4], tef810x_info->profile3_config[5],
		tef810x_info->profile3_config[6], tef810x_info->profile3_config[7]);
	PRINTF("- profile4: {%d,%d,%d,%d,%d,%d,%d,%d}\n",
		tef810x_info->profile4_config[0], tef810x_info->profile4_config[1], tef810x_info->profile4_config[2],
		tef810x_info->profile4_config[3], tef810x_info->profile4_config[4], tef810x_info->profile4_config[5],
		tef810x_info->profile4_config[6], tef810x_info->profile4_config[7]);
	PRINTF("- dwell: %d \n- settle: %d \n- jumpback: %d\n", tef810x_info->dwell, tef810x_info->settle, tef810x_info->jumpback);
	PRINTF("- txpon: {{%d,%d,%d},{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}}\n",
		tef810x_info->txpon[0][0], tef810x_info->txpon[0][1], tef810x_info->txpon[0][2],
 		tef810x_info->txpon[1][0], tef810x_info->txpon[1][1], tef810x_info->txpon[1][2],
 		tef810x_info->txpon[2][0], tef810x_info->txpon[2][1], tef810x_info->txpon[2][2],
 		tef810x_info->txpon[3][0], tef810x_info->txpon[3][1], tef810x_info->txpon[3][2]);
	PRINTF("- txsw: {{%d,%d,%d},{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}}\n",
		tef810x_info->txsw[0][0], tef810x_info->txsw[0][1], tef810x_info->txsw[0][2],
 		tef810x_info->txsw[1][0], tef810x_info->txsw[1][1], tef810x_info->txsw[1][2],
 		tef810x_info->txsw[2][0], tef810x_info->txsw[2][1], tef810x_info->txsw[2][2],
 		tef810x_info->txsw[3][0], tef810x_info->txsw[3][1], tef810x_info->txsw[3][2]);
	PRINTF("- agc_profile: %d\n", tef810x_info->agc_profile);
	PRINTF("- agc_default_gain: %d\n", tef810x_info->agc_default_gain);
	PRINTF("- narrow_band: %d\n", tef810x_info->narrow_band);
	PRINTF("- adc_recalibration: %d\n", tef810x_info->adc_recalibration);
	PRINTF("- tx_calibration: %d \n", tef810x_info->tx_calibration);
	PRINTF("- reserved: {%d}\n", tef810x_info->reserved[0]);
	PRINTF("- vco_cal_frame_time: %d\n", tef810x_info->vco_cal_frame_time);
	PRINTF("- tidle = {%d,%d,%d,%d}\n", tef810x_info->tidle[0], tef810x_info->tidle[1], tef810x_info->tidle[2], tef810x_info->tidle[3]);
	PRINTF("- rx_gain = {{%d,%d,%d,%d},", tef810x_info->rx_gain[0][0], tef810x_info->rx_gain[0][1], tef810x_info->rx_gain[0][2], tef810x_info->rx_gain[0][3]);
	PRINTF("{%d,%d,%d,%d},", tef810x_info->rx_gain[1][0], tef810x_info->rx_gain[1][1], tef810x_info->rx_gain[1][2], tef810x_info->rx_gain[1][3]);
	PRINTF("{%d,%d,%d,%d},", tef810x_info->rx_gain[2][0], tef810x_info->rx_gain[2][1], tef810x_info->rx_gain[2][2], tef810x_info->rx_gain[2][3]);
	PRINTF("{%d,%d,%d,%d}}\n", tef810x_info->rx_gain[3][0], tef810x_info->rx_gain[3][1], tef810x_info->rx_gain[3][2], tef810x_info->rx_gain[3][3]);
	PRINTF("- tx_gain = {{%d,%d,%d},", tef810x_info->tx_gain[0][0], tef810x_info->tx_gain[0][1], tef810x_info->tx_gain[0][2]);
	PRINTF("{%d,%d,%d},", tef810x_info->tx_gain[1][0], tef810x_info->tx_gain[1][1], tef810x_info->tx_gain[1][2]);
	PRINTF("{%d,%d,%d},", tef810x_info->tx_gain[2][0], tef810x_info->tx_gain[2][1], tef810x_info->tx_gain[2][2]);
	PRINTF("{%d,%d,%d}}\n", tef810x_info->tx_gain[3][0], tef810x_info->tx_gain[3][1], tef810x_info->tx_gain[3][2]);
	PRINTF("- tx_level_code = {{%d,%d},", tef810x_info->tx_level_code[0][0], tef810x_info->tx_level_code[0][1]);
	PRINTF("{%d,%d},", tef810x_info->tx_level_code[1][0], tef810x_info->tx_level_code[1][1]);
	PRINTF("{%d,%d}}\n", tef810x_info->tx_level_code[2][0], tef810x_info->tx_level_code[2][1]);
	PRINTF("- tx_level_table = {%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
			tef810x_info->tx_level_table[0][0], tef810x_info->tx_level_table[0][1], \
			tef810x_info->tx_level_table[1][0], tef810x_info->tx_level_table[1][1], \
			tef810x_info->tx_level_table[2][0], tef810x_info->tx_level_table[2][1], \
			tef810x_info->tx_level_table[3][0], tef810x_info->tx_level_table[3][1], \
			tef810x_info->tx_level_table[4][0], tef810x_info->tx_level_table[4][1], \
			tef810x_info->tx_level_table[5][0], tef810x_info->tx_level_table[5][1], \
			tef810x_info->tx_level_table[6][0], tef810x_info->tx_level_table[6][1]);
	PRINTF("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}\n", \
			tef810x_info->tx_level_table[7][0], tef810x_info->tx_level_table[7][1], \
			tef810x_info->tx_level_table[8][0], tef810x_info->tx_level_table[8][1], \
			tef810x_info->tx_level_table[9][0], tef810x_info->tx_level_table[9][1], \
			tef810x_info->tx_level_table[10][0], tef810x_info->tx_level_table[10][1], \
			tef810x_info->tx_level_table[11][0], tef810x_info->tx_level_table[11][1], \
			tef810x_info->tx_level_table[12][0], tef810x_info->tx_level_table[12][1], \
			tef810x_info->tx_level_table[13][0], tef810x_info->tx_level_table[13][1]);
	PRINTF("- reserved2: {%d,%d}\n", tef810x_info->reserved2[0], tef810x_info->reserved2[1]);
	PRINTF("- lock_freq_time: %d \n", tef810x_info->lock_freq_time);
	PRINTF("- lock_freq_tx: %d \n", tef810x_info->lock_freq_tx);
	PRINTF("- lock_freq: %d \n", tef810x_info->lock_freq);
	PRINTF("- tef_dbg: %d\n", tef810x_info->tef_dbg);
}

/******************************************************************************
Function Name : Get TEF810x information
******************************************************************************/
void get_tef810x_info(char** args, int count)
{
	PRINTF("profile-0\n");
	PRINTF("effc_freq = %f\n", rf_config[0].freq);
	PRINTF("effc_bandwith = %f\n", rf_config[0].bandwidth);
	PRINTF("reset time = %f\n", rf_config[0].tReset);
	PRINTF("chirp period = %f\n", rf_config[0].chirp_period);
	//PRINTF("TX gain= %x\n", rf_config[0].txgain);
	//PRINTF("RX gain= %x\n", rf_config[0].rxgain);
	PRINTF("effc_loopbw = %f\n", rf_config[0].loopBW);
	PRINTF("HPF = %f\n", rf_config[0].hpf);
	PRINTF("LPF = %f\n", rf_config[0].lpf);
	PRINTF("profile-1\n");
	PRINTF("effc_freq = %f\n", rf_config[1].freq);
	PRINTF("effc_bandwith = %f\n", rf_config[1].bandwidth);
	PRINTF("reset time = %f\n", rf_config[1].tReset);
	PRINTF("chirp period = %f\n", rf_config[1].chirp_period);
	//PRINTF("TX gain= %x\n", rf_config[1].txgain);
	//PRINTF("RX gain= %x\n", rf_config[1].rxgain);
	PRINTF("effc_loopbw = %f\n", rf_config[1].loopBW);
	PRINTF("HPF = %f\n", rf_config[1].hpf);
	PRINTF("LPF = %f\n", rf_config[1].lpf);
	PRINTF("profile-2\n");
	PRINTF("effc_freq = %f\n", rf_config[2].freq);
	PRINTF("effc_bandwith = %f\n", rf_config[2].bandwidth);
	PRINTF("reset time = %f\n", rf_config[2].tReset);
	PRINTF("chirp period = %f\n", rf_config[2].chirp_period);
	//PRINTF("TX gain= %x\n", rf_config[2].txgain);
	//PRINTF("RX gain= %x\n", rf_config[2].rxgain);
	PRINTF("effc_loopbw = %f\n", rf_config[2].loopBW);
	PRINTF("HPF = %f\n", rf_config[2].hpf);
	PRINTF("LPF = %f\n", rf_config[2].lpf);
	PRINTF("profile-3\n");
	PRINTF("effc_freq = %f\n", rf_config[3].freq);
	PRINTF("effc_bandwith = %f\n", rf_config[3].bandwidth);
	PRINTF("reset time = %f\n", rf_config[3].tReset);
	PRINTF("chirp period = %f\n", rf_config[3].chirp_period);
	//PRINTF("TX gain= %x\n", rf_config[3].txgain);
	//PRINTF("RX gain= %x\n", rf_config[3].rxgain);
	PRINTF("effc_loopbw = %f\n", rf_config[3].loopBW);
	PRINTF("HPF = %f\n", rf_config[3].hpf);
	PRINTF("LPF = %f\n", rf_config[3].lpf);
	PRINTF("B2 gain= %x\n", TEF810x_b2_gain);
	PRINTF("LOX3 gain= %x\n", TEF810x_lox3_gain);
	PRINTF("dwell time = %f us\n", tDwell);
	PRINTF("settle time = %f us\n", tSettle);
	PRINTF("jumpback time= %f us\n", tJumpback);
	PRINTF("profile t_idle = [%f, %f, %f, %f]\n", t_idle[0], t_idle[1], t_idle[2], t_idle[3]);
	PRINTF("TX power={{%x,%x,%x},", txpon[0][0],  txpon[0][1],  txpon[0][2]);
	PRINTF("{%x,%x,%x},", txpon[1][0],  txpon[1][1],  txpon[1][2]);
	PRINTF("{%x,%x,%x},", txpon[2][0],  txpon[2][1],  txpon[2][2]);
	PRINTF("{%x,%x,%x}}\n", txpon[3][0],  txpon[3][1],  txpon[3][2]);
	PRINTF("TX switch={{%x,%x,%x},", txsw[0][0],  txsw[0][1],  txsw[0][2]);
	PRINTF("{%x,%x,%x},", txsw[1][0],  txsw[1][1],  txsw[1][2]);
	PRINTF("{%x,%x,%x},", txsw[2][0],  txsw[2][1],  txsw[2][2]);
	PRINTF("{%x,%x,%x}}\n", txsw[3][0],  txsw[3][1],  txsw[3][2]);
	PRINTF("AGC profile=%x\n", cur_agc_profile);
	PRINTF("AGC_default_rx_gain = %x\n", AGC_default_rx_gain);
	if(add_time_type == ADD_DWELL_TIME)
	{
		PRINTF("var_tDwell[0] = %f\n", var_tDwell[0]);
		PRINTF("var_tDwell[1] = %f\n", var_tDwell[1]);
		PRINTF("var_tDwell[2] = %f\n", var_tDwell[2]);
		PRINTF("var_tDwell[3] = %f\n", var_tDwell[3]);
	}
	else if(add_time_type == ADD_SETTLE_TIME)
	{
		PRINTF("var_tSettle[0] = %f\n", var_tSettle[0]);
		PRINTF("var_tSettle[1] = %f\n", var_tSettle[1]);
		PRINTF("var_tSettle[2] = %f\n", var_tSettle[2]);
		PRINTF("var_tSettle[3] = %f\n", var_tSettle[3]);
	}
	else
	{
		PRINTF("var_idle[0] = %f\n", var_idle[0]);
		PRINTF("var_idle[1] = %f\n", var_idle[1]);
		PRINTF("var_idle[2] = %f\n", var_idle[2]);
		PRINTF("var_idle[3] = %f\n", var_idle[3]);
	}

	if(dolphin_flag.narrowband)
	    PRINTF("narrowband = TRUE\n");
	else
	    PRINTF("narrowband = FALSE\n");

	PRINTF("ADC recalibration function = %d-",adc_recalibration);
	if(adc_recalibration == 2)
		PRINTF("Background_Cal\n");
	else if(adc_recalibration == 1)
		PRINTF("Manual_Cal\n");
	else
		PRINTF("FALSE\n");

	PRINTF("TX calibration function = %d-", tx_calibration);
	if(tx_calibration == 2)
		PRINTF("Track_High_Level\n");
	else if(tx_calibration == 1)
		PRINTF("Interval_Low & High\n");
	else
		PRINTF("Disable\n");

	PRINTF("vco_start_subband = %d\n", vco_start_subband);
	PRINTF("vco_stop_subband = %d\n", vco_stop_subband);
	PRINTF("vco_cal_frame_time = %d\n", vco_cal_frame_time);
	PRINTF("rx_gain = {{%d,%d,%d,%d},", rx_gain[0][0], rx_gain[0][1], rx_gain[0][2], rx_gain[0][3]);
	PRINTF("{%d,%d,%d,%d},", rx_gain[1][0], rx_gain[1][1], rx_gain[1][2], rx_gain[1][3]);
	PRINTF("{%d,%d,%d,%d},", rx_gain[2][0], rx_gain[2][1], rx_gain[2][2], rx_gain[2][3]);
	PRINTF("{%d,%d,%d,%d}}\n", rx_gain[3][0], rx_gain[3][1], rx_gain[3][2], rx_gain[3][3]);

	PRINTF("tx_gain = {{%d,%d,%d},", tx_gain[0][0], tx_gain[0][1], tx_gain[0][2]);
	PRINTF("{%d,%d,%d},", tx_gain[1][0], tx_gain[1][1], tx_gain[1][2]);
	PRINTF("{%d,%d,%d},", tx_gain[2][0], tx_gain[2][1], tx_gain[2][2]);
	PRINTF("{%d,%d,%d}}\n", tx_gain[3][0], tx_gain[3][1], tx_gain[3][2]);
	PRINTF("tx_level_code = {{%d,%d},", tef810x_info->tx_level_code[0][0], tef810x_info->tx_level_code[0][1]);
	PRINTF("{%d,%d},", tef810x_info->tx_level_code[1][0], tef810x_info->tx_level_code[1][1]);
	PRINTF("{%d,%d}}\n", tef810x_info->tx_level_code[2][0], tef810x_info->tx_level_code[2][1]);
	PRINTF("tef table = \n");
	for (uint8_t loop = 0 ; loop < 14 ;loop++)
	{
		PRINTF("{%03d,%02d}, ", TX_HIGH_LEVEL_TABLE[loop][0], TX_HIGH_LEVEL_TABLE[loop][1]);
		if((loop+1) % 7 == 0)
			PRINTF("\n");
	}
	PRINTF("lock_freq_time = %d\n", lock_freq_time);
	PRINTF("lock_freq_tx = %d\n", lock_freq_tx);
	PRINTF("lock_freq = %d\n", lock_freq);
	PRINTF("tef_dbg = ");
	if(tef_dbg_flag)
		PRINTF("TRUE\n");
	else
		PRINTF("FALSE\n");
}

/******************************************************************************
Function Name : Get TEF810x help
******************************************************************************/
void get_tef810x_help(char** args, int count)
{
    PRINTF("\ntef command list: \n");
    PRINTF("tef init \n");
    PRINTF("tef freq : [ change profile, effc_freq, effc_bandwith, effc_loopbw, reset time, chirp period ] \n");
    PRINTF("tef chirp : [ dwell time, settle time, jumpback time, agc_profile, narrow_band, idle time  ] \n");
    PRINTF("tef txsw : {txsw(0,0), txsw(0,1), txsw(0,2)}, {txsw(1,0), txsw(1,1), txsw(1,2)} \n");
    PRINTF("           {txsw(2,0), txsw(2,1), txsw(2,2)}, {txsw(3,0), txsw(3,1), txsw(3,2)} \n");
    PRINTF("tef txpow : {txpower(0,0), txpower(0,1), txpower(0,2)}, {txpower(1,0), txpower(1,1), txpower(1,2)} \n");
    PRINTF("            {txpower(2,0), txpower(2,1), txpower(2,2)}, {txpower(3,0), txpower(3,1), txpower(3,2)} \n");
    PRINTF("tef info \n");
    PRINTF("tef save \n");
    PRINTF("tef adc : [adc_recalibration_mode 0/1/2] \n");
    PRINTF("tef txcal : [tx_calibration_flag 0/1/2] \n");
    PRINTF("tef caltime : [vco_cal_frame_time]\n");
    PRINTF("tef temp \n");
    PRINTF("tef txgain : [change profile], [Tx0 gain, Tx1 gain, Tx2 gain]\n");
    PRINTF("tef rxgain : [change profile], [Rx0 gain, Rx1 gain, Rx2 gain, Rx3 gain]\n");
    PRINTF("tef filter : [ change profile , HPF, LPF ]\n");
    PRINTF("tef reg : [w/r] [module address, reg address, reg data] \n");
    //PRINTF("tef rmtpinfo \n");
    PRINTF("tef rflv : [Tx_Num, High_Level_Code, Low_Level_Code] \n");
    PRINTF("tef flevel : [Tx_Num(1-3), Tx_Gain(0-255), IsSave(0/1)] find high level\n");
    PRINTF("tef table  : [mode, index, temperature or offset] set or get temperature table\n");
    PRINTF("tef regdump \n");
    PRINTF("tef agcdefgain \n");
//    PRINTF("tef fcwp      : set to use FCW parameters\n");
//    PRINTF("tef bsdp      : set to use BSD parameters\n");
//    PRINTF("tef tbbp      : set to use TBB(School Bus) parameters\n");
//    PRINTF("tef trbsdp    : set to use TB(Taiwan Railway) BSD parameters\n");
//    PRINTF("tef trfcwp    : set to use TB(Taiwan Railway) FCW parameters\n");
//    PRINTF("tef fenixfcwp : set to use fenix FCW parameters\n");
//    PRINTF("tef bsd2beamp : [1/2] beam_m_info=1 beam_s_info=2 \n");
    PRINTF("tef setlong : [set/unset] set long profile\n");
    PRINTF("tef dbg : [0/1] enable_dbg_flag\n");
}

//static void module_register_dump(uint16 module_add, uint16 start_add, uint16 end_add, uint16 *skip_add, uint32_t *reg_data, uint16 *cell_num)
//{
//	int i = 0;
//	uint16_t offset = 0;
//	uint16_t cell_num_temp = 0;
//
//	cell_num_temp = *cell_num;  
//		
//	for (i = (start_add/4); i <= (end_add/4); i++)
//	{	
//		offset = 4*i;
//		if (   (offset != skip_add[0]) && (offset != skip_add[1]) && (offset != skip_add[2]) && (offset != skip_add[3]) && (offset != skip_add[4])
//			&& (offset != skip_add[5]) && (offset != skip_add[6]) && (offset != skip_add[7]) && (offset != skip_add[8]) && (offset != skip_add[9])
//			&& (offset != skip_add[10]) && (offset != skip_add[11]) && (offset != skip_add[12]) && (offset != skip_add[13]) && (offset != skip_add[14]))
//		{
//			chip_reg_Read(module_add, offset, &reg_data[cell_num_temp], NULL);
//       		PRINTF("%d Reg(0x%03x) = 0x%08lx\n", cell_num_temp, offset, reg_data[cell_num_temp]);
//			cell_num_temp ++;
//		}
//	}
//	*cell_num = cell_num_temp;
//}

//void tef810x_register_dump(uint32_t id)
//{
////	RTE_services_P rte_srv = get_RTE_Handler();
//	uint16_t skip_add[15];
//	float start_time = 0, stop_time = 0, freqget = 0;
//	uint32_t reg_data[512];
//    uint16_t cell_num = 0;
////	int i;
//	uint32_t tempRO = 0;
//	
//	start_time = STM_1.CNT.R;
//
//	/*Central Control register dump */
//	skip_add[0]  = 0x30;skip_add[1]  = 0x60;skip_add[2]  = 0x74;skip_add[3]  = 0x84;skip_add[4] = 0x88;
//	skip_add[5]  = 0x8C;skip_add[6]  = 0x90;skip_add[7]  = 0x94;skip_add[8]  = 0x98;skip_add[9] = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(CENTRAL_CTRL_MOUDLE, 0x00, 0x9C, skip_add, reg_data, &cell_num);
//
//    /*LVDS transmitter register dump */  //deadbeef
//	skip_add[0]  = 0x14;skip_add[1]  = 0x1C;skip_add[2]  = 0x20;skip_add[3]  = 0x68;skip_add[4] = 0x74;
//    skip_add[5]  = 0x88;skip_add[6]  = 0x8C;skip_add[7]  = 0x90;skip_add[8]  = 0xFF;skip_add[9] = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(LVDS_TX_MODULE, 0x10, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Camera Serial Interface v2 register dump */
//	skip_add[0]  = 0x10;skip_add[1]  = 0x14;skip_add[2]  = 0x18;skip_add[3]  = 0x1C;skip_add[4]  = 0x30;
//	skip_add[5]  = 0x74;skip_add[6]  = 0x78;skip_add[7]  = 0x7C;skip_add[8]  = 0xA8;skip_add[9]  = 0xB0;
//	skip_add[10] = 0xB4;skip_add[11] = 0xB8;skip_add[12] = 0xCC;skip_add[13] = 0xD0;skip_add[14] = 0xD4;
//    module_register_dump(CSI2_TX_MODULE, 0x00, 0xD8, skip_add, reg_data, &cell_num);
//
//    /*Camera Interface register dump */  //deadbeef
//	skip_add[0]  = 0x44;skip_add[1]  = 0x48;skip_add[2]  = 0x4C;skip_add[3]  = 0x50;skip_add[4]  = 0x54;
//    skip_add[5]  = 0x58;skip_add[6]  = 0x5C;skip_add[7]  = 0x60;skip_add[8]  = 0x74;skip_add[9]  = 0x88;
//	skip_add[10] = 0x8C;skip_add[11] = 0x90;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(CIF_TX_MODULE, 0x00, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Timing Engine register dump */
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(TIMING_ENGINE_MODULE, 0x00, 0x58, skip_add, reg_data, &cell_num);
//
//	/*Sweep Control register dump */
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(SWEEP_CTRL_MODULE, 0x00, 0x60, skip_add, reg_data, &cell_num);
//
//	/*Chirp AFC register dump */
//	skip_add[0]  = 0x64;skip_add[1]  = 0x68;skip_add[2]  = 0x74;skip_add[3]  = 0x78;skip_add[4]  = 0x8C;
//    skip_add[5]  = 0x90;skip_add[6]  = 0x94;skip_add[7]  = 0x9C;skip_add[8]  = 0xA0;skip_add[9]  = 0xA4;
//	skip_add[10] = 0xAC;skip_add[11] = 0xB0;skip_add[12] = 0xB4;skip_add[13] = 0xB8;skip_add[14] = 0xFF;
//    module_register_dump(CHIRP_AFC_MODULE, 0x00, 0xC0, skip_add, reg_data, &cell_num);
//
//	/*Analog to Digital Converter 1 & 2 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x1C;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x28;
//    skip_add[5]  = 0x34;skip_add[6]  = 0x38;skip_add[7]  = 0x3C;skip_add[8]  = 0x40;skip_add[9]  = 0x44;
//	skip_add[10] = 0x48;skip_add[11] = 0x4C;skip_add[12] = 0x50;skip_add[13] = 0x54;skip_add[14] = 0xFF;
//    module_register_dump(ADC_12_MODULE, 0x00, 0x58, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0x7C;skip_add[1]  = 0x80;skip_add[2]  = 0x84;skip_add[3]  = 0x88;skip_add[4]  = 0x94;
//    skip_add[5]  = 0x98;skip_add[6]  = 0x9C;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(ADC_12_MODULE, 0x78, 0xA0, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0x308;skip_add[1] = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(ADC_12_MODULE, 0x304, 0x30C, skip_add, reg_data, &cell_num);
//
//	/*Analog to Digital Converter 3 & 4 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x1C;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x28;
//	skip_add[5]  = 0x34;skip_add[6]  = 0x38;skip_add[7]  = 0x3C;skip_add[8]  = 0x40;skip_add[9]  = 0x44;
//	skip_add[10] = 0x48;skip_add[11] = 0x4C;skip_add[12] = 0x50;skip_add[13] = 0x54;skip_add[14] = 0xFF;
//	module_register_dump(ADC_34_MODULE, 0x00, 0x58, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0x7C;skip_add[1]  = 0x80;skip_add[2]  = 0x84;skip_add[3]  = 0x88;skip_add[4]  = 0x94;
//	skip_add[5]  = 0x98;skip_add[6]  = 0x9C;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(ADC_34_MODULE, 0x78, 0xA0, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0x308;skip_add[1] = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(ADC_34_MODULE, 0x304, 0x30C, skip_add, reg_data, &cell_num);
//
//	/*Global Bias register dump */
//	skip_add[0]  = 0x4C;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(GLOBAL_BIAS_MODULE, 0x00, 0x64, skip_add, reg_data, &cell_num);
//
//	/*Local Oscillator Interface register dump */
//	skip_add[0]  = 0x04;skip_add[1]  = 0x08;skip_add[2]  = 0x0C;skip_add[3]  = 0x10;skip_add[4]  = 0x14;
//    skip_add[5]  = 0x1C;skip_add[6]  = 0x20;skip_add[7]  = 0x24;skip_add[8]  = 0x28;skip_add[9]  = 0x2C;
//	skip_add[10] = 0x30;skip_add[11] = 0x34;skip_add[12] = 0x38;skip_add[13] = 0x3C;skip_add[14] = 0xFF;
//    module_register_dump(LO_INTERFACE_MODULE, 0x00, 0x40, skip_add, reg_data, &cell_num);
//
//	/*Master Clock register dump */
//	skip_add[0]  = 0x24;skip_add[1]  = 0x28;skip_add[2]  = 0x44;skip_add[3]  = 0x48;skip_add[4]  = 0x4C;
//    skip_add[5]  = 0x50;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(MASTER_CLOCK_MODULE, 0x00, 0x6C, skip_add, reg_data, &cell_num);
//
//	/*Receiver 1 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x10;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x34;
//    skip_add[5]  = 0x38;skip_add[6]  = 0x48;skip_add[7]  = 0x4C;skip_add[8]  = 0x5C;skip_add[9]  = 0x60;
//	skip_add[10] = 0x64;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(RX1_MODULE, 0x00, 0x6C, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0x24;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0x5C;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(RX1_MODULE, 0x94, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Receiver 2 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x10;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x34;
//	skip_add[5]  = 0x38;skip_add[6]  = 0x48;skip_add[7]  = 0x4C;skip_add[8]  = 0x5C;skip_add[9]  = 0x60;
//	skip_add[10] = 0x64;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX2_MODULE, 0x00, 0x6C, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0x24;skip_add[4]  = 0xFF;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0x5C;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX2_MODULE, 0x94, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Receiver 3 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x10;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x34;
//	skip_add[5]  = 0x38;skip_add[6]  = 0x48;skip_add[7]  = 0x4C;skip_add[8]  = 0x5C;skip_add[9]  = 0x60;
//	skip_add[10] = 0x64;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX3_MODULE, 0x00, 0x6C, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0x24;skip_add[4]  = 0xFF;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0x5C;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX3_MODULE, 0x94, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Receiver 4 register dump */
//	skip_add[0]  = 0x0C;skip_add[1]  = 0x10;skip_add[2]  = 0x20;skip_add[3]  = 0x24;skip_add[4]  = 0x34;
//	skip_add[5]  = 0x38;skip_add[6]  = 0x48;skip_add[7]  = 0x4C;skip_add[8]  = 0x5C;skip_add[9]  = 0x60;
//	skip_add[10] = 0x64;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX4_MODULE, 0x00, 0x6C, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0x24;skip_add[4]  = 0xFF;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0x5C;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(RX4_MODULE, 0x94, 0x94, skip_add, reg_data, &cell_num);
//
//	/*Transmitter 1 register dump */
//	skip_add[0]  = 0x20;skip_add[1]  = 0x34;skip_add[2]  = 0x38;skip_add[3]  = 0x60;skip_add[4]  = 0x64;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(TX1_MODULE, 0x00, 0x68, skip_add, reg_data, &cell_num);
//
//	/*Transmitter 2 register dump */  //deadbeef
//	skip_add[0]  = 0x20;skip_add[1]  = 0x34;skip_add[2]  = 0x38;skip_add[3]  = 0x60;skip_add[4]  = 0x64;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(TX2_MODULE, 0x00, 0x68, skip_add, reg_data, &cell_num);
//
//	/*Transmitter 3 register dump */
//	skip_add[0]  = 0x20;skip_add[1]  = 0x34;skip_add[2]  = 0x38;skip_add[3]  = 0x60;skip_add[4]  = 0x64;
//	skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//	module_register_dump(TX3_MODULE, 0x00, 0x68, skip_add, reg_data, &cell_num);
//
//	/*Single Sideband Modulator register dump */
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(SSBMOD_MODULE, 0x00, 0x08, skip_add, reg_data, &cell_num);
//
//	/*Global LDO register dump */
//	skip_add[0]  = 0x14;skip_add[1]  = 0x30;skip_add[2]  = 0x34;skip_add[3]  = 0x38;skip_add[4]  = 0x3C;
//    skip_add[5]  = 0x40;skip_add[6]  = 0x48;skip_add[7]  = 0x4C;skip_add[8]  = 0x54;skip_add[9]  = 0x58;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(GLOBAL_LDO_MODULE, 0x04, 0x68, skip_add, reg_data, &cell_num);
//
//	/*Analog Test Bus register dump */
//	skip_add[0]  = 0x04;skip_add[1]  = 0x14;skip_add[2]  = 0x18;skip_add[3]  = 0x1C;skip_add[4]  = 0x20;
//    skip_add[5]  = 0x24;skip_add[6]  = 0x28;skip_add[7]  = 0x2C;skip_add[8]  = 0x34;skip_add[9]  = 0x38;
//	skip_add[10] = 0x3C;skip_add[11] = 0x40;skip_add[12] = 0x44;skip_add[13] = 0x48;skip_add[14] = 0x4C;
//    module_register_dump(ATB_MODULE, 0x00, 0x54, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(ATB_MODULE, 0x60, 0x60, skip_add, reg_data, &cell_num);	
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(ATB_MODULE, 0x100, 0x104, skip_add, reg_data, &cell_num);	
//
//	/*One Time Programmable register dump */
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(OPT_MOUDULE, 0x40, 0x40, skip_add, reg_data, &cell_num);
//	skip_add[0]  = 0xFF;skip_add[1]  = 0xFF;skip_add[2]  = 0xFF;skip_add[3]  = 0xFF;skip_add[4]  = 0xFF;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(OPT_MOUDULE, 0x200, 0x200, skip_add, reg_data, &cell_num);	
//
//	/*Inner Safety Monitor register dump */
//	skip_add[0]  = 0x20;skip_add[1]  = 0x9C;skip_add[2]  = 0xA0;skip_add[3]  = 0xB0;skip_add[4]  = 0xB4;
//    skip_add[5]  = 0xFF;skip_add[6]  = 0xFF;skip_add[7]  = 0xFF;skip_add[8]  = 0xFF;skip_add[9]  = 0xFF;
//	skip_add[10] = 0xFF;skip_add[11] = 0xFF;skip_add[12] = 0xFF;skip_add[13] = 0xFF;skip_add[14] = 0xFF;
//    module_register_dump(ISM_MODULE, 0x00, 0xD8, skip_add, reg_data, &cell_num);
//
//	reg_data[cell_num] = ((uint32_t)SPT.ACQ_STATUS_A1.B.CH_A_MAX << 16) + (int16_t)SPT.ACQ_STATUS_A1.B.CH_A_MIN;
//	cell_num++;
//	reg_data[cell_num] = ((uint32_t)SPT.ACQ_STATUS_B1.B.CH_B_MAX << 16) + (int16_t)SPT.ACQ_STATUS_B1.B.CH_B_MIN;
//	cell_num++;
//	reg_data[cell_num] = ((uint32_t)SPT.ACQ_STATUS_C1.B.CH_C_MAX << 16) + (int16_t)SPT.ACQ_STATUS_C1.B.CH_C_MIN;
//	cell_num++;
//	reg_data[cell_num] = ((uint32_t)SPT.ACQ_STATUS_D1.B.CH_D_MAX << 16) + (int16_t)SPT.ACQ_STATUS_D1.B.CH_D_MIN;
//	cell_num++;
//	reg_data[cell_num] = (uint32_t)chip_ATB_ReadTemp(0x1, TX1_MODULE);
//
//	PRINTF("ACQ: A[%d,%d],B[%d,%d],C[%d,%d],D[%d,%d]\n",
//			(int16_t)SPT.ACQ_STATUS_A1.B.CH_A_MAX, (int16_t)SPT.ACQ_STATUS_A1.B.CH_A_MIN,
//			(int16_t)SPT.ACQ_STATUS_B1.B.CH_B_MAX, (int16_t)SPT.ACQ_STATUS_B1.B.CH_B_MIN,
//			(int16_t)SPT.ACQ_STATUS_C1.B.CH_C_MAX, (int16_t)SPT.ACQ_STATUS_C1.B.CH_C_MIN,
//			(int16_t)SPT.ACQ_STATUS_D1.B.CH_D_MAX, (int16_t)SPT.ACQ_STATUS_D1.B.CH_D_MIN);
//
//	
//	tempRO = (uint32_t)chip_ATB_ReadTemp(0x1, TX1_MODULE);
//	PRINTF("TEF TX1 Temp = %d\n", tempRO);
//
//
//	rte_srv->COMM_PROTOCOL_Service.ISOTP_Service->send(id, (uint8_t *)&reg_data, sizeof(reg_data));
//	rte_srv->COMM_PROTOCOL_Service.ISOTP_Service->send(0x321, (uint8_t *)&reg_data, 8);
//
//
//
//	stop_time = STM_1.CNT.R;		
//	freqget = (stop_time - start_time) / 60000;
//	PRINTF("register dump time =%f ms , cell num = %d \n",freqget, cell_num);
////	for (i = 0; i < 600; i ++)
////	{
////		PRINTF("Reg %d = 0x%08lx\n", i, reg_data[i]);
////	}
//}
/******************************************************************************
Function Name : Do AGC/monitor tef810x
******************************************************************************/
static void monitor_tef810x(void)
{
	rmtp_rf_ic_status_t rf_status;
	int      rmtp_return;

	Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t master_error_status;
	Nxp_Tef810x_Mod18_SupplyErrorFlagMaskedStatusUnion_t supply_error_status;
	Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t tx_error_status;
	Nxp_Tef810x_Mod18_RxErrorFlagMaskedStatusUnion_t rx_error_status;
	Nxp_Tef810x_Mod18_ChirpErrorFlagMaskedStatusUnion_t chirp_error_status;
	Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t mc_lo_error_status;
	Nxp_Tef810x_Mod18_AdcErrorFlagMaskedStatusUnion_t adc_erro_status;
	Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t rf_power_down_error_status;
	Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t ISM_error_status_and_mcu_reset_status;

	int      tsen0;
	//int    abs_tsen0, abs_tsen1, tsen1;
	int		 ret;
	//uint8_t  calibrate_VCO_flag, calibrate_ADC_flag;
	short_frame_counter++;

	ret = chip_reg_Read(ISM_MODULE, master_error_flag_masked_status, &master_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, supply_error_flag_masked_status, &supply_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, tx_error_flag_masked_status, &tx_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, rx_error_flag_masked_status, &rx_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, chirp_error_flag_masked_status, &chirp_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, mc_lo_error_flag_masked_status, &mc_lo_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, adc_error_flag_masked_status, &adc_erro_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, rf_power_down_error_flag_masked_status, &rf_power_down_error_status.val_u32, NULL);
	ret = chip_reg_Read(ISM_MODULE, ISM_error_status_and_mcu_reset, &ISM_error_status_and_mcu_reset_status.val_u32, NULL);
	if (ret != 0) PRINTF("chip_reg_Read failed!\n");

	Rf_Temp = chip_ATB_ReadTemp(0x1, TX1_MODULE);
	tsen0 = (int)Rf_Temp;
	#ifdef TEF810X_INSERT_TEST
	Rf_Temp = Rf_Temp_V;
	#endif

	//if (dolphin_flag.tx_calibration == true)
	//{
		if (dolphin_flag.mclk_recal_flag == false)
		{
			if(master_error_status.val_u32)
				PRINTF("/*ISM master    (064) error(0x%lx)!(%d)\n", master_error_status.val_u32, tsen0);
			if(supply_error_status.val_u32)
				PRINTF("/*ISM supply    (068) error(0x%lx)!(%d)\n", supply_error_status.val_u32, tsen0);
			if(tx_error_status.val_u32 & 0x7FFF81FF)
				PRINTF("/*ISM tx        (06C) error(0x%lx)!(%d)\n", tx_error_status.val_u32, tsen0);
			if(rx_error_status.val_u32)
				PRINTF("/*ISM rx        (070) error(0x%lx)!(%d)\n", rx_error_status.val_u32, tsen0);
			if(chirp_error_status.val_u32)
				PRINTF("/*ISM chirp     (074) error(0x%lx)!(%d)\n", chirp_error_status.val_u32, tsen0);
			if(mc_lo_error_status.val_u32)
				PRINTF("/*ISM mc_lo     (078) error(0x%lx)!(%d)\n", mc_lo_error_status.val_u32, tsen0);
			if(adc_erro_status.val_u32)
				PRINTF("/*ISM adc       (07C) error(0x%lx)!(%d)\n", adc_erro_status.val_u32, tsen0);
			if(rf_power_down_error_status.val_u32)
				PRINTF("/*ISM rf_power  (080) error(0x%lx)!(%d)\n", rf_power_down_error_status.val_u32, tsen0);
			if(ISM_error_status_and_mcu_reset_status.val_u32)
				PRINTF("/*ISM rf_power  (0AC) error(0x%lx)!(%d)\n", ISM_error_status_and_mcu_reset_status.val_u32, tsen0);
		}
		else
		{
			PRINTF("monitor_tefinfo r=%.2f d=%.2f s=%.2f j=%.2f i=%.2f c=%.2f start=%d stop=%d vco=%d h=%d, %d, %d l=%d, %d, %d\n",
				rf_config[0].tReset,tDwell, tSettle,tJumpback,t_idle[0], rf_config[0].chirp_period,
				vco_start_subband, vco_stop_subband, vco_cal_frame_time,
				tx_cal_level_code[0][0], tx_cal_level_code[1][0], tx_cal_level_code[2][0],
				tx_cal_level_code[0][1], tx_cal_level_code[1][1], tx_cal_level_code[2][1]);

			PRINTF("/*ISM skip \n");
		}
	// }
	
    /*calibrate_VCO_flag = 0;
    calibrate_ADC_flag = 0;

    calibrate_ADC_cnt++;
    if(calibrate_ADC_cnt > 50)
    {
	    calibrate_ADC_flag = 1;
    }*/


	//tsen1 = get_tsens1();

    if (master_error_status.val_u32 & 0x31F)
    {
        if(dolphin_flag.mclk_recal_flag == false)
        {
        	PRINTF("MCLK error(0x%lx)! Temperature =%d\n", master_error_status.val_u32, tsen0);
//        	rte_srv->CONSOLE_Service->console_flush();
        	console_flush();

			if (mclk_error_cnt < MCLK_MAX_ERROR_TIMES)
				mclk_error_cnt++;

        	if(mclk_error_cnt >= MCLK_MAX_ERROR_TIMES)
        	{
//        		mclk_error_cnt = MCLK_MAX_ERROR_TIMES;
        		/*if(vco_cal_frame_time == VCO_CAL_OFF)
        		{
        			ret=chip_MCLK_Recalibrate();
        			if (ret != 0)
        				PRINTF("MCLK Recalibration failed!\n");
        			else
        				PRINTF("MCLK Recalibration!\n");
        		}*/

        		//calibrate_VCO_flag =1;
        		rf_status.data_type = RF_VCO_STATUS;
        		rf_status.message_ID = VCO_CALIB_MCLK_ERR;
        		rmtp_return = rmtp_send_rf_ic_status_message((uint8_t *)&rf_status, sizeof(rf_status));

      			update_tef810x_status(MONITOR_ID_MCLK, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
       			update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);

				if(rmtp_return == RES_PARAMETER_ERROR)
					PRINTF("Send rmtp message error\n");
			}
        }
    }
    else
    {
		dolphin_flag.mclk_recal_flag = false;
    	mclk_error_cnt = 0;

    	update_tef810x_status(MONITOR_ID_MCLK, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
    	update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
    }

    if(chirp_error_status.val_u32 & 0x3FFF)
    {
    	PRINTF("VCO error(0x%lx)! Temperature =%d\n", chirp_error_status.val_u32, tsen0);
		console_flush();

		if (vco_error_cnt < VCO_MAX_ERROR_TIMES)
			vco_error_cnt ++;

		if(vco_error_cnt >= VCO_MAX_ERROR_TIMES)
		{
//			vco_error_cnt = VCO_MAX_ERROR_TIMES;
			//calibrate_VCO_flag =1;
			rf_status.data_type = RF_VCO_STATUS;
			rf_status.message_ID = VCO_CALIB_CHIRP_ERR;
			rmtp_return =  rmtp_send_rf_ic_status_message((uint8_t *)&rf_status, sizeof(rf_status));

			update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);

			if(rmtp_return == RES_PARAMETER_ERROR)
				PRINTF("Send rmtp message error\n");
		}
    }
    else
    {
    	vco_error_cnt = 0;
    	update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
    }
}

static void tef_tx_check(void)
{
	if(tx_calibration == 2 && production_line_mode == kNORMAL_MODE)
	{
		hal_es3_tx_fPCtrl_CorrectTxGain_Cubtek(1, txsw, tx_gain);
		hal_es3_tx_fPCtrl_CorrectTxGain_Cubtek(2, txsw, tx_gain);
		hal_es3_tx_fPCtrl_CorrectTxGain_Cubtek(3, txsw, tx_gain);
	}
}

static void tef810x_debug_log(void)
{
#ifdef TEF810X_LOG
	Nxp_Tef810x_Mod0A_LoInterfaceGainControlUnion_t r_LoInterfaceGainControlUnion_ust;
	Nxp_Tef810x_Mod11_GTxGainProfileUnion_t r_TxGainProfile_ust;
	Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t r_ChirpVCOProfile_ust;

	Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t r_LevelRf_ustf;
//	Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoUnion_t r_VtuneVco_ust;
//	Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoBits_t r_LevelVco_ust;
//	Nxp_Tef810x_Mod0D_FuncsafeMonLevelLoUnion_t r_LevelLo_ust;

	PRINTF("---RF,%lld,%.4f,%d",frame_counter,Rf_Temp,tx_level_status);

	glue_reg_Read(LO_INTERFACE_MODULE_ADDRESS, NXP_TEF810X_MOD0A_LO_INTERFACE_GAIN_CONTROL_U16, &r_LoInterfaceGainControlUnion_ust.val_u32, NULL);
	PRINTF(",%02d",r_LoInterfaceGainControlUnion_ust.bits_st.GainCodeSel);

	glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &r_LevelRf_ustf.val_u32, NULL);
	glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE1_U16, &r_TxGainProfile_ust.val_u32, NULL);
	PRINTF(",%02d,%02d,%03d",r_LevelRf_ustf.bits_st.LevelRfHighSpi,r_LevelRf_ustf.bits_st.LevelRfLowSpi,r_TxGainProfile_ust.bits_st.GTxGainProfile0);

	glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &r_LevelRf_ustf.val_u32, NULL);
	glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE0_U16, &r_TxGainProfile_ust.val_u32, NULL);
	PRINTF(",%02d,%02d,%03d",r_LevelRf_ustf.bits_st.LevelRfHighSpi,r_LevelRf_ustf.bits_st.LevelRfLowSpi,r_TxGainProfile_ust.bits_st.GTxGainProfile0);

	glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &r_LevelRf_ustf.val_u32, NULL);
	glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_G_TX_GAIN_PROFILE2_U16, &r_TxGainProfile_ust.val_u32, NULL);
	PRINTF(",%02d,%02d,%03d",r_LevelRf_ustf.bits_st.LevelRfHighSpi,r_LevelRf_ustf.bits_st.LevelRfLowSpi,r_TxGainProfile_ust.bits_st.GTxGainProfile0);

	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &r_ChirpVCOProfile_ust.val_u32, NULL);
	PRINTF(",%03d,%02d",r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0,r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16, &r_ChirpVCOProfile_ust.val_u32, NULL);
	PRINTF(",%03d,%02d,---\n",r_ChirpVCOProfile_ust.bits_st.CtlVcoCoarseTuningSpiProfile0,r_ChirpVCOProfile_ust.bits_st.CtlVcoIvcoFineSpiProfile0);
#endif
}

/******************************************************************************
 * Function : Check vco every interleaved RF is done
 ******************************************************************************/
void tef_vco_check(void)
{
//	int32_t ret;
	uint32_t  i;

	vco_cal_frame_counter++;

	#ifdef TEF810X_LOG
	frame_counter++;
	if(tef_dbg_flag)
		tef810x_debug_log();
	#endif
	tef_tx_check();

	if(vco_cal_frame_time != VCO_CAL_OFF)
	{
		switch(calibrate_vco_state)
		{
			case TEF_VCO_CAL_RF_BEGIN:
				tef_cal_freq_start(cur_vco_subband, calibrate_vco_state, dolphin_flag.narrowband);
				timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_vco_cal_freq_get, NULL);
				break;

			case TEF_VCO_CAL_RF_END:
				tef_cal_freq_start(cur_vco_subband, calibrate_vco_state, dolphin_flag.narrowband);
				timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_vco_cal_freq_get, NULL);
				break;

			case TEF_VCO_CALIBRATION:
				update_vco_profile_suband();
				calibrate_vco_state = TEF_VCO_CAL_IDLE;
				vco_cal_frame_counter = 0;
				break;

			default:

				if(vco_cal_frame_counter >= vco_cal_frame_time)
				{
					calibrate_vco_state = TEF_VCO_CAL_RF_BEGIN;
					PRINTF("Do VCO calibration !!!!\n");
				}
				else
				{
					calibrate_vco_state = TEF_VCO_CAL_IDLE;
				}
				break;
		}
	}

	if(calibrate_vco_state == TEF_VCO_CAL_IDLE)
	{
		i = vco_cal_frame_counter % DEFAULT_CAL_FUNC_NUM;

		if(i==0)
		{
			tef_mclk_recal();
		}
		else if (i==10)
		{
			if(tx_calibration)
			{
				set_tef810x_tx_gain_code();
			}
		}
		else if (i==11)
		{
			if(tx_calibration == 1)
			{
				cubtek_profile_tx_gain_calibration(0);
				cubtek_profile_tx_gain_calibration(1);
				cubtek_profile_tx_gain_calibration(2);
			}
		}
		else if (i==25)
		{
			hal_es3_ISM_StatusCheckAndRecover();
		}
		else
			;

	}
}

static void tef_mclk_recal(void)
{
	Nxp_Tef810x_Mod0C_StartCalibrationCounterUnion_t mclkStartCalibCounter;

	//trigger a calibration

	glue_reg_Read(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, &mclkStartCalibCounter.val_u32, NULL);
	//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	mclkStartCalibCounter.bits_st.StartCalibrationCounter = 1;

	glue_reg_Write(MASTER_CLOCK_MODULE_ADDRESS, NXP_TEF810X_MOD0C_START_CALIBRATION_COUNTER_U16, mclkStartCalibCounter.val_u32, NULL);
    //HAL_GEC_ASSERT(DOLPHINIC_NOERROR);

	//poll recalib flag to confirm successful calibration
	glue_Sleep(0.5);
	//glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);
    //CHAL_GEC_ASSERT(DOLPHINIC_NOERROR);

    //hal_es3_ISM_SetMCUReset();
	//glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);
	//HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
	//if(McLoErrorFlagMaskedStatus.bits_st.McPllLockErrorFlag == 1 || McLoErrorFlagMaskedStatus.bits_st.McPllLevelErrorFlag == 1)
		// PRINTF("MCLK FAILED!!!!\n");
	dolphin_flag.mclk_recal_flag = true;
}

/*static void tef_mclk_report(void)
{
	Nxp_Tef810x_Mod18_McLoErrorFlagMaskedStatusUnion_t McLoErrorFlagMaskedStatus;

	glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);

	hal_es3_ISM_SetMCUReset();
	glue_reg_Read(ISM_MODULE_ADDRESS, NXP_TEF810X_MOD18_MC_LO_ERROR_FLAG_MASKED_STATUS_U16, &McLoErrorFlagMaskedStatus.val_u32, NULL);
	if(McLoErrorFlagMaskedStatus.bits_st.McPllLockErrorFlag == 1 || McLoErrorFlagMaskedStatus.bits_st.McPllLevelErrorFlag == 1)
		PRINTF("MCLK Recalibration failed!\n");

	calibrate_vco_state = TEF_VCO_CAL_RF_BEGIN;
}*/

#define  NUMContextReg   7
#define  COUNTPERIOD     10
const uint16_t contextRegAddr[NUMContextReg] = {
	NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16,
	NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16,
	NXP_TEF810X_MOD06_CP_REGISTER_U16,
	NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16,
	NXP_TEF810X_MOD06_REF_CNTR_INIT_U16,
	NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16,
	NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16 };

static uint32_t vco_reg_val[NUMContextReg];
extern uint32_t * g_OTPShadowLUT_ES3;

static void tef_cal_freq_start(uint8_t subband, uint8_t vco_state, bool narrow_Band)
{
	Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t		CAFCFSMonLvlVco;
	Nxp_Tef810x_Mod04_ChirpGlobalControlUnion_t			TEChirpGlblCtrl;
	Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t			VCORegisterProfile3;
	Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t		filterRegisterProfile3;

	uint32_t ref_counter_val = 0;
	uint8_t  temp_CtlVcoIvcoFineSpiProfile0;
	static int OTP_220_f76sub;

	Nxp_Tef810x_Mod06_CpRegisterUnion_t				CPReg;
	Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t		VCORegProfile;
	Nxp_Tef810x_Mod06_RefCntrInitUnion_t			VCORefCntr;
	Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t	DivideForce;
	Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t	CAFCFilter;
	Nxp_Tef810x_Mod06_FreqCounterStartUnion_t		CAFCFreqCountStrt;

	push_vco_register_for_vco_cal();

	//The below 4 local modification of registers will be restored by the above saved values in the end of this function.


	//disabled VCO mon level to avoid failure during calibration
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, &CAFCFSMonLvlVco.val_u32, NULL);

	CAFCFSMonLvlVco.bits_st.CtlLevelVcoAmpMonitorEnSpi = 0;
	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16, CAFCFSMonLvlVco.val_u32, NULL);


	//disconnect loop filter, disable CpSlice, force a constant vtune
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16, &filterRegisterProfile3.val_u32, NULL);

	//force to approx. 155mV
	filterRegisterProfile3.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x12;
	filterRegisterProfile3.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
	filterRegisterProfile3.bits_st.CtlIbiasCp150USpiProfile0 = 0;
	filterRegisterProfile3.bits_st.CtlCpSliceEnSpiProfile0 = 0;
	filterRegisterProfile3.bits_st.CtlLpfIntEnSpiProfile0 = 0;
	filterRegisterProfile3.bits_st.CtlLpfExtEnSpiProfile0 = 0;
	filterRegisterProfile3.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
	//disconnect loop filter, set force vtune to value 12(~180mV) or 69(~900mV)
	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16, filterRegisterProfile3.val_u32, NULL);


	// configure temporarily OTP value of subband number for 76GHz at 125C
	//parse the OTP value for 76GHz subband at 125C
	OTP_220_f76sub = (g_OTPShadowLUT_ES3[8] >> 9) & 0x7F;
	OTP_220_f76sub = hal_es3_bit_flip(OTP_220_f76sub, 7);
	//DbgInfo("OTP stored subband for 76GHz at 125C is:%d\n", OTP_220_f76sub);

	//select narrow/wide band, and OTP subband number, enable VCO.
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16, &VCORegisterProfile3.val_u32, NULL);
	temp_CtlVcoIvcoFineSpiProfile0 = VCORegisterProfile3.bits_st.CtlVcoIvcoFineSpiProfile0;

	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, &VCORegisterProfile3.val_u32, NULL);

	VCORegisterProfile3.bits_st.CtlVcoEnSpiProfile0 = 1;
	//VCORegisterProfile3.bits_st.CtlVcoIvcoFineSpiProfile0 = 0x0; //temporarily set to 0, just soon after it will be calibrated.
	VCORegisterProfile3.bits_st.CtlVcoIvcoFineSpiProfile0 = temp_CtlVcoIvcoFineSpiProfile0;
	VCORegisterProfile3.bits_st.CtlVcoCoarseTuningSpiProfile0 = (OTP_220_f76sub - 20 >= 0) ? (OTP_220_f76sub - 20) : 0;
	VCORegisterProfile3.bits_st.CtlVcoBandwidthSpiProfile0 = narrow_Band ? 0 : 1;

	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, VCORegisterProfile3.val_u32, NULL);


	//Force timing engine to use Profile-3 for VCO cal
	glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, &TEChirpGlblCtrl.val_u32, NULL);

	TEChirpGlblCtrl.bits_st.ChirpEnable = 1;
	TEChirpGlblCtrl.bits_st.ChirpProfileSelect = 3;
	TEChirpGlblCtrl.bits_st.ChirpStart = 0;
	TEChirpGlblCtrl.bits_st.EnableProfileReset = 0;
	TEChirpGlblCtrl.bits_st.ProfileStayCountVal = 0;

	glue_reg_Write(TIMING_ENGINE_MODULE_ADDRESS, NXP_TEF810X_MOD04_CHIRP_GLOBAL_CONTROL_U16, TEChirpGlblCtrl.val_u32, NULL);

	// calibrate CAFC amplitude in open loop condition (prepared in code above)
	//hal_es3_cafc_CalAmplitude(3);
	//glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, &VCORegisterProfile3.val_u32, NULL);

	//iVCOFineOTP76G = VCORegisterProfile3.bits_st.CtlVcoIvcoFineSpiProfile0;
	//DbgInfo("Calibrate iVCO is: 0x%x at subband:%d\n", iVCOFineOTP76G, VCORegisterProfile0.bits_st.CtlVcoCoarseTuningSpiProfile0);

	//Force a divider to 27.
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivideForce.val_u32, NULL);

	DivideForce.bits_st.CtlForceDivider = 1;
	DivideForce.bits_st.CtlDivForce = 0x1B;

	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivideForce.val_u32, NULL);

	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16, &CAFCFilter.val_u32, NULL);

	//other settings are erased, not important in VCO frequency measurement
	//if (lowerBound)
	if(vco_state == TEF_VCO_CAL_RF_BEGIN)
		//approx. 155mV
		CAFCFilter.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x12;
	else
		//approx. 945mV
		CAFCFilter.bits_st.CtlLpfProgForceVoltageSpiProfile0 = 0x6E;

	CAFCFilter.bits_st.CtlLpfForceVtuneEnSpiProfile0 = 1;
	CAFCFilter.bits_st.CtlIbiasCp150USpiProfile0 = 0;
	CAFCFilter.bits_st.CtlCpSliceEnSpiProfile0 = 0;
	CAFCFilter.bits_st.CtlLpfIntEnSpiProfile0 = 0;
	CAFCFilter.bits_st.CtlLpfExtEnSpiProfile0 = 0;
	CAFCFilter.bits_st.CtlCpIoffsetUpdnSpiProfile0 = 0;
	//disconnect loop filter, set force vtune to value 12(~180mV) or 69(~900mV)
	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16, CAFCFilter.val_u32, NULL);


	//turn off the CP
	// this SPI setting is redundant, can be removed for timing optimization, since CtlCpSliceEnSpiProfile0 is set to 0 already.
	// here it is kept just for reference.
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, &CPReg.val_u32, NULL);

	CPReg.bits_st.CtlCpEnSpi = 0;
	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_CP_REGISTER_U16, CPReg.val_u32, NULL);


	//select narrow/wide band, and user input subband number.
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, &VCORegProfile.val_u32, NULL);

	VCORegProfile.bits_st.CtlVcoEnSpiProfile0 = 1;
	//VCORegProfile.bits_st.CtlVcoIvcoFineSpiProfile0 = iVCOFine;
	VCORegProfile.bits_st.CtlVcoIvcoFineSpiProfile0 = VCORegisterProfile3.bits_st.CtlVcoIvcoFineSpiProfile0;
	VCORegProfile.bits_st.CtlVcoCoarseTuningSpiProfile0 = subband;
	VCORegProfile.bits_st.CtlVcoBandwidthSpiProfile0 = narrow_Band ? 0 : 1;

	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16, VCORegProfile.val_u32, NULL);

	//program the reference counter value to input param
	ref_counter_val = COUNTPERIOD * 40; //us to clk cycles.


	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, &VCORefCntr.val_u32, NULL);

	VCORefCntr.bits_st.RefCountValue = ref_counter_val;

	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_REF_CNTR_INIT_U16, VCORefCntr.val_u32, NULL);


	//change frequency counter trigger to SPI write to freq_start filed.
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, &CAFCFreqCountStrt.val_u32, NULL);

	CAFCFreqCountStrt.bits_st.EnableFuncSafetyFreqMea = 0;
	CAFCFreqCountStrt.bits_st.NumLsbbitsIgnored = 0;
	CAFCFreqCountStrt.bits_st.FreqStart = 0;

	glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, CAFCFreqCountStrt.val_u32, NULL);

	//trigger one counter measurement
	CAFCFreqCountStrt.bits_st.FreqStart = 1;

	glue_reg_Write(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16, CAFCFreqCountStrt.val_u32, NULL);

	tef_Caliration_status |= VCO_CALIBRATION_MASK_FLAG;
}

void tef_vco_cal_freq_get(void)
{
	Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t	FreqReadValue;

	FreqReadValue.val_u32 = 0;
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);

	if(tef_Caliration_status & VCO_CALIBRATION_MASK_FLAG)
	{
		if(FreqReadValue.bits_st.DoneFlag)
		//if(reg_val & 0x00100000)
		{
			FreqReadValue.val_u32 = 0;
			//read out the frequency counter.
			glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, &FreqReadValue.val_u32, NULL);

			if(calibrate_vco_state == TEF_VCO_CAL_RF_BEGIN)
			{
				cur_vco_start_freq = (double) FreqReadValue.bits_st.FreqCountValue / COUNTPERIOD * 27 * 2 * 3 * 1e6;
				//cur_vco_start_freq = (double)(reg_val & 0x3FFFF) / 100 * 27 * 2 * 3 * 1e6;
				//PRINTF("cur_vco_start_freq = %lf\n", cur_vco_start_freq);
				calibrate_vco_state = TEF_VCO_CAL_RF_END;
			}
			else
			{
				cur_vco_end_freq = (double)FreqReadValue.bits_st.FreqCountValue / COUNTPERIOD * 27 * 2 * 3 * 1e6;
				//cur_vco_end_freq = (double)(reg_val & 0x3FFFF) / 100 * 27 * 2 * 3 * 1e6;
				cur_vco_bw_freq = cur_vco_end_freq - cur_vco_start_freq;
				//PRINTF("cur_vco_end_freq = %lf, cur_vco_bw_freq = %lf\n", cur_vco_end_freq, cur_vco_bw_freq);
				hal_es3_cafc_SetVCOTable(dolphin_flag.narrowband, cur_vco_subband, cur_vco_start_freq, cur_vco_end_freq, cur_vco_bw_freq);
				cur_vco_subband++;
				if(cur_vco_subband > vco_stop_subband)
				{
					cur_vco_subband = vco_start_subband;
					calibrate_vco_state = TEF_VCO_CALIBRATION;
				}
				else
				{
					calibrate_vco_state = TEF_VCO_CAL_RF_BEGIN;
				}
			}
			tef_cal_freq_end();
			tef_Caliration_status &= ~VCO_CALIBRATION_MASK_FLAG;
		}
		else
		{
		    timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_vco_cal_freq_get, NULL);
			#ifdef TEF810X_DBG
			PRINTF("VCO Cal not yet! Wait next tick!");
			#endif
		}
	}
}

static void tef_cal_freq_end(void)
{
	Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t		DivForce;

	glue_reg_Write(CHIRP_AFC_MODULE,	 contextRegAddr[6], vco_reg_val[6], NULL);
	glue_reg_Write(CHIRP_AFC_MODULE,	 contextRegAddr[5], vco_reg_val[5], NULL);
	glue_reg_Write(CHIRP_AFC_MODULE,	 contextRegAddr[4], vco_reg_val[4], NULL);
	glue_reg_Write(CHIRP_AFC_MODULE, 	 contextRegAddr[3], vco_reg_val[3], NULL);
	glue_reg_Write(CHIRP_AFC_MODULE, 	 contextRegAddr[2], vco_reg_val[2], NULL);
	glue_reg_Write(CHIRP_AFC_MODULE,	 contextRegAddr[1], vco_reg_val[1], NULL);
	glue_reg_Write(TIMING_ENGINE_MODULE, contextRegAddr[0], vco_reg_val[0], NULL);

	//disable force divider
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, &DivForce.val_u32, NULL);

	DivForce.bits_st.CtlForceDivider = 0;

	glue_reg_WriteCheck(CHIRP_AFC_MODULE_ADDRESS, NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16, DivForce.val_u32, NULL);
}

static void update_vco_profile_suband(void)
{
	rmtp_rf_ic_status_t rf_status;
	int      rmtp_return;
	double effFc;
	float  fStart, fStop, usedBW = 0;
	uint8_t subband = 0, has_chg_flag = 0;
	float  tSample;
	int    SBSelStatus, i, deci;
	int    max_cur_subband = 0, min_cur_subband = 0;

	#ifdef TEF810X_DBG
	float fBegin[128];
	float fEnd[128];
	float BW[128];

	PRINTF("narrowBand = %d\n", narrowBand);
	//get VCO tables to variables
	chip_CAFC_GetVCOTable(narrowBand, fBegin, fEnd, BW);

	PRINTF("  No.      Fstart              Fstop               BW\n");
	PRINTF("************************************************************\n");
	//for(int i=0; i<128; i++)
	for(int i=20; i<80; i++)
	{
		PRINTF(" %03d  %9.5f  %0.5f  %9.5f\n", i, fBegin[i], fEnd[i], BW[i]);
	}
	#endif

	if(MIPI_NUM_LANES == 4)
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 1;                             // Sample rate = 40MHz/1 = 40 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
		else
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
	}
	else if(MIPI_NUM_LANES == 2)
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
		else
			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
	}
	else
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
		else
			deci = 16;                            // Sample rate = 40MHz/16 = 2.5 MHz
	}

	tSample = (SAMPLES_PER_CHIRP  * deci * 25.0) / 1000.0;
	for(i=0; i<3; i++)
	{
		effFc = rf_config[i].freq;
		subband = 0;
		#ifdef TEF810X_DBG
		PRINTF(" effFc[%x] = %f\n", i, effFc);
		#endif

#ifdef DOLPHIN_CFG_ES3
	#ifndef SB_BINARYSEARCH_ENABLE
			SBSelStatus = chip_CTRL_SubBandSelect(&effFc, (float)rf_config[i].bandwidth, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
	#else
			SBSelStatus = chip_CAFC_SubBandSelectBinarySearch((&effFc, (float)rf_config[i].bandwidth, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
	#endif
#else
        SBSelStatus = chip_CAFC_SubBandSelect(&effFc, (float)rf_config[i].bandwidth, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, dolphin_flag.narrowband, &subband);
#endif

		#ifdef TEF810X_DBG
		PRINTF("Profile %x, subband = %d\n", i, subband);
		#endif
		if(SBSelStatus >= 0)
		{
			if(vco_current_subband[i] != subband)
			{
				vco_current_subband[i] = subband;
#ifdef DOLPHIN_CFG_ES3
				chip_CAFC_ProfileConfig(i, dolphin_flag.narrowband, false, subband, (float)rf_config[i].loopBW, usedBW, rf_config[i].freq, (float)tSettle, tSample, (float)tJumpback);
#else
				chip_CAFC_ProfileConfig(i, dolphin_flag.narrowband, false, subband, (float)rf_config[i].loopBW, usedBW, (float)tSettle, tSample, (float)tJumpback);
#endif

				//setup the Timing Engine profile
				chip_TE_ProfileConfig(i, (float)tDwell, (float)tSettle, SAMPLES_PER_CHIRP, deci, dolphin_flag.pdc_bwwide, (float)tDwell + (float)tSettle + tSample + (float)tJumpback + (float)rf_config[i].tReset + t_idle[i],
									bps[i], txsw[i], txpon[i], rxpon[i]);

				//setup the Sweep Control profile
				chip_SC_ProfileConfig(i, fStart, usedBW, (float)tSettle, tSample, (float)tJumpback, (float)rf_config[i].tReset, false);

				has_chg_flag = 1;

				if(i==0)
				{
					PRINTF("****************************************\n");
					PRINTF("** Change Profile%d VCO subband to %d **\n", i, subband);
					PRINTF("****************************************\n");
				}
			}
		}
		else
		{
			vco_current_subband[i] = -1;
			PRINTF("Select subband Failed!!\n");
		}

		if(i==0)
		{
			max_cur_subband = vco_current_subband[0];
			min_cur_subband = vco_current_subband[0];
		}
		else
		{
			if(vco_current_subband[i] > max_cur_subband)
				max_cur_subband = vco_current_subband[i];

			if(vco_current_subband[i] < min_cur_subband)
				min_cur_subband = vco_current_subband[i];
		}
	}


	if(min_cur_subband < 0)
	{
		min_cur_subband = 0;
		TEF810x_error_status++;
		PRINTF("Can not find the subband\n");

		rf_status.data_type = RF_VCO_STATUS;
		rf_status.message_ID = VCO_NO_SUBBAND;
		rmtp_return = rmtp_send_rf_ic_status_message((uint8_t *) &rf_status, sizeof(rf_status));

		update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);

		if(rmtp_return == RES_PARAMETER_ERROR)
			PRINTF("Send rmtp message error\n");

		vco_start_subband = 0;
		vco_stop_subband = SEARCH_VCO_RANGE;
	}
	else
	{
		vco_start_subband = min_cur_subband - SEARCH_VCO_RANGE;
		if(vco_start_subband < 0)
			vco_start_subband = 0;

		vco_stop_subband  = max_cur_subband + SEARCH_VCO_RANGE;
		if(vco_stop_subband > 127)
			vco_stop_subband = 127;

		update_tef810x_status(MONITOR_ID_RF_ISM, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
	}

	if(has_chg_flag)
	{
		//set LO level control
		hal_es3_rx_SetLoLevel(effFc);

		hal_es3_cafc_EnableVCO();
	}
}

static void push_vco_register_for_vco_cal(void)
{
	//Save context.
	glue_reg_Read(TIMING_ENGINE_MODULE_ADDRESS, contextRegAddr[0], &vco_reg_val[0], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[1], &vco_reg_val[1], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[2], &vco_reg_val[2], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[3], &vco_reg_val[3], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[4], &vco_reg_val[4], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[5], &vco_reg_val[5], NULL);
	glue_reg_Read(CHIRP_AFC_MODULE_ADDRESS, 	contextRegAddr[6], &vco_reg_val[6], NULL);

}

bool_t tef_check_adc_cal_done(void)
{
	uint32_t readData = 0;

	//check calibration status 1 2 (this is finer status than CALIBRATION_STATUS)
	glue_reg_Read(ADC_12_MODULE, cal_monitor_status, &readData, NULL);
	//PRINTF("ADC12 cal status:%lx\n", readData);
	if (readData & 0x1)
	{
		readData = 0;
		//check calibration status 3 4
		glue_reg_Read(ADC_34_MODULE, cal_monitor_status, &readData, NULL);
		//PRINTF("ADC34 cal status:%lx\n", readData);

		if (readData &0x1)
		{
			//calibration succeeded
			tef_Caliration_status &= ~ADC_CALIBRATION_MASK_FLAG;
			return TRUE;
		}
		else
		{
			timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_check_adc_cal_done, NULL);
			//#ifdef TEF810X_DBG
			PRINTF("ADC Cal not yet! Wait next tick!\n");
			//#endif
			return FALSE;
		}
	}
	else
	{
		timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_check_adc_cal_done, NULL);
		//#ifdef TEF810X_DBG
		PRINTF("ADC Cal not yet! Wait next tick!\n");
		//#endif
		return FALSE;
	}
}

void do_tef_background_adc_calibration(void)
{
	uint32_t reg_val;
//	int32_t ret;

	// XXX TODO Execute IP func reset before chirp start
	chip_reg_Read(CENTRAL_CTRL_MOUDLE, functional_reset_control, &reg_val, NULL);

	reg_val &= ~0x180U;
	chip_reg_Write(CENTRAL_CTRL_MOUDLE, functional_reset_control, reg_val, NULL);

	reg_val |= 0x180U;
	chip_reg_Write(CENTRAL_CTRL_MOUDLE, functional_reset_control, reg_val, NULL);

	tef_Caliration_status |= ADC_CALIBRATION_MASK_FLAG;
	chip_ADC_Recalibrate();
//	if (ret != 0) PRINTF("chip_ADC_Recalibrate() failed!\n");
	timer_set("tef", (int16_t) 1, (int16_t) 1, (event_proc_p)tef_check_adc_cal_done, NULL);
}

/******************************************************************************
Function Name : Do AGC/monitor tef810x
******************************************************************************/
void tef_safety_check(char** args, int count)
{
	if(cur_agc_profile < 7)
	{
		rf_config[TEF810X_RSSI].rxgain = AGC_default_rx_gain;
		chip_RX_ProfileConfig(4, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
		chip_RX_ProfileConfig(3, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
		chip_RX_ProfileConfig(2, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
		chip_RX_ProfileConfig(1, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
		//spt_context_start(SPT_CONTEXT_CLIPPING, tef_clipping_check, NULL);
	}
	else
	{
	    monitor_tef810x();
		
		if(adc_recalibration == 1)
			do_tef_background_adc_calibration();

		chip_ISM_SetMCUReset();
	}
}

void tef_clipping_check(void* x)
{
	uint32_t get_adc_flag;

    //chip_reg_Read(ISM_MODULE, adc_error_flag_raw_status, &get_adc_flag, NULL);
    chip_reg_Read(ISM_MODULE,adc_error_flag_masked_status, &get_adc_flag, NULL);
	//PRINTF("get_adc_flag = 0x%lx\n", get_adc_flag);
    if((get_adc_flag & 0x7FFFFFF0) != 0)
    {
    	if(rf_config[TEF810X_RSSI].rxgain > 0)
    	{
    		rf_config[TEF810X_RSSI].rxgain -= 1;
    		chip_RX_ProfileConfig(4, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
    		chip_RX_ProfileConfig(3, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
    		chip_RX_ProfileConfig(2, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
    		chip_RX_ProfileConfig(1, 3, rf_config[TEF810X_RSSI].rxgain, rf_config[TEF810X_RSSI].lpf, rf_config[TEF810X_RSSI].hpf, TRUE);
			#ifdef TEF810X_DBG
			PRINTF("rxgain = %x\n", rf_config[TEF810X_RSSI].rxgain);
			#endif
			//spt_context_start(SPT_CONTEXT_CLIPPING, tef_clipping_check, NULL);
			return;
    	}
    	else
    	{
    		rf_config[TEF810X_RSSI].rxgain = 0;
			if(cur_agc_profile < 4)
    		{
	    		if(rf_config[TEF810X_RSSI].rxgain != rf_config[cur_agc_profile].rxgain)
    			{
    				rf_config[cur_agc_profile].rxgain = rf_config[TEF810X_RSSI].rxgain;
    				chip_RX_ProfileConfig(4, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
    				chip_RX_ProfileConfig(3, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
    				chip_RX_ProfileConfig(2, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
    				chip_RX_ProfileConfig(1, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
    			}
    		}
			else
			{
				if(rf_config[TEF810X_RSSI].rxgain != rf_config[0].rxgain)
				{
    				rf_config[0].rxgain = rf_config[TEF810X_RSSI].rxgain;
    				rf_config[1].rxgain = rf_config[TEF810X_RSSI].rxgain;
    				chip_RX_ProfileConfig(4, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
    				chip_RX_ProfileConfig(3, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
    				chip_RX_ProfileConfig(2, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
    				chip_RX_ProfileConfig(1, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
    				chip_RX_ProfileConfig(4, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
    				chip_RX_ProfileConfig(3, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
    				chip_RX_ProfileConfig(2, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
    				chip_RX_ProfileConfig(1, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
				}
			}
    	}
    }
    else
    {
		if(cur_agc_profile < 4)
		{
			if(rf_config[TEF810X_RSSI].rxgain != rf_config[cur_agc_profile].rxgain)
			{
				rf_config[cur_agc_profile].rxgain = rf_config[TEF810X_RSSI].rxgain;
				chip_RX_ProfileConfig(4, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
				chip_RX_ProfileConfig(3, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
				chip_RX_ProfileConfig(2, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
				chip_RX_ProfileConfig(1, cur_agc_profile, rf_config[cur_agc_profile].rxgain, rf_config[cur_agc_profile].lpf, rf_config[cur_agc_profile].hpf, TRUE);
			}
		}
		else
		{
			if(rf_config[TEF810X_RSSI].rxgain != rf_config[0].rxgain)
			{
				rf_config[0].rxgain = rf_config[TEF810X_RSSI].rxgain;
				rf_config[1].rxgain = rf_config[TEF810X_RSSI].rxgain;
				chip_RX_ProfileConfig(4, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
				chip_RX_ProfileConfig(3, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
				chip_RX_ProfileConfig(2, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
				chip_RX_ProfileConfig(1, 0, rf_config[0].rxgain, rf_config[0].lpf, rf_config[0].hpf, TRUE);
				chip_RX_ProfileConfig(4, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
				chip_RX_ProfileConfig(3, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
				chip_RX_ProfileConfig(2, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
				chip_RX_ProfileConfig(1, 1, rf_config[1].rxgain, rf_config[1].lpf, rf_config[1].hpf, TRUE);
			}
		}
    }

	if(adc_recalibration == 1)
		do_tef_background_adc_calibration();

	monitor_tef810x();
}

/******************************************************************************
Function Name : initial TEF810x
******************************************************************************/
void initial_tef810x(char** args, int count)
{
	init_TEF810x();
}

/******************************************************************************
Function Name : clear SDRAM 1M address data to 0
******************************************************************************/
void clr_sram(char** args, int count)
{
	clear_shared_ram();
}

/******************************************************************************
Function Name : clear SDRAM 1M address data to 0
******************************************************************************/
/*void printf_all_tef810x_reg(char** args, int count)
{
	print_TEF810x_all();
}*/

/******************************************************************************
Function Name : Send chirp function
******************************************************************************/
static void send_chirp_test(char** args, int count)
{
	if(count > 4){
		uint8_t  proileNum;
		uint16_t chirpNum;
		uint32_t repeatNum;
		uint8_t IsFailed = FALSE;

		proileNum   = (uint8_t)strtoul(args[2],NULL, 10);
		chirpNum = (uint16_t)strtoul(args[3],NULL, 10);
		repeatNum = (uint8_t)strtoul(args[4],NULL, 10);

		if(proileNum < 0 || proileNum > 6){
			PRINTF("profileNum input invalid\n");
			IsFailed = TRUE;
		}
		if(chirpNum < 1 || chirpNum > 0xFFFF){
			PRINTF("chirpNum input invalid\n");
			IsFailed = TRUE;
		}
		if(repeatNum < 1 || repeatNum > 0xFF){
			PRINTF("repeatNum input invalid\n");
			IsFailed = TRUE;
		}
		if(IsFailed){
			return;
		}
		send_chirp(proileNum, chirpNum, repeatNum);
	}
	else{
		PRINTF("tef send: [proileNum(0-6), chirpNum(1-2^16), repeatNum(1-255)]\n");
	}
}

void send_chirp(uint8_t proileNum, uint16_t chirpNum, uint32_t repeatNum)
{
	bool pin_status = 0;
	hal_ES3_CSI2_Datatoggle_Disable();

	//Enable Chirp Start Pin Output
	Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t ChirpStartPadcontrol;
	glue_reg_Read(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16, &ChirpStartPadcontrol.val_u32, NULL);
	ChirpStartPadcontrol.bits_st.ChirpstartMfioEn = 0;
	glue_reg_WriteCheck(CENTRAL_CONTROL_MODULE_ADDRESS, NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16, ChirpStartPadcontrol.val_u32, NULL);

	hal_es3_teng_CfgChirpProfile(proileNum, repeatNum, proileNum <= 3 ? 0 : 1);
	hal_es3_teng_CfgNumChirpSeq(1, chirpNum);
	hal_es3_teng_LoadProfile(proileNum);

	chip_ISM_SetMCUReset();  //reset ism error.

	uint32_t sTime = STM_0.CNT.R;
	chip_TE_ChirpStart();

	//wait for chirpSeq done.
	do{
		glue_GetGPIO(DOLPHIN_EXTPIO_CHIRPSTART, &pin_status);
		#ifdef ENABLE_SWT
		clear_SWT0_counter();
		#endif
		fs8x_wd_handle(fs8xNormal);
	}while(pin_status != 0);

	uint32_t eTime = STM_0.CNT.R;
	//tef810x status check
	if(tef_dbg_flag)
		tef810x_debug_log();
	monitor_tef810x();

	//hal_ES3_CSI2_Datatoggle_Enable();
	PRINTF("send_chirp time: %.3f\n", (eTime - sTime) * CLOCK_PERIOD_US);
}

void chg_TEF810x_agc_def_rx_gain(char** args, int count)
{
	if(count > 2)
		tef810x_info->agc_default_gain        = (uint8_t)atoi(args[2]) & 0x7;

	AGC_default_rx_gain = tef810x_info->agc_default_gain;
	PRINTF("AGC_default_rx_gain = %x\n", AGC_default_rx_gain);
}

void do_TEF810x_mclk_cal(char** args, int count)
{
	chip_MCLK_Recalibrate();
	PRINTF("Do MCLK calibrate.\n");

}

/******************************************************************************
Function Name : set_to_fcw_pars - set to use FCW parameters
******************************************************************************/
/*static void set_to_fcw_pars(char** args, int count)
{

	memcpy(&tef810x_parameters.info, &tef810x_fcw_info, sizeof(tef810x_info_t));
	pars_set((pars_ctx_p)&tef810x_parameters);
	#ifdef ENABLE_SWT
	reset_system();
	#endif

}
*/
/******************************************************************************
Function Name : set_to_bsd_pars - set to use BSD parameters
******************************************************************************/
/*static void set_to_bsd_pars(char** args, int count)
{
	memcpy(&tef810x_parameters.info, &tef810x_bsd_info, sizeof(tef810x_info_t));
	pars_set((pars_ctx_p)&tef810x_parameters);
	#ifdef ENABLE_SWT
	reset_system();
	#endif
}
*/
/******************************************************************************
Function Name : set_to_tbb_pars - set to use TBB(School Bus) parameters
******************************************************************************/
/*static void set_to_tbb_pars(char** args, int count)
{
	memcpy(&tef810x_parameters.info, &tef810x_tbb_info, sizeof(tef810x_info_t));
	pars_set((pars_ctx_p)&tef810x_parameters);
	#ifdef ENABLE_SWT
	reset_system();
	#endif
}
*/
/******************************************************************************
Function Name : set_to_bsd_two_beam_pars - set to use bsd two beam parameters
******************************************************************************/
/*static void set_to_bsd_two_beam_pars(char** args, int count)
{
	if(count > 2)
	{
		int16_t option = strtol(args[2], NULL, 10);

		if(option == 1)
		{
			memcpy(&tef810x_parameters.info, &tef810x_bsd_two_beam_m_info, sizeof(tef810x_info_t));
			pars_set((pars_ctx_p)&tef810x_parameters);
			#ifdef ENABLE_SWT
			reset_system();
			#endif
		}
		else if(option == 2)
		{
			memcpy(&tef810x_parameters.info, &tef810x_bsd_two_beam_s_info, sizeof(tef810x_info_t));
			pars_set((pars_ctx_p)&tef810x_parameters);
			#ifdef ENABLE_SWT
			reset_system();
			#endif
		}
	}
	else
	{
		PRINTF("Error: No parameter\n");
	}
}
*/
/******************************************************************************
Function Name : set_to_trbsd_pars - set to use TB(Taiwan Railway) BSD parameters
******************************************************************************/
/*static void set_to_trbsd_pars(char** args, int count)
{
	if(count > 2)
	{
		int16_t option = strtol(args[2], NULL, 10);

		if(option == 1)
		{
			memcpy(&tef810x_parameters.info, &tef810x_trh1_bsd_info, sizeof(tef810x_trh1_bsd_info));
		}
		else if (option == 2)
		{
			memcpy(&tef810x_parameters.info, &tef810x_trh2_bsd_info, sizeof(tef810x_trh2_bsd_info));
		}
		else
		{
			memcpy(&tef810x_parameters.info, &tef810x_trv1_bsd_info, sizeof(tef810x_trv1_bsd_info));
		}

		pars_set((pars_ctx_p)&tef810x_parameters);
		#ifdef ENABLE_SWT
		reset_system();
		#endif
	}
	else
	{
		PRINTF("Error: No parameter\n");
	}
}
*/
/******************************************************************************
Function Name : set_to_trfcw_pars - set to use TB(Taiwan Railway) FCW parameters
******************************************************************************/
/*static void set_to_trfcw_pars(char** args, int count)
{
	memcpy(&tef810x_parameters.info, &tef810x_tr_fcw_info, sizeof(tef810x_info_t));
	pars_set((pars_ctx_p)&tef810x_parameters);
	#ifdef ENABLE_SWT
	reset_system();
	#endif
}
*/
/******************************************************************************
Function Name : set_to_trfcw_pars - set to use TB(Taiwan Railway) FCW parameters
******************************************************************************/
/*static void set_to_fenixrcw_pars(char** args, int count)
{
	memcpy(&tef810x_parameters.info, &tef810x_fenix_rcw_info, sizeof(tef810x_info_t));
	pars_set((pars_ctx_p)&tef810x_parameters);
	#ifdef ENABLE_SWT
	reset_system();
	#endif
}
*/
/******************************************************************************
Function Name : get tef810x temperature
******************************************************************************/
static void get_TEF810x_temperature(void)
{
	float tempRO = 0;

	tempRO = chip_ATB_ReadTemp(0x1, TX1_MODULE);
	PRINTF("TEF TX1 Temp = %f\n", tempRO);
//	tempRO = chip_ATB_ReadTemp(0x1, TX2_MODULE);
//	PRINTF("TEF TX2 Temp = %f\n", tempRO);
//	tempRO = chip_ATB_ReadTemp(0x1, TX3_MODULE);
//	PRINTF("TEF TX3 Temp = %f\n", tempRO);
}

/******************************************************************************
Function Name : get_tef810x_temperature
******************************************************************************/
float get_tef810x_temperature(void)    //temperature min:-40 max:135
{
	return Rf_Temp;
}

/******************************************************************************
Function Name : tef_all_HPF100 - Set all of profile's HPF = 100k
******************************************************************************/
void tef_all_HPF100(void)
{
	uint32_t reg_val;


	//for [450,650) kHz HPF6dBCutOffHz, set to 400KHz cutoff.
	//HPF_RX_SET = 0;
	reg_val = 0;

	//write HPF setting
	glue_reg_Write(RX1_MODULE, hpf_rx_direct_set_profile0, reg_val, NULL);
	glue_reg_Write(RX2_MODULE, hpf_rx_direct_set_profile0, reg_val, NULL);
	glue_reg_Write(RX3_MODULE, hpf_rx_direct_set_profile0, reg_val, NULL);
	glue_reg_Write(RX4_MODULE, hpf_rx_direct_set_profile0, reg_val, NULL);
	glue_reg_Write(RX1_MODULE, hpf_rx_direct_set_profile1, reg_val, NULL);
	glue_reg_Write(RX2_MODULE, hpf_rx_direct_set_profile1, reg_val, NULL);
	glue_reg_Write(RX3_MODULE, hpf_rx_direct_set_profile1, reg_val, NULL);
	glue_reg_Write(RX4_MODULE, hpf_rx_direct_set_profile1, reg_val, NULL);
	glue_reg_Write(RX1_MODULE, hpf_rx_direct_set_profile2, reg_val, NULL);
	glue_reg_Write(RX2_MODULE, hpf_rx_direct_set_profile2, reg_val, NULL);
	glue_reg_Write(RX3_MODULE, hpf_rx_direct_set_profile2, reg_val, NULL);
	glue_reg_Write(RX4_MODULE, hpf_rx_direct_set_profile2, reg_val, NULL);
	glue_reg_Write(RX1_MODULE, hpf_rx_direct_set_profile3, reg_val, NULL);
	glue_reg_Write(RX2_MODULE, hpf_rx_direct_set_profile3, reg_val, NULL);
	glue_reg_Write(RX3_MODULE, hpf_rx_direct_set_profile3, reg_val, NULL);
	glue_reg_Write(RX4_MODULE, hpf_rx_direct_set_profile3, reg_val, NULL);
}

/******************************************************************************
Function Name : tef_zero_calibration - set profile 0 & 1's BW= 300M and set HPF = 100K
mode 0 :  Original model
mode 1 :  Tx gain unchanged
bandwidth == 0 : chirp bandwidth use default value in define ZERO_CALIBRATION_BW
bandwidth != 0 : chirp bandwidth (each unit = 1MHz)
******************************************************************************/
 
void tef_zero_calibration(uint8_t mode, uint16 bandwidth)
{

	float config_bw, fStart, fStop, usedBW = 0;
	double effFc;
	uint8_t subband = 0;
	float tSample;
	int SBSelStatus, i, deci, loop0, ret;


	if(MIPI_NUM_LANES == 4)
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 1;                             // Sample rate = 40MHz/1 = 40 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
		else
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
	}
	else if(MIPI_NUM_LANES == 2)
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 2;                             // Sample rate = 40MHz/2 = 20 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
		else
			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
	}
	else
	{
		if(MIPI_DATA_RATE == MBITS_480)
			deci = 4;                             // Sample rate = 40MHz/4 = 10 MHz
		else if(MIPI_DATA_RATE == MBITS_240)
			deci = 8;                             // Sample rate = 40MHz/8 =  5 MHz
		else
			deci = 16;                            // Sample rate = 40MHz/16 = 2.5 MHz
	}

	if(bandwidth == 0)
		config_bw = ZERO_CALIBRATION_BW * 1e6;
	else
		config_bw = bandwidth * 1e6;

	tSample = (SAMPLES_PER_CHIRP  * deci * 25.0) / 1000.0;
	for(i=0; i<2; i++)
	{
		float slopeSign = 1;  //sign of the slope according to downChirp
		double fSlope = slopeSign * config_bw / tSample;  //chirp slope
		double tmpFStart = rf_config[i].freq - slopeSign * config_bw / 2 - tSettle * fSlope;  //calculate start frequency include tSettle
		double tmpFStop = rf_config[i].freq + slopeSign * config_bw / 2 + tJumpback * fSlope; //calculate start frequency include tJumpback
		float tmpUsedBW = fabs(tmpFStop - tmpFStart);  //calculate real used bandwidth
		bool_t narrowband = tmpUsedBW > 1e9 ? 0 : 1;

		rf_config[i].bandwidth = config_bw;  // Need to add, because SPT need RF BW info.
		effFc = rf_config[i].freq;
		subband = 0;

		PRINTF("Profile %d bandwidth %d(%.3f) MHz\n", i, (uint16_t)(config_bw / 1e6), tmpUsedBW / 1e6);
		PRINTF("\t  used narrowband = %s\n", (narrowband ? "TRUE" : "FALSE"));

#ifdef DOLPHIN_CFG_ES3
	#ifndef SB_BINARYSEARCH_ENABLE
		SBSelStatus = chip_CTRL_SubBandSelect(&effFc, config_bw, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, (bool)narrowband, &subband);
	#else
		SBSelStatus = chip_CAFC_SubBandSelectBinarySearch((&effFc, config_bw, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, (bool)narrowband, &subband);
	#endif
#else
		SBSelStatus = chip_CAFC_SubBandSelect(&effFc, config_bw, (float)tSettle, tSample, (float)tJumpback, &fStart, &fStop, false, &usedBW, (bool)narrowband, &subband);
#endif

		#ifdef TEF810X_DBG
		PRINTF("Profile %x, subband = %d\n", i, subband);
		#endif
		if(SBSelStatus >= 0)
		{
#ifdef DOLPHIN_CFG_ES3
			chip_CAFC_ProfileConfig(i, (bool)narrowband, false, subband, (float)rf_config[i].loopBW, usedBW, rf_config[i].freq, (float)tSettle, tSample, (float)tJumpback);
#else
			chip_CAFC_ProfileConfig(i, (bool)narrowband, false, subband, (float)rf_config[i].loopBW, usedBW, (float)tSettle, tSample, (float)tJumpback);
#endif
		}
		else
		{
			PRINTF("Select subband Failed!!\n");
		}

		//setup the Timing Engine profile
		chip_TE_ProfileConfig(i, (float)tDwell, (float)tSettle, SAMPLES_PER_CHIRP, deci, dolphin_flag.pdc_bwwide, (float)tDwell + (float)tSettle + tSample + (float)tJumpback + (float)rf_config[i].tReset + t_idle[i],
								bps[i], txsw[i], txpon[i], rxpon[i]);

		//setup the Sweep Control profile
		chip_SC_ProfileConfig(i, fStart, usedBW, (float)tSettle, tSample, (float)tJumpback, (float)rf_config[i].tReset, false);
	}

	//set LO level control
	hal_es3_rx_SetLoLevel(effFc);

	hal_es3_cafc_EnableVCO();

	for(loop0 = 0; loop0 < 4; loop0++)
	{
		ret = chip_CAFC_CalibrateAmplitude(loop0);
		if (ret != 0) PRINTF("VCO profile %x Amplitude Calibration Failed!\n", loop0);
	}

	//tef_all_HPF100();
	set_tef810x_min_gain(mode);
	Delay_ms(5);
}

/******************************************************************************
Function Name : tef810x_reg_readwrite functions
******************************************************************************/
static void tef810x_reg_readwrite(char** args, int count)
{
	uint32_t reg_data[256];
	uint16_t reg_addr, len, i;
	uint8_t  module_addr;

    if(count >=6 )
    {
    	if(!strcmp(args[2], "w"))
    	{
    		module_addr = (uint8_t) strtoul(args[3], NULL, 16);
    		if(module_addr <= ISM_MODULE)
    		{
    			reg_addr       =  strtoul(args[4], NULL, 16);
    			reg_data[0]    = (uint32_t) strtoul(args[5], NULL, 16);
    			glue_reg_Write(module_addr, reg_addr, reg_data[0], NULL);
    			PRINTF("Write Module(0x%02x) Reg(0x%03x) = 0x%08lx\n", (uint16_t) module_addr, reg_addr, reg_data[0]);
    		}
    	}

    	if(!strcmp(args[2], "r"))
    	{
    		module_addr = (uint8_t) strtoul(args[3], NULL, 16);
    		if(module_addr <= ISM_MODULE)
    		{
    			reg_addr    = strtoul(args[4], NULL, 16);
    			len         = strtoul(args[5], NULL, 16);

    			if(len == 1)
    			{
    				glue_reg_Read(module_addr, reg_addr, reg_data, NULL);

        			PRINTF("Read Module(0x%02x) Reg(0x%03x) = 0x%08lx\n", (uint16_t) module_addr, reg_addr, reg_data[0]);
       			}
    			else
    			{
    				if(len > 0 && len <=256)
    				{
   						//glue_reg_BurstRead(module_addr, reg_addr, reg_data, len, FALSE, NULL);

    					PRINTF(" Read  Module(0x%02x)\n", module_addr);
       					PRINTF("--------------------------------\n");
       					for(i=0; i<len; i++)
       					{

       	    				glue_reg_Read(module_addr, reg_addr+i*4, reg_data, NULL);
       						PRINTF("Reg(0x%03x) = 0x%08lx\n", (uint16_t) reg_addr+4*i, reg_data[0]);

       						if(i%16 == 15)
       						{
    							#ifdef ENABLE_SWT
       							clear_SWT0_counter();
    							#endif
       							fs8x_wd_handle(fs8xNormal);
       						}
       					}
    				}
    			}
    		}
    	}
    }
}

/******************************************************************************
Function Name : tef810x_reg_readwrite functions
******************************************************************************/
static void chg_TEF810x_calibration_frame_time(char** args, int count)
{
	if(count > 2)
		tef810x_info->vco_cal_frame_time = (uint16_t)atoi(args[2]);

	vco_cal_frame_time = tef810x_info->vco_cal_frame_time;
	PRINTF("vco_cal_frame_time = %d\n", vco_cal_frame_time);
}

/******************************************************************************
Function Name : tef810x_reg_readwrite functions
******************************************************************************/
/*static void get_rmtp_rf_info(char** args, int count)
{
	uint8_t profile;
	rmtp_rf_profile_gain_info_t rmtp_info;

	if(count > 1)
	{
		profile = (uint16_t)atoi(args[1]);

		rmtp_get_rf_profile_gain_info(profile, &rmtp_info);
	}
}*/

void chg_tef810x_lock_freq_cb(uint8_t time, uint8_t tx, uint16_t cwfreq)
{
	tef810x_info->lock_freq_time = time;
	tef810x_info->lock_freq_tx = tx;
	tef810x_info->lock_freq = cwfreq;
	
	lock_freq_time = tef810x_info->lock_freq_time;
	lock_freq_tx = tef810x_info->lock_freq_tx&0x03;
	lock_freq = tef810x_info->lock_freq;
	
	PRINTF("lock_freq_time = %d\n", lock_freq_time);
	PRINTF("lock_freq_tx = %d\n", lock_freq_tx);
	PRINTF("lock_freq = %d\n", lock_freq);

	pars_set((pars_ctx_p)&tef810x_parameters);
	reset_system();
	
}


/******************************************************************************
Function Name : chg_tef810x_lock_freq_time functions
******************************************************************************/
/*
static void chg_tef810x_lock_freq_time(char** args, int count)
{
	uint8_t time;
	uint8_t tx;
	uint16_t cwfreq;
	
	if(count > 2)
	{
		time = (int8_t)atoi(args[1]);
		tx = (uint8_t)atoi(args[2]);
		cwfreq = (uint16_t)atoi(args[3]);
		chg_tef810x_lock_freq_cb(time, tx, cwfreq);
	}	
	else
	{
	    PRINTF("tef-lockfreq : [lock time ,lock tx, lock freq] \n");
	}
}
*/
/******************************************************************************
Function Name : chg_tef810x_rf_level functions
******************************************************************************/
static void chg_tef810x_rf_level(char** args, int count)
{
	uint8_t tx_Num, temp_H, temp_L;
	if(count > 4)
	{
		tx_Num = (uint8_t)atoi(args[2]);
		temp_H = (uint8_t)atoi(args[3]);
		temp_L = (uint8_t)atoi(args[4]);

		if (temp_H > 0xF || temp_H < 0x0 || temp_L > 0xF || temp_L < 0x0)
		{
			PRINTF("Tx_Level_Num must between 0-15\n");
			return;
		}

		if(tx_Num > 0 && tx_Num < 4)
		{
			tx_Num--;
			tx_default_level_code[tx_Num][0] = temp_H;
			tx_default_level_code[tx_Num][1] = temp_L;
			tef810x_info->tx_level_code[tx_Num][0] = temp_H;
			tef810x_info->tx_level_code[tx_Num][1] = temp_L;
		}
		else
		{
			PRINTF("Tx_Num must between 1-3\n");
			return;
		}

		PRINTF("Tx%d H:%d, L:%d\n", tx_Num, temp_H, temp_L);
	}
	else
	{
		PRINTF("Set_Tx_Level Invalid\n");
	}
}

static void chg_production_mode(char** args, int count)
{
	uint8_t temp_mode;
	if(count > 2)
	{
		temp_mode = (uint8_t)atoi(args[2]);

		if(temp_mode >= 0 && temp_mode <= 1 )
		{
			set_tef810x_production_mode(temp_mode);
		}
		else
		{
			PRINTF("mode must between 0-1\n");
			return;
		}
	}
	else
	{
		PRINTF("Production line mode = %d\n", production_line_mode);
	}
	
}

/******************************************************************************
Function Name : tef810x_command_handle functions
******************************************************************************/
static void tef810x_command_handle(char** args, int count)
{

	if(count > 1)
	{
		if(!strcmp(args[1], "freq"))
			chg_TEF810x_freq(args, count);
		else if(!strcmp(args[1], "init"))
			initial_tef810x(args, count);
		else if(!strcmp(args[1], "chirp"))
			chg_TEF810x_chirp(args, count);
		else if(!strcmp(args[1], "txsw"))
			chg_TEF810x_switch(args, count);
		else if(!strcmp(args[1], "txpow"))
			chg_TEF810x_enable(args, count);
		else if(!strcmp(args[1], "help"))
			get_tef810x_help(args, count);
		else if(!strcmp(args[1], "save"))
			TEF810x_save();
		else if(!strcmp(args[1], "adc"))
			chg_TEF810x_adc_recalibration_flag(args, count);
		else if(!strcmp(args[1], "txcal"))
			chg_TEF810x_tx_calibration_flag(args, count);
		else if(!strcmp(args[1], "caltime"))
			chg_TEF810x_calibration_frame_time(args, count);
		else if(!strcmp(args[1], "temp"))
			get_TEF810x_temperature();
		else if(!strcmp(args[1], "txgain"))
			chg_tef810x_txgain(args, count);
		else if(!strcmp(args[1], "rxgain"))
			chg_tef810x_rxgain(args, count);
		else if(!strcmp(args[1], "filter"))
			chg_tef810x_filter(args, count);
		else if(!strcmp(args[1], "reg"))
			tef810x_reg_readwrite(args, count);
		/*else if(!strcmp(args[1], "rmtpinfo"))
			get_rmtp_rf_info(args, count);*/
		else if(!strcmp(args[1], "rflv"))
			chg_tef810x_rf_level(args, count);
//		else if(!strcmp(args[1], "regdump"))
//			tef810x_register_dump(0x87);
		else if(!strcmp(args[1], "agcdefgain"))
			chg_TEF810x_agc_def_rx_gain(args, count);
//		else if(!strcmp(args[1], "fcwp"))
//			set_to_fcw_pars(args, count);
//		else if(!strcmp(args[1], "bsdp"))
//			set_to_bsd_pars(args, count);
//		else if(!strcmp(args[1], "tbbp"))
//			set_to_tbb_pars(args, count);
//		else if(!strcmp(args[1], "trbsdp"))
//			set_to_trbsd_pars(args, count);
//		else if(!strcmp(args[1], "trfcwp"))
//			set_to_trfcw_pars(args, count);
//		else if(!strcmp(args[1], "fenixfcwp"))
//			set_to_fenixrcw_pars(args, count);
//		else if(!strcmp(args[1], "bsd2beamp"))
//			set_to_bsd_two_beam_pars(args, count);
		else if (!strcmp(args[1], "cbtest"))
			callback_test(args, count);
		else if (!strcmp(args[1], "inject"))
			error_inject_test(args, count);
		else if (!strcmp(args[1], "setlong"))
			set_tef810x_long_profile_test(args, count);
		else if (!strcmp(args[1], "flevel"))
			find_tx_high_level_code_test(args, count);
		else if(!strcmp(args[1], "table"))
			tef_set_tx_table(args, count);
		else if (!strcmp(args[1], "dbg"))
			set_tef_dbg_flag(args, count);
		else if (!strcmp(args[1], "send"))
			send_chirp_test(args, count);
		else if (!strcmp(args[1], "production"))
			chg_production_mode(args, count);
		else if (!strcmp(args[1], "chipinfo"))
			tef810x_chip_info();
		else if (!strcmp(args[1], "selftest")){
			DolphinIC_rval_t data[END_OF_MESSAGE];
			if(tef810x_self_test(&data[0], sizeof(data))){
				PRINTF("SELFTEST FAILED\n");
				for(uint8_t index = 0; index < END_OF_MESSAGE; index++)
					PRINTF("ID(%02d) %ld\n", index, data[index]);
			}else{
				PRINTF("SELFTEST PASSED\n");
			}
		}
		#ifdef TEF810X_INSERT_TEST
		else if(!strcmp(args[1], "settemp"))
		{
			if (count > 2)
				Rf_Temp_V = (float)atoi(args[2]);
		}
		#endif
		else
			;
	}
	else
	{
		get_tef810x_info(args, count);
	}
}

/******************************************************************************
Function Name : register console functions
******************************************************************************/
static void tef_console_commands_reg(void)
{
	console_command_reg("tef", tef810x_command_handle);

}


/******************************************************************************
Function Name : Block read Dolphin register value
******************************************************************************/
void tef_reg_blobk_read(uint8_t module_addr, uint16_t reg_addr, uint16_t size, uint32_t* data_block)
{
	uint16_t i;

	for(i=0; i < size; i++)
	{
		glue_reg_Read(module_addr, reg_addr+i*4, data_block, NULL);
		data_block++;
	}
}


/******************************************************************************
Function Name : read Dolphin register value
******************************************************************************/
uint32_t tef_reg_read(uint8_t module_addr, uint16_t reg_addr)
{
	uint32_t read_data;

	glue_reg_Read(module_addr, reg_addr, &read_data, NULL);

	return read_data;
}


/******************************************************************************
Function Name : write Dolphin register value
******************************************************************************/
void tef_reg_write(uint8_t module_addr, uint16_t reg_addr, uint32_t write_data)
{
	glue_reg_Write(module_addr, reg_addr, write_data, NULL);
}


static int tef810x_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(TEF_PARS_ID>>24),(char)(TEF_PARS_ID>>16),(char)(TEF_PARS_ID>>8),(char)(TEF_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, tef810x_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, tef810x_parameters.hdr.size  - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt,JSON_PROFILE1_CONFIG,offsetof(tef810x_info_t, profile1_config),tef810x_info->profile1_config[0],tef810x_info->profile1_config[1],
				tef810x_info->profile1_config[2],tef810x_info->profile1_config[3],tef810x_info->profile1_config[4],tef810x_info->profile1_config[5],
				tef810x_info->profile1_config[6],tef810x_info->profile1_config[7]);
		cnt += sprintf(ws+cnt, JSON_PROFILE2_CONFIG,offsetof(tef810x_info_t, profile2_config),tef810x_info->profile2_config[0],tef810x_info->profile2_config[1],
				tef810x_info->profile2_config[2],tef810x_info->profile2_config[3],tef810x_info->profile2_config[4],tef810x_info->profile2_config[5],
				tef810x_info->profile2_config[6],tef810x_info->profile2_config[7]);
		cnt += sprintf(ws+cnt, JSON_PROFILE3_CONFIG,offsetof(tef810x_info_t, profile3_config),tef810x_info->profile3_config[0],tef810x_info->profile3_config[1],
				tef810x_info->profile3_config[2],tef810x_info->profile3_config[3],tef810x_info->profile3_config[4],tef810x_info->profile3_config[5],
				tef810x_info->profile3_config[6],tef810x_info->profile3_config[7]);
		cnt += sprintf(ws+cnt, JSON_PROFILE4_CONFIG,offsetof(tef810x_info_t, profile4_config),tef810x_info->profile4_config[0],tef810x_info->profile4_config[1],
				tef810x_info->profile4_config[2],tef810x_info->profile4_config[3],tef810x_info->profile4_config[4],tef810x_info->profile4_config[5],
				tef810x_info->profile4_config[6],tef810x_info->profile4_config[7]);
		cnt += sprintf(ws+cnt, JSON_DWELL_TIME,offsetof(tef810x_info_t, dwell),tef810x_info->dwell);
		cnt += sprintf(ws+cnt, JSON_SETTLE_TIME,offsetof(tef810x_info_t, settle),tef810x_info->settle);
		cnt += sprintf(ws+cnt, JSON_JUMPBACK_TIME,offsetof(tef810x_info_t, jumpback),tef810x_info->jumpback);
		cnt += sprintf(ws+cnt, JSON_TX_POW,offsetof(tef810x_info_t, txpon),tef810x_info->txpon[0][0],tef810x_info->txpon[0][1],tef810x_info->txpon[0][2],
				tef810x_info->txpon[1][0],tef810x_info->txpon[1][1],tef810x_info->txpon[1][2],tef810x_info->txpon[2][0],tef810x_info->txpon[2][1],
				tef810x_info->txpon[2][2],tef810x_info->txpon[3][0],tef810x_info->txpon[3][1],tef810x_info->txpon[3][2]);
		cnt += sprintf(ws+cnt, JSON_TX_SW,offsetof(tef810x_info_t, txsw),tef810x_info->txsw[0][0],tef810x_info->txsw[0][1],tef810x_info->txsw[0][2],
				tef810x_info->txsw[1][0],tef810x_info->txsw[1][1],tef810x_info->txsw[1][2],tef810x_info->txsw[2][0],tef810x_info->txsw[2][1],
				tef810x_info->txsw[2][2],tef810x_info->txsw[3][0],tef810x_info->txsw[3][1],tef810x_info->txsw[3][2]);
		cnt += sprintf(ws+cnt, JSON_AGC_PROFILE,offsetof(tef810x_info_t, agc_profile),tef810x_info->agc_profile);
		cnt += sprintf(ws+cnt, JSON_AGC_DEF_GAIN,offsetof(tef810x_info_t, agc_default_gain),tef810x_info->agc_default_gain);
		cnt += sprintf(ws+cnt, JSON_NARROW_BAND,offsetof(tef810x_info_t, narrow_band),tef810x_info->narrow_band);
		cnt += sprintf(ws+cnt, JSON_ADC_CALIBRATION,offsetof(tef810x_info_t, adc_recalibration),tef810x_info->adc_recalibration);
		cnt += sprintf(ws+cnt, JSON_TX_CALIBRATION,offsetof(tef810x_info_t, tx_calibration),tef810x_info->tx_calibration);
		cnt += sprintf(ws+cnt, JSON_RESERVER,offsetof(tef810x_info_t, reserved),tef810x_info->reserved[0]);
		cnt += sprintf(ws+cnt, JSON_VCO_CAL_TIME ,offsetof(tef810x_info_t, vco_cal_frame_time),tef810x_info->vco_cal_frame_time);
		cnt += sprintf(ws+cnt, JSON_IDLE_TIME,offsetof(tef810x_info_t, tidle), tef810x_info->tidle[0], tef810x_info->tidle[1], tef810x_info->tidle[2], tef810x_info->tidle[3]);
		cnt += sprintf(ws+cnt, JSON_RX_GAIN,offsetof(tef810x_info_t,rx_gain),
				tef810x_info->rx_gain[0][0],tef810x_info->rx_gain[0][1],tef810x_info->rx_gain[0][2],tef810x_info->rx_gain[0][3],
				tef810x_info->rx_gain[1][0],tef810x_info->rx_gain[1][1],tef810x_info->rx_gain[1][2],tef810x_info->rx_gain[1][3],
				tef810x_info->rx_gain[2][0],tef810x_info->rx_gain[2][1],tef810x_info->rx_gain[2][2],tef810x_info->rx_gain[2][3],
				tef810x_info->rx_gain[3][0],tef810x_info->rx_gain[3][1],tef810x_info->rx_gain[3][2],tef810x_info->rx_gain[3][3]);
		cnt += sprintf(ws+cnt, JSON_TX_GAIN,offsetof(tef810x_info_t,tx_gain),
				tef810x_info->tx_gain[0][0],tef810x_info->tx_gain[0][1],tef810x_info->tx_gain[0][2],
				tef810x_info->tx_gain[1][0],tef810x_info->tx_gain[1][1],tef810x_info->tx_gain[1][2],
				tef810x_info->tx_gain[2][0],tef810x_info->tx_gain[2][1],tef810x_info->tx_gain[2][2],
				tef810x_info->tx_gain[3][0],tef810x_info->tx_gain[3][1],tef810x_info->tx_gain[3][2]);
		cnt += sprintf(ws+cnt, JSON_TX_LEVEL,offsetof(tef810x_info_t,tx_level_code),
				tef810x_info->tx_level_code[0][0], tef810x_info->tx_level_code[0][1],
				tef810x_info->tx_level_code[1][0], tef810x_info->tx_level_code[1][1],
				tef810x_info->tx_level_code[2][0], tef810x_info->tx_level_code[2][1]);
		cnt += sprintf(ws+cnt, JSON_TX_LEVEL_TABLE,offsetof(tef810x_info_t,tx_level_table),
						tef810x_info->tx_level_table[0][0], tef810x_info->tx_level_table[0][1],
						tef810x_info->tx_level_table[1][0], tef810x_info->tx_level_table[1][1],
						tef810x_info->tx_level_table[2][0], tef810x_info->tx_level_table[2][1],
						tef810x_info->tx_level_table[3][0], tef810x_info->tx_level_table[3][1],
						tef810x_info->tx_level_table[4][0], tef810x_info->tx_level_table[4][1],
						tef810x_info->tx_level_table[5][0], tef810x_info->tx_level_table[5][1],
						tef810x_info->tx_level_table[6][0], tef810x_info->tx_level_table[6][1],
						tef810x_info->tx_level_table[7][0], tef810x_info->tx_level_table[7][1],
						tef810x_info->tx_level_table[8][0], tef810x_info->tx_level_table[8][1],
						tef810x_info->tx_level_table[9][0], tef810x_info->tx_level_table[9][1],
						tef810x_info->tx_level_table[10][0], tef810x_info->tx_level_table[10][1],
						tef810x_info->tx_level_table[11][0], tef810x_info->tx_level_table[11][1],
						tef810x_info->tx_level_table[12][0], tef810x_info->tx_level_table[12][1],
						tef810x_info->tx_level_table[13][0], tef810x_info->tx_level_table[13][1]);
		cnt += sprintf(ws+cnt, JSON_RESERVER2,offsetof(tef810x_info_t, reserved2),tef810x_info->reserved2[0], tef810x_info->reserved2[1]);
		cnt += sprintf(ws+cnt, JSON_LOCK_FREQ_TIME,offsetof(tef810x_info_t, lock_freq_time), tef810x_info->lock_freq_time);
		cnt += sprintf(ws+cnt, JSON_LOCK_FREQ_TX,offsetof(tef810x_info_t, lock_freq_tx), tef810x_info->lock_freq_tx);
		cnt += sprintf(ws+cnt, JSON_LOCK_FREQ,offsetof(tef810x_info_t, lock_freq), tef810x_info->lock_freq);		
		cnt += sprintf(ws+cnt, JSON_TEF_DBG,offsetof(tef810x_info_t, tef_dbg), tef810x_info->tef_dbg);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

/******************************************************************************
Function Name : set_tef810x_profile
******************************************************************************/
tef810x_status_t set_tef810x_long_profile(sctrl_profiletiming_t* config)
{
//	static uint8_t subband[2];
	int CheckFlag = TEF810X_OK;
	int ErrMsg = 0;
	uint8_t narrowband = 1; //0:wide band 1:narrow band
	uint8_t deci = deci_table[MIPI_NUM_LANES-1][MIPI_DATA_RATE];

	PRINTF("set tef810x long profile.\n");

	if(profile_recover[0].freq == 0)  //Check if the settings have been restored
		memcpy(&profile_recover[0], &rf_config[0], sizeof(sctrl_profiletiming_t)); //save long1 config for recover
	if(profile_recover[1].freq == 0)  //Check if the settings have been restored
		memcpy(&profile_recover[1], &rf_config[1], sizeof(sctrl_profiletiming_t)); //save long2 config for recover

	hal_ES3_CSI2_Datatoggle_Disable();

	for(uint8_t loop0 = 0; loop0 < 2; loop0++){
		if(config->bandwidth < 0.0 || config->bandwidth > (2000 * 1e6))
		{
			PRINTF("Dolphin error: bandwidth out of range(%dMhz-%dMhz)\n", TEF810X_BW_MIN, TEF810X_BW_MAX);
			CheckFlag = TEF810X_FAIL;
			break;
		}
			if(config->hpf < (TEF810X_HP_MIN * 1e3) || config->hpf > (TEF810X_HP_MAX * 1e3))
		{
			PRINTF("Dolphin error: HPF out of range(%dKhz-%dKhz)\n", TEF810X_HP_MIN, TEF810X_HP_MAX);
			CheckFlag = TEF810X_FAIL;
			break;
		}
		rf_config[loop0].bandwidth = config->bandwidth;
		rf_config[loop0].hpf = config->hpf;

		float slopeSign = 1;  //sign of the slope according to downChirp
		float tSample = SAMPLES_PER_CHIRP * 25.0f / 1000.0f * deci;  //calculate each sample time
		double fSlope = slopeSign * rf_config[loop0].bandwidth / tSample;  //chirp slope
		double tmpFStart = rf_config[loop0].freq - slopeSign * rf_config[loop0].bandwidth / 2 - tSettle * fSlope;  //calculate start frequency include tSettle
		double tmpFStop = rf_config[loop0].freq + slopeSign * rf_config[loop0].bandwidth / 2 + tJumpback * fSlope; //calculate start frequency include tJumpback
		float tmpUsedBW = fabs(tmpFStop - tmpFStart);  //calculate real used bandwidth

		if(tmpUsedBW > 1e9)
			narrowband = 0;
		else
			narrowband = 1;

		chip_RX_ProfileConfig(1, loop0, rx_gain[loop0][0], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(2, loop0, rx_gain[loop0][1], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(3, loop0, rx_gain[loop0][2], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(4, loop0, rx_gain[loop0][3], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);

		//chirp profile program to tef810x ic
		ErrMsg = chip_Chirp_Program(loop0, \
				narrowband, false, \
				&rf_config[loop0].freq, (float)rf_config[loop0].bandwidth, (float)rf_config[loop0].loopBW, \
				(float)tDwell, (float)tSettle, (float)tJumpback, (float)rf_config[loop0].tReset, \
				SAMPLES_PER_CHIRP, deci, \
				dolphin_flag.pdc_bwwide, \
				bps[loop0], txsw[loop0], txpon[loop0], rxpon[loop0], t_idle[loop0]);
		if(ErrMsg == -1){
			PRINTF("Dolphin error: profile(%d) chip_Chirp_Program error(%d)\n", loop0, ErrMsg);
			CheckFlag = TEF810X_FAIL;
			break;
		}

		hal_es3_cafc_EnableVCO();

	}

	hal_ES3_CSI2_Datatoggle_Enable();

	if(CheckFlag == TEF810X_FAIL){
		PRINTF("set tef810x long profile failed!\n");
		PRINTF("recovering...\n");
		if(unset_tef810x_long_profile() == TEF810X_FAIL)
			PRINTF("recovering failed!!!\n");
		else
			PRINTF("recovering success!!!\n");
	}
	else{
		PRINTF("set tef810x success!!!\n");
	}

	return CheckFlag;
}

/******************************************************************************
Function Name : recover_tef810x_profile
******************************************************************************/
tef810x_status_t unset_tef810x_long_profile(void)
{
	int CheckFlag = TEF810X_OK;
	int ErrMsg = 0;
	uint8_t deci = deci_table[MIPI_NUM_LANES-1][MIPI_DATA_RATE];

	PRINTF("recover tef810x long profile.\n");

	if(profile_recover[0].freq == 0 || profile_recover[1].freq == 0)  //Check if the settings have been restored
		return TEF810X_FAIL;
	
	memcpy(&rf_config[0], &profile_recover[0], sizeof(sctrl_profiletiming_t)); //recover long1 config
	memcpy(&rf_config[1], &profile_recover[1], sizeof(sctrl_profiletiming_t)); //recover long2 config

	hal_ES3_CSI2_Datatoggle_Disable();

	for(uint8_t loop0 = 0; loop0 < 2; loop0++){
		chip_RX_ProfileConfig(1, loop0, rx_gain[loop0][0], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(2, loop0, rx_gain[loop0][1], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(3, loop0, rx_gain[loop0][2], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);
		chip_RX_ProfileConfig(4, loop0, rx_gain[loop0][3], (float)rf_config[loop0].lpf, (float)rf_config[loop0].hpf, TRUE);

		chip_Chirp_Program(loop0, \
				dolphin_flag.narrowband, false, \
				&rf_config[loop0].freq, (float)rf_config[loop0].bandwidth, (float)rf_config[loop0].loopBW, \
				(float)tDwell, (float)tSettle, (float)tJumpback, (float)rf_config[loop0].tReset, \
				SAMPLES_PER_CHIRP, deci, \
				dolphin_flag.pdc_bwwide, \
				bps[loop0], txsw[loop0], txpon[loop0], rxpon[loop0], t_idle[loop0]);
		if(ErrMsg == -1){
			PRINTF("Dolphin error: recover profile(%d) chip_Chirp_Program error\n", loop0);
			CheckFlag = TEF810X_FAIL;
		}

		hal_es3_cafc_EnableVCO();

	}

	hal_ES3_CSI2_Datatoggle_Enable();

	return CheckFlag;
}

static void set_tef810x_long_profile_test(char** args, int count)
{
	uint16_t bandwidth, hpf;

	if(count > 2){
		if (!strcmp(args[2], "set")){
			if(count > 4){
				sctrl_profiletiming_t config;

				bandwidth = (uint16_t)atoi(args[3]);
				hpf = (uint16_t)atoi(args[4]);

				config.bandwidth = (double)(bandwidth * 1e6);
				config.hpf = (double)(hpf * 1e3);

				if(set_tef810x_long_profile(&config))
					PRINTF("set long profile failed\n");
			}
		}
		else if (!strcmp(args[2], "unset")){
			if(unset_tef810x_long_profile())
				PRINTF("unset long profile failed\n");
		}
	}
	else{
		PRINTF("input invalid\n");
		PRINTF("tef setlong\n");
		PRINTF("  set [bandwidth, hpf]\n");
		PRINTF("  unset\n");
	}
}

/******************************************************************************
Function Name : RMTP get RF profile gain info
******************************************************************************/
bool_t rmtp_get_rf_profile_gain_info(uint8_t get_profile, rmtp_rf_profile_gain_info_t  *rf_profile_gain_info)
{

	if(get_profile < 4)
	{
		rf_profile_gain_info->center_freq = (uint16_t) (rf_config[get_profile].freq / 100000000);
		rf_profile_gain_info->hpf         = (uint16_t) (rf_config[get_profile].hpf / 1000);
		rf_profile_gain_info->lpf         = (uint16_t) (rf_config[get_profile].lpf / 1e6);
		rf_profile_gain_info->txpon[0]    = txpon[get_profile][0];
		rf_profile_gain_info->txpon[1]    = txpon[get_profile][1];
		rf_profile_gain_info->txpon[2]    = txpon[get_profile][2];
		rf_profile_gain_info->txsw[0]     = txsw[get_profile][0];
		rf_profile_gain_info->txsw[1]     = txsw[get_profile][1];
		rf_profile_gain_info->txsw[2]     = txsw[get_profile][2];
		rf_profile_gain_info->rxgain[0]   = rx_gain[get_profile][0];
		rf_profile_gain_info->rxgain[1]   = rx_gain[get_profile][1];
		rf_profile_gain_info->rxgain[2]   = rx_gain[get_profile][2];
		rf_profile_gain_info->rxgain[3]   = rx_gain[get_profile][3];
		rf_profile_gain_info->txgain[0]   = tx_gain[get_profile][0];
		rf_profile_gain_info->txgain[1]   = tx_gain[get_profile][1];
		rf_profile_gain_info->txgain[2]   = tx_gain[get_profile][2];

		#if 0
		PRINTF("Profile-%x center_freq = %lf\n", get_profile, rf_config[get_profile].freq );
		PRINTF("Profile-%x center_freq = %d\n", get_profile, rf_profile_gain_info->center_freq);
		PRINTF("Profile-%x hpf = %d\n", get_profile, rf_profile_gain_info->hpf);
		PRINTF("Profile-%x lpf = %d\n", get_profile, rf_profile_gain_info->lpf);
		PRINTF("Profile-%x txgain = {%d,%d,%d}\n", get_profile, rf_profile_gain_info->txgain[0], rf_profile_gain_info->txgain[1], rf_profile_gain_info->txgain[2]);
		PRINTF("Profile-%x rxgain = {%d,%d,%d,%d}\n", get_profile, rf_profile_gain_info->rxgain[0], rf_profile_gain_info->rxgain[1], rf_profile_gain_info->rxgain[2], rf_profile_gain_info->rxgain[3]);
		#endif

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
Function Name : RMTP get RF profile gain info
******************************************************************************/
bool_t rmtp_set_rf_profile_gain_setting(uint8_t set_profile, rmtp_rf_profile_gain_info_t  *rf_profile_gain_info)
{

	if(set_profile < 4)
	{
		tx_gain[set_profile][0]               = rf_profile_gain_info->txgain[0];
		tef810x_info->tx_gain[set_profile][0] = tx_gain[set_profile][0];
		tx_gain[set_profile][1]               = rf_profile_gain_info->txgain[1];
		tef810x_info->tx_gain[set_profile][1] = tx_gain[set_profile][1];
		tx_gain[set_profile][2]               = rf_profile_gain_info->txgain[2];
		tef810x_info->tx_gain[set_profile][2] = tx_gain[set_profile][2];
		rx_gain[set_profile][0]               = rf_profile_gain_info->rxgain[0] & 0x7;
		tef810x_info->rx_gain[set_profile][0] = rx_gain[set_profile][0];
		rx_gain[set_profile][1]               = rf_profile_gain_info->rxgain[1] & 0x7;
		tef810x_info->rx_gain[set_profile][1] = rx_gain[set_profile][1];
		rx_gain[set_profile][2]               = rf_profile_gain_info->rxgain[2] & 0x7;
		tef810x_info->rx_gain[set_profile][2] = rx_gain[set_profile][2];
		rx_gain[set_profile][3]               = rf_profile_gain_info->rxgain[3] & 0x7;
		tef810x_info->rx_gain[set_profile][3] = rx_gain[set_profile][3];

		if(set_profile==0)
		{
			rf_config[set_profile].hpf        = rf_profile_gain_info->hpf * 1000;
			tef810x_info->profile1_config[4]  = rf_profile_gain_info->hpf;
			rf_config[set_profile].lpf        = rf_profile_gain_info->lpf * 1000000;
			tef810x_info->profile1_config[5]  = rf_profile_gain_info->lpf;
		}
		else if(set_profile==1)
		{
			rf_config[set_profile].hpf        = rf_profile_gain_info->hpf * 1000;
			tef810x_info->profile2_config[4]  = rf_profile_gain_info->hpf;
			rf_config[set_profile].lpf        = rf_profile_gain_info->lpf * 1000000;
			tef810x_info->profile2_config[5]  = rf_profile_gain_info->lpf;
		}
		else if(set_profile==1)
		{
			rf_config[set_profile].hpf        = rf_profile_gain_info->hpf * 1000;
			tef810x_info->profile3_config[4]  = rf_profile_gain_info->hpf;
			rf_config[set_profile].lpf        = rf_profile_gain_info->lpf * 1000000;
			tef810x_info->profile3_config[5]  = rf_profile_gain_info->lpf;
		}
		else
		{
			rf_config[set_profile].hpf        = rf_profile_gain_info->hpf * 1000;
			tef810x_info->profile4_config[4]  = rf_profile_gain_info->hpf;
			rf_config[set_profile].lpf        = rf_profile_gain_info->lpf * 1000000;
			tef810x_info->profile4_config[5]  = rf_profile_gain_info->lpf;
		}
		txpon[set_profile][0]                 = rf_profile_gain_info->txpon[0];
		tef810x_info->txpon[set_profile][0]   = rf_profile_gain_info->txpon[0];
		txpon[set_profile][1]                 = rf_profile_gain_info->txpon[1];
		tef810x_info->txpon[set_profile][1]   = rf_profile_gain_info->txpon[1];
		txpon[set_profile][2]                 = rf_profile_gain_info->txpon[2];
		tef810x_info->txpon[set_profile][2]   = rf_profile_gain_info->txpon[2];
		txsw[set_profile][0]                  = rf_profile_gain_info->txsw[0];
		tef810x_info->txsw[set_profile][0]    = rf_profile_gain_info->txsw[0];
		txsw[set_profile][1]                  = rf_profile_gain_info->txsw[1];
		tef810x_info->txsw[set_profile][1]    = rf_profile_gain_info->txsw[1];
		txsw[set_profile][2]                  = rf_profile_gain_info->txsw[2];
		tef810x_info->txsw[set_profile][2]    = rf_profile_gain_info->txsw[2];

		chip_reg_Write(TX1_MODULE, 0x0 + (set_profile * 8), tx_gain[set_profile][0], NULL);

		chip_reg_Write(TX2_MODULE, 0x0 + (set_profile * 8), tx_gain[set_profile][1], NULL);

		chip_reg_Write(TX3_MODULE, 0x0 + (set_profile * 8), tx_gain[set_profile][2], NULL);

		chip_RX_ProfileConfig(1, set_profile, rx_gain[set_profile][0], (float)rf_config[set_profile].lpf, (float)rf_config[set_profile].hpf, TRUE);
		chip_RX_ProfileConfig(2, set_profile, rx_gain[set_profile][1], (float)rf_config[set_profile].lpf, (float)rf_config[set_profile].hpf, TRUE);
		chip_RX_ProfileConfig(3, set_profile, rx_gain[set_profile][2], (float)rf_config[set_profile].lpf, (float)rf_config[set_profile].hpf, TRUE);
		chip_RX_ProfileConfig(4, set_profile, rx_gain[set_profile][3], (float)rf_config[set_profile].lpf, (float)rf_config[set_profile].hpf, TRUE);

		pars_set((pars_ctx_p)&tef810x_parameters);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


static void set_tef810x_min_gain(uint8_t mode)
{
	int loop0;

	for(loop0=0; loop0<4; loop0++)
	{
		PRINTF("Profile %d:\n", loop0);
		if(mode!=1){
		    chip_reg_Write(TX1_MODULE, 0x0 + (loop0 * 8), 1, NULL);
		    chip_reg_Write(TX2_MODULE, 0x0 + (loop0 * 8), 1, NULL);
		    chip_reg_Write(TX3_MODULE, 0x0 + (loop0 * 8), 1, NULL);
		    PRINTF(" Tx1-3 set gain to 1\n");
		}
	
		chip_RX_ProfileConfig(1, loop0, 1, (float)rf_config[loop0].lpf, 100e3, TRUE);
		chip_RX_ProfileConfig(2, loop0, 1, (float)rf_config[loop0].lpf, 100e3, TRUE);
		chip_RX_ProfileConfig(3, loop0, 1, (float)rf_config[loop0].lpf, 100e3, TRUE);
		chip_RX_ProfileConfig(4, loop0, 1, (float)rf_config[loop0].lpf, 100e3, TRUE);
		PRINTF(" Rx1-4 set gain to 1\n");
		PRINTF(" HPF set to 100k\n");
	}

}


uint8_t rmtp_tef810x_txid_to_profile(uint8_t txid)
{
    uint8_t profileId=0xff;
    uint8_t i;


    for(i=0; i<4; i++)
    {
        if(tef810x_info->txsw[i][txid]==1)
        {
            profileId=i;
            break;
        }
    }

    return(profileId);
}

/******************************************************************************
Function Name : get profile0 TX module temperature.
******************************************************************************/
/*
static int get_tef810x_profile0_temperature(float *get_temp)
{
	uint8_t	temp_module;
	float tempRO = 0;

	if(txsw[0][0] > 0)
		temp_module = TX1_MODULE;
	else if(txsw[0][1] > 0)
		temp_module = TX2_MODULE;
	else if(txsw[0][2] > 0)
		temp_module = TX3_MODULE;
	else
		return ERRNO_FAILED;

	tempRO = chip_ATB_ReadTemp(0x1, temp_module);
	PRINTF("TEF810X profile-0 TX Temperature = %f\n", tempRO);
	*get_temp = tempRO;

	return SUCCESSED;

}
*/
/******************************************************************************
Function Name : According profile-0 TX# temperature to set tx gain code
******************************************************************************/
static void set_tef810x_tx_gain_code(void)
{
	float 		tef810x_tx_temperature = Rf_Temp;

//	if(get_tef810x_profile0_temperature(&tef810x_tx_temperature) < 0)
//		PRINTF("Get tef810x profile-0 temperature failed!!!\n");

	if (tx_calibration == 2)
	{
		uint8_t loop;
		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf[3];
		uint8_t tx_level_status_temp = 0;
		int8_t change_level_val = (int8_t)TX_HIGH_LEVEL_TABLE[0][1];

		glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[0].val_u32, NULL);
		glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[1].val_u32, NULL);
		glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf[2].val_u32, NULL);

		for (loop = 0; loop < 14; loop++)
		{
			if (Rf_Temp >= ((float)TX_HIGH_LEVEL_TABLE[loop][0] + BOUNDARY))
			{
				if(tx_level_status_temp < 13)
					tx_level_status_temp = loop + 1;
				change_level_val = (int8_t)TX_HIGH_LEVEL_TABLE[tx_level_status_temp][1];
			}
		}

		if(tx_level_status_temp != tx_level_status)
		{
			if (tx_level_status_temp > tx_level_status)
			{
				tx_level_status = tx_level_status_temp;

				FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = tx_default_level_code[0][0] + change_level_val;
				if(FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = 0xF;
				FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = tx_default_level_code[1][0] + change_level_val;
				if(FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = 0xF;
				FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = tx_default_level_code[2][0] + change_level_val;
				if(FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = 0xF;
				glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[0].val_u32, NULL);
				glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[1].val_u32, NULL);
				glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[2].val_u32, NULL);
			}
			else if (tx_level_status_temp < tx_level_status)
			{
				if(Rf_Temp < ((float)TX_HIGH_LEVEL_TABLE[tx_level_status][0] - BOUNDARY - BOUNDARY_GAP))
				{
					tx_level_status = tx_level_status_temp;

					FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = tx_default_level_code[0][0] + change_level_val;
					if(FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi = 0xF;
					FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = tx_default_level_code[1][0] + change_level_val;
					if(FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi = 0xF;
					FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = tx_default_level_code[2][0] + change_level_val;
					if(FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi > 0xF) FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi = 0xF;

					glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[0].val_u32, NULL);
					glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[1].val_u32, NULL);
					glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf[2].val_u32, NULL);
				}
			}
			tx_cal_level_code[0][0] = FuncsafeMonLevelRf[0].bits_st.LevelRfHighSpi;
			tx_cal_level_code[1][0] = FuncsafeMonLevelRf[1].bits_st.LevelRfHighSpi;
			tx_cal_level_code[2][0] = FuncsafeMonLevelRf[2].bits_st.LevelRfHighSpi;
		}
	}
	else if (tx_calibration == 1)
	{
		uint32_t   	rf_mon_level_data, max_level_data, min_level_data;
	glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &rf_mon_level_data, NULL);

	max_level_data = rf_mon_level_data >> 24;
	min_level_data = 1;//rf_mon_level_data & 0x3F;

	if(tef810x_tx_temperature < 25.0)
	{
		rf_mon_level_data = ((max_level_data) << 24) | ((tx_default_level_code[0][0] - 1) << 16) | ((tx_default_level_code[0][1] - 1) << 8) | (min_level_data);

		if(tx_default_level_code[0][0] <= 0)
			rf_mon_level_data |= 0x0 << 16;
		else
			rf_mon_level_data |= (tx_default_level_code[0][0] - 1) << 16;


		if(tx_default_level_code[0][1] <= 0)
			rf_mon_level_data |= 0x0 << 8;
		else
			rf_mon_level_data |= (tx_default_level_code[0][1] - 1) << 8;

	}
	else if(tef810x_tx_temperature > 25 && tef810x_tx_temperature < 90)
	{
		rf_mon_level_data = (max_level_data << 24) | (tx_default_level_code[0][0] << 16) | (tx_default_level_code[0][1] << 8) | min_level_data;
	}
	else
	{
		rf_mon_level_data = ((max_level_data) << 24) | ((tx_default_level_code[0][0] + 1) << 16) | ((tx_default_level_code[0][1] + 1) << 8) | min_level_data;

		if(tx_default_level_code[0][0] > 15)
			rf_mon_level_data |= 0xF << 16;
		else
			rf_mon_level_data |= (tx_default_level_code[0][0] + 1) << 16;


		if(tx_default_level_code[0][1] > 15)
			rf_mon_level_data |= 0xF << 8;
		else
			rf_mon_level_data |= (tx_default_level_code[0][1] + 1) << 8;

	}
	glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, rf_mon_level_data, NULL);
	glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, rf_mon_level_data, NULL);
	glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, rf_mon_level_data, NULL);
}
	else
	{
		Nxp_Tef810x_Mod11_FuncsafeMonLevelRfUnion_t FuncsafeMonLevelRf;

		glue_reg_Read(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
		FuncsafeMonLevelRf.bits_st.LevelRfMinSpi = 1;
		FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = tx_default_level_code[0][0];
		FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = tx_default_level_code[0][1];
		glue_reg_WriteCheck(TX1_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);

		glue_reg_Read(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
		FuncsafeMonLevelRf.bits_st.LevelRfMinSpi = 1;
		FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = tx_default_level_code[1][0];
		FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = tx_default_level_code[1][1];
		glue_reg_WriteCheck(TX2_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);

		glue_reg_Read(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, &FuncsafeMonLevelRf.val_u32, NULL);
		FuncsafeMonLevelRf.bits_st.LevelRfMinSpi = 1;
		FuncsafeMonLevelRf.bits_st.LevelRfHighSpi = tx_default_level_code[2][0];
		FuncsafeMonLevelRf.bits_st.LevelRfLowSpi = tx_default_level_code[2][1];
		glue_reg_WriteCheck(TX3_MODULE_ADDRESS, NXP_TEF810X_MOD11_FUNCSAFE_MON_LEVEL_RF_U16, FuncsafeMonLevelRf.val_u32, NULL);
	}
}

uint8_t rmtp_get_tx_high_level(uint8_t txNum)
{
	if (txNum >= 0 && txNum <= 2)
		return tef810x_info->tx_level_code[txNum][0];
	else
		return 0xFF;
}

uint8_t rmtp_find_tx_high_level(uint8_t txNum, uint16_t txGain)
{
	uint8_t TxLeveValue;
	TxLeveValue = find_tx_high_level_code(txNum+1, txGain);

	if(TxLeveValue == 0xFF)	//TxLeveValue must between 0-15.
	{
		return TRUE;
	}
	else
	{
		tef810x_info->tx_level_code[txNum][0] = TxLeveValue;
		pars_set((pars_ctx_p)&tef810x_parameters);
		return FALSE;
	}
}

void set_tef810x_production_mode(tef810x_production_mode_t production_mode)
{
	switch(production_mode)
	{
	case kNORMAL_MODE:
		production_line_mode = (uint8_t)kNORMAL_MODE;
		PRINTF("Dophin in kNORMAL_MODE\n");
		break;
	case kPRODUCTION_MODE:
		production_line_mode = (uint8_t)kPRODUCTION_MODE;
		PRINTF("Dophin in kPRODUCTION_MODE\n");
		break;
	default:
		production_line_mode = (uint8_t)kNORMAL_MODE;
		break;
	}
}

/******************************************************************************
Function Name : Find tx_high_Level_code correspond with tx_gain_code
******************************************************************************/
static uint8_t find_tx_high_level_code(uint8_t txNum, uint16_t txGain)
{
	uint8_t i;
	uint8_t SELECT_PROFILE = 0xFF;
	uint8_t FOUND_HIGH_LEVEL;
	int32_t ErrMsg;

	if(txNum < 1 || txNum > 3)
	{
		PRINTF("TxNum must between 1-3\n");
		return 0xFF;
	}

	//search txNum activated in which profile
	for(i=0; i<3; i++)
	{
		if(txsw[i][txNum-1] == TRUE)
		{
			SELECT_PROFILE = i;
			break;
		}
	}

	if(SELECT_PROFILE == 0xFF)
	{
		PRINTF("Tx(%d) not active in profile\n", txNum);
		return 0xFF;
	}

	MIPICSI2.PHYC.B.PDRX = 1;                                            // power-down receiver
	MIPICSI2.RXEN.R = 0;                                              // Diable RX
	SPT.GBL_CTRL.B.ACQ_EN = 0;

	ErrMsg = hal_es3_tx_fPCtrl_SetHighThreshold_CubTek(txNum, txGain, SELECT_PROFILE, &FOUND_HIGH_LEVEL);
	if(ErrMsg != 0)
	{
		PRINTF("Tx SetHighThreshold Failed(%ld)\n", ErrMsg);
		return 0xFF;
	}

	PRINTF("Tx%d: %d-Found:%d\n", txNum, txGain, FOUND_HIGH_LEVEL);

	return FOUND_HIGH_LEVEL;
}

/******************************************************************************
Function Name : According profile to monitor
******************************************************************************/
static void cubtek_profile_tx_gain_calibration(uint8_t profile)
{
	Nxp_Tef810x_Mod18_TxErrorFlagMaskedStatusUnion_t	TxErrorFlagMaskedStatus_ust;
	uint32_t	TX_moduleID = 0x00;
	uint8_t     id_idex = 0;
	bool error_low = 0;
	bool error_high = 0;
    bool tx_changed_flags = false;
    bool has_tx_flags     = true;

    if(profile < 4)
    {
		hal_es3_ISM_GetTxErrorStatus(&TxErrorFlagMaskedStatus_ust.val_u32);
    	PRINTF("ISM profile %d ErrorStatus = %lx\n", profile, TxErrorFlagMaskedStatus_ust.val_u32);

		if(txsw[profile][0] == 1)
		{
			error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelLowError;
			error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx1RfLevelHighError;
			TX_moduleID = TX1_MODULE_ADDRESS;
		}
		else if(txsw[profile][1] == 1)
		{
			error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelLowError;
			error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx2RfLevelHighError;
			TX_moduleID = TX2_MODULE_ADDRESS;
		}
		else if(txsw[profile][2] == 1)
		{
			error_low = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelLowError;
			error_high = TxErrorFlagMaskedStatus_ust.bits_st.Tx3RfLevelHighError;
			TX_moduleID = TX3_MODULE_ADDRESS;
		}
		else
		{
		has_tx_flags = false;
		}

		if(has_tx_flags)
		{
			id_idex = TX_moduleID-TX1_MODULE_ADDRESS;
			if(error_low)
			{
				if(error_high)
				{
					PRINTF("[Tef810x] : profile %d RF level setup error\n", profile);
				}
				else
				{
					if(tx_gain[profile][id_idex] != 255)
					{
						tx_gain[profile][id_idex] += 1;
						tx_changed_flags = true;
					}
					else
					{
                		PRINTF("Tx%d Low level error and Tx gain reach to top!\n", id_idex+1);
					}
				}
			}
			else
			{
				if(error_high)
				{
					// The TX minimum gain should be 1;
                	if(tx_gain[profile][TX_moduleID-TX1_MODULE_ADDRESS]  <= 1)
                	{
                		if(tx_gain[profile][TX_moduleID-TX1_MODULE_ADDRESS] == 0)
                		{
                			tx_gain[profile][TX_moduleID-TX1_MODULE_ADDRESS] = 1;
                		}
                		PRINTF("Tx%d high level error and tx gain reach to bottom!\n", id_idex+1);
                	}
                	else
                	{
                    	tx_gain[profile][id_idex] -= 1;
                    	tx_changed_flags = true;
                	}
				}
			}

			if(tx_changed_flags)
			{
    			chip_reg_Write(TX_moduleID, 0x0 + profile*8, tx_gain[profile][TX_moduleID-TX1_MODULE_ADDRESS], NULL);
    			PRINTF("Change profile %x TX%d gain = %d\n", profile, id_idex+1, tx_gain[0][id_idex]);
    		}
		}
	}
}

static void set_tef_dbg_flag(char** args, int count)
{
	uint8_t dbg_flag;

	if(count > 2)
	{
		dbg_flag = (uint8_t)atoi(args[2]);

		if(dbg_flag >= 0 && dbg_flag <= 1 )
		{
			tef_dbg_flag = dbg_flag;
			tef810x_info->tef_dbg = dbg_flag;
		}
		else
		{
			PRINTF("DBG Flag must 0 or 1\n");
		}
	}
	PRINTF("DBG Flag : ");
	if(tef_dbg_flag)
		PRINTF("TRUE\n");
	else
		PRINTF("FALSE\n");
}

static void tef_set_tx_table(char** args, int count)
{
	uint8_t loop;

	if(count > 4)
	{
		uint8_t table_mode = 0;
		uint8_t index = 0;
		int16_t temperature_value = 0;
		int16_t offset_value = 0;

		table_mode = (uint8_t)atoi(args[2]);
		index = (uint8_t)atoi(args[3]);

		switch(table_mode)
		{
		case 0:  //only input temperature_value
			temperature_value = (uint16_t)atoi(args[4]);
			break;
		case 1:  //only input offset_value
			offset_value = (uint16_t)atoi(args[4]);
			break;
		case 2:  //input both value
			if(count > 5)
			{
				temperature_value = (uint16_t)atoi(args[4]);
				offset_value = (uint16_t)atoi(args[5]);
			}
			break;
		default:
			PRINTF("input_mode must between 0~2\n");
			break;
		}


		if (index < 0 || index >= 14)
		{
			PRINTF("index must between 0~14\n");
			return;
		}

		if(table_mode == 1 ||table_mode == 2)
		{
			if(offset_value < -15 || offset_value > 15)
			{
				PRINTF("offset_value must between (-15)~(15)\n");
				return;
			}
			TX_HIGH_LEVEL_TABLE[index][1] = offset_value;
			tef810x_info->tx_level_table[index][1] = TX_HIGH_LEVEL_TABLE[index][1];
		}

		if(table_mode == 0 ||table_mode == 2)
		{
			if(temperature_value < -40 || temperature_value > 135)
			{
				PRINTF("temperature_value must between (-40)~(135)\n");
				return;
			}
			TX_HIGH_LEVEL_TABLE[index][0] = temperature_value;
			tef810x_info->tx_level_table[index][0] = TX_HIGH_LEVEL_TABLE[index][0];
		}
	}
	else
	{
		PRINTF("tef table : [mode, index, temperature or offset] set or get temperature table\n");
	}

	PRINTF("\nTemp Table\n");
	for (loop = 0 ; loop < 14 ;loop++)
	{
		PRINTF("{%03d,%02d}, ", TX_HIGH_LEVEL_TABLE[loop][0], TX_HIGH_LEVEL_TABLE[loop][1]);
		if((loop+1) % 7 == 0)
			PRINTF("\n");
	}
}

static void find_tx_high_level_code_test(char** args, int count)
{
	uint8_t txNum, isSave, TxLeveValue;
	uint16_t txGain;

	if(count > 4)
	{
		txNum = (uint8_t)atoi(args[2]);
		txGain = (uint16_t)atoi(args[3]);
		isSave = (uint8_t)atoi(args[4]);

		if (txNum < 1 || txNum > 3)
		{
			PRINTF("Tx_Num must between 1-3\n");
			return;
		}

		if(txGain < 0 || txGain > 255)
		{
			PRINTF("Tx_Num must between 0-255\n");
			return;
		}
		TxLeveValue = find_tx_high_level_code(txNum, txGain);

		if(isSave == 1 && TxLeveValue != 0xFF)	//TxLeveValue must between 0-15.
		{
			tef810x_info->tx_level_code[txNum-1][0] = TxLeveValue;
			pars_set((pars_ctx_p)&tef810x_parameters);
		}
	}
	else
	{
		PRINTF("flevel invalid\n");
		PRINTF("tef flevel : [Tx_Num(1-3), Tx_Gain(0-255), IsSave(0/1)] find high level\n");
	}
}

static void callback_test(char** args, int count)
{
	uint8_t chgprofile, tx1gain, tx2gain, tx3gain;
	uint8_t rx1gain, rx2gain, rx3gain, rx4gain;
	uint16_t  effc_bandwith, setHPF, setLPF;

	if (count > 2)
	{
		if(!strcmp(args[2], "freq"))
		{
		    chgprofile    = (uint8_t)atoi(args[3]);
			effc_bandwith = (uint16_t)atoi(args[4]);
			chg_TEF810x_banwith_cb(chgprofile, effc_bandwith);
		}
		else if(!strcmp(args[2], "filter"))
		{
		    chgprofile = (uint8_t)atoi(args[3]);
			setHPF     = (uint16_t)atoi(args[4]);
			setLPF     = (uint16_t)atoi(args[5]);
			chg_tef810x_filter_cb(chgprofile, setHPF, setLPF);
		}
		else if(!strcmp(args[2], "txgain"))
		{
		    chgprofile  = (uint8_t)atoi(args[3]);
			tx1gain     = (uint8_t)atoi(args[4]);
			tx2gain     = (uint8_t)atoi(args[5]);
			tx3gain     = (uint8_t)atoi(args[6]);
			chg_tef810x_txgain_cb(chgprofile, tx1gain, tx2gain, tx3gain);
		}
		else if (!strcmp(args[2], "rxgain"))
		{
		    chgprofile  = (uint8_t)atoi(args[3]);
			rx1gain     = (uint8_t)atoi(args[4]);
			rx2gain     = (uint8_t)atoi(args[5]);
			rx3gain     = (uint8_t)atoi(args[6]);
			rx4gain     = (uint8_t)atoi(args[7]);
			chg_tef810x_rxgain_cb(chgprofile, rx1gain, rx2gain, rx3gain, rx4gain);
		}
		else if(!strcmp(args[2], "save"))
			TEF810x_save_cb();
		else if(!strcmp(args[2], "init"))
			re_init_TEF810x_cb(1);
	}
}

void chg_TEF810x_banwith_cb(uint8_t chgprofile, uint16_t effc_bandwith)
{
	if(chgprofile == 0)
		tef810x_info->profile1_config[1] = effc_bandwith;
	else if(chgprofile == 1)
		tef810x_info->profile2_config[1] = effc_bandwith;
	else if(chgprofile == 2)
		tef810x_info->profile3_config[1] = effc_bandwith;
	else
		tef810x_info->profile4_config[1] = effc_bandwith;

	rf_config[chgprofile].bandwidth    = (double)effc_bandwith * 1000000;

	if (effc_bandwith >= 1000)
		dolphin_flag.narrowband = false;
	else
		dolphin_flag.narrowband = true;

	tef810x_info->narrow_band = dolphin_flag.narrowband;
	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("effc_bandwith = %f\n", rf_config[chgprofile].bandwidth);
	PRINTF("narrowBand = %d\n", dolphin_flag.narrowband);
}

void chg_tef810x_filter_cb(uint8_t chgprofile, uint16_t setHPF, uint16_t setLPF)
{
	if(chgprofile == 0)
	{
		tef810x_info->profile1_config[4] = setHPF;
		tef810x_info->profile1_config[5] = setLPF;
	}
	else if(chgprofile == 1)
	{
		tef810x_info->profile2_config[4] = setHPF;
		tef810x_info->profile2_config[5] = setLPF;
	}
	else if(chgprofile == 2)
	{
		tef810x_info->profile3_config[4] = setHPF;
		tef810x_info->profile3_config[5] = setLPF;
	}
	else
	{
		tef810x_info->profile4_config[4] = setHPF;
		tef810x_info->profile4_config[5] = setLPF;
	}
	rf_config[chgprofile].hpf = (double)setHPF * 1000;
	rf_config[chgprofile].lpf = (double)setLPF * 1000000;

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("HPF = %f\n", rf_config[chgprofile].hpf);
	PRINTF("LPF = %f\n", rf_config[chgprofile].lpf);	
}

void chg_tef810x_txgain_cb(uint8_t chgprofile, uint8_t tx1gain, uint8_t tx2gain, uint8_t tx3gain)
{
	tx_gain[chgprofile][0]               = tx1gain;
	tef810x_info->tx_gain[chgprofile][0] = tx_gain[chgprofile][0];

	tx_gain[chgprofile][1]               = tx2gain;
	tef810x_info->tx_gain[chgprofile][1] = tx_gain[chgprofile][1];

	tx_gain[chgprofile][2]               = tx3gain;
	tef810x_info->tx_gain[chgprofile][2] = tx_gain[chgprofile][2];

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("TX gain= {%d,%d,%d}\n", tx_gain[chgprofile][0], tx_gain[chgprofile][1], tx_gain[chgprofile][2]);
}

void chg_tef810x_rxgain_cb(uint8_t chgprofile, uint8_t rx1gain, uint8_t rx2gain, uint8_t rx3gain, uint8_t rx4gain)
{
	rx_gain[chgprofile][0]				 = rx1gain;
	tef810x_info->rx_gain[chgprofile][0] = rx_gain[chgprofile][0];

	rx_gain[chgprofile][1]				 = rx2gain;
	tef810x_info->rx_gain[chgprofile][1] = rx_gain[chgprofile][1];

	rx_gain[chgprofile][2]				 = rx3gain;
	tef810x_info->rx_gain[chgprofile][2] = rx_gain[chgprofile][2];

	rx_gain[chgprofile][3]				 = rx4gain;
	tef810x_info->rx_gain[chgprofile][3] = rx_gain[chgprofile][3];

	PRINTF("change profile= %x\n", chgprofile);
	PRINTF("RX gain= {%d,%d,%d,%d}\n", rx_gain[chgprofile][0], rx_gain[chgprofile][1], rx_gain[chgprofile][2], rx_gain[chgprofile][3]);
}

void TEF810x_save_cb()
{
	TEF810x_save();
}

void re_init_TEF810x_cb(uint8_t default_disable)
{
	dolphin_flag.re_init_flag = default_disable;
	init_TEF810x();
}
/******************************************************************************
Function Name : check ISM adc status
******************************************************************************/
/*static void check_adc_status(void)
{
	uint32_t get_adc_flag;

	glue_reg_WriteCheck(ISM_MODULE_ADDRESS,NXP_TEF810X_MOD18_ADC_ERROR_FLAG_MASKED_STATUS_U16, &get_adc_flag, NULL);
	//PRINTF("get_adc_flag = 0x%lx\n", get_adc_flag);
    if((get_adc_flag & 0x7FFFFFF0) != 0)
    {
    	PRINTF("[Tef810x]: ADC error and error status = %lx\n", get_adc_flag);
    }
}*/

static void error_inject_test(char** args, int count){

	if(count > 2){
		if(!strcmp(args[2], "set")){
			uint8_t msgId, msgSta;
			uint8_t force = 0;
			uint8_t index = 0xFF;

			if(count > 4){
				msgId = (uint8_t)atoi(args[3]);
				msgSta = (uint8_t)atoi(args[4]) & 0x01;
				if(count > 5)
					force = (uint8_t)atoi(args[5]);

				switch(msgId){
				case MONITOR_ID_MCLK:
					index = 0;
					break;
				case MONITOR_ID_RF_ISM:
					index = 1;
					break;
				default:
					PRINTF("error message id unknow.\n");
					return;
				}

				if(msgSta){
					error_inject_table[index][1] = MONITOR_RESULT_FAILED;
					error_inject_table[index][2] = MONITOR_RESULT_CODE_ERROR;
				}
				else{
					error_inject_table[index][1] = MONITOR_RESULT_PASSED;
					error_inject_table[index][2] = MONITOR_RESULT_CODE_PASSED;
				}

				PRINTF("update Id:%d, msgSta:%d (Res:%d, ResCode:%d)\n", msgId, msgSta, error_inject_table[index][1], error_inject_table[index][2]);

				if(force){
					PRINTF("send force...\n");
					set_monitoring_result_by_id(error_inject_table[0][0], error_inject_table[0][1], error_inject_table[0][2]);
					set_monitoring_result_by_id(error_inject_table[1][0], error_inject_table[1][1], error_inject_table[1][2]);
				}
			}
		}
		else if(!strcmp(args[2], "dbg")){
			if(count > 3){
				error_inject = (uint8_t)atoi(args[3]) & 0x01;
			}
			PRINTF("tef810x error_inject: %d\n", error_inject);
		}
	}
	else{
		PRINTF("tef810x error inject\n");
		PRINTF("  set [errorId(%d-MCLK/%d-RF_ISM), errprSta(0-pass/1-failed), force(0/1)]\n", MONITOR_ID_MCLK, MONITOR_ID_RF_ISM);
		PRINTF("  dbg [injectError(0-normal/1-inject)]\n");
	}
}

static DolphinIC_rval_t hal_es3_OTP_GetChipInfo_Cubtek(TEF810xDieId_t *pChipInfo)
{
	///* DECLARE LOCAL VARIABLES HERE *///
	HAL_GERRCODE_INIT;

	if (g_OTPShadowLUT_ES3[5] == 0x1234ABCD)
	{
		DbgInfo("Chip OTP is not valid, cannot tell which mask version it is!");
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_INVALIDOTP);
	}
	else
	{
		//getting info from OTP reg 0x200
		pChipInfo->Chip_Version = (g_OTPShadowLUT_ES3[0] & 0x001F0000) >> 16;
		//getting info from OTP reg 0x208 & 0x20C
		pChipInfo->LOT_ID[0] = ((g_OTPShadowLUT_ES3[2] & 0xFC000000) >> 26) + 0x30;
		pChipInfo->LOT_ID[1] = ((g_OTPShadowLUT_ES3[2] & 0x03F00000) >> 20) + 0x30;
		pChipInfo->LOT_ID[2] = ((g_OTPShadowLUT_ES3[2] & 0x000FC000) >> 14) + 0x30;
		pChipInfo->LOT_ID[3] = ((g_OTPShadowLUT_ES3[2] & 0x00003F00) >> 8) + 0x30;
		pChipInfo->LOT_ID[4] = ((g_OTPShadowLUT_ES3[2] & 0x000000FC) >> 2) + 0x30;
		pChipInfo->LOT_ID[5] = ((g_OTPShadowLUT_ES3[2] & 0x00000003) |
				(g_OTPShadowLUT_ES3[3] & 0xF0000000) >> 28) + 0x30;
		pChipInfo->LOT_ID[6] = ((g_OTPShadowLUT_ES3[3] & 0x0FC00000) >> 22) + 0x30;
		pChipInfo->LOT_ID[7] = ((g_OTPShadowLUT_ES3[3] & 0x003F0000) >> 16) + 0x30;
		//getting info from OTP reg 0x210
		pChipInfo->maskVersion = (g_OTPShadowLUT_ES3[4] & 0x3C000000) >> 26;
		pChipInfo->Die_x = (g_OTPShadowLUT_ES3[4] & 0x03FC0000) >> 18;
		pChipInfo->Die_y = (g_OTPShadowLUT_ES3[4] & 0x0003FC00) >> 10;
		pChipInfo->Die_number = (g_OTPShadowLUT_ES3[4] & 0x000003FC) >> 2;
		//getting info from OTP reg 0x214
		pChipInfo->tpMinor_ft = (g_OTPShadowLUT_ES3[5] & 0x0000FE00) >> 9;
		pChipInfo->tpMajor_ft = (g_OTPShadowLUT_ES3[5] & 0x000001FC) >> 2;
		pChipInfo->tpMajor_wt = (g_OTPShadowLUT_ES3[5] & 0x01FC0000) >> 18;
		pChipInfo->tpMinor_wt = (g_OTPShadowLUT_ES3[5] & 0xFE000000) >> 25;
		//getting info from OTP reg 0x20C
		pChipInfo->wtDay = (g_OTPShadowLUT_ES3[3] & 0x0000F800) >> 11;
		pChipInfo->wtMonth = (g_OTPShadowLUT_ES3[3] & 0x00000780) >> 7;
		pChipInfo->wtYear = (g_OTPShadowLUT_ES3[3] & 0x0000007C) >> 2;

		return HAL_GERRCODE;
	}
}

static void tef810x_chip_info(void)
{
	DolphinIC_rval_t error_code = DOLPHINIC_NOERROR;
	TEF810xDieId_t DieInfo;

	error_code = hal_es3_OTP_GetChipInfo_Cubtek(&DieInfo);
	if(error_code != DOLPHINIC_NOERROR){
		PRINTF("GetChipInfo failed(code:%ld)\n", error_code);
		return;
	}

	PRINTF("ChipName: TEF810%d\n", DieInfo.Chip_Version);
	PRINTF("LOT ID: %c%c%c%c%c%c%c%c\n", DieInfo.LOT_ID[0], DieInfo.LOT_ID[1] \
			, DieInfo.LOT_ID[2], DieInfo.LOT_ID[3] \
			, DieInfo.LOT_ID[4], DieInfo.LOT_ID[5] \
			, DieInfo.LOT_ID[6], DieInfo.LOT_ID[7]);
	PRINTF("Wafer_x: %d\n", DieInfo.Die_x);
	PRINTF("Wafer_y: %d\n", DieInfo.Die_y);
	PRINTF("Wafer_Num: %d\n", DieInfo.Die_number);
	PRINTF("ES%x - TestProgram_FT V%d.%d \n", DieInfo.maskVersion, DieInfo.tpMajor_ft , DieInfo.tpMinor_ft);
	PRINTF("ES%x - TestProgram_WT V%d.%d \n", DieInfo.maskVersion, DieInfo.tpMajor_wt, DieInfo.tpMinor_wt );
	PRINTF("WaferTest %.2d/%.2d/20%.2d \n", DieInfo.wtDay, DieInfo.wtMonth, DieInfo.wtYear);
}

tef810x_status_t rmtp_get_tef810x_chip_info(TEF810xDieId_t* DieInfo)
{
	if(DieInfo == NULL || (hal_es3_OTP_GetChipInfo_Cubtek(DieInfo) != DOLPHINIC_NOERROR))
	{
		return TEF810X_FAIL;
	}
	return TEF810X_OK;
}

static bool_t tef810x_self_test(DolphinIC_rval_t* error_code, uint32_t size)
{
	bool_t selftest_notok_flag = FALSE;
	if(error_code == NULL || size < END_OF_MESSAGE * sizeof(DolphinIC_rval_t))
		return TRUE;

	MIPICSI2.PHYC.B.PDRX = 1;                                       // power-down receiver
	MIPICSI2.RXEN.R = 0;                                              // Diable RX

	memset(error_code, 0, END_OF_MESSAGE * sizeof(DolphinIC_rval_t));
	PRINTF("SelfTest Start\n");

	re_init_TEF810x_cb(0);  //reset and Initial TEF810x.
	hal_ES3_CSI2_Datatoggle_Disable();  //disable CSI-2 data output.

	PRINTF("MCLK integrity check...");
	error_code[MCLK_CHECK_FAIL] = chip_FS_IntegrityCheckMClk(0x1, 480.0);
	if (error_code[MCLK_CHECK_FAIL] != DOLPHINIC_NOERROR){
		PRINTF(" failed!\n");
	}
	else
		PRINTF(" passed!\n");

	for(uint8_t profile = 0; profile < PROFILE_NUM; profile++)
	{
		if(txsw[profile][0] + txsw[profile][1] + txsw[profile][2])
			PRINTF("TX %d integrity check...", profile);
		else
			continue;
		error_code[NORMAL_TX_P0_CHECK_FAIL + profile] = chip_ISM_SWTXFit(profile);
		if (error_code[NORMAL_TX_P0_CHECK_FAIL + profile] != DOLPHINIC_NOERROR){
			selftest_notok_flag = TRUE;
			PRINTF(" failed(%ld)!\n", error_code[NORMAL_TX_P0_CHECK_FAIL + profile]);
		}
		else
			PRINTF(" passed!\n");
	}

	for(uint8_t profile = 0; profile < PROFILE_NUM; profile++)
	{
		PRINTF("Chirp %d integrity check...", profile);
		error_code[NORMAL_CHIRP_P0_CHECK_FAIL + profile] = chip_ISM_SWChirpFit(profile);
		if (error_code[NORMAL_CHIRP_P0_CHECK_FAIL + profile] != DOLPHINIC_NOERROR){
			selftest_notok_flag = TRUE;
			PRINTF(" failed(%ld)!\n", error_code[NORMAL_CHIRP_P0_CHECK_FAIL + profile]);
		}
		else
			PRINTF(" passed!\n");
	}

	uint32_t ism_master_meeage[3] = {0};
	error_code[NORMAL_SEND_CHIRP_CHECK_FAIL] = normal_send_test(ism_master_meeage, sizeof(ism_master_meeage)/sizeof(uint32_t));
	PRINTF("Normal ChirpSequence Test...");
	if (error_code[NORMAL_SEND_CHIRP_CHECK_FAIL] != DOLPHINIC_NOERROR){
		selftest_notok_flag = TRUE;
		PRINTF(" failed(%ld)!\n", error_code[NORMAL_SEND_CHIRP_CHECK_FAIL]);
	}
	else
		PRINTF(" passed!\n");

	error_code[NORMAL_SEND_CHIRP_SHORT_MSG] = ism_master_meeage[0];
	error_code[NORMAL_SEND_CHIRP_LONG_MSG] = ism_master_meeage[1];
	error_code[NORMAL_SEND_CHIRP_P3_MSG] = ism_master_meeage[2];

	uint16_t bandwidth_test[BANDWIDTH_TEST_NUM] = { 100, 200, 400, 600, 1000, 1100};

	for(uint8_t index = 0; index < BANDWIDTH_TEST_NUM; index++)
	{
		bool_t chirp_is_ok = TRUE;
		DolphinIC_rval_t error_msg;
		chg_TEF810x_banwith_cb(0, bandwidth_test[index]);  //change Profile-0 bandwidth.
		chg_TEF810x_banwith_cb(1, bandwidth_test[index]);  //change Profile-1 bandwidth.
		chg_TEF810x_banwith_cb(2, bandwidth_test[index]);  //change Profile-2 bandwidth.
		chg_TEF810x_banwith_cb(3, bandwidth_test[index]);  //change Profile-3 bandwidth.
		re_init_TEF810x_cb(1);                             //reset and Initial TEF810x.
		hal_ES3_CSI2_Datatoggle_Disable();                 //disable CSI-2 data output.

		for(uint8_t profile = 0; profile < PROFILE_NUM; profile++)
		{
			DolphinIC_rval_t temp_msg;
			PRINTF("Chirp %d integrity check...", profile);
			temp_msg = chip_ISM_SWChirpFit(profile);
			if(temp_msg != DOLPHINIC_NOERROR){
				chirp_is_ok = FALSE;
				error_msg = temp_msg;
				PRINTF(" failed(%ld)!\n", temp_msg);
			}
			else
				PRINTF(" passed!\n");
		}

		if(chirp_is_ok){
			error_code[_100M_BANDWIDTH_CHIRP_CHECK_FAIL + index*2] = DOLPHINIC_NOERROR;
			error_code[_100M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL + index*2] = normal_send_test(NULL, 0);
			PRINTF("Send ChirpSequence Test...");
			if (error_code[_100M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL + index*2] != DOLPHINIC_NOERROR){
				selftest_notok_flag = TRUE;
				PRINTF(" failed(%ld)!\n", error_code[_100M_BANDWIDTH_SEND_CHIRP_CHECK_FAIL + index*2]);
			}
			else
				PRINTF(" passed!\n");
		}else{
			selftest_notok_flag = TRUE;
			error_code[_100M_BANDWIDTH_CHIRP_CHECK_FAIL + index*2] = error_msg;
		}
	}

	re_init_TEF810x_cb(0);  //reset and Initial TEF810x.
	hal_ES3_CSI2_Datatoggle_Enable();                                 // enable CSI-2 data output.
	MIPICSI2.PHYC.B.PDRX = 0;                                         // power-up receiver
	MIPICSI2.RXEN.R = 1;                                              // enable RX

	return selftest_notok_flag;
}

tef810x_status_t rmtp_rf_selftest(uint32_t* data, uint32_t size, bool_t* selftest_result)
{
	if(data == NULL || selftest_result == NULL || size < END_OF_MESSAGE * sizeof(DolphinIC_rval_t))
		return TEF810X_FAIL;

	*selftest_result = tef810x_self_test((DolphinIC_rval_t*)data, size);
	return TEF810X_OK;
}

static DolphinIC_rval_t normal_send_test(uint32_t* ism_message, uint8_t size)
{
	///* DECLARE LOCAL VARIABLES HERE *///
	HAL_GERRCODE_INIT;

	hal_ES3_CSI2_Datatoggle_Disable();  //disable CSI-2 data output.

	Nxp_Tef810x_Mod18_MasterErrorFlagMaskedStatusUnion_t master_error_status;
	Nxp_Tef810x_Mod18_RfPowerDownErrorFlagMaskedStatusUnion_t rf_power_down_error_status;
	Nxp_Tef810x_Mod18_IsmErrorStatusAndMcuResetUnion_t ISM_error_status_and_mcu_reset_status;

	send_chirp(2, 256, 1);  //send short profile for test.
	chip_reg_Read(ISM_MODULE, master_error_flag_masked_status, &master_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, rf_power_down_error_flag_masked_status, &rf_power_down_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, ISM_error_status_and_mcu_reset, &ISM_error_status_and_mcu_reset_status.val_u32, NULL);
	if(master_error_status.val_u32 || rf_power_down_error_status.val_u32 || ISM_error_status_and_mcu_reset_status.val_u32){
		if(ism_message && size >= 3)
			ism_message[0] = master_error_status.val_u32;
		HAL_GEC_FUNEXIT(DOLPHINIC_SEND_PROFILE2_TEST_FAIL);
	}

	send_chirp(4, 256, 1);  //send long profile for test.
	chip_reg_Read(ISM_MODULE, master_error_flag_masked_status, &master_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, rf_power_down_error_flag_masked_status, &rf_power_down_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, ISM_error_status_and_mcu_reset, &ISM_error_status_and_mcu_reset_status.val_u32, NULL);
	if(master_error_status.val_u32 || rf_power_down_error_status.val_u32 || ISM_error_status_and_mcu_reset_status.val_u32){
		if(ism_message && size >= 3)
			ism_message[1] = master_error_status.val_u32;
		HAL_GEC_FUNEXIT(DOLPHINIC_SEND_PROFILE01_TEST_FAIL);
	}

	send_chirp(3, 256, 1);  //send detect profile for test.
	chip_reg_Read(ISM_MODULE, master_error_flag_masked_status, &master_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, rf_power_down_error_flag_masked_status, &rf_power_down_error_status.val_u32, NULL);
	chip_reg_Read(ISM_MODULE, ISM_error_status_and_mcu_reset, &ISM_error_status_and_mcu_reset_status.val_u32, NULL);
	if(master_error_status.val_u32 || rf_power_down_error_status.val_u32 || ISM_error_status_and_mcu_reset_status.val_u32){
		if(ism_message && size >= 3)
			ism_message[2] = master_error_status.val_u32;
		HAL_GEC_FUNEXIT(DOLPHINIC_SEND_PROFILE3_TEST_FAIL);
	}

	return HAL_GERRCODE;
}

static void update_tef810x_status(uint8_t msgId, uint8_t msgSta, uint8_t msgStaCode){
	uint8_t index = 0xFF;
	switch(msgId){
	case MONITOR_ID_MCLK:
		index = 0;
		break;
	case MONITOR_ID_RF_ISM:
		index = 1;
		break;
	default:
		return;
	}
	error_table[index][0] = msgId;
	error_table[index][1] = msgSta;
	error_table[index][2] = msgStaCode;

	if(error_inject){
		set_monitoring_result_by_id(error_inject_table[0][0], error_inject_table[0][1], error_inject_table[0][2]);
		set_monitoring_result_by_id(error_inject_table[1][0], error_inject_table[1][1], error_inject_table[1][2]);
	}
	else{
		set_monitoring_result_by_id(error_table[0][0], error_table[0][1], error_table[0][2]);
		set_monitoring_result_by_id(error_table[1][0], error_table[1][1], error_table[1][2]);
	}
}
