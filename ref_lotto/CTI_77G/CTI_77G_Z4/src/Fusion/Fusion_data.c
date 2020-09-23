/*
 * Fusion_data.c
 *
 *  Created on: 2019¦~12¤ë18¤é
 *      Author: USER
 */


#include "Fusion_data.h"
#include "sys_shared.h"
#include "can_format.h"

#ifdef ENABLE_FUSION

#if defined(CTI_Z4_0)

Fusion_data_info_t __attribute__((section(".fusion_data"))) fusion_data_info;
static Fusion_data_info_p fusion_info=&fusion_data_info;

void fusion_list_init(){
	FUSION_INFO_E cnt=0;

	while(cnt<FUS_INVALID){
		fusion_info->R[cnt]=0xFFFFFFFFFFFFFFFF;
		cnt++;
	}
}


void fusion_data_init(){
	fusion_list_init();
	IPC_SEND_MSG_Z70(MSG_FUSION_DATA, (void*)fusion_info, 0);
}
#elif defined(CTI_Z7_0)
static Fusion_data_info_p fusion_info = NULL;

void fusion_usage(Fusion_data_info_p v)
{
	fusion_info = v;
}

void fusion_data_init(void)
{
	ipc_reg_msg(MSG_FUSION_DATA, "fus_data", (msg_proc_p)fusion_usage);
}



#endif
Fusion_data_info_p Fusion_data_get(){
	return fusion_info;
}
#endif
