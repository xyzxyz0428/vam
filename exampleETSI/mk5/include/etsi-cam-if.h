/**
 * @addtogroup ets_app_facilities_cam_api ETSI ITS Facilities CAM API
 * @{
 *
 * EN 302 637-2 V1.4.1
 *
 * Interface to CAM handling
 *
 * There is limited control to the CAM generation as these are periodically
 * generated from in-built rules as per the specification. There are some
 * configuration items that can be set to adjust the CAM generation, also the
 * maximum CAM interval can be adjusted dynamically.
 *
 * The CAM reception is handled by the CAM handler which validates the CAM
 * construction and then provides the decoded CAM structure to clients
 * via the EXT interface. The client subscribes to QSMSG_EXT_RX_ITSFL_PDU
 * events and can identify the PDU from the ItsPduHeader.
 *
 * @code
 *
 * #include "itsasn.h"
 * #include "itsasn_def.h"
 * #include "ext.h"
 *
 * void CAMRxExtCallback(tExtEventId Event,
 *                       tExtMessage *pData,
 *                       void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_ITSFL_PDU:
 *     {
 *       // Check PDU header
 *       if (pData->pPDU->messageID == ITSItsPduHeaderMessageID_ID_cam)
 *       {
 *         ITSCAM *pCamPdu = pData->pCAM;
 *
 *         // Parse some data
 *         printf("Station is 0x%08x\n", pCamPdu->header.stationID);
 *
 *         // Send CAM to handling application
 *       }
 *     }
 *
 *     default:
 *       // Other events
 *       break;
 *   }
 * }
 *
 * @endcode
 *
 * The CAM elements are populated thus:
 *
 *
 * |Item|Origination in System|
 * |----|---------------------|
 * |B.1 header|CONSTANT protocolVersion = 1;CONSTANT messageID = 2;stationID taken from Facilities Layer station ID, set from configuration file, or from security ID management depending on options. Also test mode where stationID is taken from IPv4 address of host machine’s network interface.|
 * |B.2 cam|-|
 * |B.3 generationDeltaTime|LPH time of GPS position update (OBU) or system time (RSU)|
 * |B.4 camParameters|-|
 * |B.5 basicContainer|Automatic|
 * |B.6 highFrequencyContainer|Automatic|
 * |B.7 lowFrequencyContainer|Automatic|
 * |B.8 specialVehicleContainer|API CAM_ActivateSpecialRole()|
 * |B.9 basicVehicleContainerHighFrequency|Automatic (Configuration item ItsGnIsMobile = 1)|
 * |B.10 basicVehicleContainerLowFrequency|Automatic (Configuration item ItsGnIsMobile = 1)|
 * |B.11 publicTransportContainer|API CAM_ActivateSpecialRole()|
 * |B.12 specialTransportContainer|API CAM_ActivateSpecialRole()|
 * |B.13 dangerousGoodsContainer|API CAM_ActivateSpecialRole()|
 * |B.14 roadWorksContainerBasic|API CAM_ActivateSpecialRole()|
 * |B.15 rescueContainer|API CAM_ActivateSpecialRole()|
 * |B.16 emergencyContainer|API CAM_ActivateSpecialRole()|
 * |B.17 safetyCarContainer|API CAM_ActivateSpecialRole()|
 * |B.18 stationType|Configuration item ItsGnStationType|
 * |B.19 referencePosition|LPH GPS position|
 * |B.20 performanceClass|VSTATE item PerfClass|
 * |B.21 heading|LPH GPS heading|
 * |B.22 speed|LPH GPS speed or VSTATE VehSpd (depending on Configuration)|
 * |B.23 vehicleRole|Configuration item ItsCamVehicleRole and via API CAM_ActivateSpecialRole()|
 * |B.24 lanePosition|VSTATE item LanePos|
 * |B.25 driveDirection|VSTATE item DriveDirection or deduced from VSTATE item PRNDL|
 * |B.26 longitudinalAcceleration|VSTATE item LonAccel|
 * |B.27 accelerationControl|VSTATE items BrkAct, AccelPos, (PanicBrake\|AEB), SafetyWarningStatus, ACC, CrusEngd, SpdLimAct|
 * |B.28 lateralAcceleration|VSTATE item LatAccel|
 * |B.29 verticalAcceleration|VSTATE item VertAccel|
 * |B.30 embarkationStatus|API CAM_ActivateSpecialRole()|
 * |B.31 curvature|LPH path prediction item RadiusOfCurve|
 * |B.32 curvatureCalculationMode|CONSTANT ITSCurvatureCalculationMode_yawRateUsed|
 * |B.33 yawRate|VSTATE item YawRate|
 * |B.34 steeringWheelAngle|VSTATE item StrWhlAng|
 * |B.35 vehicleLength|VSTATE item VehicleLength|
 * |B.36 vehicleWidth|VSTATE item VehicleWidth|
 * |B.37 exteriorLights|VSTATE items LowBeamStatus, HighBeamStatus, LftTurnSig, RtTurnSig, DtimeRunLghtsOn, FogLightsRear, PkgLghtsOn, ReversingLights|
 * |B.38 pathHistory|LPH path history|
 * |B.39 ptActivation|API CAM_ActivateSpecialRole()|
 * |B.40 specialTransportType|API CAM_ActivateSpecialRole()|
 * |B.41 dangerousGoodsBasic|API CAM_ActivateSpecialRole()|
 * |B.42 roadworksSubCauseCode|API CAM_ActivateSpecialRole()|
 * |B.43 closedLanes|API CAM_ActivateSpecialRole()|
 * |B.44 trafficRule|API CAM_ActivateSpecialRole()|
 * |B.45 speedLimit|API CAM_ActivateSpecialRole()|
 * |B.46 lightBarSirenInUse|VSTATE items LightBarInUse, SirenInUse when API CAM_ActivateSpecialRole() is used|
 * |B.47 incidentIndication|API CAM_ActivateSpecialRole()|
 * |B.48 emergencyPriority|API CAM_ActivateSpecialRole()|
 * |B.49 rsuContainerHighFrequency|Automatic (Configuration item ItsGnIsMobile = 0)|
 * |B.50 protectedCommunicationZonesRSU|API CAM_RSUProtCommsZones()|
 * |B.51 cenDsrcTollingZone|API CAM_VehTollingZone()|
 * |B.52 protectedZoneLatitude|API CAM_RSUProtCommsZones() or CAM_VehTollingZone|
 * |B.53 protectedZoneLongitude|API CAM_RSUProtCommsZones() or CAM_VehTollingZone|
 * |     emissions|API CAM_VehicleEmissionCont()|
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_CAM_ETS_CAM_IF_H_
#define __ETS_CAM_ETS_CAM_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "itsasn.h"

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

/// CAM Status codes
typedef enum CAMStatusCode
{
  /// CAM success
  CAM_SUCCESS = 0x00,
  /// CAM some parameters invalid
  CAM_FAILURE_INVALID_PARAM = 0x01,
  /// CAM limits exceeded in structure
  CAM_FAILURE_CONSTRAINT = 0x02,
  /// CAM generation failure
  CAM_FAILURE = 0x03,

} eCAMStatusCode;

/// CAM Dynamic information
typedef struct CAMInfo
{
  /// CAM StationId
  uint32_t stationID;
  /// CAM Vehicle role (ITSVehicleRole)
  uint8_t role;

} tCAMInfo;

/// Status code for CAM actions @ref CAMStatusCode
typedef uint8_t tCAMStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Start CAM Service sending (if not automatically started)
/// @return CAM Status Code
tCAMStatusCode CAM_ServiceStart(void);

/// @brief Stop CAM Service sending
/// @return CAM Status Code
tCAMStatusCode CAM_ServiceStop(void);

/// @brief Update CAM special role and special vehicle container information
/// @param role Vehicle role to activate
/// @param pSpecial Special vehicle container information
/// (note: this Special vehicle information is only used for certain roles,
///        set to NULL if not appropriate for this role or if APP-layer
///        doesn't provide information in which case FAC-layer will populate
///        any possible fields based on current vehicle state information)
/// @return CAM Status Code
tCAMStatusCode CAM_ActivateSpecialRole(ITSVehicleRole role, const ITSSpecialVehicleContainer *pSpecial);

/// @brief Clear CAM special role (return to default value)
/// (note: if the configured default role is the same as the role that was
///        activated, then the deactivate has no effect)
/// @return CAM Status Code
tCAMStatusCode CAM_DeactivateSpecialRole(void);

/// @brief Update CAM RSU Protected Communication Zones structure for transmission
/// @param pRsuCont RSU Container information (or NULL for no information)
/// (note: this structure is only used in CAM when ItsGnIsMobile is false)
/// @return CAM Status Code
tCAMStatusCode CAM_RSUProtCommsZones(const ITSProtectedCommunicationZonesRSU *pRsuCont);

/// @brief Update CAM Vehicle Tolling Zone for transmission
/// @param pVehCont Vehicle Tolling Container information (or NULL for no information)
/// (note: this structure is only used in CAM when ItsGnIsMobile is true)
/// @return CAM Status Code
tCAMStatusCode CAM_VehTollingZone(const ITSCenDsrcTollingZone *pVehCont);

/// @brief Update (optional) CAM Vehicle Emission Container for transmission
/// @param pEmissionCont Emission Container information (or NULL for no information)
/// (note: this structure is only used in CAM when ItsGnIsMobile is true)
/// @return CAM Status Code
tCAMStatusCode CAM_VehicleEmissionCont(const ITSEmissionContainer *pEmissionCont);

/// @brief Adjust maximum interval between CAMs
/// @param Interval required maximum interval in milliseconds (up to 65535)
/// @return CAM Status Code
tCAMStatusCode CAM_AdjustMaxInterval(uint16_t Interval);

/// @brief Adjust the minimum CAM DCC transmission interval
/// @param Interval required DCC interval in milliseconds (up to 65535)
/// @return CAM Status Code
tCAMStatusCode CAM_AdjustDccInterval(uint16_t Interval);

/// @brief Acquire current CAM dynamic information
/// @return CAM dynamic information
tCAMInfo CAM_GetCurrentInfo(void);

/// @brief Update CAM Platooning enabled and joinable state
/// @param Enable Platooning is enabled
/// @param Joinable State to update
/// @return CAM Status Code
tCAMStatusCode CAM_UpdatePlatooningJoinableState(bool Enable, bool Joinable);

#ifdef __cplusplus
}
#endif

#endif // __ETS_CAM_ETS_CAM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
