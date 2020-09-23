/*
 * console.h
 *
 *  Created on: 2016/12/06
 *  Modified on: 2018/05/07
 *      Author: erichu, woodliu
 */

#ifndef CONSOLE_CONSOLE_H_
#define CONSOLE_CONSOLE_H_

#include <cstdio>
#include "parameters.h"
#include "can_api.h"

/*
 * Shared console memory structure
 */
#define SIZE_OF_CONSOLE_DATA_TXD				8192
#define SIZE_OF_CONSOLE_DATA_RXD				1024
#define SIZE_OF_CAN_CONSOLE_DATA_TXD			(SIZE_OF_CONSOLE_DATA_TXD/8)
#define SIZE_OF_CAN_CONSOLE_DATA_RXD			(SIZE_OF_CONSOLE_DATA_RXD)
#define MAX_DATA_COUNT_OF_CONSOLE				(20)  // command, addr and 16 data for written

#define CH_LF			'\n'
#define CH_CR			'\r'
#define CH_BS			0x08

#define ENABLE				(1)
#define DISABLE				(0)

#define UART_CONSOLE		DISABLE

typedef enum {
	CNSL_MSG_INIT = 1,
	CNSL_MSG_PARAMETER_CHANGED,
	CNSL_MSG_PROC
}CONSOLE_MSG_E;

typedef enum {
#if UART_CONSOLE
	CNSL_ITF_UART = 0,
#endif
	CNSL_ITF_ENET = 1,
	CNSL_ITF_CAN0 = 2,
	CNSL_ITF_CAN2 = 3,
	CNSL_ITF_UNKNOWN,
}CONSOLE_INTERFACE_E;

typedef struct {
	/*General Console Format*/
	CONSOLE_INTERFACE_E itf;									//Console interface
	uint8_t				enable;									//Console enable
	uint8_t				rdy;									//Console ready
	uint16_t			txid;									//Console tx id (if need)
	uint16_t			rxid;									//Console rx id	(if need)
	uint8_t				can0_mb;								//Console can0 mailbox (if need)
	uint8_t				can2_mb;								//Console can2 mailbox (if need)

	uint8_t 			rxque[SIZE_OF_CONSOLE_DATA_RXD];		//Console rx queue
	char 				*args[MAX_DATA_COUNT_OF_CONSOLE+4];		//Console instructor
	uint16_t 			rx_head, arg_cnt;
	uint16_t 			tx_head, tx_tail;
	uint16_t 			force_tx_head, force_tx_tail;
	uint8_t 			each_data_position;
//	uint8_t				need_trigger_tx;

	/* Transmission Buffer */
	union
	{
		uint8_t 		txque[SIZE_OF_CONSOLE_DATA_TXD];			//uart tx queue
		can_packet_t	can_txque[SIZE_OF_CAN_CONSOLE_DATA_TXD];	//can tx queue
	};

} console_data_handle_t, *console_data_handle_p;

#if defined(CTI_Z4_0)

typedef struct {
	CONSOLE_INTERFACE_E itf;		//32
	uint8_t				enable;		//8
	uint16_t			txid;		//16
	uint16_t			rxid;		//16
}console_info_t, *console_info_p;

typedef struct {
	pars_header_t	hdr;
	console_info_t	info;
}console_parameters_t, *console_parameters_p;

#define CONSOLE_PARS_ID									FOURCC('c','n','s','l')
#define console_pars_info_get(_ver,_size)				pars_info_get(CONSOLE_PARS_ID,  _ver,_size)
#define console_pars_info_set(_data,_cnt)				pars_info_set(CONSOLE_PARS_ID, _data, _cnt)

#endif

void console_proc(void*);
void console_init(void);
void put_string(char *str);
extern uint16_t get_console_rx_can_id(void);
extern void console_trxid_setting(uint8_t idx);

#define MSG_PROMPT		"77G>"

#if defined(CTI_Z4_0)
	void console_flush(void);
	void console_force(char*);
	void console_err(uint32_t data);
	void console_itf_check_change(CONSOLE_INTERFACE_E itf);

#define PRINTF_FORCE(...) 									\
	do {													\
		char __line[160];									\
		snprintf(__line, sizeof(__line)-1, __VA_ARGS__); 	\
		console_force(__line);							\
	} while(0)
#endif

#endif
//#define ENET_PRINTF

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
