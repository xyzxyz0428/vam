/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_rsad Road Side Alert Description
 * ASN.1 BER encoding and decoding of J2735 RSA messages.
 *
 * @file j2735-road-side-alert.h J2735 Interface to the J2735 Library.
 *
 * ASN.1 BER encoding and decoding of J2735 RSA messages.
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_ROAD_SIDE_ALERT_H_
#define __J2735_ROAD_SIDE_ALERT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "j2735asn.h" // ASN.1 type

#include "j2735-common.h"
#include "j2735-full-position-vector.h"

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
 * @brief Config for Optional Fields in an RSA
 *
 * This struct captures all the optional fields in an RSA. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 * eg. 'position' must be turned on (1) to allow 'positionCfg' to be
 *     applied.
 */

typedef struct RoadSideAlertCfg
{
  // msgID is mandatory

  // msgCnt is mandatory

  // typeEvent is manadatory

  /// Number of items in the description list 0...8
  unsigned int description:4;

  ///
  unsigned int priority:1;

  ///
  unsigned int heading:1;

  ///
  unsigned int extent:1;

  ///
  unsigned int position:1;
  // SAEFullPositionVector_t has optional members
  struct SAEFullPositionVectorCfg positionCfg;

  ///
  unsigned int furtherInfoID:1;

  // crc is mandatory

} tRoadSideAlertCfg;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735RoadSideAlert_Create (struct SAERoadSideAlert **ppRSA,
                               const struct RoadSideAlertCfg *pCfg,
                               tJ2735CreateOption CreateOption);

int J2735RoadSideAlert_Free (struct SAERoadSideAlert *pRSA,
                             tJ2735FreeOption FreeOption);

int J2735RoadSideAlert_Encode (const struct SAERoadSideAlert *pRSA,
                               uint8_t *pBuf,
                               int BufSize);

int J2735RoadSideAlert_Decode (struct SAERoadSideAlert **ppRSA,
                               const char *pBuf,
                               int BufSize);

#ifdef __cplusplus
}
#endif

#endif // __J2735_ROAD_SIDE_ALERT_H_
// Close the doxygen group
/**
 * @}
 */
