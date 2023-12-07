#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
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

#define CONF_MAX_NESTED_FILES 10

typedef int  (fConf_Callback_Check)(const void * pCheck);
typedef void (fConf_Callback_Clean)(void * pClean);
typedef int  (fConf_Callback_Comp) (const void * pA, const void * pB);
typedef int  (fConf_Callback_Copy) (void * pDst, const void * pSrc);
typedef void (fConf_Callback_Dump) (FILE * pFile, const void * pDump,
                                    bool SkipDefault, bool SkipDisabled,
                                    bool ShowLimits);
typedef int  (fConf_Callback_Init) (void * pInit);
typedef int  (fConf_Callback_Parse)(const char * pKey, const char * pValue,
                                    void * pParse, int Mode);
typedef void (fConf_Callback_Debug)(const void * pRO, int DebugLevel);

typedef struct Conf_Callbacks
{
    uint64_t CRC;
    fConf_Callback_Check * pConf_Callback_Check;
    fConf_Callback_Clean * pConf_Callback_Clean;
    fConf_Callback_Comp  * pConf_Callback_Comp;
    fConf_Callback_Copy  * pConf_Callback_Copy;
    fConf_Callback_Dump  * pConf_Callback_Dump;
    fConf_Callback_Init  * pConf_Callback_Init;
    fConf_Callback_Parse * pConf_Callback_Parse;
    fConf_Callback_Debug * pConf_Callback_Debug;
    const char * pPrefix;
    size_t Size;
} tConf_Callbacks;

typedef struct Conf_Files
{
    unsigned Idx;
    FILE * aFiles[CONF_MAX_NESTED_FILES + 1];
} tConf_Files;

int Check_double(double Value, double Min, double Max, const char * pParam)
  __attribute__ ((warn_unused_result));
int Check_float(float Value, float Min, float Max, const char * pParam)
  __attribute__ ((warn_unused_result));
int Check_int32_t(int32_t Value, int32_t Min, int32_t Max, const char * pParam)
  __attribute__ ((warn_unused_result));
int Check_uint32_t(uint32_t Value, uint32_t Min, uint32_t Max, const char * pParam)
  __attribute__ ((warn_unused_result));

int Copy_String(const char ** ppDst, const char * pSrc)
  __attribute__ ((warn_unused_result));

int Parse_String  (const char * pValue, const char ** ppVal)
  __attribute__ ((warn_unused_result));
int Parse_bool    (const char * pValue, bool * pBool)
  __attribute__ ((warn_unused_result));
int Parse_double   (const char * pValue, double  * pVal, double   Min, double   Max, int Mode)
  __attribute__ ((warn_unused_result));
int Parse_float   (const char * pValue, float    * pVal, float    Min, float    Max, int Mode)
  __attribute__ ((warn_unused_result));
int Parse_int32_t (const char * pValue, int32_t  * pVal, int32_t  Min, int32_t  Max, int Mode)
  __attribute__ ((warn_unused_result));
int Parse_uint32_t(const char * pValue, uint32_t * pVal, uint32_t Min, uint32_t Max, int Mode)
  __attribute__ ((warn_unused_result));
int Parse_Debug (const char * pValue, int32_t  * pVal, int32_t  Min, int32_t  Max, int Mode)
  __attribute__ ((warn_unused_result));

void Clean_String(const char ** ppValue);

void Dump_String  (FILE * pFile, const char * pName,
                   const char * pValue, const char * pDefault, bool SkipDefault);
void Dump_bool    (FILE * pFile, const char * pName, bool Value, bool Default, bool SkipDefault);
void Dump_double  (FILE * pFile, const char * pName, double Value, double Default, bool SkipDefault, bool ShowLimits, double mn, double mx);
void Dump_float   (FILE * pFile, const char * pName, float Value, float Default, bool SkipDefault, bool ShowLimits, float mn, float mx);
void Dump_int32_t (FILE * pFile, const char * pName, int32_t Value, int32_t Default, bool SkipDefault, bool ShowLimits, int32_t mn, int32_t mx);
void Dump_uint32_t(FILE * pFile, const char * pName, uint32_t Value, uint32_t Default, bool SkipDefault, bool ShowLimits, uint32_t mn, uint32_t mx);
void Dump_Debug(FILE * pFile, const char * pName,
                int32_t Value, int32_t Default, bool SkipDefault,
                bool ShowLimits, int32_t mn, int32_t mx);

int Comp_String  (const char * pA, const char * pB);
int Comp_bool    (bool A, bool B);
int Comp_double  (double A, double B);
int Comp_float   (float A, float B);
int Comp_int32_t (int32_t A, int32_t B);
int Comp_uint32_t(uint32_t A, uint32_t B);


int Init_String(const char ** ppValue, const char * pDefault)
  __attribute__ ((warn_unused_result));

bool Conf_ParseString(char * pString, char ** ppKey, char ** ppValue);
int Conf_OpenFile(const char * pFilename, tConf_Files * pConf_Files);
char * Conf_GetLine(tConf_Files * pConf_Files);

int Check_blob(const tConfBlob * pValue, size_t minLen, size_t maxLen, const char * pParam);
int Parse_blob(const char * pValue, tConfBlob * pVal,
               uint32_t MinLen, uint32_t MaxLen, int Mode)
  __attribute__ ((warn_unused_result));
void Dump_blob(FILE * pFile, const char * pName,
               const tConfBlob * pValue, const tConfBlob * pDefault,
               bool SkipDefault);
int Comp_blob  (const tConfBlob * pA, const tConfBlob * pB);
void Clean_blob (const tConfBlob * pClean);
int Copy_blob(tConfBlob * pDst, const tConfBlob * pSrc)
  __attribute__ ((warn_unused_result));

void Conf_Stash(const char * pFilename);

const char * Conf_EncodeString(const char * pIn, char ** ppBuff);

#ifdef __cplusplus
}
#endif
