/*
 * controller.c
 *
 *  Created on: 2019/5/2
 *      Author: WoodLiu
 */

#include "typedefs.h"
#include "controller.h"

static uint8_t IsInited = FALSE;

void controller_init()
{
	if(IsInited == TRUE){
		return;
	}
	radar_input_controller_init();
	radar_output_controller_init();

	IsInited = TRUE;
}
