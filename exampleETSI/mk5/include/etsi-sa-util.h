/**
 * @addtogroup ets_app_facilities_sa_api ETSI ITS Facilities SA API
 * @{
 *
 * Utilities to SA handling
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_SA_ETSI_SA_UTIL_H_
#define __ETSI_SA_ETSI_SA_UTIL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <inttypes.h>

#include "itsasn.h"
#include "itsasn_def.h"
#include "etsi-sa-if.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// define largest IPv6 address string
#define ETSISA_INET6_ADDRSTRLEN 46

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Set ITSAID in SAEM structure item
/// @param ITSAID ITSAID value to set
/// @param pServiceID Pointer to Service ID structure
/// @return 0 for success
int ETSISA_SetServiceIDITSAID(uint32_t ITSAID, ITSITSaid *pServiceID);

/// @brief Get ITSAID from SAEM structure item
/// @param pServiceID Pointer to Service ID structure
/// @param pITSAID Pointer to ITSAID store
/// @return 0 for success
int ETSISA_GetServiceIDITSAID(const ITSITSaid *pServiceID, uint32_t *pITSAID);

/// @brief Get Extension Item RepeatRate from SAEM structure item
/// @param pExt Pointer to Service Announcement extension
/// @param pRepeatRate Pointer to repeat rate storage
/// @return 0 for success
int ETSISA_GetBodyExtensionRepeatRate(const ITSSrvAdvMsgHeaderExts *pExt,
                                      ITSRepeatRate *pRepeatRate);

/// @brief Get Extension Item Location from SAEM structure item
/// @param pExt Pointer to Service Announcement extension
/// @param pLoc Pointer to location storage
/// @return 0 for success
int ETSISA_GetBodyExtensionLoc(const ITSSrvAdvMsgHeaderExts *pExt,
                               tETSISA_Loc *pLoc);

/// @brief Get Extension Item AdvertiserIdentifier from SAEM structure item
/// @param pExt Pointer to Service Announcement extension
/// @param pAdvId Pointer to AdvertiserIdentifier storage (assumed to be
// /       at least ITSAdvertiserIdentifier_NumOctets in size)
/// @return Length of AdvertiserIdentifier (or 0 for not found)
int ETSISA_GetBodyExtensionAdvId(const ITSSrvAdvMsgHeaderExts *pExt,
                                 uint8_t *pAdvId);

/// @brief Get ITS-AID specific Service Info item
/// @param pSrvInfo Pointer to SAEM Service Infos
/// @param ITSAID ITS AID of required service
/// @return Pointer to required service info (or NULL if not found)
const ITSServiceInfo *ETSISA_GetServiceInfo(const ITSServiceInfos *pSrvInfo,
                                            uint32_t ITSAID);

/// @brief Get ProtocolType extension from a particular Service Info Item
/// @param pSrvInfo Pointer to particular Service Info Item
/// @param pProtocol Pointer to ProtocolType storage
/// @return Pointer to required service info (or NULL if not found)
int ETSISA_GetServiceInfoProtocol(const ITSServiceInfo *pSrvInfo,
                                  tETSISAProtocolType *pProtocol);

/// @brief Get ProviderServiceContext extension from a particular Service Info Item
/// @param pSrvInfo Pointer to particular Service Info Item
/// @param pPSC Pointer to ProviderServiceContext storage (assumed to be
///        at least ETSISA_PSCMAX in size)
/// @return Length of ProviderServiceContext (or 0 for not found)
int ETSISA_GetServiceInfoPSC(const ITSServiceInfo *pSrvInfo,
                             uint8_t *pPSC);

/// @brief Get SAMapplicationData extension from a particular Service Info Item
/// @param pSrvInfo Pointer to particular Service Info Item
/// @param pAppData Pointer to SAMapplicationData storage (assumed to be
///        at least ETSISA_APPDATAMAX in size)
/// @return Length of SAMapplicationData (or 0 for not found)
int ETSISA_GetServiceInfoAppData(const ITSServiceInfo *pSrvInfo,
                                 uint8_t *pAppData);

/// @brief Fetch IPv6 address of provided network interface
/// @param IPv6Addr Pointer to buffer for IPv6 address
/// @param pInterface Pointer to network interface to query
/// @param Link Boolean request for Link-local address
/// @return Status

int ETSISA_FetchIPv6Addr(char IPv6Addr[ETSISA_INET6_ADDRSTRLEN], const char *pInterface, bool Link);

/// @brief Convert textual IPv6 address to hex array (for use in SAEM)
/// @param HexIPv6Addr Pointer to buffer for hex array
/// @param pIPv6Text Pointer to IPv6 address
/// @return Status

int ETSISA_HexifyIPv6Addr(uint8_t HexIPv6Addr[ITSIPv6Address_NumOctets], const char *pIPv6Text);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_SA_ETSI_SA_UTIL_H_

// Close the Doxygen group
/**
 * @}
 */
