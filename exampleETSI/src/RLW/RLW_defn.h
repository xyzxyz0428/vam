#pragma once
/**
 * @addtogroup conf_if_module_RLW RLW Configuration service
 * @{
 *
 * @file
 *
 * Configuration file parameters for RLW
 */
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------
#define RLW_CRC (0x70367af559ed7300ull)
#include "RLW_debug.h"

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

bool RLW_CheckCRC(uint64_t CRC);

#define RLW_Cust_App_RLW_DebugLevel_PARAM "Cust_App_RLW.DebugLevel"
#define RLW_Cust_App_RLW_DebugLevel_MIN -1
#define RLW_Cust_App_RLW_DebugLevel_DEF -1
#define RLW_Cust_App_RLW_DebugLevel_MAX 255

#define RLW_Cust_App_RLW_ENABLE_PARAM "Cust_App_RLW.ENABLE"
#define RLW_Cust_App_RLW_ENABLE_DEF false

#define RLW_Cust_App_RLW_REC_ENABLE_PARAM "Cust_App_RLW.REC_ENABLE"
#define RLW_Cust_App_RLW_REC_ENABLE_DEF false

#define RLW_Cust_App_RLW_REC_SEVERITY_MAX_PARAM "Cust_App_RLW.REC_SEVERITY_MAX"
#define RLW_Cust_App_RLW_REC_SEVERITY_MAX_MIN 0
#define RLW_Cust_App_RLW_REC_SEVERITY_MAX_DEF 205
#define RLW_Cust_App_RLW_REC_SEVERITY_MAX_MAX 255

#define RLW_Cust_App_RLW_REC_SEVERITY_MIN_PARAM "Cust_App_RLW.REC_SEVERITY_MIN"
#define RLW_Cust_App_RLW_REC_SEVERITY_MIN_MIN 0
#define RLW_Cust_App_RLW_REC_SEVERITY_MIN_DEF 181
#define RLW_Cust_App_RLW_REC_SEVERITY_MIN_MAX 255

typedef struct RLW_Cust_App_RLW
{
  /**
   * DebugLevel default is -1, min/max -1/255
   * if != -1, override debug level for RLW module only
   */
  int32_t DebugLevel;

  /**
   * REC_SEVERITY_MAX default is 205, min/max 0/255
   * RLW severity max (0:off, 1:lowest, 255:highest) @ref TASeverity
   */
  int32_t REC_SEVERITY_MAX;

  /**
   * REC_SEVERITY_MIN default is 181, min/max 0/255
   * RLW severity min (0:off, 1:lowest, 255:highest) @ref TASeverity
   */
  int32_t REC_SEVERITY_MIN;

  /**
   * ENABLE default is false
   * RLW enabled?
   */
  bool ENABLE;

  /**
   * REC_ENABLE default is false
   * RLW receive processing enabled?
   */
  bool REC_ENABLE;
} tRLW_Cust_App_RLW;

#define RLW_Cust_App_RLW_NUM_SUB (0)
#define RLW_Cust_App_RLW_NUM_FLD (5)

/// compiled-in defaults
extern const tRLW_Cust_App_RLW RLW_Cust_App_RLW_DEF;
/// Internals.... only for unit test...
const struct Conf_Callbacks * RLW_Callbacks(void);

/**
 * @brief Get a R/O copy.
 *
 * Release with @ref RLW_Release.
 *
 * @return Read-only instance of @ref RLW_Cust_App_RLW.
 */
const tRLW_Cust_App_RLW * RLW_Get(void);

/**
 * @brief Get a R/W copy.
 *
 * Discard with @ref RLW_Cust_App_RLW_Clean
 * or commit and retain with with @ref RLW_Put.
 * or commit and discard with with @ref RLW_Push.
 *
 * @return Read/Write instance of @ref RLW_Cust_App_RLW.
 */
tRLW_Cust_App_RLW * RLW_Clone(void);

/**
 * @brief Release a R/O copy.
 *
 * Discard with a copy obtained with @ref RLW_Get
 * *ppRLW_Cust_App_RLW is set to NULL to help avoid use-after-free.
 *
 * @param ppRLW_Cust_App_RLW Pointer to tRLW_Cust_App_RLW to be cleaned up a f free(3)'d
 */
void RLW_Release(const tRLW_Cust_App_RLW ** ppRLW_Cust_App_RLW);

/**
 * @brief Commit a R/O copy.
 *
 * Deep clean pRLW_Cust_App_RLW.
 * pRLW_Cust_App_RLW is not altered or free(3)'d
 *
 * @param pRLW_Cust_App_RLW Pointer to tRLW_Cust_App_RLW to update parameters with.
 */
void RLW_Put(const tRLW_Cust_App_RLW * pRLW_Cust_App_RLW);

/**
 * @brief Commit and clean up ppRLW_Cust_App_RLW.
 *
 * Applies *ppRLW_Cust_App_RLW as the new configuration.
 * *ppRLW_Cust_App_RLW is set to NULL to help avoid use-after-free.
 * Use with @ref RLW_Clone.
 *
 * @param ppRLW_Cust_App_RLW Pointer to tRLW_Cust_App_RLW to update parameters with and clean up.
 */
void RLW_Push(tRLW_Cust_App_RLW ** ppRLW_Cust_App_RLW);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void RLW_Cust_App_RLW_Dump(
  FILE * pFile,
  const tRLW_Cust_App_RLW * pDump,
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
int  RLW_Cust_App_RLW_Parse(
  const char * pKey,
  const char * pValue,
  tRLW_Cust_App_RLW * pParse,
  int Mode);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  RLW_Cust_App_RLW_Check(
  const tRLW_Cust_App_RLW * pCheck);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref RLW_Cust_App_RLW_Copy with pSrc set to NULL
 */
int  RLW_Cust_App_RLW_Init(
  tRLW_Cust_App_RLW * pInit);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void RLW_Cust_App_RLW_Clean(
  tRLW_Cust_App_RLW * pClean);

/**
 * @brief Deep copy
 *
 * Calls @ref RLW_Cust_App_RLW_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  RLW_Cust_App_RLW_Copy(
  tRLW_Cust_App_RLW * pDst,
  const tRLW_Cust_App_RLW * pSrc);

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
int  RLW_Cust_App_RLW_Comp(
  const tRLW_Cust_App_RLW * pA,
  const tRLW_Cust_App_RLW * pB);

/**
 * @brief Update "DebugLevel"s
 *
 * update main DebugLevel and friends.
 *
 * @param pRO Config to update DebugLevels with
 * @param DebugLevel Default Debug Level
 */
void RLW_Cust_App_RLW_UpdateDebug(
  const tRLW_Cust_App_RLW * pRO,
  int DebugLevel);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
