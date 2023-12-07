#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "conf_common.h"
#include "conf_if.h"
#include "conf_internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

  struct Conf_Pluggable;
  struct Conf_Registered;

  struct Conf_Pluggable * Conf_Construct(void);

  struct Conf_Pluggable * Conf_Clone(const struct Conf_Pluggable * pConf_Pluggable);

  struct Conf_Registered * Conf_Add(struct Conf_Pluggable * pConf_Pluggable,
                                    const struct Conf_Callbacks * pConf_Callbacks);

  void Conf_Remove(struct Conf_Pluggable * pConf_Pluggable,
                   const struct Conf_Callbacks * pConf_Callbacks);

  int Conf_PlugParseFile(struct Conf_Pluggable * pConf_Pluggable,
                         const char * pFilename, int Mode);

  int Conf_PlugParseLines(struct Conf_Pluggable * pConf_PluggableExt,
                          const char * pLines, int Mode);

  int Conf_PlugDebugUpdate(struct Conf_Pluggable * pConf_PluggableExt);

  const void * Conf_PlugGet(struct Conf_Registered * pConf_Registered);
  void Conf_PlugRelease(struct Conf_Registered * pConf_Registered, const void ** ppConf);
  void Conf_PlugPut(struct Conf_Pluggable * pConf_Pluggable,
                    struct Conf_Registered * pConf_Registered,
                    const void * pConf);

  void Conf_PlugDump(struct Conf_Pluggable * pConf_Pluggable,
                     FILE * pFile, bool SkipDefault, bool SkipDisabled,
                     bool ShowLimits);

  const void * Conf_Get(struct Conf_Registered * pConf_Registered);

  const void * Conf_Find(const struct Conf_Pluggable * pConf_Pluggable,
                         const struct Conf_Callbacks * pConf_Callbacks);

  void Conf_Destroy(struct Conf_Pluggable ** ppConf_Pluggable);

#ifdef __cplusplus
}
#endif
