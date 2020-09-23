/*
 * event_handle.c
 *
 *  Created on: 2016/12/06
 *      Author: erichu
 */

#define _EVENT_HANDLE_C_

#include "sys_shared.h"

typedef struct {
	event_proc_p	proc;
	void*			data;
	const char*		name;
	uint32_t		time;
	uint32_t		stamp;
}event_t,*event_p;

#define SIZE_OF_EVENT_QUE			64
typedef struct {
	event_t 		que[SIZE_OF_EVENT_QUE];
	event_p			head,tail;
}events_t,*events_p;

void event_init(void);
void event_dump(char**, int);

static events_t events={.head=events.que, .tail=events.que};
static events_p pev=&events;

void event_init(void)
{
#if defined(CTI_Z4_0)
    console_command_reg("event",event_dump);
#endif
	return;
}
/******************************************************************************
Function Name : put_event
args e : event number need be handled
args d : data pointer for this event
caution : this function called only in ISR or interrupt disabled
******************************************************************************/
void put_event(const char* name, event_proc_p p, void*  d)
{
	PPCASM(" wrteei 0");
	pev->head->proc = p;
	pev->head->data = d;
	pev->head->name = name;
	if(pev->head == &pev->que[SIZE_OF_EVENT_QUE-1])
		pev->head = pev->que;
	else
		pev->head++;
	PPCASM(" wrteei 1");
}

/******************************************************************************
Function Name : event handler
******************************************************************************/
void event_handle(void)
{
#if defined(DEBUG_PROC)
    static int dump_cnt = 0;
#endif

	if(pev->head != pev->tail){
		if(pev->tail->proc != NULL){
			//PRINTF("%s:%p\n", pev->tail->name, pev->tail->proc); //((float)evt->time*16.7f)/1000000);
		    int evt_cnt = (pev->head-pev->tail)&(SIZE_OF_EVENT_QUE-1);

            if(evt_cnt >= SIZE_OF_EVENT_QUE-(SIZE_OF_EVENT_QUE/4))
            {
                PRINTF("Evt que almost full(%d,%d)\n", evt_cnt, SIZE_OF_EVENT_QUE);

#if defined(DEBUG_PROC)
                if(dump_cnt == 0){
                    dump_cnt = evt_cnt*2;
                    event_dump(NULL, 0);
                }
                else if(dump_cnt)
                    dump_cnt--;
#endif
            }

#if defined(DEBUG_PROC_IN_TIME) || defined(DEBUG_PROC)
			pev->tail->time = STM_0.CNT.R;
			pev->tail->proc(pev->tail->data);
			pev->tail->time = STM_0.CNT.R-pev->tail->time;

			if(pev->tail->time > (TIMER_CLOCK/200)/*5ms*/)
			{
				PRINTF("evt-%s:%p:%.1fus-%d\n", pev->tail->name, pev->tail->proc,pev->tail->time*CLOCK_PERIOD_US, evt_cnt);
			}
#else
			pev->tail->proc(pev->tail->data);
#endif
		}

		if(pev->tail == &pev->que[SIZE_OF_EVENT_QUE-1])
			pev->tail = pev->que;
		else
			pev->tail++;
	}
}

/********************************************************************************
 * Function : dump event que
 ********************************************************************************/
void event_dump(char** args, int count)
{
#if defined(CTI_Z4_0)
#if defined(DEBUG_PROC_IN_TIME) || defined(DEBUG_PROC)
	event_p evt = pev->tail+1;

	if(evt == &pev->que[SIZE_OF_EVENT_QUE])
		evt = pev->que;

	PRINTF_FORCE("Evts(%d) que dump:\n", SIZE_OF_EVENT_QUE);
	while(evt != pev->tail) {
	    PRINTF_FORCE("%s:%p:%.fus\n", evt->name, evt->proc, evt->time*CLOCK_PERIOD_US); //((float)evt->time*16.7f)/1000000);

		evt++;
		if(evt == &pev->que[SIZE_OF_EVENT_QUE])
			evt = pev->que;
	}
#endif
#endif
}
