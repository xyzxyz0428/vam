/**
 * @addtogroup saec_app_facilities_rsi_api SAEC Facilities RSI API
 * @{
 *
 * Transmits the RSI (Road Side Information) message that is constructed by customer application.
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_RSI_SAEC_RSI_IF_H_
#define __SAEC_RSI_SAEC_RSI_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "saecasn.h"

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

/// RSI Status codes
typedef enum SAECRSIStatusCode
{
  /// RSI success
  SAECRSI_SUCCESS = 0x00,
  /// RSI generation failure
  SAECRSI_FAILURE = 0x01,
  /// RSI some parameters invalid
  SAECRSI_FAILURE_INVALID_PARAMS = 0x04,
  /// RSI limits exceeded in structure
  SAECRSI_FAILURE_CONSTRAINT = 0x05,
  /// RSI failed to encode
  SAECRSI_FAILURE_ENCODING = 0x06,
  /// RSI generation not ready
  SAECRSI_FAILURE_NOT_READY = 0x07,

} eSAECRSIStatusCode;

/// @ref SAECRSIStatusCode
typedef uint8_t tSAECRSIStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Send one RSI with RTEData and RTSData
/// @param pRSI Pointer to the Road Side Information message
/// @return RSI Status Code
tSAECRSIStatusCode SAECRSI_SendRSI(const SAECRoadSideInformation *pRSI);

#ifdef __cplusplus
}
#endif

#endif//__SAEC_RSI_SAEC_RSI_IF_H_

// Close the Doxygen group
/**
 * @}
 */

