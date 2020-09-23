/*
 * I2C_api.c
 *
 *  Created on: 2019/1/25
 *      Author: user
 */

#include "sys_shared.h"
#include <stdint.h>

void clear_task(uint8_t task_index);

static i2c_handle_t i2c1_handle;

//#define I2C_PRINTF_DEBUG
#define WRITE_CMD_TX_SIZE					2
#define READ_CMD_TX_SIZE					3

#define WRITE(addr)							(addr & 0xFE)
#define READ(addr)							(addr | 0x01)
//#define WRITE(addr)							0xD6//ISM330DLC_WRITE_ADDRESS
//#define READ(addr)							0xD7//ISM330DLC_READ_ADDRESS
#define TAIL_TASK_INDEX						i2c1_handle.task_tail
#define HEAD_TASK_INDEX						i2c1_handle.task_head
#define USED_INDEX							i2c1_handle.used_index
#define BLOCK(index)						i2c1_handle.task[index].block
#define TX_CNT(index)						i2c1_handle.task[index].tx_cnt
#define RX_CNT(index)						i2c1_handle.task[index].rx_cnt
#define TX_SIZE(index)						i2c1_handle.task[index].tx_size
#define RX_SIZE(index)						i2c1_handle.task[index].rx_size
#define TX_DATA_START_POSITION(index)		i2c1_handle.task[index].tx_data_index
#define RX_DATA_START_POSITION(index)		i2c1_handle.task[index].rx_data_index
#define NOW_TX_DATA_POSITION(index)			((TX_DATA_START_POSITION(index) + TX_CNT(index)) % SIZE_OF_I2C_QUE)
#define NOW_RX_DATA_POSITION(index)			((RX_DATA_START_POSITION(index) + (RX_CNT(index) - SIZE_OF_ONE)) % SIZE_OF_I2C_QUE)
#define MSG_TX(index)						i2c1_handle.msg[NOW_TX_DATA_POSITION(index)]
#define MSG_RX(index)						i2c1_handle.msg[NOW_RX_DATA_POSITION(index)]
#define MSG(index)							i2c1_handle.msg[index]
#define CALLBACK(index)						i2c1_handle.task[index].callback
#define CALLBACKNAME(index)					i2c1_handle.task[index].name
#define TASK_STATUS(index)					i2c1_handle.task[index].status

static uint8_t sg_last_block_task_index = 0;
void clear_task(uint8_t task_index);
extern void Reinit_I2C();
//extern void I2C_Init(I2C_ConfigType *pI2CConfig);

uint8_t i2c1_get_block_task_index(void)
{
	return sg_last_block_task_index;
}

static void i2c1_sendFirstMsg(void)
{
    TX_CNT(TAIL_TASK_INDEX) = 0;
	I2C_MasterTransmit(&I2C_1,MSG_TX(TAIL_TASK_INDEX));
	TX_CNT(TAIL_TASK_INDEX)++;
	TASK_STATUS(TAIL_TASK_INDEX) = E_I2C_TASK_PROCESSING;
}

static void i2c1_StartandFirstMsg(void)
{
	I2C_Start(&I2C_1);
	i2c1_sendFirstMsg();
#ifdef I2C_PRINTF_DEBUG
	PRINTF("Tri_ST\n");
	PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
}


void i2c1_Isr(void)
{
	static uint8_t err_cnt = 0;
	uint8_t stop_cnt = 0;
	I2C_ClearIBIF(&I2C_1);
	if(TAIL_TASK_INDEX != HEAD_TASK_INDEX)
	{
		if(I2C1_IsI2CMaster())
		{
			if(I2C_NOBUSY == I2C_IsBusy(&I2C_1))
			{
			    i2c1_StartandFirstMsg();
#ifdef I2C_PRINTF_DEBUG
				PRINTF("Have ISR ST\n");
				PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
			}
			else
			{
				if(I2C_IsTxMode(&I2C_1))
				{
					if((TX_SIZE(TAIL_TASK_INDEX) == TX_CNT(TAIL_TASK_INDEX))
							&& (RX_SIZE(TAIL_TASK_INDEX) == SIZE_OF_ZERO))
					{
						I2C_Stop(&I2C_1);

						TASK_STATUS(TAIL_TASK_INDEX) = E_I2C_TASK_DONE;
						if(CALLBACK(TAIL_TASK_INDEX) != NULL)
						{
							put_event((char*)CALLBACKNAME(TAIL_TASK_INDEX), (event_proc_p)CALLBACK(TAIL_TASK_INDEX), (void*)(intptr_t)TAIL_TASK_INDEX);

							if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
			                {
			                    TAIL_TASK_INDEX = 0;
			                }
			                else
			                {
			                    TAIL_TASK_INDEX++;
			                }

#ifdef I2C_PRINTF_DEBUG
							PRINTF("tx put_event\n");
							PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
						}
						else
						{
							if(BLOCK(TAIL_TASK_INDEX))
							{
								sg_last_block_task_index = TAIL_TASK_INDEX;
							}
							else
							{
								clear_task(TAIL_TASK_INDEX);
							}

                            if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
                            {
                                TAIL_TASK_INDEX = 0;
                            }
                            else
                            {
                                TAIL_TASK_INDEX++;
                            }

#ifdef I2C_PRINTF_DEBUG
							PRINTF("tx no put event\n");
							PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
						}
					}
					else
					{
						if(I2C_IsNoAck(&I2C_1))//Tx and NO ACK
						{
							PRINTF("Tx NO ACK h:%d,t:%d,err:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX,err_cnt);
							//No Ack handle
							I2C_Stop(&I2C_1);
							while(I2C_ISBUSY == I2C_IsBusy(&I2C_1) && (stop_cnt < 10))
							{
								Delay_us(5);
								I2C_Stop(&I2C_1);
								PRINTF("Tx NO ACK h:%d,t:%d,err:%d,stop:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX,err_cnt,stop_cnt);
								stop_cnt++;
							}
							err_cnt++;


							if(BLOCK(TAIL_TASK_INDEX))
							{
								sg_last_block_task_index = TAIL_TASK_INDEX;
								TASK_STATUS(TAIL_TASK_INDEX) = E_I2C_TASK_NO_ACK;
							}
							else
							{
								clear_task(TAIL_TASK_INDEX);

	                            if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
	                            {
	                                TAIL_TASK_INDEX = 0;
	                            }
	                            else
	                            {
	                                TAIL_TASK_INDEX++;
	                            }
							}
						}
						else
						{
							if((TX_SIZE(TAIL_TASK_INDEX) == TX_CNT(TAIL_TASK_INDEX))
									&& (RX_SIZE(TAIL_TASK_INDEX) != SIZE_OF_ZERO))
							{
								if(RX_SIZE(TAIL_TASK_INDEX) == SIZE_OF_ONE)
								{
									I2C_SetNoAckState(&I2C_1,I2C_NO_ACK);
								}
								else
								{
									I2C_SetNoAckState(&I2C_1,I2C_ACK);
								}
								I2C_SetTxRxState(&I2C_1,I2C_RX);
								(void)I2C_ReadData(&I2C_1);//Dummy
								RX_CNT(TAIL_TASK_INDEX)++;
							}
							else
							{
								if(((TX_SIZE(TAIL_TASK_INDEX) - SIZE_OF_ONE) == TX_CNT(TAIL_TASK_INDEX))
										&& (RX_SIZE(TAIL_TASK_INDEX) != SIZE_OF_ZERO))
								{
									I2C_Restart(&I2C_1);
									I2C_ClearIBIF(&I2C_1);
									I2C_MasterTransmit(&I2C_1,MSG_TX(TAIL_TASK_INDEX));
									TX_CNT(TAIL_TASK_INDEX)++;
								}
								else
								{
									I2C_MasterTransmit(&I2C_1,MSG_TX(TAIL_TASK_INDEX));
									TX_CNT(TAIL_TASK_INDEX)++;
								}
							}
						}
					}
				}
				else
				{
					if(RX_CNT(TAIL_TASK_INDEX) == RX_SIZE(TAIL_TASK_INDEX))
					{
						I2C_Stop(&I2C_1);
						MSG_RX(TAIL_TASK_INDEX) = I2C_ReadData(&I2C_1);

                        TASK_STATUS(TAIL_TASK_INDEX) = E_I2C_TASK_DONE;

						if(CALLBACK(TAIL_TASK_INDEX) != NULL)
						{
							put_event((char*)CALLBACKNAME(TAIL_TASK_INDEX), (event_proc_p)CALLBACK(TAIL_TASK_INDEX), (void*)(intptr_t)TAIL_TASK_INDEX);

							if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
			                {
			                    TAIL_TASK_INDEX = 0;
			                }
			                else
			                {
			                    TAIL_TASK_INDEX++;
			                }

#ifdef I2C_PRINTF_DEBUG
							PRINTF("rx put event\n");
							PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
						}
						else
						{
							if(BLOCK(TAIL_TASK_INDEX))
							{
								sg_last_block_task_index = TAIL_TASK_INDEX;
							}
							else
							{
								clear_task(TAIL_TASK_INDEX);
							}

							if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
			                {
			                    TAIL_TASK_INDEX = 0;
			                }
			                else
			                {
			                    TAIL_TASK_INDEX++;
			                }

#ifdef I2C_PRINTF_DEBUG
							PRINTF("rx no put event\n");
							PRINTF("h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
#endif
						}
					}
					else
					{
						if((RX_SIZE(TAIL_TASK_INDEX) - SIZE_OF_ONE) == RX_CNT(TAIL_TASK_INDEX))
						{
							I2C_SetNoAckState(&I2C_1,I2C_NO_ACK);
						}
						else
						{
							I2C_SetNoAckState(&I2C_1,I2C_ACK);
						}
						MSG_RX(TAIL_TASK_INDEX) = I2C_ReadData(&I2C_1);
						RX_CNT(TAIL_TASK_INDEX)++;
					}
				}
			}
		}
		else
		{
			//Slave Handle
		}
	}
}

void init_i2c1_handle_queue(void)
{
	uint16_t u16temp;
	i2c_task_t task_reset = {0};

	for(u16temp = 0; u16temp <SIZE_OF_I2C_QUE; u16temp++)
		i2c1_handle.msg[u16temp] = 0;
	for(u16temp = 0; u16temp <SIZE_OF_I2C_TASK; u16temp++)
		i2c1_handle.task[u16temp] = task_reset;
	USED_INDEX = 0;
	HEAD_TASK_INDEX = 0;
	TAIL_TASK_INDEX = 0;
}

void clear_task(uint8_t task_index)
{
	i2c_task_t task_reset = {0};
	i2c1_handle.task[task_index] = task_reset;
}

static uint8_t put_i2c1_msg(i2c1_input_info_t i2c1_info,uint8_t type)
{
	uint8_t err = E_I2C_OK;
	uint8_t u8temp;

//	if(((HEAD_TASK_INDEX - TAIL_TASK_INDEX) & (SIZE_OF_I2C_QUE - SIZE_OF_ONE)) > (SIZE_OF_I2C_QUE - SIZE_OF_TWO))
//	{
//		return E_I2C_BUFFER_FULL;
//	}
//	while(((HEAD_TASK_INDEX - TAIL_TASK_INDEX) & (SIZE_OF_I2C_QUE - SIZE_OF_ONE)) > (SIZE_OF_I2C_QUE - SIZE_OF_TWO))
//	{
//		//wait
//		//return E_I2C_BUFFER_FULL;
//	}
	if(TX_SIZE(HEAD_TASK_INDEX) != 0)
		return E_I2C_TASK_FULL;

	switch(type)
	{
		case TYPE_WRITE:
			TX_SIZE(HEAD_TASK_INDEX) = (WRITE_CMD_TX_SIZE + i2c1_info.len);
			TX_CNT(HEAD_TASK_INDEX) = 0;
			RX_SIZE(HEAD_TASK_INDEX) = 0;
			RX_CNT(HEAD_TASK_INDEX) = 0;
			BLOCK(HEAD_TASK_INDEX) = i2c1_info.block;
			TX_DATA_START_POSITION(HEAD_TASK_INDEX) = USED_INDEX;
			RX_DATA_START_POSITION(HEAD_TASK_INDEX) = ((USED_INDEX + TX_SIZE(HEAD_TASK_INDEX)) % SIZE_OF_I2C_QUE );
			USED_INDEX = ((USED_INDEX + TX_SIZE(HEAD_TASK_INDEX) + RX_SIZE(HEAD_TASK_INDEX)) % SIZE_OF_I2C_QUE);

			MSG(TX_DATA_START_POSITION(HEAD_TASK_INDEX)) = WRITE(i2c1_info.slaveAddress);
			MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + SIZE_OF_ONE) % SIZE_OF_I2C_QUE) = i2c1_info.reg;
			CALLBACK(HEAD_TASK_INDEX) = i2c1_info.callback;
			CALLBACKNAME(HEAD_TASK_INDEX) = i2c1_info.name;
			for(u8temp=0;u8temp<i2c1_info.len;u8temp++)
			{
				MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + SIZE_OF_TWO + u8temp) % SIZE_OF_I2C_QUE) = *(i2c1_info.buf_p + u8temp);
			}
#ifdef I2C_PRINTF_DEBUG
			PRINTF("put write buf(t:%d)(r:%d)(u:%d):\n",TX_DATA_START_POSITION(HEAD_TASK_INDEX),RX_DATA_START_POSITION(HEAD_TASK_INDEX),USED_INDEX);
			for(u8temp = 0;u8temp<(TX_SIZE(HEAD_TASK_INDEX)+RX_SIZE(HEAD_TASK_INDEX));u8temp++)
				PRINTF("%2x ",MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + u8temp) % SIZE_OF_I2C_QUE));

			PRINTF("\n");
#endif
			TASK_STATUS(HEAD_TASK_INDEX) = E_I2C_TASK_CREATION;

            if(HEAD_TASK_INDEX == SIZE_OF_I2C_TASK-1)
            {
                HEAD_TASK_INDEX = 0;
            }
            else
            {
                HEAD_TASK_INDEX++;
            }

			break;

		case TYPE_READ:
			TX_SIZE(HEAD_TASK_INDEX) = (READ_CMD_TX_SIZE);
			TX_CNT(HEAD_TASK_INDEX) = 0;
			RX_SIZE(HEAD_TASK_INDEX) = i2c1_info.len;
			RX_CNT(HEAD_TASK_INDEX) = 0;
			BLOCK(HEAD_TASK_INDEX) = i2c1_info.block;
			TX_DATA_START_POSITION(HEAD_TASK_INDEX) = USED_INDEX;
			RX_DATA_START_POSITION(HEAD_TASK_INDEX) = ((USED_INDEX + TX_SIZE(HEAD_TASK_INDEX)) % SIZE_OF_I2C_QUE);
			USED_INDEX = ((USED_INDEX + TX_SIZE(HEAD_TASK_INDEX) + RX_SIZE(HEAD_TASK_INDEX)) % SIZE_OF_I2C_QUE);
			MSG(TX_DATA_START_POSITION(HEAD_TASK_INDEX)) = WRITE(i2c1_info.slaveAddress);
			MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + SIZE_OF_ONE) % SIZE_OF_I2C_QUE) = i2c1_info.reg;
			MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + SIZE_OF_TWO) % SIZE_OF_I2C_QUE)= READ(i2c1_info.slaveAddress);
			CALLBACK(HEAD_TASK_INDEX) = i2c1_info.callback;
			CALLBACKNAME(HEAD_TASK_INDEX) = i2c1_info.name;
			for(u8temp=0;u8temp<i2c1_info.len;u8temp++)
			{
				MSG((RX_DATA_START_POSITION(HEAD_TASK_INDEX) + u8temp) % SIZE_OF_I2C_QUE) = 0xFF;
			}
#ifdef I2C_PRINTF_DEBUG
			PRINTF("put read buf(t:%d)(r:%d)(u:%d):\n",TX_DATA_START_POSITION(HEAD_TASK_INDEX),RX_DATA_START_POSITION(HEAD_TASK_INDEX),USED_INDEX);
			for(u8temp = 0;u8temp<(TX_SIZE(HEAD_TASK_INDEX)+RX_SIZE(HEAD_TASK_INDEX));u8temp++)
				PRINTF("%2x ",MSG((TX_DATA_START_POSITION(HEAD_TASK_INDEX) + u8temp) % SIZE_OF_I2C_QUE));

			PRINTF("\n");
#endif
			TASK_STATUS(HEAD_TASK_INDEX) = E_I2C_TASK_CREATION;

            if(HEAD_TASK_INDEX == SIZE_OF_I2C_TASK-1)
            {
                HEAD_TASK_INDEX = 0;
            }
            else
            {
                HEAD_TASK_INDEX++;
            }

			break;

		default:
			err = E_I2C_OUTOFRANGE;
			break;
	}

	return err;
}


static uint8_t i2c1_CheckTxTrigger(void)
{
	uint8_t st = E_I2C_OK;
	if(((TAIL_TASK_INDEX + SIZE_OF_ONE) % SIZE_OF_I2C_TASK) == HEAD_TASK_INDEX)
	{
		if(I2C_NOBUSY == I2C_IsBusy(&I2C_1))
		{
			i2c1_StartandFirstMsg();
		}
		else
		{
			st = E_I2C_BUSBUSY;
			//Error Handle
			PRINTF("E_I2C_BUSBUSY:t%d,h:%d\n",TAIL_TASK_INDEX, HEAD_TASK_INDEX);

		}
	}
	return st;
}

uint8_t i2c1_SendMsg(i2c1_input_info_t i2c1_info)
{
	uint8_t st = E_I2C_OK;
	st = put_i2c1_msg(i2c1_info,TYPE_WRITE);
	if(E_I2C_OK == st)
	{
		st = i2c1_CheckTxTrigger();

	}

	if(E_I2C_BUSBUSY == st)
	{
		if(E_I2C_TASK_PROCESSING != TASK_STATUS(TAIL_TASK_INDEX))
		{
			PRINTF("W_BUSY_HANDLE\n");
			Reinit_I2C();
			init_i2c1_handle_queue();
			return E_I2C_FATEL_ERR;
		}
	}

	if(i2c1_info.block)
	{
		#ifdef ENABLE_SWT
		clear_SWT0_counter();
		#endif

		while(TAIL_TASK_INDEX != HEAD_TASK_INDEX)
		{
			if(E_I2C_TASK_NO_ACK == TASK_STATUS((TAIL_TASK_INDEX + (SIZE_OF_I2C_TASK-1))%SIZE_OF_I2C_TASK))
			{
				PRINTF("SEND NO ACK CLEAR h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
				clear_task(TAIL_TASK_INDEX);

                if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
                {
                    TAIL_TASK_INDEX = 0;
                }
                else
                {
                    TAIL_TASK_INDEX++;
                }

				return E_I2C_COMM_ERR;
			}
		}
	}

	return st;
}

uint8_t i2c1_ReadMsg(i2c1_input_info_t i2c1_info)
{
	uint8_t st = E_I2C_OK;
	st = put_i2c1_msg(i2c1_info,TYPE_READ);
	if(E_I2C_OK == st)
	{
		st = i2c1_CheckTxTrigger();
	}

	if(E_I2C_BUSBUSY == st)
	{
		if(E_I2C_TASK_PROCESSING != TASK_STATUS(TAIL_TASK_INDEX))
		{
			PRINTF("R_BUSY_HANDLE\n");
			Reinit_I2C();
			init_i2c1_handle_queue();
			return E_I2C_FATEL_ERR;
		}
	}

	if(i2c1_info.block)
	{
		#ifdef ENABLE_SWT
		clear_SWT0_counter();
		#endif

		while(TAIL_TASK_INDEX != HEAD_TASK_INDEX)
		{
			if(E_I2C_TASK_NO_ACK == TASK_STATUS((TAIL_TASK_INDEX + (SIZE_OF_I2C_TASK-1))%SIZE_OF_I2C_TASK))
			{
				PRINTF("READ NO ACK CLEAR h:%d,t:%d\n",HEAD_TASK_INDEX,TAIL_TASK_INDEX);
				clear_task(TAIL_TASK_INDEX);

                if(TAIL_TASK_INDEX == SIZE_OF_I2C_TASK-1)
                {
                    TAIL_TASK_INDEX = 0;
                }
                else
                {
                    TAIL_TASK_INDEX++;
                }

				return E_I2C_COMM_ERR;
			}
		}
	}

	return st;
}

void i2c1_get_task_reg(uint8_t *bufp,uint8_t task)
{
	*bufp = MSG(TX_DATA_START_POSITION(task) + SIZE_OF_ONE);
}

void i2c1_get_task_rx_len(uint8_t *bufp,uint8_t task)
{
	*bufp = RX_SIZE(task);
}

void i2c1_copy_data_from_task(uint8_t *bufp,uint8_t task)
{
	uint8_t u8temp;
	if(RX_SIZE(task) != SIZE_OF_ZERO)
	{
		for(u8temp = 0;u8temp<RX_SIZE(task);u8temp++)
		{
			*(bufp + u8temp) = MSG((RX_DATA_START_POSITION(task) + u8temp) % SIZE_OF_I2C_QUE);
		}
	}
	clear_task(task);
}

