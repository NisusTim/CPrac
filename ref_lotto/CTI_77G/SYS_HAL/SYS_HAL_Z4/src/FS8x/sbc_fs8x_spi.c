/*
 * sbc_fs8x_spi.c
 *
 *  Created on: 2018¦~7¤ë26¤é
 *      Author: user
 */


/**********************************************************************************************
@file       SPI_TEF810X.c
@author     nxa07096
@date       8 Jul 2016

===============================================================================================
REVISION HISTORY
===============================================================================================
REV    AUTHOR      DATE          COMMENT
1.0    nxa07096      8 Jul 2017     Initial version for TEF8102 bring-up
**********************************************************************************************/

/**********************************************************************************************
 Includes
**********************************************************************************************/

//#include <stddef.h>
#include <stdbool.h>
//#include <string.h>
//#include "SPI_TEF810X.h"
#include "sys_shared.h"
#include "sbc_fs8x_common.h"
#include "sbc_fs8x_spi.h"
#define  SPI_TIME_OUT  6000
// ---------------------------------------------------------------
// ------------  SPI Definitions ---------------------------------
// ---------------------------------------------------------------
//#define SPI_DEBUG
// I/O defines
#define MSCR_OUTPUT				 0x12840000  // Full drive slew rate, Output enabled, don't disable safe mode, Input hysteresis
#define MSCR_INPUT       		 0x008C0000  // Input buffer enabled, Input hysteresis

// SPI Chip select, Output
#define SPI_1_CS0_MSCR_NB        5
#define SPI_1_CS0_MSCR_SSS       1
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

// SPI Chip select, Output
#define SPI_2_CS3_MSCR_NB        44
#define SPI_2_CS3_MSCR_SSS       2
// SPI Serial data out, Output
#define SPI_2_SOUT_MSCR_NB       12
#define SPI_2_SOUT_MSCR_SSS      1
// SPI Clock, Output
#define SPI_2_CLK_MSCR_NB        11
#define SPI_2_CLK_MSCR_SSS       1
// SPI Serial data in, Input
#define SPI_2_SIN_MSCR_NB        13
#define SPI_2_SIN_IMCR_NB        9
#define SPI_2_SIN_IMCR_SSS       2

static uint8_t cs_number = 0;
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
    MBITS1_25
}spi_baudrate_t;

typedef enum spi_state
{
	SPI_DISABLE,
    SPI_ENABLE
}spi_state_t;

/**********************************************************************************************
 Global Variables
**********************************************************************************************/
volatile static struct SPI_tag* SPI_fs8x =(volatile struct SPI_tag*) &SPI_1;
HW_VER_E hw_ver;

/** -------------------------------------------------------------------------------------------
 @brief    Configures chosen SPI module for communication with Dolphin

 @param    spi_num_t spi_num - The SPI module to configure
           spi_baudrate_t baud_rate - The chosen Baud rate (Dolphin supports up to 40Mbps)
           state_t mtfe - Whether to use a modified timing format (MTFE)

 @return   retval_t success - Indicator of success or failure
---------------------------------------------------------------------------------------------*/
static void spi_fs8x_cfg(spi_num_t spi_num, spi_baudrate_t baud_rate, spi_state_t mtfe)
{
    // pin setup
    if (spi_num == 1){
    	SPI_fs8x =(volatile struct SPI_tag*) &SPI_1;
    	cs_number = 0;

    	SIUL2.MSCR[SPI_1_CLK_MSCR_NB].R = MSCR_OUTPUT | SPI_1_CLK_MSCR_SSS;		// PA11/F15: configure SPI2-SCK  -> PA11 on MPC57xx Motherboard
    	SIUL2.MSCR[SPI_1_SOUT_MSCR_NB].R = MSCR_OUTPUT | SPI_1_SOUT_MSCR_SSS;	// PA12/B16: configure SPI2-SOUT -> PA12 on MPC57xx Motherboard
    	SIUL2.MSCR[SPI_1_SIN_MSCR_NB].R = MSCR_INPUT;							// PA13/D17: configure SPI2-SIN  -> PA13 on MPC57XX Motherboard
    	SIUL2.IMCR[SPI_1_SIN_IMCR_NB].R  = 0x00000000 | SPI_1_SIN_IMCR_SSS;		//
    	SIUL2.MSCR[SPI_1_CS0_MSCR_NB].R = MSCR_OUTPUT | SPI_1_CS0_MSCR_SSS;		// PA10/C16: configure SPI2-CS0  -> PA10 on MPC57xx Motherboard
    } else if (spi_num == 2) {
    	SPI_fs8x =(volatile struct SPI_tag*) &SPI_2;
    	cs_number = 3;

    	SIUL2.MSCR[SPI_2_CLK_MSCR_NB].R = MSCR_OUTPUT | SPI_2_CLK_MSCR_SSS;		// PA11/F15: configure SPI2-SCK  -> PA11 on MPC57xx Motherboard
    	SIUL2.MSCR[SPI_2_SOUT_MSCR_NB].R = MSCR_OUTPUT | SPI_2_SOUT_MSCR_SSS;	// PA12/B16: configure SPI2-SOUT -> PA12 on MPC57xx Motherboard
    	SIUL2.MSCR[SPI_2_SIN_MSCR_NB].R = MSCR_INPUT;							// PA13/D17: configure SPI2-SIN  -> PA13 on MPC57XX Motherboard
    	SIUL2.IMCR[SPI_2_SIN_IMCR_NB].R  = 0x00000000 | SPI_2_SIN_IMCR_SSS;		//
    	SIUL2.MSCR[SPI_2_CS3_MSCR_NB].R = MSCR_OUTPUT | SPI_2_CS3_MSCR_SSS;		// PA10/C16: configure SPI2-CS0  -> PA10 on MPC57xx Motherboard
    } else {
                //return INVALID_PARAMETER;                                    // if SPI number not 1 or 2 return error
    }

    // Check if protocol clock is 80 MHz. If not then SPI_CLK has not been correctly configured in CGM
    if(CGM.AC12_DC0.R != 0x80020000) //return SPI_CLOCK_ERROR;
		CGM.AC12_DC0.R = 0x80020000;

    // MCR initialization:
    //SPI->MCR.R = 0x80FF0E01 | (mtfe << 26);
    SPI_fs8x->MCR.B.MSTR = 1;          // Enable Master mode
    SPI_fs8x->MCR.B.CONT_SCKE = 0;     // No continuous clock
    SPI_fs8x->MCR.B.DCONF = 1;         // SPI
    SPI_fs8x->MCR.B.FRZ = 0;           // Do not halt in debug mode
    SPI_fs8x->MCR.B.MTFE = mtfe;       // Modified transfer format
    SPI_fs8x->MCR.B.PCSSE = 0;         // Use PCS5 as chip select
    SPI_fs8x->MCR.B.ROOE = 0;          // Receive FIFO overflow -> ignore incoming data
    SPI_fs8x->MCR.B.PCSIS = 0xFF;      // PCS inactive state is high
    SPI_fs8x->MCR.B.DIS_TXF = 0;       // Enable TX FIFO
    SPI_fs8x->MCR.B.DIS_RXF = 0;       // Enable RX FIFO
    SPI_fs8x->MCR.B.CLR_TXF = 1;       // Clear TX FIFO
    SPI_fs8x->MCR.B.CLR_RXF = 1;       // Clear RX FIFO
    SPI_fs8x->MCR.B.SMPL_PT = 2;       // 2 fp clock cycles between SCK and SIN (MTFE only!)
    SPI_fs8x->MCR.B.PES = 0;           // Don't stop on parity error
    SPI_fs8x->MCR.B.HALT = 1;          // Keep HALT=1 (stop transfers)
    SPI_fs8x->MCR.B.MDIS = 0;          // Enable module

    /* CTAR0 initialization used for 8 bit data transfers
     * no double baudrate, frame size 8-bits, SCK polarity is high, data is changed on leading (falling edge) and captured on following (rising) edge (CPOL = CPHA = 1), MSB first,
     * PCS to SCK delay is 2, after SCK delay is 4, delay after transfer is 64, baudrate depends on function argument
     */
    //SPI->MODE.CTAR[0].R = 0x3E000150 | baud_rate;

    SPI_fs8x->MODE.CTAR[1].B.DBR = 0;                 // No double baud rate
    SPI_fs8x->MODE.CTAR[1].B.FMSZ = 7;                // Frame size = 8-bits
    SPI_fs8x->MODE.CTAR[1].B.CPOL = 0;                // Inactive state of SCK is low
    SPI_fs8x->MODE.CTAR[1].B.CPHA = 1;                // Data is changed on the leading edge and captured on the following edge
    SPI_fs8x->MODE.CTAR[1].B.LSBFE = 0;               // MSB transmitted first
    SPI_fs8x->MODE.CTAR[1].B.PCSSCK = 0;              // PCS to SCK delay prescaler = 1
    SPI_fs8x->MODE.CTAR[1].B.PASC = 0;                // After SCK delay prescaler = 1
    SPI_fs8x->MODE.CTAR[1].B.PDT = 0;                 // Delay after transfer prescaler = 1
    SPI_fs8x->MODE.CTAR[1].B.PBR = 0;                 // Baud rate prescaler = 2
    SPI_fs8x->MODE.CTAR[1].B.CSSCK = 0;               // PCS to SCK delay scaler = 2
    SPI_fs8x->MODE.CTAR[1].B.ASC = 1;                 // After SCK delay scaler = 4
    SPI_fs8x->MODE.CTAR[1].B.DT = 5;                  // Delay after transfer delay scaler = 64
    SPI_fs8x->MODE.CTAR[1].B.BR = baud_rate; 		 // Baude rate scaler

    SPI_fs8x->SR.R = 0xFFFFFFFF;                      // clear all flags
    SPI_fs8x->MCR.B.HALT = 0;                         // start transfers

    //return SUCCESS;
}



void fs8x_spi_init(void)
{
	hw_ver = get_hw_ver();

	if(hw_ver == HW_93G003_COMBO_FRONT_RADAR_BV3p3
	        || hw_ver == HW_93G003_COMBO_FRONT_RADAR_BV3p4
	        || hw_ver == HW_93G014_MRR_BV1p0_FOR_HIRAIN
	        || hw_ver == HW_93G014_MRR_BV2p1_FOR_HIRAIN
	        || hw_ver == HW_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264)
		spi_fs8x_cfg(SPI1, MBITS5, SPI_DISABLE);
	else
		spi_fs8x_cfg(SPI2, MBITS5, SPI_DISABLE);
}




/** @brief This function transfers single frame through blocking SPI communication
 *         in both directions. MCU specific.
 *
 * This function must be implemented if SPI communication is used. The txFrame must be
 * sent to the SPI bus from the last byte to the first (e.g. txFrame[0] will be sent
 * last). The FS8x driver expects incoming data in reversed order, e.g. rxFrame[0] = CRC,
 * rxFrame[1] = LSB ...
 * @warning This function must be implemented as blocking as there is not synchronization
 * mechanism implemented in the driver.
 * @param [in]  txFrame             Frame to be send.
 * @param [in]  frameLengthBytes    Bytes Length of the frame in bytes.
 * @param [out] rxFrame             Received frame.
 * @return @ref fs8x_status_t "Status return code." */
//extern fs8x_status_t MCU_SPI_TransferData(uint8_t* txFrame, uint16_t frameLengthBytes, uint8_t* rxFrame);
fs8x_status_t MCU_SPI_TransferData(uint8_t* txFrame, uint16_t frameLengthBytes, uint8_t* rxFrame)
{
	fs8x_status_t errorcode = fs8xStatusError;
	uint32_t timeout = SPI_TIME_OUT;
	uint32_t tx_action;
	uint16_t end_size = frameLengthBytes-1;
	uint32_t receive_data;

    // Since SPI is shared resource between ISR and main thread, below
    // block is considered as critical section, and locked to avoid Race-Conditions.
    // Disable the interrupt pins by
    // setting the appropriate EIREn bits in DIRER0
    SIUL2.DIRER0.B.EIRE0 = 0x00;

    SPI_fs8x->MCR.B.CLR_RXF = 1;             // Clear Rx FIFO
    SPI_fs8x->MCR.B.CLR_TXF = 1;             // Clear Tx FIFO
    SPI_fs8x->SR.R = 0xFFFFFFFF;             // Clear all flags

    if((txFrame == NULL) || (rxFrame == NULL) || (frameLengthBytes == 0))
    {
      errorcode = fs8xStatusError;
      FS8xDBG("SPI buffer or size error,size = %d\n",frameLengthBytes);
      goto error;
    }

    for(uint16_t cnt=0;cnt<frameLengthBytes;cnt++)
    {

		if(0 == cnt)
			tx_action = (0x94000000 |(1<< (cs_number+16)));//keep PCSn signals,CTAR1,not last data,clear tx counter
		else if(end_size == cnt)
			tx_action = (0x18000000|(1<< (cs_number+16)));//inactive PCSn signals,CTAR1,last data,not clear tx counter
		else
			tx_action = (0x90000000|(1<< (cs_number+16)));//keep PCSn signals,CTAR1,not last data,not clear tx counter

    	SPI_fs8x->PUSHR.PUSHR.R = (tx_action | (*(txFrame + end_size - cnt)));

    	FS8xDBG("SPI tx ====================\n",cnt);
    	FS8xDBG("SPI tx size = %d \n",cnt);
    	FS8xDBG("SPI tx data = %02x , complete tx = %08x\n",*(txFrame  + end_size -  cnt) , (tx_action | (*(txFrame + end_size - cnt))));
        while((!SPI_fs8x->SR.B.RFDF || !SPI_fs8x->SR.B.TCF) && timeout > 0)
        {
        	timeout--;
        }
        receive_data = SPI_fs8x->POPR.R;
        *(rxFrame + end_size - cnt) = (uint8_t)(receive_data & 0x000000FF);
        FS8xDBG("SPI rx data = %02x , complete rx = %08x\n",*(rxFrame + end_size - cnt) , receive_data);
        SPI_fs8x->SR.B.TCF = 1;
        SPI_fs8x->SR.B.RFDF = 1;
        if(0 == timeout)
		{
        	FS8xDBG("SPI transmit timeout (%d)\n" ,cnt);
			goto error;
		}
        timeout = SPI_TIME_OUT;

    }

	SIUL2.DIRER0.B.EIRE0 = 0x01;
    return fs8xStatusOk;
    error:
		SIUL2.DIRER0.B.EIRE0 = 0x01;
		FS8xDBG("SPI Fail and return error code\n");
	return errorcode;
}

