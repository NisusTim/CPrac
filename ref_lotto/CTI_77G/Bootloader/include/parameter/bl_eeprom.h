/*
 * eeprom.h
 *
 *  Created on: 2017¦~10¤ë31¤é
 *      Author: erichu
 */

#ifndef BL_EEPROM_H_
#define BL_EEPROM_H_

#include "S32R274.h"
#include "bl_typedefs.h"

#define SIZE_OF_EE_MEM_BLOCK		0x4000
#define EEPROM_PAGE_SIZE			32

// EEprom Memory blocks
#define EE_MEM_BLOCK_0              0x00800000
#define EE_MEM_BLOCK_1              0x00804000
#define EE_MEM_BLOCK_2              0x00808000
#define EE_MEM_BLOCK_3              0x0080C000

#define EE_ADDR_PARAS_START0		(EE_MEM_BLOCK_0)
#define EE_ADDR_PARAS_START1		(EE_MEM_BLOCK_1)
#define EE_ADDR_FCCU_START			(EE_MEM_BLOCK_2)

void eeprom_erase(bl_u32_t);
void eeprom_write(bl_u32_t, void*, bl_u16_t);
void eeprom_write64(bl_u32_t, bl_u64_t);
void ee_tester(char**, int);

#endif /* EEPROM_H_ */
