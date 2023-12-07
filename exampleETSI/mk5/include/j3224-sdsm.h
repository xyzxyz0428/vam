/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @internal
 *
 * ASN.1 BER encoding and decoding of the J3224 Sensor Data Sharing Messages
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2022 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J3224_SDSM_H_
#define __J3224_SDSM_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "j2735asn.h" // ASN.1 type
#include "j2735asn_def.h"
#include "j2735-common.h"

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

/// J3224 Status codes
typedef enum J3224StatusCode
{
  /// J3224 success
  J3224_SUCCESS = 0x00,
  /// J3224 generation failure
  J3224_FAILURE,
  /// J3224 some parameters invalid
  J3224_FAILURE_INVALID_PARAMS,
  /// J3224 limits exceeded in structure
  J3224_FAILURE_CONSTRAINT,
  /// J3224 failed to encode
  J3224_FAILURE_ENCODING,
  /// J3224 not ready
  J3224_FAILURE_NOT_READY,

} eJ3224StatusCode;

/// Status code for J3224 actions @ref J3224StatusCode
typedef uint8_t tJ3224StatusCode;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J3224SDSM_Create (struct SAESensorDataSharingMessage **ppSDSM);

int J3224SDSM_Free (struct SAESensorDataSharingMessage *pSDSM);

int J3224SDSM_Encode (const struct SAESensorDataSharingMessage *pSDSM,
                      uint8_t *pBuf,
                      int BufSize);

int J3224SDSM_Decode (struct SAESensorDataSharingMessage **ppSDSM,
                      const char *pBuf,
                      int BufSize);

#ifdef __cplusplus
}
#endif

#endif // __J3224_SDSM_H_
// Close the doxygen group
/**
 * @}
 */
