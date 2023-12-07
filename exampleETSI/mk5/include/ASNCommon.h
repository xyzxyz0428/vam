/**
 * @addtogroup v2x_etsi_asn ETSI ITS ASN utilities
 * @{
 *
 * ASN encoding/decoding utilities and helpers
 *
 * @file
 *
 * ETSI ASN common support
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef _ETS_ASN_ASN_COMMON_H_
#define _ETS_ASN_ASN_COMMON_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "itsasn.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Macro to access 42-bit ASN timestamp field (@ref ETSASN_GetTimestamp)
/// Timestamp is held in ASN-specific buffer rather than primitive data type
/// Access data depending on number of uint32_t 'limbs' used to store the value
#define ETSASN_GetTimestampPtr(Ptr) (((Ptr)->data[0]) | (((Ptr)->len == 1) ? 0 : ((((uint64_t)(Ptr)->data[1] << 32)) & 0x3FFFFFFFFFFULL)))

/// Macro to access bit from BIT STRING
/// Bit String is packed from left (Bit 0) to right (Bit N)
#define ETSASN_GetBitStringPtr(Ptr,Pos) ((Ptr) && (Pos < (Ptr)->len)) ? (((Ptr)->buf[Pos/8] & (1 << (7-(Pos%8)))) == (1 << (7-(Pos%8)))) : false

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// ASN encoding types
typedef enum ASNEncodingType
{
  /// XER
  ASN1_XER,
  /// PER
  ASN1_PER,
  /// OER
  ASN1_OER,
  /// SER
  ASN1_SER,
  /// JER
  ASN1_JER,
  /// XER single line
  ASN1_XER_SINGLE
}
tASNEncodingType;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Get status of a individual bit in a BITSTRING and return it
 * @param pBS pointer to Bit String to get
 * @param BSPos  Bit position to report value (first bit is the most significant
 *               bit and is position 0, as defined in ASN.1 BIT STRING)
 * @return Status of bit, false = not set, true = set
 */
bool ETSASN_GetBitStringItem(ASN1BitString *pBS, int BSPos);

/**
 * @brief Create space for bits in a BITSTRING according to size
 * @param pBS  pointer to Bit String to set
 * @param Size Size of bit-string
 * @return Status, 0 for success
 *
 * NOTE typically pBS is not previously allocated, but if it is then
 *      memory can be re-used or re-allocated if not sufficiently large
 */
int ETSASN_CreateBitString(ASN1BitString *pBS, int Size);

/**
 * @brief Set status of a individual bit in a BITSTRING
 * @param pBS pointer to Bit String to set
 * @param BSPos  Bit position to report value (first bit is the most significant
 *               bit and is position 0, as defined in ASN.1 BIT STRING)
 * @return Status, 0 for success
 */
int ETSASN_SetBitStringItem(ASN1BitString *pBS, int BSPos);

/**
 * @brief Set bits in a BITSTRING according to value of variable number
 *        of parameters each setting one bit
 * @param pBS  pointer to Bit String to set
 * @param n   number of arguments
 * @param ... VarArg items to set bits (first param is first bit in string)
 * @return Status, 0 for success
 */
int ETSASN_SetBitString(ASN1BitString *pBS, int n, /*int*/...);

/**
 * @brief Set bits in a BITSTRING according to value of list of
 *        parameters each setting one bit
 * @param pBS  pointer to Bit String to set
 * @param n   number of arguments
 * @param ap  list of items to test
 * @return Status, 0 for success
 *
 */
int ETSASN_SetBitStringList(ASN1BitString *pBS, int n, int *ap);

/**
 * @brief Set Timestamp value
 * @param pTS  pointer to Timestamp field
 * @param MSec  Timestamp value
 * @return Status, 0 for success
 *
 */
int ETSASN_SetTimestamp(ITSTimestampIts *pTS, uint64_t MSec);

/**
 * @brief Extract Timestamp value
 * @param pTS  pointer to Timestamp field
 * @return Timestamp value, milliseconds since TAI-2004 epoch
 *
 */
uint64_t ETSASN_GetTimestamp(const ITSTimestampIts *pTS);

/**
 * @brief Encode type to variable type
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @param Type encoded form
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *ETSASN_EncodeTo(const ASN1CType *pAType,
                         const void *pPDU,
                         unsigned int *pLen,
                         tASNEncodingType Type);

/**
 * @brief Encode type to XER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
char *ETSASN_EncodeToXER(const ASN1CType *pAType,
                         const ITSItsPduHeader *pPDU,
                         unsigned int *pLen);

/**
 * @brief Encode type to XER as single line
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
char *ETSASN_EncodeToXERSingle(const ASN1CType *pAType,
                               const ITSItsPduHeader *pPDU,
                               unsigned int *pLen);


/**
 * @brief Encode type to PER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *ETSASN_EncodeToPER(const ASN1CType *pAType,
                            const ITSItsPduHeader *pPDU,
                            unsigned int *pLen);

/**
 * @brief Encode type to OER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *ETSASN_EncodeToOER(const ASN1CType *pAType,
                            const void *pPDU,
                            unsigned int *pLen);

/**
 * @brief Decode from variable type to decoded data structure
 * @param pAType ASN1 data type
 * @param pStructure pointer to pointer for decoded data structure
 * @param pBuffer pointer to encoded data
 * @param Size length of encoded data
 * @param Type encoded form
 * @return Status, >0 for success (indicates number of bytes decoded)
 *                 -1 for error/unknown encoding
 *
 */
int ETSASN_DecodeFrom(const ASN1CType *pAType,
                      void **pStructure,
                      const void *pBuffer,
                      size_t Size,
                      tASNEncodingType Type);

/**
 * @brief Dump PDU in GSER form to debug print
 * @param pAType  ASN type to dump
 * @param pPDU  decoded data structure
 * @param Level  debug level to use
 * @return 0 for success
 *
 */
int ETSASN_GSERPrintLevel(const ASN1CType *pAType,
                          const void *pPDU,
                          uint8_t Level);

/**
 * @brief Dump PDU in GSER form to debug print (at D_NOTICE level)
 * @param pAType  ASN type to dump
 * @param pPDU  decoded data structure
 * @return 0 for success
 *
 */
int ETSASN_GSERPrint(const ASN1CType *pAType,
                     const void *pPDU);

#ifdef __cplusplus
}
#endif

#endif //_ETS_ASN_ASN_COMMON_H_

/**
 * @}
 */
