#pragma once
/**
 * @addtogroup ta_api Threat Arbitrator (TA) API
 * @{
 *
 * The Cohda Threat Arbitrator is used to detect and warn drivers.
 *
 * This module contains utility functions for the TA Threat Applications
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TA_UTIL_H__
#define __TA_UTIL_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "TA.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// TA inhibit masks
typedef enum
{
  TA_INHIBIT_NONE                  = 0x00000000, ///< Useful value for indicating no inhibit checks
  TA_INHIBIT_ALL                   = 0xFFFFFFFF, ///< Useful value for indicating all inhibit checks

  TA_INHIBIT_VEH_SPEED_UNDER       = 0x00000001, ///< Vehicle speed < CW_*_INHIBIT_SPEED_MIN
  TA_INHIBIT_VEH_SPEED_OVER        = 0x00000002, ///< Vehicle speed > CW_*_INHIBIT_SPEED_MAX
  TA_INHIBIT_VEH_YAW_UNDER         = 0x00000004, ///< Vehicle abs(yaw) < CW_*_INHIBIT_YAW_MIN
  TA_INHIBIT_VEH_YAW_OVER          = 0x00000008, ///< Vehicle abs(yaw) > CW_*_INHIBIT_YAW_MAX
  TA_INHIBIT_VEH_STEER_UNDER       = 0x00000010, ///< Vehicle abs(steering angle) < CW_*_INHIBIT_STEER_ANGLE_MIN
  TA_INHIBIT_VEH_STEER_OVER        = 0x00000020, ///< Vehicle abs(steering angle) > CW_*_INHIBIT_STEER_ANGLE_MAX
  TA_INHIBIT_VEH_BRAKE_UNDER       = 0x00000040, ///< Vehicle brake % < CW_*_INHIBIT_BRAKE_MIN
  TA_INHIBIT_VEH_BRAKE_OVER        = 0x00000080, ///< Vehicle brake % > CW_*_INHIBIT_BRAKE_MAX
  TA_INHIBIT_VEH_THROTTLE_UNDER    = 0x00000100, ///< Vehicle throttle % < CW_*_INHIBIT_THROTTLE_MIN
  TA_INHIBIT_VEH_THROTTLE_OVER     = 0x00000200, ///< Vehicle throttle % > CW_*_INHIBIT_THROTTLE_MAX
  TA_INHIBIT_VEH_LONACCEL_UNDER    = 0x00000400, ///< Vehicle acceleration < CW_*_INHIBIT_LONACCEL_MIN
  TA_INHIBIT_VEH_LONACCEL_OVER     = 0x00000800, ///< Vehicle acceleration > CW_*_INHIBIT_LONACCEL_MAX

  TA_INHIBIT_VEH_STEER_RATE_UNDER  = 0x00001000, ///< Vehicle abs(steering angle rate) < CW_*_INHIBIT_STEER_RATE_MIN
  TA_INHIBIT_VEH_STEER_RATE_OVER   = 0x00002000, ///< Vehicle abs(steering angle rate) > CW_*_INHIBIT_STEER_RATE_MAX
  TA_INHIBIT_VEH_BRAKE_RATE_UNDER  = 0x00004000, ///< Vehicle brake angle rate < CW_*_INHIBIT_BRAKE_RATE_MIN
  TA_INHIBIT_VEH_BRAKE_RATE_OVER   = 0x00008000, ///< Vehicle brake angle rate > CW_*_INHIBIT_BRAKE_RATE_MAX
  TA_INHIBIT_VEH_BRAKE_KPA_UNDER   = 0x00010000, ///< Vehicle brake pressure < CW_*_INHIBIT_BRAKE_KPA_MIN
  TA_INHIBIT_VEH_BRAKE_KPA_OVER    = 0x00020000, ///< Vehicle brake pressure > CW_*_INHIBIT_BRAKE_KPA_MAX
  /// Vehicle not in same/near lane and steering away from the other
  /// (abs(RV.TC.LatOffset) > CW_*_INHIBIT_LATOFFSET_MAX) &&
  /// (sign(RV.TC.LatOffset) != sign(steering angle))
  TA_INHIBIT_VEH_STEERING_AWAY     = 0x00040000,
  /// Vehicle not in same/near lane and turning away from the other
  /// (abs(RV.TC.LatOffset) > CW_*_INHIBIT_LATOFFSET_MAX) &&
  /// (sign(RV.TC.LatOffset) != sign(indicators))
  TA_INHIBIT_VEH_INDICATING_AWAY   = 0x00080000,
} eTAInhibitMask;
/// @copydoc eTAInhibitMask
typedef uint32_t tTAInhibitMask;

/// Vehicle path types
typedef enum {
  /// Vehicle is travelling in a straight line
  TA_PATH_STRAIGHT,
  /// Vehicle is travelling on a curve
  TA_PATH_CURVE,
  /// Vehicle is transitioning between _STRAIGHT and _CURVE
  TA_PATH_TRANSITION,
} eTAPathType;

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef struct TA_InhibitLimits
{
  /// @ref TA_INHIBIT_VEH_SPEED_UNDER
  float   SpeedMin_mmpnm;
  /// @ref TA_INHIBIT_VEH_SPEED_OVER
  float   SpeedMax_mmpnm;
  /// @ref TA_INHIBIT_VEH_YAW_UNDER
  int32_t YawMin_vsc3;
  /// @ref TA_INHIBIT_VEH_YAW_OVER
  int32_t YawMax_vsc3;
  /// @ref TA_INHIBIT_VEH_STEER_UNDER
  int32_t SteerAngleMin_vsc3;
  /// @ref TA_INHIBIT_VEH_STEER_OVER
  int32_t SteerAngleMax_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_UNDER
  int32_t BrakeMin_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_OVER
  int32_t BrakeMax_vsc3;
  /// @ref TA_INHIBIT_VEH_THROTTLE_UNDER
  int32_t ThrottleMin_vsc3;
  /// @ref TA_INHIBIT_VEH_THROTTLE_OVER
  int32_t ThrottleMax_vsc3;
  /// @ref TA_INHIBIT_VEH_LONACCEL_UNDER
  float   LonAccelMin_mmpnm2;
  /// @ref TA_INHIBIT_VEH_LONACCEL_OVER
  float   LonAccelMax_mmpnm2;
  /// @ref TA_INHIBIT_VEH_STEER_RATE_UNDER
  int32_t SteerRateMin_vsc3;
  /// @ref TA_INHIBIT_VEH_STEER_RATE_OVER
  int32_t SteerRateMax_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_RATE_UNDER
  int32_t BrakeRateMin_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_RATE_OVER
  int32_t BrakeRateMax_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_KPA_UNDER
  int32_t BrakePressureMin_vsc3;
  /// @ref TA_INHIBIT_VEH_BRAKE_KPA_OVER
  int32_t BrakePressureMax_vsc3;
  /// @ref TA_INHIBIT_VEH_STEERING_AWAY, @ref TA_INHIBIT_VEH_INDICATING_AWAY
  int32_t LatOffsetMin_mm;
} tTA_InhibitLimits;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void TA_InitInhibitLimits(tTA_InhibitLimits *pLimits,
                          float   SpeedMin_mps,
                          float   SpeedMax_mps,
                          int32_t YawMin_degps,
                          int32_t YawMax_degps,
                          int32_t SteerAngleMin_deg,
                          int32_t SteerAngleMax_deg,
                          int32_t BrakeMin_pc,
                          int32_t BrakeMax_pc,
                          int32_t ThrottleMin_pc,
                          int32_t ThrottleMax_pc,
                          float   LonAccelMin_mps2,
                          float   LonAccelMax_mps2,
                          int32_t SteerRateMin_degps,
                          int32_t SteerRateMax_degps,
                          int32_t BrakeRateMin_pcps,
                          int32_t BrakeRateMax_pcps,
                          int32_t BrakePressureMin_kpa,
                          int32_t BrakePressureMax_kpa,
                          int32_t LatOffsetMin_m);

bool TA_InhibitCheck(tTAInhibitMask HvMask,
                     const tTA_HV * pHV,
                     const tTA_InhibitLimits * pHvLimits,
                     tTAInhibitMask RvMask,
                     const tTA_RV * pRV,
                     const tTA_InhibitLimits * pRvLimits);

bool TA_Eligible(tTCClassif Classification,
                 uint32_t Mask_NOT,
                 uint32_t Mask_ALL,
                 uint32_t Mask_ANY);

tTASeverity TA_Severity(tTASeverity MinSeverity,
                        tTASeverity MaxSeverity,
                        float Range_mm,
                        float MaxRange_mm,
                        float RangeSlope,
                        float Time_ms,
                        float MaxTime_ms,
                        float TimeSlope,
                        bool Logic);

eTAPathType TA_DeterminePathType(const tVector *pVec,
                                 const tLPHPP  *pLPHPP,
                                 bool IndicatorsAreOn,
                                 int32_t SteerWhlAngle_raw,
                                 float   BRAKING_DECEL_MAX_mmpnm2,
                                 float   CREEPING_ACCEL_MIN_mmpnm2,
                                 float   ENTERING_SPEED_mmpnm,
                                 float   MERGING_SPEED_mmpnm,
                                 uint8_t PP_CONFIDENCE_MAX_200,
                                 uint8_t PP_CONFIDENCE_MIN_200,
                                 int32_t PP_RADIUS_MAX_dm,
                                 int32_t PP_RADIUS_MIN_dm,
                                 int32_t STEER_MAX_vsc3,
                                 int32_t STEER_GRADIENT_MAX_vsc3);

#ifdef __cplusplus
}
#endif

#endif // __TA_UTIL_H__
/**
 * @}
 */
