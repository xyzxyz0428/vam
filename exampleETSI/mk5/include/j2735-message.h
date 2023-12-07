/**
 * @addtogroup v2v_j2735_api
 * @{
 *
 * @section v2v_j2735_api_md Message Description
 * ASN.1 en/de-coding of J2735 messages.
 *
 * @file j2735-message.h J2735 Interface to the J2735 Library.
 *
 *
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_MESSAGE_H_
#define __J2735_MESSAGE_H_

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

#define J2735_MsgExtractBSM(pMsg) \
  ((SAEBasicSafetyMessage *)\
   J2735_MsgExtract(pMsg, SAEDSRCmsgID_basicSafetyMessage))

#define J2735_MsgExtractRSA(pMsg) \
  ((SAERoadSideAlert *)\
   J2735_MsgExtract(pMsg, SAEDSRCmsgID_roadSideAlert))

#define J2735_MsgExtractTIM(pMsg) \
  ((SAETravelerInformation *)\
   J2735_MsgExtract(pMsg, SAEDSRCmsgID_travelerInformation))

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Generic decoded 'J2735' message
typedef struct J2735Msg
{
  // Set by J2735_MsgPERDecode() from its pBuf & Len parameters
  struct {
    /// The UPER encoded (over-the-air) bytes.
    const char *pEncoded;
    /// The length of above pEncoded buffer
    size_t EncodedLen;
  };

  /// DSRC Msg ID (@sa e_DSRCmsgID)
  uint32_t DSRCmsgID;
  /// Decoded message
  union
  {
    void                           *pAny;
    SAEBasicSafetyMessage          *pBSM;
    SAECommonSafetyRequest         *pCSR;
    SAEEmergencyVehicleAlert       *pEVA;
    SAEIntersectionCollision       *pICA;
    SAEMapData                     *pMAP;
    SAENMEAcorrections             *pNMEA;
    SAEProbeDataManagement         *pPDM;
    SAEProbeVehicleData            *pPVD;
    SAERoadSideAlert               *pRSA;
    SAERTCMcorrections             *pRTCM;
    SAESPAT                        *pSAESPAT;
    SAESignalRequestMessage        *pSRM;
    SAESignalStatusMessage         *pSSM;
    SAETravelerInformation         *pTIM;
    SAESensorDataSharingMessage    *pSDSM;
  };
} tJ2735Msg;

// forward declaration for extraction helper
struct ExtMessage;
struct Dot3WSMPHdr;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

const ASN1CType *J2735_MsgIdToType(int DSRCMsgId);

int J2735_MsgInspect(struct Dot3WSMPHdr *pWSM,
                     char **ppPER,
                     int *pPERLen);

int J2735_MsgDecode(struct J2735Msg **ppMsg,
                    const char *pBuf,
                    int Len);

void J2735_MsgFree(struct J2735Msg *pMsg);

// UPER encode/decode
int J2735_MsgPERDecode(struct J2735Msg **ppMsg,
                       const char *pBuf,
                       int Len);

int J2735_MsgPEREncode(const struct J2735Msg *pMsg,
                       char *pBuf,
                       int Len);

// XER encode/decode
int J2735_MsgXERDecode(struct J2735Msg **ppMsg,
                       const char *pBuf,
                       int Len);

int J2735_MsgXEREncode(const struct J2735Msg *pMsg,
                       char *pBuf,
                       int Len);

// Helper function to extract messages
const void *J2735_MsgExtract(struct ExtMessage *pMsg,
                             uint32_t DSRCmsgID);

#ifdef __cplusplus
}
#endif

#endif // __J2735_MESSAGE_H_
// Close the doxygen group
/**
 * @}
 */
