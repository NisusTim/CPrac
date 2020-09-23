/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dem_LCfg.c
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

/*******************************************************************************
*   Include files
*******************************************************************************/
#include "Dem_Cfg.h"
#include "Dem_Types.h"
#include "Dem_Lcfg.h"
#include "Dem_Cbk.h"
#include "typedefs.h"
/* -----------------------------------------------------------------------------
  Container Name : DemDTCClass
  This container contains the configuration (parameters) for DTCClass.
----------------------------------------------------------------------------- */
const Dem_DTCClassType DemDTCClassSet[DEM_NUMBER_OF_DTC] =
{

    {0xC07688,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Communication Bus Off*/
	{0xC23A87,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Lost Communication with Camera*/
    {0x950098,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU temperature too high*/
	{0x95009A,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU temperature too low*/
	{0x9500A3,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU voltage too high*/
	{0x9500A2,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU voltage too low*/
	{0x9501A3,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF voltage1 too high*/
    {0x9501A2,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF voltage1 too low*/
	{0x9502A3,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF voltage2 too high*/
	{0x9502A2,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF voltage2 too low*/
	{0x911717,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Battery voltage too high*/
	{0x911716,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Battery voltage too low*/
	{0x950198,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF temperature too high*/
    {0x95019A,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF temperature too low*/
	{0x950049,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU Master Clock Error*/
	{0x950045,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU Error*/
	{0x950044,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*MCU Memory Error*/
	{0x950096,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*G-sensor fault*/
	{0x950196,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*RF sensor fault*/
	{0x950054,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Missing calibration*/
  {0x950154,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Radar mount position shift error*/
	{0x950081,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Invalid Vehicle Speed signal*/
	{0x950181,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Invalid Yaw Rate signal*/
	{0x950281,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Invalid Steering Angle signal*/
	{0x950381,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Invalid Gear position signal*/
	{0x950481,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR},/*Invalid IGN Sta signal*/
	{0x950097,0,DEM_DTC_SEV_NO_SEVERITY,FALSE,NULL_PTR}/*Radar block*/
};

const Dem_EventParameterType DemEventParameterTab[DEM_NUMBER_OF_EVENT] =
{
    {DEM_EVENT_KIND_SWC,0,0,0,0},
    {DEM_EVENT_KIND_SWC,0,1,0,0},
    {DEM_EVENT_KIND_SWC,0,2,0,0},
    {DEM_EVENT_KIND_SWC,0,3,0,0},
    {DEM_EVENT_KIND_SWC,0,4,0,0},
    {DEM_EVENT_KIND_SWC,0,5,0,0},
    {DEM_EVENT_KIND_SWC,0,6,0,0},
    {DEM_EVENT_KIND_SWC,0,7,0,0},
    {DEM_EVENT_KIND_SWC,0,8,0,0},
    {DEM_EVENT_KIND_SWC,0,9,0,0},
    {DEM_EVENT_KIND_SWC,0,10,0,0},
    {DEM_EVENT_KIND_SWC,0,11,0,0},
    {DEM_EVENT_KIND_SWC,0,12,0,0},
    {DEM_EVENT_KIND_SWC,0,13,0,0},
    {DEM_EVENT_KIND_SWC,0,14,0,0},
    {DEM_EVENT_KIND_SWC,0,15,0,0},
    {DEM_EVENT_KIND_SWC,0,16,0,0},
    {DEM_EVENT_KIND_SWC,0,17,0,0},
	{DEM_EVENT_KIND_SWC,0,18,0,0},
	{DEM_EVENT_KIND_SWC,0,19,0,0},
	{DEM_EVENT_KIND_SWC,0,20,0,0},
	{DEM_EVENT_KIND_SWC,0,21,0,0},
	{DEM_EVENT_KIND_SWC,0,22,0,0},
	{DEM_EVENT_KIND_SWC,0,23,0,0},
	{DEM_EVENT_KIND_SWC,0,24,0,0},
	{DEM_EVENT_KIND_SWC,0,25,0,0},
  {DEM_EVENT_KIND_SWC,0,26,0,0}
};

const Dem_EventClassType  DemEventClassSet[DEM_NUMBER_OF_EVENT]=
{
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0},
   {TRUE,40,FALSE,DEM_DTC_ORIGIN_PRIMARY_MEMORY,1,1,DEM_EVENT_SIGNIFICANCE_FAULT,FALSE,DEM_OPCYC_IGNITION,0,DEM_OPCYC_IGNITION,DEM_OPCYC_IGNITION,0}
};

void Dem_GetInternalDataElementFun
(
    Dem_InternalDataElementType InteElemType,uint8* Buffer
)
{

}

union
{
    uint8  _c[4];
    uint32 Example0;
}DemExternalSRDemo;
/********************All DataElementClass def**********************************/
const Dem_InternalDataElementClassType DemInternalDataElementClassTab[] =
{
    {1,DEM_OCCCTR},
    {1,DEM_PENDINFCTR},
    {1,DEM_AGEDCTR},
    {1,DEM_AGINGCTR},
};

const Dem_ExternalCSDataElementClassType Dem_ExternalCSDataElementClassTab[]=
{
    {1,Dem_ReadDataElementFun_0x0}
};

const Dem_ExternalSRDataElementClassType Dem_ExternalSRDataElementClassTab[]=
{
    {4,DemExternalSRDemo._c}
};

/***************FF*******************/
const Dem_DidClassType DemDidClassTab0[]=
{
    {0x0,DemExternalCS,0}
};
const Dem_FreezeFrameRecNumClassType DemFreezeFrameRecNumClassTab0[] =
{
    {1 ,1,&DemDidClassTab0[0]}
};

const Dem_FreezeFrameClassType DemFreezeFrameClassTab0[] =
{
    {1,&DemFreezeFrameRecNumClassTab0[0]}
};
/************extended data**************/
const Dem_ExtendedDataElementType DemExtendedDataElemen0[]=
{
    {DemInternal,0},
    {DemInternal,1},
    {DemInternal,2},
    {DemInternal,3},
};
/*
const Dem_ExtendedDataElementType DemExtendedDataElemen1[2]=
{
    {DemExternalCS,14},
    {DemExternalCS,15},
};
*/
const Dem_ExtendedDataRecordClassType DemExtendedDataRecordClassTab0[] =
{
    {1,DEM_UPDATE_RECORD_YES,4,&DemExtendedDataElemen0[0]},
    /*{2,DEM_UPDATE_RECORD_YES,2,&DemExtendedDataElemen1[0]}*/
};
const Dem_ExtendedDataClassType DemExtendedDataClassTab0[]=
{
    {1,&DemExtendedDataRecordClassTab0[0]}
};
/**********Dem_DebounceAlgorithmClassType*******/

const Dem_DebounceAlgorithmClassType DemDebounceAlgorithmClassTab[DEM_NUMBER_OF_EVENT] =
{
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
    {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
  {{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}},
	{{-3,5,-30,30,TRUE,TRUE,0,0},{3000,3000},{NULL_PTR},{0}}
};




