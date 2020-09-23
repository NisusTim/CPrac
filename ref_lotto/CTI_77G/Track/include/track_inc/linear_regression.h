/**
* @file    linear_regression.h
* @author  Samuel Chen
* @version V1.0.0
* @date    2017/12/6
* @brief   --
*/

#ifndef __LINEAR_REGRESSION_H
#define __LINEAR_REGRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _HUGE_ENUF
    #define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#endif

	typedef struct LRModel
	{
		float a;
		float b;
	} LRModel;

	void linear_regression(float* independent, float* dependent, int size, LRModel* model);

#ifdef __cplusplus
}
#endif

#endif /* __LINEAR_REGRESSION_H */
