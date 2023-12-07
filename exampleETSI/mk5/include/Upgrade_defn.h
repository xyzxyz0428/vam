#pragma once
/**
 * @addtogroup conf_if_module_Upgrade Upgrade Configuration service
 * @{
 *
 * @file
 *
 * Configuration file parameters for Upgrade
 */
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------
#define Upgrade_CRC (0x55f7fbcc5077d8a0ull)
#include "Upgrade_debug.h"

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

bool Upgrade_CheckCRC(uint64_t CRC);

#define Cohda_App_Upgrade_DebugLevel_PARAM "Cohda_App_Upgrade.DebugLevel"
#define Cohda_App_Upgrade_DebugLevel_MIN -1
#define Cohda_App_Upgrade_DebugLevel_DEF -1
#define Cohda_App_Upgrade_DebugLevel_MAX 255

#define Cohda_App_Upgrade_ENABLE_PARAM "Cohda_App_Upgrade.ENABLE"
#define Cohda_App_Upgrade_ENABLE_DEF false

#define Cohda_App_Upgrade_ACTIVE_PARAM "Cohda_App_Upgrade.ACTIVE"
#define Cohda_App_Upgrade_ACTIVE_DEF false

#define Cohda_App_Upgrade_ServerList_PARAM "Cohda_App_Upgrade.ServerList"
#define Cohda_App_Upgrade_ServerList_DEF ""

#define Cohda_App_Upgrade_Username_PARAM "Cohda_App_Upgrade.Username"
#define Cohda_App_Upgrade_Username_DEF "cohda"

#define Cohda_App_Upgrade_Password_PARAM "Cohda_App_Upgrade.Password"
#define Cohda_App_Upgrade_Password_DEF "FUjQ9XKeQUdw"

#define Cohda_App_Upgrade_SourceListFile_PARAM "Cohda_App_Upgrade.SourceListFile"
#define Cohda_App_Upgrade_SourceListFile_DEF "/etc/apt/sources.list.d/mk5.list"

#define Cohda_App_Upgrade_Packages_PARAM "Cohda_App_Upgrade.Packages"
#define Cohda_App_Upgrade_Packages_DEF "mk5-5."

#define Cohda_App_Upgrade_Pattern_PARAM "Cohda_App_Upgrade.Pattern"
#define Cohda_App_Upgrade_Pattern_DEF "mk[1-6]-[1-9].[a-z_]*"

#define Cohda_App_Upgrade_PingRequired_PARAM "Cohda_App_Upgrade.PingRequired"
#define Cohda_App_Upgrade_PingRequired_DEF true

typedef struct Cohda_App_Upgrade
{
  /**
   * ServerList default is ""
   * Space separated list of upgrade servers
   */
  const char * ServerList;

  /**
   * Username default is "cohda"
   * Username to access the https server
   */
  const char * Username;

  /**
   * Password default is "FUjQ9XKeQUdw"
   * Password to access the https server
   */
  const char * Password;

  /**
   * SourceListFile default is "/etc/apt/sources.list.d/mk5.list"
   * File where apt-get sources are added to
   */
  const char * SourceListFile;

  /**
   * Packages default is "mk5-5."
   * Upgrade packages
   */
  const char * Packages;

  /**
   * Pattern default is "mk[1-6]-[1-9].[a-z_]*"
   * Pattern used for the mk5 Package
   */
  const char * Pattern;

  /**
   * DebugLevel default is -1, min/max -1/255
   * if != -1, override debug level for Upgrade module only
   */
  int32_t DebugLevel;

  /**
   * ENABLE default is false
   * Upgrade enabled?
   */
  bool ENABLE;

  /**
   * ACTIVE default is false
   * Upgrade Active?
   */
  bool ACTIVE;

  /**
   * PingRequired default is true
   * Is a Ping required to the server?
   */
  bool PingRequired;
} tCohda_App_Upgrade;

#define Cohda_App_Upgrade_NUM_SUB (0)
#define Cohda_App_Upgrade_NUM_FLD (10)

/// compiled-in defaults
extern const tCohda_App_Upgrade Cohda_App_Upgrade_DEF;
/// Internals.... only for unit test...
const struct Conf_Callbacks * Upgrade_Callbacks(void);

/**
 * @brief Get a R/O copy.
 *
 * Release with @ref Upgrade_Release.
 *
 * @return Read-only instance of @ref Cohda_App_Upgrade.
 */
const tCohda_App_Upgrade * Upgrade_Get(void);

/**
 * @brief Get a R/W copy.
 *
 * Discard with @ref Cohda_App_Upgrade_Clean
 * or commit and retain with with @ref Upgrade_Put.
 * or commit and discard with with @ref Upgrade_Push.
 *
 * @return Read/Write instance of @ref Cohda_App_Upgrade.
 */
tCohda_App_Upgrade * Upgrade_Clone(void);

/**
 * @brief Release a R/O copy.
 *
 * Discard with a copy obtained with @ref Upgrade_Get
 * *ppCohda_App_Upgrade is set to NULL to help avoid use-after-free.
 *
 * @param ppCohda_App_Upgrade Pointer to tCohda_App_Upgrade to be cleaned up a f free(3)'d
 */
void Upgrade_Release(const tCohda_App_Upgrade ** ppCohda_App_Upgrade);

/**
 * @brief Commit a R/O copy.
 *
 * Deep clean pCohda_App_Upgrade.
 * pCohda_App_Upgrade is not altered or free(3)'d
 *
 * @param pCohda_App_Upgrade Pointer to tCohda_App_Upgrade to update parameters with.
 */
void Upgrade_Put(const tCohda_App_Upgrade * pCohda_App_Upgrade);

/**
 * @brief Commit and clean up ppCohda_App_Upgrade.
 *
 * Applies *ppCohda_App_Upgrade as the new configuration.
 * *ppCohda_App_Upgrade is set to NULL to help avoid use-after-free.
 * Use with @ref Upgrade_Clone.
 *
 * @param ppCohda_App_Upgrade Pointer to tCohda_App_Upgrade to update parameters with and clean up.
 */
void Upgrade_Push(tCohda_App_Upgrade ** ppCohda_App_Upgrade);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void Cohda_App_Upgrade_Dump(
  FILE * pFile,
  const tCohda_App_Upgrade * pDump,
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
int  Cohda_App_Upgrade_Parse(
  const char * pKey,
  const char * pValue,
  tCohda_App_Upgrade * pParse,
  int Mode);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  Cohda_App_Upgrade_Check(
  const tCohda_App_Upgrade * pCheck);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref Cohda_App_Upgrade_Copy with pSrc set to NULL
 */
int  Cohda_App_Upgrade_Init(
  tCohda_App_Upgrade * pInit);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void Cohda_App_Upgrade_Clean(
  tCohda_App_Upgrade * pClean);

/**
 * @brief Deep copy
 *
 * Calls @ref Cohda_App_Upgrade_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  Cohda_App_Upgrade_Copy(
  tCohda_App_Upgrade * pDst,
  const tCohda_App_Upgrade * pSrc);

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
int  Cohda_App_Upgrade_Comp(
  const tCohda_App_Upgrade * pA,
  const tCohda_App_Upgrade * pB);

/**
 * @brief Update "DebugLevel"s
 *
 * update main DebugLevel and friends.
 *
 * @param pRO Config to update DebugLevels with
 * @param DebugLevel Default Debug Level
 */
void Cohda_App_Upgrade_UpdateDebug(
  const tCohda_App_Upgrade * pRO,
  int DebugLevel);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
