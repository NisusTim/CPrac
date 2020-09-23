/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Lcfg.c
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
*   Include files
*******************************************************************************/
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

#define DCM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

/* Configure S3 time */
CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_CONFIG_CONST) gDcmDspNonDefaultSessionS3Server = 5000UL;/*Unit:ms*/

/* Configure Session */
CONST(DcmDspSessionRow, DCM_CONFIG_CONST) gDcmDspSessionRow[KIND_OF_SESSION] = 
{
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_DEFAULT,
        /* P2Server */
        50UL,
        /* P2*Server */
        5000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_PROGRAMMING,
        /* P2Server */
        50UL,
        /* P2*Server */
        5000UL,
    },
    {
        DCM_NO_BOOT,
        /* Session */ 
        DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* P2Server */
        50UL,
        /* P2*Server */
        5000UL,
    }
};

#if(DCM_SERVICE_27_ENABLED == STD_ON)
CONST(DcmDspSecurityRow, DCM_CONFIG_CONST)  gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL] = 
{
    /*L1*/
    {
        10000UL,  /* Delay Time */
        1000UL,  /* Delay Time On Boot */
        4UL,  /* Key Size */
        3UL,  /* Attempt Number */
        4UL  /* Seed Size */
    },
};
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)
CONST(Dcm_22_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_22[NUMBER_OF_READ_DID] =  
{
    /* Index 0 */
    {
        /* DID */
		(uint32)0x0100U,
        /* Switch */
		STD_ON,
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0x0100,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 1 */
    {
        /* DID */
		(uint32)0xF180U,
		/* Switch */
		STD_ON,
		/* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF180,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
    /* Index 2 */
    {
        /* DID */
		(uint32)0xF182U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF182,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 3 */
    {
        /* DID */
        (uint32)0xF187U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
        &App_Read0xF187,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 4 */
    {
        /* DID */
		(uint32)0xF18CU,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF18C,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 5 */
    {
        /* DID */
		(uint32)0xF190U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		17U,
		/* Application Callback Function */
		&App_Read0xF190,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 6 */
    {
        /* DID */
		(uint32)0xF192U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF192,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 7 */
    {
        /* DID */
        (uint32)0xF193U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
        &App_Read0xF193,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 8 */
    {
        /* DID */
		(uint32)0xF194U,
        /* Switch */
		STD_ON,
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF194,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 9 */
    {
        /* DID */
        (uint32)0xF195U,
        /* Switch */
        STD_ON,  
        /* Data Size */
		16U,
		/* Application Callback Function */
        &App_Read0xF195,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 10 */
    {
        /* DID */
		(uint32)0xF198U,
        /* Switch */
		STD_ON,
        /* Data Size */
        10U,
		/* Application Callback Function */
		&App_Read0xF198,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 11 */
    {
        /* DID */
		(uint32)0xF199U,
        /* Switch */
		STD_ON,
        /* Data Size */
		4U,
		/* Application Callback Function */
		&App_Read0xF199,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 12 */
    {
        /* DID */
		(uint32)0xF19DU,
        /* Switch */
        STD_ON,  
        /* Data Size */
		4U,
		/* Application Callback Function */
		&App_Read0xF19D,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 13 */
    {
        /* DID */
		(uint32)0xF1A0U,
        /* Switch */
		STD_ON,
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF1A0,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 14 */
    {
        /* DID */
		(uint32)0xF1A1U,
        /* Switch */
		STD_ON,
        /* Data Size */
		16U,
		/* Application Callback Function */
		&App_Read0xF1A1,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
    /* Index 15 */
    {
        /* DID */
		(uint32)0x0300U,
        /* Switch */
		STD_ON,
        /* Data Size */
		4U,
		/* Application Callback Function */
		&App_Read0x0300,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
        /* Supported Address Type */
        PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
    },
	/* Index 16 */
	{
		/* DID */
		(uint32)0x0301U,
		/* Switch */
		STD_ON,
		/* Data Size */
		4U,
		/* Application Callback Function */
		&App_Read0x0301,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 17 */
	{
		/* DID */
		(uint32)0x0302U,
		/* Switch */
		STD_ON,
		/* Data Size */
		1U,
		/* Application Callback Function */
		&App_Read0x0302,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 18 */
	{
		/* DID */
		(uint32)0x0303U,
		/* Switch */
		STD_ON,
		/* Data Size */
		3U,
		/* Application Callback Function */
		&App_Read0x0303,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 19 */
	{
		/* DID */
		(uint32)0x0304U,
		/* Switch */
		STD_ON,
		/* Data Size */
		2U,
		/* Application Callback Function */
		&App_Read0x0304,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 20 */
	{
		/* DID */
		(uint32)0x0305U,
		/* Switch */
		STD_ON,
		/* Data Size */
		2U,
		/* Application Callback Function */
		&App_Read0x0305,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 21 */
	{
		/* DID */
		(uint32)0x0306U,
		/* Switch */
		STD_ON,
		/* Data Size */
		1U,
		/* Application Callback Function */
		&App_Read0x0306,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 22 */
	{
		/* DID */
		(uint32)0x0307U,
		/* Switch */
		STD_ON,
		/* Data Size */
		3U,
		/* Application Callback Function */
		&App_Read0x0307,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 23 */
	{
		/* DID */
		(uint32)0x0308U,
		/* Switch */
		STD_ON,
		/* Data Size */
		1U,
		/* Application Callback Function */
		&App_Read0x0308,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 24 */
	{
		/* DID */
		(uint32)0x0309U,
		/* Switch */
		STD_ON,
		/* Data Size */
		23U,
		/* Application Callback Function */
		&App_Read0x0309,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 25 */
	{
		/* DID */
		(uint32)0x030AU,
		/* Switch */
		STD_ON,
		/* Data Size */
		1U,
		/* Application Callback Function */
		&App_Read0x030A,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 26 */
	{
		/* DID */
		(uint32)0x030BU,
		/* Switch */
		STD_ON,
		/* Data Size */
		3U,
		/* Application Callback Function */
		&App_Read0x030B,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 27 */
	{
		/* DID */
		(uint32)0x030CU,
		/* Switch */
		STD_ON,
		/* Data Size */
		1U,
		/* Application Callback Function */
		&App_Read0x030C,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 28 */
	{
		/* DID */
		(uint32)0x030DU,
		/* Switch */
		STD_ON,
		/* Data Size */
		2U,
		/* Application Callback Function */
		&App_Read0x030D,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	},
	/* Index 29 */
	{
		/* DID */
		(uint32)0x030EU,
		/* Switch */
		STD_ON,
		/* Data Size */
		2U,
		/* Application Callback Function */
		&App_Read0x030E,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		(DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC),
		/* Supported Address Type */
		PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED
	}			
};
#endif

/* 0x23 0x3D */
#if((DCM_SERVICE_23_ENABLED == STD_ON)||(DCM_SERVICE_3D_ENABLED == STD_ON))
/* Config AddressFormat Bytes and SizeFormat Bytes */
CONST(Dcm_MemoryAddressFormatType, DCM_CONFIG_CONST)  gMemoryAddressFormat = 0U;
CONST(Dcm_MemorySizeFormatType, DCM_CONFIG_CONST) gMemorySizeFormat = 0U;
#endif

/* 0x23 */
#if(DCM_SERVICE_23_ENABLED == STD_ON)
CONST(DcmDspReadMemoryRangeInfo, DCM_CONFIG_CONST)   gDcmDspReadMemoryRangeInfo_23[NUMBER_OF_READ_ADDRESS_SEG] =
{
};
#endif

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
CONST(Dcm_24_ServiceInfoType, DCM_CONFIG_CONST)  gDcmDsdSubService_24[NUMBER_OF_READ_DID_24] =
{
};
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
CONST(Dcm_2A_ServiceInfoType, DCM_CONFIG_CONST)   gDcmDsdSubService_2A[NUMBER_OF_PERIODIC_DID] =
{
};
#endif

/* 0x2C */
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
CONST(Dcm_2C_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2C[NUMBER_OF_DYN_DID] =
{
};
#endif

/* 0x2E */
CONST(Dcm_2E_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID] =
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
{
    /* Index 0 */
    {
        /* DID */
		(uint32)0x0100U,
		/* Switch */
		STD_ON,
		/* Data Size */
		16U,
		/* App Callback Function */
		&App_Write0x0100,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
    /* Index 1 */
    {
        /* DID */
        (uint32)0xF190U,
        /* Switch */
        STD_ON,  
        /* Data Size */
        17U,
        /* App Callback Function */
        &App_Write0xF190,
        /* Supported Security Level */
        (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
        /* Supported Session */
        DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
	/* Index 2 */
	{
		/* DID */
		(uint32)0xF198U,
		/* Switch */
		STD_ON,
		/* Data Size */
		10U,
		/* App Callback Function */
		&App_Write0xF198,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 3 */
	{
		/* DID */
		(uint32)0xF199U,
		/* Switch */
		STD_ON,
		/* Data Size */
		4U,
		/* App Callback Function */
		&App_Write0xF199,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 4 */
	{
		/* DID */
		(uint32)0xF19DU,
		/* Switch */
		STD_ON,
		/* Data Size */
		4U,
		/* App Callback Function */
		&App_Write0xF19D,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 5 */
	{
		/* DID */
		(uint32)0xF1A0U,
		/* Switch */
		STD_ON,
		/* Data Size */
		16U,
		/* App Callback Function */
		&App_Write0xF1A0,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 6 */
	{
		/* DID */
		(uint32)0xF1A1U,
		/* Switch */
		STD_ON,
		/* Data Size */
		16U,
		/* App Callback Function */
		&App_Write0xF1A1,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	},
	/* Index 7 */
	{
		/* DID */
		(uint32)0x0300U,
		/* Switch */
		STD_ON,
		/* Data Size */
		4U,
		/* App Callback Function */
		&App_Write0x0300,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
        /* Supported Address Type */
        PHYSICAL_REQ_SUPPORTED
    },
	/* Index 8 */
	{
		/* DID */
		(uint32)0x0301U,
		/* Switch */
		STD_ON,
		/* Data Size */
		4U,
		/* App Callback Function */
		&App_Write0x0301,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	}
#if 0
	/* Index 9 */
	{
		/* DID */
		(uint32)0x0309U,
		/* Switch */
		STD_ON,
		/* Data Size */
		23U,
		/* App Callback Function */
		&App_Write0x0309,
		/* Supported Security Level */
		(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
		/* Supported Session */
		DCM_SESSION_EXTENDED_DIAGNOSTIC,
		/* Supported Address Type */
		PHYSICAL_REQ_SUPPORTED
	}
#endif
};
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
CONST(Dcm_2F_ServiceInfoType, DCM_CONFIG_CONST) gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID] =
{
};
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
CONST(DcmDspRoutine, DCM_CONFIG_CONST)  DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID] = 
{
    /* Index 0 */
    {
        /* SID */
        (uint32)0x0200U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0200,
        /* StopRoutineFnc */
        &App_StopRoutine0x0200,
        /* RequestResultsRoutineFnc */
        &App_ResultRoutine0x0200,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                3UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    /* Index 1 */
    {
        /* SID */
        (uint32)0x0201U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0201,
        /* StopRoutineFnc */
        &App_StopRoutine0x0201,
        /* RequestResultsRoutineFnc */
        &App_ResultRoutine0x0201,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                3UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    /* Index 2 */
    {
        /* SID */
        (uint32)0x0203U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0203,
        /* StopRoutineFnc */
        &App_StopRoutine0x0203,
        /* RequestResultsRoutineFnc */
        &App_ResultRoutine0x0203,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                2UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },
    /* Index 3 */
    {
        /* SID */
        (uint32)0x0204U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0x0204,
        /* StopRoutineFnc */
        &App_StopRoutine0x0204,
        /* RequestResultsRoutineFnc */
        &App_ResultRoutine0x0204,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                2UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    },    
    /* Index 4 */
    {
        /* SID */
        (uint32)0xAA00U,
        /* Switch */
        STD_ON, 
        /* RoutineUsePort, Reserved */
        0U,
        /* Fixed Length Check Flag */
        STD_ON,
        /* StartRoutineFnc */
        &App_StartRoutine0xAA00,
        /* StopRoutineFnc */
        &App_StopRoutine0xAA00,
        /* RequestResultsRoutineFnc */
        &App_ResultRoutine0xAA00,
        {
            {
                /* Supported Security Level */
                (DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),
                /* Supported Session */
                (DCM_SESSION_EXTENDED_DIAGNOSTIC),
                /* Supported Address Type */
                PHYSICAL_REQ_SUPPORTED
            },
            {
                1UL    /* Optional Data Length of RequestRoutineResults Response */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Request */
            },
            {
                0UL    /* Optional Data Length of StopRoutine Response */
            },
            {
                0UL     /* Optional Data Length of StartRoutine Request */
            },
            {
                1UL     /* Optional Data Length of StartRoutine Response */
            }
        },
    }        
};
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
CONST(DcmDspWriteMemoryRangeInfo, DCM_CONFIG_CONST)  gDcmDspWriteMemoryRangeInfo_3D[NUMBER_OF_WRITE_ADDRESS_SEG] =
{
};
#endif
