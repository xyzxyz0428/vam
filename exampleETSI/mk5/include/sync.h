#pragma once
/**
 * @addtogroup app_sync File sync (up/download) functionality
 * @{
 *
 * @file sync.h client API
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SYNC_H__
#define __SYNC_H__

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "id-global.h"
#include "qs-lib.h"
#include "Sync_defn.h"

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define QSQUEUE_SYNC QSQUEUE_APP2
#define QS_BASE_MSG_SYNC QS_BASE_MSG_APP2

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Supported messages to Sync thread
typedef enum
{
  /// Sync start
  QSMSG_SYNC_START = QS_BASE_MSG_SYNC,
  /// Sync stop
  QSMSG_SYNC_STOP,
} tSyncMsgId;

typedef enum
{
  // 0
  /// No current action
  SYNC_STATUS_NONE,
  /// Sync is in currently downloading
  SYNC_STATUS_DOWNLOADING,
  /// Sync is updating external software
  SYNC_STATUS_EXT_UPDATE,
  /// Sync is uploading to the server
  SYNC_STATUS_UPLODADING,
  /// Sync was successful
  SYNC_STATUS_SUCCESSFUL,
  /// Log Offload was successful
  SYNC_STATUS_LOG_SUCCESSFUL,

} tSyncStatus;


typedef enum
{

  SYNC_ERR_NONE,
  SYNC_ERR_CALLBACK,

} tSyncErrCode;

typedef void (fSync_StatusCallback)(const tSyncStatus Status);

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

extern int SyncDebugLevelLocal;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/**
 * @brief Start sync
 *
 * Start the sync update thread
 *
 * @param pServerAddress URL of the sync server. NULL if the default URL Cohda_App_Sync.ServerAddress should be used.
 */
void Sync_Start(const char *pServerAddress);

tSyncStatus Sync_GetUpdateStatus(void);
tSyncStatus Sync_GetLogStatus(void);

tSyncErrCode Sync_RegisterApplication(fSync_StatusCallback *pFunc,
                                      void *pPriv);

int Sync_Init(const tCohda_App_Sync *pParam);

void Sync_Exit(void);

#ifdef __cplusplus
}
#endif

#endif // __SYNC_H__

/**
 * @}
 */
