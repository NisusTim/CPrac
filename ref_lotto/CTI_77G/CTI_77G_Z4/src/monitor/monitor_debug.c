/*
 * monitor_debug.c
 *
 *  Created on: 2019/3/28
 *      Author: WoodLiu
 */
#include "sys_shared.h" 
#include "monitor_debug.h"
#include "monitor_task.h"
#include "cubtek_monitor_handler.h"

#if (MONITOR_DBG == ENABLE)
#include "console.h"

static void monitor_tester(char** args, int count);
static void monitor_watch_status();
static monitor_tasks_p _tasks;

#define MONITOR_SHOW_RESULT(RESULT, RESULT_ARRAY)			(RESULT <= MONITOR_RESULT_PASSED ? RESULT_ARRAY[RESULT] : "NULL")

void monitor_debug_init(monitor_tasks_p tasks)
{
	_tasks = tasks;
	console_command_reg("monitdbg", monitor_tester);
}

static void monitor_tester(char** args, int count)
{

	if(count > 1) {
		if(!strcmp(args[1], "watch")){
			monitor_watch_status();
		}
		else
		if(!strcmp(args[1], "add")){
		    monitor_stop();
//			monitor_add_peek_task(MONITOR_ID_TEMPERATURE_PM_IC, (monitor_proc_p)get_fs8x_tempature, (monitor_res_hnd_p)temperature_pmic_result_handler, 125, -40, -10, 10);
			monitor_start(TIMER_200_MS_TICKS);
		}
		else
		if(!strcmp(args[1], "del")){
		    monitor_stop();
			monitor_delete_task(MONITOR_ID_TEMPERATURE_PM_IC);
			monitor_start(TIMER_200_MS_TICKS);
		} 
		else
		if(!strcmp(args[1], "stop")){
		     monitor_stop();
		}  
		else
		if(!strcmp(args[1], "start")){
		    monitor_start(TIMER_200_MS_TICKS);
		}
	}
}

static void monitor_watch_status()
{
//	monitor_t monitor;
//	PRINTF("[Registered Task Watching...]\n");
//	PRINTF("================================\n");
//	for(int i = 0 ; i < MONITOR_ID_INVALID ; i++)
//	{
//		monitor = _tasks->que[i];
//		if(MONITOR_ID_INVALID > (monitor_id_e)monitor.id)
//		{
//			PRINTF("NAME: %s,\tResult: %s\n", monitor.name, MONITOR_SHOW_RESULT(monitor.result, monitor_result_name));
//		}
//	}
//	PRINTF("================================\n");
//	PRINTF("[Registered Task End]\n");
}
#endif

