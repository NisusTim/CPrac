/*
 * shared_mem.h
 *
 *  Created on: 2017/02/21
 *      Author: erichu
 */

#ifndef SYS_SHARED_H_
#define SYS_SHARED_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "S32R274.h" /* include peripheral declarations */
#include "compiler_api.h"

//#define	DEBUG_PROC_IN_TIME
#define DEBUG_PROC

#include "customer.h"
#include "detections.h"

#ifdef CTI_Z4_0
	#include "event.h"
	#include "ioctrl.h"
	#include "frame.h"
	#include "SPI_TEF810X.h"
	#include "parameters.h"
	#include "semaphores.h"
	#include "product.h"
	#include "console.h"
	#include "console_cmd.h"
	#include "can_console.h"
	#include "console_api.h"
	#include "ENET.h"
	#include "netagent.h"
	#include "SWT.h"
	#include "tsens.h"
	#include "pass.h"
	#include "rmtp.h"
	#include "MIPI_CSI2.h"
	#include "TEF810x.h"
	#include "Utility.h"
	#include "can_id.h"
	#include "can_hal.h"
	#include "can_api.h"
	#include "timer.h"
	#include "flash.h"
	#include "tracking.h"
	#include "upgrade.h"
	#include "can_cmd.h"
	#include "DSPI.h"
	#include "FS65xx_driver.h"
	#include "TJA1145FD_Application_Specific_Functions.h"
	#include "monitor.h"
	#include "monitor_task.h"
	#include "vehicle.h"
	#include "sbc_fs8x.h"
	#include "I2C.h"
	#include "I2C_api.h"
	#include "ism330dlc.h"
	#include "ism330dlc_reg.h"
	#include "ism330dlc_i2c.h"
	#include "ism330dlc_reg_app.h"
	#include "clkout.h"
	#include "hw_ver.h"
	#include "coefs.h"
	#include "sys_hal.h"
#elif defined(CTI_Z7_0)
	#include "event.h"
	#include "timer.h"
	#include "semaphores.h"
	#include "parameters.h"
	#include "product.h"
	#include "upgrade.h"
	#include "can_hal.h"
	#include "can_api.h"
	#include "console.h"
	#include "console_cmd.h"
	#include "can_console.h"
	#include "console_api.h"
	#include "frame.h"
	#include "tracking.h"
	#include "SWT.h"
	#include "track_data.h"
	#include "vehicle.h"
	#include "sys_hal.h"
#elif defined(CTI_Z7_1)
	#include "event.h"
	#include "SWT.h"
	#include "timer.h"
	#include "semaphores.h"
	#include "upgrade.h"
	#include "parameters.h"
	#include "can_hal.h"
	#include "can_api.h"
	#include "console.h"
	#include "console_cmd.h"
	#include "can_console.h"
	#include "console_api.h"
	#include "frame.h"
	#include "product.h"
	#include "sys_hal.h"
#endif

#include "z47_ipc.h"

#if defined(CTI_Z4_0)
	#define Interrput_Core_Selected 0x8000
#elif defined(CTI_Z7_0)
	#define Interrput_Core_Selected 0x4000
#elif defined(CTI_Z7_1)
	#define Interrput_Core_Selected 0x2000
#endif

#ifdef CTI_Z4_0
	typedef enum {
		SYST_INIT = 0,
		SYST_READY,
		SYST_ACTIVE,
		SYST_PAUSED,
		SYST_DONE,
		SYST_INVALID,
	}sys_state_e;
	sys_state_e sys_state_get(void);
	void sys_state_set(sys_state_e);
	void sys_state_test(char** args, int count);
#endif

extern console_data_handle_t		console_data;


#endif /* SYS_SHARED_H_ */
