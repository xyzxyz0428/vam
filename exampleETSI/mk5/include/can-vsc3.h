/**
 * @addtogroup lib_can_vsc3_api CAN VSC3 API
 * @{
 *
 * @section lib_can_vcs3_api_wdid What Does It Do
 *
 * Provides access to VSC3 CAN messages
 *
 * @file
 *
 * Interface API definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __CAN_VSC3_IF_H_
#define __CAN_VSC3_IF_H_


//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "can-rx.h"
// Generated structures from DBC file
#include "vsc3obe.h"

#include <stdint.h>
/// Get byte endianess and infer bitfield endianess
#if defined(__QNX__)
#include <gulliver.h>
#else
#include <endian.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Supported CAN message numbers
typedef enum
{
  /// OBE1
  CAN_VSC3_MESSAGE_OBE_1 = VSC3OBE_VSTATE_OBE1_ID,
  /// OBE2
  CAN_VSC3_MESSAGE_OBE_2 = VSC3OBE_VSTATE_OBE2_ID,
  /// OBE3
  CAN_VSC3_MESSAGE_OBE_3 = VSC3OBE_VSTATE_OBE3_ID,
  /// OBE4
  CAN_VSC3_MESSAGE_OBE_4 = VSC3OBE_VSTATE_OBE4_ID,
  /// OBE5
  CAN_VSC3_MESSAGE_OBE_5 = VSC3OBE_VSTATE_OBE5_ID,
  /// OBE6
  CAN_VSC3_MESSAGE_OBE_6 = VSC3OBE_VSTATE_OBE6_ID,
  /// OBE7
  CAN_VSC3_MESSAGE_OBE_7 = VSC3OBE_VSTATE_OBE7_ID,
} eCANVSC3MsgNbr;


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

// Compiler access of bitfields is endian-dependent, even though OBE
// message is always passed in big-endian format

/// VSC3 CAN message 600 (CAN_VSC3_MESSAGE_OBE_1)
typedef tVSC3OBE_VSTATE_OBE1 tCANVSC3MsgOBE1;
typedef tVSC3OBE_VSTATE_OBE2 tCANVSC3MsgOBE2;
typedef tVSC3OBE_VSTATE_OBE3 tCANVSC3MsgOBE3;
typedef tVSC3OBE_VSTATE_OBE4 tCANVSC3MsgOBE4;
typedef tVSC3OBE_VSTATE_OBE5 tCANVSC3MsgOBE5;
typedef tVSC3OBE_VSTATE_OBE6 tCANVSC3MsgOBE6;
typedef tVSC3OBE_VSTATE_OBE7 tCANVSC3MsgOBE7;

/// Struct to read raw CAN message (@sa tCANVRxMsg)
typedef union CANVSC3Msg
{
  /// OBE1 - 600
  tCANVSC3MsgOBE1 OBE1;
  /// OBE2 - 601
  tCANVSC3MsgOBE2 OBE2;
  /// OBE3 - 602
  tCANVSC3MsgOBE3 OBE3;
  /// OBE4 - 603
  tCANVSC3MsgOBE4 OBE4;
  /// OBE5 - 604
  tCANVSC3MsgOBE5 OBE5;
  /// OBE6 - 605
  tCANVSC3MsgOBE6 OBE6;
  /// OBE7 - 606
  tCANVSC3MsgOBE7 OBE7;
  /// Raw access
  uint64_t        Raw;
} tCANVSC3Msg;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// CALL THIS FIRST!!
void CANVSC3_LibraryInit (void);

tCANRxCallback CANVSC3_HandleMsg;

/// CALL THIS LAST!!
void CANVSC3_LibraryDeinit (void);

#ifdef __cplusplus
}
#endif

#endif // __CAN_VSC3_IF_H_

/**
 * @}
 */
