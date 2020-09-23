/*
 * console.c
 *
 *  Created on: 2017/2/17
 *      Author: erichu
 */

#include "sys_shared.h"

console_data_handle_t		__attribute__((section(".console"))) console_data;
static console_data_handle_p console=&console_data;
static console_cmd_table_p consoleTable;

#if defined(CTI_Z4_0)
static void console_info_dump(void);
/*******************************************************************************
* Console usage definitions
*******************************************************************************/

#define PARS_VERSION_MAJOR				0x04
#define PARS_VERSION_MINOR				0x00
#define VERSION_OF_CONSOLE_PARS    		(((uint16_t)PARS_VERSION_MAJOR<<8) | PARS_VERSION_MINOR)

console_parameters_t console_parameters = {
		.hdr = {
			.base = (uint32_t)&console_parameters,
			.version = VERSION_OF_CONSOLE_PARS,
			.size = sizeof(console_parameters_t),
			.id=CONSOLE_PARS_ID,
			.chksum = 0,
			.mask = 0,
		},
		.info = {
#ifdef USING_CUBTEK_CAN_0
			.itf 	= CNSL_ITF_CAN0,
#else
			.itf 	= CNSL_ITF_CAN2,
#endif
			.enable	= FALSE,
			.txid	= CNSL_TX_CAN_ID_0,
			.rxid	= CNSL_RX_CAN_ID_0,
		}
};

static console_info_p console_pars = &console_parameters.info;

#define JSON_CONSOLE_INFO_ITF 		"\t\t\"itf\":{\"t\":\"u32\",\"o\":%d,\"v\":%u},\n"
#define JSON_CONSOLE_INFO_ENABLE 	"\t\t\"enable\":{\"t\":\"u8\",\"o\":%d,\"v\":%u},\n"
#define JSON_CONSOLE_INFO_TXID 		"\t\t\"txid\":{\"t\":\"u16\",\"o\":%d,\"v\":%u},\n"
#define JSON_CONSOLE_INFO_RXID 		"\t\t\"rxid\":{\"t\":\"u16\",\"o\":%d,\"v\":%u}\n"

static int console_info_in_jsons(char* ws)
{
	int cnt = 0;
	if(ws){
		cnt = sprintf(ws,"{\n");
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_ID, (char)(CONSOLE_PARS_ID>>24),(char)(CONSOLE_PARS_ID>>16),(char)(CONSOLE_PARS_ID>>8),(char)(CONSOLE_PARS_ID));
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_VERSION, console_parameters.hdr.version);
		cnt += sprintf(ws+cnt, JSON_PARS_HDR_SIZE, console_parameters.hdr.size - sizeof(pars_header_t));

		cnt += sprintf(ws+cnt,"\t\"info\":{\n");
		cnt += sprintf(ws+cnt, JSON_CONSOLE_INFO_ITF, offsetof(console_info_t, itf), console_pars->itf);
		cnt += sprintf(ws+cnt, JSON_CONSOLE_INFO_ENABLE, offsetof(console_info_t, enable), console_pars->enable);
		cnt += sprintf(ws+cnt, JSON_CONSOLE_INFO_TXID, offsetof(console_info_t, txid), console_pars->txid);
		cnt += sprintf(ws+cnt, JSON_CONSOLE_INFO_RXID, offsetof(console_info_t, rxid), console_pars->rxid);
		cnt += sprintf(ws+cnt, "\t}\n}\n");
	}
	return cnt;
}

/******************************************************************************
Function : console handler to process console request
******************************************************************************/
void console_proc(void  *d)
{
	char *p, *line=(char*)console->rxque;
	console_cmd_table_p cs= (console_cmd_table_p)consoleTable;

	//upd_timer_set(0);

	console->arg_cnt = 0;
	if(d)
		line = (char*)d;
	if(!line[0])
		goto __console_end;

	p = strtok((char*)line, " ");
	while (p != NULL){
		console->args[console->arg_cnt++] = p;
		p = strtok(NULL, " ");
		if(console->arg_cnt >= (MAX_DATA_COUNT_OF_CONSOLE+4))
			break;
	}

	if(console->arg_cnt == 0)
		goto __console_end;

	#if defined(CTI_Z4_0) && defined(S32R274)
	if(strncmp("z7-", console->args[0], strlen("z7-")) == 0){
		IPC_SEND_MSG_Z70(MSG_CONSOLE_MSG, (void*)(CONSOLE_MSG_E)CNSL_MSG_PROC, 0);
		return;
	}
	#endif
	if(strncmp("z71-", console->args[0], strlen("z71-")) == 0){
		IPC_SEND_MSG_Z71(MSG_CONSOLE_MSG, (void*)(CONSOLE_MSG_E)CNSL_MSG_PROC, 0);
		return;
	}

	while(cs->name && cs < consoleTable + MAX_COUNT_OF_CONSOLE_COMMANDS) {
		if(!strcmp(console->args[0], cs->name)) {
			cs->console_cb(console->args, console->arg_cnt);
			break;
		}
		cs++;
	}

	if(cs->name == NULL)
		PRINTF("Unsupported command : %s !!\n", console->args[0]);

__console_end:
	PRINTF(MSG_PROMPT);
}

void console_err(uint32_t data)
{
	PRINTF("Console ctrl(%02X)\n", (uint8_t)data);
}

void console_info_dump(void)
{
	const char* interface_name[4] = {"INTERFACE_UART","INTERFACE_ENET","INTERFACE_CAN0","INTERFACE_CAN2"};
	PRINTF("cnsl: show console parameters\n");
	PRINTF("cnsl itf: %s\n"		, interface_name[console_pars->itf]);
	PRINTF("cnsl enable: %d\n"	, console_pars->enable);
	PRINTF("cnsl txid: 0x%x\n"	, console_pars->txid);
	PRINTF("cnsl rxid: 0x%x\n"	, console_pars->rxid);
}

void console_info_settings(char** args, int count)
{
	if (count > 2) {
		if(!strcmp(args[1], "itf"))
		{
			int16_t itf = strtol(args[2], NULL, 10);
			console_pars->itf = itf;
			pars_set((pars_ctx_p)&console_parameters);
		}
		else if(!strcmp(args[1], "enable"))
		{
			int16_t enable = strtol(args[2], NULL, 10);
			console->enable = enable;
			console_pars->enable = enable;
			pars_set((pars_ctx_p)&console_parameters);

			IPC_SEND_MSG_Z70(MSG_CONSOLE_MSG, (void*)(CONSOLE_MSG_E)CNSL_MSG_PARAMETER_CHANGED, 0);
		}
		else if(!strcmp(args[1], "txid") || !strcmp(args[1], "rxid"))
		{	//make sure txid and rxid will be a pair i.e., {TX, RX} = {0x777, 0x77F}, {0x776, 0x77E},...{0x770, 0x778}
			uint16_t can_console_txids[8] = {CNSL_TX_CAN_ID_0, CNSL_TX_CAN_ID_1, CNSL_TX_CAN_ID_2, CNSL_TX_CAN_ID_3,
											CNSL_TX_CAN_ID_4, CNSL_TX_CAN_ID_5, CNSL_TX_CAN_ID_6, CNSL_TX_CAN_ID_7};

			uint16_t can_console_rxids[8] = {CNSL_RX_CAN_ID_0, CNSL_RX_CAN_ID_1, CNSL_RX_CAN_ID_2, CNSL_RX_CAN_ID_3,
											CNSL_RX_CAN_ID_4, CNSL_RX_CAN_ID_5, CNSL_RX_CAN_ID_6, CNSL_RX_CAN_ID_7};
			int idx = atoi(args[2]);

			if(0 <= idx && idx <= 7)
			{
				console_pars->txid  = can_console_txids[idx];
				console_pars->rxid  = can_console_rxids[idx];
				pars_set((pars_ctx_p)&console_parameters);
			}
		}
	}

	console_info_dump();
}
uint16_t get_console_rx_can_id(void)
{
	return console_parameters.info.rxid;
}
void console_trxid_setting(uint8_t idx)
{
	uint16_t can_console_txids[8] = {CNSL_TX_CAN_ID_0, CNSL_TX_CAN_ID_1, CNSL_TX_CAN_ID_2, CNSL_TX_CAN_ID_3,
									CNSL_TX_CAN_ID_4, CNSL_TX_CAN_ID_5, CNSL_TX_CAN_ID_6, CNSL_TX_CAN_ID_7};

	uint16_t can_console_rxids[8] = {CNSL_RX_CAN_ID_0, CNSL_RX_CAN_ID_1, CNSL_RX_CAN_ID_2, CNSL_RX_CAN_ID_3,
									CNSL_RX_CAN_ID_4, CNSL_RX_CAN_ID_5, CNSL_RX_CAN_ID_6, CNSL_RX_CAN_ID_7};

	if(idx >= 0 && idx <= 7)
	{
		console->txid = can_console_txids[idx];
		console->rxid = can_console_rxids[idx];
		console_parameters.info.txid = console->txid;
		console_parameters.info.rxid = console->rxid;
		pars_set((pars_ctx_p)&console_parameters);
	}
}

/******************************************************************************
Function : console initialization
******************************************************************************/
void console_init(void)
{
	int i;
	pars_get((pars_ctx_p)&console_parameters, console_info_dump, console_info_in_jsons);
	sem_gate_reset(SEM_GATE_CONSOLE);

	console->itf = console_parameters.info.itf;
	console->enable = console_parameters.info.enable;
	console->txid = console_parameters.info.txid;
	console->rxid = console_parameters.info.rxid;
	console->rdy = FALSE;

	if(CNSL_RX_CAN_ID_0 < console->rxid || console->rxid < CNSL_RX_CAN_ID_7)
	{	//If rx id is wrong set
		uint8_t find_out = FALSE;
		uint16_t can_console_txids[8] = {CNSL_TX_CAN_ID_0, CNSL_TX_CAN_ID_1, CNSL_TX_CAN_ID_2, CNSL_TX_CAN_ID_3,
										CNSL_TX_CAN_ID_4, CNSL_TX_CAN_ID_5, CNSL_TX_CAN_ID_6, CNSL_TX_CAN_ID_7};

		uint16_t can_console_rxids[8] = {CNSL_RX_CAN_ID_0, CNSL_RX_CAN_ID_1, CNSL_RX_CAN_ID_2, CNSL_RX_CAN_ID_3,
										CNSL_RX_CAN_ID_4, CNSL_RX_CAN_ID_5, CNSL_RX_CAN_ID_6, CNSL_RX_CAN_ID_7};

		for(i = 0 ; i < 8 && find_out == FALSE ; i++)
		{
			if(can_console_txids[i] == console->txid)
			{
				console->rxid = can_console_rxids[i];
				console_parameters.info.rxid = console->rxid;
				pars_set((pars_ctx_p)&console_parameters);
				find_out = TRUE;
			}
		}

		if(FALSE == find_out)
		{	//If tx id is wrong
			console->txid = can_console_txids[0];
			console->rxid = can_console_rxids[0];
			console_parameters.info.txid = console->txid;
			console_parameters.info.rxid = console->rxid;
			pars_set((pars_ctx_p)&console_parameters);
		}
	}

	for(i = 0 ; i < SIZE_OF_CAN_CONSOLE_DATA_TXD ; i++)
	{
		console->can_txque[i].dw = 0;
	}

	for(i = 0 ; i < SIZE_OF_CAN_CONSOLE_DATA_RXD ; i++)
	{
		console->rxque[i] = 0;
	}

	console->rx_head = console->arg_cnt = 0;
	console->tx_head = console->tx_tail = 0;
    console->force_tx_head = console->force_tx_tail = 0;

	consoleTable = get_cmd_table();

#if (UART_CONSOLE == ENABLE)
	uart_console_init();
#endif

	can_console_init();

	console->rdy = TRUE;

	PRINTF("\n\nCubTek 77G Radar is up...\n");

	IPC_SEND_MSG_Z70(MSG_CONSOLE_MSG, (void*)(CONSOLE_MSG_E)CNSL_MSG_INIT, 0);
}

void console_flush(void)
{
	switch(console->itf)
	{
#if UART_CONSOLE
		case CNSL_ITF_UART:
			uart_console_flush();
#endif
			break;
		case CNSL_ITF_ENET:
			break;
		case CNSL_ITF_CAN0:
#ifdef USING_CUBTEK_CAN_0
		    can_console_flush();
#endif
			break;
		case CNSL_ITF_CAN2:
		    can_console_flush();
			break;
		case CNSL_ITF_UNKNOWN:
			break;
		default:
			break;
	}
}

void console_force(char* str)
{
	switch(console->itf)
	{
#if UART_CONSOLE
		case CNSL_ITF_UART:
			uart_console_force(str);
#endif
			break;
		case CNSL_ITF_ENET:
			break;
		case CNSL_ITF_CAN0:
#ifdef USING_CUBTEK_CAN_0
		    can_console_force(str);
#endif
			break;
		case CNSL_ITF_CAN2:    
		    can_console_force(str);
			break;
		case CNSL_ITF_UNKNOWN:
			break;
		default:
			break;
	}
}

void console_itf_check_change(CONSOLE_INTERFACE_E itf)
{
	int i;
	if(console->itf != itf)
	{
		console_pars->itf = itf;
        pars_set((pars_ctx_p)&console_parameters);
		
		SEM_GATE_LOCK(SEM_GATE_CONSOLE);

		console->rdy = FALSE;
		console->itf = itf;
		
		for(i = 0 ; i < SIZE_OF_CAN_CONSOLE_DATA_TXD ; i++)
		{
			console->can_txque[i].dw = 0;
		}

		for(i = 0 ; i < SIZE_OF_CAN_CONSOLE_DATA_RXD ; i++)
		{
			console->rxque[i] = 0;
		}

		console->rx_head = console->arg_cnt = 0;
		console->tx_head = console->tx_tail = 0;

		console->rdy = TRUE;
		
		SEM_GATE_UNLOCK(SEM_GATE_CONSOLE);

		IPC_SEND_MSG_Z70(MSG_CONSOLE_MSG, (void*)(CONSOLE_MSG_E)CNSL_MSG_PARAMETER_CHANGED, 0);
	}

	if(FALSE == console->enable)
	{
		console->enable = TRUE;
	}
}
#elif defined(CTI_Z7_0) || defined(CTI_Z7_1)
/******************************************************************************
Function : console handler to process console request
******************************************************************************/
void console_proc(void* d)
{
	console_cmd_table_p cs= (console_cmd_table_p)consoleTable;

	while(cs->name && cs < consoleTable + MAX_COUNT_OF_CONSOLE_COMMANDS) {
		#if defined(CTI_Z7_0)
		if(!strcmp(console->args[0]+2, cs->name)) {
		#elif defined(CTI_Z7_1)
			if(!strcmp(console->args[0]+4, cs->name)) {
		#endif
				cs->console_cb(console->args, console->arg_cnt);
			break;
		}
		cs++;
	}

	if(cs->name == NULL)
	{
		#if defined(CTI_Z7_0)
		PRINTF("Unsupported z70- command : %s !!\n", console->args[0]);
		#elif defined(CTI_Z7_1)
		PRINTF("Unsupported z71- command : %s !!\n", console->args[0]);
		#endif
	}

	PRINTF(MSG_PROMPT);
}

/******************************************************************************
Function : console initialization
******************************************************************************/

static void console_msg_handler(CONSOLE_MSG_E msg)
{
	switch(msg)
	{
		case CNSL_MSG_INIT:
			console_init();
			break;
		case CNSL_MSG_PARAMETER_CHANGED:
			break;
		case CNSL_MSG_PROC:
			console_proc(NULL);
			break;
	}
}

void console_init(void)
{
	consoleTable = get_cmd_table();
	#if defined(CTI_Z7_0)
	PRINTF("Z7_0 core_id=%d up\n77G>", GetCoreID());
	#elif defined(CTI_Z7_1)
	PRINTF("Z7_1 core_id=%d up\n77G>", GetCoreID());
	#endif
	ipc_reg_msg(MSG_CONSOLE_MSG, "cnslmsg", (msg_proc_p)console_msg_handler);
}

#endif

/******************************************************************************
Function : put string
******************************************************************************/
void put_string(char *str)
{
//	if(!console->rdy)
//		return;

	SEM_GATE_LOCK(SEM_GATE_CONSOLE);

	if(console->enable)
	{
		switch(console->itf)
		{
#if UART_CONSOLE
			case CNSL_ITF_UART:
				uart_put_string(str);
				break;
#endif
			case CNSL_ITF_ENET:
				break;
			case CNSL_ITF_CAN0:
#ifdef USING_CUBTEK_CAN_0
				can_put_string(str);
#endif
				break;
			case CNSL_ITF_CAN2:
				can_put_string(str);
				break;
			case CNSL_ITF_UNKNOWN:
				break;
			default:
				break;
		}
	}

	SEM_GATE_UNLOCK(SEM_GATE_CONSOLE);
}
