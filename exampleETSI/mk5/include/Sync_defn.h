#pragma once
/**
 * @addtogroup conf_if_module_Sync Sync Configuration service
 * @{
 *
 * @file
 *
 * Configuration file parameters for Sync
 */
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------
#define Sync_CRC (0x2af91c1aa3ade081ull)
#include "Sync_debug.h"

#include "conf_if.h"
#include "conf_common.h"

#include "conf_common.h" // for blobs

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
extern "C"
{
#endif

bool Sync_CheckCRC(uint64_t CRC);

#define Cohda_App_Sync_DebugLevel_PARAM "Cohda_App_Sync.DebugLevel"
#define Cohda_App_Sync_DebugLevel_MIN -1
#define Cohda_App_Sync_DebugLevel_DEF -1
#define Cohda_App_Sync_DebugLevel_MAX 255

#define Cohda_App_Sync_Enable_PARAM "Cohda_App_Sync.Enable"
#define Cohda_App_Sync_Enable_DEF false

#define Cohda_App_Sync_PSID_PARAM "Cohda_App_Sync.PSID"
#define Cohda_App_Sync_PSID_MIN 0x0ul
#define Cohda_App_Sync_PSID_DEF 0xbffaul
#define Cohda_App_Sync_PSID_MAX 0xeffffffful

#define Cohda_App_Sync_Period_m_PARAM "Cohda_App_Sync.Period_m"
#define Cohda_App_Sync_Period_m_MIN 0
#define Cohda_App_Sync_Period_m_DEF 0
#define Cohda_App_Sync_Period_m_MAX 65535

#define Cohda_App_Sync_RSyncWrapper_PARAM "Cohda_App_Sync.RSyncWrapper"
#define Cohda_App_Sync_RSyncWrapper_DEF ""

#define Cohda_App_Sync_RSyncOptions_PARAM "Cohda_App_Sync.RSyncOptions"
#define Cohda_App_Sync_RSyncOptions_DEF ""

#define Cohda_App_Sync_ServerAddress_PARAM "Cohda_App_Sync.ServerAddress"
#define Cohda_App_Sync_ServerAddress_DEF ""

#define Cohda_App_Sync_UploadSrcPath_PARAM "Cohda_App_Sync.UploadSrcPath"
#define Cohda_App_Sync_UploadSrcPath_DEF ""

#define Cohda_App_Sync_UploadDstPath_PARAM "Cohda_App_Sync.UploadDstPath"
#define Cohda_App_Sync_UploadDstPath_DEF "/mnt/ubi/log/obu"

#define Cohda_App_Sync_DownloadSrcPath_PARAM "Cohda_App_Sync.DownloadSrcPath"
#define Cohda_App_Sync_DownloadSrcPath_DEF ""

#define Cohda_App_Sync_DownloadDstPath_PARAM "Cohda_App_Sync.DownloadDstPath"
#define Cohda_App_Sync_DownloadDstPath_DEF ""

#define Cohda_App_Sync_ExternalDevice_PARAM "Cohda_App_Sync.ExternalDevice"
#define Cohda_App_Sync_ExternalDevice_DEF false

#define Cohda_App_Sync_ExtUpSrcPath_PARAM "Cohda_App_Sync.ExtUpSrcPath"
#define Cohda_App_Sync_ExtUpSrcPath_DEF ""

#define Cohda_App_Sync_ExtUpDstPath_PARAM "Cohda_App_Sync.ExtUpDstPath"
#define Cohda_App_Sync_ExtUpDstPath_DEF ""

#define Cohda_App_Sync_ExtWrapper_PARAM "Cohda_App_Sync.ExtWrapper"
#define Cohda_App_Sync_ExtWrapper_DEF ""

#define Cohda_App_Sync_ExtOptions_PARAM "Cohda_App_Sync.ExtOptions"
#define Cohda_App_Sync_ExtOptions_DEF ""

#define Cohda_App_Sync_ExtUsername_PARAM "Cohda_App_Sync.ExtUsername"
#define Cohda_App_Sync_ExtUsername_DEF ""

typedef struct Cohda_App_Sync
{
  /**
   * RSyncWrapper default is ""
   * Wrapper program for rsync - ie. could use
   * sshpass -p ssh-password
   * to authenticate with password to remote host
   */
  const char * RSyncWrapper;

  /**
   * RSyncOptions default is ""
   * Extra options to pass to rsync - ie. could use
   * -e 'ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -l ssh-username'
   * to avoid errors on ssh with unknown destination host
   */
  const char * RSyncOptions;

  /**
   * ServerAddress default is ""
   * If unset will sync with the RSU, otherwise must be set to a hostname / IP address
   */
  const char * ServerAddress;

  /**
   * UploadSrcPath default is ""
   * Local path to sync from. If unset it uses the value in 'Cohda_LogDirectoryName'
   */
  const char * UploadSrcPath;

  /**
   * UploadDstPath default is "/mnt/ubi/log/obu"
   * 'Server' path to sync to
   */
  const char * UploadDstPath;

  /**
   * DownloadSrcPath default is ""
   * 'Server' path to sync from (e.g. /mnt/ubi/sync/obu)
   */
  const char * DownloadSrcPath;

  /**
   * DownloadDstPath default is ""
   * Local path to sync to (e.g. /mnt/ubi/sync)
   */
  const char * DownloadDstPath;

  /**
   * ExtUpSrcPath default is ""
   * Local path to sync from when syncinc to external device.
   */
  const char * ExtUpSrcPath;

  /**
   * ExtUpDstPath default is ""
   * Remote path to sync to (e.g. C:\\Users\\Public\\Documents\\WireframeDisplay)
   * Paths in windows need a '\\' to escape the '\' character in the pathing
   */
  const char * ExtUpDstPath;

  /**
   * ExtWrapper default is ""
   * Ext device may not have rsync and therefore needs a separate wrapper
   */
  const char * ExtWrapper;

  /**
   * ExtOptions default is ""
   * Ext device may not have rsync and therefore needs separate options
   */
  const char * ExtOptions;

  /**
   * ExtUsername default is ""
   * Username required for scp
   */
  const char * ExtUsername;

  /**
   * DebugLevel default is -1, min/max -1/255
   * if != -1, override debug level for Sync module only
   */
  int32_t DebugLevel;

  /**
   * PSID default is 0xbffaul, min/max 0x0ul/0xeffffffful
   * PSID to trigger syncing
   * Set to 0xff to trigger on ANY PSID
   */
  uint32_t PSID;

  /**
   * Period_m default is 0, min/max 0/65535
   * Periodically try and sync every N minutes - 0 to disable
   */
  int32_t Period_m;

  /**
   * Enable default is false
   * Sync enabled?
   */
  bool Enable;

  /**
   * ExternalDevice default is false
   * Enable to sync to an external device
   */
  bool ExternalDevice;
} tCohda_App_Sync;

#define Cohda_App_Sync_NUM_SUB (0)
#define Cohda_App_Sync_NUM_FLD (17)

/// compiled-in defaults
extern const tCohda_App_Sync Cohda_App_Sync_DEF;
/// Internals.... only for unit test...
const struct Conf_Callbacks * Sync_Callbacks(void);

/**
 * @brief Get a R/O copy.
 *
 * Release with @ref Sync_Release.
 *
 * @return Read-only instance of @ref Cohda_App_Sync.
 */
const tCohda_App_Sync * Sync_Get(void);

/**
 * @brief Get a R/W copy.
 *
 * Discard with @ref Cohda_App_Sync_Clean
 * or commit and retain with with @ref Sync_Put.
 * or commit and discard with with @ref Sync_Push.
 *
 * @return Read/Write instance of @ref Cohda_App_Sync.
 */
tCohda_App_Sync * Sync_Clone(void);

/**
 * @brief Release a R/O copy.
 *
 * Discard with a copy obtained with @ref Sync_Get
 * *ppCohda_App_Sync is set to NULL to help avoid use-after-free.
 *
 * @param ppCohda_App_Sync Pointer to tCohda_App_Sync to be cleaned up a f free(3)'d
 */
void Sync_Release(const tCohda_App_Sync ** ppCohda_App_Sync);

/**
 * @brief Commit a R/O copy.
 *
 * Deep clean pCohda_App_Sync.
 * pCohda_App_Sync is not altered or free(3)'d
 *
 * @param pCohda_App_Sync Pointer to tCohda_App_Sync to update parameters with.
 */
void Sync_Put(const tCohda_App_Sync * pCohda_App_Sync);

/**
 * @brief Commit and clean up ppCohda_App_Sync.
 *
 * Applies *ppCohda_App_Sync as the new configuration.
 * *ppCohda_App_Sync is set to NULL to help avoid use-after-free.
 * Use with @ref Sync_Clone.
 *
 * @param ppCohda_App_Sync Pointer to tCohda_App_Sync to update parameters with and clean up.
 */
void Sync_Push(tCohda_App_Sync ** ppCohda_App_Sync);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void Cohda_App_Sync_Dump(
  FILE * pFile,
  const tCohda_App_Sync * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Parse the given key/value
 *
 * @param pKey Key to assign it to
 * @param pValue Value to parse
 * @param pParse where to store it
 * @param Mode Deprecated?
 *
 * @return 0 if parsed without error
 */
int  Cohda_App_Sync_Parse(
  const char * pKey,
  const char * pValue,
  tCohda_App_Sync * pParse,
  int Mode);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  Cohda_App_Sync_Check(
  const tCohda_App_Sync * pCheck);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref Cohda_App_Sync_Copy with pSrc set to NULL
 */
int  Cohda_App_Sync_Init(
  tCohda_App_Sync * pInit);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void Cohda_App_Sync_Clean(
  tCohda_App_Sync * pClean);

/**
 * @brief Deep copy
 *
 * Calls @ref Cohda_App_Sync_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  Cohda_App_Sync_Copy(
  tCohda_App_Sync * pDst,
  const tCohda_App_Sync * pSrc);

/**
 * @brief Deep Compare
 *
 * Note that floating point comparisons are used.
 *
 * @param pA one
 * @param pB the other one
 *
 * @return 0 iff *pA is identical to *pB
 */
int  Cohda_App_Sync_Comp(
  const tCohda_App_Sync * pA,
  const tCohda_App_Sync * pB);

/**
 * @brief Update "DebugLevel"s
 *
 * update main DebugLevel and friends.
 *
 * @param pRO Config to update DebugLevels with
 * @param DebugLevel Default Debug Level
 */
void Cohda_App_Sync_UpdateDebug(
  const tCohda_App_Sync * pRO,
  int DebugLevel);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
