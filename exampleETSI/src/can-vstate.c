/**
 * @addtogroup mod_can_vstate_etsi CAN + VState Interface Module
 * @{
 *
 * CAN receiver and VState update module
 *
 * @file
 *
 * Module code for CAN receiver and VState updating
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
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

#include "libconfig.h" // used to read configuration file
// J2735 includes
#include "j2735-message.h"

// v2x-lib includes
#include "debug-levels.h"
#include "vstate.h"
#include "can-rx.h"
#include "dot3-wsmp.h"
#include "util.h"

#include "can-vstate.h"
#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_CANVState_DebugLevel

#define CANVSTATE_CANID 0x123

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static int CANVState_LoadConfig (tCANVStateETSI *pCV,
                                 char * pConfigFileName);

static void CANVState_ThreadProc (void *pArg);

static tVStateHandlerCallback CANVState_VStateUpdate;

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------


/**
 * @brief Allocate CAN object, Setup thread and associated data structures
 * @param ppCV pointer to CANVState handle (populated by this function)
 * @param pAttr POSIX thread attributes
 * @param pConfigFileName Configuration filename
 * @return Zero for success or an negative errno
 */
int CANVState_Open (tCANVStateETSI **ppCV,
                    pthread_attr_t *pAttr,
                    char *pConfigFileName)
{
  int Res = -ENOSYS;
  tCANVStateETSI *pCV;

  d_fnstart(D_INTERN, NULL, "(%p,%p,%s)\n",
            ppCV, pAttr, pConfigFileName);

  // Create and check the local structure
  pCV = (tCANVStateETSI *) malloc(sizeof(tCANVStateETSI));
  if (pCV == NULL)
  {
    Res = -ENOMEM;
    goto Error;
  }
  memset(pCV, 0, sizeof(tCANVStateETSI));

  // Load config settings
  Res = CANVState_LoadConfig(pCV, pConfigFileName);
  if (Res != 0)
  {
    d_error(D_ERR, NULL, "CANVState_LoadConfig() != 0\n");
    goto Error;
  }

  // Init state

  // Assign thread attributes from input param
  pCV->ThreadAttr = *pAttr;

  // Create lock to protect structure data
  Res = pthread_mutex_init(&pCV->Lock, NULL);
  if (Res != 0)
  {
    goto Error;
  }

  // Create TPSE thread
  pthread_mutex_lock(&pCV->Lock);
  pCV->ThreadState |= CANVSTATE_THREAD_STATE_INIT;
  Res = pthread_create(&pCV->ThreadID,
                       &pCV->ThreadAttr,
                       (void *)CANVState_ThreadProc,
                       pCV);
  if (Res != 0)
  {
    d_error(D_ERR, NULL, "pthread_create() failed\n");
    // Thread creation error
    pCV->ThreadState = CANVSTATE_THREAD_STATE_NONE;
    pthread_mutex_unlock(&pCV->Lock);
    goto Error;
  }
  pthread_mutex_unlock(&pCV->Lock);

  // Success!
  *ppCV = pCV;
  Res = 0;
  d_printf(D_INFO, NULL, "Successfully started the can-thr\n");
  goto Success;

Error:
  d_error(D_ERR, NULL, "Error!\n");
  *ppCV = NULL;
  CANVState_Close(pCV);
Success:
  d_fnend(D_INFO, NULL, "()\n");
  return Res;
}

/**
 * @brief Stop execution of CAN, free the thread and its associated resources
 * @param pCV CAN handle
 */
void CANVState_Close (tCANVStateETSI *pCV)
{
  int Res = -ENOSYS;
  d_fnstart(D_INFO, NULL, "()\n");

  // Catch attempt to close invalid object pointer
  if (pCV == NULL)
  {
    Res = -EINVAL;
    goto Error;
  }

  // Signal thread to terminate
  pCV->ThreadState |= CANVSTATE_THREAD_STATE_STOP;
  // Wait for thread termination
  if (pCV->ThreadState & CANVSTATE_THREAD_STATE_INIT)
    pthread_join(pCV->ThreadID, NULL);

  // Success!
  Res = 0;

Error:
  free(pCV);
  (void)Res;   // value currently not used

  d_fnend(D_INFO, NULL, "()\n");
  return;
}

/**
 * @brief Prints the statistics from the TPSE object
 * @param pCV CAN handle
 */
void CANVState_PrintStats (tCANVStateETSI *pCV)
{
  fprintf(stdout, "CANVState: Rx (Count %8u)\n", pCV->Stats.Rx.Count);
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief Load CANVSTATE parameters from the config file
 * @param pCV CANVState handle
 * @param pConfigFileName Filename of the config file
 * @return Zero for success or a negative errno
 */
static int CANVState_LoadConfig (tCANVStateETSI *pCV,
                                 char *pConfigFileName)
{
  int Res = -ENOSYS;
  config_t Config; // configuration object read from config file
  config_t *pConfig;
  config_setting_t *pSetting; // setting for CANVSTATE in config file
  int ConfigVal = 0;

  pConfig = &Config;
  config_init(pConfig); // initialise the config object

  // Set defaults
  pCV->Params.PollingInterval = CANVSTATE_CONFIG_VALUE_DEFAULT_POLLINGINTERVAL;

  // Try to read the specified config file into the config object
  if (config_read_file(pConfig, pConfigFileName) != CONFIG_TRUE)
  {
    d_error(D_ERR, NULL,  "Could not open %s\n", pConfigFileName);
    // "libconfig: %s at line %d\n", config_error_text (pConfig),
    Res = -EINVAL;
    goto Error;
  }

  // Get the 'CANVSTATE' Setting
  pSetting = config_lookup(pConfig, CANVSTATE_CONFIG_PATH_NAME);
  if (pSetting == NULL)
  {
    d_error(D_ERR, NULL,  "config_lookup(%s) failed\n", CANVSTATE_CONFIG_PATH_NAME);
    Res = -EINVAL;
    goto Error;
  }

  // config is open, now look for configuration entries

  // Rx thread Interval
  if (config_setting_lookup_int(pSetting,
                                CANVSTATE_CONFIG_VALUE_NAME_POLLINGINTERVAL,
                                &ConfigVal))
    pCV->Params.PollingInterval = (uint32_t) ConfigVal;

  // Update complete - close the configuration
  config_destroy(pConfig);

  // Success!
  Res = 0;

Error:
  return Res;
}

/**
 * @brief CAN-VState handler function to update VState based on received CAN message
 * @param pVState Provided VState structure to update
 * @param pMsg Received CAN message data
 */
void CANVState_VStateUpdate(tVStateState *pVState,
                            const tCANRxMsg *pMsg)

{
  // decide on which message ID to use
  switch(pMsg->frame.can_id)
  {
    case CANVSTATE_CANID:
    {
      // Handle the 'example' CANVSTATE_CANID CAN message
      // Bytes 0 & 1 are MSB/LSB of Vehicle Speed (in cm per sec)
      // Byte 2 is Vehicle Speed Confidence (in cm per sec)
      // Byte 3 is Detected Lane Position
      // Bytes 4 & 5 are MSB/LSB of Longitudinal Acceleration (in mm per sec per sec)
      // Byte 6 is Longitudinal Acceleration Confidence (in mm per sec per sec)

      // determine speed (in cm/sec)
      const uint16_t Speed = (pMsg->Byte[0] << 8) + pMsg->Byte[1];
      const float Speed_mps = Speed / 100.0;
      const uint16_t SpeedConf = pMsg->Byte[2];
      const float SpeedConf_mps = SpeedConf / 100.0;

      d_printf(D_WARN, NULL, "Setting VState Speed: %.2fm/s (was %.2f), conf %.2f\n",
               Speed_mps, VS_GetVehSpd_mps(pVState), SpeedConf_mps);

      // Speed set
      VS_SetVehSpd_mps(pVState, Speed_mps);
      // Speed confidence set
      VS_SetVehSpdConf_mps(pVState, SpeedConf_mps);

      // update lane position
      d_printf(D_WARN, NULL, "Setting VState Lane Position: %u\n",
               pMsg->Byte[3]);

      VS_SetLanePos(pVState, pMsg->Byte[3]);

      const int16_t LonAccel = (pMsg->Byte[5] << 8) + pMsg->Byte[6];
      const float LonAccel_mpss = LonAccel / 1000.0;
      const uint16_t LonAccelConf = pMsg->Byte[7];
      const float LonAccelConf_mpss = LonAccelConf / 1000.0;

      d_printf(D_WARN, NULL, "Setting VState LonAccel: %.2fm/s (was %.2f), conf %.2f\n",
               LonAccel_mpss, VS_GetLonAccel_m_per_s_per_s(pVState), LonAccelConf_mpss);

      // LonAcc set
      VS_SetLonAccel_m_per_s_per_s(pVState, LonAccel_mpss);
      // LonAcc confidence set
      VS_SetLonAccelConf_mps2(pVState, LonAccelConf_mpss);

    } break;

    default:
      break;
  }

  // VState thread will commit VState data periodically (about every 100mS)
  // to make it available to VState readers
}

/**
 * @brief CAN Periodic thread processing - print stats
 * @param pArg Pointer to CANVState object passed as generic input parameter
 *
 */
static void CANVState_ThreadProc (void *pArg)
{
  tCANVStateETSI *pCV;
  tUtilBufferQueueReader *pVStateReader;
  struct timespec Time;
  int Ret;

  d_printf(D_DEBUG, NULL, "Started thread\n");

  // pArg cast to TPSE object
  pCV = (tCANVStateETSI *) pArg;

  // Initialise the timespec struct for the polling loop
  clock_gettime(CLOCK_MONOTONIC, &Time);

  // Lock while using pCV
  pthread_mutex_lock(&pCV->Lock);
  // Starting CANVState Periodic Thread
  pCV->ThreadState |= CANVSTATE_THREAD_STATE_RUN;
  pthread_mutex_unlock(&pCV->Lock);

  // Register the callback with the CAN RX module
  Ret = VState_RegisterHandler(CANVSTATE_CANID, CANVState_VStateUpdate, 45);
  if (Ret < 0)
  {
    d_error(D_ERR, NULL, "Unable to register callback with CANVState module\n");
    goto Error;
  }

  d_printf(D_DEBUG, NULL, "Registered Callback!\n");

  pVStateReader = VState_ReaderRegister();
  if (pVStateReader == NULL)
  {
    d_error(D_ERR, NULL, "Unable to register VState reader to periodically poll VState speed");
    goto VStateError;
  }

  // Thread loop.
  while ((pCV->ThreadState & CANVSTATE_THREAD_STATE_STOP) == 0)
  {
    const tVStateState *pVStateState;

    // polling delay
    Util_Nap(pCV->Params.PollingInterval, &Time);
    pVStateState = VState_ReaderGetBuffer(pVStateReader);

    d_printf(D_INFO, NULL, "Current VState Speed: %u\n",
             pVStateState->VehSpd.Raw);
  }

  VState_ReaderDeregister(pVStateReader);

VStateError:
  // Deregister the CANVState Callback
  (void)VState_DeregisterHandler(CANVSTATE_CANID, CANVState_VStateUpdate);

Error:
  // exit thread
  (void) pthread_exit(NULL);
}


// Close the doxygen group
/**
 * @}
 */
