/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2017                                                   */
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
/* Right to make changes                                                        */
/* NXP reserves the right to make changes without notice at any time.           */
/*                                                                              */
/* Content correctness                                                          */
/* NXP guaratee the  correctness of this  header  file  against  the reference  */
/* TEF810x_Registermap_v28.xlsx. This header file correctness is guaranteed      */
/* through a header file validation approach. The methods used and the          */
/* validation results will be shared  to the customer to use it as an evidence  */
/* in their safety case                                                         */
/*------------------------------------------------------------------------------*/
/**
* @NXP_TEF810X_CentralControl.h
*/
#ifndef NXP_TEF810X_CENTRALCONTROL_H
#define NXP_TEF810X_CENTRALCONTROL_H
#include "Std_Types.h"

#define CENTRAL_CONTROL_MODULE_ADDRESS 0x00
/**
*NXP_TEF810X_MOD00_READYINT_PADCONTROL_U16
* RegisterName: MOD00_ReadyInt_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000321
*/
#define NXP_TEF810X_MOD00_READYINT_PADCONTROL_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16
* RegisterName: MOD00_Chirp_Start_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00000321
*/
#define NXP_TEF810X_MOD00_CHIRP_START_PADCONTROL_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD00_ERROR_N_PADCONTROL_U16
* RegisterName: MOD00_Error_n_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000321
*/
#define NXP_TEF810X_MOD00_ERROR_N_PADCONTROL_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD00_ERROR_RESET_PADCONTROL_U16
* RegisterName: MOD00_Error_Reset_PadControl
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x00000321
*/
#define NXP_TEF810X_MOD00_ERROR_RESET_PADCONTROL_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD00_TX1_PADCONTROL_U16
* RegisterName: MOD00_TX1_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x00001321
*/
#define NXP_TEF810X_MOD00_TX1_PADCONTROL_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD00_TX2_PADCONTROL_U16
* RegisterName: MOD00_TX2_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x00001321
*/
#define NXP_TEF810X_MOD00_TX2_PADCONTROL_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD00_TX3_PADCONTROL_U16
* RegisterName: MOD00_TX3_PadControl
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x00001321
*/
#define NXP_TEF810X_MOD00_TX3_PADCONTROL_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD00_MISO_PADCONTROL_U16
* RegisterName: MOD00_MISO_padControl
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x00000330
*/
#define NXP_TEF810X_MOD00_MISO_PADCONTROL_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD00_LDO_SERIALISER_SER_CONTROL_U16
* RegisterName: MOD00_Ldo_Serialiser_Ser_Control
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_LDO_SERIALISER_SER_CONTROL_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD00_LDO_SERIALISER_CSI2_CONTROL_U16
* RegisterName: MOD00_Ldo_Serialiser_csi2_Control
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_LDO_SERIALISER_CSI2_CONTROL_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD00_LDO_ADC_CONTROL_U16
* RegisterName: MOD00_Ldo_Adc_Control
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_LDO_ADC_CONTROL_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16
* RegisterName: MOD00_Ldo_Ssbmod_Control
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_LDO_SSBMOD_CONTROL_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD00_ATB1_EN_REGISTER_U16
* RegisterName: MOD00_ATB1_en_register
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_ATB1_EN_REGISTER_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD00_ATB1_AC_EN_REGISTER_U16
* RegisterName: MOD00_ATB1_ac_en_register
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x01110000
*/
#define NXP_TEF810X_MOD00_ATB1_AC_EN_REGISTER_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD00_ATB2_EN_REGISTER_U16
* RegisterName: MOD00_ATB2_en_register
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_ATB2_EN_REGISTER_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD00_ATB2_AC_EN_REGISTER_U16
* RegisterName: MOD00_ATB2_ac_en_register
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00110000
*/
#define NXP_TEF810X_MOD00_ATB2_AC_EN_REGISTER_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_ENABLE_U16
* RegisterName: MOD00_dynamic_power_control_enable
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_ENABLE_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_DELAY_U16
* RegisterName: MOD00_dynamic_power_control_delay
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x0000FFFF
*/
#define NXP_TEF810X_MOD00_DYNAMIC_POWER_CONTROL_DELAY_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16
* RegisterName: MOD00_serialiser_mode_sel
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_SERIALISER_MODE_SEL_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD00_READY_INT_CONTROL_U16
* RegisterName: MOD00_Ready_Int_Control
* AccessMode: READWRITE
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x01100090
*/
#define NXP_TEF810X_MOD00_READY_INT_CONTROL_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD00_INT_ENABLE_U16
* RegisterName: MOD00_INT_ENABLE
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_INT_ENABLE_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD00_INT_CLR_U16
* RegisterName: MOD00_INT_CLR
* AccessMode: WRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_INT_CLR_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD00_INT_SET_U16
* RegisterName: MOD00_INT_SET
* AccessMode: WRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_INT_SET_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16
* RegisterName: MOD00_ip_level_clock_enable
* AccessMode: READWRITE
* AddressRange: 0x0064 - 0x0068
* ResetValue: 0x01800000
*/
#define NXP_TEF810X_MOD00_IP_LEVEL_CLOCK_ENABLE_U16 (uint16)0x0064
/**
*NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16
* RegisterName: MOD00_ip_level_pon_enable
* AccessMode: READWRITE
* AddressRange: 0x0068 - 0x006C
* ResetValue: 0x01800000
*/
#define NXP_TEF810X_MOD00_IP_LEVEL_PON_ENABLE_U16 (uint16)0x0068
/**
*NXP_TEF810X_MOD00_RESET_CONTROL_U16
* RegisterName: MOD00_reset_control
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x01800000
*/
#define NXP_TEF810X_MOD00_RESET_CONTROL_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16
* RegisterName: MOD00_functional_reset_control
* AccessMode: READWRITE
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x01800000
*/
#define NXP_TEF810X_MOD00_FUNCTIONAL_RESET_CONTROL_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD00_INT_RAW_STATUS_U16
* RegisterName: MOD00_INT_RAW_STATUS
* AccessMode: READ
* AddressRange: 0x0078 - 0x007C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_INT_RAW_STATUS_U16 (uint16)0x0078
/**
*NXP_TEF810X_MOD00_INT_MASKED_STATUS_U16
* RegisterName: MOD00_INT_MASKED_STATUS
* AccessMode: READ
* AddressRange: 0x007C - 0x0080
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_INT_MASKED_STATUS_U16 (uint16)0x007C
/**
*NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16
* RegisterName: MOD00_scratch_register1
* AccessMode: READWRITE
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_SCRATCH_REGISTER1_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD00_SCRATCH_REGISTER8_U16
* RegisterName: MOD00_scratch_register8
* AccessMode: READWRITE
* AddressRange: 0x009C - 0x00A0
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD00_SCRATCH_REGISTER8_U16 (uint16)0x009C
/**
*NXP_TEF810X_MOD00_MODULEID_U16
* RegisterName: MOD00_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00002301
*/
#define NXP_TEF810X_MOD00_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod00_READYINT_PADCONTROLBits_t
* RegisterName: ReadyInt_PadControl
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: readyint_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ReadyintMfioEn: 1;        /*## attribute ReadyintMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: readyint_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ReadyintMfioEnzi: 1;        /*## attribute ReadyintMfioEnzi */
   /**
	* BitsName: readyint_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ReadyintMfioEpun: 1;        /*## attribute ReadyintMfioEpun */
   /**
	* BitsName: readyint_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ReadyintMfioEpd: 1;        /*## attribute ReadyintMfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: readyint_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ReadyintMfioEhs0: 1;        /*## attribute ReadyintMfioEhs0 */
   /**
	* BitsName: readyint_mfio_ehs1
	* Description: IO Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ReadyintMfioEhs1: 1;        /*## attribute ReadyintMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 22;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod00_ReadyintPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_CHIRP_START_PADCONTROLBits_t
* RegisterName: Chirp_Start_PadControl
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: chirpstart_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ChirpstartMfioEn: 1;        /*## attribute ChirpstartMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: chirpstart_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ChirpstartMfioEnzi: 1;        /*## attribute ChirpstartMfioEnzi */
   /**
	* BitsName: chirpstart_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ChirpstartMfioEpun: 1;        /*## attribute ChirpstartMfioEpun */
   /**
	* BitsName: chirpstart_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ChirpstartMfioEpd: 1;        /*## attribute ChirpstartMfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: chirpstart_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ChirpstartMfioEhs0: 1;        /*## attribute ChirpstartMfioEhs0 */
   /**
	* BitsName: chirpstart_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ChirpstartMfioEhs1: 1;        /*## attribute ChirpstartMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 22;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod00_ChirpStartPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_ERROR_N_PADCONTROLBits_t
* RegisterName: Error_n_PadControl
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: error_n_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ErrorNMfioEn: 1;        /*## attribute ErrorNMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: error_n_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ErrorNMfioEnzi: 1;        /*## attribute ErrorNMfioEnzi */
   /**
	* BitsName: error_n_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ErrorNMfioEpun: 1;        /*## attribute ErrorNMfioEpun */
   /**
	* BitsName: error_n_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ErrorNMfioEpd: 1;        /*## attribute ErrorNMfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: error_n_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ErrorNMfioEhs0: 1;        /*## attribute ErrorNMfioEhs0 */
   /**
	* BitsName: error_n_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ErrorNMfioEhs1: 1;        /*## attribute ErrorNMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 22;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod00_ErrorNPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_ERROR_RESET_PADCONTROLBits_t
* RegisterName: Error_Reset_PadControl
* 
* AddressRange: 0xREADWRITE - 0x00C
* ResetValue: 0x00000010
*/
typedef struct  {
   /**
	* BitsName: error_reset_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* In a functional context the O/P is never enabled
	*/
    uint32 ErrorResetMfioEn: 1;        /*## attribute ErrorResetMfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: error_reset_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ErrorResetMfioEnzi: 1;        /*## attribute ErrorResetMfioEnzi */
   /**
	* BitsName: error_reset_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ErrorResetMfioEpun: 1;        /*## attribute ErrorResetMfioEpun */
   /**
	* BitsName: error_reset_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ErrorResetMfioEpd: 1;        /*## attribute ErrorResetMfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: error_reset_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ErrorResetMfioEhs0: 1;        /*## attribute ErrorResetMfioEhs0 */
   /**
	* BitsName: error_reset_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ErrorResetMfioEhs1: 1;        /*## attribute ErrorResetMfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 22;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod00_ErrorResetPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_TX1_PADCONTROLBits_t
* RegisterName: TX1_PadControl
* 
* AddressRange: 0xREADWRITE - 0x010
* ResetValue: 0x00000014
*/
typedef struct  {
   /**
	* BitsName: tx1_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx1MfioEn: 1;        /*## attribute Tx1MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: tx1_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx1MfioEnzi: 1;        /*## attribute Tx1MfioEnzi */
   /**
	* BitsName: tx1_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx1MfioEpun: 1;        /*## attribute Tx1MfioEpun */
   /**
	* BitsName: tx1_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx1MfioEpd: 1;        /*## attribute Tx1MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: tx1_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx1MfioEhs0: 1;        /*## attribute Tx1MfioEhs0 */
   /**
	* BitsName: tx1_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx1MfioEhs1: 1;        /*## attribute Tx1MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ps_tx1_ext_en
	* Description: Selection bit for routing tx1_ps pad input to ps_tx1_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx1_ext from CC will be tied to 0
	*/
    uint32 PsTx1ExtEn: 1;        /*## attribute PsTx1ExtEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_Tx1PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_TX2_PADCONTROLBits_t
* RegisterName: TX2_PadControl
* 
* AddressRange: 0xREADWRITE - 0x014
* ResetValue: 0x00000018
*/
typedef struct  {
   /**
	* BitsName: tx2_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx2MfioEn: 1;        /*## attribute Tx2MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: tx2_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx2MfioEnzi: 1;        /*## attribute Tx2MfioEnzi */
   /**
	* BitsName: tx2_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx2MfioEpun: 1;        /*## attribute Tx2MfioEpun */
   /**
	* BitsName: tx2_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx2MfioEpd: 1;        /*## attribute Tx2MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: tx2_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx2MfioEhs0: 1;        /*## attribute Tx2MfioEhs0 */
   /**
	* BitsName: tx2_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx2MfioEhs1: 1;        /*## attribute Tx2MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ps_tx2_ext_en
	* Description: Selection bit for routing tx2_ps pad input to ps_tx2_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx2_ext from CC will be tied to 0
	*/
    uint32 PsTx2ExtEn: 1;        /*## attribute PsTx2ExtEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_Tx2PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_TX3_PADCONTROLBits_t
* RegisterName: TX3_PadControl
* 
* AddressRange: 0xREADWRITE - 0x018
* ResetValue: 0x0000001C
*/
typedef struct  {
   /**
	* BitsName: tx3_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx3MfioEn: 1;        /*## attribute Tx3MfioEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: tx3_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx3MfioEnzi: 1;        /*## attribute Tx3MfioEnzi */
   /**
	* BitsName: tx3_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx3MfioEpun: 1;        /*## attribute Tx3MfioEpun */
   /**
	* BitsName: tx3_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx3MfioEpd: 1;        /*## attribute Tx3MfioEpd */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: tx3_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx3MfioEhs0: 1;        /*## attribute Tx3MfioEhs0 */
   /**
	* BitsName: tx3_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx3MfioEhs1: 1;        /*## attribute Tx3MfioEhs1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ps_tx3_ext_en
	* Description: Selection bit for routing tx3_ps pad input to ps_tx3_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx3_ext from CC will be tied to 0
	*/
    uint32 PsTx3ExtEn: 1;        /*## attribute PsTx3ExtEn */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 19;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_Tx3PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_MISO_PADCONTROLBits_t
* RegisterName: MISO_padControl
* 
* AddressRange: 0xREADWRITE - 0x01C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: miso_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 MisoMfioEnzi: 1;        /*## attribute MisoMfioEnzi */
   /**
	* BitsName: miso_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 MisoMfioEpun: 1;        /*## attribute MisoMfioEpun */
   /**
	* BitsName: msio_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 MsioMfioEpd: 1;        /*## attribute MsioMfioEpd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: miso_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 MisoMfioEhs0: 1;        /*## attribute MisoMfioEhs0 */
   /**
	* BitsName: miso_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 MisoMfioEhs1: 1;        /*## attribute MisoMfioEhs1 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 22;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_MisoPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_LDO_SERIALISER_SER_CONTROLBits_t
* RegisterName: Ldo_Serialiser_Ser_Control
* 
* AddressRange: 0xREADWRITE - 0x020
* ResetValue: 0x00000024
*/
typedef struct  {
   /**
	* BitsName: ldo_en_serialiser_ser
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSerialiserSer: 1;        /*## attribute LdoEnSerialiserSer */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_serialiser_ser
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSerialiserSer: 5;        /*## attribute LdoSelVoutSerialiserSer */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod00_LdoSerialiserSerControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LDO_SERIALISER_CSI2_CONTROLBits_t
* RegisterName: Ldo_Serialiser_csi2_Control
* 
* AddressRange: 0xREADWRITE - 0x024
* ResetValue: 0x00000028
*/
typedef struct  {
   /**
	* BitsName: ldo_en_serialiser_csi2
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSerialiserCsi2: 1;        /*## attribute LdoEnSerialiserCsi2 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_serialiser_csi2
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSerialiserCsi2: 5;        /*## attribute LdoSelVoutSerialiserCsi2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LDO_ADC_CONTROLBits_t
* RegisterName: Ldo_Adc_Control
* 
* AddressRange: 0xREADWRITE - 0x028
* ResetValue: 0x0000002C
*/
typedef struct  {
   /**
	* BitsName: ldo_en_adc
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnAdc: 1;        /*## attribute LdoEnAdc */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_adc
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutAdc: 5;        /*## attribute LdoSelVoutAdc */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod00_LdoAdcControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LDO_SSBMOD_CONTROLBits_t
* RegisterName: Ldo_Ssbmod_Control
* 
* AddressRange: 0xREADWRITE - 0x02C
* ResetValue: 0x00000030
*/
typedef struct  {
   /**
	* BitsName: ldo_en_ssbmod
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSsbmod: 1;        /*## attribute LdoEnSsbmod */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_ssbmod
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSsbmod: 5;        /*## attribute LdoSelVoutSsbmod */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod00_LdoSsbmodControlBits_t;
    /**
* Nxp_Tef810x_Mod00_ATB1_EN_REGISTERBits_t
* RegisterName: ATB1_en_register
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: atb1_set
	* Description: lvds (serilaizer) = 0x01
	* cif (serilaizer) = 0x01
	* csi2 (serilaizer) = 0x01
	* chirp_afc = 0x06
	* adc12 = 0x07
	* adc34 = 0x08
	* global_bias = 0x09
	* lo_interface = 0x0A
	* master_clock = 0x0C
	* rx1 = 0x0D
	* rx2 = 0x0E
	* rx3 = 0x0F
	* rx4 = 0x10
	* tx1 = 0x11
	* tx2 = 0x12
	* tx3 = 0x13
	* ssbmod = 0x14
	* global_ldo = 0x15
	* atb = 0x16
	*/
    uint32 Atb1Set: 8;        /*## attribute Atb1Set */
   /**
	* BitsName: atb1_en
	* Description: Enable DC Test Bus fro ATB1
	* atb1_en = 0 will disable DC test bus
	* atb1_en = 1 will enable DC test bus
	*/
    uint32 Atb1En: 1;        /*## attribute Atb1En */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_Atb1EnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_ATB1_AC_EN_REGISTERBits_t
* RegisterName: ATB1_ac_en_register
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: en_atb1_dc_to_int_180
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to DC_ATB1_180 ATB line
	*/
    uint32 EnAtb1DcToInt180: 1;        /*## attribute EnAtb1DcToInt180 */
   /**
	* BitsName: en_atb1_dc_to_int_0
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to DC_ATB1_0 ATB line
	*/
    uint32 EnAtb1DcToInt0: 1;        /*## attribute EnAtb1DcToInt0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: en_atb1_dc_int_180_to_pins
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to ATB1_180 pin
	*/
    uint32 EnAtb1DcInt180ToPins: 1;        /*## attribute EnAtb1DcInt180ToPins */
   /**
	* BitsName: en_atb1_dc_int_0_to_pins
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to ATB1_0 pin
	*/
    uint32 EnAtb1DcInt0ToPins: 1;        /*## attribute EnAtb1DcInt0ToPins */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb1_dc_int_180_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to GND
	*/
    uint32 EnAtb1DcInt180Gnd: 1;        /*## attribute EnAtb1DcInt180Gnd */
   /**
	* BitsName: en_atb1_dc_int_0_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to GND
	*/
    uint32 EnAtb1DcInt0Gnd: 1;        /*## attribute EnAtb1DcInt0Gnd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb1_dc_180_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_ATB1_180 to GND
	*/
    uint32 EnAtb1Dc180Gnd: 1;        /*## attribute EnAtb1Dc180Gnd */
   /**
	* BitsName: en_atb1_dc_0_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_ATB1_0 to GND
	*/
    uint32 EnAtb1Dc0Gnd: 1;        /*## attribute EnAtb1Dc0Gnd */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: en_atb1_adc_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects ADC1234_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1AdcAcGnd: 1;        /*## attribute EnAtb1AdcAcGnd */
   /**
	* BitsName: en_atb1_adc_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects ADC1234_ATB1 (0? & 180?) to ATB1 pins
	* (both dualADCs simultaneously)
	*/
    uint32 EnAtb1AdcAc: 1;        /*## attribute EnAtb1AdcAc */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: en_atb1_rx1_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects RX1_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1Rx1AcGnd: 1;        /*## attribute EnAtb1Rx1AcGnd */
   /**
	* BitsName: en_atb1_rx1_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects RX1_ATB1 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb1Rx1Ac: 1;        /*## attribute EnAtb1Rx1Ac */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
   /**
	* BitsName: en_atb1_ssbmod_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects SSBMOD_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1SsbmodAcGnd: 1;        /*## attribute EnAtb1SsbmodAcGnd */
   /**
	* BitsName: en_atb1_ssbmod_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects SSBMOD_ATB1 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb1SsbmodAc: 1;        /*## attribute EnAtb1SsbmodAc */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
   /**
	* BitsName: atb1_ext_in_en_ssbmod
	* Description: Handles AC switch in SSBMOD: 
	* connects SSBMOD AC input (0? & 180?) to SSBMOD_ATB1
	*/
    uint32 Atb1ExtInEnSsbmod: 1;        /*## attribute Atb1ExtInEnSsbmod */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
}Nxp_Tef810x_Mod00_Atb1AcEnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_ATB2_EN_REGISTERBits_t
* RegisterName: ATB2_en_register
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: atb2_set
	* Description: lvds (serilaizer) = 0x01
	* cif (serilaizer) = 0x01
	* csi2 (serilaizer) = 0x01
	* chirp_afc = 0x06
	* adc12 = 0x07
	* adc34 = 0x08
	* global_bias = 0x09
	* lo_interface = 0x0A
	* master_clock = 0x0C
	* rx1 = 0x0D
	* rx2 = 0x0E
	* rx3 = 0x0F
	* rx4 = 0x10
	* tx1 = 0x11
	* tx2 = 0x12
	* tx3 = 0x13
	* ssbmod = 0x14
	* global_ldo = 0x15
	* atb = 0x16
	*/
    uint32 Atb2Set: 8;        /*## attribute Atb2Set */
   /**
	* BitsName: atb2_en
	* Description: Enable DC Test Bus fro ATB2
	* atb2_en = 0 will disable DC test bus
	* atb2_en = 1 will enable DC test bus
	*/
    uint32 Atb2En: 1;        /*## attribute Atb2En */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_Atb2EnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_ATB2_AC_EN_REGISTERBits_t
* RegisterName: ATB2_ac_en_register
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: en_atb2_dc_to_int_180
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to DC_ATB2_180 ATB line
	*/
    uint32 EnAtb2DcToInt180: 1;        /*## attribute EnAtb2DcToInt180 */
   /**
	* BitsName: en_atb2_dc_to_int_0
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to DC_ATB2_0 ATB line
	*/
    uint32 EnAtb2DcToInt0: 1;        /*## attribute EnAtb2DcToInt0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: en_atb2_dc_int_180_to_pins
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to ATB2_180 pin
	*/
    uint32 EnAtb2DcInt180ToPins: 1;        /*## attribute EnAtb2DcInt180ToPins */
   /**
	* BitsName: en_atb2_dc_int_0_to_pins
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to ATB2_0 pin
	*/
    uint32 EnAtb2DcInt0ToPins: 1;        /*## attribute EnAtb2DcInt0ToPins */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb2_dc_int_180_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to GND
	*/
    uint32 EnAtb2DcInt180Gnd: 1;        /*## attribute EnAtb2DcInt180Gnd */
   /**
	* BitsName: en_atb2_dc_int_0_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to GND
	*/
    uint32 EnAtb2DcInt0Gnd: 1;        /*## attribute EnAtb2DcInt0Gnd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb2_dc_180_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_ATB2_180 to GND
	*/
    uint32 EnAtb2Dc180Gnd: 1;        /*## attribute EnAtb2Dc180Gnd */
   /**
	* BitsName: en_atb2_dc_0_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_ATB2_0 to GND
	*/
    uint32 EnAtb2Dc0Gnd: 1;        /*## attribute EnAtb2Dc0Gnd */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: en_atb2_rx234_ac_gnd
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects RX234_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb2Rx234AcGnd: 1;        /*## attribute EnAtb2Rx234AcGnd */
   /**
	* BitsName: en_atb2_rx234_ac
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects RX234_ATB1 (0? & 180?) to ATB1 pins 
	* (select RX2, RX3 or RX4 by own register space)
	*/
    uint32 EnAtb2Rx234Ac: 1;        /*## attribute EnAtb2Rx234Ac */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: en_atb2_ssbmod_ac_gnd
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects SSBMOD_ATB2 (0? & 180?) to GND
	*/
    uint32 EnAtb2SsbmodAcGnd: 1;        /*## attribute EnAtb2SsbmodAcGnd */
   /**
	* BitsName: en_atb2_ssbmod_ac
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects SSBMOD_ATB2 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb2SsbmodAc: 1;        /*## attribute EnAtb2SsbmodAc */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 6;        /*## attribute Reserved5 */
   /**
	* BitsName: atb2_ext_in_en_ssbmod
	* Description: Handles AC switch in SSBMOD: 
	* connects SSBMOD AC input (0? & 180?) to SSBMOD_ATB2
	*/
    uint32 Atb2ExtInEnSsbmod: 1;        /*## attribute Atb2ExtInEnSsbmod */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod00_Atb2AcEnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_DYNAMIC_POWER_CONTROL_ENABLEBits_t
* RegisterName: dynamic_power_control_enable
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: ser_dy_power_control
	* Description: Reserved
	* Leave as reset if not needed explicitly.
	*/
    uint32 SerDyPowerControl: 1;        /*## attribute SerDyPowerControl */
   /**
	* BitsName: ser_dy_clock_control
	* Description: 0: Serializer digital part not under dynamic power control (clock gating)
	* 1: Serializer digital part   clock  is  controlled dynamically
	* Leave as reset if not needed explicitly.
	*/
    uint32 SerDyClockControl: 1;        /*## attribute SerDyClockControl */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: chirp_dy_power_control
	* Description: 0: Chirp unit   is not under dynamic power control
	* 1: Chirp unit    power is  controlled dynamically
	*/
    uint32 ChirpDyPowerControl: 1;        /*## attribute ChirpDyPowerControl */
   /**
	* BitsName: adc_dy_power_control
	* Description: 0: ADC12 and ADC34 is not under dynamic power control
	* 1: ADC12 and ADC34  power is  controlled dynamically
	*/
    uint32 AdcDyPowerControl: 1;        /*## attribute AdcDyPowerControl */
   /**
	* BitsName: lo_interface_dy_power_control
	* Description: 0: LO Interface is not under dynamic power control
	* 1: LO Interface  power is  controlled dynamically
	*/
    uint32 LoInterfaceDyPowerControl: 1;        /*## attribute LoInterfaceDyPowerControl */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: rx1_dy_power_control
	* Description: 0: RX1  unit is not under dynamic power control
	* 1: RX1  power is  controlled dynamically
	*/
    uint32 Rx1DyPowerControl: 1;        /*## attribute Rx1DyPowerControl */
   /**
	* BitsName: rx2_dy_power_control
	* Description: 0: RX2  unit is not under dynamic power control
	* 1: RX2  power is  controlled dynamically
	*/
    uint32 Rx2DyPowerControl: 1;        /*## attribute Rx2DyPowerControl */
   /**
	* BitsName: rx3_dy_power_control
	* Description: 0: RX3  unit is not under dynamic power control
	* 1: RX3  power is  controlled dynamically
	*/
    uint32 Rx3DyPowerControl: 1;        /*## attribute Rx3DyPowerControl */
   /**
	* BitsName: rx4_dy_power_control
	* Description: 0: RX4  unit is not under dynamic power control
	* 1: RX4  power is  controlled dynamically
	*/
    uint32 Rx4DyPowerControl: 1;        /*## attribute Rx4DyPowerControl */
   /**
	* BitsName: tx1_dy_power_control
	* Description: 0: TX1  unit is not under dynamic power control
	* 1: TX1  power is  controlled dynamically
	*/
    uint32 Tx1DyPowerControl: 1;        /*## attribute Tx1DyPowerControl */
   /**
	* BitsName: tx2_dy_power_control
	* Description: 0: TX2  unit is not under dynamic power control
	* 1: TX2  power is  controlled dynamically
	*/
    uint32 Tx2DyPowerControl: 1;        /*## attribute Tx2DyPowerControl */
   /**
	* BitsName: tx3_dy_power_control
	* Description: 0: TX3 unit is not under dynamic power control
	* 1: TX3 power is  controlled dynamically
	*/
    uint32 Tx3DyPowerControl: 1;        /*## attribute Tx3DyPowerControl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: dy_power_mode_sel
	* Description: Decides the control signal for dynamic power control
	* 0: Dynamic power is  controlled at chirp sequence level
	* 1: Dynamic power is controlled at individual chirp 
	* 
	* An overriding option is provided to avoid disabling power for Chirp and ADC   when this bit is set to '1'. Meaning that  both for ADC and Chirp module the power control will be at chirp sequence level  and for the rest of the IP  the power control is at individual chirp lebel. Please refere to scratch_register8  for details
	* 
	* When individual  chirp level power control, then an additional setting is required  from timing engine. teh following register must be set to '1'
	* 
	* 
	* Register:  ( timing_engine().chirp_trigger_mode_control (0x38). chirp_power_mode(9)).
	* Leave as reset if not needed explicitly.
	*/
    uint32 DyPowerModeSel: 1;        /*## attribute DyPowerModeSel */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 15;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_DynamicPowerControlEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_DYNAMIC_POWER_CONTROL_DELAYBits_t
* RegisterName: dynamic_power_control_delay
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: dy_clkgate_delay_val
	* Description: Decides the dynamic power down  delay once the data acquisition is over.
	* 
	* 
	* This value has to be  minimum  equal to the chirp reset time duration
	*/
    uint32 DyClkgateDelayVal: 16;        /*## attribute DyClkgateDelayVal */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_DynamicPowerControlDelayBits_t;
    /**
* Nxp_Tef810x_Mod00_SERIALISER_MODE_SELBits_t
* RegisterName: serialiser_mode_sel
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: sw_ctrl_ser_mode_sel
	* Description: This register is a conditionally writable register
	* 01: CSI2 mode
	* 10: LVDS
	* 11: CIF
	* The serializer mode can also be controlled  through OTP.
	* If only one function is enabled by the OTP, then this register is only a read only register r.
	* If both LVDS and CIF is enabled, then bit '0'is writable.
	* If all are enabled, then this register is fully writable
	*/
    uint32 SwCtrlSerModeSel: 2;        /*## attribute SwCtrlSerModeSel */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_SerialiserModeSelBits_t;
    /**
* Nxp_Tef810x_Mod00_READY_INT_CONTROLBits_t
* RegisterName: Ready_Int_Control
* 
* AddressRange: 0xREADWRITE - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: ReadyInt_period
	* Description: Activation Period for Ready Interrupt based on 40MHz(25 ns -Xtal Clock) 
	* default: 3.6us(144). This period is applicable only for edge triggered interrupt mode.
	*/
    uint32 ReadyintPeriod: 8;        /*## attribute ReadyintPeriod */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: Interrupt_level_or_pulse
	* Description: 1: Edge triggered interrupt. Ready Interrupt is activated for the time period mentioned in the "ReadyInt_period" .              
	* 0: Level triggered interrupt. Once Ready Interrupt is activated, is cleared by MCU by writing through interrupt clear register
	*/
    uint32 InterruptLevelOrPulse: 1;        /*## attribute InterruptLevelOrPulse */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 7;        /*## attribute Reserved1 */
   /**
	* BitsName: interrupt_polarity
	* Description: 0 Active low interrupt
	*  1: Active High interrupt
	*/
    uint32 InterruptPolarity: 1;        /*## attribute InterruptPolarity */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 7;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod00_ReadyIntControlBits_t;
    /**
* Nxp_Tef810x_Mod00_INT_ENABLEBits_t
* RegisterName: INT_ENABLE
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: chirp_start_out_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 ChirpStartOutIntEn: 1;        /*## attribute ChirpStartOutIntEn */
   /**
	* BitsName: end_of_data_acq_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 EndOfDataAcqIntEn: 1;        /*## attribute EndOfDataAcqIntEn */
   /**
	* BitsName: end_of_data_tnfr_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 EndOfDataTnfrIntEn: 1;        /*## attribute EndOfDataTnfrIntEn */
   /**
	* BitsName: status_wdt_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 StatusWdtIntEn: 1;        /*## attribute StatusWdtIntEn */
   /**
	* BitsName: rtm_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 RtmIntEn: 1;        /*## attribute RtmIntEn */
   /**
	* BitsName: rf_powerdown_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 RfPowerdownIntEn: 1;        /*## attribute RfPowerdownIntEn */
   /**
	* BitsName: crc_error_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 CrcErrorIntEn: 1;        /*## attribute CrcErrorIntEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_IntEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_INT_CLRBits_t
* RegisterName: INT_CLR
* 
* AddressRange: 0xWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: chirp_start_out_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 ChirpStartOutIntClr: 1;        /*## attribute ChirpStartOutIntClr */
   /**
	* BitsName: end_of_data_acq_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 EndOfDataAcqIntClr: 1;        /*## attribute EndOfDataAcqIntClr */
   /**
	* BitsName: end_of_data_tnfr_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 EndOfDataTnfrIntClr: 1;        /*## attribute EndOfDataTnfrIntClr */
   /**
	* BitsName: status_wdt_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 StatusWdtIntClr: 1;        /*## attribute StatusWdtIntClr */
   /**
	* BitsName: rtm_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 RtmIntClr: 1;        /*## attribute RtmIntClr */
   /**
	* BitsName: rf_powerdown_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 RfPowerdownIntClr: 1;        /*## attribute RfPowerdownIntClr */
   /**
	* BitsName: crc_error_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 CrcErrorIntClr: 1;        /*## attribute CrcErrorIntClr */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_IntClrBits_t;
    /**
* Nxp_Tef810x_Mod00_INT_SETBits_t
* RegisterName: INT_SET
* 
* AddressRange: 0xWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: chirp_start_out_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 ChirpStartOutIntSet: 1;        /*## attribute ChirpStartOutIntSet */
   /**
	* BitsName: end_of_data_acq_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 EndOfDataAcqIntSet: 1;        /*## attribute EndOfDataAcqIntSet */
   /**
	* BitsName: end_of_data_tnfr_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 EndOfDataTnfrIntSet: 1;        /*## attribute EndOfDataTnfrIntSet */
   /**
	* BitsName: status_wdt_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 StatusWdtIntSet: 1;        /*## attribute StatusWdtIntSet */
   /**
	* BitsName: rtm_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 RtmIntSet: 1;        /*## attribute RtmIntSet */
   /**
	* BitsName: rf_powerdown_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 RfPowerdownIntSet: 1;        /*## attribute RfPowerdownIntSet */
   /**
	* BitsName: crc_error_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 CrcErrorIntSet: 1;        /*## attribute CrcErrorIntSet */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_IntSetBits_t;
    /**
* Nxp_Tef810x_Mod00_IP_LEVEL_CLOCK_ENABLEBits_t
* RegisterName: ip_level_clock_enable
* 
* AddressRange: 0xREADWRITE - 0x064
* ResetValue: 0x00000068
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: clk40_ser
	* Description: Enable  40 MHz  clock to serialzer (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ser: 1;        /*## attribute Clk40Ser */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: clk40_chirp
	* Description: Enable  40 MHz  clock to Chirp  (register access as well as functional clock to timing engine)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Chirp: 1;        /*## attribute Clk40Chirp */
   /**
	* BitsName: clk40_adc12
	* Description: Enable  40 MHz  clock to ADC 1&2  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Adc12: 1;        /*## attribute Clk40Adc12 */
   /**
	* BitsName: clk40_adc34
	* Description: Enable  40 MHz  clock to ADC 3&4  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Adc34: 1;        /*## attribute Clk40Adc34 */
   /**
	* BitsName: clk40_global_bias
	* Description: Enable  40 MHz  clock to global bias  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40GlobalBias: 1;        /*## attribute Clk40GlobalBias */
   /**
	* BitsName: clk40_lo_interface
	* Description: Enable  40 MHz  clock to LO interface  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40LoInterface: 1;        /*## attribute Clk40LoInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: clk40_master_clk
	* Description: Enable  40 MHz  clock to master clock   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40MasterClk: 1;        /*## attribute Clk40MasterClk */
   /**
	* BitsName: clk40_rx1
	* Description: Enable  40 MHz  clock to RX1   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx1: 1;        /*## attribute Clk40Rx1 */
   /**
	* BitsName: clk40_rx2
	* Description: Enable  40 MHz  clock to RX2   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx2: 1;        /*## attribute Clk40Rx2 */
   /**
	* BitsName: clk40_rx3
	* Description: Enable  40 MHz  clock to RX3   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx3: 1;        /*## attribute Clk40Rx3 */
   /**
	* BitsName: clk40_rx4
	* Description: Enable  40 MHz  clock to RX4   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx4: 1;        /*## attribute Clk40Rx4 */
   /**
	* BitsName: clk40_tx1
	* Description: Enable  40 MHz  clock to TX1   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx1: 1;        /*## attribute Clk40Tx1 */
   /**
	* BitsName: clk40_tx2
	* Description: Enable  40 MHz  clock to TX2   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx2: 1;        /*## attribute Clk40Tx2 */
   /**
	* BitsName: clk40_tx3
	* Description: Enable  40 MHz  clock to TX3   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx3: 1;        /*## attribute Clk40Tx3 */
   /**
	* BitsName: clk40_ssbmod
	* Description: Enable  40 MHz  clock to SSBMOD/RFBIST   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ssbmod: 1;        /*## attribute Clk40Ssbmod */
   /**
	* BitsName: clk40_global_ldo
	* Description: Enable  40 MHz  clock to global LDO (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40GlobalLdo: 1;        /*## attribute Clk40GlobalLdo */
   /**
	* BitsName: clk40_atb
	* Description: Enable  40 MHz  clock to ATB (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Atb: 1;        /*## attribute Clk40Atb */
   /**
	* BitsName: clk40_otp
	* Description: Enable  40 MHz  clock to OTP (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Otp: 1;        /*## attribute Clk40Otp */
   /**
	* BitsName: clk40_ism
	* Description: Enable  40 MHz  clock to ISM  (register/functional  access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ism: 1;        /*## attribute Clk40Ism */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 7;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_IpLevelClockEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_IP_LEVEL_PON_ENABLEBits_t
* RegisterName: ip_level_pon_enable
* 
* AddressRange: 0xREADWRITE - 0x068
* ResetValue: 0x0000006C
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: pon_ser
	* Description: Enable  power to Serialiser 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonSer: 1;        /*## attribute PonSer */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: pon_chirp
	* Description: Enable  power to Chirp 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonChirp: 1;        /*## attribute PonChirp */
   /**
	* BitsName: pon_adc12
	* Description: Enable  power to ADC 1&2 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonAdc12: 1;        /*## attribute PonAdc12 */
   /**
	* BitsName: pon_adc34
	* Description: Enable  power to ADC 3&4 
	* 0 : power not enabled
	* 1: power is enabled
	* 
	* This bit also controls the dynamic power as well as back ground calibration
	* On start up this must be set to '1'. After star up it is recommended to keep this bit '1' always.. The dynamic power is them managed through  hardware ( configuration through dynamic_power_control_enable register) . If hardware control is not used, then software can use this bit for any possible synamic power control at SW level ( not recommended)
	*/
    uint32 PonAdc34: 1;        /*## attribute PonAdc34 */
   /**
	* BitsName: pon_global_bias
	* Description: Enable  power to global bias 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonGlobalBias: 1;        /*## attribute PonGlobalBias */
   /**
	* BitsName: pon_lo_interface
	* Description: Enable  power to LO interface 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonLoInterface: 1;        /*## attribute PonLoInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: pon_master_clk
	* Description: Enable  power to Master_clk PLL
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonMasterClk: 1;        /*## attribute PonMasterClk */
   /**
	* BitsName: pon_rx1
	* Description: Enable  power to RX1  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx1: 1;        /*## attribute PonRx1 */
   /**
	* BitsName: pon_rx2
	* Description: Enable  power to RX2 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx2: 1;        /*## attribute PonRx2 */
   /**
	* BitsName: pon_rx3
	* Description: Enable  power to RX3 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx3: 1;        /*## attribute PonRx3 */
   /**
	* BitsName: pon_rx4
	* Description: Enable  power to RX4  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx4: 1;        /*## attribute PonRx4 */
   /**
	* BitsName: pon_tx1
	* Description: Enable  power to TX1  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx1: 1;        /*## attribute PonTx1 */
   /**
	* BitsName: pon_tx2
	* Description: Enable  power to TX2  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx2: 1;        /*## attribute PonTx2 */
   /**
	* BitsName: pon_tx3
	* Description: Enable  power to TX3  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx3: 1;        /*## attribute PonTx3 */
   /**
	* BitsName: pon_ssbmod
	* Description: Enable  power to SSBMOD/RFBIST  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonSsbmod: 1;        /*## attribute PonSsbmod */
   /**
	* BitsName: pon_global_ldo
	* Description: Has to be set as '1' for proper functioning of LDO. 
	* Even though Global LDO is enabled on powerup, pon_ldo enables measurement of LDO signals for ATB.
	* 0 : Global LDO is not enabled for ATB Measurement
	* 1 : Global LDO is enabled for ATB Measurement
	* 
	* For normal IP operation the default value is sufficient.
	*/
    uint32 PonGlobalLdo: 1;        /*## attribute PonGlobalLdo */
   /**
	* BitsName: pon_atb
	* Description: Enable  power to ATB 
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 PonAtb: 1;        /*## attribute PonAtb */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 7;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod00_IpLevelPonEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_RESET_CONTROLBits_t
* RegisterName: reset_control
* 
* AddressRange: 0xREADWRITE - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: reset_ser
	* Description: Reset serializer register space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetSer: 1;        /*## attribute ResetSer */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: reset_chirp
	* Description: Reset chirp register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetChirp: 1;        /*## attribute ResetChirp */
   /**
	* BitsName: reset_adc12
	* Description: Reset ADC12 register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAdc12: 1;        /*## attribute ResetAdc12 */
   /**
	* BitsName: reset_adc34
	* Description: Reset ADC34 register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAdc34: 1;        /*## attribute ResetAdc34 */
   /**
	* BitsName: reset_global_bias
	* Description: Reset global bias register space and function 
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetGlobalBias: 1;        /*## attribute ResetGlobalBias */
   /**
	* BitsName: reset_lo_interface
	* Description: Reset lo interface register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetLoInterface: 1;        /*## attribute ResetLoInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: reset_master_clk
	* Description: Reset MC register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetMasterClk: 1;        /*## attribute ResetMasterClk */
   /**
	* BitsName: reset_rx1
	* Description: Reset chirp RX1  register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx1: 1;        /*## attribute ResetRx1 */
   /**
	* BitsName: reset_rx2
	* Description: Reset chirp RX2  register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx2: 1;        /*## attribute ResetRx2 */
   /**
	* BitsName: reset_rx3
	* Description: Reset chirp RX3 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx3: 1;        /*## attribute ResetRx3 */
   /**
	* BitsName: reset_rx4
	* Description: Reset chirp  RX4 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx4: 1;        /*## attribute ResetRx4 */
   /**
	* BitsName: reset_tx1
	* Description: Reset chirp TX1 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx1: 1;        /*## attribute ResetTx1 */
   /**
	* BitsName: reset_tx2
	* Description: Reset chirp TX2 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx2: 1;        /*## attribute ResetTx2 */
   /**
	* BitsName: reset_tx3
	* Description: Reset chirp TX3 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx3: 1;        /*## attribute ResetTx3 */
   /**
	* BitsName: reset_ssbmod
	* Description: Reset chirp  SSBMOD register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetSsbmod: 1;        /*## attribute ResetSsbmod */
   /**
	* BitsName: reset_lglobal_ldo
	* Description: Reset global LDO   register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetLglobalLdo: 1;        /*## attribute ResetLglobalLdo */
   /**
	* BitsName: reset_atb
	* Description: Reset ATB     register  space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAtb: 1;        /*## attribute ResetAtb */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: reset_ism
	* Description: Reset ISM register  space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	* Note: ISM is out of reset after a POR  to support start up
	*/
    uint32 ResetIsm: 1;        /*## attribute ResetIsm */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 7;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod00_ResetControlBits_t;
    /**
* Nxp_Tef810x_Mod00_FUNCTIONAL_RESET_CONTROLBits_t
* RegisterName: functional_reset_control
* 
* AddressRange: 0xREADWRITE - 0x070
* ResetValue: 0x00000074
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: fn_reset_ser
	* Description: Reset serializer  function
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space..
	* 
	* This reset shall be applied,  after any configuration regsiter changes to the IP register space
	*/
    uint32 FnResetSer: 1;        /*## attribute FnResetSer */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: fn_reset_chirp
	* Description: Reset chirp  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space..
	* In an application context this reset can be applied  based on application scenario  ( for example to stop an ongoing acquisition prematurely)
	*/
    uint32 FnResetChirp: 1;        /*## attribute FnResetChirp */
   /**
	* BitsName: fn_reset_adc12
	* Description: Reset ADC12   function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetAdc12: 1;        /*## attribute FnResetAdc12 */
   /**
	* BitsName: fn_reset_adc34
	* Description: Reset ADC34 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetAdc34: 1;        /*## attribute FnResetAdc34 */
   /**
	* BitsName: fn_reset_global_bias
	* Description: Reset global bias   function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetGlobalBias: 1;        /*## attribute FnResetGlobalBias */
   /**
	* BitsName: fn_reset_lo_interface
	* Description: Reset lo interface function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetLoInterface: 1;        /*## attribute FnResetLoInterface */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: fn_reset_master_clk
	* Description: Reset MC    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetMasterClk: 1;        /*## attribute FnResetMasterClk */
   /**
	* BitsName: fn_reset_rx1
	* Description: Not Used
	*/
    uint32 FnResetRx1: 1;        /*## attribute FnResetRx1 */
   /**
	* BitsName: fn_reset_rx2
	* Description: Not Used
	*/
    uint32 FnResetRx2: 1;        /*## attribute FnResetRx2 */
   /**
	* BitsName: fn_reset_rx3
	* Description: Not Used
	*/
    uint32 FnResetRx3: 1;        /*## attribute FnResetRx3 */
   /**
	* BitsName: fn_reset_rx4
	* Description: Not Used
	*/
    uint32 FnResetRx4: 1;        /*## attribute FnResetRx4 */
   /**
	* BitsName: fn_reset_tx1
	* Description: Reset chirp  TX1  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx1: 1;        /*## attribute FnResetTx1 */
   /**
	* BitsName: fn_reset_tx2
	* Description: Reset chirp  TX2 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx2: 1;        /*## attribute FnResetTx2 */
   /**
	* BitsName: fn_reset_tx3
	* Description: Reset chirp  TX3 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx3: 1;        /*## attribute FnResetTx3 */
   /**
	* BitsName: fn_reset_ssbmod
	* Description: Reset chirp  SSBMOD  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetSsbmod: 1;        /*## attribute FnResetSsbmod */
   /**
	* BitsName: fn_reset_lglobal_ldo
	* Description: Reset global LDO    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* This reset is not used within the global LDO module
	*/
    uint32 FnResetLglobalLdo: 1;        /*## attribute FnResetLglobalLdo */
   /**
	* BitsName: fn_reset_atb
	* Description: Reset ATB    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetAtb: 1;        /*## attribute FnResetAtb */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: fn_reset_ism
	* Description: Reset ISM     function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* Note: ISM is out of reset after a POR  to support start up
	* 
	* In an application context, this reset shall not be used  ( no use case to apply this reset)
	*/
    uint32 FnResetIsm: 1;        /*## attribute FnResetIsm */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 7;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod00_FunctionalResetControlBits_t;
    /**
* Nxp_Tef810x_Mod00_INT_RAW_STATUSBits_t
* RegisterName: INT_RAW_STATUS
* 
* AddressRange: 0xREAD - 0x078
* ResetValue: 0x0000007C
*/
typedef struct  {
   /**
	* BitsName: chirp_start_out_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 ChirpStartOutIntStatusRaw: 1;        /*## attribute ChirpStartOutIntStatusRaw */
   /**
	* BitsName: end_of_data_acq_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataAcqIntStatusRaw: 1;        /*## attribute EndOfDataAcqIntStatusRaw */
   /**
	* BitsName: end_of_data_tnfr_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataTnfrIntStatusRaw: 1;        /*## attribute EndOfDataTnfrIntStatusRaw */
   /**
	* BitsName: status_wdt_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 StatusWdtIntStatusRaw: 1;        /*## attribute StatusWdtIntStatusRaw */
   /**
	* BitsName: rtm_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RtmIntStatusRaw: 1;        /*## attribute RtmIntStatusRaw */
   /**
	* BitsName: rf_powerdown_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RfPowerdownIntStatusRaw: 1;        /*## attribute RfPowerdownIntStatusRaw */
   /**
	* BitsName: crc_error_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 CrcErrorIntStatusRaw: 1;        /*## attribute CrcErrorIntStatusRaw */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_IntRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod00_INT_MASKED_STATUSBits_t
* RegisterName: INT_MASKED_STATUS
* 
* AddressRange: 0xREAD - 0x07C
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: chirp_start_out_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 ChirpStartOutIntStatusMasked: 1;        /*## attribute ChirpStartOutIntStatusMasked */
   /**
	* BitsName: end_of_data_acq_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataAcqIntStatusMasked: 1;        /*## attribute EndOfDataAcqIntStatusMasked */
   /**
	* BitsName: end_of_data_tnfr_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataTnfrIntStatusMasked: 1;        /*## attribute EndOfDataTnfrIntStatusMasked */
   /**
	* BitsName: status_wdt_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 StatusWdtIntStatusMasked: 1;        /*## attribute StatusWdtIntStatusMasked */
   /**
	* BitsName: rtm_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RtmIntStatusMasked: 1;        /*## attribute RtmIntStatusMasked */
   /**
	* BitsName: rf_powerdown_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RfPowerdownIntStatusMasked: 1;        /*## attribute RfPowerdownIntStatusMasked */
   /**
	* BitsName: crc_error_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 CrcErrorIntStatusMasked: 1;        /*## attribute CrcErrorIntStatusMasked */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod00_IntMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod00_SCRATCH_REGISTER1Bits_t
* RegisterName: scratch_register1
* 
* AddressRange: 0xREADWRITE - 0x080
* ResetValue: 0x00000084
*/
typedef struct  {
   /**
	* BitsName: scratch_register1
	* Description: RW register to store information during debugging/validation
	*/
    uint32 ScratchRegister1: 32;        /*## attribute ScratchRegister1 */
}Nxp_Tef810x_Mod00_ScratchRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod00_SCRATCH_REGISTER8Bits_t
* RegisterName: scratch_register8
* 
* AddressRange: 0xREADWRITE - 0x09C
* ResetValue: 0x000000A0
*/
typedef struct  {
   /**
	* BitsName: override_chirp_level_dynamic_power_adc
	* Description: In case of dynamic power control at individual chirp level is selected, then
	* 0 : No action
	* 1 : power to the ADC  is   enabled through out chirp sequence ( override default  chirp level power control)
	* 
	* Note: After powerup, this bit to be initialized to '0' as the flop holding this bit is non-resettable flop. So known value to be initialized after every powerup
	*/
    uint32 OverrideChirpLevelDynamicPowerAdc: 1;        /*## attribute OverrideChirpLevelDynamicPowerAdc */
   /**
	* BitsName: override_chirp_level_dynamic_power_chirp
	* Description: In case of dynamic power control at individual chirp level is selected, then
	* 0 : No action
	* 1 : power to the chirp is   enabled through out chirp sequence ( override default  chirp level power control)
	* 
	* Note: After powerup, this bit to be initialized to '0' as the flop holding this bit is non-resettable flop. So known value to be initialized after every powerup
	*/
    uint32 OverrideChirpLevelDynamicPowerChirp: 1;        /*## attribute OverrideChirpLevelDynamicPowerChirp */
   /**
	* BitsName: scratch_register8
	* Description: RW register to store information during debugging/validation
	*/
    uint32 ScratchRegister8: 30;        /*## attribute ScratchRegister8 */
}Nxp_Tef810x_Mod00_ScratchRegister8Bits_t;
    /**
* Nxp_Tef810x_Mod00_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod00_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod00_ReadyintPadcontrolBits_t
* RegisterName: ReadyInt_PadControl
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: readyint_mfio_ehs1
	* Description: IO Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ReadyintMfioEhs1: 1;        /*## attribute ReadyintMfioEhs1 */
   /**
	* BitsName: readyint_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ReadyintMfioEhs0: 1;        /*## attribute ReadyintMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: readyint_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ReadyintMfioEpd: 1;        /*## attribute ReadyintMfioEpd */
   /**
	* BitsName: readyint_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ReadyintMfioEpun: 1;        /*## attribute ReadyintMfioEpun */
   /**
	* BitsName: readyint_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ReadyintMfioEnzi: 1;        /*## attribute ReadyintMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: readyint_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ReadyintMfioEn: 1;        /*## attribute ReadyintMfioEn */
}Nxp_Tef810x_Mod00_ReadyintPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_ChirpStartPadcontrolBits_t
* RegisterName: Chirp_Start_PadControl
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00000321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: chirpstart_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ChirpstartMfioEhs1: 1;        /*## attribute ChirpstartMfioEhs1 */
   /**
	* BitsName: chirpstart_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ChirpstartMfioEhs0: 1;        /*## attribute ChirpstartMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: chirpstart_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ChirpstartMfioEpd: 1;        /*## attribute ChirpstartMfioEpd */
   /**
	* BitsName: chirpstart_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ChirpstartMfioEpun: 1;        /*## attribute ChirpstartMfioEpun */
   /**
	* BitsName: chirpstart_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ChirpstartMfioEnzi: 1;        /*## attribute ChirpstartMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: chirpstart_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ChirpstartMfioEn: 1;        /*## attribute ChirpstartMfioEn */
}Nxp_Tef810x_Mod00_ChirpStartPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_ErrorNPadcontrolBits_t
* RegisterName: Error_n_PadControl
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: error_n_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ErrorNMfioEhs1: 1;        /*## attribute ErrorNMfioEhs1 */
   /**
	* BitsName: error_n_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ErrorNMfioEhs0: 1;        /*## attribute ErrorNMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: error_n_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ErrorNMfioEpd: 1;        /*## attribute ErrorNMfioEpd */
   /**
	* BitsName: error_n_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ErrorNMfioEpun: 1;        /*## attribute ErrorNMfioEpun */
   /**
	* BitsName: error_n_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ErrorNMfioEnzi: 1;        /*## attribute ErrorNMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: error_n_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	*/
    uint32 ErrorNMfioEn: 1;        /*## attribute ErrorNMfioEn */
}Nxp_Tef810x_Mod00_ErrorNPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_ErrorResetPadcontrolBits_t
* RegisterName: Error_Reset_PadControl
* 
* AddressRange: 0x00C - 0x010
* ResetValue: 0x00000321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: error_reset_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 ErrorResetMfioEhs1: 1;        /*## attribute ErrorResetMfioEhs1 */
   /**
	* BitsName: error_reset_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 ErrorResetMfioEhs0: 1;        /*## attribute ErrorResetMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: error_reset_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 ErrorResetMfioEpd: 1;        /*## attribute ErrorResetMfioEpd */
   /**
	* BitsName: error_reset_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 ErrorResetMfioEpun: 1;        /*## attribute ErrorResetMfioEpun */
   /**
	* BitsName: error_reset_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 ErrorResetMfioEnzi: 1;        /*## attribute ErrorResetMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: error_reset_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* In a functional context the O/P is never enabled
	*/
    uint32 ErrorResetMfioEn: 1;        /*## attribute ErrorResetMfioEn */
}Nxp_Tef810x_Mod00_ErrorResetPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_Tx1PadcontrolBits_t
* RegisterName: TX1_PadControl
* 
* AddressRange: 0x010 - 0x014
* ResetValue: 0x00001321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ps_tx1_ext_en
	* Description: Selection bit for routing tx1_ps pad input to ps_tx1_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx1_ext from CC will be tied to 0
	*/
    uint32 PsTx1ExtEn: 1;        /*## attribute PsTx1ExtEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: tx1_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx1MfioEhs1: 1;        /*## attribute Tx1MfioEhs1 */
   /**
	* BitsName: tx1_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx1MfioEhs0: 1;        /*## attribute Tx1MfioEhs0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: tx1_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx1MfioEpd: 1;        /*## attribute Tx1MfioEpd */
   /**
	* BitsName: tx1_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx1MfioEpun: 1;        /*## attribute Tx1MfioEpun */
   /**
	* BitsName: tx1_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx1MfioEnzi: 1;        /*## attribute Tx1MfioEnzi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: tx1_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx1MfioEn: 1;        /*## attribute Tx1MfioEn */
}Nxp_Tef810x_Mod00_Tx1PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_Tx2PadcontrolBits_t
* RegisterName: TX2_PadControl
* 
* AddressRange: 0x014 - 0x018
* ResetValue: 0x00001321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ps_tx2_ext_en
	* Description: Selection bit for routing tx2_ps pad input to ps_tx2_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx2_ext from CC will be tied to 0
	*/
    uint32 PsTx2ExtEn: 1;        /*## attribute PsTx2ExtEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: tx2_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx2MfioEhs1: 1;        /*## attribute Tx2MfioEhs1 */
   /**
	* BitsName: tx2_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx2MfioEhs0: 1;        /*## attribute Tx2MfioEhs0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: tx2_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx2MfioEpd: 1;        /*## attribute Tx2MfioEpd */
   /**
	* BitsName: tx2_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx2MfioEpun: 1;        /*## attribute Tx2MfioEpun */
   /**
	* BitsName: tx2_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx2MfioEnzi: 1;        /*## attribute Tx2MfioEnzi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: tx2_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx2MfioEn: 1;        /*## attribute Tx2MfioEn */
}Nxp_Tef810x_Mod00_Tx2PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_Tx3PadcontrolBits_t
* RegisterName: TX3_PadControl
* 
* AddressRange: 0x018 - 0x01C
* ResetValue: 0x00001321
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ps_tx3_ext_en
	* Description: Selection bit for routing tx3_ps pad input to ps_tx3_ext. This is enabled by default 
	*       1 -> Routing is enabled
	*       0 -> Rouring is disabled. The output line ps_tx3_ext from CC will be tied to 0
	*/
    uint32 PsTx3ExtEn: 1;        /*## attribute PsTx3ExtEn */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: tx3_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 Tx3MfioEhs1: 1;        /*## attribute Tx3MfioEhs1 */
   /**
	* BitsName: tx3_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 Tx3MfioEhs0: 1;        /*## attribute Tx3MfioEhs0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: tx3_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 Tx3MfioEpd: 1;        /*## attribute Tx3MfioEpd */
   /**
	* BitsName: tx3_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 Tx3MfioEpun: 1;        /*## attribute Tx3MfioEpun */
   /**
	* BitsName: tx3_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 Tx3MfioEnzi: 1;        /*## attribute Tx3MfioEnzi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: tx3_mfio_en
	* Description: Disable  O/P  driver
	* 0 => O/P enabled
	* 1 => O/P disabled
	* This is an input pin.  
	* Do not enable the O/P in functional mode.
	*/
    uint32 Tx3MfioEn: 1;        /*## attribute Tx3MfioEn */
}Nxp_Tef810x_Mod00_Tx3PadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_MisoPadcontrolBits_t
* RegisterName: MISO_padControl
* 
* AddressRange: 0x01C - 0x020
* ResetValue: 0x00000330
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 22;        /*## attribute Reserved0 */
   /**
	* BitsName: miso_mfio_ehs1
	* Description: Speed Selection Bit1 (MSB).Combination of ehs1 and ehs 0 determines the speed of the PAD.
	*/
    uint32 MisoMfioEhs1: 1;        /*## attribute MisoMfioEhs1 */
   /**
	* BitsName: miso_mfio_ehs0
	* Description: Speed Selection Bit0 (LSB)
	* ehs1  ehs0
	* 0       0    =>  low speed (12.5MHz)
	* 0       1    =>  normal speed (25MHz)
	* 1       0    =>  fast speed (50MHz)
	* 1       1   =>  high speed (80MHz)
	*/
    uint32 MisoMfioEhs0: 1;        /*## attribute MisoMfioEhs0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: msio_mfio_epd
	* Description: Enable weak pull-down
	* 0 => pull down disabled
	* 1 => pull down enabled
	*/
    uint32 MsioMfioEpd: 1;        /*## attribute MsioMfioEpd */
   /**
	* BitsName: miso_mfio_epun
	* Description: Enable weak pull-up
	* 0 => pull up disabled
	* 1 => pull up enabled
	*/
    uint32 MisoMfioEpun: 1;        /*## attribute MisoMfioEpun */
   /**
	* BitsName: miso_mfio_enzi
	* Description: Disable receiver function
	* This is not used in functional context.
	* 0: Receiver is enabled 
	* 1: Receiver is disabled
	*/
    uint32 MisoMfioEnzi: 1;        /*## attribute MisoMfioEnzi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_MisoPadcontrolBits_t;
    /**
* Nxp_Tef810x_Mod00_LdoSerialiserSerControlBits_t
* RegisterName: Ldo_Serialiser_Ser_Control
* 
* AddressRange: 0x020 - 0x024
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_serialiser_ser
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSerialiserSer: 5;        /*## attribute LdoSelVoutSerialiserSer */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_en_serialiser_ser
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSerialiserSer: 1;        /*## attribute LdoEnSerialiserSer */
}Nxp_Tef810x_Mod00_LdoSerialiserSerControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlBits_t
* RegisterName: Ldo_Serialiser_csi2_Control
* 
* AddressRange: 0x024 - 0x028
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_serialiser_csi2
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSerialiserCsi2: 5;        /*## attribute LdoSelVoutSerialiserCsi2 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_en_serialiser_csi2
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSerialiserCsi2: 1;        /*## attribute LdoEnSerialiserCsi2 */
}Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LdoAdcControlBits_t
* RegisterName: Ldo_Adc_Control
* 
* AddressRange: 0x028 - 0x02C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_adc
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutAdc: 5;        /*## attribute LdoSelVoutAdc */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_en_adc
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnAdc: 1;        /*## attribute LdoEnAdc */
}Nxp_Tef810x_Mod00_LdoAdcControlBits_t;
    /**
* Nxp_Tef810x_Mod00_LdoSsbmodControlBits_t
* RegisterName: Ldo_Ssbmod_Control
* 
* AddressRange: 0x02C - 0x030
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ldo_sel_vout_ssbmod
	* Description: set output voltage of local LDO.
	* The values to be set will be coming from the  OTP
	*/
    uint32 LdoSelVoutSsbmod: 5;        /*## attribute LdoSelVoutSsbmod */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ldo_en_ssbmod
	* Description: Enables local LDO
	* 0: LDO is disabled
	* 1: LDO is enabled
	*/
    uint32 LdoEnSsbmod: 1;        /*## attribute LdoEnSsbmod */
}Nxp_Tef810x_Mod00_LdoSsbmodControlBits_t;
    /**
* Nxp_Tef810x_Mod00_Atb1EnRegisterBits_t
* RegisterName: ATB1_en_register
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: atb1_en
	* Description: Enable DC Test Bus fro ATB1
	* atb1_en = 0 will disable DC test bus
	* atb1_en = 1 will enable DC test bus
	*/
    uint32 Atb1En: 1;        /*## attribute Atb1En */
   /**
	* BitsName: atb1_set
	* Description: lvds (serilaizer) = 0x01
	* cif (serilaizer) = 0x01
	* csi2 (serilaizer) = 0x01
	* chirp_afc = 0x06
	* adc12 = 0x07
	* adc34 = 0x08
	* global_bias = 0x09
	* lo_interface = 0x0A
	* master_clock = 0x0C
	* rx1 = 0x0D
	* rx2 = 0x0E
	* rx3 = 0x0F
	* rx4 = 0x10
	* tx1 = 0x11
	* tx2 = 0x12
	* tx3 = 0x13
	* ssbmod = 0x14
	* global_ldo = 0x15
	* atb = 0x16
	*/
    uint32 Atb1Set: 8;        /*## attribute Atb1Set */
}Nxp_Tef810x_Mod00_Atb1EnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_Atb1AcEnRegisterBits_t
* RegisterName: ATB1_ac_en_register
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x01110000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: atb1_ext_in_en_ssbmod
	* Description: Handles AC switch in SSBMOD: 
	* connects SSBMOD AC input (0? & 180?) to SSBMOD_ATB1
	*/
    uint32 Atb1ExtInEnSsbmod: 1;        /*## attribute Atb1ExtInEnSsbmod */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb1_ssbmod_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects SSBMOD_ATB1 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb1SsbmodAc: 1;        /*## attribute EnAtb1SsbmodAc */
   /**
	* BitsName: en_atb1_ssbmod_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects SSBMOD_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1SsbmodAcGnd: 1;        /*## attribute EnAtb1SsbmodAcGnd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb1_rx1_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects RX1_ATB1 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb1Rx1Ac: 1;        /*## attribute EnAtb1Rx1Ac */
   /**
	* BitsName: en_atb1_rx1_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects RX1_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1Rx1AcGnd: 1;        /*## attribute EnAtb1Rx1AcGnd */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: en_atb1_adc_ac
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects ADC1234_ATB1 (0? & 180?) to ATB1 pins
	* (both dualADCs simultaneously)
	*/
    uint32 EnAtb1AdcAc: 1;        /*## attribute EnAtb1AdcAc */
   /**
	* BitsName: en_atb1_adc_ac_gnd
	* Description: Handles AC switch in ATB1 Master Switch: 
	* connects ADC1234_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb1AdcAcGnd: 1;        /*## attribute EnAtb1AdcAcGnd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: en_atb1_dc_0_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_ATB1_0 to GND
	*/
    uint32 EnAtb1Dc0Gnd: 1;        /*## attribute EnAtb1Dc0Gnd */
   /**
	* BitsName: en_atb1_dc_180_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_ATB1_180 to GND
	*/
    uint32 EnAtb1Dc180Gnd: 1;        /*## attribute EnAtb1Dc180Gnd */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
   /**
	* BitsName: en_atb1_dc_int_0_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to GND
	*/
    uint32 EnAtb1DcInt0Gnd: 1;        /*## attribute EnAtb1DcInt0Gnd */
   /**
	* BitsName: en_atb1_dc_int_180_gnd
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to GND
	*/
    uint32 EnAtb1DcInt180Gnd: 1;        /*## attribute EnAtb1DcInt180Gnd */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
   /**
	* BitsName: en_atb1_dc_int_0_to_pins
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to ATB1_0 pin
	*/
    uint32 EnAtb1DcInt0ToPins: 1;        /*## attribute EnAtb1DcInt0ToPins */
   /**
	* BitsName: en_atb1_dc_int_180_to_pins
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to ATB1_180 pin
	*/
    uint32 EnAtb1DcInt180ToPins: 1;        /*## attribute EnAtb1DcInt180ToPins */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 2;        /*## attribute Reserved7 */
   /**
	* BitsName: en_atb1_dc_to_int_0
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_0 to DC_ATB1_0 ATB line
	*/
    uint32 EnAtb1DcToInt0: 1;        /*## attribute EnAtb1DcToInt0 */
   /**
	* BitsName: en_atb1_dc_to_int_180
	* Description: Handles DC switch in ATB1 Master Switch: 
	* connects DC_int_ATB1_180 to DC_ATB1_180 ATB line
	*/
    uint32 EnAtb1DcToInt180: 1;        /*## attribute EnAtb1DcToInt180 */
}Nxp_Tef810x_Mod00_Atb1AcEnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_Atb2EnRegisterBits_t
* RegisterName: ATB2_en_register
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: atb2_en
	* Description: Enable DC Test Bus fro ATB2
	* atb2_en = 0 will disable DC test bus
	* atb2_en = 1 will enable DC test bus
	*/
    uint32 Atb2En: 1;        /*## attribute Atb2En */
   /**
	* BitsName: atb2_set
	* Description: lvds (serilaizer) = 0x01
	* cif (serilaizer) = 0x01
	* csi2 (serilaizer) = 0x01
	* chirp_afc = 0x06
	* adc12 = 0x07
	* adc34 = 0x08
	* global_bias = 0x09
	* lo_interface = 0x0A
	* master_clock = 0x0C
	* rx1 = 0x0D
	* rx2 = 0x0E
	* rx3 = 0x0F
	* rx4 = 0x10
	* tx1 = 0x11
	* tx2 = 0x12
	* tx3 = 0x13
	* ssbmod = 0x14
	* global_ldo = 0x15
	* atb = 0x16
	*/
    uint32 Atb2Set: 8;        /*## attribute Atb2Set */
}Nxp_Tef810x_Mod00_Atb2EnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_Atb2AcEnRegisterBits_t
* RegisterName: ATB2_ac_en_register
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00110000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: atb2_ext_in_en_ssbmod
	* Description: Handles AC switch in SSBMOD: 
	* connects SSBMOD AC input (0? & 180?) to SSBMOD_ATB2
	*/
    uint32 Atb2ExtInEnSsbmod: 1;        /*## attribute Atb2ExtInEnSsbmod */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 6;        /*## attribute Reserved1 */
   /**
	* BitsName: en_atb2_ssbmod_ac
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects SSBMOD_ATB2 (0? & 180?) to ATB1 pins
	*/
    uint32 EnAtb2SsbmodAc: 1;        /*## attribute EnAtb2SsbmodAc */
   /**
	* BitsName: en_atb2_ssbmod_ac_gnd
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects SSBMOD_ATB2 (0? & 180?) to GND
	*/
    uint32 EnAtb2SsbmodAcGnd: 1;        /*## attribute EnAtb2SsbmodAcGnd */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: en_atb2_rx234_ac
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects RX234_ATB1 (0? & 180?) to ATB1 pins 
	* (select RX2, RX3 or RX4 by own register space)
	*/
    uint32 EnAtb2Rx234Ac: 1;        /*## attribute EnAtb2Rx234Ac */
   /**
	* BitsName: en_atb2_rx234_ac_gnd
	* Description: Handles AC switch in ATB2 Master Switch: 
	* connects RX234_ATB1 (0? & 180?) to GND
	*/
    uint32 EnAtb2Rx234AcGnd: 1;        /*## attribute EnAtb2Rx234AcGnd */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: en_atb2_dc_0_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_ATB2_0 to GND
	*/
    uint32 EnAtb2Dc0Gnd: 1;        /*## attribute EnAtb2Dc0Gnd */
   /**
	* BitsName: en_atb2_dc_180_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_ATB2_180 to GND
	*/
    uint32 EnAtb2Dc180Gnd: 1;        /*## attribute EnAtb2Dc180Gnd */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: en_atb2_dc_int_0_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to GND
	*/
    uint32 EnAtb2DcInt0Gnd: 1;        /*## attribute EnAtb2DcInt0Gnd */
   /**
	* BitsName: en_atb2_dc_int_180_gnd
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to GND
	*/
    uint32 EnAtb2DcInt180Gnd: 1;        /*## attribute EnAtb2DcInt180Gnd */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 2;        /*## attribute Reserved5 */
   /**
	* BitsName: en_atb2_dc_int_0_to_pins
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to ATB2_0 pin
	*/
    uint32 EnAtb2DcInt0ToPins: 1;        /*## attribute EnAtb2DcInt0ToPins */
   /**
	* BitsName: en_atb2_dc_int_180_to_pins
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to ATB2_180 pin
	*/
    uint32 EnAtb2DcInt180ToPins: 1;        /*## attribute EnAtb2DcInt180ToPins */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
   /**
	* BitsName: en_atb2_dc_to_int_0
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_0 to DC_ATB2_0 ATB line
	*/
    uint32 EnAtb2DcToInt0: 1;        /*## attribute EnAtb2DcToInt0 */
   /**
	* BitsName: en_atb2_dc_to_int_180
	* Description: Handles DC switch in ATB2 Master Switch: 
	* connects DC_int_ATB2_180 to DC_ATB2_180 ATB line
	*/
    uint32 EnAtb2DcToInt180: 1;        /*## attribute EnAtb2DcToInt180 */
}Nxp_Tef810x_Mod00_Atb2AcEnRegisterBits_t;
    /**
* Nxp_Tef810x_Mod00_DynamicPowerControlEnableBits_t
* RegisterName: dynamic_power_control_enable
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: dy_power_mode_sel
	* Description: Decides the control signal for dynamic power control
	* 0: Dynamic power is  controlled at chirp sequence level
	* 1: Dynamic power is controlled at individual chirp 
	* 
	* An overriding option is provided to avoid disabling power for Chirp and ADC   when this bit is set to '1'. Meaning that  both for ADC and Chirp module the power control will be at chirp sequence level  and for the rest of the IP  the power control is at individual chirp lebel. Please refere to scratch_register8  for details
	* 
	* When individual  chirp level power control, then an additional setting is required  from timing engine. teh following register must be set to '1'
	* 
	* 
	* Register:  ( timing_engine().chirp_trigger_mode_control (0x38). chirp_power_mode(9)).
	* Leave as reset if not needed explicitly.
	*/
    uint32 DyPowerModeSel: 1;        /*## attribute DyPowerModeSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: tx3_dy_power_control
	* Description: 0: TX3 unit is not under dynamic power control
	* 1: TX3 power is  controlled dynamically
	*/
    uint32 Tx3DyPowerControl: 1;        /*## attribute Tx3DyPowerControl */
   /**
	* BitsName: tx2_dy_power_control
	* Description: 0: TX2  unit is not under dynamic power control
	* 1: TX2  power is  controlled dynamically
	*/
    uint32 Tx2DyPowerControl: 1;        /*## attribute Tx2DyPowerControl */
   /**
	* BitsName: tx1_dy_power_control
	* Description: 0: TX1  unit is not under dynamic power control
	* 1: TX1  power is  controlled dynamically
	*/
    uint32 Tx1DyPowerControl: 1;        /*## attribute Tx1DyPowerControl */
   /**
	* BitsName: rx4_dy_power_control
	* Description: 0: RX4  unit is not under dynamic power control
	* 1: RX4  power is  controlled dynamically
	*/
    uint32 Rx4DyPowerControl: 1;        /*## attribute Rx4DyPowerControl */
   /**
	* BitsName: rx3_dy_power_control
	* Description: 0: RX3  unit is not under dynamic power control
	* 1: RX3  power is  controlled dynamically
	*/
    uint32 Rx3DyPowerControl: 1;        /*## attribute Rx3DyPowerControl */
   /**
	* BitsName: rx2_dy_power_control
	* Description: 0: RX2  unit is not under dynamic power control
	* 1: RX2  power is  controlled dynamically
	*/
    uint32 Rx2DyPowerControl: 1;        /*## attribute Rx2DyPowerControl */
   /**
	* BitsName: rx1_dy_power_control
	* Description: 0: RX1  unit is not under dynamic power control
	* 1: RX1  power is  controlled dynamically
	*/
    uint32 Rx1DyPowerControl: 1;        /*## attribute Rx1DyPowerControl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: lo_interface_dy_power_control
	* Description: 0: LO Interface is not under dynamic power control
	* 1: LO Interface  power is  controlled dynamically
	*/
    uint32 LoInterfaceDyPowerControl: 1;        /*## attribute LoInterfaceDyPowerControl */
   /**
	* BitsName: adc_dy_power_control
	* Description: 0: ADC12 and ADC34 is not under dynamic power control
	* 1: ADC12 and ADC34  power is  controlled dynamically
	*/
    uint32 AdcDyPowerControl: 1;        /*## attribute AdcDyPowerControl */
   /**
	* BitsName: chirp_dy_power_control
	* Description: 0: Chirp unit   is not under dynamic power control
	* 1: Chirp unit    power is  controlled dynamically
	*/
    uint32 ChirpDyPowerControl: 1;        /*## attribute ChirpDyPowerControl */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: ser_dy_clock_control
	* Description: 0: Serializer digital part not under dynamic power control (clock gating)
	* 1: Serializer digital part   clock  is  controlled dynamically
	* Leave as reset if not needed explicitly.
	*/
    uint32 SerDyClockControl: 1;        /*## attribute SerDyClockControl */
   /**
	* BitsName: ser_dy_power_control
	* Description: Reserved
	* Leave as reset if not needed explicitly.
	*/
    uint32 SerDyPowerControl: 1;        /*## attribute SerDyPowerControl */
}Nxp_Tef810x_Mod00_DynamicPowerControlEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_DynamicPowerControlDelayBits_t
* RegisterName: dynamic_power_control_delay
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x0000FFFF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: dy_clkgate_delay_val
	* Description: Decides the dynamic power down  delay once the data acquisition is over.
	* 
	* 
	* This value has to be  minimum  equal to the chirp reset time duration
	*/
    uint32 DyClkgateDelayVal: 16;        /*## attribute DyClkgateDelayVal */
}Nxp_Tef810x_Mod00_DynamicPowerControlDelayBits_t;
    /**
* Nxp_Tef810x_Mod00_SerialiserModeSelBits_t
* RegisterName: serialiser_mode_sel
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 30;        /*## attribute Reserved0 */
   /**
	* BitsName: sw_ctrl_ser_mode_sel
	* Description: This register is a conditionally writable register
	* 01: CSI2 mode
	* 10: LVDS
	* 11: CIF
	* The serializer mode can also be controlled  through OTP.
	* If only one function is enabled by the OTP, then this register is only a read only register r.
	* If both LVDS and CIF is enabled, then bit '0'is writable.
	* If all are enabled, then this register is fully writable
	*/
    uint32 SwCtrlSerModeSel: 2;        /*## attribute SwCtrlSerModeSel */
}Nxp_Tef810x_Mod00_SerialiserModeSelBits_t;
    /**
* Nxp_Tef810x_Mod00_ReadyIntControlBits_t
* RegisterName: Ready_Int_Control
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x01100090
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: interrupt_polarity
	* Description: 0 Active low interrupt
	*  1: Active High interrupt
	*/
    uint32 InterruptPolarity: 1;        /*## attribute InterruptPolarity */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 7;        /*## attribute Reserved1 */
   /**
	* BitsName: Interrupt_level_or_pulse
	* Description: 1: Edge triggered interrupt. Ready Interrupt is activated for the time period mentioned in the "ReadyInt_period" .              
	* 0: Level triggered interrupt. Once Ready Interrupt is activated, is cleared by MCU by writing through interrupt clear register
	*/
    uint32 InterruptLevelOrPulse: 1;        /*## attribute InterruptLevelOrPulse */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 8;        /*## attribute Reserved2 */
   /**
	* BitsName: ReadyInt_period
	* Description: Activation Period for Ready Interrupt based on 40MHz(25 ns -Xtal Clock) 
	* default: 3.6us(144). This period is applicable only for edge triggered interrupt mode.
	*/
    uint32 ReadyintPeriod: 8;        /*## attribute ReadyintPeriod */
}Nxp_Tef810x_Mod00_ReadyIntControlBits_t;
    /**
* Nxp_Tef810x_Mod00_IntEnableBits_t
* RegisterName: INT_ENABLE
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 CrcErrorIntEn: 1;        /*## attribute CrcErrorIntEn */
   /**
	* BitsName: rf_powerdown_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 RfPowerdownIntEn: 1;        /*## attribute RfPowerdownIntEn */
   /**
	* BitsName: rtm_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 RtmIntEn: 1;        /*## attribute RtmIntEn */
   /**
	* BitsName: status_wdt_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 StatusWdtIntEn: 1;        /*## attribute StatusWdtIntEn */
   /**
	* BitsName: end_of_data_tnfr_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 EndOfDataTnfrIntEn: 1;        /*## attribute EndOfDataTnfrIntEn */
   /**
	* BitsName: end_of_data_acq_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 EndOfDataAcqIntEn: 1;        /*## attribute EndOfDataAcqIntEn */
   /**
	* BitsName: chirp_start_out_int_en
	* Description: 0: Interrupt is not enabled
	* 1: Interrupt is enabled
	*/
    uint32 ChirpStartOutIntEn: 1;        /*## attribute ChirpStartOutIntEn */
}Nxp_Tef810x_Mod00_IntEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_IntClrBits_t
* RegisterName: INT_CLR
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 CrcErrorIntClr: 1;        /*## attribute CrcErrorIntClr */
   /**
	* BitsName: rf_powerdown_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 RfPowerdownIntClr: 1;        /*## attribute RfPowerdownIntClr */
   /**
	* BitsName: rtm_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 RtmIntClr: 1;        /*## attribute RtmIntClr */
   /**
	* BitsName: status_wdt_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 StatusWdtIntClr: 1;        /*## attribute StatusWdtIntClr */
   /**
	* BitsName: end_of_data_tnfr_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 EndOfDataTnfrIntClr: 1;        /*## attribute EndOfDataTnfrIntClr */
   /**
	* BitsName: end_of_data_acq_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 EndOfDataAcqIntClr: 1;        /*## attribute EndOfDataAcqIntClr */
   /**
	* BitsName: chirp_start_out_int_clr
	* Description: 0: no action
	* 1: clear pending interrupt ( clear only the latch)
	*/
    uint32 ChirpStartOutIntClr: 1;        /*## attribute ChirpStartOutIntClr */
}Nxp_Tef810x_Mod00_IntClrBits_t;
    /**
* Nxp_Tef810x_Mod00_IntSetBits_t
* RegisterName: INT_SET
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 CrcErrorIntSet: 1;        /*## attribute CrcErrorIntSet */
   /**
	* BitsName: rf_powerdown_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 RfPowerdownIntSet: 1;        /*## attribute RfPowerdownIntSet */
   /**
	* BitsName: rtm_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 RtmIntSet: 1;        /*## attribute RtmIntSet */
   /**
	* BitsName: status_wdt_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 StatusWdtIntSet: 1;        /*## attribute StatusWdtIntSet */
   /**
	* BitsName: end_of_data_tnfr_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 EndOfDataTnfrIntSet: 1;        /*## attribute EndOfDataTnfrIntSet */
   /**
	* BitsName: end_of_data_acq_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 EndOfDataAcqIntSet: 1;        /*## attribute EndOfDataAcqIntSet */
   /**
	* BitsName: chirp_start_out_int_set
	* Description: 0: no action
	* 1: Generate an interrupt
	*/
    uint32 ChirpStartOutIntSet: 1;        /*## attribute ChirpStartOutIntSet */
}Nxp_Tef810x_Mod00_IntSetBits_t;
    /**
* Nxp_Tef810x_Mod00_IpLevelClockEnableBits_t
* RegisterName: ip_level_clock_enable
* 
* AddressRange: 0x064 - 0x068
* ResetValue: 0x01800000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: clk40_ism
	* Description: Enable  40 MHz  clock to ISM  (register/functional  access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ism: 1;        /*## attribute Clk40Ism */
   /**
	* BitsName: clk40_otp
	* Description: Enable  40 MHz  clock to OTP (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Otp: 1;        /*## attribute Clk40Otp */
   /**
	* BitsName: clk40_atb
	* Description: Enable  40 MHz  clock to ATB (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Atb: 1;        /*## attribute Clk40Atb */
   /**
	* BitsName: clk40_global_ldo
	* Description: Enable  40 MHz  clock to global LDO (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40GlobalLdo: 1;        /*## attribute Clk40GlobalLdo */
   /**
	* BitsName: clk40_ssbmod
	* Description: Enable  40 MHz  clock to SSBMOD/RFBIST   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ssbmod: 1;        /*## attribute Clk40Ssbmod */
   /**
	* BitsName: clk40_tx3
	* Description: Enable  40 MHz  clock to TX3   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx3: 1;        /*## attribute Clk40Tx3 */
   /**
	* BitsName: clk40_tx2
	* Description: Enable  40 MHz  clock to TX2   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx2: 1;        /*## attribute Clk40Tx2 */
   /**
	* BitsName: clk40_tx1
	* Description: Enable  40 MHz  clock to TX1   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Tx1: 1;        /*## attribute Clk40Tx1 */
   /**
	* BitsName: clk40_rx4
	* Description: Enable  40 MHz  clock to RX4   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx4: 1;        /*## attribute Clk40Rx4 */
   /**
	* BitsName: clk40_rx3
	* Description: Enable  40 MHz  clock to RX3   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx3: 1;        /*## attribute Clk40Rx3 */
   /**
	* BitsName: clk40_rx2
	* Description: Enable  40 MHz  clock to RX2   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx2: 1;        /*## attribute Clk40Rx2 */
   /**
	* BitsName: clk40_rx1
	* Description: Enable  40 MHz  clock to RX1   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Rx1: 1;        /*## attribute Clk40Rx1 */
   /**
	* BitsName: clk40_master_clk
	* Description: Enable  40 MHz  clock to master clock   (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40MasterClk: 1;        /*## attribute Clk40MasterClk */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: clk40_lo_interface
	* Description: Enable  40 MHz  clock to LO interface  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40LoInterface: 1;        /*## attribute Clk40LoInterface */
   /**
	* BitsName: clk40_global_bias
	* Description: Enable  40 MHz  clock to global bias  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40GlobalBias: 1;        /*## attribute Clk40GlobalBias */
   /**
	* BitsName: clk40_adc34
	* Description: Enable  40 MHz  clock to ADC 3&4  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Adc34: 1;        /*## attribute Clk40Adc34 */
   /**
	* BitsName: clk40_adc12
	* Description: Enable  40 MHz  clock to ADC 1&2  (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Adc12: 1;        /*## attribute Clk40Adc12 */
   /**
	* BitsName: clk40_chirp
	* Description: Enable  40 MHz  clock to Chirp  (register access as well as functional clock to timing engine)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Chirp: 1;        /*## attribute Clk40Chirp */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 4;        /*## attribute Reserved2 */
   /**
	* BitsName: clk40_ser
	* Description: Enable  40 MHz  clock to serialzer (register access)
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 Clk40Ser: 1;        /*## attribute Clk40Ser */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod00_IpLevelClockEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_IpLevelPonEnableBits_t
* RegisterName: ip_level_pon_enable
* 
* AddressRange: 0x068 - 0x06C
* ResetValue: 0x01800000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: pon_atb
	* Description: Enable  power to ATB 
	* 0 : Clock not enabled
	* 1: Clock is enabled
	*/
    uint32 PonAtb: 1;        /*## attribute PonAtb */
   /**
	* BitsName: pon_global_ldo
	* Description: Has to be set as '1' for proper functioning of LDO. 
	* Even though Global LDO is enabled on powerup, pon_ldo enables measurement of LDO signals for ATB.
	* 0 : Global LDO is not enabled for ATB Measurement
	* 1 : Global LDO is enabled for ATB Measurement
	* 
	* For normal IP operation the default value is sufficient.
	*/
    uint32 PonGlobalLdo: 1;        /*## attribute PonGlobalLdo */
   /**
	* BitsName: pon_ssbmod
	* Description: Enable  power to SSBMOD/RFBIST  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonSsbmod: 1;        /*## attribute PonSsbmod */
   /**
	* BitsName: pon_tx3
	* Description: Enable  power to TX3  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx3: 1;        /*## attribute PonTx3 */
   /**
	* BitsName: pon_tx2
	* Description: Enable  power to TX2  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx2: 1;        /*## attribute PonTx2 */
   /**
	* BitsName: pon_tx1
	* Description: Enable  power to TX1  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonTx1: 1;        /*## attribute PonTx1 */
   /**
	* BitsName: pon_rx4
	* Description: Enable  power to RX4  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx4: 1;        /*## attribute PonRx4 */
   /**
	* BitsName: pon_rx3
	* Description: Enable  power to RX3 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx3: 1;        /*## attribute PonRx3 */
   /**
	* BitsName: pon_rx2
	* Description: Enable  power to RX2 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx2: 1;        /*## attribute PonRx2 */
   /**
	* BitsName: pon_rx1
	* Description: Enable  power to RX1  
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonRx1: 1;        /*## attribute PonRx1 */
   /**
	* BitsName: pon_master_clk
	* Description: Enable  power to Master_clk PLL
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonMasterClk: 1;        /*## attribute PonMasterClk */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: pon_lo_interface
	* Description: Enable  power to LO interface 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonLoInterface: 1;        /*## attribute PonLoInterface */
   /**
	* BitsName: pon_global_bias
	* Description: Enable  power to global bias 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonGlobalBias: 1;        /*## attribute PonGlobalBias */
   /**
	* BitsName: pon_adc34
	* Description: Enable  power to ADC 3&4 
	* 0 : power not enabled
	* 1: power is enabled
	* 
	* This bit also controls the dynamic power as well as back ground calibration
	* On start up this must be set to '1'. After star up it is recommended to keep this bit '1' always.. The dynamic power is them managed through  hardware ( configuration through dynamic_power_control_enable register) . If hardware control is not used, then software can use this bit for any possible synamic power control at SW level ( not recommended)
	*/
    uint32 PonAdc34: 1;        /*## attribute PonAdc34 */
   /**
	* BitsName: pon_adc12
	* Description: Enable  power to ADC 1&2 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonAdc12: 1;        /*## attribute PonAdc12 */
   /**
	* BitsName: pon_chirp
	* Description: Enable  power to Chirp 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonChirp: 1;        /*## attribute PonChirp */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 4;        /*## attribute Reserved4 */
   /**
	* BitsName: pon_ser
	* Description: Enable  power to Serialiser 
	* 0 : power not enabled
	* 1: power is enabled
	*/
    uint32 PonSer: 1;        /*## attribute PonSer */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
}Nxp_Tef810x_Mod00_IpLevelPonEnableBits_t;
    /**
* Nxp_Tef810x_Mod00_ResetControlBits_t
* RegisterName: reset_control
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x01800000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: reset_ism
	* Description: Reset ISM register  space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	* Note: ISM is out of reset after a POR  to support start up
	*/
    uint32 ResetIsm: 1;        /*## attribute ResetIsm */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: reset_atb
	* Description: Reset ATB     register  space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAtb: 1;        /*## attribute ResetAtb */
   /**
	* BitsName: reset_lglobal_ldo
	* Description: Reset global LDO   register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetLglobalLdo: 1;        /*## attribute ResetLglobalLdo */
   /**
	* BitsName: reset_ssbmod
	* Description: Reset chirp  SSBMOD register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetSsbmod: 1;        /*## attribute ResetSsbmod */
   /**
	* BitsName: reset_tx3
	* Description: Reset chirp TX3 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx3: 1;        /*## attribute ResetTx3 */
   /**
	* BitsName: reset_tx2
	* Description: Reset chirp TX2 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx2: 1;        /*## attribute ResetTx2 */
   /**
	* BitsName: reset_tx1
	* Description: Reset chirp TX1 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetTx1: 1;        /*## attribute ResetTx1 */
   /**
	* BitsName: reset_rx4
	* Description: Reset chirp  RX4 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx4: 1;        /*## attribute ResetRx4 */
   /**
	* BitsName: reset_rx3
	* Description: Reset chirp RX3 register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx3: 1;        /*## attribute ResetRx3 */
   /**
	* BitsName: reset_rx2
	* Description: Reset chirp RX2  register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx2: 1;        /*## attribute ResetRx2 */
   /**
	* BitsName: reset_rx1
	* Description: Reset chirp RX1  register  space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetRx1: 1;        /*## attribute ResetRx1 */
   /**
	* BitsName: reset_master_clk
	* Description: Reset MC register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetMasterClk: 1;        /*## attribute ResetMasterClk */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: reset_lo_interface
	* Description: Reset lo interface register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetLoInterface: 1;        /*## attribute ResetLoInterface */
   /**
	* BitsName: reset_global_bias
	* Description: Reset global bias register space and function 
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetGlobalBias: 1;        /*## attribute ResetGlobalBias */
   /**
	* BitsName: reset_adc34
	* Description: Reset ADC34 register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAdc34: 1;        /*## attribute ResetAdc34 */
   /**
	* BitsName: reset_adc12
	* Description: Reset ADC12 register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetAdc12: 1;        /*## attribute ResetAdc12 */
   /**
	* BitsName: reset_chirp
	* Description: Reset chirp register space and function  reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetChirp: 1;        /*## attribute ResetChirp */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: reset_ser
	* Description: Reset serializer register space and function reset
	* 0 : IP registers and functions are  in reset state
	* 1: IP register and functions are out of reset
	*/
    uint32 ResetSer: 1;        /*## attribute ResetSer */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod00_ResetControlBits_t;
    /**
* Nxp_Tef810x_Mod00_FunctionalResetControlBits_t
* RegisterName: functional_reset_control
* 
* AddressRange: 0x070 - 0x074
* ResetValue: 0x01800000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: fn_reset_ism
	* Description: Reset ISM     function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* Note: ISM is out of reset after a POR  to support start up
	* 
	* In an application context, this reset shall not be used  ( no use case to apply this reset)
	*/
    uint32 FnResetIsm: 1;        /*## attribute FnResetIsm */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: fn_reset_atb
	* Description: Reset ATB    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetAtb: 1;        /*## attribute FnResetAtb */
   /**
	* BitsName: fn_reset_lglobal_ldo
	* Description: Reset global LDO    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* This reset is not used within the global LDO module
	*/
    uint32 FnResetLglobalLdo: 1;        /*## attribute FnResetLglobalLdo */
   /**
	* BitsName: fn_reset_ssbmod
	* Description: Reset chirp  SSBMOD  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetSsbmod: 1;        /*## attribute FnResetSsbmod */
   /**
	* BitsName: fn_reset_tx3
	* Description: Reset chirp  TX3 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx3: 1;        /*## attribute FnResetTx3 */
   /**
	* BitsName: fn_reset_tx2
	* Description: Reset chirp  TX2 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx2: 1;        /*## attribute FnResetTx2 */
   /**
	* BitsName: fn_reset_tx1
	* Description: Reset chirp  TX1  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetTx1: 1;        /*## attribute FnResetTx1 */
   /**
	* BitsName: fn_reset_rx4
	* Description: Not Used
	*/
    uint32 FnResetRx4: 1;        /*## attribute FnResetRx4 */
   /**
	* BitsName: fn_reset_rx3
	* Description: Not Used
	*/
    uint32 FnResetRx3: 1;        /*## attribute FnResetRx3 */
   /**
	* BitsName: fn_reset_rx2
	* Description: Not Used
	*/
    uint32 FnResetRx2: 1;        /*## attribute FnResetRx2 */
   /**
	* BitsName: fn_reset_rx1
	* Description: Not Used
	*/
    uint32 FnResetRx1: 1;        /*## attribute FnResetRx1 */
   /**
	* BitsName: fn_reset_master_clk
	* Description: Reset MC    function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetMasterClk: 1;        /*## attribute FnResetMasterClk */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: fn_reset_lo_interface
	* Description: Reset lo interface function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. No reason to apply this reset afterwards
	*/
    uint32 FnResetLoInterface: 1;        /*## attribute FnResetLoInterface */
   /**
	* BitsName: fn_reset_global_bias
	* Description: Reset global bias   function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetGlobalBias: 1;        /*## attribute FnResetGlobalBias */
   /**
	* BitsName: fn_reset_adc34
	* Description: Reset ADC34 function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetAdc34: 1;        /*## attribute FnResetAdc34 */
   /**
	* BitsName: fn_reset_adc12
	* Description: Reset ADC12   function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space.. The IP shall not be placed under reset in an application context
	*/
    uint32 FnResetAdc12: 1;        /*## attribute FnResetAdc12 */
   /**
	* BitsName: fn_reset_chirp
	* Description: Reset chirp  function 
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space..
	* In an application context this reset can be applied  based on application scenario  ( for example to stop an ongoing acquisition prematurely)
	*/
    uint32 FnResetChirp: 1;        /*## attribute FnResetChirp */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 4;        /*## attribute Reserved3 */
   /**
	* BitsName: fn_reset_ser
	* Description: Reset serializer  function
	* 0 : IP in reset state
	* 1: IP out of reset
	* 
	* On start up after  application of power ( PON), this reset shall be applied once after configuring the register space..
	* 
	* This reset shall be applied,  after any configuration regsiter changes to the IP register space
	*/
    uint32 FnResetSer: 1;        /*## attribute FnResetSer */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
}Nxp_Tef810x_Mod00_FunctionalResetControlBits_t;
    /**
* Nxp_Tef810x_Mod00_IntRawStatusBits_t
* RegisterName: INT_RAW_STATUS
* 
* AddressRange: 0x078 - 0x07C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 CrcErrorIntStatusRaw: 1;        /*## attribute CrcErrorIntStatusRaw */
   /**
	* BitsName: rf_powerdown_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RfPowerdownIntStatusRaw: 1;        /*## attribute RfPowerdownIntStatusRaw */
   /**
	* BitsName: rtm_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RtmIntStatusRaw: 1;        /*## attribute RtmIntStatusRaw */
   /**
	* BitsName: status_wdt_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 StatusWdtIntStatusRaw: 1;        /*## attribute StatusWdtIntStatusRaw */
   /**
	* BitsName: end_of_data_tnfr_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataTnfrIntStatusRaw: 1;        /*## attribute EndOfDataTnfrIntStatusRaw */
   /**
	* BitsName: end_of_data_acq_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataAcqIntStatusRaw: 1;        /*## attribute EndOfDataAcqIntStatusRaw */
   /**
	* BitsName: chirp_start_out_int_status_raw
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 ChirpStartOutIntStatusRaw: 1;        /*## attribute ChirpStartOutIntStatusRaw */
}Nxp_Tef810x_Mod00_IntRawStatusBits_t;
    /**
* Nxp_Tef810x_Mod00_IntMaskedStatusBits_t
* RegisterName: INT_MASKED_STATUS
* 
* AddressRange: 0x07C - 0x080
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 25;        /*## attribute Reserved0 */
   /**
	* BitsName: crc_error_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 CrcErrorIntStatusMasked: 1;        /*## attribute CrcErrorIntStatusMasked */
   /**
	* BitsName: rf_powerdown_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RfPowerdownIntStatusMasked: 1;        /*## attribute RfPowerdownIntStatusMasked */
   /**
	* BitsName: rtm_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 RtmIntStatusMasked: 1;        /*## attribute RtmIntStatusMasked */
   /**
	* BitsName: status_wdt_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 StatusWdtIntStatusMasked: 1;        /*## attribute StatusWdtIntStatusMasked */
   /**
	* BitsName: end_of_data_tnfr_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataTnfrIntStatusMasked: 1;        /*## attribute EndOfDataTnfrIntStatusMasked */
   /**
	* BitsName: end_of_data_acq_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 EndOfDataAcqIntStatusMasked: 1;        /*## attribute EndOfDataAcqIntStatusMasked */
   /**
	* BitsName: chirp_start_out_int_status_masked
	* Description: 0: interrupt not set
	* 1: interrupt set
	*/
    uint32 ChirpStartOutIntStatusMasked: 1;        /*## attribute ChirpStartOutIntStatusMasked */
}Nxp_Tef810x_Mod00_IntMaskedStatusBits_t;
    /**
* Nxp_Tef810x_Mod00_ScratchRegister1Bits_t
* RegisterName: scratch_register1
* 
* AddressRange: 0x080 - 0x084
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: scratch_register1
	* Description: RW register to store information during debugging/validation
	*/
    uint32 ScratchRegister1: 32;        /*## attribute ScratchRegister1 */
}Nxp_Tef810x_Mod00_ScratchRegister1Bits_t;
    /**
* Nxp_Tef810x_Mod00_ScratchRegister8Bits_t
* RegisterName: scratch_register8
* 
* AddressRange: 0x09C - 0x0A0
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: scratch_register8
	* Description: RW register to store information during debugging/validation
	*/
    uint32 ScratchRegister8: 30;        /*## attribute ScratchRegister8 */
   /**
	* BitsName: override_chirp_level_dynamic_power_chirp
	* Description: In case of dynamic power control at individual chirp level is selected, then
	* 0 : No action
	* 1 : power to the chirp is   enabled through out chirp sequence ( override default  chirp level power control)
	* 
	* Note: After powerup, this bit to be initialized to '0' as the flop holding this bit is non-resettable flop. So known value to be initialized after every powerup
	*/
    uint32 OverrideChirpLevelDynamicPowerChirp: 1;        /*## attribute OverrideChirpLevelDynamicPowerChirp */
   /**
	* BitsName: override_chirp_level_dynamic_power_adc
	* Description: In case of dynamic power control at individual chirp level is selected, then
	* 0 : No action
	* 1 : power to the ADC  is   enabled through out chirp sequence ( override default  chirp level power control)
	* 
	* Note: After powerup, this bit to be initialized to '0' as the flop holding this bit is non-resettable flop. So known value to be initialized after every powerup
	*/
    uint32 OverrideChirpLevelDynamicPowerAdc: 1;        /*## attribute OverrideChirpLevelDynamicPowerAdc */
}Nxp_Tef810x_Mod00_ScratchRegister8Bits_t;
    /**
* Nxp_Tef810x_Mod00_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00002301
*/
typedef struct  {
   /**
	* BitsName: Identifier
	* Description: This is the unique identifier of the module
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
   /**
	* BitsName: Major_revision
	* Description: Major revision i.e. implies software modifications
	*/
    uint32 MajorRevision: 4;        /*## attribute MajorRevision */
   /**
	* BitsName: Minor_revision
	* Description: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod00_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod00_ReadyintPadcontrolUnion_t
* Nxp_Tef810x_Mod00_ReadyintPadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ReadyintPadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ReadyintPadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t
* Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ChirpStartPadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t
* Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ErrorNPadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_ErrorResetPadcontrolUnion_t
* Nxp_Tef810x_Mod00_ErrorResetPadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ErrorResetPadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ErrorResetPadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_Tx1PadcontrolUnion_t
* Nxp_Tef810x_Mod00_Tx1PadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Tx1PadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Tx1PadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_Tx2PadcontrolUnion_t
* Nxp_Tef810x_Mod00_Tx2PadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Tx2PadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Tx2PadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_Tx3PadcontrolUnion_t
* Nxp_Tef810x_Mod00_Tx3PadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Tx3PadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Tx3PadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_MisoPadcontrolUnion_t
* Nxp_Tef810x_Mod00_MisoPadcontrolUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_MisoPadcontrolBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_MisoPadcontrolUnion_t;
/**
* Nxp_Tef810x_Mod00_LdoSerialiserSerControlUnion_t
* Nxp_Tef810x_Mod00_LdoSerialiserSerControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_LdoSerialiserSerControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_LdoSerialiserSerControlUnion_t;
/**
* Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlUnion_t
* Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlUnion_t;
/**
* Nxp_Tef810x_Mod00_LdoAdcControlUnion_t
* Nxp_Tef810x_Mod00_LdoAdcControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_LdoAdcControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_LdoAdcControlUnion_t;
/**
* Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t
* Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_LdoSsbmodControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t;
/**
* Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t
* Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Atb1EnRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t;
/**
* Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t
* Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Atb1AcEnRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t;
/**
* Nxp_Tef810x_Mod00_Atb2EnRegisterUnion_t
* Nxp_Tef810x_Mod00_Atb2EnRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Atb2EnRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Atb2EnRegisterUnion_t;
/**
* Nxp_Tef810x_Mod00_Atb2AcEnRegisterUnion_t
* Nxp_Tef810x_Mod00_Atb2AcEnRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_Atb2AcEnRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_Atb2AcEnRegisterUnion_t;
/**
* Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t
* Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_DynamicPowerControlEnableBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t;
/**
* Nxp_Tef810x_Mod00_DynamicPowerControlDelayUnion_t
* Nxp_Tef810x_Mod00_DynamicPowerControlDelayUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_DynamicPowerControlDelayBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_DynamicPowerControlDelayUnion_t;
/**
* Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t
* Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_SerialiserModeSelBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t;
/**
* Nxp_Tef810x_Mod00_ReadyIntControlUnion_t
* Nxp_Tef810x_Mod00_ReadyIntControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ReadyIntControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ReadyIntControlUnion_t;
/**
* Nxp_Tef810x_Mod00_IntEnableUnion_t
* Nxp_Tef810x_Mod00_IntEnableUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IntEnableBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IntEnableUnion_t;
/**
* Nxp_Tef810x_Mod00_IntClrUnion_t
* Nxp_Tef810x_Mod00_IntClrUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IntClrBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IntClrUnion_t;
/**
* Nxp_Tef810x_Mod00_IntSetUnion_t
* Nxp_Tef810x_Mod00_IntSetUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IntSetBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IntSetUnion_t;
/**
* Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t
* Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IpLevelClockEnableBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t;
/**
* Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t
* Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IpLevelPonEnableBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t;
/**
* Nxp_Tef810x_Mod00_ResetControlUnion_t
* Nxp_Tef810x_Mod00_ResetControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ResetControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ResetControlUnion_t;
/**
* Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t
* Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_FunctionalResetControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t;
/**
* Nxp_Tef810x_Mod00_IntRawStatusUnion_t
* Nxp_Tef810x_Mod00_IntRawStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IntRawStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IntRawStatusUnion_t;
/**
* Nxp_Tef810x_Mod00_IntMaskedStatusUnion_t
* Nxp_Tef810x_Mod00_IntMaskedStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_IntMaskedStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_IntMaskedStatusUnion_t;
/**
* Nxp_Tef810x_Mod00_ScratchRegister1Union_t
* Nxp_Tef810x_Mod00_ScratchRegister1Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ScratchRegister1Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ScratchRegister1Union_t;
/**
* Nxp_Tef810x_Mod00_ScratchRegister8Union_t
* Nxp_Tef810x_Mod00_ScratchRegister8Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ScratchRegister8Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ScratchRegister8Union_t;
/**
* Nxp_Tef810x_Mod00_ModuleidUnion_t
* Nxp_Tef810x_Mod00_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod00_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod00_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod00_CentralControlRegister_t
 * Nxp_Tef810x_Mod00_CentralControlRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: ReadyInt_PadControl
    * AddressOffset: 0x000
    * ResetValue: 0x00000321
    * Description: Interrupt pin pad controls. Control the pad configuration .
	* 
	* Default values are sufficient for most use case sand application
	* 
	* The O/P need to be explicitly enabled to receive an interrupt from Dolphin
    */
    Nxp_Tef810x_Mod00_ReadyintPadcontrolUnion_t ReadyintPadcontrol_ust;        /*## attribute ReadyintPadcontrol_ust */
  /**
    * RegisterName: Chirp_Start_PadControl
    * AddressOffset: 0x004
    * ResetValue: 0x00000321
    * Description: chirp_start pin pad controls.
	* Default values are sufficient for most use cases
	* 
	* This pin can be used both input and O/P mode.   To trigger Dolphin for data acquisition  through an external pin , then use this pin in input mode. If the Dolphin is in  SPI trigger mode for data acquisition, then this pin can be  configured in an O/P mode.
    */
    Nxp_Tef810x_Mod00_ChirpStartPadcontrolUnion_t ChirpStartPadcontrol_ust;        /*## attribute ChirpStartPadcontrol_ust */
  /**
    * RegisterName: Error_n_PadControl
    * AddressOffset: 0x008
    * ResetValue: 0x00000321
    * Description: error_n pin  pad controls.
	* Default values are sufficient for most use cases, exepct the O/P control(bit 0).
	* The O/P need to be explicitly enabled to the MCU at the end of  Dolphin start up process.
	* 
	* This pin is used for reporting safety errors within Dolphin.  By default (on reset) this pin will remain in input mode ( O/P not driven). An external pull down resistor (4.7k)  has to be used  to pull this pin to low on start.  Once MCU complete the required start-up of Dolphin IC, then this pin can be configured to O/P mode.  If there are no underlying errors within Dolphin, and start up is Ok, then the inner safety monitor with drive this pin to a logic high value.  If an error is reported within Dolphin based  then this pin is driven low by Dolphin indicating a safety issue within Dolphin.
    */
    Nxp_Tef810x_Mod00_ErrorNPadcontrolUnion_t ErrorNPadcontrol_ust;        /*## attribute ErrorNPadcontrol_ust */
  /**
    * RegisterName: Error_Reset_PadControl
    * AddressOffset: 0x00C
    * ResetValue: 0x00000321
    * Description: error_reset  pin  pad controls.
	* Default values are sufficient for most use cases, exepct the O/P control(bit 0).
	* This is an input pin.  Do not enable the O/P in functional mode.
	* 
	* This pin can be used by MCU  to reset a functional safety error within Dolphin.   Typically this will clear all the latched errors within the inner safety monitors. However if  fresh errors are reported, then the error_n pin may remain low.
	* Please note that it  is also possible to reset  errors within Dolphin through a SPI register write
    */
    Nxp_Tef810x_Mod00_ErrorResetPadcontrolUnion_t ErrorResetPadcontrol_ust;        /*## attribute ErrorResetPadcontrol_ust */
  /**
    * RegisterName: TX1_PadControl
    * AddressOffset: 0x010
    * ResetValue: 0x00001321
    * Description: TX unit 1 binary phase control  pin pad controls.
	* Default values are sufficient for most use cases, exepct the O/P control(bit 0).
	* This is an input pin.  Do not enable the O/P in functional mode.
    */
    Nxp_Tef810x_Mod00_Tx1PadcontrolUnion_t Tx1Padcontrol_ust;        /*## attribute Tx1Padcontrol_ust */
  /**
    * RegisterName: TX2_PadControl
    * AddressOffset: 0x014
    * ResetValue: 0x00001321
    * Description: TX unit 2 binary phase control  pin pad controls.
	* Default values are sufficient for most use cases, exepct the O/P control(bit 0).
	* This is an input pin.  Do not enable the O/P in functional mode.
    */
    Nxp_Tef810x_Mod00_Tx2PadcontrolUnion_t Tx2Padcontrol_ust;        /*## attribute Tx2Padcontrol_ust */
  /**
    * RegisterName: TX3_PadControl
    * AddressOffset: 0x018
    * ResetValue: 0x00001321
    * Description: TX unit 3 binary phase control  pin pad controls.
	* Default values are sufficient for most use cases, exepct the O/P control(bit 0).
	* This is an input pin.  Do not enable the O/P in functional mode.
    */
    Nxp_Tef810x_Mod00_Tx3PadcontrolUnion_t Tx3Padcontrol_ust;        /*## attribute Tx3Padcontrol_ust */
  /**
    * RegisterName: MISO_padControl
    * AddressOffset: 0x01C
    * ResetValue: 0x00000330
    * Description: MISO   pin pad controls.
	* Default values are sufficient for most use cases
	* This pad is  an O./P  pad and is directly controlled by the SS_N pin
    */
    Nxp_Tef810x_Mod00_MisoPadcontrolUnion_t MisoPadcontrol_ust;        /*## attribute MisoPadcontrol_ust */
  /**
    * RegisterName: Ldo_Serialiser_Ser_Control
    * AddressOffset: 0x020
    * ResetValue: 0x00000000
    * Description: LDO controls for the Serializer digital function.
    */
    Nxp_Tef810x_Mod00_LdoSerialiserSerControlUnion_t LdoSerialiserSerControl_ust;        /*## attribute LdoSerialiserSerControl_ust */
  /**
    * RegisterName: Ldo_Serialiser_csi2_Control
    * AddressOffset: 0x024
    * ResetValue: 0x00000000
    * Description: LDO controls for the CSI/DPHY portion of serializer.
    */
    Nxp_Tef810x_Mod00_LdoSerialiserCsi2ControlUnion_t LdoSerialiserCsi2Control_ust;        /*## attribute LdoSerialiserCsi2Control_ust */
  /**
    * RegisterName: Ldo_Adc_Control
    * AddressOffset: 0x028
    * ResetValue: 0x00000000
    * Description: LDO controls for the main ADC
    */
    Nxp_Tef810x_Mod00_LdoAdcControlUnion_t LdoAdcControl_ust;        /*## attribute LdoAdcControl_ust */
  /**
    * RegisterName: Ldo_Ssbmod_Control
    * AddressOffset: 0x02C
    * ResetValue: 0x00000000
    * Description: LDO controls for the SSBMOD (RFBIST)
    */
    Nxp_Tef810x_Mod00_LdoSsbmodControlUnion_t LdoSsbmodControl_ust;        /*## attribute LdoSsbmodControl_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x030
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: ATB1_en_register
    * AddressOffset: 0x034
    * ResetValue: 0x00000000
    * Description: This register is used only during ATB based testing/validation. This is not used in functional context.
	* Controls the function active on ATB1. One hot encoding is used so that only one function can be enabled at a  time on ATB channel
    */
    Nxp_Tef810x_Mod00_Atb1EnRegisterUnion_t Atb1EnRegister_ust;        /*## attribute Atb1EnRegister_ust */
  /**
    * RegisterName: ATB1_ac_en_register
    * AddressOffset: 0x038
    * ResetValue: 0x01110000
    * Description: This register is used only during ATB based testing/validation. This is not used in functional context.
    */
    Nxp_Tef810x_Mod00_Atb1AcEnRegisterUnion_t Atb1AcEnRegister_ust;        /*## attribute Atb1AcEnRegister_ust */
  /**
    * RegisterName: ATB2_en_register
    * AddressOffset: 0x03C
    * ResetValue: 0x00000000
    * Description: This register is used only during ATB based testing/validation. not_used in functional context.
	* Controls the function active on ATB2 channel.  One hot encoding is used so that only one function can be enabled at a  time on ATB channel
    */
    Nxp_Tef810x_Mod00_Atb2EnRegisterUnion_t Atb2EnRegister_ust;        /*## attribute Atb2EnRegister_ust */
  /**
    * RegisterName: ATB2_ac_en_register
    * AddressOffset: 0x040
    * ResetValue: 0x00110000
    * Description: This register is used only during ATB based testing/validation. This is not used in functional context.
    */
    Nxp_Tef810x_Mod00_Atb2AcEnRegisterUnion_t Atb2AcEnRegister_ust;        /*## attribute Atb2AcEnRegister_ust */
  /**
    * RegisterName: dynamic_power_control_enable
    * AddressOffset: 0x044
    * ResetValue: 0x00000000
    * Description: Register to control the dynamic power of Dolphin.  
	* 
	* Dynamic power control is  possible  at two level
	* 1. Dynamic power  control at chirp sequence level: When a module is selected for power control , then power to the module  is disabled outside  chirp sequence active period
	* 2. Dynamic power control at individual chirp level.: When a module is selected for power control , then power to the module  is disabled outside  individual chirp  active period ( only for validation. not for end user)
	* 2.a..  An overriding option is provided to avoid disabling power for Chirp and ADC   when option '2'is selected. Please refere to scratch_register8  for details
	* 
	* The following modules  can be brought under dynamic power control
	* 1. Chirp 
	* 2. Individual TX units
	* 3. Individual RX units
	* 4. Serializer
	* 5. ADC
	* 6 .LO interface  (only in stand alone Dolphin)
	* 
	* Within Dynamic power control, it is also possible to  choose  modules that are part of dynamic power control .
    */
    Nxp_Tef810x_Mod00_DynamicPowerControlEnableUnion_t DynamicPowerControlEnable_ust;        /*## attribute DynamicPowerControlEnable_ust */
  /**
    * RegisterName: dynamic_power_control_delay
    * AddressOffset: 0x048
    * ResetValue: 0x0000FFFF
    * Description: At the end of data acquisition ( chirp sequence level or at individual chirp level)  a timer delay is provided to switch off the power to the respective modules ..  This is primarily to avoid any race conditions within the system  ( for example acquired data is flushed out completely before disabling the units. In some cases). The timings are depends on the decimation  factor used.
	* Minimum values 
	* 
	* 
	* This value has to be  minimum  equal to the chirp reset time duration
    */
    Nxp_Tef810x_Mod00_DynamicPowerControlDelayUnion_t DynamicPowerControlDelay_ust;        /*## attribute DynamicPowerControlDelay_ust */
  /**
    * RegisterName: serialiser_mode_sel
    * AddressOffset: 0x04C
    * ResetValue: 0x00000000
    * Description: Software control register to select  the data interface. This register is active only if the respective functions are enabled through OTP.  For example if CSI2 is disabled through OTP, then it is not possible to select CSI2 mode through software
    */
    Nxp_Tef810x_Mod00_SerialiserModeSelUnion_t SerialiserModeSel_ust;        /*## attribute SerialiserModeSel_ust */
  /**
    * RegisterName: Ready_Int_Control
    * AddressOffset: 0x050
    * ResetValue: 0x01100090
    * Description: Software control register to control the interrupt polarity, and the type of interrupt required.
    */
    Nxp_Tef810x_Mod00_ReadyIntControlUnion_t ReadyIntControl_ust;        /*## attribute ReadyIntControl_ust */
  /**
    * RegisterName: INT_ENABLE
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: Interrupt enable register. If corresponding bit is set, then the interrupt is passed to MCU
	* crc_error_int:  Interrupt is raised  when a CRC checksum error is reported on the MISO lane ( For SPI write  complete payload is protected by CRC, fo SPI erad only the command +address field)
	* 
	* rf_powerdown_int : Interrupt is raised, when a RF power down event is triggered within Dolphin ( power down to TX,RX or chirp base don excessive power levels or temperature)
	* rtm_int : Interrupt from real time safety monitoring.  This bit is a redundant bit . In case of safety error the error_n pin is also asserted.
	* status_wdt_int: Periodic  timer interrupt from status monitoring timer.  On occurrence of this interrupt, a set of status monitoring actions need to be performed by MCU before start of next Radar acquisition cycle
	* end_of_data_tnfr_int : Indicate an end of data transfer  from the serializer at the end of a current  data acquisition cycle.  This is a delayed version of the end_of_data_acq_int/. The delay depends on the decimation factor selected
	* end_of_data_acq_int : Indicate an end of current data acquisition ( end of active ADC samples) from timing engine
    */
    Nxp_Tef810x_Mod00_IntEnableUnion_t IntEnable_ust;        /*## attribute IntEnable_ust */
  /**
    * RegisterName: INT_CLR
    * AddressOffset: 0x058
    * ResetValue: 0x00000000
    * Description: Interrupt clear register.A write will clear the interrupt status , provided there are no underlying interrupt present.
	* While clearing  it is possible to read back the  status of the interrupt before clearing. For this  in the SPI protocol C/S command bit need to be set to '0'
	* 
	* rf_powerdown_int : Interrupt is raised, when a RF power down event is triggered within Dolphin ( power down to TX,RX or chirp base don excessive power levels or temperature)
	* rtm_int : Interrupt from real time safety monitoring.  This bit is a redundant bit . In case of safety error the error_n pin is also asserted.
	* status_wdt_int: Periodic  timer interrupt from status monitoring timer.  On occurrence of this interrupt, a set of status monitoring actions need to be performed by MCU before start of next Radar acquisition cycle
	* end_of_data_tnfr_int : Indicate an end of data transfer  from the serializer at the end of a current  data acquisition cycle.  This is a delayed version of the end_of_data_acq_int/. The delay depends on the decimation factor selected
	* end_of_data_acq_int : Indicate an end of current data acquisition ( end of active ADC samples) from timing engine
    */
    Nxp_Tef810x_Mod00_IntClrUnion_t IntClr_ust;        /*## attribute IntClr_ust */
  /**
    * RegisterName: INT_SET
    * AddressOffset: 0x05C
    * ResetValue: 0x00000000
    * Description: Interrupt set register.A write will set the interrupt status. This register can be used for testing the interrupt functions at the MCU without actually creating an interrupt event
	* 
	* rf_powerdown_int : Interrupt is raised, when a RF power down event is triggered within Dolphin ( power down to TX,RX or chirp base don excessive power levels or temperature)
	* rtm_int : Interrupt from real time safety monitoring.  This bit is a redundant bit . In case of safety error the error_n pin is also asserted.
	* status_wdt_int: Periodic  timer interrupt from status monitoring timer.  On occurrence of this interrupt, a set of status monitoring actions need to be performed by MCU before start of next Radar acquisition cycle
	* end_of_data_tnfr_int : Indicate an end of data transfer  from the serializer at the end of a current  data acquisition cycle.  This is a delayed version of the end_of_data_acq_int/. The delay depends on the decimation factor selected
	* end_of_data_acq_int : Indicate an end of current data acquisition ( end of active ADC samples) from timing engine
    */
    Nxp_Tef810x_Mod00_IntSetUnion_t IntSet_ust;        /*## attribute IntSet_ust */
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x060
    * ResetValue: 0x00000028
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: ip_level_clock_enable
    * AddressOffset: 0x064
    * ResetValue: 0x01800000
    * Description: Before accessing a block, the 40 MHz clock has to be enabled for that block.
	* By default  clock to all functional  modules are disabled  ( barring OTP , ISM ).
	* Clock to  a module shall be enabled before accessing the IP.  Generally this is done as part of the start up process.  Clock to specific modules   shall be  disabled at the  end of a configuration write primarily as a mechanism to reduce interference.  However in general not  required or recommended .
    */
    Nxp_Tef810x_Mod00_IpLevelClockEnableUnion_t IpLevelClockEnable_ust;        /*## attribute IpLevelClockEnable_ust */
  /**
    * RegisterName: ip_level_pon_enable
    * AddressOffset: 0x068
    * ResetValue: 0x01800000
    * Description: Analog power enables to individual modules. The modules which are not enabled from OTP will be always read back as disabled.
	* 
	* These are static power enable signals to corresponding IP's ..  Once this bit is set, then actual application of power  can be controllerd through the dynamic_power_control_enable (0x44)  register.. ( power is always applied or controlled per chirp sequence level)
    */
    Nxp_Tef810x_Mod00_IpLevelPonEnableUnion_t IpLevelPonEnable_ust;        /*## attribute IpLevelPonEnable_ust */
  /**
    * RegisterName: reset_control
    * AddressOffset: 0x06C
    * ResetValue: 0x01800000
    * Description: IP  level reset control
	* On power on or on application of reset  ( on reset release)  the reset to ISM space is automatically released by  Tef810x itself
	* OTP module can be resetted only  by power cycle ( pin reset is not  connected to OTP mnodule)
	* This register is used to apply a total reset ( register space and functional space of the IP)
    */
    Nxp_Tef810x_Mod00_ResetControlUnion_t ResetControl_ust;        /*## attribute ResetControl_ust */
  /**
    * RegisterName: functional_reset_control
    * AddressOffset: 0x070
    * ResetValue: 0x01800000
    * Description: IP   level functional reset control
	* On power on or on application of reset  ( on reset release)  the reset to ISM space is automatically released by  Tef810x itself
	* OTP module can be resetted only  by power cycle ( pin reset is not  connected to OTP mnodule)
	* This register is used to apply a total reset ( register space and functional space of the IP)
    */
    Nxp_Tef810x_Mod00_FunctionalResetControlUnion_t FunctionalResetControl_ust;        /*## attribute FunctionalResetControl_ust */
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x074
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: INT_RAW_STATUS
    * AddressOffset: 0x078
    * ResetValue: 0x00000000
    * Description: Indicates the RAW interrupt status from the source.
	* Useful for debugging
	* 
	* rf_powerdown_int : Interrupt is raised, when a RF power down event is triggered within Dolphin ( power down to TX,RX or chirp base don excessive power levels or temperature)
	* rtm_int : Interrupt from real time safety monitoring.  This bit is a redundant bit . In case of safety error the error_n pin is also asserted.
	* status_wdt_int: Periodic  timer interrupt from status monitoring timer.  On occurrence of this interrupt, a set of status monitoring actions need to be performed by MCU before start of next Radar acquisition cycle
	* end_of_data_tnfr_int : Indicate an end of data transfer  from the serializer at the end of a current  data acquisition cycle.  This is a delayed version of the end_of_data_acq_int/. The delay depends on the decimation factor selected
	* end_of_data_acq_int : Indicate an end of current data acquisition ( end of active ADC samples) from timing engine
    */
    Nxp_Tef810x_Mod00_IntRawStatusUnion_t IntRawStatus_ust;        /*## attribute IntRawStatus_ust */
  /**
    * RegisterName: INT_MASKED_STATUS
    * AddressOffset: 0x07C
    * ResetValue: 0x00000000
    * Description: Indicates the masked  interrupt status ( based on corresponding interrupt enable bit addr 0x54)
	* crc_error_int: Interrupt is raised when a CRC error happens on SPI write data packet or in the SPI read command packet 
	* rf_powerdown_int : Interrupt is raised, when a RF power down event is triggered within Dolphin ( power down to TX,RX or chirp base don excessive power levels or temperature)
	* rtm_int : Interrupt from real time safety monitoring.  This bit is a redundant bit . In case of safety error the error_n pin is also asserted.
	* status_wdt_int: Periodic  timer interrupt from status monitoring timer.  On occurrence of this interrupt, a set of status monitoring actions need to be performed by MCU before start of next Radar acquisition cycle
	* end_of_data_tnfr_int : Indicate an end of data transfer  from the serializer at the end of a current  data acquisition cycle.  This is a delayed version of the end_of_data_acq_int/. The delay depends on the decimation factor selected
	* end_of_data_acq_int : Indicate an end of current data acquisition ( end of active ADC samples) from timing engine
    */
    Nxp_Tef810x_Mod00_IntMaskedStatusUnion_t IntMaskedStatus_ust;        /*## attribute IntMaskedStatus_ust */
  /**
    * RegisterName: scratch_register1
    * AddressOffset: 0x080
    * ResetValue: 0x00000000
    * Description: RW register to store information during debugging/validation. 
	* This register is implemented with non-resettable flops. So after powerup, this register to be initialized with the proper value for further usage
    */
    Nxp_Tef810x_Mod00_ScratchRegister1Union_t ScratchRegister1_ust;        /*## attribute ScratchRegister1_ust */
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x094
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x098
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: scratch_register8
    * AddressOffset: 0x09C
    * ResetValue: 0x00000000
    * Description: Register to override dynamic power control at individual chirp level for Chirp and ADC modules of Dolphin.   Useful only dynamic_power_control_enable (ox44) dy_power_mode_sel (bit 16) I sset to '1
	* 
	* This register is implemented with non-resettable flops (especially bit 0 and bit 1 are used for dynamic powerdown mode). So after powerup, this register to be initialized with the proper value for further usage
    */
    Nxp_Tef810x_Mod00_ScratchRegister8Union_t ScratchRegister8_ust;        /*## attribute ScratchRegister8_ust */

    uint32 gap01_au32[960];        /* gap 1 in register space */  /**
    * RegisterName: Reserved09
    * AddressOffset: 0xFA0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0xFA4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0xFA8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0xFB0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0xFB4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0xFB8
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;

    uint32 gap03_au32[13];        /* gap 3 in register space */  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0xFF0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;

    uint32 gap04_au32[2];        /* gap 4 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00002301
    * Description: Register with details of Module ID and Version number
    */
    Nxp_Tef810x_Mod00_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod00_CentralControlRegister_t;

#endif
