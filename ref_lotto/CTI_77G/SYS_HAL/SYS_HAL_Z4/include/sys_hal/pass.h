/*
 * pass.h
 *
 *  Created on: 2017��10��5��
 *      Author: user
 */

#ifndef PASS_H_
#define PASS_H_

void pass_func(char** args, int count);
void write_n_enable_pass_module();
int check_DBL_lock(void);
int get_cns_state(void);
int get_LIFE_state(void);
void pass_init(void);

#endif /* PASS_H_ */
