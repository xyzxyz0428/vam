/**
 * @addtogroup ets_app_facilities_evcsn_api ETSI ITS Facilities EVCSN API
 * @{
 *
 * TS 101 556-1 V1.1.1
 *
 * Interface to EVCSN handling
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void EVCSNRxExtCallback(tExtEventId Event,
 *                         tEXT_Message *pData,
 *                         void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_evcsn)
 *       {
 *         ITSEvcsnPdu *pEvcsnPdu  = pData->evcsn;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pEvcsnPdu->header.stationID);
 *
 *         // Send EVCSN to handling application
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

#ifndef __ETSI_EVCSN_ETSI_EVCSN_IF_H_
#define __ETSI_EVCSN_ETSI_EVCSN_IF_H_

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

/// Maximum EVCSN repetition (in seconds) - one year
#define ETSIEVCSN_REPETITIONDURATIONMAX (60 * 60 * 24 * 365)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// EVCSN management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ETSIEVCSN_REPETITIONDURATIONMAX or
///       equal to ETSIFAC_REPETITIONDURATIONFOREVER for endless repetition
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct EVCSNMgmt
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
} tEVCSNMgmt;

/// EVCSN Status codes
typedef enum EVCSNStatusCode
{
  /// EVCSN success
  ETSIEVCSN_SUCCESS = 0x00,
  /// EVCSN generation failure
  ETSIEVCSN_FAILURE = 0x01,
  /// EVCSN some parameters invalid
  ETSIEVCSN_FAILURE_INVALID_PARAMS = 0x04,
  /// EVCSN limits exceeded in structure
  ETSIEVCSN_FAILURE_CONSTRAINT = 0x05,
  /// EVCSN failed to encode
  ETSIEVCSN_FAILURE_ENCODING = 0x06,
  /// EVCSN generation not ready
  ETSIEVCSN_FAILURE_NOT_READY = 0x07,

} eEVCSNStatusCode;

/// Status code for EVCSN actions @ref EVCSNStatusCode
typedef uint8_t tEVCSNStatusCode;

/// Action ID
typedef uint16_t tEVCSNIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger periodic EVCSN
/// @param pMgmt Pointer to EVCSN management structure
/// @param pEvcsn Pointer to EVCSN message content
/// @param IdNum Identifier of EVCSN to handle
/// @return EVCSN Status Code
tEVCSNStatusCode ETSIEVCSN_SendEVCSN(const tEVCSNMgmt *pMgmt, const ITSEVChargingSpotNotificationPOIMessage *pEvcsn, tEVCSNIdNum IdNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_EVCSN_ETSI_EVCSN_IF_H_

// Close the Doxygen group
/**
 * @}
 */
