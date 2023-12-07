#include "ExampleETSI_defn.h"

#include "conf_common.h"
#include "conf_if.h"
#include "conf_internal.h"

#include <stdlib.h>

static const tConf_Callbacks Callbacks_ExampleETSI_ExampleETSI =
{
  .CRC                  = ExampleETSI_CRC, // 0xa172731c9187c61e
  .pConf_Callback_Check = (fConf_Callback_Check *)ExampleETSI_ExampleETSI_Check,
  .pConf_Callback_Clean = (fConf_Callback_Clean *)ExampleETSI_ExampleETSI_Clean,
  .pConf_Callback_Comp  = (fConf_Callback_Comp  *)ExampleETSI_ExampleETSI_Comp,
  .pConf_Callback_Copy  = (fConf_Callback_Copy  *)ExampleETSI_ExampleETSI_Copy,
  .pConf_Callback_Dump  = (fConf_Callback_Dump  *)ExampleETSI_ExampleETSI_Dump,
  .pConf_Callback_Init  = (fConf_Callback_Init  *)ExampleETSI_ExampleETSI_Init,
  .pConf_Callback_Parse = (fConf_Callback_Parse *)ExampleETSI_ExampleETSI_Parse,
  .pConf_Callback_Debug = (fConf_Callback_Debug *)(void*)ExampleETSI_ExampleETSI_UpdateDebug,
  .pPrefix              = "ExampleETSI.",
  .Size                 = sizeof(tExampleETSI_ExampleETSI),
///  .MaxParamNameLen      = 32,
};

static struct Conf_Registered * pConf_Registered = NULL;

bool ExampleETSI_CheckCRC(uint64_t CRC)
{
  return ((ExampleETSI_CRC == 0xa172731c9187c61eull)
          &&
          (ExampleETSI_CRC == CRC));
}

const tExampleETSI_ExampleETSI * ExampleETSI_Get(void)
{
  const void * pConf = Conf2_Get(pConf_Registered);
  const tExampleETSI_ExampleETSI * pExampleETSI_ExampleETSI  = (const tExampleETSI_ExampleETSI *)pConf;
  if (pExampleETSI_ExampleETSI == NULL)
  {
    return &ExampleETSI_ExampleETSI_DEF;
  }
  return pExampleETSI_ExampleETSI;
}

tExampleETSI_ExampleETSI * ExampleETSI_Clone(void)
{
  const tExampleETSI_ExampleETSI * pGet = ExampleETSI_Get();
  if (pGet == NULL)
  {
    return NULL;
  }
  tExampleETSI_ExampleETSI * pClone = (tExampleETSI_ExampleETSI *)calloc(1, sizeof(tExampleETSI_ExampleETSI));
  if (pClone != NULL)
  {
    int Res = ExampleETSI_ExampleETSI_Copy(pClone, pGet);
    if (Res != 0)
    {
      ExampleETSI_ExampleETSI_Clean(pClone);
      free(pClone);
      pClone = NULL;
    }
  }
  ExampleETSI_Release(&pGet);
  return pClone;
}

void ExampleETSI_Release(const tExampleETSI_ExampleETSI ** ppExampleETSI_ExampleETSI)
{
  if ((ppExampleETSI_ExampleETSI == NULL) || (*ppExampleETSI_ExampleETSI == NULL))
  {
    return;
  }
  if (*ppExampleETSI_ExampleETSI == &ExampleETSI_ExampleETSI_DEF)
  {
    *ppExampleETSI_ExampleETSI = NULL;
    return;
  }
  Conf2_Release(pConf_Registered, (const void **)ppExampleETSI_ExampleETSI);
}

void ExampleETSI_Put(const tExampleETSI_ExampleETSI * pExampleETSI_ExampleETSI)
{
  Conf2_Put(pConf_Registered, (const void *)pExampleETSI_ExampleETSI);
}

void ExampleETSI_Push(tExampleETSI_ExampleETSI ** ppExampleETSI_ExampleETSI)
{
  if ((ppExampleETSI_ExampleETSI  != NULL)
      &&
      (*ppExampleETSI_ExampleETSI != NULL))
  {
    ExampleETSI_Put(*ppExampleETSI_ExampleETSI);
    ExampleETSI_ExampleETSI_Clean(*ppExampleETSI_ExampleETSI);
    free(*ppExampleETSI_ExampleETSI);
    *ppExampleETSI_ExampleETSI = NULL;
  }
}

static void ExampleETSI_Load(void)   __attribute__((constructor));
static void ExampleETSI_UnLoad(void) __attribute__((destructor));
void ExampleETSI_Load(void)
{
  Conf2_Init();
  pConf_Registered = Conf2_Register(&Callbacks_ExampleETSI_ExampleETSI);
}

void ExampleETSI_UnLoad(void)
{
  Conf2_DeRegister(&Callbacks_ExampleETSI_ExampleETSI);
  Conf2_Exit();
}
void ExampleETSI_ExampleETSI_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
  ExampleETSI_ExampleETSI_CANThr_Dump(pFile, &pDump->CANThr, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_CANVState_Dump(pFile, &pDump->CANVState, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_ITSCtrl_Dump(pFile, &pDump->ITSCtrl, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_ITSRx_Dump(pFile, &pDump->ITSRx, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_ITSTx_Dump(pFile, &pDump->ITSTx, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_Main_Dump(pFile, &pDump->Main, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_PosExt_Dump(pFile, &pDump->PosExt, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
  ExampleETSI_ExampleETSI_Raw_Dump(pFile, &pDump->Raw, /*MaxParamNameLen,*/ SkipDefault, SkipDisabled, ShowLimits);
}
void ExampleETSI_ExampleETSI_CANThr_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_CANThr * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.CANThr.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_CANVState_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_CANVState * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.CANVState.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_ITSCtrl_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSCtrl * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.ITSCtrl.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_ITSRx_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSRx * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.ITSRx.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_ITSTx_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_ITSTx * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.ITSTx.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_Main_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_Main * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.Main.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_PosExt_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_PosExt * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.PosExt.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}
void ExampleETSI_ExampleETSI_Raw_Dump(
  FILE * pFile,
  const tExampleETSI_ExampleETSI_Raw * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  (void)SkipDisabled;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 32;
  Dump_Debug(pFile, "ExampleETSI.Raw.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
}

int ExampleETSI_ExampleETSI_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
int ExampleETSI_ExampleETSI_CANThr_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_CANThr_debug(
  const tExampleETSI_ExampleETSI_CANThr * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_CANThr_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_CANVState_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_CANVState_debug(
  const tExampleETSI_ExampleETSI_CANVState * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_CANVState_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_ITSCtrl_debug(
  const tExampleETSI_ExampleETSI_ITSCtrl * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_ITSRx_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_ITSRx_debug(
  const tExampleETSI_ExampleETSI_ITSRx * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_ITSRx_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_ITSTx_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_ITSTx_debug(
  const tExampleETSI_ExampleETSI_ITSTx * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_ITSTx_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_Main_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_Main_debug(
  const tExampleETSI_ExampleETSI_Main * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_Main_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_PosExt_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_PosExt_debug(
  const tExampleETSI_ExampleETSI_PosExt * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_PosExt_DebugLevel = DebugLevel;
}
int ExampleETSI_ExampleETSI_Raw_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _ExampleETSI_ExampleETSI_Raw_debug(
  const tExampleETSI_ExampleETSI_Raw * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_Raw_DebugLevel = DebugLevel;
}
static void _ExampleETSI_ExampleETSI_debug(
  const tExampleETSI_ExampleETSI * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  ExampleETSI_ExampleETSI_DebugLevel = DebugLevel;
  _ExampleETSI_ExampleETSI_CANThr_debug(&pRO->CANThr, DebugLevel);
  _ExampleETSI_ExampleETSI_CANVState_debug(&pRO->CANVState, DebugLevel);
  _ExampleETSI_ExampleETSI_ITSCtrl_debug(&pRO->ITSCtrl, DebugLevel);
  _ExampleETSI_ExampleETSI_ITSRx_debug(&pRO->ITSRx, DebugLevel);
  _ExampleETSI_ExampleETSI_ITSTx_debug(&pRO->ITSTx, DebugLevel);
  _ExampleETSI_ExampleETSI_Main_debug(&pRO->Main, DebugLevel);
  _ExampleETSI_ExampleETSI_PosExt_debug(&pRO->PosExt, DebugLevel);
  _ExampleETSI_ExampleETSI_Raw_debug(&pRO->Raw, DebugLevel);
}
void ExampleETSI_ExampleETSI_UpdateDebug(
  const tExampleETSI_ExampleETSI * pRO,
  int DebugLevel)
{
  if ((DebugLevel < 0) || (DebugLevel > 255))
  {
    DebugLevel = 4;
  }
  _ExampleETSI_ExampleETSI_debug(pRO, DebugLevel);
}
int  ExampleETSI_ExampleETSI_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_DebugLevel_MIN, ExampleETSI_ExampleETSI_DebugLevel_MAX, Mode);
  }
  if (!strncmp(pKey, "CANThr.", 6 + 1))
  {
    return ExampleETSI_ExampleETSI_CANThr_Parse(pKey + (6 + 1), pValue, &pParse->CANThr, Mode);
  }
  if (!strncmp(pKey, "CANVState.", 9 + 1))
  {
    return ExampleETSI_ExampleETSI_CANVState_Parse(pKey + (9 + 1), pValue, &pParse->CANVState, Mode);
  }
  if (!strncmp(pKey, "ITSCtrl.", 7 + 1))
  {
    return ExampleETSI_ExampleETSI_ITSCtrl_Parse(pKey + (7 + 1), pValue, &pParse->ITSCtrl, Mode);
  }
  if (!strncmp(pKey, "ITSRx.", 5 + 1))
  {
    return ExampleETSI_ExampleETSI_ITSRx_Parse(pKey + (5 + 1), pValue, &pParse->ITSRx, Mode);
  }
  if (!strncmp(pKey, "ITSTx.", 5 + 1))
  {
    return ExampleETSI_ExampleETSI_ITSTx_Parse(pKey + (5 + 1), pValue, &pParse->ITSTx, Mode);
  }
  if (!strncmp(pKey, "Main.", 4 + 1))
  {
    return ExampleETSI_ExampleETSI_Main_Parse(pKey + (4 + 1), pValue, &pParse->Main, Mode);
  }
  if (!strncmp(pKey, "PosExt.", 6 + 1))
  {
    return ExampleETSI_ExampleETSI_PosExt_Parse(pKey + (6 + 1), pValue, &pParse->PosExt, Mode);
  }
  if (!strncmp(pKey, "Raw.", 3 + 1))
  {
    return ExampleETSI_ExampleETSI_Raw_Parse(pKey + (3 + 1), pValue, &pParse->Raw, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_CANThr_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_CANThr * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_CANThr_DebugLevel_MIN, ExampleETSI_ExampleETSI_CANThr_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_CANVState_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_CANVState * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_CANVState_DebugLevel_MIN, ExampleETSI_ExampleETSI_CANVState_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_ITSCtrl_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSCtrl * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_ITSRx_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSRx * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_ITSTx_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_ITSTx * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_Main_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_Main * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_Main_DebugLevel_MIN, ExampleETSI_ExampleETSI_Main_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_PosExt_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_PosExt * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_PosExt_DebugLevel_MIN, ExampleETSI_ExampleETSI_PosExt_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_Raw_Parse(
  const char * pKey,
  const char * pValue,
  tExampleETSI_ExampleETSI_Raw * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, ExampleETSI_ExampleETSI_Raw_DebugLevel_MIN, ExampleETSI_ExampleETSI_Raw_DebugLevel_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  ExampleETSI_ExampleETSI_Check(
  const tExampleETSI_ExampleETSI * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_DebugLevel_MIN, ExampleETSI_ExampleETSI_DebugLevel_MAX, ExampleETSI_ExampleETSI_DebugLevel_PARAM);
  ret |= ExampleETSI_ExampleETSI_CANThr_Check(&pCheck->CANThr);
  ret |= ExampleETSI_ExampleETSI_CANVState_Check(&pCheck->CANVState);
  ret |= ExampleETSI_ExampleETSI_ITSCtrl_Check(&pCheck->ITSCtrl);
  ret |= ExampleETSI_ExampleETSI_ITSRx_Check(&pCheck->ITSRx);
  ret |= ExampleETSI_ExampleETSI_ITSTx_Check(&pCheck->ITSTx);
  ret |= ExampleETSI_ExampleETSI_Main_Check(&pCheck->Main);
  ret |= ExampleETSI_ExampleETSI_PosExt_Check(&pCheck->PosExt);
  ret |= ExampleETSI_ExampleETSI_Raw_Check(&pCheck->Raw);
  return ret;
}
int  ExampleETSI_ExampleETSI_CANThr_Check(
  const tExampleETSI_ExampleETSI_CANThr * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_CANThr_DebugLevel_MIN, ExampleETSI_ExampleETSI_CANThr_DebugLevel_MAX, ExampleETSI_ExampleETSI_CANThr_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_CANVState_Check(
  const tExampleETSI_ExampleETSI_CANVState * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_CANVState_DebugLevel_MIN, ExampleETSI_ExampleETSI_CANVState_DebugLevel_MAX, ExampleETSI_ExampleETSI_CANVState_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_ITSCtrl_Check(
  const tExampleETSI_ExampleETSI_ITSCtrl * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_MAX, ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_ITSRx_Check(
  const tExampleETSI_ExampleETSI_ITSRx * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSRx_DebugLevel_MAX, ExampleETSI_ExampleETSI_ITSRx_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_ITSTx_Check(
  const tExampleETSI_ExampleETSI_ITSTx * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MIN, ExampleETSI_ExampleETSI_ITSTx_DebugLevel_MAX, ExampleETSI_ExampleETSI_ITSTx_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_Main_Check(
  const tExampleETSI_ExampleETSI_Main * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_Main_DebugLevel_MIN, ExampleETSI_ExampleETSI_Main_DebugLevel_MAX, ExampleETSI_ExampleETSI_Main_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_PosExt_Check(
  const tExampleETSI_ExampleETSI_PosExt * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_PosExt_DebugLevel_MIN, ExampleETSI_ExampleETSI_PosExt_DebugLevel_MAX, ExampleETSI_ExampleETSI_PosExt_DebugLevel_PARAM);
  return ret;
}
int  ExampleETSI_ExampleETSI_Raw_Check(
  const tExampleETSI_ExampleETSI_Raw * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, ExampleETSI_ExampleETSI_Raw_DebugLevel_MIN, ExampleETSI_ExampleETSI_Raw_DebugLevel_MAX, ExampleETSI_ExampleETSI_Raw_DebugLevel_PARAM);
  return ret;
}
extern const tExampleETSI_ExampleETSI ExampleETSI_ExampleETSI_DEF;
int  ExampleETSI_ExampleETSI_Init(
  tExampleETSI_ExampleETSI * pInit)
{
  return ExampleETSI_ExampleETSI_Copy(pInit, &ExampleETSI_ExampleETSI_DEF);
}
int  ExampleETSI_ExampleETSI_CANThr_Init(
  tExampleETSI_ExampleETSI_CANThr * pInit)
{
  return ExampleETSI_ExampleETSI_CANThr_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.CANThr);
}
int  ExampleETSI_ExampleETSI_CANVState_Init(
  tExampleETSI_ExampleETSI_CANVState * pInit)
{
  return ExampleETSI_ExampleETSI_CANVState_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.CANVState);
}
int  ExampleETSI_ExampleETSI_ITSCtrl_Init(
  tExampleETSI_ExampleETSI_ITSCtrl * pInit)
{
  return ExampleETSI_ExampleETSI_ITSCtrl_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.ITSCtrl);
}
int  ExampleETSI_ExampleETSI_ITSRx_Init(
  tExampleETSI_ExampleETSI_ITSRx * pInit)
{
  return ExampleETSI_ExampleETSI_ITSRx_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.ITSRx);
}
int  ExampleETSI_ExampleETSI_ITSTx_Init(
  tExampleETSI_ExampleETSI_ITSTx * pInit)
{
  return ExampleETSI_ExampleETSI_ITSTx_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.ITSTx);
}
int  ExampleETSI_ExampleETSI_Main_Init(
  tExampleETSI_ExampleETSI_Main * pInit)
{
  return ExampleETSI_ExampleETSI_Main_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.Main);
}
int  ExampleETSI_ExampleETSI_PosExt_Init(
  tExampleETSI_ExampleETSI_PosExt * pInit)
{
  return ExampleETSI_ExampleETSI_PosExt_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.PosExt);
}
int  ExampleETSI_ExampleETSI_Raw_Init(
  tExampleETSI_ExampleETSI_Raw * pInit)
{
  return ExampleETSI_ExampleETSI_Raw_Copy(pInit, &ExampleETSI_ExampleETSI_DEF.Raw);
}
void ExampleETSI_ExampleETSI_Clean(
  tExampleETSI_ExampleETSI * pClean)
{
  if (pClean == NULL) return;
  ExampleETSI_ExampleETSI_CANThr_Clean(&pClean->CANThr);
  ExampleETSI_ExampleETSI_CANVState_Clean(&pClean->CANVState);
  ExampleETSI_ExampleETSI_ITSCtrl_Clean(&pClean->ITSCtrl);
  ExampleETSI_ExampleETSI_ITSRx_Clean(&pClean->ITSRx);
  ExampleETSI_ExampleETSI_ITSTx_Clean(&pClean->ITSTx);
  ExampleETSI_ExampleETSI_Main_Clean(&pClean->Main);
  ExampleETSI_ExampleETSI_PosExt_Clean(&pClean->PosExt);
  ExampleETSI_ExampleETSI_Raw_Clean(&pClean->Raw);
}
void ExampleETSI_ExampleETSI_CANThr_Clean(
  tExampleETSI_ExampleETSI_CANThr * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_CANVState_Clean(
  tExampleETSI_ExampleETSI_CANVState * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_ITSCtrl_Clean(
  tExampleETSI_ExampleETSI_ITSCtrl * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_ITSRx_Clean(
  tExampleETSI_ExampleETSI_ITSRx * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_ITSTx_Clean(
  tExampleETSI_ExampleETSI_ITSTx * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_Main_Clean(
  tExampleETSI_ExampleETSI_Main * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_PosExt_Clean(
  tExampleETSI_ExampleETSI_PosExt * pClean)
{
  if (pClean == NULL) return;
}
void ExampleETSI_ExampleETSI_Raw_Clean(
  tExampleETSI_ExampleETSI_Raw * pClean)
{
  if (pClean == NULL) return;
}
int  ExampleETSI_ExampleETSI_Copy(
  tExampleETSI_ExampleETSI * pDst,
  const tExampleETSI_ExampleETSI * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = pExampleETSI;
    Res = ExampleETSI_ExampleETSI_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  Res |= ExampleETSI_ExampleETSI_CANThr_Copy(&pDst->CANThr, &pSrc->CANThr);
  Res |= ExampleETSI_ExampleETSI_CANVState_Copy(&pDst->CANVState, &pSrc->CANVState);
  Res |= ExampleETSI_ExampleETSI_ITSCtrl_Copy(&pDst->ITSCtrl, &pSrc->ITSCtrl);
  Res |= ExampleETSI_ExampleETSI_ITSRx_Copy(&pDst->ITSRx, &pSrc->ITSRx);
  Res |= ExampleETSI_ExampleETSI_ITSTx_Copy(&pDst->ITSTx, &pSrc->ITSTx);
  Res |= ExampleETSI_ExampleETSI_Main_Copy(&pDst->Main, &pSrc->Main);
  Res |= ExampleETSI_ExampleETSI_PosExt_Copy(&pDst->PosExt, &pSrc->PosExt);
  Res |= ExampleETSI_ExampleETSI_Raw_Copy(&pDst->Raw, &pSrc->Raw);
  return Res;
}
int  ExampleETSI_ExampleETSI_CANThr_Copy(
  tExampleETSI_ExampleETSI_CANThr * pDst,
  const tExampleETSI_ExampleETSI_CANThr * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->CANThr;
    Res = ExampleETSI_ExampleETSI_CANThr_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_CANVState_Copy(
  tExampleETSI_ExampleETSI_CANVState * pDst,
  const tExampleETSI_ExampleETSI_CANVState * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->CANVState;
    Res = ExampleETSI_ExampleETSI_CANVState_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSCtrl_Copy(
  tExampleETSI_ExampleETSI_ITSCtrl * pDst,
  const tExampleETSI_ExampleETSI_ITSCtrl * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->ITSCtrl;
    Res = ExampleETSI_ExampleETSI_ITSCtrl_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSRx_Copy(
  tExampleETSI_ExampleETSI_ITSRx * pDst,
  const tExampleETSI_ExampleETSI_ITSRx * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->ITSRx;
    Res = ExampleETSI_ExampleETSI_ITSRx_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSTx_Copy(
  tExampleETSI_ExampleETSI_ITSTx * pDst,
  const tExampleETSI_ExampleETSI_ITSTx * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->ITSTx;
    Res = ExampleETSI_ExampleETSI_ITSTx_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_Main_Copy(
  tExampleETSI_ExampleETSI_Main * pDst,
  const tExampleETSI_ExampleETSI_Main * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->Main;
    Res = ExampleETSI_ExampleETSI_Main_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_PosExt_Copy(
  tExampleETSI_ExampleETSI_PosExt * pDst,
  const tExampleETSI_ExampleETSI_PosExt * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->PosExt;
    Res = ExampleETSI_ExampleETSI_PosExt_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_Raw_Copy(
  tExampleETSI_ExampleETSI_Raw * pDst,
  const tExampleETSI_ExampleETSI_Raw * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tExampleETSI_ExampleETSI * pExampleETSI = ExampleETSI_Get();
    if (pExampleETSI == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = &pExampleETSI->Raw;
    Res = ExampleETSI_ExampleETSI_Raw_Copy(pDst, pSrc);
    ExampleETSI_Release(&pExampleETSI);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  return Res;
}
int  ExampleETSI_ExampleETSI_Comp(
  const tExampleETSI_ExampleETSI * pA,
  const tExampleETSI_ExampleETSI * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_CANThr_Comp(&pA->CANThr, &pB->CANThr);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_CANVState_Comp(&pA->CANVState, &pB->CANVState);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_ITSCtrl_Comp(&pA->ITSCtrl, &pB->ITSCtrl);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_ITSRx_Comp(&pA->ITSRx, &pB->ITSRx);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_ITSTx_Comp(&pA->ITSTx, &pB->ITSTx);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_Main_Comp(&pA->Main, &pB->Main);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_PosExt_Comp(&pA->PosExt, &pB->PosExt);
  if (Res != 0) return Res;
  Res = ExampleETSI_ExampleETSI_Raw_Comp(&pA->Raw, &pB->Raw);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_CANThr_Comp(
  const tExampleETSI_ExampleETSI_CANThr * pA,
  const tExampleETSI_ExampleETSI_CANThr * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_CANVState_Comp(
  const tExampleETSI_ExampleETSI_CANVState * pA,
  const tExampleETSI_ExampleETSI_CANVState * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSCtrl_Comp(
  const tExampleETSI_ExampleETSI_ITSCtrl * pA,
  const tExampleETSI_ExampleETSI_ITSCtrl * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSRx_Comp(
  const tExampleETSI_ExampleETSI_ITSRx * pA,
  const tExampleETSI_ExampleETSI_ITSRx * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_ITSTx_Comp(
  const tExampleETSI_ExampleETSI_ITSTx * pA,
  const tExampleETSI_ExampleETSI_ITSTx * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_Main_Comp(
  const tExampleETSI_ExampleETSI_Main * pA,
  const tExampleETSI_ExampleETSI_Main * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_PosExt_Comp(
  const tExampleETSI_ExampleETSI_PosExt * pA,
  const tExampleETSI_ExampleETSI_PosExt * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
int  ExampleETSI_ExampleETSI_Raw_Comp(
  const tExampleETSI_ExampleETSI_Raw * pA,
  const tExampleETSI_ExampleETSI_Raw * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  return Res;
}
const tExampleETSI_ExampleETSI ExampleETSI_ExampleETSI_DEF =
{
  .CANThr = {
    .DebugLevel = ExampleETSI_ExampleETSI_CANThr_DebugLevel_DEF,
  },
  .CANVState = {
    .DebugLevel = ExampleETSI_ExampleETSI_CANVState_DebugLevel_DEF,
  },
  .ITSCtrl = {
    .DebugLevel = ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel_DEF,
  },
  .ITSRx = {
    .DebugLevel = ExampleETSI_ExampleETSI_ITSRx_DebugLevel_DEF,
  },
  .ITSTx = {
    .DebugLevel = ExampleETSI_ExampleETSI_ITSTx_DebugLevel_DEF,
  },
  .Main = {
    .DebugLevel = ExampleETSI_ExampleETSI_Main_DebugLevel_DEF,
  },
  .PosExt = {
    .DebugLevel = ExampleETSI_ExampleETSI_PosExt_DebugLevel_DEF,
  },
  .Raw = {
    .DebugLevel = ExampleETSI_ExampleETSI_Raw_DebugLevel_DEF,
  },
  .DebugLevel = ExampleETSI_ExampleETSI_DebugLevel_DEF,
};
