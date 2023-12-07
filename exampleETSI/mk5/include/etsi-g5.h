/**
 * @addtogroup v2x_etsi_g5 ETSI ITS G5 Access elements
 * @{
 *
 * @file
 *
 * ETSI G5 interface definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_G5_H_
#define __ETSI_G5_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Size of FCS check that is added to the payload
#define ETSIG5_FCS_SIZE 4

/// Allow 'Cohda' TxPower to be set with 1dBm step value
#define ETSIG5_TXPOWER_FROM_DBM(power) (power * 2)

/// Allow 'Cohda' RxPower to be measured with 1dBm step value
#define ETSIG5_RXPOWER_TO_DBM(rxpower) (rxpower / 2)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Data rate
typedef enum ETSIG5DataRate
{
  /// Use the defualt value in the MIB
  ETSI_G5_FRAME_DATARATE_MIB = 0xFF,
  /// 1.5 Mb/s
  ETSI_G5_FRAME_DATARATE_1MBPS = 3,
  /// 2.25 Mb/s ()
  ETSI_G5_FRAME_DATARATE_2MBPS = 4, // actually 4.5
  /// 3 Mb/s
  ETSI_G5_FRAME_DATARATE_3MBPS = 6,
  /// 4.5 Mb/s
  ETSI_G5_FRAME_DATARATE_4MBPS = 9,
  /// 6 Mb/s
  ETSI_G5_FRAME_DATARATE_6MBPS = 12,
  /// 18 = 9 Mb/s
  ETSI_G5_FRAME_DATARATE_9MBPS = 18,
  /// 12 Mb/s
  ETSI_G5_FRAME_DATARATE_12MBPS = 24,
  /// 13.5 Mb/s
  ETSI_G5_FRAME_DATARATE_13MBPS = 27,
  /// 18 Mb/s
  ETSI_G5_FRAME_DATARATE_18MBPS = 36,
  /// 24 Mb/s
  ETSI_G5_FRAME_DATARATE_24MBPS = 48,
  /// 27 Mb/s
  ETSI_G5_FRAME_DATARATE_27MBPS = 54,
  /// 36 Mb/s
  ETSI_G5_FRAME_DATARATE_36MBPS = 72,
  /// 48 Mb/s
  ETSI_G5_FRAME_DATARATE_48MBPS = 96,
  /// 54 Mb/s
  ETSI_G5_FRAME_DATARATE_54MBPS = 108,
} eETSIG5DataRate;

/// Transmit power [0.5 dBm]
typedef enum ETSIG5TxPwr
{
  /// Use the default value in the MIB.
  ETSI_G5_FRAME_TXPWR_MIB = -128, // 0x80 (SCHAR_MIN)
  /// Mimimum output power (-63.5 dBm)
  ETSI_G5_FRAME_TXPWR_MIN = -127,
  /// Maximum output power (63.5 dBm)
  ETSI_G5_FRAME_TXPWR_MAX = 127,

} eETSIG5TxPwr;

/// Priority (ITS-G5)
typedef enum ETSIG5AccessClass
{
  /// Access class Voice
  ETSI_G5_FRAME_PRIORITY_AC_VO = 0, // highest priority
  /// Access class Video
  ETSI_G5_FRAME_PRIORITY_AC_VI = 1,
  /// Access class Best Effort
  ETSI_G5_FRAME_PRIORITY_AC_BE = 2,
  /// Access class Background
  ETSI_G5_FRAME_PRIORITY_AC_BK = 3, // lowest priority
} eETSIG5AccessClass;

/// Priority (PC5)
typedef enum ETSIPC5PPPP
{
  /// PPP Priority 0
  ETSI_PC5_PPPPRIORITY_O = 0, // highest priority
  /// PPP Priority 1
  ETSI_PC5_PPPPRIORITY_1 = 1,
  /// PPP Priority 2
  ETSI_PC5_PPPPRIORITY_2 = 2,
  /// PPP Priority 3
  ETSI_PC5_PPPPRIORITY_3 = 3,
  /// PPP Priority 4
  ETSI_PC5_PPPPRIORITY_4 = 4,
  /// PPP Priority 5
  ETSI_PC5_PPPPRIORITY_5 = 5,
  /// PPP Priority 6
  ETSI_PC5_PPPPRIORITY_6 = 6,
  /// PPP Priority 7
  ETSI_PC5_PPPPRIORITY_7 = 7, // lowest priority

} eETSIPC5PPPP;

/// ETSI G5 message format
/// This is the expected data format for all frames
typedef struct ETSIG5Desc
{
  union
  {
    /// Tx specific fields used when transmitting packets
    struct
    {
      /// Destination MAC Address
      uint8_t DA[6];
      /// DCC profile identifier (DP0=0x0 ... DP32=0x20)
      uint8_t DP;
      /// The transmit power used for the frame [0.5 dBm] @sa eETSIG5TxPwr
      int8_t TxPower;
      /// Expiry Time (absolute MAC time in microseconds, 0=no expiry)
      uint64_t ExpiryTime;
    } Tx;
    /// Rx specific fields
    struct
    {
      /// Source MAC Address
      uint8_t SA[6];
      /// RSSI [dBm]
      int8_t RSSI;
      /// Average Channel Load (%)
      uint8_t ChanLoad;
      /// Sequence number
      uint16_t SequenceNumber;
    } Rx;
  };
  /// Priority @sa eETSIG5AccessClass (ITS-G5)
  /// Priority @sa eETSIPC5PPPP (PC5)
  uint8_t AccessClass;
  /// The radio channel used for the frame
  uint8_t ChannelNumber;
  /// The data rate used for the frame @sa eETSIG5DataRate
  uint8_t DataRate;
  /// The length in octets of the 'Payload' field
  uint16_t Length;
  /// Pointer to the 'on-the-air' frame data
  uint8_t *pData;
} tETSIG5Desc;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// functions for setting up IPv6 native interface (via LLC)
// @Note this needs a re-design and ultimately moving away from here
int ETSIG5_NativeIPv6Setup ();
void ETSIG5_NativeIPv6Release ();

#ifdef __cplusplus
}
#endif

#endif // __ETSI_G5_H_

/**
 * @}
 */
