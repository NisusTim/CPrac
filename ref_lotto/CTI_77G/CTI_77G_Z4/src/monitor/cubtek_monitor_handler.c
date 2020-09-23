/*
 * cubtek_monitor_handler.c
 *
 *  Created on: 2018/8/13
 *      Author: WoodLiu
 */

#include "sys_shared.h"
#include "monitor_task.h"
#include "monitor_debug.h"
#include "cubtek_monitor_handler.h"
#include "can_cubtek.h"

#include "Com.h"
#include "Dem.h"
#include "Dem_Lcfg.h"

#include "parameters.h"
#include "flash.h"

#include "TEF810x.h"

#define MONITOR_PARS_ID   FOURCC('m','n','t','r')
#define STR(x)          #x
#define MNTR_ID         STR(mntr)
#define ACTIVE_TASK_CNT (6U)

#define JSON_MONITOR_INFO_VERBOSE_LOG       "\t\t\"verbose_log\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_MONITOR_INFO_VOL_POWER_SUPPLY  "\t\t\"vol_power_supply\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MONITOR_INFO_VOL_MCU           "\t\t\"vol_mcu\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MONITOR_INFO_VOL_1_RFIC        "\t\t\"vol_1_rfic\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MONITOR_INFO_VOL_2_RFIC        "\t\t\"vol_2_rfic\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MONITOR_INFO_TEMP_MCU          "\t\t\"temp_mcu\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]},\n"
#define JSON_MONITOR_INFO_TEMP_RFIC         "\t\t\"temp_rfic\":{\"t\":\"f32\",\"o\":%d,\"v\":[%.2f,%.2f,%.2f,%.2f]}\n"

enum
{
    CONDITION_UP_BOUND = 0,
    CONDITION_LOW_BOUND,
    CONDITION_PASSED_CNT,
    CONDITION_FAILED_CNT,
    CONDITION_COUNT,
};

typedef enum
{
    MONITOR_MODE_ACTIVE,    //Normal
    MONITOR_MODE_DEV,       //Develop, go to develop mode while  rx RMTP command and console "MNTR dev" command, exit while radar reset
    MONITOR_MODE_ERROR,     //Common error
    MONITOR_MODE_FAILURE,   //Critical error
    MONITOR_MODE_FATAL,     //Fatal error
    MONITOR_MODE_SAFE       //Hazard error
}MONITOR_MODE_E;

typedef enum
{
    MONITOR_EV_NORMAL,
    MONITOR_EV_COMMON_ERROR,    //MCU temperature, RFIC temperature
    MONITOR_EV_CRITICAL_ERROR,  //Master clock, RFIC error
    MONITOR_EV_FATAL_ERROR,     //MCU error, Memory error
    MONITOR_EV_HAZARD_ERROR     //Power supply voltage, MCU voltage, RFIC voltage
}MONITOR_EVENT_E;

typedef struct {
    MONITOR_MODE_E  cur_state;
    MONITOR_EVENT_E event;
    MONITOR_MODE_E  next_state;
    void (*func)();
} monitor_state_t;

typedef struct {
    MONITOR_MODE_E  mode;
    MONITOR_EVENT_E event;
    union
    {
        uint32_t error_mask;
        struct
        {
            uint32_t is_mcu_temperature_too_high:1;
            uint32_t is_mcu_temperature_too_low:1;
            uint32_t is_rfic_temperature_too_high:1;
            uint32_t is_rfic_temperature_too_low:1;
            uint32_t is_master_clock_error:1;
            uint32_t is_mcu_error:1;
            uint32_t is_memory_error:1;
            uint32_t is_rf_sensor_fault:1;

            uint32_t is_power_supply_voltage_too_high:1;
            uint32_t is_power_supply_voltage_too_low:1;
            uint32_t is_mcu_voltage_too_high:1;
            uint32_t is_mcu_voltage_too_low:1;
            uint32_t is_rfic_voltage_too_high:1;
            uint32_t is_rfic_voltage_too_low:1;
            uint32_t is_rfic2_voltage_too_high:1;
            uint32_t is_rfic2_voltage_too_low:1;

            uint32_t is_missing_calibration:1;
            uint32_t rsvd:15;
        }error;
    };
}monitor_info_t;

typedef struct _MonitorTaskCondition {
    float condition[CONDITION_COUNT];   //0: task passed upper bound
                                        //1: task passed lower bound
                                        //2: task passed count threshold
                                        //3: task failed count threshold
}mntr_cond_t, *mntr_cond_p;

typedef struct _MonitorParameterInfo {
    uint8_t         verbose_log;                                //log in verbose mode
    uint8_t         ignore_mis_calib;                           //Ignore missing calib and tx target list
    uint8_t         padding[6];                                 //8-byte alignment padding
    mntr_cond_t     monitor_task_condition[ACTIVE_TASK_CNT];    //0: MONITOR_ID_VOLTAGE_POWER_SUPPLY
                                                                //1: MONITOR_ID_VOLTAGE_MCU
                                                                //2: MONITOR_ID_VOLTAGE_1_RF_IC
                                                                //3: MONITOR_ID_VOLTAGE_2_RF_IC
                                                                //4: MONITOR_ID_TEMPERATURE_MCU
                                                                //5: MONITOR_ID_TEMPERATURE_RF_IC
} mntr_param_info_t;

typedef struct _MonitorParameter {
    pars_header_t       hdr;
    mntr_param_info_t   info;
} mntr_param_t, *mntr_param_p;


static void update_monitor_event();
static void monitor_mode_transition();
static void enter_active_mode();    //Normal
static void enter_develop_mode();   //Develop, go to develop mode in force while reveice RMTP command or "mntr dev" console command,
                                    //         exit while radar reset
static void enter_error_mode();     //Common error
static void enter_failure_mode();   //Critical error
static void enter_fatal_mode();     //Fatal error
static void enter_safe_mode();      //Hazard error
static void stop_tx_can_message(void*);

static void voltage_power_supply_result_handler(monitor_res_code_e res);
static void voltage_mcu_result_handler(monitor_res_code_e res);
static void voltage_rf_ic_1_result_handler(monitor_res_code_e res);
static void voltage_rf_ic_2_result_handler(monitor_res_code_e res);

static void temperature_mcu_result_handler(monitor_res_code_e res);
static void temperature_rf_ic_result_handler(monitor_res_code_e res);
//Passive task
static void master_clock_result_handler(monitor_res_code_e res);
static void fccu_other_result_handler(monitor_res_code_e res);
static void fccu_memory_result_handler(monitor_res_code_e res);
static void imu_result_handler(monitor_res_code_e res);
static void rf_ism_result_handler(monitor_res_code_e res);
static void radar_block_result_handler(monitor_res_code_e res);
static void radar_missing_calibration_handler(monitor_res_code_e res);
static void radar_mount_position_shift_handler(monitor_res_code_e res);

//Peek task
//static void temperature_pmic_result_handler(monitor_res_code_e res);

static int monitor_info_in_jsons(char* ws);
static void monitor_dump(void);
static void show_all_task_condition();
static void show_single_task_condition(uint8_t id);
static void mntr_pars_tester(char** args, int count);

static monitor_state_t ms_transition[] = {
        //Develop
        { MONITOR_MODE_DEV,     MONITOR_EV_NORMAL,          MONITOR_MODE_DEV,       NULL},
        { MONITOR_MODE_DEV,     MONITOR_EV_COMMON_ERROR,    MONITOR_MODE_DEV,       NULL},
        { MONITOR_MODE_DEV,     MONITOR_EV_CRITICAL_ERROR,  MONITOR_MODE_DEV,       NULL},
        { MONITOR_MODE_DEV,     MONITOR_EV_FATAL_ERROR,     MONITOR_MODE_DEV,       NULL},
        { MONITOR_MODE_DEV,     MONITOR_EV_HAZARD_ERROR,    MONITOR_MODE_DEV,       NULL},

        //Active
        { MONITOR_MODE_ACTIVE,  MONITOR_EV_COMMON_ERROR,    MONITOR_MODE_ERROR,     enter_error_mode },
        { MONITOR_MODE_ACTIVE,  MONITOR_EV_CRITICAL_ERROR,  MONITOR_MODE_FAILURE,   enter_failure_mode },
        { MONITOR_MODE_ACTIVE,  MONITOR_EV_FATAL_ERROR,     MONITOR_MODE_FATAL,     enter_fatal_mode },
        { MONITOR_MODE_ACTIVE,  MONITOR_EV_HAZARD_ERROR,    MONITOR_MODE_SAFE,      enter_safe_mode },

        //Warning
        { MONITOR_MODE_ERROR,   MONITOR_EV_NORMAL,          MONITOR_MODE_ACTIVE,    enter_active_mode },
        { MONITOR_MODE_ERROR,   MONITOR_EV_CRITICAL_ERROR,  MONITOR_MODE_FAILURE,   enter_failure_mode },
        { MONITOR_MODE_ERROR,   MONITOR_EV_FATAL_ERROR,     MONITOR_MODE_FATAL,     enter_fatal_mode },
        { MONITOR_MODE_ERROR,   MONITOR_EV_HAZARD_ERROR,    MONITOR_MODE_SAFE,      enter_safe_mode },

        //Failure
        { MONITOR_MODE_FAILURE, MONITOR_EV_NORMAL,          MONITOR_MODE_ACTIVE,    enter_active_mode },
        { MONITOR_MODE_FAILURE, MONITOR_EV_COMMON_ERROR,    MONITOR_MODE_ERROR,     enter_error_mode },
        { MONITOR_MODE_FAILURE, MONITOR_EV_FATAL_ERROR,     MONITOR_MODE_FATAL,     enter_fatal_mode },
        { MONITOR_MODE_FAILURE, MONITOR_EV_HAZARD_ERROR,    MONITOR_MODE_SAFE,      enter_safe_mode },

        //Fatal
        { MONITOR_MODE_FATAL,   MONITOR_EV_NORMAL,          MONITOR_MODE_ACTIVE,    enter_active_mode },
        { MONITOR_MODE_FATAL,   MONITOR_EV_CRITICAL_ERROR,  MONITOR_MODE_FAILURE,   enter_failure_mode },
        { MONITOR_MODE_FATAL,   MONITOR_EV_COMMON_ERROR,    MONITOR_MODE_ERROR,     enter_error_mode },
        { MONITOR_MODE_FATAL,   MONITOR_EV_HAZARD_ERROR,    MONITOR_MODE_SAFE,      enter_safe_mode },

        //Safe
        { MONITOR_MODE_SAFE,    MONITOR_EV_NORMAL,          MONITOR_MODE_ACTIVE,    enter_active_mode },
        { MONITOR_MODE_SAFE,    MONITOR_EV_CRITICAL_ERROR,  MONITOR_MODE_FAILURE,   enter_failure_mode },
        { MONITOR_MODE_SAFE,    MONITOR_EV_COMMON_ERROR,    MONITOR_MODE_ERROR,     enter_error_mode },
        { MONITOR_MODE_SAFE,    MONITOR_EV_FATAL_ERROR,     MONITOR_MODE_FATAL,     enter_fatal_mode },
};

monitor_info_t monitor_info = {0};

static const mntr_param_t kDefaultParam = {
        .hdr = {
                .base = (uint32_t)&kDefaultParam,
                .version = 0x0101,
                .size = sizeof(mntr_param_t),
                .id = MONITOR_PARS_ID,
                .chksum = 0,
                .mask = 0
        },
        .info = {
                .verbose_log = TRUE,
                .ignore_mis_calib = FALSE,
                .padding = {0xFF},
                .monitor_task_condition =
                {
                        {{   /*task 0 MONITOR_ID_VOLTAGE_POWER_SUPPLY*/
                            /*upper bound*/
                            32.0,
                            /*lower bound*/
                            15.0,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                        {{   /*task 1 MONITOR_ID_VOLTAGE_MCU*/
                            /*upper bound*/
                            1.32,
                            /*lower bound*/
                            1.19,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                        {{   /*task 2 MONITOR_ID_VOLTAGE_1_RF_IC*/
                            /*upper bound*/
                            3.46,
                            /*lower bound*/
                            3.13,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                        {{   /*task 3 MONITOR_ID_VOLTAGE_2_RF_IC*/
                            /*upper bound*/
                            3.46,
                            /*lower bound*/
                            3.13,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                        {{   /*task 4 MONITOR_ID_TEMPERATURE_MCU*/
                            /*upper bound*/
                            125.0,
                            /*lower bound*/
                            -40.0,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                        {{   /*task 5 MONITOR_ID_TEMPERATURE_RF_IC*/
                            /*upper bound*/
                            125.0,
                            /*lower bound*/
                            -40.0,
                            /*passed count*/
                            -5.0,
                            /*failed count*/
                            5.0
                        }},
                }
        }
};

mntr_param_t mntr_pars_t;
mntr_param_p mntr_pars = &mntr_pars_t;
static uint8_t is_ps_voltage_updated = TRUE;
static uint8_t is_mcu_temper_updated = TRUE;

void cubtek_monitor_init(int16_t ticks)
{
    mntr_cond_p monitor = NULL;

    memcpy(mntr_pars, (void*)&kDefaultParam, sizeof(mntr_param_t));
    pars_get((pars_ctx_p)mntr_pars, monitor_dump, monitor_info_in_jsons);
    console_command_reg(MNTR_ID, mntr_pars_tester);

	monitor_task_init(INTERNAL_TIMER, PROC_MAX_10_MS);
	monitor_set_fsm(monitor_mode_transition);

	monitor_info.mode = MONITOR_MODE_ACTIVE;
	monitor_info.event = MONITOR_EV_NORMAL;
	monitor_info.error_mask = 0;

	monitor = (mntr_cond_p)&mntr_pars->info.monitor_task_condition;

	monitor_add_active_task(MONITOR_ID_VOLTAGE_POWER_SUPPLY, (monitor_proc_p)get_power_supply_voltage, (monitor_res_hnd_p)voltage_power_supply_result_handler,
	        monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_FAILED_CNT]);

	monitor_add_active_task(MONITOR_ID_VOLTAGE_MCU, (monitor_proc_p)get_fs8x_vbuck1, (monitor_res_hnd_p)voltage_mcu_result_handler,
	        monitor[MONITOR_ID_VOLTAGE_MCU].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_MCU].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_MCU].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_VOLTAGE_MCU].condition[CONDITION_FAILED_CNT]);

	//rf ic 1 voltage no support in this ES2 version, so use 4.1V rf supply voltage for temporarily
	monitor_add_active_task(MONITOR_ID_VOLTAGE_1_RF_IC, (monitor_proc_p)get_fs8x_vpre, (monitor_res_hnd_p)voltage_rf_ic_1_result_handler,
	        monitor[MONITOR_ID_VOLTAGE_1_RF_IC].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_1_RF_IC].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_1_RF_IC].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_VOLTAGE_1_RF_IC].condition[CONDITION_FAILED_CNT]);

	//rf ic 2 voltage no support in this ES2 version, so use 4.1V rf supply voltage for temporarily
	monitor_add_active_task(MONITOR_ID_VOLTAGE_2_RF_IC, (monitor_proc_p)get_fs8x_vpre, (monitor_res_hnd_p)voltage_rf_ic_2_result_handler,
	        monitor[MONITOR_ID_VOLTAGE_2_RF_IC].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_2_RF_IC].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_VOLTAGE_2_RF_IC].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_VOLTAGE_2_RF_IC].condition[CONDITION_FAILED_CNT]);

	monitor_add_active_task(MONITOR_ID_TEMPERATURE_MCU, (monitor_proc_p)get_mcu_temperature, (monitor_res_hnd_p)temperature_mcu_result_handler,
	        monitor[MONITOR_ID_TEMPERATURE_MCU].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_TEMPERATURE_MCU].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_TEMPERATURE_MCU].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_TEMPERATURE_MCU].condition[CONDITION_FAILED_CNT]);

	monitor_add_active_task(MONITOR_ID_TEMPERATURE_RF_IC, (monitor_proc_p)get_tef810x_temperature, (monitor_res_hnd_p)temperature_rf_ic_result_handler,
	        monitor[MONITOR_ID_TEMPERATURE_RF_IC].condition[CONDITION_UP_BOUND],
	        monitor[MONITOR_ID_TEMPERATURE_RF_IC].condition[CONDITION_LOW_BOUND],
	        monitor[MONITOR_ID_TEMPERATURE_RF_IC].condition[CONDITION_PASSED_CNT],
	        monitor[MONITOR_ID_TEMPERATURE_RF_IC].condition[CONDITION_FAILED_CNT]);

	monitor_add_passive_task(MONITOR_ID_MCLK, (monitor_res_hnd_p)master_clock_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -20, 1);
	monitor_add_passive_task(MONITOR_ID_MEMORY, (monitor_res_hnd_p)fccu_memory_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -20, 1);
	monitor_add_passive_task(MONITOR_ID_FCCU, (monitor_res_hnd_p)fccu_other_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -20, 1);
    monitor_add_passive_task(MONITOR_ID_IMU, (monitor_res_hnd_p)imu_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -1, 1);
    monitor_add_passive_task(MONITOR_ID_RF_ISM, (monitor_res_hnd_p)rf_ism_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -20, 1);
    monitor_add_passive_task(MONITOR_ID_RADAR_BLOCKAGE, (monitor_res_hnd_p)radar_block_result_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -1, 1);
    monitor_add_passive_task(MONITOR_ID_RADAR_ALIGNMENT, (monitor_res_hnd_p)radar_missing_calibration_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -1, 1);
    monitor_add_passive_task(MONITOR_ID_RADAR_MOUNT_POSITION_SHIFT, (monitor_res_hnd_p)radar_mount_position_shift_handler, DEFAULT_MONITOR_VALUE, DEFAULT_MONITOR_VALUE, -1, 1);

//	monitor_add_peek_task(MONITOR_ID_TEMPERATURE_PM_IC, (monitor_proc_p)get_fs8x_tempature, (monitor_res_hnd_p)temperature_pmic_result_handler, 125, -40, -5, 5);

	monitor_start(ticks);
}

static int monitor_info_in_jsons(char* ws)
{
    int cnt = 0;
    if(ws){
        cnt = sprintf(ws,"{\n");
        cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(MONITOR_PARS_ID>>24),(char)(MONITOR_PARS_ID>>16),(char)(MONITOR_PARS_ID>>8),(char)(MONITOR_PARS_ID));
        cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, mntr_pars_t.hdr.version);
        cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, mntr_pars_t.hdr.size - sizeof(pars_header_t));

        cnt += sprintf(ws+cnt,"\t\"info\":{\n");
        cnt += sprintf(ws+cnt,JSON_MONITOR_INFO_VERBOSE_LOG,offsetof(mntr_param_info_t, verbose_log), mntr_pars->info.verbose_log);
        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_VOL_POWER_SUPPLY,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_VOLTAGE_POWER_SUPPLY]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[3]);

        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_VOL_MCU,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_VOLTAGE_MCU]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_MCU].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_MCU].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_MCU].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_MCU].condition[3]);

        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_VOL_1_RFIC,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_VOLTAGE_1_RF_IC]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_1_RF_IC].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_1_RF_IC].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_1_RF_IC].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_1_RF_IC].condition[3]);

        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_VOL_2_RFIC,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_VOLTAGE_2_RF_IC]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_2_RF_IC].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_2_RF_IC].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_2_RF_IC].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_VOLTAGE_2_RF_IC].condition[3]);

        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_TEMP_MCU,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_TEMPERATURE_MCU]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_MCU].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_MCU].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_MCU].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_MCU].condition[3]);

        cnt += sprintf(ws+cnt, JSON_MONITOR_INFO_TEMP_RFIC,offsetof(mntr_param_info_t, monitor_task_condition[MONITOR_ID_TEMPERATURE_RF_IC]),
                mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_RF_IC].condition[0], mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_RF_IC].condition[1],
                mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_RF_IC].condition[2], mntr_pars->info.monitor_task_condition[MONITOR_ID_TEMPERATURE_RF_IC].condition[3]);

        cnt += sprintf(ws+cnt, "\t}\n}\n");
    }
    return cnt;
}

void monitor_show()
{
    if(TRUE == is_ps_voltage_updated && TRUE == is_mcu_temper_updated && TRUE == mntr_pars->info.verbose_log)
    {
        is_ps_voltage_updated = FALSE;
        is_mcu_temper_updated = FALSE;

        PRINTF("monitor: ps_vol=%.2f, mcu_temp=%.2f, rfic_temp=%.2f\n",
                get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_POWER_SUPPLY),
                get_monitoring_value_by_id(MONITOR_ID_TEMPERATURE_MCU),
                get_monitoring_value_by_id(MONITOR_ID_TEMPERATURE_RF_IC));
    }
}

static void monitor_dump(void)
{
    mntr_cond_p monitor = (mntr_cond_p)&mntr_pars->info.monitor_task_condition;

    static const char* mode_name[] = {
            "ACTIVE",       //0
            "DEVELOP",      //1
            "ERROR",        //2
            "FAILURE",      //3
            "FATAL",        //4
            "SAFE",         //5
    };

    static const char* event_name[] = {
            "NORMAL",           //0
            "COMMON_ERROR",     //1
            "CRITICAL_ERROR",   //2
            "FATAL_ERROR",      //3
            "HAZARD_ERROR",     //4
    };

    PRINTF(" \n");
    PRINTF("VOL_POWER_SUPPLEY: %.2f ~ %.2f\n", monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_LOW_BOUND]
                                             , monitor[MONITOR_ID_VOLTAGE_POWER_SUPPLY].condition[CONDITION_UP_BOUND]);
    PRINTF(" \n");

    PRINTF("mntr verbose: %d    ;enable show log or not\n", mntr_pars->info.verbose_log);
    PRINTF("mntr tx_flag: %d    ;Ignore missing calib and tx target list\n", mntr_pars->info.ignore_mis_calib);
    PRINTF("mntr id <id>        ;Show single monitor configuration\n");
    PRINTF("mntr dev            ;Set monitor go to develop mode in force\n");
    PRINTF("mntr show           ;Show all monitor configuration\n");
    PRINTF("mntr config <id> <up_bound> <low_bound> <passed_cnt> <failed_cnt>   ;monitor id configuration\n");

    PRINTF(" \n");
    PRINTF("mntr mode: %s\n", mode_name[monitor_info.mode]);
    PRINTF("mntr event: %s\n", event_name[monitor_info.event]);
    PRINTF(" \n");
}

static void show_all_task_condition()
{
    uint8_t i = 0;

    PRINTF("----Cubtek monitor condition table----\n");
    for(i = 0 ; i < ACTIVE_TASK_CNT ; i++)
    {
        PRINTF("-----------------------\n");
        show_single_task_condition(i);

        if(i == ACTIVE_TASK_CNT-1)
        {
            PRINTF("-----------------------\n");
        }
    }
}

static void show_single_task_condition(uint8_t id)
{
    static const char* task_name[] = {
            "VOL_POWER_SUPPLEY",    //0
            "VOL_MCU",              //1
            "VOL_RF_IC_1",          //2
            "VOL_RF_IC_2",          //3
            "TEMP_MCU",             //4
            "TEMP_RF_IC",           //5
    };

    mntr_cond_p monitor = (mntr_cond_p)&mntr_pars->info.monitor_task_condition;

    PRINTF("mntr id %d:\n", id);
    PRINTF("mntr name: %s\n", task_name[id]);
    PRINTF("mntr up_bound: %.2f\n", monitor[id].condition[CONDITION_UP_BOUND]);
    PRINTF("mntr low_bound: %.2f\n", monitor[id].condition[CONDITION_LOW_BOUND]);
    PRINTF("mntr passed_cnt: %.2f\n", monitor[id].condition[CONDITION_PASSED_CNT]);
    PRINTF("mntr failed_cnt: %.2f\n", monitor[id].condition[CONDITION_FAILED_CNT]);
}

static void mntr_pars_tester(char** args, int count)
{
    if(count > 1)
    {
        if(!strcmp(args[1], "show"))
        {
            show_all_task_condition();
        }
        else if(!strcmp(args[1], "dev"))
        {
            monitor_set_develop_mode();
        }
    }
    if(count > 2)
    {
        uint8_t id = 0;
        if(!strcmp(args[1], "id"))
        {
            id = strtoul(args[2], NULL, 10);

            show_single_task_condition(id);
        }
        else if(!strcmp(args[1], "verbose"))
        {
            uint8_t enable = strtoul(args[2], NULL, 10);

            if(enable > 0)
                enable = TRUE;
            else
                enable = FALSE;

            mntr_pars->info.verbose_log = enable;
            pars_set((pars_ctx_t *)mntr_pars);
        }
        else if(!strcmp(args[1], "tx_flag"))
        {
            uint8_t op = strtoul(args[2], NULL, 10);

            if(op > 0)
                op = TRUE;
            else
                op = FALSE;

            mntr_pars->info.ignore_mis_calib = op;
            pars_set((pars_ctx_t *)mntr_pars);
        }
        else if(!strcmp(args[1], "config"))
        {
            mntr_cond_p monitor = (mntr_cond_p)&mntr_pars->info.monitor_task_condition;


            float up_bound = 0;
            float low_bound = 0;
            int8_t passed_cnt = 0;
            int8_t failed_cnt = 0;


            id = strtoul(args[2], NULL, 10);

            if(id >= 0 && id < ACTIVE_TASK_CNT)
            {
                if(count > 3)
                {
                    up_bound = strtof(args[3], NULL);
                    monitor[id].condition[CONDITION_UP_BOUND] = up_bound;
                }

                if(count > 4)
                {
                    low_bound = strtof(args[4], NULL);
                    monitor[id].condition[CONDITION_LOW_BOUND] = low_bound;
                }

                if(count > 5)
                {
                    passed_cnt = (int)strtof(args[5], NULL);
                    monitor[id].condition[CONDITION_PASSED_CNT] = passed_cnt;
                }

                if(count > 6)
                {
                    failed_cnt = (int)strtof(args[6], NULL);
                    monitor[id].condition[CONDITION_FAILED_CNT] = failed_cnt;
                }

                monitor_change_task_boundary(id,
                        monitor[id].condition[CONDITION_UP_BOUND],
                        monitor[id].condition[CONDITION_LOW_BOUND],
                        monitor[id].condition[CONDITION_PASSED_CNT],
                        monitor[id].condition[CONDITION_FAILED_CNT]);

                pars_set((pars_ctx_t *)mntr_pars);
                show_single_task_condition(id);
            }

        }
    }
    else
    {
        monitor_dump();
    }
}

void monitor_set_develop_mode()
{// Go to develop mode in force
    if(MONITOR_MODE_DEV == monitor_info.mode && FALSE == is_flash_on_safety())
        return;

    monitor_info.mode = MONITOR_MODE_DEV;

    enter_develop_mode();
}

static void update_monitor_event()
{
    if(monitor_info.error_mask == 0)
    {
        monitor_info.event = MONITOR_EV_NORMAL;
        PRINTF("[Monitor]Meet normal event \n");
    }
    else
    {
        if(monitor_info.error.is_mcu_temperature_too_high || monitor_info.error.is_mcu_temperature_too_low ||
                monitor_info.error.is_rfic_temperature_too_high || monitor_info.error.is_rfic_temperature_too_low ||
                monitor_info.error.is_missing_calibration)
        {
            monitor_info.event = MONITOR_EV_COMMON_ERROR;
            PRINTF("[Monitor]Meet common error event \n");
        }

        if(monitor_info.error.is_master_clock_error || monitor_info.error.is_rf_sensor_fault)
        {
            monitor_info.event = MONITOR_EV_CRITICAL_ERROR;
            PRINTF("[Monitor]Meet critical error event \n");
        }

        if(monitor_info.error.is_mcu_error || monitor_info.error.is_memory_error)
        {
            monitor_info.event = MONITOR_EV_FATAL_ERROR;
            PRINTF("[Monitor]Meet fatal error event \n");
        }

        if(monitor_info.error.is_power_supply_voltage_too_high || monitor_info.error.is_power_supply_voltage_too_low ||
                monitor_info.error.is_mcu_voltage_too_high || monitor_info.error.is_mcu_voltage_too_low ||
                monitor_info.error.is_rfic_voltage_too_high || monitor_info.error.is_rfic_voltage_too_low ||
                monitor_info.error.is_rfic2_voltage_too_high || monitor_info.error.is_rfic2_voltage_too_low)
        {
            monitor_info.event = MONITOR_EV_HAZARD_ERROR;
            PRINTF("[Monitor]Meet hazard error event \n");
        }
    }
}

static void monitor_mode_transition()
{
    // Iterate through the state transition matrix, checking if there is both a match with the current state.
    for(int i = 0; i < sizeof( ms_transition ) / sizeof( ms_transition[0] ); i++)
    {
        if( monitor_info.mode == ms_transition[i].cur_state )
        {
            if( monitor_info.event == ms_transition[i].event )
            {
                monitor_info.mode = ms_transition[i].next_state;
                if( ms_transition[i].func != NULL )
                {
                    ms_transition[i].func();
                }
                break;
            }
        }
    }
}

static void enter_active_mode()
{
    PRINTF("[Monitor]Enter active mode \n");
    flash_set_safety(FALSE);
    frame_resume();
    AppComTxRx_Start();
    target_list_trasmit_enable();
    set_target_list_tx_header_only(FALSE);
}

static void enter_develop_mode()
{
    PRINTF("[Monitor]Enter develop mode \n");

    flash_set_safety(FALSE);
}

static void enter_error_mode()
{
    //MCU temperature, RFIC temperature, Missing calibration
    PRINTF("[Monitor]Enter error mode \n");
    flash_set_safety(FALSE);
    frame_resume();
    AppComTxRx_Start();
    target_list_trasmit_enable();

    if(TRUE == monitor_info.error.is_missing_calibration && (FALSE == mntr_pars->info.ignore_mis_calib))
    {
        //Missing calibration is set and transmit target list header only
        set_target_list_tx_header_only(TRUE);   //Only transmit target list header
    }
    else
    {
        //MCU temperature, RFIC temperature
        set_target_list_tx_header_only(FALSE);  //Transmit target list header and data
    }
}

static void enter_failure_mode()
{
    //Master clock, RFIC error
    PRINTF("[Monitor]Enter failure mode \n");
    flash_set_safety(FALSE);
    frame_resume();
    AppComTxRx_Start();
    target_list_trasmit_enable();
    set_target_list_tx_header_only(TRUE);
}

static void enter_fatal_mode()
{
    //MCU error, Memory error
    PRINTF("[Monitor]Enter fatal mode \n");
    flash_set_safety(FALSE);
    frame_pause(NULL,NULL);
    AppComTxRx_Start();
}

static timer_p safe_mode_timer = NULL;
static void enter_safe_mode()
{
    //Power supply voltage, MCU voltage, RFIC voltage
    PRINTF("[Monitor]Enter safe mode \n");

    if(NULL == safe_mode_timer)
    {
        safe_mode_timer = timer_set("safe_mode", TIMER_100_MS_TICKS * 105, 1, stop_tx_can_message, NULL);
    }
    else
    {
        if (!strcmp("safe_mode", safe_mode_timer->name))
        {
            timer_unset(&safe_mode_timer);
        }

        safe_mode_timer = timer_set("safe_mode", TIMER_100_MS_TICKS * 105, 1, stop_tx_can_message, NULL);
    }

    frame_pause(NULL,NULL);
    flash_set_safety(TRUE);
}

static void stop_tx_can_message(void* d)
{
    if(MONITOR_MODE_SAFE == monitor_info.mode)
    {
        AppComTxRx_Stop();
    }
    safe_mode_timer = NULL;

    MONITOR_PRINTF("[Monitor]stop_tx_can_message\n");
}

static void voltage_power_supply_result_handler(monitor_res_code_e res)
{
	static uint16_t Battery_Voltage_too_high = 0;
	static uint16_t Battery_Voltage_too_low = 0;
	static uint16_t custom_sig_battery_v_too_high = 0;
	static uint16_t custom_sig_battery_v_too_low = 0;
	static uint32_t power_low_detected_elapsed = 0;

	is_ps_voltage_updated = TRUE;

	//911717	Battery voltage too high
	//911716	Battery voltage too low

	static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

	if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//Battery too high
        Battery_Voltage_too_high        = 1;
        Battery_Voltage_too_low         = 0;
        custom_sig_battery_v_too_high   = 1;
        custom_sig_battery_v_too_low    = 0;

        Dem_SetEventStatus(DTC_0x911717_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x911716_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//Battery too low
        Battery_Voltage_too_high    = 0;
        Battery_Voltage_too_low     = 1;

        if(power_low_detected_elapsed == 0)
        {
            power_low_detected_elapsed = STM_0.CNT.R;
        }

        if(power_low_detected_elapsed && ((STM_0.CNT.R - power_low_detected_elapsed)*CLOCK_PERIOD_S >= 10.0)) //10s
        {//10s
            custom_sig_battery_v_too_high   = 0;
            custom_sig_battery_v_too_low    = 1;

            Dem_SetEventStatus(DTC_0x911717_INDEX,DEM_EVENT_STATUS_PASSED); //Failed
            Dem_SetEventStatus(DTC_0x911716_INDEX,DEM_EVENT_STATUS_FAILED); //Passed
        }

        if(power_low_detected_elapsed)
        {
            PRINTF("[Monitor]power_low_detected elapsed: %.2fs\n", (STM_0.CNT.R - power_low_detected_elapsed)*CLOCK_PERIOD_S);
        }
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {

    }
    else
    {//Passed
        power_low_detected_elapsed      = 0;
        Battery_Voltage_too_high        = 0;
        Battery_Voltage_too_low         = 0;
        custom_sig_battery_v_too_high   = 0;
        custom_sig_battery_v_too_low    = 0;

        Dem_SetEventStatus(DTC_0x911717_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x911716_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_BATTERY_VOLTAGE_TOO_HIGH, &custom_sig_battery_v_too_high);
    Com_SendSignal(COM_TXSIG_BATTERY_VOLTAGE_TOO_LOW, &custom_sig_battery_v_too_low);

	if(res != result)
	{
	    result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//Battery too high
            MONITOR_PRINTF("[Monitor]Battery voltage too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//Battery too low
            MONITOR_PRINTF("[Monitor]Battery voltage too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]Battery voltage status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]Battery voltage status passed\n");
        }

        MONITOR_PRINTF("[Monitor]Voltage power supply value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_POWER_SUPPLY));

        monitor_info.error.is_power_supply_voltage_too_high = Battery_Voltage_too_high;
        monitor_info.error.is_power_supply_voltage_too_low = Battery_Voltage_too_low;

        update_monitor_event();
	}
}

static void voltage_mcu_result_handler(monitor_res_code_e res)
{
	static uint16_t MCU_Voltage_too_high = 0;
	static uint16_t MCU_Voltage_too_low = 0;

	static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

	//9500A3	MCU_L voltage too high
	//9500A2	MCU_L voltage too low

	if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//MCU voltage too high
        MCU_Voltage_too_high    = 1;
        MCU_Voltage_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9500A3_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x9500A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//MCU voltage too low
        MCU_Voltage_too_high    = 0;
        MCU_Voltage_too_low     = 1;

        Dem_SetEventStatus(DTC_0x9500A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9500A2_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {

    }
    else
    {//Passed
        MCU_Voltage_too_high    = 0;
        MCU_Voltage_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9500A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9500A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_MCU_VOLTAGE_TOO_HIGH, &MCU_Voltage_too_high);
    Com_SendSignal(COM_TXSIG_MCU_VOLTAGE_TOO_LOW, &MCU_Voltage_too_low);

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//MCU voltage too high
            MONITOR_PRINTF("[Monitor]MCU voltage too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//MCU voltage too low
            MONITOR_PRINTF("[Monitor]MCU voltage too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]MCU voltage status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]MCU voltage status passed\n");
        }
        MONITOR_PRINTF("[Monitor]Voltage mcu value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_MCU));

        monitor_info.error.is_mcu_voltage_too_high = MCU_Voltage_too_high;
        monitor_info.error.is_mcu_voltage_too_low = MCU_Voltage_too_low;

        update_monitor_event();
    }
}

static void voltage_rf_ic_1_result_handler(monitor_res_code_e res)
{
	static uint16_t RF_Voltage1_too_high = 0;
	static uint16_t RF_Voltage1_too_low = 0;

	//9501A3	RF_L voltage1 too high
	//9501A2	RF_L voltage1 too low
    if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//RF_L voltage1 too high
        RF_Voltage1_too_high    = 1;
        RF_Voltage1_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9501A3_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x9501A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//RF_L voltage1 too low
        RF_Voltage1_too_high    = 0;
        RF_Voltage1_too_low     = 1;

        Dem_SetEventStatus(DTC_0x9501A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9501A2_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {
    }
    else
    {//Passed
        RF_Voltage1_too_high    = 0;
        RF_Voltage1_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9501A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9501A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_RF_VOLTAGE1_TOO_HIGH, &RF_Voltage1_too_high);
    Com_SendSignal(COM_TXSIG_RF_VOLTAGE1_TOO_LOW, &RF_Voltage1_too_low);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//RF_L voltage1 too high
            MONITOR_PRINTF("[Monitor]RF_L voltage1 too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//RF_L voltage1 too low
            MONITOR_PRINTF("[Monitor]RF_L voltage1 too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]RF_L voltage1 status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]RF_L voltage1 status passed\n");
        }
        MONITOR_PRINTF("[Monitor]Voltage rf ic 1 value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_1_RF_IC));

        monitor_info.error.is_rfic_voltage_too_high = RF_Voltage1_too_high;
        monitor_info.error.is_rfic_voltage_too_low = RF_Voltage1_too_low;

        update_monitor_event();
    }
}

static void voltage_rf_ic_2_result_handler(monitor_res_code_e res)
{
	static uint16_t RF_Voltage2_too_high = 0;
	static uint16_t RF_Voltage2_too_low = 0;

	//9502A3	RF_L voltage2 too high
	//9502A2	RF_L voltage2 too low
	if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//RF_L voltage2 too high
        RF_Voltage2_too_high    = 1;
        RF_Voltage2_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9502A3_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x9502A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//RF_L voltage2 too low
        RF_Voltage2_too_high    = 0;
        RF_Voltage2_too_low     = 1;

        Dem_SetEventStatus(DTC_0x9502A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9502A2_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {

    }
    else
    {//Passed
        RF_Voltage2_too_high    = 0;
        RF_Voltage2_too_low     = 0;

        Dem_SetEventStatus(DTC_0x9502A3_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x9502A2_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_RF_VOLTAGE2_TOO_HIGH, &RF_Voltage2_too_high);
    Com_SendSignal(COM_TXSIG_RF_VOLTAGE2_TOO_LOW, &RF_Voltage2_too_low);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//RF_L voltage2 too high
            MONITOR_PRINTF("[Monitor]RF_L voltage2 too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//RF_L voltage2 too low
            MONITOR_PRINTF("[Monitor]RF_L voltage2 too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]RF_L voltage2 status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]RF_L voltage2 status passed\n");
        }
        MONITOR_PRINTF("[Monitor]Voltage rf ic 2 value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_2_RF_IC));

        monitor_info.error.is_rfic2_voltage_too_high = RF_Voltage2_too_high;
        monitor_info.error.is_rfic2_voltage_too_low = RF_Voltage2_too_low;

        update_monitor_event();
    }
}

static void temperature_mcu_result_handler(monitor_res_code_e res)
{
	static uint16_t MCU_Temperature_too_high = 0;
	static uint16_t MCU_Temperature_too_low = 0;

	is_mcu_temper_updated = TRUE;

	//950098 	MCU_L temperature too high
	//95009A 	MCU_L temperature too low
	if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//MCU_L temperature too high
        MCU_Temperature_too_high    = 1;
        MCU_Temperature_too_low     = 0;

        Dem_SetEventStatus(DTC_0x950098_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x95009A_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//MCU_L temperature too low
        MCU_Temperature_too_high    = 0;
        MCU_Temperature_too_low     = 1;

        Dem_SetEventStatus(DTC_0x950098_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x95009A_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {

    }
    else
    {//Passed
        MCU_Temperature_too_high    = 0;
        MCU_Temperature_too_low     = 0;

        Dem_SetEventStatus(DTC_0x950098_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x95009A_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_MCU_TEMPERATURE_TOO_HIGH, &MCU_Temperature_too_high);
    Com_SendSignal(COM_TXSIG_MCU_TEMPERATURE_TOO_LOW, &MCU_Temperature_too_low);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//MCU_L temperature too high
            MONITOR_PRINTF("[Monitor]MCU_L temperature too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//MCU_L temperature too low
            MONITOR_PRINTF("[Monitor]MCU_L temperature too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]MCU_L temperature status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]MCU_L temperature status passed\n");
        }
        MONITOR_PRINTF("[Monitor]Temperature mcu value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_TEMPERATURE_MCU));

        monitor_info.error.is_mcu_temperature_too_high = MCU_Temperature_too_high;
        monitor_info.error.is_mcu_temperature_too_low = MCU_Temperature_too_low;

        update_monitor_event();
    }
}

//static void temperature_pmic_result_handler(monitor_res_code_e res)
//{
//	MONITOR_PRINTF("[Monitor]Temperature pmic value: %.2f\n", get_monitoring_value_by_id(MONITOR_ID_TEMPERATURE_PM_IC));
//}

static void temperature_rf_ic_result_handler(monitor_res_code_e res)
{
	static uint16_t RF_Temperature_too_high = 0;
	static uint16_t RF_Temperature_too_low = 0;

	//950198	RF_L temperature too high
	//95019A	RF_L temperature too low
    if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
    {//RF_L temperature too high
        RF_Temperature_too_high = 1;
        RF_Temperature_too_low  = 0;

        Dem_SetEventStatus(DTC_0x950198_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
        Dem_SetEventStatus(DTC_0x95019A_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
    {//RF_L temperature too low
        RF_Temperature_too_high = 0;
        RF_Temperature_too_low  = 1;

        Dem_SetEventStatus(DTC_0x950198_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x95019A_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }
    else if(MONITOR_RESULT_CODE_ERROR == res)
    {

    }
    else
    {//Passed
        RF_Temperature_too_high = 0;
        RF_Temperature_too_low  = 0;

        Dem_SetEventStatus(DTC_0x950198_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
        Dem_SetEventStatus(DTC_0x95019A_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }

    Com_SendSignal(COM_TXSIG_RF_TEMPERATURE_TOO_HIGH, &RF_Temperature_too_high);
    Com_SendSignal(COM_TXSIG_RF_TEMPERATURE_TOO_LOW, &RF_Temperature_too_low);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_FAILED_BEYOUND_MAX_VALUE == res)
        {//RF_L temperature too high
            MONITOR_PRINTF("[Monitor]RF_L temperature too high\n");
        }
        else if(MONITOR_RESULT_CODE_FAILED_BELOW_MIN_VALUE == res)
        {//RF_L temperature too low
            MONITOR_PRINTF("[Monitor]RF_L temperature too low\n");
        }
        else if(MONITOR_RESULT_CODE_ERROR == res)
        {
            MONITOR_PRINTF("[Monitor]RF_L temperature status error\n");
        }
        else
        {//Passed
            MONITOR_PRINTF("[Monitor]RF_L temperature status passed\n");
        }
        MONITOR_PRINTF("[Monitor]Temperature rf ic res: %d\n", res);

        monitor_info.error.is_rfic_temperature_too_high = RF_Temperature_too_high;
        monitor_info.error.is_rfic_temperature_too_low = RF_Temperature_too_low;

        update_monitor_event();
    }
}

static void master_clock_result_handler(monitor_res_code_e res)
{
	static uint16_t MCU_Master_Clock_Error = 0;
	//950049	MCU_L Master Clock Error	(V)(V)
	if(MONITOR_RESULT_CODE_PASSED == res)
    {
        MCU_Master_Clock_Error  = 0;

        Dem_SetEventStatus(DTC_0x950049_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        MCU_Master_Clock_Error  = 1;

        Dem_SetEventStatus(DTC_0x950049_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_MCU_MASTER_CLOCK_ERROR, &MCU_Master_Clock_Error);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]MCU_L Master Clock status passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]MCU_L Master Clock status failed\n");
        }
        MONITOR_PRINTF("[Monitor]MCLK res: %d\n", res);

        monitor_info.error.is_master_clock_error = MCU_Master_Clock_Error;

        update_monitor_event();
    }
}

static void fccu_other_result_handler(monitor_res_code_e res)
{
	static uint16_t MCU_Error = 0;

	//950045	MCU_L MCU Error
	if(MONITOR_RESULT_CODE_PASSED == res)
    {
        MCU_Error   = 0;

        Dem_SetEventStatus(DTC_0x950045_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        MCU_Error   = 1;
        Dem_SetEventStatus(DTC_0x950045_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_MCU_ERROR, &MCU_Error);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]MCU error status passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]MCU error status failed\n");
        }
        MONITOR_PRINTF("[Monitor]MCU error res: %d\n", res);

        monitor_info.error.is_mcu_error = MCU_Error;

        update_monitor_event();
    }
}

static void fccu_memory_result_handler(monitor_res_code_e res)
{
	static uint16_t MCU_Memory_Error = 0;

	//950044	MCU_L Memory Error
	if(MONITOR_RESULT_CODE_PASSED == res)
	{
	    MCU_Memory_Error    = 0;

        Dem_SetEventStatus(DTC_0x950044_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        MCU_Memory_Error    = 1;

        Dem_SetEventStatus(DTC_0x950044_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_MCU_MEMORY_ERROR, &MCU_Memory_Error);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]FCCU memory status passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]FCCU memory status failed\n");
        }
        MONITOR_PRINTF("[Monitor]FCCU memory res: %d\n", res);

        monitor_info.error.is_memory_error = MCU_Memory_Error;

        update_monitor_event();
    }
}

static void imu_result_handler(monitor_res_code_e res)
{
	static uint16_t IMU_Sensor_fault = 0;

    if(MONITOR_RESULT_CODE_PASSED == res)
    {
        IMU_Sensor_fault     = 0;

        Dem_SetEventStatus(DTC_0x950096_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        IMU_Sensor_fault     = 1;

        Dem_SetEventStatus(DTC_0x950096_INDEX,DEM_EVENT_STATUS_FAILED); //Passed
    }

    Com_SendSignal(COM_TXSIG_G_SENSOR_FAULT, &IMU_Sensor_fault);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]IMU status passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]IMU status failed\n");
        }
    }
}

static void rf_ism_result_handler(monitor_res_code_e res)
{
	static uint16_t RF_Sensor_fault = 0;

    if(MONITOR_RESULT_CODE_PASSED == res)
    {
        RF_Sensor_fault     = 0;

        Dem_SetEventStatus(DTC_0x950196_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        RF_Sensor_fault     = 1;

        Dem_SetEventStatus(DTC_0x950196_INDEX,DEM_EVENT_STATUS_FAILED); //Passed
    }

    Com_SendSignal(COM_TXSIG_RF_SENSOR_FAULT, &RF_Sensor_fault);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]RF ISM status passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]RF ISM status failed\n");
        }

        monitor_info.error.is_rf_sensor_fault = RF_Sensor_fault;

        update_monitor_event();
    }
}

static void radar_block_result_handler(monitor_res_code_e res)
{
	static uint16_t Radar_block_fault = 0;

    if(MONITOR_RESULT_CODE_PASSED == res)
    {
        Radar_block_fault   = 0;

        Dem_SetEventStatus(DTC_0x950097_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        Radar_block_fault   = 1;

        Dem_SetEventStatus(DTC_0x950097_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_RADAR_BLOCK, &Radar_block_fault);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]Radar block passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]Radar block failed\n");
        }

        Com_SendSignal(COM_TXSIG_RADAR_BLOCK, &Radar_block_fault);
    }
}

static void radar_missing_calibration_handler(monitor_res_code_e res)
{
	static uint16_t Radar_missing_calibration_fault = 0;

    if(MONITOR_RESULT_CODE_PASSED == res)
    {
        Radar_missing_calibration_fault     = 0;

        Dem_SetEventStatus(DTC_0x950054_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        Radar_missing_calibration_fault     = 1;

        Dem_SetEventStatus(DTC_0x950054_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_MISSING_CALIBRATION, &Radar_missing_calibration_fault);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]Missing calibration passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]Missing calibration failed\n");
        }

        monitor_info.error.is_missing_calibration = Radar_missing_calibration_fault;

        update_monitor_event();
    }
}

static void radar_mount_position_shift_handler(monitor_res_code_e res)
{
    static uint16_t Radar_mount_position_shift_fault = 0;

    if(MONITOR_RESULT_CODE_PASSED == res)
    {
        Radar_mount_position_shift_fault     = 0;

        Dem_SetEventStatus(DTC_0x950154_INDEX,DEM_EVENT_STATUS_PASSED); //Passed
    }
    else
    {
        Radar_mount_position_shift_fault     = 1;

        Dem_SetEventStatus(DTC_0x950154_INDEX,DEM_EVENT_STATUS_FAILED); //Failed
    }

    Com_SendSignal(COM_TXSIG_RADAR_MOUNT_POSITION_SHIFT_ERROR, &Radar_mount_position_shift_fault);

    static monitor_res_code_e result = MONITOR_RESULT_CODE_NONE;

    if(res != result)
    {
        result = res;
        if(MONITOR_RESULT_CODE_PASSED == res)
        {
            MONITOR_PRINTF("[Monitor]Radar mount position shift passed\n");
        }
        else
        {
            MONITOR_PRINTF("[Monitor]Radar mount position shift failed\n");
        }
    }
}
