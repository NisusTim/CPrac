/*
 * Nvm.h
 *
 *  Created on: 2015-12-17
 *      Author: lim
 */

#ifndef NVM_H_
#define NVM_H_
#include "Std_Types.h"
#include "parameters.h"
#include <cstdint>

/*********************** NVM ************************/
typedef struct {
	volatile uint8_t data[SIZE_OF_PARS_CTX_DATA];
} dtc_info_t, *dtc_info_p;

typedef struct {
	pars_header_t	hdr;
	dtc_info_t		info;
}dtc_parameters_t, *dtc_parameters_p;

#define DTC1_PARS_ID									FOURCC('d','t','c','1')
#define DTC2_PARS_ID									FOURCC('d','t','c','2')
#define DTC3_PARS_ID									FOURCC('d','t','c','3')
//#define DTC4_PARS_ID									FOURCC('d','t','c','4')
//#define DTC5_PARS_ID									FOURCC('d','t','c','5')
//#define DTC6_PARS_ID									FOURCC('d','t','c','6')
#define dtc_pars_info_get(_data)					pars_info_get(DTC_PARS_ID, _data)
#define dtc_pars_info_set(_data,_cnt)				pars_info_set(DTC_PARS_ID, _data, _cnt)
#define dtc_pars_version_size_get(_ver,_size)		pars_version_size_get(DTC_PARS_ID, _ver,_size)

typedef uint8 NvM_ReqOperationType;
#define NVM_REQ_OP_NONE     0
#define NVM_REQ_OP_WRITE    1
#define NVM_REQ_OP_READ     2

typedef uint8 NvM_RequestResultType;
#define NVM_REQ_OK                 (0)
#define NVM_REQ_NOT_OK             (1)
#define NVM_REQ_PENDING            (2)
#define NVM_REQ_INTEGRITY_FAILED   (3)
#define NVM_REQ_BLOCK_SKIPPED      (4)
#define NVM_REQ_NV_INVALIDATED     (5)
#define NVM_REQ_CANCELLED          (6)  
#define NVM_REQ_REDUNDANCY_FAILED  (7) 
#define NVM_REQ_RESTORED_FROM_ROM  (8) 
#define NVM_REQ_BUSYING            (9)

//#define DEM_NVM_BLOCKID             2     //Remove by Wood, in order to resolve unused warning

#define NVM_NUMOFBLOCK              1u

typedef enum
{
    NVM_STATE_UNINIT      = 0, /* Block not init    */
    NVM_STATE_IDLE        = 1, /* Block Idle         */
    NVM_STATE_READ        = 2, /* Read Block       */    
    NVM_STATE_WRITE       = 3, /* Write Block       */
#if 0
    NVM_STATE_RESTORE     = 4,    
    NVM_STATE_ERASE       = 5, /* Erase Block              */
    NVM_STATE_INVALIDNV   = 6, /* InvalidateNvBlock     */
    NVM_STATE_SETRAMSTS   = 7, /* request Crc calculate */
    NVM_STATE_READALL     = 8, /* Read all           */    
    NVM_STATE_WRITEALL    = 9, /* Write All          */
    NVM_STATE_FSM_DEFAULT = 10 /* Other State      */
#endif
}NvM_State_t;

typedef struct
{
    uint16 NvMCurrentBlockId;
    uint16 NvMDataSize;
    //uint16 NvMDoneSize;
    uint16 NvMPageSzie;
    uint32 NvMMemAddr;
    uint8* NvMDataPtr;
    //NvM_RequestResultType  NvMResult;
}NvmMemRecdInfoType;

typedef struct
{
    uint32 addrss;
    uint16 length;
    uint16 psize;/*page size*/
}NvmMemBlockCfgType;

typedef uint16 NvM_BlockIdType;
extern Std_ReturnType NvM_GetErrorStatus(
    NvM_BlockIdType BlockId,
    NvM_RequestResultType* RequestResultPtr
);

extern Std_ReturnType NvM_ReadBlock(
    NvM_BlockIdType BlockId,
    void* NvM_DstPtr
);

extern Std_ReturnType NvM_WriteBlock(
    NvM_BlockIdType BlockId,
    void* NvM_SrcPtr
);
extern void NvM_Init(void);
extern void NvM_MainFunction( void );
#endif /* NVM_H_ */
