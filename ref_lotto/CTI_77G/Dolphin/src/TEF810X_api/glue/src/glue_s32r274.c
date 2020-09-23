/*------------------------------------------------------------------------------*/
/* Copyright(C) NXP B.V. 2016													*/
/*																				*/
/* All rights are reserved. Reproduction in whole or in part is prohibited		*/
/* without the prior written consent of the copy-right owner.					*/
/* This source code and any compilation or derivative thereof is the sole		*/
/* property of NXP B.V. and is provided pursuant to a Software License			*/
/* Agreement. This code is the proprietary information of NXP B.V. and			*/
/* is confidential in nature. Its use and dissemination by any party other		*/
/* than NXP B.V. is strictly limited by the confidential information			*/
/* provisions of the agreement referenced above.								*/
/*																				*/
/* NXP reserves the right to make changes without notice at any time.			*/
/* NXP makes no warranty, expressed, implied or statutory, including but		*/
/* not limited to any implied warranty of merchantability or fitness for any	*/
/* particular purpose, or that the use will not infringe any third party patent,*/
/* copyright or trademark. NXP must not be liable for any loss or damage		*/
/* arising from its use.														*/
/*------------------------------------------------------------------------------*/

/**
*
* @file glue_s32r274.c
*
* @author
*
* @date 04/02/2016
*
* @brief Platform wrapper for SPI functions.
*
*
******************************************************************************/
#include <stdint.h>
#include <dbgprintf.h>
#include <dolphin_cfg.h>
#include <glue.h>
#include <hal_es3_OTP.h>
#include <math.h>
#include <stdlib.h>
#ifdef DOLPHIN_CFG_HOST_S32R274

// #include "rsys_fsv.h" 
// #include "project.h"
// #include "rsys_fsv_cfg.h"
#include "SPI_TEF810X.h"
#include <hal_es3_rshd.h>
// 
#ifdef __cplusplus
extern "C"
{
#endif

#define GLUE_S32R274_CRC_CNTRL_SIGN (0x7500)

static volatile uint32_t tsupd;
static volatile uint32_t timestamp;
static volatile uint32_t startTimeStamp;
// static int STM0Enabled = 0;

static void UpdateTimestamp()
{
	//STM_0 running @ 60MHz
	timestamp += (uint32_t)roundf((STM_1_CNT - tsupd) / 60.0f);

	//save current CNT
	tsupd = STM_1_CNT;

	while (STM_1_CNT - tsupd >= 600)
	{
		timestamp++;
		tsupd += 600;
	}
}

static uint32_t GetTimestamp(void)
{
	UpdateTimestamp();
	return timestamp;
}


enum
{
	SPI_CMD_FLAG_CRC_NE = 0x00,
	SPI_CMD_FLAG_CRC_E  = 0x01
};

enum
{
	SPI_CMD_FLAG_CURRENT = 0x00,
	SPI_CMD_FLAG_STORED  = 0x01
};

enum
{
	SPI_CMD_FLAG_SEQ = 0x00,
	SPI_CMD_FLAG_REPT  = 0x01
};

enum
{
	SPI_CMD_FLAG_READ  = 0x00,
	SPI_CMD_FLAG_WRITE = 0x01
};

uint32_t g_glue_reg_spi_cmd = 0x00;


/* This GPIO to pin bindings are platform specific and need to be set based on
 * hardware configuration.
 */

/*   372 ISM pin defination                  */
#define RSYS_CFG_GPIO_ERROR_RESET (77)    //B15
#define RSYS_CFG_GPIO_READYINT    (43)    //A14
#define RSYS_CFG_GPIO_TX1_PS      (6)     //H17
#define RSYS_CFG_GPIO_TX2_PS      (7)     //A15
#define RSYS_CFG_GPIO_TX3_PS      (8)     //D15
#define RSYS_CFG_GPIO_CHIRP_START (42)    //D14
#define RSYS_CFG_GPIO_ERROR_N     (80)    //B17

static uint8_t rsys_dio_GetDeviceIo(dolphin_ExtPinID_t selectedIO);

static uint8_t rsys_dio_GetDeviceIo(dolphin_ExtPinID_t selectedIO)
{
    uint8_t gpio;
    switch (selectedIO)
    {
        case (int32_t)DOLPHIN_EXTPO_ERRORRESET:
            gpio = RSYS_CFG_GPIO_ERROR_RESET;
            break;
        case (int32_t)DOLPHIN_EXTPO_READYINT:
            gpio = RSYS_CFG_GPIO_READYINT;
            break;
        case (int32_t)DOLPHIN_PI_TX1PS:
            gpio = RSYS_CFG_GPIO_TX1_PS;
            break;
        case (int32_t)DOLPHIN_PI_TX2PS:
            gpio = RSYS_CFG_GPIO_TX2_PS;
            break;
        case (int32_t)DOLPHIN_PI_TX3PS:
            gpio = RSYS_CFG_GPIO_TX3_PS;
            break;
        case (int32_t)DOLPHIN_EXTPIO_CHIRPSTART:
            gpio = RSYS_CFG_GPIO_CHIRP_START;
            break;
        case (int32_t)DOLPHIN_EXTPO_ERRORN:
        default:
            gpio = RSYS_CFG_GPIO_ERROR_N;
            break;
    }
    return gpio;
}



static void glue_xfrom_ErrorCode( retval_e err )
{
	switch( err )
	{
		case SPI_CRC_ERROR:
		{
			g_halerrcode = DOLPHINIC_EC_SPICRCFAILED;
		}
		break;

		default:
		{
			g_halerrcode = DOLPHINIC_NOERROR;
		}
		break;
	}
}

uint32_t glue_CalcParity(uint32_t a){
    uint32_t x = a & 0x7FFFFFFF;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return (((x & 1) * 0x80000000) | (a & 0x7FFFFFFF));
}

DolphinIC_rval_t glue_reg_Write(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReturnedData)
{
	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;
//	uint32_t dev_rd = 0x00;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm2_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm1_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

	//DbgInfo("glue_reg_Write: 0x%x, 0x%x, WriteData:0x%8x\n", ModuleAddress, RegAddress, (uint32_t)WriteData);

	plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, &WriteData, NULL, 0x01, ReturnedData );

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	hal_es3_rshd_UpDateShadow( ModuleAddress, RegAddress, WriteData );

	// Quick Check to analyse the imapct of adding Write Read check ...
	// glue_reg_Read( ModuleAddress, RegAddress, &dev_rd, NULL );
	// HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	// if( dev_rd != WriteData )
	// {
	// 	DbgErr("Err WriteCheck (0x%x::0x%x) Dev(0x%x) Exp(0x%x) \n",
	// 		ModuleAddress,
	// 		RegAddress,
	// 		dev_rd,
	// 		WriteData);
	// 	//HAL_GERRCODE = DOLPHINIC_EC_SPIWRCHKFAILED;
	// }
	//wrc+=1;
	// DbgInfo("Write Mod: %d, Reg: %d\n", ModuleAddress, RegAddress);
	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_BurstWrite(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData)
{

	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm2_SR = (bool)SR_Mode, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm1_SR = (bool)SR_Mode, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

	//DbgInfo("glue_reg_Write: 0x%x, 0x%x, WriteData:0x%8x\n", ModuleAddress, RegAddress, (uint32_t)WriteData);

// #ifndef CASCADE_VAL_BOARD	
//	plferr = SPI_TEF810X_xferDmaMode( ModuleAddress, cmd, RegAddress, WriteData, NULL, NumWords, ReturnedData );
// #else
// 	plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, WriteData, NULL, NumWords, ReturnedData );
// #endif

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_Read(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint32_t *ReturnedData)
{
	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm2_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_READ;
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm1_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm0_RW = (bool)SPI_CMD_FLAG_READ;
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_E;
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

	plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, NULL, ReadData, 0x01, ReturnedData );

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );
	// rdc+=1;
	// DbgInfo(" Read Mod: %d, Reg: %d\n", ModuleAddress, RegAddress);
	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_BurstRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *ReadData, uint8_t NumWords, bool SR_Mode, uint32_t *ReturnedData)
{
	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm2_SR = (bool)SR_Mode, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_READ;
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)SPI_CMD_FLAG_CURRENT, f_cm1_SR = (bool)SR_Mode, f_cm0_RW = (bool)SPI_CMD_FLAG_READ;
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_E;
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

// #ifndef CASCADE_VAL_BOARD	
// 	plferr = SPI_TEF810X_xferDmaMode( ModuleAddress, cmd, RegAddress, NULL, ReadData, NumWords, ReturnedData );
// #else
	plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, NULL, ReadData, NumWords, ReturnedData );
// #endif

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	// brdc+=1;
	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_WriteCheck(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, const uint32_t * ExpData)
{
	HAL_GERRCODE_INIT;
//	uint32_t dev_rd = 0x00;
//	uint32_t exp_val = 0x00;

	//DbgInfo("glue_reg_Write: 0x%x, 0x%x, WriteData:0x%8x\n", ModuleAddress, RegAddress, (uint32_t)WriteData);
	
	if((ModuleAddress==0x0)&&(RegAddress==0x68)) {
		uint32_t mask = 0xFFFFFFFF;
		hal_es3_OTP_checkValidIP(0, &mask, NULL);
		WriteData = WriteData & mask;
	}

	glue_reg_Write( ModuleAddress, RegAddress, WriteData, NULL );
	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	// glue_reg_Read( ModuleAddress, RegAddress, &dev_rd, NULL );
	// HAL_GEC_ASSERT( DOLPHINIC_NOERROR );
	//
	// if( ExpData == NULL )
	// {
	// 	if (ModuleAddress == 0x18) exp_val = glue_CalcParity(WriteData);
	// 	else if ((ModuleAddress == 0x4) && (RegAddress == 0x58)) { //Ignore chirp_start and active profile fields as they are autoclear
	// 		exp_val = WriteData & 0xFFCFFFFE;
	// 		dev_rd = dev_rd & 0xFFCFFFFE;
	// 	}
	// 	else exp_val = WriteData;
	// }
	// else
	// {
	// 	exp_val = *ExpData;
	// }
	
	// if(( dev_rd != exp_val ) &&	(hal_es3_OTP_checkValidIP(ModuleAddress, NULL, NULL)==DOLPHINIC_NOERROR))
	// {
	// 	DbgSpecial("Err WriteCheck (0x%x::0x%x) Dev(0x%x) Exp(0x%x) \n",
	// 		ModuleAddress,
	// 		RegAddress,
	// 		dev_rd,
	// 		exp_val);

	// 	HAL_GERRCODE = DOLPHINIC_EC_SPIWRCHKFAILED;
	// }

	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_WriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t WriteData, uint32_t *ReadData, bool CS_Mode, uint32_t *ReturnedData)
{
	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)CS_Mode, f_cm2_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE; //SPI_CMD_FLAG_REPT
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)CS_Mode, f_cm1_SR = (bool)SPI_CMD_FLAG_SEQ, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE; //SPI_CMD_FLAG_REPT
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_E;
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

	plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, &WriteData, ReadData, 0x01, ReturnedData );

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_reg_BurstWriteRead(uint8_t ModuleAddress, uint16_t RegAddress, uint32_t *WriteData, uint32_t *ReadData, uint8_t NumWords, bool CS_Mode, bool SR_Mode, bool LoopBack, uint32_t *ReturnedData)
{
	HAL_GERRCODE_INIT;
//	DolphinIC_rval_t rval = DOLPHINIC_NOERROR;
	retval_e plferr = SUCCESS;

	uint32_t cmd = 0x00;

	#if defined(DOLPHIN_CFG_ES1)

	bool f_cm3_CS = (bool)CS_Mode, f_cm2_SR = (bool)SR_Mode, f_cm1_Res = 0x00, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	cmd = ( (f_cm3_CS << 0x03) | (f_cm2_SR << 0x02) | (f_cm1_Res << 0x01) | f_cm0_RW );

	#elif defined( DOLPHIN_CFG_ES3 )

	bool f_cm2_CS = (bool)CS_Mode, f_cm1_SR = (bool)SR_Mode, f_cm0_RW = (bool)SPI_CMD_FLAG_WRITE;
	bool f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_NE;

	#if defined(DOLPHIN_CFG_SPI_CMD_CRCCHK_ENABLE)
	f_cm3_CE = (bool)SPI_CMD_FLAG_CRC_E;
	cmd = GLUE_S32R274_CRC_CNTRL_SIGN;
	#endif

	cmd |= ( (f_cm3_CE << 0x03) | (f_cm2_CS << 0x02) | (f_cm1_SR << 0x01) | f_cm0_RW );

	#endif

	g_glue_reg_spi_cmd = cmd;

	if( LoopBack )
	{
		ModuleAddress = ( 0x80 | ModuleAddress );
	}

	if( NumWords < 2 )
	{
		plferr = SPI_TEF810X_xferFifoMode( ModuleAddress, cmd, RegAddress, WriteData, ReadData, NumWords, ReturnedData );
	}
	else
	{
//		plferr = SPI_TEF810X_xferDmaMode( ModuleAddress, cmd, RegAddress, WriteData, ReadData, NumWords, ReturnedData );
	}

	glue_xfrom_ErrorCode( plferr );

	HAL_GEC_ASSERT( DOLPHINIC_NOERROR );

	return HAL_GERRCODE;
}

DolphinIC_rval_t glue_SystemReset( void )
{
	HAL_GERRCODE_INIT;

	//glue_reg_Write(0x0, 0x68, 0x0, NULL); //Turn off all modules, no access on validation board to reset pin

	return HAL_GERRCODE;
}

void __attribute__((optimize("O0"))) glue_Sleep(float ticksInMilliSec)
{
	if (ticksInMilliSec > 0)
		{
			glue_usecSleep(ticksInMilliSec * 1000);
		}
}

void __attribute__((optimize("O0"))) glue_usecSleep(uint32_t ticksInUSec)
{
	/*if (ticksInUSec > 0)
		{
			__asm__ volatile(
					"      mtctr %0 \n"
					"loop2: e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_nop \n"
					"      e_bdnz loop2 \n"*/
					//: /* no outputs */ : "r" (ticksInUSec * TIMEOUT_COUNT_Z4_120MHZ_1US) : /* no clobbers */);
			/*wait += ticksInUSec;
		}*/

		uint32_t j;

		for ( j=0; j < ticksInUSec; j++ )
		{
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
			__asm__ volatile("e_nop");
		}
}

// Platform implementation to set the status for GPIO pin ...
void glue_SetGPIO( dolphin_ExtPinID_t en_pid , bool val )
{
	uint32_t gpioMask;                                // associate out registry mask
    uint8_t  gpioNum = rsys_dio_GetDeviceIo(en_pid);  // get the pin number

    SIUL2.MSCR[gpioNum].R = 0x2850000;                       // enable the output
    gpioMask = (uint32_t)1 << ((3u - (gpioNum % 4u)) * 8u);  // get the pin mask in the registry

    // adjust the output
    if (val == true)
    {
        SIUL2.GPDO[gpioNum / 4u].R |= gpioMask;  // set to high if true
    }
    else
    {
        SIUL2.GPDO[gpioNum / 4u].R &= ~gpioMask;  // clear if false
    }
	// uint8_t gpioNum = rsys_dio_GetDeviceIo(en_pid);

	// switch( en_pid )
	// {
	// 	case DOLPHIN_EXTPO_READYINT:
	// 	case DOLPHIN_EXTPIO_CHIRPSTART:
	// 		/*Enable and disable pin as output here otherwise it affects the signal level of 
	// 		ChirpStart/Ready Int measured by other instruments (or received by slave)*/
	// 		if (val == 1) SIUL2.MSCR[gpioNum].R = 0x28c0000;  // opBuff enable ...
	// 		SIUL2.GPDO[gpioNum].R = val;
	// 		if (val == 0){
	// 			glue_usecSleep(1);
	// 			SIUL2.MSCR[gpioNum].R = 0x8c0000; // inBuff enable ...
	// 		}
	// 		break;
	// 	default:
	// 		//error_reset <-> GPIO[8]
	// 		SIUL2.GPDO[gpioNum].R = val;
	// 		break;
	// }

}

// Platform implementation to read the status of GPIO ...
void glue_GetGPIO( dolphin_ExtPinID_t en_pid , bool * val )
{
	uint32_t regVal;                                    // registry value
    uint32_t gpioMask;                                  // pin associated mask
	uint8_t gpioNum = rsys_dio_GetDeviceIo(en_pid);     // pin number
    SIUL2.MSCR[gpioNum].R = 0x008c0000;                 // input enable
    glue_usecSleep(1u);
    gpioMask = (uint32_t)1 << ((3u - (gpioNum % 4u)) * 8u);
    regVal = SIUL2.GPDI[gpioNum / 4u].R;  // read the registry
    if ((regVal & gpioMask) != 0u)
    {
        *val = true;  // the input is high
    }
    else
    {
        *val = false;  // the input is low
    }
	// bool result = false;
	// uint8_t gpioNum = rsys_dio_GetDeviceIo(en_pid);
	// uint8_t rounded = gpioNum == 0?0:gpioNum/4;
	// uint8_t nibble =  gpioNum == 0?0:gpioNum % 4;
	// switch(nibble){
	// 	case 1:
	// 		result = SIUL2.GPDI[rounded].B.PDI_4n1;
	// 		break;
	// 	case 2:
	// 		result = SIUL2.GPDI[rounded].B.PDI_4n2;
	// 		break;
	// 	case 3:
	// 		result = SIUL2.GPDI[rounded].B.PDI_4n3;
	// 		break;
	// 	default:
	// 	case 0:
	// 		result = SIUL2.GPDI[rounded].B.PDI_4n;
	// 		break;
	// }
	// *val = result;
}

void glue_CaptureHostTrigger( void )
{
	// Trigger the Teng for chirping ...
	chip_TE_ChirpStart();
}

bool glue_CaptureTestPattern( void )
{
	// retval_t sptrval = SUCCESS;

	// sptrval = SPT_wait_frame_acq();

	// if( sptrval == SUCCESS )
	// {
		return( true );
	// }

	// DbgErr("Data Capture Failed (%d) \n", sptrval);

	return( false );
}

bool glue_CheckTestPattern( void )
{
	// uint16_t * acq_buff = NULL;
	// uint16_t * sampl_buff = NULL;
	// uint32_t spad_reg1 = 0x00;
	// uint32_t no_samples = ( DOLPHIN_CFG_FSM_PROF3_NSAMPLES / DOLPHIN_CFG_FSM_PROF3_DEC_FACT );
	// uint32_t adc_sample_size = 0x02;
	// uint32_t rx_active = 0x04;

	// //get base address of the memory ...
	// acq_buff = ( uint16_t * ) SHARED_SRAM_ADDR;

	// for(uint32_t loop_chirp = 0x00; loop_chirp < DOLPHIN_CFG_FSM_PROF3_NCHIRPS; loop_chirp++ )
	// {
	// 	for(uint32_t loop_samples = 0x00; loop_samples < no_samples; loop_samples++ )
	// 	{
	// 		spad_reg1 = 0x00;
	// 		uint32_t buff_index = (loop_chirp * (no_samples * (rx_active * adc_sample_size))) + (loop_samples * (rx_active * adc_sample_size));
	// 		//DbgInfo("[%d][%d][%d]::",loop_chirp,loop_samples,buff_index);
	// 		sampl_buff = (uint16_t *)(&acq_buff[ buff_index / adc_sample_size]);
	// 		//DbgInfo("0x%x, 0x%x, 0x%x, 0x%x \n", ( sampl_buff[0] >> 3 ), ( sampl_buff[1] >> 3 ), ( sampl_buff[2] >> 3 ), ( sampl_buff[3] >> 3 ) );

	// 		spad_reg1 += ( sampl_buff[0] >> 3 );
	// 		spad_reg1 += ( sampl_buff[1] >> 3 );
	// 		spad_reg1 += ( sampl_buff[2] >> 3 );
	// 		spad_reg1 += ( sampl_buff[3] >> 3 );

	// 		spad_reg1 /= rx_active;

	// 		if( spad_reg1 != DOLPHIN_CFG_FSM_CSI2_DATAPATTERN )
	// 		{
	// 			DbgInfo("Test Pattern mismatch expec(0x%x):act(0x%x) \n", DOLPHIN_CFG_FSM_CSI2_DATAPATTERN, spad_reg1);
	// 			return( false );
	// 		}
	// 	}
	// }

	// DbgInfo("Data Pattern check OK !!!\n");
	return( true );
}

void glue_Tic()
{
	startTimeStamp = GetTimestamp();
}

float glue_Toc()
{
	float timeSpentNanoSec = (float)((GetTimestamp() - startTimeStamp) * 1000);
	DbgInfo("%f nanoSec (%.2f uSec) has passed since last tic().\n", timeSpentNanoSec, timeSpentNanoSec / 1000.0f);

	return timeSpentNanoSec;
}

#ifdef __cplusplus
}
#endif

#endif //DOLPHIN_CFG_HOST_S32R274
