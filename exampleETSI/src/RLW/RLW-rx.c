/**
 * @addtogroup app_rlw Red Light Warning app plugin
 * @{
 *
 *
 * @dontinclude RLW-rx.c
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "RLW-rx.h"
#include "RLW.h"

#include "j2735-message.h"
#include "debug-levels.h"
#include "spat-rx.h"
#include "util.h"

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL RLW_Cust_App_RLW_DebugLevel

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static fSPATMAP_Callback RLW_SpatCallback;
static void RLW_PrepareAlertInfo(const tSPATMAPIntersection  *pSpatMapIn);

static fTA_NonRVThreatApplication RLW_Eval;

static uint16_t RLW_GenerateNotification(tSPATMAPIntersection *pSpatMapIn);
static uint16_t RLW_AlertLeftMove(tSPATMAPEvaluatedLane *pLane);
static uint16_t RLW_AlertRightMove(tSPATMAPEvaluatedLane *pLane);
static uint16_t RLW_AlertStraightMove(tSPATMAPEvaluatedLane *pLane);
static uint16_t RLW_AlertUTurnMove(tSPATMAPEvaluatedLane *pLane);

static void RLW_GetAlertInfo(tRLWAlertInfo  *pRLWAlertInfo);
static void RLW_PrintApproachOutput(tSPATMAPIntersection *pSpatMapIn);

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

/**
 * Initialze RLW. Once called, the SPaT/Map framework is
 * automatically initialised and process starts in background
 *
 * @brief Initialise the RLW application
 * @return Zero for success or a negative error
 */
int RLWRx_Init(void)
{
  int Res = -ENOSYS;

  d_fnstart(D_TST, NULL, "()\n");

  // Initialize TAAlert
  RLW_PrepareAlertInfo(NULL);

  if ((RLW.Param.ENABLE == 0) ||
      (RLW.Param.REC_ENABLE == 0))
  {
    Res = 0;
    goto Exit;
  }

  // Initialise SPATMAP
  RLW.Rx.SPATMAP.pModule = SPATMAP_Open();
  if (RLW.Rx.SPATMAP.pModule == NULL)
  {
    d_error(D_ERR, 0, "SPATMAP_Open() failed\n");
    goto Error;
  }

  // Register the callback with SpatMap module
  RLW.Rx.SPATMAP.Handle = SPATMAP_RegisterPeriodicCallback(RLW_SpatCallback);
  if (RLW.Rx.SPATMAP.Handle < 0)
  {
    d_error(D_ERR, 0, "Unable to register callback with SpatMap module\n");
    goto Error;
  }

  Res = (int)TA_RegisterNonRVApplication(RLW_Eval,
                                         RLW.Param.REC_SEVERITY_MAX,
                                         &RLW,
                                         NULL,
                                         "RLW");
  if (Res)
  {
    d_printf(D_TST, NULL, "TA_RegisterNonRVApplication(...): %d\n", Res);
    goto Error;
  }

  Res = 0;
  goto Success;

Error:
  RLWRx_Exit();

Exit:
Success:
  d_fnend(D_TST, NULL, "() = %d\n", Res);
  return Res;
}

/**
 * @brief De-initialize the RLWRx
 */
void RLWRx_Exit(void)
{
  d_fnstart(D_TST, NULL, "()\n");

  int Res = TA_DeregisterNonRVApplication(RLW_Eval,
                                          RLW.Param.REC_SEVERITY_MAX);
  if (Res != 0)
  {
    d_printf(D_WARN, NULL, "Failed to deregister RLW TA Callback\n");
  }

  // De-register the periodic Callback
  if (RLW.Rx.SPATMAP.Handle >= 0)
  {
    SPATMAP_DeregisterPeriodicCallback(RLW.Rx.SPATMAP.Handle);
    RLW.Rx.SPATMAP.Handle = -1;
  }

  if (RLW.Rx.SPATMAP.pModule != NULL)
  {
    SPATMAP_Close();
    RLW.Rx.SPATMAP.pModule = NULL;
  }

  d_fnend(D_TST, NULL, "()\n");
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief Find the most suitable intersection, lane and light information
 *
 * @param apRelevantIntersections Array of pointers to candidate intersections
 * @param Size Length of apRelevantIntersections
 * @param ppSpatMapIn Where to return pointer to best intersection
 */
void RLW_FindMostConfident(tSPATMAPIntersection **apRelevantIntersections,
                           int Size,
                           tSPATMAPIntersection **ppSpatMapIn)
{
  d_fnstart(D_TST, NULL, "(%p %d %p)\n",
            apRelevantIntersections, Size, ppSpatMapIn);

  int MaxInConf = 0;
  if ((apRelevantIntersections == NULL) || (ppSpatMapIn == NULL))
  {
    d_printf(D_WARN, NULL, "Invalid arguments\n");
    goto Exit;
  }
  *ppSpatMapIn = NULL;

  uint64_t Now = Util_Now();
  uint64_t Oldest = Now - RLW_MAX_SPAT_AGE_ms;

  int i;
  for (i = 0; i < Size; ++i)
  {
    tSPATMAPIntersection *pIntersection = apRelevantIntersections[i];

    if (pIntersection == NULL)
      continue;

    // eliminate all the intersections that are too old
    if(pIntersection->LastUpdated < Oldest)
      continue;

    // Find the intersection with the highest confidence factor
    if (pIntersection->ConfidenceFactor > MaxInConf)
    {
      *ppSpatMapIn = apRelevantIntersections[i];
      MaxInConf = apRelevantIntersections[i]->ConfidenceFactor;
    }
  }

Exit:
  d_fnend(D_TST, NULL, "(%p %d %p): %d\n",
          apRelevantIntersections, Size, ppSpatMapIn, MaxInConf);
}


/**
 * Callback registered to SpatMap framework. This callback will only
 * be called once PeriodicEvaluation is executed and a relative approach is
 * found. Inside this callback, we can ask for FineGrain for this returned
 * approach to get a list of evaluated lanes with confidence value for each.
 * NOTE: FineGrain should be called here or NEVER called. It is called in Spat
 * worker thread context, and needs to be short execution.
 *
 * @brief Callback from PeriodicEvaluation from SpatMap framework
 * @param apRelevantIntersections Pointer array of output relevant intersections
 * @param Size Size of output array. Array is allocated in framework itself.
 */
void RLW_SpatCallback(tSPATMAPIntersection **apRelevantIntersections,
                      int Size)
{
  d_fnstart(D_TST, NULL, "(%p %d)\n", apRelevantIntersections, Size);

  if ((RLW.Param.ENABLE == 0) ||
      (RLW.Param.REC_ENABLE == 0))
  {
    d_fnend(D_TST, NULL, "(%p %i): !Enable\n",
            apRelevantIntersections, Size);
    goto Exit;
  }

  tSPATMAPIntersection *pSpatMapIn = NULL;

  if ((apRelevantIntersections == NULL) || (Size <= 0))
  {
    RLW_PrepareAlertInfo(NULL);
    d_printf(D_TST, NULL, "No valid intersections\n");
    goto Exit;
  }

  RLW_FindMostConfident(apRelevantIntersections, Size, &pSpatMapIn);

  if (pSpatMapIn == NULL)
  {
    RLW_PrepareAlertInfo(NULL);
    d_printf(D_TST, NULL, "No confident intersection found. Exit!\n");
    goto Exit;
  }

  // Found an intersection to evaluate
  d_printf(D_TST, NULL, "Evaluating IntersectionId = %d, EvLanesCount = %d\n",
           pSpatMapIn->IntersectionId, pSpatMapIn->EvLanesCount);

  SPATMAP_FineGrainedEvaluation(pSpatMapIn);

  RLW_PrintApproachOutput(pSpatMapIn);

  // Check to see whether this SPAT meets alert-triggering conditions
  uint16_t CurrentAlert = RLW_GenerateNotification(pSpatMapIn);
  d_printf(D_TST, NULL, "Current Alert = %u\n", CurrentAlert);
  if (CurrentAlert > 0)
  {
    d_printf(D_TST, NULL, "Red light: alert trigger active\n");
    RLW_PrepareAlertInfo(pSpatMapIn);
  }
  else
  {
    d_printf(D_TST, NULL, "No red light: reset alert latch\n");
    RLW_PrepareAlertInfo(NULL);
  }

Exit:
  d_fnend(D_TST, NULL, "()\n");
}

/**
 * Callback registered to TA framework called every 100ms
 */
static void RLW_Eval(const tTA_HV *pHV,
                     tTAAlert *pAlert,
                     const tTAAlert *pCurrentAlert,
                     void *pPriv)
{
  d_fnstart(D_TST, NULL, "(%p %p %p %p)\n",
            pHV, pAlert, pCurrentAlert, pPriv);

  tRLWAlertInfo RLWAlertInfo;
  RLW_GetAlertInfo(&RLWAlertInfo);

  bool CurrentAlertIsRLW = ((pCurrentAlert != NULL) &&
                            (pCurrentAlert->Type == TA_THREATTYPE_CUSTOM0));

  // If the currently active alert is a RLW
  if (CurrentAlertIsRLW)
  {
    d_printf(D_TST, NULL, "Currently alerting\n");
    // if the alerting intersection is no longer the most relevant
    // or
    // there are no relevant intersections
    if ((pCurrentAlert->ID != RLWAlertInfo.TAAlert.ID) ||
        (RLWAlertInfo.NoInfo))
    {
      // Inform registered alert call back function to cancel alert.
      TA_CancelAlert(pCurrentAlert);
      d_printf(D_TST, NULL, "(%p %p %p %p): no longer relevant\n",
               pHV, pAlert, pCurrentAlert, pPriv);
    }
  }
  else if ((RLWAlertInfo.NoInfo == false) &&
           (RLWAlertInfo.TAAlert.ID > 0))
  {
    // alert structure already set, update level
    // But level should not exceed that used during TA registration
    RLWAlertInfo.TAAlert.Level = RLW.Param.REC_SEVERITY_MAX;

    d_printf(D_TST, NULL, "Reporting RLW Alert (%08"PRIx32" %d)\n",
             RLWAlertInfo.TAAlert.Type, RLWAlertInfo.TAAlert.Level);

    TA_ReportAlert(&RLWAlertInfo.TAAlert);
  }
  d_fnend(D_TST, NULL, "(%p %p %p %p)\n",
          pHV, pAlert, pCurrentAlert, pPriv);
}

/**
 * @brief Populate TAAlert with information
 * @param pSpatMapIn FineGrain output intersection - most relevant approach
 */
static void RLW_PrepareAlertInfo(const tSPATMAPIntersection *pSpatMapIn)
{
  pthread_mutex_lock(&(RLW.Rx.AlertInfo.Mutex));
  if (pSpatMapIn == NULL)
  {
    d_printf(D_WARN, NULL, "No valid data.\n");
    RLW.Rx.AlertInfo.NoInfo        = true;
    RLW.Rx.AlertInfo.TAAlert.ID    = -1;
    RLW.Rx.AlertInfo.TAAlert.Level = TA_SEVERITY_CANCEL;
  }
  else
  {
    RLW.Rx.AlertInfo.NoInfo        = false;
    RLW.Rx.AlertInfo.RxTime        = Util_Now();

    // now fill in the alert...
    tTAAlert * pTAAlert = & RLW.Rx.AlertInfo.TAAlert;
    memset(pTAAlert, 0, sizeof(tTAAlert));

    // generic alert info
    pTAAlert->ID                   = pSpatMapIn->IntersectionId;
    pTAAlert->pLastOTA             = pTAAlert->pLastCert = NULL;
    pTAAlert->Type                 = TA_THREATTYPE_CUSTOM0;
    pTAAlert->Level                = 0; // set by Evaluate
  }
  pthread_mutex_unlock(&(RLW.Rx.AlertInfo.Mutex));
}


/**
 * In this version of the software, it is proposed to alert the
 * driver only for amber and red signals that have a high probability of
 * applying to the vehicle or where that signal might impact through the
 * behaviour of other vehicles
 *
 * @brief Based on evaluated lanes from fine grain, generate driver alert
 * @param pSpatMapIn FineGrain output intersection - most relevant approach
 * @return bit mask presenting all active alerts, or zero if none is active
 */
static uint16_t RLW_GenerateNotification(tSPATMAPIntersection *pSpatMapIn)
{
  int i;
  uint16_t DriverAlert = 0;

  if(pSpatMapIn->IsLeftTurnSig == true)
  {
    // Only left signal groups will be evaluated. Left state for all lanes are
    // evaluated, regardless of lane confidence factor
    for(i = 0; i < pSpatMapIn->EvLanesCount; i++)
    {
      tSPATMAPEvaluatedLane *pLane = &pSpatMapIn->aEvaluatedLanes[i];
      if(pLane->IsFound == true)
      {
        DriverAlert |= RLW_AlertLeftMove(pLane);
      }
    }
  }
  else if(pSpatMapIn->IsRightTurnSig == true)
  {
    // Only right signal groups will be evaluated. Right state for all lanes are
    // evaluated, regardless of lane confidence factor
    for(i = 0; i < pSpatMapIn->EvLanesCount; i++)
    {
      tSPATMAPEvaluatedLane *pLane = &pSpatMapIn->aEvaluatedLanes[i];
      if(pLane->IsFound == true)
      {
        DriverAlert |= RLW_AlertRightMove(pLane);
      }
    }
  }
  else
  {
    bool IsCertain = false;
    // Search for highest confidence lanes to evaluate (any conf > 90%)
    for(i = 0; i < pSpatMapIn->EvLanesCount; i++)
    {
      tSPATMAPEvaluatedLane *pLane = &pSpatMapIn->aEvaluatedLanes[i];

      // The 90 confidence factor is arbitrary - could be made configurable
      if((pLane->IsFound == true) && (pLane->ConfidenceFactor > 90))
      {
        // At least one lane is found with a conf value > 95%, that means
        // vehicle move is certain and only this/these lane(s) will be evaluated
        IsCertain = true;

        DriverAlert |= RLW_AlertStraightMove(pLane);
        DriverAlert |= RLW_AlertRightMove(pLane);
        DriverAlert |= RLW_AlertLeftMove(pLane);
        DriverAlert |= RLW_AlertUTurnMove(pLane);
      }
    }

    // Okay, no certain lanes found. Evaluate all and alert for any RED/YLW lane
    if(IsCertain != true)
    {
      for(i = 0; i < pSpatMapIn->EvLanesCount; i++)
      {
        tSPATMAPEvaluatedLane *pLane = &pSpatMapIn->aEvaluatedLanes[i];

        if(pLane->IsFound == true)
        {
          DriverAlert |= RLW_AlertStraightMove(pLane);
          DriverAlert |= RLW_AlertRightMove(pLane);
          DriverAlert |= RLW_AlertLeftMove(pLane);
          DriverAlert |= RLW_AlertUTurnMove(pLane);
        }
      }
    }
  }
  return DriverAlert;
}


/**
 * @brief Alert based on left and soft left arrow signal group evacuation
 * @param pLane pointer to current lane to be evaluated - can't be null
 * @return bit mask presenting left active alerts, or zero if none is active
 */
static uint16_t RLW_AlertLeftMove(tSPATMAPEvaluatedLane *pLane)
{
  uint16_t DriverAlert = 0;

  if(!pLane)
    return DriverAlert;

  // Check Left Arrow
  //if(pLane->StConfLeft != StateConfidence_unKnownEstimate)
  {
    // For red state, alert if driver time to RSU is faster than time to change
    if (pLane->Left.TrfcClr == SIGCOLOR_SOLID_RED)
    {
      DriverAlert |= ALERT_LEFT_RED;
    }
    else if (pLane->Left.TrfcClr == SIGCOLOR_SOLID_YELLOW)
    {
      // For amber state, treat as red state for now
      DriverAlert |= ALERT_LEFT_YLW;
    }
  }

  return DriverAlert;
}


/**
 * @brief Alert based on right and soft right arrow signal group evacuation
 * @param pLane pointer to current lane to be evaluated - can't be null
 * @return bit mask presenting right active alerts, or zero if none is active
 */
static uint16_t RLW_AlertRightMove(tSPATMAPEvaluatedLane *pLane)
{
  uint16_t DriverAlert = 0;

  if(!pLane)
    return DriverAlert;

  // Check Right Arrow
  //if(pLane->StConfRight != StateConfidence_unKnownEstimate)
  {
    // For red state, alert if driver time to RSU is faster than time to change
    if (pLane->Right.TrfcClr == SIGCOLOR_SOLID_RED)
    {
      DriverAlert |= ALERT_RIGHT_RED;
    }
    else if (pLane->Right.TrfcClr == SIGCOLOR_SOLID_YELLOW)
    {
      // For amber state, treat as red state for now
      DriverAlert |= ALERT_RIGHT_YLW;
    }
  }

  return DriverAlert;
}


/**
 * @brief Alert based on ball and straight signal group evacuation
 * @param pLane pointer to current lane to be evaluated - can't be null
 * @return bit mask presenting straight active alerts, or zero if none is active
 */
static uint16_t RLW_AlertStraightMove(tSPATMAPEvaluatedLane *pLane)
{
  uint16_t DriverAlert = 0;

  if(!pLane)
    return DriverAlert;

  // Check Ball
  //if(pLane->StConfBall != StateConfidence_unKnownEstimate)
  {
    // For red state, alert if driver time to RSU is faster than time to change
    if (pLane->Ball.TrfcClr == SIGCOLOR_SOLID_RED)
    {
      DriverAlert |= ALERT_BALL_RED;
    }
    else if (pLane->Ball.TrfcClr == SIGCOLOR_SOLID_YELLOW)
    {
      // For amber state, treat as red state for now
      DriverAlert |= ALERT_BALL_YLW;
    }
  }

  return DriverAlert;
}


/**
 * @brief Alert based on uturn signal group evacuation
 * @param pLane pointer to current lane to be evaluated - can't be null
 * @return bit mask presenting u-turn active alerts, or zero if none is active
 */
static uint16_t RLW_AlertUTurnMove(tSPATMAPEvaluatedLane *pLane)
{
  uint16_t DriverAlert = 0;

  if(!pLane)
    return DriverAlert;

  // Check UTurn
  //if(pLane->StConfUTurn != StateConfidence_unKnownEstimate)
  {
    // For red state, alert if driver time to RSU is faster than time to change
    if (pLane->UTurn.TrfcClr == SIGCOLOR_SOLID_RED)
    {
      DriverAlert |= ALERT_UTURN_RED;
    }
    else if (pLane->UTurn.TrfcClr == SIGCOLOR_SOLID_YELLOW)
    {
      // For amber state, treat as red state for now
      DriverAlert |= ALERT_UTURN_YLW;
    }
  }
  return DriverAlert;
}


/**
 * @brief Retrieve latest RLW alert
 * @return copy of latest RLW alert
 */
static void RLW_GetAlertInfo(tRLWAlertInfo *pRLWAlertInfo)
{
  if(!pRLWAlertInfo) return;

  pthread_mutex_lock(&(RLW.Rx.AlertInfo.Mutex));

  // Copy latest info data to caller
  memcpy(pRLWAlertInfo, &(RLW.Rx.AlertInfo), sizeof(tRLWAlertInfo));

  pthread_mutex_unlock(&(RLW.Rx.AlertInfo.Mutex));
}


/**
 * @brief Print output of FineGrain evaluation to standard output, for debugging
 * @param pSpatMapIn FineGrain output intersection - most relevant approach
 */
static void RLW_PrintApproachOutput(tSPATMAPIntersection *pSpatMapIn)
{
  int i;
  static const char *aSigColors[4] = {"OFF","GRN","YLW","RED"};

  d_printf(D_TST, NULL, ">> InId %d AppId %d Lanes %d Dist %.2f Angle %.2f Conf %d LfTurn %d RtTurn %d\n",
      pSpatMapIn->IntersectionId,
      pSpatMapIn->ApproachId,
      pSpatMapIn->EvLanesCount,
      pSpatMapIn->DistanceToReferencePoint_m,
      pSpatMapIn->Angle_deg,
      pSpatMapIn->ConfidenceFactor,
      pSpatMapIn->IsLeftTurnSig,
      pSpatMapIn->IsRightTurnSig);

  for(i = 0; i < pSpatMapIn->EvLanesCount; i++)
  {
    d_printf(D_TST, NULL, ">> Lane %d: found %d dist %.2f distToStopLine %.2f angle %.2f conf %d\n",
        pSpatMapIn->aEvaluatedLanes[i].LaneId,
        pSpatMapIn->aEvaluatedLanes[i].IsFound,
        pSpatMapIn->aEvaluatedLanes[i].DistanceToLane_m,
        pSpatMapIn->aEvaluatedLanes[i].DistanceToStopLine_m,
        pSpatMapIn->aEvaluatedLanes[i].AlignmentAngle_deg,
        pSpatMapIn->aEvaluatedLanes[i].ConfidenceFactor);

    d_printf(D_TST, NULL, ">> Times: B(%u) L(%u) R(%u) U(%u)\n",
        pSpatMapIn->aEvaluatedLanes[i].Ball.TimChng_ds,
        pSpatMapIn->aEvaluatedLanes[i].Left.TimChng_ds,
        pSpatMapIn->aEvaluatedLanes[i].Right.TimChng_ds,
        pSpatMapIn->aEvaluatedLanes[i].UTurn.TimChng_ds);

    d_printf(D_TST, NULL, ">> Light: B(%s) L(%s) R(%s) U(%s)\n",
        aSigColors[pSpatMapIn->aEvaluatedLanes[i].Ball.TrfcClr],
        aSigColors[pSpatMapIn->aEvaluatedLanes[i].Left.TrfcClr],
        aSigColors[pSpatMapIn->aEvaluatedLanes[i].Right.TrfcClr],
        aSigColors[pSpatMapIn->aEvaluatedLanes[i].UTurn.TrfcClr]);
  }
}

#if defined(UNITTEST)

void UNITTEST_RLW_FindMostConfident(tSPATMAPIntersection **apRelevantIntersections,
                                    int Size,
                                    tSPATMAPIntersection **ppSpatMapIn)
{
  RLW_FindMostConfident(apRelevantIntersections, Size, ppSpatMapIn);
}


void UNITTEST_RLW_PrepareAlertInfo(const tSPATMAPIntersection *pSpatMapIn)
{
  RLW_PrepareAlertInfo(pSpatMapIn);
}

void UNITTEST_RLW_GetAlertInfo(tRLWAlertInfo *pRLWAlertInfo)
{
  RLW_GetAlertInfo(pRLWAlertInfo);
}

#endif

/**
 * @}
 */
