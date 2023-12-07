#pragma once
/**
 * @addtogroup ubx uBlox GPS parsing library
 * @{
 *
 * Parses the binary uBlox packets and injects them into libpos
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __INCLUDE_UBX8_H_
#define __INCLUDE_UBX8_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------


/// M8N standard GPS
#define UBX_DEVICE_TYPE_M8N (0)
/// M8U UDR GPS module with 6-axis IMU
#define UBX_DEVICE_TYPE_M8U_UDR (1)
/// M8N ADR GPS module with 6-axis IMU and speed/wheel-tick support
#define UBX_DEVICE_TYPE_M8L_ADR (2)
/// M8N ADR GPS module in basic NAV_PVT + ESF_RAW only mode - dead-reckoning disabled.
#define UBX_DEVICE_TYPE_M8L_ADR_BASIC (3)

#define UBX_MAX_NUM_CALLBACKS 64

// these constants were obtained from:
// u-bloxM8-V15_ReceiverDescriptionProtocolSpec_Confidential_(UBX-13002887).pdf
#define UBX_NAV_DOP_ID      0x04
#define UBX_NAV_COV_ID      0x36
#define UBX_NAV_PVT_ID      0x07
#define UBX_NAV_TIMEGPS_ID  0x20
#define UBX_NAV_SAT_ID      0x35
#define UBX_NAV_HNR_ID      0x37
#define UBX_ACK_ACK_ID      0x01
#define UBX_ACK_NAK_ID      0x00
#define UBX_AID_HUI_ID      0x02
#define UBX_UPD_SOS_ID      0x14
#define UBX_HNR_PVT_ID      0x00
#define UBX_HNR_INS_ID      0x02
#define UBX_ESF_STATUS_ID   0x10
#define UBX_ESF_RAW_ID      0x03
#define UBX_ESF_INS_ID      0x15
#define UBX_ESF_MEAS_ID     0x02
#define UBX_ESF_ALG_ID      0x14

#define UBX_CFG_TTAG_ID     0x4B

#define UBX_MON_VER_ID      0x04

#define UBX_CLASS_NAV       0x01
#define UBX_CLASS_ACK       0x05
#define UBX_CLASS_CFG       0x06
#define UBX_CLASS_AID       0x0B
#define UBX_CLASS_UPD       0x09
#define UBX_CLASS_ESF       0x10
#define UBX_CLASS_HNR       0x28
#define UBX_CLASS_RES       0x03   /* Reserved for ublox logging support only */
#define UBX_CLASS_MON       0x0A

// ASCII sata dumps contain length in hex
#define UBX_CFG_PRT_PAYLOAD 0x14
#define UBX_CFG_MSG_PAYLOAD 0x08
#define UBX_CFG_RST_PAYLOAD 0x04
#define UBX_CFG_CFG_PAYLOAD 0x0D
#define UBX_CFG_HNR_PAYLOAD 0x04
#define UBX_CFG_RTE_PAYLOAD 0x06
#define UBX_CFG_TP5_PAYLOAD 0x20
#define UBX_NAV_PVT_PAYLOAD 0x5C
#define UBX_NAV_HNR_PAYLOAD 0x34
#define UBX_NAV_DOP_PAYLOAD  0x12
#define UBX_NAV_COV_PAYLOAD  0x40
#define UBX_NAV_TIMEGPS_PAYLOAD 0x10
#define UBX_NAV_SAT_PAYLOAD_MIN 0x08
#define UBX_AID_HUI_PAYLOAD 0x48
#define UBX_HNR_PVT_PAYLOAD 0x48
#define UBX_HNR_INS_PAYLOAD 0x24
#define UBX_ESF_STATUS_PAYLOAD_MIN 0x16
#define UBX_ESF_RAW_PAYLOAD_MIN 0x04
#define UBX_ESF_MEAS_PAYLOAD_MIN 0x08
#define UBX_ESF_INS_PAYLOAD 0x24
#define UBX_ACK_ACK_PAYLOAD 0x02
#define UBX_ACK_NAK_PAYLOAD 0x02
#define UBX_MON_VER_PAYLOAD_MIN 0x28
//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
enum {
  /// Valid UTC Date
  UBX_BF_VALID_DATE = 0x1,
  /// Valid UTC Time of Day
  UBX_BF_VALID_TIME = 0x2,
  /// UTC Time of Day fully reolved (no second uncertainty)
  UBX_BF_VALID_FULLY_RESOLVED = 0x4,
};

enum
{
  /// no fix
  UBX_FIX_NO_FIX      = 0,
  /// Dear Reckoning only
  UBX_FIX_DR          = 1,
  /// 2D fix
  UBX_FIX_2D          = 2,
  /// 3D fixu
  UBX_FIX_3D          = 3,
  /// GNSS + dead reckoning combined
  UBX_FIX_GNSS_DR     = 4,
  /// Time only fix
  UBX_FIX_TIME_ONLY   = 5,
};
enum
{
  /// A valid fix (i.e. within DOP & accuracy masks)
  UBX_BF_FLAGS_GNSS_FIX_OK           = 0x01,
  /// 1 if differential corrections were applied
  UBX_BF_FLAGS_DIFF_SOLN             = 0x02,
  /// Power Save Mode - no PSM is active
  UBX_BF_FLAGS_PSM_STATE_NA          = 0x00,
  /// Power Save Mode -  ENABLED (intermediate state before ACQUISITION)
  UBX_BF_FLAGS_PSM_STATE_ENABLED     = 0x04,
  /// Power Save Mode - ACQUISITION
  UBX_BF_FLAGS_PSM_STATE_ACQUISITION = 0x08,
  /// Power Save Mode - TRACKING
  UBX_BF_FLAGS_PSM_STATE_TRACKING    = 0x0C,
  /// Power Save Mode - POWER OPTIMISED TRACKING
  UBX_BF_FLAGS_PSM_STATE_PO_TRACKING = 0x10,
  /// Power Save Mode - INACTIVE
  UBX_BF_FLAGS_PSM_STATE_INACTIVE    = 0x14,
  /// Heading of vehicle is valid
  UBX_BF_FLAGS_HEADING_VALID         = 0x20,
};


enum
{
  /// Valid GPS time of week (iTOW and fTOW)
  UBX_BF_FLAGS_TOW_VALID   = 0x01,
  /// Valid GPS week number
  UBX_BF_FLAGS_WEEK_VALID  = 0x02,
  /// Valid GPS leap seconds
  UBX_BF_FLAGS_LEAPS_VALID = 0x04,
};

enum
{
  /// Healthmask field in this message is valid
  UBX_BF_FLAG_HEALTH_VALID = 0x1,
  /// UTC parameter fields in this message are valid
  UBX_BF_FLAG_UTC_VALID = 0x2,
  /// Klobuchar parameter fields in this message are valid
  UBX_BF_FLAG_KLOB_VALID = 0x4,
};

typedef enum Ubx_ErrCode
{
  /// OK
  UBX_ERR_NONE = 0,
  /// Callback application disabled
  UBX_ERR_APP_DISABLED = -1,
  /// Unable to register additional callback
  UBX_ERR_TOO_MANY_CALLBACKS = -2,
  /// Message invalid
  UBX_MESSAGE_INVALID = -3,
  /// Failed to send a message (either failed on open
  UBX_FAILED_SEND = -4,
  /// Failed to allocate memory for a serialised message.
  UBX_FAILED_ALLOC = -5,
  /// Failed to generate a message
  UBX_FAILED_GEN = -6,
  /// Failed to initialise the Ubx
  UBX_FAILED_INIT = -7,
  /// Failed to enable extra messages such as DOP, COV for Ubx
  UBX_FAILED_INIT_EXTRA_MSGS = -8,
  /// Failed to enable ubox proprietry V2XLocate merge messages
  UBX_FAILED_UBLOX_MSGS = -9,
} tUbx_ErrCode;

/// u-bloxM8-V15_ReceiverDescriptionProtocolSpec_Confidential_(UBX-13002887).pdf
/// Page 99 of 293
/// 24 UBX Packet Structure
typedef struct UBX_Header
{
  /// magic numbers, 0xb5 0x62 (ISO 8859.1 for micro, "b"
  uint8_t  Magic[2];
  uint8_t  Class;
  uint8_t  Id;
  uint16_t Length;
  uint8_t  Payload[0];
} tUBX_Header;

/// u-bloxM8-V15_ReceiverDescriptionProtocolSpec_Confidential_(UBX-13002887).pdf
/// Section 38.13.2 REciever/Software Version
/// MOV-VER 0x0A 0x04 Packet Structure
typedef struct UBX_MON_VER
{
  /// Zero terminated software version string.
  uint8_t  swVersion[30];
  /// Zero terminated Hardware version string.
  uint8_t  hwVersion[10];
  /// Contains 40 +30*N extension text data which the decoder of the packet needs to handle.
  /// tUBX_MON_VER_EXT extension[N];
} __attribute__ ((packed)) tUBX_MON_VER;

// Repeated data for UBX_MON_VER extension field
typedef struct UBX_MON_VER_EXT {
  /// Extension receiver/software information, any product capabilities etc.
  uint8_t  extension[30];
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_MON_VER_EXT;


/// UBX-CFG-RATE (0x06 0x08) Navigation/measurement rate settings
typedef struct UBX_CFG_RATE
{
  /// GPS measurment rate (in milliseconds)
  uint16_t measRate;
  /// Navigation calculation rate (in cycles)
  uint16_t navRate;
  /// Time reference, 1 == GPS, 0 == UTC
  uint16_t timeRef;
}  __attribute__ ((packed)) tUBX_CFG_RATE;

/// UBX-CFG-RATE constants
typedef enum {
  UBX_CFG_RATE_CLASS_ID  = 0x06,
  UBX_CFG_RATE_MESSAGE_ID = 0x08,
  UBX_CFG_RATE_LENGTH = 6,
} eUBX_CFG_RATE;

/// UBX-CFG-HNR (0x06 0x5C) High navigation rate settings
typedef struct UBX_CFG_HNR
{
  /// Rate of navigation solution output [Hz]
  uint8_t highNavRate;
  /// Reserved
  uint8_t reserved1[3];
}  __attribute__ ((packed)) tUBX_CFG_HNR;

/// UBX-CFG-HNR constants
typedef enum {
  UBX_CFG_HNR_CLASS_ID  = 0x06,
  UBX_CFG_HNR_MESSAGE_ID = 0x5C,
  UBX_CFG_HNR_LENGTH = 4,
} eUBX_CFG_HNR;

/// common timestamp into at the startof PVT and HNR
typedef struct UBX_UTC_Timestamp
{
  /// U4 iTOW GPS time of week [ms]
  uint32_t iTOW;
  /// U2 year (UTC)
  uint16_t year;
  /// U1 month (UTC)
  uint8_t month;
  /// U1 day (UTC)
  uint8_t day;
  /// U1 hour (UTC)
  uint8_t hour;
  /// U1 min (UTC)
  uint8_t min;
  /// U1 sec (UTC)
  uint8_t sec;
  /// X1 valid : Validity flags for time (UBX_BF_VALID_*)
  uint8_t valid;

}  __attribute__ ((packed)) tUBX_UTC_Timestamp;

typedef struct UBX_NAV_PVT
{
  /// timestamp info
  tUBX_UTC_Timestamp timestamp;
  /// U4 tAcc: Time Accuracy estimate (UTC) [ns]
  uint32_t tAcc;
  /// I4 nano: Fraction of second, range -1e9 .. 1e9 (UTC) [ns]
  int32_t nano;
  /// U1 fixType: GNSSfix type (UBX_FIX_TYPE_*)
  uint8_t fixType;
  /// X1 flags: Fix Status Flags (UBX_BF_FLAGS_*)
  uint8_t flags;
  /// U1 reserved
  uint8_t reserved1;
  /// U1 numSV
  uint8_t numSv;
  /// I4 lon: longitude [1e-7 deg]
  int32_t lon;
  /// I4 lat: latitude  [1e-7 deg]
  int32_t lat;
  /// I4 height: Height above ellipsoid [mm]
  int32_t height;
  /// I4 hMSL: Height above mean sea level [mm]
  int32_t hMSL;
  /// U4 hAcc: horizontal accuracy estimate [mm]
  uint32_t hAcc;
  /// U4 vAcc: vertical accuracy estimate [mm]
  uint32_t vAcc;
  /// I4 velN: NED north velocity [mm/s]
  int32_t velN;
  /// I4 velE: NED east velocity [mm/s]
  int32_t velE;
  /// I4 velD: NED down velocity [mm/s]
  int32_t velD;
  /// I4 gSpeed: Ground Speed (2D) [mm/s]
  int32_t gSpeed;
  /// I4 headMot: heading of motion (2D) [1e-5 deg]
  int32_t headMot;
  /// U4 sAcc: Speed accuracy estimate [mm/s]
  uint32_t sAcc;
  /// U4 headAcc: heading (Mot and Veh) accuracy estimage [1e-5 deg]
  uint32_t headAcc;
  /// U2 pDop: Position DOP [0.01]
  int16_t pDop;
  /// X2 reserved2
  uint16_t reserved2;
  /// X4 reserved3
  uint32_t reserved3;
  /// I4 headingVeh: heading of vehicle (2D) [1e-5 deg]
  int32_t headingVeh;
  /// X4 reserved4;
  uint32_t reserved4;
} __attribute__ ((packed)) tUBX_NAV_PVT;

typedef struct UBX_NAV_HNR
{
  /// timestamp info
  tUBX_UTC_Timestamp timestamp;
  /// I4 nano: Fraction of second, range -1e9 .. 1e9 (UTC) [ns]
  int32_t nano;
  /// U1 gpsFix: GNSSfix type (UBX_FIX_TYPE_*)
  uint8_t gpsFix;
  /// X1 flags: Fix Status Flags (UBX_BF_FLAGS_*)
  uint8_t flags;
  /// X2 reserved
  uint16_t reserved1;
  /// I4 lon: longitude [1e-7 deg]
  int32_t lon;
  /// I4 lat: latitude  [1e-7 deg]
  int32_t lat;
  /// I4 height: Height above ellipsoid [mm]
  int32_t height;
  /// I4 hMSL: Height above mean sea level [mm]
  int32_t hMSL;
  /// I4 gSpeed: Ground Speed (2D) [mm/s]
  int32_t gSpeed;
  /// I4 speed: Speed (3D) [mm/s]
  int32_t speed;
  /// I4 headMot: heading of motion (2D) [1e-5 deg]
  int32_t headMot;
  /// I4 headVeh: heading of vehicle (2D) [1e-5 deg]
  int32_t headVeh;
} __attribute__ ((packed)) tUBX_NAV_HNR;


typedef struct UBX_HNR_PVT
{
  /// timestamp info
  tUBX_UTC_Timestamp timestamp;
  /// I4 nano: Fraction of second, range -1e9 .. 1e9 (UTC) [ns]
  int32_t nano;
  /// U1 gpsFix: GNSSfix type (UBX_FIX_TYPE_*)
  uint8_t gpsFix;
  /// X1 flags: Fix Status Flags (UBX_BF_FLAGS_*)
  uint8_t flags;
  /// X2 reserved
  uint16_t reserved1;
  /// I4 lon: longitude [1e-7 deg]
  int32_t lon;
  /// I4 lat: latitude  [1e-7 deg]
  int32_t lat;
  /// I4 height: Height above ellipsoid [mm]
  int32_t height;
  /// I4 hMSL: Height above mean sea level [mm]
  int32_t hMSL;
  /// I4 gSpeed: Ground Speed (2D) [mm/s]
  int32_t gSpeed;
  /// I4 speed: Speed (3D) [mm/s]
  int32_t speed;
  /// I4 headMot: heading of motion (2D) [1e-5 deg]
  int32_t headMot;
  /// I4 headVeh: heading of vehicle (2D) [1e-5 deg]
  int32_t headVeh;
  /// U4 hAcc: horizontal accuracy estimate [mm]
  uint32_t hAcc;
  /// U4 vAcc: vertical accuracy estimate [mm]
  uint32_t vAcc;
  /// U4 sAcc: Speed accuracy estimate [mm/s]
  uint32_t sAcc;
  /// U4 headAcc: heading (Mot and Veh) accuracy estimage [1e-5 deg]
  uint32_t headAcc;
  /// X2 reserved2
  uint32_t reserved2;
//}  tUBX_HNR_PVT;
} __attribute__ ((packed)) tUBX_HNR_PVT;


typedef struct UBX_NAV_DOP
{
  /// U4   iTOW GPS time of week [ms]
  uint32_t iTOW;
  /// U2   gDOP Geometric  (0.01) [%]
  uint16_t gDOP;
  /// U2   pDOP Position   (0.01) [%]
  uint16_t pDOP;
  /// U2   tDOP Time       (0.01) [%]
  uint16_t tDOP;
  /// U2   vDOP Vertical   (0.01) [%]
  uint16_t vDOP;
  /// U2   hDOP Horizontal (0.01) [%]
  uint16_t hDOP;
  /// U2   nDOP Northing   (0.01) [%]
  uint16_t nDOP;
  /// U2   eDOP Easting    (0.01) [%]
  uint16_t eDOP;
  // packed to avoid padding at the end
}  __attribute__ ((packed)) tUBX_NAV_DOP;

typedef struct UBX_NAV_COV
{
  /// U4   iTOW GPS time of week [ms]
  uint32_t iTOW;
  /// U1 - version - Message version (0 for this version)
  uint8_t  version;
  /// U1 - posCovValid - Position covariance matrix validity flag
  uint8_t  posCovValid;
  /// U1 - velCovValid - Velocity covariance matrix validity flag
  uint8_t  velCovValid;
  /// U1 - reserved1 - Reserved
  uint8_t  reserved1;
  /// U4 - reserved2 - Reserved
  uint32_t reserved2;
  /// U4 - reserved3 - Reserved
  uint32_t reserved3;
  /// R4 - posCov11 m^2 Position covariance matrix value p11
  float    posCov11;
  /// R4 - posCov12 m^2 Position covariance matrix value p12
  float    posCov12;
  /// R4 - posCov13 m^2 Position covariance matrix value p13
  float    posCov13;
  /// R4 - posCov22 m^2 Position covariance matrix value p22
  float    posCov22;
  /// R4 - posCov23 m^2 Position covariance matrix value p23
  float    posCov23;
  /// R4 - posCov33 m^2 Position covariance matrix value p33
  float    posCov33;
  /// R4 - velCov11 m^2/s^2 Velocity covariance matrix value v11
  float    velCov11;
  /// R4 - velCov12 m^2/s^2 Velocity covariance matrix value v12
  float    velCov12;
  /// R4 - velCov13 m^2/s^2 Velocity covariance matrix value v13
  float    velCov13;
  /// R4 - velCov22 m^2/s^2 Velocity covariance matrix value v22
  float    velCov22;
  /// R4 - velCov23 m^2/s^2 Velocity covariance matrix value v23
  float    velCov23;
  /// R4 - velCov33 m^2/s^2 Velocity covariance matrix value v33
  float    velCov33;
}  __attribute__ ((packed)) tUBX_NAV_COV;

typedef struct UBX_NAV_TIMEGPS
{
  /// GPS time of week of the navigation epoch [ms]
  /// TOW = (iTOW / 1e3) + (fTOW / 1e9)
  uint32_t iTOW;
  /// Fractional part of iTOW (eange +/- 500000) [ns]
  /// TOW = (iTOW / 1e3) + (fTOW / 1e9)
  int32_t fTOW;
  /// GPS week number of the navigation epoch
  int16_t week;
  /// GPS leap seconds (GPS - UTC)
  int8_t leapS;
  /// Validity flag
  /// @ref UBX_BF_FLAGS_TOW_VALID, @ref UBX_BF_FLAGS_WEEK_VALID, @ref UBX_BF_FLAGS_LEAP_SECONDS
  uint8_t valid;
  /// Time accuracy Estimate [ns]
  uint32_t tAcc;
}  __attribute__ ((packed)) tUBX_NAV_TIMEGPS;

typedef struct UBX_AID_HUI
{
  /// Bitmask, every bit represenst a GPS SV (1-32).
  /// If the bit is set the SV is healthy.
  /// @ref UBX_BF_FLAG_HEALTH_VALID, @ref UBX_BF_FLAG_UTC_VALID, @ref UBX_BF_FLAG_KLOB_VALID
  uint32_t health;
  /// UTC - parameter A0
  uint64_t utcA0;
  /// UTC - parameter A1
  uint64_t utcA1;
  /// UTC - reference time of week
  int32_t utcTOW;
  /// UTC - reference week number
  int16_t utcWNT;
  /// UTC - time difference due to leap seconds before event
  int16_t utcLS;
  /// UTC - week number when next leap second event occurs
  int16_t utcWNF;
  /// UTC - day of week when next leap second event occurs
  int16_t utcDN;
  /// UTC - time difference due to leap seconds after event
  int16_t utcLSF;
  /// UTC - Spare to ensure structure is a multiple of 4 bytes
  int16_t utcSpare;
  /// Klobuchar - alpha 0
  uint32_t klobA0;
  /// Klobuchar - alpha 1
  uint32_t klobA1;
  /// Klobuchar - alpha 2
  uint32_t klobA2;
  /// Klobuchar - alpha 3
  uint32_t klobA3;
  /// Klobuchar - beta 0
  uint32_t klobB0;
  /// Klobuchar - beta 1
  uint32_t klobB1;
  /// Klobuchar - beta 2
  uint32_t klobB2;
  /// Klobuchar - beta 3
  uint32_t klobB3;
  /// flags
  uint32_t flags;
}  __attribute__ ((packed)) tUBX_AID_HUI;

typedef struct UBX_NAV_SAT_INFO
{
  /// U1 GNSS identifier
  uint8_t GNNSId;
  /// U1   Satellite ID
  uint8_t SvID;
  /// U1   Carrier to noise ratio
  uint8_t Cno;
  /// I1   elevation
  int8_t  Elev;
  /// I2   azimuth
  int16_t Azim;
  /// I2   Pseudo range
  int16_t PrRes;
  /// X4  bitmask
  uint32_t Flags;
  // packed to avoid padding at the end
}  __attribute__ ((packed)) tUBX_NAV_SAT_INFO;

typedef struct UBX_NAV_SAT
{
  /// U4   iTOW GPS time of week [ms]
  uint32_t iTOW;
  /// U1   Message version
  uint8_t Version;
  /// U1   Number of satellites
  uint8_t NumSvs;
  /// U1[2]   Reserved
  uint8_t Reserved[2];
  // Satellite information to follow
  // packed to avoid padding at the end
}  __attribute__ ((packed)) tUBX_NAV_SAT;

// Repeated data for UBX_ESF_STATUS
typedef struct UBX_ESF_STATUS_INFO {
  /// X1    Sensor status, part 1 (Bitfield)
  uint8_t SensStatus1;
  /// X1    Sensor status, part 2 (Bitfield)
  uint8_t SensStatus2;
  /// U1    Observation frequency
  uint8_t Freq;
  /// X1    Sensor faults (Bitfield)
  uint8_t Faults;
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ESF_STATUS_INFO;

typedef struct UBX_ESF_STATUS {
  /// U4    iTOW GPS time of week [ms]
  uint32_t iTOW;
  /// U1    Message version ( 2 for this version )
  uint8_t version;
  uint8_t initStatus1;
  uint8_t initStatus2;
  /// U1[5] Reserved
  uint8_t Reserved[5];
  /// U1    fusionMode ( 0: Initialisation, 1: Fusion mode,
  ///                    2: Suspended fusion mode, 3: Disabled fusion mode)
  uint8_t FusionMode;
  /// U1[2] Reserved
  uint8_t Reserved2[2];
  /// U1    Number of sensors
  uint8_t NumSens;
  // Sensor calibration information to follow
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ESF_STATUS;

// Repeated data for UBX_ESF_RAW
typedef struct UBX_ESF_RAW_INFO {
  /// X4    Data (Bitfield)
  uint32_t data;
  /// U4    Sensor time tag.
  uint32_t sTtag;
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ESF_RAW_INFO;

typedef struct UBX_ESF_RAW {
  /// U1[4] Reserved
  uint8_t reserved1[4];
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ESF_RAW;

typedef struct UBX_ESF_INS {
  /// U4    Bitfield
  //  Contains Validities of all information and the version number
  uint32_t bitfield;
  /// U1[4] reserved1
  uint32_t reserved1;
  /// U4    GPS time of the week of the navigation epoch
  uint32_t iTOW;
  /// I4    Compensated x-axis angular rate
  int32_t xAngRate;
  /// I4    Compensated y-axis angular rate
  int32_t yAngRate;
  /// I4    Compensated z-axis angular rate
  int32_t zAngRate;
  /// I4    Compensated x-axis acceleration (gravity-free)
  int32_t xAccel;
  /// I4    Compensated y-axis acceleration (gravity-free)
  int32_t yAccel;
  /// I4    Compensated z-axis acceleration (gravity-free)
  int32_t zAccel;
  // packed to avoid padding at the end
} __attribute__ ((packed)) tUBX_ESF_INS;

typedef struct UBX_HNR_INS {
  /// U4    Bitfield
  //  Contains Validities of all information and the version number
  uint32_t bitfield;
  /// U1[4] reserved1
  uint32_t reserved1;
  /// U4    GPS time of the week of the navigation epoch
  uint32_t iTOW;
  /// I4    Compensated x-axis angular rate
  int32_t xAngRate;
  /// I4    Compensated y-axis angular rate
  int32_t yAngRate;
  /// I4    Compensated z-axis angular rate
  int32_t zAngRate;
  /// I4    Compensated x-axis acceleration (with gravity)
  int32_t xAccel;
  /// I4    Compensated y-axis acceleration (with gravity)
  int32_t yAccel;
  /// I4    Compensated z-axis acceleration (with gravity)
  int32_t zAccel;
  // packed to avoid padding at the end
} __attribute__ ((packed)) tUBX_HNR_INS;

/// UBX-CFG-NAV5 (0x06 0x24) Navigation engine settings
typedef struct UBX_CFG_NAV5
{
  /// Parameters bitmask. Only the masked parameters will be applied
  uint16_t mask;
  /// Dynamic platform model
  /// 0: portable
  /// 2: stationary
  /// 3: pedestrian
  /// 4: automotive
  /// 5: sea
  /// 6: airborne with <1g acceleration
  /// 7: airborne with <2g acceleration
  /// 8: airborne with <4g acceleration
  /// 9: wrist-worn watch (not supported inprotocol versions less than 18)
  /// 10: bike (supported in protocol versions 19.2)
  uint8_t dynModel;
  /// Position fixing mode:
  /// 1: 2D only
  /// 2: 3D only
  /// 3: auto 2D/3D
  uint8_t fixMode;
  /// Fixed altitude (mean sea level) for 2D fix mode [m * 0.01]
  int32_t fixedAlt;
  /// Fixed altitude variance for 2D mode [m^2 * 0.0001]
  uint32_t  fixedAltVar;
  /// Minimum elevation for a GNSS satellite to be used in NAV [deg]
  int8_t minElev;
  /// Reserved [s]
  uint8_t drLimit;
  /// Position DOP mask to use [n * 0.1]
  uint16_t pDop;
  /// Time DOP mask to use [n * 0.1]
  uint16_t tDop;
  /// Position accuracy mask [m]
  uint16_t pAcc;
  /// Time accuracy mask [m]
  uint16_t tAcc;
  /// Static hold threshold [cm/s]
  uint8_t staticHoldThresh;
  /// DGNSS timeout [s]
  uint8_t dgnssTimeout;
  /// Number of satellites required to have C/N0 above cnoThresh for a fix to be attempted
  uint8_t cnoThreshNumSVs;
  /// C/N0 threshold for deciding whether to attempt a fix [dBHz]
  uint8_t cnoThresh;
  /// Reserved
  uint8_t reserved1[2];
  /// Static hold distance threshold (before quitting static hold) [m]
  uint16_t staticHoldMaxDist;
  /// UTC standard to be used:
  /// 0: Automatic; receiver selects based on GNSS configuration (see GNSS time bases)
  /// 3: UTC as operated by the U.S. Naval Observatory (USNO); derived from GPS time
  /// 5: UTC as combined from multiple European laboratories; derived from Galileo time
  /// 6: UTC as operated by the former Soviet Union (SU); derived from GLONASS time
  /// 7: UTC as operated by the National Time Service Center (NTSC), China; derived from BeiDou time
  uint8_t utcStandard;
  /// Reserved
  uint8_t reserved2[5];

} __attribute__ ((packed)) tUBX_CFG_NAV5;

/// UBX-CFG-NAV5 constants
typedef enum {
  UBX_CFG_NAV5_CLASS_ID  = 0x06,
  UBX_CFG_NAV5_MESSAGE_ID = 0x24,
  UBX_CFG_NAV5_LENGTH = 36,

  UBX_CFG_NAV5_MASK_DYN            = (1 << 0),  ///< Apply dynamic model settings
  UBX_CFG_NAV5_MASK_MINEL          = (1 << 1),  ///< Apply minimum elevation settings
  UBX_CFG_NAV5_MASK_POSFIXMODE     = (1 << 2),  ///< Apply fix mode settings
  UBX_CFG_NAV5_MASK_DRLIM          = (1 << 3),  ///< Reserved
  UBX_CFG_NAV5_MASK_POSMASK        = (1 << 4),  ///< Apply position mask settings
  UBX_CFG_NAV5_MASK_TIMEMASK       = (1 << 5),  ///< Apply time mask settings
  UBX_CFG_NAV5_MASK_STATICHOLDMASK = (1 << 6),  ///< Apply static hold settings
  UBX_CFG_NAV5_MASK_DGPSMASK       = (1 << 7),  ///< Apply DGPS settings
  UBX_CFG_NAV5_MASK_CNOTHRESHOLD   = (1 << 8),  ///< Apply CNO threshold settings (cnoThresh, cnoThreshNumSVs)
  UBX_CFG_NAV5_MASK_UTC            = (1 << 10), ///< Apply UTC settings
} eUBX_CFG_NAV5;

/// UBX-CFG-NAVX5 (0x06 0x23) Navigation Engine Expert Settings
typedef struct UBX_CFG_NAVX5
{
  uint16_t version;       ///< Message version (set to 0)
  uint16_t mask1;         ///< First parameters bitmask
  uint32_t mask2;         ///< Second parameters bitmask (Firmware >=8 only)
  uint8_t  reserved1[2];  ///< Always set to zero
  uint8_t  minSVs;        ///< Minimum number of satellites for navigation
  uint8_t  maxSVs;        ///< Maximum number of satellites for navigation
  uint8_t  minCNO;        ///< Minimum satellite signal level for navigation [dBHz]
  uint8_t  reserved2;     ///< Always set to zero
  uint8_t  iniFix3D;      ///< If set to 1, initial fix must be 3D
  uint8_t  reserved3[2];  ///< Always set to zero

  uint8_t  ackAiding;     ///< If set to 1, issue acknowledgments for assistance
  uint16_t wknRollover;   ///< GPS week rollover number
  uint8_t  reserved4[6];  ///< Always set to zero
  uint8_t  usePPP;        ///< Enable/disable PPP (on supported units)
  uint8_t  aopCfg;        ///< AssistNow Autonomous configuration, 1: enabled
  uint8_t  reserved5[2];  ///< Always set to zero
  uint16_t aopOrbMaxErr;  ///< Maximum acceptable (modeled) autonomous orbit error [m] (valid range = 5..1000, 0 = reset to firmware default)
  uint8_t  reserved6[4];  ///< Always set to zero
  uint8_t  reserved7[3];  ///< Always set to zero
  uint8_t  useAdr;        ///< Enable/disable ADR sensor fusion. 1: enabled, 0: disabled
} __attribute__ ((packed)) tUBX_CFG_NAVX5;

/// UBX-CFG-NAVX5 constants
typedef enum {
  UBX_CFG_NAVX5_CLASS_ID  = 0x06,
  UBX_CFG_NAVX5_MESSAGE_ID = 0x23,
  UBX_CFG_NAVX5_LENGTH = 40,

  UBX_CFG_NAVX5_VERSION = 0,

  UBX_CFG_NAVX5_MASK1_MIN_MAX        = 4,     ///< apply min/max SVs settings
  UBX_CFG_NAVX5_MASK1_MIN_CNO        = 8,     ///< apply minimum C/N0 setting
  UBX_CFG_NAVX5_MASK1_INITIAL_FIX_3D = 64,    ///< apply initial 3D fix settings
  UBX_CFG_NAVX5_MASK1_WKN_ROLL       = 512,   ///< apply GPS week number rollover settings
  UBX_CFG_NAVX5_MASK1_ACK_AID        = 1024,  ///< apply assistance acknowledgment settings
  UBX_CFG_NAVX5_MASK1_PPP            = 8192,  ///< apply usePPP flag
  UBX_CFG_NAVX5_MASK1_AOP            = 16384, ///< apply aopCfg (useAOP flag) and aopOrbMaxErr settings (AssistNow Autonomous)

  UBX_CFG_NAVX5_MASK2_ADR = 64,                  ///< Apply ADR sensor fusion on/off setting
  UBX_CFG_NAVX5_MASK2_SIG_ATTEN_COMP_MODE = 128, ///< Apply signal attenuation compensation feature settings
} eUBX_CFG_NAVX5;

/// UBX-CFG-MSG (0x06 0x01) Message configuration
typedef struct UBX_CFG_MSG
{
  /// Message class
  uint8_t msgClass;
  /// Message identifier
  uint8_t msgID;
  /// Send rate on current port
  uint8_t rate;
} __attribute__ ((packed)) tUBX_CFG_MSG;

/// UBX-CFG-MSG constants
typedef enum {
  UBX_CFG_MSG_CLASS_ID  = 0x06,
  UBX_CFG_MSG_MESSAGE_ID = 0x01,
  UBX_CFG_MSG_LENGTH = 3,
} eUBX_CFG_MSG;


/// Wheel-tick confiuration message - 32 bytes.
typedef struct UBX_CFG_ESFWT
{
  /// U4    Bitfield
  ///  Version
  uint8_t version; // set to zero
  /// flags1 field
  uint8_t flags1;
  /// flags2 field
  uint8_t flags2;
  /// unused, set to zero
  uint8_t reserved1;
  /// wheel-tick scale factor
  uint32_t wtFactor;
  /// quantisation error or RMS error in speed measurement (m/s 1e-6)
  uint32_t wtQantError;
  /// max wtcount - set to zero
  uint32_t wtCountMax;
  /// speed measurement latency - in ms.
  uint16_t wtLatency;
  uint8_t wtFrequency;
  uint8_t flags3;
  uint16_t speedDeadBand;
  uint8_t reserved2[10];
} __attribute__ ((packed)) tUBX_CFG_ESFWT;


/// UBX-CFG-ESFGAWT (0x06 0x2D)
typedef struct UBX_CFG_ESFGAWT
{
  /// Message version (0 for this version)
  uint8_t version;
  /// Identification number of the sensor data provider: set to zero
  uint8_t id;
  /// UBX_CFG_ESFGAWT_FLAGS_*
  uint16_t flags;
  /// Sensor time tag scale factor to seconds [n * 1e-6]
  uint32_t senTtagFactor;
  /// Sensor time tag maximum value (rollover - 1)
  uint32_t senTtagMax;
  /// Wheel tick factor to obtain distance [m * 1e-6] from wheel ticks (0 = not set)
  uint32_t wtFactor;
  /// Wheel tick quantization. [m * 1e-6] (or m/s)
  /// If useWtSpeed is set then this is interpreted as the speed measurement error RMS.
  uint32_t wtQuantError;
  /// Wheel tick counter maximum value (rollover - 1) (0 if no rollover but relative values).
  /// If useWtSpeed is set then this value is ignored.
  uint32_t wtCountMax;
  /// Wheel tick data latency due to e.g. CAN bus [ms]
  uint16_t wtLatency;
  /// Nominal wheel tick data frequency (0 = not set) [Hz]
  uint8_t wtFrequency;
  /// Nominal gyroscope data frequency (0 = not set)
  uint8_t gyroFrequency;
  /// Gyroscope measurement accuracy [deg/s * 1e-6]
  uint16_t gyroAcc;
  /// Gyroscope data latency due to e.g. CAN bus [ms]
  uint16_t gyroLatency;
  /// Accelerometer measurement accuracy [m/s^2 * 1e-4]
  uint16_t accelAcc;
  /// Accelerometer data latency due to e.g. CAN bus [ms]
  uint16_t accelLatency;
  /// Nominal accelerometer data frequency (0 = not set) [Hz]
  uint8_t accelFrequency;
  ///
  uint8_t reserved1;
  /// Speed sensor dead band (0 = not set) [cm/s]
  uint16_t speedDeadBand;
  /// Temperature compensation table save-to-flash interval [s]
  uint16_t tcTableSaveRate;
  /// Gyroscope RMS threshold for automatic noise-level (accuracy) estimation and
  /// temperature compensation table entry (0: no temperature compensation)
  /// [deg/s * 2^-8]
  uint8_t gyroRmsThdl;
  /// Accelerometer RMS threshold for automatic noise-level (accuracy) estimation and
  /// temperature compensation table entry (0: no temperature compensation)
  /// [m/s^2 * 2^-6]
  uint8_t accelRmsThdl;
  /// UBX_CFG_ESFGAWT_FLAGS2_*
  uint32_t flags2;
  ///
  uint8_t reserved2[4];
} __attribute__ ((packed)) tUBX_CFG_ESFGAWT;

/// UBX-CFG-ESFGAWT constants
typedef enum {
  UBX_CFG_ESFGAWT_CLASS_ID  = 0x06,
  UBX_CFG_ESFGAWT_MESSAGE_ID = 0x2d,
  UBX_CFG_ESFGAWT_LENGTH = 52,

  /// Use combined rear wheel ticks instead of the single tick
  UBX_CFG_ESFGAWT_FLAGS_COMBINETICKS = (1 << 0),
  /// Use speed measurements (data type 11 in ESF-MEAS) instead of single ticks (data type 10)
  UBX_CFG_ESFGAWT_FLAGS_USEWTSPEED = (1<< 10),
  /// Direction pin polarity
  /// 0: High signal level means forward direction,
  /// 1: High signal level means backward direction.
  UBX_CFG_ESFGWT_FLAGS_DIRPINPOL = (1 << 12),
  /// Use wheel tick pin for speed measurement.
  /// This field can only be used with modules supporting analog wheel-tick signals.
  UBX_CFG_ESFGWT_FLAGS_USEWTPIN = (1 << 13),

  // Count both rising and falling edges on wheel tick signal
  // (only relevant if wheel tick is measured by the u-blox receiver).
  // Only turn on this feature if the wheel-tick signal has 50 % duty cycle.
  UBX_CFG_ESFGWT_FLAGS2_CNTBOTHEDGES = (1 << 13),

} eUBX_CFG_ESFGAWT;

/// UBX-CFG-ESFALG (0x06 0x56) IMU-mount misalignment configuration
typedef struct UBX_CFG_ESFALG
{
  /// Bitfield
  uint32_t bitfield;
  /// User-defined IMU-mount yaw angle (0..360) [deg * 1e-2]
  uint32_t yaw;
  /// User-defined IMU-mount pitch angle (-90..90) [deg * 1e-2]
  int16_t pitch;
  /// User-defined IMU-mount roll angle (-180...180) [deg * 1e-2]
  int16_t roll;

} __attribute__ ((packed)) tUBX_CFG_ESFALG;
/// UBX-CFG-ESFALG constants
typedef enum {
  UBX_CFG_ESFALG_CLASS_ID  = 0x06,
  UBX_CFG_ESFALG_MESSAGE_ID = 0x56,
  UBX_CFG_ESFALG_LENGTH = 12,

  UBX_CFG_ESFALG_BITFIELD_DOAUTOMNTALG = (1 << 8),
} eUBX_CFG_ESFALG;

/// UBX-CFG-ESFLA (0x06 0x2F) lever-arm configuration
typedef struct UBX_CFG_ESFLA
{
  /// Message version (0)
  uint8_t version;
  /// Number of lever-arm configurations in the message (2)
  uint8_t numConfigs;
  /// Reserved
  uint8_t reserved1[2];
  /// Antenna
  struct {
    /// 0: VRP-to-Antenna
    uint8_t leverArmType;
    /// Reserved
    uint8_t reserved2;
    /// x coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmX;
    /// y coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmY;
    /// z coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmZ;
  } Ant;
  /// IMU
  struct {
    /// 1: VRP-to-IMU
    uint8_t leverArmType;
    /// Reserved
    uint8_t reserved2;
    /// x coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmX;
    /// y coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmY;
    /// z coordinate of lever-arm in the installation-frame [cm]
    int16_t leverArmZ;
  } IMU;
} __attribute__ ((packed)) tUBX_CFG_ESFLA;

/// UBX-CFG-ESFLA constants
typedef enum {
  UBX_CFG_ESFLA_CLASS_ID  = 0x06,
  UBX_CFG_ESFLA_MESSAGE_ID = 0x2F,
  UBX_CFG_ESFLA_LENGTH = 20,
} eUBX_CFG_ESFLA;


/// Time tag configuration message
typedef struct UBX_CFG_ESFTTAG
{
  /// Version, set to zero
  uint8_t version; // set to zero
  /// reserved, set to zero
  uint8_t reserved1[3];
  /// Time tag scaling factor to seconds x 1e-6, eg 1000 == ttags are in ms
  uint32_t ttagFactor;
  /// Maximum time tag value
  uint32_t ttagMax;
  /// reserved, set to zero
  uint32_t reserved2;
} __attribute__ ((packed)) tUBX_CFG_ESFTTAG;

/// Set the ESF_MEASURE message data fields.
#define UBX_ESF_MEASURE_SET_DATA(type, data) (((type << 24) & 0xff000000) | (data & 0x00ffffff))

// ESF_MEAS data types
enum
{
  /// z-axis gyroscope angular rate (ie, yaw-rate) [deg/s * 2^-12] signed
  UBX_ESF_DATA_TYPE_ZAXIS_GYRO_RATE = 5,
  /// speed [m/s * 1e-3] signed
  UBX_ESF_DATA_TYPE_SPEED = 11,
  // x-axis accelerometer specific force [m/s^2 * 2^-10] signed
  UBX_ESF_DATA_TYPE_XAXIS_ACCEL_FORCE = 16,
  // y-axis accelerometer specific force [m/s^2 * 2^-10] signed
  UBX_ESF_DATA_TYPE_YAXIS_ACCEL_FORCE = 17,
  // z-axis accelerometer specific force [m/s^2 * 2^-10] signed
  UBX_ESF_DATA_TYPE_ZAXIS_ACCEL_FORCE = 18,

};

typedef struct UBX_ESF_MEAS_DATA
{
  /// X4    Data
  uint32_t  Data;
  // packed to avoid padding at the end
} __attribute__ ((packed)) tUBX_ESF_MEAS_DATA;

typedef struct UBX_ESF_MEAS
{
  /// U4    Time tag of measurement generated by external sensor
  uint32_t  TimeTag;
  /// U2    Flags. Set all unused bits to zero
  uint16_t  Flags;
  /// U2    Identification number of data provider
  uint16_t  Id;
  // Sensor data to follow
  tUBX_ESF_MEAS_DATA Data[0];
  // packed to avoid padding at the end
} __attribute__ ((packed)) tUBX_ESF_MEAS;

typedef struct UBX_ACK_ACK {
  /// U1 Class ID of the Acknowledged Message
  uint8_t ClsID;
  /// U1 Message ID of the Acknowledged Message
  uint8_t MsgID;
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ACK_ACK;

typedef struct UBX_ACK_NAK {
  /// U1 Class ID of the Not-Acknowledged Message
  uint8_t ClsID;
  /// U1 Message ID of the Not-Acknowledged Message
  uint8_t MsgID;
  // packed to avoid padding at the end
}__attribute__ ((packed)) tUBX_ACK_NAK;

typedef struct UBX_UPD_SOS {
  /// U1 Command (0 for create backup, 1 for clear backup,
  ///             2 for backup create ack, 3 for backup restore ack)
  uint8_t cmd;
  /// U1[3] reserved1
  uint8_t reserved1[3];
  /// U1 Response (0: Unknown, 1: Failed to restore, 2: Restored, 3: No backup)
  uint8_t response;
  /// U1[3] reserved2
  uint8_t reserved2[3];
} __attribute__ ((packed)) tUBX_UPD_SOS;

typedef struct UBX_Packet {
  tUBX_Header Header;
  union {
    tUBX_NAV_PVT PVT;
    tUBX_NAV_HNR HNR;
    tUBX_HNR_PVT HNR_PVT;
    tUBX_NAV_DOP DOP;
    tUBX_NAV_COV COV;
    tUBX_NAV_TIMEGPS TIMEGPS;
    tUBX_AID_HUI HUI;
    tUBX_NAV_SAT SAT;
    tUBX_ESF_STATUS STATUS;
    tUBX_ESF_RAW RAW;
    tUBX_ESF_INS ESF_INS;
    tUBX_HNR_INS HNR_INS;
    tUBX_ESF_MEAS MEAS;
    tUBX_ACK_ACK ACK;
    tUBX_ACK_NAK NAK;
    tUBX_UPD_SOS SOS;
    tUBX_MON_VER MON;
  };
} __attribute__ ((packed)) tUBX_Packet;

typedef void (fUbx_CallbackApplication)(void * pPriv, const tUBX_Packet * pPkt);

typedef struct Ubx_Callback {
  uint8_t Class;
  uint8_t MessageID;
  /// Callback should be called for all valid messages
  bool AllMessages;
  fUbx_CallbackApplication *pCallback;
  void *pPriv;
} tUbx_Callback;

// State information for Ubx Callbacks
typedef struct Ubx {
  /// Flag that callback sub-system is ready
  int CallbackInitialised;
  pthread_mutex_t Ubx_CallbackLock;
  // Number of registered callbacks
  unsigned NbrCallbacks;
  // Callbacks
  tUbx_Callback Callbacks[UBX_MAX_NUM_CALLBACKS];
} tUbx;



//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void UBX8_Init(void);
void UBX8_ProcessUbxPacket(void * pBuf, int Length);
tUbx_ErrCode UBX8_RegisterCallback(uint8_t Class,
                                   uint8_t MessageID,
                                   bool    AllMessages,
                                   fUbx_CallbackApplication *pCallback,
                                   void * pPriv);

tUbx_ErrCode UBX8_DeregisterCallback(uint8_t Class, uint8_t MessageID,
                                     fUbx_CallbackApplication *pCallback);
void UBX8_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif // __INCLUDE_UBX8_H_

/**
 * @}
 */
