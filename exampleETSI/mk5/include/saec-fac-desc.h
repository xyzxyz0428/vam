/**
 * @addtogroup saec_app_facilities_common_api SAEC Facilities Common data
 * @{
 *
 * @file
 *
 * Tx/Rx parameters used by the SAEC Facility Layer.
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_FAC_DESC_H_
#define __SAEC_FAC_DESC_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "saec-sec-if.h"

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

/**
 * @brief Facilities Tx/Rx description.
 * Set up the Tx specific fields when transmitting a packet through the facility
 * layer.
 * Inspect the Rx specific when receiving a packet through the facility layer.
 */
typedef struct SAECFacDesc
{
  union
  {
    /// Tx specific fields
    struct
    {
      /// Security Parameters for message signing
      tSAECSecSignParams SignParams;
    } Tx;
    /// Rx specific fields
    struct
    {
    } Rx;
  };
} tSAECFacDesc;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif // __SAEC_FAC_DESC_H_

// Close the doxygen group
/**
 * @}
 */
