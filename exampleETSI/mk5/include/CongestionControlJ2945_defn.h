#pragma once
/**
 * @addtogroup conf_if_module_CongestionControlJ2945 CongestionControlJ2945 Configuration service
 * @{
 *
 * @file
 *
 * Configuration file parameters for CongestionControlJ2945
 */
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------
#define CongestionControlJ2945_CRC (0x6f14ed5cb954f2c6ull)
#include "CongestionControlJ2945_debug.h"

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

bool CongestionControlJ2945_CheckCRC(uint64_t CRC);

#define Cohda_App_CongestionControlJ2945_DebugLevel_PARAM "Cohda_App_CongestionControlJ2945.DebugLevel"
#define Cohda_App_CongestionControlJ2945_DebugLevel_MIN -1
#define Cohda_App_CongestionControlJ2945_DebugLevel_DEF -1
#define Cohda_App_CongestionControlJ2945_DebugLevel_MAX 255

#define Cohda_App_CongestionControlJ2945_ENABLE_PARAM "Cohda_App_CongestionControlJ2945.ENABLE"
#define Cohda_App_CongestionControlJ2945_ENABLE_DEF false

typedef struct Cohda_App_CongestionControlJ2945
{
  /**
   * DebugLevel default is -1, min/max -1/255
   *## Congestion Control J2945 tuneable parameters
   * if != -1, override debug level for CongestionControlJ2945 module only
   */
  int32_t DebugLevel;

  /**
   * ENABLE default is false
   * CongestionControlJ2945 enabled?
   */
  bool ENABLE;
} tCohda_App_CongestionControlJ2945;

#define Cohda_App_CongestionControlJ2945_NUM_SUB (0)
#define Cohda_App_CongestionControlJ2945_NUM_FLD (2)

/// compiled-in defaults
extern const tCohda_App_CongestionControlJ2945 Cohda_App_CongestionControlJ2945_DEF;
/// Internals.... only for unit test...
const struct Conf_Callbacks * CongestionControlJ2945_Callbacks(void);

/**
 * @brief Get a R/O copy.
 *
 * Release with @ref CongestionControlJ2945_Release.
 *
 * @return Read-only instance of @ref Cohda_App_CongestionControlJ2945.
 */
const tCohda_App_CongestionControlJ2945 * CongestionControlJ2945_Get(void);

/**
 * @brief Get a R/W copy.
 *
 * Discard with @ref Cohda_App_CongestionControlJ2945_Clean
 * or commit and retain with with @ref CongestionControlJ2945_Put.
 * or commit and discard with with @ref CongestionControlJ2945_Push.
 *
 * @return Read/Write instance of @ref Cohda_App_CongestionControlJ2945.
 */
tCohda_App_CongestionControlJ2945 * CongestionControlJ2945_Clone(void);

/**
 * @brief Release a R/O copy.
 *
 * Discard with a copy obtained with @ref CongestionControlJ2945_Get
 * *ppCohda_App_CongestionControlJ2945 is set to NULL to help avoid use-after-free.
 *
 * @param ppCohda_App_CongestionControlJ2945 Pointer to tCohda_App_CongestionControlJ2945 to be cleaned up a f free(3)'d
 */
void CongestionControlJ2945_Release(const tCohda_App_CongestionControlJ2945 ** ppCohda_App_CongestionControlJ2945);

/**
 * @brief Commit a R/O copy.
 *
 * Deep clean pCohda_App_CongestionControlJ2945.
 * pCohda_App_CongestionControlJ2945 is not altered or free(3)'d
 *
 * @param pCohda_App_CongestionControlJ2945 Pointer to tCohda_App_CongestionControlJ2945 to update parameters with.
 */
void CongestionControlJ2945_Put(const tCohda_App_CongestionControlJ2945 * pCohda_App_CongestionControlJ2945);

/**
 * @brief Commit and clean up ppCohda_App_CongestionControlJ2945.
 *
 * Applies *ppCohda_App_CongestionControlJ2945 as the new configuration.
 * *ppCohda_App_CongestionControlJ2945 is set to NULL to help avoid use-after-free.
 * Use with @ref CongestionControlJ2945_Clone.
 *
 * @param ppCohda_App_CongestionControlJ2945 Pointer to tCohda_App_CongestionControlJ2945 to update parameters with and clean up.
 */
void CongestionControlJ2945_Push(tCohda_App_CongestionControlJ2945 ** ppCohda_App_CongestionControlJ2945);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void Cohda_App_CongestionControlJ2945_Dump(
  FILE * pFile,
  const tCohda_App_CongestionControlJ2945 * pDump,
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
int  Cohda_App_CongestionControlJ2945_Parse(
  const char * pKey,
  const char * pValue,
  tCohda_App_CongestionControlJ2945 * pParse,
  int Mode);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  Cohda_App_CongestionControlJ2945_Check(
  const tCohda_App_CongestionControlJ2945 * pCheck);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref Cohda_App_CongestionControlJ2945_Copy with pSrc set to NULL
 */
int  Cohda_App_CongestionControlJ2945_Init(
  tCohda_App_CongestionControlJ2945 * pInit);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void Cohda_App_CongestionControlJ2945_Clean(
  tCohda_App_CongestionControlJ2945 * pClean);

/**
 * @brief Deep copy
 *
 * Calls @ref Cohda_App_CongestionControlJ2945_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  Cohda_App_CongestionControlJ2945_Copy(
  tCohda_App_CongestionControlJ2945 * pDst,
  const tCohda_App_CongestionControlJ2945 * pSrc);

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
int  Cohda_App_CongestionControlJ2945_Comp(
  const tCohda_App_CongestionControlJ2945 * pA,
  const tCohda_App_CongestionControlJ2945 * pB);

/**
 * @brief Update "DebugLevel"s
 *
 * update main DebugLevel and friends.
 *
 * @param pRO Config to update DebugLevels with
 * @param DebugLevel Default Debug Level
 */
void Cohda_App_CongestionControlJ2945_UpdateDebug(
  const tCohda_App_CongestionControlJ2945 * pRO,
  int DebugLevel);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
