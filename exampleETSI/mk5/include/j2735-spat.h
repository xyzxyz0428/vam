/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_spatd SPAT Description
 * ASN.1 BER encoding and decoding of J2735 SPAT messages.
 *
 * @file j2735-map.h J2735 Interface to the J2735 Library.
 *
 * ASN.1 BER encoding and decoding of J2735 SPAT messages.
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_SPAT_H_
#define __J2735_SPAT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "j2735asn.h" // ASN.1 type
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

/**
 * @brief Config for Optional Fields in an SPAT
 *
 * This struct captures all the optional fields in a SPAT. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 * eg. 'position' must be turned on (1) to allow 'positionCfg' to be
 *     applied.
 */

typedef struct SPATCfg
{
  int Reserved;
} tSPATCfg;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735SPAT_Create (struct SAESPAT **ppSPAT,
                     const struct SPATCfg *pCfg,
                     tJ2735CreateOption CreateOption);

int J2735SPAT_Free (struct SAESPAT *pSPAT,
                   tJ2735FreeOption FreeOption);

int J2735SPAT_Encode (const struct SAESPAT *pSPAT,
                     uint8_t *pBuf,
                     int BufSize);

int J2735SPAT_Decode (struct SAESPAT **ppSPAT,
                     const char *pBuf,
                     int BufSize);

#ifdef __cplusplus
}
#endif

#endif // __J2735_SPAT_H_
// Close the doxygen group
/**
 * @}
 */
