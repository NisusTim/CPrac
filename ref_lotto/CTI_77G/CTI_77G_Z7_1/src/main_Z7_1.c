/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "sys_shared.h"
#include "upgrade.h"

#if JSON_LIST_EN
#include "json_debug_info.h"
#endif

extern void __IMG_END_ADDR(void);
extern void _start_core2(void);
extern void __IMG_MAGIC_Z71(void);

void xcptn_xmpl(void);
void vehicle_init(void);
void measurements_init(void);

const image_header_t __attribute__ ((section(".z71imghdr"))) z71_image_header = {
		.rchw1 = 0xFFFFFFFF,
		.rchw2 = (uint32_t)_start_core2,
		.checksum = 0xFFFFFFFF,
		.magic = (uint32_t)__IMG_MAGIC_Z71,
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

int main(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	timer_init(0);
	console_init();
	pars_init();
	vehicle_init();
	product_init();
	measurements_init();

#ifdef ENABLE_SWT
	SWT2_Init();
#endif

	ipc_sync_ready(NULL);
#if JSON_LIST_EN
	init_json_dbg_info();
#endif
	/* Loop forever */
	for(;;) {
#ifdef ENABLE_SWT
		clear_SWT2_counter();
#endif
		event_handle();
	   	IPC_HANDLE_MSG_Z40();
	   	IPC_HANDLE_MSG_Z70();

	}
}
