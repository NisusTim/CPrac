/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_Cbk.c
********************************************************************************
*   Project/Product : AUTOSAR BSW PROJECT
*   Title           : Dem module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : Dem module configuration File
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

#include "Dem_Cbk.h"

/*
extern VMSCtrlPara VmsCmdPara;
extern McuFeedbackPara1 McuSendPara300h;
extern McuFeedbackPara2 McuSendPara301h;
extern McuFeedbackPara3 McuSendPara302h;
extern McuFeedbackPara4 McuSendPara310h;
extern int16 G_i16_KeyOn;*/
/*------------------------------------------------------------------------------------------------*
 * FUNCTION DEFINITIONS
 *------------------------------------------------------------------------------------------------*/
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Dem_TriggerOnEventStatusChangeCallback
* Description   : Triggers on changes of the UDS DTC status byte.
*
* Inputs        :
*     Type                 Name         Description
*     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Dem_EventIdType     EventId   Identification of an Event by assigned EventId.
*      uint8    EventStatusOld   UDS DTC status byte of event before change
*      uint8    EventStatusNew   UDS DTC status byte of event after change(
*
* Outputs       : none
*
* Limitations   : none
*
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_CallbackTriggerOnEventStatusChange(Dem_EventIdType EventId,
                                                      uint8 EventStatusOld,
                                                      uint8 EventStatusNew)
{
    (void)EventId;
    (void)EventStatusOld;
    (void)EventStatusNew;
    return E_OK;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Dem_CallbackTriggerOnClearEventAllowed
* Description   : Triggers on DTC-deletion, which is not allowed if the out-parameter returns False..
*
* Inputs        : none
*
* Outputs       : none
*
* Limitations   : E_OK :clearance of event is allowed
                  E_NOT_OK :clearance of event is not allowed 
*
************************************************************************************************
END_FUNCTION_HDR */
Std_ReturnType Dem_CallbackTriggerOnClearEventAllowed(void)
{
    return E_OK;
}

Std_ReturnType Dem_ReadDataElementFun_0x0(uint8 size,uint8* Buffer)
{
    return E_OK;
}



