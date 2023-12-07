#pragma once
/**
 * @addtogroup app_fsp Freight Signal Priority
 * @{
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __FSP_IF_H__
#define __FSP_IF_H__

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include <stdio.h>

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

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void FSP_PrintStats(FILE *pStream);

#ifdef __cplusplus
}
#endif

#endif // __FSP_IF_H__
/**
 * @}
 */
