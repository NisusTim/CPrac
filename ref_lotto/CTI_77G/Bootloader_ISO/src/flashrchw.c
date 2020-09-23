#if defined(START_FROM_FLASH)
#include "typedefs.h"

#define MPC57xx_ID    0x005A0000  /* RCHW boot ID for MPC57xx devices     */
#define VLE_ENABLE    0x01000000  /* VLE is enabled                       */

extern void _start(void);
#define ENTRY_POINT  _start
#define RCHW_VAL (VLE_ENABLE | MPC57xx_ID)

const uint32_t __attribute__ ((section(".rchw"))) RCHW1 = RCHW_VAL;
const uint32_t __attribute__ ((section(".cpu0_reset_vector"))) RCHW2 = (uint32_t)ENTRY_POINT;

#endif /* defined(START_FROM_FLASH) */






