/*
 * can_upgrade.c
 *
*  Created on: 2017/9/5
 *      Author: erichu
 */

#include "sys_shared.h" /* include peripheral declarations */
#include "LibVer.h"

extern void __IMG_END_ADDR(void);
extern void _start_core0(void);
extern void z7s_up(uint32_t, uint32_t);
extern void __IMG_MAGIC_Z4(void);

#define MPC57xx_ID    			((uint32_t)0x005A0000)  /* RCHW boot ID for MPC57xx devices     */
#define VLE_ENABLE    			((uint32_t)0x01000000)  /* VLE is enabled                       */
#define RCHW_VAL 				(VLE_ENABLE | MPC57xx_ID)
#define RCHW_ENABLE				(MPC57xx_ID | VLE_ENABLE)
#define RCHW_DISABLE			(MPC57xx_DISABLE_ID | VLE_ENABLE)

#define MAX_BLOCKS_PER_IMAGE	4
#define DEFAULT_SECURITY_KEY	0x14018012

#define DEFAULT_REV_PROD		REV_PROD_FCW
#define DEFAULT_REV_CUSID		DEFAULT_CUSTOMER_ID
#define DEFAULT_REV_BUILD		REV_BUILD_BETA
#define REV_MAJOR				3
#define REV_MINOR				9
#define REV_SVN				    0

const image_header_t __attribute__ ((section(".z4imghdr"))) z4_image_header = {
		.rchw1 = RCHW_ENABLE,
		.rchw2 = (uint32_t)_start_core0,
		.checksum = 0xFFFFFFFF,
		.magic = (uint32_t)__IMG_MAGIC_Z4,
		.addrs = {IMGE_ADDR_BLDR,IMAGE_ADDR_Z70,IMAGE_ADDR_Z71},
		.end = (uint32_t)__IMG_END_ADDR,
		.rev = {.major			= REV_MAJOR,
				.product		= DEFAULT_REV_PROD,
				.cusid			= DEFAULT_REV_CUSID,
				.minor			= REV_MINOR,
				.build			= DEFAULT_REV_BUILD,
				.maintenance	= 1,
				.svn=REV_SVN},
		.rv = "3009b1",
		.rd = "20200909",
		.key = 12345678,
};

typedef struct {
	uint32_t	addr;
	uint32_t	size;
	uint32_t	szs[MAX_BLOCKS_PER_IMAGE];
	uint32_t	magic;
	char		name[4];
} image_priv_t, *image_priv_p;

const static image_priv_t image_privs[IMGS_COUNT] = {
		{.addr=IMGE_ADDR_BLDR, .size=0x18000, .szs={0x4000, 0x4000, 0x10000, 0}, .magic=CUBTEK_IMG_MAGIC|0x4B, .name="bld"},
		{.addr=IMAGE_ADDR_Z70, .size=0x80000, .szs={0x40000, 0x40000, 0, 0}, .magic=CUBTEK_IMG_MAGIC|0x70, .name="z70"},
		{.addr=IMAGE_ADDR_Z71, .size=0x40000, .szs={0x40000, 0, 0, 0}, .magic=CUBTEK_IMG_MAGIC|0x71, .name="z71"},
		{.addr=IMAGE_ADDR_Z4, .size=0xC0000, .szs={0x40000, 0x40000, 0x40000, 0}, .magic=CUBTEK_IMG_MAGIC|0x40, .name="z4"}};

#define IMG_HDR(imgno) 		((image_header_p)image_privs[imgno].addr)

int image_verify(uint32_t img)
{
	image_header_p hdr = (image_header_p)img;
	image_priv_p priv = (image_priv_p)image_privs;

	while(priv < &image_privs[IMGS_COUNT]){
		if(hdr->magic == priv->magic){
			for(int imgno=IMGE_ADDR_BLDR; imgno<IMGNO_Z4; imgno++){
				if(hdr->addrs[imgno] != image_privs[imgno].addr)
					return ERRNO_INVALID_ADDR;
			}

			if(hdr->end >= priv->addr+priv->size)
				return ERRNO_SIZE;

			return SUCCESSED;
		}
		priv++;
	}
	return ERRNO_MAGIC;
}

void upd_tester(char** args, int count)
{
	if(count >= 3 && !strcmp(args[1], "vfy")){
		int imgno = (uint32_t)strtoul(args[2], NULL, 10);
		PRINTF("img %d verify result=%d\n",imgno, image_verify(image_privs[imgno].addr));
	} else {
        char ver32b[32];
        upd_revision_get(ver32b);
        put_string(ver32b);
        PRINTF("%s@%s\n",z4_image_header.rv, z4_image_header.rd);

        dump_lib_ver(SYS_HAL_LIB_VER, ver32b);
        PRINTF("LibSys_Hal rev: %s\n", ver32b);

        dump_lib_ver(DETECTION_LIB_VER, ver32b);
        PRINTF("LibDetection rev: %s\n", ver32b);

        dump_lib_ver(DOLPHIN_LIB_VER, ver32b);
        PRINTF("LibDolphin rev: %s\n", ver32b);

        dump_lib_ver(MEAS_LIB_VER, ver32b);
        PRINTF("LibMeasurements rev: %s\n", ver32b);

        dump_lib_ver(TRACK_LIB_VER, ver32b);
        PRINTF("LibTrack rev: %s\n", ver32b);
	}
}

errno_e upd_z7s_up(void)
{
	if(image_verify(image_privs[IMGNO_Z70].addr) != SUCCESSED){
		PRINTF("upd: image z70 failed\n");
		return ERRNO_FAILED;
	}

	if(image_verify(image_privs[IMGNO_Z71].addr) != SUCCESSED){
		PRINTF("upd: image z71 failed\n");
		return ERRNO_FAILED;
	}

	z7s_up(IMG_HDR(IMGNO_Z70)->rchw2, IMG_HDR(IMGNO_Z71)->rchw2);

	return SUCCESSED;
}

static char rev_build_char[]={'a','b','r','x'};
revision_p upd_revision_get(char* ver32b)
{
	revision_t *rev=&IMG_HDR(IMGNO_Z4)->rev;
	if(ver32b == NULL)
		return rev;

	sprintf(ver32b,"V%u.%u.%u.%u.%c%u.%u\n",rev->major,rev->product,
			rev->cusid,rev->minor,rev_build_char[rev->build],rev->maintenance,rev->svn);

	return rev;
}

image_header_p upd_image_get(imgno_e ino)
{
	if(ino < IMGS_COUNT)
		return (image_header_p)image_privs[ino].addr;
	return NULL;
}

/*************************************************************************************
 * Update Boot loader start here
 *************************************************************************************/
const uint8_t __attribute__ ((section(".bivert"))) addsub[256] = {
				195,30,37,124,73,191,139,33,248,40,180,243,186,205,164,63,148,18,169,35,
				47,83,228,2,192,45,108,90,231,254,111,245,232,153,77,233,158,109,234,117,249,
				89,76,217,130,199,211,39,197,242,107,102,10,54,171,230,16,87,56,250,62,152,97,
				43,114,179,131,142,93,79,92,161,52,187,1,14,67,48,133,166,81,244,11,8,115,70,
				163,177,206,20,25,46,236,12,85,64,157,214,50,215,176,224,68,207,201,170,235,
				167,193,144,178,72,210,17,57,135,110,146,58,99,21,203,200,6,251,51,252,91,172,
				229,247,22,59,41,55,141,84,118,26,127,225,160,216,121,122,0,182,31,29,106,13,
				125,24,95,75,240,128,132,190,19,71,96,162,101,86,100,222,28,150,168,165,202,98,
				3,123,143,44,209,155,15,181,156,113,184,104,145,198,183,159,137,212,36,103,223,
				119,255,23,88,94,27,120,238,237,241,174,188,154,151,221,61,34,126,185,147,32,53,
				5,175,65,173,105,80,74,116,194,69,208,49,149,138,204,213,220,129,4,226,42,189,9,
				66,218,134,112,78,253,219,38,60,239,140,82,246,227,7,136,196};

typedef struct {
	void		*mem;
	uint32_t	size;
	uint8_t 	state;
	uint8_t		img_no;
} upd_handle_t, *upd_handle_p;

static upd_handle_t upd_handle = {0}, *upd = &upd_handle;

static uint32_t image_sum(uint32_t img, imgno_e imgno)
{
	image_header_p hdr = (image_header_p)img;
	uint32_t		sum = hdr->checksum;
	uint32_t	    *d = (uint32_t*)img, size;

	size = (hdr->end-hdr->addrs[imgno] + 3) & 0xFFFFFFFC;
	while(size > 0){
		sum += *d;
		d++;
		if(size < 4)
			size = 0;
		else
			size = size - sizeof(uint32_t);
	}

	sum = sum-hdr->checksum;

	if(sum) {
		sum = sum - hdr->checksum;
		sum = 0 - sum;
	}

	return sum;
}

#define ENCRYPT_COVER_AND_CODE

#ifdef ENCRYPT_COVER_AND_CODE
static void image_cover_reveal(uint32_t img, int size)
{
	uint32_t *data = (uint32_t*)img;
	uint8_t *slice=(uint8_t*)img, offs=0;
	while(size) {
		*data = *data ^ DEFAULT_SECURITY_KEY;
		*slice = *slice-offs;
		slice++;
		*slice = *slice-addsub[offs++];
		slice++;
		*slice = *slice-offs;
		slice++;
		*slice = *slice-addsub[offs++];
		slice++;
		data++;
		size -= sizeof(uint32_t);
	}
}

#endif

static void upd_wait_cb(void* d)
{
	if(upd->state == UPST_WAIT_DONE && sys_state_get() == SYST_PAUSED){
		upd->state = UPST_READY;
		PRINTF("upd: ready\n");
	}
	else {
		upd->state = UPST_STANDBY;
		upd->img_no = IMGS_COUNT;
		upd->mem = NULL;
	}
}

int upd_prepare_state(int d) // d = 0 => app, otherwaise => bootloader
{
	if(upd->state == UPST_STANDBY) {
		if(d){
			sys_state_set(SYST_PAUSED);
			timer_unset_all();
			upd->state = UPST_WAIT_DONE;
			timer_set("upd", 10, 1, upd_wait_cb, NULL);
			return SUCCESSED;
		}
		else
			return ERRNO_FAILED;
	}
	else if(upd->state == UPST_WAIT_DONE || upd->state == UPST_READY)
		return SUCCESSED;

	return ERRNO_FAILED;
}

int upd_request(imgno_e ino, uint32_t size)
{
	if(upd->state != UPST_READY || ino != IMGNO_BLDR)
		return ERRNO_FAILED;

	if(size > image_privs[ino].size )
		return ERRNO_FAILED;

	upd->size = size;
	upd->img_no = ino;
	upd->mem = spt_fft_data_get();
	upd->state = UPST_DATA;
	PRINTF("upd: img=%d,sz=%ld\n", upd->img_no, upd->size);

	return SUCCESSED;
}

void upd_data_write(int offset, void* data, int count)
{
	void *mem = NULL;

	mem = upd->mem + offset;

	if((upd->state == UPST_DATA)){
		memcpy(mem, data, count);
	}
}

void upd_data_write_done(uint32_t size)
{
	PRINTF("upd: write done %p:%lX\n",upd->mem, size);
}


int upd_data_done(imgno_e ino)
{
	image_header_p img = (image_header_p)upd->mem;
	image_priv_p priv = (image_priv_p)&image_privs[upd->img_no];
	uint64_t	 rchw;

	uint32_t size = 0, blk = 0, addr, count;
	uint8_t  *src = (uint8_t*)upd->mem;

	if((upd->state != UPST_DATA)){
		upd->state = UPST_STANDBY;
		return ERRNO_FAILED;
	}

	if(ino != upd->img_no){
		PRINTF("upd: wrong img number %d\n", ino);
		upd->state = UPST_STANDBY;
		return ERRNO_IMGNO;
	}

#ifdef ENCRYPT_COVER_AND_CODE
	image_cover_reveal((uint32_t)img, upd->size);
#endif

	if((count = image_sum((uint32_t)img, ino))) {
		PRINTF("upd: sum %08lX\n", count);
		upd->state = UPST_STANDBY;
		return ERRNO_CHKSUM;
	}

	if(img->magic != priv->magic) {
		PRINTF("upd: magic %08lX\n", img->magic);
		upd->state = UPST_STANDBY;
		return ERRNO_MAGIC;
	}

	PRINTF("upd: done %s date(%s)\n", priv->name, img->rd);

	rchw = ((uint64_t)img->rchw1 << 32) | img->rchw2;
	img->rchw1 = 0xFFFFFFFF;
	img->rchw2 = 0xFFFFFFFF;
	PRINTF("rchw revised:[%lX%lX,%lX%lX]\n", (uint32_t)(rchw>>32), (uint32_t)rchw, img->rchw1, img->rchw2);

	addr = priv->addr;
	while(blk < MAX_BLOCKS_PER_IMAGE){
		if(priv->szs[blk] > 0)
			flash_erase_bio(addr, 0);
		else
			break;
		addr += priv->szs[blk];
		blk++;
	}

	addr = priv->addr;
	src = (uint8_t*)upd->mem;
	blk = 0;
	size = img->end - priv->addr;
	while(blk < MAX_BLOCKS_PER_IMAGE){
		if(size > priv->szs[blk])
			count = priv->szs[blk];
		else
			count = size;

		if(flash_write_bio(addr, (void*)src, count)){
			PRINTF("upd: wr err\n");
			upd->state = UPST_STANDBY;
			return ERRNO_FLASH_WRITE;
		}

		size -= count;
		if(size > 0){
			src += count;
			addr += count;
			blk++;
		}
		else
			break;
	}

	size = img->end - priv->addr;
	if(image_verify(priv->addr) != SUCCESSED){
		PRINTF("upd: verify err\n");
		upd->state = UPST_STANDBY;
		return ERRNO_VERIFY;
	}

	if(upd->img_no == IMGNO_BLDR ){
		flash_write_bio(priv->addr, (void*)(&rchw), sizeof(rchw));
		upd->state = UPST_STANDBY;
		sys_state_set(SYST_READY);
	}

	PRINTF("upd: done\n");
	return SUCCESSED;
}

errno_e upd_init(void)
{
	lib_ver_init();
	upd_z7s_up();
	console_command_reg("upd", upd_tester);
	
	return SUCCESSED;
}
