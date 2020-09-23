/*
 * console_cmd.c
 *
 *  Created on: 2018/6/18
 *      Author: WoodLiu
 */

#include "sys_shared.h"
#include "sbc_fs8x.h"       // fs8x_wd_handle()
#include "SWT.h"            // clear_SWT0_counter()
#include "Utility.h"        // Delay_us()

#define DEFAULT_COUNT_OF_CONSOLE_COMMANDS  19

static void dump_word(char**, int);
static void hangup(char**, int);
static void console_commands_list(char**, int);
#if defined(CTI_Z4_0)
static void dump_radar_info(void);
#endif
extern void __SP_INIT(void);
#if defined(CTI_Z7_0) || defined(CTI_Z7_1)
extern stack_info_t stkinfo_data;  //Z70 & Z71 stack_address_info
#endif

#if defined(CTI_Z4_0)
enum {
	LOCK_ST_PASSWORD = 0,
	LOCK_ST_SET,
	LOCK_ST_OFF,
	LOCK_ST_INVALID
};

/*******************************************************************************
* Locker usage definitions
*******************************************************************************/
#define DUMP_LOCKER_ON

#ifdef DUMP_LOCKER_ON
static int locker = LOCK_ST_PASSWORD;
#else
static int locker = LOCK_ST_OFF;
#endif

/*******************************************************************************
* Function prototypes
*******************************************************************************/
static void dump_hword(char**, int);
static void dump_signed_word(char**, int);
static void dump_signed_hword(char**, int);
static void dump_float(char**,int);
static void write_word(char **, int);
static void read_word(char **, int);
static void read_hword(char **, int);
static void fill_word(char **, int);
static void copy_word(char **, int);
static void copy_hword(char **, int);
static void write_hword(char **, int);
static void list_map(char**, int);
static void unlock(char** args, int count);

extern void console_info_settings(char** args, int count);

static console_cmd_table_t consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS] = {
		{"d", dump_word},
		{"dh", dump_hword},
		{"ds", dump_signed_word},
		{"dhs", dump_signed_hword},
		{"df", dump_float},
		{"rw", read_word},
		{"rh", read_hword},
		{"ww", write_word},
		{"fw", fill_word},
		{"wh", write_hword},
		{"cpw", copy_word},
		{"cph", copy_hword},
		{"map", list_map},
		{"ulock", unlock},
		{"reset", hangup},
		{"list", console_commands_list},
		{"cnsl", console_info_settings},
		{"event", event_dump},
		{"radar_info", (void (*)(char **, int))dump_radar_info},
		{NULL,NULL}};  // DEFAULT_COUNT_OF_CONSOLE_COMMANDS  19

#elif defined(CTI_Z7_0)
//void track_vrs(int value);
//void vrs_proc(char** args, int count);
//void log_cfar_set(char ** args, int );
extern void final_proc_command(char **, int);

static console_cmd_table_t consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS] = {
	{"-d", dump_word, 1},
	{"-dump", dump_word, 1},
	{"-list", console_commands_list},
	{"-vrs", final_proc_command, 1},
	{"-log-cfar", final_proc_command, 1},
	{"-sh", final_proc_command, 0},
	{"-cdbg", final_proc_command, 0},
	{"-dump", final_proc_command, 0},
#ifndef DISABLE_SWT
	{"-reset", hangup, 0},
#endif
	{"-", final_proc_command, 0},
	{NULL,NULL,0}
};

#elif defined(CTI_Z7_1)

static console_cmd_table_t consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS] = {
	{"d", dump_word, 1},
	{"list", console_commands_list},
	{"reset", hangup},
	{NULL,NULL,0}
};
#endif

static console_cmd_table_p console_table_p = consoleTable;

console_cmd_table_p get_cmd_table()
{
	return console_table_p;
}

void console_commands_list(char** args, int count)
{
	console_cmd_table_p cs= (console_cmd_table_p) &consoleTable[0];
#if defined(CTI_Z4_0)
	if(locker != LOCK_ST_OFF)
		return;
#endif

	PRINTF("Console commands:\n");
	while(cs < &consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS])
	{
		if(cs->name != NULL){
			#if defined(CTI_Z4_0)
			PRINTF("%s\n", cs->name);
			#elif defined(CTI_Z7_0)
			PRINTF("z70-%s\n", cs->name);
			#elif defined(CTI_Z7_1)
			PRINTF("z71-%s\n", cs->name);
			#endif
			}
		else
			return;
		cs++;
	}
}



int console_command_reg(const char* name, console_callback_p cb)
{
	console_cmd_table_p cs= (console_cmd_table_p) &consoleTable[0];
	if(name == NULL || cb == NULL)
		return ERRNO_FAILED;

	while(cs < &consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS]) {
		if(cs->name == NULL){
			cs->name = name;
			cs->console_cb = cb;
			if(cs < &consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS-1]){
				cs++;
				cs->name = NULL;
			}
			return SUCCESSED;
		}
		else if(!strcmp(name, cs->name)) {
			PRINTF("con: %s reged already\n", name);
			break;
		}
		cs++;
	}
	return ERRNO_FAILED;
}
#if defined(CTI_Z4_0)
static void dump_radar_info(void)
{
    if (LOCK_ST_SET != locker && LOCK_ST_OFF != locker)
        return;

    console_cmd_table_t *cmd_list = &consoleTable[DEFAULT_COUNT_OF_CONSOLE_COMMANDS];

    for (; cmd_list < &consoleTable[MAX_COUNT_OF_CONSOLE_COMMANDS]; ++cmd_list) {
        if (cmd_list->console_cb)
        {
            PRINTF(" \n");
            PRINTF("[%s]\n", cmd_list->name);
            cmd_list->console_cb((char **)cmd_list->name, cmd_list->min_arg_cnt);
        }
#ifdef ENABLE_SWT
        clear_SWT0_counter();
#endif
        fs8x_wd_handle(fs8xFlash);
        Delay_ms(10);
    }
}

void unlock(char** args, int count)
{
	if(count == 2){
		if (!strncmp("uk77fcws", args[1], 8)){
			locker = LOCK_ST_SET;
			PRINTF("ok\n");
		}
	}
}

/******************************************************************************
Function : dump memory in hex word(32bit) format
******************************************************************************/
void dump_word(char** args, int count)
{
	int cnt = 0;
	uint32_t addr, *d;

	if(count < 2)
		return;

	switch(locker) {
	case LOCK_ST_OFF :
		break;

	case LOCK_ST_SET :
		if(!strncmp(args[1], "on", 2))
			locker = LOCK_ST_OFF;
		return;

	default:
		return;
	}

		addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}
	if(count < 0x100)
		count = 0x100;

	addr &= 0xFFFFFFFC; // in case not aligned
	d = (uint32_t*) addr;
	put_string("Add/Offs 00000000 00000004 00000008 0000000C 00000010 00000014 00000018 0000001C\n");
	while(cnt < count) {
		PRINTF("%08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n", (uint32_t)d, d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
		d += 8;
		cnt += 0x20;
	}
}

/******************************************************************************
Function : dump memory in signed decimal word(32bit)
******************************************************************************/
void dump_signed_word(char** args, int count)
{
	int cnt = 0;
	uint32_t addr;
	int32_t  *d;

	if(locker < LOCK_ST_OFF || count < 2)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}
	if(count < 0x100)
		count = 0x100;

	addr &= 0xFFFFFFFC; // in case not aligned
	d = (int32_t*) addr;
	while(cnt < count) {
		PRINTF("%08lX %ld %ld %ld %ld %ld %ld %ld %ld\n", (uint32_t)d, d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
		d += 8;
		cnt += 0x20;
	}
}


/******************************************************************************
Function : dump memory in signed decimal half word(32bit)
******************************************************************************/
void dump_signed_hword(char** args, int count)
{
	int cnt=0;
	uint32_t addr;
	int16_t *d;

	if(locker < LOCK_ST_OFF || count < 2)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}
	if(count < 0x100)
		count = 0x100;


	addr &= 0xFFFFFFFC; // in case not aligned
	d = (int16_t*) addr;
	while(cnt < count) {
		PRINTF("%08lX %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", (uint32_t)d, \
				d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8],d[9],d[10],d[11],d[12],d[13],d[14],d[15]);
		d += 16;
		cnt += 0x20;
	}
}

/******************************************************************************
Function : dump memory in hex half word(16bit)
******************************************************************************/
void dump_hword(char** args, int count)
{
	int cnt = 0;
	uint32_t addr;
	uint16_t *d;

	if(locker < LOCK_ST_OFF || count < 2)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}
	if(count < 0x100)
		count = 0x100;

	addr &= 0xFFFFFFFC; // in case not aligned
	d = (uint16_t*) addr;
	PRINTF("Add/Offs 0000 0002 0004 0006 0008 000A 000C 000E 0010 0012 0014 0016 0018 001A 001C 001E\n");
	while(cnt < count) {
		PRINTF("%08lX %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X\n", (uint32_t)d, \
				d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7],d[8],d[9],d[10],d[11],d[12],d[13],d[14],d[15]);
		d += 16;
		cnt += 0x20;
	}
}

/******************************************************************************
Function : dump memory in float word(32bit) format
******************************************************************************/
void dump_float(char** args, int count)
{
	int cnt = 0;
	uint32_t addr;
	float *d;

	if(count < 2)
		return;

	switch(locker) {
	case LOCK_ST_OFF :
		break;

	case LOCK_ST_SET :
		if(!strncmp(args[1], "on", 2))
			locker = LOCK_ST_OFF;
		return;

	default:
		return;
	}

		addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}
	if(count < 0x100)
		count = 0x100;

	addr &= 0xFFFFFFFC; // in case not aligned
	d = (float*) addr;
	while(cnt < count) {
		PRINTF("%08lX %.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f\n", (uint32_t)d, d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
		d += 8;
		cnt += 0x20;
	}
}

/******************************************************************************
Function : read count of word data from d
******************************************************************************/
void read_word(char** args, int count)
{
	uint32_t addr, *p;

	if(locker < LOCK_ST_OFF || count < 2)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	addr &= 0xFFFFFFFC;

	p = (uint32_t*)addr;
	PRINTF("%08lX:%08lX\n", addr, *p);
}

/******************************************************************************
Function : read count of word data from d
******************************************************************************/
void read_hword(char** args, int count)
{
	uint32_t addr;
	uint16_t *p;

	if(locker < LOCK_ST_OFF || count < 2)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	addr &= 0xFFFFFFFE;

	p = (uint16_t*)addr;
	PRINTF("%08lX:%04X\n", addr, *p);
}

/******************************************************************************
Function : write count of word data from d
******************************************************************************/
void write_word(char** args, int count)
{
	int cnt = 2;
	uint32_t addr, *p;

	if(locker < LOCK_ST_OFF || count < 3)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	addr &= 0xFFFFFFFC;

	p = (uint32_t*)addr;
	while(cnt < count){
		*p = (uint32_t)strtoul(args[cnt], NULL, 16);
		p++;
		cnt++;
	}

	p = (uint32_t*)addr;
	cnt = 2;
	PRINTF("%08lX ", addr);
	while(cnt < count){
		PRINTF("%08lX ", *p++);
		cnt++;
	}
	PRINTF("\n");
}

/******************************************************************************
Function : write count of word data from d
******************************************************************************/
void fill_word(char** args, int count)
{
	int cnt, inc=0 ;
	uint32_t addr, *p, value = 0;

	if(locker < LOCK_ST_OFF || count < 3)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	cnt = (uint32_t)strtoul(args[2], NULL, 16);
	addr &= 0xFFFFFFFC;

	if (count >= 4)
		value = (uint32_t)strtoul(args[3], NULL, 16);

	if (count >= 5)
		inc= (uint32_t)strtoul(args[4], NULL, 16);

	p = (uint32_t*)addr;

	while(cnt--){
		*p = value;
		value += inc;
		p++;
	}
}

/******************************************************************************
Function : write count of word data from d
******************************************************************************/
void copy_word(char** args, int count)
{
	int cnt ;
	uint32_t sa, da, *sp, *dp;

	if(locker < LOCK_ST_OFF || count < 4)
		return;

	sa = (uint32_t)strtoul(args[1], NULL, 16);
	da = (uint32_t)strtoul(args[2], NULL, 16);
	sa &= 0xFFFFFFFC;
	da &= 0xFFFFFFFC;
	cnt = (uint32_t)strtoul(args[3], NULL, 16);

	sp = (uint32_t*)sa;
	dp = (uint32_t*)da;

	while(cnt--)
		*dp++ = *sp++;
}

/******************************************************************************
Function : write count of word data from d
******************************************************************************/
void copy_hword(char** args, int count)
{
	int cnt ;
	uint32_t sa, da;
	uint16_t *sp, *dp;

	if(locker < LOCK_ST_OFF || count < 4)
		return;

	sa = (uint32_t)strtoul(args[1], NULL, 16);
	da = (uint32_t)strtoul(args[2], NULL, 16);
	sa &= 0xFFFFFFFC;
	da &= 0xFFFFFFFC;
	cnt = (uint32_t)strtoul(args[3], NULL, 16);

	sp = (uint16_t*)sa;
	dp = (uint16_t*)da;

	while(cnt--)
		*dp++ = *sp++;
}

/******************************************************************************
Function : write count of half word data from d
******************************************************************************/
void write_hword(char** args, int count)
{
	int cnt = 2;
	uint32_t addr;
	uint16_t* p;

	if(locker < LOCK_ST_OFF || count < 3)
		return;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	addr &= 0xFFFFFFFE;

	p = (uint16_t*)addr;
	while(cnt < count){
		*p = (uint16_t)strtoul(args[cnt++], NULL, 16);
		p++;
	}

	p = (uint16_t*)addr;
	cnt = 2;
	PRINTF("%08lX ", addr);
	while(cnt < count){
		PRINTF("%04X ", *p++);
		cnt++;
	}
	PRINTF("\n");
}

/******************************************************************************
Function : list meaning memory map for each module
*******************************************************************************/
void list_map(char** args, int count)
{
	PRINTF("stack:%08lX:%08lX\n", (uint32_t)__SP_INIT, (uint32_t)__builtin_frame_address(1));
	PRINTF("RxSize:%08X:%08X\n", SIZE_OF_CONSOLE_DATA_RXD, MAX_DATA_COUNT_OF_CONSOLE);
	PRINTF("upd_mem:%08X:%08X\n", 0x40000000, 0x100000);
	SPT_mapped();
}

void mem_dump_force(uint32_t addr, int sz)
{
	int cnt = 0;
	uint32_t *d;
	addr &= 0xFFFFFFFC; // in case not aligned
	d = (uint32_t*) addr;
	console_force("Add/Offs 00000000 00000004 00000008 0000000C 00000010 00000014 00000018 0000001C\n");
	while(cnt < sz) {
		PRINTF_FORCE("%08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n", (uint32_t)d, d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
		d += 8;
		cnt += 0x20;
	}
}
#endif

/*******************************************************************************
Function Name : Machine_check_handler
Engineer      : b05111
Date          : Sep-16-2015
Notes         : Function handles Machine_check_handler
*******************************************************************************/
//__interrupt
void Machine_check_handler(void)
{
#if defined(CTI_Z4_0)
    uint32_t MCAR_VAL = MFSPR(573);  //read MCAR register. according S32R274RM page:313(Table 13-2. Special Purpose Registers)
    if(0xFD0000 <= MCAR_VAL && MCAR_VAL <= 0xFFFFFF)    //check ECC error between 0xFD0000-0xFFFFFF (according flash.h blackbox used area).
    {
        MTSPR(572, 0x0);  //clear MCSR register.
        MTSPR(573, 0x0);  //clear MCAR register.
    }

	PPCASM(" wrteei 1 ");  //enable ISR, let FCCU into alarm_isr.
	uint32_t stk = (uint32_t)__builtin_frame_address(1);
    /* If error was injected, disable EIM */
    if (EIM.EIMCR.R)
    {
        EIM.EIMCR.R = 0; // global error injection
    }

	PPCASM(" wrteei 0 ");
	console_flush();
	PRINTF_FORCE("\n\nivor stack: %08lX %08lX\n", (uint32_t)__SP_INIT, stk);
	mem_dump_force(stk, (uint32_t)__SP_INIT-stk);
	console_force("\n\n");
	PPCASM(" wrteei 1 ");
	console_flush();
	while(TRUE);
#elif defined(CTI_Z7_0)
	/* Write stack information into shared memory */
	stkinfo_data.z70_start_addr  = (uint32_t)__SP_INIT;
	stkinfo_data.z70_stack_head = (uint32_t)__builtin_frame_address(1);
	stkinfo_data.z70_sync = 1;
	while(TRUE);
#elif defined(CTI_Z7_1)
	/* Write stack information into shared memory */
	stkinfo_data.z71_start_addr  = (uint32_t)__SP_INIT;
	stkinfo_data.z71_stack_head = (uint32_t)__builtin_frame_address(1);
	stkinfo_data.z71_sync = 1;
	while(TRUE);
#endif
}

void hangup(char** args, int count)
{
	if (count > 1)
	{
		#if defined(CTI_Z4_0)
		console_flush();
		#endif

		uint8_t command = (uint8_t)strtoul(args[1], NULL, 10);
		switch(command){
		case 1 :
		default :
			ILLEGAL_PROC(NULL);
			break;
		case 2 :
			while(1);
			break;
		}
	}
	else
	{
	    reset_system();
	}
}
#if defined(CTI_Z7_0) || defined(CTI_Z7_1)
/******************************************************************************
Function : dump memory in hex word(32bit) format
******************************************************************************/
void dump_word(char** args, int count)
{
	int cnt = 0;
	uint32_t addr, *d;

	addr = (uint32_t)strtoul(args[1], NULL, 16);
	if(count >= 3){
		count = (uint32_t)strtoul(args[2], NULL, 16);
		if(count > 0x1000)
			count = 0x1000;
	}

	if(count < 0x200)
		count = 0x200;

	addr &= 0xFFFFFFFC; // in case not aligned
	d = (uint32_t*) addr;
	put_string("Add/Offs 00000000 00000004 00000008 0000000C 00000010 00000014 00000018 0000001C\n");
	while(cnt < count) {
		PRINTF("%08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n", (uint32_t)d, d[0],d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
		d += 8;
		cnt += 0x20;
	}
}

///******************************************************************************
//Function : velocity range shift
//*******************************************************************************/
//void vrs_proc(char** args, int count)/
//{
//    track_vrs(atoi(args[1]));//
//}

#endif
