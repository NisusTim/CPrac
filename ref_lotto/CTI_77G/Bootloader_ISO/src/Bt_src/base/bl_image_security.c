/*
 * bl_image_security.c
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#include "bl_image_security.h"

void encryption(uint8_t *buf, uint16_t len, uint16_t offset);
void decryption(uint8_t *buf, uint16_t len, uint16_t offset);

uint8_t swapBits(uint8_t x, uint8_t p1, uint8_t p2, uint8_t n);

const char encryptionTableList[16] =
{
	0x00,	//0
	0x06,	//1
	0x03,	//2
	0x0C,	//3
	0x0B,	//4
	0x09,	//5
	0x05,	//6
	0x04,	//7
	0x0F,	//8
	0x0D,	//9
	0x07,	//A
	0x01,	//B
	0x02,	//C
	0x0E,	//D
	0x0A,	//E
	0x08	//F
};

const char decryptionTableList[16] =
{
	0x00,	//0
	0x0B,	//1
	0x0C,	//2
	0x02,	//3
	0x07,	//4
	0x06,	//5
	0x01,	//6
	0x0A,	//7
	0x0F,	//8
	0x05,	//9
	0x0E,	//A
	0x04,	//B
	0x03,	//C
	0x09,	//D
	0x0D,	//E
	0x08	//F
};

#define SWAP_P1 	2
#define SWAP_P2		5
#define SWAP_N		2

void image_encryption(uint32_t addr, uint8_t *buf, uint16_t len)
{
	uint16_t offset = 0;

	if(addr >= BL_IMAGE_Z4_START_ADDR && addr <= BL_IMAGE_SECURITY_END_ADDR)
	{
		if(addr < BL_IMAGE_SECURITY_START_ADDR)
		{
			if(addr + len > BL_IMAGE_SECURITY_START_ADDR)
			{
				offset = BL_IMAGE_SECURITY_START_ADDR - addr;
				len = addr + len - BL_IMAGE_SECURITY_START_ADDR;
				encryption(buf, len, offset);
			}
		}
		else
		{
			encryption(buf, len, offset);
		}
	}
}

void image_decryption(uint32_t addr, uint8_t *buf, uint16_t len)
{
	uint16_t offset = 0;

	if(addr >= BL_IMAGE_Z4_START_ADDR && addr <= BL_IMAGE_SECURITY_END_ADDR)
	{
		if(addr < BL_IMAGE_SECURITY_START_ADDR)
		{
			if(addr + len > BL_IMAGE_SECURITY_START_ADDR)
			{
				offset = BL_IMAGE_SECURITY_START_ADDR - addr;
				len = (addr + len - BL_IMAGE_SECURITY_START_ADDR);
				decryption(buf, len, offset);
			}
		}
		else
		{
			decryption(buf, len, offset);
		}

	}
}

void encryption(uint8_t *buf, uint16_t len, uint16_t offset)
{
	uint8_t high_bit = 0;
	uint8_t low_bit = 0;
	uint16_t i = 0;
	uint8_t data;

	for (i = offset ; i < len + offset; i++)
	{
		data = swapBits(buf[i], SWAP_P1, SWAP_P2, SWAP_N);
		high_bit = data >> 4;
		low_bit = data & 0x0F;

		high_bit = encryptionTableList[high_bit];
		low_bit = encryptionTableList[low_bit];

		buf[i] = high_bit << 4 | low_bit;
	}
}

void decryption(uint8_t *buf, uint16_t len, uint16_t offset)
{
	uint8_t high_bit = 0;
	uint8_t low_bit = 0;
	uint16_t i = 0;
	uint8_t data;

	for (i = offset ; i < len + offset; i++)
	{
		high_bit = buf[i] >> 4;
		low_bit = buf[i] & 0x0F;

		high_bit = decryptionTableList[high_bit];
		low_bit = decryptionTableList[low_bit];

		data = swapBits(high_bit << 4 | low_bit, SWAP_P1, SWAP_P2, SWAP_N);
		buf[i] = data;
	}
}

uint8_t swapBits(uint8_t x, uint8_t p1, uint8_t p2, uint8_t n)
{
    /* Move all bits of first set to rightmost side */
	uint8_t set1 =  (x >> p1) & ((1U << n) - 1);

    /* Move all bits of second set to rightmost side */
	uint8_t set2 =  (x >> p2) & ((1U << n) - 1);

    /* XOR the two sets */
	uint8_t xor = (set1 ^ set2);

    /* Put the xor bits back to their original positions */
    xor = (xor << p1) | (xor << p2);

    /* XOR the 'xor' with the original number so that the
       two sets are swapped */
    uint8_t result = x ^ xor;

    return result;
}


