/**
 * 2D points and operations on simple operations on 2D points
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_GEOMETRY_POINT2D_H_
#define __PLAT_GEOMETRY_POINT2D_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef struct Point2D
{
  /// Northings [mm]
  union {
    double Latitude;
    double Northings;
    double N;
    double Y;
  };
  /// Eastings [mm]
  union {
    double Longitude;
    double Eastings;
    double E;
    double X;
  };
} tPoint2D;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Translate a point.
 *
 * @param pPoint The point to translate
 * @param X X delta to apply
 * @param Y Y delta to apply
 */
static inline void Point2D_Translate(tPoint2D *pPoint, float X, float Y)
{
  if (pPoint != NULL)
  {
    pPoint->X = pPoint->X + X;
    pPoint->Y = pPoint->Y + Y;
  }
}

/**
 * @brief Rotate a point around an optional pivot.
 *
 * @param pPoint The point to rotate
 * @param angle_rad counter clockwise rotation to apply in radians.
 * @param pPivot optional pivot point
 */
void Point2D_Rotate(tPoint2D *pPoint, float angle_rad, const tPoint2D *pPivot);

/**
 * @brief   Check whether a point lies within the shape point set defined
 *          in the provided shape point set.
 *
 * @param pShapePointSet Provided shape point set to check.
 *                       They all share the same reference point and unit with pPositin.
 * @param NumPoints      Number of points in the list
 * @param pPosition      Provided X,Y position to check
 * @param LaneWidth      Effective lane width of shape point set. Must be in
 *                       the same unit as pPosition asl well.
 *
 * @return true if the point lies within the shape point set, otherwise false
 */
bool Point2D_InShapePointList(const tPoint2D * pShapePointList,
                              size_t NumPoints,
                              const tPoint2D * pPosition,
                              float LaneWidth);
/**
 * @brief   Check whether a point lies within the circle defined by the ref pos
 *          and radius.
 *
 * @param Radius Radius of the circle with the reference position as the centre.
 * @param pPos Provided X,Y offset relative to a reference position.
 *
 * @return true if the point lies within the circle, otherwise false
 */
bool Point2D_InCircle(float Radius,
                      const tPoint2D * pPos);

/**
 * @brief Calculate linear distance between two points given X-Y for each
 * @param pA First point. Same unit must be used for all inputs
 * @param pB Second point. Same unit must be used for all inputs
 * @return Linear distance between 1st and 2nd points (in same passed units)
 */
float Point2D_Distance(const tPoint2D * pA, const tPoint2D * pB);

/**
 * @brief Calculate linear distance in metres between two points given Lat-Lon for each
 * @param pA First point. Same linear unit must be used for all inputs
 * @param pB Second point. Same linear unit must be used for all inputs
 * @return Linear distance between 1st and 2nd points (in metres)
 */
float Point2D_DistanceLatLon(const tPoint2D * pALatLon, const tPoint2D * pBLatLon);

/**
 * Description Calculate linear distance to a certain segment defined by its
 * start and end points - all inputs should be in same units
 *
 * @brief calculate distance between a point and segment (defined by 2 points)
 * @param pSegStart segment start point
 * @param pSegEnd segment end point
 * @param pPoint required point to calculate distance from
 * @return Linear distance between point and segment (in same passed units)
 */
float Point2D_DistanceToSegment(const tPoint2D * pSegStart,
                                const tPoint2D * pSegEnd,
                                const tPoint2D * pPoint);

/**
 * @brief Get shortest perpendicular distance to a given lane
 * @param pShapePointList Pointer to current lane to which we want to get distance
 *                   They all share the same reference point and unit with pPositin.
 * @param NumPoints Number of points to represent the lane.
 * @param pPosition Position to check.
 * @param[out] pBearing If non-NULL it returns the bearing of the closest segment.
 *                      Note that consistent with @ref tHDU and J2735 DE_Heading, 0 means north
 *                      and 180 means south. This segment starts from pPointList[i] and ends
 *                      at pShapePointList[i + 1]
 * @return Shortest perpendicular distance (in cm) to this lane. NAN if the input is valid.
 */
float Point2D_DistanceToPointList(const tPoint2D * pShapePointList,
                                  size_t NumPoints,
                                  const tPoint2D * pPosition,
                                  double * pBearing_deg);

/**
 * @brief Calculate bearing between two points
 * @param pP1 First point. Same linear unit must be used for all inputs
 * @param pP2 Second point. Same linear unit must be used for all inputs
 * @return Bearing angle in degrees from first to second point (0 to 360)
 */
double Point2D_Bearing(const tPoint2D * pP1, const tPoint2D * pP2);


double Point2D_HaversineDistanceLatLon(const tPoint2D * pALatLon,
                                       const tPoint2D * pBLatLon);

tPoint2D Point2D_GreatCircleMidpoint(const tPoint2D * pALatLon,
                                     const tPoint2D * pBLatLon);

/**
 * @brief Distance estimate (using Equirectangular approximation).
 *
 * @param [in] Lat0_deg7
 * @param [in] Lon0_deg7
 * @param [in] Lat1_deg7
 * @param [in] Lon1_deg7
 *
 * @return Distance in meters between point 0 and point 1
 */
float Point2D_DistanceLL7_m(const int32_t Lat0_deg7,
                            const int32_t Lon0_deg7,
                            const int32_t Lat1_deg7,
                            const int32_t Lon1_deg7);
/**
 * @brief Distance estimate (using Equirectangular approximation).
 *
 * @param [in] Lat0_deg
 * @param [in] Lon0_deg
 * @param [in] Lat1_deg
 * @param [in] Lon1_deg
 *
 * @return Distance in meters between point 0 and point 1
 */
float Point2D_DistanceLL_m(const double Lat0_deg,
                           const double Lon0_deg,
                           const double Lat1_deg,
                           const double Lon1_deg);


#ifdef __cplusplus
}
#endif

#endif // __PLAT_GEOMETRY_POINT2D_H_
// Close the doxygen group
/**
 * @}
 */
