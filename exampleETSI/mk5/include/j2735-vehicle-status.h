/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_vsd Vehicle Status Description
 * ASN.1 BER encoding and decoding of J2735 Vehicle Status.
 *
 * @file j2735-vehicle-status.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_VEHICLE_STATUS_H_
#define __J2735_VEHICLE_STATUS_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

// Don't rely on the include hierarchy as that creates portability issues.
// If your code below uses a type definition: explicitly include the header that
// defines that type
#include "j2735asn.h" /* SAEBasicSafetyMessage ASN.1 type */

#include "j2735-common.h"
#include "j2735-full-position-vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------


/**
 * @brief config for Optional Fields Vehicle Status
 *
 * This struct captures all the optional fields in Vehicle Status. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 *
 */

typedef struct VehicleStatusConfig
{
  /// VS_ExteriorLights element
  unsigned int VS_ExteriorLights:1;
  /// VS_LightBarInUse element
  unsigned int VS_LightBarInUse:1;
  /// VS_Wipers element
  unsigned int VS_Wipers:1;
  /// VS_Wipers_WiperStatusRear element
  unsigned int VS_Wipers_WiperStatusRear:1;
  /// VS_Wipers_WiperRateRear element
  unsigned int VS_Wipers_WiperRateRear:1;
  /// VS_BrakeSystemStatus element
  unsigned int VS_BrakeSystemStatus:1;
  /// VS_BrakePressure element
  unsigned int VS_BrakePressure:1;
  /// VS_RoadFriction element
  unsigned int VS_RoadFriction:1;
  /// VS_SunData element
  unsigned int VS_SunData:1;
  /// VS_RainData element
  unsigned int VS_RainData:1;
  /// VS_AirTemp element
  unsigned int VS_AirTemp:1;
  /// VS_AirPressure element
  unsigned int VS_AirPressure:1;
  /// VS_Steering element
  unsigned int VS_Steering:1;
  /// VS_SteeringConfidence element
  unsigned int VS_SteeringConfidence:1;
  /// VS_SteeringRate element
  unsigned int VS_SteeringRate:1;
  /// VS_SteeringWheels element
  unsigned int VS_SteeringWheels:1;
  /// VS_AccelSets element
  unsigned int VS_AccelSets:1;
  /// VS_AccelSets_Accel4way element
  unsigned int VS_AccelSets_Accel4way:1;
  /// VS_AccelSets_VertAceelThres element
  unsigned int VS_AccelSets_VertAceelThres:1;
  /// VS_AccelSets_YawRateCon element
  unsigned int VS_AccelSets_YawRateCon:1;
  /// VS_AccelSets_HozAccelCon element
  unsigned int VS_AccelSets_HozAccelCon:1;
  /// VS_AccelSets_ConfidenceSet element
  unsigned int VS_AccelSets_ConfidenceSet:1;
  /// VS_AccelSets_ConfidenceSet_AccelConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_AccelConfidence:1;
  /// VS_AccelSets_ConfidenceSet_SpeedConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_SpeedConfidence:1;
  /// VS_AccelSets_ConfidenceSet_TimeConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_TimeConfidence:1;
  /// VS_AccelSets_ConfidenceSet_PosConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_PosConfidence:1;
  /// VS_AccelSets_ConfidenceSet_SteerConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_SteerConfidence:1;
  /// VS_AccelSets_ConfidenceSet_ThrottleConfidence element
  unsigned int VS_AccelSets_ConfidenceSet_ThrottleConfidence:1;
  /// VS_Objects element
  unsigned int VS_Objects:1;
  /// VS_FullPos element
  unsigned int VS_FullPos:1;
  // Full position config
  tSAEFullPositionVectorCfg VS_FullPosCfg;
  /// VS_Throttlepos element
  unsigned int VS_Throttlepos:1;
  /// VS_SpeedHeadc element
  unsigned int VS_SpeedHeadC:1;
  /// VS_Speedc element
  unsigned int VS_Speedc:1;
  /// VS_Vehicledata element
  unsigned int VS_Vehicledata:1;
  /// VS_Vehicleident element
  unsigned int VS_Vehicleident:1;
  /// VS_Vehicleident_Name element
  unsigned int VS_Vehicleident_Name:1;
  /// VS_Vehicleident_Vin element
  unsigned int VS_Vehicleident_Vin:1;
  /// VS_Vehicleident_OwnerCode element
  unsigned int VS_Vehicleident_OwnerCode:1;
  /// VS_Vehicleident_Id element
  unsigned int VS_Vehicleident_Id:1;
  /// VS_Vehicleident_VehicleType element
  unsigned int VS_Vehicleident_VehicleType:1;
  /// VS_Vehicleident_VehicleClass element
  unsigned int VS_Vehicleident_VehicleClass:1;
  /// VS_J1939Data element
  unsigned int VS_J1939Data:1;
  /* continue here ...more optionals inside J2939data */
  /// VS_WeatherReport element
  unsigned int VS_WeatherReport:1;
  /// VS_WeatherReport_RainRate element
  unsigned int VS_WeatherReport_RainRate:1;
  /// VS_WeatherReport_PrecipSituation element
  unsigned int VS_WeatherReport_PrecipSituation:1;
  /// VS_WeatherReport_SolarRadiation element
  unsigned int VS_WeatherReport_SolarRadiation:1;
  /// VS_WeatherReport_Friction element
  unsigned int VS_WeatherReport_Friction:1;
  /// VS_GnssStatus element
  unsigned int VS_GnssStatus:1;
  // Lengths of the variable size fields.
  unsigned int VS_Vehicleident_Name_len;
  unsigned int VS_Vehicleident_Vin_len;
  unsigned int VS_Vehicleident_OwnerCode_len;
} tVehicleStatusConfig;



//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735VehicleStatus_Create(SAEVehicleStatus *pVehicleStatus,
                              const tVehicleStatusConfig *pConfig);

int J2735VehicleStatus_Free(SAEVehicleStatus *pVehicleStatus,
                            tJ2735FreeOption FreeOption);

#ifdef __cplusplus
}
#endif

#endif // __J2735_VEHICLE_STATUS_H_
// Close the doxygen group
/**
 * @}
 */
