/**
 * @addtogroup v2x_etsi_gn ETSI ITS Network elements
 * @{
 *
 * @file
 *
 * ETSI GN interface definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_GN_H_
#define __ETSI_GN_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

#include "c2xsec.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Basic header length
#define GNBASIC_HDR_LEN (sizeof(tETSIGeoNetBasicHdr))

/// Helper for Tx Power setting
#define ETSI_GN_TX_POWER_FROM_DBM(db_val) ((db_val) * 2)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// GeoNetworking address
typedef struct ETSIGeoNetAddr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
          /// Reserved (MSB)
  uint8_t Res_M :2,
          /// ITS Station Type @ref ETSIGeoNetStationType
          ST :5,
          /// M is set to 1 if the address is manually configured
          M :1;
#else
          /// M is set to 1 if the address is manually configured
  uint8_t M :1,
          /// ITS Station Type @ref ETSIGeoNetStationType
          ST :5,
          /// Reserved (MSB)
          Res_M :2;
#endif
  /// Reserved (LSB) - LS 8 bits split from MS 2 bits
  /// as field spans octet boundary and gcc bit packing doesn't
  /// allow this to be defined.
  // Probably should use mask & shift instead!
  uint8_t Res_L :8;
  /// Represents the LL_ADDR (MAC address)
  uint64_t  MID :48;
} __attribute__ ((packed)) tETSIGeoNetAddr;

/// Packet transport type
typedef enum ETSIGeoNetTransport
{
  /// Beacon
  ETSI_GN_TRANSPORT_BEACON = 0x1,
  /// GeoUnicast
  ETSI_GN_TRANSPORT_GEOUNICAST = 0x2,
  /// Geographically-Scoped Anycast (GAC)
  ETSI_GN_TRANSPORT_GEOANYCAST = 0x3,
  /// Geographically-Scoped broadcast (GBC)
  ETSI_GN_TRANSPORT_GEOBROADCAST = 0x4,
  /// Topologically-scoped broadcast (TSB)
  ETSI_GN_TRANSPORT_TSB = 0x5,
  /// Single hop broadcast (SHB)
  ETSI_GN_TRANSPORT_SHB = 0x7,
  /// Location Serivice Request (LS)
  ETSI_GN_TRANSPORT_LS_REQ = 0x8,
  /// Location Serivice Reply (LS)
  ETSI_GN_TRANSPORT_LS_REPLY = 0x9,

} eETSIGeoNetTransport;

/// Destination area type
typedef enum ETSIGeoNetDestType
{
  /// Circular area
  ETSI_GN_DEST_TYPE_CIRCLE = 0x0,
  /// Rectangular area
  ETSI_GN_DEST_TYPE_RECT = 0x1,
  /// Ellipsoidal area
  ETSI_GN_DEST_TYPE_ELIP = 0x2,

  /// Allow auto-population of shape centre position
  ETSI_GN_DEST_TYPE_POS_AUTO = 0x80,

} eETSIGeoNetDestType;

/// Next Header (NH) field in the Basic Header
typedef enum ETSIGeoNetBasicNH
{
  /// Unspecified
  ETSI_GN_BASIC_NH_ANY = 0x0,
  /// GeoNetworking Common Header
  ETSI_GN_BASIC_NH_COMMON = 0x1,
  /// GeoNetworking Secured Packet
  ETSI_GN_BASIC_NH_SECURED = 0x2,

} eETSIGeoNetBasicNH;

/// Next Header (NH) field in the Common Header
typedef enum ETSIGeoNetNH
{
  /// Unspecified
  ETSI_GN_NH_ANY = 0x0,
  /// Transport protocol (BTP-A for interactive packet transport)
  ETSI_GN_NH_BTPA = 0x1,
  /// Transport protocol (BTP-B for non-interactive packet transport)
  ETSI_GN_NH_BTPB = 0x2,
  /// IPv6 header
  ETSI_GN_NH_IPV6 = 0x3,

} eETSIGeoNetNH;

/// Security Type
typedef enum ETSIGeoNetSecPacket
{
  /// Clear
  ETSI_GN_SEC_PACKET_CLEAR = 0x0,
  /// Secure
  ETSI_GN_SEC_PACKET_SECURED = 0x1,

} eETSIGeoNetSecPacket;

/// Storage for Security Type (@ref ETSIGeoNetSecPacket)
typedef uint8_t tETSIGeoNetSecPacket;

/// GN (ITS-G5/CV2X) Communication Profile Identifier
typedef enum ETSIGeoNetProfile
{
  /// GN communication profile: Default
  ETSI_GN_PROFILE_DEFAULT = 0x00,

  /// GN communication profile: ITS-G5 (802.11)
  ETSI_GN_PROFILE_ITS_G5 = 0x80,
  /// GN communication profile: PC5 (LTE-V2X or 5G NR V2X)
  ETSI_GN_PROFILE_PC5 = 0x40,
  /// GN communication profile: Cellular-V2X (e.g. via UDP or MQTT)
  ETSI_GN_PROFILE_CV2X = 0x20,

  // Short range access technologies
  ETSI_GN_PROFILE_ITS_SHORT_RANGE = ETSI_GN_PROFILE_ITS_G5 | ETSI_GN_PROFILE_PC5,
  // Long range access technologies
  ETSI_GN_PROFILE_ITS_LONG_RANGE = ETSI_GN_PROFILE_CV2X,

} eETSIGeoNetProfile;

/// Storage for Communication Profile Identifier (@ref ETSIGeoNetProfile)
typedef uint8_t tETSIGeoNetProfile;

/// Max allowed Tx power
typedef enum ETSIGeoNetMaxTxPower
{
  /// Use the default value
  // (0 as DEFAULT means 0dBm not possible, but avoids erroneous power selection)
  ETSI_GN_TXPWR_DEFAULT = 0,
  /// Minimum output power (-63.5 dBm)
  ETSI_GN_TXPWR_MIN = -127,
  /// Maximum output power (63.5 dBm) (may be limited by other mechanisms)
  ETSI_GN_TXPWR_MAX = 127,

} eETSIGeoNetMaxTxPower;

/// GN Traffic Class values from GN-DATA ind
typedef enum ETSIGeoNetTCVals
{
  /// GN traffic class - store/carry-forward set
  ETSI_GN_TC_SCF_SET     = 0x80,
  /// GN traffic class - G5 channel offload set
  ETSI_GN_TC_OFFLOAD_SET = 0x40,

  /// GN traffic class identifier
  ETSI_GN_TC_ID_DP0      = 0x00,
  ETSI_GN_TC_ID_DP1      = 0x01,
  ETSI_GN_TC_ID_DP2      = 0x02,
  ETSI_GN_TC_ID_DP3      = 0x03,
  ETSI_GN_TC_ID_DP4      = 0x04,
  ETSI_GN_TC_ID_DP5      = 0x05,
  ETSI_GN_TC_ID_DP6      = 0x06,
  ETSI_GN_TC_ID_DP7      = 0x07,
  ETSI_GN_TC_ID_DP8      = 0x08,
  /// GN traffic classes DP9 to DP32 not used on CCH, will be sent on SCH
  ETSI_GN_TC_ID_DP9      = 0x09,
  ETSI_GN_TC_ID_DP10     = 0x0A,
  ETSI_GN_TC_ID_DP11     = 0x0B,
  ETSI_GN_TC_ID_DP12     = 0x0C,
  ETSI_GN_TC_ID_DP13     = 0x0D,
  ETSI_GN_TC_ID_DP14     = 0x0E,
  ETSI_GN_TC_ID_DP15     = 0x0F,
  ETSI_GN_TC_ID_DP16     = 0x10,
  ETSI_GN_TC_ID_DP17     = 0x11,
  ETSI_GN_TC_ID_DP18     = 0x12,
  ETSI_GN_TC_ID_DP19     = 0x13,
  ETSI_GN_TC_ID_DP20     = 0x14,
  ETSI_GN_TC_ID_DP21     = 0x15,
  ETSI_GN_TC_ID_DP22     = 0x16,
  ETSI_GN_TC_ID_DP23     = 0x17,
  ETSI_GN_TC_ID_DP24     = 0x18,
  ETSI_GN_TC_ID_DP25     = 0x19,
  ETSI_GN_TC_ID_DP26     = 0x1A,
  ETSI_GN_TC_ID_DP27     = 0x1B,
  ETSI_GN_TC_ID_DP28     = 0x1C,
  ETSI_GN_TC_ID_DP29     = 0x1D,
  ETSI_GN_TC_ID_DP30     = 0x1E,
  ETSI_GN_TC_ID_DP31     = 0x1F,
  ETSI_GN_TC_ID_DP32     = 0x20,

  /// GN traffic class - DP mask
  ETSI_GN_TC_ID_MASK     = 0x3F,

  /// GN traffic class - Use default values
  ETSI_GN_TC_DEFAULT     = 0xFF,

} eETSIGeoNetTCVals;

/// GN Hop limit values from GN-DATA ind
typedef enum ETSIGeoNetHopLimitVal
{
  /// GN hop limit default
  ETSI_GN_HOPLIMIT_DEFAULT = 0x00,

  /// otherwise GN hop-limit

} eETSIGeoNetHopLimitVal;

/// GN Lifetime values from GN-DATA ind
typedef enum ETSIGeoNetLifetimeVal
{
  /// GN lifetime default
  ETSI_GN_LT_DEFAULT = 0x00,

  /// otherwise GN lifetime in milli-seconds

} eETSIGeoNetLifetimeVal;

/// Traffic class that represents Facility-layer requirements on packet transport
/// Composed of three sub-fields
///   Bit 0: SCF
/// Indicates whether the packet shall be buffered when no neighbour exists
/// (store-carry-forward)
///   Bit 1: Channel Offload
/// Indicates whether the packet can be off-loaded to channel other than
/// that specified in the DCC profile ID.
///   Bits 2 to 7: DCC Profile ID
/// DCC Profile ID as specified in the media-dependent part of GeoNetworking
typedef struct ETSIGeoNetTC
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  /// DCC Profile ID value
  uint8_t DCCProfId :6,
          /// Channel Offload (1 = can offload)
          ChanOffload :1,
          /// SCF (1 = buffer when no neighbours)
          SCF :1;
#else
  /// SCF (1 = buffer when no neighbours)
  uint8_t SCF :1,
          /// Channel Offload (1 = can offload)
          ChanOffload :1,
          /// DCC Profile ID value (see @ref ETSIGeoNetTCVals)
          DCCProfId :6;
#endif
} __attribute__ ((packed)) tETSIGeoNetTC;

/// Destination/Source
typedef struct ETSIGeoNetDestSrc
{
  /// The network address for the GeoAdhoc router entity
  /// For Tx: GN_ADDR.MID must be set (everything else can be zeros)
  union
  {
    struct ETSIGeoNetAddr GN_ADDR;
    uint64_t GN_ADDR_as_64;
  };
  /// - All zeros for SHB
  /// - 'Location' for GeoUnicast
  /// - 'Area' for GeoBroadcast/GeoAnycast
  union
  {
    /// Location for GeoUnicast
    struct
    {
      /// WGS-84 latitude of the GeoAdhoc router expressed in 1/10 micro degree
      int32_t Lat;
      /// WGS-84 longitude of the GeoAdhoc router expressed in 1/10 micro degree
      int32_t Long;
      /// Expresses the rx time in milliseconds (modulo 2^32)
      uint32_t TST;
      // Padding
      uint32_t Unused;
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

} __attribute__ ((packed)) tETSIGeoNetDestSrc;

/// Position Accuracy Indicator and Speed
typedef struct ETSIGeoNetPAIS
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  /// Speed of the GeoAdhoc router expressed in signed units of 0.01 metres per second
  int16_t S:15;
  /// Position Accuracy Indicator
  /// Set to 1 (i.e. True) if the semiMajorConfidence of the PosConfidenceEllipse as
  /// specified in ETSI TS 102 894-2 is smaller than (itsGnPaiInterval / 2)
  /// Set to 0 (i.e. False) otherwise
  uint16_t PAI:1;
#else
  /// Position Accuracy Indicator
  /// Set to 1 (i.e. True) if the semiMajorConfidence of the PosConfidenceEllipse as
  /// specified in ETSI TS 102 894-2 is smaller than (itsGnPaiInterval / 2)
  /// Set to 0 (i.e. False) otherwise
  int16_t PAI:1;
  /// Speed of the GeoAdhoc router expressed in signed units of 0.01 metres per second
  int16_t S:15;
#endif
} __attribute__ ((packed)) tETSIGeoNetPAIS;

/// Long Position Vector
typedef struct ETSIGeoNetLPV
{
  /// The network address for the GeoAdhoc router entity
  union
  {
    struct ETSIGeoNetAddr GN_ADDR;
    uint64_t GN_ADDR_as_64;
  };
  /// Expresses the time in milliseconds at which the latitude and longitude of
  /// the ITS-S were acquired by the GeoAdhoc router. The time is encoded as:
  ///   TST = TST (TAI)mod 2^32
  /// where TST(TAI) is the number of elapsed TAI milliseconds
  /// since 2004-01-01 00:00:00.000 UTC.
  uint32_t TST;
  /// WGS-84 latitude of the GeoAdhoc router expressed in 1/10 micro degree
  int32_t Lat;
  /// WGS-84 longitude of the GeoAdhoc router expressed in 1/10 micro degree
  int32_t Long;
  union
  {
    uint16_t PAISpeed;
    struct ETSIGeoNetPAIS PAIS;
  };
  /// Heading of the GeoAdhoc router,
  /// expressed in unsigned units of 0.1 degree from North
  uint16_t H;
} __attribute__ ((packed)) tETSIGeoNetLPV;

/// Short Position Vector
typedef struct ETSIGeoNetSPV
{
  /// The network address for the GeoAdhoc router entity
  union
  {
    struct ETSIGeoNetAddr GN_ADDR;
    uint64_t GN_ADDR_as_64;
  };
  /// Expresses the time in milliseconds at which the latitude and longitude of
  /// the ITS-S were acquired by the GeoAdhoc router. The time is encoded as:
  ///   TST = TST (TAI)mod 2^32
  /// where TST(TAI) is the number of elapsed TAI milliseconds
  /// since 2004-01-01 00:00:00.000 UTC.
  uint32_t TST;
  /// WGS-84 latitude of the GeoAdhoc router expressed in 1/10 micro degree
  int32_t Lat;
  /// WGS-84 longitude of the GeoAdhoc router expressed in 1/10 micro degree
  int32_t Long;

} __attribute__ ((packed)) tETSIGeoNetSPV;

/// On-air ETSI GN message Basic Header format
typedef struct ETSIGeoNetBasicHdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  /// Type of header immediately following the GeoNetworking Basic header
  /// @ref ETSIGeoNetBasicNH
  uint8_t NH :4,
          /// Identifies the version of the GeoNetworking protocol
          Version :4;
#else
  /// Identifies the version of the GeoNetworking protocol
  uint8_t Version :4,
          /// Type of header immediately following the GeoNetworking Basic header
          /// @ref ETSIGeoNetBasicNH
          NH :4;
#endif

  /// Reserved for media-dependent functionality
  uint8_t Reserved;

  /// Lifetime field
  /// Indicates the maximum tolerable time a packet can be buffered until
  /// it reaches its destination.
  uint8_t LT;

  /// Remaining Hop Limit
  /// Decremented by 1 by each GeoAdhoc router that forwards the packet.
  /// The packet must not be forwarded if Hop Limit is decremented to zero
  uint8_t RHL;

} __attribute__ ((packed)) tETSIGeoNetBasicHdr;

/// On-air ETSI GN message Common Header format
typedef struct ETSIGeoNetCommonHdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
  /// Reserved
  uint8_t ReservedBits :4,
          /// Type of header immediately following the GeoNetworking Common header
          /// @ref ETSIGeoNetNH
          NH :4;
  /// Sub-type of the GeoAdhoc header
  /// @ref ETSIGeoNetHST
  uint8_t HST :4,
          /// Type of the GeoAdhoc header
          /// @ref ETSIGeoNetHT
          HT :4;
#else
  /// Type of header immediately following the GeoNetworking Common header
  /// @ref ETSIGeoNetNH
  uint8_t NH :4,
          /// Reserved
          ReservedBits :4;
  /// Type of the GeoAdhoc header
  /// @ref ETSIGeoNetHT
  uint8_t HT :4,
          /// Sub-type of the GeoAdhoc header
          /// @ref ETSIGeoNetHST
          HST :4;
#endif

  /// Traffic class that represents Facility-layer
  /// requirements on packet transport
  union
  {
    uint8_t TC;
    struct ETSIGeoNetTC Bits;
  };

  /// Bit 0: IsMobile station
  uint8_t Flags;

  /// Length of the Network Header payload, i.e. the
  /// rest of the packet following the whole
  /// GeoNetworking header in octets
  uint16_t PL;

  /// Maximum Hop Limit
  uint8_t MHL;

  /// Reserved
  uint8_t Reserved;

} __attribute__ ((packed)) tETSIGeoNetCommonHdr;

/// GeoNetworking header

/// Header Type (HT) field in the Common Header
typedef enum ETSIGeoNetHT
{
  /// Unspecified
  ETSI_GN_HT_ANY = 0x0,
  /// Beacon
  ETSI_GN_HT_BEACON = 0x1,
  /// GeoUnicast
  ETSI_GN_HT_GEOUNICAST = 0x2,
  /// Geographically-Scoped Anycast (GAC)
  ETSI_GN_HT_GEOANYCAST = 0x3,
  /// Geographically-Scoped broadcast (GBC)
  ETSI_GN_HT_GEOBROADCAST = 0x4,
  /// Topologically-scoped broadcast (TSB)
  ETSI_GN_HT_TSB = 0x5,
  /// Location service (LS)
  ETSI_GN_HT_LS = 0x6,

} eETSIGeoNetHT;

/// Header sub-type (HST) field in the Common Header
typedef enum ETSIGeoNetHST
{
  /// Unspecified
  ETSI_GN_HST_UNSPEC = 0x0,
  /// Circular area
  ETSI_GN_HST_CIRCLE = 0x0,
  /// Rectangular area
  ETSI_GN_HST_RECT = 0x1,
  /// Ellipsoidal area
  ETSI_GN_HST_ELIP = 0x2,
  /// Single-hop broadcast (SHB)
  ETSI_GN_HST_SINGLE_HOP = 0x0,
  /// Multi-hop TSB
  ETSI_GN_HST_MULTI_HOP = 0x1,
  /// Location service request
  ETSI_GN_HST_LS_REQUEST = 0x0,
  /// Location service reply
  ETSI_GN_HST_LS_REPLY = 0x1,

} eETSIGeoNetHST;

/// GeoUnicast packet header
typedef struct ETSIGeoNetUnicastHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Sequence number field
  uint16_t SN;
  /// Reserved for media-dependent functionality
  uint16_t Reserved;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  /// Short position vector of the destination
  struct ETSIGeoNetSPV DE_PV;
  /// Payload
  uint8_t Data[0];
} __attribute__ ((packed)) tETSIGeoNetUnicastHdr;

/// TSB packet header
typedef struct ETSIGeoNetTSBHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Sequence number field
  uint16_t SN;
  /// Reserved for media-dependent functionality
  uint16_t Reserved;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  /// Payload
  uint8_t Data[0];
} __attribute__ ((packed)) tETSIGeoNetTSBHdr;

/// SHB packet header
typedef struct ETSIGeoNetSHBHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  union MediaDep
  {
    struct G5SHB
    {
      /// DCC-MCO From ETSI TS 102 636-4-2 V1.1.1
      /// NOTE: Used when DCC is active
      /// Local CBR
      uint8_t CBR_L_0_Hop;
      /// High CBR from neighbours
      uint8_t CBR_L_1_Hop;
#if __BYTE_ORDER == __LITTLE_ENDIAN
      /// Reserved
      uint8_t ReservedBits :3,
              /// EIRP (0 to 31dBm)
              OutPowerdBm  :5;
#else
      /// EIRP (0 to 31dBm)
      uint8_t OutPowerdBm  :5,
              /// Reserved
              ReservedBits :3;
#endif
      uint8_t ReservedMCO;
    } G5;
    struct PC5SHB
    {
      /// Timing Sync Info ETSI TS 102 636-4-3 V1.1.1
      /// NOTE: Used if available
#if __BYTE_ORDER == __LITTLE_ENDIAN
      /// Compact Time Confidence (CTC)
      uint8_t TimeSynEnc  :4,
              /// Version
              Version :4;
#else
      /// Version
      uint8_t Version :4,
              /// Compact Time Confidence (CTC)
              TimeSynEnc  :4;
#endif
      uint8_t Reserved1;
      uint8_t Reserved2;
      uint8_t Reserved3;
    } PC5;
    /// Reserved (used when DCC is not active)
    uint32_t Reserved;
  } MediaDep;

  /// Payload
  uint8_t Data[0];
} __attribute__ ((packed)) tETSIGeoNetSHBHdr;

/// GeoBroadcast/GeoAnycast packet header
typedef struct ETSIGeoNetMulticastHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Sequence number field
  uint16_t SN;
  /// Reserved for media-dependent functionality
  uint16_t Reserved;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  /// WGS-84 latitude for the centre position of shape [1/10 micro degree]
  int32_t GeoAreaPosLatitude;
  /// WGS-84 longitude for the centre position of shape [1/10 micro degree]
  int32_t GeoAreaPosLongitude;
  /// Distance a of the geometric shape [metres]
  uint16_t Distance_a;
  /// Distance b of the geometric shape [metres]
  uint16_t Distance_b;
  /// Angle of the geometric shape [degrees from North]
  uint16_t Angle;
  /// Unused
  uint16_t Unused;
  /// Payload
  uint8_t Data[0];
} __attribute__ ((packed)) tETSIGeoNetMulticastHdr;

/// Beacon packet header
typedef struct ETSIGeoNetBeaconHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  // No Payload
} __attribute__ ((packed)) tETSIGeoNetBeaconHdr;

/// LS Request header
typedef struct ETSIGeoNetLSReqHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Sequence number field
  uint16_t SN;
  /// Reserved for media-dependent functionality
  uint16_t Reserved;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  /// The GN_ADDR address for the GeoAdhoc
  /// router entity for which the location is being requested.
  union
  {
    struct ETSIGeoNetAddr GN_ADDR;
    uint64_t GN_ADDR_as_64;
  };
  // No payload
} __attribute__ ((packed)) tETSIGeoNetLSReqHdr;

/// LS Reply header
typedef struct ETSIGeoNetLSReplyHdr
{
  /// Common Header
  struct ETSIGeoNetCommonHdr Common;
  /// Sequence number field
  uint16_t SN;
  /// Reserved for media-dependent functionality
  uint16_t Reserved;
  /// Long position vector of the source
  struct ETSIGeoNetLPV SO_PV;
  /// Short position vector of the destination
  struct ETSIGeoNetSPV DE_PV;
  // No payload
} __attribute__ ((packed)) tETSIGeoNetLSReplyHdr;

/// On-air ETSI GN message format
typedef struct ETSIGeoNetPktHdr
{
  union
  {
    /// Common Header
    struct ETSIGeoNetCommonHdr Common;
    /// GeoUnicast packet header
    struct ETSIGeoNetUnicastHdr GeoUnicast;
    /// TSB packet
    struct ETSIGeoNetTSBHdr TSB;
    /// SHB packet
    struct ETSIGeoNetSHBHdr SHB;
    /// Beacon packet header
    struct ETSIGeoNetBeaconHdr Beacon;
    /// GeoBroadcast/GeoAnycast
    struct ETSIGeoNetMulticastHdr GeoMulticast;
    /// LS Request
    struct ETSIGeoNetLSReqHdr LocReq;
    /// LS Reply
    struct ETSIGeoNetLSReplyHdr LocReply;
    /// Just the bytes
    uint8_t Data[0];
  };
} __attribute__ ((packed)) tETSIGeoNetPktHdr;

/// ETSI GN descriptor format (GN-DATA.request & GN-DATA.indication)
typedef struct ETSIGeoNetDesc
{
  /// Upper entity @ref ETSIGeoNetNH
  uint8_t UpperEntity;

  /// Destination port information when using BTP-A & BTP-B UpperEntity
  uint16_t      DestPort;
  /// BTP-A/B
  union
  {
    /// Source port (BTP-A)
    uint16_t    SrcPort;
    /// Destination port info (BTP-B)
    uint16_t    DestInfo;
  };

  /// Packet transport type @ref ETSIGeoNetTransport
  uint8_t PktTransport;

  /// Destination @ref ETSIGeoNetDestSrc
  struct ETSIGeoNetDestSrc Dest;
  union
  {
    /// Tx specific fields
    struct
    {
      /// GN Repetition interval (unsupported)
      uint8_t RepeatInterval;
      /// Can limit Tx power (@ref ETSIGeoNetMaxTxPower)
      int8_t MaxTxPower;
      /// Security info
      tC2XSEC_SendControlData SecControl;
      /// Signed Meta
      tC2XSEC_SignedPacketMetaData SecSignedMeta;
    } Tx;
    /// Rx specific fields
    struct
    {
      /// Source position vector @ref ETSIGeoNetLPV
      struct ETSIGeoNetLPV Src; // 28 bytes
      /// Security info
      tC2XSEC_PayloadMetaData SecMeta;
    } Rx;
  };
  /// GN Communication profile (@ref ETSIGeoNetProfile)
  tETSIGeoNetProfile CommProfile;
  /// GN Traffic class (@ref ETSIGeoNetTC)
  union
  {
    uint8_t TrafficClass;
    struct ETSIGeoNetTC TCBits;
  };

  /// GN Hop Limit
  uint8_t HopLimit;

  /// GN Version
  uint8_t Version;

  /// The length in octets of the 'on-the-air' frame data
  uint16_t Length;

  /// GN Maximum packet lifetime (mSec) @ref ETSIGeoNetLifetimeVal
  uint32_t MaxPktLifetime;

} tETSIGeoNetDesc;

/// GN Timer
typedef struct ETSIGeoNetTimer
{
  /// Identifier for Timer
  timer_t Id;
  /// Timer specification
  struct itimerspec Spec;
  /// Timer signalling event
  struct sigevent Evt;
} tETSIGeoNetTimer;

/// Location service management
typedef struct ETSIGeoNetLS
{
  /// Active (single) LS GN_ADDR
  union
  {
    struct ETSIGeoNetAddr GN_ADDR;
    uint64_t GN_ADDR_as_64;
  };
  /// LS Retransmit timer (restarted on each LS Request)
  struct ETSIGeoNetTimer Timer;
  /// LS Retransmit counter
  uint8_t Counter;
  /// LS Retransmit active
  bool Active;

} tETSIGeoNetLS;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Set GN-layer country code (based on location)
 *        Ensure GN auto-country-code detection is disabled with
 *        'ItsGnRegionCode = 0' when using this API
 *        A single controller is expected to use this API (not thread safe)
 * @param CountryCode ISO3166 numeric code
 */
void ETSIGN_SetCountryCode (uint16_t CountryCode);

/**
 * @brief Dynamically set GN Tx/Rx controls after initialisation
 *        GN Tx/Rx initially set based on configuration (via EnableTxRx)
 *        A single controller is expected to use this API (not thread safe)
 * @param TxDisable true indicates GN Transmit is to be disabled
 * @param RxDisable true indicates GN Receive is to be disabled
 */
void ETSIGN_SetTxRxDisable (bool TxDisable, bool RxDisable);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_GN_H_

/**
 * @}
 */
