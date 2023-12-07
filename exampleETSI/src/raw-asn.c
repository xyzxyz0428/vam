/* Automatically generated file - do not edit */

#include "asn1defs.h"
#include "raw-asn.h"

const ASN1CType asn1_type_RAW__local_0[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_ItsPduHeader,
};

const ASN1CType asn1_type_RAW_RAW[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_RAW),

  offsetof(RAW_RAW, header) | 0x0,
  (intptr_t)asn1_type_RAW__local_0,
  0,
  (intptr_t)"header",

  offsetof(RAW_RAW, vammsg) | 0x0,
  (intptr_t)asn1_type_RAW_VAM,
  0,
  (intptr_t)"vammsg",

  (intptr_t)"RAW",
};

const ASN1CType asn1_type_RAW__local_1[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x1800000 | 0x100000,
  0x0,
  0xff,
};

const ASN1CType asn1_type_RAW__local_2[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x1800000 | 0x100001,
  0x0,
  0xff,
};

const ASN1CType asn1_type_RAW__local_3[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_StationID,
};

const ASN1CType asn1_type_RAW_ItsPduHeader[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  3,
  sizeof(RAW_ItsPduHeader),

  offsetof(RAW_ItsPduHeader, protocolVersion) | 0x0,
  (intptr_t)asn1_type_RAW__local_1,
  0,
  (intptr_t)"protocolVersion",

  offsetof(RAW_ItsPduHeader, messageID) | 0x0,
  (intptr_t)asn1_type_RAW__local_2,
  0,
  (intptr_t)"messageID",

  offsetof(RAW_ItsPduHeader, stationID) | 0x0,
  (intptr_t)asn1_type_RAW__local_3,
  0,
  (intptr_t)"stationID",

  (intptr_t)"ItsPduHeader",
};

const ASN1CType asn1_type_RAW_StationID[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0xffffffff,
  (intptr_t)"StationID",
};

const ASN1CType asn1_type_RAW_VAM[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_VAM),

  offsetof(RAW_VAM, header) | 0x0,
  (intptr_t)asn1_type_RAW_ItsPduHeaderVam,
  0,
  (intptr_t)"header",

  offsetof(RAW_VAM, vam) | 0x0,
  (intptr_t)asn1_type_RAW_VruAwareness,
  0,
  (intptr_t)"vam",

  (intptr_t)"VAM",
};

const ASN1CType asn1_type_RAW_ItsPduHeaderVam[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  (intptr_t)asn1_type_RAW_ItsPduHeader,
  (intptr_t)"ItsPduHeaderVam",
};

const ASN1CType asn1_type_RAW_VruAwareness[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_VruAwareness),

  offsetof(RAW_VruAwareness, generationDeltaTime) | 0x0,
  (intptr_t)asn1_type_RAW_GenerationDeltaTime,
  0,
  (intptr_t)"generationDeltaTime",

  offsetof(RAW_VruAwareness, vamParameters) | 0x0,
  (intptr_t)asn1_type_RAW_VamParameters,
  0,
  (intptr_t)"vamParameters",

  (intptr_t)"VruAwareness",
};

const ASN1CType asn1_type_RAW_GenerationDeltaTime[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0xffff,
  (intptr_t)"GenerationDeltaTime",
};

const ASN1CType asn1_type_RAW_VamParameters[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100001,
  6,
  sizeof(RAW_VamParameters),

  offsetof(RAW_VamParameters, basicContainer) | 0x0,
  (intptr_t)asn1_type_RAW_BasicContainer,
  0,
  (intptr_t)"basicContainer",

  offsetof(RAW_VamParameters, vruHighFrequencyContainer) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruHighFrequencyContainer,
  offsetof(RAW_VamParameters, vruHighFrequencyContainer_option),
  (intptr_t)"vruHighFrequencyContainer",

  offsetof(RAW_VamParameters, vruLowFrequencyContainer) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruLowFrequencyContainer,
  offsetof(RAW_VamParameters, vruLowFrequencyContainer_option),
  (intptr_t)"vruLowFrequencyContainer",

  offsetof(RAW_VamParameters, vruClusterInformationContainer) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruClusterInformationContainer,
  offsetof(RAW_VamParameters, vruClusterInformationContainer_option),
  (intptr_t)"vruClusterInformationContainer",

  offsetof(RAW_VamParameters, vruClusterOperationContainer) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruClusterOperationContainer,
  offsetof(RAW_VamParameters, vruClusterOperationContainer_option),
  (intptr_t)"vruClusterOperationContainer",

  offsetof(RAW_VamParameters, vruMotionPredictionContainer) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruMotionPredictionContainer,
  offsetof(RAW_VamParameters, vruMotionPredictionContainer_option),
  (intptr_t)"vruMotionPredictionContainer",

  (intptr_t)"VamParameters",
};

const ASN1CType asn1_type_RAW__local_4[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_ReferencePosition,
};

const ASN1CType asn1_type_RAW_BasicContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100000,
  2,
  sizeof(RAW_BasicContainer),

  offsetof(RAW_BasicContainer, stationType) | 0x0,
  (intptr_t)asn1_type_RAW_StationType,
  0,
  (intptr_t)"stationType",

  offsetof(RAW_BasicContainer, referencePosition) | 0x0,
  (intptr_t)asn1_type_RAW__local_4,
  0,
  (intptr_t)"referencePosition",

  (intptr_t)"BasicContainer",
};

const ASN1CType asn1_type_RAW_StationType[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0xff,
  (intptr_t)"StationType",
};

const ASN1CType asn1_type_RAW__local_5[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Latitude,
};

const ASN1CType asn1_type_RAW__local_6[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Longitude,
};

const ASN1CType asn1_type_RAW_ReferencePosition[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  4,
  sizeof(RAW_ReferencePosition),

  offsetof(RAW_ReferencePosition, latitude) | 0x0,
  (intptr_t)asn1_type_RAW__local_5,
  0,
  (intptr_t)"latitude",

  offsetof(RAW_ReferencePosition, longitude) | 0x0,
  (intptr_t)asn1_type_RAW__local_6,
  0,
  (intptr_t)"longitude",

  offsetof(RAW_ReferencePosition, positionConfidenceEllipse) | 0x0,
  (intptr_t)asn1_type_RAW_PosConfidenceEllipse,
  0,
  (intptr_t)"positionConfidenceEllipse",

  offsetof(RAW_ReferencePosition, altitude) | 0x0,
  (intptr_t)asn1_type_RAW_Altitude,
  0,
  (intptr_t)"altitude",

  (intptr_t)"ReferencePosition",
};

const ASN1CType asn1_type_RAW_Longitude[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x94b62e00,
  0x6b49d201,
  (intptr_t)"Longitude",
};

const ASN1CType asn1_type_RAW_Latitude[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xca5b1700,
  0x35a4e901,
  (intptr_t)"Latitude",
};

const ASN1CType asn1_type_RAW_Altitude[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100003,
  2,
  sizeof(RAW_Altitude),

  offsetof(RAW_Altitude, altitudeValue) | 0x0,
  (intptr_t)asn1_type_RAW_AltitudeValue,
  0,
  (intptr_t)"altitudeValue",

  offsetof(RAW_Altitude, altitudeConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_AltitudeConfidence,
  0,
  (intptr_t)"altitudeConfidence",

  (intptr_t)"Altitude",
};

const ASN1CType asn1_type_RAW_AltitudeConfidence[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  16,
  (intptr_t)"alt-000-01",
  (intptr_t)"alt-000-02",
  (intptr_t)"alt-000-05",
  (intptr_t)"alt-000-10",
  (intptr_t)"alt-000-20",
  (intptr_t)"alt-000-50",
  (intptr_t)"alt-001-00",
  (intptr_t)"alt-002-00",
  (intptr_t)"alt-005-00",
  (intptr_t)"alt-010-00",
  (intptr_t)"alt-020-00",
  (intptr_t)"alt-050-00",
  (intptr_t)"alt-100-00",
  (intptr_t)"alt-200-00",
  (intptr_t)"outOfRange",
  (intptr_t)"unavailable",
  (intptr_t)"AltitudeConfidence",
};

const ASN1CType asn1_type_RAW_AltitudeValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xfffe7960,
  0xc3501,
  (intptr_t)"AltitudeValue",
};

const ASN1CType asn1_type_RAW__local_7[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_SemiAxisLength,
};

const ASN1CType asn1_type_RAW__local_8[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_SemiAxisLength,
};

const ASN1CType asn1_type_RAW__local_9[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_HeadingValue,
};

const ASN1CType asn1_type_RAW_PosConfidenceEllipse[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100002,
  3,
  sizeof(RAW_PosConfidenceEllipse),

  offsetof(RAW_PosConfidenceEllipse, semiMajorConfidence) | 0x0,
  (intptr_t)asn1_type_RAW__local_7,
  0,
  (intptr_t)"semiMajorConfidence",

  offsetof(RAW_PosConfidenceEllipse, semiMinorConfidence) | 0x0,
  (intptr_t)asn1_type_RAW__local_8,
  0,
  (intptr_t)"semiMinorConfidence",

  offsetof(RAW_PosConfidenceEllipse, semiMajorOrientation) | 0x0,
  (intptr_t)asn1_type_RAW__local_9,
  0,
  (intptr_t)"semiMajorOrientation",

  (intptr_t)"PosConfidenceEllipse",
};

const ASN1CType asn1_type_RAW_SemiAxisLength[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0xfff,
  (intptr_t)"SemiAxisLength",
};

const ASN1CType asn1_type_RAW_HeadingValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0xe11,
  (intptr_t)"HeadingValue",
};

const ASN1CType asn1_type_RAW_HeadingConfidence[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x1,
  0x7f,
  (intptr_t)"HeadingConfidence",
};

const ASN1CType asn1_type_RAW_VruProfile[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0xa,
  6,
  (intptr_t)"unavailable",
  (intptr_t)"pedestrian",
  (intptr_t)"cyclist",
  (intptr_t)"motorcyclist",
  (intptr_t)"animal",
  (intptr_t)"max",
  (intptr_t)"VruProfile",
  0,
  1,
  2,
  3,
  4,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  15,
  5,
};

const ASN1CType asn1_type_RAW__local_10[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Heading,
};

const ASN1CType asn1_type_RAW_VruHighFrequencyContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100001,
  14,
  sizeof(RAW_VruHighFrequencyContainer),

  offsetof(RAW_VruHighFrequencyContainer, heading) | 0x0,
  (intptr_t)asn1_type_RAW__local_10,
  0,
  (intptr_t)"heading",

  offsetof(RAW_VruHighFrequencyContainer, speed) | 0x0,
  (intptr_t)asn1_type_RAW_Speed,
  0,
  (intptr_t)"speed",

  offsetof(RAW_VruHighFrequencyContainer, longitudinalAcceleration) | 0x0,
  (intptr_t)asn1_type_RAW_LongitudinalAcceleration,
  0,
  (intptr_t)"longitudinalAcceleration",

  offsetof(RAW_VruHighFrequencyContainer, curvature) | 0x8000000,
  (intptr_t)asn1_type_RAW_Curvature,
  offsetof(RAW_VruHighFrequencyContainer, curvature_option),
  (intptr_t)"curvature",

  offsetof(RAW_VruHighFrequencyContainer, curvatureCalculationMode) | 0x8000000,
  (intptr_t)asn1_type_RAW_CurvatureCalculationMode,
  offsetof(RAW_VruHighFrequencyContainer, curvatureCalculationMode_option),
  (intptr_t)"curvatureCalculationMode",

  offsetof(RAW_VruHighFrequencyContainer, yawRate) | 0x8000000,
  (intptr_t)asn1_type_RAW_YawRate,
  offsetof(RAW_VruHighFrequencyContainer, yawRate_option),
  (intptr_t)"yawRate",

  offsetof(RAW_VruHighFrequencyContainer, lateralAcceleration) | 0x8000000,
  (intptr_t)asn1_type_RAW_LateralAcceleration,
  offsetof(RAW_VruHighFrequencyContainer, lateralAcceleration_option),
  (intptr_t)"lateralAcceleration",

  offsetof(RAW_VruHighFrequencyContainer, verticalAcceleration) | 0x8000000,
  (intptr_t)asn1_type_RAW_VerticalAcceleration,
  offsetof(RAW_VruHighFrequencyContainer, verticalAcceleration_option),
  (intptr_t)"verticalAcceleration",

  offsetof(RAW_VruHighFrequencyContainer, vruLanePosition) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruLanePosition,
  offsetof(RAW_VruHighFrequencyContainer, vruLanePosition_option),
  (intptr_t)"vruLanePosition",

  offsetof(RAW_VruHighFrequencyContainer, environment) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruEnvironment,
  offsetof(RAW_VruHighFrequencyContainer, environment_option),
  (intptr_t)"environment",

  offsetof(RAW_VruHighFrequencyContainer, movementControl) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruMovementControl,
  offsetof(RAW_VruHighFrequencyContainer, movementControl_option),
  (intptr_t)"movementControl",

  offsetof(RAW_VruHighFrequencyContainer, orientation) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruOrientation,
  offsetof(RAW_VruHighFrequencyContainer, orientation_option),
  (intptr_t)"orientation",

  offsetof(RAW_VruHighFrequencyContainer, rollAngle) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruRollAngle,
  offsetof(RAW_VruHighFrequencyContainer, rollAngle_option),
  (intptr_t)"rollAngle",

  offsetof(RAW_VruHighFrequencyContainer, deviceUsage) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruDeviceUsage,
  offsetof(RAW_VruHighFrequencyContainer, deviceUsage_option),
  (intptr_t)"deviceUsage",

  (intptr_t)"VruHighFrequencyContainer",
};

const ASN1CType asn1_type_RAW__local_11[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_HeadingValue,
};

const ASN1CType asn1_type_RAW_Heading[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_Heading),

  offsetof(RAW_Heading, headingValue) | 0x0,
  (intptr_t)asn1_type_RAW__local_11,
  0,
  (intptr_t)"headingValue",

  offsetof(RAW_Heading, headingConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_HeadingConfidence,
  0,
  (intptr_t)"headingConfidence",

  (intptr_t)"Heading",
};

const ASN1CType asn1_type_RAW_SpeedValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0x3fff,
  (intptr_t)"SpeedValue",
};

const ASN1CType asn1_type_RAW_SpeedConfidence[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x1,
  0x7f,
  (intptr_t)"SpeedConfidence",
};

const ASN1CType asn1_type_RAW_Speed[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_Speed),

  offsetof(RAW_Speed, speedValue) | 0x0,
  (intptr_t)asn1_type_RAW_SpeedValue,
  0,
  (intptr_t)"speedValue",

  offsetof(RAW_Speed, speedConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_SpeedConfidence,
  0,
  (intptr_t)"speedConfidence",

  (intptr_t)"Speed",
};

const ASN1CType asn1_type_RAW_LongitudinalAcceleration[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100002,
  2,
  sizeof(RAW_LongitudinalAcceleration),

  offsetof(RAW_LongitudinalAcceleration, longitudinalAccelerationValue) | 0x0,
  (intptr_t)asn1_type_RAW_LongitudinalAccelerationValue,
  0,
  (intptr_t)"longitudinalAccelerationValue",

  offsetof(RAW_LongitudinalAcceleration, longitudinalAccelerationConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_AccelerationConfidence,
  0,
  (intptr_t)"longitudinalAccelerationConfidence",

  (intptr_t)"LongitudinalAcceleration",
};

const ASN1CType asn1_type_RAW_LongitudinalAccelerationValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xffffff60,
  0xa1,
  (intptr_t)"LongitudinalAccelerationValue",
};

const ASN1CType asn1_type_RAW_Curvature[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100003,
  2,
  sizeof(RAW_Curvature),

  offsetof(RAW_Curvature, curvatureValue) | 0x0,
  (intptr_t)asn1_type_RAW_CurvatureValue,
  0,
  (intptr_t)"curvatureValue",

  offsetof(RAW_Curvature, curvatureConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_CurvatureConfidence,
  0,
  (intptr_t)"curvatureConfidence",

  (intptr_t)"Curvature",
};

const ASN1CType asn1_type_RAW_CurvatureValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xfffffc01,
  0x3ff,
  (intptr_t)"CurvatureValue",
};

const ASN1CType asn1_type_RAW_CurvatureConfidence[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  8,
  (intptr_t)"onePerMeter-0-00002",
  (intptr_t)"onePerMeter-0-0001",
  (intptr_t)"onePerMeter-0-0005",
  (intptr_t)"onePerMeter-0-002",
  (intptr_t)"onePerMeter-0-01",
  (intptr_t)"onePerMeter-0-1",
  (intptr_t)"outOfRange",
  (intptr_t)"unavailable",
  (intptr_t)"CurvatureConfidence",
};

const ASN1CType asn1_type_RAW_CurvatureCalculationMode[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100004,
  3,
  0,
  (intptr_t)"yawRateUsed",
  (intptr_t)"yawRateNotUsed",
  (intptr_t)"unavailable",
  (intptr_t)"CurvatureCalculationMode",
};

const ASN1CType asn1_type_RAW_YawRate[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100005,
  2,
  sizeof(RAW_YawRate),

  offsetof(RAW_YawRate, yawRateValue) | 0x0,
  (intptr_t)asn1_type_RAW_YawRateValue,
  0,
  (intptr_t)"yawRateValue",

  offsetof(RAW_YawRate, yawRateConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_YawRateConfidence,
  0,
  (intptr_t)"yawRateConfidence",

  (intptr_t)"YawRate",
};

const ASN1CType asn1_type_RAW_YawRateValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xffff8002,
  0x7fff,
  (intptr_t)"YawRateValue",
};

const ASN1CType asn1_type_RAW_YawRateConfidence[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  9,
  (intptr_t)"degSec-000-01",
  (intptr_t)"degSec-000-05",
  (intptr_t)"degSec-000-10",
  (intptr_t)"degSec-001-00",
  (intptr_t)"degSec-005-00",
  (intptr_t)"degSec-010-00",
  (intptr_t)"degSec-100-00",
  (intptr_t)"outOfRange",
  (intptr_t)"unavailable",
  (intptr_t)"YawRateConfidence",
};

const ASN1CType asn1_type_RAW_AccelerationConfidence[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x0,
  0x66,
  (intptr_t)"AccelerationConfidence",
};

const ASN1CType asn1_type_RAW_LateralAcceleration[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100006,
  2,
  sizeof(RAW_LateralAcceleration),

  offsetof(RAW_LateralAcceleration, lateralAccelerationValue) | 0x0,
  (intptr_t)asn1_type_RAW_LateralAccelerationValue,
  0,
  (intptr_t)"lateralAccelerationValue",

  offsetof(RAW_LateralAcceleration, lateralAccelerationConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_AccelerationConfidence,
  0,
  (intptr_t)"lateralAccelerationConfidence",

  (intptr_t)"LateralAcceleration",
};

const ASN1CType asn1_type_RAW_LateralAccelerationValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xffffff60,
  0xa1,
  (intptr_t)"LateralAccelerationValue",
};

const ASN1CType asn1_type_RAW_VerticalAcceleration[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100007,
  2,
  sizeof(RAW_VerticalAcceleration),

  offsetof(RAW_VerticalAcceleration, verticalAccelerationValue) | 0x0,
  (intptr_t)asn1_type_RAW_VerticalAccelerationValue,
  0,
  (intptr_t)"verticalAccelerationValue",

  offsetof(RAW_VerticalAcceleration, verticalAccelerationConfidence) | 0x0,
  (intptr_t)asn1_type_RAW_AccelerationConfidence,
  0,
  (intptr_t)"verticalAccelerationConfidence",

  (intptr_t)"VerticalAcceleration",
};

const ASN1CType asn1_type_RAW_VerticalAccelerationValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xffffff60,
  0xa1,
  (intptr_t)"VerticalAccelerationValue",
};

const ASN1CType asn1_type_RAW__local_12[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100003,
  (intptr_t)asn1_type_RAW_MapPosition,
};

const ASN1CType asn1_type_RAW_VruLanePosition[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100008,
  4,
  0,
  sizeof(RAW_VruLanePosition),
  offsetof(RAW_VruLanePosition, choice),
  offsetof(RAW_VruLanePosition, u),
  (intptr_t)asn1_type_RAW_OffRoadLanePosition,
  (intptr_t)"offRoadLanePosition",
  (intptr_t)asn1_type_RAW_LanePosition,
  (intptr_t)"vehicularLanePosition",
  (intptr_t)asn1_type_RAW_TrafficIslandPosition,
  (intptr_t)"trafficIslandPosition",
  (intptr_t)asn1_type_RAW__local_12,
  (intptr_t)"mapPosition",
  (intptr_t)"VruLanePosition",
};

const ASN1CType asn1_type_RAW_LanePosition[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0xffffffff,
  0xe,
  (intptr_t)"LanePosition",
};

const ASN1CType asn1_type_RAW_OffRoadLanePosition[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100000,
  5,
  (intptr_t)"unavailable",
  (intptr_t)"sidewalk",
  (intptr_t)"parkingLane",
  (intptr_t)"bikeLane",
  (intptr_t)"max",
  (intptr_t)"OffRoadLanePosition",
  0,
  1,
  2,
  3,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  15,
  4,
};

const ASN1CType asn1_type_RAW__local_13[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x2000000 | 0x100000,
  (intptr_t)asn1_type_RAW_NonIslandLanePosition,
};

const ASN1CType asn1_type_RAW__local_14[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x2000000 | 0x100001,
  (intptr_t)asn1_type_RAW_NonIslandLanePosition,
};

const ASN1CType asn1_type_RAW_TrafficIslandPosition[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100002,
  2,
  sizeof(RAW_TrafficIslandPosition),

  offsetof(RAW_TrafficIslandPosition, oneSide) | 0x0,
  (intptr_t)asn1_type_RAW__local_13,
  0,
  (intptr_t)"oneSide",

  offsetof(RAW_TrafficIslandPosition, otherSide) | 0x0,
  (intptr_t)asn1_type_RAW__local_14,
  0,
  (intptr_t)"otherSide",

  (intptr_t)"TrafficIslandPosition",
};

const ASN1CType asn1_type_RAW__local_15[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_MapPosition,
};

const ASN1CType asn1_type_RAW_NonIslandLanePosition[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x0,
  3,
  0,
  sizeof(RAW_NonIslandLanePosition),
  offsetof(RAW_NonIslandLanePosition, choice),
  offsetof(RAW_NonIslandLanePosition, u),
  (intptr_t)asn1_type_RAW_OffRoadLanePosition,
  (intptr_t)"offRoadLanePosition",
  (intptr_t)asn1_type_RAW_LanePosition,
  (intptr_t)"vehicularLanePosition",
  (intptr_t)asn1_type_RAW__local_15,
  (intptr_t)"mapPosition",
  (intptr_t)"NonIslandLanePosition",
};

const ASN1CType asn1_type_RAW_MapPosition[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_MapPosition),

  offsetof(RAW_MapPosition, intersectionId) | 0x0,
  (intptr_t)asn1_type_RAW_IntersectionReferenceID,
  0,
  (intptr_t)"intersectionId",

  offsetof(RAW_MapPosition, lane) | 0x0,
  (intptr_t)asn1_type_RAW_LaneID,
  0,
  (intptr_t)"lane",

  (intptr_t)"MapPosition",
};

const ASN1CType asn1_type_RAW_IntersectionReferenceID[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  2,
  sizeof(RAW_IntersectionReferenceID),

  offsetof(RAW_IntersectionReferenceID, region) | 0x8000000,
  (intptr_t)asn1_type_RAW_RoadRegulatorID,
  offsetof(RAW_IntersectionReferenceID, region_option),
  (intptr_t)"region",

  offsetof(RAW_IntersectionReferenceID, id) | 0x0,
  (intptr_t)asn1_type_RAW_IntersectionID,
  0,
  (intptr_t)"id",

  (intptr_t)"IntersectionReferenceID",
};

const ASN1CType asn1_type_RAW_RoadRegulatorID[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0xffff,
  (intptr_t)"RoadRegulatorID",
};

const ASN1CType asn1_type_RAW_IntersectionID[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x0,
  0xffff,
  (intptr_t)"IntersectionID",
};

const ASN1CType asn1_type_RAW_LaneID[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x0,
  0xff,
  (intptr_t)"LaneID",
};

const ASN1CType asn1_type_RAW_VruEnvironment[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100009,
  7,
  (intptr_t)"unavailable",
  (intptr_t)"intersectionCrossing",
  (intptr_t)"zebraCrossing",
  (intptr_t)"sidewalk",
  (intptr_t)"onVehicleRoad",
  (intptr_t)"protectedGeographicArea",
  (intptr_t)"max",
  (intptr_t)"VruEnvironment",
  0,
  1,
  2,
  3,
  4,
  5,
  255,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  255,
  6,
};

const ASN1CType asn1_type_RAW_VruMovementControl[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x10000a,
  8,
  (intptr_t)"unavailable",
  (intptr_t)"braking",
  (intptr_t)"hardBraking",
  (intptr_t)"stopPedaling",
  (intptr_t)"brakingAndStopPedaling",
  (intptr_t)"hardBrakingAndStopPedaling",
  (intptr_t)"noReaction",
  (intptr_t)"max",
  (intptr_t)"VruMovementControl",
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  255,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  6,
  6,
  255,
  7,
};

const ASN1CType asn1_type_RAW_VruOrientation[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10000b,
  (intptr_t)asn1_type_RAW_Heading,
  (intptr_t)"VruOrientation",
};

const ASN1CType asn1_type_RAW_VruRollAngle[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10000c,
  (intptr_t)asn1_type_RAW_Heading,
  (intptr_t)"VruRollAngle",
};

const ASN1CType asn1_type_RAW_VruDeviceUsage[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x10000d,
  10,
  (intptr_t)"unavailable",
  (intptr_t)"other",
  (intptr_t)"idle",
  (intptr_t)"listeningToAudio",
  (intptr_t)"typing",
  (intptr_t)"calling",
  (intptr_t)"playingGames",
  (intptr_t)"reading",
  (intptr_t)"viewing",
  (intptr_t)"max",
  (intptr_t)"VruDeviceUsage",
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  255,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  6,
  6,
  7,
  7,
  8,
  8,
  255,
  9,
};

const ASN1CType asn1_type_RAW_VruLowFrequencyContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100002,
  3,
  sizeof(RAW_VruLowFrequencyContainer),

  offsetof(RAW_VruLowFrequencyContainer, profileAndSubprofile) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruProfileAndSubprofile,
  offsetof(RAW_VruLowFrequencyContainer, profileAndSubprofile_option),
  (intptr_t)"profileAndSubprofile",

  offsetof(RAW_VruLowFrequencyContainer, exteriorLights) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruExteriorLights,
  offsetof(RAW_VruLowFrequencyContainer, exteriorLights_option),
  (intptr_t)"exteriorLights",

  offsetof(RAW_VruLowFrequencyContainer, sizeClass) | 0x8000000,
  (intptr_t)asn1_type_RAW_VruSizeClass,
  offsetof(RAW_VruLowFrequencyContainer, sizeClass_option),
  (intptr_t)"sizeClass",

  (intptr_t)"VruLowFrequencyContainer",
};

const ASN1CType asn1_type_RAW_VruProfileAndSubprofile[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100000,
  4,
  0,
  sizeof(RAW_VruProfileAndSubprofile),
  offsetof(RAW_VruProfileAndSubprofile, choice),
  offsetof(RAW_VruProfileAndSubprofile, u),
  (intptr_t)asn1_type_RAW_VruSubProfilePedestrian,
  (intptr_t)"pedestrian",
  (intptr_t)asn1_type_RAW_VruSubProfileBicyclist,
  (intptr_t)"bicyclist",
  (intptr_t)asn1_type_RAW_VruSubProfileMotorcyclist,
  (intptr_t)"motorcylist",
  (intptr_t)asn1_type_RAW_VruSubProfileAnimal,
  (intptr_t)"animal",
  (intptr_t)"VruProfileAndSubprofile",
};

const ASN1CType asn1_type_RAW_VruSubProfilePedestrian[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100000,
  5,
  (intptr_t)"unavailable",
  (intptr_t)"ordinary-pedestrian",
  (intptr_t)"road-worker",
  (intptr_t)"first-responder",
  (intptr_t)"max",
  (intptr_t)"VruSubProfilePedestrian",
  0,
  1,
  2,
  3,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  15,
  4,
};

const ASN1CType asn1_type_RAW_VruSubProfileBicyclist[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100001,
  10,
  (intptr_t)"unavailable",
  (intptr_t)"bicyclist",
  (intptr_t)"wheelchair-user",
  (intptr_t)"horse-and-rider",
  (intptr_t)"rollerskater",
  (intptr_t)"e-scooter",
  (intptr_t)"personal-transporter",
  (intptr_t)"pedelec",
  (intptr_t)"speed-pedelec",
  (intptr_t)"max",
  (intptr_t)"VruSubProfileBicyclist",
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  6,
  6,
  7,
  7,
  8,
  8,
  15,
  9,
};

const ASN1CType asn1_type_RAW_VruSubProfileMotorcyclist[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100002,
  6,
  (intptr_t)"unavailable",
  (intptr_t)"moped",
  (intptr_t)"motorcycle",
  (intptr_t)"motorcycle-and-sidecar-right",
  (intptr_t)"motorcycle-and-sidecar-left",
  (intptr_t)"max",
  (intptr_t)"VruSubProfileMotorcyclist",
  0,
  1,
  2,
  3,
  4,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  15,
  5,
};

const ASN1CType asn1_type_RAW_VruSubProfileAnimal[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100003,
  5,
  (intptr_t)"unavailable",
  (intptr_t)"wild-animal",
  (intptr_t)"farm-animal",
  (intptr_t)"service-animal",
  (intptr_t)"max",
  (intptr_t)"VruSubProfileAnimal",
  0,
  1,
  2,
  3,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  15,
  4,
};

const ASN1CType asn1_type_RAW_VruExteriorLights[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_VruExteriorLights),

  offsetof(RAW_VruExteriorLights, vruSpecific) | 0x0,
  (intptr_t)asn1_type_RAW_VruSpecificExteriorLights,
  0,
  (intptr_t)"vruSpecific",

  offsetof(RAW_VruExteriorLights, vehicular) | 0x0,
  (intptr_t)asn1_type_RAW_ExteriorLights,
  0,
  (intptr_t)"vehicular",

  (intptr_t)"VruExteriorLights",
};

const ASN1CType asn1_type_RAW_ExteriorLights[] = {
  (ASN1_CTYPE_BIT_STRING << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x8,
  0x8,
  (intptr_t)"ExteriorLights",
};

const ASN1CType asn1_type_RAW_VruSpecificExteriorLights[] = {
  (ASN1_CTYPE_BIT_STRING << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x8,
  0x8,
  (intptr_t)"VruSpecificExteriorLights",
};

const ASN1CType asn1_type_RAW_VruSizeClass[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100002,
  5,
  (intptr_t)"unavailable",
  (intptr_t)"low",
  (intptr_t)"medium",
  (intptr_t)"high",
  (intptr_t)"max",
  (intptr_t)"VruSizeClass",
  0,
  1,
  2,
  3,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  15,
  4,
};

const ASN1CType asn1_type_RAW_VruClusterInformationContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100003,
  4,
  sizeof(RAW_VruClusterInformationContainer),

  offsetof(RAW_VruClusterInformationContainer, clusterId) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterId,
  0,
  (intptr_t)"clusterId",

  offsetof(RAW_VruClusterInformationContainer, clusterBoundingBoxShape) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterBoundingBoxShape,
  0,
  (intptr_t)"clusterBoundingBoxShape",

  offsetof(RAW_VruClusterInformationContainer, clusterCardinalitySize) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterCardinalitySize,
  0,
  (intptr_t)"clusterCardinalitySize",

  offsetof(RAW_VruClusterInformationContainer, clusterProfiles) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterProfiles,
  0,
  (intptr_t)"clusterProfiles",

  (intptr_t)"VruClusterInformationContainer",
};

const ASN1CType asn1_type_RAW_ClusterId[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0xff,
  (intptr_t)"ClusterId",
};

const ASN1CType asn1_type_RAW_ClusterBoundingBoxShape[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100001,
  3,
  0,
  sizeof(RAW_ClusterBoundingBoxShape),
  offsetof(RAW_ClusterBoundingBoxShape, choice),
  offsetof(RAW_ClusterBoundingBoxShape, u),
  (intptr_t)asn1_type_RAW_AreaRectangle,
  (intptr_t)"clusterRectangle",
  (intptr_t)asn1_type_RAW_AreaCircular,
  (intptr_t)"clusterCircle",
  (intptr_t)asn1_type_RAW_AreaPolygon,
  (intptr_t)"clusterPolygon",
  (intptr_t)"ClusterBoundingBoxShape",
};

const ASN1CType asn1_type_RAW__local_16[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_OffsetPoint,
};

const ASN1CType asn1_type_RAW_AreaCircular[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_AreaCircular),

  offsetof(RAW_AreaCircular, nodeCenterPoint) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_16,
  offsetof(RAW_AreaCircular, nodeCenterPoint_option),
  (intptr_t)"nodeCenterPoint",

  offsetof(RAW_AreaCircular, radius) | 0x0,
  (intptr_t)asn1_type_RAW_Radius,
  0,
  (intptr_t)"radius",

  (intptr_t)"AreaCircular",
};

const ASN1CType asn1_type_RAW_AreaPolygon[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100002,
  1,
  sizeof(RAW_AreaPolygon),

  offsetof(RAW_AreaPolygon, polyPointList) | 0x0,
  (intptr_t)asn1_type_RAW_PolyPointList,
  0,
  (intptr_t)"polyPointList",

  (intptr_t)"AreaPolygon",
};

const ASN1CType asn1_type_RAW__local_17[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_OffsetPoint,
};

const ASN1CType asn1_type_RAW__local_18[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_SemiRangeLength,
};

const ASN1CType asn1_type_RAW__local_19[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_SemiRangeLength,
};

const ASN1CType asn1_type_RAW__local_20[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100004,
  (intptr_t)asn1_type_RAW_SemiRangeLength,
};

const ASN1CType asn1_type_RAW_AreaRectangle[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  5,
  sizeof(RAW_AreaRectangle),

  offsetof(RAW_AreaRectangle, nodeCenterPoint) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_17,
  offsetof(RAW_AreaRectangle, nodeCenterPoint_option),
  (intptr_t)"nodeCenterPoint",

  offsetof(RAW_AreaRectangle, semiMajorRangeLength) | 0x0,
  (intptr_t)asn1_type_RAW__local_18,
  0,
  (intptr_t)"semiMajorRangeLength",

  offsetof(RAW_AreaRectangle, semiMinorRangeLength) | 0x0,
  (intptr_t)asn1_type_RAW__local_19,
  0,
  (intptr_t)"semiMinorRangeLength",

  offsetof(RAW_AreaRectangle, semiMajorRangeOrientation) | 0x0,
  (intptr_t)asn1_type_RAW_WGS84AngleValue,
  0,
  (intptr_t)"semiMajorRangeOrientation",

  offsetof(RAW_AreaRectangle, semiHeight) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_20,
  offsetof(RAW_AreaRectangle, semiHeight_option),
  (intptr_t)"semiHeight",

  (intptr_t)"AreaRectangle",
};

const ASN1CType asn1_type_RAW_OffsetPoint[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_OffsetPoint),

  offsetof(RAW_OffsetPoint, nodeOffsetPointXY) | 0x0,
  (intptr_t)asn1_type_RAW_NodeOffsetPointXY,
  0,
  (intptr_t)"nodeOffsetPointXY",

  offsetof(RAW_OffsetPoint, nodeOffsetPointZ) | 0x8000000,
  (intptr_t)asn1_type_RAW_NodeOffsetPointZ,
  offsetof(RAW_OffsetPoint, nodeOffsetPointZ_option),
  (intptr_t)"nodeOffsetPointZ",

  (intptr_t)"OffsetPoint",
};

const ASN1CType asn1_type_RAW_NodeOffsetPointXY[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  8,
  sizeof(RAW_NodeOffsetPointXY),
  offsetof(RAW_NodeOffsetPointXY, choice),
  offsetof(RAW_NodeOffsetPointXY, u),
  (intptr_t)asn1_type_RAW_Node_XY_20b,
  (intptr_t)"node-XY1",
  (intptr_t)asn1_type_RAW_Node_XY_22b,
  (intptr_t)"node-XY2",
  (intptr_t)asn1_type_RAW_Node_XY_24b,
  (intptr_t)"node-XY3",
  (intptr_t)asn1_type_RAW_Node_XY_26b,
  (intptr_t)"node-XY4",
  (intptr_t)asn1_type_RAW_Node_XY_28b,
  (intptr_t)"node-XY5",
  (intptr_t)asn1_type_RAW_Node_XY_32b,
  (intptr_t)"node-XY6",
  (intptr_t)asn1_type_RAW_Node_LLmD_64b,
  (intptr_t)"node-LatLon",
  (intptr_t)asn1_type_RAW_RegionalExtension_1,
  (intptr_t)"regional",
  (intptr_t)"NodeOffsetPointXY",
};

const ASN1CType asn1_type_RAW_REG_EXT_ID_AND_TYPE[] = {
  (ASN1_CTYPE_OBJECT_CLASS << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x0,
  2,

  0x1,
  (intptr_t)asn1_type_RAW_RegionId,
  0,
  (intptr_t)"&id",

  0x0,
  0,
  0,
  (intptr_t)"&Type",
  (intptr_t)"REG-EXT-ID-AND-TYPE",
};

const ASN1CType asn1_type_RAW__local_21[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_RegionId,
};

static const ASN1CType asn1_constraint__local_23[] = {
  ASN1_CCONSTRAINT_TABLE,
  (intptr_t)asn1_type_RAW_REG_EXT_ID_AND_TYPE,
  1,
  0,
  0,
  1,
  0,
  0x80000000,
  0,
};

const ASN1CType asn1_type_RAW__local_22[] = {
  (ASN1_CTYPE_ANY << ASN1_CTYPE_SHIFT) | 0x200000 | 0x100001,
  (intptr_t)asn1_constraint__local_23,
};

const ASN1CType asn1_type_RAW_RegionalExtension_1[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x0 | 0x100007,
  2,
  sizeof(RAW_RegionalExtension_1),

  offsetof(RAW_RegionalExtension_1, regionId) | 0x0,
  (intptr_t)asn1_type_RAW__local_21,
  0,
  (intptr_t)"regionId",

  offsetof(RAW_RegionalExtension_1, regExtValue) | 0x0,
  (intptr_t)asn1_type_RAW__local_22,
  0,
  (intptr_t)"regExtValue",

};

const ASN1CType asn1_type_RAW_RegionId[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0xff,
  (intptr_t)"RegionId",
};

const ASN1CType asn1_type_RAW__local_25[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Longitude,
};

const ASN1CType asn1_type_RAW__local_26[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Latitude,
};

const ASN1CType asn1_type_RAW_Node_LLmD_64b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100006,
  2,
  sizeof(RAW_Node_LLmD_64b),

  offsetof(RAW_Node_LLmD_64b, lon) | 0x0,
  (intptr_t)asn1_type_RAW__local_25,
  0,
  (intptr_t)"lon",

  offsetof(RAW_Node_LLmD_64b, lat) | 0x0,
  (intptr_t)asn1_type_RAW__local_26,
  0,
  (intptr_t)"lat",

  (intptr_t)"Node-LLmD-64b",
};

const ASN1CType asn1_type_RAW__local_27[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B10,
};

const ASN1CType asn1_type_RAW__local_28[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B10,
};

const ASN1CType asn1_type_RAW_Node_XY_20b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  2,
  sizeof(RAW_Node_XY_20b),

  offsetof(RAW_Node_XY_20b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_27,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_20b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_28,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-20b",
};

const ASN1CType asn1_type_RAW__local_29[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B11,
};

const ASN1CType asn1_type_RAW__local_30[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B11,
};

const ASN1CType asn1_type_RAW_Node_XY_22b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  2,
  sizeof(RAW_Node_XY_22b),

  offsetof(RAW_Node_XY_22b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_29,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_22b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_30,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-22b",
};

const ASN1CType asn1_type_RAW__local_31[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B12,
};

const ASN1CType asn1_type_RAW__local_32[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B12,
};

const ASN1CType asn1_type_RAW_Node_XY_24b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100002,
  2,
  sizeof(RAW_Node_XY_24b),

  offsetof(RAW_Node_XY_24b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_31,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_24b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_32,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-24b",
};

const ASN1CType asn1_type_RAW__local_33[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B13,
};

const ASN1CType asn1_type_RAW__local_34[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B13,
};

const ASN1CType asn1_type_RAW_Node_XY_26b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100003,
  2,
  sizeof(RAW_Node_XY_26b),

  offsetof(RAW_Node_XY_26b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_33,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_26b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_34,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-26b",
};

const ASN1CType asn1_type_RAW__local_35[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B14,
};

const ASN1CType asn1_type_RAW__local_36[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B14,
};

const ASN1CType asn1_type_RAW_Node_XY_28b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100004,
  2,
  sizeof(RAW_Node_XY_28b),

  offsetof(RAW_Node_XY_28b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_35,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_28b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_36,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-28b",
};

const ASN1CType asn1_type_RAW__local_37[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B16,
};

const ASN1CType asn1_type_RAW__local_38[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B16,
};

const ASN1CType asn1_type_RAW_Node_XY_32b[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100005,
  2,
  sizeof(RAW_Node_XY_32b),

  offsetof(RAW_Node_XY_32b, x) | 0x0,
  (intptr_t)asn1_type_RAW__local_37,
  0,
  (intptr_t)"x",

  offsetof(RAW_Node_XY_32b, y) | 0x0,
  (intptr_t)asn1_type_RAW__local_38,
  0,
  (intptr_t)"y",

  (intptr_t)"Node-XY-32b",
};

const ASN1CType asn1_type_RAW__local_39[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_Offset_B10,
};

const ASN1CType asn1_type_RAW__local_40[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_Offset_B11,
};

const ASN1CType asn1_type_RAW__local_41[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_Offset_B12,
};

const ASN1CType asn1_type_RAW__local_42[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100003,
  (intptr_t)asn1_type_RAW_Offset_B13,
};

const ASN1CType asn1_type_RAW__local_43[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100004,
  (intptr_t)asn1_type_RAW_Offset_B14,
};

const ASN1CType asn1_type_RAW__local_44[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100005,
  (intptr_t)asn1_type_RAW_Offset_B16,
};

const ASN1CType asn1_type_RAW_NodeOffsetPointZ[] = {
  (ASN1_CTYPE_CHOICE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  6,
  sizeof(RAW_NodeOffsetPointZ),
  offsetof(RAW_NodeOffsetPointZ, choice),
  offsetof(RAW_NodeOffsetPointZ, u),
  (intptr_t)asn1_type_RAW__local_39,
  (intptr_t)"node-Z1",
  (intptr_t)asn1_type_RAW__local_40,
  (intptr_t)"node-Z2",
  (intptr_t)asn1_type_RAW__local_41,
  (intptr_t)"node-Z3",
  (intptr_t)asn1_type_RAW__local_42,
  (intptr_t)"node-Z4",
  (intptr_t)asn1_type_RAW__local_43,
  (intptr_t)"node-Z5",
  (intptr_t)asn1_type_RAW__local_44,
  (intptr_t)"node-Z6",
  (intptr_t)"NodeOffsetPointZ",
};

const ASN1CType asn1_type_RAW_Offset_B10[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xfffffe00,
  0x1ff,
  (intptr_t)"Offset-B10",
};

const ASN1CType asn1_type_RAW_Offset_B11[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xfffffc00,
  0x3ff,
  (intptr_t)"Offset-B11",
};

const ASN1CType asn1_type_RAW_Offset_B12[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xfffff800,
  0x7ff,
  (intptr_t)"Offset-B12",
};

const ASN1CType asn1_type_RAW_Offset_B13[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xfffff000,
  0xfff,
  (intptr_t)"Offset-B13",
};

const ASN1CType asn1_type_RAW_Offset_B14[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xffffe000,
  0x1fff,
  (intptr_t)"Offset-B14",
};

const ASN1CType asn1_type_RAW_Offset_B16[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0xffff8000,
  0x7fff,
  (intptr_t)"Offset-B16",
};

const ASN1CType asn1_type_RAW_Radius[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x0,
  0x2710,
  (intptr_t)"Radius",
};

const ASN1CType asn1_type_RAW_PolyPointList[] = {
  (ASN1_CTYPE_SEQUENCE_OF << ASN1_CTYPE_SHIFT) | 0x7800000 | 0x100000,
  0x3,
  0x10,
  sizeof(RAW_OffsetPoint),
  (intptr_t)asn1_type_RAW_OffsetPoint,
  0,
  (intptr_t)"PolyPointList",
};

const ASN1CType asn1_type_RAW_SemiRangeLength[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0x2710,
  (intptr_t)"SemiRangeLength",
};

const ASN1CType asn1_type_RAW_WGS84AngleValue[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100003,
  0x0,
  0xe11,
  (intptr_t)"WGS84AngleValue",
};

const ASN1CType asn1_type_RAW_ClusterCardinalitySize[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100002,
  0x0,
  0xff,
  (intptr_t)"ClusterCardinalitySize",
};

const ASN1CType asn1_type_RAW_ClusterProfiles[] = {
  (ASN1_CTYPE_BIT_STRING << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100003,
  0x4,
  0x4,
  (intptr_t)"ClusterProfiles",
};

const ASN1CType asn1_type_RAW__local_45[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100003,
  (intptr_t)asn1_type_RAW_VruClusterOpTimestamp,
};

const ASN1CType asn1_type_RAW_VruClusterOperationContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100004,
  4,
  sizeof(RAW_VruClusterOperationContainer),

  offsetof(RAW_VruClusterOperationContainer, clusterJoinInfo) | 0x8000000,
  (intptr_t)asn1_type_RAW_ClusterJoinInfo,
  offsetof(RAW_VruClusterOperationContainer, clusterJoinInfo_option),
  (intptr_t)"clusterJoinInfo",

  offsetof(RAW_VruClusterOperationContainer, clusterLeaveInfo) | 0x8000000,
  (intptr_t)asn1_type_RAW_ClusterLeaveInfo,
  offsetof(RAW_VruClusterOperationContainer, clusterLeaveInfo_option),
  (intptr_t)"clusterLeaveInfo",

  offsetof(RAW_VruClusterOperationContainer, clusterBreakupInfo) | 0x8000000,
  (intptr_t)asn1_type_RAW_ClusterBreakupInfo,
  offsetof(RAW_VruClusterOperationContainer, clusterBreakupInfo_option),
  (intptr_t)"clusterBreakupInfo",

  offsetof(RAW_VruClusterOperationContainer, clusterIdChangeTimeInfo) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_45,
  offsetof(RAW_VruClusterOperationContainer, clusterIdChangeTimeInfo_option),
  (intptr_t)"clusterIdChangeTimeInfo",

  (intptr_t)"VruClusterOperationContainer",
};

const ASN1CType asn1_type_RAW_VruClusterOpTimestamp[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x1,
  0xff,
  (intptr_t)"VruClusterOpTimestamp",
};

const ASN1CType asn1_type_RAW__local_46[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_VruClusterOpTimestamp,
};

const ASN1CType asn1_type_RAW_ClusterJoinInfo[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100000,
  2,
  sizeof(RAW_ClusterJoinInfo),

  offsetof(RAW_ClusterJoinInfo, clusterId) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterId,
  0,
  (intptr_t)"clusterId",

  offsetof(RAW_ClusterJoinInfo, joinTime) | 0x0,
  (intptr_t)asn1_type_RAW__local_46,
  0,
  (intptr_t)"joinTime",

  (intptr_t)"ClusterJoinInfo",
};

const ASN1CType asn1_type_RAW_ClusterLeaveInfo[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100001,
  2,
  sizeof(RAW_ClusterLeaveInfo),

  offsetof(RAW_ClusterLeaveInfo, clusterId) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterId,
  0,
  (intptr_t)"clusterId",

  offsetof(RAW_ClusterLeaveInfo, clusterLeaveReason) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterLeaveReason,
  0,
  (intptr_t)"clusterLeaveReason",

  (intptr_t)"ClusterLeaveInfo",
};

const ASN1CType asn1_type_RAW__local_47[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_VruClusterOpTimestamp,
};

const ASN1CType asn1_type_RAW_ClusterBreakupInfo[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100002,
  2,
  sizeof(RAW_ClusterBreakupInfo),

  offsetof(RAW_ClusterBreakupInfo, clusterBreakupReason) | 0x0,
  (intptr_t)asn1_type_RAW_ClusterBreakupReason,
  0,
  (intptr_t)"clusterBreakupReason",

  offsetof(RAW_ClusterBreakupInfo, breakupTime) | 0x0,
  (intptr_t)asn1_type_RAW__local_47,
  0,
  (intptr_t)"breakupTime",

  (intptr_t)"ClusterBreakupInfo",
};

const ASN1CType asn1_type_RAW_ClusterLeaveReason[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100001,
  10,
  (intptr_t)"notProvided",
  (intptr_t)"clusterLeaderLost",
  (intptr_t)"clusterDisbandedByLeader",
  (intptr_t)"outOfClusterBoundingBox",
  (intptr_t)"outOfClusterSpeedRange",
  (intptr_t)"joiningAnotherCluster",
  (intptr_t)"cancelledJoin",
  (intptr_t)"failedJoin",
  (intptr_t)"safetyCondition",
  (intptr_t)"max",
  (intptr_t)"ClusterLeaveReason",
  0,
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  6,
  6,
  7,
  7,
  8,
  8,
  15,
  9,
};

const ASN1CType asn1_type_RAW_ClusterBreakupReason[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100000,
  7,
  (intptr_t)"notProvided",
  (intptr_t)"clusteringPurposeCompleted",
  (intptr_t)"leaderMovedOutOfClusterBoundingBox",
  (intptr_t)"joiningAnotherCluster",
  (intptr_t)"enteringLowRiskAreaBasedOnMaps",
  (intptr_t)"receptionOfCpmContainingCluster",
  (intptr_t)"max",
  (intptr_t)"ClusterBreakupReason",
  0,
  1,
  2,
  3,
  4,
  5,
  15,
  0,
  0,
  1,
  1,
  2,
  2,
  3,
  3,
  4,
  4,
  5,
  5,
  15,
  6,
};

const ASN1CType asn1_type_RAW_VruMotionPredictionContainer[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100005,
  7,
  sizeof(RAW_VruMotionPredictionContainer),

  offsetof(RAW_VruMotionPredictionContainer, pathHistory) | 0x8000000,
  (intptr_t)asn1_type_RAW_PathHistory,
  offsetof(RAW_VruMotionPredictionContainer, pathHistory_option),
  (intptr_t)"pathHistory",

  offsetof(RAW_VruMotionPredictionContainer, pathPrediction) | 0x8000000,
  (intptr_t)asn1_type_RAW_SequenceOfVruPathPoint,
  offsetof(RAW_VruMotionPredictionContainer, pathPrediction_option),
  (intptr_t)"pathPrediction",

  offsetof(RAW_VruMotionPredictionContainer, safeDistance) | 0x8000000,
  (intptr_t)asn1_type_RAW_SequenceOfVruSafeDistanceIndication,
  offsetof(RAW_VruMotionPredictionContainer, safeDistance_option),
  (intptr_t)"safeDistance",

  offsetof(RAW_VruMotionPredictionContainer, trajectoryInterceptionIndication) | 0x8000000,
  (intptr_t)asn1_type_RAW_SequenceOfTrajectoryInterceptionIndication,
  offsetof(RAW_VruMotionPredictionContainer, trajectoryInterceptionIndication_option),
  (intptr_t)"trajectoryInterceptionIndication",

  offsetof(RAW_VruMotionPredictionContainer, accelerationChangeIndication) | 0x8000000,
  (intptr_t)asn1_type_RAW_AccelerationChangeIndication,
  offsetof(RAW_VruMotionPredictionContainer, accelerationChangeIndication_option),
  (intptr_t)"accelerationChangeIndication",

  offsetof(RAW_VruMotionPredictionContainer, headingChangeIndication) | 0x8000000,
  (intptr_t)asn1_type_RAW_HeadingChangeIndication,
  offsetof(RAW_VruMotionPredictionContainer, headingChangeIndication_option),
  (intptr_t)"headingChangeIndication",

  offsetof(RAW_VruMotionPredictionContainer, stabilityChangeIndication) | 0x8000000,
  (intptr_t)asn1_type_RAW_StabilityChangeIndication,
  offsetof(RAW_VruMotionPredictionContainer, stabilityChangeIndication_option),
  (intptr_t)"stabilityChangeIndication",

  (intptr_t)"VruMotionPredictionContainer",
};

const ASN1CType asn1_type_RAW_PathHistory[] = {
  (ASN1_CTYPE_SEQUENCE_OF << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0x28,
  sizeof(RAW_PathPoint),
  (intptr_t)asn1_type_RAW_PathPoint,
  0,
  (intptr_t)"PathHistory",
};

const ASN1CType asn1_type_RAW_PathPoint[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_PathPoint),

  offsetof(RAW_PathPoint, pathPosition) | 0x0,
  (intptr_t)asn1_type_RAW_DeltaReferencePosition,
  0,
  (intptr_t)"pathPosition",

  offsetof(RAW_PathPoint, pathDeltaTime) | 0x8000000,
  (intptr_t)asn1_type_RAW_PathDeltaTime,
  offsetof(RAW_PathPoint, pathDeltaTime_option),
  (intptr_t)"pathDeltaTime",

  (intptr_t)"PathPoint",
};

const ASN1CType asn1_type_RAW_PathDeltaTime[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x7800000 | 0x100001,
  0x1,
  0xffff,
  (intptr_t)"PathDeltaTime",
};

const ASN1CType asn1_type_RAW_DeltaReferencePosition[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  3,
  sizeof(RAW_DeltaReferencePosition),

  offsetof(RAW_DeltaReferencePosition, deltaLatitude) | 0x0,
  (intptr_t)asn1_type_RAW_DeltaLatitude,
  0,
  (intptr_t)"deltaLatitude",

  offsetof(RAW_DeltaReferencePosition, deltaLongitude) | 0x0,
  (intptr_t)asn1_type_RAW_DeltaLongitude,
  0,
  (intptr_t)"deltaLongitude",

  offsetof(RAW_DeltaReferencePosition, deltaAltitude) | 0x0,
  (intptr_t)asn1_type_RAW_DeltaAltitude,
  0,
  (intptr_t)"deltaAltitude",

  (intptr_t)"DeltaReferencePosition",
};

const ASN1CType asn1_type_RAW_DeltaLongitude[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0xfffe0001,
  0x20000,
  (intptr_t)"DeltaLongitude",
};

const ASN1CType asn1_type_RAW_DeltaLatitude[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0xfffe0001,
  0x20000,
  (intptr_t)"DeltaLatitude",
};

const ASN1CType asn1_type_RAW_DeltaAltitude[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100002,
  0xffffce64,
  0x3200,
  (intptr_t)"DeltaAltitude",
};

const ASN1CType asn1_type_RAW_SequenceOfVruPathPoint[] = {
  (ASN1_CTYPE_SEQUENCE_OF << ASN1_CTYPE_SHIFT) | 0x5000000 | 0x100001,
  0x0,
  sizeof(RAW_VruPathPoint),
  (intptr_t)asn1_type_RAW_VruPathPoint,
  0,
  (intptr_t)"SequenceOfVruPathPoint",
};

const ASN1CType asn1_type_RAW__local_48[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_ReferencePosition,
};

const ASN1CType asn1_type_RAW_VruPathPoint[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x10,
  2,
  sizeof(RAW_VruPathPoint),

  offsetof(RAW_VruPathPoint, pathPosition) | 0x0,
  (intptr_t)asn1_type_RAW__local_48,
  0,
  (intptr_t)"pathPosition",

  offsetof(RAW_VruPathPoint, pathDeltaTime) | 0x8000000,
  (intptr_t)asn1_type_RAW_PathDeltaTime,
  offsetof(RAW_VruPathPoint, pathDeltaTime_option),
  (intptr_t)"pathDeltaTime",

  (intptr_t)"VruPathPoint",
};

const ASN1CType asn1_type_RAW_SequenceOfVruSafeDistanceIndication[] = {
  (ASN1_CTYPE_SEQUENCE_OF << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100002,
  0x1,
  0x8,
  sizeof(RAW_VruSafeDistanceIndication),
  (intptr_t)asn1_type_RAW_VruSafeDistanceIndication,
  0,
  (intptr_t)"SequenceOfVruSafeDistanceIndication",
};

const ASN1CType asn1_type_RAW__local_49[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_StationID,
};

const ASN1CType asn1_type_RAW__local_50[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100002,
  (intptr_t)asn1_type_RAW_ActionDeltaTime,
};

const ASN1CType asn1_type_RAW_VruSafeDistanceIndication[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x10,
  3,
  sizeof(RAW_VruSafeDistanceIndication),

  offsetof(RAW_VruSafeDistanceIndication, subjectStation) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_49,
  offsetof(RAW_VruSafeDistanceIndication, subjectStation_option),
  (intptr_t)"subjectStation",

  offsetof(RAW_VruSafeDistanceIndication, stationSafeDistanceIndication) | 0x0,
  (intptr_t)asn1_type_RAW_StationSafeDistanceIndication,
  0,
  (intptr_t)"stationSafeDistanceIndication",

  offsetof(RAW_VruSafeDistanceIndication, timeToCollision) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_50,
  offsetof(RAW_VruSafeDistanceIndication, timeToCollision_option),
  (intptr_t)"timeToCollision",

  (intptr_t)"VruSafeDistanceIndication",
};

const ASN1CType asn1_type_RAW_StationSafeDistanceIndication[] = {
  (ASN1_CTYPE_BOOLEAN << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100001,
  (intptr_t)"StationSafeDistanceIndication",
};

const ASN1CType asn1_type_RAW_SequenceOfTrajectoryInterceptionIndication[] = {
  (ASN1_CTYPE_SEQUENCE_OF << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100003,
  0x1,
  0x8,
  sizeof(RAW_TrajectoryInterceptionIndication),
  (intptr_t)asn1_type_RAW_TrajectoryInterceptionIndication,
  0,
  (intptr_t)"SequenceOfTrajectoryInterceptionIndication",
};

const ASN1CType asn1_type_RAW__local_51[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100000,
  (intptr_t)asn1_type_RAW_StationID,
};

const ASN1CType asn1_type_RAW_TrajectoryInterceptionIndication[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x10,
  3,
  sizeof(RAW_TrajectoryInterceptionIndication),

  offsetof(RAW_TrajectoryInterceptionIndication, subjectStation) | 0x8000000,
  (intptr_t)asn1_type_RAW__local_51,
  offsetof(RAW_TrajectoryInterceptionIndication, subjectStation_option),
  (intptr_t)"subjectStation",

  offsetof(RAW_TrajectoryInterceptionIndication, trajectoryInterceptionProbability) | 0x0,
  (intptr_t)asn1_type_RAW_TrajectoryInterceptionProbability,
  0,
  (intptr_t)"trajectoryInterceptionProbability",

  offsetof(RAW_TrajectoryInterceptionIndication, trajectoryInterceptionConfidence) | 0x8000000,
  (intptr_t)asn1_type_RAW_TrajectoryInterceptionConfidence,
  offsetof(RAW_TrajectoryInterceptionIndication, trajectoryInterceptionConfidence_option),
  (intptr_t)"trajectoryInterceptionConfidence",

  (intptr_t)"TrajectoryInterceptionIndication",
};

const ASN1CType asn1_type_RAW_TrajectoryInterceptionProbability[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100001,
  0x0,
  0x3f,
  (intptr_t)"TrajectoryInterceptionProbability",
};

const ASN1CType asn1_type_RAW_TrajectoryInterceptionConfidence[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100002,
  0x0,
  0x3,
  (intptr_t)"TrajectoryInterceptionConfidence",
};

const ASN1CType asn1_type_RAW__local_52[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_ActionDeltaTime,
};

const ASN1CType asn1_type_RAW_HeadingChangeIndication[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100005,
  2,
  sizeof(RAW_HeadingChangeIndication),

  offsetof(RAW_HeadingChangeIndication, direction) | 0x0,
  (intptr_t)asn1_type_RAW_LeftOrRight,
  0,
  (intptr_t)"direction",

  offsetof(RAW_HeadingChangeIndication, actionDeltaTime) | 0x0,
  (intptr_t)asn1_type_RAW__local_52,
  0,
  (intptr_t)"actionDeltaTime",

  (intptr_t)"HeadingChangeIndication",
};

const ASN1CType asn1_type_RAW_LeftOrRight[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  2,
  (intptr_t)"left",
  (intptr_t)"right",
  (intptr_t)"LeftOrRight",
};

const ASN1CType asn1_type_RAW_ActionDeltaTime[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x2,
  0x0,
  0x7f,
  (intptr_t)"ActionDeltaTime",
};

const ASN1CType asn1_type_RAW__local_53[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_ActionDeltaTime,
};

const ASN1CType asn1_type_RAW_AccelerationChangeIndication[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100004,
  2,
  sizeof(RAW_AccelerationChangeIndication),

  offsetof(RAW_AccelerationChangeIndication, accelOrDecel) | 0x0,
  (intptr_t)asn1_type_RAW_AccelOrDecel,
  0,
  (intptr_t)"accelOrDecel",

  offsetof(RAW_AccelerationChangeIndication, actionDeltaTime) | 0x0,
  (intptr_t)asn1_type_RAW__local_53,
  0,
  (intptr_t)"actionDeltaTime",

  (intptr_t)"AccelerationChangeIndication",
};

const ASN1CType asn1_type_RAW_AccelOrDecel[] = {
  (ASN1_CTYPE_ENUMERATED << ASN1_CTYPE_SHIFT) | 0x4000000 | 0x100000,
  2,
  (intptr_t)"accelerate",
  (intptr_t)"decelerate",
  (intptr_t)"AccelOrDecel",
};

const ASN1CType asn1_type_RAW__local_54[] = {
  (ASN1_CTYPE_TAGGED << ASN1_CTYPE_SHIFT) | 0x0 | 0x100001,
  (intptr_t)asn1_type_RAW_ActionDeltaTime,
};

const ASN1CType asn1_type_RAW_StabilityChangeIndication[] = {
  (ASN1_CTYPE_SEQUENCE << ASN1_CTYPE_SHIFT) | 0x6000000 | 0x100006,
  2,
  sizeof(RAW_StabilityChangeIndication),

  offsetof(RAW_StabilityChangeIndication, lossProbability) | 0x0,
  (intptr_t)asn1_type_RAW_StabilityLossProbability,
  0,
  (intptr_t)"lossProbability",

  offsetof(RAW_StabilityChangeIndication, actionDeltaTime) | 0x0,
  (intptr_t)asn1_type_RAW__local_54,
  0,
  (intptr_t)"actionDeltaTime",

  (intptr_t)"StabilityChangeIndication",
};

const ASN1CType asn1_type_RAW_StabilityLossProbability[] = {
  (ASN1_CTYPE_INTEGER << ASN1_CTYPE_SHIFT) | 0x5800000 | 0x100000,
  0x0,
  0x3f,
  (intptr_t)"StabilityLossProbability",
};

