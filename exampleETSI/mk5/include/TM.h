#pragma once

/**
 * @addtogroup tm_api Threat Management (TM) API
 * @{
 *
 * Threat Management is used to verify and prioritise warnings from
 * the threat applications and forward them to the HMI.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __TM_H_
#define __TM_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

/// Auto-generated header file containing TM error code enumeration
#include "TM_Err.h"

#include "TA.h"
#include "default_stack_defn.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Message ID for alerts from Threat Applications
#define TM_MSG_ALERT      (QS_BASE_MSG_TM + 0)
/// Message ID for successful verifications from the security module
#define TM_MSG_VRFY_OK    (QS_BASE_MSG_TM + 1)
/// Message ID for failed verifications from the security module
#define TM_MSG_VRFY_FAIL  (QS_BASE_MSG_TM + 2)


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// Obtain compiled-in default parameters
void TM_SetDefaultParams(tdefault_stack_Cohda_TM *pParams);

//  Register a callback function with the TM
int TM_RegisterCallback(fTA_Callback *pCallback,
                        void* pCBContext);

// Delete a callback function from the TM
int TM_DeregisterCallback(fTA_Callback *pCallback,
                          void* pCBContext);

// Initialise TM & Set a callback client
tTM_ErrCode TM_Init(const tdefault_stack_Cohda_TM *pParams,
                    fTA_Callback *pCallback,
                    void* pCBContext);

// Exit TC
tTM_ErrCode TM_Exit(void);

// Set the alert inhibit flag (i.e. don't notify HMI if true)
void TM_SetAlertInhibit(bool Inhibit);

// Get the alert inhibit flag
bool TM_GetAlertInhibit(void);

// Callback for alerts
fTA_Callback TM_AlertCallback;

// Return true and copy alert details if and only if there's an active alert
fTA_CurrentAlert TM_CurrentAlert;

#ifdef __cplusplus
}
#endif

#endif // __TM_H_
// Close the doxygen group
/**
 * @}
 */
