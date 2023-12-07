/**
 * @addtogroup stack_lph_api
 * @{
 *
 * @file lph-float.h providing float point type definations
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __LPH_FLOAT_H__
#define __LPH_FLOAT_H__

// make sure we get NAN
#ifndef  _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <math.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Consider HW specific performance tuning of the tLPHFloat type
typedef double tLPHFloat;

#define LPH_ISNAN(x) isnan(x)
#define LPH_NAN NAN
#define LPH_POW(x) pow(x)
#define LPH_SQRT(x) sqrt(x)
#define LPH_FABS(x) fabs(x)
#define LPH_SIN(x) sin(x)
#define LPH_COS(x) cos(x)
#define LPH_SINCOS(x, pSin, pCos) sincos(x, pSin, pCos)
#define LPH_TAN(x) tan(x)
#define LPH_ASIN(x) asin(x)
#define LPH_ACOS(x) acos(x)
#define LPH_ATAN(x) atan(x)
#define LPH_ATAN2(x, y) atan2(x, y)
#define LPH_HYPOT(x, y) hypot(x, y)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif // __LPH_FLOAT_H__
