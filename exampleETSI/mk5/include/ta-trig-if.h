/**
 * @addtogroup ta_triggering Triggering support
 * @{
 *
 * TA support for triggering
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TA_TRIG__TA_TRIG_IF_H_
#define __TA_TRIG__TA_TRIG_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "id-global.h"
#include "default_stack_defn.h"
#include "lph.h"
#include "vstate.h"

#include <sys/time.h>
#include <stdint.h>

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

/// Message/Event Id Numbers
typedef enum
{
  /// Vstate event
  TA_TRIG_VSTATE_EVENT = QS_BASE_MSG_TA_TRIG,
  /// Fast recheck
  TA_TRIG_TIMER_FAST_100MS,
  /// Slow refresh
  TA_TRIG_TIMER_SLOW_1S,
  /// Config change
  TA_TRIG_CONF,

} eTATrigId;
/// @copydoc eTATrigId
typedef uint32_t tTATrigId;


/// Triggering client acessible info
typedef struct TATrigInfo
{
  /// Latest 'safe to read' LPH data
  const tLPHData *pLPHData;
  /// Latest 'safe to read' VSTATE data
  const tVStateState *pVState;

} tTATrigInfo;


/**
 * @brief Type for TA TRIG event callback function
 * @param Id Event identifier
 * @param Now Event time (roughly 'now')
 * @param pInfo Trigger info availible to clients
 * @param pPriv Private pointer that was provided in TATrig_CallbackRegister()
 *
 */
typedef void (fTATrig_Callback) (tTATrigId Id,
                                 struct timeval Now,
                                 tTATrigInfo *pInfo,
                                 void *pPriv);


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int TATrig_CallbackRegister (fTATrig_Callback *pFunc,
                             void *pPriv);

void TATrig_CallbackDeregister (int Handle);

#ifdef __cplusplus
}
#endif

#endif //__TA_TRIG__TA_TRIG_IF_H_

// Close the Doxygen group
/**
 * @}
 */
