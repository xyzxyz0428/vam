#pragma once
/**
 * @addtogroup cohda_spat_cn_api Signal Phase and Timing (SPaT) (for CN) helpers API
 * @{
 *
 * @file spat-cn-rx.h
 *
 * SPaT module main function definitions
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __SPAT_CN_RX_H_
#define __SPAT_CN_RX_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "default_stack_defn.h"
#include "ext.h"
#include "lph.h"
#include "point-2d.h"
#include "qs-lib.h"
#include "saecasn.h"
#include "saecasn_def.h"
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

/// Maximum number of links to be evaluated and returned to client.
#define MAX_EVAL_LINKS            32
/// Maximum number of lanes to be evaluated and returned to client.
#define MAX_EVAL_LANES            32

/// Time to signal change is undefined/unknown
#define TIME_SIG_CHANGE_UNDEFINED 36001

/// Time to signal change is > 3600 seconds
#define TIME_SIG_CHANGE_MAX       36000

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Light colours
typedef enum SPATMAPCNLightColorState
{
  SIGCOLOR_OFF,
  SIGCOLOR_SOLID_GREEN,
  SIGCOLOR_SOLID_YELLOW,
  SIGCOLOR_SOLID_RED,
} eSPATMAPCNLightColorState;

typedef enum SPATMAPCNLightWarning
{
  SPATMAPCN_WARN_UNKNOWN,
  SPATMAPCN_WARN_INACTIVE,
  SPATMAPCN_WARN_ACTIVE
} eSPATMAPCNLightWarning;

/// Simple (i.e. generic) node set format.
/// Nodes are ordered from upstream to downstream (following the car's driving direction)
/// - Tab[0] is the point furthest from the stop line.
/// All the points contain the offsets from refPos in cm.
typedef struct MAPNodeSetXY
{
  tPoint2D Tab[SAECNodeList_SeqSize_Max];
  size_t Count;
} tMAPNodeSetXY;

/// Speed Limit
typedef struct SPATMAPCNSpeedLimit
{
  SAECSpeedLimitType Type;
  float Speed_mps;
} tSPATMAPCNSpeedLimit;

/// Speed Limit List
typedef struct SPATMAPCNSpeedLimitList
{
  tSPATMAPCNSpeedLimit Tab[SAECSpeedLimitList_SeqSize_Max];
  size_t Count;
} tSPATMAPCNSpeedLimitList;

/// SPATMAPCN Lights information
typedef struct SPATMAPCNLightInfo
{
  /// Sets if the Light information is available.
  bool Available;
  /// Current (or next) signal state of all lights pertaining to this lane
  eSPATMAPCNLightColorState TrfcClr;
  /// Indicates when a signal phase is predicted to change (step of 1/10 second)
  int TimChng_ds;
  /// Wait on Stop
  eSPATMAPCNLightWarning WaitOnStop;
  /// Protected movement
  bool ProtectedMovement;
} tSPATMAPCNLightInfo;

/// SPATMAPCN Lights information
typedef struct SPATMAPCNSignals
{
  // information about the different signals that may apply to this lane
  // "ball" (i.e. the default, round traffic signal)
  tSPATMAPCNLightInfo Ball;
  // left-turn arrow
  tSPATMAPCNLightInfo Left;
  // right-turn arrow
  tSPATMAPCNLightInfo Right;
  // U-turn
  tSPATMAPCNLightInfo UTurn;
} tSPATMAPCNSignals;

/// Lane IDs for corresponding egress lanes, -1 for unconnected
typedef struct SPATMAPCNEgressLaneIds
{
  SAECLaneID Ball;
  SAECLaneID Left;
  SAECLaneID Right;
  SAECLaneID UTurn;
  SAECLaneID Default;
} tSPATMAPCNEgressLaneIds;

/// Output of fine evaluation is a set of links with associated signals
typedef struct SPATMAPCNEvaluatedLink
{
  /// Flag indicated if lane is found in any states of associated SPaT or not
  bool IsFound;
  /// Integer presenting link number used to associate SPaT and Map
  int LinkId;
  /// Current shortest perpendicular distance (m) between vehicle and this lane
  float DistanceToLink_m;
  /// Stop line latitude (degree) and longitude. NAN if unavailable
  tPoint2D StopLineLatLon;
  /// Current distance to the Stop Line of this link (m)
  float DistanceToStopLine_m;
  /// Angle between link alignment (lane bearing) and current vehicle heading
  float AlignmentAngle_deg;
  /// Confidence factor for the returned links, based on angle and distance
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
  tSPATMAPCNSignals Signals;
} tSPATMAPCNEvaluatedLink;

/// Output of fine evaluation is a set of lanes with associated signals
typedef struct SPATMAPCNEvaluatedLane
{
  /// Flag indicated if lane is found in any states of associated SPaT or not
  bool IsFound;
  /// Integer presenting Link Idx in @ref SPATMAPCNEvaluatedLink
  int LinkIdx;
  /// Integer presenting lane number used to associate SPaT and Map
  int LaneId;
  /// Current shortest perpendicular distance (m) between vehicle and this lane
  float DistanceToLane_m;
  /// Stop line latitude (degree) and longitude. NAN if unavailable
  tPoint2D StopLineLatLon;
  /// Current distance to the Stop Line of this lane (m)
  float DistanceToStopLine_m;
  /// Angle between lane alignment (lane bearing) and current vehicle heading
  float AlignmentAngle_deg;
  /// Confidence factor for the returned lanes, based on angle and distance
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
  tSPATMAPCNSignals Signals;
  // maybe store the egress lane IDs in tSPATMAPCNLightInfo?
  tSPATMAPCNEgressLaneIds EgressLaneIds;
} tSPATMAPCNEvaluatedLane;

/// Some extra needed information for each Link, used to ease evalaution
typedef struct SPATMAPCNExtraLinkInfo
{
  /// Integer presenting Link number
  int  LinkId;
  /// Link width for this Link in cm
  int  LinkWidth_cm;
  /// Bearing of the segment cloest to the stop line
  float Bearing;
  /// Simple node set translated from all node set formats
  tMAPNodeSetXY SimpleNodeSet;
  /// Speed Limits
  tSPATMAPCNSpeedLimitList SpeedLimitList;
} tSPATMAPCNExtraLinkInfo;

/// Array of size equals to intersection Links holds extra Links information
typedef struct SPATMAPCNExtraLinkInfoArray
{
  // Dynamically allocated array of Links, each entry holds Link extra info
  tSPATMAPCNExtraLinkInfo *Links;
  // Size of allocated array above (equals to ITSLinkList.count)
  size_t Count;
} tSPATMAPCNExtraLinkInfoArray;

/// Some extra needed information for each lane, used to ease evalaution
typedef struct SPATMAPCNExtraLaneInfo
{
  /// Integer presenting lane number
  int LaneId;
  /// Lane width for this lane in cm
  int LaneWidth_cm;
  /// Bearing of the segment cloest to the stop line
  float Bearing;
  /// Link this lane belongs to
  int LinkId;
  /// Egress Lanes
  tSPATMAPCNEgressLaneIds EgressLaneIds;
  /// Simple node set translated from all node set formats
  tMAPNodeSetXY SimpleNodeSet;
  /// Speed Limits
  tSPATMAPCNSpeedLimitList SpeedLimitList;
} tSPATMAPCNExtraLaneInfo;

/// Array of size equals to intersection lanes holds extra lanes information
typedef struct SPATMAPCNExtraLaneInfoArray
{
  // Dynamically allocated array of lanes, each entry holds lane extra info
  tSPATMAPCNExtraLaneInfo *Lanes;
  // Size of allocated array above (equals to ITSLaneList.count)
  size_t Count;
} tSPATMAPCNExtraLaneInfoArray;

/// Intersection structure referencing both SPaT and Map
typedef struct SPATMAPCNIntersection
{
  /// Flag for intersection relevance based on current vehicle position
  /// Intersection is irrelevant if behind vehicle or distance is out of range
  bool IsRelevant;
  /// Flat set if vehicle is heading to this intersection (function in distance)
  bool IsHeadingFor;
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
  const SAECNode *pIntersection;
  /// Pointer to intersection state data, extracted from SPAT message
  /// P.S: if we are sure SPAT has one intersection, this field is not needed
  const SAECIntersectionState *pIntersectionState;
  /// Most relevant link to vehicle position for this intersection
  int LinkId;
  /// Array of evaluated lanes that used for fine evaluation if app requires
  tSPATMAPCNEvaluatedLane* aEvaluatedLanes;
  /// Number of previous evaluated lanes - output if fine grained evaluation
  int NumEvaluatedLanes;
  /// Array of evaluated lanes that used for fine evaluation if app requires
  tSPATMAPCNEvaluatedLink* aEvaluatedLinks;
  /// Number of previous evaluated lanes - output if fine grained evaluation
  int NumEvaluatedLinks;
  /// Distance (in cm) in X/Y axis from vehicle to RSU reference point
  tPoint2D VehXY;
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
  /// Extra link informations
  tSPATMAPCNExtraLinkInfoArray ExtraLinkInfoArray;
  /// Extra lane informations
  tSPATMAPCNExtraLaneInfoArray ExtraLaneInfoArray;
  /// Reception or last update time stamp for this intersection (ms since epoch)
  uint64_t LastUpdated;
  /// Snapshot of current position at which this intersection is evaluated
  tLPHPos LPHPos;
} tSPATMAPCNIntersection;

/// SPAT/MAP thread state
typedef enum SPATMAPCNThreadState
{
  /// Not initialized
  SPATMAPCN_THREAD_STATE_NONE = 0x00,
  /// Initializing
  SPATMAPCN_THREAD_STATE_INIT = 0x01,
  /// Running
  SPATMAPCN_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  SPATMAPCN_THREAD_STATE_STOP = 0x04,
  /// Stopped
  SPATMAPCN_THREAD_STATE_END  = 0x08,
} eSPATMAPCNThreadState;
/// @ref SPATMAPCNThreadState
typedef int tSPATMAPCNThreadState;

/// Supported return error codes. All errors are negative
typedef enum
{
  /// No error
  SPATMAPCN_STATUS_OK = 0,
  /// Generic error
  SPATMAPCN_STATUS_ERROR = -1,
  /// Error code for register API: lock failure
  SPATMAPCN_STATUS_ELOCK = -101,
  /// Error code for register API: registration errors
  SPATMAPCN_STATUS_EHANDLE = -102,
} eSPATMAPCNStatus;

/// SPAT receiver state
typedef struct SPATMAPCN
{
  /// ID of SPAT receiver thread
  pthread_t ThreadID;
  /// SPAT receiver thread state
  tSPATMAPCNThreadState ThreadState;
  /// Configuration
  tdefault_stack_Cohda_SPATMAP Params;
  /// LPH
  void *pLPH;
  /// VState
  tUtilBufferQueueReader *pVState_Reader;
  /// Current position at any given moment - periodically updated
  tLPHPos LPHPos;
  /// Array of intersections, to store all "recent" intersection data
  tSPATMAPCNIntersection *aStoredIntersections;
  /// Array of intersection pointers, updated periodically with relevant ones
  tSPATMAPCNIntersection **apRelevantIntersections;
  /// Identifier for Timer
  timer_t PeriodicId;
  /// Timer specification (for normal operation)
  struct itimerspec TNormalSpec;
  /// Timer specification (for fast operation)
  struct itimerspec TFastSpec;
  /// Timer signalling event
  struct sigevent PeriodicEvt;
} tSPATMAPCN;

/** Force select the egress lanes */
typedef enum SPATMAPCNLaneSelection
{
  /// Select highest confidence lane with turn information that doesnt contradict an active driver
  /// turn signal of LEFT or RIGHT
  SPATMAPCN_LANE_SELECTION_POSITION_AND_TURN = 0,
  /// Select most confident lane (based on position only)
  SPATMAPCN_LANE_SELECTION_POSITION
} eSPATMAPCNLaneSelection;

/// @ref SPATMAPCNLaneSelection
typedef uint8_t tSPATMAPCNLaneSelection;

/** Force select the egress lane */
typedef enum SPATMAPCNDirection
{
  SPATMAPCN_DIRECTION_UNKNOWN = 0, ///< Don't force select
  SPATMAPCN_DIRECTION_STRAIGHT,    ///< Force select the straight egress lane
  SPATMAPCN_DIRECTION_LEFT,        ///< Force select the left egress lane
  SPATMAPCN_DIRECTION_RIGHT,       ///< Force select the right egress lane
  SPATMAPCN_DIRECTION_UTURN        ///< Force select the uturn egress lane
} eSPATMAPCNDirection;

/// @ref SPATMAPCNDirection
typedef uint8_t tSPATMAPCNDirection;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
* @brief Type for periodic evaluation callback function
* @param apRelevantIntersections Array of pointers of relevant intersections
* @param Size size of relevant intersections array
*/
typedef void(fSPATMAPCN_Callback) (tSPATMAPCNIntersection **apRelevantIntersections,
                                   int Size);

/**
 * initialise SPAT activity. Should be called before any API in
 * the spat-map module
 *
 * @brief Allocate SPAT object then setup thread and associated data structures
 * @param pAttr POSIX thread attributes (deprecated, not used).
 * @return Handler of opened SPaT structure, NULL if failed
 * @ref SPATMAPCN_Close()
 */
tSPATMAPCN *SPATMAPCN_Open(pthread_attr_t *pAttr);

/**
 * @brief Stop execution of SPAT and free the thread and associated resources
 */
void SPATMAPCN_Close(void);

/**
 * Return number of currenty "active" intersections within the past
 * period. Period is passed as parameter to this function. The function loops
 * local aStoredIntersections and count all non-zero entries updated within
 * passed period
 *
 * @brief Return number of currenty intersections stored in local array
 * @param ActivePeriod Period (sec) within it intersection is considered active
 * @return Number of current intersections
 */
int SPATMAPCN_GetNumIntersections(uint32_t ActivePeriod);

/**
 * Fine-grained evaluation is used to determine the specific signal
 * groups which are relevant to the host vehicle. Output of this evaluation is
 * building of aEvaluatedLanes to reflect all relevant lanes (up to max size)
 * associated with confidence factor, and SPaT states
 *
 * It is responsibility of application to allocate an array of desired size,
 * and pass a pointer to array with the allocated size. Number of evaluated
 * lanes will be less than or equal passed (desired) size
 * @note This function must be invoked within the SPAT callback.
 *
 * @brief Fine grained evaluation to get the vehicle specific movements
 * @param[in,out] pSpatMapIn One relevant intersection selected earlier via evaluation
 * @return Number of evaluated lanes per this intersection/approach
 */
int SPATMAPCN_FineGrainedEvaluation(tSPATMAPCNIntersection *pSpatMapIn);

/**
 * Application can register a callback to be called once a new
 * evaluation is executed and a new approach is found relevant
 *
 * @brief Register callback to be called after periodic course evaluation
 * @param Callback callback function
 * @return handle of client - application should use this handle to de-register
 */
int SPATMAPCN_RegisterPeriodicCallback(fSPATMAPCN_Callback Callback);

/**
 * De-register callback registered earlier. Application should call
 * this API when decides not to receive any more updates about SpatMap eval
 *
 * @brief De-register callback registered earlier
 * @param Handle Handle to de-register as obtained though register API
 * @return Zero for success or a negative errno
 */
int SPATMAPCN_DeregisterPeriodicCallback(int Handle);

/**
 * @brief Find the most suitable intersection, lane and light information
 * @note This function must be invoked within the SPAT callback.
 *
 * @param [in,out] apRelevantIntersections Array of pointers to candidate intersections
 * @param Size Length of apRelevantIntersections
 * @param LaneSelectionPolicy Selection policy using @ref tSPATMAPCNLaneSelection
 * @param PriorityDirection Optionally force the selection of egress lane
 * @param[out] pEgressLaneId (optional) where to store egress ID
 * @param[out] ppSpatMapIn Where to return pointer to best intersection
 * @param[out] ppLane Where to return pointer to best lane
 * @param[out] ppInfo Where to return pointer to best light info
 */
void SPATMAPCN_FindMostConfident(tSPATMAPCNIntersection  ** apRelevantIntersections,
                                 size_t Size,
                                 tSPATMAPCNLaneSelection LaneSelectionPolicy,
                                 tSPATMAPCNDirection PriorityDirection,
                                 int * pEgressLaneId,
                                 const tSPATMAPCNIntersection  ** ppSpatMapIn,
                                 const tSPATMAPCNEvaluatedLane ** ppLane,
                                 const tSPATMAPCNLightInfo     ** ppInfo);

#ifdef __cplusplus
}
#endif

#endif // __SPAT_CN_RX_H_
// Close the doxygen group
/**
 * @}
 */
