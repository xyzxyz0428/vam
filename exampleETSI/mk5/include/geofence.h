/**
 * @addtogroup <module_name> <Free text description of the module>
 * @{
 *
 * <Top-level (overview) documentation about the module goes here>
 *
 * @note This should be sparse as functionality is preferably described in
 *       the .c files
 *
 * @file <Brief description of the file's contents/functionality>
 *
 * <Detailed information about this file's functionality goes here>
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __GEOFENCE_H__
#define __GEOFENCE_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "raycast.h"

// only for .h files!
#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
//Define as fixed
#define MAX_POLYGON_NAME    50

#define MAX_COORDINATE_ENTRY 600

#define INFINITE_SLOPE FLT_MAX

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef struct GeoFenceImportPolygon
{
  /// Basic polygon type (array of coordinates)
  tPoint2D * aGeoFenceNewCoordinates;
  /// Number of Coordinates in the polygon
  int NumCoordinates;
  /// Name of the Polygon
  char PolygonName[MAX_POLYGON_NAME + 1];
} tGeoFenceImportPolygon;

/// List of polygons used for relevancy checks
typedef struct GeoFencePolygonList
{
  /// Polygon Name (if applicable)
  char PolygonName[MAX_POLYGON_NAME + 1];
  /// Polygon Unique ID incremented from 0
  int PolygonID;
} tGeoFencePolygonList;

/// Polygon
typedef struct GeoFencePolygon
{
  /// Raycast
  tRaycastPolygon Polygon;
  /// Polygon Name (if applicable)
  char PolygonName[MAX_POLYGON_NAME + 1];
  /// Polygon Unique ID incremented from 0
  int PolygonID;
} tGeoFencePolygon;

typedef void(fGeoFence_Callback) (const tGeoFencePolygonList *apRelevantPolygons,
                                  int NumPolygons);

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int GeoFence_Init(int SchedulerPolicy,
                  int SchedulerPriority);

void GeoFence_Exit();

int GeoFence_RegisterCallback(fGeoFence_Callback *pCallback,
                              void *pPriv);

int GeoFence_DeregisterCallback(fGeoFence_Callback *pCallback);

int GeoFence_ImportNewPolygons(tGeoFenceImportPolygon *aNewPolygons,
                               int NumPolygons);

// only for .h files!
#ifdef __cplusplus
}
#endif

#endif // __GEOFENCE_H__

// Close the doxygen group
/**
 * @}
 */
