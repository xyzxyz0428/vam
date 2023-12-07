/**
 * @addtogroup ets_app_facilities_cpm_api ETSI ITS Facilities CPM API
 * @{
 *
 * TR 103 562 V2.1.1
 *
 * Interface to CPM handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2018 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_CPM_ETSI_CPM_IF_H_
#define __ETSI_CPM_ETSI_CPM_IF_H_

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

/// CPM management
typedef struct CPMMgmt
{
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

  /// CPM managementContainer (and generationDeltaTime) to be set by FAC layer
  bool AutoPopulateMgmtContainer;
  /// CPM stationDataContainer to be set by FAC layer
  bool AutoPopulateStationDataContainer;
} tCPMMgmt;

/// CPM Status codes
typedef enum CPMStatusCode
{
  /// CPM success
  ETSICPM_SUCCESS = 0x00,
  /// CPM generation failure
  ETSICPM_FAILURE = 0x01,
  /// CPM some parameters invalid
  ETSICPM_FAILURE_INVALID_PARAMS = 0x04,
  /// CPM limits exceeded in structure
  ETSICPM_FAILURE_CONSTRAINT = 0x05,
  /// CPM failed to encode
  ETSICPM_FAILURE_ENCODING = 0x06,
  /// CPM not ready
  ETSICPM_FAILURE_NOT_READY = 0x07,

} eCPMStatusCode;

/// Status code for CPM actions @ref CPMStatusCode
typedef uint8_t tCPMStatusCode;

/// ITSPerceivedObject with Unix time.
typedef struct ITSPerceivedObjectSnapshot
{
  int64_t Time_ms; // Unix time in ms
  ITSPerceivedObject PerceivedObject; // ITSPerceivedObject container.
} tITSPerceivedObjectSnapshot;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger single CPM
/// @param pMgmt Pointer to CPM management information
/// @param pCpm Pointer to CPM message content
/// @return CPM Status Code
tCPMStatusCode ETSICPM_SendCPM(const tCPMMgmt *pMgmt, const ITSCollectivePerceptionMessage *pCpm);

/// @brief Trigger single CPM with perceived objects
/// @param pMgmt Pointer to CPM management information (or NULL for defaults)
/// @param pObjs Pointer to array of objects (with Unix timestamps) to be sent
/// @param NumObjs Number of objects
/// @return CPM Status Code
tCPMStatusCode ETSICPM_SendCPM_PerceivedObjects(const tCPMMgmt *pMgmt, const tITSPerceivedObjectSnapshot *pObjs, size_t NumObjs);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_CPM_ETSI_CPM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
