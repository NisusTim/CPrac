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

#include "bl_rte.h"
#include "FS8x/sbc_fs8x.h"
#include "FS8x/sbc_fs8x_map.h"
#include "FS8x/sbc_fs8x_assert.h"
#include "FS8x/sbc_fs8x_communication.h"
#include "FS8x/sbc_fs8x_common.h"
#include "FS8x/sbc_fs8x_spi.h"


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
static void loadDefaultDriverConfig(fs8x_drv_data_t* drvData);
static fs8x_status_t fs8x_wd_window_init(fs8x_drv_data_t* drvData);
static fs8x_status_t fs8x_wd_cfg_init(fs8x_drv_data_t* drvData);
static fs8x_status_t fs8x_wd_init(void);
static fs8x_status_t FS8x_WD_Refresh(fs8x_drv_data_t* drvData);
static fs8x_status_t FS8x_WD_Refresh_and_Load_Config(void);
static fs8x_status_t FS8x_Read_Register_and_Load_Config(fs8x_rx_frame_t* rxData,uint16_t isfs,uint16_t addr);
static uint16_t get_fs8x_wd_seed(void);
static void fs8x_wd_handle(fs8x_wd_mode mode);
/*******************************************************************************
 * Local Functions Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Local Variables
 ******************************************************************************/
static uint8_t init_fs8x_flag = 0;//1:init,0:not init
static bl_u32_t wd_feed_timestamp = 0;
/*******************************************************************************
 * Global Variables
 ******************************************************************************/


/*******************************************************************************
 * Local Functions - Implementation
 ******************************************************************************/

/*******************************************************************************
 * API - Implementation
 ******************************************************************************/

/* Loads default driver configuration. */
static void loadDefaultDriverConfig(fs8x_drv_data_t* drvData)
{
	(void)fs8x_spi_init();
    drvData->watchdogSeed = FS8x_WD_SEED_DEFAULT;
    drvData->communicationMode = FS8x_COMMUNICATION_MODE;
    drvData->i2cAddressOtp = FS8x_I2C_MAIN_ADDRESS;
}

//===============================================================================
//WD
/* Performs the watchdog refresh. */
static fs8x_status_t FS8x_WD_Refresh(fs8x_drv_data_t* drvData)
{
    fs8x_status_t status = fs8xStatusError;   /* Status variable. */

    FS_ASSERT(drvData != NULL);

    status = FS8x_WriteRegister(drvData, true, FS8X_FS_WD_ANSWER_ADDR,
            drvData->watchdogSeed);

    return status; /* Return error if no WD is selected. */
}

static fs8x_status_t FS8x_WD_Refresh_and_Load_Config(void)
{
	fs8x_drv_data_t drvConfig;

	loadDefaultDriverConfig(&drvConfig);

	return 	FS8x_WD_Refresh(&drvConfig);
}

void fs8x_wd_handle(fs8x_wd_mode mode)
{
	bl_u32_t refresh_wd_time; //800000*1000/16.7  //refresh:800ms	//wd setting:1024ms
	static bl_u32_t end = 0 ,total = 0;

	if(fs8xFlash == mode)
	{
		refresh_wd_time = 26946107;//450000*1000/16.7  //refresh:450ms	//wd setting:1024ms
	}
	else if(fs8xNormal == mode)
	{
		refresh_wd_time = 47904191;//800000*1000/16.7  //refresh:800ms	//wd setting:1024ms
	}

	if(init_fs8x_flag)
	{
		end = STM_0.CNT.R;
		total += (end - wd_feed_timestamp);
		wd_feed_timestamp = STM_0.CNT.R;
		if(total > refresh_wd_time)
		{
			FS8x_WD_Refresh_and_Load_Config();
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

static uint16_t get_fs8x_wd_seed(void)
{
	fs8x_rx_frame_t rxData = {0};
	uint16_t isFailSafe = 1;
	uint16_t addr = FS8X_FS_WD_SEED_ADDR;
	FS8x_Read_Register_and_Load_Config(&rxData,isFailSafe,addr);
	return rxData.readData;
}

void FS8x_Init(void)
{
	(void)fs8x_spi_init();
	if(FS8X_FS_WD_SEED_DEFAULT == get_fs8x_wd_seed())
	{
		init_fs8x_flag = 1;
		(void)fs8x_external_clock_init();
		(void)fs8x_wd_init();
		(void)FS8x_WD_Refresh_and_Load_Config();
	}
}

void FS8x_Feed(void)
{
	fs8x_wd_handle(fs8xFlash);
}

bl_u32_t FS8x_Get_Last_Feed_Timestamp()
{
	return wd_feed_timestamp;
}

void FS8x_Set_Last_Feed_Timestamp(bl_u32_t timestamp)
{
	wd_feed_timestamp = timestamp;
}
