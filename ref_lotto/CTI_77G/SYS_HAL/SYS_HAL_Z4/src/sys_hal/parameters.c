/*
 * parameters.c
 *
 *  Created on: 2017¦~5¤ë11¤é
 *      Author: erichu
 */
#include "sys_shared.h"
#include "flash.h"

#define PREV_ERASE_NIO  1

#define DEFAULT_VALUE_OF_PARS_MASK	0xFFFFFFFFFFFFFFFF
#define ERASED_VALUE_OF_PARS_MASK	0xAA0A55F55505AAFA

#define CTX_COUNT_PER_EEBLOCK		(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)

typedef struct {
	pars_ctx_p 		start;
	pars_ctx_p 		available;
}pars_handle_t, *pars_handle_p;

typedef struct {
	pars_ctx_p		ctx;
	void			(*dump)(void);
	pars_json_fun	json;
}pars_instance_t, *pars_instance_p;

static pars_instance_p _pars_instance_get(uint32_t id);

#if defined(CTI_Z4_0)
static pars_instance_t	__attribute__((section(".pars_inst"))) pars_instances[MAX_PARS_CONTEXTS];
static pars_handle_t	pars_handle = {.start=NULL, .available=NULL}, *pars=&pars_handle;

static uint32_t _pars_chksum(pars_ctx_p ctx, uint16_t size)
{
	int cnt = 0;
	uint32_t chksum = 0, *d = (uint32_t*)ctx;
	while(cnt < (size/sizeof(uint32_t))){
		chksum += d[cnt++];
	}
	return chksum;
}

#if PREV_ERASE_NIO == 0
static void _pars_find_start(void)
{
	if((*(uint32_t*)EE_ADDR_PARAS_START0) == EE_ADDR_PARAS_START0)
		pars->start = (pars_ctx_p)EE_ADDR_PARAS_START0;

	else if((*(uint32_t*)EE_ADDR_PARAS_START1) == EE_ADDR_PARAS_START1)
		pars->start = (pars_ctx_p)EE_ADDR_PARAS_START1;

	else {
		eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
		pars->start = (pars_ctx_p)EE_ADDR_PARAS_START0;
	}
}
#endif

static int _pars_is_ctx_valid(pars_ctx_p ctx)
{
	if(ctx->hdr.base == (uint32_t)ctx && ctx->hdr.mask == DEFAULT_VALUE_OF_PARS_MASK){
		if(_pars_chksum(ctx, ctx->hdr.size) == 0)
			return True;
		else{
			uint8_t* d = (uint8_t*)&ctx->hdr.id;
			eeprom_write64_bio(ctx->hdr.base+offsetof(pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
			PRINTF("pars: invalid %c%c%c%c@%p erased\n", d[0], d[1], d[2], d[3], ctx);
		}
	}
	return False;
}

static pars_ctx_p _pars_find_next(pars_ctx_p curr)
{
	if(pars->available == NULL)
		return NULL;

	while(curr < pars->available){
		if(_pars_is_ctx_valid(curr) == True)
			return curr;
		curr++;
	}
	return NULL;
}

static int _pars_is_available(uint64_t* base, uint64_t* end)
{
	while(base < end){
		if(*base != 0xFFFFFFFFFFFFFFFF)
			return False;
		base++;
	}
	return True;
}

static pars_ctx_p _pars_get_available(pars_ctx_p start, uint16_t* cnt)
{
	pars_ctx_p avail = start, end = (start+CTX_COUNT_PER_EEBLOCK);
	*cnt = 0;
	while(avail < end){
		if(_pars_is_available((uint64_t*)avail, (uint64_t*)end) == True)
			return avail;

		else if(_pars_is_ctx_valid(avail) == True)
			*cnt = *cnt +1;
		avail++;
	}
	return avail;
}

static pars_ctx_p _pars_new(uint32_t addr, pars_ctx_p pctx)
{
	if (is_flash_on_safety()) {
		PRINTF("  parameters: pars_new() failed on safety mode.\n");
		return NULL;
	}

	uint16_t size=pctx->hdr.size;
	uint8_t *d;
	if(addr == 0){
		addr = (uint32_t)pars->available;
		pars->available++;
	}

	pctx->hdr.base = addr;
	pctx->hdr.mask = DEFAULT_VALUE_OF_PARS_MASK;
	pctx->hdr.chksum = 0;
	pctx->hdr.chksum = 0-_pars_chksum(pctx, size);
	eeprom_write_bio(addr, pctx, size);
	d = (uint8_t*)&pctx->hdr.id;
	PRINTF("pars: new %c%c%c%c %08lX\n", d[0], d[1], d[2], d[3], addr);
	return (pars_ctx_p)addr;
}

static void _pars_duplication_check(void)
{
	pars_ctx_p last = pars->available-1, prev;
	while(last > pars->start){
		if(_pars_is_ctx_valid(last) == True)
			break;
		last--;
	}
	prev = last - 1;
	while(prev >= pars->start){
		if(_pars_is_ctx_valid(prev) == True){
			if(last->hdr.id == prev->hdr.id){
				uint8_t* d= (uint8_t*)&prev->hdr.id;
				eeprom_write64_bio(prev->hdr.base+offsetof(pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
				PRINTF("pars: duplicated %c%c%c%c@%p erased\n", d[0], d[1], d[2], d[3], prev);
				break;
			}
		}
		prev--;
	}
}

static pars_ctx_p _pars_migration(void)
{
	pars_instance_p instp;
	pars_ctx_p  ctx0, ctxn;
	uint32_t	addr, addr0;
	uint16_t 	dummy;
	pars_ctx_t	tmp_ctx;

	PRINTF("pars: migration start@%p, available@%p\n", pars->start, pars->available);
	if((uint32_t)pars->start == EE_ADDR_PARAS_START0){
#if PREV_ERASE_NIO
		if (*(uint64_t *)EE_ADDR_PARAS_START1 != kFlashBlank) {
			eeprom_erase_bio(EE_ADDR_PARAS_START1, 0);
		}
#else
		eeprom_erase_bio(EE_ADDR_PARAS_START1, 0);
#endif
		addr0 = EE_ADDR_PARAS_START1;
	}

	else if((uint32_t)pars->start == EE_ADDR_PARAS_START1){
#if PREV_ERASE_NIO
		if (*(uint64_t *)EE_ADDR_PARAS_START0 != kFlashBlank) {
			eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
		}
#else
		eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
#endif
		addr0 = EE_ADDR_PARAS_START0;
	}

	else
		return NULL;

	ctx0 = _pars_find_next(pars->start);
	ctxn = _pars_find_next(ctx0+1);
	addr = addr0 + SIZE_OF_PARS_CTX;
	while(ctxn != NULL){
		memcpy((void*)&tmp_ctx, (void*)(ctxn->hdr.base), ctxn->hdr.size);
		_pars_new(addr, &tmp_ctx);
		if((instp = _pars_instance_get(tmp_ctx.hdr.id)) != NULL)
			instp->ctx->hdr.base = addr;
		ctxn = _pars_find_next(ctxn+1);
		addr += SIZE_OF_PARS_CTX;
	}
	memcpy((void*)&tmp_ctx, (void*)(ctx0->hdr.base), ctx0->hdr.size);
	_pars_new(addr0, &tmp_ctx);
	if((instp = _pars_instance_get(tmp_ctx.hdr.id)) != NULL)
		instp->ctx->hdr.base = addr0;

#if PREV_ERASE_NIO
	eeprom_erase((uint32_t)pars->start, 0, NULL, NULL);
	if ((uint32_t)pars->start == EE_ADDR_PARAS_START0)
		pars->start = (pars_ctx_p)EE_ADDR_PARAS_START1;
	else if ((uint32_t)pars->start == EE_ADDR_PARAS_START1)
		pars->start = (pars_ctx_p)EE_ADDR_PARAS_START0;
#else
	eeprom_erase_bio((uint32_t)pars->start, 0);
	_pars_find_start();
#endif
	pars->available = _pars_get_available(pars->start, &dummy);
	return (pars_ctx_p)addr0;
}


static pars_ctx_p _pars_ctx_update(pars_ctx_p old, pars_ctx_p pctx)
{
	_pars_new(0, pctx);
	if(old)
		eeprom_write64_bio(old->hdr.base+offsetof(pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);

	if(pars->available == (pars->start+CTX_COUNT_PER_EEBLOCK))
		_pars_migration();
	return (pars_ctx_p)(pctx->hdr.base);
}


static void _pars_instance_set(pars_ctx_p ctx, void(*dump)(void), pars_json_fun json)
{
	pars_instance_p pip = pars_instances;
	while(pip < (pars_instances+MAX_PARS_CONTEXTS)){
		if(pip->ctx != NULL) {
			if(pip->ctx->hdr.id == ctx->hdr.id){
				pip->ctx = ctx;
				if(dump)
					pip->dump = dump;

				if (json)
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
	PRINTF("pars: ctx instance full already!\n");
}

static void _pars_tester(char** args, int count)
{
	pars_ctx_p ctx = _pars_find_next(pars->start);
	uint8_t *d;

	if(count > 1){
		if(count > 2){
			if(!strncmp(args[1], "erase", 5)){
				if(!strncmp(args[2], "reset", 5))
					pars_init(TRUE, TRUE);
				else if (!strncmp(args[2], "opt", 3))
				{
					uint16_t size = 0;
					uint8_t tmp[MAX_PARS_CONTEXTS][5];
					uint8_t *tmp_ptr;

					ctx = _pars_find_next(pars->start);

					// get size
					while(ctx != NULL) {
						tmp_ptr = (uint8_t*)&ctx->hdr.id;
						tmp[size][0] = tmp_ptr[0];
						tmp[size][1] = tmp_ptr[1];
						tmp[size][2] = tmp_ptr[2];
						tmp[size][3] = tmp_ptr[3];
						tmp[size][4] = 0;
						ctx = _pars_find_next(ctx+1);
						size++;
					}

					if (count > size + 3)
					{
						PRINTF("parameter too much.\n");
					}
					else
					{
						uint16_t i, idx;
						for (i = 3; i < count; i++)
						{
							idx = (uint16_t)atoi(args[i]);
							if (idx < size)
							{
								pars_ctx_erase(FOURCC(tmp[idx][0], tmp[idx][1], tmp[idx][2], tmp[idx][3]));
							}
						}

						PRINTF("reboot...\n");
						reset_system();
					}
				}
				else
					pars_ctx_erase(FOURCC(args[2][0],args[2][1],args[2][2],args[2][3]));
			}
			else if(!strcmp(args[1],"json")) {
				uint32_t id;
				char* idc=(char*)&id;
				idc[0] = args[2][0];
				idc[1] = args[2][1];
				idc[2] = args[2][2];
				idc[3] = args[2][3];
				if(pars_json_get(id, &count) != NULL){
					PRINTF("pars %c%c%c%c in json %d:\n",idc[0],idc[1],idc[2],idc[3], count);
					idc = (char*)WORK_SPACE;
					idc[count] = 0;
					put_string(idc);
				}
			}
		}
		else {
		    if(!strcmp(args[1],"json-all")) {
				char *data = (char*)spt_work_space_get();
				pars_all_json_data_get(data);
				put_string(data);
		    }
		    else if(!strcmp(args[1],"erase-all")) {
		    	eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
		    	eeprom_erase_bio(EE_ADDR_PARAS_START1, 0);
		        PRINTF("erase all eeprom block...\n");
		    }
		    else if(!strcmp(args[1],"instd")) {
		    	pars_instance_p instp = pars_instances;
		    	while(instp < (pars_instances+MAX_PARS_CONTEXTS)){
		    		if(instp->ctx){
		    			d = (uint8_t*)&instp->ctx->hdr.id;
		    			PRINTF("%c%c%c%c@%08lX[%p,%p,%p]\n",d[0],d[1],d[2],d[3],
		    					instp->ctx->hdr.base, instp->ctx, instp->json, instp->dump);
		    		}
		    		else
		    			break;
		    		instp++;
		    	}
		    }
		    else{
			    pars_instance_p inst=_pars_instance_get(FOURCC(args[1][0],args[1][1],args[1][2],args[1][3]));
			    if(inst && inst->dump)
				    inst->dump();
			    else
				    PRINTF("pars: %s not found\n",args[1]);
			}
		}
	}
	else {
		uint16_t idx = 0;
		PRINTF("pars %p dump:\n", pars->start);
		while(ctx != NULL) {
			d = (uint8_t*)&ctx->hdr.id;
			PRINTF("[%2d] %c%c%c%c@%p, ver=%04X, sz=%04X\n",
					idx,
					d[0],d[1],d[2],d[3], ctx, ctx->hdr.version, ctx->hdr.size);
			ctx = _pars_find_next(ctx+1);
			idx++;
		}
		PRINTF("\n");
	}
}


////////////////////////////////////////////////////////////////////////////////
//
//  parameters exported apis
//
///////////////////////////////////////////////////////////////////////////////

int pars_id_list(uint32_t* ids)
{
	int idx = 0;
	pars_instance_p inst = pars_instances;
	while(inst < &pars_instances[MAX_PARS_CONTEXTS]){
		if(inst->ctx != NULL){
		    if(inst->json !=NULL){
			    ids[idx++] = inst->ctx->hdr.id;
			}
		}
		else{
			ids[idx] = 0;
			break;
		}
		inst++;
	}
	return idx;
}

char* pars_json_get(uint32_t id, int* cnt)
{
	pars_instance_p inst = _pars_instance_get(id);
	if(cnt != NULL && inst != NULL){
		if(inst->json != NULL){
			*cnt = inst->json((char*)WORK_SPACE);
			return (char*)WORK_SPACE;
		}
	}
	return NULL;
}

int pars_json_data_get(uint32_t id, char* ws)
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
		    inst++;
		    if(subcnt==0) continue;
		    ws += subcnt;
		    cnt += subcnt;
		}
		else{
			break;
		}
		*ws++ = ',';
		cnt++;
		
	}
	*(ws-1) = ']';
	*ws++ = '\n';
	*ws++ = '\0';
	return cnt;
	
}

int pars_info_set(uint32_t id, void* data, int cnt)
{
	pars_instance_p inst;
	if(data == NULL)
		return ERRNO_FAILED;

	if((inst = _pars_instance_get(id)) == NULL)
		return ERRNO_FAILED;

	if(cnt > (inst->ctx->hdr.size-sizeof(pars_header_t)))
		cnt = inst->ctx->hdr.size-sizeof(pars_header_t);

	if(data != inst->ctx->info)
		memcpy((void*)&inst->ctx->info, data, cnt);

	pars_set(inst->ctx);

	if(inst->dump != NULL)
		inst->dump();

	return SUCCESSED;
}

int16_t pars_get(pars_ctx_p pctx, void(*dump)(void), pars_json_fun json)
{
	pars_ctx_p c;

	if(!pctx) {
		PRINTF("pars: null pctx!\n");
		return -1;
	}
	else if (pctx->hdr.size > SIZE_OF_PARS_CTX){
		char* id = (char*)&pctx->hdr.id;
		PRINTF("pars: %c%c%c%c, size=%03X too much\n", id[0],id[1],id[2],id[3], pctx->hdr.size);
		return -1;
	}

	_pars_instance_set(pctx, dump, json);

	c = _pars_find_next(pars->start);
	while(c != NULL){
		if(c->hdr.id == pctx->hdr.id){
			if(c->hdr.version == pctx->hdr.version){
				memcpy(((void*)pctx)+SIZE_OF_PARS_CTX_HEADER, (void*)c->hdr.base+SIZE_OF_PARS_CTX_HEADER, pctx->hdr.size-SIZE_OF_PARS_CTX_HEADER);
				pctx->hdr.base = c->hdr.base;
				return SUCCESSED;
			}
			else{
				if((c->hdr.version>>8) == (pctx->hdr.version>>8)){
					if(c->hdr.size <= pctx->hdr.size)
						memcpy(((void*)pctx)+SIZE_OF_PARS_CTX_HEADER, ((void*)c->hdr.base)+SIZE_OF_PARS_CTX_HEADER, c->hdr.size-SIZE_OF_PARS_CTX_HEADER);
				}
				_pars_ctx_update(c, pctx);
				return SUCCESSED+1;
			}
		}
		c = _pars_find_next(c+1);
	}

	_pars_ctx_update(NULL, pctx);
	return SUCCESSED+2;
}

pars_ctx_p pars_set(pars_ctx_p pctx)
{
	pars_ctx_p c=_pars_find_next(pars->start), p=NULL;

	if (pctx == NULL)
		return NULL;

	if(pctx->hdr.size > SIZE_OF_PARS_CTX){
		char* id = (char*)&pctx->hdr.id;
		PRINTF("pars: %c%c%c%c, size=%03X too much\n", id[0], id[1], id[2], id[3], pctx->hdr.size);
		return NULL;
	}

	while(c != NULL){
		if(c->hdr.id == pctx->hdr.id){
			p = _pars_ctx_update(c, pctx);
			return p;
		}
		c = _pars_find_next(c+1);
	}

	return _pars_ctx_update(NULL, pctx);
}

void pars_ctx_erase(uint32_t id)
{
	pars_ctx_p ctx = _pars_find_next(pars->start);
	uint8_t* d= (uint8_t*)&id;
	while(ctx != NULL){
		if(id == ctx->hdr.id){
			eeprom_write64_bio(ctx->hdr.base+offsetof(pars_header_t, mask), ERASED_VALUE_OF_PARS_MASK);
			PRINTF("pars: ctx %c%c%c%c erased\n", d[0], d[1], d[2], d[3]);
			return;
		}
		ctx = _pars_find_next(ctx+1);
	}
}

void pars_ipc_set(void *d)
{
    uint32_t id =(uint32_t)d;
    PRINTF("ipc pars: %c%c%c%c set\n",(char)(id>>24),(char)((id>>16)&0xFF),(char)((id>>8)&0xFF),(char)(id&0xFF));
    pars_set(pars_ctx_get(id));
    
}

void pars_init(int force, int block)
{
	uint16_t cnt0, cnt1;
	pars_ctx_p avail0, avail1;

	memset((void*)pars_instances, 0, sizeof(pars_instances));

	if(force) {
		eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
		eeprom_erase_bio(EE_ADDR_PARAS_START1, 0);
		pars->available = pars->start = (pars_ctx_p)EE_ADDR_PARAS_START0;

		if (block){
			PRINTF("pars: erase all, system reset\n");
			reset_system();
		}
		else{
			PRINTF("pars: erase by prod\n");
		}
	}
	else {
		avail0 = _pars_get_available((pars_ctx_p)EE_ADDR_PARAS_START0, &cnt0);
		avail1 = _pars_get_available((pars_ctx_p)EE_ADDR_PARAS_START1, &cnt1);
		if(cnt0 >= cnt1){
			pars->available = avail0;
			pars->start = (pars_ctx_p)EE_ADDR_PARAS_START0;
			eeprom_erase_bio(EE_ADDR_PARAS_START1, 0);
		}
		else{
			pars->available = avail1;
			pars->start = (pars_ctx_p)EE_ADDR_PARAS_START1;
			eeprom_erase_bio(EE_ADDR_PARAS_START0, 0);
		}
	}

	_pars_duplication_check();

	if(pars->available >= (pars->start+(SIZE_OF_EE_MEM_BLOCK/SIZE_OF_PARS_CTX)))
		_pars_migration();

	console_command_reg("pars", _pars_tester);
	ipc_reg_msg(MSG_PARAMETER_SET, "pars_set", (msg_proc_p)pars_ipc_set);
	PRINTF("pars: init start@%p, available@%p\n", pars->start, pars->available);
}


void pars_insts_share(void)
{
	IPC_SEND_MSG_Z70(MSG_PARS_INST, (void*)pars_instances, 0);
	IPC_SEND_MSG_Z71(MSG_PARS_INST, (void*)pars_instances, 0);
}

uint8_t* pars_info_get(uint32_t id, uint16_t *ver, uint16_t* size)
{
	pars_ctx_p ctx = pars_ctx_get(id);

	if(ctx == NULL)
		return NULL;

	if(size != NULL)
		*size = ctx->hdr.size-sizeof(pars_header_t);

	if(ver != NULL)
		*ver = ctx->hdr.version;

	PRINTF("pars: %c%c%c%c@%p,ver=%d,size=%d\n",(char)(id>>24),(char)((id>>16)&0xFF),
			(char)((id>>8)&0xFF),(char)(id&0xFF), ctx->info,*ver, *size);
	return ctx->info;
}

void pars_restore(uint32_t id, pars_ctx_p ctx)
{
	if (ctx == NULL){
		ctx = pars_ctx_get(id);
		if(ctx == NULL)
			return;
	}

	memcpy(ctx->info, (void*)(ctx->hdr.base)+sizeof(pars_header_t), ctx->hdr.size-sizeof(pars_header_t));
}

#else

#define MAX_PARS_INIT_CLIENTS		4
typedef struct _pars_init_proc{
	event_proc_p proc;
	void*		data;
} pars_init_proc_t, *pars_init_proc_p;

pars_init_proc_t pars_inits[MAX_PARS_INIT_CLIENTS] = {{NULL, 0},{NULL, 0},{NULL, 0},{NULL, 0}};

static pars_instance_p pars_instances = NULL;

void pars_init_proc_reg(event_proc_p proc, void* data, const char* name)
{
	for(int i=0; i < MAX_PARS_INIT_CLIENTS; i++){
		if(pars_inits[i].proc == NULL){
			pars_inits[i].proc = proc;
			pars_inits[i].data = data;
			return;
		}
	}
	PRINTF("pars: %s failed to register init proc\n", name);
}

void pars_insts_set(void* d)
{
	pars_instances = (pars_instance_p)d;
	PRINTF("pars: core%d insts(%p) set\n",CORE_ID, pars_instances);
	for(int i=0; i < MAX_PARS_INIT_CLIENTS; i++){
		if(pars_inits[i].proc == NULL)
			return;
		pars_inits[i].proc(pars_inits[i].data);
	}
}

void pars_init(void)
{
	ipc_reg_msg(MSG_PARS_INST, "pars", (msg_proc_p)pars_insts_set);
}

#endif

pars_ctx_p pars_ctx_get(uint32_t id)
{
	pars_instance_p inst;

	if((inst = _pars_instance_get(id)) == NULL)
		return NULL;

	//PRINTF("pars: %c%c%c%c@%p\n",(char)(id>>24),(char)((id>>16)&0xFF),
			//(char)((id>>8)&0xFF),(char)(id&0xFF), inst->ctx);
	return inst->ctx;
}

static pars_instance_p _pars_instance_get(uint32_t id)
{
	pars_instance_p pip = pars_instances;
	while(pip < (pars_instances+MAX_PARS_CONTEXTS)){
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

