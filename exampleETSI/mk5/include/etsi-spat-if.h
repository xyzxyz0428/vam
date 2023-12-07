/**
 * @addtogroup ets_app_facilities_spat_api ETSI ITS Facilities SPAT API
 * @{
 *
 * TS 103 301 V1.3.1
 *
 * Interface to SPAT handling
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void SPATRxExtCallback(tExtEventId Event,
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
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_spatem)
 *       {
 *         ITSSPATEM *pSpatPdu = pData->pSPAT;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pSpatPdu->header.stationID);
 *
 *         // Send SPAT to handling application
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

#ifndef __ETSI_SPAT_ETSI_SPAT_IF_H_
#define __ETSI_SPAT_ETSI_SPAT_IF_H_

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

/// SPAT management
typedef struct SPATMgmt
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
} tSPATMgmt;

/// SPAT Status codes
typedef enum SPATStatusCode
{
  /// SPAT success
  ETSISPAT_SUCCESS = 0x00,
  /// SPAT generation failure
  ETSISPAT_FAILURE = 0x01,
  /// SPAT some parameters invalid
  ETSISPAT_FAILURE_INVALID_PARAMS = 0x04,
  /// SPAT limits exceeded in structure
  ETSISPAT_FAILURE_CONSTRAINT = 0x05,
  /// SPAT failed to encode
  ETSISPAT_FAILURE_ENCODING = 0x06,
  /// SPAT not ready
  ETSISPAT_FAILURE_NOT_READY = 0x07,

} eSPATStatusCode;

/// Status code for SPAT actions @ref SPATStatusCode
typedef uint8_t tSPATStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger single SPAT
/// @param pMgmt Pointer to SPAT management information
/// @param pSpat Pointer to SPAT message content
/// @return SPAT Status Code
tSPATStatusCode ETSISPAT_SendSPAT(const tSPATMgmt *pMgmt, const ITSSPAT *pSpat);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_SPAT_ETSI_SPAT_IF_H_

// Close the Doxygen group
/**
 * @}
 */
