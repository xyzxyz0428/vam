/* Automatically generated file - do not edit */
#ifndef _FFASN1_SAECASN_H
#define _FFASN1_SAECASN_H

#include "asn1defs.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef int SAECDSecond;

extern const ASN1CType asn1_type_SAECDSecond[];

typedef int SAECDYear;

extern const ASN1CType asn1_type_SAECDYear[];

typedef int SAECDMonth;

extern const ASN1CType asn1_type_SAECDMonth[];

typedef int SAECDDay;

extern const ASN1CType asn1_type_SAECDDay[];

typedef int SAECDHour;

extern const ASN1CType asn1_type_SAECDHour[];

typedef int SAECDMinute;

extern const ASN1CType asn1_type_SAECDMinute[];

typedef int SAECDTimeOffset;

extern const ASN1CType asn1_type_SAECDTimeOffset[];

typedef struct SAECDDateTime {
  BOOL year_option;
  SAECDYear year;
  BOOL month_option;
  SAECDMonth month;
  BOOL day_option;
  SAECDDay day;
  BOOL hour_option;
  SAECDHour hour;
  BOOL minute_option;
  SAECDMinute minute;
  BOOL second_option;
  SAECDSecond second;
  BOOL offset_option;
  SAECDTimeOffset offset;
} SAECDDateTime;


extern const ASN1CType asn1_type_SAECDDateTime[];

typedef int SAECMinuteOfTheYear;

extern const ASN1CType asn1_type_SAECMinuteOfTheYear[];

typedef int SAECTimeMark;

extern const ASN1CType asn1_type_SAECTimeMark[];

typedef int SAECTimeOffset;

extern const ASN1CType asn1_type_SAECTimeOffset[];

typedef enum SAECTimeConfidence {
  SAECTimeConfidence_unavailable,
  SAECTimeConfidence_time_100_000,
  SAECTimeConfidence_time_050_000,
  SAECTimeConfidence_time_020_000,
  SAECTimeConfidence_time_010_000,
  SAECTimeConfidence_time_002_000,
  SAECTimeConfidence_time_001_000,
  SAECTimeConfidence_time_000_500,
  SAECTimeConfidence_time_000_200,
  SAECTimeConfidence_time_000_100,
  SAECTimeConfidence_time_000_050,
  SAECTimeConfidence_time_000_020,
  SAECTimeConfidence_time_000_010,
  SAECTimeConfidence_time_000_005,
  SAECTimeConfidence_time_000_002,
  SAECTimeConfidence_time_000_001,
  SAECTimeConfidence_time_000_000_5,
  SAECTimeConfidence_time_000_000_2,
  SAECTimeConfidence_time_000_000_1,
  SAECTimeConfidence_time_000_000_05,
  SAECTimeConfidence_time_000_000_02,
  SAECTimeConfidence_time_000_000_01,
  SAECTimeConfidence_time_000_000_005,
  SAECTimeConfidence_time_000_000_002,
  SAECTimeConfidence_time_000_000_001,
  SAECTimeConfidence_time_000_000_000_5,
  SAECTimeConfidence_time_000_000_000_2,
  SAECTimeConfidence_time_000_000_000_1,
  SAECTimeConfidence_time_000_000_000_05,
  SAECTimeConfidence_time_000_000_000_02,
  SAECTimeConfidence_time_000_000_000_01,
  SAECTimeConfidence_time_000_000_000_005,
  SAECTimeConfidence_time_000_000_000_002,
  SAECTimeConfidence_time_000_000_000_001,
  SAECTimeConfidence_time_000_000_000_000_5,
  SAECTimeConfidence_time_000_000_000_000_2,
  SAECTimeConfidence_time_000_000_000_000_1,
  SAECTimeConfidence_time_000_000_000_000_05,
  SAECTimeConfidence_time_000_000_000_000_02,
  SAECTimeConfidence_time_000_000_000_000_01,
} SAECTimeConfidence;

extern const ASN1CType asn1_type_SAECTimeConfidence[];

typedef int SAECAcceleration;

extern const ASN1CType asn1_type_SAECAcceleration[];

typedef int SAECVerticalAcceleration;

extern const ASN1CType asn1_type_SAECVerticalAcceleration[];

typedef int SAECYawRate;

extern const ASN1CType asn1_type_SAECYawRate[];

typedef struct SAECAccelerationSet4Way {
  SAECAcceleration Long;
  SAECAcceleration lat;
  SAECVerticalAcceleration vert;
  SAECYawRate yaw;
} SAECAccelerationSet4Way;


extern const ASN1CType asn1_type_SAECAccelerationSet4Way[];

typedef int SAECSpeed;

extern const ASN1CType asn1_type_SAECSpeed[];

typedef int SAECHeading;

extern const ASN1CType asn1_type_SAECHeading[];

typedef int SAECCoarseHeading;

extern const ASN1CType asn1_type_SAECCoarseHeading[];

typedef int SAECSteeringWheelAngle;

extern const ASN1CType asn1_type_SAECSteeringWheelAngle[];

typedef enum SAECSpeedConfidence {
  SAECSpeedConfidence_unavailable,
  SAECSpeedConfidence_prec100ms,
  SAECSpeedConfidence_prec10ms,
  SAECSpeedConfidence_prec5ms,
  SAECSpeedConfidence_prec1ms,
  SAECSpeedConfidence_prec0_1ms,
  SAECSpeedConfidence_prec0_05ms,
  SAECSpeedConfidence_prec0_01ms,
} SAECSpeedConfidence;

extern const ASN1CType asn1_type_SAECSpeedConfidence[];

typedef enum SAECHeadingConfidence {
  SAECHeadingConfidence_unavailable,
  SAECHeadingConfidence_prec10deg,
  SAECHeadingConfidence_prec05deg,
  SAECHeadingConfidence_prec01deg,
  SAECHeadingConfidence_prec0_1deg,
  SAECHeadingConfidence_prec0_05deg,
  SAECHeadingConfidence_prec0_01deg,
  SAECHeadingConfidence_prec0_0125deg,
} SAECHeadingConfidence;

extern const ASN1CType asn1_type_SAECHeadingConfidence[];

typedef enum SAECSteeringWheelAngleConfidence {
  SAECSteeringWheelAngleConfidence_unavailable,
  SAECSteeringWheelAngleConfidence_prec2deg,
  SAECSteeringWheelAngleConfidence_prec1deg,
  SAECSteeringWheelAngleConfidence_prec0_02deg,
} SAECSteeringWheelAngleConfidence;

extern const ASN1CType asn1_type_SAECSteeringWheelAngleConfidence[];

typedef struct SAECMotionConfidenceSet {
  BOOL speedCfd_option;
  SAECSpeedConfidence speedCfd;
  BOOL headingCfd_option;
  SAECHeadingConfidence headingCfd;
  BOOL steerCfd_option;
  SAECSteeringWheelAngleConfidence steerCfd;
} SAECMotionConfidenceSet;


extern const ASN1CType asn1_type_SAECMotionConfidenceSet[];

typedef int SAECLatitude;

extern const ASN1CType asn1_type_SAECLatitude[];

typedef int SAECLongitude;

extern const ASN1CType asn1_type_SAECLongitude[];

typedef int SAECElevation;

extern const ASN1CType asn1_type_SAECElevation[];

typedef enum SAECPositionConfidence {
  SAECPositionConfidence_unavailable,
  SAECPositionConfidence_a500m,
  SAECPositionConfidence_a200m,
  SAECPositionConfidence_a100m,
  SAECPositionConfidence_a50m,
  SAECPositionConfidence_a20m,
  SAECPositionConfidence_a10m,
  SAECPositionConfidence_a5m,
  SAECPositionConfidence_a2m,
  SAECPositionConfidence_a1m,
  SAECPositionConfidence_a50cm,
  SAECPositionConfidence_a20cm,
  SAECPositionConfidence_a10cm,
  SAECPositionConfidence_a5cm,
  SAECPositionConfidence_a2cm,
  SAECPositionConfidence_a1cm,
} SAECPositionConfidence;

extern const ASN1CType asn1_type_SAECPositionConfidence[];

typedef enum SAECElevationConfidence {
  SAECElevationConfidence_unavailable,
  SAECElevationConfidence_elev_500_00,
  SAECElevationConfidence_elev_200_00,
  SAECElevationConfidence_elev_100_00,
  SAECElevationConfidence_elev_050_00,
  SAECElevationConfidence_elev_020_00,
  SAECElevationConfidence_elev_010_00,
  SAECElevationConfidence_elev_005_00,
  SAECElevationConfidence_elev_002_00,
  SAECElevationConfidence_elev_001_00,
  SAECElevationConfidence_elev_000_50,
  SAECElevationConfidence_elev_000_20,
  SAECElevationConfidence_elev_000_10,
  SAECElevationConfidence_elev_000_05,
  SAECElevationConfidence_elev_000_02,
  SAECElevationConfidence_elev_000_01,
} SAECElevationConfidence;

extern const ASN1CType asn1_type_SAECElevationConfidence[];

typedef struct SAECPositionConfidenceSet {
  SAECPositionConfidence pos;
  BOOL elevation_option;
  SAECElevationConfidence elevation;
} SAECPositionConfidenceSet;


extern const ASN1CType asn1_type_SAECPositionConfidenceSet[];

typedef struct SAECPosition3D {
  SAECLatitude lat;
  SAECLongitude Long;
  BOOL elevation_option;
  SAECElevation elevation;
} SAECPosition3D;


extern const ASN1CType asn1_type_SAECPosition3D[];

typedef int SAECSemiMajorAxisAccuracy;

extern const ASN1CType asn1_type_SAECSemiMajorAxisAccuracy[];

typedef int SAECSemiMinorAxisAccuracy;

extern const ASN1CType asn1_type_SAECSemiMinorAxisAccuracy[];

typedef int SAECSemiMajorAxisOrientation;

extern const ASN1CType asn1_type_SAECSemiMajorAxisOrientation[];

typedef struct SAECPositionalAccuracy {
  SAECSemiMajorAxisAccuracy semiMajor;
  SAECSemiMinorAxisAccuracy semiMinor;
  SAECSemiMajorAxisOrientation orientation;
} SAECPositionalAccuracy;


extern const ASN1CType asn1_type_SAECPositionalAccuracy[];

typedef int SAECOffsetLL_B12;

extern const ASN1CType asn1_type_SAECOffsetLL_B12[];

typedef struct SAECPosition_LL_24B {
  SAECOffsetLL_B12 lon;
  SAECOffsetLL_B12 lat;
} SAECPosition_LL_24B;


extern const ASN1CType asn1_type_SAECPosition_LL_24B[];

typedef int SAECOffsetLL_B14;

extern const ASN1CType asn1_type_SAECOffsetLL_B14[];

typedef struct SAECPosition_LL_28B {
  SAECOffsetLL_B14 lon;
  SAECOffsetLL_B14 lat;
} SAECPosition_LL_28B;


extern const ASN1CType asn1_type_SAECPosition_LL_28B[];

typedef int SAECOffsetLL_B16;

extern const ASN1CType asn1_type_SAECOffsetLL_B16[];

typedef struct SAECPosition_LL_32B {
  SAECOffsetLL_B16 lon;
  SAECOffsetLL_B16 lat;
} SAECPosition_LL_32B;


extern const ASN1CType asn1_type_SAECPosition_LL_32B[];

typedef int SAECOffsetLL_B18;

extern const ASN1CType asn1_type_SAECOffsetLL_B18[];

typedef struct SAECPosition_LL_36B {
  SAECOffsetLL_B18 lon;
  SAECOffsetLL_B18 lat;
} SAECPosition_LL_36B;


extern const ASN1CType asn1_type_SAECPosition_LL_36B[];

typedef int SAECOffsetLL_B22;

extern const ASN1CType asn1_type_SAECOffsetLL_B22[];

typedef struct SAECPosition_LL_44B {
  SAECOffsetLL_B22 lon;
  SAECOffsetLL_B22 lat;
} SAECPosition_LL_44B;


extern const ASN1CType asn1_type_SAECPosition_LL_44B[];

typedef int SAECOffsetLL_B24;

extern const ASN1CType asn1_type_SAECOffsetLL_B24[];

typedef struct SAECPosition_LL_48B {
  SAECOffsetLL_B24 lon;
  SAECOffsetLL_B24 lat;
} SAECPosition_LL_48B;


extern const ASN1CType asn1_type_SAECPosition_LL_48B[];

typedef struct SAECPosition_LLmD_64b {
  SAECLongitude lon;
  SAECLatitude lat;
} SAECPosition_LLmD_64b;


extern const ASN1CType asn1_type_SAECPosition_LLmD_64b[];

typedef enum {
  SAECPositionOffsetLL_position_LL1,
  SAECPositionOffsetLL_position_LL2,
  SAECPositionOffsetLL_position_LL3,
  SAECPositionOffsetLL_position_LL4,
  SAECPositionOffsetLL_position_LL5,
  SAECPositionOffsetLL_position_LL6,
  SAECPositionOffsetLL_position_LatLon,
} SAECPositionOffsetLL_choice;

typedef struct SAECPositionOffsetLL {
  SAECPositionOffsetLL_choice choice;
  union {
    SAECPosition_LL_24B position_LL1;
    SAECPosition_LL_28B position_LL2;
    SAECPosition_LL_32B position_LL3;
    SAECPosition_LL_36B position_LL4;
    SAECPosition_LL_44B position_LL5;
    SAECPosition_LL_48B position_LL6;
    SAECPosition_LLmD_64b position_LatLon;
  } u;
} SAECPositionOffsetLL;

extern const ASN1CType asn1_type_SAECPositionOffsetLL[];

typedef int SAECVertOffset_B07;

extern const ASN1CType asn1_type_SAECVertOffset_B07[];

typedef int SAECVertOffset_B08;

extern const ASN1CType asn1_type_SAECVertOffset_B08[];

typedef int SAECVertOffset_B09;

extern const ASN1CType asn1_type_SAECVertOffset_B09[];

typedef int SAECVertOffset_B10;

extern const ASN1CType asn1_type_SAECVertOffset_B10[];

typedef int SAECVertOffset_B11;

extern const ASN1CType asn1_type_SAECVertOffset_B11[];

typedef int SAECVertOffset_B12;

extern const ASN1CType asn1_type_SAECVertOffset_B12[];

typedef enum {
  SAECVerticalOffset_offset1,
  SAECVerticalOffset_offset2,
  SAECVerticalOffset_offset3,
  SAECVerticalOffset_offset4,
  SAECVerticalOffset_offset5,
  SAECVerticalOffset_offset6,
  SAECVerticalOffset_elevation,
} SAECVerticalOffset_choice;

typedef struct SAECVerticalOffset {
  SAECVerticalOffset_choice choice;
  union {
    SAECVertOffset_B07 offset1;
    SAECVertOffset_B08 offset2;
    SAECVertOffset_B09 offset3;
    SAECVertOffset_B10 offset4;
    SAECVertOffset_B11 offset5;
    SAECVertOffset_B12 offset6;
    SAECElevation elevation;
  } u;
} SAECVerticalOffset;

extern const ASN1CType asn1_type_SAECVerticalOffset[];

typedef struct SAECPositionOffsetLLV {
  SAECPositionOffsetLL offsetLL;
  BOOL offsetV_option;
  SAECVerticalOffset offsetV;
} SAECPositionOffsetLLV;


extern const ASN1CType asn1_type_SAECPositionOffsetLLV[];

typedef int SAECMsgCount;

extern const ASN1CType asn1_type_SAECMsgCount[];

typedef ASN1String SAECDescriptiveName;

extern const ASN1CType asn1_type_SAECDescriptiveName[];

typedef int SAECRoadRegulatorID;

extern const ASN1CType asn1_type_SAECRoadRegulatorID[];

typedef int SAECNodeID;

extern const ASN1CType asn1_type_SAECNodeID[];

typedef struct SAECNodeReferenceID {
  BOOL region_option;
  SAECRoadRegulatorID region;
  SAECNodeID id;
} SAECNodeReferenceID;


extern const ASN1CType asn1_type_SAECNodeReferenceID[];

typedef ASN1BitString SAECIntersectionStatusObject;

extern const ASN1CType asn1_type_SAECIntersectionStatusObject[];

typedef int SAECPhaseID;

extern const ASN1CType asn1_type_SAECPhaseID[];

typedef enum SAECLightState {
  SAECLightState_unavailable,
  SAECLightState_dark,
  SAECLightState_flashing_red,
  SAECLightState_red,
  SAECLightState_flashing_green,
  SAECLightState_permissive_green,
  SAECLightState_protected_green,
  SAECLightState_yellow,
  SAECLightState_flashing_yellow,
} SAECLightState;

extern const ASN1CType asn1_type_SAECLightState[];

typedef int SAECConfidence;

extern const ASN1CType asn1_type_SAECConfidence[];

typedef struct SAECTimeCountingDown {
  SAECTimeMark startTime;
  BOOL minEndTime_option;
  SAECTimeMark minEndTime;
  BOOL maxEndTime_option;
  SAECTimeMark maxEndTime;
  SAECTimeMark likelyEndTime;
  BOOL timeConfidence_option;
  SAECConfidence timeConfidence;
  BOOL nextStartTime_option;
  SAECTimeMark nextStartTime;
  BOOL nextDuration_option;
  SAECTimeMark nextDuration;
} SAECTimeCountingDown;


extern const ASN1CType asn1_type_SAECTimeCountingDown[];

typedef struct SAECUTCTiming {
  SAECTimeMark startUTCTime;
  BOOL minEndUTCTime_option;
  SAECTimeMark minEndUTCTime;
  BOOL maxEndUTCTime_option;
  SAECTimeMark maxEndUTCTime;
  SAECTimeMark likelyEndUTCTime;
  BOOL timeConfidence_option;
  SAECConfidence timeConfidence;
  BOOL nextStartUTCTime_option;
  SAECTimeMark nextStartUTCTime;
  BOOL nextEndUTCTime_option;
  SAECTimeMark nextEndUTCTime;
} SAECUTCTiming;


extern const ASN1CType asn1_type_SAECUTCTiming[];

typedef enum {
  SAECTimeChangeDetails_counting,
  SAECTimeChangeDetails_utcTiming,
} SAECTimeChangeDetails_choice;

typedef struct SAECTimeChangeDetails {
  SAECTimeChangeDetails_choice choice;
  union {
    SAECTimeCountingDown counting;
    SAECUTCTiming utcTiming;
  } u;
} SAECTimeChangeDetails;

extern const ASN1CType asn1_type_SAECTimeChangeDetails[];

typedef struct SAECPhaseState {
  SAECLightState light;
  BOOL timing_option;
  SAECTimeChangeDetails timing;
} SAECPhaseState;


extern const ASN1CType asn1_type_SAECPhaseState[];

typedef struct SAECPhaseStateList {
  SAECPhaseState *tab;
  size_t count;
} SAECPhaseStateList;

extern const ASN1CType asn1_type_SAECPhaseStateList[];

typedef struct SAECPhase {
  SAECPhaseID id;
  SAECPhaseStateList phaseStates;
} SAECPhase;


extern const ASN1CType asn1_type_SAECPhase[];

typedef struct SAECPhaseList {
  SAECPhase *tab;
  size_t count;
} SAECPhaseList;

extern const ASN1CType asn1_type_SAECPhaseList[];

typedef struct SAECIntersectionState {
  SAECNodeReferenceID intersectionId;
  SAECIntersectionStatusObject status;
  BOOL moy_option;
  SAECMinuteOfTheYear moy;
  BOOL timeStamp_option;
  SAECDSecond timeStamp;
  BOOL timeConfidence_option;
  SAECTimeConfidence timeConfidence;
  SAECPhaseList phases;
} SAECIntersectionState;


extern const ASN1CType asn1_type_SAECIntersectionState[];

typedef struct SAECIntersectionStateList {
  SAECIntersectionState *tab;
  size_t count;
} SAECIntersectionStateList;

extern const ASN1CType asn1_type_SAECIntersectionStateList[];

typedef struct SAECSPAT {
  SAECMsgCount msgCnt;
  BOOL moy_option;
  SAECMinuteOfTheYear moy;
  BOOL timeStamp_option;
  SAECDSecond timeStamp;
  BOOL name_option;
  SAECDescriptiveName name;
  SAECIntersectionStateList intersections;
} SAECSPAT;


extern const ASN1CType asn1_type_SAECSPAT[];

typedef struct SAECRoadPoint {
  SAECPositionOffsetLLV posOffset;
} SAECRoadPoint;


extern const ASN1CType asn1_type_SAECRoadPoint[];

typedef struct SAECPointList {
  SAECRoadPoint *tab;
  size_t count;
} SAECPointList;

extern const ASN1CType asn1_type_SAECPointList[];

typedef int SAECLaneID;

extern const ASN1CType asn1_type_SAECLaneID[];

typedef int SAECLaneWidth;

extern const ASN1CType asn1_type_SAECLaneWidth[];

typedef ASN1BitString SAECLaneSharing;

extern const ASN1CType asn1_type_SAECLaneSharing[];

typedef ASN1BitString SAECLaneAttributes_Vehicle;

extern const ASN1CType asn1_type_SAECLaneAttributes_Vehicle[];

typedef ASN1BitString SAECLaneAttributes_Crosswalk;

extern const ASN1CType asn1_type_SAECLaneAttributes_Crosswalk[];

typedef ASN1BitString SAECLaneAttributes_Bike;

extern const ASN1CType asn1_type_SAECLaneAttributes_Bike[];

typedef ASN1BitString SAECLaneAttributes_Sidewalk;

extern const ASN1CType asn1_type_SAECLaneAttributes_Sidewalk[];

typedef ASN1BitString SAECLaneAttributes_Barrier;

extern const ASN1CType asn1_type_SAECLaneAttributes_Barrier[];

typedef ASN1BitString SAECLaneAttributes_Striping;

extern const ASN1CType asn1_type_SAECLaneAttributes_Striping[];

typedef ASN1BitString SAECLaneAttributes_TrackedVehicle;

extern const ASN1CType asn1_type_SAECLaneAttributes_TrackedVehicle[];

typedef ASN1BitString SAECLaneAttributes_Parking;

extern const ASN1CType asn1_type_SAECLaneAttributes_Parking[];

typedef enum {
  SAECLaneTypeAttributes_vehicle,
  SAECLaneTypeAttributes_crosswalk,
  SAECLaneTypeAttributes_bikeLane,
  SAECLaneTypeAttributes_sidewalk,
  SAECLaneTypeAttributes_median,
  SAECLaneTypeAttributes_striping,
  SAECLaneTypeAttributes_trackedVehicle,
  SAECLaneTypeAttributes_parking,
} SAECLaneTypeAttributes_choice;

typedef struct SAECLaneTypeAttributes {
  SAECLaneTypeAttributes_choice choice;
  union {
    SAECLaneAttributes_Vehicle vehicle;
    SAECLaneAttributes_Crosswalk crosswalk;
    SAECLaneAttributes_Bike bikeLane;
    SAECLaneAttributes_Sidewalk sidewalk;
    SAECLaneAttributes_Barrier median;
    SAECLaneAttributes_Striping striping;
    SAECLaneAttributes_TrackedVehicle trackedVehicle;
    SAECLaneAttributes_Parking parking;
  } u;
} SAECLaneTypeAttributes;

extern const ASN1CType asn1_type_SAECLaneTypeAttributes[];

typedef struct SAECLaneAttributes {
  BOOL shareWith_option;
  SAECLaneSharing shareWith;
  SAECLaneTypeAttributes laneType;
} SAECLaneAttributes;


extern const ASN1CType asn1_type_SAECLaneAttributes[];

typedef ASN1BitString SAECAllowedManeuvers;

extern const ASN1CType asn1_type_SAECAllowedManeuvers[];

typedef struct SAECConnectingLane {
  SAECLaneID lane;
  BOOL maneuver_option;
  SAECAllowedManeuvers maneuver;
} SAECConnectingLane;


extern const ASN1CType asn1_type_SAECConnectingLane[];

typedef struct SAECConnection {
  SAECNodeReferenceID remoteIntersection;
  BOOL connectingLane_option;
  SAECConnectingLane connectingLane;
  BOOL phaseId_option;
  SAECPhaseID phaseId;
} SAECConnection;


extern const ASN1CType asn1_type_SAECConnection[];

typedef struct SAECConnectsToList {
  SAECConnection *tab;
  size_t count;
} SAECConnectsToList;

extern const ASN1CType asn1_type_SAECConnectsToList[];

typedef enum SAECSpeedLimitType {
  SAECSpeedLimitType_unknown,
  SAECSpeedLimitType_maxSpeedInSchoolZone,
  SAECSpeedLimitType_maxSpeedInSchoolZoneWhenChildrenArePresent,
  SAECSpeedLimitType_maxSpeedInConstructionZone,
  SAECSpeedLimitType_vehicleMinSpeed,
  SAECSpeedLimitType_vehicleMaxSpeed,
  SAECSpeedLimitType_vehicleNightMaxSpeed,
  SAECSpeedLimitType_truckMinSpeed,
  SAECSpeedLimitType_truckMaxSpeed,
  SAECSpeedLimitType_truckNightMaxSpeed,
  SAECSpeedLimitType_vehiclesWithTrailersMinSpeed,
  SAECSpeedLimitType_vehiclesWithTrailersMaxSpeed,
  SAECSpeedLimitType_vehiclesWithTrailersNightMaxSpeed,
} SAECSpeedLimitType;

extern const ASN1CType asn1_type_SAECSpeedLimitType[];

typedef struct SAECRegulatorySpeedLimit {
  SAECSpeedLimitType type;
  SAECSpeed speed;
} SAECRegulatorySpeedLimit;


extern const ASN1CType asn1_type_SAECRegulatorySpeedLimit[];

typedef struct SAECSpeedLimitList {
  SAECRegulatorySpeedLimit *tab;
  size_t count;
} SAECSpeedLimitList;

extern const ASN1CType asn1_type_SAECSpeedLimitList[];

typedef struct SAECLane {
  SAECLaneID laneID;
  BOOL laneWidth_option;
  SAECLaneWidth laneWidth;
  BOOL laneAttributes_option;
  SAECLaneAttributes laneAttributes;
  BOOL maneuvers_option;
  SAECAllowedManeuvers maneuvers;
  BOOL connectsTo_option;
  SAECConnectsToList connectsTo;
  BOOL speedLimits_option;
  SAECSpeedLimitList speedLimits;
  BOOL points_option;
  SAECPointList points;
} SAECLane;


extern const ASN1CType asn1_type_SAECLane[];

typedef struct SAECLaneList {
  SAECLane *tab;
  size_t count;
} SAECLaneList;

extern const ASN1CType asn1_type_SAECLaneList[];

typedef struct SAECMovement {
  SAECNodeReferenceID remoteIntersection;
  BOOL phaseId_option;
  SAECPhaseID phaseId;
} SAECMovement;


extern const ASN1CType asn1_type_SAECMovement[];

typedef struct SAECMovementList {
  SAECMovement *tab;
  size_t count;
} SAECMovementList;

extern const ASN1CType asn1_type_SAECMovementList[];

typedef struct SAECLink {
  BOOL name_option;
  SAECDescriptiveName name;
  SAECNodeReferenceID upstreamNodeId;
  BOOL speedLimits_option;
  SAECSpeedLimitList speedLimits;
  SAECLaneWidth linkWidth;
  BOOL points_option;
  SAECPointList points;
  BOOL movements_option;
  SAECMovementList movements;
  SAECLaneList lanes;
} SAECLink;


extern const ASN1CType asn1_type_SAECLink[];

typedef struct SAECLinkList {
  SAECLink *tab;
  size_t count;
} SAECLinkList;

extern const ASN1CType asn1_type_SAECLinkList[];

typedef struct SAECNode {
  BOOL name_option;
  SAECDescriptiveName name;
  SAECNodeReferenceID id;
  SAECPosition3D refPos;
  BOOL inLinks_option;
  SAECLinkList inLinks;
} SAECNode;


extern const ASN1CType asn1_type_SAECNode[];

typedef struct SAECNodeList {
  SAECNode *tab;
  size_t count;
} SAECNodeList;

extern const ASN1CType asn1_type_SAECNodeList[];

typedef struct SAECMapData {
  SAECMsgCount msgCnt;
  BOOL timeStamp_option;
  SAECMinuteOfTheYear timeStamp;
  SAECNodeList nodes;
} SAECMapData;


extern const ASN1CType asn1_type_SAECMapData[];

typedef enum SAECParticipantType {
  SAECParticipantType_unknown,
  SAECParticipantType_motor,
  SAECParticipantType_non_motor,
  SAECParticipantType_pedestrian,
  SAECParticipantType_rsu,
} SAECParticipantType;

extern const ASN1CType asn1_type_SAECParticipantType[];

typedef enum SAECSourceType {
  SAECSourceType_unknown,
  SAECSourceType_selfinfo,
  SAECSourceType_v2x,
  SAECSourceType_video,
  SAECSourceType_microwaveRadar,
  SAECSourceType_loop,
  SAECSourceType_lidar,
  SAECSourceType_integrated,
} SAECSourceType;

extern const ASN1CType asn1_type_SAECSourceType[];

typedef enum SAECTransmissionState {
  SAECTransmissionState_neutral,
  SAECTransmissionState_park,
  SAECTransmissionState_forwardGears,
  SAECTransmissionState_reverseGears,
  SAECTransmissionState_reserved1,
  SAECTransmissionState_reserved2,
  SAECTransmissionState_reserved3,
  SAECTransmissionState_unavailable,
} SAECTransmissionState;

extern const ASN1CType asn1_type_SAECTransmissionState[];

typedef int SAECVehicleWidth;

extern const ASN1CType asn1_type_SAECVehicleWidth[];

typedef int SAECVehicleLength;

extern const ASN1CType asn1_type_SAECVehicleLength[];

typedef int SAECVehicleHeight;

extern const ASN1CType asn1_type_SAECVehicleHeight[];

typedef struct SAECVehicleSize {
  SAECVehicleWidth width;
  SAECVehicleLength length;
  BOOL height_option;
  SAECVehicleHeight height;
} SAECVehicleSize;


extern const ASN1CType asn1_type_SAECVehicleSize[];

typedef int SAECBasicVehicleClass;

extern const ASN1CType asn1_type_SAECBasicVehicleClass[];

typedef int SAECFuelType;

extern const ASN1CType asn1_type_SAECFuelType[];

typedef struct SAECVehicleClassification {
  SAECBasicVehicleClass classification;
  BOOL fuelType_option;
  SAECFuelType fuelType;
} SAECVehicleClassification;


extern const ASN1CType asn1_type_SAECVehicleClassification[];

typedef struct SAECParticipantData {
  SAECParticipantType ptcType;
  int ptcId;
  SAECSourceType source;
  BOOL id_option;
  ASN1String id;
  SAECDSecond secMark;
  SAECPositionOffsetLLV pos;
  SAECPositionConfidenceSet posConfidence;
  BOOL transmission_option;
  SAECTransmissionState transmission;
  SAECSpeed speed;
  SAECHeading heading;
  BOOL angle_option;
  SAECSteeringWheelAngle angle;
  BOOL motionCfd_option;
  SAECMotionConfidenceSet motionCfd;
  BOOL accelSet_option;
  SAECAccelerationSet4Way accelSet;
  SAECVehicleSize size;
  BOOL vehicleClass_option;
  SAECVehicleClassification vehicleClass;
} SAECParticipantData;


extern const ASN1CType asn1_type_SAECParticipantData[];

typedef struct SAECParticipantList {
  SAECParticipantData *tab;
  size_t count;
} SAECParticipantList;

extern const ASN1CType asn1_type_SAECParticipantList[];

typedef struct SAECRoadsideSafetyMessage {
  SAECMsgCount msgCnt;
  ASN1String id;
  SAECPosition3D refPos;
  SAECParticipantList participants;
} SAECRoadsideSafetyMessage;


extern const ASN1CType asn1_type_SAECRoadsideSafetyMessage[];

typedef int SAECEventType;

extern const ASN1CType asn1_type_SAECEventType[];

typedef enum SAECEventSource {
  SAECEventSource_unknown,
  SAECEventSource_police,
  SAECEventSource_government,
  SAECEventSource_meteorological,
  SAECEventSource_internet,
  SAECEventSource_detection,
} SAECEventSource;

extern const ASN1CType asn1_type_SAECEventSource[];

typedef int SAECRadius;

extern const ASN1CType asn1_type_SAECRadius[];

typedef enum {
  SAECDescription_textString,
  SAECDescription_textGB2312,
} SAECDescription_choice;

typedef struct SAECDescription {
  SAECDescription_choice choice;
  union {
    ASN1String textString;
    ASN1String textGB2312;
  } u;
} SAECDescription;

extern const ASN1CType asn1_type_SAECDescription[];

typedef struct SAECRSITimeDetails {
  BOOL startTime_option;
  SAECMinuteOfTheYear startTime;
  BOOL endTime_option;
  SAECMinuteOfTheYear endTime;
  BOOL endTimeConfidence_option;
  SAECTimeConfidence endTimeConfidence;
} SAECRSITimeDetails;


extern const ASN1CType asn1_type_SAECRSITimeDetails[];

typedef ASN1String SAECRSIPriority;

extern const ASN1CType asn1_type_SAECRSIPriority[];

typedef struct SAECPathPointList {
  SAECPositionOffsetLLV *tab;
  size_t count;
} SAECPathPointList;

extern const ASN1CType asn1_type_SAECPathPointList[];

typedef struct SAECReferencePath {
  SAECPathPointList activePath;
  SAECRadius pathRadius;
} SAECReferencePath;


extern const ASN1CType asn1_type_SAECReferencePath[];

typedef struct SAECReferencePathList {
  SAECReferencePath *tab;
  size_t count;
} SAECReferencePathList;

extern const ASN1CType asn1_type_SAECReferencePathList[];

typedef ASN1BitString SAECReferenceLanes;

extern const ASN1CType asn1_type_SAECReferenceLanes[];

typedef struct SAECReferenceLink {
  SAECNodeReferenceID upstreamNodeId;
  SAECNodeReferenceID downstreamNodeId;
  BOOL referenceLanes_option;
  SAECReferenceLanes referenceLanes;
} SAECReferenceLink;


extern const ASN1CType asn1_type_SAECReferenceLink[];

typedef struct SAECReferenceLinkList {
  SAECReferenceLink *tab;
  size_t count;
} SAECReferenceLinkList;

extern const ASN1CType asn1_type_SAECReferenceLinkList[];

typedef struct SAECRTEData {
  int rteId;
  SAECEventType eventType;
  SAECEventSource eventSource;
  BOOL eventPos_option;
  SAECPositionOffsetLLV eventPos;
  BOOL eventRadius_option;
  SAECRadius eventRadius;
  BOOL description_option;
  SAECDescription description;
  BOOL timeDetails_option;
  SAECRSITimeDetails timeDetails;
  BOOL priority_option;
  SAECRSIPriority priority;
  BOOL referencePaths_option;
  SAECReferencePathList referencePaths;
  BOOL referenceLinks_option;
  SAECReferenceLinkList referenceLinks;
  BOOL eventConfidence_option;
  SAECConfidence eventConfidence;
} SAECRTEData;


extern const ASN1CType asn1_type_SAECRTEData[];

typedef struct SAECRTEList {
  SAECRTEData *tab;
  size_t count;
} SAECRTEList;

extern const ASN1CType asn1_type_SAECRTEList[];

typedef int SAECSignType;

extern const ASN1CType asn1_type_SAECSignType[];

typedef struct SAECRTSData {
  int rtsId;
  SAECSignType signType;
  BOOL signPos_option;
  SAECPositionOffsetLLV signPos;
  BOOL description_option;
  SAECDescription description;
  BOOL timeDetails_option;
  SAECRSITimeDetails timeDetails;
  BOOL priority_option;
  SAECRSIPriority priority;
  BOOL referencePaths_option;
  SAECReferencePathList referencePaths;
  BOOL referenceLinks_option;
  SAECReferenceLinkList referenceLinks;
} SAECRTSData;


extern const ASN1CType asn1_type_SAECRTSData[];

typedef struct SAECRTSList {
  SAECRTSData *tab;
  size_t count;
} SAECRTSList;

extern const ASN1CType asn1_type_SAECRTSList[];

typedef struct SAECRoadSideInformation {
  SAECMsgCount msgCnt;
  BOOL moy_option;
  SAECMinuteOfTheYear moy;
  ASN1String id;
  SAECPosition3D refPos;
  BOOL rtes_option;
  SAECRTEList rtes;
  BOOL rtss_option;
  SAECRTSList rtss;
} SAECRoadSideInformation;


extern const ASN1CType asn1_type_SAECRoadSideInformation[];

typedef enum SAECBrakePedalStatus {
  SAECBrakePedalStatus_unavailable,
  SAECBrakePedalStatus_off,
  SAECBrakePedalStatus_on,
} SAECBrakePedalStatus;

extern const ASN1CType asn1_type_SAECBrakePedalStatus[];

typedef ASN1BitString SAECBrakeAppliedStatus;

extern const ASN1CType asn1_type_SAECBrakeAppliedStatus[];

typedef enum SAECTractionControlStatus {
  SAECTractionControlStatus_unavailable,
  SAECTractionControlStatus_off,
  SAECTractionControlStatus_on,
  SAECTractionControlStatus_engaged,
} SAECTractionControlStatus;

extern const ASN1CType asn1_type_SAECTractionControlStatus[];

typedef enum SAECAntiLockBrakeStatus {
  SAECAntiLockBrakeStatus_unavailable,
  SAECAntiLockBrakeStatus_off,
  SAECAntiLockBrakeStatus_on,
  SAECAntiLockBrakeStatus_engaged,
} SAECAntiLockBrakeStatus;

extern const ASN1CType asn1_type_SAECAntiLockBrakeStatus[];

typedef enum SAECStabilityControlStatus {
  SAECStabilityControlStatus_unavailable,
  SAECStabilityControlStatus_off,
  SAECStabilityControlStatus_on,
  SAECStabilityControlStatus_engaged,
} SAECStabilityControlStatus;

extern const ASN1CType asn1_type_SAECStabilityControlStatus[];

typedef enum SAECBrakeBoostApplied {
  SAECBrakeBoostApplied_unavailable,
  SAECBrakeBoostApplied_off,
  SAECBrakeBoostApplied_on,
} SAECBrakeBoostApplied;

extern const ASN1CType asn1_type_SAECBrakeBoostApplied[];

typedef enum SAECAuxiliaryBrakeStatus {
  SAECAuxiliaryBrakeStatus_unavailable,
  SAECAuxiliaryBrakeStatus_off,
  SAECAuxiliaryBrakeStatus_on,
  SAECAuxiliaryBrakeStatus_reserved,
} SAECAuxiliaryBrakeStatus;

extern const ASN1CType asn1_type_SAECAuxiliaryBrakeStatus[];

typedef struct SAECBrakeSystemStatus {
  BOOL brakePadel_option;
  SAECBrakePedalStatus brakePadel;
  BOOL wheelBrakes_option;
  SAECBrakeAppliedStatus wheelBrakes;
  BOOL traction_option;
  SAECTractionControlStatus traction;
  BOOL abs_option;
  SAECAntiLockBrakeStatus abs;
  BOOL scs_option;
  SAECStabilityControlStatus scs;
  BOOL brakeBoost_option;
  SAECBrakeBoostApplied brakeBoost;
  BOOL auxBrakes_option;
  SAECAuxiliaryBrakeStatus auxBrakes;
} SAECBrakeSystemStatus;


extern const ASN1CType asn1_type_SAECBrakeSystemStatus[];

#define SAECunknownVehicleClass 0

#define SAECspecialVehicleClass 1

#define SAECpassenger_Vehicle_TypeUnknown 10

#define SAECpassenger_Vehicle_TypeOther 11

#define SAEClightTruck_Vehicle_TypeUnknown 20

#define SAEClightTruck_Vehicle_TypeOther 21

#define SAECtruck_Vehicle_TypeUnknown 25

#define SAECtruck_Vehicle_TypeOther 26

#define SAECtruck_axleCnt2 27

#define SAECtruck_axleCnt3 28

#define SAECtruck_axleCnt4 29

#define SAECtruck_axleCnt4Trailer 30

#define SAECtruck_axleCnt5Trailer 31

#define SAECtruck_axleCnt6Trailer 32

#define SAECtruck_axleCnt5MultiTrailer 33

#define SAECtruck_axleCnt6MultiTrailer 34

#define SAECtruck_axleCnt7MultiTrailer 35

#define SAECmotorcycle_TypeUnknown 40

#define SAECmotorcycle_TypeOther 41

#define SAECmotorcycle_Cruiser_Standard 42

#define SAECmotorcycle_SportUnclad 43

#define SAECmotorcycle_SportTouring 44

#define SAECmotorcycle_SuperSport 45

#define SAECmotorcycle_Touring 46

#define SAECmotorcycle_Trike 47

#define SAECmotorcycle_wPassengers 48

#define SAECtransit_TypeUnknown 50

#define SAECtransit_TypeOther 51

#define SAECtransit_BRT 52

#define SAECtransit_ExpressBus 53

#define SAECtransit_LocalBus 54

#define SAECtransit_SchoolBus 55

#define SAECtransit_FixedGuideway 56

#define SAECtransit_Paratransit 57

#define SAECtransit_Paratransit_Ambulance 58

#define SAECemergency_TypeUnknown 60

#define SAECemergency_TypeOther 61

#define SAECemergency_Fire_Light_Vehicle 62

#define SAECemergency_Fire_Heavy_Vehicle 63

#define SAECemergency_Fire_Paramedic_Vehicle 64

#define SAECemergency_Fire_Ambulance_Vehicle 65

#define SAECemergency_Police_Light_Vehicle 66

#define SAECemergency_Police_Heavy_Vehicle 67

#define SAECemergency_Other_Responder 68

#define SAECemergency_Other_Ambulance 69

#define SAECotherTraveler_TypeUnknown 80

#define SAECotherTraveler_TypeOther 81

#define SAECotherTraveler_Pedestrian 82

#define SAECotherTraveler_Visually_Disabled 83

#define SAECotherTraveler_Physically_Disabled 84

#define SAECotherTraveler_Bicycle 85

#define SAECotherTraveler_Vulnerable_Roadworker 86

#define SAECinfrastructure_TypeUnknown 90

#define SAECinfrastructure_Fixed 91

#define SAECinfrastructure_Movable 92

#define SAECequipped_CargoTrailer 93

#define SAECunknownFuel 0

#define SAECgasoline 1

#define SAECethanol 2

#define SAECdiesel 3

#define SAECelectric 4

#define SAEChybrid 5

#define SAEChydrogen 6

#define SAECnatGasLiquid 7

#define SAECnatGasComp 8

#define SAECpropane 9

typedef enum SAECResponseType {
  SAECResponseType_notInUseOrNotEquipped,
  SAECResponseType_emergency,
  SAECResponseType_nonEmergency,
  SAECResponseType_pursuit,
  SAECResponseType_stationary,
  SAECResponseType_slowMoving,
  SAECResponseType_stopAndGoMovement,
} SAECResponseType;

extern const ASN1CType asn1_type_SAECResponseType[];

typedef enum SAECSirenInUse {
  SAECSirenInUse_unavailable,
  SAECSirenInUse_notInUse,
  SAECSirenInUse_inUse,
  SAECSirenInUse_reserved,
} SAECSirenInUse;

extern const ASN1CType asn1_type_SAECSirenInUse[];

typedef enum SAECLightbarInUse {
  SAECLightbarInUse_unavailable,
  SAECLightbarInUse_notInUse,
  SAECLightbarInUse_inUse,
  SAECLightbarInUse_yellowCautionLights,
  SAECLightbarInUse_schooldBusLights,
  SAECLightbarInUse_arrowSignsActive,
  SAECLightbarInUse_slowMovingVehicle,
  SAECLightbarInUse_freqStops,
} SAECLightbarInUse;

extern const ASN1CType asn1_type_SAECLightbarInUse[];

typedef struct SAECVehicleEmergencyExtensions {
  BOOL responseType_option;
  SAECResponseType responseType;
  BOOL sirenUse_option;
  SAECSirenInUse sirenUse;
  BOOL lightsUse_option;
  SAECLightbarInUse lightsUse;
} SAECVehicleEmergencyExtensions;


extern const ASN1CType asn1_type_SAECVehicleEmergencyExtensions[];

typedef ASN1BitString SAECVehicleEventFlags;

extern const ASN1CType asn1_type_SAECVehicleEventFlags[];

typedef struct SAECFullPositionVector {
  BOOL utcTime_option;
  SAECDDateTime utcTime;
  SAECPosition3D pos;
  BOOL heading_option;
  SAECHeading heading;
  BOOL transmission_option;
  SAECTransmissionState transmission;
  BOOL speed_option;
  SAECSpeed speed;
  BOOL posAccuracy_option;
  SAECPositionConfidenceSet posAccuracy;
  BOOL timeConfidence_option;
  SAECTimeConfidence timeConfidence;
  BOOL motionCfd_option;
  SAECMotionConfidenceSet motionCfd;
} SAECFullPositionVector;


extern const ASN1CType asn1_type_SAECFullPositionVector[];

typedef ASN1BitString SAECGNSSstatus;

extern const ASN1CType asn1_type_SAECGNSSstatus[];

typedef struct SAECPathHistoryPoint {
  SAECPositionOffsetLLV llvOffset;
  SAECTimeOffset timeOffset;
  BOOL speed_option;
  SAECSpeed speed;
  BOOL posAccuracy_option;
  SAECPositionConfidenceSet posAccuracy;
  BOOL heading_option;
  SAECCoarseHeading heading;
} SAECPathHistoryPoint;


extern const ASN1CType asn1_type_SAECPathHistoryPoint[];

typedef struct SAECPathHistoryPointList {
  SAECPathHistoryPoint *tab;
  size_t count;
} SAECPathHistoryPointList;

extern const ASN1CType asn1_type_SAECPathHistoryPointList[];

typedef struct SAECPathHistory {
  BOOL initialPosition_option;
  SAECFullPositionVector initialPosition;
  BOOL currGNSSstatus_option;
  SAECGNSSstatus currGNSSstatus;
  SAECPathHistoryPointList crumbData;
} SAECPathHistory;


extern const ASN1CType asn1_type_SAECPathHistory[];

typedef int SAECRadiusOfCurvature;

extern const ASN1CType asn1_type_SAECRadiusOfCurvature[];

typedef struct SAECPathPrediction {
  SAECRadiusOfCurvature radiusOfCurve;
  SAECConfidence confidence;
} SAECPathPrediction;


extern const ASN1CType asn1_type_SAECPathPrediction[];

typedef ASN1BitString SAECExteriorLights;

extern const ASN1CType asn1_type_SAECExteriorLights[];

typedef struct SAECVehicleSafetyExtensions {
  BOOL events_option;
  SAECVehicleEventFlags events;
  BOOL pathHistory_option;
  SAECPathHistory pathHistory;
  BOOL pathPrediction_option;
  SAECPathPrediction pathPrediction;
  BOOL lights_option;
  SAECExteriorLights lights;
} SAECVehicleSafetyExtensions;


extern const ASN1CType asn1_type_SAECVehicleSafetyExtensions[];

typedef struct SAECBasicSafetyMessage {
  SAECMsgCount msgCnt;
  ASN1String id;
  SAECDSecond secMark;
  BOOL timeConfidence_option;
  SAECTimeConfidence timeConfidence;
  SAECPosition3D pos;
  BOOL posAccuracy_option;
  SAECPositionalAccuracy posAccuracy;
  BOOL posConfidence_option;
  SAECPositionConfidenceSet posConfidence;
  SAECTransmissionState transmission;
  SAECSpeed speed;
  SAECHeading heading;
  BOOL angle_option;
  SAECSteeringWheelAngle angle;
  BOOL motionCfd_option;
  SAECMotionConfidenceSet motionCfd;
  SAECAccelerationSet4Way accelSet;
  SAECBrakeSystemStatus brakes;
  SAECVehicleSize size;
  SAECVehicleClassification vehicleClass;
  BOOL safetyExt_option;
  SAECVehicleSafetyExtensions safetyExt;
  BOOL emergencyExt_option;
  SAECVehicleEmergencyExtensions emergencyExt;
} SAECBasicSafetyMessage;


extern const ASN1CType asn1_type_SAECBasicSafetyMessage[];

typedef enum {
  SAECMessageFrame_bsmFrame,
  SAECMessageFrame_mapFrame,
  SAECMessageFrame_rsmFrame,
  SAECMessageFrame_spatFrame,
  SAECMessageFrame_rsiFrame,
} SAECMessageFrame_choice;

typedef struct SAECMessageFrame {
  SAECMessageFrame_choice choice;
  union {
    SAECBasicSafetyMessage bsmFrame;
    SAECMapData mapFrame;
    SAECRoadsideSafetyMessage rsmFrame;
    SAECSPAT spatFrame;
    SAECRoadSideInformation rsiFrame;
  } u;
} SAECMessageFrame;

extern const ASN1CType asn1_type_SAECMessageFrame[];

#ifdef  __cplusplus
}
#endif

#endif /* _FFASN1_SAECASN_H */
