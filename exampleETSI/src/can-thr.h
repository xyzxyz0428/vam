/**
 * @addtogroup mod_can_thr_etsi CAN Interface Module
 * @{
 *
 * @section mod_can_thr_etsi_dd What Does It Do
 *
 * Registers with CAN notification interface to receive a particular incoming CAN message.
 * When a message with this CAN ID is received, notify the trigger module.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __CAN_THR_H_
#define __CAN_THR_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Location of the CAN configuration settings
#define CAN_CONFIG_PATH_NAME  "Example.CAN"

// Configuration value names
#define CAN_CONFIG_VALUE_NAME_POLLINGINTERVAL      "PollingInterval"
#define CAN_CONFIG_VALUE_NAME_MININTERVAL_MS       "MinInterval_ms"

// Configuration value defaults for mandatory items
#define CAN_CONFIG_VALUE_DEFAULT_POLLINGINTERVAL           (500)
#define CAN_CONFIG_VALUE_DEFAULT_MININTERVAL_MS            (10)

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------


/// State IDs for CAN thread state
typedef enum CANETSIThreadState
{
  /// Not initialized
  CAN_THREAD_STATE_NONE = 0x00,
  /// Initializing
  CAN_THREAD_STATE_INIT = 0x01,
  /// Running
  CAN_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  CAN_THREAD_STATE_STOP = 0x04,
  /// Stopped
  CAN_THREAD_STATE_END  = 0x08,
} eCANETSIThreadState;

/// @ref CANETSIThreadState
typedef int tCANETSIThreadState;

/// CAN Statistics
typedef struct CANETSIStats
{
  /// Receive counters
  struct {
    uint32_t Count;
  } Rx;

} tCANETSIStats;

/// CAN parameters - Stored in Config File
typedef struct CANETSIParams
{
  /// period
  uint32_t PollingInterval;
  /// minimum inter-packet interval
  uint32_t minInterval_ms;
} tCANETSIParams;

/// CAN state
typedef struct CANETSI
{
  /// ID of CAN thread
  pthread_t ThreadID;
  /// CAN thread state
  tCANETSIThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;
  /// Module statistics
  tCANETSIStats Stats;
  /// Configuration
  tCANETSIParams Params;
  /// Most recently received CAN msg
  tCANRxMsg Msg;
} tCANETSI;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

int CAN_Open (tCANETSI *pCAN,
              pthread_attr_t *pAttr,
              char *pConfigFileName);

void CAN_Close (tCANETSI *pCAN);

void CAN_PrintStats (tCANETSI *pCAN);


#endif // __CAN_THR_H_
/**
 * @}
 */
