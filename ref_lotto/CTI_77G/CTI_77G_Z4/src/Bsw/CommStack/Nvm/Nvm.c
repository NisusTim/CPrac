/*
 * Nvm.c
 *
 *  Created on: 2015-12-17
 *      Author: lim
 */
#include <string.h>
#include "Nvm.h"
#include "Dem.h"
#include "console.h"
#include "event.h"
#include "timer.h"

//volatile uint8 dememu[512];

#define EEPPAGESIZE 	695
STATIC NvmMemRecdInfoType NvmMemRecdInfo;
STATIC NvM_State_t  NvM_TaskState;
STATIC NvmMemBlockCfgType NvmMemBlockCfg/*[NVM_NUMOFBLOCK] */= 
{
//        (uint32)(&dememu[0]),//0x2620,/*The start address of the EEP where the Dem data is located*/
        (uint32)(0),//0x2620,/*The start address of the EEP where the Dem data is located*/
        sizeof(DemStorageMem), /*Dem data takes up the size of EEP*/
        EEPPAGESIZE   /*NvM module write (read) data length per call cycle*/
};

#define PARS_VERSION_MAJOR				0x01
#define PARS_VERSION_MINOR				0x00
#define VERSION_OF_DTC_PARS    		(((uint16_t)PARS_VERSION_MAJOR<<8) | PARS_VERSION_MINOR)

dtc_parameters_t dtc1_parameters = {
		.hdr = {
			.base = (uint32_t)&dtc1_parameters,
			.version = VERSION_OF_DTC_PARS,
			.size = sizeof(dtc_parameters_t),
			.id=DTC1_PARS_ID,
			.chksum = 0,
			.mask = 0,
		},
		.info = {
			.data = {0},
		}
};

dtc_parameters_t dtc2_parameters = {
		.hdr = {
			.base = (uint32_t)&dtc2_parameters,
			.version = VERSION_OF_DTC_PARS,
			.size = sizeof(dtc_parameters_t),
			.id=DTC2_PARS_ID,
			.chksum = 0,
			.mask = 0,
		},
		.info = {
			.data = {0},
		}
};

dtc_parameters_t dtc3_parameters = {
		.hdr = {
			.base = (uint32_t)&dtc3_parameters,
			.version = VERSION_OF_DTC_PARS,
			.size = sizeof(dtc_parameters_t),
			.id=DTC3_PARS_ID,
			.chksum = 0,
			.mask = 0,
		},
		.info = {
			.data = {0},
		}
};

//dtc_parameters_t dtc4_parameters = {
//		.hdr = {
//			.base = (uint32_t)&dtc4_parameters,
//			.version = VERSION_OF_DTC_PARS,
//			.size = sizeof(dtc_parameters_t),
//			.id=DTC4_PARS_ID,
//			.chksum = 0,
//			.mask = 0,
//		},
//		.info = {
//			.data = {0},
//		}
//};
//
//dtc_parameters_t dtc5_parameters = {
//		.hdr = {
//			.base = (uint32_t)&dtc5_parameters,
//			.version = VERSION_OF_DTC_PARS,
//			.size = sizeof(dtc_parameters_t),
//			.id=DTC5_PARS_ID,
//			.chksum = 0,
//			.mask = 0,
//		},
//		.info = {
//			.data = {0},
//		}
//};
//
//dtc_parameters_t dtc6_parameters = {
//		.hdr = {
//			.base = (uint32_t)&dtc6_parameters,
//			.version = VERSION_OF_DTC_PARS,
//			.size = sizeof(dtc_parameters_t),
//			.id=DTC6_PARS_ID,
//			.chksum = 0,
//			.mask = 0,
//		},
//		.info = {
//			.data = {0},
//		}
//};

static dtc_info_p dtc1_pars = &dtc1_parameters.info;
static dtc_info_p dtc2_pars = &dtc2_parameters.info;
static dtc_info_p dtc3_pars = &dtc3_parameters.info;
//static dtc_info_p dtc4_pars = &dtc4_parameters.info;
//static dtc_info_p dtc5_pars = &dtc5_parameters.info;
//static dtc_info_p dtc6_pars = &dtc6_parameters.info;

#define STR(x)          #x
#define NVM_PARS_SET_ID           STR(nvm_pars_set_id)
timer_p nvm_pars_set_timer_p = NULL;
static uint8 pars_set_flag = FALSE;

static void NvM_DTC_PARS_SET_Function(void)
{

    //PRINTF("NvM_DTC_PARS_SET_Function: do pars_set function\n");
    pars_set_flag = TRUE;
    pars_set((pars_ctx_p)&dtc1_parameters);
    pars_set((pars_ctx_p)&dtc2_parameters);
    pars_set((pars_ctx_p)&dtc3_parameters);

    if(nvm_pars_set_timer_p)
    {
        if (!strcmp(NVM_PARS_SET_ID, nvm_pars_set_timer_p->name))
        {
            timer_unset(&nvm_pars_set_timer_p);
            PRINTF("nvm_pars_set timer_unset\n");
        }        
    }
    //PRINTF("nvm_pars_set_timer_p set to NULL \n");
    nvm_pars_set_timer_p = NULL;
    pars_set_flag = FALSE;
}

static void EeppIfWrite(uint8* buff,uint16 length,uint32 add)
{
    uint16 i;
    uint32 checksum = 0;
    int q;
    int r;
    for(i = 0; i < length; i++)
    {
    	q = i / SIZE_OF_PARS_CTX_DATA;
    	r = i % SIZE_OF_PARS_CTX_DATA;

    	if(q == 0)
    	{	//0~231
            if(pars_set_flag == FALSE)
            {
                dtc1_pars->data[r] = buff[i];
            }
    	}
    	else if(q == 1)
    	{	//232~463
            if(pars_set_flag == FALSE)
            {
                dtc2_pars->data[r] = buff[i];
            }            
    	}
    	else if(q == 2)
    	{	//464~695
            if(pars_set_flag == FALSE)
            {
                dtc3_pars->data[r] = buff[i];
            }             
    	}
//    	else if(q == 3)
//    	{	//696~927
//    		dtc4_pars->data[r] = buff[i];
//    	}
//    	else if(q == 4)
//    	{	//928~1159
//    		dtc5_pars->data[r] = buff[i];
//    	}
//    	else
//    	{	//1160~1280
//    		dtc6_pars->data[r] = buff[i];
//    	}
    	checksum += buff[i];
//        dememu[add-(uint32)(&dememu[0]) +i] = buff[i];
    }

//    pars_set((pars_ctx_p)&dtc1_parameters);
//    pars_set((pars_ctx_p)&dtc2_parameters);
//    pars_set((pars_ctx_p)&dtc3_parameters);
//    pars_set((pars_ctx_p)&dtc4_parameters);
//    pars_set((pars_ctx_p)&dtc5_parameters);
//    pars_set((pars_ctx_p)&dtc6_parameters);

    if(NULL == nvm_pars_set_timer_p)
    {
        nvm_pars_set_timer_p = timer_set(NVM_PARS_SET_ID, TIMER_100_MS_TICKS, 1, (event_proc_p)NvM_DTC_PARS_SET_Function, NULL);
        
        if(nvm_pars_set_timer_p)
        {
            PRINTF("nvm_pars_set_timer start\n");
        }
        else
        {
            PRINTF("[Error]timer full: nvm_pars_set_timer cannot set\n");
        }            
    }

    PRINTF("EeppIfWrite checksum: %lu\n", checksum);
}

static void EeppIfRead(uint8* buff,uint16 length,uint32 add)
{
    uint16 i;
    uint32 checksum = 0;
    int q;
    int r;

    for(i = 0;i<length;i++)
    {
    	q = i / SIZE_OF_PARS_CTX_DATA;
    	r = i % SIZE_OF_PARS_CTX_DATA;

    	if(q == 0)
		{	//0~231
    		buff[i] = dtc1_pars->data[r];
		}
		else if(q == 1)
		{	//232~463
			buff[i] = dtc2_pars->data[r];
		}
		else if(q == 2)
		{	//464~695
			buff[i] = dtc3_pars->data[r];
		}
//		else if(q == 3)
//		{	//696~927
//			buff[i] = dtc4_pars->data[r];
//		}
//		else if(q == 4)
//		{	//928~1159
//			buff[i] = dtc5_pars->data[r];
//		}
//		else
//		{	//1160~1280
//			buff[i] = dtc6_pars->data[r];
//		}

//    	buff[i]= dememu[add-(uint32)(&dememu[0]) +i];
//        buff[i]= dtc1_pars->data[add-(uint32)(&dtc1_pars->data[0]) +i];
        checksum += buff[i];
    }
    PRINTF("EeppIfRead checksum: %lu\n", checksum);
}

Std_ReturnType NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType* RequestResultPtr
)
{

    Std_ReturnType ret = E_OK;
    
    if(NvM_TaskState == NVM_STATE_UNINIT)
    {
        ret = E_NOT_OK;
    }
    else if(NvM_TaskState == NVM_STATE_IDLE)
    {
        *RequestResultPtr = NVM_REQ_OK;
    }
    else/*NVM_STATE_READ  NVM_STATE_WRITE*/
    {
        *RequestResultPtr = NVM_REQ_PENDING;
    }

    return ret;
}

Std_ReturnType NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    void* NvM_DstPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NVM_STATE_IDLE == NvM_TaskState)&&(DEM_NVM_BLOCKID == BlockId))
    {
        NvmMemRecdInfo.NvMCurrentBlockId = BlockId;
        NvmMemRecdInfo.NvMMemAddr  = NvmMemBlockCfg.addrss;
        NvmMemRecdInfo.NvMDataSize = NvmMemBlockCfg.length;
        NvmMemRecdInfo.NvMPageSzie = NvmMemBlockCfg.psize;
        NvmMemRecdInfo.NvMDataPtr  = (uint8*)NvM_DstPtr;
        NvM_TaskState = NVM_STATE_READ;
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    void* NvM_SrcPtr
)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NVM_STATE_IDLE == NvM_TaskState)&&(DEM_NVM_BLOCKID == BlockId))
    {
        NvmMemRecdInfo.NvMCurrentBlockId = BlockId;
        NvmMemRecdInfo.NvMMemAddr  = NvmMemBlockCfg.addrss;
        NvmMemRecdInfo.NvMDataSize = NvmMemBlockCfg.length;
        NvmMemRecdInfo.NvMPageSzie = NvmMemBlockCfg.psize;
        NvmMemRecdInfo.NvMDataPtr  = (uint8*)NvM_SrcPtr;
        NvM_TaskState = NVM_STATE_WRITE;
        ret = E_OK;
    }
    return ret;
}
void NvM_Init(void)
{
    NvM_TaskState = NVM_STATE_IDLE;
    //NvmMemRecdInfo.NvMResult = NVM_REQ_NOT_OK;

    pars_get((pars_ctx_p)&dtc1_parameters, 0L, 0L);
    pars_get((pars_ctx_p)&dtc2_parameters, 0L, 0L);
    pars_get((pars_ctx_p)&dtc3_parameters, 0L, 0L);
//    pars_get((pars_ctx_p)&dtc4_parameters, 0L, 0L);
//    pars_get((pars_ctx_p)&dtc5_parameters, 0L, 0L);
//    pars_get((pars_ctx_p)&dtc6_parameters, 0L, 0L);

    NvmMemBlockCfg.addrss 	= (uint32)(&dtc1_pars->data[0]);
    NvmMemBlockCfg.length 	= (uint16)(sizeof(DemStorageMem));
    NvmMemBlockCfg.psize 	= (uint16)EEPPAGESIZE;
}

void NvM_MainFunction( void )
{
    uint16 len;
    /*Call EEP Write*/

    if((NvM_TaskState == NVM_STATE_WRITE)||(NvM_TaskState == NVM_STATE_READ))
    {
        if(NvmMemRecdInfo.NvMDataSize > NvmMemRecdInfo.NvMPageSzie)
        {
            len = NvmMemRecdInfo.NvMPageSzie;
        }
        else
        {
            len = NvmMemRecdInfo.NvMDataSize;
        }
        
        if(NvM_TaskState == NVM_STATE_WRITE)
        {
            EeppIfWrite(NvmMemRecdInfo.NvMDataPtr,len,NvmMemRecdInfo.NvMMemAddr);
            NvmMemRecdInfo.NvMMemAddr += len;
            NvmMemRecdInfo.NvMDataSize -= len;
            NvmMemRecdInfo.NvMDataPtr += len;
        
            if(NvmMemRecdInfo.NvMDataSize == 0)
            {
                NvM_TaskState = NVM_STATE_IDLE;
                //NvmMemRecdInfo.NvMResult = NVM_REQ_OK;
            }
        }
        else if(NvM_TaskState == NVM_STATE_READ)
        {
            /*Call EEP Read*/
            EeppIfRead(NvmMemRecdInfo.NvMDataPtr,len,NvmMemRecdInfo.NvMMemAddr);
            
            NvmMemRecdInfo.NvMMemAddr += len;
            NvmMemRecdInfo.NvMDataSize -= len;
            NvmMemRecdInfo.NvMDataPtr += len;
            if(NvmMemRecdInfo.NvMDataSize == 0)
            {
                NvM_TaskState = NVM_STATE_IDLE;
                //NvmMemRecdInfo.NvMResult = NVM_REQ_OK;
            }
        }
        else
        {
        
        }
    }
}

/********************** NVM Inferface define End **************************/

