/**
 * @addtogroup ets_app_facilities_sa_api ETSI ITS Facilities SA API
 * @{
 *
 * EN 302 890-1 V1.2.1
 *
 * Interface to SA handling
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_SA_ETSI_SA_IF_H_
#define __ETSI_SA_ETSI_SA_IF_H_

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

/// Max service infos per SaID
#define ETSISA_SERIVICE_INFO_MAX 4

/// Max ITS-AID list size
#define ETSISA_AIDLIST_MAX 15

/// Maximum SA application data size
#define ETSISA_APPDATAMAX 256

/// Maximum SA PSC size
#define ETSISA_PSCMAX 31

/// Maximum SA repetition (in seconds) - one year
#define ETSISA_REPETITIONDURATIONMAX (60 * 60 * 24 * 365)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// SA Protocol type
typedef enum ETSISAProtocolType
{
  /// Protocol stack unknown
  ETSISA_PROTOCOL_TYPE_UNKNOWN = 0,
  /// Any protocol stack as desired by the service user
  ETSISA_PROTOCOL_TYPE_ANY = 1,
  /// A protocol stack featuring the networking protocol: Wave Short Message Protocol according to IEEE 1609.3
  ETSISA_PROTOCOL_TYPE_WSMP = 2,
  /// A protocol stack featuring the networking protocol: Geonetworking and the transport protocol: Basic Transport Protocol
  ETSISA_PROTOCOL_TYPE_GN = 3,
  /// A protocol stack featuring the networking protocol: Internet Protocol Version 6 "IPv6" and the transport protocol: Transmission Control Protocol
  ETSISA_PROTOCOL_TYPE_IPV6 = 6,
  /// Max allowed value
  ETSISA_PROTOCOL_TYPE_MAX = 50,
} eETSISAProtocolType;

/// SA Protocol type value @ref ETSISAProtocolType
typedef uint8_t tETSISAProtocolType;

/// SA Request type
typedef enum ETSISAReqType
{
  /// Registration
  ETSISA_REQUEST_REGISTRATION = 1,
  /// Update
  ETSISA_REQUEST_UPDATE = 2,
  /// Deregistration
  ETSISA_REQUEST_DEREGISTRATION = 3,
} eETSISAReqType;

/// SA Request type value @ref ETSISAReqType
typedef uint8_t tETSISAReqType;

/// SA Service
typedef struct SAService
{
  /// Id of protocol stack to be used, e.g. ETSISA_PROTOCOL_TYPE_GN
  /// Use ETSISA_PROTOCOL_TYPE_UNKNOWN to not include this item in SA
  uint8_t ProtId;

  /// Channel Index to be used, e.g. ITSChannelIndex_firstEntry
  /// Use ITSChannelIndex_notUsed to not include this item in SA
  uint8_t ChannelIndex;

  /// ITS-AID of service
  uint32_t ITSAID;

  /// Provider Service Context data
  uint8_t PSC[ETSISA_PSCMAX];
  /// Provider Service Context of service len (optional set length if not required,
  /// otherwise min 1, max ETSISA_PSCMAX)
  uint16_t PSCLen;

  /// Application data
  /// Application data used when ApplicationDataLen is not 0
  uint8_t ApplicationData[ETSISA_APPDATAMAX];
  /// Application data length (max ETSISA_APPDATAMAX)
  uint16_t ApplicationDataLen;

  /// IPv6 parameters used when ETSISA_PROTOCOL_TYPE_IPV6 is set
  /// SA IPv6 address (TBD)
  uint8_t IPv6Addr[ITSIPv6Address_NumOctets];
  /// SA IPv6 port (optional, 0 for none) (TBD)
  uint16_t IPv6Port;
} tSAService;

/// SA message
typedef struct SAMsg
{
  /// Request type
  tETSISAReqType ReqType;

  /// Number of services in this request
  uint8_t ServiceCount;
  /// Service Information
  tSAService Service[ETSISA_SERIVICE_INFO_MAX];

  /// Inclusion of Repeat Rate
  bool IncRptRate;
  /// Inclusion of 3D location
  bool Inc3DLoc;
  /// Inclusion of 2D location (if not including 3D location)
  bool Inc2DLoc;
  /// Advertiser Identifier (optional, NULL for none, ASCII string, max length ITSAdvertiserIdentifier_NumOctets-1 i.e. 31)
  const char *pAdvID;
} tSAMsg;

/// SA location
typedef struct ETSISA_Loc
{
  /// Tenths of micro-degrees
  int32_t Longitude;
  /// Tenths of micro-degrees
  int32_t Latitude;
  /// 0.1 metres
  int32_t Elevation;
} tETSISA_Loc;

/// SA ITS-AID list
typedef struct ETSISA_AIDList
{
  /// All ITS-AIDs
  uint32_t AID[ETSISA_AIDLIST_MAX];
} tETSISA_AIDList;

/// SA Information
typedef struct ETSISA_Info
{
  /// Number of services
  uint8_t NumAID;
  /// List of services
  tETSISA_AIDList AIDList;

  /// AdvertiserIdentifier length (in octets)
  int AdvIdLen;
  /// AdvertiserIdentifier octet sequence (not necessarily ASCII!)
  uint8_t AdvId[ITSAdvertiserIdentifier_NumOctets];

  /// Location status
  int LocStatus;
  /// Location
  tETSISA_Loc Loc;

  /// RepeatRate status
  int RepeatRateStatus;
  /// RepeatRate
  ITSRepeatRate RepeatRate;
} tETSISA_Info;

/// SA management
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ETSISA_REPETITIONDURATIONMAX or
///       equal to ETSIFAC_REPETITIONDURATIONFOREVER for endless repetition
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct SAMgmt
{
  /// Repetition Duration (sec), ETSIFAC_REPETITIONDURATIONNONE for none
  uint32_t RepetitionDuration;
  /// Repetition Interval (mS), ETSIFAC_REPETITIONINTERVALNONE for none
  uint16_t RepetitionInterval;

  /// Comms Profile
  tETSIFACGNProfile CommsProfile;
  /// Traffic Class
  tETSIFACGNTC TrafficClass;
} tSAMgmt;

/// SA Status codes
typedef enum SAStatusCode
{
  /// SA success
  ETSISA_SUCCESS = 0x00,
  /// SA generation failure
  ETSISA_FAILURE = 0x01,
  /// SA some parameters invalid
  ETSISA_FAILURE_INVALID_PARAMS = 0x04,
  /// SA failed to encode
  ETSISA_FAILURE_ENCODING = 0x05,
  /// SA generation not ready
  ETSISA_FAILURE_NOT_READY = 0x06,
  /// SA failure to modify services
  ETSISA_FAILURE_SERVICE_MOD = 0x07,
  /// SA failed permissions consistency
  ETSISA_FAILURE_PERMISSIONS = 0x08,

} eSAStatusCode;

/// Status code for SA actions @ref SAStatusCode
typedef uint8_t tSAStatusCode;

/// saID
typedef uint8_t tSAIdNum;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Update periodic SA
/// @param pMgmt Pointer to SA management structure
/// @param pSAMsg Pointer to SA message content
/// @param SaID Identifier of SA
/// @return SA Status Code
tSAStatusCode ETSISA_ProviderUpdateSA(const tSAMgmt *pMgmt, const tSAMsg *pSAMsg, tSAIdNum SaID);

/// @brief User query in SA
/// @param pSaPdu Pointer to SA
/// @param pInfo Pointer to SA information elements
/// @return SA Status Code
tSAStatusCode ETSISA_UserInfoSA(const ITSSAEM *pSaPdu, tETSISA_Info* pInfo);

/// @brief User query in SA
/// @param pSaPdu Pointer to SA
/// @param AID Applicatiuon ID to query in SA
/// @param pService Pointer to SA service info for ITSAID
/// @return SA Status Code
tSAStatusCode ETSISA_UserQuerySA(const ITSSAEM *pSaPdu, uint32_t AID, tSAService *pService);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_SA_ETSI_SA_IF_H_

// Close the Doxygen group
/**
 * @}
 */
