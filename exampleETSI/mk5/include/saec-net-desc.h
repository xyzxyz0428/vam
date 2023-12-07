/**
 * @addtogroup v2x_saec_net_desc SAEC Network Layer Parameters
 * @{
 *
 * Tx/Rx parameters used by the SAEC Network Layer.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_NET_DESC_H_
#define __SAEC_NET_DESC_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdbool.h>

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

/// SAEC DSMP descriptor format (DSM.request & DSM.indication)
typedef struct SAECNetDesc
{
  union
  {
    /// Tx specific fields
    struct
    {
      /// AID to be encoded in the message
      uint32_t AID;
      /// Tx Priority
      uint8_t Priority;
      /// Need to update the L2 source addr
      bool NewL2SourceAddr;
    } Tx;
    /// Rx specific fields
    struct
    {
      /// Extracted DSMP version
      uint8_t Version;
      /// Has Extensions
      bool HasExtensions;
      /// Extracted AID
      uint32_t AID;
      /// The length in octets of the 'on-the-air' frame data
      uint16_t Length;
    } Rx;
  };
} tSAECNetDesc;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif // __SAEC_NET_DESC_H_

// Close the doxygen group
/**
 * @}
 */
