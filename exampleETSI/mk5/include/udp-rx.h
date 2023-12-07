/**
 * @addtogroup udp_rx_api ETSI ITS UDP BTP API
 * @{
 *
 * Define supported messages for UDP/BTP messaging interface
 * The 'data request' allows an external client to sent a UDP datagram to trigger a GN packet transmission
 * The 'data indication' allows an external client to receive a UDP datagram of a GN packet reception
 *
 * @file
 *
 * Interface message ID definitions
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UDPBTP_RX_IF_H_
#define __UDPBTP_RX_IF_H_

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

/// UDP data read buffer
#define UDP_DATA_READ_BUFFER  (4 * 1024)

/// UDP security SSP bits length (in bytes)
#define UDPRX_SEC_SSP_BITS_LENGTH 32

/// UDP security Cert Id length (in bytes)
#define UDPRX_SEC_CERT_ID_LENGTH 8

/// UDP supported message interface version
/// Version 4 avoids conflict with existing message formats
#define UDPRX_MSG_INTERFACE_VERSION 4

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Security Types
typedef enum UDPBTPMsgId
{
  /// BTP Data Request
  UDPBTP_MSG_DATAREQ = 0,
  /// BTP Data Indication
  UDPBTP_MSG_DATAIND = 1,

  /// BTP max number of supported messages
  UDPRX_MSG_MAX = 2

} eUDPBTPMsgId;

/// Security Types
typedef enum UDPBTPDataSecType
{
  /// No security
  UDPRX_SEC_NONE = 0,
  /// Security - ITS-AID and SSP bitmap
  /// (SSP data expected to contain leading version octet before bitmap)
  UDPRX_SEC_AID_SSP_BITMAP = 1,
  /// Security - ITS-AID and opaque SSP data
  /// (opaque SSP data can be zero-length for ITS-AID only usage) 
  UDPRX_SEC_AID_SSP_OPAQUE = 2

} eUDPBTPDataSecType;

/// UDP BTP Message Type
typedef struct UDPBTPMsgType
{
  /// Version
  uint8_t Version;
  /// Message ID
  uint8_t MsgID;
  /// Message length (amount following, Big Endian)
  uint16_t MsgLen;
} tUDPBTPMsgType;

/// UDP BTP Data Req header (with Security)
typedef struct UDPBTPDataReqHdr
{
  /// BTP Type @ref ETSIGeoNetNH
  uint8_t BTPType;
  /// GN Packet Transport type @ref ETSIGeoNetTransport
  uint8_t PktTransport;
  /// GN Traffic Class @ref ETSIGeoNetTC
  uint8_t TrafficClass;
  /// GN Maximum Packet Lifetime (seconds, 0 will select GN MIB DefaultPacketLifetime)
  uint8_t MaxPktLifetime;

  /// BTP Destination Port (BTP-A & BTP-B BTPTypes)
  uint16_t DestPort;

  /// BTP Additional Port Information
  union
  {
    /// Source Port (BTP-A)
    uint16_t SrcPort;
    /// Destination Port Info (BTP-B)
    uint16_t DestInfo;
  };

  /// GBC/GAC/GUC Destination Information
  union
  {
    /// Location for GeoUnicast
    struct
    {
      /// Address of destination station
      uint64_t GN_ADDR_as_64;
      // Padding
      uint64_t Unused;
    } Location;
    /// Area for GBC or GAC
    struct
    {
      /// WGS-84 latitude for the centre position of shape [1/10 micro degree]
      int32_t Latitude;
      /// WGS-84 longitude for the centre position of shape [1/10 micro degree]
      int32_t Longitude;
      /// Distance a of the geometric shape [metres] (always non-zero)
      uint16_t Distance_a;
      /// Distance b of the geometric shape [metres]
      uint16_t Distance_b;
      /// Angle of the geometric shape [degrees from North]
      uint16_t Angle;
      // Shape @ref ETSIGeoNetDestType
      uint8_t Shape;
      // Padding
      uint8_t Unused;
    } Area;
  };

  /// GN Communication Profile @ref ETSIGeoNetProfile
  uint8_t CommProfile;
  /// GN Repetition Interval (unsupported)
  uint8_t RepeatInterval;

  /// GN Security Type @ref UDPBTPDataSecType
  uint8_t SecProfile;
  /// For secure packets (SecProfile != UDPRX_SEC_NONE):
  /// SSP len (0-UDPRX_SEC_SSP_BITS_LENGTH)
  uint8_t SSPLen;
  /// ITS-AID (numerical value)
  uint32_t AID;
  /// SSP Bits/Data
  uint8_t SSPBits[UDPRX_SEC_SSP_BITS_LENGTH];

  /// The length in octets of the 'on-the-air' frame data
  uint16_t Length;
} __attribute__ ((packed)) tUDPBTPDataReqHdr;

/// UDP BTP Data Req message
typedef struct UDPBTPDataReqMsg
{
  /// Message type
  tUDPBTPMsgType Type;
  /// Message header
  tUDPBTPDataReqHdr Hdr;
  /// Message payload
  uint8_t Payload[1];
} __attribute__ ((packed)) tUDPBTPDataReqMsg;


/// UDP BTP Data Ind Header (with Security)
typedef struct UDPBTPDataIndHdr
{
  /// BTP Type @ref ETSIGeoNetNH
  uint8_t BTPType;
  /// GN Packet Transport type @ref ETSIGeoNetTransport
  uint8_t PktTransport;
  /// GN Traffic Class @ref ETSIGeoNetTC
  uint8_t TrafficClass;
  /// GN Maximum Packet Lifetime (seconds)
  uint8_t MaxPktLifetime;

  /// BTP Destination Port (BTP-A & BTP-B BTPTypes)
  uint16_t DestPort;

  /// BTP Additional Port Information
  union
  {
    /// Source Port (BTP-A)
    uint16_t SrcPort;
    /// Destination Port Info (BTP-B)
    uint16_t DestInfo;
  };

  /// GBC/GAC/GUC Destination Information
  union
  {
    /// Location for GeoUnicast
    /// (PktTransport == ETSI_GN_TRANSPORT_GEOUNICAST)
    struct
    {
      /// Address of destination station
      uint64_t GN_ADDR_as_64;
      /// WGS-84 latitude of the GeoAdhoc router expressed in 1/10 micro degree
      int32_t Lat;
      /// WGS84 longitude of the GeoAdhoc router expressed in 1/10 micro degree
      int32_t Long;
    } Location;
    /// Area for GBC or GAC
    /// (PktTransport == ETSI_GN_TRANSPORT_GEOBROADCAST) ||
    /// (PktTransport == ETSI_GN_TRANSPORT_GEOANYCAST)
    struct
    {
      /// WGS-84 latitude for the centre position of shape [1/10 micro degree]
      int32_t Latitude;
      /// WGS-84 longitude for the centre position of shape [1/10 micro degree]
      int32_t Longitude;
      /// Distance a of the geometric shape [metres] (always non-zero)
      uint16_t Distance_a;
      /// Distance b of the geometric shape [metres]
      uint16_t Distance_b;
      /// Angle of the geometric shape [degrees from North]
      uint16_t Angle;
      // Shape @ref ETSIGeoNetDestType
      uint8_t Shape;
      // Padding
      uint8_t Unused;
    } Area;
  };

  /// GN Security Type @ref UDPBTPDataSecType
  uint8_t SecProfile;

  /// For Secure Packets (SecProfile != UDPRX_SEC_NONE):
  /// Result of Security Parsing @ref C2XSEC_ParserResult
  uint8_t ParserResult;
  /// Result of Security Verification @ref C2XSEC_VerificationResult
  uint8_t VerificationResult;
  /// SSP Length
  uint8_t SSPLen;
  /// ITS-AID (numerical value)
  uint32_t AID;
  /// SSP Bits/Data
  uint8_t SSPBits[UDPRX_SEC_SSP_BITS_LENGTH];
  /// CertID8
  /// (NOTE: Cohda_Crypto_Verify_Stats must be enabled as well to get CertID8)
  uint8_t CertId[UDPRX_SEC_CERT_ID_LENGTH];

  /// The length in octets of the 'on-the-air' frame data
  uint16_t Length;
} __attribute__ ((packed)) tUDPBTPDataIndHdr;

/// UDP BTP Ind message
typedef struct UDPBTPDataIndMsg
{
  /// Message type
  tUDPBTPMsgType Type;
  /// Message header
  tUDPBTPDataIndHdr Hdr;
  /// Message payload
  uint8_t Payload[1];
} __attribute__ ((packed)) tUDPBTPDataIndMsg;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void UDPBTPRX_ThreadInit (int SchedulerPolicy,
                          int SchedulerPriority_pc);

void UDPBTPRX_ThreadDeinit (void);

#ifdef __cplusplus
}
#endif

#endif // __UDPBTP_RX_IF_H_

/**
 * @}
 */
