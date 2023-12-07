/**
 * @addtogroup ets_app_facilities_mcdm_api ETSI ITS Facilities MCDM API
 * @{
 *
 * TS 103 152 V2.1.1
 *
 * Interface to MCDM handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_MCDM_ETSI_MCDM_IF_H_
#define __ETSI_MCDM_ETSI_MCDM_IF_H_

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

/// MCDM management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ITSValidityDuration_Limit_Max
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct MCDMMgmt
{
  /// Repetition Duration (sec), ETSIFAC_REPETITIONDURATIONNONE for none
  uint32_t RepetitionDuration;
  /// Repetition Interval (mS), ETSIFAC_REPETITIONINTERVALNONE for none
  uint16_t RepetitionInterval;

  /// GN Packet transport type @ref ETSIFACGeoNetTransport
  /// ETSIFAC_GN_TRANSPORT_GEOUNICAST, ETSIFAC_GN_TRANSPORT_GEOANYCAST,
  /// ETSIFAC_GN_TRANSPORT_GEOBROADCAST, ETSIFAC_GN_TRANSPORT_TSB,
  /// ETSIFAC_GN_TRANSPORT_SHB supported
  tETSIFACGeoNetTransport PktTransport;

  /// Destination Area (only required for GBC PktTransport)
  tETSIFACGeoNetArea DestArea;
  /// Destination Address (only required for GUC PktTransport)
  tETSIFACGeoNetAddr DestAddr;

  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;
  /// HopLimit
  tETSIFACGNHopLimit HopLimit;
} tMCDMMgmt;

/// MCDM Status codes
typedef enum MCDMStatusCode
{
  /// MCDM success
  ETSIMCDM_SUCCESS = 0x00,
  /// MCDM generation failure
  ETSIMCDM_FAILURE = 0x01,
  /// MCDM some parameters invalid
  ETSIMCDM_FAILURE_INVALID_PARAMS = 0x04,
  /// MCDM limits exceeded in structure
  ETSIMCDM_FAILURE_CONSTRAINT = 0x05,
  /// MCDM failed to encode
  ETSIMCDM_FAILURE_ENCODING = 0x06,
  /// MCDM not ready
  ETSIMCDM_FAILURE_NOT_READY = 0x07,

} eMCDMStatusCode;

/// Status code for MCDM actions @ref MCDMStatusCode
typedef uint8_t tMCDMStatusCode;

/// Action ID
typedef uint16_t tMCDMIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger periodic MCDM
/// @param pMgmt Pointer to MCDM management information
/// @param pMcdm Pointer to MCDM message content
/// @param IdNum Identifier of MCDM to handle
/// @return MCDM Status Code
tMCDMStatusCode ETSIMCDM_SendMCDM(const tMCDMMgmt *pMgmt, const ITSMcdmInfo *pMcdm, tMCDMIdNum IdNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_MCDM_ETSI_MCDM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
