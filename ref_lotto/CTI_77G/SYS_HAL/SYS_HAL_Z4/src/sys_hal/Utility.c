/*
 * Utility.c
 *
 *  Created on: 2016�~12��13��
 *      Author: Bruce Chang
 */

#include "typedefs.h"
#include "Utility.h"



//=============================================================================
// Delay X ms Functions
//=============================================================================

void Delay_us(uint16_t dly_us)
{

	uint16_t i;
	uint32_t j;


	for(i = 0; i < dly_us; i++)
	{
		for(j=0; j<8; j++)
		{
			__asm("");
		}
	}
}


//=============================================================================
// Delay X ms Functions
//=============================================================================

void Delay_ms(uint16_t dly_ms)
{

	uint16_t i;
	uint32_t j;


	for(i = 0; i < dly_ms; i++)
	{
		for(j=0; j<10000; j++)
		{
			__asm("");
		}
	}
}

void bubble_sort(float array[], int length, int order)
{
    int i, j, swapped;

    for(i = length - 1 ; i > 0 ; --i)
    {
        swapped = FALSE;

        for(j = 0 ; j < i ; ++j)
        {
            if(order == ASCENDING_ORDER)
            {
                if(array[j] > array[j+1])
                {
                    SWAP(array[j], array[j+1], float);
                    swapped = TRUE;
                }
            }
            else
            {
                if(array[j] < array[j+1])
                {
                    SWAP(array[j], array[j+1], float);
                    swapped = TRUE;
                }
            }
        }

        if(swapped == FALSE)
        {
            break;
        }
    }
}

