#include "can_format.h"
/*
 * can_format.c
 *
 *  Created on: 2018年8月22日
 *      Author: WoodLiu
 */

//====================================================================================
//Transfer Format
uint64_t intel_to_motorola(uint64_t data)
{
	INTEL_FROMAT intel;
	MOTOROLA_FROMAT motorola;
	intel.R = data;
	motorola.B.bit7to0 = intel.B.bit7to0;
	motorola.B.bit15to8 = intel.B.bit15to8;
	motorola.B.bit23to16 = intel.B.bit23to16;
	motorola.B.bit31to24 = intel.B.bit31to24;
	motorola.B.bit39to32 = intel.B.bit39to32;
	motorola.B.bit47to40 = intel.B.bit47to40;
	motorola.B.bit55to48 = intel.B.bit55to48;
	motorola.B.bit63to56 = intel.B.bit63to56;
	return motorola.R;
}

uint64_t motorola_to_intel(uint64_t data)
{
	INTEL_FROMAT intel;
	MOTOROLA_FROMAT motorola;
	motorola.R = data;
	intel.B.bit7to0 = motorola.B.bit7to0;
	intel.B.bit15to8 = motorola.B.bit15to8;
	intel.B.bit23to16 = motorola.B.bit23to16;
	intel.B.bit31to24 = motorola.B.bit31to24;
	intel.B.bit39to32 = motorola.B.bit39to32;
	intel.B.bit47to40 = motorola.B.bit47to40;
	intel.B.bit55to48 = motorola.B.bit55to48;
	intel.B.bit63to56 = motorola.B.bit63to56;
	return intel.R;
}
//====================================================================================


