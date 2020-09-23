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
* @NXP_TEF810X_ChirpAfc.h
*/
#ifndef NXP_TEF810X_CHIRPAFC_H
#define NXP_TEF810X_CHIRPAFC_H
#include "Std_Types.h"

#define CHIRP_AFC_MODULE_ADDRESS 0x06
/**
*NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16
* RegisterName: MOD06_filter_register_profile0
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x60070017
*/
#define NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE0_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE0_U16
* RegisterName: MOD06_filter_par_register_profile0
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x52921616
*/
#define NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE0_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16
* RegisterName: MOD06_vco_register_profile0
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x000F0F00
*/
#define NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE0_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE1_U16
* RegisterName: MOD06_filter_register_profile1
* AccessMode: READWRITE
* AddressRange: 0x000C - 0x0010
* ResetValue: 0x60070017
*/
#define NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE1_U16 (uint16)0x000C
/**
*NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE1_U16
* RegisterName: MOD06_filter_par_register_profile1
* AccessMode: READWRITE
* AddressRange: 0x0010 - 0x0014
* ResetValue: 0x52921616
*/
#define NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE1_U16 (uint16)0x0010
/**
*NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16
* RegisterName: MOD06_vco_register_profile1
* AccessMode: READWRITE
* AddressRange: 0x0014 - 0x0018
* ResetValue: 0x000F0F00
*/
#define NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE1_U16 (uint16)0x0014
/**
*NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE2_U16
* RegisterName: MOD06_filter_register_profile2
* AccessMode: READWRITE
* AddressRange: 0x0018 - 0x001C
* ResetValue: 0x60070017
*/
#define NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE2_U16 (uint16)0x0018
/**
*NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE2_U16
* RegisterName: MOD06_filter_par_register_profile2
* AccessMode: READWRITE
* AddressRange: 0x001C - 0x0020
* ResetValue: 0x52921616
*/
#define NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE2_U16 (uint16)0x001C
/**
*NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16
* RegisterName: MOD06_vco_register_profile2
* AccessMode: READWRITE
* AddressRange: 0x0020 - 0x0024
* ResetValue: 0x000F0F00
*/
#define NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE2_U16 (uint16)0x0020
/**
*NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16
* RegisterName: MOD06_filter_register_profile3
* AccessMode: READWRITE
* AddressRange: 0x0024 - 0x0028
* ResetValue: 0x60070017
*/
#define NXP_TEF810X_MOD06_FILTER_REGISTER_PROFILE3_U16 (uint16)0x0024
/**
*NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE3_U16
* RegisterName: MOD06_filter_par_register_profile3
* AccessMode: READWRITE
* AddressRange: 0x0028 - 0x002C
* ResetValue: 0x52921616
*/
#define NXP_TEF810X_MOD06_FILTER_PAR_REGISTER_PROFILE3_U16 (uint16)0x0028
/**
*NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16
* RegisterName: MOD06_vco_register_profile3
* AccessMode: READWRITE
* AddressRange: 0x002C - 0x0030
* ResetValue: 0x000F0F00
*/
#define NXP_TEF810X_MOD06_VCO_REGISTER_PROFILE3_U16 (uint16)0x002C
/**
*NXP_TEF810X_MOD06_CP_REGISTER_U16
* RegisterName: MOD06_cp_register
* AccessMode: READWRITE
* AddressRange: 0x0030 - 0x0034
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_CP_REGISTER_U16 (uint16)0x0030
/**
*NXP_TEF810X_MOD06_VCO_BUFFER_LDO_REGISTER_U16
* RegisterName: MOD06_vco_buffer_ldo_register
* AccessMode: READWRITE
* AddressRange: 0x0034 - 0x0038
* ResetValue: 0x0000000F
*/
#define NXP_TEF810X_MOD06_VCO_BUFFER_LDO_REGISTER_U16 (uint16)0x0034
/**
*NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16
* RegisterName: MOD06_cppfd_ldo_register
* AccessMode: READWRITE
* AddressRange: 0x0038 - 0x003C
* ResetValue: 0x0000000F
*/
#define NXP_TEF810X_MOD06_CPPFD_LDO_REGISTER_U16 (uint16)0x0038
/**
*NXP_TEF810X_MOD06_DIVIDER_LDO_REGISTER_U16
* RegisterName: MOD06_divider_ldo_register
* AccessMode: READWRITE
* AddressRange: 0x003C - 0x0040
* ResetValue: 0x0000000F
*/
#define NXP_TEF810X_MOD06_DIVIDER_LDO_REGISTER_U16 (uint16)0x003C
/**
*NXP_TEF810X_MOD06_BIAS_BLOCK_REGISTER_U16
* RegisterName: MOD06_bias_block_register
* AccessMode: READWRITE
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_BIAS_BLOCK_REGISTER_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD06_BUFFER_REGISTER_U16
* RegisterName: MOD06_buffer_register
* AccessMode: READWRITE
* AddressRange: 0x0044 - 0x0048
* ResetValue: 0x00000110
*/
#define NXP_TEF810X_MOD06_BUFFER_REGISTER_U16 (uint16)0x0044
/**
*NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16
* RegisterName: MOD06_divide_force_register
* AccessMode: READWRITE
* AddressRange: 0x0048 - 0x004C
* ResetValue: 0x0000011B
*/
#define NXP_TEF810X_MOD06_DIVIDE_FORCE_REGISTER_U16 (uint16)0x0048
/**
*NXP_TEF810X_MOD06_LOOP_DYNAMIC_REG_0_U16
* RegisterName: MOD06_loop_dynamic_reg_0
* AccessMode: READWRITE
* AddressRange: 0x004C - 0x0050
* ResetValue: 0x0015150F
*/
#define NXP_TEF810X_MOD06_LOOP_DYNAMIC_REG_0_U16 (uint16)0x004C
/**
*NXP_TEF810X_MOD06_LPF_VTUNE_VCO_STATUS_U16
* RegisterName: MOD06_lpf_vtune_vco_status
* AccessMode: READ
* AddressRange: 0x0050 - 0x0054
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_LPF_VTUNE_VCO_STATUS_U16 (uint16)0x0050
/**
*NXP_TEF810X_MOD06_FUNCSAFE_MON_VTUNE_VCO_U16
* RegisterName: MOD06_funcsafe_mon_vtune_vco
* AccessMode: READWRITE
* AddressRange: 0x0054 - 0x0058
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_FUNCSAFE_MON_VTUNE_VCO_U16 (uint16)0x0054
/**
*NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16
* RegisterName: MOD06_funcsafe_mon_unlock_vco
* AccessMode: READWRITE
* AddressRange: 0x0058 - 0x005C
* ResetValue: 0x00100020
*/
#define NXP_TEF810X_MOD06_FUNCSAFE_MON_UNLOCK_VCO_U16 (uint16)0x0058
/**
*NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16
* RegisterName: MOD06_funcsafe_mon_level_vco
* AccessMode: READWRITE
* AddressRange: 0x005C - 0x0060
* ResetValue: 0x00007777
*/
#define NXP_TEF810X_MOD06_FUNCSAFE_MON_LEVEL_VCO_U16 (uint16)0x005C
/**
*NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16
* RegisterName: MOD06_funcsafe_mon_temperature_vco
* AccessMode: READWRITE
* AddressRange: 0x0060 - 0x0064
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_FUNCSAFE_MON_TEMPERATURE_VCO_U16 (uint16)0x0060
/**
*NXP_TEF810X_MOD06_CONTROL_SPARE_U16
* RegisterName: MOD06_control_spare
* AccessMode: READWRITE
* AddressRange: 0x006C - 0x0070
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_CONTROL_SPARE_U16 (uint16)0x006C
/**
*NXP_TEF810X_MOD06_CAL_LO_DET_U16
* RegisterName: MOD06_cal_lo_det
* AccessMode: READWRITE
* AddressRange: 0x0070 - 0x0074
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_CAL_LO_DET_U16 (uint16)0x0070
/**
*NXP_TEF810X_MOD06_REF_CNTR_INIT_U16
* RegisterName: MOD06_ref_cntr_init
* AccessMode: READWRITE
* AddressRange: 0x007C - 0x0080
* ResetValue: 0x01E00028
*/
#define NXP_TEF810X_MOD06_REF_CNTR_INIT_U16 (uint16)0x007C
/**
*NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16
* RegisterName: MOD06_freq_counter_start
* AccessMode: READWRITE
* AddressRange: 0x0080 - 0x0084
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD06_FREQ_COUNTER_START_U16 (uint16)0x0080
/**
*NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16
* RegisterName: MOD06_freq_counter_read_value
* AccessMode: READ
* AddressRange: 0x0084 - 0x0088
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_FREQ_COUNTER_READ_VALUE_U16 (uint16)0x0084
/**
*NXP_TEF810X_MOD06_REF_COUNTER_READ_VALUE_U16
* RegisterName: MOD06_ref_counter_read_value
* AccessMode: READ
* AddressRange: 0x0088 - 0x008C
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_REF_COUNTER_READ_VALUE_U16 (uint16)0x0088
/**
*NXP_TEF810X_MOD06_ATB_U16
* RegisterName: MOD06_atb
* AccessMode: READWRITE
* AddressRange: 0x0098 - 0x009C
* ResetValue: 0x000000FF
*/
#define NXP_TEF810X_MOD06_ATB_U16 (uint16)0x0098
/**
*NXP_TEF810X_MOD06_TEST_ERROR_FLAG_STATUS_U16
* RegisterName: MOD06_test_error_flag_status
* AccessMode: READ
* AddressRange: 0x00A8 - 0x00AC
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_TEST_ERROR_FLAG_STATUS_U16 (uint16)0x00A8
/**
*NXP_TEF810X_MOD06_DIVIDE_FREQ_COUNTER_START_U16
* RegisterName: MOD06_divide_freq_counter_start
* AccessMode: READWRITE
* AddressRange: 0x00BC - 0x00C0
* ResetValue: 0x00000100
*/
#define NXP_TEF810X_MOD06_DIVIDE_FREQ_COUNTER_START_U16 (uint16)0x00BC
/**
*NXP_TEF810X_MOD06_DIVIDE_FREQ_COUNTER_READ_VALUE_U16
* RegisterName: MOD06_divide_freq_counter_read_value
* AccessMode: READ
* AddressRange: 0x00C0 - 0x00C4
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD06_DIVIDE_FREQ_COUNTER_READ_VALUE_U16 (uint16)0x00C0
/**
*NXP_TEF810X_MOD06_MODULEID_U16
* RegisterName: MOD06_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00063301
*/
#define NXP_TEF810X_MOD06_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod06_FILTER_REGISTER_PROFILEBits_t
* RegisterName: filter_register_profile
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: ctl_lpf_prog_force_voltage_spi_profile0
	* Description: Program the force vtune voltage
	*/
    uint32 CtlLpfProgForceVoltageSpiProfile0: 7;        /*## attribute CtlLpfProgForceVoltageSpiProfile0 */
   /**
	* BitsName: ctl_cp_ioffset_updn_spi_profile0
	* Description: Direction of the charge pump offset
	* 1 :  Pmos inject current 
	* 0 :  Nmos substract current
	*/
    uint32 CtlCpIoffsetUpdnSpiProfile0: 1;        /*## attribute CtlCpIoffsetUpdnSpiProfile0 */
   /**
	* BitsName: ctl_lpf_force_vtune_en_spi_profile0
	* Description: Enable the force vtune circuit
	* 1 :  Enable force vtune circuit
	* 0 :  Disable  force vtune circuit
	*/
    uint32 CtlLpfForceVtuneEnSpiProfile0: 1;        /*## attribute CtlLpfForceVtuneEnSpiProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_lpf_ext_en_spi_profile0
	* Description: Enable external VCO tune voltage.
	* 1 :  Enable external vco tune voltage
	* 0 :  Disable external vco tune voltage
	*/
    uint32 CtlLpfExtEnSpiProfile0: 1;        /*## attribute CtlLpfExtEnSpiProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_lpf_int_en_spi_profile0
	* Description: Enable internal loop filter
	* 1 :  Enable loop filter
	* 0 :  Disable loop filter
	*/
    uint32 CtlLpfIntEnSpiProfile0: 1;        /*## attribute CtlLpfIntEnSpiProfile0 */
   /**
	* BitsName: ctl_cp_slice_en_spi_profile0
	* Description: Enable cp slices (enable two slices 300uA). Every bit corresponds to one slice.
	*/
    uint32 CtlCpSliceEnSpiProfile0: 8;        /*## attribute CtlCpSliceEnSpiProfile0 */
   /**
	* BitsName: ctl_ibias_cp_150u_spi_profile0
	* Description: Program current of the CP (latest versions is closer to 100uA)
	*/
    uint32 CtlIbiasCp150USpiProfile0: 6;        /*## attribute CtlIbiasCp150USpiProfile0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_FilterRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_FILTER_PAR_REGISTER_PROFILEBits_t
* RegisterName: filter_par_register_profile
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: ctl_lpf_R1_spi_profile0
	* Description: Select loop filter res. R1
	*/
    uint32 CtlLpfR1SpiProfile0: 5;        /*## attribute CtlLpfR1SpiProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_lpf_R2_spi_profile0
	* Description: Select loop filter res.R2
	*/
    uint32 CtlLpfR2SpiProfile0: 5;        /*## attribute CtlLpfR2SpiProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_lpf_C1_spi_profile0
	* Description: Select loop filter cap. C1
	*/
    uint32 CtlLpfC1SpiProfile0: 5;        /*## attribute CtlLpfC1SpiProfile0 */
   /**
	* BitsName: ctl_lpf_C2_spi_profile0
	* Description: Select loop filter cap. C2
	*/
    uint32 CtlLpfC2SpiProfile0: 5;        /*## attribute CtlLpfC2SpiProfile0 */
   /**
	* BitsName: ctl_lpf_C3_spi_profile0
	* Description: Select loop filter cap. C3
	*/
    uint32 CtlLpfC3SpiProfile0: 5;        /*## attribute CtlLpfC3SpiProfile0 */
   /**
	* BitsName: ctl_lpf_vtune_monitor_en_spi_profile0
	* Description: Enable the vtune monitor
	* 1 :  Enable vtune monitor
	* 0 :  Disable  vtune monitor
	*/
    uint32 CtlLpfVtuneMonitorEnSpiProfile0: 1;        /*## attribute CtlLpfVtuneMonitorEnSpiProfile0 */
}Nxp_Tef810x_Mod06_FilterParRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_VCO_REGISTER_PROFILEBits_t
* RegisterName: vco_register_profile
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: ctl_vco_coarse_tuning_spi_profile0
	* Description: Select Sub-band VCO
	*/
    uint32 CtlVcoCoarseTuningSpiProfile0: 7;        /*## attribute CtlVcoCoarseTuningSpiProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_vco_ivco_fine_spi_profile0
	* Description: Select current VCO
	*/
    uint32 CtlVcoIvcoFineSpiProfile0: 5;        /*## attribute CtlVcoIvcoFineSpiProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_vco_r_ibias_set_spi_profile0
	* Description: Select resistor used for VCO current generation
	*/
    uint32 CtlVcoRIbiasSetSpiProfile0: 5;        /*## attribute CtlVcoRIbiasSetSpiProfile0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_vco_bandwidth_spi_profile0
	* Description: Select VCO bandwidth:
	* 0: narrow bandwidth 
	* 1: large bandwidth
	*/
    uint32 CtlVcoBandwidthSpiProfile0: 1;        /*## attribute CtlVcoBandwidthSpiProfile0 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_vco_en_spi_profile0
	* Description: Enable VCO 
	* 1 :  Enable VCO
	* 0 :  Disable VCO
	*/
    uint32 CtlVcoEnSpiProfile0: 1;        /*## attribute CtlVcoEnSpiProfile0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod06_VcoRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_CP_REGISTERBits_t
* RegisterName: cp_register
* 
* AddressRange: 0xREADWRITE - 0x030
* ResetValue: 0x00000034
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 8;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_cp_force_up_spi
	* Description: Force the Charge Pump up 
	* 1 :  Increase CP current
	* 0 :  No action
	*/
    uint32 CtlCpForceUpSpi: 1;        /*## attribute CtlCpForceUpSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_cp_force_dn_spi
	* Description: Force the Charge Pump down
	* 1 : Decrease CP current
	* 0 :  No action
	*/
    uint32 CtlCpForceDnSpi: 1;        /*## attribute CtlCpForceDnSpi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: ctl_cp_en_spi
	* Description: Enable charge pump 
	* 1 :  Enable CP 
	* 0 :  Disable CP
	*/
    uint32 CtlCpEnSpi: 1;        /*## attribute CtlCpEnSpi */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
   /**
	* BitsName: ctl_cp_replica_bias_en_spi
	* Description: Enable charge pump replica bias circuit (improve linearity)
	* 1 :  Enable CP replica bias
	* 0 :  Disable CP replica bias
	*/
    uint32 CtlCpReplicaBiasEnSpi: 1;        /*## attribute CtlCpReplicaBiasEnSpi */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 3;        /*## attribute Reserved8 */
}Nxp_Tef810x_Mod06_CpRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_VCO_BUFFER_LDO_REGISTERBits_t
* RegisterName: vco_buffer_ldo_register
* 
* AddressRange: 0xREADWRITE - 0x034
* ResetValue: 0x00000038
*/
typedef struct  {
   /**
	* BitsName: ctl_ldo_vco_sel_vout_spi
	* Description: Select vout of VCO LDO
	*/
    uint32 CtlLdoVcoSelVoutSpi: 5;        /*## attribute CtlLdoVcoSelVoutSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_vco_en_spi
	* Description: Enable VCO LDO
	* 1 :  Enable LDO
	* 0 :  Disable LDO
	*/
    uint32 CtlLdoVcoEnSpi: 1;        /*## attribute CtlLdoVcoEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod06_VcoBufferLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_CPPFD_LDO_REGISTERBits_t
* RegisterName: cppfd_ldo_register
* 
* AddressRange: 0xREADWRITE - 0x038
* ResetValue: 0x0000003C
*/
typedef struct  {
   /**
	* BitsName: ctl_ldo_cppfd_sel_vout_spi
	* Description: Select vout PFDCP LDO
	*/
    uint32 CtlLdoCppfdSelVoutSpi: 5;        /*## attribute CtlLdoCppfdSelVoutSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_cppfd_en_spi
	* Description: Enable PFDCP LDO
	* 1 :  Enable LDO
	* 0 :  Disable LDO
	*/
    uint32 CtlLdoCppfdEnSpi: 1;        /*## attribute CtlLdoCppfdEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod06_CppfdLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_DIVIDER_LDO_REGISTERBits_t
* RegisterName: divider_ldo_register
* 
* AddressRange: 0xREADWRITE - 0x03C
* ResetValue: 0x00000040
*/
typedef struct  {
   /**
	* BitsName: ctl_ldo_divider_sel_vout_spi
	* Description: Select vout  Divider LDO
	*/
    uint32 CtlLdoDividerSelVoutSpi: 5;        /*## attribute CtlLdoDividerSelVoutSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_divider_en_spi
	* Description: Enable Divider LDO
	* 1 :  Enable Divider LDO
	* 0 :  Disable Divider LDO
	*/
    uint32 CtlLdoDividerEnSpi: 1;        /*## attribute CtlLdoDividerEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod06_DividerLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_BIAS_BLOCK_REGISTERBits_t
* RegisterName: bias_block_register
* 
* AddressRange: 0xREADWRITE - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: ctl_ibias_div_350u_en_spi
	* Description: Enable current of the dividers
	* 1 :  Enable divider current
	* 0 :  Disable  divider current
	*/
    uint32 CtlIbiasDiv350UEnSpi: 1;        /*## attribute CtlIbiasDiv350UEnSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ibias_bist_dac_200u_en_spi
	* Description: Enable current rms detector (name is missleading)
	* 1 :  Enable rms detector
	* 0 :  Disable rms detector
	*/
    uint32 CtlIbiasBistDac200UEnSpi: 1;        /*## attribute CtlIbiasBistDac200UEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ibias_cp_opamp_100u_en_spi
	* Description: Enable current of the CP opamp
	* 1 :  Enable current
	* 0 :  Disable current
	*/
    uint32 CtlIbiasCpOpamp100UEnSpi: 1;        /*## attribute CtlIbiasCpOpamp100UEnSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 6;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 2;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_ibias_LD_10u_en_spi
	* Description: Enable current of the Lock detector
	* 1 :  Enable lock detector
	* 0 :  Disable lock detector
	*/
    uint32 CtlIbiasLd10UEnSpi: 1;        /*## attribute CtlIbiasLd10UEnSpi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_ibias_VAM_100u_en_spi
	* Description: Enable current of the VCO amplitude monitor
	* 1 :  Enable vco amplitude monitor
	* 0 :  Disable vco amplitude monitor
	*/
    uint32 CtlIbiasVam100UEnSpi: 1;        /*## attribute CtlIbiasVam100UEnSpi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: ctl_ibias_TVN_20u_en_spi
	* Description: Enable current of the Tuning Voltage Monitor
	* 1 :  Enable tune current
	* 0 :  Disable tune current
	*/
    uint32 CtlIbiasTvn20UEnSpi: 1;        /*## attribute CtlIbiasTvn20UEnSpi */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 2;        /*## attribute Reserved7 */
   /**
	* BitsName: ctl_ibias_en_spi
	* Description: Enable all the biasing block
	* 1 :  Enable Bias
	* 0 :  Disable Bias
	*/
    uint32 CtlIbiasEnSpi: 1;        /*## attribute CtlIbiasEnSpi */
}Nxp_Tef810x_Mod06_BiasBlockRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_BUFFER_REGISTERBits_t
* RegisterName: buffer_register
* 
* AddressRange: 0xREADWRITE - 0x044
* ResetValue: 0x00000048
*/
typedef struct  {
   /**
	* BitsName: ctl_buffer_480meg_pol_spi
	* Description: Select signal polarity 480MHz buffer (in case it is balanced 0 degrees or 180 degrees) 
	* 1 :  180 degree
	* 0 :  0 degree (reset value for costumers)
	*/
    uint32 CtlBuffer480MegPolSpi: 1;        /*## attribute CtlBuffer480MegPolSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_buffer_480meg_bal_spi
	* Description: Select balanced or unbalanced signal 480MHz buffer (used for debugging)
	* 1 :  balanced (reset value for costumers)
	* 0 :  unbalanced
	*/
    uint32 CtlBuffer480MegBalSpi: 1;        /*## attribute CtlBuffer480MegBalSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_buffer_480meg_en_spi
	* Description: Enable 480MHz buffer
	* 1 :  Enable 480MHz buffer
	* 0 :  Disable 480MHz buffer
	*/
    uint32 CtlBuffer480MegEnSpi: 1;        /*## attribute CtlBuffer480MegEnSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_BufferRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_DIVIDE_FORCE_REGISTERBits_t
* RegisterName: divide_force_register
* 
* AddressRange: 0xREADWRITE - 0x048
* ResetValue: 0x0000004C
*/
typedef struct  {
   /**
	* BitsName: ctl_div_force
	* Description: defines the PLL loop back divider (26-28[dec] are allowed settings). Requires 'ctl_force_divider' to be set (otherwise the divider is under control of sweep engine)
	*/
    uint32 CtlDivForce: 6;        /*## attribute CtlDivForce */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_force_divider
	* Description: enables forcing a PLL loop back divider. If set, divider is programmed to the setting of 'ctl_div_force' (see below)
	* 1 :  Enable pll loop back divider
	* 0 :  Disable pll loop back divider
	*/
    uint32 CtlForceDivider: 1;        /*## attribute CtlForceDivider */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_en_rf_div_spi
	* Description: Enable Divider (not used, disabled from the LDO)
	* 1 :  Enable divider
	* 0 :  Disable divider
	*/
    uint32 CtlEnRfDivSpi: 1;        /*## attribute CtlEnRfDivSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 19;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_DivideForceRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_LOOP_DYNAMIC_REG_0Bits_t
* RegisterName: loop_dynamic_reg_0
* 
* AddressRange: 0xREADWRITE - 0x04C
* ResetValue: 0x00000050
*/
typedef struct  {
   /**
	* BitsName: ctl_en_cp_slice_up
	* Description: Charge pump registor up while toggling
	* (*not i/o*)
	*/
    uint32 CtlEnCpSliceUp: 8;        /*## attribute CtlEnCpSliceUp */
   /**
	* BitsName: ctl_set_lpf_R1_up
	* Description: Resitor R1 value up while toggling 
	* (*not i/o*)
	*/
    uint32 CtlSetLpfR1Up: 5;        /*## attribute CtlSetLpfR1Up */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_set_lpf_R2_up
	* Description: Resitor R2 value up while toggling 
	* (*not i/o*)
	*/
    uint32 CtlSetLpfR2Up: 5;        /*## attribute CtlSetLpfR2Up */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_set_lpf_en_toggling
	* Description: Enable filter R1/R2/Icp  toggling
	* (*not i/o*)  
	* 1 :  Enable toggling
	* 0 :  Disable toggling
	*/
    uint32 CtlSetLpfEnToggling: 1;        /*## attribute CtlSetLpfEnToggling */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 7;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_LoopDynamicReg0Bits_t;
    /**
* Nxp_Tef810x_Mod06_LPF_VTUNE_VCO_STATUSBits_t
* RegisterName: lpf_vtune_vco_status
* 
* AddressRange: 0xREAD - 0x050
* ResetValue: 0x00000054
*/
typedef struct  {
   /**
	* BitsName: lpf_vtune_vco_low
	* Description: vtune_low raw status before the functional safety monitor latch i.e vtune voltage is lesser than the programmed value ctl_vtune_vco_low_spi
	* 1: Low
	* 0: ignore
	*/
    uint32 LpfVtuneVcoLow: 1;        /*## attribute LpfVtuneVcoLow */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: lpf_vtune_vco_high
	* Description: vtune_high raw status before the functional safety monitor latch i.e vtune voltage is greater than the programmed value ctl_vtune_vco_high_spi
	* 1: High
	* 0: ignore
	*/
    uint32 LpfVtuneVcoHigh: 1;        /*## attribute LpfVtuneVcoHigh */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 27;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod06_LpfVtuneVcoStatusBits_t;
    /**
* Nxp_Tef810x_Mod06_FUNCSAFE_MON_VTUNE_VCOBits_t
* RegisterName: funcsafe_mon_vtune_vco
* 
* AddressRange: 0xREADWRITE - 0x054
* ResetValue: 0x00000058
*/
typedef struct  {
   /**
	* BitsName: ctl_vtune_vco_low_spi
	* Description: tuning voltage monitor low threshold: V_thresh =  V_thresh = 50mV + ctl_vtune_vco_low * 12.5mV
	*/
    uint32 CtlVtuneVcoLowSpi: 4;        /*## attribute CtlVtuneVcoLowSpi */
   /**
	* BitsName: ctl_vtune_vco_high_spi
	* Description: tuning voltage monitor high threshold: V_thresh = 850mV + ctl_vtune_vco_high * 12.5mV
	*/
    uint32 CtlVtuneVcoHighSpi: 4;        /*## attribute CtlVtuneVcoHighSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FUNCSAFE_MON_UNLOCK_VCOBits_t
* RegisterName: funcsafe_mon_unlock_vco
* 
* AddressRange: 0xREADWRITE - 0x058
* ResetValue: 0x0000005C
*/
typedef struct  {
   /**
	* BitsName: ctl_ld_window_delta_spi
	* Description: Window size
	*/
    uint32 CtlLdWindowDeltaSpi: 6;        /*## attribute CtlLdWindowDeltaSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ld_window_offset_spi
	* Description: Lock detector window offset
	*/
    uint32 CtlLdWindowOffsetSpi: 6;        /*## attribute CtlLdWindowOffsetSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ld_pol_spi
	* Description: Lock detector polarity
	* 1: Negative polarity
	* 0: Positive polarity
	*/
    uint32 CtlLdPolSpi: 1;        /*## attribute CtlLdPolSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_ld_en_spi
	* Description: Enable Lock detector. This bit cannot be used as the analog doesn't implement this.
	* 1: Enable lock detector
	* 0: Disable lock detector
	*/
    uint32 CtlLdEnSpi: 1;        /*## attribute CtlLdEnSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 11;        /*## attribute Reserved3 */
}Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FUNCSAFE_MON_LEVEL_VCOBits_t
* RegisterName: funcsafe_mon_level_vco
* 
* AddressRange: 0xREADWRITE - 0x05C
* ResetValue: 0x00000060
*/
typedef struct  {
   /**
	* BitsName: ctl_level_vco_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage): V_thresh = 117mV + ctl_level_vco_min* 19.5mV
	*/
    uint32 CtlLevelVcoMinSpi: 4;        /*## attribute CtlLevelVcoMinSpi */
   /**
	* BitsName: ctl_level_vco_low_spi
	* Description: Low trigger level for Gain Control: V_thresh = 117mV + ctl_level_vco_low * 19.5mV
	*/
    uint32 CtlLevelVcoLowSpi: 4;        /*## attribute CtlLevelVcoLowSpi */
   /**
	* BitsName: ctl_level_vco_high_spi
	* Description: High trigger level for Gain Control: V_thresh = 527mV + ctl_level_vco_high * 19.5mV
	*/
    uint32 CtlLevelVcoHighSpi: 4;        /*## attribute CtlLevelVcoHighSpi */
   /**
	* BitsName: ctl_level_vco_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage): V_thresh = 527mV + ctl_level_vco_max * 19.5mV
	*/
    uint32 CtlLevelVcoMaxSpi: 4;        /*## attribute CtlLevelVcoMaxSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_level_vco_amp_monitor_en_spi
	* Description: Enable the amplitude monitor
	* 1: Enable amplitude monitor
	* 0: Disable amplitude monitor
	*/
    uint32 CtlLevelVcoAmpMonitorEnSpi: 1;        /*## attribute CtlLevelVcoAmpMonitorEnSpi */
}Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FUNCSAFE_MON_TEMPERATURE_VCOBits_t
* RegisterName: funcsafe_mon_temperature_vco
* 
* AddressRange: 0xREADWRITE - 0x060
* ResetValue: 0x00000064
*/
typedef struct  {
   /**
	* BitsName: ctl_temp_sensor_max_temp_threshold_sel_spi
	* Description: Set the maximun temperature threshold values
	*/
    uint32 CtlTempSensorMaxTempThresholdSelSpi: 6;        /*## attribute CtlTempSensorMaxTempThresholdSelSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_temp_sensor_buf_gain_spi
	* Description: Gain of the buffer of the temperature sensor
	*/
    uint32 CtlTempSensorBufGainSpi: 1;        /*## attribute CtlTempSensorBufGainSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_temp_sensor_chopper_spi
	* Description: Temperature sensor Chopeper  polarity
	*/
    uint32 CtlTempSensorChopperSpi: 1;        /*## attribute CtlTempSensorChopperSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 19;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_CONTROL_SPAREBits_t
* RegisterName: control_spare
* 
* AddressRange: 0xREADWRITE - 0x06C
* ResetValue: 0x00000070
*/
typedef struct  {
   /**
	* BitsName: ctl_ibias_TS_100u_en_ls
	* Description: Bias enable for the temperature sensor 
	* 1: Enable bias of temp sensor
	* 0: Disable bias of temp sensor
	*/
    uint32 CtlIbiasTs100UEnLs: 1;        /*## attribute CtlIbiasTs100UEnLs */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ld_polarity_from_sweep_control
	* Description: This bit controls the polarity of the lock detector based on the sweep control settings automatically.
	* 1: Sweep control module drives the polarity bit of the lock detector based on the chirp profile (active up/downchirp) 
	* 0 (Reset Value):  The polarity of the lock detector is controlled by the bit in the ctl_ld_pol_spi bit in the register funcsafe_mon_unlock_vco
	* 
	* Note: If this bit is set to '1', ctl_ld_pol_spi bit in the register funcsafe_mon_unlock_vco should be set to '0' to override the software based polarity setting
	*/
    uint32 LdPolarityFromSweepControl: 1;        /*## attribute LdPolarityFromSweepControl */
   /**
	* BitsName: disable_hard_func_reset
	* Description: This bit controls the selection of the hardware functional reset based on the chirp fast switch. 
	* 0: Enable hardware functional reset at every chirp start or every sequence start and release after the fast_switch timer expires (chirp_dynamic_power_control reg in timing engine).  
	* - In normal mode/Powerdown per sequence mode, this functional reset is asserted at the start of every sequence.
	* - In Powerdown per chirp mode, this functional reset is asserted at the start of every chirp.
	* 1: Disable  hardware functional reset. No hardware functional reset will be issued.
	*/
    uint32 DisableHardFuncReset: 1;        /*## attribute DisableHardFuncReset */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 24;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_ControlSpareBits_t;
    /**
* Nxp_Tef810x_Mod06_CAL_LO_DETBits_t
* RegisterName: cal_lo_det
* 
* AddressRange: 0xREADWRITE - 0x070
* ResetValue: 0x00000074
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 6;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_rms_meas_in_out_spi
	* Description: Select input or output of power detector. 
	* 0=input
	* 1=output.
	*/
    uint32 CtlRmsMeasInOutSpi: 1;        /*## attribute CtlRmsMeasInOutSpi */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_rms_en_spi
	* Description: Enable the rms detector
	* 1: Enable rms detector
	* 0: Disable rms detector
	*/
    uint32 CtlRmsEnSpi: 1;        /*## attribute CtlRmsEnSpi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 1;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 7;        /*## attribute Reserved9 */
}Nxp_Tef810x_Mod06_CalLoDetBits_t;
    /**
* Nxp_Tef810x_Mod06_REF_CNTR_INITBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0xREADWRITE - 0x07C
* ResetValue: 0x00000080
*/
typedef struct  {
   /**
	* BitsName: ref_count_value
	* Description: value for the reference count time (40 MHz= 25 ns base time) default is d'40. This is used as reference count in both spi triggered mode and window_active triggered mode
	*/
    uint32 RefCountValue: 16;        /*## attribute RefCountValue */
   /**
	* BitsName: ideal_480_count_value
	* Description: This is applicable when the freq counter trigger is based on window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
}Nxp_Tef810x_Mod06_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod06_FREQ_COUNTER_STARTBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0xREADWRITE - 0x080
* ResetValue: 0x00000084
*/
typedef struct  {
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle
	* 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: num_lsbbits_ignored
	* Description: Number of lsb bits to be ignored while comparing the final freq counter read value. This is required incase of frequency counter trigger is based on window_active  for functional safety. The hardware then compares the value measured by frequency counter against ideal_480_count_value ignoring the lsb bits. 
	* 0001: Zeroth bit is ignored from comparison
	* 0011: Zeroth & first bits are ignored from comparison
	* 0111: Zeroth & first & second bits are ignored from comparison
	* 1111: Zeroth & first & second & third bits are ignored from comparison
	*/
    uint32 NumLsbbitsIgnored: 4;        /*## attribute NumLsbbitsIgnored */
   /**
	* BitsName: enable_func_safety_freq_mea
	* Description: By default, the frequency counter is triggered based on safety_monitor_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	* 1: trigger is based on safety_monitor_active
	* 0: Trigger is based on the spi write on bit 0 i.e freq_start
	*/
    uint32 EnableFuncSafetyFreqMea: 1;        /*## attribute EnableFuncSafetyFreqMea */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 23;        /*## attribute Reserved1 */
}Nxp_Tef810x_Mod06_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod06_FREQ_COUNTER_READ_VALUEBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0xREAD - 0x084
* ResetValue: 0x00000088
*/
typedef struct  {
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq value = freq count value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq value = freq count value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 10;        /*## attribute Reserved1 */
   /**
	* BitsName: xor_parity_freq_counter
	* Description: This is simple xor of all the bits in the frequency counter read value. This bit can be used by MCU to check against stuckat fault error
	* 1: Odd parity (Number of ones in the register value is odd)
	* 0: Even parity (Number of ones in the register value is even)
	*/
    uint32 XorParityFreqCounter: 1;        /*## attribute XorParityFreqCounter */
}Nxp_Tef810x_Mod06_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_REF_COUNTER_READ_VALUEBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0xREAD - 0x088
* ResetValue: 0x0000008C
*/
typedef struct  {
   /**
	* BitsName: counter_read_value
	* Description: Reference count value
	*/
    uint32 CounterReadValue: 16;        /*## attribute CounterReadValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod06_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_ATBBits_t
* RegisterName: atb
* 
* AddressRange: 0xREADWRITE - 0x098
* ResetValue: 0x0000009C
*/
typedef struct  {
   /**
	* BitsName: atb_set
	* Description: 8'h01 :  level_vco_min (Functional Safety VCO amplitude monitor min threshold)
	* 8'h02:   level_vco_low (Functional Safety VCO amplitude monitor low threshold)
	* 8'h03:   level_vco_high(Functional Safety VCO amplitude monitor high threshold) 
	* 8'h04:   level_vco_max(Functional Safety VCO amplitude monitor max threshold)
	* 8'h05:   rms_det_ref(RMS detector reference voltage)
	* 8'h06:   rms_det (RMS detector output voltage)
	* 8'h07:   temp_sns_buffer(Temperature sensor buffer output)
	* 8'h08:   temp_sns_comp(Functional Safety Temperature Monitor comparator input (unbuffered temperature sensor output))
	* 8'h09:   vco_ibias (Reference currents for ? enabled by ?ctl_vco_pbusp_i100u_test_en?)
	* 8'h0A:   vco_ind_cnt_tap (VCO center voltage)
	* 8'h0B:   vtune_level_high (Functional Safety VCO tuning voltage monitor high threshold can be tuned by ?ctl_vtune_vco_high_spi?)
	* 8'h0C:   vtune_level_low (Functional Safety VCO tuning voltage monitorlow threshold. can be tuned by ?ctl_vtune_vco_low_spi?)
	* 8'h0D:   ldo_divider_vdd (Analog divider 1.1V supply: Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_divider_sel_vout_spi?)
	* 8'h0E:   ldo_cppfd_vdd (Analog Charge Pump/Phase Detector 1.1V supply:Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_cppfd_sel_vout_spi?)
	* 8'h0F:   ldo_vco_vdd (Analog VCO 1.1V supply: Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_vco_sel_vout_spi?)
	* 8'h10:   vdd_pll_1v8 (PLL analog 1.8V supply; Locally divided 1/6 (? 300mV typ))
	* 8'h11:   vdd_vco_1v8 (VCO analog 1.8V supply; Loacally divided 1/6 (? 300mV typ))
	* 8'h12:   ibias_cp_150u (Charge Pump current;: 150uA (typ); locally I/V converted trim-able resistor (4k); )
	* 8'h13:   ibias_ref_100u (BG Reference current;:100uA (typ); locally I/V converted trim-able resistor (4k); )
	* 8'h14:   vdd_pll_1v1 (Analog PLL 1.1V supply: Locally divided 3/11 (? 300mV typ))
	*/
    uint32 AtbSet: 8;        /*## attribute AtbSet */
   /**
	* BitsName: atb_en
	* Description: Enable DC Test Bus
	* 1: Enable testbus
	* 0: Disable testbus
	*/
    uint32 AtbEn: 1;        /*## attribute AtbEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod06_AtbBits_t;
    /**
* Nxp_Tef810x_Mod06_TEST_ERROR_FLAG_STATUSBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0xREAD - 0x0A8
* ResetValue: 0x000000AC
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 4;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 1;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 3;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 1;        /*## attribute Reserved9 */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 3;        /*## attribute Reserved10 */
   /**
	* BitsName: Reserved_11
	* Description: nan
	*/
    uint32 Reserved11: 1;        /*## attribute Reserved11 */
   /**
	* BitsName: Reserved_12
	* Description: nan
	*/
    uint32 Reserved12: 3;        /*## attribute Reserved12 */
   /**
	* BitsName: Reserved_13
	* Description: nan
	*/
    uint32 Reserved13: 1;        /*## attribute Reserved13 */
   /**
	* BitsName: Reserved_14
	* Description: nan
	*/
    uint32 Reserved14: 1;        /*## attribute Reserved14 */
   /**
	* BitsName: divide_freq_error_flag
	* Description: sweep control divide freq error flag
	* 1:  divide freq error is set
	* 0:  divide freq error is not set
	*/
    uint32 DivideFreqErrorFlag: 1;        /*## attribute DivideFreqErrorFlag */
   /**
	* BitsName: vco_freq_480_error_flag
	* Description: vco 480 freq error flag
	* 1:  freq error is set 
	* 0:  freq error is not set
	*/
    uint32 VcoFreq480ErrorFlag: 1;        /*## attribute VcoFreq480ErrorFlag */
}Nxp_Tef810x_Mod06_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod06_DIVIDE_FREQ_COUNTER_STARTBits_t
* RegisterName: divide_freq_counter_start
* 
* AddressRange: 0xREADWRITE - 0x0BC
* ResetValue: 0x000000C0
*/
typedef struct  {
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle, 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: enable_func_safety_freq_mea
	* Description: By default, the frequency counter is triggered based on safety_monitor_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	* 1: Trigger based on the safety_monitor_active signal
	* 0: Trigger based on the spi write of bit 0 of this reqister i.e freq_start
	*/
    uint32 EnableFuncSafetyFreqMea: 1;        /*## attribute EnableFuncSafetyFreqMea */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 23;        /*## attribute Reserved2 */
}Nxp_Tef810x_Mod06_DivideFreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod06_DIVIDE_FREQ_COUNTER_READ_VALUEBits_t
* RegisterName: divide_freq_counter_read_value
* 
* AddressRange: 0xREAD - 0x0C0
* ResetValue: 0x000000C4
*/
typedef struct  {
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq count value = reported value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq count value = (reported value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
	* 1: counting done
	* 0: couting not done yet
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 10;        /*## attribute Reserved1 */
   /**
	* BitsName: xor_parity_divide_freq_counter
	* Description: This is simple xor of all the bits in the frequency counter read value. This bit can be used by MCU to check against stuckat fault error
	* 1: Odd parity (Number of ones in the register value is odd)
	* 0: Even parity (Number of ones in the register value is even)
	*/
    uint32 XorParityDivideFreqCounter: 1;        /*## attribute XorParityDivideFreqCounter */
}Nxp_Tef810x_Mod06_DivideFreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_MODULEIDBits_t
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
	* Description: Minor revision numer i.e. with no software consequences
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
}Nxp_Tef810x_Mod06_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod06_FilterRegisterProfileBits_t
* RegisterName: filter_register_profile
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x60070017
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ibias_cp_150u_spi_profile0
	* Description: Program current of the CP (latest versions is closer to 100uA)
	*/
    uint32 CtlIbiasCp150USpiProfile0: 6;        /*## attribute CtlIbiasCp150USpiProfile0 */
   /**
	* BitsName: ctl_cp_slice_en_spi_profile0
	* Description: Enable cp slices (enable two slices 300uA). Every bit corresponds to one slice.
	*/
    uint32 CtlCpSliceEnSpiProfile0: 8;        /*## attribute CtlCpSliceEnSpiProfile0 */
   /**
	* BitsName: ctl_lpf_int_en_spi_profile0
	* Description: Enable internal loop filter
	* 1 :  Enable loop filter
	* 0 :  Disable loop filter
	*/
    uint32 CtlLpfIntEnSpiProfile0: 1;        /*## attribute CtlLpfIntEnSpiProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_lpf_ext_en_spi_profile0
	* Description: Enable external VCO tune voltage.
	* 1 :  Enable external vco tune voltage
	* 0 :  Disable external vco tune voltage
	*/
    uint32 CtlLpfExtEnSpiProfile0: 1;        /*## attribute CtlLpfExtEnSpiProfile0 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_lpf_force_vtune_en_spi_profile0
	* Description: Enable the force vtune circuit
	* 1 :  Enable force vtune circuit
	* 0 :  Disable  force vtune circuit
	*/
    uint32 CtlLpfForceVtuneEnSpiProfile0: 1;        /*## attribute CtlLpfForceVtuneEnSpiProfile0 */
   /**
	* BitsName: ctl_cp_ioffset_updn_spi_profile0
	* Description: Direction of the charge pump offset
	* 1 :  Pmos inject current 
	* 0 :  Nmos substract current
	*/
    uint32 CtlCpIoffsetUpdnSpiProfile0: 1;        /*## attribute CtlCpIoffsetUpdnSpiProfile0 */
   /**
	* BitsName: ctl_lpf_prog_force_voltage_spi_profile0
	* Description: Program the force vtune voltage
	*/
    uint32 CtlLpfProgForceVoltageSpiProfile0: 7;        /*## attribute CtlLpfProgForceVoltageSpiProfile0 */
}Nxp_Tef810x_Mod06_FilterRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_FilterParRegisterProfileBits_t
* RegisterName: filter_par_register_profile
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x52921616
*/
typedef struct  {
   /**
	* BitsName: ctl_lpf_vtune_monitor_en_spi_profile0
	* Description: Enable the vtune monitor
	* 1 :  Enable vtune monitor
	* 0 :  Disable  vtune monitor
	*/
    uint32 CtlLpfVtuneMonitorEnSpiProfile0: 1;        /*## attribute CtlLpfVtuneMonitorEnSpiProfile0 */
   /**
	* BitsName: ctl_lpf_C3_spi_profile0
	* Description: Select loop filter cap. C3
	*/
    uint32 CtlLpfC3SpiProfile0: 5;        /*## attribute CtlLpfC3SpiProfile0 */
   /**
	* BitsName: ctl_lpf_C2_spi_profile0
	* Description: Select loop filter cap. C2
	*/
    uint32 CtlLpfC2SpiProfile0: 5;        /*## attribute CtlLpfC2SpiProfile0 */
   /**
	* BitsName: ctl_lpf_C1_spi_profile0
	* Description: Select loop filter cap. C1
	*/
    uint32 CtlLpfC1SpiProfile0: 5;        /*## attribute CtlLpfC1SpiProfile0 */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_lpf_R2_spi_profile0
	* Description: Select loop filter res.R2
	*/
    uint32 CtlLpfR2SpiProfile0: 5;        /*## attribute CtlLpfR2SpiProfile0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_lpf_R1_spi_profile0
	* Description: Select loop filter res. R1
	*/
    uint32 CtlLpfR1SpiProfile0: 5;        /*## attribute CtlLpfR1SpiProfile0 */
}Nxp_Tef810x_Mod06_FilterParRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_VcoRegisterProfileBits_t
* RegisterName: vco_register_profile
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x000F0F00
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
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_vco_en_spi_profile0
	* Description: Enable VCO 
	* 1 :  Enable VCO
	* 0 :  Disable VCO
	*/
    uint32 CtlVcoEnSpiProfile0: 1;        /*## attribute CtlVcoEnSpiProfile0 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_vco_bandwidth_spi_profile0
	* Description: Select VCO bandwidth:
	* 0: narrow bandwidth 
	* 1: large bandwidth
	*/
    uint32 CtlVcoBandwidthSpiProfile0: 1;        /*## attribute CtlVcoBandwidthSpiProfile0 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_vco_r_ibias_set_spi_profile0
	* Description: Select resistor used for VCO current generation
	*/
    uint32 CtlVcoRIbiasSetSpiProfile0: 5;        /*## attribute CtlVcoRIbiasSetSpiProfile0 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_vco_ivco_fine_spi_profile0
	* Description: Select current VCO
	*/
    uint32 CtlVcoIvcoFineSpiProfile0: 5;        /*## attribute CtlVcoIvcoFineSpiProfile0 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: ctl_vco_coarse_tuning_spi_profile0
	* Description: Select Sub-band VCO
	*/
    uint32 CtlVcoCoarseTuningSpiProfile0: 7;        /*## attribute CtlVcoCoarseTuningSpiProfile0 */
}Nxp_Tef810x_Mod06_VcoRegisterProfileBits_t;
    /**
* Nxp_Tef810x_Mod06_CpRegisterBits_t
* RegisterName: cp_register
* 
* AddressRange: 0x030 - 0x034
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_cp_replica_bias_en_spi
	* Description: Enable charge pump replica bias circuit (improve linearity)
	* 1 :  Enable CP replica bias
	* 0 :  Disable CP replica bias
	*/
    uint32 CtlCpReplicaBiasEnSpi: 1;        /*## attribute CtlCpReplicaBiasEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_cp_en_spi
	* Description: Enable charge pump 
	* 1 :  Enable CP 
	* 0 :  Disable CP
	*/
    uint32 CtlCpEnSpi: 1;        /*## attribute CtlCpEnSpi */
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
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_cp_force_dn_spi
	* Description: Force the Charge Pump down
	* 1 : Decrease CP current
	* 0 :  No action
	*/
    uint32 CtlCpForceDnSpi: 1;        /*## attribute CtlCpForceDnSpi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_cp_force_up_spi
	* Description: Force the Charge Pump up 
	* 1 :  Increase CP current
	* 0 :  No action
	*/
    uint32 CtlCpForceUpSpi: 1;        /*## attribute CtlCpForceUpSpi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 1;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 8;        /*## attribute Reserved8 */
}Nxp_Tef810x_Mod06_CpRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_VcoBufferLdoRegisterBits_t
* RegisterName: vco_buffer_ldo_register
* 
* AddressRange: 0x034 - 0x038
* ResetValue: 0x0000000F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_vco_en_spi
	* Description: Enable VCO LDO
	* 1 :  Enable LDO
	* 0 :  Disable LDO
	*/
    uint32 CtlLdoVcoEnSpi: 1;        /*## attribute CtlLdoVcoEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ldo_vco_sel_vout_spi
	* Description: Select vout of VCO LDO
	*/
    uint32 CtlLdoVcoSelVoutSpi: 5;        /*## attribute CtlLdoVcoSelVoutSpi */
}Nxp_Tef810x_Mod06_VcoBufferLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_CppfdLdoRegisterBits_t
* RegisterName: cppfd_ldo_register
* 
* AddressRange: 0x038 - 0x03C
* ResetValue: 0x0000000F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_cppfd_en_spi
	* Description: Enable PFDCP LDO
	* 1 :  Enable LDO
	* 0 :  Disable LDO
	*/
    uint32 CtlLdoCppfdEnSpi: 1;        /*## attribute CtlLdoCppfdEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ldo_cppfd_sel_vout_spi
	* Description: Select vout PFDCP LDO
	*/
    uint32 CtlLdoCppfdSelVoutSpi: 5;        /*## attribute CtlLdoCppfdSelVoutSpi */
}Nxp_Tef810x_Mod06_CppfdLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_DividerLdoRegisterBits_t
* RegisterName: divider_ldo_register
* 
* AddressRange: 0x03C - 0x040
* ResetValue: 0x0000000F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ldo_divider_en_spi
	* Description: Enable Divider LDO
	* 1 :  Enable Divider LDO
	* 0 :  Disable Divider LDO
	*/
    uint32 CtlLdoDividerEnSpi: 1;        /*## attribute CtlLdoDividerEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ldo_divider_sel_vout_spi
	* Description: Select vout  Divider LDO
	*/
    uint32 CtlLdoDividerSelVoutSpi: 5;        /*## attribute CtlLdoDividerSelVoutSpi */
}Nxp_Tef810x_Mod06_DividerLdoRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_BiasBlockRegisterBits_t
* RegisterName: bias_block_register
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: ctl_ibias_en_spi
	* Description: Enable all the biasing block
	* 1 :  Enable Bias
	* 0 :  Disable Bias
	*/
    uint32 CtlIbiasEnSpi: 1;        /*## attribute CtlIbiasEnSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ibias_TVN_20u_en_spi
	* Description: Enable current of the Tuning Voltage Monitor
	* 1 :  Enable tune current
	* 0 :  Disable tune current
	*/
    uint32 CtlIbiasTvn20UEnSpi: 1;        /*## attribute CtlIbiasTvn20UEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ibias_VAM_100u_en_spi
	* Description: Enable current of the VCO amplitude monitor
	* 1 :  Enable vco amplitude monitor
	* 0 :  Disable vco amplitude monitor
	*/
    uint32 CtlIbiasVam100UEnSpi: 1;        /*## attribute CtlIbiasVam100UEnSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_ibias_LD_10u_en_spi
	* Description: Enable current of the Lock detector
	* 1 :  Enable lock detector
	* 0 :  Disable lock detector
	*/
    uint32 CtlIbiasLd10UEnSpi: 1;        /*## attribute CtlIbiasLd10UEnSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 6;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_ibias_cp_opamp_100u_en_spi
	* Description: Enable current of the CP opamp
	* 1 :  Enable current
	* 0 :  Disable current
	*/
    uint32 CtlIbiasCpOpamp100UEnSpi: 1;        /*## attribute CtlIbiasCpOpamp100UEnSpi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: ctl_ibias_bist_dac_200u_en_spi
	* Description: Enable current rms detector (name is missleading)
	* 1 :  Enable rms detector
	* 0 :  Disable rms detector
	*/
    uint32 CtlIbiasBistDac200UEnSpi: 1;        /*## attribute CtlIbiasBistDac200UEnSpi */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 3;        /*## attribute Reserved7 */
   /**
	* BitsName: ctl_ibias_div_350u_en_spi
	* Description: Enable current of the dividers
	* 1 :  Enable divider current
	* 0 :  Disable  divider current
	*/
    uint32 CtlIbiasDiv350UEnSpi: 1;        /*## attribute CtlIbiasDiv350UEnSpi */
}Nxp_Tef810x_Mod06_BiasBlockRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_BufferRegisterBits_t
* RegisterName: buffer_register
* 
* AddressRange: 0x044 - 0x048
* ResetValue: 0x00000110
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_buffer_480meg_en_spi
	* Description: Enable 480MHz buffer
	* 1 :  Enable 480MHz buffer
	* 0 :  Disable 480MHz buffer
	*/
    uint32 CtlBuffer480MegEnSpi: 1;        /*## attribute CtlBuffer480MegEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_buffer_480meg_bal_spi
	* Description: Select balanced or unbalanced signal 480MHz buffer (used for debugging)
	* 1 :  balanced (reset value for costumers)
	* 0 :  unbalanced
	*/
    uint32 CtlBuffer480MegBalSpi: 1;        /*## attribute CtlBuffer480MegBalSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_buffer_480meg_pol_spi
	* Description: Select signal polarity 480MHz buffer (in case it is balanced 0 degrees or 180 degrees) 
	* 1 :  180 degree
	* 0 :  0 degree (reset value for costumers)
	*/
    uint32 CtlBuffer480MegPolSpi: 1;        /*## attribute CtlBuffer480MegPolSpi */
}Nxp_Tef810x_Mod06_BufferRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_DivideForceRegisterBits_t
* RegisterName: divide_force_register
* 
* AddressRange: 0x048 - 0x04C
* ResetValue: 0x0000011B
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_en_rf_div_spi
	* Description: Enable Divider (not used, disabled from the LDO)
	* 1 :  Enable divider
	* 0 :  Disable divider
	*/
    uint32 CtlEnRfDivSpi: 1;        /*## attribute CtlEnRfDivSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_force_divider
	* Description: enables forcing a PLL loop back divider. If set, divider is programmed to the setting of 'ctl_div_force' (see below)
	* 1 :  Enable pll loop back divider
	* 0 :  Disable pll loop back divider
	*/
    uint32 CtlForceDivider: 1;        /*## attribute CtlForceDivider */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_div_force
	* Description: defines the PLL loop back divider (26-28[dec] are allowed settings). Requires 'ctl_force_divider' to be set (otherwise the divider is under control of sweep engine)
	*/
    uint32 CtlDivForce: 6;        /*## attribute CtlDivForce */
}Nxp_Tef810x_Mod06_DivideForceRegisterBits_t;
    /**
* Nxp_Tef810x_Mod06_LoopDynamicReg0Bits_t
* RegisterName: loop_dynamic_reg_0
* 
* AddressRange: 0x04C - 0x050
* ResetValue: 0x0015150F
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_set_lpf_en_toggling
	* Description: Enable filter R1/R2/Icp  toggling
	* (*not i/o*)  
	* 1 :  Enable toggling
	* 0 :  Disable toggling
	*/
    uint32 CtlSetLpfEnToggling: 1;        /*## attribute CtlSetLpfEnToggling */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_set_lpf_R2_up
	* Description: Resitor R2 value up while toggling 
	* (*not i/o*)
	*/
    uint32 CtlSetLpfR2Up: 5;        /*## attribute CtlSetLpfR2Up */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_set_lpf_R1_up
	* Description: Resitor R1 value up while toggling 
	* (*not i/o*)
	*/
    uint32 CtlSetLpfR1Up: 5;        /*## attribute CtlSetLpfR1Up */
   /**
	* BitsName: ctl_en_cp_slice_up
	* Description: Charge pump registor up while toggling
	* (*not i/o*)
	*/
    uint32 CtlEnCpSliceUp: 8;        /*## attribute CtlEnCpSliceUp */
}Nxp_Tef810x_Mod06_LoopDynamicReg0Bits_t;
    /**
* Nxp_Tef810x_Mod06_LpfVtuneVcoStatusBits_t
* RegisterName: lpf_vtune_vco_status
* 
* AddressRange: 0x050 - 0x054
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 27;        /*## attribute Reserved0 */
   /**
	* BitsName: lpf_vtune_vco_high
	* Description: vtune_high raw status before the functional safety monitor latch i.e vtune voltage is greater than the programmed value ctl_vtune_vco_high_spi
	* 1: High
	* 0: ignore
	*/
    uint32 LpfVtuneVcoHigh: 1;        /*## attribute LpfVtuneVcoHigh */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: lpf_vtune_vco_low
	* Description: vtune_low raw status before the functional safety monitor latch i.e vtune voltage is lesser than the programmed value ctl_vtune_vco_low_spi
	* 1: Low
	* 0: ignore
	*/
    uint32 LpfVtuneVcoLow: 1;        /*## attribute LpfVtuneVcoLow */
}Nxp_Tef810x_Mod06_LpfVtuneVcoStatusBits_t;
    /**
* Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoBits_t
* RegisterName: funcsafe_mon_vtune_vco
* 
* AddressRange: 0x054 - 0x058
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_vtune_vco_high_spi
	* Description: tuning voltage monitor high threshold: V_thresh = 850mV + ctl_vtune_vco_high * 12.5mV
	*/
    uint32 CtlVtuneVcoHighSpi: 4;        /*## attribute CtlVtuneVcoHighSpi */
   /**
	* BitsName: ctl_vtune_vco_low_spi
	* Description: tuning voltage monitor low threshold: V_thresh =  V_thresh = 50mV + ctl_vtune_vco_low * 12.5mV
	*/
    uint32 CtlVtuneVcoLowSpi: 4;        /*## attribute CtlVtuneVcoLowSpi */
}Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoBits_t
* RegisterName: funcsafe_mon_unlock_vco
* 
* AddressRange: 0x058 - 0x05C
* ResetValue: 0x00100020
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 11;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_ld_en_spi
	* Description: Enable Lock detector. This bit cannot be used as the analog doesn't implement this.
	* 1: Enable lock detector
	* 0: Disable lock detector
	*/
    uint32 CtlLdEnSpi: 1;        /*## attribute CtlLdEnSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_ld_pol_spi
	* Description: Lock detector polarity
	* 1: Negative polarity
	* 0: Positive polarity
	*/
    uint32 CtlLdPolSpi: 1;        /*## attribute CtlLdPolSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_ld_window_offset_spi
	* Description: Lock detector window offset
	*/
    uint32 CtlLdWindowOffsetSpi: 6;        /*## attribute CtlLdWindowOffsetSpi */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 2;        /*## attribute Reserved3 */
   /**
	* BitsName: ctl_ld_window_delta_spi
	* Description: Window size
	*/
    uint32 CtlLdWindowDeltaSpi: 6;        /*## attribute CtlLdWindowDeltaSpi */
}Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoBits_t
* RegisterName: funcsafe_mon_level_vco
* 
* AddressRange: 0x05C - 0x060
* ResetValue: 0x00007777
*/
typedef struct  {
   /**
	* BitsName: ctl_level_vco_amp_monitor_en_spi
	* Description: Enable the amplitude monitor
	* 1: Enable amplitude monitor
	* 0: Disable amplitude monitor
	*/
    uint32 CtlLevelVcoAmpMonitorEnSpi: 1;        /*## attribute CtlLevelVcoAmpMonitorEnSpi */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_level_vco_max_spi
	* Description: High trigger level for Reliability (the most high threshold voltage): V_thresh = 527mV + ctl_level_vco_max * 19.5mV
	*/
    uint32 CtlLevelVcoMaxSpi: 4;        /*## attribute CtlLevelVcoMaxSpi */
   /**
	* BitsName: ctl_level_vco_high_spi
	* Description: High trigger level for Gain Control: V_thresh = 527mV + ctl_level_vco_high * 19.5mV
	*/
    uint32 CtlLevelVcoHighSpi: 4;        /*## attribute CtlLevelVcoHighSpi */
   /**
	* BitsName: ctl_level_vco_low_spi
	* Description: Low trigger level for Gain Control: V_thresh = 117mV + ctl_level_vco_low * 19.5mV
	*/
    uint32 CtlLevelVcoLowSpi: 4;        /*## attribute CtlLevelVcoLowSpi */
   /**
	* BitsName: ctl_level_vco_min_spi
	* Description: Low trigger level for FSM (the most low threshold voltage): V_thresh = 117mV + ctl_level_vco_min* 19.5mV
	*/
    uint32 CtlLevelVcoMinSpi: 4;        /*## attribute CtlLevelVcoMinSpi */
}Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoBits_t
* RegisterName: funcsafe_mon_temperature_vco
* 
* AddressRange: 0x060 - 0x064
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 19;        /*## attribute Reserved0 */
   /**
	* BitsName: ctl_temp_sensor_chopper_spi
	* Description: Temperature sensor Chopeper  polarity
	*/
    uint32 CtlTempSensorChopperSpi: 1;        /*## attribute CtlTempSensorChopperSpi */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: ctl_temp_sensor_buf_gain_spi
	* Description: Gain of the buffer of the temperature sensor
	*/
    uint32 CtlTempSensorBufGainSpi: 1;        /*## attribute CtlTempSensorBufGainSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 2;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_temp_sensor_max_temp_threshold_sel_spi
	* Description: Set the maximun temperature threshold values
	*/
    uint32 CtlTempSensorMaxTempThresholdSelSpi: 6;        /*## attribute CtlTempSensorMaxTempThresholdSelSpi */
}Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoBits_t;
    /**
* Nxp_Tef810x_Mod06_ControlSpareBits_t
* RegisterName: control_spare
* 
* AddressRange: 0x06C - 0x070
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 24;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: disable_hard_func_reset
	* Description: This bit controls the selection of the hardware functional reset based on the chirp fast switch. 
	* 0: Enable hardware functional reset at every chirp start or every sequence start and release after the fast_switch timer expires (chirp_dynamic_power_control reg in timing engine).  
	* - In normal mode/Powerdown per sequence mode, this functional reset is asserted at the start of every sequence.
	* - In Powerdown per chirp mode, this functional reset is asserted at the start of every chirp.
	* 1: Disable  hardware functional reset. No hardware functional reset will be issued.
	*/
    uint32 DisableHardFuncReset: 1;        /*## attribute DisableHardFuncReset */
   /**
	* BitsName: ld_polarity_from_sweep_control
	* Description: This bit controls the polarity of the lock detector based on the sweep control settings automatically.
	* 1: Sweep control module drives the polarity bit of the lock detector based on the chirp profile (active up/downchirp) 
	* 0 (Reset Value):  The polarity of the lock detector is controlled by the bit in the ctl_ld_pol_spi bit in the register funcsafe_mon_unlock_vco
	* 
	* Note: If this bit is set to '1', ctl_ld_pol_spi bit in the register funcsafe_mon_unlock_vco should be set to '0' to override the software based polarity setting
	*/
    uint32 LdPolarityFromSweepControl: 1;        /*## attribute LdPolarityFromSweepControl */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: ctl_ibias_TS_100u_en_ls
	* Description: Bias enable for the temperature sensor 
	* 1: Enable bias of temp sensor
	* 0: Disable bias of temp sensor
	*/
    uint32 CtlIbiasTs100UEnLs: 1;        /*## attribute CtlIbiasTs100UEnLs */
}Nxp_Tef810x_Mod06_ControlSpareBits_t;
    /**
* Nxp_Tef810x_Mod06_CalLoDetBits_t
* RegisterName: cal_lo_det
* 
* AddressRange: 0x070 - 0x074
* ResetValue: 0x00000000
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
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 1;        /*## attribute Reserved3 */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: ctl_rms_en_spi
	* Description: Enable the rms detector
	* 1: Enable rms detector
	* 0: Disable rms detector
	*/
    uint32 CtlRmsEnSpi: 1;        /*## attribute CtlRmsEnSpi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: ctl_rms_meas_in_out_spi
	* Description: Select input or output of power detector. 
	* 0=input
	* 1=output.
	*/
    uint32 CtlRmsMeasInOutSpi: 1;        /*## attribute CtlRmsMeasInOutSpi */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 1;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 2;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 6;        /*## attribute Reserved9 */
}Nxp_Tef810x_Mod06_CalLoDetBits_t;
    /**
* Nxp_Tef810x_Mod06_RefCntrInitBits_t
* RegisterName: ref_cntr_init
* 
* AddressRange: 0x07C - 0x080
* ResetValue: 0x01E00028
*/
typedef struct  {
   /**
	* BitsName: ideal_480_count_value
	* Description: This is applicable when the freq counter trigger is based on window_active (for func safety). The correct value to be programmed which is compared against the freq counter read value in the hardware. The value is restricted to 16 bits (as against 18 bit in the freq read counter value) as this triggered one time during active period of the window active and the bit width is sufficient to cover the frequency counting considering the variation of the chirp period
	*/
    uint32 Ideal480CountValue: 16;        /*## attribute Ideal480CountValue */
   /**
	* BitsName: ref_count_value
	* Description: value for the reference count time (40 MHz= 25 ns base time) default is d'40. This is used as reference count in both spi triggered mode and window_active triggered mode
	*/
    uint32 RefCountValue: 16;        /*## attribute RefCountValue */
}Nxp_Tef810x_Mod06_RefCntrInitBits_t;
    /**
* Nxp_Tef810x_Mod06_FreqCounterStartBits_t
* RegisterName: freq_counter_start
* 
* AddressRange: 0x080 - 0x084
* ResetValue: 0x00000100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: enable_func_safety_freq_mea
	* Description: By default, the frequency counter is triggered based on safety_monitor_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	* 1: trigger is based on safety_monitor_active
	* 0: Trigger is based on the spi write on bit 0 i.e freq_start
	*/
    uint32 EnableFuncSafetyFreqMea: 1;        /*## attribute EnableFuncSafetyFreqMea */
   /**
	* BitsName: num_lsbbits_ignored
	* Description: Number of lsb bits to be ignored while comparing the final freq counter read value. This is required incase of frequency counter trigger is based on window_active  for functional safety. The hardware then compares the value measured by frequency counter against ideal_480_count_value ignoring the lsb bits. 
	* 0001: Zeroth bit is ignored from comparison
	* 0011: Zeroth & first bits are ignored from comparison
	* 0111: Zeroth & first & second bits are ignored from comparison
	* 1111: Zeroth & first & second & third bits are ignored from comparison
	*/
    uint32 NumLsbbitsIgnored: 4;        /*## attribute NumLsbbitsIgnored */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle
	* 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
}Nxp_Tef810x_Mod06_FreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod06_FreqCounterReadValueBits_t
* RegisterName: freq_counter_read_value
* 
* AddressRange: 0x084 - 0x088
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: xor_parity_freq_counter
	* Description: This is simple xor of all the bits in the frequency counter read value. This bit can be used by MCU to check against stuckat fault error
	* 1: Odd parity (Number of ones in the register value is odd)
	* 0: Even parity (Number of ones in the register value is even)
	*/
    uint32 XorParityFreqCounter: 1;        /*## attribute XorParityFreqCounter */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq value = freq count value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq value = freq count value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
}Nxp_Tef810x_Mod06_FreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_RefCounterReadValueBits_t
* RegisterName: ref_counter_read_value
* 
* AddressRange: 0x088 - 0x08C
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 16;        /*## attribute Reserved0 */
   /**
	* BitsName: counter_read_value
	* Description: Reference count value
	*/
    uint32 CounterReadValue: 16;        /*## attribute CounterReadValue */
}Nxp_Tef810x_Mod06_RefCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_AtbBits_t
* RegisterName: atb
* 
* AddressRange: 0x098 - 0x09C
* ResetValue: 0x000000FF
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: atb_en
	* Description: Enable DC Test Bus
	* 1: Enable testbus
	* 0: Disable testbus
	*/
    uint32 AtbEn: 1;        /*## attribute AtbEn */
   /**
	* BitsName: atb_set
	* Description: 8'h01 :  level_vco_min (Functional Safety VCO amplitude monitor min threshold)
	* 8'h02:   level_vco_low (Functional Safety VCO amplitude monitor low threshold)
	* 8'h03:   level_vco_high(Functional Safety VCO amplitude monitor high threshold) 
	* 8'h04:   level_vco_max(Functional Safety VCO amplitude monitor max threshold)
	* 8'h05:   rms_det_ref(RMS detector reference voltage)
	* 8'h06:   rms_det (RMS detector output voltage)
	* 8'h07:   temp_sns_buffer(Temperature sensor buffer output)
	* 8'h08:   temp_sns_comp(Functional Safety Temperature Monitor comparator input (unbuffered temperature sensor output))
	* 8'h09:   vco_ibias (Reference currents for ? enabled by ?ctl_vco_pbusp_i100u_test_en?)
	* 8'h0A:   vco_ind_cnt_tap (VCO center voltage)
	* 8'h0B:   vtune_level_high (Functional Safety VCO tuning voltage monitor high threshold can be tuned by ?ctl_vtune_vco_high_spi?)
	* 8'h0C:   vtune_level_low (Functional Safety VCO tuning voltage monitorlow threshold. can be tuned by ?ctl_vtune_vco_low_spi?)
	* 8'h0D:   ldo_divider_vdd (Analog divider 1.1V supply: Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_divider_sel_vout_spi?)
	* 8'h0E:   ldo_cppfd_vdd (Analog Charge Pump/Phase Detector 1.1V supply:Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_cppfd_sel_vout_spi?)
	* 8'h0F:   ldo_vco_vdd (Analog VCO 1.1V supply: Locally divided 3/11 (? 300mV typ); can be tuned by ?ctl_ldo_vco_sel_vout_spi?)
	* 8'h10:   vdd_pll_1v8 (PLL analog 1.8V supply; Locally divided 1/6 (? 300mV typ))
	* 8'h11:   vdd_vco_1v8 (VCO analog 1.8V supply; Loacally divided 1/6 (? 300mV typ))
	* 8'h12:   ibias_cp_150u (Charge Pump current;: 150uA (typ); locally I/V converted trim-able resistor (4k); )
	* 8'h13:   ibias_ref_100u (BG Reference current;:100uA (typ); locally I/V converted trim-able resistor (4k); )
	* 8'h14:   vdd_pll_1v1 (Analog PLL 1.1V supply: Locally divided 3/11 (? 300mV typ))
	*/
    uint32 AtbSet: 8;        /*## attribute AtbSet */
}Nxp_Tef810x_Mod06_AtbBits_t;
    /**
* Nxp_Tef810x_Mod06_TestErrorFlagStatusBits_t
* RegisterName: test_error_flag_status
* 
* AddressRange: 0x0A8 - 0x0AC
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: vco_freq_480_error_flag
	* Description: vco 480 freq error flag
	* 1:  freq error is set 
	* 0:  freq error is not set
	*/
    uint32 VcoFreq480ErrorFlag: 1;        /*## attribute VcoFreq480ErrorFlag */
   /**
	* BitsName: divide_freq_error_flag
	* Description: sweep control divide freq error flag
	* 1:  divide freq error is set
	* 0:  divide freq error is not set
	*/
    uint32 DivideFreqErrorFlag: 1;        /*## attribute DivideFreqErrorFlag */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 1;        /*## attribute Reserved0 */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 1;        /*## attribute Reserved1 */
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
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 1;        /*## attribute Reserved5 */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: Reserved_7
	* Description: nan
	*/
    uint32 Reserved7: 1;        /*## attribute Reserved7 */
   /**
	* BitsName: Reserved_8
	* Description: nan
	*/
    uint32 Reserved8: 3;        /*## attribute Reserved8 */
   /**
	* BitsName: Reserved_9
	* Description: nan
	*/
    uint32 Reserved9: 1;        /*## attribute Reserved9 */
   /**
	* BitsName: Reserved_10
	* Description: nan
	*/
    uint32 Reserved10: 3;        /*## attribute Reserved10 */
   /**
	* BitsName: Reserved_11
	* Description: nan
	*/
    uint32 Reserved11: 1;        /*## attribute Reserved11 */
   /**
	* BitsName: Reserved_12
	* Description: nan
	*/
    uint32 Reserved12: 2;        /*## attribute Reserved12 */
   /**
	* BitsName: Reserved_13
	* Description: nan
	*/
    uint32 Reserved13: 2;        /*## attribute Reserved13 */
   /**
	* BitsName: Reserved_14
	* Description: nan
	*/
    uint32 Reserved14: 4;        /*## attribute Reserved14 */
}Nxp_Tef810x_Mod06_TestErrorFlagStatusBits_t;
    /**
* Nxp_Tef810x_Mod06_DivideFreqCounterStartBits_t
* RegisterName: divide_freq_counter_start
* 
* AddressRange: 0x0BC - 0x0C0
* ResetValue: 0x00000100
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 23;        /*## attribute Reserved0 */
   /**
	* BitsName: enable_func_safety_freq_mea
	* Description: By default, the frequency counter is triggered based on safety_monitor_active posedge to measure the frequency deviation if any and to report to the ISM for every chirp. If this bit is disabled, then the bit 0 of this register is required to be written to trigger the frequency counter
	* 1: Trigger based on the safety_monitor_active signal
	* 0: Trigger based on the spi write of bit 0 of this reqister i.e freq_start
	*/
    uint32 EnableFuncSafetyFreqMea: 1;        /*## attribute EnableFuncSafetyFreqMea */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 4;        /*## attribute Reserved1 */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: freq_start
	* Description: Start the freq. count
	* 0 = idle, 1 = start
	*/
    uint32 FreqStart: 1;        /*## attribute FreqStart */
}Nxp_Tef810x_Mod06_DivideFreqCounterStartBits_t;
    /**
* Nxp_Tef810x_Mod06_DivideFreqCounterReadValueBits_t
* RegisterName: divide_freq_counter_read_value
* 
* AddressRange: 0x0C0 - 0x0C4
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: xor_parity_divide_freq_counter
	* Description: This is simple xor of all the bits in the frequency counter read value. This bit can be used by MCU to check against stuckat fault error
	* 1: Odd parity (Number of ones in the register value is odd)
	* 0: Even parity (Number of ones in the register value is even)
	*/
    uint32 XorParityDivideFreqCounter: 1;        /*## attribute XorParityDivideFreqCounter */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 10;        /*## attribute Reserved0 */
   /**
	* BitsName: done_flag
	* Description: Indicates that a freq count value is valid. Write to freq counter start clear this bit
	* 1: counting done
	* 0: couting not done yet
	*/
    uint32 DoneFlag: 1;        /*## attribute DoneFlag */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 2;        /*## attribute Reserved1 */
   /**
	* BitsName: freq_count_value
	* Description: Freq value computed. Actual value need to be assessed based on  the ref_cntr_init value
	* e.g ref_cntr_int = d'40 then freq count value = reported value in MHz
	* e.g ref_cntr_int = d'400 (40*10) then freq count value = (reported value/10 ) in MHz
	*/
    uint32 FreqCountValue: 18;        /*## attribute FreqCountValue */
}Nxp_Tef810x_Mod06_DivideFreqCounterReadValueBits_t;
    /**
* Nxp_Tef810x_Mod06_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00063301
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
	* Description: Minor revision numer i.e. with no software consequences
	*/
    uint32 MinorRevision: 4;        /*## attribute MinorRevision */
   /**
	* BitsName: Aperture
	* Description: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Aperture: 8;        /*## attribute Aperture */
}Nxp_Tef810x_Mod06_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t
* Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FilterRegisterProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t;
/**
* Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t
* Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FilterParRegisterProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t;
/**
* Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t
* Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_VcoRegisterProfileBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t;
/**
* Nxp_Tef810x_Mod06_CpRegisterUnion_t
* Nxp_Tef810x_Mod06_CpRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_CpRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_CpRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_VcoBufferLdoRegisterUnion_t
* Nxp_Tef810x_Mod06_VcoBufferLdoRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_VcoBufferLdoRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_VcoBufferLdoRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t
* Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_CppfdLdoRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_DividerLdoRegisterUnion_t
* Nxp_Tef810x_Mod06_DividerLdoRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_DividerLdoRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_DividerLdoRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_BiasBlockRegisterUnion_t
* Nxp_Tef810x_Mod06_BiasBlockRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_BiasBlockRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_BiasBlockRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_BufferRegisterUnion_t
* Nxp_Tef810x_Mod06_BufferRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_BufferRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_BufferRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t
* Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_DivideForceRegisterBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t;
/**
* Nxp_Tef810x_Mod06_LoopDynamicReg0Union_t
* Nxp_Tef810x_Mod06_LoopDynamicReg0Union_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_LoopDynamicReg0Bits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_LoopDynamicReg0Union_t;
/**
* Nxp_Tef810x_Mod06_LpfVtuneVcoStatusUnion_t
* Nxp_Tef810x_Mod06_LpfVtuneVcoStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_LpfVtuneVcoStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_LpfVtuneVcoStatusUnion_t;
/**
* Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoUnion_t
* Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoUnion_t;
/**
* Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t
* Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t;
/**
* Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t
* Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t;
/**
* Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t
* Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t;
/**
* Nxp_Tef810x_Mod06_ControlSpareUnion_t
* Nxp_Tef810x_Mod06_ControlSpareUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_ControlSpareBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_ControlSpareUnion_t;
/**
* Nxp_Tef810x_Mod06_CalLoDetUnion_t
* Nxp_Tef810x_Mod06_CalLoDetUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_CalLoDetBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_CalLoDetUnion_t;
/**
* Nxp_Tef810x_Mod06_RefCntrInitUnion_t
* Nxp_Tef810x_Mod06_RefCntrInitUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_RefCntrInitBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_RefCntrInitUnion_t;
/**
* Nxp_Tef810x_Mod06_FreqCounterStartUnion_t
* Nxp_Tef810x_Mod06_FreqCounterStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FreqCounterStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FreqCounterStartUnion_t;
/**
* Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t
* Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_FreqCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod06_RefCounterReadValueUnion_t
* Nxp_Tef810x_Mod06_RefCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_RefCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_RefCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod06_AtbUnion_t
* Nxp_Tef810x_Mod06_AtbUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_AtbBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_AtbUnion_t;
/**
* Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t
* Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_TestErrorFlagStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t;
/**
* Nxp_Tef810x_Mod06_DivideFreqCounterStartUnion_t
* Nxp_Tef810x_Mod06_DivideFreqCounterStartUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_DivideFreqCounterStartBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_DivideFreqCounterStartUnion_t;
/**
* Nxp_Tef810x_Mod06_DivideFreqCounterReadValueUnion_t
* Nxp_Tef810x_Mod06_DivideFreqCounterReadValueUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_DivideFreqCounterReadValueBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_DivideFreqCounterReadValueUnion_t;
/**
* Nxp_Tef810x_Mod06_ModuleidUnion_t
* Nxp_Tef810x_Mod06_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod06_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod06_ModuleidUnion_t;
	/**
* Nxp_Tef810x_Mod06_ChirpAfcprofile_t
* Nxp_Tef810x_Mod06_ChirpAfcprofile_t
* Structure for module specific profile management
*/
typedef struct  {
  /**
    * RegisterName: filter_register_profile0
    * AddressOffset: 0x000
    * ResetValue: 0x60070017
    * Description: Filter settings
    */
    Nxp_Tef810x_Mod06_FilterRegisterProfileUnion_t FilterRegisterProfile0_ust;        /*## attribute FilterRegisterProfile0_ust */
  /**
    * RegisterName: filter_par_register_profile0
    * AddressOffset: 0x004
    * ResetValue: 0x52921616
    * Description: Filter parameter settings
    */
    Nxp_Tef810x_Mod06_FilterParRegisterProfileUnion_t FilterParRegisterProfile0_ust;        /*## attribute FilterParRegisterProfile0_ust */
  /**
    * RegisterName: vco_register_profile0
    * AddressOffset: 0x008
    * ResetValue: 0x000F0F00
    * Description: Vco control settings
    */
    Nxp_Tef810x_Mod06_VcoRegisterProfileUnion_t VcoRegisterProfile0_ust;        /*## attribute VcoRegisterProfile0_ust */
}Nxp_Tef810x_Mod06_ChirpAfcProfile_t;
/**
 * Nxp_Tef810x_Mod06_ChirpAfcRegister_t
 * Nxp_Tef810x_Mod06_ChirpAfcRegister_t
 * structure used as shadow register map
 */
typedef struct  {
	/**
    * RegisterName: Nxp_Tef810x_Mod06_ChirpAfcProfile_t;
    *AddressOffset: 0x000 - 0x02C
    * Description: Structure for module specific profile management.
                       
    */
    Nxp_Tef810x_Mod06_ChirpAfcProfile_t ChirpAfcProfile_ast[0x04];        /*## attribute ChirpAfcProfile_ast */
  /**
    * RegisterName: cp_register
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: Charge pump settings
    */
    Nxp_Tef810x_Mod06_CpRegisterUnion_t CpRegister_ust;        /*## attribute CpRegister_ust */
  /**
    * RegisterName: vco_buffer_ldo_register
    * AddressOffset: 0x034
    * ResetValue: 0x0000000F
    * Description: Vco buffer ldo controls
    */
    Nxp_Tef810x_Mod06_VcoBufferLdoRegisterUnion_t VcoBufferLdoRegister_ust;        /*## attribute VcoBufferLdoRegister_ust */
  /**
    * RegisterName: cppfd_ldo_register
    * AddressOffset: 0x038
    * ResetValue: 0x0000000F
    * Description: Charge pump Phase Frequency Detector control settings
    */
    Nxp_Tef810x_Mod06_CppfdLdoRegisterUnion_t CppfdLdoRegister_ust;        /*## attribute CppfdLdoRegister_ust */
  /**
    * RegisterName: divider_ldo_register
    * AddressOffset: 0x03C
    * ResetValue: 0x0000000F
    * Description: Divider LDO settings
    */
    Nxp_Tef810x_Mod06_DividerLdoRegisterUnion_t DividerLdoRegister_ust;        /*## attribute DividerLdoRegister_ust */
  /**
    * RegisterName: bias_block_register
    * AddressOffset: 0x040
    * ResetValue: 0x00000000
    * Description: Bias settings
    */
    Nxp_Tef810x_Mod06_BiasBlockRegisterUnion_t BiasBlockRegister_ust;        /*## attribute BiasBlockRegister_ust */
  /**
    * RegisterName: buffer_register
    * AddressOffset: 0x044
    * ResetValue: 0x00000110
    * Description: REF Buffer settings
    */
    Nxp_Tef810x_Mod06_BufferRegisterUnion_t BufferRegister_ust;        /*## attribute BufferRegister_ust */
  /**
    * RegisterName: divide_force_register
    * AddressOffset: 0x048
    * ResetValue: 0x0000011B
    * Description: PLL divider settings
    */
    Nxp_Tef810x_Mod06_DivideForceRegisterUnion_t DivideForceRegister_ust;        /*## attribute DivideForceRegister_ust */
  /**
    * RegisterName: loop_dynamic_reg_0
    * AddressOffset: 0x04C
    * ResetValue: 0x0015150F
    * Description: Loop filter settings only for internal use
    */
    Nxp_Tef810x_Mod06_LoopDynamicReg0Union_t LoopDynamicReg0_ust;        /*## attribute LoopDynamicReg0_ust */
  /**
    * RegisterName: lpf_vtune_vco_status
    * AddressOffset: 0x050
    * ResetValue: 0x00000000
    * Description: Vtune status
    */
    Nxp_Tef810x_Mod06_LpfVtuneVcoStatusUnion_t LpfVtuneVcoStatus_ust;        /*## attribute LpfVtuneVcoStatus_ust */
  /**
    * RegisterName: funcsafe_mon_vtune_vco
    * AddressOffset: 0x054
    * ResetValue: 0x00000000
    * Description: Functional safety monitor related to vtune settings
    */
    Nxp_Tef810x_Mod06_FuncsafeMonVtuneVcoUnion_t FuncsafeMonVtuneVco_ust;        /*## attribute FuncsafeMonVtuneVco_ust */
  /**
    * RegisterName: funcsafe_mon_unlock_vco
    * AddressOffset: 0x058
    * ResetValue: 0x00100020
    * Description: Functional safety monitor related to unlock settings
    */
    Nxp_Tef810x_Mod06_FuncsafeMonUnlockVcoUnion_t FuncsafeMonUnlockVco_ust;        /*## attribute FuncsafeMonUnlockVco_ust */
  /**
    * RegisterName: funcsafe_mon_level_vco
    * AddressOffset: 0x05C
    * ResetValue: 0x00007777
    * Description: Functional safety monitor related to vco level settings
    */
    Nxp_Tef810x_Mod06_FuncsafeMonLevelVcoUnion_t FuncsafeMonLevelVco_ust;        /*## attribute FuncsafeMonLevelVco_ust */
  /**
    * RegisterName: funcsafe_mon_temperature_vco
    * AddressOffset: 0x060
    * ResetValue: 0x00000000
    * Description: Functional safety monitor related to vco temperature settings
    */
    Nxp_Tef810x_Mod06_FuncsafeMonTemperatureVcoUnion_t FuncsafeMonTemperatureVco_ust;        /*## attribute FuncsafeMonTemperatureVco_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x064
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x068
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: control_spare
    * AddressOffset: 0x06C
    * ResetValue: 0x00000000
    * Description: This register is for internal (validation and debug) use
    */
    Nxp_Tef810x_Mod06_ControlSpareUnion_t ControlSpare_ust;        /*## attribute ControlSpare_ust */
  /**
    * RegisterName: cal_lo_det
    * AddressOffset: 0x070
    * ResetValue: 0x00000000
    * Description: Lo rms detector calibration settings
    */
    Nxp_Tef810x_Mod06_CalLoDetUnion_t CalLoDet_ust;        /*## attribute CalLoDet_ust */
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x074
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x078
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: ref_cntr_init
    * AddressOffset: 0x07C
    * ResetValue: 0x01E00028
    * Description: Reference count value for 480Mhz frequency measurement
    */
    Nxp_Tef810x_Mod06_RefCntrInitUnion_t RefCntrInit_ust;        /*## attribute RefCntrInit_ust */
  /**
    * RegisterName: freq_counter_start
    * AddressOffset: 0x080
    * ResetValue: 0x00000100
    * Description: 480Mhz frequency measurement trigger
    */
    Nxp_Tef810x_Mod06_FreqCounterStartUnion_t FreqCounterStart_ust;        /*## attribute FreqCounterStart_ust */
  /**
    * RegisterName: freq_counter_read_value
    * AddressOffset: 0x084
    * ResetValue: 0x00000000
    * Description: Actual frequency measurement value
    */
    Nxp_Tef810x_Mod06_FreqCounterReadValueUnion_t FreqCounterReadValue_ust;        /*## attribute FreqCounterReadValue_ust */
  /**
    * RegisterName: ref_counter_read_value
    * AddressOffset: 0x088
    * ResetValue: 0x00000000
    * Description: Reference count value
    */
    Nxp_Tef810x_Mod06_RefCounterReadValueUnion_t RefCounterReadValue_ust;        /*## attribute RefCounterReadValue_ust */
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x08C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x090
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;
  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x094
    * ResetValue: 0x0000001F
    * Description: 	nan
    */
    uint32 Reserved06;
  /**
    * RegisterName: atb
    * AddressOffset: 0x098
    * ResetValue: 0x000000FF
    * Description: ATB bus settings
    */
    Nxp_Tef810x_Mod06_AtbUnion_t Atb_ust;        /*## attribute Atb_ust */
  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x09C
    * ResetValue: 0x0000002B
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x0A0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved08;
  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x0A4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: test_error_flag_status
    * AddressOffset: 0x0A8
    * ResetValue: 0x00000000
    * Description: This register is kept for validation and not to be used in the functional context. This register indicates the status of the errors
    */
    Nxp_Tef810x_Mod06_TestErrorFlagStatusUnion_t TestErrorFlagStatus_ust;        /*## attribute TestErrorFlagStatus_ust */
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x0AC
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x0B0
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;
  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x0B4
    * ResetValue: 0x000000FF
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x0B8
    * ResetValue: 0x00000001
    * Description: 	nan
    */
    uint32 Reserved0D;
  /**
    * RegisterName: divide_freq_counter_start
    * AddressOffset: 0x0BC
    * ResetValue: 0x00000100
    * Description: Trigger for divider output frequency measurement
    */
    Nxp_Tef810x_Mod06_DivideFreqCounterStartUnion_t DivideFreqCounterStart_ust;        /*## attribute DivideFreqCounterStart_ust */
  /**
    * RegisterName: divide_freq_counter_read_value
    * AddressOffset: 0x0C0
    * ResetValue: 0x00000000
    * Description: Divider output frequency measured value
    */
    Nxp_Tef810x_Mod06_DivideFreqCounterReadValueUnion_t DivideFreqCounterReadValue_ust;        /*## attribute DivideFreqCounterReadValue_ust */
 /**   
	* RegisterName: Reserved0E
    * AddressOffset: 0x0C4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;

    uint32 gap01_au32[971];        /* gap 1 in register space */  /**
    * RegisterName: Reserved0F
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0F;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00063301
    * Description: Module ID of the block
    */
    Nxp_Tef810x_Mod06_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod06_ChirpAfcRegister_t;

#endif
