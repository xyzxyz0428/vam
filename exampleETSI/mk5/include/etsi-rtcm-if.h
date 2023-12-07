/**
 * @addtogroup ets_app_facilities_rtcm_api ETSI ITS Facilities RTCM API
 * @{
 *
 * TS 103 301 V1.3.1
* 
 * Interface to RTCM handling
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void RTCMRxExtCallback(tExtEventId Event,
 *                        tEXT_Message *pData,
 *                        void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_rtcmem)
 *       {
 *         ITSRtcmPdu *pRtcmPdu  = pData->rtcm;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pRtcmPdu->header.stationID);
 *
 *         // Send RTCM to handling application
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
// Copyright (c) 2018 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_RTCM_ETSI_RTCM_IF_H_
#define __ETSI_RTCM_ETSI_RTCM_IF_H_

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

/// RTCM management
typedef struct RTCMMgmt
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
} tRTCMMgmt;

/// RTCM Status codes
typedef enum RTCMStatusCode
{
  /// RTCM success
  ETSIRTCM_SUCCESS = 0x00,
  /// RTCM generation failure
  ETSIRTCM_FAILURE = 0x01,
  /// RTCM some parameters invalid
  ETSIRTCM_FAILURE_INVALID_PARAMS = 0x04,
  /// RTCM limits exceeded in structure
  ETSIRTCM_FAILURE_CONSTRAINT = 0x05,
  /// RTCM failed to encode
  ETSIRTCM_FAILURE_ENCODING = 0x06,
  /// RTCM generation not ready
  ETSIRTCM_FAILURE_NOT_READY = 0x07,

} eRTCMStatusCode;

/// Status code for RTCM actions @ref RTCMStatusCode
typedef uint8_t tRTCMStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger single RTCM
/// @param pMgmt Pointer to RTCM management structure
/// @param pRtcm Pointer to RTCM message content
/// @return RTCM Status Code
tRTCMStatusCode ETSIRTCM_SendRTCM(const tRTCMMgmt *pMgmt, const ITSRTCMcorrections *pRtcm);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_RTCM_ETSI_RTCM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
