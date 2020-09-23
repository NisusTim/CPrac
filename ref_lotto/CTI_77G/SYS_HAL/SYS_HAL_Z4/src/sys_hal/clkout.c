/*
 * clkout.c
 *
 *  Created on: 2018¦~10¤ë12¤é
 *      Author: user
 */


#include "sys_shared.h"


void clkout_init(void)
{

	MCB.CLKOUT_SEL.B.CLKOUT0 = 0;//Source 16MHz
	CGM.AC14_DC0.B.DE = 1;//Enable divider
	CGM.AC14_DC0.B.DIV = 5;//16MHz / 6 = 2.66...MHz
}


