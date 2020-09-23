/*
 * fbl_parameter.c
 *
 *  Created on: 2019¦~10¤ë16¤é
 *      Author: WoodLiu
 */

#include <stdio.h>
#include <cstdint>
#include "console.h"
#include "fbl_parameter.h"
#include "string.h"
#include "App_boot.h"
#include "console_cmd.h"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define PARS_FBL_VERSION_MAJOR 		0x02
#define PARS_FBL_VERSION_MINOR 		0x00
#define VERSION_OF_FBL_PARS    		(((uint16_t)PARS_FBL_VERSION_MAJOR<<8) | PARS_FBL_VERSION_MINOR)

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void bl_pars_dump(void);
static void fbl_pars_setting(char** args, int count);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
bl_parameters_t bl_parameters = {
		.hdr = {
			.base = (uint32_t)&bl_parameters,
			.version = VERSION_OF_FBL_PARS,
			.size = sizeof(bl_parameters_t),
			.id=FBL_PARS_ID,
			.chksum = 0,
			.mask = 0,
		},
		.info = {
			.F180_BootloaderVersionNumber = {'\0'},
			.F198_TesterSeriesNumber = {'\0'},
			.F199_ProgrammingDate	 = {0x00},
			.Reprogramming_flag		 = 0x0
		}
};

static bl_info_p bl_info_pars = &bl_parameters.info;


/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
#define BL_ERR_OK 				(0)	//@see ref at bl_typedefs.h
#define BL_ERR_BUFFER_OVERFLOW  (6)	//@see ref at bl_typedefs.h
/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
void fbl_spec_init()
{
	pars_get((pars_ctx_p)&bl_parameters, bl_pars_dump, NULL);

	console_command_reg("fblp", fbl_pars_setting);
}

static void fbl_pars_setting(char** args, int count)
{
	bl_pars_dump();
}

uint8_t F180_BootloaderVersionNumber(char* sn)
{
	int len = strlen(sn);

	if(len > LENGTH_OF_TESTER_SN)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	strcpy(bl_info_pars->F180_BootloaderVersionNumber, sn);

	pars_set((pars_ctx_p)&bl_parameters);

	return BL_ERR_OK;
}

uint8_t set_F198_TesterSeriesNumber(char* sn)
{
	int len = strlen(sn);

	if(len > LENGTH_OF_TESTER_SN)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	strcpy(bl_info_pars->F198_TesterSeriesNumber, sn);

	pars_set((pars_ctx_p)&bl_parameters);

	return BL_ERR_OK;
}

uint8_t set_F199_ProgrammingDate(uint8_t* date, uint8_t len)
{
	if(len > LENGTH_OF_PROGRAMING_DATE)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	memcpy(bl_info_pars->F199_ProgrammingDate, date, LENGTH_OF_PROGRAMING_DATE);

	pars_set((pars_ctx_p)&bl_parameters);

	return BL_ERR_OK;
}

uint8_t* get_F180_BootloaderVersionNumber()
{
	return (uint8_t *)&bl_info_pars->F180_BootloaderVersionNumber[0];
}

uint8_t* get_F198_TesterSeriesNumber()
{
	return (uint8_t *)&bl_info_pars->F198_TesterSeriesNumber[0];
}

uint8_t* get_F199_ProgrammingDate()
{
	return (uint8_t *)&bl_info_pars->F199_ProgrammingDate[0];
}

void set_reporgram_flag()
{
	bl_info_pars->Reprogramming_flag = FLAG_REPROGRAM_DATA;
	pars_set((pars_ctx_p)&bl_parameters);
}


static void bl_pars_dump(void)
{
	char rev_build_char[]={'a','b','r','x'};
#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("Flash Bootloader parameters:\n");
	PRINTF("- Bootloader rev: V%u.%u.%u.%u.%c%u.%u\n",bl_info_pars->rev_read_only.major,bl_info_pars->rev_read_only.product,
			bl_info_pars->rev_read_only.cusid,bl_info_pars->rev_read_only.minor,rev_build_char[bl_info_pars->rev_read_only.build],
			bl_info_pars->rev_read_only.maintenance,bl_info_pars->rev_read_only.svn);
	PRINTF("- Bootloader version number: %s\n", bl_info_pars->F180_BootloaderVersionNumber);
	PRINTF("- Tester series number (testersn): %s\n", bl_info_pars->F198_TesterSeriesNumber);
	PRINTF("- Programming Date (progdate): %.2x%.2x%.2x%.2x\n",
			bl_info_pars->F199_ProgrammingDate[0], bl_info_pars->F199_ProgrammingDate[1],
			bl_info_pars->F199_ProgrammingDate[2], bl_info_pars->F199_ProgrammingDate[3]);
#endif
}
