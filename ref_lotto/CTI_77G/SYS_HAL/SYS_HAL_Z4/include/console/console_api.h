/*
 * console_api.h
 *
 *  Created on: 2019¦~2¤ë22¤é
 *      Author: user
 */

#ifndef CONSOLE_CONSOLE_API_H_
#define CONSOLE_CONSOLE_API_H_

#ifdef ENET_PRINTF

#define PRINTF(...)		enet_printf(__VA_ARGS__)

#else

#define PRINTF(...) 										\
	do {													\
		char __line[160];									\
		snprintf(__line, sizeof(__line)-1, __VA_ARGS__); 	\
		put_string(__line);									\
	} while(0)

#define NEW_LINE() PRINTF(" \n")

#endif /* CONSOLE_H_ */

#endif /* CONSOLE_CONSOLE_API_H_ */
