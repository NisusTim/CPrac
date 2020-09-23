/*
 * Utility.h
 *
 *  Created on: 2016�~12��13��
 *      Author: Bruce Chang
 */

#ifndef UTILITY_H_
#define UTILITY_H_

//#define ABS(x)      (((x) < 0) ? -(x) : (x))
//#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)

void Delay_us(uint16_t dly_us);
void Delay_ms(uint16_t dly_ms);

#define ASCENDING_ORDER 1
#define DESCENDING_ORDER 0
void bubble_sort(float array[], int length, int order);



#endif /* UTILITY_H_ */
