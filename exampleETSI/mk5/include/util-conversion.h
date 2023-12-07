#pragma once
/**
 * @addtogroup util
 * @{
 *
 * Utility functions for conversion between different units
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __APPCORE_UTIL_CONVERSION_H_
#define __APPCORE_UTIL_CONVERSION_H_


//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// acceleration in multiples of earth's gravity
static const float UTIL_G2MPSS = 9.80665;

/// legacy support
#define UTIL_M_TO_YARDS 1.0936133

/// KPH to MPS factor
static const float UTIL_KPH2MPS = (1e3 / (60 * 60));

/// Time Units (Normalised Minute Units, 2^16 ticks per minute)
static const float UTIL_NMINUNITSTOSECONDS = (60.0 / (1 << 16));

/// Reciprocal
static const float UTIL_SECONDSTONMINUNITS = ((1 << 16) / 60.0);

/// (1 << 16) / 60,000
///< Step per milli second in a 16 bit wrapping minute
static const float UTIL_MSTONMINS = (60e3 / (1 << 16));

/// (60. / (1 << 16)) * (1000 / 1)
static const float UTIL_MPS_TO_MMPNMIN = (60e3 / (1 << 16));

/// reciprocal
static const float UTIL_MMPNMIN_TO_MPS = ((1 << 16) / 60e3);

/// 0.02 m/s
static const float UTIL_DESPEED_TO_MPS = 0.02;

///< Heading Units to Degs
// 5.493164e-3
static const float UTIL_HDU_TO_DEGS = ((double)180.0 / (1<<15));

static const int32_t UTIL_DEG7_90  =  900000000;
static const int32_t UTIL_DEG7_180 = 1800000000;

// Get the definition of NAN in QNX
#ifndef NAN
#define NAN (0.0/0.0)
#endif

// TODO: QNX seems fussy about std::round in C++ code
#if defined(__QNX__) && defined(__cplusplus)
#define ROUND(val) std::round(val)
#else
#define ROUND(val) round(val)
#endif

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Convert standard gravity to metres per second squared
static inline float Util_GToMpss(float G)
{
  return G * UTIL_G2MPSS;
}

/// Convert kilometres per hour to metres per second
static inline float Util_KphToMps(float Kph)
{
  return Kph * UTIL_KPH2MPS;
}

/// Convert metres per second to kilometres per hour
static inline float Util_MpsToKph(float Mps)
{
  return Mps / UTIL_KPH2MPS;
}

/// Convert metres to millimetres
static inline float Util_MToMm(float Metres)
{
  return Metres * 1000;
}

/// Convert millimetres to metres
static inline float Util_MmToM(float Millimetres)
{
  return Millimetres / 1000;
}

/// Convert metres to dm
static inline float Util_MToDm(float Metres)
{
  return Metres * 10;
}

/// Convert dm to metres
static inline float Util_DmToM(float Dm)
{
  return Dm / 10;
}

/// Convert metres per second to millimetres per second
static inline float Util_MpsToMmps(float Mps)
{
  return Util_MToMm(Mps);
}

/// Convert millimetres to metres
static inline float Util_MmpsToMps(float Mmps)
{
  return Util_MmToM(Mmps);
}

/// Convert millimetres per normalised minute to metres per second
static inline float Util_MmpnminToMps(float Mmpnmin)
{
  return Mmpnmin * UTIL_MMPNMIN_TO_MPS;
}

/// Convert standard gravity to metres per second squared
static inline float Util_DESpeedToMps(float DESpeed)
{
  return DESpeed * UTIL_DESPEED_TO_MPS;
}

/// Convert metres per second to millimetres per normalised minute
static inline float Util_MpsToMmpnmin(float Mps)
{
  return Mps * UTIL_MPS_TO_MMPNMIN;
}

/// Convert millimetres per normalised minute to kilometres per hour
static inline float Util_MmpnminToKph(float Mmpnmin)
{
  return Util_MpsToKph(Util_MmpnminToMps(Mmpnmin));
}

/// Convert kilometres per hour to millimetres per normalised minute
static inline float Util_KphToMmpnmin(float Kph)
{
  return Util_MpsToMmpnmin(Util_KphToMps(Kph));
}

/// Convert seconds to milliseconds
static inline double Util_SToMs(double seconds)
{
  return seconds * 1000.0;
}

/// Convert milliseconds to seconds
static inline double Util_MsToS(double milliseconds)
{
  return milliseconds / 1000.0f;
}

/// Convert milliseconds to microseconds
static inline double Util_MsToUs(double milliseconds)
{
  return milliseconds * 1000.0;
}

/// Convert microseconds to milliseconds
static inline double Util_UsTMs(double microseconds)
{
  return microseconds / 1000.0f;
}
/// Convert normalised minutes to seconds
static inline float Util_NmToS(float Nm)
{
  return Nm * UTIL_NMINUNITSTOSECONDS;
}

/// Convert meters to yards
static inline float Util_MeterToYard(float meters)
{
  return meters * UTIL_M_TO_YARDS;
}

/// Convert meters per second squared to millimeters per normalised minute squared
static inline float Util_MpssToMmpnm2(float Mpss)
{
  return Util_MpsToMmpnmin(Util_NmToS(Mpss));
}

/// Convert nanoseconds to seconds
static inline double Util_NsToS(double nanoeconds)
{
  return nanoeconds / 1e9;
}

/**
 * @brief Normalize a degree value to [0,360)
 *
 * @param Angle_deg Angle to normalize
 *
 * @return 0 <= Ret < 360
 */
static inline double Util_NormaliseDeg360(double Angle_deg)
{
  Angle_deg = fmod(Angle_deg, 360.0);
  if (Angle_deg < 0.0)
  {
    return Angle_deg + 360.0;
  }
  return Angle_deg;
}

/**
 * @brief Normalize a degree value to [-180,180)
 *
 * @param Angle_deg Angle to normalize
 *
 * @return -180 <= Ret < 180
 */
static inline double Util_NormaliseDeg(double Angle_deg)
{
  Angle_deg = fmod(Angle_deg, 360.0);
  if (Angle_deg < -180.0)
  {
    return Angle_deg + 360.0;
  }
  if (Angle_deg >= 180.0)
  {
    return Angle_deg - 360.0;
  }
  return Angle_deg;
}

/**
 * @brief Normalise Latitude
 *
 * @param Latitude_deg
 *
 * @return [-90,90] or NAN
 */
static inline double Util_NormaliseLatitudeDeg(double Latitude_deg)
{
  // can't wrap latitude as we'd have to adjust longitude as well..
  if ((Latitude_deg >= -90.0)
      &&
      (Latitude_deg <=  90.0))
  {
    return Latitude_deg;
  }
  return NAN;
}

/**
 * @brief Normalise Longitude
 *
 * @param Longitude_deg
 *
 * @return [-180, 180)
 */
static inline double Util_NormaliseLongitudeDeg(double Longitude_deg)
{
  Longitude_deg = fmod(Longitude_deg, 360.0);
  if (Longitude_deg < -180.0)
  {
    Longitude_deg += 180.0;
  }
  else if (Longitude_deg >= 180.0)
  {
    Longitude_deg += 180.0;
  }
  return Longitude_deg;
}

static inline int32_t Util_NormaliseLatitudeDeg7(int32_t Latitude_deg7)
{
  if ((Latitude_deg7 >= -UTIL_DEG7_90)
      &&
      (Latitude_deg7 <=  UTIL_DEG7_90))
  {
    return Latitude_deg7;
  }
  return (UTIL_DEG7_90 + 1);
}

static inline int32_t Util_NormaliseLongitudeDeg7(int32_t Longitude_deg7)
{
  if (Longitude_deg7 < -UTIL_DEG7_180)
  {
    // 3600000000 > 0x80000000 so do this in 2 steps
    // to avoid weird over/under-flow
    Longitude_deg7 += UTIL_DEG7_180;
    Longitude_deg7 += UTIL_DEG7_180;
  }
  else if (Longitude_deg7 >= UTIL_DEG7_180)
  {
    Longitude_deg7 -= UTIL_DEG7_180;
    Longitude_deg7 -= UTIL_DEG7_180;
  }
  return Longitude_deg7;
}


/**
 * @brief Normalize a radian value to [-pi,pi)
 *
 * @param Angle_rad Angle to normalize
 *
 * @return -pi <= Ret < pi
 */
static inline double Util_NormaliseRad(double Angle_rad)
{
  Angle_rad = fmodf(Angle_rad, (2 * M_PI));
  if (Angle_rad < -M_PI)
  {
    return Angle_rad + (2 * M_PI);
  }
  if (Angle_rad >= M_PI)
  {
    return Angle_rad - (2 * M_PI);
  }
  return Angle_rad;
}

/**
 * @brief Convert milliseconds to timeval struct
 */
static inline void Util_ms2tv(struct timeval *pResult_tv, int32_t Interval_ms)
{
    pResult_tv->tv_sec  = (Interval_ms / 1000);
    pResult_tv->tv_usec = ((Interval_ms % 1000) * 1000);
}

/**
 * @brief Convert seconds to timeval struct
 */
static inline void Util_s2tv(struct timeval *pResult_tv, int32_t Interval_s)
{
    pResult_tv->tv_sec  = Interval_s;
    pResult_tv->tv_usec = 0;
}

/**
 * @brief Convert from Degrees to Radians
 *
 * @param Angle_deg Angle in Degrees
 *
 * @return Angle in Radians
 */
static inline float Util_DegToRad(float Angle_deg)
{
  return Angle_deg * (M_PI / 180.0);
}

/**
 * @brief Convert from Radians to Degrees
 *
 * @param Angle_rad Angle in Radians
 *
 * @return Angle in Degrees
 */
static inline float Util_RadToDeg(float Angle_rad)
{
  return Angle_rad * (180.0 / M_PI);
}

/**
 * @brief Convert from scaled degrees to radians
 *
 * In theory all arithmatic is at double anyway, so no need to change this to float.
 *
 * @param Angle_deg7 Angle in scaled degrees
 *
 * @return Radian equivalent of angle
 */
static inline double Util_Deg7ToRad(int32_t Angle_deg7)
{
  return Angle_deg7 * (M_PI / 180.0e7);
}

static inline double Util_Deg7ToLatitudeDeg(int32_t Latitude_deg7)
{
  if ((Latitude_deg7 < -UTIL_DEG7_90)
      ||
      (Latitude_deg7 >  UTIL_DEG7_90))
  {
    return NAN;
  }
  return Latitude_deg7 * 1e-7;
}

static inline double Util_Deg7ToLongitudeDeg(int32_t Longitude_deg7)
{
  if ((Longitude_deg7 < -UTIL_DEG7_180) // <= ?
      ||
      (Longitude_deg7 >  UTIL_DEG7_180))
  {
    return NAN;
  }
  return Longitude_deg7 * 1e-7;
}

static inline int32_t Util_DegToLatitudeDeg7(double Latitude_deg)
{
  if (!(Latitude_deg == Latitude_deg)
      ||
      (Latitude_deg < -90.0)
      ||
      (Latitude_deg >  90.0))
  {
    return UTIL_DEG7_90 + 1;
  }
  return (int32_t)ROUND(Latitude_deg * 1e7);
}

static inline int32_t Util_DegToLongitudeDeg7(double Longitude_deg)
{
  if (!(Longitude_deg == Longitude_deg)
      ||
      (Longitude_deg < -180.0) // <= ?
      ||
      (Longitude_deg >  180.0))
  {
    return UTIL_DEG7_180 + 1;
  }
  return (int32_t)ROUND(Longitude_deg * 1e7);
}

/**
 * @brief Convert from degrees to HDU
 * @param Degs Degrees (-180 to 180)
 * @return Heading units equivalent of degrees
 */
static inline float Util_DegToHdu(float Degs)
{
  return Degs / UTIL_HDU_TO_DEGS;
}

/**
 * @brief Convert from HDU to degrees
 * @param HDU Heading units
 * @return Degree equivalent of heading units
 */
static inline float Util_HduToDeg(float HDU)
{
  return HDU * UTIL_HDU_TO_DEGS;
}

/**
 * @brief Convert timval to UTC in milliseconds
 */
static inline int64_t Util_TimevalToUTC_ms(const struct timeval * pTimeVal)
{
  // make sure this operation is done as a 64-bit integer to avoid truncation.
  return ((((int64_t)pTimeVal->tv_sec) * ((int64_t)1000)))
	  + (pTimeVal->tv_usec / 1000);
}

/**
 * @brief Convert timval to UTC in seconds
 */
static inline double Util_TimevalToUTC_s(const struct timeval * pTimeVal)
{
  return pTimeVal->tv_sec + (pTimeVal->tv_usec * 1e-6);
}

static inline void Util_UTCstoTimeval(struct timeval * pUTC, const double UTC_s)
{
  double seconds = NAN;
  const double fraction = modf(UTC_s + 0.5e-6, &seconds);
  pUTC->tv_sec  = seconds;
  pUTC->tv_usec = fraction * 1e6;
}

/**
 * @brief Convert J2735 DE_Heading to degrees
 */
static inline float Util_DEHeadingToDeg(uint16_t DEHeading)
{
  return DEHeading * 0.0125;
}

/**
 * @brief Convert degrees to J2735 DE_Heading
 */
static inline uint16_t Util_DegToDEHeading(float Heading_deg)
{
  return Heading_deg / 0.0125;
}

/**
 * @brief "IsEmpty" test, typically for configuration strings.
 *
 * @param pStr string to test
 *
 * @return true if string is NULL or zero-length
 */
static inline bool Util_Empty(const char * pStr)
{
  return ((pStr    == NULL)
          ||
          (pStr[0] == '\0'));
}


#ifdef __cplusplus
}
#endif

#endif //  __APPCORE_UTIL_CONVERSION_H_

/**
 * @}
 */
