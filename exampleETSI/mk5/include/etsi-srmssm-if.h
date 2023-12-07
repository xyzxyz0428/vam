/**
 * @addtogroup ets_app_facilities_srmssm_api ETSI ITS Facilities SRM/SSM API
 * @{
 *
 * TS 103 301 V1.3.1
 *
 * Interface to SRMSSM handling
 *
 * @code
 *
 * #include "etsi-srmssm-if.h"
 * #include "ext.h"
 *
 * void SRMSSM_SRMTx(tSRMSSMIdNum SRMID)
 * {
 *   tSRMMgmt Mgmt = {0};
 *   ITSSignalRequestMessage SrmRequest = {0};
 *
 *   Mgmt.RepetitionDuration = 5;
 *   Mgmt.RepetitionInterval = 1000;
 *
 *   Mgmt.CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
 *   Mgmt.PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
 *   Mgmt.TrafficClass = ETSIFAC_GN_TC_ITS_DP2;
 *   Mgmt.HopLimit = ETSIFAC_GN_HOP_LIMIT_DEFAULT;
 *
 *   SrmRequest.requestor.id.choice = ITSVehicleID_stationID;
 *   // NOTE: stationID of ETSISRMSSM_STATIONID_POPULATE is automatically
 *   // populated with current stationID
 *   SrmRequest.requestor.id.u.stationID = ETSISRMSSM_STATIONID_POPULATE;
 *
 *   tSRMSSMStatusCode Status = ETSISRMSSM_SendSRM (&Mgmt, &SrmRequest, SRMID);
 *
 *   printf("SRM id %d, status is %d\n", SRMID, Status);
 * }
 *
 * void SRMSSMRxExtCallback(tExtEventId Event,
 *                          tExtMessage *pData,
 *                          void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_srem)
 *       {
 *         ITSSREM *pSrmPdu  = (ITSSREM *)pData->pPDU;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pSrmPdu->header.stationID);
 *
 *         // Send SRM to handling application
 *       }
 *       else if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_ssem)
 *       {
 *         ITSSSEM *pSsmPdu  = (ITSSSEM *)pData->pPDU;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pSsmPdu->header.stationID);
 *
 *         // Send SSM to handling application
 *       }
 *
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

#ifndef __ETSI_SRMSSM_ETSI_SRMSSM_IF_H_
#define __ETSI_SRMSSM_ETSI_SRMSSM_IF_H_

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

// Can auto-populate station ID in requestor ID
#define ETSISRMSSM_STATIONID_POPULATE 0

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// SRM management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ITSValidityDuration_Limit_Max
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct SRMMgmt
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
} tSRMMgmt;

/// SSM management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ITSValidityDuration_Limit_Max
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct SSMMgmt
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
} tSSMMgmt;

/// SRMSSM Status codes
typedef enum SRMSSMStatusCode
{
  /// SRMSSM success
  ETSISRMSSM_SUCCESS = 0x00,
  /// SRMSSM generation failure
  ETSISRMSSM_FAILURE = 0x01,
  /// SRMSSM some parameters invalid
  ETSISRMSSM_FAILURE_INVALID_PARAMS = 0x04,
  /// SRMSSM limits exceeded in structure
  ETSISRMSSM_FAILURE_CONSTRAINT = 0x05,
  /// SRMSSM failed to encode
  ETSISRMSSM_FAILURE_ENCODING = 0x06,
  /// SRMSSM not ready
  ETSISRMSSM_FAILURE_NOT_READY = 0x07,

} eSRMSSMStatusCode;

/// Status code for SRMSSM actions @ref SRMSSMStatusCode
typedef uint8_t tSRMSSMStatusCode;

/// Action ID
typedef uint16_t tSRMSSMIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger SRM
/// @param pMgmt Pointer to SRM management structure
/// @param pSrm Pointer to SRM message content
/// @param IdNum Identifier of SRM to handle
/// @return SRMSSM Status Code
tSRMSSMStatusCode ETSISRMSSM_SendSRM(const tSRMMgmt *pMgmt, const ITSSignalRequestMessage *pSrm, tSRMSSMIdNum IdNum);

/// @brief Trigger SSM
/// @param pMgmt Pointer to SSM management structure
/// @param pSsm Pointer to SSM message content
/// @param IdNum Identifier of SSM to handle
/// @return SRMSSM Status Code
tSRMSSMStatusCode ETSISRMSSM_SendSSM(const tSSMMgmt *pMgmt, const ITSSignalStatusMessage *pSsm, tSRMSSMIdNum IdNum);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_SRMSSM_ETSI_SRMSSM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
