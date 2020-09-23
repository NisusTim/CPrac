/*
 * fbl_spec.c
 * Flash bootloader specification
 *  Created on: 2019¦~10¤ë15¤é
 *      Author: WoodLiu
 */

#include <stdio.h>
#include <string.h>

#include "fbl_spec.h"
#include "version.h"
#include "console.h"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define PARS_FBL_VERSION_MAJOR 		0x02
#define PARS_FBL_VERSION_MINOR 		0x00
#define VERSION_OF_FBL_PARS    		(((bl_u16_t)PARS_FBL_VERSION_MAJOR<<8) | PARS_FBL_VERSION_MINOR)

#define FLAG_REPROGRAM_DATA     	(0xA5A5A5A5UL)

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void bl_pars_dump(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
bl_parameters_t bl_parameters = {
		.hdr = {
			.base = (bl_u32_t)&bl_parameters,
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

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
void fbl_spec_init()
{
	char* bl_version = get_bl_version();
	bl_revision_p rev = get_bl_revision();
	bl_u8_t is_changed = 0;

	pars_get((bl_pars_ctx_p)&bl_parameters, bl_pars_dump, NULL);

	version_init();

	if((bl_info_pars->rev_read_only.major != rev->major) ||
			(bl_info_pars->rev_read_only.product != rev->product) ||
			(bl_info_pars->rev_read_only.cusid != rev->cusid) ||
			(bl_info_pars->rev_read_only.minor != rev->minor) ||
			(bl_info_pars->rev_read_only.build != rev->build) ||
			(bl_info_pars->rev_read_only.maintenance != rev->maintenance) ||
			(bl_info_pars->rev_read_only.svn != rev->svn))
	{
		is_changed = 1;
		memcpy(&bl_info_pars->rev_read_only, rev, sizeof(bl_revision_t));
	}

	if(0 != strcmp(bl_info_pars->F180_BootloaderVersionNumber, bl_version))
	{
		is_changed = 1;
		strcpy(bl_info_pars->F180_BootloaderVersionNumber, bl_version);
	}

	if(is_changed)
	{
		pars_set((bl_pars_ctx_p)&bl_parameters);
	}
}

bl_Return_t set_F180_BootloaderVersionNumber(char* sn)
{
	bl_s8_t len = strlen(sn);

	if(len > LENGTH_OF_BL_VERSION)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	strcpy(bl_info_pars->F180_BootloaderVersionNumber, sn);

	pars_set((bl_pars_ctx_p)&bl_parameters);

	return BL_ERR_OK;
}

bl_Return_t set_F198_TesterSeriesNumber(char* sn)
{
	bl_s8_t len = strlen(sn);

	if(len > LENGTH_OF_TESTER_SN)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	if(0 != strcmp(bl_info_pars->F198_TesterSeriesNumber, sn))
	{
		strcpy(bl_info_pars->F198_TesterSeriesNumber, sn);
		pars_set((bl_pars_ctx_p)&bl_parameters);
	}

	return BL_ERR_OK;
}

bl_Return_t set_F199_ProgrammingDate(bl_u8_t* date, bl_u8_t len)
{
	bl_u8_t i;
	bl_u8_t is_changed = 0;
	if(len > LENGTH_OF_PROGRAMING_DATE)
	{
		return BL_ERR_BUFFER_OVERFLOW;
	}

	for(i = 0 ; i < len ; i++)
	{
		if(bl_info_pars->F199_ProgrammingDate[i] != date[i])
		{
			is_changed = 1;
			bl_info_pars->F199_ProgrammingDate[i] = date[i];
		}
	}

	if(1 == is_changed)
	{
		pars_set((bl_pars_ctx_p)&bl_parameters);
	}

	return BL_ERR_OK;
}

bl_u8_t* get_F180_BootloaderVersionNumber()
{
	return (bl_u8_t *)&bl_info_pars->F180_BootloaderVersionNumber[0];
}

bl_u8_t* get_F198_TesterSeriesNumber()
{
	return (bl_u8_t *)&bl_info_pars->F198_TesterSeriesNumber[0];
}

bl_u8_t* get_F199_ProgrammingDate()
{
	return (bl_u8_t *)&bl_info_pars->F199_ProgrammingDate[0];
}


bl_Return_t is_need_reprogram()
{
	if(FLAG_REPROGRAM_DATA == bl_info_pars->Reprogramming_flag)
	{
		return BL_ERR_OK;
	}
	else
	{
		return BL_ERR_NOT_OK;
	}
}

void clear_reprogram_flag()
{
	bl_info_pars->Reprogramming_flag = 0;
	pars_set((bl_pars_ctx_p)&bl_parameters);
}

static void bl_pars_dump(void)
{
#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("Flash Bootloader parameters:\n");
	PRINTF("- Tester series number (testersn): %s", bl_info_pars->F198_TesterSeriesNumber);
	PRINTF("- Programming Date (progdate): %.2x%.2x%.2x%.2x\n",
			bl_info_pars->F199_ProgrammingDate[0], bl_info_pars->F199_ProgrammingDate[1],
			bl_info_pars->F199_ProgrammingDate[2], bl_info_pars->F199_ProgrammingDate[3]);
#endif
}
