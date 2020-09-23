/*
 * sbc_fs8x_spi.h
 *
 *  Created on: 2018¦~7¤ë26¤é
 *      Author: user
 */

#ifndef FS8X_SBC_FS8X_SPI_H_
#define FS8X_SBC_FS8X_SPI_H_

//#define FS8X_DBG	1

#ifdef FS8X_DBG
	#define FS8xDBG(...) 	PRINTF(__VA_ARGS__)
#else
	#define FS8xDBG(...)
#endif

void fs8x_spi_init(void);

#endif /* FS8X_SBC_FS8X_SPI_H_ */
