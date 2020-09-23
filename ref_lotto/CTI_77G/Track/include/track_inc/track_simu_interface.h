/*
 * track_simu_interface.h
 *
 *  Created on: 2020/8/26
 *      Author: B0217 Tina Lee
 */

#ifndef _TRACK_SIMU_INTERFACE_H_
#define _TRACK_SIMU_INTERFACE_H_

// this interface is for simulator to process macro define, like PRINTF, IPC_SEND
// don't enable this if in radar code

#ifdef DEBUG_SIMU

    /*---DEBUG_CONSOLE this is for old simulator */
    //#define DEBUG_CONSOLE_PRINTF
    extern void printf_handler(char* fmt, ...);

    #ifdef DEBUG_CONSOLE_PRINTF
        #define PRINTF(fmt, ...) printf_handler(fmt, ##__VA_ARGS__);
    #else
        #define PRINTF(...)
    #endif

    #ifndef IPC_SEND_MSG_Z40
        #define IPC_SEND_MSG_Z40(...)
    #endif

    #ifndef IPC_SEND_MSG_Z71
        #define IPC_SEND_MSG_Z71(...)
    #endif

#endif

#endif /* _TRACK_SIMU_INTERFACE_H_ */
