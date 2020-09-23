/*
 * bl_access_udsfaw.h
 *
 *  Created on: 2019/10/12/
 *      Author: WoodLiu
 */

#ifndef INC_BL_ACCESS_UDSFAW_H_
#define INC_BL_ACCESS_UDSFAW_H_

#include "bl_typedefs.h"
/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 */

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
/** \brief Initialize the demo algorithm used by UDS.*/
extern void Acc_UdsFawInit(void);
/** \brief Make a new seed.*/
extern void Acc_UdsFawMakeNewSeed(void);
/** \brief Get current seed value.*/
extern void Acc_UdsFawGetSeed(bl_Buffer_t *seed);
/** \brief Verify the transmitted key whether is right.*/
extern bl_Return_t Acc_UdsFawVerifyKey(const bl_Buffer_t *key);

#endif /* INC_BL_ACCESS_UDSFAW_H_ */
