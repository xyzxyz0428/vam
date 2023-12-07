/**
 * @addtogroup v2x_saec_asn SAEC ASN utilities
 * @{
 *
 * ASN encoding/decoding utilities and helpers
 *
 * @file
 *
 * SAEC ASN common support
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef _SAEC_ASN_ASN_COMMON_H_
#define _SAEC_ASN_ASN_COMMON_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "saecasn.h"
#include "saecasn_def.h"

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

/// Macro to access bit from BIT STRING
/// Bit String is packed from left (Bit 0) to right (Bit N)
#define SAECASN_GetBitStringPtr(Ptr,Pos) \
  ((Ptr) && (Pos < (Ptr)->len)) ? (((Ptr)->buf[Pos/8] & (1 << (7-(Pos%8)))) == (1 << (7-(Pos%8)))) : false

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// ASN encoding types
typedef enum
{
  /// XER
  SAEC_ASN1_XER,
  /// PER
  SAEC_ASN1_PER,
  /// OER
  SAEC_ASN1_OER,
  /// SER
  SAEC_ASN1_SER,
  /// XER single line
  SAEC_ASN1_XER_SINGLE,
  /// BER (DER)
  SAEC_ASN1_BER,
  /// JER
  SAEC_ASN1_JER
}
tCSAEEncodingType;

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
bool SAECASN_GetBitStringItem(ASN1BitString *pBS, int BSPos);

/**
 * @brief Create space for bits in a BITSTRING according to size
 * @param pBS  pointer to Bit String to set
 * @param Size Size of bit-string
 * @return Status, 0 for success
 */
int SAECASN_CreateBitString(ASN1BitString *pBS, int Size) __attribute__ ((warn_unused_result));

/**
 * @brief Set status of a individual bit in a BITSTRING
 * @param pBS pointer to Bit String to set
 * @param BSPos  Bit position to report value (first bit is the most significant
 *               bit and is position 0, as defined in ASN.1 BIT STRING)
 * @return Status, 0 for success
 */
int SAECASN_SetBitStringItem(ASN1BitString *pBS, int BSPos);

/**
 * @brief Set bits in a BITSTRING according to value of variable number
 *        of parameters each setting one bit
 * @param pBS  pointer to Bit String to set
 * @param n   number of arguments
 * @param ... VarArg items to set bits (first param is first bit in string)
 * @return Status, 0 for success
 */
int SAECASN_SetBitString(ASN1BitString *pBS, int n, /*int*/...);

/**
 * @brief Set bits in a BITSTRING according to value of list of
 *        parameters each setting one bit
 * @param pBS  pointer to Bit String to set
 * @param n   number of arguments
 * @param ap  list of items to test
 * @return Status, 0 for success
 *
 */
int SAECASN_SetBitStringList(ASN1BitString *pBS, int n, int *ap);

/**
 * @brief Encode type to variable type
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @param Type encoded form
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *SAECASN_EncodeTo(const ASN1CType *pAType,
                          const void *pPDU,
                          unsigned int *pLen,
                          tCSAEEncodingType Type);

/**
 * @brief Encode type to XER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
char *SAECASN_EncodeToXER(const ASN1CType *pAType,
                          const uint8_t *pPDU,
                          unsigned int *pLen);

/**
 * @brief Encode type to XER as single line
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
char *SAECASN_EncodeToXERSingle(const ASN1CType *pAType,
                                const uint8_t *pPDU,
                                unsigned int *pLen);


/**
 * @brief Encode type to PER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *SAECASN_EncodeToPER(const ASN1CType *pAType,
                             const uint8_t *pPDU,
                             unsigned int *pLen);

/**
 * @brief Encode type to OER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *SAECASN_EncodeToOER(const ASN1CType *pAType,
                             const void *pPDU,
                             unsigned int *pLen);

/**
 * @brief Encode type to BER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *SAECASN_EncodeToBER(const ASN1CType *pAType,
                             const void *pPDU,
                             unsigned int *pLen);

/**
 * @brief Encode type to JER
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @param pLen pointer to length of encoded data
 * @return pointer to (allocated) encoded data (NULL on error)
 *
 */
uint8_t *SAECASN_EncodeToJER(const ASN1CType *pAType,
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
int SAECASN_DecodeFrom(const ASN1CType *pAType,
                       void **pStructure,
                       const void *pBuffer,
                       size_t Size,
                       tCSAEEncodingType Type);

/**
 * @brief Print XER to file stream
 * @param pStream Stream
 * @param pAType ASN1 data type
 * @param pPDU pointer to decoded data structure
 * @return Status, 0 for success
 *
 */
int SAECASN_xer_fprint(FILE *pStream,
                       const ASN1CType *pAType,
                       const uint8_t *pPDU);

/**
 * @brief Dump PDU in GSER form to debug print
 * @param pAType  ASN type to dump
 * @param pPDU  decoded data structure
 * @return 0 for success
 *
 */
int SAECASN_GSERPrint(const ASN1CType *pAType,
                      const void *pPDU);


/**
 * @brief Validate the if the constraints are met
 * @param pASN1CType ASN1 type
 * @param pData Pointer to the ASN1 structure
 * @return If the ASN1 structure is successfully validated
 */
bool SAECASN_Validate(const ASN1CType * pASN1CType, void *pData);
#ifdef __cplusplus
}
#endif

#endif //_ETS_ASN_ASN_COMMON_H_

/**
 * @}
 */
