/**
 * @addtogroup mod_message Example ETSI Messaging
 * @{
 *
 * Defines message ID's and queues for inter module messaging
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __MESSAGE_H_
#define __MESSAGE_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "id-global.h"

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Msg Q Numbers
#define QSQUEUE_CAN       QSQUEUE_APP2
#define QSQUEUE_ITSTX     QSQUEUE_APP3

/// Message ID Base Numbers
#define QS_BASE_MSG_CAN       QS_BASE_MSG_APP2
#define QS_BASE_MSG_ITSTX     QS_BASE_MSG_APP3


//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

/// Message ID Numbers
typedef enum
{
  /// CAN transmit request
  QSMSG_CAN_TX_REQ = QS_BASE_MSG_CAN,
  /// CAN receive indication
  QSMSG_CAN_RX_IND,

  /// ITS BTP transmit request
  QSMSG_ITS_BTP_TX_REQ = QS_BASE_MSG_ITSTX,
  /// ITS encoded transmit request for Roadworks
  QSMSG_ITS_DENM_ROADWORKS_TX_REQ,
  /// ITS encoded terminate request for Roadworks
  QSMSG_ITS_DENM_ROADWORKS_TERMINATE_TX_REQ,
  /// ITS encoded transmit request for EEBL
  QSMSG_ITS_DENM_EEBL_TX_REQ,
  /// ITS encoded transmit request for EVW
  QSMSG_ITS_DENM_EVW_TX_REQ,
  /// ITS encoded transmit request for SPAT
  QSMSG_ITS_SPAT_TX_REQ,
  /// ITS encoded transmit request for MAP
  QSMSG_ITS_MAP_TX_REQ,
  /// ITS encoded transmit request for SRM
  QSMSG_ITS_SRM_TX_REQ,
  /// ITS encoded transmit request for SSM
  QSMSG_ITS_SSM_TX_REQ,
  /// ITS encoded transmit request for SA
  QSMSG_ITS_SA_TX_REQ,
  /// ITS encoded transmit request for RTCM
  QSMSG_ITS_RTCM_TX_REQ,
  /// ITS encoded transmit request for CPM
  QSMSG_ITS_CPM_TX_REQ,
  /// ITS encoded transmit request for VAM
  QSMSG_ITS_VAM_TX_REQ,
  /// ITS encoded transmit request for IVI
  QSMSG_ITS_IVI_TX_REQ,
  /// ITS encoded transmit request for IMZM
  QSMSG_ITS_IMZM_TX_REQ,
  /// ITS encoded terminate request for IVI
  QSMSG_ITS_IVI_TERMINATE_TX_REQ,
  /// ITS receive indication
  QSMSG_ETSI_NOTIF_IND,
} eEventId;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

#endif // __MESSAGE_H_
/**
 * @}
 */
