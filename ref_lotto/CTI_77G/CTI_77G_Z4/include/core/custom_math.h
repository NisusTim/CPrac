/**
* @file    custom_math.h
* @author  Samuel Chen
* @version V1.0.0
* @date    2019/04/30
* @brief   --
*/

#ifndef __CUSTOM_MATH_H
#define __CUSTOM_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdint.h>

#define CM_PI	3.141592653589793238462643383279502884197169399375105820974944592307816406f
#define DEGREE_TO_RADIAN			0.01745329252f  // (PI / 180.0)
#define RADIAN_TO_DEGREE			57.2957795131f  // 180.0 / PI
#define KPH_TO_MS      				(1000.0 / 3600.0)
#define MS_TO_KPH     				3.6

#define SINF(arg)						sinf(arg)
#define COSF(arg)						cosf(arg)
#define TANF(arg)						tanf(arg)
#define ATANF(arg)						atanf(arg)
#define ATAN2F(y, x)					atan2f(y, x)
#define ASINF(arg)						asinf(arg)
#define ACOSF(arg)						acosf(arg)
#define ABSF(arg)						fabsf(arg)
#define CEILDF(arg)						ceilf(arg)
#define FLOORF(arg)						floorf(arg)
#define POWF(base, exponent)			powf(base, exponent)
#define SQRTF(arg)						sqrtf(arg)

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_MATH_H */
