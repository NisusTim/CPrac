/*
 * SPI_TJA1145.h
 *
 *  Created on: 2018¦~6¤ë14¤é
 *      Author: user
 */

#ifndef TJA1145_SPI_TJA1145_H_
#define TJA1145_SPI_TJA1145_H_
#include "sys_shared.h"

//#define TJA1145_DBG	1

#ifdef TJA1145_DBG
	#define TJADBG(...) 	PRINTF(__VA_ARGS__)
#else
	#define TJADBG(...)
#endif

typedef enum
{
  HAL_SPI_STATE_OK      = 0x00,
  HAL_SPI_STATE_ERROR      = 0x01
}HAL_SPI_StateTypeDef;


extern void SPI_TJA1145_init(void);
extern void DSPI_TJA1145_Init(uint8_t DspiNumber,uint8_t mode, uint32_t sysClk, uint32_t baudRate, uint32_t intMask);
extern HAL_SPI_StateTypeDef HAL_SPI_TransmitReceive(uint8_t *pTxData,uint8_t *pRxData,uint16_t Size,uint32_t Timeout);
#endif /* TJA1145_SPI_TJA1145_H_ */
