/*
 * sbc_fs8x_adc.c
 *
 *  Created on: 2018�~8��2��
 *      Author: user
 */

#include "sys_shared.h"
#include "sbc_fs8x_adc.h"

#define ADC0_AN0_PIN		23
#define MSCR_INPUT       	0x00400000  // Input buffer enabled, Input hysteresis
#define SAMPLE_TIME			5

void fs8x_adc_init(void)
{
	//	I/O
	SIUL2.MSCR[ADC0_AN0_PIN].R = MSCR_INPUT;

	//	ADC
    ADC_0.MCR.R	= 0x80000000;	// enable result overwriting in scan mode
    ADC_0.CTR1.B.INPSAMP = 0xFF;
    ADC_0.NCMR0.R |= 0x00000001;	// enable channels 0 (amux)
}

float fs8x_sample_amux_adc(void)
{
	//float   start, end;
	uint16_t adc_val = 0;
	uint32_t total_val = 0;
	float voltage;
	int cnt;
	//start = STM_0.CNT.R;
	static uint8_t times = SAMPLE_TIME;
	float samples[times];
	int remove_cnt = 2;
	int retrieve_cnt = 0;

	for(cnt = 0;cnt<times;cnt++)
	{
		ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
		while (ADC_0.CDR[0].B.VALID != 1) {}; /* Wait for last scan to complete */

	    adc_val = ADC_0.CDR[0].B.CDATA;

	    samples[cnt] = adc_val;
	}

	retrieve_cnt = 0;
	for(cnt = remove_cnt ; cnt < times ; cnt++)
	{
		retrieve_cnt++;
		total_val += samples[cnt];
	}

    voltage = (float)total_val/retrieve_cnt/ 4095 * 3.3;
	//end = STM_0.CNT.R;
	//PRINTF("Get %d adc time: %d us\n",cnt,(int)((end - start)*16.7/1000));
    return voltage;
}
