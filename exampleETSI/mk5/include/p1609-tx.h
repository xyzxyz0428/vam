/**
 * @addtogroup v2x_p1609_tx_api IEEE 1609.3 Transmit API
 * @{
 *
 * @section v2v_p1609_tx_api_wdid What Does It Do
 * Provides 1609 WSM tx and periodic BSM tx
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_TX_IF_H_
#define __P1609_TX_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "lph.h"

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

/// Callback to return security self verification result
typedef void (fP1609_SecSelfCallback)(int Result);

/// Message structure to do security self verification
typedef struct P1609_SecSelfMsg
{
  uint32_t PSID;
  size_t Len;
  void *pData;
} tP1609_SecSelfMsg;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int P1609TX_ThreadInit(int SchedulerPolicy, int SchedulerPriority);

void P1609TX_ThreadDeinit(void);

int P1609TXReplay_ThreadInit(int SchedulerPolicy, int SchedulerPriority);

void P1609TXReplay_ThreadDeinit(void);

uint32_t P1609TX_GetTempID(void);

uint32_t P1609TX_GetNumTxWSM(void);

void P1609TX_UpdateIdentifiers(void);

void P1609TX_ChangeCertNow(void);

void P1609_SetSecSelfCallback(fP1609_SecSelfCallback *pCallback);

int P1609TX_RequestTx(const struct timespec * pNextTxTime);

int P1609TX_SetMaxITT(unsigned int MaxITT);

int P1609TX_SetTxPower(int TxPower);

int P1609TX_GetTxPower();

int P1609TX_GetLastTx(struct timespec * pTransmittedAt,
                      tLPHPos * pLPHPos,
                      struct timespec * pScheduled);

#ifdef __cplusplus
}
#endif

#endif // __P1609_TX_IF_H_

// Close the doxygen group
/**
 * @}
 */
