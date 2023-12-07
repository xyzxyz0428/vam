/**
 * @addtogroup saec_app_facilities_msg_api SAEC Facilities MSG API
 * @{
 *
 * Interface to manage Generic Message packet generation and handling
 *
 * The client can send an SAEC MSG packet with the configured AID by using this
 * API. The relevant sending parameters can be set by the client.
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_MSG_SAEC_MSG_IF_H_
#define __SAEC_MSG_SAEC_MSG_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "saec-fac-desc.h"
#include "saec-net-desc.h"
#include <stddef.h>

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

/// Status code for MSG packet sending
typedef enum SAECMSGStatusCode
{
  /// MSG generation success
  SAECMSG_SUCCESS = 0x00,
  /// MSG generation failure
  SAECMSG_FAILURE_GENERATION = 0x01,
  /// MSG configuration failure
  SAECMSG_FAILURE_CONFIGURATION = 0x03,
  /// MAP some parameters invalid
  SAECMSG_FAILURE_INVALID_PARAMS = 0x04,
  /// MAP generation not ready
  SAECMSG_FAILURE_NOT_READY = 0x07,

} eSAECMSGStatusCode;

/// @ref SAECMSGStatusCode
typedef uint8_t tSAECMSGStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/// @brief Trigger MSG packet sending
/// @param pPayload Pointer to payload data
/// @param Length Length in octets
/// @param pFacTxParams Tx params for the facility layer
/// @param pNetTxParams Tx params for the network layer
/// @return MSG Status Code
tSAECMSGStatusCode SAECMSG_SendPacket(const uint8_t *pPayload,
                                      size_t Length,
                                      const tSAECFacDesc * pFacTxParams,
                                      const tSAECNetDesc * pNetTxParams);

#ifdef __cplusplus
}
#endif

#endif // __SAEC_MSG_SAEC_MSG_IF_H_

// Close the Doxygen group
/**
 * @}
 */
