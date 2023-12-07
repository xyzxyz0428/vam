/**
 * @addtogroup app_rlw Red Light Warning app plugin
 * @{
 *
 *
 * @file RLW-rx.h Module code for red light warning/violation
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __RLW_RX_H_
#define __RLW_RX_H_


//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include "spat-rx.h"
#include "TA.h"

#include <stdint.h>
#include <stdbool.h>

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// RLW uses this intersection ID to indicate _no_ intersection (blank)
#define RLW_INTERSECTION_ID_NONE (-1)

/// RLW disregards activity related to SPATs which are older than this time
#define RLW_MAX_SPAT_AGE_ms (300000)

#define ALERT_LEFT_RED          0x0001
#define ALERT_LEFT_YLW          0x0002
#define ALERT_SLEFT_RED         0x0004
#define ALERT_SLEFT_YLW         0x0008
#define ALERT_RIGHT_RED         0x0010
#define ALERT_RIGHT_YLW         0x0020
#define ALERT_SRIGHT_RED        0x0040
#define ALERT_SRIGHT_YLW        0x0080
#define ALERT_BALL_RED          0x0100
#define ALERT_BALL_YLW          0x0200
#define ALERT_STRAIGHT_RED      0x0400
#define ALERT_STRAIGHT_YLW      0x0800
#define ALERT_UTURN_RED         0x1000
#define ALERT_UTURN_YLW         0x2000

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

/// RLW internal alert information
typedef struct RLWAlertInfo
{
  // Mutex to protect alert info
  pthread_mutex_t Mutex;
  /// No intersection information availble
  bool     NoInfo;
  /// SPAT's receive timestamp
  uint64_t RxTime;
  /// Fill out .GLOSA
  tTAAlert TAAlert;
} tRLWAlertInfo;

/// RLW receive specific state information
typedef struct RLWRx
{
  /// Status
  bool Active;
  // Parameters in pre-converted units
  struct
  {
    float ALERT_DISTANCE_MAX_mm;
  } Fast;
  /// SPAT/MAP API handles
  struct
  {
    tSPATMAP *pModule;
    int Handle;
  } SPATMAP;
  /// Alert information
  tRLWAlertInfo  AlertInfo;
} tRLWRx;


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

int RLWRx_Init(void);
void RLWRx_Exit(void);

void RLWRx_PrintStats(FILE *pStream);
void RLWRx_MakeFastParams(void);

#if defined(UNITTEST)
void UNITTEST_RLW_FindMostConfident(tSPATMAPIntersection **apRelevantIntersections,
                                    int Size,
                                    tSPATMAPIntersection **ppSpatMapIn);
void UNITTEST_RLW_PrepareAlertInfo(const tSPATMAPIntersection *pSpatMapIn);
void UNITTEST_RLW_GetAlertInfo(tRLWAlertInfo *pRLWAlertInfo);
#endif

#endif // __RLW_RX_H_

/**
 * @}
 */
