//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_UTIL_TIMEDBOOL_H_
#define __PLAT_UTIL_TIMEDBOOL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

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

typedef enum TimedBoolState
{
  TB_off,         ///< off for longer than lockout period
  TB_lockout,     ///< lockout period, re-triggering not allowed
  TB_on,          ///< on, but not for long enough yet
  TB_active,      ///< active
  TB_persist,     ///< turn-off delay
} eTimedBoolState;


typedef struct TimedBool
{
  char Dummy[4 * sizeof(struct timeval) + sizeof(uint32_t)
#if (defined(__amd64__)||defined(__aarch64__))
             + 4 // padding in 64-bit machines.
                 // pack the struct?
                 // give up on hiding the data?
#endif
             ];
} tTimedBool;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


void TimedBool_Init(struct TimedBool * pTimedBoolExt,
                    const struct timeval * pMinOn,
                    const struct timeval * pLockout,
                    const struct timeval * pPersist);

void TimedBool_Init_State(struct TimedBool * pTimedBoolExt,
                          const struct timeval * pMinOn,
                          const struct timeval * pLockout,
                          const struct timeval * pPersist,
                          const eTimedBoolState InitialState);

void TimedBool_Init_ms(struct TimedBool * pTimedBoolExt,
                       unsigned MinOn_ms,
                       unsigned Lockout_ms,
                       unsigned Persist_ms);

void TimedBool_Init_State_ms(struct TimedBool * pTimedBoolExt,
                       unsigned MinOn_ms,
                       unsigned Lockout_ms,
                       unsigned Persist_ms,
                       unsigned InitialState);

bool TimedBool_Set(struct TimedBool * pTimedBoolExt,
                   const struct timeval * pNow,
                   bool Current);

// should maybe add an optional "const struct timeval * pNow"
bool TimedBool_Get(const struct TimedBool * pTimedBoolExt);

// pNow may be NULL
bool TimedBool_Locked(struct TimedBool * pTimedBoolExt,
                      const struct timeval * pNow);

// Extract state information.
// pNextChange may be NULL
// Caller is responsible for thread safety!
eTimedBoolState TimedBool_State(const struct TimedBool * pTimedBoolExt,
                                struct timeval * pNextChange);

#ifdef __cplusplus
}
#endif

#endif // __PLAT_UTIL_TIMEDBOOL_H_
