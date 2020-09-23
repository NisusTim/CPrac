/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of the ram module.
 *
 *  \file       bl_ram.h
 *  \ingroup    ram_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    2.0.0
 *  \date       25/09/2012
 *
 *  \par        Changelist
 *      Version  | Date       | Authors    | CR# | Descriptions
 *      -------- | ---------- | ---------- | --- | ------------
 *      02.00.00 | 25/09/2012 | xin.shang  | N/A | Boot020001
 *
 *****************************************************************************/
#ifndef _BL_RAM_H_
#define _BL_RAM_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
/** \brief This function is used to write ram memory.*/
extern bl_Return_t Ram_Write(bl_Address_t addr,
                             bl_Size_t size,
                             const bl_Buffer_t *buffer);
/** \brief This function is used to read ram memory.*/
extern bl_Return_t Ram_Read(bl_Address_t addr,
                            bl_Size_t size,
                            bl_Buffer_t *buffer);

#endif

