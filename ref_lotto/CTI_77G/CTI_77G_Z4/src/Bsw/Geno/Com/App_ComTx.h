/*
 * App_ComTx.h
 *
 *  Created on: 2020/03/18
 *      Author: Cubtek
 */

#ifndef _APP_COMTX_H_
#define _APP_COMTX_H_

#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Std_Types.h"
#include "Com_cfg.h"

extern FUNC(void, COM_PUBLIC_CODE) App_ComTx_Init
(
	void
);

extern FUNC(Std_ReturnType, COM_PUBLIC_CODE) App_ComTx_RmtpData_Transmit
(
	uint64 Data
);

extern FUNC(Std_ReturnType, COM_PUBLIC_CODE) App_ComTx_IpduData_Transmit
(
	uint32 Id,
	uint64 Data
);

extern FUNC(void, COM_PUBLIC_CODE) App_ComTx_Confirmation
(
	PduIdType PduId
);

#endif /* _APP_COMTX_H_ */
