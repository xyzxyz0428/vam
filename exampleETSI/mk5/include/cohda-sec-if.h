/**
 * @addtogroup cohda_security ETSI ITS Security API
 * @{
 *
 * Interface for Public Security API
 *
 * @file
 *
 */

#ifndef __LIB_IF_SEC_COHDA_SEC_IF_H__
#define __LIB_IF_SEC_COHDA_SEC_IF_H__
//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "PacketBuffer.h"
#include "c2xsec.h"

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

/// Actions for secured received packets
typedef enum CohdaSec_RecvAction
{
  /// Extract, check relevance/consistency and verify
  COHDASEC_EXTRACT_CHECK_VERIFY = 0,
  /// verify only
  COHDASEC_VERIFY_ONLY = 1,

  /// Max
  COHDASEC_ACTIONS_MAX = 2,
} eCohdaSec_RecvAction;

/// @ref CohdaSec_RecvAction
typedef uint8_t tCohdaSec_RecvAction;

/** type for confirmation callback */
typedef void (*tSignedVerifiedConfirm) (struct UtilPacketBuffer *pPkt,
                                        int ret);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Security Library API
//------------------------------------------------------------------------------

int CohdaSec_SendPkt(struct UtilPacketBuffer *pPkt);

int CohdaSec_RecvPkt(tSignedVerifiedConfirm pVerifyCallback,
                     tCohdaSec_RecvAction Action,
                     struct UtilPacketBuffer *pPkt);

int CohdaSec_SignVerifyTest(struct UtilPacketBuffer *pPkt, bool IncludeEncryption, int *pCode);

tC2XSEC_Stats CohdaSec_GetStats(void);

int CohdaSec_RegisterChangeIdCallback(tC2XSEC_ClientType Client,
                                      fC2XSEC_ChangeIdCallback pCallback);
void CohdaSec_RequestNewID(tC2XSEC_ClientType Client);

void CohdaSec_LockIdChange(tC2XSEC_ClientType Client);
void CohdaSec_UnlockIdChange(tC2XSEC_ClientType Client);

uint8_t CohdaSec_GetValidATCertCount(void);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_IF_SEC_COHDA_SEC_IF_H__ */

// Close the doxygen group
/**
 * @}
 */
