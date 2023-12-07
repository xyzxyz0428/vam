/**
 * @addtogroup saec_app_facilities_spat_api SAEC Facilities SPAT API
 * @{
 *
 * Transmits the SPAT (Signal Phase And Timing) message that is constructed by customer application.
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_SPAT_SAEC_SPAT_IF_H_
#define __SAEC_SPAT_SAEC_SPAT_IF_H_

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

/// SPAT Status codes
typedef enum SAECSPATStatusCode
{
  /// SPAT success
  SAECSPAT_SUCCESS = 0x00,
  /// SPAT generation failure
  SAECSPAT_FAILURE = 0x01,
  /// SPAT some parameters invalid
  SAECSPAT_FAILURE_INVALID_PARAMS = 0x04,
  /// SPAT limits exceeded in structure
  SAECSPAT_FAILURE_CONSTRAINT = 0x05,
  /// SPAT failed to encode
  SAECSPAT_FAILURE_ENCODING = 0x06,
  /// SPAT generation not ready
  SAECSPAT_FAILURE_NOT_READY = 0x07,

} eSAECSPATStatusCode;

/// @ref SAECSPATStatusCode
typedef uint8_t tSAECSPATStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Send one SPAT
/// @param pSPAT Pointer to SPAT message content
/// @return SPAT Status Code
tSAECSPATStatusCode SAECSPAT_SendSPAT(const SAECSPAT *pSPAT);

#ifdef __cplusplus
}
#endif

#endif//__SAEC_SPAT_SAEC_SPAT_IF_H_

// Close the Doxygen group
/**
 * @}
 */

