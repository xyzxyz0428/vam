#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef BUILD_BUG_ON
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#endif

typedef struct ConfBlob
{
  const void * pBlob;
  size_t Len;
} tConfBlob;

struct Conf_Callbacks;

int Conf_check(const struct Conf_Callbacks * pConf_Callbacks, const void * pConf);
int Conf_clean(const struct Conf_Callbacks * pConf_Callbacks, void * pConf);
int Conf_comp (const struct Conf_Callbacks * pConf_Callbacks, const void * pA, const void * pB);
int Conf_copy (const struct Conf_Callbacks * pConf_Callbacks, void * pDst, const void * pSrc);
int Conf_dump (const struct Conf_Callbacks * pConf_Callbacks, const void * pConf,
               FILE * pFile, bool SkipDefault, bool SkipDisabled, bool ShowLimits);
int Conf_init (const struct Conf_Callbacks * pConf_Callbacks, void * pConf);
int Conf_parse(const struct Conf_Callbacks * pConf_Callbacks, void * pConf,
               const char * pFilename, int Mode);


#ifdef __cplusplus
}
#endif
