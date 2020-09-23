/*
 * monitor_debug.h
 *
 *  Created on: 2019/3/28
 *      Author: WoodLiu
 */

#ifndef MONITOR_MONITOR_DEBUG_H_
#define MONITOR_MONITOR_DEBUG_H_

#include "console.h"

#define MONITOR_DBG				ENABLE

#if (MONITOR_DBG == ENABLE)
#define MONITOR_PRINTF(...) 	PRINTF(__VA_ARGS__)
#else
#define MONITOR_PRINTF(...)		do { } while(0)
#endif

#if (MONITOR_DBG == ENABLE)
void monitor_debug_init();
#endif

#endif /* MONITOR_MONITOR_DEBUG_H_ */
