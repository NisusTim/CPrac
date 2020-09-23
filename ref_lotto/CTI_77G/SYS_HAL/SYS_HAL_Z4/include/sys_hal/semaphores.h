/*
 * semaphores.h
 *
 *  Created on: 2017/02/21
 *      Author: erichu
 */

#ifndef SEMAPHORES_H_
#define SEMAPHORES_H_

#include "S32R274.h"

#define UNLOCK 			0
#define CORE0_LOCK 		1

typedef enum {
	SEM_GATE_CONSOLE  	= 0,
	SEM_GATE_SPI,
	SEM_GATE_REG_JSON_DBG,
	SEM_GATE_SEND_JSON_DBG,
	GATE_INVALID
}SEM_GATE_E;

#define stringify(s) tostring(s)
#define tostring(s) #s
#define mfspr(rn) ({unsigned int rval; __asm__ volatile("mfspr %0," stringify(rn) : "=r" (rval)); rval;})
#define mtspr(rn, v)   __asm__ volatile("mtspr " stringify(rn) ",%0" : : "r" (v))

#if defined(CTI_Z4_0)
    #define MASTER_ID    0
#elif defined(CTI_Z7_0)
    #define MASTER_ID    1
#else
    #define MASTER_ID    7
#endif
#define GetCoreID() ((uint16_t) mfspr(286))
#define SEM_MASTER_ID    (MASTER_ID+1)
#define SEM_GATE_LOCK(_gate_)						\
	do {											\
		while((uint8_t)SEMA42.GATE[_gate_].R != SEM_MASTER_ID) { \
			SEMA42.GATE[_gate_].R = SEM_MASTER_ID;		\
		}											\
	}while(0)


#define SEM_GATE_UNLOCK(_gate_)				\
	do {									\
		SEMA42.GATE[_gate_].R = UNLOCK;		\
	}while(0)

#define SEM_GATE_GET(_gate_)		SEMA42.GATE[_gate_].R

uint8_t sem_gate_reset(uint8_t gate_no);

#endif /* SEMAPHORES_H_ */
