/* Automatically generated file - do not edit */
#ifndef _FFASN1_RAW_ASN_H
#define _FFASN1_RAW_ASN_H

#include "asn1defs.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef unsigned int RAW_StationID;

extern const ASN1CType asn1_type_RAW_StationID[];

typedef struct RAW_ItsPduHeader {
  int protocolVersion;
  int messageID;
  RAW_StationID stationID;
} RAW_ItsPduHeader;


extern const ASN1CType asn1_type_RAW_ItsPduHeader[];

typedef RAW_ItsPduHeader RAW_ItsPduHeaderVam;

extern const ASN1CType asn1_type_RAW_ItsPduHeaderVam[];

typedef int RAW_GenerationDeltaTime;

enum {
  RAW_GenerationDeltaTime_oneMilliSec = 1,
};

extern const ASN1CType asn1_type_RAW_GenerationDeltaTime[];

typedef int RAW_StationType;

enum {
  RAW_StationType_unknown = 0,
  RAW_StationType_pedestrian = 1,
  RAW_StationType_cyclist = 2,
  RAW_StationType_moped = 3,
  RAW_StationType_motorcycle = 4,
  RAW_StationType_passengerCar = 5,
  RAW_StationType_bus = 6,
  RAW_StationType_lightTruck = 7,
  RAW_StationType_heavyTruck = 8,
  RAW_StationType_trailer = 9,
  RAW_StationType_specialVehicles = 10,
  RAW_StationType_tram = 11,
  RAW_StationType_lightVruVehicle = 12,
  RAW_StationType_animal = 13,
  RAW_StationType_roadSideUnit = 15,
};

extern const ASN1CType asn1_type_RAW_StationType[];

typedef int RAW_Latitude;

enum {
  RAW_Latitude_oneMicrodegreeNorth = 10,
  RAW_Latitude_oneMicrodegreeSouth = -10,
  RAW_Latitude_unavailable = 900000001,
};

extern const ASN1CType asn1_type_RAW_Latitude[];

typedef int RAW_Longitude;

enum {
  RAW_Longitude_oneMicrodegreeEast = 10,
  RAW_Longitude_oneMicrodegreeWest = -10,
  RAW_Longitude_unavailable = 1800000001,
};

extern const ASN1CType asn1_type_RAW_Longitude[];

typedef int RAW_SemiAxisLength;

enum {
  RAW_SemiAxisLength_oneCentimeter = 1,
  RAW_SemiAxisLength_outOfRange = 4094,
  RAW_SemiAxisLength_unavailable = 4095,
};

extern const ASN1CType asn1_type_RAW_SemiAxisLength[];

typedef int RAW_HeadingValue;

enum {
  RAW_HeadingValue_wgs84North = 0,
  RAW_HeadingValue_wgs84East = 900,
  RAW_HeadingValue_wgs84South = 1800,
  RAW_HeadingValue_wgs84West = 2700,
  RAW_HeadingValue_unavailable = 3601,
};

extern const ASN1CType asn1_type_RAW_HeadingValue[];

typedef struct RAW_PosConfidenceEllipse {
  RAW_SemiAxisLength semiMajorConfidence;
  RAW_SemiAxisLength semiMinorConfidence;
  RAW_HeadingValue semiMajorOrientation;
} RAW_PosConfidenceEllipse;


extern const ASN1CType asn1_type_RAW_PosConfidenceEllipse[];

typedef int RAW_AltitudeValue;

enum {
  RAW_AltitudeValue_referenceEllipsoidSurface = 0,
  RAW_AltitudeValue_oneCentimeter = 1,
  RAW_AltitudeValue_unavailable = 800001,
};

extern const ASN1CType asn1_type_RAW_AltitudeValue[];

typedef enum RAW_AltitudeConfidence {
  RAW_AltitudeConfidence_alt_000_01,
  RAW_AltitudeConfidence_alt_000_02,
  RAW_AltitudeConfidence_alt_000_05,
  RAW_AltitudeConfidence_alt_000_10,
  RAW_AltitudeConfidence_alt_000_20,
  RAW_AltitudeConfidence_alt_000_50,
  RAW_AltitudeConfidence_alt_001_00,
  RAW_AltitudeConfidence_alt_002_00,
  RAW_AltitudeConfidence_alt_005_00,
  RAW_AltitudeConfidence_alt_010_00,
  RAW_AltitudeConfidence_alt_020_00,
  RAW_AltitudeConfidence_alt_050_00,
  RAW_AltitudeConfidence_alt_100_00,
  RAW_AltitudeConfidence_alt_200_00,
  RAW_AltitudeConfidence_outOfRange,
  RAW_AltitudeConfidence_unavailable,
} RAW_AltitudeConfidence;

extern const ASN1CType asn1_type_RAW_AltitudeConfidence[];

typedef struct RAW_Altitude {
  RAW_AltitudeValue altitudeValue;
  RAW_AltitudeConfidence altitudeConfidence;
} RAW_Altitude;


extern const ASN1CType asn1_type_RAW_Altitude[];

typedef struct RAW_ReferencePosition {
  RAW_Latitude latitude;
  RAW_Longitude longitude;
  RAW_PosConfidenceEllipse positionConfidenceEllipse;
  RAW_Altitude altitude;
} RAW_ReferencePosition;


extern const ASN1CType asn1_type_RAW_ReferencePosition[];

typedef struct RAW_BasicContainer {
  RAW_StationType stationType;
  RAW_ReferencePosition referencePosition;
} RAW_BasicContainer;


extern const ASN1CType asn1_type_RAW_BasicContainer[];

typedef int RAW_HeadingConfidence;

enum {
  RAW_HeadingConfidence_equalOrWithinZeroPointOneDegree = 1,
  RAW_HeadingConfidence_equalOrWithinOneDegree = 10,
  RAW_HeadingConfidence_outOfRange = 126,
  RAW_HeadingConfidence_unavailable = 127,
};

extern const ASN1CType asn1_type_RAW_HeadingConfidence[];

typedef struct RAW_Heading {
  RAW_HeadingValue headingValue;
  RAW_HeadingConfidence headingConfidence;
} RAW_Heading;


extern const ASN1CType asn1_type_RAW_Heading[];

typedef int RAW_SpeedValue;

enum {
  RAW_SpeedValue_standstill = 0,
  RAW_SpeedValue_oneCentimeterPerSec = 1,
  RAW_SpeedValue_unavailable = 16383,
};

extern const ASN1CType asn1_type_RAW_SpeedValue[];

typedef int RAW_SpeedConfidence;

enum {
  RAW_SpeedConfidence_equalOrWithinOneCentimeterPerSec = 1,
  RAW_SpeedConfidence_equalOrWithinOneMeterPerSec = 100,
  RAW_SpeedConfidence_outOfRange = 126,
  RAW_SpeedConfidence_unavailable = 127,
};

extern const ASN1CType asn1_type_RAW_SpeedConfidence[];

typedef struct RAW_Speed {
  RAW_SpeedValue speedValue;
  RAW_SpeedConfidence speedConfidence;
} RAW_Speed;


extern const ASN1CType asn1_type_RAW_Speed[];

typedef int RAW_LongitudinalAccelerationValue;

enum {
  RAW_LongitudinalAccelerationValue_pointOneMeterPerSecSquaredForward = 1,
  RAW_LongitudinalAccelerationValue_pointOneMeterPerSecSquaredBackward = -1,
  RAW_LongitudinalAccelerationValue_unavailable = 161,
};

extern const ASN1CType asn1_type_RAW_LongitudinalAccelerationValue[];

typedef int RAW_AccelerationConfidence;

enum {
  RAW_AccelerationConfidence_pointOneMeterPerSecSquared = 1,
  RAW_AccelerationConfidence_outOfRange = 101,
  RAW_AccelerationConfidence_unavailable = 102,
};

extern const ASN1CType asn1_type_RAW_AccelerationConfidence[];

typedef struct RAW_LongitudinalAcceleration {
  RAW_LongitudinalAccelerationValue longitudinalAccelerationValue;
  RAW_AccelerationConfidence longitudinalAccelerationConfidence;
} RAW_LongitudinalAcceleration;


extern const ASN1CType asn1_type_RAW_LongitudinalAcceleration[];

typedef int RAW_CurvatureValue;

enum {
  RAW_CurvatureValue_straight = 0,
  RAW_CurvatureValue_unavailable = 1023,
};

extern const ASN1CType asn1_type_RAW_CurvatureValue[];

typedef enum RAW_CurvatureConfidence {
  RAW_CurvatureConfidence_onePerMeter_0_00002,
  RAW_CurvatureConfidence_onePerMeter_0_0001,
  RAW_CurvatureConfidence_onePerMeter_0_0005,
  RAW_CurvatureConfidence_onePerMeter_0_002,
  RAW_CurvatureConfidence_onePerMeter_0_01,
  RAW_CurvatureConfidence_onePerMeter_0_1,
  RAW_CurvatureConfidence_outOfRange,
  RAW_CurvatureConfidence_unavailable,
} RAW_CurvatureConfidence;

extern const ASN1CType asn1_type_RAW_CurvatureConfidence[];

typedef struct RAW_Curvature {
  RAW_CurvatureValue curvatureValue;
  RAW_CurvatureConfidence curvatureConfidence;
} RAW_Curvature;


extern const ASN1CType asn1_type_RAW_Curvature[];

typedef enum RAW_CurvatureCalculationMode {
  RAW_CurvatureCalculationMode_yawRateUsed,
  RAW_CurvatureCalculationMode_yawRateNotUsed,
  RAW_CurvatureCalculationMode_unavailable,
} RAW_CurvatureCalculationMode;

extern const ASN1CType asn1_type_RAW_CurvatureCalculationMode[];

typedef int RAW_YawRateValue;

enum {
  RAW_YawRateValue_straight = 0,
  RAW_YawRateValue_degSec_000_01ToRight = -1,
  RAW_YawRateValue_degSec_000_01ToLeft = 1,
  RAW_YawRateValue_unavailable = 32767,
};

extern const ASN1CType asn1_type_RAW_YawRateValue[];

typedef enum RAW_YawRateConfidence {
  RAW_YawRateConfidence_degSec_000_01,
  RAW_YawRateConfidence_degSec_000_05,
  RAW_YawRateConfidence_degSec_000_10,
  RAW_YawRateConfidence_degSec_001_00,
  RAW_YawRateConfidence_degSec_005_00,
  RAW_YawRateConfidence_degSec_010_00,
  RAW_YawRateConfidence_degSec_100_00,
  RAW_YawRateConfidence_outOfRange,
  RAW_YawRateConfidence_unavailable,
} RAW_YawRateConfidence;

extern const ASN1CType asn1_type_RAW_YawRateConfidence[];

typedef struct RAW_YawRate {
  RAW_YawRateValue yawRateValue;
  RAW_YawRateConfidence yawRateConfidence;
} RAW_YawRate;


extern const ASN1CType asn1_type_RAW_YawRate[];

typedef int RAW_LateralAccelerationValue;

enum {
  RAW_LateralAccelerationValue_pointOneMeterPerSecSquaredToRight = -1,
  RAW_LateralAccelerationValue_pointOneMeterPerSecSquaredToLeft = 1,
  RAW_LateralAccelerationValue_unavailable = 161,
};

extern const ASN1CType asn1_type_RAW_LateralAccelerationValue[];

typedef struct RAW_LateralAcceleration {
  RAW_LateralAccelerationValue lateralAccelerationValue;
  RAW_AccelerationConfidence lateralAccelerationConfidence;
} RAW_LateralAcceleration;


extern const ASN1CType asn1_type_RAW_LateralAcceleration[];

typedef int RAW_VerticalAccelerationValue;

enum {
  RAW_VerticalAccelerationValue_pointOneMeterPerSecSquaredUp = 1,
  RAW_VerticalAccelerationValue_pointOneMeterPerSecSquaredDown = -1,
  RAW_VerticalAccelerationValue_unavailable = 161,
};

extern const ASN1CType asn1_type_RAW_VerticalAccelerationValue[];

typedef struct RAW_VerticalAcceleration {
  RAW_VerticalAccelerationValue verticalAccelerationValue;
  RAW_AccelerationConfidence verticalAccelerationConfidence;
} RAW_VerticalAcceleration;


extern const ASN1CType asn1_type_RAW_VerticalAcceleration[];

typedef enum RAW_OffRoadLanePosition {
  RAW_OffRoadLanePosition_unavailable,
  RAW_OffRoadLanePosition_sidewalk,
  RAW_OffRoadLanePosition_parkingLane,
  RAW_OffRoadLanePosition_bikeLane,
  RAW_OffRoadLanePosition_max,
} RAW_OffRoadLanePosition;

extern const ASN1CType asn1_type_RAW_OffRoadLanePosition[];

typedef int RAW_LanePosition;

enum {
  RAW_LanePosition_offTheRoad = -1,
  RAW_LanePosition_hardShoulder = 0,
  RAW_LanePosition_outermostDrivingLane = 1,
  RAW_LanePosition_secondLaneFromOutside = 2,
};

extern const ASN1CType asn1_type_RAW_LanePosition[];

typedef int RAW_RoadRegulatorID;

extern const ASN1CType asn1_type_RAW_RoadRegulatorID[];

typedef int RAW_IntersectionID;

extern const ASN1CType asn1_type_RAW_IntersectionID[];

typedef struct RAW_IntersectionReferenceID {
  BOOL region_option;
  RAW_RoadRegulatorID region;
  RAW_IntersectionID id;
} RAW_IntersectionReferenceID;


extern const ASN1CType asn1_type_RAW_IntersectionReferenceID[];

typedef int RAW_LaneID;

extern const ASN1CType asn1_type_RAW_LaneID[];

typedef struct RAW_MapPosition {
  RAW_IntersectionReferenceID intersectionId;
  RAW_LaneID lane;
} RAW_MapPosition;


extern const ASN1CType asn1_type_RAW_MapPosition[];

typedef enum {
  RAW_NonIslandLanePosition_offRoadLanePosition,
  RAW_NonIslandLanePosition_vehicularLanePosition,
  RAW_NonIslandLanePosition_mapPosition,
} RAW_NonIslandLanePosition_choice;

typedef struct RAW_NonIslandLanePosition {
  RAW_NonIslandLanePosition_choice choice;
  union {
    RAW_OffRoadLanePosition offRoadLanePosition;
    RAW_LanePosition vehicularLanePosition;
    RAW_MapPosition mapPosition;
  } u;
} RAW_NonIslandLanePosition;

extern const ASN1CType asn1_type_RAW_NonIslandLanePosition[];

typedef struct RAW_TrafficIslandPosition {
  RAW_NonIslandLanePosition oneSide;
  RAW_NonIslandLanePosition otherSide;
} RAW_TrafficIslandPosition;


extern const ASN1CType asn1_type_RAW_TrafficIslandPosition[];

typedef enum {
  RAW_VruLanePosition_offRoadLanePosition,
  RAW_VruLanePosition_vehicularLanePosition,
  RAW_VruLanePosition_trafficIslandPosition,
  RAW_VruLanePosition_mapPosition,
} RAW_VruLanePosition_choice;

typedef struct RAW_VruLanePosition {
  RAW_VruLanePosition_choice choice;
  union {
    RAW_OffRoadLanePosition offRoadLanePosition;
    RAW_LanePosition vehicularLanePosition;
    RAW_TrafficIslandPosition trafficIslandPosition;
    RAW_MapPosition mapPosition;
  } u;
} RAW_VruLanePosition;

extern const ASN1CType asn1_type_RAW_VruLanePosition[];

typedef enum RAW_VruEnvironment {
  RAW_VruEnvironment_unavailable,
  RAW_VruEnvironment_intersectionCrossing,
  RAW_VruEnvironment_zebraCrossing,
  RAW_VruEnvironment_sidewalk,
  RAW_VruEnvironment_onVehicleRoad,
  RAW_VruEnvironment_protectedGeographicArea,
  RAW_VruEnvironment_max,
} RAW_VruEnvironment;

extern const ASN1CType asn1_type_RAW_VruEnvironment[];

typedef enum RAW_VruMovementControl {
  RAW_VruMovementControl_unavailable,
  RAW_VruMovementControl_braking,
  RAW_VruMovementControl_hardBraking,
  RAW_VruMovementControl_stopPedaling,
  RAW_VruMovementControl_brakingAndStopPedaling,
  RAW_VruMovementControl_hardBrakingAndStopPedaling,
  RAW_VruMovementControl_noReaction,
  RAW_VruMovementControl_max,
} RAW_VruMovementControl;

extern const ASN1CType asn1_type_RAW_VruMovementControl[];

typedef RAW_Heading RAW_VruOrientation;

extern const ASN1CType asn1_type_RAW_VruOrientation[];

typedef RAW_Heading RAW_VruRollAngle;

extern const ASN1CType asn1_type_RAW_VruRollAngle[];

typedef enum RAW_VruDeviceUsage {
  RAW_VruDeviceUsage_unavailable,
  RAW_VruDeviceUsage_other,
  RAW_VruDeviceUsage_idle,
  RAW_VruDeviceUsage_listeningToAudio,
  RAW_VruDeviceUsage_typing,
  RAW_VruDeviceUsage_calling,
  RAW_VruDeviceUsage_playingGames,
  RAW_VruDeviceUsage_reading,
  RAW_VruDeviceUsage_viewing,
  RAW_VruDeviceUsage_max,
} RAW_VruDeviceUsage;

extern const ASN1CType asn1_type_RAW_VruDeviceUsage[];

typedef struct RAW_VruHighFrequencyContainer {
  RAW_Heading heading;
  RAW_Speed speed;
  RAW_LongitudinalAcceleration longitudinalAcceleration;
  BOOL curvature_option;
  RAW_Curvature curvature;
  BOOL curvatureCalculationMode_option;
  RAW_CurvatureCalculationMode curvatureCalculationMode;
  BOOL yawRate_option;
  RAW_YawRate yawRate;
  BOOL lateralAcceleration_option;
  RAW_LateralAcceleration lateralAcceleration;
  BOOL verticalAcceleration_option;
  RAW_VerticalAcceleration verticalAcceleration;
  BOOL vruLanePosition_option;
  RAW_VruLanePosition vruLanePosition;
  BOOL environment_option;
  RAW_VruEnvironment environment;
  BOOL movementControl_option;
  RAW_VruMovementControl movementControl;
  BOOL orientation_option;
  RAW_VruOrientation orientation;
  BOOL rollAngle_option;
  RAW_VruRollAngle rollAngle;
  BOOL deviceUsage_option;
  RAW_VruDeviceUsage deviceUsage;
} RAW_VruHighFrequencyContainer;


extern const ASN1CType asn1_type_RAW_VruHighFrequencyContainer[];

typedef enum RAW_VruSubProfilePedestrian {
  RAW_VruSubProfilePedestrian_unavailable,
  RAW_VruSubProfilePedestrian_ordinary_pedestrian,
  RAW_VruSubProfilePedestrian_road_worker,
  RAW_VruSubProfilePedestrian_first_responder,
  RAW_VruSubProfilePedestrian_max,
} RAW_VruSubProfilePedestrian;

extern const ASN1CType asn1_type_RAW_VruSubProfilePedestrian[];

typedef enum RAW_VruSubProfileBicyclist {
  RAW_VruSubProfileBicyclist_unavailable,
  RAW_VruSubProfileBicyclist_bicyclist,
  RAW_VruSubProfileBicyclist_wheelchair_user,
  RAW_VruSubProfileBicyclist_horse_and_rider,
  RAW_VruSubProfileBicyclist_rollerskater,
  RAW_VruSubProfileBicyclist_e_scooter,
  RAW_VruSubProfileBicyclist_personal_transporter,
  RAW_VruSubProfileBicyclist_pedelec,
  RAW_VruSubProfileBicyclist_speed_pedelec,
  RAW_VruSubProfileBicyclist_max,
} RAW_VruSubProfileBicyclist;

extern const ASN1CType asn1_type_RAW_VruSubProfileBicyclist[];

typedef enum RAW_VruSubProfileMotorcyclist {
  RAW_VruSubProfileMotorcyclist_unavailable,
  RAW_VruSubProfileMotorcyclist_moped,
  RAW_VruSubProfileMotorcyclist_motorcycle,
  RAW_VruSubProfileMotorcyclist_motorcycle_and_sidecar_right,
  RAW_VruSubProfileMotorcyclist_motorcycle_and_sidecar_left,
  RAW_VruSubProfileMotorcyclist_max,
} RAW_VruSubProfileMotorcyclist;

extern const ASN1CType asn1_type_RAW_VruSubProfileMotorcyclist[];

typedef enum RAW_VruSubProfileAnimal {
  RAW_VruSubProfileAnimal_unavailable,
  RAW_VruSubProfileAnimal_wild_animal,
  RAW_VruSubProfileAnimal_farm_animal,
  RAW_VruSubProfileAnimal_service_animal,
  RAW_VruSubProfileAnimal_max,
} RAW_VruSubProfileAnimal;

extern const ASN1CType asn1_type_RAW_VruSubProfileAnimal[];

typedef enum {
  RAW_VruProfileAndSubprofile_pedestrian,
  RAW_VruProfileAndSubprofile_bicyclist,
  RAW_VruProfileAndSubprofile_motorcylist,
  RAW_VruProfileAndSubprofile_animal,
} RAW_VruProfileAndSubprofile_choice;

typedef struct RAW_VruProfileAndSubprofile {
  RAW_VruProfileAndSubprofile_choice choice;
  union {
    RAW_VruSubProfilePedestrian pedestrian;
    RAW_VruSubProfileBicyclist bicyclist;
    RAW_VruSubProfileMotorcyclist motorcylist;
    RAW_VruSubProfileAnimal animal;
  } u;
} RAW_VruProfileAndSubprofile;

extern const ASN1CType asn1_type_RAW_VruProfileAndSubprofile[];

typedef ASN1BitString RAW_VruSpecificExteriorLights;

extern const ASN1CType asn1_type_RAW_VruSpecificExteriorLights[];

typedef ASN1BitString RAW_ExteriorLights;

extern const ASN1CType asn1_type_RAW_ExteriorLights[];

typedef struct RAW_VruExteriorLights {
  RAW_VruSpecificExteriorLights vruSpecific;
  RAW_ExteriorLights vehicular;
} RAW_VruExteriorLights;


extern const ASN1CType asn1_type_RAW_VruExteriorLights[];

typedef enum RAW_VruSizeClass {
  RAW_VruSizeClass_unavailable,
  RAW_VruSizeClass_low,
  RAW_VruSizeClass_medium,
  RAW_VruSizeClass_high,
  RAW_VruSizeClass_max,
} RAW_VruSizeClass;

extern const ASN1CType asn1_type_RAW_VruSizeClass[];

typedef struct RAW_VruLowFrequencyContainer {
  BOOL profileAndSubprofile_option;
  RAW_VruProfileAndSubprofile profileAndSubprofile;
  BOOL exteriorLights_option;
  RAW_VruExteriorLights exteriorLights;
  BOOL sizeClass_option;
  RAW_VruSizeClass sizeClass;
} RAW_VruLowFrequencyContainer;


extern const ASN1CType asn1_type_RAW_VruLowFrequencyContainer[];

typedef int RAW_ClusterId;

extern const ASN1CType asn1_type_RAW_ClusterId[];

typedef int RAW_Offset_B10;

extern const ASN1CType asn1_type_RAW_Offset_B10[];

typedef struct RAW_Node_XY_20b {
  RAW_Offset_B10 x;
  RAW_Offset_B10 y;
} RAW_Node_XY_20b;


extern const ASN1CType asn1_type_RAW_Node_XY_20b[];

typedef int RAW_Offset_B11;

extern const ASN1CType asn1_type_RAW_Offset_B11[];

typedef struct RAW_Node_XY_22b {
  RAW_Offset_B11 x;
  RAW_Offset_B11 y;
} RAW_Node_XY_22b;


extern const ASN1CType asn1_type_RAW_Node_XY_22b[];

typedef int RAW_Offset_B12;

extern const ASN1CType asn1_type_RAW_Offset_B12[];

typedef struct RAW_Node_XY_24b {
  RAW_Offset_B12 x;
  RAW_Offset_B12 y;
} RAW_Node_XY_24b;


extern const ASN1CType asn1_type_RAW_Node_XY_24b[];

typedef int RAW_Offset_B13;

extern const ASN1CType asn1_type_RAW_Offset_B13[];

typedef struct RAW_Node_XY_26b {
  RAW_Offset_B13 x;
  RAW_Offset_B13 y;
} RAW_Node_XY_26b;


extern const ASN1CType asn1_type_RAW_Node_XY_26b[];

typedef int RAW_Offset_B14;

extern const ASN1CType asn1_type_RAW_Offset_B14[];

typedef struct RAW_Node_XY_28b {
  RAW_Offset_B14 x;
  RAW_Offset_B14 y;
} RAW_Node_XY_28b;


extern const ASN1CType asn1_type_RAW_Node_XY_28b[];

typedef int RAW_Offset_B16;

extern const ASN1CType asn1_type_RAW_Offset_B16[];

typedef struct RAW_Node_XY_32b {
  RAW_Offset_B16 x;
  RAW_Offset_B16 y;
} RAW_Node_XY_32b;


extern const ASN1CType asn1_type_RAW_Node_XY_32b[];

typedef struct RAW_Node_LLmD_64b {
  RAW_Longitude lon;
  RAW_Latitude lat;
} RAW_Node_LLmD_64b;


extern const ASN1CType asn1_type_RAW_Node_LLmD_64b[];

typedef int RAW_RegionId;

extern const ASN1CType asn1_type_RAW_RegionId[];

typedef struct RAW_RegionalExtension_1 {
  RAW_RegionId regionId;
  ASN1OpenType regExtValue;
} RAW_RegionalExtension_1;


extern const ASN1CType asn1_type_RAW_RegionalExtension_1[];

typedef enum {
  RAW_NodeOffsetPointXY_node_XY1,
  RAW_NodeOffsetPointXY_node_XY2,
  RAW_NodeOffsetPointXY_node_XY3,
  RAW_NodeOffsetPointXY_node_XY4,
  RAW_NodeOffsetPointXY_node_XY5,
  RAW_NodeOffsetPointXY_node_XY6,
  RAW_NodeOffsetPointXY_node_LatLon,
  RAW_NodeOffsetPointXY_regional,
} RAW_NodeOffsetPointXY_choice;

typedef struct RAW_NodeOffsetPointXY {
  RAW_NodeOffsetPointXY_choice choice;
  union {
    RAW_Node_XY_20b node_XY1;
    RAW_Node_XY_22b node_XY2;
    RAW_Node_XY_24b node_XY3;
    RAW_Node_XY_26b node_XY4;
    RAW_Node_XY_28b node_XY5;
    RAW_Node_XY_32b node_XY6;
    RAW_Node_LLmD_64b node_LatLon;
    RAW_RegionalExtension_1 regional;
  } u;
} RAW_NodeOffsetPointXY;

extern const ASN1CType asn1_type_RAW_NodeOffsetPointXY[];

typedef enum {
  RAW_NodeOffsetPointZ_node_Z1,
  RAW_NodeOffsetPointZ_node_Z2,
  RAW_NodeOffsetPointZ_node_Z3,
  RAW_NodeOffsetPointZ_node_Z4,
  RAW_NodeOffsetPointZ_node_Z5,
  RAW_NodeOffsetPointZ_node_Z6,
} RAW_NodeOffsetPointZ_choice;

typedef struct RAW_NodeOffsetPointZ {
  RAW_NodeOffsetPointZ_choice choice;
  union {
    RAW_Offset_B10 node_Z1;
    RAW_Offset_B11 node_Z2;
    RAW_Offset_B12 node_Z3;
    RAW_Offset_B13 node_Z4;
    RAW_Offset_B14 node_Z5;
    RAW_Offset_B16 node_Z6;
  } u;
} RAW_NodeOffsetPointZ;

extern const ASN1CType asn1_type_RAW_NodeOffsetPointZ[];

typedef struct RAW_OffsetPoint {
  RAW_NodeOffsetPointXY nodeOffsetPointXY;
  BOOL nodeOffsetPointZ_option;
  RAW_NodeOffsetPointZ nodeOffsetPointZ;
} RAW_OffsetPoint;


extern const ASN1CType asn1_type_RAW_OffsetPoint[];

typedef int RAW_SemiRangeLength;

enum {
  RAW_SemiRangeLength_zeroPointOneMeter = 1,
  RAW_SemiRangeLength_oneMeter = 10,
};

extern const ASN1CType asn1_type_RAW_SemiRangeLength[];

typedef int RAW_WGS84AngleValue;

enum {
  RAW_WGS84AngleValue_wgs84North = 0,
  RAW_WGS84AngleValue_wgs84East = 900,
  RAW_WGS84AngleValue_wgs84South = 1800,
  RAW_WGS84AngleValue_wgs84West = 2700,
  RAW_WGS84AngleValue_unavailable = 3601,
};

extern const ASN1CType asn1_type_RAW_WGS84AngleValue[];

typedef struct RAW_AreaRectangle {
  BOOL nodeCenterPoint_option;
  RAW_OffsetPoint nodeCenterPoint;
  RAW_SemiRangeLength semiMajorRangeLength;
  RAW_SemiRangeLength semiMinorRangeLength;
  RAW_WGS84AngleValue semiMajorRangeOrientation;
  BOOL semiHeight_option;
  RAW_SemiRangeLength semiHeight;
} RAW_AreaRectangle;


extern const ASN1CType asn1_type_RAW_AreaRectangle[];

typedef int RAW_Radius;

enum {
  RAW_Radius_zeroPointOneMeter = 1,
  RAW_Radius_oneMeter = 10,
};

extern const ASN1CType asn1_type_RAW_Radius[];

typedef struct RAW_AreaCircular {
  BOOL nodeCenterPoint_option;
  RAW_OffsetPoint nodeCenterPoint;
  RAW_Radius radius;
} RAW_AreaCircular;


extern const ASN1CType asn1_type_RAW_AreaCircular[];

typedef struct RAW_PolyPointList {
  RAW_OffsetPoint *tab;
  size_t count;
} RAW_PolyPointList;

extern const ASN1CType asn1_type_RAW_PolyPointList[];

typedef struct RAW_AreaPolygon {
  RAW_PolyPointList polyPointList;
} RAW_AreaPolygon;


extern const ASN1CType asn1_type_RAW_AreaPolygon[];

typedef enum {
  RAW_ClusterBoundingBoxShape_clusterRectangle,
  RAW_ClusterBoundingBoxShape_clusterCircle,
  RAW_ClusterBoundingBoxShape_clusterPolygon,
} RAW_ClusterBoundingBoxShape_choice;

typedef struct RAW_ClusterBoundingBoxShape {
  RAW_ClusterBoundingBoxShape_choice choice;
  union {
    RAW_AreaRectangle clusterRectangle;
    RAW_AreaCircular clusterCircle;
    RAW_AreaPolygon clusterPolygon;
  } u;
} RAW_ClusterBoundingBoxShape;

extern const ASN1CType asn1_type_RAW_ClusterBoundingBoxShape[];

typedef int RAW_ClusterCardinalitySize;

enum {
  RAW_ClusterCardinalitySize_unavailable = 0,
  RAW_ClusterCardinalitySize_onlyLeader = 1,
};

extern const ASN1CType asn1_type_RAW_ClusterCardinalitySize[];

typedef ASN1BitString RAW_ClusterProfiles;

extern const ASN1CType asn1_type_RAW_ClusterProfiles[];

typedef struct RAW_VruClusterInformationContainer {
  RAW_ClusterId clusterId;
  RAW_ClusterBoundingBoxShape clusterBoundingBoxShape;
  RAW_ClusterCardinalitySize clusterCardinalitySize;
  RAW_ClusterProfiles clusterProfiles;
} RAW_VruClusterInformationContainer;


extern const ASN1CType asn1_type_RAW_VruClusterInformationContainer[];

typedef int RAW_VruClusterOpTimestamp;

extern const ASN1CType asn1_type_RAW_VruClusterOpTimestamp[];

typedef struct RAW_ClusterJoinInfo {
  RAW_ClusterId clusterId;
  RAW_VruClusterOpTimestamp joinTime;
} RAW_ClusterJoinInfo;


extern const ASN1CType asn1_type_RAW_ClusterJoinInfo[];

typedef enum RAW_ClusterLeaveReason {
  RAW_ClusterLeaveReason_notProvided,
  RAW_ClusterLeaveReason_clusterLeaderLost,
  RAW_ClusterLeaveReason_clusterDisbandedByLeader,
  RAW_ClusterLeaveReason_outOfClusterBoundingBox,
  RAW_ClusterLeaveReason_outOfClusterSpeedRange,
  RAW_ClusterLeaveReason_joiningAnotherCluster,
  RAW_ClusterLeaveReason_cancelledJoin,
  RAW_ClusterLeaveReason_failedJoin,
  RAW_ClusterLeaveReason_safetyCondition,
  RAW_ClusterLeaveReason_max,
} RAW_ClusterLeaveReason;

extern const ASN1CType asn1_type_RAW_ClusterLeaveReason[];

typedef struct RAW_ClusterLeaveInfo {
  RAW_ClusterId clusterId;
  RAW_ClusterLeaveReason clusterLeaveReason;
} RAW_ClusterLeaveInfo;


extern const ASN1CType asn1_type_RAW_ClusterLeaveInfo[];

typedef enum RAW_ClusterBreakupReason {
  RAW_ClusterBreakupReason_notProvided,
  RAW_ClusterBreakupReason_clusteringPurposeCompleted,
  RAW_ClusterBreakupReason_leaderMovedOutOfClusterBoundingBox,
  RAW_ClusterBreakupReason_joiningAnotherCluster,
  RAW_ClusterBreakupReason_enteringLowRiskAreaBasedOnMaps,
  RAW_ClusterBreakupReason_receptionOfCpmContainingCluster,
  RAW_ClusterBreakupReason_max,
} RAW_ClusterBreakupReason;

extern const ASN1CType asn1_type_RAW_ClusterBreakupReason[];

typedef struct RAW_ClusterBreakupInfo {
  RAW_ClusterBreakupReason clusterBreakupReason;
  RAW_VruClusterOpTimestamp breakupTime;
} RAW_ClusterBreakupInfo;


extern const ASN1CType asn1_type_RAW_ClusterBreakupInfo[];

typedef struct RAW_VruClusterOperationContainer {
  BOOL clusterJoinInfo_option;
  RAW_ClusterJoinInfo clusterJoinInfo;
  BOOL clusterLeaveInfo_option;
  RAW_ClusterLeaveInfo clusterLeaveInfo;
  BOOL clusterBreakupInfo_option;
  RAW_ClusterBreakupInfo clusterBreakupInfo;
  BOOL clusterIdChangeTimeInfo_option;
  RAW_VruClusterOpTimestamp clusterIdChangeTimeInfo;
} RAW_VruClusterOperationContainer;


extern const ASN1CType asn1_type_RAW_VruClusterOperationContainer[];

typedef int RAW_DeltaLatitude;

enum {
  RAW_DeltaLatitude_oneMicrodegreeNorth = 10,
  RAW_DeltaLatitude_oneMicrodegreeSouth = -10,
  RAW_DeltaLatitude_unavailable = 131072,
};

extern const ASN1CType asn1_type_RAW_DeltaLatitude[];

typedef int RAW_DeltaLongitude;

enum {
  RAW_DeltaLongitude_oneMicrodegreeEast = 10,
  RAW_DeltaLongitude_oneMicrodegreeWest = -10,
  RAW_DeltaLongitude_unavailable = 131072,
};

extern const ASN1CType asn1_type_RAW_DeltaLongitude[];

typedef int RAW_DeltaAltitude;

enum {
  RAW_DeltaAltitude_oneCentimeterUp = 1,
  RAW_DeltaAltitude_oneCentimeterDown = -1,
  RAW_DeltaAltitude_unavailable = 12800,
};

extern const ASN1CType asn1_type_RAW_DeltaAltitude[];

typedef struct RAW_DeltaReferencePosition {
  RAW_DeltaLatitude deltaLatitude;
  RAW_DeltaLongitude deltaLongitude;
  RAW_DeltaAltitude deltaAltitude;
} RAW_DeltaReferencePosition;


extern const ASN1CType asn1_type_RAW_DeltaReferencePosition[];

typedef int RAW_PathDeltaTime;

enum {
  RAW_PathDeltaTime_tenMilliSecondsInPast = 1,
};

extern const ASN1CType asn1_type_RAW_PathDeltaTime[];

typedef struct RAW_PathPoint {
  RAW_DeltaReferencePosition pathPosition;
  BOOL pathDeltaTime_option;
  RAW_PathDeltaTime pathDeltaTime;
} RAW_PathPoint;


extern const ASN1CType asn1_type_RAW_PathPoint[];

typedef struct RAW_PathHistory {
  RAW_PathPoint *tab;
  size_t count;
} RAW_PathHistory;

extern const ASN1CType asn1_type_RAW_PathHistory[];

typedef struct RAW_VruPathPoint {
  RAW_ReferencePosition pathPosition;
  BOOL pathDeltaTime_option;
  RAW_PathDeltaTime pathDeltaTime;
} RAW_VruPathPoint;


extern const ASN1CType asn1_type_RAW_VruPathPoint[];

typedef struct RAW_SequenceOfVruPathPoint {
  RAW_VruPathPoint *tab;
  size_t count;
} RAW_SequenceOfVruPathPoint;

extern const ASN1CType asn1_type_RAW_SequenceOfVruPathPoint[];

typedef BOOL RAW_StationSafeDistanceIndication;

extern const ASN1CType asn1_type_RAW_StationSafeDistanceIndication[];

typedef int RAW_ActionDeltaTime;

enum {
  RAW_ActionDeltaTime_zero = 0,
  RAW_ActionDeltaTime_hundredMs = 1,
  RAW_ActionDeltaTime_twoHundredMs = 2,
  RAW_ActionDeltaTime_unavailable = 127,
};

extern const ASN1CType asn1_type_RAW_ActionDeltaTime[];

typedef struct RAW_VruSafeDistanceIndication {
  BOOL subjectStation_option;
  RAW_StationID subjectStation;
  RAW_StationSafeDistanceIndication stationSafeDistanceIndication;
  BOOL timeToCollision_option;
  RAW_ActionDeltaTime timeToCollision;
} RAW_VruSafeDistanceIndication;


extern const ASN1CType asn1_type_RAW_VruSafeDistanceIndication[];

typedef struct RAW_SequenceOfVruSafeDistanceIndication {
  RAW_VruSafeDistanceIndication *tab;
  size_t count;
} RAW_SequenceOfVruSafeDistanceIndication;

extern const ASN1CType asn1_type_RAW_SequenceOfVruSafeDistanceIndication[];

typedef int RAW_TrajectoryInterceptionProbability;

enum {
  RAW_TrajectoryInterceptionProbability_zero = 0,
  RAW_TrajectoryInterceptionProbability_twoPercent = 1,
  RAW_TrajectoryInterceptionProbability_fourPercent = 2,
  RAW_TrajectoryInterceptionProbability_oneHundredPercent = 50,
  RAW_TrajectoryInterceptionProbability_unavailable = 63,
};

extern const ASN1CType asn1_type_RAW_TrajectoryInterceptionProbability[];

typedef int RAW_TrajectoryInterceptionConfidence;

enum {
  RAW_TrajectoryInterceptionConfidence_lessthan50percent = 0,
  RAW_TrajectoryInterceptionConfidence_between50and70Percent = 1,
  RAW_TrajectoryInterceptionConfidence_between70and90Percent = 2,
  RAW_TrajectoryInterceptionConfidence_above90Percent = 3,
};

extern const ASN1CType asn1_type_RAW_TrajectoryInterceptionConfidence[];

typedef struct RAW_TrajectoryInterceptionIndication {
  BOOL subjectStation_option;
  RAW_StationID subjectStation;
  RAW_TrajectoryInterceptionProbability trajectoryInterceptionProbability;
  BOOL trajectoryInterceptionConfidence_option;
  RAW_TrajectoryInterceptionConfidence trajectoryInterceptionConfidence;
} RAW_TrajectoryInterceptionIndication;


extern const ASN1CType asn1_type_RAW_TrajectoryInterceptionIndication[];

typedef struct RAW_SequenceOfTrajectoryInterceptionIndication {
  RAW_TrajectoryInterceptionIndication *tab;
  size_t count;
} RAW_SequenceOfTrajectoryInterceptionIndication;

extern const ASN1CType asn1_type_RAW_SequenceOfTrajectoryInterceptionIndication[];

typedef enum RAW_AccelOrDecel {
  RAW_AccelOrDecel_accelerate,
  RAW_AccelOrDecel_decelerate,
} RAW_AccelOrDecel;

extern const ASN1CType asn1_type_RAW_AccelOrDecel[];

typedef struct RAW_AccelerationChangeIndication {
  RAW_AccelOrDecel accelOrDecel;
  RAW_ActionDeltaTime actionDeltaTime;
} RAW_AccelerationChangeIndication;


extern const ASN1CType asn1_type_RAW_AccelerationChangeIndication[];

typedef enum RAW_LeftOrRight {
  RAW_LeftOrRight_left,
  RAW_LeftOrRight_right,
} RAW_LeftOrRight;

extern const ASN1CType asn1_type_RAW_LeftOrRight[];

typedef struct RAW_HeadingChangeIndication {
  RAW_LeftOrRight direction;
  RAW_ActionDeltaTime actionDeltaTime;
} RAW_HeadingChangeIndication;


extern const ASN1CType asn1_type_RAW_HeadingChangeIndication[];

typedef int RAW_StabilityLossProbability;

enum {
  RAW_StabilityLossProbability_zero = 0,
  RAW_StabilityLossProbability_twoPercent = 1,
  RAW_StabilityLossProbability_fourPercent = 2,
  RAW_StabilityLossProbability_unavailable = 63,
};

extern const ASN1CType asn1_type_RAW_StabilityLossProbability[];

typedef struct RAW_StabilityChangeIndication {
  RAW_StabilityLossProbability lossProbability;
  RAW_ActionDeltaTime actionDeltaTime;
} RAW_StabilityChangeIndication;


extern const ASN1CType asn1_type_RAW_StabilityChangeIndication[];

typedef struct RAW_VruMotionPredictionContainer {
  BOOL pathHistory_option;
  RAW_PathHistory pathHistory;
  BOOL pathPrediction_option;
  RAW_SequenceOfVruPathPoint pathPrediction;
  BOOL safeDistance_option;
  RAW_SequenceOfVruSafeDistanceIndication safeDistance;
  BOOL trajectoryInterceptionIndication_option;
  RAW_SequenceOfTrajectoryInterceptionIndication trajectoryInterceptionIndication;
  BOOL accelerationChangeIndication_option;
  RAW_AccelerationChangeIndication accelerationChangeIndication;
  BOOL headingChangeIndication_option;
  RAW_HeadingChangeIndication headingChangeIndication;
  BOOL stabilityChangeIndication_option;
  RAW_StabilityChangeIndication stabilityChangeIndication;
} RAW_VruMotionPredictionContainer;


extern const ASN1CType asn1_type_RAW_VruMotionPredictionContainer[];

typedef struct RAW_VamParameters {
  RAW_BasicContainer basicContainer;
  BOOL vruHighFrequencyContainer_option;
  RAW_VruHighFrequencyContainer vruHighFrequencyContainer;
  BOOL vruLowFrequencyContainer_option;
  RAW_VruLowFrequencyContainer vruLowFrequencyContainer;
  BOOL vruClusterInformationContainer_option;
  RAW_VruClusterInformationContainer vruClusterInformationContainer;
  BOOL vruClusterOperationContainer_option;
  RAW_VruClusterOperationContainer vruClusterOperationContainer;
  BOOL vruMotionPredictionContainer_option;
  RAW_VruMotionPredictionContainer vruMotionPredictionContainer;
} RAW_VamParameters;


extern const ASN1CType asn1_type_RAW_VamParameters[];

typedef struct RAW_VruAwareness {
  RAW_GenerationDeltaTime generationDeltaTime;
  RAW_VamParameters vamParameters;
} RAW_VruAwareness;


extern const ASN1CType asn1_type_RAW_VruAwareness[];

typedef struct RAW_VAM {
  RAW_ItsPduHeaderVam header;
  RAW_VruAwareness vam;
} RAW_VAM;


extern const ASN1CType asn1_type_RAW_VAM[];

typedef struct RAW_RAW {
  RAW_ItsPduHeader header;
  RAW_VAM vammsg;
} RAW_RAW;


extern const ASN1CType asn1_type_RAW_RAW[];

typedef enum RAW_VruProfile {
  RAW_VruProfile_unavailable,
  RAW_VruProfile_pedestrian,
  RAW_VruProfile_cyclist,
  RAW_VruProfile_motorcyclist,
  RAW_VruProfile_animal,
  RAW_VruProfile_max,
} RAW_VruProfile;

extern const ASN1CType asn1_type_RAW_VruProfile[];

typedef struct RAW_REG_EXT_ID_AND_TYPE { /* object class definition */
  ASN1CType id;
  ASN1CType Type;
} RAW_REG_EXT_ID_AND_TYPE;


extern const ASN1CType asn1_type_RAW_REG_EXT_ID_AND_TYPE[];

#define RAW_noRegion 0

#define RAW_addGrpA 1

#define RAW_addGrpB 2

#define RAW_addGrpC 3

#ifdef  __cplusplus
}
#endif

#endif /* _FFASN1_RAW_ASN_H */
