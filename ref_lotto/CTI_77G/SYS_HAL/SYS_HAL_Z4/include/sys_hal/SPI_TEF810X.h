#ifndef SPI_TEF810X_H
#define SPI_TEF810X_H

//#include "project.h"
#include "typedefs.h"
#include "S32R274.h"
#include "event.h"

void SPI_init(void);
//retval_t SPI_TEF810X_cfg(spi_num_t spi_num, spi_baudrate_t baud_rate, state_t mtfe);
retval_e SPI_TEF810X_txrx(uint32_t mod_addr, uint32_t cmd, uint32_t reg_addr, uint32_t * tx_buff, uint32_t * rx_buff, uint32_t len, uint32_t * ret_cmd );
retval_e SPI_TEF810X_xferFifoMode(uint8_t mod_addr, uint32_t cmd, uint16_t reg_addr, uint32_t * tx_buff, uint32_t * rx_buff, uint8_t len, uint32_t * ret_cmd );

#endif // SPI_TEF810X_H
