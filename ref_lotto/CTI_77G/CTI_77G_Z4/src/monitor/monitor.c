/*
 * monitor.c
 *
 *  Created on: 2018�~5��16��
 *      Author: erichu
 */
#include "monitor.h"
#include "monitor_task.h"
#include "monitor_debug.h"
#include "timer.h"
#include "sbc_fs8x.h"

#define MONITOR_RECORD_VALUE_UPDATE		0xA5A5AA5513572468

/*typedef struct {
	uint64_t		update;

}monitor_record_t, *monitor_record_p;

monitor_record_t		__attribute__ ((section(".monitor"))) monitor_record;
*/

static void _task_init(uint8_t i);
static uint8_t _monitor_add_task(monitor_type type,
							monitor_id_e id,
							monitor_proc_p proc,
							monitor_res_hnd_p res_hnd,
							const float max_value,
							const float min_value,
							const int8_t passed_cnt,
							const int8_t failed_cnt);

static uint8_t _monitor_change_boundary_by_id(monitor_id_e id,
                        const float max_value,
                        const float min_value,
                        const int8_t passed_cnt,
                        const int8_t failed_cnt);

static void _monitor_fault_detection(monitor_p monitor);
static void _dispatch_task_order();

static const char* monitor_proc_name[] = {
        "VOL_POWER_SUPPLEY",    //0
        "VOL_MCU",              //1
        "VOL_RF_IC_1",          //2
        "VOL_RF_IC_2",          //3
        "TEMP_MCU",             //4
        "TEMP_RF_IC",           //5
        "TEMP_PM_IC",           //6
        "MCLK",                 //7
        "VCO",                  //8
        "MEMORY",               //9
        "FCCU",                 //10
        "RF_ISM",               //11
        "STACK",                //12
        "BLOCKAGE"              //13
};

static timer_type _timer_type = NONE_TIMER;
static monitor_tasks_t _monitor_task;

static timer_p _moniter_timer = NULL;
static monitor_state _monitor_state = MONITOR_STATE_INIT;
static monitor_mode_fsm_proc_p monitor_fsm_proc = NULL;

static void _task_init(uint8_t i)
{
	_monitor_task.que[i].id 			= MONITOR_ID_INVALID;
	_monitor_task.que[i].name			= "invalid";
	_monitor_task.que[i].type			= MONITOR_TYPE_ACTIVE_PROCESS;
	_monitor_task.que[i].proc_group_num = 0;
	_monitor_task.que[i].proc 			= NULL;
	_monitor_task.que[i].result_handler = NULL;
	_monitor_task.que[i].value 			= 0;
	_monitor_task.que[i].max_value 		= 0;
	_monitor_task.que[i].min_value 		= 0;
	_monitor_task.que[i].cnt 			= MONITOR_OK_CNT;
	_monitor_task.que[i].passed_cnt 	= DEFAULT_MONITOR_PASSED_CNT;
	_monitor_task.que[i].failed_cnt 	= DEFAULT_MONITOR_FAILED_CNT;
	_monitor_task.que[i].proc_time 		= 0;
	_monitor_task.que[i].result 		= MONITOR_RESULT_OK;
	_monitor_task.que[i].res_code 		= MONITOR_RESULT_CODE_PASSED;
}

static uint8_t _monitor_add_task(	monitor_type type,
						monitor_id_e id,
						monitor_proc_p proc,
						monitor_res_hnd_p res_hnd,
						const float max_value,
						const float min_value,
						const int8_t passed_cnt,
						const int8_t failed_cnt)
{
	uint32_t elapsed = 0;

	if(MONITOR_STATE_INIT == _monitor_state || MONITOR_STATE_STOP == _monitor_state)
	{
		if(MONITOR_ID_INVALID > id && _monitor_task.tasks_count < MAX_MONITOR_TASK_NUM)
		{
			if(MONITOR_TYPE_ACTIVE_PROCESS == type || MONITOR_TYPE_PEEK_PROCESS == type )
			{
				if(NULL != proc)
				{
					//Calculate monitoring function processing time
					elapsed = STM_0.CNT.R;
					proc();
					elapsed = STM_0.CNT.R - elapsed;
				}
				else
				{
					return FALSE;
				}
			}

			//Enqueue monitor process
			_monitor_task.que[id].id 				= id;
			_monitor_task.que[id].name				= monitor_proc_name[id];
			_monitor_task.que[id].type				= type;
			_monitor_task.que[id].proc 				= proc;
			_monitor_task.que[id].result_handler	= res_hnd;
			_monitor_task.que[id].max_value 		= max_value;
			_monitor_task.que[id].min_value 		= min_value;
			_monitor_task.que[id].passed_cnt 		= passed_cnt;
			_monitor_task.que[id].failed_cnt 		= failed_cnt;
			_monitor_task.que[id].proc_time 		= elapsed;

			_monitor_task.tasks_count = _monitor_task.tasks_count + 1;

			return TRUE;
		}
	}

	return FALSE;
}

static uint8_t _monitor_change_boundary_by_id(monitor_id_e id,
                        const float max_value,
                        const float min_value,
                        const int8_t passed_cnt,
                        const int8_t failed_cnt)
{
    if(MONITOR_ID_INVALID > id && _monitor_task.tasks_count < MAX_MONITOR_TASK_NUM)
    {
        _monitor_task.que[id].id                = id;
        _monitor_task.que[id].max_value         = max_value;
        _monitor_task.que[id].min_value         = min_value;
        _monitor_task.que[id].passed_cnt        = passed_cnt;
        _monitor_task.que[id].failed_cnt        = failed_cnt;

        return TRUE;
    }

    return FALSE;
}

static void _monitor_fault_detection(monitor_p monitor)
{
	if(NULL == monitor)
		return;

	//Check value passed or failed
	if(monitor->max_value < monitor->value)
	{//Failed: Beyond max value
		monitor->res_code = MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE;

		if(monitor->cnt < MONITOR_OK_CNT)
			monitor->cnt = 1;
		else if(monitor->cnt < monitor->failed_cnt)
			monitor->cnt++;
		else
			monitor->cnt = monitor->failed_cnt;
	}
	else if(monitor->min_value > monitor->value)
	{//Failed: Below min value
		monitor->res_code = MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE;

		if(monitor->cnt < MONITOR_OK_CNT)
			monitor->cnt = 1;
		else if(monitor->cnt < monitor->failed_cnt)
			monitor->cnt++;
		else
			monitor->cnt = monitor->failed_cnt;
	}
	else
	{//Passed
		monitor->res_code = MONITOR_RESULT_CODE_PASSED;

		if(monitor->cnt > monitor->passed_cnt)
			monitor->cnt--;
		else
			monitor->cnt = monitor->passed_cnt;
	}

	//Check result passed or failed
	if(monitor->cnt == monitor->failed_cnt)
	{
		monitor->result = MONITOR_RESULT_FAILED;
	}
	else if(0 < monitor->cnt && monitor->cnt < monitor->failed_cnt)
	{
		monitor->result = MONITOR_RESULT_PRE_FAILED;
	}
	else if(monitor->cnt == MONITOR_OK_CNT)
	{
		monitor->result = MONITOR_RESULT_OK;
	}
	else if(monitor->passed_cnt < monitor->cnt && monitor->cnt < 0 )
	{
		monitor->result = MONITOR_RESULT_PRE_PASSED;
	}
	else
	{
		monitor->result = MONITOR_RESULT_PASSED;
	}
}

static void _dispatch_task_order()
{//Based on Algo: Knapsack Problem

	//Need to dispatch group count
	_monitor_task.proc_groups_count	= 1;
}

void monitor_task_init(timer_type timer_type, uint32_t limit_time)
{
	uint8_t i = 0;

	_timer_type = timer_type;

	_monitor_task.tasks_count 		= 0;
	_monitor_task.proc_groups_count	= 0;

	for(i = 0 ; i < MAX_MONITOR_TASK_NUM ; i++)
	{
		_task_init(i);
	}

	_monitor_task.proc_limit_time = limit_time;
	_moniter_timer = NULL;

	_monitor_state = MONITOR_STATE_INIT;

#if (MONITOR_DBG == ENABLE)
	monitor_debug_init(&_monitor_task);
#endif
}

void monitor_set_fsm(monitor_mode_fsm_proc_p proc)
{
    monitor_fsm_proc = proc;
}


void external_power_check(external_voltage_fault_hander_p handler)
{
	float battery_voltage;
	uint8_t voltage_tolronce = 20;

	//safety check: battery voltage
	battery_voltage = 0;

	for(int i = 0 ; i < 10 ; i++)
	{
        battery_voltage += get_power_supply_voltage();
	}

	battery_voltage /= 10.0;

	if(17.0 < battery_voltage || 9.4 > battery_voltage)
	{	//Voltage Hazard
		//Verify

		while( (17.0 < battery_voltage || 9.4 > battery_voltage) && voltage_tolronce > 0)
		{
			//safety check: battery voltage
			battery_voltage = 0;

			for(int i = 0 ; i < 10 ; i++)
			{
				battery_voltage += get_power_supply_voltage();
			}

			battery_voltage /= 10.0;
			voltage_tolronce--;
		}

		if(voltage_tolronce == 0)
	    {    //Voltage Hazard
			if(NULL != handler)
			{
				handler();
			}
		}
	}
}

uint8_t monitor_add_active_task(	monitor_id_e id,
								monitor_proc_p proc,
								monitor_res_hnd_p res_hnd,
								const float max_value,
								const float min_value,
								const int8_t passed_cnt,
								const int8_t failed_cnt)
{
	return _monitor_add_task(MONITOR_TYPE_ACTIVE_PROCESS, id, proc, res_hnd, max_value, min_value, passed_cnt, failed_cnt);
}

uint8_t monitor_add_passive_task(	monitor_id_e id,
								monitor_res_hnd_p res_hnd,
								const float max_value,
								const float min_value,
								const int8_t passed_cnt,
								const int8_t failed_cnt)
{
	return _monitor_add_task(MONITOR_TYPE_PASSIVE_PROCESS, id, NULL, res_hnd, max_value, min_value, passed_cnt, failed_cnt);
}

uint8_t monitor_change_task_boundary(    monitor_id_e id,
                                const float max_value,
                                const float min_value,
                                const int8_t passed_cnt,
                                const int8_t failed_cnt)
{
    return _monitor_change_boundary_by_id(id, max_value, min_value, passed_cnt, failed_cnt);
}

uint8_t monitor_add_peek_task(	monitor_id_e id,
							monitor_proc_p proc,
							monitor_res_hnd_p res_hnd,
							const float max_value,
							const float min_value,
							const int8_t passed_cnt,
							const int8_t failed_cnt)
{
	return _monitor_add_task(MONITOR_TYPE_PEEK_PROCESS, id, proc, res_hnd, max_value, min_value, passed_cnt, failed_cnt);
}

uint8_t monitor_delete_task(monitor_id_e id)
{
	if(MONITOR_STATE_STOP == _monitor_state || MONITOR_STATE_INIT == _monitor_state)
	{
		if(MONITOR_ID_INVALID > id)
		{
			_task_init(id);
			_monitor_task.tasks_count = _monitor_task.tasks_count - 1;
			return TRUE;
		}
	}

	return FALSE;
}

uint8_t monitor_start(int16_t ticks)
{
	//Dispatch process task
	_dispatch_task_order();

	//monitor_worker start
	_monitor_state = MONITOR_STATE_START;

	if(INTERNAL_TIMER == _timer_type)
	{
		if(TIMER_50_MS_TICKS <= ticks)
		    _moniter_timer = timer_set("monitor", ticks, -1, monitor_worker, NULL);
		else
		    return FALSE;
	}
	return TRUE;
}

uint8_t monitor_stop()
{
	_monitor_state = MONITOR_STATE_STOP;

	if(NULL != _moniter_timer)
	{
		if (!strcmp("monitor", _moniter_timer->name))
			timer_unset(&_moniter_timer);
		_moniter_timer = NULL;

		if(NULL != _moniter_timer)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void monitor_worker()
{
	uint8_t i = 0;
	static uint8_t group_num = 0;
	uint32_t elapsed = STM_0.CNT.R;


	if(MONITOR_STATE_START == _monitor_state)
	{
		_monitor_state = MONITOR_STATE_PROC;
	}

	if(MONITOR_STATE_PROC == _monitor_state)
	{
		for(i = 0 ; i < MAX_MONITOR_TASK_NUM ; i++)
		{
			if(MONITOR_ID_INVALID > _monitor_task.que[i].id)
			{
				if(_monitor_task.que[i].proc_group_num == (group_num % _monitor_task.proc_groups_count))
				{
					if(_monitor_task.que[i].proc != NULL &&
							_monitor_task.que[i].type != MONITOR_TYPE_PASSIVE_PROCESS)
					{
						//Monitoring process
						//Active, Peek process
						_monitor_task.que[i].value = _monitor_task.que[i].proc();

						if(MONITOR_TYPE_ACTIVE_PROCESS == _monitor_task.que[i].type)
						{
							//Fault detection process
							_monitor_fault_detection(&_monitor_task.que[i]);
						}
					}
				}
			}
		}
		_monitor_state = MONITOR_STATE_RES_HND;
	}
	else if(MONITOR_STATE_RES_HND == _monitor_state)
	{
		for(i = 0 ; i < MAX_MONITOR_TASK_NUM ; i++)
		{
			if(MONITOR_ID_INVALID > _monitor_task.que[i].id)
			{
				if(_monitor_task.que[i].proc_group_num == (group_num % _monitor_task.proc_groups_count))
				{
					if(MONITOR_TYPE_ACTIVE_PROCESS == _monitor_task.que[i].type)
					{//type active
						if(_monitor_task.que[i].result_handler != NULL)
						{
							//Execution handler
							if(MONITOR_RESULT_FAILED == _monitor_task.que[i].result ||
									MONITOR_RESULT_PASSED == _monitor_task.que[i].result)
							{
								//The callback function is called only if the confirmation result is a pass or a failure.
								_monitor_task.que[i].result_handler(_monitor_task.que[i].res_code);
							}
							else
							{
								//Not sure for result
							}
						}
					}
					else
					{	//type passive or peek
						_monitor_task.que[i].result_handler(_monitor_task.que[i].res_code);
					}
				}
			}
		}

		//monitor mode FSM
		monitor_fsm_proc();

		if(MAX_MONITOR_GROUP == group_num)
		{
			group_num = 0;
		}
		else
		{
			group_num++;
		}

		_monitor_state = MONITOR_STATE_PROC;
	}
	else
	{
		//MONITOR_STATE_INIT
		//MONITOR_STATE_STOP
	}

	elapsed = STM_0.CNT.R - elapsed;
//	PRINTF("[monitor worker elapsed]: %.2f\n", elapsed * 16.7f/1000000.0f);
}



void set_monitoring_value_by_id(monitor_id_e id, float value)
{
	if(MONITOR_ID_INVALID > _monitor_task.que[id].id)
	{
		_monitor_task.que[id].value = value;

		_monitor_fault_detection(&_monitor_task.que[id]);
	}
}

float get_monitoring_value_by_id(monitor_id_e id)
{
	float rtvl = 0;

	if(MONITOR_ID_INVALID > _monitor_task.que[id].id)
	{
		rtvl = _monitor_task.que[id].value;
	}

	return rtvl;
}

void set_monitoring_result_by_id(monitor_id_e id, monitor_result_e result, monitor_res_code_e result_code)
{
	if(MONITOR_ID_INVALID > _monitor_task.que[id].id)
	{
		_monitor_task.que[id].result = result;
		_monitor_task.que[id].res_code = result_code;
	}
}

monitor_result_e get_monitoring_result_by_id(monitor_id_e id)
{
	monitor_result_e result = MONITOR_RESULT_OK;

	if(MONITOR_ID_INVALID > _monitor_task.que[id].id)
	{
		result = _monitor_task.que[id].result;
	}

	return result;
}



monitor_result_e get_monitoring_result()
{
	monitor_result_e result = MONITOR_RESULT_PASSED;
	uint8_t i = 0;

	for(i = 0 ; (i < MAX_MONITOR_TASK_NUM); i++)
	{
		if(MONITOR_ID_INVALID > _monitor_task.que[i].id)
		{
			if(MONITOR_TYPE_ACTIVE_PROCESS == _monitor_task.que[i].type ||
					MONITOR_TYPE_PASSIVE_PROCESS == _monitor_task.que[i].type)
			{	//type active or passive
				if(_monitor_task.que[i].result < result)
				{
					result = _monitor_task.que[i].result;
				}
			}
			else
			{
				//type peek
				//Overall result don't take the peek task result into account
			}
		}
	}

	return result;
}


