/*
 * pass.c
 *
 *  Created on: 2017Äê10ÔÂ2ÈÕ
 *      Author: user
 */

#include "sys_shared.h" /* include peripheral declarations */

#define LIFE_CYCLE_SLOT_1_0			0x400210
#define LIFE_CYCLE_SLOT_1_1			0x400218
#define LIFE_CYCLE_SLOT_2_0			0x400220
#define LIFE_CYCLE_SLOT_2_1			0x400228
#define LIFE_CYCLE_SLOT_3_0			0x400230
#define LIFE_CYCLE_SLOT_3_1			0x400238
#define LIFE_CYCLE_SLOT_4_0			0x400240
#define LIFE_CYCLE_SLOT_4_1			0x400248
#define LIFE_CYCLE_PROGRAM_MAGIC	0x55AA50AF55AA50AF

void pass_oem_set(void)
{

	utest_write64_bio(LIFE_CYCLE_SLOT_1_1, LIFE_CYCLE_PROGRAM_MAGIC);
	utest_write64_bio(LIFE_CYCLE_SLOT_2_0, LIFE_CYCLE_PROGRAM_MAGIC);
}

void pass_field_set(void)
{
	utest_write64_bio(LIFE_CYCLE_SLOT_1_1, LIFE_CYCLE_PROGRAM_MAGIC);
	utest_write64_bio(LIFE_CYCLE_SLOT_2_0, LIFE_CYCLE_PROGRAM_MAGIC);
	utest_write64_bio(LIFE_CYCLE_SLOT_2_1, LIFE_CYCLE_PROGRAM_MAGIC);
	utest_write64_bio(LIFE_CYCLE_SLOT_3_0, LIFE_CYCLE_PROGRAM_MAGIC);
}

#define JTAG_PASSWORD			0x1234567812345678
#define JTAG_PASSWORD_0			0x400120
#define JTAG_PASSWORD_1			0x400128
#define JTAG_PASSWORD_2			0x400130
#define JTAG_PASSWORD_3			0x400138

#define PASS_PASSWORD_GROUP0 	0x1234567812345678
#define PASS_PASSWORD_GROUP0_0	0x400140
#define PASS_PASSWORD_GROUP0_1	0x400148
#define PASS_PASSWORD_GROUP0_2	0x400150
#define PASS_PASSWORD_GROUP0_3	0x400158
#define PASS_PASSWORD_GROUP1 	0x1234567812345678
#define PASS_PASSWORD_GROUP1_0	0x400160
#define PASS_PASSWORD_GROUP1_1	0x400168
#define PASS_PASSWORD_GROUP1_2	0x400170
#define PASS_PASSWORD_GROUP1_3	0x400178
#define PASS_PASSWORD_GROUP2 	0x1234567812345678
#define PASS_PASSWORD_GROUP2_0	0x400180
#define PASS_PASSWORD_GROUP2_1	0x400188
#define PASS_PASSWORD_GROUP2_2	0x400190
#define PASS_PASSWORD_GROUP2_3	0x400198
#define PASS_PASSWORD_GROUP3 	0x1234567812345678
#define PASS_PASSWORD_GROUP3_0	0x4001A0
#define PASS_PASSWORD_GROUP3_1	0x4001A8
#define PASS_PASSWORD_GROUP3_2	0x4001B0
#define PASS_PASSWORD_GROUP3_3	0x4001B8

void pass_set_passwd(void)
{
	utest_write64_bio(JTAG_PASSWORD_0, JTAG_PASSWORD);
	utest_write64_bio(JTAG_PASSWORD_1, JTAG_PASSWORD);
	utest_write64_bio(JTAG_PASSWORD_2, JTAG_PASSWORD);
	utest_write64_bio(JTAG_PASSWORD_3, JTAG_PASSWORD);
	utest_write64_bio(PASS_PASSWORD_GROUP0_0, PASS_PASSWORD_GROUP0);
	utest_write64_bio(PASS_PASSWORD_GROUP0_1, PASS_PASSWORD_GROUP0);
	utest_write64_bio(PASS_PASSWORD_GROUP0_2, PASS_PASSWORD_GROUP0);
	utest_write64_bio(PASS_PASSWORD_GROUP0_3, PASS_PASSWORD_GROUP0);
	utest_write64_bio(PASS_PASSWORD_GROUP1_0, PASS_PASSWORD_GROUP1);
	utest_write64_bio(PASS_PASSWORD_GROUP1_1, PASS_PASSWORD_GROUP1);
	utest_write64_bio(PASS_PASSWORD_GROUP1_2, PASS_PASSWORD_GROUP1);
	utest_write64_bio(PASS_PASSWORD_GROUP1_3, PASS_PASSWORD_GROUP1);
	utest_write64_bio(PASS_PASSWORD_GROUP2_0, PASS_PASSWORD_GROUP2);
	utest_write64_bio(PASS_PASSWORD_GROUP2_1, PASS_PASSWORD_GROUP2);
	utest_write64_bio(PASS_PASSWORD_GROUP2_2, PASS_PASSWORD_GROUP2);
	utest_write64_bio(PASS_PASSWORD_GROUP2_3, PASS_PASSWORD_GROUP2);
	utest_write64_bio(PASS_PASSWORD_GROUP3_0, PASS_PASSWORD_GROUP3);
	utest_write64_bio(PASS_PASSWORD_GROUP3_1, PASS_PASSWORD_GROUP3);
	utest_write64_bio(PASS_PASSWORD_GROUP3_2, PASS_PASSWORD_GROUP3);
	utest_write64_bio(PASS_PASSWORD_GROUP3_3, PASS_PASSWORD_GROUP3);
}

void pass_unlock_group0(void)
{
	PASS.CHSEL.B.GRP=0;
	PASS.CIN[0].R = 0x12345678;
	PASS.CIN[1].R = 0x12345678;
	PASS.CIN[2].R = 0x12345678;
	PASS.CIN[3].R = 0x12345678;
	PASS.CIN[4].R = 0x12345678;
	PASS.CIN[5].R = 0x12345678;
	PASS.CIN[6].R = 0x12345678;
	PASS.CIN[7].R = 0x12345678;
	PASS.PG[0].LOCK3.B.DBL = 0;
	PRINTF("unlock group0 lock3 DBL\n");
}

void pass_unlock_group1(void)
{
	PASS.CHSEL.B.GRP=1;
	PASS.CIN[0].R = 0x12345678;
	PASS.CIN[1].R = 0x12345678;
	PASS.CIN[2].R = 0x12345678;
	PASS.CIN[3].R = 0x12345678;
	PASS.CIN[4].R = 0x12345678;
	PASS.CIN[5].R = 0x12345678;
	PASS.CIN[6].R = 0x12345678;
	PASS.CIN[7].R = 0x12345678;
	PASS.PG[1].LOCK3.B.DBL = 0;
	PRINTF("unlock group1 lock3 DBL\n");
}

void pass_unlock_group2(void)
{
	PASS.CHSEL.B.GRP=2;
	PASS.CIN[0].R = 0x12345678;
	PASS.CIN[1].R = 0x12345678;
	PASS.CIN[2].R = 0x12345678;
	PASS.CIN[3].R = 0x12345678;
	PASS.CIN[4].R = 0x12345678;
	PASS.CIN[5].R = 0x12345678;
	PASS.CIN[6].R = 0x12345678;
	PASS.CIN[7].R = 0x12345678;
	PASS.PG[2].LOCK3.B.DBL = 0;
	PRINTF("unlock group2 lock3 DBL\n");
}

void pass_unlock_group3(void)
{
	PASS.CHSEL.B.GRP=3;
	PASS.CIN[0].R = 0x12345678;
	PASS.CIN[1].R = 0x12345678;
	PASS.CIN[2].R = 0x12345678;
	PASS.CIN[3].R = 0x12345678;
	PASS.CIN[4].R = 0x12345678;
	PASS.CIN[5].R = 0x12345678;
	PASS.CIN[6].R = 0x12345678;
	PASS.CIN[7].R = 0x12345678;
	PRINTF("unlock group3 lock3 \n");
}

void pass_set_group_lock_val(int group, int lock, uint32_t val)
{
	if(group <= 3)
	{
		PASS.CHSEL.B.GRP=group;
		if(lock ==  0)
			PASS.PG[group].LOCK0.R = val;
		else if(lock == 1)
			PASS.PG[group].LOCK1.R = val;
		else if(lock == 2)
			PASS.PG[group].LOCK2.R = val;
		else if(lock == 3)
			PASS.PG[group].LOCK3.R = val;
		PRINTF("set group%d lock%d reg=%lu \n",group, lock, val);
	}
}

void pass_print_group_lock_val(int group, int lock)
{
	uint32_t val = 0;
	if(group <= 3)
	{
		PASS.CHSEL.B.GRP=group;
		if(lock ==  0)
			val = PASS.PG[group].LOCK0.R;
		else if(lock == 1)
			val = PASS.PG[group].LOCK1.R;
		else if(lock == 2)
			val = PASS.PG[group].LOCK2.R;
		else if(lock == 3)
			val = PASS.PG[group].LOCK3.R;

		PRINTF("group%d lock%d reg=%lu \n",group, lock, val);
	}
}

static uint32_t find_avail_DCF_record()
{
	uint64_t* ptemp = (uint64_t*) 0x400300;

	while((*ptemp != 0xffffffffffffffff) && (ptemp <  (uint64_t*)0x400B00))
	{
		ptemp++;
	}

	if(ptemp >=  (uint64_t*)0x400B00)
		return 0;
	else
		return (uint32_t) ptemp;
}

void show_PASS_lcstat(void)
{
	if(PASS.LCSTAT.B.CNS == 1)
		PRINTF("CNS = 1\n");
	else
		PRINTF("CNS = 0\n");
	if(PASS.LCSTAT.B.JUN == 1)
		PRINTF("JUN = 1\n");
	else
		PRINTF("JUN = 0\n");
	if(PASS.LCSTAT.B.TME == 1)
		PRINTF("TME = 1\n");
	else
		PRINTF("TME = 0\n");

	switch(PASS.LCSTAT.B.LIFE)
	{
	case 0:
		PRINTF("Failure Analysis\n");
		break;
	case 2:
		PRINTF("OEM Production\n");
		break;
	case 3:
		PRINTF("Customer Delivery\n");
		break;
	case 6:
		PRINTF("MCU Production\n");
		break;
	case 7:
		PRINTF("In Field\n");
		break;
	default:
		PRINTF("Reserved\n");
	}

	PRINTF("PASS.PG[0].LOCK3.B.DBL = %d\n", PASS.PG[0].LOCK3.B.DBL);
	PRINTF("PASS.PG[1].LOCK3.B.DBL = %d\n", PASS.PG[1].LOCK3.B.DBL);
	PRINTF("PASS.PG[2].LOCK3.B.DBL = %d\n", PASS.PG[2].LOCK3.B.DBL);
	PRINTF("PASS.PG[3].LOCK3.B.DBL = %d\n", PASS.PG[3].LOCK3.B.DBL);

}

void write_PASS_group()
{
	uint32_t pWDCF = find_avail_DCF_record();

	utest_write64_bio(pWDCF, 0x0000000000800100);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800104);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800108);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x400000000080010C);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800110);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800114);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800118);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x000000000080011C);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800120);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800124);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800128);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x000000000080012C);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800130);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800134);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x0000000000800138);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x000000000080013C);
	pWDCF = pWDCF + 8;
	utest_write64_bio(pWDCF, 0x00000000008000B0);
}

/*******************************************************************************************
Configuration steps for the PASS module to enable password protection for debugger and flash
1. Program JTAG Password and PASS Group 0-3 Passwords
	Fixed location in UTEST flash 0x0040_0120 to 0x0040_01BF

2. Program PASS DCF records to set PASS Group 0-3 lock status
	DCFs programmed in UTEST region beyond 0x0040_0300
	PASS_LOCK DCFs control debugger and flash access
3. Program Censorship DCF records
4. Advance Life Cycle from Customer Delivery to OEM Production
********************************************************************************************/
void write_n_enable_pass_module()
{
	 if(PASS.LCSTAT.B.LIFE == 3)
	 {
		pass_set_passwd();
	 	write_PASS_group();
	 	pass_field_set();
	 }
	 else
	 {
		 show_PASS_lcstat();
	 }
}

int check_DBL_lock(void)
{
	int lock = 0; //unlock

	if(PASS.LCSTAT.B.CNS == 1)
	{
		switch(PASS.LCSTAT.B.LIFE)
		{
			case 2:
				PRINTF("OEM Production\n");
				lock = 1;
				break;
			case 7:
				PRINTF("In Field\n");
				lock = 1;
				break;
		}
	}
	if(lock == 1)
		PRINTF("locked\n");
	else
		PRINTF("unlock\n");
	
	return lock;
}

int get_LIFE_state(void)
{
	return PASS.LCSTAT.B.LIFE;
}

int get_cns_state(void)
{
	return PASS.LCSTAT.B.CNS;
}

void pass_func(char** args, int count)
{
	if(count >= 2){
		if(strncmp("state", args[1], 5) == 0){
			show_PASS_lcstat();
		}
		else if(strncmp("oem", args[1], 3) == 0){
			pass_oem_set();
		}
		else if(strncmp("field", args[1], 5) == 0){
			pass_field_set();
		}
		else if(strncmp("ulockg0", args[1], 7) == 0){
			pass_unlock_group0();
		}
		else if(strncmp("ulockg1", args[1], 7) == 0){
			pass_unlock_group1();
		}
		else if(strncmp("ulockg2", args[1], 7) == 0){
			pass_unlock_group2();
		}
		else if(strncmp("ulockg3", args[1], 7) == 0){
			pass_unlock_group3();
		}
		else if(strncmp("writepw", args[1], 7) == 0){
			pass_set_passwd();
		}
		else if(strncmp("writegroup", args[1], 10) == 0){
			write_PASS_group();
		}
		else if(strncmp("wdcf", args[1], 4) == 0){
			if(count >= 3){
				uint64_t data = strtoull(args[2], NULL, 16);
				utest_write64_bio(find_avail_DCF_record(), data);
			}
		}
		else if(strncmp("setlock", args[1], 7) == 0){
			if(count >= 5){
				uint32_t group = strtoul(args[2], NULL, 10);
				uint32_t lock = strtoul(args[3], NULL, 10);
				uint32_t val = strtoul(args[4], NULL, 10);
				pass_set_group_lock_val(group, lock, val);
			}
		}
		else if(strncmp("getlock", args[1], 7) == 0){
			if(count >= 5){
				uint32_t group = strtoul(args[2], NULL, 10);
				uint32_t lock = strtoul(args[3], NULL, 10);
				pass_print_group_lock_val(group, lock);
			}
		}
		else if(strncmp("enable_pass", args[1], 11) == 0){
			write_n_enable_pass_module();
		}
		else if(strncmp("dbl", args[1], 3) == 0){
			check_DBL_lock();
		}
	}
	else
	{
	    PRINTF("pass dbl\n");
	    check_DBL_lock();
	}
}

void pass_init(void)
{
	console_command_reg("pass", pass_func);
}
