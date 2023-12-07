/**
 * @addtogroup mod_can_vstate_etsi CAN + VState Interface Module
 * @{
 *
 * @section mod_can_vstate_etsi_dd What Does It Do
 *
 * Registers with @ref can_rx_api to receive a particular incoming CAN message.
 * When a message with this CAN ID is received, requests to update VState with
 * data from the CAN message.
 *
 * In the case that custom CAN messages are used for vehicle data then the
 * custom CAN handler has to be created and VState updated with a specific
 * API, as demonstrated in this example.
 *
 * This example shows the installation of a CAN handler enabling for message
 * ID 0x321, and then that handler extracting the speed information and
 * updating VState (@ref CANVState_VStateUpdate.)
 *
 * It's important to note that the correct tIniFile::TxDataSource is selection
 * is made. The 'Live Mode' has to be enabled, rather than other Test Modes
 * that update VState from other data sources.
 *
 * One useful mode, in the case that no CAN messaging is available, is the
 * GPS Only mode that fakes some VState data based on GPS position & speed
 * information, specifically VehSpd, LonAccel, YawRate, BrkAct, PanicBrake.
 *
 * In the case that the CAN VSC messages (0x600-0x605) are supported, then
 * the Cohda Stack library libCLV will handle the appropriate vehicle data
 * fields and set the VState data store for clients to access.
 *
 *
 * @file
 *
 * CAN receiver definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __CAN_VSTATE_H_
#define __CAN_VSTATE_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <sys/time.h>

#include "dot3-wsmp.h"
#include "j2735-message.h"

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Location of the CANVState configuration settings
#define CANVSTATE_CONFIG_PATH_NAME  "Example.CANVState"

// Configuration value names
#define CANVSTATE_CONFIG_VALUE_NAME_POLLINGINTERVAL      "PollingInterval"

// Configuration value defaults for mandatory items
#define CANVSTATE_CONFIG_VALUE_DEFAULT_POLLINGINTERVAL           (500)

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

/// State IDs for the CAN-VState thread
typedef enum CANVStateETSIThreadState
{
  /// Not initialized
  CANVSTATE_THREAD_STATE_NONE = 0x00,
  /// Initializing
  CANVSTATE_THREAD_STATE_INIT = 0x01,
  /// Running
  CANVSTATE_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  CANVSTATE_THREAD_STATE_STOP = 0x04,
  /// Stopped
  CANVSTATE_THREAD_STATE_END  = 0x08,
} eCANVStateETSIThreadState;
/// @ref CANVStateETSIThreadState
typedef int tCANVStateETSIThreadState;

/// CANVState Statistics
typedef struct CANVStateETSIStats
{
  /// Receive counters
  struct {
    uint32_t Count;
  } Rx;

} tCANVStateETSIStats;

/// CANVState parameters - Stored in Config File
typedef struct CANVStateETSIParams
{
  /// Period in ms
  uint32_t PollingInterval; // just for the thread sleep

} tCANVStateETSIParams;

/// CANVState state
typedef struct CANVStateETSI
{
  /// ID of CANVState thread
  pthread_t ThreadID;
  /// CANVState thread state
  tCANVStateETSIThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;
  /// Lock to be used when accessing data
  pthread_mutex_t Lock;
  /// Module statistics
  tCANVStateETSIStats Stats;
  /// Configuration
  tCANVStateETSIParams Params;
  /// Most recently received CAN msg
  tCANRxMsg Msg;
} tCANVStateETSI;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

int CANVState_Open (tCANVStateETSI **ppCV,
                pthread_attr_t *pAttr,
                char *pConfigFileName);

void CANVState_Close (tCANVStateETSI *pCV);

void CANVState_PrintStats (tCANVStateETSI *pCV);


#endif // __CAN_VSTATE_H_
/**
 * @}
 */
