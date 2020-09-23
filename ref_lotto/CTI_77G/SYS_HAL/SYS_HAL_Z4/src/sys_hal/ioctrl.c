/*
 * io_ctrl.c
 *
 *  Created on: 2017�~1��3��
 *      Author: erichu
 */

#include "sys_shared.h"

void comb_es3_ioctrl_init(void);
void comb_ioctrl_init(void);
void dualboard_ioctrl_init(void);



void set_gpio(uint8_t index, uint8_t op)
{
	//0x32000000
	SIUL2.MSCR[index].B.SSS = 0;
	SIUL2.MSCR[index].B.OBE = 1;
	SIUL2.MSCR[index].B.SRC = 3;

	if(index % 4 == 0)
	{
		SIUL2.GPDO[index/4].B.PDO_4n = op;	/* output */
	}
	else if(index % 4 == 1)
	{
		SIUL2.GPDO[index/4].B.PDO_4n1 = op;	/* output */
	}
	else if(index % 4 == 2)
	{
		SIUL2.GPDO[index/4].B.PDO_4n2 = op;	/* output */
	}
	else if(index % 4 == 3)
	{
		SIUL2.GPDO[index/4].B.PDO_4n3 = op;	/* output */
	}
}

uint8_t get_gpio(uint8_t index)
{
	//0x00080000
	SIUL2.MSCR[index].B.SSS = 0;
	SIUL2.MSCR[index].B.OBE = 0;
	SIUL2.MSCR[index].B.IBE = 1;

	if(index % 4 == 0)
	{
		return (uint8_t)SIUL2.GPDI[index/4].B.PDI_4n;
	}
	else if(index % 4 == 1)
	{
		return (uint8_t)SIUL2.GPDI[index/4].B.PDI_4n1;
	}
	else if(index % 4 == 2)
	{
		return (uint8_t)SIUL2.GPDI[index/4].B.PDI_4n2;
	}
	else if(index % 4 == 3)
	{
		return (uint8_t)SIUL2.GPDI[index/4].B.PDI_4n3;
	}
	else
		return 2;
}

void comb_amo_ioctrl_init(void)
{
    /*Initial CAN 0 I/O Settings*/
    SIUL2.MSCR[16].B.SSS = 1;    /* Pad L15: Source signal is CAN0_TX */
    SIUL2.MSCR[16].B.OBE = 1;    /* Pad L15: Output Buffer Enable */
    SIUL2.MSCR[16].B.SRC = 3;    /* Pad L15: Maximum slew rate */

    SIUL2.MSCR[17].B.IBE = 1;    /* Pad M17: Enable pad for input - CAN0_RXD */
    SIUL2.IMCR[0].B.SSS = 0;     /* Pad M17: Source signal is CAN0_RXD */

    SIUL2.MSCR[56].B.SSS = 0;    /* Pad B13: Source signal is CAN0 CANSLPN,GPO */
    SIUL2.MSCR[56].B.OBE = 1;    /* Pad B13: Output Buffer Enable */
    SIUL2.MSCR[56].B.SRC = 3;    /* Pad B13: Maximum slew rate */
    SIUL2.GPDO[14].B.PDO_4n = 1;    /* Set CAN0 Transceiver to Normal mode ( output high ) */


    SIUL2.MSCR[6].B.SSS = 1;    /* Pad H17: Source signal is CAN0CTS,when CANTS high => TXD/RXD Enable */
    SIUL2.MSCR[6].B.OBE = 0;    /* Pad H17: Output Buffer Enable */
    SIUL2.MSCR[6].B.SRC = 3;    /* Pad H17: Maximum slew rate */

    /*Initial CAN 2 I/O Settings*/
    SIUL2.MSCR[0].B.SSS = 0;    /* Pad A11: Source signal is DSP_CAN2_STB,GPO*/
    SIUL2.MSCR[0].B.OBE = 1;    /* Pad A11: Output Buffer Enable */
    SIUL2.MSCR[0].B.SRC = 3;    /* Pad A11: Slew Rate Control => Full drive strength without slew rate control */
    SIUL2.GPDO[0].B.PDO_4n = 1;    /* Set CAN2 Transceiver to Normal mode ( output high ) */

    SIUL2.MSCR[133].B.SSS = 1;    /* Pad M16: Source signal is CAN2_TXD */
    SIUL2.MSCR[133].B.OBE = 1;    /* Pad M16: Output Buffer Enable */
    SIUL2.MSCR[133].B.SRC = 3;    /* Pad M16: Maximum slew rate */

    SIUL2.IMCR[2].B.SSS = 3;    /* Pad E16: Source signal is CAN2_RXD */
    SIUL2.MSCR[134].B.IBE = 1;    /* Pad E16: Enable pad for input */

    SIUL2.MSCR[42].R  = 0x00080000;        // RF_CHIRP_START
    SIUL2.MSCR[43].R  = 0x00080000;        // RF_READY_INT
    SIUL2.MSCR[77].R  = 0x32000000;        // RF_ERROR_RESET
    SIUL2.GPDO[19].R  = SIUL2.GPDO[19].R | 0x00010000;        // ERROR_RESET = high
    SIUL2.MSCR[80].R  = 0x00080000;        // RF_ERROR_N
    SIUL2.MSCR[128].R = 0x32000000;        // RF_RESET_N    0:RESET
    SIUL2.GPDO[32].R  = SIUL2.GPDO[32].R | 0x01000000;        // RESET_N = high
    SIUL2.MSCR[123].R = 0x00080000;        // RF_DATA_ACTIVE
    SIUL2.MSCR[124].R = 0x00080000;        // RF_DATA_OUT_CLK
}



void comb_es3_ioctrl_init(void)
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

	SIUL2.MSCR[133].B.SSS = 1;	/* Pad M16: Source signal is CAN2_TXD */
	SIUL2.MSCR[133].B.OBE = 1;	/* Pad M16: Output Buffer Enable */
	SIUL2.MSCR[133].B.SRC = 3;	/* Pad M16: Maximum slew rate */

	SIUL2.IMCR[2].B.SSS = 3;	/* Pad E16: Source signal is CAN2_RXD */
	SIUL2.MSCR[134].B.IBE = 1;	/* Pad E16: Enable pad for input */

	// H/W Version GPIO
	SIUL2.MSCR[5].R  = 0x00080000;		// DSP_VER0
	SIUL2.MSCR[9].R  = 0x00080000;		// DSP_VER1
	SIUL2.MSCR[18].R = 0x00080000;		// RF_VER0
	SIUL2.MSCR[19].R = 0x00080000;		// RF_VER1
	// RF GPIO
	SIUL2.MSCR[6].R   = 0x32000000;		// RF_TX1_PS
	SIUL2.MSCR[7].R   = 0x32000000;		// RF_TX2_PS
	SIUL2.MSCR[8].R   = 0x32000000;		// RF_TX3_PS

	SIUL2.MSCR[42].R  = 0x00080000;		// RF_CHIRP_START
	SIUL2.MSCR[43].R  = 0x00080000;		// RF_READY_INT
	SIUL2.MSCR[77].R  = 0x32000000;		// RF_ERROR_RESET
	SIUL2.GPDO[19].R  = SIUL2.GPDO[19].R | 0x00010000;		// ERROR_RESET = high
	SIUL2.MSCR[80].R  = 0x00080000;		// RF_ERROR_N
	SIUL2.MSCR[128].R = 0x32000000;		// RF_RESET_N	0:RESET
	SIUL2.GPDO[32].R  = SIUL2.GPDO[32].R | 0x01000000;		// RESET_N = high
	SIUL2.MSCR[123].R = 0x00080000;		// RF_DATA_ACTIVE
	SIUL2.MSCR[124].R = 0x00080000;		// RF_DATA_OUT_CLK

	//CLKOUT
	SIUL2.MSCR[22].B.SSS = 1;	/* Pad J14: Source signal is CLKOUT */
	SIUL2.MSCR[22].B.OBE = 1;	/* Pad J14: Output Buffer Enable */
	SIUL2.MSCR[22].B.SRC = 1;	/* Pad J14: Maximum slew rate */
}

void comb_ioctrl_init(void)
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
	SIUL2.GPDO[0].B.PDO_4n = 1;	/* Set CAN2 Transceiver to Normal mode ( output high ) */

	SIUL2.MSCR[133].B.SSS = 1;	/* Pad M16: Source signal is CAN2_TXD */
	SIUL2.MSCR[133].B.OBE = 1;	/* Pad M16: Output Buffer Enable */
	SIUL2.MSCR[133].B.SRC = 3;	/* Pad M16: Maximum slew rate */

	SIUL2.IMCR[2].B.SSS = 3;	/* Pad E16: Source signal is CAN2_RXD */
	SIUL2.MSCR[134].B.IBE = 1;	/* Pad E16: Enable pad for input */

	// H/W Version GPIO
	SIUL2.MSCR[5].R  = 0x00080000;		// DSP_VER0
	SIUL2.MSCR[9].R  = 0x00080000;		// DSP_VER1
	SIUL2.MSCR[18].R = 0x00080000;		// RF_VER0
	SIUL2.MSCR[19].R = 0x00080000;		// RF_VER1
	// RF GPIO
	SIUL2.MSCR[6].R   = 0x32000000;		// RF_TX1_PS
	SIUL2.MSCR[7].R   = 0x32000000;		// RF_TX2_PS
	SIUL2.MSCR[8].R   = 0x32000000;		// RF_TX3_PS

	SIUL2.MSCR[42].R  = 0x00080000;		// RF_CHIRP_START
	SIUL2.MSCR[43].R  = 0x00080000;		// RF_READY_INT
	SIUL2.MSCR[77].R  = 0x32000000;		// RF_ERROR_RESET
	SIUL2.GPDO[19].R  = SIUL2.GPDO[19].R | 0x00010000;		// ERROR_RESET = high
	SIUL2.MSCR[80].R  = 0x00080000;		// RF_ERROR_N
	SIUL2.MSCR[128].R = 0x32000000;		// RF_RESET_N	0:RESET
	SIUL2.GPDO[32].R  = SIUL2.GPDO[32].R | 0x01000000;		// RESET_N = high
	SIUL2.MSCR[123].R = 0x00080000;		// RF_DATA_ACTIVE
	SIUL2.MSCR[124].R = 0x00080000;		// RF_DATA_OUT_CLK
}

void dualboard_ioctrl_init(void)
{
	// CAN GPIO
	SIUL2.MSCR[0].R   = 0x32000000;
	/*Initial CAN 0 I/O Settings*/
	SIUL2.MSCR[16].B.SSS = 1;    /* Pad L15: Source signal is CAN0_TX */
	SIUL2.MSCR[16].B.OBE = 1;    /* Pad L15: Output Buffer Enable */
	SIUL2.MSCR[16].B.SRC = 3;    /* Pad L15: Maximum slew rate */

	SIUL2.MSCR[15].B.IBE = 1;    /* Pad L16: Enable pad for input - CAN0_RXD */
	SIUL2.IMCR[0].B.SSS = 1;     /* Pad L16: Source signal is CAN0_RXD */

	// LED GPIO
	SIUL2.MSCR[1].R   = 0x32000000;		// LED-R	0:Enable
	SIUL2.MSCR[2].R   = 0x32000000;		// LED-Y
	SIUL2.MSCR[3].R   = 0x32000000;		// LED-G
	SIUL2.GPDO[0].R   = 0x00010101;		// set GPIO[0] = 0 and turn off all LED
	// TEST GPIO
	SIUL2.MSCR[4].R   = 0x32000000;		// TEST1 pin
	SIUL2.MSCR[5].R   = 0x32000000;		// TEST2 pin
	// RF GPIO
	SIUL2.MSCR[6].R   = 0x32000000;		// RF_TX1_PS
	SIUL2.MSCR[7].R   = 0x32000000;		// RF_TX2_PS
	SIUL2.MSCR[8].R   = 0x32000000;		// RF_TX3_PS
	SIUL2.GPDO[1].R   = SIUL2.GPDO[1].R & 0xFF000000;		// not use and set to ground
	SIUL2.GPDO[2].R   = SIUL2.GPDO[2].R & 0x00FFFFFF;		// not use and set to ground

	SIUL2.MSCR[42].R  = 0x00080000;		// RF_CHIRP_START
	SIUL2.MSCR[43].R  = 0x00080000;		// RF_READY_INT
	SIUL2.MSCR[77].R  = 0x32000000;		// RF_ERROR_RESET
	SIUL2.GPDO[19].R  = SIUL2.GPDO[19].R | 0x00010000;		// ERROR_RESET = high
	SIUL2.MSCR[80].R  = 0x00080000;		// RF_ERROR_N
	SIUL2.MSCR[128].R = 0x32000000;		// RF_RESET_N	0:RESET
	SIUL2.GPDO[32].R  = SIUL2.GPDO[32].R | 0x01000000;		// RESET_N = high
	SIUL2.MSCR[123].R = 0x00080000;		// RF_DATA_ACTIVE
	SIUL2.MSCR[124].R = 0x00080000;		// RF_DATA_OUT_CLK
}

void ioctrl_init(void)
{
	HW_VER_E hw_ver;
	hw_ver = get_hw_ver();

	switch(hw_ver)
	{
		//AMO
		case HW_30693G006030_AMO_RF_BV1p0:
		case HW_30963G006040_AMO_RF_BV2p0:
		case HW_93G006_RAY:
			 comb_amo_ioctrl_init();
			break;
		//DUAL
		case HW_DUAL_BOARD:
			Delay_ms(1);
			DSPI_Init(2, 1, 80000000, 1000000, 0);		//DSPI initialization as a MASTER, RFDF interrupt flag
			//Init FS65xx
			Delay_ms(1);
			dualboard_ioctrl_init();
			break;

		//SINGLE_BOARD
		case HW_SINGLE_BOARD_FS65:
			Delay_ms(1);
			DSPI_Init(2, 1, 80000000, 1000000, 0);		//DSPI initialization as a MASTER, RFDF interrupt flag
			//Init FS65xx
			Delay_ms(1);
			RGM.DES.B.F_LVD_IO = 1;
			RGM.DES.B.F_POR    = 1;
			comb_ioctrl_init();
			break;

		//SINGLE_BOARD
		default:
			RGM.DES.B.F_LVD_IO = 1;
			RGM.DES.B.F_POR    = 1;
			comb_es3_ioctrl_init();
			TJA1145_init();
			clkout_init();
			break;

	}
}


#if 0
void gpo6_level(int level)
{
	uint32_t gpdo;
	gpdo = SIUL2.GPDO[1].R;
	if(level)
		gpdo |= 0x00000100;
	else
		gpdo &= 0xFFFF00FF;
	SIUL2.GPDO[1].R = gpdo;
}


void gpo7_level(int level)
{
	uint32_t gpdo;
	gpdo = SIUL2.GPDO[1].R;
	if(level)
		gpdo |= 0x00000001;
	else
		gpdo &= 0xFFFFFF00;
	SIUL2.GPDO[1].R = gpdo;
}


void gpo6_toggle()
{
	uint32_t gpdo;
	gpdo = SIUL2.GPDO[1].R;
	if(gpdo & 0x00000100)
		gpdo &= 0xFFFF00FF;
	else
		gpdo |= 0x00000100;
	SIUL2.GPDO[1].R = gpdo;
}


void gpo7_toggle()
{
	uint32_t gpdo;
	gpdo = SIUL2.GPDO[1].R;
	if(gpdo & 0x00000001)
		gpdo &= 0xFFFFFF00;
	else
		gpdo |= 0x00000001;
	SIUL2.GPDO[1].R = gpdo;
}
#endif
