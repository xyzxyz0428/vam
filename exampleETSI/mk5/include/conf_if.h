#pragma once
/**
 * @addtogroup conf_if Configuration2 service
 * @{
 *
 * Configuration 2
 *
 * Conf2 is the 'second-generation' configuration control system and supersedes
 * conf which is now deprecated. Conf2 allows localised configuration settings
 * per module, hierarchical parameters and is run-time extensible.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_CONF_CONF_IF_H_
#define __PLAT_CONF_CONF_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define CONF_MODE_STRICT   0
#define CONF_MODE_LIMIT    1
#define CONF_MODE_ALLOW    2

#define CONF_ERROR_INVALID (1 << 0)
#define CONF_ERROR_OM      (1 << 1)
#define CONF_ERROR_LOW     (1 << 2)
#define CONF_ERROR_HIGH    (1 << 3)
#define CONF_ERROR_UNK     (1 << 4)
#define CONF_ERROR_NULL    (1 << 5)
#define CONF_ERROR_FOPEN   (1 << 6)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

  struct Conf_Callbacks;
  struct Conf_Registered;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

  void Conf2_Init(void);
  void Conf2_Exit(void);

  int Conf2_ParseFile(const char * pFilename, int Mode);

  int Conf2_ParseLines(const char * pLines, int Mode);
  int Conf2_ParseLinesFmt(const char * pLinesFmt, ...) __attribute__ ((format (printf, 1, 2)));

  struct Conf_Registered * Conf2_Register(const struct Conf_Callbacks * pConf_Callbacks);
  void Conf2_DeRegister(const struct Conf_Callbacks * pConf_Callbacks);

  const void * Conf2_Get(struct Conf_Registered * pConf_Registered);
  void Conf2_Release(struct Conf_Registered * pConf_Registered, const void ** ppConf);

  void Conf2_Put(struct Conf_Registered * pConf_Registered, const void * pConf);

  void Conf2_Dump(FILE * pFile,
                  bool SkipDefault,
                  bool SkipDisabled,
                  bool ShowLimts);
  void Conf2_DumpTo(const char * pFilename,
                    bool SkipDefault,
                    bool SkipDisabled,
                    bool ShowLimts);

  int Conf2_DebugUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // __PLAT_CONF_CONF_IF_H_

// Close the doxygen group
/**
 * @}
 */
