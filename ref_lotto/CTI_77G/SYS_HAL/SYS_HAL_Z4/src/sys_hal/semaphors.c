/*
 * semaphors.c
 *
 *  Created on: 2018¦~5¤ë22¤é
 *      Author: erichu
 */

#include "sys_shared.h"

/*******************************************************************************
Function Name : Reset semaphore Gate
*******************************************************************************/
uint8_t sem_gate_reset(uint8_t gate_no)
{
	uint8_t cnt = 0;

	SEMA42.RSTGT.W.R = (0xE2 << 8);

	while(SEMA42.RSTGT.R.B.RSTGSM != 0x01)
	{
		if(cnt++>10) return 1;
	}

	SEMA42.RSTGT.W.R = (0x1D<<8) | gate_no;

	return 0;
}

