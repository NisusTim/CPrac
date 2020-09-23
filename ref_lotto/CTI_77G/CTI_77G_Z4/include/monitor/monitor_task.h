/*
 * monitor_task.h
 *
 *  Created on: 2019年3月28日
 *      Author: WoodLiu
 */

#ifndef MONITOR_MONITOR_TASK_H_
#define MONITOR_MONITOR_TASK_H_

typedef enum
{
	/*Voltage*/
	MONITOR_ID_VOLTAGE_POWER_SUPPLY,
	MONITOR_ID_VOLTAGE_MCU,
	MONITOR_ID_VOLTAGE_1_RF_IC,
	MONITOR_ID_VOLTAGE_2_RF_IC,

	/*Temperature*/
	MONITOR_ID_TEMPERATURE_MCU,
	MONITOR_ID_TEMPERATURE_RF_IC,
	MONITOR_ID_TEMPERATURE_PM_IC,

	/*System*/
	MONITOR_ID_MCLK,
	MONITOR_ID_VCO,
	MONITOR_ID_MEMORY,
	MONITOR_ID_IMU,
	MONITOR_ID_FCCU,
	MONITOR_ID_RF_ISM,
	MONITOR_ID_STACK,

	/*Signal*/
	MONITOR_ID_RADAR_BLOCKAGE,
	MONITOR_ID_RADAR_ALIGNMENT,
	MONITOR_ID_RADAR_MOUNT_POSITION_SHIFT,

	/*Invalid*/
	MONITOR_ID_INVALID = MAX_MONITOR_TASK_NUM
}monitor_id_e;

typedef struct
{
	//Monitor task queue
	monitor_t 	que[MAX_MONITOR_TASK_NUM];

	//Limit execution time, used to dispatch_task_order
	uint32_t	proc_limit_time;

	//Count of tasks
	uint8_t		tasks_count;

	//Count of groups
	uint8_t		proc_groups_count;

}monitor_tasks_t, *monitor_tasks_p;

typedef void (* external_voltage_fault_hander_p) (void);
typedef void (*monitor_mode_fsm_proc_p)();

void monitor_task_init(timer_type timer_tpye, uint32_t limit_time);
void monitor_set_fsm(monitor_mode_fsm_proc_p proc);
void external_power_check(external_voltage_fault_hander_p handler);

uint8_t monitor_add_active_task(monitor_id_e id, monitor_proc_p proc, monitor_res_hnd_p res_hnd, const float max_value, const float min_value, const int8_t passed_cnt, const int8_t failed_cnt);
uint8_t monitor_add_passive_task(monitor_id_e id, monitor_res_hnd_p res_hnd, const float max_value, const float min_value, const int8_t passed_cnt, const int8_t failed_cnt);
uint8_t monitor_change_task_boundary(monitor_id_e id, const float max_value, const float min_value, const int8_t passed_cnt, const int8_t failed_cnt);
uint8_t monitor_add_peek_task(monitor_id_e id, monitor_proc_p proc, monitor_res_hnd_p res_hnd, const float max_value, const float min_value, const int8_t passed_cnt, const int8_t failed_cnt);
uint8_t monitor_delete_task(monitor_id_e id);
void monitor_worker();
uint8_t monitor_start(int16_t ticks);
uint8_t monitor_stop();

monitor_result_e get_monitoring_result();


void set_monitoring_value_by_id(monitor_id_e id, float value);
float get_monitoring_value_by_id(monitor_id_e id);

void set_monitoring_result_by_id(monitor_id_e id, monitor_result_e result, monitor_res_code_e result_code);
monitor_result_e get_monitoring_result_by_id(monitor_id_e id);

#endif /* MONITOR_MONITOR_TASK_H_ */
