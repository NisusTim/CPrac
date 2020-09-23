/*
 * z47_ipc.c
 *
 *  Created on: 2017/03/02
 *      Author: erichu
 */

#include "sys_shared.h"
ipc_handle_t		__attribute__((section(".ipcz47"))) ipc_handle;

static ipc_handle_p ipc = &ipc_handle;
static msg_proc_p 	msg_proc[MSG_INVALID]={NULL};
static void*		msg_data[MSG_INVALID]={NULL};
static const char * msg_name[MSG_INVALID]={NULL};

#if defined(CTI_Z4_0)
static int ready = -1;
#endif

void ipc_handle_init()
{
#if defined(CTI_Z4_0)
	ipc->head[0] = ipc->tail[0] = ipc->que[0];
	ipc->head[1] = ipc->tail[1] = ipc->que[1];
	ipc->head[2] = ipc->tail[2] = ipc->que[2];
	ipc->head[3] = ipc->tail[3] = ipc->que[3];
	ipc->head[4] = ipc->tail[4] = ipc->que[4];
	ipc->head[5] = ipc->tail[5] = ipc->que[5];
	console_command_reg("ipc",ipc_dump_msg_que);
#endif
}

void ipc_ready_handler(void* x)
{
#ifdef CTI_Z4_0
	ready |= (int)x;
	if(ready == (CORE_ID_Z70 | CORE_ID_Z71))
		sys_state_set(SYST_ACTIVE);
	PRINTF("ipc: recv %d, rdy=%d\n",(int)x,ready);
#else
	IPC_SEND_MSG_Z40(MSG_READY, (void*)(intptr_t)CORE_ID, 0);
	//PRINTF("z7-%d send rdy\n",CORE_ID);
#endif
}

void ipc_sync_ready(void* x)
{
#if defined(CTI_Z4_0)
	if(ready == -1){
		ipc_reg_msg(MSG_READY, "rdy", ipc_ready_handler);
		timer_set("rdy", DEFAULT_TICKS_PER_SECOND/50, 1, ipc_sync_ready, NULL);
		ready = 0;
	}
	else {
		IPC_SEND_MSG_Z70(MSG_READY, (void*)(intptr_t)CORE_ID, 0);
		IPC_SEND_MSG_Z71(MSG_READY, (void*)(intptr_t)CORE_ID, 0);
	}
#else
	ipc_reg_msg(MSG_READY, "rdy", ipc_ready_handler);
#endif
}

void ipc_reg_msg(ipc_msg_e msg, const char* name, msg_proc_p proc)
{
	if(msg >= MSG_INVALID)
		return;

	msg_proc[msg] = proc;
	msg_name[msg] = name;
	//PRINTF("c%d:%s(%d)\n", CORE_ID, name, msg);
}

void ipc_reg_msg_data(ipc_msg_e msg, const char* name, msg_proc_p proc, void* data)
{
	if(msg >= MSG_INVALID)
		return;

	msg_proc[msg] = proc;
	msg_data[msg] = data;
	PRINTF("c%d:%s(%d:%p)\n", CORE_ID, name, msg, data);
}

void ipc_send_msg_next(ipc_msg_e m, void* d, bool_t block_mode)
{
	if(m >= MSG_INVALID){
		PRINTF("Invalid msg %d\n", m);
		return;
	}
	ipc_msg_p ipc_m = ipc->head[NEXT_MSG_SEND_IDX];

	ipc->head[NEXT_MSG_SEND_IDX]->d = d;
	ipc->head[NEXT_MSG_SEND_IDX]->count = 0;
	ipc->head[NEXT_MSG_SEND_IDX]->msg = m;
	ipc->head[NEXT_MSG_SEND_IDX]->msg_status = IPC_MSG_SEND;

	if(ipc->head[NEXT_MSG_SEND_IDX] == &ipc->que[NEXT_MSG_SEND_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->head[NEXT_MSG_SEND_IDX] = ipc->que[NEXT_MSG_SEND_IDX];
	else
		ipc->head[NEXT_MSG_SEND_IDX]++;

	if(block_mode)
	{
		volatile uint32_t startTimeStamp = get_STM_CNT();
		while(ipc_m->msg_status == IPC_MSG_SEND)
		{
			if((get_STM_CNT() - startTimeStamp) *0.01667 > IPC_BLOCK_MODE_TIMEOUT)
			{
#ifdef IPC_DEBUG_MSG
				PRINTF("IPC_BLOCK_TIME_OUT %s:%d\n", __FUNCTION__, __LINE__);
#endif
				ipc_m->msg_status = IPC_MSG_IDLE;
			}
		}
#ifdef IPC_DEBUG_MSG
		volatile uint32_t endTimeStamp = get_STM_CNT();
		PRINTF("IPC_BLOCK_TIME:%.3f us\n",(endTimeStamp - startTimeStamp)*0.01667);
#endif
		if(ipc_m->msg_status == IPC_MSG_PROCCESS_DONE)
		{
			ipc_m->msg_status = IPC_MSG_IDLE;
		}
	}
}

void ipc_send_msg_data_next(ipc_msg_e m, uint32_t v, void* d, int count)
{
	void* data;
	if(m >= MSG_INVALID){
		PRINTF("Invalid msg %d\n", m);
		return;
	}

	ipc->head[NEXT_MSG_SEND_IDX]->d = (void*)v;
	ipc->head[NEXT_MSG_SEND_IDX]->count = count;
	ipc->head[NEXT_MSG_SEND_IDX]->msg = m;

	if(ipc->head[NEXT_MSG_SEND_IDX] == &ipc->que[NEXT_MSG_SEND_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->head[NEXT_MSG_SEND_IDX] = ipc->que[NEXT_MSG_SEND_IDX];
	else
		ipc->head[NEXT_MSG_SEND_IDX]++;

	while(count) {
		data = (void*)ipc->head[NEXT_MSG_HANDLE_IDX];
		memcpy(data, d, sizeof(ipc_msg_t));
		d += sizeof(ipc_msg_t);

		if(ipc->head[NEXT_MSG_HANDLE_IDX] == &ipc->que[NEXT_MSG_HANDLE_IDX][SIZE_OF_IPC_MSG_QUE-1])
			ipc->head[NEXT_MSG_HANDLE_IDX] = ipc->que[NEXT_MSG_HANDLE_IDX];
		else
			ipc->head[NEXT_MSG_HANDLE_IDX]++;
		count--;
	}
}

void ipc_send_msg_prev(ipc_msg_e m, void* d, bool_t block_mode)
{
	if(m >= MSG_INVALID){
		PRINTF("Invalid msg %d\n", m);
		return;
	}
	ipc_msg_p ipc_m = ipc->head[PREV_MSG_SEND_IDX];
	//PRINTF("c%d :msg %d prev\n", CORE_ID, m);

	ipc->head[PREV_MSG_SEND_IDX]->d = d;
	ipc->head[PREV_MSG_SEND_IDX]->count = 0;
	ipc->head[PREV_MSG_SEND_IDX]->msg = m;
	ipc->head[NEXT_MSG_SEND_IDX]->msg_status = IPC_MSG_SEND;

	if(ipc->head[PREV_MSG_SEND_IDX] == &ipc->que[PREV_MSG_SEND_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->head[PREV_MSG_SEND_IDX] = ipc->que[PREV_MSG_SEND_IDX];
	else
		ipc->head[PREV_MSG_SEND_IDX]++;

	if(block_mode)
	{
		volatile uint32_t startTimeStamp = get_STM_CNT();
		while(ipc_m->msg_status == IPC_MSG_SEND)
		{
			if((get_STM_CNT() - startTimeStamp) *0.01667 > IPC_BLOCK_MODE_TIMEOUT)
			{
#ifdef IPC_DEBUG_MSG
				PRINTF("IPC_BLOCK_TIME_OUT %s:%d\n", __FUNCTION__, __LINE__);
#endif
				ipc_m->msg_status = IPC_MSG_IDLE;
			}
		}
#ifdef IPC_DEBUG_MSG
		volatile uint32_t endTimeStamp = get_STM_CNT();
		PRINTF("IPC_BLOCK_TIME:%.3f us\n",(endTimeStamp - startTimeStamp)*0.01667);
#endif
		if(ipc_m->msg_status == IPC_MSG_PROCCESS_DONE)
		{
			ipc_m->msg_status = IPC_MSG_IDLE;
		}
	}
}

void ipc_send_msg_data_prev(ipc_msg_e m, uint32_t v, void* d, int count)
{
	void* data;
	if(m >= MSG_INVALID){
		PRINTF("Invalid msg %d\n", m);
		return;
	}

	ipc->head[PREV_MSG_SEND_IDX]->d = (void*)v;
	ipc->head[PREV_MSG_SEND_IDX]->count = count;
	ipc->head[PREV_MSG_SEND_IDX]->msg = m;

	if(ipc->head[PREV_MSG_SEND_IDX] == &ipc->que[PREV_MSG_SEND_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->head[PREV_MSG_SEND_IDX] = ipc->que[PREV_MSG_SEND_IDX];
	else
		ipc->head[PREV_MSG_SEND_IDX]++;

	while(count) {
		data = (void*)ipc->head[PREV_MSG_SEND_IDX];
		memcpy(data, d, sizeof(ipc_msg_t));
		d += sizeof(ipc_msg_t);

		if(ipc->head[PREV_MSG_SEND_IDX] == &ipc->que[PREV_MSG_SEND_IDX][SIZE_OF_IPC_MSG_QUE-1])
			ipc->head[PREV_MSG_SEND_IDX] = ipc->que[PREV_MSG_SEND_IDX];
		else
			ipc->head[PREV_MSG_SEND_IDX]++;
		count--;
	}
}

static void* _ipc_next_data_get(void)
{
	while(ipc->head[NEXT_MSG_HANDLE_IDX] == ipc->tail[NEXT_MSG_HANDLE_IDX]);

	void* data = (void*)ipc->tail[NEXT_MSG_HANDLE_IDX];
	if(ipc->tail[NEXT_MSG_HANDLE_IDX] == &ipc->que[NEXT_MSG_HANDLE_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->tail[NEXT_MSG_HANDLE_IDX] = ipc->que[NEXT_MSG_HANDLE_IDX];
	else
		ipc->tail[NEXT_MSG_HANDLE_IDX]++;

	return data;
}

static void* _ipc_prev_data_get(void)
{
	while(ipc->head[PREV_MSG_HANDLE_IDX] == ipc->tail[PREV_MSG_HANDLE_IDX]);

	void* data = (void*)ipc->tail[PREV_MSG_HANDLE_IDX];
	if(ipc->tail[PREV_MSG_HANDLE_IDX] == &ipc->que[PREV_MSG_HANDLE_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->tail[PREV_MSG_HANDLE_IDX] = ipc->que[PREV_MSG_HANDLE_IDX];
	else
		ipc->tail[PREV_MSG_HANDLE_IDX]++;

	return data;
}

static ipc_msg_p _ipc_next_msg_get(void)
{
	if(ipc->head[NEXT_MSG_HANDLE_IDX] == ipc->tail[NEXT_MSG_HANDLE_IDX])
		return NULL;

	ipc_msg_p msg = ipc->tail[NEXT_MSG_HANDLE_IDX];
	if(ipc->tail[NEXT_MSG_HANDLE_IDX] == &ipc->que[NEXT_MSG_HANDLE_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->tail[NEXT_MSG_HANDLE_IDX] = ipc->que[NEXT_MSG_HANDLE_IDX];
	else
		ipc->tail[NEXT_MSG_HANDLE_IDX]++;

	return msg;
}

static ipc_msg_p _ipc_prev_msg_get(void)
{
	if(ipc->head[PREV_MSG_HANDLE_IDX] == ipc->tail[PREV_MSG_HANDLE_IDX])
		return NULL;

	ipc_msg_p msg = ipc->tail[PREV_MSG_HANDLE_IDX];
	if(ipc->tail[PREV_MSG_HANDLE_IDX] == &ipc->que[PREV_MSG_HANDLE_IDX][SIZE_OF_IPC_MSG_QUE-1])
		ipc->tail[PREV_MSG_HANDLE_IDX] = ipc->que[PREV_MSG_HANDLE_IDX];
	else
		ipc->tail[PREV_MSG_HANDLE_IDX]++;

	return msg;
}

void ipc_handle_msg_next(void)
{
	ipc_msg_p m = _ipc_next_msg_get();
	if(m){
		if(m->msg < MSG_INVALID && msg_proc[m->msg] != NULL) {
			void *data, *dest=msg_data[m->msg];
			while(m->count) {
				data = _ipc_next_data_get();
				if(dest) {
					memcpy(dest, data, sizeof(ipc_msg_t));
					dest += sizeof(ipc_msg_t);
				}
				m->count--;
			}
#if defined(DEBUG_PROC_IN_TIME)
			m->time = STM_0.CNT.R;
			m->name = msg_name[m->msg];
			msg_proc[m->msg](m->d);
			m->time = STM_0.CNT.R-m->time;
#else
			msg_proc[m->msg](m->d);
#endif
			if(m->block_mode)
				m->msg_status = IPC_MSG_PROCCESS_DONE;
			else
				m->msg_status = IPC_MSG_IDLE;
		}
		else
			CORE_DEBUG("Err:ipcmsg %d wo proc!\n", m->msg);
	}
}

void ipc_handle_msg_prev(void)
{
	ipc_msg_p m = _ipc_prev_msg_get();
	if(m){
		if(m->msg < MSG_INVALID && msg_proc[m->msg] != NULL) {
			void *data, *dest=msg_data[m->msg];
			while(m->count) {
				data = _ipc_prev_data_get();
				if(dest) {
					memcpy(dest, data, sizeof(ipc_msg_t));
					dest += sizeof(ipc_msg_t);
				}
				m->count--;
			}
#if defined(DEBUG_PROC_IN_TIME)
			m->time = STM_0.CNT.R;
			m->name = msg_name[m->msg];
			msg_proc[m->msg](m->d);
			m->time = STM_0.CNT.R-m->time;
#else
			msg_proc[m->msg](m->d);
#endif
			if(m->block_mode)
				m->msg_status = IPC_MSG_PROCCESS_DONE;
			else
				m->msg_status = IPC_MSG_IDLE;
		}
		else
			CORE_DEBUG("Err:ipcmsg %d wo proc!\n", m->msg);
	}
}

const uint8_t ipc_que_src_dest[6][2]={{0,1},{1,0},{1,2},{2,1},{2,0},{0,2}};
#if defined(CTI_Z4_0)
/********************************************************************************
 * Function : dump event que
 ********************************************************************************/
void ipc_dump_msg_que(char** args, int count)
{
#if defined(DEBUG_PROC_IN_TIME)
	if(count >= 6)
		return;

	ipc_msg_p msg = ipc->tail[count]+1;
	if(msg == &ipc->que[count][SIZE_OF_IPC_MSG_QUE])
		msg = ipc->que[count];

	PRINTF("ipc(%d) c%d->c%d dump:\n", count, ipc_que_src_dest[count][0],ipc_que_src_dest[count][1]);
	while(msg != ipc->tail[count]) {
		PRINTF("%d:%s:%.fus\n", msg->msg, msg->name, msg->time*0.0166667); //((float)evt->time*16.7f)/1000000);

		msg++;
		if(msg == &ipc->que[count][SIZE_OF_IPC_MSG_QUE])
			msg = ipc->que[count];
	}
#endif
}
#endif

