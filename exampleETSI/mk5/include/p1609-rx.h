/**
 * @addtogroup v2x_p1609_rx_api IEEE 1609.3 Reception API
 * @{
 *
 * @section v2v_p1609_rx_api_wdid What Does It Do
 * Provides access to WSM reception (forwarded via EXT module)
 *
 * @file p1609-rx.h Interface message id definitions
 *
 * Define supported messages
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_RX_IF_H_
#define __P1609_RX_IF_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int P1609RX_ThreadInit(int SchedulerPolicy, int SchedulerPriority);

void P1609RX_ThreadDeinit(void);

void P1609RX_UpdateTempID (uint32_t TempId);

void P1609RX_UpdateMAC (uint8_t *pMAC);

void P1609RX_CheckAndUpdateTempID (uint32_t TempIdPeer);

uint32_t P1609RX_GetNumRxWSM(void);

#ifdef __cplusplus
}
#endif

#endif // __P1609_RX_IF_H_

// Close the doxygen group
/**
 * @}
 */
