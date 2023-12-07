#pragma once
/**
 * @addtogroup ta_api Threat Arbitrator (TA) API
 * @{
 *
 * @file
 *
 * Event Data Recorder definitions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#ifdef PACKED
#undef PACKED
#define PACKED __attribute__ ((packed))
#else
#define PACKED
#endif

/// Number of RVs per ADR record, maximum value
#define CW_ADR_RV_CNT  12
/// Number of SPAT/MAP intersections per ADR record
#define CW_ADR_INTXN_CNT  3

#define TA_ADR_CNTRL_BRK_UNAVAIL    (1<<0)
#define TA_ADR_CNTRL_BRK_ON         (1<<1)
#define TA_ADR_CNTRL_THROTTLE       (1<<2)
#define TA_ADR_CNTRL_TRACTION       (1<<3)
#define TA_ADR_CNTRL_BRK_ABS        (1<<4)
#define TA_ADR_CNTRL_ESC            (1<<5)
#define TA_ADR_CNTRL_AIRBAG         (1<<6)
#define TA_ADR_CNTRL_HARD_BRAKE     (1<<7)
#define TA_ADR_CNTRL_BRK_ANY (TA_ADR_CNTRL_BRK_ON|TA_ADR_CNTRL_BRK_ABS|TA_ADR_CNTRL_HARD_BRAKE)

#define TA_ADR_LIGHT_OFF            (0)
#define TA_ADR_LIGHT_LOW            (1<<0)
#define TA_ADR_LIGHT_HIGH           (1<<1)
#define TA_ADR_LIGHT_LEFT           (1<<2)
#define TA_ADR_LIGHT_RIGHT          (1<<3)
#define TA_ADR_LIGHT_HZRD (TA_ADR_LIGHT_LEFT|TA_ADR_LIGHT_RIGHT)
#define TA_ADR_LIGHT_HV_AUTO        (1<<4)
#define TA_ADR_LIGHT_HV_DTR         (1<<5)
#define TA_ADR_LIGHT_RV_EVW         (1<<4)
#define TA_ADR_LIGHT_RV_RWW         (1<<5)
#define TA_ADR_LIGHT_FOG            (1<<6)
#define TA_ADR_LIGHT_PARK           (1<<7)


// RV.TA.Flags: Collapse TA_THREATTYPE_* down to 8 bits
#define TA_ADR_THREATTYPE_NONE      0 ///< No alert
#define TA_ADR_THREATTYPE_EEBL_MASK (1<<0) ///< Emergency Electronic Brake Light
#define TA_ADR_THREATTYPE_HLW_MASK  (1<<1) ///< Hazard location warning
#define TA_ADR_THREATTYPE_SVA_MASK  (1<<2) ///< Stationary Vehicles Ahead
#define TA_ADR_THREATTYPE_FCW_MASK  (1<<3) ///< Forward Collision Warning
#define TA_ADR_THREATTYPE_ICW_MASK  (1<<4) ///< Intersection Collision Warning
#define TA_ADR_THREATTYPE_EVW_MASK  (1<<5) ///< Emergency Vehicle Warning
#define TA_ADR_THREATTYPE_TJA_MASK  (1<<6) ///< Traffic Jam Ahead
#define TA_ADR_THREATTYPE_V2I_MASK  (1<<7) ///< Green Light Speed Advice, Signal Violation Warning, In Vehicle Signage

// IntXn.LAne.Lights.Direction values
#define TA_ADR_TRAFFICLIGHT_DIRECTION_Ball   (0x01)
#define TA_ADR_TRAFFICLIGHT_DIRECTION_Left   (0x02)
#define TA_ADR_TRAFFICLIGHT_DIRECTION_Right  (0x03)
#define TA_ADR_TRAFFICLIGHT_DIRECTION_UTurn  (0x04)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// @ref eTCClassif
typedef enum
{
  /// Range > CW_TC_MAX_RANGE
  TA_ADR_CLASSIF_NONE               = 0x0000,
  /// Elev within CW_TC_SAME_ELEVATION_LIMIT_MIN/MAX
  TA_ADR_CLASSIF_SAME_ELEVATION     = 0x0001,
  /// Elev outside CW_TC_SAME_ELEVATION_LIMIT_MIN/MAX
  TA_ADR_CLASSIF_DIFF_ELEVATION     = 0x0002,
  /// abs(HeadingDiff) < CW_TC_SAME_HEADING_LIMIT
  TA_ADR_CLASSIF_SIMILAR_DIRECTION  = 0x0004,
  /// abs(HeadingDiff) > CW_TC_OPPOSITE_HEADING_LIMIT
  TA_ADR_CLASSIF_OPPOSITE_DIRECTION = 0x0008,
  /// Separation Velocity < CW_RELATIVE_SPEED_CLOSING
  TA_ADR_CLASSIF_CLOSING            = 0x0010,
  /// Separation Velocity > CW_RELATIVE_SPEED_RECEDING (i.e. separating)
  TA_ADR_CLASSIF_RECEDING           = 0x0020,
  /// abs(Azimuth) < CW_TC_FWD_BORESIGHT_LIMIT
  TA_ADR_CLASSIF_IS_AHEAD           = 0x0040,
  /// abs(Azimuth) > CW_TC_REAR_BORESIGHT_LIMIT
  TA_ADR_CLASSIF_IS_BEHIND          = 0x0080,
  /// (PHdist || PPdist) < CW_TC_LANE_SEPARATION
  TA_ADR_CLASSIF_SAME_LANE          = 0x0100,
  /// (PHdist || PPdist) < (CW_TC_LANE_SEPARATION/2) + CW_TC_LANE_WIDTH
  TA_ADR_CLASSIF_NEAR_LANE          = 0x0200,
  /// (PHdist || PPdist) > (CW_TC_LANE_WIDTH*2)
  TA_ADR_CLASSIF_FAR_LANE           = 0x0400,
  /// Azimuth < 0 && !IS_AHEAD && !IS_BEHIND
  TA_ADR_CLASSIF_IS_LEFT            = 0x0800,
  /// Azimuth > 0 && !IS_AHEAD && !IS_BEHIND
  TA_ADR_CLASSIF_IS_RIGHT           = 0x1000,
  /// Intersecting vectors
  TA_ADR_CLASSIF_LINE_LINE_XSING    = 0x2000,
  /// Intersecting vector & PP circle
  TA_ADR_CLASSIF_LINE_CIRC_XSING    = 0x4000,
  /// PP circles intersecting
  TA_ADR_CLASSIF_CIRC_CIRC_XSING    = 0x8000,
  /// Intersecting vectors
  TA_ADR_CLASSIF_XSING              = 0xE000,
} eTAADRClassif;

/// Heading Units (wraps naturally)
/// NORTH =    0 (  0deg,   0   rad)
/// EAST  =   64 ( 90deg,  pi/2 rad)
/// SOUTH = -128 (180deg,  pi   rad)
/// WEST  =  -64 (270deg, -pi/2 rad)
typedef int8_t tADRHead;

/// Time Normalised Minute Units (2^16 ticks per minute)
/// Multiply milliseconds by 2^16/60000 and store in uint16.
/// Then can do wrapping arithmetic (module 1 minute) for free.
/// Differences of more than 30 sec no longer safe.
typedef uint16_t tADRTime;
/// See @ref tADRTime
typedef  int16_t tADRTimeDiff;

/////////////////////////// E.2.2.6 ADR format
/////////////////////////// The format is shown below:

typedef struct ADRTM
{
  /// Active (highest priority) alert
  uint8_t AlertId;
  /// RV that the alert is caused by
  uint8_t Id;
  /// Alert specific info (distance, bearing...)
  int16_t Extra;
} PACKED tADRTM;

/// Path history point
typedef struct ADRPHpoint
{
  /// INTEGER (-32768..32767) (16 signed bits) in 4/10th micro degrees
  /// value  32767 to be used for  131068 or greater
  /// value -32767 to be used for -131068 or less
  /// value -32768 to be used for unavailable lat or long
  /// Offset from tADRRV.DeltaLat which is the RV offset from the HV
  int16_t DeltaLat; // (same as OTA format)
  /// see @ref DeltaLat;
  int16_t DeltaLon; // (same as OTA format)
  /// INTEGER (-128..127), LSB units of 1m
  /// value  127 to be used for  127 or greater
  /// value -127 to be used for -127 or less
  /// value -128 for unavailable
  int8_t DeltaElev;
  /// Time difference [100ms]
  int8_t  DeltaTime;
} PACKED tADRPHpoint;

/// Path History
typedef struct ADRPH
{
  /// PH count
  uint8_t PHCount;
  // TC calculated separations
  /// Lateral separation (-12.8...12.7 m)
  /// overflow? underflow? unavail?
  int8_t LatSep;
  /// Longitudinal separation (-4096...4095 m)
  /// scale to use all 16 bits?
  /// overflow? underflow? unavail?
  int16_t LonSep;
  /// 1st PH point
  tADRPHpoint First;
  /// Last/Matching PH point (may be same as First)
  tADRPHpoint Match;
} PACKED tADRPH;

/// Common vehicle info
typedef struct ADRVeh
{
  /// range 0-12.7 meter, LSB = .05m
  /// 0xFE=254=any value equal or greater than 12.70 meter
  /// 0xFF=255=unavailable value
  uint8_t PositionConfidence;
  /// Heading
  tADRHead Heading;

  /// Transmission in top 3 bits (PRNDL)
  /// see "typedef enum TransmissionState" in j2735.h
  /// INTEGER (0..8191) -- Units of 0.02 m/s
  /// The value 8191 indicates that speed is unavailable
  uint16_t TransmissionAndSpeed;
  // (except for being little-endian this is the same as in the blob etc.)
  /// see TA_ADR_CNTRL_*
  /// BrakesUnavail           (1),      -- B'0000-0001
  /// Brakes                  (2),      -- B'0000-0010
  /// Throttle                (4),      -- B'0000-0100
  /// Traction                (8),      -- B'0000-1000
  /// AntiLockBrake           (16),     -- B'0001-0000
  /// StabilityControl        (32),     -- B'0010-0000
  /// Airbag                  (64),     -- B'0100-0000
  /// HardBraking            (128)      -- B'1000-0000
  uint8_t Control;
  /// INTEGER (-128..127) LSB units are 0.16 m/s^2
  /// value 127 to be used for values greater than 20.32
  /// value -127 to be used for values less than -20.32
  ///  value -128 to be used for unavailable
  int8_t LonAccel;
  /// INTEGER (-128..127), LSB units of 2.55 degs/s/s
  /// value  127 to be used for  327 or greater
  /// value -127 to be used for -327 or less
  /// value -128 for unavailable
  int8_t YawRate;
  /// LSB units of 1.5 degrees.
  /// a range of -189 to +189 degrees
  /// 0x01 = 00 = +1.5 deg
  /// 0x81 = -126 = -189 deg and beyond
  /// 0x7E = +126 = +189 deg and beyond
  /// 0x7F = +127 to be used for unavailable
  int8_t SteeringWheelAngle;
  /// see TA_ADR_LIGHT_*
  /// ExteriorLights
  /// allLightsOff              (0),      -- B'0000-0000
  /// lowBeamHeadlightsOn       (1),      -- B'0000-0001
  /// highBeamHeadlightsOn      (2),      -- B'0000-0010
  /// leftTurnSignalOn          (4),      -- B'0000-0100
  /// rightTurnSignalOn         (8),      -- B'0000-1000
  /// hazardSignalOn            (12),     -- B'0000-1100 left + right
  /// automaticLightControlOn   (16),     -- B'0001-0000 (HV only)
  /// daytimeRunningLightsOn    (32),     -- B'0010-0000 (HV only)
  /// emergencyVehicleLightbar  (16),     -- B'0001-0000 (RV only)
  /// roadworkSign              (32),     -- B'0010-0000 (RV only)
  /// fogLightOn                (64),     -- B'0100-0000
  /// parkingLightsOn           (128)     -- B'1000-0000
  uint8_t Lights;
  /// PP confidence [100/255 %]
  uint8_t PPConf;
  /// PP radius [m]
  /// unavail? straight?
  int16_t PPRadius;

  /// INTEGER (0..25.5m) -- LSB units are 10 cm
  uint8_t Width;
  /// INTEGER (0..25.5m) -- LSB units are 10 cm
  uint8_t Length;

  union
  {
    /// HV specific info
    struct
    {
      /// Number of RVs processed (0..1024)
      uint16_t RVs:10;
      /// Number of Intersections (SPAT/MAP) processed (0..7)
      uint16_t Intersections:3;
      /// Number of LDM messages (IVI) processed (0..7)
      uint16_t LDMs:3;
    } HV;
    /// RV specific
    struct
    {
      /// RSSI of corresponding OTA packet (if available, else 0)
      int8_t RSSI;
      /// Counter incremented at each packet reception
      uint8_t RxCnt;
    } RV;
  };

} PACKED tADRVeh;

typedef struct ADRRV
{
  /// Unique identifier (0xFF for unavailable)
  uint8_t Id;
  /// Sequence number (0..127) (BSM's only)
  uint8_t SeqNbr;
  /// DSecond / Generation time
  tADRTime Timestamp;
  /// INTEGER (-32768..32767) (16 signed bits) in 4/10th micro degrees
  /// value  32767 to be used for  131071 or greater
  /// value -32767 to be used for -32767 or less
  /// value -32768 to be used for unavailable lat or long
  int16_t DeltaLat;
  /// see @ref DeltaLat;
  int16_t DeltaLon;
  /// INTEGER (-128..127), LSB units of 1m
  /// value  127 to be used for  127 or greater
  /// value -127 to be used for -127 or less
  /// value -128 for unavailable
  int8_t DeltaElev;
  /// Security info (verified, not verified, failure, etc.)
  uint8_t Security;
  /// TA
  struct
  {
    /// Alert flags (SVA, EEBL, ICW...)
    /// The TA_THREATTYPE_* is collapsed down to just 8 bits:
    /// See @ref tTAThreatType to determine the value of each alert
    ///   e.g. TA_THREATTYPE_GLOSA = (UINT32_C(1)<<18)
    ///        ... which becomes TA_ADR_THREATTYPE_GLOSA = 18 + 1
    uint8_t Flags;
    /// Highest severity
    uint8_t Severity;
  } PACKED TA;
  /// TC
  struct
  {
    // Vector separation

    /// Northings (X) offset from HV to RV (-2048...2047 m)
    /// +'ve means the RV is north of the HV
    int16_t  North;
    /// Eastings (Y)  offset from HV to RV (-2048...2047 m)
    /// +'ve means the RV is east of the HV
    int16_t  East;
    /// Elevation     offset from HV to RV (-128...127 m)
    /// +'ve means the RV is above the HV
    int8_t   Elev;
    int8_t   Accel;       ///< Relative Accel: Rate of change of Rate of change of separation (-12.8...12.7 m/s/s)
    int16_t  Velocity;    ///< Relative HorizontalSpeed: Rate of change of separation (-327.67 to 327.67 m/s)
    uint16_t  Range;      ///< Range: Distance between Locations (0..6553.5 m)
    tADRHead Bearing;     ///< Horizontal Bearing to RV from HV
    tADRHead HeadingDiff; ///< Heading of RV relative to HV
    tADRHead Azimuth;     ///< Relative bearing of RV from HV
    uint8_t  _PADDING_;
    tADRTimeDiff TimeDiff;    ///< Time difference. Normalised Minute Units (2^16 ticks per minute)
    /// Classification
    uint16_t Classification;
    /// Path history matching
    tADRPH PH;
  } PACKED TC;
  /// Vehicle info
  tADRVeh Veh;
} PACKED tADRRV;

// SPAT & MAP based intersection info
typedef struct ADRIntXn
{
  /// Unique identifier (0xFFFF for unavailable)
  uint16_t Id;
  /// Flags
  uint8_t Flags;
  /// Confidence
  uint8_t Confidence;
  /// INTEGER (-32768..32767) (16 signed bits) in 4/10th micro degrees
  /// value  32767 to be used for  32767 or greater
  /// value -32767 to be used for -32767 or less
  /// value -32768 to be used for unavailable
  int16_t DeltaLat;
  /// see @ref DeltaLat;
  int16_t DeltaLon;

  /// Lanes
  struct
  {
    /// Lane identifier (0xFF for unavailable)
    uint8_t Id;
    /// Confidence
    uint8_t Confidence;
    /// Longitudinal separation (-4096...4095 m) to stop line
    int16_t LonSep;
    /// Lateral separation (-12.8...12.7 m) from lane center
    int8_t LatSep;
    /// Heading of RV relative to lane's
    tADRHead HeadingDiff;

    /// Nodes (first, mid, last) intermental offsets relative to IntXn lat/lon
    struct
    {
      /// INTEGER (-128..127) (8 signed bits) in 2 meter units
      /// value  127 to be used for 254m or greater
      /// value -127 to be used for -254m or less
      /// value -128 to be used for unavailable
      int8_t X;
      int8_t Y;
    } PACKED Node[3];

    /// Light state (ball, left/right/other)
    struct
    {
      /// See TA_ADR_TRAFFICLIGHT_DIRECTION_* ball:1 left:2 right:3 uturn:4
      uint8_t Direction:3;
      /// See @ref SPATMAPLightColorState. off:0 green:1 yellow:2 red:3
      uint8_t State:5;
      /// When a signal phase is predicted to change (step of 1/10 second)
      /// value 254 to be used for 25.4s or greater
      /// value 255 to be used for unavailable
      uint8_t TimeToChange;
      /// SPAT's speed reccomendation
      /// 0..254 = 0..127 kph (steps of 0.5 kph), 255 = unavailible
      uint8_t RecomendedSpeed;
    } PACKED Light[2];

  } PACKED Lane[3];

} PACKED tADRIntXn;

/// Local (host/ego) vehicle
typedef struct ADRHV
{
  /// absolute position
  /// Units of 1/10th micro degrees (tLPHPos)
  int32_t Lat;
  /// Units of 1/10th micro degrees (tLPHPos)
  int32_t Lon;
  /// LSB units of 0.1m (J2735's DE_Elevation, tLPHPos)
  /// Range: 0x0000..0xEFFF (0 to 6143.9 meters) Units: 0.1 m
  /// Range: 0xF001..0xFFFF (-409.5 to -0.1 meters) Units: 0.1 m
  uint16_t Elev;
  /// HV's grade [1/8'th degrees]
  int8_t   Slope;
  /// System State (low 8 bits only) @ref StateFlags
  int8_t   State;
  /// Vehicle info (specific to HV)
  tADRVeh Veh;
} PACKED tADRHV;

/// Header (32bits)
typedef union ADRHdr
{
  /// Legacy (Pre-versioning) Unix epoch time
  uint32_t Timestamp;
  /// Generic version & Info
  struct {
    uint32_t Version:4; ///< Version 0..15
    uint32_t Extra:28;  ///< Version specific data
  };
  // Version = 0x1
  struct {
    uint32_t Version1:4; ///< == 0x1
    uint32_t DeciSec:20; ///< Deciseconds since 1970 epoch (20 LSbs ~= 29h)
    uint32_t RV:6;       ///< == # of tADRRV records. 0..63
    uint32_t IntXn:2;    ///< == # of tADRIntXn records. 0..3
  };
} PACKED tADRHdr;

typedef struct ADR
{
  // Header
  tADRHdr Hdr;
  /// Threat manager state
  tADRTM TM;
  /// Host vehicle info
  tADRHV HV;
  union {
    /// Remote vehicle info
    /// (the most interesting ones: alerting, event flags set, intersecting, high closing rate)
    tADRRV RV[0];
    /// SPAT/MAP intersections (immediately following the RVs)
    tADRIntXn IntXn[0];
    /// Binary data
    uint8_t Data[(sizeof(tADRRV) * CW_ADR_RV_CNT)];
  };
} tADR;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */
