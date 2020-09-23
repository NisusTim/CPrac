/*
 * event.h
 *
 *  Created on: 2016/12/06
 *      Author: erichu
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "typedefs.h"

#define ILLEGAL_PROC(x)	((event_proc_p)0x00404000)(x)
typedef void (*event_proc_p)(void*);

void put_event(const char *, event_proc_p, void*);
void event_handle(void);
void event_init(void);
void event_dump(char**, int);

typedef enum {
	SUCCESSED = 0,
	ERRNO_FAILED = -1,
	ERRNO_INVALID_ADDR = -2,
	ERRNO_CHECKSUM = -3,
	ERRNO_STATE=-4,
	ERRNO_IMGNO=-5,
	ERRNO_SIZE=-6,
	ERRNO_MAGIC=-7,
	ERRNO_CHKSUM=-8,
	ERRNO_FLASH_WRITE=-9,
	ERRNO_VERIFY=-10,
}errno_e;

//=============================================================================
// STANDARD ENUMERATIONS
//=============================================================================
typedef enum return_value
{
    SUCCESS=0,
    ERROR,
    TIMEOUT,
	MODE_CHANGE_ERROR,
    INVALID_PARAMETER,
	CHECKSUM_ERROR,
	TRIMMING_ERROR,
	CALIBRATION_ERROR,
	SPI_CLOCK_ERROR,
	SPI_CRC_ERROR
}retval_e;

#endif /* EVENT_H_ */
