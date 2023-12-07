/**
 * @addtogroup ets_app_facilities_common_api ETSI ITS Facilities Common data
 * @{
 *
 * Common ETSI Facilities Layer definitions
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_MSG_ETS_FAC_COMMON_H_
#define __ETS_MSG_ETS_FAC_COMMON_H_

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

/// No repetition duration
#define ETSIFAC_REPETITIONDURATIONNONE 0 // seconds

/// Forever repetition duration
#define ETSIFAC_REPETITIONDURATIONFOREVER 0xFFFFFFFF

/// No repetition interval (i.e. single shot message)
#define ETSIFAC_REPETITIONINTERVALNONE 0 // milli-seconds

/// Shortest supported repetition interval (non-DENMs)
#define ETSIFAC_REPETITIONINTERVALMINMS 100 // milli-seconds

/// Longest supported repetition interval
#define ETSIFAC_REPETITIONINTERVALMAXMS 60000 // milli-seconds

/// Terminate repetition interval (i.e. immediate termination of previously repeating message)
#define ETSIFAC_REPETITIONINTERVALTERMINATE 0xFFFF

/// Protocol version 1
#define ETSIFAC_PROTOCOLVERSION1 1
/// Protocol version 2
#define ETSIFAC_PROTOCOLVERSION2 2

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// ETSIFAC detection time - special values
typedef enum ETSIFACTimestampTai
{
  /// timestamp = 'use current time'
  ETSIFAC_TIMESTAMP_TAI_NOW = 0x00
} eETSIFACTimestampTai;

/// ETSIFAC timestamp, mSec in TAI time @ref ETSIFACTimestampTai
typedef uint64_t tTimestampTai;

/// BTP type
typedef enum ETSIFACBTPType
{
  /// BTP-B
  ETSIFAC_BTP_TYPE_B = 0x0,
  /// BTP-A
  ETSIFAC_BTP_TYPE_A = 0x1,

} eETSIFACBTPType;

/// BTP type element @ref ETSIFACBTPType
typedef uint8_t tETSIFACBTPType;

/// Packet transport type
typedef enum ETSIFACGeoNetTransport
{
  /// ETSIFAC will select default GN transport
  ETSIFAC_GN_TRANSPORT_DEFAULT = 0x0,

  /// GeoUnicast (GUC)
  ETSIFAC_GN_TRANSPORT_GEOUNICAST = 0x2,
  /// Geographically-Scoped Anycast (GAC)
  ETSIFAC_GN_TRANSPORT_GEOANYCAST = 0x3,
  /// Geographically-Scoped broadcast (GBC)
  ETSIFAC_GN_TRANSPORT_GEOBROADCAST = 0x4,
  /// Topologically-scoped broadcast (TSB)
  ETSIFAC_GN_TRANSPORT_TSB = 0x5,
  /// Single hop broadcast (SHB)
  ETSIFAC_GN_TRANSPORT_SHB = 0x7,

} eETSIFACGeoNetTransport;

/// Packet transport type element @ref ETSIFACGeoNetTransport
typedef uint8_t tETSIFACGeoNetTransport;

/// Address for GeoUnicast
typedef struct ETSIFACGeoNetAddr
{
  /// Address of destination station
  uint64_t GN_ADDR_as_64;
} tETSIFACGeoNetAddr;

/// ETSIFAC Destination area shape type
typedef enum ETSIFACDestShapeType
{
  /// Circular area
  ETSIFAC_DEST_TYPE_CIRCLE = 0x0,
  /// Rectangular area
  ETSIFAC_DEST_TYPE_RECT = 0x1,
  /// Ellipsoidal area
  ETSIFAC_DEST_TYPE_ELIP = 0x2,

} eETSIFACDestShapeType;

/// ETSIFAC Destination area shape type @ref ETSIFACDestShapeType
typedef uint8_t tETSIFACDestShapeType;

/// Destination Area information for GeoBroadcast or GeoAnycast
typedef struct ETSIFACGeoNetArea
{
  /// WGS-84 latitude for the center position of shape [1/10 micro degrees]
  int32_t Latitude;
  /// WGS-84 longitude for the center position of shape [1/10 micro degrees]
  int32_t Longitude;
  /// Distance a of the geometric shape [metres] (must be non-zero, as always required)
  uint16_t Distance_a;
  /// Distance b of the geometric shape [metres] (required for RECT and ELIP shapes)
  uint16_t Distance_b;
  /// Angle of the geometric shape [degrees] (0 to 359 degrees from North)
  uint16_t Angle;
  /// Shape of Area @ref ETSIFACDestShapeType
  tETSIFACDestShapeType Shape;
} tETSIFACGeoNetArea;

/// Source position vector
typedef struct ETSIFACGeoNetPos
{
  /// The network address for the GeoAdhoc router entity
  uint64_t GN_ADDR_as_64;
  /// Expresses the time in milliseconds at which the latitude and longitude of
  /// the ITS-S were acquired by the GeoAdhoc router. The time is encoded as:
  uint32_t TST;
  /// WGS-84 latitude for the center position of shape [1/10 micro degree]
  int32_t Latitude;
  /// WGS-84 longitude for the center position of shape [1/10 micro degree]
  int32_t Longitude;
} tETSIFACGeoNetPos;

/// MSG Communications Profile Identifier
typedef enum ETSIFACGNProfile
{
  /// communication profile: Default
  ETSIFAC_GN_PROFILE_DEFAULT = 0x00,

  /// communication profile: short-range (ITS-G5/PC5 LTE-V2X)
  ETSIFAC_GN_PROFILE_SHORT_RANGE = 0xC0,
  /// communication profile: long range (C-V2X)
  ETSIFAC_GN_PROFILE_LONG_RANGE  = 0x20,
} eETSIFACGNProfile;

/// MSG Communications Profile @ref ETSIFACGNProfile
typedef uint8_t tETSIFACGNProfile;

/// MSG Channel type identifiers
typedef enum ETSIFACGNChanType
{
  /// Channel type: CCH
  ETSIFAC_GN_CHAN_TYPE_CCH = 0x00,
  /// Channel type: SCH1
  ETSIFAC_GN_CHAN_TYPE_SCH1 = 0x01,
  /// Channel type: SCH2
  ETSIFAC_GN_CHAN_TYPE_SCH2 = 0x02,
  /// Channel type: SCH3
  ETSIFAC_GN_CHAN_TYPE_SCH3 = 0x03,
  /// Channel type: SCH4
  ETSIFAC_GN_CHAN_TYPE_SCH4 = 0x04,
} eETSIFACGNChanType;

/// MSG Channel type @ref ETSIFACGNChanType
typedef uint8_t tETSIFACGNChanType;

/// MSG Security profile
typedef enum ETSIFACGNSecProf
{
  /// Security profile: NONE
  ETSIFAC_GN_SEC_PROF_NONE = 0,
  /// Security profile: GENERAL
  ETSIFAC_GN_SEC_PROF_GENERAL = 1,

  /// Security profile: Custom AID & SSP
  ETSIFAC_GN_SEC_PROF_AID_SSP = 2,

  /// Security profile: CAM
  ETSIFAC_GN_SEC_PROF_CAM = 3,
  /// Security profile: DENM
  ETSIFAC_GN_SEC_PROF_DENM = 4,
  /// Security profile: SPAT
  ETSIFAC_GN_SEC_PROF_SPAT = 5,
  /// Security profile: MAP
  ETSIFAC_GN_SEC_PROF_MAP = 6,
  /// Security profile: IVI
  ETSIFAC_GN_SEC_PROF_IVI = 7,
  /// Security profile: SRM
  ETSIFAC_GN_SEC_PROF_SRM = 8,
  /// Security profile: SSM
  ETSIFAC_GN_SEC_PROF_SSM = 9,
  /// Security profile: CPM
  ETSIFAC_GN_SEC_PROF_CPM = 10,
  /// Security profile: GPC (RTCM)
  ETSIFAC_GN_SEC_PROF_GPC = 11,
  /// Security profile: VAM (VRU)
  ETSIFAC_GN_SEC_PROF_VAM = 12,

} eETSIFACGNSecProf;

/// MSG Channel type @ref ETSIFACGNSecProf
typedef uint8_t tETSIFACGNSecProf;

/// MSG Traffic Class Identifier
typedef enum ETSIFACGNTC
{
  /// Store-Carry-Forward setting, set or not set
  ETSIFAC_GN_TC_SCF      = 0x80,

  /// Channel offload setting, set or not set
  ETSIFAC_GN_TC_OFFLOAD  = 0x40,

  /// Traffic class DP0 to DP32, select one
  ETSIFAC_GN_TC_ITS_DP0  = 0x00,
  ETSIFAC_GN_TC_ITS_DP1  = 0x01,
  ETSIFAC_GN_TC_ITS_DP2  = 0x02,
  ETSIFAC_GN_TC_ITS_DP3  = 0x03,
  ETSIFAC_GN_TC_ITS_DP4  = 0x04,
  ETSIFAC_GN_TC_ITS_DP5  = 0x05,
  ETSIFAC_GN_TC_ITS_DP6  = 0x06,
  ETSIFAC_GN_TC_ITS_DP7  = 0x07,
  ETSIFAC_GN_TC_ITS_DP8  = 0x08,
  /// Traffic classes DP9 to DP32 not used on CCH, will be sent on SCH
  ETSIFAC_GN_TC_ITS_DP9  = 0x09,
  ETSIFAC_GN_TC_ITS_DP10 = 0x0A,
  ETSIFAC_GN_TC_ITS_DP11 = 0x0B,
  ETSIFAC_GN_TC_ITS_DP12 = 0x0C,
  ETSIFAC_GN_TC_ITS_DP13 = 0x0D,
  ETSIFAC_GN_TC_ITS_DP14 = 0x0E,
  ETSIFAC_GN_TC_ITS_DP15 = 0x0F,
  ETSIFAC_GN_TC_ITS_DP16 = 0x10,
  ETSIFAC_GN_TC_ITS_DP17 = 0x11,
  ETSIFAC_GN_TC_ITS_DP18 = 0x12,
  ETSIFAC_GN_TC_ITS_DP19 = 0x13,
  ETSIFAC_GN_TC_ITS_DP20 = 0x14,
  ETSIFAC_GN_TC_ITS_DP21 = 0x15,
  ETSIFAC_GN_TC_ITS_DP22 = 0x16,
  ETSIFAC_GN_TC_ITS_DP23 = 0x17,
  ETSIFAC_GN_TC_ITS_DP24 = 0x18,
  ETSIFAC_GN_TC_ITS_DP25 = 0x19,
  ETSIFAC_GN_TC_ITS_DP26 = 0x1A,
  ETSIFAC_GN_TC_ITS_DP27 = 0x1B,
  ETSIFAC_GN_TC_ITS_DP28 = 0x1C,
  ETSIFAC_GN_TC_ITS_DP29 = 0x1D,
  ETSIFAC_GN_TC_ITS_DP30 = 0x1E,
  ETSIFAC_GN_TC_ITS_DP31 = 0x1F,
  ETSIFAC_GN_TC_ITS_DP32 = 0x20

} eETSIFACGNTC;

/// MSG Traffic Class Profile @ref ETSIFACGNTC
typedef uint8_t tETSIFACGNTC;

/// MSG Hop Limit
typedef enum ETSIFACGNHopLimit
{
  /// Use GN default Hop Limit value
  ETSIFAC_GN_HOP_LIMIT_DEFAULT = 0

} eETSIFACGNHopLimit;

/// MSG Hop Limit @ref ETSIFACGNHopLimit
typedef uint8_t tETSIFACGNHopLimit;

/// FAC PDU header
typedef struct ETSIFACPduHeader {
  /// Version
  uint8_t protocolVersion;
  /// Message ID
  uint8_t messageID;
  /// Station ID
  uint8_t stationID[4];
} __attribute__ ((packed)) tETSIFACPduHeader;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // __ETS_MSG_ETS_FAC_COMMON_H_

// Close the Doxygen group
/**
 * @}
 */
