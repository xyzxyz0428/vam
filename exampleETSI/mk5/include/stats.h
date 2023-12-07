/**
 * @addtogroup thr_stats Statistics Thread
 * @{
 *
 * Define supported messages
 *
 * @file
 *
 * Interface message id definitions
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __STATS_IF_H_
#define __STATS_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#ifndef NO_SYSINFO
#include <sys/sysinfo.h>
#endif

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

typedef enum Stats_StackTxResult
{
  /// Transmitted OK
  STACK_TX_OK = 0,
  /// Transmission inhibited by configuration option
  STACK_TX_CONF,
  /// Transmission inhibited by lack of GPS position
  STACK_TX_POS,
  /// Transmission inhibited by mismatch between GPS and system time
  STACK_TX_TIME,
  /// Transmission inhibited due to insuficcient GPS fix quality
  STACK_TX_GPS,
  /// Unable to obtain vehicle state
  STACK_TX_VSTATE,
  /// Unable to crate packet (BSM, CAN, DENM etc.) to transmit
  STACK_TX_CREATE,
  /// Unable to sign packet to transmit
  STACK_TX_SIGN,
  /// Unable to send packet to transmit
  STACK_TX_SEND,
  /// Network interface is down
  STACK_TX_HW,
  /// Transmission inhibited by geo-fencing
  STACK_TX_GEOFENCE,
  /// Transmission failed due to some other reason
  STACK_TX_OTHER,

  // number of counters required
  STACK_TX_MAX,
} tStats_StackTxResult;

typedef enum Stats_StackRxResult
{
  /// Received OK
  STACK_RX_OK = 0,
  /// Reception inhibited by configuration option
  STACK_RX_CONF,
  /// Received packet failed verification check
  STACK_RX_VRFY,
  /// Reception failed due to some other reason
  STACK_RX_OTHER,
  // number of counters required
  STACK_RX_MAX,
} tStats_StackRxResult;

typedef enum Stats_StackCryptoResult
{
  /// Crypto OK
  STACK_CRYPTO_OK = 0,
  /// No pseudonym certificates
  STACK_CRYPTO_NO_CERTIFICATES,
  /// No CA certificates
  STACK_CRYPTO_NO_CA_CERTIFICATES,
  /// id change is ongoing
  STACK_CRYPTO_ID_CHANGE_ONGOING,
  /// Not initialised
  STACK_CRYPTO_NOT_INITIALIZED,
  /// Signing hardware failure
  STACK_CRYPTO_HARDWARE_FAILED,
  /// signing failure other than no certificates and hw failure
  STACK_CRYPTO_SIGNING_FAILED,
  /// Verification failure
  STACK_CRYPTO_VERIFICATION_FAILED,
  /// Other crypto failures
  STACK_CRYPTO_OTHER,
  /// number of counters required
  STACK_CRYPTO_MAX,
} tStats_StackCryptoResult;

typedef struct Stats_StackStats
{
  tStats_StackTxResult LastTxResult;
  tStats_StackRxResult LastRxResult;
  tStats_StackCryptoResult LastTxCryptoResult;
  tStats_StackCryptoResult LastRxCryptoResult;
  unsigned TxCounters[STACK_TX_MAX];
  unsigned RxCounters[STACK_RX_MAX];
  unsigned TxCryptoCounters[STACK_CRYPTO_MAX];
  unsigned RxCryptoCounters[STACK_CRYPTO_MAX];
} tStats_StackStats;

/// Statistics logging data
typedef struct StatsLog
{
  /// CPU Utilization (0..100, 255 for invalid/unknown)
  uint8_t CPUUtilization;
  /// Control Channel Busy ratio (0..100, 255 for invalid/unknown)
  uint8_t CCHBusyRatio;
  /// Service Channel Busy ratio (0..100, 255 for invalid/unknown)
  uint8_t SCHBusyRatio;
  /// "Raw" (averaged) Channel Busy ratio (0..100)
  uint8_t RawBusyRatio;

  /// stack statistics
  tStats_StackStats StackStats;

#ifndef NO_SYSINFO
  /// RAM usage etc. Not part of the spec, but might be interesting...
  struct sysinfo SystemInfo;
#endif
} tStatsLog;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Callback to notify change of state
typedef void (fStats_StackModeChange)(const tStats_StackStats * pStats,
                                      void * pParam);

/// Update the TX status (increment counter, invoke callback on delta)
void Stats_Report_TX(tStats_StackTxResult TxResult);

/// Update the RX status (increment counter, invoke callback on delta)
void Stats_Report_RX(tStats_StackRxResult RxResult);

/// Update the TX crypto status (increment counter, invoke callback on delta)
void Stats_Report_TXCrypto(tStats_StackCryptoResult CryptoResult);

/// Update the RX crypto counter only
void Stats_Update_RXCryptoCounterOnly(tStats_StackCryptoResult CryptoResult);

/// Update the RX crypto status (increment counter, invoke callback on delta)
void Stats_Report_RXCrypto(tStats_StackCryptoResult CryptoResult);


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int Stats_ThreadInit(int schedulerPolicy, int schedulerPriority_pc);

void Stats_ThreadDeinit(void);

void Stats_SetCallback(fStats_StackModeChange *pCallback_,
                       void *pCallbackParam_);

const tStats_StackStats *Stats_GetStackStats(void);

#ifdef __cplusplus
}
#endif

#endif // __STATS_IF_H_

/**
 * @}
 */
