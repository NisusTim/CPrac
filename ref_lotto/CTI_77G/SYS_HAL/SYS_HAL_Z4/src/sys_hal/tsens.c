/*
 * tsens.c
 *
 *  Created on: 2017��8��28��
 *      Author: user
 */


#include "sys_shared.h" /* include peripheral declarations */

#define SAMPLE_TIME			20

static int16_t K1_0, K2_0, K3_0, K4_0;
static int16_t K1_1, K2_1, K3_1, K4_1;
static uint16_t Vbg0_code, Vbg1_code, TSENS0_code, TSENS1_code;

static float TSENS0_T, TSENS1_T;

int get_Vbg0_code(void)
{
	ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
        while (ADC_0.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg0_code = ADC_0.CDR[10].B.CDATA;

    //PRINTF("Vbg0_code   = %d \n\r", Vbg0_code);

	//SIUL2.GPDO[0].R ^= 0x1;
	return (int)Vbg0_code;
}

float get_mcu_temperature(void)
{
	float temp1 = 0,temp2 = 0;
	float rtvl = 0;

	int cnt;
	static uint8_t times = SAMPLE_TIME;
	float samples[times];
	int remove_cnt = times * 0.2;
	float retrieve_cnt = 0;

	float total_val = 0;

	for(cnt = 0;cnt<times;cnt++)
	{
		// TSEN0 temperature calculation
		ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
		while (ADC_0.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
		Vbg0_code = ADC_0.CDR[10].B.CDATA;
		TSENS0_code = ADC_0.CDR[15].B.CDATA;

		temp1 = K1_0 * Vbg0_code / 2 + K2_0 * TSENS0_code * 8;
		temp2 = (K3_0 * Vbg0_code * 4 + K4_0 * TSENS0_code) * 0.0009765625;

		TSENS0_T = temp1 / temp2 / 4 - 273.15;

		samples[cnt] = TSENS0_T;
	}

	retrieve_cnt = 0;
	for(cnt = remove_cnt ; cnt < times - remove_cnt ; cnt++)
	{
		retrieve_cnt++;
		total_val += samples[cnt];
	}

	rtvl = total_val / retrieve_cnt;

	return rtvl;
}


int get_tsens0(void)
{
	float temp1,temp2;

	// TSEN0 temperature calculation
	ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
        while (ADC_0.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg0_code = ADC_0.CDR[10].B.CDATA;
	TSENS0_code = ADC_0.CDR[15].B.CDATA;

	temp1 = K1_0 * Vbg0_code / 2 + K2_0 * TSENS0_code * 8;
	temp2 = (K3_0 * Vbg0_code * 4 + K4_0 * TSENS0_code) * 0.0009765625;

	TSENS0_T = temp1 / temp2 / 4 - 273.15;

#if DEBUG_TSENS
    PRINTF("Vbg0_code   = %d \t\t Vbg1_code   = %d\n\r", Vbg0_code , Vbg1_code );
    PRINTF("TSENS0_code = %d \t\t TSENS1_code = %d\n\r", TSENS0_code , TSENS1_code );
#endif
    //PRINTF("TSENS0 temp = %.2f degC \r", TSENS0_T);


	//SIUL2.GPDO[0].R ^= 0x1;
	return (int)TSENS0_T;
}

int get_Vbg1_code(void)
{
	// TSEN1 temperature calculation
	ADC_1.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC1 */
        while (ADC_1.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg1_code = ADC_1.CDR[10].B.CDATA;

    //PRINTF("Vbg1_code   = %d\n\r", Vbg1_code );

	//SIUL2.GPDO[0].R ^= 0x1;
	return (int)Vbg1_code;
}


int get_tsens1(void)
{
	float temp1,temp2;
#if 0
	// TSEN0 temperature calculation
	ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
        while (ADC_0.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg0_code = ADC_0.CDR[10].B.CDATA;
	TSENS0_code = ADC_0.CDR[15].B.CDATA;

	temp1 = K1_0 * Vbg0_code / 2 + K2_0 * TSENS0_code * 8;
	temp2 = (K3_0 * Vbg0_code * 4 + K4_0 * TSENS0_code) * 0.0009765625;

	TSENS0_T = temp1 / temp2 / 4 - 273.15;
#endif
	// TSEN1 temperature calculation
	ADC_1.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC1 */
        while (ADC_1.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg1_code = ADC_1.CDR[10].B.CDATA;
	TSENS1_code = ADC_1.CDR[15].B.CDATA;

	temp1 = K1_1 * Vbg1_code / 2 + K2_1 * TSENS1_code * 8;
	temp2 = (K3_1 * Vbg1_code * 4 + K4_1 * TSENS1_code) * 0.0009765625;

	TSENS1_T = temp1 / temp2 / 4 - 273.15;
#if DEBUG_TSENS
    PRINTF("Vbg0_code   = %d \t\t Vbg1_code   = %d\n\r", Vbg0_code , Vbg1_code );
    PRINTF("TSENS0_code = %d \t\t TSENS1_code = %d\n\r", TSENS0_code , TSENS1_code );
#endif
    //PRINTF("TSENS1 temp = %.2f degC\r", TSENS1_T);


	//SIUL2.GPDO[0].R ^= 0x1;
	return (int)TSENS1_T;
}

void print_tsens(char** args, int count)
{
	float temp1,temp2;

	// TSEN0 temperature calculation
	ADC_0.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC0 */
        while (ADC_0.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg0_code = ADC_0.CDR[10].B.CDATA;
	TSENS0_code = ADC_0.CDR[15].B.CDATA;

	temp1 = K1_0 * Vbg0_code / 2 + K2_0 * TSENS0_code * 8;
	temp2 = (K3_0 * Vbg0_code * 4 + K4_0 * TSENS0_code) * 0.0009765625;

	TSENS0_T = temp1 / temp2 / 4 - 273.15;

	// TSEN1 temperature calculation
	ADC_1.MCR.B.NSTART=1;           /* Trigger normal conversions for ADC1 */
        while (ADC_1.CDR[15].B.VALID != 1) {}; /* Wait for last scan to complete */
	Vbg1_code = ADC_1.CDR[10].B.CDATA;
	TSENS1_code = ADC_1.CDR[15].B.CDATA;

	temp1 = K1_1 * Vbg1_code / 2 + K2_1 * TSENS1_code * 8;
	temp2 = (K3_1 * Vbg1_code * 4 + K4_1 * TSENS1_code) * 0.0009765625;

	TSENS1_T = temp1 / temp2 / 4 - 273.15;
#if DEBUG_TSENS
    PRINTF("Vbg0_code   = %d \t\t Vbg1_code   = %d\n\r", Vbg0_code , Vbg1_code );
    PRINTF("TSENS0_code = %d \t\t TSENS1_code = %d\n\r", TSENS0_code , TSENS1_code );
#endif
    //PRINTF("TSENS0 temp = %.2f degC \t TSENS1 temp = %.2f degC\r", TSENS0_T, TSENS1_T);


	//SIUL2.GPDO[0].R ^= 0x1;
}

void print_Vbg_core(char** args, int count)
{
    PRINTF("Vbg0_code = %d\n\r", get_Vbg0_code());
    PRINTF("Vbg1_code = %d\n\r", get_Vbg1_code());

}


/*******************************************************************************
Function Name : ADC_Init
Engineer      : PetrS
Date          : Apr-16-2015
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : ADCs initialization
Issues        : NONE
*******************************************************************************/
void ADC_Init(void)
{

    ADC_0.MCR.R	= 0x80000000;	// enable result overwriting in scan mode
    //ADC_0.CTR1.R = 0x00000016;	// setup conversion time, max value
    ADC_0.CTR1.B.INPSAMP = 0xFF;
    ADC_0.NCMR0.R |= 0x00008400;	// enable channels 10 (Vbdg), 15 (TSENS0) to be sampled


    ADC_1.MCR.R	= 0x80000000;	// enable result overwriting in scan mode
    //ADC_1.CTR1.R = 0x00000016;	// setup conversion time, max value
    ADC_1.CTR1.B.INPSAMP = 0xFF;
    ADC_1.NCMR0.R |= 0x00008400;	// enable channels 10 (Vbdg), 15 (TSENS1) to be sampled

}



void tsens_init(void)
{
    uint16_t *testFlashPtr =(uint16_t*) 0x04000C0;

    // Read TSENS calibration constants from Test Flash
    K1_0 = *testFlashPtr++;
    K2_0 = *testFlashPtr++;
    K3_0 = *testFlashPtr++;
    K4_0 = *testFlashPtr++;
    K1_1 = *testFlashPtr++;
    K2_1 = *testFlashPtr++;
    K3_1 = *testFlashPtr++;
    K4_1 = *testFlashPtr;

#if DEBUG_TSENS
    PRINTF("Calibration constants read from Test Flash\n\r");
    PRINTF("\n\r");
    PRINTF("TSENS0 \t\t\t\t TSENS1\n\r");
    PRINTF("\n\r");
    PRINTF("K1 = %d \t\t\t K1 = %d \n\r", K1_0, K1_1);
    PRINTF("K2 = %d \t\t\t K2 = %d \n\r", K2_0, K2_1);
    PRINTF("K3 = %d \t\t\t K3 = %d \n\r", K3_0, K3_1);
    PRINTF("K4 = %d \t\t\t K4 = %d \n\r", K4_0, K4_1);
    PRINTF("\n\r");
    PRINTF("     K1 * Vbg_code * 2^-1 + K2 * TSENS_code * 2^3\n\r");
    PRINTF("T = ---------------------------------------------- / 4 - 273.15 [degC]\n\r");
    PRINTF("    [K3 * Vbg_code * 2^2 + K4 * TSENS_code] * 2^-10\n\r");
    PRINTF("\n\r");
#endif

}

