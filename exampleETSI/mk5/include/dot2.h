/**
 * @addtogroup dot2_api IEEE 1609.2 (Dot2) Security API
 * @{
 *
 * @section dot2_api_dd What Does It Do
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __DOT2_DOT2_h_
#define __DOT2_DOT2_h_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "stats.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
// number of bytes
#define DOT2_PSEUDONYM_ID_LEN 8

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// specifies to use default attachment profile, force attach certificate or
/// force attach digest
typedef enum
{
  DOT2_CERT_ATTACH_DEFAULT = 0,
  DOT2_CERT_ATTACH_CERTIFICATE = 1,
  DOT2_CERT_ATTACH_DIGEST = 2
} eDot2CertAttach;

/// @copydoc eDot2CertAttach
typedef uint8_t tDot2CertAttach;

typedef enum Dot2VerifyChecks
{
  DOT2_VERIFY_CHECK_RELEVANCE = 1 << 0,
  DOT2_VERIFY_CHECK_CONSISTENCY = 1 << 1,
  DOT2_VERIFY_CHECK_PSID = 1 << 2,
  DOT2_VERIFY_CHECK_SIGNATURES = 1 << 3
} eDot2VerifyChecks;

/// @ref Dot2VerifyChecks
typedef uint8_t tDot2VerifyChecks;

/// Ret will be 0 on success and non-zero on error - pPriv corresponds to the
/// value provided in @ref Dot2_VerifyAsync()
typedef void (fDot2AsyncVerifyCallback)(int Ret,
                                        void *pPriv,
                                        const uint8_t *pPayload,
                                        uint32_t PayloadLen);
/// Function prototype to send a PDU (p2p) - return 0 for success, otherwise
/// for error
typedef int (fDot2SendPDUCallback)(uint32_t PSID,
                                   const uint8_t *pPDU,
                                   uint32_t Len);

typedef struct Dot2Location
{
  /// Latitude in one tens microdegree.
  /// -900000000 to 900000000. -900000001 indicates that latitude is unknown
  int Latitude;
  /// Longitude in one tens microdegree.
  /// -1800000000 to 1800000000. -1800000001 indicates that longitude is unknown
  int Longitude;
  /// Elevation in decimeters using the WGS84 ellipsoid
  /// -4095 to 61439. -4096 indicates that elevation is unknown
  int Elevation;
} tDot2Location;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int Dot2_Init(void);
void Dot2_Deinit(void);

int Dot2_ThreadInit(int SchedulerPolicy, int SchedulerPriority);
void Dot2_ThreadDeinit(void);

/// inform the dot2 library if cert changes should be delayed
void Dot2_SetDelayCertChange(bool DelayCertChange);
/// Check whether Id change is needed
bool Dot2_CheckIdChange(void);
/// get pseudonym ID
int Dot2_GetPseudonymId(uint8_t Id[DOT2_PSEUDONYM_ID_LEN]);
/// initiate ID change
void Dot2_RequestIdChange(bool Duplicate);
/// get TX crypto result from security library's error code
tStats_StackCryptoResult Dot2_GetTxCryptoReasonCode(int Res);
/// get RX crypto result from security library's error code
tStats_StackCryptoResult Dot2_GetRxCryptoReasonCode(int Res);
/// p2p process message
void Dot2_P2PProcess(uint32_t PSID, uint8_t *pData, uint32_t Len);

/// Sign the data with the given PSID
int Dot2_Sign(uint32_t PSID,
              tDot2CertAttach CertAttach,
              uint32_t Headroom,
              const uint8_t *pData,
              uint32_t Len,
              uint8_t **ppSignedData,
              uint32_t *pSignedLen);

/// Validate and verify the data
int Dot2_Verify(tDot2VerifyChecks Checks,
                uint32_t *pPSID,
                const tDot2Location *pLocation,
                const uint8_t *pData,
                uint32_t Len,
                const uint8_t **ppPayload,
                uint32_t *pPayloadLen);
int Dot2_VerifyAsync(tDot2VerifyChecks Checks,
                     uint32_t *pPSID,
                     const tDot2Location *pLocation,
                     const uint8_t *pData,
                     uint32_t Len,
                     const uint8_t **ppPayload,
                     uint32_t *pPayloadLen,
                     fDot2AsyncVerifyCallback *pCallback,
                     void *pPriv);

int Dot2_Inspect(uint8_t *pBuf, uint32_t Len);

void Dot2_SetSendPDUCallback(fDot2SendPDUCallback *pCallback);

#ifdef __cplusplus
}
#endif

#endif // __DOT2_DOT2_h_

// Close the doxygen group
/**
 * @}
 */
