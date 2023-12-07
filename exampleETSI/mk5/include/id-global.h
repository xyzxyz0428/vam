/**
 * @addtogroup stack_global_ids Global identifiers
 * @{
 *
 * Cohda Wireless Stack Libraries module definitions
 *
 * @file
 *
 * Interface for Cohda Wireless Stack Library
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ID_GLOBAL_H_
#define __ID_GLOBAL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Some timers can be scaled (e.g. for testing)
#define ETSI_TIME_SCALING (1)

/// Message Queue definitions
enum
{
  QSQUEUE_LPH = 0,
  QSQUEUE_STATS,
  QSQUEUE_VSTATE,
  QSQUEUE_EXT2,
  QSQUEUE_CONF,

  QSQUEUE_ETSI_G5_MON,
  QSQUEUE_ETSI_G5_TX,
  QSQUEUE_ETSI_GN,
  QSQUEUE_ETSI_GN6,

  QSQUEUE_ETSI_FAC,
  QSQUEUE_ETSI_CAM,

  QSQUEUE_TIME,
  QSQUEUE_P1609_TX,
  QSQUEUE_P1609_CTRL,
  QSQUEUE_P1609_RX,
  QSQUEUE_DAS,
  QSQUEUE_SPATMAP,
  QSQUEUE_CPM,

  QSQUEUE_SAEC_PC5_TX,
  QSQUEUE_ETSI_PC5_TX = QSQUEUE_SAEC_PC5_TX,
  QSQUEUE_SAEC_FAC,

  // threat assessment triggering
  QSQUEUE_TA_TRIG,
  // threat classification
  QSQUEUE_TC,
  // threat manager
  QSQUEUE_TM,

  // In vehicle information
  QSQUEUE_IVI,
  // Traveler information
  QSQUEUE_TIM,
  // Road Side Information
  QSQUEUE_RSICN,
  // Probe Vehicle Data Message
  QSQUEUE_PVD,
  // Local dynamic mapping
  QSQUEUE_LDM,

  // Queues for Inter-Process Communication (IPC)
  QSQUEUE_IPC_TOCOHDA,
  QSQUEUE_IPC_FROMCOHDA,

  // Queues defined for higher layer application use
  QSQUEUE_APP1,
  QSQUEUE_APP2,
  QSQUEUE_APP3,
  QSQUEUE_APP4,
  QSQUEUE_APP5,

  // Must be last entry
  // ensure this is <= QSQUEUE_MAX_LIMIT in qs-lib.c
  QSQUEUE_LIMIT
};

/// Low thread priority
#define THREAD_LOW_PRIORITY    10
/// Normal thread priority
#define THREAD_NORMAL_PRIORITY 20
/// High thread priority
#define THREAD_HIGH_PRIORITY   30
/// Urgent thread priority
#define THREAD_URGENT_PRIORITY 40

/// Bits used for message ID
#define QS_BASE_SHIFT 16

/// LPH message base value (avoid non-zero value)
#define QS_BASE_MSG_LPH         ((QSQUEUE_LPH << QS_BASE_SHIFT)+1)
/// STATS message base value
#define QS_BASE_MSG_STATS       (QSQUEUE_STATS << QS_BASE_SHIFT)
/// VSTATE message base value
#define QS_BASE_MSG_VSTATE      (QSQUEUE_VSTATE << QS_BASE_SHIFT)
/// EXT message base value
#define QS_BASE_MSG_EXT         (QSQUEUE_EXT2 << QS_BASE_SHIFT)
/// CONF message base value
#define QS_BASE_MSG_CONF        (QSQUEUE_CONF << QS_BASE_SHIFT)

/// ETSI G5 Monitoring message base value
#define QS_BASE_MSG_ETSI_G5_MON (QSQUEUE_ETSI_G5_MON << QS_BASE_SHIFT)
/// ETSI G5 transmit message base value
#define QS_BASE_MSG_ETSI_G5_TX  (QSQUEUE_ETSI_G5_TX << QS_BASE_SHIFT)
/// ETSI GN message base value
#define QS_BASE_MSG_ETSI_GN     (QSQUEUE_ETSI_GN    << QS_BASE_SHIFT)
/// ETSI DENM message base value
#define QS_BASE_MSG_ETSI_FAC    (QSQUEUE_ETSI_FAC  << QS_BASE_SHIFT)
/// ETSI CAM message base value
#define QS_BASE_MSG_ETSI_CAM    (QSQUEUE_ETSI_CAM   << QS_BASE_SHIFT)
/// ETSI GN6 message base value
#define QS_BASE_MSG_ETSI_GN6    (QSQUEUE_ETSI_GN6   << QS_BASE_SHIFT)

/// SAEC PC5 transmit message base value
#define QS_BASE_MSG_SAEC_PC5_TX  (QSQUEUE_SAEC_PC5_TX << QS_BASE_SHIFT)

/// SAEC FAC message base value
#define QS_BASE_MSG_SAEC_FAC    (QSQUEUE_SAEC_FAC << QS_BASE_SHIFT)

/// TA Trig message base value
#define QS_BASE_MSG_TA_TRIG     (QSQUEUE_TA_TRIG  << QS_BASE_SHIFT)
/// TC message base value
#define QS_BASE_MSG_TC          (QSQUEUE_TC << QS_BASE_SHIFT)
/// TM message base value
#define QS_BASE_MSG_TM          (QSQUEUE_TM << QS_BASE_SHIFT)

// SPAT/MAP message base value
#define QS_BASE_MSG_SPATMAP     (QSQUEUE_SPATMAP << QS_BASE_SHIFT)
// CPM message base value
#define QS_BASE_MSG_CPM         (QSQUEUE_CPM << QS_BASE_SHIFT)

/// IVI message base value
#define QS_BASE_MSG_IVI         (QSQUEUE_IVI << QS_BASE_SHIFT)
/// TIM message base value
#define QS_BASE_MSG_TIM         (QSQUEUE_TIM << QS_BASE_SHIFT)
/// RSICN message base value
#define QS_BASE_MSG_RSICN       (QSQUEUE_RSICN << QS_BASE_SHIFT)
/// PVD message base value
#define QS_BASE_MSG_PVD         (QSQUEUE_PVD << QS_BASE_SHIFT)
/// LDM message base value
#define QS_BASE_MSG_LDM         (QSQUEUE_LDM << QS_BASE_SHIFT)

/// Define System message group
#define QS_BASE_MSG_SYSTEM      (0x0fff << QS_BASE_SHIFT)

/// Application1 message base value
#define QS_BASE_MSG_APP1        (QSQUEUE_APP1 << QS_BASE_SHIFT)
/// Application2 message base value
#define QS_BASE_MSG_APP2        (QSQUEUE_APP2 << QS_BASE_SHIFT)
/// Application3 message base value
#define QS_BASE_MSG_APP3        (QSQUEUE_APP3 << QS_BASE_SHIFT)
/// Application4 message base value
#define QS_BASE_MSG_APP4        (QSQUEUE_APP4 << QS_BASE_SHIFT)
/// Application5 message base value
#define QS_BASE_MSG_APP5        (QSQUEUE_APP5 << QS_BASE_SHIFT)

/// IPC to Cohda message base value
#define QS_BASE_MSG_TOCOHDA     (QSQUEUE_IPC_TOCOHDA << QS_BASE_SHIFT)
/// IPC from Cohda message base value
#define QS_BASE_MSG_FROMCOHDA   (QSQUEUE_IPC_FROMCOHDA << QS_BASE_SHIFT)

/// Application8 message base value
#define QS_BASE_MSG_APP8        (QSQUEUE_APP8 << QS_BASE_SHIFT)
/// Application9 message base value
#define QS_BASE_MSG_APP9        (QSQUEUE_APP9 << QS_BASE_SHIFT)

#define QS_BASE_MSG_TIME        (QSQUEUE_TIME << QS_BASE_SHIFT)
#define QS_BASE_MSG_P1609_TX    (QSQUEUE_P1609_TX << QS_BASE_SHIFT)
#define QS_BASE_MSG_DAS         (QSQUEUE_DAS << QS_BASE_SHIFT)
#define QS_BASE_MSG_P1609_CTRL  (QSQUEUE_P1609_CTRL << QS_BASE_SHIFT)
#define QS_BASE_MSG_P1609_RX    (QSQUEUE_P1609_RX << QS_BASE_SHIFT)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// System message identifiers
typedef enum
{
  /// System no message event
  QSMSG_SYS_NO_MESSAGE         = QS_BASE_MSG_SYSTEM,
  /// System configuration update to worker threads
  QSMSG_SYS_CONF,
  /// System terminate message to worker threads
  QSMSG_SYS_TERMINATE
} tSystemMsdId;

/// Supported messages in ETSI G5
typedef enum
{
  // Mon thread
  QSMSG_ETSI_G5_MON_PERIODIC_MSG = QS_BASE_MSG_ETSI_G5_MON,

  // Tx thread
  QSMSG_ETSI_G5_TX_UPDATE_CFG = QS_BASE_MSG_ETSI_G5_TX,
  /// G5 transmit Pkt Buf message
  QSMSG_ETSI_G5_TX_MSG,
  /// G5 identity change message
  QSMSG_ETSI_G5_IDCHANGE_MSG,
  /// G5 Tx power change message
  QSMSG_ETSI_G5_TXPOWERCHANGE_MSG,
  /// G5 transmit trigger message for G5 LLC client frames
  QSMSG_ETSI_G5_TX_CLIENT_MSG,

} tETSIG5MsgId;

/// Supported messages in SAEC PC5
typedef enum
{
  // Tx thread
  /// Transmit Pkt Buf message
  QSMSG_SAEC_PC5_TX_MSG = QS_BASE_MSG_SAEC_PC5_TX,

} tSAECPC5MsgId;


/// Supported messages in ETSI GN
typedef enum
{
  /// only dummy message
  QSMSG_ETSI_GN_UPDATE_CFG = QS_BASE_MSG_ETSI_GN,
  /// GN transmit source message
  QSMSG_ETSI_GN_TX_MSG,
  /// GN transmit forward message
  QSMSG_ETSI_GN_FWD_MSG,
  /// GN transmit buffered message
  QSMSG_ETSI_GN_BUF_MSG,
  /// GN transmit CBF timed-out immediate message
  QSMSG_ETSI_GN_IMM_MSG,
  /// GN receive message (from G5)
  QSMSG_ETSI_GN_RX_MSG,
  /// GN receive secure/signed message (from G5)
  QSMSG_ETSI_GN_RX_SEC_MSG,
  /// Trigger to perform periodic processing (LPH etc.)
  QSMSG_ETSI_GN_PERIODIC_MSG,
  /// Trigger to transmit a GN beacon
  QSMSG_ETSI_GN_BEACON_MSG,
  /// Indicate GN ID change
  QSMSG_ETSI_GN_IDCHANGE,
  /// Indicate GN data reset
  QSMSG_ETSI_GN_DATA_RESET,
  /// Indicate GN Location Service timer event
  QSMSG_ETSI_GN_LOCSERV_MSG
} tETSIGNMsgId;

/// Supported messages in LPH
typedef enum
{
  /// Position fix for LPH
  QSMSG_LPH_POS_FIX = QS_BASE_MSG_LPH,
  /// VState message
  QSMSG_LPH_VSTATE_EVENT,
  /// Dynamic adjustment to position
  QSMSG_LPH_ADJUST_POS_FIX,
  /// External position fix handler for LPH
  QSMSG_LPH_EXTERNAL_POS_FIX,
  /// LPH leap second modes
  /// make sure this is last item of the enum, more messages defined in lph.h
  QSMSG_LPH_LEAP_SECOND_MODE,
} tLPHMsgId;

/// Supported messages in TIME
typedef enum
{
  /// P1609 SCH sync event
  QSMSG_TIME_SYNC_SCH = QS_BASE_MSG_TIME,
  /// P1609 CCH sync event
  QSMSG_TIME_SYNC_CCH,

} tTimeMsgId;

/// Supported messages in P1609 TX
typedef enum
{
  /// P1609 TX timer trigger message
  QSMSG_P1609_TX_TIMER_MSG = QS_BASE_MSG_P1609_TX,
  /// P1609 TX replay trigger message
  QSMSG_P1609_TX_REPLAY_MSG,
  /// P1609 TX instant trigger message
  QSMSG_P1609_TX_INSTANT_MSG,
  /// P1609 TX hybrid trigger message
  QSMSG_P1609_TX_HYBRID_MSG,
  /// P1609 TX SYNC trigger message
  QSMSG_P1609_TX_SYNC_MSG,
  /// P1609 TX security self verification
  QSMSG_P1609_TX_SEC_SELF,
  /// P1609 TX DOT2 message
  QSMSG_P1609_TX_DOT2_MSG
} tP1609_TXMsgId;

/// Supported messages in P1609 CTRL
typedef enum
{
  /// only dummy message
  QSMSG_P1609_CTRL_NO_MESSAGE = QS_BASE_MSG_P1609_CTRL
} tP1609_CTRLMsgId;

/// Supported messages in P1609 RX
typedef enum
{
  QSMSG_P1609_RX_WSM = QS_BASE_MSG_P1609_RX
} tP1609_RXMsgId;


/// Supported messages/events from EXT
typedef enum ExtEventId
{
  /// EXT received WSM
  /// @note include "dot3-wsmp.h" & cast pData to 'struct Dot3WSMPHdr *'
  QSMSG_EXT_RX_WSM = QS_BASE_MSG_EXT,
  /// EXT VSTATE vehicle event
  /// @note include "vstate.h" & cast pData to 'tVstateEventType'
  QSMSG_EXT_VSTATE_EVENT,
  /// EXT Dot3WMENotifInd event
  /// @note include "dot3-wme-api-types.h" & cast pData to 'tDot3WMENotifInd *'
  QSMSG_EXT_DOT3_WME_NOTIF_IND,
  /// EXT Tx BSM
  /// @note include "p1609-tx-msg.h" & cast pData to 'tBSMTxData *'
  QSMSG_EXT_TX_BSM,
  /// EXT received BTP message
  /// @note include "PacketBuffer.h" & cast pData to 'struct UtilPacketBuffer *'
  QSMSG_EXT_RX_BTP,
  /// EXT decoded message (CAM, DENM etc.)
  QSMSG_EXT_RX_ITSFL_PDU,
  /// EXT undecoded message (RAW)
  QSMSG_EXT_RX_ITSFL_MSG,
  /// EXT received GN message
  QSMSG_EXT_RX_GN,
  /// EXT received GN6 message
  QSMSG_EXT_RX_GN6,
  /// EXT LPH position fix update
  QSMSG_EXT_LPH_FIX,
  /// EXT FAC Tx info
  /// @note include "etsi-trx-if.h" & cast pData to 'tTRX_TxInfo'
  QSMSG_EXT_FAC_TX_INFO,
  /// EXT encoded message (BSM/SPAT/MAP/RSI/RSM)
  QSMSG_EXT_TX_SAECFL_PDU,
  /// EXT decoded message (BSM/SPAT/MAP/RSI/RSM)
  QSMSG_EXT_RX_SAECFL_PDU,
} eExtEventId;

/// Supported messages in STATS
typedef enum
{
  /// Status Update Message
  QSMSG_STATS_RECV_GPS_STAT = QS_BASE_MSG_STATS
} tStatsMsgId;

#endif // __ID_GLOBAL_H_

// Close the Doxygen group
/**
 * @}
 */

