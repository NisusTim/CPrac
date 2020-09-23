/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Dcm.c
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
#include "App_Dcm.h"
#if(DCM_SERVICE_28_ENABLED == STD_ON)
#include "Com.h"
#endif
#include "Dem.h"
#include "Dem_Lcfg.h"
#include "App_boot.h"
#include "SWT.h"
#include <S32R274.h>

#include "Utility.h"
#include "sys_shared.h"
#include "can_cubtek.h"
#include "fbl_parameter.h"
#include "coefs.h"
#include "frame.h"
#include "timer.h"
#include "static_vertical_feedback.h"
#include "vertical_feedback_shared.h"
#include "alignment_main.h"
#include "ism330dlc.h"

#include <cmath>    //round
/*******************************************************************************
* Macros and Typedef
********************************************************************************/
#define STR(x)          #x

#if(DCM_SERVICE_85_ENABLED == STD_ON)
uint8 gDTCSwitch;
#endif

#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#define W8(addr, value)              (*((uint8 *) (addr)) = (value))
#define R8(addr)                     (*((uint8 *) (addr)))
#endif

#if(ISO_15031_5 == STD_ON)
/* For 0x01*/
/* For 0x02*/
/* For 0x06*/
/* For 0x09*/
#endif
#define IS_FW_CONTAIN_BOOTLOADER		TRUE
/* For 0x22*/
#define ReadHandle_0x0100    (0U)
#define ReadHandle_0xF180    (1U)
#define ReadHandle_0xF182    (2U)
#define ReadHandle_0xF187    (3U)
#define ReadHandle_0xF18C    (4U)
#define ReadHandle_0xF190    (5U)
#define ReadHandle_0xF192    (6U)
#define ReadHandle_0xF193    (7U)
#define ReadHandle_0xF194    (8U)
#define ReadHandle_0xF195    (9U)
#define ReadHandle_0xF198    (10U)
#define ReadHandle_0xF199    (11U)
#define ReadHandle_0xF19D    (12U)
#define ReadHandle_0xF1A0    (13U)
#define ReadHandle_0xF1A1    (14U)
#define ReadHandle_0x0300    (15U)
#define ReadHandle_0x0301    (16U)
#define ReadHandle_0x0302    (17U)
#define ReadHandle_0x0303    (18U)
#define ReadHandle_0x0304    (19U)
#define ReadHandle_0x0305    (20U)
#define ReadHandle_0x0306    (21U)
#define ReadHandle_0x0307    (22U)
#define ReadHandle_0x0308    (23U)
#define ReadHandle_0x0309    (24U)
#define ReadHandle_0x030A    (25U)
#define ReadHandle_0x030B    (26U)
#define ReadHandle_0x030C    (27U)
#define ReadHandle_0x030D    (28U)
#define ReadHandle_0x030E    (29U)
/* For 0x24*/

/* For 0x28 */
#define Dcm_EnRx_EnTx                (0U)
#define Dcm_DisRx_EnTx               (1U)
#define Dcm_EnRx_DisTx               (2U)
#define Dcm_DisRx_DisTx              (3U)


/* For 0x2A*/

/* For 0x2C*/

/* For 0x2E*/
#define WriteHandle_0x0100    (0U)
#define WriteHandle_0xF190    (1U)
#define WriteHandle_0xF198    (2U)
#define WriteHandle_0xF199    (3U)
#define WriteHandle_0xF19D    (4U)
#define WriteHandle_0xF1A0    (5U)
#define WriteHandle_0xF1A1    (6U)
#define WriteHandle_0x0300    (7U)
#define WriteHandle_0x0301    (8U)
#define WriteHandle_0x0309    (9U)

/* For 0x2F*/

/* For 0x31*/
#define RoutineHandle_0x0200    (0U)
#define RoutineHandle_0x0201    (1U)
#define RoutineHandle_0x0203    (2U)
#define RoutineHandle_0x0204    (3U)  // IMU
#define RoutineHandle_0xAA00    (4U)  // RMTP enable/disable

timer_p auto_calibration_timer_p = NULL;

#define ROUNDING_NEAREST_TENTH  0.049f

typedef enum
{
    CALIBRATION_CONDITION_CORRECT = 0,
    CALIBRATION_CONDITION_INCORRECT_VEHILCE_SPEED_GREATER_THAN_ZERO,
    CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE,
    CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST,
    CALIBRATION_CONDITION_INCORRECT_DID0300_NOT_WRITTEN,
    CALIBRATION_CONDITION_INCORRECT_DID0301_NOT_WRITTEN
}RID_200_StartRoutine_Status;

typedef enum
{
    AUTO_CALIBRATION_CONDITION_CORRECT = 0,
    AUTO_CALIBRATION_CONDITION_RESVERD,
    AUTO_CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE,
    AUTO_CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST,
}RID_201_StartRoutine_Status;

typedef enum
{
    CALIBRATION_RESULT_CORRECT = 0,
    CALIBRATION_RESULT_EQUIPMENT_NOT_FOUND,
    CALIBRATION_RESULT_EQUIPMENT_RANGE_ERROR,
    CALIBRATION_RESULT_EQUIPMENT_AOA_ERROR,
    CALIBRATION_RESULT_EQUIPMENT_SIGNAL_MAG_ERRPR,
    CALIBRATION_RESULT_EQUIPMENT_HARDWARE_ERROR,
    CALIBRATION_RESULT_EQUIPMENT_TIMEOUT,
    CALIBRATION_RESULT_EQUIPMENT_VAOA_ERROR,
    CALIBRATION_RESULT_EQUIPMENT_PROCESSING,
}RID_200_ResultRoutine_Status;

typedef enum
{
    AUTO_ALIGNMENT_H_RESULT_CORRECT = 0,
    AUTO_ALIGNMENT_H_RESULT_RESVERD,
    AUTO_ALIGNMENT_H_RESULT_RESVERD_2,
    AUTO_ALIGNMENT_H_RESULT_ANGLE_OUT_OF_RANGE,
    AUTO_ALIGNMENT_H_RESULT_SIGNAL_ERROR,
    AUTO_ALIGNMENT_H_RESULT_YAWRATE_ERROR,
    AUTO_ALIGNMENT_H_RESULT_TIMEOUT,
    AUTO_ALIGNMENT_H_RESULT_RESVERD_5,
    AUTO_ALIGNMENT_H_RESULT_PROCESSING,

    AUTO_ALIGNMENT_V_RESULT_CORRECT = 0,
    AUTO_ALIGNMENT_V_RESULT_RESVERD,
    AUTO_ALIGNMENT_V_RESULT_RESVERD_2,
    AUTO_ALIGNMENT_V_RESULT_ANGLE_OUT_OF_RANGE,
    AUTO_ALIGNMENT_V_RESULT_SIGNAL_ERROR,
    AUTO_ALIGNMENT_V_RESULT_ACC_ERROR,
    AUTO_ALIGNMENT_V_RESULT_TIMEOUT,
    AUTO_ALIGNMENT_V_RESULT_RESVERD_5,
    AUTO_ALIGNMENT_V_RESULT_PROCESSING,
}RID_201_ResultRoutine_Status;

typedef enum
{
    VERTICAL_CALIBRATION_CONDITION_CORRECT = 0,
    VERTICAL_CALIBRATION_CONDITION_VEHILCE_SPEED_GREATER_THAN_ZERO,
    VERTICAL_CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE,
    VERTICAL_CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST,
}RID_203_StartRoutine_Status;

typedef enum
{
    VERTICAL_CALIBRATION_RESULT_CORRECT = 0,
    VERTICAL_CALIBRATION_RESULT_RESVERD,
    VERTICAL_CALIBRATION_RESULT_RESVERD_2,
    VERTICAL_CALIBRATION_RESULT_AOA_OUT_OF_RANGE,
    VERTICAL_CALIBRATION_RESULT_RESVERD_3,
    VERTICAL_CALIBRATION_RESULT_ACC_ERROR,
    VERTICAL_CALIBRATION_RESULT_TIMEOUT,
    VERTICAL_CALIBRATION_RESULT_RESVERD_5,
    VERTICAL_CALIBRATION_RESULT_PROCESSING,
}RID_203_ResultRoutine_Status;

#define DTCS_EXCEPT    (0xFFBFDCFFFFFFFFFF) //Ignore:   Missing_Calibration,
                                            //          Invalid_Steering_Angle_signal,
                                            //          Invalid_Yaw_Rate_signal
											//			Radar_Mount_Position_Shift_Error

#define AUTO_CALIB_ID           STR(auto_calib)

#define UNDEFINED       (0x00U)
#define NOT_COMPLETED   (0x55U)
#define COMPLETED       (0xAAU)

typedef union
{
    uint8 result;
    struct
    {
        uint8 vertical:     4;  //b4~b7
        uint8 horizontal:   4;  //b0~b3
    };
}RID_0201_result_t;
static uint8 RMTP_HCAN_Config_Flag = FALSE;

typedef enum
{

	IMU_RESULT_CORRECT = 0,
	IMU_RESULT_INCORRECT_VEHILCE_SPEED_GREATER_THAN_ZERO,
	IMU_RESULT_INCORRECT_RADAR_IN_CALIBRATION_MODE,
	IMU_RESULT_INCORRECT_DTCS_EXIST,
	IMU_RESULT_INCORRECT_CALIB,	
	IMU_RESULT_INIT,
	IMU_RESULT_TIMEOUT,
	IMU_RESULT_RESVERD_2,
	IMU_RESULT_PROCESSING,	

}RID_204_ResultRoutine_Status;

typedef enum
{

	IMU_STATUS_CORRECT = 0,
	IMU_STATUS_INCORRECT_VEHILCE_SPEED_GREATER_THAN_ZERO,
	IMU_STATUS_INCORRECT_RADAR_IN_CALIBRATION_MODE,
	IMU_STATUS_INCORRECT_DTCS_EXIST,
	IMU_STATUS_INCORRECT_CALIB,
	IMU_STATUS_INIT,
	IMU_STATUS_TIMEOUT,
	IMU_STATUS_RESVERD_2,
	IMU_STATUS_PROCESSING,

}RID_204_Routine_Status;

typedef union
{
    uint8 result;
    struct
    {
        uint8 self_test:    4;  //b4~b7
        uint8 self_calib:   4;  //b0~b3
    };
}RID_204_result_t;


timer_p imu_calibration_timer_p = NULL;
#define IMU_CALIB_ID           STR(imu_calib)

static uint8 IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
static uint8 IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;

static uint8 IMU_SELF_TEST_RESULT = IMU_RESULT_INIT;
static uint8 IMU_SELF_CALIB_RESULT = IMU_RESULT_INIT;
/*******************************************************************************
*   Internal Function declaration
*******************************************************************************/
FUNC(void,DCM_CODE) Update_RadarFailsafeState(RadarFailsafeState_p failState);
FUNC(void,DCM_CODE) App_AutoCalibrationTimeout();
FUNC(void,DCM_CODE) App_IMUCalibrationTimeout();

STATIC FUNC(void,DCM_CODE) App_Write0x0100_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF190_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF198_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF199_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF19D_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF1A0_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0xF1A1_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0x0300_Fun(void);
STATIC FUNC(void,DCM_CODE) App_Write0x0301_Fun(void);
//STATIC FUNC(void,DCM_CODE) App_Write0x0309_Fun(void);

STATIC FUNC(void,DCM_CODE) start_rountine_0x0200(void);
STATIC FUNC(void,DCM_CODE) stop_rountine_0x0200(void);
STATIC FUNC(void,DCM_CODE) start_rountine_0x0201(void);
STATIC FUNC(void,DCM_CODE) stop_rountine_0x0201(void);
STATIC FUNC(void,DCM_CODE) start_rountine_0x0203(void);
STATIC FUNC(void,DCM_CODE) stop_rountine_0x0203(void);
//STATIC FUNC(void,DCM_CODE) start_rountine_0x0204(void);
STATIC FUNC(void,DCM_CODE) start_rountine_imu_self_test_0x0204(void);
STATIC FUNC(void,DCM_CODE) start_rountine_imu_self_calib_0x0204(void);
STATIC FUNC(void,DCM_CODE) stop_rountine_0x0204(void);
STATIC FUNC(void,DCM_CODE) App_SoftReset_ResetPost_Handler(void);
STATIC FUNC(void,DCM_CODE) start_rountine_0xAA00(void);
STATIC FUNC(void,DCM_CODE) stop_rountine_0xAA00(void);
//STATIC FUNC(void,DCM_CODE) result_routine_0xAA00(void);
STATIC FUNC(void,DCM_CODE) set_rmtp_hcan_config_enable(void);
STATIC FUNC(void,DCM_CODE) set_rmtp_hcan_config_disable(void);

FUNC(uint8,DCM_CODE) static_vertical_alignment_completion_flag();
FUNC(uint8,DCM_CODE) horizontal_alignment_result_mapping(uint8 result);
FUNC(uint8,DCM_CODE) vertical_alignment_result_mapping(uint8 result);
FUNC(uint8,DCM_CODE) static_vertical_alignment_result_mapping(uint8 result);
FUNC(uint8,DCM_CODE) alignment_angle_convert(float angle, float sign, float scale);

STATIC FUNC(void,DCM_CODE) imu_self_calib_rid_204_cb(imu_calib_result_p res);
STATIC FUNC(void,DCM_CODE) imu_self_test_rid_204_cb(int res);

STATIC FUNC(float,DCM_CODE) get_auto_alignment_combine_progress_rate();
STATIC FUNC(float,DCM_CODE) get_auto_hori_alignmnet_progress_rate();
STATIC FUNC(float,DCM_CODE) get_auto_vert_alignmnet_progress_rate();

static inline const char *string_of_result(calib_equipment_e result);
void iron_calib_done_handler(calib_equipment_e iron_calib_status, iron_calib_result_p iron_calib_result);

/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
#if(ISO_15031_5 == STD_ON)
/* For 0x02*/
/* For 0x03*/
/* For 0x04*/
/* For 0x07*/
/* For 0x08*/
/* For 0x0A*/
#endif

static uint8 DTCStatusAvailabilityMask = 0x49U;
uint32 SupportedDTCGroup = 0x00U;
static uint32 SupportedDTC[NUM_OF_DTC] =
{
	0xC07688,
	0xC23A87,
	0x950098,
	0x95009A,
	0x9500A3,
	0x9500A2,
	0x9501A3,
	0x9501A2,
	0x9502A3,
	0x9502A2,
	0x911717,
	0x911716,
	0x950198,
	0x95019A,
	0x950049,
	0x950045,
	0x950044,
	0x950096,
	0x950196,
	0x950054,
	0x950154,
	0x950081,
	0x950181,
	0x950281,
	0x950381,
	0x950481,
	0x950097
};
uint8 DTCStatus[NUM_OF_DTC] =
{
    0x08U
};

#define LEN_OF_F187				(12U)
#define LEN_OF_F18A				(10U)
#define LEN_OF_F18C				(14U)
#define LEN_OF_F190				(17U)
#define LEN_OF_F193				(15U)
#define LEN_OF_F195				(15U)
#define LEN_OF_F197				(10U)

//static uint8 ApplicationSoftwareIdentification[32] =
//{
//    0x00, 0x01, 0x02, 0x03,
//    0x04, 0x05, 0x06, 0x07,
//    0x08, 0x09, 0x0a, 0x0b,
//    0x0c, 0x0d, 0x0e, 0x0f,
//    0x10, 0x11, 0x12, 0x13,
//    0x14, 0x15, 0x16, 0x17,
//    0x18, 0x19, 0x1a, 0x1b,
//    0x1c, 0x1d, 0x1e, 0x1f
//};

/* Below codes are demo for 0x27, all of them can be deleted */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
STATIC uint32 seedToKey_L1(uint32 seed);
STATIC uint32 seedToKey_L1_Hirain(uint32 seed, uint32 mask);
STATIC uint32 seedToKey_L1_Neusoft(uint32 seed, uint32 mask);
STATIC uint32 seedToKey_L1_Cubtek(uint32 seed, uint32 mask);
static uint32 _seed = 0x0C;
#endif

#if(DCM_SERVICE_28_ENABLED == STD_ON)
/* if Hirain Com& Nm are used, don't change below codes */
static uint8 Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
#endif

//static SOD_L_1_t sod_l_1 = {.Raw = 0};
/***************************************************************************
* Internal Function Implementation
****************************************************************************/
FUNC(void,DCM_CODE) Update_RadarFailsafeState(RadarFailsafeState_p failState)
{
	uint8 tempValue = 0;

	Dem_GetEventStatus(DTC_0xC07688_INDEX, &tempValue);
	failState->Communication_Bus_OFF = tempValue;

	Dem_GetEventStatus(DTC_0xC23A87_INDEX, &tempValue);
	failState->Lost_Communication_With_Camera = tempValue;

	Dem_GetEventStatus(DTC_0x950098_INDEX, &tempValue);
	failState->MCU_Temperature_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x95009A_INDEX, &tempValue);
	failState->MCU_Temperature_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x9500A3_INDEX, &tempValue);
	failState->MCU_Voltage_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x9500A2_INDEX, &tempValue);
	failState->MCU_Voltage_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x9501A3_INDEX, &tempValue);
	failState->RF_Voltage1_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x9501A2_INDEX, &tempValue);
	failState->RF_Voltage1_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x9502A3_INDEX, &tempValue);
	failState->RF_Voltage2_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x9502A2_INDEX, &tempValue);
	failState->RF_Voltage2_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x911717_INDEX, &tempValue);
	failState->Battery_Voltage_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x911716_INDEX, &tempValue);
	failState->Battery_Voltage_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x950198_INDEX, &tempValue);
	failState->RF_Temperature_too_high = tempValue;

	Dem_GetEventStatus(DTC_0x95019A_INDEX, &tempValue);
	failState->RF_Temperature_too_low = tempValue;

	Dem_GetEventStatus(DTC_0x950054_INDEX, &tempValue);
	failState->Missing_Calibration = tempValue;

	Dem_GetEventStatus(DTC_0x950154_INDEX, &tempValue);
	failState->Radar_Mount_Position_Shift_Error = tempValue;

	Dem_GetEventStatus(DTC_0x950081_INDEX, &tempValue);
	failState->Invalid_Vehicle_Speed_signal = tempValue;

	Dem_GetEventStatus(DTC_0x950181_INDEX, &tempValue);
	failState->Invalid_Yaw_Rate_signal = tempValue;

	Dem_GetEventStatus(DTC_0x950281_INDEX, &tempValue);
	failState->Invalid_Steering_Angle_signal = tempValue;

	Dem_GetEventStatus(DTC_0x950381_INDEX, &tempValue);
	failState->Invalid_Gear_position_signal = tempValue;

	Dem_GetEventStatus(DTC_0x950481_INDEX, &tempValue);
	failState->Invalid_IGN_Sta_signal = tempValue;

	Dem_GetEventStatus(DTC_0x950097_INDEX, &tempValue);
	failState->Radar_block = tempValue;
}

/***************************************************************************
* Global Function Implementation
****************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL == STD_ON)
/****************************************************************************
* Name         :App_DiagnosticActive 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :N/A  
* Return code  :N/A  
* Description  :Check is it possible to enable Dcm module.  
*                
******************************************************************************/
FUNC(Std_ReturnType,DCM_CODE) App_DiagnosticActive(void)
{
	return E_OK;
}
#endif 

#if(ISO_15031_5 == STD_ON)
#if(DCM_SERVICE_01_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_03_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_04_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_06_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_07_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_08_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_09_ENABLED == STD_ON)
#endif

#if(DCM_SERVICE_0A_ENABLED == STD_ON)
#endif
#endif 

/* 0x10 */
#if(DCM_SERVICE_10_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_Default 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_0].DcmDspSessionP2StarServerMax/10; //resolution 10ms
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_DefaultPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT); 
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE; 
        Clr_S3_Server_Timer(); 
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* Reset the CommunicationControl Flags */
        #if(DCM_SERVICE_28_ENABLED == STD_ON)
        switch(Dcm_ComMessage_Status)
        {
            case Dcm_DisRx_DisTx:
                 Com_TxStart();
                 Com_RxStart();
                 cubtek_faw_did_ds_can_status_set(CAN_EnRx_EnTx);
                 break;
        
            case Dcm_DisRx_EnTx:
                 Com_RxStart();
                 break;
        
            case Dcm_EnRx_DisTx:
                 Com_TxStart();
                 break;
        
            default:
                 break;
        }
        Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
        #endif
        
        /*Re-enable dtc updating.*/
        (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS,DEM_DTC_KIND_ALL_DTCS);
        /* add your code here*/
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_Programming 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{	//10 02 Response 50 02

#if (IS_FW_CONTAIN_BOOTLOADER == FALSE)

    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_1].DcmDspSessionP2StarServerMax/10; //resolution 10ms
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }

#else
    //If firmware contain bootloader driver, than 50 02 will response in bootloader mode
	DslInternal_RCRResponsePending(FORCERCR_RP);
	Clr_DiagState(DIAG_UDS_PROCESSING);

#endif
}


/******************************************************************************
* Name         :App_ProgrammingPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result)
{
#if (IS_FW_CONTAIN_BOOTLOADER == FALSE)

    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_PROGRAMMING);  
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;  
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);  
        for(i = 0U; i < KIND_OF_SECURITY_LEVEL; i++)
        {
            gSecurityAcessSequence[i] = 0U;
        }
        gSecLevelType = DCM_SEC_LEV_LOCK;
        
        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }

#else

    put_event((const char*)"boot_cb", (event_proc_p)Boot_ReprogramCallBack, NULL);

#endif
}

/******************************************************************************
* Name         :App_Extended_Diagnostic 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{	// 10 03 Response => 50 03
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit() == 0U)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER == STD_ON)
        pMsgContext->resData[DCM_INDEX_2] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax >> 8U);
        pMsgContext->resData[DCM_INDEX_3] = (uint8)(gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2ServerMax); 
        tempP2Star = gDcmDspSessionRow[DCM_INDEX_2].DcmDspSessionP2StarServerMax/10; //resolution 10ms
        pMsgContext->resData[DCM_INDEX_4] = (uint8)(tempP2Star >> 8U);
        pMsgContext->resData[DCM_INDEX_5] = (uint8)(tempP2Star);
        pMsgContext->resDataLen = 6U;
        #else
        pMsgContext->resDataLen = 2U;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}


/******************************************************************************
* Name         :App_Extended_DiagnosticPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted. 
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result)
{
    uint8 i;
    
    if(Result == E_OK)
    {
        /* Reset MCU and go to bootloader at here. */
        /* Below codes are demo, can be removed */
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);  
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);

        /* reset routine Control */
        #if(DCM_SERVICE_31_ENABLED == STD_ON)
        gRountineControlDidHandle = 0xFFu;    /* Reset */ 
        for(i = 0U; i < NUMBER_OF_RID; i++) 
        {
            gRountineControlSequence[i] = 0U;
        }
        #endif
        
        /* add your code here*/
    }
    else
    {
    }
}
#endif

/* 0x11 */
#if(DCM_SERVICE_11_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_SoftReset_Reset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :SoftReset_Reset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_SoftReset_Reset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen = 2U;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_SoftReset_ResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_SoftReset_ResetPost(Std_ReturnType Result)
{
    if(Result == E_OK)
    {
        put_event((const char*)"app_softreset_handler", (event_proc_p)App_SoftReset_ResetPost_Handler, NULL);
    }
    else
    {
    }
}

STATIC FUNC(void,DCM_CODE) App_SoftReset_ResetPost_Handler(void)
{
    uint8 *data = cubtek_faw_did_g_security_acess_attemp_number_get();
//    save_gSecurityAcessAttempNumber_to_eeprom();
    /*save the attempt number*/
    data[0] = gSecurityAcessAttempNumber[0]; /*Need to save securityAcessAttempNumber to eeprom*/;
    cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);         
//    Dem_Shutdown();	//Record DTC after call Dem_Shutdown()
    cubtek_faw_did_ds_can_status_set(CAN_EnRx_EnTx);
    Delay_ms(50);//TODO Make sure write flash done

    /* Reset MCU at here. */
    reset_system();
}

#endif

/* 0x14 */
#if(DCM_SERVICE_14_ENABLED == STD_ON)
/************************************************************************
* Name         :App_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 error = 0U;
    uint32 Dtc;
    uint32 i;

    Dtc = Make32Bit(pMsgContext->reqData[DCM_INDEX_1], pMsgContext->reqData[DCM_INDEX_2], pMsgContext->reqData[DCM_INDEX_3]);
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if(Dtc == SupportedDTC[i])
        {
            i = NUM_OF_DTC;                                
        }
        else
        {
            if(i == (NUM_OF_DTC - 1U))
            {
                if((Dtc != 0xffffff) && (Dtc != SupportedDTCGroup))
                {
                    error = 1U;
                    DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
                }
                else
                {
                }
            }
            else
            {
            }
        }
    }
    if(error == 0U)
    {
        for(i = 0U; i < NUM_OF_DTC; i++)
        {
           DTCStatus[i] = 0U;        
        }
        pMsgContext->resDataLen = 1U; 
        DsdInternal_ProcessingDone(pMsgContext);

        /* Add your code here to clear DTC information */
    }
    else
    {
    }
}
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED == STD_ON)

/******************************************************************************
* Name         :App_Read0x0100
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0100(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = cubtek_faw_did_config_info_get();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0100].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
	pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0100].DcmDspDataSize + 2U);
	pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0100].DcmDspDataSize + 2U);
	DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF180
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF180(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = get_F180_BootloaderVersionNumber();

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF180].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF182
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF182(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    char* DataInformationFieldVersion = {"F182"};
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF182].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = DataInformationFieldVersion[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF182].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF182].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF187
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{ 
    uint16 i;
    char* PartNumber = {"F187"};
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = PartNumber[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF18C
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{ 
    uint16 i;
    char* calib_sw_info = {"F18C"};
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
    	pMsgContext->resData[2U + i] = calib_sw_info[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF18C].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF190
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{ 
    uint16 i;
    uint8 *data = cubtek_faw_did_vin_get();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF192
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF192(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
   	uint16 i;
    char hw_number[16] = {"\0"};

	upd_hw_number_get((char *)&hw_number[0]);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF192].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = hw_number[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF192].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF192].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF193
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF193(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
   	uint16 i;
    char hw_version[16] = {"\0"};

	upd_hw_version_get((char *)&hw_version[0]);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = hw_version[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF193].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF194
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF194(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    char sw_number[16] = {"\0"};

	upd_sw_number_get((char *)&sw_number[0]);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF194].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
    	pMsgContext->resData[2U + i] = sw_number[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF194].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF194].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF195
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  : 
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF195(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{ 
    uint16 i;
    char sw_vesrion[16] = {"\0"};

	upd_sw_version_get((char *)&sw_vesrion[0]);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = sw_vesrion[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = get_F198_TesterSeriesNumber();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF198].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF198].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF198].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}
/******************************************************************************
* Name         :App_Read0xF199
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF199(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = get_F199_ProgrammingDate();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF199].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF199].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF199].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}


/******************************************************************************
* Name         :App_Read0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = cubtek_faw_did_ecu_installation_date_get();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF19D].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF19D].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF19D].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF1A0
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A0(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = cubtek_faw_did_reserved_1_get();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF1A0].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1A0].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1A0].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0xF1A1
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF1A1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 *data = cubtek_faw_did_reserved_2_get();
	
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0xF1A1].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0xF1A1].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0xF1A1].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}


/******************************************************************************
* Name         :App_Read0x0300
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0300(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    sint16 value;
    uint8 radar_mount_pos[4]; 			//0300

    value = (sint16)(tracking_lateral_shift_get() * 100);
    memcpy(&radar_mount_pos[0], &value, sizeof(sint16));
    value = (sint16)(tracking_radar_hight_get() * 100);
    memcpy(&radar_mount_pos[2], &value, sizeof(sint16));    
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0300].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_mount_pos[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0300].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0300].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0301
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0301(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i = 0;
    uint8 radar_alignment_target_position[4];
	//uint8 *data = cubtek_faw_did_aligment_h_angle_offset_get();
    sint16 angle_offset=(sint16)(get_calib_iron_target_offset_angle()*100);
    sint16 target_distance=(sint16)(get_calib_iron_target_distance()*100);

    memcpy(&radar_alignment_target_position[0], &angle_offset, sizeof(sint16));
    memcpy(&radar_alignment_target_position[2], &target_distance, sizeof(sint16));

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0301].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
    	pMsgContext->resData[2U + i] = radar_alignment_target_position[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0301].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0301].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0302
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0302(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_align_finish_flag;

    radar_align_finish_flag = get_calib_iron_alignment_completion_flag();

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0302].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_align_finish_flag;
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0302].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0302].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0303
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0303(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_align_result[3]; 		//0303

    float h_angle = get_calib_iron_h_alignment_angle();
    float v_angle = get_calib_iron_v_alignment_angle();

    radar_align_result[0] = (uint8)(alignment_angle_convert(h_angle, +1.0, 10.0)); //Calibration Angle shift, Iron calibration, no sign issue (Upside positive, Clockwise positive)
    radar_align_result[1] = (uint8)(alignment_angle_convert(v_angle, +1.0, 10.0)); //Calibration VAngle shift, Iron calibration, no sign issue (Upside positive, Clockwise positive)
    radar_align_result[2] = get_calib_iron_radar_alignment_result();

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0303].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_align_result[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0303].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0303].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0304
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0304(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
   	uint16 i;
    uint8 radar_auto_align_result[2];      //0304

    float h_angle = frame_get_aoa_shift(0);

    radar_auto_align_result[0] = (uint8)(alignment_angle_convert(h_angle, +1.0, 10.0));   //Calibration Angle shift
    radar_auto_align_result[1] = 0;                         //Reserved

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0304].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_auto_align_result[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0304].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0304].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0305
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0305(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint16 value;
    uint8 radar_supply_vol[2];         //0305

    value = (uint16)(get_monitoring_value_by_id(MONITOR_ID_VOLTAGE_POWER_SUPPLY) * 10.0);
    radar_supply_vol[0] = (uint8)((value & 0xFF00) >> 8);
    radar_supply_vol[1] = (uint8)((value & 0x00FF));

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0305].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_supply_vol[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0305].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0305].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0306
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0306(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_temperature;        //0306

    radar_temperature = (uint8)((sint8)get_monitoring_value_by_id(MONITOR_ID_TEMPERATURE_MCU));
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0306].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_temperature;
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0306].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0306].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0307
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0307(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    RadarFailsafeState_t failState = {.Raw = 0};

    Update_RadarFailsafeState(&failState);

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0307].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = failState.Byte[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0307].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0307].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0308
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0308(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    RadarMalfunctionErrorReason_t errorReason = {.Raw = 0};
    uint8 tempValue = 0;

    Dem_GetEventStatus(DTC_0x950049_INDEX, &tempValue);
    errorReason.MCU_Master_Clock_Error = tempValue;

    Dem_GetEventStatus(DTC_0x950045_INDEX, &tempValue);
    errorReason.MCU_Error = tempValue;

    Dem_GetEventStatus(DTC_0x950044_INDEX, &tempValue);
    errorReason.MCU_Memory_Error = tempValue;

    Dem_GetEventStatus(DTC_0x950096_INDEX, &tempValue);
    errorReason.G_Sensor_fault = tempValue;

    Dem_GetEventStatus(DTC_0x950196_INDEX, &tempValue);
    errorReason.RF_Sensor_fault = tempValue;

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0308].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = errorReason.Byte[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0308].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0308].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x0309
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x0309(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
	uint8 data[23] = {0};

	data[0] = (uint8)((product_info_get()->manufacture_date & 0xFF000000) >> 24);
	data[1] = (uint8)((product_info_get()->manufacture_date & 0x00FF0000) >> 16);
	data[2] = (uint8)((product_info_get()->manufacture_date & 0x0000FF00) >> 8);
	data[3] = (uint8)((product_info_get()->manufacture_date & 0x000000FF));
	product_serial_no_get((uint8*)&data[4]);
    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x0309].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = data[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x0309].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x0309].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x030A
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x030A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_align_finish_flag = UNDEFINED;

    bool is_hori_completed = ( ALIGN_COMPLETED == get_hori_alignment_completed() );
    bool is_vert_completed = ( ALIGN_COMPLETED == get_vert_alignment_completed() );

    if(true == is_hori_completed && true == is_vert_completed)
    {
        radar_align_finish_flag = COMPLETED;
    }
    else
    {
        radar_align_finish_flag = NOT_COMPLETED;
    }

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x030A].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_align_finish_flag;
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x030A].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x030A].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x030B
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x030B(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_auto_align_result[3];      //030B
    RID_0201_result_t calibrationResult = {.result = 0};

    uint8_t h_angle = (*(cubtek_faw_did_aligment_auto_align_h_angle_get()));
    uint8_t v_angle = (*(cubtek_faw_did_aligment_auto_align_v_angle_get()));
    uint8 h_result = get_hori_alignment_result();
    uint8 v_result = get_vert_alignment_result();

    calibrationResult.horizontal = h_result;
    calibrationResult.vertical = vertical_alignment_result_mapping(v_result);

    radar_auto_align_result[0] = (uint8)(alignment_angle_convert(h_angle, -1.0, 1.0));	//Calibration Angle shift, (-1) for display same coord as iron calib
    radar_auto_align_result[1] = (uint8)(alignment_angle_convert(v_angle, 1.0, 1.0));	//Calibration VAngle shift
    radar_auto_align_result[2] = (uint8)calibrationResult.result;               //Calibration Result


    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x030B].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_auto_align_result[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x030B].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x030B].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

/******************************************************************************
* Name         :App_Read0x030C
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x030C(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_vertical_align_finish_flag;

    radar_vertical_align_finish_flag = static_vertical_alignment_completion_flag();

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x030C].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_vertical_align_finish_flag;
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x030C].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x030C].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

FUNC(uint8,DCM_CODE) static_vertical_alignment_completion_flag()
{
    uint8 result = svtf_eeprom_complete_state_get();

    if(kVtfbNotCompleted == result)
    {
        return NOT_COMPLETED;
    }
    else if(kVtfbCompleted == result)
    {
        return COMPLETED;
    }
    else
    {
        return UNDEFINED;
    }
}

/******************************************************************************
* Name         :App_Read0x030D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x030D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_auto_align_result[2];      //030D
    float v_aoa = svtf_eeprom_pitch_angle_get();
    uint8 result = svtf_eeprom_state_get();

    radar_auto_align_result[0] = (uint8)alignment_angle_convert(v_aoa, +1.0, 10.0);               //static vertical alignment angle, UDS upside-positive, no upside down issue
    radar_auto_align_result[1] = (uint8)static_vertical_alignment_result_mapping(result);   //static vertical alignment result

    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x030D].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_auto_align_result[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x030D].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x030D].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

FUNC(uint8,DCM_CODE) horizontal_alignment_result_mapping(uint8 result)
{
    switch(result)
    {
        case ALIGN_STATUS_READY:
        case ALIGN_STATUS_START:
        case ALIGN_STATUS_PROCESS:
            return AUTO_ALIGNMENT_H_RESULT_PROCESSING;          //8
        case ALIGN_STATUS_DONE_SAVE:
        case ALIGN_STATUS_DONE_NOT_SAVE:
            return AUTO_ALIGNMENT_H_RESULT_CORRECT;             //0
        case ALIGN_STATUS_ERROR:
            //AoA error
            return AUTO_ALIGNMENT_H_RESULT_ANGLE_OUT_OF_RANGE;  //3
        case ALIGN_STATUS_YAW_ERR:
            return AUTO_ALIGNMENT_H_RESULT_YAWRATE_ERROR;       //5
        case ALIGN_STATUS_TIMEOUT:
            return AUTO_ALIGNMENT_H_RESULT_TIMEOUT;             //6
        default:
            return AUTO_ALIGNMENT_H_RESULT_PROCESSING;          //8
    }
}

FUNC(uint8,DCM_CODE) vertical_alignment_result_mapping(uint8 result)
{
    switch(result)
    {
        case ALIGN_STATUS_READY:
        case ALIGN_STATUS_START:
        case ALIGN_STATUS_PROCESS:
            return AUTO_ALIGNMENT_V_RESULT_PROCESSING;          //8
        case ALIGN_STATUS_DONE_SAVE:
        case ALIGN_STATUS_DONE_NOT_SAVE:
            return AUTO_ALIGNMENT_V_RESULT_CORRECT;             //0
        case ALIGN_STATUS_ERROR:
            //AoA error
            return AUTO_ALIGNMENT_V_RESULT_ANGLE_OUT_OF_RANGE;  //3
        case ALIGN_STATUS_YAW_ERR:
        	return AUTO_ALIGNMENT_V_RESULT_SIGNAL_ERROR;        //4
        case ALIGN_STATUS_ACCZ_ERR:
        	return AUTO_ALIGNMENT_V_RESULT_ACC_ERROR;        	//5
        case ALIGN_STATUS_TIMEOUT:
            return AUTO_ALIGNMENT_V_RESULT_TIMEOUT;             //6
        default:
            return AUTO_ALIGNMENT_V_RESULT_PROCESSING;          //8
    }

}

FUNC(uint8,DCM_CODE) static_vertical_alignment_result_mapping(uint8 result)
{
    if(kVtfbCorrect == result)
    {
        return VERTICAL_CALIBRATION_RESULT_CORRECT;             //0
    }
    else if(kVtfbAngOutOfBounds == result)
    {
        return VERTICAL_CALIBRATION_RESULT_AOA_OUT_OF_RANGE;    //3
    }
    else if(kVtfbVehIoError == result)
    {
        return VERTICAL_CALIBRATION_RESULT_ACC_ERROR;           //5
    }
    else if(kVtfbTimeout == result)
    {
        return VERTICAL_CALIBRATION_RESULT_TIMEOUT;             //6
    }
    else
    {
        return VERTICAL_CALIBRATION_RESULT_PROCESSING;          //8
    }
}

FUNC(uint8,DCM_CODE) alignment_angle_convert(float angle, float sign, float scale)
{
    uint8 result;
    angle = (angle >= 0 ? angle + ROUNDING_NEAREST_TENTH : angle - ROUNDING_NEAREST_TENTH) * scale;  //Round it to the nearest whole number

    angle = sign >= 0 ? angle : -angle;

    result = (uint8)((sint8)angle);

    return result;
}

/******************************************************************************
* Name         :App_Read0x030E
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x030E(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 radar_mount_position_offset_result[2];      //030E
    uint8_t h_angle = (*(cubtek_faw_did_aligment_auto_detect_h_angle_get()));
    uint8_t v_angle = (*(cubtek_faw_did_aligment_auto_detect_v_angle_get()));
    radar_mount_position_offset_result[0] = (uint8)(alignment_angle_convert(h_angle, -1.0, 1.0));;   //Horizontal offset angle
    radar_mount_position_offset_result[1] = (uint8)(alignment_angle_convert(v_angle, 1.0, 1.0));;   //Vertical offset angle


    for(i = 0U; i < gDcmDsdSubService_22[ReadHandle_0x030E].DcmDspDataSize; i++)
    {
        /* Add your codes here to get data. Below codes can be removed */
        pMsgContext->resData[2U + i] = radar_mount_position_offset_result[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID == STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData += (gDcmDsdSubService_22[ReadHandle_0x030E].DcmDspDataSize + 2U);
    pMsgContext->resDataLen += (gDcmDsdSubService_22[ReadHandle_0x030E].DcmDspDataSize + 2U);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif
}

#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#if(DCM_SERVICE_2C_ENABLED == STD_ON)
#endif
#endif
#endif

/* 0x2A */
#if(DCM_SERVICE_2A_ENABLED == STD_ON)
#endif

/* 0x23 */

/* 0x24 */
#if(DCM_SERVICE_24_ENABLED == STD_ON)
#endif

/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Write0x0100
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x0100(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	    
    put_event((const char*)"app_write0100", (event_proc_p)App_Write0x0100_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0x0100_Fun(void)
{
    uint16 i;
	uint8 len = 0;
	uint8 *data = cubtek_faw_did_config_info_get();
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x0100].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
		len++;
	}
	if(len == 16)
	{
        cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	}
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}

/******************************************************************************
* Name         :App_Write0xF190
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext 
* Return code  :N/A  
* Description  :
*      
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	    
    put_event((const char*)"app_writeF190", (event_proc_p)App_Write0xF190_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF190_Fun(void)
{
    uint16 i;
	uint8 len = 0;
	uint8 *data = cubtek_faw_did_vin_get();
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF190].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
		len++;
    }
	if(len == 17)
	{
        cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	}
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}
/******************************************************************************
* Name         :App_Write0xF198
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF198(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_writeF198", (event_proc_p)App_Write0xF198_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF198_Fun(void)
{
    uint16 i;
	char temp[ADPT_F198_SIZE+1] = {'\0'};
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF198].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        temp[i] = gMsgContextBackup.resData[2U + i];
	}

    gMsgContextType.resDataLen = 3U;

    if(E_OK == set_F198_TesterSeriesNumber(temp))
	{
        DsdInternal_ProcessingDone(&gMsgContextType);
	}
	else
	{
		DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
	}
}
/******************************************************************************
* Name         :App_Write0xF199
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF199(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_writeF199", (event_proc_p)App_Write0xF199_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF199_Fun(void)
{
    uint16 i;
	uint8 temp[ADPT_F199_SIZE+1] = {'\0'};
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF199].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        temp[i] = gMsgContextBackup.resData[2U + i];
    }

    gMsgContextType.resDataLen = 3U;

	if(E_OK == set_F199_ProgrammingDate(temp, gDcmDsdSubService_2E[WriteHandle_0xF199].DcmDspDataSize))
	{
        DsdInternal_ProcessingDone(&gMsgContextType);
	}
	else
	{
		DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
	}
}
/******************************************************************************
* Name         :App_Write0xF19D
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF19D(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_writeF19D", (event_proc_p)App_Write0xF19D_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF19D_Fun(void)
{
    uint16 i;
	uint8 len = 0;
	uint8 *data = cubtek_faw_did_ecu_installation_date_get();
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF19D].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
		len++;
    }
	if(len == 4)
	{
        cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	}
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}
/******************************************************************************
* Name         :App_Write0xF1A0
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1A0(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_writeF1A0", (event_proc_p)App_Write0xF1A0_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF1A0_Fun(void)
{
    uint16 i;
	uint8 len = 0;
	uint8 *data = cubtek_faw_did_reserved_1_get();
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF1A0].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
		len++;
    }
	if(len == 16)
	{
        cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	}
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}
/******************************************************************************
* Name         :App_Write0xF1A1
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF1A1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_writeF1A1", (event_proc_p)App_Write0xF1A1_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0xF1A1_Fun(void)
{
    uint16 i;
	uint8 len = 0;
	uint8 *data = cubtek_faw_did_reserved_2_get();
	
    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0xF1A1].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
		len++;
    }
	if(len == 16)
	{
        cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	}
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}
/******************************************************************************
* Name         :App_Write0x0300
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x0300(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{    
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));   
    DslInternal_RCRResponsePending(FORCERCR_RP);   
    Clr_DiagState(DIAG_UDS_PROCESSING); 
    put_event((const char*)"app_write0300", (event_proc_p)App_Write0x0300_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0x0300_Fun(void)
{
    uint16 i;
    sint16 value;
	uint8 radar_mount_pos[4]; 			//0300
	uint8 *data = cubtek_faw_did_is_300_301_written_get();

    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x0300].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        radar_mount_pos[i] = gMsgContextBackup.resData[2U + i];
    }
    memcpy(&value, &radar_mount_pos[0], sizeof(sint16));
    tracking_lateral_shift_set((float)value * 0.01);
    memcpy(&value, &radar_mount_pos[2], sizeof(sint16));
    tracking_radar_hight_set((float)value * 0.01);

    *data |= 0x10;

    cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);

    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);       
}
/******************************************************************************
* Name         :App_Write0x0301
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x0301(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{    	
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));   
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	       
    put_event((const char*)"app_write0301", (event_proc_p)App_Write0x0301_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0x0301_Fun(void)
{
    uint16 i = 0;
    uint8 radar_alignment_target_position[4];
	sint16 angle_offset;
    sint16 target_distance;
	uint8 *data = cubtek_faw_did_is_300_301_written_get();

    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x0301].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        radar_alignment_target_position[i] = gMsgContextBackup.resData[2U + i];
    }

    memcpy(&angle_offset, &radar_alignment_target_position[0], 2);
    memcpy(&target_distance, &radar_alignment_target_position[2], 2);

    //cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);
	set_calib_iron_target_offset_angle((float)angle_offset * 0.01);
	set_calib_iron_target_distance((float)target_distance * 0.01);

	*data |= 0x01;
    cubtek_faw_did_pars_save(DIDPARS_SAVE_DIRECT);

    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);             
}
#if 0
/******************************************************************************
* Name         :App_Write0x0309
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0x0309(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    memcpy(&gMsgContextBackup, pMsgContext, sizeof(Dcm_MsgContextType));
    DslInternal_RCRResponsePending(FORCERCR_RP);
    Clr_DiagState(DIAG_UDS_PROCESSING);	
    put_event((const char*)"app_write0309", (event_proc_p)App_Write0x0309_Fun, NULL);
}

STATIC FUNC(void,DCM_CODE) App_Write0x0309_Fun(void)
{
    uint16 i;
	uint32 date = 0;
	uint8 data[23] = {0};

    for(i = 0U; i < gDcmDsdSubService_2E[WriteHandle_0x0309].DcmDspDataSize; i++)
    {
        /* Add your codes here to write data. Below codes can be removed */
        data[i] = gMsgContextBackup.resData[2U + i];
    }
	date = ((uint32)data[0] << 24) + ((uint32)data[1] << 16) + ((uint32)data[2] << 8) + (uint32)data[3];
	product_manufacture_date_set(date);
	product_serial_no_set((uint8*)&data[4]);
    gMsgContextType.resDataLen = 3U;
    DsdInternal_ProcessingDone(&gMsgContextType);
}
#endif
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED == STD_ON)
#endif

/* 0x19 */
#if(DCM_SERVICE_19_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Report number of DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_Number(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];

    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            counter++;
        }
        else
        {  
        }
    }

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    /* Change below data if necessary */
    /* 0x00 ISO15031-6Format,0x01 ISO14229-1Format,0x02 J1939 Format */
    pMsgContext->resData[DCM_INDEX_3] = 0x00U;
    pMsgContext->resData[DCM_INDEX_4] = (uint8)(counter >> 8U);
    pMsgContext->resData[DCM_INDEX_5] = (uint8)(counter);
    /* Always equals 6, don't change it */
    pMsgContext->resDataLen = 6U;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_Fault_Memory_Read_identified_errors
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_identified_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8  i;
    uint16 counter = 0U;
    uint8  DtcStatus_Temp;
    DtcStatus_Temp = pMsgContext->reqData[DCM_INDEX_2];
   
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        if((DtcStatus_Temp & DTCStatus[i]) != 0U)
        {
            pMsgContext->resData[DCM_INDEX_3 + counter * 4U] = (uint8)(SupportedDTC[i] >> 16U);
            pMsgContext->resData[DCM_INDEX_4 + counter * 4U] = (uint8)(SupportedDTC[i] >> 8U);
            pMsgContext->resData[DCM_INDEX_5 + counter * 4U] = (uint8)SupportedDTC[i];
            pMsgContext->resData[DCM_INDEX_6 + counter * 4U] = DTCStatus[i]; 
            counter++;
        }
        else
        {
        }
    }

    pMsgContext->resData[DCM_INDEX_1] = pMsgContext->reqData[DCM_INDEX_1];
    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    pMsgContext->resDataLen = DCM_INDEX_3 + (counter * 4U);
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Fault_Memory_Read_supported_errors(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;

    pMsgContext->resData[DCM_INDEX_2] = DTCStatusAvailabilityMask;
    for(i = 0U; i < NUM_OF_DTC; i++)
    {
        pMsgContext->resData[DCM_INDEX_3 + i * 4U] = (uint8)(SupportedDTC[i] >> 16U);
        pMsgContext->resData[DCM_INDEX_4 + i * 4U] = (uint8)(SupportedDTC[i] >> 8U);
        pMsgContext->resData[DCM_INDEX_5 + i * 4U] = (uint8)(SupportedDTC[i]);
        pMsgContext->resData[DCM_INDEX_6 + i * 4U] = DTCStatus[i]; 
    }
    pMsgContext->resDataLen = 3U + NUM_OF_DTC * 4U;
    DsdInternal_ProcessingDone(pMsgContext);
}

#endif

/* 0x27 */
#if(DCM_SERVICE_27_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_Request_Seed_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16 i;
    uint8 seed;

    for(i = 0U; i < 4; i++)
    {
        /* add your code here, generate App Seed */
		srand(STM_0.CNT.R);
		seed = rand();
        gMsgContextType.resData[2U + i] = seed ;
    }

    _seed = gMsgContextType.resData[2] << 24 | gMsgContextType.resData[3] << 16 | gMsgContextType.resData[4] << 8 | gMsgContextType.resData[5];
    pMsgContext->resDataLen = 6U;/*seed size + 2*/ 
    DsdInternal_ProcessingDone(pMsgContext); 
}

/******************************************************************************
* Name         :App_Send_Key_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 key = 0U;
    
    key = *((uint32*)&pMsgContext->reqData[2]);

    if(key == seedToKey_L1(_seed))
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen = 2U;
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
    }
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC uint32 seedToKey_L1(uint32 seed)
{
	uint32 key=0;
    /*FAW mask*/
    const uint32 FawMask = 0xBF868693;

    /*Neusoft mask*/
    const uint32 NeusoftMask = 0x9B8DB46C;

    /*TSINTEL mask*/
    const uint32 TsintelMask = 0x45B4B5B9;

    uint32 UDS_CanID = 0;
    UDS_CanID = get_uds_physical_request();

    if(0x7A0 == UDS_CanID)
    {
        key = seedToKey_L1_Hirain(seed, FawMask);
    }
    else if(0x7B0 == UDS_CanID)
    {
        key = seedToKey_L1_Neusoft(seed, NeusoftMask);
    }
    else if(0x7C1 == UDS_CanID)
    {
        key = seedToKey_L1_Cubtek(seed, TsintelMask);
    }


	return key;
}

STATIC uint32 seedToKey_L1_Hirain(uint32 seed, uint32 mask)
{
    uint32 key=0;
    uint8 i;
    if(seed !=0)
    {

        for (i=0; i<35; i++)
        {
            if (seed & 0x80000000)
            {
                seed = seed << 1;
                seed = seed ^ mask;
            }
            else
            {
                seed = seed << 1;
            }
        }
        key=seed;
    }

    return key;
}

STATIC uint32 seedToKey_L1_Neusoft(uint32 seed, uint32 mask)
{
    uint32 key=0;
    uint8 i;

    if(seed != 0)
    {
        for (i=0; i<32; i++)
        {
            if (seed & 0x40000000)
            {
                seed = seed << 1;
                seed = ~seed;
                seed = seed ^ mask;
            }
            else
            {
                seed = seed << 1;
            }
        }
        key=seed;
    }

    return key;
}

STATIC uint32 seedToKey_L1_Cubtek(uint32 seed, uint32 mask)
{
    uint32 key=0;
    uint8 i;

    if(seed != 0)
    {
        for (i=0; i<36; i++)
        {
            if (seed & 0x08000000)
            {
                seed = seed << 1;
                seed = ~seed;
                seed = seed ^ mask;
            }
            else
            {
                seed = seed << 1;
            }
        }
        key=seed;
    }

    return key;
}

#endif

/* 0x28 */
#if(DCM_SERVICE_28_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_EnableRxAndEnableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_EnableRxAndEnableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
	//Nm, App Enable
    Com_RxStart();
    Com_TxStart();
    cubtek_faw_did_ds_can_status_set(CAN_EnRx_EnTx);
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DisableRxAndDisableTx_Control
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DisableRxAndDisableTx_Control(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    //Disable all can tx and rx except Diagnostic
	//Nm, App Disable
    Com_RxStop();
    Com_TxStop();
    Dcm_ComMessage_Status = Dcm_DisRx_DisTx;
    cubtek_faw_did_ds_can_status_set(CAN_DisRx_DisTx);
    pMsgContext->resDataLen = 2U;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x31 */
#if(DCM_SERVICE_31_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_StartRoutine0x0200
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0200(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	RadarFailsafeState_t failState = {.Raw = 0};
	uint8 is_did_0x300_written = (*(cubtek_faw_did_is_300_301_written_get())) >> 4;
	uint8 is_did_0x301_written = (*(cubtek_faw_did_is_300_301_written_get())) & 0x0F;
	uint8 isNRC = 0;

    DsdInternal_RoutineStarted();

    Update_RadarFailsafeState(&failState);
    /* Add your code here */
    if(VEH_STATUS_VALID == get_eps_speed_status() && 0 != get_eps_speed_value())
    {
    	pMsgContext->resData[4] = CALIBRATION_CONDITION_INCORRECT_VEHILCE_SPEED_GREATER_THAN_ZERO;
    }
    else if(CALIB_STATUS_BUSY == get_calib_iron_sta())
    {
    	pMsgContext->resData[4] = CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE;
    }
    else if(0 != (failState.Raw & DTCS_EXCEPT))
    {
    	//Have DTC occur except missing calibration, yaw rate invalid, steering angle invalid
    	pMsgContext->resData[4] = CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST;
    }
    else if(FALSE == is_did_0x300_written)
    {
    	pMsgContext->resData[4] = CALIBRATION_CONDITION_INCORRECT_DID0300_NOT_WRITTEN;
    }
    else if(FALSE == is_did_0x301_written)
    {
    	pMsgContext->resData[4] = CALIBRATION_CONDITION_INCORRECT_DID0301_NOT_WRITTEN;
    }
    else
    {
        /* Routine diagnostic start*/

    	if(CALIB_IRON_PARS_CORRECT == get_calib_iron_pars_status())
    	{
    		isNRC = 0;
			frame_pause(NULL, 0);

			put_event((const char*)"rid200-start", (event_proc_p)start_rountine_0x0200, NULL);
			pMsgContext->resData[4] = 0x00;//Routine diagnostic pass = 0x00
    	}
    	else
    	{
    		isNRC = 1;
    	}
    }


    if(0 == isNRC)
    {
		pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0200].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
		DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
    	DsdInternal_SetNegResponse(&gMsgContextType, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }

}

STATIC FUNC(void,DCM_CODE) start_rountine_0x0200(void)
{
	if(FRAME_ST_READY != get_frame_state())
	{
		put_event((const char*)"rid200-start", (event_proc_p)start_rountine_0x0200, NULL);
	}
	else
	{
		start_iron_calibration((iron_calib_done_p)iron_calib_done_handler);
	}
}
/******************************************************************************
* Name         :App_StopRoutine0x0200
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0200(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

	put_event((const char*)"rid200-stop", (event_proc_p)stop_rountine_0x0200, NULL);

	pMsgContext->resData[4] = 0x00;//Stop routine success = 0x00
	pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0200].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
	DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) stop_rountine_0x0200(void)
{
	if(FRAME_ST_READY != get_frame_state())
	{
		put_event((const char*)"rid200-stop", (event_proc_p)stop_rountine_0x0200, NULL);
	}
	else
	{
		stop_iron_calibration();
		frame_play(-1 ,-1 ,-1 , NULL, NULL);
	}
}

/******************************************************************************
* Name         :App_ResultRoutine0x0200
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_ResultRoutine0x0200(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	if(CALIB_STATUS_DONE != get_calib_iron_sta())
	{
		gMsgContextType.resData[4] = CALIBRATION_RESULT_EQUIPMENT_PROCESSING; //Calibration Result -Error Code
	}
	else
	{
		float h_angle = get_calib_iron_h_alignment_angle();
		float v_angle = get_calib_iron_v_alignment_angle();

		gMsgContextType.resData[4] = (uint8)get_calib_iron_radar_alignment_result();    //Calibration Result -Error Code
		gMsgContextType.resData[5] = (uint8)(alignment_angle_convert(h_angle, +1.0, 10.0));   //Calibration Angle shift, Iron calibration, no sign issue (Upside positive, Clockwise positive)
		gMsgContextType.resData[6] = (uint8)(alignment_angle_convert(v_angle, +1.0, 10.0));   //Calibration VAngle shift, Iron calibration, no sign issue (Upside positive, Clockwise positive)
	}

	pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0200].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
	DsdInternal_ProcessingDone(pMsgContext);
}

static inline const char *string_of_result(calib_equipment_e result)
{
    static const char *result_code_list[] = {
        "correct",
        "not found",
        "range err",
        "aoa err",
        "signal mag err",
        "hw err",
        "timeout",
        "vaoa err",
        "processing",
        "invalid"
    };

    return result_code_list[result];
}

void iron_calib_done_handler(calib_equipment_e iron_calib_status, iron_calib_result_p iron_calib_result)
{
    switch(iron_calib_status)
    {
        case CALIB_EQUIPMENT_CORRECT:
            if(CALIB_IRON_COMPLETED != get_calib_iron_alignment_completion_flag())
            {
                set_calib_iron_alignment_completion_flag(CALIB_IRON_COMPLETED);
            }
            break;

        case CALIB_EQUIPMENT_RADAR_HW_ERR:
            if(CALIB_IRON_NOT_COMPLETED != get_calib_iron_alignment_completion_flag())
            {
                set_calib_iron_alignment_completion_flag(CALIB_IRON_NOT_COMPLETED);
            }
            break;

        default:
            //Do NOT change the completion flag
            break;
    }

    PRINTF("[iron calib result]: %s\n", string_of_result(iron_calib_status));
    PRINTF("[iron calib result]: angle: %.2f, vangle: %.2f, mag: %.2f\n", iron_calib_result->iron_angle, iron_calib_result->iron_vangle, iron_calib_result->iron_mag);

    check_radar_alignment_result();
}

FUNC(void,DCM_CODE) App_HorizontalAlignmentDoneHandler()
{
    //Horizontal alignment done
    if(auto_calibration_timer_p)
    {
        if (!strcmp(AUTO_CALIB_ID, auto_calibration_timer_p->name))
        {
            timer_unset(&auto_calibration_timer_p);
        }
        PRINTF("auto_calib_timer_stop\n");
    }
}

/******************************************************************************
* Name         :App_StartRoutine0x0201
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0201(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    RadarFailsafeState_t failState = {.Raw = 0};
    uint8 h_status = get_hori_alignment_status();
    uint8 v_status = get_vert_alignment_status();

    DsdInternal_RoutineStarted();

    Update_RadarFailsafeState(&failState);
    /* Add your code here */
    if(h_status == ALIGN_STATUS_PROCESS || v_status == ALIGN_STATUS_PROCESS )
    {
        pMsgContext->resData[4] = (uint8)AUTO_CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE;
    }
    else if(0 != (failState.Raw & DTCS_EXCEPT))
    {
        //Have DTC occur except missing calibration, yaw rate invalid, steering angle invalid
        pMsgContext->resData[4] = (uint8)AUTO_CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST;
    }
    else
    {
        /* Routine diagnostic start*/
        start_rountine_0x0201();
        pMsgContext->resData[4] = 0x00;//Routine diagnostic pass = 0x00
    }

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0201].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) start_rountine_0x0201(void)
{
    const uint32 ROUNTINE_START = 1;
    IPC_SEND_MSG_Z70(MSG_AUTO_HORI_ALIGN, (void *)ROUNTINE_START, 0);

    // clear alignment count for progress bar show when uds process start
    clear_hori_finished_num();
    clear_vert_finished_num();

    if(NULL == auto_calibration_timer_p)
    {
        auto_calibration_timer_p = timer_set(AUTO_CALIB_ID, DEFAULT_TICKS_PER_SECOND * 1800, 1, (event_proc_p)App_AutoCalibrationTimeout, NULL);
        if(auto_calibration_timer_p)
        {
            PRINTF("auto_calib_timer start\n");
        }
        else
        {
            PRINTF("[Error]timer full: auto_calib_timer cannot set\n");
        }
    }
}

/******************************************************************************
* Name         :App_StopRoutine0x0201
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0201(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    stop_rountine_0x0201();

    pMsgContext->resData[4] = 0x00;//Stop routine success = 0x00
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0201].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) stop_rountine_0x0201(void)
{
    const uint32 ROUNTINE_STOP = 0;
    IPC_SEND_MSG_Z70(MSG_AUTO_HORI_ALIGN, (void *)ROUNTINE_STOP, 0);

    if(auto_calibration_timer_p)
    {
        PRINTF("auto_calib_timer_stop\n");

        if (!strcmp(AUTO_CALIB_ID, auto_calibration_timer_p->name))
        {
            timer_unset(&auto_calibration_timer_p);
        }
    }
}

/******************************************************************************
* Name         :App_ResultRoutine0x0201
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_ResultRoutine0x0201(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    float h_angle = get_auto_hori_align_mount_angle();
    float v_angle = get_auto_vert_align_mount_angle();
    uint8 h_status = get_hori_alignment_status();
    uint8 v_status = get_vert_alignment_status();
    uint8 h_aoa_result = 0;
    uint8 v_aoa_result = 0;
    RID_0201_result_t calibrationResult = {.result = 0};

    h_status = horizontal_alignment_result_mapping(h_status);
    v_status = vertical_alignment_result_mapping(v_status);


    if((AUTO_ALIGNMENT_H_RESULT_PROCESSING != h_status) && (AUTO_ALIGNMENT_V_RESULT_PROCESSING != v_status))
    {
        calibrationResult.horizontal    = h_status;
        calibrationResult.vertical      = v_status;

        if(PB_ENABLE == is_enable_RID_0201_progress_bar())
        {
            if(AUTO_ALIGNMENT_H_RESULT_CORRECT == h_status || AUTO_ALIGNMENT_H_RESULT_ANGLE_OUT_OF_RANGE == h_status)
            {
                h_aoa_result                    = alignment_angle_convert(h_angle, -1.0, 10.0);   //Calibration Angle shift, UDS upside-positive, upside down with our SPT parameter direction
            }
            else
            {
                h_aoa_result                    = get_auto_alignment_combine_progress_rate();
            }

            if(AUTO_ALIGNMENT_V_RESULT_CORRECT == v_status || AUTO_ALIGNMENT_V_RESULT_ANGLE_OUT_OF_RANGE == v_status)
            {
                v_aoa_result                    = alignment_angle_convert(v_angle, +1.0, 10.0);   //Calibration VAngle shift, clockwise-positive
            }
            else
            {
                v_aoa_result                    = get_auto_alignment_combine_progress_rate();
            }
        }
        else
        {
            h_aoa_result                    = alignment_angle_convert(h_angle, -1.0, 10.0);   //Calibration Angle shift, UDS upside-positive, upside down with our SPT parameter direction
            v_aoa_result                    = alignment_angle_convert(v_angle, +1.0, 10.0);   //Calibration VAngle shift, clockwise-positive
        }
    }
    else
    {
        calibrationResult.horizontal    = AUTO_ALIGNMENT_H_RESULT_PROCESSING;
        calibrationResult.vertical      = AUTO_ALIGNMENT_V_RESULT_PROCESSING;

        if(PB_ENABLE == is_enable_RID_0201_progress_bar())
        {
            h_aoa_result                    = get_auto_alignment_combine_progress_rate();
            v_aoa_result                    = get_auto_alignment_combine_progress_rate();
        }
        else
        {
            h_aoa_result                    = 0;
            v_aoa_result                    = 0;
        }
    }


    gMsgContextType.resData[4] = (uint8)calibrationResult.result;   //Calibration Result
    gMsgContextType.resData[5] = (uint8)h_aoa_result;               //Calibration Angle shift
    gMsgContextType.resData[6] = (uint8)v_aoa_result;               //Calibration VAngle shift

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0201].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(float,DCM_CODE) get_auto_alignment_combine_progress_rate(){
	return (get_auto_hori_alignmnet_progress_rate() + get_auto_vert_alignmnet_progress_rate()) / 2.0;
}

STATIC FUNC(float,DCM_CODE) get_auto_hori_alignmnet_progress_rate(){
    uint16 h_now    = get_hori_finished_num();
    uint16 h_max    = get_hori_alignment_total_num();
    float  h_result = (float)h_now / (float)h_max * 100.0;
    return h_result;
}

STATIC FUNC(float,DCM_CODE) get_auto_vert_alignmnet_progress_rate(){
    uint16 v_now = get_vert_finished_num();
    uint16 v_max = get_vert_alignment_total_num();
    float  v_result = (float)v_now / (float)v_max * 100.0;
    return v_result;
}

void App_AutoCalibrationTimeout()
{
    const uint32 ROUNTINE_TIMEOUT = 2;
    IPC_SEND_MSG_Z70(MSG_AUTO_HORI_ALIGN, (void *)ROUNTINE_TIMEOUT, 0);

    if(auto_calibration_timer_p)
    {
        PRINTF("auto_calib_timer_stop\n");

        if (!strcmp(AUTO_CALIB_ID, auto_calibration_timer_p->name))
        {
            timer_unset(&auto_calibration_timer_p);
        }
    }

    //1800s
    PRINTF("Auto-calib 30mins timeout \n");
    auto_calibration_timer_p = NULL;
}

/******************************************************************************
* Name         :App_StartRoutine0x0203
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    RadarFailsafeState_t failState = {.Raw = 0};
    uint8 state = svtf_buffer_state_get();

    DsdInternal_RoutineStarted();

    Update_RadarFailsafeState(&failState);
    /* Add your code here */
    if(VEH_STATUS_VALID != get_eps_speed_status() || 0 != get_eps_speed_value())
    {
        pMsgContext->resData[4] = VERTICAL_CALIBRATION_CONDITION_VEHILCE_SPEED_GREATER_THAN_ZERO;
    }
    else if(kVtfbProcessing == state)
    {
        pMsgContext->resData[4] = (uint8)VERTICAL_CALIBRATION_CONDITION_INCORRECT_RADAR_IN_CALIBRATION_MODE;
    }
    else if(0 != (failState.Raw & DTCS_EXCEPT))
    {
        //Have DTC occur except missing calibration, yaw rate invalid, steering angle invalid
        pMsgContext->resData[4] = (uint8)VERTICAL_CALIBRATION_CONDITION_INCORRECT_DTCS_EXIST;
    }
    else
    {
        /* Routine diagnostic start*/
        put_event((const char*)"rid203-start", (event_proc_p)start_rountine_0x0203, NULL);
        pMsgContext->resData[4] = 0x00;//Routine diagnostic pass = 0x00
    }

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) start_rountine_0x0203(void)
{
    svtf_process(0);
}

/******************************************************************************
* Name         :App_StopRoutine0x0203
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    put_event((const char*)"rid203-stop", (event_proc_p)stop_rountine_0x0203, NULL);

    pMsgContext->resData[4] = 0x00;//Stop routine success = 0x00
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) stop_rountine_0x0203(void)
{
    svtf_process_stop();
}

/******************************************************************************
* Name         :App_ResultRoutine0x0203
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_ResultRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 result = svtf_buffer_state_get();
    float v_aoa = svtf_buffer_pitch_angle_get();
    uint8 rtvl_result = static_vertical_alignment_result_mapping(result);

    if(VERTICAL_CALIBRATION_RESULT_PROCESSING != rtvl_result)
    {
        put_event((const char*)"app_checkAlignm", (event_proc_p)check_radar_alignment_result, (void*)NULL);
    }

    gMsgContextType.resData[4] = (uint8)rtvl_result;                            //Calibration Result
    gMsgContextType.resData[5] = (uint8)alignment_angle_convert(v_aoa, +1.0, 10.0);   //Calibration Angle shift
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_StartRoutine0x0204
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0204(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    RadarFailsafeState_t failState = {.Raw = 0};

    DsdInternal_RoutineStarted();

    Update_RadarFailsafeState(&failState);
    /* Add your code here */
    if(VEH_STATUS_VALID == get_eps_speed_status() && 0 != get_eps_speed_value())
    {    	
        //Speed >0, disable IMU calibration
        pMsgContext->resData[4] = IMU_RESULT_INCORRECT_VEHILCE_SPEED_GREATER_THAN_ZERO;
        PRINTF("App_StartRoutine0x0204 Speed greather than zero\n");
        //Speed > 0 FAIL, configure STATUS: INIT
        IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
        IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;

    }    
    else if(0 != (failState.Raw & DTCS_EXCEPT))
    {
        //Have DTC occur except missing calibration, yaw rate invalid, steering angle invalid
        pMsgContext->resData[4] = IMU_RESULT_INCORRECT_DTCS_EXIST;
        PRINTF("App_StartRoutine0x0204 DTCS_EXCEPT\n");
        //DTCS FAIL, configure STATUS: INIT
        IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
        IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;        
    }    
    else
    {
        if ((IMU_STATUS_INIT == IMU_SELF_TEST_STATUS) &&	
    	(IMU_STATUS_INIT == IMU_SELF_CALIB_STATUS))
        {
            IMU_SELF_TEST_STATUS = IMU_STATUS_PROCESSING;
            IMU_SELF_CALIB_STATUS = IMU_STATUS_PROCESSING;

            IMU_SELF_TEST_RESULT = IMU_RESULT_INIT;
            IMU_SELF_CALIB_RESULT = IMU_RESULT_INIT;

            PRINTF("App_StartRoutine0x0204 put_event start_rountine_imu_self_test_0x0204\n"); 
            put_event((const char*)"rid204-start-imu-self-test", (event_proc_p)start_rountine_imu_self_test_0x0204, NULL);
            pMsgContext->resData[4] = 0x00;       
    	
        }
        else
        {
        	//PRINTF("App_StartRoutine0x0204 Not put_event start_rountine_imu_self_test_0x0204\n"); 
        	pMsgContext->resData[4] = IMU_RESULT_INCORRECT_RADAR_IN_CALIBRATION_MODE;   
        }
//        PRINTF("App_StartRoutine0x0204 TEST_STATUS:%d, CALIB_STATUS:%d\n", 
//            	IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS); 
        //pMsgContext->resData[4] = IMU_RESULT_INCORRECT_CALIB;    	   	
    }

    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0204].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
    
}

STATIC FUNC(void,DCM_CODE) start_rountine_imu_self_test_0x0204(void)
{
    uint8 test_result;
    	   
    test_result = imu_self_test_by_RMTP(imu_self_test_rid_204_cb);

    if (0 != test_result)
    {
        // IMU self test condition fail
        PRINTF("App_StartRoutine0x0204 self test check fail test_result:%d TEST_STATUS:%d, CALIB_STATUS:%d\n", 
          	test_result, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);

        IMU_SELF_TEST_RESULT = IMU_RESULT_INCORRECT_CALIB;
        //SELF test check FAIL, configure STATUS: INIT
        IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
        IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;
    }
    else
    {
        //PRINTF("App_StartRoutine0x0204 self test pass test_result:%d TEST_STATUS:%d, CALIB_STATUS:%d\n", 
        // 	test_result, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);
      	IMU_SELF_TEST_STATUS = IMU_STATUS_PROCESSING;
      	//Create timer to wait self test cb function  
        if(NULL == imu_calibration_timer_p)
        {            
            imu_calibration_timer_p = timer_set(IMU_CALIB_ID, DEFAULT_TICKS_PER_SECOND * 60, 1, (event_proc_p)App_IMUCalibrationTimeout, NULL);            
            if(imu_calibration_timer_p)
            {
                PRINTF("imu_calib_timer start to wait self test cb function\n");
            }
            else
            {
                PRINTF("[Error]timer full: imu_calib_timer cannot set to wait self test cb function \n");
            }
        }
              	     	  	
    }
}

STATIC FUNC(void,DCM_CODE) start_rountine_imu_self_calib_0x0204(void)
{
 
    uint8 calib_result;
    	   
   	calib_result = ism330dlc_self_calibration_by_RMTP(imu_self_calib_rid_204_cb);

    if(0 != calib_result)
    {
        // IMU self calibration condition fail 
        PRINTF("App_StartRoutine0x0204 self calib return fail:%d TEST_STATUS:%d, CALIB_STATUS:%d\n", 
          	calib_result, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);

        IMU_SELF_CALIB_RESULT = IMU_RESULT_INCORRECT_CALIB;
        //SELF Calib check FAIL, configure STATUS: INIT
        IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
        IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;          	                
    }
    else
    {
        IMU_SELF_CALIB_STATUS = IMU_STATUS_PROCESSING;
        //PRINTF("App_StartRoutine0x0204 self calib pass, ready to wait cb calib result:%d TEST_STATUS:%d, CALIB_STATUS:%d\n", 
        //    	calib_result, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);
        if(NULL == imu_calibration_timer_p)
        {
            imu_calibration_timer_p = timer_set(IMU_CALIB_ID, DEFAULT_TICKS_PER_SECOND * 60, 1, (event_proc_p)App_IMUCalibrationTimeout, NULL);
            if(imu_calibration_timer_p)
            {
                PRINTF("imu_calib_timer start to wait self calibration cb function \n");
            }
            else
            {
                PRINTF("[Error]timer full: imu_calib_timer cannot set to wait self calib cb function\n");
            }
        }              	       	                 
    }           	
}


FUNC(void,DCM_CODE) App_IMUCalibrationTimeout()
{

    if(imu_calibration_timer_p)
    {
        PRINTF("App_IMUCalibrationTimeout imu_calib_timer_stop\n");

        if (!strcmp(IMU_CALIB_ID, imu_calibration_timer_p->name))
        {
            timer_unset(&imu_calibration_timer_p);
        }
    }

    imu_calibration_timer_p = NULL;
    PRINTF("IMU-calib 1mins timeout, reset TEST/CALIB STATUS to INIT \n");

    IMU_SELF_TEST_RESULT = IMU_RESULT_TIMEOUT;
    IMU_SELF_CALIB_RESULT = IMU_RESULT_TIMEOUT;
    //Timeout, configure STATUS: INIT
    IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
    IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;
}

STATIC FUNC(void,DCM_CODE) imu_self_test_rid_204_cb(int res)
{
	IMU_SELF_TEST_RESULT = (uint8)res;

    if(imu_calibration_timer_p)
    {
        PRINTF("imu_self_test_rid_204_cb pass imu_calib_timer stop\n");

        if (!strcmp(IMU_CALIB_ID, imu_calibration_timer_p->name))
        {
            timer_unset(&imu_calibration_timer_p);
        }
    }
    imu_calibration_timer_p = NULL;

	if(0 != IMU_SELF_TEST_RESULT)
	{		
		//PRINTF("imu_self_test_rid_204_cb fail TEST_RESULT:%d, TEST_STATUS:%d\n", IMU_SELF_TEST_RESULT, IMU_SELF_TEST_STATUS);
		PRINTF("imu_self_test_rid_204_cb return fail\n");
        IMU_SELF_TEST_RESULT = IMU_RESULT_INCORRECT_CALIB;

        //SELF TEST FAIL, configure STATUS: INIT
		IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
        IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;
	}
	else
	{
		IMU_SELF_TEST_RESULT = IMU_RESULT_CORRECT;
		IMU_SELF_TEST_STATUS = IMU_STATUS_CORRECT;
		//PRINTF("imu_self_test_rid_204_cb pass, put_event imu self calib TEST_RESULT:%d, TEST_STATUS:%d\n", IMU_SELF_TEST_RESULT, IMU_SELF_TEST_STATUS);
		put_event((const char*)"rid204-start-imu-self-calib", (event_proc_p)start_rountine_imu_self_calib_0x0204, NULL);
	}

	return;
}

STATIC FUNC(void,DCM_CODE) imu_self_calib_rid_204_cb(imu_calib_result_p res)
{

    IMU_SELF_CALIB_RESULT = (uint8)(res->result);

    if(imu_calibration_timer_p)
    {
        PRINTF("imu_self_calib_rid_204_cb pass imu_calib_timer stop\n");

        if (!strcmp(IMU_CALIB_ID, imu_calibration_timer_p->name))
        {
            timer_unset(&imu_calibration_timer_p);
        }
    }
    imu_calibration_timer_p = NULL;

    if(0 != IMU_SELF_CALIB_RESULT)
    {
    	PRINTF("imu_self_calib_rid_204_cb return fail:%d, TEST_STATUS:%d, CALIB_STATUS:%d\n", 
    		IMU_SELF_CALIB_RESULT, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);

    	IMU_SELF_CALIB_RESULT = IMU_RESULT_INCORRECT_CALIB;
    }
    else
    {
    	PRINTF("imu_self_calib_rid_204_cb return pass:%d, TEST_STATUS:%d, CALIB_STATUS:%d\n", 
    		IMU_SELF_CALIB_RESULT, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);

    	IMU_SELF_CALIB_RESULT = IMU_RESULT_CORRECT;
    }

    //Calibration finish, configure STATUS: INIT
    IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
    IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;
    return;
 }

/******************************************************************************
* Name         :App_StopRoutine0x0204
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0x0204(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    put_event((const char*)"rid204-stop", (event_proc_p)stop_rountine_0x0204, NULL);

    pMsgContext->resData[4] = 0x00;//Stop routine success = 0x00
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0204].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) stop_rountine_0x0204(void)
{
    if(imu_calibration_timer_p)
    {
        PRINTF("stop_rountine_0x0204 imu_calib_timer_stop\n");

        if (!strcmp(IMU_CALIB_ID, imu_calibration_timer_p->name))
        {
            timer_unset(&imu_calibration_timer_p);
        }
    }
    imu_calibration_timer_p = NULL;

    IMU_SELF_TEST_STATUS = IMU_STATUS_INIT;
    IMU_SELF_CALIB_STATUS = IMU_STATUS_INIT;

}

/******************************************************************************
* Name         :App_ResultRoutine0x0204
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_ResultRoutine0x0204(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    RID_204_result_t IMUResult = {.result = 0};
   
    if ((IMU_SELF_CALIB_RESULT == IMU_RESULT_TIMEOUT) || (IMU_SELF_TEST_RESULT == IMU_RESULT_TIMEOUT))
    {
    	// Not trig cb function
    	gMsgContextType.resData[4] = IMU_RESULT_TIMEOUT;
    	PRINTF("IMU_RESULT_TIMEOUT \n");
    }    
    else if ((IMU_SELF_CALIB_RESULT == IMU_RESULT_INCORRECT_CALIB) || (IMU_SELF_TEST_RESULT == IMU_RESULT_INCORRECT_CALIB))
    {
    	//IMU_SELF_CALIB_STATUS = IMU_STATUS_INCORRECT_CALIB;
    	gMsgContextType.resData[4] = IMU_RESULT_INCORRECT_CALIB;
    	PRINTF("IMU_RESULT_INCORRECT_CALIB \n");
    }
    else if (IMU_SELF_CALIB_RESULT == IMU_RESULT_INIT)
    {
    	if ( (IMU_SELF_TEST_RESULT == IMU_RESULT_INIT) && (IMU_SELF_CALIB_STATUS == IMU_STATUS_INIT) 
    		&& (IMU_SELF_TEST_STATUS == IMU_STATUS_INIT))	
    	{
    		// System init
            gMsgContextType.resData[4] = IMU_RESULT_INIT;
            PRINTF("IMU_RESULT_INIT \n");
    	}
    	else
    	{
    		// Nt trig cb function
            gMsgContextType.resData[4] = IMU_RESULT_PROCESSING;
            PRINTF("IMU_RESULT_PROCESSING \n");
    	}	
    }    
    else
    {
    	gMsgContextType.resData[4] = IMU_RESULT_CORRECT;
    	PRINTF("IMU_RESULT_CORRECT \n");
    }
    PRINTF("ResultRoutine0x0204 SELF_TEST_RESULT:%d, SELF_CALIB_RESULT:%d, SELF_TEST_STATUS:%d, SELF_CALIB_STATUS:%d \n", 
    	IMU_SELF_TEST_RESULT, IMU_SELF_CALIB_RESULT, IMU_SELF_TEST_STATUS, IMU_SELF_CALIB_STATUS);
    
 
    IMUResult.self_test = IMU_SELF_TEST_RESULT;
    IMUResult.self_calib = IMU_SELF_CALIB_RESULT;
    gMsgContextType.resData[5] = (uint8)IMUResult.result; 
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0204].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_StartRoutine0xAA00
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :
*  
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0xAA00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    DsdInternal_RoutineStarted();
    /* Add your code here */    
    
    put_event((const char*)"ridAA00-start", (event_proc_p)start_rountine_0xAA00, NULL);
    pMsgContext->resData[4] = 0x00;//Routine diagnostic pass = 0x00
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xAA00].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) start_rountine_0xAA00(void)
{
    set_rmtp_hcan_config_enable();
}

/******************************************************************************
* Name         :App_StopRoutine0xAA00
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_StopRoutine0xAA00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    put_event((const char*)"ridAA00-stop", (event_proc_p)stop_rountine_0xAA00, NULL);

    pMsgContext->resData[4] = 0x00;//Stop routine success = 0x00
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xAA00].DcmDspRoutineInfoRef.DcmDspRoutineStopOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}

STATIC FUNC(void,DCM_CODE) stop_rountine_0xAA00(void)
{
    set_rmtp_hcan_config_disable();
}

/******************************************************************************
* Name         :App_ResultRoutine0xAA00
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :
*
******************************************************************************/
FUNC(void,DCM_CODE) App_ResultRoutine0xAA00(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    Std_ReturnType ret = E_OK;

    ret = get_rmtp_hcan_config_status();

    //put_event((const char*)"ridAA00-result", (event_proc_p)result_rountine_0xAA00, (void*)NULL);

    gMsgContextType.resData[4] = (uint8)ret; 
    pMsgContext->resDataLen = 4U + DcmDspRoutineIdentifierTable_31[RoutineHandle_0xAA00].DcmDspRoutineInfoRef.DcmDspRoutineRequestResOut.DcmDspRoutineSignalLength;
    DsdInternal_ProcessingDone(pMsgContext);
}
#if 0
STATIC FUNC(void,DCM_CODE) result_rountine_0xAA00(void)
{
    
}
#endif
STATIC FUNC(void,DCM_CODE) set_rmtp_hcan_config_enable(void)
{
    RMTP_HCAN_Config_Flag = TRUE;
}

STATIC FUNC(void,DCM_CODE) set_rmtp_hcan_config_disable(void)
{
    RMTP_HCAN_Config_Flag = FALSE;
}

FUNC(Std_ReturnType, DCM_CODE) get_rmtp_hcan_config_status(void)
{
    Std_ReturnType Result = E_OK;
    Result = (RMTP_HCAN_Config_Flag == TRUE ? E_OK : E_NOT_OK) ;
    return Result;
}
#endif

/* 0x3D */
#if(DCM_SERVICE_3D_ENABLED == STD_ON)
#endif

/* 0x85 */
#if(DCM_SERVICE_85_ENABLED == STD_ON)
/******************************************************************************
* Name         :App_ON_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ON_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS,DEM_DTC_KIND_ALL_DTCS); 

    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_OFF_Send
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_OFF_Send(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    /* Add your code here */
    (void)Dem_DisableDTCSetting(DEM_DTC_GROUP_ALL_DTCS,DEM_DTC_KIND_ALL_DTCS); 

    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
#endif

/* 0x86 */
#if(DCM_SERVICE_86_ENABLED == STD_ON)
#endif

void AppComTxRx_Start(void)
{
    Com_RxStart();
    Com_TxStart();
    Dcm_ComMessage_Status = Dcm_EnRx_EnTx;
    cubtek_faw_did_ds_can_status_set(CAN_EnRx_EnTx);
}

void AppComTxRx_Stop(void)
{
	Com_RxStop();
    Com_TxStop();
    Dcm_ComMessage_Status = Dcm_DisRx_DisTx;
    cubtek_faw_did_ds_can_status_set(CAN_DisRx_DisTx);
}

void AppCom_DisTx_EnRx(void)
{
    Com_RxStart();
    Com_TxStop();
    Dcm_ComMessage_Status = Dcm_EnRx_DisTx;
    cubtek_faw_did_ds_can_status_set(CAN_EnRx_DisTx);
}
