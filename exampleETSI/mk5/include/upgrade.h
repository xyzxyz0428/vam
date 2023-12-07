#pragma once
/**
 * @addtogroup app_Upgrade
 * @{
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UPGRADE_H__
#define __UPGRADE_H__
// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "Upgrade_defn.h"
#include "qs-lib.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define QSQUEUE_UPGRADE QSQUEUE_APP5
#define QS_BASE_MSG_UPGRADE QS_BASE_MSG_APP5

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Supported messages to Upgrade thread
typedef enum
{
  /// Upgrade has not started
  UPGRADE_STATE_IDLE = 0,
  /// Upgrade has started
  UPGRADE_STATE_UPGRADING,
  /// Upgrade has succedded
  UPGRADE_STATE_SUCCESS,
  /// Upgrade has failed
  UPGRADE_STATE_FAIL,
  /// Number of states
  NUM_UPGRADE_STATE_FAIL,
} eUpgradeState;

typedef uint8_t tUpgradeState;

/// Supported messages to Upgrade thread
typedef enum
{
  /// Launch Upgrade request
  QSMSG_UPGRADE_START = QS_BASE_MSG_UPGRADE,

  /// Stop Upgrade
  QSMSG_UPGRADE_STOP,

  /// Terminate Upgrade
  QSMSG_UPGRADE_TERMINATE,
} tUpgradeMsgId;

typedef struct UpgradeParam
{
  char* serverAddress;
  char* params;
} tUpgradeParam;

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int  Upgrade_Init(const tCohda_App_Upgrade *pParam);
void Upgrade_Exit(void);

/**
 * @brief Request to start firmware upgrade
 * @return Success: 0, Error: -1
 */
int Upgrade_Start();

void Upgrade_PrintStats(FILE *pStream);

tUpgradeState Upgrade_GetState();

#ifdef __cplusplus
}
#endif

#endif // __UPGRADE_H__
/**
 * @}
 */
