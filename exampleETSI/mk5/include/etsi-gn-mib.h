/**
 * @addtogroup v2x_etsi_gn ETSI ITS Network elements
 * @{
 *
 * @section v2x_etsi_gn_mib ETSI GN MIB

 * @file
 *
 * ETSI GN library functionality
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_GN_MIB_H_
#define __ETSI_GN_MIB_H_

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

/// Geonetworking address length in uint8_t
#define ETSI_GN_ADDR_LEN       8

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// GN Addr configuration method
typedef enum ETSIGeoNetLocalAddrConfMethod
{
  ETSIGeoNetLocalAddrConfMethod_auto = 0,
  ETSIGeoNetLocalAddrConfMethod_managed = 1,
  ETSIGeoNetLocalAddrConfMethod_anonymous = 2
} eETSIGeoNetLocalAddrConfMethod;

/// StationType
typedef enum ETSIGeoNetStationType
{
  ETSIGeoNetStationType_unknown = 0,
  ETSIGeoNetStationType_pedestrian = 1,
  ETSIGeoNetStationType_cyclist = 2,
  ETSIGeoNetStationType_moped = 3,
  ETSIGeoNetStationType_motorcycle = 4,
  ETSIGeoNetStationType_passengerCar = 5,
  ETSIGeoNetStationType_bus = 6,
  ETSIGeoNetStationType_lightTruck = 7,
  ETSIGeoNetStationType_heavyTruck = 8,
  ETSIGeoNetStationType_trailer = 9,
  ETSIGeoNetStationType_specialVehicles = 10,
  ETSIGeoNetStationType_tram = 11,
  ETSIGeoNetStationType_roadSideUnit = 15
} eETSIGeoNetStationType;

/// IfType
typedef enum ETSIGeoNetIfType
{
  ETSIGeoNetIfType_unspecified = 0,
  ETSIGeoNetIfType_itsg5 = 1,
  ETSIGeoNetIfType_ltev2x = 2
} eETSIGeoNetIfType;

/// SnDecapResultHandling
typedef enum ETSIGeoNetSnDecapResultHandling
{
  ETSIGeoNetSnDecapResultHandling_strict = 0,
  ETSIGeoNetSnDecapResultHandling_nonStrict = 1
} eETSIGeoNetSnDecapResultHandling;

/// Geo NonArea forwarding algorithm types
typedef enum ETSIGeoNetGeoNonAreaForwardingAlgorithm
{
  ETSIGeoNetGeoNonAreaForwardingAlgorithm_unspecified = 0,
  ETSIGeoNetGeoNonAreaForwardingAlgorithm_greedy = 1,
  ETSIGeoNetGeoNonAreaForwardingAlgorithm_cbf = 2
} eETSIGeoNetGeoNonAreaForwardingAlgorithm;

/// Geo Area forwarding algorithm types
typedef enum ETSIGeoNetGeoAreaForwardingAlgorithm
{
  ETSIGeoNetGeoAreaForwardingAlgorithm_unspecified = 0,
  ETSIGeoNetGeoAreaForwardingAlgorithm_simple = 1,
  ETSIGeoNetGeoAreaForwardingAlgorithm_cbf = 2,
  ETSIGeoNetGeoAreaForwardingAlgorithm_advanced = 3
} eETSIGeoNetGeoAreaForwardingAlgorithm;

/// Struct for GN MIB parameters
typedef struct libITS_GNMIBParams_tag
{
  /// GN_ADDR value
  uint8_t LocalGnAddr[ETSI_GN_ADDR_LEN];
  /// Addr method
  eETSIGeoNetLocalAddrConfMethod LocalAddrConfMethod;
  /// Protocol version
  uint8_t ProtocolVersion;
  /// Station type
  eETSIGeoNetStationType StationType;
  /// Reserved, formerly CountryCode
  uint16_t Reserved;
  /// LTE-V2X Timing Confidence
  uint8_t CompactTimeConfidence;
  /// IsMobile
  bool IsMobile;
  /// Interface Type
  eETSIGeoNetIfType IfType;
  /// MinimumUpdateFrequencyEPV
  uint16_t MinimumUpdateFrequencyEPV;
  /// PaiInterval
  uint16_t PaiInterval;
  /// MaxSduSize
  uint16_t MaxSduSize;
  /// MaxGeoNetworkingHeaderSize
  uint16_t MaxGeoNetworkingHeaderSize;
  /// LifetimeLocTE
  uint16_t LifetimeLocTE;
  /// Security
  bool Security;
  /// SnDecapResultHandling
  eETSIGeoNetSnDecapResultHandling SnDecapResultHandling;
  /// LocationServiceMaxRetrans
  uint8_t LocationServiceMaxRetrans;
  /// LocationServiceRetransmitTimer
  uint16_t LocationServiceRetransmitTimer;
  /// LocationServicePacketBufferSize
  uint16_t LocationServicePacketBufferSize;
  /// BeaconServiceRetransmitTimer
  uint16_t BeaconServiceRetransmitTimer;
  /// BeaconServiceMaxJitter
  uint16_t BeaconServiceMaxJitter;
  /// DefaultHopLimit
  uint8_t DefaultHopLimit;
  /// DefaultHopLimit
  uint8_t DPLLength;
  /// MaxPacketLifetime
  uint16_t MaxPacketLifetime;
  /// DefaultPacketLifetime
  uint16_t DefaultPacketLifetime;
  /// MaxPacketDataRate
  uint16_t MaxPacketDataRate;
  /// MaxPacketDataRateEmaBeta
  uint8_t MaxPacketDataRateEmaBeta;
  /// MaxGeoAreaSize
  uint16_t MaxGeoAreaSize;
  /// MinPacketRepetitionInterval
  uint16_t MinPacketRepetitionInterval;
  /// GeoNonAreaForwardingAlgorithm
  eETSIGeoNetGeoNonAreaForwardingAlgorithm GeoNonAreaForwardingAlgorithm;
  /// GeoAreaForwardingAlgorithm
  eETSIGeoNetGeoAreaForwardingAlgorithm GeoAreaForwardingAlgorithm;
  /// CbfMinTime
  uint16_t CbfMinTime;
  /// CbfMaxTime
  uint16_t CbfMaxTime;
  /// DefaultMaxCommunicationRange
  uint16_t DefaultMaxCommunicationRange;
  /// BroadcastCBFDefSectorAngle
  uint8_t BroadcastCBFDefSectorAngle;
  /// UcForwardingPacketBufferSize
  uint16_t UcForwardingPacketBufferSize;
  /// BcForwardingPacketBufferSize
  uint16_t BcForwardingPacketBufferSize;
  /// CbfPacketBufferSize
  uint16_t CbfPacketBufferSize;
  /// DefaultTrafficClass
  uint8_t DefaultTrafficClass;
  /// NeighbourFlagExpiry (time in milliseconds)
  uint16_t NeighbourFlagExpiry;
} tETSIGeoNetMIBParams;

#ifdef __cplusplus
}
#endif

#endif // __ETSI_GN_MIB_H_

// Close the Doxygen group
/**
 * @}
 */
