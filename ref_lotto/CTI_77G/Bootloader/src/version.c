/*
 * version.c
 *
 *  Created on: 2019¦~10¤ë16¤é
 *      Author: WoodLiu
 */

#include <stdio.h>
#include "version.h"
#include "image.h"
#include "string.h"

char bl_number[LENGTH_OF_BL_VERSION+1] = {'\0'};
char bl_version_number[LENGTH_OF_BL_VERSION+1] = {'\0'};

void version_init()
{
	strcpy((char*)&bl_number[0], DEFAULT_BL_NUMBER);
	sprintf((char*)bl_version_number, "%s%s%s", PROJECT_CODE, CUSTOMER_CODE, DEFAULT_BL_NUMBER);
}

char* get_bl_number()
{
	return bl_number;
}

char* get_bl_version()
{
    return bl_version_number;
}

const bl_revision_p get_bl_revision()
{
	return &(((bl_image_header_p)(IMGE_ADDR_BLDR))->rev);
}
