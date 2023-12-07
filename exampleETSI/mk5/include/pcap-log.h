/**
 * @addtogroup pcap_log_api Logging/replay API for PCAP log files
 * @{
 *
 * @section pcap_log_api_dd What Does It Do
 * PCAP logging library.
 *
 * @note Interface definition for the PCAP logging library.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PCAP_LOG_H_
#define __PCAP_LOG_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------

#if !(defined(__QNX__))
#include <linux/limits.h>
#endif
#include <sys/time.h>
#include <stdio.h>
#include <pcap.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#ifndef PCAP_ERRBUF_SIZE
#define PCAP_ERRBUF_SIZE 256
#endif

/// IDs of various PCAP logs
typedef enum
{
  PCAP_LOG_CAN = 0, ///< CAN bus
  PCAP_LOG_CAN_TX, ///< TX
  PCAP_LOG_GPS, ///< GPS
  PCAP_LOG_RX, ///< RX
  PCAP_LOG_TX, ///< TX
  PCAP_LOG_C2X_RX, ///< RX
  PCAP_LOG_C2X_TX, ///< TX
  PCAP_LOG_C2X_SIMRX, ///< RX
  PCAP_LOG_C2X_SIMTX, ///< TX
  PCAP_LOG_SAEC_RX, ///< SAE-C RX
  PCAP_LOG_SAEC_TX, ///< SAE-C TX
  PCAP_LOG_ST, ///< Stats
  PCAP_LOG_G5MON, ///< G5 monitor info
  PCAP_LOG_TA_ADR, ///< TA Application Data Recorder
  PCAP_LOG_LLC, ///< Selective LLC interface
  PCAP_LOG_RPS,   ///< RPS positioning output
  PCAP_LOG_LVW_VEHIF,        ///< VEHIF for LVW
  PCAP_LOG_LVW_POTIIF,       ///< POTIIF for LVW
  PCAP_LOG_LVW_PSDIF,        ///< PSDIF for LVW
  PCAP_LOG_LVW_POTIIF2,      ///< POTIIF2 for LVW
  PCAP_LOG_LVW_MESSAGE,      ///< C2XMessage for LVW
  PCAP_LOG_RPS_RAW_RANGING,   ///< RPS raw ranging interface output
  PCAP_LOG_RPS_PVT, ///<RPS position output service PVT message output
  PCAP_LOG_RPS_UBX_JSON, ///<RPS UBX JSON output messages
  PCAP_LOG_RPS_RAW_RANGING_CLOUD, /// Cloud mode raw-ranging output
  PCAP_LOG_RADIOTAP_TXA, ///< tx_r1a.pcap
  PCAP_LOG_RADIOTAP_RXA, ///< rx_r1a.pcap
  PCAP_LOG_RADIOTAP_TXB, ///< tx_r1c.pcap
  PCAP_LOG_RADIOTAP_RXB, ///< rx_r1c.pcap
  PCAP_LOG_RX_PC5, /// < rx_pc5.pcap (NA)
  PCAP_LOG_TX_PC5, /// < tx_pc5.pcap (NA)
  PCAP_LOG_VSTATE, ///< VSTATE pseudo-CAN
  PCAP_LOG_MAX
  /// @note Must be kept in sync with static struct PcapLog PcapLog in pcap-log.c
} ePcapLogId;
/// @copydoc ePcapLogId
typedef int tPcapLogId;


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
struct PcapMetaData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Open/close for logging
int pl_OpenLog (const tPcapLogId Id);
int pl_Close (const tPcapLogId Id);

/// FILE based access - can be used safely
FILE *pl_File(const tPcapLogId Id);

// Initialisation / deinitialisation
// These are the first and last functions to call respectively
int pl_init (void);
void pl_cleanup (void);

/// Force all open log files to flush NOW
void pl_flushNow (void);

/// Force truncate check of all open log files
void pl_TruncateCheckAll(void);

/// Write given data as PCAP frame
ssize_t pl_Write (const tPcapLogId Id,
                  const void *pData,
                  size_t Len);
ssize_t pl_Write2 (const tPcapLogId Id,
                   const void *pData,
                   size_t Len,
                   const void *pData2,
                   size_t Len2);
ssize_t pl_Write3 (const tPcapLogId Id,
                   const void *pData,
                   size_t Len,
                   const void *pData2,
                   size_t Len2,
                   const void *pData3,
                   size_t Len3);
ssize_t pl_Write4 (const tPcapLogId Id,
                   const void *pData,
                   size_t Len,
                   const void *pData2,
                   size_t Len2,
                   const void *pData3,
                   size_t Len3,
                   const void *pData4,
                   size_t Len4);

/// Write with time stamp
ssize_t pl_WriteWithTs (const tPcapLogId Id,
                        const void *pData,
                        size_t Len,
                        struct timeval *pTimeStamp);

#ifndef NO_PCAP_REPLAY
/// Open/close for replay
void * pl_OpenReplay (const char *pFileName,
                      struct timeval *pFirst,
                      struct PcapMetaData *pMetaData,
                      char pErrMsg[PCAP_ERRBUF_SIZE]);
void pl_CloseReplay (void *pReplay);

struct timeval pl_ReplayOffset (void *pReplay,
                                struct timeval *pFirstFrameTimestamp);

// Read frame, return with optional delay
ssize_t pl_Read (void *pReplay,
                 void *pData,
                 size_t Len,
                 struct timeval *pOffset);

// Read exactly or treat as error
ssize_t pl_ReadExactly (void *pReplay,
                        void *pData,
                        size_t Len,
                        struct timeval *pOffset);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PCAP_LOG_H_ */

/**
 * @}
 */
