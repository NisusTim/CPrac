/*
 * can_console.h
 *
 *  Created on: 2018/5/8
 *      Author: WoodLiu
 */

#ifndef CONSOLE_CAN_CONSOLE_H_
#define CONSOLE_CAN_CONSOLE_H_

enum {
	CNSL_TX_CAN_ID_0		=0x777,
	CNSL_TX_CAN_ID_1		=0x776,
	CNSL_TX_CAN_ID_2		=0x775,
	CNSL_TX_CAN_ID_3		=0x774,
	CNSL_TX_CAN_ID_4		=0x773,
	CNSL_TX_CAN_ID_5		=0x772,
	CNSL_TX_CAN_ID_6		=0x771,
	CNSL_TX_CAN_ID_7		=0x770,
};

enum {
	CNSL_RX_CAN_ID_0		=0x77F,
	CNSL_RX_CAN_ID_1		=0x77E,
	CNSL_RX_CAN_ID_2		=0x77D,
	CNSL_RX_CAN_ID_3		=0x77C,
	CNSL_RX_CAN_ID_4		=0x77B,
	CNSL_RX_CAN_ID_5		=0x77A,
	CNSL_RX_CAN_ID_6		=0x779,
	CNSL_RX_CAN_ID_7		=0x778,
};

/*******************************************************************************
* Function prototypes
*******************************************************************************/
#if defined(CTI_Z4_0)
	void can_console_init(void);
	void can_console_tx_handler(uint8_t* data);
	void can_console_rx_handler(can_message_p msg);
	void can2_console_rx_handler(can_message_p msg);
	void can_console_force(char *str);
	
#endif

void can_put_string(char *str);
void can_put_ch(char ch);
void can_tx_data();
uint8_t can_console_tx_ready_st(CONSOLE_INTERFACE_E itf);
void can_console_flush(void);
#endif /* SYS_HAL_CONSOLE_CAN_CONSOLE_H_ */
