/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2017                                                   */
/*                                                                              */
/* All rights are reserved. Reproduction in whole or in part is prohibited      */
/* without the prior written consent of the copy-right owner.                   */
/* This source code and any compilation or derivative thereof is the sole       */
/* property of NXP B.V. and is provided pursuant to a Software License          */
/* Agreement. This code is the proprietary information of NXP B.V. and          */
/* is confidential in nature. Its use and dissemination by any party other      */
/* than NXP B.V. is strictly limited by the confidential information            */
/* provisions of the agreement referenced above.                                */
/*                                                                              */
/* NXP reserves the right to make changes without notice at any time.           */
/* NXP makes no warranty, expressed, implied or statutory, including but        */
/* not limited to any implied warranty of merchantability or fitness for any    */
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage        */
/* arising from its use.                                                        */
/*                                                                              */
/* NOT A CONTRIBUTION                                                           */
/*------------------------------------------------------------------------------*/
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

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "hw_ver.h"
//#include "sys_shared.h"
#include "SPI_TEF810X.h"
#define  SPI_TIME_OUT  6000
// ---------------------------------------------------------------
// ------------  SPI Definitions ---------------------------------
// ---------------------------------------------------------------
//#define SPI_DEBUG
// I/O defines
#define MSCR_OUTPUT				 0x32840000  // Full drive without slew rate, Output enabled, don't disable safe mode, Input hysteresis
#define MSCR_INPUT       		 0x008C0000  // Input buffer enabled, Input hysteresis


//AMO
// SPI Chip select, Output
#define SPI_2_CS0_MSCR_NB_AMO        44
#define SPI_2_CS0_MSCR_SSS_AMO       2
// SPI Serial data out, Output
#define SPI_2_SOUT_MSCR_NB_AMO       12
#define SPI_2_SOUT_MSCR_SSS_AMO      1
// SPI Clock, Output
#define SPI_2_CLK_MSCR_NB_AMO        11
#define SPI_2_CLK_MSCR_SSS_AMO       1
// SPI Serial data in, Input
#define SPI_2_SIN_MSCR_NB_AMO        13
#define SPI_2_SIN_IMCR_NB_AMO        9
#define SPI_2_SIN_IMCR_SSS_AMO       2
#define S_FIFO_PCS_AMO                    (1 << 3)//PCS3
#define S_TXRX_PCS_AMO                    (1 << (3 + 16))//PCS3

// SPI Chip select, Output
#define SPI_2_CS0_MSCR_NB        10
#define SPI_2_CS0_MSCR_SSS       1
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
#define S_FIFO_PCS                    (1 << 0)//PCS0
#define S_TXRX_PCS                    (1 << (0 + 16))//PCS0




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

/* ------------------------------------------------------------------------------
 Global Variables
--------------------------------------------------------------------------------*/
volatile struct SPI_tag* SPI;

/* The depth of the HW FIFO */
#define FIFO_DEPTH              4
#define SPI_DATA_WIDTH          16

#define SPIE_OK             (0)
#define SPIE_BAD            (-1)
#define SPIE_JOB_NOT_DONE   (-2)

uint8_t g_txbuff[1024];
uint8_t g_rxbuff[1024];

typedef struct dol_es1_spicmdtype
{
    uint32_t mod_add:8;
    uint32_t cmd:4;
    uint32_t reg_offh:4;
    uint32_t reg_offl:8;
    uint32_t recv:8;
}dol_es1_spicmdtype_t;

typedef SPI_PUSHR_PUSHR_tag Spi_CommandType;

static uint64_t s_fifo_pcs = S_FIFO_PCS;
static uint64_t s_txrx_pcs = S_TXRX_PCS;
/* ------------------------------------------------------------------------------
 Local Function Prototypes
--------------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------------
 Function Implementations
--------------------------------------------------------------------------------*/

/* ------------------------------------------------------------------------------
SPI_cfg

DESCRIPTION:
Configures chosen SPI module for communication with Dolphin

INPUTS:
spi_num_t spi_num - The SPI module to configure
spi_baudrate_t baud_rate - The chosen Baud rate (Dolphin supports up to 40Mbps)
state_t mtfe - Whether to use a modified timing format (MTFE)

RETURNS:
retval_t success - Indicator of success or failure
--------------------------------------------------------------------------------*/
static void  SPI_TEF810X_cfg(spi_num_t spi_num, spi_baudrate_t baud_rate, spi_state_t mtfe)
{
	HW_VER_E hw_ver;
	hw_ver = get_hw_ver();
	uint8_t clk_mscr_nb,sout_mscr_nb,sin_mscr_nb,sin_imcr_nb,cs_mscr_nb;
	uint8_t clk_mscr_nb_sss,sout_mscr_nb_sss,sin_imcr_nb_sss,cs_mscr_nb_sss;
	if(	(hw_ver == HW_30693G006030_AMO_RF_BV1p0)
		||(hw_ver == HW_30963G006040_AMO_RF_BV2p0)
		||(hw_ver == HW_30963G006040_AMO_RF_BV2p0))
	{
		clk_mscr_nb = SPI_2_CLK_MSCR_NB_AMO;
		sout_mscr_nb = SPI_2_SOUT_MSCR_NB_AMO;
		sin_mscr_nb = SPI_2_SIN_MSCR_NB_AMO;
		sin_imcr_nb = SPI_2_SIN_IMCR_NB_AMO;
		cs_mscr_nb = SPI_2_CS0_MSCR_NB_AMO;
		clk_mscr_nb_sss = SPI_2_CLK_MSCR_SSS_AMO;
		sout_mscr_nb_sss = SPI_2_SOUT_MSCR_SSS_AMO;
		sin_imcr_nb_sss = SPI_2_SIN_IMCR_SSS_AMO;
		cs_mscr_nb_sss = SPI_2_CS0_MSCR_SSS_AMO;
		s_fifo_pcs = S_FIFO_PCS_AMO;
		s_txrx_pcs = S_TXRX_PCS_AMO;
	}
	else
	{
		clk_mscr_nb = SPI_2_CLK_MSCR_NB;
		sout_mscr_nb = SPI_2_SOUT_MSCR_NB;
		sin_mscr_nb = SPI_2_SIN_MSCR_NB;
		sin_imcr_nb = SPI_2_SIN_IMCR_NB;
		cs_mscr_nb = SPI_2_CS0_MSCR_NB;
		clk_mscr_nb_sss = SPI_2_CLK_MSCR_SSS;
		sout_mscr_nb_sss = SPI_2_SOUT_MSCR_SSS;
		sin_imcr_nb_sss = SPI_2_SIN_IMCR_SSS;
		cs_mscr_nb_sss = SPI_2_CS0_MSCR_SSS;
		s_fifo_pcs = S_FIFO_PCS;
		s_txrx_pcs = S_TXRX_PCS;
	}
    // pin setup
    if (spi_num == 1){
        SPI = (volatile struct SPI_tag*) &SPI_1;
        SIUL2.MSCR[5].R = 0x12840001;                        // PA5/F14: configure SPI2-CS0  -> PA5 on MPC57xx Motherboard
        SIUL2.MSCR[6].R = 0x12840001;                        // PA6/H17: configure SPI2-SCK  -> PA6 on MPC57xx Motherboard
        SIUL2.MSCR[7].R = 0x12840001;                        // PA7/A15: configure SPI2-SOUT -> PA7 on MPC57xx Motherboard
        SIUL2.MSCR[8].R = 0x008C0000;                        // PA8/D15: configure SPI2-SIN  -> PA8 on MPC57XX Motherboard
        SIUL2.IMCR[6].R = 0x00000001;                         //
    } else if (spi_num == 2) {
                SPI = (volatile struct SPI_tag*) &SPI_2;
                SIUL2.MSCR[clk_mscr_nb].R = MSCR_OUTPUT | clk_mscr_nb_sss;                           // PA11/F15: configure SPI2-SCK  -> PA11 on MPC57xx Motherboard
                SIUL2.MSCR[sout_mscr_nb].R = MSCR_OUTPUT | sout_mscr_nb_sss;                   // PA12/B16: configure SPI2-SOUT -> PA12 on MPC57xx Motherboard
                SIUL2.MSCR[sin_mscr_nb].R = MSCR_INPUT;                  // PA13/D17: configure SPI2-SIN  -> PA13 on MPC57XX Motherboard
                SIUL2.IMCR[sin_imcr_nb].R  = 0x00000000 | sin_imcr_nb_sss;                       //
                SIUL2.MSCR[cs_mscr_nb].R = MSCR_OUTPUT | cs_mscr_nb_sss;                           // PA10/C16: configure SPI2-CS0  -> PA10 on MPC57xx Motherboard
    } /*else {
                return INVALID_ARGUMENT;                                    // if SPI number not 1 or 2 return error
    }*/

    // Check if protocol clock is 80 MHz. If not then SPI_CLK has not been correctly configured in CGM
    if(CGM.AC12_DC0.R != 0x80020000) //return SPI_CLOCK_ERROR;
    	CGM.AC12_DC0.R = 0x80020000;

    // MCR initialization:
    //SPI->MCR.R = 0x80FF0E01 | (mtfe << 26);
    SPI->MCR.B.MSTR = 1;          // Enable Master mode
    SPI->MCR.B.CONT_SCKE = 0;     // No continuous clock
    SPI->MCR.B.DCONF = 1;         // SPI
    SPI->MCR.B.FRZ = 0;           // Do not halt in debug mode
    SPI->MCR.B.MTFE = mtfe;       // Modified transfer format
    SPI->MCR.B.PCSSE = 0;         // Use PCS5 as chip select
    SPI->MCR.B.ROOE = 0;          // Receive FIFO overflow -> ignore incoming data
    SPI->MCR.B.PCSIS = 0xFF;      // PCS inactive state is high
    SPI->MCR.B.DIS_TXF = 0;       // Enable TX FIFO
    SPI->MCR.B.DIS_RXF = 0;       // Enable RX FIFO
    SPI->MCR.B.CLR_TXF = 1;       // Clear TX FIFO
    SPI->MCR.B.CLR_RXF = 1;       // Clear RX FIFO
    SPI->MCR.B.SMPL_PT = 2;       // 2 fp clock cycles between SCK and SIN (MTFE only!)
    SPI->MCR.B.PES = 0;           // Don't stop on parity error
    SPI->MCR.B.HALT = 1;          // Keep HALT=1 (stop transfers)
    SPI->MCR.B.MDIS = 0;          // Enable module

    /* CTAR0 initialization used for 8 bit data transfers
     * no double baudrate, frame size 8-bits, SCK polarity is high, data is changed on leading (falling edge) and captured on following (rising) edge (CPOL = CPHA = 1), MSB first,
     * PCS to SCK delay is 2, after SCK delay is 4, delay after transfer is 64, baudrate depends on function argument
     */
    //SPI->MODE.CTAR[0].R = 0x3E000150 | baud_rate;

    SPI->MODE.CTAR[0].B.BR = baud_rate;          // Baude rate scaler
    SPI->MODE.CTAR[0].B.DBR = 0;                 // No double baud rate
    SPI->MODE.CTAR[0].B.PBR = 0;                 // Baud rate prescaler = 2

    SPI->MODE.CTAR[0].B.FMSZ = ( SPI_DATA_WIDTH - 1 );      // Frame size = 8-bits

    SPI->MODE.CTAR[0].B.LSBFE = 0;               // MSB transmitted first
    SPI->MODE.CTAR[0].B.CPOL = 0;                // Inactive state of SCK is Low
    SPI->MODE.CTAR[0].B.CPHA = 0;                // Data is captured on the leading edge of SCK and changed on the following edge.


    SPI->MODE.CTAR[0].B.PASC = 0;                // After SCK delay prescaler = 1
    SPI->MODE.CTAR[0].B.ASC = 1;                 // After SCK delay scaler = 4

    SPI->MODE.CTAR[0].B.PCSSCK = 0;              // PCS to SCK delay prescaler = 1
    SPI->MODE.CTAR[0].B.CSSCK = 0;               // PCS to SCK delay scaler = 2

    SPI->MODE.CTAR[0].B.PDT = 2;                 // Delay after transfer prescaler = 1
    SPI->MODE.CTAR[0].B.DT = 2;                  // Delay after transfer delay scaler = 64

    SPI->SR.R = 0xFFFFFFFF;                      // clear all flags
    SPI->MCR.B.HALT = 0;                         // start transfers

    SPI->RSER.B.TFFF_RE = 0x01;
    SPI->RSER.B.TFFF_DIRS = 0x01;
    SPI->RSER.B.RFDF_RE = 0x01;
    SPI->RSER.B.RFDF_DIRS = 0x01;

    //return SUCCESS;
}

void SPI_init(void)
{
	 SPI_TEF810X_cfg(SPI2, MBITS20, SPI_DISABLE);
}

void TEF810X_spiTxRx(uint8_t* txbuf, uint8_t* rxbuf, int len)
{
    Spi_CommandType cmd;
    uint32_t        popVal;
    int32_t         fifoLeft;
    int             tx_cnt;
    int             rx_cnt;

    cmd.R = 0;
    fifoLeft = FIFO_DEPTH;
    tx_cnt = 0;
    rx_cnt = 0;

    while (rx_cnt < len)
	{
    	/* keep tx fifo filled */
    	if ((fifoLeft > 0) && (tx_cnt < len))
    	{
			/* Channels should keep CS active ( A job must assert CS continuously) */
			cmd.B.CONT = 1;
			/* Set the Chip Select (PCS) */
            cmd.B.PCS = s_fifo_pcs;
			cmd.B.CTAS = 0x00;

			if(SPI_DATA_WIDTH > 8 )
			{
				cmd.B.TXDATA = (txbuf[tx_cnt] << 8) | txbuf[tx_cnt + 1];
				tx_cnt += 2;
			}
			else
			{
				cmd.B.TXDATA = txbuf[tx_cnt];
				tx_cnt++;
			}

			/* Done with channel? */
			if (tx_cnt >= len)
			{
				cmd.B.CONT = 0;
			}

			fifoLeft--;
			SPI->PUSHR.PUSHR.R = cmd.R;
        }

    	/* keep rx fifo empty */
    	if (SPI->SR.B.RXCTR > 0)
    	{
   	        /* Pop the FIFO */
			popVal = SPI->POPR.B.RXDATA;
			fifoLeft++;

			if(SPI_DATA_WIDTH > 8)
			{
				rxbuf[rx_cnt++] = (uint8_t)(popVal >> 8);
			}
			rxbuf[rx_cnt++] = (uint8_t)popVal;
    	}
    }
}

/*
    Calculates the SAE-J1850 Cyclic Redundancy Check byte (CRC)

    CRC result width        ::  8 bits
    Polynomial              ::  1Dh (x8+ x4+ x3+ x2+ x0)
    Initial value           ::  FFh
    Input data reflected    ::  No
    Result data reflected   ::  No
    XOR value               ::  FFh
    check                   ::  4Bh
    Magic check             ::  C4h

    Check value indicates that if the implementation is given the ASCII values "123456789" then it should return the value 0x4B.
    Magic Check - Compute the checksum over data plus checksum and XOR that with 0xFF. The result for should always be 0xC4.

    Note: The 0x11D constant used in the routine is derived from
    the mandated CRC division polynomial of: x^8+x^4+X^3+X^2+1, which
    corresponds to bit positions 8,4,3,2 and 0. Those bit
    positions form the binary number: 100011101 which is $11D.
    $1D could be used instead because we are only generating an 8-bit CRC.

*/
static uint8_t SPI_TEF810X_crc8_sae_j1850( uint8_t * buff, int length )
{
    uint32_t crc;
    int32_t f, bit;

    crc = 0xFF;

    for( f = 0; f < length; f++ )
    {
        crc ^= buff[f];

        for( bit = 0; bit < 8; bit++ )
        {
            if ((crc & 0x80) != 0)
            {
                crc <<= 1;
                crc ^= 0x1D;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return (~crc) & 0xFF;
}

retval_e SPI_TEF810X_xferFifoMode(uint8_t mod_addr, uint32_t cmd, uint16_t reg_addr, uint32_t * tx_buff, uint32_t * rx_buff, uint8_t len, uint32_t * ret_cmd )
{
    retval_e rv = SUCCESS;
    dol_es1_spicmdtype_t dolcmd;
    int32_t copy_loop = 0x01000000;
    bool en_crc = false;
    int tot_len;

    SPI->MCR.B.CLR_RXF = 1;             // Clear Rx FIFO
    SPI->MCR.B.CLR_TXF = 1;             // Clear Tx FIFO
    SPI->SR.R = 0xFFFFFFFF;             // Clear all flags
    SPI->MCR.B.HALT = 0;

    tot_len   = 0x00;

    memset((void *)&dolcmd, 0x00, sizeof(dol_es1_spicmdtype_t));

    if( (cmd & 0xFF00) == 0x7500 )
    {
        en_crc = true;
    }

    dolcmd.recv = 0xBA;
    dolcmd.mod_add = mod_addr;
    dolcmd.reg_offh = (reg_addr & 0x0F00) >> 0x08;
    dolcmd.cmd = ( cmd & 0x0F );
    dolcmd.reg_offl = (reg_addr & 0xFF);

    memcpy(( void *) &g_txbuff[0x00], ( void * )&dolcmd, 0x03); //sizeof(dol_es1_spicmdtype_t)
    tot_len += 0x03; //sizeof(dol_es1_spicmdtype_t)

    if( tx_buff != NULL )
    {
        for( copy_loop = 0x00; copy_loop < len; copy_loop++ )
        {
            uint8_t * p_txbuff = (uint8_t *)&tx_buff[ copy_loop ];

            g_txbuff[ tot_len + 3 ] = p_txbuff[ 3 ];
            g_txbuff[ tot_len + 2 ] = p_txbuff[ 2 ];
            g_txbuff[ tot_len + 1 ] = p_txbuff[ 1 ];
            g_txbuff[ tot_len ] = p_txbuff[ 0 ];

            tot_len += 0x04;
        }
    }
    else
    {
        memset( (void*)&g_txbuff[ tot_len ], 0x5B, len * sizeof(uint32_t));
        tot_len += ( len * sizeof(uint32_t) );
    }

    if( en_crc == true )
    {
        uint8_t cal_crcval = 0x00;

        if( tx_buff != NULL )
        {
            cal_crcval = SPI_TEF810X_crc8_sae_j1850( (void*)&g_txbuff[0x00], tot_len );
            g_txbuff[tot_len] = cal_crcval;
            tot_len += 0x01;
        }
        else
        {
            g_txbuff[ 0x03 + 0x00 ] = 0x00;       //MC4 Burst length (upper bits)
            g_txbuff[ 0x03 + 0x01 ] = (len - 1);  //MC5 Burst length (lower bits)
            g_txbuff[ 0x03 + 0x02 ] = 0x00;       //Zero byte
            g_txbuff[ 0x03 + 0x03 ] = 0x00;       //Zero byte
            cal_crcval = SPI_TEF810X_crc8_sae_j1850( (void*)&g_txbuff[0x00], 0x07 );
            g_txbuff[0x03 + 0x04] = cal_crcval;
            tot_len += 0x02;
        }
    }

    //g_txbuff[ tot_len ] = 0x00;
    tot_len += ( tot_len % 2 ) ? 1 : 0;

    TEF810X_spiTxRx(g_txbuff, g_rxbuff, tot_len);

    if( rx_buff != NULL )
    {
        if ( ( mod_addr & 0x80 ) == 0x80 )
        {
        	tot_len = 0x03;
        }
        else
        {
        	tot_len = 0x04;
        }

        if( en_crc == true )
        {
            uint8_t cal_crcval;
            uint32_t crc_cal_buff_length = 0x03;
            crc_cal_buff_length += (len * sizeof(uint32_t));
            cal_crcval = SPI_TEF810X_crc8_sae_j1850( (void*)&g_rxbuff[0x01],  crc_cal_buff_length );

            if( cal_crcval != g_rxbuff[crc_cal_buff_length + 1 ] )
            {
                rv = SPI_CRC_ERROR;
            }
        }

        for( copy_loop = 0x00; copy_loop < len; copy_loop++ )
        {
            uint8_t * p_rxbuff = (uint8_t *)&rx_buff[ copy_loop ];

            p_rxbuff[ 3 ] = g_rxbuff[ tot_len + 3];
            p_rxbuff[ 2 ] = g_rxbuff[ tot_len + 2 ];
            p_rxbuff[ 1 ] = g_rxbuff[ tot_len + 1 ];
            p_rxbuff[ 0 ] = g_rxbuff[ tot_len ];

            tot_len += 0x04;
        }
    }

    SPI->MCR.B.HALT = 1;
    return( rv );
}

uint32_t g_SPI_TEF810X_spad_txbuff[16];
uint32_t g_SPI_TEF810X_spad_rxbuff[16];

/* ------------------------------------------------------------------------------
 SPI_TEF810X_txrx

 DESCRIPTION:
 Performs a 64-bit SPI transfer/receive with Dolphin.

 INPUTS:
 uint32_t mod_addr - 8-bit module address
 uint32_t cmd - 4-bit command
 uint32_t reg_addr - 12-bit register address
 uint32_t data - 32-bit data payload

 RETURNS:
 retval_e success - Indicator of success or failure
 uint32_t *returnBytes - Array of 4 bytes to contain the data received
--------------------------------------------------------------------------------*/
retval_e SPI_TEF810X_txrx(uint32_t mod_addr, uint32_t cmd, uint32_t reg_addr, uint32_t * tx_buff, uint32_t * rx_buff, uint32_t len, uint32_t * ret_cmd )
{
    int32_t timeout = SPI_TIME_OUT;                                  // ~100 ms timeout at 16 MHz core clock, ~40 ms at 40 MHz, ~12 ms at 133 MHz
    uint32_t loop_inx;
    uint32_t tx_word;
    uint8_t * slv_rcv = (uint8_t *)(&g_SPI_TEF810X_spad_rxbuff[0x00]);
    uint8_t * slv_rcv2 = (uint8_t *)(&g_SPI_TEF810X_spad_rxbuff[0x04]);
    bool wr_rd_mode = false;
    bool loop_back_mode = false;

    mod_addr = mod_addr & 0x000000FF;   // Module address is 8-bits
    cmd = cmd & 0x0000000F;             // Command is 4-bits
    reg_addr = reg_addr & 0x00000FFF;   // Register address is 12-bits

    // Since SPI is shared resource between ISR and main thread, below
    // block is considered as critical section, and locked to avoid Race-Conditions.
    // Disable the interrupt pins by
    // setting the appropriate EIREn bits in DIRER0
    SIUL2.DIRER0.B.EIRE0 = 0x00;

    SPI->MCR.B.CLR_RXF = 1;             // Clear Rx FIFO
    SPI->MCR.B.CLR_TXF = 1;             // Clear Tx FIFO
    SPI->SR.R = 0xFFFFFFFF;             // Clear all flags

    memset(g_SPI_TEF810X_spad_txbuff,sizeof(uint32_t) * 16, 0x00);
    memset(g_SPI_TEF810X_spad_rxbuff,sizeof(uint32_t) * 16, 0x00);

    if( ( tx_buff != NULL ) && ( rx_buff != NULL ) )
    {
        wr_rd_mode = true;
    }

    if( ( mod_addr & 0x80 ) != 0x00 )
    {
        loop_back_mode = true;
    }

    g_SPI_TEF810X_spad_txbuff[0x00] = (0x84010000 | mod_addr);
    //.while(!SPI->SR.B.TFFF);
    while(!SPI->SR.B.TFFF && timeout > 0)
    {
    	timeout--;
    }
    SPI->PUSHR.PUSHR.R = 0x84010000 | s_txrx_pcs | mod_addr;                                                     // (MOSI-M0) 8-bit transfer of 8-bit module address, CTAR0, keep PCS asserted, clear transfer counter
    //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
    timeout = SPI_TIME_OUT;
    while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
    {
    	timeout--;
    }
    slv_rcv[0x00] = SPI->POPR.R; SPI->SR.B.TCF = 1;       											// (MISO-S0) Pop useless received byte, clear transfer complete flag

    g_SPI_TEF810X_spad_txbuff[0x01] = (0x80010000 | (cmd << 4) | (reg_addr >> 8));
    //while(!SPI->SR.B.TFFF);
    timeout = SPI_TIME_OUT;
    while(!SPI->SR.B.TFFF && timeout > 0)
    {
    	timeout--;
    }
    SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | (cmd << 4) | (reg_addr >> 8);                                 // (MOSI-M1) 8-bit transfer of 4-bit write cmd + upper 4 bits of reg_addr, CTAR0, keep PCS asserted
    //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
    timeout = SPI_TIME_OUT;
    while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
    {
    	timeout--;
    }
    slv_rcv[0x01] = SPI->POPR.R; SPI->SR.B.TCF = 1;       											// (MISO-S1) Pop useless received byte, clear transfer complete flag

    g_SPI_TEF810X_spad_txbuff[0x02] = (0x80010000 | (reg_addr & 0x000000FF));
    //while(!SPI->SR.B.TFFF);
    timeout = SPI_TIME_OUT;
    while(!SPI->SR.B.TFFF && timeout > 0)
    {
    	timeout--;
    }
    SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | (reg_addr & 0x000000FF);                                      // (MOSI-M2) 8-bit transfer of lower 8 bits of reg_addr, CTAR0, keep PCS asserted
    //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
    timeout = SPI_TIME_OUT;
    while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
    {
    	timeout--;
    }
    slv_rcv[0x02] =  SPI->POPR.R; SPI->SR.B.TCF = 1;      											// (MISO-S2) Pop useless received byte, clear transfer complete flag

    for( loop_inx = 0; loop_inx < len; loop_inx++ )
    {
        tx_word = ( tx_buff != NULL) ? tx_buff[loop_inx] : 0x55;

        if( loop_inx == 0x00 )
        {
            if( tx_buff != NULL )
            {
                g_SPI_TEF810X_spad_txbuff[0x03] = (0x80010000 | ((tx_word >> 24) & 0x000000FF));
                //while(!SPI->SR.B.TFFF);
                timeout = SPI_TIME_OUT;
                while(!SPI->SR.B.TFFF && timeout > 0)
                {
                	timeout--;
                }
                SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | ((tx_word >> 24) & 0x000000FF);                    // R-(MOSI-M4) W-(MOSI-M3) 8-bit transfer of upper 8 bits of reg_addr, CTAR0, keep PCS asserted
                //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
                timeout = SPI_TIME_OUT;
                while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
                {
                	timeout--;
                }
                slv_rcv2[0x00] = SPI->POPR.R; SPI->SR.B.TCF = 1;   									// R-(MISO-S4) W-(MISO-S3) Pop useless received byte, clear transfer complete flag
            }
            else
            {
                // Perform dummy write
                g_SPI_TEF810X_spad_txbuff[0x03] = (0x80010000 | 0x55);
                //while(!SPI->SR.B.TFFF);
                timeout = SPI_TIME_OUT;
                while(!SPI->SR.B.TFFF && timeout > 0)
                {
                	timeout--;
                }
                SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | 0x55;                                             // R-(MOSI-M3)
                //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
                timeout = SPI_TIME_OUT;
                while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
                {
                	timeout--;
                }
                slv_rcv[0x03] = SPI->POPR.R; SPI->SR.B.TCF = 1;        								// R-(MISO-S3) Pop useless received byte

                g_SPI_TEF810X_spad_txbuff[0x04] = (0x80010000 | ((tx_word >> 24) & 0x000000FF));
                //while(!SPI->SR.B.TFFF);
                timeout = SPI_TIME_OUT;
                while(!SPI->SR.B.TFFF && timeout > 0)
                {
                	timeout--;
                }
                SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | ((tx_word >> 24) & 0x000000FF);                    // R-(MOSI-M4) W-(MOSI-M3) 8-bit transfer of upper 8 bits of reg_addr, CTAR0, keep PCS asserted
                //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
                timeout = SPI_TIME_OUT;
                while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
                {
                	timeout--;
                }
                slv_rcv2[0x00] = SPI->POPR.R; SPI->SR.B.TCF = 1;   									// R-(MISO-S4) W-(MISO-S3) Pop useless received byte, clear transfer complete flag
            }
        }
        else
        {
            g_SPI_TEF810X_spad_txbuff[0x04] = (0x80010000 | ((tx_word >> 24) & 0x000000FF));
            //while(!SPI->SR.B.TFFF);
            timeout = SPI_TIME_OUT;
            while(!SPI->SR.B.TFFF && timeout > 0)
            {
            	timeout--;
            }
            SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs | ((tx_word >> 24) & 0x000000FF);                        // R-(MOSI-M4) W-(MOSI-M3) 8-bit transfer of upper 8 bits of reg_addr, CTAR0, keep PCS asserted

            if(( wr_rd_mode == true ) && (loop_back_mode == false))
            {
                //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
                timeout = SPI_TIME_OUT;
                while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
                {
                	timeout--;
                }
                slv_rcv2[0x04] = SPI->POPR.R; SPI->SR.B.TCF = 1;   									// R-(MISO-S4) W-(MISO-S3) Pop useless received byte, clear transfer complete flag
                rx_buff[loop_inx - 1] = ( (slv_rcv2[0x01] << 24) | (slv_rcv2[0x02] << 16) |  (slv_rcv2[0x03] << 8) | slv_rcv2[0x04] );
            }
            else
            {
                while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
                timeout = SPI_TIME_OUT;
                while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
                {
                	timeout--;
                }
                slv_rcv2[0x00] = SPI->POPR.R; SPI->SR.B.TCF = 1;   									// R-(MISO-S4) W-(MISO-S3) Pop useless received byte, clear transfer complete flag
            }
        }

        g_SPI_TEF810X_spad_txbuff[0x05] = (0x80010000 | ((tx_word >> 16) & 0x000000FF));
        //while(!SPI->SR.B.TFFF);
        timeout = SPI_TIME_OUT;
        while(!SPI->SR.B.TFFF && timeout > 0)
        {
        	timeout--;
        }
        SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs |((tx_word >> 16) & 0x000000FF);                             // R-(MOSI-M5) W-(MOSI-M4) 8-bit transfer of bits [16:23] of reg_addr, CTAR0, keep PCS asserted
        //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
        timeout = SPI_TIME_OUT;
        while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
        {
        	timeout--;
        }
        slv_rcv2[0x01] = SPI->POPR.R; SPI->SR.B.TCF = 1;    										// R-(MISO-S5) W-(MISO-S4) Pop useless received byte, clear transfer complete flag

        g_SPI_TEF810X_spad_txbuff[0x06] = (0x80010000 | ((tx_word >> 8) & 0x000000FF));
        //while(!SPI->SR.B.TFFF);
        timeout = SPI_TIME_OUT;
        while(!SPI->SR.B.TFFF && timeout > 0)
        {
        	timeout--;
        }
        SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs |((tx_word >> 8) & 0x000000FF);                              // R-(MOSI-M6) W-(MOSI-M5) 8-bit transfer of bits [8:15] of reg_addr, CTAR0, keep PCS asserted
        //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
        timeout = SPI_TIME_OUT;
        while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
        {
        	timeout--;
        }
        slv_rcv2[0x02] = SPI->POPR.R; SPI->SR.B.TCF = 1;    										// R-(MISO-S6) W-(MISO-S5) Pop useless received byte, clear transfer complete flag

        g_SPI_TEF810X_spad_txbuff[0x07] = (0x80010000 | (tx_word & 0x000000FF));
        //while(!SPI->SR.B.TFFF);
        timeout = SPI_TIME_OUT;
        while(!SPI->SR.B.TFFF && timeout > 0)
        {
        	timeout--;
        }
        SPI->PUSHR.PUSHR.R = 0x80010000 | s_txrx_pcs |(tx_word & 0x000000FF);                                     // R-(MOSI-M7) W-(MOSI-M6) 8-bit transfer of lower 8 bits of reg_addr, CTAR0, keep PCS asserted
        //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
        timeout = SPI_TIME_OUT;
        while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
        {
        	timeout--;
        }
        slv_rcv2[0x03] = SPI->POPR.R; SPI->SR.B.TCF = 1;    										// R-(MISO-S7) W-(MISO-S6) Pop useless received byte, clear transfer complete flag

        if( rx_buff != NULL )
        {
            rx_buff[loop_inx] = ( (slv_rcv2[0x00] << 24) | (slv_rcv2[0x01] << 16) |  (slv_rcv2[0x02] << 8) | slv_rcv2[0x03] );
        }

        if( loop_inx == (len -1) )
        {
            //while(!SPI->SR.B.TFFF);
            timeout = SPI_TIME_OUT;
            while(!SPI->SR.B.TFFF && timeout > 0)
            {
            	timeout--;
            }
            SPI->PUSHR.PUSHR.R = 0x08010000 | s_txrx_pcs |0x55;                                                 // W-(MOSI-M7) 8-bit dummy write, CTAR0, end of queue
            //while(!SPI->SR.B.RFDF || !SPI->SR.B.TCF);
            timeout = SPI_TIME_OUT;
            while((!SPI->SR.B.RFDF || !SPI->SR.B.TCF) && timeout > 0)
            {
            	timeout--;
            }
            slv_rcv2[0x04] = SPI->POPR.R;                 											// W-(MISO-S7) Pop useless received byte,

            if(( wr_rd_mode == true ) && (loop_back_mode == false))
            {
                rx_buff[loop_inx] = ( (slv_rcv2[0x01] << 24) | (slv_rcv2[0x02] << 16) |  (slv_rcv2[0x03] << 8) | slv_rcv2[0x04] );
            }
        }

    }

    timeout = SPI_TIME_OUT;
    while((!SPI->SR.B.EOQF) && (timeout > 0))
    {
        timeout--;          // wait for EOQ flag
    }
    if(timeout < 1)
    {
        return TIMEOUT;
    }

    SPI->SR.R = 0xFFFFFFFF;                                 // clear all flags

    if( ret_cmd != NULL )
    {
        *ret_cmd = ( (slv_rcv[0x00] << 24) | (slv_rcv[0x01] << 16) |  (slv_rcv[0x02] << 8) | slv_rcv[0x03] );
    }

    // Enable the interrupt pins by
    // setting the appropriate EIREn bits in DIRER0
    SIUL2.DIRER0.B.EIRE0 = 0x01;

    return SUCCESS;
}
