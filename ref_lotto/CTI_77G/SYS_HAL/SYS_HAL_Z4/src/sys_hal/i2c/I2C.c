// I2C 

#include "sys_shared.h"


static I2C_ConfigType config = {NULL};
static void _store_configuration(I2C_ConfigType* user_config);

void I2C_MasterTransmit(volatile struct I2C_tag *pI2Cx,uint8_t data)
{
	pI2Cx->IBDR.R = data;
}

void I2C_Stop(volatile struct I2C_tag *pI2Cx)
{
	pI2Cx->IBCR.B.MSSL = 0;        /* master generate stop    */
}

void I2C_Start(volatile struct I2C_tag *pI2Cx)
{
	pI2Cx->IBCR.B.TXRX = I2C_TX;
	pI2Cx->IBCR.B.MSSL = I2C_MASTER_MODE;
}


void I2C_ClearIBIF(volatile struct I2C_tag *pI2Cx)
{
	pI2Cx->IBSR.B.IBIF = 1;
}

void I2C_Restart(volatile struct I2C_tag *pI2Cx)
{
	pI2Cx->IBCR.B.RSTA = 1;
}

void I2C_SetNoAckState(volatile struct I2C_tag *pI2Cx , uint8_t ack_st)
{
	pI2Cx->IBCR.B.NOACK = ack_st;
}

void I2C_SetTxRxState(volatile struct I2C_tag *pI2Cx , uint8_t txrx_st)
{
	pI2Cx->IBCR.B.TXRX = txrx_st;
}

uint8_t I2C_ReadData(volatile struct I2C_tag *pI2Cx)
{
	return pI2Cx->IBDR.R;
}

uint8_t I2C_IsBusy(volatile struct I2C_tag *pI2Cx)
{
	return pI2Cx->IBSR.B.IBB;
}

uint8_t I2C_IsNoAck(volatile struct I2C_tag *pI2Cx)
{
	return pI2Cx->IBSR.B.RXAK;
}

uint8_t I2C_IsTxMode(volatile struct I2C_tag *pI2Cx)
{
	return pI2Cx->IBCR.B.TXRX;
}

uint8_t I2C1_IsI2CMaster(void)
{
	uint8_t mode = 0;
	I2C1_GetSetMasterSlaveMode(I2C_GET_DATA,&mode);
	return mode;
}

/***********************************************************************************************
*
* @brief     I2C_SetSlaveAddress - set slave address.
*
* @param[in] pI2Cx           - point to I2C module type
* @param[in] u8SlaveAddress  - slave address
*
* @return    none
*
************************************************************************************************/
static void I2C_SetSlaveAddress(volatile struct I2C_tag *pI2Cx, uint8_t u8SlaveAddress)
{
    pI2Cx->IBAD.R = u8SlaveAddress;
}

static void I2C_SetBitRate(volatile struct I2C_tag *pI2Cx, uint16_t uBitRate)
{
    switch(uBitRate)
    {
        /* divider = Fpb / bit rate = 60MHz / 100kHz = 600 */
        /* select  divider = 576, IBFD.B.IBC = 0x2C        */
        case 100: pI2Cx->IBFD.B.IBC = 0x2C; break;
        /* divider = Fpb / bit rate = 60MHz / 200kHz = 300 */
        /* select  divider = 288, IBFD.B.IBC = 0x24        */
        case 200: pI2Cx->IBFD.B.IBC = 0x24; break;
        /* divider = Fpb / bit rate = 60MHz / 400kHz = 150 */
        /* select  divider = 144, IBFD.B.IBC = 0x1C        */
        case 400: pI2Cx->IBFD.B.IBC = 0x1C; break;
        /* divider = Fpb / bit rate = 60MHz / 250kHz = 240 */
        /* select  divider = 240, IBFD.B.IBC = 0x1F        */
        default:  pI2Cx->IBFD.B.IBC = 0x1F; break;
    }
}




void I2C1_GetSetMasterSlaveMode(uint8_t method,uint8_t* data)
{
	static uint8_t MasterSlaveMode = I2C_SLAVE_MODE;
	if(I2C_SET_DATA == method)
	{
		MasterSlaveMode = *data;
	}
	else
	{
		*data = MasterSlaveMode;
	}
}



void I2C_RegisterInit(I2C_ConfigType *pI2CConfig)
{
    uint8_t u8Temp = pI2CConfig->sSetting.bMSSL;

    I2C_ClearIBIF(pI2CConfig->i2cx);
	I2C_SetBitRate(pI2CConfig->i2cx, pI2CConfig->uBitrate);
	I2C1_GetSetMasterSlaveMode(I2C_SET_DATA,&u8Temp);
	if (pI2CConfig->sSetting.bMSSL == 0)
	{
		I2C_SetSlaveAddress(pI2CConfig->i2cx, pI2CConfig->uAddress);
	}
	/* configure IBCR control register */
	u8Temp = 0;
	if( pI2CConfig->sSetting.bMDIS )
	{
		u8Temp |= I2C_C_MDIS_MASK;
	}
	if( pI2CConfig->sSetting.bIBIE )
	{
		u8Temp |= I2C_C_IBIE_MASK;
	}
	pI2CConfig->i2cx->IBCR.R = u8Temp;
	if(	pI2CConfig->sSetting.bBIIE)
	{
		pI2CConfig->i2cx->IBIC.B.BIIE = 1;
	}
}

static void I2C1_IsrInit(void)
{
	INTC.PSR[I2C1_VECTOR].R = 0x8001; //set I2C1 interrupt core and priority
}

static void I2C1_IOInit(void)
{
    SIUL2.MSCR[119].R = 0x128C0004;  /* Pad PH7: Module: I2C_1,
                                       Function: SCL*/
    SIUL2.MSCR[120].R = 0x338C0004;  /* Pad PH8: Module: I2C_1,
									Function: SDA */
    SIUL2.IMCR[88].R = 0x2;        /* Connected to pad PH7  */
    SIUL2.IMCR[89].R = 0x2;        /* Connected to pad PH8  */
}

static void _store_configuration(I2C_ConfigType* user_config)
{
	memcpy(&config, user_config, sizeof(I2C_ConfigType));
}

void I2C1_Init(I2C_ConfigType *pI2CConfig)
{
	if(NULL != pI2CConfig)
	{
		_store_configuration(pI2CConfig);
		if(pI2CConfig->i2cx == (volatile struct I2C_tag*)&I2C_1)
		{
			I2C1_IOInit();
			I2C1_IsrInit();
		}

		I2C_RegisterInit(pI2CConfig);
	}
}

void Reinit_I2C()
{
	if(config.i2cx == (volatile struct I2C_tag*)&I2C_1)
	{
		I2C_ConfigType disable_settings = {0};
		PRINTF("[Debug]: Reinit_I2C Start\n");

		disable_settings.sSetting.bMDIS       = 1;        /* Disable I2C module                   */
		disable_settings.sSetting.bIBIE       = 0;        /* Disable I2C interrupt                */
		disable_settings.sSetting.bMSSL       = 0;        /* slave node                          */
		disable_settings.sSetting.bBIIE		  = 0;
		disable_settings.uBitrate             = 0;        /* bit rate = 0 Hz                     */
		disable_settings.uAddress             = 0;    	 /*  no slave address    				*/
		disable_settings.i2cx = (volatile struct I2C_tag*)&I2C_1;

		I2C_RegisterInit(&disable_settings);
		PRINTF("[Debug]: Disable I2C\n");

		I2C_RegisterInit(&config);
		PRINTF("[Debug]: Enable I2C\n");
		PRINTF("[Debug]: Reinit_I2C End\n");
	}
}
