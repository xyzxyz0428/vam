/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_vse Vehicle Safety Extension
 * ASN.1 BER encoding and decoding of J2735 Vehicle safety extension.
 *
 * @file j2735-vehicle-safetyextension.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R36_Source.ASN
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_VEHICLE_SAFETY_EXTENSION_H_
#define __J2735_VEHICLE_SAFETY_EXTENSION_H_

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

// Configuration for vehicle status elements
typedef struct VehicleSafetyExtensionConfig
{

  /// VSE_EventFlags element
  unsigned int VSE_EventFlags:1;
  /// VSE_SAEPathHistory element
  unsigned int VSE_SAEPathHistory:1;
  /// VSE_PH_SAEFullPositionVector element
  unsigned int VSE_PH_SAEFullPositionVector:1;
  /// VSE_PH_FullPositionVecotor config
  tSAEFullPositionVectorCfg VSE_PH_FPV_Config;
  /// VSE_PH_GpsStatus element
  unsigned int VSE_PH_GpsStatus:1;
  /// VSE_PH_Count element
  unsigned int VSE_PH_Count:5;
  /// VSE_PH_PointType element
  unsigned int VSE_PH_PointType:3;
  /// VSE_SAEPathPrediction element
  unsigned int VSE_SAEPathPrediction:1;
  /// VSE_RTCMPackage element
  unsigned int VSE_RTCMPackage:1;
  /// VSE_RTCM_SAEFullPositionVector element
  unsigned int VSE_RTCM_SAEFullPositionVector:1;
  /// VSE_RTCM_FullPositionVecotor config
  tSAEFullPositionVectorCfg VSE_RTCM_FPV_Config;
  /// VSE_RTCM_Msg1001 element
  unsigned int VSE_RTCM_Msg1001:1;
  /// VSE_RTCM_Msg1002 element
  unsigned int VSE_RTCM_Msg1002:1;
  /// VSE_RTCM_Msg1003 element
  unsigned int VSE_RTCM_Msg1003:1;
  /// VSE_RTCM_Msg1004 element
  unsigned int VSE_RTCM_Msg1004:1;
} tVehicleSafetyExtensionConfig;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735VehicleSafetyExtension_Create(SAEVehicleSafetyExtensions *pSafetyExt,
                                       const tVehicleSafetyExtensionConfig *pConfig);

int J2735VehicleSafetyExtension_Free(SAEVehicleSafetyExtensions *pSafetyExt,
                                     tJ2735FreeOption FreeOption);

#ifdef __cplusplus
}
#endif

#endif // __J2735_VEHICLE_SAFETY_EXTENSION_H_
// Close the doxygen group
/**
 * @}
 */
