/**
 * @addtogroup ubx uBlox GPS parsing library
 * @{
 *
 * Parses the binary uBlox packets and injects them into libpos
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __INCLUDE_UBX_EXTRACTOR_H_
#define __INCLUDE_UBX_EXTRACTOR_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
// Callback that is registered with tUBXExtractor to handle an extracted packet
typedef void tUBXPacketHandler(void * pBuf, int Length);

typedef struct UBXExtractor
{
  void * pPrivate;
} tUBXExtractor;
//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int UBXExtractor_Init(tUBXExtractor * pExtractor);

int UBXExtractor_SetPacketHandler(tUBXExtractor * pExtractor, tUBXPacketHandler * pHandler);

int UBXExtractor_EnableChecksum(tUBXExtractor * pExtractor, bool Enable);

int UBXExtractor_Process(tUBXExtractor * pExtractor, const uint8_t * pBuf, size_t Length);

int UBXExtractor_Deinit(tUBXExtractor * pExtractor);

#ifdef __cplusplus
}
#endif

#endif // __INCLUDE_UBX_EXTRACTOR_H_

/**
 * @}
 */
