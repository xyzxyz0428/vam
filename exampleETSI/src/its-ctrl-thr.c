/**
 * @addtogroup mod_its_ctrl ITS Control Module
 * @{
 *
 * ITS control thread
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "libconfig.h" // used to read configuration file

// v2x-lib includes
#include "conf.h"
#include "util.h"
#include "qs-lib.h"
#include "debug-levels.h"

#include "its-ctrl-thr.h"
#include "etsi-fac-c2c-if.h"
#include "etsi-ivi-util.h"
#include "etsi-cam-if.h"
#include "ASNCommon.h"
#include "message.h"
#include "itsasn_def.h"

#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_ITSCtrl_DebugLevel

// Define App triggering interval (mSec)
#define ITSCTRL_NAP_INTERVAL 100

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static int ITSCtrl_LoadConfig (struct ITSCtrl *pITS,
                               char * pConfigFileName);
static int  ITSCtrl_LoadRWWConfig(tITSTxRWWParams *pRWW,
                                  config_setting_t *pSetting);
static int ITSCtrl_LoadEEBLConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting);
static int  ITSCtrl_LoadEVWConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadMapConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadSpatConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting);
static void ITSCtrl_LoadSRMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadSSMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadSAConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting);
static void ITSCtrl_LoadRTCMConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting);
static void ITSCtrl_LoadCPMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadVAMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting);
static void ITSCtrl_LoadIMZMConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting);
static void ITSCtrl_LoadIviConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting);
static int ITSCtrl_LoadIVSConfig(tITSTxIVSParams *pIVS,
                                 config_setting_t *pSetting);
static int ITSCtrl_UnloadConfig (struct ITSCtrl *pITS);

static void ITSCtrl_ThreadProc (void *pArg);

static void ITSCtrl_ReadLatLong(int32_t * pLatitude,
                                int32_t * pLongitude,
                                int32_t * pAltitude,
                                const config_setting_t * pSetting,
                                const char * pLatitudeName,
                                const char * pLongitudeName,
                                const char * pAltitudeName);

static void ITSCtrl_ReadPos(tDENMReferencePoint    * pDENMReferencePoint,
                            const config_setting_t * pSetting,
                            const char * pLatitudeName,
                            const char * pLongitudeName,
                            const char * pAltitudeName,
                            const char * pQualityName);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------


#define DBG_CONFIG
#ifdef  DBG_CONFIG

int config_setting_lookup_bool_DBG(const config_setting_t *setting,
                                   const char *name, int *value)
{
  d_assert(setting);
  d_assert(name);
  d_assert(value);
  int rc = config_setting_lookup_bool(setting, name, value);
  if (rc == CONFIG_TRUE)
  {
    d_printf(D_INTERN, NULL, "Setting '%s' item '%s' to %d (%p,%p,ret=%d)\n",
             SAFE(setting->name), name, *value, setting, value, rc);
  }
  else
  {
    d_printf(D_INTERN, NULL, "(%p{%s},%s,%p{%d}): %d\n",
             setting, SAFE(setting->name), name, value, *value, rc);
  }
  return rc;
}

int config_setting_lookup_int_DBG(const config_setting_t *setting,
                                  const char *name, int *value)
{
  d_assert(setting);
  d_assert(name);
  d_assert(value);
  int rc = config_setting_lookup_int(setting, name, value);
  if (rc == CONFIG_TRUE)
  {
    d_printf(D_INTERN, NULL, "Setting '%s' item '%s' to %d (%p,%p,ret=%d)\n",
             SAFE(setting->name), name, *value, setting, value, rc);
  }
  else
  {
    d_printf(D_INTERN, NULL, "(%p{%s},%s,%p{%d}): %d\n",
             setting, SAFE(setting->name), name, value, *value, rc);
  }
  return rc;
}

int config_setting_lookup_int64_DBG(const config_setting_t *setting,
                                  const char *name, long long *value)
{
  d_assert(setting);
  d_assert(name);
  d_assert(value);
  int rc = config_setting_lookup_int64(setting, name, value);
  if (rc == CONFIG_TRUE)
  {
    d_printf(D_INTERN, NULL, "Setting '%s' item '%s' to %lld (%p,%p,ret=%d)\n",
             SAFE(setting->name), name, *value, setting, value, rc);
  }
  else
  {
    d_printf(D_INTERN, NULL, "(%p{%s},%s,%p{%lld}): %d\n",
             setting, SAFE(setting->name), name, value, *value, rc);
  }
  return rc;
}

#define config_setting_lookup_bool(s,n,v) config_setting_lookup_bool_DBG(s,n,v)
#define config_setting_lookup_int(s,n,v)  config_setting_lookup_int_DBG(s,n,v)
#define config_setting_lookup_int64(s,n,v)  config_setting_lookup_int64_DBG(s,n,v)

#endif


/**
 * @brief Allocate ITS object, Setup thread and associated data structures
 * @param pITS pointer to ITS handle
 * @param pAttr POSIX thread attributes
 * @param pConfigFileName Configuration filename
 * @return Zero for success or an negative errno
 */
int ITSCtrl_Open (struct ITSCtrl *pITS,
                  pthread_attr_t *pAttr,
                  char *pConfigFileName)
{
  d_assert(pITS);
  d_assert(pAttr);
  d_assert(pConfigFileName);

  d_fnstart(D_INTERN, NULL, "(%p,%p,%s)\n",
            pITS, pAttr, pConfigFileName);

  memset(pITS, 0, sizeof(struct ITSCtrl));

  // Load config settings
  int Res = ITSCtrl_LoadConfig(pITS, pConfigFileName);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "(%p,%p,%s): ITSCtrl_LoadConfig() Fail: %d\n",
             pITS, pAttr, pConfigFileName,
             Res);
    goto Error;
  }

  // Assign thread attributes from input param
  pITS->Ctrl.ThreadAttr = *pAttr;

  // Create ITSCtrl thread
  pITS->Ctrl.ThreadState |= ITS_THREAD_STATE_INIT;
  Res = pthread_create(&pITS->Ctrl.ThreadID,
                       &pITS->Ctrl.ThreadAttr,
                       (void *) ITSCtrl_ThreadProc,
                       pITS);
  if (Res != 0)
  {
    d_error(D_ERR, 0, "pthread_create() failed\n");
    // Thread creation error
    pITS->Ctrl.ThreadState = ITS_THREAD_STATE_NONE;
    goto Error;
  }

  // Success!
  Res = 0;
  d_printf(D_INFO, 0, "Successfully started the its-ctrl\n");
  goto Success;

Error:
  d_error(D_ERR, 0, "Error!\n");
  ITSCtrl_Close(pITS);

Success:
  d_fnend(D_INFO, NULL, "()\n");
  return Res;
}

/**
 * @brief Stop execution of ITS, free the thread and its associated resources
 * @param pITS ITS handle
 */
void ITSCtrl_Close (struct ITSCtrl *pITS)
{
  int Res = -ENOSYS;
  d_fnstart(D_INFO, NULL, "()\n");

  // Catch attempt to close invalid object pointer
  if (pITS == NULL)
  {
    Res = -EINVAL;
    goto Error;
  }

  // Signal thread to terminate
  pITS->Ctrl.ThreadState |= ITS_THREAD_STATE_STOP;
  // Wait for thread termination
  if (pITS->Ctrl.ThreadState & ITS_THREAD_STATE_INIT)
    pthread_join(pITS->Ctrl.ThreadID, NULL);

  // Unload config settings
  Res = ITSCtrl_UnloadConfig(pITS);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "(%p): ITSCtrl_UnloadConfig() Fail: %d\n",
             pITS,
             Res);
    goto Error;
  }

  // Success!
  Res = 0;

Error:
  (void)Res;   // value not currently used

  d_fnend(D_INFO, NULL, "()\n");
  return;
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------


/**
 * @brief Read a latitude/longitude
 *
 * @param pLatitude  Where to store the retrieved latitude
 * @param pLongitude Where to store the retrieved longitude
 * @param pAltitude  Where to store the retrieved altitude
 * @param pSetting Section to interogate
 * @param pLatitudeName  Name of the latitude parameter
 * @param pLongitudeName Name of the latitude parameter
 * @param pAltitudeName  Name of the altitude parameter
 */
static void ITSCtrl_ReadLatLong(int32_t * pLatitude,
                                int32_t * pLongitude,
                                int32_t * pAltitude,
                                const config_setting_t *pSetting,
                                const char * pLatitudeName,
                                const char * pLongitudeName,
                                const char * pAltitudeName)
{
  BUILD_BUG_ON(sizeof(int) < sizeof(int32_t));
  d_assert(pLatitude);
  d_assert(pLongitude);
  d_assert(pAltitude);
  d_assert(pSetting);
  d_assert(pLatitudeName);
  d_assert(pLongitudeName);
  d_assert(pAltitudeName);

  d_fnstart(D_INTERN, NULL, "(%p,%p,%p,%p{%s},%s,%s,%s)\n",
            pLatitude, pLongitude, pAltitude,
            pSetting,
            SAFE(pSetting->name),
            SAFE(pLatitudeName), SAFE(pLongitudeName), SAFE(pAltitudeName));

  int ConfigVal = 0;
  // Latitude
  if (config_setting_lookup_int(pSetting,
                                pLatitudeName,
                                &ConfigVal))
  {
    *pLatitude = (int32_t) ConfigVal;
  }
  else
  {
    d_printf(D_WARN, NULL, "Latitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pLatitudeName));
  }

  // Longitude
  if (config_setting_lookup_int(pSetting,
                                pLongitudeName,
                                &ConfigVal))
  {
    *pLongitude = (int32_t) ConfigVal;
  }
  else
  {
    d_printf(D_WARN, NULL, "Longitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pLongitudeName));
  }

  // Altitude (optional)
  if (config_setting_lookup_int(pSetting,
                                pAltitudeName,
                                &ConfigVal))
  {
    *pAltitude = (int32_t) ConfigVal;
  }
  else
  {
    d_printf(D_INFO, NULL, "Altitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pAltitudeName));
  }

  d_fnend(D_INTERN, NULL, "(%p,%p,%p,%p{%s},%s,%s,%s): (%"PRId32",%"PRId32",%"PRId32")\n",
          pLatitude, pLongitude, pAltitude,
          pSetting,
          SAFE(pSetting->name),
          SAFE(pLatitudeName), SAFE(pLongitudeName), SAFE(pAltitudeName),
          *pLatitude, *pLongitude, *pAltitude);
}


/**
 * @brief Read a delta position with optional quality
 *
 * @param pDENMReferencePoint
 * @param pSetting
 * @param pLatitudeName
 * @param pLongitudeName
 * @param pAltitudeName
 * @param pQualityName
 */
static void ITSCtrl_ReadPos(tDENMReferencePoint    * pDENMReferencePoint,
                            const config_setting_t * pSetting,
                            const char * pLatitudeName,
                            const char * pLongitudeName,
                            const char * pAltitudeName,
                            const char * pQualityName)
{
  BUILD_BUG_ON(sizeof(int) < sizeof(int32_t));
  d_assert(pDENMReferencePoint);
  d_assert(pSetting);
  d_assert(pLatitudeName);
  d_assert(pLongitudeName);
  d_assert(pAltitudeName);

  d_fnstart(D_INTERN, NULL, "(%p,%p{%s},%s,%s,%s,%s)\n",
            pDENMReferencePoint,
            pSetting, SAFE(pSetting->name),
            SAFE(pLatitudeName), SAFE(pLongitudeName),
            SAFE(pAltitudeName), SAFE(pQualityName));

  int ConfigVal = 0;
  // Latitude
  if (config_setting_lookup_int(pSetting, pLatitudeName, &ConfigVal))
  {
    pDENMReferencePoint->DeltaLatitude = ((int32_t) ConfigVal);
  }
  else
  {
    d_printf(D_WARN, NULL, "Latitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pLatitudeName));
  }

  // Longitude
  if (config_setting_lookup_int(pSetting, pLongitudeName, &ConfigVal))
  {
    pDENMReferencePoint->DeltaLongitude = ((int32_t) ConfigVal);
  }
  else
  {
    d_printf(D_WARN, NULL, "Longitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pLongitudeName));
  }

  // Altitude
  if (config_setting_lookup_int(pSetting, pAltitudeName, &ConfigVal))
  {
    pDENMReferencePoint->DeltaAltitude = ((int32_t) ConfigVal);
  }
  else
  {
    d_printf(D_INFO, NULL, "Altitude unavail, %p{%s}[%s]\n",
             pSetting, SAFE(pSetting->name), SAFE(pAltitudeName));
  }

  // Quality
  if (pQualityName)
  {
    if (config_setting_lookup_int(pSetting, pQualityName, &ConfigVal))
    {
      pDENMReferencePoint->InformationQuality = ((int8_t) ConfigVal);
    }
    else
    {
      d_printf(D_INFO, NULL, "Quality unavail, %p{%s}[%s]\n",
               pSetting, SAFE(pSetting->name), SAFE(pQualityName));
    }
  }

  d_fnend(D_INTERN, NULL, "(%p,%p{%s},%s,%s,%s,%s) : "
          "{%"PRId32",%"PRId32",%"PRId32",%d}\n",
          pDENMReferencePoint,
          pSetting, SAFE(pSetting->name),
          SAFE(pLatitudeName), SAFE(pLongitudeName),
          SAFE(pAltitudeName), SAFE(pQualityName),
          pDENMReferencePoint->DeltaLatitude,
          pDENMReferencePoint->DeltaLongitude,
          pDENMReferencePoint->DeltaAltitude,
          pDENMReferencePoint->InformationQuality);
}

/**
 * @brief Load ITSCtrl parameters from the config file
 * @param pITS ITS transmitter handle
 * @param pConfigFileName Filename of the config file
 * @return Zero for success or a negative errno
 */
static int ITSCtrl_LoadConfig(struct ITSCtrl *pITS,
                              char *pConfigFileName)
{
  d_assert(pITS);
  d_assert(pConfigFileName);
  int Res = -ENOSYS;
  config_t Config;             // configuration object read from config file
  config_setting_t *pSetting;  // setting for ITSCtrl in config file
  int ConfigVal = 0;

  config_init(&Config); // initialise the config object

  // Try to read the specified config file into the config object
  if (config_read_file(&Config, pConfigFileName) != CONFIG_TRUE)
  {
    d_error(D_ERR, 0, "Could not open %s\n", pConfigFileName);
    // "libconfig: %s at line %d\n", config_error_text (pConfig),
    Res = -EINVAL;
    goto Error;
  }

  // Get the 'ITSCtrl' Setting
  pSetting = config_lookup(&Config, ITS_CONFIG_PATH_NAME);
  if (pSetting == NULL)
  {
    d_error(D_ERR, 0, "config_lookup(%s) failed\n", ITS_CONFIG_PATH_NAME);
    Res = -EINVAL;
    goto Error;
  }

  // config is open, now look for configuration entries

  // CAM

  // Set defaults
  pITS->Tx.CAMEnabled = true;
  pITS->Tx.pRSUCont   = NULL;

  config_setting_t * pCAM = config_setting_get_member(pSetting,
                                                      ITS_CONFIG_VALUE_NAME_CAM);
  if(!pCAM)
  {
    d_printf(D_INFO, NULL, "No %s.%s section in %s\n",
             pSetting->name,
             ITS_CONFIG_VALUE_NAME_CAM,
             pConfigFileName);
  }
  else
  {
    // CAM Enabled
    if (config_setting_lookup_bool(pCAM,
                                   ITS_CONFIG_VALUE_NAME_CAMENABLED,
                                   &ConfigVal))
    {
      pITS->Tx.CAMEnabled = (bool) ConfigVal;
    }

    // RSU tolling
    config_setting_t * pToll = config_setting_get_member(pCAM,
                                                         ITS_CONFIG_VALUE_NAME_CAMRSUTOLLING);
    if (pToll != NULL)
    {
      int Len = config_setting_length(pToll);
      if (Len > 0)
      {
        pITS->Tx.pRSUCont = asn1_mallocz_value(asn1_type_ITSProtectedCommunicationZonesRSU);
        pITS->Tx.pRSUCont->count = Len;
        pITS->Tx.pRSUCont->tab = (ITSProtectedCommunicationZone *)asn1_mallocz(
          sizeof(ITSProtectedCommunicationZone) * pITS->Tx.pRSUCont->count);

        const struct ITSProtectedCommunicationZone Temp =
          {
            .protectedZoneType          = ITSProtectedZoneType_permanentCenDsrcTolling,
            .expiryTime_option          = false,
            .expiryTime                 = {0},
            .protectedZoneLatitude      = ITSLatitude_unavailable,
            .protectedZoneLongitude     = ITSLongitude_unavailable,
            .protectedZoneRadius_option = false,
            .protectedZoneRadius        = 0,
            .protectedZoneID_option     = false,
            .protectedZoneID            = 0,
          };

        int Idx = 0;
        for (; Idx < Len; ++Idx)
        {
          ITSProtectedCommunicationZone  * pTmp = pITS->Tx.pRSUCont->tab + Idx;
          *pTmp = Temp;
          config_setting_t * pElem = config_setting_get_elem(pToll, Idx);

          if (config_setting_lookup_int(pElem,
                                        ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLATITUDE,
                                        &ConfigVal))
          {
            pTmp->protectedZoneLatitude = ConfigVal;
          }
          if (config_setting_lookup_int(pElem,
                                        ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLONGITUDE,
                                        &ConfigVal))
          {
            pTmp->protectedZoneLongitude = ConfigVal;
          }
          if (config_setting_lookup_int(pElem,
                                        ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGRADIUS,
                                        &ConfigVal))
          {
            pTmp->protectedZoneRadius_option = true;
            pTmp->protectedZoneRadius        = ConfigVal;
          }

          if (config_setting_lookup_bool(pElem,
                                         ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGTEMPORARY,
                                         &ConfigVal))
          {
            if ((bool)ConfigVal)
            {
              pTmp->protectedZoneType = ITSProtectedZoneType_temporaryCenDsrcTolling;
            }
          }

          if (config_setting_lookup_int(pElem,
                                        ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGPROTID,
                                        &ConfigVal))
          {
            pTmp->protectedZoneID_option = true;
            pTmp->protectedZoneID        = ConfigVal;
          }
        }
      }
    }

    // Vehicle tolling
    pToll = config_setting_get_member(pCAM, ITS_CONFIG_VALUE_NAME_CAMVEHTOLLING);
    if (pToll != NULL)
    {
      int Len = config_setting_length(pToll);
      if (Len == 1)
      {
        config_setting_t * pElem = config_setting_get_elem(pToll, 0);

        pITS->Tx.pVehCont = asn1_mallocz_value(asn1_type_ITSCenDsrcTollingZone);

        if (config_setting_lookup_int(pElem,
                                      ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLATITUDE,
                                      &ConfigVal))
        {
          pITS->Tx.pVehCont->protectedZoneLatitude = ConfigVal;
        }
        if (config_setting_lookup_int(pElem,
                                      ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLONGITUDE,
                                      &ConfigVal))
        {
          pITS->Tx.pVehCont->protectedZoneLongitude = ConfigVal;
        }
        if (config_setting_lookup_int(pElem,
                                      ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGPROTID,
                                      &ConfigVal))
        {
          pITS->Tx.pVehCont->cenDsrcTollingZoneID_option = true;
          pITS->Tx.pVehCont->cenDsrcTollingZoneID        = ConfigVal;
        }
      }
    }
  }

  // DENM

  // Set defaults
  pITS->Tx.RWW.Enabled       = false;
  pITS->Tx.RWW2.Enabled      = false;
  pITS->Tx.RWW3.Enabled      = false;
  pITS->Tx.RWW4.Enabled      = false;
  pITS->Tx.EVW.Enabled       = false;
  pITS->Tx.UseRefDENMEnabled = false;

  config_setting_t * pDENM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_DENM);
  if (!pDENM)
  {
    d_printf(D_INFO, NULL, "No %s.%s section in %s\n",
             pSetting->name,
             ITS_CONFIG_VALUE_NAME_DENM,
             pConfigFileName);
  }
  else
  {
    bool DENMTxEnabled = true;

    if (config_setting_lookup_bool(pDENM,
                                   ITS_CONFIG_VALUE_NAME_DENMENABLED,
                                   &ConfigVal))
    {
      DENMTxEnabled = ConfigVal;

      // Top-level DENM enabler
      if (DENMTxEnabled)
      {
        if (config_setting_lookup_bool(pDENM,
                                       ITS_CONFIG_VALUE_NAME_DENMUSEREFS,
                                       &ConfigVal))
        {
          pITS->Tx.UseRefDENMEnabled = (bool) ConfigVal;
        }

        // Event1
        config_setting_t * pEventConfig = config_setting_get_member(
          pDENM, ITS_CONFIG_VALUE_NAME_DENMEVENT1);
        if (pEventConfig)
        {
          Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW, pEventConfig);
          if (Res)
          {
            d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
            goto Error;
          }
        }
        else
        {
          // RWW
          config_setting_t * pRWWConfig = config_setting_get_member(
            pDENM, ITS_CONFIG_VALUE_NAME_DENMRWW);

          if (pRWWConfig)
          {
            // RWW
            Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW, pRWWConfig);
            if (Res)
            {
              d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
              goto Error;
            }
          }
          else
          {
            d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
                     pDENM->name, ITS_CONFIG_VALUE_NAME_DENMEVENT1);
          }
        }

        // Event2
        pEventConfig = config_setting_get_member(
          pDENM, ITS_CONFIG_VALUE_NAME_DENMEVENT2);
        if (pEventConfig)
        {
          Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW2, pEventConfig);
          if (Res)
          {
            d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
            goto Error;
          }
        }
        else
        {
          // RWW2
          config_setting_t * pRWWConfig = config_setting_get_member(
            pDENM, ITS_CONFIG_VALUE_NAME_DENMRWW2);

          if (pRWWConfig)
          {
            // RWW2
            Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW2, pRWWConfig);
            if (Res)
            {
              d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
              goto Error;
            }
          }
          else
          {
            d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
                     pDENM->name, ITS_CONFIG_VALUE_NAME_DENMEVENT2);
          }
        }

        // Event3
        pEventConfig = config_setting_get_member(
          pDENM, ITS_CONFIG_VALUE_NAME_DENMEVENT3);
        if (pEventConfig)
        {
          Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW3, pEventConfig);
          if (Res)
          {
            d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
            goto Error;
          }
        }
        else
        {
          // RWW3
          config_setting_t * pRWWConfig = config_setting_get_member(
            pDENM, ITS_CONFIG_VALUE_NAME_DENMRWW3);

          if (pRWWConfig)
          {
            // RWW3
            Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW3, pRWWConfig);
            if (Res)
            {
              d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
              goto Error;
            }
          }
          else
          {
            d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
                     pDENM->name, ITS_CONFIG_VALUE_NAME_DENMEVENT3);
          }
        }

        // Event4
        pEventConfig = config_setting_get_member(
          pDENM, ITS_CONFIG_VALUE_NAME_DENMEVENT4);
        if (pEventConfig)
        {
          Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW4, pEventConfig);
          if (Res)
          {
            d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
            goto Error;
          }
        }
        else
        {
          // RWW4
          config_setting_t * pRWWConfig = config_setting_get_member(
            pDENM, ITS_CONFIG_VALUE_NAME_DENMRWW4);

          if (pRWWConfig)
          {
            // RWW4
            Res = ITSCtrl_LoadRWWConfig(&pITS->Tx.RWW4, pRWWConfig);
            if (Res)
            {
              d_fnend(D_ERR, NULL, "ITSCtrl_LoadRWWConfig(): %d\n", Res);
              goto Error;
            }
          }
          else
          {
            d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
                     pDENM->name, ITS_CONFIG_VALUE_NAME_DENMEVENT4);
          }
        }

        // EEBL
        Res = ITSCtrl_LoadEEBLConfig(pITS, pDENM);
        if (Res)
        {
          d_fnend(D_ERR, NULL, "ITSCtrl_LoadEEBLConfig(): %d\n", Res);
          goto Error;
        }

        // EVW
        Res = ITSCtrl_LoadEVWConfig(pITS, pDENM);
        if (Res)
        {
          d_fnend(D_ERR, NULL, "ITSCtrl_LoadEVWConfig(): %d\n", Res);
          goto Error;
        }
      }
      else
      {
        d_printf(D_INFO, NULL, "ITSCtrl_LoadConfig(): DENM disabled\n");
      }
    }
  }

  // SPAT
  ITSCtrl_LoadSpatConfig(pITS, pSetting);

  // MAP
  ITSCtrl_LoadMapConfig(pITS, pSetting);

  // SRM
  ITSCtrl_LoadSRMConfig(pITS, pSetting);

  // SSM
  ITSCtrl_LoadSSMConfig(pITS, pSetting);

  // SA
  ITSCtrl_LoadSAConfig(pITS, pSetting);

  // RTCM
  ITSCtrl_LoadRTCMConfig(pITS, pSetting);

  // CPM
  ITSCtrl_LoadCPMConfig(pITS, pSetting);

  // VAM
  ITSCtrl_LoadVAMConfig(pITS, pSetting);

  // IMZM
  ITSCtrl_LoadIMZMConfig(pITS, pSetting);

  // IVI
  config_setting_t * pIVI = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_IVI);
  if (!pIVI)
  {
    d_printf(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name, ITS_CONFIG_VALUE_NAME_IVI);
  }
  else
  {
    ITSCtrl_LoadIviConfig(pITS, pIVI);

    // IVS
    config_setting_t * pIVSConfig = config_setting_get_member(
      pIVI, ITS_CONFIG_VALUE_NAME_IVI_IVS);
    if (!pIVSConfig)
    {
      d_printf(D_WARN, NULL, "'%s' has no '%s' section\n",
               pIVI->name, ITS_CONFIG_VALUE_NAME_IVI_IVS);
    }
    else
    {
      // IVS
      Res = ITSCtrl_LoadIVSConfig(&pITS->Tx.IVS, pIVSConfig);
      if (Res)
      {
        d_fnend(D_ERR, NULL, "ITSCtrl_LoadIVSConfig(): %d\n", Res);
        goto Error;
      }
    }

    // IVS2
    pIVSConfig = config_setting_get_member(
      pIVI, ITS_CONFIG_VALUE_NAME_IVI_IVS2);
    if (!pIVSConfig)
    {
      d_printf(D_WARN, NULL, "'%s' has no '%s' section\n",
               pIVI->name, ITS_CONFIG_VALUE_NAME_IVI_IVS2);
    }
    else
    {
      // IVS
      Res = ITSCtrl_LoadIVSConfig(&pITS->Tx.IVS2, pIVSConfig);
      if (Res)
      {
        d_fnend(D_ERR, NULL, "ITSCtrl_LoadIVSConfig(): %d\n", Res);
        goto Error;
      }
    }
  }


  // Success!
  Res = 0;

  d_fnend(D_INFO, NULL, "(%p,%s):%s%s%s%s%s%s%s%s\n",
          pITS,
          SAFE(pConfigFileName),
          pITS->Tx.RWW.Enabled  ? " RWW"  : "",
          pITS->Tx.EVW.Enabled  ? " EVW"  : "",
          pITS->Tx.SPAT.Enabled ? " SPAT" : "",
          pITS->Tx.MAP.Enabled  ? " MAP"  : "",
          pITS->Tx.SRM.Enabled  ? " SRM"  : "",
          pITS->Tx.SSM.Enabled  ? " SSM"  : "",
          pITS->Tx.IVI.Enabled  ? " IVI"  : "",
          pITS->Tx.CAMEnabled   ? " CAM"  : "");

Error:
  // Update complete - close the configuration
  config_destroy(&Config);

  return Res;
}

/**
 * @brief Load the RWW-specific sections of the config file
 *
 * @param pITS Config structure to initialise
 * @param pSetting libconfig settings to use
 */
static int ITSCtrl_LoadRWWConfig(tITSTxRWWParams *pRWW,
                                 config_setting_t *pSetting)
{
  d_assert(pRWW);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pRWW, pSetting);

  memset(pRWW, 0, sizeof(tITSTxRWWParams));

  // Ensure subsequent DENM structures have unique default SeqNum values
  static int SeqExtra = 0;

  pRWW->Enabled             = false;
  pRWW->Duration            = ITS_CONFIG_VALUE_DEFAULT_DURATION;
  pRWW->OrigStationId       = ITS_CONFIG_VALUE_DEFAULT_ORIGSTATIONID;
  pRWW->SeqNumber           = ITS_CONFIG_VALUE_DEFAULT_SEQNUMBER+SeqExtra;
  pRWW->UpdatePeriod        = ITS_CONFIG_VALUE_DEFAULT_UPDATEPERIOD;
  pRWW->RepInterval         = ITS_CONFIG_VALUE_DEFAULT_REPINTERVAL;
  pRWW->EventOffsetAbsolute = ITS_CONFIG_VALUE_DEFAULT_EVENTOFFSETABSOLUTE;
  pRWW->RelativeOffsetCumulative = ITS_CONFIG_VALUE_DEFAULT_RELATIVEOFFSETCUMULATIVE;
  pRWW->EventPositionSource = ITS_CONFIG_VALUE_DEFAULT_EVENTPOSITIONSOURCE;
  pRWW->EventLatitude       = ITS_CONFIG_VALUE_DEFAULT_EVENTLAT;
  pRWW->EventLongitude      = ITS_CONFIG_VALUE_DEFAULT_EVENTLONG;
  pRWW->EventAltitude       = ITS_CONFIG_VALUE_DEFAULT_EVENTALT;
  pRWW->TrafficClass        = ITS_CONFIG_VALUE_DEFAULT_TRAFFICCLASS;
  pRWW->InformationQuality  = ITS_CONFIG_VALUE_DEFAULT_INFORMATIONQUALITY;
  pRWW->CauseCode           = ITS_CONFIG_VALUE_DEFAULT_CAUSECODE;
  pRWW->SubCauseCode        = ITS_CONFIG_VALUE_DEFAULT_SUBCAUSECODE;
  pRWW->RelevanceTrafficDirection = ITS_CONFIG_VALUE_DEFAULT_TRAFFICDIRECTION;
  pRWW->RelevanceDistance   = ITS_CONFIG_VALUE_DEFAULT_RELEVANCEDIST;
  pRWW->EventHeading        = ITS_CONFIG_VALUE_DEFAULT_EVENTHEADING;

  // optional items not present by default
  pRWW->ClosedLanesOption = false;
  pRWW->SpeedLimitOption = false;
  pRWW->StartingPointSpeedLimitOption = false;
  pRWW->LanePositionOption = false;
  pRWW->TrafficFlowRuleOption = false;
  pRWW->EventHeadingOption = 0;

  // traces
  pRWW->TraceUpdateDistance_m = ITS_CONFIG_VALUE_DEFAULT_TRACEUPDATEDISTANCE_M;

  // These are optional, use illegal values
  pRWW->OuterHardShoulderStatus = ITSHardShoulderStatus_Limit_Max+1;
  pRWW->InnerHardShoulderStatus = ITSHardShoulderStatus_Limit_Max+1;

  pRWW->NumClosedLanes = 0;

  int ConfigVal = 0;
  // RWW DENM Enabled
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_DENMRWWTXENABLED,
                                 &ConfigVal))
    pRWW->Enabled = (bool) ConfigVal;

  // Duration
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DURATION,
                                &ConfigVal))
    pRWW->Duration = (uint16_t) ConfigVal;

  // OrigStationId
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMORIGSTATIONID,
                                &ConfigVal))
    pRWW->OrigStationId = (uint32_t) ConfigVal;

  // SeqNumber
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMSEQNUMBER,
                                &ConfigVal))
    pRWW->SeqNumber = (uint16_t) ConfigVal;

  // UpdatePeriod
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_UPDATEPERIOD,
                                &ConfigVal))
    pRWW->UpdatePeriod = (uint16_t) ConfigVal;

  // RepInterval
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_REPINTERVAL,
                                &ConfigVal))
    pRWW->RepInterval = (uint16_t) ConfigVal;
  // RelativeOffsetCumulative
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_RELATIVEOFFSETCUMULATIVE,
                                &ConfigVal))
    pRWW->RelativeOffsetCumulative = (uint8_t) ConfigVal;
  // EventOffsetAbsolute
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_EVENTOFFSETABSOLUTE,
                                &ConfigVal))
    pRWW->EventOffsetAbsolute = (uint8_t) ConfigVal;
  // EventPositionSource
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_EVENTPOSSOURCE,
                                &ConfigVal))
    pRWW->EventPositionSource = (uint16_t) ConfigVal;


  // read position from the configuration file only if config source specified
  if (pRWW->EventPositionSource == ITS_CONFIG_VALUE_EVENTPOSITION_CONFIG)
  {
    ITSCtrl_ReadLatLong(&pRWW->EventLatitude,
                        &pRWW->EventLongitude,
                        &pRWW->EventAltitude,
                        pSetting,
                        ITS_CONFIG_VALUE_NAME_EVENTLAT,
                        ITS_CONFIG_VALUE_NAME_EVENTLONG,
                        ITS_CONFIG_VALUE_NAME_EVENTALT);
  }
  else
  {
    // There is no event position so tag with NAN to ensure we don't actually use it
    pRWW->EventLatitude  =
      pRWW->EventLongitude =
      pRWW->EventAltitude  = (UINT32_C(1) << 31);
  }

  // TrafficClass
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_TRAFFICCLASS,
                                &ConfigVal))
    pRWW->TrafficClass = (uint8_t) ConfigVal;

  // InformationQuality
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWINFORMATIONQUALITY,
                                &ConfigVal))
    pRWW->InformationQuality = (uint8_t) ConfigVal;

  // CauseCode
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWCAUSECODE,
                                &ConfigVal))
    pRWW->CauseCode = (uint8_t) ConfigVal;

  // SubCauseCode
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWSUBCAUSECODE,
                                &ConfigVal))
    pRWW->SubCauseCode = (uint8_t) ConfigVal;

  // RelevanceTrafficDirection
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWRELEVANCETRAFFICDIRECTION,
                                &ConfigVal))
    pRWW->RelevanceTrafficDirection = (uint8_t) ConfigVal;

  // RelevanceDistance
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWRELEVANCEDIST,
                                &ConfigVal))
    pRWW->RelevanceDistance = (uint8_t) ConfigVal;

  // EventHeadingOption
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHEADINGOPTION,
                                &ConfigVal))
    pRWW->EventHeadingOption = (uint8_t) ConfigVal;

  // EventHeading
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHEADING,
                                &ConfigVal))
    pRWW->EventHeading = (uint16_t) ConfigVal;

  // ClosedLanesOption
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_DENMRWWCLOSEDLANESOPTION,
                                 &ConfigVal))
    pRWW->ClosedLanesOption = (bool) ConfigVal;

  // ClosedLanes
  config_setting_t * pClosedLanes = config_setting_get_member
    (pSetting, ITS_CONFIG_VALUE_NAME_DENMRWWCLOSEDLANES);
  if (pClosedLanes)
  {
    int NumberOfLanes = config_setting_length(pClosedLanes);
    if (NumberOfLanes > 0)
    {
      pRWW->NumClosedLanes = NumberOfLanes;
      pRWW->ClosedLanes = (int *)calloc(sizeof(int), NumberOfLanes);
      if (!pRWW->ClosedLanes)
      {
        d_printf(D_ERR, NULL,
                 "Unable to calloc %d ClosedLanes\n", NumberOfLanes);
        return -ENOMEM;
      }
      int i;
      for(i = 0; i < NumberOfLanes; i++)
      {
        ConfigVal = config_setting_get_int_elem(pClosedLanes, i);
        if ((ConfigVal != 1) && (ConfigVal != 0))
        {
          d_printf(D_ERR, NULL,
                   "ClosedLanes can only be specified with 0 and 1, not %d - Fail\n", ConfigVal);
          return -EINVAL;
        }
        pRWW->ClosedLanes[i] = ConfigVal;
      }
    }
  }

  // SpeedLimitOption
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_DENMRWWSPEEDLIMITOPTION,
                                 &ConfigVal))
    pRWW->SpeedLimitOption = (bool) ConfigVal;
  // SpeedLimit
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWSPEEDLIMIT,
                                &ConfigVal))
    pRWW->SpeedLimit = (uint8_t) ConfigVal;

  // StartingPointSpeedLimitOption
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_DENMRWWSTARTINGPOINTSPEEDLIMITOPTION,
                                 &ConfigVal))
    pRWW->StartingPointSpeedLimitOption = (bool) ConfigVal;

  // StartingPointSpeedLimit
  {
    config_setting_t *pStartingPointSpeedLimitPoints =
      config_setting_get_member(
        pSetting, ITS_CONFIG_VALUE_NAME_DENMRWWSTARTINGPOINTSPEEDLIMIT);
    if (pStartingPointSpeedLimitPoints != NULL)
    {
      int NumberOfSpeedLimitPoints =
        config_setting_length(pStartingPointSpeedLimitPoints);

      //There can only be 1 StartingPointSpeedLimit
      if (NumberOfSpeedLimitPoints != 1)
      {
        d_printf(D_ERR, NULL,
                 "StartingPointSpeedLimit point must specifiy exactly"
                 " 1 point. %d provided\n",
                 NumberOfSpeedLimitPoints);
        return -EINVAL;
      }


      config_setting_t *pStartingPointSpeedLimit =
        config_setting_get_elem(pStartingPointSpeedLimitPoints, 0);

      if (pStartingPointSpeedLimit != NULL)
      {
        ITSCtrl_ReadPos(&pRWW->StartingPointSpeedLimit,
                        pStartingPointSpeedLimit,
                        ITS_CONFIG_VALUE_NAME_DENMRWWLATITUDE,
                        ITS_CONFIG_VALUE_NAME_DENMRWWLONGITUDE,
                        ITS_CONFIG_VALUE_NAME_DENMRWWALTITUDE,
                        NULL);
      }
    }
  }

  // TrafficFlowRuleOption
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_DENMRWWTRAFFICFLOWRULEOPTION,
                                 &ConfigVal))
    pRWW->TrafficFlowRuleOption = (bool) ConfigVal;

  // TrafficFlowRule
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWTRAFFICFLOWRULE,
                                &ConfigVal))
    pRWW->TrafficFlowRule = (uint8_t) ConfigVal;

  // LanePositionOption
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_LANEPOSITIONOPTION,
                                 &ConfigVal))
    pRWW->LanePositionOption = (bool) ConfigVal;

  // LanePosition
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_LANEPOSITION,
                                &ConfigVal))
    pRWW->LanePosition = (uint8_t) ConfigVal;

  // OuterHardShoulderStatus
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWOUTERHARDSHOULDERSTATUS,
                                &ConfigVal))
    pRWW->OuterHardShoulderStatus = (uint8_t) ConfigVal;

  // InnerHardShoulderStatus
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_DENMRWWINNERHARDSHOULDERSTATUS,
                                &ConfigVal))
    pRWW->InnerHardShoulderStatus = (uint8_t) ConfigVal;

  // Event History - Defines the RWW segments
  {
    config_setting_t * pEventPoints = config_setting_get_member(
      pSetting, ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHISTORY);
    if (pEventPoints != NULL)
    {
      int NumberOfEventPoints = config_setting_length(pEventPoints);
      pRWW->NumEventPoints = NumberOfEventPoints;
      if (NumberOfEventPoints > 0)
      {
        pRWW->pEventPoints = (tDENMReferencePoint *)calloc(sizeof(tDENMReferencePoint),
                                                           NumberOfEventPoints);
        if (!pRWW->pEventPoints)
        {
          d_printf(D_ERR, NULL,
                   "Unable to calloc %d EventPoints\n", NumberOfEventPoints);
          return -ENOMEM;
        }
        int i;
        for (i = 0; i < NumberOfEventPoints; i++)
        {
          config_setting_t *pEventPoint = config_setting_get_elem(pEventPoints, i);
          if (pEventPoint != NULL)
          {
            ITSCtrl_ReadPos(&pRWW->pEventPoints[i],
                            pEventPoint,
                            ITS_CONFIG_VALUE_NAME_DENMRWWLATITUDE,
                            ITS_CONFIG_VALUE_NAME_DENMRWWLONGITUDE,
                            ITS_CONFIG_VALUE_NAME_DENMRWWALTITUDE,
                            ITS_CONFIG_VALUE_NAME_DENMRWWINFORMATIONQUALITY);
          }
        }
      }
    }
  } // Traces
  // Traces
  {

    // Trace update distance for mobile RWW
    if (config_setting_lookup_int(pSetting,
                                  ITS_CONFIG_VALUE_NAME_DENMRWWTRACEUPDATEDISTANCE,
                                  &ConfigVal))
      pRWW->TraceUpdateDistance_m = (int16_t) ConfigVal;

    config_setting_t * pTraces = config_setting_get_member(
      pSetting, ITS_CONFIG_VALUE_NAME_DENMRWWTRACES);
    if (pTraces != NULL)
    {
      int NumberOfTraces = config_setting_length(pTraces);
      if (NumberOfTraces > 0)
      {
        pRWW->NumTraces = NumberOfTraces;
        pRWW->pTraces = (tDENMReferencePoint *)calloc(sizeof(tDENMReferencePoint),
                                                                   NumberOfTraces);
        if (!pRWW->pTraces)
        {
          d_printf(D_ERR, NULL,
                   "Unable to calloc %d tDENMReferencePoint\n", NumberOfTraces);
          return -ENOMEM;
        }

        int i;
        for (i = 0; i < NumberOfTraces; i++)
        {
          config_setting_t *pTrace = config_setting_get_elem(pTraces, i);
          if (pTrace != NULL)
          {
            // Latitude & Longitude
            ITSCtrl_ReadPos(&pRWW->pTraces[i],
                            pTrace,
                            ITS_CONFIG_VALUE_NAME_DENMRWWLATITUDE,
                            ITS_CONFIG_VALUE_NAME_DENMRWWLONGITUDE,
                            ITS_CONFIG_VALUE_NAME_DENMRWWALTITUDE,
                            NULL);
          }
        }
      }
    }
  }
  d_fnend(D_INTERN, NULL, "(%p,%p)\n", pRWW, pSetting);
  SeqExtra++;
  return 0;
}

/**
 * @brief Load the EEBL-specific sections of the config file
 *
 * @param pITS Config structure to initialise
 * @param pSetting libconfig settings to use
 */
static int ITSCtrl_LoadEEBLConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  memset(&pITS->Tx.EEBL, 0, sizeof(pITS->Tx.EEBL));

  pITS->Tx.EEBL.Enabled = false;

  // EEBL
  const config_setting_t * pEEBL = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_DENMEEBL);
  if (!pEEBL)
  {
    d_fnend(D_NOTICE, NULL, "'%s' has no '%s' section\n",
            pSetting->name, ITS_CONFIG_VALUE_NAME_DENMEEBL);
    return 0;
  }

  int ConfigVal = 0;
  // EEBL DENM Enabled
  if (config_setting_lookup_bool(pEEBL,
                                 ITS_CONFIG_VALUE_NAME_DENMEEBLENABLED,
                                 &ConfigVal))
    pITS->Tx.EEBL.Enabled = (bool) ConfigVal;

  d_fnend(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);
  return 0;
}

/**
 * @brief Load the EVW-specific sections of the config file
 *
 * @param pITS Config structure to initialise
 * @param pSetting libconfig settings to use
 */
static int ITSCtrl_LoadEVWConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  memset(&pITS->Tx.EVW, 0, sizeof(pITS->Tx.EVW));

  pITS->Tx.EVW.Duration = ITS_CONFIG_VALUE_DEFAULT_EVWDURATION;
  pITS->Tx.EVW.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_EVWAPPLINTERVAL;

  // EVW
  const config_setting_t * pEVW = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_DENMEVW);
  if (!pEVW)
  {
    d_fnend(D_NOTICE, NULL, "'%s' has no '%s' section\n",
            pSetting->name, ITS_CONFIG_VALUE_NAME_DENMEVW);
    return 0;
  }

  int ConfigVal = 0;
  // EVW DENM Enabled
  if (config_setting_lookup_bool(pEVW,
                                 ITS_CONFIG_VALUE_NAME_DENMEVWENABLED,
                                 &ConfigVal))
    pITS->Tx.EVW.Enabled = (bool) ConfigVal;

  // Duration
  if (config_setting_lookup_int(pEVW,
                                ITS_CONFIG_VALUE_NAME_DURATION,
                                &ConfigVal))
    pITS->Tx.EVW.Duration = (uint16_t) ConfigVal;

  // EVW DENM ApplInterval
  if (config_setting_lookup_int(pEVW,
                                ITS_CONFIG_VALUE_NAME_DENMEVWAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.EVW.ApplInterval = (uint16_t) ConfigVal;

  d_fnend(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);
  return 0;
}


static void ITSCtrl_LoadMapConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.MAP.Enabled = false;
  pITS->Tx.MAP.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_MAPAPPLINTERVAL;
  pITS->Tx.MAP.IntersectionId = ITS_CONFIG_VALUE_DEFAULT_MAPINTERSECTIONID;
  pITS->Tx.MAP.Latitude = ITS_CONFIG_VALUE_DEFAULT_MAPLATITUDE;
  pITS->Tx.MAP.Longitude = ITS_CONFIG_VALUE_DEFAULT_MAPLONGITUDE;
  pITS->Tx.MAP.Altitude_cm = ITS_CONFIG_VALUE_DEFAULT_MAPALTITUDE;
  pITS->Tx.MAP.NumLanes = 0;
  pITS->Tx.MAP.pLanes = NULL;

  config_setting_t *pMAP = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_MAP);
  if (!pMAP)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_MAP);
    return;
  }

  // MAP Enabled
  if (config_setting_lookup_bool(pMAP,
                                 ITS_CONFIG_VALUE_NAME_MAPENABLED,
                                 &ConfigVal))
    pITS->Tx.MAP.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "MAP.Enabled = %d\n", pITS->Tx.MAP.Enabled);

  // Duration
  if (config_setting_lookup_int(pMAP,
                                ITS_CONFIG_VALUE_NAME_MAPAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.MAP.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "MAP.ApplInterval = %d\n", pITS->Tx.MAP.ApplInterval);

  // Intersection ID
  if (config_setting_lookup_int(pMAP,
                                ITS_CONFIG_VALUE_NAME_MAPINTERSECTIONID,
                                &ConfigVal))
    pITS->Tx.MAP.IntersectionId = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "MAP.IntersectionId = 0x%x\n", pITS->Tx.MAP.IntersectionId);

  // Latitude & Longitude
  ITSCtrl_ReadLatLong(&pITS->Tx.MAP.Latitude,
                      &pITS->Tx.MAP.Longitude,
                      &pITS->Tx.MAP.Altitude_cm,
                      pMAP,
                      ITS_CONFIG_VALUE_NAME_MAPLATITUDE,
                      ITS_CONFIG_VALUE_NAME_MAPLONGITUDE,
                      ITS_CONFIG_VALUE_NAME_MAPALTITUDE);
  d_printf(D_DEBUG, 0, "MAP.Latitude = %d\n", pITS->Tx.MAP.Latitude);
  d_printf(D_DEBUG, 0, "MAP.Longitude = %d\n", pITS->Tx.MAP.Longitude);
  d_printf(D_DEBUG, 0, "MAP.Altitude = %d\n", pITS->Tx.MAP.Altitude_cm);

  // Construct intersection lanes
  config_setting_t *pLanes;
  pLanes = config_setting_get_member(pMAP, ITS_CONFIG_VALUE_NAME_MAPLANES);
  if (pLanes != NULL)
  {
    int NumberOfLanes = config_setting_length(pLanes);
    pITS->Tx.MAP.NumLanes = NumberOfLanes;
    d_printf(D_DEBUG, 0, "MAP.NumLanes = %d\n", pITS->Tx.MAP.NumLanes);

    if (NumberOfLanes > 0)
    {
      pITS->Tx.MAP.pLanes = (tMAPLaneParams *)
        calloc(sizeof(tMAPLaneParams), NumberOfLanes);
      if (pITS->Tx.MAP.pLanes != NULL)
      {
        int i;
        for (i = 0; i < NumberOfLanes; i++)
        {
          config_setting_t *pLane = config_setting_get_elem(pLanes, i);
          pITS->Tx.MAP.pLanes[i].LaneId = ITS_CONFIG_VALUE_DEFAULT_MAPLANEID;
          pITS->Tx.MAP.pLanes[i].NumNodes = 0;
          pITS->Tx.MAP.pLanes[i].NumConnections = 0;
          pITS->Tx.MAP.pLanes[i].egressLane = false;
          pITS->Tx.MAP.pLanes[i].ingressLane = true; // as this what was previously set before egressLane/ingressLane config added
          pITS->Tx.MAP.pLanes[i].pNodes = NULL;
          pITS->Tx.MAP.pLanes[i].pConnections = NULL;

          if (pLane != NULL)
          {
            if (config_setting_lookup_int(pLane,
                                          ITS_CONFIG_VALUE_NAME_MAPLANEID,
                                          &ConfigVal))
              pITS->Tx.MAP.pLanes[i].LaneId =  (int) ConfigVal;
            d_printf(D_DEBUG, 0, "MAP.pLanes[%d].LaneId = %d\n",
                     i, pITS->Tx.MAP.pLanes[i].LaneId);

            if (config_setting_lookup_int(pLane,
                                          ITS_CONFIG_VALUE_NAME_MAPLANEDIRECTION,
                                          &ConfigVal))
            {
              if (((int) ConfigVal) & 0x01)
                pITS->Tx.MAP.pLanes[i].egressLane = true;
              else
                pITS->Tx.MAP.pLanes[i].egressLane = false;
              if (((int) ConfigVal) & 0x02)
                pITS->Tx.MAP.pLanes[i].ingressLane = true;
              else
                pITS->Tx.MAP.pLanes[i].ingressLane = false;
            }

            // Construct lane nodes:
            config_setting_t *pNodes;
            pNodes = config_setting_get_member(pLane, ITS_CONFIG_VALUE_NAME_MAPNODES);
            if (pNodes != NULL)
            {
              int NumberOfNodes = config_setting_length(pNodes);
              pITS->Tx.MAP.pLanes[i].NumNodes = NumberOfNodes;
              d_printf(D_DEBUG, 0, "MAP.pLanes[%d].NumNodes = %d (delta cm position)\n",
                       i, pITS->Tx.MAP.pLanes[i].NumNodes);
              if (NumberOfNodes > 0)
              {
                pITS->Tx.MAP.pLanes[i].AbsolutePosNodes = false;
                pITS->Tx.MAP.pLanes[i].pNodes = (tMAPLaneNodeParams *)
                  calloc(sizeof(tMAPLaneNodeParams), NumberOfNodes);
                if (pITS->Tx.MAP.pLanes[i].pNodes != NULL)
                {
                  int j;
                  for (j = 0; j < NumberOfNodes; j++)
                  {
                    config_setting_t *pNode = config_setting_get_elem(pNodes, j);
                    pITS->Tx.MAP.pLanes[i].pNodes[j].X =
                      ITS_CONFIG_VALUE_DEFAULT_MAPNODEX;
                    pITS->Tx.MAP.pLanes[i].pNodes[j].Y =
                      ITS_CONFIG_VALUE_DEFAULT_MAPNODEY;

                    if (pNode != NULL)
                    {
                      if (config_setting_lookup_int(pNode,
                                                    ITS_CONFIG_VALUE_NAME_MAPNODEX,
                                                    &ConfigVal))
                        pITS->Tx.MAP.pLanes[i].pNodes[j].X =  (int) ConfigVal;
                      d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pNodes[%d].X = %d\n",
                               i, j, pITS->Tx.MAP.pLanes[i].pNodes[j].X);

                      if (config_setting_lookup_int(pNode,
                                                    ITS_CONFIG_VALUE_NAME_MAPNODEY,
                                                    &ConfigVal))
                        pITS->Tx.MAP.pLanes[i].pNodes[j].Y =  (int) ConfigVal;
                      d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pNodes[%d].Y = %d\n",
                               i, j, pITS->Tx.MAP.pLanes[i].pNodes[j].Y);
                    }
                  }
                }
              }
            }
            else
            {
              pNodes = config_setting_get_member(pLane, ITS_CONFIG_VALUE_NAME_MAPABSOLUTENODES);
              if (pNodes != NULL)
              {
                int NumberOfNodes = config_setting_length(pNodes);
                pITS->Tx.MAP.pLanes[i].NumNodes = NumberOfNodes;
                d_printf(D_DEBUG, 0, "MAP.pLanes[%d].NumNodes = %d (absolute position)\n",
                         i, pITS->Tx.MAP.pLanes[i].NumNodes);
                if (NumberOfNodes > 0)
                {
                  pITS->Tx.MAP.pLanes[i].AbsolutePosNodes = true;
                  pITS->Tx.MAP.pLanes[i].pNodes = (tMAPLaneNodeParams *)
                    calloc(sizeof(tMAPLaneNodeParams), NumberOfNodes);
                  if (pITS->Tx.MAP.pLanes[i].pNodes != NULL)
                  {
                    int j;
                    for (j = 0; j < NumberOfNodes; j++)
                    {
                      config_setting_t *pNode = config_setting_get_elem(pNodes, j);
                      pITS->Tx.MAP.pLanes[i].pNodes[j].X =
                        ITS_CONFIG_VALUE_DEFAULT_MAPNODEX;
                      pITS->Tx.MAP.pLanes[i].pNodes[j].Y =
                        ITS_CONFIG_VALUE_DEFAULT_MAPNODEY;

                      if (pNode != NULL)
                      {
                        if (config_setting_lookup_int(pNode,
                                                      ITS_CONFIG_VALUE_NAME_MAPNODELON,
                                                      &ConfigVal))
                          pITS->Tx.MAP.pLanes[i].pNodes[j].X =  (int) ConfigVal;
                        d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pNodes[%d].X = %d\n",
                                 i, j, pITS->Tx.MAP.pLanes[i].pNodes[j].X);

                        if (config_setting_lookup_int(pNode,
                                                      ITS_CONFIG_VALUE_NAME_MAPNODELAT,
                                                      &ConfigVal))
                          pITS->Tx.MAP.pLanes[i].pNodes[j].Y =  (int) ConfigVal;
                        d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pNodes[%d].Y = %d\n",
                                 i, j, pITS->Tx.MAP.pLanes[i].pNodes[j].Y);
                      }
                    }
                  }
                }
              }
            }


            // Construct lane connections:
            config_setting_t *pConnections;
            pConnections = config_setting_get_member(pLane, ITS_CONFIG_VALUE_NAME_MAPCONNECTIONS);
            if (pConnections != NULL)
            {
              int NumberOfConnections = config_setting_length(pConnections);
              pITS->Tx.MAP.pLanes[i].NumConnections = NumberOfConnections;
              d_printf(D_DEBUG, 0, "MAP.pLanes[%d].NumConnections = %d\n",
                       i, pITS->Tx.MAP.pLanes[i].NumConnections);
              if (NumberOfConnections > 0)
              {
                pITS->Tx.MAP.pLanes[i].pConnections =(tMAPLaneConnectionParams *)
                  calloc(sizeof(tMAPLaneConnectionParams), NumberOfConnections);
                if (pITS->Tx.MAP.pLanes[i].pConnections != NULL)
                {
                  int j;
                  for (j = 0; j < NumberOfConnections; j++)
                  {
                    config_setting_t *pConnection = config_setting_get_elem(pConnections, j);
                    pITS->Tx.MAP.pLanes[i].pConnections[j].SignalGroup =
                      ITS_CONFIG_VALUE_DEFAULT_MAPSIGNALGROUP;
                    pITS->Tx.MAP.pLanes[i].pConnections[j].ConnectsTo =
                      ITS_CONFIG_VALUE_DEFAULT_MAPCONNECTSTO;
                    pITS->Tx.MAP.pLanes[i].pConnections[j].Maneuver =
                      ITS_CONFIG_VALUE_DEFAULT_MAPMANEUVER;

                    if (pConnection != NULL)
                    {
                      if (config_setting_lookup_int(pConnection,
                                                    ITS_CONFIG_VALUE_NAME_MAPSIGNALGROUP,
                                                    &ConfigVal))
                        pITS->Tx.MAP.pLanes[i].pConnections[j].SignalGroup =  (uint8_t) ConfigVal;
                      d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pConnections[%d].SignalGroup = %d\n",
                               i, j, pITS->Tx.MAP.pLanes[i].pConnections[j].SignalGroup);

                      if (config_setting_lookup_int(pConnection,
                                                    ITS_CONFIG_VALUE_NAME_MAPCONNECTSTO,
                                                    &ConfigVal))
                        pITS->Tx.MAP.pLanes[i].pConnections[j].ConnectsTo =  (int) ConfigVal;
                      d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pConnections[%d].ConnectsTo = %d\n",
                               i, j, pITS->Tx.MAP.pLanes[i].pConnections[j].ConnectsTo);

                      if (config_setting_lookup_int(pConnection,
                                                    ITS_CONFIG_VALUE_NAME_MAPMANEUVER,
                                                    &ConfigVal))
                        pITS->Tx.MAP.pLanes[i].pConnections[j].Maneuver =  (uint8_t) ConfigVal;
                      d_printf(D_DEBUG, 0, "MAP.pLanes[%d].pConnections[%d].Maneuver = %d\n",
                               i, j, pITS->Tx.MAP.pLanes[i].pConnections[j].Maneuver);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}


static void ITSCtrl_LoadSpatConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.SPAT.Enabled = false;
  pITS->Tx.SPAT.DynamicPhases = ITS_CONFIG_VALUE_DEFAULT_SPATDYNAMICPHASES;
  pITS->Tx.SPAT.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_SPATAPPLINTERVAL;
  pITS->Tx.SPAT.IntersectionId = ITS_CONFIG_VALUE_DEFAULT_SPATINTERSECTIONID;
  pITS->Tx.SPAT.RedPhasePeriod = ITS_CONFIG_VALUE_DEFAULT_SPATREDTIME;
  pITS->Tx.SPAT.GreenPhasePeriod = ITS_CONFIG_VALUE_DEFAULT_SPATGREENTIME;
  pITS->Tx.SPAT.YellowPhasePeriod = ITS_CONFIG_VALUE_DEFAULT_SPATYELLOWTIME;
  pITS->Tx.SPAT.NumMovements = 0;
  pITS->Tx.SPAT.pMovements = NULL;

  config_setting_t * pSPAT = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_SPAT);
  if (!pSPAT)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name, ITS_CONFIG_VALUE_NAME_SPAT);
    return;
  }

  // SPAT Enabled
  if (config_setting_lookup_bool(pSPAT,
                                 ITS_CONFIG_VALUE_NAME_SPATENABLED,
                                 &ConfigVal))
    pITS->Tx.SPAT.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.Enabled = %d\n", pITS->Tx.SPAT.Enabled);


  // Dynamic/Fixed SPAT contents
  if (config_setting_lookup_bool(pSPAT,
                                 ITS_CONFIG_VALUE_NAME_SPATDYNAMICPHASES,
                                 &ConfigVal))
    pITS->Tx.SPAT.DynamicPhases = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.DynamicPhases = %d\n", pITS->Tx.SPAT.DynamicPhases);

  // Duration
  if (config_setting_lookup_int(pSPAT,
                                ITS_CONFIG_VALUE_NAME_SPATAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.SPAT.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.ApplInterval = %d\n", pITS->Tx.SPAT.ApplInterval);

  // Intersection ID
  if (config_setting_lookup_int(pSPAT,
                                ITS_CONFIG_VALUE_NAME_SPATINTERSECTIONID,
                                &ConfigVal))
    pITS->Tx.SPAT.IntersectionId = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.IntersectionId = 0x%x\n", pITS->Tx.SPAT.IntersectionId);

  // Red phase reload
  if (config_setting_lookup_int(pSPAT,
                                ITS_CONFIG_VALUE_NAME_SPATREDTIME,
                                &ConfigVal))
    pITS->Tx.SPAT.RedPhasePeriod = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.RedPhasePeriod = %d\n", pITS->Tx.SPAT.RedPhasePeriod);

  // Green phase reload
  if (config_setting_lookup_int(pSPAT,
                                ITS_CONFIG_VALUE_NAME_SPATGREENTIME,
                                &ConfigVal))
    pITS->Tx.SPAT.GreenPhasePeriod = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.GreenPhasePeriod = %d\n", pITS->Tx.SPAT.GreenPhasePeriod);

  // Yellow phase reload
  if (config_setting_lookup_int(pSPAT,
                                ITS_CONFIG_VALUE_NAME_SPATYELLOWTIME,
                                &ConfigVal))
    pITS->Tx.SPAT.YellowPhasePeriod = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SPAT.YellowPhasePeriod = %d\n", pITS->Tx.SPAT.YellowPhasePeriod);

  // Construct movement states
  config_setting_t *pMovemenets;
  pMovemenets = config_setting_get_member(pSPAT, ITS_CONFIG_VALUE_NAME_SPATMOVEMENETS);
  if (!pMovemenets)
  {
    d_fnend(D_INTERN, NULL, "(%p,%p): no movements\n", pITS, pSetting);
    return;
  }
  int NumberOfMovements = pITS->Tx.SPAT.NumMovements = config_setting_length(pMovemenets);

  d_printf(D_DEBUG, 0, "SPAT.NumMovements = %d\n", pITS->Tx.SPAT.NumMovements);

  if (NumberOfMovements <= 0)
  {
    pITS->Tx.SPAT.NumMovements = 0;
    d_fnend(D_INTERN, NULL, "(%p,%p): 0 movements\n", pITS, pSetting);
    return;
  }
  pITS->Tx.SPAT.pMovements = (tSPATMovementParams *)
    calloc(sizeof(tSPATMovementParams), NumberOfMovements);
  if (!pITS->Tx.SPAT.pMovements)
  {
    pITS->Tx.SPAT.NumMovements = 0;
    d_fnend(D_CRIT, NULL, "(%p,%p): Unable to allocate %d Movements\n",
            pITS, pSetting, NumberOfMovements);
    return;
  }
  int i;
  for (i = 0; i < NumberOfMovements; ++i)
  {
    tSPATMovementParams *pMovementParams = &(pITS->Tx.SPAT.pMovements[i]);
    config_setting_t *pMovement   = config_setting_get_elem(pMovemenets, i);
    // initialise some defaults
    pMovementParams->SignalGroup  = ITS_CONFIG_VALUE_DEFAULT_SPATSIGNALGROUP;
    pMovementParams->TimeToChange = ITS_CONFIG_VALUE_DEFAULT_SPATTIMETOCHANGE;
    pMovementParams->CurrentState = ITS_CONFIG_VALUE_DEFAULT_SPATCURRENTSTATE;

    if (!pMovement)
    {
      // we couldn't get libconfig to provide the movement info it told us was there.
      d_printf(D_WARN, NULL, "Unable to get movement %d\n", i);
      continue;
    }

    // override the defaults (if they're in the config file)
    if (config_setting_lookup_int(pMovement,
                                  ITS_CONFIG_VALUE_NAME_SPATSIGNALGROUP,
                                  &ConfigVal))
      pMovementParams->SignalGroup =  (uint8_t) ConfigVal;
    d_printf(D_DEBUG, 0, "SPAT.pMovements[%d].SignalGroup = %d\n",
             i, pMovementParams->SignalGroup);

    if (config_setting_lookup_int(pMovement,
                                  ITS_CONFIG_VALUE_NAME_SPATTIMETOCHANGE,
                                  &ConfigVal))
      pMovementParams->TimeToChange =  (uint16_t) ConfigVal;
    d_printf(D_DEBUG, 0, "SPAT.pMovements[%d].TimeToChange = %d\n",
             i, pMovementParams->TimeToChange);

    if (config_setting_lookup_int(pMovement,
                                  ITS_CONFIG_VALUE_NAME_SPATCURRENTSTATE,
                                  &ConfigVal))
      pMovementParams->CurrentState =  (uint8_t) ConfigVal;
    d_printf(D_DEBUG, 0, "SPAT.pMovements[%d].CurrentState = %d\n",
             i, pMovementParams->CurrentState);

    config_setting_t *pSpeedAdvisories;
    pSpeedAdvisories = config_setting_get_member(pMovement,
                                                 ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICE);
    if (!pSpeedAdvisories)
    {
      // no speed advisories
      continue;
    }
    int NumSpeedAdvisories = pMovementParams->NumSpeedAdvisories =
      config_setting_length(pSpeedAdvisories);

    d_printf(D_DEBUG, 0,
             "SPAT.pMovements[%d].NumSpeedAdvice = %d\n",
             i, pMovementParams->NumSpeedAdvisories);

    if (NumSpeedAdvisories <= 0)
    {
      pMovementParams->NumSpeedAdvisories = 0;
      continue;
    }

    pMovementParams->pSpeedAdvisories =
      (tSPATSpeedAdvisory *)calloc(sizeof(tSPATSpeedAdvisory), NumSpeedAdvisories);

    if (!pMovementParams->pSpeedAdvisories)
    {
      d_printf(D_CRIT, NULL,
               "(%p,%p): Unable to allocate %d SpeedAdvisories for movement %d\n",
               pITS, pSetting, NumSpeedAdvisories, i);
      pMovementParams->NumSpeedAdvisories = 0;
      continue;
    }
    int j;
    for (j = 0; j < NumSpeedAdvisories; ++j)
    {
      tSPATSpeedAdvisory *pSpeedAdvisory = &(pMovementParams->pSpeedAdvisories[j]);
      // set some defaults ...
      pSpeedAdvisory->Speed_tenthmps = 0;
      pSpeedAdvisory->Distance_m     = 0;
      pSpeedAdvisory->Type           = 0;

      // ... and try to override them
      config_setting_t *pSpeedAdvice = config_setting_get_elem(pSpeedAdvisories, j);
      if (!pSpeedAdvice)
      {
        // config data missing, leave the defaults.
        d_printf(D_WARN, NULL, "Unable to get speedadvice %d for movement %d\n", j, i);
        continue;
      }

      if (config_setting_lookup_int(pSpeedAdvice,
                                    ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICESPEED,
                                    &ConfigVal))
        pSpeedAdvisory->Speed_tenthmps =  (uint16_t)ConfigVal;

      d_printf(D_DEBUG, 0,
               "SPAT.pMovements[%d].SpeedAdvisories[%d].Speed_tenthmps = %d\n",
               i, j, pSpeedAdvisory->Speed_tenthmps);

      if (config_setting_lookup_int(pSpeedAdvice,
                                    ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICEDISTANCE,
                                    &ConfigVal))
        pSpeedAdvisory->Distance_m =  (uint16_t)ConfigVal;

      d_printf(D_DEBUG, 0,
               "SPAT.pMovements[%d].SpeedAdvisories[%d].Distance_m = %d\n",
               i, j, pSpeedAdvisory->Distance_m);

      if (config_setting_lookup_int(pSpeedAdvice,
                                    ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICETYPE,
                                    &ConfigVal))
        pSpeedAdvisory->Type =  (uint8_t)ConfigVal;

      d_printf(D_DEBUG, 0,
               "SPAT.pMovements[%d].SpeedAdvisories[%d].Type = %d\n",
               i, j, pSpeedAdvisory->Type);
    } // end "for (j = 0; j < NumSpeedAdvisories; ++j)"
  } // end "for (i = 0; i < NumberOfMovements; ++i)"
}

static void ITSCtrl_LoadSRMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.SRM.Enabled = false;
  pITS->Tx.SRM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_SRMAPPLINTERVAL;
  pITS->Tx.SRM.IntersectionId = ITS_CONFIG_VALUE_DEFAULT_SRMINTERSECTIONID;

  config_setting_t *pSRM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_SRM);
  if (!pSRM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_SRM);
    return;
  }

  // SRM Enabled
  if (config_setting_lookup_bool(pSRM,
                                 ITS_CONFIG_VALUE_NAME_SRMENABLED,
                                 &ConfigVal))
    pITS->Tx.SRM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "SRM.Enabled = %d\n", pITS->Tx.SRM.Enabled);

  // Duration
  if (config_setting_lookup_int(pSRM,
                                ITS_CONFIG_VALUE_NAME_SRMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.SRM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SRM.ApplInterval = %d\n", pITS->Tx.SRM.ApplInterval);

  // Intersection ID
  if (config_setting_lookup_int(pSRM,
                                ITS_CONFIG_VALUE_NAME_SRMINTERSECTIONID,
                                &ConfigVal))
    pITS->Tx.SRM.IntersectionId = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SRM.IntersectionId = 0x%x\n", pITS->Tx.SRM.IntersectionId);
}

static void ITSCtrl_LoadSSMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.SSM.Enabled = false;
  pITS->Tx.SSM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_SSMAPPLINTERVAL;
  pITS->Tx.SSM.IntersectionId = ITS_CONFIG_VALUE_DEFAULT_SSMINTERSECTIONID;

  config_setting_t *pSSM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_SSM);
  if (!pSSM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_SSM);
    return;
  }

  // SSM Enabled
  if (config_setting_lookup_bool(pSSM,
                                 ITS_CONFIG_VALUE_NAME_SSMENABLED,
                                 &ConfigVal))
    pITS->Tx.SSM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "SSM.Enabled = %d\n", pITS->Tx.SSM.Enabled);

  // Duration
  if (config_setting_lookup_int(pSSM,
                                ITS_CONFIG_VALUE_NAME_SSMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.SSM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SSM.ApplInterval = %d\n", pITS->Tx.SSM.ApplInterval);

  // Intersection ID
  if (config_setting_lookup_int(pSSM,
                                ITS_CONFIG_VALUE_NAME_SSMINTERSECTIONID,
                                &ConfigVal))
    pITS->Tx.SSM.IntersectionId = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SSM.IntersectionId = 0x%x\n", pITS->Tx.SSM.IntersectionId);
}

static void ITSCtrl_LoadSAConfig(struct ITSCtrl *pITS,
                                 config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.SA.Enabled = false;
  pITS->Tx.SA.Protocol = 0; // UNKNOWN
  pITS->Tx.SA.ITSAID = 0;
  pITS->Tx.SA.DataLen = 0;

  config_setting_t *pSA = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_SA);
  if (!pSA)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_SA);
    return;
  }

  // SA Enabled
  if (config_setting_lookup_bool(pSA,
                                 ITS_CONFIG_VALUE_NAME_SAENABLED,
                                 &ConfigVal))
    pITS->Tx.SA.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "SA.Enabled = %d\n", pITS->Tx.SA.Enabled);

  // Protocol
  if (config_setting_lookup_int(pSA,
                                ITS_CONFIG_VALUE_NAME_SAPROTOCOL,
                                &ConfigVal))
    pITS->Tx.SA.Protocol = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SA.Protocol = 0x%x\n", pITS->Tx.SA.Protocol);

  // ITSAID
  if (config_setting_lookup_int(pSA,
                                ITS_CONFIG_VALUE_NAME_SAITSAID,
                                &ConfigVal))
    pITS->Tx.SA.ITSAID = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "SA.ITSAID = 0x%x\n", pITS->Tx.SA.ITSAID);

  // Data
  config_setting_t * pData = config_setting_get_member
    (pSA, ITS_CONFIG_VALUE_NAME_SADATA);
  if (pData)
  {
    int DataLen = config_setting_length(pData);
    if (DataLen > 0)
    {
      pITS->Tx.SA.DataLen = DataLen;
      d_printf(D_DEBUG, 0, "SA.DataLen = %d\n", pITS->Tx.SA.DataLen);

      int i;
      for(i = 0; i < DataLen; i++)
      {
        ConfigVal = config_setting_get_int_elem(pData, i);
        pITS->Tx.SA.Data[i] = ConfigVal;
      }
    }
  }

}

static void ITSCtrl_LoadRTCMConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.RTCM.Enabled = false;
  pITS->Tx.RTCM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_RTCMAPPLINTERVAL;
  pITS->Tx.RTCM.DataLen = 0;

  config_setting_t *pRTCM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_RTCM);
  if (!pRTCM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_RTCM);
    return;
  }

  // RTCM Enabled
  if (config_setting_lookup_bool(pRTCM,
                                 ITS_CONFIG_VALUE_NAME_RTCMENABLED,
                                 &ConfigVal))
    pITS->Tx.RTCM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "RTCM.Enabled = %d\n", pITS->Tx.RTCM.Enabled);

  // Interval
  if (config_setting_lookup_int(pRTCM,
                                ITS_CONFIG_VALUE_NAME_RTCMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.RTCM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "RTCM.ApplInterval = %d\n", pITS->Tx.RTCM.ApplInterval);

  // Data
  config_setting_t * pData = config_setting_get_member
    (pRTCM, ITS_CONFIG_VALUE_NAME_RTCMDATA);
  if (pData)
  {
    int DataLen = config_setting_length(pData);
    if (DataLen > 0)
    {
      pITS->Tx.RTCM.DataLen = DataLen;
      d_printf(D_DEBUG, 0, "RTCM.DataLen = %d\n", pITS->Tx.RTCM.DataLen);

      int i;
      for(i = 0; i < DataLen; i++)
      {
        ConfigVal = config_setting_get_int_elem(pData, i);
        pITS->Tx.RTCM.Data[i] = ConfigVal;
      }
    }
  }

}

static void ITSCtrl_LoadCPMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.CPM.Enabled = false;
  pITS->Tx.CPM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_CPMAPPLINTERVAL;

  config_setting_t *pCPM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_CPM);
  if (!pCPM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_CPM);
    return;
  }

  // CPM Enabled
  if (config_setting_lookup_bool(pCPM,
                                 ITS_CONFIG_VALUE_NAME_CPMENABLED,
                                 &ConfigVal))
    pITS->Tx.CPM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "CPM.Enabled = %d\n", pITS->Tx.CPM.Enabled);

  // Interval
  if (config_setting_lookup_int(pCPM,
                                ITS_CONFIG_VALUE_NAME_CPMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.CPM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "CPM.ApplInterval = %d\n", pITS->Tx.CPM.ApplInterval);

}

static void ITSCtrl_LoadVAMConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.VAM.Enabled = false;
  pITS->Tx.VAM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_VAMAPPLINTERVAL;

  config_setting_t *pVAM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_VAM);
  if (!pVAM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_VAM);
    return;
  }

  // VAM Enabled
  if (config_setting_lookup_bool(pVAM,
                                 ITS_CONFIG_VALUE_NAME_VAMENABLED,
                                 &ConfigVal))
    pITS->Tx.VAM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "VAM.Enabled = %d\n", pITS->Tx.VAM.Enabled);

  // Interval
  if (config_setting_lookup_int(pVAM,
                                ITS_CONFIG_VALUE_NAME_VAMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.VAM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "VAM.ApplInterval = %d\n", pITS->Tx.VAM.ApplInterval);

}

static void ITSCtrl_LoadIMZMConfig(struct ITSCtrl *pITS,
                                   config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.IMZM.Enabled = false;
  pITS->Tx.IMZM.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_IMZMAPPLINTERVAL;

  config_setting_t *pIMZM = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_IMZM);
  if (!pIMZM)
  {
    d_fnend(D_INFO, NULL, "'%s' has no '%s' section\n",
            pSetting->name,  ITS_CONFIG_VALUE_NAME_IMZM);
    return;
  }

  // IMZM Enabled
  if (config_setting_lookup_bool(pIMZM,
                                 ITS_CONFIG_VALUE_NAME_IMZMENABLED,
                                 &ConfigVal))
    pITS->Tx.IMZM.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "IMZM.Enabled = %d\n", pITS->Tx.IMZM.Enabled);

  // Interval
  if (config_setting_lookup_int(pIMZM,
                                ITS_CONFIG_VALUE_NAME_IMZMAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.IMZM.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "IMZM.ApplInterval = %d\n", pITS->Tx.IMZM.ApplInterval);

}

// General IVI config
static void ITSCtrl_LoadIviConfig(struct ITSCtrl *pITS,
                                  config_setting_t *pSetting)
{
  d_assert(pITS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pITS, pSetting);

  int ConfigVal = 0;

  pITS->Tx.IVI.Enabled = false;
  pITS->Tx.IVI.ApplInterval = ITS_CONFIG_VALUE_DEFAULT_IVIAPPLINTERVAL;

  // IVI Enabled
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_IVIENABLED,
                                 &ConfigVal))
    pITS->Tx.IVI.Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "IVI.Enabled = %d\n", pITS->Tx.IVI.Enabled);

  // Interval
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_IVIAPPLINTERVAL,
                                &ConfigVal))
    pITS->Tx.IVI.ApplInterval = (uint16_t) ConfigVal;
  d_printf(D_DEBUG, 0, "IVI.ApplInterval = %d\n", pITS->Tx.IVI.ApplInterval);

}

// Specific IVS information
static int ITSCtrl_LoadIVSConfig(tITSTxIVSParams *pIVS,
                                 config_setting_t *pSetting)
{
  d_assert(pIVS);
  d_assert(pSetting);
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pIVS, pSetting);

  int ConfigVal = 0;
  long long ConfigVal64 = 0;

  pIVS->Enabled = false;

  pIVS->ValidFromTime = 0;
  pIVS->ValidToTime = 0;

  pIVS->RefLatitude = ITS_CONFIG_VALUE_DEFAULT_EVENTLAT;
  pIVS->RefLongitude = ITS_CONFIG_VALUE_DEFAULT_EVENTLONG;
  pIVS->RefAltitude = ITS_CONFIG_VALUE_DEFAULT_EVENTALT;

  // IVI Enabled
  if (config_setting_lookup_bool(pSetting,
                                 ITS_CONFIG_VALUE_NAME_IVIENABLED,
                                 &ConfigVal))
    pIVS->Enabled = (bool) ConfigVal;
  d_printf(D_DEBUG, 0, "Enabled = %d\n", pIVS->Enabled);

  // IVI ID
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_IVIIDNUMBER,
                                &ConfigVal))
    pIVS->IviIdentificationNumber = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "IviIdentificationNumber = 0x%x\n", pIVS->IviIdentificationNumber);

  // Service Provider
  // Support 'raw' format that matches the packed 24-bit Service Provider ID
  // Also support split format (note that Country ID occupies least significant 10-bits of configuration variable)
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_IVISPRAW,
                                &ConfigVal))
  {
    pIVS->ServiceProviderCountryID = (ConfigVal >> 14) & 0x3FF;
    pIVS->ServiceProviderIssuerId = ConfigVal & 0x3FFF;
  }
  else
  {
    if (config_setting_lookup_int(pSetting,
                                  ITS_CONFIG_VALUE_NAME_IVISPCOUNTRYID,
                                  &ConfigVal))
      pIVS->ServiceProviderCountryID = (uint32_t) ConfigVal;
    if (config_setting_lookup_int(pSetting,
                                  ITS_CONFIG_VALUE_NAME_IVISPISSUERID,
                                  &ConfigVal))
      pIVS->ServiceProviderIssuerId = (uint32_t) ConfigVal;
  }

  // CountryBuf has 10-bit BIT STRING representation of Country ID (i.e. data in most-significant bits)
  uint8_t CountryBuf[2];
  CountryBuf[0] = (pIVS->ServiceProviderCountryID >> 2) & 0xFF;
  CountryBuf[1] = (pIVS->ServiceProviderCountryID << 6) & 0xC0;
  char CountryCode[3] = {0};
  // Display 2-character country code with ITA2 encoding
  ETSIIVI_GetISO31661Code(CountryBuf, CountryCode);
  d_printf(D_DEBUG, 0, "ServiceProviderCountryID = 0x%02x ('%c%c')\n", pIVS->ServiceProviderCountryID, CountryCode[0], CountryCode[1]);
  d_printf(D_DEBUG, 0, "ServiceProviderIssuerId = 0x%04x\n", pIVS->ServiceProviderIssuerId);
  d_printf(D_DEBUG, 0, "ServiceProviderRaw = 0x%03x\n", (pIVS->ServiceProviderCountryID << 14) | pIVS->ServiceProviderIssuerId);

  // Validity
  if (config_setting_lookup_int64(pSetting,
                                  ITS_CONFIG_VALUE_NAME_IVIVALIDFROM,
                                  &ConfigVal64))
    pIVS->ValidFromTime = (uint64_t) ConfigVal64;
  d_printf(D_DEBUG, 0, "ValidFromTime = 0x%" PRIx64 "\n", pIVS->ValidFromTime);
  if (config_setting_lookup_int64(pSetting,
                                  ITS_CONFIG_VALUE_NAME_IVIVALIDTO,
                                  &ConfigVal64))
    pIVS->ValidToTime = (uint64_t) ConfigVal64;
  d_printf(D_DEBUG, 0, "ValidToTime = 0x%" PRIx64 "\n", pIVS->ValidToTime);

  // Position
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_REFPOSLATITUDE,
                                &ConfigVal))
    pIVS->RefLatitude = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "RefLatitude = 0x%x\n", pIVS->RefLatitude);
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_REFPOSLONGITUDE,
                                &ConfigVal))
    pIVS->RefLongitude = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "RefLongitude = 0x%x\n", pIVS->RefLongitude);
  if (config_setting_lookup_int(pSetting,
                                ITS_CONFIG_VALUE_NAME_REFPOSALTITIUDE,
                                &ConfigVal))
    pIVS->RefAltitude = (uint32_t) ConfigVal;
  d_printf(D_DEBUG, 0, "RefAltitude = 0x%x\n", pIVS->RefAltitude);

  // Detection - delta offsets
  const config_setting_t * pDetOff = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_DETECTZONEOFFSET);

  if (pDetOff)
  {
    pIVS->DetectionZoneOffsetCount = config_setting_length(pDetOff);

    if (pIVS->DetectionZoneOffsetCount > 0)
    {
      int DetIndex;
      for (DetIndex = 0; DetIndex < pIVS->DetectionZoneOffsetCount; DetIndex++)
      {
        config_setting_t *pDetInfo = config_setting_get_elem(pDetOff, DetIndex);
        if (pDetInfo != NULL)
        {
          if (config_setting_lookup_int(pDetInfo, ITS_CONFIG_VALUE_NAME_LATOFFSET, &ConfigVal))
            pIVS->DetectionZoneOffset[DetIndex].DeltaLatitude = ((int32_t) ConfigVal);
          if (config_setting_lookup_int(pDetInfo, ITS_CONFIG_VALUE_NAME_LONGOFFSET, &ConfigVal))
            pIVS->DetectionZoneOffset[DetIndex].DeltaLongitude = ((int32_t) ConfigVal);

        }
      }
    }
  }

  // Detection - absolute position
  const config_setting_t * pDetAbs = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_DETECTZONEABSPOS);

  if (pDetAbs)
  {
    pIVS->DetectionZoneAbsPosnCount = config_setting_length(pDetAbs);

    d_printf(D_DEBUG, 0, "DetectionZoneAbsPosnCount = %d\n", pIVS->DetectionZoneAbsPosnCount);

    if (pIVS->DetectionZoneAbsPosnCount > 0)
    {
      int DetIndex;
      for (DetIndex = 0; DetIndex < pIVS->DetectionZoneAbsPosnCount; DetIndex++)
      {
        config_setting_t *pDetInfo = config_setting_get_elem(pDetAbs, DetIndex);
        if (pDetInfo != NULL)
        {
          if (config_setting_lookup_int(pDetInfo, ITS_CONFIG_VALUE_NAME_LATOFFSET, &ConfigVal))
            pIVS->DetectionZoneAbsPosn[DetIndex].Latitude = ((int32_t) ConfigVal);
          if (config_setting_lookup_int(pDetInfo, ITS_CONFIG_VALUE_NAME_LONGOFFSET, &ConfigVal))
            pIVS->DetectionZoneAbsPosn[DetIndex].Longitude = ((int32_t) ConfigVal);

        }
      }
    }
  }

  // Relevance - delta offsets
  const config_setting_t * pRelOff = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_RELZONEOFFSET);

  if (pRelOff)
  {
    pIVS->RelevanceZoneOffsetCount = config_setting_length(pRelOff);

    if (pIVS->RelevanceZoneOffsetCount > 0)
    {
      int RelIndex;
      for (RelIndex = 0; RelIndex < pIVS->RelevanceZoneOffsetCount; RelIndex++)
      {
        config_setting_t *pRelInfo = config_setting_get_elem(pRelOff, RelIndex);
        if (pRelInfo != NULL)
        {
          if (config_setting_lookup_int(pRelInfo, ITS_CONFIG_VALUE_NAME_LATOFFSET, &ConfigVal))
            pIVS->RelevanceZoneOffset[RelIndex].DeltaLatitude = ((int32_t) ConfigVal);
          if (config_setting_lookup_int(pRelInfo, ITS_CONFIG_VALUE_NAME_LONGOFFSET, &ConfigVal))
            pIVS->RelevanceZoneOffset[RelIndex].DeltaLongitude = ((int32_t) ConfigVal);

        }
      }
    }
  }

  // Relevance - absolute position
  const config_setting_t * pRelAbs = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_RELZONEABSPOS);

  if (pRelAbs)
  {
    pIVS->RelevanceZoneAbsPosnCount = config_setting_length(pRelAbs);

    d_printf(D_DEBUG, 0, "RelevanceZoneAbsPosnCount = %d\n", pIVS->RelevanceZoneAbsPosnCount);

    if (pIVS->RelevanceZoneAbsPosnCount > 0)
    {
      int RelIndex;
      for (RelIndex = 0; RelIndex < pIVS->RelevanceZoneAbsPosnCount; RelIndex++)
      {
        config_setting_t *pRelInfo = config_setting_get_elem(pRelAbs, RelIndex);
        if (pRelInfo != NULL)
        {
          if (config_setting_lookup_int(pRelInfo, ITS_CONFIG_VALUE_NAME_LATOFFSET, &ConfigVal))
            pIVS->RelevanceZoneAbsPosn[RelIndex].Latitude = ((int32_t) ConfigVal);
          if (config_setting_lookup_int(pRelInfo, ITS_CONFIG_VALUE_NAME_LONGOFFSET, &ConfigVal))
            pIVS->RelevanceZoneAbsPosn[RelIndex].Longitude = ((int32_t) ConfigVal);

        }
      }
    }
  }

  // Generic - delta offsets
  const config_setting_t * pGenTraces = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_GENERICZONE);

  if (pGenTraces)
  {
    pIVS->GenericZoneCount = config_setting_length(pGenTraces);

    d_printf(D_DEBUG, 0, "GenericZoneCount = %d\n", pIVS->GenericZoneCount);

    if (pIVS->GenericZoneCount > 0)
    {
      int GenTraceIndex;
      for (GenTraceIndex = 0; GenTraceIndex < pIVS->GenericZoneCount; GenTraceIndex++)
      {
        config_setting_t *pGenZone = config_setting_get_elem(pGenTraces, GenTraceIndex);

        if (pGenZone)
        {
          if (config_setting_lookup_int(pGenZone, ITS_CONFIG_VALUE_NAME_GENERICZONEID, &ConfigVal))
            pIVS->GenericZone[GenTraceIndex].GenericZoneId = ((int32_t) ConfigVal);

          // Check offsets type
          const config_setting_t * pGenOff = config_setting_get_member(
            pGenZone, ITS_CONFIG_VALUE_NAME_GENERICOFFSETS);

          if (pGenOff == NULL)
          {
            // Try absolutes type
            pGenOff = config_setting_get_member(
              pGenZone, ITS_CONFIG_VALUE_NAME_GENERICABSOLUTES);
            if (pGenOff)
            {
              pIVS->GenericZone[GenTraceIndex].IsAbsolutes = true;
            }
          }

          if (pGenOff)
          {
            pIVS->GenericZone[GenTraceIndex].GenericSegmentCount = config_setting_length(pGenOff);

            d_printf(D_DEBUG, 0, "GenericSegmentCount = %d\n", pIVS->GenericZone[GenTraceIndex].GenericSegmentCount);

            if (pIVS->GenericZone[GenTraceIndex].GenericSegmentCount > 0)
            {
              int GenIndex;

              for (GenIndex = 0; GenIndex < pIVS->GenericZone[GenTraceIndex].GenericSegmentCount; GenIndex++)
              {
                config_setting_t *pGenInfo = config_setting_get_elem(pGenOff, GenIndex);
                if (pGenInfo != NULL)
                {
                  if (config_setting_lookup_int(pGenInfo, ITS_CONFIG_VALUE_NAME_LATOFFSET, &ConfigVal))
                    pIVS->GenericZone[GenTraceIndex].GenericSegment[GenIndex].Latitude = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pGenInfo, ITS_CONFIG_VALUE_NAME_LONGOFFSET, &ConfigVal))
                    pIVS->GenericZone[GenTraceIndex].GenericSegment[GenIndex].Longitude = ((int32_t) ConfigVal);
                }
              }
            }
          }
        }
      }
    }
  }

  // GIC
  const config_setting_t * pGIC = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_GIC);

  if (pGIC)
  {
    pIVS->GICPartsCount = config_setting_length(pGIC);

    d_printf(D_DEBUG, 0, "GICPartsCount = %d\n", pIVS->GICPartsCount);

    if (pIVS->GICPartsCount > 0)
    {
      int PartIndex;
      for (PartIndex = 0; PartIndex < pIVS->GICPartsCount; PartIndex++)
      {
        config_setting_t *pPartInfo = config_setting_get_elem(pGIC, PartIndex);
        if (pPartInfo != NULL)
        {
          pIVS->GICPart[PartIndex].MinimumAwarenessTime = 4; // the value used prior to adding configurability
          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_GIC_MINAWARETIME,
                                        &ConfigVal))
            pIVS->GICPart[PartIndex].MinimumAwarenessTime = (uint32_t) ConfigVal;

          pIVS->GICPart[PartIndex].IviType = 0; // the value used prior to adding configurability
          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_GIC_IVITYPE,
                                        &ConfigVal))
            pIVS->GICPart[PartIndex].IviType = (uint32_t) ConfigVal;

          const config_setting_t * pLane = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_GIC_LANES);

          if (pLane)
          {
            pIVS->GICPart[PartIndex].NumApplicLanes = config_setting_length(pLane);

            d_printf(D_DEBUG, 0, "GICPart[PartIndex].NumApplicLanes = %d\n", pIVS->GICPart[PartIndex].NumApplicLanes);

            int LaneIndex;
            for (LaneIndex = 0; LaneIndex < pIVS->GICPart[PartIndex].NumApplicLanes; LaneIndex++)
            {
              pIVS->GICPart[PartIndex].ApplicLanes[LaneIndex] = config_setting_get_int_elem(pLane, LaneIndex);
            }
          }

          const config_setting_t * pDetZone = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_GIC_DETZONES);

          if (pDetZone)
          {
            pIVS->GICPart[PartIndex].NumDetZones = config_setting_length(pDetZone);

            d_printf(D_DEBUG, 0, "GICPart[PartIndex].NumDetZones = %d\n", pIVS->GICPart[PartIndex].NumDetZones);

            int ZoneIndex;
            for (ZoneIndex = 0; ZoneIndex < pIVS->GICPart[PartIndex].NumDetZones; ZoneIndex++)
            {
              pIVS->GICPart[PartIndex].DetZones[ZoneIndex] = config_setting_get_int_elem(pDetZone, ZoneIndex);
            }
          }

          const config_setting_t * pRelZone = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_GIC_RELZONES);

          if (pRelZone)
          {
            pIVS->GICPart[PartIndex].NumRelZones = config_setting_length(pRelZone);

            d_printf(D_DEBUG, 0, "GICPart[PartIndex].NumRelZones = %d\n", pIVS->GICPart[PartIndex].NumRelZones);

            int ZoneIndex;
            for (ZoneIndex = 0; ZoneIndex < pIVS->GICPart[PartIndex].NumRelZones; ZoneIndex++)
            {
              pIVS->GICPart[PartIndex].RelZones[ZoneIndex] = config_setting_get_int_elem(pRelZone, ZoneIndex);
            }
          }

          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_HGVINFO_INCLUDED,
                                        &ConfigVal))
            pIVS->GICPart[PartIndex].HGVInfo = (uint32_t) ConfigVal;

          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_IVITYPE,
                                        &ConfigVal))
            pIVS->GICPart[PartIndex].IviType = (uint32_t) ConfigVal;

          int choice = 0;
          if (config_setting_lookup_int(pPartInfo, ITS_CONFIG_VALUE_NAME_ITSISO14823_CHOICE, &ConfigVal))
            choice = ((int32_t) ConfigVal);

          pIVS->GICPart[PartIndex].useITSISO14823Code = false; // Possibly already is zero if there was a memset 0
          if(choice == 1)
          {
            if (config_setting_lookup_int(pPartInfo, ITS_CONFIG_VALUE_NAME_ITSISO14823_CODE, &ConfigVal))
            {
              pIVS->GICPart[PartIndex].ITSISO14823Code = ((int32_t) ConfigVal);
              pIVS->GICPart[PartIndex].useITSISO14823Code = true;
            }
          }

          // SIGN
          const config_setting_t * pSign = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS);

          if (pSign)
          {
            pIVS->GICPart[PartIndex].NumRoadSigns = config_setting_length(pSign);

            d_printf(D_DEBUG, 0, "GICPart[PartIndex].NumRoadSigns = %d\n", pIVS->GICPart[PartIndex].NumRoadSigns);

            if (pIVS->GICPart[PartIndex].NumRoadSigns > 0)
            {
              int SignIndex;
              for (SignIndex = 0; SignIndex < pIVS->GICPart[PartIndex].NumRoadSigns; SignIndex++)
              {
                config_setting_t *pSignInfo = config_setting_get_elem(pSign, SignIndex);
                if (pSignInfo != NULL)
                {
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_CODE4, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].ITSISO14823Code_4 = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_PICTO, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].TrafficSignPictogram = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_NATURE, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].PictogramCategoryCodeNature = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_SERNUM, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].PictogramCategoryCodeSerialNumber = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_SPEVAL, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].AttributesSPEValue = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pSignInfo, ITS_CONFIG_VALUE_NAME_ROADSIGNS_SPEUNIT, &ConfigVal))
                    pIVS->GICPart[PartIndex].RoadSigns[SignIndex].AttributesSPEUnits = ((int32_t) ConfigVal);
                }
              }
            }
          }

          // TEXT
          const config_setting_t * pText = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_EXTRATEXT);
          if (pText)
          {
            pIVS->GICPart[PartIndex].NumExtraText = config_setting_length(pText);

            if (pIVS->GICPart[PartIndex].NumExtraText > 0)
            {
              int TextIndex;
              for (TextIndex = 0; TextIndex < pIVS->GICPart[PartIndex].NumExtraText; TextIndex++)
              {
                config_setting_t *pTextInfo = config_setting_get_elem(pText, TextIndex);
                if (pTextInfo != NULL)
                {
                  const char *ConfigStr;
                  if (config_setting_lookup_int(pTextInfo, ITS_CONFIG_VALUE_NAME_EXTRATEXT_ID, &ConfigVal))
                    pIVS->GICPart[PartIndex].ExtraText[TextIndex].LayoutComponentId = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pTextInfo, ITS_CONFIG_VALUE_NAME_EXTRATEXT_LANG, &ConfigVal))
                  {
                    pIVS->GICPart[PartIndex].ExtraText[TextIndex].LanguageBitStr[0] = ((uint16_t) ConfigVal) >> 8;
                    pIVS->GICPart[PartIndex].ExtraText[TextIndex].LanguageBitStr[1] = ((uint16_t) ConfigVal);
                  }
                  if (config_setting_lookup_string(pTextInfo, ITS_CONFIG_VALUE_NAME_EXTRATEXT_TEXT, &ConfigStr))
                    strcpy(pIVS->GICPart[PartIndex].ExtraText[TextIndex].TextContent, ConfigStr);
                }
              }
            }
          }
        }
      }
    }
  }
  else
  {
    d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
             pSetting->name, ITS_CONFIG_VALUE_NAME_GIC);
  }

  // RCC
  const config_setting_t * pRCC = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_RCC);

  if (pRCC)
  {
    pIVS->RCCPartsCount = config_setting_length(pRCC);

    d_printf(D_DEBUG, 0, "RCCPartsCount = %d\n", pIVS->RCCPartsCount);

    if (pIVS->RCCPartsCount > 0)
    {
      int PartIndex;
      for (PartIndex = 0; PartIndex < pIVS->RCCPartsCount; PartIndex++)
      {
        config_setting_t *pPartInfo = config_setting_get_elem(pRCC, PartIndex);
        if (pPartInfo != NULL)
        {
          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_RCC_ROADTYPE,
                                        &ConfigVal))
          {
            pIVS->RCCPart[PartIndex].RoadType = (uint32_t) ConfigVal;
          }

          const config_setting_t * pRelZone = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_RCC_RELZONES);

          if (pRelZone)
          {
            pIVS->RCCPart[PartIndex].NumRelZones = config_setting_length(pRelZone);

            d_printf(D_DEBUG, 0, "RCCPart[PartIndex].NumRelZones = %d\n", pIVS->RCCPart[PartIndex].NumRelZones);

            int ZoneIndex;
            for (ZoneIndex = 0; ZoneIndex < pIVS->RCCPart[PartIndex].NumRelZones; ZoneIndex++)
            {
              pIVS->RCCPart[PartIndex].RelZones[ZoneIndex] = config_setting_get_int_elem(pRelZone, ZoneIndex);
            }
          }

          // RoadInfo
          const config_setting_t * pConf = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_RCC_LANECONF);

          if (pConf)
          {
            pIVS->RCCPart[PartIndex].NumLaneConf = config_setting_length(pConf);

            d_printf(D_DEBUG, 0, "RCCPart[PartIndex].NumLaneConf = %d\n", pIVS->RCCPart[PartIndex].NumLaneConf);

            int LaneConfs;
            for (LaneConfs = 0; LaneConfs < pIVS->RCCPart[PartIndex].NumLaneConf; LaneConfs++)
            {
              config_setting_t *pLaneConf = config_setting_get_elem(pConf, LaneConfs);
              if (pLaneConf != NULL)
              {
                if (config_setting_lookup_int(pLaneConf, ITS_CONFIG_VALUE_NAME_RCC_LANECONFNUM, &ConfigVal))
                  pIVS->RCCPart[PartIndex].LaneInfoNumbers[LaneConfs] = ((int32_t) ConfigVal);
                if (config_setting_lookup_int(pLaneConf, ITS_CONFIG_VALUE_NAME_RCC_LANECONFDIR, &ConfigVal))
                  pIVS->RCCPart[PartIndex].LaneInfoDirs[LaneConfs] = ((int32_t) ConfigVal);
              }
            }
          }
        }
      }
    }
  }
  else
  {
    d_printf(D_NOTICE, NULL, "'%s' has no '%s' section\n",
             pSetting->name, ITS_CONFIG_VALUE_NAME_RCC);
  }

  // TC (optional)
  const config_setting_t * pTC = config_setting_get_member(
    pSetting, ITS_CONFIG_VALUE_NAME_TC);

  if (pTC)
  {
    pIVS->TCPartsCount = config_setting_length(pTC);

    d_printf(D_DEBUG, 0, "TCCount = %d\n", pIVS->TCPartsCount);

    if (pIVS->TCPartsCount > 0)
    {
      int PartIndex;
      for (PartIndex = 0; PartIndex < pIVS->TCPartsCount; PartIndex++)
      {
        config_setting_t *pPartInfo = config_setting_get_elem(pTC, PartIndex);
        if (pPartInfo != NULL)
        {
          pIVS->TCPart[PartIndex].MinimumAwarenessTime = 4; // the value used prior to adding configurability
          if (config_setting_lookup_int(pPartInfo,
                                        ITS_CONFIG_VALUE_NAME_TC_MINAWARETIME,
                                        &ConfigVal))
            pIVS->TCPart[PartIndex].MinimumAwarenessTime = (uint32_t) ConfigVal;

          // TEXT
          const config_setting_t * pText = config_setting_get_member(
            pPartInfo, ITS_CONFIG_VALUE_NAME_TC_TEXT);
          if (pText)
          {
            pIVS->TCPart[PartIndex].NumText = config_setting_length(pText);

            if (pIVS->TCPart[PartIndex].NumText > 0)
            {
              int TextIndex;
              for (TextIndex = 0; TextIndex < pIVS->TCPart[PartIndex].NumText; TextIndex++)
              {
                config_setting_t *pTextInfo = config_setting_get_elem(pText, TextIndex);
                if (pTextInfo != NULL)
                {
                  const char *ConfigStr;
                  if (config_setting_lookup_int(pTextInfo, ITS_CONFIG_VALUE_NAME_TC_TEXT_ID, &ConfigVal))
                    pIVS->TCPart[PartIndex].Text[TextIndex].LayoutComponentId = ((int32_t) ConfigVal);
                  if (config_setting_lookup_int(pTextInfo, ITS_CONFIG_VALUE_NAME_TC_TEXT_LANG, &ConfigVal))
                  {
                    pIVS->TCPart[PartIndex].Text[TextIndex].LanguageBitStr[0] = ((uint16_t) ConfigVal) >> 8;
                    pIVS->TCPart[PartIndex].Text[TextIndex].LanguageBitStr[1] = ((uint16_t) ConfigVal);
                  }
                  if (config_setting_lookup_string(pTextInfo, ITS_CONFIG_VALUE_NAME_TC_TEXT_TEXTCONTENT, &ConfigStr))
                    strcpy(pIVS->TCPart[PartIndex].Text[TextIndex].TextContent, ConfigStr);
                }
              }
            }
          }
        }
      }
    }
  }
  else
  {
    d_printf(D_INFO, NULL, "'%s' has no '%s' section\n",
             pSetting->name, ITS_CONFIG_VALUE_NAME_TC);
  }

  return 0;
}

/**
 * @brief Unload ITSCtrl parameters
 * @param pITS ITS transmitter handle
 * @return Zero for success or a negative errno
 */
static int ITSCtrl_UnloadConfig(struct ITSCtrl *pITS)
{
  int Res = -ENOSYS;

  if (pITS)
  {
    pITS->Tx.EVW.Enabled = false;

    pITS->Tx.CAMEnabled = false;

    pITS->Tx.IVI.Enabled = false;

    pITS->Tx.SPAT.Enabled = false;

    int ix;
    for (ix = 0; ix < pITS->Tx.SPAT.NumMovements; ix++)
    {
      free(pITS->Tx.SPAT.pMovements[ix].pSpeedAdvisories);
    }
    free(pITS->Tx.SPAT.pMovements);

    pITS->Tx.MAP.Enabled = false;

    for (ix = 0; ix < pITS->Tx.MAP.NumLanes; ix++)
    {
      free(pITS->Tx.MAP.pLanes[ix].pNodes);
      free(pITS->Tx.MAP.pLanes[ix].pConnections);
    }
    free(pITS->Tx.MAP.pLanes);

    pITS->Tx.SRM.Enabled = false;
    pITS->Tx.SSM.Enabled = false;

    pITS->Tx.RWW.Enabled = false;
    free(pITS->Tx.RWW.pTraces);
    free(pITS->Tx.RWW.ClosedLanes);
    free(pITS->Tx.RWW.pEventPoints);

    Res = 0;
  }

  return Res;
}

/**
 * @brief ITS Periodic thread processing - sends a ITS
 * @param pArg Pointer to ITSCtrl object passed as generic input parameter
 *
 */
static void ITSCtrl_ThreadProc (void *pArg)
{
  struct ITSCtrl *pITS;
  struct timespec Time;

  d_printf(D_WARN, 0, "ITS Ctrl thread running\n");

  // pArg cast to ITStx object
  pITS = (struct ITSCtrl *) pArg;

  // Start RX
  ITSRx_Open(pITS);
  // Start TX
  ITSTx_Open(pITS);

  // Allow Tx/Rx to get up and running
  sleep(2);

  // Initialise the timespec struct for the polling loop
  clock_gettime(CLOCK_MONOTONIC, &Time);

  uint64_t TimeMSec = (Time.tv_sec * 1000) + (Time.tv_nsec / 1000000);

  pITS->Tx.RWW.NextTxTimeMS = TimeMSec;
  pITS->Tx.EVW.NextTxTimeMS = TimeMSec;
  pITS->Tx.SPAT.NextTxTimeMS = TimeMSec;
  pITS->Tx.MAP.NextTxTimeMS = TimeMSec;
  pITS->Tx.SRM.NextTxTimeMS = TimeMSec;
  pITS->Tx.SSM.NextTxTimeMS = TimeMSec;
  pITS->Tx.IVI.NextTxTimeMS = TimeMSec;
  pITS->Tx.RTCM.NextTxTimeMS = TimeMSec;
  pITS->Tx.CPM.NextTxTimeMS = TimeMSec;
  pITS->Tx.VAM.NextTxTimeMS = TimeMSec;
  pITS->Tx.IMZM.NextTxTimeMS = TimeMSec;

  // "Starting ITS Periodic Thread");
  pITS->Ctrl.ThreadState |= ITS_THREAD_STATE_RUN;

  // Startup so initialise/start/...

  // CAM sending enabled
  if (pITS->Tx.CAMEnabled)
  {
    // Assumes CAM is not automatically started
    (void)CAM_ServiceStart();
  }

  // Emergency vehicle
  if (pITS->Tx.EVW.Enabled)
  {
    // Special container fields populated from VState (e.g. LightBarInUse, SirenInUse)
    (void)C2C_ActivateSpecialRole(C2CVehicleRole_emergency_response);
  }

  if (pITS->Tx.pVehCont != NULL)
  {
    (void)CAM_VehTollingZone(pITS->Tx.pVehCont);
  }

  if (pITS->Tx.pRSUCont != NULL)
  {
    (void)CAM_RSUProtCommsZones(pITS->Tx.pRSUCont);
  }

  if (pITS->Tx.MAP.Enabled)
  {
    d_printf(D_INFO, 0, "Sending MAP %x\n", QSMSG_ITS_MAP_TX_REQ);
    (void)Msg_SendId(QSMSG_ITS_MAP_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
  }

  if (pITS->Tx.IMZM.Enabled)
  {
    d_printf(D_INFO, 0, "Sending IMZM %x\n", QSMSG_ITS_IMZM_TX_REQ);
    (void)Msg_SendId(QSMSG_ITS_IMZM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
  }

  if (pITS->Tx.SA.Enabled)
  {
    d_printf(D_INFO, 0, "Sending SA %x\n", QSMSG_ITS_SA_TX_REQ);
    (void)Msg_SendId(QSMSG_ITS_SA_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
  }

  // Thread loop for periodic actions
  while ((pITS->Ctrl.ThreadState & ITS_THREAD_STATE_STOP) == 0)
  {
    uint64_t NowMSec = (Time.tv_sec * 1000) + (Time.tv_nsec / 1000000);

    if ((pITS->Tx.EVW.Enabled) && (NowMSec >= pITS->Tx.EVW.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending EVW DENM %x\n", QSMSG_ITS_DENM_EVW_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_DENM_EVW_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.EVW.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.EVW.ApplInterval);
    }

    if ((pITS->Tx.SPAT.Enabled) && (NowMSec >= pITS->Tx.SPAT.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending SPAT %x\n", QSMSG_ITS_SPAT_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_SPAT_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.SPAT.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.SPAT.ApplInterval);
    }

    if ((pITS->Tx.SRM.Enabled) && (NowMSec >= pITS->Tx.SRM.NextTxTimeMS))
    {
      // Normally SRM sent when approaching an intersection and terminated when no longer needed
      // But this just allows periodic sending to demonstrate the APIs
      d_printf(D_INFO, 0, "Sending SRM %x\n", QSMSG_ITS_SRM_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_SRM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.SRM.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.SRM.ApplInterval);
    }

    if ((pITS->Tx.SSM.Enabled) && (NowMSec >= pITS->Tx.SSM.NextTxTimeMS))
    {
      // Normally SSM sent in response to SRM
      // But this just allows periodic sending to demonstrate the APIs
      d_printf(D_INFO, 0, "Sending SSM %x\n", QSMSG_ITS_SSM_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_SSM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.SSM.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.SSM.ApplInterval);
    }

    if ((pITS->Tx.CPM.Enabled) && (NowMSec >= pITS->Tx.CPM.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending CPM %x\n", QSMSG_ITS_CPM_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_CPM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.CPM.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.CPM.ApplInterval);
    }

    if ((pITS->Tx.VAM.Enabled) && (NowMSec >= pITS->Tx.VAM.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending VAM %x\n", QSMSG_ITS_VAM_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_VAM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.VAM.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.VAM.ApplInterval);
    }

    if ((pITS->Tx.IVI.Enabled) && (NowMSec >= pITS->Tx.IVI.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending IVI %x\n", QSMSG_ITS_IVI_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_IVI_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.IVI.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.IVI.ApplInterval);
    }

    if (((pITS->Tx.RWW.Enabled) || (pITS->Tx.RWW2.Enabled) || (pITS->Tx.RWW3.Enabled) || (pITS->Tx.RWW4.Enabled)) &&
        (NowMSec >= pITS->Tx.RWW.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending RWW DENM %x\n", QSMSG_ITS_DENM_ROADWORKS_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_DENM_ROADWORKS_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.RWW.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.RWW.RepInterval);
    }

    if ((pITS->Tx.RTCM.Enabled) && (NowMSec >= pITS->Tx.RTCM.NextTxTimeMS))
    {
      d_printf(D_INFO, 0, "Sending RTCM %x\n", QSMSG_ITS_RTCM_TX_REQ);
      (void)Msg_SendId(QSMSG_ITS_RTCM_TX_REQ, QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
      pITS->Tx.RTCM.NextTxTimeMS += max(ITSCTRL_NAP_INTERVAL, pITS->Tx.RTCM.ApplInterval);
    }

    // polling delay
    Util_Nap(ITSCTRL_NAP_INTERVAL, &Time);
  }

  d_printf(D_WARN, 0, "ITS Ctrl thread done\n");

  // Shutdown, so deactivate/cancel/...

  if (pITS->Tx.EVW.Enabled)
  {
    (void)C2C_DeactivateSpecialVehicle();
  }

  if ((pITS->Tx.RWW.Enabled) || (pITS->Tx.RWW2.Enabled) || (pITS->Tx.RWW3.Enabled) || (pITS->Tx.RWW4.Enabled))
  {
    (void)Msg_SendId(QSMSG_ITS_DENM_ROADWORKS_TERMINATE_TX_REQ,
                     QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
  }

  if (pITS->Tx.IVI.Enabled)
  {
    (void)Msg_SendId(QSMSG_ITS_IVI_TERMINATE_TX_REQ,
                     QSQUEUE_ITSTX, QSPRIORITY_DEFAULT);
  }


  if (pITS->Tx.pRSUCont != NULL)
  {
    asn1_free_value(asn1_type_ITSProtectedCommunicationZonesRSU,
                    pITS->Tx.pRSUCont);
  }

  if (pITS->Tx.pVehCont != NULL)
  {
    asn1_free_value(asn1_type_ITSCenDsrcTollingZone,
                    pITS->Tx.pVehCont);
  }

  // Stop RX
  ITSRx_Close(pITS);
  // Stop TX
  ITSTx_Close(pITS);

  // exit thread
  (void) pthread_exit(NULL);

}

// Close the doxygen group
/**
 * @}
*/
