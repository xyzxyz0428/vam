// -*- Mode:c -*-

#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum VStateQueueId
{
  VS_RMT_ABS,
  VS_RMT_BrkAct,
  VS_RMT_ParkingBrakeStatus,
  VS_RMT_TrcCtrl,
  VS_RMT_PRNDL,
  VS_RMT_DrvIntendedBrk,
  VS_RMT_StbCtrl,
  VS_RMT_Weather,
  VS_RMT_RoadType,
  VS_RMT_Separation,
  VS_RMT_EmergCallStatus,
  VS_RMT_ExtAirbagStatus,
  VS_RMT_AutoEngineShutdown,
  VS_RMT_AutoBrake,
  VS_RMT_Restraint,
  VS_RMT_BattVolt,
  VS_RMT_BrkPedalGrad,
  VS_RMT_BrkPedalPos,
  VS_RMT_YawRate,
  VS_RMT_StrWhlAngGrad,
  VS_RMT_StrWhlAng,
  VS_RMT_VehSpd,
  VS_RMT_VehSpdConf,
  VS_RMT_LatAccel,
  VS_RMT_PanicBrake,
  VS_RMT_BrakePreChg,
  VS_RMT_WiperSwRear,
  VS_RMT_AirbagStatus,
  VS_RMT_HighBeamStatus,
  VS_RMT_WiperSweepStatus,
  VS_RMT_WiperSwFnt,
  VS_RMT_SafetyWarningStatus,
  VS_RMT_LonAccel,
  VS_RMT_VertAccel,
  VS_RMT_LftTurnSig,
  VS_RMT_RtTurnSig,
  VS_RMT_CrusEngd,
  VS_RMT_CrusOvrd,
  VS_RMT_AccelPos,
  VS_RMT_VehWidth,
  VS_RMT_VehLength,
  VS_RMT_LowBeamStatus,
  VS_RMT_HzdLgts,
  VS_RMT_AutoLghtCntrlOn,
  VS_RMT_DtimeRunLghtsOn,
  VS_RMT_FogLightsFront,
  VS_RMT_FogLightsRear,
  VS_RMT_ReversingLights,
  VS_RMT_PkgLghtsOn,
  VS_RMT_CruiseSetSpeed,
  VS_RMT_WheelVelocityLF,
  VS_RMT_WheelVelocityRF,
  VS_RMT_WheelVelocityLR,
  VS_RMT_WheelVelocityRR,
  VS_RMT_TirePressureLF,
  VS_RMT_TirePressureRF,
  VS_RMT_TirePressureLR,
  VS_RMT_TirePressureRR,
  VS_RMT_DrvrSeatbelt,
  VS_RMT_PsngrSeatbelt,
  VS_RMT_PwrMode,
  VS_RMT_ACC,
  VS_RMT_Horn,
  VS_RMT_DrvrDoor,
  VS_RMT_WasherFront,
  VS_RMT_PsngrDoor,
  VS_RMT_RearDoor,
  VS_RMT_Hood,
  VS_RMT_Trunk,
  VS_RMT_OutAirTemp,
  VS_RMT_WiperRtFnt,
  VS_RMT_WiperRtRear,
  VS_RMT_SpdLimAct,
  VS_RMT_Odo,
  VS_RMT_BmprHghtFnt,
  VS_RMT_BmprHghtRear,
  VS_RMT_VehHght,
  VS_RMT_VehMass,
  VS_RMT_VehType,
  VS_RMT_CAN_GPS_BAD,
  VS_RMT_Slow,
  VS_RMT_DecelHard,
  VS_RMT_Swerving,
  VS_RMT_Slope_deg8,
  VS_RMT_LanePos,
  VS_RMT_PerfClass,
  VS_RMT_YawRateConf,
  VS_RMT_VisibilityRange,
  VS_RMT_LightBarInUse,
  VS_RMT_SirenInUse,
  VS_RMT_AEB,
  VS_RMT_DrivingSide,
  VS_RMT_Environment,
  VS_RMT_CoolantOverheat,
  VS_RMT_ElectricalSystemError,
  VS_RMT_ElectricalSystemOverheat,
  VS_RMT_EngineOilPressureWarning,
  VS_RMT_HybridSystemError,
  VS_RMT_SteeringDefect,
  VS_RMT_TransmissionOverheat,
  VS_RMT_LowSpeedAccident,
  VS_RMT_LonAccelConf,
  VS_RMT_LatAccelConf,
  VS_RMT_VertAccelConf,
  VS_RMT_DriveDirection,
  VS_RMT_UNAVAILABLE = 0x800000,
} tVStateQueueId;

typedef struct VStateQueueElem
{
  tVStateQueueId Id;
  int32_t        Raw;
} tVStateQueueElem;

void VS_RmtSetABS(int32_t ABS);
void VS_RmtSetBrkAct(bool BrkAct);
void VS_RmtSetParkingBrakeStatus(int32_t ParkingBrakeStatus);
void VS_RmtSetTrcCtrl(int32_t TrcCtrl);
void VS_RmtSetPRNDL(int32_t PRNDL);
void VS_RmtSetPRNDL_asn2016(unsigned /*SAETransmissionState*/ PRNDL_asn2016);
void VS_RmtSetDrvIntendedBrk(int32_t DrvIntendedBrk);
void VS_RmtSetDrvIntendedBrk_kpa(float DrvIntendedBrk_kpa);
void VS_RmtSetDrvIntendedBrk_percent(uint16_t DrvIntendedBrk_percent);
void VS_RmtSetStbCtrl(int32_t StbCtrl);
void VS_RmtSetWeather(int32_t Weather);
void VS_RmtSetRoadType(int32_t RoadType);
void VS_RmtSetSeparation(int32_t Separation);
void VS_RmtSetEmergCallStatus(bool EmergCallStatus);
void VS_RmtSetExtAirbagStatus(bool ExtAirbagStatus);
void VS_RmtSetAutoEngineShutdown(bool AutoEngineShutdown);
void VS_RmtSetAutoBrake(int32_t AutoBrake);
void VS_RmtSetRestraint(int32_t Restraint);
void VS_RmtSetBattVolt(int32_t BattVolt);
void VS_RmtSetBattVolt_V(float BattVolt_V);
void VS_RmtSetBrkPedalGrad(int32_t BrkPedalGrad);
void VS_RmtSetBrkPedalGrad_percent_per_s(int16_t BrkPedalGrad_percent_per_s);
void VS_RmtSetBrkPedalPos(int32_t BrkPedalPos);
void VS_RmtSetBrkPedalPos_percent(uint16_t BrkPedalPos_percent);
void VS_RmtSetYawRate(int32_t YawRate);
void VS_RmtSetYawRate_deg_per_s(float YawRate_deg_per_s);
void VS_RmtSetYawRate_rad_per_s(float YawRate_rad_per_s);
void VS_RmtSetYawRate_asn2016(int16_t YawRate_asn2016);
void VS_RmtSetStrWhlAngGrad(int32_t StrWhlAngGrad);
void VS_RmtSetStrWhlAngGrad_deg_per_s(int16_t StrWhlAngGrad_deg_per_s);
void VS_RmtSetStrWhlAngGrad_asn2016(int StrWhlAngGrad_asn2016);
void VS_RmtSetStrWhlAng(int32_t StrWhlAng);
void VS_RmtSetStrWhlAng_deg(float StrWhlAng_deg);
void VS_RmtSetStrWhlAng_asn2016(int StrWhlAng_asn2016);
void VS_RmtSetVehSpd(int32_t VehSpd);
void VS_RmtSetVehSpd_kph(float VehSpd_kph);
void VS_RmtSetVehSpd_mps(float VehSpd_mps);
void VS_RmtSetVehSpd_mmpnm(float VehSpd_mmpnm);
void VS_RmtSetVehSpd_asn2016(int32_t VehSpd_asn2016);
void VS_RmtSetVehSpdConf(int32_t VehSpdConf);
void VS_RmtSetVehSpdConf_mps(float VehSpdConf_mps);
void VS_RmtSetLatAccel(int32_t LatAccel);
void VS_RmtSetLatAccel_m_per_s_per_s(float LatAccel_m_per_s_per_s);
void VS_RmtSetLatAccel_mps2(float LatAccel_mps2);
void VS_RmtSetLatAccel_mmpnm2(float LatAccel_mmpnm2);
void VS_RmtSetLatAccel_asn2016(int16_t LatAccel_asn2016);
void VS_RmtSetPanicBrake(bool PanicBrake);
void VS_RmtSetBrakePreChg(int32_t BrakePreChg);
void VS_RmtSetWiperSwRear(int32_t WiperSwRear);
void VS_RmtSetAirbagStatus(bool AirbagStatus);
void VS_RmtSetHighBeamStatus(bool HighBeamStatus);
void VS_RmtSetWiperSweepStatus(bool WiperSweepStatus);
void VS_RmtSetWiperSwFnt(int32_t WiperSwFnt);
void VS_RmtSetSafetyWarningStatus(bool SafetyWarningStatus);
void VS_RmtSetLonAccel(int32_t LonAccel);
void VS_RmtSetLonAccel_m_per_s_per_s(float LonAccel_m_per_s_per_s);
void VS_RmtSetLonAccel_mmpnm2(float LonAccel_mmpnm2);
void VS_RmtSetLonAccel_asn2016(int16_t LonAccel_asn2016);
void VS_RmtSetVertAccel(int32_t VertAccel);
void VS_RmtSetVertAccel_m_per_s_per_s(float VertAccel_m_per_s_per_s);
void VS_RmtSetVertAccel_mmpnm2(float VertAccel_mmpnm2);
void VS_RmtSetVertAccel_asn2016(int8_t VertAccel_asn2016);
void VS_RmtSetLftTurnSig(bool LftTurnSig);
void VS_RmtSetRtTurnSig(bool RtTurnSig);
void VS_RmtSetCrusEngd(bool CrusEngd);
void VS_RmtSetCrusOvrd(bool CrusOvrd);
void VS_RmtSetAccelPos(int32_t AccelPos);
void VS_RmtSetAccelPos_percent(uint16_t AccelPos_percent);
void VS_RmtSetVehWidth(int32_t VehWidth);
void VS_RmtSetVehWidth_m(float VehWidth_m);
void VS_RmtSetVehWidth_vsc3(uint16_t VehWidth_vsc3);
void VS_RmtSetVehWidth_dm(uint16_t VehWidth_dm);
void VS_RmtSetVehWidth_cm(uint16_t VehWidth_cm);
void VS_RmtSetVehWidth_mm(uint32_t VehWidth_mm);
void VS_RmtSetVehLength(int32_t VehLength);
void VS_RmtSetVehLength_m(float VehLength_m);
void VS_RmtSetVehLength_vsc3(uint16_t VehLength_vsc3);
void VS_RmtSetVehLength_dm(uint16_t VehLength_dm);
void VS_RmtSetVehLength_cm(uint16_t VehLength_cm);
void VS_RmtSetVehLength_mm(uint32_t VehLength_mm);
void VS_RmtSetLowBeamStatus(bool LowBeamStatus);
void VS_RmtSetHzdLgts(bool HzdLgts);
void VS_RmtSetAutoLghtCntrlOn(bool AutoLghtCntrlOn);
void VS_RmtSetDtimeRunLghtsOn(bool DtimeRunLghtsOn);
void VS_RmtSetFogLightsFront(int32_t FogLightsFront);
void VS_RmtSetFogLightsRear(int32_t FogLightsRear);
void VS_RmtSetReversingLights(int32_t ReversingLights);
void VS_RmtSetPkgLghtsOn(bool PkgLghtsOn);
void VS_RmtSetCruiseSetSpeed(int32_t CruiseSetSpeed);
void VS_RmtSetCruiseSetSpeed_kph(uint16_t CruiseSetSpeed_kph);
void VS_RmtSetWheelVelocityLF(int32_t WheelVelocityLF);
void VS_RmtSetWheelVelocityLF_kph(float WheelVelocityLF_kph);
void VS_RmtSetWheelVelocityRF(int32_t WheelVelocityRF);
void VS_RmtSetWheelVelocityRF_kph(float WheelVelocityRF_kph);
void VS_RmtSetWheelVelocityLR(int32_t WheelVelocityLR);
void VS_RmtSetWheelVelocityLR_kph(float WheelVelocityLR_kph);
void VS_RmtSetWheelVelocityRR(int32_t WheelVelocityRR);
void VS_RmtSetWheelVelocityRR_kph(float WheelVelocityRR_kph);
void VS_RmtSetTirePressureLF(int32_t TirePressureLF);
void VS_RmtSetTirePressureLF_psi(uint16_t TirePressureLF_psi);
void VS_RmtSetTirePressureLF_kpa(uint16_t TirePressureLF_kpa);
void VS_RmtSetTirePressureRF(int32_t TirePressureRF);
void VS_RmtSetTirePressureRF_psi(uint16_t TirePressureRF_psi);
void VS_RmtSetTirePressureRF_kpa(uint16_t TirePressureRF_kpa);
void VS_RmtSetTirePressureLR(int32_t TirePressureLR);
void VS_RmtSetTirePressureLR_psi(uint16_t TirePressureLR_psi);
void VS_RmtSetTirePressureLR_kpa(uint16_t TirePressureLR_kpa);
void VS_RmtSetTirePressureRR(int32_t TirePressureRR);
void VS_RmtSetTirePressureRR_psi(uint16_t TirePressureRR_psi);
void VS_RmtSetTirePressureRR_kpa(uint16_t TirePressureRR_kpa);
void VS_RmtSetDrvrSeatbelt(int32_t DrvrSeatbelt);
void VS_RmtSetPsngrSeatbelt(int32_t PsngrSeatbelt);
void VS_RmtSetPwrMode(int32_t PwrMode);
void VS_RmtSetACC(bool ACC);
void VS_RmtSetHorn(bool Horn);
void VS_RmtSetDrvrDoor(int32_t DrvrDoor);
void VS_RmtSetWasherFront(int32_t WasherFront);
void VS_RmtSetPsngrDoor(int32_t PsngrDoor);
void VS_RmtSetRearDoor(int32_t RearDoor);
void VS_RmtSetHood(bool Hood);
void VS_RmtSetTrunk(bool Trunk);
void VS_RmtSetOutAirTemp(int32_t OutAirTemp);
void VS_RmtSetOutAirTemp_de(int8_t OutAirTemp_de);
void VS_RmtSetOutAirTemp_deg(float OutAirTemp_deg);
void VS_RmtSetWiperRtFnt(int32_t WiperRtFnt);
void VS_RmtSetWiperRtFnt_Sweep_per_min(uint16_t WiperRtFnt_Sweep_per_min);
void VS_RmtSetWiperRtRear(int32_t WiperRtRear);
void VS_RmtSetWiperRtRear_Sweep_per_min(uint16_t WiperRtRear_Sweep_per_min);
void VS_RmtSetSpdLimAct(bool SpdLimAct);
void VS_RmtSetOdo(int32_t Odo);
void VS_RmtSetOdo_m(uint32_t Odo_m);
void VS_RmtSetBmprHghtFnt(int32_t BmprHghtFnt);
void VS_RmtSetBmprHghtFnt_cm(uint16_t BmprHghtFnt_cm);
void VS_RmtSetBmprHghtRear(int32_t BmprHghtRear);
void VS_RmtSetBmprHghtRear_cm(uint16_t BmprHghtRear_cm);
void VS_RmtSetVehHght(int32_t VehHght);
void VS_RmtSetVehHght_cm(uint16_t VehHght_cm);
void VS_RmtSetVehMass(int32_t VehMass);
void VS_RmtSetVehMass_kg(unsigned VehMass_kg);
void VS_RmtSetVehMass_asn2016(uint8_t VehMass_asn2016);
void VS_RmtSetVehType(int32_t VehType);
void VS_RmtSetCAN_GPS_BAD(bool CAN_GPS_BAD);
void VS_RmtSetSlow(bool Slow);
void VS_RmtSetDecelHard(bool DecelHard);
void VS_RmtSetSwerving(bool Swerving);
void VS_RmtSetSlope_deg8(int32_t Slope_deg8);
void VS_RmtSetSlope_deg8_deg(float Slope_deg8_deg);
void VS_RmtSetSlope_deg8_rad(float Slope_deg8_rad);
void VS_RmtSetLanePos(int32_t LanePos);
void VS_RmtSetPerfClass(int32_t PerfClass);
void VS_RmtSetYawRateConf(int32_t YawRateConf);
void VS_RmtSetYawRateConf_deg_per_sec(float YawRateConf_deg_per_sec);
void VS_RmtSetVisibilityRange(int32_t VisibilityRange);
void VS_RmtSetVisibilityRange_m(float VisibilityRange_m);
void VS_RmtSetLightBarInUse(int32_t LightBarInUse);
void VS_RmtSetSirenInUse(int32_t SirenInUse);
void VS_RmtSetAEB(int32_t AEB);
void VS_RmtSetDrivingSide(int32_t DrivingSide);
void VS_RmtSetEnvironment(int32_t Environment);
void VS_RmtSetCoolantOverheat(int32_t CoolantOverheat);
void VS_RmtSetElectricalSystemError(int32_t ElectricalSystemError);
void VS_RmtSetElectricalSystemOverheat(int32_t ElectricalSystemOverheat);
void VS_RmtSetEngineOilPressureWarning(int32_t EngineOilPressureWarning);
void VS_RmtSetHybridSystemError(int32_t HybridSystemError);
void VS_RmtSetSteeringDefect(int32_t SteeringDefect);
void VS_RmtSetTransmissionOverheat(int32_t TransmissionOverheat);
void VS_RmtSetLowSpeedAccident(int32_t LowSpeedAccident);
void VS_RmtSetLonAccelConf(int32_t LonAccelConf);
void VS_RmtSetLonAccelConf_mps2(float LonAccelConf_mps2);
void VS_RmtSetLatAccelConf(int32_t LatAccelConf);
void VS_RmtSetLatAccelConf_mps2(float LatAccelConf_mps2);
void VS_RmtSetVertAccelConf(int32_t VertAccelConf);
void VS_RmtSetVertAccelConf_mps2(float VertAccelConf_mps2);
void VS_RmtSetDriveDirection(int32_t DriveDirection);


/**
 * Client-Side (stub) prototypes.
 */
// provide this when instantiating the stub on the client to forward requests to the server
typedef void (fVS_ForwardRequests)(void * pBuff, size_t Len);

// Flush the queue of updates to the server
void VS_RmtFlush(void);
// Initialise the Stub Interface on the client.
int VS_RemoteStubInit(fVS_ForwardRequests * pVS_ForwardRequests);
// Shut down the Stub Interface on the client.
void VS_RemoteStubExit(void);


/**
 * Server-Side (skel) prototypes.
 */
// call this on the server to process remote updates
int VS_ProcessRequests(void * pBuf, size_t Len);

// Initialise the Skeleton on the server
int  VS_RemoteSkelInit(void);
// Shut down the Skeleton on the server
void VS_RemoteSkelExit(void);

#ifdef UNITTEST
struct VStateState;
void VS_ProcessQueue(struct VStateState * pVState, void * pPriv);
#endif

#ifdef __cplusplus
}
#endif
