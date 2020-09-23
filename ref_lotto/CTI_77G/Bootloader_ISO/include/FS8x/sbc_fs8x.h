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

/** @file sbc_fs8x.h
 * @brief FS8x driver interface.
 *
 * @author nxf44615
 * @version 1.0
 * @date 29-Jun-2018
 * @copyright Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
 */

#ifndef SBC_FS8X_H_
#define SBC_FS8X_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdbool.h>
#include "sbc_fs8x_map.h"
#include "sbc_fs8x_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief Watchdog seed default value. */
#define FS8x_WD_SEED_DEFAULT 0x5AB2U
#define FS8x_COMMUNICATION_MODE (fs8xSPI)
#define FS8x_I2C_MAIN_ADDRESS (0x02U)
/** @addtogroup EnumsDefs
 * @{ */
/** @brief Voltage outputs. Can be used with function @ref FS8x_SetRegulatorState(). */
typedef enum
{
    fs8xBuck1 = 4,  /**< BUCK1 */
    fs8xBuck2 = 3,  /**< BUCK2 */
    fs8xBuck3 = 2,  /**< BUCK3 */
    fs8xLdo1 = 1,   /**< LDO1 */
    fs8xLdo2 = 0,   /**< LDO2 */
    fs8xVBoost = 5, /**< VBOOST */
    fs8xVPre = 6    /**< VPRE */
} fs8x_reg_output_t;

typedef enum
{
	fs8xFlash = 0,
	fs8xNormal = 1
}fs8x_wd_mode;

typedef enum
{
	fs8x_init_err = 0,
	fs8x_init_ok = 1
}fs8x_init_status;

/** AMUX channel selection. Can be used with function @ref FS8x_SwitchAMUXchannel(). */
typedef enum
{
    fs8xAmuxGnd = FS8X_M_AMUX_GND,                                  /**< GND */
    fs8xAmuxVddio = FS8X_M_AMUX_VDDIO,                              /**< VDDIO */
    fs8xAmuxTempSensor = FS8X_M_AMUX_TEMPERATURE_SENSOR,            /**< Temperature sensor */
    fs8xAmuxBandgapMain = FS8X_M_AMUX_BAND_GAP_MAIN,                /**< Main Bandgap */
    fs8xAmuxBandgapFailSafe = FS8X_M_AMUX_BAND_GAP_FAIL_SAFE,       /**< Fail-safe bandgap */
    fs8xAmuxVbuck1Volt = FS8X_M_AMUX_VBUCK1_VOLTAGE,                /**< BUCK1 */
    fs8xAmuxVbuck2Volt = FS8X_M_AMUX_VBUCK2_VOLTAGE,                /**< BUCK2 */
    fs8xAmuxVbuck3VoltDiv2_5 = FS8X_M_AMUX_VBUCK3_VOLTAGE_DIVIDED,  /**< BUCK3 divided by 2.5 */
    fs8xAmuxVpreVoltDiv2_5 = FS8X_M_AMUX_VPRE_VOLTAGE_DIVIDED,      /**< VPRE divided by 2.5 */
    fs8xAmuxVboostVoltDiv2_5 = FS8X_M_AMUX_VBOOST_VOLTAGE_DIVIDED,  /**< VBOOST divided by 2.5 */
    fs8xAmuxVldo1VoltDiv2_5 = FS8X_M_AMUX_VLDO1_VOLTAGE_DIVIDED,    /**< VLDO1 divided by 2.5 */
    fs8xAmuxVldo2VoltDiv2_5 = FS8X_M_AMUX_VLDO2_VOLTAGE_DIVIDED,    /**< VLDO2 divided by 2.5 */
    fs8xAmuxVbosVoltDiv2_5 = FS8X_M_AMUX_VBOS_VOLTAGE_DIVIDED,      /**< VBOS divided by 2.5 */
    fs8xAmuxVsup1VoltDiv7_5 = FS8X_M_AMUX_VSUP1_VOLTAGE_DIVIDED,    /**< VSUP1 divided by 7.5 */
    fs8xAmuxWake1VoltDiv7_5 = FS8X_M_AMUX_WAKE1_VOLTAGE_DIVIDED,    /**< WAKE1 divided by 7.5 */
    fs8xAmuxWake2VoltDiv7_5 = FS8X_M_AMUX_WAKE2_VOLTAGE_DIVIDED,    /**< WAKE2 divided by 7.5 */
    fs8xAmuxVana = FS8X_M_AMUX_VANA,                                /**< Vana */
    fs8xAmuxVdig = FS8X_M_AMUX_VDIG,                                /**< Vdig */
    fs8xAmuxVdigFs = FS8X_M_AMUX_VDIG_FS,                           /**< Vdig_fs */
    fs8xAmuxPsync = FS8X_M_AMUX_PSYNC_VOLTAGE,                      /**< PSYNC */
    fs8xAmuxVsup1VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_VSUP1_VOLTAGE_DIVIDED, /**< VSUP1 divided by 14 */
    fs8xAmuxWake1VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_WAKE1_VOLTAGE_DIVIDED, /**< WAKE1 divided by 14 */
    fs8xAmuxWake2VoltDiv14 = FS8X_M_RATIO_RATIO_14 | FS8X_M_AMUX_WAKE2_VOLTAGE_DIVIDED  /**< WAKE2 divided by 14 */
} fs8x_amux_selection_t;
/** @} */

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
/*******************************************************************************
 * Init
***************************************************************************** */
extern void FS8x_Init(void);
extern void FS8x_Feed(void);
extern bl_u32_t FS8x_Get_Last_Feed_Timestamp();
extern void FS8x_Set_Last_Feed_Timestamp(bl_u32_t timestamp);

#endif /* SBC_FS8X_H_ */
