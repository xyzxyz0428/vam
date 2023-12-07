/**
 * @addtogroup ets_app_facilities_cam_api
 * @{
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_ETSI_ETS_ETSI_UTIL_H_
#define __ETS_ETSI_ETS_ETSI_UTIL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

#include "itsasn.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Conversion factor for Curvature
/// see TS 102 894-2 v1.3.1 (2018-08)
/// ETSI uses units of 1-in-10,000 m
  static const unsigned ETSI_CURVATURE_UNITS_pm = 10000;

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
  struct VStateState;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Calculate distance (using Equirectangular approximation)
 *        between points
 * @param DELat_deg7   Destination Latitude position in 1/10 microdegrees
 * @param DELong_deg7  Destination Longitude position in 1/10 microdegrees
 * @param SOLat_deg7   Source Latitude position in 1/10 microdegrees
 * @param SOLong_deg7  Source Latitude position in 1/10 microdegrees
 * @return        Distance (in metres) from destination to source
 */
  uint32_t ETSI_EquiRectDist_m(const int32_t DELat_deg7,
                               const int32_t DELong_deg7,
                               const int32_t SOLat_deg7,
                               const int32_t SOLong_deg7);

/**
 * @brief Attempt to convert 16-bit CAM delta time to absolute TAI time
 *
 * @param TAICurrent Current TAI time
 * @param CAMDeltaTime Provided CAM delta time
 *
 * @return Predicted TAI time from delta time
 *
 */
  uint64_t ETSI_GetTAITimeFromDeltaTime(uint64_t TAICurrent, uint16_t CAMDeltaTime);

/**
 * @brief Convert a curvature and confidence enum into a percentage
 *
 * @param CurvatureConfidenceEnum
 *
 * @return percentage conficense (as reported by @ref LPH_PathPredict)
 */
  uint8_t ETSI_GetCurvatureConfidenceHalfPercent(
    const ITSCurvatureConfidence CurvatureConfidenceEnum);

  /**
 * @brief Convert LPH/1609 to ITS
 *
 * @param RadiusOfCurve_LPH LPH/1609
 * @param ConfidenceHalfPercent LPH/1609
 *
 * @return ITSCurvature
 */
  ITSCurvature ETSI_CurvatureLPHtoITS(const int16_t RadiusOfCurve_LPH,
                                      const uint8_t ConfidenceHalfPercent);

  float ETSI_CurvatureITStoZdown_m(const ITSCurvatureValue Curvature);
  ITSSpeedConfidence ETSI_SpeedConfidence(const struct VStateState * pVState);

#ifdef __cplusplus
}
#endif

#endif // __ETS_ETSI_ETS_ETSI_UTIL_H_

// Close the Doxygen group
/**
 * @}
 */
