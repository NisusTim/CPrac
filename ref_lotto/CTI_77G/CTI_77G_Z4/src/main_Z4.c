/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "sys_shared.h"
#include "isotp.h"
#include "controller.h"
#include "customer.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "Dcm.h"
#include "Com.h"
#include "Nvm.h"
#include "App_ComTx.h"
#include "monitor_task.h"
#include "cubtek_monitor_handler.h"
#include "can_cubtek.h"
#include "blackbox_api.h"
#include "fbl_parameter.h"

extern uint32_t FCCU_cfg(void);
extern void fccu_record_check(void);
extern void xcptn_xmpl(void);
extern void pass_init(void);

static sys_state_e sys_state = SYST_INIT;
void sys_state_test(char** args, int count){
	sys_state_e s = SYST_INVALID;
	if(count > 1)
		s = strtoul(args[1], NULL, 16);
	if(s < SYST_INVALID)
		sys_state_set(s);
	PRINTF("syst %d\n", sys_state);
}
sys_state_e sys_state_get(void) {return sys_state;}
void sys_state_set(sys_state_e s)
{
	if (s < SYST_DONE)
		sys_state = s;

	switch (sys_state) {
	case SYST_ACTIVE :
		customer_init();
#if 0
		radar_warning_timer_init();
#endif
		break;
	case SYST_PAUSED:
		frame_pause(NULL,0);
		break;
	default:
		break;
	}
}

#ifdef ENABLE_BSW_UDS_NM
void bsw_uds_nm_sys_init()
{
	const uint8 MASTER_DEVICE_ID = 0; //1
	uint8 *data = cubtek_faw_did_g_security_acess_attemp_number_get();
	const product_info_t* prod = product_info_get();

	if(MASTER_DEVICE_ID == prod->device_id)
	{
		/*Need to load securityAcessAttempNumber from eeprom*/
		gSecurityAcessAttempNumber[0] = data[0];		
		Can_Init();
		CanIf_Init();
		CanIf_SetControllerMode(0, CANIF_CS_STARTED);
		Can_DisableGlobalInterrupt();
		Can_EnableGlobalInterrupt();
		CanTp_Init(&CanTp_Cfg);
		Dcm_Init(DCM_NULL);
		Com_Init();
		// CanNm_GotoMode(0,GOTO_AWAKE);

		NvM_Init();
		Dem_Init();

		Com_RxStart();
		Com_TxStop();
		App_ComTx_Init();

		cubtek_faw_did_ds_can_status_set(CAN_EnRx_DisTx);

		custom_timer_init(0);
	}
}
#endif

/* --------------------------------------------------------------------
 * Main
 * -------------------------------------------------------------------*/
int __attribute__((section(".z4main")))main(void)
{
	xcptn_xmpl();              	// * Configure and Enable Interrupts * //
	#ifdef ENABLE_SWT
	FCCU_cfg();
	#endif
	flash_init();
	tsens_init();
	pars_init(FALSE, FALSE);
	hw_ver_info_init();
	FS8x_init();
	ioctrl_init();

	can_init();

	timer_init(0);

	ipc_handle_init();
	console_init();

	product_init();
#ifdef ENABLE_BSW_UDS_NM
	cubtek_did_init();
	bsw_uds_nm_sys_init();
#endif

	ADC_Init();

	monitor_task_init(INTERNAL_TIMER, PROC_MAX_10_MS);
	cubtek_monitor_init(TIMER_100_MS_TICKS);
	fccu_record_check();

	rmtp_init();

	na_init();
	SPI_init();
	init_TEF810x();
	CSI2_init();
	frame_init(); // calibration may access flash write
	vehicle_init();
	tracking_init();
	pass_init();
	fbl_spec_init();

	if(SUCCESSED == upd_init()){
		sys_state_set(SYST_READY);
		ipc_sync_ready(NULL);
	}

	ism330dlc_i2c_init();
	init_ism330dlc();
	put_string(MSG_PROMPT);
#if ISOTP_EN
	isotp_init_link();
#endif
	controller_init();
	Blackbox_Init();
#ifdef ENABLE_SWT
	SWT0_Init();
#endif

	pars_insts_share();

	// * Loop forever * //
	while(sys_state < SYST_DONE) {

#ifdef ENABLE_SWT
		clear_SWT0_counter();
#endif
		fs8x_wd_handle(fs8xNormal);
		event_handle();
		IPC_HANDLE_MSG_Z70();
		IPC_HANDLE_MSG_Z71();
	}
	return 0;
}

