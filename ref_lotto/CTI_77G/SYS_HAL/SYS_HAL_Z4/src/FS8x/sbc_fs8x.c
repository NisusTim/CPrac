/*
 * Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @file sbc_fs8x.c
 * @brief Driver functions for the FS8x SBC.
 *
 * @author nxf44615
 * @version 1.0
 * @date 29-Jun-2018
 * @copyright Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stddef.h>

#include "sbc_fs8x.h"
#include "sbc_fs8x_map.h"
#include "sbc_fs8x_assert.h"
#include "sbc_fs8x_communication.h"
#include "sbc_fs8x_common.h"
#include "sbc_fs8x_spi.h"
#include "sbc_fs8x_adc.h"
#include "sys_shared.h" /* include peripheral declarations */
#include "TJA1145FD_Application_Specific_Functions.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** @brief Returns true if value VAL is in the range defined by MIN and MAX values
 * (range includes the border values).
 * @param val Comparison value.
 * @param min Minimal value of the range.
 * @param max Maximal value of the range.
 * @return True if value is the range. False otherwise. */
#define FS8x_IS_IN_RANGE(val, min, max)   (((val) >= (min)) && ((val) <= (max)))

//AMUX
#define FS8x_V_TEMP25 2.07F
#define FS8x_V_TEMP_COEFF (-0.006F)
/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
static float conversionDiv2_5(float number);
//static float conversionDiv7_5(float number);  //Removed by Wood, in order to fix not used warning
static float conversionDiv14(float number);
static float conversionTemp(float number);
static void loadDefaultDriverConfig(fs8x_drv_data_t* drvData);
static float get_fs8x_amux_voltage(fs8x_amux_selection_t ch);
static fs8x_status_t fs8x_wd_window_init(fs8x_drv_data_t* drvData);
static fs8x_status_t fs8x_wd_cfg_init(fs8x_drv_data_t* drvData);
static fs8x_status_t fs8x_wd_init(void);
static fs8x_status_t fs8x_fs0b_release(void);
static fs8x_status_t FS8x_WD_Refresh(fs8x_drv_data_t* drvData);
static fs8x_status_t FS8x_WD_Refresh_and_Load_Config(void);
static fs8x_status_t FS8x_WD_Bad_Refresh_and_Load_Config(void);
static fs8x_status_t FS8x_SwitchAMUXchannel(fs8x_drv_data_t *drvData, fs8x_amux_selection_t channelSelection);
static fs8x_status_t FS8x_ReadSwitchAMUXchannel(fs8x_drv_data_t *drvData,fs8x_rx_frame_t* rxData);
static fs8x_status_t FS8x_SwitchAMUXchannel_and_Load_Config(uint16_t channel);
static fs8x_status_t FS8x_ReadSwitchAMUXchannel_and_Load_Config(fs8x_rx_frame_t* rxData);
static fs8x_status_t FS8x_Read_Register_and_Load_Config(fs8x_rx_frame_t* rxData,uint16_t isfs,uint16_t addr);
static fs8x_status_t FS8x_Write_Register_and_Load_Config(uint16_t txData,uint16_t isfs,uint16_t addr);
static uint16_t get_fs8x_wd_seed(void);
static void fs8x_spread_spectrum_23khz(void);
/*******************************************************************************
 * Local Functions Prototypes
 ******************************************************************************/
#if (FS8x_WD_TYPE == FS8x_WD_CHALLENGER)

/* Reads challenge token (next generated LFSR state) from the SBC. */
static fs8x_status_t FS8x_WD_ReadChallengeToken(fs8x_drv_data_t *drvData, uint16_t* wdSeed);

/* Compute Challenger Watchdog answer. */
static uint16_t FS8x_WD_ComputeAnswer(uint16_t token);

#endif

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static uint8_t init_fs8x_flag = 0;//1:init,0:not init
/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Local Functions - Implementation
 ******************************************************************************/

#if (FS8x_WD_TYPE == FS8x_WD_CHALLENGER)
/* Reads challenge token (next generated LFSR state) from the SBC and stores it
 * into the driver data structure. */
static fs8x_status_t FS8x_WD_ReadChallengeToken(fs8x_drv_data_t *drvData, uint16_t* wdSeed)
{
    fs8x_status_t status = fs8xStatusOk;    /* Status variable. */
    fs8x_rx_frame_t response;               /* Response to the command. */

    FS_ASSERT(drvData != NULL);

    status = FS8x_ReadRegister(drvData, true, FS8X_FS_WD_SEED_ADDR, &response);
    if (status != fs8xStatusOk)
    {
        return status;
    }

    /* Store the watchdog seed from the SBC device. */
    *wdSeed = response.readData;

    return status;
}

/* Compute Challenger Watchdog answer. */
static uint16_t FS8x_WD_ComputeAnswer(uint16_t token)
{
    uint16_t mr = token; /* Monitoring result. */

    /* Simulates ALU Checker on the MCU side. */
    mr *= 4U;
    mr += 6U;
    mr -= 4U;
    mr = ~mr;
    mr /= 4U;

    return mr;
}
#endif

/*******************************************************************************
 * API - Implementation
 ******************************************************************************/

/* Loads default driver configuration. */
static void loadDefaultDriverConfig(fs8x_drv_data_t* drvData)
{
	fs8x_spi_init();
    drvData->watchdogSeed = FS8x_WD_SEED_DEFAULT;
    drvData->communicationMode = FS8x_COMMUNICATION_MODE;
    drvData->i2cAddressOtp = FS8x_I2C_MAIN_ADDRESS;
}

//static fs8x_status_t FS8x_ReadFlag1(fs8x_drv_data_t *drvData,fs8x_rx_frame_t* rxData)
//{
//    FS_ASSERT(drvData != NULL);
//
//    /* Check of AMUX channel selection range. */
//
//    return FS8x_ReadRegister(drvData, false, FS8X_M_FLAG1_ADDR, rxData);
//}
//
//static fs8x_status_t FS8x_ReadFlag1_and_Load_Config(fs8x_rx_frame_t* rxData)
//{
//	fs8x_drv_data_t drvConfig;
//
//	loadDefaultDriverConfig(&drvConfig);
//	return 	FS8x_ReadFlag1(&drvConfig,rxData);
//}

//===============================================================================
//WD
/* Performs the watchdog refresh. */
static fs8x_status_t FS8x_WD_Refresh(fs8x_drv_data_t* drvData)
{
    fs8x_status_t status = fs8xStatusError;   /* Status variable. */

    FS_ASSERT(drvData != NULL);

#if (FS8x_WD_TYPE == FS8x_WD_SIMPLE)
    status = FS8x_WriteRegister(drvData, true, FS8X_FS_WD_ANSWER_ADDR,
            drvData->watchdogSeed);
#elif (FS8x_WD_TYPE == FS8x_WD_CHALLENGER)
    uint16_t answer;    /* Calculated monitoring result. */

    /* Synchronize with LFSR generator on the device. */
    status = FS8x_WD_ReadChallengeToken(drvData, &(drvData->watchdogSeed));
    if (status != fs8xStatusOk)
    {
        return status;
    }
    answer = FS8x_WD_ComputeAnswer(drvData->watchdogSeed);
    status = FS8x_WriteRegister(drvData, true, FS8X_FS_WD_ANSWER_ADDR, answer);
#endif
    return status; /* Return error if no WD is selected. */
}




static fs8x_status_t FS8x_WD_Refresh_and_Load_Config(void)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);

	return 	FS8x_WD_Refresh(&drvConfig);
}

static fs8x_status_t FS8x_WD_Bad_Refresh_and_Load_Config(void)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);
	drvConfig.watchdogSeed = 0x1234;
	return 	FS8x_WD_Refresh(&drvConfig);
}

uint8_t FS8x_power_down(void)
{
	uint8_t i;
	if(ChangeToSleepOperation() == 0)
	{
		Delay_ms(100);
	if(init_fs8x_flag)
	{
		for(i=0;i<20;i++)
			{
			FS8x_WD_Bad_Refresh_and_Load_Config();
	}
		}
	}
	else
	{
		return FALSE;
	}

	return FALSE;
}


uint8_t FS8x_goto_standby(void)
{
    uint16_t isFailSafe ;
    uint16_t addr ;
    uint16_t txdata ;

    if(ChangeToSleepOperation() == 0)
    {
        Delay_ms(100);

        //can console command - fs8x wreg 0 1 3
        isFailSafe = 0;
        addr = 1;
        txdata = 3;
        FS8x_Write_Register_and_Load_Config(txdata,isFailSafe,addr);
        PRINTF("Enter sleep mode, Write register val:%02x\n",txdata);
        return TRUE;
    }
    else
    {
        return FALSE;
    }

    return FALSE;    
}

void fs8x_wd_handle(fs8x_wd_mode mode)
{
	uint32_t refresh_wd_time; //800000*1000/16.7  //refresh:800ms	//wd setting:1024ms
	static uint32_t   start = 0, end = 0 ,total = 0;
//	fs8x_rx_frame_t rxData; //Removed by Wood, in order to fix not used warning

	if(fs8xFlash == mode)
	{
		refresh_wd_time = 26946107;//450000*1000/16.7  //refresh:450ms	//wd setting:1024ms
	}
	else if(fs8xNormal == mode)
	{
		refresh_wd_time = 47904191;//800000*1000/16.7  //refresh:800ms	//wd setting:1024ms
	}
	else
	{
		refresh_wd_time = 47904191;//800000*1000/16.7  //refresh:800ms	//wd setting:1024ms
	}

	if(init_fs8x_flag)
	{
		end = STM_0.CNT.R;
		total += (end - start);

		start = STM_0.CNT.R;
		if(total > refresh_wd_time)
		{
			FS8x_WD_Refresh_and_Load_Config();
			fs8x_fs0b_release();
			//PRINTF("wd time: %d \n",total);
			total = 0;
		}
	}
}

static fs8x_status_t fs8x_wd_window_init(fs8x_drv_data_t* drvData)
{
	uint16_t writeData = FS8X_FS_WDW_RECOVERY_DISABLE | FS8X_FS_WDW_DC_31_25 | FS8X_FS_WD_WINDOW_1024MS;
	fs8x_status_t st = fs8xStatusOk;

	st = FS8x_WriteRegister(drvData, true, FS8X_FS_WD_WINDOW_ADDR, writeData);
	st |= FS8x_WriteRegister(drvData, true, FS8X_FS_NOT_WD_WINDOW_ADDR, ~writeData);
	return st;
}

static fs8x_status_t fs8x_wd_cfg_init(fs8x_drv_data_t* drvData)
{
	uint16_t writeData = FS8X_FS_I_WD_ERR_LIMIT_6 | FS8X_FS_I_WD_RFR_LIMIT_6 | FS8X_FS_I_WD_FS_IMPACT_FS0B_RSTB | FS8X_FS_I_WD_RFR_CNT_0 | FS8X_FS_I_WD_ERR_CNT_0;
	fs8x_status_t st = fs8xStatusOk;

	st = FS8x_WriteRegister(drvData, true, FS8X_FS_I_WD_CFG_ADDR, writeData);
	st |= FS8x_WriteRegister(drvData, true, FS8X_FS_I_NOT_WD_CFG_ADDR, ~writeData);
	return st;
}


static fs8x_status_t fs8x_wd_init(void)
{
	fs8x_drv_data_t drvConfig;
	fs8x_status_t st = fs8xStatusOk;

	loadDefaultDriverConfig(&drvConfig);

	st = fs8x_wd_window_init(&drvConfig);
	st |= fs8x_wd_cfg_init(&drvConfig);
	return st;
}


static fs8x_status_t fs8x_fs0b_release(void)
{
    fs8x_drv_data_t drvConfig;
    fs8x_status_t st = fs8xStatusOk;

    loadDefaultDriverConfig(&drvConfig);

    st = FS8x_FS0B_Release(&drvConfig);
    return st;
}



/* Changes seed of LFSR used for watchdog. */
fs8x_status_t FS8x_WD_ChangeSeed(fs8x_drv_data_t *drvData, uint16_t wdSeed)
{
    fs8x_status_t status = fs8xStatusOk;   /* Status variable. */
    fs8x_rx_frame_t rxData;
    uint8_t registerAddress;

    FS_ASSERT(drvData != NULL);

#if (FS8x_WD_TYPE == FS8x_WD_SIMPLE)
    registerAddress = FS8X_FS_WD_ANSWER_ADDR;
#elif (FS8x_WD_TYPE == FS8x_WD_CHALLENGER)
    registerAddress = FS8X_FS_WD_SEED_ADDR;
#endif
    status = FS8x_WriteRegister(drvData, true, registerAddress, wdSeed);
    status |= FS8x_ReadRegister(drvData, true, registerAddress, &rxData);
    if (wdSeed != rxData.readData)
    {
        status = fs8xStatusError;
    }
    return status;
}




//==============================================================
fs8x_status_t FS8x_FS0B_Release(fs8x_drv_data_t* drvData)
{
    fs8x_status_t status;       /* Status variable. */
    fs8x_rx_frame_t rxData;     /* Response to the command. */
    uint16_t fs0b_write = 0;    /* Value to be written to the FS_RELEASE_FS0B register. */
    uint8_t i = 0;              /* Counter. */
    uint16_t diagSafetyMask;    /* Mask for reading of value from the FS_DIAG_SAFETY reg. */
    uint16_t diagSafetyValue;   /* FS_DIAG_SAFETY bits defined by the former mask should have this value. */
    uint8_t errorCounter;       /* Fault Error Counter value. */

    FS_ASSERT(drvData != NULL);

    /* Preconditions check */
    /* Fault Error Counter = 0 */
    status = FS8x_GetFaultErrorCounterValue(drvData, &errorCounter);
    if (status != fs8xStatusOk)
    {
        return status;
    }
    if (errorCounter > 0)
    {
        return fs8xStatusError;
    }
    /* LBIST_OK = ABIST1_OK = ABIST2_OK = 1 */
    status = FS8x_ReadRegister(drvData, true, FS8X_FS_DIAG_SAFETY_ADDR, &rxData);
    if (status != fs8xStatusOk)
    {
        return status;
    }
    diagSafetyMask = (FS8X_FS_LBIST_OK_MASK | FS8X_FS_ABIST2_OK_MASK | FS8X_FS_ABIST1_OK_MASK);
    diagSafetyValue = (FS8X_FS_LBIST_OK_PASS | FS8X_FS_ABIST2_OK_PASS | FS8X_FS_ABIST1_OK_PASS);
    if ((rxData.readData & diagSafetyMask) != diagSafetyValue)
    {
        return fs8xStatusError;
    }
    /* RELEASE_FS0B register filled with ongoing WD_SEED reversed and complemented */
    status = FS8x_ReadRegister(drvData, true, FS8X_FS_WD_SEED_ADDR, &rxData);
    if (status != fs8xStatusOk)
    {
        return status;
    }

    for (i = 0; i < 16; i++)
    {
        fs0b_write |= (uint16_t)(((rxData.readData >> (15 - i)) & 1U) << i);
    }
    fs0b_write = ~fs0b_write;
    return FS8x_WriteRegister(drvData, true, FS8X_FS_RELEASE_FS0B_ADDR, fs0b_write);
}

/* Switches a desired channel to the AMUX pin. */
static fs8x_status_t FS8x_SwitchAMUXchannel(fs8x_drv_data_t *drvData, fs8x_amux_selection_t channelSelection)
{
    FS_ASSERT(drvData != NULL);

    /* Check of AMUX channel selection range. */
    if ((!FS8x_IS_IN_RANGE(channelSelection, fs8xAmuxGnd, fs8xAmuxPsync)
        && !FS8x_IS_IN_RANGE(channelSelection, fs8xAmuxVsup1VoltDiv14, fs8xAmuxWake2VoltDiv14))
        || channelSelection == FS8X_M_AMUX_RESERVED)
    {
        return fs8xStatusError;
    }
    return FS8x_WriteRegister(drvData, false, FS8X_M_AMUX_ADDR, (uint16_t)channelSelection);
}

static fs8x_status_t FS8x_ReadSwitchAMUXchannel(fs8x_drv_data_t *drvData,fs8x_rx_frame_t* rxData)
{
    FS_ASSERT(drvData != NULL);

    /* Check of AMUX channel selection range. */

    return FS8x_ReadRegister(drvData, false, FS8X_M_AMUX_ADDR, rxData);
}

static fs8x_status_t FS8x_SwitchAMUXchannel_and_Load_Config(uint16_t channel)
{
	fs8x_drv_data_t drvConfig;
	fs8x_amux_selection_t ch = (fs8x_amux_selection_t)channel;

	loadDefaultDriverConfig(&drvConfig);
	return 	FS8x_SwitchAMUXchannel(&drvConfig,ch);
}

static fs8x_status_t FS8x_ReadSwitchAMUXchannel_and_Load_Config(fs8x_rx_frame_t* rxData)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);
	return 	FS8x_ReadSwitchAMUXchannel(&drvConfig,rxData);
}
/* Sets state (enable/disable) of the selected voltage regulator. */
fs8x_status_t FS8x_SetRegulatorState(fs8x_drv_data_t *drvData, fs8x_reg_output_t vreg, bool enable)
{
    uint16_t writeValue;                /* Mask and value is the same as we set just 1 bit. */
    uint16_t shift = (uint16_t)vreg;    /* Shift of the mask for disable value. */

    FS_ASSERT(drvData != NULL);

    if (!enable)
    {
        shift += 8; /* Disable value is shifted 8 bits left. */
    }
    writeValue = (uint16_t)(1U << shift);

    /* Mask is not necessary here as bit value of 0 is ignored anyway. */
    return FS8x_UpdateRegister(drvData, false, FS8X_M_REG_CTRL1_ADDR, writeValue, writeValue);
}

/* Reads actual Fault Error Counter value. */
fs8x_status_t FS8x_GetFaultErrorCounterValue(fs8x_drv_data_t *drvData, uint8_t* faultErrorCounterValue)
{
    fs8x_status_t status;   /* Status value. */
    fs8x_rx_frame_t rxData; /* Register received data. */

    FS_ASSERT(drvData != NULL);
    FS_ASSERT(faultErrorCounterValue != NULL);

    status = FS8x_ReadRegister(drvData, true, FS8X_FS_I_FSSM_ADDR, &rxData);
    if (status != fs8xStatusOk)
    {
        return status;
    }

    *faultErrorCounterValue = FS8x_BO_GET_REG_VALUE(rxData.readData, FS8X_FS_I_FLT_ERR_CNT_MASK,
            FS8X_FS_I_FLT_ERR_CNT_SHIFT);

    return fs8xStatusOk;
}

static fs8x_status_t FS8x_SetMClock(fs8x_drv_data_t *drvData,uint16_t data)
{
    FS_ASSERT(drvData != NULL);
    return FS8x_WriteRegister(drvData, false, FS8X_M_CLOCK_ADDR, data);
}

static fs8x_status_t FS8x_set_m_clock_and_Load_Config(void)
{
	fs8x_drv_data_t drvConfig;
	uint16_t data = (FS8X_M_FIN_DIV_DIVIDER_BY_6 | FS8X_M_EXT_FIN_SEL_EN);
	loadDefaultDriverConfig(&drvConfig);
	return 	FS8x_SetMClock(&drvConfig,data);
}

static fs8x_status_t fs8x_external_clock_init(void)
{
	fs8x_status_t st = fs8xStatusOk;
	st = FS8x_set_m_clock_and_Load_Config();
	return st;
}

static fs8x_status_t FS8x_Read_Register_and_Load_Config(fs8x_rx_frame_t* rxData,uint16_t isfs,uint16_t addr)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);
	return 	FS8x_ReadRegister(&drvConfig, isfs, addr, rxData);
}

static fs8x_status_t FS8x_Write_Register_and_Load_Config(uint16_t txData,uint16_t isfs,uint16_t addr)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);
	return 	FS8x_WriteRegister(&drvConfig, isfs, addr, txData);
}




static float conversionDiv2_5(float number)
{
    return number * 2.5F;
}

//static float conversionDiv7_5(float number)   //Removed by Wood, in order to fix not used warning
//{
//    return number * 7.5F;
//}

static float conversionDiv14(float number)
{
    return number * 14.0F;
}

static float conversionTemp(float number)
{
    return (number - FS8x_V_TEMP25) / FS8x_V_TEMP_COEFF + 25;
}


static float get_fs8x_amux_voltage(fs8x_amux_selection_t ch)
{
	fs8x_rx_frame_t rxData;
	uint8_t valid_flag = 0;
	while(!valid_flag)
	{
		FS8x_ReadSwitchAMUXchannel_and_Load_Config(&rxData);
		if(ch == rxData.readData)
		{
			Delay_us(10);//Max Setting time
			valid_flag = 1;
			return fs8x_sample_amux_adc();
		}
		else
		{
			FS8x_SwitchAMUXchannel_and_Load_Config(ch);
		}
	}
	return 0;
}

float get_fs8x_tempature(void)
{
	if(init_fs8x_flag)
	{
		return conversionTemp(get_fs8x_amux_voltage(fs8xAmuxTempSensor));
	}
	return 0;
}

float get_power_supply_voltage(void)
{
    const float voltage_compensation = 0.4; //Voltage difference generated by protection circuit
    if(init_fs8x_flag)
    {
        return get_fs8x_vsup1() + voltage_compensation;
    }
    return 0;
}

float get_fs8x_vsup1(void)
{
	if(init_fs8x_flag)
	{
		return conversionDiv14(get_fs8x_amux_voltage(fs8xAmuxVsup1VoltDiv14));
	}
	return 0;
}

float get_fs8x_vbuck1(void)//dsp core voltage
{
	if(init_fs8x_flag)
	{
		return get_fs8x_amux_voltage(fs8xAmuxVbuck1Volt);
	}
	return 0;
}

float get_fs8x_vldo1(void)//dsp i/o voltage
{
	if(init_fs8x_flag)
	{
		return conversionDiv2_5(get_fs8x_amux_voltage(fs8xAmuxVldo1VoltDiv2_5));
	}
	return 0;
}

float get_fs8x_vpre(void)//rf supply voltage
{
	if(init_fs8x_flag)
	{
		return conversionDiv2_5(get_fs8x_amux_voltage(fs8xAmuxVpreVoltDiv2_5));
	}
	return 0;
}

static uint16_t get_fs8x_wd_seed(void)
{
	fs8x_rx_frame_t rxData = {0};
	uint16_t isFailSafe = 1;
	uint16_t addr = FS8X_FS_WD_SEED_ADDR;
	FS8x_Read_Register_and_Load_Config(&rxData,isFailSafe,addr);
	return rxData.readData;
}

static void fs8x_spread_spectrum_23khz(void)
{
	fs8x_rx_frame_t rxData = {0};
	uint16_t writeData = FS8X_M_MOD_EN_MODULATION_ENABLE | FS8X_M_FIN_DIV_DIVIDER_BY_6 | FS8X_M_MOD_CONF_23KHZ; // Modulation enabled | FIN selection request | 23 kHz
	fs8x_status_t st = fs8xStatusOk;

	st = FS8x_Read_Register_and_Load_Config(&rxData, 0, FS8X_M_CLOCK_ADDR);
	rxData.readData |= writeData;
	st |= FS8x_Write_Register_and_Load_Config(writeData, 0, FS8X_M_CLOCK_ADDR);

	if(st){
		PRINTF("set spread spectrum 23khz failed\n");
	}
}

static void _fs8x_list(char** args, int count)
{
//	float   start, end;
	fs8x_rx_frame_t rxData;

//	start = STM_0.CNT.R;

	if(count == 2)
	{
		if(!strcmp(args[1],"rswch"))
		{
			FS8x_ReadSwitchAMUXchannel_and_Load_Config(&rxData);
			PRINTF("Read Channel:%d\n",rxData.readData);
		}
		else if(!strcmp(args[1],"rtemp"))
		{
			PRINTF("Read Temperature: %f C\n",get_fs8x_tempature());
		}
		else if(!strcmp(args[1],"rvsup1"))
		{
			PRINTF("Read vsup1 voltage: %f V\n",get_fs8x_vsup1());
		}
		else if(!strcmp(args[1],"rvpre"))
		{
			PRINTF("Read vpre voltage: %f V\n",get_fs8x_vpre());
		}
		else if(!strcmp(args[1],"rvldo1"))
		{
			PRINTF("Read vldo1 voltage: %f V\n",get_fs8x_vldo1());
		}
		else if(!strcmp(args[1],"rvbuck1"))
		{
			PRINTF("Read vbuck1 voltage: %f V\n",get_fs8x_vbuck1());
		}
		else if(!strcmp(args[1],"seed"))
		{
			PRINTF("Read seed: %04x \n",get_fs8x_wd_seed());
		}
		else if(!strcmp(args[1],"sleep"))
		{
			FS8x_power_down();
		}
		else if(!strcmp(args[1],"ss23k"))
		{
			fs8x_spread_spectrum_23khz();
		}
	}
	else if((count == 3))
	{
		if(!strcmp(args[1],"wswch"))
		{
			uint16_t val = (uint16_t)strtoul(args[2], NULL, 10);
			if(val <= fs8xAmuxWake2VoltDiv14)
			{
				FS8x_SwitchAMUXchannel_and_Load_Config(val);
				PRINTF("Set Channel:%d\n",val);
			}
		}
	}
	else if(count == 4)
	{
		if(!strcmp(args[1],"rreg"))
		{
			uint16_t isFailSafe = (uint16_t)strtoul(args[2], NULL, 16) & 0x1;
			uint16_t addr = (uint16_t)strtoul(args[3], NULL, 16);
			FS8x_Read_Register_and_Load_Config(&rxData,isFailSafe,addr);
			PRINTF("Read register val:0x%04X\n",rxData.readData);
		}
	}
	else if(count == 5)
	{
		if(!strcmp(args[1],"wreg"))
		{
			uint16_t isFailSafe = (uint16_t)strtoul(args[2], NULL, 16) & 0x1;
			uint16_t addr = (uint16_t)strtoul(args[3], NULL, 16);
			uint16_t txdata = (uint16_t)strtoul(args[4], NULL, 16);
			FS8x_Write_Register_and_Load_Config(txdata,isFailSafe,addr);
			PRINTF("Write register val:0x%04X\n",txdata);
		}
	}
	else
	{
		PRINTF("fs8x console cmd:\n");
		PRINTF("fs8x wswch ch\t(change amux channel,ch need number)\n");
		PRINTF("fs8x rswch\t(read amux channel)\n");
		PRINTF("fs8x rtemp\t(read fs8x temperature)\n");
		PRINTF("fs8x rvsup1\t(read fs8x vsup1 voltage,power supply)\n");
		PRINTF("fs8x rvpre\t(read fs8x vpre voltage,supply rf)\n");
		PRINTF("fs8x rvbuck1\t(read fs8x vbuck1 voltage,supply core)\n");
		PRINTF("fs8x rvldo1\t(read fs8x vldo1 voltage,supply dsp i/o)\n");
		PRINTF("fs8x rreg\t[isFailSafe, address] (read fs8x register)\n");
		PRINTF("fs8x wreg\t[isFailSafe, address, txdata_u16] (write fs8x register)\n");
		PRINTF("fs8x sleep\t(fs8x vreg power down)\n");
		PRINTF("fs8x ss23k\t(fs8x spread spectrum 23khz)\n");
	}
//	end = STM_0.CNT.R;
//	PRINTF("Call function time: %d us\n",(int)((end - start)*16.7/1000));
}



fs8x_init_status get_fs8x_status(void)
{
	return (fs8x_init_status)init_fs8x_flag;
}

void FS8x_init(void)
{
	if(init_fs8x_flag != 1)
	{
		(void)fs8x_spi_init();
		if(FS8X_FS_WD_SEED_DEFAULT == get_fs8x_wd_seed())
		{
			init_fs8x_flag = 1;
			(void)fs8x_external_clock_init();
			(void)fs8x_wd_init();
			(void)fs8x_adc_init();
			(void)FS8x_WD_Refresh_and_Load_Config();
			fs8x_spread_spectrum_23khz();
			console_command_reg("fs8x", _fs8x_list);
		}
	}
}
