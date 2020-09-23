/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_LCfg.h
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
#ifndef _DEM_LCFG_H_
#define _DEM_LCFG_H_
#include "Dem_Cfg.h"

#define DTC_0xC07688_INDEX                                          (0U)
#define DTC_0xC23A87_INDEX                                          (1U)
#define DTC_0x950098_INDEX                                          (2U)
#define DTC_0x95009A_INDEX                                          (3U)
#define DTC_0x9500A3_INDEX                                          (4U)
#define DTC_0x9500A2_INDEX                                          (5U)
#define DTC_0x9501A3_INDEX                                          (6U)
#define DTC_0x9501A2_INDEX                                          (7U)
#define DTC_0x9502A3_INDEX                                          (8U)
#define DTC_0x9502A2_INDEX                                          (9U)
#define DTC_0x911717_INDEX                                          (10U)
#define DTC_0x911716_INDEX                                          (11U)
#define DTC_0x950198_INDEX                                          (12U)
#define DTC_0x95019A_INDEX                                          (13U)
#define DTC_0x950049_INDEX                                          (14U)
#define DTC_0x950045_INDEX                                          (15U)
#define DTC_0x950044_INDEX                                          (16U)
#define DTC_0x950096_INDEX                                          (17U)
#define DTC_0x950196_INDEX                                          (18U)
#define DTC_0x950054_INDEX                                          (19U)
#define DTC_0x950154_INDEX                                          (20U)
#define DTC_0x950081_INDEX                                          (21U)
#define DTC_0x950181_INDEX                                          (22U)
#define DTC_0x950281_INDEX                                          (23U)
#define DTC_0x950381_INDEX                                          (24U)
#define DTC_0x950481_INDEX                                          (25U)
#define DTC_0x950097_INDEX                                          (26U)

extern const Dem_DebounceAlgorithmClassType DemDebounceAlgorithmClassTab[];
extern const Dem_EventClassType  DemEventClassSet[];
extern const Dem_FreezeFrameClassType DemFreezeFrameClassTab0[] ;
extern const Dem_EventParameterType DemEventParameterTab[];
extern const Dem_ExternalCSDataElementClassType Dem_ExternalCSDataElementClassTab[];
extern const Dem_ExternalSRDataElementClassType Dem_ExternalSRDataElementClassTab[];
extern const Dem_DTCClassType DemDTCClassSet[];
extern const Dem_ExtendedDataClassType DemExtendedDataClassTab0[];
extern const Dem_InternalDataElementClassType DemInternalDataElementClassTab[];

#endif

