/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Com.c
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
#include "Dem.h"
#include "Dem_Lcfg.h"
#include "typedefs.h"

#include "sbc_fs8x.h"
#include "event.h"
#include "customer.h"
#include "can_cubtek.h"
#include "vehicle.h"
#include "sys_shared.h"

#define MAX_ERROR_CNT			(10)
#define MAX_PASS_CNT			(10)
#define MAX_SLEEP_CNT			(300)

PduIdType _pduId;
uint8 *_dataPtr;

static uint16 timeout_count_VehInfo1 = 0;
static uint16 timeout_count_VehInfo2 = 0;
static uint16 timeout_sleep_count_VehInfo2 = 0;
static uint16 Lost_Communication_With_Camera = 0;
static uint8 app_vehinfo1_flag = FALSE;
static uint8 app_vehinfo2_flag = FALSE;
static uint32 ign_status = 0;
static uint32 ign_val = 0;
static uint8 disable_sleep_flag = FALSE;

void Com_TxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
    (void)PduId;
}

void Com_RxIpduCallout(PduIdType PduId, uint8 *DataPtr)
{
	_pduId = PduId;
	_dataPtr = DataPtr;

	uint16 Communication_Bus_OFF = 0;

	if(FALSE != cubtek_faw_did_ds_communication_bus_off_status_get())	
	{	
		cubtek_faw_did_ds_communication_bus_off_status_set(FALSE);
		Communication_Bus_OFF = 0;
		put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC07688_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
	}
	Com_SendSignal(COM_TXSIG_COMMUNICATION_BUS_OFF, &Communication_Bus_OFF);
}

extern void cubtek_can_vehcle_info2_proc(uint64_t data);
extern void cubtek_can_info_proc(uint64_t data);

/******************************************
 * Vehicle physical signals to radar
 * ID: 0x300
 ******************************************/
void AppIpduVehInfo1_Ind(void)
{
	if(TRUE == app_vehinfo1_flag)
	{
		return;
	}

	app_vehinfo1_flag = TRUE;	
	cubtek_can_info_proc(((IpduVehInfo1_bufType_p)_dataPtr)->Raw);

	timeout_count_VehInfo1 = 0;
	timeout_sleep_count_VehInfo2 = 0;
	if ( (timeout_count_VehInfo1 == 0) && (timeout_count_VehInfo2 == 0))
	{	
		if(Lost_Communication_With_Camera != 0)
		{
			put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC23A87_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
			Lost_Communication_With_Camera = 0;
		}
	}

	Com_SendSignal(COM_TXSIG_LOST_COMMUNICATION_WITH_CAMERA, &Lost_Communication_With_Camera);
	app_vehinfo1_flag = FALSE;
}

/******************************************
 * Vehicle status signals to radar
 * ID: 0x301
 ******************************************/
void AppIpduVehInfo2_Ind(void)
{
	if(TRUE == app_vehinfo2_flag)
	{
		return;
	}

	app_vehinfo2_flag = TRUE;	
	cubtek_can_vehcle_info2_proc(((IpduVehInfo2_bufType_p)_dataPtr)->Raw);

	timeout_count_VehInfo2 = 0;
	timeout_sleep_count_VehInfo2 = 0;
	if ( (timeout_count_VehInfo1 == 0) && (timeout_count_VehInfo2 == 0))
	{
		if(Lost_Communication_With_Camera != 0)
		{		
			put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC23A87_INDEX<<8) | DEM_EVENT_STATUS_PASSED));
			Lost_Communication_With_Camera = 0;
		}
	}
	
	Com_SendSignal(COM_TXSIG_LOST_COMMUNICATION_WITH_CAMERA, &Lost_Communication_With_Camera);
	app_vehinfo2_flag = FALSE;
}

void AppRxIpduVehInfo1_TimeOutInd(void)
{
	IpduVehInfo2_bufType data = {.Raw =0};

	/*Timeout handler (0x301) starts when power is on 60s*/
	if(FALSE == cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_get())	
	{
		return;
	}

	Com_ReceiveSignal(COM_RXIPDUVehInfo1, &data);
	timeout_count_VehInfo1++;
	if(MAX_ERROR_CNT < timeout_count_VehInfo1)
	{
		ign_status = get_ign_status();
		ign_val = get_ign_value();		
		// Record lost communication of DTC when
		// IGN ON, IGN valid, and no 0x300(more than 10 frames)			
		if ( (VEH_IGN_ON == ign_val) && ( VEH_STATUS_VALID == ign_status))
		{			
			if(Lost_Communication_With_Camera != 1)
			{
				Lost_Communication_With_Camera = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC23A87_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
 		}
		Com_SendSignal(COM_TXSIG_LOST_COMMUNICATION_WITH_CAMERA, &Lost_Communication_With_Camera);
		timeout_count_VehInfo1 = MAX_ERROR_CNT - 9;
	}
}

void AppRxIpduVehInfo2_TimeOutInd(void)
{
	IpduVehInfo2_bufType data = {.Raw =0};

	/* Lost CAN message(0x301) more than 30 sec and  enter sleep mode when enable sleep flag*/
	disable_sleep_flag = product_dis_sleep_flag_get();
	if(FALSE == disable_sleep_flag)
	{	
		if (MAX_SLEEP_CNT < timeout_sleep_count_VehInfo2 )
		{
			if(FALSE == cubtek_faw_did_ds_ready_to_sleep_status_get())	
			{
				cubtek_faw_did_ds_ready_to_sleep_status_set(TRUE);
			}
			timeout_sleep_count_VehInfo2 = 0;
		}
		else
		{
			timeout_sleep_count_VehInfo2++;
		}
	}
	else
	{
		timeout_sleep_count_VehInfo2 = 0;
	}

	/*Timeout handler (0x301) starts when power is on 60s*/
	if(FALSE == cubtek_faw_did_ds_can_comm_lost_after_wakeup_status_get())
	{
		return;
	}

	Com_ReceiveSignal(COM_RXIPDUVehInfo2, &data);
	timeout_count_VehInfo2++;
	if(MAX_ERROR_CNT < timeout_count_VehInfo2)
	{
		ign_status = get_ign_status();
		ign_val = get_ign_value();

		// Record lost communication of DTC when
		// IGN ON, IGN valid, and no 0x301(more than 10 frames)
		if ( (VEH_IGN_ON == ign_val) && ( VEH_STATUS_VALID == ign_status))
		{				
			if(Lost_Communication_With_Camera != 1)
			{		
				Lost_Communication_With_Camera = 1;
				put_event("dem_event_set", (event_proc_p)Dem_SetEventStatus_By_Parameter, (void*)( (DTC_0xC23A87_INDEX<<8) | DEM_EVENT_STATUS_FAILED));
			}
 		}
		Com_SendSignal(COM_TXSIG_LOST_COMMUNICATION_WITH_CAMERA, &Lost_Communication_With_Camera);
		timeout_count_VehInfo2 = MAX_ERROR_CNT - 9;
	}
}

