/**
 * @addtogroup ets_app_facilities_c2c_api ETSI ITS Facilities C2C API
 * @{
 *
 * Interface to provide abstract C2C DENM triggering and operations based on
 * C2C-CC Basic System Standards Profile document
 *
 * The client can use this to have higher-level controls for C2C DENM
 * triggering and CAM vehicle role changes, without having to utilise the
 * lower-level and more complex DENM and CAM APIs directly (@ref
 * ets_app_facilities_denm_api and @ref ets_app_facilities_cam_api)
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_FAC_ETS_FAC_C2C_IF_H_
#define __ETS_FAC_ETS_FAC_C2C_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// No validity duration
#define C2C_VALIDITYDURATIONDEFAULT 0
/// Maximum validity duration
#define C2C_VALIDITYDURATIONMAX 86400

/// No repetition
#define C2C_REPETITIONINTERVALDISABLED 0

/// Get Station Id from action ID created by C2C_SendDENMTrigger
#define C2C_ACTIONID_STATION(ActionId) ((ActionId >> 16) & 0xFFFFFFFF)
/// Get Sequence Number from action ID created by C2C_SendDENMTrigger
#define C2C_ACTIONID_SEQNUM(ActionId) (ActionId & 0xFFFF)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// C2C Relevance Distance
/// Use 'doNotInclude' if item is not required
typedef enum C2CRelevanceDistance
{
  C2CRelevanceDistance_lessThan50m,
  C2CRelevanceDistance_lessThan100m,
  C2CRelevanceDistance_lessThan200m,
  C2CRelevanceDistance_lessThan500m,
  C2CRelevanceDistance_lessThan1000m,
  C2CRelevanceDistance_lessThan5km,
  C2CRelevanceDistance_lessThan10km,
  C2CRelevanceDistance_over10km,

  C2CRelevanceDistance_doNotInclude

} eC2CRelevanceDistance;

/// C2C Relevance Distance type @ref C2CRelevanceDistance
typedef uint8_t tC2CRelevanceDistance;

/// C2C Relevance Traffic Direction
/// Use 'doNotInclude' if item is not required
typedef enum C2CRelevanceTrafficDirection
{
  C2CRelevanceTrafficDirection_allTrafficDirections,
  C2CRelevanceTrafficDirection_upstreamTraffic,
  C2CRelevanceTrafficDirection_downstreamTraffic,
  C2CRelevanceTrafficDirection_oppositeTraffic,

  C2CRelevanceTrafficDirection_doNotInclude

} eC2CRelevanceTrafficDirection;

/// C2C Relevance Traffic Direction type @ref C2CRelevanceTrafficDirection
typedef uint8_t tC2CRelevanceTrafficDirection;

/// C2C Information Quality
/// Item is mandatory
typedef enum C2CInformationQuality
{
  C2CInformationQuality_unavailable = 0,
  C2CInformationQuality_lowest = 1,
  C2CInformationQuality_1 = 1,
  C2CInformationQuality_2 = 2,
  C2CInformationQuality_3 = 3,
  C2CInformationQuality_4 = 4,
  C2CInformationQuality_5 = 5,
  C2CInformationQuality_6 = 6,
  C2CInformationQuality_7 = 7,
  C2CInformationQuality_highest = 7

} eC2CInformationQuality;

/// C2C Information Quality type @ref C2CInformationQuality
typedef uint8_t tC2CInformationQuality;

/// C2C Cause Code
/// Item is mandatory
/// Only relevant C2C cause codes are defined. All codes defined in ITSCauseCodeType.
typedef enum C2CCauseCode
{
  C2CCauseCodeType_ID_trafficCondition = 1,
  C2CCauseCodeType_ID_adverseWeatherCondition_Adhesion = 6,
  C2CCauseCodeType_ID_rescueAndRecoveryWorkInProgress = 15,
  C2CCauseCodeType_ID_adverseWeatherCondition_Visibility = 18,
  C2CCauseCodeType_ID_adverseWeatherCondition_Precipitation = 19,
  C2CCauseCodeType_ID_dangerousEndOfQueue = 27,
  C2CCauseCodeType_ID_stationaryVehicle = 94,
  C2CCauseCodeType_ID_emergencyVehicleApproaching = 95,
  C2CCauseCodeType_ID_collisionRisk = 97,
  C2CCauseCodeType_ID_dangerousSituation = 99
} eC2CCauseCode;

/// C2C Cause Code type @ref C2CCauseCode
/// Indicate DENM cause code
typedef uint16_t tC2CCauseCode;

/// C2C Sub Cause Code
/// Item is mandatory
/// Only relevant C2C sub-cause codes are defined. All codes defined in ITSSubCauseCodeType.
typedef enum C2CSubCauseCode
{
  C2CAdverseWeatherCondition_AdhesionSubCauseCode_ID_unavailable = 0,

  C2CAdverseWeatherCondition_PrecipitationSubCauseCode_ID_unavailable = 0,
  C2CAdverseWeatherCondition_PrecipitationSubCauseCode_ID_heavyRain = 1,
  C2CAdverseWeatherCondition_PrecipitationSubCauseCode_ID_heavySnowfall = 2,

  C2CAdverseWeatherCondition_VisibilitySubCauseCode_ID_unavailable = 0,
  C2CAdverseWeatherCondition_VisibilitySubCauseCode_ID_fog = 1,

  C2CCollisionRiskSubCauseCode_ID_unavailable = 0,
  C2CCollisionRiskSubCauseCode_ID_preCrashInformation = 5,

  C2CDangerousEndOfQueueSubCauseCode_ID_unavailable = 0,

  C2CDangerousSituationSubCauseCode_ID_emergencyElectronicBrakeEngaged = 1,
  C2CDangerousSituationSubCauseCode_ID_preCrashSystemEngaged = 2,
  C2CDangerousSituationSubCauseCode_ID_aebEngaged = 5,

  C2CEmergencyVehicleApproachingSubCauseCode_ID_emergencyVehicleApproaching = 1,

  C2CRescueAndRecoveryWorkInProgressSubCauseCode_ID_unavailable = 0,
  C2CRescueAndRecoveryWorkInProgressSubCauseCode_ID_emergencyVehicles = 1,

  C2CStationaryVehicleSubCauseCode_ID_unavailable = 0,
  C2CStationaryVehicleSubCauseCode_ID_vehicleBreakdown = 2,
  C2CStationaryVehicleSubCauseCode_ID_postCrash = 3,

  C2CTrafficConditionSubCauseCode_ID_unavailable = 0
} eC2CSubCauseCode;

/// C2C Sub Cause Code type @ref C2CSubCauseCode
/// Indicate DENM sub-cause code
typedef uint16_t tC2CSubCauseCode;

/// C2C Linked Cause Code
/// Item is optional
/// Same values as C2C cause codes, or able indicate that it is not used
typedef enum C2CLinkedCauseCode
{
  C2CLinkedCauseCodeType_ID_doNotInclude = 0
  // Otherwise use eC2CCauseCode
} eC2CLinkedCauseCode;

/// C2C Linked Cause Code type @ref C2CLinkedCauseCode
/// Indicate linked DENM cause code (if required)
typedef uint16_t tC2CLinkedCauseCode;

/// C2C IRC Request ResponseIndication
typedef enum C2CIRCRequestResponseIndication
{
  C2CIRCRequestResponseIndication_request,
  C2CIRCRequestResponseIndication_response,

  C2CIRCRequestResponseIndication_doNotInclude

} eC2CIRCRequestResponseIndication;

/// C2C IRC Request Response Indication type @ref C2CIRCRequestResponseIndication
typedef uint8_t tC2CIRCRequestResponseIndication;

/// C2C Stationary Since
/// Define some convenient values, or use own numerical value up to 65535 seconds
typedef enum C2CStationarySince
{
  C2CStationarySince_doNotInclude = 0,

  C2CStationarySince_1Second = 1,
  C2CStationarySince_1Minute = 60,
  C2CStationarySince_2Minutes = 120,
  C2CStationarySince_15Minutes = 900,
  C2CStationarySince_1Hour = 3600,

  C2CStationarySince_Max = 65535

} eC2CStationarySince;

/// C2C Stationary Since type @ref C2CStationarySince
/// Indicate stationary time in completed seconds
typedef uint16_t tC2CStationarySince;

typedef enum C2CStationID {
  C2CStationID_doNotInclude = 0

} eC2CStationID;

/// C2C PreCrash StationID @ref C2CStationID
typedef uint32_t tC2CStationID;

/// C2C PreCrash PerceivedObject Identifier type
typedef uint8_t tC2CIdentifier;

typedef enum C2CTimeOfMeasurement {
  C2CTimeOfMeasurement_maxPast = -1500,
  C2CTimeOfMeasurement_now = 0,
  C2CTimeOfMeasurement_oneMilliSecondFuture = 1,
  C2CTimeOfMeasurement_maxFuture = 1500

} eC2CTimeOfMeasurement;

/// C2C PreCrash TimeOfMeasurement type @ref C2CTimeOfMeasurement
typedef int16_t tC2CTimeOfMeasurement;

typedef enum C2CObjDistanceConfidence {
  C2CDistanceConfidence_minLimit = 0,
  C2CDistanceConfidence_zeroPointZeroOneMeter = 1,
  C2CDistanceConfidence_oneMeter = 100,
  C2CDistanceConfidence_maxLimit = 100,

  C2CDistanceConfidence_outOfRange = 101,
  C2CDistanceConfidence_unavailable = 102
} eC2CObjDistanceConfidence;

/// C2C PreCrash Object DistanceConfidence type @ref C2CObjDistanceConfidence
typedef uint8_t tC2CObjDistanceConfidence;

typedef enum C2CObjDistanceValue {
  C2CObjDistanceValue_minLimit = -132768,
  C2CObjDistanceValue_zeroPointZeroOneMeter = 1,
  C2CObjDistanceValue_oneMeter = 100,
  C2CObjDistanceValue_maxLimit = 132767
} eC2CObjDistanceValue;

/// C2C PreCrash Object DistanceValue type @ref C2CObjDistanceValue
typedef int32_t tC2CObjDistanceValue;

typedef struct C2CObjDistance {
  tC2CObjDistanceValue value;
  tC2CObjDistanceConfidence confidence;
} tC2CObjDistance;

typedef enum C2CSpeedValueExtended {
  C2CSpeedValueExtended_minLimit = -16383,
  C2CSpeedValueExtended_standstill = 0,
  C2CSpeedValueExtended_oneCentimeterPerSec = 1,
  C2CSpeedValueExtended_maxLimit = 16382,
  C2CSpeedValueExtended_unavailable = 16383
} eC2CSpeedValueExtended;

/// C2C PreCrash Object SpeedValueExtended type @ref C2CSpeedValueExtended
typedef int16_t tC2CSpeedValueExtended;

typedef enum C2CSpeedConfidence {
  C2CSpeedConfidence_equalOrWithinOneCentimeterPerSec = 1,
  C2CSpeedConfidence_equalOrWithinOneMeterPerSec = 100,
  C2CSpeedConfidence_outOfRange = 126,
  C2CSpeedConfidence_unavailable = 127
} eC2CSpeedConfidence;

/// C2C PreCrash Object SpeedConfidence type @ref C2CSpeedConfidence
typedef int16_t tC2CSpeedConfidence;

typedef struct C2CSpeedExtended {
  tC2CSpeedValueExtended value;
  tC2CSpeedConfidence confidence;
} tC2CSpeedExtended;

typedef enum C2CAngleValue {
  C2CAngleValue_zeroPointOneDegree = 1,
  C2CAngleValue_oneDegree = 10,
  C2CAngleValue_unavailable = 3601
} eC2CAngleValue;

/// C2C PreCrash AngleValue @ref C2CAngleValue
typedef uint16_t tC2CAngleValue;

typedef enum C2CAngleConfidence {
  C2CAngleConfidence_zeroPointOneDegree = 1,
  C2CAngleConfidence_oneDegree = 10,
  C2CAngleConfidence_outOfRange = 126,
  C2CAngleConfidence_unavailable = 127
} eC2CAngleConfidence;

/// C2C PreCrash AngleConfidence @ref C2CAngleConfidence
typedef uint16_t tC2CAngleConfidence;

/// C2C PreCrash Angle
typedef struct C2CAngle {
  tC2CAngleValue value;
  tC2CAngleConfidence confidence;
} tC2CAngle;

typedef enum C2CObjectDimensionValue {
  C2CObjectDimensionValue_minLimit = 0,
  C2CObjectDimensionValue_zeroPointOneMeter = 1,
  C2CObjectDimensionValue_oneMeter = 10,
  C2CObjectDimensionValue_maxLimit = 1023
} eC2CObjectDimensionValue;

/// C2C PreCrash ObjectDimension Value @ref C2CObjectDimensionValue
typedef uint16_t tC2CObjectDimensionValue;

typedef enum C2CObjectDimensionConfidence {
  C2CObjectDimensionConfidence_zeroPointZeroOneMeter = 1,
  C2CObjectDimensionConfidence_oneMeter = 100,
  C2CObjectDimensionConfidence_outOfRange = 101,
  C2CObjectDimensionConfidence_unavailable = 102,
} eC2CObjectDimensionConfidence;

/// C2C PreCrash ObjectDimension Confidence @ref C2CObjectDimensionConfidence
typedef uint16_t tC2CObjectDimensionConfidence;

/// C2C PreCrash Object Dimension
typedef struct C2CObjectDimension {
  tC2CObjectDimensionValue value;
  tC2CObjectDimensionConfidence confidence;
} tC2CObjectDimension;

typedef enum C2CObjectRefPoint {
  C2CObjectRefPoint_mid,
  C2CObjectRefPoint_bottomLeft,
  C2CObjectRefPoint_midLeft,
  C2CObjectRefPoint_topLeft,
  C2CObjectRefPoint_bottomMid,
  C2CObjectRefPoint_topMid,
  C2CObjectRefPoint_bottomRight,
  C2CObjectRefPoint_midRight,
  C2CObjectRefPoint_topRight
} eC2CObjectRefPoint;

/// C2C PreCrash Object RefPoint @ref C2CObjectRefPoint
typedef uint8_t tC2CObjectRefPoint;

/// C2C PreCrash Perceived Object
typedef struct C2CPerceivedObject {
  /// Identifier of the object
  tC2CIdentifier objectID;
  /// Relative time (in milliseconds) when sensor provided information
  tC2CTimeOfMeasurement timeOfMeasurement_ms;
  /// X-component of relative distance (cm)
  tC2CObjDistance xDistance_cm;
  /// Y-component of relative distance (cm)
  tC2CObjDistance yDistance_cm;
  /// X-component of relative speed (cm per second)
  tC2CSpeedExtended xSpeed_cmps;
  /// Y-component of relative speed (cm per second)
  tC2CSpeedExtended ySpeed_cmps;
  /// Flag indicating inclusion of YawAngle information
  bool yawAngleCartesian_option;
  /// Relative angle (tenths of degrees) of object
  tC2CAngle yawAngleCartesian;
  /// Perceived width (0.1m) of the side of the object
  tC2CObjectDimension planarObjectDimensionWidth;
  /// Object reference point
  tC2CObjectRefPoint objectRefPoint;
} tC2CPerceivedObject;

typedef enum C2CTimeToCollision {
  C2CTimeToCollision_oneMilliSecond = 1,
  C2CTimeToCollision_tenSeconds = 10000,

  C2CTimeToCollision_doNotInclude = 10001
} eC2CTimeToCollision;

/// C2C PreCrash TimeToCollision type @ref C2CTimeToCollision
typedef uint16_t tC2CTimeToCollision;

typedef enum C2CImpactSection {
  C2CImpactSection_unavailable = 0,
  C2CImpactSection_rear = 1,
  C2CImpactSection_front = 2,
  C2CImpactSection_sideLeftFront = 3,
  C2CImpactSection_sideLeftBack = 4,
  C2CImpactSection_sideRightFront = 5,
  C2CImpactSection_sideRightBack = 6,

  C2CImpactSection_doNotInclude = 7
} eC2CImpactSection;

/// C2C PreCrash ImpactSection type @ref C2CImpactSection
typedef uint8_t tC2CImpactSection;

/// C2C PreCrash Container
/// Define data for preCrash Alacarte
typedef struct C2CPreCrashContainer {
  /// Perceived object information for PreCrash target
  tC2CPerceivedObject perceivedObject;
  /// StationId for PreCrash target
  tC2CStationID objectStationId;
  /// TimeToCollision (in milliseconds) to PreCrash target
  tC2CTimeToCollision timeToCollision_ms;
  /// ImpactSection expected for PreCrash target
  tC2CImpactSection impactSection;
  /// Absolute orientation (tenths of degrees) for ego in WGS84
  tC2CAngle hostVehicleOrientationWGS84;
} tC2CPreCrashContainer;

/// C2C Traffic Class Identifier
/// ITS-GN: DP0 to DP3, select one
/// Note: DP2 reserved for CAMs
typedef enum C2CGNTC
{
  /// Urgent DENMs
  C2C_GN_TC_DP0_URGENT_DENM  = 0x00,
  /// Less Urgent DENMs
  C2C_GN_TC_DP1_NORMAL_DENM  = 0x01,
  /// Low priority DENMs
  C2C_GN_TC_DP3_LOW_PRIORITY_DENM  = 0x03

} eC2CGNTC;

/// C2C Traffic Class Profile @ref C2CGNTC
typedef uint8_t tC2CGNTC;

/// DENM Hop Limit
typedef enum C2CGNHopLimit
{
  /// Use C2C default Hop Limit value
  /// GN Hoplimit set according to C2CCC rules based on destination area radius
  C2C_GN_HOP_LIMIT_DEFAULT = 0

  // Otherwise use numerical value for maximum number of hops
} eC2CGNHopLimit;

/// DENM Hop Limit @ref C2CGNHopLimit
/// Indicate hop limit in numerical value if using a specific value
/// Otherwise set to C2C_GN_HOP_LIMIT_DEFAULT if not applicable or
/// if default value is to be used.
typedef uint8_t tC2CGNHopLimit;

/// DENM management
typedef struct C2CMgmt
{
  /// Validity Duration, 0 for default value (defaultValidity)
  /// (a validityDuration of 0 sec makes no sense)
  uint32_t ValidityDuration_s;

  /// Repetition Duration in seconds, 0 for none
  /// Either repetitionDuration or repetitionDurationSubSec and also
  /// repetitionInterval need to be non-zero for repetition, and both
  /// repetitionDuration and repetitionInterval must be inferior to
  /// validityDuration
  uint32_t RepetitionDuration_s;
  /// Additional Repetition Duration in mSec (0 to 999 only)
  /// This is added to repetitionDuration, although for short repetition
  /// durations (< 1 sec), set this and leave repetitionDuration as 0
  uint16_t RepetitionDurationSubSec_ms;

  /// Repetition Interval (mS), 0 for none
  uint16_t RepetitionInterval_ms;

  /// Relevance distance (optional)
  tC2CRelevanceDistance RelevanceDistance;

  /// Relevance traffic direction (optional)
  tC2CRelevanceTrafficDirection RelevanceTrafficDirection;

  /// Information Quality (mandatory)
  tC2CInformationQuality InformationQuality;

  /// Situation Container (situation container always included)
  /// Cause Code (mandatory)
  tC2CCauseCode CauseCode;
  /// Sub Cause Code (mandatory)
  tC2CSubCauseCode SubCauseCode;
  /// Linked Cause Code (optional)
  tC2CLinkedCauseCode LinkedCauseCode;

  /// Event History present (optional)
  /// Use the event information from previous DENM trigger
  /// as next position in eventHistory (pos/time/infoQuality)
  bool EventHistory_populate;

  /// Location Container (if all optional items not present, then no Location container)

  /// Event Speed & Event Position Heading (optional)
  /// Populate eventSpeed and eventPositionHeading from current vehicle information
  bool EventSpeedHeading_populate;

  /// Traces (a.k.a. Path History) (optional)
  /// Populate Traces with vehicle path history as single trace from current position information
  bool PathHistory_populate;

  /// Note: RoadType in Location Container included if any of
  /// EventSpeedHeading_populate or PathHistory_populate included

  /// AlaCarte Container (if all optional items not present, then no AlaCarte container)

  /// Lane Position (optional)
  /// Populate LanePosition from current vehicle information
  bool LanePosition_populate;

  /// Impact Reduction Container type (optional)
  /// If enabled, populate ImpactReductionContainer from current vehicle information (or configuration)
  tC2CIRCRequestResponseIndication IRCType;
  /// Stationary Since (optional)
  /// Optionally include user-provided value, with time in seconds
  tC2CStationarySince StationarySince;

  /// PreCrash Container (optional)
  /// Populate PreCrash Container from provided information
  bool PreCrashContainer_option;
  /// Provide PreCrash Container information
  tC2CPreCrashContainer PreCrashContainer;

  /// GN Traffic Class (mandatory)
  tC2CGNTC TrafficClass;

  /// GN Hop Limit (mandatory, but can set default value)
  tC2CGNHopLimit HopLimit;

  // Other GN parameters using default values
  // e.g. destination area implied from relevance area

} tC2CMgmt;

/// C2C Vehicle Role
typedef enum C2CVehicleRole
{
  C2CVehicleRole_specialTransport,
  C2CVehicleRole_dangerousGoods,
  C2CVehicleRole_roadWork,
  C2CVehicleRole_recovery_service,
  C2CVehicleRole_emergency_undercover,
  C2CVehicleRole_emergency_response,
  C2CVehicleRole_emergency_safeguarding,
  C2CVehicleRole_safetyCar,

} eC2CVehicleRole;

/// C2C Vehicle Role type @ref C2CVehicleRole
typedef uint8_t tC2CVehicleRole;

/// C2C Status codes
typedef enum C2CStatusCode
{
  /// C2C success
  C2C_SUCCESS = 0x00,
  /// C2C failure
  C2C_FAILURE = 0x01,
  /// C2C generation failure
  C2C_FAILURE_GENERATION = 0x02,
  /// C2C ActionID not existing
  C2C_FAILURE_INVALID_ACTION_ID = 0x03,
  /// C2C Time invalid
  C2C_FAILURE_INVALID_TIME = 0x04,
  /// C2C some parameters invalid
  C2C_FAILURE_INVALID_PARAMS = 0x05,
  /// C2C failed to encode
  C2C_FAILURE_ENCODING = 0x06,
  /// C2C not ready
  C2C_FAILURE_NOT_READY = 0x07,
  /// C2C ActionID invalid due to ID change
  C2C_FAILURE_INVALID_ACTION_ID_IDCHANGE = 0x08,

} eC2CStatusCode;

/// Status code for C2C actions @ref C2CStatusCode
typedef uint8_t tC2CStatusCode;

/// Action ID
/// This is made up from station Id and a sequence number managed by the DENM
/// component (so will be unique in V2X environment)
typedef uint64_t tC2CActionID;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger initial DENM, ActionID will be automatically assigned
/// @param pInfo Pointer to C2C management information
/// @param pActionId Pointer to ActionID to set on successful DENM trigger
///        (not set on DENM trigger failure)
/// @return C2C Status Code
tC2CStatusCode C2C_SendDENMTrigger(const tC2CMgmt *pInfo, tC2CActionID *pActionId);

/// @brief Update a previously triggered DENM using provided ActionId
/// @param pInfo Pointer to C2C management information
/// @param ActionId ActionID provided by C2C_SendDENMTrigger
/// @return C2C Status Code
tC2CStatusCode C2C_SendDENMUpdate(const tC2CMgmt *pInfo, tC2CActionID ActionId);

/// @brief Terminate a previously triggered DENM using provided ActionId
/// @param pInfo Pointer to C2C management information
/// @param ActionId ActionID provided by C2C_SendDENMTrigger
/// @return C2C Status Code
tC2CStatusCode C2C_SendDENMTermination(const tC2CMgmt *pInfo, tC2CActionID ActionId);

/// @brief Update CAM special vehicle information
/// @param Role Vehicle role to activate
/// @return C2C Status Code
tC2CStatusCode C2C_ActivateSpecialRole(tC2CVehicleRole Role);

/// @brief Clear CAM special vehicle information
/// @return C2C Status Code
tC2CStatusCode C2C_DeactivateSpecialVehicle(void);

#ifdef __cplusplus
}
#endif

#endif // __ETS_FAC_ETS_FAC_C2C_IF_H_

// Close the Doxygen group
/**
 * @}
 */
