/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can transceiver.
 *
 *  \file       bl_can_transceiver.c
 *  \ingroup    driver_module
 *  \author     sijia.hao <sijia.hao@hirain.com>
 *
 *  \version    1.2.0
 *  \date       05/08/2013
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 17/03/2010 | he.yang          | N/A | BootDrv010001
 *      01.01.00 | 21/02/2011 | ning.chen        | N/A | BootDrv010002
 *      01.02.00 | 05/08/2013 | sijia.hao        | N/A | BootDrv010003
 *
 *****************************************************************************/

#include "bl_can_transceiver.h"
#include "bl_can_if_funcfg.h"
#include "S32R274.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 277,303,602,781,1532,2100,2103,3112,3227,3453,4130 EOF*/
/*
 * 277:An integer constant expression with negative value is being converted
 * to an unsigned type.
 *
 * MISRA-C:2004 11.3(303):Cast a pointer to an integral type.
 * To address a register must cast an integral type to a pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect. 
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 *
 * MISRA-C:2004 12.7(4130):Bitwise operations on signed data will give
 * implementation defined results.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
void ioctrl_init()
{
	/*Initial CAN 0 I/O Settings*/
	SIUL2.MSCR[16].B.SSS = 1;    /* Pad L15: Source signal is CAN0_TX */
	SIUL2.MSCR[16].B.OBE = 1;    /* Pad L15: Output Buffer Enable */
	SIUL2.MSCR[16].B.SRC = 3;    /* Pad L15: Maximum slew rate */

	SIUL2.MSCR[15].B.IBE = 1;    /* Pad L16: Enable pad for input - CAN0_RXD */
	SIUL2.IMCR[0].B.SSS = 1;     /* Pad L16: Source signal is CAN0_RXD */

	/*Initial CAN 2 I/O Settings*/
	SIUL2.MSCR[0].B.SSS = 0;    /* Pad A11: Source signal is DSP_CAN2_STB,GPO*/
	SIUL2.MSCR[0].B.OBE = 1;    /* Pad A11: Output Buffer Enable */
	SIUL2.MSCR[0].B.SRC = 3;    /* Pad A11: Slew Rate Control => Full drive strength without slew rate control */
	SIUL2.GPDO[0].B.PDO_4n = 0;	/* Set CAN2 Transceiver to Normal mode ( output low ) */

	SIUL2.MSCR[133].B.SSS = 1;
	SIUL2.MSCR[133].B.OBE = 1;
	SIUL2.MSCR[133].B.SRC = 3;

	SIUL2.IMCR[2].B.SSS = 3;
	SIUL2.MSCR[134].B.IBE = 1;
}
#if (CANIF_FUN_INIT_TRANSCEIVER == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Initialize can transceiver.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
void Cantrc_InitTransceiver(void)
{
    /*Can1 STB PA1*/
	ioctrl_init();
	TJA1145_init();
    return ; 
}
#endif

