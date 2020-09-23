/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the timer module for MPC5744P.
 *
 *  \file       bl_system.c
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
#include "bl_system.h"
#include "S32R274.h"

#include "bl_watchdog.h"

#define FCCU_NCFK_KEY 0xAB3498FE
#define DRUN_MODE     0x3

 /*****************************************************************************
  *  Internal Type Definitions
  *****************************************************************************/
typedef void (* theApp)(void);
/* ------------------------------------------------------------------------------
 MC_MODE_INIT

 Configure the Mode Entry module and set the system clock dividers
-------------------------------------------------------------------------------*/
static void MC_MODE_INIT(void){

    MC_ME.ME.R = DEFAULT_MC_ME_MODE;		/* Enable all modes */

    /* Setting RUN Configuration Register ME_RUN_PC[n] */
    MC_ME.RUN_PC[0].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[1].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[2].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[3].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[4].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[5].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[6].R=0x000000FE;	/* Peripheral ON in every mode */
    MC_ME.RUN_PC[7].R=0x000000FE;	/* Peripheral ON in every mode */

    /* Configure system clock dividers (CGM.SC_DC[0..5])
    Dividers are configured for PLL1 as system clock source
    PLL1 is configured to provide 240MHz clock
    f = 240 / (1 + DIV) MHz
    */
    CGM.SC_DC0.B.DIV = 0x1;		/* SYS_CLK = 120MHz */
    CGM.SC_DC1.B.DIV = 0x0;	    /* Z7a CORE1_CLK = 240MHz */
    CGM.SC_DC2.B.DIV = 0x0;	    /* Z7b CORE2_CLK = 240MHz */
    CGM.SC_DC3.B.DIV = 0x3;	    /* AIPS PBRIDGE_CLK = 60MHz */
    CGM.SC_DC4.B.DIV = 0x1;		/* DMA_CLK = 120MHz */
    CGM.SC_DC5.B.DIV = 0x1;		/* z4 CORE0_CLK = 120MHz */

    MC_ME.IM.R = 0x3F;  			/* Enable all interrupts */
}

/* ------------------------------------------------------------------------------
 OSC_INIT

 Enable the AFE oscillator(XOSC). Requires 40MHz external crystal connected to EXTAL.
 Follows procedure from Initialization section in AFE chapter of reference manual
-------------------------------------------------------------------------------*/
static void OSC_INIT (clock_mode_type clock_mode)
{
    AFE.VRFCTRL1.B.PWRDN = 0;             /* Power on VREF */
    while (AFE.LVDSTS.B.BGOK !=1) ;       /* Ensure 1.2V VREF is present */

    AFE.ADCCTRL2.B.RT_PWRDN = 0;           /* Must clear this bit if no external trim resistor is present (SD_R) */

    if (clock_mode == XOSC_DIFF_BYP_MODE)
    { //differential bypass
      AFE.OSCCTRL.B.EN_EXT = 1;           // Oscillator to external clock mode
      MC_ME.DRUN_MC.B.XOSCON=1;
    }
    else if (clock_mode == XOSC_SE_BYPASS)
    { //single ended bypass
      AFE.OSCCTRL.B.EN_EXT = 1;           // Oscillator to normal operation, no bypass
      MC_ME.DRUN_MC.B.XOSCON=0;
    }
    else
    { //crystal
      AFE.OSCCTRL.B.EN_EXT = 0;           // Oscillator to normal operation, no bypass
      MC_ME.DRUN_MC.B.XOSCON=1;
    }

    /* 2. Set OSCCTRL[ICAL] to 0110. */
    AFE.OSCCTRL.B.ICAL = 0x6;             /* Buffer bias 100�A, oscillator bias 20�A */

    /* 3. Write the desired oscillator settling time into OSCDLY */
    AFE.OSCDLY.R = 0x80;                  /* Set count of transitions to complete for OSC stability. 0x80*256 = 32768 transitions */

    /* 4. Enable the oscillator in the Mode Entry module. */
    //MC_ME.DRUN_MC.B.XOSCON = 0x1;         /* Enable the XOSC clock in Mode Entry DRUN mode */
    /* Re-enter the DRUN mode to apply changes */
    MC_ME.MCTL.R = 0x30005AF0;		            /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;		            /* Mode & Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1);	        /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);	/* Check DRUN mode has been entered */

    /* 5. Set OSCCTRL[IE] and wait for oscillator interrupt.
    Status flag polling is used instead of interrupts */
    //AFE.OSCCTRL.B.IE = 0x1;               /* Set Osc Interrupt  */
    //while (AFE.OSCSTS.B.STS != 0x1);      /* Wait for oscillator to complete set number of transitions (considered stable) */

    /* 6 Write OSCSTS[STS] to clear interrupt. */
    //AFE.OSCSTS.B.STS = 0x1;               /* Clear OSC stable interrupt flag  */

}

/* ------------------------------------------------------------------------------
 PLL_INIT_0

 Configure and enable PLL0 for 200MHz (PLL0_PHI_CLK)
 PLL0_PHI1_CLK is 60MHz reference input to PLL1
-------------------------------------------------------------------------------*/
static void PLL_INIT_0( clock_mode_type clock_mode )
{
   if( clock_mode == IRC_MODE ){
     /* Route IRC to PLL0 */
     CGM.AC3_SC.B.SELCTL = 0x0;    /* Connect IRC as PLL0 ref */

     /* PLL0_PHI_CLK = 197MHz */
     /* PLL0_PHI1_CLK = 59MHz (ref input to PLL1) */
     PLLDIG.PLL0DV.B.PREDIV = 0x1;       /* Reference clock predivider. XOSC 16MHz/1 = 16MHz */
     PLLDIG.PLL0DV.B.MFD = 0x25;         /* Feedback loop multiplier. 16MHz * 37 = 592MHz */
     PLLDIG.PLL0DV.B.RFDPHI = 0x03;      /* Divider for PLL0_PHI_CLK. 592MHz/3 = 197MHz */
     PLLDIG.PLL0DV.B.RFDPHI1 = 0xA;      /* Divider for PLL0 feed to PLL1. 592MHz/10 = 59.2MHz */
   }
   else {
     MC_ME.DRUN_MC.B.PLL0ON = 0; // Disable PLL0

     /* RE  enter the drun mode, to update the configuration */
     MC_ME.MCTL.R = 0x30005AF0;    /* Mode & Key */
     MC_ME.MCTL.R = 0x3000A50F;    /* Mode & Key inverted */
     while(MC_ME.GS.B.S_MTRANS == 1);  /* Wait for mode entry to complete */
     while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);  /* Check DRUN mode has been entered */

     /* Route XOSC to PLL0 - IRC is default */
     CGM.AC3_SC.B.SELCTL = 0x1;    /* Connect XOSC as PLL0 ref */

     /* PLL0_PHI_CLK = 200MHz */
     /* PLL0_PHI1_CLK = 60MHz (ref input to PLL1) */
     PLLDIG.PLL0DV.B.PREDIV = 0x1;       /* Reference clock predivider. XOSC 40MHz/1 = 40MHz */
     PLLDIG.PLL0DV.B.MFD = 0x0F;         /* Feedback loop multiplier. 40MHz*15 = 600MHz */
     PLLDIG.PLL0DV.B.RFDPHI = 0x03;      /* Divider for PLL0_PHI_CLK. 600MHz/3 = 200MHz */
     PLLDIG.PLL0DV.B.RFDPHI1 = 0xA;      /* Divider for PLL0 feed to PLL1. 600MHz/10 = 60MHz */
   }

    PLLDIG.PLL0CR.R = 0x8;		        /* Enable interrupts on loss of lock */
    MC_ME.DRUN_MC.B.PLL0ON = 0x1;       /* Enable PLL0 in DRUN mode */

    /* Re-enter the DRUN mode to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;		            /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;		            /* Mode & Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1);	        /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);	/* Check DRUN mode has been entered */

    /* Wait for PLL0 to lock */
    while(PLLDIG.PLL0SR.B.LOCK == 0);
    while(MC_ME.GS.B.S_PLL0 == 0);
}

/* ------------------------------------------------------------------------------
 PLL_INIT_1

 Configure and enable PLL1 to 240MHz (PLL1_PHI_CLK)
-------------------------------------------------------------------------------*/
static void PLL_INIT_1(void)
{
    /* Route PLL0_PHI1_CLK to PLL1 */
    CGM.AC4_SC.B.SELCTL = 0x0;		        /* Connect PLL0_PHI1_CLK as PLL1 ref */

    /* PLL1_PHI_CLK = 240MHz */
    PLLDIG.PLL1DV.B.MFD = 0x10;		        /* Feedback loop multiplier. 60MHz*16 = 960MHz */
    PLLDIG.PLL1DV.B.RFDPHI = 0x2;		    /* Divider for PLL1_PHI_CLK. 960MHz/(2*2) = 240MHz */

    PLLDIG.PLL1CR.R = 0x8;		            /* Enable interrupts on loss of lock */
    MC_ME.DRUN_MC.B.PLL1ON = 0x1; 		    /* Enable PLL1 */

    /* Re-enter the DRUN mode to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;		            /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;		            /* Mode & Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1);	        /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);	/* Check DRUN mode has been entered */

    /* Wait for PLL1 to lock */
    while(PLLDIG.PLL1SR.B.LOCK ==0);
    while(MC_ME.GS.B.S_PLL1 ==0);
}

/* ------------------------------------------------------------------------------
 AIPS_INIT

 Configure the peripheral bridges(PBRIDGE/AIPS)
-------------------------------------------------------------------------------*/
static void AIPS_INIT (void){
    // SMPU_x logical bus master ID assignment:
	// Master  0: core-0 (Z4)
	// Master  1: core-1 (Z7a)
	// Master  2: eDMA
	// Master  3: Flexray
	// Master  4: Zipwire (LFAST+SIPI)
	// Master  5: Ethernet
	// Master  6: SPT PDMA
	// Master  7: core-2 (Z7b)
	// Master  8: core-0 Nexus
	// Master  9: core-1 Nexus
	// Master 10: SPT SDMA MIPI CSI image data and ADC channel5
	// Master 11: n/a
	// Master 12: CSE
	// Master 13: SPT Command Sequencer
	// Master 14: SPT SDMA
	// Master 15: core-2 Nexus
    // same MPU setup for both XBAR MPUs (SMPU_0 and SMPU_1)

    AIPS_0.MPRA.R = 0x77700007;     /* R/W access from all cores and eDMA */
    AIPS_0.MPRB.R = 0x77007007;		/* R/W access from all core Nexus */
    AIPS_1.MPRA.R = 0x77700007;     /* R/W access from all cores and eDMA */
    AIPS_1.MPRB.R = 0x77007007;		/* R/W access from all core Nexus */
}

/* ------------------------------------------------------------------------------
 CGM_INIT

 Configure the clock generation module. Selects a source clock and divider value
 for each module/peripheral attached to the clock tree.
-------------------------------------------------------------------------------*/
static void CGM_INIT (void)
{
    /* Enable and configure Aux clocks */

    /* Auxiliary Clock 0 */
    CGM.AC0_SC.B.SELCTL = 0x3;	    /* SDPLL_CLK_160(160MHz) clock source for MC_CLK, ADC_CLK */

    CGM.AC0_DC0.B.DIV = 0x0;	    /* Divide by 1. MC_CLK = 160MHz */
    CGM.AC0_DC0.B.DE = 0x1;		    /* Enable Auxilliary Clock 0 divider 0 (Motor Control clock) (max 160MHz)*/

    CGM.AC0_DC2.B.DIV = 0x1;	    /* Divide by 2. ADC_CLK = 80MHz */
    CGM.AC0_DC2.B.DE = 0x1;		    /* Enable Auxilliary Clock 0 divider 2 (SARADC clock) (max 80MHz)*/

    /* Auxiliary Clock 1 */
    CGM.AC1_SC.B.SELCTL = 0x2;	    /* PLL0_PHI_CLK(200MHz) clock source for FR_CLK */

    CGM.AC1_DC0.B.DIV = 0x4;	    /* Divide by 5. FR_CLK = 40MHz */
    CGM.AC1_DC0.B.DE = 0x1;		    /* Enable Auxilliary Clock 1 divider 0 (FlexRay) (max 40MHz) */

    /* Auxiliary Clock 2 */
    CGM.AC2_SC.B.SELCTL = 0x2;	    /* PLL0_PHI_CLK(200MHz) clock source for CAN_CLK */

    CGM.AC2_DC0.B.DIV = 0x4;	    /* Divide by 5. CAN_CLK = 40MHz */
    CGM.AC2_DC0.B.DE = 0x1;		    /* Enable Auxilliary Clock 2 divider 0 (CAN) (max 40MHz)*/

    /* Auxiliary Clock 3 set in PLL_INIT_0 */
    /* Auxiliary Clock 4 set in PLL_INIT_1 */

    /* Auxiliary Clock 5 - NOT IMPLEMENTED */
    /* Auxiliary Clock 6 - NOT IMPLEMENTED */

    /* Auxiliary Clock 7 */
    //CGM.AC7_SC.B.SELCTL = 0x3;	    /* PLL0_PHI_CLK(160MHz) clock source for SPT_CLK */
    CGM.AC7_SC.B.SELCTL = 0x2;	    /* PLL0_PHI_CLK(200MHz) clock source for SPT_CLK */

    CGM.AC7_DC0.B.DIV = 0x0;	    /* Divide by 1. SPT_CLK = 200MHz */
    CGM.AC7_DC0.B.DE = 0x1;		    /* Enable Auxilliary Clock 7 divider 0 (SPT_CLK) (max 200MHz)*/

    /* Auxiliary Clock 8 */
    CGM.AC8_SC.B.SELCTL = 0x2;	    /* PLL0_PHI_CLK(200MHz) clock source for LFAST_CLK */

    CGM.AC8_DC0.B.DIV = 0x0;	    /* Divide by 1. LFAST_CLK = 200MHz */
    CGM.AC8_DC0.B.DE = 0x1;		    /* Enable Auxilliary Clock 8 divider 0 (LFAST_CLK)(max 320MHz) */

    /* Auxiliary Clock 9 set in CLK_OUT function */
//   CGM.AC9_SC.B.SELCTL=2;	        /* (PLL0_PHI_CLK) clock source for CLK_OUT1 */

//   CGM.AC9_DC0.B.DIV=3;       	/* Divide by 4 */
//   CGM.AC9_DC0.B.DE=1;	        /* Enable Auxilliary Clock 9 divider 0 (CLK_OUT1) (max 60MHz)*/

    /* Auxiliary Clock 10 */
    CGM.AC10_SC.B.SELCTL = 0x2;	    /* PLL0_PHI_CLK(200MHz) clock source for ENET_CLK */

    CGM.AC10_DC0.B.DIV = 0x3;	    /* Divide by 4. ENET_CLK = 50MHz */
    CGM.AC10_DC0.B.DE = 0x1;	    /* Enable Auxilliary Clock 10 divider 0 (ENET_CLK) (max 50MHz)*/

    /* Auxiliary Clock 11 */
    CGM.AC11_SC.B.SELCTL = 0x2; 	/* PLL0_PHI_CLK(200MHz) clock source for ENET_TIME_CLK */

    CGM.AC11_DC0.B.DIV = 0x1;	    /* Divide by 2. ENET_TIME_CLK = 100MHz */
    CGM.AC11_DC0.B.DE = 0x1;	    /* Enable Auxilliary Clock 11 divider 0 (ENET_TIME_CLK)(max 100MHz) */

    /* Auxiliary Clock 12 */
    CGM.AC12_SC.B.SELCTL = 0x4;     /* PLL1_PHI_CLK(240MHz) clock source for SPI_CLK */

    CGM.AC12_DC0.B.DIV = 0x2;       /* Divide by 3. SPI_CLK = 80MHz */
    CGM.AC12_DC0.B.DE = 0x1;        /* Enable Auxilliary Clock 12 divider 0 (SPI_CLK)(max 80MHz) */

    /* Auxiliary Clock 13 */
    CGM.AC13_SC.B.SELCTL = 0x6;     /* PBRIDGE_0(59.2MHz) clock source for LIN_CLK, LINIPS_CLK */

    CGM.AC13_DC0.B.DIV = 0x0;       /* Divide by 1. LIN_CLK = 59.2MHz, LINIPS_CLK = 59.2MHz */
    //CGM.AC13_DC0.B.DE = 0x1;        /* Enable Auxilliary Clock 13 divider 0 (LIN_CLK)(max 80MHz) */

    /* Auxiliary Clock 14 set in CLK_OUT function */
//   CGM.AC14_SC.B.SELCTL = 0x2;      /* (PLL0_PHI_CLK) clock source for CLK_OUT0 */

//   CGM.AC14_DC0.B.DIV = 0x3;        /* Divide by 4 */
//   CGM.AC14_DC0.B.DE = 0x1;         /* Enable Auxilliary Clock 14 divider 0 (CLK_OUT0) (max 60MHz)*/

}

/* ------------------------------------------------------------------------------
 SET_SYS_CLK

 Set the source of the overall system clock for default run(DRUN) mode.
-------------------------------------------------------------------------------*/
static void SET_SYS_CLK ( system_clock_e system_clock ){

    if( system_clock == CLOCK_IRC ){
      MC_ME.DRUN_MC.B.SYSCLK=0;               /* IRC system CLK (16MHz) */
    }
    else if( system_clock == CLOCK_XOSC ){
      MC_ME.DRUN_MC.B.SYSCLK=1;               /* XOSC system CLK (40MHz) */
    }
    else if( system_clock == CLOCK_PLL0 ){
      MC_ME.DRUN_MC.B.SYSCLK=2;               /* PLL0 system CLK (200MHz) */
    }
    else if( system_clock == CLOCK_SDPLL_DIV_2 ){
      MC_ME.DRUN_MC.B.SYSCLK=3;               /* SDPLL/2 system CLK (160MHz) */
    }
    else{
      MC_ME.DRUN_MC.B.SYSCLK=4;               /* PLL1 system CLK (240MHz) */
    }

    /* Re-enter the DRUN mode to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;		            /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;		            /* Mode & Key inverted */
    while(MC_ME.GS.B.S_MTRANS == 1);	        /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3);	/* Check DRUN mode has been entered */
}

/* ------------------------------------------------------------------------------
 CLK_OUT

 Configure the CLK_OUT0 & CLK_OUT1 signals to be available on GPIO pins.
 clk0_sel selects the source for CLK_OUT0, clk1_sel for CLK_OUT1
 clk0_div is the divider value for CLK_OUT0, clk1_div for CLK_OUT1
-------------------------------------------------------------------------------*/
static void CLK_OUT(uint8_t clk0_sel, uint8_t clk0_div, uint8_t clk1_sel, uint8_t clk1_div)
{
    #define DIV 7               // Divider value = DIV+1

    /* Configure CLKOUT selection in multi-purpose control block (MCB) */
    //MCB.CLKOUT_SEL.B.CLKOUT0 = clk0_sel;         /* Route XOSC to CLKOUT0 */
    //MCB.CLKOUT_SEL.B.CLKOUT1 = clk1_sel;         /* Route XOSC to CLKOUT0 */
    MCB.CLKOUT_SEL.R = 0x00000402 | clk0_sel << 6 | clk1_sel << 2;

    /* Aux clock 14 controls divider for CLK_OUT0(max 67MHz) */
    CGM.AC14_DC0.R = 0x80000000 | (clk0_div-1) << 16;               /* Write with 32-bit access */

    /* Aux clock 9 controls divider for CLK_OUT1(max 67MHz)*/
    //CGM.AC9_DC0.R = 0x80000000 | (clk1_div-1) << 16;               /* Write with 32-bit access */

    /* Configure SIUL2 to make clock available on GPIO */
    SIUL2.MSCR[22].R =  0x12800001;		/* CLKOUT0 on pin J14 (PB6 on EVB) */
    //SIUL2.MSCR[79].R =  0x12800002;		/* CLKOUT1 on pin C15 (PE15 on EVB)*/
}

/* ------------------------------------------------------------------------------
 SDPLL_INIT

 Configure and enable the Sigma Delta PLL (SDPLL) in the AFE at 320MHz
-------------------------------------------------------------------------------*/
static void SDPLL_INIT (void){
    while (!AFE.LVDSTS.B.BGOK) ;         /* Check 1.25v rail is up */

    /* 1. Clear MC_ME_RUNn_MC[SDPLLON] in
    Mode Entry Module in order to make sure SDPLL is reset and off. */
    MC_ME.DRUN_MC.B.SDPLLON = 0x0;       /* Disable SDPLL in Mode Entry Module */
    /* Perform mode change */
    MC_ME.MCTL.R = 0x30005AF0;                  /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                  /* Mode & Key inverted */
    /* Ensure mode change was successful */
    while(MC_ME.GS.B.S_MTRANS == 1) ;           /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3) ;   /* Check DRUN mode has been entered */

    /* 2. Clear PLLCTRL1[RST_B] */
    AFE.PLLCTRL1.B.RST_B = 0x0;          /* Reset the SDPLL */

    /* 3. Set PLLCTRL1[CLKGEN_EN]. */
    AFE.PLLCTRL1.B.CLKGEN_EN = 0x1;      /* Enable generation of 160MHz and 80MHz clocks */

    /* 4. Set PLLCTRL8[REFCLK_CNT] to 0xF and set PLLCTRL8[FCLKBY2_CNT] to 0x0F0. */
    AFE.PLLCTRL8.B.REFCLK_CNT = 0xF;     /* Program reference clock count */
    AFE.PLLCTRL8.B.FCLKBY2_CNT = 0x0F0;  /* Program Fvco/2 clock count */

    /* 5. Set PLLCTRL3[CP_I_SEL] to 100. */
    AFE.PLLCTRL3.B.CP_I_SEL = 0x4;       /* Set charge pump current to improve phase noise */

    /* 6. Turn on SDPLL using the Magic Carpet module. */
    MC_ME.DRUN_MC.B.SDPLLON = 0x1;       /* Enable SDPLL in Mode Entry Module */
    /* Re-enter the DRUN mode to update the configuration */
    MC_ME.MCTL.R = 0x30005AF0;                  /* Mode & Key */
    MC_ME.MCTL.R = 0x3000A50F;                  /* Mode & Key inverted */

    /* 7. Set PLLCTRL1[RST_B] to take SDPLL out of reset. */
    AFE.PLLCTRL1.B.RST_B = 0x1;          /* Bring SDPLL out of reset */

    /* 8. Set PLLCTRL3[LCKHIIE] to enable SDPLL lock interrupt.
    Status flag polling is used instead of interrupts */
    //AFE.PLLCTRL3.B.LCKHIIE = 0x1;      /* Enable SDPLL lock achieved interrupt */

    /* 9. Enable SDPLL calibration by setting PLLCTRL2[START]. */
    AFE.PLLCTRL2.B.START = 0x1;          /* Starts DCbias and Fcap calibration in SDPLL */

    /* 10. Wait for SDPLL lock interrupt which indicates completion of calibration (500usec)
    and lock (75usec).
    Status flag polling is used instead of interrupts */
    while (AFE.PLLSTS.B.LOCK != 0x1);	 /* Wait unitl SDPLL has calibrated and locked */

    /* 11. Clear PLLCTRL3[LCKHIIE] and set PLLCTRL3[LCKLOIE] to clear lock interrupt
    and to enable loss of lock interrupt. */
    AFE.PLLCTRL3.B.LCKHIIE = 0x0;      /* Disable SDPLL lock achieved interrupt */
    AFE.PLLCTRL3.B.LCKLOIE = 0x1;        /* Enable SDPLL loss of lock interrupt */

    /* 11. Set PLLCTRL3[LORIE] to enable loss of reference interrupt. */
    AFE.PLLCTRL3.B.LORIE = 0x1;          /* Enable SDPLL loss of reference clock interrupt */

    /* Ensure mode change was successful */
    while(MC_ME.GS.B.S_MTRANS == 1) ;           /* Wait for mode entry to complete */
    while(MC_ME.GS.B.S_CURRENT_MODE != 0x3) ;   /* Check DRUN mode has been entered */
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Mcu_ClkSet
*
* Description   : MCU bus clock set.
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   : this function set clock to a target bus.
*
************************************************************************************************
END_FUNCTION_HDR */
void MCU_ClkSet(void)
{
	if(MC_ME.ME.R == DEFAULT_MC_ME_MODE)
		return;

	OSC_INIT (XOSC_SE_BYPASS);	    // Configure XOSC (40 MHz signal end bypass)
	PLL_INIT_0(XOSC_MODE);          // Configure PLL 0
	PLL_INIT_1();                  	// Configure PLL 1
	CGM_INIT();                    	// Configure Clocks
	MC_MODE_INIT();    				// Configure Modules via Mode Entry
	SET_SYS_CLK( CLOCK_PLL1 );      // Set the system clock
	CLK_OUT(PLL1_SEL, 80, 0, 0); 	// Synchronize switcher with 1MHz
	AIPS_INIT();                    // Configure PBridge
	SDPLL_INIT();
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Sys_DeinitClock
*
* Description   : Deinit all ,mcu related registers if necessary
*
* Inputs        : None
*
* Outputs       : None
*
* Limitations   :
*
************************************************************************************************
END_FUNCTION_HDR */
void Sys_DeinitClock(void)
{
//    MC_ME.MCTL.R = 0x30005AF0;               /* Enter DRUN Mode & Key */
//    MC_ME.MCTL.R = 0x3000A50F;               /* Enter DRUN Mode & Inverted Key */
//    while(MC_ME.GS.B.S_MTRANS == 1){}        /* Wait for mode entry to complete */
//    while(MC_ME.GS.B.S_CURRENT_MODE != 3) {} /* Verify DRUN is the current mode */
//    MC_ME.IS.R = 0x00000001;
//    MC_ME.DRUN_MC.R = 0x00130010;
//    MC_ME.RUN_PC[0].R = 0x0;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Sys_InitClock
*
* Description   : Init Mcu Resource
*
* Inputs        : None
*
*
* Outputs       : None
*
* Limitations   :
*
*
************************************************************************************************
END_FUNCTION_HDR */
void Sys_InitClock(void)
{
    //FCCU_clear_faults();
    //FCCU_Init();

    MCU_ClkSet();

}

/**************************************************************************//**
 *
 *  \details Set system clock to sleep mode.
 *
 *  \return None.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
void Sys_Sleep(void)
{
}

/**************************************************************************//**
 *
 *  \details Remap the interrupt vector table.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Sys_RemapInterrupt(void)
{
}

/**************************************************************************//**
 *
 *  \details Set up the application entry point, and go to the application.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Sys_GotoApplication(void)
{
    /*when a new application is downloaded by the bootloader, the enter address
      of this application maybe is different from the old one.*/

    theApp AppEntry = (theApp)(*(volatile bl_u32_t *)SYS_ENTRY_POINT);
    AppEntry();

}

/**************************************************************************//**
 *
 *  \details .
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
void Sys_ProtectBootloader(void)
{
}



