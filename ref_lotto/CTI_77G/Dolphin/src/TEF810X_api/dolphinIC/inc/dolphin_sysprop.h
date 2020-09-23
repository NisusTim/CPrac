/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016													*/
/*																				*/
/* All rights are reserved. Reproduction in whole or in part is prohibited		*/
/* without the prior written consent of the copy-right owner.					*/
/* This source code and any compilation or derivative thereof is the sole		*/
/* property of NXP B.V. and is provided pursuant to a Software License			*/
/* Agreement. This code is the proprietary information of NXP B.V. and			*/
/* is confidential in nature. Its use and dissemination by any party other		*/
/* than NXP B.V. is strictly limited by the confidential information			*/
/* provisions of the agreement referenced above.								*/
/*																				*/
/* NXP reserves the right to make changes without notice at any time.			*/
/* NXP makes no warranty, expressed, implied or statutory, including but		*/
/* not limited to any implied warranty of merchantability or fitness for any	*/
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage		*/
/* arising from its use.														*/
/*------------------------------------------------------------------------------*/

/**
*
* @file dolphin_sysprop.h
*
* @ver vX.Y.Z 
*
* @author
*
* @date 04/02/2016
*
* @brief Dolphin System properties exposed to user.
*
******************************************************************************/

#ifndef DOLPHIN_SYSPROP_H
#define DOLPHIN_SYSPROP_H

/******************************************************************************
* INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C"
{
#endif  /* defined(__cplusplus) */

/******************************************************************************
* DEFINES
*******************************************************************************/

//-----------------------------------Chirpping--------------------------------------------------
enum dolphin_SysProp_ProfMode
{
    DOLPHIN_SYSPROP_PROFMODE_0 = 0x00,  // Selects Prof-0 LUT
    DOLPHIN_SYSPROP_PROFMODE_1 = 0x01,  // Selects Prof-1 LUT
    DOLPHIN_SYSPROP_PROFMODE_2 = 0x02,   // Selects Prof-2 LUT
    DOLPHIN_SYSPROP_PROFMODE_3 = 0x03,  // Selects Prof-3 LUT
    DOLPHIN_SYSPROP_PROFMODE_4 = 0x04,  // Selects Prof-0-1 LUT
    DOLPHIN_SYSPROP_PROFMODE_5 = 0x05,   // Selects Prof-0-1-2 LUT
    DOLPHIN_SYSPROP_PROFMODE_6 = 0x06   // Selects Prof-0-1-2-3 LUT

};
typedef int32_t dolphin_SysProp_ProfMode_t;

enum dolphin_SysProp_ProfID
{
    DOLPHIN_SYSPROP_PROFID_P0        = 0x0,    //Profile-0
    DOLPHIN_SYSPROP_PROFID_P1        = 0x1,    //Profile-1
    DOLPHIN_SYSPROP_PROFID_P2        = 0x2,    //Profile-2
    DOLPHIN_SYSPROP_PROFID_P3        = 0x3     //Profile-3
};

typedef int32_t dolphin_SysProp_ProfID_t;

struct dolphin_SysProp_SubBandProp
{
    int32_t         subbandID;
    double          effFc;
    double          effBW;
    double          loopBW;
    bool            use2GBands;
    double          fstart;         // In units of Hz
    double          fstop;          // In units of Hz
    double          chbw;           // In units of Hz
};
typedef struct dolphin_SysProp_SubBandProp dolphin_SysProp_SubBandProp_t;

struct dolphin_SysProp_ProfEntry
{
    uint32_t                    nadcSample;
    bool                        downchirp;

    double                      tdwell;         //units in sec, eg 1.5e-6 (1.5usec)
    double                      tsettle;        //units in sec, eg 1.5e-6 (1.5usec)
    double                      treset;         //units in sec, eg 1.5e-6 (1.5usec)
    double                      tramp;          //units in sec, eg 1.5e-6 (1.5usec)

    // uint8_t                     txbpsnumeric;   // bit0-TX0 | bit1-TX1 | bit2-TX3
    // uint8_t                     txonnumeric;    // bit0-TX0 | bit1-TX1 | bit2-TX3
    // uint8_t                     rxonnumeric;    // bit0-RX0 | bit1-RX1 | bit2-RX3 | bit3-RX4

    bool                        bpscontrol[3];
    bool                        txsw[3];
    bool                        txpon[3];
    bool                        rxpon[4];

    //Sub-Band property ...
    dolphin_SysProp_SubBandProp_t subband;

    //TODO :: Better to move following settings as part of advance cfg ...
    uint8_t                     pdc_decifact;       // PDC Decimation Factor
    bool                        pdc_op_signed;      // PDC Output Signed
    bool                        tx_bps_fast_switch_cntrlpoint_settle;
    double                      tx_bps_fast_switch_time;
};
typedef struct dolphin_SysProp_ProfEntry dolphin_SysProp_ProfEntry_t;


struct dolphin_SysProp_ChirpingProp
{
    uint8_t                             n_seq;
    uint16_t                            n_chirp;
    dolphin_SysProp_ProfMode_t          profmode;
    uint32_t                            profstaycount;
    bool                                enprofreset;
    dolphin_SysProp_ProfEntry_t         proflut[0x04];
    double                              tjumpback;      //units in sec, eg 1.5e-6 (1.5usec)
    double                              seq_interval;   //units in sec, eg 1.5e-6 (1.5usec)


    // -------------------------SweepControl SweepMode---------------------------------------------

    bool progressive;           // 0: Load accumulator between chirps,
                                // 1: Do not load accumulator and the chirps are progressive i.e the next chirp wil follow from where the previous chirp resetted
                                // and accumulator will not load the base frequency"
    bool sweepcounter;          // 0: Sweep control will follow timing engine (activeresetTE signal)
                                // 1: Sweep control will follow the sweep counter value (up/down counter)

    // -------------------------(end)SweepControl SweepMode-----------------------------------------

};
typedef struct dolphin_SysProp_ChirpingProp dolphin_SysProp_ChirpingProp_t;


//-----------------------------------(end)Chirpping----------------------------------------------


enum dolphin_SysProp_SerialiserMode
{
    dolphin_SysProp_SerialiserMode_CSI2        = 0x1,
    dolphin_SysProp_SerialiserMode_LVDS        = 0x2,
    dolphin_SysProp_SerialiserMode_CIF         = 0x3
};

typedef int32_t dolphin_SysProp_SerialiserMode_t;


//-----------------------------------TX--------------------------------------------------
struct dolphin_SysProp_TXPowerMeasured
{
    double          powdet[0x03];
};
typedef struct dolphin_SysProp_TXPowerMeasured dolphin_SysProp_TXPowerMeasured_t;

struct dolphin_SysProp_TXPACalibInParam
{
    bool enable_dcbus;
    int8_t ctl_pdt_cal_cur_bist_spi_val1;
    int8_t ctl_pdt_cal_cur_bist_spi_val2;
    double vdd_adc;
};
typedef struct dolphin_SysProp_TXPACalibInParam dolphin_SysProp_TXPACalibInParam_t;

struct dolphin_SysProp_TXPALevel
{
    double          offset[0x03];         // Offset(mV)
    double          gcorr[0x03];          // GCorr(mV)
    double          vrms[0x03];           // Vrms(mV)
};
typedef struct dolphin_SysProp_TXPALevel dolphin_SysProp_TXPALevel_t;

struct dolphin_SysProp_TXActiveCtrl
{
    bool phaseshift[0x03];        //Control TX phase: 0=0deg , 1=180deg.
    bool ctrlswitch[0x03];        //Control TX switch: 0=off, 1=on
    bool enable[0x03];            //Enable TX 0=off, 1=on.
    uint8_t power[0x03];          //TX output power
};
typedef struct dolphin_SysProp_TXActiveCtrl dolphin_SysProp_TXActiveCtrl_t;

//-----------------------------------(end)TX--------------------------------------------------

//-----------------------------------RX------------------------------------------------------
struct dolphin_SysProp_RXActiveCtrl
{
    bool enable[0x04];            //Enable receiver: 0=off, 1=on
    uint8_t rxgain[0x04];         //Control RX Gain
};
typedef struct dolphin_SysProp_RXActiveCtrl dolphin_SysProp_RXActiveCtrl_t;
//-----------------------------------(end)RX--------------------------------------------------

//-----------------------------------MISC------------------------------------------------------
enum dolphin_SysProp_Modid
{
    DOLPHIN_SYSPROP_MODID_CCTRL         = 0x01, //Central Control
    DOLPHIN_SYSPROP_MODID_INTERFACE     = 0x02, //Interface
    DOLPHIN_SYSPROP_MODID_MCLK          = 0x04, //MCLK
    DOLPHIN_SYSPROP_MODID_ADC           = 0x08, //ADC
    DOLPHIN_SYSPROP_MODID_LVDS          = 0x10, //LVDS
    DOLPHIN_SYSPROP_MODID_AFC           = 0x20, //AFC/CHIRP
    DOLPHIN_SYSPROP_MODID_SCTRL         = 0x40, //SWEEP CTRL
    DOLPHIN_SYSPROP_MODID_TENG          = 0x80, //TENG
    DOLPHIN_SYSPROP_MODID_RX            = 0x100, //RX
    DOLPHIN_SYSPROP_MODID_TX            = 0x200 //TX
};
typedef enum dolphin_SysProp_Modid dolphin_SysProp_Modid_t;
//-----------------------------------(end)MISC------------------------------------------------------

#if defined(__cplusplus)
}
#endif  /* defined(__cplusplus) */

#endif /* DOLPHIN_SYSPROP_H */

