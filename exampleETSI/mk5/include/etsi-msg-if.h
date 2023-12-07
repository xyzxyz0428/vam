/**
 * @addtogroup ets_app_facilities_msg_api ETSI ITS Facilities MSG API
 * @{
 *
 * Interface to manage Generic Message packet generation and handling
 *
 * The client can send an ITS MSG packet the configured BTP port by using this
 * API. The relevant sending parameters can be set by the client.
 *
 * The ITS MSG packet reception is handled by the MSG handler which passes the
 * MSG packet to clients via a callback function. If no callback is provided to
 * @ref ETSIMSG_OpenInterface then the MSG packet is sent via EXT interface
 * as tExtMessage.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_MSG_ETS_MSG_IF_H_
#define __ETS_MSG_ETS_MSG_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#include "etsi-fac-common.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Define max allowed MSG payload
#define ETSIMSG_MAX_PAYLOAD_LEN 2000 // bytes

/// Maximum MSG repetition (in seconds) - one year
#define ETSIMSG_REPETITIONDURATIONMAX (60 * 60 * 24 * 365)

/// Define max allowed custom SSP size (octets)
#define ETSIMSG_SSP_MAX_LEN 32 // bytes

/// Ensure MSG action ID is within 48-bits
#define ETSIMSG_ACTIONID(UniqueId) ((uint64_t)(UniqueId & 0xFFFFFFFFFFFF))

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Security information passed to the MSG API for custom security settings
typedef struct ETSIMSGSecInfo
{
  /// SSP Len (number of octets of SSP bits)
  uint8_t SSPLen;
  /// SSP bitmap in use
  bool SSPBitmap;
  /// ITS-AID (numerical value, i.e. not encoded in any way)
  uint32_t AID;
  /// SSP Bits (up to ETSIMSG_SSP_MAX_LEN octets)
  uint8_t SSPBits[ETSIMSG_SSP_MAX_LEN];
  /// SSP Mask (up to ETSIMSG_SSP_MAX_LEN octets)
  uint8_t SSPMask[ETSIMSG_SSP_MAX_LEN];
} tETSIMSGSecInfo;

/// MSG packet request information
/// @note Both RepetitionDuration and RepetitionInterval need to be non-zero for repetition
/// @note RepetitionDuration needs to be less than ETSIMSG_REPETITIONDURATIONMAX
/// @note RepetitionInterval needs to be between ETSIFAC_REPETITIONINTERVALMINMS
///       and ETSIFAC_REPETITIONINTERVALMAXMS
/// @note To immediately terminate a repetition, set RepetitionDuration to ETSIFAC_REPETITIONDURATIONNONE
///       and RepetitionInterval to ETSIFAC_REPETITIONINTERVALTERMINATE
typedef struct ETSIMSGReqMgmt
{
  /// Identifier
  uint64_t ID;

  /// Repetition Duration (sec), ETSIFAC_REPETITIONDURATIONNONE for none
  uint32_t RepetitionDuration;
  /// Repetition Interval (mS), ETSIFAC_REPETITIONINTERVALNONE for none
  uint16_t RepetitionInterval;

  /// BTP Destination port
  uint16_t DestPort;
  /// BTP Destination port info/source port
  uint16_t DestInfo;

  /// BTP Type
  tETSIFACBTPType BTPType;

  /// GN Packet transport type @ref ETSIFACGeoNetTransport
  tETSIFACGeoNetTransport PktTransport;

  /// GN Location for GeoUnicast (only used for GUC transport)
  tETSIFACGeoNetAddr Address;

  /// GN Area for GeoBroadcast or GeoAnycast (only used for GBC/GAC)
  tETSIFACGeoNetArea Area;

  /// GN Communication Profile
  tETSIFACGNProfile CommProfile;
  /// GN Traffic Class
  tETSIFACGNTC TrafficClass;
  /// GN HopLimit
  tETSIFACGNHopLimit HopLimit;
  /// GN Maximum packet lifetime (milli-seconds).
  uint32_t MaxPktLifetime;

  /// G5 Channel Type
  tETSIFACGNChanType ChanType;

  /// Security Information
  tETSIFACGNSecProf SecControl;
  /// Optional custom SSP & AID information
  tETSIMSGSecInfo SecInfo;

} tETSIMSGReqMgmt;

/// MSG packet indication information
typedef struct ETSIMSGIndMgmt
{
  /// BTP Destination port
  uint16_t DestPort;
  /// BTP Destination port info/source port
  uint16_t DestInfo;

  /// BTP Type
  tETSIFACBTPType BTPType;

  /// GN Packet transport type @ref ETSIFACGeoNetTransport
  tETSIFACGeoNetTransport PktTransport;

  /// GN Destination address for GeoUnicast (only used for GUC transport)
  tETSIFACGeoNetAddr Address;

  /// GN Source Position
  tETSIFACGeoNetPos SrcPos;

  /// GN Traffic Class
  tETSIFACGNTC TrafficClass;

  /// GN Remaining packet lifetime (milli-seconds).
  uint32_t RemainPktLifetime;

} tETSIMSGIndMgmt;

/// Status code for MSG packet sending
typedef enum ETSIMSGStatusCode
{
  /// MSG generation success
  ETSIMSG_SUCCESS = 0x00,
  /// MSG generation failure
  ETSIMSG_FAILURE_GENERATION = 0x01,
  /// MSG ActionID invalid
  ETSIMSG_FAILURE_INVALID_ACTION_ID = 0x02,
  /// MSG configuration failure
  ETSIMSG_FAILURE_CONFIGURATION = 0x03,
  /// MSG some parameters invalid
  ETSIMSG_FAILURE_INVALID_PARAMS = 0x04,
  /// MSG generation not ready
  ETSIMSG_FAILURE_NOT_READY = 0x07,

} eETSIMSGStatusCode;

/// Status code for MSG actions @ref ETSIMSGStatusCode
typedef int16_t tETSIMSGStatusCode;

/// Handle code for MSG port opening
typedef int16_t tETSIMSGHandleCode;

/// @brief Callback function for MSG packet handler
/// @param pETSIMSGInd pointer to MSG information (only valid for duration of callback)
/// @param pPayload pointer to Payload (only valid for duration of callback)
/// @param Length Length of the payload
/// @return 0 for success
typedef int (*fMSGPacketIndCallback)(
  const tETSIMSGIndMgmt *pETSIMSGInd,
  const uint8_t *pPayload,
  uint16_t Length);

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Open MSG BTP port for packet receiving
/// @param DestPort port number to open (BTP packets with this destination port received)
/// @param pInd callback function, or NULL to use EXT interface
/// @return Handle to identify this client, or negative for failure status code
tETSIMSGHandleCode ETSIMSG_OpenInterface (uint16_t DestPort, fMSGPacketIndCallback pInd);

/// @brief Close MSG BTP port
/// @param Handle Handle to identify this client
/// @return MSG Status Code
tETSIMSGStatusCode ETSIMSG_CloseInterface (tETSIMSGHandleCode Handle);

/// @brief Trigger MSG packet sending
/// @param pETSIMSGReq Msg packet sending paramters
/// @param pPayload Pointer to payload data
/// @param Length Length in octets
/// @return MSG Status Code
tETSIMSGStatusCode ETSIMSG_SendPacket(const tETSIMSGReqMgmt *pETSIMSGReq,
                                      const uint8_t *pPayload,
                                      uint16_t Length);

#ifdef __cplusplus
}
#endif

#endif // __ETS_MSG_ETS_MSG_IF_H_

// Close the Doxygen group
/**
 * @}
 */
