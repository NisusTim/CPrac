/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_Cbk.h
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

#ifndef _DEM_CBK_H_
#define _DEM_CBK_H_

/*------------------------------------------------------------------------------------------------*
 *   INCLUDES
 *------------------------------------------------------------------------------------------------*/

#include "Std_Types.h"
#include "Dem_Types.h"

/*------------------------------------------------------------------------------------------------*
 *   FUNCTION PROTOTYPES
 *------------------------------------------------------------------------------------------------*/

extern Std_ReturnType Dem_CallbackTriggerOnEventStatusChange(Dem_EventIdType EventId,
        uint8 EventStatusOld,
        uint8 EventStatusNew);
extern Std_ReturnType Dem_CallbackTriggerOnClearEventAllowed(void);

extern Std_ReturnType Dem_ReadDataElementFun_0x0(uint8 size,uint8* Buffer);

#endif /* _DEM_CBK_H_ */



