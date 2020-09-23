/*
 * fbl_spec.h
 * Flash bootloader specification
 *  Created on: 2019¦~10¤ë15¤é
 *      Author: WoodLiu
 */

#ifndef FBL_SPEC_H_
#define FBL_SPEC_H_

#include <bl_parameters.h>
#include "bl_typedefs.h"
#include "version.h"

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define FBL_PARS_ID								FOURCC('f','b','l','p')
#define fbl_pars_info_get(_ver,_size)			pars_info_get(FBL_PARS_ID,  _ver,_size)
#define fbl_pars_info_set(_data,_cnt)			pars_info_set(FBL_PARS_ID, _data, _cnt))

#define LENGTH_OF_TESTER_SN			(10)
#define LENGTH_OF_PROGRAMING_DATE	(4)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
typedef struct
{
	bl_revision_t 	rev_read_only;
	char			F180_BootloaderVersionNumber[LENGTH_OF_BL_VERSION+1];	//Data Type:ASCII
	char 			F198_TesterSeriesNumber[LENGTH_OF_TESTER_SN+1]; 		//Data Type:ASCII
	bl_u8_t 		F199_ProgrammingDate[LENGTH_OF_PROGRAMING_DATE]; 		//Data Type:BCD
	bl_u32_t		Reprogramming_flag;
}bl_info_t, *bl_info_p;

typedef struct {
	bl_pars_header_t	hdr;
	bl_info_t			info;
}bl_parameters_t, *bl_parameters_p;

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void fbl_spec_init();
extern bl_Return_t set_F180_BootloaderVersionNumber(char* sn);
extern bl_Return_t set_F198_TesterSeriesNumber(char* sn);
extern bl_Return_t set_F199_ProgrammingDate(bl_u8_t* date, bl_u8_t len);
extern bl_u8_t* get_F180_BootloaderVersionNumber();
extern bl_u8_t* get_F198_TesterSeriesNumber();
extern bl_u8_t* get_F199_ProgrammingDate();

extern bl_Return_t is_need_reprogram();
extern void clear_reprogram_flag();


#endif /* FBL_SPEC_H_ */
