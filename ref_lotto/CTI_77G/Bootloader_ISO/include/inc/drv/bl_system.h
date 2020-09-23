/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the system module for MPC5744P.
 *
 *  \file       bl_system.h
 *  \ingroup    driver_module
 *  \author     jun.li <jun.li3@hirain.com>
 *
 *  \version    1.0.0
 *  \date       16/08/2016
 *
 *  \par        Changelist 
 *      Version    | Date       | Authors          | CR# | Descriptions
 *      --------   | ---------- | ---------------- | --- | -------------
 *      01.00.00   | 12/08/2016 | jun.li           | N/A | BootDrv010001
 *
 *****************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "bl_typedefs.h"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define SYS_OSC_CLOCK_FREQ      (40000)
#define SYS_ENTRY_POINT         (0x00FB0004UL)

// CLK sources for the CLK_OUT pins
#define IRCOSC_SEL 				0x0
#define XOSC_SEL 				0x1
#define PLL0_SEL 				0x2
#define SDPLL160_SEL 			0x3
#define PLL1_SEL 				0x4
#define NAP_NAL_SEL 			0x5
#define OSC_SEL 				0x6
#define CTE_SEL 				0x8
#define SDPLL320_SEL 			0xA
#define SDPLL80_SEL 			0xB
#define DEFAULT_MC_ME_MODE		0x85FF

typedef enum clock_mode {
	IRC_MODE,           // Internal RC oscillator for startup
    XOSC_MODE,          // External crystal for startup
    XOSC_CRYSTAL_MODE,
    XOSC_DIFF_BYP_MODE,
    XOSC_SE_BYPASS
}clock_mode_type;

typedef enum system_clock {
    CLOCK_IRC,
    CLOCK_XOSC,
    CLOCK_PLL0,
    CLOCK_SDPLL_DIV_2,
    CLOCK_PLL1
}system_clock_e;

/*****************************************************************************
Internal Type Definitions
 *****************************************************************************/

#if  (SYS_OSC_CLOCK_FREQ == 8000)
#define PLLDIG_DV_PREDIV      1U
#define PLLDIG_DV_MFD       25U
#define PLLDIG_DV_RFDPHI   1U
#define CGM_SC_DC_DIV        3U
#elif  (SYS_OSC_CLOCK_FREQ == 12000)
#define PLLDIG_DV_PREDIV      1U
#define PLLDIG_DV_MFD       50U
#define PLLDIG_DV_RFDPHI   1U
#define CGM_SC_DC_DIV        11U
#elif  (SYS_OSC_CLOCK_FREQ == 16000)
#define PLLDIG_DV_PREDIV      1U
#define PLLDIG_DV_MFD       50U
#define PLLDIG_DV_RFDPHI   1U
#define CGM_SC_DC_DIV        15U
#elif  (SYS_OSC_CLOCK_FREQ == 20000)
#define PLLDIG_DV_PREDIV      1U
#define PLLDIG_DV_MFD       20U
#define PLLDIG_DV_RFDPHI   2U
#define CGM_SC_DC_DIV        3U
#elif  (SYS_OSC_CLOCK_FREQ == 40000)
#define PLLDIG_DV_PREDIV      2U//1U	//yanan.zhao1
#define PLLDIG_DV_MFD       10U
#define PLLDIG_DV_RFDPHI   2U
#define CGM_SC_DC_DIV        3U
#else
#error "The osc clock is error."
#endif


extern void MCU_ClkSet(void);
extern void Sys_DeinitClock(void);
extern void Sys_Sleep(void);
extern void Sys_InitClock(void);
extern void Sys_GotoApplication(void);
/** \brief This function is used to remap interrupt vector table.*/
extern void Sys_RemapInterrupt(void);
/** \brief This function is used to turn on the flash protection.*/
extern void Sys_ProtectBootloader(void);

#endif /* SYSTEM_H */







