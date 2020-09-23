/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Cfg.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dcm module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dcm module configuration File
*
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   04.03.02    12/11/2018     Geno          N/A          N/A
*
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
* Include files
********************************************************************************/
#include "Dcm_Cfg.h"
#include "Dcm.h"
#include "Dem.h"

#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

CONST(uint8, DCM_CONFIG_CONST)  gSidMap_1[DCM_MAX_NUMBER_OF_SID_MAP] =
{
    #if(ISO_15031_5 == STD_ON) 
 /* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07 */
    0xFFU,0x00U,0x01U,0x02U,0x03U,0xFFU,0x04U,0x05U, 
 /* 0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
    0x06U,0x07U,0x08U,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU, 
    #else
 /* 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07 */
    0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,
 /* 0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
    0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFu,
    #endif
 /* 0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17 */
    0x0U,0x1U,0xFFU,0xFFU,0x2U,0xFFU,0xFFU,0xFFU,
 /* 0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F */
    0xFFU,0x3U,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,
 /* 0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 */
    0xFFU,0xFFU,0x4U,0xFFU,0xFFU,0xFFU,0xFFU,0x5U,
 /* 0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F */
    0x6U,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0x7U,0xFFU,
 /* 0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37 */
    0xFFU,0x8U,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,
 /* 0x38  0x39  0x3A  0x3B  0x3C  0x3D  0x3E  0x3F */ 
    0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0x9U,0xFFU,
 /* 0x80  0x81  0x82  0x83  0x84  0x85  0x86  0x87 */
    0xFFU,0xFFU,0xFFU,0xFFU,0xFFU,0xAU,0xFFU,0xFFU
};

CONST(DcmDsdServiceTable, DCM_CONFIG_CONST)   gServiceTable_1[DCM_NUM_OF_SERVICE] =
{
    /*10*/
    #if(DCM_SERVICE_10_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_DiagnosticSessionControl,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING)
        },
        /* Sub-function Index Start */
        (DCM_SUBSERVICESTART),
        /* Sub-function Index End */
        (NUM_OF_10_SUB_FUNCTION - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*11*/
    #if(DCM_SERVICE_11_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_EcuReset,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING)
        },
        /* Sub-function Index Start */
        (NUM_OF_10_SUB_FUNCTION),
        /* Sub-function Index End */
        (NUM_OF_10_SUB_FUNCTION + (NUM_OF_11_SUB_FUNCTION-1U)),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*14*/
    #if(DCM_SERVICE_14_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_ClearDiagnosticInformation,
            /* Sub-function Flag */
            UDS_SERVICE_WITHOUT_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Sub-function Index End */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*19*/
    #if(DCM_SERVICE_19_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_ReadDTCInformation,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        (NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION),
        /* Sub-function Index End */
        (((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*22*/
    #if(DCM_SERVICE_22_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_ReadDataByIdentifier,
            /* Sub-function Flag */
            UDS_SERVICE_WITHOUT_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING)
        },
        /* Sub-function Index Start */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Sub-function Index End */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*27*/
    #if(DCM_SERVICE_27_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_SecurityAccess,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING)
        },
        /* Sub-function Index Start */
        ((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION),
        /* Sub-function Index End */
        ((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION) + NUM_OF_27_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    #endif 
    /*28*/
    #if(DCM_SERVICE_28_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_CommunicationControl,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        (((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION),
        /* Sub-function Index End */
        (((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION) + NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*2E*/
    #if(DCM_SERVICE_2E_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_WriteDataByIdentifier,
            /* Sub-function Flag */
            UDS_SERVICE_WITHOUT_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
            /* Supported Session */
            DCM_SESSION_EXTENDED_DIAGNOSTIC
        },
        /* Sub-function Index Start */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Sub-function Index End */
        (DCM_NUM_OF_SUB_SERVICE - 1U),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    #endif 
    /*31*/
    #if(DCM_SERVICE_31_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_RoutineControl,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
            /* Supported Session */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        ((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION),
        /* Sub-function Index End */
        ((((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION)+ NUM_OF_31_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
    #endif 
    /*3E*/
    #if(DCM_SERVICE_3E_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_TesterPresent,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        (((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION) + NUM_OF_31_SUB_FUNCTION),
        /* Sub-function Index End */
        (((((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION)+ NUM_OF_31_SUB_FUNCTION) + NUM_OF_3E_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    #endif 
    /*85*/
    #if(DCM_SERVICE_85_ENABLED == STD_ON)
    { 
        /* Reserved */
        DCM_DSDSIDTABID, 
        {
            /* Internal Callback Function */
            &DspInternal_Uds_ControlDTCSetting,
            /* Sub-function Flag */
            UDS_SERVICE_WITH_SUB_FUNCTION,
            /* Supported Security Level */
            (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
            /* Supported Session */
            (DCM_SESSION_EXTENDED_DIAGNOSTIC)
        },
        /* Sub-function Index Start */
        ((((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION) + NUM_OF_31_SUB_FUNCTION) + NUM_OF_3E_SUB_FUNCTION),
        /* Sub-function Index End */
        ((((((((NUM_OF_10_SUB_FUNCTION + NUM_OF_11_SUB_FUNCTION) + NUM_OF_19_SUB_FUNCTION )+ NUM_OF_27_SUB_FUNCTION) + NUM_OF_28_SUB_FUNCTION) + NUM_OF_31_SUB_FUNCTION) + NUM_OF_3E_SUB_FUNCTION) + NUM_OF_85_SUB_FUNCTION) - 1U),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }
    #endif 
};

CONSTP2CONST(CurrentSidMapType,DCM_CONFIG_CONST,DCM_CONFIG_CONST)  gCurrentSidMap = gSidMap_1;

CONST(DcmDsdSubService, DCM_CONFIG_CONST)  gDcmDsdSubService[DCM_NUM_OF_SUB_SERVICE]=
{
 /* 0x10*/
    {
        /* App Callback Function */
        &App_Default,
        /* App Post Callback Function */
        &App_DefaultPost,
        /* Sub-function ID */
        DCM_DEFAULT_SESSION,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &App_Programming,
        /* App Post Callback Function */
        &App_ProgrammingPost,
        /* Sub-function ID */
        DCM_PROGRAMMING_SESSION,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &App_Extended_Diagnostic,
        /* App Post Callback Function */
        &App_Extended_DiagnosticPost,
        /* Sub-function ID */
        DCM_EXTENDED_DIAGNOSTIC_SESSION,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
 /* 0x11*/
    {
        /* App Callback Function */
        &App_SoftReset_Reset,
        /* App Post Callback Function */
        &App_SoftReset_ResetPost,
        /* Sub-function ID */
		DCM_HARD_RESET,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
 /* 0x14*/
 /* 0x19*/
    {
        /* App Callback Function */
        &DemDcmIf_ReportNumberOfDTCByStatusMask,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DCM_REPORTNUMBEROFDTCBYSTATUSMASK,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &DemDcmIf_ReportDTCByStatusMask,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DCM_REPORTDTCBYSTATUSMASK,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &DemDcmIf_ReportSupportedDTC,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DCM_REPORTSUPPORTEDDTC,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
 /* 0x22*/
 /* 0x27*/
    {
        /* App Callback Function */
        &App_Request_Seed_L1,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        REQUEST_SEED_L1,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &App_Send_Key_L1,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        SEND_KEY_L1,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    }, 
 /* 0x28*/
    {
        /* App Callback Function */
        &App_EnableRxAndEnableTx_Control,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        ENABLE_RX_AND_TX,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &App_DisableRxAndDisableTx_Control,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DISABLE_RX_AND_TX,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
 /* 0x2E*/
 /* 0x31*/
    {
        /* App Callback Function */
        DCM_NULL,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        START_ROUTINE,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
	{
		/* App Callback Function */
		DCM_NULL,
		/* App Post Callback Function */
		DCM_NULL,
		/* Sub-function ID */
		STOP_ROUTINE,
		/* Sub-function Flag */
		SUB_FUNCTION_SUPPORTED,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	{
		/* App Callback Function */
		DCM_NULL,
		/* App Post Callback Function */
		DCM_NULL,
		/* Sub-function ID */
		REQUEST_ROUTINE_RESULT,
		/* Sub-function Flag */
		SUB_FUNCTION_SUPPORTED,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},        
 /* 0x3E*/
    {
        /* App Callback Function */
        DCM_NULL,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        ZERO_SUB_FUNCTION,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_PROGRAMMING),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
 /* 0x85*/
    {
        /* App Callback Function */
        &App_ON_Send,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DTC_RECORD_ON,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
    {
        /* App Callback Function */
        &App_OFF_Send,
        /* App Post Callback Function */
        DCM_NULL,
        /* Sub-function ID */
        DTC_RECORD_OFF,
        /* Sub-function Flag */
        SUB_FUNCTION_SUPPORTED, 
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  
        /* Supported Session */
        (DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    }, 
};

#define DCM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
