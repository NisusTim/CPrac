/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Cfg.h
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Com module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Com module configuration File
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
#ifndef _COM_CFG_H_
#define _COM_CFG_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com_Types.h"
/*adding underlying layer's head files here if necessary*/ 
#include "CanIf.h" 

/*******************************************************************************
*   Macro define
*******************************************************************************/
#define COM_VERSION_INFO_API					STD_OFF
#define COM_ENABLE_NONSENDTYPEONLY
//#define COM_ENABLE_TXCONFIRMATIONFUN
//#define COM_ENABLE_TXTOINDF UN
#define COM_ENABLE_RXINDICATIONFUN
#define COM_ENABLE_RXTOINDFUN
#define COM_TXMAIN_FUNCTION_PERIOD				(10U)
#define COM_RXMAIN_FUNCTION_PERIOD				(10U)
#define COM_SIGNALROUTINEMAIN_FUNCTION_PERIOD	(10U)
#define RADAR_STA_TXPDUID						(1U)
#define TP_BAM_TXPDUID   						(2U)  //CanIfTxPduConfig[2]
#define TP_DM1_TXPDUID   						(3U)  //CanIfTxPduConfig[3]
#define TP_DT_TXPDUID   						(4U)  //CanIfTxPduConfig[4]
#define RMTP_DATA_TXPDUID   					(5U)  //CanIfTxPduConfig[5]
#define IPDU_DATA_TXPDUID   					(6U)  //CanIfTxPduConfig[6]

/******************************************************************************
*    number of Tx object                                                       
******************************************************************************/
#define COM_TXIPDUNUM    		(2U)
/******************************************************************************
*    Handles of send messages                                                  
******************************************************************************/
#define COM_TXIPDUHeader    	(0U)
#define COM_TXIPDURadar_Sta    	(1U)
/******************************************************************************
*    number of Tx object Signal                                                
******************************************************************************/
#define COM_TXSIGNUM 		  	(28U)
/******************************************************************************
*    Handles of send signals                                                  
******************************************************************************/
#define COM_TXSIG_RADER_SLEEP_FLAG    				(0U)
#define COM_TXSIG_COMMUNICATION_BUS_OFF    			(1U)
#define COM_TXSIG_LOST_COMMUNICATION_WITH_CAMERA 	(2U)
#define COM_TXSIG_MCU_TEMPERATURE_TOO_HIGH 			(3U)
#define COM_TXSIG_MCU_TEMPERATURE_TOO_LOW   		(4U)
#define COM_TXSIG_MCU_VOLTAGE_TOO_HIGH    			(5U)
#define COM_TXSIG_MCU_VOLTAGE_TOO_LOW    			(6U)
#define COM_TXSIG_RF_VOLTAGE1_TOO_HIGH    			(7U)
#define COM_TXSIG_RF_VOLTAGE1_TOO_LOW    			(8U)
#define COM_TXSIG_RF_VOLTAGE2_TOO_HIGH   			(9U)
#define COM_TXSIG_RF_VOLTAGE2_TOO_LOW    			(10U)
#define COM_TXSIG_BATTERY_VOLTAGE_TOO_HIGH			(11U)
#define COM_TXSIG_BATTERY_VOLTAGE_TOO_LOW			(12U)
#define COM_TXSIG_RF_TEMPERATURE_TOO_HIGH			(13U)
#define COM_TXSIG_RF_TEMPERATURE_TOO_LOW    		(14U)
#define COM_TXSIG_MCU_MASTER_CLOCK_ERROR    		(15U)
#define COM_TXSIG_MCU_ERROR    						(16U)
#define COM_TXSIG_MCU_MEMORY_ERROR    				(17U)
#define COM_TXSIG_G_SENSOR_FAULT    				(18U)
#define COM_TXSIG_RF_SENSOR_FAULT    				(19U)
#define COM_TXSIG_MISSING_CALIBRATION    			(20U)
#define COM_TXSIG_RADAR_MOUNT_POSITION_SHIFT_ERROR	(21U)
#define COM_TXSIG_INVALID_VEHICLE_SPEED_SIGNAL		(22U)
#define COM_TXSIG_INVALID_YAW_RATE_SIGNAL    		(23U)
#define COM_TXSIG_INVALID_STEERING_ANGLE_SIGNAL		(24U)
#define COM_TXSIG_INVALID_GEAR_POSITION_SIGNAL		(25U)
#define COM_TXSIG_INVALID_IGN_STA_SIGNAL    		(26U)
#define COM_TXSIG_RADAR_BLOCK 						(27U)
/******************************************************************************
*    Send Signal structures                                                    
******************************************************************************/
typedef struct {
	uint16 RF_Voltage1_too_low:1; //bit 7
	uint16 MCU_Voltage_too_low:1; //bit 6
	uint16 MCU_Voltage_too_high:1; //bit 5
	uint16 MCU_Temperature_too_low:1; //bit 4
 	uint16 MCU_Temperature_too_high:1; //bit 3
	uint16 Lost_Communication_With_Camera:1; //bit 2
	uint16 Communication_Bus_OFF:1; //bit 1
	uint16 Radar_Sleep_Flag:1; //bit 0
	uint16 MCU_Master_Clock_Error:1; //bit 15
	uint16 RF_Temperature_too_low:1; //bit 14
	uint16 RF_Temperature_too_high:1; //bit 13
	uint16 Battery_Voltage_too_low:1; //bit 12
	uint16 Battery_Voltage_too_high:1; //bit 11
	uint16 RF_Voltage2_too_high:1; //bit 10
	uint16 RF_Voltage2_too_low:1; //bit 9
	uint16 RF_Voltage1_too_high:1; //bit 8
	uint16 Invalid_Steering_Angle_signal:1; //bit 23
	uint16 Invalid_Yaw_Rate_signal:1; //bit 22
	uint16 Invalid_Vehicle_Speed_signal:1; //bit 21
	uint16 Missing_Calibration:1; //bit 20
	uint16 RF_Sensor_fault:1; //bit 19
	uint16 G_Sensor_fault:1; //bit 18
	uint16 MCU_Memory_Error:1; //bit 17
	uint16 MCU_Error:1; //bit 16
	uint16 unused1:4;
	uint16 Radar_Mount_Position_Shift_Error:1; //bit27
	uint16 Radar_block:1; //bit26
	uint16 Invalid_IGN_Sta_signal:1; //bit 25
	uint16 Invalid_Gear_position_signal:1; //bit 24
	uint16 unused2;
	uint16 unused3;
}IpduRadar_Sta_Type;
/******************************************************************************
*    Send Message unions                                                       
******************************************************************************/
typedef union {
	IpduRadar_Sta_Type  Ipdu;
    uint8  _c[8];
}IpduRadar_Sta_bufType;

/******************************************************************************
*    Data buffer for sent objects
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduRadar_Sta_bufType, COM_PRIVATE_DATA) TxIpduRadar_Sta;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Data buffer for Sent Message default Value
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduRadar_Sta_bufType, COM_CONFIG_CONST)  TxIpduRadar_StaDefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_TXIPDUNUM >= 1u)
/******************************************************************************
*    used for application:message tx timeout indication Function               
******************************************************************************/
#ifdef COM_ENABLE_TXTOINDFUN 
extern void AppIpduRadar_Sta_TxTOIndication(void);
#endif

/******************************************************************************
*    Ipdu Tx Confirmation function declare                                     
******************************************************************************/
#ifdef COM_ENABLE_TXCONFIRMATIONFUN 
extern void AppIpduRadar_Sta_Conf(void);
#endif

#endif /*#if (COM_TXIPDUNUM>=1)*/ 

/******************************************************************************
*    number of Rx object                                                       
******************************************************************************/
#define COM_RXIPDUNUM    (2U)
/******************************************************************************
*    Handles of receive messages                                                  
******************************************************************************/
#define COM_RXIPDUVehInfo1    (0U)
#define COM_RXIPDUVehInfo2    (1U)
/******************************************************************************
*    the buffer size of Message received                                       
******************************************************************************/
#define COM_RXIPDUVehInfo1_BUFFER_SIZE    (8U)
#define COM_RXIPDUVehInfo2_BUFFER_SIZE    (8U)
/******************************************************************************
*    number of Rx object Signal                                                
******************************************************************************/
#define COM_RXSIGNUM    (0U)
/******************************************************************************
*    Handles of receive signals                                                  
******************************************************************************/
/*PHY_Info*/


/******************************************************************************
*    Receive Signal structures                                                    
******************************************************************************/
typedef struct {
	uint16 VehSpeed		: 11;
	uint16 VehSpeed_V 	: 1;
	uint16 YawRat_V		: 1;
	uint16 unused1		: 2;
	uint16 Str_Angle_V	: 1;
	uint16 YawRate;
    uint16 Str_Angle;
    uint16 unused3;
}IpduVehInfo1_Type;

typedef struct {
	uint16 unused1:1;
	uint16 Gear_sta 	: 3;
	uint16 Gear_Sta_V 	: 1;
	uint16 unused2:5;
	uint16 IGN_Sta_V	: 1;
	uint16 IGN_Sta		: 1;
	uint16 unused3:4;
	uint16 unused4;
	uint16 unused5;
    uint16 unused6;
}IpduVehInfo2_Type;


/******************************************************************************
*    Receive Message unions                                                       
******************************************************************************/
typedef union {
	uint64 Raw;
	IpduVehInfo1_Type  Ipdu;
    uint8  _c[8];
}IpduVehInfo1_bufType,*IpduVehInfo1_bufType_p;

typedef union {
	uint64 Raw;
	IpduVehInfo2_Type  Ipdu;
    uint8  _c[8];
}IpduVehInfo2_bufType,*IpduVehInfo2_bufType_p;

/******************************************************************************
*    Data buffer for Receive objects
******************************************************************************/
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"
extern VAR(IpduVehInfo1_bufType, COM_PRIVATE_DATA)  RxIpduVehInfo1;
extern VAR(IpduVehInfo2_bufType, COM_PRIVATE_DATA)  RxIpduVehInfo2;
#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

/******************************************************************************
*    Data buffer for Receive Message default Value
******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"
extern CONST(IpduVehInfo1_bufType, COM_CONFIG_CONST)  RxIpduVehInfo1_DefaultValue;
extern CONST(IpduVehInfo2_bufType, COM_CONFIG_CONST)  RxIpduVehInfo2_DefaultValue;
#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

#if (COM_RXIPDUNUM >= 1u)

/******************************************************************************
*    rx Ipdu timeout indication function Declare                               
******************************************************************************/
#ifdef COM_ENABLE_RXTOINDFUN 
extern void AppRxIpduVehInfo1_TimeOutInd(void);
extern void AppRxIpduVehInfo2_TimeOutInd(void);
#endif

/******************************************************************************
*    Rx indication function Declare                                            
******************************************************************************/
#ifdef COM_ENABLE_RXINDICATIONFUN 
extern void AppIpduVehInfo1_Ind(void);
extern void AppIpduVehInfo2_Ind(void);
extern void AppComTxRx_Stop(void);
extern void AppComTxRx_Start(void);
extern void AppCom_DisTx_EnRx(void);
#endif

#endif /*#if (COM_RXIPDUNUM>=1)*/ 

/******************************************************************************
*    Signal Gateway                                                            
******************************************************************************/
#ifdef COM_ENABLE_ROUTESIGNAL
#define COM_GWIPDUNUM    (0U)
#define COM_GWSIGNUM     (0U)
#endif

/******************************************************************************
*    Ipdu Group                                                                
******************************************************************************/
#if((COM_TXIPDUNUM >= 1u) || (COM_RXIPDUNUM >= 1u))
#define COM_IPDUGROUPNUM    (2U)
#define COM_IPDUGROUP0    (0x1U)
#define COM_IPDUGROUP1    (0x2U)
#define COM_GROUPIPDUNUM    (9U)
#endif

/******************************************************************************
*    data declaration                                                          
******************************************************************************/
extern void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr);
extern void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr);

#if(COM_TXIPDUNUM >= 1u)
#define COM_START_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

extern VAR(PduInfoType, COM_APPL_DATA) Com_TxIpdu[COM_TXIPDUNUM];

#define COM_STOP_SEC_VAR_UNSPECIFIED  
#include "MemMap.h"

#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED  
#include "MemMap.h"

extern CONST(PduInfoType, COM_CONFIG_CONST)  Com_TxIpduInitTable[COM_TXIPDUNUM]; 
extern CONST(Com_TxSigTableType, COM_CONFIG_CONST)  Com_TxSigTable[COM_TXSIGNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_TxIpduDefaultValue[COM_TXIPDUNUM];

#ifdef COM_ENABLE_TXCONFIRMATIONFUN
extern CONST(Com_TxConfirmationType, COM_CONFIG_CONST)  Com_TxIpduConfirmTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_TXTOINDFUN
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST)  Com_TxIpduTOIndicationTable[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDUTXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST)  Com_LpduTxErrIndicationTable[COM_TXIPDUNUM];
#endif

extern CONST(uint8, COM_CONFIG_CONST)  Com_TxIpduTable[COM_TXIPDUNUM];

#ifndef COM_ENABLE_NONSENDTYPEONLY

#ifdef COM_ENABLE_ACTIVEPORPERTY 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduFastCycleTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduSigNum[COM_TXIPDUNUM];

extern FUNC(void, COM_PUBLIC_CODE) Com_ActiveSig
(
    Com_SignalIdType SignalId
);

extern FUNC(void, COM_PUBLIC_CODE) Com_DisactiveSig
(
    Com_SignalIdType SignalId
);

extern CONST(Com_SignalIdType, COM_CONFIG_CONST)  Com_TxSigOffsetTable[COM_TXIPDUNUM];

#endif

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTdelayTable[COM_TXIPDUNUM];
extern CONST(uint8, COM_CONFIG_CONST) Com_TxIpduRepNumTable[COM_TXIPDUNUM];
#endif /*#ifndef COM_ENABLE_NONSENDTYPEONLY*/

extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduCycleTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduTimeOutTable[COM_TXIPDUNUM]; 
extern CONST(uint16, COM_CONFIG_CONST) Com_TxIpduOffsetTable[COM_TXIPDUNUM];

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM >= 1u)

#ifdef COM_ENABLE_RXEXTEND
extern CONST(uint8, COM_CONFIG_CONST) Com_RxIpduSigNum[COM_RXIPDUNUM];
extern CONST(Com_SignalIdType, COM_CONFIG_CONST) Com_RxSigOffsetTable[COM_RXIPDUNUM];
#endif

extern CONST(PduInfoType, COM_CONFIG_CONST) Com_RxIpduInitTable[COM_RXIPDUNUM];
extern CONST(Com_RxSigTableType, COM_CONFIG_CONST) Com_RxSigTable[COM_RXSIGNUM];
extern CONST(Com_RxIpduTableType, COM_CONFIG_CONST) Com_RxIpduTable[COM_RXIPDUNUM];
extern CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduDefaultValue[COM_RXIPDUNUM];

#ifdef COM_ENABLE_RXINDICATIONFUN
extern CONST(Com_RxIndicationType, COM_CONFIG_CONST) Com_RxIpduIndicationTable[COM_RXIPDUNUM]; 
#endif

#ifdef COM_ENABLE_RXTOINDFUN 
extern CONST(Com_TOIndicationType, COM_CONFIG_CONST) Com_RxIpduTOIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXERRINDFUN
extern CONST(Com_ErrIndicationType, COM_CONFIG_CONST) Com_LpduRxErrIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXSTARTINDIFUN
extern CONST(Com_LpduRxStartIndicationType, COM_CONFIG_CONST)  
             Com_LpduRxStartIndicationTable[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_RXTIMEOUTVALUE
extern  CONSTP2CONST(uint8,COM_CONFIG_CONST,COM_CONFIG_CONST) Com_RxIpduTimeoutValue[COM_RXIPDUNUM];
#endif

extern CONST(PduLengthType, COM_CONFIG_CONST)  Com_RxIpduBufferSize[COM_RXIPDUNUM];


#endif /*#if(COM_RXIPDUNUM>=1)*/


#if(COM_TXIPDUNUM >= 1u)
extern CONST(Com_SendSignalType, COM_CONFIG_CONST)  Com_SendSignalTable[COM_TXSIGNUM];
#endif


#if(COM_RXIPDUNUM >= 1u)
extern  CONST(Com_ReceiveSignalType, COM_CONFIG_CONST)   Com_ReceiveSignalTable[COM_RXSIGNUM];
#endif

#ifdef COM_ENABLE_ROUTESIGNAL
#if(COM_GWSIGNUM >= 1u)
extern CONST(Com_SignalGatewayIpduTableType, COM_CONFIG_CONST)  
             Com_SignalGatewayIpduTable[COM_GWIPDUNUM];
             
extern CONST(Com_SignalGatewayTableType, COM_CONFIG_CONST)  Com_SignalGatewayTable[COM_GWSIGNUM];
#endif /*#if(COM_GWSIGNUM>=1)*/
#endif /*#ifdef COM_ENABLE_ROUTESIGNAL*/


#if(COM_IPDUGROUPNUM >= 1u)
extern CONST(Com_GroupIpduTableType, COM_CONFIG_CONST)  Com_GroupIpduTable[COM_GROUPIPDUNUM];
extern CONST(Com_IpduGroupTableType, COM_CONFIG_CONST)  Com_IpduGroupTable[COM_IPDUGROUPNUM];
#endif

#if(COM_TXIPDUNUM >= 1u)
extern CONST(PduIdType, COM_CONFIG_CONST) Com_TxIpduIdMapTable[COM_TXIPDUNUM];
#define Com_TransmitLPDU(ComTxPduId,PduInfoPtr)     CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr) 
#define Com_Transmit(ComTxPduId,PduInfoPtr)	        CanIf_Transmit(Com_TxIpduIdMapTable[ComTxPduId],PduInfoPtr)
#endif

#endif



