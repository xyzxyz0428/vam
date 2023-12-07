/**
 * @addtogroup mod_can_thr_etsi CAN Interface Module
 * @{
 *
 * CAN receiver module
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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#include "libconfig.h" // used to read configuration file

// v2x-lib includes
#include "debug-levels.h"
#include "can-rx.h"
#include "util.h"
#include "qs-lib.h"

#include "can-thr.h"
#include "message.h"
#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_CANThr_DebugLevel

/// Define simple message
#define CAN_ID_HEARTBEAT 0x150

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static int CAN_LoadConfig (tCANETSI *pCAN,
                           char * pConfigFileName);

static void CAN_ThreadProc (void *pArg);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------


/**
 * @brief Allocate CAN object, Setup thread and associated data structures
 * @param pCAN pointer to CAN handle (populated by this function)
 * @param pAttr POSIX thread attributes
 * @param pConfigFileName Configuration filename
 * @return Zero for success or an negative errno
 */
int CAN_Open (tCANETSI *pCAN,
              pthread_attr_t *pAttr,
              char *pConfigFileName)
{
  int Res;
  d_fnstart(D_INTERN, NULL, "(%p,%p,%s)\n",
            pCAN, pAttr, pConfigFileName);

  memset(pCAN, 0, sizeof(tCANETSI));

  // Load config settings
  Res = CAN_LoadConfig(pCAN, pConfigFileName);
  if (Res != 0)
  {
    d_error(D_ERR, NULL, "CAN_LoadConfig() != 0\n");
    goto Error;
  }

  // Create the CAN message queue
  tQsStatus SStat = Msg_QueueInit(QSQUEUE_CAN);
  if (SStat != QSSTATUS_OK)
  {
    d_error(D_WARN, NULL, "Failed to set up CAN message queue\n");
    goto Error;
  }

  // Init state

  // Assign thread attributes from input param
  pCAN->ThreadAttr = *pAttr;

  // Create TPSE thread
  pCAN->ThreadState |= CAN_THREAD_STATE_INIT;
  Res = pthread_create(&pCAN->ThreadID,
                       &pCAN->ThreadAttr,
                       (void *)CAN_ThreadProc,
                       pCAN);
  if (Res != 0)
  {
    d_error(D_ERR, NULL, "pthread_create() failed\n");
    // Thread creation error
    pCAN->ThreadState = CAN_THREAD_STATE_NONE;
    goto Error;
  }

  // Success!
  Res = 0;
  d_printf(D_INFO, NULL, "Successfully started the can-thr\n");
  goto Success;

Error:
  d_error(D_ERR, NULL, "Error!\n");
  CAN_Close(pCAN);
Success:
  d_fnend(D_INFO, NULL, "()\n");
  return Res;
}

/**
 * @brief Stop execution of CAN, free the thread and its associated resources
 * @param pCAN CAN handle
 */
void CAN_Close (tCANETSI *pCAN)
{
  d_fnstart(D_INFO, NULL, "()\n");

  tQsStatus SStat = Msg_SendId(QSMSG_SYS_TERMINATE, QSQUEUE_CAN, QSPRIORITY_MAX);

  if (SStat != QSSTATUS_OK)
  {
    d_printf(D_DEBUG, NULL, "CAN thread deinit:QSMSG_SYS_TERMINATE fail\n");
    pCAN->ThreadState |= CAN_THREAD_STATE_STOP;
  }

  // Wait for thread termination
  if (pCAN->ThreadState & CAN_THREAD_STATE_INIT)
    pthread_join(pCAN->ThreadID, NULL);

  Msg_QueueDeInit(QSQUEUE_CAN);

  d_fnend(D_INFO, NULL, "()\n");
  return;
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief Load CAN parameters from the config file
 * @param pCAN CAN handle
 * @param pConfigFileName Filename of the config file
 * @return Zero for success or a negative errno
 */
static int CAN_LoadConfig (tCANETSI *pCAN,
                           char *pConfigFileName)
{
  int Res;
  config_t Config; // configuration object read from config file
  config_t *pConfig;
  config_setting_t *pSetting; // setting for CAN in config file
  int ConfigVal = 0;

  pConfig = &Config;
  config_init(pConfig); // initialise the config object

  // Set defaults
  pCAN->Params.PollingInterval = CAN_CONFIG_VALUE_DEFAULT_POLLINGINTERVAL;
  pCAN->Params.minInterval_ms  = CAN_CONFIG_VALUE_DEFAULT_MININTERVAL_MS;

  // Try to read the specified config file into the config object
  if (config_read_file(pConfig, pConfigFileName) != CONFIG_TRUE)
  {
    d_error(D_ERR, NULL,  "Could not open %s\n", pConfigFileName);
    // "libconfig: %s at line %d\n", config_error_text (pConfig),
    Res = -EINVAL;
    goto Error;
  }

  // Get the 'CAN' Setting
  pSetting = config_lookup(pConfig, CAN_CONFIG_PATH_NAME);
  if (pSetting == NULL)
  {
    d_error(D_ERR, NULL,  "config_lookup(%s) failed\n", CAN_CONFIG_PATH_NAME);
    Res = -EINVAL;
    goto Error;
  }

  // config is open, now look for configuration entries

  // Rx thread Interval
  if (config_setting_lookup_int(pSetting,
                                CAN_CONFIG_VALUE_NAME_POLLINGINTERVAL,
                                &ConfigVal))
    pCAN->Params.PollingInterval = (uint32_t) ConfigVal;

  if (config_setting_lookup_int(pSetting,
                                CAN_CONFIG_VALUE_NAME_MININTERVAL_MS,
                                &ConfigVal))
    pCAN->Params.minInterval_ms = (uint32_t) ConfigVal;

  // Update complete - close the configuration
  config_destroy(pConfig);

  // Success!
  Res = 0;

Error:
  return Res;
}

/**
 * @brief CAN Rx Callback function
 * @param pMsg Received CAN Message
 * @param pPriv Private data (tCANETSI)
 *
 */
static void CAN_CANCallback(const tCANRxMsg *pMsg,
                            void *pPriv)
{
  tCANETSI *pCAN = (tCANETSI *)pPriv;

  d_printf(D_WARN, NULL, "Received new CAN Message (ID:0x%4.4x,Len:%d)\n",
           pMsg->frame.can_id, pMsg->frame.can_dlc);

  // Copy the message data
  memcpy(&pCAN->Msg, pMsg, sizeof(pCAN->Msg));
}

/**
 * @brief CAN Periodic thread processing - print stats
 * @param pArg Pointer to CAN object passed as generic input parameter
 *
 */
static void CAN_ThreadProc (void *pArg)
{
  tCANETSI *pCAN;
  int Ret;
  uint8_t CanCounter = 0;

  d_printf(D_DEBUG, NULL, "Started thread\n");

  // pArg cast to TPSE object
  pCAN = (tCANETSI *) pArg;

  // Starting CAN Periodic Thread
  pCAN->ThreadState |= CAN_THREAD_STATE_RUN;

  // Register the callback with the CAN RX module
  Ret = CANRx_AddCANID(CAN_ID_PROMISCUOUS_MODE,
                       CAN_CANCallback, pCAN,
                       pCAN->Params.minInterval_ms);

  if (Ret < 0)
  {
    d_error(D_ERR, NULL, "Unable to register callback with CAN module\n");
    goto Error;
  }

  d_printf(D_DEBUG, NULL, "Registered Callback!\n");

  // Initial send
  CANTx_SendCANIDStd(CAN_ID_HEARTBEAT, 1, &CanCounter);

  // Thread loop
  while ((pCAN->ThreadState & CAN_THREAD_STATE_STOP) == 0)
  {
    tQsStatus RStat;
    tQsMessage RecvMsg;

    // Wait on received message
    RStat = Msg_Recv(QSQUEUE_CAN, &RecvMsg);

    if (RStat != QSSTATUS_OK)
    {
      d_error(D_ERR, 0, "Msg_Recv failed (%d)\n", RStat);
      continue;
    }

    d_printf(D_INFO, NULL, "CAN thread message id (0x%04x)\n", RecvMsg.Id);

    // Got a message, handle it
    switch (RecvMsg.Id)
    {
      case QSMSG_CAN_TX_REQ:
        // Transmit a CAN message
        CanCounter++;
        CANTx_SendCANIDStd(CAN_ID_HEARTBEAT, 1, &CanCounter);

        break;

      case QSMSG_SYS_TERMINATE:
        pCAN->ThreadState |= CAN_THREAD_STATE_STOP;
        break;

      default:
        d_error(D_ERR, 0, "Unsupported message ID (%d)\n", RecvMsg.Id);
        break;
    }
  }

  CANRx_RemoveCANID(CAN_ID_PROMISCUOUS_MODE, CAN_CANCallback, pCAN);

Error:
  // exit thread
  (void) pthread_exit(NULL);
}


// Close the doxygen group
/**
 * @}
 */
