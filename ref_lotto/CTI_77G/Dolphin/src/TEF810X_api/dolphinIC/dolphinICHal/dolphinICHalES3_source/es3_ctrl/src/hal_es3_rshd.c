/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016                                                   */
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
/* NXP reserves the right to make changes without notice at any time.           */
/* NXP makes no warranty, expressed, implied or statutory, including but        */
/* not limited to any implied warranty of merchantability or fitness for any    */
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage        */
/* arising from its use.                                                        */
/*------------------------------------------------------------------------------*/

/**
*
* @file hal_es3_rshd.c
*
* @ver v5.3.0  
*
* @author
*
* @date 04/02/2016
*
* @brief Device Register Shadow implementation.
*
*
******************************************************************************/

#include <math.h>
#include <stdbool.h>
#include <dbgprintf.h>
#include <dolphin_cfg.h>
#include <dolphin_errcodes.h>
#include <stdlib.h>
#ifdef DOLPHIN_CFG_ES3

#include "hal_es3.h"

#include <es3/NXP_TEF810X_CentralControl.h>
#include <es3/NXP_TEF810X_LvdsTx.h>
#include <es3/NXP_TEF810X_Csi2.h>
#include <es3/NXP_TEF810X_Cif.h>
#include <es3/NXP_TEF810X_TimingEngine.h>
#include <es3/NXP_TEF810X_SweepControl.h>
#include <es3/NXP_TEF810X_ChirpAfc.h>
#include <es3/NXP_TEF810X_Adc.h>
#include <es3/NXP_TEF810X_GlobalBias.h>
#include <es3/NXP_TEF810X_LoInterface.h>
#include <es3/NXP_TEF810X_MasterClock.h>
#include <es3/NXP_TEF810X_Rx.h>
#include <es3/NXP_TEF810X_Tx.h>
#include <es3/NXP_TEF810X_Ssbmod.h>
#include <es3/NXP_TEF810X_GlobalLdo.h>
#include <es3/NXP_TEF810X_Atb.h>
#include <es3/NXP_TEF810X_Ism.h>
#include <es3/NXP_TEF810X_LvdsTx.h>
#include <es3/NXP_TEF810X_Otp.h>

#include <hal_es3_rshd.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define ES3_MODULE_MAX 0x19
#define MAX_BURST_CHUNK 250				//Limitations by current FPGA driver, can only read ~250 words at a time

static uint32_t g_scratchbuff[2 * 1024];
//static uint32_t g_scratchbuff_debug[2 * 1024];	//Added for internal debugging

#if (DOLPHIN_CFG_FSM_RSHD_CCTRL)
#include <es3/NXP_TEF810X_CentralControl.h>
static Nxp_Tef810x_Mod00_CentralControlRegister_t g_cctrlregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_CCTRL

#if (DOLPHIN_CFG_FSM_RSHD_LVDS)
#include <es3/NXP_TEF810X_LvdsTx.h>
static Nxp_Tef810x_Mod01_LvdsTxRegister_t g_lvdsregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_LVDS

#if (DOLPHIN_CFG_FSM_RSHD_CSI2)
#include <es3/NXP_TEF810X_Csi2.h>
static Nxp_Tef810x_Mod02_Csi2Register_t g_csi2regpg;
#endif //DOLPHIN_CFG_FSM_RSHD_CSI2

#if (DOLPHIN_CFG_FSM_RSHD_CIF)
#include <es3/NXP_TEF810X_Cif.h>
static Nxp_Tef810x_Mod03_CifRegister_t g_cifregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_CIF

#if (DOLPHIN_CFG_FSM_RSHD_TENG)
#include <es3/NXP_TEF810X_TimingEngine.h>
static Nxp_Tef810x_Mod04_TimingEngineRegister_t g_tengregpg;
static uint16_t teng_reg_ignorelist[] = { NXP_TEF810X_MOD04_CHIRP_TRIGGER_MODE_CONTROL_U16 };
#endif //DOLPHIN_CFG_FSM_RSHD_TENG

#if (DOLPHIN_CFG_FSM_RSHD_SCTRL)
#include <es3/NXP_TEF810X_SweepControl.h>
static Nxp_Tef810x_Mod05_SweepControlRegister_t g_sctrlregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_SCTRL


#if (DOLPHIN_CFG_FSM_RSHD_CAFC)
#include <es3/NXP_TEF810X_ChirpAfc.h>
static Nxp_Tef810x_Mod06_ChirpAfcRegister_t g_cafcregpg;
static uint16_t cafc_reg_ignorelist[] = { NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16, \
NXP_TEF810X_MOD06_TEST_ERROR_FLAG_STATUS_U16, \
NXP_TEF810X_MOD06_LPF_VTUNE_VCO_STATUS_U16,\
NXP_TEF810X_MOD06_DIVIDE_FREQ_COUNTER_READ_VALUE_U16,\
NXP_TEF810X_MOD06_REF_COUNTER_READ_VALUE_U16,\
NXP_TEF810X_MOD06_TEST_ERROR_FLAG_STATUS_U16,\
NXP_TEF810X_MOD06_BIAS_BLOCK_REGISTER_U16 };
#endif //DOLPHIN_CFG_FSM_RSHD_CAFC

#if (DOLPHIN_CFG_FSM_RSHD_ADC)
#include <es3/NXP_TEF810X_Adc.h>
static Nxp_Tef810x_Mod07_AdcRegister_t g_adc12regpg;
static Nxp_Tef810x_Mod07_AdcRegister_t g_adc34regpg;
#endif //DOLPHIN_CFG_FSM_RSHD_ADC

#if (DOLPHIN_CFG_FSM_RSHD_GBIAS)
#include <es3/NXP_TEF810X_GlobalBias.h>
static Nxp_Tef810x_Mod09_GlobalBiasRegister_t g_gbiasregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_GBIAS

#if (DOLPHIN_CFG_FSM_RSHD_LOINTF)
#include <es3/NXP_TEF810X_LoInterface.h>
static Nxp_Tef810x_Mod0A_LoInterfaceRegister_t g_loiregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_LOINTF

#if (DOLPHIN_CFG_FSM_RSHD_MCLK)
#include <es3/NXP_TEF810X_MasterClock.h>
static Nxp_Tef810x_Mod0C_MasterClockRegister_t g_mclkregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_MCLK

#if (DOLPHIN_CFG_FSM_RSHD_RX)
#include <es3/NXP_TEF810X_Rx.h>
static Nxp_Tef810x_Mod0D_RxRegister_t g_rx1regpg;
static Nxp_Tef810x_Mod0D_RxRegister_t g_rx2regpg;
static Nxp_Tef810x_Mod0D_RxRegister_t g_rx3regpg;
static Nxp_Tef810x_Mod0D_RxRegister_t g_rx4regpg;
#endif //DOLPHIN_CFG_FSM_RSHD_RX

#if (DOLPHIN_CFG_FSM_RSHD_TX)
#include <es3/NXP_TEF810X_Tx.h>
static Nxp_Tef810x_Mod11_TxRegister_t g_tx1regpg;
static Nxp_Tef810x_Mod11_TxRegister_t g_tx2regpg;
static Nxp_Tef810x_Mod11_TxRegister_t g_tx3regpg;
#endif //DOLPHIN_CFG_FSM_RSHD_TX

#if (DOLPHIN_CFG_FSM_RSHD_SSBMOD)
#include <es3/NXP_TEF810X_Ssbmod.h>
static Nxp_Tef810x_Mod14_SsbmodRegister_t g_ssbmodregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_SSBMOD


#if (DOLPHIN_CFG_FSM_RSHD_GLDO)
#include <es3/NXP_TEF810X_GlobalLdo.h>
static Nxp_Tef810x_Mod15_GlobalLdoRegister_t g_gldoregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_GLDO

#if (DOLPHIN_CFG_FSM_RSHD_ATB)
#include <es3/NXP_TEF810X_Atb.h>
static Nxp_Tef810x_Mod16_AtbRegister_t g_atbregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_GLDO

#if (DOLPHIN_CFG_FSM_RSHD_OTP)
#include <es3/NXP_TEF810X_Otp.h>
static Nxp_Tef810x_Mod17_OtpRegister_t g_otpregpg;
#endif //DOLPHIN_CFG_FSM_RSHD_OTP

#if (DOLPHIN_CFG_FSM_RSHD_ISM)
#include <es3/NXP_TEF810X_Ism.h>
static Nxp_Tef810x_Mod18_IsmRegister_t g_ismregpg;
static uint16_t ism_reg_ignorelist[] = { NXP_TEF810X_MOD18_FTTI_WDT_RD_VALUE_U16, NXP_TEF810X_MOD18_STATUS_WDT_RD_VALUE_U16};
#endif //DOLPHIN_CFG_FSM_RSHD_ISM

typedef struct hal_es3_rshd_ctrlstruct_t
{
	bool      rshd_enable;
	uint32_t *rshd_page;
	uint32_t  n_regs;
	uint16_t * reg_ign_list;
	uint16_t   n_reg_ign;
}hal_es3_rshd_CtrlStruct_t;

static hal_es3_rshd_CtrlStruct_t g_InstCtrl[ES3_MODULE_MAX];

void hal_es3_rshd_Init(void)
{

#if (DOLPHIN_CFG_FSM_RSHD_CCTRL)

	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_cctrlregpg;
	//g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].n_regs = (sizeof(Nxp_Tef810x_Mod00_CentralControlRegister_t) / sizeof(uint32_t));
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].n_regs = 0x28; //For performance improvement
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CENTRAL_CONTROL_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_CCTRL

#if (DOLPHIN_CFG_FSM_RSHD_LVDS)

	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_lvdsregpg;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod01_LvdsTxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[LVDS_TX_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_LVDS

#if (DOLPHIN_CFG_FSM_RSHD_CSI2)

	g_InstCtrl[CSI2_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[CSI2_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_csi2regpg;
	g_InstCtrl[CSI2_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod02_Csi2Register_t) / sizeof(uint32_t) );
	g_InstCtrl[CSI2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CSI2_MODULE_ADDRESS].n_reg_ign = 0x00;


#else

	g_InstCtrl[CSI2_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[CSI2_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[CSI2_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[CSI2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CSI2_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_CSI2

#if (DOLPHIN_CFG_FSM_RSHD_CIF)

	g_InstCtrl[CIF_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[CIF_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_cifregpg;
	g_InstCtrl[CIF_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod03_CifRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[CIF_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CIF_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[CIF_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[CIF_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[CIF_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[CIF_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CIF_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_CIF

#if (DOLPHIN_CFG_FSM_RSHD_TENG)

	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].rshd_page = (uint32_t *)&g_tengregpg;
	//g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].n_regs = (sizeof(Nxp_Tef810x_Mod04_TimingEngineRegister_t) / sizeof(uint32_t));
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].n_regs = 0x17; //For performance improvement
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].reg_ign_list = &teng_reg_ignorelist[0x00];
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].n_reg_ign = (sizeof(teng_reg_ignorelist) / sizeof(uint16_t));

#else

	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].rshd_page = (uint32_t *) NULL;
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TIMING_ENGINE_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_TENG

#if (DOLPHIN_CFG_FSM_RSHD_SCTRL)

	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].rshd_page = (uint32_t *)&g_sctrlregpg;
	//g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].n_regs = (sizeof(Nxp_Tef810x_Mod05_SweepControlRegister_t) / sizeof(uint32_t));
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].n_regs = 0x19; //For performance improvement
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].rshd_page = (uint32_t *) NULL;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[SWEEP_CONTROL_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_SCTRL

#if (DOLPHIN_CFG_FSM_RSHD_CAFC)

	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].rshd_page = (uint32_t *)&g_cafcregpg;
	//g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].n_regs = (sizeof(Nxp_Tef810x_Mod06_ChirpAfcRegister_t) / sizeof(uint32_t));
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].n_regs = 0x31; //For performance improvement
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].reg_ign_list = &cafc_reg_ignorelist[0x00];
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].n_reg_ign = (sizeof(cafc_reg_ignorelist) / sizeof(uint16_t));

#else

	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].rshd_page = (uint32_t *) NULL;
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[CHIRP_AFC_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_CAFC

#if (DOLPHIN_CFG_FSM_RSHD_ADC)

	g_InstCtrl[ADC12_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[ADC12_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_adc12regpg;
	g_InstCtrl[ADC12_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod07_AdcRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[ADC12_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ADC12_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[ADC34_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[ADC34_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_adc34regpg;
	g_InstCtrl[ADC34_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod07_AdcRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[ADC34_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ADC34_MODULE_ADDRESS].n_reg_ign = 0x00;


#else

	g_InstCtrl[ADC12_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[ADC12_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[ADC12_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[ADC12_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ADC12_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[ADC34_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[ADC34_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[ADC34_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[ADC34_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ADC34_MODULE_ADDRESS].n_reg_ign = 0x00;


#endif //DOLPHIN_CFG_FSM_RSHD_ADC

#if (DOLPHIN_CFG_FSM_RSHD_GBIAS)

	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_gbiasregpg;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod09_GlobalBiasRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[GLOBAL_BIAS_MODULE_ADDRESS].n_reg_ign = 0x00;


#endif //DOLPHIN_CFG_FSM_RSHD_GBIAS

#if (DOLPHIN_CFG_FSM_RSHD_LOINTF)

	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_loiregpg;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0A_LoInterfaceRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[LO_INTERFACE_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_LOINTF

#if (DOLPHIN_CFG_FSM_RSHD_MCLK)

	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_mclkregpg;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0C_MasterClockRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[MASTER_CLOCK_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_MCLK

#if (DOLPHIN_CFG_FSM_RSHD_RX)

	g_InstCtrl[RX1_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[RX1_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_rx1regpg;
	g_InstCtrl[RX1_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0D_RxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[RX1_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX1_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX2_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[RX2_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_rx2regpg;
	g_InstCtrl[RX2_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0D_RxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[RX2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX2_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX3_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[RX3_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_rx3regpg;
	g_InstCtrl[RX3_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0D_RxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[RX3_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX3_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX4_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[RX4_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_rx4regpg;
	g_InstCtrl[RX4_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod0D_RxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[RX4_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX4_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[RX1_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[RX1_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[RX1_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[RX1_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX1_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX2_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[RX2_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[RX2_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[RX2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX2_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX3_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[RX3_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[RX3_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[RX3_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX3_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[RX4_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[RX4_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[RX4_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[RX4_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[RX4_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_RX

#if (DOLPHIN_CFG_FSM_RSHD_TX)

	g_InstCtrl[TX1_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[TX1_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_tx1regpg;
	//g_InstCtrl[TX1_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod11_TxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[TX1_MODULE_ADDRESS].n_regs = 0x1A; //For performance improvement
	g_InstCtrl[TX1_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX1_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[TX2_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[TX2_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_tx2regpg;
	//g_InstCtrl[TX2_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod11_TxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[TX2_MODULE_ADDRESS].n_regs = 0x1A; //For performance improvement
	g_InstCtrl[TX2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX2_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[TX3_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[TX3_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_tx3regpg;
	//g_InstCtrl[TX3_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod11_TxRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[TX3_MODULE_ADDRESS].n_regs = 0x1A; //For performance improvement
	g_InstCtrl[TX3_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX3_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[TX1_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[TX1_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[TX1_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[TX1_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX1_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[TX2_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[TX2_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[TX2_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[TX2_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX2_MODULE_ADDRESS].n_reg_ign = 0x00;

	g_InstCtrl[TX3_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[TX3_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[TX3_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[TX3_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[TX3_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_TX

#if (DOLPHIN_CFG_FSM_RSHD_SSBMOD)

	g_InstCtrl[SSBMOD_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_ssbmodregpg;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod14_SsbmodRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[SSBMOD_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[SSBMOD_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_SSBMOD

#if (DOLPHIN_CFG_FSM_RSHD_GLDO)

	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_gldoregpg;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod15_GlobalLdoRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[GLOBAL_LDO_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_GLDO

#if (DOLPHIN_CFG_FSM_RSHD_ATB)

	g_InstCtrl[ATB_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[ATB_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_atbregpg;
	g_InstCtrl[ATB_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod16_AtbRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[ATB_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ATB_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[ATB_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[ATB_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[ATB_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[ATB_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ATB_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_ATB

#if (DOLPHIN_CFG_FSM_RSHD_OTP)

	g_InstCtrl[OTP_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[OTP_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_otpregpg;
	g_InstCtrl[OTP_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod17_OtpRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[OTP_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[OTP_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[OTP_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[OTP_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[OTP_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[OTP_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[OTP_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_OTP

#if (DOLPHIN_CFG_FSM_RSHD_ISM)

	g_InstCtrl[ISM_MODULE_ADDRESS].rshd_enable = true;
	g_InstCtrl[ISM_MODULE_ADDRESS].rshd_page = (uint32_t *) &g_ismregpg;
	//g_InstCtrl[ISM_MODULE_ADDRESS].n_regs = ( sizeof(Nxp_Tef810x_Mod18_IsmRegister_t) / sizeof(uint32_t) );
	g_InstCtrl[ISM_MODULE_ADDRESS].n_regs = 0x10; //For performance improvement
	g_InstCtrl[ISM_MODULE_ADDRESS].reg_ign_list = &ism_reg_ignorelist[0x0];
	g_InstCtrl[ISM_MODULE_ADDRESS].n_reg_ign = 0x00;

#else

	g_InstCtrl[ISM_MODULE_ADDRESS].rshd_enable = false;
	g_InstCtrl[ISM_MODULE_ADDRESS].rshd_page = (uint32_t *)NULL;
	g_InstCtrl[ISM_MODULE_ADDRESS].n_regs = 0x00;
	g_InstCtrl[ISM_MODULE_ADDRESS].reg_ign_list = NULL;
	g_InstCtrl[ISM_MODULE_ADDRESS].n_reg_ign = 0x00;

#endif //DOLPHIN_CFG_FSM_RSHD_ISM


}

void hal_es3_rshd_UpDateShadow(uint8_t moduleaddress, uint16_t regaddress, uint32_t writedata)
{

	if (moduleaddress < ES3_MODULE_MAX)
	{
		if ((g_InstCtrl[moduleaddress].rshd_enable == true) && \
			(g_InstCtrl[moduleaddress].rshd_page != NULL))
		{
			uint32_t pg_inx = (regaddress >> 2);

			if (pg_inx < g_InstCtrl[moduleaddress].n_regs)
			{
				if ((moduleaddress == 0x4) && (regaddress == 0x58)) writedata &= 0xFFFFFFFE; //Mask the chirp start autoclear bit 
				g_InstCtrl[moduleaddress].rshd_page[pg_inx] = writedata;
			}
		}
	}
}

//Note that the shadow checks have not been optimized and read the complete module, including the non declared registers.
DolphinIC_rval_t hal_es3_rshd_updateFromDev(uint8_t moduleaddress)
{
	HAL_GERRCODE_INIT;

	if (moduleaddress < ES3_MODULE_MAX)
	{
		if ((g_InstCtrl[moduleaddress].rshd_enable == true) && \
			(g_InstCtrl[moduleaddress].rshd_page != NULL))
		{
//			DolphinIC_rval_t glrval;
//			uint32_t pg_inx = 0x00;
			int readSize = 0;

			//Driver only accepts uint8_t as numbere of words, so to read more than that we need to loop

			for (int i = 0; i <= ((g_InstCtrl[moduleaddress].n_regs) / MAX_BURST_CHUNK); i++) {
				readSize = MIN(ABS(g_InstCtrl[moduleaddress].n_regs - (i * MAX_BURST_CHUNK)), MAX_BURST_CHUNK);
				if (readSize <= 0) break;
//				glrval = glue_reg_BurstRead(moduleaddress, i * MAX_BURST_CHUNK, &g_InstCtrl[moduleaddress].rshd_page[i * MAX_BURST_CHUNK],
//					readSize, false, NULL);
				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}

			DbgInfo("Reg shadow for mod:%x is updated!\n", moduleaddress);
		}
	}
	
	return HAL_GERRCODE;
}

DolphinIC_rval_t hal_es3_rshd_checkRegPage(uint8_t moduleaddress)
{
	bool rval = false;
	uint32_t ign_inx = 0x00;
	bool bregignore = false;
//	DolphinIC_rval_t glrval;
	uint32_t pg_inx;
	HAL_GERRCODE_INIT;



	if (moduleaddress < ES3_MODULE_MAX)
	{
		if ((g_InstCtrl[moduleaddress].rshd_enable == true) && \
			(g_InstCtrl[moduleaddress].rshd_page != NULL))
		{

			pg_inx = 0x00;

			//Driver only accepts uint8_t as numbere of words, so to read more than that we need to loop

//			uint32_t temp = 0x0;
//			uint32_t dummy = 0;
			int readSize = 0;
//			int error = 0;
			for (int i = 0; i <= ((g_InstCtrl[moduleaddress].n_regs) / MAX_BURST_CHUNK); i++) {
				readSize = MIN(ABS(g_InstCtrl[moduleaddress].n_regs - (i * MAX_BURST_CHUNK)), MAX_BURST_CHUNK);
				if (readSize <= 0) break;
//				glrval = glue_reg_BurstRead(moduleaddress, i * MAX_BURST_CHUNK, &g_scratchbuff[i * MAX_BURST_CHUNK],
//					readSize, false, NULL);

				HAL_GEC_ASSERT(DOLPHINIC_NOERROR);
			}
			
			for (pg_inx = 0x00; pg_inx < (g_InstCtrl[moduleaddress].n_regs); pg_inx++)
			{
				if (g_scratchbuff[pg_inx] != g_InstCtrl[moduleaddress].rshd_page[pg_inx])
				{
					bregignore = false;

					for (ign_inx = 0x00; ign_inx < g_InstCtrl[moduleaddress].n_reg_ign; ign_inx++)
					{
						if (g_InstCtrl[moduleaddress].reg_ign_list[ign_inx] == (pg_inx << 2))
						{
							bregignore = true;
							break;
						}
					}

					//In ISM registers ignore the parity bit as it can cause mismatch
					if (moduleaddress == 0x18) {
						if ((g_scratchbuff[pg_inx] & 0x7FFFFFF) == (g_InstCtrl[moduleaddress].rshd_page[pg_inx] & 0x7FFFFFF)) bregignore = true;
					}

					if (bregignore == false)
					{
						DbgInfo("Mod(0x%x) Reg-Pg-Chk failed at Index(%d) \n", moduleaddress, pg_inx);
						DbgInfo("Add(0x%x) Expc(0x%x) Act(0x%x) \n", (pg_inx << 2), g_InstCtrl[moduleaddress].rshd_page[pg_inx], g_scratchbuff[pg_inx]);
						break;
					}
				}
			}

			if (pg_inx == (g_InstCtrl[moduleaddress].n_regs))
			{
				rval = true;
			}
		}
	}

	if (rval == true)
		return HAL_GERRCODE;
	else
		HAL_GEC_FUNEXIT(DOLPHINIC_EC_SHDWREGCHECKFAIL);
}

#endif //DOLPHIN_CFG_ES3
