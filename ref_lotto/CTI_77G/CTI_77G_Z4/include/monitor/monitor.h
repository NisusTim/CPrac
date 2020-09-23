/*
 * monitor.h
 *
 *  Created on: 2018/8/3
 *      Author: WoodLiu
 */

#ifndef MONITOR_MONITOR_H_
#define MONITOR_MONITOR_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "S32R274.h" /* include peripheral declarations */
#include "compiler_api.h"

#define MAX_MONITOR_TASK_NUM 	20
#define MAX_MONITOR_GROUP 		5

#define PROC_MAX_1_MS	(060000U)		//@timer clock = 60Mhz
#define PROC_MAX_2_MS	(120000U)
#define PROC_MAX_4_MS	(240000U)
#define PROC_MAX_5_MS	(300000U)
#define PROC_MAX_10_MS	(600000U)

#define PROC_PERIOD_750_MS_TICKS	(PROC_PERIOD_500_MS_TICKS + PROC_PERIOD_200_MS_TICKS)

#define DEFAULT_MONITOR_PASSED_CNT	(-10)
#define DEFAULT_MONITOR_FAILED_CNT	(10)
#define	MONITOR_OK_CNT				(0)

#define DEFAULT_MONITOR_VALUE		(0)
#define MONITOR_RES_PASSED			(0)
#define MONITOR_RES_FAILED			(1)

typedef enum
{
	NONE_TIMER,
	INTERNAL_TIMER,
	EXTERNAL_TIMER
}timer_type;

typedef enum
{
	MONITOR_STATE_INIT,
	MONITOR_STATE_START,
	MONITOR_STATE_PROC,
	MONITOR_STATE_RES_HND,
	MONITOR_STATE_STOP
}monitor_state;

typedef enum
{
	MONITOR_TYPE_ACTIVE_PROCESS,
	MONITOR_TYPE_PASSIVE_PROCESS,
	MONITOR_TYPE_PEEK_PROCESS
}monitor_type;

typedef enum
{
	MONITOR_RESULT_FAILED,				//Failed
	MONITOR_RESULT_PRE_FAILED,			//PreFailed
	MONITOR_RESULT_OK,					//OK
	MONITOR_RESULT_PRE_PASSED,			//PrePassed
	MONITOR_RESULT_PASSED,				//Passed
}monitor_result_e;

typedef enum
{
	MONITOR_RESULT_CODE_PASSED,
	MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE,
	MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE,
	MONITOR_RESULT_CODE_ERROR,
	MONITOR_RESULT_CODE_NONE
}monitor_res_code_e;

typedef float (* monitor_proc_p) (void);
typedef void (* monitor_res_hnd_p) (monitor_res_code_e result);

typedef struct
{
	//The process id
	uint8_t				id;

	//The process id
	const char* 		name;

	//Monitor type of process
	monitor_type		type;

	//The group number of this process
	uint8_t				proc_group_num;

	//The process function pointer, can't be null
	monitor_proc_p 		proc;

	//The process result callback function, nullable
	monitor_res_hnd_p 	result_handler;

	//The return value of monitoring process
	float				value;

	//The maximum standard of testing
	float				max_value;

	//The minimum standard of testing
	float				min_value;

	//Fault detection counter : -128~128
	int8_t				cnt;

	//Passed const value, negative number
	int8_t 				passed_cnt;

	//Failed const value, positive number
	int8_t 				failed_cnt;

	//The time required to execute this process
	uint32_t			proc_time;

	//Monitoring result
	monitor_result_e	result;

	//Monitoring result code
	monitor_res_code_e	res_code;

}monitor_t, *monitor_p;

#endif /* SYS_HAL_MONITOR_H_ */
