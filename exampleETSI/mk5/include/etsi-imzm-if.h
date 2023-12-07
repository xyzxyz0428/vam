/**
 * @addtogroup ets_app_facilities_imzm_api ETSI ITS Facilities IMZM API
 * @{
 *
 * TS 103 724 V2.1.1
 *
 * Interface to IMZM handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_IMZM_ETSI_IMZM_IF_H_
#define __ETSI_IMZM_ETSI_IMZM_IF_H_

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

/// IMZM management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ITSValidityDuration_Limit_Max
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct IMZMMgmt
{
  /// ETSI FAC will populate Pos/Heading/Speed/Acceleration/Yaw
  bool PopulateBasicContainer;

  /// Repetition Duration (sec), ETSIFAC_REPETITIONDURATIONNONE for none
  uint32_t RepetitionDuration;
  /// Repetition Interval (mS), ETSIFAC_REPETITIONINTERVALNONE for none
  uint16_t RepetitionInterval;

  /// GN Packet transport type @ref ETSIFACGeoNetTransport
  /// ETSIFAC_GN_TRANSPORT_GEOBROADCAST, ETSIFAC_GN_TRANSPORT_TSB,
  /// ETSIFAC_GN_TRANSPORT_SHB supported
  tETSIFACGeoNetTransport PktTransport;

  /// Destination Area (only required for GBC PktTransport)
  tETSIFACGeoNetArea DestArea;

  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;
  /// HopLimit
  tETSIFACGNHopLimit HopLimit;
} tIMZMMgmt;

/// IMZM Status codes
typedef enum IMZMStatusCode
{
  /// IMZM success
  ETSIIMZM_SUCCESS = 0x00,
  /// IMZM generation failure
  ETSIIMZM_FAILURE = 0x01,
  /// IMZM some parameters invalid
  ETSIIMZM_FAILURE_INVALID_PARAMS = 0x04,
  /// IMZM limits exceeded in structure
  ETSIIMZM_FAILURE_CONSTRAINT = 0x05,
  /// IMZM failed to encode
  ETSIIMZM_FAILURE_ENCODING = 0x06,
  /// IMZM not ready
  ETSIIMZM_FAILURE_NOT_READY = 0x07,

} eIMZMStatusCode;

/// Status code for IMZM actions @ref IMZMStatusCode
typedef uint8_t tIMZMStatusCode;

/// Action ID
typedef uint16_t tIMZMIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger periodic IMZM
/// @param pMgmt Pointer to IMZM management information
/// @param pImzm Pointer to IMZM message content
/// @param IdNum Identifier of IMZM to handle
/// @return IMZM Status Code
tIMZMStatusCode ETSIIMZM_SendIMZM(const tIMZMMgmt *pMgmt, const ITSInterferenceManagementZoneMessage *pImzm, tIMZMIdNum IdNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_IMZM_ETSI_IMZM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
