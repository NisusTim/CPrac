/*
 * lib_version.c
 *
 *  Created on: 2020/01/22
 *      Author: Jack Lee
 */

/*******************************************************************************
*   Local Data Define
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "LibVer.h"

static LIBS_VER_P LibVersion[LIB_VER_INVAILD] = {NULL};
const char RevBuild[] = {'a','b','r', 'x'};

/*******************************************************************************
*	Local Function Declaration
*******************************************************************************/
void lib_ver_init(void);
LIBS_VER_P get_lib_ver(LIB_VERSION_E);
void dump_lib_ver(LIB_VERSION_E index, char* ver32b);

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: lib_ver_init
* Description:   library version initialization.
* Inputs:        None
* Outputs:       None
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
void lib_ver_init(void)
{
	LIBS_VER_P temp_lib_ver = NULL;

	memset(LibVersion, NULL, sizeof(LibVersion));

	temp_lib_ver = (LIBS_VER_P)Z4_LIB_VER_START_ADDR;     //find Z4 library version
	while((uint8_t*)temp_lib_ver < ((uint8_t*)Z4_LIB_VER_START_ADDR + SIZEOF_LIB_VER_SECTIONS) && temp_lib_ver->id < LIB_VER_INVAILD){
		LibVersion[temp_lib_ver->id] = temp_lib_ver;
		temp_lib_ver++;
	}

	temp_lib_ver = (LIBS_VER_P)Z70_LIB_VER_START_ADDR;    //find Z70 library version
	while((uint8_t*)temp_lib_ver < ((uint8_t*)Z70_LIB_VER_START_ADDR + SIZEOF_LIB_VER_SECTIONS) && temp_lib_ver->id < LIB_VER_INVAILD){
		LibVersion[temp_lib_ver->id] = temp_lib_ver;
		temp_lib_ver++;
	}

	temp_lib_ver = (LIBS_VER_P)Z71_LIB_VER_START_ADDR;    //find Z71 library version
	while((uint8_t*)temp_lib_ver < ((uint8_t*)Z71_LIB_VER_START_ADDR + SIZEOF_LIB_VER_SECTIONS) && temp_lib_ver->id < LIB_VER_INVAILD){
		LibVersion[temp_lib_ver->id] = temp_lib_ver;
		temp_lib_ver++;
	}
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: lib_ver_get
* Description:   get library version.
* Inputs:        LIB_VERSION_E
* Outputs:       LIBS_VER_P
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
LIBS_VER_P get_lib_ver(LIB_VERSION_E index)
{
	if(index < LIB_VER_INVAILD)
	return LibVersion[(uint8_t)index];
	else
		return NULL;
}

/* BEGIN_FUNCTION_HDR
********************************************************************************
* Function Name: dump_lib_ver
* Description:   dump library version.
* Inputs:        LIB_VERSION_E, char*
* Outputs:       None
* Limitations:   None
********************************************************************************
END_FUNCTION_HDR*/
void dump_lib_ver(LIB_VERSION_E index, char* ver32b)
{
	if(index < LIB_VER_INVAILD){
		if(LibVersion[index] != NULL){
			sprintf(ver32b, "V%u.%u.%c%u",
					LibVersion[index]->major,
					LibVersion[index]->minor,
					RevBuild[LibVersion[index]->build],
					LibVersion[index]->maintenance);
		}
		else{
			sprintf(ver32b, "NULL\n");
		}
	}
}
