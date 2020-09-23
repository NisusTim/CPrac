/*
 * hw_ver.c
 *
 *  Created on: 2018¦~10¤ë12¤é
 *      Author: user
 */


#include "S32R274.h"
#include "Utility.h"
#include "hw_ver.h"
#include "sbc_fs8x.h"
#include "FS65xx_driver.h"

#define ADC1_AN0_PIN		29
#define ADC1_AN1_PIN		30
#define ADC1_AN2_PIN		31
#define ADC1_AN3_PIN		32
#define MSCR_INPUT       	0x00400000  // Input buffer enabled, Input hysteresis
#define SAMPLE_TIME			50

#define DEVIATION_VOLTAGE	0.1
#define HW_VOLTAGE1			3.195
#define HW_VOLTAGE2			2.797
#define HW_VOLTAGE3			2.481
#define HW_VOLTAGE4			2.057
#define HW_VOLTAGE5			1.650

static HW_VER_E hw_ver = 0;




typedef struct
{
	float adc1_0;
	float adc1_1;
	float adc1_2;
	float adc1_3;
}hw_table;


const hw_table hw_ver_table[] = {
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1},//HW_93G002_COMBO_BSD_MASTER_BV3p3_MINNA
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2},//HW_93G002_COMBO_BSD_SLAVE_BV1p3
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE3},//HW_BSD_PIECE_BV1p0
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE4},//HW_AM_LKQ_79G_COMBO_BSD_BV2p0
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE5},//HW_93G003_BV3p2p1_30693G003190
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE1},//HW_30693G006030_AMO_RF_BV1p0
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE2},//HW_30963G006040_AMO_RF_BV2p0
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE3},//HW_93G007_COMBO_BSD_MASTER_BV3p3_HAITEC
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE4},//HW_93G007_COMBO_BSD_SLAVE_BV1p3_HAITEC
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE5},//HW_93G006_RAY
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE4, HW_VOLTAGE4},//HW_93G003_COMBO_FRONT_RADAR_BV3p3
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE5, HW_VOLTAGE4}, //HW_93G003_COMBO_FRONT_RADAR_BV3p4
		{HW_VOLTAGE1, HW_VOLTAGE1, HW_VOLTAGE5, HW_VOLTAGE2}, //HW_93G014_MRR_BV1p0_FOR_HIRAIN
        {HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE1, HW_VOLTAGE2},//HW_93G014_MRR_BV2p1_FOR_HIRAIN
        {HW_VOLTAGE1, HW_VOLTAGE2, HW_VOLTAGE1, HW_VOLTAGE3} //HW_93G016_MRR_BV2p1_FOR_HIRAIN_S32R264
};

static void check_hw_ver(hw_table v_source)
{
	uint8_t i;
	for(i=0;i<HW_INVALID;i++)
	{
		if(
			(v_source.adc1_0 < (hw_ver_table[i].adc1_0 + DEVIATION_VOLTAGE))
			&&(v_source.adc1_0 > (hw_ver_table[i].adc1_0 - DEVIATION_VOLTAGE))
			&&(v_source.adc1_1 < (hw_ver_table[i].adc1_1 + DEVIATION_VOLTAGE))
			&&(v_source.adc1_1 > (hw_ver_table[i].adc1_1 - DEVIATION_VOLTAGE))
			&&(v_source.adc1_2 < (hw_ver_table[i].adc1_2 + DEVIATION_VOLTAGE))
			&&(v_source.adc1_2 > (hw_ver_table[i].adc1_2 - DEVIATION_VOLTAGE))
			&&(v_source.adc1_3 < (hw_ver_table[i].adc1_3 + DEVIATION_VOLTAGE))
			&&(v_source.adc1_3 > (hw_ver_table[i].adc1_3 - DEVIATION_VOLTAGE))
		)
		{
			break;
		}
	}
	if(i < HW_INVALID)
	{
		hw_ver = (HW_VER_E)i;
	}
	else
	{
		FS8x_init();
		if(fs8x_init_ok == get_fs8x_status())
		{
			hw_ver = HW_SINGLE_BOARD_FS85_84;
		}
		else
		{
			if(FS65_Init() == 0)
			{
				hw_ver = HW_SINGLE_BOARD_FS65;
			}
			else
			{
				hw_ver = HW_DUAL_BOARD;
			}
		}
	}

}
static void hw_ver_adc_init(void)
{
	//	I/O
	SIUL2.MSCR[ADC1_AN0_PIN].R = MSCR_INPUT;
	SIUL2.MSCR[ADC1_AN1_PIN].R = MSCR_INPUT;
	SIUL2.MSCR[ADC1_AN2_PIN].R = MSCR_INPUT;
	SIUL2.MSCR[ADC1_AN3_PIN].R = MSCR_INPUT;

	//	ADC
    ADC_1.MCR.R	= 0x80000000;	// enable result overwriting in scan mode
    ADC_1.CTR1.B.INPSAMP = 0xFF;
    ADC_1.NCMR0.R |= 0x0000000F;	// enable channels 0 (amux)
}


float get_sample_amux_adc1(uint8_t ch)
{
	//float   start, end;
	uint16_t adc_val = 0;
	uint32_t total_val = 0;
	float voltage;
	int cnt;
	//start = STM_0.CNT.R;
	static uint8_t times = SAMPLE_TIME;
	float samples[times];
	int remove_cnt = times * 0.2;
	int retrieve_cnt = 0;

	for(cnt = 0;cnt<times;cnt++)
	{
		ADC_1.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
		while (ADC_1.CDR[ch].B.VALID != 1) {}; /* Wait for last scan to complete */

	    adc_val = ADC_1.CDR[ch].B.CDATA;

	    samples[cnt] = adc_val;
	}

	bubble_sort(samples, times, ASCENDING_ORDER);

	retrieve_cnt = 0;
	for(cnt = remove_cnt ; cnt < times - remove_cnt ; cnt++)
	{
		retrieve_cnt++;
		total_val += samples[cnt];
	}

    voltage = (float)total_val/retrieve_cnt/ 4095 * 3.3;
	//end = STM_0.CNT.R;
	//PRINTF("Get %d adc time: %d us\n",cnt,(int)((end - start)*16.7/1000));
    return voltage;
}



void hw_ver_info_init(void)
{
	hw_table volatge;
	hw_ver_adc_init();
	volatge.adc1_0 = get_sample_amux_adc1(0);
	volatge.adc1_1 = get_sample_amux_adc1(1);
	volatge.adc1_2 = get_sample_amux_adc1(2);
	volatge.adc1_3 = get_sample_amux_adc1(3);
	check_hw_ver(volatge);
}

HW_VER_E get_hw_ver(void)
{
	return hw_ver;
}
