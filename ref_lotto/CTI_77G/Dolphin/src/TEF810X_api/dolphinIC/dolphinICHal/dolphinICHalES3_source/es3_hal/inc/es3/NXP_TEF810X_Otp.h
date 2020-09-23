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
* @NXP_TEF810X_Otp.h
*/
#ifndef NXP_TEF810X_OTP_H
#define NXP_TEF810X_OTP_H
#include "Std_Types.h"

#define OTP_MODULE_ADDRESS 0x17
/**
*NXP_TEF810X_MOD17_OTP_STATUS_U16
* RegisterName: MOD17_OTP_STATUS
* AccessMode: READ
* AddressRange: 0x0040 - 0x0044
* ResetValue: 0x00000007
*/
#define NXP_TEF810X_MOD17_OTP_STATUS_U16 (uint16)0x0040
/**
*NXP_TEF810X_MOD17_OTP_DATA_RD_REG_U16
* RegisterName: MOD17_OTP_DATA_RD_REG
* AccessMode: READ
* AddressRange: 0x0200 - 0x0204
* ResetValue: 0x00000000
*/
#define NXP_TEF810X_MOD17_OTP_DATA_RD_REG_U16 (uint16)0x0200
/**
*NXP_TEF810X_MOD17_MODULEID_U16
* RegisterName: MOD17_ModuleID
* AccessMode: READ
* AddressRange: 0x0FFC - 0x1000
* ResetValue: 0x00172201
*/
#define NXP_TEF810X_MOD17_MODULEID_U16 (uint16)0x0FFC

#ifdef NXP_TEF810X_CPU_LITTLE_ENDIAN/**
* Nxp_Tef810x_Mod17_OTP_STATUSBits_t
* RegisterName: OTP_STATUS
* 
* AddressRange: 0xREAD - 0x040
* ResetValue: 0x00000044
*/
typedef struct  {
   /**
	* BitsName: ready_for_read
	* Description: Read to OTP_DATA_REG should happen only if this bit is HIGH associated with prreaddone
	*/
    uint32 ReadyForRead: 1;        /*## attribute ReadyForRead */
   /**
	* BitsName: ready_for_write
	* Description: write to OTP_DATA_REG should happen only if this bit is HIGH associated with prreaddone
	*/
    uint32 ReadyForWrite: 1;        /*## attribute ReadyForWrite */
   /**
	* BitsName: prreaddone
	* Description: High indicates power on reset read is completed. This read is internally initiated by the OTP controller. So this bit will automatically set to '1' few clock cycles after power on reset.
	*/
    uint32 Prreaddone: 1;        /*## attribute Prreaddone */
   /**
	* BitsName: time_out_error
	* Description: High indicates FSOURCE active time exceeded the maximum allowable time
	*/
    uint32 TimeOutError: 1;        /*## attribute TimeOutError */
   /**
	* BitsName: otp_cmd_error
	* Description: Goes high when any read/write comes to OTP_DATA_REG register when ready_for_read/ read_for_wrtie  flag respectively is low or prreaddone flag is low. Also goes high if write comes and prconfigdone is high.                                           Gets cleared when STATUS register is read.
	*/
    uint32 OtpCmdError: 1;        /*## attribute OtpCmdError */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: fsource_active_count
	* Description: FSOURCE active value is tracked through an up counter inside the OTP controller. This up counter active value can be read through FSOURCE_ACTIVE_COUNT these register bits. It is an up counter and software can program the max value using ?FSOURCE_MAX? register.         FSOURCE_ACTIVE time = (FSOURCE_ACTIVE_COUNT) * 25 ns  Note:  FSOURCE_ACTIVE_COUNT is value is invalid, if Time out error = ?1'
	*/
    uint32 FsourceActiveCount: 20;        /*## attribute FsourceActiveCount */
}Nxp_Tef810x_Mod17_OtpStatusBits_t;
    /**
* Nxp_Tef810x_Mod17_OTP_DATA_RD_REGBits_t
* RegisterName: OTP_DATA_RD_REG
* 
* AddressRange: 0xREAD - 0x200
* ResetValue: 0x00000204
*/
typedef struct  {
   /**
	* BitsName: otp_data_rd_reg
	* Description: OTP_DATA_REG provides read access to the controller to OTP memory.  Read access to this register trigger the read operation (pre-fetch) inside OTP controller.  Only burst read is supported in OTP. In every burst 1st data will be invalid data and Software should ignore this. This is due to the internal memory/controller latency requirement.                       NOTE: Read to this register is only possible when ready_for_read is '1' and prreaddone is '1'
	*/
    uint32 OtpDataRdReg: 32;        /*## attribute OtpDataRdReg */
}Nxp_Tef810x_Mod17_OtpDataRdRegBits_t;
    /**
* Nxp_Tef810x_Mod17_MODULEIDBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xREAD - 0xFFC
* ResetValue: 0x00001000
*/
typedef struct  {
   /**
	* BitsName: APPERURE
	* Description: Aperture: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Apperure: 8;        /*## attribute Apperure */
   /**
	* BitsName: MINOR_RIVISION
	* Description: Minor revision: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRivision: 4;        /*## attribute MinorRivision */
   /**
	* BitsName: MAJOR_RIVISION
	* Description: Major revision: Major revision i.e. implies software modifications.
	*/
    uint32 MajorRivision: 4;        /*## attribute MajorRivision */
   /**
	* BitsName: IDENTIFIER
	* Description: Identifier value. This is the unique identifier of the module. In case of OTP it is 0x17
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
}Nxp_Tef810x_Mod17_ModuleidBits_t;
    #endif

#ifdef NXP_TEF810X_CPU_BIG_ENDIAN/**
* Nxp_Tef810x_Mod17_OtpStatusBits_t
* RegisterName: OTP_STATUS
* 
* AddressRange: 0x040 - 0x044
* ResetValue: 0x00000007
*/
typedef struct  {
   /**
	* BitsName: fsource_active_count
	* Description: FSOURCE active value is tracked through an up counter inside the OTP controller. This up counter active value can be read through FSOURCE_ACTIVE_COUNT these register bits. It is an up counter and software can program the max value using ?FSOURCE_MAX? register.         FSOURCE_ACTIVE time = (FSOURCE_ACTIVE_COUNT) * 25 ns  Note:  FSOURCE_ACTIVE_COUNT is value is invalid, if Time out error = ?1'
	*/
    uint32 FsourceActiveCount: 20;        /*## attribute FsourceActiveCount */
   /**
	* BitsName: Reserved_0
	* Description: nan
	*/
    uint32 Reserved0: 7;        /*## attribute Reserved0 */
   /**
	* BitsName: otp_cmd_error
	* Description: Goes high when any read/write comes to OTP_DATA_REG register when ready_for_read/ read_for_wrtie  flag respectively is low or prreaddone flag is low. Also goes high if write comes and prconfigdone is high.                                           Gets cleared when STATUS register is read.
	*/
    uint32 OtpCmdError: 1;        /*## attribute OtpCmdError */
   /**
	* BitsName: time_out_error
	* Description: High indicates FSOURCE active time exceeded the maximum allowable time
	*/
    uint32 TimeOutError: 1;        /*## attribute TimeOutError */
   /**
	* BitsName: prreaddone
	* Description: High indicates power on reset read is completed. This read is internally initiated by the OTP controller. So this bit will automatically set to '1' few clock cycles after power on reset.
	*/
    uint32 Prreaddone: 1;        /*## attribute Prreaddone */
   /**
	* BitsName: ready_for_write
	* Description: write to OTP_DATA_REG should happen only if this bit is HIGH associated with prreaddone
	*/
    uint32 ReadyForWrite: 1;        /*## attribute ReadyForWrite */
   /**
	* BitsName: ready_for_read
	* Description: Read to OTP_DATA_REG should happen only if this bit is HIGH associated with prreaddone
	*/
    uint32 ReadyForRead: 1;        /*## attribute ReadyForRead */
}Nxp_Tef810x_Mod17_OtpStatusBits_t;
    /**
* Nxp_Tef810x_Mod17_OtpDataRdRegBits_t
* RegisterName: OTP_DATA_RD_REG
* 
* AddressRange: 0x200 - 0x204
* ResetValue: 0x00000000
*/
typedef struct  {
   /**
	* BitsName: otp_data_rd_reg
	* Description: OTP_DATA_REG provides read access to the controller to OTP memory.  Read access to this register trigger the read operation (pre-fetch) inside OTP controller.  Only burst read is supported in OTP. In every burst 1st data will be invalid data and Software should ignore this. This is due to the internal memory/controller latency requirement.                       NOTE: Read to this register is only possible when ready_for_read is '1' and prreaddone is '1'
	*/
    uint32 OtpDataRdReg: 32;        /*## attribute OtpDataRdReg */
}Nxp_Tef810x_Mod17_OtpDataRdRegBits_t;
    /**
* Nxp_Tef810x_Mod17_ModuleidBits_t
* RegisterName: ModuleID
* 
* AddressRange: 0xFFC - 0x1000
* ResetValue: 0x00172201
*/
typedef struct  {
   /**
	* BitsName: IDENTIFIER
	* Description: Identifier value. This is the unique identifier of the module. In case of OTP it is 0x17
	*/
    uint32 Identifier: 16;        /*## attribute Identifier */
   /**
	* BitsName: MAJOR_RIVISION
	* Description: Major revision: Major revision i.e. implies software modifications.
	*/
    uint32 MajorRivision: 4;        /*## attribute MajorRivision */
   /**
	* BitsName: MINOR_RIVISION
	* Description: Minor revision: Minor revision number i.e. with no software consequences
	*/
    uint32 MinorRivision: 4;        /*## attribute MinorRivision */
   /**
	* BitsName: APPERURE
	* Description: Aperture: Aperture i.e. number minus 1 of consecutive packets reserved for this IP. 0 is classical value
	*/
    uint32 Apperure: 8;        /*## attribute Apperure */
}Nxp_Tef810x_Mod17_ModuleidBits_t;
    #endif
/**
* Nxp_Tef810x_Mod17_OtpStatusUnion_t
* Nxp_Tef810x_Mod17_OtpStatusUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod17_OtpStatusBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod17_OtpStatusUnion_t;
/**
* Nxp_Tef810x_Mod17_OtpDataRdRegUnion_t
* Nxp_Tef810x_Mod17_OtpDataRdRegUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod17_OtpDataRdRegBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod17_OtpDataRdRegUnion_t;
/**
* Nxp_Tef810x_Mod17_ModuleidUnion_t
* Nxp_Tef810x_Mod17_ModuleidUnion_t
* union used for simple register initialization
*/
typedef union  {
    /**
    * ## attribure bits_st
    */
    Nxp_Tef810x_Mod17_ModuleidBits_t bits_st;        /*## attribute bits_st */
    /**
    * ## attribute val_u32
    */
    uint32 val_u32;        /*## attribute val_u32 */
    }Nxp_Tef810x_Mod17_ModuleidUnion_t;

/**
 * Nxp_Tef810x_Mod17_OtpRegister_t
 * Nxp_Tef810x_Mod17_OtpRegister_t
 * structure used as shadow register map
 */
typedef struct  {
  /**
    * RegisterName: Reserved00
    * AddressOffset: 0x000
    * ResetValue: 0x000000A0
    * Description: 	nan
    */
    uint32 Reserved00;
  /**
    * RegisterName: Reserved01
    * AddressOffset: 0x004
    * ResetValue: 0x0C50020C
    * Description: 	nan
    */
    uint32 Reserved01;
  /**
    * RegisterName: Reserved02
    * AddressOffset: 0x008
    * ResetValue: 0x00061A80
    * Description: 	nan
    */
    uint32 Reserved02;
  /**
    * RegisterName: Reserved03
    * AddressOffset: 0x00C
    * ResetValue: 0x00000100
    * Description: 	nan
    */
    uint32 Reserved03;

    uint32 gap01_au32[12];        /* gap 1 in register space */  /**
    * RegisterName: OTP_STATUS
    * AddressOffset: 0x040
    * ResetValue: 0x00000007
    * Description: Read /WriteStatus register.
    */
    Nxp_Tef810x_Mod17_OtpStatusUnion_t OtpStatus_ust;        /*## attribute OtpStatus_ust */

    uint32 gap02_au32[47];        /* gap 2 in register space */  /**
    * RegisterName: Reserved04
    * AddressOffset: 0x100
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved04;

    uint32 gap03_au32[63];        /* gap 3 in register space */  /**
    * RegisterName: OTP_DATA_RD_REG
    * AddressOffset: 0x200
    * ResetValue: 0x00000000
    * Description: OTP data read register
    */
    Nxp_Tef810x_Mod17_OtpDataRdRegUnion_t OtpDataRdReg_ust;        /*## attribute OtpDataRdReg_ust */

    uint32 gap04_au32[892];        /* gap 4 in register space */  /**
    * RegisterName: Reserved05
    * AddressOffset: 0xFF4
    * ResetValue: 0x00000000
    * Description: 	nan
    */
    uint32 Reserved05;

    uint32 gap05_au32[1];        /* gap 5 in register space */  /**
    * RegisterName: ModuleID
    * AddressOffset: 0xFFC
    * ResetValue: 0x00172201
    * Description: Module Idetification Register
    */
    Nxp_Tef810x_Mod17_ModuleidUnion_t Moduleid_ust;        /*## attribute Moduleid_ust */
}Nxp_Tef810x_Mod17_OtpRegister_t;

#endif
