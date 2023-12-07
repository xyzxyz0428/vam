/**
 * @addtogroup saec_security SAEC Security API
 * @{
 *
 * @file
 *
 * Interface for Public Security API
 *
 */

#ifndef __LIB_IF_SEC_SAEC_SEC_IF_H__
#define __LIB_IF_SEC_SAEC_SEC_IF_H__
//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "saec-sktbuf.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

// NOTE: AIDs are a numerical value, they are not encoded in any way

#define SAECSEC_AID_BSM 111

#define SAECSEC_AID_SPAT 3619

#define SAECSEC_AID_MAP 3618

/// Define size (in bytes) of BSM SSP bits
#define SAECSEC_SSP_LEN_BSM 0

/// Define size (in bytes) of RSI SSP bits
#define SAECSEC_SSP_LEN_RSI 0

/// Define size (in bytes) of RSM SSP bits
#define SAECSEC_SSP_LEN_RSM 0

/// Define size (in bytes) of SPAT SSP bits
#define SAECSEC_SSP_LEN_SPAT 0

/// Define size (in bytes) of MAP SSP bits
#define SAECSEC_SSP_LEN_MAP 0

/// Maximum number of octets for SSP bits
#define SAECSEC_SSP_OCTETS_MAX_LEN 32

/// Max failures to track
#define NUM_LAST_FAILS_LOG 10

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Return type for the secure messaging module
typedef enum
{
  /// OK
  SAECSEC_E_OK = 0,
  /// An error has occurred
  SAECSEC_E_NOT_OK = 1,
  /// Action already ongoing
  SAECSEC_E_ONGOING = 2,
  /// Action already complete
  SAECSEC_E_ALREADY_DONE = 3,
  /// An external memory buffer was to small
  SAECSEC_E_SMALL_BUFFER = 4,
  /// System is too busy to handle more requests
  SAECSEC_E_SYSTEM_BUSY = 5,
  /// The component which was called, was not initialized before the call
  SAECSEC_E_UNINITIALIZED = 6,
  /// Feature not supported
  SAECSEC_E_NOT_SUPPORTED = 7,
  /// Invalid params
  SAECSEC_E_INVALID_PARAMS = 8,
  /// Memory allocation failure
  SAECSEC_E_NO_MEM = 9,

  /// Relevance check fails
  SAECSEC_E_CHECK_RELEVANCE = 100,
  /// Consistency check fails
  SAECSEC_E_CHECK_CONSISTENCY,
  /// Signature check fails
  SAECSEC_E_CHECK_SIGNATURES,
  /// Invalid SPDU Version
  SAECSEC_E_SPDU_VERSION,
  /// Generation time too far or missing
  SAECSEC_E_SPDU_GENERATION_TIME,

  /// Invalid hash algorithm
  SAECSEC_E_SPDU_HASH_ALGORITHM = 105,
  /// Invalid or mismatching AID
  SAECSEC_E_SPDU_AID_MISMATCH,
} eSAECSecResult;

/// @sa eSAECSec_Result
typedef uint8_t tSAECSecResult;

/// Security Certificate Type
typedef enum
{
  /// Pseudonym certificate
  SAECSEC_CERT_TYPE_PSEUDONYM  = 0,
  /// Application certificate
  SAECSEC_CERT_TYPE_APPLICATION = 1,
} eSAECSecCertType;

/// @sa eSAECSecCertType
typedef uint8_t tSAECSecCertType;

/// Security Certificate
typedef enum
{
  /// Default policy in the security library
  SAECSEC_CERT_ATTACH_DEFAULT = 0,
  /// Attach certificate digest
  SAECSEC_CERT_ATTACH_DIGEST = 1,
  /// Attach full certificate
  SAECSEC_CERT_ATTACH_CERTIFICATE = 2,
} eSAECSecCertAttach;

/// @sa eSAECSecCertAttach
typedef uint8_t tSAECSecCertAttach;

/// Security information passed to the secure messaging module,
/// together with the payload to sign
typedef struct SAECSecSignParams
{
  /// @ref eSAECSec_CertType
  tSAECSecCertType Type;
  /// @ref eSAECSec_CertAttach
  tSAECSecCertAttach Attach;
  /// AID (numerical value, i.e. not encoded in any way)
  uint32_t AID;
  /// SSP (up to SAECSEC_SSP_BITS_MAX_LEN octets)
  uint8_t SSP[SAECSEC_SSP_OCTETS_MAX_LEN];
  /// SSP Length
  uint8_t SSPLen;
} tSAECSecSignParams;

/// Declares a functional pointer type to a callback which has to be
/// called by the security module to indicate the new ID to be used.
/// Copy the necessary length of ID, as required by the client layer.
typedef tSAECSecResult (fSAECSec_ChangeIdCallback)(const uint8_t InIdSize,
                                                   const uint8_t *pInId);

/// Client type for ID change
typedef enum
{
  /// Networking Layer
  SAECSEC_CLIENT_NET = 0,
  /// Facilities Layer
  SAECSEC_CLIENT_FAC = 1,
  /// Application Layer
  SAECSEC_CLIENT_APP = 2,
  /// Management Entity
  SAECSEC_CLIENT_MGMT = 3,
  /// Test Entity
  SAECSEC_CLIENT_TEST = 4,
  /// Custom
  SAECSEC_CLIENT_CUSTOM = 5,
  /// Max marker
  SAECSEC_CLIENT_MAX_AMOUNT = 6,

  /// Alt ID mask
  SAECSEC_CLIENT_ALT_ID = 0x40,
  /// Normal ID mask
  SAECSEC_CLIENT_NORMAL_ID = 0x80
} eSAECSecClientType;

/// @sa eSAECSec_ClientType
typedef uint8_t tSAECSecClientType;

/// Statistics
typedef struct SAECSecStats
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

  // ID change counter
  uint32_t NumIDChange;

  // Last used pseudonym index
  uint8_t LastPseudonymIndex;

  // Verification failure codes
  uint8_t VerifyFailed[NUM_LAST_FAILS_LOG];
  uint8_t VerifyFailedCount;

  // Stats detail level
  uint8_t InfoLevel;
} tSAECSecStats;

/// Verification checks
typedef enum
{
  /// Get cert information
  SAECSEC_VERIFY_CHECK_PSID        = 1 << 0,
  /// Check relevance
  SAECSEC_VERIFY_CHECK_RELEVANCE   = 1 << 1,
  /// Check consistency
  SAECSEC_VERIFY_CHECK_CONSISTENCY = 1 << 2,
  /// Verify
  SAECSEC_VERIFY_CHECK_SIGNATURES  = 1 << 3,
} eSAECSecVerifyChecks;

/// @sa eSAECSec_ReceiveCheck
typedef uint32_t tSAECSecVerifyChecks;

typedef struct SAECSecVerifyActions
{
  /// Action to be performed
  tSAECSecVerifyChecks Checks;
  /// AID to match
  uint32_t AID;
} tSAECSecVerifyActions;

/** Callback for asynchronous signing
 * @param Ret Signing result
 * @param pUserData User data passed in
 * @param pSigned Signed data
 * @param SignedLen Length of signed data
 */
typedef void (fSAECSec_SignCallback)(tSAECSecResult Ret,
                                     void * pUserData,
                                     uint8_t * pSigned,
                                     size_t SignedLen);

/** Callback for asynchronous signing
 * @param Ret Signing result
 * @param pUserData User data passed in
 */
typedef void (fSAECSec_SignPktCallback)(tSAECSecResult Ret,
                                        void * pUserData);

/** Callback for asynchronous verification
 * @param Ret Verification result
 * @param pUserData User data passed in
 */
typedef void (fSAECSec_VerifyCallback)(tSAECSecResult Ret,
                                       void * pUserData);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Security Library API
//------------------------------------------------------------------------------
/**
 * @brief Sign a message
 * Sign a message using the specified parameters.
 * @param pPayload Payload to sign
 * @param PayloadLen Size of Payload
 * @param pSignParams Signing Parameters
 * @param[out] pSigned Buffer for the signed content. Must be allocated before being passed in.
 * @param[in, out] pSignedLen Size of the signed content buffer. After signing it returns the size of the signed message.
 *                 When signing the message asynchronously, it is only used as input when  this function is invoked.
 * @param pCallback Callback to be invoked if asynchronous signing is intened.
 *                  If it is NULL, synchronous signing will be performed.
 * @param pUserData User data for @ref pCallback
 * @return Result of the signing operaton.
 */
tSAECSecResult SAECSec_Sign(const uint8_t * pPayload,
                            size_t PayloadLen,
                            const tSAECSecSignParams * pSignParams,
                            uint8_t * pSigned,
                            size_t * pSignedLen,
                            fSAECSec_SignCallback * pCallback,
                            void * pUserData);

/**
 * @brief Verify a message
 * Verify a message using the specified parameters.
 * @param pSigned Signed message.
 * @param SignedLen Size of the signed message.
 * @param pActions Verification actions
 * @param[out] ppPayload A pointer to the payload memory within
 *        @code
 *        [pSigned, pSigned + SignedLen)
 *        @endcode
 * @param[in, out] pPayloadLen Size of the extracted Payload buffer. After verification it returns the size of payload.
 * @param pCallback Callback to be invoked if asynchronous verification is intened.
 *                  If it is NULL, synchronous verification will be performed.
 * @param pUserData User data for @ref pCallback
 * @return Result of the verification operaton.
 */
tSAECSecResult SAECSec_Verify(const uint8_t * pSigned,
                              size_t SignedLen,
                              const tSAECSecVerifyActions * pActions,
                              uint8_t const ** ppPayload,
                              size_t * pPayloadLen,
                              fSAECSec_VerifyCallback * pCallback,
                              void * pUserData);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_IF_SEC_SAEC_SEC_IF_H__ */

// Close the doxygen group
/**
 * @}
 */
