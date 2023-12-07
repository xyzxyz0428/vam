/**
 * @addtogroup ets_app_facilities_denm_api ETSI ITS Facilities DENM API
 * @{
 *
 * EN 302 637-3 V1.3.1
 *
 * Interface to manage DENM generation and handling
 *
 * The client generates DENM events using the API functions provided. The
 * expected sequence is that a DENM event is triggered, this can then expire
 * normally, or be updated, or be be terminated. The client sets the mandatory
 * fields and the optional fields as required.
 *
 * For C2C-based scenarios the DENM triggering can be more efficiently
 * implemented by using the dedicated FAC C2C API (@ref ets_app_facilities_c2c_api)
 *
 * The DENM reception is handled by the DENM handler which validates the DENM
 * construction and then provides the decoded DENM structure to clients
 * via the EXT interface. The client subscribes to QSMSG_EXT_RX_ITSFL_PDU
 * events and can identify the PDU from the ItsPduHeader.
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void DENMRxExtCallback(tExtEventId Event,
 *                        tExtMessage *pData,
 *                        void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_denm)
 *       {
 *         ITSDENM *pDenmPdu = pData->pDENM;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pDenmPdu->header.stationID);
 *
 *         // Send DENM to handling application
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

#ifndef __ETS_DENM_ETS_DENM_IF_H_
#define __ETS_DENM_ETS_DENM_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>

#include "itsasn.h"
#include "itsasn_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// No validity duration
#define VALIDITYDURATIONDEFAULT 0
/// Maximum validity duration
#define VALIDITYDURATIONMAX 86400

/// No repetition duration
#define REPETITIONDURATIONNONE 0

/// No repetition interval
#define REPETITIONINTERVALDISABLED 0

/// Shortest repetition interval
#define REPETITIONINTERVALMIN_MS 50

/// Longest repetition interval
#define REPETITIONINTERVALMAX_MS 60000

/// Terminate repetition interval (i.e. immediate termination of previously repeating message)
#define REPETITIONINTERVALTERMINATE 0xFFFF

/// No Keep-Alive Forwarding
#define TRANSMISSIONINTERVALDISABLED 0

/// @brief Convert time in seconds to DENM item 'StationarySince'
/// @param Seconds time to convert (in seconds)
/// @return StationarySince enum
#define DENM_GetStationarySinceFromSec(Seconds) \
  ((Seconds) <  (1 * 60)) ? ITSStationarySince_lessThan1Minute : \
  ((Seconds) <  (2 * 60)) ? ITSStationarySince_lessThan2Minutes : \
  ((Seconds) < (15 * 60)) ? ITSStationarySince_lessThan15Minutes : \
                            ITSStationarySince_equalOrGreater15Minutes

/// @brief Convert distance in metres to DENM item 'RelevanceDistance'
/// @param Metres distance to convert (in metres)
/// @return RelevanceDistance enum
#define DENM_GetRelevanceDistanceFromMetre(Metres) \
  ((Metres) <    50) ? ITSRelevanceDistance_lessThan50m : \
  ((Metres) <   100) ? ITSRelevanceDistance_lessThan100m : \
  ((Metres) <   200) ? ITSRelevanceDistance_lessThan200m : \
  ((Metres) <   500) ? ITSRelevanceDistance_lessThan500m : \
  ((Metres) <  1000) ? ITSRelevanceDistance_lessThan1000m : \
  ((Metres) <  5000) ? ITSRelevanceDistance_lessThan5km : \
  ((Metres) < 10000) ? ITSRelevanceDistance_lessThan10km : \
                       ITSRelevanceDistance_over10km

/// Get Station Id from DENM action ID
#define ETSIDENM_ACTIONID_STATION(ActionId) ((uint32_t)((ActionId >> 16) & 0xFFFFFFFF))
/// Get Sequence Number from DENM action ID
#define ETSIDENM_ACTIONID_SEQNUM(ActionId) ((uint16_t)(ActionId & 0xFFFF))

/// Create DENM action ID from Station ID + Sequence Number
#define ETSIDENM_ACTIONID(StationId, SeqNum) (((tDENMActionID)(StationId & 0xFFFFFFFF) << 16) | (SeqNum & 0xFFFF))

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// DENM detection time - special values
typedef enum DENMTimestampTai
{
  /// timestamp = 'use current time'
  DENM_TIMESTAMP_TAI_NOW = 0x00
} eDENMTimestampTai;

/// DENM timestamp, mSec in TAI time @ref DENMTimestampTai
typedef uint64_t TimestampTai;

/// DENM Communications Profile Identifier
typedef enum DENMBTPProfile
{
  /// comunication profile: ITS-GN
  DENM_BTP_PROFILE_ITS_GN = 0x00,
  /// other comunication profile: (unsupported)
  DENM_BTP_PROFILE_OTHER  = 0x80
} eDENMBTPProfile;

/// DENM Communications Profile @ref DENMBTPProfile
typedef uint8_t tDENMBTPProfile;

/// DENM Traffic Class Identifier
typedef enum DENMBTPTC
{
  /// Store-Carry-Forward setting, set or not set
  DENM_BTP_TC_SCF      = 0x80,

  /// Channel offload setting, set or not set
  DENM_BTP_TC_OFFLOAD  = 0x40,

  /// ITS-GN: DP0 to DP32, select one
  DENM_BTP_TC_ITS_DP0  = 0x00,
  DENM_BTP_TC_ITS_DP1  = 0x01,
  DENM_BTP_TC_ITS_DP2  = 0x02,
  DENM_BTP_TC_ITS_DP3  = 0x03,
  DENM_BTP_TC_ITS_DP4  = 0x04,
  DENM_BTP_TC_ITS_DP5  = 0x05,
  DENM_BTP_TC_ITS_DP6  = 0x06,
  DENM_BTP_TC_ITS_DP7  = 0x07,
  DENM_BTP_TC_ITS_DP8  = 0x08,
  DENM_BTP_TC_ITS_DP9  = 0x09,
  DENM_BTP_TC_ITS_DP10 = 0x0A,
  DENM_BTP_TC_ITS_DP11 = 0x0B,
  DENM_BTP_TC_ITS_DP12 = 0x0C,
  DENM_BTP_TC_ITS_DP13 = 0x0D,
  DENM_BTP_TC_ITS_DP14 = 0x0E,
  DENM_BTP_TC_ITS_DP15 = 0x0F,
  DENM_BTP_TC_ITS_DP16 = 0x10,
  DENM_BTP_TC_ITS_DP17 = 0x11,
  DENM_BTP_TC_ITS_DP18 = 0x12,
  DENM_BTP_TC_ITS_DP19 = 0x13,
  DENM_BTP_TC_ITS_DP20 = 0x14,
  DENM_BTP_TC_ITS_DP21 = 0x15,
  DENM_BTP_TC_ITS_DP22 = 0x16,
  DENM_BTP_TC_ITS_DP23 = 0x17,
  DENM_BTP_TC_ITS_DP24 = 0x18,
  DENM_BTP_TC_ITS_DP25 = 0x19,
  DENM_BTP_TC_ITS_DP26 = 0x1A,
  DENM_BTP_TC_ITS_DP27 = 0x1B,
  DENM_BTP_TC_ITS_DP28 = 0x1C,
  DENM_BTP_TC_ITS_DP29 = 0x1D,
  DENM_BTP_TC_ITS_DP30 = 0x1E,
  DENM_BTP_TC_ITS_DP31 = 0x1F,
  DENM_BTP_TC_ITS_DP32 = 0x20

} eDENMBTPTC;

/// DENM Hop Limit
typedef enum DENMBTPHopLimit
{
  /// Use GN default Hop Limit value
  DENM_BTP_HOP_LIMIT_DEFAULT = 0

} eDENMBTPHopLimit;

/// DENM Hop Limit @ref DENMBTPHopLimit
typedef uint8_t tDENMBTPHopLimit;

/// DENM Traffic Class Profile @ref DENMBTPTC
typedef uint8_t tDENMBTPTC;

/// DENM Destination area shape type
typedef enum DenmDestShapeType
{
  /// Circular area
  DENM_DEST_TYPE_CIRCLE = 0x0,
  /// Rectangular area
  DENM_DEST_TYPE_RECT = 0x1,
  /// Ellipsoidal area
  DENM_DEST_TYPE_ELIP = 0x2,

} eDenmDestShapeType;

/// DENM Destination area shape type @ref DenmDestShapeType
typedef uint8_t tDenmDestShapeType;

/// DENM Destination area option
typedef enum DenmDestOption
{
  /// Use provided DestArea
  DENM_DEST_OPTION_PROVIDED = 0x0,
  /// Imply DestArea from eventPosition & relevanceDistance
  DENM_DEST_OPTION_IMPLIED = 0x1,
  /// DestArea from local Position & relevanceDistance
  DENM_DEST_OPTION_LOCAL = 0x2,

} eDenmDestOption;

/// DENM Destination option type @ref DenmDestOption
typedef uint8_t tDenmDestOption;

/// Destination Area information
typedef struct DenmArea_ref
{
  /// WGS-84 latitude for the center position of shape [1/10 micro degrees]
  int32_t Latitude;
  /// WGS-84 longitude for the center position of shape [1/10 micro degrees]
  int32_t Longitude;
  /// Distance a of the geometric shape [metres] (must be non-zero, as always required)
  uint16_t Distance_a;
  /// Distance b of the geometric shape [metres] (required for RECT and ELIP shapes)
  uint16_t Distance_b;
  /// Angle of the geometric shape [degrees] (0 to 359 degrees from North)
  uint16_t Angle;
  /// Shape
  tDenmDestShapeType Shape;
  /// Options
  tDenmDestOption Option;
} tDenmArea;

/// DENM LocationContainer option
typedef enum DenmLocationContainerOption
{
  /// No ITSLocationContainer provided
  DENM_LOC_OPTION_NONE = 0x0,
  /// Use provided ITSLocationContainer from API
  DENM_LOC_OPTION_PROVIDED = 0x1,
  /// Populate ITSLocationContainer eventPositionHeading & eventSpeed from information in FAC layer
  DENM_LOC_OPTION_POPULATE_HEADING_SPEED = 0x2,
  /// Populate ITSLocationContainer traces from ego Path History information in FAC layer
  DENM_LOC_OPTION_POPULATE_TRACE = 0x4,
  /// Populate ITSLocationContainer roadType from information in FAC layer
  DENM_LOC_OPTION_POPULATE_ROADTYPE = 0x8,
  /// Populate ITSLocationContainer from information in FAC layer
  DENM_LOC_OPTION_POPULATE = DENM_LOC_OPTION_POPULATE_HEADING_SPEED | DENM_LOC_OPTION_POPULATE_TRACE | DENM_LOC_OPTION_POPULATE_ROADTYPE,
  /// Populate ITSReferencePosition from information in FAC layer (otherwise ITSReferencePosition must be set via API)
  DENM_LOC_OPTION_EVENT = 0x10,
  /// Check ITSReferencePosition is meaningful (no UNAVAILABLE data)
  DENM_LOC_OPTION_VALID_POS = 0x20,

/// Some options:
/// DENM_LOC_OPTION_NONE: no location container
/// DENM_LOC_OPTION_PROVIDED: location container copied from API
/// DENM_LOC_OPTION_POPULATE: location container set with information in FAC layer
/// DENM_LOC_OPTION_POPULATE + DENM_LOC_OPTION_EVENT: set with information in FAC layer AND eventPosition set as local position
} eDenmLocationContainerOption;

/// DENM LocationContainer option type @ref DenmLocationContainerOption
typedef uint8_t tDenmLocationContainerOption;

/// DENM management
typedef struct DENMMgmt
{
  /// Detection Time in mSec since 2004, DENM_TIMESTAMP_TAI_NOW for 'now'
  TimestampTai detectionTime;

  /// Validity Duration in seconds, VALIDITYDURATIONDEFAULT for default value (ITSdefaultValidity)
  /// (a validityDuration of 0 sec makes no sense) validityDuration needs to be less than
  /// ITSValidityDuration_Limit_Max
  ITSValidityDuration validityDuration;

  /// Repetition Duration in seconds, REPETITIONDURATIONNONE for none
  /// Either repetitionDuration or repetitionDurationSubSec and also
  /// repetitionInterval need to be non-zero for repetition, and both
  /// repetitionDuration and repetitionInterval must be inferior to
  /// validityDuration
  ITSValidityDuration repetitionDuration;
  /// Additional Repetition Duration in mSec (0 to 999 only)
  /// This is added to repetitionDuration, although for short repetition
  /// durations (< 1 sec), set this and leave repetitionDuration as 0
  uint16_t repetitionDurationSubSec;

  /// Repetition Interval in mSec, REPETITIONINTERVALDISABLED for none
  /// To immediately terminate a repetition, set RepetitionDuration to
  /// REPETITIONDURATIONNONE  and RepetitionInterval to
  /// REPETITIONINTERVALTERMINATE
  uint16_t repetitionInterval;

  /// Destination Area
  tDenmArea DestArea;

  /// Comms Profile
  tDENMBTPProfile CommsProfile;
  /// Traffic Class
  tDENMBTPTC TrafficClass;
  /// HopLimit
  tDENMBTPHopLimit HopLimit;

  /// Transmission Interval (for KAF)
  uint16_t TransmissionInterval;
} tDENMMgmt;

/// DENM Status codes
typedef enum DENMStatusCode
{
  /// DENM generation success
  DENM_SUCCESS = 0x00,
  /// DENM generation failure
  DENM_FAILURE_GENERATION = 0x01,
  /// DENM ActionID not existing
  DENM_FAILURE_INVALID_ACTION_ID = 0x02,
  /// DENM Time invalid
  DENM_FAILURE_INVALID_TIME = 0x03,
  /// DENM Position invalid
  DENM_FAILURE_INVALID_POSITION = 0x04,
  /// DENM some parameters invalid
  DENM_FAILURE_INVALID_PARAMS = 0x05,
  /// DENM limits exceeded in structure
  DENM_FAILURE_CONSTRAINT = 0x06,
  /// DENM failed to encode
  DENM_FAILURE_ENCODING = 0x07,
  /// DENM not ready
  DENM_FAILURE_NOT_READY = 0x08,
  /// DENM internal failure
  DENM_FAILURE_INTERNAL = 0x09,
  /// DENM deleted due to ID change
  DENM_FAILURE_IDCHANGE_DELETE = 0x0A,
  /// DENM has been cancelled
  DENM_FAILURE_CANCELLED = 0x0B,

} eDENMStatusCode;

/// Status code for DENM actions @ref DENMStatusCode
typedef uint8_t tDENMStatusCode;

/// Action ID
/// This is made up from station Id and a sequence number managed by the DENM
/// component (so will be unique in V2X environment)
typedef uint64_t tDENMActionID;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger initial DENM, ActionID will be automatically assigned
/// @param pMgmt Pointer to DENM management information, some fields are optional
/// @param pDenm Pointer to DENM message content
/// @param pActionId Pointer to ActionID to set on successful DENM trigger
///        (not set on DENM trigger failure)
/// @return DENM Status Code
tDENMStatusCode DENM_SendDENMTrigger(const tDENMMgmt *pMgmt, const ITSDecentralizedEnvironmentalNotificationMessage *pDenm, tDENMActionID *pActionId);

/// @brief Update a previously triggered DENM using provided ActionId
/// @param pMgmt Pointer to DENM management information, some fields are optional
/// @param pDenm Pointer to DENM message content
/// @param ActionId ActionID provided by DENM_SendDENMTrigger (or user-defined action ID)
/// @return DENM Status Code
tDENMStatusCode DENM_SendDENMUpdate(const tDENMMgmt *pMgmt, const ITSDecentralizedEnvironmentalNotificationMessage *pDenm, tDENMActionID ActionId);

/// @brief Terminate a previously triggered DENM using provided ActionId
/// @param pMgmt Pointer to DENM management information, some fields are optional,
///              also situation, location, alacarte and relevance fields not used
/// @param pDenm Pointer to DENM message content
/// @param ActionId ActionID provided by DENM_SendDENMTrigger (or user-defined action ID)
/// @return DENM Status Code
tDENMStatusCode DENM_SendDENMTermination(const tDENMMgmt *pMgmt, const ITSDecentralizedEnvironmentalNotificationMessage *pDenm, tDENMActionID ActionId);

/// @brief Trigger initial DENM with a user-defined action ID
/// @param pMgmt Pointer to DENM management information, some fields are optional
/// @param pDenm Pointer to DENM message content
/// @param ActionId ActionID provided by ETSIDENM_ACTIONID(StationId,SequenceNumber)
/// @return DENM Status Code
tDENMStatusCode DENM_SendDENMTriggerWithId(const tDENMMgmt *pMgmt, const ITSDecentralizedEnvironmentalNotificationMessage *pDenm, tDENMActionID ActionId);

#ifdef __cplusplus
}
#endif

#endif // __ETS_DENM_ETS_DENM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
