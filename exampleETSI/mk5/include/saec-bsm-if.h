/**
 * @addtogroup saec_app_facilities_bsm_api SAEC Facilities BSM API
 * @{
 *
 * Interface to BSM handling
 *
 * There is limited control to the BSM generation as these are periodically
 * generated from in-built rules as per the specification. There are some
 * configuration items that can be set to adjust the BSM generation, also the
 * maximum BSM interval can be adjusted dynamically.
 *
 * The BSM reception is handled by the BSM handler which validates the BSM
 * construction and then provides the decoded BSM structure to clients
 * via the EXT interface. The client subscribes to QSMSG_EXT_RX_SAECFL_PDU
 * events and can identify the PDU from pType.
 *
 * @code
 *
 * #include "saecasn.h"
 * #include "saecasn_def.h"
 * #include "ext.h"
 *
 * void BSMRxExtCallback(tExtEventId Event,
 *                       tExtMessage *pData,
 *                       void *pPriv)
 * {
 *   (void)pPriv; // My private data
 *
 *   switch (Event)
 *   {
 *     case QSMSG_EXT_RX_SAECFL_PDU:
 *     {
 *       // Check pType
 *       if (pData->pType == asn1_type_SAECBasicSafetyMessage)
 *       {
 *         SAECBasicSafetyMessage *pBSM = pData->pSAECBSM;
 *
 *         // Parse some data
 *         printf("Message Count is %zu\n", pBSM->msgCnt);
 *
 *         // Send BSM to handling application
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
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_BSM_SAEC_BSM_IF_H_
#define __SAEC_BSM_SAEC_BSM_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "saecasn.h"

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

/// BSM Status codes
typedef enum SAECBSMStatusCode
{
  /// BSM success
  SAECBSM_SUCCESS = 0x00,
  /// BSM some parameters invalid
  SAECBSM_FAILURE_INVALID_PARAM = 0x01,
  /// BSM limits exceeded in structure
  SAECBSM_FAILURE_CONSTRAINT = 0x02,
  /// BSM generation failure
  SAECBSM_FAILURE = 0x03,

} eSAECBSMStatusCode;

/// BSM Dynamic information
typedef struct SAECBSMInfo
{
  /// BSM StationId
  uint32_t stationID;

} tSAECBSMInfo;

/// @ref SAECBSMStatusCode
typedef uint8_t tSAECBSMStatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Adjust maximum interval between BSMs
/// @param Interval required maximum interval in milliseconds (up to 65535)
/// @return BSM Status Code
tSAECBSMStatusCode SAECBSM_AdjustMaxInterval(uint16_t Interval);

/// @brief Acquire current BSM dynamic information
/// @return BSM dynamic information
tSAECBSMInfo SAECBSM_GetCurrentInfo(void);

/**
 * @brief Set up the emergency extension to use in outgoing BSMs
 * @param pEmergencyExt Supplied extensions
 * @return 0 on success. Negative on errors.
 */
int SAECBSM_SetEmergencyExt(const SAECVehicleEmergencyExtensions * pEmergencyExt);

/**
 * @brief Set up the vehicle event flags to use in outgoing BSMs
 * @param pEventFlags Supplied flags
 * @return 0 on success. Negative on errors.
 */
int SAECBSM_SetVehicleEventFlags(const SAECVehicleEventFlags * pEventFlags);

/**
 * @brief Set up the vehicle class classification to use in outgoing BSMs
 * @param pClassification Supplied classification
 * @return 0 on success. Negative on errors.
 */
int SAECBSM_SetVehicleClassification(const SAECVehicleClassification * pClassification);

/**
 * @brief Set up the brake system status to use in outgoing BSMs
 * @param pBrakes Supplied status
 * @return 0 on success. Negative on errors.
 */
int SAECBSM_SetBrakeSystemStatus(const SAECBrakeSystemStatus * pBrakes);

/**
 * @brief Start BSM Service
 *
 * Start BSM sevice (if not automatically started)
 * @return BSM Status Code
 */
uint8_t SAECBSM_ServiceStart(void);

/**
 * @brief Stop BSM Service
 * @return BSM Status Code
 */
uint8_t SAECBSM_ServiceStop(void);

#ifdef __cplusplus
}
#endif

#endif // __SAEC_BSM_SAEC_BSM_IF_H_

// Close the Doxygen group
/**
 * @}
 */
