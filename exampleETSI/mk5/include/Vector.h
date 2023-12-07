/**
 * @addtogroup vector Vector Calculations API
 * @{
 *
 * @section vector_dd What Does It Do
 * Provides functions to create, destroy, manipulate and do various
 * calculations with vectors.
 *
 * @file Vector.h Module code for vector functions
 *
 *
 */

//=============================================================================
// Copyright 2008
// Cohda Wireless PTY LTD
//=============================================================================


//-----------------------------------------------------------------------------
// Module: Vector
// Author(s): Paul Alexander
//-----------------------------------------------------------------------------

#ifndef VECTOR_DEF
#define VECTOR_DEF

// make sure we get NAN
#ifndef  _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#ifdef __cplusplus
#include <cmath>
extern "C" {
#endif

void sincosf(float x, float *sin, float *cos);

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

#define DEGSTORADS   0.0174532925
#define RADSTODEGS  57.2957795
#define PI           3.14159265
#define TWOPI        6.28318531
/// http://www.koordinaten.de/english/informations/earth.shtml
#define PLANETPOLARCIRCUM 40076592 // Metres
#define PLANETEQCIRCUM    40009153 // Metres
#define PLANETMPERLATDEG  111323.87 // Metres per Lateral Degree
#define PLANETMPERLONDEG  111136.54 // Metres per Longitudinal Degree @ Equator
/// mm versions
#define PLANETPOLARCIRCUM_MM 40076592000 // mm
#define PLANETEQCIRCUM_MM    40009153000 // mm
#define PLANETMMPERLATDEG  111323870 // mm per Latitude Degree @ equator
#define PLANETMMPERLONDEG  111136540 // mm per Longitude Degree @ Equator

/// Time Units (Normalised Minute Units, 2^16 ticks per minute)
/// 60. / (1 << 16)
#define NMINUNITSTOSECONDS 9.15527344e-004
/// Reciprocal
#define SECONDSTONMINUNITS 1092.266667
/// (1 << 16) / 60,000
#define MSTONMINS 1.092266667 ///< Step per milli second in a 16 bit wrapping minute
/// (60. / (1 << 16)) * (1000 / 1)
#define MPS_TO_MMPNMIN 0.91552734375
/// reciprocal
#define MMPNMIN_TO_MPS 1.092266667

/// Acceleration Units

#define MMPNMIN2_TO_MPS2 (MMPNMIN_TO_MPS / NMINUNITSTOSECONDS)
#define MPS2_TO_MMPNMIN2 (MPS_TO_MMPNMIN / SECONDSTONMINUNITS)

/// Meters per second same as mm per ms
#define MMPNMIN_TO_MMPMS (MMPNMIN_TO_MPS)
/// 1 m/s/s = 1000 mm/s/s
#define MMPNMIN2_TO_MMPMS2 (MMPNMIN2_TO_MPS2 * 1e3)

/// Heading Units
#define RADSTOHDU  ((float)(UINT16_C(1)<<15) / M_PI)  // 1.043038e4  ///< Rads to Heading Units
#define HDUTORADS  ((float)1.0 / RADSTOHDU) // 9.587380e-5 ///< Heading Units to Rads
#define HDUTODEGS  ((float)180.0 / (UINT16_C(1)<<15)) // 5.493164e-3 ///< Heading Units to Degs
#define DEGSTOHDUS ((float)1.0 / HDUTODEGS) // 182.044444  ///< Degs to Heading Units
#define MINANGLE_HDUS -32768
#define MAXANGLE_HDUS  32767
#define MINUSPI_HDUS  -32768
#define QUADRANT_HDUS  16384  ///< Quarter of a circle in HDUS
#define N_HDUS             0  ///< Due north
#define NE_HDUS      (UINT16_C(1)<<13)  ///<  +45 Degrees
#define E_HDUS       (UINT16_C(2)<<13)  ///< Due East, 90 degrees
#define SE_HDUS      (UINT16_C(3)<<13)  ///< +135 Degrees (clockwise from North)
#define S_HDUS     (-(UINT16_C(4)<<13)) ///< Due south, half turn, wrap around
#define SW_HDUS    (-SE_HDUS) ///< -135 Degrees (Anticlockwise from North)
#define W_HDUS      (-E_HDUS) ///< Due West
#define NW_HDUS    (-NE_HDUS) ///< -45 Degrees (Anticlockwise from North)

#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef MAXFLOAT
#define MAXFLOAT  3.40282347e+38F
#endif

#ifndef INFINITY
#define INFINITY (MAXFLOAT+MAXFLOAT)
#endif

/// Check/set the radius to indicate the vehicle is travelling in a straight line
#define VECTOR_RADIUS_IS_STRAIGHT(r)  (isnan(r))
#define VECTOR_RADIUS_SET_STRAIGHT(r) ((r) = NAN)

/// Check/set the radius to indicate that the radius is unavailable
#define VECTOR_RADIUS_IS_UNAVAIL(r)  ((r) == 0)
#define VECTOR_RADIUS_SET_UNAVAIL(r) ((r)  = 0)

/// Check/set the elevation to indicate that it is unavailable
#define VECTOR_ELEVATION_UNAVAIL        ((int32_t)(UINT32_C(1)<<31))
#define VECTOR_ELEVATION_IS_UNAVAIL(e)  ((e) == VECTOR_ELEVATION_UNAVAIL)
#define VECTOR_ELEVATION_SET_UNAVAIL(e) ((e)  = VECTOR_ELEVATION_UNAVAIL)

/// Trigonometric functions with input in Degrees
#define cosd(d) cos((d) * DEGSTORADS)
#define sind(d) sin((d) * DEGSTORADS)
#define coshdu(h) cos((h) * HDUTORADS)
#define sinhdu(h) sin((h) * HDUTORADS)
#define atan2d(y,x)   (atan2((y),(x)) * RADSTODEGS)
#define atan2hdu(y,x) (atan2((y),(x)) * RADSTOHDU)


//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

/**
 * tHDU:
 *
 * Heading Units (wraps naturally)\n
 *
 * NORTH =      0 (  0deg,   0   rad)\n
 * EAST  =  16384 ( 90deg,  pi/2 rad)\n
 * SOUTH = -32768 (180deg,  pi   rad)\n
 * WEST  = -16384 (270deg, -pi/2 rad)\n
 *
 * Also used for relative bearings\n
 *
 * AHEAD  =      0 (  0deg,   0   rad)\n
 * RIGHT  =  16384 ( 90deg,  pi/2 rad)\n
 * BEHIND = -32768 (180deg,  pi   rad)\n
 * LEFT   = -16384 (270deg, -pi/2 rad)\n
 *
 */
typedef int16_t tHDU;

/**
 * tVector:
 *
 * Vector Type
 *
 * Assume you are currently in Adelaide
 *     http://www.openstreetmap.org/#map=12/-34.9328/138.5359
 * heading to Alice Springs
 *     http://www.openstreetmap.org/#map=13/-23.7180/133.8578
 * at 100km/h, accelerating and turning slightly to the right,
 * time is 15 seconds past the last minute
 * @verbatim
         ^
         | NORTH,y (0)
         + --> EAST,x (16384)

      (1) Alice Springs
           _
            /|
           |
          |   Initially heading NNW, turning right
           |
          (0) Adelaide
 @endverbatim
 *
 * Lat_Degs   -34.9328\n
 * Lon_Degs   138.5359\n
 * Elevation_cm   0\n
 * Heading  -3640 (call it 20  degrees WEST of NORTH)\n
 * Speed       25.43 (100 km/h * 1e6 mm/km / (60*65536 units/h)\n
 * LonAccel    positive (accelerating)\n
 * LatAccel    // ???? same as  J2735\n
 * Radius_mm large and positive (describing a large circle clockwise)\n
 * t         16384 (15000 ms * (65536 / 60000))
 *
 * Speed        in mm per Normalised Minutes
 * Heading      in tHDU
 * Acceleration in mm per (Normalised Minutes)^2
 * t            in Normalised Minutes
 */
typedef struct
{
  double    Lat_Degs;         ///< Latitude in Degrees ([-90,90] related to Northings)
  double    Lon_Degs;         ///< Longitude in Degrees ([-180,180) ]related to Eastings)
  int32_t   Elevation_cm;     ///< Elevation in centimetres (WSG84 coordinate system)
  float     cosHeading;       ///< cosine of heading (cached)
  float     sinHeading;       ///< sine of heading (cached)
  float     Speed_mmpnm;      ///< unsigned speed (mm per normalised minute unit)
  float     LonAccel_mmpnm2;  ///< Acceleration in direction of travel (signed)
  float     LatAccel_mmpnm2;  ///< Acceleration orthogonal to direction of travel (signed)
  float     Radius_mm;        ///< Signed radius of motion (+ == Clockwise)
  float     VertAccel_mmpnm2; ///< Signed vertical acceleration along vertical axis
  tHDU      Heading;          ///< Heading in wrapping Units
  uint16_t  t;                ///< normalised minute unit (wraps at 1 minute)
} tVector;

/**
 * @brief Set the vector heading in tHDU units
 *
 * @note: HERE BE DRAGONS!!!
 * if you pass in a floating point type expecting implicit type conversion the
 * float MUST BE in [-32768 .. 32767] (i.e. [MINANGLE_HDUS ... MAXANGLE_HDUS] )
 * else if will default to the INT16_MIN value and break silently and hilariously
 *
 * @param pVector Vector to update
 * @param h heading in [-32768 .. 32767]
 */
inline static void VECTOR_HEADING_SET_HDU(tVector * pVector, tHDU h)
{
  pVector->Heading = h;
  float r = pVector->Heading * HDUTORADS;
  sincosf(r, &(pVector->sinHeading), &(pVector->cosHeading));
}

/**
 * @brief Set the Vector heading using degrees
 *
 * @note: HERE BE DRAGONS!!!
 * the degree parameter MUST BE in [-180 .. 179.99]
 * (exact upper limit is 180 * ((MAXANGLE_HDUS-1)/MAXANGLE_HDUS) )
 * else if will default to the INT16_MIN value and break silently and hilariously
 *
 * @param pVector Vector to update
 * @param d Degree in +/- 180
 */
inline static void VECTOR_HEADING_SET_DEG(tVector * pVector, float d)
{

#ifdef __QNX__
  if (d != d)
#elif defined __cplusplus
  if (std::isnan(d))
#else
  if (isnan(d))
#endif
  {
    pVector->Heading = 0; // we don't have a value that means "invalid"...
    pVector->sinHeading = pVector->cosHeading = NAN;
  }
  else
  {
    pVector->Heading = d * DEGSTOHDUS;
    // could calculate"r" directly from "d".
    // This is more accurate (as we're not rounding off to 16 bits) but
    // means Heading is inconsistent with the cached sin/cos.
    float r = pVector->Heading * HDUTORADS;
    sincosf(r, &(pVector->sinHeading), &(pVector->cosHeading));
  }
}

#define VECTOR_HEADING_SET_UNAVAIL(v)           \
  do                                            \
  {                                             \
    (v)->Heading    = 0;                        \
    (v)->cosHeading = NAN;                      \
    (v)->sinHeading = NAN;                      \
  } while(0)

#define VECTOR_HEADING_IS_UNAVAIL(v)      \
  (isnan((v)->cosHeading)                 \
   ||                                     \
   isnan((v)->sinHeading))

#define VECTOR_HEADING_IS_AVAIL(v)        \
  (!VECTOR_HEADING_IS_UNAVAIL(v))

/**
 * tVectorSeparation:
 *
 * Difference between two Vectors (From 0 to 1)
 *
 * In the diagram below:
 *
 * @verbatim
         ^
         | NORTH,y (0)
         + --> EAST,x (16384)

           _
           /|
       (0)/ (slow, NE, steady, current)

                      (1)| (fast, S, decelerating, 5 seconds old)
                         |
                         |
                         |
                         |
                         V
 @endverbatim
 *
 *  x10:  large and positive ((1) is east of (0))\n
 *  y10:  small and negative ((1) is just south of (0))\n
 *  e10:  0 ((0) and (1) have the same elevation)\n
 *  r10:  sqrt(x10**2 + y10**2) (pythagoras)\n
 *  v10:  large and positive (we're moving away form each other)\n
 *  a10:  negative (rate of separation is decreasing)\n
 *  b10:  ~18000   (1) slightly south of due east of (0)\n
 *  h10:  ~24000   (1) is moving to the right rear of (0)\n
 * rb10:  ~10000   (1) is moving slightly right relative to the (0)\n
 *  t10:  -5461    (5000 ms * (65536 / 60000))\n
 *
 * All distances in mm (except elevation which is in cm)
 * All angles    in tHDU
 * All times     in Normalised Minute Units
 * Speed         in mm per Normalised Minute Units
 * Acceleration  in mm per (Normalised Minute Units)^2
 *
 */
typedef struct {
   float    x10; ///< Easting from 0 to 1 (mm)
   float    y10; ///< Northings from 0 to 1 (mm)
   int32_t  e10; ///< Elevation from 0 to 1 (cm)
   float    r10; ///< Range: Distance between Locations (mm)
   float    v10; ///< Rel Speed: Rate of change of separation (mm per Normalised Minute Unit!)
   float    a10; ///< Rel Accel: Rate of change of Rate of change of separation (mm per (Normalised Minute Unit)^2)
   tHDU     b10; ///< Bearing to 1 from 0 (tHDU)
   tHDU     h10; ///< Heading of 1 relative to 0 (tHDU)
   tHDU     rb10;///< Relative bearing of 1 from 0 (tHDU)
   int16_t  t10; ///< Time difference. Normalised Minute Units (2^16 ticks per minute)
} tVectorSeparation;

/// Vector Error Codes
typedef enum
{
  VECTOR_ERR_NONE       =  0, ///< OK
  VECTOR_ERR_NULL       =  7, ///< Vector is NULL
  VECTOR_ERR_FILE_NULL  =  8, ///< Tried to print to NULL file handle
} tVectorErrCode;


//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

tVectorErrCode Vector_Clear(tVector *pVector);

bool Vector_Advance(tVector *pVector,
                    int16_t dt,
                    float *pDistance_mm)
  __attribute__((warn_unused_result));

tVectorErrCode Vector_Copy(const tVector *pVectorFrom,
                           tVector *pVectorTo)
  __attribute__ ((deprecated));

tVectorErrCode Vector_fwrite(FILE *fp,
                             const tVector *pVector);

tVectorErrCode Vector_printf(const tVector *pVector);

tVectorErrCode Vector_fprintf(FILE *fp,
                              const tVector *pVector);

tVectorErrCode Vector_fprintf_native(FILE *fp,
                                     const tVector *pVector);

int Vector_snprintf(char *buf,
                    size_t size,
                    const tVector *pVector);

void Vector_Separation(const tVector *pVector1,
                       const tVector *pVector0,
                       tVectorSeparation *pSeparation);

void VectorSeparation_printf(const tVectorSeparation *pSeparation);

int VectorSeparation_snprintf(char *buf,
                              size_t size,
                              const tVectorSeparation *pSeparation);

float Vector_HeadingDiffDegs(const tVector *pVectorFrom,
                             const tVector *pVectorTo);

float Vector_DistSquared(const tVector * pVA,
                         const tVector * pVB);

float Vector_SegmentIntersect(const tVector *pA,
                              const tVector *pB,
                              float *pAt_m,
                              float *pBt_m);

float Vector_SegmentIntersectPlus(const tVector *pA,
                                  const tVector *pB,
                                  float *pAt_m,
                                  float *pBt_m,
                                  float *pBAx_m,
                                  float *pBAy_m);

float dLat2dY(float dLat_Degs);

float dY2dLat(float dY);

float dLon2dX(float dLon_Degs, float Lat_Degs);

float dX2dLon(float dX, float Lat_Degs);

float dLat2dYmm(float dLat_Degs);

float dYmm2dLat(float dY);

float dLon2dXmm(float dLon_Degs, float Lat_Degs);

float dXmm2dLon(float dX, float Lat_Degs);

#ifdef __cplusplus
}
#endif

#endif // VECTOR_DEF


// Close the doxygen group
/**
 * @}
 */
