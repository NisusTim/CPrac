#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include"linear_regression.h"

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
static float arithmetic_mean(float* data, int size);

// --------------------------------------------------------
// FUNCTION linear_regression
// --------------------------------------------------------
void linear_regression(float* independent, float* dependent, int size, LRModel* model)
{
	float independent_mean = arithmetic_mean(independent, size);
	float dependent_mean = arithmetic_mean(dependent, size);
	//float products_mean = mean_of_products(independent, dependent, size);
	//float independent_variance = variance(independent, size);
	float Lxx = 0.0f;
	float Lxy = 0.0f;
	uint16_t cnt;
	for (cnt = 0; cnt < size; cnt ++)
	{
		Lxy += powf((independent[cnt] - independent_mean), 2);
		Lxx += (independent[cnt] - independent_mean) * (dependent[cnt] - dependent_mean);
	}
	if (Lxy == 0) {
		Lxy = 0.0000001f;
	}
	model->a = Lxx / Lxy;
	model->b = dependent_mean - (model->a * independent_mean);
}

//--------------------------------------------------------
// FUNCTION arithmetic_mean
//--------------------------------------------------------
static float arithmetic_mean(float* data, int size)
{
	float total = 0;
	int i;

	// note that incrementing total is done within the for loop
	for (i = 0; i < size; total += data[i], i++);

	return total / size;
}

