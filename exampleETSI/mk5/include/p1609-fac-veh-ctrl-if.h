/**
 * @addtogroup v2x_p1609_tx_api
 * @{
 *
 * Interface to provide abstract EVA, etc triggering.
 *
 * The client can use this to have higher-level controls for EVA, etc
 * triggering and vehicle type changes.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_FAC_VEH_CTRL_IF_H_
#define __P1609_FAC_VEH_CTRL_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "j2735asn.h"

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// P1609VehCtl Status codes
typedef enum P1609VehCtlStatusCode
{
  /// P1609VehCtl success
  P1609VEHCTL_SUCCESS = 0x00,
  /// P1609VehCtl failure
  P1609VEHCTL_FAILURE = 0x01,
  /// P1609VehCtl generation failure
  //P1609VEHCTL_FAILURE_GENERATION = 0x02,
  /// P1609VehCtl ActionID not existing
  //P1609VEHCTL_FAILURE_INVALID_ACTION_ID = 0x03,
  /// P1609VehCtl Time invalid
  //P1609VEHCTL_FAILURE_INVALID_TIME = 0x04,
  /// P1609VehCtl some parameters invalid
  P1609VEHCTL_FAILURE_INVALID_PARAMS = 0x05,
  /// P1609VehCtl failed to encode
  //P1609VEHCTL_FAILURE_ENCODING = 0x06,
  /// P1609VehCtl not ready
  //P1609VEHCTL_FAILURE_NOT_READY = 0x07,
} eP1609VehCtlStatusCode;

/// Status code for P1609 veh ctrl actions @ref P1609VehCtlStatusCode
typedef uint8_t tP1609VehCtlStatusCode;

/// P1609VehCtl Vehicle Role (base upon j2735 ASN)
typedef SAEBasicVehicleRole eP1609VehCtlBasicVehicleRole;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Update BSM special vehicle information
/// @param Role Vehicle role to activate
/// @return Status Code
tP1609VehCtlStatusCode P1609VehCtl_SetBasicVehicleRole(SAEBasicVehicleRole Role);

/// @brief Clear BSM special vehicle information
/// @return Status Code
tP1609VehCtlStatusCode P1609VehCtl_ClearBasicVehicleRole(void);


#endif // __P1609_FAC_VEH_CTRL_IF_H_

// Close the Doxygen group
/**
 * @}
 */

