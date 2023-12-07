/**
 * @addtogroup saec_app_facilities_map_api SAEC Facilities MAP API
 * @{
 *
 * Transmits the MAP Message that is constructed by customer application.
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_MAP_SAEC_MAP_IF_H_
#define __SAEC_MAP_SAEC_MAP_IF_H_

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

/// MAP Status codes
typedef enum SAECMAPStatusCode
{
  /// MAP success
  SAECMAP_SUCCESS = 0x00,
  /// MAP generation failure
  SAECMAP_FAILURE = 0x01,
  /// MAP some parameters invalid
  SAECMAP_FAILURE_INVALID_PARAMS = 0x04,
  /// MAP limits exceeded in structure
  SAECMAP_FAILURE_CONSTRAINT = 0x05,
  /// MAP failed to encode
  SAECMAP_FAILURE_ENCODING = 0x06,
  /// MAP generation not ready
  SAECMAP_FAILURE_NOT_READY = 0x07,

} eSAECMAPStatusCode;

/// @ref SAECMAPStatusCode
typedef uint8_t tSAECMAPStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Send one MAP
/// @param pMAP Pointer to MAP message content
/// @return MAP Status Code
tSAECMAPStatusCode SAECMAP_SendMAP(const SAECMapData *pMAP);

#ifdef __cplusplus
}
#endif

#endif//__SAEC_MAP_SAEC_MAP_IF_H_

// Close the Doxygen group
/**
 * @}
 */

