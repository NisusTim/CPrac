/*
 * tsens.h
 *
 *  Created on: 2017��8��28��
 *      Author: user
 */

#ifndef TSENS_H_
#define TSENS_H_

void tsens_init(void);
void print_tsens(char** args, int count);
int get_tsens0(void);
int get_tsens1(void);
float get_mcu_temperature(void);

void print_Vbg_core(char** args, int count);
int get_Vbg1_code(void);
int get_Vbg0_code(void);
void ADC_Init(void);

#endif /* TSENS_H_ */
