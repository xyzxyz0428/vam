// -*- Mode:c -*-
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

#ifndef __VSTATE_GEN_H
#define __VSTATE_GEN_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Allow us to create pointers. The structure internals are private.
typedef struct VStateState tVStateState;

// Enumerations for ABS
#define VS_ABS_Unknown    (0)
#define VS_ABS_Off    (1)
#define VS_ABS_On    (2)
#define VS_ABS_Engaged    (3)


// Enumerations for ParkingBrakeStatus
#define VS_ParkingBrakeStatus_Unknown    (0)
#define VS_ParkingBrakeStatus_Off    (1)
#define VS_ParkingBrakeStatus_On    (2)
#define VS_ParkingBrakeStatus_Reserved    (3)


// Enumerations for TrcCtrl
#define VS_TrcCtrl_Unknown    (0)
#define VS_TrcCtrl_Off    (1)
#define VS_TrcCtrl_On    (2)
#define VS_TrcCtrl_Engaged    (3)


// Enumerations for PRNDL
#define VS_PRNDL_Unknown    (0)
#define VS_PRNDL_Park    (1)
#define VS_PRNDL_Reverse    (2)
#define VS_PRNDL_Neutral    (3)
#define VS_PRNDL_OverDrive    (4)
#define VS_PRNDL_Drive    (5)
#define VS_PRNDL_Drive1    (6)
#define VS_PRNDL_Drive2    (7)
#define VS_PRNDL_Drive3    (8)
#define VS_PRNDL_Drive4    (9)
#define VS_PRNDL_Reserved0    (10)
#define VS_PRNDL_Reserved1    (11)
#define VS_PRNDL_Reserved2    (12)
#define VS_PRNDL_Reserved3    (13)
#define VS_PRNDL_Reserved4    (14)
#define VS_PRNDL_Reserved5    (15)


// Enumerations for StbCtrl
#define VS_StbCtrl_Unknown    (0)
#define VS_StbCtrl_Off    (1)
#define VS_StbCtrl_On    (2)
#define VS_StbCtrl_Engaged    (3)


// Enumerations for Weather
#define VS_Weather_Clear_Dry    (0)
#define VS_Weather_Fog    (1)
#define VS_Weather_Snow    (2)
#define VS_Weather_Rain    (3)
#define VS_Weather_Reserved4__may_be_donated_to_RoadType_    (4)
#define VS_Weather_Reserved5__may_be_donated_to_RoadType_    (5)
#define VS_Weather_Reserved6__may_be_donated_to_RoadType_    (6)
#define VS_Weather_Reserved7__may_be_donated_to_RoadType_    (7)


// Enumerations for RoadType
#define VS_RoadType_Unknown    (0)
#define VS_RoadType_LocalRoad    (1)
#define VS_RoadType_RegionalRoad    (2)
#define VS_RoadType_Highway    (3)


// Enumerations for Separation
#define VS_Separation_Unknown    (0)
#define VS_Separation_None    (1)
#define VS_Separation_Structural    (2)


// Enumerations for AutoBrake
#define VS_AutoBrake_Unknown    (0)
#define VS_AutoBrake_Off    (1)
#define VS_AutoBrake_On    (2)
#define VS_AutoBrake_Engaged    (3)
#define VS_AutoBrake_Error    (4)


// Enumerations for Restraint
#define VS_Restraint_Unknown    (0)
#define VS_Restraint_Off    (1)
#define VS_Restraint_On    (2)
#define VS_Restraint_Engaged    (3)
#define VS_Restraint_Error    (4)


// Enumerations for BrakePreChg
#define VS_BrakePreChg_Unknown    (0)
#define VS_BrakePreChg_Off    (1)
#define VS_BrakePreChg_On    (2)


// Enumerations for WiperSwRear
#define VS_WiperSwRear_Off    (0)
#define VS_WiperSwRear_Delay_5    (1)
#define VS_WiperSwRear_Delay_4    (2)
#define VS_WiperSwRear_Delay_3    (3)
#define VS_WiperSwRear_Delay_2    (4)
#define VS_WiperSwRear_Delay_1    (5)
#define VS_WiperSwRear_Low    (6)
#define VS_WiperSwRear_High    (7)
#define VS_WiperSwRear_Auto    (8)
#define VS_WiperSwRear_Error    (9)


// Enumerations for WiperSwFnt
#define VS_WiperSwFnt_Off    (0)
#define VS_WiperSwFnt_Delay_5    (1)
#define VS_WiperSwFnt_Delay_4    (2)
#define VS_WiperSwFnt_Delay_3    (3)
#define VS_WiperSwFnt_Delay_2    (4)
#define VS_WiperSwFnt_Delay_1    (5)
#define VS_WiperSwFnt_Low    (6)
#define VS_WiperSwFnt_High    (7)
#define VS_WiperSwFnt_Auto    (8)
#define VS_WiperSwFnt_Error    (9)


// Enumerations for FogLightsFront
#define VS_FogLightsFront_unknown    (0)
#define VS_FogLightsFront_unavailable    (1)
#define VS_FogLightsFront_error    (2)
#define VS_FogLightsFront_off    (3)
#define VS_FogLightsFront_automatic    (4)
#define VS_FogLightsFront_active    (5)
#define VS_FogLightsFront_driver    (6)


// Enumerations for FogLightsRear
#define VS_FogLightsRear_unknown    (0)
#define VS_FogLightsRear_unavailable    (1)
#define VS_FogLightsRear_error    (2)
#define VS_FogLightsRear_off    (3)
#define VS_FogLightsRear_automatic    (4)
#define VS_FogLightsRear_active    (5)
#define VS_FogLightsRear_driver    (6)


// Enumerations for ReversingLights
#define VS_ReversingLights_unknown    (0)
#define VS_ReversingLights_unavailable    (1)
#define VS_ReversingLights_error    (2)
#define VS_ReversingLights_off    (3)
#define VS_ReversingLights_automatic    (4)
#define VS_ReversingLights_active    (5)
#define VS_ReversingLights_driver    (6)


// Enumerations for DrvrSeatbelt
#define VS_DrvrSeatbelt_Unknown    (0)
#define VS_DrvrSeatbelt_Latched    (1)
#define VS_DrvrSeatbelt_Unlatched    (2)
#define VS_DrvrSeatbelt_Empty    (3)


// Enumerations for PsngrSeatbelt
#define VS_PsngrSeatbelt_Unknown    (0)
#define VS_PsngrSeatbelt_Latched    (1)
#define VS_PsngrSeatbelt_Unlatched    (2)
#define VS_PsngrSeatbelt_Empty    (3)


// Enumerations for PwrMode
#define VS_PwrMode_Off    (0)
#define VS_PwrMode_Accessory    (1)
#define VS_PwrMode_Run    (2)
#define VS_PwrMode_Start_Crank_Request    (3)
#define VS_PwrMode_Engine_Relay    (4)
#define VS_PwrMode_Reserved5    (5)
#define VS_PwrMode_Reserved6    (6)
#define VS_PwrMode_Reserved7    (7)


// Enumerations for DrvrDoor
#define VS_DrvrDoor_Unknown    (0)
#define VS_DrvrDoor_Closed_and_locked    (1)
#define VS_DrvrDoor_Closed_and_unlocked    (2)
#define VS_DrvrDoor_Open    (3)


// Enumerations for WasherFront
#define VS_WasherFront_unknown    (0)
#define VS_WasherFront_off    (1)
#define VS_WasherFront_active    (2)
#define VS_WasherFront_error    (3)


// Enumerations for RearDoor
#define VS_RearDoor_Both_closed__or_unknown_    (0)
#define VS_RearDoor_Left_open    (1)
#define VS_RearDoor_Right_open    (2)
#define VS_RearDoor_Both_open    (3)


// Enumerations for LanePos
#define VS_LanePos_unknown    (-2)
#define VS_LanePos_offTheRoad    (-1)
#define VS_LanePos_innerHardShoulder    (0)
#define VS_LanePos_innermostDrivingLane    (1)
#define VS_LanePos_secondLaneFromInside    (2)
#define VS_LanePos_outerHardShoulder    (14)


// Enumerations for LightBarInUse
#define VS_LightBarInUse_Unavailable    (0)
#define VS_LightBarInUse_NotInUse    (1)
#define VS_LightBarInUse_InUse    (2)
#define VS_LightBarInUse_YellowCautionLights    (3)
#define VS_LightBarInUse_SchooldBusLights    (4)
#define VS_LightBarInUse_ArrowSignsActive    (5)
#define VS_LightBarInUse_SlowMovingVehicle    (6)
#define VS_LightBarInUse_FreqStops    (7)


// Enumerations for SirenInUse
#define VS_SirenInUse_Unavailable    (0)
#define VS_SirenInUse_NotInUse    (1)
#define VS_SirenInUse_InUse    (2)
#define VS_SirenInUse_Reserved    (3)


// Enumerations for AEB
#define VS_AEB_Unknown    (0)
#define VS_AEB_Off    (1)
#define VS_AEB_On    (2)
#define VS_AEB_Engaged    (3)
#define VS_AEB_Error    (4)


// Enumerations for DrivingSide
#define VS_DrivingSide_Unknown    (0)
#define VS_DrivingSide_Left    (1)
#define VS_DrivingSide_Right    (2)


// Enumerations for Environment
#define VS_Environment_Unavailable    (0)
#define VS_Environment_Unknown    (1)
#define VS_Environment_Rural    (2)
#define VS_Environment_Urban    (3)


// Enumerations for CoolantOverheat
#define VS_CoolantOverheat_unknown    (0)
#define VS_CoolantOverheat_off    (1)
#define VS_CoolantOverheat_active    (2)
#define VS_CoolantOverheat_error    (3)


// Enumerations for ElectricalSystemError
#define VS_ElectricalSystemError_unknown    (0)
#define VS_ElectricalSystemError_off    (1)
#define VS_ElectricalSystemError_active    (2)
#define VS_ElectricalSystemError_error    (3)


// Enumerations for ElectricalSystemOverheat
#define VS_ElectricalSystemOverheat_unknown    (0)
#define VS_ElectricalSystemOverheat_off    (1)
#define VS_ElectricalSystemOverheat_active    (2)
#define VS_ElectricalSystemOverheat_error    (3)


// Enumerations for EngineOilPressureWarning
#define VS_EngineOilPressureWarning_unknown    (0)
#define VS_EngineOilPressureWarning_off    (1)
#define VS_EngineOilPressureWarning_active    (2)
#define VS_EngineOilPressureWarning_error    (3)


// Enumerations for HybridSystemError
#define VS_HybridSystemError_unknown    (0)
#define VS_HybridSystemError_off    (1)
#define VS_HybridSystemError_active    (2)
#define VS_HybridSystemError_error    (3)


// Enumerations for SteeringDefect
#define VS_SteeringDefect_unknown    (0)
#define VS_SteeringDefect_off    (1)
#define VS_SteeringDefect_active    (2)
#define VS_SteeringDefect_error    (3)


// Enumerations for TransmissionOverheat
#define VS_TransmissionOverheat_unknown    (0)
#define VS_TransmissionOverheat_off    (1)
#define VS_TransmissionOverheat_active    (2)
#define VS_TransmissionOverheat_error    (3)


// Enumerations for LowSpeedAccident
#define VS_LowSpeedAccident_unknown    (0)
#define VS_LowSpeedAccident_off    (1)
#define VS_LowSpeedAccident_active    (2)
#define VS_LowSpeedAccident_error    (3)


// Enumerations for DriveDirection
#define VS_DriveDirection_unknown    (0)
#define VS_DriveDirection_forward    (1)
#define VS_DriveDirection_backward    (2)
#define VS_DriveDirection_error    (3)

//  #### ABS ####
// Antilock Brake System (ABS) status
// (NOTE: 'On' means brake monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
int32_t VS_GetABS(const tVStateState * pVState, bool * pValid);
// Antilock Brake System (ABS) status
// (NOTE: 'On' means brake monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
void VS_SetABS(tVStateState * pVState, int32_t ABS);
bool VS_ABSIsActive(const tVStateState * pVState);
bool VS_ABSIsPassive(const tVStateState * pVState);

//  #### BrkAct ####
// Wheel Brakes Active (1=True; 0=False)
bool VS_GetBrkAct(const tVStateState * pVState, bool * pValid);
// Wheel Brakes Active (1=True; 0=False)
void VS_SetBrkAct(tVStateState * pVState, bool BrkAct);
bool VS_BrkActIsActive(const tVStateState * pVState);
bool VS_BrkActIsPassive(const tVStateState * pVState);

//  #### ParkingBrakeStatus ####
// Parking Brake Status (AKA Auxiliary Brake)
// 0: Unknown
// 1: Off
// 2: On
// 3: Reserved
int32_t VS_GetParkingBrakeStatus(const tVStateState * pVState, bool * pValid);
// Parking Brake Status (AKA Auxiliary Brake)
// 0: Unknown
// 1: Off
// 2: On
// 3: Reserved
void VS_SetParkingBrakeStatus(tVStateState * pVState, int32_t ParkingBrakeStatus);

//  #### TrcCtrl ####
// Traction Control System Status
// (NOTE: 'On' means traction monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
int32_t VS_GetTrcCtrl(const tVStateState * pVState, bool * pValid);
// Traction Control System Status
// (NOTE: 'On' means traction monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
void VS_SetTrcCtrl(tVStateState * pVState, int32_t TrcCtrl);
bool VS_TrcCtrlIsActive(const tVStateState * pVState);
bool VS_TrcCtrlIsPassive(const tVStateState * pVState);

//  #### PRNDL ####
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
int32_t VS_GetPRNDL(const tVStateState * pVState, bool * pValid);
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
void VS_SetPRNDL(tVStateState * pVState, int32_t PRNDL);
bool VS_PRNDLIsActive(const tVStateState * pVState);

//  #### PRNDL ####
// ASN-2016
unsigned /*SAETransmissionState*/ VS_GetPRNDL_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetPRNDL_asn2016(tVStateState * pVState, unsigned /*SAETransmissionState*/ PRNDL_asn2016);

//  #### DrvIntendedBrk ####
// Driver Intended Braking Level
int32_t VS_GetDrvIntendedBrk(const tVStateState * pVState, bool * pValid);
// Driver Intended Braking Level
void VS_SetDrvIntendedBrk(tVStateState * pVState, int32_t DrvIntendedBrk);

//  #### DrvIntendedBrk ####
// vsc3
// Driver Intended Braking Level
float VS_GetDrvIntendedBrk_kpa(const tVStateState * pVState);
// vsc3
// Driver Intended Braking Level
void VS_SetDrvIntendedBrk_kpa(tVStateState * pVState, float DrvIntendedBrk_kpa);

//  #### DrvIntendedBrk ####
// vw
uint16_t VS_GetDrvIntendedBrk_percent(const tVStateState * pVState, bool * pValid);
// vw
void VS_SetDrvIntendedBrk_percent(tVStateState * pVState, uint16_t DrvIntendedBrk_percent);

//  #### StbCtrl ####
// Stability Control System Status (AKA ESP - Electronic Stability Program)
// (NOTE: 'On' means stability monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
int32_t VS_GetStbCtrl(const tVStateState * pVState, bool * pValid);
// Stability Control System Status (AKA ESP - Electronic Stability Program)
// (NOTE: 'On' means stability monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
void VS_SetStbCtrl(tVStateState * pVState, int32_t StbCtrl);
bool VS_StbCtrlIsActive(const tVStateState * pVState);
bool VS_StbCtrlIsPassive(const tVStateState * pVState);

//  #### Weather ####
// Weather
// 0: Clear Dry
// 1: Fog
// 2: Snow
// 3: Rain
// 4: Reserved4 (may be donated to RoadType)
// 5: Reserved5 (may be donated to RoadType)
// 6: Reserved6 (may be donated to RoadType)
// 7: Reserved7 (may be donated to RoadType)
int32_t VS_GetWeather(const tVStateState * pVState, bool * pValid);
// Weather
// 0: Clear Dry
// 1: Fog
// 2: Snow
// 3: Rain
// 4: Reserved4 (may be donated to RoadType)
// 5: Reserved5 (may be donated to RoadType)
// 6: Reserved6 (may be donated to RoadType)
// 7: Reserved7 (may be donated to RoadType)
void VS_SetWeather(tVStateState * pVState, int32_t Weather);

//  #### RoadType ####
// Road Type
// 0: Unknown
// 1: LocalRoad
// 2: RegionalRoad
// 3: Highway
int32_t VS_GetRoadType(const tVStateState * pVState, bool * pValid);
// Road Type
// 0: Unknown
// 1: LocalRoad
// 2: RegionalRoad
// 3: Highway
void VS_SetRoadType(tVStateState * pVState, int32_t RoadType);

//  #### Separation ####
// Structural Separation Information
// 0: Unknown
// 1: None
// 2: Structural
int32_t VS_GetSeparation(const tVStateState * pVState, bool * pValid);
// Structural Separation Information
// 0: Unknown
// 1: None
// 2: Structural
void VS_SetSeparation(tVStateState * pVState, int32_t Separation);

//  #### EmergCallStatus ####
// E-Call Status (1=True; 0=False)
bool VS_GetEmergCallStatus(const tVStateState * pVState, bool * pValid);
// E-Call Status (1=True; 0=False)
void VS_SetEmergCallStatus(tVStateState * pVState, bool EmergCallStatus);
bool VS_EmergCallStatusIsActive(const tVStateState * pVState);
bool VS_EmergCallStatusIsPassive(const tVStateState * pVState);

//  #### ExtAirbagStatus ####
// Exterior Airbag Deployed (1=True; 0=False)
bool VS_GetExtAirbagStatus(const tVStateState * pVState, bool * pValid);
// Exterior Airbag Deployed (1=True; 0=False)
void VS_SetExtAirbagStatus(tVStateState * pVState, bool ExtAirbagStatus);
bool VS_ExtAirbagStatusIsActive(const tVStateState * pVState);
bool VS_ExtAirbagStatusIsPassive(const tVStateState * pVState);

//  #### AutoEngineShutdown ####
// Engine Shutdown Status (1=True; 0=False)
bool VS_GetAutoEngineShutdown(const tVStateState * pVState, bool * pValid);
// Engine Shutdown Status (1=True; 0=False)
void VS_SetAutoEngineShutdown(tVStateState * pVState, bool AutoEngineShutdown);
bool VS_AutoEngineShutdownIsActive(const tVStateState * pVState);
bool VS_AutoEngineShutdownIsPassive(const tVStateState * pVState);

//  #### AutoBrake ####
// Automatic Brake System status
// (NOTE: 'On' means brake monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
int32_t VS_GetAutoBrake(const tVStateState * pVState, bool * pValid);
// Automatic Brake System status
// (NOTE: 'On' means brake monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
void VS_SetAutoBrake(tVStateState * pVState, int32_t AutoBrake);
bool VS_AutoBrakeIsActive(const tVStateState * pVState);
bool VS_AutoBrakeIsPassive(const tVStateState * pVState);

//  #### Restraint ####
// Reversible Occupant Restraint System status
// (NOTE: 'On' means RORS monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
int32_t VS_GetRestraint(const tVStateState * pVState, bool * pValid);
// Reversible Occupant Restraint System status
// (NOTE: 'On' means RORS monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
void VS_SetRestraint(tVStateState * pVState, int32_t Restraint);
bool VS_RestraintIsActive(const tVStateState * pVState);
bool VS_RestraintIsPassive(const tVStateState * pVState);

//  #### BattVolt ####
// Battery Voltage (0...31.75 volts, E = N * .25)
int32_t VS_GetBattVolt(const tVStateState * pVState, bool * pValid);
// Battery Voltage (0...31.75 volts, E = N * .25)
void VS_SetBattVolt(tVStateState * pVState, int32_t BattVolt);

//  #### BattVolt ####
// vsc3
// Battery Voltage
float VS_GetBattVolt_V(const tVStateState * pVState);
// vsc3
// Battery Voltage
void VS_SetBattVolt_V(tVStateState * pVState, float BattVolt_V);

//  #### BrkPedalGrad ####
// Brake Pedal Gradient ([40, 0] [-5120, 5080] percent_per_s)
int32_t VS_GetBrkPedalGrad(const tVStateState * pVState, bool * pValid);
// Brake Pedal Gradient ([40, 0] [-5120, 5080] percent_per_s)
void VS_SetBrkPedalGrad(tVStateState * pVState, int32_t BrkPedalGrad);

//  #### BrkPedalGrad ####
// vsc3
// Brake Pedal Gradient
int16_t VS_GetBrkPedalGrad_percent_per_s(const tVStateState * pVState, bool * pValid);
// vsc3
// Brake Pedal Gradient
void VS_SetBrkPedalGrad_percent_per_s(tVStateState * pVState, int16_t BrkPedalGrad_percent_per_s);

//  #### BrkPedalPos ####
// Brake Pedal Position (0...255, E = N * 1)
int32_t VS_GetBrkPedalPos(const tVStateState * pVState, bool * pValid);
// Brake Pedal Position (0...255, E = N * 1)
void VS_SetBrkPedalPos(tVStateState * pVState, int32_t BrkPedalPos);

//  #### BrkPedalPos ####
// vsc3
// Brake Pedal Position
uint16_t VS_GetBrkPedalPos_percent(const tVStateState * pVState, bool * pValid);
// vsc3
// Brake Pedal Position
void VS_SetBrkPedalPos_percent(tVStateState * pVState, uint16_t BrkPedalPos_percent);

//  #### YawRate ####
// Yaw Rate (-327.68...327.67 deg/s, E = N * .01)
// (+'ve for right-hand turns)
int32_t VS_GetYawRate(const tVStateState * pVState, bool * pValid);
// Yaw Rate (-327.68...327.67 deg/s, E = N * .01)
// (+'ve for right-hand turns)
void VS_SetYawRate(tVStateState * pVState, int32_t YawRate);

//  #### YawRate ####
// vsc3
// Yaw Rate
float VS_GetYawRate_deg_per_s(const tVStateState * pVState);
// vsc3
// Yaw Rate
void VS_SetYawRate_deg_per_s(tVStateState * pVState, float YawRate_deg_per_s);

//  #### YawRate ####
// radians
float VS_GetYawRate_rad_per_s(const tVStateState * pVState);
// radians
void VS_SetYawRate_rad_per_s(tVStateState * pVState, float YawRate_rad_per_s);

//  #### YawRate ####
// ASN-2016
int16_t VS_GetYawRate_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetYawRate_asn2016(tVStateState * pVState, int16_t YawRate_asn2016);

//  #### StrWhlAngGrad ####
// Steering Wheel Angle Gradient ([1, 0] [-2048, 2047] deg_per_s)
// Same sense as StrWhlAng, i.e.
// +'ve means the wheel is being turned clockwise (e.g. tightening right-hand turn)
int32_t VS_GetStrWhlAngGrad(const tVStateState * pVState, bool * pValid);
// Steering Wheel Angle Gradient ([1, 0] [-2048, 2047] deg_per_s)
// Same sense as StrWhlAng, i.e.
// +'ve means the wheel is being turned clockwise (e.g. tightening right-hand turn)
void VS_SetStrWhlAngGrad(tVStateState * pVState, int32_t StrWhlAngGrad);

//  #### StrWhlAngGrad ####
// vsc3
// Steering Wheel Angle Gradient
int16_t VS_GetStrWhlAngGrad_deg_per_s(const tVStateState * pVState, bool * pValid);
// vsc3
// Steering Wheel Angle Gradient
void VS_SetStrWhlAngGrad_deg_per_s(tVStateState * pVState, int16_t StrWhlAngGrad_deg_per_s);

//  #### StrWhlAngGrad ####
// ASN-2016
int VS_GetStrWhlAngGrad_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetStrWhlAngGrad_asn2016(tVStateState * pVState, int StrWhlAngGrad_asn2016);

//  #### StrWhlAng ####
// Steering Wheel Angle ([0.5, 0] [-1024, 1023.5] deg)
// +'ve means the wheel has been turned clockwise (e.g. right-hand turn)
int32_t VS_GetStrWhlAng(const tVStateState * pVState, bool * pValid);
// Steering Wheel Angle ([0.5, 0] [-1024, 1023.5] deg)
// +'ve means the wheel has been turned clockwise (e.g. right-hand turn)
void VS_SetStrWhlAng(tVStateState * pVState, int32_t StrWhlAng);

//  #### StrWhlAng ####
// vsc3
// Steering Wheel Angle
float VS_GetStrWhlAng_deg(const tVStateState * pVState);
// vsc3
// Steering Wheel Angle
void VS_SetStrWhlAng_deg(tVStateState * pVState, float StrWhlAng_deg);

//  #### StrWhlAng ####
// ASN-2016
int VS_GetStrWhlAng_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetStrWhlAng_asn2016(tVStateState * pVState, int StrWhlAng_asn2016);

//  #### VehSpd ####
// Vehicle Speed (0...655.35 kph, E = N * .01)
int32_t VS_GetVehSpd(const tVStateState * pVState, bool * pValid);
// Vehicle Speed (0...655.35 kph, E = N * .01)
void VS_SetVehSpd(tVStateState * pVState, int32_t VehSpd);
bool VS_VehSpdIsActive(const tVStateState * pVState);
bool VS_VehSpdIsPassive(const tVStateState * pVState);

//  #### VehSpd ####
// vsc3
// Vehicle Speed
float VS_GetVehSpd_kph(const tVStateState * pVState);
// vsc3
// Vehicle Speed
void VS_SetVehSpd_kph(tVStateState * pVState, float VehSpd_kph);

//  #### VehSpd ####
// si
// SI units
float VS_GetVehSpd_mps(const tVStateState * pVState);
// si
// SI units
void VS_SetVehSpd_mps(tVStateState * pVState, float VehSpd_mps);

//  #### VehSpd ####
// ta
// Internal TC/TA/App units
float VS_GetVehSpd_mmpnm(const tVStateState * pVState);
// ta
// Internal TC/TA/App units
void VS_SetVehSpd_mmpnm(tVStateState * pVState, float VehSpd_mmpnm);

//  #### VehSpd ####
// ASN-2016
int32_t VS_GetVehSpd_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetVehSpd_asn2016(tVStateState * pVState, int32_t VehSpd_asn2016);

//  #### VehSpdConf ####
// Vehicle Speed confidence cm/s
// Data should be provided at 2-sigma confidence
int32_t VS_GetVehSpdConf(const tVStateState * pVState, bool * pValid);
// Vehicle Speed confidence cm/s
// Data should be provided at 2-sigma confidence
void VS_SetVehSpdConf(tVStateState * pVState, int32_t VehSpdConf);

//  #### VehSpdConf ####
// si
// SI units
float VS_GetVehSpdConf_mps(const tVStateState * pVState);
// si
// SI units
void VS_SetVehSpdConf_mps(tVStateState * pVState, float VehSpdConf_mps);

//  #### LatAccel ####
// Lateral Acceleration in mm/s/s, +/- 100,000
int32_t VS_GetLatAccel(const tVStateState * pVState, bool * pValid);
// Lateral Acceleration in mm/s/s, +/- 100,000
void VS_SetLatAccel(tVStateState * pVState, int32_t LatAccel);

//  #### LatAccel ####
// vsc3
// Lateral Acceleration
float VS_GetLatAccel_m_per_s_per_s(const tVStateState * pVState);
// vsc3
// Lateral Acceleration
void VS_SetLatAccel_m_per_s_per_s(tVStateState * pVState, float LatAccel_m_per_s_per_s);

//  #### LatAccel ####
// si
// SI units
float VS_GetLatAccel_mps2(const tVStateState * pVState);
// si
// SI units
void VS_SetLatAccel_mps2(tVStateState * pVState, float LatAccel_mps2);

//  #### LatAccel ####
// mmpnm2
// Internal Units
float VS_GetLatAccel_mmpnm2(const tVStateState * pVState);
// mmpnm2
// Internal Units
void VS_SetLatAccel_mmpnm2(tVStateState * pVState, float LatAccel_mmpnm2);

//  #### LatAccel ####
// ASN-2016
int16_t VS_GetLatAccel_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetLatAccel_asn2016(tVStateState * pVState, int16_t LatAccel_asn2016);

//  #### PanicBrake ####
// Panic Brake (AKA Emergency Brake Lights) active (1=True; 0=False)
bool VS_GetPanicBrake(const tVStateState * pVState, bool * pValid);
// Panic Brake (AKA Emergency Brake Lights) active (1=True; 0=False)
void VS_SetPanicBrake(tVStateState * pVState, bool PanicBrake);
bool VS_PanicBrakeIsActive(const tVStateState * pVState);
bool VS_PanicBrakeIsPassive(const tVStateState * pVState);

//  #### BrakePreChg ####
// Brake Pre-charge status (AKA Brake Boost)
// 0: Unknown
// 1: Off
// 2: On
int32_t VS_GetBrakePreChg(const tVStateState * pVState, bool * pValid);
// Brake Pre-charge status (AKA Brake Boost)
// 0: Unknown
// 1: Off
// 2: On
void VS_SetBrakePreChg(tVStateState * pVState, int32_t BrakePreChg);

//  #### WiperSwRear ####
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
int32_t VS_GetWiperSwRear(const tVStateState * pVState, bool * pValid);
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
void VS_SetWiperSwRear(tVStateState * pVState, int32_t WiperSwRear);
bool VS_WiperSwRearIsActive(const tVStateState * pVState);
bool VS_WiperSwRearIsPassive(const tVStateState * pVState);

//  #### AirbagStatus ####
// Driver Airbag Deployed (1=True; 0=False)
bool VS_GetAirbagStatus(const tVStateState * pVState, bool * pValid);
// Driver Airbag Deployed (1=True; 0=False)
void VS_SetAirbagStatus(tVStateState * pVState, bool AirbagStatus);
bool VS_AirbagStatusIsActive(const tVStateState * pVState);
bool VS_AirbagStatusIsPassive(const tVStateState * pVState);

//  #### HighBeamStatus ####
// High Beam Active (1=True; 0=False)
bool VS_GetHighBeamStatus(const tVStateState * pVState, bool * pValid);
// High Beam Active (1=True; 0=False)
void VS_SetHighBeamStatus(tVStateState * pVState, bool HighBeamStatus);
bool VS_HighBeamStatusIsActive(const tVStateState * pVState);
bool VS_HighBeamStatusIsPassive(const tVStateState * pVState);

//  #### WiperSweepStatus ####
// Wiper Sweep Active (1=True; 0=False)
bool VS_GetWiperSweepStatus(const tVStateState * pVState, bool * pValid);
// Wiper Sweep Active (1=True; 0=False)
void VS_SetWiperSweepStatus(tVStateState * pVState, bool WiperSweepStatus);
bool VS_WiperSweepStatusIsActive(const tVStateState * pVState);
bool VS_WiperSweepStatusIsPassive(const tVStateState * pVState);

//  #### WiperSwFnt ####
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
int32_t VS_GetWiperSwFnt(const tVStateState * pVState, bool * pValid);
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
void VS_SetWiperSwFnt(tVStateState * pVState, int32_t WiperSwFnt);
bool VS_WiperSwFntIsActive(const tVStateState * pVState);
bool VS_WiperSwFntIsPassive(const tVStateState * pVState);

//  #### SafetyWarningStatus ####
// Safety/Collision Warning Active (1=True; 0=False)
bool VS_GetSafetyWarningStatus(const tVStateState * pVState, bool * pValid);
// Safety/Collision Warning Active (1=True; 0=False)
void VS_SetSafetyWarningStatus(tVStateState * pVState, bool SafetyWarningStatus);
bool VS_SafetyWarningStatusIsActive(const tVStateState * pVState);
bool VS_SafetyWarningStatusIsPassive(const tVStateState * pVState);

//  #### LonAccel ####
// Longitudinal Acceleration in mm/s/s, +/- 100,000
int32_t VS_GetLonAccel(const tVStateState * pVState, bool * pValid);
// Longitudinal Acceleration in mm/s/s, +/- 100,000
void VS_SetLonAccel(tVStateState * pVState, int32_t LonAccel);
bool VS_LonAccelIsActive(const tVStateState * pVState);
bool VS_LonAccelIsPassive(const tVStateState * pVState);

//  #### LonAccel ####
// vsc3
// Longitudinal Acceleration
float VS_GetLonAccel_m_per_s_per_s(const tVStateState * pVState);
// vsc3
// Longitudinal Acceleration
void VS_SetLonAccel_m_per_s_per_s(tVStateState * pVState, float LonAccel_m_per_s_per_s);

//  #### LonAccel ####
// mmpnm2
// Internal Units
float VS_GetLonAccel_mmpnm2(const tVStateState * pVState);
// mmpnm2
// Internal Units
void VS_SetLonAccel_mmpnm2(tVStateState * pVState, float LonAccel_mmpnm2);

//  #### LonAccel ####
// ASN-2016
int16_t VS_GetLonAccel_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetLonAccel_asn2016(tVStateState * pVState, int16_t LonAccel_asn2016);

//  #### VertAccel ####
// Vertical Acceleration in mm/s/s, +/- 100,000
int32_t VS_GetVertAccel(const tVStateState * pVState, bool * pValid);
// Vertical Acceleration in mm/s/s, +/- 100,000
void VS_SetVertAccel(tVStateState * pVState, int32_t VertAccel);

//  #### VertAccel ####
// vsc3
// Vertical Acceleration
float VS_GetVertAccel_m_per_s_per_s(const tVStateState * pVState);
// vsc3
// Vertical Acceleration
void VS_SetVertAccel_m_per_s_per_s(tVStateState * pVState, float VertAccel_m_per_s_per_s);

//  #### VertAccel ####
// mmpnm2
// Internal Units
float VS_GetVertAccel_mmpnm2(const tVStateState * pVState);
// mmpnm2
// Internal Units
void VS_SetVertAccel_mmpnm2(tVStateState * pVState, float VertAccel_mmpnm2);

//  #### VertAccel ####
// ASN-2016
int8_t VS_GetVertAccel_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetVertAccel_asn2016(tVStateState * pVState, int8_t VertAccel_asn2016);

//  #### LftTurnSig ####
// Left Turn Signal (1=True; 0=False)
bool VS_GetLftTurnSig(const tVStateState * pVState, bool * pValid);
// Left Turn Signal (1=True; 0=False)
void VS_SetLftTurnSig(tVStateState * pVState, bool LftTurnSig);
bool VS_LftTurnSigIsActive(const tVStateState * pVState);
bool VS_LftTurnSigIsPassive(const tVStateState * pVState);

//  #### RtTurnSig ####
// Right Turn Signal (1=True; 0=False)
bool VS_GetRtTurnSig(const tVStateState * pVState, bool * pValid);
// Right Turn Signal (1=True; 0=False)
void VS_SetRtTurnSig(tVStateState * pVState, bool RtTurnSig);
bool VS_RtTurnSigIsActive(const tVStateState * pVState);
bool VS_RtTurnSigIsPassive(const tVStateState * pVState);

//  #### CrusEngd ####
// Cruise Control Engaged (1=True; 0=False)
bool VS_GetCrusEngd(const tVStateState * pVState, bool * pValid);
// Cruise Control Engaged (1=True; 0=False)
void VS_SetCrusEngd(tVStateState * pVState, bool CrusEngd);
bool VS_CrusEngdIsActive(const tVStateState * pVState);
bool VS_CrusEngdIsPassive(const tVStateState * pVState);

//  #### CrusOvrd ####
// Cruise Control Override (1=True; 0=False)
bool VS_GetCrusOvrd(const tVStateState * pVState, bool * pValid);
// Cruise Control Override (1=True; 0=False)
void VS_SetCrusOvrd(tVStateState * pVState, bool CrusOvrd);
bool VS_CrusOvrdIsActive(const tVStateState * pVState);
bool VS_CrusOvrdIsPassive(const tVStateState * pVState);

//  #### AccelPos ####
// Accelerator Pedal Position % (0...100%, E = N * 100.0/255)
int32_t VS_GetAccelPos(const tVStateState * pVState, bool * pValid);
// Accelerator Pedal Position % (0...100%, E = N * 100.0/255)
void VS_SetAccelPos(tVStateState * pVState, int32_t AccelPos);

//  #### AccelPos ####
// vsc3
// Accelerator Pedal Position %
uint16_t VS_GetAccelPos_percent(const tVStateState * pVState, bool * pValid);
// vsc3
// Accelerator Pedal Position %
void VS_SetAccelPos_percent(tVStateState * pVState, uint16_t AccelPos_percent);

//  #### VehWidth ####
// Vehicle Width in cm
// EU: CDD supports up to 600 cm with 10 cm resolution (use 610 for larger widths)
// NA: J2735 supports up to 1023 cm with 1 cm resolution
int32_t VS_GetVehWidth(const tVStateState * pVState, bool * pValid);
// Vehicle Width in cm
// EU: CDD supports up to 600 cm with 10 cm resolution (use 610 for larger widths)
// NA: J2735 supports up to 1023 cm with 1 cm resolution
void VS_SetVehWidth(tVStateState * pVState, int32_t VehWidth);

//  #### VehWidth ####
// si
// meter
float VS_GetVehWidth_m(const tVStateState * pVState);
// si
// meter
void VS_SetVehWidth_m(tVStateState * pVState, float VehWidth_m);

//  #### VehWidth ####
// vsc3
// Vehicle Width
uint16_t VS_GetVehWidth_vsc3(const tVStateState * pVState, bool * pValid);
// vsc3
// Vehicle Width
void VS_SetVehWidth_vsc3(tVStateState * pVState, uint16_t VehWidth_vsc3);

//  #### VehWidth ####
// eu
// SI units
uint16_t VS_GetVehWidth_dm(const tVStateState * pVState, bool * pValid);
// eu
// SI units
void VS_SetVehWidth_dm(tVStateState * pVState, uint16_t VehWidth_dm);

//  #### VehWidth ####
// na
// SI units
uint16_t VS_GetVehWidth_cm(const tVStateState * pVState, bool * pValid);
// na
// SI units
void VS_SetVehWidth_cm(tVStateState * pVState, uint16_t VehWidth_cm);

//  #### VehWidth ####
// mm
// SI units
uint32_t VS_GetVehWidth_mm(const tVStateState * pVState, bool * pValid);
// mm
// SI units
void VS_SetVehWidth_mm(tVStateState * pVState, uint32_t VehWidth_mm);

//  #### VehLength ####
// Vehicle Length in cm
// EU: CDD supports up to 10210 cm with 10 cm resolution (use 10220 for larger lengths)
// NA: J2735 supports up to 4095 cm with 1 cm resolution
int32_t VS_GetVehLength(const tVStateState * pVState, bool * pValid);
// Vehicle Length in cm
// EU: CDD supports up to 10210 cm with 10 cm resolution (use 10220 for larger lengths)
// NA: J2735 supports up to 4095 cm with 1 cm resolution
void VS_SetVehLength(tVStateState * pVState, int32_t VehLength);

//  #### VehLength ####
// si
// meter
float VS_GetVehLength_m(const tVStateState * pVState);
// si
// meter
void VS_SetVehLength_m(tVStateState * pVState, float VehLength_m);

//  #### VehLength ####
// vsc3
// Vehicle Length
uint16_t VS_GetVehLength_vsc3(const tVStateState * pVState, bool * pValid);
// vsc3
// Vehicle Length
void VS_SetVehLength_vsc3(tVStateState * pVState, uint16_t VehLength_vsc3);

//  #### VehLength ####
// eu
// SI units
uint16_t VS_GetVehLength_dm(const tVStateState * pVState, bool * pValid);
// eu
// SI units
void VS_SetVehLength_dm(tVStateState * pVState, uint16_t VehLength_dm);

//  #### VehLength ####
// na
// SI units
uint16_t VS_GetVehLength_cm(const tVStateState * pVState, bool * pValid);
// na
// SI units
void VS_SetVehLength_cm(tVStateState * pVState, uint16_t VehLength_cm);

//  #### VehLength ####
// mm
// SI units
uint32_t VS_GetVehLength_mm(const tVStateState * pVState, bool * pValid);
// mm
// SI units
void VS_SetVehLength_mm(tVStateState * pVState, uint32_t VehLength_mm);

//  #### LowBeamStatus ####
// Low Beam Status (1=True; 0=False)
bool VS_GetLowBeamStatus(const tVStateState * pVState, bool * pValid);
// Low Beam Status (1=True; 0=False)
void VS_SetLowBeamStatus(tVStateState * pVState, bool LowBeamStatus);
bool VS_LowBeamStatusIsActive(const tVStateState * pVState);
bool VS_LowBeamStatusIsPassive(const tVStateState * pVState);

//  #### HzdLgts ####
// Hazard Lights (1=True; 0=False)
bool VS_GetHzdLgts(const tVStateState * pVState, bool * pValid);
// Hazard Lights (1=True; 0=False)
void VS_SetHzdLgts(tVStateState * pVState, bool HzdLgts);
bool VS_HzdLgtsIsActive(const tVStateState * pVState);
bool VS_HzdLgtsIsPassive(const tVStateState * pVState);

//  #### AutoLghtCntrlOn ####
// Auto Light Control On (1=True; 0=False)
bool VS_GetAutoLghtCntrlOn(const tVStateState * pVState, bool * pValid);
// Auto Light Control On (1=True; 0=False)
void VS_SetAutoLghtCntrlOn(tVStateState * pVState, bool AutoLghtCntrlOn);
bool VS_AutoLghtCntrlOnIsActive(const tVStateState * pVState);
bool VS_AutoLghtCntrlOnIsPassive(const tVStateState * pVState);

//  #### DtimeRunLghtsOn ####
// Daytime Running Lights On (1=True; 0=False)
bool VS_GetDtimeRunLghtsOn(const tVStateState * pVState, bool * pValid);
// Daytime Running Lights On (1=True; 0=False)
void VS_SetDtimeRunLghtsOn(tVStateState * pVState, bool DtimeRunLghtsOn);
bool VS_DtimeRunLghtsOnIsActive(const tVStateState * pVState);
bool VS_DtimeRunLghtsOnIsPassive(const tVStateState * pVState);

//  #### FogLightsFront ####
// Front Fog Lights
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
int32_t VS_GetFogLightsFront(const tVStateState * pVState, bool * pValid);
// Front Fog Lights
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
void VS_SetFogLightsFront(tVStateState * pVState, int32_t FogLightsFront);

//  #### FogLightsRear ####
// Rear Fog Lights
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
int32_t VS_GetFogLightsRear(const tVStateState * pVState, bool * pValid);
// Rear Fog Lights
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
void VS_SetFogLightsRear(tVStateState * pVState, int32_t FogLightsRear);

//  #### ReversingLights ####
// Reversing Lights (usually automatically turned on in reverse gear).
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
int32_t VS_GetReversingLights(const tVStateState * pVState, bool * pValid);
// Reversing Lights (usually automatically turned on in reverse gear).
// 0: unknown
// 1: unavailable
// 2: error
// 3: off
// 4: automatic
// 5: active
// 6: driver
void VS_SetReversingLights(tVStateState * pVState, int32_t ReversingLights);

//  #### PkgLghtsOn ####
// Parking Lights On (1=True; 0=False)
bool VS_GetPkgLghtsOn(const tVStateState * pVState, bool * pValid);
// Parking Lights On (1=True; 0=False)
void VS_SetPkgLghtsOn(tVStateState * pVState, bool PkgLghtsOn);
bool VS_PkgLghtsOnIsActive(const tVStateState * pVState);
bool VS_PkgLghtsOnIsPassive(const tVStateState * pVState);

//  #### CruiseSetSpeed ####
// Cruise set speed (0...255 kph, E = N * 1)
int32_t VS_GetCruiseSetSpeed(const tVStateState * pVState, bool * pValid);
// Cruise set speed (0...255 kph, E = N * 1)
void VS_SetCruiseSetSpeed(tVStateState * pVState, int32_t CruiseSetSpeed);

//  #### CruiseSetSpeed ####
// vsc3
// Cruise Set Speed
uint16_t VS_GetCruiseSetSpeed_kph(const tVStateState * pVState, bool * pValid);
// vsc3
// Cruise Set Speed
void VS_SetCruiseSetSpeed_kph(tVStateState * pVState, uint16_t CruiseSetSpeed_kph);

//  #### WheelVelocityLF ####
// Wheel Velocity LF
int32_t VS_GetWheelVelocityLF(const tVStateState * pVState, bool * pValid);
// Wheel Velocity LF
void VS_SetWheelVelocityLF(tVStateState * pVState, int32_t WheelVelocityLF);

//  #### WheelVelocityLF ####
// vsc3
// Wheel Velocity Left Front
float VS_GetWheelVelocityLF_kph(const tVStateState * pVState);
// vsc3
// Wheel Velocity Left Front
void VS_SetWheelVelocityLF_kph(tVStateState * pVState, float WheelVelocityLF_kph);

//  #### WheelVelocityRF ####
// Wheel Velocity RF
int32_t VS_GetWheelVelocityRF(const tVStateState * pVState, bool * pValid);
// Wheel Velocity RF
void VS_SetWheelVelocityRF(tVStateState * pVState, int32_t WheelVelocityRF);

//  #### WheelVelocityRF ####
// vsc3
// Wheel Velocity Right Front
float VS_GetWheelVelocityRF_kph(const tVStateState * pVState);
// vsc3
// Wheel Velocity Right Front
void VS_SetWheelVelocityRF_kph(tVStateState * pVState, float WheelVelocityRF_kph);

//  #### WheelVelocityLR ####
// Wheel Velocity LR
int32_t VS_GetWheelVelocityLR(const tVStateState * pVState, bool * pValid);
// Wheel Velocity LR
void VS_SetWheelVelocityLR(tVStateState * pVState, int32_t WheelVelocityLR);

//  #### WheelVelocityLR ####
// vsc3
// Wheel Velocity Left Rear
float VS_GetWheelVelocityLR_kph(const tVStateState * pVState);
// vsc3
// Wheel Velocity Left Rear
void VS_SetWheelVelocityLR_kph(tVStateState * pVState, float WheelVelocityLR_kph);

//  #### WheelVelocityRR ####
// Wheel Velocity RR
int32_t VS_GetWheelVelocityRR(const tVStateState * pVState, bool * pValid);
// Wheel Velocity RR
void VS_SetWheelVelocityRR(tVStateState * pVState, int32_t WheelVelocityRR);

//  #### WheelVelocityRR ####
// vsc3
// Wheel Velocity Right Rear
float VS_GetWheelVelocityRR_kph(const tVStateState * pVState);
// vsc3
// Wheel Velocity Right Rear
void VS_SetWheelVelocityRR_kph(tVStateState * pVState, float WheelVelocityRR_kph);

//  #### TirePressureLF ####
// Tire Pressure LF (0...255 psi, E = N * 1)
int32_t VS_GetTirePressureLF(const tVStateState * pVState, bool * pValid);
// Tire Pressure LF (0...255 psi, E = N * 1)
void VS_SetTirePressureLF(tVStateState * pVState, int32_t TirePressureLF);
bool VS_TirePressureLFIsActive(const tVStateState * pVState);
bool VS_TirePressureLFIsPassive(const tVStateState * pVState);

//  #### TirePressureLF ####
// vsc3
// Tire Pressure Left Front
uint16_t VS_GetTirePressureLF_psi(const tVStateState * pVState, bool * pValid);
// vsc3
// Tire Pressure Left Front
void VS_SetTirePressureLF_psi(tVStateState * pVState, uint16_t TirePressureLF_psi);

//  #### TirePressureLF ####
// kpa
// Tire Pressure Left Front
uint16_t VS_GetTirePressureLF_kpa(const tVStateState * pVState, bool * pValid);
// kpa
// Tire Pressure Left Front
void VS_SetTirePressureLF_kpa(tVStateState * pVState, uint16_t TirePressureLF_kpa);

//  #### TirePressureRF ####
// Tire Pressure RF (0...255 psi, E = N * 1)
int32_t VS_GetTirePressureRF(const tVStateState * pVState, bool * pValid);
// Tire Pressure RF (0...255 psi, E = N * 1)
void VS_SetTirePressureRF(tVStateState * pVState, int32_t TirePressureRF);
bool VS_TirePressureRFIsActive(const tVStateState * pVState);
bool VS_TirePressureRFIsPassive(const tVStateState * pVState);

//  #### TirePressureRF ####
// vsc3
// Tire Pressure Right Front
uint16_t VS_GetTirePressureRF_psi(const tVStateState * pVState, bool * pValid);
// vsc3
// Tire Pressure Right Front
void VS_SetTirePressureRF_psi(tVStateState * pVState, uint16_t TirePressureRF_psi);

//  #### TirePressureRF ####
// kpa
// Tire Pressure Left Front
uint16_t VS_GetTirePressureRF_kpa(const tVStateState * pVState, bool * pValid);
// kpa
// Tire Pressure Left Front
void VS_SetTirePressureRF_kpa(tVStateState * pVState, uint16_t TirePressureRF_kpa);

//  #### TirePressureLR ####
// Tire Pressure LR (0...255 psi, E = N * 1)
int32_t VS_GetTirePressureLR(const tVStateState * pVState, bool * pValid);
// Tire Pressure LR (0...255 psi, E = N * 1)
void VS_SetTirePressureLR(tVStateState * pVState, int32_t TirePressureLR);
bool VS_TirePressureLRIsActive(const tVStateState * pVState);
bool VS_TirePressureLRIsPassive(const tVStateState * pVState);

//  #### TirePressureLR ####
// vsc3
// Tire Pressure Left Rear
uint16_t VS_GetTirePressureLR_psi(const tVStateState * pVState, bool * pValid);
// vsc3
// Tire Pressure Left Rear
void VS_SetTirePressureLR_psi(tVStateState * pVState, uint16_t TirePressureLR_psi);

//  #### TirePressureLR ####
// kpa
// Tire Pressure Left Front
uint16_t VS_GetTirePressureLR_kpa(const tVStateState * pVState, bool * pValid);
// kpa
// Tire Pressure Left Front
void VS_SetTirePressureLR_kpa(tVStateState * pVState, uint16_t TirePressureLR_kpa);

//  #### TirePressureRR ####
// Tire Pressure RR (0...255 psi, E = N * 1)
int32_t VS_GetTirePressureRR(const tVStateState * pVState, bool * pValid);
// Tire Pressure RR (0...255 psi, E = N * 1)
void VS_SetTirePressureRR(tVStateState * pVState, int32_t TirePressureRR);
bool VS_TirePressureRRIsActive(const tVStateState * pVState);
bool VS_TirePressureRRIsPassive(const tVStateState * pVState);

//  #### TirePressureRR ####
// vsc3
// Tire Pressure Right Rear
uint16_t VS_GetTirePressureRR_psi(const tVStateState * pVState, bool * pValid);
// vsc3
// Tire Pressure Right Rear
void VS_SetTirePressureRR_psi(tVStateState * pVState, uint16_t TirePressureRR_psi);

//  #### TirePressureRR ####
// kpa
// Tire Pressure Left Front
uint16_t VS_GetTirePressureRR_kpa(const tVStateState * pVState, bool * pValid);
// kpa
// Tire Pressure Left Front
void VS_SetTirePressureRR_kpa(tVStateState * pVState, uint16_t TirePressureRR_kpa);

//  #### DrvrSeatbelt ####
// Driver seatbelt status
// 0: Unknown
// 1: Latched
// 2: Unlatched
// 3: Empty
int32_t VS_GetDrvrSeatbelt(const tVStateState * pVState, bool * pValid);
// Driver seatbelt status
// 0: Unknown
// 1: Latched
// 2: Unlatched
// 3: Empty
void VS_SetDrvrSeatbelt(tVStateState * pVState, int32_t DrvrSeatbelt);

//  #### PsngrSeatbelt ####
// Front passenger seatbelt status
// 0: Unknown
// 1: Latched
// 2: Unlatched
// 3: Empty
int32_t VS_GetPsngrSeatbelt(const tVStateState * pVState, bool * pValid);
// Front passenger seatbelt status
// 0: Unknown
// 1: Latched
// 2: Unlatched
// 3: Empty
void VS_SetPsngrSeatbelt(tVStateState * pVState, int32_t PsngrSeatbelt);

//  #### PwrMode ####
// Power mode
// 0: Off
// 1: Accessory
// 2: Run
// 3: Start Crank Request
// 4: Engine Relay
// 5: Reserved5
// 6: Reserved6
// 7: Reserved7
int32_t VS_GetPwrMode(const tVStateState * pVState, bool * pValid);
// Power mode
// 0: Off
// 1: Accessory
// 2: Run
// 3: Start Crank Request
// 4: Engine Relay
// 5: Reserved5
// 6: Reserved6
// 7: Reserved7
void VS_SetPwrMode(tVStateState * pVState, int32_t PwrMode);

//  #### ACC ####
// Adaptive Cruise Control (ACC) status (1=ON 0=OFF)
bool VS_GetACC(const tVStateState * pVState, bool * pValid);
// Adaptive Cruise Control (ACC) status (1=ON 0=OFF)
void VS_SetACC(tVStateState * pVState, bool ACC);
bool VS_ACCIsActive(const tVStateState * pVState);
bool VS_ACCIsPassive(const tVStateState * pVState);

//  #### Horn ####
// Horn status (1=ON 0=OFF)
bool VS_GetHorn(const tVStateState * pVState, bool * pValid);
// Horn status (1=ON 0=OFF)
void VS_SetHorn(tVStateState * pVState, bool Horn);
bool VS_HornIsActive(const tVStateState * pVState);
bool VS_HornIsPassive(const tVStateState * pVState);

//  #### DrvrDoor ####
// Driver door status
// 0: Unknown
// 1: Closed and locked
// 2: Closed and unlocked
// 3: Open
int32_t VS_GetDrvrDoor(const tVStateState * pVState, bool * pValid);
// Driver door status
// 0: Unknown
// 1: Closed and locked
// 2: Closed and unlocked
// 3: Open
void VS_SetDrvrDoor(tVStateState * pVState, int32_t DrvrDoor);
bool VS_DrvrDoorIsActive(const tVStateState * pVState);

//  #### WasherFront ####
// Front Window Washer
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetWasherFront(const tVStateState * pVState, bool * pValid);
// Front Window Washer
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetWasherFront(tVStateState * pVState, int32_t WasherFront);

//  #### PsngrDoor ####
// Front passenger door status
// Same Values as DrvrDoor
int32_t VS_GetPsngrDoor(const tVStateState * pVState, bool * pValid);
// Front passenger door status
// Same Values as DrvrDoor
void VS_SetPsngrDoor(tVStateState * pVState, int32_t PsngrDoor);
bool VS_PsngrDoorIsActive(const tVStateState * pVState);

//  #### RearDoor ####
// Rear passenger doors status
// 0: Both closed (or unknown)
// 1: Left open
// 2: Right open
// 3: Both open
int32_t VS_GetRearDoor(const tVStateState * pVState, bool * pValid);
// Rear passenger doors status
// 0: Both closed (or unknown)
// 1: Left open
// 2: Right open
// 3: Both open
void VS_SetRearDoor(tVStateState * pVState, int32_t RearDoor);
bool VS_RearDoorIsActive(const tVStateState * pVState);
bool VS_RearDoorIsPassive(const tVStateState * pVState);

//  #### Hood ####
// Hood/Bonnet Open (1=True; 0=False)
bool VS_GetHood(const tVStateState * pVState, bool * pValid);
// Hood/Bonnet Open (1=True; 0=False)
void VS_SetHood(tVStateState * pVState, bool Hood);
bool VS_HoodIsActive(const tVStateState * pVState);
bool VS_HoodIsPassive(const tVStateState * pVState);

//  #### Trunk ####
// Trunk/Boot Open (1=True; 0=False)
bool VS_GetTrunk(const tVStateState * pVState, bool * pValid);
// Trunk/Boot Open (1=True; 0=False)
void VS_SetTrunk(tVStateState * pVState, bool Trunk);
bool VS_TrunkIsActive(const tVStateState * pVState);
bool VS_TrunkIsPassive(const tVStateState * pVState);

//  #### OutAirTemp ####
// Outside Air Temperature (-40...87 deg C, E = N * 1 - 40)
int32_t VS_GetOutAirTemp(const tVStateState * pVState, bool * pValid);
// Outside Air Temperature (-40...87 deg C, E = N * 1 - 40)
void VS_SetOutAirTemp(tVStateState * pVState, int32_t OutAirTemp);

//  #### OutAirTemp ####
// vsc3
// Outside Air Temperature
int8_t VS_GetOutAirTemp_de(const tVStateState * pVState, bool * pValid);
// vsc3
// Outside Air Temperature
void VS_SetOutAirTemp_de(tVStateState * pVState, int8_t OutAirTemp_de);

//  #### OutAirTemp ####
// SI
float VS_GetOutAirTemp_deg(const tVStateState * pVState);
// SI
void VS_SetOutAirTemp_deg(tVStateState * pVState, float OutAirTemp_deg);

//  #### WiperRtFnt ####
// Wiper Rate Front (0...62, E = N * 2 (Sweeps per minute))
int32_t VS_GetWiperRtFnt(const tVStateState * pVState, bool * pValid);
// Wiper Rate Front (0...62, E = N * 2 (Sweeps per minute))
void VS_SetWiperRtFnt(tVStateState * pVState, int32_t WiperRtFnt);

//  #### WiperRtFnt ####
// vsc3
// Wiper Rate Front
uint16_t VS_GetWiperRtFnt_Sweep_per_min(const tVStateState * pVState, bool * pValid);
// vsc3
// Wiper Rate Front
void VS_SetWiperRtFnt_Sweep_per_min(tVStateState * pVState, uint16_t WiperRtFnt_Sweep_per_min);

//  #### WiperRtRear ####
// Wiper Rate Rear (0...62, E = N * 2 (Sweeps per minute))
int32_t VS_GetWiperRtRear(const tVStateState * pVState, bool * pValid);
// Wiper Rate Rear (0...62, E = N * 2 (Sweeps per minute))
void VS_SetWiperRtRear(tVStateState * pVState, int32_t WiperRtRear);

//  #### WiperRtRear ####
// vsc3
// Wiper Rate Rear
uint16_t VS_GetWiperRtRear_Sweep_per_min(const tVStateState * pVState, bool * pValid);
// vsc3
// Wiper Rate Rear
void VS_SetWiperRtRear_Sweep_per_min(tVStateState * pVState, uint16_t WiperRtRear_Sweep_per_min);

//  #### SpdLimAct ####
// Speed Limiter Active
bool VS_GetSpdLimAct(const tVStateState * pVState, bool * pValid);
// Speed Limiter Active
void VS_SetSpdLimAct(tVStateState * pVState, bool SpdLimAct);
bool VS_SpdLimActIsActive(const tVStateState * pVState);
bool VS_SpdLimActIsPassive(const tVStateState * pVState);

//  #### Odo ####
// Odometer reading (0...4294967295 m, E = N * 1)
int32_t VS_GetOdo(const tVStateState * pVState, bool * pValid);
// Odometer reading (0...4294967295 m, E = N * 1)
void VS_SetOdo(tVStateState * pVState, int32_t Odo);

//  #### Odo ####
// vsc3
// Odometer
uint32_t VS_GetOdo_m(const tVStateState * pVState, bool * pValid);
// vsc3
// Odometer
void VS_SetOdo_m(tVStateState * pVState, uint32_t Odo_m);

//  #### BmprHghtFnt ####
// Bumper Height Front (0...127 cm)
int32_t VS_GetBmprHghtFnt(const tVStateState * pVState, bool * pValid);
// Bumper Height Front (0...127 cm)
void VS_SetBmprHghtFnt(tVStateState * pVState, int32_t BmprHghtFnt);

//  #### BmprHghtFnt ####
// vsc3
// Bumper Height Front
uint16_t VS_GetBmprHghtFnt_cm(const tVStateState * pVState, bool * pValid);
// vsc3
// Bumper Height Front
void VS_SetBmprHghtFnt_cm(tVStateState * pVState, uint16_t BmprHghtFnt_cm);

//  #### BmprHghtRear ####
// Bumper Height Rear (0...127 cm)
int32_t VS_GetBmprHghtRear(const tVStateState * pVState, bool * pValid);
// Bumper Height Rear (0...127 cm)
void VS_SetBmprHghtRear(tVStateState * pVState, int32_t BmprHghtRear);

//  #### BmprHghtRear ####
// vsc3
// Bumper Height rear
uint16_t VS_GetBmprHghtRear_cm(const tVStateState * pVState, bool * pValid);
// vsc3
// Bumper Height rear
void VS_SetBmprHghtRear_cm(tVStateState * pVState, uint16_t BmprHghtRear_cm);

//  #### VehHght ####
// Vehicle Height (0...635 cm, E = N * 5)
int32_t VS_GetVehHght(const tVStateState * pVState, bool * pValid);
// Vehicle Height (0...635 cm, E = N * 5)
void VS_SetVehHght(tVStateState * pVState, int32_t VehHght);

//  #### VehHght ####
// vsc3
// Vehicle Height
uint16_t VS_GetVehHght_cm(const tVStateState * pVState, bool * pValid);
// vsc3
// Vehicle Height
void VS_SetVehHght_cm(tVStateState * pVState, uint16_t VehHght_cm);

//  #### VehMass ####
// Vehicle Mass (Kg, E = N * 50)
int32_t VS_GetVehMass(const tVStateState * pVState, bool * pValid);
// Vehicle Mass (Kg, E = N * 50)
void VS_SetVehMass(tVStateState * pVState, int32_t VehMass);

//  #### VehMass ####
// vsc3
// Vehicle Mass
unsigned VS_GetVehMass_kg(const tVStateState * pVState, bool * pValid);
// vsc3
// Vehicle Mass
void VS_SetVehMass_kg(tVStateState * pVState, unsigned VehMass_kg);

//  #### VehMass ####
// ASN-2016
uint8_t VS_GetVehMass_asn2016(const tVStateState * pVState, bool * pValid);
// ASN-2016
void VS_SetVehMass_asn2016(tVStateState * pVState, uint8_t VehMass_asn2016);

//  #### VehType ####
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
int32_t VS_GetVehType(const tVStateState * pVState, bool * pValid);
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
void VS_SetVehType(tVStateState * pVState, int32_t VehType);

//  #### CAN_GPS_BAD ####
// CAN GPS bad (i.e. disagrees with LPH)
bool VS_GetCAN_GPS_BAD(const tVStateState * pVState, bool * pValid);
// CAN GPS bad (i.e. disagrees with LPH)
void VS_SetCAN_GPS_BAD(tVStateState * pVState, bool CAN_GPS_BAD);
bool VS_CAN_GPS_BADIsActive(const tVStateState * pVState);
bool VS_CAN_GPS_BADIsPassive(const tVStateState * pVState);

//  #### Slow ####
bool VS_GetSlow(const tVStateState * pVState, bool * pValid);
void VS_SetSlow(tVStateState * pVState, bool Slow);
bool VS_SlowIsActive(const tVStateState * pVState);
bool VS_SlowIsPassive(const tVStateState * pVState);

//  #### DecelHard ####
bool VS_GetDecelHard(const tVStateState * pVState, bool * pValid);
void VS_SetDecelHard(tVStateState * pVState, bool DecelHard);
bool VS_DecelHardIsActive(const tVStateState * pVState);
bool VS_DecelHardIsPassive(const tVStateState * pVState);

//  #### Swerving ####
bool VS_GetSwerving(const tVStateState * pVState, bool * pValid);
void VS_SetSwerving(tVStateState * pVState, bool Swerving);
bool VS_SwervingIsActive(const tVStateState * pVState);
bool VS_SwervingIsPassive(const tVStateState * pVState);

//  #### Slope_deg8 ####
// raw is scaled by 8 hence the resolution 1/8 degree
int32_t VS_GetSlope_deg8(const tVStateState * pVState, bool * pValid);
// raw is scaled by 8 hence the resolution 1/8 degree
void VS_SetSlope_deg8(tVStateState * pVState, int32_t Slope_deg8);

//  #### Slope_deg8 ####
// degrees
float VS_GetSlope_deg8_deg(const tVStateState * pVState);
// degrees
void VS_SetSlope_deg8_deg(tVStateState * pVState, float Slope_deg8_deg);

//  #### Slope_deg8 ####
// radians
float VS_GetSlope_deg8_rad(const tVStateState * pVState);
// radians
void VS_SetSlope_deg8_rad(tVStateState * pVState, float Slope_deg8_rad);

//  #### LanePos ####
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
int32_t VS_GetLanePos(const tVStateState * pVState, bool * pValid);
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
void VS_SetLanePos(tVStateState * pVState, int32_t LanePos);

//  #### PerfClass ####
// Performance Class
// (0 unavailable, 1 performanceClassA, 2 performanceClassB, ...)
int32_t VS_GetPerfClass(const tVStateState * pVState, bool * pValid);
// Performance Class
// (0 unavailable, 1 performanceClassA, 2 performanceClassB, ...)
void VS_SetPerfClass(tVStateState * pVState, int32_t PerfClass);

//  #### YawRateConf ####
// Yaw Rate Confidence (0...655.35 deg/s, E = N * .01)
int32_t VS_GetYawRateConf(const tVStateState * pVState, bool * pValid);
// Yaw Rate Confidence (0...655.35 deg/s, E = N * .01)
void VS_SetYawRateConf(tVStateState * pVState, int32_t YawRateConf);

//  #### YawRateConf ####
// si
float VS_GetYawRateConf_deg_per_sec(const tVStateState * pVState);
// si
void VS_SetYawRateConf_deg_per_sec(tVStateState * pVState, float YawRateConf_deg_per_sec);

//  #### VisibilityRange ####
// Visible range in meters
int32_t VS_GetVisibilityRange(const tVStateState * pVState, bool * pValid);
// Visible range in meters
void VS_SetVisibilityRange(tVStateState * pVState, int32_t VisibilityRange);

//  #### VisibilityRange ####
// si
float VS_GetVisibilityRange_m(const tVStateState * pVState);
// si
void VS_SetVisibilityRange_m(tVStateState * pVState, float VisibilityRange_m);

//  #### LightBarInUse ####
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
int32_t VS_GetLightBarInUse(const tVStateState * pVState, bool * pValid);
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
void VS_SetLightBarInUse(tVStateState * pVState, int32_t LightBarInUse);

//  #### SirenInUse ####
// Siren In Use
// (emergency vehicles only)
// 0: Unavailable
// 1: NotInUse
// 2: InUse
// 3: Reserved
int32_t VS_GetSirenInUse(const tVStateState * pVState, bool * pValid);
// Siren In Use
// (emergency vehicles only)
// 0: Unavailable
// 1: NotInUse
// 2: InUse
// 3: Reserved
void VS_SetSirenInUse(tVStateState * pVState, int32_t SirenInUse);

//  #### AEB ####
// Autonomous Emergency Braking (AEB) System status
// (NOTE: 'On' means monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
int32_t VS_GetAEB(const tVStateState * pVState, bool * pValid);
// Autonomous Emergency Braking (AEB) System status
// (NOTE: 'On' means monitoring system is on but not engaged)
// 0: Unknown
// 1: Off
// 2: On
// 3: Engaged
// 4: Error
void VS_SetAEB(tVStateState * pVState, int32_t AEB);
bool VS_AEBIsActive(const tVStateState * pVState);
bool VS_AEBIsPassive(const tVStateState * pVState);

//  #### DrivingSide ####
// Which side of the road you drive on
// https://en.wikipedia.org/wiki/Right-_and_left-hand_traffic
// Left == AU, UK etc., Right == EU, US etc.
// 0: Unknown
// 1: Left
// 2: Right
int32_t VS_GetDrivingSide(const tVStateState * pVState, bool * pValid);
// Which side of the road you drive on
// https://en.wikipedia.org/wiki/Right-_and_left-hand_traffic
// Left == AU, UK etc., Right == EU, US etc.
// 0: Unknown
// 1: Left
// 2: Right
void VS_SetDrivingSide(tVStateState * pVState, int32_t DrivingSide);

//  #### Environment ####
// Local Road Environment
// 0: Unavailable
// 1: Unknown
// 2: Rural
// 3: Urban
int32_t VS_GetEnvironment(const tVStateState * pVState, bool * pValid);
// Local Road Environment
// 0: Unavailable
// 1: Unknown
// 2: Rural
// 3: Urban
void VS_SetEnvironment(tVStateState * pVState, int32_t Environment);

//  #### CoolantOverheat ####
// Engine Coolant Overheating
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetCoolantOverheat(const tVStateState * pVState, bool * pValid);
// Engine Coolant Overheating
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetCoolantOverheat(tVStateState * pVState, int32_t CoolantOverheat);

//  #### ElectricalSystemError ####
// Electrical System Error
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetElectricalSystemError(const tVStateState * pVState, bool * pValid);
// Electrical System Error
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetElectricalSystemError(tVStateState * pVState, int32_t ElectricalSystemError);

//  #### ElectricalSystemOverheat ####
// Electrical System Overheat
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetElectricalSystemOverheat(const tVStateState * pVState, bool * pValid);
// Electrical System Overheat
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetElectricalSystemOverheat(tVStateState * pVState, int32_t ElectricalSystemOverheat);

//  #### EngineOilPressureWarning ####
// Engine Oil Pressure Warning
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetEngineOilPressureWarning(const tVStateState * pVState, bool * pValid);
// Engine Oil Pressure Warning
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetEngineOilPressureWarning(tVStateState * pVState, int32_t EngineOilPressureWarning);

//  #### HybridSystemError ####
// Hybrid System Error
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetHybridSystemError(const tVStateState * pVState, bool * pValid);
// Hybrid System Error
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetHybridSystemError(tVStateState * pVState, int32_t HybridSystemError);

//  #### SteeringDefect ####
// Steering Defect
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetSteeringDefect(const tVStateState * pVState, bool * pValid);
// Steering Defect
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetSteeringDefect(tVStateState * pVState, int32_t SteeringDefect);

//  #### TransmissionOverheat ####
// Transmission Overheat
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetTransmissionOverheat(const tVStateState * pVState, bool * pValid);
// Transmission Overheat
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetTransmissionOverheat(tVStateState * pVState, int32_t TransmissionOverheat);

//  #### LowSpeedAccident ####
// Low-Speed Accident
// 0: unknown
// 1: off
// 2: active
// 3: error
int32_t VS_GetLowSpeedAccident(const tVStateState * pVState, bool * pValid);
// Low-Speed Accident
// 0: unknown
// 1: off
// 2: active
// 3: error
void VS_SetLowSpeedAccident(tVStateState * pVState, int32_t LowSpeedAccident);

//  #### LonAccelConf ####
// Longitudinal Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
int32_t VS_GetLonAccelConf(const tVStateState * pVState, bool * pValid);
// Longitudinal Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
void VS_SetLonAccelConf(tVStateState * pVState, int32_t LonAccelConf);

//  #### LonAccelConf ####
// si
// SI units
float VS_GetLonAccelConf_mps2(const tVStateState * pVState);
// si
// SI units
void VS_SetLonAccelConf_mps2(tVStateState * pVState, float LonAccelConf_mps2);

//  #### LatAccelConf ####
// Lateral Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
int32_t VS_GetLatAccelConf(const tVStateState * pVState, bool * pValid);
// Lateral Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
void VS_SetLatAccelConf(tVStateState * pVState, int32_t LatAccelConf);

//  #### LatAccelConf ####
// si
// SI units
float VS_GetLatAccelConf_mps2(const tVStateState * pVState);
// si
// SI units
void VS_SetLatAccelConf_mps2(tVStateState * pVState, float LatAccelConf_mps2);

//  #### VertAccelConf ####
// Vertical Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
int32_t VS_GetVertAccelConf(const tVStateState * pVState, bool * pValid);
// Vertical Acceleration Confidence (0.0...10.0 m/s/s, E = N * 0.01)
void VS_SetVertAccelConf(tVStateState * pVState, int32_t VertAccelConf);

//  #### VertAccelConf ####
// si
// SI units
float VS_GetVertAccelConf_mps2(const tVStateState * pVState);
// si
// SI units
void VS_SetVertAccelConf_mps2(tVStateState * pVState, float VertAccelConf_mps2);

//  #### DriveDirection ####
// Vehicle drive direction.
// 0: unknown
// 1: forward
// 2: backward
// 3: error
int32_t VS_GetDriveDirection(const tVStateState * pVState, bool * pValid);
// Vehicle drive direction.
// 0: unknown
// 1: forward
// 2: backward
// 3: error
void VS_SetDriveDirection(tVStateState * pVState, int32_t DriveDirection);

// -*- Mode:c -*-


static inline void VS_SetFogLghtsOn(tVStateState  *pVState, bool On)
{
  VS_SetFogLightsFront(pVState, On ? VS_FogLightsFront_driver : VS_FogLightsFront_off);
  VS_SetFogLightsRear (pVState, On ? VS_FogLightsRear_driver  : VS_FogLightsRear_off);
}

static inline bool VSTATE_IS_AVAIL_FogLghtsOn(const tVStateState  *pVState)
{
  bool Valid;
  uint32_t Mode = VS_GetFogLightsFront(pVState, &Valid);
  if (Valid && (Mode != VS_FogLightsFront_unknown))
  {
    return true;
  }
  Mode = VS_GetFogLightsRear(pVState, &Valid);
  if (Valid && (Mode != VS_FogLightsRear_unknown))
  {
    return true;
  }
  return false;
}

static inline bool VS_FogLghtsOnIsActive(const tVStateState  *pVState)
{
  bool Valid;
  uint32_t Mode = VS_GetFogLightsFront(pVState, &Valid);
  if (Valid && ((Mode == VS_FogLightsFront_active)
                ||
                (Mode == VS_FogLightsFront_driver)))
  {
    return true;
  }
  Mode = VS_GetFogLightsRear(pVState, &Valid);
  if (Valid && ((Mode == VS_FogLightsRear_active)
                ||
                (Mode == VS_FogLightsRear_driver)))
  {
    return true;
  }
  return false;
}

#ifdef __cplusplus
}
#endif

#endif // __VSTATE_GEN_H

// Close the doxygen group
/**
 * @}
 */
