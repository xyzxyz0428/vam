/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_cd Common Description
 * ASN.1 BER encoding and decoding of J2735 messages - common
 *
 * @file j2735-common.h J2735 Interface to the J2735 Library.
 *
 * defines utilities used across the library for alloc etc.
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 *
 */


//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_COMMON_H_
#define __J2735_COMMON_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "asn1defs.h"

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
/// Dot2 parser info
typedef struct J2735Dot2Info
{
  /// Length of the packet
  uint16_t Length;
  /// Parser specific: Offset
  int16_t Offset;
  /// Parser specific: Public Key Algorithm
  uint8_t PkAlg;
  /// Set according to eDot3WSMPSecurity
  uint8_t Flags;
  /// ToBeSigned data offset
  int16_t Pos;
} tJ2735Dot2Info;

/// Create methods - provide option to create both the container object and its
/// subordinate members, or just to allocate the subordinate members (requiring
/// preallocation of the container.
typedef enum
{
  J2735_CREATE_ALL = 0,
} tJ2735CreateOption;

/// Free methods
typedef enum
{
  J2735_FREE_ALL = 0,
  J2735_FREE_CONTENTS_ONLY = 1,
} tJ2735FreeOption;


/// Error codes
typedef enum
{
  J2735_ERR_NONE       = 0,   // No Error
  J2735_ERR_NULL,             // Attempt to access NULL pointer
  J2735_ERR_MALLOC,           // Error performing malloc
} tJ2735ErrorCode;

/// Alloc structure size with calloc
#define ALLOC_OBJ(type, num) \
  (type *)calloc(num, sizeof(type))

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
int J2735_xer_fprint(FILE * stream,
                     const ASN1CType *,
                     const void * pData);

int J2735_InspectDot2 (uint8_t *pBuf, int *pLen, tJ2735Dot2Info *pCtx);

int J2735_EncodeXML(const void * pData,
                    const ASN1CType * pType,
                    void *buffer,
                    size_t buffer_size);

// Functions not used

#if 0

int J2735_EncodeToFileXML(const void * pData,
                          const ASN1CType * pType,
                          const char *pFileName);

int J2735_EncodeToFileUPER(const void * pData,
                           const ASN1CType * pType,
                           const char *pFileName);

int J2735_DecodeFromFileXML(void ** ppData,
                            const ASN1CType * pType,
                            const char *pFileName);

int J2735_DecodeFromFileUPER(void ** ppData,
                             const ASN1CType * pType,
                             const char *pFileName);

#endif

int J2735_SetBitString(ASN1BitString *pBS, int n, ...);

#ifdef __cplusplus
}
#endif

#endif // __J2735_COMMON_H_
// Close the doxygen group
/**
 * @}
 */
