/**
 * @addtogroup ets_app_facilities_vam_api ETSI ITS Facilities VAM API
 * @{
 *
 * TS 103 300-2 V2.1.1
 *
 * Interface to VAM handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_VAM_ETSI_VAM_IF_H_
#define __ETSI_VAM_ETSI_VAM_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include "etsi-fac-common.h"

#include "itsasn.h"
#include "itsasn_def.h"

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

/// VAM management
typedef struct VAMMgmt
{
  /// Populate known Dyanmic Properties information
  /// ETSI FAC will populate Pos/Heading/Speed/Acceleration/Yaw
  bool PopulateDyanmicProperties;
  /// ETSI FAC will populate Past Locations
  bool PopulatePastLocations;
  /// ETSI FAC will populate Predicted Locations
  /// NOTE: Not supported at present
  bool PopulatePredictedLocations;

  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;
} tVAMMgmt;

/// VAM Status codes
typedef enum VAMStatusCode
{
  /// VAM success
  ETSIVAM_SUCCESS = 0x00,
  /// VAM generation failure
  ETSIVAM_FAILURE = 0x01,
  /// VAM some parameters invalid
  ETSIVAM_FAILURE_INVALID_PARAMS = 0x04,
  /// VAM limits exceeded in structure
  ETSIVAM_FAILURE_CONSTRAINT = 0x05,
  /// VAM failed to encode
  ETSIVAM_FAILURE_ENCODING = 0x06,
  /// VAM not ready
  ETSIVAM_FAILURE_NOT_READY = 0x07,

} eVAMStatusCode;

/// Status code for VAM actions @ref VAMStatusCode
typedef uint8_t tVAMStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger single VAM
/// @param pMgmt Pointer to VAM management information
/// @param pVam Pointer to VAM message content
/// @return VAM Status Code
tVAMStatusCode ETSIVAM_SendVAM(const tVAMMgmt *pMgmt, const ITSVruAwareness *pVam);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_VAM_ETSI_VAM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
