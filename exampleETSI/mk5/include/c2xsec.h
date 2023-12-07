/**
 * @addtogroup c2x_sec ETSI ITS Network Security elements
 * @{
 *
 * Module code for Security Data and Internal Control
 *
 * @file
 *
 */

#ifndef __IF_SEC_C2X_SEC_H__
#define __IF_SEC_C2X_SEC_H__

//------------------------------------------------------------------------------
// Copyright (c) 2013 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

// NOTE: ITS-AIDs are a numerical value, they are not encoded in any way

/// EN3026372 defined CAM AID (36)
#define C2XSEC_ITS_AID_CAM 0x24

/// EN3026373 defined DENM AID (37)
#define C2XSEC_ITS_AID_DENM 0x25

/// TS103301 defined SPAT AID (137)
#define C2XSEC_ITS_AID_SPAT 0x89

/// TS103301 defined MAP AID (138)
#define C2XSEC_ITS_AID_MAP 0x8a

/// TS103301 defined IVI AID (139)
#define C2XSEC_ITS_AID_IVI 0x8b

/// TS103301 defined SRM AID (140)
#define C2XSEC_ITS_AID_SRM 0x8c

/// EN30263641 defined GN AID (141)
#define C2XSEC_ITS_AID_GN 0x8d

/// TS102941 defined CRL AID (622)
#define C2XSEC_ITS_AID_CRL 0x026e

/// TS102941 defined SCR AID (623)
#define C2XSEC_ITS_AID_SCR 0x026f

/// TS102941 defined CTL AID (624)
#define C2XSEC_ITS_AID_CTL 0x0270

/// ISO17426 defined CSPEED AID (626)
#define C2XSEC_ITS_AID_CSPEED 0x0272

/// TS103301 defined SSM AID (637)
#define C2XSEC_ITS_AID_SSM 0x27d

/// TS1033002 defined VRU AID (638)
#define C2XSEC_ITS_AID_VRU 0x027e

/// TS103324 defined CPM AID (639)
#define C2XSEC_ITS_AID_CPM 0x027f

/// TS103724 defined IMZ AID (640)
#define C2XSEC_ITS_AID_IMZ 0x0280

/// ENSEMBLE defined PMM AID (1023)
#define C2XSEC_ITS_AID_PMM 0x03ff

/// EN3028901 defined SA AID (540801)
#define C2XSEC_ITS_AID_SA 0x084081

/// TS103301 defined GPC AID (540802)
#define C2XSEC_ITS_AID_GPC 0x084082

/// IEEE1609.3 defined IPv6 ROUTING AID (270549118)
#define C2XSEC_ITS_AID_IPV6_ROUTING 0x1020407e

/// Define size (in bytes) of CAM SSP bits
#define C2XSEC_CAM_SSP_LEN 3

/// Define size (in bytes) of DENM SSP bits
#define C2XSEC_DENM_SSP_LEN 4

/// Define size (in bytes) of SPAT SSP bits
#define C2XSEC_SPAT_SSP_LEN 2

/// Define size (in bytes) of MAP SSP bits
#define C2XSEC_MAP_SSP_LEN 2

/// Define size (in bytes) of IVI SSP bits
#define C2XSEC_IVI_SSP_LEN 6

/// Define size (in bytes) of SRM SSP bits
#define C2XSEC_SRM_SSP_LEN 4

/// Define size (in bytes) of SSM SSP bits
#define C2XSEC_SSM_SSP_LEN 1

/// Define size (in bytes) of VRU SSP bits
#define C2XSEC_VRU_SSP_LEN 1

/// Define size (in bytes) of CPM SSP bits
#define C2XSEC_CPM_SSP_LEN 1

/// Define size (in bytes) of IMZ SSP bits
#define C2XSEC_IMZ_SSP_LEN 10

/// Define size (in bytes) of PMM SSP bits
#define C2XSEC_PMM_SSP_LEN 0

/// Define minimum size (in bytes) of SA SSP bits
#define C2XSEC_SA_SSP_MIN_LEN 1

/// Define size (in bytes) of GPC SSP bits
#define C2XSEC_GPC_SSP_LEN 1

/// Define size (in bytes) of GN SSP bits
#define C2XSEC_GN_SSP_LEN 0

/// Define size (in bytes) of CRL SSP bits
#define C2XSEC_CRL_SSP_LEN 2

/// Define size (in bytes) of SCR SSP bits
#define C2XSEC_SCR_SSP_LEN 2

/// Define size (in bytes) of CTL SSP bits
#define C2XSEC_CTL_SSP_LEN 2

/// Maximum number of octets for SSP bits
#define C2XSEC_SSP_BITS_MAX_LEN 32

/// SSP version 0
#define C2XSEC_SSP_VER_0 0x00
/// SSP version 1
#define C2XSEC_SSP_VER_1 0x01
/// SSP version 2
#define C2XSEC_SSP_VER_2 0x02

/// Max failures to track
#define NUM_LAST_FAILS_LOG 10

/// Mask for ID change clients
#define C2XSEC_IDCHANGE_CLIENTS_MASK 0x3F

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Security information
typedef enum C2XSEC_SecType
{
  /// Clear packet (no security information)
  C2XSEC_PKT_CLEAR = 0x00,
  /// Secure packet
  C2XSEC_PKT_SECURE = 0x01,
  /// Certificate attached
  C2XSEC_PKT_SECURE_CERT = 0x02,
} eC2XSEC_SecType;

/// @ref C2XSEC_SecType
typedef uint8_t tC2XSEC_SecType;

/// Result code telling the caller whether parser recognized the message format
typedef enum C2XSEC_ParserResult
{
  /// Parsing was OK
  C2XSEC_PARSE_OK = 0,
  /// Parsing failed
  C2XSEC_PARSE_NOT_OK = 1,
  /// Parsing found wrong type
  C2XSEC_PARSE_WRONG_TYPE = 2,

  /// Parsing not done
  C2XSEC_PARSE_NOT_DONE = 255
} eC2XSEC_ParserResult;

/// @ref C2XSEC_ParserResult
typedef uint8_t tC2XSEC_ParserResult;

/// Result of the verification
/// Standardised values from ETSI EN 302 636-4-1
typedef enum C2XSEC_VerificationResult
{
  /// Verification was OK
  C2XSEC_VERIFY_SUCCESS = 0,
  /// Signature is invalid
  C2XSEC_VERIFY_FALSE_SIGNATURE = 1,
  /// Certificate is invalid
  C2XSEC_VERIFY_INVALID_CERTIFICATE = 2,
  /// Certificate is revoked
  C2XSEC_VERIFY_REVOKED_CERTIFICATE = 3,
  /// Certificate chain inconsistent
  C2XSEC_VERIFY_INCONSISTENT_CHAIN = 4,
  /// Time in message invalid
  C2XSEC_VERIFY_INVALID_TIMESTAMP = 5,
  /// Duplicate message (replay)
  C2XSEC_VERIFY_DUPLICATE_MESSAGE = 6,
  /// Invalid mobility data
  C2XSEC_VERIFY_INVALID_MOBILITY_DATA = 7,
  /// Message is unsigned
  C2XSEC_VERIFY_UNSIGNED_MESSAGE = 8,
  /// Signer certificate not found
  C2XSEC_VERIFY_SIGNER_CERTIFICATE_NOT_FOUND = 9,
  /// Signer identifier type is not supported
  C2XSEC_VERIFY_UNSUPPORTED_SIGNER_IDENTIFIER_TYPE = 10,
  /// Certificate protocol not supported
  C2XSEC_VERIFY_INCOMPATIBLE_PROTOCOL = 11,
  /// Message is unencrypted
  C2XSEC_VERIFY_UNENCRYPTED_MESSAGE = 12,
  /// Decryption error
  C2XSEC_VERIFY_DECRYPTION_ERROR = 13,

  /// Smart verification says not to verifiy
  C2XSEC_VERIFY_SMART_SAYS_NO = 250,
  /// No position
  C2XSEC_VERIFY_NO_POSITION = 251,
  /// Some other error
  C2XSEC_VERIFY_OTHER_ERROR = 252,
  /// Verification started, not completed
  C2XSEC_VERIFY_ONGOING = 253,
  /// Verification skipped
  C2XSEC_VERIFY_SKIPPED = 254,
  /// Verification not done
  C2XSEC_VERIFY_NOT_DONE = 255
} eC2XSEC_VerificationResult;

/// @ref C2XSEC_VerificationResult
typedef uint8_t tC2XSEC_VerificationResult;

/// Metadata for the unpacked payload after receiving the message.
/// This structure is shared between the current security APIs,
/// so it should be identical in layout to 'struct C2X_SEC_PayloadMetaData'.
typedef struct C2XSEC_PayloadMetaData
{
  /// Type of packet (NO SEC/SEC/SEC_CERT/..)
  tC2XSEC_SecType SecType;
  /// Result of security parsing
  tC2XSEC_ParserResult ParserResult;
  /// Result of security verification
  tC2XSEC_VerificationResult VerificationResult;
  /// SSP length
  uint8_t SSPLen;
  /// ITS-AID
  uint32_t AID;
  /// SSP bits
  uint8_t SSPBits[C2XSEC_SSP_BITS_MAX_LEN];
  /// CertId8
  uint8_t CertId8[8];
  /// Caller provides private data that must be preserved during the
  /// security operation
  void *pCallerPrivateData;
  /// Caller provides private function that must be preserved during the
  /// security operation
  void *pCallerPrivateFunction;
  /// Caller provides private handle that must be preserved during the
  /// security operation
  void *pCallerPrivateHandle;
} tC2XSEC_PayloadMetaData;

/// Metadata for the signed packet after signing the payload and
/// generating the security header and footer
typedef struct C2XSEC_SignedPacketMetaData
{
  /// Caller provides private data that must be preserved during the
  /// security operation
  void *pCallerPrivateData;
} tC2XSEC_SignedPacketMetaData;

/// Verification actions
typedef enum C2XSEC_ReceiveAction
{
  /// Extract only
  C2XSEC_RECEIVE_EXTRACT = 0x01,
  /// Get cert information
  C2XSEC_RECEIVE_CERT_INFO = 0x02,
  /// Check relevance
  C2XSEC_RECEIVE_RELEVANCE = 0x04,
  /// Check consistency
  C2XSEC_RECEIVE_CONSISTENCY = 0x08,
  /// Smart check
  C2XSEC_RECEIVE_SMART_DECISION = 0x10,
  /// Verify (asynchronous)
  C2XSEC_RECEIVE_VERIFY_ASYNC = 0x20,
  /// Verify (synchronous)
  C2XSEC_RECEIVE_VERIFY_SYNC = 0x40,
  /// Verify (new SMP)
  C2XSEC_RECEIVE_VERIFY_NEW_SMP = 0x80,
} eC2XSEC_ReceiveAction;

/// @ref C2XSEC_ReceiveAction
typedef uint8_t tC2XSEC_ReceiveAction;

/// Verification Latency
typedef enum C2XSEC_VerifLatency
{
  /// Min latency, no skip, Latency 0
  C2XSEC_LATENCY_MIN_NO_SKIP_0 = 0,
  /// Min latency, no skip, Latency 1
  C2XSEC_LATENCY_MIN_NO_SKIP_1 = 1,
  /// Low latency, no skip
  C2XSEC_LATENCY_LOW_NO_SKIP = 2,
  /// Low latency, can skip
  C2XSEC_LATENCY_LOW_CAN_SKIP = 3,
  /// Medium latency, no skip
  C2XSEC_LATENCY_MEDIUM_NO_SKIP = 4,
  /// Medium latency, can skip
  C2XSEC_LATENCY_MEDIUM_CAN_SKIP = 5,
  /// High latency, no skip
  C2XSEC_LATENCY_HIGH_NO_SKIP = 6,
  /// High latency, can skip
  C2XSEC_LATENCY_HIGH_CAN_SKIP = 7,
  /// Best effort latency, no skip
  C2XSEC_LATENCY_BEST_NO_SKIP = 8,
  /// Best effort latency, can skip
  C2XSEC_LATENCY_BEST_CAN_SKIP = 9,

  /// Limit for valid latency option
  C2XSEC_LATENCY_LIMIT = 10,

  /// Don't use latency option
  C2XSEC_LATENCY_NOT_USED = 255,
} eC2XSEC_VerifLatency;

/// @ref C2XSEC_VerifLatency
typedef uint8_t tC2XSEC_VerifyLatency;

/// Packet Verification decision
typedef enum C2XSEC_PacketDecision
{
  /// Not verifying, drop packet
  C2XSEC_DECISION_DROP,
  /// Considered for verification
  C2XSEC_DECISION_VERIFY,
  /// Not verifying, but continue to process
  C2XSEC_DECISION_CONTINUE,
} eC2XSEC_PacketDecision;

/// @ref C2XSEC_PacketDecision
typedef uint8_t tC2XSEC_PacketDecision;

/// Metadata passed to the secure messaging together with a received packet
typedef struct C2XSEC_ReceiveControlData
{
  /// Actions on receive packet
  tC2XSEC_ReceiveAction ReceiveAction;
  /// Expected latency of verification
  tC2XSEC_VerifyLatency VerifyLatency;
} tC2XSEC_ReceiveControlData;

/// Security profile
typedef enum C2XSEC_SecProfile
{
  /// No security
  C2XSEC_NONE = 0,
  /// Sec information with AID/SSP
  C2XSEC_AID_SSP = 1,
  /// Use default profile
  C2XSEC_DEFAULT = 2,
} eC2XSEC_SecProfile;

/// @ref C2XSEC_SecProfile
typedef uint8_t tC2XSEC_SecProfile;

/// Security information passed to the secure messaging module,
/// together with the payload to sign
typedef struct C2XSEC_SendControlData
{
  /// Security profile to use
  tC2XSEC_SecProfile Profile;
  /// SSP Len (number of octets of SSP bits)
  uint8_t SSPLen;
  /// SSP bitmap in use
  bool SSPBitmap;
  /// ITS-AID (numerical value, i.e. not encoded in any way)
  uint32_t AID;
  /// SSP Bits (up to C2XSEC_SSP_BITS_MAX_LEN octets)
  uint8_t SSPBits[C2XSEC_SSP_BITS_MAX_LEN];
  /// SSP Mask (up to C2XSEC_SSP_BITS_MAX_LEN octets)
  uint8_t SSPMask[C2XSEC_SSP_BITS_MAX_LEN];
} tC2XSEC_SendControlData;

/// Return type for the secure messaging module
typedef enum C2XSEC_Result
{
  /// OK
  C2XSEC_E_OK = 0,
  /// An error has occurred
  C2XSEC_E_NOT_OK = 1,
  /// Action already ongoing
  C2XSEC_E_ONGOING = 2,
  /// Action already complete
  C2XSEC_E_ALREADY_DONE = 3,
  /// An external memory buffer was to small
  C2XSEC_E_SMALL_BUFFER = 4,
  /// System is too busy to handle more requests
  C2XSEC_E_SYSTEM_BUSY = 5,
  /// The component which was called, was not initialized before the call
  C2XSEC_E_UNINITIALIZED = 6,
} eC2XSEC_Result;

/// @ref C2XSEC_Result
typedef uint8_t tC2XSEC_Result;

/// Type of the callback which has to be called after the secure
/// messaging has signed the packet
typedef void (*fC2XSEC_SendPacketCallback)
(
  /// Length in bytes of the signed packet
  uint16_t SignedPacketLength,
  /// Pointer to the signed packet
  uint8_t *pSignedPacket,
  /// Returned MetaData, provided in C2XSEC_SendPacket
  tC2XSEC_SignedPacketMetaData *pSendPacketMetaData,
  /// Return status
  tC2XSEC_Result RetVal
);

/// Type of the callback which has to be called after the secure
/// messaging has verified the packet
typedef void (*fC2XSEC_ReceivePacketCallback)
(
  /// Returned MetaData, provided in C2XSEC_ReceivePacket
  void *pData,
  /// Return status
  tC2XSEC_Result RetVal
);

/// Type of the callback which has to be called after the message extraction
///
typedef void (*fC2XSEC_ReceiveExtractCb)
(
  /// Pointer to the Params
  void *pCallerPrivateData,
  /// Signed Packet Length
  uint32_t SignedPacketLength,
  /// Payload Length
  uint32_t PayloadLength,
  /// Payload loacation
  uint8_t const *pPayload
);

/// Parameters to be handed to the Async verify func
typedef struct AsyncParams
{
  tC2XSEC_PayloadMetaData *pPayloadMetaData;
} tAsyncParams;

/// Declares a structure for data required to initialize the security module
/// such as functional pointers to callbacks implemented by the GN layer
typedef struct C2XSEC_SecMessagingCallbacks
{
  /// Send packet callback
  fC2XSEC_SendPacketCallback pSendPacketCallback;
  /// Receive packet callback
  fC2XSEC_ReceivePacketCallback pReceivePacketCallback;
} tC2XSEC_SecMessagingCallbacks;

/// Declares a functional pointer type to a callback which has to be
/// called by the security module to indicate the new ID to be used.
/// Copy the necessary length of ID, as required by the client layer.
typedef tC2XSEC_Result (*fC2XSEC_ChangeIdCallback)(
  const uint8_t InIdSize,
  const uint8_t *pInId);

/// Client type for ID change
typedef enum C2XSEC_ClientType
{
  /// Initial ID change
  C2XSEC_CLIENT_INIT = 0,
  /// Networking Layer
  C2XSEC_CLIENT_NET = 1,
  /// Facilities Layer
  C2XSEC_CLIENT_FAC = 2,
  /// Application Layer
  C2XSEC_CLIENT_APP = 3,
  /// Management Entity
  C2XSEC_CLIENT_MGMT = 4,
  /// Test Entity
  C2XSEC_CLIENT_TEST = 5,
  /// Custom
  C2XSEC_CLIENT_CUSTOM = 6,
  /// Max marker
  C2XSEC_CLIENT_MAX_AMOUNT = 7,

  /// Alt ID mask
  C2XSEC_CLIENT_ALT_ID = 0x40,
  /// Normal ID mask
  C2XSEC_CLIENT_NORMAL_ID = 0x80
} eC2XSEC_ClientType;

/// @ref C2XSEC_ClientType
typedef uint8_t tC2XSEC_ClientType;

/// C2X Statistics
typedef struct C2XSEC_Stats
{
  // Average time storage
  uint32_t AvgTIDChange;
  uint32_t AvgTSign;
  uint32_t AvgTVerify;

  // Receive/verify counters
  uint32_t NumRecv;
  uint32_t NumExtract;
  uint32_t NumRelevance;
  uint32_t NumConsistency;
  uint32_t NumVerify;

  // Send/sign counters
  uint32_t NumSend;
  uint32_t NumSign;

  // absolute ID change counter
  uint32_t NumIDChange;
  // scheduled ID change counter
  uint32_t NumIDSched;

  // Last used pseudonym index
  uint8_t LastPseudonymIndex;

  // Verification failure codes
  uint8_t VerifyFailed[NUM_LAST_FAILS_LOG];
  uint8_t VerifyFailedCount;

  // Stats detail level
  uint8_t InfoLevel;
} tC2XSEC_Stats;

typedef struct C2XSECEncKey
{
  uint8_t *pKey;
  uint32_t KeyLen;
} tC2XSECEncKey;

#ifdef __cplusplus
}
#endif

#endif // __IF_SEC_C2X_SEC_H__

/**
 * @}
 */
