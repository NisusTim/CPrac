/*
 * SPI_TJA1145.h
 *
 *  Created on: 2018¦~6¤ë14¤é
 *      Author: user
 */

#ifndef TJA1145_SPI_TJA1145_H_
#define TJA1145_SPI_TJA1145_H_
#include "derivative.h" /* include peripheral declarations */
typedef enum
{
  HAL_SPI_STATE_OK      = 0x00,
  HAL_SPI_STATE_ERROR      = 0x01
}HAL_SPI_StateTypeDef;


extern void SPI_TJA1145_init(void);
extern void DSPI_TJA1145_Init(uint8_t DspiNumber,uint8_t mode, uint32_t sysClk, uint32_t baudRate, uint32_t intMask);
#endif /* TJA1145_SPI_TJA1145_H_ */
