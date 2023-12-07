/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_Api_fpvd Full Position Vector Description
 * ASN.1 BER encoding and decoding of J2735 Full Position Vector.
 *
 *
 * @file j2735-full-position-vector.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_FULL_POSITION_VECTOR_H_
#define __J2735_FULL_POSITION_VECTOR_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <j2735asn.h>
#include <j2735asn_def.h>

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
 * @brief config for Optional Fields in DDateTime
 *
 * This struct captures all the optional fields in DDate. This
 * structure is used to turn each optional field on and off.
 *
 */

typedef struct DDateTimeCfg
{
  /// Year
  unsigned int Year:1;
  /// Month
  unsigned int Month:1;
  /// Day
  unsigned int Day:1;
  /// Hour
  unsigned int Hour:1;
  /// Min
  unsigned int Min:1;
  /// Sec
  unsigned int Sec:1;
} tDDateTimeCfg;

/**
 * @brief config for Optional Fields in Full Position Vector
 *
 * This struct captures all the optional fields in FullPostionVector. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 *
 * eg. DDateTime must be turned on (1) to
 * allow DDateTimeConfig (1) to be functional.
 *
 */

typedef struct SAEFullPositionVectorCfg
{
  /// utcTime *
  unsigned int utcTime:1;
  /// struct DDateTime *
  struct DDateTimeCfg utcTimeConfig;
  // Long is mandatory
  // Lat is mandatory
  /// Elevation_t * (OCTET_STRING_t *))
  unsigned int elevation:1;
  /// Heading_t * (long))
  unsigned int heading:1;
  /// TransmissionAndSpeed_t * (OCTET_STRING_t *)
  unsigned int speed:1;
  /// PositionalAccuracy_t * (OCTET_STRING_t *)
  unsigned int posAccuracy:1;
  /// TimeConfidence_t * (enum *)
  unsigned int timeConfidence:1;
  /// PositionConfidenceSet_t * (OCTET_STRING_t *)
  unsigned int posConfidence:1;
  /// SpeedHeadingandThrottleConfidence_t * (OCTET_STRING_t *)
  unsigned int speedConfidence:1;
} tSAEFullPositionVectorCfg;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735SAEFullPositionVector_Create(SAEFullPositionVector *pFullPosVec,
                                   const tSAEFullPositionVectorCfg *pConfig);

int J2735SAEFullPositionVector_Free(SAEFullPositionVector *pFullPosVec,
                                 tJ2735FreeOption FreeOption);

struct LPHPos;
void J2735_PolulateSAEFullPositionVectorFromLPHPos(
  SAEFullPositionVector * pSAEFullPositionVector,
  const struct LPHPos *pLPHPos);

#ifdef __cplusplus
}
#endif

#endif // __J2735_FULL_POSITION_VECTOR_H_
// Close the doxygen group
/**
 * @}
 */
