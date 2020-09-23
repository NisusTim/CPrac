/*
 * bl_image_security.c
 *
 *  Created on: 2018/12/10
 *      Author: WoodLiu
 */

#include "bl_image_security.h"
#include "bl_data_cfg.h"

void encryption(bl_Buffer_t *buf, bl_BufferSize_t len, bl_u16_t offset);
void decryption(bl_Buffer_t *buf, bl_BufferSize_t len, bl_u16_t offset);

bl_u8_t swapBits(bl_u8_t x, bl_u8_t p1, bl_u8_t p2, bl_u8_t n);

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

void image_encryption(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len)
{
    bl_u16_t offset = 0;

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
		else if(addr >= BL_IMAGE_SECURITY_START_ADDR && addr < DM_DATA_2_LOCAL_ADDR)
		{
			encryption(buf, len, offset);
		}
	}
}

void image_decryption(bl_Address_t addr, bl_Buffer_t *buf, bl_BufferSize_t len)
{
    bl_u16_t offset = 0;

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
		else if(addr >= BL_IMAGE_SECURITY_START_ADDR && addr < DM_DATA_2_LOCAL_ADDR)
		{
			decryption(buf, len, offset);
		}
	}
}

void Image_ChecksumInit(void)
{
    g_ImgVerOps.Init();
}

void Image_StartChecksum(void)
{
    g_ImgVerOps.Start();
}

bl_Return_t Image_UpdateChecksum(bl_Address_t addr, bl_Size_t size, const bl_Buffer_t *data)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    ret = g_ImgVerOps.Update(addr, size, data);

    return ret;
}

bl_Return_t Image_VerifyChecksum(void)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    ret = g_ImgVerOps.Verify();

    return ret;
}

void encryption(bl_Buffer_t *buf, bl_BufferSize_t len, bl_u16_t offset)
{
    bl_u8_t high_bit = 0;
	bl_u8_t low_bit = 0;
	bl_u16_t i = 0;
	bl_u8_t data;

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

void decryption(bl_Buffer_t *buf, bl_BufferSize_t len, bl_u16_t offset)
{
    bl_u8_t high_bit = 0;
    bl_u8_t low_bit = 0;
    bl_u16_t i = 0;
    bl_u8_t data;

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

bl_u8_t swapBits(bl_u8_t x, bl_u8_t p1, bl_u8_t p2, bl_u8_t n)
{
    /* Move all bits of first set to rightmost side */
    bl_u8_t set1 =  (x >> p1) & ((1U << n) - 1);

    /* Move all bits of second set to rightmost side */
    bl_u8_t set2 =  (x >> p2) & ((1U << n) - 1);

    /* XOR the two sets */
    bl_u8_t xor = (set1 ^ set2);

    /* Put the xor bits back to their original positions */
    xor = (xor << p1) | (xor << p2);

    /* XOR the 'xor' with the original number so that the
       two sets are swapped */
    bl_u8_t result = x ^ xor;

    return result;
}


