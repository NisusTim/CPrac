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
* @NXP_TEF810X_Ssbmod.h
*/
#ifndef NXP_TEF810X_SSBMOD_H
#define NXP_TEF810X_SSBMOD_H
#include "Std_Types.h"

#define SSBMOD_MODULE_ADDRESS 0x14
/**
*NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16
* RegisterName: MOD14_SSBmod_control
* AccessMode: READWRITE
* AddressRange: 0x0000 - 0x0004
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD14_SSBMOD_CONTROL_U16 (uint16)0x0000
/**
*NXP_TEF810X_MOD14_IF_CONTROL_U16
* RegisterName: MOD14_IF_CONTROL
* AccessMode: READWRITE
* AddressRange: 0x0004 - 0x0008
* ResetValue: 0x00001120
*/
#define NXP_TEF810X_MOD14_IF_CONTROL_U16 (uint16)0x0004
/**
*NXP_TEF810X_MOD14_LEVEL_SET_U16
* RegisterName: MOD14_LEVEL_set
* AccessMode: READWRITE
* AddressRange: 0x0008 - 0x000C
* ResetValue: 0x00000020
*/
#define NXP_TEF810X_MOD14_LEVEL_SET_U16 (uint16)0x0008
/**
*NXP_TEF810X_MOD14_MODULEID_U16
* RegisterName: MOD14_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00141101
*/
#define NXP_TEF810X_MOD14_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod14_SSBMOD_CONTROLBits_t
* RegisterName: SSBmod_control
* 
* AddressRange: 0xREADWRITE - 0x000
* ResetValue: 0x00000004
*/
typedef struct  {
   /**
	* BitsName: ssbmod_en
	* Description: SSB modulator Control
	* 0 = Disable SSB modulator
	* 1 = Enable SSB modulator
	*/
    uint32 SsbmodEn: 1;        /*## attribute SsbmodEn */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: mod_sel
	* Description: Select modulation input:
	* 0 = internal signal generator
	* 1 = external signal generator
	*/
    uint32 ModSel: 1;        /*## attribute ModSel */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: en_rf_det
	* Description: Controls RMS Detector inside SSB Module
	* 0 = Disable RMS detector
	* 1 = Enable RMS detector
	*/
    uint32 EnRfDet: 1;        /*## attribute EnRfDet */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 3;        /*## attribute Reserved2 */
   /**
	* BitsName: div1_set
	* Description: Select division ratio N1 of DIV1(First Divider in the divider chan in SSB Digital Module) (divider ratio = programmed value + 1)
	*/
    uint32 Div1Set: 5;        /*## attribute Div1Set */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: div2_set
	* Description: Select division ratio N2 of DIV2(second stage divider) inside SSB Digital Module.
	* 000 = Select the divider ratio as  1
	* 001 = Select the divider ratio as  4
	* 010 = Select the divider ratio as  16
	* 011 = Select the divider ratio as  64
	* 100 = Select the divider ratio as  256
	* 101 = Select the divider ratio as  1024
	*/
    uint32 Div2Set: 3;        /*## attribute Div2Set */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 1;        /*## attribute Reserved4 */
   /**
	* BitsName: pon_ls_spi
	* Description: This enables the level shifters between digital and analogue modules
	* 0 = Disable the Level Shifters
	* 1 = Enable the Level Shifters
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: clk_600_en
	* Description: This is the clock enable signal for analogue module.
	* 0 = Disable the 600Mhz Clock from MasterClock
	* 1 = Enable the 600Mhz Clock from MasterClock
	*/
    uint32 Clk600En: 1;        /*## attribute Clk600En */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod14_SsbmodControlBits_t;
    /**
* Nxp_Tef810x_Mod14_IF_CONTROLBits_t
* RegisterName: IF_CONTROL
* 
* AddressRange: 0xREADWRITE - 0x004
* ResetValue: 0x00000008
*/
typedef struct  {
   /**
	* BitsName: if_level_set
	* Description: IF level control: 3 LSBs set the internal IF signal in 4 dB steps, bit 4 sets gain of the IF transconductor with 18 dB step.
	*/
    uint32 IfLevelSet: 6;        /*## attribute IfLevelSet */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 2;        /*## attribute Reserved0 */
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
    uint32 Reserved6: 15;        /*## attribute Reserved6 */
}Nxp_Tef810x_Mod14_IfControlBits_t;
    /**
* Nxp_Tef810x_Mod14_LEVEL_SETBits_t
* RegisterName: LEVEL_set
* 
* AddressRange: 0xREADWRITE - 0x008
* ResetValue: 0x0000000C
*/
typedef struct  {
   /**
	* BitsName: level_set
	* Description: Control SSB modulator output level [dBm]
	*/
    uint32 LevelSet: 6;        /*## attribute LevelSet */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
}Nxp_Tef810x_Mod14_LevelSetBits_t;
    /**
* Nxp_Tef810x_Mod14_MODULEIDBits_t
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
}Nxp_Tef810x_Mod14_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod14_SsbmodControlBits_t
* RegisterName: SSBmod_control
* 
* AddressRange: 0x000 - 0x004
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 3;        /*## attribute Reserved0 */
   /**
	* BitsName: clk_600_en
	* Description: This is the clock enable signal for analogue module.
	* 0 = Disable the 600Mhz Clock from MasterClock
	* 1 = Enable the 600Mhz Clock from MasterClock
	*/
    uint32 Clk600En: 1;        /*## attribute Clk600En */
   /**
	* BitsName: Reserved_1
	* Description: nan
	*/
    uint32 Reserved1: 3;        /*## attribute Reserved1 */
   /**
	* BitsName: pon_ls_spi
	* Description: This enables the level shifters between digital and analogue modules
	* 0 = Disable the Level Shifters
	* 1 = Enable the Level Shifters
	*/
    uint32 PonLsSpi: 1;        /*## attribute PonLsSpi */
   /**
	* BitsName: Reserved_2
	* Description: nan
	*/
    uint32 Reserved2: 1;        /*## attribute Reserved2 */
   /**
	* BitsName: div2_set
	* Description: Select division ratio N2 of DIV2(second stage divider) inside SSB Digital Module.
	* 000 = Select the divider ratio as  1
	* 001 = Select the divider ratio as  4
	* 010 = Select the divider ratio as  16
	* 011 = Select the divider ratio as  64
	* 100 = Select the divider ratio as  256
	* 101 = Select the divider ratio as  1024
	*/
    uint32 Div2Set: 3;        /*## attribute Div2Set */
   /**
	* BitsName: Reserved_3
	* Description: nan
	*/
    uint32 Reserved3: 3;        /*## attribute Reserved3 */
   /**
	* BitsName: div1_set
	* Description: Select division ratio N1 of DIV1(First Divider in the divider chan in SSB Digital Module) (divider ratio = programmed value + 1)
	*/
    uint32 Div1Set: 5;        /*## attribute Div1Set */
   /**
	* BitsName: Reserved_4
	* Description: nan
	*/
    uint32 Reserved4: 3;        /*## attribute Reserved4 */
   /**
	* BitsName: en_rf_det
	* Description: Controls RMS Detector inside SSB Module
	* 0 = Disable RMS detector
	* 1 = Enable RMS detector
	*/
    uint32 EnRfDet: 1;        /*## attribute EnRfDet */
   /**
	* BitsName: Reserved_5
	* Description: nan
	*/
    uint32 Reserved5: 3;        /*## attribute Reserved5 */
   /**
	* BitsName: mod_sel
	* Description: Select modulation input:
	* 0 = internal signal generator
	* 1 = external signal generator
	*/
    uint32 ModSel: 1;        /*## attribute ModSel */
   /**
	* BitsName: Reserved_6
	* Description: nan
	*/
    uint32 Reserved6: 3;        /*## attribute Reserved6 */
   /**
	* BitsName: ssbmod_en
	* Description: SSB modulator Control
	* 0 = Disable SSB modulator
	* 1 = Enable SSB modulator
	*/
    uint32 SsbmodEn: 1;        /*## attribute SsbmodEn */
}Nxp_Tef810x_Mod14_SsbmodControlBits_t;
    /**
* Nxp_Tef810x_Mod14_IfControlBits_t
* RegisterName: IF_CONTROL
* 
* AddressRange: 0x004 - 0x008
* ResetValue: 0x00001120
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 15;        /*## attribute Reserved0 */
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
    uint32 Reserved6: 2;        /*## attribute Reserved6 */
   /**
	* BitsName: if_level_set
	* Description: IF level control: 3 LSBs set the internal IF signal in 4 dB steps, bit 4 sets gain of the IF transconductor with 18 dB step.
	*/
    uint32 IfLevelSet: 6;        /*## attribute IfLevelSet */
}Nxp_Tef810x_Mod14_IfControlBits_t;
    /**
* Nxp_Tef810x_Mod14_LevelSetBits_t
* RegisterName: LEVEL_set
* 
* AddressRange: 0x008 - 0x00C
* ResetValue: 0x00000020
*/
typedef struct  {
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 26;        /*## attribute Reserved0 */
   /**
	* BitsName: level_set
	* Description: Control SSB modulator output level [dBm]
	*/
    uint32 LevelSet: 6;        /*## attribute LevelSet */
}Nxp_Tef810x_Mod14_LevelSetBits_t;
    /**
* Nxp_Tef810x_Mod14_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00141101
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
}Nxp_Tef810x_Mod14_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod14_SsbmodControlUnion_t
* Nxp_Tef810x_Mod14_SsbmodControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod14_SsbmodControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod14_SsbmodControlUnion_t;
/**
* Nxp_Tef810x_Mod14_IfControlUnion_t
* Nxp_Tef810x_Mod14_IfControlUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod14_IfControlBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod14_IfControlUnion_t;
/**
* Nxp_Tef810x_Mod14_LevelSetUnion_t
* Nxp_Tef810x_Mod14_LevelSetUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod14_LevelSetBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod14_LevelSetUnion_t;
/**
* Nxp_Tef810x_Mod14_ModuleidUnion_t
* Nxp_Tef810x_Mod14_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod14_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod14_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod14_SsbmodRegister_t
 * Nxp_Tef810x_Mod14_SsbmodRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: SSBmod_control
    * AddressOffset: 0x000
    * ResetValue: 0x00000000
    * Description: This is the control register for SSB Module. This register also selects the divider ratios of varaiable dividers inside SSB Digital Module.
    */
    Nxp_Tef810x_Mod14_SsbmodControlUnion_t SsbmodControl_ust;        /*## attribute SsbmodControl_ust */
  /**
    * RegisterName: IF_CONTROL
    * AddressOffset: 0x004
    * ResetValue: 0x00001120
    * Description: This register is not used
    */
    Nxp_Tef810x_Mod14_IfControlUnion_t IfControl_ust;        /*## attribute IfControl_ust */
  /**
    * RegisterName: LEVEL_set
    * AddressOffset: 0x008
    * ResetValue: 0x00000020
    * Description: Output Level control reg
    */
    Nxp_Tef810x_Mod14_LevelSetUnion_t LevelSet_ust;        /*## attribute LevelSet_ust */
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x00C
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x010
    * ResetValue: 0x00000003
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x014
    * ResetValue: 0x00000004
    * Description: 	nan
    */
    uint32 Reserved02;

    uint32 gap01_au32[2];        /* gap 1 in register space */  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x020
    * ResetValue: 0x00001F1F
    * Description: 	nan
    */
    uint32 Reserved03;
  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x024
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;
  /**
    * RegisterName: Reserved05
    * AddressOffset: 0x028
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;

    uint32 gap02_au32[1];        /* gap 2 in register space */  /**
    * RegisterName: Reserved06
    * AddressOffset: 0x030
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved06;

    uint32 gap03_au32[51];        /* gap 3 in register space */  /**
    * RegisterName: Reserved07
    * AddressOffset: 0x100
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved07;
  /**
    * RegisterName: Reserved08
    * AddressOffset: 0x104
    * ResetValue: 0x00000001
    * Description: 	nan
    */
    uint32 Reserved08;

    uint32 gap04_au32[254];        /* gap 4 in register space */  /**
    * RegisterName: Reserved09
    * AddressOffset: 0x500
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved09;
  /**
    * RegisterName: Reserved0A
    * AddressOffset: 0x504
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0A;
  /**
    * RegisterName: Reserved0B
    * AddressOffset: 0x508
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0B;

    uint32 gap05_au32[61];        /* gap 5 in register space */  /**
    * RegisterName: Reserved0C
    * AddressOffset: 0x600
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0C;
  /**
    * RegisterName: Reserved0D
    * AddressOffset: 0x604
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0D;

    uint32 gap06_au32[635];        /* gap 6 in register space */  /**
    * RegisterName: Reserved0E
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved0E;

    uint32 gap07_au32[1];        /* gap 7 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00141101
    * Description: Module ID register
    */
    Nxp_Tef810x_Mod14_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod14_SsbmodRegister_t;

#endif
