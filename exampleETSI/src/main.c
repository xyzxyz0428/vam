/**
 * @addtogroup v2v_exampleetsi ExampleETSI Application
 * @{
 *
 *  @section v2v_exampleetsi_overview Overview of the ExampleETSI Application
 *
 *  This example application shipped with the SDK demonstrates how to use
 *  the Cohda Wireless Stack APIs to develop a V2X application. Full
 *  source code for the application is provided and this can be used as
 *  a basis for the development of new customer applications.
 *
 *  The example application can be run in either an on-board equipment
 *  (OBE) configuration, intended to demonstrate the basic functionality
 *  for a V2X OBE device, or it can be run as an example road-side
 *  equipment (RSE) configuration.
 *
 *  @section v2v_exampleetsi_building Compiling the Example Application
 *
 *  The application can be compiled for an MKx device by compiling it
 *  with the appropriate mkx-tarball Makefile target (where mkx is
 *  replaced by mk5, or x86 as appropriate in the following):
 *
 *  @code
 *  cd ~/mkx/stack/apps/exampleETSI
 *  make mkx-tarball
 *  @endcode
 *
 *  This will produce the tarball exampleETSI-mkx.tgz which contains the example
 *  application and all required configuration etc. This should be
 *  copied to the MKx device and extracted under the /mnt/ubi directory
 *  as follows:
 *
 *  @code
 *  scp exampleETSI-mkx.tgz user@IP_OF_MKX:/tmp
 *  ssh user@IP_OF_MKX
 *  cd /mnt/ubi
 *  mv /tmp/exampleETSI-mkx.tgz .
 *  tar xzf exampleETSI-mkx.tgz
 *  @endcode
 *
 *  @section v2v_exampleeetsi_running Running the Example Application
 *
 *  The application is managed via the rc.exampleETSI script which is used
 *  to launch the application with a particular configuration and to
 *  then stop the application as follows:
 *
 *  @note The example application requires root permissions when run
 *
 *  @code
 *  # launch the application in OBU configuration
 *  ./rc.exampleETSI start obu
 *
 *  # launch the application in RSU configuration
 *  ./rc.exampleETSI start rsu
 *
 *  # launch the application in RAW ITS configuration
 *  ./rc.exampleETSI start raw
 *
 *  # stop the application
 *  ./rc.exampleETSI stop
 *
 *  # Alternatively, use application directly - then terminate with SIGINT
 *  sudo ./exampleETSI -f <appl-config> -c <stack-config>
 *
 *  @endcode
 *
 *  @section v2v_exampleetsi_config Configuring the Example Application
 *
 *  The application is configured using the standard libconfig library.
 *  For more information concerning libconfig in general please see
 *  http://www.hyperrealm.com/libconfig/libconfig_manual.html
 *
 *  The files obu.cfg and rsu.cfg contain the libconfig configuration
 *  for the application in the OBU and RSU modes respectively.
 *  Also present are corresponding stack configuration file (suffix .conf)
 *
 *  @section v2v_exampleetsi_details Basic details of the Example Application
 *
 *  @example exampleETSI/src/main.c
 *  This file contains the main parts of the example ETSI application.
 *
 *  @example exampleETSI/src/raw-its.c
 *  Provides an example of sending & receiving custom ETSI MSG packets on ETSI stack.
 *
 *  @example exampleETSI/src/its-rx-thr.c
 *  Provides an example of receiving CAM & DENM packets on ETSI stack.
 *
 *  @example exampleETSI/src/its-tx-thr.c
 *  Provides an example of sending DENM packets on ETSI stack.
 *
 *  @example exampleETSI/src/pos-ext.c
 *  Provides an example of using external position interface.
 *
 *  @example exampleETSI/src/can-thr.c
 *  Provides an example of using general CAN handling
 *
 *  @example exampleETSI/src/can-vstate.c
 *  Provides an example of using CAN data to update VState
 *
 * @file
 *
 * Example application with both OBE and RSE functionality
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2018 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

/// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>

/// Third-party includes
#include "libconfig.h"

/// Stack includes
#include "util.h"
#include "id-global.h"
#include "libitsnet-mgmt.h"
#include "libitsfac-mgmt.h"
#include "libplat-mgmt.h"
#include "etsi-trx-if.h"
#include "etsi-cam-if.h"
#include "v2xlib-plugin.h"
#include "lph.h"
#include "vstate.h"
#include "gps-rx.h"
#include "can-rx.h"
#include "can-vsc3.h"
#include "debug-levels.h"
#include "ext.h"
#include "TA.h"
#include "TC.h"
#include "TM.h"
#include "hmi.h"
#include "ivi.h"
#include "ldm.h"
#include "log.h"
#include "spat-rx.h"
#include "stats.h"
#include "conf_if.h"

/// OBU app includes
#include "can-vstate.h"
#include "can-thr.h"
#include "its-ctrl-thr.h"
#include "raw-its.h"
#include "pos-ext.h"
#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_Main_DebugLevel

/// Stack size (at least 16384, multiple of 16)
#ifdef __aarch64__
/// Need larger stacksize for 64-bit architectures
#define APP_THREAD_STACK_SIZE   262144
#else
#define APP_THREAD_STACK_SIZE   65536
#endif
/// Commandline option for the obu.cfg file
#define OPTS_TAG_APP_CFG_FILENAME   "-f"
/// Commandline option for the stack config file
#define OPTS_TAG_STACK_CFG_FILENAME  "-c"
/// Commandline option for the extra stack config file
#define OPTS_TAG_EXTRA_CFG_FILENAME  "-C"
/// Commandline option for the flag to override limits on conf files
#define OPTS_TAG_OVERRIDE_LIMITS "-a"
/// Default stack config file
#define OPTS_DEFAULT_STACK_CFG_FILENAME  "stack.conf"
/// Commandline option for help
#define OPTS_TAG_APP_HELP "-h"
/// KPH conversion
#define MPS_TO_KPH 3.6
/// Alert message string size
#define ALERT_STR_SIZE 40
/// Configuration filename max length
#define CONFIG_NAME_MAX_LEN 255

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------

/// App state
// cppcheck-suppress ctuOneDefinitionRuleViolation
typedef struct App
{
  /// App configuration file name
  char pAppConfigFilename[CONFIG_NAME_MAX_LEN];

  /// Stack configuration file name
  char pStackConfigFilename[CONFIG_NAME_MAX_LEN];

  /// Extra configuration file name
  char pExtraConfigFilename[CONFIG_NAME_MAX_LEN];

  // HMI object
  struct HMI *pHMI;

  /// App configuration (from config file)
  struct
  {
    bool CAN;
    bool ITS;
    bool RAWIts;
    bool ExtraConf;
    bool CANVState;
    bool CANVSC3;
    bool PosExt;
  } Cfg;

  /// Application Module handles
  struct
  {
    tCANETSI CAN;
    tITSCtrl ITS;
    tRAWIts RAWIts;
    tCANVStateETSI *pCANVState;
  } Hdl;

} tApp;

#if defined(__QNX__)
typedef union sigval sigval_t;
#endif

//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

/// Thread attribute initialisation
static int Attr_Init(pthread_attr_t *pAttr);

/// Appl initialisation
static int App_Init (tApp *pApp);

/// Appl exit
static void App_Exit (void);

/// Signal handler thread
static void *SignalThread (void *pArg);

/// Signal handler for no-event
static void DummyHandler (int Sig);

/// Signal handler for timeout
static void TimeoutHandler (sigval_t SigVal);

/// Appl usage help
static void PrintUsage (void);

/// Callback for threat assessment
static fTA_Callback TACallback;

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------

/// Thread attributes variable
static pthread_attr_t Attr;

/// Signal set
static sigset_t SigSet;

/// Signal handler thread
static pthread_t Signal_ThreadId;

#if defined(V2XATK)
/// ATK functions called by Aerolink
void *(*ll_get)(const char *dev_name);
int (*ll_init)(const char *dev_name);
#endif

/// App state
static tApp _App;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

/**
 * @brief Get heartbeat info for HMI
 * @param pInfo Info to fill in
 * @return A tHMIErrCode to indicate status
 *
 */
static tHMIErrCode GetHeartBeatInfo(tHMIInfoHeartBeat *pInfo,
                                    void *pPriv)
{
  tHMIErrCode Ret = HMI_ERR_NONE;
  void *pLPH;
  const tStats_StackStats *pStats;

  d_fnstart(D_INFO, NULL, "(%p)\n", pInfo);

  // stop compiler warning
  (void)pPriv;
  pInfo->Id = CAM_GetCurrentInfo().stationID;
  strncpy(pInfo->Version, "exampleETSI", HMI_VERSION_MAX_LEN);
  pInfo->Version[HMI_VERSION_MAX_LEN-1] = '\0';
  pInfo->TxPowerdBm = TRX_GetMaxPower().MaxTxPower / 2;
  pInfo->NumRemotes = TC_GetNumRemotes();
  pInfo->NumIntersections = SPATMAP_GetNumIntersections(61);
  pStats = Stats_GetStackStats();
  if (pStats != NULL)
  {
    pInfo->NumTx = pStats->TxCounters[STACK_TX_OK];
    pInfo->NumRx = pStats->RxCounters[STACK_RX_OK];

    d_printf(D_INFO, 0, "TX OK %d, Sign Failures %d, RX OK %d, Verification Failures %d\n",
             pStats->TxCounters[STACK_TX_OK], pStats->TxCounters[STACK_TX_SIGN],
             pStats->RxCounters[STACK_RX_OK], pStats->RxCounters[STACK_RX_VRFY]);
  }
  pLPH = LPH_Open();
  if (pLPH != NULL)
  {
    int Res;
    tLPHPos Pos;

    Res = LPH_Position(pLPH, &Pos);
    if (Res == 0)
      pInfo->Fix = Pos.Mode;
    LPH_Close(pLPH);
  }
  pInfo->Sync = system("timeout -s 9 3 chronyc waitsync 1 0 0 1>/dev/null 2>/dev/null") == 0 ? 1 : 0;

  d_fnend(D_INFO, NULL, "(%p) = %d\n", pInfo, Ret);
  return Ret;
}

/**
 * @brief Starts stack components and then launches application module threads
 * @param Argc Number of command-line arguments
 * @param pArgv Array of command-line arguments
 * @return 0 on success, error code on error
 */
int main (int Argc, char *pArgv[])
{
  int Stat;
  int ArgIndex;
  int GotAppConfigFilename;
  int GotStackConfigFilename;
  int GotExtraConfigFilename;
  bool OverrideLimits = false;
  int ErrCode = 0;
  tApp *pApp = &_App;

  printf("\nStarting Example ETSI Application...\n");

  // Clear the application state
  memset(pApp, 0x00, sizeof(tApp));

  // Get help
  for (ArgIndex = 0; ArgIndex < Argc; ArgIndex++)
  {
    if (strcmp(pArgv[ArgIndex], OPTS_TAG_APP_HELP) == 0)
    {
      PrintUsage();
      goto Exit;
    }
  }

  // Get app config filename from input params
  GotAppConfigFilename = 0;
  for (ArgIndex = 0; ArgIndex < Argc; ArgIndex++)
  {
    if (strcmp(pArgv[ArgIndex], OPTS_TAG_APP_CFG_FILENAME) == 0)
    {
      if ((ArgIndex + 1) < Argc)
      {
        strncpy_t(pApp->pAppConfigFilename, pArgv[ArgIndex + 1], CONFIG_NAME_MAX_LEN);
        GotAppConfigFilename = 1;
        break;
      }
      else
      {
        fprintf(stderr, "Error: expecting app config filename after %s tag\n",
                OPTS_TAG_APP_CFG_FILENAME);
        PrintUsage();
        goto Exit;
      }
    }
  }

  if (GotAppConfigFilename)
  {
    printf("Reading app configuration from %s...\n",
           pApp->pAppConfigFilename);
  }
  else
  {
    fprintf(stderr,
            "Error: app config file not specified - use \"%s <filename>\"\n",
            OPTS_TAG_APP_CFG_FILENAME);
    PrintUsage();
    goto Exit;
  }

  // Get stack config filename from input params
  GotStackConfigFilename = 0;
  for (ArgIndex = 0; ArgIndex < Argc; ArgIndex++)
  {
    if (strcmp(pArgv[ArgIndex], OPTS_TAG_STACK_CFG_FILENAME) == 0)
    {
      if ((ArgIndex + 1) < Argc)
      {
        strncpy_t(pApp->pStackConfigFilename, pArgv[ArgIndex + 1], CONFIG_NAME_MAX_LEN);
        GotStackConfigFilename = 1;
        break;
      }
      else
      {
        fprintf(stderr, "Error: expecting stack config filename after %s tag\n",
                OPTS_TAG_STACK_CFG_FILENAME);
        PrintUsage();
        goto Exit;
      }
    }
  }

  if (GotStackConfigFilename)
  {
    printf("Reading stack configuration from %s...\n",
           pApp->pStackConfigFilename);
  }
  else
  {
    strncpy_t(pApp->pStackConfigFilename, OPTS_DEFAULT_STACK_CFG_FILENAME, CONFIG_NAME_MAX_LEN);
    printf("Using default configuration file %s...\n",
           pApp->pStackConfigFilename);
  }

  // Get extra stack config filename from input params
  GotExtraConfigFilename = 0;
  for (ArgIndex = 0; ArgIndex < Argc; ArgIndex++)
  {
    if (strcmp(pArgv[ArgIndex], OPTS_TAG_EXTRA_CFG_FILENAME) == 0)
    {
      if ((ArgIndex + 1) < Argc)
      {
        strncpy_t(pApp->pExtraConfigFilename, pArgv[ArgIndex + 1], CONFIG_NAME_MAX_LEN);
        GotExtraConfigFilename = 1;
        break;
      }
      else
      {
        fprintf(stderr, "Error: expecting extra stack config filename after %s tag\n",
                OPTS_TAG_EXTRA_CFG_FILENAME);
        PrintUsage();
        goto Exit;
      }
    }
  }

  if (GotExtraConfigFilename)
  {
    printf("Reading extra stack configuration from %s...\n",
           pApp->pExtraConfigFilename);
    pApp->Cfg.ExtraConf = true;
  }

  // override limits
  for (ArgIndex = 0; ArgIndex < Argc; ArgIndex++)
  {
    if (strcmp(pArgv[ArgIndex], OPTS_TAG_OVERRIDE_LIMITS) == 0)
    {
      OverrideLimits = true;
    }
  }
  if (OverrideLimits)
  {
    printf("Overriding limits in configuration files...\n");
  }

  // Reset the application state
  Stat = App_Init(pApp);
  if (Stat != 0)
  {
    d_printf(D_ERR, NULL, "App_Init() failed, returned %d\n", Stat);
    goto Exit;
  }

  // Init thread attribute data
  Stat = Attr_Init(&Attr);
  if (Stat != 0)
  {
    d_printf(D_ERR, NULL, "Attr_Init() failed, returned %d\n", Stat);
    goto Exit;
  }

  // Set signal mask for other threads, and block
  sigemptyset(&SigSet);
  sigaddset(&SigSet, SIGINT);
  sigaddset(&SigSet, SIGTERM);
  sigaddset(&SigSet, SIGQUIT);
  sigaddset(&SigSet, SIGHUP);
  pthread_sigmask(SIG_BLOCK, &SigSet, NULL);

  /// Begin initialising and starting the stack library components
  printf("Initialising and starting stack components...\n");

  // Initialise libPlat
  tlibPlat_InitData libPlatInitData;

  if (pApp->Cfg.ExtraConf)
    libPlatInitData.pUserCfgFile = pApp->pExtraConfigFilename;
  else
    libPlatInitData.pUserCfgFile = NULL;

  libPlatInitData.pDefaultsCfgFile = pApp->pStackConfigFilename;
  libPlatInitData.AllowOutOfSpecValues = OverrideLimits;
  libPlatInitData.LimitOutOfSpecValues = false;

  Stat = libPlat_Init(&libPlatInitData);
  if (Stat != 0)
  {
    fprintf(stdout, "libPlat_Init() failed, returned %d\n", Stat);
    d_printf(D_ERR, NULL, "libPlat_Init() failed, returned %d\n", Stat);
    goto Exit;
  }

  // re-read the application configuration file and stash it in the log directory
  {
    config_t Config;
    config_init(&Config);
    if (config_read_file(&Config, pApp->pAppConfigFilename) == CONFIG_TRUE)
    {
      char Path[LOG_PATH_MAX+1];
      Log_GetLogDir(Path);
      (void)strncat(Path, "/cfg", LOG_PATH_MAX);
      Path[LOG_PATH_MAX] = '\0';
      int Res = config_write_file(&Config, Path);
      d_printf(D_INFO, NULL, "config_write_file(%p,%s): %s\n",
               &Config, Path, (Res == CONFIG_TRUE) ? "OK" : "Fail");
    }
    else
    {
      d_printf(D_WARN, NULL, "config_read_file(%p,%s): Failed!\n",
               &Config, pApp->pAppConfigFilename);
    }
    config_destroy(&Config);
  }

  GPSRX_LibraryInit();
  CANRx_LibraryInit();
  (void)LPH_Init();
  VState_LibraryInit();
  Ext_Init();

  #if defined(V2XATK)
  {
    ll_init = NULL;
    ll_get = NULL;

    // (pIni->ProtocolMode == default_stack_ProtocolMode_ITS)
    {
      void *pDLL = dlopen("libitsnet.so", RTLD_NOW | RTLD_LOCAL);
      if (pDLL != NULL)
      {
        ll_init = dlsym(pDLL, "g5_ll_init");
        ll_get  = dlsym(pDLL, "g5_ll_get");
        dlclose(pDLL);
      }
    }

    if ((ll_init == NULL) || (ll_get == NULL))
    {
      d_printf(D_ERR, NULL, "ll_init() or ll_get() unavailable\n");
      goto InitError;
    }
  }
  #endif

  tlibITSNet_InitData NetInitData;
  NetInitData.pMIBParams = NULL; // use config file

  // Initialise libITSNet
  Stat = libITSNet_Init(&NetInitData);
  if (Stat != 0)
  {
    fprintf(stdout, "libITSNet_Init() failed, returned %d\n", Stat);
    d_printf(D_ERR, NULL, "libITSNet_Init() failed, returned %d\n", Stat);
    goto InitError;
  }

  struct sigaction SigAct;

  memset(&SigAct, 0, sizeof(SigAct));
  SigAct.sa_handler = DummyHandler;

  // Install some dummy signal handlers
  if(sigaction(SIGINT,  &SigAct, NULL) == -1)
    d_error(D_ERR, NULL, "SIGACTION failed\n");
  if(sigaction(SIGTERM, &SigAct, NULL) == -1)
    d_error(D_ERR, NULL, "SIGACTION failed\n");
  if(sigaction(SIGQUIT, &SigAct, NULL) == -1)
    d_error(D_ERR, NULL, "SIGACTION failed\n");
  if(sigaction(SIGHUP,  &SigAct, NULL) == -1)
    d_error(D_ERR, NULL, "SIGACTION failed\n");

  // create signal processing thread
  Stat = pthread_create(&Signal_ThreadId, NULL, SignalThread, NULL);
  if (Stat)
  {
    d_error(D_WARN, NULL, "SignalThread create failed [%d] %s)\n",
            Stat, strerror(Stat));
    goto InitError;
  }

  // Initialise libITSFac
  Stat = libITSFac_Init(NULL);
  if (Stat != 0)
  {
    fprintf(stdout, "libITSFac_Init() failed, returned %d\n", Stat);
    d_printf(D_ERR, NULL, "libITSFac_Init() failed, returned %d\n", Stat);
    goto InitError;
  }

  // Start libPlat
  Stat = libPlat_Start();
  if (Stat != 0)
  {
    d_printf(D_ERR, NULL, "libPlat_Start() failed, returned %d\n", Stat);
    goto PlatStartError;
  }

  // Start plat worker threads
  LPH_ThreadInit      (SCHED_FIFO, THREAD_LOW_PRIORITY);
  VState_ThreadInit   (SCHED_FIFO, THREAD_LOW_PRIORITY);
  Ext_ThreadInit      (SCHED_FIFO, THREAD_LOW_PRIORITY);

  // Start all interface threads
  (void)GPSRX_ThreadInit(SCHED_FIFO, THREAD_NORMAL_PRIORITY);
  CANRx_ThreadInit(SCHED_FIFO, THREAD_LOW_PRIORITY);

  // Delay allows GPSRX/CANRX thread to perform basic init before next stages
  Util_Sleep(50);

  // Start libITSNet
  Stat = libITSNet_Start();
  if (Stat != 0)
  {
    d_printf(D_ERR, NULL, "libITSNet_Start failed, returned %d\n", Stat);
    goto NetStartError;
  }

  // Initialise the LDM (required before ITS-FAC)
  (void)LDM_Init();

  (void)IVI_Init();

  // Start libITSFac
  Stat = libITSFac_Start();
  if (Stat != 0)
  {
    d_printf(D_ERR, NULL, "libITSFac_Start failed, returned %d\n", Stat);
    goto FLStartError;
  }

  int Ret;

  // HMI
  Ret = HMI_Open(&pApp->pHMI, GetHeartBeatInfo, pApp);
  if (Ret != HMI_ERR_NONE)
  {
    d_error(D_ERR, NULL, "HMI Open Error [%d]", Ret);
    goto HMIOpenError;
  }

  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_EEBL,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0,
                     190,
                     "./ui/EEBL/EEBL.gif",
                     "./ui/EEBL/EEBL.wav",
                     "BRAKE!");
  // FCW alert severity range is from 81:95
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_FCW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     81,
                     85,
                     "./ui/FCW/FCW_track.gif",
                     "",
                     "Forward Collision Ahead");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_FCW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     86,
                     90,
                     "./ui/FCW/FCW_mid.gif",
                     "./ui/FCW/FCW.wav",
                     "Forward Collision Ahead");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_FCW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     91,
                     95,
                     "./ui/FCW/FCW_high.gif",
                     "./ui/FCW/FCW.wav",
                     "Forward Collision Ahead");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_ICW,
                     HMI_ALERT_DIRECTION_LEFT,
                     0,
                     255,
                     "./ui/ICW/ICW_left.gif",
                     "./ui/ICW/ICW.wav",
                     "Oncoming Left Vehicle");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_ICW,
                     HMI_ALERT_DIRECTION_RIGHT,
                     0,
                     255,
                     "./ui/ICW/ICW_right.gif",
                     "./ui/ICW/ICW.wav",
                     "Oncoming Right Vehicle");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_TJA,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     1,
                     255,
                     "",
                     "",
                     "Traffic Jam");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_RLW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     255,
                     "./ui/RLW/RLW.png",
                     "./ui/FCW/FCW.wav",
                     "STOP!");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_GREEN_PHASE,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     250,
                     "./ui/GLOSA/GLOSA_Green.png",
                     "",
                     "");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_YELLOW_PHASE,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     250,
                     "./ui/GLOSA/GLOSA_Yellow.png",
                     "",
                     "");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_RED_PHASE,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     250,
                     "./ui/GLOSA/GLOSA_Red.png",
                     "",
                     "");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_ROADWORK,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0,
                     190,
                     "./ui/RWW/RWW.png",
                     "./ui/ping.wav",
                     "Roadwork");
  // speed limit warning for roadworks etc
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_SPEEDLIMIT,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0, 100,
                     "", // no icon
                     "./ui/FCW/FCW.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_HLW_FOG,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0,
                     190,
                     "./ui/Other/Other.png",
                     "./ui/Other/Other.wav",
                     "Warning");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_LTA,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0, 255,
                     "./ui/Other/Other.png",
                     "./ui/ICW/ICW.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_BSW_LCW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0, 255,
                     "./ui/LCW/LCW.png",
                     "./ui/ping.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_DNPW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0, 255,
                     "./ui/DNPW/DNPW.png",
                     "./ui/ping.wav",
                     "Do not pass!");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_HLW_RAIN,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0,
                     190,
                     "./ui/Other/Other.png",
                     "./ui/Other/Other.wav",
                     "Warning");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_HLW_TRC,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     0,
                     190,
                     "./ui/Other/Other.png",
                     "./ui/Other/Other.wav",
                     "Warning");
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_IVS,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     255,
                     "./ui/Other/Other.png",
                     "./ui/ping.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_EVW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     255,
                     "./ui/EVW/EVW.png",
                     "./ui/EVW/EVW.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_SVA,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50, // Cohda_App_SVA.REC_SEVERITY_MIN
                     255, // Cohda_App_SVA.REC_SEVERITY_MAX
                     "./ui/Other/Other.png",
                     "./ui/ping.wav",
                     ""); // use dynamic text
  HMI_AddAlertConfig(pApp->pHMI,
                     HMI_ALERT_TYPE_IHW,
                     HMI_ALERT_DIRECTION_UNKNOWN,
                     50,
                     255,
                     "./ui/Other/Other.png",
                     "./ui/ping.wav",
                     ""); // use dynamic text

  // Target classification
  Ret = TC_Init(NULL);
  if (Ret != TC_ERR_NONE)
  {
    d_error(D_ERR, NULL, "TC Init Error [%d] %s",
            Ret,
            TC_ErrToStr(Ret));
    goto TCInitError;
  }

  // Threat Management
  Ret = TM_Init(NULL, TACallback, pApp->pHMI);
  if (Ret != TM_ERR_NONE)
  {
    d_error(D_ERR, NULL, "TM Init Error [%d] %s",
            Ret,
            TM_ErrToStr(Ret));
    goto TMInitError;
  }

  // Threat assessment
  tdefault_stack_Cohda_TA * pTAParams = NULL;
  // this is where pTAParams could be overridden from the libconfig file
  // or (preferably) use @ref Conf2_ParseLinesFmt

  // report alerts to HMI
  // no callback available to get active alert
  Ret = TA_Init(pTAParams,
                TM_AlertCallback, pApp->pHMI,
                TM_CurrentAlert,  NULL);
  if (Ret != TA_ERR_NONE)
  {
    d_error(D_ERR, NULL, "TA Init Error [%d] %s",
            Ret,
            TA_ErrToStr(Ret));
    goto TAOpenError;
  }

  // Start the application threads

  if (pApp->Cfg.ITS)
  {
    d_printf(D_INFO, NULL, "Open ITS...\n");
    ErrCode = ITSCtrl_Open(&(pApp->Hdl.ITS), &Attr,
                           pApp->pAppConfigFilename);
    if (ErrCode != 0)
    {
      d_printf(D_ERR, NULL, "ITS Open Error [%d] %s\n", ErrCode,
               strerror(ErrCode));
      goto FLInitError;
    }
    else
    {
      d_printf(D_INFO, NULL, "ITS Opened OK\n");
    }
  }
  else
  {
    d_printf(D_INFO, NULL, "ITS Not Opened\n");
  }

  if (pApp->Cfg.RAWIts)
  {
    d_printf(D_INFO, NULL, "Open RAWIts...\n");
    ErrCode = RAWIts_Open(&(pApp->Hdl.RAWIts), &Attr,
                          pApp->pAppConfigFilename);
    if (ErrCode != 0)
    {
      d_printf(D_ERR, NULL, "RAWIts Open Error [%d] %s\n", ErrCode,
               strerror(ErrCode));
      goto FLInitError;
    }
    else
    {
      d_printf(D_INFO, NULL, "RAWIts Opened OK\n");
    }
  }

  if (pApp->Cfg.CANVSC3)
  {
    d_printf(D_INFO, NULL, "Open CAN VSC3 Lib...\n");
    CANVSC3_LibraryInit ();
  }

  if (pApp->Cfg.CANVState)
  {
    d_printf(D_INFO, NULL, "Open CANVState...\n");
    ErrCode = CANVState_Open(&(pApp->Hdl.pCANVState), &Attr,
                             pApp->pAppConfigFilename);
    if (ErrCode != 0)
    {
      d_printf(D_ERR, NULL, "CANVState Open Error [%d] %s\n", ErrCode,
               strerror(ErrCode));
      goto FLInitError;
    }
    else
    {
      d_printf(D_INFO, NULL, "CANVState Opened OK. (pCANVState=%p)\n",
               pApp->Hdl.pCANVState);
    }
  }

  if (pApp->Cfg.CAN)
  {
    d_printf(D_INFO, NULL, "Open CAN...\n");
    ErrCode = CAN_Open(&(pApp->Hdl.CAN), &Attr,
                       pApp->pAppConfigFilename);
    if (ErrCode != 0)
    {
      d_printf(D_ERR, NULL, "CAN Open Error [%d] %s\n", ErrCode,
               strerror(ErrCode));
      goto FLInitError;
    }
    else
    {
      d_printf(D_INFO, NULL, "CAN Opened OK\n");
    }
  }

  if (pApp->Cfg.PosExt)
  {
    d_printf(D_INFO, NULL, "Open PosExt...\n");
    ErrCode = PosExt_Init();
    if (ErrCode != 0)
    {
      d_printf(D_ERR, NULL, "PosExt Open Error [%d] %s\n", ErrCode,
               strerror(ErrCode));
      goto FLInitError;
    }
    else
    {
      d_printf(D_INFO, NULL, "PosExt Opened OK.\n");
    }
  }

  // Finally the plugins
  Stat = Plugin_Init();
  if (Stat != 0)
  {
    d_printf(D_CRIT, NULL, "Plugin_Init() = %d\n", Stat);
    goto PluginInitError;
  }

  // Running
  libPlat_Running();

  // Wait for signal handler to exit threads
  (void) pthread_join(Signal_ThreadId, NULL);

  goto Exit;

PluginInitError:
FLInitError:
  TA_Exit();
TAOpenError:
  TM_Exit();
TMInitError:
  TC_Exit();
TCInitError:
  HMI_Close(pApp->pHMI);
HMIOpenError:
  libITSFac_Stop();
FLStartError:
  IVI_Deinit();
  LDM_Deinit();
NetStartError:
  libITSNet_Stop();
  libPlat_Stop();
PlatStartError:
  (void)libITSFac_DeInit();
InitError:
  (void)libITSNet_DeInit();
  (void)libPlat_DeInit();
Exit:
  return 0;
}

/**
 * @brief Initialise the pthread attributes
 * @param pAttr Pointer to pthread attribute data
 * @return 0 on success, error code on error
 */
static int Attr_Init(pthread_attr_t *pAttr)
{
  int Res;

  Res = pthread_attr_init(pAttr);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "pthread_attr_init failed [%d] %s\n",
             Res, strerror(Res));
    goto Exit;
  }

  #ifndef __aarch64__
  Res = pthread_attr_setinheritsched(pAttr, PTHREAD_EXPLICIT_SCHED);
  if (Res)
  {
    d_printf(D_ERR, NULL, "pthread_attr_setinheritsched failed [%d] %s\n",
             Res, strerror(Res));
    goto Exit;
  }
  #endif

  Res = pthread_attr_setstacksize(pAttr, APP_THREAD_STACK_SIZE);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "pthread_attr_setstacksize failed [%d,%d] %s\n",
             Res, APP_THREAD_STACK_SIZE, strerror(Res));
    goto Exit;
  }

  Res = pthread_attr_setschedpolicy(pAttr, SCHED_FIFO);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "pthread_attr_setschedpolicy failed [%d] %s\n",
             Res, strerror(Res));
    goto Exit;
  }

  struct sched_param Param = { 0 };
  Param.sched_priority = sched_get_priority_min(SCHED_FIFO);

  Res = pthread_attr_setschedparam(pAttr, &Param);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "pthread_attr_setschedparam failed [%d] %s\n",
             Res, strerror(Res));
    goto Exit;
  }

  Res = pthread_attr_setdetachstate(pAttr, PTHREAD_CREATE_JOINABLE);
  if (Res != 0)
  {
    d_printf(D_ERR, NULL, "pthread_attr_setdetachstate failed [%d] %s\n",
             Res, strerror(Res));
    goto Exit;
  }

Exit:
  return Res;
}

/**
 * @brief Initialise the application (parse application configuration)
 * @param pApp Pointer to application data
 * @return 0 on success, error code on error
 */
int App_Init (tApp *pApp)
{
  int Res = -ENOSYS; // return error code
  config_t Config; // configuration object read from config file
  config_t * pConfig;
  int ConfigVal = 0; // temporary variable to store config words
  const config_setting_t *pSetting;

  d_fnstart(D_DEBUG, NULL, "(%p)\n", pApp);

  pConfig = &Config;

  // Set some default values (all disabled)
  pApp->Cfg.CAN = false;
  pApp->Cfg.ITS = false;
  pApp->Cfg.RAWIts = false;
  pApp->Cfg.CANVSC3= false;
  pApp->Cfg.CANVState = false;
  pApp->Cfg.PosExt = false;

  // Read settings from config file

  config_init(pConfig); // initialise the config object

  // Try to read the specified config file into the config object
  if (config_read_file(pConfig, pApp->pAppConfigFilename) != CONFIG_TRUE)
  {
    d_printf(D_ERR, NULL, "Could not open %s\n", pApp->pAppConfigFilename);
    d_printf(D_ERR, NULL, "libconfig: %s at line %d\n",
             config_error_text(pConfig), config_error_line(pConfig));
    Res = -EBADFD;
    goto Error;
  }

  // Get the application Setting
  pSetting = config_lookup(pConfig, "Example");
  if (pSetting == NULL)
  {
    Res = -ESRCH;
    d_printf(D_WARN, 0, "Missing 'Example' member in %s\n", pApp->pAppConfigFilename);
    goto Error;
  }

  // Config is open, now look for configuration entries

#define SET_BOOL(x)                                     \
  do                                                    \
  {                                                     \
    if (config_lookup_bool                              \
        (pConfig, "Example." #x ".Enable", &ConfigVal)) \
    {                                                   \
      pApp->Cfg.x = (bool) ConfigVal;                   \
      d_printf(D_INTERN, 0,                             \
               #x ": %d\n", ConfigVal);                 \
    }                                                   \
    else                                                \
    {                                                   \
      pApp->Cfg.x = false;                              \
    }                                                   \
  }                                                     \
  while(0)

  SET_BOOL(CAN);
  SET_BOOL(CANVSC3);
  SET_BOOL(CANVState);
  SET_BOOL(ITS);
  SET_BOOL(RAWIts);
  SET_BOOL(PosExt);

#undef SET_BOOL

  // Success!
  Res = 0;

Error:
  // Update complete - close the configuration
  config_destroy(pConfig);

  d_fnend(D_DEBUG, NULL, "() = %d\n", Res);
  return Res;
}

/**
 * @brief Print basic help type message for application usage
 */
static void PrintUsage (void)
{
  fprintf(stderr, "Usage:\n  exampleETSI %s <application configuration> [%s <stack configuration>] [%s <extra stack configuration>]\n",
          OPTS_TAG_APP_CFG_FILENAME, OPTS_TAG_STACK_CFG_FILENAME, OPTS_TAG_EXTRA_CFG_FILENAME);
}

/**
 * @brief Stop threads, shutdown stack and free any memory
 */
static void App_Exit (void)
{
  tApp *pApp = &_App;

  d_fnstart(D_DEBUG, NULL, "()\n");

  // set the global shutdown flag
  Util_SetShutdownFlagBecause("App Exit");

  Plugin_Exit();

  TA_Exit();
  TM_Exit();

  IVI_Deinit();

  TC_Exit();

  HMI_Close(pApp->pHMI);

  if (pApp->Cfg.ITS)
  {
    ITSCtrl_Close(&(pApp->Hdl.ITS));
  }
  if (pApp->Cfg.RAWIts)
  {
    RAWIts_Close(&(pApp->Hdl.RAWIts));
  }
  if (pApp->Cfg.CAN)
  {
    CAN_Close(&(pApp->Hdl.CAN));
  }
  if (pApp->Cfg.CANVSC3)
  {
    CANVSC3_LibraryDeinit();
  }
  if (pApp->Hdl.pCANVState)
  {
    CANVState_Close(pApp->Hdl.pCANVState);
    pApp->Hdl.pCANVState = NULL;
  }
  if (pApp->Cfg.PosExt)
  {
    PosExt_DeInit();
  }

  // Tidy up
  (void) pthread_attr_destroy(&Attr);

  /// Close down all the stack component threads

  // Shutdown all interface threads
  (void)CANRx_ThreadDeinit();
  (void)GPSRX_ThreadDeinit();

  // Close down the ITS Library
  (void)libITSFac_Stop();
  (void)libITSNet_Stop();

  LDM_Deinit();

  // Shutdown all worker threads
  (void)Ext_ThreadDeinit();
  (void)VState_ThreadDeinit();
  (void)LPH_ThreadDeinit();

  (void)libPlat_Stop();

  (void)libITSFac_DeInit();
  (void)libITSNet_DeInit();

  // Library de-initialisations
  Ext_Exit();
  CANRx_LibraryDeinit();
  GPSRX_LibraryDeinit();
  VState_LibraryDeinit();
  LPH_Exit();

  (void)libPlat_DeInit();

  d_fnend(D_DEBUG, NULL, "()\n");

  return;
}

/**
 * @brief Dummy Signal Handler
 *
 * Should do nothing, but if a signal arrives send it to the Signal handler thread
 */
static void DummyHandler(int Sig)
{
  d_printf(D_DEBUG, NULL, "Handler SIG: %d\n", Sig);
  (void) pthread_kill(Signal_ThreadId, Sig);
}

/**
 * @brief Timeout Signal Handler
 *
 * Used after graceful exit timeout
 */
static void TimeoutHandler(sigval_t SigVal)
{
  (void)SigVal;

  // For user's benefit
  printf("Force Shutdown: Timeout\n");

  // For log
  d_error(D_ERR, NULL, "Force Shutdown: Timeout\n");

  // Attempt to shutdown libPlat
  // tcpdump logging needs to be terminated
  (void)libPlat_Stop();
  (void)libPlat_DeInit();

  printf("Force Shutdown: Exit\n");

  exit(1);
}

/**
 * @brief Signal Handler thread
 *
 * Calls thread's DeInit functions
 */
void *SignalThread(void *pArg)
{
  (void)pArg;

  // Timer info
  timer_t ShutdownTimerId;
  struct itimerspec ShutdownT;
  struct sigevent ShutdownEvt;

  int SigThread = 1;
  int SigCount = 0;
  int TStat;

  while (SigThread == 1)
  {
    int Sig;

    // wait for any signal
    sigfillset(&SigSet);
    sigwait(&SigSet, &Sig);

    d_printf(D_DEBUG, NULL, "SIG: %d\n", Sig);

    // and handle it
    switch(Sig)
    {
      case SIGHUP:
      case SIGINT:
      case SIGTERM:
      case SIGQUIT:
        if (SigCount > 0)
        {
          // Force exit
          (void)timer_delete(ShutdownTimerId);
          printf("Forced exit on signal %d\n", Sig);
          exit(1);
        }
        else
        {
          // Graceful exit
          printf("Exiting on signal %d\n", Sig);

          d_printf(D_NOTICE, NULL, "Shutdown signal (%d)\n", Sig);

          // Create timer for shutdown limit time
          memset(&ShutdownEvt, 0, sizeof(ShutdownEvt));

          // Timer handler action
          ShutdownEvt.sigev_notify          = SIGEV_THREAD;
          ShutdownEvt.sigev_notify_function = TimeoutHandler;

          TStat = timer_create(CLOCK_REALTIME, &ShutdownEvt, &ShutdownTimerId);
          if (TStat != 0)
            d_error(D_WARN, NULL, "Timer create failed (errno %d, %s)\n",
                    errno, strerror(errno));

          ShutdownT.it_interval.tv_sec  = 0;
          ShutdownT.it_interval.tv_nsec = 0;
          ShutdownT.it_value.tv_sec     = 9;
          ShutdownT.it_value.tv_nsec    = 0;
          TStat = timer_settime(ShutdownTimerId,
                                0,
                                &ShutdownT,
                                NULL);

          if (TStat != 0)
            d_error(D_WARN, NULL, "Timer start failed (errno %d, %s)\n",
                    errno, strerror(errno));

          // Exit app
          App_Exit();

          SigThread = 0;
        }
        SigCount++;
        break;

      default:
        d_error(D_WARN, NULL, "Caught signal %d - no action\n", Sig);
        break;
    }
  }

  (void)timer_delete(ShutdownTimerId);
  pthread_exit(NULL);
}

/**
 * @brief TA callback handler
 * @param pAlert Pointer to Alert information
 * @param pParam Additional TA information (HMI handle)
 *
 */
static void TACallback(const tTAAlert *pAlert,
                       void *pParam)
{
  struct HMI *pHMI = (struct HMI *)pParam;
  char AlertStr[ALERT_STR_SIZE] = {0,};
  struct timeval now;
  (void)gettimeofday(&now,0);

  d_fnstart(D_WARN, 0, "(%p{%08"PRIx32"(%s),%3d,%f,%f}) @ %ld.%06ld\n",
            pAlert,
            pAlert->Type,
            TA_ThreatType(pAlert->Type),
            pAlert->Level,
            pAlert->TimeToEvent_s,
            pAlert->DistanceToEvent_m,
            (long)now.tv_sec, (long)now.tv_usec);

  // A cancel is signified by a level of 0
  if (pAlert->Level == 0)
  {
    (void)HMI_CancelAlerts(pHMI);
    goto Exit;
  }

  switch(pAlert->Type)
  {
    case TA_THREATTYPE_NONE:
    {
      d_printf(D_WARN, NULL,"TA_THREATTYPE_NONE\n");
    }
    break;
    case TA_THREATTYPE_EEBL:
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_EEBL,
                      HMI_ALERT_DIRECTION_UNKNOWN,
                      pAlert->Level,
                      NULL,
                      pAlert->DistanceToEvent_m);
      break;

    case TA_THREATTYPE_FCW:
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_FCW,
                      HMI_ALERT_DIRECTION_UNKNOWN,
                      pAlert->Level,
                      NULL,
                      pAlert->DistanceToEvent_m);
      break;

    case TA_THREATTYPE_HLW_FOG:
      snprintf(AlertStr, ALERT_STR_SIZE, "HLW FOG in %dm", (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_HLW_FOG: %x\n", pAlert->Type);
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_HLW_FOG,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
      break;

    case TA_THREATTYPE_HLW_RAIN:
      snprintf(AlertStr, ALERT_STR_SIZE, "HLW RAIN in %dm", (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_HLW_RAIN: %x\n", pAlert->Type);
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_HLW_RAIN,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
      break;

    case TA_THREATTYPE_HLW_TRC:
      snprintf(AlertStr, ALERT_STR_SIZE, "HLW TRC in %dm", (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_HLW_TRC: %08"PRIx32"\n", pAlert->Type);
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_HLW_TRC,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
      break;

    case TA_THREATTYPE_ICW:
    {
      tHDU ThreatBearing;
      tSafetyZone SafetyZone;
      tHMIAlertDirection Direction;
      tTASeverity Level = pAlert->Level;
      tHMIAlertConfig *pConfig;
      tHMIErrCode Err;
      char Warning[1024];
      char *pText = NULL;

      SafetyZone = pAlert->ICW.SafetyZone;
      ThreatBearing = pAlert->ICW.ThreatBearing;

      // figure out which direction flag to use
      if (ThreatBearing > SafetyZone.SouthEast)
        // Rear (tracking only, no icon nor audio)
        Direction = HMI_ALERT_DIRECTION_UNKNOWN;
      else
        if (ThreatBearing > SafetyZone.NorthEast)
          // Right
          Direction = HMI_ALERT_DIRECTION_RIGHT;
        else
          if (ThreatBearing > SafetyZone.NorthWest)
            // Front (should not get here)
            Direction = HMI_ALERT_DIRECTION_UNKNOWN;
          else
            if (ThreatBearing > SafetyZone.SouthWest)
              // Left
              Direction = HMI_ALERT_DIRECTION_LEFT;
            else
              // Rear (tracking only, no icon nor audio)
              Direction = HMI_ALERT_DIRECTION_UNKNOWN;

      // add direction to warning text if has a %s or remove %s from warning text
      // if no direction flag is present
      Err = HMI_GetAlertConfig(pHMI, HMI_ALERT_TYPE_ICW, Direction, Level, &pConfig);
      if (Err == HMI_ERR_NONE)
      {
        if (pConfig)
        {
          unsigned int i, NumPC = 0;

          // replace %s placeholder in pText if it is provided with direction
          for (i = 0; pConfig->pText != NULL && i < strlen(pConfig->pText); i++)
          {
            if (pConfig->pText[i] == '%')
            {
              NumPC++;
            }
          }

          // allow one format directives - must be %s
          if (NumPC == 1 && strstr(pConfig->pText, "%s") != NULL)
          {
            snprintf(Warning, sizeof(Warning), pConfig->pText,
                     (Direction == HMI_ALERT_DIRECTION_LEFT ? "Left" :
                      (Direction == HMI_ALERT_DIRECTION_RIGHT ? "Right" :
                       "")));

            pText = Warning;
          }

          HMI_FreeAlertConfig(pConfig);
        }
      }
      else
      {
        d_printf(D_WARN, NULL, "Error getting ICW alert config: %d\n", Err);
      }

      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_ICW,
                      Direction,
                      Level,
                      pText,
                      pAlert->DistanceToEvent_m);
    }
    break;
    case TA_THREATTYPE_SVA_AIR:
    case TA_THREATTYPE_SVA_HZR:
    case TA_THREATTYPE_SVA_BRK:
    {
      snprintf(AlertStr, ALERT_STR_SIZE, "SVA in %dm", (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_SVA: %08"PRIx32"\n", pAlert->Type);
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_SVA,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    }
    break;
    case TA_THREATTYPE_EVW:
    {
      // ↑ ↗ → ↘ ↓ ↙ ← ↖
      uint32_t Slice = TC_HeadingToSlice(pAlert->Azimuth);
      const char *pDirection = "!";
      if (Slice & 0xc0000003)
        pDirection = "↑";
      if (Slice & 0x0000003c)
        pDirection = "↗";
      if (Slice & 0x000003c0)
        pDirection = "→";
      if (Slice & 0x00003c00)
        pDirection = "↘";
      if (Slice & 0x0003c000)
        pDirection = "↓";
      if (Slice & 0x003c0000)
        pDirection = "↙";
      if (Slice & 0x03c00000)
        pDirection = "←";
      if (Slice & 0x3c000000)
        pDirection = "↖";

      snprintf(AlertStr, ALERT_STR_SIZE, "EVW %s %dm", pDirection, (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_EVW\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_EVW,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    }
    break;
    case TA_THREATTYPE_TJA:
        {
          snprintf(AlertStr, ALERT_STR_SIZE, "TJA in %dm", (int)pAlert->DistanceToEvent_m);
          d_printf(D_WARN, NULL,"TA_THREATTYPE_TJA\n");
          (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_TJA,
                          HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                          pAlert->DistanceToEvent_m);
        }
    break;
    case TA_THREATTYPE_RWW:
    {
      size_t Len = 0;
      if (pAlert->RWW.SpeedLimitApplicable)
      {
        Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                 "%ukmh ", pAlert->RWW.SpeedLimit_kmph);
        AlertStr[sizeof(AlertStr) - 1] = '\0';
      }

      if (pAlert->RWW.RWWDirection == 0 /* RWW_AHEAD */)
      {
        Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                        "Start %dm ",
                       (int)pAlert->RWW.Distance2RWW_mm / 1000);
      }
      else if (pAlert->RWW.RWWDirection == 1 /* RWW_BEHIND */)
      {
        Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                        "End %dm ",
                       (int)pAlert->RWW.Distance2EndRWW_mm / 1000);
      }

      AlertStr[sizeof(AlertStr) - 1] = '\0';

      if (pAlert->RWW.RWWDirection == 1 /* RWW_BEHIND */)
      {
        // For LHD vehicles
        if (pAlert->RWW.InnerHardShoulderStatus >= 0)
        {
          Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                          "|%s|", (pAlert->RWW.InnerHardShoulderStatus == 2 ? "↑" :
                                 (pAlert->RWW.InnerHardShoulderStatus == 1 ? "T" :
                                  "_")));
        }
        int i;
        for (i = pAlert->RWW.NumberOfLanes - 1; i >= 0; i--)
        {
          uint8_t NumBytes = (uint8_t)((pAlert->RWW.NumberOfLanes+7)/8);
          uint8_t Lane = (pAlert->RWW.ClosedLanes >> (((NumBytes*8) - 1) - (i + 1))) & 0x1;
          Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                          "|%s", Lane ? "T" : "↑");
          AlertStr[sizeof(AlertStr) - 1] = '\0';
        }
        Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len, "|");
        AlertStr[sizeof(AlertStr) - 1] = '\0';
        // add hardshoulder bit
        if (pAlert->RWW.OuterHardShoulderStatus >= 0)
        {
          Len += snprintf(AlertStr + Len, sizeof(AlertStr) - Len,
                          "|%s|", (pAlert->RWW.OuterHardShoulderStatus == 2 ? "↑" :
                                 (pAlert->RWW.OuterHardShoulderStatus == 1 ? "T" :
                                  "_")));
        }
        // TODO: For RHD vehicles
        (void)Len;
      }

      d_printf(D_WARN, NULL,"TA_THREATTYPE_RWW\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_ROADWORK,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    }
    break;
    case TA_THREATTYPE_SVW:
    {
      d_printf(D_WARN, NULL,"TA_THREATTYPE_SVW\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_RLW,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, NULL,
                      pAlert->DistanceToEvent_m);
    }
    break;
    case TA_THREATTYPE_GLOSA:
    {
      tHMIAlertType Type = -1;
      uint32_t TimeToChange = (pAlert->GLOSA.TimeChange_ds / 10);
      // Max at sensible limit
      if (TimeToChange > 120)
      {
        TimeToChange = 120;
      }
      int32_t Distance = ((int)pAlert->DistanceToEvent_m / 10) * 10;
      float Speedmps = pAlert->GLOSA.CurSpeed_mps;
      int LaneId = pAlert->GLOSA.LaneId;
      char *pText = NULL;

      d_printf(D_WARN, NULL,"TA_THREATTYPE_GLOSA\n");
      switch (pAlert->GLOSA.CurrentPhase)
      {
        case TA_SIGCOLOR_GREEN:
        {
          Type = HMI_ALERT_TYPE_GREEN_PHASE;
        }
        break;
        case TA_SIGCOLOR_YELLOW:
        {
          Type = HMI_ALERT_TYPE_YELLOW_PHASE;
        }
        break;
        case TA_SIGCOLOR_RED:
        {
          Type = HMI_ALERT_TYPE_RED_PHASE;
        }
        break;
        default:
        {
          Type = -1;
        }
      }
      if (Type == (tHMIAlertType)-1)
      {
        break;
      }

      // Determine 'speed up/slow down' based on S(adv)
      uint16_t AdvSpeed_KPH;
      if (Speedmps > 0)
      {
        AdvSpeed_KPH = (uint16_t)(Speedmps * MPS_TO_KPH);
      }
      else
      {
        AdvSpeed_KPH = 0;
      }

      uint16_t SpeedLimit_KPH = 80;
      float MaxAccel_mps2 = 1.66;

      d_printf(D_INFO, NULL, "GLOSA: Speed %.1f, Light %d\n",
               Speedmps, pAlert->GLOSA.CurrentPhase);

      if ((Speedmps >= 0) && (Speedmps < 1))
      {
        // Time to change
        d_printf(D_NOTICE, NULL, "WAIT at Light: (Dist %dm, Time %ds, Lane %d)\n",
            Distance, TimeToChange, LaneId);

        if (((pAlert->GLOSA.CurrentPhase == TA_SIGCOLOR_GREEN) ||
             (pAlert->GLOSA.CurrentPhase == TA_SIGCOLOR_RED)) &&
            (Distance < 50))
        {
          pText = xxprintf("change %ds (%dm,L%d)",
                           TimeToChange,
                           Distance,
                           LaneId);
          (void)HMI_Alert(pHMI, Type,
                          HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, pText,
                          pAlert->DistanceToEvent_m);
          free(pText);
        }
      }
      else if (Speedmps > 2.7)
      {
        // GLOSA
        if (pAlert->GLOSA.CurrentPhase == TA_SIGCOLOR_RED)
        {
          if (Speedmps > pAlert->GLOSA.AdvSpeed_mps)
          {
            if (MaxAccel_mps2 > pAlert->GLOSA.AdvAccel_mps2)
            {
              if (AdvSpeed_KPH > SpeedLimit_KPH)
              {
                d_printf(D_WARN, NULL, "RED Light: Advised %u > Speed limit %u, slow down\n",
                         AdvSpeed_KPH, SpeedLimit_KPH);

                AdvSpeed_KPH = SpeedLimit_KPH;
              }
              else
              {
                d_printf(D_NOTICE, NULL, "RED Light: Setting advised speed %u\n",
                    AdvSpeed_KPH);
              }
            }
            else
            {
              // calculate an advised speed based on the maximum acceleration
              AdvSpeed_KPH = (MaxAccel_mps2 * (pAlert->GLOSA.TimeChange_ds / 10.0) + Speedmps) * MPS_TO_KPH;

              if (AdvSpeed_KPH > SpeedLimit_KPH)
              {
                AdvSpeed_KPH = SpeedLimit_KPH;
              }

              d_printf(D_INFO, NULL, "RED Light: Limit advised speed (%f, %.1f, %d)\n",
                       MaxAccel_mps2, (pAlert->GLOSA.TimeChange_ds / 10.0), AdvSpeed_KPH);
            }
          }
          else
          {
            d_printf(D_NOTICE, NULL, "RED Light: safe, speed < advised\n");
            AdvSpeed_KPH = (int)(Speedmps * 3.6);
            // Indicate green will appear
            Type = HMI_ALERT_TYPE_GREEN_PHASE;
          }

          if (AdvSpeed_KPH > 0)
          {
            pText = xxprintf("adv %dkm/h (%ds,%dm,L%d),", AdvSpeed_KPH, TimeToChange, Distance, LaneId);
          }
          else
          {
            pText = xxprintf("change %ds (%dm,L%d)", TimeToChange, Distance, LaneId);
          }

          (void)HMI_Alert(pHMI, Type,
                          HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, pText,
                          pAlert->DistanceToEvent_m);
          free(pText);
        }
        else if (pAlert->GLOSA.CurrentPhase == TA_SIGCOLOR_YELLOW)
        {
          // No advice
        }
        else if (pAlert->GLOSA.CurrentPhase == TA_SIGCOLOR_GREEN)
        {
          // Determine 'prepare to stop' based on S(stop_check)
          float AdvStopSpeed_mps = pAlert->DistanceToEvent_m / (pAlert->GLOSA.TimeChange_ds / 10.0);
          float AdvStopAcc_mps2 = (2 * (pAlert->DistanceToEvent_m - (Speedmps * (pAlert->GLOSA.TimeChange_ds / 10.0))) /
                                   ((pAlert->GLOSA.TimeChange_ds / 10.0) * (pAlert->GLOSA.TimeChange_ds / 10.0)));
          uint16_t AdvStopSpeed_KPH = (uint16_t)(AdvStopSpeed_mps * MPS_TO_KPH);

          d_printf(D_NOTICE, NULL, "GREEN light: Speed %.2f, AdvisedSpeed %.2f, AdvisedAcc %.2f "
                                 "(StopSpeed %.2f, StopAcc %.2f)\n",
              Speedmps,
              pAlert->GLOSA.AdvSpeed_mps,
              pAlert->GLOSA.AdvAccel_mps2,
              AdvStopSpeed_mps,
              AdvStopAcc_mps2);

          if ((AdvStopSpeed_KPH > SpeedLimit_KPH) ||
              (AdvStopAcc_mps2 > MaxAccel_mps2))
          {
            // Speed / accel too high
            d_printf(D_NOTICE, NULL, "RED Light: Accel too high (%.2f/%.2f)\n",
                     AdvStopSpeed_mps,
                     AdvStopAcc_mps2);

            Type = HMI_ALERT_TYPE_RED_PHASE;
          }
          else
          {
            if (pAlert->GLOSA.AdvAccel_mps2 < MaxAccel_mps2)
            {
              d_printf(D_NOTICE, NULL, "GREEN Light: Accel acceptable (%.2f < %.2f)\n",
                       pAlert->GLOSA.AdvAccel_mps2,
                       MaxAccel_mps2);

              if (Speedmps < pAlert->GLOSA.AdvSpeed_mps)
              {
                if (AdvSpeed_KPH > SpeedLimit_KPH)
                {
                  // advised speed higher than limit
                  d_printf(D_ERR, NULL, "GREEN Light: advised %u > limit %u\n",
                           AdvSpeed_KPH, SpeedLimit_KPH);
                  AdvSpeed_KPH = 0;
                }
                else
                {
                  d_printf(D_NOTICE, NULL, "GREEN Light: Setting advised speed %u\n",
                           AdvSpeed_KPH);
                }
              }
              else
              {
                d_printf(D_NOTICE, NULL, "GREEN Light: speed %u > advised %d (limit %u)\n",
                         (int)(Speedmps * 3.6), AdvSpeed_KPH, SpeedLimit_KPH);

                if (AdvSpeed_KPH > SpeedLimit_KPH)
                {
                  AdvSpeed_KPH = SpeedLimit_KPH;
                }
              }
            }
            else
            {
              d_printf(D_WARN, NULL,
                       "GREEN Light: Accel required too high %f, max(%f)\n",
                       pAlert->GLOSA.AdvAccel_mps2,
                       MaxAccel_mps2);
              AdvSpeed_KPH = 0;
              // Indicate should stop
              Type = HMI_ALERT_TYPE_RED_PHASE;
            }
          }

          if (AdvSpeed_KPH > 0)
          {
            pText = xxprintf("adv %dkm/h (%ds,%dm,L%d),", AdvSpeed_KPH, TimeToChange, Distance, LaneId);
          }
          else
          {
            pText = xxprintf("change %ds (%dm,L%d)", TimeToChange, Distance, LaneId);
          }
          (void)HMI_Alert(pHMI, Type,
                          HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, pText,
                          pAlert->DistanceToEvent_m);
          free(pText);
        }
      }
    }
    break;
    case TA_THREATTYPE_IHW:
    {
      if (pAlert->IHW.Alerts[0].CauseCode == 3)
      {
        // RWW
        d_printf(D_WARN, NULL,"TA_THREATTYPE_RWW\n");
        int Dist = ((int)pAlert->IHW.Alerts[0].Distance2IHW_mm/10000)*10;
        if (Dist > 0)
        {
          snprintf(AlertStr, ALERT_STR_SIZE, "Roadwork in %dm", Dist);
        }
        else
        {
          snprintf(AlertStr, ALERT_STR_SIZE, "Roadwork");
        }
        (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_ROADWORK,
                        HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                        pAlert->DistanceToEvent_m);
      }
      else
      {
        // IHW
        d_printf(D_WARN, NULL,"TA_THREATTYPE_IHW\n");
        int Dist = ((int)pAlert->IHW.Alerts[0].Distance2IHW_mm/10000)*10;
        if (Dist > 0)
        {
          snprintf(AlertStr, ALERT_STR_SIZE, "Hazard (%d/%d) in %dm",
                   pAlert->IHW.Alerts[0].CauseCode,
                   pAlert->IHW.Alerts[0].SubCauseCode,
                   Dist);
        }
        else
        {
          snprintf(AlertStr, ALERT_STR_SIZE, "Hazard (%d/%d)",
                   pAlert->IHW.Alerts[0].CauseCode,
                   pAlert->IHW.Alerts[0].SubCauseCode);
        }
        (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_IHW,
                        HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                        pAlert->DistanceToEvent_m);
      }
    }
    break;

    case TA_THREATTYPE_IVS:
    {
      if (pAlert->IVS.Signs[0].Distance2IVS_mm != -1)
        snprintf(AlertStr, ALERT_STR_SIZE, "IVS start %dm",
                 (int)pAlert->IVS.Signs[0].Distance2IVS_mm/1000);
      else
        snprintf(AlertStr, ALERT_STR_SIZE, "IVS %dm %d %d %d",
                 (int)pAlert->IVS.Signs[0].Distance2EndIVS_mm/1000,
                 pAlert->IVS.Signs[0].ServiceCategory,
                 pAlert->IVS.Signs[0].PictogramCategory,
                 pAlert->IVS.Signs[0].Value);

      d_printf(D_WARN, NULL,"TA_THREATTYPE_IVS\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_IVS,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    }
    break;

    case TA_THREATTYPE_LTA:
    {
      snprintf(AlertStr, ALERT_STR_SIZE, "LTA in %dm", (int)pAlert->DistanceToEvent_m);
      d_printf(D_WARN, NULL,"TA_THREATTYPE_LTA\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_LTA,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    } break;

    case TA_THREATTYPE_BSW_LCW:
    {
      // left/right??
      d_printf(D_WARN, NULL,"TA_THREATTYPE_BSW_LCW\n");
      if (pAlert->BSW_LCW.Scenario == TA_BSW_LCW_SCENARIO_BSW)
      {
        snprintf(AlertStr, sizeof(AlertStr), "BSW!");
      }
      else
      {
        snprintf(AlertStr, sizeof(AlertStr), "LCW!");
      }

      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_BSW_LCW,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    } break;

    case TA_THREATTYPE_DNPW:
    {
      // left/right??
      snprintf(AlertStr, ALERT_STR_SIZE, "Do not pass!");
      d_printf(D_WARN, NULL,"TA_THREATTYPE_DNPW\n");
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_DNPW,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, AlertStr,
                      pAlert->DistanceToEvent_m);
    } break;

    case TA_THREATTYPE_CUSTOM0:
    {
      d_printf(D_WARN, NULL,"TA_THREATTYPE_CUSTOM0\n");
      // Custom alert from RLW plugin, re-use RLW alert notification
      (void)HMI_Alert(pHMI, HMI_ALERT_TYPE_RLW,
                      HMI_ALERT_DIRECTION_UNKNOWN, pAlert->Level, NULL,
                      pAlert->DistanceToEvent_m);
    }
    break;

    default:
    {
      d_printf(D_WARN, NULL,"Alert (%08"PRIx32", %s) unknown\n",
               pAlert->Type, TA_ThreatType(pAlert->Type));
    }
    break;
  }

Exit:
  d_fnend(D_INTERN, NULL, "(%p, %p)-> {%08"PRIx32"}\n",
          pAlert, pParam, pAlert->Type);
}

// Close the doxygen group
/**
 * @}
 */
