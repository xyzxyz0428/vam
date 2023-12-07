/**
 * @addtogroup cohda_tim_api Traveler Information Messages (TIM) API
 * @{
 *
 * @section mod_tim_rx_dd What Does It Do
 * Creates a thread to listen for TIM messages.
 * Decodes and stores any TIM messages it receives in the LDM.
 *
 * @file tim.h
 *
 * TIM receiver definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __TIM_H_
#define __TIM_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "tim-region.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Declarations
//------------------------------------------------------------------------------

int TIM_Init(void);
void TIM_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif // __TIM_H_
/**
 * @}
 */
