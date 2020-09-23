/*
 * z47_ipc.h
 *
 *  Created on: 2017/3/2
 *      Author: erichu
 */

#ifndef Z47_IPC_H_
#define Z47_IPC_H_

#include "typedefs.h"

typedef enum {
	MSG_TARGETS_LIST=0,			// 0
	MSG_MEASUREMENTS_DONE,		// 1
	MSG_CONSOLE_MSG,			// 2
	MSG_FRAMERATE,				// 3
	MSG_FRAME_NEXT,				// 4
	MSG_READY,					// 5
	MSG_PARS_INST,				// 6
	MSG_FRAME_DATA,				// 7
	MSG_VEHICLE_STATUS,			// 8, door b0:1=open,0=closed, gear b1:0=forward,1=backward
	MSG_VEHICLE_DATA,			// 9
	MSG_YAW_ONBOARD,			// 10
	MSG_TARGETS_INFO,			// 11
	MSG_MUSIC_COEFS,			// 12
	MSG_JSON_DBG_INFO,			// 13
	MSG_RF_GAIN_PARS,			// 14
	MSG_WARN_MSG,				// 15
	MSG_JSON_TARGET_LIST,		// 16
	MSG_AOAIDXS_TABLE,			// 17
	MSG_JSON_MEAS_LIST,			// 18
	MSG_TRACK_LIB_VER,			// 19
	MSG_FUSION_DATA,			// 20
	MSG_PARAMETER_SET,          // 21
    MSG_AUTO_HORI_ALIGN,		// 22
	MSG_AUTO_VERT_ALIGN,		// 23
	MSG_AUTO_HORI_DETECT,		// 24
	MSG_AUTO_VERT_DETECT,		// 25
	MSG_APP_DCM_DATA,			// 26
	MSG_INVALID
}ipc_msg_e;

typedef void (*msg_proc_p)(void*);

typedef enum {
	IPC_MSG_IDLE,
	IPC_MSG_SEND,
	IPC_MSG_PROCCESS_DONE,
	IPC_MSG_INVALID
}ipc_msg_status_e;

typedef struct {
	uint16_t	msg;
	uint16_t	count;
	void		*d;
	bool_t		block_mode;
	ipc_msg_status_e msg_status;
#if defined(DEBUG_PROC_IN_TIME)
	uint32_t	time;
	const char* name;
#endif
}ipc_msg_t, *ipc_msg_p;

#if defined(CTI_Z4_0)
void 		ipc_handle_init(void);
#define		CORE_ID								0
#define		CORE_ID_Z70							1
#define 	CORE_ID_Z71							2
#define		NEXT_MSG_SEND_IDX					0
#define		PREV_MSG_SEND_IDX					5
#define		NEXT_MSG_HANDLE_IDX					1
#define		PREV_MSG_HANDLE_IDX					4
#define 	IPC_SEND_MSG_Z70(_m, _d, _b)		ipc_send_msg_next(_m, _d, _b)
#define 	IPC_SEND_MSG_Z71(_m, _d, _b)		ipc_send_msg_prev(_m, _d, _b)
#define		IPC_HANDLE_MSG_Z70					ipc_handle_msg_next
#define		IPC_HANDLE_MSG_Z71					ipc_handle_msg_prev
#elif defined(CTI_Z7_0)
#define		CORE_ID								1
#define		NEXT_MSG_SEND_IDX					2
#define		PREV_MSG_SEND_IDX					1
#define		NEXT_MSG_HANDLE_IDX					3
#define		PREV_MSG_HANDLE_IDX					0
#define 	IPC_SEND_MSG_Z40(_m, _d, _b)		ipc_send_msg_prev(_m, _d, _b)
#define 	IPC_SEND_MSG_Z71(_m, _d, _b)		ipc_send_msg_next(_m, _d, _b)
#define		IPC_HANDLE_MSG_Z71					ipc_handle_msg_next
#define		IPC_HANDLE_MSG_Z40					ipc_handle_msg_prev
#else
#define		CORE_ID								2
#define		NEXT_MSG_SEND_IDX					4
#define		PREV_MSG_SEND_IDX					3
#define		NEXT_MSG_HANDLE_IDX					5
#define		PREV_MSG_HANDLE_IDX					2
#define 	IPC_SEND_MSG_Z40(_m, _d, _b)		ipc_send_msg_next(_m, _d, _b)
#define 	IPC_SEND_MSG_Z70(_m, _d, _b)		ipc_send_msg_prev(_m, _d, _b)
#define		IPC_HANDLE_MSG_Z40					ipc_handle_msg_next
#define		IPC_HANDLE_MSG_Z70					ipc_handle_msg_prev
#endif

#define 	SIZE_OF_IPC_MSG_QUE					64
#define		IPC_BLOCK_MODE_TIMEOUT				1000.0f //1000 us
typedef struct {
	ipc_msg_t	que[6][SIZE_OF_IPC_MSG_QUE];
	ipc_msg_p	head[6], tail[6];
}ipc_handle_t, *ipc_handle_p;

void ipc_send_msg_data_next(ipc_msg_e, uint32_t, void*, int);
void ipc_send_msg_data_prev(ipc_msg_e, uint32_t, void*, int);
void ipc_send_msg_next(ipc_msg_e, void*, bool_t block_mode);
void ipc_send_msg_prev(ipc_msg_e, void*, bool_t block_mode);
void ipc_handle_msg_next(void);
void ipc_handle_msg_prev(void);
void ipc_reg_msg(ipc_msg_e msg, const char*, msg_proc_p p);
void ipc_reg_msg_data(ipc_msg_e msg, const char*, msg_proc_p p, void* data);
void ipc_ready_handler(void*);
void ipc_sync_ready(void*);
void ipc_dump_msg_que(char**,int);

#endif /* Z47_IPC_H_ */
