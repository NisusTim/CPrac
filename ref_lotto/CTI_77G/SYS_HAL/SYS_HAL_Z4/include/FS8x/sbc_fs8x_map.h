///*
// * Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
// * All rights reserved.
// *
// * Redistribution and use in source and binary forms, with or without modification,
// * are permitted provided that the following conditions are met:
// *
// * o Redistributions of source code must retain the above copyright notice, this list
// *   of conditions and the following disclaimer.
// *
// * o Redistributions in binary form must reproduce the above copyright notice, this
// *   list of conditions and the following disclaimer in the documentation and/or
// *   other materials provided with the distribution.
// *
// * o Neither the name of the copyright holder nor the names of its
// *   contributors may be used to endorse or promote products derived from this
// *   software without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// */
//
///** @file sbc_fs8x_map.h
// * @brief FS8x register map.
// *
// * This header file contains adresses, masks, shifts and shifted discreete values
// * for all registers of the FS8x. Note that some registers have the same address;
// * the reason is that there are 3 register groups: main, fail-safe and OTP.
// * See datasheet for details.
// *
// * @author nxf44615
// * @version 1.0
// * @date 29-Jun-2018
// * @copyright Copyright (c) 2016 - 2018, NXP Semiconductors, Inc.
// *
// * @warning Some macro names are not compliant with MISRA rule 5.4 if C90 standard is used
// *          (the first 31 characters of macro identifiers are significant).
// *          If C99 standard is used, there is no issue, as the first 63 characters of macro
// *          identifiers are significant.
// */
#ifndef SBC_FS8X_MAP_H__
#define SBC_FS8X_MAP_H__
//
///******************************************************************************/
///* OTP_TRIM_BG1_1 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BG1_1_ADDR       0x00U
//#define FS8X_M_OTP_TRIM_BG1_1_DEFAULT    0x00U
//
//#define FS8X_M_OTP_TRM_ABS_BG1_MASK      0x1FU /*!< N/A */
//
//#define FS8X_M_OTP_TRM_ABS_BG1_SHIFT     0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BG1_2 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BG1_2_ADDR       0x01U
//#define FS8X_M_OTP_TRIM_BG1_2_DEFAULT    0x00U
//
//#define FS8X_M_OTP_TRM_TC_BG1_MASK       0x0FU /*!< N/A */
//
//#define FS8X_M_OTP_TRM_TC_BG1_SHIFT      0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_IREF - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_IREF_ADDR        0x02U
//#define FS8X_M_OTP_TRIM_IREF_DEFAULT     0x00U
//
//#define FS8X_M_OTP_TRM_I1_BG1_MASK       0x07U /*!< N/A */
//#define FS8X_M_OTP_TRM_I2_BG1_MASK       0x38U /*!< N/A */
//
//#define FS8X_M_OTP_TRM_I1_BG1_SHIFT      0x00U /*!< N/A */
//#define FS8X_M_OTP_TRM_I2_BG1_SHIFT      0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_VPRE - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_VPRE_ADDR        0x03U
//#define FS8X_M_OTP_TRIM_VPRE_DEFAULT     0x00U
//
//#define FS8X_M_OTP_TRIM_VPRE_V_MASK      0x0FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_VPRE_ILIM_MASK   0xF0U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_VPRE_V_SHIFT     0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_VPRE_ILIM_SHIFT  0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BOOST - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BOOST_ADDR       0x04U
//#define FS8X_M_OTP_TRIM_BOOST_DEFAULT    0x00U
//
//#define FS8X_M_OTP_TRIM_RATIO_MASK       0x07U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_RATIO_SHIFT      0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK1_1 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK1_1_ADDR     0x05U
//#define FS8X_M_OTP_TRIM_BUCK1_1_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK1_DVS_MASK    0x0FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK1_ILIM_HS_MASK 0x70U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK1_DVS_SHIFT   0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK1_ILIM_HS_SHIFT 0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK1_2 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK1_2_ADDR     0x06U
//#define FS8X_M_OTP_TRIM_BUCK1_2_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK1_LOOP_I_OFFSET_MASK 0x0FU /*!< make spare, N/A */
//#define FS8X_M_OTP_TRIM_BCK1_SC_MASK     0xF0U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK1_LOOP_I_OFFSET_SHIFT 0x00U /*!< make spare, N/A */
//#define FS8X_M_OTP_TRIM_BCK1_SC_SHIFT    0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK1_3 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK1_3_ADDR     0x07U
//#define FS8X_M_OTP_TRIM_BUCK1_3_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK1_RSUM_MASK   0x1FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK1_ZCD_MASK    0x60U /*!< make spare, N/A */
//
//#define FS8X_M_OTP_TRIM_BCK1_RSUM_SHIFT  0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK1_ZCD_SHIFT   0x05U /*!< make spare, N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK1_4 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK1_4_ADDR     0x08U
//#define FS8X_M_OTP_TRIM_BUCK1_4_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK1_TON_MASK    0x1FU /*!< make spare, N/A */
//
//#define FS8X_M_OTP_TRIM_BCK1_TON_SHIFT   0x00U /*!< make spare, N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK2_1 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK2_1_ADDR     0x09U
//#define FS8X_M_OTP_TRIM_BUCK2_1_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK2_DVS_MASK    0x0FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK2_ILIM_HS_MASK 0x70U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK2_DVS_SHIFT   0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK2_ILIM_HS_SHIFT 0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK2_2 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK2_2_ADDR     0x0AU
//#define FS8X_M_OTP_TRIM_BUCK2_2_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK2_LOOP_I_OFFSET_MASK 0x0FU /*!< make spare, N/A */
//#define FS8X_M_OTP_TRIM_BCK2_SC_MASK     0xF0U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK2_LOOP_I_OFFSET_SHIFT 0x00U /*!< make spare, N/A */
//#define FS8X_M_OTP_TRIM_BCK2_SC_SHIFT    0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK2_3 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK2_3_ADDR     0x0BU
//#define FS8X_M_OTP_TRIM_BUCK2_3_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK2_RSUM_MASK   0x1FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK2_ZCD_MASK    0x60U /*!< make spare, N/A */
//
//#define FS8X_M_OTP_TRIM_BCK2_RSUM_SHIFT  0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK2_ZCD_SHIFT   0x05U /*!< make spare, N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK2_4 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK2_4_ADDR     0x0CU
//#define FS8X_M_OTP_TRIM_BUCK2_4_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK2_TON_MASK    0x1FU /*!< make spare, N/A */
//
//#define FS8X_M_OTP_TRIM_BCK2_TON_SHIFT   0x00U /*!< make spare, N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK3_1 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK3_1_ADDR     0x0DU
//#define FS8X_M_OTP_TRIM_BUCK3_1_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK3_REF_LV_MASK 0x07U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK3_ILIM_HS_MASK 0x78U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK3_REF_LV_SHIFT 0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK3_ILIM_HS_SHIFT 0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK3_2 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK3_2_ADDR     0x0EU
//#define FS8X_M_OTP_TRIM_BUCK3_2_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK3_RC_HS_MASK  0x0FU /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK3_SC_MASK     0xF0U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK3_RC_HS_SHIFT 0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_BCK3_SC_SHIFT    0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BUCK3_3 - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_BUCK3_3_ADDR     0x0FU
//#define FS8X_M_OTP_TRIM_BUCK3_3_DEFAULT  0x00U
//
//#define FS8X_M_OTP_TRIM_BCK3_ZCD_MASK    0x03U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_BCK3_ZCD_SHIFT   0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_LDO - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_LDO_ADDR         0x10U
//#define FS8X_M_OTP_TRIM_LDO_DEFAULT      0x00U
//
//#define FS8X_M_OTP_TRIM_LDO1_VREF_MASK   0x07U /*!< N/A */
//#define FS8X_M_OTP_TRIM_LDO2_VREF_MASK   0x38U /*!< N/A */
//
//#define FS8X_M_OTP_TRIM_LDO1_VREF_SHIFT  0x00U /*!< N/A */
//#define FS8X_M_OTP_TRIM_LDO2_VREF_SHIFT  0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_CLOCK - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_TRIM_CLOCK_ADDR       0x11U
//#define FS8X_M_OTP_TRIM_CLOCK_DEFAULT    0x00U
//
//#define FS8X_M_OTP_CLK_TRIM_20M_MAIN_MASK 0x7FU /*!< N/A */
//
//#define FS8X_M_OTP_CLK_TRIM_20M_MAIN_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_M_S0_CRC_LSB - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_M_S0_CRC_LSB_ADDR     0x12U
//#define FS8X_M_OTP_M_S0_CRC_LSB_DEFAULT  0x00U
//
//#define FS8X_M_OTP_OTP_M_S0_CRC_LSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_M_OTP_OTP_M_S0_CRC_LSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_M_S0_CRC_MSB - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_M_S0_CRC_MSB_ADDR     0x13U
//#define FS8X_M_OTP_M_S0_CRC_MSB_DEFAULT  0x00U
//
//#define FS8X_M_OTP_OTP_M_S0_CRC_MSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_M_OTP_OTP_M_S0_CRC_MSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BG_1 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_BG_1_ADDR       0x00U
//#define FS8X_FS_OTP_TRIM_BG_1_DEFAULT    0x00U
//
//#define FS8X_FS_OTP_TRIM_ABS_BG2_MASK    0x1FU /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_ABS_BG2_SHIFT   0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BG_2 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_BG_2_ADDR       0x01U
//#define FS8X_FS_OTP_TRIM_BG_2_DEFAULT    0x00U
//
//#define FS8X_FS_OTP_TRIM_TC_BG2_MASK     0x0FU /*!< N/A */
//#define FS8X_FS_OTP_TRIM_I1_BG2_MASK     0x70U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_TC_BG2_SHIFT    0x00U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_I1_BG2_SHIFT    0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_BG_3 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_BG_3_ADDR       0x02U
//#define FS8X_FS_OTP_TRIM_BG_3_DEFAULT    0x00U
//
//#define FS8X_FS_OTP_TRIM_I2_BG2_MASK     0x07U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_ABS_BG2_BUFFER_MASK 0xF8U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_I2_BG2_SHIFT    0x00U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_ABS_BG2_BUFFER_SHIFT 0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_UVOV_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_UVOV_1_ADDR     0x03U
//#define FS8X_FS_OTP_TRIM_UVOV_1_DEFAULT  0x00U
//
//#define FS8X_FS_OTP_TRIM_VCORE_DVS_MASK  0x0FU /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VCOREMON_MASK   0x70U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_VCORE_DVS_SHIFT 0x00U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VCOREMON_SHIFT  0x04U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_UVOV_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_UVOV_2_ADDR     0x04U
//#define FS8X_FS_OTP_TRIM_UVOV_2_DEFAULT  0x00U
//
//#define FS8X_FS_OTP_TRIM_VDDIOMON_MASK   0x07U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VMON1_MASK      0x38U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_VDDIOMON_SHIFT  0x00U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VMON1_SHIFT     0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_UVOV_3 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_UVOV_3_ADDR     0x05U
//#define FS8X_FS_OTP_TRIM_UVOV_3_DEFAULT  0x00U
//
//#define FS8X_FS_OTP_TRIM_VMON2_MASK      0x07U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VMON3_MASK      0x38U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_VMON2_SHIFT     0x00U /*!< N/A */
//#define FS8X_FS_OTP_TRIM_VMON3_SHIFT     0x03U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_UVOV_4 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_UVOV_4_ADDR     0x06U
//#define FS8X_FS_OTP_TRIM_UVOV_4_DEFAULT  0x00U
//
//#define FS8X_FS_OTP_TRIM_VMON4_MASK      0x07U /*!< N/A */
//
//#define FS8X_FS_OTP_TRIM_VMON4_SHIFT     0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_TRIM_CLOCK - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_TRIM_CLOCK_ADDR      0x07U
//#define FS8X_FS_OTP_TRIM_CLOCK_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_CLK_TRIM_20M_FS_MASK 0x7FU /*!< N/A */
//
//#define FS8X_FS_OTP_CLK_TRIM_20M_FS_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_FS_S0_CRC_LSB - Type: RW                                               */
///******************************************************************************/
//
//#define FS8X_FS_OTP_FS_S0_CRC_LSB_ADDR   0x08U
//#define FS8X_FS_OTP_FS_S0_CRC_LSB_DEFAULT 0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S0_CRC_LSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S0_CRC_LSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_FS_S0_CRC_MSB - Type: RW                                               */
///******************************************************************************/
//
//#define FS8X_FS_OTP_FS_S0_CRC_MSB_ADDR   0x09U
//#define FS8X_FS_OTP_FS_S0_CRC_MSB_DEFAULT 0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S0_CRC_MSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S0_CRC_MSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_CFG_VPRE_1 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_VPRE_1_ADDR       0x14U
//#define FS8X_M_OTP_CFG_VPRE_1_DEFAULT    0x00U
//
//#define FS8X_M_OTP_VPREV_MASK            0x3FU /*!< VPRE output voltage */
//#define FS8X_M_OTP_VPREDEADT_0NS_MASK    0x40U /*!< When a hard short circuit occurs on the Vpre HS, there is a possibility (OTP Bit) to activate voluntary the LS to get a huge amount of current in the VBAT line to the GND and potentially burn a fuse or tighter copper line on the board acting like a fuse. */
//#define FS8X_M_OTP_VPREPWR_PROTECT_MASK  0x80U /*!< Detect cross-conduction by measuring the middle point when HS and LS are driven. */
//
//#define FS8X_M_OTP_VPREV_SHIFT           0x00U /*!< VPRE output voltage */
//#define FS8X_M_OTP_VPREDEADT_0NS_SHIFT   0x06U /*!< When a hard short circuit occurs on the Vpre HS, there is a possibility (OTP Bit) to activate voluntary the LS to get a huge amount of current in the VBAT line to the GND and potentially burn a fuse or tighter copper line on the board acting like a fuse. */
//#define FS8X_M_OTP_VPREPWR_PROTECT_SHIFT 0x07U /*!< Detect cross-conduction by measuring the middle point when HS and LS are driven. */
//
//#define FS8X_M_OTP_VPREV_3_3V            (0x0FU << FS8X_M_OTP_VPREV_SHIFT) /*!< 3.3 V */
//#define FS8X_M_OTP_VPREV_4_1V            (0x17U << FS8X_M_OTP_VPREV_SHIFT) /*!< 4.1 V */
//#define FS8X_M_OTP_VPREV_5_0V            (0x20U << FS8X_M_OTP_VPREV_SHIFT) /*!< 5.0 V */
//
//#define FS8X_M_OTP_VPREDEADT_0NS_0       (0x00U << FS8X_M_OTP_VPREDEADT_0NS_SHIFT) /*!< 0 */
//#define FS8X_M_OTP_VPREDEADT_0NS_1       (0x01U << FS8X_M_OTP_VPREDEADT_0NS_SHIFT) /*!< 1 */
//
//#define FS8X_M_OTP_VPREPWR_PROTECT_DISABLED (0x00U << FS8X_M_OTP_VPREPWR_PROTECT_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_VPREPWR_PROTECT_ENABLED (0x01U << FS8X_M_OTP_VPREPWR_PROTECT_SHIFT) /*!< Enabled */
//
///******************************************************************************/
///* OTP_CFG_VPRE_2 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_VPRE_2_ADDR       0x15U
//#define FS8X_M_OTP_CFG_VPRE_2_DEFAULT    0x00U
//
//#define FS8X_M_OTP_VPRESC_MASK           0x3FU /*!< VPRE slope compensation */
//
//#define FS8X_M_OTP_VPRESC_SHIFT          0x00U /*!< VPRE slope compensation */
//
//#define FS8X_M_OTP_VPRESC_60MV_US        (0x06U << FS8X_M_OTP_VPRESC_SHIFT) /*!< 60 mV/us */
//#define FS8X_M_OTP_VPRESC_70MV_US        (0x07U << FS8X_M_OTP_VPRESC_SHIFT) /*!< 70 mV/us */
//#define FS8X_M_OTP_VPRESC_140MV_US       (0x0EU << FS8X_M_OTP_VPRESC_SHIFT) /*!< 140 mV/us */
//
///******************************************************************************/
///* OTP_CFG_VPRE_3 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_VPRE_3_ADDR       0x16U
//#define FS8X_M_OTP_CFG_VPRE_3_DEFAULT    0x00U
//
//#define FS8X_M_OTP_VPRESRHS_MASK         0x03U /*!< VPRE High Side slew rate control */
//#define FS8X_M_OTP_VPRESRLS_MASK         0x0CU /*!< VPRE Low Side slew rate control */
//#define FS8X_M_OTP_VPRETOFF_MASK         0x30U /*!< VPRE minimum OFF time */
//#define FS8X_M_OTP_VPREILIM_MASK         0xC0U /*!< VPRE current limitation threshold */
//
//#define FS8X_M_OTP_VPRESRHS_SHIFT        0x00U /*!< VPRE High Side slew rate control */
//#define FS8X_M_OTP_VPRESRLS_SHIFT        0x02U /*!< VPRE Low Side slew rate control */
//#define FS8X_M_OTP_VPRETOFF_SHIFT        0x04U /*!< VPRE minimum OFF time */
//#define FS8X_M_OTP_VPREILIM_SHIFT        0x06U /*!< VPRE current limitation threshold */
//
//#define FS8X_M_OTP_VPRESRHS_130MA        (0x00U << FS8X_M_OTP_VPRESRHS_SHIFT) /*!< PU/PD/130mA */
//#define FS8X_M_OTP_VPRESRHS_260MA        (0x01U << FS8X_M_OTP_VPRESRHS_SHIFT) /*!< PU/PD/260mA */
//#define FS8X_M_OTP_VPRESRHS_520MA        (0x02U << FS8X_M_OTP_VPRESRHS_SHIFT) /*!< PU/PD/520mA */
//#define FS8X_M_OTP_VPRESRHS_900MA        (0x03U << FS8X_M_OTP_VPRESRHS_SHIFT) /*!< PU/PD/900mA */
//
//#define FS8X_M_OTP_VPRESRLS_130MA        (0x00U << FS8X_M_OTP_VPRESRLS_SHIFT) /*!< PU/PD/130mA */
//#define FS8X_M_OTP_VPRESRLS_260MA        (0x01U << FS8X_M_OTP_VPRESRLS_SHIFT) /*!< PU/PD/260mA */
//#define FS8X_M_OTP_VPRESRLS_520MA        (0x02U << FS8X_M_OTP_VPRESRLS_SHIFT) /*!< PU/PD/520mA */
//#define FS8X_M_OTP_VPRESRLS_900MA        (0x03U << FS8X_M_OTP_VPRESRLS_SHIFT) /*!< PU/PD/900mA */
//
//#define FS8X_M_OTP_VPRETOFF_40NS         (0x02U << FS8X_M_OTP_VPRETOFF_SHIFT) /*!< 40 ns */
//
//#define FS8X_M_OTP_VPREILIM_50MV         (0x00U << FS8X_M_OTP_VPREILIM_SHIFT) /*!< 50 mV */
//#define FS8X_M_OTP_VPREILIM_80MV         (0x01U << FS8X_M_OTP_VPREILIM_SHIFT) /*!< 80 mV */
//#define FS8X_M_OTP_VPREILIM_120MV        (0x02U << FS8X_M_OTP_VPREILIM_SHIFT) /*!< 120 mV */
//#define FS8X_M_OTP_VPREILIM_150MV        (0x03U << FS8X_M_OTP_VPREILIM_SHIFT) /*!< 150 mV */
//
///******************************************************************************/
///* OTP_CFG_BOOST_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BOOST_1_ADDR      0x17U
//#define FS8X_M_OTP_CFG_BOOST_1_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VBSTV_MASK            0x0FU /*!< VBOOST output voltage */
//#define FS8X_M_OTP_VBOS_VBOOST_DIS_MASK  0x10U /*!< VBOOST path to VBOS. Disable VBOOST path to VBOS to gain efficiency if VSUPCFG=1 (Vpre >4.5V) or BOOST is disabled */
//#define FS8X_M_OTP_OTP_SPARE0_MASK       0xE0U /*!< N/A */
//
//#define FS8X_M_OTP_VBSTV_SHIFT           0x00U /*!< VBOOST output voltage */
//#define FS8X_M_OTP_VBOS_VBOOST_DIS_SHIFT 0x04U /*!< VBOOST path to VBOS. Disable VBOOST path to VBOS to gain efficiency if VSUPCFG=1 (Vpre >4.5V) or BOOST is disabled */
//#define FS8X_M_OTP_OTP_SPARE0_SHIFT      0x05U /*!< N/A */
//
//#define FS8X_M_OTP_VBSTV_5_0V            (0x06U << FS8X_M_OTP_VBSTV_SHIFT) /*!< 5.0 V */
//#define FS8X_M_OTP_VBSTV_5_74V           (0x0DU << FS8X_M_OTP_VBSTV_SHIFT) /*!< 5.74 V */
//
//#define FS8X_M_OTP_VBOS_VBOOST_DIS_ENABLED (0x00U << FS8X_M_OTP_VBOS_VBOOST_DIS_SHIFT) /*!< Enabled */
//#define FS8X_M_OTP_VBOS_VBOOST_DIS_DISABLED (0x01U << FS8X_M_OTP_VBOS_VBOOST_DIS_SHIFT) /*!< Disabled */
//
//#define FS8X_M_OTP_OTP_SPARE0_0          (0x00U << FS8X_M_OTP_OTP_SPARE0_SHIFT) /*!< 0 */
//
///******************************************************************************/
///* OTP_CFG_BOOST_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BOOST_2_ADDR      0x18U
//#define FS8X_M_OTP_CFG_BOOST_2_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VBSTSC_MASK           0x1FU /*!< VBOOST slope compensation */
//#define FS8X_M_OTP_VBSTTONTIME_MASK      0x60U /*!< BOOST minimum ON time */
//#define FS8X_M_OTP_BOOSTEN_MASK          0x80U /*!< BOOST enable */
//
//#define FS8X_M_OTP_VBSTSC_SHIFT          0x00U /*!< VBOOST slope compensation */
//#define FS8X_M_OTP_VBSTTONTIME_SHIFT     0x05U /*!< BOOST minimum ON time */
//#define FS8X_M_OTP_BOOSTEN_SHIFT         0x07U /*!< BOOST enable */
//
//#define FS8X_M_OTP_VBSTSC_158MV_US       (0x06U << FS8X_M_OTP_VBSTSC_SHIFT) /*!< 158 mV/us */
//#define FS8X_M_OTP_VBSTSC_140MV_US       (0x0CU << FS8X_M_OTP_VBSTSC_SHIFT) /*!< 140 mV/us */
//#define FS8X_M_OTP_VBSTSC_79MV_US        (0x0EU << FS8X_M_OTP_VBSTSC_SHIFT) /*!< 79 mV/us */
//
//#define FS8X_M_OTP_VBSTTONTIME_60NS      (0x00U << FS8X_M_OTP_VBSTTONTIME_SHIFT) /*!< 60 ns */
//
//#define FS8X_M_OTP_BOOSTEN_DISABLED      (0x00U << FS8X_M_OTP_BOOSTEN_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_BOOSTEN_ENABLED       (0x01U << FS8X_M_OTP_BOOSTEN_SHIFT) /*!< Enabled */
//
///******************************************************************************/
///* OTP_CFG_BOOST_3 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BOOST_3_ADDR      0x19U
//#define FS8X_M_OTP_CFG_BOOST_3_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VBSTSR_MASK           0x03U /*!< VBOOST Low Side slew rate control */
//#define FS8X_M_OTP_VBSTILIM_MASK         0x0CU /*!< VBOOST current limitation */
//#define FS8X_M_OTP_VBSTCCOMP_MASK        0x30U /*!< VBOOST Compensation Network Capacitor Ccomp */
//#define FS8X_M_OTP_VBSTRCOMP_MASK        0xC0U /*!< VBOOST Compensation Network Resistor Rcomp */
//
//#define FS8X_M_OTP_VBSTSR_SHIFT          0x00U /*!< VBOOST Low Side slew rate control */
//#define FS8X_M_OTP_VBSTILIM_SHIFT        0x02U /*!< VBOOST current limitation */
//#define FS8X_M_OTP_VBSTCCOMP_SHIFT       0x04U /*!< VBOOST Compensation Network Capacitor Ccomp */
//#define FS8X_M_OTP_VBSTRCOMP_SHIFT       0x06U /*!< VBOOST Compensation Network Resistor Rcomp */
//
//#define FS8X_M_OTP_VBSTSR_300V_US        (0x02U << FS8X_M_OTP_VBSTSR_SHIFT) /*!< 300 V/us */
//#define FS8X_M_OTP_VBSTSR_500V_US        (0x03U << FS8X_M_OTP_VBSTSR_SHIFT) /*!< 500 V/us */
//
//#define FS8X_M_OTP_VBSTILIM_2A           (0x01U << FS8X_M_OTP_VBSTILIM_SHIFT) /*!< 2 A */
//
//#define FS8X_M_OTP_VBSTCCOMP_125PF       (0x00U << FS8X_M_OTP_VBSTCCOMP_SHIFT) /*!< 125 pF */
//
//#define FS8X_M_OTP_VBSTRCOMP_750KOHMS    (0x00U << FS8X_M_OTP_VBSTRCOMP_SHIFT) /*!< 750 Kohms */
//#define FS8X_M_OTP_VBSTRCOMP_500KOHMS    (0x01U << FS8X_M_OTP_VBSTRCOMP_SHIFT) /*!< 500 Kohms */
//
///******************************************************************************/
///* OTP_CFG_BUCK1_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK1_1_ADDR      0x1AU
//#define FS8X_M_OTP_CFG_BUCK1_1_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB1V_MASK             0xFFU /*!< VBUCK1 output voltage */
//
//#define FS8X_M_OTP_VB1V_SHIFT            0x00U /*!< VBUCK1 output voltage */
//
//#define FS8X_M_OTP_VB1V_0_8V             (0x40U << FS8X_M_OTP_VB1V_SHIFT) /*!< 0.80 V */
//#define FS8X_M_OTP_VB1V_0_9V             (0x50U << FS8X_M_OTP_VB1V_SHIFT) /*!< 0.90 V */
//#define FS8X_M_OTP_VB1V_1_00V            (0x60U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.00 V */
//#define FS8X_M_OTP_VB1V_1_10V            (0x70U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.10 V */
//#define FS8X_M_OTP_VB1V_1_20V            (0x80U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.20 V */
//#define FS8X_M_OTP_VB1V_1_25V            (0x88U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.25 V */
//#define FS8X_M_OTP_VB1V_1_30V            (0x90U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.30 V */
//#define FS8X_M_OTP_VB1V_1_35V            (0x98U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.35 V */
//#define FS8X_M_OTP_VB1V_1_40V            (0xA0U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.40 V */
//#define FS8X_M_OTP_VB1V_1_50V            (0xB0U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.50 V */
//#define FS8X_M_OTP_VB1V_1_80V            (0xB1U << FS8X_M_OTP_VB1V_SHIFT) /*!< 1.80 V */
//
///******************************************************************************/
///* OTP_CFG_BUCK1_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK1_2_ADDR      0x1BU
//#define FS8X_M_OTP_CFG_BUCK1_2_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB12MULTIPH_MASK      0x01U /*!< VBUCK1 & VBUCK2 multiphase operation enable */
//#define FS8X_M_OTP_VB1SWILIM_MASK        0x06U /*!< VBUCK1 current limitation */
//#define FS8X_M_OTP_VB1INDOPT_MASK        0x18U /*!< BUCK1 inductor selection */
//
//#define FS8X_M_OTP_VB12MULTIPH_SHIFT     0x00U /*!< VBUCK1 & VBUCK2 multiphase operation enable */
//#define FS8X_M_OTP_VB1SWILIM_SHIFT       0x01U /*!< VBUCK1 current limitation */
//#define FS8X_M_OTP_VB1INDOPT_SHIFT       0x03U /*!< BUCK1 inductor selection */
//
//#define FS8X_M_OTP_VB12MULTIPH_DISABLED  (0x00U << FS8X_M_OTP_VB12MULTIPH_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_VB12MULTIPH_ENABLED   (0x01U << FS8X_M_OTP_VB12MULTIPH_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_VB1SWILIM_2_6A        (0x01U << FS8X_M_OTP_VB1SWILIM_SHIFT) /*!< 2.6 A */
//#define FS8X_M_OTP_VB1SWILIM_4_5A        (0x03U << FS8X_M_OTP_VB1SWILIM_SHIFT) /*!< 4.5 A */
//
//#define FS8X_M_OTP_VB1INDOPT_1UH         (0x00U << FS8X_M_OTP_VB1INDOPT_SHIFT) /*!< 1 uH */
//
///******************************************************************************/
///* OTP_CFG_BUCK2_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK2_1_ADDR      0x1CU
//#define FS8X_M_OTP_CFG_BUCK2_1_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB2V_MASK             0xFFU /*!< VBUCK2 output voltage */
//
//#define FS8X_M_OTP_VB2V_SHIFT            0x00U /*!< VBUCK2 output voltage */
//
//#define FS8X_M_OTP_VB2V_0_8V             (0x40U << FS8X_M_OTP_VB2V_SHIFT) /*!< 0.80 V */
//#define FS8X_M_OTP_VB2V_0_9V             (0x50U << FS8X_M_OTP_VB2V_SHIFT) /*!< 0.90 V */
//#define FS8X_M_OTP_VB2V_1_00V            (0x60U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.00 V */
//#define FS8X_M_OTP_VB2V_1_10V            (0x70U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.10 V */
//#define FS8X_M_OTP_VB2V_1_20V            (0x80U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.20 V */
//#define FS8X_M_OTP_VB2V_1_25V            (0x88U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.25 V */
//#define FS8X_M_OTP_VB2V_1_30V            (0x90U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.30 V */
//#define FS8X_M_OTP_VB2V_1_35V            (0x98U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.35 V */
//#define FS8X_M_OTP_VB2V_1_40V            (0xA0U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.40 V */
//#define FS8X_M_OTP_VB2V_1_50V            (0xB0U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.50 V */
//#define FS8X_M_OTP_VB2V_1_80V            (0xB1U << FS8X_M_OTP_VB2V_SHIFT) /*!< 1.80 V */
//
///******************************************************************************/
///* OTP_CFG_BUCK2_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK2_2_ADDR      0x1DU
//#define FS8X_M_OTP_CFG_BUCK2_2_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB3_CTRL_GM_MASK      0x01U /*!< BUCK3 Gain control */
//#define FS8X_M_OTP_VB3_CTRL_RC_MASK      0x02U /*!< BUCK3 Compensation Network */
//#define FS8X_M_OTP_VB2SWILIM_MASK        0x0CU /*!< VBUCK2 current limitation */
//#define FS8X_M_OTP_BUCK2EN_MASK          0x10U /*!< BUCK2 enable */
//#define FS8X_M_OTP_VB2INDOPT_MASK        0x60U /*!< BUCK2 inductor selection. */
//
//#define FS8X_M_OTP_VB3_CTRL_GM_SHIFT     0x00U /*!< BUCK3 Gain control */
//#define FS8X_M_OTP_VB3_CTRL_RC_SHIFT     0x01U /*!< BUCK3 Compensation Network */
//#define FS8X_M_OTP_VB2SWILIM_SHIFT       0x02U /*!< VBUCK2 current limitation */
//#define FS8X_M_OTP_BUCK2EN_SHIFT         0x04U /*!< BUCK2 enable */
//#define FS8X_M_OTP_VB2INDOPT_SHIFT       0x05U /*!< BUCK2 inductor selection. */
//
//#define FS8X_M_OTP_VB3_CTRL_GM_DEFAULT   (0x00U << FS8X_M_OTP_VB3_CTRL_GM_SHIFT) /*!< Default */
//#define FS8X_M_OTP_VB3_CTRL_GM_1         (0x01U << FS8X_M_OTP_VB3_CTRL_GM_SHIFT) /*!< 1 */
//
//#define FS8X_M_OTP_VB3_CTRL_RC_DEFAULT   (0x00U << FS8X_M_OTP_VB3_CTRL_RC_SHIFT) /*!< Default */
//
//#define FS8X_M_OTP_VB2SWILIM_2_6A        (0x01U << FS8X_M_OTP_VB2SWILIM_SHIFT) /*!< 2.6A */
//#define FS8X_M_OTP_VB2SWILIM_4_5A        (0x03U << FS8X_M_OTP_VB2SWILIM_SHIFT) /*!< 4.5A */
//
//#define FS8X_M_OTP_BUCK2EN_DISABLED      (0x00U << FS8X_M_OTP_BUCK2EN_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_BUCK2EN_ENABLED       (0x01U << FS8X_M_OTP_BUCK2EN_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_VB2INDOPT_1UH         (0x00U << FS8X_M_OTP_VB2INDOPT_SHIFT) /*!< 1uH */
//
///******************************************************************************/
///* OTP_CFG_BUCK3_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK3_1_ADDR      0x1EU
//#define FS8X_M_OTP_CFG_BUCK3_1_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB3V_MASK             0x1FU /*!< VBUCK3 output voltage */
//#define FS8X_M_OTP_VB3INDOPT_MASK        0x60U /*!< BUCK3 inductor selection */
//#define FS8X_M_OTP_BUCK3EN_MASK          0x80U /*!< BUCK3 enable */
//
//#define FS8X_M_OTP_VB3V_SHIFT            0x00U /*!< VBUCK3 output voltage */
//#define FS8X_M_OTP_VB3INDOPT_SHIFT       0x05U /*!< BUCK3 inductor selection */
//#define FS8X_M_OTP_BUCK3EN_SHIFT         0x07U /*!< BUCK3 enable */
//
//#define FS8X_M_OTP_VB3V_1_0V             (0x00U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.0 V */
//#define FS8X_M_OTP_VB3V_1_1V             (0x01U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.1 V */
//#define FS8X_M_OTP_VB3V_1_2V             (0x02U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.2 V */
//#define FS8X_M_OTP_VB3V_1_25V            (0x03U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.25 V */
//#define FS8X_M_OTP_VB3V_1_3V             (0x04U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.3 V */
//#define FS8X_M_OTP_VB3V_1_35V            (0x05U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.35 V */
//#define FS8X_M_OTP_VB3V_1_5V             (0x06U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.5 V */
//#define FS8X_M_OTP_VB3V_1_6V             (0x07U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.6 V */
//#define FS8X_M_OTP_VB3V_1_8V             (0x08U << FS8X_M_OTP_VB3V_SHIFT) /*!< 1.8 V */
//#define FS8X_M_OTP_VB3V_2_3V             (0x0EU << FS8X_M_OTP_VB3V_SHIFT) /*!< 2.3 V */
//#define FS8X_M_OTP_VB3V_2_5V             (0x10U << FS8X_M_OTP_VB3V_SHIFT) /*!< 2.5 V */
//#define FS8X_M_OTP_VB3V_3_3V             (0x15U << FS8X_M_OTP_VB3V_SHIFT) /*!< 3.3 V */
//
//#define FS8X_M_OTP_VB3INDOPT_1UH         (0x00U << FS8X_M_OTP_VB3INDOPT_SHIFT) /*!< 1uH */
//
//#define FS8X_M_OTP_BUCK3EN_DISABLED      (0x00U << FS8X_M_OTP_BUCK3EN_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_BUCK3EN_ENABLED       (0x01U << FS8X_M_OTP_BUCK3EN_SHIFT) /*!< Enabled */
//
///******************************************************************************/
///* OTP_CFG_BUCK3_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_BUCK3_2_ADDR      0x1FU
//#define FS8X_M_OTP_CFG_BUCK3_2_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VB3SWILIM_MASK        0x03U /*!< VBUCK3 current limitation */
//#define FS8X_M_OTP_VB1GMCOMP_MASK        0x1CU /*!< BUCK1 Compensation Network */
//#define FS8X_M_OTP_VB2GMCOMP_MASK        0xE0U /*!< BUCK2 Compensation Network */
//
//#define FS8X_M_OTP_VB3SWILIM_SHIFT       0x00U /*!< VBUCK3 current limitation */
//#define FS8X_M_OTP_VB1GMCOMP_SHIFT       0x02U /*!< BUCK1 Compensation Network */
//#define FS8X_M_OTP_VB2GMCOMP_SHIFT       0x05U /*!< BUCK2 Compensation Network */
//
//#define FS8X_M_OTP_VB3SWILIM_2_6A        (0x01U << FS8X_M_OTP_VB3SWILIM_SHIFT) /*!< 2.6 A */
//#define FS8X_M_OTP_VB3SWILIM_4_5A        (0x03U << FS8X_M_OTP_VB3SWILIM_SHIFT) /*!< 4.5 A */
//
//#define FS8X_M_OTP_VB1GMCOMP_16_25GM     (0x01U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 16.25 GM */
//#define FS8X_M_OTP_VB1GMCOMP_32_5GM      (0x02U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 32.5 GM */
//#define FS8X_M_OTP_VB1GMCOMP_48_75GM     (0x03U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 48.75 GM */
//#define FS8X_M_OTP_VB1GMCOMP_65GM        (0x04U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 65 GM */
//#define FS8X_M_OTP_VB1GMCOMP_81_25GM     (0x05U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 81.25 GM */
//#define FS8X_M_OTP_VB1GMCOMP_97_5GM      (0x06U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 97.5 GM */
//#define FS8X_M_OTP_VB1GMCOMP_113_75GM    (0x07U << FS8X_M_OTP_VB1GMCOMP_SHIFT) /*!< 113.75 GM */
//
//#define FS8X_M_OTP_VB2GMCOMP_16_25GM     (0x01U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 16.25 GM */
//#define FS8X_M_OTP_VB2GMCOMP_32_5GM      (0x02U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 32.5 GM */
//#define FS8X_M_OTP_VB2GMCOMP_48_75GM     (0x03U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 48.75 GM */
//#define FS8X_M_OTP_VB2GMCOMP_65GM        (0x04U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 65 GM */
//#define FS8X_M_OTP_VB2GMCOMP_81_25GM     (0x05U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 81.25 GM */
//#define FS8X_M_OTP_VB2GMCOMP_97_5GM      (0x06U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 97.5 GM */
//#define FS8X_M_OTP_VB2GMCOMP_113_75GM    (0x07U << FS8X_M_OTP_VB2GMCOMP_SHIFT) /*!< 113.75 GM */
//
///******************************************************************************/
///* OTP_CFG_LDO - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_LDO_ADDR          0x20U
//#define FS8X_M_OTP_CFG_LDO_DEFAULT       0x00U
//
//#define FS8X_M_OTP_LDO1V_MASK            0x07U /*!< VLDO1 output voltage */
//#define FS8X_M_OTP_LDO1ILIM_MASK         0x08U /*!< VLDO1 current limitation */
//#define FS8X_M_OTP_LDO2V_MASK            0x70U /*!< VLDO2 output voltage */
//#define FS8X_M_OTP_LDO2ILIM_MASK         0x80U /*!< VLDO2 current limitation */
//
//#define FS8X_M_OTP_LDO1V_SHIFT           0x00U /*!< VLDO1 output voltage */
//#define FS8X_M_OTP_LDO1ILIM_SHIFT        0x03U /*!< VLDO1 current limitation */
//#define FS8X_M_OTP_LDO2V_SHIFT           0x04U /*!< VLDO2 output voltage */
//#define FS8X_M_OTP_LDO2ILIM_SHIFT        0x07U /*!< VLDO2 current limitation */
//
//#define FS8X_M_OTP_LDO1V_1_1V            (0x00U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 1.1 V */
//#define FS8X_M_OTP_LDO1V_1_2V            (0x01U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 1.2 V */
//#define FS8X_M_OTP_LDO1V_1_6V            (0x02U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 1.6 V */
//#define FS8X_M_OTP_LDO1V_1_8V            (0x03U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 1.8 V */
//#define FS8X_M_OTP_LDO1V_2_5V            (0x04U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 2.5 V */
//#define FS8X_M_OTP_LDO1V_3_0V            (0x05U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 3.0 V */
//#define FS8X_M_OTP_LDO1V_3_3V            (0x06U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 3.3 V */
//#define FS8X_M_OTP_LDO1V_5_0V            (0x07U << FS8X_M_OTP_LDO1V_SHIFT) /*!< 5.0 V */
//
//#define FS8X_M_OTP_LDO1ILIM_400MA        (0x00U << FS8X_M_OTP_LDO1ILIM_SHIFT) /*!< 400 mA */
//#define FS8X_M_OTP_LDO1ILIM_150MA        (0x01U << FS8X_M_OTP_LDO1ILIM_SHIFT) /*!< 150 mA */
//
//#define FS8X_M_OTP_LDO2V_1_1V            (0x00U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 1.1 V */
//#define FS8X_M_OTP_LDO2V_1_2V            (0x01U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 1.2 V */
//#define FS8X_M_OTP_LDO2V_1_6V            (0x02U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 1.6 V */
//#define FS8X_M_OTP_LDO2V_1_8V            (0x03U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 1.8 V */
//#define FS8X_M_OTP_LDO2V_2_5V            (0x04U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 2.5 V */
//#define FS8X_M_OTP_LDO2V_3_0V            (0x05U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 3.0 V */
//#define FS8X_M_OTP_LDO2V_3_3V            (0x06U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 3.3 V */
//#define FS8X_M_OTP_LDO2V_5_0V            (0x07U << FS8X_M_OTP_LDO2V_SHIFT) /*!< 5.0 V */
//
//#define FS8X_M_OTP_LDO2ILIM_400MA        (0x00U << FS8X_M_OTP_LDO2ILIM_SHIFT) /*!< 400 mA */
//#define FS8X_M_OTP_LDO2ILIM_150MA        (0x01U << FS8X_M_OTP_LDO2ILIM_SHIFT) /*!< 150 mA */
//
///******************************************************************************/
///* OTP_CFG_SEQ_1 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_SEQ_1_ADDR        0x21U
//#define FS8X_M_OTP_CFG_SEQ_1_DEFAULT     0x00U
//
//#define FS8X_M_OTP_VB1S_MASK             0x07U /*!< BUCK1 sequencing slot */
//#define FS8X_M_OTP_VB2S_MASK             0x38U /*!< BUCK2 sequencing slot */
//
//#define FS8X_M_OTP_VB1S_SHIFT            0x00U /*!< BUCK1 sequencing slot */
//#define FS8X_M_OTP_VB2S_SHIFT            0x03U /*!< BUCK2 sequencing slot */
//
//#define FS8X_M_OTP_VB1S_SLOT0            (0x00U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 0 */
//#define FS8X_M_OTP_VB1S_SLOT1            (0x01U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 1 */
//#define FS8X_M_OTP_VB1S_SLOT2            (0x02U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 2 */
//#define FS8X_M_OTP_VB1S_SLOT3            (0x03U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 3 */
//#define FS8X_M_OTP_VB1S_SLOT4            (0x04U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 4 */
//#define FS8X_M_OTP_VB1S_SLOT5            (0x05U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 5 */
//#define FS8X_M_OTP_VB1S_SLOT6            (0x06U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Start and Stop in Slot 6 */
//#define FS8X_M_OTP_VB1S_NOTSTART         (0x07U << FS8X_M_OTP_VB1S_SHIFT) /*!< Regulator Does not Start (Enabled by SPI) */
//
//#define FS8X_M_OTP_VB2S_SLOT0            (0x00U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 0 */
//#define FS8X_M_OTP_VB2S_SLOT1            (0x01U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 1 */
//#define FS8X_M_OTP_VB2S_SLOT2            (0x02U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 2 */
//#define FS8X_M_OTP_VB2S_SLOT3            (0x03U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 3 */
//#define FS8X_M_OTP_VB2S_SLOT4            (0x04U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 4 */
//#define FS8X_M_OTP_VB2S_SLOT5            (0x05U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 5 */
//#define FS8X_M_OTP_VB2S_SLOT6            (0x06U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Start and Stop in Slot 6 */
//#define FS8X_M_OTP_VB2S_NOTSTART         (0x07U << FS8X_M_OTP_VB2S_SHIFT) /*!< Regulator Does not Start (Enabled by SPI) */
//
///******************************************************************************/
///* OTP_CFG_SEQ_2 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_SEQ_2_ADDR        0x22U
//#define FS8X_M_OTP_CFG_SEQ_2_DEFAULT     0x00U
//
//#define FS8X_M_OTP_LDO1S_MASK            0x07U /*!< LDO1 sequencing slot */
//#define FS8X_M_OTP_LDO2S_MASK            0x38U /*!< LDO2 sequencing slot */
//
//#define FS8X_M_OTP_LDO1S_SHIFT           0x00U /*!< LDO1 sequencing slot */
//#define FS8X_M_OTP_LDO2S_SHIFT           0x03U /*!< LDO2 sequencing slot */
//
//#define FS8X_M_OTP_LDO1S_SLOT0           (0x00U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 0 */
//#define FS8X_M_OTP_LDO1S_SLOT1           (0x01U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 1 */
//#define FS8X_M_OTP_LDO1S_SLOT2           (0x02U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 2 */
//#define FS8X_M_OTP_LDO1S_SLOT3           (0x03U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 3 */
//#define FS8X_M_OTP_LDO1S_SLOT4           (0x04U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 4 */
//#define FS8X_M_OTP_LDO1S_SLOT5           (0x05U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 5 */
//#define FS8X_M_OTP_LDO1S_SLOT6           (0x06U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Start and Stop in Slot 6 */
//#define FS8X_M_OTP_LDO1S_NOTSTART        (0x07U << FS8X_M_OTP_LDO1S_SHIFT) /*!< Regulator Does not Start (Enabled by SPI) */
//
//#define FS8X_M_OTP_LDO2S_SLOT0           (0x00U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 0 */
//#define FS8X_M_OTP_LDO2S_SLOT1           (0x01U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 1 */
//#define FS8X_M_OTP_LDO2S_SLOT2           (0x02U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 2 */
//#define FS8X_M_OTP_LDO2S_SLOT3           (0x03U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 3 */
//#define FS8X_M_OTP_LDO2S_SLOT4           (0x04U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 4 */
//#define FS8X_M_OTP_LDO2S_SLOT5           (0x05U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 5 */
//#define FS8X_M_OTP_LDO2S_SLOT6           (0x06U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Start and Stop in Slot 6 */
//#define FS8X_M_OTP_LDO2S_NOTSTART        (0x07U << FS8X_M_OTP_LDO2S_SHIFT) /*!< Regulator Does not Start (Enabled by SPI) */
//
///******************************************************************************/
///* OTP_CFG_SEQ_3 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_SEQ_3_ADDR        0x23U
//#define FS8X_M_OTP_CFG_SEQ_3_DEFAULT     0x00U
//
//#define FS8X_M_OTP_VB3S_MASK             0x07U /*!< BUCK3 sequencing slot */
//
//#define FS8X_M_OTP_VB3S_SHIFT            0x00U /*!< BUCK3 sequencing slot */
//
//#define FS8X_M_OTP_VB3S_SLOT0            (0x00U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 0 */
//#define FS8X_M_OTP_VB3S_SLOT1            (0x01U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 1 */
//#define FS8X_M_OTP_VB3S_SLOT2            (0x02U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 2 */
//#define FS8X_M_OTP_VB3S_SLOT3            (0x03U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 3 */
//#define FS8X_M_OTP_VB3S_SLOT4            (0x04U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 4 */
//#define FS8X_M_OTP_VB3S_SLOT5            (0x05U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 5 */
//#define FS8X_M_OTP_VB3S_SLOT6            (0x06U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Start and Stop in Slot 6 */
//#define FS8X_M_OTP_VB3S_NOTSTART         (0x07U << FS8X_M_OTP_VB3S_SHIFT) /*!< Regulator Does not Start (Enabled by SPI) */
//
///******************************************************************************/
///* OTP_CFG_CLOCK_1 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_CLOCK_1_ADDR      0x24U
//#define FS8X_M_OTP_CFG_CLOCK_1_DEFAULT   0x00U
//
//#define FS8X_M_OTP_CLK_DIV2_MASK         0x07U /*!< Divider 2 setting */
//#define FS8X_M_OTP_VPRE_PH_MASK          0x38U /*!< VPRE phase (delay) selection */
//
//#define FS8X_M_OTP_CLK_DIV2_SHIFT        0x00U /*!< Divider 2 setting */
//#define FS8X_M_OTP_VPRE_PH_SHIFT         0x03U /*!< VPRE phase (delay) selection */
//
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE8      (0x00U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 8 - CLK=2.5MHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE10     (0x01U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 10 - CLK=2MHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE12     (0x02U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 12 - CLK=1.67MHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE14     (0x03U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 14 - CLK=1.43MHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE44     (0x04U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 44 - CLK=455KHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE46     (0x05U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 46 - CLK=435KHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE48     (0x06U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 48 - CLK=417KHz */
//#define FS8X_M_OTP_CLK_DIV2_DIVIDE64     (0x07U << FS8X_M_OTP_CLK_DIV2_SHIFT) /*!< divide by 64 - CLK=312.5KHz */
//
//#define FS8X_M_OTP_VPRE_PH_NODELAY       (0x00U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< no delay */
//#define FS8X_M_OTP_VPRE_PH_DELAY1        (0x01U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 1 */
//#define FS8X_M_OTP_VPRE_PH_DELAY2        (0x02U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 2 */
//#define FS8X_M_OTP_VPRE_PH_DELAY3        (0x03U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 3 */
//#define FS8X_M_OTP_VPRE_PH_DELAY4        (0x04U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 4 */
//#define FS8X_M_OTP_VPRE_PH_DELAY5        (0x05U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 5 */
//#define FS8X_M_OTP_VPRE_PH_DELAY6        (0x06U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 6 */
//#define FS8X_M_OTP_VPRE_PH_DELAY7        (0x07U << FS8X_M_OTP_VPRE_PH_SHIFT) /*!< delay 7 */
//
///******************************************************************************/
///* OTP_CFG_CLOCK_2 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_CLOCK_2_ADDR      0x25U
//#define FS8X_M_OTP_CFG_CLOCK_2_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VBST_PH_MASK          0x07U /*!< BOOST phase (delay) selection */
//#define FS8X_M_OTP_BUCK1_PH_MASK         0x38U /*!< BUCK1 phase (delay) selection */
//
//#define FS8X_M_OTP_VBST_PH_SHIFT         0x00U /*!< BOOST phase (delay) selection */
//#define FS8X_M_OTP_BUCK1_PH_SHIFT        0x03U /*!< BUCK1 phase (delay) selection */
//
//#define FS8X_M_OTP_VBST_PH_NODELAY       (0x00U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< no delay */
//#define FS8X_M_OTP_VBST_PH_DELAY1        (0x01U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 1 */
//#define FS8X_M_OTP_VBST_PH_DELAY2        (0x02U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 2 */
//#define FS8X_M_OTP_VBST_PH_DELAY3        (0x03U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 3 */
//#define FS8X_M_OTP_VBST_PH_DELAY4        (0x04U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 4 */
//#define FS8X_M_OTP_VBST_PH_DELAY5        (0x05U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 5 */
//#define FS8X_M_OTP_VBST_PH_DELAY6        (0x06U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 6 */
//#define FS8X_M_OTP_VBST_PH_DELAY7        (0x07U << FS8X_M_OTP_VBST_PH_SHIFT) /*!< delay 7 */
//
//#define FS8X_M_OTP_BUCK1_PH_NODELAY      (0x00U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< no delay */
//#define FS8X_M_OTP_BUCK1_PH_DELAY1       (0x01U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 1 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY2       (0x02U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 2 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY3       (0x03U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 3 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY4       (0x04U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 4 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY5       (0x05U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 5 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY6       (0x06U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 6 */
//#define FS8X_M_OTP_BUCK1_PH_DELAY7       (0x07U << FS8X_M_OTP_BUCK1_PH_SHIFT) /*!< delay 7 */
//
///******************************************************************************/
///* OTP_CFG_CLOCK_3 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_CLOCK_3_ADDR      0x26U
//#define FS8X_M_OTP_CFG_CLOCK_3_DEFAULT   0x00U
//
//#define FS8X_M_OTP_BUCK2_PH_MASK         0x07U /*!< BUCK2 phase (delay) selection */
//#define FS8X_M_OTP_BUCK3_PH_MASK         0x38U /*!< BUCK3 phase (delay) selection */
//
//#define FS8X_M_OTP_BUCK2_PH_SHIFT        0x00U /*!< BUCK2 phase (delay) selection */
//#define FS8X_M_OTP_BUCK3_PH_SHIFT        0x03U /*!< BUCK3 phase (delay) selection */
//
//#define FS8X_M_OTP_BUCK2_PH_NODELAY      (0x00U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< no delay */
//#define FS8X_M_OTP_BUCK2_PH_DELAY1       (0x01U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 1 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY2       (0x02U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 2 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY3       (0x03U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 3 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY4       (0x04U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 4 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY5       (0x05U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 5 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY6       (0x06U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 6 */
//#define FS8X_M_OTP_BUCK2_PH_DELAY7       (0x07U << FS8X_M_OTP_BUCK2_PH_SHIFT) /*!< delay 7 */
//
//#define FS8X_M_OTP_BUCK3_PH_NODELAY      (0x00U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< no delay */
//#define FS8X_M_OTP_BUCK3_PH_DELAY1       (0x01U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 1 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY2       (0x02U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 2 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY3       (0x03U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 3 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY4       (0x04U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 4 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY5       (0x05U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 5 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY6       (0x06U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 6 */
//#define FS8X_M_OTP_BUCK3_PH_DELAY7       (0x07U << FS8X_M_OTP_BUCK3_PH_SHIFT) /*!< delay 7 */
//
///******************************************************************************/
///* OTP_CFG_CLOCK_4 - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_CLOCK_4_ADDR      0x27U
//#define FS8X_M_OTP_CFG_CLOCK_4_DEFAULT   0x00U
//
//#define FS8X_M_OTP_CLK_DIV1_MASK         0x03U /*!< Divider 1 setting */
//#define FS8X_M_OTP_PLL_SEL_MASK          0x04U /*!< PLL enable */
//#define FS8X_M_OTP_VPRE_CLK_SEL_MASK     0x08U /*!< VPRE clock selection */
//#define FS8X_M_OTP_VBST_CLK_SEL_MASK     0x10U /*!< BOOST clock selection */
//#define FS8X_M_OTP_BUCK1_CLK_SEL_MASK    0x20U /*!< BUCK1 clock selection */
//#define FS8X_M_OTP_BUCK2_CLK_SEL_MASK    0x40U /*!< BUCK2 clock selection */
//#define FS8X_M_OTP_BUCK3_CLK_SEL_MASK    0x80U /*!< BUCK3 clock selection */
//
//#define FS8X_M_OTP_CLK_DIV1_SHIFT        0x00U /*!< Divider 1 setting */
//#define FS8X_M_OTP_PLL_SEL_SHIFT         0x02U /*!< PLL enable */
//#define FS8X_M_OTP_VPRE_CLK_SEL_SHIFT    0x03U /*!< VPRE clock selection */
//#define FS8X_M_OTP_VBST_CLK_SEL_SHIFT    0x04U /*!< BOOST clock selection */
//#define FS8X_M_OTP_BUCK1_CLK_SEL_SHIFT   0x05U /*!< BUCK1 clock selection */
//#define FS8X_M_OTP_BUCK2_CLK_SEL_SHIFT   0x06U /*!< BUCK2 clock selection */
//#define FS8X_M_OTP_BUCK3_CLK_SEL_SHIFT   0x07U /*!< BUCK3 clock selection */
//
//#define FS8X_M_OTP_CLK_DIV1_DIVIDE8      (0x00U << FS8X_M_OTP_CLK_DIV1_SHIFT) /*!< divide by 8 - CLK=2.5MHz */
//#define FS8X_M_OTP_CLK_DIV1_DIVIDE10     (0x01U << FS8X_M_OTP_CLK_DIV1_SHIFT) /*!< divide by 9 - CLK=2.22MHz */
//#define FS8X_M_OTP_CLK_DIV1_DIVIDE12     (0x02U << FS8X_M_OTP_CLK_DIV1_SHIFT) /*!< divide by 10 - CLK=2MHz */
//#define FS8X_M_OTP_CLK_DIV1_DIVIDE14     (0x03U << FS8X_M_OTP_CLK_DIV1_SHIFT) /*!< divide by 14 - CLK=1.43MHz */
//
//#define FS8X_M_OTP_PLL_SEL_DISABLED      (0x00U << FS8X_M_OTP_PLL_SEL_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_PLL_SEL_ENABLED       (0x01U << FS8X_M_OTP_PLL_SEL_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_VPRE_CLK_SEL_CLK_DIV1 (0x00U << FS8X_M_OTP_VPRE_CLK_SEL_SHIFT) /*!< CLK_DIV1 */
//#define FS8X_M_OTP_VPRE_CLK_SEL_CLK_DIV2 (0x01U << FS8X_M_OTP_VPRE_CLK_SEL_SHIFT) /*!< CLK_DIV2 */
//
//#define FS8X_M_OTP_VBST_CLK_SEL_CLK_DIV1 (0x00U << FS8X_M_OTP_VBST_CLK_SEL_SHIFT) /*!< CLK_DIV1 */
//#define FS8X_M_OTP_VBST_CLK_SEL_CLK_DIV2 (0x01U << FS8X_M_OTP_VBST_CLK_SEL_SHIFT) /*!< CLK_DIV2 */
//
//#define FS8X_M_OTP_BUCK1_CLK_SEL_CLK_DIV1 (0x00U << FS8X_M_OTP_BUCK1_CLK_SEL_SHIFT) /*!< CLK_DIV1 */
//#define FS8X_M_OTP_BUCK1_CLK_SEL_CLK_DIV2 (0x01U << FS8X_M_OTP_BUCK1_CLK_SEL_SHIFT) /*!< CLK_DIV2 */
//
//#define FS8X_M_OTP_BUCK2_CLK_SEL_CLK_DIV1 (0x00U << FS8X_M_OTP_BUCK2_CLK_SEL_SHIFT) /*!< CLK_DIV1 */
//#define FS8X_M_OTP_BUCK2_CLK_SEL_CLK_DIV2 (0x01U << FS8X_M_OTP_BUCK2_CLK_SEL_SHIFT) /*!< CLK_DIV2 */
//
//#define FS8X_M_OTP_BUCK3_CLK_SEL_CLK_DIV1 (0x00U << FS8X_M_OTP_BUCK3_CLK_SEL_SHIFT) /*!< CLK_DIV1 */
//#define FS8X_M_OTP_BUCK3_CLK_SEL_CLK_DIV2 (0x01U << FS8X_M_OTP_BUCK3_CLK_SEL_SHIFT) /*!< CLK_DIV2 */
//
///******************************************************************************/
///* OTP_CFG_SM_1 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_SM_1_ADDR         0x28U
//#define FS8X_M_OTP_CFG_SM_1_DEFAULT      0x00U
//
//#define FS8X_M_OTP_CONF_TSD_MASK         0x3FU /*!< Global TSD versus regulator TSD configuration */
//
//#define FS8X_M_OTP_CONF_TSD_SHIFT        0x00U /*!< Global TSD versus regulator TSD configuration */
//
//#define FS8X_M_OTP_CONF_TSD_NO           (0x00U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< No global TSD */
//#define FS8X_M_OTP_CONF_TSD_LDO2         (0x01U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on LDO2 */
//#define FS8X_M_OTP_CONF_TSD_LDO1         (0x02U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on LDO1 */
//#define FS8X_M_OTP_CONF_TSD_BUCK3        (0x04U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on BUCK3 */
//#define FS8X_M_OTP_CONF_TSD_BUCK2        (0x08U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on BUCK2 */
//#define FS8X_M_OTP_CONF_TSD_BUCK1        (0x10U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on BUCK1 */
//#define FS8X_M_OTP_CONF_TSD_BOOST        (0x20U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on BOOST */
//#define FS8X_M_OTP_CONF_TSD_BUCK2_LDO2   (0x09U << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS only if TSD on BUCK2 or LDO2 */
//#define FS8X_M_OTP_CONF_TSD_ANY          (0x3FU << FS8X_M_OTP_CONF_TSD_SHIFT) /*!< GoTo DFS on any TSD */
//
///******************************************************************************/
///* OTP_CFG_SM_2 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_SM_2_ADDR         0x29U
//#define FS8X_M_OTP_CFG_SM_2_DEFAULT      0x00U
//
//#define FS8X_M_OTP_PSYNC_EN_MASK         0x01U /*!< Synchronization with 2 devices */
//#define FS8X_M_OTP_PSYNC_CFG_MASK        0x02U /*!< Synchronization with 1x FS85 or 1x PF82 */
//#define FS8X_M_OTP_AUTORETRY_EN_MASK     0x04U /*!< Deep Fail-safe autoretry enable */
//#define FS8X_M_OTP_AUTORETRY_INFINITE_MASK 0x08U /*!< Deep Fail-safe infinite autoretry enable */
//#define FS8X_M_OTP_VPRE_OFF_DLY_MASK     0x10U /*!< Delay to turn OFF VPRE at device power down */
//
//#define FS8X_M_OTP_PSYNC_EN_SHIFT        0x00U /*!< Synchronization with 2 devices */
//#define FS8X_M_OTP_PSYNC_CFG_SHIFT       0x01U /*!< Synchronization with 1x FS85 or 1x PF82 */
//#define FS8X_M_OTP_AUTORETRY_EN_SHIFT    0x02U /*!< Deep Fail-safe autoretry enable */
//#define FS8X_M_OTP_AUTORETRY_INFINITE_SHIFT 0x03U /*!< Deep Fail-safe infinite autoretry enable */
//#define FS8X_M_OTP_VPRE_OFF_DLY_SHIFT    0x04U /*!< Delay to turn OFF VPRE at device power down */
//
//#define FS8X_M_OTP_PSYNC_EN_DISABLED     (0x00U << FS8X_M_OTP_PSYNC_EN_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_PSYNC_EN_ENABLED      (0x01U << FS8X_M_OTP_PSYNC_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_PSYNC_CFG_2XFS85      (0x00U << FS8X_M_OTP_PSYNC_CFG_SHIFT) /*!< 2x FS85 */
//#define FS8X_M_OTP_PSYNC_CFG_1XFS85_1XPF82 (0x01U << FS8X_M_OTP_PSYNC_CFG_SHIFT) /*!< 1x FS85 and 1x PF82 */
//
//#define FS8X_M_OTP_AUTORETRY_EN_DISABLED (0x00U << FS8X_M_OTP_AUTORETRY_EN_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_AUTORETRY_EN_ENABLED  (0x01U << FS8X_M_OTP_AUTORETRY_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_AUTORETRY_INFINITE_DISABLED (0x00U << FS8X_M_OTP_AUTORETRY_INFINITE_SHIFT) /*!< Disabled */
//#define FS8X_M_OTP_AUTORETRY_INFINITE_ENABLED (0x01U << FS8X_M_OTP_AUTORETRY_INFINITE_SHIFT) /*!< Enabled */
//
//#define FS8X_M_OTP_VPRE_OFF_DLY_250US    (0x00U << FS8X_M_OTP_VPRE_OFF_DLY_SHIFT) /*!< 250 us */
//#define FS8X_M_OTP_VPRE_OFF_DLY_32MS     (0x01U << FS8X_M_OTP_VPRE_OFF_DLY_SHIFT) /*!< 32 ms */
//
///******************************************************************************/
///* OTP_CFG_VSUP_UV - Type: RW                                                 */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_VSUP_UV_ADDR      0x2AU
//#define FS8X_M_OTP_CFG_VSUP_UV_DEFAULT   0x00U
//
//#define FS8X_M_OTP_VSUPCFG_MASK          0x01U /*!< VSUP Under Voltage Threshold Configuration */
//#define FS8X_M_OTP_OTP_SPARE2_MASK       0xFEU /*!< N/A */
//
//#define FS8X_M_OTP_VSUPCFG_SHIFT         0x00U /*!< VSUP Under Voltage Threshold Configuration */
//#define FS8X_M_OTP_OTP_SPARE2_SHIFT      0x01U /*!< N/A */
//
//#define FS8X_M_OTP_VSUPCFG_4_9V          (0x00U << FS8X_M_OTP_VSUPCFG_SHIFT) /*!< 0 - 4.9V for Vpre < 4.5V */
//#define FS8X_M_OTP_VSUPCFG_6_2V          (0x01U << FS8X_M_OTP_VSUPCFG_SHIFT) /*!< 1 - 6.2V for Vpre > 4.5V */
//
//#define FS8X_M_OTP_OTP_SPARE2_0          (0x00U << FS8X_M_OTP_OTP_SPARE2_SHIFT) /*!< 0000000 */
//
///******************************************************************************/
///* OTP_CFG_I2C - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_I2C_ADDR          0x2BU
//#define FS8X_M_OTP_CFG_I2C_DEFAULT       0x00U
//
//#define FS8X_M_OTP_I2CDEVADDR_MASK       0x0FU /*!< Device I2C address */
//
//#define FS8X_M_OTP_I2CDEVADDR_SHIFT      0x00U /*!< Device I2C address */
//
//#define FS8X_M_OTP_I2CDEVADDR_D0         (0x00U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D0 */
//#define FS8X_M_OTP_I2CDEVADDR_D1         (0x01U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D1 */
//#define FS8X_M_OTP_I2CDEVADDR_D2         (0x02U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D2 */
//#define FS8X_M_OTP_I2CDEVADDR_D3         (0x03U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D3 */
//#define FS8X_M_OTP_I2CDEVADDR_D4         (0x04U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D4 */
//#define FS8X_M_OTP_I2CDEVADDR_D5         (0x05U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D5 */
//#define FS8X_M_OTP_I2CDEVADDR_D6         (0x06U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D6 */
//#define FS8X_M_OTP_I2CDEVADDR_D7         (0x07U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D7 */
//#define FS8X_M_OTP_I2CDEVADDR_D8         (0x08U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D8 */
//#define FS8X_M_OTP_I2CDEVADDR_D9         (0x09U << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D9 */
//#define FS8X_M_OTP_I2CDEVADDR_D10        (0x0AU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D10 */
//#define FS8X_M_OTP_I2CDEVADDR_D11        (0x0BU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D11 */
//#define FS8X_M_OTP_I2CDEVADDR_D12        (0x0CU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D12 */
//#define FS8X_M_OTP_I2CDEVADDR_D13        (0x0DU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D13 */
//#define FS8X_M_OTP_I2CDEVADDR_D14        (0x0EU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D14 */
//#define FS8X_M_OTP_I2CDEVADDR_D15        (0x0FU << FS8X_M_OTP_I2CDEVADDR_SHIFT) /*!< Address D15 */
//
///******************************************************************************/
///* OTP_CFG_OV - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_OV_ADDR           0x2CU
//#define FS8X_M_OTP_CFG_OV_DEFAULT        0x00U
//
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_MASK 0x07U /*!< Regulator assigned to VDDIO */
//
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT 0x00U /*!< Regulator assigned to VDDIO */
//
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_EXTREGOPTION0 (0x00U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< External regulator */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_VPRE (0x01U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< VPRE */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_LDO1 (0x02U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< LDO1 */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_LDO2 (0x03U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< LDO2 */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_BUCK3 (0x04U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< BUCK3 */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_EXTREGOPTION5 (0x05U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< External regulator */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_EXTREGOPTION6 (0x06U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< External regulator */
//#define FS8X_M_OTP_VDDIO_REG_ASSIGN_EXTREGOPTION7 (0x07U << FS8X_M_OTP_VDDIO_REG_ASSIGN_SHIFT) /*!< External regulator */
//
///******************************************************************************/
///* OTP_CFG_DEVID - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_M_OTP_CFG_DEVID_ADDR        0x2DU
//#define FS8X_M_OTP_CFG_DEVID_DEFAULT     0x00U
//
//#define FS8X_M_OTP_DEVICEID_MASK         0xFFU /*!< Device ID */
//
//#define FS8X_M_OTP_DEVICEID_SHIFT        0x00U /*!< Device ID */
//
///******************************************************************************/
///* OTP_M_S1_CRC_LSB - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_M_S1_CRC_LSB_ADDR     0x2EU
//#define FS8X_M_OTP_M_S1_CRC_LSB_DEFAULT  0x00U
//
//#define FS8X_M_OTP_OTP_M_S1_CRC_LSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_M_OTP_OTP_M_S1_CRC_LSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_M_S1_CRC_MSB - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_M_OTP_M_S1_CRC_MSB_ADDR     0x2FU
//#define FS8X_M_OTP_M_S1_CRC_MSB_DEFAULT  0x00U
//
//#define FS8X_M_OTP_OTP_M_S1_CRC_MSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_M_OTP_OTP_M_S1_CRC_MSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_CFG_UVOV_1 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_1_ADDR      0x0AU
//#define FS8X_FS_OTP_CFG_UVOV_1_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VCORE_V_MASK         0xFFU /*!< VCORE (VBUCK1) monitoring voltage */
//
//#define FS8X_FS_OTP_VCORE_V_SHIFT        0x00U /*!< VCORE (VBUCK1) monitoring voltage */
//
//#define FS8X_FS_OTP_VCORE_V_0_8V         (0x40U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 0.80 V */
//#define FS8X_FS_OTP_VCORE_V_0_9V         (0x50U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 0.90 V */
//#define FS8X_FS_OTP_VCORE_V_1_00V        (0x60U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.00 V */
//#define FS8X_FS_OTP_VCORE_V_1_10V        (0x70U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.10 V */
//#define FS8X_FS_OTP_VCORE_V_1_20V        (0x80U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.20 V */
//#define FS8X_FS_OTP_VCORE_V_1_25V        (0x88U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.25 V */
//#define FS8X_FS_OTP_VCORE_V_1_30V        (0x90U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.30 V */
//#define FS8X_FS_OTP_VCORE_V_1_35V        (0x98U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.35 V */
//#define FS8X_FS_OTP_VCORE_V_1_40V        (0xA0U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.40 V */
//#define FS8X_FS_OTP_VCORE_V_1_50V        (0xB0U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.50 V */
//#define FS8X_FS_OTP_VCORE_V_1_80V        (0xB1U << FS8X_FS_OTP_VCORE_V_SHIFT) /*!< 1.80 V */
//
///******************************************************************************/
///* OTP_CFG_UVOV_2 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_2_ADDR      0x0BU
//#define FS8X_FS_OTP_CFG_UVOV_2_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VCOREOVTH_MASK       0x0FU /*!< VCORE (BUCK1) overvoltage threshold configuration */
//#define FS8X_FS_OTP_VDDIOOVTH_MASK       0xF0U /*!< VDDIO overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VCOREOVTH_SHIFT      0x00U /*!< VCORE (BUCK1) overvoltage threshold configuration */
//#define FS8X_FS_OTP_VDDIOOVTH_SHIFT      0x04U /*!< VDDIO overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VCOREOVTH_104_5      (0x00U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VCOREOVTH_105        (0x01U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VCOREOVTH_105_5      (0x02U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VCOREOVTH_106        (0x03U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VCOREOVTH_106_5      (0x04U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VCOREOVTH_107        (0x05U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VCOREOVTH_107_5      (0x06U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VCOREOVTH_108        (0x07U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VCOREOVTH_108_5      (0x08U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VCOREOVTH_109        (0x09U << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VCOREOVTH_109_5      (0x0AU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VCOREOVTH_110        (0x0BU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VCOREOVTH_110_5      (0x0CU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VCOREOVTH_111        (0x0DU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VCOREOVTH_111_5      (0x0EU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VCOREOVTH_112        (0x0FU << FS8X_FS_OTP_VCOREOVTH_SHIFT) /*!< 112% */
//
//#define FS8X_FS_OTP_VDDIOOVTH_104_5      (0x00U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_105        (0x01U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VDDIOOVTH_105_5      (0x02U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_106        (0x03U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VDDIOOVTH_106_5      (0x04U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_107        (0x05U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VDDIOOVTH_107_5      (0x06U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_108        (0x07U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VDDIOOVTH_108_5      (0x08U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_109        (0x09U << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VDDIOOVTH_109_5      (0x0AU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_110        (0x0BU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VDDIOOVTH_110_5      (0x0CU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_111        (0x0DU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VDDIOOVTH_111_5      (0x0EU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VDDIOOVTH_112        (0x0FU << FS8X_FS_OTP_VDDIOOVTH_SHIFT) /*!< 112% */
//
///******************************************************************************/
///* OTP_CFG_UVOV_3 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_3_ADDR      0x0CU
//#define FS8X_FS_OTP_CFG_UVOV_3_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_MASK 0x1FU /*!< SVS max value allowed (mask) */
//#define FS8X_FS_OTP_VDDIO_V_MASK         0x20U /*!< VDDIO voltage selection */
//
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT 0x00U /*!< SVS max value allowed (mask) */
//#define FS8X_FS_OTP_VDDIO_V_SHIFT        0x05U /*!< VDDIO voltage selection */
//
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_NOSVS (0x00U << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< No SVS */
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_2STEPS (0x01U << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< 2 steps available */
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_4STEPS (0x03U << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< 4 steps available */
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_8STEPS (0x07U << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< 8 steps available */
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_16STEPS (0x0FU << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< 16 steps available */
//#define FS8X_FS_OTP_VCORE_SVS_CLAMP_32STEPS (0x1FU << FS8X_FS_OTP_VCORE_SVS_CLAMP_SHIFT) /*!< 32 steps available */
//
//#define FS8X_FS_OTP_VDDIO_V_3_3V         (0x00U << FS8X_FS_OTP_VDDIO_V_SHIFT) /*!< 3.3 V */
//#define FS8X_FS_OTP_VDDIO_V_5V           (0x01U << FS8X_FS_OTP_VDDIO_V_SHIFT) /*!< 5 V */
//
///******************************************************************************/
///* OTP_CFG_UVOV_4 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_4_ADDR      0x0DU
//#define FS8X_FS_OTP_CFG_UVOV_4_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VMON1OVTH_MASK       0x0FU /*!< VMON1 overvoltage threshold configuration */
//#define FS8X_FS_OTP_VMON2OVTH_MASK       0xF0U /*!< VMON2 overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON1OVTH_SHIFT      0x00U /*!< VMON1 overvoltage threshold configuration */
//#define FS8X_FS_OTP_VMON2OVTH_SHIFT      0x04U /*!< VMON2 overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON1OVTH_104_5      (0x00U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VMON1OVTH_105        (0x01U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VMON1OVTH_105_5      (0x02U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VMON1OVTH_106        (0x03U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VMON1OVTH_106_5      (0x04U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VMON1OVTH_107        (0x05U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VMON1OVTH_107_5      (0x06U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VMON1OVTH_108        (0x07U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VMON1OVTH_108_5      (0x08U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VMON1OVTH_109        (0x09U << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VMON1OVTH_109_5      (0x0AU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VMON1OVTH_110        (0x0BU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VMON1OVTH_110_5      (0x0CU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VMON1OVTH_111        (0x0DU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VMON1OVTH_111_5      (0x0EU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VMON1OVTH_112        (0x0FU << FS8X_FS_OTP_VMON1OVTH_SHIFT) /*!< 112% */
//
//#define FS8X_FS_OTP_VMON2OVTH_104_5      (0x00U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VMON2OVTH_105        (0x01U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VMON2OVTH_105_5      (0x02U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VMON2OVTH_106        (0x03U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VMON2OVTH_106_5      (0x04U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VMON2OVTH_107        (0x05U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VMON2OVTH_107_5      (0x06U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VMON2OVTH_108        (0x07U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VMON2OVTH_108_5      (0x08U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VMON2OVTH_109        (0x09U << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VMON2OVTH_109_5      (0x0AU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VMON2OVTH_110        (0x0BU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VMON2OVTH_110_5      (0x0CU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VMON2OVTH_111        (0x0DU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VMON2OVTH_111_5      (0x0EU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VMON2OVTH_112        (0x0FU << FS8X_FS_OTP_VMON2OVTH_SHIFT) /*!< 112% */
//
///******************************************************************************/
///* OTP_CFG_UVOV_5 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_5_ADDR      0x0EU
//#define FS8X_FS_OTP_CFG_UVOV_5_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VMON3OVTH_MASK       0x0FU /*!< VMON3 overvoltage threshold configuration */
//#define FS8X_FS_OTP_VMON4OVTH_MASK       0xF0U /*!< VMON4 overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON3OVTH_SHIFT      0x00U /*!< VMON3 overvoltage threshold configuration */
//#define FS8X_FS_OTP_VMON4OVTH_SHIFT      0x04U /*!< VMON4 overvoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON3OVTH_104_5      (0x00U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VMON3OVTH_105        (0x01U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VMON3OVTH_105_5      (0x02U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VMON3OVTH_106        (0x03U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VMON3OVTH_106_5      (0x04U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VMON3OVTH_107        (0x05U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VMON3OVTH_107_5      (0x06U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VMON3OVTH_108        (0x07U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VMON3OVTH_108_5      (0x08U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VMON3OVTH_109        (0x09U << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VMON3OVTH_109_5      (0x0AU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VMON3OVTH_110        (0x0BU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VMON3OVTH_110_5      (0x0CU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VMON3OVTH_111        (0x0DU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VMON3OVTH_111_5      (0x0EU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VMON3OVTH_112        (0x0FU << FS8X_FS_OTP_VMON3OVTH_SHIFT) /*!< 112% */
//
//#define FS8X_FS_OTP_VMON4OVTH_104_5      (0x00U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 104.5% */
//#define FS8X_FS_OTP_VMON4OVTH_105        (0x01U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 105% */
//#define FS8X_FS_OTP_VMON4OVTH_105_5      (0x02U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 105.5% */
//#define FS8X_FS_OTP_VMON4OVTH_106        (0x03U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 106% */
//#define FS8X_FS_OTP_VMON4OVTH_106_5      (0x04U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 106.5% */
//#define FS8X_FS_OTP_VMON4OVTH_107        (0x05U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 107% */
//#define FS8X_FS_OTP_VMON4OVTH_107_5      (0x06U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 107.5% */
//#define FS8X_FS_OTP_VMON4OVTH_108        (0x07U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 108% */
//#define FS8X_FS_OTP_VMON4OVTH_108_5      (0x08U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 108.5% */
//#define FS8X_FS_OTP_VMON4OVTH_109        (0x09U << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 109% */
//#define FS8X_FS_OTP_VMON4OVTH_109_5      (0x0AU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 109.5% */
//#define FS8X_FS_OTP_VMON4OVTH_110        (0x0BU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 110% */
//#define FS8X_FS_OTP_VMON4OVTH_110_5      (0x0CU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 110.5% */
//#define FS8X_FS_OTP_VMON4OVTH_111        (0x0DU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 111% */
//#define FS8X_FS_OTP_VMON4OVTH_111_5      (0x0EU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 111.5% */
//#define FS8X_FS_OTP_VMON4OVTH_112        (0x0FU << FS8X_FS_OTP_VMON4OVTH_SHIFT) /*!< 112% */
//
///******************************************************************************/
///* OTP_CFG_UVOV_6 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_6_ADDR      0x0FU
//#define FS8X_FS_OTP_CFG_UVOV_6_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VCOREUVTH_MASK       0x0FU /*!< VCORE undervoltage threshold configuration */
//#define FS8X_FS_OTP_VDDIOUVTH_MASK       0xF0U /*!< VDDIO undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VCOREUVTH_SHIFT      0x00U /*!< VCORE undervoltage threshold configuration */
//#define FS8X_FS_OTP_VDDIOUVTH_SHIFT      0x04U /*!< VDDIO undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VCOREUVTH_95_5       (0x00U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VCOREUVTH_95         (0x01U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VCOREUVTH_94_5       (0x02U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VCOREUVTH_94         (0x03U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VCOREUVTH_93_5       (0x04U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VCOREUVTH_93         (0x05U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VCOREUVTH_92_5       (0x06U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VCOREUVTH_92         (0x07U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VCOREUVTH_91_5       (0x08U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VCOREUVTH_91         (0x09U << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VCOREUVTH_90_5       (0x0AU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VCOREUVTH_90         (0x0BU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VCOREUVTH_89_5       (0x0CU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VCOREUVTH_89         (0x0DU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VCOREUVTH_88_5       (0x0EU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VCOREUVTH_88         (0x0FU << FS8X_FS_OTP_VCOREUVTH_SHIFT) /*!< 88% */
//
//#define FS8X_FS_OTP_VDDIOUVTH_95_5       (0x00U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_95         (0x01U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VDDIOUVTH_94_5       (0x02U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_94         (0x03U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VDDIOUVTH_93_5       (0x04U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_93         (0x05U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VDDIOUVTH_92_5       (0x06U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_92         (0x07U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VDDIOUVTH_91_5       (0x08U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_91         (0x09U << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VDDIOUVTH_90_5       (0x0AU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_90         (0x0BU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VDDIOUVTH_89_5       (0x0CU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_89         (0x0DU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VDDIOUVTH_88_5       (0x0EU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VDDIOUVTH_88         (0x0FU << FS8X_FS_OTP_VDDIOUVTH_SHIFT) /*!< 88% */
//
///******************************************************************************/
///* OTP_CFG_UVOV_7 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_7_ADDR      0x10U
//#define FS8X_FS_OTP_CFG_UVOV_7_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VMON1UVTH_MASK       0x0FU /*!< VMON1 undervoltage threshold configuration */
//#define FS8X_FS_OTP_VMON2UVTH_MASK       0xF0U /*!< VMON2 undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON1UVTH_SHIFT      0x00U /*!< VMON1 undervoltage threshold configuration */
//#define FS8X_FS_OTP_VMON2UVTH_SHIFT      0x04U /*!< VMON2 undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON1UVTH_95_5       (0x00U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VMON1UVTH_95         (0x01U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VMON1UVTH_94_5       (0x02U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VMON1UVTH_94         (0x03U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VMON1UVTH_93_5       (0x04U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VMON1UVTH_93         (0x05U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VMON1UVTH_92_5       (0x06U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VMON1UVTH_92         (0x07U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VMON1UVTH_91_5       (0x08U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VMON1UVTH_91         (0x09U << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VMON1UVTH_90_5       (0x0AU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VMON1UVTH_90         (0x0BU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VMON1UVTH_89_5       (0x0CU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VMON1UVTH_89         (0x0DU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VMON1UVTH_88_5       (0x0EU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VMON1UVTH_88         (0x0FU << FS8X_FS_OTP_VMON1UVTH_SHIFT) /*!< 88% */
//
//#define FS8X_FS_OTP_VMON2UVTH_95_5       (0x00U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VMON2UVTH_95         (0x01U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VMON2UVTH_94_5       (0x02U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VMON2UVTH_94         (0x03U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VMON2UVTH_93_5       (0x04U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VMON2UVTH_93         (0x05U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VMON2UVTH_92_5       (0x06U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VMON2UVTH_92         (0x07U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VMON2UVTH_91_5       (0x08U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VMON2UVTH_91         (0x09U << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VMON2UVTH_90_5       (0x0AU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VMON2UVTH_90         (0x0BU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VMON2UVTH_89_5       (0x0CU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VMON2UVTH_89         (0x0DU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VMON2UVTH_88_5       (0x0EU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VMON2UVTH_88         (0x0FU << FS8X_FS_OTP_VMON2UVTH_SHIFT) /*!< 88% */
//
///******************************************************************************/
///* OTP_CFG_UVOV_8 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_UVOV_8_ADDR      0x11U
//#define FS8X_FS_OTP_CFG_UVOV_8_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_VMON3UVTH_MASK       0x0FU /*!< VMON3 undervoltage threshold configuration */
//#define FS8X_FS_OTP_VMON4UVTH_MASK       0xF0U /*!< VMON4 undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON3UVTH_SHIFT      0x00U /*!< VMON3 undervoltage threshold configuration */
//#define FS8X_FS_OTP_VMON4UVTH_SHIFT      0x04U /*!< VMON4 undervoltage threshold configuration */
//
//#define FS8X_FS_OTP_VMON3UVTH_95_5       (0x00U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VMON3UVTH_95         (0x01U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VMON3UVTH_94_5       (0x02U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VMON3UVTH_94         (0x03U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VMON3UVTH_93_5       (0x04U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VMON3UVTH_93         (0x05U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VMON3UVTH_92_5       (0x06U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VMON3UVTH_92         (0x07U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VMON3UVTH_91_5       (0x08U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VMON3UVTH_91         (0x09U << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VMON3UVTH_90_5       (0x0AU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VMON3UVTH_90         (0x0BU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VMON3UVTH_89_5       (0x0CU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VMON3UVTH_89         (0x0DU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VMON3UVTH_88_5       (0x0EU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VMON3UVTH_88         (0x0FU << FS8X_FS_OTP_VMON3UVTH_SHIFT) /*!< 88% */
//
//#define FS8X_FS_OTP_VMON4UVTH_95_5       (0x00U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 95.5% */
//#define FS8X_FS_OTP_VMON4UVTH_95         (0x01U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 95% */
//#define FS8X_FS_OTP_VMON4UVTH_94_5       (0x02U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 94.5% */
//#define FS8X_FS_OTP_VMON4UVTH_94         (0x03U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 94% */
//#define FS8X_FS_OTP_VMON4UVTH_93_5       (0x04U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 93.5% */
//#define FS8X_FS_OTP_VMON4UVTH_93         (0x05U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 93% */
//#define FS8X_FS_OTP_VMON4UVTH_92_5       (0x06U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 92.5% */
//#define FS8X_FS_OTP_VMON4UVTH_92         (0x07U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 92% */
//#define FS8X_FS_OTP_VMON4UVTH_91_5       (0x08U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 91.5% */
//#define FS8X_FS_OTP_VMON4UVTH_91         (0x09U << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 91% */
//#define FS8X_FS_OTP_VMON4UVTH_90_5       (0x0AU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 90.5% */
//#define FS8X_FS_OTP_VMON4UVTH_90         (0x0BU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 90% */
//#define FS8X_FS_OTP_VMON4UVTH_89_5       (0x0CU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 89.5% */
//#define FS8X_FS_OTP_VMON4UVTH_89         (0x0DU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 89% */
//#define FS8X_FS_OTP_VMON4UVTH_88_5       (0x0EU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 88.5% */
//#define FS8X_FS_OTP_VMON4UVTH_88         (0x0FU << FS8X_FS_OTP_VMON4UVTH_SHIFT) /*!< 88% */
//
///******************************************************************************/
///* OTP_CFG_PGOOD - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_PGOOD_ADDR       0x12U
//#define FS8X_FS_OTP_CFG_PGOOD_DEFAULT    0x00U
//
//#define FS8X_FS_OTP_PGOOD_VCORE_MASK     0x01U /*!< VCORE (BUCK1) assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VDDIO_MASK     0x02U /*!< VDDIO assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON1_MASK     0x04U /*!< VMON1 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON2_MASK     0x08U /*!< VMON2 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON3_MASK     0x10U /*!< VMON3 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON4_MASK     0x20U /*!< VMON4 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_RSTB_MASK      0x40U /*!< RSTB assignment to PGOOD */
//
//#define FS8X_FS_OTP_PGOOD_VCORE_SHIFT    0x00U /*!< VCORE (BUCK1) assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VDDIO_SHIFT    0x01U /*!< VDDIO assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON1_SHIFT    0x02U /*!< VMON1 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON2_SHIFT    0x03U /*!< VMON2 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON3_SHIFT    0x04U /*!< VMON3 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_VMON4_SHIFT    0x05U /*!< VMON4 assignment to PGOOD */
//#define FS8X_FS_OTP_PGOOD_RSTB_SHIFT     0x06U /*!< RSTB assignment to PGOOD */
//
//#define FS8X_FS_OTP_PGOOD_VCORE_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VCORE_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VCORE_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VCORE_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_VDDIO_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VDDIO_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VDDIO_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VDDIO_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_VMON1_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VMON1_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VMON1_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VMON1_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_VMON2_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VMON2_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VMON2_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VMON2_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_VMON3_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VMON3_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VMON3_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VMON3_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_VMON4_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_VMON4_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_VMON4_ASSIGNED (0x01U << FS8X_FS_OTP_PGOOD_VMON4_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_PGOOD_RSTB_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_PGOOD_RSTB_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_PGOOD_RSTB_ASSIGNED  (0x01U << FS8X_FS_OTP_PGOOD_RSTB_SHIFT) /*!< Assigned */
//
///******************************************************************************/
///* OTP_CFG_ABIST1 - Type: RW                                                  */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_ABIST1_ADDR      0x13U
//#define FS8X_FS_OTP_CFG_ABIST1_DEFAULT   0x00U
//
//#define FS8X_FS_OTP_ABIST1_VCORE_MASK    0x01U /*!< VCORE assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VDDIO_MASK    0x02U /*!< VDDIO assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON1_MASK    0x04U /*!< VMON1 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON2_MASK    0x08U /*!< VMON2 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON3_MASK    0x10U /*!< VMON3 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON4_MASK    0x20U /*!< VMON4 assignment to ABIST1 */
//#define FS8X_FS_OTP_OTP_SPARE_MASK       0xC0U /*!< N/A */
//
//#define FS8X_FS_OTP_ABIST1_VCORE_SHIFT   0x00U /*!< VCORE assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VDDIO_SHIFT   0x01U /*!< VDDIO assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON1_SHIFT   0x02U /*!< VMON1 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON2_SHIFT   0x03U /*!< VMON2 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON3_SHIFT   0x04U /*!< VMON3 assignment to ABIST1 */
//#define FS8X_FS_OTP_ABIST1_VMON4_SHIFT   0x05U /*!< VMON4 assignment to ABIST1 */
//#define FS8X_FS_OTP_OTP_SPARE_SHIFT      0x06U /*!< N/A */
//
//#define FS8X_FS_OTP_ABIST1_VCORE_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VCORE_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VCORE_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VCORE_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_ABIST1_VDDIO_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VDDIO_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VDDIO_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VDDIO_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_ABIST1_VMON1_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VMON1_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VMON1_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VMON1_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_ABIST1_VMON2_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VMON2_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VMON2_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VMON2_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_ABIST1_VMON3_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VMON3_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VMON3_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VMON3_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_ABIST1_VMON4_NOT_ASSIGNED (0x00U << FS8X_FS_OTP_ABIST1_VMON4_SHIFT) /*!< Not assigned */
//#define FS8X_FS_OTP_ABIST1_VMON4_ASSIGNED (0x01U << FS8X_FS_OTP_ABIST1_VMON4_SHIFT) /*!< Assigned */
//
//#define FS8X_FS_OTP_OTP_SPARE_0          (0x00U << FS8X_FS_OTP_OTP_SPARE_SHIFT) /*!< 00 */
//
///******************************************************************************/
///* OTP_CFG_ASIL - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_ASIL_ADDR        0x14U
//#define FS8X_FS_OTP_CFG_ASIL_DEFAULT     0x00U
//
//#define FS8X_FS_OTP_VMON1_EN_MASK        0x01U /*!< VMON1 monitoring enable */
//#define FS8X_FS_OTP_VMON2_EN_MASK        0x02U /*!< VMON2 monitoring enable */
//#define FS8X_FS_OTP_VMON3_EN_MASK        0x04U /*!< VMON3 monitoring enable */
//#define FS8X_FS_OTP_VMON4_EN_MASK        0x08U /*!< VMON4 monitoring enable */
//#define FS8X_FS_OTP_FCCU_EN_MASK         0x10U /*!< FCCU monitoring enable */
//#define FS8X_FS_OTP_ERRMON_EN_MASK       0x20U /*!< ERRMON monitoring enable */
//#define FS8X_FS_OTP_WD_SELECTION_MASK    0x40U /*!< Watchdog mode selection */
//#define FS8X_FS_OTP_WD_DIS_MASK          0x80U /*!< Watchdog monitoring enable */
//
//#define FS8X_FS_OTP_VMON1_EN_SHIFT       0x00U /*!< VMON1 monitoring enable */
//#define FS8X_FS_OTP_VMON2_EN_SHIFT       0x01U /*!< VMON2 monitoring enable */
//#define FS8X_FS_OTP_VMON3_EN_SHIFT       0x02U /*!< VMON3 monitoring enable */
//#define FS8X_FS_OTP_VMON4_EN_SHIFT       0x03U /*!< VMON4 monitoring enable */
//#define FS8X_FS_OTP_FCCU_EN_SHIFT        0x04U /*!< FCCU monitoring enable */
//#define FS8X_FS_OTP_ERRMON_EN_SHIFT      0x05U /*!< ERRMON monitoring enable */
//#define FS8X_FS_OTP_WD_SELECTION_SHIFT   0x06U /*!< Watchdog mode selection */
//#define FS8X_FS_OTP_WD_DIS_SHIFT         0x07U /*!< Watchdog monitoring enable */
//
//#define FS8X_FS_OTP_VMON1_EN_DISABLED    (0x00U << FS8X_FS_OTP_VMON1_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_VMON1_EN_ENABLED     (0x01U << FS8X_FS_OTP_VMON1_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_VMON2_EN_DISABLED    (0x00U << FS8X_FS_OTP_VMON2_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_VMON2_EN_ENABLED     (0x01U << FS8X_FS_OTP_VMON2_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_VMON3_EN_DISABLED    (0x00U << FS8X_FS_OTP_VMON3_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_VMON3_EN_ENABLED     (0x01U << FS8X_FS_OTP_VMON3_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_VMON4_EN_DISABLED    (0x00U << FS8X_FS_OTP_VMON4_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_VMON4_EN_ENABLED     (0x01U << FS8X_FS_OTP_VMON4_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_FCCU_EN_DISABLED     (0x00U << FS8X_FS_OTP_FCCU_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_FCCU_EN_ENABLED      (0x01U << FS8X_FS_OTP_FCCU_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_ERRMON_EN_DISABLED   (0x00U << FS8X_FS_OTP_ERRMON_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_ERRMON_EN_ENABLED    (0x01U << FS8X_FS_OTP_ERRMON_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_OTP_WD_SELECTION_SIMPLE_WD (0x00U << FS8X_FS_OTP_WD_SELECTION_SHIFT) /*!< Simple WD */
//#define FS8X_FS_OTP_WD_SELECTION_CHALLENGER_WD (0x01U << FS8X_FS_OTP_WD_SELECTION_SHIFT) /*!< Challenger_WD */
//
//#define FS8X_FS_OTP_WD_DIS_ENABLED       (0x00U << FS8X_FS_OTP_WD_DIS_SHIFT) /*!< Enabled */
//#define FS8X_FS_OTP_WD_DIS_DISABLED      (0x01U << FS8X_FS_OTP_WD_DIS_SHIFT) /*!< Disabled */
//
///******************************************************************************/
///* OTP_CFG_I2C - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_FS_OTP_CFG_I2C_ADDR         0x15U
//#define FS8X_FS_OTP_CFG_I2C_DEFAULT      0x00U
//
//#define FS8X_FS_OTP_I2CDEVADDR_MASK      0x0FU /*!< Device I2C address */
//#define FS8X_FS_OTP_FLT_RECOVERY_EN_MASK 0x10U /*!< Fault recovery strategy enable */
//
//#define FS8X_FS_OTP_I2CDEVADDR_SHIFT     0x00U /*!< Device I2C address */
//#define FS8X_FS_OTP_FLT_RECOVERY_EN_SHIFT 0x04U /*!< Fault recovery strategy enable */
//
//#define FS8X_FS_OTP_I2CDEVADDR_D0        (0x00U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D0 */
//#define FS8X_FS_OTP_I2CDEVADDR_D1        (0x01U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D1 */
//#define FS8X_FS_OTP_I2CDEVADDR_D2        (0x02U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D2 */
//#define FS8X_FS_OTP_I2CDEVADDR_D3        (0x03U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D3 */
//#define FS8X_FS_OTP_I2CDEVADDR_D4        (0x04U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D4 */
//#define FS8X_FS_OTP_I2CDEVADDR_D5        (0x05U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D5 */
//#define FS8X_FS_OTP_I2CDEVADDR_D6        (0x06U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D6 */
//#define FS8X_FS_OTP_I2CDEVADDR_D7        (0x07U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D7 */
//#define FS8X_FS_OTP_I2CDEVADDR_D8        (0x08U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D8 */
//#define FS8X_FS_OTP_I2CDEVADDR_D9        (0x09U << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D9 */
//#define FS8X_FS_OTP_I2CDEVADDR_D10       (0x0AU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D10 */
//#define FS8X_FS_OTP_I2CDEVADDR_D11       (0x0BU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D11 */
//#define FS8X_FS_OTP_I2CDEVADDR_D12       (0x0CU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D12 */
//#define FS8X_FS_OTP_I2CDEVADDR_D13       (0x0DU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D13 */
//#define FS8X_FS_OTP_I2CDEVADDR_D14       (0x0EU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D14 */
//#define FS8X_FS_OTP_I2CDEVADDR_D15       (0x0FU << FS8X_FS_OTP_I2CDEVADDR_SHIFT) /*!< Address D15 */
//
//#define FS8X_FS_OTP_FLT_RECOVERY_EN_DISABLED (0x00U << FS8X_FS_OTP_FLT_RECOVERY_EN_SHIFT) /*!< Disabled */
//#define FS8X_FS_OTP_FLT_RECOVERY_EN_ENABLED (0x01U << FS8X_FS_OTP_FLT_RECOVERY_EN_SHIFT) /*!< Enabled */
//
///******************************************************************************/
///* OTP_FS_S1_CRC_LSB - Type: RW                                               */
///******************************************************************************/
//
//#define FS8X_FS_OTP_FS_S1_CRC_LSB_ADDR   0x16U
//#define FS8X_FS_OTP_FS_S1_CRC_LSB_DEFAULT 0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S1_CRC_LSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S1_CRC_LSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_FS_S1_CRC_MSB - Type: RW                                               */
///******************************************************************************/
//
//#define FS8X_FS_OTP_FS_S1_CRC_MSB_ADDR   0x17U
//#define FS8X_FS_OTP_FS_S1_CRC_MSB_DEFAULT 0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S1_CRC_MSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S1_CRC_MSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_1 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_1_ADDR          0x18U
//#define FS8X_FS_OTP_MARK_1_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_MARK0_MASK           0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_MARK0_SHIFT          0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_2 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_2_ADDR          0x19U
//#define FS8X_FS_OTP_MARK_2_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_MARK1_MASK           0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_MARK1_SHIFT          0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_3 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_3_ADDR          0x1AU
//#define FS8X_FS_OTP_MARK_3_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_MARK2_MASK           0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_MARK2_SHIFT          0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_4 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_4_ADDR          0x1BU
//#define FS8X_FS_OTP_MARK_4_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_MARK3_MASK           0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_MARK3_SHIFT          0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_5 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_5_ADDR          0x1CU
//#define FS8X_FS_OTP_MARK_5_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_MARK4_MASK           0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_MARK4_SHIFT          0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_6 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_6_ADDR          0x1DU
//#define FS8X_FS_OTP_MARK_6_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S2_CRC_LSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S2_CRC_LSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* OTP_MARK_7 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTP_MARK_7_ADDR          0x1EU
//#define FS8X_FS_OTP_MARK_7_DEFAULT       0x00U
//
//#define FS8X_FS_OTP_OTP_FS_S2_CRC_MSB_MASK 0xFFU /*!< N/A */
//
//#define FS8X_FS_OTP_OTP_FS_S2_CRC_MSB_SHIFT 0x00U /*!< N/A */
//
///******************************************************************************/
///* M_FLAG - Type: RW                                                          */
///******************************************************************************/
//
//#define FS8X_M_FLAG_ADDR                 0x00U
//#define FS8X_M_FLAG_DEFAULT              0x0000U
//
//#define FS8X_M_I2C_M_REQ_MASK            0x0001U /*!< Invalid Main Domain I2C access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address). */
//#define FS8X_M_I2C_M_CRC_MASK            0x0002U /*!< Main Domain I2C communication CRC issue. */
//#define FS8X_M_SPI_M_CRC_MASK            0x0004U /*!< Main Domain SPI communication CRC issue */
//#define FS8X_M_SPI_M_REQ_MASK            0x0008U /*!< Invalid Main domain SPI access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address). */
//#define FS8X_M_SPI_M_CLK_MASK            0x0010U /*!< Main Domain SPI SCLK error detection. */
//#define FS8X_M_VLDO2_G_MASK              0x0080U /*!< Report an event on LDO2 (status change or failure) */
//#define FS8X_M_VLDO1_G_MASK              0x0100U /*!< Report an event on LDO1 (status change or failure) */
//#define FS8X_M_VBUCK3_G_MASK             0x0200U /*!< Report an event on BUCK3 (status change or failure) */
//#define FS8X_M_VBUCK2_G_MASK             0x0400U /*!< Report an event on BUCK2 (status change or failure) */
//#define FS8X_M_VBUCK1_G_MASK             0x0800U /*!< Report an event on BUCK1 (status change or failure) */
//#define FS8X_M_VBOOST_G_MASK             0x1000U /*!< Report an event on VBOOST (status change or failure) */
//#define FS8X_M_VPRE_G_MASK               0x2000U /*!< Report an event on VPRE (status change or failure) */
//#define FS8X_M_WU_G_MASK                 0x4000U /*!< Report a wake-up event. Logical OR of WAKE1 and WAKE2 source */
//#define FS8X_M_COM_ERR_MASK              0x8000U /*!< Report an error in the Communication (SPI or I2C) */
//
//#define FS8X_M_I2C_M_REQ_SHIFT           0x0000U /*!< Invalid Main Domain I2C access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address). */
//#define FS8X_M_I2C_M_CRC_SHIFT           0x0001U /*!< Main Domain I2C communication CRC issue. */
//#define FS8X_M_SPI_M_CRC_SHIFT           0x0002U /*!< Main Domain SPI communication CRC issue */
//#define FS8X_M_SPI_M_REQ_SHIFT           0x0003U /*!< Invalid Main domain SPI access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address). */
//#define FS8X_M_SPI_M_CLK_SHIFT           0x0004U /*!< Main Domain SPI SCLK error detection. */
//#define FS8X_M_VLDO2_G_SHIFT             0x0007U /*!< Report an event on LDO2 (status change or failure) */
//#define FS8X_M_VLDO1_G_SHIFT             0x0008U /*!< Report an event on LDO1 (status change or failure) */
//#define FS8X_M_VBUCK3_G_SHIFT            0x0009U /*!< Report an event on BUCK3 (status change or failure) */
//#define FS8X_M_VBUCK2_G_SHIFT            0x000AU /*!< Report an event on BUCK2 (status change or failure) */
//#define FS8X_M_VBUCK1_G_SHIFT            0x000BU /*!< Report an event on BUCK1 (status change or failure) */
//#define FS8X_M_VBOOST_G_SHIFT            0x000CU /*!< Report an event on VBOOST (status change or failure) */
//#define FS8X_M_VPRE_G_SHIFT              0x000DU /*!< Report an event on VPRE (status change or failure) */
//#define FS8X_M_WU_G_SHIFT                0x000EU /*!< Report a wake-up event. Logical OR of WAKE1 and WAKE2 source */
//#define FS8X_M_COM_ERR_SHIFT             0x000FU /*!< Report an error in the Communication (SPI or I2C) */
//
//#define FS8X_M_I2C_M_REQ_NO_ERROR        (0x0000U << FS8X_M_I2C_M_REQ_SHIFT) /*!< No error */
//#define FS8X_M_I2C_M_REQ_I2C_V           (0x0001U << FS8X_M_I2C_M_REQ_SHIFT) /*!< I2C Violation */
//
//#define FS8X_M_I2C_M_CRC_NO_ERROR        (0x0000U << FS8X_M_I2C_M_CRC_SHIFT) /*!< No error */
//#define FS8X_M_I2C_M_CRC_ERROR           (0x0001U << FS8X_M_I2C_M_CRC_SHIFT) /*!< Error detected in the I2C CRC */
//
//#define FS8X_M_SPI_M_CRC_NO_ERROR        (0x0000U << FS8X_M_SPI_M_CRC_SHIFT) /*!< No error */
//#define FS8X_M_SPI_M_CRC_ERROR           (0x0001U << FS8X_M_SPI_M_CRC_SHIFT) /*!< Error detected in the SPI CRC */
//
//#define FS8X_M_SPI_M_REQ_NO_ERROR        (0x0000U << FS8X_M_SPI_M_REQ_SHIFT) /*!< No error */
//#define FS8X_M_SPI_M_REQ_SPI_V           (0x0001U << FS8X_M_SPI_M_REQ_SHIFT) /*!< SPI Violation */
//
//#define FS8X_M_SPI_M_CLK_NO_ERROR        (0x0000U << FS8X_M_SPI_M_CLK_SHIFT) /*!< No error */
//#define FS8X_M_SPI_M_CLK_WRONG           (0x0001U << FS8X_M_SPI_M_CLK_SHIFT) /*!< Wrong number of clock cycles (<32 or >32) */
//
//#define FS8X_M_VLDO2_G_NO_EVENT          (0x0000U << FS8X_M_VLDO2_G_SHIFT) /*!< No event */
//#define FS8X_M_VLDO2_G_EVENT_OCCURRED    (0x0001U << FS8X_M_VLDO2_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VLDO1_G_NO_EVENT          (0x0000U << FS8X_M_VLDO1_G_SHIFT) /*!< No event */
//#define FS8X_M_VLDO1_G_EVENT_OCCURRED    (0x0001U << FS8X_M_VLDO1_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VBUCK3_G_NO_EVENT         (0x0000U << FS8X_M_VBUCK3_G_SHIFT) /*!< No event */
//#define FS8X_M_VBUCK3_G_EVENT_OCCURRED   (0x0001U << FS8X_M_VBUCK3_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VBUCK2_G_NO_EVENT         (0x0000U << FS8X_M_VBUCK2_G_SHIFT) /*!< No event */
//#define FS8X_M_VBUCK2_G_EVENT_OCCURRED   (0x0001U << FS8X_M_VBUCK2_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VBUCK1_G_NO_EVENT         (0x0000U << FS8X_M_VBUCK1_G_SHIFT) /*!< No event */
//#define FS8X_M_VBUCK1_G_EVENT_OCCURRED   (0x0001U << FS8X_M_VBUCK1_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VBOOST_G_NO_EVENT         (0x0000U << FS8X_M_VBOOST_G_SHIFT) /*!< No event */
//#define FS8X_M_VBOOST_G_EVENT_OCCURRED   (0x0001U << FS8X_M_VBOOST_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VPRE_G_NO_EVENT           (0x0000U << FS8X_M_VPRE_G_SHIFT) /*!< No event */
//#define FS8X_M_VPRE_G_EVENT_OCCURRED     (0x0001U << FS8X_M_VPRE_G_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_WU_G_NO_WAKE_EVENT        (0x0000U << FS8X_M_WU_G_SHIFT) /*!< No Wake event */
//#define FS8X_M_WU_G_WAKE_EVENT           (0x0001U << FS8X_M_WU_G_SHIFT) /*!< Wake event */
//
//#define FS8X_M_COM_ERR_NO_FAILURE        (0x0000U << FS8X_M_COM_ERR_SHIFT) /*!< No Failure */
//#define FS8X_M_COM_ERR_FAILURE           (0x0001U << FS8X_M_COM_ERR_SHIFT) /*!< Failure */
//
///******************************************************************************/
///* M_MODE - Type: RW                                                          */
///******************************************************************************/
//
//#define FS8X_M_MODE_ADDR                 0x01U
//#define FS8X_M_MODE_DEFAULT              0x0000U
//
//#define FS8X_M_GOTOSTBY_MASK             0x0001U /*!< Entry in Standby mode */
//#define FS8X_M_W1DIS_MASK                0x0002U /*!< WAKE1 wake up disable */
//#define FS8X_M_W2DIS_MASK                0x0004U /*!< WAKE2 wake up disable */
//#define FS8X_M_MAIN_NORMAL_MASK          0x0020U /*!< State machine Normal mode */
//#define FS8X_M_EXT_FIN_DIS_MASK          0x0040U /*!< EXT FIN selection disable at PLL input request */
//
//#define FS8X_M_GOTOSTBY_SHIFT            0x0000U /*!< Entry in Standby mode */
//#define FS8X_M_W1DIS_SHIFT               0x0001U /*!< WAKE1 wake up disable */
//#define FS8X_M_W2DIS_SHIFT               0x0002U /*!< WAKE2 wake up disable */
//#define FS8X_M_MAIN_NORMAL_SHIFT         0x0005U /*!< State machine Normal mode */
//#define FS8X_M_EXT_FIN_DIS_SHIFT         0x0006U /*!< EXT FIN selection disable at PLL input request */
//
//#define FS8X_M_GOTOSTBY_REMAINS_IN_CURRENT_STATE (0x0000U << FS8X_M_GOTOSTBY_SHIFT) /*!< Device remains in current state */
//#define FS8X_M_GOTOSTBY_ENTER_IN_STANDBY_MODE (0x0001U << FS8X_M_GOTOSTBY_SHIFT) /*!< Device will enter in Standby mode */
//
//#define FS8X_M_W1DIS_WAKE_UP_ENABLE      (0x0000U << FS8X_M_W1DIS_SHIFT) /*!< wake up enable */
//#define FS8X_M_W1DIS_WAKE_UP_DISABLE     (0x0001U << FS8X_M_W1DIS_SHIFT) /*!< wake up disable */
//
//#define FS8X_M_W2DIS_WAKE_UP_ENABLE      (0x0000U << FS8X_M_W2DIS_SHIFT) /*!< wake up enable */
//#define FS8X_M_W2DIS_WAKE_UP_DISABLE     (0x0001U << FS8X_M_W2DIS_SHIFT) /*!< wake up disable */
//
//#define FS8X_M_MAIN_NORMAL_NOT_IN_NORMAL_MODE (0x0000U << FS8X_M_MAIN_NORMAL_SHIFT) /*!< State Machine NOT in Normal mode */
//#define FS8X_M_MAIN_NORMAL_IN_NORMAL_MODE (0x0001U << FS8X_M_MAIN_NORMAL_SHIFT) /*!< State Machine in Normal mode - Entry in Standby mode possible */
//
//#define FS8X_M_EXT_FIN_DIS_NO_EFFECT     (0x0000U << FS8X_M_EXT_FIN_DIS_SHIFT) /*!< No effect */
//#define FS8X_M_EXT_FIN_DIS_DISABLE_FIN   (0x0001U << FS8X_M_EXT_FIN_DIS_SHIFT) /*!< Disable FIN selection */
//
///******************************************************************************/
///* M_REG_CTRL1 - Type: RW                                                     */
///******************************************************************************/

#define FS8X_M_REG_CTRL1_ADDR            0x02U
#define FS8X_M_REG_CTRL1_DEFAULT         0x0000U

#define FS8X_M_LDO2EN_MASK               0x0001U /*!< Enable request of LDO2 */
#define FS8X_M_LDO1EN_MASK               0x0002U /*!< Enable request of LDO1 */
#define FS8X_M_BUCK3EN_MASK              0x0004U /*!< Enable request of BUCK3 */
#define FS8X_M_BUCK2EN_MASK              0x0008U /*!< Enable request of BUCK2 */
#define FS8X_M_BUCK1EN_MASK              0x0010U /*!< Enable request of BUCK1 */
#define FS8X_M_BOOSTEN_MASK              0x0020U /*!< Enable request of BOOST */
#define FS8X_M_VPEN_MASK                 0x0040U /*!< Enable request of VPRE */
#define FS8X_M_LDO2DIS_MASK              0x0100U /*!< Disable request of LDO2 */
#define FS8X_M_LDO1DIS_MASK              0x0200U /*!< Disable request of LDO1 */
#define FS8X_M_BUCK3DIS_MASK             0x0400U /*!< Disable request of BUCK3 */
#define FS8X_M_BUCK2DIS_MASK             0x0800U /*!< Disable request of BUCK2 */
#define FS8X_M_BUCK1DIS_MASK             0x1000U /*!< Disable request of BUCK1 */
#define FS8X_M_BOOSTDIS_MASK             0x2000U /*!< Disable request of BOOST */
#define FS8X_M_VPDIS_MASK                0x4000U /*!< Disable request of VPRE */
#define FS8X_M_VPRE_PD_DIS_MASK          0x8000U /*!< Force disable of VPRE pull down. */

#define FS8X_M_LDO2EN_SHIFT              0x0000U /*!< Enable request of LDO2 */
#define FS8X_M_LDO1EN_SHIFT              0x0001U /*!< Enable request of LDO1 */
#define FS8X_M_BUCK3EN_SHIFT             0x0002U /*!< Enable request of BUCK3 */
#define FS8X_M_BUCK2EN_SHIFT             0x0003U /*!< Enable request of BUCK2 */
#define FS8X_M_BUCK1EN_SHIFT             0x0004U /*!< Enable request of BUCK1 */
#define FS8X_M_BOOSTEN_SHIFT             0x0005U /*!< Enable request of BOOST */
#define FS8X_M_VPEN_SHIFT                0x0006U /*!< Enable request of VPRE */
#define FS8X_M_LDO2DIS_SHIFT             0x0008U /*!< Disable request of LDO2 */
#define FS8X_M_LDO1DIS_SHIFT             0x0009U /*!< Disable request of LDO1 */
#define FS8X_M_BUCK3DIS_SHIFT            0x000AU /*!< Disable request of BUCK3 */
#define FS8X_M_BUCK2DIS_SHIFT            0x000BU /*!< Disable request of BUCK2 */
#define FS8X_M_BUCK1DIS_SHIFT            0x000CU /*!< Disable request of BUCK1 */
#define FS8X_M_BOOSTDIS_SHIFT            0x000DU /*!< Disable request of BOOST */
#define FS8X_M_VPDIS_SHIFT               0x000EU /*!< Disable request of VPRE */
#define FS8X_M_VPRE_PD_DIS_SHIFT         0x000FU /*!< Force disable of VPRE pull down. */

#define FS8X_M_LDO2EN_NO_EFFECT          (0x0000U << FS8X_M_LDO2EN_SHIFT) /*!< no effect (regulator remains in existing state - if ON it remains ON, if OFF it remains OFF) */
#define FS8X_M_LDO2EN_LDO2_ENABLE_REQUEST (0x0001U << FS8X_M_LDO2EN_SHIFT) /*!< LDO2 Enable Request */

#define FS8X_M_LDO1EN_NO_EFFECT          (0x0000U << FS8X_M_LDO1EN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_LDO1EN_LDO1_ENABLE_REQUEST (0x0001U << FS8X_M_LDO1EN_SHIFT) /*!< LDO1 Enable Request */

#define FS8X_M_BUCK3EN_NO_EFFECT         (0x0000U << FS8X_M_BUCK3EN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK3EN_BUCK3_ENABLE_REQUEST (0x0001U << FS8X_M_BUCK3EN_SHIFT) /*!< BUCK3 Enable Request */

#define FS8X_M_BUCK2EN_NO_EFFECT         (0x0000U << FS8X_M_BUCK2EN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK2EN_BUCK2_ENABLE_REQUEST (0x0001U << FS8X_M_BUCK2EN_SHIFT) /*!< BUCK2 Enable Request */

#define FS8X_M_BUCK1EN_NO_EFFECT         (0x0000U << FS8X_M_BUCK1EN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK1EN_BUCK1_ENABLE_REQUEST (0x0001U << FS8X_M_BUCK1EN_SHIFT) /*!< BUCK1 Enable Request */

#define FS8X_M_BOOSTEN_NO_EFFECT         (0x0000U << FS8X_M_BOOSTEN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BOOSTEN_BOOST_ENABLE_REQUEST (0x0001U << FS8X_M_BOOSTEN_SHIFT) /*!< BOOST Enable Request */

#define FS8X_M_VPEN_NO_EFFECT            (0x0000U << FS8X_M_VPEN_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_VPEN_VPRE_ENABLE_REQUEST  (0x0001U << FS8X_M_VPEN_SHIFT) /*!< VPRE Enable Request */

#define FS8X_M_LDO2DIS_NO_EFFECT         (0x0000U << FS8X_M_LDO2DIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_LDO2DIS_LDO2_DISABLE_REQUEST (0x0001U << FS8X_M_LDO2DIS_SHIFT) /*!< LDO2 Disable Request */

#define FS8X_M_LDO1DIS_NO_EFFECT         (0x0000U << FS8X_M_LDO1DIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_LDO1DIS_LDO1_DISABLE_REQUEST (0x0001U << FS8X_M_LDO1DIS_SHIFT) /*!< LDO1 Disable Request */

#define FS8X_M_BUCK3DIS_NO_EFFECT        (0x0000U << FS8X_M_BUCK3DIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK3DIS_BUCK3_DISABLE_REQUEST (0x0001U << FS8X_M_BUCK3DIS_SHIFT) /*!< BUCK3 Disable Request */

#define FS8X_M_BUCK2DIS_NO_EFFECT        (0x0000U << FS8X_M_BUCK2DIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK2DIS_BUCK2_DISABLE_REQUEST (0x0001U << FS8X_M_BUCK2DIS_SHIFT) /*!< BUCK2 Disable Request */

#define FS8X_M_BUCK1DIS_NO_EFFECT        (0x0000U << FS8X_M_BUCK1DIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BUCK1DIS_BUCK1_DISABLE_REQUEST (0x0001U << FS8X_M_BUCK1DIS_SHIFT) /*!< BUCK1 Disable Request */

#define FS8X_M_BOOSTDIS_NO_EFFECT        (0x0000U << FS8X_M_BOOSTDIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_BOOSTDIS_BOOST_DISABLE_REQUEST (0x0001U << FS8X_M_BOOSTDIS_SHIFT) /*!< BOOST Disable Request */

#define FS8X_M_VPDIS_NO_EFFECT           (0x0000U << FS8X_M_VPDIS_SHIFT) /*!< no effect (regulator remains in existing state) */
#define FS8X_M_VPDIS_VPRE_DISABLE_REQUEST (0x0001U << FS8X_M_VPDIS_SHIFT) /*!< VPRE Disable Request */

#define FS8X_M_VPRE_PD_DIS_NO_EFFECT     (0x0000U << FS8X_M_VPRE_PD_DIS_SHIFT) /*!< no effect (VPRE pull down is automatically controlled by the logic) */
#define FS8X_M_VPRE_PD_DIS_VPRE_DISABLE_REQUEST (0x0001U << FS8X_M_VPRE_PD_DIS_SHIFT) /*!< VPRE pull down disable Request */

///******************************************************************************/
///* M_REG_CTRL2 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_REG_CTRL2_ADDR            0x03U
//#define FS8X_M_REG_CTRL2_DEFAULT         0x0009U
//
//#define FS8X_M_VPRESRHS_MASK             0x0003U /*!< VPRE High Side slew rate control */
//#define FS8X_M_VPRESRLS_MASK             0x0018U /*!< VPRE Low Side slew rate control */
//#define FS8X_M_LDO2TSDCFG_MASK           0x0100U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_LDO1TSDCFG_MASK           0x0200U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK3TSDCFG_MASK          0x0400U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK2TSDCFG_MASK          0x0800U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK1TSDCFG_MASK          0x1000U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BOOSTTSDCFG_MASK          0x2000U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_VBSTSR_MASK               0xC000U /*!< VBOOST Low Side slew rate control */
//
//#define FS8X_M_VPRESRHS_SHIFT            0x0000U /*!< VPRE High Side slew rate control */
//#define FS8X_M_VPRESRLS_SHIFT            0x0003U /*!< VPRE Low Side slew rate control */
//#define FS8X_M_LDO2TSDCFG_SHIFT          0x0008U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_LDO1TSDCFG_SHIFT          0x0009U /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK3TSDCFG_SHIFT         0x000AU /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK2TSDCFG_SHIFT         0x000BU /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BUCK1TSDCFG_SHIFT         0x000CU /*!< Regulator behavior in case of TSD */
//#define FS8X_M_BOOSTTSDCFG_SHIFT         0x000DU /*!< Regulator behavior in case of TSD */
//#define FS8X_M_VBSTSR_SHIFT              0x000EU /*!< VBOOST Low Side slew rate control */
//
//#define FS8X_M_VPRESRHS_130MA_DRIVE_CAPABILITY (0x0000U << FS8X_M_VPRESRHS_SHIFT) /*!< 130mA typical drive capability - slow */
//#define FS8X_M_VPRESRHS_260MA_DRIVE_CAPABILITY (0x0001U << FS8X_M_VPRESRHS_SHIFT) /*!< 260mA typical drive capability - medium */
//#define FS8X_M_VPRESRHS_520MA_DRIVE_CAPABILITY (0x0002U << FS8X_M_VPRESRHS_SHIFT) /*!< 520mA typical drive capability - fast */
//#define FS8X_M_VPRESRHS_900MA_DRIVE_CAPABILITY (0x0003U << FS8X_M_VPRESRHS_SHIFT) /*!< 900mA typical drive capability - ultra fast */
//
//#define FS8X_M_VPRESRLS_130MA_DRIVE_CAPABILITY (0x0000U << FS8X_M_VPRESRLS_SHIFT) /*!< 130mA typical drive capability - slow */
//#define FS8X_M_VPRESRLS_260MA_DRIVE_CAPABILITY (0x0001U << FS8X_M_VPRESRLS_SHIFT) /*!< 260mA typical drive capability - medium */
//#define FS8X_M_VPRESRLS_520MA_DRIVE_CAPABILITY (0x0002U << FS8X_M_VPRESRLS_SHIFT) /*!< 520mA typical drive capability - fast */
//#define FS8X_M_VPRESRLS_900MA_DRIVE_CAPABILITY (0x0003U << FS8X_M_VPRESRLS_SHIFT) /*!< 900mA typical drive capability - ultra fast */
//
//#define FS8X_M_LDO2TSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_LDO2TSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_LDO2TSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_LDO2TSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_LDO1TSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_LDO1TSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_LDO1TSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_LDO1TSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_BUCK3TSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_BUCK3TSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_BUCK3TSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_BUCK3TSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_BUCK2TSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_BUCK2TSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_BUCK2TSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_BUCK2TSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_BUCK1TSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_BUCK1TSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_BUCK1TSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_BUCK1TSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_BOOSTTSDCFG_REGULATOR_SHUTDOWN (0x0000U << FS8X_M_BOOSTTSDCFG_SHIFT) /*!< Regulator Shutdown */
//#define FS8X_M_BOOSTTSDCFG_REGULATOR_SHUTDOWN_AND_STANDBY_MODE (0x0001U << FS8X_M_BOOSTTSDCFG_SHIFT) /*!< Regulator Shutdown + State machine transition to Standby mode */
//
//#define FS8X_M_VBSTSR_50V_US             (0x0000U << FS8X_M_VBSTSR_SHIFT) /*!< 50V/us */
//#define FS8X_M_VBSTSR_100V_US            (0x0001U << FS8X_M_VBSTSR_SHIFT) /*!< 100V/us */
//#define FS8X_M_VBSTSR_300V_US            (0x0002U << FS8X_M_VBSTSR_SHIFT) /*!< 300V/us */
//#define FS8X_M_VBSTSR_500V_US            (0x0003U << FS8X_M_VBSTSR_SHIFT) /*!< 500V/us */
//
///******************************************************************************/
///* M_AMUX - Type: RW                                                          */
///******************************************************************************/

#define FS8X_M_AMUX_ADDR                 0x04U
#define FS8X_M_AMUX_DEFAULT              0x0000U

#define FS8X_M_AMUX_MASK                 0x001FU /*!< Signal selection for AMUX output */
#define FS8X_M_RATIO_MASK                0x0020U /*!< Selection of divider ratio for Vsup, Wake1, Wake 2 inputs */

#define FS8X_M_AMUX_SHIFT                0x0000U /*!< Signal selection for AMUX output */
#define FS8X_M_RATIO_SHIFT               0x0005U /*!< Selection of divider ratio for Vsup, Wake1, Wake 2 inputs */

#define FS8X_M_AMUX_GND                  (0x0000U << FS8X_M_AMUX_SHIFT) /*!< GND */
#define FS8X_M_AMUX_VDDIO                (0x0001U << FS8X_M_AMUX_SHIFT) /*!< VDDIO */
#define FS8X_M_AMUX_TEMPERATURE_SENSOR   (0x0002U << FS8X_M_AMUX_SHIFT) /*!< Temperature Sensor : T(_C) = (VAMUX _ VTEMP25) / VTEMP_COEFF + 25 */
#define FS8X_M_AMUX_BAND_GAP_MAIN        (0x0003U << FS8X_M_AMUX_SHIFT) /*!< Band Gap Main */
#define FS8X_M_AMUX_BAND_GAP_FAIL_SAFE   (0x0004U << FS8X_M_AMUX_SHIFT) /*!< Band Gap Fail Safe */
#define FS8X_M_AMUX_VBUCK1_VOLTAGE       (0x0005U << FS8X_M_AMUX_SHIFT) /*!< VBUCK1 voltage */
#define FS8X_M_AMUX_VBUCK2_VOLTAGE       (0x0006U << FS8X_M_AMUX_SHIFT) /*!< VBUCK2 voltage */
#define FS8X_M_AMUX_VBUCK3_VOLTAGE_DIVIDED (0x0007U << FS8X_M_AMUX_SHIFT) /*!< VBUCK3 voltage divided by 2.5 */
#define FS8X_M_AMUX_VPRE_VOLTAGE_DIVIDED (0x0008U << FS8X_M_AMUX_SHIFT) /*!< VPRE voltage divided by 2.5 */
#define FS8X_M_AMUX_VBOOST_VOLTAGE_DIVIDED (0x0009U << FS8X_M_AMUX_SHIFT) /*!< VBOOST Voltage divided by 2.5 */
#define FS8X_M_AMUX_VLDO1_VOLTAGE_DIVIDED (0x000AU << FS8X_M_AMUX_SHIFT) /*!< VLDO1 voltage divided by 2.5 */
#define FS8X_M_AMUX_VLDO2_VOLTAGE_DIVIDED (0x000BU << FS8X_M_AMUX_SHIFT) /*!< VLDO2 voltage divided by 2.5 */
#define FS8X_M_AMUX_VBOS_VOLTAGE_DIVIDED (0x000CU << FS8X_M_AMUX_SHIFT) /*!< VBOS voltage divided by 2.5 */
#define FS8X_M_AMUX_RESERVED             (0x000DU << FS8X_M_AMUX_SHIFT) /*!< RESERVED */
#define FS8X_M_AMUX_VSUP1_VOLTAGE_DIVIDED (0x000EU << FS8X_M_AMUX_SHIFT) /*!< VSUP1 voltage divided by 7.5 or 14 (SPI/I2C configuration with bit RATIO) */
#define FS8X_M_AMUX_WAKE1_VOLTAGE_DIVIDED (0x000FU << FS8X_M_AMUX_SHIFT) /*!< WAKE1 voltage divided by 7.5 or 14 (SPI/I2C configuration with bit RATIO) */
#define FS8X_M_AMUX_WAKE2_VOLTAGE_DIVIDED (0x0010U << FS8X_M_AMUX_SHIFT) /*!< WAKE2 voltage divided by 7.5 or 14 (SPI/I2C configuration with bit RATIO) */
#define FS8X_M_AMUX_VANA                 (0x0011U << FS8X_M_AMUX_SHIFT) /*!< Vana: internal Main analog voltage supp */
#define FS8X_M_AMUX_VDIG                 (0x0012U << FS8X_M_AMUX_SHIFT) /*!< Vdig: internal Main digital voltage suppl */
#define FS8X_M_AMUX_VDIG_FS              (0x0013U << FS8X_M_AMUX_SHIFT) /*!< Vdig_fs: internal Fail Safe digital voltage supp */
#define FS8X_M_AMUX_PSYNC_VOLTAGE        (0x0014U << FS8X_M_AMUX_SHIFT) /*!< PSYNC voltage */

#define FS8X_M_RATIO_RATIO_7_5           (0x0000U << FS8X_M_RATIO_SHIFT) /*!< Ratio = 7.5 */
#define FS8X_M_RATIO_RATIO_14            (0x0001U << FS8X_M_RATIO_SHIFT) /*!< Ratio = 14 */

///******************************************************************************/
///* M_CLOCK - Type: RW                                                         */
///******************************************************************************/
//
#define FS8X_M_CLOCK_ADDR                0x05U
#define FS8X_M_CLOCK_DEFAULT             0x0000U

#define FS8X_M_CLK_TUNE_MASK             0x000FU /*!< Oscillator Frequency [MHz] */
#define FS8X_M_MOD_EN_MASK               0x0010U /*!< CLOCK Modulation */
#define FS8X_M_FIN_DIV_MASK              0x0020U /*!< FIN input signal divider selection */
#define FS8X_M_EXT_FIN_SEL_MASK          0x0040U /*!< EXT FIN selection at PLL input */
#define FS8X_M_FOUT_CLK_SEL_MASK         0x0080U /*!< FOUT frequency selection (CLK1 or CLK2) */
#define FS8X_M_FOUT_PHASE_MASK           0x0700U /*!< FOUT phase shifting configuration. */
#define FS8X_M_FOUT_MUX_SEL_MASK         0x7800U /*!< Fout Multiplexer selection */
#define FS8X_M_MOD_CONF_MASK             0x8000U /*!< CLOCK Modulation Configuration */

#define FS8X_M_CLK_TUNE_SHIFT            0x0000U /*!< Oscillator Frequency [MHz] */
#define FS8X_M_MOD_EN_SHIFT              0x0004U /*!< CLOCK Modulation */
#define FS8X_M_FIN_DIV_SHIFT             0x0005U /*!< FIN input signal divider selection */
#define FS8X_M_EXT_FIN_SEL_SHIFT         0x0006U /*!< EXT FIN selection at PLL input */
#define FS8X_M_FOUT_CLK_SEL_SHIFT        0x0007U /*!< FOUT frequency selection (CLK1 or CLK2) */
#define FS8X_M_FOUT_PHASE_SHIFT          0x0008U /*!< FOUT phase shifting configuration. */
#define FS8X_M_FOUT_MUX_SEL_SHIFT        0x000BU /*!< Fout Multiplexer selection */
#define FS8X_M_MOD_CONF_SHIFT            0x000FU /*!< CLOCK Modulation Configuration */

#define FS8X_M_CLK_TUNE_20               (0x0000U << FS8X_M_CLK_TUNE_SHIFT) /*!< 20 */
#define FS8X_M_CLK_TUNE_21               (0x0001U << FS8X_M_CLK_TUNE_SHIFT) /*!< 21 */
#define FS8X_M_CLK_TUNE_22               (0x0002U << FS8X_M_CLK_TUNE_SHIFT) /*!< 22 */
#define FS8X_M_CLK_TUNE_23               (0x0003U << FS8X_M_CLK_TUNE_SHIFT) /*!< 23 */
#define FS8X_M_CLK_TUNE_24               (0x0004U << FS8X_M_CLK_TUNE_SHIFT) /*!< 24 */
#define FS8X_M_CLK_TUNE_16               (0x0009U << FS8X_M_CLK_TUNE_SHIFT) /*!< 16 */
#define FS8X_M_CLK_TUNE_17               (0x000AU << FS8X_M_CLK_TUNE_SHIFT) /*!< 17 */
#define FS8X_M_CLK_TUNE_18               (0x000BU << FS8X_M_CLK_TUNE_SHIFT) /*!< 18 */
#define FS8X_M_CLK_TUNE_19               (0x000CU << FS8X_M_CLK_TUNE_SHIFT) /*!< 19 */

#define FS8X_M_MOD_EN_MODULATION_DISABLE (0x0000U << FS8X_M_MOD_EN_SHIFT) /*!< Modulation Disable */
#define FS8X_M_MOD_EN_MODULATION_ENABLE  (0x0001U << FS8X_M_MOD_EN_SHIFT) /*!< Modulation Enable */

#define FS8X_M_FIN_DIV_DIVIDER_BY_1      (0x0000U << FS8X_M_FIN_DIV_SHIFT) /*!< Divider by 1 */
#define FS8X_M_FIN_DIV_DIVIDER_BY_6      (0x0001U << FS8X_M_FIN_DIV_SHIFT) /*!< Divider by 6 */

#define FS8X_M_EXT_FIN_SEL_DIS           (0x0000U << FS8X_M_EXT_FIN_SEL_SHIFT) /*!< DIS */
#define FS8X_M_EXT_FIN_SEL_EN            (0x0001U << FS8X_M_EXT_FIN_SEL_SHIFT) /*!< EN */

#define FS8X_M_FOUT_CLK_SEL_CLK1         (0x0000U << FS8X_M_FOUT_CLK_SEL_SHIFT) /*!< CLK1 */
#define FS8X_M_FOUT_CLK_SEL_CLK2         (0x0001U << FS8X_M_FOUT_CLK_SEL_SHIFT) /*!< CLK2 */

#define FS8X_M_FOUT_PHASE_NO_SHIFT       (0x0000U << FS8X_M_FOUT_PHASE_SHIFT) /*!< No shift */
#define FS8X_M_FOUT_PHASE_1CLK           (0x0001U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 1 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_2CLK           (0x0002U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 2 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_3CLK           (0x0003U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 3 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_4CLK           (0x0004U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 4 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_5CLK           (0x0005U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 5 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_6CLK           (0x0006U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 6 clock cycle of CLK running at 20MHz */
#define FS8X_M_FOUT_PHASE_7CLK           (0x0007U << FS8X_M_FOUT_PHASE_SHIFT) /*!< Shifted by 7 clock cycle of CLK running at 20MHz */

#define FS8X_M_FOUT_MUX_SEL_NO_SIGNAL    (0x0000U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< No signal, Fout Low */
#define FS8X_M_FOUT_MUX_SEL_VPRE_CLK     (0x0001U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< VPRE_clk */
#define FS8X_M_FOUT_MUX_SEL_BUCKS_BOOST_CLK (0x0003U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< BUCKs & Boost_clk */
#define FS8X_M_FOUT_MUX_SEL_CLK1         (0x0006U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< CLK1 with FOUT_sel = 0 */
#define FS8X_M_FOUT_MUX_SEL_CLK2         (0x0006U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< CLK2 with FOUT_sel = 1 */
#define FS8X_M_FOUT_MUX_SEL_CLOCK_FIN_DIV (0x0009U << FS8X_M_FOUT_MUX_SEL_SHIFT) /*!< CLOCK_FIN_DIV */

#define FS8X_M_MOD_CONF_23KHZ            (0x0000U << FS8X_M_MOD_CONF_SHIFT) /*!< range +- 5% 23kHz */
#define FS8X_M_MOD_CONF_94KHZ            (0x0001U << FS8X_M_MOD_CONF_SHIFT) /*!< range +- 5% 94kHz */
//
///******************************************************************************/
///* M_INT_MASK1 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_INT_MASK1_ADDR            0x06U
//#define FS8X_M_INT_MASK1_DEFAULT         0x0000U
//
//#define FS8X_M_LDO2TSD_M_MASK            0x0001U /*!< Inhibit INTERRUPT for LDO2 over temperature shutdown event */
//#define FS8X_M_LDO1TSD_M_MASK            0x0002U /*!< Inhibit INTERRUPT for LDO1 over temperature shutdown event */
//#define FS8X_M_BUCK3TSD_M_MASK           0x0004U /*!< Inhibit INTERRUPT for BUCK3 over temperature shutdown event */
//#define FS8X_M_BUCK2TSD_M_MASK           0x0008U /*!< Inhibit INTERRUPT for BUCK2 over temperature shutdown event */
//#define FS8X_M_BUCK1TSD_M_MASK           0x0010U /*!< Inhibit INTERRUPT for BUCK1 over temperature shutdown event */
//#define FS8X_M_BOOSTTSD_M_MASK           0x0020U /*!< Inhibit INTERRUPT for BOOST over temperature shutdown event */
//#define FS8X_M_BOSTSD_M_MASK             0x0040U /*!< Inhibit INTERRUPT for Best Of Supply over temperature shutdown event */
//#define FS8X_M_LDO2OC_M_MASK             0x0100U /*!< Inhibit INTERRUPT for LDO2 Over current */
//#define FS8X_M_LDO1OC_M_MASK             0x0200U /*!< Inhibit INTERRUPT for LDO1 Over current */
//#define FS8X_M_BUCK3OC_M_MASK            0x0400U /*!< Inhibit INTERRUPT for BUCK3 Over current */
//#define FS8X_M_BUCK2OC_M_MASK            0x0800U /*!< Inhibit INTERRUPT for BUCK2 Over current */
//#define FS8X_M_BUCK1OC_M_MASK            0x1000U /*!< Inhibit INTERRUPT for BUCK1 Over current */
//#define FS8X_M_BOOSTOC_M_MASK            0x2000U /*!< Inhibit INTERRUPT for VBOOST Over current */
//#define FS8X_M_VPREOC_M_MASK             0x4000U /*!< Inhibit INTERRUPT for VPRE Over current */
//
//#define FS8X_M_LDO2TSD_M_SHIFT           0x0000U /*!< Inhibit INTERRUPT for LDO2 over temperature shutdown event */
//#define FS8X_M_LDO1TSD_M_SHIFT           0x0001U /*!< Inhibit INTERRUPT for LDO1 over temperature shutdown event */
//#define FS8X_M_BUCK3TSD_M_SHIFT          0x0002U /*!< Inhibit INTERRUPT for BUCK3 over temperature shutdown event */
//#define FS8X_M_BUCK2TSD_M_SHIFT          0x0003U /*!< Inhibit INTERRUPT for BUCK2 over temperature shutdown event */
//#define FS8X_M_BUCK1TSD_M_SHIFT          0x0004U /*!< Inhibit INTERRUPT for BUCK1 over temperature shutdown event */
//#define FS8X_M_BOOSTTSD_M_SHIFT          0x0005U /*!< Inhibit INTERRUPT for BOOST over temperature shutdown event */
//#define FS8X_M_BOSTSD_M_SHIFT            0x0006U /*!< Inhibit INTERRUPT for Best Of Supply over temperature shutdown event */
//#define FS8X_M_LDO2OC_M_SHIFT            0x0008U /*!< Inhibit INTERRUPT for LDO2 Over current */
//#define FS8X_M_LDO1OC_M_SHIFT            0x0009U /*!< Inhibit INTERRUPT for LDO1 Over current */
//#define FS8X_M_BUCK3OC_M_SHIFT           0x000AU /*!< Inhibit INTERRUPT for BUCK3 Over current */
//#define FS8X_M_BUCK2OC_M_SHIFT           0x000BU /*!< Inhibit INTERRUPT for BUCK2 Over current */
//#define FS8X_M_BUCK1OC_M_SHIFT           0x000CU /*!< Inhibit INTERRUPT for BUCK1 Over current */
//#define FS8X_M_BOOSTOC_M_SHIFT           0x000DU /*!< Inhibit INTERRUPT for VBOOST Over current */
//#define FS8X_M_VPREOC_M_SHIFT            0x000EU /*!< Inhibit INTERRUPT for VPRE Over current */
//
//#define FS8X_M_LDO2TSD_M_INT_NOT_MASKED  (0x0000U << FS8X_M_LDO2TSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_LDO2TSD_M_INT_MASKED      (0x0001U << FS8X_M_LDO2TSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_LDO1TSD_M_INT_NOT_MASKED  (0x0000U << FS8X_M_LDO1TSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_LDO1TSD_M_INT_MASKED      (0x0001U << FS8X_M_LDO1TSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK3TSD_M_INT_NOT_MASKED (0x0000U << FS8X_M_BUCK3TSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK3TSD_M_INT_MASKED     (0x0001U << FS8X_M_BUCK3TSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK2TSD_M_INT_NOT_MASKED (0x0000U << FS8X_M_BUCK2TSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK2TSD_M_INT_MASKED     (0x0001U << FS8X_M_BUCK2TSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK1TSD_M_INT_NOT_MASKED (0x0000U << FS8X_M_BUCK1TSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK1TSD_M_INT_MASKED     (0x0001U << FS8X_M_BUCK1TSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BOOSTTSD_M_INT_NOT_MASKED (0x0000U << FS8X_M_BOOSTTSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BOOSTTSD_M_INT_MASKED     (0x0001U << FS8X_M_BOOSTTSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BOSTSD_M_INT_NOT_MASKED   (0x0000U << FS8X_M_BOSTSD_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BOSTSD_M_INT_MASKED       (0x0001U << FS8X_M_BOSTSD_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_LDO2OC_M_INT_NOT_MASKED   (0x0000U << FS8X_M_LDO2OC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_LDO2OC_M_INT_MASKED       (0x0001U << FS8X_M_LDO2OC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_LDO1OC_M_INT_NOT_MASKED   (0x0000U << FS8X_M_LDO1OC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_LDO1OC_M_INT_MASKED       (0x0001U << FS8X_M_LDO1OC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK3OC_M_INT_NOT_MASKED  (0x0000U << FS8X_M_BUCK3OC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK3OC_M_INT_MASKED      (0x0001U << FS8X_M_BUCK3OC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK2OC_M_INT_NOT_MASKED  (0x0000U << FS8X_M_BUCK2OC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK2OC_M_INT_MASKED      (0x0001U << FS8X_M_BUCK2OC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BUCK1OC_M_INT_NOT_MASKED  (0x0000U << FS8X_M_BUCK1OC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BUCK1OC_M_INT_MASKED      (0x0001U << FS8X_M_BUCK1OC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_BOOSTOC_M_INT_NOT_MASKED  (0x0000U << FS8X_M_BOOSTOC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_BOOSTOC_M_INT_MASKED      (0x0001U << FS8X_M_BOOSTOC_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VPREOC_M_INT_NOT_MASKED   (0x0000U << FS8X_M_VPREOC_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VPREOC_M_INT_MASKED       (0x0001U << FS8X_M_VPREOC_M_SHIFT) /*!< INT masked */
//
///******************************************************************************/
///* M_INT_MASK2 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_INT_MASK2_ADDR            0x07U
//#define FS8X_M_INT_MASK2_DEFAULT         0x0000U
//
//#define FS8X_M_WAKE2_M_MASK              0x0001U /*!< Inhibit INTERRUPT for WAKE2 any transition */
//#define FS8X_M_WAKE1_M_MASK              0x0002U /*!< Inhibit INTERRUPT for WAKE1 any transition */
//#define FS8X_M_VSUPUVH_M_MASK            0x0004U /*!< Inhibit INTERRUPT for VSUP_UVH */
//#define FS8X_M_VSUPUVL_M_MASK            0x0008U /*!< Inhibit INTERRUPT for VSUP_UVL */
//#define FS8X_M_VPREUVH_M_MASK            0x0010U /*!< Inhibit INTERRUPT for VPRE_UVH */
//#define FS8X_M_VPREUVL_M_MASK            0x0020U /*!< Inhibit INTERRUPT for VPRE_UVL */
//#define FS8X_M_VSUPUV7_M_MASK            0x0040U /*!< Inhibit INTERRUPT for VSUP_UV7 */
//#define FS8X_M_VBOOST_UVH_M_MASK         0x0080U /*!< Inhibit INTERRUPT for VBOOST_UVH */
//#define FS8X_M_VPRE_FB_OV_M_MASK         0x0100U /*!< Inhibit INTERRUPT for VPRE_FB_OV */
//#define FS8X_M_COM_M_MASK                0x0200U /*!< Inhibit INTERRUPT for COM any transition */
//#define FS8X_M_VBOSUVH_M_MASK            0x0400U /*!< Inhibit INTERRUPT for VBOS_UVH any transition */
//#define FS8X_M_VBOOSTOV_M_MASK           0x0800U /*!< Inhibit INTERRUPT for VBOOST_OV any transition */
//
//#define FS8X_M_WAKE2_M_SHIFT             0x0000U /*!< Inhibit INTERRUPT for WAKE2 any transition */
//#define FS8X_M_WAKE1_M_SHIFT             0x0001U /*!< Inhibit INTERRUPT for WAKE1 any transition */
//#define FS8X_M_VSUPUVH_M_SHIFT           0x0002U /*!< Inhibit INTERRUPT for VSUP_UVH */
//#define FS8X_M_VSUPUVL_M_SHIFT           0x0003U /*!< Inhibit INTERRUPT for VSUP_UVL */
//#define FS8X_M_VPREUVH_M_SHIFT           0x0004U /*!< Inhibit INTERRUPT for VPRE_UVH */
//#define FS8X_M_VPREUVL_M_SHIFT           0x0005U /*!< Inhibit INTERRUPT for VPRE_UVL */
//#define FS8X_M_VSUPUV7_M_SHIFT           0x0006U /*!< Inhibit INTERRUPT for VSUP_UV7 */
//#define FS8X_M_VBOOST_UVH_M_SHIFT        0x0007U /*!< Inhibit INTERRUPT for VBOOST_UVH */
//#define FS8X_M_VPRE_FB_OV_M_SHIFT        0x0008U /*!< Inhibit INTERRUPT for VPRE_FB_OV */
//#define FS8X_M_COM_M_SHIFT               0x0009U /*!< Inhibit INTERRUPT for COM any transition */
//#define FS8X_M_VBOSUVH_M_SHIFT           0x000AU /*!< Inhibit INTERRUPT for VBOS_UVH any transition */
//#define FS8X_M_VBOOSTOV_M_SHIFT          0x000BU /*!< Inhibit INTERRUPT for VBOOST_OV any transition */
//
//#define FS8X_M_WAKE2_M_INT_NOT_MASKED    (0x0000U << FS8X_M_WAKE2_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_WAKE2_M_INT_MASKED        (0x0001U << FS8X_M_WAKE2_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_WAKE1_M_INT_NOT_MASKED    (0x0000U << FS8X_M_WAKE1_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_WAKE1_M_INT_MASKED        (0x0001U << FS8X_M_WAKE1_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VSUPUVH_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VSUPUVH_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VSUPUVH_M_INT_MASKED      (0x0001U << FS8X_M_VSUPUVH_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VSUPUVL_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VSUPUVL_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VSUPUVL_M_INT_MASKED      (0x0001U << FS8X_M_VSUPUVL_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VPREUVH_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VPREUVH_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VPREUVH_M_INT_MASKED      (0x0001U << FS8X_M_VPREUVH_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VPREUVL_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VPREUVL_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VPREUVL_M_INT_MASKED      (0x0001U << FS8X_M_VPREUVL_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VSUPUV7_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VSUPUV7_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VSUPUV7_M_INT_MASKED      (0x0001U << FS8X_M_VSUPUV7_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VBOOST_UVH_M_INT_NOT_MASKED (0x0000U << FS8X_M_VBOOST_UVH_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VBOOST_UVH_M_INT_MASKED   (0x0001U << FS8X_M_VBOOST_UVH_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VPRE_FB_OV_M_INT_NOT_MASKED (0x0000U << FS8X_M_VPRE_FB_OV_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VPRE_FB_OV_M_INT_MASKED   (0x0001U << FS8X_M_VPRE_FB_OV_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_COM_M_INT_NOT_MASKED      (0x0000U << FS8X_M_COM_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_COM_M_INT_MASKED          (0x0001U << FS8X_M_COM_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VBOSUVH_M_INT_NOT_MASKED  (0x0000U << FS8X_M_VBOSUVH_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VBOSUVH_M_INT_MASKED      (0x0001U << FS8X_M_VBOSUVH_M_SHIFT) /*!< INT masked */
//
//#define FS8X_M_VBOOSTOV_M_INT_NOT_MASKED (0x0000U << FS8X_M_VBOOSTOV_M_SHIFT) /*!< INT not masked */
//#define FS8X_M_VBOOSTOV_M_INT_MASKED     (0x0001U << FS8X_M_VBOOSTOV_M_SHIFT) /*!< INT masked */
//
///******************************************************************************/
///* M_FLAG1 - Type: RW                                                         */
///******************************************************************************/
//
#define FS8X_M_FLAG1_ADDR                0x08U
#define FS8X_M_FLAG1_DEFAULT             0x0000U

#define FS8X_M_LDO2OT_MASK               0x0001U /*!< LDO2 over temperature shutdown event */
#define FS8X_M_LDO1OT_MASK               0x0002U /*!< LDO1 over temperature shutdown event */
#define FS8X_M_BUCK3OT_MASK              0x0004U /*!< BUCK3 over temperature shutdown event */
#define FS8X_M_BUCK2OT_MASK              0x0008U /*!< BUCK2 over temperature shutdown event */
#define FS8X_M_BUCK1OT_MASK              0x0010U /*!< BUCK1 over temperature shutdown event */
#define FS8X_M_VBOOSTOT_MASK             0x0020U /*!< VBOOST over temperature shutdown event */
#define FS8X_M_VBOOSTOV_MASK             0x0040U /*!< VBOOST Over voltage protection event */
#define FS8X_M_CLK_FIN_DIV_OK_MASK       0x0080U /*!< CLK_FIN_DIV monitoring */
#define FS8X_M_LDO2OC_MASK               0x0100U /*!< LDO2 Over current event */
#define FS8X_M_LDO1OC_MASK               0x0200U /*!< LDO1 Over current event */
#define FS8X_M_BUCK3OC_MASK              0x0400U /*!< BUCK3 Over current */
#define FS8X_M_BUCK2OC_MASK              0x0800U /*!< BUCK2 Over current */
#define FS8X_M_BUCK1OC_MASK              0x1000U /*!< BUCK1 Over current */
#define FS8X_M_VPREOC_MASK               0x2000U /*!< VPRE Over current event */
#define FS8X_M_VBOOSTUVH_MASK            0x4000U /*!< VBOOST Under voltage high event (falling) */
#define FS8X_M_VBOSUVH_MASK              0x8000U /*!< VBOS Under voltage high event (falling) */

#define FS8X_M_LDO2OT_SHIFT              0x0000U /*!< LDO2 over temperature shutdown event */
#define FS8X_M_LDO1OT_SHIFT              0x0001U /*!< LDO1 over temperature shutdown event */
#define FS8X_M_BUCK3OT_SHIFT             0x0002U /*!< BUCK3 over temperature shutdown event */
#define FS8X_M_BUCK2OT_SHIFT             0x0003U /*!< BUCK2 over temperature shutdown event */
#define FS8X_M_BUCK1OT_SHIFT             0x0004U /*!< BUCK1 over temperature shutdown event */
#define FS8X_M_VBOOSTOT_SHIFT            0x0005U /*!< VBOOST over temperature shutdown event */
#define FS8X_M_VBOOSTOV_SHIFT            0x0006U /*!< VBOOST Over voltage protection event */
#define FS8X_M_CLK_FIN_DIV_OK_SHIFT      0x0007U /*!< CLK_FIN_DIV monitoring */
#define FS8X_M_LDO2OC_SHIFT              0x0008U /*!< LDO2 Over current event */
#define FS8X_M_LDO1OC_SHIFT              0x0009U /*!< LDO1 Over current event */
#define FS8X_M_BUCK3OC_SHIFT             0x000AU /*!< BUCK3 Over current */
#define FS8X_M_BUCK2OC_SHIFT             0x000BU /*!< BUCK2 Over current */
#define FS8X_M_BUCK1OC_SHIFT             0x000CU /*!< BUCK1 Over current */
#define FS8X_M_VPREOC_SHIFT              0x000DU /*!< VPRE Over current event */
#define FS8X_M_VBOOSTUVH_SHIFT           0x000EU /*!< VBOOST Under voltage high event (falling) */
#define FS8X_M_VBOSUVH_SHIFT             0x000FU /*!< VBOS Under voltage high event (falling) */

#define FS8X_M_LDO2OT_NO_EVENT           (0x0000U << FS8X_M_LDO2OT_SHIFT) /*!< No event */
#define FS8X_M_LDO2OT_EVENT_OCCURRED     (0x0001U << FS8X_M_LDO2OT_SHIFT) /*!< Event occurred */

#define FS8X_M_LDO1OT_NO_EVENT           (0x0000U << FS8X_M_LDO1OT_SHIFT) /*!< No event */
#define FS8X_M_LDO1OT_EVENT_OCCURRED     (0x0001U << FS8X_M_LDO1OT_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK3OT_NO_EVENT          (0x0000U << FS8X_M_BUCK3OT_SHIFT) /*!< No event */
#define FS8X_M_BUCK3OT_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK3OT_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK2OT_NO_EVENT          (0x0000U << FS8X_M_BUCK2OT_SHIFT) /*!< No event */
#define FS8X_M_BUCK2OT_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK2OT_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK1OT_NO_EVENT          (0x0000U << FS8X_M_BUCK1OT_SHIFT) /*!< No event */
#define FS8X_M_BUCK1OT_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK1OT_SHIFT) /*!< Event occurred */

#define FS8X_M_VBOOSTOT_NO_EVENT         (0x0000U << FS8X_M_VBOOSTOT_SHIFT) /*!< No event */
#define FS8X_M_VBOOSTOT_EVENT_OCCURRED   (0x0001U << FS8X_M_VBOOSTOT_SHIFT) /*!< Event occurred */

#define FS8X_M_VBOOSTOV_NO_EVENT         (0x0000U << FS8X_M_VBOOSTOV_SHIFT) /*!< No event */
#define FS8X_M_VBOOSTOV_EVENT_OCCURRED   (0x0001U << FS8X_M_VBOOSTOV_SHIFT) /*!< Event occurred */

#define FS8X_M_CLK_FIN_DIV_OK_NOT_OK     (0x0000U << FS8X_M_CLK_FIN_DIV_OK_SHIFT) /*!< Not OK : FINERR_LONG < CLK_FIN_DIV deviation < FINERR_SHORT */
#define FS8X_M_CLK_FIN_DIV_OK_OK         (0x0001U << FS8X_M_CLK_FIN_DIV_OK_SHIFT) /*!< OK : FINERR_SHORT < CLK_FIN_DIV deviation < FINERR_LONG */

#define FS8X_M_LDO2OC_NO_EVENT           (0x0000U << FS8X_M_LDO2OC_SHIFT) /*!< No event */
#define FS8X_M_LDO2OC_EVENT_OCCURRED     (0x0001U << FS8X_M_LDO2OC_SHIFT) /*!< Event occurred */

#define FS8X_M_LDO1OC_NO_EVENT           (0x0000U << FS8X_M_LDO1OC_SHIFT) /*!< No event */
#define FS8X_M_LDO1OC_EVENT_OCCURRED     (0x0001U << FS8X_M_LDO1OC_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK3OC_NO_EVENT          (0x0000U << FS8X_M_BUCK3OC_SHIFT) /*!< No event */
#define FS8X_M_BUCK3OC_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK3OC_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK2OC_NO_EVENT          (0x0000U << FS8X_M_BUCK2OC_SHIFT) /*!< No event */
#define FS8X_M_BUCK2OC_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK2OC_SHIFT) /*!< Event occurred */

#define FS8X_M_BUCK1OC_NO_EVENT          (0x0000U << FS8X_M_BUCK1OC_SHIFT) /*!< No event */
#define FS8X_M_BUCK1OC_EVENT_OCCURRED    (0x0001U << FS8X_M_BUCK1OC_SHIFT) /*!< Event occurred */

#define FS8X_M_VPREOC_NO_EVENT           (0x0000U << FS8X_M_VPREOC_SHIFT) /*!< No event */
#define FS8X_M_VPREOC_EVENT_OCCURRED     (0x0001U << FS8X_M_VPREOC_SHIFT) /*!< Event occured */

#define FS8X_M_VBOOSTUVH_NO_EVENT        (0x0000U << FS8X_M_VBOOSTUVH_SHIFT) /*!< No event */
#define FS8X_M_VBOOSTUVH_EVENT_OCCURRED  (0x0001U << FS8X_M_VBOOSTUVH_SHIFT) /*!< Event occured */

#define FS8X_M_VBOSUVH_NO_EVENT          (0x0000U << FS8X_M_VBOSUVH_SHIFT) /*!< No event */
#define FS8X_M_VBOSUVH_EVENT_OCCURRED    (0x0001U << FS8X_M_VBOSUVH_SHIFT) /*!< Event occured */
//
///******************************************************************************/
///* M_FLAG2 - Type: RW                                                         */
///******************************************************************************/
//
//#define FS8X_M_FLAG2_ADDR                0x09U
//#define FS8X_M_FLAG2_DEFAULT             0x0000U
//
//#define FS8X_M_WK1FLG_MASK               0x0001U /*!< WAKE1 wake up souce flag */
//#define FS8X_M_WK2FLG_MASK               0x0002U /*!< WAKE2 wake up souce flag */
//#define FS8X_M_WK1RT_MASK                0x0004U /*!< Report event: WAKE1 real time state */
//#define FS8X_M_WK2RT_MASK                0x0008U /*!< Report event: WAKE2 real time state */
//#define FS8X_M_VSUPUVH_MASK              0x0010U /*!< VSUP_UVHH event */
//#define FS8X_M_VSUPUVL_MASK              0x0020U /*!< VSUP_UVHL event */
//#define FS8X_M_VPREUVH_MASK              0x0040U /*!< VPRE_UVH event */
//#define FS8X_M_VPREUVL_MASK              0x0080U /*!< VPRE_UVL event */
//#define FS8X_M_LDO2_ST_MASK              0x0100U /*!< LDO2 state */
//#define FS8X_M_LDO1_ST_MASK              0x0200U /*!< LDO1 state */
//#define FS8X_M_BUCK3_ST_MASK             0x0400U /*!< BUCK3 state */
//#define FS8X_M_BUCK2_ST_MASK             0x0800U /*!< BUCK2 state */
//#define FS8X_M_BUCK1_ST_MASK             0x1000U /*!< BUCK1 state */
//#define FS8X_M_BOOST_ST_MASK             0x2000U /*!< BOOST state */
//#define FS8X_M_VSUPUV7_MASK              0x4000U /*!< VSUP_UV7 event */
//#define FS8X_M_VPRE_FB_OV_MASK           0x8000U /*!< VPRE_FB_OV event */
//
//#define FS8X_M_WK1FLG_SHIFT              0x0000U /*!< WAKE1 wake up souce flag */
//#define FS8X_M_WK2FLG_SHIFT              0x0001U /*!< WAKE2 wake up souce flag */
//#define FS8X_M_WK1RT_SHIFT               0x0002U /*!< Report event: WAKE1 real time state */
//#define FS8X_M_WK2RT_SHIFT               0x0003U /*!< Report event: WAKE2 real time state */
//#define FS8X_M_VSUPUVH_SHIFT             0x0004U /*!< VSUP_UVHH event */
//#define FS8X_M_VSUPUVL_SHIFT             0x0005U /*!< VSUP_UVHL event */
//#define FS8X_M_VPREUVH_SHIFT             0x0006U /*!< VPRE_UVH event */
//#define FS8X_M_VPREUVL_SHIFT             0x0007U /*!< VPRE_UVL event */
//#define FS8X_M_LDO2_ST_SHIFT             0x0008U /*!< LDO2 state */
//#define FS8X_M_LDO1_ST_SHIFT             0x0009U /*!< LDO1 state */
//#define FS8X_M_BUCK3_ST_SHIFT            0x000AU /*!< BUCK3 state */
//#define FS8X_M_BUCK2_ST_SHIFT            0x000BU /*!< BUCK2 state */
//#define FS8X_M_BUCK1_ST_SHIFT            0x000CU /*!< BUCK1 state */
//#define FS8X_M_BOOST_ST_SHIFT            0x000DU /*!< BOOST state */
//#define FS8X_M_VSUPUV7_SHIFT             0x000EU /*!< VSUP_UV7 event */
//#define FS8X_M_VPRE_FB_OV_SHIFT          0x000FU /*!< VPRE_FB_OV event */
//
//#define FS8X_M_WK1FLG_NO_EVENT           (0x0000U << FS8X_M_WK1FLG_SHIFT) /*!< No event */
//#define FS8X_M_WK1FLG_EVENT_OCCURRED     (0x0001U << FS8X_M_WK1FLG_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_WK2FLG_NO_EVENT           (0x0000U << FS8X_M_WK2FLG_SHIFT) /*!< No event */
//#define FS8X_M_WK2FLG_EVENT_OCCURRED     (0x0001U << FS8X_M_WK2FLG_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_WK1RT_WAKE1_LOW           (0x0000U << FS8X_M_WK1RT_SHIFT) /*!< WAKE1 is low level */
//#define FS8X_M_WK1RT_WAKE1_HIGH          (0x0001U << FS8X_M_WK1RT_SHIFT) /*!< WAKE1 is high */
//
//#define FS8X_M_WK2RT_WAKE2_LOW           (0x0000U << FS8X_M_WK2RT_SHIFT) /*!< WAKE2 is low level */
//#define FS8X_M_WK2RT_WAKE2_HIGH          (0x0001U << FS8X_M_WK2RT_SHIFT) /*!< WAKE2 is high */
//
//#define FS8X_M_VSUPUVH_NO_EVENT          (0x0000U << FS8X_M_VSUPUVH_SHIFT) /*!< No event */
//#define FS8X_M_VSUPUVH_EVENT_OCCURRED    (0x0001U << FS8X_M_VSUPUVH_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VSUPUVL_NO_EVENT          (0x0000U << FS8X_M_VSUPUVL_SHIFT) /*!< No event */
//#define FS8X_M_VSUPUVL_EVENT_OCCURRED    (0x0001U << FS8X_M_VSUPUVL_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VPREUVH_NO_EVENT          (0x0000U << FS8X_M_VPREUVH_SHIFT) /*!< No event */
//#define FS8X_M_VPREUVH_EVENT_OCCURRED    (0x0001U << FS8X_M_VPREUVH_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_VPREUVL_NO_EVENT          (0x0000U << FS8X_M_VPREUVL_SHIFT) /*!< No event */
//#define FS8X_M_VPREUVL_EVENT_OCCURRED    (0x0001U << FS8X_M_VPREUVL_SHIFT) /*!< Event occurred */
//
//#define FS8X_M_LDO2_ST_REGULATOR_OFF     (0x0000U << FS8X_M_LDO2_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_LDO2_ST_REGULATOR_ON      (0x0001U << FS8X_M_LDO2_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_LDO1_ST_REGULATOR_OFF     (0x0000U << FS8X_M_LDO1_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_LDO1_ST_REGULATOR_ON      (0x0001U << FS8X_M_LDO1_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_BUCK3_ST_REGULATOR_OFF    (0x0000U << FS8X_M_BUCK3_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_BUCK3_ST_REGULATOR_ON     (0x0001U << FS8X_M_BUCK3_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_BUCK2_ST_REGULATOR_OFF    (0x0000U << FS8X_M_BUCK2_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_BUCK2_ST_REGULATOR_ON     (0x0001U << FS8X_M_BUCK2_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_BUCK1_ST_REGULATOR_OFF    (0x0000U << FS8X_M_BUCK1_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_BUCK1_ST_REGULATOR_ON     (0x0001U << FS8X_M_BUCK1_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_BOOST_ST_REGULATOR_OFF    (0x0000U << FS8X_M_BOOST_ST_SHIFT) /*!< regulator OFF */
//#define FS8X_M_BOOST_ST_REGULATOR_ON     (0x0001U << FS8X_M_BOOST_ST_SHIFT) /*!< regulator ON */
//
//#define FS8X_M_VSUPUV7_NO_EVENT          (0x0000U << FS8X_M_VSUPUV7_SHIFT) /*!< No event */
//#define FS8X_M_VSUPUV7_EVENT_OCCURRED    (0x0001U << FS8X_M_VSUPUV7_SHIFT) /*!< Event occured */
//
//#define FS8X_M_VPRE_FB_OV_NO_EVENT       (0x0000U << FS8X_M_VPRE_FB_OV_SHIFT) /*!< No event */
//#define FS8X_M_VPRE_FB_OV_EVENT_OCCURRED (0x0001U << FS8X_M_VPRE_FB_OV_SHIFT) /*!< Event occured */
//
///******************************************************************************/
///* M_VMON_REGX - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_VMON_REGX_ADDR            0x0AU
//#define FS8X_M_VMON_REGX_DEFAULT         0x0000U
//
//#define FS8X_M_VMON1_REG_MASK            0x0007U /*!< Regulator Assignment to VMON1 */
//#define FS8X_M_VMON2_REG_MASK            0x0038U /*!< Regulator Assignment to VMON2 */
//#define FS8X_M_VMON3_REG_MASK            0x01C0U /*!< Regulator Assignment to VMON3 */
//#define FS8X_M_VMON4_REG_MASK            0x0E00U /*!< Regulator Assignment to VMON4 */
//
//#define FS8X_M_VMON1_REG_SHIFT           0x0000U /*!< Regulator Assignment to VMON1 */
//#define FS8X_M_VMON2_REG_SHIFT           0x0003U /*!< Regulator Assignment to VMON2 */
//#define FS8X_M_VMON3_REG_SHIFT           0x0006U /*!< Regulator Assignment to VMON3 */
//#define FS8X_M_VMON4_REG_SHIFT           0x0009U /*!< Regulator Assignment to VMON4 */
//
//#define FS8X_M_VMON1_REG_EXTERNAL_REGULATOR (0x0000U << FS8X_M_VMON1_REG_SHIFT) /*!< External Regulator */
//#define FS8X_M_VMON1_REG_VPRE            (0x0001U << FS8X_M_VMON1_REG_SHIFT) /*!< VPRE */
//#define FS8X_M_VMON1_REG_LDO1            (0x0002U << FS8X_M_VMON1_REG_SHIFT) /*!< LDO1 */
//#define FS8X_M_VMON1_REG_LDO2            (0x0003U << FS8X_M_VMON1_REG_SHIFT) /*!< LDO2 */
//#define FS8X_M_VMON1_REG_BUCK2           (0x0004U << FS8X_M_VMON1_REG_SHIFT) /*!< BUCK2 */
//#define FS8X_M_VMON1_REG_BUCK3           (0x0005U << FS8X_M_VMON1_REG_SHIFT) /*!< BUCK3 */
//
//#define FS8X_M_VMON2_REG_EXTERNAL_REGULATOR (0x0000U << FS8X_M_VMON2_REG_SHIFT) /*!< External Regulator */
//#define FS8X_M_VMON2_REG_VPRE            (0x0001U << FS8X_M_VMON2_REG_SHIFT) /*!< VPRE */
//#define FS8X_M_VMON2_REG_LDO1            (0x0002U << FS8X_M_VMON2_REG_SHIFT) /*!< LDO1 */
//#define FS8X_M_VMON2_REG_LDO2            (0x0003U << FS8X_M_VMON2_REG_SHIFT) /*!< LDO2 */
//#define FS8X_M_VMON2_REG_BUCK2           (0x0004U << FS8X_M_VMON2_REG_SHIFT) /*!< BUCK2 */
//#define FS8X_M_VMON2_REG_BUCK3           (0x0005U << FS8X_M_VMON2_REG_SHIFT) /*!< BUCK3 */
//
//#define FS8X_M_VMON3_REG_EXTERNAL_REGULATOR (0x0000U << FS8X_M_VMON3_REG_SHIFT) /*!< External Regulator */
//#define FS8X_M_VMON3_REG_VPRE            (0x0001U << FS8X_M_VMON3_REG_SHIFT) /*!< VPRE */
//#define FS8X_M_VMON3_REG_LDO1            (0x0002U << FS8X_M_VMON3_REG_SHIFT) /*!< LDO1 */
//#define FS8X_M_VMON3_REG_LDO2            (0x0003U << FS8X_M_VMON3_REG_SHIFT) /*!< LDO2 */
//#define FS8X_M_VMON3_REG_BUCK2           (0x0004U << FS8X_M_VMON3_REG_SHIFT) /*!< BUCK2 */
//#define FS8X_M_VMON3_REG_BUCK3           (0x0005U << FS8X_M_VMON3_REG_SHIFT) /*!< BUCK3 */
//
//#define FS8X_M_VMON4_REG_EXTERNAL_REGULATOR (0x0000U << FS8X_M_VMON4_REG_SHIFT) /*!< External Regulator */
//#define FS8X_M_VMON4_REG_VPRE            (0x0001U << FS8X_M_VMON4_REG_SHIFT) /*!< VPRE */
//#define FS8X_M_VMON4_REG_LDO1            (0x0002U << FS8X_M_VMON4_REG_SHIFT) /*!< LDO1 */
//#define FS8X_M_VMON4_REG_LDO2            (0x0003U << FS8X_M_VMON4_REG_SHIFT) /*!< LDO2 */
//#define FS8X_M_VMON4_REG_BUCK2           (0x0004U << FS8X_M_VMON4_REG_SHIFT) /*!< BUCK2 */
//#define FS8X_M_VMON4_REG_BUCK3           (0x0005U << FS8X_M_VMON4_REG_SHIFT) /*!< BUCK3 */
//
///******************************************************************************/
///* M_LVB1_SVS - Type: R                                                       */
///******************************************************************************/
//
//#define FS8X_M_LVB1_SVS_ADDR             0x0BU
//#define FS8X_M_LVB1_SVS_DEFAULT          0x0000U
//
//#define FS8X_M_LVB1_SVS_MASK             0x001FU /*!< Static Voltage Scaling negative offset */
//
//#define FS8X_M_LVB1_SVS_SHIFT            0x0000U /*!< Static Voltage Scaling negative offset */
//
//#define FS8X_M_LVB1_SVS_0MV              (0x0000U << FS8X_M_LVB1_SVS_SHIFT) /*!< 0mV */
//#define FS8X_M_LVB1_SVS_M6_25MV          (0x0001U << FS8X_M_LVB1_SVS_SHIFT) /*!< -6.25mV */
//#define FS8X_M_LVB1_SVS_M12_50MV         (0x0002U << FS8X_M_LVB1_SVS_SHIFT) /*!< -12.50mV */
//#define FS8X_M_LVB1_SVS_M18_75MV         (0x0003U << FS8X_M_LVB1_SVS_SHIFT) /*!< -18.75mV */
//#define FS8X_M_LVB1_SVS_M25MV            (0x0004U << FS8X_M_LVB1_SVS_SHIFT) /*!< -25mV */
//#define FS8X_M_LVB1_SVS_M31_25MV         (0x0005U << FS8X_M_LVB1_SVS_SHIFT) /*!< -31.25mV */
//#define FS8X_M_LVB1_SVS_M37_5MV          (0x0006U << FS8X_M_LVB1_SVS_SHIFT) /*!< -37.5mV */
//#define FS8X_M_LVB1_SVS_M43_75MV         (0x0007U << FS8X_M_LVB1_SVS_SHIFT) /*!< -43.75mV */
//#define FS8X_M_LVB1_SVS_M50MV            (0x0008U << FS8X_M_LVB1_SVS_SHIFT) /*!< -50mV */
//#define FS8X_M_LVB1_SVS_M56_25MV         (0x0009U << FS8X_M_LVB1_SVS_SHIFT) /*!< -56.25mV */
//#define FS8X_M_LVB1_SVS_M62_5MV          (0x000AU << FS8X_M_LVB1_SVS_SHIFT) /*!< -62.5mV */
//#define FS8X_M_LVB1_SVS_M68_75MV         (0x000BU << FS8X_M_LVB1_SVS_SHIFT) /*!< -68.75mV */
//#define FS8X_M_LVB1_SVS_M75MV            (0x000CU << FS8X_M_LVB1_SVS_SHIFT) /*!< -75mV */
//#define FS8X_M_LVB1_SVS_M81_25MV         (0x000DU << FS8X_M_LVB1_SVS_SHIFT) /*!< -81.25mV */
//#define FS8X_M_LVB1_SVS_M87_5MV          (0x000EU << FS8X_M_LVB1_SVS_SHIFT) /*!< -87.5mV */
//#define FS8X_M_LVB1_SVS_M93_75MV         (0x000FU << FS8X_M_LVB1_SVS_SHIFT) /*!< -93.75mV */
//#define FS8X_M_LVB1_SVS_M100MV           (0x0010U << FS8X_M_LVB1_SVS_SHIFT) /*!< -100mV */
//
///******************************************************************************/
///* M_MEMORY0 - Type: RW                                                       */
///******************************************************************************/
//
//#define FS8X_M_MEMORY0_ADDR              0x23U
//#define FS8X_M_MEMORY0_DEFAULT           0x0000U
//
//#define FS8X_M_M_MEMORY0_MASK            0xFFFFU /*!< Free field for data storage */
//
//#define FS8X_M_M_MEMORY0_SHIFT           0x0000U /*!< Free field for data storage */
//
///******************************************************************************/
///* M_MEMORY1 - Type: RW                                                       */
///******************************************************************************/
//
//#define FS8X_M_MEMORY1_ADDR              0x24U
//#define FS8X_M_MEMORY1_DEFAULT           0x0000U
//
//#define FS8X_M_M_MEMORY1_MASK            0xFFFFU /*!< Free field for data storage */
//
//#define FS8X_M_M_MEMORY1_SHIFT           0x0000U /*!< Free field for data storage */
//
///******************************************************************************/
///* M_DEVICEID - Type: R                                                       */
///******************************************************************************/
//
//#define FS8X_M_DEVICEID_ADDR             0x25U
//#define FS8X_M_DEVICEID_DEFAULT          0x0000U
//
//#define FS8X_M_M_DEVICE_MASK             0x00FFU /*!< Device ID */
//
//#define FS8X_M_M_DEVICE_SHIFT            0x0000U /*!< Device ID */
//
///******************************************************************************/
///* M_MIRRORCMD - Type: RW                                                     */
///******************************************************************************/

#define FS8X_M_MIRRORCMD_ADDR            0x0CU
#define FS8X_M_MIRRORCMD_DEFAULT         0x0000U

#define FS8X_M_ADDR_MASK                 0x00FFU /*!< Mirror register address pointer/index */
#define FS8X_M_WRITE_MASK                0x0100U /*!< Mirror register write command */

#define FS8X_M_ADDR_SHIFT                0x0000U /*!< Mirror register address pointer/index */
#define FS8X_M_WRITE_SHIFT               0x0008U /*!< Mirror register write command */

#define FS8X_M_WRITE_NO_OPERATION        (0x0000U << FS8X_M_WRITE_SHIFT) /*!< No operation */
#define FS8X_M_WRITE_WRITE_DATA          (0x0001U << FS8X_M_WRITE_SHIFT) /*!< Write data in DATAWR field into mirror registers table at address ADDR */

///******************************************************************************/
///* M_MIRRORDATA - Type: RW                                                    */
///******************************************************************************/

#define FS8X_M_MIRRORDATA_ADDR           0x0DU
#define FS8X_M_MIRRORDATA_DEFAULT        0x0000U

#define FS8X_M_DATAWR_MASK               0x00FFU /*!< Mirror Data to be programmed at address specified by ADDR in MIRRORCMD register */
#define FS8X_M_DATAR_MASK                0xFF00U /*!< Mirror register read data content */

#define FS8X_M_DATAWR_SHIFT              0x0000U /*!< Mirror Data to be programmed at address specified by ADDR in MIRRORCMD register */
#define FS8X_M_DATAR_SHIFT               0x0008U /*!< Mirror register read data content */

///******************************************************************************/
///* M_OTPADDR - Type: RW                                                       */
///******************************************************************************/
//
//#define FS8X_M_OTPADDR_ADDR              0x0EU
//#define FS8X_M_OTPADDR_DEFAULT           0x0000U
//
//#define FS8X_M_START_MASK                0x00FFU /*!< Start address for some OTPC commands */
//#define FS8X_M_STOP_MASK                 0xFF00U /*!< OTP operation stop address */
//
//#define FS8X_M_START_SHIFT               0x0000U /*!< Start address for some OTPC commands */
//#define FS8X_M_STOP_SHIFT                0x0008U /*!< OTP operation stop address */
//
///******************************************************************************/
///* M_OTPDATA - Type: RW                                                       */
///******************************************************************************/
//
//#define FS8X_M_OTPDATA_ADDR              0x0FU
//#define FS8X_M_OTPDATA_DEFAULT           0x0000U
//
//#define FS8X_M_DATAIN_MASK               0x00FFU /*!< Data to be written on certain OTPC commands */
//#define FS8X_M_DATAOUT_MASK              0xFF00U /*!< Data to be read on certain OTPC commands */
//
//#define FS8X_M_DATAIN_SHIFT              0x0000U /*!< Data to be written on certain OTPC commands */
//#define FS8X_M_DATAOUT_SHIFT             0x0008U /*!< Data to be read on certain OTPC commands */
//
///******************************************************************************/
///* M_OTPCMD - Type: RW                                                        */
///******************************************************************************/
//
//#define FS8X_M_OTPCMD_ADDR               0x10U
//#define FS8X_M_OTPCMD_DEFAULT            0x0000U
//
//#define FS8X_M_CMD_MASK                  0x003FU /*!< OTP operation commands - see below */
//#define FS8X_M_GO_MASK                   0x0100U /*!< N/A */
//
//#define FS8X_M_CMD_SHIFT                 0x0000U /*!< OTP operation commands - see below */
//#define FS8X_M_GO_SHIFT                  0x0008U /*!< N/A */
//
//#define FS8X_M_CMD_C_IDLE                (0x0000U << FS8X_M_CMD_SHIFT) /*!< C_IDLE */
//#define FS8X_M_CMD_C_PRG                 (0x0016U << FS8X_M_CMD_SHIFT) /*!< C_PRG */
//#define FS8X_M_CMD_C_PRG_ONE             (0x0007U << FS8X_M_CMD_SHIFT) /*!< C_PRG_ONE */
//#define FS8X_M_CMD_C_RD                  (0x0012U << FS8X_M_CMD_SHIFT) /*!< C_RD */
//#define FS8X_M_CMD_C_RD_ALL              (0x0003U << FS8X_M_CMD_SHIFT) /*!< C_RD_ALL */
//#define FS8X_M_CMD_C_RD_ONE              (0x000BU << FS8X_M_CMD_SHIFT) /*!< C_RD_ONE */
//#define FS8X_M_CMD_C_CHK                 (0x001BU << FS8X_M_CMD_SHIFT) /*!< C_CHK */
//#define FS8X_M_CMD_C_CHK_XX              (0x001AU << FS8X_M_CMD_SHIFT) /*!< C_CHK_XX */
//
//#define FS8X_M_GO_NO_ACTION              (0x0000U << FS8X_M_GO_SHIFT) /*!< No action */
//#define FS8X_M_GO_START_COMMAND          (0x0001U << FS8X_M_GO_SHIFT) /*!< START Command specified by CMD. Self clears after BUSY flag in STATUS register is set. */
//
///******************************************************************************/
///* M_OTPSTATUS0 - Type: R                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPSTATUS0_ADDR           0x11U
//#define FS8X_M_OTPSTATUS0_DEFAULT        0x0000U
//
//#define FS8X_M_BUSY_MASK                 0x0001U /*!< N/A */
//#define FS8X_M_ERROR_MASK                0x0002U /*!< N/A */
//#define FS8X_M_ONE_ERR_MASK              0x0004U /*!< N/A */
//#define FS8X_M_TWO_ERR_MASK              0x0008U /*!< N/A */
//#define FS8X_M_MAX_PGM_EXCEED_MASK       0x0010U /*!< N/A */
//#define FS8X_M_VRR_CHECK_TRIES_MASK      0x07E0U /*!< Count numbers of cold start VRR reads or programming tries */
//#define FS8X_M_PGM_FAIL_WP_MASK          0x0800U /*!< tried to prg a WP sector */
//#define FS8X_M_BOOT_ERROR_MASK           0x1000U /*!< no crc error and no double error for bootable sector - updated after CRC check cmd */
//
//#define FS8X_M_BUSY_SHIFT                0x0000U /*!< N/A */
//#define FS8X_M_ERROR_SHIFT               0x0001U /*!< N/A */
//#define FS8X_M_ONE_ERR_SHIFT             0x0002U /*!< N/A */
//#define FS8X_M_TWO_ERR_SHIFT             0x0003U /*!< N/A */
//#define FS8X_M_MAX_PGM_EXCEED_SHIFT      0x0004U /*!< N/A */
//#define FS8X_M_VRR_CHECK_TRIES_SHIFT     0x0005U /*!< Count numbers of cold start VRR reads or programming tries */
//#define FS8X_M_PGM_FAIL_WP_SHIFT         0x000BU /*!< tried to prg a WP sector */
//#define FS8X_M_BOOT_ERROR_SHIFT          0x000CU /*!< no crc error and no double error for bootable sector - updated after CRC check cmd */
//
//#define FS8X_M_BUSY_IDLE                 (0x0000U << FS8X_M_BUSY_SHIFT) /*!< Fuse Interface Idle */
//#define FS8X_M_BUSY_PROGRAMMING          (0x0001U << FS8X_M_BUSY_SHIFT) /*!< Programming in progress */
//
//#define FS8X_M_ERROR_NA                  (0x0000U << FS8X_M_ERROR_SHIFT) /*!< N/A */
//#define FS8X_M_ERROR_ERROR_FLAG_SET      (0x0001U << FS8X_M_ERROR_SHIFT) /*!< The ERROR flag is set during VERIFY commands, if the verification fails and if any invalid command is issued. Also, ERROR is set if trying to program a data at an address which was previously programmed (and the bits to be programmed later were not masked). */
//
//#define FS8X_M_ONE_ERR_NA                (0x0000U << FS8X_M_ONE_ERR_SHIFT) /*!< N/A */
//#define FS8X_M_ONE_ERR_ERROR_DETECTED    (0x0001U << FS8X_M_ONE_ERR_SHIFT) /*!< If ECC is enabled, one ECC error was detected in one or multiple rows */
//
//#define FS8X_M_TWO_ERR_NA                (0x0000U << FS8X_M_TWO_ERR_SHIFT) /*!< N/A */
//#define FS8X_M_TWO_ERR_TWO_ERR_DETECTED  (0x0001U << FS8X_M_TWO_ERR_SHIFT) /*!< If ECC is enabled, two ECC errors were detected in one or multiple rows */
//
//#define FS8X_M_MAX_PGM_EXCEED_NA         (0x0000U << FS8X_M_MAX_PGM_EXCEED_SHIFT) /*!< N/A */
//#define FS8X_M_MAX_PGM_EXCEED_EXCEEDED   (0x0001U << FS8X_M_MAX_PGM_EXCEED_SHIFT) /*!< exceeded maximum number of programming trials (specified by MAX_PGM_TRIES register setting) */
//
//#define FS8X_M_PGM_FAIL_WP_NO_FAIL       (0x0000U << FS8X_M_PGM_FAIL_WP_SHIFT) /*!< no fail */
//#define FS8X_M_PGM_FAIL_WP_FAIL_DETECTED (0x0001U << FS8X_M_PGM_FAIL_WP_SHIFT) /*!< fail detected */
//
//#define FS8X_M_BOOT_ERROR_NO_ERROR_DETECTED (0x0000U << FS8X_M_BOOT_ERROR_SHIFT) /*!< no error detected */
//#define FS8X_M_BOOT_ERROR_ERROR_DETECTED (0x0001U << FS8X_M_BOOT_ERROR_SHIFT) /*!< error detected */
//
///******************************************************************************/
///* M_OTPSTATUS1 - Type: R                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPSTATUS1_ADDR           0x12U
//#define FS8X_M_OTPSTATUS1_DEFAULT        0x0000U
//
//#define FS8X_M_CRCSTS0_MASK              0x0001U /*!< Sector CRC status */
//#define FS8X_M_CRCSTS1_MASK              0x0002U /*!< Sector CRC status */
//#define FS8X_M_SECTBE0_MASK              0x0004U /*!< Sector Boot Enable status */
//#define FS8X_M_SECTBE1_MASK              0x0008U /*!< Sector Boot Enable status */
//#define FS8X_M_SECTWP0_MASK              0x0010U /*!< Sector Write Protected status */
//#define FS8X_M_SECTWP1_MASK              0x0020U /*!< Sector Write Protected status */
//#define FS8X_M_MTP_INDEX_S0_MASK         0x01C0U /*!< Multi Time Progr Index Status for Sector 0 */
//#define FS8X_M_MTP_INDEX_S1_MASK         0x0E00U /*!< Multi Time Progr Index Status for Sector 1 */
//
//#define FS8X_M_CRCSTS0_SHIFT             0x0000U /*!< Sector CRC status */
//#define FS8X_M_CRCSTS1_SHIFT             0x0001U /*!< Sector CRC status */
//#define FS8X_M_SECTBE0_SHIFT             0x0002U /*!< Sector Boot Enable status */
//#define FS8X_M_SECTBE1_SHIFT             0x0003U /*!< Sector Boot Enable status */
//#define FS8X_M_SECTWP0_SHIFT             0x0004U /*!< Sector Write Protected status */
//#define FS8X_M_SECTWP1_SHIFT             0x0005U /*!< Sector Write Protected status */
//#define FS8X_M_MTP_INDEX_S0_SHIFT        0x0006U /*!< Multi Time Progr Index Status for Sector 0 */
//#define FS8X_M_MTP_INDEX_S1_SHIFT        0x0009U /*!< Multi Time Progr Index Status for Sector 1 */
//
//#define FS8X_M_CRCSTS0_CRC_ERROR         (0x0000U << FS8X_M_CRCSTS0_SHIFT) /*!< CRC error at sector 0 or CRC check not run on that sector */
//#define FS8X_M_CRCSTS0_CRC_OK            (0x0001U << FS8X_M_CRCSTS0_SHIFT) /*!< CRC check OK at sector 0 */
//
//#define FS8X_M_CRCSTS1_CRC_ERROR         (0x0000U << FS8X_M_CRCSTS1_SHIFT) /*!< CRC error at sector 1 or CRC check not run on that sector */
//#define FS8X_M_CRCSTS1_CRC_OK            (0x0001U << FS8X_M_CRCSTS1_SHIFT) /*!< CRC check OK at sector 1 */
//
//#define FS8X_M_SECTBE0_NOT_BOOTABLE      (0x0000U << FS8X_M_SECTBE0_SHIFT) /*!< Sector 0 is not bootable */
//#define FS8X_M_SECTBE0_BOOTABLE          (0x0001U << FS8X_M_SECTBE0_SHIFT) /*!< Sector 0 is bootable */
//
//#define FS8X_M_SECTBE1_NOT_BOOTABLE      (0x0000U << FS8X_M_SECTBE1_SHIFT) /*!< Sector 1 is not bootable */
//#define FS8X_M_SECTBE1_BOOTABLE          (0x0001U << FS8X_M_SECTBE1_SHIFT) /*!< Sector 1 is bootable */
//
//#define FS8X_M_SECTWP0_NOT_WRITE_PROTECTED (0x0000U << FS8X_M_SECTWP0_SHIFT) /*!< Sector 0 is not write protected */
//#define FS8X_M_SECTWP0_WRITE_PROTECTED   (0x0001U << FS8X_M_SECTWP0_SHIFT) /*!< Sector 0 is write protected */
//
//#define FS8X_M_SECTWP1_NOT_WRITE_PROTECTED (0x0000U << FS8X_M_SECTWP1_SHIFT) /*!< Sector 1 is not write protected */
//#define FS8X_M_SECTWP1_WRITE_PROTECTED   (0x0001U << FS8X_M_SECTWP1_SHIFT) /*!< Sector 1 is write protected */
//
///******************************************************************************/
///* M_OTPPARAM0 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM0_ADDR            0x13U
//#define FS8X_M_OTPPARAM0_DEFAULT         0x0268U
//
//#define FS8X_M_MAX_PGM_TRIES_MASK        0x003FU /*!< MAX_PGM_TRIES */
//#define FS8X_M_SVDR_IN_MASK              0x0040U /*!< SVDR_IN */
//#define FS8X_M_MRR_IN_MASK               0x0780U /*!< MRR_IN */
//#define FS8X_M_LOVCC_IN_MASK             0x0800U /*!< LOVCC_IN */
//#define FS8X_M_MR_SCREF_RD_1_MASK        0xF000U /*!< MR_SCREF_RD_1 */
//
//#define FS8X_M_MAX_PGM_TRIES_SHIFT       0x0000U /*!< MAX_PGM_TRIES */
//#define FS8X_M_SVDR_IN_SHIFT             0x0006U /*!< SVDR_IN */
//#define FS8X_M_MRR_IN_SHIFT              0x0007U /*!< MRR_IN */
//#define FS8X_M_LOVCC_IN_SHIFT            0x000BU /*!< LOVCC_IN */
//#define FS8X_M_MR_SCREF_RD_1_SHIFT       0x000CU /*!< MR_SCREF_RD_1 */
//
//#define FS8X_M_SVDR_IN_CUSTOM            (0x0000U << FS8X_M_SVDR_IN_SHIFT) /*!< custom */
//#define FS8X_M_SVDR_IN_DEFAULT           (0x0001U << FS8X_M_SVDR_IN_SHIFT) /*!< default */
//
//#define FS8X_M_LOVCC_IN_DEFAULT          (0x0000U << FS8X_M_LOVCC_IN_SHIFT) /*!< default */
//#define FS8X_M_LOVCC_IN_CUSTOM           (0x0001U << FS8X_M_LOVCC_IN_SHIFT) /*!< custom */
//
///******************************************************************************/
///* M_OTPPARAM1 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM1_ADDR            0x14U
//#define FS8X_M_OTPPARAM1_DEFAULT         0x0000U
//
//#define FS8X_M_MREF_IREF_RD_1_MASK       0x003FU /*!< MREF_IREF_RD_1 */
//#define FS8X_M_MR_SCREF_RD_2_MASK        0x03C0U /*!< MR_SCREF_RD_2 */
//#define FS8X_M_MREF_IREF_RD_2_MASK       0xFC00U /*!< MREF_IREF_RD_2 */
//
//#define FS8X_M_MREF_IREF_RD_1_SHIFT      0x0000U /*!< MREF_IREF_RD_1 */
//#define FS8X_M_MR_SCREF_RD_2_SHIFT       0x0006U /*!< MR_SCREF_RD_2 */
//#define FS8X_M_MREF_IREF_RD_2_SHIFT      0x000AU /*!< MREF_IREF_RD_2 */
//
///******************************************************************************/
///* M_OTPPARAM2 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM2_ADDR            0x15U
//#define FS8X_M_OTPPARAM2_DEFAULT         0x0000U
//
//#define FS8X_M_MREF_TEST_MASK            0xFFFFU /*!< MREF_TEST */
//
//#define FS8X_M_MREF_TEST_SHIFT           0x0000U /*!< MREF_TEST */
//
///******************************************************************************/
///* M_OTPPARAM3 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM3_ADDR            0x16U
//#define FS8X_M_OTPPARAM3_DEFAULT         0x0000U
//
//#define FS8X_M_MR_TEST_MASK              0xFFFFU /*!< MR_TEST */
//
//#define FS8X_M_MR_TEST_SHIFT             0x0000U /*!< MR_TEST */
//
///******************************************************************************/
///* M_OTPPARAM4 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM4_ADDR            0x17U
//#define FS8X_M_OTPPARAM4_DEFAULT         0x0000U
//
//#define FS8X_M_TEST_MODE_MASK            0x0001U /*!< TEST_MODE */
//#define FS8X_M_START_LSB_MASK            0x0006U /*!< START_LSB */
//#define FS8X_M_STOP_LSB_MASK             0x0018U /*!< STOP_LSB */
//#define FS8X_M_DISABLE_WP_MASK           0x0020U /*!< DISABLE_WP */
//#define FS8X_M_TM10_MASK                 0x0040U /*!< TM10 */
//#define FS8X_M_SE_MASK                   0x0380U /*!< SE */
//#define FS8X_M_PGM_PULSE_DUR_MASK        0x3C00U /*!< PGM_PULSE_DUR */
//#define FS8X_M_PGM_SKIP_READS_MASK       0x4000U /*!< PGM_SKIP_READS */
//#define FS8X_M_TRIES_SOAK_OPT_MASK       0x8000U /*!< TRIES_SOAK_OPT */
//
//#define FS8X_M_TEST_MODE_SHIFT           0x0000U /*!< TEST_MODE */
//#define FS8X_M_START_LSB_SHIFT           0x0001U /*!< START_LSB */
//#define FS8X_M_STOP_LSB_SHIFT            0x0003U /*!< STOP_LSB */
//#define FS8X_M_DISABLE_WP_SHIFT          0x0005U /*!< DISABLE_WP */
//#define FS8X_M_TM10_SHIFT                0x0006U /*!< TM10 */
//#define FS8X_M_SE_SHIFT                  0x0007U /*!< SE */
//#define FS8X_M_PGM_PULSE_DUR_SHIFT       0x000AU /*!< PGM_PULSE_DUR */
//#define FS8X_M_PGM_SKIP_READS_SHIFT      0x000EU /*!< PGM_SKIP_READS */
//#define FS8X_M_TRIES_SOAK_OPT_SHIFT      0x000FU /*!< TRIES_SOAK_OPT */
//
//#define FS8X_M_TEST_MODE_DEFAULT         (0x0000U << FS8X_M_TEST_MODE_SHIFT) /*!< default */
//#define FS8X_M_TEST_MODE_CUSTOM          (0x0001U << FS8X_M_TEST_MODE_SHIFT) /*!< custom */
//
//#define FS8X_M_DISABLE_WP_DEFAULT        (0x0000U << FS8X_M_DISABLE_WP_SHIFT) /*!< default */
//#define FS8X_M_DISABLE_WP_CUSTOM         (0x0001U << FS8X_M_DISABLE_WP_SHIFT) /*!< custom */
//
//#define FS8X_M_TM10_DEFAULT              (0x0000U << FS8X_M_TM10_SHIFT) /*!< default */
//#define FS8X_M_TM10_CUSTOM               (0x0001U << FS8X_M_TM10_SHIFT) /*!< custom */
//
//#define FS8X_M_PGM_SKIP_READS_DEFAULT    (0x0000U << FS8X_M_PGM_SKIP_READS_SHIFT) /*!< default */
//#define FS8X_M_PGM_SKIP_READS_CUSTOM     (0x0001U << FS8X_M_PGM_SKIP_READS_SHIFT) /*!< custom */
//
//#define FS8X_M_TRIES_SOAK_OPT_DEFAULT    (0x0000U << FS8X_M_TRIES_SOAK_OPT_SHIFT) /*!< default */
//#define FS8X_M_TRIES_SOAK_OPT_CUSTOM     (0x0001U << FS8X_M_TRIES_SOAK_OPT_SHIFT) /*!< custom */
//
///******************************************************************************/
///* M_OTPPARAM5 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM5_ADDR            0x18U
//#define FS8X_M_OTPPARAM5_DEFAULT         0x2400U
//
//#define FS8X_M_SOAK_PULSE_DUR_MASK       0x000FU /*!< SOAK_PULSE_DUR */
//#define FS8X_M_READ_PULSE_DUR_MASK       0x00F0U /*!< READ_PULSE_DUR */
//#define FS8X_M_ALWAYS_ON_MASK            0x0100U /*!< ALWAYS_ON */
//#define FS8X_M_TEST_ROW_ACCESS_MASK      0x0200U /*!< TEST_ROW_ACCESS */
//#define FS8X_M_ECC_ENABLE_MASK           0x0400U /*!< ECC_ENABLE */
//#define FS8X_M_PGM_ONE_BIT_MASK          0x0800U /*!< PGM_ONE_BIT */
//#define FS8X_M_SOAK_ONE_BIT_MASK         0x1000U /*!< SOAK_ONE_BIT */
//#define FS8X_M_ROM_READ_PULSE_WIDTH_MASK 0x2000U /*!< ROM_READ_PULSE_WIDTH */
//
//#define FS8X_M_SOAK_PULSE_DUR_SHIFT      0x0000U /*!< SOAK_PULSE_DUR */
//#define FS8X_M_READ_PULSE_DUR_SHIFT      0x0004U /*!< READ_PULSE_DUR */
//#define FS8X_M_ALWAYS_ON_SHIFT           0x0008U /*!< ALWAYS_ON */
//#define FS8X_M_TEST_ROW_ACCESS_SHIFT     0x0009U /*!< TEST_ROW_ACCESS */
//#define FS8X_M_ECC_ENABLE_SHIFT          0x000AU /*!< ECC_ENABLE */
//#define FS8X_M_PGM_ONE_BIT_SHIFT         0x000BU /*!< PGM_ONE_BIT */
//#define FS8X_M_SOAK_ONE_BIT_SHIFT        0x000CU /*!< SOAK_ONE_BIT */
//#define FS8X_M_ROM_READ_PULSE_WIDTH_SHIFT 0x000DU /*!< ROM_READ_PULSE_WIDTH */
//
//#define FS8X_M_ALWAYS_ON_DEFAULT         (0x0000U << FS8X_M_ALWAYS_ON_SHIFT) /*!< default */
//#define FS8X_M_ALWAYS_ON_CUSTOM          (0x0001U << FS8X_M_ALWAYS_ON_SHIFT) /*!< custom */
//
//#define FS8X_M_TEST_ROW_ACCESS_DEFAULT   (0x0000U << FS8X_M_TEST_ROW_ACCESS_SHIFT) /*!< default */
//#define FS8X_M_TEST_ROW_ACCESS_CUSTOM    (0x0001U << FS8X_M_TEST_ROW_ACCESS_SHIFT) /*!< custom */
//
//#define FS8X_M_ECC_ENABLE_CUSTOM         (0x0000U << FS8X_M_ECC_ENABLE_SHIFT) /*!< custom */
//#define FS8X_M_ECC_ENABLE_DEFAULT        (0x0001U << FS8X_M_ECC_ENABLE_SHIFT) /*!< default */
//
//#define FS8X_M_PGM_ONE_BIT_DEFAULT       (0x0000U << FS8X_M_PGM_ONE_BIT_SHIFT) /*!< default */
//#define FS8X_M_PGM_ONE_BIT_CUSTOM        (0x0001U << FS8X_M_PGM_ONE_BIT_SHIFT) /*!< custom */
//
//#define FS8X_M_SOAK_ONE_BIT_DEFAULT      (0x0000U << FS8X_M_SOAK_ONE_BIT_SHIFT) /*!< default */
//#define FS8X_M_SOAK_ONE_BIT_CUSTOM       (0x0001U << FS8X_M_SOAK_ONE_BIT_SHIFT) /*!< custom */
//
//#define FS8X_M_ROM_READ_PULSE_WIDTH_CUSTOM (0x0000U << FS8X_M_ROM_READ_PULSE_WIDTH_SHIFT) /*!< custom */
//#define FS8X_M_ROM_READ_PULSE_WIDTH_DEFAULT (0x0001U << FS8X_M_ROM_READ_PULSE_WIDTH_SHIFT) /*!< default */
//
///******************************************************************************/
///* M_OTPPARAM6 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_OTPPARAM6_ADDR            0x19U
//#define FS8X_M_OTPPARAM6_DEFAULT         0x0000U
//
//#define FS8X_M_PGM_IDLE_MASK             0x003FU /*!< PGM_IDLE */
//
//#define FS8X_M_PGM_IDLE_SHIFT            0x0000U /*!< PGM_IDLE */
//
///******************************************************************************/
///* M_TM_ENTRY - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_M_TM_ENTRY_ADDR             0x1AU
//#define FS8X_M_TM_ENTRY_DEFAULT          0x0000U
//
//#define FS8X_M_TM_TM_ENTRY_KEY_MASK      0xFFFFU /*!< TEST MODE ENTRY KEYS SEQUENCE */
//
//#define FS8X_M_TM_TM_ENTRY_KEY_SHIFT     0x0000U /*!< TEST MODE ENTRY KEYS SEQUENCE */
//
///******************************************************************************/
///* M_TM_DMUX1 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_M_TM_DMUX1_ADDR             0x1BU
//#define FS8X_M_TM_DMUX1_DEFAULT          0x0000U
//
//#define FS8X_M_TM_DMUX_FCCU1_SEL_MASK    0x001FU /*!< Select DMUX FCCU1 input */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_MASK    0x03E0U /*!< Select DMUX FCCU2 input */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_MASK   0x7C00U /*!< Select DMUX ERRMON input */
//
//#define FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT   0x0000U /*!< Select DMUX FCCU1 input */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT   0x0005U /*!< Select DMUX FCCU2 input */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT  0x000AU /*!< Select DMUX ERRMON input */
//
//#define FS8X_M_TM_DMUX_FCCU1_SEL_0       (0x0000U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< 0 */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_1       (0x0001U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_2       (0x0002U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< vpre_high_uv_n_d_xor ^ hvbuck_bootl_d_xor ^ vboost_low_uv_n_d_xor ^ vsup_7_uv_n_d_xor ^ fs_vmonx_ov_d[3]_xor ^ lvbuck2_tsd_d_xor */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_3       (0x0003U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< spare[5] */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_4       (0x0004U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< rst (from internal ctrl) */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_5       (0x0005U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< bos_rcp_flag_vsup */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_6       (0x0006U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< lvbuck1_tsd */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_7       (0x0007U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< scl2logic */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_8       (0x0008U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< OV<0> */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_9       (0x0009U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< ipg_fs_deepfs */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_10      (0x000AU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< vsup_nuv_high ^ vsup_nuv_low ^ vsup_nuv_7 */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_11      (0x000BU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< wd_status */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_12      (0x000CU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< vbos_por */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_13      (0x000DU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< dmux_hvbuck<0> */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_14      (0x000EU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< ipg_hvbuck_bootl */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_15      (0x000FU << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< sw1_dmux_out_1p5 (internal out of sw ctrl) */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_16      (0x0010U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< FIN */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_17      (0x0011U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< wake1_ok */
//#define FS8X_M_TM_DMUX_FCCU1_SEL_18      (0x0012U << FS8X_M_TM_DMUX_FCCU1_SEL_SHIFT) /*!< bg1_bg2_ok */
//
//#define FS8X_M_TM_DMUX_FCCU2_SEL_0       (0x0000U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< 0 */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_1       (0x0001U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_2       (0x0002U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< vpre_fb2_ov_d_xor ^ fsb_d_xor ^ vboost_high_uv_n_d_xor ^ psync_sense_d_xor ^ fs_vmonx_ov_d[2]_xor ^ lvbuck1_tsd_d_xor ^ fs_valid_wd_d_xor */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_3       (0x0003U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< spare[4] */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_4       (0x0004U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< ilim(from internal ctrl) */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_5       (0x0005U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< bos_rcp_flag_vsup */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_6       (0x0006U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< lvbuck2_tsd */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_7       (0x0007U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< sda2logic */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_8       (0x0008U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< OV<1> */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_9       (0x0009U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< ipg_fs_ready */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_10      (0x000AU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< vbos_nuv_high ^ vbos_nuv_low */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_11      (0x000BU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< ring_osc_main */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_12      (0x000CU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< vpre3_por */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_13      (0x000DU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< dmux_hvbuck<1> */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_14      (0x000EU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< ipg_hvbuck_dvrls */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_15      (0x000FU << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< sw2_dmux_out_1p5 (internal out of sw ctrl) */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_16      (0x0010U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< PSYNC */
//#define FS8X_M_TM_DMUX_FCCU2_SEL_17      (0x0011U << FS8X_M_TM_DMUX_FCCU2_SEL_SHIFT) /*!< wake2_ok */
//
//#define FS8X_M_TM_DMUX_ERRMON_SEL_0      (0x0000U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< 0 */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_1      (0x0001U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_2      (0x0002U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< vbos_low_uv_n_d_xor ^ fs_ready_d_xor ^ wake2_d_xor ^ reg2_tsd_d_xor ^ fs_vmonx_ov_d[1]_xor ^ debug_mode_d_xor */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_3      (0x0003U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< spare[3] */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_4      (0x0004U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< ilim2(from internal ctrl) */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_5      (0x0005U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< bos_rcp_flag_vbst */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_6      (0x0006U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< lvbuck3_tsd */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_7      (0x0007U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< ipt_i2c_tsp_dmux */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_8      (0x0008U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< OV<2> */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_9      (0x0009U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< ipg_fs_valid_wd */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_10     (0x000AU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< vpre_nuv_high ^ vpre_nuv_low ^ vpre_fb2_ov */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_11     (0x000BU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< pll_lock */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_12     (0x000CU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< vdig_por */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_13     (0x000DU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< dmux_hvbuck<2> */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_14     (0x000EU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< ipg_hvbuck_oc */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_15     (0x000FU << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< sw3_dmux_out_lv */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_16     (0x0010U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< DBG_out */
//#define FS8X_M_TM_DMUX_ERRMON_SEL_17     (0x0011U << FS8X_M_TM_DMUX_ERRMON_SEL_SHIFT) /*!< dmux_vpre3 */
//
///******************************************************************************/
///* M_TM_DMUX2 - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_M_TM_DMUX2_ADDR             0x1CU
//#define FS8X_M_TM_DMUX2_DEFAULT          0x0000U
//
//#define FS8X_M_TM_DMUX_FOUT_SEL_MASK     0x001FU /*!< Select DMUX FOUT input */
//#define FS8X_M_TM_DMUX_INTB_SEL_MASK     0x03E0U /*!< Select DMUX INTB input */
//#define FS8X_M_TM_DMUX_AMUX_SEL_MASK     0x7C00U /*!< Select DMUX AMUX input */
//
//#define FS8X_M_TM_DMUX_FOUT_SEL_SHIFT    0x0000U /*!< Select DMUX FOUT input */
//#define FS8X_M_TM_DMUX_INTB_SEL_SHIFT    0x0005U /*!< Select DMUX INTB input */
//#define FS8X_M_TM_DMUX_AMUX_SEL_SHIFT    0x000AU /*!< Select DMUX AMUX input */
//
//#define FS8X_M_TM_DMUX_FOUT_SEL_0        (0x0000U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< FOUT */
//#define FS8X_M_TM_DMUX_FOUT_SEL_1        (0x0001U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_FOUT_SEL_2        (0x0002U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< vbos_high_uv_n_d_xor ^ pll_lock_d_xor ^ wake1_d_xor ^ reg1_tsd_d_xor ^ fs_vmonx_ov_d[0]_xor ^ vsup_low_uv_n_d_xor ^ bg1_bg2_ok_d_xor */
//#define FS8X_M_TM_DMUX_FOUT_SEL_3        (0x0003U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< spare[2] */
//#define FS8X_M_TM_DMUX_FOUT_SEL_4        (0x0004U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< vea_min(from internal ctrl) */
//#define FS8X_M_TM_DMUX_FOUT_SEL_5        (0x0005U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< bos_vsup_reg */
//#define FS8X_M_TM_DMUX_FOUT_SEL_6        (0x0006U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< lvboost_tsd */
//#define FS8X_M_TM_DMUX_FOUT_SEL_7        (0x0007U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< csb */
//#define FS8X_M_TM_DMUX_FOUT_SEL_8        (0x0008U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< OV<3> */
//#define FS8X_M_TM_DMUX_FOUT_SEL_9        (0x0009U << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< ipg_fs_intb */
//#define FS8X_M_TM_DMUX_FOUT_SEL_10       (0x000AU << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< vboost_nuv_high ^ vboost_nuv_low */
//#define FS8X_M_TM_DMUX_FOUT_SEL_11       (0x000BU << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< FOUT */
//#define FS8X_M_TM_DMUX_FOUT_SEL_12       (0x000CU << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< vana_por */
//#define FS8X_M_TM_DMUX_FOUT_SEL_13       (0x000DU << FS8X_M_TM_DMUX_FOUT_SEL_SHIFT) /*!< dmux_hvbuck<3> */
//
//#define FS8X_M_TM_DMUX_INTB_SEL_0        (0x0000U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< 0 */
//#define FS8X_M_TM_DMUX_INTB_SEL_1        (0x0001U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_INTB_SEL_2        (0x0002U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< fs_vmonx_ov_d[5]_xor ^ lvboost_tsd_d_xor ^ lvbuck3_sw_on_lv_d_xor ^ vsup_high_uv_n_d_xor ^ fs_deepfs_d_xor */
//#define FS8X_M_TM_DMUX_INTB_SEL_3        (0x0003U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< spare[1] */
//#define FS8X_M_TM_DMUX_INTB_SEL_4        (0x0004U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< Dmux_blanking_time */
//#define FS8X_M_TM_DMUX_INTB_SEL_5        (0x0005U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< bos_vpre_reg */
//#define FS8X_M_TM_DMUX_INTB_SEL_6        (0x0006U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< reg1_tsd */
//#define FS8X_M_TM_DMUX_INTB_SEL_7        (0x0007U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< mosi */
//#define FS8X_M_TM_DMUX_INTB_SEL_8        (0x0008U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< OV<4> */
//#define FS8X_M_TM_DMUX_INTB_SEL_9        (0x0009U << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< ipg_fs_i2c_err */
//#define FS8X_M_TM_DMUX_INTB_SEL_10       (0x000AU << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< lvboost_up */
//#define FS8X_M_TM_DMUX_INTB_SEL_11       (0x000BU << FS8X_M_TM_DMUX_INTB_SEL_SHIFT) /*!< clock_channel_select (osc or FIN) */
//
//#define FS8X_M_TM_DMUX_AMUX_SEL_0        (0x0000U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< 0 */
//#define FS8X_M_TM_DMUX_AMUX_SEL_1        (0x0001U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< state toogle */
//#define FS8X_M_TM_DMUX_AMUX_SEL_2        (0x0002U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< fs_vmonx_ov_d[4]_xor ^ lvbuck3_tsd_d_xor ^ hvbuck_oc_d_xor ^ vpre_low_uv_n_d_xor ^ hvbuck_dvrls_d_xor */
//#define FS8X_M_TM_DMUX_AMUX_SEL_3        (0x0003U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< spare[0] */
//#define FS8X_M_TM_DMUX_AMUX_SEL_4        (0x0004U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< Lvboost_ov(from internal ctrl) */
//#define FS8X_M_TM_DMUX_AMUX_SEL_5        (0x0005U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< bos_vbst_reg */
//#define FS8X_M_TM_DMUX_AMUX_SEL_6        (0x0006U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< reg2_tsd */
//#define FS8X_M_TM_DMUX_AMUX_SEL_7        (0x0007U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< sck */
//#define FS8X_M_TM_DMUX_AMUX_SEL_8        (0x0008U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< OV<5> */
//#define FS8X_M_TM_DMUX_AMUX_SEL_9        (0x0009U << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< ipg_fs_spi_miso */
//#define FS8X_M_TM_DMUX_AMUX_SEL_10       (0x000AU << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< lvboost_down */
//#define FS8X_M_TM_DMUX_AMUX_SEL_11       (0x000BU << FS8X_M_TM_DMUX_AMUX_SEL_SHIFT) /*!< otp_busy */
//
///******************************************************************************/
///* M_TM_MODES1 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_TM_MODES1_ADDR            0x1DU
//#define FS8X_M_TM_MODES1_DEFAULT         0x0000U
//
//#define FS8X_M_TM_SCANMODE_M_FS_MASK     0x0001U /*!< Scan mode of Main and FailSafe top logics */
//#define FS8X_M_TM_SCANMODE_HVBCK_MASK    0x0002U /*!< Scan mode of HVBUCK AMSIP logics */
//#define FS8X_M_TM_SCANMODE_ALL_MASK      0x0004U /*!< Scan mode of all logics (HVBUCK and Main and FailSafe top logics) */
//#define FS8X_M_TM_M_MASK_UVOV_MASK       0x0400U /*!< Mask any UV/OV effect */
//#define FS8X_M_TM_AMUX_RM_LIMIT_MASK     0x0800U /*!< Test mode to remove the amux channel selection limit */
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_MASK  0x3000U /*!< Control I2C SDA out */
//#define FS8X_M_TM_M_MASK_RST_MASK        0x8000U /*!< N/A */
//
//#define FS8X_M_TM_SCANMODE_M_FS_SHIFT    0x0000U /*!< Scan mode of Main and FailSafe top logics */
//#define FS8X_M_TM_SCANMODE_HVBCK_SHIFT   0x0001U /*!< Scan mode of HVBUCK AMSIP logics */
//#define FS8X_M_TM_SCANMODE_ALL_SHIFT     0x0002U /*!< Scan mode of all logics (HVBUCK and Main and FailSafe top logics) */
//#define FS8X_M_TM_M_MASK_UVOV_SHIFT      0x000AU /*!< Mask any UV/OV effect */
//#define FS8X_M_TM_AMUX_RM_LIMIT_SHIFT    0x000BU /*!< Test mode to remove the amux channel selection limit */
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_SHIFT 0x000CU /*!< Control I2C SDA out */
//#define FS8X_M_TM_M_MASK_RST_SHIFT       0x000FU /*!< N/A */
//
//#define FS8X_M_TM_SCANMODE_M_FS_NOT_ACTIVATED (0x0000U << FS8X_M_TM_SCANMODE_M_FS_SHIFT) /*!< Not activated */
//#define FS8X_M_TM_SCANMODE_M_FS_ACTIVATED (0x0001U << FS8X_M_TM_SCANMODE_M_FS_SHIFT) /*!< activated */
//
//#define FS8X_M_TM_SCANMODE_HVBCK_NOT_ACTIVATED (0x0000U << FS8X_M_TM_SCANMODE_HVBCK_SHIFT) /*!< Not activated */
//#define FS8X_M_TM_SCANMODE_HVBCK_ACTIVATED (0x0001U << FS8X_M_TM_SCANMODE_HVBCK_SHIFT) /*!< activated */
//
//#define FS8X_M_TM_SCANMODE_ALL_NOT_ACTIVATED (0x0000U << FS8X_M_TM_SCANMODE_ALL_SHIFT) /*!< Not activated */
//#define FS8X_M_TM_SCANMODE_ALL_ACTIVATED (0x0001U << FS8X_M_TM_SCANMODE_ALL_SHIFT) /*!< activated */
//
//#define FS8X_M_TM_M_MASK_UVOV_NOT_ACTIVATED (0x0000U << FS8X_M_TM_M_MASK_UVOV_SHIFT) /*!< Not activated */
//#define FS8X_M_TM_M_MASK_UVOV_UV_OV_MASKED (0x0001U << FS8X_M_TM_M_MASK_UVOV_SHIFT) /*!< All UV/OV flag effect are masked */
//
//#define FS8X_M_TM_AMUX_RM_LIMIT_NOT_ACTIVATED (0x0000U << FS8X_M_TM_AMUX_RM_LIMIT_SHIFT) /*!< Not activated - channel selection is limited up to channel 20 */
//#define FS8X_M_TM_AMUX_RM_LIMIT_ACTIVATED (0x0001U << FS8X_M_TM_AMUX_RM_LIMIT_SHIFT) /*!< activated - all channels could be selected */
//
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_FREE_CONTROL (0x0000U << FS8X_M_TM_CTRL_I2C_SDA_OUT_SHIFT) /*!< Free control from both I2C controler Ips */
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_MASK_MAIN (0x0001U << FS8X_M_TM_CTRL_I2C_SDA_OUT_SHIFT) /*!< Mask I2C SDA out datapath from Main I2C controller */
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_MASK_FAILSAFE (0x0002U << FS8X_M_TM_CTRL_I2C_SDA_OUT_SHIFT) /*!< Mask I2C SDA out datapath from FailSafe I2C controller */
//#define FS8X_M_TM_CTRL_I2C_SDA_OUT_FORCE_ZERO (0x0003U << FS8X_M_TM_CTRL_I2C_SDA_OUT_SHIFT) /*!< Force 0 state on SDA */
//
//#define FS8X_M_TM_M_MASK_RST_NOT_ACTIVATED (0x0000U << FS8X_M_TM_M_MASK_RST_SHIFT) /*!< Not activated */
//#define FS8X_M_TM_M_MASK_RST_ACTIVATED   (0x0001U << FS8X_M_TM_M_MASK_RST_SHIFT) /*!< activated */
//
///******************************************************************************/
///* M_TM_MODES2 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_M_TM_MODES2_ADDR            0x1EU
//#define FS8X_M_TM_MODES2_DEFAULT         0x0000U
//
//#define FS8X_M_TM_JTAG_EN_MASK           0x0001U /*!< JTAG mode */
//#define FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_MASK 0x0002U /*!< Test Mode to activate division by 8 of dmux signals from lvbuck mp dvs AMS IP */
//#define FS8X_M_TM_FORCE_MISO_EN_MASK     0x0004U /*!< Set forced value on MISO_EN */
//#define FS8X_M_TM_FORCE_MISO_MASK        0x0008U /*!< Set forced value on MISO */
//#define FS8X_M_TM_FORCE_SPI_OUT_MASK     0x0010U /*!< Enable to force MISO and MISO_EN output state */
//#define FS8X_M_TM_ILIM_FILT_SEL_MASK     0x0060U /*!< Select Ilim flag filters detection duration */
//#define FS8X_M_TM_M_FORCE_DBG_MODE_MASK  0x0080U /*!< Force Debug Mode */
//#define FS8X_M_TM_CLKMGT_WD_BYPASS_MASK  0x0100U /*!< Test Mode to bypass clock management WD detection */
//#define FS8X_M_TM_M_EXT_CLK_MASK         0x0200U /*!< Take control of the clock oscillateur source */
//#define FS8X_M_TM_MASK_TSD_MASK          0x0400U /*!< Mask TSD event effect */
//#define FS8X_M_TM_CLK_FM_STEP_MASK       0x0800U /*!< Clock FM Test Mode Step Advancement */
//#define FS8X_M_TM_CLK_FM_EN_MASK         0x1000U /*!< Clock FM Test Mode Enable */
//#define FS8X_M_TM_M_FUSE_VPP_EN_MASK     0x2000U /*!< Control the output pin ipg_fuse_vpp_en state */
//#define FS8X_M_TM_REF_CLK_FIN_MASK       0x4000U /*!< Reference clock control */
//#define FS8X_M_TM_LVBOOST_HTOL_MASK      0x8000U /*!< LVBOOST HTOL Test Mode Control */
//
//#define FS8X_M_TM_JTAG_EN_SHIFT          0x0000U /*!< JTAG mode */
//#define FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_SHIFT 0x0001U /*!< Test Mode to activate division by 8 of dmux signals from lvbuck mp dvs AMS IP */
//#define FS8X_M_TM_FORCE_MISO_EN_SHIFT    0x0002U /*!< Set forced value on MISO_EN */
//#define FS8X_M_TM_FORCE_MISO_SHIFT       0x0003U /*!< Set forced value on MISO */
//#define FS8X_M_TM_FORCE_SPI_OUT_SHIFT    0x0004U /*!< Enable to force MISO and MISO_EN output state */
//#define FS8X_M_TM_ILIM_FILT_SEL_SHIFT    0x0005U /*!< Select Ilim flag filters detection duration */
//#define FS8X_M_TM_M_FORCE_DBG_MODE_SHIFT 0x0007U /*!< Force Debug Mode */
//#define FS8X_M_TM_CLKMGT_WD_BYPASS_SHIFT 0x0008U /*!< Test Mode to bypass clock management WD detection */
//#define FS8X_M_TM_M_EXT_CLK_SHIFT        0x0009U /*!< Take control of the clock oscillateur source */
//#define FS8X_M_TM_MASK_TSD_SHIFT         0x000AU /*!< Mask TSD event effect */
//#define FS8X_M_TM_CLK_FM_STEP_SHIFT      0x000BU /*!< Clock FM Test Mode Step Advancement */
//#define FS8X_M_TM_CLK_FM_EN_SHIFT        0x000CU /*!< Clock FM Test Mode Enable */
//#define FS8X_M_TM_M_FUSE_VPP_EN_SHIFT    0x000DU /*!< Control the output pin ipg_fuse_vpp_en state */
//#define FS8X_M_TM_REF_CLK_FIN_SHIFT      0x000EU /*!< Reference clock control */
//#define FS8X_M_TM_LVBOOST_HTOL_SHIFT     0x000FU /*!< LVBOOST HTOL Test Mode Control */
//
//#define FS8X_M_TM_JTAG_EN_INACTIVE       (0x0000U << FS8X_M_TM_JTAG_EN_SHIFT) /*!< Inactive */
//#define FS8X_M_TM_JTAG_EN_JTAG_MODE_ENABLED (0x0001U << FS8X_M_TM_JTAG_EN_SHIFT) /*!< JTAG mode is enabled */
//
//#define FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_NO_DIVISION (0x0000U << FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_SHIFT) /*!< No division */
//#define FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_DIVISION_BY_8 (0x0001U << FS8X_M_TM_LVBUCK_DMUX_DIV8_EN_SHIFT) /*!< Division by 8 is activated */
//
//#define FS8X_M_TM_FORCE_MISO_EN_FORCE_0_STATE (0x0000U << FS8X_M_TM_FORCE_MISO_EN_SHIFT) /*!< Force a 0 state */
//#define FS8X_M_TM_FORCE_MISO_EN_FORCE_1_STATE (0x0001U << FS8X_M_TM_FORCE_MISO_EN_SHIFT) /*!< Force a 1 state */
//
//#define FS8X_M_TM_FORCE_MISO_FORCE_0_STATE (0x0000U << FS8X_M_TM_FORCE_MISO_SHIFT) /*!< Force a 0 state */
//#define FS8X_M_TM_FORCE_MISO_FORCE_1_STATE (0x0001U << FS8X_M_TM_FORCE_MISO_SHIFT) /*!< Force a 1 state */
//
//#define FS8X_M_TM_FORCE_SPI_OUT_FORCE_NOT_ENABLED (0x0000U << FS8X_M_TM_FORCE_SPI_OUT_SHIFT) /*!< Force not enabled */
//#define FS8X_M_TM_FORCE_SPI_OUT_FORCE_ENABLED (0x0001U << FS8X_M_TM_FORCE_SPI_OUT_SHIFT) /*!< Force is enabled */
//
//#define FS8X_M_TM_ILIM_FILT_SEL_1MS      (0x0000U << FS8X_M_TM_ILIM_FILT_SEL_SHIFT) /*!< 1ms duration selected */
//#define FS8X_M_TM_ILIM_FILT_SEL_2MS      (0x0001U << FS8X_M_TM_ILIM_FILT_SEL_SHIFT) /*!< 2ms duration selected */
//#define FS8X_M_TM_ILIM_FILT_SEL_4MS      (0x0000U << FS8X_M_TM_ILIM_FILT_SEL_SHIFT) /*!< 4ms duration selected */
//#define FS8X_M_TM_ILIM_FILT_SEL_8MS      (0x0001U << FS8X_M_TM_ILIM_FILT_SEL_SHIFT) /*!< 8ms duration selected */
//
//#define FS8X_M_TM_M_FORCE_DBG_MODE_NOT_FORCED (0x0000U << FS8X_M_TM_M_FORCE_DBG_MODE_SHIFT) /*!< Debug mode not forced */
//#define FS8X_M_TM_M_FORCE_DBG_MODE_FORCED (0x0001U << FS8X_M_TM_M_FORCE_DBG_MODE_SHIFT) /*!< Debug mode forced */
//
//#define FS8X_M_TM_CLKMGT_WD_BYPASS_NOT_BYPASSED (0x0000U << FS8X_M_TM_CLKMGT_WD_BYPASS_SHIFT) /*!< Not bypassed */
//#define FS8X_M_TM_CLKMGT_WD_BYPASS_BYPASSED (0x0001U << FS8X_M_TM_CLKMGT_WD_BYPASS_SHIFT) /*!< Bypassed */
//
//#define FS8X_M_TM_M_EXT_CLK_OSCILLATOR   (0x0000U << FS8X_M_TM_M_EXT_CLK_SHIFT) /*!< Oscillaltor is the clock source */
//#define FS8X_M_TM_M_EXT_CLK_FIN          (0x0001U << FS8X_M_TM_M_EXT_CLK_SHIFT) /*!< FIN (fsync_in) pad is the clock source */
//
//#define FS8X_M_TM_MASK_TSD_NOT_MASKED    (0x0000U << FS8X_M_TM_MASK_TSD_SHIFT) /*!< Not masked */
//#define FS8X_M_TM_MASK_TSD_MASKED        (0x0001U << FS8X_M_TM_MASK_TSD_SHIFT) /*!< Masked */
//
//#define FS8X_M_TM_CLK_FM_STEP_NO_EFFECT  (0x0000U << FS8X_M_TM_CLK_FM_STEP_SHIFT) /*!< No effect */
//#define FS8X_M_TM_CLK_FM_STEP_STEP_TO_NEXT_VALUE (0x0001U << FS8X_M_TM_CLK_FM_STEP_SHIFT) /*!< Step to next clock deviation value */
//
//#define FS8X_M_TM_CLK_FM_EN_TEST_MODE_INACTIVE (0x0000U << FS8X_M_TM_CLK_FM_EN_SHIFT) /*!< Test Mode inactive */
//#define FS8X_M_TM_CLK_FM_EN_TEST_MODE_ACTIVATED (0x0001U << FS8X_M_TM_CLK_FM_EN_SHIFT) /*!< Tet Mode activated */
//
//#define FS8X_M_TM_M_FUSE_VPP_EN_SET_ZERO (0x0000U << FS8X_M_TM_M_FUSE_VPP_EN_SHIFT) /*!< Set to 0 */
//#define FS8X_M_TM_M_FUSE_VPP_EN_SET_ONE  (0x0001U << FS8X_M_TM_M_FUSE_VPP_EN_SHIFT) /*!< Set to 1 */
//
//#define FS8X_M_TM_REF_CLK_FIN_CLK_OSC_DIV_5 (0x0000U << FS8X_M_TM_REF_CLK_FIN_SHIFT) /*!< Ref clock is a copy of clock osc divided by 5 */
//#define FS8X_M_TM_REF_CLK_FIN_FIN        (0x0001U << FS8X_M_TM_REF_CLK_FIN_SHIFT) /*!< Ref clock is driven by FIN (fsync_in) */
//
//#define FS8X_M_TM_LVBOOST_HTOL_NOT_ACTIVATED (0x0000U << FS8X_M_TM_LVBOOST_HTOL_SHIFT) /*!< Htol TM not activated */
//#define FS8X_M_TM_LVBOOST_HTOL_ACTIVATED (0x0001U << FS8X_M_TM_LVBOOST_HTOL_SHIFT) /*!< Htol TM activated */
//
///******************************************************************************/
///* M_TM_STATUS1 - Type: R                                                     */
///******************************************************************************/
//
//#define FS8X_M_TM_STATUS1_ADDR           0x1FU
//#define FS8X_M_TM_STATUS1_DEFAULT        0x0000U
//
//#define FS8X_M_TM_M_FSM_CURR_STATE_MASK  0x001FU /*!< Main FSM current state */
//#define FS8X_M_TM_M_TM_ACTIVE_MASK       0x0020U /*!< Main logic Test Mode Activation */
//#define FS8X_M_TM_HVBUCK_CURR_STATE_MASK 0x0380U /*!< HVBUCK FSM current state */
//#define FS8X_M_TM_M_FSM_AUTORETRY_CNT_MASK 0x3C00U /*!< FSM autoretry counter value */
//#define FS8X_M_TM_CLKMGT_EXT_FIN_SEL_MASK 0x4000U /*!< Clock management FIN clock selection to PLL status */
//#define FS8X_M_TM_CLKMGT_WD_OK_MASK      0x8000U /*!< Clock Management Watchdog OK status */
//
//#define FS8X_M_TM_M_FSM_CURR_STATE_SHIFT 0x0000U /*!< Main FSM current state */
//#define FS8X_M_TM_M_TM_ACTIVE_SHIFT      0x0005U /*!< Main logic Test Mode Activation */
//#define FS8X_M_TM_HVBUCK_CURR_STATE_SHIFT 0x0007U /*!< HVBUCK FSM current state */
//#define FS8X_M_TM_M_FSM_AUTORETRY_CNT_SHIFT 0x000AU /*!< FSM autoretry counter value */
//#define FS8X_M_TM_CLKMGT_EXT_FIN_SEL_SHIFT 0x000EU /*!< Clock management FIN clock selection to PLL status */
//#define FS8X_M_TM_CLKMGT_WD_OK_SHIFT     0x000FU /*!< Clock Management Watchdog OK status */
//
//#define FS8X_M_TM_M_FSM_CURR_STATE_M1    (0x0000U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M1 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M2    (0x0001U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M2 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M3    (0x0002U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M3 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M4    (0x0003U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M4 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M5    (0x0004U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M5 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M6    (0x0005U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M6 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M7    (0x0006U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M7 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M8    (0x0007U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M8 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M9    (0x0008U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M9 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M10   (0x0009U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M10 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M11   (0x000AU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M11 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M12   (0x000BU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M12 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M13   (0x000CU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M13 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M14   (0x000DU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M14 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M15   (0x000EU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M15 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M16   (0x000FU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M16 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M17   (0x0010U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M17 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M18   (0x0011U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M18 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M19   (0x0012U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M19 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M20   (0x0013U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M20 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M21   (0x0014U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M21 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M22   (0x0015U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M22 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M23   (0x0016U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M23 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M24   (0x0017U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M24 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M25   (0x0018U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M25 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M26   (0x0019U << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M26 */
//#define FS8X_M_TM_M_FSM_CURR_STATE_M27   (0x001AU << FS8X_M_TM_M_FSM_CURR_STATE_SHIFT) /*!< M27 */
//
//#define FS8X_M_TM_M_TM_ACTIVE_TEST_MODE_ACTIVATED (0x0000U << FS8X_M_TM_M_TM_ACTIVE_SHIFT) /*!< Main Test Mode is not activated */
//#define FS8X_M_TM_M_TM_ACTIVE_TEST_MODE_NOT_ACTIVATED (0x0001U << FS8X_M_TM_M_TM_ACTIVE_SHIFT) /*!< Main logic Test Mode is activated */
//
//#define FS8X_M_TM_M_FSM_AUTORETRY_CNT_NO_AUTORETRY_PERFORMED (0x0000U << FS8X_M_TM_M_FSM_AUTORETRY_CNT_SHIFT) /*!< No autoretry performed */
//
//#define FS8X_M_TM_CLKMGT_EXT_FIN_SEL_INTERNAL_OSCILATOR (0x0000U << FS8X_M_TM_CLKMGT_EXT_FIN_SEL_SHIFT) /*!< Internal clock oscilaltor is selected */
//#define FS8X_M_TM_CLKMGT_EXT_FIN_SEL_EXTERNAL_CLOCK (0x0001U << FS8X_M_TM_CLKMGT_EXT_FIN_SEL_SHIFT) /*!< External FIN clock is selected */
//
//#define FS8X_M_TM_CLKMGT_WD_OK_RANGE_NOT_OK (0x0000U << FS8X_M_TM_CLKMGT_WD_OK_SHIFT) /*!< Clock frequency range is not ok */
//#define FS8X_M_TM_CLKMGT_WD_OK_RANGE_OK  (0x0001U << FS8X_M_TM_CLKMGT_WD_OK_SHIFT) /*!< Clock frequency range is ok */
//
///******************************************************************************/
///* M_TM_STATUS2 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_M_TM_STATUS2_ADDR           0x20U
//#define FS8X_M_TM_STATUS2_DEFAULT        0x0000U
//
//#define FS8X_M_TM_LVBUCK1_STATE_MASK     0x0007U /*!< Lvbuck1 state */
//#define FS8X_M_TM_LVBUCK1_MODE_MASK      0x0038U /*!< Lvbuck1 mode */
//#define FS8X_M_TM_LVBUCK2_STATE_MASK     0x01C0U /*!< Lvbuck2 state */
//#define FS8X_M_TM_LVBUCK2_MODE_MASK      0x0E00U /*!< Lvbuck2 mode */
//
//#define FS8X_M_TM_LVBUCK1_STATE_SHIFT    0x0000U /*!< Lvbuck1 state */
//#define FS8X_M_TM_LVBUCK1_MODE_SHIFT     0x0003U /*!< Lvbuck1 mode */
//#define FS8X_M_TM_LVBUCK2_STATE_SHIFT    0x0006U /*!< Lvbuck2 state */
//#define FS8X_M_TM_LVBUCK2_MODE_SHIFT     0x0009U /*!< Lvbuck2 mode */
//
///******************************************************************************/
///* M_TM_STATUS3 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_M_TM_STATUS3_ADDR           0x21U
//#define FS8X_M_TM_STATUS3_DEFAULT        0x0000U
//
//#define FS8X_M_TM_M_FS_LVBUCK_SVS_MASK   0x001FU /*!< LVBUCK SVS from FailSafe logic */
//
//#define FS8X_M_TM_M_FS_LVBUCK_SVS_SHIFT  0x0000U /*!< LVBUCK SVS from FailSafe logic */
//
///******************************************************************************/
///* M_TM_MASKID - Type: R                                                      */
///******************************************************************************/
//
//#define FS8X_M_TM_MASKID_ADDR            0x22U
//#define FS8X_M_TM_MASKID_DEFAULT         0x0000U
//
//#define FS8X_M_TM_MASKID_MASK            0xFFFFU /*!< Metal Mask ID */
//
//#define FS8X_M_TM_MASKID_SHIFT           0x0000U /*!< Metal Mask ID */
//
///******************************************************************************/
///* FS_GRL_FLAGS - Type: R                                                     */
///******************************************************************************/
//
//#define FS8X_FS_GRL_FLAGS_ADDR           0x00U
//#define FS8X_FS_GRL_FLAGS_DEFAULT        0x0000U
//
//#define FS8X_FS_FS_REG_OVUV_G_MASK       0x1000U /*!< Report an issue in one of the voltage monitoring (OV or UV) */
//#define FS8X_FS_FS_IO_G_MASK             0x2000U /*!< Report an issue in one of the Fail Safe IOs */
//#define FS8X_FS_FS_WD_G_MASK             0x4000U /*!< Report an issue on the Watchdog refresh */
//#define FS8X_FS_FS_COM_G_MASK            0x8000U /*!< Report an issue in the communication (SPI or I2C) */
//
//#define FS8X_FS_FS_REG_OVUV_G_SHIFT      0x000CU /*!< Report an issue in one of the voltage monitoring (OV or UV) */
//#define FS8X_FS_FS_IO_G_SHIFT            0x000DU /*!< Report an issue in one of the Fail Safe IOs */
//#define FS8X_FS_FS_WD_G_SHIFT            0x000EU /*!< Report an issue on the Watchdog refresh */
//#define FS8X_FS_FS_COM_G_SHIFT           0x000FU /*!< Report an issue in the communication (SPI or I2C) */
//
//#define FS8X_FS_FS_REG_OVUV_G_NO_FAILURE (0x0000U << FS8X_FS_FS_REG_OVUV_G_SHIFT) /*!< No Failure */
//#define FS8X_FS_FS_REG_OVUV_G_FAILURE    (0x0001U << FS8X_FS_FS_REG_OVUV_G_SHIFT) /*!< Failure */
//
//#define FS8X_FS_FS_IO_G_NO_FAILURE       (0x0000U << FS8X_FS_FS_IO_G_SHIFT) /*!< No Failure */
//#define FS8X_FS_FS_IO_G_FAILURE          (0x0001U << FS8X_FS_FS_IO_G_SHIFT) /*!< Failure */
//
//#define FS8X_FS_FS_WD_G_GOOD_WD_REFRESH  (0x0000U << FS8X_FS_FS_WD_G_SHIFT) /*!< Good WD Refresh */
//#define FS8X_FS_FS_WD_G_BAD_WD_REFRESH   (0x0001U << FS8X_FS_FS_WD_G_SHIFT) /*!< Bad WD Refresh */
//
//#define FS8X_FS_FS_COM_G_NO_FAILURE      (0x0000U << FS8X_FS_FS_COM_G_SHIFT) /*!< No Failure */
//#define FS8X_FS_FS_COM_G_FAILURE         (0x0001U << FS8X_FS_FS_COM_G_SHIFT) /*!< Failure */
//
///******************************************************************************/
///* FS_WD_WINDOW - Type: RW                                                    */
///******************************************************************************/

#define FS8X_FS_WD_WINDOW_ADDR           0x0DU
#define FS8X_FS_WD_WINDOW_DEFAULT        0x3200U

#define FS8X_FS_WDW_RECOVERY_MASK        0x000FU /*!< Watchdog Window Duration when the device is in Fault Recovery Strategy. */
#define FS8X_FS_WDW_DC_MASK              0x0700U /*!< CLOSED window */
#define FS8X_FS_WD_WINDOW_MASK           0xF000U /*!< Watchdog Window Duration */

#define FS8X_FS_WDW_RECOVERY_SHIFT       0x0000U /*!< Watchdog Window Duration when the device is in Fault Recovery Strategy. */
#define FS8X_FS_WDW_DC_SHIFT             0x0008U /*!< CLOSED window */
#define FS8X_FS_WD_WINDOW_SHIFT          0x000CU /*!< Watchdog Window Duration */

#define FS8X_FS_WDW_RECOVERY_DISABLE     (0x0000U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< DISABLE */
#define FS8X_FS_WDW_RECOVERY_1MS         (0x0001U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 1.0ms */
#define FS8X_FS_WDW_RECOVERY_2MS         (0x0002U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 2.0ms */
#define FS8X_FS_WDW_RECOVERY_3MS         (0x0003U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 3.0ms */
#define FS8X_FS_WDW_RECOVERY_4MS         (0x0004U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 4.0ms */
#define FS8X_FS_WDW_RECOVERY_6MS         (0x0005U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 6.0ms */
#define FS8X_FS_WDW_RECOVERY_8MS         (0x0006U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 8.0ms */
#define FS8X_FS_WDW_RECOVERY_12MS        (0x0007U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 12ms */
#define FS8X_FS_WDW_RECOVERY_16MS        (0x0008U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 16ms */
#define FS8X_FS_WDW_RECOVERY_24MS        (0x0009U << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 24ms */
#define FS8X_FS_WDW_RECOVERY_32MS        (0x000AU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 32ms */
#define FS8X_FS_WDW_RECOVERY_64MS        (0x000BU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 64ms */
#define FS8X_FS_WDW_RECOVERY_128MS       (0x000CU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 128ms */
#define FS8X_FS_WDW_RECOVERY_256MS       (0x000DU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 256ms */
#define FS8X_FS_WDW_RECOVERY_512MS       (0x000EU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 512ms */
#define FS8X_FS_WDW_RECOVERY_1024MS      (0x000FU << FS8X_FS_WDW_RECOVERY_SHIFT) /*!< 1024ms */

#define FS8X_FS_WDW_DC_31_25             (0x0000U << FS8X_FS_WDW_DC_SHIFT) /*!< 31.25% */
#define FS8X_FS_WDW_DC_37_5              (0x0001U << FS8X_FS_WDW_DC_SHIFT) /*!< 37.5% */
#define FS8X_FS_WDW_DC_50                (0x0002U << FS8X_FS_WDW_DC_SHIFT) /*!< 50% */
#define FS8X_FS_WDW_DC_62_5              (0x0003U << FS8X_FS_WDW_DC_SHIFT) /*!< 62.5% */
#define FS8X_FS_WDW_DC_68_75             (0x0004U << FS8X_FS_WDW_DC_SHIFT) /*!< 68.75% */

#define FS8X_FS_WD_WINDOW_DISABLE        (0x0000U << FS8X_FS_WD_WINDOW_SHIFT) /*!< DISABLE (during INIT_FS only) */
#define FS8X_FS_WD_WINDOW_1MS            (0x0001U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 1.0ms */
#define FS8X_FS_WD_WINDOW_2MS            (0x0002U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 2.0ms */
#define FS8X_FS_WD_WINDOW_3MS            (0x0003U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 3.0ms */
#define FS8X_FS_WD_WINDOW_4MS            (0x0004U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 4.0ms */
#define FS8X_FS_WD_WINDOW_6MS            (0x0005U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 6.0ms */
#define FS8X_FS_WD_WINDOW_8MS            (0x0006U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 8.0ms */
#define FS8X_FS_WD_WINDOW_12MS           (0x0007U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 12ms */
#define FS8X_FS_WD_WINDOW_16MS           (0x0008U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 16ms */
#define FS8X_FS_WD_WINDOW_24MS           (0x0009U << FS8X_FS_WD_WINDOW_SHIFT) /*!< 24ms */
#define FS8X_FS_WD_WINDOW_32MS           (0x000AU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 32ms */
#define FS8X_FS_WD_WINDOW_64MS           (0x000BU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 64ms */
#define FS8X_FS_WD_WINDOW_128MS          (0x000CU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 128ms */
#define FS8X_FS_WD_WINDOW_256MS          (0x000DU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 256ms */
#define FS8X_FS_WD_WINDOW_512MS          (0x000EU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 512ms */
#define FS8X_FS_WD_WINDOW_1024MS         (0x000FU << FS8X_FS_WD_WINDOW_SHIFT) /*!< 1024ms */

///******************************************************************************/
///* FS_NOT_WD_WINDOW - Type: RW                                                */
///******************************************************************************/

#define FS8X_FS_NOT_WD_WINDOW_ADDR       0x0EU
#define FS8X_FS_NOT_WD_WINDOW_DEFAULT    0xCDF0U

#define FS8X_FS_NOT_WDW_RECOVERY_MASK    0x000FU /*!< Watchdog Window Duration when the device is in Fault Recovery Strategy. */
#define FS8X_FS_NOT_WDW_DC_MASK          0x0700U /*!< CLOSED window */
#define FS8X_FS_NOT_WD_WINDOW_MASK       0xF000U /*!< Watchdog Window Duration */

#define FS8X_FS_NOT_WDW_RECOVERY_SHIFT   0x0000U /*!< Watchdog Window Duration when the device is in Fault Recovery Strategy. */
#define FS8X_FS_NOT_WDW_DC_SHIFT         0x0008U /*!< CLOSED window */
#define FS8X_FS_NOT_WD_WINDOW_SHIFT      0x000CU /*!< Watchdog Window Duration */

///******************************************************************************/
///* FS_WD_SEED - Type: RW                                                      */
///******************************************************************************/

#define FS8X_FS_WD_SEED_ADDR             0x0FU
#define FS8X_FS_WD_SEED_DEFAULT          0x5AB2U

#define FS8X_FS_WD_SEED_MASK             0xFFFFU /*!< Seed for the LFSR */

#define FS8X_FS_WD_SEED_SHIFT            0x0000U /*!< Seed for the LFSR */

///******************************************************************************/
///* FS_WD_ANSWER - Type: RW                                                    */
///******************************************************************************/

#define FS8X_FS_WD_ANSWER_ADDR           0x10U
#define FS8X_FS_WD_ANSWER_DEFAULT        0x0000U

#define FS8X_FS_WD_ANSWER_MASK           0xFFFFU /*!< WATCHDOG LFSR VALUE */

#define FS8X_FS_WD_ANSWER_SHIFT          0x0000U /*!< WATCHDOG LFSR VALUE */

///******************************************************************************/
///* FS_OVUVREG_STATUS - Type: RW                                               */
///******************************************************************************/
//
//#define FS8X_FS_OVUVREG_STATUS_ADDR      0x11U
//#define FS8X_FS_OVUVREG_STATUS_DEFAULT   0x5550U
//
//#define FS8X_FS_FS_OSC_DRIFT_MASK        0x0002U /*!< Drift of the Fail Safe OSC */
//#define FS8X_FS_FS_DIG_REF_OV_MASK       0x0004U /*!< Overvoltage of the Internal Digital Fail Safe reference voltage */
//#define FS8X_FS_VMON1_UV_MASK            0x0010U /*!< Undervoltage Monitoring on VMON1 */
//#define FS8X_FS_VMON1_OV_MASK            0x0020U /*!< Overvoltage Monitoring on VMON1 */
//#define FS8X_FS_VMON2_UV_MASK            0x0040U /*!< Undervoltage Monitoring on VMON2 */
//#define FS8X_FS_VMON2_OV_MASK            0x0080U /*!< Overvoltage Monitoring on VMON2 */
//#define FS8X_FS_VMON3_UV_MASK            0x0100U /*!< Undervoltage Monitoring on VMON3 */
//#define FS8X_FS_VMON3_OV_MASK            0x0200U /*!< Overvoltage Monitoring on VMON3 */
//#define FS8X_FS_VMON4_UV_MASK            0x0400U /*!< Undervoltage Monitoring on VMON4 */
//#define FS8X_FS_VMON4_OV_MASK            0x0800U /*!< Overvoltage Monitoring on VMON4 */
//#define FS8X_FS_VDDIO_UV_MASK            0x1000U /*!< Undervoltage Monitoring on VDDIO */
//#define FS8X_FS_VDDIO_OV_MASK            0x2000U /*!< Overvoltage Monitoring on VDDIO */
//#define FS8X_FS_VCOREMON_UV_MASK         0x4000U /*!< Undervoltage Monitoring on VCOREMON */
//#define FS8X_FS_VCOREMON_OV_MASK         0x8000U /*!< Overvoltage Monitoring on VCOREMON */
//
//#define FS8X_FS_FS_OSC_DRIFT_SHIFT       0x0001U /*!< Drift of the Fail Safe OSC */
//#define FS8X_FS_FS_DIG_REF_OV_SHIFT      0x0002U /*!< Overvoltage of the Internal Digital Fail Safe reference voltage */
//#define FS8X_FS_VMON1_UV_SHIFT           0x0004U /*!< Undervoltage Monitoring on VMON1 */
//#define FS8X_FS_VMON1_OV_SHIFT           0x0005U /*!< Overvoltage Monitoring on VMON1 */
//#define FS8X_FS_VMON2_UV_SHIFT           0x0006U /*!< Undervoltage Monitoring on VMON2 */
//#define FS8X_FS_VMON2_OV_SHIFT           0x0007U /*!< Overvoltage Monitoring on VMON2 */
//#define FS8X_FS_VMON3_UV_SHIFT           0x0008U /*!< Undervoltage Monitoring on VMON3 */
//#define FS8X_FS_VMON3_OV_SHIFT           0x0009U /*!< Overvoltage Monitoring on VMON3 */
//#define FS8X_FS_VMON4_UV_SHIFT           0x000AU /*!< Undervoltage Monitoring on VMON4 */
//#define FS8X_FS_VMON4_OV_SHIFT           0x000BU /*!< Overvoltage Monitoring on VMON4 */
//#define FS8X_FS_VDDIO_UV_SHIFT           0x000CU /*!< Undervoltage Monitoring on VDDIO */
//#define FS8X_FS_VDDIO_OV_SHIFT           0x000DU /*!< Overvoltage Monitoring on VDDIO */
//#define FS8X_FS_VCOREMON_UV_SHIFT        0x000EU /*!< Undervoltage Monitoring on VCOREMON */
//#define FS8X_FS_VCOREMON_OV_SHIFT        0x000FU /*!< Overvoltage Monitoring on VCOREMON */
//
//#define FS8X_FS_FS_OSC_DRIFT_NO_DRIFT    (0x0000U << FS8X_FS_FS_OSC_DRIFT_SHIFT) /*!< No Drift */
//#define FS8X_FS_FS_OSC_DRIFT_OSCILLATOR_DRIFT (0x0001U << FS8X_FS_FS_OSC_DRIFT_SHIFT) /*!< Oscillator Drift */
//
//#define FS8X_FS_FS_DIG_REF_OV_NO_OVERVOLTAGE (0x0000U << FS8X_FS_FS_DIG_REF_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_FS_DIG_REF_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_FS_DIG_REF_OV_SHIFT) /*!< Overvoltage reported of the internal digital fail safe reference voltage */
//
//#define FS8X_FS_VMON1_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VMON1_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VMON1_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON1_UV_SHIFT) /*!< Undervoltage Reported on VMON1 */
//
//#define FS8X_FS_VMON1_OV_NO_OVERVOLTAGE  (0x0000U << FS8X_FS_VMON1_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VMON1_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON1_OV_SHIFT) /*!< Overvoltage Reported on VMON1 */
//
//#define FS8X_FS_VMON2_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VMON2_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VMON2_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON2_UV_SHIFT) /*!< Undervoltage Reported on VMON2 */
//
//#define FS8X_FS_VMON2_OV_NO_OVERVOLTAGE  (0x0000U << FS8X_FS_VMON2_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VMON2_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON2_OV_SHIFT) /*!< Overvoltage Reported on VMON2 */
//
//#define FS8X_FS_VMON3_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VMON3_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VMON3_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON3_UV_SHIFT) /*!< Undervoltage Reported on VMON3 */
//
//#define FS8X_FS_VMON3_OV_NO_OVERVOLTAGE  (0x0000U << FS8X_FS_VMON3_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VMON3_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON3_OV_SHIFT) /*!< Overvoltage Reported on VMON3 */
//
//#define FS8X_FS_VMON4_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VMON4_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VMON4_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON4_UV_SHIFT) /*!< Undervoltage Reported on VMON4 */
//
//#define FS8X_FS_VMON4_OV_NO_OVERVOLTAGE  (0x0000U << FS8X_FS_VMON4_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VMON4_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VMON4_OV_SHIFT) /*!< Overvoltage Reported on VMON4 */
//
//#define FS8X_FS_VDDIO_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VDDIO_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VDDIO_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VDDIO_UV_SHIFT) /*!< Undervoltage Reported on VDDIO */
//
//#define FS8X_FS_VDDIO_OV_NO_OVERVOLTAGE  (0x0000U << FS8X_FS_VDDIO_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VDDIO_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VDDIO_OV_SHIFT) /*!< Overvoltage Reported on VDDIO */
//
//#define FS8X_FS_VCOREMON_UV_NO_UNDERVOLTAGE (0x0000U << FS8X_FS_VCOREMON_UV_SHIFT) /*!< No Undervoltage */
//#define FS8X_FS_VCOREMON_UV_UNDERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VCOREMON_UV_SHIFT) /*!< Undervoltage Reported on VCOREMON */
//
//#define FS8X_FS_VCOREMON_OV_NO_OVERVOLTAGE (0x0000U << FS8X_FS_VCOREMON_OV_SHIFT) /*!< No Overvoltage */
//#define FS8X_FS_VCOREMON_OV_OVERVOLTAGE_REPORTED (0x0001U << FS8X_FS_VCOREMON_OV_SHIFT) /*!< Overvoltage Reported on VCOREMON */
//
///******************************************************************************/
///* FS_RELEASE_FS0B - Type: RW                                                 */
///******************************************************************************/

#define FS8X_FS_RELEASE_FS0B_ADDR        0x12U
#define FS8X_FS_RELEASE_FS0B_DEFAULT     0x0000U

#define FS8X_FS_RELEASE_FS0B_MASK        0xFFFFU /*!< Secure 16bits word to release FS0B */

#define FS8X_FS_RELEASE_FS0B_SHIFT       0x0000U /*!< Secure 16bits word to release FS0B */

///******************************************************************************/
///* FS_SAFE_IOS - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_FS_SAFE_IOS_ADDR            0x13U
//#define FS8X_FS_SAFE_IOS_DEFAULT         0x0000U
//
//#define FS8X_FS_GO_TO_INITFS_MASK        0x0004U /*!< Go back to INIT Fail Safe request */
//#define FS8X_FS_FS0B_REQ_MASK            0x0008U /*!< Request assertion of FS0B */
//#define FS8X_FS_FS0B_DIAG_MASK           0x0010U /*!< Report a Failure on FS0B */
//#define FS8X_FS_FS0B_SNS_MASK            0x0020U /*!< Sense of FS0B pad */
//#define FS8X_FS_FS0B_DRV_MASK            0x0040U /*!< FS0B driver _ digital command */
//#define FS8X_FS_RSTB_REQ_MASK            0x0080U /*!< Request assertion of RSTB (Pulse) */
//#define FS8X_FS_RSTB_DIAG_MASK           0x0100U /*!< Report a RSTB Short to High */
//#define FS8X_FS_RSTB_EVENT_MASK          0x0200U /*!< Report a RSTB event */
//#define FS8X_FS_RSTB_SNS_MASK            0x0400U /*!< Sense of RSTB pad */
//#define FS8X_FS_RSTB_DRV_MASK            0x0800U /*!< RSTB driver _ digital command */
//#define FS8X_FS_EXT_RSTB_MASK            0x1000U /*!< Report an External RESET */
//#define FS8X_FS_PGOOD_SNS_MASK           0x2000U /*!< Sense of PGOOD pad */
//#define FS8X_FS_PGOOD_EVENT_MASK         0x4000U /*!< Report a Power GOOD event */
//#define FS8X_FS_PGOOD_DIAG_MASK          0x8000U /*!< Report a PGOOD Short to High */
//
//#define FS8X_FS_GO_TO_INITFS_SHIFT       0x0002U /*!< Go back to INIT Fail Safe request */
//#define FS8X_FS_FS0B_REQ_SHIFT           0x0003U /*!< Request assertion of FS0B */
//#define FS8X_FS_FS0B_DIAG_SHIFT          0x0004U /*!< Report a Failure on FS0B */
//#define FS8X_FS_FS0B_SNS_SHIFT           0x0005U /*!< Sense of FS0B pad */
//#define FS8X_FS_FS0B_DRV_SHIFT           0x0006U /*!< FS0B driver _ digital command */
//#define FS8X_FS_RSTB_REQ_SHIFT           0x0007U /*!< Request assertion of RSTB (Pulse) */
//#define FS8X_FS_RSTB_DIAG_SHIFT          0x0008U /*!< Report a RSTB Short to High */
//#define FS8X_FS_RSTB_EVENT_SHIFT         0x0009U /*!< Report a RSTB event */
//#define FS8X_FS_RSTB_SNS_SHIFT           0x000AU /*!< Sense of RSTB pad */
//#define FS8X_FS_RSTB_DRV_SHIFT           0x000BU /*!< RSTB driver _ digital command */
//#define FS8X_FS_EXT_RSTB_SHIFT           0x000CU /*!< Report an External RESET */
//#define FS8X_FS_PGOOD_SNS_SHIFT          0x000DU /*!< Sense of PGOOD pad */
//#define FS8X_FS_PGOOD_EVENT_SHIFT        0x000EU /*!< Report a Power GOOD event */
//#define FS8X_FS_PGOOD_DIAG_SHIFT         0x000FU /*!< Report a PGOOD Short to High */
//
//#define FS8X_FS_GO_TO_INITFS_NO_ACTION   (0x0000U << FS8X_FS_GO_TO_INITFS_SHIFT) /*!< No action */
//#define FS8X_FS_GO_TO_INITFS_GO_BACK_TO_INIT_FS (0x0001U << FS8X_FS_GO_TO_INITFS_SHIFT) /*!< Go back to INIT_FS */
//
//#define FS8X_FS_FS0B_REQ_NO_ASSERTION    (0x0000U << FS8X_FS_FS0B_REQ_SHIFT) /*!< No Assertion */
//#define FS8X_FS_FS0B_REQ_FS0B_ASSERTION  (0x0001U << FS8X_FS_FS0B_REQ_SHIFT) /*!< FS0B Assertion */
//
//#define FS8X_FS_FS0B_DIAG_NO_FAILURE     (0x0000U << FS8X_FS_FS0B_DIAG_SHIFT) /*!< No Failure */
//#define FS8X_FS_FS0B_DIAG_SHORT_CIRCUIT_HIGH (0x0001U << FS8X_FS_FS0B_DIAG_SHIFT) /*!< Short Circuit High */
//
//#define FS8X_FS_FS0B_SNS_PAD_SENSED_LOW  (0x0000U << FS8X_FS_FS0B_SNS_SHIFT) /*!< FS0B pad sensed low */
//#define FS8X_FS_FS0B_SNS_PAD_SENSED_HIGH (0x0001U << FS8X_FS_FS0B_SNS_SHIFT) /*!< FS0B pad sensed high */
//
//#define FS8X_FS_FS0B_DRV_COMMAND_SENSED_LOW (0x0000U << FS8X_FS_FS0B_DRV_SHIFT) /*!< FS0B driver command sensed low */
//#define FS8X_FS_FS0B_DRV_COMMAND_SENSED_HIGH (0x0001U << FS8X_FS_FS0B_DRV_SHIFT) /*!< FS0B driver command sensed high */
//
//#define FS8X_FS_RSTB_REQ_NO_ASSERTION    (0x0000U << FS8X_FS_RSTB_REQ_SHIFT) /*!< No Assertion */
//#define FS8X_FS_RSTB_REQ_RSTB_ASSERTION  (0x0001U << FS8X_FS_RSTB_REQ_SHIFT) /*!< RSTB Assertion (Pulse) */
//
//#define FS8X_FS_RSTB_DIAG_NO_FAILURE     (0x0000U << FS8X_FS_RSTB_DIAG_SHIFT) /*!< No Failure */
//#define FS8X_FS_RSTB_DIAG_SHORT_CIRCUIT_HIGH (0x0001U << FS8X_FS_RSTB_DIAG_SHIFT) /*!< Short Circuit High */
//
//#define FS8X_FS_RSTB_EVENT_NO_RESET      (0x0000U << FS8X_FS_RSTB_EVENT_SHIFT) /*!< No RESET */
//#define FS8X_FS_RSTB_EVENT_RESET_OCCURRED (0x0001U << FS8X_FS_RSTB_EVENT_SHIFT) /*!< RESET occurred */
//
//#define FS8X_FS_RSTB_SNS_PAD_SENSED_LOW  (0x0000U << FS8X_FS_RSTB_SNS_SHIFT) /*!< RSTB pad sensed low */
//#define FS8X_FS_RSTB_SNS_PAD_SENSED_HIGH (0x0001U << FS8X_FS_RSTB_SNS_SHIFT) /*!< RSTB pad sensed high */
//
//#define FS8X_FS_RSTB_DRV_COMMAND_SENSED_LOW (0x0000U << FS8X_FS_RSTB_DRV_SHIFT) /*!< RSTB driver command sensed low */
//#define FS8X_FS_RSTB_DRV_COMMAND_SENSED_HIGH (0x0001U << FS8X_FS_RSTB_DRV_SHIFT) /*!< RSTB driver command sensed high */
//
//#define FS8X_FS_EXT_RSTB_NO_EXTERNAL_RESET (0x0000U << FS8X_FS_EXT_RSTB_SHIFT) /*!< No External RESET */
//#define FS8X_FS_EXT_RSTB_EXTERNAL_RESET  (0x0001U << FS8X_FS_EXT_RSTB_SHIFT) /*!< External RESET */
//
//#define FS8X_FS_PGOOD_SNS_PAD_SENSED_LOW (0x0000U << FS8X_FS_PGOOD_SNS_SHIFT) /*!< PGOOD pad sensed low */
//#define FS8X_FS_PGOOD_SNS_PAD_SENSED_HIGH (0x0001U << FS8X_FS_PGOOD_SNS_SHIFT) /*!< PGOOD pad sensed high */
//
//#define FS8X_FS_PGOOD_EVENT_NO_POWER_GOOD (0x0000U << FS8X_FS_PGOOD_EVENT_SHIFT) /*!< No Power GOOD */
//#define FS8X_FS_PGOOD_EVENT_POWER_GOOD_EVENT_OCCURRED (0x0001U << FS8X_FS_PGOOD_EVENT_SHIFT) /*!< Power Good event occurred */
//
//#define FS8X_FS_PGOOD_DIAG_NO_FAILURE    (0x0000U << FS8X_FS_PGOOD_DIAG_SHIFT) /*!< No Failure */
//#define FS8X_FS_PGOOD_DIAG_SHORT_CIRCUIT_HIGH (0x0001U << FS8X_FS_PGOOD_DIAG_SHIFT) /*!< Short-Circuit HIGH */
//
///******************************************************************************/
///* FS_DIAG_SAFETY - Type: RW                                                  */
///******************************************************************************/

#define FS8X_FS_DIAG_SAFETY_ADDR         0x14U
#define FS8X_FS_DIAG_SAFETY_DEFAULT      0x0000U

#define FS8X_FS_LBIST_OK_MASK            0x0001U /*!< Diagnostic of Logical BIST */
#define FS8X_FS_I2C_FS_REQ_MASK          0x0002U /*!< Invalid Fail Safe I2C access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address) */
#define FS8X_FS_I2C_FS_CRC_MASK          0x0004U /*!< Fail Safe I2C communication CRC issue */
#define FS8X_FS_SPI_FS_CRC_MASK          0x0008U /*!< Fail Safe SPI communication CRC issue */
#define FS8X_FS_SPI_FS_REQ_MASK          0x0010U /*!< Invalid Fail Safe SPI access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address) */
#define FS8X_FS_SPI_FS_CLK_MASK          0x0020U /*!< Fail Safe SPI SCLK error detection */
#define FS8X_FS_ABIST2_OK_MASK           0x0040U /*!< Diagnostic of Analog BIST2 */
#define FS8X_FS_ABIST1_OK_MASK           0x0080U /*!< Diagnostic of Analog BIST1 */
#define FS8X_FS_BAD_WD_TIMING_MASK       0x0100U /*!< WD refresh status - Timing */
#define FS8X_FS_BAD_WD_DATA_MASK         0x0200U /*!< WD Refresh status - Data */
#define FS8X_FS_ERRMON_STATUS_MASK       0x0400U /*!< Report ERRMON pin level */
#define FS8X_FS_ERRMON_MASK              0x0800U /*!< Report an error in the ERRMON input */
#define FS8X_FS_ERRMON_ACK_MASK          0x1000U /*!< Acknowledge ERRMON failure detection from MCU */
#define FS8X_FS_FCCU2_MASK               0x2000U /*!< Report an error in the FCCU2 input */
#define FS8X_FS_FCCU1_MASK               0x4000U /*!< Report an error in the FCCU1 input */
#define FS8X_FS_FCCU12_MASK              0x8000U /*!< Report an error in the FCCU12 input */

#define FS8X_FS_LBIST_OK_SHIFT           0x0000U /*!< Diagnostic of Logical BIST */
#define FS8X_FS_I2C_FS_REQ_SHIFT         0x0001U /*!< Invalid Fail Safe I2C access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address) */
#define FS8X_FS_I2C_FS_CRC_SHIFT         0x0002U /*!< Fail Safe I2C communication CRC issue */
#define FS8X_FS_SPI_FS_CRC_SHIFT         0x0003U /*!< Fail Safe SPI communication CRC issue */
#define FS8X_FS_SPI_FS_REQ_SHIFT         0x0004U /*!< Invalid Fail Safe SPI access (Wrong Write or Read, Write to INIT registers in normal mode, wrong address) */
#define FS8X_FS_SPI_FS_CLK_SHIFT         0x0005U /*!< Fail Safe SPI SCLK error detection */
#define FS8X_FS_ABIST2_OK_SHIFT          0x0006U /*!< Diagnostic of Analog BIST2 */
#define FS8X_FS_ABIST1_OK_SHIFT          0x0007U /*!< Diagnostic of Analog BIST1 */
#define FS8X_FS_BAD_WD_TIMING_SHIFT      0x0008U /*!< WD refresh status - Timing */
#define FS8X_FS_BAD_WD_DATA_SHIFT        0x0009U /*!< WD Refresh status - Data */
#define FS8X_FS_ERRMON_STATUS_SHIFT      0x000AU /*!< Report ERRMON pin level */
#define FS8X_FS_ERRMON_SHIFT             0x000BU /*!< Report an error in the ERRMON input */
#define FS8X_FS_ERRMON_ACK_SHIFT         0x000CU /*!< Acknowledge ERRMON failure detection from MCU */
#define FS8X_FS_FCCU2_SHIFT              0x000DU /*!< Report an error in the FCCU2 input */
#define FS8X_FS_FCCU1_SHIFT              0x000EU /*!< Report an error in the FCCU1 input */
#define FS8X_FS_FCCU12_SHIFT             0x000FU /*!< Report an error in the FCCU12 input */

#define FS8X_FS_LBIST_OK_FAIL            (0x0000U << FS8X_FS_LBIST_OK_SHIFT) /*!< LBIST FAIL */
#define FS8X_FS_LBIST_OK_PASS            (0x0001U << FS8X_FS_LBIST_OK_SHIFT) /*!< LBIST PASS */

#define FS8X_FS_I2C_FS_REQ_NO_ERROR      (0x0000U << FS8X_FS_I2C_FS_REQ_SHIFT) /*!< No error */
#define FS8X_FS_I2C_FS_REQ_I2C_VIOLATION (0x0001U << FS8X_FS_I2C_FS_REQ_SHIFT) /*!< I2c Violation */

#define FS8X_FS_I2C_FS_CRC_NO_ERROR      (0x0000U << FS8X_FS_I2C_FS_CRC_SHIFT) /*!< No error */
#define FS8X_FS_I2C_FS_CRC_ERROR_DETECTED (0x0001U << FS8X_FS_I2C_FS_CRC_SHIFT) /*!< Error detected in the CRC */

#define FS8X_FS_SPI_FS_CRC_NO_ERROR      (0x0000U << FS8X_FS_SPI_FS_CRC_SHIFT) /*!< No error */
#define FS8X_FS_SPI_FS_CRC_ERROR_DETECTED (0x0001U << FS8X_FS_SPI_FS_CRC_SHIFT) /*!< Error detected in the CRC */

#define FS8X_FS_SPI_FS_REQ_NO_ERROR      (0x0000U << FS8X_FS_SPI_FS_REQ_SHIFT) /*!< No error */
#define FS8X_FS_SPI_FS_REQ_SPI_VIOLATION (0x0001U << FS8X_FS_SPI_FS_REQ_SHIFT) /*!< SPI Violation */

#define FS8X_FS_SPI_FS_CLK_NO_ERROR      (0x0000U << FS8X_FS_SPI_FS_CLK_SHIFT) /*!< No error */
#define FS8X_FS_SPI_FS_CLK_WRONG_NUMBER_OF_CLOCK_CYCLES (0x0001U << FS8X_FS_SPI_FS_CLK_SHIFT) /*!< Wrong number of clock cycles <32 or >32) */

#define FS8X_FS_ABIST2_OK_ABIST2_FAIL    (0x0000U << FS8X_FS_ABIST2_OK_SHIFT) /*!< ABIST2 FAIL or NOT EXECUTED */
#define FS8X_FS_ABIST2_OK_PASS           (0x0001U << FS8X_FS_ABIST2_OK_SHIFT) /*!< PASS */

#define FS8X_FS_ABIST1_OK_ABIST1_FAIL    (0x0000U << FS8X_FS_ABIST1_OK_SHIFT) /*!< ABIST1 FAIL or NOT EXECUTED */
#define FS8X_FS_ABIST1_OK_PASS           (0x0001U << FS8X_FS_ABIST1_OK_SHIFT) /*!< PASS */

#define FS8X_FS_BAD_WD_TIMING_GOOD_WD_REFRESH (0x0000U << FS8X_FS_BAD_WD_TIMING_SHIFT) /*!< Good WD Refresh */
#define FS8X_FS_BAD_WD_TIMING_BAD_WD_REFRESH (0x0001U << FS8X_FS_BAD_WD_TIMING_SHIFT) /*!< Bad WD refresh, wrong window or in timeout */

#define FS8X_FS_BAD_WD_DATA_GOOD_WD_REFRESH (0x0000U << FS8X_FS_BAD_WD_DATA_SHIFT) /*!< Good WD Refresh */
#define FS8X_FS_BAD_WD_DATA_BAD_WD_REFRESH (0x0001U << FS8X_FS_BAD_WD_DATA_SHIFT) /*!< Bad WD refresh, error in the DATA */

#define FS8X_FS_ERRMON_STATUS_LOW_LEVEL  (0x0000U << FS8X_FS_ERRMON_STATUS_SHIFT) /*!< LOW Level */
#define FS8X_FS_ERRMON_STATUS_HIGH_LEVEL (0x0001U << FS8X_FS_ERRMON_STATUS_SHIFT) /*!< HIGH Level */

#define FS8X_FS_ERRMON_NO_ERROR          (0x0000U << FS8X_FS_ERRMON_SHIFT) /*!< No error */
#define FS8X_FS_ERRMON_ERROR_DETECTED    (0x0001U << FS8X_FS_ERRMON_SHIFT) /*!< Error detected */

#define FS8X_FS_ERRMON_ACK_NO_EFFECT     (0x0000U << FS8X_FS_ERRMON_ACK_SHIFT) /*!< No effect */
#define FS8X_FS_ERRMON_ACK_FAILURE_DETECTION (0x0001U << FS8X_FS_ERRMON_ACK_SHIFT) /*!< Acknowledge ERRMON failure detection */

#define FS8X_FS_FCCU2_NO_ERROR           (0x0000U << FS8X_FS_FCCU2_SHIFT) /*!< No error */
#define FS8X_FS_FCCU2_ERROR_DETECTED     (0x0001U << FS8X_FS_FCCU2_SHIFT) /*!< Error detected */

#define FS8X_FS_FCCU1_NO_ERROR           (0x0000U << FS8X_FS_FCCU1_SHIFT) /*!< No error */
#define FS8X_FS_FCCU1_ERROR_DETECTED     (0x0001U << FS8X_FS_FCCU1_SHIFT) /*!< Error detected */

#define FS8X_FS_FCCU12_NO_ERROR          (0x0000U << FS8X_FS_FCCU12_SHIFT) /*!< No error */
#define FS8X_FS_FCCU12_ERROR_DETECTED    (0x0001U << FS8X_FS_FCCU12_SHIFT) /*!< Error detected */

///******************************************************************************/
///* FS_INTB_MASK - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_INTB_MASK_ADDR           0x15U
//#define FS8X_FS_INTB_MASK_DEFAULT        0x0000U
//
//#define FS8X_FS_INT_INH_FCCU1_MASK       0x0001U /*!< Inhibit INTERRUPT on FCCU1 event */
//#define FS8X_FS_INT_INH_FCCU2_MASK       0x0002U /*!< Inhibit INTERRUPT on FCCU2 event */
//#define FS8X_FS_INT_INH_ERRMON_MASK      0x0004U /*!< Inhibit INTERRUPT on ERRMON event */
//#define FS8X_FS_INT_INH_BAD_WD_REFRESH_MASK 0x0008U /*!< Inhibit INTERRUPT on bad WD refresh event */
//#define FS8X_FS_INT_INH_VCOREMON_OV_UV_MASK 0x0010U /*!< Inhibit INTERRUPT on VCOREMON OV and UV event */
//#define FS8X_FS_INT_INH_VDDIO_OV_UV_MASK 0x0020U /*!< Inhibit INTERRUPT on VDDIO OV and UV event */
//#define FS8X_FS_INT_INH_VMON1_OV_UV_MASK 0x0040U /*!< Inhibit INTERRUPT on VMON1 OV and UV event */
//#define FS8X_FS_INT_INH_VMON2_OV_UV_MASK 0x0080U /*!< Inhibit INTERRUPT on VMON2 OV and UV event */
//#define FS8X_FS_INT_INH_VMON3_OV_UV_MASK 0x0100U /*!< Inhibit INTERRUPT on VMON3 OV and UV event */
//#define FS8X_FS_INT_INH_VMON4_OV_UV_MASK 0x0200U /*!< Inhibit INTERRUPT on VMON4 OV and UV event */
//
//#define FS8X_FS_INT_INH_FCCU1_SHIFT      0x0000U /*!< Inhibit INTERRUPT on FCCU1 event */
//#define FS8X_FS_INT_INH_FCCU2_SHIFT      0x0001U /*!< Inhibit INTERRUPT on FCCU2 event */
//#define FS8X_FS_INT_INH_ERRMON_SHIFT     0x0002U /*!< Inhibit INTERRUPT on ERRMON event */
//#define FS8X_FS_INT_INH_BAD_WD_REFRESH_SHIFT 0x0003U /*!< Inhibit INTERRUPT on bad WD refresh event */
//#define FS8X_FS_INT_INH_VCOREMON_OV_UV_SHIFT 0x0004U /*!< Inhibit INTERRUPT on VCOREMON OV and UV event */
//#define FS8X_FS_INT_INH_VDDIO_OV_UV_SHIFT 0x0005U /*!< Inhibit INTERRUPT on VDDIO OV and UV event */
//#define FS8X_FS_INT_INH_VMON1_OV_UV_SHIFT 0x0006U /*!< Inhibit INTERRUPT on VMON1 OV and UV event */
//#define FS8X_FS_INT_INH_VMON2_OV_UV_SHIFT 0x0007U /*!< Inhibit INTERRUPT on VMON2 OV and UV event */
//#define FS8X_FS_INT_INH_VMON3_OV_UV_SHIFT 0x0008U /*!< Inhibit INTERRUPT on VMON3 OV and UV event */
//#define FS8X_FS_INT_INH_VMON4_OV_UV_SHIFT 0x0009U /*!< Inhibit INTERRUPT on VMON4 OV and UV event */
//
//#define FS8X_FS_INT_INH_FCCU1_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_FCCU1_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_FCCU1_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_FCCU1_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_FCCU2_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_FCCU2_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_FCCU2_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_FCCU2_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_ERRMON_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_ERRMON_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_ERRMON_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_ERRMON_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_BAD_WD_REFRESH_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_BAD_WD_REFRESH_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_BAD_WD_REFRESH_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_BAD_WD_REFRESH_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VCOREMON_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VCOREMON_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VCOREMON_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VCOREMON_OV_UV_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VDDIO_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VDDIO_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VDDIO_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VDDIO_OV_UV_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VMON1_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VMON1_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VMON1_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VMON1_OV_UV_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VMON2_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VMON2_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VMON2_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VMON2_OV_UV_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VMON3_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VMON3_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VMON3_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VMON3_OV_UV_SHIFT) /*!< Interruption MASKED */
//
//#define FS8X_FS_INT_INH_VMON4_OV_UV_INTERRUPTION_NOT_MASKED (0x0000U << FS8X_FS_INT_INH_VMON4_OV_UV_SHIFT) /*!< Interruption NOT MASKED */
//#define FS8X_FS_INT_INH_VMON4_OV_UV_INTERRUPTION_MASKED (0x0001U << FS8X_FS_INT_INH_VMON4_OV_UV_SHIFT) /*!< Interruption MASKED */
//
/******************************************************************************/
/* FS_STATES - Type: RW                                                       */
/******************************************************************************/

#define FS8X_FS_STATES_ADDR              0x16U
#define FS8X_FS_STATES_DEFAULT           0x0000U
//
//#define FS8X_FS_FSM_STATE_MASK           0x001FU /*!< Report Fail-safe state machine current state */
//#define FS8X_FS_REG_CORRUPT_MASK         0x0200U /*!< INIT register corruption detection (5ms cyclic check) */
//#define FS8X_FS_OTP_CORRUPT_MASK         0x0800U /*!< OTP bits corruption detection (5ms cyclic check) */
//#define FS8X_FS_DBG_MODE_MASK            0x2000U /*!< DEBUG mode status */
//#define FS8X_FS_DBG_EXIT_MASK            0x4000U /*!< Leave DEBUG mode */
//#define FS8X_FS_TM_ACTIVE_MASK           0x8000U /*!< Test Mode Activation Status */
//
//#define FS8X_FS_FSM_STATE_SHIFT          0x0000U /*!< Report Fail-safe state machine current state */
//#define FS8X_FS_REG_CORRUPT_SHIFT        0x0009U /*!< INIT register corruption detection (5ms cyclic check) */
//#define FS8X_FS_OTP_CORRUPT_SHIFT        0x000BU /*!< OTP bits corruption detection (5ms cyclic check) */
//#define FS8X_FS_DBG_MODE_SHIFT           0x000DU /*!< DEBUG mode status */
//#define FS8X_FS_DBG_EXIT_SHIFT           0x000EU /*!< Leave DEBUG mode */
//#define FS8X_FS_TM_ACTIVE_SHIFT          0x000FU /*!< Test Mode Activation Status */
//
//#define FS8X_FS_FSM_STATE_INIT_FS        (0x0006U << FS8X_FS_FSM_STATE_SHIFT) /*!< INIT_FS */
//#define FS8X_FS_FSM_STATE_WAIT_ABIST2    (0x0007U << FS8X_FS_FSM_STATE_SHIFT) /*!< WAIT_ABIST2 */
//#define FS8X_FS_FSM_STATE_ABIST2         (0x0008U << FS8X_FS_FSM_STATE_SHIFT) /*!< ABIST2 */
//#define FS8X_FS_FSM_STATE_ASSERT_FS0B    (0x0009U << FS8X_FS_FSM_STATE_SHIFT) /*!< ASSERT_FS0B */
//#define FS8X_FS_FSM_STATE_NORMAL_FS      (0x000AU << FS8X_FS_FSM_STATE_SHIFT) /*!< NORMAL_FS */
//
//#define FS8X_FS_REG_CORRUPT_NO_ERROR     (0x0000U << FS8X_FS_REG_CORRUPT_SHIFT) /*!< No error */
//#define FS8X_FS_REG_CORRUPT_ERROR        (0x0001U << FS8X_FS_REG_CORRUPT_SHIFT) /*!< INIT register content error detected(mismatch between FS_I_Register / FS_I_NOT_Register) */
//
//#define FS8X_FS_OTP_CORRUPT_NO_ERROR     (0x0000U << FS8X_FS_OTP_CORRUPT_SHIFT) /*!< No error */
//#define FS8X_FS_OTP_CORRUPT_ERROR        (0x0001U << FS8X_FS_OTP_CORRUPT_SHIFT) /*!< OTP CRC error detected */
//
//#define FS8X_FS_DBG_MODE_NO_DEBUG        (0x0000U << FS8X_FS_DBG_MODE_SHIFT) /*!< NOT in DEBUG mode */
//#define FS8X_FS_DBG_MODE_DEBUG           (0x0001U << FS8X_FS_DBG_MODE_SHIFT) /*!< In DEBUG mode */
//
//#define FS8X_FS_DBG_EXIT_NO_ACTION       (0x0000U << FS8X_FS_DBG_EXIT_SHIFT) /*!< No Action */
//#define FS8X_FS_DBG_EXIT_LEAVE_DEBUG_MODE (0x0001U << FS8X_FS_DBG_EXIT_SHIFT) /*!< Leave DEBUG mode */
//
//#define FS8X_FS_TM_ACTIVE_NOT_ACTIVE     (0x0000U << FS8X_FS_TM_ACTIVE_SHIFT) /*!< Test mode is not activated */
//#define FS8X_FS_TM_ACTIVE_ACTIVE         (0x0001U << FS8X_FS_TM_ACTIVE_SHIFT) /*!< Test mode is activated */
//
///******************************************************************************/
///* FS_I_OVUV_SAFE_REACTION1 - Type: RW                                        */
///******************************************************************************/
//
//#define FS8X_FS_I_OVUV_SAFE_REACTION1_ADDR 0x01U
//#define FS8X_FS_I_OVUV_SAFE_REACTION1_DEFAULT 0xD00DU
//
//#define FS8X_FS_I_VDDIO_UV_FS_IMPACT_MASK 0x0003U /*!< VDDIO UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VDDIO_OV_FS_IMPACT_MASK 0x000CU /*!< VDDIO OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_ABIST2_MASK      0x0020U /*!< VMON4 ABIST2 configuration */
//#define FS8X_FS_I_VMON3_ABIST2_MASK      0x0040U /*!< VMON3 ABIST2 configuration */
//#define FS8X_FS_I_VMON2_ABIST2_MASK      0x0080U /*!< VMON2 ABIST2 configuration */
//#define FS8X_FS_I_VMON1_ABIST2_MASK      0x0100U /*!< VMON1 ABIST2 configuration */
//#define FS8X_FS_I_VDDIO_ABIST2_MASK      0x0200U /*!< VDDIO ABIST2 configuration */
//#define FS8X_FS_I_VCOREMON_ABIST2_MASK   0x0400U /*!< VCOREMON ABIST2 configuration */
//#define FS8X_FS_I_VCOREMON_UV_FS_IMPACT_MASK 0x3000U /*!< VCOREMON UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VCOREMON_OV_FS_IMPACT_MASK 0xC000U /*!< VCOREMON OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_VDDIO_UV_FS_IMPACT_SHIFT 0x0000U /*!< VDDIO UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VDDIO_OV_FS_IMPACT_SHIFT 0x0002U /*!< VDDIO OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_ABIST2_SHIFT     0x0005U /*!< VMON4 ABIST2 configuration */
//#define FS8X_FS_I_VMON3_ABIST2_SHIFT     0x0006U /*!< VMON3 ABIST2 configuration */
//#define FS8X_FS_I_VMON2_ABIST2_SHIFT     0x0007U /*!< VMON2 ABIST2 configuration */
//#define FS8X_FS_I_VMON1_ABIST2_SHIFT     0x0008U /*!< VMON1 ABIST2 configuration */
//#define FS8X_FS_I_VDDIO_ABIST2_SHIFT     0x0009U /*!< VDDIO ABIST2 configuration */
//#define FS8X_FS_I_VCOREMON_ABIST2_SHIFT  0x000AU /*!< VCOREMON ABIST2 configuration */
//#define FS8X_FS_I_VCOREMON_UV_FS_IMPACT_SHIFT 0x000CU /*!< VCOREMON UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VCOREMON_OV_FS_IMPACT_SHIFT 0x000EU /*!< VCOREMON OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_VDDIO_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VDDIO_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VDDIO_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VDDIO_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VDDIO_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VDDIO_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VDDIO_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VDDIO_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VDDIO_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VDDIO_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VDDIO_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VDDIO_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON4_ABIST2_NO_ABIST  (0x0000U << FS8X_FS_I_VMON4_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VMON4_ABIST2_VMON4_BIST (0x0001U << FS8X_FS_I_VMON4_ABIST2_SHIFT) /*!< VMON4 BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VMON3_ABIST2_NO_ABIST  (0x0000U << FS8X_FS_I_VMON3_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VMON3_ABIST2_VMON3_BIST (0x0001U << FS8X_FS_I_VMON3_ABIST2_SHIFT) /*!< VMON3 BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VMON2_ABIST2_NO_ABIST  (0x0000U << FS8X_FS_I_VMON2_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VMON2_ABIST2_VMON2_BIST (0x0001U << FS8X_FS_I_VMON2_ABIST2_SHIFT) /*!< VMON2 BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VMON1_ABIST2_NO_ABIST  (0x0000U << FS8X_FS_I_VMON1_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VMON1_ABIST2_VMON1_BIST (0x0001U << FS8X_FS_I_VMON1_ABIST2_SHIFT) /*!< VMON1 BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VDDIO_ABIST2_NO_ABIST  (0x0000U << FS8X_FS_I_VDDIO_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VDDIO_ABIST2_VDDIO_BIST (0x0001U << FS8X_FS_I_VDDIO_ABIST2_SHIFT) /*!< VDDIO BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VCOREMON_ABIST2_NO_ABIST (0x0000U << FS8X_FS_I_VCOREMON_ABIST2_SHIFT) /*!< No ABIST */
//#define FS8X_FS_I_VCOREMON_ABIST2_VCOREMON_BIST (0x0001U << FS8X_FS_I_VCOREMON_ABIST2_SHIFT) /*!< VCOREMON BIST executed during ABIST2 */
//
//#define FS8X_FS_I_VCOREMON_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VCOREMON_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VCOREMON_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VCOREMON_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VCOREMON_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VCOREMON_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VCOREMON_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VCOREMON_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VCOREMON_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VCOREMON_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VCOREMON_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VCOREMON_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
///******************************************************************************/
///* FS_I_NOT_OVUV_SAFE_REACTION1 - Type: RW                                    */
///******************************************************************************/
//
//#define FS8X_FS_I_NOT_OVUV_SAFE_REACTION1_ADDR 0x02U
//#define FS8X_FS_I_NOT_OVUV_SAFE_REACTION1_DEFAULT 0x2FF2U
//
//#define FS8X_FS_I_NOT_VDDIO_UV_FS_IMPACT_MASK 0x0003U /*!< VDDIO UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VDDIO_OV_FS_IMPACT_MASK 0x000CU /*!< VDDIO OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_ABIST2_MASK  0x0020U /*!< VMON4 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON3_ABIST2_MASK  0x0040U /*!< VMON3 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON2_ABIST2_MASK  0x0080U /*!< VMON2 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON1_ABIST2_MASK  0x0100U /*!< VMON1 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VDDIO_ABIST2_MASK  0x0200U /*!< VDDIO ABIST2 configuration */
//#define FS8X_FS_I_NOT_VCOREMON_ABIST2_MASK 0x0400U /*!< VCOREMON ABIST2 configuration */
//#define FS8X_FS_I_NOT_VCOREMON_UV_FS_IMPACT_MASK 0x3000U /*!< VCOREMON UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VCOREMON_OV_FS_IMPACT_MASK 0xC000U /*!< VCOREMON OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_NOT_VDDIO_UV_FS_IMPACT_SHIFT 0x0000U /*!< VDDIO UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VDDIO_OV_FS_IMPACT_SHIFT 0x0002U /*!< VDDIO OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_ABIST2_SHIFT 0x0005U /*!< VMON4 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON3_ABIST2_SHIFT 0x0006U /*!< VMON3 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON2_ABIST2_SHIFT 0x0007U /*!< VMON2 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VMON1_ABIST2_SHIFT 0x0008U /*!< VMON1 ABIST2 configuration */
//#define FS8X_FS_I_NOT_VDDIO_ABIST2_SHIFT 0x0009U /*!< VDDIO ABIST2 configuration */
//#define FS8X_FS_I_NOT_VCOREMON_ABIST2_SHIFT 0x000AU /*!< VCOREMON ABIST2 configuration */
//#define FS8X_FS_I_NOT_VCOREMON_UV_FS_IMPACT_SHIFT 0x000CU /*!< VCOREMON UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VCOREMON_OV_FS_IMPACT_SHIFT 0x000EU /*!< VCOREMON OV impact on RSTB/FS0B */
//
///******************************************************************************/
///* FS_I_OVUV_SAFE_REACTION2 - Type: RW                                        */
///******************************************************************************/
//
//#define FS8X_FS_I_OVUV_SAFE_REACTION2_ADDR 0x03U
//#define FS8X_FS_I_OVUV_SAFE_REACTION2_DEFAULT 0xDDDDU
//
//#define FS8X_FS_I_VMON1_UV_FS_IMPACT_MASK 0x0003U /*!< VMON1 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON1_OV_FS_IMPACT_MASK 0x000CU /*!< VMON1 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON2_UV_FS_IMPACT_MASK 0x0030U /*!< VMON2 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON2_OV_FS_IMPACT_MASK 0x00C0U /*!< VMON2 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON3_UV_FS_IMPACT_MASK 0x0300U /*!< VMON3 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON3_OV_FS_IMPACT_MASK 0x0C00U /*!< VMON3 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_UV_FS_IMPACT_MASK 0x3000U /*!< VMON4 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_OV_FS_IMPACT_MASK 0xC000U /*!< VMON4 OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_VMON1_UV_FS_IMPACT_SHIFT 0x0000U /*!< VMON1 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON1_OV_FS_IMPACT_SHIFT 0x0002U /*!< VMON1 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON2_UV_FS_IMPACT_SHIFT 0x0004U /*!< VMON2 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON2_OV_FS_IMPACT_SHIFT 0x0006U /*!< VMON2 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON3_UV_FS_IMPACT_SHIFT 0x0008U /*!< VMON3 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON3_OV_FS_IMPACT_SHIFT 0x000AU /*!< VMON3 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_UV_FS_IMPACT_SHIFT 0x000CU /*!< VMON4 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_VMON4_OV_FS_IMPACT_SHIFT 0x000EU /*!< VMON4 OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_VMON1_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON1_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON1_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON1_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON1_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON1_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON1_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON1_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON1_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON1_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON1_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON1_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON2_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON2_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON2_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON2_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON2_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON2_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON2_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON2_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON2_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON2_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON2_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON2_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON3_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON3_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON3_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON3_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON3_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON3_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON3_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON3_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON3_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON3_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON3_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON3_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON4_UV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON4_UV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON4_UV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON4_UV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON4_UV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON4_UV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_VMON4_OV_FS_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_VMON4_OV_FS_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
//#define FS8X_FS_I_VMON4_OV_FS_IMPACT_FS0B (0x0001U << FS8X_FS_I_VMON4_OV_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_VMON4_OV_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_VMON4_OV_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
///******************************************************************************/
///* FS_I_NOT_OVUV_SAFE_REACTION2 - Type: RW                                    */
///******************************************************************************/
//
//#define FS8X_FS_I_NOT_OVUV_SAFE_REACTION2_ADDR 0x04U
//#define FS8X_FS_I_NOT_OVUV_SAFE_REACTION2_DEFAULT 0x2222U
//
//#define FS8X_FS_I_NOT_VMON1_UV_FS_IMPACT_MASK 0x0003U /*!< VMON1 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON1_OV_FS_IMPACT_MASK 0x000CU /*!< VMON1 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON2_UV_FS_IMPACT_MASK 0x0030U /*!< VMON2 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON2_OV_FS_IMPACT_MASK 0x00C0U /*!< VMON2 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON3_UV_FS_IMPACT_MASK 0x0300U /*!< VMON3 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON3_OV_FS_IMPACT_MASK 0x0C00U /*!< VMON3 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_UV_FS_IMPACT_MASK 0x3000U /*!< VMON4 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_OV_FS_IMPACT_MASK 0xC000U /*!< VMON4 OV impact on RSTB/FS0B */
//
//#define FS8X_FS_I_NOT_VMON1_UV_FS_IMPACT_SHIFT 0x0000U /*!< VMON1 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON1_OV_FS_IMPACT_SHIFT 0x0002U /*!< VMON1 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON2_UV_FS_IMPACT_SHIFT 0x0004U /*!< VMON2 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON2_OV_FS_IMPACT_SHIFT 0x0006U /*!< VMON2 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON3_UV_FS_IMPACT_SHIFT 0x0008U /*!< VMON3 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON3_OV_FS_IMPACT_SHIFT 0x000AU /*!< VMON3 OV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_UV_FS_IMPACT_SHIFT 0x000CU /*!< VMON4 UV impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_VMON4_OV_FS_IMPACT_SHIFT 0x000EU /*!< VMON4 OV impact on RSTB/FS0B */
//
///******************************************************************************/
///* FS_I_WD_CFG - Type: RW                                                     */
///******************************************************************************/

#define FS8X_FS_I_WD_CFG_ADDR            0x05U
#define FS8X_FS_I_WD_CFG_DEFAULT         0x4200U

#define FS8X_FS_I_WD_ERR_CNT_MASK        0x000FU /*!< Reflect the value of the Watchdog Error Counter. */
#define FS8X_FS_I_WD_RFR_CNT_MASK        0x0070U /*!< Reflect the value of the Watchdog Refresh Counter */
#define FS8X_FS_I_WD_FS_IMPACT_MASK      0x0300U /*!< Watchdog Error Impact on RSTB/FS0B */
#define FS8X_FS_I_WD_RFR_LIMIT_MASK      0x1800U /*!< Watchdog Refresh Counter value */
#define FS8X_FS_I_WD_ERR_LIMIT_MASK      0xC000U /*!< Watchdog Error Counter value */

#define FS8X_FS_I_WD_ERR_CNT_SHIFT       0x0000U /*!< Reflect the value of the Watchdog Error Counter. */
#define FS8X_FS_I_WD_RFR_CNT_SHIFT       0x0004U /*!< Reflect the value of the Watchdog Refresh Counter */
#define FS8X_FS_I_WD_FS_IMPACT_SHIFT     0x0008U /*!< Watchdog Error Impact on RSTB/FS0B */
#define FS8X_FS_I_WD_RFR_LIMIT_SHIFT     0x000BU /*!< Watchdog Refresh Counter value */
#define FS8X_FS_I_WD_ERR_LIMIT_SHIFT     0x000EU /*!< Watchdog Error Counter value */

#define FS8X_FS_I_WD_ERR_CNT_0           (0x0000U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 0 */
#define FS8X_FS_I_WD_ERR_CNT_1           (0x0001U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 1 */
#define FS8X_FS_I_WD_ERR_CNT_2           (0x0002U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 2 */
#define FS8X_FS_I_WD_ERR_CNT_3           (0x0003U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 3 */
#define FS8X_FS_I_WD_ERR_CNT_4           (0x0004U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 4 */
#define FS8X_FS_I_WD_ERR_CNT_5           (0x0005U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 5 */
#define FS8X_FS_I_WD_ERR_CNT_6           (0x0006U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 6 */
#define FS8X_FS_I_WD_ERR_CNT_7           (0x0007U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 7 */
#define FS8X_FS_I_WD_ERR_CNT_8           (0x0008U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 8 */
#define FS8X_FS_I_WD_ERR_CNT_9           (0x0009U << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 9 */
#define FS8X_FS_I_WD_ERR_CNT_10          (0x000AU << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 10 */
#define FS8X_FS_I_WD_ERR_CNT_11          (0x000BU << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 11 */
#define FS8X_FS_I_WD_ERR_CNT_12          (0x000CU << FS8X_FS_I_WD_ERR_CNT_SHIFT) /*!< 12 */

#define FS8X_FS_I_WD_RFR_CNT_0           (0x0000U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 0 */
#define FS8X_FS_I_WD_RFR_CNT_1           (0x0001U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 1 */
#define FS8X_FS_I_WD_RFR_CNT_2           (0x0002U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 2 */
#define FS8X_FS_I_WD_RFR_CNT_3           (0x0003U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 3 */
#define FS8X_FS_I_WD_RFR_CNT_4           (0x0004U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 4 */
#define FS8X_FS_I_WD_RFR_CNT_5           (0x0005U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 5 */
#define FS8X_FS_I_WD_RFR_CNT_6           (0x0006U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 6 */
#define FS8X_FS_I_WD_RFR_CNT_7           (0x0007U << FS8X_FS_I_WD_RFR_CNT_SHIFT) /*!< 7 */

#define FS8X_FS_I_WD_FS_IMPACT_NO_ACTION (0x0000U << FS8X_FS_I_WD_FS_IMPACT_SHIFT) /*!< No action on RSTB and FS0B */
#define FS8X_FS_I_WD_FS_IMPACT_FS0B      (0x0001U << FS8X_FS_I_WD_FS_IMPACT_SHIFT) /*!< FS0B only is asserted if WD error counter = WD_ERR_LIMIT[1:0] */
#define FS8X_FS_I_WD_FS_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_WD_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted if WD error counter = WD_ERR_LIMIT[1:0] */

#define FS8X_FS_I_WD_RFR_LIMIT_6         (0x0000U << FS8X_FS_I_WD_RFR_LIMIT_SHIFT) /*!< 6 */
#define FS8X_FS_I_WD_RFR_LIMIT_4         (0x0001U << FS8X_FS_I_WD_RFR_LIMIT_SHIFT) /*!< 4 */
#define FS8X_FS_I_WD_RFR_LIMIT_2         (0x0002U << FS8X_FS_I_WD_RFR_LIMIT_SHIFT) /*!< 2 */
#define FS8X_FS_I_WD_RFR_LIMIT_1         (0x0003U << FS8X_FS_I_WD_RFR_LIMIT_SHIFT) /*!< 1 */

#define FS8X_FS_I_WD_ERR_LIMIT_8         (0x0000U << FS8X_FS_I_WD_ERR_LIMIT_SHIFT) /*!< 8 */
#define FS8X_FS_I_WD_ERR_LIMIT_6         (0x0001U << FS8X_FS_I_WD_ERR_LIMIT_SHIFT) /*!< 6 */
#define FS8X_FS_I_WD_ERR_LIMIT_4         (0x0002U << FS8X_FS_I_WD_ERR_LIMIT_SHIFT) /*!< 4 */
#define FS8X_FS_I_WD_ERR_LIMIT_2         (0x0003U << FS8X_FS_I_WD_ERR_LIMIT_SHIFT) /*!< 2 */

///******************************************************************************/
///* FS_I_NOT_WD_CFG - Type: RW                                                 */
///******************************************************************************/

#define FS8X_FS_I_NOT_WD_CFG_ADDR        0x06U
#define FS8X_FS_I_NOT_WD_CFG_DEFAULT     0xBDFFU

#define FS8X_FS_I_NOT_WD_FS_IMPACT_MASK  0x0300U /*!< Watchdog Error Impact on RSTB/FS0B */
#define FS8X_FS_I_NOT_WD_RFR_LIMIT_MASK  0x1800U /*!< Watchdog Refresh Counter value */
#define FS8X_FS_I_NOT_WD_ERR_LIMIT_MASK  0xC000U /*!< Watchdog Error Counter value */

#define FS8X_FS_I_NOT_WD_FS_IMPACT_SHIFT 0x0008U /*!< Watchdog Error Impact on RSTB/FS0B */
#define FS8X_FS_I_NOT_WD_RFR_LIMIT_SHIFT 0x000BU /*!< Watchdog Refresh Counter value */
#define FS8X_FS_I_NOT_WD_ERR_LIMIT_SHIFT 0x000EU /*!< Watchdog Error Counter value */

///******************************************************************************/
///* FS_I_SAFE_INPUTS - Type: RW                                                */
///******************************************************************************/
//
//#define FS8X_FS_I_SAFE_INPUTS_ADDR       0x07U
//#define FS8X_FS_I_SAFE_INPUTS_DEFAULT    0x41C6U
//
//#define FS8X_FS_I_ERRMON_FS_IMPACT_MASK  0x0002U /*!< ERRMON impact on RSTB/FS0B */
//#define FS8X_FS_I_ERRMON_ACK_TIME_MASK   0x000CU /*!< ERRMON acknowledgement timing */
//#define FS8X_FS_I_ERRMON_FLT_POL_MASK    0x0010U /*!< ERRMON polarity */
//#define FS8X_FS_I_FCCU2_FS_IMPACT_MASK   0x0040U /*!< FCCU2 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU1_FS_IMPACT_MASK   0x0080U /*!< FCCU1 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU12_FS_IMPACT_MASK  0x0100U /*!< FCCU12 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU2_FLT_POL_MASK     0x0400U /*!< FCCU2 polarity */
//#define FS8X_FS_I_FCCU1_FLT_POL_MASK     0x0800U /*!< FCCU1 polarity */
//#define FS8X_FS_I_FCCU12_FLT_POL_MASK    0x1000U /*!< FCCU12 polarity */
//#define FS8X_FS_I_FCCU_CFG_MASK          0xC000U /*!< FCCU pins configuration */
//
//#define FS8X_FS_I_ERRMON_FS_IMPACT_SHIFT 0x0001U /*!< ERRMON impact on RSTB/FS0B */
//#define FS8X_FS_I_ERRMON_ACK_TIME_SHIFT  0x0002U /*!< ERRMON acknowledgement timing */
//#define FS8X_FS_I_ERRMON_FLT_POL_SHIFT   0x0004U /*!< ERRMON polarity */
//#define FS8X_FS_I_FCCU2_FS_IMPACT_SHIFT  0x0006U /*!< FCCU2 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU1_FS_IMPACT_SHIFT  0x0007U /*!< FCCU1 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU12_FS_IMPACT_SHIFT 0x0008U /*!< FCCU12 impact on RSTB/FS0B */
//#define FS8X_FS_I_FCCU2_FLT_POL_SHIFT    0x000AU /*!< FCCU2 polarity */
//#define FS8X_FS_I_FCCU1_FLT_POL_SHIFT    0x000BU /*!< FCCU1 polarity */
//#define FS8X_FS_I_FCCU12_FLT_POL_SHIFT   0x000CU /*!< FCCU12 polarity */
//#define FS8X_FS_I_FCCU_CFG_SHIFT         0x000EU /*!< FCCU pins configuration */
//
//#define FS8X_FS_I_ERRMON_FS_IMPACT_FS0B  (0x0000U << FS8X_FS_I_ERRMON_FS_IMPACT_SHIFT) /*!< FS0B only is asserted when ERRMON fault is detected */
//#define FS8X_FS_I_ERRMON_FS_IMPACT_FS0B_RSTB (0x0001U << FS8X_FS_I_ERRMON_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted when ERRMON fault is detected */
//
//#define FS8X_FS_I_ERRMON_ACK_TIME_1MS    (0x0000U << FS8X_FS_I_ERRMON_ACK_TIME_SHIFT) /*!< 1ms */
//#define FS8X_FS_I_ERRMON_ACK_TIME_8MS    (0x0001U << FS8X_FS_I_ERRMON_ACK_TIME_SHIFT) /*!< 8ms */
//#define FS8X_FS_I_ERRMON_ACK_TIME_16MS   (0x0002U << FS8X_FS_I_ERRMON_ACK_TIME_SHIFT) /*!< 16ms */
//#define FS8X_FS_I_ERRMON_ACK_TIME_32MS   (0x0003U << FS8X_FS_I_ERRMON_ACK_TIME_SHIFT) /*!< 32ms */
//
//#define FS8X_FS_I_ERRMON_FLT_POL_NEGATIVE_EDGE (0x0000U << FS8X_FS_I_ERRMON_FLT_POL_SHIFT) /*!< Negative edge at ERRMON pin is a fault */
//#define FS8X_FS_I_ERRMON_FLT_POL_POSITIVE_EDGE (0x0001U << FS8X_FS_I_ERRMON_FLT_POL_SHIFT) /*!< Positive edge at ERRMON pin is a fault */
//
//#define FS8X_FS_I_FCCU2_FS_IMPACT_FS0B   (0x0000U << FS8X_FS_I_FCCU2_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_FCCU2_FS_IMPACT_FS0B_RSTB (0x0001U << FS8X_FS_I_FCCU2_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_FCCU1_FS_IMPACT_FS0B   (0x0000U << FS8X_FS_I_FCCU1_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_FCCU1_FS_IMPACT_FS0B_RSTB (0x0001U << FS8X_FS_I_FCCU1_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_FCCU12_FS_IMPACT_FS0B  (0x0000U << FS8X_FS_I_FCCU12_FS_IMPACT_SHIFT) /*!< FS0B only is asserted */
//#define FS8X_FS_I_FCCU12_FS_IMPACT_FS0B_RSTB (0x0001U << FS8X_FS_I_FCCU12_FS_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted */
//
//#define FS8X_FS_I_FCCU2_FLT_POL_FCCU2_L  (0x0000U << FS8X_FS_I_FCCU2_FLT_POL_SHIFT) /*!< FCCU2 low level is a fault */
//#define FS8X_FS_I_FCCU2_FLT_POL_FCCU2_H  (0x0001U << FS8X_FS_I_FCCU2_FLT_POL_SHIFT) /*!< FCCU2 hign level is a fault */
//
//#define FS8X_FS_I_FCCU1_FLT_POL_FCCU1_L  (0x0000U << FS8X_FS_I_FCCU1_FLT_POL_SHIFT) /*!< FCCU1 low level is a fault */
//#define FS8X_FS_I_FCCU1_FLT_POL_FCCU1_H  (0x0001U << FS8X_FS_I_FCCU1_FLT_POL_SHIFT) /*!< FCCU1 high level is a fault */
//
//#define FS8X_FS_I_FCCU12_FLT_POL_FCCU1_L_FCCU2_H (0x0000U << FS8X_FS_I_FCCU12_FLT_POL_SHIFT) /*!< FCCU1=0 or FCCU2=1 level is a fault */
//#define FS8X_FS_I_FCCU12_FLT_POL_FCCU1_H_FCCU2_L (0x0001U << FS8X_FS_I_FCCU12_FLT_POL_SHIFT) /*!< FCCU1=1 or FCCU2=0 level is a fault */
//
//#define FS8X_FS_I_FCCU_CFG_NO_MONITORING (0x0000U << FS8X_FS_I_FCCU_CFG_SHIFT) /*!< No monitoring */
//#define FS8X_FS_I_FCCU_CFG_FCCU1_FCCU2_PAIR (0x0001U << FS8X_FS_I_FCCU_CFG_SHIFT) /*!< FCCU1 and FCCU2 monitoring by pair (bi-stable protocol) */
//#define FS8X_FS_I_FCCU_CFG_FCCU1_FCCU2_INPUT (0x0002U << FS8X_FS_I_FCCU_CFG_SHIFT) /*!< FCCU1 or FCCU2 input monitoring */
//#define FS8X_FS_I_FCCU_CFG_FCCU1_INPUT   (0x0003U << FS8X_FS_I_FCCU_CFG_SHIFT) /*!< FCCU1 input monitoring only */
//
///******************************************************************************/
///* FS_I_NOT_SAFE_INPUTS - Type: RW                                            */
///******************************************************************************/
//
//#define FS8X_FS_I_NOT_SAFE_INPUTS_ADDR   0x08U
//#define FS8X_FS_I_NOT_SAFE_INPUTS_DEFAULT 0xBE39U
//
//#define FS8X_FS_I_BIT0_MASK              0x0001U /*!< RESERVED */
//#define FS8X_FS_I_NOT_ERRMON_FS_IMPACT_MASK 0x0002U /*!< ERRMON impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_ERRMON_ACK_TIME_MASK 0x000CU /*!< ERRMON acknowledgement timing */
//#define FS8X_FS_I_NOT_ERRMON_FLT_POL_MASK 0x0010U /*!< ERRMON polarity */
//#define FS8X_FS_I_NOT_FCCU2_FS_IMPACT_MASK 0x0040U /*!< FCCU2 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU1_FS_IMPACT_MASK 0x0080U /*!< FCCU1 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU12_FS_IMPACT_MASK 0x0100U /*!< FCCU12 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU2_FLT_POL_MASK 0x0400U /*!< FCCU2 polarity */
//#define FS8X_FS_I_NOT_FCCU1_FLT_POL_MASK 0x0800U /*!< FCCU1 polarity */
//#define FS8X_FS_I_NOT_FCCU12_FLT_POL_MASK 0x1000U /*!< FCCU12 polarity */
//#define FS8X_FS_I_NOT_FCCU_CFG_MASK      0xC000U /*!< FCCU pins configuration */
//
//#define FS8X_FS_I_BIT0_SHIFT             0x0000U /*!< RESERVED */
//#define FS8X_FS_I_NOT_ERRMON_FS_IMPACT_SHIFT 0x0001U /*!< ERRMON impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_ERRMON_ACK_TIME_SHIFT 0x0002U /*!< ERRMON acknowledgement timing */
//#define FS8X_FS_I_NOT_ERRMON_FLT_POL_SHIFT 0x0004U /*!< ERRMON polarity */
//#define FS8X_FS_I_NOT_FCCU2_FS_IMPACT_SHIFT 0x0006U /*!< FCCU2 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU1_FS_IMPACT_SHIFT 0x0007U /*!< FCCU1 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU12_FS_IMPACT_SHIFT 0x0008U /*!< FCCU12 impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FCCU2_FLT_POL_SHIFT 0x000AU /*!< FCCU2 polarity */
//#define FS8X_FS_I_NOT_FCCU1_FLT_POL_SHIFT 0x000BU /*!< FCCU1 polarity */
//#define FS8X_FS_I_NOT_FCCU12_FLT_POL_SHIFT 0x000CU /*!< FCCU12 polarity */
//#define FS8X_FS_I_NOT_FCCU_CFG_SHIFT     0x000EU /*!< FCCU pins configuration */
//
//#define FS8X_FS_I_BIT0_1                 (0x0001U << FS8X_FS_I_BIT0_SHIFT) /*!< 1 */
//
///******************************************************************************/
///* FS_I_FSSM - Type: RW                                                       */
///******************************************************************************/
//
#define FS8X_FS_I_FSSM_ADDR              0x09U
#define FS8X_FS_I_FSSM_DEFAULT           0x5180U

#define FS8X_FS_I_FLT_ERR_CNT_MASK       0x000FU /*!< Reflect the value of the Fault Error Counter */
#define FS8X_FS_I_DIS_8S_MASK            0x0010U /*!< Disable 8S timer */
#define FS8X_FS_I_CLK_MON_DIS_MASK       0x0020U /*!< Disable Clock Monitoring */
#define FS8X_FS_I_FS0B_SC_HIGH_CFG_MASK  0x0080U /*!< Assert RSTB in case of a short to high detected on FS0B */
#define FS8X_FS_I_RSTB_DUR_MASK          0x0200U /*!< RSTB pulse duration configuration */
#define FS8X_FS_I_FLT_ERR_IMPACT_MASK    0x1800U /*!< Fault Error Counter intermediate value impact on RSTB/FS0B */
#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_MASK 0xC000U /*!< Fault Error Counter max value configuration */

#define FS8X_FS_I_FLT_ERR_CNT_SHIFT      0x0000U /*!< Reflect the value of the Fault Error Counter */
#define FS8X_FS_I_DIS_8S_SHIFT           0x0004U /*!< Disable 8S timer */
#define FS8X_FS_I_CLK_MON_DIS_SHIFT      0x0005U /*!< Disable Clock Monitoring */
#define FS8X_FS_I_FS0B_SC_HIGH_CFG_SHIFT 0x0007U /*!< Assert RSTB in case of a short to high detected on FS0B */
#define FS8X_FS_I_RSTB_DUR_SHIFT         0x0009U /*!< RSTB pulse duration configuration */
#define FS8X_FS_I_FLT_ERR_IMPACT_SHIFT   0x000BU /*!< Fault Error Counter intermediate value impact on RSTB/FS0B */
#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_SHIFT 0x000EU /*!< Fault Error Counter max value configuration */

#define FS8X_FS_I_FLT_ERR_CNT_0          (0x0000U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 0 */
#define FS8X_FS_I_FLT_ERR_CNT_1          (0x0001U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 1 */
#define FS8X_FS_I_FLT_ERR_CNT_2          (0x0002U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 2 */
#define FS8X_FS_I_FLT_ERR_CNT_3          (0x0003U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 3 */
#define FS8X_FS_I_FLT_ERR_CNT_4          (0x0004U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 4 */
#define FS8X_FS_I_FLT_ERR_CNT_5          (0x0005U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 5 */
#define FS8X_FS_I_FLT_ERR_CNT_6          (0x0006U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 6 */
#define FS8X_FS_I_FLT_ERR_CNT_7          (0x0007U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 7 */
#define FS8X_FS_I_FLT_ERR_CNT_8          (0x0008U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 8 */
#define FS8X_FS_I_FLT_ERR_CNT_9          (0x0009U << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 9 */
#define FS8X_FS_I_FLT_ERR_CNT_10         (0x000AU << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 10 */
#define FS8X_FS_I_FLT_ERR_CNT_11         (0x000BU << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 11 */
#define FS8X_FS_I_FLT_ERR_CNT_12         (0x000CU << FS8X_FS_I_FLT_ERR_CNT_SHIFT) /*!< 12 */

#define FS8X_FS_I_DIS_8S_COUNTER_ENABLED (0x0000U << FS8X_FS_I_DIS_8S_SHIFT) /*!< RSTB LOW 8s Counter enabled */
#define FS8X_FS_I_DIS_8S_COUNTER_DISABLED (0x0001U << FS8X_FS_I_DIS_8S_SHIFT) /*!< RSTB LOW 8s Counter disabled */

#define FS8X_FS_I_CLK_MON_DIS_MONITORING_ACTIVE (0x0000U << FS8X_FS_I_CLK_MON_DIS_SHIFT) /*!< Clock Monitoring active */
#define FS8X_FS_I_CLK_MON_DIS_MONITORING_DISABLED (0x0001U << FS8X_FS_I_CLK_MON_DIS_SHIFT) /*!< Clock Monitoring disabled */

#define FS8X_FS_I_FS0B_SC_HIGH_CFG_NO_ASSERTION (0x0000U << FS8X_FS_I_FS0B_SC_HIGH_CFG_SHIFT) /*!< No assertion of the RESET */
#define FS8X_FS_I_FS0B_SC_HIGH_CFG_RESET_ASSERTED (0x0001U << FS8X_FS_I_FS0B_SC_HIGH_CFG_SHIFT) /*!< RESET asserted */

#define FS8X_FS_I_RSTB_DUR_10MS          (0x0000U << FS8X_FS_I_RSTB_DUR_SHIFT) /*!< 10 ms */
#define FS8X_FS_I_RSTB_DUR_1MS           (0x0001U << FS8X_FS_I_RSTB_DUR_SHIFT) /*!< 1 ms */

#define FS8X_FS_I_FLT_ERR_IMPACT_NO_EFFECT (0x0000U << FS8X_FS_I_FLT_ERR_IMPACT_SHIFT) /*!< No effect on RSTB and FS0B */
#define FS8X_FS_I_FLT_ERR_IMPACT_FS0B    (0x0001U << FS8X_FS_I_FLT_ERR_IMPACT_SHIFT) /*!< FS0B only is asserted if FLT_ERR_CNT=intermediate value */
#define FS8X_FS_I_FLT_ERR_IMPACT_FS0B_RSTB (0x0002U << FS8X_FS_I_FLT_ERR_IMPACT_SHIFT) /*!< FS0B and RSTB are asserted if FLT_ERR_CNT=intermediate value */

#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_2    (0x0000U << FS8X_FS_I_FLT_ERR_CNT_LIMIT_SHIFT) /*!< 2 */
#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_6    (0x0001U << FS8X_FS_I_FLT_ERR_CNT_LIMIT_SHIFT) /*!< 6 */
#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_8    (0x0002U << FS8X_FS_I_FLT_ERR_CNT_LIMIT_SHIFT) /*!< 8 */
#define FS8X_FS_I_FLT_ERR_CNT_LIMIT_12   (0x0003U << FS8X_FS_I_FLT_ERR_CNT_LIMIT_SHIFT) /*!< 12 */

///******************************************************************************/
///* FS_I_NOT_FSSM - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_I_NOT_FSSM_ADDR          0x0AU
//#define FS8X_FS_I_NOT_FSSM_DEFAULT       0xAE7FU
//
//#define FS8X_FS_I_NOT_DIS_8S_MASK        0x0010U /*!< Disable 8S timer */
//#define FS8X_FS_I_NOT_CLK_MON_DIS_MASK   0x0020U /*!< Disable Clock Monitoring */
//#define FS8X_FS_I_NOT_FS0B_SC_HIGH_CFG_MASK 0x0080U /*!< Assert RSTB in case of a short to high detected on FS0B */
//#define FS8X_FS_I_NOT_RSTB_DUR_MASK      0x0200U /*!< RSTB pulse duration configuration */
//#define FS8X_FS_I_NOT_FLT_ERR_IMPACT_MASK 0x1800U /*!< Fault Error Counter intermediate value impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FLT_ERR_CNT_LIMIT_MASK 0xC000U /*!< Fault Error Counter max value configuration */
//
//#define FS8X_FS_I_NOT_DIS_8S_SHIFT       0x0004U /*!< Disable 8S timer */
//#define FS8X_FS_I_NOT_CLK_MON_DIS_SHIFT  0x0005U /*!< Disable Clock Monitoring */
//#define FS8X_FS_I_NOT_FS0B_SC_HIGH_CFG_SHIFT 0x0007U /*!< Assert RSTB in case of a short to high detected on FS0B */
//#define FS8X_FS_I_NOT_RSTB_DUR_SHIFT     0x0009U /*!< RSTB pulse duration configuration */
//#define FS8X_FS_I_NOT_FLT_ERR_IMPACT_SHIFT 0x000BU /*!< Fault Error Counter intermediate value impact on RSTB/FS0B */
//#define FS8X_FS_I_NOT_FLT_ERR_CNT_LIMIT_SHIFT 0x000EU /*!< Fault Error Counter max value configuration */
//
///******************************************************************************/
///* FS_I_SVS - Type: RW                                                        */
///******************************************************************************/
//
//#define FS8X_FS_I_SVS_ADDR               0x0BU
//#define FS8X_FS_I_SVS_DEFAULT            0x0000U
//
//#define FS8X_FS_I_SVS_OFFSET_MASK        0xF800U /*!< Static Voltage Scaling negative offset */
//
//#define FS8X_FS_I_SVS_OFFSET_SHIFT       0x000BU /*!< Static Voltage Scaling negative offset */
//
//#define FS8X_FS_I_SVS_OFFSET_EXTERNAL_REGULATOR (0x0000U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< 0mV */
//#define FS8X_FS_I_SVS_OFFSET_M6_25MV     (0x0001U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -6.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M12_50MV    (0x0002U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -12.50mV */
//#define FS8X_FS_I_SVS_OFFSET_M18_75MV    (0x0003U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -18.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M25MV       (0x0004U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -25mV */
//#define FS8X_FS_I_SVS_OFFSET_M31_25MV    (0x0005U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -31.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M37_5MV     (0x0006U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -37.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M43_75MV    (0x0007U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -43.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M50MV       (0x0008U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -50mV */
//#define FS8X_FS_I_SVS_OFFSET_M56_25MV    (0x0009U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -56.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M62_5MV     (0x000AU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -62.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M68_75MV    (0x000BU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -68.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M75MV       (0x000CU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -75mV */
//#define FS8X_FS_I_SVS_OFFSET_M81_25MV    (0x000DU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -81.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M87_5MV     (0x000EU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -87.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M93_75MV    (0x000FU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -93.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M100MV      (0x0010U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -100mV */
//#define FS8X_FS_I_SVS_OFFSET_M106_25MV   (0x0011U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -106.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M112_5MV    (0x0012U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -112.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M118_75MV   (0x0013U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -118.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M125MV      (0x0014U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -125mV */
//#define FS8X_FS_I_SVS_OFFSET_M131_25MV   (0x0015U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -131.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M137_5MV    (0x0016U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -137.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M143_75MV   (0x0017U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -143.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M150MV      (0x0018U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -150mV */
//#define FS8X_FS_I_SVS_OFFSET_M156_25MV   (0x0019U << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -156.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M162_5MV    (0x001AU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -162.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M168_75MV   (0x001BU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -168.75mV */
//#define FS8X_FS_I_SVS_OFFSET_M175MV      (0x001CU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -175mV */
//#define FS8X_FS_I_SVS_OFFSET_M181_25MV   (0x001DU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -181.25mV */
//#define FS8X_FS_I_SVS_OFFSET_M187_5MV    (0x001EU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -187.5mV */
//#define FS8X_FS_I_SVS_OFFSET_M193_75MV   (0x001FU << FS8X_FS_I_SVS_OFFSET_SHIFT) /*!< -193.75mV */
//
///******************************************************************************/
///* FS_I_NOT_SVS - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_I_NOT_SVS_ADDR           0x0CU
//#define FS8X_FS_I_NOT_SVS_DEFAULT        0xFFFFU
//
//#define FS8X_FS_I_NOT_SVS_OFFSET_MASK    0xF800U /*!< Static Voltage Scaling negative offset */
//
//#define FS8X_FS_I_NOT_SVS_OFFSET_SHIFT   0x000BU /*!< Static Voltage Scaling negative offset */
//
///******************************************************************************/
///* FS_MIRRORCMD - Type: RW                                                    */
///******************************************************************************/
//
#define FS8X_FS_MIRRORCMD_ADDR           0x17U
#define FS8X_FS_MIRRORCMD_DEFAULT        0x0000U

#define FS8X_FS_ADDR_MASK                0x00FFU /*!< Mirror register address pointer/index */
#define FS8X_FS_WRITE_MASK               0x0100U /*!< Mirror register write command */

#define FS8X_FS_ADDR_SHIFT               0x0000U /*!< Mirror register address pointer/index */
#define FS8X_FS_WRITE_SHIFT              0x0008U /*!< Mirror register write command */

#define FS8X_FS_WRITE_NO_OPERATION       (0x0000U << FS8X_FS_WRITE_SHIFT) /*!< No operation */
#define FS8X_FS_WRITE_WRITE_DATA         (0x0001U << FS8X_FS_WRITE_SHIFT) /*!< Write data in DATAWR field into mirror registers table at address ADDR */
//
///******************************************************************************/
///* FS_MIRRORDATA - Type: RW                                                   */
///******************************************************************************/

#define FS8X_FS_MIRRORDATA_ADDR          0x18U
#define FS8X_FS_MIRRORDATA_DEFAULT       0x0000U

#define FS8X_FS_DATAWR_MASK              0x00FFU /*!< Mirror Data to be programmed at address specified by ADDR in MIRRORCMD register */
#define FS8X_FS_DATAR_MASK               0xFF00U /*!< Mirror register read data content */

#define FS8X_FS_DATAWR_SHIFT             0x0000U /*!< Mirror Data to be programmed at address specified by ADDR in MIRRORCMD register */
#define FS8X_FS_DATAR_SHIFT              0x0008U /*!< Mirror register read data content */

///******************************************************************************/
///* FS_OTPADDR - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTPADDR_ADDR             0x19U
//#define FS8X_FS_OTPADDR_DEFAULT          0x0000U
//
//#define FS8X_FS_START_MASK               0x00FFU /*!< Start address for some OTPC commands */
//#define FS8X_FS_STOP_MASK                0xFF00U /*!< OTP operation stop address */
//
//#define FS8X_FS_START_SHIFT              0x0000U /*!< Start address for some OTPC commands */
//#define FS8X_FS_STOP_SHIFT               0x0008U /*!< OTP operation stop address */
//
///******************************************************************************/
///* FS_OTPDATA - Type: RW                                                      */
///******************************************************************************/
//
//#define FS8X_FS_OTPDATA_ADDR             0x1AU
//#define FS8X_FS_OTPDATA_DEFAULT          0x0000U
//
//#define FS8X_FS_DATAIN_MASK              0x00FFU /*!< Data to be written on certain OTPC commands */
//#define FS8X_FS_DATAOUT_MASK             0xFF00U /*!< Data to be read on certain OTPC commands */
//
//#define FS8X_FS_DATAIN_SHIFT             0x0000U /*!< Data to be written on certain OTPC commands */
//#define FS8X_FS_DATAOUT_SHIFT            0x0008U /*!< Data to be read on certain OTPC commands */
//
///******************************************************************************/
///* FS_OTPCMD - Type: RW                                                       */
///******************************************************************************/
//
//#define FS8X_FS_OTPCMD_ADDR              0x1BU
//#define FS8X_FS_OTPCMD_DEFAULT           0x0000U
//
//#define FS8X_FS_CMD_MASK                 0x003FU /*!< OTP operation commands - see below */
//#define FS8X_FS_GO_MASK                  0x0100U /*!< N/A */
//
//#define FS8X_FS_CMD_SHIFT                0x0000U /*!< OTP operation commands - see below */
//#define FS8X_FS_GO_SHIFT                 0x0008U /*!< N/A */
//
//#define FS8X_FS_CMD_C_IDLE               (0x0000U << FS8X_FS_CMD_SHIFT) /*!< C_IDLE */
//#define FS8X_FS_CMD_C_PRG                (0x0016U << FS8X_FS_CMD_SHIFT) /*!< C_PRG */
//#define FS8X_FS_CMD_C_PRG_ONE            (0x0007U << FS8X_FS_CMD_SHIFT) /*!< C_PRG_ONE */
//#define FS8X_FS_CMD_C_RD                 (0x0012U << FS8X_FS_CMD_SHIFT) /*!< C_RD */
//#define FS8X_FS_CMD_C_RD_ALL             (0x0003U << FS8X_FS_CMD_SHIFT) /*!< C_RD_ALL */
//#define FS8X_FS_CMD_C_RD_ONE             (0x000BU << FS8X_FS_CMD_SHIFT) /*!< C_RD_ONE */
//#define FS8X_FS_CMD_C_CHK                (0x001BU << FS8X_FS_CMD_SHIFT) /*!< C_CHK */
//#define FS8X_FS_CMD_C_CHK_XX             (0x001AU << FS8X_FS_CMD_SHIFT) /*!< C_CHK_XX */
//
//#define FS8X_FS_GO_NO_ACTION             (0x0000U << FS8X_FS_GO_SHIFT) /*!< No action */
//#define FS8X_FS_GO_START_COMMAND         (0x0001U << FS8X_FS_GO_SHIFT) /*!< START Command specified by CMD. Self clears after BUSY flag in STATUS register is set. */
//
///******************************************************************************/
///* FS_OTPSTATUS0 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPSTATUS0_ADDR          0x1CU
//#define FS8X_FS_OTPSTATUS0_DEFAULT       0x0000U
//
//#define FS8X_FS_BUSY_MASK                0x0001U /*!< N/A */
//#define FS8X_FS_ERROR_MASK               0x0002U /*!< N/A */
//#define FS8X_FS_ONE_ERR_MASK             0x0004U /*!< N/A */
//#define FS8X_FS_TWO_ERR_MASK             0x0008U /*!< N/A */
//#define FS8X_FS_MAX_PGM_EXCEED_MASK      0x0010U /*!< N/A */
//#define FS8X_FS_VRR_CHECK_TRIES_MASK     0x07E0U /*!< Count numbers of cold start VRR reads or programming tries */
//#define FS8X_FS_PGM_FAIL_WP_MASK         0x0800U /*!< tried to prg a WP sector */
//#define FS8X_FS_BOOT_ERROR_MASK          0x1000U /*!< no crc error and no double error for bootable sector - updated after CRC check cmd */
//
//#define FS8X_FS_BUSY_SHIFT               0x0000U /*!< N/A */
//#define FS8X_FS_ERROR_SHIFT              0x0001U /*!< N/A */
//#define FS8X_FS_ONE_ERR_SHIFT            0x0002U /*!< N/A */
//#define FS8X_FS_TWO_ERR_SHIFT            0x0003U /*!< N/A */
//#define FS8X_FS_MAX_PGM_EXCEED_SHIFT     0x0004U /*!< N/A */
//#define FS8X_FS_VRR_CHECK_TRIES_SHIFT    0x0005U /*!< Count numbers of cold start VRR reads or programming tries */
//#define FS8X_FS_PGM_FAIL_WP_SHIFT        0x000BU /*!< tried to prg a WP sector */
//#define FS8X_FS_BOOT_ERROR_SHIFT         0x000CU /*!< no crc error and no double error for bootable sector - updated after CRC check cmd */
//
//#define FS8X_FS_BUSY_IDLE                (0x0000U << FS8X_FS_BUSY_SHIFT) /*!< Fuse Interface Idle */
//#define FS8X_FS_BUSY_PROGRAMMING         (0x0001U << FS8X_FS_BUSY_SHIFT) /*!< Programming in progress */
//
//#define FS8X_FS_ERROR_NA                 (0x0000U << FS8X_FS_ERROR_SHIFT) /*!< N/A */
//#define FS8X_FS_ERROR_ERROR_FLAG_SET     (0x0001U << FS8X_FS_ERROR_SHIFT) /*!< The ERROR flag is set during VERIFY commands, if the verification fails and if any invalid command is issued. Also, ERROR is set if trying to program a data at an address which was previously programmed (and the bits to be programmed later were not masked). */
//
//#define FS8X_FS_ONE_ERR_NA               (0x0000U << FS8X_FS_ONE_ERR_SHIFT) /*!< N/A */
//#define FS8X_FS_ONE_ERR_ERROR_DETECTED   (0x0001U << FS8X_FS_ONE_ERR_SHIFT) /*!< If ECC is enabled, one ECC error was detected in one or multiple rows */
//
//#define FS8X_FS_TWO_ERR_NA               (0x0000U << FS8X_FS_TWO_ERR_SHIFT) /*!< N/A */
//#define FS8X_FS_TWO_ERR_TWO_ERR_DETECTED (0x0001U << FS8X_FS_TWO_ERR_SHIFT) /*!< If ECC is enabled, two ECC errors were detected in one or multiple rows */
//
//#define FS8X_FS_MAX_PGM_EXCEED_NA        (0x0000U << FS8X_FS_MAX_PGM_EXCEED_SHIFT) /*!< N/A */
//#define FS8X_FS_MAX_PGM_EXCEED_EXCEEDED  (0x0001U << FS8X_FS_MAX_PGM_EXCEED_SHIFT) /*!< exceeded maximum number of programming trials (specified by MAX_PGM_TRIES register setting) */
//
//#define FS8X_FS_PGM_FAIL_WP_NO_FAIL      (0x0000U << FS8X_FS_PGM_FAIL_WP_SHIFT) /*!< no fail */
//#define FS8X_FS_PGM_FAIL_WP_FAIL_DETECTED (0x0001U << FS8X_FS_PGM_FAIL_WP_SHIFT) /*!< fail detected */
//
//#define FS8X_FS_BOOT_ERROR_NO_ERROR_DETECTED (0x0000U << FS8X_FS_BOOT_ERROR_SHIFT) /*!< no error detected */
//#define FS8X_FS_BOOT_ERROR_ERROR_DETECTED (0x0001U << FS8X_FS_BOOT_ERROR_SHIFT) /*!< error detected */
//
///******************************************************************************/
///* FS_OTPSTATUS1 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPSTATUS1_ADDR          0x1DU
//#define FS8X_FS_OTPSTATUS1_DEFAULT       0x0000U
//
//#define FS8X_FS_CRCSTS0_MASK             0x0001U /*!< Sector CRC status */
//#define FS8X_FS_CRCSTS1_MASK             0x0002U /*!< Sector CRC status */
//#define FS8X_FS_CRCSTS2_MASK             0x0004U /*!< Sector CRC status */
//#define FS8X_FS_SECTBE0_MASK             0x0008U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTBE1_MASK             0x0010U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTBE2_MASK             0x0020U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTWP0_MASK             0x0040U /*!< Sector Write Protected status */
//#define FS8X_FS_SECTWP1_MASK             0x0080U /*!< Sector Write Protected status */
//#define FS8X_FS_SECTWP2_MASK             0x0100U /*!< Sector Write Protected status */
//#define FS8X_FS_MTP_INDEX_S1_MASK        0x0E00U /*!< Multi Time Progr Index Status for Sector 1 */
//
//#define FS8X_FS_CRCSTS0_SHIFT            0x0000U /*!< Sector CRC status */
//#define FS8X_FS_CRCSTS1_SHIFT            0x0001U /*!< Sector CRC status */
//#define FS8X_FS_CRCSTS2_SHIFT            0x0002U /*!< Sector CRC status */
//#define FS8X_FS_SECTBE0_SHIFT            0x0003U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTBE1_SHIFT            0x0004U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTBE2_SHIFT            0x0005U /*!< Sector Boot Enable status */
//#define FS8X_FS_SECTWP0_SHIFT            0x0006U /*!< Sector Write Protected status */
//#define FS8X_FS_SECTWP1_SHIFT            0x0007U /*!< Sector Write Protected status */
//#define FS8X_FS_SECTWP2_SHIFT            0x0008U /*!< Sector Write Protected status */
//#define FS8X_FS_MTP_INDEX_S1_SHIFT       0x0009U /*!< Multi Time Progr Index Status for Sector 1 */
//
//#define FS8X_FS_CRCSTS0_CRC_ERROR        (0x0000U << FS8X_FS_CRCSTS0_SHIFT) /*!< CRC error at sector 0 or CRC check not run on that sector */
//#define FS8X_FS_CRCSTS0_CRC_OK           (0x0001U << FS8X_FS_CRCSTS0_SHIFT) /*!< CRC check OK at sector 0 */
//
//#define FS8X_FS_CRCSTS1_CRC_ERROR        (0x0000U << FS8X_FS_CRCSTS1_SHIFT) /*!< CRC error at sector 1 or CRC check not run on that sector */
//#define FS8X_FS_CRCSTS1_CRC_OK           (0x0001U << FS8X_FS_CRCSTS1_SHIFT) /*!< CRC check OK at sector 1 */
//
//#define FS8X_FS_CRCSTS2_CRC_ERROR        (0x0000U << FS8X_FS_CRCSTS2_SHIFT) /*!< CRC error at sector 2 or CRC check not run on that sector */
//#define FS8X_FS_CRCSTS2_CRC_OK           (0x0001U << FS8X_FS_CRCSTS2_SHIFT) /*!< CRC check OK at sector 2 */
//
//#define FS8X_FS_SECTBE0_NOT_BOOTABLE     (0x0000U << FS8X_FS_SECTBE0_SHIFT) /*!< Sector 0 is not bootable */
//#define FS8X_FS_SECTBE0_BOOTABLE         (0x0001U << FS8X_FS_SECTBE0_SHIFT) /*!< Sector 0 is bootable */
//
//#define FS8X_FS_SECTBE1_NOT_BOOTABLE     (0x0000U << FS8X_FS_SECTBE1_SHIFT) /*!< Sector 1 is not bootable */
//#define FS8X_FS_SECTBE1_BOOTABLE         (0x0001U << FS8X_FS_SECTBE1_SHIFT) /*!< Sector 1 is bootable */
//
//#define FS8X_FS_SECTBE2_NOT_BOOTABLE     (0x0000U << FS8X_FS_SECTBE2_SHIFT) /*!< Sector 2 is not bootable */
//#define FS8X_FS_SECTBE2_BOOTABLE         (0x0001U << FS8X_FS_SECTBE2_SHIFT) /*!< Sector 2 is bootable */
//
//#define FS8X_FS_SECTWP0_NOT_WRITE_PROTECTED (0x0000U << FS8X_FS_SECTWP0_SHIFT) /*!< Sector 0 is not write protected */
//#define FS8X_FS_SECTWP0_WRITE_PROTECTED  (0x0001U << FS8X_FS_SECTWP0_SHIFT) /*!< Sector 0 is write protected */
//
//#define FS8X_FS_SECTWP1_NOT_WRITE_PROTECTED (0x0000U << FS8X_FS_SECTWP1_SHIFT) /*!< Sector 1 is not write protected */
//#define FS8X_FS_SECTWP1_WRITE_PROTECTED  (0x0001U << FS8X_FS_SECTWP1_SHIFT) /*!< Sector 1 is write protected */
//
//#define FS8X_FS_SECTWP2_NOT_WRITE_PROTECTED (0x0000U << FS8X_FS_SECTWP2_SHIFT) /*!< Sector 2 is not write protected */
//#define FS8X_FS_SECTWP2_WRITE_PROTECTED  (0x0001U << FS8X_FS_SECTWP2_SHIFT) /*!< Sector 2 is write protected */
//
///******************************************************************************/
///* FS_OTPPARAM0 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM0_ADDR           0x1EU
//#define FS8X_FS_OTPPARAM0_DEFAULT        0x0268U
//
//#define FS8X_FS_MAX_PGM_TRIES_MASK       0x003FU /*!< MAX_PGM_TRIES */
//#define FS8X_FS_SVDR_IN_MASK             0x0040U /*!< SVDR_IN */
//#define FS8X_FS_MRR_IN_MASK              0x0780U /*!< MRR_IN */
//#define FS8X_FS_LOVCC_IN_MASK            0x0800U /*!< LOVCC_IN */
//#define FS8X_FS_MR_SCREF_RD_1_MASK       0xF000U /*!< MR_SCREF_RD_1 */
//
//#define FS8X_FS_MAX_PGM_TRIES_SHIFT      0x0000U /*!< MAX_PGM_TRIES */
//#define FS8X_FS_SVDR_IN_SHIFT            0x0006U /*!< SVDR_IN */
//#define FS8X_FS_MRR_IN_SHIFT             0x0007U /*!< MRR_IN */
//#define FS8X_FS_LOVCC_IN_SHIFT           0x000BU /*!< LOVCC_IN */
//#define FS8X_FS_MR_SCREF_RD_1_SHIFT      0x000CU /*!< MR_SCREF_RD_1 */
//
//#define FS8X_FS_SVDR_IN_CUSTOM           (0x0000U << FS8X_FS_SVDR_IN_SHIFT) /*!< custom */
//#define FS8X_FS_SVDR_IN_DEFAULT          (0x0001U << FS8X_FS_SVDR_IN_SHIFT) /*!< default */
//
//#define FS8X_FS_LOVCC_IN_DEFAULT         (0x0000U << FS8X_FS_LOVCC_IN_SHIFT) /*!< default */
//#define FS8X_FS_LOVCC_IN_CUSTOM          (0x0001U << FS8X_FS_LOVCC_IN_SHIFT) /*!< custom */
//
///******************************************************************************/
///* FS_OTPPARAM1 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM1_ADDR           0x1FU
//#define FS8X_FS_OTPPARAM1_DEFAULT        0x0000U
//
//#define FS8X_FS_MREF_IREF_RD_1_MASK      0x003FU /*!< MREF_IREF_RD_1 */
//#define FS8X_FS_MR_SCREF_RD_2_MASK       0x03C0U /*!< MR_SCREF_RD_2 */
//#define FS8X_FS_MREF_IREF_RD_2_MASK      0xFC00U /*!< MREF_IREF_RD_2 */
//
//#define FS8X_FS_MREF_IREF_RD_1_SHIFT     0x0000U /*!< MREF_IREF_RD_1 */
//#define FS8X_FS_MR_SCREF_RD_2_SHIFT      0x0006U /*!< MR_SCREF_RD_2 */
//#define FS8X_FS_MREF_IREF_RD_2_SHIFT     0x000AU /*!< MREF_IREF_RD_2 */
//
///******************************************************************************/
///* FS_OTPPARAM2 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM2_ADDR           0x20U
//#define FS8X_FS_OTPPARAM2_DEFAULT        0x0000U
//
//#define FS8X_FS_MREF_TEST_MASK           0xFFFFU /*!< MREF_TEST */
//
//#define FS8X_FS_MREF_TEST_SHIFT          0x0000U /*!< MREF_TEST */
//
///******************************************************************************/
///* FS_OTPPARAM3 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM3_ADDR           0x21U
//#define FS8X_FS_OTPPARAM3_DEFAULT        0x0000U
//
//#define FS8X_FS_MR_TEST_MASK             0xFFFFU /*!< MR_TEST */
//
//#define FS8X_FS_MR_TEST_SHIFT            0x0000U /*!< MR_TEST */
//
///******************************************************************************/
///* FS_OTPPARAM4 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM4_ADDR           0x22U
//#define FS8X_FS_OTPPARAM4_DEFAULT        0x0000U
//
//#define FS8X_FS_TEST_MODE_MASK           0x0001U /*!< TEST_MODE */
//#define FS8X_FS_START_LSB_MASK           0x0006U /*!< START_LSB */
//#define FS8X_FS_STOP_LSB_MASK            0x0018U /*!< STOP_LSB */
//#define FS8X_FS_DISABLE_WP_MASK          0x0020U /*!< DISABLE_WP */
//#define FS8X_FS_TM10_MASK                0x0040U /*!< TM10 */
//#define FS8X_FS_SE_MASK                  0x0380U /*!< SE */
//#define FS8X_FS_PGM_PULSE_DUR_MASK       0x3C00U /*!< PGM_PULSE_DUR */
//#define FS8X_FS_PGM_SKIP_READS_MASK      0x4000U /*!< PGM_SKIP_READS */
//#define FS8X_FS_TRIES_SOAK_OPT_MASK      0x8000U /*!< TRIES_SOAK_OPT */
//
//#define FS8X_FS_TEST_MODE_SHIFT          0x0000U /*!< TEST_MODE */
//#define FS8X_FS_START_LSB_SHIFT          0x0001U /*!< START_LSB */
//#define FS8X_FS_STOP_LSB_SHIFT           0x0003U /*!< STOP_LSB */
//#define FS8X_FS_DISABLE_WP_SHIFT         0x0005U /*!< DISABLE_WP */
//#define FS8X_FS_TM10_SHIFT               0x0006U /*!< TM10 */
//#define FS8X_FS_SE_SHIFT                 0x0007U /*!< SE */
//#define FS8X_FS_PGM_PULSE_DUR_SHIFT      0x000AU /*!< PGM_PULSE_DUR */
//#define FS8X_FS_PGM_SKIP_READS_SHIFT     0x000EU /*!< PGM_SKIP_READS */
//#define FS8X_FS_TRIES_SOAK_OPT_SHIFT     0x000FU /*!< TRIES_SOAK_OPT */
//
//#define FS8X_FS_TEST_MODE_DEFAULT        (0x0000U << FS8X_FS_TEST_MODE_SHIFT) /*!< default */
//#define FS8X_FS_TEST_MODE_CUSTOM         (0x0001U << FS8X_FS_TEST_MODE_SHIFT) /*!< custom */
//
//#define FS8X_FS_DISABLE_WP_DEFAULT       (0x0000U << FS8X_FS_DISABLE_WP_SHIFT) /*!< default */
//#define FS8X_FS_DISABLE_WP_CUSTOM        (0x0001U << FS8X_FS_DISABLE_WP_SHIFT) /*!< custom */
//
//#define FS8X_FS_TM10_DEFAULT             (0x0000U << FS8X_FS_TM10_SHIFT) /*!< default */
//#define FS8X_FS_TM10_CUSTOM              (0x0001U << FS8X_FS_TM10_SHIFT) /*!< custom */
//
//#define FS8X_FS_PGM_SKIP_READS_DEFAULT   (0x0000U << FS8X_FS_PGM_SKIP_READS_SHIFT) /*!< default */
//#define FS8X_FS_PGM_SKIP_READS_CUSTOM    (0x0001U << FS8X_FS_PGM_SKIP_READS_SHIFT) /*!< custom */
//
//#define FS8X_FS_TRIES_SOAK_OPT_DEFAULT   (0x0000U << FS8X_FS_TRIES_SOAK_OPT_SHIFT) /*!< default */
//#define FS8X_FS_TRIES_SOAK_OPT_CUSTOM    (0x0001U << FS8X_FS_TRIES_SOAK_OPT_SHIFT) /*!< custom */
//
///******************************************************************************/
///* FS_OTPPARAM5 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM5_ADDR           0x23U
//#define FS8X_FS_OTPPARAM5_DEFAULT        0x2400U
//
//#define FS8X_FS_SOAK_PULSE_DUR_MASK      0x000FU /*!< SOAK_PULSE_DUR */
//#define FS8X_FS_READ_PULSE_DUR_MASK      0x00F0U /*!< READ_PULSE_DUR */
//#define FS8X_FS_ALWAYS_ON_MASK           0x0100U /*!< ALWAYS_ON */
//#define FS8X_FS_TEST_ROW_ACCESS_MASK     0x0200U /*!< TEST_ROW_ACCESS */
//#define FS8X_FS_ECC_ENABLE_MASK          0x0400U /*!< ECC_ENABLE */
//#define FS8X_FS_PGM_ONE_BIT_MASK         0x0800U /*!< PGM_ONE_BIT */
//#define FS8X_FS_SOAK_ONE_BIT_MASK        0x1000U /*!< SOAK_ONE_BIT */
//#define FS8X_FS_ROM_READ_PULSE_WIDTH_MASK 0x2000U /*!< ROM_READ_PULSE_WIDTH */
//
//#define FS8X_FS_SOAK_PULSE_DUR_SHIFT     0x0000U /*!< SOAK_PULSE_DUR */
//#define FS8X_FS_READ_PULSE_DUR_SHIFT     0x0004U /*!< READ_PULSE_DUR */
//#define FS8X_FS_ALWAYS_ON_SHIFT          0x0008U /*!< ALWAYS_ON */
//#define FS8X_FS_TEST_ROW_ACCESS_SHIFT    0x0009U /*!< TEST_ROW_ACCESS */
//#define FS8X_FS_ECC_ENABLE_SHIFT         0x000AU /*!< ECC_ENABLE */
//#define FS8X_FS_PGM_ONE_BIT_SHIFT        0x000BU /*!< PGM_ONE_BIT */
//#define FS8X_FS_SOAK_ONE_BIT_SHIFT       0x000CU /*!< SOAK_ONE_BIT */
//#define FS8X_FS_ROM_READ_PULSE_WIDTH_SHIFT 0x000DU /*!< ROM_READ_PULSE_WIDTH */
//
//#define FS8X_FS_ALWAYS_ON_DEFAULT        (0x0000U << FS8X_FS_ALWAYS_ON_SHIFT) /*!< default */
//#define FS8X_FS_ALWAYS_ON_CUSTOM         (0x0001U << FS8X_FS_ALWAYS_ON_SHIFT) /*!< custom */
//
//#define FS8X_FS_TEST_ROW_ACCESS_DEFAULT  (0x0000U << FS8X_FS_TEST_ROW_ACCESS_SHIFT) /*!< default */
//#define FS8X_FS_TEST_ROW_ACCESS_CUSTOM   (0x0001U << FS8X_FS_TEST_ROW_ACCESS_SHIFT) /*!< custom */
//
//#define FS8X_FS_ECC_ENABLE_CUSTOM        (0x0000U << FS8X_FS_ECC_ENABLE_SHIFT) /*!< custom */
//#define FS8X_FS_ECC_ENABLE_DEFAULT       (0x0001U << FS8X_FS_ECC_ENABLE_SHIFT) /*!< default */
//
//#define FS8X_FS_PGM_ONE_BIT_DEFAULT      (0x0000U << FS8X_FS_PGM_ONE_BIT_SHIFT) /*!< default */
//#define FS8X_FS_PGM_ONE_BIT_CUSTOM       (0x0001U << FS8X_FS_PGM_ONE_BIT_SHIFT) /*!< custom */
//
//#define FS8X_FS_SOAK_ONE_BIT_DEFAULT     (0x0000U << FS8X_FS_SOAK_ONE_BIT_SHIFT) /*!< default */
//#define FS8X_FS_SOAK_ONE_BIT_CUSTOM      (0x0001U << FS8X_FS_SOAK_ONE_BIT_SHIFT) /*!< custom */
//
//#define FS8X_FS_ROM_READ_PULSE_WIDTH_CUSTOM (0x0000U << FS8X_FS_ROM_READ_PULSE_WIDTH_SHIFT) /*!< custom */
//#define FS8X_FS_ROM_READ_PULSE_WIDTH_DEFAULT (0x0001U << FS8X_FS_ROM_READ_PULSE_WIDTH_SHIFT) /*!< default */
//
///******************************************************************************/
///* FS_OTPPARAM6 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_OTPPARAM6_ADDR           0x24U
//#define FS8X_FS_OTPPARAM6_DEFAULT        0x0000U
//
//#define FS8X_FS_PGM_IDLE_MASK            0x003FU /*!< PGM_IDLE */
//
//#define FS8X_FS_PGM_IDLE_SHIFT           0x0000U /*!< PGM_IDLE */
//
///******************************************************************************/
///* FS_TM_ENTRY - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_FS_TM_ENTRY_ADDR            0x25U
//#define FS8X_FS_TM_ENTRY_DEFAULT         0x0000U
//
//#define FS8X_FS_TM_TM_ENTRY_KEY_MASK     0xFFFFU /*!< TEST MODE ENTRY KEYS SEQUENCE */
//
//#define FS8X_FS_TM_TM_ENTRY_KEY_SHIFT    0x0000U /*!< TEST MODE ENTRY KEYS SEQUENCE */
//
///******************************************************************************/
///* FS_TM_DMUX1 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_FS_TM_DMUX1_ADDR            0x26U
//#define FS8X_FS_TM_DMUX1_DEFAULT         0x0000U
//
//#define FS8X_FS_TM_DMUX_OV0_SEL_MASK     0x001FU /*!< Select DMUX FCCU1 input */
//#define FS8X_FS_TM_DMUX_OV1_SEL_MASK     0x03E0U /*!< Select DMUX FCCU2 input */
//#define FS8X_FS_TM_DMUX_OV2_SEL_MASK     0x7C00U /*!< Select DMUX ERRMON input */
//
//#define FS8X_FS_TM_DMUX_OV0_SEL_SHIFT    0x0000U /*!< Select DMUX FCCU1 input */
//#define FS8X_FS_TM_DMUX_OV1_SEL_SHIFT    0x0005U /*!< Select DMUX FCCU2 input */
//#define FS8X_FS_TM_DMUX_OV2_SEL_SHIFT    0x000AU /*!< Select DMUX ERRMON input */
//
//#define FS8X_FS_TM_DMUX_OV0_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< vddio_ov_d */
//#define FS8X_FS_TM_DMUX_OV0_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< to_func_obs_vddio_ov */
//#define FS8X_FS_TM_DMUX_OV0_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< to_func_obs_vddio_uv_n */
//#define FS8X_FS_TM_DMUX_OV0_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< spare[5] */
//#define FS8X_FS_TM_DMUX_OV0_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV0_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< vmonx_ov_d_xor[5] ^ vmonx_uv_n_d_xor[5] ^ fccu1_d_xor */
//#define FS8X_FS_TM_DMUX_OV0_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< to_func_obs_PGOOD_sense */
//#define FS8X_FS_TM_DMUX_OV0_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< ring_osc_fs */
//#define FS8X_FS_TM_DMUX_OV0_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< scl2logic */
//#define FS8X_FS_TM_DMUX_OV0_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< clk mon ok */
//#define FS8X_FS_TM_DMUX_OV0_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< wd_ok */
//#define FS8X_FS_TM_DMUX_OV0_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< abist1_check_event */
//#define FS8X_FS_TM_DMUX_OV0_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< fccu1_err */
//#define FS8X_FS_TM_DMUX_OV0_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< fs0b_fault */
//#define FS8X_FS_TM_DMUX_OV0_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< abist1_fail */
//#define FS8X_FS_TM_DMUX_OV0_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< spi_bad_crc */
//#define FS8X_FS_TM_DMUX_OV0_SEL_16       (0x0010U << FS8X_FS_TM_DMUX_OV0_SEL_SHIFT) /*!< to_func_obs_main_fs_enable */
//
//#define FS8X_FS_TM_DMUX_OV1_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< vcore_ov_d */
//#define FS8X_FS_TM_DMUX_OV1_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< to_func_obs_vcore_ov */
//#define FS8X_FS_TM_DMUX_OV1_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< to_func_obs_vcore_uv_n */
//#define FS8X_FS_TM_DMUX_OV1_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< spare[4] */
//#define FS8X_FS_TM_DMUX_OV1_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV1_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< vmonx_ov_d_xor[4] ^ vmonx_uv_n_d_xor[4] ^ main_fs_enable_d_xor */
//#define FS8X_FS_TM_DMUX_OV1_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< to_func_obs_RSTb_sense */
//#define FS8X_FS_TM_DMUX_OV1_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< main_ref_clock */
//#define FS8X_FS_TM_DMUX_OV1_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< sda2logic */
//#define FS8X_FS_TM_DMUX_OV1_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< clk mon failure */
//#define FS8X_FS_TM_DMUX_OV1_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< wd_nok */
//#define FS8X_FS_TM_DMUX_OV1_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< abist2_check_event */
//#define FS8X_FS_TM_DMUX_OV1_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< fccu2_err */
//#define FS8X_FS_TM_DMUX_OV1_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< resetb_fault */
//#define FS8X_FS_TM_DMUX_OV1_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< abist1_pass */
//#define FS8X_FS_TM_DMUX_OV1_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV1_SEL_SHIFT) /*!< spi_underbit_cnt */
//
//#define FS8X_FS_TM_DMUX_OV2_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< vmon1_ov_d */
//#define FS8X_FS_TM_DMUX_OV2_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< to_func_obs_vmon1_ov */
//#define FS8X_FS_TM_DMUX_OV2_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< to_func_obs_vmon1_uv_n */
//#define FS8X_FS_TM_DMUX_OV2_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< spare[3] */
//#define FS8X_FS_TM_DMUX_OV2_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV2_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< vmonx_ov_d_xor[3] ^ vmonx_uv_n_d_xor[3] ^ debug_mode_d_xor */
//#define FS8X_FS_TM_DMUX_OV2_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< to_func_obs_FS0b_sense */
//#define FS8X_FS_TM_DMUX_OV2_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< to_func_obs_DEBUG_MODE_active */
//#define FS8X_FS_TM_DMUX_OV2_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< ipt_i2c_tsp_dmux */
//#define FS8X_FS_TM_DMUX_OV2_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< clk ref failure */
//#define FS8X_FS_TM_DMUX_OV2_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< wd open window */
//#define FS8X_FS_TM_DMUX_OV2_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< otp_busy */
//#define FS8X_FS_TM_DMUX_OV2_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< fccu12_err */
//#define FS8X_FS_TM_DMUX_OV2_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< pgood_fault */
//#define FS8X_FS_TM_DMUX_OV2_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< abist2_fail */
//#define FS8X_FS_TM_DMUX_OV2_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV2_SEL_SHIFT) /*!< spi_overbit_cnt */
//
///******************************************************************************/
///* FS_TM_DMUX2 - Type: RW                                                     */
///******************************************************************************/
//
//#define FS8X_FS_TM_DMUX2_ADDR            0x27U
//#define FS8X_FS_TM_DMUX2_DEFAULT         0x0000U
//
//#define FS8X_FS_TM_DMUX_OV3_SEL_MASK     0x001FU /*!< Select DMUX FOUT input */
//#define FS8X_FS_TM_DMUX_OV4_SEL_MASK     0x03E0U /*!< Select DMUX INTB input */
//#define FS8X_FS_TM_DMUX_OV5_SEL_MASK     0x7C00U /*!< Select DMUX AMUX input */
//
//#define FS8X_FS_TM_DMUX_OV3_SEL_SHIFT    0x0000U /*!< Select DMUX FOUT input */
//#define FS8X_FS_TM_DMUX_OV4_SEL_SHIFT    0x0005U /*!< Select DMUX INTB input */
//#define FS8X_FS_TM_DMUX_OV5_SEL_SHIFT    0x000AU /*!< Select DMUX AMUX input */
//
//#define FS8X_FS_TM_DMUX_OV3_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< vmon2_ov_d */
//#define FS8X_FS_TM_DMUX_OV3_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< to_func_obs_vmon2_ov */
//#define FS8X_FS_TM_DMUX_OV3_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< to_func_obs_vmon2_uv_n */
//#define FS8X_FS_TM_DMUX_OV3_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< spare[2] */
//#define FS8X_FS_TM_DMUX_OV3_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV3_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< vmonx_ov_d_xor[2] ^ vmonx_uv_n_d_xor[2] ^ pgood_sense_d_xor ^ errmon_d_xor */
//#define FS8X_FS_TM_DMUX_OV3_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< to_func_obs_FCCU1_failure */
//#define FS8X_FS_TM_DMUX_OV3_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< to_func_obs_vdig_fs_ov */
//#define FS8X_FS_TM_DMUX_OV3_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< csb */
//#define FS8X_FS_TM_DMUX_OV3_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< pgood short2hi */
//#define FS8X_FS_TM_DMUX_OV3_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< wd time out */
//#define FS8X_FS_TM_DMUX_OV3_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< lbist_checker_ok */
//#define FS8X_FS_TM_DMUX_OV3_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< fccu_error_recovery */
//#define FS8X_FS_TM_DMUX_OV3_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< fs0b_incr_flt */
//#define FS8X_FS_TM_DMUX_OV3_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< abist2_pass */
//#define FS8X_FS_TM_DMUX_OV3_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV3_SEL_SHIFT) /*!< spi_sclk_errr */
//
//#define FS8X_FS_TM_DMUX_OV4_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< vmon3_ov_d */
//#define FS8X_FS_TM_DMUX_OV4_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< to_func_obs_vmon3_ov */
//#define FS8X_FS_TM_DMUX_OV4_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< to_func_obs_vmon3_uv_n */
//#define FS8X_FS_TM_DMUX_OV4_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< spare[1] */
//#define FS8X_FS_TM_DMUX_OV4_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV4_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< vmonx_ov_d_xor[1] ^ vmonx_uv_n_d_xor[1] ^ fs0b_sense_d_xor ^ fccu2_d_xor */
//#define FS8X_FS_TM_DMUX_OV4_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< to_func_obs_FCCU2_failure */
//#define FS8X_FS_TM_DMUX_OV4_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< v5_fs_porn */
//#define FS8X_FS_TM_DMUX_OV4_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< mosi */
//#define FS8X_FS_TM_DMUX_OV4_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< rstb short2hi */
//#define FS8X_FS_TM_DMUX_OV4_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< wd_nok_recovery */
//#define FS8X_FS_TM_DMUX_OV4_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< ref_clk_toogle */
//#define FS8X_FS_TM_DMUX_OV4_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< crc_check_go */
//#define FS8X_FS_TM_DMUX_OV4_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< rstb_incr_flt */
//#define FS8X_FS_TM_DMUX_OV4_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< otp_corrupt */
//#define FS8X_FS_TM_DMUX_OV4_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV4_SEL_SHIFT) /*!< i2c_bad_rqst */
//
//#define FS8X_FS_TM_DMUX_OV5_SEL_0        (0x0000U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< vmon4_ov_d */
//#define FS8X_FS_TM_DMUX_OV5_SEL_1        (0x0001U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< to_func_obs_vmon4_ov */
//#define FS8X_FS_TM_DMUX_OV5_SEL_2        (0x0002U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< to_func_obs_vmon4_uv_n */
//#define FS8X_FS_TM_DMUX_OV5_SEL_3        (0x0003U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< spare[0] */
//#define FS8X_FS_TM_DMUX_OV5_SEL_4        (0x0004U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< state toogle */
//#define FS8X_FS_TM_DMUX_OV5_SEL_5        (0x0005U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< vmonx_ov_d_xor[0] ^ vmonx_uv_n_d_xor[0] ^ rstb_sense_d_xor ^ vdig_ov_d_xor */
//#define FS8X_FS_TM_DMUX_OV5_SEL_6        (0x0006U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< to_func_obs_ERRMON_failure */
//#define FS8X_FS_TM_DMUX_OV5_SEL_7        (0x0007U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< vdig_fs_porn */
//#define FS8X_FS_TM_DMUX_OV5_SEL_8        (0x0008U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< sck */
//#define FS8X_FS_TM_DMUX_OV5_SEL_9        (0x0009U << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< fs0b short2hi */
//#define FS8X_FS_TM_DMUX_OV5_SEL_10       (0x000AU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< SVS error */
//#define FS8X_FS_TM_DMUX_OV5_SEL_11       (0x000BU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< rstb_8sec_failure */
//#define FS8X_FS_TM_DMUX_OV5_SEL_12       (0x000CU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< errormon_err */
//#define FS8X_FS_TM_DMUX_OV5_SEL_13       (0x000DU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< svs_mode1p8 */
//#define FS8X_FS_TM_DMUX_OV5_SEL_14       (0x000EU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< reg_corrupt */
//#define FS8X_FS_TM_DMUX_OV5_SEL_15       (0x000FU << FS8X_FS_TM_DMUX_OV5_SEL_SHIFT) /*!< i2c_bad_crc */
//
///******************************************************************************/
///* FS_TM_MODES1 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_MODES1_ADDR           0x28U
//#define FS8X_FS_TM_MODES1_DEFAULT        0x0000U
//
//#define FS8X_FS_TM_TM_VMON_MUX_MASK      0x001FU /*!< Test Mode Vmon Mux */
//#define FS8X_FS_TM_TM_VDDIO_BRIDGE_MASK  0x0020U /*!< Test Mode VDDIO Bridge */
//#define FS8X_FS_TM_TM_DVS_REF_MASK       0x0040U /*!< Test Mode DVS Ref */
//#define FS8X_FS_TM_TM_FUSE_FS_MASK       0x0080U /*!< Test Mode Fuse */
//#define FS8X_FS_TM_TM_VBG2_MASK          0x0700U /*!< Test Mode VBG2 */
//#define FS8X_FS_TM_TM_VDIG_DIS_MASK      0x0800U /*!< Test Mode VDIG Dis */
//#define FS8X_FS_TM_DIS_CLK_MON_MASK      0x1000U /*!< Disable clock monitoring test mode */
//#define FS8X_FS_TM_FS_FUSE_VPP_EN_MASK   0x2000U /*!< Control the output pin ipg_fuse_vpp_en state */
//#define FS8X_FS_TM_TM_V5FS_CLAMP_MASK    0x4000U /*!< Test Mode V5FS Clamp */
//#define FS8X_FS_TM_FS_MASK_RST_MASK      0x8000U /*!< Dual TM effect: Mask POR effect / Reset LBIST Checker */
//
//#define FS8X_FS_TM_TM_VMON_MUX_SHIFT     0x0000U /*!< Test Mode Vmon Mux */
//#define FS8X_FS_TM_TM_VDDIO_BRIDGE_SHIFT 0x0005U /*!< Test Mode VDDIO Bridge */
//#define FS8X_FS_TM_TM_DVS_REF_SHIFT      0x0006U /*!< Test Mode DVS Ref */
//#define FS8X_FS_TM_TM_FUSE_FS_SHIFT      0x0007U /*!< Test Mode Fuse */
//#define FS8X_FS_TM_TM_VBG2_SHIFT         0x0008U /*!< Test Mode VBG2 */
//#define FS8X_FS_TM_TM_VDIG_DIS_SHIFT     0x000BU /*!< Test Mode VDIG Dis */
//#define FS8X_FS_TM_DIS_CLK_MON_SHIFT     0x000CU /*!< Disable clock monitoring test mode */
//#define FS8X_FS_TM_FS_FUSE_VPP_EN_SHIFT  0x000DU /*!< Control the output pin ipg_fuse_vpp_en state */
//#define FS8X_FS_TM_TM_V5FS_CLAMP_SHIFT   0x000EU /*!< Test Mode V5FS Clamp */
//#define FS8X_FS_TM_FS_MASK_RST_SHIFT     0x000FU /*!< Dual TM effect: Mask POR effect / Reset LBIST Checker */
//
//#define FS8X_FS_TM_TM_VDDIO_BRIDGE_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_VDDIO_BRIDGE_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_VDDIO_BRIDGE_ACTIVATED (0x0001U << FS8X_FS_TM_TM_VDDIO_BRIDGE_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_DVS_REF_NOT_DISABLED (0x0000U << FS8X_FS_TM_TM_DVS_REF_SHIFT) /*!< Not disabled */
//#define FS8X_FS_TM_TM_DVS_REF_DISABLED   (0x0001U << FS8X_FS_TM_TM_DVS_REF_SHIFT) /*!< Disabled */
//
//#define FS8X_FS_TM_TM_FUSE_FS_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_FUSE_FS_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_FUSE_FS_ACTIVATED  (0x0001U << FS8X_FS_TM_TM_FUSE_FS_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_VDIG_DIS_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_VDIG_DIS_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_VDIG_DIS_ACTIVATED (0x0001U << FS8X_FS_TM_TM_VDIG_DIS_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_DIS_CLK_MON_NOT_DISABLED (0x0000U << FS8X_FS_TM_DIS_CLK_MON_SHIFT) /*!< Not disabled */
//#define FS8X_FS_TM_DIS_CLK_MON_DISABLED  (0x0001U << FS8X_FS_TM_DIS_CLK_MON_SHIFT) /*!< Disabled */
//
//#define FS8X_FS_TM_FS_FUSE_VPP_EN_SET_ZERO (0x0000U << FS8X_FS_TM_FS_FUSE_VPP_EN_SHIFT) /*!< Set to 0 */
//#define FS8X_FS_TM_FS_FUSE_VPP_EN_SET_ONE (0x0001U << FS8X_FS_TM_FS_FUSE_VPP_EN_SHIFT) /*!< Set to 1 */
//
//#define FS8X_FS_TM_TM_V5FS_CLAMP_NOT_DISABLED (0x0000U << FS8X_FS_TM_TM_V5FS_CLAMP_SHIFT) /*!< Not disabled */
//#define FS8X_FS_TM_TM_V5FS_CLAMP_DISABLED (0x0001U << FS8X_FS_TM_TM_V5FS_CLAMP_SHIFT) /*!< Disabled */
//
//#define FS8X_FS_TM_FS_MASK_RST_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_FS_MASK_RST_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_FS_MASK_RST_ACTIVATED (0x0001U << FS8X_FS_TM_FS_MASK_RST_SHIFT) /*!< activated */
//
///******************************************************************************/
///* FS_TM_MODES2 - Type: RW                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_MODES2_ADDR           0x29U
//#define FS8X_FS_TM_MODES2_DEFAULT        0x0000U
//
//#define FS8X_FS_TM_TM_BG2_TRIMX10_MASK   0x0001U /*!< Test Mode BG2_TRIMX10 */
//#define FS8X_FS_TM_TM_ABIST1_FAIL_STATE_MASK 0x0002U /*!< TM ABIST Fail STATE Backup. When set, the failing state backuped value can be read back in the ABIST FSM State field. */
//#define FS8X_FS_TM_TM_ABIST1_NO_FAIL_MASK 0x0004U /*!< TM ABIST No Fail Mode. Enable the No Fail mode. In this mode the fails are ignored and the ABIST will run until it ends up into the PASS state. This mode can be used as a skip mode of the ABIST (ABIST will be run anyway). Also, this mode can be combined with the Step mode. */
//#define FS8X_FS_TM_TM_ABIST1_STEP_MODE_MASK 0x0008U /*!< TM ABIST Step Mode. Enable the Step by Step mode. In this mode, the ABIST FSM will wait for a Next Step command to move to next step. This test mode can be combined with the ""No Fail mode"" to mask potential failure and thus force the ABIST FSM to go through all its states. */
//#define FS8X_FS_TM_TM_ABIST1_NXT_STEP_MASK 0x0010U /*!< Test Mode ABIST Step Mode Next Step. Only valid if Step mode is activated. Writting a one in this bit field will make the ABIST FSM to perform inputs check then avdvance to next state. Note: Test mode configuration must be wrtitten on each write access to Next Step bit in order to keep the selected test modes activated. */
//#define FS8X_FS_TM_TM_ABIST2_FAIL_STATE_MASK 0x0020U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_NO_FAIL_MASK 0x0040U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_STEP_MODE_MASK 0x0080U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_NXT_STEP_MASK 0x0100U /*!< N/A */
//#define FS8X_FS_TM_FS_MASK_UVOV_MASK     0x0200U /*!< Mask any UV/OV effect */
//#define FS8X_FS_TM_FS_VCOREMON_EN_MASK   0x0400U /*!< Test Mode Control VCORE VMON Enable */
//#define FS8X_FS_TM_FS_VDDIOMON_EN_MASK   0x0800U /*!< Test Mode Control VDDIO VMON Enable */
//#define FS8X_FS_TM_DIS_LBIST_CHECKER_MASK 0x1000U /*!< Test Mode to disable the lbist checker effect in case of failure (release safety pin lock) - must be combined with DIS_LBIST_CHECKER_NOT bit to be effective */
//#define FS8X_FS_TM_FS_EXT_CLK_MASK       0x4000U /*!< Take control of the clock oscillateur source */
//#define FS8X_FS_TM_FS_RINGO_EN_MASK      0x8000U /*!< N/A */
//
//#define FS8X_FS_TM_TM_BG2_TRIMX10_SHIFT  0x0000U /*!< Test Mode BG2_TRIMX10 */
//#define FS8X_FS_TM_TM_ABIST1_FAIL_STATE_SHIFT 0x0001U /*!< TM ABIST Fail STATE Backup. When set, the failing state backuped value can be read back in the ABIST FSM State field. */
//#define FS8X_FS_TM_TM_ABIST1_NO_FAIL_SHIFT 0x0002U /*!< TM ABIST No Fail Mode. Enable the No Fail mode. In this mode the fails are ignored and the ABIST will run until it ends up into the PASS state. This mode can be used as a skip mode of the ABIST (ABIST will be run anyway). Also, this mode can be combined with the Step mode. */
//#define FS8X_FS_TM_TM_ABIST1_STEP_MODE_SHIFT 0x0003U /*!< TM ABIST Step Mode. Enable the Step by Step mode. In this mode, the ABIST FSM will wait for a Next Step command to move to next step. This test mode can be combined with the ""No Fail mode"" to mask potential failure and thus force the ABIST FSM to go through all its states. */
//#define FS8X_FS_TM_TM_ABIST1_NXT_STEP_SHIFT 0x0004U /*!< Test Mode ABIST Step Mode Next Step. Only valid if Step mode is activated. Writting a one in this bit field will make the ABIST FSM to perform inputs check then avdvance to next state. Note: Test mode configuration must be wrtitten on each write access to Next Step bit in order to keep the selected test modes activated. */
//#define FS8X_FS_TM_TM_ABIST2_FAIL_STATE_SHIFT 0x0005U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_NO_FAIL_SHIFT 0x0006U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_STEP_MODE_SHIFT 0x0007U /*!< N/A */
//#define FS8X_FS_TM_TM_ABIST2_NXT_STEP_SHIFT 0x0008U /*!< N/A */
//#define FS8X_FS_TM_FS_MASK_UVOV_SHIFT    0x0009U /*!< Mask any UV/OV effect */
//#define FS8X_FS_TM_FS_VCOREMON_EN_SHIFT  0x000AU /*!< Test Mode Control VCORE VMON Enable */
//#define FS8X_FS_TM_FS_VDDIOMON_EN_SHIFT  0x000BU /*!< Test Mode Control VDDIO VMON Enable */
//#define FS8X_FS_TM_DIS_LBIST_CHECKER_SHIFT 0x000CU /*!< Test Mode to disable the lbist checker effect in case of failure (release safety pin lock) - must be combined with DIS_LBIST_CHECKER_NOT bit to be effective */
//#define FS8X_FS_TM_FS_EXT_CLK_SHIFT      0x000EU /*!< Take control of the clock oscillateur source */
//#define FS8X_FS_TM_FS_RINGO_EN_SHIFT     0x000FU /*!< N/A */
//
//#define FS8X_FS_TM_TM_BG2_TRIMX10_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_BG2_TRIMX10_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_BG2_TRIMX10_ACTIVATED (0x0001U << FS8X_FS_TM_TM_BG2_TRIMX10_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_ABIST1_FAIL_STATE_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_ABIST1_FAIL_STATE_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_ABIST1_FAIL_STATE_ACTIVATED (0x0001U << FS8X_FS_TM_TM_ABIST1_FAIL_STATE_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_ABIST1_NO_FAIL_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_ABIST1_NO_FAIL_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_ABIST1_NO_FAIL_ACTIVATED (0x0001U << FS8X_FS_TM_TM_ABIST1_NO_FAIL_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_ABIST1_STEP_MODE_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_TM_ABIST1_STEP_MODE_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_TM_ABIST1_STEP_MODE_ACTIVATED (0x0001U << FS8X_FS_TM_TM_ABIST1_STEP_MODE_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_TM_ABIST1_NXT_STEP_NO_EFFECT (0x0000U << FS8X_FS_TM_TM_ABIST1_NXT_STEP_SHIFT) /*!< No effect */
//#define FS8X_FS_TM_TM_ABIST1_NXT_STEP_PERFORM_ABIST_THEN_MOVE_ (0x0001U << FS8X_FS_TM_TM_ABIST1_NXT_STEP_SHIFT) /*!< Perform ABIST check then move to next ABIST FSM state */
//
//#define FS8X_FS_TM_TM_ABIST2_FAIL_STATE_NA (0x0000U << FS8X_FS_TM_TM_ABIST2_FAIL_STATE_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_TM_ABIST2_NO_FAIL_NA  (0x0000U << FS8X_FS_TM_TM_ABIST2_NO_FAIL_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_TM_ABIST2_STEP_MODE_NA (0x0000U << FS8X_FS_TM_TM_ABIST2_STEP_MODE_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_TM_ABIST2_NXT_STEP_NA (0x0000U << FS8X_FS_TM_TM_ABIST2_NXT_STEP_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_FS_MASK_UVOV_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_FS_MASK_UVOV_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_FS_MASK_UVOV_ACTIVATED (0x0001U << FS8X_FS_TM_FS_MASK_UVOV_SHIFT) /*!< All UV/OV flag effect are masked */
//
//#define FS8X_FS_TM_FS_VCOREMON_EN_NOT_ENABLED (0x0000U << FS8X_FS_TM_FS_VCOREMON_EN_SHIFT) /*!< Not enabled */
//#define FS8X_FS_TM_FS_VCOREMON_EN_ENABLED (0x0001U << FS8X_FS_TM_FS_VCOREMON_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_TM_FS_VDDIOMON_EN_NOT_ENABLED (0x0000U << FS8X_FS_TM_FS_VDDIOMON_EN_SHIFT) /*!< Not enabled */
//#define FS8X_FS_TM_FS_VDDIOMON_EN_ENABLED (0x0001U << FS8X_FS_TM_FS_VDDIOMON_EN_SHIFT) /*!< Enabled */
//
//#define FS8X_FS_TM_DIS_LBIST_CHECKER_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_DIS_LBIST_CHECKER_SHIFT) /*!< Not activated */
//#define FS8X_FS_TM_DIS_LBIST_CHECKER_ACTIVATED (0x0001U << FS8X_FS_TM_DIS_LBIST_CHECKER_SHIFT) /*!< activated */
//
//#define FS8X_FS_TM_FS_EXT_CLK_OSCILLATOR (0x0000U << FS8X_FS_TM_FS_EXT_CLK_SHIFT) /*!< Oscillaltor is the clock source */
//#define FS8X_FS_TM_FS_EXT_CLK_SPI_CLK    (0x0001U << FS8X_FS_TM_FS_EXT_CLK_SHIFT) /*!< SPI_CLK pad is the clock source */
//
//#define FS8X_FS_TM_FS_RINGO_EN_NA        (0x0000U << FS8X_FS_TM_FS_RINGO_EN_SHIFT) /*!< N/A */
//
///******************************************************************************/
///* FS_TM_STATUS1 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS1_ADDR          0x2AU
//#define FS8X_FS_TM_STATUS1_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_FS_MASK_RST_SET_MASK  0x0001U /*!< Mask Reset Test Mode status */
//#define FS8X_FS_TM_FS_TM_ENTRY_CURR_STATE_MASK 0x1E00U
//#define FS8X_FS_TM_LBIST_CHKR_DONE_MASK  0x2000U /*!< Embedded LBIST Done flag indication (lbist has run and completed) */
//#define FS8X_FS_TM_LBIST_CHKR_FAIL_MASK  0x4000U /*!< LBIST Fail flag indication */
//#define FS8X_FS_TM_LBIST_CHKR_OK_MASK    0x8000U /*!< LBIST Checker General OK flag indication unlock FailSafe pins if set high) */
//
//#define FS8X_FS_TM_FS_MASK_RST_SET_SHIFT 0x0000U /*!< Mask Reset Test Mode status */
//#define FS8X_FS_TM_FS_TM_ENTRY_CURR_STATE_SHIFT 0x0005U
//#define FS8X_FS_TM_LBIST_CHKR_DONE_SHIFT 0x000DU /*!< Embedded LBIST Done flag indication (lbist has run and completed) */
//#define FS8X_FS_TM_LBIST_CHKR_FAIL_SHIFT 0x000EU /*!< LBIST Fail flag indication */
//#define FS8X_FS_TM_LBIST_CHKR_OK_SHIFT   0x000FU /*!< LBIST Checker General OK flag indication unlock FailSafe pins if set high) */
//
//#define FS8X_FS_TM_FS_MASK_RST_SET_NOT_ACTIVATED (0x0000U << FS8X_FS_TM_FS_MASK_RST_SET_SHIFT) /*!< Mask Reset Test mode not activated */
//#define FS8X_FS_TM_FS_MASK_RST_SET_ACTIVATED (0x0001U << FS8X_FS_TM_FS_MASK_RST_SET_SHIFT) /*!< Mask Reset Test mode activated */
//
//#define FS8X_FS_TM_LBIST_CHKR_DONE_NOT_DONE (0x0000U << FS8X_FS_TM_LBIST_CHKR_DONE_SHIFT) /*!< Not done */
//#define FS8X_FS_TM_LBIST_CHKR_DONE_DONE  (0x0001U << FS8X_FS_TM_LBIST_CHKR_DONE_SHIFT) /*!< Done */
//
//#define FS8X_FS_TM_LBIST_CHKR_FAIL_NO_FAILURE (0x0000U << FS8X_FS_TM_LBIST_CHKR_FAIL_SHIFT) /*!< No fail reported */
//#define FS8X_FS_TM_LBIST_CHKR_FAIL_FAILURE (0x0001U << FS8X_FS_TM_LBIST_CHKR_FAIL_SHIFT) /*!< Failure is reported */
//
//#define FS8X_FS_TM_LBIST_CHKR_OK_NOT_OK  (0x0000U << FS8X_FS_TM_LBIST_CHKR_OK_SHIFT) /*!< Not ok (either LBIST has not run or has failed) - Safety pins are locked */
//#define FS8X_FS_TM_LBIST_CHKR_OK_OK      (0x0001U << FS8X_FS_TM_LBIST_CHKR_OK_SHIFT) /*!< OK (LBIST as run and passed or disaled by secured test mode) - FailSafe pins are unlocked */
//
///******************************************************************************/
///* FS_TM_STATUS2 - Type: RW                                                   */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS2_ADDR          0x2BU
//#define FS8X_FS_TM_STATUS2_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_ABIST1_CURR_STATE_MASK 0x001FU /*!< ABIST1 FSM current state */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_MASK 0x03E0U /*!< ABIST2 FSM current state */
//
//#define FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT 0x0000U /*!< ABIST1 FSM current state */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT 0x0005U /*!< ABIST2 FSM current state */
//
//#define FS8X_FS_TM_ABIST1_CURR_STATE_IDLE (0x0001U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< IDLE */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_WAIT (0x0002U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< WAIT */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK0 (0x0003U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK0 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP0 (0x0004U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP0 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK1 (0x0005U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK1 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK2 (0x0006U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK2 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP1 (0x0007U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP1 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK3 (0x0008U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK3 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK4 (0x0009U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK4 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP2 (0x000AU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP2 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK5 (0x000BU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK5 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK6 (0x000CU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK6 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP3 (0x000DU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP3 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK7 (0x000EU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK7 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK8 (0x000FU << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK8 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP4 (0x0010U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP4 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK9 (0x0011U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK9 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK10 (0x0012U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK10 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_JUMP5 (0x0013U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< JUMP5 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK11 (0x0014U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK11 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK12 (0x0015U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK12 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_CHECK13 (0x0016U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< CHECK13 */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_FAIL (0x0017U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< FAIL */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_PASS (0x0018U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< PASS */
//#define FS8X_FS_TM_ABIST1_CURR_STATE_POST_FAIL (0x0019U << FS8X_FS_TM_ABIST1_CURR_STATE_SHIFT) /*!< POST_FAIL */
//
//#define FS8X_FS_TM_ABIST2_CURR_STATE_IDLE (0x0001U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< IDLE */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_WAIT (0x0002U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< WAIT */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP0 (0x0003U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP0 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK0 (0x0004U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK0 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK1 (0x0005U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK1 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP1 (0x0006U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP1 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK2 (0x0007U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK2 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK3 (0x0008U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK3 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP2 (0x0009U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP2 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK4 (0x000AU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK4 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK5 (0x000BU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK5 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP3 (0x000CU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP3 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK6 (0x000DU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK6 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK7 (0x000EU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK7 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP4 (0x000FU << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP4 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK8 (0x0010U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK8 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK9 (0x0011U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK9 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_JUMP5 (0x0012U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< JUMP5 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK10 (0x0013U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK10 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK11 (0x0014U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK11 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_CHECK12 (0x0015U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< CHECK12 */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_FAIL (0x0016U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< FAIL */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_PASS (0x0017U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< PASS */
//#define FS8X_FS_TM_ABIST2_CURR_STATE_POST_FAIL (0x0018U << FS8X_FS_TM_ABIST2_CURR_STATE_SHIFT) /*!< POST_FAIL */
//
///******************************************************************************/
///* FS_TM_STATUS3 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS3_ADDR          0x2CU
//#define FS8X_FS_TM_STATUS3_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_ABIST1_FAIL_VECT_MASK 0xFFFFU /*!< ABIST1 Compare Vector */
//
//#define FS8X_FS_TM_ABIST1_FAIL_VECT_SHIFT 0x0000U /*!< ABIST1 Compare Vector */
//
///******************************************************************************/
///* FS_TM_STATUS4 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS4_ADDR          0x2DU
//#define FS8X_FS_TM_STATUS4_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_ABIST2_FAIL_VECT_MASK 0x0FFFU /*!< ABIST2 Compare Vector */
//
//#define FS8X_FS_TM_ABIST2_FAIL_VECT_SHIFT 0x0000U /*!< ABIST2 Compare Vector */
//
///******************************************************************************/
///* FS_TM_STATUS5 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS5_ADDR          0x2EU
//#define FS8X_FS_TM_STATUS5_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_VOTE_LBIST_CTRL_MASK  0x0001U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDDUR_MASK   0x0002U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDDATA_MASK  0x0004U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDRECOV_MASK 0x0008U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_FSM_MASK     0x0010U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDCYCLE_MASK 0x0020U /*!< N/A */
//#define FS8X_FS_TM_SVS_VOTE_ERROR_MASK   0x0040U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_MASK 0x0080U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ABIST2_VOTE_ERROR_MASK 0x0100U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ABIST1_VOTE_ERROR_MASK 0x0200U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ERRORMON_VOTE_ERROR_MASK 0x0400U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_MASK 0x0800U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_WDERRCNT_VOTE_ERROR_MASK 0x1000U /*!< Internal triplication voter error */
//
//#define FS8X_FS_TM_VOTE_LBIST_CTRL_SHIFT 0x0000U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDDUR_SHIFT  0x0001U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDDATA_SHIFT 0x0002U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDRECOV_SHIFT 0x0003U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_FSM_SHIFT    0x0004U /*!< N/A */
//#define FS8X_FS_TM_VOTE_ERR_WDCYCLE_SHIFT 0x0005U /*!< N/A */
//#define FS8X_FS_TM_SVS_VOTE_ERROR_SHIFT  0x0006U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_SHIFT 0x0007U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ABIST2_VOTE_ERROR_SHIFT 0x0008U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ABIST1_VOTE_ERROR_SHIFT 0x0009U /*!< Internal triplication voter error */
//#define FS8X_FS_TM_ERRORMON_VOTE_ERROR_SHIFT 0x000AU /*!< Internal triplication voter error */
//#define FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_SHIFT 0x000BU /*!< Internal triplication voter error */
//#define FS8X_FS_TM_WDERRCNT_VOTE_ERROR_SHIFT 0x000CU /*!< Internal triplication voter error */
//
//#define FS8X_FS_TM_VOTE_LBIST_CTRL_NA    (0x0000U << FS8X_FS_TM_VOTE_LBIST_CTRL_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_VOTE_ERR_WDDUR_NA     (0x0000U << FS8X_FS_TM_VOTE_ERR_WDDUR_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_VOTE_ERR_WDDATA_NA    (0x0000U << FS8X_FS_TM_VOTE_ERR_WDDATA_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_VOTE_ERR_WDRECOV_NA   (0x0000U << FS8X_FS_TM_VOTE_ERR_WDRECOV_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_VOTE_ERR_FSM_NA       (0x0000U << FS8X_FS_TM_VOTE_ERR_FSM_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_VOTE_ERR_WDCYCLE_NA   (0x0000U << FS8X_FS_TM_VOTE_ERR_WDCYCLE_SHIFT) /*!< N/A */
//
//#define FS8X_FS_TM_SVS_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_SVS_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_SVS_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_SVS_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_CRC_CHECK_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_ABIST2_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_ABIST2_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_ABIST2_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_ABIST2_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_ABIST1_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_ABIST1_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_ABIST1_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_ABIST1_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_ERRORMON_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_ERRORMON_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_ERRORMON_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_ERRORMON_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_FLTERRCNT_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
//#define FS8X_FS_TM_WDERRCNT_VOTE_ERROR_NO_DIFFERENCE (0x0000U << FS8X_FS_TM_WDERRCNT_VOTE_ERROR_SHIFT) /*!< No difference on the triplicated register detected */
//#define FS8X_FS_TM_WDERRCNT_VOTE_ERROR_MISMATCH (0x0001U << FS8X_FS_TM_WDERRCNT_VOTE_ERROR_SHIFT) /*!< At least one mismatch between the triplicated register detected */
//
///******************************************************************************/
///* FS_TM_STATUS6 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS6_ADDR          0x2FU
//#define FS8X_FS_TM_STATUS6_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_FS_SVS_MASK           0x00FFU /*!< Computed SVS value */
//
//#define FS8X_FS_TM_FS_SVS_SHIFT          0x0000U /*!< Computed SVS value */
//
///******************************************************************************/
///* FS_TM_STATUS7 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS7_ADDR          0x30U
//#define FS8X_FS_TM_STATUS7_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART3_MASK 0xFFFFU /*!< LBIST SIGNATURE Part3 from bit 63 downto bit 48 */
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART3_SHIFT 0x0000U /*!< LBIST SIGNATURE Part3 from bit 63 downto bit 48 */
//
///******************************************************************************/
///* FS_TM_STATUS8 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS8_ADDR          0x31U
//#define FS8X_FS_TM_STATUS8_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART2_MASK 0xFFFFU /*!< LBIST SIGNATURE Part2 from bit 47 downto bit 32 */
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART2_SHIFT 0x0000U /*!< LBIST SIGNATURE Part2 from bit 47 downto bit 32 */
//
///******************************************************************************/
///* FS_TM_STATUS9 - Type: R                                                    */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS9_ADDR          0x32U
//#define FS8X_FS_TM_STATUS9_DEFAULT       0x0000U
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART1_MASK 0xFFFFU /*!< LBIST SIGNATURE Part1 from bit 31 downto bit 16 */
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART1_SHIFT 0x0000U /*!< LBIST SIGNATURE Part1 from bit 31 downto bit 16 */
//
///******************************************************************************/
///* FS_TM_STATUS10 - Type: R                                                   */
///******************************************************************************/
//
//#define FS8X_FS_TM_STATUS10_ADDR         0x33U
//#define FS8X_FS_TM_STATUS10_DEFAULT      0x0000U
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART0_MASK 0xFFFFU /*!< LBIST SIGNATURE Part0 from bit 15 downto bit 0 */
//
//#define FS8X_FS_TM_LBIST_SIGNATURE_PART0_SHIFT 0x0000U /*!< LBIST SIGNATURE Part0 from bit 15 downto bit 0 */
//
//
//
#endif /* SBC_FS8X_MAP_H__ */
