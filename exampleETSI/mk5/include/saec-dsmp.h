/**
 * @addtogroup v2x_saec_dsmp SAEC Network DSMP API
 * @{
 *
 * This module provides an API to send/receive DSMP packets.
 *
 * The most commonly used functions are
 * - @ref SAECDSMP_Open : Open a DSMP port and register a callback to receive packets from DSMP
 *   - This returns a @ref tSAECDSMP which can then be used to later close the port
 * - @ref SAECDSMP_Close : Close the DSMP port and de-register the callback
 *
 * - @ref SAECDSMP_Send : Used to transmit generic payload via DSMP
 *   - Configure the packet transport type with the @ref SAECNetDesc parameters, and send the payload
 *   - This is the primary way for an Upper Layer entity to send a DSMP payload
 *
 * Function defined by DSMP client
 * - @ref fSAECDSMP_DataInd : function pointer type that is used to define Data Indication callback
 *   - The callback is provided with a @ref tSktBuf and the private data from @ref SAECDSMP_Open
 *   - The packet is freed with @ref SktBuf_Free
 *
 * Also implemented
 * - @ref SAECDSMP_DataInd : Used by the lower layers to deliver packets received (in a @ref tSktBuf)
 *   - The packet needs to be freed with @ref SktBuf_Free
 *
 * - @ref SAECDSMP_SendPkt : Used to transmit @ref tSktBuf via DSMP
 *   - A packet allocated with @ref SktBuf_AllocSAEC can be transmitted
 *   - This function is mainly used by the Upper Layer entity to send a DSMP payload that is already
 *     encapsulated.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_DSMP_H_
#define __SAEC_DSMP_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "id-global.h"
#include "ext.h"
#include "saec-sktbuf.h"
#include "saec-net-desc.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define SAECDSMP_PROMISCUOUS_AID 0xFFFFFFFF
//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// DSMP client handle
typedef struct SAECDSMP tSAECDSMP;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Callback indication of a received DSMP frame
 * @param pPriv The DSMP handle submitted in @ref SAECDSMP_Open
 * @param pBuf The packet buffer
 * @param pRxParams The Rx parameters of this indication
 *
 * This callback is invoked by the DSMP to deliver received frames to the upper layers
 */
typedef int fSAECDSMP_DataInd(void * pPriv, tSktBuf * pBuf, const tSAECNetDesc * pRxParams);

/**
 * @brief DSMP open/register
 *
 * Upper layer gets a DSMP handle by calling this function
 *
 * @param[in] DestAID AID number associated with the caller
 * @param[in] pPriv Caller's private data (provided to callback)
 * @param[in] pInd Callback indication function (must be set)
 * @return A tSAECDSMP* handle (NULL for error)
 */
tSAECDSMP *SAECDSMP_Open(uint32_t DestAID, void * pPriv, fSAECDSMP_DataInd * pInd);

/**
 * @brief DSMP Packet sending request (with payload)
 *
 * Create a DSMP Data Request using parameters provided
 * This creates the packet buffer and populates the element fields, and
 * copies the provided Payload to the packet buffer space.
 *
 * @param[in] pHandle DSMP handler
 * @param[in] pPayload DSMP payload
 * @param[in] PayloadLen DSMP payload length
 * @param[in] pTxParams Tx parameters
 * @return Status, 0 for success,
 *                 -EPROTO for invalid DSMP type
 *                 -EFAULT for invalid DSMP descriptor
 *                 -EFBIG for invalid DSMP length
 *                 -ENOMEM for Packet creation (memory) error
 *                 -EINVAL for invalid parameter
 *                 -EBUSY for messaging busy
 */
int SAECDSMP_Send(tSAECDSMP * pHandle,
                  const uint8_t * pPayload,
                  size_t PayloadLen,
                  const tSAECNetDesc * pTxParams);

/**
 * @brief DSMP Packet sending request (with Packet Buffer)
 *
 * Upper Layer calls this function to transmit a DSMP message
 *
 * @param[in] pHandle DSMP handler
 * @param[in] pPkt Request packet buffer
 * @param[in] pTxParams Tx parameters
 * @return Status, 0 for success,
 *                 -EPROTO for invalid DSMP type
 *                 -EFBIG for invalid DSMP length
 *                 -EBUSY for messaging busy
 */
int SAECDSMP_SendPkt(tSAECDSMP * pHandle, tSktBuf * pPkt, const tSAECNetDesc * pTxParams);

/**
 * @brief DSMP close/deregister
 *
 * Upper layer frees a DSMP handle by calling this function
 *
 * @param[in] pHandle A tSAECDSMP* handle to be freed
 *
 */
void SAECDSMP_Close(tSAECDSMP * pHandle);

/**
 * @brief Convert a (non-zero) p-encoded AID to its integer version
 * @param[in] AIDPEnc The p-encoded AID
 * @param[out] pAIDInt Pointer to integer AID (to store the result)
 * @return -1 on error. Number of valid bytes in pAIDInt on success.
 */
int SAECDSMP_DecodeAID(uint32_t AIDPEnc, uint32_t * pAIDInt);

/**
 * @brief Convert a (non-zero) integer AID to its p-encoded version
 * @param[in] AIDInt The integer AID
 * @param[out] pAIDPEnc Pointer to p-encoded AID (to store the result)
 * @return -1 on error. Number of valid bytes in pAIDPEnc on success.
 */
int SAECDSMP_EncodeAID(uint32_t AIDInt, uint32_t * pAIDPEnc);

#ifdef __cplusplus
}
#endif

#endif // __SAEC_DSMP_H_

/**
 * @}
 */
