/*
 * I2C_api.h
 *
 *  Created on: 2019¦~1¤ë25¤é
 *      Author: user
 */

#ifndef SYS_HAL_I2C_I2C_API_H_
#define SYS_HAL_I2C_I2C_API_H_

#include "event.h"

#define SIZE_OF_I2C_QUE		480
#define SIZE_OF_I2C_TASK	20
#define SIZE_OF_ZERO		0
#define SIZE_OF_ONE			1
#define SIZE_OF_TWO			2

#define TYPE_WRITE			0
#define TYPE_READ			1

typedef enum
{
	E_I2C_TASK_IDEL = 0,
	E_I2C_TASK_CREATION = 1,
	E_I2C_TASK_PROCESSING = 2,
	E_I2C_TASK_DONE = 3,
	E_I2C_TASK_NO_ACK = 4
}E_I2C_TASK_STATUS;

typedef enum
{
	E_I2C_OK = 0,
	E_I2C_BUFFER_FULL,
	E_I2C_OUTOFRANGE,
	E_I2C_BUSBUSY,
	E_I2C_TASK_FULL,
	E_I2C_COMM_ERR,
	E_I2C_FATEL_ERR
}E_I2C_STATUS;

typedef struct
{
	char* name;
	event_proc_p callback;
	uint8_t slaveAddress;
	uint8_t reg;
	uint8_t	*buf_p;
	uint8_t len;
	uint8_t	block;
}i2c1_input_info_t;

typedef struct
{
	char* name;
	event_proc_p callback;
	uint8_t	tx_data_index;
	uint8_t rx_data_index;
	uint8_t block;
	uint8_t	tx_size;
	uint8_t	rx_size;
	uint8_t tx_cnt;
	uint8_t rx_cnt;
	uint8_t status;
}i2c_task_t;

typedef struct{
	uint8_t msg[SIZE_OF_I2C_QUE];
	i2c_task_t task[SIZE_OF_I2C_TASK];
	uint16_t used_index;
	uint8_t task_head;
	uint8_t task_tail;
}i2c_handle_t,*i2c_handle_p;

void HAL_I2C_Register(void);

extern void i2c1_Isr(void);
extern void init_i2c1_handle_queue(void);
extern uint8_t i2c1_SendMsg(i2c1_input_info_t i2c1_info);
extern uint8_t i2c1_ReadMsg(i2c1_input_info_t i2c1_info);
extern void i2c1_get_task_reg(uint8_t *bufp,uint8_t task);
extern void i2c1_get_task_rx_len(uint8_t *bufp,uint8_t task);
extern void i2c1_copy_data_from_task(uint8_t *bufp,uint8_t task);
extern uint8_t i2c1_get_block_task_index(void);
#endif /* SYS_HAL_I2C_I2C_API_H_ */
