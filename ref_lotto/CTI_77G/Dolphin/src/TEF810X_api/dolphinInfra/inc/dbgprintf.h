/*
 *    DebugPrintf version 1.0.3
 *
 *    Prints out formatted text to the system debugger.
 *
 */

//#include <chrono>
//#include <ctime>
//#include <windows.h>
//#include <tchar.h>
//#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "console.h"

#ifndef _DBGPRINTF_H_
#define _DBGPRINTF_H_

#ifdef __cplusplus
extern "C"
{
#endif

// typdef struct __dbgprioctrl
// {
//     char * modID;

// }DbgPrioCtrl_t;

// #define DEBUG_MOD_INIT(MODID)
// {
//     static DbgPrioCtrl_t dbgctrl = {.modID = MODID};
// }

//The compiler defines _DEBUG when you specify the /MTd or /MDd option.
//C++ -> Code Generation --> Run Time Library

#ifdef _DEBUG

#ifndef VC_APP
int DebugPrintf(char * Format,...);
#define DbgPrintf DebugPrintf
#endif

#define DbgVer(_FMT_, ...) DbgPrintf("V::%s::%d::"_FMT_,__FUNCTION__,__LINE__,__VA_ARGS__)
#define DbgInfo(_FMT_, ...) DbgPrintf("I::%s::%d::"_FMT_,__FUNCTION__,__LINE__,__VA_ARGS__)
#define DbgErr(_FMT_, ...) DbgPrintf("E::%s::%d::"_FMT_,__FUNCTION__,__LINE__,__VA_ARGS__)
#define DbgWar(_FMT_, ...) DbgPrintf("W::%s::%d::"_FMT_,__FUNCTION__,__LINE__,__VA_ARGS__)
#define DbgTs(_FMT_, ...)

#else

#define DbgPrintf
#define DebugPrintf
#define DbgVer(_FMT_, ...)
#define DbgInfo(_FMT_, ...)
#define DbgErr(_FMT_, ...)
#define DbgWar(_FMT_, ...)
#define DbgTs(_FMT_, ...)

//#define DbgInfo PRINTF
//#define DbgErr PRINTF

#endif

	char * DebugGetPCTime(void);

#ifdef __cplusplus
}
#endif

#endif //_DBGPRINTF_H_
