/**
 * @addtogroup tcpdump_log_api Logging API for packet capture via tcpdump
 * @{
 *
 * @section tcpdump_log_api_dd What Does It Do
 * TCPDUMP logging library.
 *
 * @note Interface definition for the TCPDUMP logging library.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TCPDUMP_LOG_H_
#define __TCPDUMP_LOG_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------

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

/// Various tcpdump supported 'interfaces'
typedef enum
{
  TCPDUMP_LOG_OTA_TX, ///< TX over-the-air
  TCPDUMP_LOG_R1A_RX, ///< RX
  TCPDUMP_LOG_R1A_TX, ///< TX
  TCPDUMP_LOG_R1C_RX, ///< RX
  TCPDUMP_LOG_R1C_TX, ///< TX
  TCPDUMP_LOG_SSL, ///< ASD specific 'SSL'
  TCPDUMP_LOG_GEN, ///< Configurable Generic TCP_DUMP
  TCPDUMP_LOG_MAX
/// NOTE: Must be kept in sync with TcpdumpLogIdPrefix in tcpdump-log.c
} eTcpdumpLogId;

typedef uint8_t tTcpdumpLogId;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Initialisation / deinitialisation
/// These are the first and last functions to call respectively
void TcpdumpLog_Init (void);
void TcpdumpLog_Deinit (void);

/// Call when configuration updated so we can dynamically start / stop tcpdump
/// as required
void TcpdumpLog_ConfigUpdated(void);

#ifdef __cplusplus
}
#endif

#endif /* __TCPDUMP_LOG_H_ */

/**
 * @}
 */
