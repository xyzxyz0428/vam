// No doxygen 'group' header because this file is included by both user & kernel implmentations

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __LINUX__IEEE1609__DOT3__DOT3_WSMP_H__
#define __LINUX__IEEE1609__DOT3__DOT3_WSMP_H__

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/socket.h>
#include <net/sock.h>
#else
#include <stdint.h>
#include <stdbool.h>

#if (!defined(__THREADX__))
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#include <nx_api.h>
#include <nxd_bsd.h>
typedef unsigned short sa_family_t;
#endif
#endif

/// Protocol family definition.
#define AF_IEEE1609                (AF_SNA)
#define PF_IEEE1609                (AF_IEEE1609)
#define AF_IEEE1609_WSMP           (AF_IEEE1609)
#define PF_IEEE1609_WSMP           (PF_IEEE1609)
#define PROTO_IEEE1609DOT3_WSMP    (0)
#define PROTO_IEEE1609DOT3_WSMPS   (129)

/// EtherType: WSMP
#define ETH_P_DOT3_WSMP            (0x88DC)
/// EtherType: IPv6
#define ETH_P_DOT3_IPV6            (0x86DD)

/// WSM version values
typedef enum Dot3WSMPVersion
{
  /// WSM version: trial use
  DOT3_WSMP_VERSION_2009     = 0x01,
  DOT3_WSMP_VERSION_TRIALUSE = 0x01,
  /// WSM version: full use
  DOT3_WSMP_VERSION_2010     = 0x02,
  DOT3_WSMP_VERSION_FULLUSE  = 0x02,
  /// WSM version: full use
  DOT3_WSMP_VERSION_2016     = 0x03,
  DOT3_WSMP_VERSION_3        = 0x03,
  /// Masks for accessing parts of Version octet (shared)
  DOT3_WSMP_SUBTYPE_MASK     = 0xF0,
  DOT3_WSMP_N_OPTION_MASK    = 0x08,
  DOT3_WSMP_VERSION_MASK     = 0x07,
} eDot3WSMPVersion;

/// WSM security indicator flags
typedef enum Dot3WSMPSecurity
{
  /// Unsecured WSM
  DOT3_WSMP_WSM_SEC_UNSECURED   = 0x01,
  /// Signed WSM (not encrypted)
  DOT3_WSMP_WSM_SEC_SIGNED      = 0x02,
  /// Encypted WSM
  DOT3_WSMP_WSM_SEC_ENCRYPTED   = 0x04,
  /// Certificate attached
  DOT3_WSMP_WSM_SEC_CERTIFICATE = 0x10,
  /// Certificate digest attached
  DOT3_WSMP_WSM_SEC_DIGEST      = 0x20,
  /// IEEE 1609.2-2010 (full-use)
  DOT3_WSMP_WSM_SEC_V2          = 0x40,
  /// IEEE 1609.2-2015
  DOT3_WSMP_WSM_SEC_V3          = 0x80,

} eDot3WSMPSecurity;

/// WSM data rate
typedef enum Dot3WSMPDataRate
{
  /// Use the value in the MIB. This is same as NOT_PRSNT.
  DOT3_WSMP_WSM_DATARATE_MIB = 0xFF,
  /// 1.5 Mb/s
  DOT3_WSMP_WSM_DATARATE_1MBPS = 3,
  /// 2.25 Mb/s ()
  DOT3_WSMP_WSM_DATARATE_2MBPS = 4, // actually 4.5
  /// 3 Mb/s
  DOT3_WSMP_WSM_DATARATE_3MBPS = 6,
  /// 4.5 Mb/s
  DOT3_WSMP_WSM_DATARATE_4MBPS = 9,
  /// 6 Mb/s
  DOT3_WSMP_WSM_DATARATE_6MBPS = 12,
  /// 18 = 9 Mb/s
  DOT3_WSMP_WSM_DATARATE_9MBPS = 18,
  /// 12 Mb/s
  DOT3_WSMP_WSM_DATARATE_12MBPS = 24,
  /// 13.5 Mb/s
  DOT3_WSMP_WSM_DATARATE_13MBPS = 27,
  /// 18 Mb/s
  DOT3_WSMP_WSM_DATARATE_18MBPS = 36,
  /// 24 Mb/s
  DOT3_WSMP_WSM_DATARATE_24MBPS = 48,
  /// 27 Mb/s
  DOT3_WSMP_WSM_DATARATE_27MBPS = 54,
  /// 36 Mb/s
  DOT3_WSMP_WSM_DATARATE_36MBPS = 72,
  /// 48 Mb/s
  DOT3_WSMP_WSM_DATARATE_48MBPS = 96,
  /// 54 Mb/s
  DOT3_WSMP_WSM_DATARATE_54MBPS = 108,
} eDot3WSMPDataRate;

/// WSM transmit power [dBm]
typedef enum Dot3WSMPTxPwr
{
  /// Use the value in the MIB. This is the same as NOT_PRSNT.
  DOT3_WSMP_WSM_TXPWR_MIB = -128, // 0x80 (SCHAR_MIN)
  /// Mimimum output power
  DOT3_WSMP_WSM_TXPWR_MIN = -64,
  /// Maximum output power
  DOT3_WSMP_WSM_TXPWR_MAX = 64,

} eDot3WSMPTxPwr;

/// PSID range is 0x00000001 to 0x7FFFFFFF
/// Special PSID: all
#define DOT3_WSMP_PSID_ALL   0x80000000
/// Special PSID default value: none (send only socket)
#define DOT3_WSMP_PSID_NONE  0xFFFFFFFF

/// dot3 not present field define
#define DOT3_WSMP_FIELD_NOT_PRSNT  0x80

/// WSMP Wave Element Id
#define DOT3_WSMP_ELMID_WSM         128
#define DOT3_WSMP_ELMID_WSMS        129

/// WSM 'N' and 'T' extension flags
typedef enum Dot3WSMPExtFlag
{
  /// WSM-N header extentions: Channel number
  DOT3_WSMP_WSM_EXT_N_CHANNEL  = 0x01,
  /// WSM-N header extentions: DataRate
  DOT3_WSMP_WSM_EXT_N_DATARATE = 0x02,
  /// WSM-N header extentions: TxPwr
  DOT3_WSMP_WSM_EXT_N_TXPWR    = 0x04,
  /// WSM-N header extentions: TxPwr
  DOT3_WSMP_WSM_EXT_N_CHANLOAD = 0x08,
  /// Mask for WSM-N fields
  DOT3_WSMP_WSM_EXT_N_MASK     = 0x0f,
  // 0x10..0x80 : TBD
  /// Mask for WSM-T fields
  DOT3_WSMP_WSM_EXT_T_MASK     = 0xf0,
} eDot3WSMPExtFlag;

// Socket stuff and address definitions.

/// WSMP/WSMP-S message format
/// This is the expected data format when sendto() and recvmsg() are called
typedef struct Dot3WSMPHdr
{
  union
  {
    /// Tx specific fields used when transmitting packets
    struct
    {
      /// Destination MAC Address
      uint8_t DA[6];
      /// Priority
      uint8_t Priority;
      /// Expiry Time
      uint8_t ExpiryTime;
    } Tx;
    /// Rx specific fields
    struct
    {
      /// Source MAC Address
      uint8_t SA[6];
      /// RSSI [dBm]
      int8_t RSSI;
      /// Reserved for alignment purposes or future use
      uint8_t Align1;
    } Rx;
  };
  /// WSM Subtype & Version
  uint8_t Version;
  /// The radio channel used for the WSM
  uint8_t ChannelNumber;
  /// The data rate used for the WSM.
  uint8_t DataRate;
  /// The transmit power used for the WSM [dBm]
  int8_t TxPower;
  /// The application that originated the WSM
  /// @note network byte order (Big endian) so use ntohl & htonl
  uint32_t PSID;
  /// The length in octets of the WSM Data field
  /// @note network byte order (Big endian) so use ntohs & htons
  uint16_t Length;
  union {
    /// 1609.3-2010: if (Version =< 2)
    struct {
      /// The WAVE element ID (WSMP or WSMP-S)
      uint8_t WAVEElementId;
      /// Reserved for alignment purposes (and/or future use)
      uint8_t Align;
      /// WSMP-S control field (only if WAVEElementId==DOT3_WSMP_ELMID_WSMS)
      /// @note network byte order (Big endian) so use ntohl & htonl
      uint32_t Control;
    };
    /// 1609.3-2016: if (Version & 0x07 == 0x3)
    struct {
      /// WSM-N/T header fields included/to include in over-the-air message
      /// See @sa Dot3WSMPExtFlag
      uint8_t HdrExtFlags;
      /// Reserved for alignment purposes (and/or future use)
      uint8_t Reserved;
      /// The measured channel load (the 1st 4 bytes)
      uint32_t ChannelLoad;
    };

  };
  /// 'Extra' info
  struct
  {
    /// The extra length in octets
    /// @note network byte order (Big endian) so use ntohs & htons
    uint16_t     Length;
    union {
      /// Reserved for alignment purposes (and/or future use)
      uint8_t    Reserved[6];
      /// IEEE1609.2 security flags @sa Dot3WSMPSecurity
      uint8_t    Dot2Flags;
    };
  } Extra;
  /// Pointer to the WSM Data field (actually it just follows the header)
  uint8_t Data[0];
} __attribute__ ((packed)) tDot3WSMPHdr;

/// WSMP header size
#define WSMP_HDR_SIZE            (sizeof(struct Dot3WSMPHdr))

/// WSMP address structure.
/// We need the sock address structure for the bind, connect and other socket calls.
typedef struct Dot3WSMPSockAddr
{
  /// AF_IEEE1609_WSMP only
  sa_family_t Family;
  /// Receive packet UTC timestamp: populated by recvfrom() call
  uint64_t RxUTC;
  /// For bind() usage [sendto() usage later on]
  /// Peer MAC address (usually broadcast)
  uint8_t Peer[6];
  /// Default WSM header values @ref ieee1609dot3_arch_wsmp
  struct Dot3WSMPHdr Hdr;
} __attribute__ ((packed)) tDot3WSMPSockAddr;

/// WSMP Profile Info structure
/// This structure is used for Performance Benchmarking
struct Dot3WSMPProfileInfo
{
  long int Dot3_WSMPSendMsgTime;
  long int Dot4_WSMPLoopbackTime;
  long int Dot3_WSMPRecvMsgTime;
  long int Dot3_WSMPAppSendMsgTime;
  long int Dot3_WSMPAppRecvMsgTime;
} __attribute__ ((packed));

#endif // #ifndef __LINUX__IEEE1609__DOT3__DOT3_WSMP_H__
