#pragma once
/**
 * @addtogroup ta_api Threat Arbitrator (TA) API
 * @{
 *
 * @file
 *
 * Event Data Recorder definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "TA.h"
#include "TA_ADR_data.h"
#include "Vector.h"
#include "default_stack_defn.h"
#include "lph.h"
#include "udp.h"
#include "vstate.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Initialise parameters with defaults
// void TA_ADR_SetDefaultParams(tCohda_ADR *pParam);
// deprecated, use
//    default_stack_Cohda_ADR_Copy(pParam, NULL)
// or
//   default_stack_DEF.Cohda_ADR
// instead

/// Initialise the module
void TA_ADR_Init(const tdefault_stack_Cohda_ADR *pParam);

/// Finalise the module
void TA_ADR_Exit(void);

/// Add a record to the circular buffer
void TA_ADR_Add(void *pPtr,
                unsigned ClientID,
                const tVector *pVec,
                const tVStateState *pVState,
                const tLPHData *pLPHData,
                const tLPHPos *pLPHPos);

/// Flush the circular buffer after the next add
void TA_ADR_Flush(void);

/// Flush the circular NOW (thread unsafe?)
void TA_ADR_FlushNow(void);

/// Called by TA to build up a list of interesting RVs to snapshot
void TA_ADR_Interesting(tTA_RV *pRV,
                        tTA_RV pInterestingRVs[CW_ADR_RV_CNT],
                        const tTAAlert *pCurrentAlert);

void TA_ADR_Snapshot(const tTA_HV *pHV,
                     tTA_RV pInterestingRVs[CW_ADR_RV_CNT],
                     const tTAAlert *pCurrentAlert,
                     time_t now);

void TA_ADR_Intersections(void *pIntersections[], // tSPATMAPCNIntersection
                          int Cnt);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
