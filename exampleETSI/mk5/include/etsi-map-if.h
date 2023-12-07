/**
 * @addtogroup ets_app_facilities_map_api ETSI ITS Facilities MAP API
 * @{
 *
 * TS 103 301 V1.3.1
 *
 * Interface to MAP handling
 *
 * The MAP API allows complete or fragmented MAPEMs to be sent. The fragmented
 * MAPEMs require a layerID to be set within the MAPEM (obviously all fragments
 * must be sent to allow correct re-assembly.) At least for this implementation,
 * the MAPEM fragments must refer to one intersection only and the fragments
 * contain laneSets (usually describing one or more approaches) for that
 * intersection. Fragmented road segments are not supported.
 *
 * The EXT API can be used to receive MAPEMs for processing by the application
 * code.
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void MAPRxExtCallback(tExtEventId Event,
 *                       tEXT_Message *pData,
 *                       void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_mapem)
 *       {
 *         ITSMAPEM *pMapPdu = pData->pMAP;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pMapPdu->header.stationID);
 *
 *         // Send MAP to handling application
 *       }
 *     }
 *
 *     default:
 *       // Other events
 *       break;
 *   }
 * }
 *
 * @endcode
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_MAP_ETSI_MAP_IF_H_
#define __ETSI_MAP_ETSI_MAP_IF_H_

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

/// Maximum MAP repetition (in seconds) - approximately one year
#define ETSIMAP_REPETITIONDURATIONMAX (60 * 60 * 24 * 365)

/// IdNum not required if Intersection Id to be used as identifier
#define ETSIMAP_IDNUM_FROM_INTERSECTION (0)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// MAP management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ETSIMAP_REPETITIONDURATIONMAX or
///       equal to ETSIFAC_REPETITIONDURATIONFOREVER for endless repetition
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct MAPMgmt
{
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
} tMAPMgmt;

/// MAP Status codes
typedef enum MAPStatusCode
{
  /// MAP success
  ETSIMAP_SUCCESS = 0x00,
  /// MAP generation failure
  ETSIMAP_FAILURE = 0x01,
  /// MAP some parameters invalid
  ETSIMAP_FAILURE_INVALID_PARAMS = 0x04,
  /// MAP limits exceeded in structure
  ETSIMAP_FAILURE_CONSTRAINT = 0x05,
  /// MAP failed to encode
  ETSIMAP_FAILURE_ENCODING = 0x06,
  /// MAP generation not ready
  ETSIMAP_FAILURE_NOT_READY = 0x07,

} eMAPStatusCode;

/// Status code for MAP actions @ref MAPStatusCode
typedef uint8_t tMAPStatusCode;

/// Control handle ID
typedef uint16_t tMAPIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger periodic MAP
/// @param pMgmt Pointer to MAP management structure
/// @param pMap Pointer to MAPEM message content
/// @param IdNum (Optional) Control handle for subsequent actions on this MAP
///              (set to ETSIMAP_IDNUM_FROM_INTERSECTION to use MAPEM
///              intersection ID as control handle)
/// @return MAP Status Code
tMAPStatusCode ETSIMAP_SendMAP(const tMAPMgmt *pMgmt, const ITSMapData *pMap, tMAPIdNum IdNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_MAP_ETSI_MAP_IF_H_

// Close the Doxygen group
/**
 * @}
 */
