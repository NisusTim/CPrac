/*
 * MIPI_CSI2.c
 *
 *  Created on: 2016¦~12¤ë8¤é
 *      Author: Bruce Chang
 */

#include "sys_shared.h"


/*******************************************************************************
* Function prototypes
*******************************************************************************/
void MIPI_CSI2_cfg(mipi_num_lanes_t num_lanes, mipi_data_rate_t input_data_rate);


//=============================================================================
// MIPI-CSI initianlization
//=============================================================================
void CSI2_init(void)
{
	MIPI_CSI2_cfg( MIPI_NUM_LANES, MIPI_DATA_RATE ); // MIPI-CSI module configuration
}

//=============================================================================
// MIPI-CSI CONFIGURATION
//=============================================================================
void MIPI_CSI2_cfg(mipi_num_lanes_t num_lanes, mipi_data_rate_t input_data_rate)
{
	int32_t timeout = 120000;												// ~10ms timeout at 120 MHz core clock
	uint32_t hssetl_value;


	if(input_data_rate == MBITS_120)
		hssetl_value = 14;
	else if(input_data_rate == MBITS_240)
	    hssetl_value = 11;
	else
	    hssetl_value = 10;

    MIPICSI2.CONC.R = num_lanes-1;											// set number of lanes
    MIPICSI2.PHYC.R = 0;													// power-up receiver
    MIPICSI2.RXEN.R = 1;													// enable RX
    MIPICSI2.RESCS.R = 0;													// auto calibration
    while((MIPICSI2.RESCS.B.CALCOM != 1) && (timeout>0)){timeout--;}		// wait for calibration to complete
    if(timeout==0)
        PRINTF("Config CSI2 TIME OUT!\n");

    MIPICSI2.CLKCS.B.HSSETL  = hssetl_value;
    MIPICSI2.LAN0CS.B.D0HSET = hssetl_value;
    MIPICSI2.LAN1CS.B.D1HSET = hssetl_value;
    MIPICSI2.LAN2CS.B.D2HSET = hssetl_value;
    MIPICSI2.LAN3CS.B.D3HSET = hssetl_value;

    MIPICSI2.LINLEN.R = ((SAMPLES_PER_CHIRP*3)/2) * RX_ACTIVES;				// set line length to samples per chirp divided by 1.5 -> 4 ADC samples transferred in 6 data packets
    MIPICSI2.EXPCTDL.R = CHIRPS_PER_FRAME;									// set expected number of lines in a frame to chirps per frame

    MIPICSI2.INTRS.R = 0xF;													// clear all interrupt status flags
    MIPICSI2.ERRPHY.R = 0x000FFFFF;											// clear all MIPI DPHY error flags
    MIPICSI2.ERRPPREG.R = 0x3F;												// clear all packet and protocol errors

}

/* Interrupts from MIPICSI2_ERRPHY */
void DPHY_isr(void){

    // Handle errors
    while(1){};   // Placeholder

    return;
}

/* Interrupts from MIPICSI2_ERRPPREG */
void ERR_isr(void){

    // Handle errors
    while(1){};   // Placeholder

    return;
}

/* Interrupts from MIPICSI2_INTRS */
void VC_isr(void){
    // Handle errors
    while(1);    // Placeholder

    return;
}

