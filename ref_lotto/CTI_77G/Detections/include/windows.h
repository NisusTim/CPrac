/*
 * windows.h
 *
 *  Created on: 2018¦~4¤ë26¤é
 *      Author: erichu
 */

#ifndef CORE_WINDOWS_H_
#define CORE_WINDOWS_H_

typedef enum {
	WIN_TYPE_NONE=0,
	WIN_TYPE_HAMMING,
	WIN_TYPE_CHEBY,
	WIN_TYPE_BLACKMAN,
	WIN_TYPE_INVALID
}WIN_TYPE_E;

#define DEFAULT_HAMMING_FACTOR			54	// 0.54
#define DEFAULT_CHEBY_FACTOR			70  // 70db
#define DEFAULT_BLACKMAN_FACTOR			16  // 0.16

typedef void (*win_proc_p)(double *out, int N, float factor);
typedef struct {
	win_proc_p		proc;
	char*			name;
}window_context_t,*window_context_p;
void window_get(WIN_TYPE_E type, int N, void* out, int8_t);

#endif /* CORE_WINDOWS_H_ */
