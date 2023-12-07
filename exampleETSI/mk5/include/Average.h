/**
 * @addtogroup util_average Calculation of Averages
 * @{
 *
 * Utilities for calculation of averages
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_UTIL_AVERAGE_H_
#define __PLAT_UTIL_AVERAGE_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

struct UtilAverage;
struct UtilTimedAverage;
struct timeval;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

struct UtilAverage * UtilAverage_Construct(size_t Num);
int32_t UtilAverage_Update(struct UtilAverage * pUtilAverage, int32_t Val);
void UtilAverage_Destruct(struct UtilAverage ** ppUtilAverage);

// maximum slots to allocate (i.e. MaxAge / (expected update rate))
struct UtilTimedAverage * UtilTimedAverage_Construct(size_t Num, uint32_t Duration_ms);
struct UtilTimedAverage * UtilTimedAverage_Construct2(size_t Num, uint32_t Duration_ms,
                                                      float InitialValue);
// pNow may be NULL to get current
float UtiltimedAverage_Update(struct UtilTimedAverage * pUtilTimedAverage,
                              float Val, const struct timeval *pNow);
void UtilTimedAverage_Destruct(struct UtilTimedAverage ** ppUtilTimedAverage);

#ifdef __cplusplus
}
#endif

#endif // __PLAT_UTIL_AVERAGE_H_

// Close the doxygen group
/**
 * @}
 */
