#pragma once
/**
 * @addtogroup cohda_spat_api Signal Phase and Timing (SPaT) helpers API
 * @{
 *
 * @section cohda_spat_api_dd Generic framework for the implementation of SAE J2735 SPaT/MAP based applications within the Cohda 1609 Facilities Layer
 *
 * Framework is intended to allow for multiple SPaT/MAP-based applications
 * to be easily implemented, with each application only performing the specific
 * steps required for its own operation without unduly repeating calculations
 * made by other similar applications.
 *
 * Objective is to have a common framework which handles the various
 * operations required by each application – i.e. handling incoming SPaT / MAP
 * messages, processing of messages, storage of messages, geolocation of host
 * vehicle within a MAP etc. This common framework should also allow all of
 * SPaT/MAP based applications to be easily implemented using the framework as
 * a basis.
 *
 * MAP messages describe the location and geometry of a given intersection.
 * Signal Phase and Timing (SPaT) messages describe the states of the signal
 * groups for a given intersection. The MAP message is static whilst the SPaT
 * message is generally updated each time it is sent. In general it is assumed
 * MAP messages are transmitted at ~1 message per second, whilst SPaT messages
 * are sent at ~0.1 message per second. This design targets the SPAT/MAP
 * message format as described in SAE J2735 2014.10
 *
 * @file
 * spat-rx.h: SPaT module main function definitions
 *
 */

//==============================================================================
// Copyright (c) 2014
// Cohda Wireless PTY LTD
//==============================================================================

#ifndef __SPAT_RX_2014_H_
#define __SPAT_RX_2014_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "default_stack_defn.h"
#include "ext.h"
#include "itsasn.h"
#include "itsasn_def.h"
#include "lph.h"
#include "raycast.h"
#include "qs-lib.h"
#include "util.h"
#include "vstate.h"

#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Replacement policy: replace new intersection with oldest entry
#define OLDEST_ENTRY            0
/// Replacement policy: replace new intersection with least relevant entry
#define MOST_IRRELEVANT_ENTRY   1

/// TimeMark absolute value (tenths of a second in the current or next hour)
#define TIMEMARK_ABSOLUTE        0
/// TimeMark Relative value (remaining tenths of seconds from now)
#define TIMEMARK_RELATIVE       1

/// Maximum number of lanes to be evaluated and returned to client. As per J2735,
/// approach drivingLanes = SEQUENCE (SIZE(0.. 32)) - we can use this is max
#define MAX_EVAL_LANES            32

/// Time to signal change is undefined/unknown
#define TIME_SIG_CHANGE_UNDEFINED 36002

/// Max time to change is greater than the range allowed by SPaT message
#define TIME_SIG_CHANGE_MAX       36001


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Light colours
typedef enum SPATMAPLightColorState
{
  SIGCOLOR_OFF,
  SIGCOLOR_SOLID_GREEN,
  SIGCOLOR_SOLID_YELLOW,
  SIGCOLOR_SOLID_RED,
} eSPATMAPLightColorState;

typedef enum SPATMAPLightWarning
{
  SPATMAP_WARN_UNKNOWN,
  SPATMAP_WARN_INACTIVE,
  SPATMAP_WARN_ACTIVE
} eSPATMAPLightWarning;

/// Speed Advisory List
typedef struct SPATMAPSpeedAdvisoryList
{
  float AdvisedSpeed_mps;
  int Distance_m;
  int Confidence;
} tSPATMAPSpeedAdvisoryList;

/// Simple node format
typedef struct MAPNodeXY {
  int32_t X_cm;
  int32_t Y_cm;
} tMAPNodeXY;

/// Simple (i.e. generic) node set format
typedef struct MAPNodeSetXY {
  tMAPNodeXY Tab[ITSNodeSetXY_SeqSize_Max];
  tMAPNodeXY Total;
  size_t Count;
} tMAPNodeSetXY;

/// SPATMAP Lights information
typedef struct SPATMAPLightInfo
{
  /// Sets if the Light information is available.
  bool Available;

  /// Current (or next) signal state of all lights pertaining to this lane
  eSPATMAPLightColorState TrfcClr;

  /// Indicates when a signal phase is predicted to change (step of 1/10 second)
  int TimChng_ds;

  /// Speed Advisory List
  tSPATMAPSpeedAdvisoryList *pSpeedAdvisoryList;

  /// Speed Advisory List amount
  int SpeedAdvisoryCount;

  /// Pedestrian/Bicycle Detected
  eSPATMAPLightWarning PedestrianBicycleDetect;

  /// Wait on Stop
  eSPATMAPLightWarning WaitOnStop;

  /// Protected movement
  bool ProtectedMovement;

} tSPATMAPLightInfo;

/// Lane IDs for corresponding egress lanes, -1 for unconnected
typedef struct SPATMAPEgressLaneIds
{
  ITSLaneID Ball;
  ITSLaneID Left;
  ITSLaneID Right;
  ITSLaneID UTurn;
  ITSLaneID Default;
} tSPATMAPEgressLaneIds;

/// Output of fine evaluation is a set of lanes with associated signals
typedef struct SPATMAPEvaluatedLane
{
  /// Flag indicated if lane is found in any states of associated SPaT or not
  bool IsFound;

  /// Integer presenting lane number used to associate SPaT and Map
  int LaneId;

  /// Current shortest perpendicular distance (m) between vehicle and this lane
  float DistanceToLane_m;

  /// Stop line latitude (degree). NAN if unavailable
  double StopLineLat_deg;

  /// Stop line longitude (degree). NAN if unavailable
  double StopLineLon_deg;

  /// Current distance to the Stop Line of this lane (m)
  float DistanceToStopLine_m;

  /// Angle between lane alignment (lane bearing) and current vehicle heading
  float AlignmentAngle_deg;

  // Confidence factor for the returned lanes, based on angle and distance:
  // DistanceFactor:
  //    Scale:  0:90, where 0 is lowest confidence, and 90 is highest
  //    Step:   1 step presents 0.5 meter distance
  //    Sat:    Distance confidence saturates if dist > 45 (conf = 0)
  //    Weight: 90%    -- Distance is of high priority as conf factor
  //
  // AngleFactor:
  //    Scale:  0:10, where 0 is lowest confidence, and 10 is highest
  //    Step:   1 step presents 5 degree
  //    Sat:    Angle confidence saturates if angle > 50 (conf = 0)
  //    Weight: 10%    -- Angle is of low priority as conf factor
  //
  // ConfidenceFactor = DistanceFactor + AngleFactor
  // ConfidenceFactor scale 0 to 100, with step = 1
  int8_t ConfidenceFactor;

  // information about the different signals that may apply to this lane
  // "ball" (i.e. the default, round traffic signal)
  tSPATMAPLightInfo Ball;
  // left-turn arrow
  tSPATMAPLightInfo Left;
  // right-turn arrow
  tSPATMAPLightInfo Right;
  // U-turn
  tSPATMAPLightInfo UTurn;
  // maybe store the egress lane IDs in tSPATMAPLightInfo?
  tSPATMAPEgressLaneIds EgressLaneIds;
  // Signal Group Id
  int SignalGroupId;
} tSPATMAPEvaluatedLane;

/// Some extra needed information for each lane, used to ease evalaution
typedef struct SPATMAPExtraLaneInfo
{
  /// Integer presenting lane number
  int  LaneId;

  /// Lane bearing calculated once for lane to save multiple heavy processing
  float Bearing;

  /// Approach this lane belongs to - this is either from MapData, or deduced
  int ApproachId;

  /// Egress Lanes
  tSPATMAPEgressLaneIds EgressLaneIds;

  /// Whether this lane is signalised as an ingress or egress lane.
  bool IsSignalised;

  /// Simple node set translated from all node set formats
  tMAPNodeSetXY SimpleNodeSet;
} tSPATMAPExtraLaneInfo;

/// Array of size equals to intersection lanes holds extra lanes information
typedef struct SPATMAPExtraLaneInfoArray
{
  // Dynamically allocated array of lanes, each entry holds lane extra info
  tSPATMAPExtraLaneInfo *Lanes;
  // Size of allocated array above (equals to ITSLaneList.count)
  size_t Count;
  // Max Approach ID for this intersection (used for loop only)
  int MaxApproachId;
} tSPATMAPExtraLaneInfoArray;

/// Intersection structure referencing both SPaT and Map
typedef struct SPATMAPIntersection
{
  /// Flag for intersection relevance based on current vehicle position
  /// Intersection is irrelevant if behind vehicle or distance is out of range
  bool IsRelevant;
  /// Flag set if vehicle is heading to this intersection (function in distance)
  bool IsHeadingFor;
  /// Fag set if vehicle is in the intersection conflict area
  bool IsInConflictArea;
  /// Unique identifier for intersection
  int32_t IntersectionId;
  /// Distance (meters) between vehicle and RSU reference point at the moment
  float DistanceToReferencePoint_m;
  /// Angle (degrees) between vehicle heading and vehicle-to-RSU bearing
  float Angle_deg;
  // Confidence factor for the this intersection, based on angle and distance
  // both participating with equal weight. Factor scale 0 to 100, with step = 1
  int ConfidenceFactor;
  /// Pointer to SPAT structure (copy of tExtMessage*)
  tExtMessage *pSpatExt;
  /// Pointer to MAP structure (copy of tExtMessage*)
  tExtMessage *pMapExt;
  /// Pointer to intersection data, extracted from MapData message
  /// P.S: if we are sure MapData has one intersection, this field is not needed
  const ITSIntersectionGeometry *pIntersection;
  /// Pointer to intersection state data, extracted from SPAT message
  /// P.S: if we are sure SPAT has one intersection, this field is not needed
  const ITSIntersectionState *pIntersectionState;
  /// Most relevant approach to vehicle position for this intersection
  int ApproachId;
  /// Array of evaluated lanes that used for fine evaluation if app requires
  tSPATMAPEvaluatedLane* aEvaluatedLanes;
  /// Distance (in cm) in X axis from vehicle to RSU reference point
  float VehX;
  /// Distance (in cm) in Y axis from vehicle to RSU reference point
  float VehY;
  /// Number of previous evaluated lanes - output if fine grained evaluation
  int EvLanesCount;
  /// Right Turn Signal (1=True; 0=False)
  bool IsRightTurnSig;
  /// Left Turn Signal (1=True; 0=False)
  bool IsLeftTurnSig;
  /// Based on vehicle speed, this is the time vehicle take to reach RSU
  int TimeToRsu_ds;
  /// Based on vehicle speed, this is the time vehicle take to reach the
  /// stop line at the intersection
  int TimeToStopLine_s;
  /// Current vehicle speed (m/s)
  float Speed_mps;
  /// Extra lane informations
  tSPATMAPExtraLaneInfoArray ExtraLaneInfoArray;
  /// Conflict area polygon
  tRaycastPolygon ConflictAreaPolygon;
  /// Reception or last update time stamp for this intersection (ms since epoch)
  uint64_t LastUpdated;
  /// Snapshot of current position at which this intersection is evaluated
  tLPHPos LPHPos;
} tSPATMAPIntersection;

/// SPAT/MAP thread state
typedef enum SPATMAPThreadState
{
  /// Not initialized
  SPATMAP_THREAD_STATE_NONE = 0x00,
  /// Initializing
  SPATMAP_THREAD_STATE_INIT = 0x01,
  /// Running
  SPATMAP_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  SPATMAP_THREAD_STATE_STOP = 0x04,
  /// Stopped
  SPATMAP_THREAD_STATE_END  = 0x08,
} eSPATMAPThreadState;
/// @ref SPATMAPThreadState
typedef int tSPATMAPThreadState;

/// Supported return error codes. All errors are negative
typedef enum
{
  /// No error
  SPATMAP_STATUS_OK = 0,
  /// Generic error
  SPATMAP_STATUS_ERROR = -1,
  /// Error code for register API: lock failure
  SPATMAP_STATUS_ELOCK = -101,
  /// Error code for register API: registration errors
  SPATMAP_STATUS_EHANDLE = -102,
} eSPATMAPStatus;


/// SPAT receiver state
typedef struct SPATMAP
{
  /// ID of SPAT receiver thread
  pthread_t ThreadID;
  /// SPAT receiver thread state
  tSPATMAPThreadState ThreadState;
  /// Configuration
  tdefault_stack_Cohda_SPATMAP Params;
  /// LPH
  void *pLPH;
  /// VState
  tUtilBufferQueueReader *pVState_Reader;
  /// Current position at any given moment - periodically updated
  tLPHPos LPHPos;
  /// Array of intersections, to store all "recent" intersection data
  tSPATMAPIntersection *aStoredIntersections;
  /// Array of intersection pointers, updated periodically with relevant ones
  tSPATMAPIntersection **apRelevantIntersections;
  /// Identifier for Timer
  timer_t PeriodicId;
  /// Timer specification (for normal operation)
  struct itimerspec TNormalSpec;
  /// Timer specification (for fast operation)
  struct itimerspec TFastSpec;
  /// Timer signalling event
  struct sigevent PeriodicEvt;
} tSPATMAP;


typedef enum SPATMAPDirection
{
  SPATMAP_DIRECTION_UNKNOWN,
  SPATMAP_DIRECTION_STRAIGHT,
  SPATMAP_DIRECTION_LEFT,
  SPATMAP_DIRECTION_RIGHT,
  SPATMAP_DIRECTION_UTURN
} eSPATMAPDirection;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
* @brief Type for periodic evaluation callback function
* @param apRelevantIntersections Array of pointers of relevant intersections
* @param Size size of relevant intersections array
*/
typedef void(fSPATMAP_Callback) (tSPATMAPIntersection **apRelevantIntersections,
                                 int Size);

tSPATMAP *SPATMAP_Open(void);

void SPATMAP_Close(void);

int SPATMAP_GetNumIntersections(uint32_t ActivePeriod);

int SPATMAP_FineGrainedEvaluation(tSPATMAPIntersection *pSpatMapIn);

int SPATMAP_RegisterPeriodicCallback(fSPATMAP_Callback Callback);

int SPATMAP_DeregisterPeriodicCallback(int Handle);

void SPATMAP_FindMostConfident(tSPATMAPIntersection  ** apRelevantIntersections,int Size,
                               int LaneSelectionPolicy,
                               int * pEgressLaneId,
                               const tSPATMAPIntersection  ** ppSpatMapIn,
                               const tSPATMAPEvaluatedLane ** ppLane,
                               const tSPATMAPLightInfo     ** ppInfo,
                               eSPATMAPDirection PriorityDirection);

#ifdef __cplusplus
}
#endif

#endif // __SPAT_RX_2014_H_
// Close the doxygen group
/**
 * @}
 */
