/*
 * parameters.h
 *
 *  Created on: 2017¦~5¤ë11¤é
 *      Author: erichu
 */

#ifndef BL_PARAMETERS_H_
#define BL_PARAMETERS_H_

#include <bl_eeprom.h>
#include "bl_typedefs.h"

#define PARS_GET_SUCCESSED	(0)
#define PARS_GET_FAILED		(-1)

#define JSON_PARS_HDR_ID		"\t\"id\":\"%c%c%c%c\",\n"
#define JSON_PARS_HDR_VERSION	"\t\"version\":%d,\n"
#define JSON_PARS_HDR_SIZE		"\t\"size\":%d,\n"

#define	MAX_PARS_CONTEXTS			25
#define	FOURCC(_a,_b,_c,_d)			((((bl_u32_t)_a)<<24)|(((bl_u32_t)_b)<<16)|(((bl_u32_t)_c)<<8)|((bl_u32_t)_d))
#define SIZE_OF_PARS_CTX			256
#define SIZE_OF_PARS_CTX_ID			4
#define SIZE_OF_PARS_CTX_HEADER		24
#define SIZE_OF_PARS_CTX_DATA		(SIZE_OF_PARS_CTX-SIZE_OF_PARS_CTX_HEADER)

#define NO_FORCE_ERASE				(0)
#define NO_BLOCK					(0)

typedef struct {
	bl_u32_t	base;
	bl_u16_t	version;
	bl_u16_t	size;
	bl_u32_t	id;
	bl_u32_t	chksum;
	bl_u64_t	mask;
}bl_pars_header_t, *bl_pars_header_p;

typedef struct {
	bl_pars_header_t	hdr;
	bl_u8_t				info[SIZE_OF_PARS_CTX_DATA];
}bl_pars_ctx_t, *bl_pars_ctx_p;

typedef int (*bl_pars_json_fun)(char*);

bl_pars_ctx_p pars_set(bl_pars_ctx_p);
bl_s16_t pars_get(bl_pars_ctx_p, void(*dump)(void), bl_pars_json_fun);
int pars_info_set(bl_u32_t,void*,int);
void* pars_info_get(bl_u32_t, bl_u16_t*,bl_u16_t*);
int pars_version_size_get(bl_u32_t, bl_u16_t *ver, bl_u16_t *size);
char* pars_json_get(bl_u32_t id, int* cnt);
int pars_json_data_get(bl_u32_t id, char*);
int	pars_id_list(bl_u32_t*);
void pars_init(int,int);
void pars_ctx_erase(bl_u32_t id);
int pars_all_json_data_get(char* ws);

#endif /* PARAMETERS_H_ */
