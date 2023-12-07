#pragma once
/**
 * @addtogroup plat_state Platofrm State
 * @{
 *
 * Maintains platofrm state (distinct from vehicle state)
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_STATE_STATE_H_
#define __PLAT_STATE_STATE_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

typedef enum StateFlags
{
  // The 8 least-signifficant bits are intended for ADR @ref tADRHV
  STATE_ADR_EEBL      = (UINT32_C(1) <<  0), ///< Emergency Electronic Brake Light
  STATE_ADR_HLW       = (UINT32_C(1) <<  1), ///< Hazard Location Warning
  STATE_ADR_SVA       = (UINT32_C(1) <<  2), ///< Slow/Stationary Vehicle Alert
  STATE_ADR_POSTCRASH = (UINT32_C(1) <<  3), ///< Post-crash (i.e. airbag deployed & stopped ??)
  STATE_ADR_BREAKDOWN = (UINT32_C(1) <<  4), ///< breakdown (i.e. hazard lights & stopped ??)
  STATE_ADR_DEOQ      = (UINT32_C(1) <<  5), ///< Dangerous End of Queue (i.e. Traffic-Jam ahead)
  STATE_TRIGGER_RES6  = (UINT32_C(1) <<  6),
  STATE_TRIGGER_RES7  = (UINT32_C(1) <<  7),
  // the next 8 bits are intended for system state
  STATE_RESERVED0     = (UINT32_C(1) <<  8),
  STATE_RESERVED1     = (UINT32_C(1) <<  9),
  STATE_RESERVED2     = (UINT32_C(1) << 10),
  STATE_RESERVED3     = (UINT32_C(1) << 11),
  STATE_RESERVED4     = (UINT32_C(1) << 12),
  STATE_RESERVED5     = (UINT32_C(1) << 13),
  STATE_RADIO_ERR_0   = (UINT32_C(1) << 14),
  STATE_RADIO_ERR_1   = (UINT32_C(1) << 15),
  // the last 16 bits are allocated to user applications
  STATE_USER0         = (UINT32_C(1) << 16),
  STATE_USER1         = (UINT32_C(1) << 17),
  STATE_USER2         = (UINT32_C(1) << 18),
  STATE_USER3         = (UINT32_C(1) << 19),
  STATE_USER4         = (UINT32_C(1) << 20),
  STATE_USER5         = (UINT32_C(1) << 21),
  STATE_USER6         = (UINT32_C(1) << 22),
  STATE_USER7         = (UINT32_C(1) << 23),
  STATE_USER8         = (UINT32_C(1) << 24),
  STATE_USER9         = (UINT32_C(1) << 25),
  STATE_USER10        = (UINT32_C(1) << 26),
  STATE_USER11        = (UINT32_C(1) << 27),
  STATE_USER12        = (UINT32_C(1) << 28),
  STATE_USER13        = (UINT32_C(1) << 29),
  STATE_USER14        = (UINT32_C(1) << 30),
  STATE_USER15        = (UINT32_C(1) << 31),
} eStateFlags;

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Unsigned integer type for storing state bits
typedef uint32_t tState;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// Atomically set the bits given in mask.
void State_Set(tState Mask);
// Atomically clear the bits given in mask.
void State_Clear(tState Mask);
// Atomically set or clear the bits given in mask.
void State_Update(tState Mask, bool Set);
// Atomically return the current state
tState State_Get(void);

#ifdef __cplusplus
}
#endif

#endif // __PLAT_STATE_STATE_H_

// Close the doxygen group
/**
 * @}
 */
