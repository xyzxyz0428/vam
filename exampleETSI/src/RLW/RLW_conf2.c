#include "RLW_defn.h"

#include "conf_common.h"
#include "conf_if.h"
#include "conf_internal.h"

#include <stdlib.h>

static const tConf_Callbacks Callbacks_RLW_Cust_App_RLW =
{
  .CRC                  = RLW_CRC, // 0x70367af559ed7300
  .pConf_Callback_Check = (fConf_Callback_Check *)RLW_Cust_App_RLW_Check,
  .pConf_Callback_Clean = (fConf_Callback_Clean *)RLW_Cust_App_RLW_Clean,
  .pConf_Callback_Comp  = (fConf_Callback_Comp  *)RLW_Cust_App_RLW_Comp,
  .pConf_Callback_Copy  = (fConf_Callback_Copy  *)RLW_Cust_App_RLW_Copy,
  .pConf_Callback_Dump  = (fConf_Callback_Dump  *)RLW_Cust_App_RLW_Dump,
  .pConf_Callback_Init  = (fConf_Callback_Init  *)RLW_Cust_App_RLW_Init,
  .pConf_Callback_Parse = (fConf_Callback_Parse *)RLW_Cust_App_RLW_Parse,
  .pConf_Callback_Debug = (fConf_Callback_Debug *)(void*)RLW_Cust_App_RLW_UpdateDebug,
  .pPrefix              = "Cust_App_RLW.",
  .Size                 = sizeof(tRLW_Cust_App_RLW),
///  .MaxParamNameLen      = 29,
};

static struct Conf_Registered * pConf_Registered = NULL;

bool RLW_CheckCRC(uint64_t CRC)
{
  return ((RLW_CRC == 0x70367af559ed7300ull)
          &&
          (RLW_CRC == CRC));
}

const tRLW_Cust_App_RLW * RLW_Get(void)
{
  const void * pConf = Conf2_Get(pConf_Registered);
  const tRLW_Cust_App_RLW * pRLW_Cust_App_RLW  = (const tRLW_Cust_App_RLW *)pConf;
  if (pRLW_Cust_App_RLW == NULL)
  {
    return &RLW_Cust_App_RLW_DEF;
  }
  return pRLW_Cust_App_RLW;
}

tRLW_Cust_App_RLW * RLW_Clone(void)
{
  const tRLW_Cust_App_RLW * pGet = RLW_Get();
  if (pGet == NULL)
  {
    return NULL;
  }
  tRLW_Cust_App_RLW * pClone = (tRLW_Cust_App_RLW *)calloc(1, sizeof(tRLW_Cust_App_RLW));
  if (pClone != NULL)
  {
    int Res = RLW_Cust_App_RLW_Copy(pClone, pGet);
    if (Res != 0)
    {
      RLW_Cust_App_RLW_Clean(pClone);
      free(pClone);
      pClone = NULL;
    }
  }
  RLW_Release(&pGet);
  return pClone;
}

void RLW_Release(const tRLW_Cust_App_RLW ** ppRLW_Cust_App_RLW)
{
  if ((ppRLW_Cust_App_RLW == NULL) || (*ppRLW_Cust_App_RLW == NULL))
  {
    return;
  }
  if (*ppRLW_Cust_App_RLW == &RLW_Cust_App_RLW_DEF)
  {
    *ppRLW_Cust_App_RLW = NULL;
    return;
  }
  Conf2_Release(pConf_Registered, (const void **)ppRLW_Cust_App_RLW);
}

void RLW_Put(const tRLW_Cust_App_RLW * pRLW_Cust_App_RLW)
{
  Conf2_Put(pConf_Registered, (const void *)pRLW_Cust_App_RLW);
}

void RLW_Push(tRLW_Cust_App_RLW ** ppRLW_Cust_App_RLW)
{
  if ((ppRLW_Cust_App_RLW  != NULL)
      &&
      (*ppRLW_Cust_App_RLW != NULL))
  {
    RLW_Put(*ppRLW_Cust_App_RLW);
    RLW_Cust_App_RLW_Clean(*ppRLW_Cust_App_RLW);
    free(*ppRLW_Cust_App_RLW);
    *ppRLW_Cust_App_RLW = NULL;
  }
}

static void RLW_Load(void)   __attribute__((constructor));
static void RLW_UnLoad(void) __attribute__((destructor));
void RLW_Load(void)
{
  Conf2_Init();
  pConf_Registered = Conf2_Register(&Callbacks_RLW_Cust_App_RLW);
}

void RLW_UnLoad(void)
{
  Conf2_DeRegister(&Callbacks_RLW_Cust_App_RLW);
  Conf2_Exit();
}
void RLW_Cust_App_RLW_Dump(
  FILE * pFile,
  const tRLW_Cust_App_RLW * pDump,
  /*int MaxParamNameLen,*/
  bool SkipDefault,
  bool SkipDisabled,
  bool ShowLimits)
{
  if (pFile == NULL) return;
  if (pDump == NULL) return;
  if (SkipDisabled && !pDump->ENABLE) return;
  (void)ShowLimits;
///  MaxParamNameLen = MaxParamNameLen ?: 29;
  Dump_Debug(pFile, "Cust_App_RLW.DebugLevel", pDump->DebugLevel, -1, /*MaxParamNameLen, */SkipDefault, ShowLimits, -1, 255);
  Dump_bool(pFile, "Cust_App_RLW.ENABLE", pDump->ENABLE, false, /*MaxParamNameLen, */SkipDefault);
  Dump_bool(pFile, "Cust_App_RLW.REC_ENABLE", pDump->REC_ENABLE, false, /*MaxParamNameLen, */SkipDefault);
  Dump_int32_t(pFile, "Cust_App_RLW.REC_SEVERITY_MAX", pDump->REC_SEVERITY_MAX, 205, /*MaxParamNameLen, */SkipDefault, ShowLimits, 0, 255);
  Dump_int32_t(pFile, "Cust_App_RLW.REC_SEVERITY_MIN", pDump->REC_SEVERITY_MIN, 181, /*MaxParamNameLen, */SkipDefault, ShowLimits, 0, 255);
}

int RLW_Cust_App_RLW_DebugLevel = 4; //default_stack_Cohda_DebugLevel_WARN
static void _RLW_Cust_App_RLW_debug(
  const tRLW_Cust_App_RLW * pRO,
  int DebugLevel)
{
  (void)DebugLevel;
  if (pRO == NULL) return;
  if (pRO->DebugLevel != -1)
  {
    DebugLevel = pRO->DebugLevel;
  }
  RLW_Cust_App_RLW_DebugLevel = DebugLevel;
}
void RLW_Cust_App_RLW_UpdateDebug(
  const tRLW_Cust_App_RLW * pRO,
  int DebugLevel)
{
  if ((DebugLevel < 0) || (DebugLevel > 255))
  {
    DebugLevel = 4;
  }
  _RLW_Cust_App_RLW_debug(pRO, DebugLevel);
}
int  RLW_Cust_App_RLW_Parse(
  const char * pKey,
  const char * pValue,
  tRLW_Cust_App_RLW * pParse,
  int Mode)
{
  (void)Mode;
  if (pParse == NULL) return CONF_ERROR_NULL;
  if (!strcmp(pKey, "DebugLevel"))
  {
    return Parse_Debug(pValue, &pParse->DebugLevel, RLW_Cust_App_RLW_DebugLevel_MIN, RLW_Cust_App_RLW_DebugLevel_MAX, Mode);
  }
  if (!strcmp(pKey, "ENABLE"))
  {
    return Parse_bool(pValue, &pParse->ENABLE);
  }
  if (!strcmp(pKey, "REC_ENABLE"))
  {
    return Parse_bool(pValue, &pParse->REC_ENABLE);
  }
  if (!strcmp(pKey, "REC_SEVERITY_MAX"))
  {
    return Parse_int32_t(pValue, &pParse->REC_SEVERITY_MAX, RLW_Cust_App_RLW_REC_SEVERITY_MAX_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MAX_MAX, Mode);
  }
  if (!strcmp(pKey, "REC_SEVERITY_MIN"))
  {
    return Parse_int32_t(pValue, &pParse->REC_SEVERITY_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MIN_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MIN_MAX, Mode);
  }
  return CONF_ERROR_UNK;
}
int  RLW_Cust_App_RLW_Check(
  const tRLW_Cust_App_RLW * pCheck)
{
  int ret = 0;
  if (pCheck == NULL) return CONF_ERROR_NULL;
  ret |= Check_int32_t(pCheck->DebugLevel, RLW_Cust_App_RLW_DebugLevel_MIN, RLW_Cust_App_RLW_DebugLevel_MAX, RLW_Cust_App_RLW_DebugLevel_PARAM);
  ret |= Check_int32_t(pCheck->REC_SEVERITY_MAX, RLW_Cust_App_RLW_REC_SEVERITY_MAX_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MAX_MAX, RLW_Cust_App_RLW_REC_SEVERITY_MAX_PARAM);
  ret |= Check_int32_t(pCheck->REC_SEVERITY_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MIN_MIN, RLW_Cust_App_RLW_REC_SEVERITY_MIN_MAX, RLW_Cust_App_RLW_REC_SEVERITY_MIN_PARAM);
  return ret;
}
extern const tRLW_Cust_App_RLW RLW_Cust_App_RLW_DEF;
int  RLW_Cust_App_RLW_Init(
  tRLW_Cust_App_RLW * pInit)
{
  return RLW_Cust_App_RLW_Copy(pInit, &RLW_Cust_App_RLW_DEF);
}
void RLW_Cust_App_RLW_Clean(
  tRLW_Cust_App_RLW * pClean)
{
  if (pClean == NULL) return;
}
int  RLW_Cust_App_RLW_Copy(
  tRLW_Cust_App_RLW * pDst,
  const tRLW_Cust_App_RLW * pSrc)
{
  int Res = 0;
  if (pDst == NULL) return CONF_ERROR_NULL;
  if (pSrc == pDst) return CONF_ERROR_INVALID;
  if (pSrc == NULL)
  {
    const tRLW_Cust_App_RLW * pRLW = RLW_Get();
    if (pRLW == NULL)
    {
      return CONF_ERROR_NULL;
    }
    pSrc = pRLW;
    Res = RLW_Cust_App_RLW_Copy(pDst, pSrc);
    RLW_Release(&pRLW);
    return Res;
  }
  pDst->DebugLevel = pSrc->DebugLevel;
  pDst->ENABLE = pSrc->ENABLE;
  pDst->REC_ENABLE = pSrc->REC_ENABLE;
  pDst->REC_SEVERITY_MAX = pSrc->REC_SEVERITY_MAX;
  pDst->REC_SEVERITY_MIN = pSrc->REC_SEVERITY_MIN;
  return Res;
}
int  RLW_Cust_App_RLW_Comp(
  const tRLW_Cust_App_RLW * pA,
  const tRLW_Cust_App_RLW * pB)
{
  int Res = 0;
  if (pA == NULL) return CONF_ERROR_NULL;
  if (pB == NULL) return CONF_ERROR_NULL;
  Res = Comp_int32_t(pA->DebugLevel, pB->DebugLevel);
  if (Res != 0) return Res;
  Res = Comp_bool(pA->ENABLE, pB->ENABLE);
  if (Res != 0) return Res;
  Res = Comp_bool(pA->REC_ENABLE, pB->REC_ENABLE);
  if (Res != 0) return Res;
  Res = Comp_int32_t(pA->REC_SEVERITY_MAX, pB->REC_SEVERITY_MAX);
  if (Res != 0) return Res;
  Res = Comp_int32_t(pA->REC_SEVERITY_MIN, pB->REC_SEVERITY_MIN);
  if (Res != 0) return Res;
  return Res;
}
const tRLW_Cust_App_RLW RLW_Cust_App_RLW_DEF =
{
  .DebugLevel = RLW_Cust_App_RLW_DebugLevel_DEF,
  .REC_SEVERITY_MAX = RLW_Cust_App_RLW_REC_SEVERITY_MAX_DEF,
  .REC_SEVERITY_MIN = RLW_Cust_App_RLW_REC_SEVERITY_MIN_DEF,
  .ENABLE = RLW_Cust_App_RLW_ENABLE_DEF,
  .REC_ENABLE = RLW_Cust_App_RLW_REC_ENABLE_DEF,
};
