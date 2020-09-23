/*******************************************************************************
* NXP Semiconductors
* (c) Copyright 2016 NXP Semiconductors
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without any 
warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be held
liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED 
TO THE PROJECT BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES. 
IN NO EVENT SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THIS AGREEMENT. 
CUSTOMER agrees to hold NXP harmless against any and all claims demands 
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result 
of the advise or assistance supplied CUSTOMER in connection with product, 
services or goods supplied under this Agreement.
********************************************************************************
* File:             I2C.h
* Owner:            PetrS
* Version:          0.1
* Date:             Mar-25-2016
* Classification:   General Business Information
* Brief:            Function prototypes of the simple I2C driver
********************************************************************************
********************************************************************************
* Detailed Description:
********************************************************************************
Revision History:
Ver  Date         Author        Description of Changes
0.1  Mar-25-2016  PetrS		Initial version
*******************************************************************************/
#ifndef _I2C_2_H_
#define _I2C_2_H_

/*******************************************************************************
* Includes
*******************************************************************************/
//#include "typedefs.h"

/*******************************************************************************
* Constants
*******************************************************************************/

/*******************************************************************************
* Macros 
*******************************************************************************/
#define I2C1_VECTOR				442
#define I2C_C_MDIS_MASK         0x80u
#define I2C_C_IBIE_MASK         0x40u
#define I2C_GET_DATA			0
#define I2C_SET_DATA			1
#define I2C_MASTER_MODE			1
#define I2C_SLAVE_MODE			0
#define I2C_NO_ACK				1
#define I2C_ACK					0
#define I2C_TX					1
#define I2C_RX					0
#define I2C_ISBUSY				1
#define I2C_NOBUSY				0
/*******************************************************************************
* Macros Function
*******************************************************************************/

/*******************************************************************************
* Types
*******************************************************************************/
typedef struct
{
	uint8_t bMDIS          :1;     			    /*!< 1: disable I2C module
	                                                 0: enable  I2C module                   */
	uint8_t bIBIE          :1;    			 	/*!< 1: enable  I2C interrupt
	                                                 0: disable I2C interrupt                */
	uint8_t bMSSL          :1;    			 	/*!< 1: master node  0: slave node           */
	uint8_t bBIIE          :1;
}I2C_SettingType;


typedef struct
{
	volatile struct I2C_tag*	i2cx;        /* I2C module */
    I2C_SettingType sSetting;
    uint16_t uBitrate;                          /*!< setting the bit rate (kHz) for I2C      */
    uint8_t uAddress;                           /*!< slave address                           */
}I2C_ConfigType, *I2C_ConfigPtr;

/*******************************************************************************
* Global variables
*******************************************************************************/
   
/*******************************************************************************
* Global functions
*******************************************************************************/
void HAL_I2C_Module_Register(void);

extern void I2C_SetTxRxState(volatile struct I2C_tag *pI2Cx , uint8_t txrx_st);
extern void I2C_SetNoAckState(volatile struct I2C_tag *pI2Cx , uint8_t ack_st);
extern uint8_t I2C_IsNoAck(volatile struct I2C_tag *pI2Cx);
extern uint8_t I2C_ReadData(volatile struct I2C_tag *pI2Cx);
extern uint8_t I2C_IsBusy(volatile struct I2C_tag *pI2Cx);
extern void I2C_MasterTransmit(volatile struct I2C_tag *pI2Cx,uint8_t data);
extern void I2C_Stop(volatile struct I2C_tag *pI2Cx);
extern void I2C_Start(volatile struct I2C_tag *pI2Cx);
extern void I2C_Restart(volatile struct I2C_tag *pI2Cx);
extern void I2C_ClearIBIF(volatile struct I2C_tag *pI2Cx);
extern void I2C1_Init(I2C_ConfigType *pI2CConfig);
extern uint8_t I2C_IsTxMode(volatile struct I2C_tag *pI2Cx);
extern uint8_t I2C1_IsI2CMaster(void);
extern void I2C_RegisterInit(I2C_ConfigType *pI2CConfig);
extern void I2C1_GetSetMasterSlaveMode(uint8_t method,uint8_t* data);

#endif
