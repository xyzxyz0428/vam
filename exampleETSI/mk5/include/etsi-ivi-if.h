/**
 * @addtogroup ets_app_facilities_ivi_api ETSI ITS Facilities IVI API
 * @{
 *
 * TS 103 301 V1.3.1
 *
 * Interface to IVI handling
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void IVIRxExtCallback(tExtEventId Event,
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
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_ivim)
 *       {
 *         ITSIVI_PDU *pIviPdu  = (ITSIVI_PDU *)pData->pPDU;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pIviPdu->header.stationID);
 *
 *         // Send IVI to handling application
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

#ifndef __ETSI_IVI_ETSI_IVI_IF_H_
#define __ETSI_IVI_ETSI_IVI_IF_H_

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

/// Allow application to define IVI identification number in New PDU content
#define ETSIIVI_NEW_ID_APPL_DEFINED (NULL)

/// Allow application to define IVI identification number in Update PDU content
#define ETSIIVI_UPDATE_ID_APPL_DEFINED (0)

/// Maximum IVI repetition (in seconds) - one year
#define ETSIIVI_REPETITIONDURATIONMAX (60 * 60 * 24 * 365)

/// Maximum IVI ID number supported (less than INTEGER limit)
#define ETSIIVI_IDNUMBER_MAX (0xFFFFFF)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// IVI management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ETSIIVI_REPETITIONDURATIONMAX
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct IVIMgmt
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
} tIVIMgmt;

/// IVI Status codes
typedef enum IVIStatusCode
{
  /// IVI success
  ETSIIVI_SUCCESS = 0x00,
  /// IVI generation failure
  ETSIIVI_FAILURE = 0x01,
  /// IVI ID not existing
  ETSIIVI_FAILURE_INVALID_ID = 0x02,
  /// IVI Time invalid
  ETSIIVI_FAILURE_INVALID_TIME = 0x03,
  /// IVI some parameters invalid
  ETSIIVI_FAILURE_INVALID_PARAMS = 0x04,
  /// IVI limits exceeded in structure
  ETSIIVI_FAILURE_CONSTRAINT = 0x05,
  /// IVI failed to encode
  ETSIIVI_FAILURE_ENCODING = 0x06,
  /// IVI not ready
  ETSIIVI_FAILURE_NOT_READY = 0x07,

} eIVIStatusCode;

/// Status code for IVI actions @ref IVIStatusCode
typedef uint8_t tIVIStatusCode;

/// Action ID, 0 for failure
typedef uint64_t tIVIIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger initial IVI
/// @param pMgmt Pointer to IVI management information (incl IVI message info)
/// @param pIvi Pointer to IVI message content
//         Use timeStamp_option to determine if timestamp is included, if timeStamp
//         set to ETSIFAC_TIMESTAMP_TAI_NOW it is updated with the current time
//         Use validFrom_option to determine if validFrom is included, if validFrom
//         set to ETSIFAC_TIMESTAMP_TAI_NOW it is updated with the current time
/// @param pIDNum Optional pointer to store IVI identification number (if IVI
///        identification number is created by IVI service.) If pIDNum is
///        ETSIIVI_NEW_ID_APPL_DEFINED then IVI identification number is assumed
///        to be already defined in 'mandatory' fields of the provided IVI
///        message info.
/// @return IVI Status Code
tIVIStatusCode ETSIIVI_SendIVINew(const tIVIMgmt *pMgmt, const ITSIviStructure *pIvi, tIVIIdNum *pIDNum);

/// @brief Update IVI
/// @param pMgmt Pointer to IVI management information (incl IVI message info)
/// @param pIvi Pointer to IVI message content
//         Use timeStamp_option to determine if timestamp is included, if timeStamp
//         set to ETSIFAC_TIMESTAMP_TAI_NOW it is updated with the current time
//         Use validFrom_option to determine if validFrom is included, if validFrom
//         set to ETSIFAC_TIMESTAMP_TAI_NOW it is updated with the current time
/// @param IDNum IVI identification number (if IVI identification number is
///        created by IVI service.) If IDNum is ETSIIVI_UPDATE_ID_APPL_DEFINED
///        then IVI identification number is assumed to be already defined in
///        'mandatory' fields of the provided IVI message info.
/// @return IVI Status Code
tIVIStatusCode ETSIIVI_SendIVIUpdate(const tIVIMgmt *pMgmt, const ITSIviStructure *pIvi, tIVIIdNum IDNum);

/// @brief Terminate IVI
/// @param pMgmt Pointer to IVI management information (incl IVI message info)
/// @param pIvi Pointer to IVI message content
//         Use timeStamp_option to determine if timestamp is included, if timeStamp
//         set to ETSIFAC_TIMESTAMP_TAI_NOW it is updated with the current time
/// @param IDNum IVI identification number (if IVI identification number is
///        created by IVI service.) If IDNum is ETSIIVI_UPDATE_ID_APPL_DEFINED
///        then IVI identification number is assumed to be already defined in
///        'mandatory' fields of the provided IVI message info.
/// @return IVI Status Code
tIVIStatusCode ETSIIVI_SendIVITermination(const tIVIMgmt *pMgmt, const ITSIviStructure *pIvi, tIVIIdNum IDNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_IVI_ETSI_IVI_IF_H_

// Close the Doxygen group
/**
 * @}
 */
