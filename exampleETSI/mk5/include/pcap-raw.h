/**
 * @addtogroup pcap_raw_api Raw PCAP Logging API
 * @{
 *
 * @section pcapc_raw_api_dd What Does It Do
 * Raw PCAP access API
 *
 * @file
 *
 * API definition for PCAP file access module
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PCAP_RAW_H_
#define __PCAP_RAW_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdio.h>

#include "util.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Maximum packet size (not including PCAP header)
static const size_t PR_MAX_LEN = 2000;


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef struct PcapRawLog
{
} tPcapRawLog;

typedef struct PcapStats
{
  /// Capture bytes
  bool WriteCountersEnabled;
  /// Capture timing
  bool WriteMetricsEnabled;

  /// Logged writes
  uint32_t LoggedWrites;
  /// Logged bytes
  uint32_t LoggedBytes;

  /// When the short-term stats were last reset and dumped
  time_t NextShortDump;
  /// Short-term statistics
  tTimingStats Short;
  /// Long-term statistics
  tTimingStats Long;
} tPcapStats;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Open/close for logging
void * pr_OpenLog (const char *pFilename,
                   unsigned Datalink,
                   char *pWriteBuf,
                   ssize_t WriteBufLen);
int pr_Close (void *pWrite);

FILE *pr_File (void *pWrite);

// Direct file descriptor operations -- NOTE: USE WITH CARE
int pr_Fd(void *pWrite);
int pr_Flush(void *pWrite);

// Write data as a PCAP record (i.e. pre-pend header)
int pr_Write (void *pWrite,
              const void *pData,
              size_t Len,
              tPcapStats * pPcapStats);
int pr_Write2 (void *pWrite,
               const void *pData,
               size_t Len,
               const void *pData2,
               size_t Len2,
               tPcapStats * pPcapStats);
int pr_Write3 (void *pWrite,
               const void *pData,
               size_t Len,
               const void *pData2,
               size_t Len2,
               const void *pData3,
               size_t Len3,
               tPcapStats * pPcapStats);
int pr_Write4 (void *pWrite,
               const void *pData,
               size_t Len,
               const void *pData2,
               size_t Len2,
               const void *pData3,
               size_t Len3,
               const void *pData4,
               size_t Len4,
               tPcapStats * pPcapStats);

/// Write with time stamp
int pr_WriteWithTs (void *pWrite,
                    const void *pData,
                    size_t Len,
                    struct timeval *pTimeStamp,
                    tPcapStats * pPcapStats);

/// Write all of buffer or close file
int pr_WriteOrClose (void *pWrite,
                     const void *pData,
                     size_t Len);

#ifndef NO_PCAP_REPLAY
/// Open/close for replay
void * pr_OpenReplay (const char *pFileName,
                      char *pErrMsg);
void pr_CloseReplay (void *pRead);

/// Read a packet with optional delay
int pr_Read (void *pRead,
             void *pData,
             size_t *pLen,
             const struct timeval *pOffset,
             struct timeval *pTimestamp);

/// Read a packet, optionally return packet timestamp
int pr_ReadNoDelay (void *pRead,
                    void *pData,
                    size_t *pLen,
                    struct timeval *pTimestamp);

#endif
/// Write all given data to given file
int pr_WriteAllOrFail (void *pWrite,
                       const void *pData,
                       size_t Len);

#ifdef __cplusplus
}
#endif

#endif /* __PCAP_RAW_H_ */

/**
 * @}
 */
