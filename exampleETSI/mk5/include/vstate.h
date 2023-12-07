/**
 * @addtogroup vstate_api Vehicle State (VSTATE) API
 * @{
 *
 * @section vstate_api_wdid What Does It Do
 * VSTATE thread receiver handler provides access to the state information of
 * the vehicle (CAN etc). It also indirectly sends notifications of important events
 * happening (eg Hard Braking) via the EXT module.
 *
 * A client will subscribe to the EXT events, identifying the
 * @c QSMSG_EXT_VSTATE_EVENT as the one containing the VSTATE information.
 * This contains the new and currently active VSTATE events, in the format
 * of @ref VstateEvents;
 * See the EXT module for further details.
 *
 * @section vstate_api_hdwui How Do We Use It
 * Vehicle state information can be accessed using immediately returning function
 * calls. The sending of notifications on various events is configured via
 * the EXT module.
 *
 * The most commonly used functions are
 * - @ref VState_ReaderRegister
 * - @ref VState_ReaderGetBuffer
 * - @ref VState_ReaderDeregister
 *
 * Define supported messages for Vstate, Vstate alert types,
 * and CAN message layouts.
 *
 * Unless stated otherwise the reference frame is SAE J670 (Z down)
 * see smb://cw-svr04/data/Engineering/Reference/01_FreeStandards/02_US/SAE/J670v002.pdf
 *
 * @file
 *
 * Interface definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __VSTATE_IF_H_
#define __VSTATE_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "id-global.h"
#include "vstate-data.h"

#include "can-vsc3.h"
#include "BufferQueue.h"
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Limit Vstate readers
#define VSTATE_MAX_READERS  12

/// Supported messages in VSTATE
typedef enum
{
  /// VSTATE vehichle state message from VSC1 message type
  QSMSG_VSTATE_MSG_VSC1 = QS_BASE_MSG_VSTATE,
  /// VSTATE vehichle state message from VSC2 message type
  QSMSG_VSTATE_MSG_VSC2,
  /// VSTATE vehichle state message from VSC3 message type
  QSMSG_VSTATE_MSG_VSC3,
  /// VSTATE vehichle state message from VSC4 message type
  QSMSG_VSTATE_MSG_VSC4,
  /// VSTATE vehichle state message from VSC5 message type
  QSMSG_VSTATE_MSG_VSC5,
  /// VSTATE vehichle state message from VSC6 message type
  QSMSG_VSTATE_MSG_VSC6,
  /// VSTATE vehichle state message from VSC7 message type
  QSMSG_VSTATE_MSG_VSC7,
  /// tGPSRxInfo
  QSMSG_VSTATE_MSG_LPH_POS,
  /// VSTATE update request (only used internally by VSTATE)
  QSMSG_VSTATE_MSG_UPDATE_REQUEST,
  /// VSTATE update request (only used internally by VSTATE)
  QSMSG_VSTATE_MSG_HANDLE_REQUEST,
  /// VSTATE processing request (only used internally by VSTATE)
  QSMSG_VSTATE_MSG_WORK_REQUEST,
} tVStateMsgId;


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/**
 * @brief VSTATE callback prototype requested by VState_RequestWork()
 * @param pVState Vehicle state to update
 * @param pReq Request
 *
 */
typedef void (fVState_Callback)(tVStateState *pVState,
                                void *pPriv);

/**
 * VState handler
 *
 * This callback function is given a CAN message and an instance
 * of the vehicle state to update.
 * It must be registered (@ref VState_RegisterHandler) and will then
 * be invoked by the VState thread when the given CAN message is received.
 *
 * The callback is expected to update pVStateState using
 * @ref VS_UpdateMeta, @ref VS_UpdateEvtBool, @ref VS_UpdateEvtData
 * and/or @ref VS_UpdateEvtDelta as appropriate.
 *
 * @param pVStateState the vehicle state to update
 * @param pMsg the received CAN message
 */
typedef void (tVStateHandlerCallback)(tVStateState *pVStateState,
                                      const tCANRxMsg *pMsg);

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// Init/Exit functions in order of execution:
int VState_LibraryInit(void);
int VState_ThreadInit(int SchedulerPolicy, int SchedulerPriority);
void VState_ThreadDeinit(void);
void VState_LibraryDeinit(void);

// Reader functions (used by clients that just want to know the current state)
tUtilBufferQueueReader *VState_ReaderRegister(void);
const tVStateState     *VState_ReaderGetBuffer(tUtilBufferQueueReader *pReader);
void                    VState_ReaderDeregister(tUtilBufferQueueReader *pReader);

// (De)Register a CAN message handler that runs in the VSTATE context
// when a specific CAN message (matching 'id') is received
int VState_RegisterHandler(canid_t Id,
                           tVStateHandlerCallback Handler,
                           unsigned int MinInterval_ms);
int VState_DeregisterHandler(canid_t Id,
                             tVStateHandlerCallback Handler);

// Request work in VSTATE context
int VState_RequestWork(fVState_Callback *pFunc, void *pPriv);

#ifdef __cplusplus
}
#endif

#endif // __VSTATE_H_

// Close the Doxygen group
/**
 * @}
 */
