/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "sys_shared.h"
#include "upgrade.h"
#include "track_lib.h"

#if JSON_LIST_EN
#include "json_debug_info.h"
#endif

extern void __IMG_END_ADDR(void);
extern void __start(void);
extern void __IMG_MAGIC_Z70(void);

const image_header_t __attribute__ ((section(".z70imghdr"))) z70_image_header = {
		.rchw1 = 0xFFFFFFFF,
		.rchw2 = (uint32_t)__start,
		.checksum = 0xFFFFFFFF,
		.magic = (uint32_t)__IMG_MAGIC_Z70,
		.addrs = {IMGE_ADDR_BLDR,IMAGE_ADDR_Z70,IMAGE_ADDR_Z71},
		.end = (uint32_t)__IMG_END_ADDR,
		.rev = {.major			= 0,
				.product		= 0,
				.cusid			= 0,
				.minor			= 0,
				.build			= 0,
				.maintenance	= 0,
				.svn=0},
		.rv = "31010",
		.rd = "20191010",
		.key = 0x13579bdf};

void xcptn_xmpl(void);

extern void tracking_frame_data_init(void *data);
extern void tracking_frame_rate_set(int);
extern void vehicle_status_fun(void*);
extern void tracking_frame_next(void*);
extern void get_yaw_rate_type(void* type);
extern void get_rf_gain(void* data);
extern void tracking_process(void *);
extern void tracking_pars_init(void);
extern void app_dcm_data_init(void *data);

/*******************************************************************************
Function Name : main
Engineer      :
Date          : 06-29-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Z7-0 main function
Issues        : NONE
*******************************************************************************/
int main(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */
	console_init();
	ipc_reg_msg(MSG_FRAME_DATA, "fdata", (msg_proc_p)tracking_frame_data_init);	
	ipc_reg_msg(MSG_TARGETS_LIST, "tgtlist", (msg_proc_p)tracking_process);
	ipc_reg_msg(MSG_FRAMERATE, "fs", (msg_proc_p)tracking_frame_rate_set);
	ipc_reg_msg(MSG_FRAME_NEXT, "nxt", (msg_proc_p)tracking_frame_next);
	ipc_reg_msg(MSG_VEHICLE_STATUS, "vehsts", (msg_proc_p)vehicle_status_fun);
	ipc_reg_msg(MSG_YAW_ONBOARD, "yaw", (msg_proc_p)get_yaw_rate_type);
	ipc_reg_msg(MSG_RF_GAIN_PARS, "rfgain", (msg_proc_p)get_rf_gain);
	ipc_reg_msg(MSG_AUTO_HORI_ALIGN, "auto_calib_start", (msg_proc_p)auto_calibration_handler);
	ipc_reg_msg(MSG_APP_DCM_DATA, "app_dcm_shared_data", (msg_proc_p)app_dcm_data_init);

	vehicle_init();
	pars_init();
	product_init();
	tracking_pars_init();

#ifdef ENABLE_SWT
	SWT1_Init();
#endif

	ipc_sync_ready(NULL);
#if JSON_LIST_EN
	init_json_dbg_info();
#endif

	/* Loop forever */
	for(;;) {
#ifdef ENABLE_SWT
		clear_SWT1_counter();
#endif
	   	IPC_HANDLE_MSG_Z40();
	   	IPC_HANDLE_MSG_Z71();
	}
}
