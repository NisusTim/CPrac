/*
 * SPI_TJA1145.c
 *
 *  Created on: 2018¦~6¤ë13¤é
 *      Author: user
 */

#include "derivative.h" /* include peripheral declarations */
#include <stdbool.h>
#include "TJA1145/SPI_TJA1145.h"

// ---------------------------------------------------------------
// ------------  SPI Definitions ---------------------------------
// ---------------------------------------------------------------
//#define SPI_DEBUG
// I/O defines
#define MSCR_OUTPUT				 0x12840000  // Full drive slew rate, Output enabled, don't disable safe mode, Input hysteresis
#define MSCR_INPUT       		 0x008C0000  // Input buffer enabled, Input hysteresis

// SPI Chip select, Output
#define SPI_1_CS2_MSCR_NB        56
#define SPI_1_CS2_MSCR_SSS       1
// SPI Serial data out, Output
#define SPI_1_SOUT_MSCR_NB       9
#define SPI_1_SOUT_MSCR_SSS      4
// SPI Clock, Output
#define SPI_1_CLK_MSCR_NB        18
#define SPI_1_CLK_MSCR_SSS       4
// SPI Serial data in, Input
#define SPI_1_SIN_MSCR_NB        19
#define SPI_1_SIN_IMCR_NB        6
#define SPI_1_SIN_IMCR_SSS       2

#define NULL (0)
/**********************************************************************************************
SPI ENUMERATIONS
**********************************************************************************************/

typedef enum spi_num
{
    SPIDUMMY,
    SPI1,
    SPI2
}spi_num_t;

typedef enum spi_baudrate
{
    MBITS20,
    MBITS10,
    MBITS6_6,
    MBITS5,
    MBITS2_5,
    MBITS1_25,
	MBITS0_625,
	MBITS0_3125,
	MBITS0_15625
}spi_baudrate_t;

typedef enum spi_state
{
	SPI_DISABLE,
    SPI_ENABLE
}spi_state_t;



/**********************************************************************************************
 Global Variables
**********************************************************************************************/

volatile static struct SPI_tag* SPI_TJA1145 =(volatile struct SPI_tag*) &SPI_1;
/** -------------------------------------------------------------------------------------------
 @brief    Configures chosen SPI module for communication with Dolphin

 @param    spi_num_t spi_num - The SPI module to configure
           spi_baudrate_t baud_rate - The chosen Baud rate (Dolphin supports up to 40Mbps)
           state_t mtfe - Whether to use a modified timing format (MTFE)

 @return   retval_t success - Indicator of success or failure
---------------------------------------------------------------------------------------------*/
static void SPI_TJA1145_cfg(spi_num_t spi_num, spi_baudrate_t baud_rate, spi_state_t mtfe)
{
    // pin setup
    if (spi_num == 1){
        SIUL2.MSCR[SPI_1_CLK_MSCR_NB].R = MSCR_OUTPUT | SPI_1_CLK_MSCR_SSS;                           // PA11/F15: configure SPI2-SCK  -> PA11 on MPC57xx Motherboard
        SIUL2.MSCR[SPI_1_SOUT_MSCR_NB].R = MSCR_OUTPUT | SPI_1_SOUT_MSCR_SSS;                   // PA12/B16: configure SPI2-SOUT -> PA12 on MPC57xx Motherboard
        SIUL2.MSCR[SPI_1_SIN_MSCR_NB].R = MSCR_INPUT;                  // PA13/D17: configure SPI2-SIN  -> PA13 on MPC57XX Motherboard
        SIUL2.IMCR[SPI_1_SIN_IMCR_NB].R  = 0x00000000 | SPI_1_SIN_IMCR_SSS;                       //
        SIUL2.MSCR[SPI_1_CS2_MSCR_NB].R = MSCR_OUTPUT | SPI_1_CS2_MSCR_SSS;                           // PA10/C16: configure SPI2-CS0  -> PA10 on MPC57xx Motherboard
    } else {
                //return INVALID_PARAMETER;                                    // if SPI number not 1 or 2 return error
    }

    // Check if protocol clock is 80 MHz. If not then SPI_CLK has not been correctly configured in CGM
    if(CGM.AC12_DC0.R != 0x80020000) //return SPI_CLOCK_ERROR;
		CGM.AC12_DC0.R = 0x80020000;

    // MCR initialization:
    //SPI->MCR.R = 0x80FF0E01 | (mtfe << 26);
    SPI_TJA1145->MCR.B.MSTR = 1;          // Enable Master mode
    SPI_TJA1145->MCR.B.CONT_SCKE = 0;     // continuous clock
    SPI_TJA1145->MCR.B.DCONF = 0;         // SPI
    SPI_TJA1145->MCR.B.FRZ = 0;           // Do not halt in debug mode
    SPI_TJA1145->MCR.B.MTFE = mtfe;       // Modified transfer format
    SPI_TJA1145->MCR.B.PCSSE = 1;         // Use PCS5 as chip select
    SPI_TJA1145->MCR.B.ROOE = 0;          // Receive FIFO overflow -> ignore incoming data
    SPI_TJA1145->MCR.B.PCSIS = 0xFF;      // PCS inactive state is high
    SPI_TJA1145->MCR.B.DIS_TXF = 1;       // Disable TX FIFO
    SPI_TJA1145->MCR.B.DIS_RXF = 1;       // Disable RX FIFO
    SPI_TJA1145->MCR.B.CLR_TXF = 1;       // Clear TX FIFO
    SPI_TJA1145->MCR.B.CLR_RXF = 1;       // Clear RX FIFO
    SPI_TJA1145->MCR.B.SMPL_PT = 2;       // 2 fp clock cycles between SCK and SIN (MTFE only!)
    SPI_TJA1145->MCR.B.PES = 0;           // Don't stop on parity error
    SPI_TJA1145->MCR.B.HALT = 1;          // Keep HALT=1 (stop transfers)
    SPI_TJA1145->MCR.B.MDIS = 0;          // Enable module
    /* CTAR0 initialization used for 8 bit data transfers
     * no double baudrate, frame size 8-bits, SCK polarity is high, data is changed on leading (falling edge) and captured on following (rising) edge (CPOL = CPHA = 1), MSB first,
     * PCS to SCK delay is 2, after SCK delay is 4, delay after transfer is 64, baudrate depends on function argument
     */
    //SPI->MODE.CTAR[0].R = 0x3E000150 | baud_rate;

    SPI_TJA1145->MODE.CTAR[2].B.DBR = 0;                 // No double baud rate
    SPI_TJA1145->MODE.CTAR[2].B.FMSZ = 7;                // Frame size = 8-bits
    SPI_TJA1145->MODE.CTAR[2].B.CPOL = 0;                // Inactive state of SCK is high
    SPI_TJA1145->MODE.CTAR[2].B.CPHA = 1;                // Data is changed on the leading edge and captured on the following edge
    SPI_TJA1145->MODE.CTAR[2].B.LSBFE = 0;               // MSB transmitted first
    SPI_TJA1145->MODE.CTAR[2].B.PCSSCK = 0;              // PCS to SCK delay prescaler = 1
    SPI_TJA1145->MODE.CTAR[2].B.PASC = 0;                // After SCK delay prescaler = 1
    SPI_TJA1145->MODE.CTAR[2].B.PDT = 0;                 // Delay after transfer prescaler = 1
    SPI_TJA1145->MODE.CTAR[2].B.PBR = 0;                 // Baud rate prescaler = 2
    SPI_TJA1145->MODE.CTAR[2].B.CSSCK = 0;               // PCS to SCK delay scaler = 2
    SPI_TJA1145->MODE.CTAR[2].B.ASC = 1;                 // After SCK delay scaler = 4
    SPI_TJA1145->MODE.CTAR[2].B.DT = 5;                  // Delay after transfer delay scaler = 64
    SPI_TJA1145->MODE.CTAR[2].B.BR = baud_rate; 		 // Baude rate scaler
    SPI_TJA1145->SR.R = 0xFFFFFFFF;                      // clear all flags
    SPI_TJA1145->MCR.B.HALT = 0;                         // start transfers

    //return SUCCESS;
}

void SPI_TJA1145_init(void)
{
	 SPI_TJA1145_cfg(SPI1, MBITS0_625, SPI_DISABLE);
}

HAL_SPI_StateTypeDef HAL_SPI_TransmitReceive(uint8_t *pTxData,uint8_t *pRxData,uint16_t Size,uint32_t Timeout)
{
	HAL_SPI_StateTypeDef errorcode = HAL_SPI_STATE_OK;
	uint32_t timeout = Timeout;
	uint32_t tx_action;
	uint8_t end_size = Size-1;
	uint32_t receive_data;
	uint8_t cnt;
    // Since SPI is shared resource between ISR and main thread, below
    // block is considered as critical section, and locked to avoid Race-Conditions.
    // Disable the interrupt pins by
    // setting the appropriate EIREn bits in DIRER0
    SIUL2.DIRER0.B.EIRE0 = 0x00;

    SPI_TJA1145->MCR.B.CLR_RXF = 1;             // Clear Rx FIFO
    SPI_TJA1145->MCR.B.CLR_TXF = 1;             // Clear Tx FIFO
    SPI_TJA1145->SR.R = 0xFFFFFFFF;             // Clear all flags

    if((pTxData == NULL) || (pRxData == NULL) || (Size == 0))
    {
      errorcode = HAL_SPI_STATE_ERROR;
      goto error;
    }

    for(cnt=0;cnt<Size;cnt++)
    {

    	if(0 == cnt)
    		tx_action = 0xA4040000;//keep PCSn signals,CTAR2,not last data,clear tx counter
    	else if(end_size == cnt)
			tx_action = 0x28040000;//inactive PCSn signals,CTAR2,last data,not clear tx counter
    	else
    		tx_action = 0xA0040000;//keep PCSn signals,CTAR2,not last data,not clear tx counter

    	SPI_TJA1145->PUSHR.PUSHR.R = (tx_action | (*(pTxData + cnt)));

        while((!SPI_TJA1145->SR.B.RFDF || !SPI_TJA1145->SR.B.TCF) && timeout > 0)
        {
        	timeout--;
        }
        receive_data = SPI_TJA1145->POPR.R;
        *(pRxData + cnt) = (uint8_t)(receive_data & 0x000000FF);
        SPI_TJA1145->SR.B.TCF = 1;
        SPI_TJA1145->SR.B.RFDF = 1;
        if(0 == timeout)
		{
			goto error;
		}
        timeout = Timeout;

    }

	SIUL2.DIRER0.B.EIRE0 = 0x01;
    return HAL_SPI_STATE_OK;
    error:
		SIUL2.DIRER0.B.EIRE0 = 0x01;
	return errorcode;
}
