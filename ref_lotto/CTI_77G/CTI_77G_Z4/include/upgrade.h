/*
 * bootldr.h
 *
 *  Created on: 2017�~8��24��
 *      Author: erichu
 */

#ifndef UPGRADE_H_
#define UPGRADE_H_

#include "event.h"

typedef enum {
	REV_PROD_FCW = 0,
	REV_PROD_2BEAM_BSD,
	REV_PROD_OMNI_BSD,
	REV_PROD_RCW,
	REV_PROD_PDS,
	REV_PROD_ODS,
	REV_PROD_INVALID
}REV_PROD_E;

typedef enum {
	REV_BUILD_ALPHA=0,
	REV_BUILD_BETA,
	REV_BUILD_RELEASE
}REV_BUILD_E;

#define CUBTEK_IMG_MAGIC		0x68BEEF00
#define IMAGE_ADDR_Z4			0x01000000
#define IMAGE_ADDR_Z70			0x010C0000
#define IMAGE_ADDR_Z71			0x01140000
#define IMGE_ADDR_BLDR			0x00F98000

typedef enum {
	IMGNO_BLDR=0,
	IMGNO_Z70,
	IMGNO_Z71,
	IMGNO_Z4,
	IMGS_COUNT
}imgno_e;

typedef enum {
	UPST_STANDBY = 0,			// state for default entry
	UPST_WAIT_DONE,
	UPST_READY,
	UPST_DATA,
	UPST_INVALID
}upd_state_e;

typedef struct {
	uint16_t	svn;
	uint16_t	minor;
	uint8_t		product;
	uint8_t		major;
	uint8_t		cusid;
	uint8_t		build:2;
	uint8_t		maintenance:6;
}revision_t,*revision_p;

typedef struct {
	uint32_t		rchw1;
	uint32_t		rchw2;
	uint32_t		checksum;
	uint32_t		magic;
	uint32_t		addrs[IMGS_COUNT-1]; // wo Z4 addr
	uint32_t		end;
	revision_t		rev;
	char			rv[8];
	char			rd[16];
	uint32_t		key;
}image_header_t, *image_header_p;

errno_e upd_init(void);
revision_p upd_revision_get(char*);
int upd_prepare_state(int);
int upd_data_done(imgno_e ino);
void upd_data(void* data, int count);
void upd_data_write(int offset, void* data, int count);
void upd_data_write_done(uint32_t size);
int upd_request(imgno_e ino, uint32_t size);

#endif /* UPGRADE_H_ */
