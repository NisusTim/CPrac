/*
 * parameters.c
 *
 *  Created on: 2017¦~5¤ë11¤é
 *      Author: erichu
 */

#include <bl_parameters.h>
#include <stdio.h>
#include <string.h>
#include "console.h"

#define DEFAULT_VALUE_OF_PARS_MASK	0xFFFFFFFFFFFFFFFF
#define ERASED_VALUE_OF_PARS_MASK	0xAA0A55F55505AAFA

typedef struct {
	bl_pars_ctx_p 		start;
	bl_pars_ctx_p 		available;
}pars_handle_t, *pars_handle_p;

typedef struct {
	bl_pars_ctx_p		ctx;
	void			(*dump)(void);
	bl_pars_json_fun	json;
}pars_instance_t, *pars_instance_p;

static pars_handle_t	pars_handle = {.start=NULL, .available=NULL}, *pars=&pars_handle;
static pars_instance_t	pars_instances[MAX_PARS_CONTEXTS]={{NULL,NULL}};

static bl_u32_t _pars_chksum(bl_pars_ctx_p ctx, bl_u16_t size)
{
	int cnt = 0;
	bl_u32_t chksum = 0, *d = (bl_u32_t*)ctx;
	while(cnt < (size/sizeof(bl_u32_t))){
		chksum += d[cnt++];
	}
	return chksum;
}

static void _pars_find_start(void)
{
	if((*(bl_u32_t*)EE_ADDR_PARAS_START0) == EE_ADDR_PARAS_START0)
		pars->start = (bl_pars_ctx_p)EE_ADDR_PARAS_START0;

	else if((*(bl_u32_t*)EE_ADDR_PARAS_START1) == EE_ADDR_PARAS_START1)
		pars->start = (bl_pars_ctx_p)EE_ADDR_PARAS_START1;

	else {
		eeprom_erase(EE_ADDR_PARAS_START0);
		//eeprom_erase(EE_ADDR_PARAS_START1);
		pars->start = (bl_pars_ctx_p)EE_ADDR_PARAS_START0;
	}
}

static bl_pars_ctx_p _pars_find_next(bl_pars_ctx_p curr)
{
	bl_u32_t sum = 0;
	if(pars->available == NULL)
		return NULL;

	while(curr < pars->available){
		if(curr->hdr.base == (bl_u32_t)curr && curr->hdr.mask == DEFAULT_VALUE_OF_PARS_MASK && curr->hdr.version != 0xFFFF){
			if((sum=_pars_chksum(curr, curr->hdr.size)) == 0)
				return curr;
			else {
				eeprom_write64(curr->hdr.base+offsetof(bl_pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
			}
		}
		curr++;
	}
	return NULL;
}

static int _pars_set_available(void)
{
	if(pars->start == NULL)
		return 0;

	int cnt = 0;
	pars->available = pars->start;
	while(pars->available < (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX))){
		if(pars->available->hdr.base == 0xFFFFFFFF)
			return cnt;

		else if(pars->available->hdr.mask == DEFAULT_VALUE_OF_PARS_MASK)
			cnt++;
		pars->available++;
	}
	return cnt;
}

static bl_pars_ctx_p _pars_new(bl_u32_t addr, bl_pars_ctx_p pctx)
{
	bl_pars_ctx_t ctx;
	bl_u16_t size=pctx->hdr.size;
	bl_u8_t *d = (bl_u8_t*)&ctx;
	if(addr == 0){
		addr = (bl_u32_t)pars->available;
		pars->available++;
		while(pars->available->hdr.base != 0xFFFFFFFF)
			pars->available++;
	}

	memcpy(&ctx, pctx, size);

	while(size & 0x03)
		d[size++] = 0xFF;

	ctx.hdr.base = addr;
	ctx.hdr.mask = DEFAULT_VALUE_OF_PARS_MASK;
	ctx.hdr.chksum = 0;
	ctx.hdr.chksum = 0-_pars_chksum(&ctx, size);
	eeprom_write(addr, &ctx, size);
	d = (bl_u8_t*)&pctx->hdr.id;

#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("pars: new %c%c%c%c %08lX\n", d[0], d[1], d[2], d[3], addr);
#endif

	return (bl_pars_ctx_p)addr;
}

static bl_pars_ctx_p _pars_migration(void)
{
	bl_pars_ctx_p  ctx0, ctxn;
	bl_u32_t	addr, addr0;

#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("pars: migration start@%p, available@%p\n", pars->start, pars->available);
#endif
	if((bl_u32_t)pars->start == EE_ADDR_PARAS_START0){
		eeprom_erase(EE_ADDR_PARAS_START1);
		addr0 = EE_ADDR_PARAS_START1;
	}

	else if((bl_u32_t)pars->start == EE_ADDR_PARAS_START1){
		eeprom_erase(EE_ADDR_PARAS_START0);
		addr0 = EE_ADDR_PARAS_START0;
	}

	else
		return NULL;

	ctx0 = _pars_find_next(pars->start);

	ctxn = _pars_find_next(ctx0+1);
	addr = addr0+SIZE_OF_PARS_CTX;
	while(ctxn != NULL){
		_pars_new(addr, ctxn);
		ctxn = _pars_find_next(ctxn+1);
		addr += SIZE_OF_PARS_CTX;
	 }

	_pars_new(addr0, ctx0);
	eeprom_erase((bl_u32_t)pars->start);
	_pars_find_start();
	_pars_set_available();
	return (bl_pars_ctx_p)addr0;
}

static void _pars_instance_set(bl_pars_ctx_p ctx, void(*dump)(void), bl_pars_json_fun json)
{
	pars_instance_p pip = pars_instances;
	while(pip < &pars_instances[MAX_PARS_CONTEXTS]){
		if(pip->ctx != NULL) {
			if(pip->ctx->hdr.id == ctx->hdr.id){
				pip->ctx = ctx;
				if(dump)
					pip->dump = dump;
				pip->json = json;
				return;
			}
		}
		else {
			pip->ctx = ctx;
			if(dump)
				pip->dump = dump;
			pip->json = json;
			return;
		}
		pip++;
	}
#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("pars: ctx instance full already!\n");
#endif
}

static pars_instance_p _pars_instance_get(bl_u32_t id)
{
	pars_instance_p pip = pars_instances;
	while(pip < &pars_instances[MAX_PARS_CONTEXTS]){
		if(pip->ctx != NULL) {
			if(pip->ctx->hdr.id == id)
				return pip;
		}
		else
			return NULL;
		pip++;
	}
	return NULL;
}


int pars_json_data_get(bl_u32_t id, char* ws)
{
	pars_instance_p inst = _pars_instance_get(id);
	int cnt = 0;
	if(ws != NULL  && inst != NULL){
		if(inst->json != NULL){
			cnt = inst->json(ws);
			return cnt;
		}
	}
	return 0;
}

int pars_all_json_data_get(char* ws)
{
	int cnt = 0, subcnt = 0;
	pars_instance_p inst = pars_instances;
	
	ws[0] = '[';
	ws += 1;
	cnt++;
	while(inst < &pars_instances[MAX_PARS_CONTEXTS]){
	    if(inst->ctx != NULL){
		    subcnt = pars_json_data_get(inst->ctx->hdr.id, ws);
		    ws += subcnt;
		    cnt += subcnt;
		}
		else{
			break;
		}
		*ws++ = ',';
		cnt++;
		inst++;
	}
	*(ws-1) = ']';
	*ws++ = '\n';
	*ws++ = '\0';
	return cnt;
	
}


int pars_info_set(bl_u32_t id, void* data, int cnt)
{
	pars_instance_p inst;
	if(data == NULL)
		return PARS_GET_FAILED;

	if((inst = _pars_instance_get(id)) == NULL)
		return PARS_GET_FAILED;

	if(cnt > (inst->ctx->hdr.size-sizeof(bl_pars_header_t)))
		cnt = inst->ctx->hdr.size-sizeof(bl_pars_header_t);

	if(data != inst->ctx->info)
		memcpy((void*)&inst->ctx->info, data, cnt);

	pars_set(inst->ctx);

	if(inst->dump != NULL)
		inst->dump();

	return PARS_GET_SUCCESSED;
}

void* pars_info_get(bl_u32_t id, bl_u16_t *ver, bl_u16_t* size)
{
	pars_instance_p inst;
	if(size == NULL || ver == NULL)
		return NULL;

	if((inst = _pars_instance_get(id)) == NULL)
		return NULL;

	*size = inst->ctx->hdr.size-sizeof(bl_pars_header_t);
	*ver = inst->ctx->hdr.version;

#if (CONSOLE_ENABLE == CONSOLE_ON)
	PRINTF("pars: %c%c%c%c@%p,ver=%d,size=%d\n",(char)(id>>24),(char)((id>>16)&0xFF),
			(char)((id>>8)&0xFF),(char)(id&0xFF), inst->ctx->info,*ver, *size);
#endif
	return inst->ctx->info;
}

bl_s16_t pars_get(bl_pars_ctx_p pctx, void(*dump)(void), bl_pars_json_fun json)
{
	bl_pars_ctx_p c;

	if(!pctx) {
#if (CONSOLE_ENABLE == CONSOLE_ON)
		PRINTF("pars: null pctx!\n");
#endif
		return -1;
	}
	else if (pctx->hdr.size > SIZE_OF_PARS_CTX){
#if (CONSOLE_ENABLE == CONSOLE_ON)
		char* id = (char*)&pctx->hdr.id;
		PRINTF("pars: %c%c%c%c, size=%03X too much\n", id[0],id[1],id[2],id[3], pctx->hdr.size);
#endif
		return -1;
	}

	_pars_instance_set(pctx, dump, json);

	c = _pars_find_next(pars->start);
	while(c != NULL){
		if(c->hdr.id == pctx->hdr.id){
			if(c->hdr.version == pctx->hdr.version){
				memcpy(((void*)pctx)+SIZE_OF_PARS_CTX_HEADER, (void*)c->hdr.base+SIZE_OF_PARS_CTX_HEADER, pctx->hdr.size-SIZE_OF_PARS_CTX_HEADER);
				return PARS_GET_SUCCESSED;
			}
			else{
				if((c->hdr.version>>8) == (pctx->hdr.version>>8)){
					if(c->hdr.size <= pctx->hdr.size)
						memcpy(((void*)pctx)+SIZE_OF_PARS_CTX_HEADER, ((void*)c->hdr.base)+SIZE_OF_PARS_CTX_HEADER, c->hdr.size-SIZE_OF_PARS_CTX_HEADER);
				}
				_pars_new(0, pctx);
				eeprom_write64(c->hdr.base+offsetof(bl_pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
				if(pars->available == (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
					_pars_migration();

				return PARS_GET_SUCCESSED+1;
			}
		}
		c = _pars_find_next(c+1);
	}

	_pars_new(0, pctx);
	if(pars->available == (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
		_pars_migration();
	return PARS_GET_SUCCESSED+2;
}

bl_pars_ctx_p pars_set(bl_pars_ctx_p pctx)
{
	bl_pars_ctx_p c=_pars_find_next(pars->start), p=NULL;

	if (pctx == NULL)
		return NULL;

	if(pctx->hdr.size > SIZE_OF_PARS_CTX){
#if (CONSOLE_ENABLE == CONSOLE_ON)
		char* id = (char*)&pctx->hdr.id;
		PRINTF("pars: %c%c%c%c, size=%03X too much\n", id[0], id[1], id[2], id[3], pctx->hdr.size);
#endif
		return NULL;
	}

	while(c != NULL){
		if(c->hdr.id == pctx->hdr.id){
			p = _pars_new(0, pctx);
			eeprom_write64(c->hdr.base+offsetof(bl_pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
			if(pars->available == (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
				_pars_migration();
			return p;
		}
		c = _pars_find_next(c+1);
	}

	_pars_new(0, pctx);
	if(pars->available == (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
		_pars_migration();
	return p;
}

void pars_ctx_erase(bl_u32_t id)
{
	bl_pars_ctx_p ctx = _pars_find_next(pars->start);
#if (CONSOLE_ENABLE == CONSOLE_ON)
	bl_u8_t* d= (bl_u8_t*)&id;
#endif
	while(ctx != NULL){
		if(id == ctx->hdr.id){
			eeprom_write64(ctx->hdr.base+offsetof(bl_pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
#if (CONSOLE_ENABLE == CONSOLE_ON)
			PRINTF("pars: ctx %c%c%c%c erased\n", d[0], d[1], d[2], d[3]);
#endif
			return;
		}
		ctx = _pars_find_next(ctx+1);
	}
}

void pars_init(int force, int block)
{
	if(force) {
		eeprom_erase(EE_ADDR_PARAS_START0);
		eeprom_erase(EE_ADDR_PARAS_START1);
		pars->start = (bl_pars_ctx_p)EE_ADDR_PARAS_START0;

		if (block)
		{
#if (CONSOLE_ENABLE == CONSOLE_ON)
			PRINTF("pars: erase all, system reset\n");
#endif
			while (1);
		}
		else
		{
#if (CONSOLE_ENABLE == CONSOLE_ON)
			PRINTF("pars: erase by prod\n");
#endif
		}
	}
	else
		_pars_find_start();

	if(_pars_set_available() > MAX_PARS_CONTEXTS){
		eeprom_erase(EE_ADDR_PARAS_START0);
		eeprom_erase(EE_ADDR_PARAS_START1);
		pars->start = (bl_pars_ctx_p)EE_ADDR_PARAS_START0;
		pars->available = pars->start;
	}
	else if(pars->available >= (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
		_pars_migration();

#if (CONSOLE_ENABLE == CONSOLE_ON)
	console_command_reg("pars", _pars_tester);
	PRINTF("pars: init start@%p, available@%p\n", pars->start, pars->available);
#endif
}

