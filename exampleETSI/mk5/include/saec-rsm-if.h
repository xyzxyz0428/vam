/**
 * @addtogroup saec_app_facilities_rsm_api SAEC Facilities RSM API
 * @{
 *
 * Transmits the RSM (Road Safety Message) that is constructed by customer application.
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_RSM_SAEC_RSM_IF_H_
#define __SAEC_RSM_SAEC_RSM_IF_H_

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

/// RSM Status codes
typedef enum SAECRSMStatusCode
{
  /// RSM success
  SAECRSM_SUCCESS = 0x00,
  /// RSM generation failure
  SAECRSM_FAILURE = 0x01,
  /// RSM some parameters invalid
  SAECRSM_FAILURE_INVALID_PARAMS = 0x04,
  /// RSM limits exceeded in structure
  SAECRSM_FAILURE_CONSTRAINT = 0x05,
  /// RSM failed to encode
  SAECRSM_FAILURE_ENCODING = 0x06,
  /// RSM generation not ready
  SAECRSM_FAILURE_NOT_READY = 0x07,

} eSAECRSMStatusCode;

/// @ref SAECRSMStatusCode
typedef uint8_t tSAECRSMStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Send one RSM with RTEData and RTSData
/// @param pRSM Pointer to the Road Side Information message
/// @return RSM Status Code
tSAECRSMStatusCode SAECRSM_SendRSM(const SAECRoadsideSafetyMessage *pRSM);

#ifdef __cplusplus
}
#endif

#endif//__SAEC_RSM_SAEC_RSM_IF_H_

// Close the Doxygen group
/**
 * @}
 */

