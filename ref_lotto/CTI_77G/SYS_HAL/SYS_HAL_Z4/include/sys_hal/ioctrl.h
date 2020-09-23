/*
 * ioctrl.h
 *
 *  Created on: 2017�~1��3��
 *      Author: erichu
 */

#ifndef IOCTRL_H_
#define IOCTRL_H_

typedef enum
{
	SINGLE_BOARD = 0,
	DUAL_BOARD
}hardware_type_e;

void ioctrl_init(void);
void set_gpio(uint8_t index, uint8_t op);
uint8_t get_gpio(uint8_t index);

#endif /* IOCTRL_H_ */
