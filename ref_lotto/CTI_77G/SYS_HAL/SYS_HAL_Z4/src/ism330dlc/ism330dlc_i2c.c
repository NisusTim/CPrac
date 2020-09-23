/*
 * ism330dlc_i2c.c
 *
 *  Created on: 2019/1/25
 *      Author: user
 */

#include "sys_shared.h"



void I2C_RegisterConfig(I2C_ConfigType *pI2CConfig)
{
	pI2CConfig->sSetting.bMDIS       = 0;        /* enable I2C module                   */
	pI2CConfig->sSetting.bIBIE       = 1;        /* enable I2C interrupt                */
	pI2CConfig->sSetting.bMSSL       = 1;        /* master node                         */
	pI2CConfig->sSetting.bBIIE		 = 1;
	pI2CConfig->uBitrate             = 400;      /* bit rate = 400 kHz                  */
	pI2CConfig->uAddress             = 0;    	 /*  no slave address                	*/
	pI2CConfig->i2cx = (volatile struct I2C_tag*)&I2C_1;
}


void ism330dlc_i2c_init(void)
{
	I2C_ConfigType  sI2CConfig1;
	I2C_ConfigType  *pI2C_Config1 = &sI2CConfig1;
	I2C_RegisterConfig(pI2C_Config1);
//	I2C_RegisterInit(pI2C_Config1);
	I2C1_Init(pI2C_Config1);
	init_i2c1_handle_queue();
}
