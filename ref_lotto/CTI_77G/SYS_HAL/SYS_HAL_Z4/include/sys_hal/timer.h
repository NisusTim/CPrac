/*
 * timer.h
 *
 *  Created on: 2017/3/21
 *      Author: erichu
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "event.h"

#define TIMER_CLOCK						60000000
#define CLOCK_PERIOD_US					(1000000.0f/TIMER_CLOCK)			// 0.016667
#define CLOCK_PERIOD_MS					(1000.0f/TIMER_CLOCK)				// 0.000016667
#define CLOCK_PERIOD_S					(1.0f/TIMER_CLOCK)					// 0.000000016667
#define DEFAULT_TICKS_PER_SECOND		240									// 4.17ms
#define PERIOD_TIME_PER_TICK			(1000.0f/DEFAULT_TICKS_PER_SECOND)  // ms

#define TIMER_1000_MS_TICKS		(DEFAULT_TICKS_PER_SECOND)		//@tick = 240 per second
#define TIMER_500_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 2)
#define TIMER_333_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 3)
#define TIMER_200_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 5)
#define TIMER_125_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 8)
#define TIMER_100_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 10)
#define TIMER_50_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 20)
#define TIMER_25_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 40)
#define TIMER_13_MS_TICKS		(DEFAULT_TICKS_PER_SECOND / 80)

typedef struct {
	char*			name;
	uint32_t		time;
	event_proc_p 	proc;
	void*			data;
	uint32_t		ticks;
	int16_t			cnt;
	uint16_t        rsvd;
}timer_t,*timer_p;

void timer_init(int32_t);
void timer_unset_all(void);
timer_p timer_set(char* name, uint32_t ticks, int16_t cnt, event_proc_p proc, void *d);
void timer_unset(timer_p*);
void time_reset();
uint32_t time_get(void);
void timer_dump(char**,int);

#ifdef ENABLE_BSW_UDS_NM
void custom_timer_init(int32_t ticks);
void custom_timer_event(void* x);

uint32_t get_STM_CNT();
void start_watch();
void stop_watch();
float elapsed_time_ms();
#endif

#endif /* TIMER_H_ */
