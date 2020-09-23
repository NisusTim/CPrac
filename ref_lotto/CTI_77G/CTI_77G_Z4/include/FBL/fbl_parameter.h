/*
 * fbl_parameter.h
 *
 *  Created on: 2019¦~10¤ë16¤é
 *      Author: WoodLiu
 */

#ifndef FBL_FBL_PARAMETER_H_
#define FBL_FBL_PARAMETER_H_

#include "upgrade.h"
#include "parameters.h"
/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define FBL_PARS_ID								FOURCC('f','b','l','p')
#define fbl_pars_info_get(_ver,_size)			pars_info_get(FBL_PARS_ID,  _ver,_size)
#define fbl_pars_info_set(_data,_cnt)			pars_info_set(FBL_PARS_ID, _data, _cnt))

#define LENGTH_OF_TESTER_SN			(10)
#define LENGTH_OF_PROGRAMING_DATE	(4)

#define LENGTH_OF_BL_VERSION		(16)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
typedef struct
{
	revision_t 		rev_read_only;
	char			F180_BootloaderVersionNumber[LENGTH_OF_BL_VERSION+1];	//Data Type:ASCII
	char 			F198_TesterSeriesNumber[LENGTH_OF_TESTER_SN+1]; 		//Data Type:ASCII
	uint8_t 		F199_ProgrammingDate[LENGTH_OF_PROGRAMING_DATE]; 		//Data Type:BCD
	uint32_t 		Reprogramming_flag;
}bl_info_t, *bl_info_p;

typedef struct {
	pars_header_t	hdr;
	bl_info_t		info;
}bl_parameters_t, *bl_parameters_p;

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void fbl_spec_init();
extern uint8_t set_F198_TesterSeriesNumber(char* sn);
extern uint8_t set_F199_ProgrammingDate(uint8_t* date, uint8_t len);
extern uint8_t* get_F180_BootloaderVersionNumber();
extern uint8_t* get_F198_TesterSeriesNumber();
extern uint8_t* get_F199_ProgrammingDate();

extern void set_reporgram_flag();

#endif /* FBL_FBL_PARAMETER_H_ */
