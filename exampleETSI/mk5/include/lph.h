/**
 * @addtogroup stack_lph_api Local Position Handler (LPH) API
 * @{
 *
 * @section lph_api_wdid What Does It Do
 * This library provides an API to access various position information:
 *   - Precise Position Information
 *   - Path History
 *   - Path Prediction
 *
 * The position information is typically taken from the GPS-Rx module
 *
 * @section lph_api_hdwui How Do We Use It
 * The most commonly used functions are
 * - @ref LPH_Open
 * - @ref LPH_Close
 * - @ref LPH_Data
 * - @ref LPH_Position
 * - @ref LPH_PathHistory
 * - @ref LPH_PathPredict
 *
 * Applications access the latest position information available via the
 * access functions provided. Mechanisms inside the library handle the updating
 * of this information and users of this library are not exposed to this issue.
 * These function calls return immediately with the most recent data.
 *
 * Clients can be notified of LPH position update by handling the EXT event
 * @c QSMSG_EXT_LPH_FIX.
 * See the EXT module for further details.
 *
 * @file
 *
 * Define supported messages
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __LPH_H_
#define __LPH_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "lph-float.h"

#include "id-global.h"
#include "lph-pos-api.h"

#include <sys/time.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define UNAVAIL_DE_SECOND (65535)

#define MAX_DE_LAT 900000000
#define MIN_DE_LAT -900000000
#define UNAVAIL_DE_LAT 900000001

#define MAX_DE_LON 1800000000
#define MIN_DE_LON -1799999999
#define UNAVAIL_DE_LON 1800000001

#define MAX_DE_ELEV (61439)
#define MIN_DE_ELEV (-4095)
#define UNAVAIL_DE_ELEV (-4096)

#define LPH_LAT_VALID(lat)          (((lat) >= MIN_DE_LAT) && ((lat) <= MAX_DE_LAT))
#define LPH_LON_VALID(lon)          (((lon) >= MIN_DE_LON) && ((lon) <= MAX_DE_LON))
#define LPH_LAT_LON_VALID(lat, lon) (LPH_LAT_VALID(lat) && LPH_LON_VALID(lon))

/// Heading is given in 1/80'th of a degree with 80*360 denoting "unavailable"
#define UNAVAIL_DE_HEAD (80*360)
#define MAX_DE_HEAD (UNAVAIL_DE_HEAD-1)
#define MIN_DE_HEAD 0

/// Speed is given in 1/50'th of a metre per sec with 8191 denoting "unavailable"
#define UNAVAIL_DE_SPEED 8191
#define MAX_DE_SPEED (UNAVAIL_DE_SPEED-1)
#define MIN_DE_SPEED 0

/// Radius is given in 1/10'th of a metre with 32767 denoting "straight"
#define UNAVAIL_DE_RADIUS 32767
#define STRAIGHT_DE_RADIUS (UNAVAIL_DE_RADIUS)
#define MAX_DE_RADIUS (UNAVAIL_DE_RADIUS-1)
#define MIN_DE_RADIUS -32767

/// Max PH points
#define LPH_PH_POINTS_MAX 40

/// Number of leap-seconds at the 2004 epoch (see https://en.wikipedia.org/wiki/Leap_second)
#define NUM_LEAPSECONDS_2004 22

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// LPH determined position fix
/// @note Position may be interpolated (if feature is enabled)
typedef struct LPHPos
{
  /// Mode of fix
  /// 0 = Init, 1 = No fix, 2 = 2D, 3 = 3D
  uint8_t Mode;

  /// Number of satellites used in solution
  uint8_t NbrSatellitesUsed;
  /// Number of satellites visible
  struct {
    /// Number of GPS satellites visible
    int16_t GPS;
    /// Number of GBAS satellites visible
    int16_t GBAS;
    /// Number of SBAS satellites visible
    int16_t SBAS;
    /// Number of Other GNSS satellites visible
    int16_t GNSS;
  } NbrSatellitesVisible;

  /// DynamicAccuracy (speed/heading)
  uint16_t DynAccuracy;

  /// PositionalAccuracy
  struct
  {
    /// Semi-major axis accuracy with 95% confidence (two sigmas)
    /// Range: N/A Units: m
    float SemiMajorAxis_m;
    /// Semi-minor axis accuracy with 95% confidence (two sigmas)
    /// Range: N/A Units: m
    float SemiMinorAxis_m;
    /// Orientation of semi-major axis
    /// Range: N/A Units: Degree
    float SemiMajorAxisOrientation_deg;
  } PositionalAccuracy;

  /// Time of fix (UTC)
  struct timeval Time;
  /// SecMark, milliseconds since start of minute
  /// As per J2735's DE_DSecond.
  /// Range: 0...65535
  /// Value Range: 0..59999 (0..59.999 seconds) Units: milliseconds
  /// Special values 60000..60999 indicate a leap second (not yet implemented)
  /// Special value 65535 indicates unavailable
  uint16_t SecMark;
  /// Position Latitude
  /// As per J2735's DE_Latitude.
  /// Range: -900000000..900000001
  /// Value Range: -900000000..900000000 (-90..90 degs) Units: 1/10 micro degree
  /// Special value 900000001 indicates unavailable
  int32_t Latitude;
  /// Position Longitude
  /// As per J2735's DE_Longitude.
  /// Range: -1799999999..1800000001
  /// Value Range: -1799999999..1800000000 (-179.9999999..180 degs) Units: 1/10 micro degree
  /// Special value 1800000001 indicates unavailable
  int32_t Longitude;
  /// Position Elevation (Altitude) above or below the reference ellipsoid
  /// As per J2735's DE_Elevation
  /// Range: -4096..61439
  /// Value Range: -4095..61439 (-409.5..6143.9m) Units: 10 cm
  /// Special value -4096 indicates unavailable
  int32_t Elevation;
  /// Heading, from North
  /// As per J2735's DE_Heading
  /// Range: 0..28800
  /// Value Range: 0..28799 (0 to 359.9875 degrees) Units: 0.0125 degrees
  /// Special value 28800 indicates unavailable
  uint16_t Heading;
  /// Ground Speed
  /// (from VState, if available, otherwise as measured by GNSS system)
  /// J2735's DE_Speed
  /// Range: 0..8191
  /// Value Range: 0..8190 (0..163.8 m/s) Units: 0.02 m/s
  /// Special value 8191 indicates unavailable
  uint16_t Speed;
  /// Original format GPS fix information
  tLPHPosFix Fix;
} tLPHPos;

typedef struct LPHCrumb
{
  /// Latitude offset
  /// Range: -131072..131071 Units: 1/10 micro degree
  int32_t LatOffset; // _ deg7
  /// Longitude offset
  /// Range: -131072..131071 Units: 1/10 micro degree
  int32_t LongOffset; // _deg7
  /// Elevation offset
  /// Range: -2048..2047 Units: 0.1 m
  int32_t ElevationOffset; // _dm
  /// Time offset
  /// Range: 1..65535 Units: 10 msec
  uint32_t TimeOffset; // _cs
  /// Heading
  /// Range: 0..28799 (0 to 359.9875 degrees) Units: 0.0125 degrees
  uint16_t Heading;
  /// Speed
  /// Range: 0..8190 (0..163.8 m/s) Units: 0.02 m/s
  /// Special value 8191 indicates that speed is unavailable
  uint16_t Speed;
  /// Crumb distance
  uint16_t Dist_cm;
} tLPHCrumb;

/// LPH determined path history
typedef struct LPHPH
{
  /// InitialPosition (Path history points are relative to this one)
  tLPHPos InitialPosition;
  /// Number of entries in the path history table (0...LPH_PH_POINTS_MAX)
  int ItemCnt;
  /// Path history points table (index 0...LPH_PH_POINTS_MAX-1)
  tLPHCrumb CrumbData[LPH_PH_POINTS_MAX];
} tLPHPH;

/// LPH determined path prediction
typedef struct LPHPP
{
  /// Radius of curve
  /// Range: -32767..32767 (-3276.7..3276.6 meters) Units: 0.1 meters
  /// a value of 32767 indicates a straight path
  int16_t RadiusOfCurve;
  /// Confidence
  /// Range 0..200 (0..100%) Units: 0.5 percent
  uint8_t Confidence;
} tLPHPP;

/// LPH determined position fix, path history & prediction
typedef struct LPHData
{
  /// Latest position fix @note Position may be interpolated
  struct LPHPos Pos;
  /// Latest path history points
  struct LPHPH PH;
  /// Latest path prediction
  struct LPHPP PP;
} tLPHData;

 /**
 * @brief Type for security leap second change callback
 * @param NumLeapSecondsUTC number of leap seconds since Unix epoch
 */
typedef void (fLPH_LeapSecondChangeSecCb)(int NumLeapSecondsUTC);

/// leap-second state, used in the message broadcasts
typedef enum
{
  /// no leap second pending
  LPH_LEAP_SECOND_MODE_NONE      = QSMSG_LPH_LEAP_SECOND_MODE + 0,
  /// leap second scheduled
  LPH_LEAP_SECOND_MODE_SCHEDULED = QSMSG_LPH_LEAP_SECOND_MODE + 1,
  /// leap second within next 30 seconds
  LPH_LEAP_SECOND_MODE_PENDING   = QSMSG_LPH_LEAP_SECOND_MODE + 2,
  /// experiencing the leap-second the first time
  LPH_LEAP_SECOND_MODE_1         = QSMSG_LPH_LEAP_SECOND_MODE + 3,
  /// experiencing the leap-second the second time
  LPH_LEAP_SECOND_MODE_2         = QSMSG_LPH_LEAP_SECOND_MODE + 4,
  /// leap second within the last 30 seconds
  LPH_LEAP_SECOND_MODE_RECENT    = QSMSG_LPH_LEAP_SECOND_MODE + 5,
} eLeapSecondState;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// LPH library API functions (called by the main application)

int LPH_Init(void);
void LPH_Exit(void);

// LPH thread API functions (called by the main application)

int LPH_ThreadInit(int SchedulerPolicy, int SchedulerPriority);
void LPH_ThreadDeinit(void);

// LPH client API functions

/// @brief Get an exclusive handle to an LPH context
void * LPH_Open(void);
/// @brief Release the handle created in LPH_Open()
void LPH_Close(void *pHdl);
/// @brief Query the latest LPH data (Position, PathHistory & PathPrediction)
int LPH_Data(void *pHdl, const struct LPHData **ppData);
/// @brief Query the latest LPH position
int LPH_Position(void *pHdl, struct LPHPos *pPos);
/// @brief Extrapolate the position from the most recent LPH position to designated time (usually now)
int LPH_Predict(void *pHdl,
                const struct timeval *pWhen,
                struct LPHPos *pPos);
/// @brief Query the latest LPH PathPrediction
int LPH_PathPredict(void *pHdl, struct LPHPP *pPP);
/// @brief Query the latest LPH PathHistory
int LPH_PathHistory (void *pHdl, struct LPHPH *pPH);
/// @brief Reset the LPH PathHistory
void LPH_PathHistoryReset(void);


void LPH_SetNumLeapSecondsGPS(int NumLeapSeconds);
void LPH_SetNumLeapSecondsUTC(int NumLeapSeconds);
int LPH_GetNumLeapSecondsUTC(void);
void LPH_SetOffset2004(int NumLeapSecondsSince2004);
int LPH_GetOffset2004(void);
uint64_t LPH_UTCtoLeap2004(const struct timeval *pUTC);
void LPH_Leap2004toUTC(struct timeval *pUTC, uint64_t Leap2004);
uint64_t LPH_Leap2004Now(void);
time_t LPH_NextLeapSecondUTC(int utcWNF, int utcDN);

void LPH_DecodePosAccuracy(float *pSemiMajor_m,
                           float *pSemiMinor_m,
                           float *pHeading_deg,
                           uint32_t SemiMajor,
                           uint32_t SemiMinor,
                           uint32_t Orientation);

void LPH_NotifyPendingLeapSecond(time_t UTCofNextLeapSecond, int CurrentLeapSecondNum);
void LPH_UpdateLeapSecondSecMark(struct LPHPos *pPos);
void LPH_SetLeapSecondChangeCallback(fLPH_LeapSecondChangeSecCb *pCallback);
int16_t LPH_RadiustoLPH(const float RadiusZdown_m);

//------------------------------------------------------------------------------
// Global variable declaration
//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
#endif // __LPH_H_
