/*
 * console_cmd.h
 *
 *  Created on: 2018/06/18
 *      Author: WoodLiu
 */

#ifndef CONSOLE_CONSOLE_CMD_H_
#define CONSOLE_CONSOLE_CMD_H_

#define MAX_COUNT_OF_CONSOLE_COMMANDS	128

typedef void (*console_proc_p)(char**, int);
typedef void (*console_callback_p) (char**, int);

typedef struct {
	const char* 		name;
	console_callback_p 	console_cb;
	int min_arg_cnt;
} console_cmd_table_t,*console_cmd_table_p;

#if defined(CTI_Z4_0)
	void mem_dump_force(uint32_t, int);
#endif
	int console_command_reg(const char*, console_callback_p);

console_cmd_table_p get_cmd_table();

#endif /* CONSOLE_CONSOLE_CMD_H_ */
