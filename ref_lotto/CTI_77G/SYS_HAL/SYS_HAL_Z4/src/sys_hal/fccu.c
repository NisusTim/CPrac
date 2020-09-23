//#############################################################################
//	FILE:		fccu.c
//	PROJECT:	RRU_Doplhin
//	AUTHOR:		Yale.Ge
//=============================================================================
//	REVISION HISTORY
//=============================================================================
//	VERSION		DATE		CHANGES
//	VER 01.00	04 Sep 2016	- Initial version from Florian.Ebert
//#############################################################################
#include "sys_shared.h"
#include "can_cubtek.h"

extern void __SP_INIT(void);

#define FCCU_RECORD_VALUE_ERASED		0x5A5A55AA24681357
#define FCCU_RECORD_VALUE_FAILED		0xA5A5AA5513572468

//fccu_record_p	available=(fccu_record_p)EE_ADDR_FCCU_START;

typedef struct {
	uint64_t	mask;
	uint32_t	ncfs[4];
	uint32_t	stack[8];
}fccu_record_t,*fccu_record_p;

stack_info_t __attribute__((section(".stack_info")))stkinfo_data;  //Z70 & Z71 stack_address_info
fccu_record_t		__attribute__ ((section(".monitor"))) fccu_record;
fccu_record_p		available=&fccu_record;

int rmtp_send_fccu_status_message(uint8_t *data, uint8_t size);
int rmtp_send_stack_dump_message(uint8_t *data, uint8_t size);

#define CODE_ADDR_START		0x1000000
#define CODE_ADDR_END		0x1180000
void fccu_record_check(void)
{
	if(RGM.FES.B.F_FCCU_HARD | RGM.FES.B.F_FCCU_SOFT)
	{
		rmtp_send_fccu_status_message((uint8_t*)(available->ncfs), member_size(fccu_record_t, ncfs));
		rmtp_send_stack_dump_message((uint8_t*)(available->stack), member_size(fccu_record_t, stack));

		set_monitoring_result_by_id(MONITOR_ID_FCCU, MONITOR_RESULT_FAILED, MONITOR_RESULT_CODE_ERROR);
		PRINTF("fccu: error(RGM.FES = 0x%08lX)\n", RGM.FES.R);
	}
	else
	{
		set_monitoring_result_by_id(MONITOR_ID_FCCU, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
		PRINTF("fccu: passed(RGM.FES = 0x%08lX)\n", RGM.FES.R);
	}

	RGM.FES.R |= RGM.FES.R;
}

static void fccu_record_stack(uint32_t *stack)
{
	uint32_t* dest = (uint32_t*)available->stack, *end=stack+((uint32_t)__SP_INIT-(uint32_t)stack)/sizeof(uint32_t);
	int cnt = 8;

	while(stack < end) {
		if(*stack < CODE_ADDR_END && *stack >= CODE_ADDR_START){
			*dest = *stack;
			dest++;
			cnt--;
			if(cnt == 0)
				break;
		}
		stack++;
	}
	available->mask = FCCU_RECORD_VALUE_FAILED;
}

//=============================================================================
// CONTROL FUNCTIONS
//=============================================================================
uint32_t FCCU_read_status(void)
{
	// get FCCU status
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	FCCU.CTRL.R = 3;									// read FCCU status register
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 0x100;				// if operation not successful return error code 0x100
	return FCCU.STAT.B.STATUS;							// assign FCCU status to local variable
}
uint32_t FCCU_enter_normal(void)
{
	FCCU.CTRLK.R = 0x825A132B;							// write key for OP2
	FCCU.CTRL.R = 2;									// set FCCU into NORMAL state
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 1;					// if operation not successful return error code 1
	return 0;											// return 0 if successful
}
uint32_t FCCU_enter_config(void)
{
	FCCU.CTRLK.R = 0x913756AF;							// write key for OP1
	FCCU.CTRL.R = 1;									// set FCCU into CONFIG state
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 1;					// if operation not successful return error code 1
	return 0;											// return 0 if successful
}
uint32_t FCCU_read_ncfs(uint32_t reg_num)
{
	FCCU.CTRL.R = 10;									// read FCCU NCF status register
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 0xFFFFFFFF;		// if operation not successful return error code all 1
	return FCCU.NCF_S[reg_num].R;						// return register content
}
uint32_t FCCU_read_n2af(void)
{
	FCCU.CTRL.R = 4;									// read N2AF status register
	while (FCCU.CTRL.B.OPR != 0);						// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 0xFFFFFFFF;		// if operation not successful return error code all 1
	return FCCU.N2AF_STATUS.R;							// assign FCCU status to local variable
}
uint32_t FCCU_clear_ncfs(uint32_t reg_num, uint32_t mask)
{
	FCCU.NCFK.R = 0xAB3498FE;							// write key into NCF key register
	FCCU.NCF_S[reg_num].R = mask;						// clear flags
	while (FCCU.CTRL.B.OPR);							// wait for operation to complete
	if (FCCU.CTRL.B.OPS != 3) return 1;					// if operation not successful return error code 3
	return 0;											// return 0 if successful
}
uint32_t FCCU_cfg(void)
{
	uint32_t i;
	uint32_t fccu_status;
	stkinfo_data.z70_sync = 0;  //clear z70 stack sync flag
	stkinfo_data.z71_sync = 0;  //clear z71 stack sync flag

	fccu_status = FCCU_read_status();					// get FCCU status
	if (fccu_status > 0xFF) return 1;					// return error code 1 if get status operation failed

	// check for pending faults and clear them
	if (fccu_status) {									// check if not in NORMAL state
		for (i = 0; i < 4; i++) {						// check/clear all four available NCF status registers
			if (FCCU_read_ncfs(i)) 						// read NCF status register and clear flags if necessary
				FCCU_clear_ncfs(i, 0xFFFFFFFF);
		}
		if (FCCU_read_status()) return 2;				// return error code 4 if status not NORMAL
	}

	// put FCCU in config state
	FCCU.TRANS_LOCK.R = 0xBC;							// unlock configuration
	if (FCCU_enter_config()) return 3;					// set FCCU into CONFIG state, if operation not successful return error code 5
	if (FCCU_read_status() != 1) return 4;				// check that FCCU is in config state, if not return error code 6

	// configure FCCU
	FCCU.CFG.R = 0x0100003F;							// set FCCU_SET_AFTER_RESET, set FOP max
	FCCU.NCF_E[0].R = 0xFFFFFFFE;						// reset value 0xFFFF_FFFF, disable TSENSE0/1
	FCCU.NCF_E[1].R = 0x7FFDFFFF;						// reset value 0x0000_3FFF, enable all XBAR, PRAMCtrl and test control faults
	FCCU.NCF_E[2].R = 0xF90000C0;						// keep reset value 0xFF80_00C0
	FCCU.NCF_E[3].R = 0xFFFFFFFF;						// keep reset value 0xFFFF_FFFF
	FCCU.IRQ_ALARM_EN[0].R = 0xFFFFFFFF;				// enable ALRAM IRQ for all enabled NCF except SWTx
	FCCU.IRQ_ALARM_EN[1].R = 0x7FFDFFFF;				//
	FCCU.IRQ_ALARM_EN[2].R = 0xF90000C0;				//
	FCCU.IRQ_ALARM_EN[3].R = 0xFFFFFFFF;				//
	FCCU.NCF_TOE[0].R = 0xFFFFFFFF;
	FCCU.NCF_TOE[1].R = 0xFFFFFFFF;
	FCCU.NCF_TOE[2].R = 0xFFFFFFFF;
	FCCU.NCF_TOE[3].R = 0xFFFFFFFF;
	FCCU.NCF_TO.R = 0x726F69;							// FCCU alarm max recovery time 500ms = 66.67ns * 7499625
	FCCU.NCFS_CFG[0].R = 0xAAAAAAAA;					// configure SWTx to generate long functional reset
	FCCU.NCFS_CFG[1].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[2].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[3].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[4].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[5].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[6].R = 0xAAAAAAAA;
	FCCU.NCFS_CFG[7].R = 0xAAAAAAAA;

	// put FFCU back in normal state
	if (FCCU_enter_normal()) return 5;					// set FCCU in normal state, if operation not successful return error code 7
	if (FCCU_read_status()) return 6;					// check that NORMAL state is entered, if not return operation status

	PRINTF("fccu: inited\n");

	INTC.PSR[488].R = 0x8006; 							// register interrupt handler
	INTC.PSR[489].R = 0x8006; 							// register interrupt handler

	return 0;											// return 0 if successful
}
//=============================================================================
// INTERRUPT SERVICE ROUTINES
//=============================================================================
void FCCU_alarm_isr(void)
{
	PPCASM(" wrteei 0 ");
	uint32_t stk = (uint32_t)__builtin_frame_address(1);
	uint32_t i,*ncfs=available->ncfs;

	union data_word {
		uint32_t uint32;
		char char32[4];
	} fccu_n2af_status;

	while (FCCU.CTRL.B.OPR != 0);							// wait for operation to complete
	for (i = 0; i < 4; i++)									// read out all four available NCF status registers
		ncfs[i] = FCCU_read_ncfs(i);

	fccu_n2af_status.uint32 = FCCU_read_n2af();				// copy FCCU N2AF register content to local variable

	console_flush();

	if(ncfs[0] & 0xC00000){  //check flash uncorrectable/correctable ECC error.
		uint32_t flash_error_addr = MEMU.FLASH_UNCERR_ADDR.R;  //read where ECC error.

		if(ncfs[0] & 0x20000){  //check ram uncorrectable ECC error.
			MEMU.ERR_FLAG.B.SR_UCE = 1;  //clear MEMU System RAM ECC Uncorrectable Error Detect flag.
		}

		PRINTF_FORCE("\n flash ECC error (0x%08lX)\n", flash_error_addr);

		if(0xFD0000 <= flash_error_addr && flash_error_addr <= 0xFFFFFF)  //check ECC error between 0xFD0000-0xFFFFFF (according flash.h blackbox used area).
		{
			flash_erase_bio(flash_error_addr, 0);  //erase flash error area
		}

		MEMU.ERR_FLAG.B.F_CE = 1;   //clear MEMU Flash ECC Correctable Error Detect flag.
		MEMU.ERR_FLAG.B.F_UCE = 1;  //clear MEMU Flash ECC Uncorrectable Error Detect flag.

		console_flush();
		reset_system();  //reset system after flash erase.
	}

	if (fccu_n2af_status.uint32) {
		fccu_n2af_status.uint32 -= 1;						// correct error number to be compliant to NCF#

		fccu_record_stack((uint32_t*)stk);
		PRINTF_FORCE("\nfccu alarm[127..0]: %08lX %08lX %08lX %08lX\n", ncfs[3],
				ncfs[2], ncfs[1], ncfs[0]);

		console_force("\n Z74 Memory dump \n");
		mem_dump_force(stk, (uint32_t)__SP_INIT-stk);
		if((ncfs[0] & (0x1 << 14)) | (ncfs[2] & (0x1 << 21))){  //SWT_1 Reset request NFC[14] & Z70 Machine check condition NFC[85]
			while(stkinfo_data.z70_sync == 0);  //wait for z70 stack sync flag
			if(ncfs[2] & (0x1 << 21))
				PRINTF_FORCE("\n Z70_ivor stack: %08lX %08lX\n", (uint32_t)stkinfo_data.z70_start_addr, stkinfo_data.z70_stack_head);
			console_force("\n Z7_0 Memory dump \n");
			mem_dump_force(stkinfo_data.z70_stack_head, (uint32_t)stkinfo_data.z70_start_addr - stkinfo_data.z70_stack_head);
		}
		if((ncfs[0] & (0x1 << 15)) | (ncfs[2] & (0x1 << 22))){  //SWT_2 Reset request NFC[15] & Z71 Machine check condition NFC[86]
			while(stkinfo_data.z71_sync == 0);  //wait for z71 stack sync flag
			if(ncfs[2] & (0x1 << 22))
				PRINTF_FORCE("\n Z71_ivor stack: %08lX %08lX\n", (uint32_t)stkinfo_data.z71_start_addr, stkinfo_data.z71_stack_head);
			console_force("\n Z7_1 Memory dump \n");
			mem_dump_force(stkinfo_data.z71_stack_head, (uint32_t)stkinfo_data.z71_start_addr - stkinfo_data.z71_stack_head);
		}
		console_force("\n");

		while (FCCU_read_status()) {
			for (i = 0; i < 4; i++) {						// check/clear all four available NCF status registers
				if (FCCU_read_ncfs(i)) 						// read NCF status register and clear flags if necessary
					FCCU_clear_ncfs(i, 0xFFFFFFFF);
			}
		}
	}
	PPCASM(" wrteei 1 ");
}

void FCCU_misc_isr(void)
{
	uint32_t i;
	uint32_t fccu_ncf_status[4];
	union data_word {
		uint32_t uint32;
		char char32[4];
	} fccu_n2af_status;

	while (FCCU.CTRL.B.OPR != 0);							// wait for operation to complete
	for (i = 0; i < 4; i++)									// read out all four available NCF status registers
		fccu_ncf_status[i] = FCCU_read_ncfs(i);

	fccu_n2af_status.uint32 = FCCU_read_n2af();				// copy FCCU N2AF register content to local variable

	if (fccu_n2af_status.uint32) {
		fccu_n2af_status.uint32 -= 1;						// correct error number to be compliant to NCF#

		PRINTF_FORCE("\nfccu misc[127..0]: %08lX %08lX %08lX %08lX\n\n", fccu_ncf_status[3],
				fccu_ncf_status[2], fccu_ncf_status[1], fccu_ncf_status[0]);

		while (FCCU_read_status()) {
			for (i = 0; i < 4; i++) {						// check/clear all four available NCF status registers
				if (FCCU_read_ncfs(i)) 						// read NCF status register and clear flags if necessary
					FCCU_clear_ncfs(i, 0xFFFFFFFF);
			}
		}
	}
}

void FCCU_mcu_error_passed(void)
{
    set_monitoring_result_by_id(MONITOR_ID_FCCU, MONITOR_RESULT_PASSED, MONITOR_RESULT_CODE_PASSED);
}
