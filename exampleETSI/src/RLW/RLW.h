#pragma once
/**
 * @addtogroup app_rlw Red Light Warning app plugin
 * @{
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __RLW_H__
#define __RLW_H__

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "RLW_defn.h"
#include "RLW-rx.h"

#include <stdio.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// RLW configurable parameters
typedef struct RLWParam
{
  /// Enabled?
  bool Enable;
  /// Log verbosity level
  int DebugLevel;
} tRLWParam;

/// Top level RLW state information
typedef struct RLW
{
  bool Active;                  ///< ~= CW_RLW_ENABLE
  /// RLW confguration parameters (from the config)
  tRLW_Cust_App_RLW Param;
  /// Threat/receive functionality
  tRLWRx Rx;
} tRLW;

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

/// Singleton
extern tRLW RLW;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int  RLW_Init(void);
void RLW_Exit(void);

void RLW_PrintStats(FILE *pStream);

#if defined(UNITTEST)
tRLW *RLW_Ptr(void);
#endif

#endif // __RLW_H__
/**
 * @}
 */
