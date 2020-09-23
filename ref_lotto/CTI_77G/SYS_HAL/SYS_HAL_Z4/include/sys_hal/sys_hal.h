/*
 * sys_hal.h
 *
 *  Created on: 2019/04/17
 *      Author: cubtek
 */

#ifndef SYS_HAL_H_
#define SYS_HAL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "typedefs.h"

typedef enum system_clock {
    CLOCK_IRC,
    CLOCK_XOSC,
    CLOCK_PLL0,
    CLOCK_SDPLL_DIV_2,
    CLOCK_PLL1
}system_clock_e;

#endif /* SYS_HAL_H_ */
