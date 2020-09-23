#ifndef __ISOTP_USER_H__
#define __ISOTP_USER_H__

#include "customer.h"

#if ISOTP_EN
/* user implemented, print debug message */
void isotp_user_debug(const char* message, ...);

/* user implemented, send can message */
int  isotp_user_send_can(const uint32_t arbitration_id,
                         const uint8_t* data, const uint8_t size);

/* user implemented, get millisecond */
uint32_t isotp_user_get_ms(void);

void can2_burst_tx_handler(uint8_t mb);

#endif
#endif // __ISOTP_H__

