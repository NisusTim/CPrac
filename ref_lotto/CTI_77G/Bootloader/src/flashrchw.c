#if defined(START_FROM_FLASH)
#include "typedefs.h"
#include "image.h"
#include "fbl_spec.h"

#define MPC57xx_ID    0x005A0000  /* RCHW boot ID for MPC57xx devices     */
#define VLE_ENABLE    0x01000000  /* VLE is enabled                       */
#define __IMG_MAGIC_Z4_bootloader (CUBTEK_IMG_MAGIC|0x4B)

extern void _start(void);
extern void __IMG_END_ADDR(void);

#define ENTRY_POINT  _start
#define RCHW_VAL (VLE_ENABLE | MPC57xx_ID)

const bl_u32_t __attribute__ ((section(".rchw"))) RCHW1 = RCHW_VAL;
const bl_u32_t __attribute__ ((section(".cpu0_reset_vector"))) RCHW2 = (bl_u32_t)ENTRY_POINT;

const bl_image_header_t __attribute__ ((section(".z4bimghdr"))) z4_image_header = {
		.rchw1 = RCHW_VAL,
		.rchw2 = (bl_u32_t)ENTRY_POINT,
		.checksum = 0xFFFFFFFF,
		.magic = (bl_u32_t)__IMG_MAGIC_Z4_bootloader,
		.addrs = {IMGE_ADDR_BLDR,IMAGE_ADDR_Z70,IMAGE_ADDR_Z71},
		.end = (uint32_t)__IMG_END_ADDR,
		.rev = {.major			= REV_MAJOR,
				.product		= DEFAULT_REV_PROD,
				.cusid			= DEFAULT_REV_CUSID,
				.minor			= REV_MINOR,
				.build			= DEFAULT_REV_BUILD,
				.maintenance	= REV_MAINTENANCE,
				.svn=REV_SVN},
        .rv = "3004r0",
        .rd = "20200304",
		.key = 12345678,
};

#endif /* defined(START_FROM_FLASH) */






