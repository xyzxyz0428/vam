/* Automatically generated file - do not edit */
#ifndef _FFASN1_J2735ASN_H
#define _FFASN1_J2735ASN_H

#include "asn1defs.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef int SAEDSRCmsgID;

extern const ASN1CType asn1_type_SAEDSRCmsgID[];

typedef struct SAEMessageFrame {
  SAEDSRCmsgID messageId;
  ASN1OpenType value;
} SAEMessageFrame;


extern const ASN1CType asn1_type_SAEMessageFrame[];

typedef struct SAEMESSAGE_ID_AND_TYPE { /* object class definition */
  ASN1CType id;
  ASN1CType Type;
} SAEMESSAGE_ID_AND_TYPE;


extern const ASN1CType asn1_type_SAEMESSAGE_ID_AND_TYPE[];

typedef int SAEMsgCount;

extern const ASN1CType asn1_type_SAEMsgCount[];

typedef ASN1String SAETemporaryID;

extern const ASN1CType asn1_type_SAETemporaryID[];

typedef int SAEDSecond;

extern const ASN1CType asn1_type_SAEDSecond[];

typedef int SAELatitude;

extern const ASN1CType asn1_type_SAELatitude[];

typedef int SAELongitude;

extern const ASN1CType asn1_type_SAELongitude[];

typedef int SAEElevation;

extern const ASN1CType asn1_type_SAEElevation[];

typedef int SAESemiMajorAxisAccuracy;

extern const ASN1CType asn1_type_SAESemiMajorAxisAccuracy[];

typedef int SAESemiMinorAxisAccuracy;

extern const ASN1CType asn1_type_SAESemiMinorAxisAccuracy[];

typedef int SAESemiMajorAxisOrientation;

extern const ASN1CType asn1_type_SAESemiMajorAxisOrientation[];

typedef struct SAEPositionalAccuracy {
  SAESemiMajorAxisAccuracy semiMajor;
  SAESemiMinorAxisAccuracy semiMinor;
  SAESemiMajorAxisOrientation orientation;
} SAEPositionalAccuracy;


extern const ASN1CType asn1_type_SAEPositionalAccuracy[];

typedef enum SAETransmissionState {
  SAETransmissionState_neutral,
  SAETransmissionState_park,
  SAETransmissionState_forwardGears,
  SAETransmissionState_reverseGears,
  SAETransmissionState_reserved1,
  SAETransmissionState_reserved2,
  SAETransmissionState_reserved3,
  SAETransmissionState_unavailable,
} SAETransmissionState;

extern const ASN1CType asn1_type_SAETransmissionState[];

typedef int SAESpeed;

extern const ASN1CType asn1_type_SAESpeed[];

typedef int SAEHeading;

extern const ASN1CType asn1_type_SAEHeading[];

typedef int SAESteeringWheelAngle;

extern const ASN1CType asn1_type_SAESteeringWheelAngle[];

typedef int SAEAcceleration;

extern const ASN1CType asn1_type_SAEAcceleration[];

typedef int SAEVerticalAcceleration;

extern const ASN1CType asn1_type_SAEVerticalAcceleration[];

typedef int SAEYawRate;

extern const ASN1CType asn1_type_SAEYawRate[];

typedef struct SAEAccelerationSet4Way {
  SAEAcceleration Long;
  SAEAcceleration lat;
  SAEVerticalAcceleration vert;
  SAEYawRate yaw;
} SAEAccelerationSet4Way;


extern const ASN1CType asn1_type_SAEAccelerationSet4Way[];

typedef ASN1BitString SAEBrakeAppliedStatus;

extern const ASN1CType asn1_type_SAEBrakeAppliedStatus[];

typedef enum SAETractionControlStatus {
  SAETractionControlStatus_unavailable,
  SAETractionControlStatus_off,
  SAETractionControlStatus_on,
  SAETractionControlStatus_engaged,
} SAETractionControlStatus;

extern const ASN1CType asn1_type_SAETractionControlStatus[];

typedef enum SAEAntiLockBrakeStatus {
  SAEAntiLockBrakeStatus_unavailable,
  SAEAntiLockBrakeStatus_off,
  SAEAntiLockBrakeStatus_on,
  SAEAntiLockBrakeStatus_engaged,
} SAEAntiLockBrakeStatus;

extern const ASN1CType asn1_type_SAEAntiLockBrakeStatus[];

typedef enum SAEStabilityControlStatus {
  SAEStabilityControlStatus_unavailable,
  SAEStabilityControlStatus_off,
  SAEStabilityControlStatus_on,
  SAEStabilityControlStatus_engaged,
} SAEStabilityControlStatus;

extern const ASN1CType asn1_type_SAEStabilityControlStatus[];

typedef enum SAEBrakeBoostApplied {
  SAEBrakeBoostApplied_unavailable,
  SAEBrakeBoostApplied_off,
  SAEBrakeBoostApplied_on,
} SAEBrakeBoostApplied;

extern const ASN1CType asn1_type_SAEBrakeBoostApplied[];

typedef enum SAEAuxiliaryBrakeStatus {
  SAEAuxiliaryBrakeStatus_unavailable,
  SAEAuxiliaryBrakeStatus_off,
  SAEAuxiliaryBrakeStatus_on,
  SAEAuxiliaryBrakeStatus_reserved,
} SAEAuxiliaryBrakeStatus;

extern const ASN1CType asn1_type_SAEAuxiliaryBrakeStatus[];

typedef struct SAEBrakeSystemStatus {
  SAEBrakeAppliedStatus wheelBrakes;
  SAETractionControlStatus traction;
  SAEAntiLockBrakeStatus abs;
  SAEStabilityControlStatus scs;
  SAEBrakeBoostApplied brakeBoost;
  SAEAuxiliaryBrakeStatus auxBrakes;
} SAEBrakeSystemStatus;


extern const ASN1CType asn1_type_SAEBrakeSystemStatus[];

typedef int SAEVehicleWidth;

extern const ASN1CType asn1_type_SAEVehicleWidth[];

typedef int SAEVehicleLength;

extern const ASN1CType asn1_type_SAEVehicleLength[];

typedef struct SAEVehicleSize {
  SAEVehicleWidth width;
  SAEVehicleLength length;
} SAEVehicleSize;


extern const ASN1CType asn1_type_SAEVehicleSize[];

typedef struct SAEBSMcoreData {
  SAEMsgCount msgCnt;
  SAETemporaryID id;
  SAEDSecond secMark;
  SAELatitude lat;
  SAELongitude Long;
  SAEElevation elev;
  SAEPositionalAccuracy accuracy;
  SAETransmissionState transmission;
  SAESpeed speed;
  SAEHeading heading;
  SAESteeringWheelAngle angle;
  SAEAccelerationSet4Way accelSet;
  SAEBrakeSystemStatus brakes;
  SAEVehicleSize size;
} SAEBSMcoreData;


extern const ASN1CType asn1_type_SAEBSMcoreData[];

typedef int SAEPartII_Id;

extern const ASN1CType asn1_type_SAEPartII_Id[];

typedef struct SAEPartIIcontent_1 {
  SAEPartII_Id partII_Id;
  ASN1OpenType partII_Value;
} SAEPartIIcontent_1;


extern const ASN1CType asn1_type_SAEPartIIcontent_1[];

typedef struct SAEBasicSafetyMessage_1 {
  SAEPartIIcontent_1 *tab;
  size_t count;
} SAEBasicSafetyMessage_1;

extern const ASN1CType asn1_type_SAEBasicSafetyMessage_1[];

typedef int SAERegionId;

extern const ASN1CType asn1_type_SAERegionId[];

typedef struct SAERegionalExtension_1 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_1;


extern const ASN1CType asn1_type_SAERegionalExtension_1[];

typedef struct SAEBasicSafetyMessage_2 {
  SAERegionalExtension_1 *tab;
  size_t count;
} SAEBasicSafetyMessage_2;

extern const ASN1CType asn1_type_SAEBasicSafetyMessage_2[];

typedef struct SAEBasicSafetyMessage {
  SAEBSMcoreData coreData;
  BOOL partII_option;
  SAEBasicSafetyMessage_1 partII;
  BOOL regional_option;
  SAEBasicSafetyMessage_2 regional;
} SAEBasicSafetyMessage;


extern const ASN1CType asn1_type_SAEBasicSafetyMessage[];

typedef int SAEMinuteOfTheYear;

extern const ASN1CType asn1_type_SAEMinuteOfTheYear[];

typedef enum SAELayerType {
  SAELayerType_none,
  SAELayerType_mixedContent,
  SAELayerType_generalMapData,
  SAELayerType_intersectionData,
  SAELayerType_curveData,
  SAELayerType_roadwaySectionData,
  SAELayerType_parkingAreaData,
  SAELayerType_sharedLaneData,
} SAELayerType;

extern const ASN1CType asn1_type_SAELayerType[];

typedef int SAELayerID;

extern const ASN1CType asn1_type_SAELayerID[];

typedef ASN1String SAEDescriptiveName;

extern const ASN1CType asn1_type_SAEDescriptiveName[];

typedef int SAERoadRegulatorID;

extern const ASN1CType asn1_type_SAERoadRegulatorID[];

typedef int SAEIntersectionID;

extern const ASN1CType asn1_type_SAEIntersectionID[];

typedef struct SAEIntersectionReferenceID {
  BOOL region_option;
  SAERoadRegulatorID region;
  SAEIntersectionID id;
} SAEIntersectionReferenceID;


extern const ASN1CType asn1_type_SAEIntersectionReferenceID[];

typedef struct SAERegionalExtension_49 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_49;


extern const ASN1CType asn1_type_SAERegionalExtension_49[];

typedef struct SAEPosition3D_1 {
  SAERegionalExtension_49 *tab;
  size_t count;
} SAEPosition3D_1;

extern const ASN1CType asn1_type_SAEPosition3D_1[];

typedef struct SAEPosition3D {
  SAELatitude lat;
  SAELongitude Long;
  BOOL elevation_option;
  SAEElevation elevation;
  BOOL regional_option;
  SAEPosition3D_1 regional;
} SAEPosition3D;


extern const ASN1CType asn1_type_SAEPosition3D[];

typedef int SAELaneWidth;

extern const ASN1CType asn1_type_SAELaneWidth[];

typedef enum SAESpeedLimitType {
  SAESpeedLimitType_unknown,
  SAESpeedLimitType_maxSpeedInSchoolZone,
  SAESpeedLimitType_maxSpeedInSchoolZoneWhenChildrenArePresent,
  SAESpeedLimitType_maxSpeedInConstructionZone,
  SAESpeedLimitType_vehicleMinSpeed,
  SAESpeedLimitType_vehicleMaxSpeed,
  SAESpeedLimitType_vehicleNightMaxSpeed,
  SAESpeedLimitType_truckMinSpeed,
  SAESpeedLimitType_truckMaxSpeed,
  SAESpeedLimitType_truckNightMaxSpeed,
  SAESpeedLimitType_vehiclesWithTrailersMinSpeed,
  SAESpeedLimitType_vehiclesWithTrailersMaxSpeed,
  SAESpeedLimitType_vehiclesWithTrailersNightMaxSpeed,
} SAESpeedLimitType;

extern const ASN1CType asn1_type_SAESpeedLimitType[];

typedef int SAEVelocity;

extern const ASN1CType asn1_type_SAEVelocity[];

typedef struct SAERegulatorySpeedLimit {
  SAESpeedLimitType type;
  SAEVelocity speed;
} SAERegulatorySpeedLimit;


extern const ASN1CType asn1_type_SAERegulatorySpeedLimit[];

typedef struct SAESpeedLimitList {
  SAERegulatorySpeedLimit *tab;
  size_t count;
} SAESpeedLimitList;

extern const ASN1CType asn1_type_SAESpeedLimitList[];

typedef int SAELaneID;

extern const ASN1CType asn1_type_SAELaneID[];

typedef int SAEApproachID;

extern const ASN1CType asn1_type_SAEApproachID[];

typedef ASN1BitString SAELaneDirection;

extern const ASN1CType asn1_type_SAELaneDirection[];

typedef ASN1BitString SAELaneSharing;

extern const ASN1CType asn1_type_SAELaneSharing[];

typedef ASN1BitString SAELaneAttributes_Vehicle;

extern const ASN1CType asn1_type_SAELaneAttributes_Vehicle[];

typedef ASN1BitString SAELaneAttributes_Crosswalk;

extern const ASN1CType asn1_type_SAELaneAttributes_Crosswalk[];

typedef ASN1BitString SAELaneAttributes_Bike;

extern const ASN1CType asn1_type_SAELaneAttributes_Bike[];

typedef ASN1BitString SAELaneAttributes_Sidewalk;

extern const ASN1CType asn1_type_SAELaneAttributes_Sidewalk[];

typedef ASN1BitString SAELaneAttributes_Barrier;

extern const ASN1CType asn1_type_SAELaneAttributes_Barrier[];

typedef ASN1BitString SAELaneAttributes_Striping;

extern const ASN1CType asn1_type_SAELaneAttributes_Striping[];

typedef ASN1BitString SAELaneAttributes_TrackedVehicle;

extern const ASN1CType asn1_type_SAELaneAttributes_TrackedVehicle[];

typedef ASN1BitString SAELaneAttributes_Parking;

extern const ASN1CType asn1_type_SAELaneAttributes_Parking[];

typedef enum {
  SAELaneTypeAttributes_vehicle,
  SAELaneTypeAttributes_crosswalk,
  SAELaneTypeAttributes_bikeLane,
  SAELaneTypeAttributes_sidewalk,
  SAELaneTypeAttributes_median,
  SAELaneTypeAttributes_striping,
  SAELaneTypeAttributes_trackedVehicle,
  SAELaneTypeAttributes_parking,
} SAELaneTypeAttributes_choice;

typedef struct SAELaneTypeAttributes {
  SAELaneTypeAttributes_choice choice;
  union {
    SAELaneAttributes_Vehicle vehicle;
    SAELaneAttributes_Crosswalk crosswalk;
    SAELaneAttributes_Bike bikeLane;
    SAELaneAttributes_Sidewalk sidewalk;
    SAELaneAttributes_Barrier median;
    SAELaneAttributes_Striping striping;
    SAELaneAttributes_TrackedVehicle trackedVehicle;
    SAELaneAttributes_Parking parking;
  } u;
} SAELaneTypeAttributes;

extern const ASN1CType asn1_type_SAELaneTypeAttributes[];

typedef struct SAERegionalExtension_41 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_41;


extern const ASN1CType asn1_type_SAERegionalExtension_41[];

typedef struct SAELaneAttributes {
  SAELaneDirection directionalUse;
  SAELaneSharing sharedWith;
  SAELaneTypeAttributes laneType;
  BOOL regional_option;
  SAERegionalExtension_41 regional;
} SAELaneAttributes;


extern const ASN1CType asn1_type_SAELaneAttributes[];

typedef ASN1BitString SAEAllowedManeuvers;

extern const ASN1CType asn1_type_SAEAllowedManeuvers[];

typedef int SAEOffset_B10;

extern const ASN1CType asn1_type_SAEOffset_B10[];

typedef struct SAENode_XY_20b {
  SAEOffset_B10 x;
  SAEOffset_B10 y;
} SAENode_XY_20b;


extern const ASN1CType asn1_type_SAENode_XY_20b[];

typedef int SAEOffset_B11;

extern const ASN1CType asn1_type_SAEOffset_B11[];

typedef struct SAENode_XY_22b {
  SAEOffset_B11 x;
  SAEOffset_B11 y;
} SAENode_XY_22b;


extern const ASN1CType asn1_type_SAENode_XY_22b[];

typedef int SAEOffset_B12;

extern const ASN1CType asn1_type_SAEOffset_B12[];

typedef struct SAENode_XY_24b {
  SAEOffset_B12 x;
  SAEOffset_B12 y;
} SAENode_XY_24b;


extern const ASN1CType asn1_type_SAENode_XY_24b[];

typedef int SAEOffset_B13;

extern const ASN1CType asn1_type_SAEOffset_B13[];

typedef struct SAENode_XY_26b {
  SAEOffset_B13 x;
  SAEOffset_B13 y;
} SAENode_XY_26b;


extern const ASN1CType asn1_type_SAENode_XY_26b[];

typedef int SAEOffset_B14;

extern const ASN1CType asn1_type_SAEOffset_B14[];

typedef struct SAENode_XY_28b {
  SAEOffset_B14 x;
  SAEOffset_B14 y;
} SAENode_XY_28b;


extern const ASN1CType asn1_type_SAENode_XY_28b[];

typedef int SAEOffset_B16;

extern const ASN1CType asn1_type_SAEOffset_B16[];

typedef struct SAENode_XY_32b {
  SAEOffset_B16 x;
  SAEOffset_B16 y;
} SAENode_XY_32b;


extern const ASN1CType asn1_type_SAENode_XY_32b[];

typedef struct SAENode_LLmD_64b {
  SAELongitude lon;
  SAELatitude lat;
} SAENode_LLmD_64b;


extern const ASN1CType asn1_type_SAENode_LLmD_64b[];

typedef struct SAERegionalExtension_48 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_48;


extern const ASN1CType asn1_type_SAERegionalExtension_48[];

typedef enum {
  SAENodeOffsetPointXY_node_XY1,
  SAENodeOffsetPointXY_node_XY2,
  SAENodeOffsetPointXY_node_XY3,
  SAENodeOffsetPointXY_node_XY4,
  SAENodeOffsetPointXY_node_XY5,
  SAENodeOffsetPointXY_node_XY6,
  SAENodeOffsetPointXY_node_LatLon,
  SAENodeOffsetPointXY_regional,
} SAENodeOffsetPointXY_choice;

typedef struct SAENodeOffsetPointXY {
  SAENodeOffsetPointXY_choice choice;
  union {
    SAENode_XY_20b node_XY1;
    SAENode_XY_22b node_XY2;
    SAENode_XY_24b node_XY3;
    SAENode_XY_26b node_XY4;
    SAENode_XY_28b node_XY5;
    SAENode_XY_32b node_XY6;
    SAENode_LLmD_64b node_LatLon;
    SAERegionalExtension_48 regional;
  } u;
} SAENodeOffsetPointXY;

extern const ASN1CType asn1_type_SAENodeOffsetPointXY[];

typedef enum SAENodeAttributeXY {
  SAENodeAttributeXY_reserved,
  SAENodeAttributeXY_stopLine,
  SAENodeAttributeXY_roundedCapStyleA,
  SAENodeAttributeXY_roundedCapStyleB,
  SAENodeAttributeXY_mergePoint,
  SAENodeAttributeXY_divergePoint,
  SAENodeAttributeXY_downstreamStopLine,
  SAENodeAttributeXY_downstreamStartNode,
  SAENodeAttributeXY_closedToTraffic,
  SAENodeAttributeXY_safeIsland,
  SAENodeAttributeXY_curbPresentAtStepOff,
  SAENodeAttributeXY_hydrantPresent,
} SAENodeAttributeXY;

extern const ASN1CType asn1_type_SAENodeAttributeXY[];

typedef struct SAENodeAttributeXYList {
  SAENodeAttributeXY *tab;
  size_t count;
} SAENodeAttributeXYList;

extern const ASN1CType asn1_type_SAENodeAttributeXYList[];

typedef enum SAESegmentAttributeXY {
  SAESegmentAttributeXY_reserved,
  SAESegmentAttributeXY_doNotBlock,
  SAESegmentAttributeXY_whiteLine,
  SAESegmentAttributeXY_mergingLaneLeft,
  SAESegmentAttributeXY_mergingLaneRight,
  SAESegmentAttributeXY_curbOnLeft,
  SAESegmentAttributeXY_curbOnRight,
  SAESegmentAttributeXY_loadingzoneOnLeft,
  SAESegmentAttributeXY_loadingzoneOnRight,
  SAESegmentAttributeXY_turnOutPointOnLeft,
  SAESegmentAttributeXY_turnOutPointOnRight,
  SAESegmentAttributeXY_adjacentParkingOnLeft,
  SAESegmentAttributeXY_adjacentParkingOnRight,
  SAESegmentAttributeXY_adjacentBikeLaneOnLeft,
  SAESegmentAttributeXY_adjacentBikeLaneOnRight,
  SAESegmentAttributeXY_sharedBikeLane,
  SAESegmentAttributeXY_bikeBoxInFront,
  SAESegmentAttributeXY_transitStopOnLeft,
  SAESegmentAttributeXY_transitStopOnRight,
  SAESegmentAttributeXY_transitStopInLane,
  SAESegmentAttributeXY_sharedWithTrackedVehicle,
  SAESegmentAttributeXY_safeIsland,
  SAESegmentAttributeXY_lowCurbsPresent,
  SAESegmentAttributeXY_rumbleStripPresent,
  SAESegmentAttributeXY_audibleSignalingPresent,
  SAESegmentAttributeXY_adaptiveTimingPresent,
  SAESegmentAttributeXY_rfSignalRequestPresent,
  SAESegmentAttributeXY_partialCurbIntrusion,
  SAESegmentAttributeXY_taperToLeft,
  SAESegmentAttributeXY_taperToRight,
  SAESegmentAttributeXY_taperToCenterLine,
  SAESegmentAttributeXY_parallelParking,
  SAESegmentAttributeXY_headInParking,
  SAESegmentAttributeXY_freeParking,
  SAESegmentAttributeXY_timeRestrictionsOnParking,
  SAESegmentAttributeXY_costToPark,
  SAESegmentAttributeXY_midBlockCurbPresent,
  SAESegmentAttributeXY_unEvenPavementPresent,
} SAESegmentAttributeXY;

extern const ASN1CType asn1_type_SAESegmentAttributeXY[];

typedef struct SAESegmentAttributeXYList {
  SAESegmentAttributeXY *tab;
  size_t count;
} SAESegmentAttributeXYList;

extern const ASN1CType asn1_type_SAESegmentAttributeXYList[];

typedef int SAEDeltaAngle;

extern const ASN1CType asn1_type_SAEDeltaAngle[];

typedef int SAERoadwayCrownAngle;

extern const ASN1CType asn1_type_SAERoadwayCrownAngle[];

typedef int SAEMergeDivergeNodeAngle;

extern const ASN1CType asn1_type_SAEMergeDivergeNodeAngle[];

typedef struct SAERegionalExtension_42 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_42;


extern const ASN1CType asn1_type_SAERegionalExtension_42[];

typedef struct SAELaneDataAttribute_1 {
  SAERegionalExtension_42 *tab;
  size_t count;
} SAELaneDataAttribute_1;

extern const ASN1CType asn1_type_SAELaneDataAttribute_1[];

typedef enum {
  SAELaneDataAttribute_pathEndPointAngle,
  SAELaneDataAttribute_laneCrownPointCenter,
  SAELaneDataAttribute_laneCrownPointLeft,
  SAELaneDataAttribute_laneCrownPointRight,
  SAELaneDataAttribute_laneAngle,
  SAELaneDataAttribute_speedLimits,
  SAELaneDataAttribute_regional,
} SAELaneDataAttribute_choice;

typedef struct SAELaneDataAttribute {
  SAELaneDataAttribute_choice choice;
  union {
    SAEDeltaAngle pathEndPointAngle;
    SAERoadwayCrownAngle laneCrownPointCenter;
    SAERoadwayCrownAngle laneCrownPointLeft;
    SAERoadwayCrownAngle laneCrownPointRight;
    SAEMergeDivergeNodeAngle laneAngle;
    SAESpeedLimitList speedLimits;
    SAELaneDataAttribute_1 regional;
  } u;
} SAELaneDataAttribute;

extern const ASN1CType asn1_type_SAELaneDataAttribute[];

typedef struct SAELaneDataAttributeList {
  SAELaneDataAttribute *tab;
  size_t count;
} SAELaneDataAttributeList;

extern const ASN1CType asn1_type_SAELaneDataAttributeList[];

typedef struct SAERegionalExtension_46 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_46;


extern const ASN1CType asn1_type_SAERegionalExtension_46[];

typedef struct SAENodeAttributeSetXY_1 {
  SAERegionalExtension_46 *tab;
  size_t count;
} SAENodeAttributeSetXY_1;

extern const ASN1CType asn1_type_SAENodeAttributeSetXY_1[];

typedef struct SAENodeAttributeSetXY {
  BOOL localNode_option;
  SAENodeAttributeXYList localNode;
  BOOL disabled_option;
  SAESegmentAttributeXYList disabled;
  BOOL enabled_option;
  SAESegmentAttributeXYList enabled;
  BOOL data_option;
  SAELaneDataAttributeList data;
  BOOL dWidth_option;
  SAEOffset_B10 dWidth;
  BOOL dElevation_option;
  SAEOffset_B10 dElevation;
  BOOL regional_option;
  SAENodeAttributeSetXY_1 regional;
} SAENodeAttributeSetXY;


extern const ASN1CType asn1_type_SAENodeAttributeSetXY[];

typedef struct SAENodeXY {
  SAENodeOffsetPointXY delta;
  BOOL attributes_option;
  SAENodeAttributeSetXY attributes;
} SAENodeXY;


extern const ASN1CType asn1_type_SAENodeXY[];

typedef struct SAENodeSetXY {
  SAENodeXY *tab;
  size_t count;
} SAENodeSetXY;

extern const ASN1CType asn1_type_SAENodeSetXY[];

typedef int SAEDrivenLineOffsetSm;

extern const ASN1CType asn1_type_SAEDrivenLineOffsetSm[];

typedef int SAEDrivenLineOffsetLg;

extern const ASN1CType asn1_type_SAEDrivenLineOffsetLg[];

typedef enum {
  SAEComputedLane_1_small,
  SAEComputedLane_1_large,
} SAEComputedLane_1_choice;

typedef struct SAEComputedLane_1 {
  SAEComputedLane_1_choice choice;
  union {
    SAEDrivenLineOffsetSm small;
    SAEDrivenLineOffsetLg large;
  } u;
} SAEComputedLane_1;

extern const ASN1CType asn1_type_SAEComputedLane_1[];

typedef enum {
  SAEComputedLane_2_small,
  SAEComputedLane_2_large,
} SAEComputedLane_2_choice;

typedef struct SAEComputedLane_2 {
  SAEComputedLane_2_choice choice;
  union {
    SAEDrivenLineOffsetSm small;
    SAEDrivenLineOffsetLg large;
  } u;
} SAEComputedLane_2;

extern const ASN1CType asn1_type_SAEComputedLane_2[];

typedef int SAEAngle;

extern const ASN1CType asn1_type_SAEAngle[];

typedef int SAEScale_B12;

extern const ASN1CType asn1_type_SAEScale_B12[];

typedef struct SAERegionalExtension_33 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_33;


extern const ASN1CType asn1_type_SAERegionalExtension_33[];

typedef struct SAEComputedLane_3 {
  SAERegionalExtension_33 *tab;
  size_t count;
} SAEComputedLane_3;

extern const ASN1CType asn1_type_SAEComputedLane_3[];

typedef struct SAEComputedLane {
  SAELaneID referenceLaneId;
  SAEComputedLane_1 offsetXaxis;
  SAEComputedLane_2 offsetYaxis;
  BOOL rotateXY_option;
  SAEAngle rotateXY;
  BOOL scaleXaxis_option;
  SAEScale_B12 scaleXaxis;
  BOOL scaleYaxis_option;
  SAEScale_B12 scaleYaxis;
  BOOL regional_option;
  SAEComputedLane_3 regional;
} SAEComputedLane;


extern const ASN1CType asn1_type_SAEComputedLane[];

typedef enum {
  SAENodeListXY_nodes,
  SAENodeListXY_computed,
} SAENodeListXY_choice;

typedef struct SAENodeListXY {
  SAENodeListXY_choice choice;
  union {
    SAENodeSetXY nodes;
    SAEComputedLane computed;
  } u;
} SAENodeListXY;

extern const ASN1CType asn1_type_SAENodeListXY[];

typedef struct SAEConnectingLane {
  SAELaneID lane;
  BOOL maneuver_option;
  SAEAllowedManeuvers maneuver;
} SAEConnectingLane;


extern const ASN1CType asn1_type_SAEConnectingLane[];

typedef int SAESignalGroupID;

extern const ASN1CType asn1_type_SAESignalGroupID[];

typedef int SAERestrictionClassID;

extern const ASN1CType asn1_type_SAERestrictionClassID[];

typedef int SAELaneConnectionID;

extern const ASN1CType asn1_type_SAELaneConnectionID[];

typedef struct SAEConnection {
  SAEConnectingLane connectingLane;
  BOOL remoteIntersection_option;
  SAEIntersectionReferenceID remoteIntersection;
  BOOL signalGroup_option;
  SAESignalGroupID signalGroup;
  BOOL userClass_option;
  SAERestrictionClassID userClass;
  BOOL connectionID_option;
  SAELaneConnectionID connectionID;
} SAEConnection;


extern const ASN1CType asn1_type_SAEConnection[];

typedef struct SAEConnectsToList {
  SAEConnection *tab;
  size_t count;
} SAEConnectsToList;

extern const ASN1CType asn1_type_SAEConnectsToList[];

typedef struct SAEOverlayLaneList {
  SAELaneID *tab;
  size_t count;
} SAEOverlayLaneList;

extern const ASN1CType asn1_type_SAEOverlayLaneList[];

typedef struct SAERegionalExtension_36 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_36;


extern const ASN1CType asn1_type_SAERegionalExtension_36[];

typedef struct SAEGenericLane_1 {
  SAERegionalExtension_36 *tab;
  size_t count;
} SAEGenericLane_1;

extern const ASN1CType asn1_type_SAEGenericLane_1[];

typedef struct SAEGenericLane {
  SAELaneID laneID;
  BOOL name_option;
  SAEDescriptiveName name;
  BOOL ingressApproach_option;
  SAEApproachID ingressApproach;
  BOOL egressApproach_option;
  SAEApproachID egressApproach;
  SAELaneAttributes laneAttributes;
  BOOL maneuvers_option;
  SAEAllowedManeuvers maneuvers;
  SAENodeListXY nodeList;
  BOOL connectsTo_option;
  SAEConnectsToList connectsTo;
  BOOL overlays_option;
  SAEOverlayLaneList overlays;
  BOOL regional_option;
  SAEGenericLane_1 regional;
} SAEGenericLane;


extern const ASN1CType asn1_type_SAEGenericLane[];

typedef struct SAELaneList {
  SAEGenericLane *tab;
  size_t count;
} SAELaneList;

extern const ASN1CType asn1_type_SAELaneList[];

typedef struct SAERegionalExtension_50 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_50;


extern const ASN1CType asn1_type_SAERegionalExtension_50[];

typedef struct SAESignalControlZone {
  SAERegionalExtension_50 zone;
} SAESignalControlZone;


extern const ASN1CType asn1_type_SAESignalControlZone[];

typedef struct SAEPreemptPriorityList {
  SAESignalControlZone *tab;
  size_t count;
} SAEPreemptPriorityList;

extern const ASN1CType asn1_type_SAEPreemptPriorityList[];

typedef struct SAERegionalExtension_39 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_39;


extern const ASN1CType asn1_type_SAERegionalExtension_39[];

typedef struct SAEIntersectionGeometry_1 {
  SAERegionalExtension_39 *tab;
  size_t count;
} SAEIntersectionGeometry_1;

extern const ASN1CType asn1_type_SAEIntersectionGeometry_1[];

typedef struct SAEIntersectionGeometry {
  BOOL name_option;
  SAEDescriptiveName name;
  SAEIntersectionReferenceID id;
  SAEMsgCount revision;
  SAEPosition3D refPoint;
  BOOL laneWidth_option;
  SAELaneWidth laneWidth;
  BOOL speedLimits_option;
  SAESpeedLimitList speedLimits;
  SAELaneList laneSet;
  BOOL preemptPriorityData_option;
  SAEPreemptPriorityList preemptPriorityData;
  BOOL regional_option;
  SAEIntersectionGeometry_1 regional;
} SAEIntersectionGeometry;


extern const ASN1CType asn1_type_SAEIntersectionGeometry[];

typedef struct SAEIntersectionGeometryList {
  SAEIntersectionGeometry *tab;
  size_t count;
} SAEIntersectionGeometryList;

extern const ASN1CType asn1_type_SAEIntersectionGeometryList[];

typedef int SAERoadSegmentID;

extern const ASN1CType asn1_type_SAERoadSegmentID[];

typedef struct SAERoadSegmentReferenceID {
  BOOL region_option;
  SAERoadRegulatorID region;
  SAERoadSegmentID id;
} SAERoadSegmentReferenceID;


extern const ASN1CType asn1_type_SAERoadSegmentReferenceID[];

typedef struct SAERoadLaneSetList {
  SAEGenericLane *tab;
  size_t count;
} SAERoadLaneSetList;

extern const ASN1CType asn1_type_SAERoadLaneSetList[];

typedef struct SAERegionalExtension_54 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_54;


extern const ASN1CType asn1_type_SAERegionalExtension_54[];

typedef struct SAERoadSegment_1 {
  SAERegionalExtension_54 *tab;
  size_t count;
} SAERoadSegment_1;

extern const ASN1CType asn1_type_SAERoadSegment_1[];

typedef struct SAERoadSegment {
  BOOL name_option;
  SAEDescriptiveName name;
  SAERoadSegmentReferenceID id;
  SAEMsgCount revision;
  SAEPosition3D refPoint;
  BOOL laneWidth_option;
  SAELaneWidth laneWidth;
  BOOL speedLimits_option;
  SAESpeedLimitList speedLimits;
  SAERoadLaneSetList roadLaneSet;
  BOOL regional_option;
  SAERoadSegment_1 regional;
} SAERoadSegment;


extern const ASN1CType asn1_type_SAERoadSegment[];

typedef struct SAERoadSegmentList {
  SAERoadSegment *tab;
  size_t count;
} SAERoadSegmentList;

extern const ASN1CType asn1_type_SAERoadSegmentList[];

typedef struct SAEDataParameters {
  BOOL processMethod_option;
  ASN1String processMethod;
  BOOL processAgency_option;
  ASN1String processAgency;
  BOOL lastCheckedDate_option;
  ASN1String lastCheckedDate;
  BOOL geoidUsed_option;
  ASN1String geoidUsed;
} SAEDataParameters;


extern const ASN1CType asn1_type_SAEDataParameters[];

typedef enum SAERestrictionAppliesTo {
  SAERestrictionAppliesTo_none,
  SAERestrictionAppliesTo_equippedTransit,
  SAERestrictionAppliesTo_equippedTaxis,
  SAERestrictionAppliesTo_equippedOther,
  SAERestrictionAppliesTo_emissionCompliant,
  SAERestrictionAppliesTo_equippedBicycle,
  SAERestrictionAppliesTo_weightCompliant,
  SAERestrictionAppliesTo_heightCompliant,
  SAERestrictionAppliesTo_pedestrians,
  SAERestrictionAppliesTo_slowMovingPersons,
  SAERestrictionAppliesTo_wheelchairUsers,
  SAERestrictionAppliesTo_visualDisabilities,
  SAERestrictionAppliesTo_audioDisabilities,
  SAERestrictionAppliesTo_otherUnknownDisabilities,
} SAERestrictionAppliesTo;

extern const ASN1CType asn1_type_SAERestrictionAppliesTo[];

typedef struct SAERegionalExtension_53 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_53;


extern const ASN1CType asn1_type_SAERegionalExtension_53[];

typedef struct SAERestrictionUserType_1 {
  SAERegionalExtension_53 *tab;
  size_t count;
} SAERestrictionUserType_1;

extern const ASN1CType asn1_type_SAERestrictionUserType_1[];

typedef enum {
  SAERestrictionUserType_basicType,
  SAERestrictionUserType_regional,
} SAERestrictionUserType_choice;

typedef struct SAERestrictionUserType {
  SAERestrictionUserType_choice choice;
  union {
    SAERestrictionAppliesTo basicType;
    SAERestrictionUserType_1 regional;
  } u;
} SAERestrictionUserType;

extern const ASN1CType asn1_type_SAERestrictionUserType[];

typedef struct SAERestrictionUserTypeList {
  SAERestrictionUserType *tab;
  size_t count;
} SAERestrictionUserTypeList;

extern const ASN1CType asn1_type_SAERestrictionUserTypeList[];

typedef struct SAERestrictionClassAssignment {
  SAERestrictionClassID id;
  SAERestrictionUserTypeList users;
} SAERestrictionClassAssignment;


extern const ASN1CType asn1_type_SAERestrictionClassAssignment[];

typedef struct SAERestrictionClassList {
  SAERestrictionClassAssignment *tab;
  size_t count;
} SAERestrictionClassList;

extern const ASN1CType asn1_type_SAERestrictionClassList[];

typedef struct SAERegionalExtension_5 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_5;


extern const ASN1CType asn1_type_SAERegionalExtension_5[];

typedef struct SAEMapData_1 {
  SAERegionalExtension_5 *tab;
  size_t count;
} SAEMapData_1;

extern const ASN1CType asn1_type_SAEMapData_1[];

typedef struct SAEMapData {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  SAEMsgCount msgIssueRevision;
  BOOL layerType_option;
  SAELayerType layerType;
  BOOL layerID_option;
  SAELayerID layerID;
  BOOL intersections_option;
  SAEIntersectionGeometryList intersections;
  BOOL roadSegments_option;
  SAERoadSegmentList roadSegments;
  BOOL dataParameters_option;
  SAEDataParameters dataParameters;
  BOOL restrictionList_option;
  SAERestrictionClassList restrictionList;
  BOOL regional_option;
  SAEMapData_1 regional;
} SAEMapData;


extern const ASN1CType asn1_type_SAEMapData[];

typedef ASN1BitString SAEIntersectionStatusObject;

extern const ASN1CType asn1_type_SAEIntersectionStatusObject[];

typedef struct SAEEnabledLaneList {
  SAELaneID *tab;
  size_t count;
} SAEEnabledLaneList;

extern const ASN1CType asn1_type_SAEEnabledLaneList[];

typedef enum SAEMovementPhaseState {
  SAEMovementPhaseState_unavailable,
  SAEMovementPhaseState_dark,
  SAEMovementPhaseState_stop_Then_Proceed,
  SAEMovementPhaseState_stop_And_Remain,
  SAEMovementPhaseState_pre_Movement,
  SAEMovementPhaseState_permissive_Movement_Allowed,
  SAEMovementPhaseState_protected_Movement_Allowed,
  SAEMovementPhaseState_permissive_clearance,
  SAEMovementPhaseState_protected_clearance,
  SAEMovementPhaseState_caution_Conflicting_Traffic,
} SAEMovementPhaseState;

extern const ASN1CType asn1_type_SAEMovementPhaseState[];

typedef int SAETimeMark;

extern const ASN1CType asn1_type_SAETimeMark[];

typedef int SAETimeIntervalConfidence;

extern const ASN1CType asn1_type_SAETimeIntervalConfidence[];

typedef struct SAETimeChangeDetails {
  BOOL startTime_option;
  SAETimeMark startTime;
  SAETimeMark minEndTime;
  BOOL maxEndTime_option;
  SAETimeMark maxEndTime;
  BOOL likelyTime_option;
  SAETimeMark likelyTime;
  BOOL confidence_option;
  SAETimeIntervalConfidence confidence;
  BOOL nextTime_option;
  SAETimeMark nextTime;
} SAETimeChangeDetails;


extern const ASN1CType asn1_type_SAETimeChangeDetails[];

typedef enum SAEAdvisorySpeedType {
  SAEAdvisorySpeedType_none,
  SAEAdvisorySpeedType_greenwave,
  SAEAdvisorySpeedType_ecoDrive,
  SAEAdvisorySpeedType_transit,
} SAEAdvisorySpeedType;

extern const ASN1CType asn1_type_SAEAdvisorySpeedType[];

typedef int SAESpeedAdvice;

extern const ASN1CType asn1_type_SAESpeedAdvice[];

typedef enum SAESpeedConfidence {
  SAESpeedConfidence_unavailable,
  SAESpeedConfidence_prec100ms,
  SAESpeedConfidence_prec10ms,
  SAESpeedConfidence_prec5ms,
  SAESpeedConfidence_prec1ms,
  SAESpeedConfidence_prec0_1ms,
  SAESpeedConfidence_prec0_05ms,
  SAESpeedConfidence_prec0_01ms,
} SAESpeedConfidence;

extern const ASN1CType asn1_type_SAESpeedConfidence[];

typedef int SAEZoneLength;

extern const ASN1CType asn1_type_SAEZoneLength[];

typedef struct SAERegionalExtension_32 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_32;


extern const ASN1CType asn1_type_SAERegionalExtension_32[];

typedef struct SAEAdvisorySpeed_1 {
  SAERegionalExtension_32 *tab;
  size_t count;
} SAEAdvisorySpeed_1;

extern const ASN1CType asn1_type_SAEAdvisorySpeed_1[];

typedef struct SAEAdvisorySpeed {
  SAEAdvisorySpeedType type;
  BOOL speed_option;
  SAESpeedAdvice speed;
  BOOL confidence_option;
  SAESpeedConfidence confidence;
  BOOL distance_option;
  SAEZoneLength distance;
  BOOL Class_option;
  SAERestrictionClassID Class;
  BOOL regional_option;
  SAEAdvisorySpeed_1 regional;
} SAEAdvisorySpeed;


extern const ASN1CType asn1_type_SAEAdvisorySpeed[];

typedef struct SAEAdvisorySpeedList {
  SAEAdvisorySpeed *tab;
  size_t count;
} SAEAdvisorySpeedList;

extern const ASN1CType asn1_type_SAEAdvisorySpeedList[];

typedef struct SAERegionalExtension_43 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_43;


extern const ASN1CType asn1_type_SAERegionalExtension_43[];

typedef struct SAEMovementEvent_1 {
  SAERegionalExtension_43 *tab;
  size_t count;
} SAEMovementEvent_1;

extern const ASN1CType asn1_type_SAEMovementEvent_1[];

typedef struct SAEMovementEvent {
  SAEMovementPhaseState eventState;
  BOOL timing_option;
  SAETimeChangeDetails timing;
  BOOL speeds_option;
  SAEAdvisorySpeedList speeds;
  BOOL regional_option;
  SAEMovementEvent_1 regional;
} SAEMovementEvent;


extern const ASN1CType asn1_type_SAEMovementEvent[];

typedef struct SAEMovementEventList {
  SAEMovementEvent *tab;
  size_t count;
} SAEMovementEventList;

extern const ASN1CType asn1_type_SAEMovementEventList[];

typedef BOOL SAEWaitOnStopline;

extern const ASN1CType asn1_type_SAEWaitOnStopline[];

typedef BOOL SAEPedestrianBicycleDetect;

extern const ASN1CType asn1_type_SAEPedestrianBicycleDetect[];

typedef struct SAERegionalExtension_34 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_34;


extern const ASN1CType asn1_type_SAERegionalExtension_34[];

typedef struct SAEConnectionManeuverAssist_1 {
  SAERegionalExtension_34 *tab;
  size_t count;
} SAEConnectionManeuverAssist_1;

extern const ASN1CType asn1_type_SAEConnectionManeuverAssist_1[];

typedef struct SAEConnectionManeuverAssist {
  SAELaneConnectionID connectionID;
  BOOL queueLength_option;
  SAEZoneLength queueLength;
  BOOL availableStorageLength_option;
  SAEZoneLength availableStorageLength;
  BOOL waitOnStop_option;
  SAEWaitOnStopline waitOnStop;
  BOOL pedBicycleDetect_option;
  SAEPedestrianBicycleDetect pedBicycleDetect;
  BOOL regional_option;
  SAEConnectionManeuverAssist_1 regional;
} SAEConnectionManeuverAssist;


extern const ASN1CType asn1_type_SAEConnectionManeuverAssist[];

typedef struct SAEManeuverAssistList {
  SAEConnectionManeuverAssist *tab;
  size_t count;
} SAEManeuverAssistList;

extern const ASN1CType asn1_type_SAEManeuverAssistList[];

typedef struct SAERegionalExtension_44 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_44;


extern const ASN1CType asn1_type_SAERegionalExtension_44[];

typedef struct SAEMovementState_1 {
  SAERegionalExtension_44 *tab;
  size_t count;
} SAEMovementState_1;

extern const ASN1CType asn1_type_SAEMovementState_1[];

typedef struct SAEMovementState {
  BOOL movementName_option;
  SAEDescriptiveName movementName;
  SAESignalGroupID signalGroup;
  SAEMovementEventList state_time_speed;
  BOOL maneuverAssistList_option;
  SAEManeuverAssistList maneuverAssistList;
  BOOL regional_option;
  SAEMovementState_1 regional;
} SAEMovementState;


extern const ASN1CType asn1_type_SAEMovementState[];

typedef struct SAEMovementList {
  SAEMovementState *tab;
  size_t count;
} SAEMovementList;

extern const ASN1CType asn1_type_SAEMovementList[];

typedef struct SAERegionalExtension_40 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_40;


extern const ASN1CType asn1_type_SAERegionalExtension_40[];

typedef struct SAEIntersectionState_1 {
  SAERegionalExtension_40 *tab;
  size_t count;
} SAEIntersectionState_1;

extern const ASN1CType asn1_type_SAEIntersectionState_1[];

typedef struct SAEIntersectionState {
  BOOL name_option;
  SAEDescriptiveName name;
  SAEIntersectionReferenceID id;
  SAEMsgCount revision;
  SAEIntersectionStatusObject status;
  BOOL moy_option;
  SAEMinuteOfTheYear moy;
  BOOL timeStamp_option;
  SAEDSecond timeStamp;
  BOOL enabledLanes_option;
  SAEEnabledLaneList enabledLanes;
  SAEMovementList states;
  BOOL maneuverAssistList_option;
  SAEManeuverAssistList maneuverAssistList;
  BOOL regional_option;
  SAEIntersectionState_1 regional;
} SAEIntersectionState;


extern const ASN1CType asn1_type_SAEIntersectionState[];

typedef struct SAEIntersectionStateList {
  SAEIntersectionState *tab;
  size_t count;
} SAEIntersectionStateList;

extern const ASN1CType asn1_type_SAEIntersectionStateList[];

typedef struct SAERegionalExtension_12 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_12;


extern const ASN1CType asn1_type_SAERegionalExtension_12[];

typedef struct SAESPAT_1 {
  SAERegionalExtension_12 *tab;
  size_t count;
} SAESPAT_1;

extern const ASN1CType asn1_type_SAESPAT_1[];

typedef struct SAESPAT {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL name_option;
  SAEDescriptiveName name;
  SAEIntersectionStateList intersections;
  BOOL regional_option;
  SAESPAT_1 regional;
} SAESPAT;


extern const ASN1CType asn1_type_SAESPAT[];

typedef enum SAERequestedItem {
  SAERequestedItem_reserved,
  SAERequestedItem_itemA,
  SAERequestedItem_itemB,
  SAERequestedItem_itemC,
  SAERequestedItem_itemD,
  SAERequestedItem_itemE,
  SAERequestedItem_itemF,
  SAERequestedItem_itemG,
  SAERequestedItem_itemI,
  SAERequestedItem_itemJ,
  SAERequestedItem_itemK,
  SAERequestedItem_itemL,
  SAERequestedItem_itemM,
  SAERequestedItem_itemN,
  SAERequestedItem_itemO,
  SAERequestedItem_itemP,
  SAERequestedItem_itemQ,
} SAERequestedItem;

extern const ASN1CType asn1_type_SAERequestedItem[];

typedef struct SAERequestedItemList {
  SAERequestedItem *tab;
  size_t count;
} SAERequestedItemList;

extern const ASN1CType asn1_type_SAERequestedItemList[];

typedef struct SAERegionalExtension_2 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_2;


extern const ASN1CType asn1_type_SAERegionalExtension_2[];

typedef struct SAECommonSafetyRequest_1 {
  SAERegionalExtension_2 *tab;
  size_t count;
} SAECommonSafetyRequest_1;

extern const ASN1CType asn1_type_SAECommonSafetyRequest_1[];

typedef struct SAECommonSafetyRequest {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL msgCnt_option;
  SAEMsgCount msgCnt;
  BOOL id_option;
  SAETemporaryID id;
  SAERequestedItemList requests;
  BOOL regional_option;
  SAECommonSafetyRequest_1 regional;
} SAECommonSafetyRequest;


extern const ASN1CType asn1_type_SAECommonSafetyRequest[];

typedef int SAEITIScodes;

extern const ASN1CType asn1_type_SAEITIScodes[];

typedef struct SAERoadSideAlert_1 {
  SAEITIScodes *tab;
  size_t count;
} SAERoadSideAlert_1;

extern const ASN1CType asn1_type_SAERoadSideAlert_1[];

typedef ASN1String SAEPriority;

extern const ASN1CType asn1_type_SAEPriority[];

typedef ASN1BitString SAEHeadingSlice;

extern const ASN1CType asn1_type_SAEHeadingSlice[];

typedef enum SAEExtent {
  SAEExtent_useInstantlyOnly,
  SAEExtent_useFor3meters,
  SAEExtent_useFor10meters,
  SAEExtent_useFor50meters,
  SAEExtent_useFor100meters,
  SAEExtent_useFor500meters,
  SAEExtent_useFor1000meters,
  SAEExtent_useFor5000meters,
  SAEExtent_useFor10000meters,
  SAEExtent_useFor50000meters,
  SAEExtent_useFor100000meters,
  SAEExtent_useFor500000meters,
  SAEExtent_useFor1000000meters,
  SAEExtent_useFor5000000meters,
  SAEExtent_useFor10000000meters,
  SAEExtent_forever,
} SAEExtent;

extern const ASN1CType asn1_type_SAEExtent[];

typedef int SAEDYear;

extern const ASN1CType asn1_type_SAEDYear[];

typedef int SAEDMonth;

extern const ASN1CType asn1_type_SAEDMonth[];

typedef int SAEDDay;

extern const ASN1CType asn1_type_SAEDDay[];

typedef int SAEDHour;

extern const ASN1CType asn1_type_SAEDHour[];

typedef int SAEDMinute;

extern const ASN1CType asn1_type_SAEDMinute[];

typedef int SAEDOffset;

extern const ASN1CType asn1_type_SAEDOffset[];

typedef struct SAEDDateTime {
  BOOL year_option;
  SAEDYear year;
  BOOL month_option;
  SAEDMonth month;
  BOOL day_option;
  SAEDDay day;
  BOOL hour_option;
  SAEDHour hour;
  BOOL minute_option;
  SAEDMinute minute;
  BOOL second_option;
  SAEDSecond second;
  BOOL offset_option;
  SAEDOffset offset;
} SAEDDateTime;


extern const ASN1CType asn1_type_SAEDDateTime[];

typedef struct SAETransmissionAndSpeed {
  SAETransmissionState transmisson;
  SAEVelocity speed;
} SAETransmissionAndSpeed;


extern const ASN1CType asn1_type_SAETransmissionAndSpeed[];

typedef enum SAETimeConfidence {
  SAETimeConfidence_unavailable,
  SAETimeConfidence_time_100_000,
  SAETimeConfidence_time_050_000,
  SAETimeConfidence_time_020_000,
  SAETimeConfidence_time_010_000,
  SAETimeConfidence_time_002_000,
  SAETimeConfidence_time_001_000,
  SAETimeConfidence_time_000_500,
  SAETimeConfidence_time_000_200,
  SAETimeConfidence_time_000_100,
  SAETimeConfidence_time_000_050,
  SAETimeConfidence_time_000_020,
  SAETimeConfidence_time_000_010,
  SAETimeConfidence_time_000_005,
  SAETimeConfidence_time_000_002,
  SAETimeConfidence_time_000_001,
  SAETimeConfidence_time_000_000_5,
  SAETimeConfidence_time_000_000_2,
  SAETimeConfidence_time_000_000_1,
  SAETimeConfidence_time_000_000_05,
  SAETimeConfidence_time_000_000_02,
  SAETimeConfidence_time_000_000_01,
  SAETimeConfidence_time_000_000_005,
  SAETimeConfidence_time_000_000_002,
  SAETimeConfidence_time_000_000_001,
  SAETimeConfidence_time_000_000_000_5,
  SAETimeConfidence_time_000_000_000_2,
  SAETimeConfidence_time_000_000_000_1,
  SAETimeConfidence_time_000_000_000_05,
  SAETimeConfidence_time_000_000_000_02,
  SAETimeConfidence_time_000_000_000_01,
  SAETimeConfidence_time_000_000_000_005,
  SAETimeConfidence_time_000_000_000_002,
  SAETimeConfidence_time_000_000_000_001,
  SAETimeConfidence_time_000_000_000_000_5,
  SAETimeConfidence_time_000_000_000_000_2,
  SAETimeConfidence_time_000_000_000_000_1,
  SAETimeConfidence_time_000_000_000_000_05,
  SAETimeConfidence_time_000_000_000_000_02,
  SAETimeConfidence_time_000_000_000_000_01,
} SAETimeConfidence;

extern const ASN1CType asn1_type_SAETimeConfidence[];

typedef enum SAEPositionConfidence {
  SAEPositionConfidence_unavailable,
  SAEPositionConfidence_a500m,
  SAEPositionConfidence_a200m,
  SAEPositionConfidence_a100m,
  SAEPositionConfidence_a50m,
  SAEPositionConfidence_a20m,
  SAEPositionConfidence_a10m,
  SAEPositionConfidence_a5m,
  SAEPositionConfidence_a2m,
  SAEPositionConfidence_a1m,
  SAEPositionConfidence_a50cm,
  SAEPositionConfidence_a20cm,
  SAEPositionConfidence_a10cm,
  SAEPositionConfidence_a5cm,
  SAEPositionConfidence_a2cm,
  SAEPositionConfidence_a1cm,
} SAEPositionConfidence;

extern const ASN1CType asn1_type_SAEPositionConfidence[];

typedef enum SAEElevationConfidence {
  SAEElevationConfidence_unavailable,
  SAEElevationConfidence_elev_500_00,
  SAEElevationConfidence_elev_200_00,
  SAEElevationConfidence_elev_100_00,
  SAEElevationConfidence_elev_050_00,
  SAEElevationConfidence_elev_020_00,
  SAEElevationConfidence_elev_010_00,
  SAEElevationConfidence_elev_005_00,
  SAEElevationConfidence_elev_002_00,
  SAEElevationConfidence_elev_001_00,
  SAEElevationConfidence_elev_000_50,
  SAEElevationConfidence_elev_000_20,
  SAEElevationConfidence_elev_000_10,
  SAEElevationConfidence_elev_000_05,
  SAEElevationConfidence_elev_000_02,
  SAEElevationConfidence_elev_000_01,
} SAEElevationConfidence;

extern const ASN1CType asn1_type_SAEElevationConfidence[];

typedef struct SAEPositionConfidenceSet {
  SAEPositionConfidence pos;
  SAEElevationConfidence elevation;
} SAEPositionConfidenceSet;


extern const ASN1CType asn1_type_SAEPositionConfidenceSet[];

typedef enum SAEHeadingConfidence {
  SAEHeadingConfidence_unavailable,
  SAEHeadingConfidence_prec10deg,
  SAEHeadingConfidence_prec05deg,
  SAEHeadingConfidence_prec01deg,
  SAEHeadingConfidence_prec0_1deg,
  SAEHeadingConfidence_prec0_05deg,
  SAEHeadingConfidence_prec0_01deg,
  SAEHeadingConfidence_prec0_0125deg,
} SAEHeadingConfidence;

extern const ASN1CType asn1_type_SAEHeadingConfidence[];

typedef enum SAEThrottleConfidence {
  SAEThrottleConfidence_unavailable,
  SAEThrottleConfidence_prec10percent,
  SAEThrottleConfidence_prec1percent,
  SAEThrottleConfidence_prec0_5percent,
} SAEThrottleConfidence;

extern const ASN1CType asn1_type_SAEThrottleConfidence[];

typedef struct SAESpeedandHeadingandThrottleConfidence {
  SAEHeadingConfidence heading;
  SAESpeedConfidence speed;
  SAEThrottleConfidence throttle;
} SAESpeedandHeadingandThrottleConfidence;


extern const ASN1CType asn1_type_SAESpeedandHeadingandThrottleConfidence[];

typedef struct SAEFullPositionVector {
  BOOL utcTime_option;
  SAEDDateTime utcTime;
  SAELongitude Long;
  SAELatitude lat;
  BOOL elevation_option;
  SAEElevation elevation;
  BOOL heading_option;
  SAEHeading heading;
  BOOL speed_option;
  SAETransmissionAndSpeed speed;
  BOOL posAccuracy_option;
  SAEPositionalAccuracy posAccuracy;
  BOOL timeConfidence_option;
  SAETimeConfidence timeConfidence;
  BOOL posConfidence_option;
  SAEPositionConfidenceSet posConfidence;
  BOOL speedConfidence_option;
  SAESpeedandHeadingandThrottleConfidence speedConfidence;
} SAEFullPositionVector;


extern const ASN1CType asn1_type_SAEFullPositionVector[];

typedef ASN1String SAEFurtherInfoID;

extern const ASN1CType asn1_type_SAEFurtherInfoID[];

typedef struct SAERegionalExtension_10 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_10;


extern const ASN1CType asn1_type_SAERegionalExtension_10[];

typedef struct SAERoadSideAlert_2 {
  SAERegionalExtension_10 *tab;
  size_t count;
} SAERoadSideAlert_2;

extern const ASN1CType asn1_type_SAERoadSideAlert_2[];

typedef struct SAERoadSideAlert {
  SAEMsgCount msgCnt;
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  SAEITIScodes typeEvent;
  BOOL description_option;
  SAERoadSideAlert_1 description;
  BOOL priority_option;
  SAEPriority priority;
  BOOL heading_option;
  SAEHeadingSlice heading;
  BOOL extent_option;
  SAEExtent extent;
  BOOL position_option;
  SAEFullPositionVector position;
  BOOL furtherInfoID_option;
  SAEFurtherInfoID furtherInfoID;
  BOOL regional_option;
  SAERoadSideAlert_2 regional;
} SAERoadSideAlert;


extern const ASN1CType asn1_type_SAERoadSideAlert[];

typedef enum SAEResponseType {
  SAEResponseType_notInUseOrNotEquipped,
  SAEResponseType_emergency,
  SAEResponseType_nonEmergency,
  SAEResponseType_pursuit,
  SAEResponseType_stationary,
  SAEResponseType_slowMoving,
  SAEResponseType_stopAndGoMovement,
} SAEResponseType;

extern const ASN1CType asn1_type_SAEResponseType[];

typedef int SAESSPindex;

extern const ASN1CType asn1_type_SAESSPindex[];

typedef enum SAESirenInUse {
  SAESirenInUse_unavailable,
  SAESirenInUse_notInUse,
  SAESirenInUse_inUse,
  SAESirenInUse_reserved,
} SAESirenInUse;

extern const ASN1CType asn1_type_SAESirenInUse[];

typedef enum SAELightbarInUse {
  SAELightbarInUse_unavailable,
  SAELightbarInUse_notInUse,
  SAELightbarInUse_inUse,
  SAELightbarInUse_yellowCautionLights,
  SAELightbarInUse_schooldBusLights,
  SAELightbarInUse_arrowSignsActive,
  SAELightbarInUse_slowMovingVehicle,
  SAELightbarInUse_freqStops,
} SAELightbarInUse;

extern const ASN1CType asn1_type_SAELightbarInUse[];

typedef enum SAEMultiVehicleResponse {
  SAEMultiVehicleResponse_unavailable,
  SAEMultiVehicleResponse_singleVehicle,
  SAEMultiVehicleResponse_multiVehicle,
  SAEMultiVehicleResponse_reserved,
} SAEMultiVehicleResponse;

extern const ASN1CType asn1_type_SAEMultiVehicleResponse[];

typedef ASN1BitString SAEPrivilegedEventFlags;

extern const ASN1CType asn1_type_SAEPrivilegedEventFlags[];

typedef struct SAEPrivilegedEvents {
  SAESSPindex sspRights;
  SAEPrivilegedEventFlags event;
} SAEPrivilegedEvents;


extern const ASN1CType asn1_type_SAEPrivilegedEvents[];

typedef struct SAEEmergencyDetails {
  SAESSPindex sspRights;
  SAESirenInUse sirenUse;
  SAELightbarInUse lightsUse;
  SAEMultiVehicleResponse multi;
  BOOL events_option;
  SAEPrivilegedEvents events;
  BOOL responseType_option;
  SAEResponseType responseType;
} SAEEmergencyDetails;


extern const ASN1CType asn1_type_SAEEmergencyDetails[];

typedef int SAEVehicleMass;

extern const ASN1CType asn1_type_SAEVehicleMass[];

typedef enum SAEVehicleType {
  SAEVehicleType_none,
  SAEVehicleType_unknown,
  SAEVehicleType_special,
  SAEVehicleType_moto,
  SAEVehicleType_car,
  SAEVehicleType_carOther,
  SAEVehicleType_bus,
  SAEVehicleType_axleCnt2,
  SAEVehicleType_axleCnt3,
  SAEVehicleType_axleCnt4,
  SAEVehicleType_axleCnt4Trailer,
  SAEVehicleType_axleCnt5Trailer,
  SAEVehicleType_axleCnt6Trailer,
  SAEVehicleType_axleCnt5MultiTrailer,
  SAEVehicleType_axleCnt6MultiTrailer,
  SAEVehicleType_axleCnt7MultiTrailer,
} SAEVehicleType;

extern const ASN1CType asn1_type_SAEVehicleType[];

typedef enum SAEVehicleGroupAffected {
  SAEVehicleGroupAffected_all_vehicles,
  SAEVehicleGroupAffected_bicycles,
  SAEVehicleGroupAffected_motorcycles,
  SAEVehicleGroupAffected_cars,
  SAEVehicleGroupAffected_light_vehicles,
  SAEVehicleGroupAffected_cars_and_light_vehicles,
  SAEVehicleGroupAffected_cars_with_trailers,
  SAEVehicleGroupAffected_cars_with_recreational_trailers,
  SAEVehicleGroupAffected_vehicles_with_trailers,
  SAEVehicleGroupAffected_heavy_vehicles,
  SAEVehicleGroupAffected_trucks,
  SAEVehicleGroupAffected_buses,
  SAEVehicleGroupAffected_articulated_buses,
  SAEVehicleGroupAffected_school_buses,
  SAEVehicleGroupAffected_vehicles_with_semi_trailers,
  SAEVehicleGroupAffected_vehicles_with_double_trailers,
  SAEVehicleGroupAffected_high_profile_vehicles,
  SAEVehicleGroupAffected_wide_vehicles,
  SAEVehicleGroupAffected_long_vehicles,
  SAEVehicleGroupAffected_hazardous_loads,
  SAEVehicleGroupAffected_exceptional_loads,
  SAEVehicleGroupAffected_abnormal_loads,
  SAEVehicleGroupAffected_convoys,
  SAEVehicleGroupAffected_maintenance_vehicles,
  SAEVehicleGroupAffected_delivery_vehicles,
  SAEVehicleGroupAffected_vehicles_with_even_numbered_license_plates,
  SAEVehicleGroupAffected_vehicles_with_odd_numbered_license_plates,
  SAEVehicleGroupAffected_vehicles_with_parking_permits,
  SAEVehicleGroupAffected_vehicles_with_catalytic_converters,
  SAEVehicleGroupAffected_vehicles_without_catalytic_converters,
  SAEVehicleGroupAffected_gas_powered_vehicles,
  SAEVehicleGroupAffected_diesel_powered_vehicles,
  SAEVehicleGroupAffected_lPG_vehicles,
  SAEVehicleGroupAffected_military_convoys,
  SAEVehicleGroupAffected_military_vehicles,
} SAEVehicleGroupAffected;

extern const ASN1CType asn1_type_SAEVehicleGroupAffected[];

typedef enum SAEIncidentResponseEquipment {
  SAEIncidentResponseEquipment_ground_fire_suppression,
  SAEIncidentResponseEquipment_heavy_ground_equipment,
  SAEIncidentResponseEquipment_aircraft,
  SAEIncidentResponseEquipment_marine_equipment,
  SAEIncidentResponseEquipment_support_equipment,
  SAEIncidentResponseEquipment_medical_rescue_unit,
  SAEIncidentResponseEquipment_other,
  SAEIncidentResponseEquipment_ground_fire_suppression_other,
  SAEIncidentResponseEquipment_engine,
  SAEIncidentResponseEquipment_truck_or_aerial,
  SAEIncidentResponseEquipment_quint,
  SAEIncidentResponseEquipment_tanker_pumper_combination,
  SAEIncidentResponseEquipment_brush_truck,
  SAEIncidentResponseEquipment_aircraft_rescue_firefighting,
  SAEIncidentResponseEquipment_heavy_ground_equipment_other,
  SAEIncidentResponseEquipment_dozer_or_plow,
  SAEIncidentResponseEquipment_tractor,
  SAEIncidentResponseEquipment_tanker_or_tender,
  SAEIncidentResponseEquipment_aircraft_other,
  SAEIncidentResponseEquipment_aircraft_fixed_wing_tanker,
  SAEIncidentResponseEquipment_helitanker,
  SAEIncidentResponseEquipment_helicopter,
  SAEIncidentResponseEquipment_marine_equipment_other,
  SAEIncidentResponseEquipment_fire_boat_with_pump,
  SAEIncidentResponseEquipment_boat_no_pump,
  SAEIncidentResponseEquipment_support_apparatus_other,
  SAEIncidentResponseEquipment_breathing_apparatus_support,
  SAEIncidentResponseEquipment_light_and_air_unit,
  SAEIncidentResponseEquipment_medical_rescue_unit_other,
  SAEIncidentResponseEquipment_rescue_unit,
  SAEIncidentResponseEquipment_urban_search_rescue_unit,
  SAEIncidentResponseEquipment_high_angle_rescue,
  SAEIncidentResponseEquipment_crash_fire_rescue,
  SAEIncidentResponseEquipment_bLS_unit,
  SAEIncidentResponseEquipment_aLS_unit,
  SAEIncidentResponseEquipment_mobile_command_post,
  SAEIncidentResponseEquipment_chief_officer_car,
  SAEIncidentResponseEquipment_hAZMAT_unit,
  SAEIncidentResponseEquipment_type_i_hand_crew,
  SAEIncidentResponseEquipment_type_ii_hand_crew,
  SAEIncidentResponseEquipment_privately_owned_vehicle,
  SAEIncidentResponseEquipment_other_apparatus_resource,
  SAEIncidentResponseEquipment_ambulance,
  SAEIncidentResponseEquipment_bomb_squad_van,
  SAEIncidentResponseEquipment_combine_harvester,
  SAEIncidentResponseEquipment_construction_vehicle,
  SAEIncidentResponseEquipment_farm_tractor,
  SAEIncidentResponseEquipment_grass_cutting_machines,
  SAEIncidentResponseEquipment_hAZMAT_containment_tow,
  SAEIncidentResponseEquipment_heavy_tow,
  SAEIncidentResponseEquipment_light_tow,
  SAEIncidentResponseEquipment_flatbed_tow,
  SAEIncidentResponseEquipment_hedge_cutting_machines,
  SAEIncidentResponseEquipment_mobile_crane,
  SAEIncidentResponseEquipment_refuse_collection_vehicle,
  SAEIncidentResponseEquipment_resurfacing_vehicle,
  SAEIncidentResponseEquipment_road_sweeper,
  SAEIncidentResponseEquipment_roadside_litter_collection_crews,
  SAEIncidentResponseEquipment_salvage_vehicle,
  SAEIncidentResponseEquipment_sand_truck,
  SAEIncidentResponseEquipment_snowplow,
  SAEIncidentResponseEquipment_steam_roller,
  SAEIncidentResponseEquipment_swat_team_van,
  SAEIncidentResponseEquipment_track_laying_vehicle,
  SAEIncidentResponseEquipment_unknown_vehicle,
  SAEIncidentResponseEquipment_white_lining_vehicle,
  SAEIncidentResponseEquipment_dump_truck,
  SAEIncidentResponseEquipment_supervisor_vehicle,
  SAEIncidentResponseEquipment_snow_blower,
  SAEIncidentResponseEquipment_rotary_snow_blower,
  SAEIncidentResponseEquipment_road_grader,
  SAEIncidentResponseEquipment_steam_truck,
} SAEIncidentResponseEquipment;

extern const ASN1CType asn1_type_SAEIncidentResponseEquipment[];

typedef enum SAEResponderGroupAffected {
  SAEResponderGroupAffected_emergency_vehicle_units,
  SAEResponderGroupAffected_federal_law_enforcement_units,
  SAEResponderGroupAffected_state_police_units,
  SAEResponderGroupAffected_county_police_units,
  SAEResponderGroupAffected_local_police_units,
  SAEResponderGroupAffected_ambulance_units,
  SAEResponderGroupAffected_rescue_units,
  SAEResponderGroupAffected_fire_units,
  SAEResponderGroupAffected_hAZMAT_units,
  SAEResponderGroupAffected_light_tow_unit,
  SAEResponderGroupAffected_heavy_tow_unit,
  SAEResponderGroupAffected_freeway_service_patrols,
  SAEResponderGroupAffected_transportation_response_units,
  SAEResponderGroupAffected_private_contractor_response_units,
} SAEResponderGroupAffected;

extern const ASN1CType asn1_type_SAEResponderGroupAffected[];

typedef struct SAERegionalExtension_3 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_3;


extern const ASN1CType asn1_type_SAERegionalExtension_3[];

typedef struct SAEEmergencyVehicleAlert_1 {
  SAERegionalExtension_3 *tab;
  size_t count;
} SAEEmergencyVehicleAlert_1;

extern const ASN1CType asn1_type_SAEEmergencyVehicleAlert_1[];

typedef struct SAEEmergencyVehicleAlert {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL id_option;
  SAETemporaryID id;
  SAERoadSideAlert rsaMsg;
  BOOL responseType_option;
  SAEResponseType responseType;
  BOOL details_option;
  SAEEmergencyDetails details;
  BOOL mass_option;
  SAEVehicleMass mass;
  BOOL basicType_option;
  SAEVehicleType basicType;
  BOOL vehicleType_option;
  SAEVehicleGroupAffected vehicleType;
  BOOL responseEquip_option;
  SAEIncidentResponseEquipment responseEquip;
  BOOL responderType_option;
  SAEResponderGroupAffected responderType;
  BOOL regional_option;
  SAEEmergencyVehicleAlert_1 regional;
} SAEEmergencyVehicleAlert;


extern const ASN1CType asn1_type_SAEEmergencyVehicleAlert[];

typedef ASN1BitString SAEGNSSstatus;

extern const ASN1CType asn1_type_SAEGNSSstatus[];

typedef int SAEOffsetLL_B18;

extern const ASN1CType asn1_type_SAEOffsetLL_B18[];

typedef int SAEVertOffset_B12;

extern const ASN1CType asn1_type_SAEVertOffset_B12[];

typedef int SAETimeOffset;

extern const ASN1CType asn1_type_SAETimeOffset[];

typedef int SAECoarseHeading;

extern const ASN1CType asn1_type_SAECoarseHeading[];

typedef struct SAEPathHistoryPoint {
  SAEOffsetLL_B18 latOffset;
  SAEOffsetLL_B18 lonOffset;
  SAEVertOffset_B12 elevationOffset;
  SAETimeOffset timeOffset;
  BOOL speed_option;
  SAESpeed speed;
  BOOL posAccuracy_option;
  SAEPositionalAccuracy posAccuracy;
  BOOL heading_option;
  SAECoarseHeading heading;
} SAEPathHistoryPoint;


extern const ASN1CType asn1_type_SAEPathHistoryPoint[];

typedef struct SAEPathHistoryPointList {
  SAEPathHistoryPoint *tab;
  size_t count;
} SAEPathHistoryPointList;

extern const ASN1CType asn1_type_SAEPathHistoryPointList[];

typedef struct SAEPathHistory {
  BOOL initialPosition_option;
  SAEFullPositionVector initialPosition;
  BOOL currGNSSstatus_option;
  SAEGNSSstatus currGNSSstatus;
  SAEPathHistoryPointList crumbData;
} SAEPathHistory;


extern const ASN1CType asn1_type_SAEPathHistory[];

typedef int SAERadiusOfCurvature;

extern const ASN1CType asn1_type_SAERadiusOfCurvature[];

typedef int SAEConfidence;

extern const ASN1CType asn1_type_SAEConfidence[];

typedef struct SAEPathPrediction {
  SAERadiusOfCurvature radiusOfCurve;
  SAEConfidence confidence;
} SAEPathPrediction;


extern const ASN1CType asn1_type_SAEPathPrediction[];

typedef enum {
  SAEApproachOrLane_approach,
  SAEApproachOrLane_lane,
} SAEApproachOrLane_choice;

typedef struct SAEApproachOrLane {
  SAEApproachOrLane_choice choice;
  union {
    SAEApproachID approach;
    SAELaneID lane;
  } u;
} SAEApproachOrLane;

extern const ASN1CType asn1_type_SAEApproachOrLane[];

typedef ASN1BitString SAEVehicleEventFlags;

extern const ASN1CType asn1_type_SAEVehicleEventFlags[];

typedef struct SAERegionalExtension_4 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_4;


extern const ASN1CType asn1_type_SAERegionalExtension_4[];

typedef struct SAEIntersectionCollision_1 {
  SAERegionalExtension_4 *tab;
  size_t count;
} SAEIntersectionCollision_1;

extern const ASN1CType asn1_type_SAEIntersectionCollision_1[];

typedef struct SAEIntersectionCollision {
  SAEMsgCount msgCnt;
  SAETemporaryID id;
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL partOne_option;
  SAEBSMcoreData partOne;
  BOOL path_option;
  SAEPathHistory path;
  BOOL pathPrediction_option;
  SAEPathPrediction pathPrediction;
  SAEIntersectionReferenceID intersectionID;
  SAEApproachOrLane laneNumber;
  SAEVehicleEventFlags eventFlag;
  BOOL regional_option;
  SAEIntersectionCollision_1 regional;
} SAEIntersectionCollision;


extern const ASN1CType asn1_type_SAEIntersectionCollision[];

typedef enum SAENMEA_Revision {
  SAENMEA_Revision_unknown,
  SAENMEA_Revision_reserved,
  SAENMEA_Revision_rev1,
  SAENMEA_Revision_rev2,
  SAENMEA_Revision_rev3,
  SAENMEA_Revision_rev4,
  SAENMEA_Revision_rev5,
} SAENMEA_Revision;

extern const ASN1CType asn1_type_SAENMEA_Revision[];

typedef int SAENMEA_MsgType;

extern const ASN1CType asn1_type_SAENMEA_MsgType[];

typedef int SAEObjectCount;

extern const ASN1CType asn1_type_SAEObjectCount[];

typedef ASN1String SAENMEA_Payload;

extern const ASN1CType asn1_type_SAENMEA_Payload[];

typedef struct SAERegionalExtension_6 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_6;


extern const ASN1CType asn1_type_SAERegionalExtension_6[];

typedef struct SAENMEAcorrections_1 {
  SAERegionalExtension_6 *tab;
  size_t count;
} SAENMEAcorrections_1;

extern const ASN1CType asn1_type_SAENMEAcorrections_1[];

typedef struct SAENMEAcorrections {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL rev_option;
  SAENMEA_Revision rev;
  BOOL msg_option;
  SAENMEA_MsgType msg;
  BOOL wdCount_option;
  SAEObjectCount wdCount;
  SAENMEA_Payload payload;
  BOOL regional_option;
  SAENMEAcorrections_1 regional;
} SAENMEAcorrections;


extern const ASN1CType asn1_type_SAENMEAcorrections[];

typedef struct SAESample {
  int sampleStart;
  int sampleEnd;
} SAESample;


extern const ASN1CType asn1_type_SAESample[];

typedef int SAETermTime;

extern const ASN1CType asn1_type_SAETermTime[];

typedef int SAETermDistance;

extern const ASN1CType asn1_type_SAETermDistance[];

typedef enum {
  SAEProbeDataManagement_1_termtime,
  SAEProbeDataManagement_1_termDistance,
} SAEProbeDataManagement_1_choice;

typedef struct SAEProbeDataManagement_1 {
  SAEProbeDataManagement_1_choice choice;
  union {
    SAETermTime termtime;
    SAETermDistance termDistance;
  } u;
} SAEProbeDataManagement_1;

extern const ASN1CType asn1_type_SAEProbeDataManagement_1[];

typedef int SAEGrossSpeed;

extern const ASN1CType asn1_type_SAEGrossSpeed[];

typedef int SAESecondOfTime;

extern const ASN1CType asn1_type_SAESecondOfTime[];

typedef struct SAESnapshotTime {
  SAEGrossSpeed speed1;
  SAESecondOfTime time1;
  SAEGrossSpeed speed2;
  SAESecondOfTime time2;
} SAESnapshotTime;


extern const ASN1CType asn1_type_SAESnapshotTime[];

typedef int SAEGrossDistance;

extern const ASN1CType asn1_type_SAEGrossDistance[];

typedef struct SAESnapshotDistance {
  SAEGrossDistance distance1;
  SAEGrossSpeed speed1;
  SAEGrossDistance distance2;
  SAEGrossSpeed speed2;
} SAESnapshotDistance;


extern const ASN1CType asn1_type_SAESnapshotDistance[];

typedef enum {
  SAEProbeDataManagement_2_snapshotTime,
  SAEProbeDataManagement_2_snapshotDistance,
} SAEProbeDataManagement_2_choice;

typedef struct SAEProbeDataManagement_2 {
  SAEProbeDataManagement_2_choice choice;
  union {
    SAESnapshotTime snapshotTime;
    SAESnapshotDistance snapshotDistance;
  } u;
} SAEProbeDataManagement_2;

extern const ASN1CType asn1_type_SAEProbeDataManagement_2[];

typedef enum SAEVehicleStatusDeviceTypeTag {
  SAEVehicleStatusDeviceTypeTag_unknown,
  SAEVehicleStatusDeviceTypeTag_lights,
  SAEVehicleStatusDeviceTypeTag_wipers,
  SAEVehicleStatusDeviceTypeTag_brakes,
  SAEVehicleStatusDeviceTypeTag_stab,
  SAEVehicleStatusDeviceTypeTag_trac,
  SAEVehicleStatusDeviceTypeTag_abs,
  SAEVehicleStatusDeviceTypeTag_sunS,
  SAEVehicleStatusDeviceTypeTag_rainS,
  SAEVehicleStatusDeviceTypeTag_airTemp,
  SAEVehicleStatusDeviceTypeTag_steering,
  SAEVehicleStatusDeviceTypeTag_vertAccelThres,
  SAEVehicleStatusDeviceTypeTag_vertAccel,
  SAEVehicleStatusDeviceTypeTag_hozAccelLong,
  SAEVehicleStatusDeviceTypeTag_hozAccelLat,
  SAEVehicleStatusDeviceTypeTag_hozAccelCon,
  SAEVehicleStatusDeviceTypeTag_accel4way,
  SAEVehicleStatusDeviceTypeTag_confidenceSet,
  SAEVehicleStatusDeviceTypeTag_obDist,
  SAEVehicleStatusDeviceTypeTag_obDirect,
  SAEVehicleStatusDeviceTypeTag_yaw,
  SAEVehicleStatusDeviceTypeTag_yawRateCon,
  SAEVehicleStatusDeviceTypeTag_dateTime,
  SAEVehicleStatusDeviceTypeTag_fullPos,
  SAEVehicleStatusDeviceTypeTag_position2D,
  SAEVehicleStatusDeviceTypeTag_position3D,
  SAEVehicleStatusDeviceTypeTag_vehicle,
  SAEVehicleStatusDeviceTypeTag_speedHeadC,
  SAEVehicleStatusDeviceTypeTag_speedC,
} SAEVehicleStatusDeviceTypeTag;

extern const ASN1CType asn1_type_SAEVehicleStatusDeviceTypeTag[];

typedef struct SAEVehicleStatusRequest {
  SAEVehicleStatusDeviceTypeTag dataType;
  BOOL subType_option;
  int subType;
  BOOL sendOnLessThenValue_option;
  int sendOnLessThenValue;
  BOOL sendOnMoreThenValue_option;
  int sendOnMoreThenValue;
  BOOL sendAll_option;
  BOOL sendAll;
} SAEVehicleStatusRequest;


extern const ASN1CType asn1_type_SAEVehicleStatusRequest[];

typedef struct SAEVehicleStatusRequestList {
  SAEVehicleStatusRequest *tab;
  size_t count;
} SAEVehicleStatusRequestList;

extern const ASN1CType asn1_type_SAEVehicleStatusRequestList[];

typedef struct SAERegionalExtension_8 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_8;


extern const ASN1CType asn1_type_SAERegionalExtension_8[];

typedef struct SAEProbeDataManagement_3 {
  SAERegionalExtension_8 *tab;
  size_t count;
} SAEProbeDataManagement_3;

extern const ASN1CType asn1_type_SAEProbeDataManagement_3[];

typedef struct SAEProbeDataManagement {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  SAESample sample;
  SAEHeadingSlice directions;
  SAEProbeDataManagement_1 term;
  SAEProbeDataManagement_2 snapshot;
  SAESecondOfTime txInterval;
  BOOL dataElements_option;
  SAEVehicleStatusRequestList dataElements;
  BOOL regional_option;
  SAEProbeDataManagement_3 regional;
} SAEProbeDataManagement;


extern const ASN1CType asn1_type_SAEProbeDataManagement[];

typedef int SAEProbeSegmentNumber;

extern const ASN1CType asn1_type_SAEProbeSegmentNumber[];

typedef ASN1String SAEVINstring;

extern const ASN1CType asn1_type_SAEVINstring[];

typedef unsigned int SAEStationID;

extern const ASN1CType asn1_type_SAEStationID[];

typedef enum {
  SAEVehicleID_entityID,
  SAEVehicleID_stationID,
} SAEVehicleID_choice;

typedef struct SAEVehicleID {
  SAEVehicleID_choice choice;
  union {
    SAETemporaryID entityID;
    SAEStationID stationID;
  } u;
} SAEVehicleID;

extern const ASN1CType asn1_type_SAEVehicleID[];

typedef enum {
  SAEVehicleIdent_1_vGroup,
  SAEVehicleIdent_1_rGroup,
  SAEVehicleIdent_1_rEquip,
} SAEVehicleIdent_1_choice;

typedef struct SAEVehicleIdent_1 {
  SAEVehicleIdent_1_choice choice;
  union {
    SAEVehicleGroupAffected vGroup;
    SAEResponderGroupAffected rGroup;
    SAEIncidentResponseEquipment rEquip;
  } u;
} SAEVehicleIdent_1;

extern const ASN1CType asn1_type_SAEVehicleIdent_1[];

typedef struct SAEVehicleIdent {
  BOOL name_option;
  SAEDescriptiveName name;
  BOOL vin_option;
  SAEVINstring vin;
  BOOL ownerCode_option;
  ASN1String ownerCode;
  BOOL id_option;
  SAEVehicleID id;
  BOOL vehicleType_option;
  SAEVehicleType vehicleType;
  BOOL vehicleClass_option;
  SAEVehicleIdent_1 vehicleClass;
} SAEVehicleIdent;


extern const ASN1CType asn1_type_SAEVehicleIdent[];

typedef int SAEBasicVehicleClass;

extern const ASN1CType asn1_type_SAEBasicVehicleClass[];

typedef enum SAEBasicVehicleRole {
  SAEBasicVehicleRole_basicVehicle,
  SAEBasicVehicleRole_publicTransport,
  SAEBasicVehicleRole_specialTransport,
  SAEBasicVehicleRole_dangerousGoods,
  SAEBasicVehicleRole_roadWork,
  SAEBasicVehicleRole_roadRescue,
  SAEBasicVehicleRole_emergency,
  SAEBasicVehicleRole_safetyCar,
  SAEBasicVehicleRole_none_unknown,
  SAEBasicVehicleRole_truck,
  SAEBasicVehicleRole_motorcycle,
  SAEBasicVehicleRole_roadSideSource,
  SAEBasicVehicleRole_police,
  SAEBasicVehicleRole_fire,
  SAEBasicVehicleRole_ambulance,
  SAEBasicVehicleRole_dot,
  SAEBasicVehicleRole_transit,
  SAEBasicVehicleRole_slowMoving,
  SAEBasicVehicleRole_stopNgo,
  SAEBasicVehicleRole_cyclist,
  SAEBasicVehicleRole_pedestrian,
  SAEBasicVehicleRole_nonMotorized,
  SAEBasicVehicleRole_military,
} SAEBasicVehicleRole;

extern const ASN1CType asn1_type_SAEBasicVehicleRole[];

typedef int SAEIso3833VehicleType;

extern const ASN1CType asn1_type_SAEIso3833VehicleType[];

typedef int SAEFuelType;

extern const ASN1CType asn1_type_SAEFuelType[];

typedef struct SAERegionalExtension_60 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_60;


extern const ASN1CType asn1_type_SAERegionalExtension_60[];

typedef struct SAEVehicleClassification_1 {
  SAERegionalExtension_60 *tab;
  size_t count;
} SAEVehicleClassification_1;

extern const ASN1CType asn1_type_SAEVehicleClassification_1[];

typedef struct SAEVehicleClassification {
  BOOL keyType_option;
  SAEBasicVehicleClass keyType;
  BOOL role_option;
  SAEBasicVehicleRole role;
  BOOL iso3883_option;
  SAEIso3833VehicleType iso3883;
  BOOL hpmsType_option;
  SAEVehicleType hpmsType;
  BOOL vehicleType_option;
  SAEVehicleGroupAffected vehicleType;
  BOOL responseEquip_option;
  SAEIncidentResponseEquipment responseEquip;
  BOOL responderType_option;
  SAEResponderGroupAffected responderType;
  BOOL fuelType_option;
  SAEFuelType fuelType;
  BOOL regional_option;
  SAEVehicleClassification_1 regional;
} SAEVehicleClassification;


extern const ASN1CType asn1_type_SAEVehicleClassification[];

typedef ASN1BitString SAEExteriorLights;

extern const ASN1CType asn1_type_SAEExteriorLights[];

typedef struct SAEVehicleSafetyExtensions {
  BOOL events_option;
  SAEVehicleEventFlags events;
  BOOL pathHistory_option;
  SAEPathHistory pathHistory;
  BOOL pathPrediction_option;
  SAEPathPrediction pathPrediction;
  BOOL lights_option;
  SAEExteriorLights lights;
} SAEVehicleSafetyExtensions;


extern const ASN1CType asn1_type_SAEVehicleSafetyExtensions[];

typedef enum SAEWiperStatus {
  SAEWiperStatus_unavailable,
  SAEWiperStatus_off,
  SAEWiperStatus_intermittent,
  SAEWiperStatus_low,
  SAEWiperStatus_high,
  SAEWiperStatus_washerInUse,
  SAEWiperStatus_automaticPresent,
} SAEWiperStatus;

extern const ASN1CType asn1_type_SAEWiperStatus[];

typedef int SAEWiperRate;

extern const ASN1CType asn1_type_SAEWiperRate[];

typedef struct SAEWiperSet {
  SAEWiperStatus statusFront;
  SAEWiperRate rateFront;
  BOOL statusRear_option;
  SAEWiperStatus statusRear;
  BOOL rateRear_option;
  SAEWiperRate rateRear;
} SAEWiperSet;


extern const ASN1CType asn1_type_SAEWiperSet[];

typedef enum SAEBrakeAppliedPressure {
  SAEBrakeAppliedPressure_unavailable,
  SAEBrakeAppliedPressure_minPressure,
  SAEBrakeAppliedPressure_bkLvl_2,
  SAEBrakeAppliedPressure_bkLvl_3,
  SAEBrakeAppliedPressure_bkLvl_4,
  SAEBrakeAppliedPressure_bkLvl_5,
  SAEBrakeAppliedPressure_bkLvl_6,
  SAEBrakeAppliedPressure_bkLvl_7,
  SAEBrakeAppliedPressure_bkLvl_8,
  SAEBrakeAppliedPressure_bkLvl_9,
  SAEBrakeAppliedPressure_bkLvl_10,
  SAEBrakeAppliedPressure_bkLvl_11,
  SAEBrakeAppliedPressure_bkLvl_12,
  SAEBrakeAppliedPressure_bkLvl_13,
  SAEBrakeAppliedPressure_bkLvl_14,
  SAEBrakeAppliedPressure_maxPressure,
} SAEBrakeAppliedPressure;

extern const ASN1CType asn1_type_SAEBrakeAppliedPressure[];

typedef int SAECoefficientOfFriction;

extern const ASN1CType asn1_type_SAECoefficientOfFriction[];

typedef int SAESunSensor;

extern const ASN1CType asn1_type_SAESunSensor[];

typedef enum SAERainSensor {
  SAERainSensor_none,
  SAERainSensor_lightMist,
  SAERainSensor_heavyMist,
  SAERainSensor_lightRainOrDrizzle,
  SAERainSensor_rain,
  SAERainSensor_moderateRain,
  SAERainSensor_heavyRain,
  SAERainSensor_heavyDownpour,
} SAERainSensor;

extern const ASN1CType asn1_type_SAERainSensor[];

typedef int SAEAmbientAirTemperature;

extern const ASN1CType asn1_type_SAEAmbientAirTemperature[];

typedef int SAEAmbientAirPressure;

extern const ASN1CType asn1_type_SAEAmbientAirPressure[];

typedef enum SAESteeringWheelAngleConfidence {
  SAESteeringWheelAngleConfidence_unavailable,
  SAESteeringWheelAngleConfidence_prec2deg,
  SAESteeringWheelAngleConfidence_prec1deg,
  SAESteeringWheelAngleConfidence_prec0_02deg,
} SAESteeringWheelAngleConfidence;

extern const ASN1CType asn1_type_SAESteeringWheelAngleConfidence[];

typedef int SAESteeringWheelAngleRateOfChange;

extern const ASN1CType asn1_type_SAESteeringWheelAngleRateOfChange[];

typedef int SAEDrivingWheelAngle;

extern const ASN1CType asn1_type_SAEDrivingWheelAngle[];

typedef struct SAEVehicleStatus_1 {
  SAESteeringWheelAngle angle;
  BOOL confidence_option;
  SAESteeringWheelAngleConfidence confidence;
  BOOL rate_option;
  SAESteeringWheelAngleRateOfChange rate;
  BOOL wheels_option;
  SAEDrivingWheelAngle wheels;
} SAEVehicleStatus_1;


extern const ASN1CType asn1_type_SAEVehicleStatus_1[];

typedef ASN1BitString SAEVerticalAccelerationThreshold;

extern const ASN1CType asn1_type_SAEVerticalAccelerationThreshold[];

typedef enum SAEYawRateConfidence {
  SAEYawRateConfidence_unavailable,
  SAEYawRateConfidence_degSec_100_00,
  SAEYawRateConfidence_degSec_010_00,
  SAEYawRateConfidence_degSec_005_00,
  SAEYawRateConfidence_degSec_001_00,
  SAEYawRateConfidence_degSec_000_10,
  SAEYawRateConfidence_degSec_000_05,
  SAEYawRateConfidence_degSec_000_01,
} SAEYawRateConfidence;

extern const ASN1CType asn1_type_SAEYawRateConfidence[];

typedef enum SAEAccelerationConfidence {
  SAEAccelerationConfidence_unavailable,
  SAEAccelerationConfidence_accl_100_00,
  SAEAccelerationConfidence_accl_010_00,
  SAEAccelerationConfidence_accl_005_00,
  SAEAccelerationConfidence_accl_001_00,
  SAEAccelerationConfidence_accl_000_10,
  SAEAccelerationConfidence_accl_000_05,
  SAEAccelerationConfidence_accl_000_01,
} SAEAccelerationConfidence;

extern const ASN1CType asn1_type_SAEAccelerationConfidence[];

typedef struct SAEAccelSteerYawRateConfidence {
  SAEYawRateConfidence yawRate;
  SAEAccelerationConfidence acceleration;
  SAESteeringWheelAngleConfidence steeringWheelAngle;
} SAEAccelSteerYawRateConfidence;


extern const ASN1CType asn1_type_SAEAccelSteerYawRateConfidence[];

typedef struct SAEConfidenceSet {
  BOOL accelConfidence_option;
  SAEAccelSteerYawRateConfidence accelConfidence;
  BOOL speedConfidence_option;
  SAESpeedandHeadingandThrottleConfidence speedConfidence;
  BOOL timeConfidence_option;
  SAETimeConfidence timeConfidence;
  BOOL posConfidence_option;
  SAEPositionConfidenceSet posConfidence;
  BOOL steerConfidence_option;
  SAESteeringWheelAngleConfidence steerConfidence;
  BOOL headingConfidence_option;
  SAEHeadingConfidence headingConfidence;
  BOOL throttleConfidence_option;
  SAEThrottleConfidence throttleConfidence;
} SAEConfidenceSet;


extern const ASN1CType asn1_type_SAEConfidenceSet[];

typedef struct SAEVehicleStatus_2 {
  BOOL accel4way_option;
  SAEAccelerationSet4Way accel4way;
  BOOL vertAccelThres_option;
  SAEVerticalAccelerationThreshold vertAccelThres;
  BOOL yawRateCon_option;
  SAEYawRateConfidence yawRateCon;
  BOOL hozAccelCon_option;
  SAEAccelerationConfidence hozAccelCon;
  BOOL confidenceSet_option;
  SAEConfidenceSet confidenceSet;
} SAEVehicleStatus_2;


extern const ASN1CType asn1_type_SAEVehicleStatus_2[];

typedef int SAEObstacleDistance;

extern const ASN1CType asn1_type_SAEObstacleDistance[];

typedef struct SAEVehicleStatus_3 {
  SAEObstacleDistance obDist;
  SAEAngle obDirect;
  SAEDDateTime dateTime;
} SAEVehicleStatus_3;


extern const ASN1CType asn1_type_SAEVehicleStatus_3[];

typedef int SAEThrottlePosition;

extern const ASN1CType asn1_type_SAEThrottlePosition[];

typedef int SAEVehicleHeight;

extern const ASN1CType asn1_type_SAEVehicleHeight[];

typedef int SAEBumperHeight;

extern const ASN1CType asn1_type_SAEBumperHeight[];

typedef struct SAEBumperHeights {
  SAEBumperHeight front;
  SAEBumperHeight rear;
} SAEBumperHeights;


extern const ASN1CType asn1_type_SAEBumperHeights[];

typedef int SAETrailerWeight;

extern const ASN1CType asn1_type_SAETrailerWeight[];

typedef struct SAEVehicleStatus_4 {
  SAEVehicleHeight height;
  SAEBumperHeights bumpers;
  SAEVehicleMass mass;
  SAETrailerWeight trailerWeight;
  SAEVehicleType type;
} SAEVehicleStatus_4;


extern const ASN1CType asn1_type_SAEVehicleStatus_4[];

typedef int SAETireLocation;

extern const ASN1CType asn1_type_SAETireLocation[];

typedef int SAETirePressure;

extern const ASN1CType asn1_type_SAETirePressure[];

typedef int SAETireTemp;

extern const ASN1CType asn1_type_SAETireTemp[];

typedef enum SAEWheelSensorStatus {
  SAEWheelSensorStatus_off,
  SAEWheelSensorStatus_on,
  SAEWheelSensorStatus_notDefined,
  SAEWheelSensorStatus_notSupported,
} SAEWheelSensorStatus;

extern const ASN1CType asn1_type_SAEWheelSensorStatus[];

typedef enum SAEWheelEndElectFault {
  SAEWheelEndElectFault_isOk,
  SAEWheelEndElectFault_isNotDefined,
  SAEWheelEndElectFault_isError,
  SAEWheelEndElectFault_isNotSupported,
} SAEWheelEndElectFault;

extern const ASN1CType asn1_type_SAEWheelEndElectFault[];

typedef int SAETireLeakageRate;

extern const ASN1CType asn1_type_SAETireLeakageRate[];

typedef enum SAETirePressureThresholdDetection {
  SAETirePressureThresholdDetection_noData,
  SAETirePressureThresholdDetection_overPressure,
  SAETirePressureThresholdDetection_noWarningPressure,
  SAETirePressureThresholdDetection_underPressure,
  SAETirePressureThresholdDetection_extremeUnderPressure,
  SAETirePressureThresholdDetection_undefined,
  SAETirePressureThresholdDetection_errorIndicator,
  SAETirePressureThresholdDetection_notAvailable,
} SAETirePressureThresholdDetection;

extern const ASN1CType asn1_type_SAETirePressureThresholdDetection[];

typedef struct SAETireData {
  BOOL location_option;
  SAETireLocation location;
  BOOL pressure_option;
  SAETirePressure pressure;
  BOOL temp_option;
  SAETireTemp temp;
  BOOL wheelSensorStatus_option;
  SAEWheelSensorStatus wheelSensorStatus;
  BOOL wheelEndElectFault_option;
  SAEWheelEndElectFault wheelEndElectFault;
  BOOL leakageRate_option;
  SAETireLeakageRate leakageRate;
  BOOL detection_option;
  SAETirePressureThresholdDetection detection;
} SAETireData;


extern const ASN1CType asn1_type_SAETireData[];

typedef struct SAETireDataList {
  SAETireData *tab;
  size_t count;
} SAETireDataList;

extern const ASN1CType asn1_type_SAETireDataList[];

typedef int SAEAxleLocation;

extern const ASN1CType asn1_type_SAEAxleLocation[];

typedef int SAEAxleWeight;

extern const ASN1CType asn1_type_SAEAxleWeight[];

typedef struct SAEAxleWeightSet {
  BOOL location_option;
  SAEAxleLocation location;
  BOOL weight_option;
  SAEAxleWeight weight;
} SAEAxleWeightSet;


extern const ASN1CType asn1_type_SAEAxleWeightSet[];

typedef struct SAEAxleWeightList {
  SAEAxleWeightSet *tab;
  size_t count;
} SAEAxleWeightList;

extern const ASN1CType asn1_type_SAEAxleWeightList[];

typedef int SAECargoWeight;

extern const ASN1CType asn1_type_SAECargoWeight[];

typedef int SAESteeringAxleTemperature;

extern const ASN1CType asn1_type_SAESteeringAxleTemperature[];

typedef int SAEDriveAxleLocation;

extern const ASN1CType asn1_type_SAEDriveAxleLocation[];

typedef int SAEDriveAxleLiftAirPressure;

extern const ASN1CType asn1_type_SAEDriveAxleLiftAirPressure[];

typedef int SAEDriveAxleTemperature;

extern const ASN1CType asn1_type_SAEDriveAxleTemperature[];

typedef int SAEDriveAxleLubePressure;

extern const ASN1CType asn1_type_SAEDriveAxleLubePressure[];

typedef int SAESteeringAxleLubePressure;

extern const ASN1CType asn1_type_SAESteeringAxleLubePressure[];

typedef struct SAEJ1939data {
  BOOL tires_option;
  SAETireDataList tires;
  BOOL axles_option;
  SAEAxleWeightList axles;
  BOOL trailerWeight_option;
  SAETrailerWeight trailerWeight;
  BOOL cargoWeight_option;
  SAECargoWeight cargoWeight;
  BOOL steeringAxleTemperature_option;
  SAESteeringAxleTemperature steeringAxleTemperature;
  BOOL driveAxleLocation_option;
  SAEDriveAxleLocation driveAxleLocation;
  BOOL driveAxleLiftAirPressure_option;
  SAEDriveAxleLiftAirPressure driveAxleLiftAirPressure;
  BOOL driveAxleTemperature_option;
  SAEDriveAxleTemperature driveAxleTemperature;
  BOOL driveAxleLubePressure_option;
  SAEDriveAxleLubePressure driveAxleLubePressure;
  BOOL steeringAxleLubePressure_option;
  SAESteeringAxleLubePressure steeringAxleLubePressure;
} SAEJ1939data;


extern const ASN1CType asn1_type_SAEJ1939data[];

typedef enum SAEEssPrecipYesNo {
  SAEEssPrecipYesNo_precip,
  SAEEssPrecipYesNo_noPrecip,
  SAEEssPrecipYesNo_error,
} SAEEssPrecipYesNo;

extern const ASN1CType asn1_type_SAEEssPrecipYesNo[];

typedef int SAEEssPrecipRate;

extern const ASN1CType asn1_type_SAEEssPrecipRate[];

typedef enum SAEEssPrecipSituation {
  SAEEssPrecipSituation_other,
  SAEEssPrecipSituation_unknown,
  SAEEssPrecipSituation_noPrecipitation,
  SAEEssPrecipSituation_unidentifiedSlight,
  SAEEssPrecipSituation_unidentifiedModerate,
  SAEEssPrecipSituation_unidentifiedHeavy,
  SAEEssPrecipSituation_snowSlight,
  SAEEssPrecipSituation_snowModerate,
  SAEEssPrecipSituation_snowHeavy,
  SAEEssPrecipSituation_rainSlight,
  SAEEssPrecipSituation_rainModerate,
  SAEEssPrecipSituation_rainHeavy,
  SAEEssPrecipSituation_frozenPrecipitationSlight,
  SAEEssPrecipSituation_frozenPrecipitationModerate,
  SAEEssPrecipSituation_frozenPrecipitationHeavy,
} SAEEssPrecipSituation;

extern const ASN1CType asn1_type_SAEEssPrecipSituation[];

typedef int SAEEssSolarRadiation;

extern const ASN1CType asn1_type_SAEEssSolarRadiation[];

typedef int SAEEssMobileFriction;

extern const ASN1CType asn1_type_SAEEssMobileFriction[];

typedef struct SAEVehicleStatus_5 {
  SAEEssPrecipYesNo isRaining;
  BOOL rainRate_option;
  SAEEssPrecipRate rainRate;
  BOOL precipSituation_option;
  SAEEssPrecipSituation precipSituation;
  BOOL solarRadiation_option;
  SAEEssSolarRadiation solarRadiation;
  BOOL friction_option;
  SAEEssMobileFriction friction;
} SAEVehicleStatus_5;


extern const ASN1CType asn1_type_SAEVehicleStatus_5[];

typedef struct SAEVehicleStatus {
  BOOL lights_option;
  SAEExteriorLights lights;
  BOOL lightBar_option;
  SAELightbarInUse lightBar;
  BOOL wipers_option;
  SAEWiperSet wipers;
  BOOL brakeStatus_option;
  SAEBrakeSystemStatus brakeStatus;
  BOOL brakePressure_option;
  SAEBrakeAppliedPressure brakePressure;
  BOOL roadFriction_option;
  SAECoefficientOfFriction roadFriction;
  BOOL sunData_option;
  SAESunSensor sunData;
  BOOL rainData_option;
  SAERainSensor rainData;
  BOOL airTemp_option;
  SAEAmbientAirTemperature airTemp;
  BOOL airPres_option;
  SAEAmbientAirPressure airPres;
  BOOL steering_option;
  SAEVehicleStatus_1 steering;
  BOOL accelSets_option;
  SAEVehicleStatus_2 accelSets;
  BOOL object_option;
  SAEVehicleStatus_3 object;
  BOOL fullPos_option;
  SAEFullPositionVector fullPos;
  BOOL throttlePos_option;
  SAEThrottlePosition throttlePos;
  BOOL speedHeadC_option;
  SAESpeedandHeadingandThrottleConfidence speedHeadC;
  BOOL speedC_option;
  SAESpeedConfidence speedC;
  BOOL vehicleData_option;
  SAEVehicleStatus_4 vehicleData;
  BOOL vehicleIdent_option;
  SAEVehicleIdent vehicleIdent;
  BOOL j1939data_option;
  SAEJ1939data j1939data;
  BOOL weatherReport_option;
  SAEVehicleStatus_5 weatherReport;
  BOOL gnssStatus_option;
  SAEGNSSstatus gnssStatus;
} SAEVehicleStatus;


extern const ASN1CType asn1_type_SAEVehicleStatus[];

typedef struct SAESnapshot {
  SAEFullPositionVector thePosition;
  BOOL safetyExt_option;
  SAEVehicleSafetyExtensions safetyExt;
  BOOL dataSet_option;
  SAEVehicleStatus dataSet;
} SAESnapshot;


extern const ASN1CType asn1_type_SAESnapshot[];

typedef struct SAEProbeVehicleData_1 {
  SAESnapshot *tab;
  size_t count;
} SAEProbeVehicleData_1;

extern const ASN1CType asn1_type_SAEProbeVehicleData_1[];

typedef struct SAERegionalExtension_9 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_9;


extern const ASN1CType asn1_type_SAERegionalExtension_9[];

typedef struct SAEProbeVehicleData_2 {
  SAERegionalExtension_9 *tab;
  size_t count;
} SAEProbeVehicleData_2;

extern const ASN1CType asn1_type_SAEProbeVehicleData_2[];

typedef struct SAEProbeVehicleData {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL segNum_option;
  SAEProbeSegmentNumber segNum;
  BOOL probeID_option;
  SAEVehicleIdent probeID;
  SAEFullPositionVector startVector;
  SAEVehicleClassification vehicleType;
  SAEProbeVehicleData_1 snapshots;
  BOOL regional_option;
  SAEProbeVehicleData_2 regional;
} SAEProbeVehicleData;


extern const ASN1CType asn1_type_SAEProbeVehicleData[];

typedef enum SAERTCM_Revision {
  SAERTCM_Revision_unknown,
  SAERTCM_Revision_rtcmRev2,
  SAERTCM_Revision_rtcmRev3,
  SAERTCM_Revision_reserved,
} SAERTCM_Revision;

extern const ASN1CType asn1_type_SAERTCM_Revision[];

typedef int SAEOffset_B09;

extern const ASN1CType asn1_type_SAEOffset_B09[];

typedef struct SAEAntennaOffsetSet {
  SAEOffset_B12 antOffsetX;
  SAEOffset_B09 antOffsetY;
  SAEOffset_B10 antOffsetZ;
} SAEAntennaOffsetSet;


extern const ASN1CType asn1_type_SAEAntennaOffsetSet[];

typedef struct SAERTCMheader {
  SAEGNSSstatus status;
  SAEAntennaOffsetSet offsetSet;
} SAERTCMheader;


extern const ASN1CType asn1_type_SAERTCMheader[];

typedef ASN1String SAERTCMmessage;

extern const ASN1CType asn1_type_SAERTCMmessage[];

typedef struct SAERTCMmessageList {
  SAERTCMmessage *tab;
  size_t count;
} SAERTCMmessageList;

extern const ASN1CType asn1_type_SAERTCMmessageList[];

typedef struct SAERegionalExtension_11 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_11;


extern const ASN1CType asn1_type_SAERegionalExtension_11[];

typedef struct SAERTCMcorrections_1 {
  SAERegionalExtension_11 *tab;
  size_t count;
} SAERTCMcorrections_1;

extern const ASN1CType asn1_type_SAERTCMcorrections_1[];

typedef struct SAERTCMcorrections {
  SAEMsgCount msgCnt;
  SAERTCM_Revision rev;
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL anchorPoint_option;
  SAEFullPositionVector anchorPoint;
  BOOL rtcmHeader_option;
  SAERTCMheader rtcmHeader;
  SAERTCMmessageList msgs;
  BOOL regional_option;
  SAERTCMcorrections_1 regional;
} SAERTCMcorrections;


extern const ASN1CType asn1_type_SAERTCMcorrections[];

typedef int SAERequestID;

extern const ASN1CType asn1_type_SAERequestID[];

typedef enum SAEPriorityRequestType {
  SAEPriorityRequestType_priorityRequestTypeReserved,
  SAEPriorityRequestType_priorityRequest,
  SAEPriorityRequestType_priorityRequestUpdate,
  SAEPriorityRequestType_priorityCancellation,
} SAEPriorityRequestType;

extern const ASN1CType asn1_type_SAEPriorityRequestType[];

typedef enum {
  SAEIntersectionAccessPoint_lane,
  SAEIntersectionAccessPoint_approach,
  SAEIntersectionAccessPoint_connection,
} SAEIntersectionAccessPoint_choice;

typedef struct SAEIntersectionAccessPoint {
  SAEIntersectionAccessPoint_choice choice;
  union {
    SAELaneID lane;
    SAEApproachID approach;
    SAELaneConnectionID connection;
  } u;
} SAEIntersectionAccessPoint;

extern const ASN1CType asn1_type_SAEIntersectionAccessPoint[];

typedef struct SAERegionalExtension_56 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_56;


extern const ASN1CType asn1_type_SAERegionalExtension_56[];

typedef struct SAESignalRequest_1 {
  SAERegionalExtension_56 *tab;
  size_t count;
} SAESignalRequest_1;

extern const ASN1CType asn1_type_SAESignalRequest_1[];

typedef struct SAESignalRequest {
  SAEIntersectionReferenceID id;
  SAERequestID requestID;
  SAEPriorityRequestType requestType;
  SAEIntersectionAccessPoint inBoundLane;
  BOOL outBoundLane_option;
  SAEIntersectionAccessPoint outBoundLane;
  BOOL regional_option;
  SAESignalRequest_1 regional;
} SAESignalRequest;


extern const ASN1CType asn1_type_SAESignalRequest[];

typedef struct SAERegionalExtension_55 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_55;


extern const ASN1CType asn1_type_SAERegionalExtension_55[];

typedef struct SAESignalRequestPackage_1 {
  SAERegionalExtension_55 *tab;
  size_t count;
} SAESignalRequestPackage_1;

extern const ASN1CType asn1_type_SAESignalRequestPackage_1[];

typedef struct SAESignalRequestPackage {
  SAESignalRequest request;
  BOOL minute_option;
  SAEMinuteOfTheYear minute;
  BOOL second_option;
  SAEDSecond second;
  BOOL duration_option;
  SAEDSecond duration;
  BOOL regional_option;
  SAESignalRequestPackage_1 regional;
} SAESignalRequestPackage;


extern const ASN1CType asn1_type_SAESignalRequestPackage[];

typedef struct SAESignalRequestList {
  SAESignalRequestPackage *tab;
  size_t count;
} SAESignalRequestList;

extern const ASN1CType asn1_type_SAESignalRequestList[];

typedef enum SAERequestSubRole {
  SAERequestSubRole_requestSubRoleUnKnown,
  SAERequestSubRole_requestSubRole1,
  SAERequestSubRole_requestSubRole2,
  SAERequestSubRole_requestSubRole3,
  SAERequestSubRole_requestSubRole4,
  SAERequestSubRole_requestSubRole5,
  SAERequestSubRole_requestSubRole6,
  SAERequestSubRole_requestSubRole7,
  SAERequestSubRole_requestSubRole8,
  SAERequestSubRole_requestSubRole9,
  SAERequestSubRole_requestSubRole10,
  SAERequestSubRole_requestSubRole11,
  SAERequestSubRole_requestSubRole12,
  SAERequestSubRole_requestSubRole13,
  SAERequestSubRole_requestSubRole14,
  SAERequestSubRole_requestSubRoleReserved,
} SAERequestSubRole;

extern const ASN1CType asn1_type_SAERequestSubRole[];

typedef enum SAERequestImportanceLevel {
  SAERequestImportanceLevel_requestImportanceLevelUnKnown,
  SAERequestImportanceLevel_requestImportanceLevel1,
  SAERequestImportanceLevel_requestImportanceLevel2,
  SAERequestImportanceLevel_requestImportanceLevel3,
  SAERequestImportanceLevel_requestImportanceLevel4,
  SAERequestImportanceLevel_requestImportanceLevel5,
  SAERequestImportanceLevel_requestImportanceLevel6,
  SAERequestImportanceLevel_requestImportanceLevel7,
  SAERequestImportanceLevel_requestImportanceLevel8,
  SAERequestImportanceLevel_requestImportanceLevel9,
  SAERequestImportanceLevel_requestImportanceLevel10,
  SAERequestImportanceLevel_requestImportanceLevel11,
  SAERequestImportanceLevel_requestImportanceLevel12,
  SAERequestImportanceLevel_requestImportanceLevel13,
  SAERequestImportanceLevel_requestImportanceLevel14,
  SAERequestImportanceLevel_requestImportanceReserved,
} SAERequestImportanceLevel;

extern const ASN1CType asn1_type_SAERequestImportanceLevel[];

typedef struct SAERegionalExtension_52 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_52;


extern const ASN1CType asn1_type_SAERegionalExtension_52[];

typedef struct SAERequestorType {
  SAEBasicVehicleRole role;
  BOOL subrole_option;
  SAERequestSubRole subrole;
  BOOL request_option;
  SAERequestImportanceLevel request;
  BOOL iso3883_option;
  SAEIso3833VehicleType iso3883;
  BOOL hpmsType_option;
  SAEVehicleType hpmsType;
  BOOL regional_option;
  SAERegionalExtension_52 regional;
} SAERequestorType;


extern const ASN1CType asn1_type_SAERequestorType[];

typedef struct SAERequestorPositionVector {
  SAEPosition3D position;
  BOOL heading_option;
  SAEAngle heading;
  BOOL speed_option;
  SAETransmissionAndSpeed speed;
} SAERequestorPositionVector;


extern const ASN1CType asn1_type_SAERequestorPositionVector[];

typedef ASN1BitString SAETransitVehicleStatus;

extern const ASN1CType asn1_type_SAETransitVehicleStatus[];

typedef enum SAETransitVehicleOccupancy {
  SAETransitVehicleOccupancy_occupancyUnknown,
  SAETransitVehicleOccupancy_occupancyEmpty,
  SAETransitVehicleOccupancy_occupancyVeryLow,
  SAETransitVehicleOccupancy_occupancyLow,
  SAETransitVehicleOccupancy_occupancyMed,
  SAETransitVehicleOccupancy_occupancyHigh,
  SAETransitVehicleOccupancy_occupancyNearlyFull,
  SAETransitVehicleOccupancy_occupancyFull,
} SAETransitVehicleOccupancy;

extern const ASN1CType asn1_type_SAETransitVehicleOccupancy[];

typedef int SAEDeltaTime;

extern const ASN1CType asn1_type_SAEDeltaTime[];

typedef struct SAERegionalExtension_51 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_51;


extern const ASN1CType asn1_type_SAERegionalExtension_51[];

typedef struct SAERequestorDescription_1 {
  SAERegionalExtension_51 *tab;
  size_t count;
} SAERequestorDescription_1;

extern const ASN1CType asn1_type_SAERequestorDescription_1[];

typedef struct SAERequestorDescription {
  SAEVehicleID id;
  BOOL type_option;
  SAERequestorType type;
  BOOL position_option;
  SAERequestorPositionVector position;
  BOOL name_option;
  SAEDescriptiveName name;
  BOOL routeName_option;
  SAEDescriptiveName routeName;
  BOOL transitStatus_option;
  SAETransitVehicleStatus transitStatus;
  BOOL transitOccupancy_option;
  SAETransitVehicleOccupancy transitOccupancy;
  BOOL transitSchedule_option;
  SAEDeltaTime transitSchedule;
  BOOL regional_option;
  SAERequestorDescription_1 regional;
} SAERequestorDescription;


extern const ASN1CType asn1_type_SAERequestorDescription[];

typedef struct SAERegionalExtension_13 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_13;


extern const ASN1CType asn1_type_SAERegionalExtension_13[];

typedef struct SAESignalRequestMessage_1 {
  SAERegionalExtension_13 *tab;
  size_t count;
} SAESignalRequestMessage_1;

extern const ASN1CType asn1_type_SAESignalRequestMessage_1[];

typedef struct SAESignalRequestMessage {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  SAEDSecond second;
  BOOL sequenceNumber_option;
  SAEMsgCount sequenceNumber;
  BOOL requests_option;
  SAESignalRequestList requests;
  SAERequestorDescription requestor;
  BOOL regional_option;
  SAESignalRequestMessage_1 regional;
} SAESignalRequestMessage;


extern const ASN1CType asn1_type_SAESignalRequestMessage[];

typedef struct SAESignalRequesterInfo {
  SAEVehicleID id;
  SAERequestID request;
  SAEMsgCount sequenceNumber;
  BOOL role_option;
  SAEBasicVehicleRole role;
  BOOL typeData_option;
  SAERequestorType typeData;
} SAESignalRequesterInfo;


extern const ASN1CType asn1_type_SAESignalRequesterInfo[];

typedef enum SAEPrioritizationResponseStatus {
  SAEPrioritizationResponseStatus_unknown,
  SAEPrioritizationResponseStatus_requested,
  SAEPrioritizationResponseStatus_processing,
  SAEPrioritizationResponseStatus_watchOtherTraffic,
  SAEPrioritizationResponseStatus_granted,
  SAEPrioritizationResponseStatus_rejected,
  SAEPrioritizationResponseStatus_maxPresence,
  SAEPrioritizationResponseStatus_reserviceLocked,
} SAEPrioritizationResponseStatus;

extern const ASN1CType asn1_type_SAEPrioritizationResponseStatus[];

typedef struct SAERegionalExtension_57 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_57;


extern const ASN1CType asn1_type_SAERegionalExtension_57[];

typedef struct SAESignalStatusPackage_1 {
  SAERegionalExtension_57 *tab;
  size_t count;
} SAESignalStatusPackage_1;

extern const ASN1CType asn1_type_SAESignalStatusPackage_1[];

typedef struct SAESignalStatusPackage {
  BOOL requester_option;
  SAESignalRequesterInfo requester;
  SAEIntersectionAccessPoint inboundOn;
  BOOL outboundOn_option;
  SAEIntersectionAccessPoint outboundOn;
  BOOL minute_option;
  SAEMinuteOfTheYear minute;
  BOOL second_option;
  SAEDSecond second;
  BOOL duration_option;
  SAEDSecond duration;
  SAEPrioritizationResponseStatus status;
  BOOL regional_option;
  SAESignalStatusPackage_1 regional;
} SAESignalStatusPackage;


extern const ASN1CType asn1_type_SAESignalStatusPackage[];

typedef struct SAESignalStatusPackageList {
  SAESignalStatusPackage *tab;
  size_t count;
} SAESignalStatusPackageList;

extern const ASN1CType asn1_type_SAESignalStatusPackageList[];

typedef struct SAERegionalExtension_58 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_58;


extern const ASN1CType asn1_type_SAERegionalExtension_58[];

typedef struct SAESignalStatus_1 {
  SAERegionalExtension_58 *tab;
  size_t count;
} SAESignalStatus_1;

extern const ASN1CType asn1_type_SAESignalStatus_1[];

typedef struct SAESignalStatus {
  SAEMsgCount sequenceNumber;
  SAEIntersectionReferenceID id;
  SAESignalStatusPackageList sigStatus;
  BOOL regional_option;
  SAESignalStatus_1 regional;
} SAESignalStatus;


extern const ASN1CType asn1_type_SAESignalStatus[];

typedef struct SAESignalStatusList {
  SAESignalStatus *tab;
  size_t count;
} SAESignalStatusList;

extern const ASN1CType asn1_type_SAESignalStatusList[];

typedef struct SAERegionalExtension_14 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_14;


extern const ASN1CType asn1_type_SAERegionalExtension_14[];

typedef struct SAESignalStatusMessage_1 {
  SAERegionalExtension_14 *tab;
  size_t count;
} SAESignalStatusMessage_1;

extern const ASN1CType asn1_type_SAESignalStatusMessage_1[];

typedef struct SAESignalStatusMessage {
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  SAEDSecond second;
  BOOL sequenceNumber_option;
  SAEMsgCount sequenceNumber;
  SAESignalStatusList status;
  BOOL regional_option;
  SAESignalStatusMessage_1 regional;
} SAESignalStatusMessage;


extern const ASN1CType asn1_type_SAESignalStatusMessage[];

typedef ASN1String SAEUniqueMSGID;

extern const ASN1CType asn1_type_SAEUniqueMSGID[];

typedef ASN1String SAEURL_Base;

extern const ASN1CType asn1_type_SAEURL_Base[];

typedef enum SAETravelerInfoType {
  SAETravelerInfoType_unknown,
  SAETravelerInfoType_advisory,
  SAETravelerInfoType_roadSignage,
  SAETravelerInfoType_commercialSignage,
} SAETravelerInfoType;

extern const ASN1CType asn1_type_SAETravelerInfoType[];

typedef enum SAEMUTCDCode {
  SAEMUTCDCode_none,
  SAEMUTCDCode_regulatory,
  SAEMUTCDCode_warning,
  SAEMUTCDCode_maintenance,
  SAEMUTCDCode_motoristService,
  SAEMUTCDCode_guide,
  SAEMUTCDCode_rec,
} SAEMUTCDCode;

extern const ASN1CType asn1_type_SAEMUTCDCode[];

typedef ASN1String SAEMsgCRC;

extern const ASN1CType asn1_type_SAEMsgCRC[];

typedef struct SAERoadSignID {
  SAEPosition3D position;
  SAEHeadingSlice viewAngle;
  BOOL mutcdCode_option;
  SAEMUTCDCode mutcdCode;
  BOOL crc_option;
  SAEMsgCRC crc;
} SAERoadSignID;


extern const ASN1CType asn1_type_SAERoadSignID[];

typedef enum {
  SAETravelerDataFrame_1_furtherInfoID,
  SAETravelerDataFrame_1_roadSignID,
} SAETravelerDataFrame_1_choice;

typedef struct SAETravelerDataFrame_1 {
  SAETravelerDataFrame_1_choice choice;
  union {
    SAEFurtherInfoID furtherInfoID;
    SAERoadSignID roadSignID;
  } u;
} SAETravelerDataFrame_1;

extern const ASN1CType asn1_type_SAETravelerDataFrame_1[];

typedef int SAEMinutesDuration;

extern const ASN1CType asn1_type_SAEMinutesDuration[];

typedef int SAESignPrority;

extern const ASN1CType asn1_type_SAESignPrority[];

typedef enum SAEDirectionOfUse {
  SAEDirectionOfUse_unavailable,
  SAEDirectionOfUse_forward,
  SAEDirectionOfUse_reverse,
  SAEDirectionOfUse_both,
} SAEDirectionOfUse;

extern const ASN1CType asn1_type_SAEDirectionOfUse[];

typedef int SAEZoom;

extern const ASN1CType asn1_type_SAEZoom[];

typedef int SAEOffsetLL_B12;

extern const ASN1CType asn1_type_SAEOffsetLL_B12[];

typedef struct SAENode_LL_24B {
  SAEOffsetLL_B12 lon;
  SAEOffsetLL_B12 lat;
} SAENode_LL_24B;


extern const ASN1CType asn1_type_SAENode_LL_24B[];

typedef int SAEOffsetLL_B14;

extern const ASN1CType asn1_type_SAEOffsetLL_B14[];

typedef struct SAENode_LL_28B {
  SAEOffsetLL_B14 lon;
  SAEOffsetLL_B14 lat;
} SAENode_LL_28B;


extern const ASN1CType asn1_type_SAENode_LL_28B[];

typedef int SAEOffsetLL_B16;

extern const ASN1CType asn1_type_SAEOffsetLL_B16[];

typedef struct SAENode_LL_32B {
  SAEOffsetLL_B16 lon;
  SAEOffsetLL_B16 lat;
} SAENode_LL_32B;


extern const ASN1CType asn1_type_SAENode_LL_32B[];

typedef struct SAENode_LL_36B {
  SAEOffsetLL_B18 lon;
  SAEOffsetLL_B18 lat;
} SAENode_LL_36B;


extern const ASN1CType asn1_type_SAENode_LL_36B[];

typedef int SAEOffsetLL_B22;

extern const ASN1CType asn1_type_SAEOffsetLL_B22[];

typedef struct SAENode_LL_44B {
  SAEOffsetLL_B22 lon;
  SAEOffsetLL_B22 lat;
} SAENode_LL_44B;


extern const ASN1CType asn1_type_SAENode_LL_44B[];

typedef int SAEOffsetLL_B24;

extern const ASN1CType asn1_type_SAEOffsetLL_B24[];

typedef struct SAENode_LL_48B {
  SAEOffsetLL_B24 lon;
  SAEOffsetLL_B24 lat;
} SAENode_LL_48B;


extern const ASN1CType asn1_type_SAENode_LL_48B[];

typedef struct SAERegionalExtension_47 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_47;


extern const ASN1CType asn1_type_SAERegionalExtension_47[];

typedef enum {
  SAENodeOffsetPointLL_node_LL1,
  SAENodeOffsetPointLL_node_LL2,
  SAENodeOffsetPointLL_node_LL3,
  SAENodeOffsetPointLL_node_LL4,
  SAENodeOffsetPointLL_node_LL5,
  SAENodeOffsetPointLL_node_LL6,
  SAENodeOffsetPointLL_node_LatLon,
  SAENodeOffsetPointLL_regional,
} SAENodeOffsetPointLL_choice;

typedef struct SAENodeOffsetPointLL {
  SAENodeOffsetPointLL_choice choice;
  union {
    SAENode_LL_24B node_LL1;
    SAENode_LL_28B node_LL2;
    SAENode_LL_32B node_LL3;
    SAENode_LL_36B node_LL4;
    SAENode_LL_44B node_LL5;
    SAENode_LL_48B node_LL6;
    SAENode_LLmD_64b node_LatLon;
    SAERegionalExtension_47 regional;
  } u;
} SAENodeOffsetPointLL;

extern const ASN1CType asn1_type_SAENodeOffsetPointLL[];

typedef enum SAENodeAttributeLL {
  SAENodeAttributeLL_reserved,
  SAENodeAttributeLL_stopLine,
  SAENodeAttributeLL_roundedCapStyleA,
  SAENodeAttributeLL_roundedCapStyleB,
  SAENodeAttributeLL_mergePoint,
  SAENodeAttributeLL_divergePoint,
  SAENodeAttributeLL_downstreamStopLine,
  SAENodeAttributeLL_downstreamStartNode,
  SAENodeAttributeLL_closedToTraffic,
  SAENodeAttributeLL_safeIsland,
  SAENodeAttributeLL_curbPresentAtStepOff,
  SAENodeAttributeLL_hydrantPresent,
} SAENodeAttributeLL;

extern const ASN1CType asn1_type_SAENodeAttributeLL[];

typedef struct SAENodeAttributeLLList {
  SAENodeAttributeLL *tab;
  size_t count;
} SAENodeAttributeLLList;

extern const ASN1CType asn1_type_SAENodeAttributeLLList[];

typedef enum SAESegmentAttributeLL {
  SAESegmentAttributeLL_reserved,
  SAESegmentAttributeLL_doNotBlock,
  SAESegmentAttributeLL_whiteLine,
  SAESegmentAttributeLL_mergingLaneLeft,
  SAESegmentAttributeLL_mergingLaneRight,
  SAESegmentAttributeLL_curbOnLeft,
  SAESegmentAttributeLL_curbOnRight,
  SAESegmentAttributeLL_loadingzoneOnLeft,
  SAESegmentAttributeLL_loadingzoneOnRight,
  SAESegmentAttributeLL_turnOutPointOnLeft,
  SAESegmentAttributeLL_turnOutPointOnRight,
  SAESegmentAttributeLL_adjacentParkingOnLeft,
  SAESegmentAttributeLL_adjacentParkingOnRight,
  SAESegmentAttributeLL_adjacentBikeLaneOnLeft,
  SAESegmentAttributeLL_adjacentBikeLaneOnRight,
  SAESegmentAttributeLL_sharedBikeLane,
  SAESegmentAttributeLL_bikeBoxInFront,
  SAESegmentAttributeLL_transitStopOnLeft,
  SAESegmentAttributeLL_transitStopOnRight,
  SAESegmentAttributeLL_transitStopInLane,
  SAESegmentAttributeLL_sharedWithTrackedVehicle,
  SAESegmentAttributeLL_safeIsland,
  SAESegmentAttributeLL_lowCurbsPresent,
  SAESegmentAttributeLL_rumbleStripPresent,
  SAESegmentAttributeLL_audibleSignalingPresent,
  SAESegmentAttributeLL_adaptiveTimingPresent,
  SAESegmentAttributeLL_rfSignalRequestPresent,
  SAESegmentAttributeLL_partialCurbIntrusion,
  SAESegmentAttributeLL_taperToLeft,
  SAESegmentAttributeLL_taperToRight,
  SAESegmentAttributeLL_taperToCenterLine,
  SAESegmentAttributeLL_parallelParking,
  SAESegmentAttributeLL_headInParking,
  SAESegmentAttributeLL_freeParking,
  SAESegmentAttributeLL_timeRestrictionsOnParking,
  SAESegmentAttributeLL_costToPark,
  SAESegmentAttributeLL_midBlockCurbPresent,
  SAESegmentAttributeLL_unEvenPavementPresent,
} SAESegmentAttributeLL;

extern const ASN1CType asn1_type_SAESegmentAttributeLL[];

typedef struct SAESegmentAttributeLLList {
  SAESegmentAttributeLL *tab;
  size_t count;
} SAESegmentAttributeLLList;

extern const ASN1CType asn1_type_SAESegmentAttributeLLList[];

typedef struct SAERegionalExtension_45 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_45;


extern const ASN1CType asn1_type_SAERegionalExtension_45[];

typedef struct SAENodeAttributeSetLL_1 {
  SAERegionalExtension_45 *tab;
  size_t count;
} SAENodeAttributeSetLL_1;

extern const ASN1CType asn1_type_SAENodeAttributeSetLL_1[];

typedef struct SAENodeAttributeSetLL {
  BOOL localNode_option;
  SAENodeAttributeLLList localNode;
  BOOL disabled_option;
  SAESegmentAttributeLLList disabled;
  BOOL enabled_option;
  SAESegmentAttributeLLList enabled;
  BOOL data_option;
  SAELaneDataAttributeList data;
  BOOL dWidth_option;
  SAEOffset_B10 dWidth;
  BOOL dElevation_option;
  SAEOffset_B10 dElevation;
  BOOL regional_option;
  SAENodeAttributeSetLL_1 regional;
} SAENodeAttributeSetLL;


extern const ASN1CType asn1_type_SAENodeAttributeSetLL[];

typedef struct SAENodeLL {
  SAENodeOffsetPointLL delta;
  BOOL attributes_option;
  SAENodeAttributeSetLL attributes;
} SAENodeLL;


extern const ASN1CType asn1_type_SAENodeLL[];

typedef struct SAENodeSetLL {
  SAENodeLL *tab;
  size_t count;
} SAENodeSetLL;

extern const ASN1CType asn1_type_SAENodeSetLL[];

typedef enum {
  SAENodeListLL_nodes,
} SAENodeListLL_choice;

typedef struct SAENodeListLL {
  SAENodeListLL_choice choice;
  union {
    SAENodeSetLL nodes;
  } u;
} SAENodeListLL;

extern const ASN1CType asn1_type_SAENodeListLL[];

typedef enum {
  SAEOffsetSystem_1_xy,
  SAEOffsetSystem_1_ll,
} SAEOffsetSystem_1_choice;

typedef struct SAEOffsetSystem_1 {
  SAEOffsetSystem_1_choice choice;
  union {
    SAENodeListXY xy;
    SAENodeListLL ll;
  } u;
} SAEOffsetSystem_1;

extern const ASN1CType asn1_type_SAEOffsetSystem_1[];

typedef struct SAEOffsetSystem {
  BOOL scale_option;
  SAEZoom scale;
  SAEOffsetSystem_1 offset;
} SAEOffsetSystem;


extern const ASN1CType asn1_type_SAEOffsetSystem[];

typedef int SAERadius_B12;

extern const ASN1CType asn1_type_SAERadius_B12[];

typedef enum SAEDistanceUnits {
  SAEDistanceUnits_centimeter,
  SAEDistanceUnits_cm2_5,
  SAEDistanceUnits_decimeter,
  SAEDistanceUnits_meter,
  SAEDistanceUnits_kilometer,
  SAEDistanceUnits_foot,
  SAEDistanceUnits_yard,
  SAEDistanceUnits_mile,
} SAEDistanceUnits;

extern const ASN1CType asn1_type_SAEDistanceUnits[];

typedef struct SAECircle {
  SAEPosition3D center;
  SAERadius_B12 radius;
  SAEDistanceUnits units;
} SAECircle;


extern const ASN1CType asn1_type_SAECircle[];

typedef struct SAERegionalExtension_38 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_38;


extern const ASN1CType asn1_type_SAERegionalExtension_38[];

typedef struct SAEGeometricProjection_1 {
  SAERegionalExtension_38 *tab;
  size_t count;
} SAEGeometricProjection_1;

extern const ASN1CType asn1_type_SAEGeometricProjection_1[];

typedef struct SAEGeometricProjection {
  SAEHeadingSlice direction;
  BOOL extent_option;
  SAEExtent extent;
  BOOL laneWidth_option;
  SAELaneWidth laneWidth;
  SAECircle circle;
  BOOL regional_option;
  SAEGeometricProjection_1 regional;
} SAEGeometricProjection;


extern const ASN1CType asn1_type_SAEGeometricProjection[];

typedef struct SAEShapePointSet {
  BOOL anchor_option;
  SAEPosition3D anchor;
  BOOL laneWidth_option;
  SAELaneWidth laneWidth;
  BOOL directionality_option;
  SAEDirectionOfUse directionality;
  SAENodeListXY nodeList;
} SAEShapePointSet;


extern const ASN1CType asn1_type_SAEShapePointSet[];

typedef struct SAERegionOffsets {
  SAEOffsetLL_B16 xOffset;
  SAEOffsetLL_B16 yOffset;
  BOOL zOffset_option;
  SAEOffsetLL_B16 zOffset;
} SAERegionOffsets;


extern const ASN1CType asn1_type_SAERegionOffsets[];

typedef struct SAERegionList {
  SAERegionOffsets *tab;
  size_t count;
} SAERegionList;

extern const ASN1CType asn1_type_SAERegionList[];

typedef struct SAERegionPointSet {
  BOOL anchor_option;
  SAEPosition3D anchor;
  BOOL scale_option;
  SAEZoom scale;
  SAERegionList nodeList;
} SAERegionPointSet;


extern const ASN1CType asn1_type_SAERegionPointSet[];

typedef enum {
  SAEValidRegion_1_shapePointSet,
  SAEValidRegion_1_circle,
  SAEValidRegion_1_regionPointSet,
} SAEValidRegion_1_choice;

typedef struct SAEValidRegion_1 {
  SAEValidRegion_1_choice choice;
  union {
    SAEShapePointSet shapePointSet;
    SAECircle circle;
    SAERegionPointSet regionPointSet;
  } u;
} SAEValidRegion_1;

extern const ASN1CType asn1_type_SAEValidRegion_1[];

typedef struct SAEValidRegion {
  SAEHeadingSlice direction;
  BOOL extent_option;
  SAEExtent extent;
  SAEValidRegion_1 area;
} SAEValidRegion;


extern const ASN1CType asn1_type_SAEValidRegion[];

typedef enum {
  SAEGeographicalPath_1_path,
  SAEGeographicalPath_1_geometry,
  SAEGeographicalPath_1_oldRegion,
} SAEGeographicalPath_1_choice;

typedef struct SAEGeographicalPath_1 {
  SAEGeographicalPath_1_choice choice;
  union {
    SAEOffsetSystem path;
    SAEGeometricProjection geometry;
    SAEValidRegion oldRegion;
  } u;
} SAEGeographicalPath_1;

extern const ASN1CType asn1_type_SAEGeographicalPath_1[];

typedef struct SAERegionalExtension_37 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_37;


extern const ASN1CType asn1_type_SAERegionalExtension_37[];

typedef struct SAEGeographicalPath_2 {
  SAERegionalExtension_37 *tab;
  size_t count;
} SAEGeographicalPath_2;

extern const ASN1CType asn1_type_SAEGeographicalPath_2[];

typedef struct SAEGeographicalPath {
  BOOL name_option;
  SAEDescriptiveName name;
  BOOL id_option;
  SAERoadSegmentReferenceID id;
  BOOL anchor_option;
  SAEPosition3D anchor;
  BOOL laneWidth_option;
  SAELaneWidth laneWidth;
  BOOL directionality_option;
  SAEDirectionOfUse directionality;
  BOOL closedPath_option;
  BOOL closedPath;
  BOOL direction_option;
  SAEHeadingSlice direction;
  BOOL description_option;
  SAEGeographicalPath_1 description;
  BOOL regional_option;
  SAEGeographicalPath_2 regional;
} SAEGeographicalPath;


extern const ASN1CType asn1_type_SAEGeographicalPath[];

typedef struct SAETravelerDataFrame_2 {
  SAEGeographicalPath *tab;
  size_t count;
} SAETravelerDataFrame_2;

extern const ASN1CType asn1_type_SAETravelerDataFrame_2[];

typedef ASN1String SAEITIStext;

extern const ASN1CType asn1_type_SAEITIStext[];

typedef enum {
  SAEITIScodesAndText_1_itis,
  SAEITIScodesAndText_1_text,
} SAEITIScodesAndText_1_choice;

typedef struct SAEITIScodesAndText_1 {
  SAEITIScodesAndText_1_choice choice;
  union {
    SAEITIScodes itis;
    SAEITIStext text;
  } u;
} SAEITIScodesAndText_1;

extern const ASN1CType asn1_type_SAEITIScodesAndText_1[];

typedef struct SAEITIScodesAndText_2 {
  SAEITIScodesAndText_1 item;
} SAEITIScodesAndText_2;


extern const ASN1CType asn1_type_SAEITIScodesAndText_2[];

typedef struct SAEITIScodesAndText {
  SAEITIScodesAndText_2 *tab;
  size_t count;
} SAEITIScodesAndText;

extern const ASN1CType asn1_type_SAEITIScodesAndText[];

typedef ASN1String SAEITIStextPhrase;

extern const ASN1CType asn1_type_SAEITIStextPhrase[];

typedef enum {
  SAEWorkZone_1_itis,
  SAEWorkZone_1_text,
} SAEWorkZone_1_choice;

typedef struct SAEWorkZone_1 {
  SAEWorkZone_1_choice choice;
  union {
    SAEITIScodes itis;
    SAEITIStextPhrase text;
  } u;
} SAEWorkZone_1;

extern const ASN1CType asn1_type_SAEWorkZone_1[];

typedef struct SAEWorkZone_2 {
  SAEWorkZone_1 item;
} SAEWorkZone_2;


extern const ASN1CType asn1_type_SAEWorkZone_2[];

typedef struct SAEWorkZone {
  SAEWorkZone_2 *tab;
  size_t count;
} SAEWorkZone;

extern const ASN1CType asn1_type_SAEWorkZone[];

typedef enum {
  SAEGenericSignage_1_itis,
  SAEGenericSignage_1_text,
} SAEGenericSignage_1_choice;

typedef struct SAEGenericSignage_1 {
  SAEGenericSignage_1_choice choice;
  union {
    SAEITIScodes itis;
    SAEITIStextPhrase text;
  } u;
} SAEGenericSignage_1;

extern const ASN1CType asn1_type_SAEGenericSignage_1[];

typedef struct SAEGenericSignage_2 {
  SAEGenericSignage_1 item;
} SAEGenericSignage_2;


extern const ASN1CType asn1_type_SAEGenericSignage_2[];

typedef struct SAEGenericSignage {
  SAEGenericSignage_2 *tab;
  size_t count;
} SAEGenericSignage;

extern const ASN1CType asn1_type_SAEGenericSignage[];

typedef enum {
  SAESpeedLimit_1_itis,
  SAESpeedLimit_1_text,
} SAESpeedLimit_1_choice;

typedef struct SAESpeedLimit_1 {
  SAESpeedLimit_1_choice choice;
  union {
    SAEITIScodes itis;
    SAEITIStextPhrase text;
  } u;
} SAESpeedLimit_1;

extern const ASN1CType asn1_type_SAESpeedLimit_1[];

typedef struct SAESpeedLimit_2 {
  SAESpeedLimit_1 item;
} SAESpeedLimit_2;


extern const ASN1CType asn1_type_SAESpeedLimit_2[];

typedef struct SAESpeedLimit {
  SAESpeedLimit_2 *tab;
  size_t count;
} SAESpeedLimit;

extern const ASN1CType asn1_type_SAESpeedLimit[];

typedef enum {
  SAEExitService_1_itis,
  SAEExitService_1_text,
} SAEExitService_1_choice;

typedef struct SAEExitService_1 {
  SAEExitService_1_choice choice;
  union {
    SAEITIScodes itis;
    SAEITIStextPhrase text;
  } u;
} SAEExitService_1;

extern const ASN1CType asn1_type_SAEExitService_1[];

typedef struct SAEExitService_2 {
  SAEExitService_1 item;
} SAEExitService_2;


extern const ASN1CType asn1_type_SAEExitService_2[];

typedef struct SAEExitService {
  SAEExitService_2 *tab;
  size_t count;
} SAEExitService;

extern const ASN1CType asn1_type_SAEExitService[];

typedef enum {
  SAETravelerDataFrame_3_advisory,
  SAETravelerDataFrame_3_workZone,
  SAETravelerDataFrame_3_genericSign,
  SAETravelerDataFrame_3_speedLimit,
  SAETravelerDataFrame_3_exitService,
} SAETravelerDataFrame_3_choice;

typedef struct SAETravelerDataFrame_3 {
  SAETravelerDataFrame_3_choice choice;
  union {
    SAEITIScodesAndText advisory;
    SAEWorkZone workZone;
    SAEGenericSignage genericSign;
    SAESpeedLimit speedLimit;
    SAEExitService exitService;
  } u;
} SAETravelerDataFrame_3;

extern const ASN1CType asn1_type_SAETravelerDataFrame_3[];

typedef ASN1String SAEURL_Short;

extern const ASN1CType asn1_type_SAEURL_Short[];

typedef struct SAETravelerDataFrame {
  SAESSPindex sspTimRights;
  SAETravelerInfoType frameType;
  SAETravelerDataFrame_1 msgId;
  BOOL startYear_option;
  SAEDYear startYear;
  SAEMinuteOfTheYear startTime;
  SAEMinutesDuration duratonTime;
  SAESignPrority priority;
  SAESSPindex sspLocationRights;
  SAETravelerDataFrame_2 regions;
  SAESSPindex sspMsgRights1;
  SAESSPindex sspMsgRights2;
  SAETravelerDataFrame_3 content;
  BOOL url_option;
  SAEURL_Short url;
} SAETravelerDataFrame;


extern const ASN1CType asn1_type_SAETravelerDataFrame[];

typedef struct SAETravelerDataFrameList {
  SAETravelerDataFrame *tab;
  size_t count;
} SAETravelerDataFrameList;

extern const ASN1CType asn1_type_SAETravelerDataFrameList[];

typedef struct SAERegionalExtension_15 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_15;


extern const ASN1CType asn1_type_SAERegionalExtension_15[];

typedef struct SAETravelerInformation_1 {
  SAERegionalExtension_15 *tab;
  size_t count;
} SAETravelerInformation_1;

extern const ASN1CType asn1_type_SAETravelerInformation_1[];

typedef struct SAETravelerInformation {
  SAEMsgCount msgCnt;
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL packetID_option;
  SAEUniqueMSGID packetID;
  BOOL urlB_option;
  SAEURL_Base urlB;
  SAETravelerDataFrameList dataFrames;
  BOOL regional_option;
  SAETravelerInformation_1 regional;
} SAETravelerInformation;


extern const ASN1CType asn1_type_SAETravelerInformation[];

typedef enum SAEPersonalDeviceUserType {
  SAEPersonalDeviceUserType_unavailable,
  SAEPersonalDeviceUserType_aPEDESTRIAN,
  SAEPersonalDeviceUserType_aPEDALCYCLIST,
  SAEPersonalDeviceUserType_aPUBLICSAFETYWORKER,
  SAEPersonalDeviceUserType_anANIMAL,
} SAEPersonalDeviceUserType;

extern const ASN1CType asn1_type_SAEPersonalDeviceUserType[];

typedef enum SAEHumanPropelledType {
  SAEHumanPropelledType_unavailable,
  SAEHumanPropelledType_otherTypes,
  SAEHumanPropelledType_onFoot,
  SAEHumanPropelledType_skateboard,
  SAEHumanPropelledType_pushOrKickScooter,
  SAEHumanPropelledType_wheelchair,
} SAEHumanPropelledType;

extern const ASN1CType asn1_type_SAEHumanPropelledType[];

typedef enum SAEAnimalPropelledType {
  SAEAnimalPropelledType_unavailable,
  SAEAnimalPropelledType_otherTypes,
  SAEAnimalPropelledType_animalMounted,
  SAEAnimalPropelledType_animalDrawnCarriage,
} SAEAnimalPropelledType;

extern const ASN1CType asn1_type_SAEAnimalPropelledType[];

typedef enum SAEMotorizedPropelledType {
  SAEMotorizedPropelledType_unavailable,
  SAEMotorizedPropelledType_otherTypes,
  SAEMotorizedPropelledType_wheelChair,
  SAEMotorizedPropelledType_bicycle,
  SAEMotorizedPropelledType_scooter,
  SAEMotorizedPropelledType_selfBalancingDevice,
} SAEMotorizedPropelledType;

extern const ASN1CType asn1_type_SAEMotorizedPropelledType[];

typedef enum {
  SAEPropelledInformation_human,
  SAEPropelledInformation_animal,
  SAEPropelledInformation_motor,
} SAEPropelledInformation_choice;

typedef struct SAEPropelledInformation {
  SAEPropelledInformation_choice choice;
  union {
    SAEHumanPropelledType human;
    SAEAnimalPropelledType animal;
    SAEMotorizedPropelledType motor;
  } u;
} SAEPropelledInformation;

extern const ASN1CType asn1_type_SAEPropelledInformation[];

typedef ASN1BitString SAEPersonalDeviceUsageState;

extern const ASN1CType asn1_type_SAEPersonalDeviceUsageState[];

typedef BOOL SAEPersonalCrossingRequest;

extern const ASN1CType asn1_type_SAEPersonalCrossingRequest[];

typedef BOOL SAEPersonalCrossingInProgress;

extern const ASN1CType asn1_type_SAEPersonalCrossingInProgress[];

typedef enum SAENumberOfParticipantsInCluster {
  SAENumberOfParticipantsInCluster_unavailable,
  SAENumberOfParticipantsInCluster_small,
  SAENumberOfParticipantsInCluster_medium,
  SAENumberOfParticipantsInCluster_large,
} SAENumberOfParticipantsInCluster;

extern const ASN1CType asn1_type_SAENumberOfParticipantsInCluster[];

typedef int SAEPersonalClusterRadius;

extern const ASN1CType asn1_type_SAEPersonalClusterRadius[];

typedef enum SAEPublicSafetyEventResponderWorkerType {
  SAEPublicSafetyEventResponderWorkerType_unavailable,
  SAEPublicSafetyEventResponderWorkerType_towOperater,
  SAEPublicSafetyEventResponderWorkerType_fireAndEMSWorker,
  SAEPublicSafetyEventResponderWorkerType_aDOTWorker,
  SAEPublicSafetyEventResponderWorkerType_lawEnforcement,
  SAEPublicSafetyEventResponderWorkerType_hazmatResponder,
  SAEPublicSafetyEventResponderWorkerType_animalControlWorker,
  SAEPublicSafetyEventResponderWorkerType_otherPersonnel,
} SAEPublicSafetyEventResponderWorkerType;

extern const ASN1CType asn1_type_SAEPublicSafetyEventResponderWorkerType[];

typedef ASN1BitString SAEPublicSafetyAndRoadWorkerActivity;

extern const ASN1CType asn1_type_SAEPublicSafetyAndRoadWorkerActivity[];

typedef ASN1BitString SAEPublicSafetyDirectingTrafficSubType;

extern const ASN1CType asn1_type_SAEPublicSafetyDirectingTrafficSubType[];

typedef ASN1BitString SAEPersonalAssistive;

extern const ASN1CType asn1_type_SAEPersonalAssistive[];

typedef ASN1BitString SAEUserSizeAndBehaviour;

extern const ASN1CType asn1_type_SAEUserSizeAndBehaviour[];

typedef enum SAEAttachment {
  SAEAttachment_unavailable,
  SAEAttachment_stroller,
  SAEAttachment_bicycleTrailer,
  SAEAttachment_cart,
  SAEAttachment_wheelchair,
  SAEAttachment_otherWalkAssistAttachments,
  SAEAttachment_pet,
} SAEAttachment;

extern const ASN1CType asn1_type_SAEAttachment[];

typedef int SAEAttachmentRadius;

extern const ASN1CType asn1_type_SAEAttachmentRadius[];

typedef enum SAEAnimalType {
  SAEAnimalType_unavailable,
  SAEAnimalType_serviceUse,
  SAEAnimalType_pet,
  SAEAnimalType_farm,
} SAEAnimalType;

extern const ASN1CType asn1_type_SAEAnimalType[];

typedef struct SAERegionalExtension_7 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_7;


extern const ASN1CType asn1_type_SAERegionalExtension_7[];

typedef struct SAEPersonalSafetyMessage_1 {
  SAERegionalExtension_7 *tab;
  size_t count;
} SAEPersonalSafetyMessage_1;

extern const ASN1CType asn1_type_SAEPersonalSafetyMessage_1[];

typedef struct SAEPersonalSafetyMessage {
  SAEPersonalDeviceUserType basicType;
  SAEDSecond secMark;
  SAEMsgCount msgCnt;
  SAETemporaryID id;
  SAEPosition3D position;
  SAEPositionalAccuracy accuracy;
  SAEVelocity speed;
  SAEHeading heading;
  BOOL accelSet_option;
  SAEAccelerationSet4Way accelSet;
  BOOL pathHistory_option;
  SAEPathHistory pathHistory;
  BOOL pathPrediction_option;
  SAEPathPrediction pathPrediction;
  BOOL propulsion_option;
  SAEPropelledInformation propulsion;
  BOOL useState_option;
  SAEPersonalDeviceUsageState useState;
  BOOL crossRequest_option;
  SAEPersonalCrossingRequest crossRequest;
  BOOL crossState_option;
  SAEPersonalCrossingInProgress crossState;
  BOOL clusterSize_option;
  SAENumberOfParticipantsInCluster clusterSize;
  BOOL clusterRadius_option;
  SAEPersonalClusterRadius clusterRadius;
  BOOL eventResponderType_option;
  SAEPublicSafetyEventResponderWorkerType eventResponderType;
  BOOL activityType_option;
  SAEPublicSafetyAndRoadWorkerActivity activityType;
  BOOL activitySubType_option;
  SAEPublicSafetyDirectingTrafficSubType activitySubType;
  BOOL assistType_option;
  SAEPersonalAssistive assistType;
  BOOL sizing_option;
  SAEUserSizeAndBehaviour sizing;
  BOOL attachment_option;
  SAEAttachment attachment;
  BOOL attachmentRadius_option;
  SAEAttachmentRadius attachmentRadius;
  BOOL animalType_option;
  SAEAnimalType animalType;
  BOOL regional_option;
  SAEPersonalSafetyMessage_1 regional;
} SAEPersonalSafetyMessage;


extern const ASN1CType asn1_type_SAEPersonalSafetyMessage[];

typedef enum SAEEquipmentType {
  SAEEquipmentType_unknown,
  SAEEquipmentType_rsu,
  SAEEquipmentType_obu,
  SAEEquipmentType_vru,
} SAEEquipmentType;

extern const ASN1CType asn1_type_SAEEquipmentType[];

typedef enum SAEObjectType {
  SAEObjectType_unknown,
  SAEObjectType_vehicle,
  SAEObjectType_vru,
  SAEObjectType_animal,
} SAEObjectType;

extern const ASN1CType asn1_type_SAEObjectType[];

typedef int SAEClassificationConfidence;

extern const ASN1CType asn1_type_SAEClassificationConfidence[];

typedef int SAEObjectID;

extern const ASN1CType asn1_type_SAEObjectID[];

typedef int SAEMeasurementTimeOffset;

extern const ASN1CType asn1_type_SAEMeasurementTimeOffset[];

typedef int SAEObjectDistance;

extern const ASN1CType asn1_type_SAEObjectDistance[];

typedef struct SAEPositionOffsetXYZ {
  SAEObjectDistance offsetX;
  SAEObjectDistance offsetY;
  BOOL offsetZ_option;
  SAEObjectDistance offsetZ;
} SAEPositionOffsetXYZ;


extern const ASN1CType asn1_type_SAEPositionOffsetXYZ[];

typedef struct SAEDetectedObjectCommonData {
  SAEObjectType objType;
  SAEClassificationConfidence objTypeCfd;
  SAEObjectID objectID;
  SAEMeasurementTimeOffset measurementTime;
  SAETimeConfidence timeConfidence;
  SAEPositionOffsetXYZ pos;
  SAEPositionConfidenceSet posConfidence;
  SAESpeed speed;
  SAESpeedConfidence speedConfidence;
  BOOL speedZ_option;
  SAESpeed speedZ;
  BOOL speedConfidenceZ_option;
  SAESpeedConfidence speedConfidenceZ;
  SAEHeading heading;
  SAEHeadingConfidence headingConf;
  BOOL accel4way_option;
  SAEAccelerationSet4Way accel4way;
  BOOL accCfdX_option;
  SAEAccelerationConfidence accCfdX;
  BOOL accCfdY_option;
  SAEAccelerationConfidence accCfdY;
  BOOL accCfdZ_option;
  SAEAccelerationConfidence accCfdZ;
  BOOL accCfdYaw_option;
  SAEYawRateConfidence accCfdYaw;
} SAEDetectedObjectCommonData;


extern const ASN1CType asn1_type_SAEDetectedObjectCommonData[];

typedef int SAEPitchDetected;

extern const ASN1CType asn1_type_SAEPitchDetected[];

typedef int SAERollDetected;

extern const ASN1CType asn1_type_SAERollDetected[];

typedef int SAEYawDetected;

extern const ASN1CType asn1_type_SAEYawDetected[];

typedef struct SAEAttitude {
  SAEPitchDetected pitch;
  SAERollDetected roll;
  SAEYawDetected yaw;
} SAEAttitude;


extern const ASN1CType asn1_type_SAEAttitude[];

typedef struct SAEAttitudeConfidence {
  SAEHeadingConfidence pitchConfidence;
  SAEHeadingConfidence rollConfidence;
  SAEHeadingConfidence yawConfidence;
} SAEAttitudeConfidence;


extern const ASN1CType asn1_type_SAEAttitudeConfidence[];

typedef int SAEPitchRate;

extern const ASN1CType asn1_type_SAEPitchRate[];

typedef int SAERollRate;

extern const ASN1CType asn1_type_SAERollRate[];

typedef struct SAEAngularVelocity {
  SAEPitchRate pitchRate;
  SAERollRate rollRate;
} SAEAngularVelocity;


extern const ASN1CType asn1_type_SAEAngularVelocity[];

typedef enum SAEPitchRateConfidence {
  SAEPitchRateConfidence_unavailable,
  SAEPitchRateConfidence_degSec_100_00,
  SAEPitchRateConfidence_degSec_010_00,
  SAEPitchRateConfidence_degSec_005_00,
  SAEPitchRateConfidence_degSec_001_00,
  SAEPitchRateConfidence_degSec_000_10,
  SAEPitchRateConfidence_degSec_000_05,
  SAEPitchRateConfidence_degSec_000_01,
} SAEPitchRateConfidence;

extern const ASN1CType asn1_type_SAEPitchRateConfidence[];

typedef enum SAERollRateConfidence {
  SAERollRateConfidence_unavailable,
  SAERollRateConfidence_degSec_100_00,
  SAERollRateConfidence_degSec_010_00,
  SAERollRateConfidence_degSec_005_00,
  SAERollRateConfidence_degSec_001_00,
  SAERollRateConfidence_degSec_000_10,
  SAERollRateConfidence_degSec_000_05,
  SAERollRateConfidence_degSec_000_01,
} SAERollRateConfidence;

extern const ASN1CType asn1_type_SAERollRateConfidence[];

typedef struct SAEAngularVelocityConfidence {
  BOOL pitchRateConfidence_option;
  SAEPitchRateConfidence pitchRateConfidence;
  BOOL rollRateConfidence_option;
  SAERollRateConfidence rollRateConfidence;
} SAEAngularVelocityConfidence;


extern const ASN1CType asn1_type_SAEAngularVelocityConfidence[];

typedef enum SAESizeValueConfidence {
  SAESizeValueConfidence_unavailable,
  SAESizeValueConfidence_size_100_00,
  SAESizeValueConfidence_size_050_00,
  SAESizeValueConfidence_size_020_00,
  SAESizeValueConfidence_size_010_00,
  SAESizeValueConfidence_size_005_00,
  SAESizeValueConfidence_size_002_00,
  SAESizeValueConfidence_size_001_00,
  SAESizeValueConfidence_size_000_50,
  SAESizeValueConfidence_size_000_20,
  SAESizeValueConfidence_size_000_10,
  SAESizeValueConfidence_size_000_05,
  SAESizeValueConfidence_size_000_02,
  SAESizeValueConfidence_size_000_01,
} SAESizeValueConfidence;

extern const ASN1CType asn1_type_SAESizeValueConfidence[];

typedef struct SAEVehicleSizeConfidence {
  SAESizeValueConfidence vehicleWidthConfidence;
  SAESizeValueConfidence vehicleLengthConfidence;
  BOOL vehicleHeightConfidence_option;
  SAESizeValueConfidence vehicleHeightConfidence;
} SAEVehicleSizeConfidence;


extern const ASN1CType asn1_type_SAEVehicleSizeConfidence[];

typedef struct SAEDetectedVehicleData {
  BOOL lights_option;
  SAEExteriorLights lights;
  BOOL vehAttitude_option;
  SAEAttitude vehAttitude;
  BOOL vehAttitudeConfidence_option;
  SAEAttitudeConfidence vehAttitudeConfidence;
  BOOL vehAngVel_option;
  SAEAngularVelocity vehAngVel;
  BOOL vehAngVelConfidence_option;
  SAEAngularVelocityConfidence vehAngVelConfidence;
  BOOL size_option;
  SAEVehicleSize size;
  BOOL height_option;
  SAEVehicleHeight height;
  BOOL vehicleSizeConfidence_option;
  SAEVehicleSizeConfidence vehicleSizeConfidence;
  BOOL vehicleClass_option;
  SAEBasicVehicleClass vehicleClass;
  BOOL classConf_option;
  SAEClassificationConfidence classConf;
} SAEDetectedVehicleData;


extern const ASN1CType asn1_type_SAEDetectedVehicleData[];

typedef struct SAEDetectedVRUData {
  BOOL basicType_option;
  SAEPersonalDeviceUserType basicType;
  BOOL propulsion_option;
  SAEPropelledInformation propulsion;
  BOOL attachment_option;
  SAEAttachment attachment;
  BOOL radius_option;
  SAEAttachmentRadius radius;
} SAEDetectedVRUData;


extern const ASN1CType asn1_type_SAEDetectedVRUData[];

typedef int SAESizeValue;

extern const ASN1CType asn1_type_SAESizeValue[];

typedef struct SAEObstacleSize {
  SAESizeValue width;
  SAESizeValue length;
  BOOL height_option;
  SAESizeValue height;
} SAEObstacleSize;


extern const ASN1CType asn1_type_SAEObstacleSize[];

typedef struct SAEObstacleSizeConfidence {
  SAESizeValueConfidence widthConfidence;
  SAESizeValueConfidence lengthConfidence;
  BOOL heightConfidence_option;
  SAESizeValueConfidence heightConfidence;
} SAEObstacleSizeConfidence;


extern const ASN1CType asn1_type_SAEObstacleSizeConfidence[];

typedef struct SAEDetectedObstacleData {
  SAEObstacleSize obstSize;
  SAEObstacleSizeConfidence obstSizeConfidence;
} SAEDetectedObstacleData;


extern const ASN1CType asn1_type_SAEDetectedObstacleData[];

typedef enum {
  SAEDetectedObjectOptionalData_detVeh,
  SAEDetectedObjectOptionalData_detVRU,
  SAEDetectedObjectOptionalData_detObst,
} SAEDetectedObjectOptionalData_choice;

typedef struct SAEDetectedObjectOptionalData {
  SAEDetectedObjectOptionalData_choice choice;
  union {
    SAEDetectedVehicleData detVeh;
    SAEDetectedVRUData detVRU;
    SAEDetectedObstacleData detObst;
  } u;
} SAEDetectedObjectOptionalData;

extern const ASN1CType asn1_type_SAEDetectedObjectOptionalData[];

typedef struct SAEDetectedObjectData {
  SAEDetectedObjectCommonData detObjCommon;
  BOOL detObjOptData_option;
  SAEDetectedObjectOptionalData detObjOptData;
} SAEDetectedObjectData;


extern const ASN1CType asn1_type_SAEDetectedObjectData[];

typedef struct SAEDetectedObjectList {
  SAEDetectedObjectData *tab;
  size_t count;
} SAEDetectedObjectList;

extern const ASN1CType asn1_type_SAEDetectedObjectList[];

typedef struct SAESensorDataSharingMessage {
  SAEMsgCount msgCnt;
  SAETemporaryID sourceID;
  SAEEquipmentType equipmentType;
  SAEDDateTime sDSMTimeStamp;
  SAEPosition3D refPos;
  SAEPositionalAccuracy refPosXYConf;
  BOOL refPosElConf_option;
  SAEElevationConfidence refPosElConf;
  SAEDetectedObjectList objects;
} SAESensorDataSharingMessage;


extern const ASN1CType asn1_type_SAESensorDataSharingMessage[];

typedef struct SAEHeader {
  BOOL year_option;
  SAEDYear year;
  BOOL timeStamp_option;
  SAEMinuteOfTheYear timeStamp;
  BOOL secMark_option;
  SAEDSecond secMark;
  BOOL msgIssueRevision_option;
  SAEMsgCount msgIssueRevision;
} SAEHeader;


extern const ASN1CType asn1_type_SAEHeader[];

typedef struct SAERegionalExtension_16 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_16;


extern const ASN1CType asn1_type_SAERegionalExtension_16[];

typedef struct SAETestMessage00 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_16 regional;
} SAETestMessage00;


extern const ASN1CType asn1_type_SAETestMessage00[];

typedef struct SAERegionalExtension_17 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_17;


extern const ASN1CType asn1_type_SAERegionalExtension_17[];

typedef struct SAETestMessage01 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_17 regional;
} SAETestMessage01;


extern const ASN1CType asn1_type_SAETestMessage01[];

typedef struct SAERegionalExtension_18 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_18;


extern const ASN1CType asn1_type_SAERegionalExtension_18[];

typedef struct SAETestMessage02 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_18 regional;
} SAETestMessage02;


extern const ASN1CType asn1_type_SAETestMessage02[];

typedef struct SAERegionalExtension_19 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_19;


extern const ASN1CType asn1_type_SAERegionalExtension_19[];

typedef struct SAETestMessage03 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_19 regional;
} SAETestMessage03;


extern const ASN1CType asn1_type_SAETestMessage03[];

typedef struct SAERegionalExtension_20 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_20;


extern const ASN1CType asn1_type_SAERegionalExtension_20[];

typedef struct SAETestMessage04 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_20 regional;
} SAETestMessage04;


extern const ASN1CType asn1_type_SAETestMessage04[];

typedef struct SAERegionalExtension_21 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_21;


extern const ASN1CType asn1_type_SAERegionalExtension_21[];

typedef struct SAETestMessage05 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_21 regional;
} SAETestMessage05;


extern const ASN1CType asn1_type_SAETestMessage05[];

typedef struct SAERegionalExtension_22 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_22;


extern const ASN1CType asn1_type_SAERegionalExtension_22[];

typedef struct SAETestMessage06 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_22 regional;
} SAETestMessage06;


extern const ASN1CType asn1_type_SAETestMessage06[];

typedef struct SAERegionalExtension_23 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_23;


extern const ASN1CType asn1_type_SAERegionalExtension_23[];

typedef struct SAETestMessage07 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_23 regional;
} SAETestMessage07;


extern const ASN1CType asn1_type_SAETestMessage07[];

typedef struct SAERegionalExtension_24 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_24;


extern const ASN1CType asn1_type_SAERegionalExtension_24[];

typedef struct SAETestMessage08 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_24 regional;
} SAETestMessage08;


extern const ASN1CType asn1_type_SAETestMessage08[];

typedef struct SAERegionalExtension_25 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_25;


extern const ASN1CType asn1_type_SAERegionalExtension_25[];

typedef struct SAETestMessage09 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_25 regional;
} SAETestMessage09;


extern const ASN1CType asn1_type_SAETestMessage09[];

typedef struct SAERegionalExtension_26 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_26;


extern const ASN1CType asn1_type_SAERegionalExtension_26[];

typedef struct SAETestMessage10 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_26 regional;
} SAETestMessage10;


extern const ASN1CType asn1_type_SAETestMessage10[];

typedef struct SAERegionalExtension_27 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_27;


extern const ASN1CType asn1_type_SAERegionalExtension_27[];

typedef struct SAETestMessage11 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_27 regional;
} SAETestMessage11;


extern const ASN1CType asn1_type_SAETestMessage11[];

typedef struct SAERegionalExtension_28 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_28;


extern const ASN1CType asn1_type_SAERegionalExtension_28[];

typedef struct SAETestMessage12 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_28 regional;
} SAETestMessage12;


extern const ASN1CType asn1_type_SAETestMessage12[];

typedef struct SAERegionalExtension_29 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_29;


extern const ASN1CType asn1_type_SAERegionalExtension_29[];

typedef struct SAETestMessage13 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_29 regional;
} SAETestMessage13;


extern const ASN1CType asn1_type_SAETestMessage13[];

typedef struct SAERegionalExtension_30 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_30;


extern const ASN1CType asn1_type_SAERegionalExtension_30[];

typedef struct SAETestMessage14 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_30 regional;
} SAETestMessage14;


extern const ASN1CType asn1_type_SAETestMessage14[];

typedef struct SAERegionalExtension_31 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_31;


extern const ASN1CType asn1_type_SAERegionalExtension_31[];

typedef struct SAETestMessage15 {
  BOOL header_option;
  SAEHeader header;
  BOOL regional_option;
  SAERegionalExtension_31 regional;
} SAETestMessage15;


extern const ASN1CType asn1_type_SAETestMessage15[];

typedef struct SAEREG_EXT_ID_AND_TYPE { /* object class definition */
  ASN1CType id;
  ASN1CType Type;
} SAEREG_EXT_ID_AND_TYPE;


extern const ASN1CType asn1_type_SAEREG_EXT_ID_AND_TYPE[];

typedef struct SAEPARTII_EXT_ID_AND_TYPE { /* object class definition */
  ASN1CType id;
  ASN1CType Type;
} SAEPARTII_EXT_ID_AND_TYPE;


extern const ASN1CType asn1_type_SAEPARTII_EXT_ID_AND_TYPE[];

typedef struct SAEEventDescription_1 {
  SAEITIScodes *tab;
  size_t count;
} SAEEventDescription_1;

extern const ASN1CType asn1_type_SAEEventDescription_1[];

typedef struct SAERegionalExtension_35 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_35;


extern const ASN1CType asn1_type_SAERegionalExtension_35[];

typedef struct SAEEventDescription_2 {
  SAERegionalExtension_35 *tab;
  size_t count;
} SAEEventDescription_2;

extern const ASN1CType asn1_type_SAEEventDescription_2[];

typedef struct SAEEventDescription {
  SAEITIScodes typeEvent;
  BOOL description_option;
  SAEEventDescription_1 description;
  BOOL priority_option;
  SAEPriority priority;
  BOOL heading_option;
  SAEHeadingSlice heading;
  BOOL extent_option;
  SAEExtent extent;
  BOOL regional_option;
  SAEEventDescription_2 regional;
} SAEEventDescription;


extern const ASN1CType asn1_type_SAEEventDescription[];

typedef BOOL SAEPivotingAllowed;

extern const ASN1CType asn1_type_SAEPivotingAllowed[];

typedef struct SAEPivotPointDescription {
  SAEOffset_B11 pivotOffset;
  SAEAngle pivotAngle;
  SAEPivotingAllowed pivots;
} SAEPivotPointDescription;


extern const ASN1CType asn1_type_SAEPivotPointDescription[];

typedef BOOL SAEIsDolly;

extern const ASN1CType asn1_type_SAEIsDolly[];

typedef int SAETrailerMass;

extern const ASN1CType asn1_type_SAETrailerMass[];

typedef int SAEVertOffset_B07;

extern const ASN1CType asn1_type_SAEVertOffset_B07[];

typedef struct SAETrailerHistoryPoint {
  SAEAngle pivotAngle;
  SAETimeOffset timeOffset;
  SAENode_XY_24b positionOffset;
  BOOL elevationOffset_option;
  SAEVertOffset_B07 elevationOffset;
  BOOL heading_option;
  SAECoarseHeading heading;
} SAETrailerHistoryPoint;


extern const ASN1CType asn1_type_SAETrailerHistoryPoint[];

typedef struct SAETrailerHistoryPointList {
  SAETrailerHistoryPoint *tab;
  size_t count;
} SAETrailerHistoryPointList;

extern const ASN1CType asn1_type_SAETrailerHistoryPointList[];

typedef struct SAETrailerUnitDescription {
  SAEIsDolly isDolly;
  SAEVehicleWidth width;
  SAEVehicleLength length;
  BOOL height_option;
  SAEVehicleHeight height;
  BOOL mass_option;
  SAETrailerMass mass;
  BOOL bumperHeights_option;
  SAEBumperHeights bumperHeights;
  BOOL centerOfGravity_option;
  SAEVehicleHeight centerOfGravity;
  SAEPivotPointDescription frontPivot;
  BOOL rearPivot_option;
  SAEPivotPointDescription rearPivot;
  BOOL rearWheelOffset_option;
  SAEOffset_B12 rearWheelOffset;
  SAENode_XY_24b positionOffset;
  BOOL elevationOffset_option;
  SAEVertOffset_B07 elevationOffset;
  BOOL crumbData_option;
  SAETrailerHistoryPointList crumbData;
} SAETrailerUnitDescription;


extern const ASN1CType asn1_type_SAETrailerUnitDescription[];

typedef struct SAETrailerUnitDescriptionList {
  SAETrailerUnitDescription *tab;
  size_t count;
} SAETrailerUnitDescriptionList;

extern const ASN1CType asn1_type_SAETrailerUnitDescriptionList[];

typedef struct SAETrailerData {
  SAESSPindex sspRights;
  SAEPivotPointDescription connection;
  SAETrailerUnitDescriptionList units;
} SAETrailerData;


extern const ASN1CType asn1_type_SAETrailerData[];

typedef struct SAESpecialVehicleExtensions {
  BOOL vehicleAlerts_option;
  SAEEmergencyDetails vehicleAlerts;
  BOOL description_option;
  SAEEventDescription description;
  BOOL trailers_option;
  SAETrailerData trailers;
} SAESpecialVehicleExtensions;


extern const ASN1CType asn1_type_SAESpecialVehicleExtensions[];

typedef struct SAEVehicleData {
  BOOL height_option;
  SAEVehicleHeight height;
  BOOL bumpers_option;
  SAEBumperHeights bumpers;
  BOOL mass_option;
  SAEVehicleMass mass;
  BOOL trailerWeight_option;
  SAETrailerWeight trailerWeight;
} SAEVehicleData;


extern const ASN1CType asn1_type_SAEVehicleData[];

typedef struct SAEWeatherReport {
  SAEEssPrecipYesNo isRaining;
  BOOL rainRate_option;
  SAEEssPrecipRate rainRate;
  BOOL precipSituation_option;
  SAEEssPrecipSituation precipSituation;
  BOOL solarRadiation_option;
  SAEEssSolarRadiation solarRadiation;
  BOOL friction_option;
  SAEEssMobileFriction friction;
  BOOL roadFriction_option;
  SAECoefficientOfFriction roadFriction;
} SAEWeatherReport;


extern const ASN1CType asn1_type_SAEWeatherReport[];

typedef struct SAEWeatherProbe {
  BOOL airTemp_option;
  SAEAmbientAirTemperature airTemp;
  BOOL airPressure_option;
  SAEAmbientAirPressure airPressure;
  BOOL rainRates_option;
  SAEWiperSet rainRates;
} SAEWeatherProbe;


extern const ASN1CType asn1_type_SAEWeatherProbe[];

typedef SAEAngle SAEObstacleDirection;

extern const ASN1CType asn1_type_SAEObstacleDirection[];

typedef int SAEITIScodes_2;

extern const ASN1CType asn1_type_SAEITIScodes_2[];

typedef enum SAEGenericLocations {
  SAEGenericLocations_on_bridges,
  SAEGenericLocations_in_tunnels,
  SAEGenericLocations_entering_or_leaving_tunnels,
  SAEGenericLocations_on_ramps,
  SAEGenericLocations_in_road_construction_area,
  SAEGenericLocations_around_a_curve,
  SAEGenericLocations_on_curve,
  SAEGenericLocations_on_tracks,
  SAEGenericLocations_in_street,
  SAEGenericLocations_shoulder,
  SAEGenericLocations_on_minor_roads,
  SAEGenericLocations_in_the_opposing_lanes,
  SAEGenericLocations_adjacent_to_roadway,
  SAEGenericLocations_across_tracks,
  SAEGenericLocations_on_bend,
  SAEGenericLocations_intersection,
  SAEGenericLocations_entire_intersection,
  SAEGenericLocations_in_the_median,
  SAEGenericLocations_moved_to_side_of_road,
  SAEGenericLocations_moved_to_shoulder,
  SAEGenericLocations_on_the_roadway,
  SAEGenericLocations_dip,
  SAEGenericLocations_traffic_circle,
  SAEGenericLocations_crossover,
  SAEGenericLocations_cross_road,
  SAEGenericLocations_side_road,
  SAEGenericLocations_to,
  SAEGenericLocations_by,
  SAEGenericLocations_through,
  SAEGenericLocations_area_of,
  SAEGenericLocations_under,
  SAEGenericLocations_over,
  SAEGenericLocations_from,
  SAEGenericLocations_approaching,
  SAEGenericLocations_entering_at,
  SAEGenericLocations_exiting_at,
  SAEGenericLocations_in_shaded_areas,
  SAEGenericLocations_in_low_lying_areas,
  SAEGenericLocations_in_the_downtown_area,
  SAEGenericLocations_in_the_inner_city_area,
  SAEGenericLocations_in_parts,
  SAEGenericLocations_in_some_places,
  SAEGenericLocations_in_the_ditch,
  SAEGenericLocations_in_the_valley,
  SAEGenericLocations_on_hill_top,
  SAEGenericLocations_near_the_foothills,
  SAEGenericLocations_at_high_altitudes,
  SAEGenericLocations_near_the_lake,
  SAEGenericLocations_near_the_shore,
  SAEGenericLocations_nearby_basin,
  SAEGenericLocations_over_the_crest_of_a_hill,
  SAEGenericLocations_other_than_on_the_roadway,
  SAEGenericLocations_near_the_beach,
  SAEGenericLocations_near_beach_access_point,
  SAEGenericLocations_mountain_pass,
  SAEGenericLocations_lower_level,
  SAEGenericLocations_upper_level,
  SAEGenericLocations_airport,
  SAEGenericLocations_concourse,
  SAEGenericLocations_gate,
  SAEGenericLocations_baggage_claim,
  SAEGenericLocations_customs_point,
  SAEGenericLocations_reservation_center,
  SAEGenericLocations_station,
  SAEGenericLocations_platform,
  SAEGenericLocations_dock,
  SAEGenericLocations_depot,
  SAEGenericLocations_ev_charging_point,
  SAEGenericLocations_information_welcome_point,
  SAEGenericLocations_at_rest_area,
  SAEGenericLocations_at_service_area,
  SAEGenericLocations_at_weigh_station,
  SAEGenericLocations_roadside_park,
  SAEGenericLocations_picnic_areas,
  SAEGenericLocations_rest_area,
  SAEGenericLocations_service_stations,
  SAEGenericLocations_toilets,
  SAEGenericLocations_bus_stop,
  SAEGenericLocations_park_and_ride_lot,
  SAEGenericLocations_on_the_right,
  SAEGenericLocations_on_the_left,
  SAEGenericLocations_in_the_center,
  SAEGenericLocations_in_the_opposite_direction,
  SAEGenericLocations_cross_traffic,
  SAEGenericLocations_northbound_traffic,
  SAEGenericLocations_eastbound_traffic,
  SAEGenericLocations_southbound_traffic,
  SAEGenericLocations_westbound_traffic,
  SAEGenericLocations_north,
  SAEGenericLocations_south,
  SAEGenericLocations_east,
  SAEGenericLocations_west,
  SAEGenericLocations_northeast,
  SAEGenericLocations_northwest,
  SAEGenericLocations_southeast,
  SAEGenericLocations_southwest,
} SAEGenericLocations;

extern const ASN1CType asn1_type_SAEGenericLocations[];

typedef struct SAEObstacleDetection {
  SAEObstacleDistance obDist;
  SAEObstacleDirection obDirect;
  BOOL description_option;
  SAEITIScodes_2 description;
  BOOL locationDetails_option;
  SAEGenericLocations locationDetails;
  SAEDDateTime dateTime;
  BOOL vertEvent_option;
  SAEVerticalAccelerationThreshold vertEvent;
} SAEObstacleDetection;


extern const ASN1CType asn1_type_SAEObstacleDetection[];

typedef int SAEITIScodes_1;

extern const ASN1CType asn1_type_SAEITIScodes_1[];

typedef struct SAEDisabledVehicle {
  SAEITIScodes_1 statusDetails;
  BOOL locationDetails_option;
  SAEGenericLocations locationDetails;
} SAEDisabledVehicle;


extern const ASN1CType asn1_type_SAEDisabledVehicle[];

typedef SAEGrossSpeed SAESpeedProfileMeasurement;

#define asn1_type_SAESpeedProfileMeasurement asn1_type_SAEGrossSpeed

typedef struct SAESpeedProfileMeasurementList {
  SAESpeedProfileMeasurement *tab;
  size_t count;
} SAESpeedProfileMeasurementList;

extern const ASN1CType asn1_type_SAESpeedProfileMeasurementList[];

typedef struct SAESpeedProfile {
  SAESpeedProfileMeasurementList speedReports;
} SAESpeedProfile;


extern const ASN1CType asn1_type_SAESpeedProfile[];

typedef struct SAERTCMPackage {
  BOOL rtcmHeader_option;
  SAERTCMheader rtcmHeader;
  SAERTCMmessageList msgs;
} SAERTCMPackage;


extern const ASN1CType asn1_type_SAERTCMPackage[];

typedef struct SAERegionalExtension_59 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_59;


extern const ASN1CType asn1_type_SAERegionalExtension_59[];

typedef struct SAESupplementalVehicleExtensions_1 {
  SAERegionalExtension_59 *tab;
  size_t count;
} SAESupplementalVehicleExtensions_1;

extern const ASN1CType asn1_type_SAESupplementalVehicleExtensions_1[];

typedef struct SAESupplementalVehicleExtensions {
  BOOL classification_option;
  SAEBasicVehicleClass classification;
  BOOL classDetails_option;
  SAEVehicleClassification classDetails;
  BOOL vehicleData_option;
  SAEVehicleData vehicleData;
  BOOL weatherReport_option;
  SAEWeatherReport weatherReport;
  BOOL weatherProbe_option;
  SAEWeatherProbe weatherProbe;
  BOOL obstacle_option;
  SAEObstacleDetection obstacle;
  BOOL status_option;
  SAEDisabledVehicle status;
  BOOL speedProfile_option;
  SAESpeedProfile speedProfile;
  BOOL theRTCM_option;
  SAERTCMPackage theRTCM;
  BOOL regional_option;
  SAESupplementalVehicleExtensions_1 regional;
} SAESupplementalVehicleExtensions;


extern const ASN1CType asn1_type_SAESupplementalVehicleExtensions[];

typedef struct SAEDDate {
  SAEDYear year;
  SAEDMonth month;
  SAEDDay day;
} SAEDDate;


extern const ASN1CType asn1_type_SAEDDate[];

typedef struct SAEDFullTime {
  SAEDYear year;
  SAEDMonth month;
  SAEDDay day;
  SAEDHour hour;
  SAEDMinute minute;
} SAEDFullTime;


extern const ASN1CType asn1_type_SAEDFullTime[];

typedef struct SAEDMonthDay {
  SAEDMonth month;
  SAEDDay day;
} SAEDMonthDay;


extern const ASN1CType asn1_type_SAEDMonthDay[];

typedef struct SAEDTime {
  SAEDHour hour;
  SAEDMinute minute;
  SAEDSecond second;
  BOOL offset_option;
  SAEDOffset offset;
} SAEDTime;


extern const ASN1CType asn1_type_SAEDTime[];

typedef struct SAEDYearMonth {
  SAEDYear year;
  SAEDMonth month;
} SAEDYearMonth;


extern const ASN1CType asn1_type_SAEDYearMonth[];

typedef int SAEVertOffset_B08;

extern const ASN1CType asn1_type_SAEVertOffset_B08[];

typedef int SAEVertOffset_B09;

extern const ASN1CType asn1_type_SAEVertOffset_B09[];

typedef int SAEVertOffset_B10;

extern const ASN1CType asn1_type_SAEVertOffset_B10[];

typedef int SAEVertOffset_B11;

extern const ASN1CType asn1_type_SAEVertOffset_B11[];

typedef struct SAERegionalExtension_61 {
  SAERegionId regionId;
  ASN1OpenType regExtValue;
} SAERegionalExtension_61;


extern const ASN1CType asn1_type_SAERegionalExtension_61[];

typedef enum {
  SAEVerticalOffset_offset1,
  SAEVerticalOffset_offset2,
  SAEVerticalOffset_offset3,
  SAEVerticalOffset_offset4,
  SAEVerticalOffset_offset5,
  SAEVerticalOffset_offset6,
  SAEVerticalOffset_elevation,
  SAEVerticalOffset_regional,
} SAEVerticalOffset_choice;

typedef struct SAEVerticalOffset {
  SAEVerticalOffset_choice choice;
  union {
    SAEVertOffset_B07 offset1;
    SAEVertOffset_B08 offset2;
    SAEVertOffset_B09 offset3;
    SAEVertOffset_B10 offset4;
    SAEVertOffset_B11 offset5;
    SAEVertOffset_B12 offset6;
    SAEElevation elevation;
    SAERegionalExtension_61 regional;
  } u;
} SAEVerticalOffset;

extern const ASN1CType asn1_type_SAEVerticalOffset[];

typedef ASN1String SAECodeWord;

extern const ASN1CType asn1_type_SAECodeWord[];

typedef int SAECount;

extern const ASN1CType asn1_type_SAECount[];

typedef int SAEDuration;

extern const ASN1CType asn1_type_SAEDuration[];

typedef enum SAELocation_quality {
  SAELocation_quality_loc_qual_bt1m,
  SAELocation_quality_loc_qual_bt5m,
  SAELocation_quality_loc_qual_bt12m,
  SAELocation_quality_loc_qual_bt50m,
  SAELocation_quality_loc_qual_bt125m,
  SAELocation_quality_loc_qual_bt500m,
  SAELocation_quality_loc_qual_bt1250m,
  SAELocation_quality_loc_qual_unknown,
} SAELocation_quality;

extern const ASN1CType asn1_type_SAELocation_quality[];

typedef enum SAELocation_tech {
  SAELocation_tech_loc_tech_unknown,
  SAELocation_tech_loc_tech_GNSS,
  SAELocation_tech_loc_tech_DGPS,
  SAELocation_tech_loc_tech_RTK,
  SAELocation_tech_loc_tech_PPP,
  SAELocation_tech_loc_tech_drGPS,
  SAELocation_tech_loc_tech_drDGPS,
  SAELocation_tech_loc_tech_dr,
  SAELocation_tech_loc_tech_nav,
  SAELocation_tech_loc_tech_fault,
} SAELocation_tech;

extern const ASN1CType asn1_type_SAELocation_tech[];

typedef ASN1String SAEMessageBLOB;

extern const ASN1CType asn1_type_SAEMessageBLOB[];

typedef ASN1String SAEPayloadData;

extern const ASN1CType asn1_type_SAEPayloadData[];

typedef ASN1String SAESignalReqScheme;

extern const ASN1CType asn1_type_SAESignalReqScheme[];

typedef ASN1BitString SAETransitStatus;

extern const ASN1CType asn1_type_SAETransitStatus[];

typedef ASN1String SAEURL_Link;

extern const ASN1CType asn1_type_SAEURL_Link[];

typedef struct SAEVehicleToLanePosition {
  SAEStationID stationID;
  SAELaneID laneID;
} SAEVehicleToLanePosition;


extern const ASN1CType asn1_type_SAEVehicleToLanePosition[];

typedef struct SAEVehicleToLanePositionList {
  SAEVehicleToLanePosition *tab;
  size_t count;
} SAEVehicleToLanePositionList;

extern const ASN1CType asn1_type_SAEVehicleToLanePositionList[];

typedef struct SAEConnectionManeuverAssist_addGrpC {
  SAEVehicleToLanePositionList vehicleToLanePositions;
  BOOL rsuDistanceFromAnchor_option;
  SAENodeOffsetPointXY rsuDistanceFromAnchor;
} SAEConnectionManeuverAssist_addGrpC;


extern const ASN1CType asn1_type_SAEConnectionManeuverAssist_addGrpC[];

typedef struct SAEPrioritizationResponse {
  SAEStationID stationID;
  SAEPrioritizationResponseStatus priorState;
  SAESignalGroupID signalGroup;
} SAEPrioritizationResponse;


extern const ASN1CType asn1_type_SAEPrioritizationResponse[];

typedef struct SAEPrioritizationResponseList {
  SAEPrioritizationResponse *tab;
  size_t count;
} SAEPrioritizationResponseList;

extern const ASN1CType asn1_type_SAEPrioritizationResponseList[];

typedef struct SAEIntersectionState_addGrpC {
  BOOL activePrioritizations_option;
  SAEPrioritizationResponseList activePrioritizations;
} SAEIntersectionState_addGrpC;


extern const ASN1CType asn1_type_SAEIntersectionState_addGrpC[];

typedef struct SAELaneDataAttribute_addGrpB {
  uint8_t dummy_field;
} SAELaneDataAttribute_addGrpB;


extern const ASN1CType asn1_type_SAELaneDataAttribute_addGrpB[];

typedef int SAETimeRemaining;

extern const ASN1CType asn1_type_SAETimeRemaining[];

typedef int SAEMinTimetoChange;

extern const ASN1CType asn1_type_SAEMinTimetoChange[];

typedef int SAEMaxTimetoChange;

extern const ASN1CType asn1_type_SAEMaxTimetoChange[];

typedef struct SAEMovementEvent_addGrpB {
  BOOL startTime_option;
  SAETimeRemaining startTime;
  SAEMinTimetoChange minEndTime;
  BOOL maxEndTime_option;
  SAEMaxTimetoChange maxEndTime;
  BOOL likelyTime_option;
  SAETimeRemaining likelyTime;
  BOOL confidence_option;
  SAETimeIntervalConfidence confidence;
  BOOL nextTime_option;
  SAETimeRemaining nextTime;
} SAEMovementEvent_addGrpB;


extern const ASN1CType asn1_type_SAEMovementEvent_addGrpB[];

typedef int SAELongitudeDMS;

extern const ASN1CType asn1_type_SAELongitudeDMS[];

typedef int SAELatitudeDMS;

extern const ASN1CType asn1_type_SAELatitudeDMS[];

typedef struct SAENode_LLdms_48b {
  SAELongitudeDMS lon;
  SAELatitudeDMS lat;
} SAENode_LLdms_48b;


extern const ASN1CType asn1_type_SAENode_LLdms_48b[];

typedef int SAEDegreesLong;

extern const ASN1CType asn1_type_SAEDegreesLong[];

typedef int SAEMinutesAngle;

extern const ASN1CType asn1_type_SAEMinutesAngle[];

typedef int SAESecondsAngle;

extern const ASN1CType asn1_type_SAESecondsAngle[];

typedef struct SAELongitudeDMS2 {
  SAEDegreesLong d;
  SAEMinutesAngle m;
  SAESecondsAngle s;
} SAELongitudeDMS2;


extern const ASN1CType asn1_type_SAELongitudeDMS2[];

typedef int SAEDegreesLat;

extern const ASN1CType asn1_type_SAEDegreesLat[];

typedef struct SAELatitudeDMS2 {
  SAEDegreesLat d;
  SAEMinutesAngle m;
  SAESecondsAngle s;
} SAELatitudeDMS2;


extern const ASN1CType asn1_type_SAELatitudeDMS2[];

typedef struct SAENode_LLdms_80b {
  SAELongitudeDMS2 lon;
  SAELatitudeDMS2 lat;
} SAENode_LLdms_80b;


extern const ASN1CType asn1_type_SAENode_LLdms_80b[];

typedef enum {
  SAENodeOffsetPointXY_addGrpB_posA,
  SAENodeOffsetPointXY_addGrpB_posB,
} SAENodeOffsetPointXY_addGrpB_choice;

typedef struct SAENodeOffsetPointXY_addGrpB {
  SAENodeOffsetPointXY_addGrpB_choice choice;
  union {
    SAENode_LLdms_48b posA;
    SAENode_LLdms_80b posB;
  } u;
} SAENodeOffsetPointXY_addGrpB;

extern const ASN1CType asn1_type_SAENodeOffsetPointXY_addGrpB[];

typedef int SAEAddGrpB_Elevation;

extern const ASN1CType asn1_type_SAEAddGrpB_Elevation[];

typedef struct SAEPosition3D_addGrpB {
  SAELatitudeDMS2 latitude;
  SAELongitudeDMS2 longitude;
  SAEAddGrpB_Elevation elevation;
} SAEPosition3D_addGrpB;


extern const ASN1CType asn1_type_SAEPosition3D_addGrpB[];

typedef int SAEAltitudeValue;

extern const ASN1CType asn1_type_SAEAltitudeValue[];

typedef enum SAEAltitudeConfidence {
  SAEAltitudeConfidence_alt_000_01,
  SAEAltitudeConfidence_alt_000_02,
  SAEAltitudeConfidence_alt_000_05,
  SAEAltitudeConfidence_alt_000_10,
  SAEAltitudeConfidence_alt_000_20,
  SAEAltitudeConfidence_alt_000_50,
  SAEAltitudeConfidence_alt_001_00,
  SAEAltitudeConfidence_alt_002_00,
  SAEAltitudeConfidence_alt_005_00,
  SAEAltitudeConfidence_alt_010_00,
  SAEAltitudeConfidence_alt_020_00,
  SAEAltitudeConfidence_alt_050_00,
  SAEAltitudeConfidence_alt_100_00,
  SAEAltitudeConfidence_alt_200_00,
  SAEAltitudeConfidence_outOfRange,
  SAEAltitudeConfidence_unavailable,
} SAEAltitudeConfidence;

extern const ASN1CType asn1_type_SAEAltitudeConfidence[];

typedef struct SAEAltitude {
  SAEAltitudeValue value;
  SAEAltitudeConfidence confidence;
} SAEAltitude;


extern const ASN1CType asn1_type_SAEAltitude[];

typedef struct SAEPosition3D_addGrpC {
  SAEAltitude altitude;
} SAEPosition3D_addGrpC;


extern const ASN1CType asn1_type_SAEPosition3D_addGrpC[];

typedef enum SAEEmissionType {
  SAEEmissionType_typeA,
  SAEEmissionType_typeB,
  SAEEmissionType_typeC,
  SAEEmissionType_typeD,
  SAEEmissionType_typeE,
} SAEEmissionType;

extern const ASN1CType asn1_type_SAEEmissionType[];

typedef struct SAERestrictionUserType_addGrpC {
  BOOL emission_option;
  SAEEmissionType emission;
} SAERestrictionUserType_addGrpC;


extern const ASN1CType asn1_type_SAERestrictionUserType_addGrpC[];

typedef struct SAESignalHeadLocation {
  SAENodeOffsetPointXY node;
  SAESignalGroupID signalGroupID;
} SAESignalHeadLocation;


extern const ASN1CType asn1_type_SAESignalHeadLocation[];

typedef struct SAESignalHeadLocationList {
  SAESignalHeadLocation *tab;
  size_t count;
} SAESignalHeadLocationList;

extern const ASN1CType asn1_type_SAESignalHeadLocationList[];

typedef struct SAEMapData_addGrpC {
  BOOL signalHeadLocations_option;
  SAESignalHeadLocationList signalHeadLocations;
} SAEMapData_addGrpC;


extern const ASN1CType asn1_type_SAEMapData_addGrpC[];

typedef int SAEAddGrpB_Angle;

extern const ASN1CType asn1_type_SAEAddGrpB_Angle[];

typedef int SAEDay;

extern const ASN1CType asn1_type_SAEDay[];

typedef enum SAEDayOfWeek {
  SAEDayOfWeek_unknown,
  SAEDayOfWeek_monday,
  SAEDayOfWeek_tuesday,
  SAEDayOfWeek_wednesday,
  SAEDayOfWeek_thursday,
  SAEDayOfWeek_friday,
  SAEDayOfWeek_saturday,
  SAEDayOfWeek_sunday,
} SAEDayOfWeek;

extern const ASN1CType asn1_type_SAEDayOfWeek[];

typedef enum SAEHoliday {
  SAEHoliday_weekday,
  SAEHoliday_holiday,
} SAEHoliday;

extern const ASN1CType asn1_type_SAEHoliday[];

typedef int SAEHour;

extern const ASN1CType asn1_type_SAEHour[];

typedef int SAEMinute;

extern const ASN1CType asn1_type_SAEMinute[];

typedef int SAEMonth;

extern const ASN1CType asn1_type_SAEMonth[];

typedef int SAEAddGrpB_MsgCount;

extern const ASN1CType asn1_type_SAEAddGrpB_MsgCount[];

typedef int SAESecond;

extern const ASN1CType asn1_type_SAESecond[];

typedef enum SAESummerTime {
  SAESummerTime_notInSummerTime,
  SAESummerTime_inSummerTime,
} SAESummerTime;

extern const ASN1CType asn1_type_SAESummerTime[];

typedef int SAETenthSecond;

extern const ASN1CType asn1_type_SAETenthSecond[];

typedef int SAEYear;

extern const ASN1CType asn1_type_SAEYear[];

typedef struct SAEAddGrpB_TimeMark {
  SAEYear year;
  SAEMonth month;
  SAEDay day;
  SAESummerTime summerTime;
  SAEHoliday holiday;
  SAEDayOfWeek dayofWeek;
  SAEHour hour;
  SAEMinute minute;
  SAESecond second;
  SAETenthSecond tenthSecond;
} SAEAddGrpB_TimeMark;


extern const ASN1CType asn1_type_SAEAddGrpB_TimeMark[];

#ifdef  __cplusplus
}
#endif

#endif /* _FFASN1_J2735ASN_H */
