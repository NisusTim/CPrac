/*
 * parameters.h
 *
 *  Created on: 2017¦~5¤ë11¤é
 *      Author: erichu
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <stdint.h>
#include "event.h"

#define JSON_PARS_HDR_ID		"\t\"id\":\"%c%c%c%c\",\n"
#define JSON_PARS_HDR_VERSION	"\t\"version\":%d,\n"
#define JSON_PARS_HDR_SIZE		"\t\"size\":%d,\n"

#define	MAX_PARS_CONTEXTS			25
#define	FOURCC(_a,_b,_c,_d)			((((uint32_t)_a)<<24)|(((uint32_t)_b)<<16)|(((uint32_t)_c)<<8)|((uint32_t)_d))
#define SIZE_OF_PARS_CTX			256
#define SIZE_OF_PARS_CTX_ID			4
#define SIZE_OF_PARS_CTX_HEADER		24
#define SIZE_OF_PARS_CTX_DATA		(SIZE_OF_PARS_CTX-SIZE_OF_PARS_CTX_HEADER)
typedef struct {
	uint32_t	base;
	uint16_t	version;
	uint16_t	size;
	uint32_t	id;
	uint32_t	chksum;
	uint64_t	mask;
}pars_header_t, *pars_header_p;

typedef struct {
	pars_header_t	hdr;
	uint8_t			info[SIZE_OF_PARS_CTX_DATA];
}pars_ctx_t, *pars_ctx_p;

typedef int (*pars_json_fun)(char*);

pars_ctx_p pars_ctx_get(uint32_t id);

#if defined(CTI_Z4_0)

pars_ctx_p pars_set(pars_ctx_p);
int16_t pars_get(pars_ctx_p, void(*dump)(void), pars_json_fun);
int pars_info_set(uint32_t,void*,int);
int pars_version_size_get(uint32_t, uint16_t *ver, uint16_t *size);
char* pars_json_get(uint32_t id, int* cnt);
int pars_json_data_get(uint32_t id, char*);
int	pars_id_list(uint32_t*);
void pars_init(int,int);
void pars_insts_share(void);
void pars_ctx_erase(uint32_t id);
int pars_all_json_data_get(char* ws);
uint8_t* pars_info_get(uint32_t, uint16_t*,uint16_t*);
void pars_restore(uint32_t, pars_ctx_p);

#else

void pars_init(void);
void pars_init_proc_reg(event_proc_p proc, void* data, const char* name);

#endif

#endif /* PARAMETERS_H_ */
