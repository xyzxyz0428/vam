#pragma once
//-----------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __DBS2CH_GEN_VSC3OBE_H__
#define __DBS2CH_GEN_VSC3OBE_H__

#include <inttypes.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define GET_RAW(s)  (ntohll(s.Raw))

#define SET_RAW(s,r)   \
do                     \
{                      \
    s.Raw = ntohll(r); \
} while(0)

/// 0x600 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE1
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [1, 0] [0, 1]
        /// ABS Active
        uint16_t ABSAct:1;
        ///1
        /// [1, 0] [0, 1]
        /// Brakes Active
        uint16_t BrkAct:1;
        ///2
        /// [1, 0] [0, 1]
        /// Extended Brake Switch
        uint16_t ExtBrkSw:1;
        ///3
        /// [1, 0] [0, 1]
        /// Traction Control Active
        uint16_t TrcCtrlAct:1;
        ///4
        /// [1, 0] [0, 15]
        /// PRNDL
        uint16_t PRNDL:4;
        ///8
        /// [75, 0] [0, 19125] kpa
        /// Driver Intended Braking Level
        uint16_t DrvIntendedBrk:8;
        ///16
        /// [1, 0] [0, 1]
        /// Stability Control Active
        uint16_t StbCtrlAct:1;
        ///17
        /// [1, 0] [0, 7]
        /// Weather
        uint16_t Weather:3;
        ///20
        /// [1, 0] [0, 3]
        /// Road Type
        uint16_t RoadType:2;
        ///22
        /// [1, 0] [0, 1]
        /// E-Call Status
        uint16_t EmergCallStatus:1;
        ///23
        /// [1, 0] [0, 1]
        /// Exterior Airbag Status
        uint16_t ExtAirbagStatus:1;
        ///24
        /// [1, 0] [0, 1]
        /// Engine Shutdown Status
        uint16_t AutoEngineShutdown:1;
        ///25
        /// [0.25, 0] [0, 31.75] V
        /// Battery Voltage
        uint16_t BattVolt:7;
        ///32
        /// [40, 0] [-5120, 5080] percent_per_s
        /// Brake Pedal Gradient
        int16_t BrkPedalGrad:8;
        ///40
        /// [0.392156862745098, 0] [0, 100] percent
        /// Brake Pedal Position
        uint16_t BrkPedalPos:8;
        ///48
        /// [0.01, 0] [-327.68, 327.67] deg_per_s
        /// Yaw Rate
        int16_t YawRate:16;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///48
        /// [0.01, 0] [-327.68, 327.67] deg_per_s
        /// Yaw Rate
        int16_t YawRate:16;
        ///40
        /// [0.392156862745098, 0] [0, 100] percent
        /// Brake Pedal Position
        uint16_t BrkPedalPos:8;
        ///32
        /// [40, 0] [-5120, 5080] percent_per_s
        /// Brake Pedal Gradient
        int16_t BrkPedalGrad:8;
        ///25
        /// [0.25, 0] [0, 31.75] V
        /// Battery Voltage
        uint16_t BattVolt:7;
        ///24
        /// [1, 0] [0, 1]
        /// Engine Shutdown Status
        uint16_t AutoEngineShutdown:1;
        ///23
        /// [1, 0] [0, 1]
        /// Exterior Airbag Status
        uint16_t ExtAirbagStatus:1;
        ///22
        /// [1, 0] [0, 1]
        /// E-Call Status
        uint16_t EmergCallStatus:1;
        ///20
        /// [1, 0] [0, 3]
        /// Road Type
        uint16_t RoadType:2;
        ///17
        /// [1, 0] [0, 7]
        /// Weather
        uint16_t Weather:3;
        ///16
        /// [1, 0] [0, 1]
        /// Stability Control Active
        uint16_t StbCtrlAct:1;
        ///8
        /// [75, 0] [0, 19125] kpa
        /// Driver Intended Braking Level
        uint16_t DrvIntendedBrk:8;
        ///4
        /// [1, 0] [0, 15]
        /// PRNDL
        uint16_t PRNDL:4;
        ///3
        /// [1, 0] [0, 1]
        /// Traction Control Active
        uint16_t TrcCtrlAct:1;
        ///2
        /// [1, 0] [0, 1]
        /// Extended Brake Switch
        uint16_t ExtBrkSw:1;
        ///1
        /// [1, 0] [0, 1]
        /// Brakes Active
        uint16_t BrkAct:1;
        ///0
        /// [1, 0] [0, 1]
        /// ABS Active
        uint16_t ABSAct:1;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE1;

#define VSC3OBE_VSTATE_OBE1_NUM_ELEMENTS 16

#define VSC3OBE_VSTATE_OBE1_ID                0x600
#define VSC3OBE_VSTATE_OBE1_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE1(
 const tVSC3OBE_VSTATE_OBE1 * s);

#define VSC3OBE_VSTATE_OBE1_ABSAct_raw_TO_(r)                     (r)
#define VSC3OBE_VSTATE_OBE1_ABSAct__TO_raw(u)                     (u)
#define VSC3OBE_VSTATE_OBE1__ABSAct__False                        (0)
#define VSC3OBE_VSTATE_OBE1__ABSAct__True                         (1)
#define VSC3OBE_VSTATE_OBE1_BrkAct_raw_TO_(r)                     (r)
#define VSC3OBE_VSTATE_OBE1_BrkAct__TO_raw(u)                     (u)
#define VSC3OBE_VSTATE_OBE1__BrkAct__False                        (0)
#define VSC3OBE_VSTATE_OBE1__BrkAct__True                         (1)
#define VSC3OBE_VSTATE_OBE1_ExtBrkSw_raw_TO_(r)                   (r)
#define VSC3OBE_VSTATE_OBE1_ExtBrkSw__TO_raw(u)                   (u)
#define VSC3OBE_VSTATE_OBE1__ExtBrkSw__False                      (0)
#define VSC3OBE_VSTATE_OBE1__ExtBrkSw__True                       (1)
#define VSC3OBE_VSTATE_OBE1_TrcCtrlAct_raw_TO_(r)                 (r)
#define VSC3OBE_VSTATE_OBE1_TrcCtrlAct__TO_raw(u)                 (u)
#define VSC3OBE_VSTATE_OBE1__TrcCtrlAct__False                    (0)
#define VSC3OBE_VSTATE_OBE1__TrcCtrlAct__True                     (1)
#define VSC3OBE_VSTATE_OBE1_PRNDL_raw_TO_(r)                      (r)
#define VSC3OBE_VSTATE_OBE1_PRNDL__TO_raw(u)                      (u)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Unknown                       (0)
#define VSC3OBE_VSTATE_OBE1__PRNDL__P__Park_                      (1)
#define VSC3OBE_VSTATE_OBE1__PRNDL__R__Reverse_                   (2)
#define VSC3OBE_VSTATE_OBE1__PRNDL__N__Neutral_                   (3)
#define VSC3OBE_VSTATE_OBE1__PRNDL__OD__Overdrive_                (4)
#define VSC3OBE_VSTATE_OBE1__PRNDL__D__Drive_                     (5)
#define VSC3OBE_VSTATE_OBE1__PRNDL__D1                            (6)
#define VSC3OBE_VSTATE_OBE1__PRNDL__D2                            (7)
#define VSC3OBE_VSTATE_OBE1__PRNDL__D3                            (8)
#define VSC3OBE_VSTATE_OBE1__PRNDL__D4                            (9)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved                      (10)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved_11                   (11)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved_12                   (12)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved_13                   (13)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved_14                   (14)
#define VSC3OBE_VSTATE_OBE1__PRNDL__Reserved_15                   (15)
#define VSC3OBE_VSTATE_OBE1_DrvIntendedBrk_raw_TO_kpa(r)          ((r) * 75)
#define VSC3OBE_VSTATE_OBE1_DrvIntendedBrk_kpa_TO_raw(u)          ((u) / 75)
#define VSC3OBE_VSTATE_OBE1_StbCtrlAct_raw_TO_(r)                 (r)
#define VSC3OBE_VSTATE_OBE1_StbCtrlAct__TO_raw(u)                 (u)
#define VSC3OBE_VSTATE_OBE1__StbCtrlAct__False                    (0)
#define VSC3OBE_VSTATE_OBE1__StbCtrlAct__True                     (1)
#define VSC3OBE_VSTATE_OBE1_Weather_raw_TO_(r)                    (r)
#define VSC3OBE_VSTATE_OBE1_Weather__TO_raw(u)                    (u)
#define VSC3OBE_VSTATE_OBE1__Weather__Clear_Dry                   (0)
#define VSC3OBE_VSTATE_OBE1__Weather__Fog                         (1)
#define VSC3OBE_VSTATE_OBE1__Weather__Snow                        (2)
#define VSC3OBE_VSTATE_OBE1__Weather__Rain                        (3)
#define VSC3OBE_VSTATE_OBE1__Weather__Reserved                    (4)
#define VSC3OBE_VSTATE_OBE1__Weather__Reserved_5                  (5)
#define VSC3OBE_VSTATE_OBE1__Weather__Reserved_6                  (6)
#define VSC3OBE_VSTATE_OBE1__Weather__Reserved_7                  (7)
#define VSC3OBE_VSTATE_OBE1_RoadType_raw_TO_(r)                   (r)
#define VSC3OBE_VSTATE_OBE1_RoadType__TO_raw(u)                   (u)
#define VSC3OBE_VSTATE_OBE1__RoadType__Unknown                    (0)
#define VSC3OBE_VSTATE_OBE1__RoadType__LocalRoad                  (1)
#define VSC3OBE_VSTATE_OBE1__RoadType__RegionalRoad               (2)
#define VSC3OBE_VSTATE_OBE1__RoadType__Highway                    (3)
#define VSC3OBE_VSTATE_OBE1_EmergCallStatus_raw_TO_(r)            (r)
#define VSC3OBE_VSTATE_OBE1_EmergCallStatus__TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE1__EmergCallStatus__Call_inactive       (0)
#define VSC3OBE_VSTATE_OBE1__EmergCallStatus__Call_active         (1)
#define VSC3OBE_VSTATE_OBE1_ExtAirbagStatus_raw_TO_(r)            (r)
#define VSC3OBE_VSTATE_OBE1_ExtAirbagStatus__TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE1_AutoEngineShutdown_raw_TO_(r)         (r)
#define VSC3OBE_VSTATE_OBE1_AutoEngineShutdown__TO_raw(u)         (u)
#define VSC3OBE_VSTATE_OBE1_BattVolt_raw_TO_V(r)                  ((r) / 4)
#define VSC3OBE_VSTATE_OBE1_BattVolt_V_TO_raw(u)                  ((u) * 4)
#define VSC3OBE_VSTATE_OBE1_BrkPedalGrad_raw_TO_percent_per_s(r)  ((r) * 40)
#define VSC3OBE_VSTATE_OBE1_BrkPedalGrad_percent_per_s_TO_raw(u)  ((u) / 40)
#define VSC3OBE_VSTATE_OBE1_BrkPedalPos_raw_TO_percent(r)         ((r) * 0.392156862745098)
#define VSC3OBE_VSTATE_OBE1_BrkPedalPos_percent_TO_raw(u)         ((u) / 0.392156862745098)
#define VSC3OBE_VSTATE_OBE1_YawRate_raw_TO_deg_per_s(r)           ((r) / 100)
#define VSC3OBE_VSTATE_OBE1_YawRate_deg_per_s_TO_raw(u)           ((u) * 100)

/// 0x601 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE2
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [1, 0] [-2048, 2047] deg_per_s
        /// Steering Wheel Angle Gradient
        int16_t StrWhlAngGrad:12;
        ///12
        /// [0.5, 0] [-1024, 1023.5] deg
        /// Steering Wheel Angle
        int16_t StrWhlAng:12;
        ///24
        /// [0.01, 0] [0, 655.35] kph
        /// Vehicle Speed
        uint16_t VehSpd:16;
        ///40
        /// [0.0194, -9.9] [-9.9, 9.9462] m_per_s_per_s
        /// Lateral Acceleration
        uint16_t LatAccel:10;
        ///50
        /// [1, 0] [0, 1]
        /// Panic brake active
        uint16_t PanicBrake:1;
        ///51
        /// [1, 0] [0, 1]
        /// Pre charge status
        uint16_t BrakePreChg:1;
        uint64_t pad_53:1;
        ///53
        /// [1, 0] [0, 7]
        /// Wiper Status Rear
        uint16_t WiperSwRear:3;
        ///56
        /// [1, 0] [0, 1]
        /// AEB Active
        uint16_t AEBAct:1;
        ///57
        /// [1, 0] [0, 1]
        /// Airbag Status
        uint16_t AirbagStatus:1;
        ///58
        /// [1, 0] [0, 1]
        /// High Beam Status
        uint16_t HighBeamStatus:1;
        ///59
        /// [1, 0] [0, 1]
        /// Wiper Sweep Status
        uint16_t WiperSweepStatus:1;
        ///60
        /// [1, 0] [0, 7]
        /// Wiper Status Front
        uint16_t WiperSwFnt:3;
        ///63
        /// [1, 0] [0, 1]
        /// Safety Warning Status
        uint16_t SafetyWarningStatus:1;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///63
        /// [1, 0] [0, 1]
        /// Safety Warning Status
        uint16_t SafetyWarningStatus:1;
        ///60
        /// [1, 0] [0, 7]
        /// Wiper Status Front
        uint16_t WiperSwFnt:3;
        ///59
        /// [1, 0] [0, 1]
        /// Wiper Sweep Status
        uint16_t WiperSweepStatus:1;
        ///58
        /// [1, 0] [0, 1]
        /// High Beam Status
        uint16_t HighBeamStatus:1;
        ///57
        /// [1, 0] [0, 1]
        /// Airbag Status
        uint16_t AirbagStatus:1;
        ///56
        /// [1, 0] [0, 1]
        /// AEB Active
        uint16_t AEBAct:1;
        ///53
        /// [1, 0] [0, 7]
        /// Wiper Status Rear
        uint16_t WiperSwRear:3;
        uint64_t pad_51:1;
        ///51
        /// [1, 0] [0, 1]
        /// Pre charge status
        uint16_t BrakePreChg:1;
        ///50
        /// [1, 0] [0, 1]
        /// Panic brake active
        uint16_t PanicBrake:1;
        ///40
        /// [0.0194, -9.9] [-9.9, 9.9462] m_per_s_per_s
        /// Lateral Acceleration
        uint16_t LatAccel:10;
        ///24
        /// [0.01, 0] [0, 655.35] kph
        /// Vehicle Speed
        uint16_t VehSpd:16;
        ///12
        /// [0.5, 0] [-1024, 1023.5] deg
        /// Steering Wheel Angle
        int16_t StrWhlAng:12;
        ///0
        /// [1, 0] [-2048, 2047] deg_per_s
        /// Steering Wheel Angle Gradient
        int16_t StrWhlAngGrad:12;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE2;

#define VSC3OBE_VSTATE_OBE2_NUM_ELEMENTS 13

#define VSC3OBE_VSTATE_OBE2_ID                0x601
#define VSC3OBE_VSTATE_OBE2_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE2(
 const tVSC3OBE_VSTATE_OBE2 * s);

#define VSC3OBE_VSTATE_OBE2_StrWhlAngGrad_raw_TO_deg_per_s(r)  (r)
#define VSC3OBE_VSTATE_OBE2_StrWhlAngGrad_deg_per_s_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE2_StrWhlAng_raw_TO_deg(r)            ((r) / 2)
#define VSC3OBE_VSTATE_OBE2_StrWhlAng_deg_TO_raw(u)            ((u) * 2)
#define VSC3OBE_VSTATE_OBE2_VehSpd_raw_TO_kph(r)               ((r) / 100)
#define VSC3OBE_VSTATE_OBE2_VehSpd_kph_TO_raw(u)               ((u) * 100)
#define VSC3OBE_VSTATE_OBE2_LatAccel_raw_TO_m_per_s_per_s(r)   (((r) * 0.0194) - 9.9)
#define VSC3OBE_VSTATE_OBE2_LatAccel_m_per_s_per_s_TO_raw(u)   (((u) + 9.9) / 0.0194)
#define VSC3OBE_VSTATE_OBE2_PanicBrake_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE2_PanicBrake__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE2__PanicBrake__False                 (0)
#define VSC3OBE_VSTATE_OBE2__PanicBrake__True                  (1)
#define VSC3OBE_VSTATE_OBE2_BrakePreChg_raw_TO_(r)             (r)
#define VSC3OBE_VSTATE_OBE2_BrakePreChg__TO_raw(u)             (u)
#define VSC3OBE_VSTATE_OBE2__BrakePreChg__False                (0)
#define VSC3OBE_VSTATE_OBE2__BrakePreChg__True                 (1)
#define VSC3OBE_VSTATE_OBE2_WiperSwRear_raw_TO_(r)             (r)
#define VSC3OBE_VSTATE_OBE2_WiperSwRear__TO_raw(u)             (u)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Off                  (0)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Auto                 (1)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Delay4               (2)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Delay3               (3)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Delay2               (4)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Delay1               (5)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__Low                  (6)
#define VSC3OBE_VSTATE_OBE2__WiperSwRear__High                 (7)
#define VSC3OBE_VSTATE_OBE2_AEBAct_raw_TO_(r)                  (r)
#define VSC3OBE_VSTATE_OBE2_AEBAct__TO_raw(u)                  (u)
#define VSC3OBE_VSTATE_OBE2__AEBAct__False                     (0)
#define VSC3OBE_VSTATE_OBE2__AEBAct__True                      (1)
#define VSC3OBE_VSTATE_OBE2_AirbagStatus_raw_TO_(r)            (r)
#define VSC3OBE_VSTATE_OBE2_AirbagStatus__TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE2__AirbagStatus__False               (0)
#define VSC3OBE_VSTATE_OBE2__AirbagStatus__True                (1)
#define VSC3OBE_VSTATE_OBE2_HighBeamStatus_raw_TO_(r)          (r)
#define VSC3OBE_VSTATE_OBE2_HighBeamStatus__TO_raw(u)          (u)
#define VSC3OBE_VSTATE_OBE2__HighBeamStatus__False             (0)
#define VSC3OBE_VSTATE_OBE2__HighBeamStatus__True              (1)
#define VSC3OBE_VSTATE_OBE2_WiperSweepStatus_raw_TO_(r)        (r)
#define VSC3OBE_VSTATE_OBE2_WiperSweepStatus__TO_raw(u)        (u)
#define VSC3OBE_VSTATE_OBE2__WiperSweepStatus__False           (0)
#define VSC3OBE_VSTATE_OBE2__WiperSweepStatus__True            (1)
#define VSC3OBE_VSTATE_OBE2_WiperSwFnt_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE2_WiperSwFnt__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Off                   (0)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Auto                  (1)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Delay4                (2)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Delay3                (3)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Delay2                (4)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Delay1                (5)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__Low                   (6)
#define VSC3OBE_VSTATE_OBE2__WiperSwFnt__High                  (7)
#define VSC3OBE_VSTATE_OBE2_SafetyWarningStatus_raw_TO_(r)     (r)
#define VSC3OBE_VSTATE_OBE2_SafetyWarningStatus__TO_raw(u)     (u)
#define VSC3OBE_VSTATE_OBE2__SafetyWarningStatus__False        (0)
#define VSC3OBE_VSTATE_OBE2__SafetyWarningStatus__True         (1)

/// 0x602 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE3
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [0.0194, -9.9] [-9.9, 9.9462] m_per_s_per_s
        /// Longitudinal Acceleration
        uint16_t LonAccel:10;
        ///10
        /// [0.0194, -19.7] [-19.7, 0.1462] m_per_s_per_s
        /// Vertical Acceleration
        uint16_t VertAccel:10;
        ///20
        /// [1, 0] [0, 1]
        /// Left Turn Signal
        uint16_t LftTurnSig:1;
        ///21
        /// [1, 0] [0, 1]
        /// Right Turn Signal
        uint16_t RtTurnSig:1;
        ///22
        /// [1, 0] [0, 1]
        /// Cruise Engaged
        uint16_t CrusEngd:1;
        ///23
        /// [1, 0] [0, 1]
        /// Cruise Override
        uint16_t CrusOvrd:1;
        ///24
        /// [0.392156862745098, 0] [0, 100] percent
        /// Accelerator Pedal Position %
        uint16_t AccelPos:8;
        uint64_t pad_50:18;
        ///50
        /// [1, 0] [0, 1]
        /// Low Beam Status
        uint16_t LowBeamStatus:1;
        ///51
        /// [1, 0] [0, 1]
        /// Hazard Lights
        uint16_t HzdLgts:1;
        ///52
        /// [1, 0] [0, 1]
        /// Auto Light Control On
        uint16_t AutoLghtCntrlOn:1;
        ///53
        /// [1, 0] [0, 1]
        /// Daytime Running Lights On
        uint16_t DtimeRunLghtsOn:1;
        ///54
        /// [1, 0] [0, 1]
        /// Fog Lights On
        uint16_t FogLghtsOn:1;
        ///55
        /// [1, 0] [0, 1]
        /// Parking Lights On
        uint16_t PkgLghtsOn:1;
        ///56
        /// [1, 0] [0, 255] kph
        /// Cruise Set Speed
        uint16_t CruiseSetSpeed:8;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///56
        /// [1, 0] [0, 255] kph
        /// Cruise Set Speed
        uint16_t CruiseSetSpeed:8;
        ///55
        /// [1, 0] [0, 1]
        /// Parking Lights On
        uint16_t PkgLghtsOn:1;
        ///54
        /// [1, 0] [0, 1]
        /// Fog Lights On
        uint16_t FogLghtsOn:1;
        ///53
        /// [1, 0] [0, 1]
        /// Daytime Running Lights On
        uint16_t DtimeRunLghtsOn:1;
        ///52
        /// [1, 0] [0, 1]
        /// Auto Light Control On
        uint16_t AutoLghtCntrlOn:1;
        ///51
        /// [1, 0] [0, 1]
        /// Hazard Lights
        uint16_t HzdLgts:1;
        ///50
        /// [1, 0] [0, 1]
        /// Low Beam Status
        uint16_t LowBeamStatus:1;
        uint64_t pad_24:18;
        ///24
        /// [0.392156862745098, 0] [0, 100] percent
        /// Accelerator Pedal Position %
        uint16_t AccelPos:8;
        ///23
        /// [1, 0] [0, 1]
        /// Cruise Override
        uint16_t CrusOvrd:1;
        ///22
        /// [1, 0] [0, 1]
        /// Cruise Engaged
        uint16_t CrusEngd:1;
        ///21
        /// [1, 0] [0, 1]
        /// Right Turn Signal
        uint16_t RtTurnSig:1;
        ///20
        /// [1, 0] [0, 1]
        /// Left Turn Signal
        uint16_t LftTurnSig:1;
        ///10
        /// [0.0194, -19.7] [-19.7, 0.1462] m_per_s_per_s
        /// Vertical Acceleration
        uint16_t VertAccel:10;
        ///0
        /// [0.0194, -9.9] [-9.9, 9.9462] m_per_s_per_s
        /// Longitudinal Acceleration
        uint16_t LonAccel:10;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE3;

#define VSC3OBE_VSTATE_OBE3_NUM_ELEMENTS 14

#define VSC3OBE_VSTATE_OBE3_ID                0x602
#define VSC3OBE_VSTATE_OBE3_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE3(
 const tVSC3OBE_VSTATE_OBE3 * s);

#define VSC3OBE_VSTATE_OBE3_LonAccel_raw_TO_m_per_s_per_s(r)   (((r) * 0.0194) - 9.9)
#define VSC3OBE_VSTATE_OBE3_LonAccel_m_per_s_per_s_TO_raw(u)   (((u) + 9.9) / 0.0194)
#define VSC3OBE_VSTATE_OBE3_VertAccel_raw_TO_m_per_s_per_s(r)  (((r) * 0.0194) - 19.7)
#define VSC3OBE_VSTATE_OBE3_VertAccel_m_per_s_per_s_TO_raw(u)  (((u) + 19.7) / 0.0194)
#define VSC3OBE_VSTATE_OBE3_LftTurnSig_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE3_LftTurnSig__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE3__LftTurnSig__False                 (0)
#define VSC3OBE_VSTATE_OBE3__LftTurnSig__True                  (1)
#define VSC3OBE_VSTATE_OBE3_RtTurnSig_raw_TO_(r)               (r)
#define VSC3OBE_VSTATE_OBE3_RtTurnSig__TO_raw(u)               (u)
#define VSC3OBE_VSTATE_OBE3__RtTurnSig__False                  (0)
#define VSC3OBE_VSTATE_OBE3__RtTurnSig__True                   (1)
#define VSC3OBE_VSTATE_OBE3_CrusEngd_raw_TO_(r)                (r)
#define VSC3OBE_VSTATE_OBE3_CrusEngd__TO_raw(u)                (u)
#define VSC3OBE_VSTATE_OBE3__CrusEngd__False                   (0)
#define VSC3OBE_VSTATE_OBE3__CrusEngd__True                    (1)
#define VSC3OBE_VSTATE_OBE3_CrusOvrd_raw_TO_(r)                (r)
#define VSC3OBE_VSTATE_OBE3_CrusOvrd__TO_raw(u)                (u)
#define VSC3OBE_VSTATE_OBE3__CrusOvrd__False                   (0)
#define VSC3OBE_VSTATE_OBE3__CrusOvrd__True                    (1)
#define VSC3OBE_VSTATE_OBE3_AccelPos_raw_TO_percent(r)         ((r) * 0.392156862745098)
#define VSC3OBE_VSTATE_OBE3_AccelPos_percent_TO_raw(u)         ((u) / 0.392156862745098)
#define VSC3OBE_VSTATE_OBE3_LowBeamStatus_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE3_LowBeamStatus__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE3__LowBeamStatus__False              (0)
#define VSC3OBE_VSTATE_OBE3__LowBeamStatus__True               (1)
#define VSC3OBE_VSTATE_OBE3_HzdLgts_raw_TO_(r)                 (r)
#define VSC3OBE_VSTATE_OBE3_HzdLgts__TO_raw(u)                 (u)
#define VSC3OBE_VSTATE_OBE3__HzdLgts__False                    (0)
#define VSC3OBE_VSTATE_OBE3__HzdLgts__True                     (1)
#define VSC3OBE_VSTATE_OBE3_AutoLghtCntrlOn_raw_TO_(r)         (r)
#define VSC3OBE_VSTATE_OBE3_AutoLghtCntrlOn__TO_raw(u)         (u)
#define VSC3OBE_VSTATE_OBE3__AutoLghtCntrlOn__False            (0)
#define VSC3OBE_VSTATE_OBE3__AutoLghtCntrlOn__True             (1)
#define VSC3OBE_VSTATE_OBE3_DtimeRunLghtsOn_raw_TO_(r)         (r)
#define VSC3OBE_VSTATE_OBE3_DtimeRunLghtsOn__TO_raw(u)         (u)
#define VSC3OBE_VSTATE_OBE3__DtimeRunLghtsOn__False            (0)
#define VSC3OBE_VSTATE_OBE3__DtimeRunLghtsOn__True             (1)
#define VSC3OBE_VSTATE_OBE3_FogLghtsOn_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE3_FogLghtsOn__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE3__FogLghtsOn__False                 (0)
#define VSC3OBE_VSTATE_OBE3__FogLghtsOn__True                  (1)
#define VSC3OBE_VSTATE_OBE3_PkgLghtsOn_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE3_PkgLghtsOn__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE3__PkgLghtsOn__False                 (0)
#define VSC3OBE_VSTATE_OBE3__PkgLghtsOn__True                  (1)
#define VSC3OBE_VSTATE_OBE3_CruiseSetSpeed_raw_TO_kph(r)       (r)
#define VSC3OBE_VSTATE_OBE3_CruiseSetSpeed_kph_TO_raw(u)       (u)

/// 0x603 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE4
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Left Front
        int16_t WheelVelocityLF:16;
        ///16
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Right Front
        int16_t WheelVelocityRF:16;
        ///32
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Left Rear
        int16_t WheelVelocityLR:16;
        ///48
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Right Rear
        int16_t WheelVelocityRR:16;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///48
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Right Rear
        int16_t WheelVelocityRR:16;
        ///32
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Left Rear
        int16_t WheelVelocityLR:16;
        ///16
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Right Front
        int16_t WheelVelocityRF:16;
        ///0
        /// [0.015, 0] [-491.52, 491.505] kph
        /// Wheel Velocity Left Front
        int16_t WheelVelocityLF:16;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE4;

#define VSC3OBE_VSTATE_OBE4_NUM_ELEMENTS 4

#define VSC3OBE_VSTATE_OBE4_ID                0x603
#define VSC3OBE_VSTATE_OBE4_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE4(
 const tVSC3OBE_VSTATE_OBE4 * s);

#define VSC3OBE_VSTATE_OBE4_WheelVelocityLF_raw_TO_kph(r)  ((r) * 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityLF_kph_TO_raw(u)  ((u) / 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityRF_raw_TO_kph(r)  ((r) * 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityRF_kph_TO_raw(u)  ((u) / 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityLR_raw_TO_kph(r)  ((r) * 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityLR_kph_TO_raw(u)  ((u) / 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityRR_raw_TO_kph(r)  ((r) * 0.015)
#define VSC3OBE_VSTATE_OBE4_WheelVelocityRR_kph_TO_raw(u)  ((u) / 0.015)

/// 0x604 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE5
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Left Front
        uint16_t TirePressureLF:8;
        ///8
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Right Front
        uint16_t TirePressureRF:8;
        ///16
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Left Rear
        uint16_t TirePressureLR:8;
        ///24
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Right Rear
        uint16_t TirePressureRR:8;
        ///32
        /// [1, 0] [0, 3]
        /// Driver seatbelt status
        uint16_t DrvrSeatbelt:2;
        ///34
        /// [1, 0] [0, 3]
        /// Front passenger seatbelt status
        uint16_t PsngrSeatbelt:2;
        ///36
        /// [1, 0] [0, 0]
        /// Siren Active
        uint16_t SirenAct:1;
        ///37
        /// [1, 0] [0, 0]
        /// Light Bar Active
        uint16_t LightBarAct:1;
        ///38
        /// [1, 0] [0, 1]
        /// ACC Status
        uint16_t ACC:1;
        ///39
        /// [1, 0] [0, 1]
        /// Horn Status
        uint16_t Horn:1;
        ///40
        /// [1, 0] [0, 3]
        /// Driver door status
        uint16_t DrvrDoor:2;
        ///42
        /// [1, 0] [0, 3]
        /// Front passenger door status
        uint16_t PsngrDoor:2;
        ///44
        /// [1, 0] [0, 3]
        /// Rear passenger doors status
        uint16_t RearDoor:2;
        ///46
        /// [1, 0] [0, 1]
        /// Hood Status
        uint16_t Hood:1;
        ///47
        /// [1, 0] [0, 1]
        /// Trunk Status
        uint16_t Trunk:1;
        ///48
        /// [1, 0] [0, 1]
        /// Speed Limiter Active
        uint16_t SpdLimAct:1;
        ///49
        /// [1, -40] [-40, 87] de
        /// Outside Air Temperature
        uint16_t OutAirTemp:7;
        ///56
        /// [2, 0] [0, 62] Sweep
        /// Wiper Rate Front
        uint16_t WiperRtFnt:5;
        ///61
        /// [1, 0] [0, 7]
        /// Power mode
        uint16_t PwrMode:3;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///61
        /// [1, 0] [0, 7]
        /// Power mode
        uint16_t PwrMode:3;
        ///56
        /// [2, 0] [0, 62] Sweep
        /// Wiper Rate Front
        uint16_t WiperRtFnt:5;
        ///49
        /// [1, -40] [-40, 87] de
        /// Outside Air Temperature
        uint16_t OutAirTemp:7;
        ///48
        /// [1, 0] [0, 1]
        /// Speed Limiter Active
        uint16_t SpdLimAct:1;
        ///47
        /// [1, 0] [0, 1]
        /// Trunk Status
        uint16_t Trunk:1;
        ///46
        /// [1, 0] [0, 1]
        /// Hood Status
        uint16_t Hood:1;
        ///44
        /// [1, 0] [0, 3]
        /// Rear passenger doors status
        uint16_t RearDoor:2;
        ///42
        /// [1, 0] [0, 3]
        /// Front passenger door status
        uint16_t PsngrDoor:2;
        ///40
        /// [1, 0] [0, 3]
        /// Driver door status
        uint16_t DrvrDoor:2;
        ///39
        /// [1, 0] [0, 1]
        /// Horn Status
        uint16_t Horn:1;
        ///38
        /// [1, 0] [0, 1]
        /// ACC Status
        uint16_t ACC:1;
        ///37
        /// [1, 0] [0, 0]
        /// Light Bar Active
        uint16_t LightBarAct:1;
        ///36
        /// [1, 0] [0, 0]
        /// Siren Active
        uint16_t SirenAct:1;
        ///34
        /// [1, 0] [0, 3]
        /// Front passenger seatbelt status
        uint16_t PsngrSeatbelt:2;
        ///32
        /// [1, 0] [0, 3]
        /// Driver seatbelt status
        uint16_t DrvrSeatbelt:2;
        ///24
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Right Rear
        uint16_t TirePressureRR:8;
        ///16
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Left Rear
        uint16_t TirePressureLR:8;
        ///8
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Right Front
        uint16_t TirePressureRF:8;
        ///0
        /// [1, 0] [0, 255] psi
        /// Tire Pressure Left Front
        uint16_t TirePressureLF:8;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE5;

#define VSC3OBE_VSTATE_OBE5_NUM_ELEMENTS 19

#define VSC3OBE_VSTATE_OBE5_ID                0x604
#define VSC3OBE_VSTATE_OBE5_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE5(
 const tVSC3OBE_VSTATE_OBE5 * s);

#define VSC3OBE_VSTATE_OBE5_TirePressureLF_raw_TO_psi(r)  (r)
#define VSC3OBE_VSTATE_OBE5_TirePressureLF_psi_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE5_TirePressureRF_raw_TO_psi(r)  (r)
#define VSC3OBE_VSTATE_OBE5_TirePressureRF_psi_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE5_TirePressureLR_raw_TO_psi(r)  (r)
#define VSC3OBE_VSTATE_OBE5_TirePressureLR_psi_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE5_TirePressureRR_raw_TO_psi(r)  (r)
#define VSC3OBE_VSTATE_OBE5_TirePressureRR_psi_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE5_DrvrSeatbelt_raw_TO_(r)       (r)
#define VSC3OBE_VSTATE_OBE5_DrvrSeatbelt__TO_raw(u)       (u)
#define VSC3OBE_VSTATE_OBE5__DrvrSeatbelt__Unknown        (0)
#define VSC3OBE_VSTATE_OBE5__DrvrSeatbelt__Latched        (1)
#define VSC3OBE_VSTATE_OBE5__DrvrSeatbelt__Unlatched      (2)
#define VSC3OBE_VSTATE_OBE5__DrvrSeatbelt__Empty          (3)
#define VSC3OBE_VSTATE_OBE5_PsngrSeatbelt_raw_TO_(r)      (r)
#define VSC3OBE_VSTATE_OBE5_PsngrSeatbelt__TO_raw(u)      (u)
#define VSC3OBE_VSTATE_OBE5__PsngrSeatbelt__Unknown       (0)
#define VSC3OBE_VSTATE_OBE5__PsngrSeatbelt__Latched       (1)
#define VSC3OBE_VSTATE_OBE5__PsngrSeatbelt__Unlatched     (2)
#define VSC3OBE_VSTATE_OBE5__PsngrSeatbelt__Empty         (3)
#define VSC3OBE_VSTATE_OBE5_SirenAct_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE5_SirenAct__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE5__SirenAct__False              (0)
#define VSC3OBE_VSTATE_OBE5__SirenAct__True               (1)
#define VSC3OBE_VSTATE_OBE5_LightBarAct_raw_TO_(r)        (r)
#define VSC3OBE_VSTATE_OBE5_LightBarAct__TO_raw(u)        (u)
#define VSC3OBE_VSTATE_OBE5__LightBarAct__False           (0)
#define VSC3OBE_VSTATE_OBE5__LightBarAct__True            (1)
#define VSC3OBE_VSTATE_OBE5_ACC_raw_TO_(r)                (r)
#define VSC3OBE_VSTATE_OBE5_ACC__TO_raw(u)                (u)
#define VSC3OBE_VSTATE_OBE5__ACC__False                   (0)
#define VSC3OBE_VSTATE_OBE5__ACC__True                    (1)
#define VSC3OBE_VSTATE_OBE5_Horn_raw_TO_(r)               (r)
#define VSC3OBE_VSTATE_OBE5_Horn__TO_raw(u)               (u)
#define VSC3OBE_VSTATE_OBE5__Horn__False                  (0)
#define VSC3OBE_VSTATE_OBE5__Horn__True                   (1)
#define VSC3OBE_VSTATE_OBE5_DrvrDoor_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE5_DrvrDoor__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE5__DrvrDoor__Unknown            (0)
#define VSC3OBE_VSTATE_OBE5__DrvrDoor__Closed__locked     (1)
#define VSC3OBE_VSTATE_OBE5__DrvrDoor__Closed__unlocked   (2)
#define VSC3OBE_VSTATE_OBE5__DrvrDoor__Open               (3)
#define VSC3OBE_VSTATE_OBE5_PsngrDoor_raw_TO_(r)          (r)
#define VSC3OBE_VSTATE_OBE5_PsngrDoor__TO_raw(u)          (u)
#define VSC3OBE_VSTATE_OBE5__PsngrDoor__Unknown           (0)
#define VSC3OBE_VSTATE_OBE5__PsngrDoor__Closed__locked    (1)
#define VSC3OBE_VSTATE_OBE5__PsngrDoor__Closed__unlocked  (2)
#define VSC3OBE_VSTATE_OBE5__PsngrDoor__Open              (3)
#define VSC3OBE_VSTATE_OBE5_RearDoor_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE5_RearDoor__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE5__RearDoor__Both_closed___unknown  (0)
#define VSC3OBE_VSTATE_OBE5__RearDoor__Left_open          (1)
#define VSC3OBE_VSTATE_OBE5__RearDoor__Right_open         (2)
#define VSC3OBE_VSTATE_OBE5__RearDoor__Both_open          (3)
#define VSC3OBE_VSTATE_OBE5_Hood_raw_TO_(r)               (r)
#define VSC3OBE_VSTATE_OBE5_Hood__TO_raw(u)               (u)
#define VSC3OBE_VSTATE_OBE5__Hood__Closed                 (0)
#define VSC3OBE_VSTATE_OBE5__Hood__Open                   (1)
#define VSC3OBE_VSTATE_OBE5_Trunk_raw_TO_(r)              (r)
#define VSC3OBE_VSTATE_OBE5_Trunk__TO_raw(u)              (u)
#define VSC3OBE_VSTATE_OBE5__Trunk__Closed                (0)
#define VSC3OBE_VSTATE_OBE5__Trunk__Open                  (1)
#define VSC3OBE_VSTATE_OBE5_SpdLimAct_raw_TO_(r)          (r)
#define VSC3OBE_VSTATE_OBE5_SpdLimAct__TO_raw(u)          (u)
#define VSC3OBE_VSTATE_OBE5__SpdLimAct__False             (0)
#define VSC3OBE_VSTATE_OBE5__SpdLimAct__True              (1)
#define VSC3OBE_VSTATE_OBE5_OutAirTemp_raw_TO_de(r)       ((r) - 40)
#define VSC3OBE_VSTATE_OBE5_OutAirTemp_de_TO_raw(u)       ((u) + 40)
#define VSC3OBE_VSTATE_OBE5_WiperRtFnt_raw_TO_Sweep(r)    ((r) * 2)
#define VSC3OBE_VSTATE_OBE5_WiperRtFnt_Sweep_TO_raw(u)    ((u) / 2)
#define VSC3OBE_VSTATE_OBE5_PwrMode_raw_TO_(r)            (r)
#define VSC3OBE_VSTATE_OBE5_PwrMode__TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Off                 (0)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Accessory           (1)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Run                 (2)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Start_Crank_Request  (3)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Engine_Relay        (4)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Reserved            (5)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Reserved_6          (6)
#define VSC3OBE_VSTATE_OBE5__PwrMode__Reserved_7          (7)

/// 0x605 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE6
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [1, 0] [0, 4294967296] m
        /// Odometer
        uint32_t Odo:32;
        ///32
        /// [1, 0] [0, 127] cm
        /// Bumper Height Front
        uint16_t BmprHghtFnt:7;
        ///39
        /// [1, 0] [0, 127] cm
        /// Bumper Height rear
        uint16_t BmprHghtRear:7;
        ///46
        /// [5, 0] [0, 635] cm
        /// Vehicle Height
        uint16_t VehHght:7;
        ///53
        /// [50, 0] [0, 6350] kg
        /// Vehicle Mass
        uint16_t VehMass:7;
        ///60
        /// [1, 0] [0, 15]
        /// Vehicle Type
        uint16_t VehType:4;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        ///60
        /// [1, 0] [0, 15]
        /// Vehicle Type
        uint16_t VehType:4;
        ///53
        /// [50, 0] [0, 6350] kg
        /// Vehicle Mass
        uint16_t VehMass:7;
        ///46
        /// [5, 0] [0, 635] cm
        /// Vehicle Height
        uint16_t VehHght:7;
        ///39
        /// [1, 0] [0, 127] cm
        /// Bumper Height rear
        uint16_t BmprHghtRear:7;
        ///32
        /// [1, 0] [0, 127] cm
        /// Bumper Height Front
        uint16_t BmprHghtFnt:7;
        ///0
        /// [1, 0] [0, 4294967296] m
        /// Odometer
        uint32_t Odo:32;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE6;

#define VSC3OBE_VSTATE_OBE6_NUM_ELEMENTS 6

#define VSC3OBE_VSTATE_OBE6_ID                0x605
#define VSC3OBE_VSTATE_OBE6_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE6(
 const tVSC3OBE_VSTATE_OBE6 * s);

#define VSC3OBE_VSTATE_OBE6_Odo_raw_TO_m(r)            (r)
#define VSC3OBE_VSTATE_OBE6_Odo_m_TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE6_BmprHghtFnt_raw_TO_cm(r)   (r)
#define VSC3OBE_VSTATE_OBE6_BmprHghtFnt_cm_TO_raw(u)   (u)
#define VSC3OBE_VSTATE_OBE6_BmprHghtRear_raw_TO_cm(r)  (r)
#define VSC3OBE_VSTATE_OBE6_BmprHghtRear_cm_TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE6_VehHght_raw_TO_cm(r)       ((r) * 5)
#define VSC3OBE_VSTATE_OBE6_VehHght_cm_TO_raw(u)       ((u) / 5)
#define VSC3OBE_VSTATE_OBE6_VehMass_raw_TO_kg(r)       ((r) * 50)
#define VSC3OBE_VSTATE_OBE6_VehMass_kg_TO_raw(u)       ((u) / 50)
#define VSC3OBE_VSTATE_OBE6_VehType_raw_TO_(r)         (r)
#define VSC3OBE_VSTATE_OBE6_VehType__TO_raw(u)         (u)
#define VSC3OBE_VSTATE_OBE6__VehType__none             (0)
#define VSC3OBE_VSTATE_OBE6__VehType__unknown          (1)
#define VSC3OBE_VSTATE_OBE6__VehType__special          (2)
#define VSC3OBE_VSTATE_OBE6__VehType__motorcycle       (3)
#define VSC3OBE_VSTATE_OBE6__VehType__car              (4)
#define VSC3OBE_VSTATE_OBE6__VehType__carOther         (5)
#define VSC3OBE_VSTATE_OBE6__VehType__bus              (6)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt2         (7)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt3         (8)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt4         (9)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt4Trailer  (10)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt5Trailer  (11)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt6Trailer  (12)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt5MultiTrailer  (13)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt6MultiTrailer  (14)
#define VSC3OBE_VSTATE_OBE6__VehType__axleCnt7MultiTrailer  (15)

/// 0x606 8 Vehicle
typedef union VSC3OBE_VSTATE_OBE7
{
    uint64_t Raw;
    struct
    {
#if __BYTE_ORDER != __LITTLE_ENDIAN
        ///0
        /// [1, 0] [0, 1023]
        /// Visibility in Meters.
        uint16_t VisibilityRange:10;
        ///10
        /// [1, 0] [0, 3]
        /// Environment
        uint16_t Environment:2;
        ///12
        /// [1, 0] [0, 3]
        /// Front Window Washer status
        uint16_t WasherFront:2;
        ///14
        /// [1, 0] [0, 1023] cm
        /// Vehicle Width
        uint16_t VehicleWidth:10;
        ///24
        /// [1, 0] [0, 4095] cm
        /// Vehicle Length
        uint16_t VehicleLength:12;
        ///36
        /// [1, 0] [0, 2]
        /// Structural Separation Information
        uint16_t Separation:2;
        ///38
        /// [1, 0] [0, 3]
        /// Coolant Overheat
        uint16_t CoolantOverheat:2;
        ///40
        /// [1, 0] [0, 3]
        /// Electrical System Error
        uint16_t ElectricalSystemError:2;
        ///42
        /// [1, 0] [0, 3]
        /// Electrical System Overheat
        uint16_t ElectricalSystemOverheat:2;
        ///44
        /// [1, 0] [0, 3]
        /// Engine Oil Pressure Warning
        uint16_t EngineOilPressureWarning:2;
        ///46
        /// [1, 0] [0, 3]
        /// Hybrid System Error
        uint16_t HybridSystemError:2;
        ///48
        /// [1, 0] [0, 3]
        /// Steering Defect
        uint16_t SteeringDefect:2;
        ///50
        /// [1, 0] [0, 3]
        /// Transmission Overheat
        uint16_t TransmissionOverheat:2;
        ///52
        /// [1, 0] [0, 3]
        /// Low-Speed Accident
        uint16_t LowSpeedAccident:2;
        uint64_t pad_56:2;
        ///56
        /// [1, 0] [0, 7]
        /// Reversible Restraint
        uint16_t Restraint:3;
        ///59
        /// [1, 0] [0, 7]
        /// Automatic Brake
        uint16_t AutoBrake:3;
#else   // __BYTE_ORDER != __BIG_ENDIAN
        uint64_t pad_59:2;
        ///59
        /// [1, 0] [0, 7]
        /// Automatic Brake
        uint16_t AutoBrake:3;
        ///56
        /// [1, 0] [0, 7]
        /// Reversible Restraint
        uint16_t Restraint:3;
        uint64_t pad_52:2;
        ///52
        /// [1, 0] [0, 3]
        /// Low-Speed Accident
        uint16_t LowSpeedAccident:2;
        ///50
        /// [1, 0] [0, 3]
        /// Transmission Overheat
        uint16_t TransmissionOverheat:2;
        ///48
        /// [1, 0] [0, 3]
        /// Steering Defect
        uint16_t SteeringDefect:2;
        ///46
        /// [1, 0] [0, 3]
        /// Hybrid System Error
        uint16_t HybridSystemError:2;
        ///44
        /// [1, 0] [0, 3]
        /// Engine Oil Pressure Warning
        uint16_t EngineOilPressureWarning:2;
        ///42
        /// [1, 0] [0, 3]
        /// Electrical System Overheat
        uint16_t ElectricalSystemOverheat:2;
        ///40
        /// [1, 0] [0, 3]
        /// Electrical System Error
        uint16_t ElectricalSystemError:2;
        ///38
        /// [1, 0] [0, 3]
        /// Coolant Overheat
        uint16_t CoolantOverheat:2;
        ///36
        /// [1, 0] [0, 2]
        /// Structural Separation Information
        uint16_t Separation:2;
        ///24
        /// [1, 0] [0, 4095] cm
        /// Vehicle Length
        uint16_t VehicleLength:12;
        ///14
        /// [1, 0] [0, 1023] cm
        /// Vehicle Width
        uint16_t VehicleWidth:10;
        ///12
        /// [1, 0] [0, 3]
        /// Front Window Washer status
        uint16_t WasherFront:2;
        ///10
        /// [1, 0] [0, 3]
        /// Environment
        uint16_t Environment:2;
        ///0
        /// [1, 0] [0, 1023]
        /// Visibility in Meters.
        uint16_t VisibilityRange:10;
#endif
    } __attribute__ ((packed));
} tVSC3OBE_VSTATE_OBE7;

#define VSC3OBE_VSTATE_OBE7_NUM_ELEMENTS 16

#define VSC3OBE_VSTATE_OBE7_ID                0x606
#define VSC3OBE_VSTATE_OBE7_LEN               8
void    VSC3OBE_Dump_VSTATE_OBE7(
 const tVSC3OBE_VSTATE_OBE7 * s);

#define VSC3OBE_VSTATE_OBE7_VisibilityRange_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE7_VisibilityRange__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE7_Environment_raw_TO_(r)               (r)
#define VSC3OBE_VSTATE_OBE7_Environment__TO_raw(u)               (u)
#define VSC3OBE_VSTATE_OBE7__Environment__unavailable            (0)
#define VSC3OBE_VSTATE_OBE7__Environment__unknown                (1)
#define VSC3OBE_VSTATE_OBE7__Environment__rural                  (2)
#define VSC3OBE_VSTATE_OBE7__Environment__urban                  (3)
#define VSC3OBE_VSTATE_OBE7_WasherFront_raw_TO_(r)               (r)
#define VSC3OBE_VSTATE_OBE7_WasherFront__TO_raw(u)               (u)
#define VSC3OBE_VSTATE_OBE7__WasherFront__unavailable            (0)
#define VSC3OBE_VSTATE_OBE7__WasherFront__off                    (1)
#define VSC3OBE_VSTATE_OBE7__WasherFront__active                 (2)
#define VSC3OBE_VSTATE_OBE7__WasherFront__error                  (3)
#define VSC3OBE_VSTATE_OBE7_VehicleWidth_raw_TO_cm(r)            (r)
#define VSC3OBE_VSTATE_OBE7_VehicleWidth_cm_TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE7_VehicleLength_raw_TO_cm(r)           (r)
#define VSC3OBE_VSTATE_OBE7_VehicleLength_cm_TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE7_Separation_raw_TO_(r)                (r)
#define VSC3OBE_VSTATE_OBE7_Separation__TO_raw(u)                (u)
#define VSC3OBE_VSTATE_OBE7__Separation__Unknown                 (0)
#define VSC3OBE_VSTATE_OBE7__Separation__None                    (1)
#define VSC3OBE_VSTATE_OBE7__Separation__Structural              (2)
#define VSC3OBE_VSTATE_OBE7_CoolantOverheat_raw_TO_(r)           (r)
#define VSC3OBE_VSTATE_OBE7_CoolantOverheat__TO_raw(u)           (u)
#define VSC3OBE_VSTATE_OBE7__CoolantOverheat__unavailable        (0)
#define VSC3OBE_VSTATE_OBE7__CoolantOverheat__off                (1)
#define VSC3OBE_VSTATE_OBE7__CoolantOverheat__active             (2)
#define VSC3OBE_VSTATE_OBE7__CoolantOverheat__error              (3)
#define VSC3OBE_VSTATE_OBE7_ElectricalSystemError_raw_TO_(r)     (r)
#define VSC3OBE_VSTATE_OBE7_ElectricalSystemError__TO_raw(u)     (u)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemError__unavailable  (0)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemError__off          (1)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemError__active       (2)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemError__error        (3)
#define VSC3OBE_VSTATE_OBE7_ElectricalSystemOverheat_raw_TO_(r)  (r)
#define VSC3OBE_VSTATE_OBE7_ElectricalSystemOverheat__TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemOverheat__unavailable  (0)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemOverheat__off       (1)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemOverheat__active    (2)
#define VSC3OBE_VSTATE_OBE7__ElectricalSystemOverheat__error     (3)
#define VSC3OBE_VSTATE_OBE7_EngineOilPressureWarning_raw_TO_(r)  (r)
#define VSC3OBE_VSTATE_OBE7_EngineOilPressureWarning__TO_raw(u)  (u)
#define VSC3OBE_VSTATE_OBE7__EngineOilPressureWarning__unavailable  (0)
#define VSC3OBE_VSTATE_OBE7__EngineOilPressureWarning__off       (1)
#define VSC3OBE_VSTATE_OBE7__EngineOilPressureWarning__active    (2)
#define VSC3OBE_VSTATE_OBE7__EngineOilPressureWarning__error     (3)
#define VSC3OBE_VSTATE_OBE7_HybridSystemError_raw_TO_(r)         (r)
#define VSC3OBE_VSTATE_OBE7_HybridSystemError__TO_raw(u)         (u)
#define VSC3OBE_VSTATE_OBE7__HybridSystemError__unavailable      (0)
#define VSC3OBE_VSTATE_OBE7__HybridSystemError__off              (1)
#define VSC3OBE_VSTATE_OBE7__HybridSystemError__active           (2)
#define VSC3OBE_VSTATE_OBE7__HybridSystemError__error            (3)
#define VSC3OBE_VSTATE_OBE7_SteeringDefect_raw_TO_(r)            (r)
#define VSC3OBE_VSTATE_OBE7_SteeringDefect__TO_raw(u)            (u)
#define VSC3OBE_VSTATE_OBE7__SteeringDefect__unavailable         (0)
#define VSC3OBE_VSTATE_OBE7__SteeringDefect__off                 (1)
#define VSC3OBE_VSTATE_OBE7__SteeringDefect__active              (2)
#define VSC3OBE_VSTATE_OBE7__SteeringDefect__error               (3)
#define VSC3OBE_VSTATE_OBE7_TransmissionOverheat_raw_TO_(r)      (r)
#define VSC3OBE_VSTATE_OBE7_TransmissionOverheat__TO_raw(u)      (u)
#define VSC3OBE_VSTATE_OBE7__TransmissionOverheat__unavailable   (0)
#define VSC3OBE_VSTATE_OBE7__TransmissionOverheat__off           (1)
#define VSC3OBE_VSTATE_OBE7__TransmissionOverheat__active        (2)
#define VSC3OBE_VSTATE_OBE7__TransmissionOverheat__error         (3)
#define VSC3OBE_VSTATE_OBE7_LowSpeedAccident_raw_TO_(r)          (r)
#define VSC3OBE_VSTATE_OBE7_LowSpeedAccident__TO_raw(u)          (u)
#define VSC3OBE_VSTATE_OBE7__LowSpeedAccident__unavailable       (0)
#define VSC3OBE_VSTATE_OBE7__LowSpeedAccident__off               (1)
#define VSC3OBE_VSTATE_OBE7__LowSpeedAccident__active            (2)
#define VSC3OBE_VSTATE_OBE7__LowSpeedAccident__error             (3)
#define VSC3OBE_VSTATE_OBE7_Restraint_raw_TO_(r)                 (r)
#define VSC3OBE_VSTATE_OBE7_Restraint__TO_raw(u)                 (u)
#define VSC3OBE_VSTATE_OBE7__Restraint__unavailable              (0)
#define VSC3OBE_VSTATE_OBE7__Restraint__off                      (1)
#define VSC3OBE_VSTATE_OBE7__Restraint__on                       (2)
#define VSC3OBE_VSTATE_OBE7__Restraint__engaged                  (3)
#define VSC3OBE_VSTATE_OBE7__Restraint__error                    (4)
#define VSC3OBE_VSTATE_OBE7_AutoBrake_raw_TO_(r)                 (r)
#define VSC3OBE_VSTATE_OBE7_AutoBrake__TO_raw(u)                 (u)
#define VSC3OBE_VSTATE_OBE7__AutoBrake__unavailable              (0)
#define VSC3OBE_VSTATE_OBE7__AutoBrake__off                      (1)
#define VSC3OBE_VSTATE_OBE7__AutoBrake__on                       (2)
#define VSC3OBE_VSTATE_OBE7__AutoBrake__engaged                  (3)
#define VSC3OBE_VSTATE_OBE7__AutoBrake__error                    (4)

int VSC3OBE__Dump(uint32_t id, uint64_t Raw);

#ifdef __cplusplus
}
#endif

#endif // __DBS2CH_GEN_VSC3OBE_H__
