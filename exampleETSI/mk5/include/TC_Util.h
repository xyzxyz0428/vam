#pragma once
/**
 * @addtogroup tc_util Utility functions for Target Classification (TC)
 * @{
 *
 * Helper functions for TC
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TC_UTIL_H_
#define __TC_UTIL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "TC_Err.h"

#include "Vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// meters / second / second (SI units) to mm / millisecond / millisecond
#define MPS2_TO_MMPMS2   1e-3
/// meters / second (SI units) to mm / millisecond
#define MPS_TO_MMPMS     1

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef struct TCParamsFast
{
  float   maxRange_mm;
  int16_t sameHeadingLimit_tHDU;
  int16_t oppositeHeadingLimit_tHDU;
  float   safeSpeed_mmpnm;
  float   RELATIVE_SPEED_CLOSING_mmpnm;
  float   RELATIVE_SPEED_RECEDING_mmpnm;
  tHDU    rearBoreSightLimit_tHDU;
  tHDU    fwdBoreSightLimit_tHDU;
  float   laneFarLeft_mm;
  float   laneLeft_mm;
  float   laneRight_mm;
  float   laneFarRight_mm;
  float   parallelLimit_sine;
  float   phLonSepLimitFactor;
  float   laneChangeSpeedMax_mmpnm;
  float   laneChangeRadiusMax_mm;
  float   CurveMinRadius_mm;
  float   CurveMaxRadius_mm;

  tHDU    pathIsStraightAngularThreshold_tHDU;

  float   TTCAccelMin_mmpms2;
  float   TTCSpeedMin_mmpms;

  int16_t AdvanceTimeMax_nm;
  int16_t AdvanceTimeMin_nm;

  /// path prediction confidence, half-percent ([0..200])
  uint8_t curveMinConf_hpc;

  ///  threshold with hysteresis to open up elevation check [0.125 degree]
  int     ElevCheckOpenupWithHysteresis_eighthdeg;
  ///  threshold with hysteresis not to open up elevation check [0.125 degree]
  int     ElevCheckNormalWithHysteresis_eighthdeg;
} tTCParamsFast;

struct TCRemote;
struct LPHData;
struct LPHPos;
struct VStateState;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

float TC_CalcTTC(const float Accel_mmpnm2,
                 const float Speed_mmpnm,
                 const float Range_mm);

void TC_MakeFastConfig(void);

void TC_SetDefaultExpiryTimes(struct TCRemote * pTCRemote);

tTC_ErrCode TC_MakeLocalVector(tVector * pVector,
                               const struct LPHPos * pLPHPos,
                               const struct LPHData * pLPHData,
                               const struct VStateState * pVStateState);

#ifdef __cplusplus
}
#endif

#endif // __TC_UTIL_H_

// Close the doxygen group
/**
 * @}
 */
