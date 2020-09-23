/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the adapter module based on uds
 *              platform.
 *
 *  \file       bl_adpt_uds_platform.c
 *  \ingroup    communication_adapter_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.2.1
 *  \date       19/06/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.02.00 | 27/09/2011 | mingqing.tang    | N/A | Boot030003
 *      03.03.00 | 29/09/2011 | mingqing.tang    | N/A | Boot030004
 *      03.05.00 | 12/10/2011 | mingqing.tang    | N/A | Boot030006
 *      04.00.00 | 10/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.02.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040003
 *      04.04.00 | 18/07/2012 | mingqing.tang    | N/A | Boot040005
 *      04.06.00 | 31/07/2012 | mingqing.tang    | N/A | Boot040007
 *      04.10.00 | 07/08/2012 | mingqing.tang    | N/A | Boot040011
 *      04.11.00 | 15/08/2012 | mingqing.tang    | N/A | Boot040012
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *      05.02.00 | 19/06/2014 | mingqing.tang    | N/A | BootSpec050001
 *      05.02.01 | 21/08/2014 | mingqing.tang    | N/A | BootSpec050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_rte.h"
#include "bl_data.h"
#include "bl_can_tp.h"
#include "bl_can_if.h"
#include "bl_dcm.h"
#include "bl_adapter.h"
#include "bl_security.h"
#include "bl_logical_block.h"

#include "bl_adpt_uds_platform.h"
#include "bl_adpt_uds_platform_cfg.h"
#include "bl_adapter_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,602,771,781,783,1251,1253,1257,1258,1505,1531,1532,2100,2103 EOF*/
/*PRQA S 3112,3120,3204,3211,3212,3218,3227,3416,3455,3673,4121,4152 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameters are not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 14.6(771):More than one break statement is being used to
 * terminate an iteration statement.
 * it can simplify the code and have no side-effect.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 783:A subsequent declaration of the identifier means that it is being used
 * both as a structure/union member and also as a label, ordinary identifier.
 * The member of the structure is used through the structure object.
 *
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 1253:Unsuffixed integer constant implicitly converted to different integer
 * type.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1258:Suffixed integer constant explicitly cast to another type.
 *
 * 1531:The object is referenced in only one translation unit.
 *
 * 1532:The function is only referenced in one translation unit.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3120:Hard-coded magic integer constant.
 * This is a only configuration.
 *
 * 3204:The variable is only set once and so it could be declared with the
 * 'const' qualifier.
 *
 * 3211:The global identifier is defined but not used.
 *
 * 3212:This explicit cast is redundant and could be removed.
 *
 * MISRA-C:2004 8.7(3218):File scope static identifier is only accessed in one
 * function.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * 3416:This boolean expression contains side effects.
 * This function has no side-effects.
 *
 * 3455:Macro argument contains a function call.
 *
 * MISRA-C:2004 16.7(3673): the pointer could be of type 'pointer to const'.
 * These functions are callback of the DCM module.
 *
 * MISRA-C:2004 10.3(4121):Cast of complex expression of integral type to wider
 * type.
 *
 * 4152:The identifier may cause confusion.
 * Adpt_UdsCallbackGetSeedForLevel1 is LEVEL One.
 * Adpt_UdsCallbackVerifyKeyForLevel1 is LEVEL One.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if (DCM_BUFFER_SIZE < ADPT_MAXNUM_OF_BLOCKLENGTH)
#error "the buffer of the Dcm module is too small."
#endif

#if (RTE_FUN_GATEWAY == BL_FUN_ON)
#error "the function of gateway is not ok."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
/*lint -emacro(778,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1)*/
/*lint -emacro(778,ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3)*/
/*lint -emacro(572,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1)*/
/*lint -emacro(572,ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3)*/
#define ADPT_P2START_TIMER          (DCM_P2STARTIMEVALUE/DCM_P2STARTIMER_DIV)
#define ADPT_SESSION_RESPONSE0      ((DCM_P2TIMEVALUE >> 8) & 0xFFu)
#define ADPT_SESSION_RESPONSE1      ((DCM_P2TIMEVALUE >> 0) & 0xFFu)
#define ADPT_SESSION_RESPONSE2      ((ADPT_P2START_TIMER >> 8) & 0xFFu)
#define ADPT_SESSION_RESPONSE3      ((ADPT_P2START_TIMER >> 0) & 0xFFu)

#define ADPT_MEMORY_LEN_FORMAT          (0x04u)
#define ADPT_MEMORY_ADDR_FORMAT         (0x04u)

#define ADPT_MEMORY_LENANDADDR_FORMAT   ((ADPT_MEMORY_LEN_FORMAT << 4) \
                                           | ADPT_MEMORY_ADDR_FORMAT)

#define ADPT_ERASE_DATA_LENGTH          (0x01u \
                                           + ADPT_MEMORY_LEN_FORMAT \
                                           + ADPT_MEMORY_ADDR_FORMAT)
#define ADPT_CHECKSUM_LENGTH            (0x04u)

#define ADPT_DATAFORMAT_IDEN            (0x00u)
#define ADPT_LENFORMAT_IDEN             (0x20u)
#define ADPT_IDEN_LEN_FORMAT            ((ADPT_LENFORMAT_IDEN >> 4) & 0x0Fu)
#define ADPT_REQDOWNLOAD_RESPLENGTH     (0x01u + ADPT_IDEN_LEN_FORMAT)

/** \brief Indicate the 31 service is ok.*/
#define ADPT_ROUTINE_CORRECT_RESULT     (0)
/** \brief Indicate the 31 service is not ok.*/
#define ADPT_ROUTINE_INCORRECT_RESULT   (1)

#define ADPT_UDS_SYSTEM_STATUS_MASK     (RTE_SYSFLAG_WRITE_FINGPRINT \
                                            | ADPT_SYSTEM_STATUS_MASK \
                                            | ADPT_STATUS_CHECK_PRECONDITION)

#define ADPT_UDS_STATUS_MASK            (ADPT_STATUS_ALLOW_TRANS_DATA \
                                            | ADPT_STATUS_BLOCK_FIRST_DATA \
                                            | ADPT_STATUS_SEGMENT_FIRST_DATA \
                                            | ADPT_STATUS_CONFIRM_TRANS_DATA)

#define ADPT_UDS_36_SERVICE_ID              (0x36u)
#define ADPT_UDS_31_SERVICE_ID              (0x31u)
#define ADPT_UDS_3E_SERVICE_ID              (0x3Eu)
#define ADPT_UDS_11_SERVICE_ID              (0x11u)

#define ADPT_UDS_36_SERVICE_INDEX_POS       (0x00u)
#define ADPT_UDS_36_SERVICE_DATA_POS        (0x01u)

#define ADPT_UDS_ERASE_MEMORY_FORMAT_POS    (0)
#define ADPT_UDS_ERASE_MEMORY_ADDRESS_POS   (1)
#define ADPT_UDS_ERASE_MEMORY_SIZE_POS      (5)

#define ADPT_UDS_34_SERVICE_IDEN_POS        (0)
#define ADPT_UDS_34_SERVICE_ADDRANDSIZE_POS (1)
#define ADPT_UDS_34_SERVICE_ADDRESS_POS     (2)
#define ADPT_UDS_34_SERVICE_SIZE_POS        (ADPT_UDS_34_SERVICE_ADDRESS_POS \
                                                + ADPT_MEMORY_ADDR_FORMAT)

#define ADPT_UDS_34_RESPONSE_FORMAT_POS     (0)
#define ADPT_UDS_34_RESPONSE_SIZE_POS       (1)


#define ADPT_STATUS_ALLOW_TRANS_DATA        DCM_MAKE_FLAG(0x20000000UL)
#define ADPT_STATUS_BLOCK_FIRST_DATA        DCM_MAKE_FLAG(0x10000000UL)
#define ADPT_STATUS_SEGMENT_FIRST_DATA      DCM_MAKE_FLAG(0x08000000UL)
#define ADPT_STATUS_CONFIRM_TRANS_DATA      DCM_MAKE_FLAG(0x04000000UL)
#define ADPT_STATUS_CHECK_PRECONDITION      DCM_MAKE_FLAG(0x02000000UL)

#define ADPT_UDS_MAX_CAN_FRAME_SIZE         (8)
#define ADPT_UDS_CAN_FRAME_INDEX_0          (0)
#define ADPT_UDS_CAN_FRAME_INDEX_1          (1)
#define ADPT_UDS_CAN_FRAME_INDEX_2          (2)
#define ADPT_UDS_CAN_FRAME_INDEX_3          (3)
#define ADPT_UDS_CAN_FRAME_INDEX_4          (4)
#define ADPT_UDS_CAN_FRAME_INDEX_5          (5)
#define ADPT_UDS_CAN_FRAME_INDEX_6          (6)
#define ADPT_UDS_CAN_FRAME_INDEX_7          (7)

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
/** \brief A alias of struct _tag_AdapterData.*/
typedef struct _tag_AdapterData bl_AdapterData_t;

#if (RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief A alias of struct _tag_GatewayTransmitList.*/
typedef struct _tag_GatewayTransmitList bl_GatewayTransmitList_t;
/** \brief A alias of struct _tag_GatewayConversion.*/
typedef struct _tag_GatewayConversion bl_GatewayConversion_t;
#endif

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/
/** \brief This is data of a adapter.*/
struct _tag_AdapterData
{
    struct _tag_SecurityDelay delay;    /**< security access delay*/
    bl_u8_t blockIndex;     /**< the block index of 36 service*/
    bl_Buffer_t serviceId;  /**< the id of processing service*/
    bl_Address_t address;   /**< the address of 36 service*/
    bl_Size_t remainSize;   /**< the remain size of 36 service*/
};

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief This is a list of gateway transmission.*/
struct _tag_GatewayTransmitList
{
    bl_u16_t handle;
    bl_u16_t number;
    struct _tag_GatewayConversion *data;
};

/**
 * \brief This is info of gateway conversion, it includes services
 *        needed to be transmitted.
 */
struct _tag_GatewayConversion
{
    bl_u8_t sid;
    bl_u16_t size;
    bl_Buffer_t *data;
};

#endif
/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief Gateway transmits messages.*/
static void _Adpt_UdsGatewayTransmit(bl_u8_t id);
#endif
/** \brief Send 0x78 negative response.*/
static void _Adpt_UdsPendingResponse(bl_u8_t id);
/** \brief Timeout callback of sending 0x78.*/
static void _Adpt_TimeOutCallBack(bl_u8_t id);
/** \brief send a response by comif.*/
static void _Adpt_SendResponse(bl_BufferSize_t size, const bl_Buffer_t *buffer);
/** \brief Set response info of session.*/
static bl_BufferSize_t _Adpt_SetSessionResp(bl_Buffer_t *buffer);
/** \brief Goto the session.*/
static void _Adpt_UdsGotoSession(bl_DownStatus_t sessionMask);
/** \brief Reset the bootloader.*/
static void _Adpt_UdsResetSystem(bl_u8_t sid, bl_u16_t flagId);
/** \brief Clear the download information.*/
static void _Adpt_UdsClearDownInfo(bl_AdapterData_t *adpt);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
/** \brief Private data variable.*/
static bl_AdapterData_t gs_UdsPrivateData;

static bl_u8_t gs_PreconditionFlg;

/*Modified by yq at 20170601*/
#if(CANTP_FUN_TX_FRAME_PADDING == BL_FUN_ON)
static const bl_Buffer_t gs_DefaultResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x06u,0x50u,0x01u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3,CANTP_FRAME_PADDING_VALUE
};

static const bl_Buffer_t gs_ReprogrammingResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE]=
{
    0x06u,0x50u,0x02u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3,CANTP_FRAME_PADDING_VALUE
};

static const bl_Buffer_t gs_ResetResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x02u,0x51u,0x01u,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE
};

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
static const bl_Buffer_t gs_StayInBootResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x04u,0x71u,0x01u,ADPT_STAY_IN_BOOT_RESPONSE_HID,
    ADPT_STAY_IN_BOOT_RESPONSE_LID,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE
};
#endif
#else
static const bl_Buffer_t gs_DefaultResponse[ADPT_UDS_CAN_FRAME_INDEX_7] =
{
    0x06u,0x50u,0x01u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3
};

static const bl_Buffer_t gs_ReprogrammingResponse[ADPT_UDS_CAN_FRAME_INDEX_7]=
{
    0x06u,0x50u,0x02u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3
};

static const bl_Buffer_t gs_ResetResponse[ADPT_UDS_CAN_FRAME_INDEX_3] =
{
    0x02u,0x51u,0x01u
};

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
static const bl_Buffer_t gs_StayInBootResponse[ADPT_UDS_CAN_FRAME_INDEX_5] =
{
    0x04u,0x71u,0x01u,ADPT_STAY_IN_BOOT_RESPONSE_HID,
    ADPT_STAY_IN_BOOT_RESPONSE_LID
};
#endif

#endif
/*end of #if(CANTP_FUN_TX_FRAME_PADDING == BL_FUN_ON)*/

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \details The data of gateway conversion. */
static const bl_u8_t gs_UdsGatewayData[ADPT_UDS_CONVERSION_DATA_LENGTH] =
{
    0x3Eu, 0x80u,
}

/** \details A list of gateway transmission. */
static const bl_GatewayTransmitList_t gs_UdsGatewayList =
{
    ADPT_UDS_COMOPS_HANDLE,
    ADPT_UDS_NUMBER_OF_GATEWAY,
    gs_UdsGateway,
};

/** \details The info of gateway conversion. */
static const bl_GatewayConversion_t gs_UdsGateway[ADPT_UDS_NUMBER_OF_GATEWAY] =
{
    {
        ADPT_UDS_3E_SERVICE_ID,
        ADPT_UDS_CONVERSION_DATA_LENGTH,
        gs_UdsGatewayData
    },
};

#endif

/*UdsFingerprint Buffer*/
static bl_Buffer_t gs_UdsFingerprint[RTE_FINGERPRINT_F15B_SIZE];

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/** \details The Uds platform adapter informations. */
const bl_Adapter_t g_UdsPlatformAdapter =
{
    0x00u, 0x00u, &Adpt_UdsInit, &Adpt_UdsCallback,
    &Adpt_UdsPeriodicCallback, &Adpt_UdsTimeOutCallBack,
#if (RTE_FUN_SYSTEM_SLEEP == BL_FUN_ON)
    &Canif_Sleep,
#else
    BL_NULL_PTR, /*RTE_FUN_SYSTEM_SLEEP is OFF*/
#endif
};
/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the uds module. This function mainly initialize
 *           CanTp, dcm and security access delay info.
 *
 *  \return If Initialization is successful return BL_ERR_OK,
 *          otherwise return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - Initialize successfully.
 *  \retval BL_ERR_NOT_OK   - Initialize unsuccessfully.
 *
 *  \note This function is called by the process driver module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_UdsInit(void)
{
    bl_Return_t ret;

    ret = Canif_Init();
    Cantp_Init();
    Dcm_Init();

    gs_UdsPrivateData.serviceId = 0;

    Adpt_InitDelayInfo(&gs_UdsPrivateData.delay);

    _Adpt_UdsGotoSession(DCM_STATUS_SESSION_DEFAULT);

    gs_PreconditionFlg = 0x00;

    return ret;
}

/**************************************************************************//**
 *
 *  \details Periodic callback of function Rte_PeriodicSchedule. This function
 *           needs to be called periodically, and mainly handles timer of dcm,
 *           and CanTp module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsPeriodicCallback(void)
{
    Adpt_DelayTimeCallback(&gs_UdsPrivateData.delay);
    Dcm_TimerFunction();
    Cantp_PeriodFunction();
    Dcm_MainFunction();
}

/**************************************************************************//**
 *
 *  \details Callback of the adapter, it should be always running. This
 *           function will be called by process driver module, and performs
 *           tx confirmation and rx indication.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsCallback(void)
{
    Canif_TxMainFunction();
    Canif_RxMainFunction();
    Canif_BusoffMainFunction();
}

/**************************************************************************//**
 *
 *  \details Callback of default session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1001(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    /*programming session.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_PROGRAMMING);
    if(BL_ERR_OK == ret)
    {
        if (Dcm_IsSuspendedResponse() != BL_ERR_OK)
        {
            _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_DefaultResponse),
                                gs_DefaultResponse);
        }

        g_RteInfo.SystemReset();
    }
    else
    {
        /*extended session.*/
        ret = Rte_IsValidStatus(&g_DownContext,
                                    DCM_STATUS_SESSION_EXTENDED);
        if(BL_ERR_OK == ret)
        {
            Dcm_StopS3Timer();

            _Adpt_UdsGotoSession(DCM_STATUS_SESSION_DEFAULT);
        }

        *respSize = _Adpt_SetSessionResp(buffer);
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of programming session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1002(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_CONDITIONSNOTCORRECT;
    bl_Return_t ret;

    (void)size;

    ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_CHECK_PRECONDITION);
    if (ret == BL_ERR_OK)
    {
        ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_DEFAULT);
            if (ret != BL_ERR_OK) /*the default can not go to programming.*/
            {
                Dcm_StartS3Timer();

                Lbm_ClearBlock(&g_DownContext);

                Rte_ClearAddressInfo(&g_DownContext);

                _Adpt_UdsGotoSession(DCM_STATUS_SESSION_PROGRAMMING);

                *respSize = _Adpt_SetSessionResp(buffer);

                resCode = DCM_E_POSITIVERESPONSE;
            }

    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of extended session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1003(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_CONDITIONSNOTCORRECT;
    bl_Return_t ret;

    (void)size;

    /*programming session.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_PROGRAMMING);
    if (ret != BL_ERR_OK) /*the programming can not go to extended.*/
    {
        Dcm_StartS3Timer();

        _Adpt_UdsGotoSession(DCM_STATUS_SESSION_EXTENDED);

        *respSize = _Adpt_SetSessionResp(buffer);

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1101(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)respSize;
    (void)buffer;
    (void)size;

    if (Dcm_IsSuspendedResponse() != BL_ERR_OK)
    {
        _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ResetResponse),
                        gs_ResetResponse);
    }

    g_RteInfo.SystemReset();

    /*never return*/

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadFingerprint(bl_BufferSize_t size,
                                                  bl_Buffer_t *buffer,
                                                  bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    /*read fingerprint.*/
    ret = Lbm_ReadFingerprint(buffer, respSize);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F187.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF187(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F187_FLAGID,
						 (bl_Size_t)ADPT_F187_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F187_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F18A.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF18A(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F18A_FLAGID,
						 (bl_Size_t)ADPT_F18A_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F197_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F197.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF197(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F197_FLAGID,
						 (bl_Size_t)ADPT_F197_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F197_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F193.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF193(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F193_FLAGID,
						 (bl_Size_t)ADPT_F193_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F193_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F195.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF195(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F195_FLAGID,
						 (bl_Size_t)ADPT_F195_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F195_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F18C.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF18C(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F18C_FLAGID,
						 (bl_Size_t)ADPT_F18C_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F18C_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reading F190.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadF190(bl_BufferSize_t size,
                                                      bl_Buffer_t *buffer,
                                                      bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	bl_Return_t ret;

	(void)size;

	/*read fingerprint.*/
	ret = Dm_ReadData(ADPT_F190_FLAGID,
						 (bl_Size_t)ADPT_F190_SIZE, buffer);
	if(BL_ERR_OK != ret)
	{
		resCode = DCM_E_CONDITIONSNOTCORRECT;
	}
	else
	{
		*respSize = ADPT_F190_SIZE;
	}

	return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of getting seed.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackGetSeedForLevel1(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;
#if(ADPT_FUN_DELAY_WITH_CONTINUOUS_SEED == BL_FUN_ON)
    bl_u16_t remainCount = 0;
#endif

    (void)size;

    do
    {
        /*judge wheter security access is available.*/
        ret = Adpt_IsAccessible(&gs_UdsPrivateData.delay);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
            break;
        }

        ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SECURITY_UNLOCK_1);
        if(BL_ERR_OK == ret)
        {
            /*when unlock, return seed 0x00u.*/
            Bl_MemSet(buffer,0,(bl_Size_t)SECM_ACCESS_SEED_SIZE);
            break;
        }

        /*If a seed is requested, return it.*/
        ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SECURITY_WAITKEY_1);
        if(BL_ERR_OK == ret)
        {
#if(ADPT_FUN_DELAY_WITH_CONTINUOUS_SEED == BL_FUN_ON)
            /*if always request seed, decrease attemptcount.*/
            remainCount = Adpt_DecreaseAttemptCount(&gs_UdsPrivateData.delay);
            if(remainCount == 0x00u)
            {
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
                /*set security access delay flag.*/
                (void)Dm_WriteDefaultData(gs_UdsPrivateData.delay.delayFlagId);
#endif

                Rte_SetMutexDownStatus(&g_DownContext,
                                        DCM_STATUS_SECURITY_LOCK_1,
                                        DCM_SECURITYACCESS_1_MASK);

                resCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;
                break;
            }
#endif

            /*return the last seed.*/
            Secm_GetSeed(buffer);

            break;
        }

        /*request a new seed.*/
        Secm_MakeNewSeed();
        /*Copy the seed to buffer*/
        Secm_GetSeed(buffer);
        /*set wait key status.*/
        Rte_SetDownStatus(&g_DownContext, DCM_STATUS_SECURITY_WAITKEY_1);

    }while(0);/*lint !e717*/

    *respSize = SECM_ACCESS_SEED_SIZE;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of verifying key.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallbackVerifyKeyForLevel1(bl_BufferSize_t size,
                                                     bl_Buffer_t *buffer,
                                                     bl_BufferSize_t *respSize)
{
    bl_u16_t remainCount;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext,
                                    DCM_STATUS_SECURITY_WAITKEY_1);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        /*verify key.*/
        ret = Secm_VerifyKey((bl_Size_t)size,buffer);
        if (ret != BL_ERR_OK)
        {
            remainCount = Adpt_DecreaseAttemptCount(&gs_UdsPrivateData.delay);
            if (0x00u == remainCount)
            {
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
                /*set security access delay flag.*/
                (void)Dm_WriteDefaultData(gs_UdsPrivateData.delay.delayFlagId);
#endif
                Rte_SetMutexDownStatus(&g_DownContext,
                                        DCM_STATUS_SECURITY_LOCK_1,
                                        DCM_SECURITYACCESS_1_MASK);

                resCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;
            }
            else
            {
                resCode = DCM_E_INVALIDKEY;
            }

            break;
        }
        else
        {
            gs_UdsPrivateData.delay.attemptCount = g_SecurityDelayInfo.attemptCount;
        }

        *respSize = 0x00u;
        Rte_SetMutexDownStatus(&g_DownContext,
                                DCM_STATUS_SECURITY_UNLOCK_1,
                                DCM_SECURITYACCESS_1_MASK);
    }while(0);/*lint !e717*/

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of enable or disable communication.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval DCM_E_POSITIVERESPONSE   - Positive response code.
 *  \retval DCM_E_REQUESTOUTOFRANGE - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallback28(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;
    (void)buffer;

    if(ADPT_COMMCONTROLTYPE_DATA != buffer[0])
    {
        resCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        *respSize = 0x00u;
    }


    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of writting fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallBackWriteFingerprint(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
//    bl_Return_t ret;
    (void)size;

    /*write fingerprint data.*/
//    ret = Dm_WriteData(ADPT_FINGERPRINT_FLAGID, (bl_Size_t)size, buffer);
//    if(BL_ERR_OK == ret)
    {
#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
        Lbm_SaveFingerprint(buffer);
#endif
        Rte_SetDownStatus(&g_DownContext, RTE_SYSFLAG_WRITE_FINGPRINT);
        *respSize = 0u;

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of writting F190.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallbackWriteF190(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    bl_Return_t ret;

    /*write fingerprint data.*/
    ret = Dm_WriteData(ADPT_F190_FLAGID, (bl_Size_t)size, buffer);
    if(BL_ERR_OK == ret)
    {
        *respSize = 0u;
        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}


/**************************************************************************//**
 *
 *  \details Callback of checking programming contiditions.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackCheckProgramCond(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;

    *respSize = 0x01u;
    buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;

    Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_CHECK_PRECONDITION);

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of erasing memory.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackEraseMemory(bl_BufferSize_t size,
                                              bl_Buffer_t *buffer,
                                              bl_BufferSize_t *respSize)
{
    bl_Size_t eraseSize;
    bl_Address_t address;
    bl_ResponseCode_t resCode = DCM_E_CONDITIONSNOTCORRECT;
    bl_Return_t ret;

    (void)size;

    if((bl_Buffer_t)ADPT_MEMORY_LENANDADDR_FORMAT
        == buffer[ADPT_UDS_ERASE_MEMORY_FORMAT_POS])
    {
        address = BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_ADDRESS_POS]);
        eraseSize = BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_SIZE_POS]);

        gs_UdsPrivateData.serviceId = ADPT_UDS_31_SERVICE_ID;
        _Adpt_TimeOutCallBack(ADPT_UDS_31_SERVICE_ID);

        ret = Adpt_EraseLB(&g_DownContext, address, eraseSize);
        if(BL_ERR_LB_OUTOFRANGE == ret)
        {
            resCode = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
            if(BL_ERR_OK == ret)
            {
                buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
            }
            else
            {
                Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);
                buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
            }

            *respSize = 0x01u;

            resCode = DCM_E_POSITIVERESPONSE;
        }

    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of checksum.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackCheckSum(bl_BufferSize_t size,
                                           bl_Buffer_t *buffer,
                                           bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    gs_UdsPrivateData.serviceId = ADPT_UDS_31_SERVICE_ID;
    _Adpt_TimeOutCallBack(ADPT_UDS_31_SERVICE_ID);

    ret = Adpt_VerifyData(&g_DownContext, (bl_Size_t)size, buffer);
    if(BL_ERR_OK == ret)
    {
        buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
    }

    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);

    *respSize = 0x01u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of checking compatibility.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackCheckCompatibility(bl_BufferSize_t size,
                                                     bl_Buffer_t *buffer,
                                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    ret = Adpt_CheckCompatibility();	//TODO::wood.liu CheckCompatibility
	//ret = BL_ERR_OK;	//TODO::yanan.zhao1
    if(BL_ERR_OK == ret)
    {
        buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
    }

    _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

    *respSize = 0x01u;

    return resCode;
}

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Callback of stayinboot.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackStayInBoot(bl_BufferSize_t size,
                                             bl_Buffer_t *buffer,
                                             bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)buffer;
    (void)size;

    *respSize = 0x00u;

    return resCode;
}
#endif

/**************************************************************************//**
 *
 *  \details Callback of requesting download.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback34(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_Size_t reqSize;
    bl_Address_t addr;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        if(BL_ERR_OK == ret)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        if((ADPT_DATAFORMAT_IDEN != buffer[ADPT_UDS_34_SERVICE_IDEN_POS])
            || (ADPT_MEMORY_LENANDADDR_FORMAT
                    != buffer[ADPT_UDS_34_SERVICE_ADDRANDSIZE_POS]))
        {
            resCode = DCM_E_CONDITIONSNOTCORRECT;
            break;
        }

        addr = BL_BE32_TO_MCU(&buffer[ADPT_UDS_34_SERVICE_ADDRESS_POS]);
        reqSize = BL_BE32_TO_MCU(&buffer[ADPT_UDS_34_SERVICE_SIZE_POS]);

        ret = Adpt_ActivateDownload(&g_DownContext, addr, reqSize);
        if(BL_ERR_OK == ret)
        {
            buffer[ADPT_UDS_34_RESPONSE_FORMAT_POS] = ADPT_LENFORMAT_IDEN;

#if(1u == ADPT_IDEN_LEN_FORMAT)
            /*get maxnum of block length.*/
            buffer[ADPT_UDS_34_RESPONSE_SIZE_POS] = ADPT_MAXNUM_OF_BLOCKLENGTH;
#elif (2u == ADPT_IDEN_LEN_FORMAT)
            BL_MCU_TO_BE16(&buffer[ADPT_UDS_34_RESPONSE_SIZE_POS],
                            ADPT_MAXNUM_OF_BLOCKLENGTH);
#else
#error "ADPT_IDEN_LEN_FORMAT is error."
#endif

            gs_UdsPrivateData.address = addr;
            gs_UdsPrivateData.remainSize = reqSize;
            gs_UdsPrivateData.blockIndex = 0x01u;

            *respSize = ADPT_REQDOWNLOAD_RESPLENGTH;

            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        }
        else
        {
            resCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }while(0);/*lint !e717*/

    if (resCode != DCM_E_POSITIVERESPONSE)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);
    }
    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of transferring data.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallback36(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_u8_t expendIndex;
    bl_Size_t dataSize;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    dataSize = (bl_Size_t)(size - 1u); /*overflow checking is not required.*/

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        expendIndex = gs_UdsPrivateData.blockIndex;

        ret = Rte_IsValidStatus(&g_DownContext,ADPT_STATUS_SEGMENT_FIRST_DATA);
        if(BL_ERR_NOT_OK == ret)
        {
            if (buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != expendIndex)
            {
                resCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
                break;
            }
            /*set first 0x36 service of a download segment.*/
            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_SEGMENT_FIRST_DATA);
        }

#if(ADPT_FUN_FIRST_DATA_PREPROCESS == BL_FUN_ON)
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_BLOCK_FIRST_DATA);
        if(BL_ERR_NOT_OK == ret)
        {

            /*set first 0x36 service of a logical block.*/
            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_BLOCK_FIRST_DATA);

            App_PreprocessData();
        }
#endif

        /*check whether the SN is valid.*/
        if(buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != expendIndex)
        {
            if (buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != (expendIndex - 1))
            {
                resCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
            }
            else
            {
                /*repeat request*/
                resCode = DCM_E_POSITIVERESPONSE;
            }
            break;
        }

        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_CONFIRM_TRANS_DATA);
        if (BL_ERR_OK == ret)
        {
            resCode = DCM_E_REQUESTOUTOFRANGE;
            break;
        }
        /*Check the size of received data.*/
        if(gs_UdsPrivateData.remainSize > ADPT_MAXNUM_OF_TRANS_DATA)
        {
            /*It is not the last 0x36 service.*/
            if(ADPT_MAXNUM_OF_TRANS_DATA != dataSize)
            {
                resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                break;
            }
        }
        else if(gs_UdsPrivateData.remainSize != dataSize)
        {
            resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            break;
        }
        else
        {
            /*last service and data size is ok.*/
        }

        /*send 0x78.*/
        gs_UdsPrivateData.serviceId = ADPT_UDS_36_SERVICE_ID;
        _Adpt_TimeOutCallBack(ADPT_UDS_36_SERVICE_ID);

        ret = Adpt_DownloadData(&g_DownContext,
                                    gs_UdsPrivateData.address,
                                    dataSize,
                                    &buffer[ADPT_UDS_36_SERVICE_DATA_POS]);
        if(BL_ERR_OK != ret)
        {
            resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            break;
        }
        else
        {
            gs_UdsPrivateData.blockIndex++;
            gs_UdsPrivateData.address += dataSize;
            gs_UdsPrivateData.remainSize -= dataSize;
        }
        if(0u == gs_UdsPrivateData.remainSize)
        {
            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_CONFIRM_TRANS_DATA);
        }
    }while(0);/*lint !e717*/

    if (resCode != DCM_E_POSITIVERESPONSE)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);
    }
    else
    {
        *respSize = 0x01u;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of requesting transfer exit.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback37(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)buffer;
    (void)size;

    ret = Rte_IsValidStatus(&g_DownContext,
                                ADPT_STATUS_CONFIRM_TRANS_DATA);
    if(BL_ERR_OK != ret)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

        resCode = DCM_E_REQUESTSEQUENCEERROR;
    }
    else
    {
        Rte_ClearDownStatus(&g_DownContext,
                                (ADPT_STATUS_SEGMENT_FIRST_DATA
                                | ADPT_STATUS_ALLOW_TRANS_DATA
                                | ADPT_STATUS_CONFIRM_TRANS_DATA));
        *respSize = 0x00u;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of keeping session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback3E(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;
    (void)buffer;

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
        _Adpt_UdsGatewayTransmit(ADPT_UDS_3E_SERVICE_ID);
#endif

    *respSize = 0x00u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of switching on of off dtc.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval DCM_E_POSITIVERESPONSE   - Positive response code.
 *  \retval DCM_E_SUBFUNCTIONNOTSUPPORTED - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback85(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;
    (void)buffer;

    *respSize = 0x00u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Timeout callback of sending 0x78.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsTimeOutCallBack(void)
{
    _Adpt_TimeOutCallBack(gs_UdsPrivateData.serviceId);

    return ;
}

/**************************************************************************//**
 *
 *  \details When the reprogram flag is valid, the RTE module call this
 *           function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_ReprogramValidProcess(void)
{
    Dcm_StartS3Timer();

    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SESSION_PROGRAMMING,
                            DCM_SESSION_MASK);

    gs_UdsPrivateData.delay.delayTime = 0u;
    _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ReprogrammingResponse),
                        gs_ReprogrammingResponse);

    return ;
}
#if(RTE_FUN_RST_RSP_IN_BT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details When the reset flag is valid, the RTE module call this function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_SystemResetProcess(void)
{
    _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ResetResponse),
                        gs_ResetResponse);

    return ;
}
#endif
#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details When the application is valid and the stay in boot is enabled,
 *           the RTE module call this function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_AppValidProcess(void)
{
    _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_StayInBootResponse),
                        gs_StayInBootResponse);

    return ;
}
#endif

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Gateway transmits messages by id.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsGatewayTransmit(bl_u8_t id)
{
    bl_u8_t i;
    bl_u16_t handle;
    bl_u16_t number;
    const bl_GatewayConversion_t *gateway;

    number = gs_UdsGatewayList.number;
    gateway = gs_UdsGatewayList.data;
    handle = gs_UdsGatewayList.handle;

    for(i = 0u; i < number; i++)
    {
        if(id == gateway[i].sid)
        {
            (void)Canif_Write(handle, gateway[i].size, gateway[i].data);
            break;
        }
    }

    return ;
}
#endif

/**************************************************************************//**
 *
 *  \details Send 0x78 negative response.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsPendingResponse(bl_u8_t id)
{
    bl_Buffer_t buffer[ADPT_UDS_MAX_CAN_FRAME_SIZE];

    buffer[ADPT_UDS_CAN_FRAME_INDEX_0] = DCM_NEGATIVE_RESPONSE_SIZE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_1] = DCM_NEGATIVE_RESPONSE_CODE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_2] = id;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_3] =
                                DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;
#if(CANTP_TX_FUN_FRAME_PADDING == BL_FUN_ON)
    buffer[ADPT_UDS_CAN_FRAME_INDEX_4] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_5] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_6] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_7] = CANTP_FRAME_PADDING_VALUE;
#endif

    _Adpt_SendResponse((bl_BufferSize_t)sizeof(buffer), buffer);

    Dcm_Allow_Positive_Response();

    return ;
}

/**************************************************************************//**
 *
 *  \details Send a response by ComOps in the g_RteInfo. When the transmitter
 *           is activated, This function will wait for some time configurated
 *           by ADPT_UDS_TX_TIMEOUT. If the response is not send within this
 *           time, this function will still return.
 *
 *  \param[in]  size    - the size of buffer.
 *  \param[in]  buffer  - the data will be send.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static void _Adpt_SendResponse(bl_BufferSize_t size, const bl_Buffer_t *buffer)
{
    bl_u32_t timeout = ADPT_UDS_TX_TIMEOUT;

    /*whether return value is necessary*/
    (void)Canif_Write(ADPT_UDS_TX_HANDLE, size, buffer);

    BL_WAITFOR_TIMEOUT(timeout,
                        Canif_IsWritten(ADPT_UDS_TX_HANDLE) == BL_ERR_OK)

    return ;
}
/**************************************************************************//**
 *
 *  \details Timeout callback of sending 0x78.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
static void _Adpt_TimeOutCallBack(bl_u8_t id)
{
    _Adpt_UdsPendingResponse(id);

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
    _Adpt_UdsGatewayTransmit(ADPT_UDS_3E_SERVICE_ID);
#endif
}

/**************************************************************************//**
 *
 *  \details Set response info of session.
 *
 *  \param[out]  buffer  - the pointer of response data.
 *
 *  \return Return the size of response data.
 *
 *  \since  V4.0.0
 *
 *****************************************************************************/
static bl_BufferSize_t _Adpt_SetSessionResp(bl_Buffer_t *buffer)
{
    bl_BufferSize_t size;

    size = ADPT_SESSION_RESPONSE_LEN;

    buffer[ADPT_UDS_CAN_FRAME_INDEX_0] = ADPT_SESSION_RESPONSE0;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_1] = ADPT_SESSION_RESPONSE1;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_2] = ADPT_SESSION_RESPONSE2;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_3] = ADPT_SESSION_RESPONSE3;

    return size;
}

/**************************************************************************//**
 *
 *  \details Go to the session
 *
 *  \param[in] sessionMask - the session will be gone.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsGotoSession(bl_DownStatus_t sessionMask)
{
    _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

#if (DCM_FUN_SECURITY_ACCESS == BL_FUN_ON)
    /*lock the level 1.*/
    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SECURITY_LOCK_1,
                            DCM_SECURITYACCESS_1_MASK);
#else
    /*unlock the level 1.*/
    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SECURITY_UNLOCK_1,
                            DCM_SECURITYACCESS_1_MASK);
#endif
    Rte_SetMutexDownStatus(&g_DownContext,
                            sessionMask,
                            DCM_SESSION_MASK);

    return ;
}

/**************************************************************************//**
 *
 *  \details Clear the download information.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
static void _Adpt_UdsClearDownInfo(bl_AdapterData_t *adpt)
{
    adpt->address = 0;
    adpt->remainSize = 0;
    adpt->blockIndex = 0;

    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_SYSTEM_STATUS_MASK);
    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);
    return ;
}

/**************************************************************************//**
 *
 *  \details Reset the system.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
static void _Adpt_UdsResetSystem(bl_u8_t sid, bl_u16_t flagId)
{
    bl_Return_t ret;

    ret = Dcm_IsSuspendedResponse();
    if (ret != BL_ERR_OK)
    {
        _Adpt_TimeOutCallBack(sid);
        /*write flag.*/
        (void)Dm_WriteDefaultData(flagId);
    }

    g_RteInfo.SystemReset();
}

