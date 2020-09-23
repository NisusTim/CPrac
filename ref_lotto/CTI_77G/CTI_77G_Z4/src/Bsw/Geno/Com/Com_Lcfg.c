/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Com_Lcfg.c
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

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com.h"

#define COM_START_SEC_PUBLIC_CODE
#include "MemMap.h"
/*******************************************************************************
*   for Com_SendSignal
*******************************************************************************/

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRadar_Sleep_Flag
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Radar_Sleep_Flag = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgCommunication_Bus_OFF
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Communication_Bus_OFF = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgLost_Communication_With_Camera
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Lost_Communication_With_Camera = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Temperature_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Temperature_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Temperature_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Temperature_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Voltage_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Voltage_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Voltage_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Voltage_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Voltage1_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Voltage1_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Voltage1_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Voltage1_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Voltage2_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Voltage2_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Voltage2_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Voltage2_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgBattery_Voltage_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Battery_Voltage_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgBattery_Voltage_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Battery_Voltage_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Temperature_too_high
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Temperature_too_high = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Temperature_too_low
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Temperature_too_low = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Master_Clock_Error
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Master_Clock_Error = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Error
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Error = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMCU_Memory_Error
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.MCU_Memory_Error = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgG_Sensor_fault
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.G_Sensor_fault = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRF_Sensor_fault
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.RF_Sensor_fault = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgMissing_Calibration
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Missing_Calibration = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRadar_Mount_Position_Shift_Error
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Radar_Mount_Position_Shift_Error = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgInvalid_Vehicle_Speed_signal
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Invalid_Vehicle_Speed_signal = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgInvalid_Yaw_Rate_signal
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Invalid_Yaw_Rate_signal = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgInvalid_Steering_Angle_signal
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Invalid_Steering_Angle_signal = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgInvalid_Gear_position_signal
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Invalid_Gear_position_signal = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgInvalid_IGN_Sta_signal
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Invalid_IGN_Sta_signal = (*(uint16 *)SigValue);
}

FUNC(void, COM_PUBLIC_CODE) Com_SendSIgRadar_Block
(
    P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue
)
{
	TxIpduRadar_Sta.Ipdu.Radar_block = (*(uint16 *)SigValue);
}


/*******************************************************************************
*   for Com_ReceiveSignal
*******************************************************************************/


#define COM_STOP_SEC_PUBLIC_CODE
#include "MemMap.h"

/*******************************************************************************
*   Signal Interface Structure
*******************************************************************************/
#define COM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"

#if (COM_TXSIGNUM >= 1u)
CONST(Com_SendSignalType, COM_CONFIG_CONST) Com_SendSignalTable[COM_TXSIGNUM] =
{
	&Com_SendSIgRadar_Sleep_Flag,
	&Com_SendSIgCommunication_Bus_OFF,
	&Com_SendSIgLost_Communication_With_Camera,
	&Com_SendSIgMCU_Temperature_too_high,
	&Com_SendSIgMCU_Temperature_too_low,
	&Com_SendSIgMCU_Voltage_too_high,
	&Com_SendSIgMCU_Voltage_too_low,
	&Com_SendSIgRF_Voltage1_too_high,
	&Com_SendSIgRF_Voltage1_too_low,
	&Com_SendSIgRF_Voltage2_too_high,
	&Com_SendSIgRF_Voltage2_too_low,
	&Com_SendSIgBattery_Voltage_too_high,
	&Com_SendSIgBattery_Voltage_too_low,
	&Com_SendSIgRF_Temperature_too_high,
	&Com_SendSIgRF_Temperature_too_low,
	&Com_SendSIgMCU_Master_Clock_Error,
	&Com_SendSIgMCU_Error,
	&Com_SendSIgMCU_Memory_Error,
	&Com_SendSIgG_Sensor_fault,
	&Com_SendSIgRF_Sensor_fault,
	&Com_SendSIgMissing_Calibration,
	&Com_SendSIgRadar_Mount_Position_Shift_Error,
	&Com_SendSIgInvalid_Vehicle_Speed_signal,
	&Com_SendSIgInvalid_Yaw_Rate_signal,
	&Com_SendSIgInvalid_Steering_Angle_signal,
	&Com_SendSIgInvalid_Gear_position_signal,
	&Com_SendSIgInvalid_IGN_Sta_signal,
	&Com_SendSIgRadar_Block
};
#endif

#if (COM_RXIPDUNUM >= 1u)
CONST(Com_ReceiveSignalType, COM_CONFIG_CONST) Com_ReceiveSignalTable[COM_RXSIGNUM] =
{

};
#endif

#define COM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
