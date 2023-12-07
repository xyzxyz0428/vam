#pragma once
/**
 * @addtogroup v2v_ext_api External Notifications (EXT) API
 * @{
 *
 *
 * @section v2v_ext_api_wdid What Does It Do
 *
 * This library provides a notification mechanism for events with optional
 * payload or message data. Clients can register to receive notifications
 * (via callback) and optionally 'retain' (@ref Ext_Retain) these EXT
 * messages until no longer required, then they must be 'released'
 * (@ref Ext_Release). When no clients have retained an EXT message it
 * is destructed.
 *
 * @section v2v_ext_api_hdwui How Do We Use It
 *
 * System setup
 * - @ref Ext_Init
 * - @ref Ext_ThreadInit
 * - @ref Ext_ThreadDeinit
 * - @ref Ext_Exit
 *
 * Client setup functions
 * - @ref Ext_CallbackRegister
 * - @ref Ext_CallbackDeregister
 *
 * Reservation functions
 * - @ref Ext_Retain
 * - @ref Ext_Release
 *
 * Notification functions
 * - @ref Ext_Post (Asynchronously deliver an EXT message)
 * - @ref Ext_Send (Synchronously deliver an EXT message)
 * - @ref Ext_ForwardMsgTo (Forward EXT message to a specific message queue)
 *
 * @file
 *
 * Functional interface to the Ext module
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __EXT_H_
#define __EXT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
#include "qs-lib.h"
#ifdef __cplusplus
}
#endif


#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// @ref ExtEventId
typedef uint32_t tExtEventId;

/// Supported return codes from @ref fExt_Callback
typedef enum ExtStatus
{
  /// All errors are negative
  EXT_STATUS_ERROR = -1,
  /// No error
  EXT_STATUS_OK = 0,

  // EXT API return codes
  /// Error code for EXT API: lock failure
  EXT_STATUS_ELOCK = -101,
  /// Error code for EXT API: registration errors
  EXT_STATUS_EHANDLE = -102,
} eExtStatus;
/// @ref ExtStatus
typedef int tExtStatus;


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Pre-declaration of ExtMessage to allow circular callback/struct definitions
struct ExtMessage;

/// Function type for Asynchronous Verify application callback
typedef void (fAppAsyncVerifyCallback)(int Res, void *pData);

/**
 * @brief Prototype for a message destructor
 * @param pMsg The EXT message to destroy
 *
 */
typedef void (fExt_Destructor)(struct ExtMessage *pMsg);

/**
 * @brief Prototype for a message decoder.
 * @param pMsg The EXT message to decode
 * @return true if decoding worked
 *
 * @note The decoder must monotonically set pMsg->decoded to valid data.
 */
typedef bool (fExt_Decoder)(struct ExtMessage *pMsg);

/**
 * @brief Prototype for Crypto Helper
 *
 * @param pLastOTA The last received EXT message
 * @param pLastCert The last received EXT message with certificate embedded
 * @param pCallback Application callback of async verification
 * @param pCallbackPriv
 * @return 0 or -1 if there's an error
 */

typedef int (fExt_CryptoHelper)(struct ExtMessage *pLastOTA,
                                struct ExtMessage *pLastCert,
                                fAppAsyncVerifyCallback *pCallback,
                                void *pCallbackPriv);

// Possible OTA packet formats, 1609 and ITS
struct Dot3WSMPHdr;
struct UtilPacketBuffer;
typedef struct SktBuf tSktBuf;

// Possible payloads - 1609
struct J2735Msg;
struct SAEBasicSafetyMessage;
// Add more here, if required.

// Possible decoded - ITS
struct ITSItsPduHeader;
struct ITSCAM;
struct ITSDENM;
// Add more here, if required.

// Possible decoded - SAEC
struct SAECMessageFrame;
// Add more here, if required.

/// EXT message
typedef struct ExtMessage
{
  /// Raw over-the-air packet or equivalent.
  /// Non-const so we can free it, but beware that
  /// payload points somewhere within this.
  union
  {
    /// Raw access
    const void *pRaw;
    /// J2735
    struct Dot3WSMPHdr *pWSM;
    /// ITS
    struct UtilPacketBuffer *pPkt;
    /// SAEC
    tSktBuf *pSAECPkt;
  };
  /// Relevant payload from packet, probably ASN.1 encoded
  union
  {
    /// Raw access
    const void *pPayload;
    /// J2735 container
    const struct J2735Msg *pJ2735;
    /// SAEC container
    const struct SAECMessageFrame *pSAECMessageFrame;
  };
  /// Decoded ASN.1 structure, probably ITSDENM, ITSCAM, SAEBasicSafetyMessage
  /// or SAECMessageFrame
  union
  {
    // pointers are const because the contents should not be changed. ever.
    // Except for the destructor which will have to break const to clean up.
    const  void                         *pDecoded;
    const struct ITSItsPduHeader        *pPDU;
    const struct ITSCAM                 *pCAM;
    const struct ITSDENM                *pDENM;
    const struct ITSMAPEM               *pMAP;
    const struct ITSSPATEM              *pSPAT;
    const struct ITSIVIM                *pIVI;
    const struct ITSSREM                *pSREM;
    const struct ITSSSEM                *pSSEM;
    const struct ITSCPM                 *pCPM;
    const struct ITSSAEM                *pSAEM;
    const struct ITSMcdmPdu             *pMCDM;
    const struct ITSEvcsnPdu            *pEVCSN;
    const struct ITSRTCMEM              *pRTCM;

    const struct SAEBasicSafetyMessage       *pBSM;
    const struct SAETravelerInformation      *pTIM;
    const struct SAEMapData                  *pSAEMAP;
    const struct SAESPAT                     *pSAESPAT;
    const struct SAESensorDataSharingMessage *pSAESDSM;

    const struct SAECBasicSafetyMessage    *pSAECBSM;
    const struct SAECRoadSideInformation   *pSAECRSI;
    const struct SAECRoadsideSafetyMessage *pSAECRSM;
    const struct SAECMapData               *pSAECMAP;
    const struct SAECSPAT                  *pSAECSPAT;
  };
  /// ASN.1 type information (if decoded or otherwise available)
  /// ASN1CType
  const uintptr_t *pType;
} tExtMessage;


 /**
 * @brief Type for EXT event callback function
 * @param Evt Event identifier
 * @param pMsg The EXT message
 * @param pPriv Private pointer that was provided in Ext_CallbackRegister()
 *
 * @note The callback must call @ref Ext_Retain
 * (and eventually @ref Ext_Release) if the data is to be accessed
 * after the callback returns.
 */
typedef void (fExt_Callback) (tExtEventId Evt,
                              struct ExtMessage *pMsg,
                              void *pPriv);

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// EXT initialisation/deinitialisation API

/**
 * @brief Initialise the EXT library
 */
int Ext_Init (void);

/**
 * @brief Deinitialise the EXT library
 */
void Ext_Exit (void);

// EXT thread control API

/**
 * @brief Init function for EXT thread
 * @param SchedulerPolicy   application thread attribute
 * @param SchedulerPriority   application thread priority
 * @return 0 or one of the EXT error codes, @ref ExtStatus
 *
 * Init EXT thread by creating thread and allowing thread to
 * setup its interfaces
 *
 */
int Ext_ThreadInit (int SchedulerPolicy,
                    int SchedulerPriority);

/**
 * @brief Deinit function for EXT thread
 *
 */
void Ext_ThreadDeinit (void);

// EXT client API

/**
 * @brief Client registration for EXT notifications
 * @param pFunc Client's handler function
 * @param pPriv A private pointer to provide to the handler function
 * @return A handle to use when de-registering (>= 0)
 *         A negative value indicates failure
 */
int Ext_CallbackRegister (fExt_Callback *pFunc,
                          void *pPriv);

/**
 * @brief Client de-registration for EXT notifications
 * @param Handle Handle to de-register
 * as obtained from @ref Ext_CallbackRegister
 * @return 0 or one of the EXT error codes, @ref ExtStatus
 *
 */
int Ext_CallbackDeregister (int Handle);

/**
 * @brief Asynchronously deliver an EXT message.
 * @param Evt EXT Event Id (@ref ExtEventId)
 * @param pRaw Pointer to Raw packet
 * @param pPayload Pointer to payload within Raw packet
 * @param pDecoded Pointer to decoded payload
 * @param pType Pointer to payload type
 * @param pDestructor Cleanup function
 * @param pDecoder ASN1 decode function
 * @param pCrypto Verification on demand function
 * @return 0 if the message was posted
 *
 * @note that, even if posting the message fails,
 * the @ref fExt_Destructor is called.
 */
int Ext_Post (tExtEventId Evt,
              const void *pRaw,
              const void *pPayload,
              const void *pDecoded,
              const void *pType,
              fExt_Destructor *pDestructor,
              fExt_Decoder *pDecoder,
              fExt_CryptoHelper *pCrypto);

/**
 * @brief Asynchronously deliver a message containing a malloc'ed pointer
 * @param Evt EXT Event Id (@ref ExtEventId)
 * @param pPayload Pointer to payload
 * @return 0 if the message was posted
 *
 * @note that pPayload is free()'d even if the message fails to send
 */
int Ext_PostRef (tExtEventId Evt,
                 const void *pPayload);

/**
 * @brief Synchronously deliver an EXT message
 * @param Evt EXT Event Id (@ref ExtEventId)
 * @param pRaw Pointer to Raw packet
 * @param pPayload Pointer to payload within Raw packet
 * @param pDecoded Pointer to decoded payload
 * @param pType Pointer to payload type
 * @param pDestructor Cleanup function
 * @param pDecoder ASN1 decode function
 * @param pCrypto Verification on demand function
 *
 * @note that pPayload is free()'d even if the call fails
 */
void Ext_Send (tExtEventId Evt,
               const void *pRaw,
               const void *pPayload,
               const void *pDecoded,
               const void *pType,
               fExt_Destructor *pDestructor,
               fExt_Decoder *pDecoder,
               fExt_CryptoHelper *pCrypto) __attribute__((deprecated));

/**
 * @brief Forward message via given queue
 *
 * The message is @ref Ext_Retain -ed by this call.
 * If the message send fails it is @ref Ext_Release -ed again,
 * otherwise the receiver must call @ref Ext_Release
 *
 * @param Evt      Evt EXT Event Id (@ref ExtEventId)
 * @param Queue    Target message queue
 * @param Priority Message queue priority
 * @param pMsg     EXT Message to send
 */
void Ext_ForwardMsgTo(tExtEventId Evt,
                      tQsQueueId Queue,
                      tQsPriority Priority,
                      struct ExtMessage *pMsg);

/**
 * @brief Request that an EXT message be retained
 * @param pMsg The message to be retained
 *
 * Destruction of the message (@ref fExt_Destructor) is delayed until
 * @ref Ext_Release is invoked the appropriate number of times.
 *
 */
void Ext_Retain (struct ExtMessage *pMsg);

/**
 * @brief Synchronously lazy-decode the message.
 * @param pMsg The EXT message to decode
 * @return true if the decoded data is available
 *
 * The first invocation to this function per
 * message will call the decoder.
 * Subsequent invocations will return as soon as
 * the decode has finished.
 * (see @ref fExt_Decoder)
 *
 * Note that it is not safe to use pMsg->pDecoded unless
 * this method is invoked and returns true.
 */
bool Ext_Decode (struct ExtMessage *pMsg);

/**
 * @brief Invoke the crypto helper (verification)
 * @param pLastOTA The last OTA Ext message
 * @param pLastCert The last Ext message with certificate attached
 * @param pCallback The callback after verification is complete
 * @param pCallbackPriv private data for callback
 * @return Status, zero for success otherwise negative error code
 */
int Ext_Crypto (struct ExtMessage *pLastOTA,
                struct ExtMessage *pLastCert,
                fAppAsyncVerifyCallback *pCallback,
                void *pCallbackPriv);

/**
 * @brief Release and potentially clean up (@ref fExt_Destructor) an EXT message.
 * @param pMsg The EXT message to release/destroy.
 *
 * The last caller to release the message will cause synchronous cleanup.
 * (see @ref Ext_Retain, @ref fExt_Destructor)
 */
void Ext_Release (struct ExtMessage *pMsg);

#ifdef __cplusplus
}
#endif

#endif // __EXT_H_
/**
 * @}
 */
