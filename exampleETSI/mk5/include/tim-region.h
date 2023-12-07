/**
 * @addtogroup cohda_tim_api Traveler Information Messages (TIM) API
 * @{
 *
 * @section mod_tim_region_dd What Does It Do
 * Provides functionality for processing the region specified in
 * Traveler Information Messages
 *
 * @file tim-region.h
 *
 * Region definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TIM_REGION_H_
#define __TIM_REGION_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "lph.h"
#include "j2735-message.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define METRES_PER_FOOT (0.3048)
#define METRES_PER_YARD (3    * METRES_PER_FOOT)
#define METRES_PER_MILE (1760 * METRES_PER_YARD)

// J2735-2016 DF_TravelerDataFrame has 1 to 16 regions (GeographicalPath)
#define J2735_GEOGRAPHICALPATH_MINCOUNT (1)
#define J2735_GEOGRAPHICALPATH_MAXCOUNT (16)

// J2735-2016 DF_NodeSetXY and DF_NodeSetLL have 2 to 63 items
#define J2735_NODESET_MINCOUNT (2)
#define J2735_NODESET_MAXCOUNT (63)

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

// Choice for type of area per TIM region
typedef enum TIMAreaChoice
{
  TIM_AREA_SHAPE_POINT_SET = 0,
  TIM_AREA_CIRCLE = 1,
} eTIMAreaChoice;

/// Type of TIM area @ref TIMAreaChoice
typedef uint8_t tTIMAreaChoice;

/// A global position, from which @ref TIMOffset positions can be referenced
typedef struct TIMGloPos
{
  double Lat_deg;
  double Lon_deg;
} tTIMGloPos;

/// Offset to a @ref TIMGloPos
typedef struct TIMOffset
{
  float Northings_m;
  float Eastings_m;
} tTIMOffset;

typedef struct TIMShapePointSet
{
  /// The number of valid crumbs (maximum 63 in J2735-2016)
  uint8_t NumCrumbs;
  // The crumbs, relative to the sign latitude/longitude
  tTIMOffset *pCrumbs;
} tTIMShapePointSet;

typedef struct TIMCircle
{
  /// Radius of circle [m] which extends from the centre which is at the RefPos
  float Radius_m;
} tTIMCircle;

typedef struct TIMRegionArea
{
  /// XY offsets are relative to this point and circles are centred upon it
  tTIMGloPos RefPos;
  /// 16 heading slice bits defining directionality for this region area
  uint16_t Directionality;
  /// Width [m] of valid areas defined by offset points
  float LaneWidth_m;
  /// Choice of area followed by union of area types
  tTIMAreaChoice AreaChoice;
  union
  {
    tTIMShapePointSet ShapePointSet;
    tTIMCircle Circle;
  } Area;
} tTIMRegionArea;


/// Structure representing a TIM region (includes sign and multiple areas)
/**
 * Example TIM Region containing 3 region areas (1 circle, 2 shape point sets):
 *
 * @verbatim
                                               x ============ x
                                            ==
                                         ==
        Sign  - - - - - - - - Ref ==== x
         -   -
         -     -
         -       -
         -          -
         -          Ref ==== x
         -                     ==
      =======                     ==
    ||   -   ||                      x ======== x ====================== x
   ||   Ref   ||
    ||       ||
      =======
 
    Sign         Sign Position (1 per region)
    Ref          Reference Position (1 per region area)
    x            Offset Points (multiple per shape point set)
    - - -        Approach (1 per region area, rectangle between Sign & Ref)
    ======       Region Areas (multiple offset points which define rectangles,
                               or a circle radius which defines circular area)
 
   @endverbatim
 *
 *   For both approach and region areas, widths are defined by the lane widths.
 *   If no lane width(s) explicitly defined in TIM, then will be default width.
 *   The Ref position of a region area may be the same as the Sign position, in
 *   which case there is no approach defined for that region area.
 *
 *   Note: Sign view angle is interpreted as applying to the approaches (all).
 *         Directionality is interpreted as being per region area.
 */
typedef struct TIMRegion
{
  /// Position of the road sign
  tTIMGloPos SignPos;
  /// 16 heading slice bits defining view angle for the road sign
  uint16_t SignViewAngle;

  /// Number of areas defined for this TIM region (maximum 16 in J2735-2016)
  uint8_t NumRegionAreas;
  /// Region areas
  tTIMRegionArea *pRegionAreas;

} tTIMRegion;

typedef enum PointInRegionResult
{
  /// Point is neither inside the region areas, nor on the approach
  POINT_OUTSIDE_REGION = 0,
  /// Point is inside one of the approaches (between the SignPos and a RefPos),
  /// but not inside any of the region areas. (Region area overrides approach).
  POINT_INSIDE_APPROACH = 1,
  /// Point is inside one of the region areas (defined relative to a RefPos)
  /// Note: if also inside an approach, this overrides the approach result.
  POINT_INSIDE_AREAS = 2,
} ePointInRegionResult;

/// @ref PointInRegionResult
typedef uint8_t tPointInRegionResult;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

tTIMRegion *TIMRegion_ExtractFromTIM(const SAETravelerDataFrame *pTIM);

void TIMRegion_Free(tTIMRegion *pRegion);

tPointInRegionResult TIMRegion_PointInRegion(const tTIMRegion *pRegion,
                                             const struct LPHPos *pLPHPos);

float TIMRegion_DistanceToClosestApproach(const tTIMRegion *pRegion,
                                          const struct LPHPos *pLPHPos);

#ifdef __cplusplus
}
#endif

#endif // __TIM_REGION_H_
/**
 * @}
 */
