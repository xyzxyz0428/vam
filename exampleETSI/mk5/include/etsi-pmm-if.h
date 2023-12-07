/**
 * @addtogroup ets_app_facilities_pmm_api ETSI ITS Facilities PMM API
 * @{
 *
 * Interface to Platoon Management Message handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_PMM_ETSI_PMM_IF_H_
#define __ETSI_PMM_ETSI_PMM_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include "etsi-fac-common.h"

#include "itsasn.h"
#include "itsasn_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Platoon ID (octets) 
#define ETSIPCMCW_PLATOONIDLEN ITSPlatoonID_NumOctets

/// Platoon ID (octets) 
#define ETSIPCMCW_VEHICLEIDLEN (ITSPlatoonVehicleID_NumOctets)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// PMM management
typedef struct PMMMgmt
{
  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;

} tPMMMgmt;

/// PCM management
typedef struct PCMMgmt
{
  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;

} tPCMMgmt;

/// PMM Status codes
typedef enum PMMStatusCode
{
  /// PMM success
  ETSIPMM_SUCCESS = 0x00,
  /// PMM generation failure
  ETSIPMM_FAILURE = 0x01,
  /// PMM some parameters invalid
  ETSIPMM_FAILURE_INVALID_PARAMS = 0x04,
  /// PMM limits exceeded in structure
  ETSIPMM_FAILURE_CONSTRAINT = 0x05,
  /// PMM failed to encode
  ETSIPMM_FAILURE_ENCODING = 0x06,
  /// PMM not ready
  ETSIPMM_FAILURE_NOT_READY = 0x07,

} ePMMStatusCode;

/// Status code for PMM actions @ref PMMStatusCode
typedef uint8_t tPMMStatusCode;

/// CW PCM Message
/// NOTE: PCM modified since CW implementation
/// Many fields now not included in PCM
typedef struct PCMCWMsg
{
  /// Sequence number
  uint32_t SeqNo;
  /// Number Of Trucks
  uint8_t NumberTrucks;
  /// Position of ego vehicle in Platoon
  uint8_t PlatoonPosition;
  /// Vehicle ID string (ID is 11-20 bytes)
  char VehicleID[ETSIPCMCW_VEHICLEIDLEN+1];
  /// Platoon ID octet string (ID is 16 octets)
  uint8_t PlatoonID[ETSIPCMCW_PLATOONIDLEN];
  /// Vehicle in front flag
  bool VehicleInFront;
  /// ID string of Vehicle in front (ID is 11-20 bytes)
  uint8_t VehicleInFrontID[ETSIPCMCW_VEHICLEIDLEN+1];
  /// Distance to vehicle in front in centimetres
  uint16_t DistanceToVehicleAhead_cm;
  /// Speed of vehicle in front
  uint32_t SpeedOfVehicleAhead;
  /// About to leave flag
  bool AboutToLeave;
  /// About to leave in front flag
  bool ReadyToLeaveInFront;

} tPCMCWMsg;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Trigger Platoon Management Message
/// @param pMgmt Pointer to PMM management information
/// @param pPmm Pointer to PMM message content
/// @return PMM Status Code
tPMMStatusCode ETSIPMM_SendPMM(const tPMMMgmt* pMgmt, 
                               const ITSPlatoonManagementContainer* pPmm);

/// @brief Trigger Platoon Control Message
/// @param pMgmt Pointer to PCM management information
/// @param pPcm Pointer to PlatoonControlContainer structure containing PCM message fields to update
/// @return PCM Status Code
tPMMStatusCode ETSIPMM_SendPCM(const tPCMMgmt* pMgmt, 
                               const ITSPlatoonControlContainer* pPcm);
                               
/// @brief Trigger Platoon Control Message (CW parameters)
/// @param pMgmt Pointer to PCM management information
/// @param pPcm Pointer to CW control structure containing PCM message fields to update
/// @return PCM Status Code
tPMMStatusCode ETSIPMM_SendPCMCW(const tPCMMgmt* pMgmt, 
                                 const tPCMCWMsg* pPcm);


#ifdef __cplusplus
}
#endif


#endif //__ETSI_PMM_ETSI_PMM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
