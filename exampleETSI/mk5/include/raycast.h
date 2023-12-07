/**
 * @addtogroup Geometry
 * @{
 *
 * Raycast algorithm to determine whether a point is inside a polygon
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_GEOMETRY_RAYCAST_H_
#define __PLAT_GEOMETRY_RAYCAST_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------

#include "point-2d.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

// Polygon edge for the raycast algorithm
typedef struct RaycastEdge
{
  tPoint2D PointA;
  tPoint2D PointB;

  /// The equation of line for which this edge is a line segment
  /// latitude = Slope * longitude + Offset
  /// (vertical lines are denoted by an infinite slope value)
  double Slope;
  double Offset;
} tRaycastEdge;

typedef struct tRaycastPolygon
{
  /// Bounding box
  tPoint2D Min;
  tPoint2D Max;
  /// Table of edges
  tRaycastEdge *pEdges;
  /// Number of entries in the edge table below
  size_t NumEdges;
} tRaycastPolygon;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

bool Raycast_Create(const tPoint2D * pPoints, size_t NumPoints, tRaycastPolygon * pPolygon);
bool Raycast_InsidePolygon(const tRaycastPolygon * pPolygon, const tPoint2D * pPos);
bool Raycast_EdgeIntersect(const tRaycastEdge *pEdge, const tPoint2D * pPos);
void Raycast_Destroy(tRaycastPolygon * pPolygon);

#ifdef __cplusplus
}
#endif

#endif /* __PLAT_GEOMETRY_RAYCAST_H_ */

/**
 * @}
 */
