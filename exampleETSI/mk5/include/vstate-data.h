#pragma once
/**
 * @addtogroup vstate_api Vehicle State (VSTATE) API
 * @{
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __VSTATE_DATA_H_
#define __VSTATE_DATA_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "vstate_gen.h"

#include "default_stack_defn.h"

#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// check if the data is available
#define VSTATE_IS_AVAIL(x) ((x).Meta.State != unavailable)

/// Set the field as available
#define VSTATE_SET_AVAIL(x) ((x).Meta.State = available)

/// Set the field as unavailable
#define VSTATE_SET_UNAVAIL(x) ((x).Meta.State = unavailable)

/// check if the non-boolean data is available and non-zero
#define VSTATE_IS_SET(x) (VSTATE_IS_AVAIL(x) && (x).Raw)

/// check if the boolean data is available and active
#define VSTATE_IS_ACTIVE(x)                     \
  (((x).Flag)                                   \
   &&                                           \
   (((x).Meta.State == activeEvt)               \
    ||                                          \
    ((x).Meta.State == available)))

/// check if the boolean data is available and inactive
#define VSTATE_IS_INACTIVE(x)                   \
  ((!(x).Flag)                                  \
   &&                                           \
   (((x).Meta.State == passiveEvt)              \
    ||                                          \
    ((x).Meta.State == available)))

/// J2735 Events mask
#define VSTATE_J2735_EVENTS_MASK (\
    VSTATE_ALERT_AIRBAGDEPLOYMENT | VSTATE_ALERT_HARDBRAKING |\
    VSTATE_ALERT_STABILITYCONTROLACTIVATED | VSTATE_ALERT_TRACTIONCONTROLLOSS|\
    VSTATE_ALERT_ABSACTIVATED | VSTATE_ALERT_HAZARDLIGHTS)

/// Emergency Events mask
#define VSTATE_EMERGENCY_EVENTS_MASK (\
    VSTATE_ALERT_AIRBAGDEPLOYMENT | VSTATE_ALERT_HARDBRAKING |\
    VSTATE_ALERT_STABILITYCONTROLACTIVATED | VSTATE_ALERT_TRACTIONCONTROLLOSS|\
    VSTATE_ALERT_ABSACTIVATED)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Enumeration of potential events that can be signalled by VSTATE
typedef enum VstateEventType
{
  /// No active events
  VSTATE_ALERT_NONE                      =  0,

  /// Error notification
  VSTATE_ALERT_ERROR                     = (UINT32_C(1) <<  0),

  /// Hazards activated
  VSTATE_ALERT_HzdLgts                   = (UINT32_C(1) <<  1),
  /// ABS activated
  VSTATE_ALERT_ABSAct                    = (UINT32_C(1) <<  2),
  /// Traction Control activated
  VSTATE_ALERT_TrcCtrlAct                = (UINT32_C(1) <<  3),
  /// Stability Control activated
  VSTATE_ALERT_StbCtrlAct                = (UINT32_C(1) <<  4),
  /// Hard Braking detected
  VSTATE_ALERT_PanicBrake                = (UINT32_C(1) <<  5),
  /// Lights Setting changed. High and low-bean status change share the same event
  VSTATE_ALERT_LIGHTSCHANGED             = (UINT32_C(1) <<  6),
  VSTATE_ALERT_HighBeamStatus            = VSTATE_ALERT_LIGHTSCHANGED,
  VSTATE_ALERT_LowBeamStatus             = VSTATE_ALERT_LIGHTSCHANGED,
  /// Wipers Setting changed. Front and rear wiper change share the same event
  VSTATE_ALERT_WIPERSCHANGED             = (UINT32_C(1) <<  7),
  VSTATE_ALERT_WiperSwRear               = VSTATE_ALERT_WIPERSCHANGED,
  VSTATE_ALERT_WiperSwFnt                = VSTATE_ALERT_WIPERSCHANGED,
  /// Flat Tyre detected. Tire pressure alerts share a common event
  VSTATE_ALERT_FLATTIRE                  = (UINT32_C(1) <<  8),
  VSTATE_ALERT_TirePressureRR            = VSTATE_ALERT_FLATTIRE,
  VSTATE_ALERT_TirePressureLR            = VSTATE_ALERT_FLATTIRE,
  VSTATE_ALERT_TirePressureRF            = VSTATE_ALERT_FLATTIRE,
  VSTATE_ALERT_TirePressureLF            = VSTATE_ALERT_FLATTIRE,
  /// Airbag deployed
  VSTATE_ALERT_AirbagStatus              = (UINT32_C(1) <<  9),

  /// Calculated heavy braking
  VSTATE_ALERT_HEAVYBRAKING              = (UINT32_C(1) << 10),

  // 11 and 12 used to be start/stop moving, combined into VehSpd
  /// Vehicle has started/stopped
  VSTATE_ALERT_VehSpd                    = (UINT32_C(1) << 11),
  VSTATE_ALERT_MOVING                    = VSTATE_ALERT_VehSpd,

  /// Left indicator
  VSTATE_ALERT_LftTurnSig                = (UINT32_C(1) << 13),
  /// Right indicator
  VSTATE_ALERT_RtTurnSig                 = (UINT32_C(1) << 13),
  /// Either/Both indicators
  VSTATE_ALERT_INDICATE                  = (VSTATE_ALERT_LftTurnSig |
                                            VSTATE_ALERT_RtTurnSig),
  /// Brake active (from ODB-II)
  VSTATE_ALERT_BrkAct                    = (UINT32_C(1) << 15),
  // Gear status change
  VSTATE_ALERT_PRNDL                     = (UINT32_C(1) << 16),
  // Cruise Control status changed
  VSTATE_ALERT_CrusEngd                  = (UINT32_C(1) << 17),
  // longitudinal acceleration (i.e. braking/accelerating)
  VSTATE_ALERT_LonAccel                  = (UINT32_C(1) << 18),

  // Door state change. All share the same event
  VSTATE_ALERT_DOOR                      = (UINT32_C(1) << 19),
  VSTATE_ALERT_DrvrDoor                  = VSTATE_ALERT_DOOR,
  VSTATE_ALERT_PsngrDoor                 = VSTATE_ALERT_DOOR,
  VSTATE_ALERT_RearDoor                  = VSTATE_ALERT_DOOR,
  /// CAN (or GPS) is reporting bad data
  /// Don't use separate events for bad CAN data... at least not yet
  VSTATE_ALERT_CAN_BAD                   = (UINT32_C(1) << 20),
  VSTATE_ALERT_CAN_GPS_BAD               = VSTATE_ALERT_CAN_BAD,
  // Automatic Braking
  VSTATE_ALERT_AUTOBRAKE                 = (UINT32_C(1) << 21),
  // Reversible Occupant Restraint System
  VSTATE_ALERT_RESTRAINT                 = (UINT32_C(1) << 22),
  // Autonomous Emergency Braking
  VSTATE_ALERT_AEBAct                    = (UINT32_C(1) << 23),

  /// OR this with the other flags to signal on-to-off transitions
  VSTATE_ALERT_ON_TO_OFF                 = (UINT32_C(1) << 31),

  // Old SHOUTY NAMES
  VSTATE_ALERT_AIRBAGDEPLOYMENT          = VSTATE_ALERT_AirbagStatus,
  VSTATE_ALERT_HARDBRAKING               = VSTATE_ALERT_PanicBrake,
  VSTATE_ALERT_STABILITYCONTROLACTIVATED = VSTATE_ALERT_StbCtrlAct,
  VSTATE_ALERT_TRACTIONCONTROLLOSS       = VSTATE_ALERT_TrcCtrlAct,
  VSTATE_ALERT_ABSACTIVATED              = VSTATE_ALERT_ABSAct,
  VSTATE_ALERT_HAZARDLIGHTS              = VSTATE_ALERT_HzdLgts,
  VSTATE_ALERT_RIGHT_INDICATE            = VSTATE_ALERT_RtTurnSig,
  VSTATE_ALERT_LEFT_INDICATE             = VSTATE_ALERT_LftTurnSig,
  VSTATE_ALERT_BRAKE_RELEASE             = VSTATE_ALERT_BrkAct,
  VSTATE_ALERT_START_MOVING              = VSTATE_ALERT_MOVING,
  VSTATE_ALERT_STOP_MOVING               = (VSTATE_ALERT_MOVING | VSTATE_ALERT_ON_TO_OFF),

} eVstateEventType;

/// VState event bitfield container
/// with bits @ref VstateEventType
typedef uint32_t tVstateEventType;

/// state machine states
typedef enum VStateEventState
{
  /// no data available
  unavailable,
  /// non-event
  available,
  /// available, not active, no event generated yet
  /// Level trigger that generatess an event when the level becomes low
  /// for @b timeOff
  ///                  |---timeOff---|Event|
  ///__________________
  ///                  |_______________________
  passive,
  /// available, not active, event generated.
  passiveEvt,
  /// available, active, no event generated yet
  /// Level trigger that generates an event when the level becomes high
  /// for @b timeOn
  ///                  |---timeOn---|Event|
  ///                   _______________________
  ///__________________|
  active,
  /// available, active, event generated
  activeEvt,
  /// available, changed, no event generated yet
  /// Edge trigger that generate an event when the level changes
  /// for @b timeOn
  ///                  |---timeOn---|Event|    |---timeOn---|Event|
  ///                   _______________________
  ///                  |                       |___________________
  ///__________________|
  delta,
  /// available, changed, event generated
  deltaEvt,
} eVStateEventState;

/// @ref VStateEventState
typedef uint16_t tVStateEventState;

// Metadata for something we store but which does not generate events
typedef struct VStateMetaData
{
  /// when the available flag was last set in normalised minute
  uint16_t LastUpdated;
  /// current state
  tVStateEventState State;
} tVStateMetaData;

/// data (including Metadata) which may generate events
typedef struct VStateData
{
  /// Metadata (state, timestamp)
  tVStateMetaData Meta;
  /// raw data
  int32_t Raw;
} tVStateData;

/// boolean data (including Metadata) which may generate events
typedef struct VStateBool
{
  tVStateMetaData Meta;
  bool Flag;
} tVStateBool;

/// Structure of New and Current events
/// This is also used by the EXT event @c QSMSG_EXT_VSTATE_EVENT
///
typedef struct VstateEvents
{
  /// New event
  tVstateEventType New;
  /// Current event
  tVstateEventType Current;
} tVstateEvents;

/// Vstate event configuration
typedef struct VstateEventCfg
{
  /// Value the signal must be above before the ON event is considered
  /// (unless ValueOn < ValueOff in which case the value must be below)
  int32_t  ValueOn;
  /// Value condition must be below before the OFF event is considered
  /// (unless ValueOn < ValueOff in which case the value must be above)
  int32_t  ValueOff;
  /// Time an event must be active before signaling off-to-on (0..65535 fractions of a minute)
  uint16_t TimeOn;
  /// Time an event must be passive before signaling on-to-off (0..65535 fractions of a minute)
  uint16_t TimeOff;
  /// Event to signal (VSTATE_ALERT_* or 0 to disable event generation)
  tVstateEventType Event;
} tVstateEventCfg;

/// Configs for all signals updated with VS_EVT_*() that generate @ref VstateEventType
typedef struct VstateEventCfgs
{
  /// Anonymous union of default values (Signals without VSTATE_ALERT_ or
  /// configurations in tdefault_stack_Cohda_VS)
  union
  {
    tVstateEventCfg Default;
    tVstateEventCfg CAN_GPS_BAD;
    tVstateEventCfg Slow;
    tVstateEventCfg DecelHard;
    tVstateEventCfg Swerving;
  };
  // Values we independently configure
  tVstateEventCfg HzdLgts;
  tVstateEventCfg ABSAct;
  tVstateEventCfg AEBAct;
  tVstateEventCfg TrcCtrlAct;
  tVstateEventCfg StbCtrlAct;
  tVstateEventCfg PanicBrake;
  tVstateEventCfg AutoBrake;
  tVstateEventCfg Restraint;
  /// VSTATE_ALERT_LIGHTSCHANGED
  union
  {
    tVstateEventCfg HighBeamStatus;
    tVstateEventCfg LowBeamStatus;
  };
  /// VSTATE_ALERT_WIPERSCHANGED
  union
  {
    tVstateEventCfg WiperSwRear;
    tVstateEventCfg WiperSwFnt;
  };
  /// VSTATE_ALERT_FLATTIRE
  union
  {
    tVstateEventCfg TirePressure;
    tVstateEventCfg TirePressureRR;
    tVstateEventCfg TirePressureLR;
    tVstateEventCfg TirePressureRF;
    tVstateEventCfg TirePressureLF;
  };
  tVstateEventCfg AirbagStatus;
  tVstateEventCfg VehSpd;
  tVstateEventCfg LftTurnSig;
  tVstateEventCfg RtTurnSig;
  tVstateEventCfg BrkAct;
  tVstateEventCfg PRNDL;
  tVstateEventCfg CrusEngd;
  tVstateEventCfg LonAccel;
  /// VSTATE_ALERT_DOOR
  union
  {
    tVstateEventCfg DrvrDoor;
    tVstateEventCfg PsngrDoor;
    tVstateEventCfg RearDoor;
  };
} tVstateEventCfgs;

/// Vehicle state data
struct VStateState
{
  /// Configuration
  struct
  {
    /// Raw parameters (as read from config file)
    tdefault_stack_Cohda_VS Param;
    // The rest below is derived for Param's contents
    /// Event configurations for VS_EVT_*()
    tVstateEventCfgs Evt;
  } Cfg;

  /// Current time (should be treated as read-only - this is updated by VState
  /// internally)
  uint16_t Now;

  /// Timestamp obtained from CAN-Event in microseconds
  uint64_t Timestamp_us;

  /// New and Current events
  tVstateEvents VstateEvents;
  // Antilock Brake System (ABS) status
  // (NOTE: 'On' means brake monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  tVStateData ABS; // ABSAct

  // Wheel Brakes Active (1=True; 0=False)
  tVStateBool BrkAct; // BrkAct

  // Parking Brake Status (AKA Auxiliary Brake)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Reserved
  tVStateData ParkingBrakeStatus;

  // Traction Control System Status
  // (NOTE: 'On' means traction monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  tVStateData TrcCtrl; // TrcCtrlAct

  // PRNDL
  // 0: Unknown
  // 1: Park
  // 2: Reverse
  // 3: Neutral
  // 4: OverDrive
  // 5: Drive
  // 6: Drive1
  // 7: Drive2
  // 8: Drive3
  // 9: Drive4
  // 10: Reserved0
  // 11: Reserved1
  // 12: Reserved2
  // 13: Reserved3
  // 14: Reserved4
  // 15: Reserved5
  tVStateData PRNDL; // PRNDL

  // Driver Intended Braking Level
  tVStateData DrvIntendedBrk;

  // Stability Control System Status (AKA ESP - Electronic Stability Program)
  // (NOTE: 'On' means stability monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  tVStateData StbCtrl; // StbCtrlAct

  // Weather
  // 0: Clear Dry
  // 1: Fog
  // 2: Snow
  // 3: Rain
  // 4: Reserved4 (may be donated to RoadType)
  // 5: Reserved5 (may be donated to RoadType)
  // 6: Reserved6 (may be donated to RoadType)
  // 7: Reserved7 (may be donated to RoadType)
  tVStateData Weather;

  // Road Type
  // 0: Unknown
  // 1: LocalRoad
  // 2: RegionalRoad
  // 3: Highway
  tVStateData RoadType;

  // Structural Separation Information
  // 0: Unknown
  // 1: None
  // 2: Structural
  tVStateData Separation;

  // E-Call Status (1=True; 0=False)
  tVStateBool EmergCallStatus;

  // Exterior Airbag Deployed (1=True; 0=False)
  tVStateBool ExtAirbagStatus;

  // Engine Shutdown Status (1=True; 0=False)
  tVStateBool AutoEngineShutdown;

  // Automatic Brake System status
  // (NOTE: 'On' means brake monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  // 4: Error
  tVStateData AutoBrake; // AutoBrake

  // Reversible Occupant Restraint System status
  // (NOTE: 'On' means RORS monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  // 4: Error
  tVStateData Restraint; // Restraint

  // Battery Voltage (0...31.75 volts, E = N * .25)
  tVStateData BattVolt;

  // Brake Pedal Gradient ([40, 0] [-5120, 5080] percent_per_s)
  tVStateData BrkPedalGrad;

  // Brake Pedal Position (0...255, E = N * 1)
  tVStateData BrkPedalPos;

  // Yaw Rate (-327.68...327.67 deg/s, E = N * .01)
  // (+'ve for right-hand turns)
  tVStateData YawRate;

  // Steering Wheel Angle Gradient ([1, 0] [-2048, 2047] deg_per_s)
  // Same sense as StrWhlAng, i.e.
  // +'ve means the wheel is being turned clockwise (e.g. tightening right-hand turn)
  tVStateData StrWhlAngGrad;

  // Steering Wheel Angle ([0.5, 0] [-1024, 1023.5] deg)
  // +'ve means the wheel has been turned clockwise (e.g. right-hand turn)
  tVStateData StrWhlAng;

  // Vehicle Speed (0...655.35 kph, E = N * .01)
  tVStateData VehSpd; // VehSpd

  // Vehicle Speed confidence cm/s
  // Data should be provided at 2-sigma confidence
  tVStateData VehSpdConf;

  // Lateral Acceleration in mm/s/s, +/- 100,000
  tVStateData LatAccel;

  // Panic Brake (AKA Emergency Brake Lights) active (1=True; 0=False)
  tVStateBool PanicBrake; // PanicBrake

  // Brake Pre-charge status (AKA Brake Boost)
  // 0: Unknown
  // 1: Off
  // 2: On
  tVStateData BrakePreChg;

  // Wiper Status Rear
  // see VSC3OBE_VSTATE_OBE2__WiperSwRear__*
  // 0: Off
  // 1: Delay 5
  // 2: Delay 4
  // 3: Delay 3
  // 4: Delay 2
  // 5: Delay 1
  // 6: Low
  // 7: High
  // 8: Auto
  // 9: Error
  tVStateData WiperSwRear; // WiperSwRear

  // Driver Airbag Deployed (1=True; 0=False)
  tVStateBool AirbagStatus; // AirbagStatus

  // High Beam Active (1=True; 0=False)
  tVStateBool HighBeamStatus; // HighBeamStatus

  // Wiper Sweep Active (1=True; 0=False)
  tVStateBool WiperSweepStatus;

  // Wiper Status Front
  // see VSC3OBE_VSTATE_OBE2__WiperSwFnt__*
  // 0: Off
  // 1: Delay 5
  // 2: Delay 4
  // 3: Delay 3
  // 4: Delay 2
  // 5: Delay 1
  // 6: Low
  // 7: High
  // 8: Auto
  // 9: Error
  tVStateData WiperSwFnt; // WiperSwFnt

  // Safety/Collision Warning Active (1=True; 0=False)
  tVStateBool SafetyWarningStatus;

  // Longitudinal Acceleration in mm/s/s, +/- 100,000
  tVStateData LonAccel; // LonAccel

  // Vertical Acceleration in mm/s/s, +/- 100,000
  tVStateData VertAccel;

  // Left Turn Signal (1=True; 0=False)
  tVStateBool LftTurnSig; // LftTurnSig

  // Right Turn Signal (1=True; 0=False)
  tVStateBool RtTurnSig; // RtTurnSig

  // Cruise Control Engaged (1=True; 0=False)
  tVStateBool CrusEngd; // CrusEngd

  // Cruise Control Override (1=True; 0=False)
  tVStateBool CrusOvrd;

  // Accelerator Pedal Position % (0...100%, E = N * 100.0/255)
  tVStateData AccelPos;

  // Vehicle Width in cm
  // EU: CDD supports up to 600 cm with 10 cm resolution (use 610 for larger widths)
  // NA: J2735 supports up to 1023 cm with 1 cm resolution
  tVStateData VehWidth;

  // Vehicle Length in cm
  // EU: CDD supports up to 10210 cm with 10 cm resolution (use 10220 for larger lengths)
  // NA: J2735 supports up to 4095 cm with 1 cm resolution
  tVStateData VehLength;

  // Low Beam Status (1=True; 0=False)
  tVStateBool LowBeamStatus; // LowBeamStatus

  // Hazard Lights (1=True; 0=False)
  tVStateBool HzdLgts; // HzdLgts

  // Auto Light Control On (1=True; 0=False)
  tVStateBool AutoLghtCntrlOn;

  // Daytime Running Lights On (1=True; 0=False)
  tVStateBool DtimeRunLghtsOn;

  // Front Fog Lights
  // 0: unknown
  // 1: unavailable
  // 2: error
  // 3: off
  // 4: automatic
  // 5: active
  // 6: driver
  tVStateData FogLightsFront;

  // Rear Fog Lights
  // 0: unknown
  // 1: unavailable
  // 2: error
  // 3: off
  // 4: automatic
  // 5: active
  // 6: driver
  tVStateData FogLightsRear;

  // Reversing Lights (usually automatically turned on in reverse gear).
  // 0: unknown
  // 1: unavailable
  // 2: error
  // 3: off
  // 4: automatic
  // 5: active
  // 6: driver
  tVStateData ReversingLights;

  // Parking Lights On (1=True; 0=False)
  tVStateBool PkgLghtsOn;

  // Cruise set speed (0...255 kph, E = N * 1)
  tVStateData CruiseSetSpeed;

  // Wheel Velocity LF
  tVStateData WheelVelocityLF;

  // Wheel Velocity RF
  tVStateData WheelVelocityRF;

  // Wheel Velocity LR
  tVStateData WheelVelocityLR;

  // Wheel Velocity RR
  tVStateData WheelVelocityRR;

  // Tire Pressure LF (0...255 psi, E = N * 1)
  tVStateData TirePressureLF; // TirePressureLF

  // Tire Pressure RF (0...255 psi, E = N * 1)
  tVStateData TirePressureRF; // TirePressureRF

  // Tire Pressure LR (0...255 psi, E = N * 1)
  tVStateData TirePressureLR; // TirePressureLR

  // Tire Pressure RR (0...255 psi, E = N * 1)
  tVStateData TirePressureRR; // TirePressureRR

  // Driver seatbelt status
  // 0: Unknown
  // 1: Latched
  // 2: Unlatched
  // 3: Empty
  tVStateData DrvrSeatbelt;

  // Front passenger seatbelt status
  // 0: Unknown
  // 1: Latched
  // 2: Unlatched
  // 3: Empty
  tVStateData PsngrSeatbelt;

  // Power mode
  // 0: Off
  // 1: Accessory
  // 2: Run
  // 3: Start Crank Request
  // 4: Engine Relay
  // 5: Reserved5
  // 6: Reserved6
  // 7: Reserved7
  tVStateData PwrMode;

  // Adaptive Cruise Control (ACC) status (1=ON 0=OFF)
  tVStateBool ACC;

  // Horn status (1=ON 0=OFF)
  tVStateBool Horn;

  // Driver door status
  // 0: Unknown
  // 1: Closed and locked
  // 2: Closed and unlocked
  // 3: Open
  tVStateData DrvrDoor; // DrvrDoor

  // Front Window Washer
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData WasherFront;

  // Front passenger door status
  // Same Values as DrvrDoor
  tVStateData PsngrDoor; // PsngrDoor

  // Rear passenger doors status
  // 0: Both closed (or unknown)
  // 1: Left open
  // 2: Right open
  // 3: Both open
  tVStateData RearDoor; // RearDoor

  // Hood/Bonnet Open (1=True; 0=False)
  tVStateBool Hood;

  // Trunk/Boot Open (1=True; 0=False)
  tVStateBool Trunk;

  // Outside Air Temperature (-40...87 deg C, E = N * 1 - 40)
  tVStateData OutAirTemp;

  // Wiper Rate Front (0...62, E = N * 2 (Sweeps per minute))
  tVStateData WiperRtFnt;

  // Wiper Rate Rear (0...62, E = N * 2 (Sweeps per minute))
  tVStateData WiperRtRear;

  // Speed Limiter Active
  tVStateBool SpdLimAct;

  // Odometer reading (0...4294967295 m, E = N * 1)
  tVStateData Odo;

  // Bumper Height Front (0...127 cm)
  tVStateData BmprHghtFnt;

  // Bumper Height Rear (0...127 cm)
  tVStateData BmprHghtRear;

  // Vehicle Height (0...635 cm, E = N * 5)
  tVStateData VehHght;

  // Vehicle Mass (Kg, E = N * 50)
  tVStateData VehMass;

  // Vehicle Type (Per SAE DE_VehicleType)
  // 0  none
  // 1  unknown
  // 2  special
  // 3  motorcycle
  // 4  car
  // 5  carOther
  // 6  bus
  // 7  axleCnt2
  // 8  axleCnt3
  // 9  axleCnt4
  // 10 axleCnt4Trailer
  // 11 axleCnt5Trailer
  // 12 axleCnt6Trailer
  // 13 axleCnt5MultiTrailer
  // 14 axleCnt6MultiTrailer
  // 15 axleCnt7MultiTrailer
  tVStateData VehType;

  // CAN GPS bad (i.e. disagrees with LPH)
  tVStateBool CAN_GPS_BAD;

  tVStateBool Slow;

  tVStateBool DecelHard;

  tVStateBool Swerving;

  // raw is scaled by 8 hence the resolution 1/8 degree
  tVStateData Slope_deg8;

  // Additional ETSI parameters not already handled in OBE messages
  // Lane Position
  // 'inside' means closest to centre line/central reservation, 
  // i.e. 1 is the 'fast' lane.
  // -2: unknown
  // -1: offTheRoad
  // 0: innerHardShoulder
  // 1: innermostDrivingLane
  // 2: secondLaneFromInside
  // 14: outerHardShoulder
  tVStateData LanePos;

  // Performance Class
  // (0 unavailable, 1 performanceClassA, 2 performanceClassB, ...)
  tVStateData PerfClass;

  // Yaw Rate Confidence (0...655.35 deg/s, E = N * .01)
  tVStateData YawRateConf;

  // Visible range in meters
  tVStateData VisibilityRange;

  // Light Bar in Use
  // (emergency/rescue vehicles only)
  // 0: Unavailable
  // 1: NotInUse
  // 2: InUse
  // 3: YellowCautionLights
  // 4: SchooldBusLights
  // 5: ArrowSignsActive
  // 6: SlowMovingVehicle
  // 7: FreqStops
  tVStateData LightBarInUse;

  // Siren In Use
  // (emergency vehicles only)
  // 0: Unavailable
  // 1: NotInUse
  // 2: InUse
  // 3: Reserved
  tVStateData SirenInUse;

  // Autonomous Emergency Braking (AEB) System status
  // (NOTE: 'On' means monitoring system is on but not engaged)
  // 0: Unknown
  // 1: Off
  // 2: On
  // 3: Engaged
  // 4: Error
  tVStateData AEB; // AEBAct

  // Which side of the road you drive on
  // https:  //en.wikipedia.org/wiki/Right-_and_left-hand_traffic
  // Left == AU, UK etc., Right == EU, US etc.
  // 0: Unknown
  // 1: Left
  // 2: Right
  tVStateData DrivingSide;

  // Local Road Environment
  // 0: Unavailable
  // 1: Unknown
  // 2: Rural
  // 3: Urban
  tVStateData Environment;

  // Engine Coolant Overheating
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData CoolantOverheat;

  // Electrical System Error
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData ElectricalSystemError;

  // Electrical System Overheat
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData ElectricalSystemOverheat;

  // Engine Oil Pressure Warning
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData EngineOilPressureWarning;

  // Hybrid System Error
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData HybridSystemError;

  // Steering Defect
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData SteeringDefect;

  // Transmission Overheat
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData TransmissionOverheat;

  // Low-Speed Accident
  // 0: unknown
  // 1: off
  // 2: active
  // 3: error
  tVStateData LowSpeedAccident;

  // Longitudinal Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
  tVStateData LonAccelConf;

  // Lateral Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
  tVStateData LatAccelConf;

  // Vertical Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
  tVStateData VertAccelConf;

  // Vehicle drive direction.
  // 0: unknown
  // 1: forward
  // 2: backward
  // 3: error
  tVStateData DriveDirection;



  // extra stuff

  struct
  {
    /// GPS heading in degrees
    float Heading;  // for yaw rate & lateral acceleration
    /// GPS altitude in meters
    float Altitude; // for fake vertical acceleration
    struct timeval Timestamp;
  } GPS;

  /// Vehicle layout:
  /// 0x0:not configured,
  /// 0x1:2WD - Front Driven,
  /// 0x2:2WD - Rear Driven,
  /// 0x3:4WD - 4 Wheel Drive,
  /// 0x4=AWD - All Wheel Drive
  uint8_t VehLayout;

  // GPS data from the CAN bus
  struct
  {
    /// Latitude as reported by CAN bus
    tVStateData Latitude_deg7;
    tVStateData Longitude_deg7;
    /// Heading [tHDU]
    tVStateData Heading;
    /// Speed [mmpnm]
    tVStateData Speed;
    /// Elevation [cm]
    tVStateData Elevation;
    /// Epoch [s]
    tVStateData Epoch;
  } CAN_GPS;

#ifdef UNITTEST
  float WhlAccel_mps2;
  float LonAccel_mps2;
#endif
};

// how long between updates before we invalidate a field
// make it two seconds (1/30'th of a minute).
#define VSTATE_MAX_AGE_PRNDL                 ((1<<16) / 30)
#define VSTATE_MAX_AGE_TrcCtrl               ((1<<16) / 30)
#define VSTATE_MAX_AGE_BrkAct                ((1<<16) / 30)
#define VSTATE_MAX_AGE_ABS                   ((1<<16) / 30)
#define VSTATE_MAX_AGE_StbCtrl               ((1<<16) / 30)
#define VSTATE_MAX_AGE_VehSpd                ({ const tdefault_stack * pIni = default_stack_Get(); const int Res = pIni->Cohda_VS.VehSpd_TIME_OLD; default_stack_Release(&pIni); Res; })
#define VSTATE_MAX_AGE_WiperSwRear           ((1<<16) / 30)
#define VSTATE_MAX_AGE_PanicBrake            ((1<<16) / 30)
#define VSTATE_MAX_AGE_WiperSwFnt            ((1<<16) / 30)
#define VSTATE_MAX_AGE_HighBeamStatus        ((1<<16) / 30)
#define VSTATE_MAX_AGE_AirbagStatus          ((1<<16) / 30)
#define VSTATE_MAX_AGE_HzdLgts               ((1<<16) / 30)
#define VSTATE_MAX_AGE_LowBeamStatus         ((1<<16) / 30)
#define VSTATE_MAX_AGE_CrusEngd              ((1<<16) / 30)
#define VSTATE_MAX_AGE_RtTurnSig             ((1<<16) / 30)
#define VSTATE_MAX_AGE_LftTurnSig            ((1<<16) / 30)
#define VSTATE_MAX_AGE_TirePressureRR        ((1<<16) / 30)
#define VSTATE_MAX_AGE_TirePressureLR        ((1<<16) / 30)
#define VSTATE_MAX_AGE_TirePressureRF        ((1<<16) / 30)
#define VSTATE_MAX_AGE_TirePressureLF        ((1<<16) / 30)
#define VSTATE_MAX_AGE_LonAccel              ((1<<16) / 30)
#define VSTATE_MAX_AGE_DoorOpenPsngr         ((1<<16) / 30)
#define VSTATE_MAX_AGE_DoorOpenDrvr          ((1<<16) / 30)
#define VSTATE_MAX_AGE_DoorOpenRearL         ((1<<16) / 30)
#define VSTATE_MAX_AGE_DoorOpenRearR         ((1<<16) / 30)
#define VSTATE_MAX_AGE_Slow                  ((1<<16) / 30)
#define VSTATE_MAX_AGE_DecelHard             ((1<<16) / 30)
#define VSTATE_MAX_AGE_Swerving              ((1<<16) / 30)
#define VSTATE_MAX_AGE_CAN_GPS_BAD           ((1<<16) / 30)

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void VS_PlausibilityCheck(tVStateState *pVState,
                          void *pLPH);

void VS_PurgeUnavailable(tVStateState *pVState);

/// Update the Metadata for non-event data
void VS_UpdateMeta(tVStateMetaData *pMeta, uint16_t Now);

void VS_Nag(void) ; // __attribute((deprecated)); // deprecate to find old uses

/// Helper macro for @ref VS_UpdateMeta for boolean data
#define VS_BOOL(s,b,f)                          \
  do                                            \
  {                                             \
    ((s)->b).Flag = f;                          \
    VS_UpdateMeta(&(((s)->b).Meta), (s)->Now);  \
    VS_Nag();                                   \
  } while(0)

/// Helper macro for @ref VS_UpdateMeta for non-boolean data
#define VS_DATA(s,d,v)                          \
  do                                            \
  {                                             \
    ((s)->d).Raw = v;                           \
    VS_UpdateMeta(&(((s)->d).Meta), (s)->Now);  \
    VS_Nag();                                   \
  } while(0)

/// update the Metadata and potentially generate events for boolean data
bool VS_UpdateEvtBool(tVStateBool *pBool,
                      uint16_t Now,
                      const tVstateEventCfg *pEvt,
                      const char *pTag);

#define VS_EVT_BOOL(s,b,f)                      \
  do                                            \
  {                                             \
    (s)->b.Flag = f;                            \
    VS_UpdateEvtBool(&((s)->b),                 \
                     (s)->Now,                  \
                     &((s)->Cfg.Evt.b),         \
                     #b);                       \
    VS_Nag();                                   \
  } while(0)


/// update the Metadata and potentially generate events for
/// non-boolean data for thresholded changes
bool VS_UpdateEvtData(tVStateData *pData,
                      uint16_t Now,
                      const tVstateEventCfg *pEvt,
                      const char *pTag);

#define VS_EVT_DATA(s,d,v)                      \
  do                                            \
  {                                             \
    bool Evt;                                   \
    (s)->d.Raw = v;                             \
    Evt =                                       \
    VS_UpdateEvtData(&((s)->d),                 \
                     (s)->Now,                  \
                     &((s)->Cfg.Evt.d),         \
                     #d);                       \
    VS_Nag();                                   \
    (void)Evt;                                  \
  } while(0)

/// update the Metadata and potentially generate events for
///  non-boolean data for any change
bool VS_UpdateEvtDelta(tVStateData *pData,
                       int32_t Raw,
                       uint16_t Now,
                       const tVstateEventCfg *pEvt,
                       const char *pTag);

#define VS_EVT_DELTA(s,d,v)                     \
  do                                            \
  {                                             \
    VS_UpdateEvtDelta(&((s)->d),                \
                      v,                        \
                      (s)->Now,                 \
                      &((s)->Cfg.Evt.d),        \
                      #d);                      \
    VS_Nag();                                   \
  } while(0)

#endif // __VSTATE_DATA_H_

/**
 * @brief Infinite-Inpulse response filter
 * @param In Input value
 * @param pPrev Previous input value
 * @param Gain Filter gain
 * @return Gain * In + ((1 - Gain) * *pPrev)
 *
 * This function applies the gain and updates the Prev value
 *
 */
static inline float VS_IIR(float In, float *pPrev, float Gain)
{
  // cache (1 - GAIN) ?
  float Out = (Gain * In) + ((1 - Gain) * *pPrev);
  *pPrev = Out;
  return Out;
}

#ifdef __cplusplus
}
#endif

// Close the doxygen group
/**
 * @}
 */
