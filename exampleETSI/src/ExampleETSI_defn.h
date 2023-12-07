#pragma once
/**
 * @addtogroup conf_if_module_ExampleETSI ExampleETSI Configuration service
 * @{
 *
 * @file
 *
 * Configuration file parameters for ExampleETSI
 */
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------
#define ExampleETSI_CRC (0xa172731c9187c61eull)
#include "ExampleETSI_debug.h"

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

bool ExampleETSI_CheckCRC(uint64_t CRC);

#define ExampleETSI_ExampleETSI_DebugLevel_PARAM "ExampleETSI.DebugLevel"
#define ExampleETSI_ExampleETSI_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_DebugLevel_MAX 255


#define ExampleETSI_ExampleETSI_CANThr_DebugLevel_PARAM "ExampleETSI.CANThr.DebugLevel"
#define ExampleETSI_ExampleETSI_CANThr_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_CANThr_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_CANThr_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_CANThr
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_CANThr;

#define ExampleETSI_ExampleETSI_CANThr_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_CANThr_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_CANVState_DebugLevel_PARAM "ExampleETSI.CANVState.DebugLevel"
#define ExampleETSI_ExampleETSI_CANVState_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_CANVState_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_CANVState_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_CANVState
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_CANVState;

#define ExampleETSI_ExampleETSI_CANVState_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_CANVState_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_PARAM "ExampleETSI.ITSCtrl.DebugLevel"
#define ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_ITSCtrl
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_ITSCtrl;

#define ExampleETSI_ExampleETSI_ITSCtrl_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_ITSCtrl_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_ITSRx_DebugLevel_PARAM "ExampleETSI.ITSRx.DebugLevel"
#define ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_ITSRx_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_ITSRx
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_ITSRx;

#define ExampleETSI_ExampleETSI_ITSRx_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_ITSRx_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_ITSTx_DebugLevel_PARAM "ExampleETSI.ITSTx.DebugLevel"
#define ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_ITSTx_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_ITSTx
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_ITSTx;

#define ExampleETSI_ExampleETSI_ITSTx_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_ITSTx_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_Main_DebugLevel_PARAM "ExampleETSI.Main.DebugLevel"
#define ExampleETSI_ExampleETSI_Main_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_Main_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_Main_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_Main
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_Main;

#define ExampleETSI_ExampleETSI_Main_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_Main_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_PosExt_DebugLevel_PARAM "ExampleETSI.PosExt.DebugLevel"
#define ExampleETSI_ExampleETSI_PosExt_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_PosExt_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_PosExt_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_PosExt
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_PosExt;

#define ExampleETSI_ExampleETSI_PosExt_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_PosExt_NUM_FLD (1)


#define ExampleETSI_ExampleETSI_Raw_DebugLevel_PARAM "ExampleETSI.Raw.DebugLevel"
#define ExampleETSI_ExampleETSI_Raw_DebugLevel_MIN -1
#define ExampleETSI_ExampleETSI_Raw_DebugLevel_DEF -1
#define ExampleETSI_ExampleETSI_Raw_DebugLevel_MAX 255

typedef struct ExampleETSI_ExampleETSI_Raw
{
  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI_Raw;

#define ExampleETSI_ExampleETSI_Raw_NUM_SUB (0)
#define ExampleETSI_ExampleETSI_Raw_NUM_FLD (1)

typedef struct ExampleETSI_ExampleETSI
{
  tExampleETSI_ExampleETSI_CANThr CANThr;

  tExampleETSI_ExampleETSI_CANVState CANVState;

  tExampleETSI_ExampleETSI_ITSCtrl ITSCtrl;

  tExampleETSI_ExampleETSI_ITSRx ITSRx;

  tExampleETSI_ExampleETSI_ITSTx ITSTx;

  tExampleETSI_ExampleETSI_Main Main;

  tExampleETSI_ExampleETSI_PosExt PosExt;

  tExampleETSI_ExampleETSI_Raw Raw;

  /**
   * DebugLevel default is -1, min/max -1/255
   */
  int32_t DebugLevel;
} tExampleETSI_ExampleETSI;

#define ExampleETSI_ExampleETSI_NUM_SUB (8)
#define ExampleETSI_ExampleETSI_NUM_FLD (1)

/// compiled-in defaults
extern const tExampleETSI_ExampleETSI ExampleETSI_ExampleETSI_DEF;
/// Internals.... only for unit test...
const struct Conf_Callbacks * ExampleETSI_Callbacks(void);

/**
 * @brief Get a R/O copy.
 *
 * Release with @ref ExampleETSI_Release.
 *
 * @return Read-only instance of @ref ExampleETSI_ExampleETSI.
 */
const tExampleETSI_ExampleETSI * ExampleETSI_Get(void);

/**
 * @brief Get a R/W copy.
 *
 * Discard with @ref ExampleETSI_ExampleETSI_Clean
 * or commit and retain with with @ref ExampleETSI_Put.
 * or commit and discard with with @ref ExampleETSI_Push.
 *
 * @return Read/Write instance of @ref ExampleETSI_ExampleETSI.
 */
tExampleETSI_ExampleETSI * ExampleETSI_Clone(void);

/**
 * @brief Release a R/O copy.
 *
 * Discard with a copy obtained with @ref ExampleETSI_Get
 * *ppExampleETSI_ExampleETSI is set to NULL to help avoid use-after-free.
 *
 * @param ppExampleETSI_ExampleETSI Pointer to tExampleETSI_ExampleETSI to be cleaned up a f free(3)'d
 */
void ExampleETSI_Release(const tExampleETSI_ExampleETSI ** ppExampleETSI_ExampleETSI);

/**
 * @brief Commit a R/O copy.
 *
 * Deep clean pExampleETSI_ExampleETSI.
 * pExampleETSI_ExampleETSI is not altered or free(3)'d
 *
 * @param pExampleETSI_ExampleETSI Pointer to tExampleETSI_ExampleETSI to update parameters with.
 */
void ExampleETSI_Put(const tExampleETSI_ExampleETSI * pExampleETSI_ExampleETSI);

/**
 * @brief Commit and clean up ppExampleETSI_ExampleETSI.
 *
 * Applies *ppExampleETSI_ExampleETSI as the new configuration.
 * *ppExampleETSI_ExampleETSI is set to NULL to help avoid use-after-free.
 * Use with @ref ExampleETSI_Clone.
 *
 * @param ppExampleETSI_ExampleETSI Pointer to tExampleETSI_ExampleETSI to update parameters with and clean up.
 */
void ExampleETSI_Push(tExampleETSI_ExampleETSI ** ppExampleETSI_ExampleETSI);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_CANThr_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_CANThr * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_CANVState_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_CANVState * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_ITSCtrl_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSCtrl * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_ITSRx_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSRx * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_ITSTx_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSTx * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_Main_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_Main * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_PosExt_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_PosExt * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits);

/**
 * @brief Write to file
 *
 * @param pFile where to dump
 * @param pDump what to dump
 * @param SkipDefault skip values at their default
 * @param SkipDisabled skip structure where DISABLED is false
 * @param ShowLimits show min/max
 */
void ExampleETSI_ExampleETSI_Raw_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_Raw * pDump,
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
int  ExampleETSI_ExampleETSI_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_CANThr_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_CANThr * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_CANVState_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_CANVState * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_ITSCtrl_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSCtrl * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_ITSRx_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSRx * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_ITSTx_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSTx * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_Main_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_Main * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_PosExt_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_PosExt * pParse,
  int Mode);

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
int  ExampleETSI_ExampleETSI_Raw_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_Raw * pParse,
  int Mode);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_Check(
  const tExampleETSI_ExampleETSI * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_CANThr_Check(
  const tExampleETSI_ExampleETSI_CANThr * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_CANVState_Check(
  const tExampleETSI_ExampleETSI_CANVState * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_ITSCtrl_Check(
  const tExampleETSI_ExampleETSI_ITSCtrl * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_ITSRx_Check(
  const tExampleETSI_ExampleETSI_ITSRx * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_ITSTx_Check(
  const tExampleETSI_ExampleETSI_ITSTx * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_Main_Check(
  const tExampleETSI_ExampleETSI_Main * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_PosExt_Check(
  const tExampleETSI_ExampleETSI_PosExt * pCheck);

/**
 * @brief Sanity Check
 *
 * @param pCheck what to check
 *
 * @return 0 iff sane
 */
int  ExampleETSI_ExampleETSI_Raw_Check(
  const tExampleETSI_ExampleETSI_Raw * pCheck);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_Init(
  tExampleETSI_ExampleETSI * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_CANThr_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_CANThr_Init(
  tExampleETSI_ExampleETSI_CANThr * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_CANVState_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_CANVState_Init(
  tExampleETSI_ExampleETSI_CANVState * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_ITSCtrl_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_ITSCtrl_Init(
  tExampleETSI_ExampleETSI_ITSCtrl * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_ITSRx_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_ITSRx_Init(
  tExampleETSI_ExampleETSI_ITSRx * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_ITSTx_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_ITSTx_Init(
  tExampleETSI_ExampleETSI_ITSTx * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_Main_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_Main_Init(
  tExampleETSI_ExampleETSI_Main * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_PosExt_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_PosExt_Init(
  tExampleETSI_ExampleETSI_PosExt * pInit);

/**
 * @brief Load with compiled-in defaults
 *
 * This is probably not what you want.
 * Try @ref ExampleETSI_ExampleETSI_Raw_Copy with pSrc set to NULL
 */
int  ExampleETSI_ExampleETSI_Raw_Init(
  tExampleETSI_ExampleETSI_Raw * pInit);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_Clean(
  tExampleETSI_ExampleETSI * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_CANThr_Clean(
  tExampleETSI_ExampleETSI_CANThr * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_CANVState_Clean(
  tExampleETSI_ExampleETSI_CANVState * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_ITSCtrl_Clean(
  tExampleETSI_ExampleETSI_ITSCtrl * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_ITSRx_Clean(
  tExampleETSI_ExampleETSI_ITSRx * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_ITSTx_Clean(
  tExampleETSI_ExampleETSI_ITSTx * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_Main_Clean(
  tExampleETSI_ExampleETSI_Main * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_PosExt_Clean(
  tExampleETSI_ExampleETSI_PosExt * pClean);

/**
 * @brief Clean up
 *
 * pClean is not free(d)'d
 *
 * @param pClean what to clean
 */
void ExampleETSI_ExampleETSI_Raw_Clean(
  tExampleETSI_ExampleETSI_Raw * pClean);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_Copy(
  tExampleETSI_ExampleETSI * pDst,
  const tExampleETSI_ExampleETSI * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_CANThr_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_CANThr_Copy(
  tExampleETSI_ExampleETSI_CANThr * pDst,
  const tExampleETSI_ExampleETSI_CANThr * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_CANVState_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_CANVState_Copy(
  tExampleETSI_ExampleETSI_CANVState * pDst,
  const tExampleETSI_ExampleETSI_CANVState * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_ITSCtrl_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_ITSCtrl_Copy(
  tExampleETSI_ExampleETSI_ITSCtrl * pDst,
  const tExampleETSI_ExampleETSI_ITSCtrl * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_ITSRx_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_ITSRx_Copy(
  tExampleETSI_ExampleETSI_ITSRx * pDst,
  const tExampleETSI_ExampleETSI_ITSRx * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_ITSTx_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_ITSTx_Copy(
  tExampleETSI_ExampleETSI_ITSTx * pDst,
  const tExampleETSI_ExampleETSI_ITSTx * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_Main_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_Main_Copy(
  tExampleETSI_ExampleETSI_Main * pDst,
  const tExampleETSI_ExampleETSI_Main * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_PosExt_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_PosExt_Copy(
  tExampleETSI_ExampleETSI_PosExt * pDst,
  const tExampleETSI_ExampleETSI_PosExt * pSrc);

/**
 * @brief Deep copy
 *
 * Calls @ref ExampleETSI_ExampleETSI_Raw_Clean on pSrc
 * Use current settings if pSrc is NULL
 */
int  ExampleETSI_ExampleETSI_Raw_Copy(
  tExampleETSI_ExampleETSI_Raw * pDst,
  const tExampleETSI_ExampleETSI_Raw * pSrc);

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
int  ExampleETSI_ExampleETSI_Comp(
  const tExampleETSI_ExampleETSI * pA,
  const tExampleETSI_ExampleETSI * pB);

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
int  ExampleETSI_ExampleETSI_CANThr_Comp(
  const tExampleETSI_ExampleETSI_CANThr * pA,
  const tExampleETSI_ExampleETSI_CANThr * pB);

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
int  ExampleETSI_ExampleETSI_CANVState_Comp(
  const tExampleETSI_ExampleETSI_CANVState * pA,
  const tExampleETSI_ExampleETSI_CANVState * pB);

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
int  ExampleETSI_ExampleETSI_ITSCtrl_Comp(
  const tExampleETSI_ExampleETSI_ITSCtrl * pA,
  const tExampleETSI_ExampleETSI_ITSCtrl * pB);

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
int  ExampleETSI_ExampleETSI_ITSRx_Comp(
  const tExampleETSI_ExampleETSI_ITSRx * pA,
  const tExampleETSI_ExampleETSI_ITSRx * pB);

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
int  ExampleETSI_ExampleETSI_ITSTx_Comp(
  const tExampleETSI_ExampleETSI_ITSTx * pA,
  const tExampleETSI_ExampleETSI_ITSTx * pB);

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
int  ExampleETSI_ExampleETSI_Main_Comp(
  const tExampleETSI_ExampleETSI_Main * pA,
  const tExampleETSI_ExampleETSI_Main * pB);

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
int  ExampleETSI_ExampleETSI_PosExt_Comp(
  const tExampleETSI_ExampleETSI_PosExt * pA,
  const tExampleETSI_ExampleETSI_PosExt * pB);

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
int  ExampleETSI_ExampleETSI_Raw_Comp(
  const tExampleETSI_ExampleETSI_Raw * pA,
  const tExampleETSI_ExampleETSI_Raw * pB);

/**
 * @brief Update "DebugLevel"s
 *
 * update main DebugLevel and friends.
 *
 * @param pRO Config to update DebugLevels with
 * @param DebugLevel Default Debug Level
 */
void ExampleETSI_ExampleETSI_UpdateDebug(
  const tExampleETSI_ExampleETSI * pRO,
  int DebugLevel);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
