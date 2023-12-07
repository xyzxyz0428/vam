/**
 * @addtogroup lph_pos_api External Position API
 * @{
 *
 * @section lph_pos_api__wdid What Does It Do
 *
 * Provides a consistent API for injecting position fixes into the LPH module
 *
 * On a position update, provide the time and position and other position-
 * related information, including accuracy information. Each position update
 * is then 'pushed' to the LPH processing module and the position information
 * is available to LPH readers.
 *
 * For an OBU, typically the position information will be updated at 10Hz,
 * with the time of the position acquisition used as the time. The time is
 * always in 'Unix' time.
 *
 * For an RSU, typically the position information will be updated only once
 * at initialisation. However, the time of the position initialisation should
 * still be in 'Unix' time.
 *
 * The 'mode' of the position fix provides a coarse indication of position
 * validity and accuracy.
 *
 * Although all fields accept 'NAN' and an indicator of unavailable
 * information, a minimum set of information would include a valid time,
 * Latitude, Longitude, Mode (higher than LPH_POS_FIX_MODE_NO_FIX) and
 * usually Heading, Speed and position accuracy information. Be aware
 * that when Speed is also available through a more accurate sensor, and
 * set in VState, that will be used in LPH.
 *
 * If a data item is no longer valid then it should be set to NAN as on each
 * update the information provided is considered as current (i.e. items are
 * not automatically aged-out.) This includes position loss, where the Mode
 * should be set to LPH_POS_FIX_MODE_NO_FIX. If the loss of position is not
 * reported, then the last set position will continue to be used within LPH.
 *
 * If a GNSS system is used to provide positioning then the
 * SatellitesVisible can be set to provide an additional quality indicator.
 *
 *
 * @file
 *
 * LPH Position API header file
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __LPH_POS_API_H_
#define __LPH_POS_API_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Not A Number
#ifndef NAN
#define NAN (0.0/0.0)
#endif

#define LPH_POS_FIX_UNKNOWN_SATELLITES_VIS 255

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Return codes returned when calling Pos Fix functions
typedef enum LPHPosFixReturnCode
{
  LPH_POS_FIX_SUCCESS = 0,
  LPH_POS_FIX_INVALID = 1,
  LPH_POS_FIX_BAD_PARAM = 2,
  LPH_POS_FIX_NOT_INIT = 3,
  LPH_POS_FIX_ERROR = 4,
} eLPHPosFixReturnCode;

/// Storage for Return codes (@ref LPHPosFixReturnCode)
typedef uint8_t tLPHPosFixReturnCode;

/// LPH position fix mode IDs
typedef enum LPHPosFixMode
{
  LPH_POS_FIX_MODE_NOT_SEEN = 0,  ///< No mode update received yet (unknown)
  LPH_POS_FIX_MODE_NO_FIX = 1, ///< No fix
  LPH_POS_FIX_MODE_2D = 2, ///< Time, latitude, longitude, heading, ground speed
  LPH_POS_FIX_MODE_3D = 3, ///< 2D components, plus altitude & vertical speed
  LPH_POS_FIX_MODE_4 = 4, ///< 3D positioning components with dead reckoning
} eLPHPosFixMode;

/// Storage for LPH position fix mode (@ref LPHPosFixMode)
typedef uint8_t tLPHPosFixMode;

/// LPH position fix format
typedef struct LPHPosFix
{
  /// KINEMATIC DATA
  ///   * Valid floating point number (not NAN): valid provided value
  ///   * NAN: unknown/unavailable
  double UtcTime_s; ///< Unix time, seconds since epoch with fractional part
  double Latitude_deg; ///< Global latitude (WGS-84) in degrees
  double Longitude_deg; ///< Global longitude (WGS-84) in degrees
  float  Altitude_m; ///< WGS-84 altitude (elevation) in metres
  float  Heading_deg; ///< Track made good, degrees relative to north (WGS-84)
  float  GroundSpeed_mps; ///< Speed over ground (WGS-84), metres per second
  float  VerticalSpeed_mps; ///< Vertical speed (climb rate), metres per second

  /// EXPECTED ERROR DATA
  ///   * Valid floating point number (not NAN): valid provided value
  ///   * NAN: unknown/unavailable
  ///   * Errors are expressed as standard deviation (1-sigma, 68% confidence)
  float  UtcTimeErr_s; ///< UTC time error standard deviation, seconds
  float  PosErrSemiMajorAxisLen_m; ///< Error axis length standard deviation, m
  float  PosErrSemiMinorAxisLen_m; ///< Error axis length standard deviation, m
  float  PosErrSemiMajorAxisOrientation_deg; ///< Degrees c.w. relative to north
  float  AltitudeErr_m; ///< Altitude error standard deviation, metres
  float  HeadingErr_deg; ///< Heading error standard deviation, degrees
  float  GroundSpeedErr_mps; ///< Ground speed error standard deviation, m/s
  float  VerticalSpeedErr_mps; ///< Vertical speed error standard deviation, m/s
  float  DOP;                  ///< Position Dilution of Precision DOP [1.]

  tLPHPosFixMode Mode; ///< Identified according to @ref LPHPosFixMode

  uint8_t SatellitesVisible; ///< (0: none, 254: 254 or more, 255: unknown)

} tLPHPosFix;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/*
 * @brief Provide a position fix into the LPH module
 * @param pLPHPosFix Pointer to the position fix information
 * @return Return code enumerated as per @ref eLPHPosFixReturnCode
 */
tLPHPosFixReturnCode LPHPosFix_Position(const tLPHPosFix *pLPHPosFix);

/**
 * @brief Helper function to set position information to defaults, i.e no position
 * @param pFix The fix in which the defaults should be set
 */
void LPHPosFix_SetDefaults(tLPHPosFix *pFix);

/**
 * @brief Helper function to convert X-Y errors to an error ellipse in the fix
 * @param pFix The fix in which the error ellipse should be set (filled out)
 * @param ErrX The expected error in X axis (E-W), 1 standard deviation
 * @param ErrY The expected error in Y axis (N-S), 1 standard deviation
 */
void LPHPosFix_SetErrEllipseFromErrXY(tLPHPosFix *pFix,
                                      float ErrX,
                                      float ErrY);

#ifdef __cplusplus
}
#endif

#endif // __LPH_POS_API_H_

// Close the doxygen group
/**
 * @}
 */
