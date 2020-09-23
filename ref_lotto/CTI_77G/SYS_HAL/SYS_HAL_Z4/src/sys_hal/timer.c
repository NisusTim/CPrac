/*
 * timer.c
 *
 *  Created on: 2017/03/21
 *      Author: erichu
 */

#ifndef TIMER_C_
#define TIMER_C_

#include "sys_shared.h"

#ifdef CTI_Z4_0
extern void FCCU_mcu_error_passed(void);
#ifdef ENABLE_BSW_UDS_NM
#include "Can.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Com.h"
#include "Dem.h"
#include "Nvm.h"
#include "Dem_Lcfg.h"
#include "cubtek_monitor_handler.h"
#include "can_cubtek.h"
#include "Com_cfg.h"
#endif
#endif

#define MAX_COUNT_OF_TIMER		8

static timer_t timer_data[MAX_COUNT_OF_TIMER];
static int32_t ticks_per_second = DEFAULT_TICKS_PER_SECOND;
static uint32_t	time = 0;

#ifdef CTI_Z4_0
#ifdef ENABLE_BSW_UDS_NM
static uint32_t ds_1s_delay_timer = 1000/CANTP_MAIN_FUNCTION_PERIOD;
static uint32_t ds_can_comm_lost_after_wakeup_timer = 60000/CANTP_MAIN_FUNCTION_PERIOD; //
static timer_p  sleep_timer = NULL;
void set_sleep_flag(void* d);
#endif
#endif


#ifdef CTI_Z4_0
#ifdef ENABLE_BSW_UDS_NM
static uint8_t dem_start_init_flag = FALSE;
#endif
#endif

#if defined(CTI_Z4_0)
static void _timer_dump(char** args, int count)
{
	timer_p tmr = timer_data;
	char * unset = NULL;
	if(count > 1){
		unset = args[1];
	}
	while(tmr < &timer_data[MAX_COUNT_OF_TIMER]) {
		if(tmr->proc != NULL){
			if(unset != NULL && !strcmp(unset, tmr->name))
				tmr->proc = NULL;
			else
				PRINTF("tmr(%s): %p:%lu\n",tmr->name, tmr->proc, tmr->ticks);
		}
		tmr++;
	}
}
#endif

#if defined(CTI_Z4_0) || defined(CTI_Z7_1)
static void _timer_trigger(void)
{
	timer_p tmr = timer_data;
	while (tmr != &timer_data[MAX_COUNT_OF_TIMER]) {
		if(tmr->proc && tmr->time <= time) {
			put_event((const char*)tmr->name, tmr->proc, tmr->data);
			tmr->time = time + tmr->ticks;
			if(tmr->cnt > 0) {
				tmr->cnt--;
				if(tmr->cnt == 0) {
					tmr->proc = NULL;
				}
			}
		}
		tmr++;
	}
}
#endif

timer_p timer_set(char* name, uint32_t ticks, int16_t cnt, event_proc_p proc, void *d)
{
	timer_p tmr = timer_data;
	while(tmr < &timer_data[MAX_COUNT_OF_TIMER]) {
		if(tmr->proc == NULL){
			tmr->name = name;
			tmr->cnt = cnt;
			tmr->data = d;
			tmr->ticks = ticks;
			tmr->time = time+ticks;
			tmr->proc = proc;
			return tmr;
		}
		tmr++;
	}
	return NULL;
}

void timer_unset_all(void)
{
	timer_p tmr = timer_data;
	while(tmr < (timer_data+MAX_COUNT_OF_TIMER)){
		tmr->proc = NULL;
		tmr++;
	}
}

void timer_unset(timer_p *tp)
{
	timer_p tmr = timer_data;

	if (*tp == NULL)
		return;

	if(*tp >= tmr && *tp < &timer_data[MAX_COUNT_OF_TIMER])
		(*tp)->proc = NULL;

	*tp = NULL;
}

uint32_t time_get(void)
{
	return time;
}

void timer_init(int32_t ticks)
{
	// PIT Timer Initialization
	memset((void*)timer_data, 0, sizeof(timer_data));
	if(ticks != 0)
		ticks_per_second = ticks;
#if defined(CTI_Z4_0)
	PIT_0.TIMER[0].LDVAL.R = (TIMER_CLOCK/ticks_per_second)-1;   // setup timer 0 for 20 cycles/per second
	PIT_0.MCR.B.MDIS = 0;               //Enable PIT_0 timers
	PIT_0.TIMER[0].TCTRL.B.TIE = 1;     // Timer interrupt enable
	PIT_0.TIMER[0].TCTRL.B.TEN = 1;     // start Timer

	INTC.PSR[226].R = Interrput_Core_Selected| 0x0001;	//set priority and core for PIT interrupt

    // Start STM0 in free running
    STM_0.CHANNEL[0].CCR.R = 0x1; 	        // Channel enable CH0
    STM_0.CNT.R = 0;            			// Clear counter.
    STM_0.CR.R = 0x00000001;		        // Divide system clock by 1 & enable timer

    console_command_reg("timer", _timer_dump);
    
    cubtek_faw_did_ds_1s_delay_status_set(FALSE);
    ds_1s_delay_timer = 1000/CANTP_MAIN_FUNCTION_PERIOD;

    cubtek_faw_did_ds_communication_bus_off_status_set(FALSE);

    cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_set(FALSE);
    ds_can_comm_lost_after_wakeup_timer = 60000/CANTP_MAIN_FUNCTION_PERIOD;

    cubtek_faw_did_ds_ready_to_sleep_status_set(FALSE);
    cubtek_faw_did_ds_can_status_set(CAN_EnRx_EnTx);

#elif defined(CTI_Z7_0)
	PIT_1.MCR.B.MDIS = 1;               //Disable PIT_1 timers
	PIT_1.TIMER[0].LDVAL.R = (TIMER_CLOCK/ticks_per_second)-1;   // setup timer 0 for 20 cycles/per second
	PIT_1.TIMER[0].TCTRL.B.TIE = 1;     // Timer interrupt enable
	PIT_1.TIMER[0].TCTRL.B.TEN = 1;     // start Timer
	PIT_1.MCR.B.MDIS = 0;               //Enable PIT_1 timers

	INTC.PSR[230].R = Interrput_Core_Selected| 0x0001;

    STM_1.CNT.R = 0;            			// Clear counter.
    STM_1.CR.R = 0x00000001;		        // Divide system clock by 1 & enable timer
#elif defined(CTI_Z7_1)
	PIT_1.MCR.B.MDIS = 1;               //Disable PIT_1 timers
	PIT_1.TIMER[1].LDVAL.R = (TIMER_CLOCK/ticks_per_second)-1;   // setup timer 1 for 20 cycles/per second
	PIT_1.TIMER[1].TCTRL.B.TIE = 1;     // Timer interrupt enable
	PIT_1.TIMER[1].TCTRL.B.TEN = 1;     // start Timer
	PIT_1.MCR.B.MDIS = 0;               //Enable PIT_1 timers

	INTC.PSR[231].R = Interrput_Core_Selected| 0x0001;

    // Start STM2 in free running
    STM_2.CHANNEL[0].CCR.R = 0x1; 	        // Channel enable CH0
    STM_2.CNT.R = 0;            			// Clear counter.
    STM_2.CR.R = 0x00000001;		        // Divide system clock by 1 & enable timer
#endif
}

void system_timer_isr(void)
{
#if defined(CTI_Z4_0)
    PIT_0.TIMER[0].TFLG.B.TIF = 1;      // Clear PIT_0 interrupt flag
#elif defined(CTI_Z7_0)
    PIT_1.TIMER[0].TFLG.B.TIF = 1;      // Clear PIT_1 channel 0 interrupt flag
#elif defined(CTI_Z7_1)
    PIT_1.TIMER[1].TFLG.B.TIF = 1;      // Clear PIT_1 channel 1 interrupt flag
#endif
    time++;
#if defined(CTI_Z4_0) || defined(CTI_Z7_1)
    _timer_trigger();
#endif
}

#ifdef ENABLE_BSW_UDS_NM
/*
 * Custom timer initialization
 */
#define MAX_COUNT_OF_CUSTOM_TIMER	4
static timer_t custom_timer_data[MAX_COUNT_OF_CUSTOM_TIMER];
static int32_t custom_ticks_per_second = 200; // 5ms

void custom_timer_init(int32_t ticks)
{
	// PIT Timer Initialization
	memset((void*)custom_timer_data, 0, sizeof(custom_timer_data));
	if(ticks != 0)
		custom_ticks_per_second = ticks;
	PIT_0.TIMER[1].LDVAL.R = (TIMER_CLOCK/custom_ticks_per_second)-1;   // setup timer 0 for 20 cycles/per second
	PIT_0.MCR.B.MDIS = 0;               //Enable PIT_0 timers
	PIT_0.TIMER[1].TCTRL.B.TIE = 1;     // Timer interrupt enable
	PIT_0.TIMER[1].TCTRL.B.TEN = 1;     // start Timer

	INTC.PSR[227].R = 0x8001;           //set priority and core for PIT interrupt

    // Start STM in free running
    STM_0.CHANNEL[1].CCR.R = 0x1; 	        // Channel enable CH1
    //STM_0.CNT.R = 0;            			// Clear counter.
    //STM_0.CR.R = 0x00000001;		        // Divide system clock by 1 & enable timer
}

#ifdef CTI_Z4_0
void custom_timer_event(void* x)
{
    //100ms
    static uint8_t count = 0;

	if(count % 10 == 9)
	{
	    FCCU_mcu_error_passed();
	}

    count++;
}

void custom_timer_isr(void)
{
    static uint32_t custom_time = 0;

    PIT_0.TIMER[1].TFLG.B.TIF = 1;      // Clear PIT_0[1] interrupt flag
    custom_time++;
    if(custom_time %2 ==1)
    {   //10ms
    	if(FALSE == cubtek_faw_did_ds_1s_delay_status_get())
		{
			ds_1s_delay_timer--;
			if(0 == ds_1s_delay_timer)  //ds_1s_delay_timer == 100, 100*10ms = 1000ms
			{   //1000ms
				Dem_SetOperationCycleState(DEM_OPCYC_IGNITION,DEM_CYCLE_STATE_START);	//DEM start
				cubtek_faw_did_ds_1s_delay_status_set(TRUE);
			}
		}

		if(FALSE == cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_get())
		{
			ds_can_comm_lost_after_wakeup_timer--;
			if(0 == ds_can_comm_lost_after_wakeup_timer)
			{
				cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_set(TRUE);
			}
		}

        Com_MainFunctionRx();
        Com_MainFunctionTx();
        Dem_MainFunction();
        NvM_MainFunction();

        if(custom_time %20 ==1)
        {   //100ms
            put_event((const char*)"ctmr", custom_timer_event, NULL);
        }
        //J1939_DM1_monitor();

        /*Diagnostic service starts to start when power is on 1s*/
        if(TRUE == cubtek_faw_did_ds_1s_delay_status_get())	
        {
            CanTp_MainFunction();
            Dcm_MainFunction();
            if(!dem_start_init_flag)
            {
                dem_start_init_flag = TRUE;
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC07688_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC23A87_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950096_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950081_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950181_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950281_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950381_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0x950481_INDEX<<8) | DEM_EVENT_STATUS_PASSED));	
            }

            if(TRUE == cubtek_faw_did_ds_ready_to_sleep_status_get())
            {
                //Enter sleep mode
                if(NULL == sleep_timer)
                {
                    sleep_timer = timer_set("sleep_flag", DEFAULT_TICKS_PER_SECOND, 1, set_sleep_flag, NULL);
                    //sleep_timer = timer_set("sleep_flag", TIMER_13_MS_TICKS, 1, set_sleep_flag, NULL);
                }
            }                        
        }

        if(TRUE == gs_CanBusoffOccur)
        {
            uint16 Communication_Bus_OFF = 1;
            gs_CanBusoffOccur = FALSE;
            Dcm_Init(DCM_NULL);
            if(TRUE != cubtek_faw_did_ds_communication_bus_off_status_get())	
            {
                cubtek_faw_did_ds_communication_bus_off_status_set(TRUE);
                Communication_Bus_OFF = 1;
                put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC07688_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
            }
            Com_SendSignal(COM_TXSIG_COMMUNICATION_BUS_OFF, &Communication_Bus_OFF);
        }

    }
}

void set_sleep_flag(void* d)
{
	uint16_t flag = 1;
	AppComTxRx_Stop();
	Dem_Shutdown();	
	Com_SendSignal(COM_TXSIG_RADER_SLEEP_FLAG, &flag);

	while(FALSE == FS8x_goto_standby());
	sleep_timer = NULL;		
}
#endif

static uint32_t elapsed = 0;
uint32_t get_STM_CNT()
{
#if defined(CTI_Z4_0)
    return STM_0.CNT.R;
#elif defined(CTI_Z7_0)
    return STM_1.CNT.R;
#elif defined(CTI_Z7_1)
    return STM_2.CNT.R;
#endif
}
void start_watch(uint32_t *time)
{
	elapsed = STM_0.CNT.R;
	*time = elapsed;
}

void stop_watch()
{
	elapsed = STM_0.CNT.R - elapsed;
}

float elapsed_time_ms()
{
	return (float)elapsed * 16.7f/1000000.0f;
}
#endif

#endif /* TIMER_C_ */
