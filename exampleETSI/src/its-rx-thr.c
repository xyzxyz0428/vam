/**
 * @addtogroup mod_its_rx ITS Rx Module
 * @{
 *
 * ITS receiver thread
 *
 * Registers with the EXT handler for events
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "ASNCommon.h"
#include "debug-levels.h"
#include "etsi-denm-if.h"
#include "etsi-cam-if.h"
#include "etsi-sa-if.h"
#include "etsi-sa-util.h"
#include "ext.h"
#include "id-global.h"
#include "its-ctrl-thr.h"
#include "itsasn.h"
#include "itsasn_def.h"
#include "util.h"

#include "libconfig.h" // used to read configuration file

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_ITSRx_DebugLevel

#define QSQUEUE_ITS_RX   QSQUEUE_APP1
#define QSMSG_ITS_RX_PDU QS_BASE_MSG_APP1

#define ITS_RX_RECV_TIMEOUT_MS (500)

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static void ITSRx_ThreadProc (void *pArg);

static void ITSRx_ExtCallback (tExtEventId Event,
                               tExtMessage *pData,
                               void *pPriv);

static void ITSRx_ProcessMessage (const tExtMessage *pData,
                                  struct ITSCtrl *pITS);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------

/**
 * @brief Allocate ITSRx object, Setup thread and associated data structures
 * @param pITS pointer to ITS handle
 * @return Zero for success or an negative errno
 */
int ITSRx_Open (struct ITSCtrl *pITS)
{
  int Res;

  // Init state

  // Assign thread attributes from input param
  pITS->Rx.ThreadAttr = pITS->Ctrl.ThreadAttr;

  // Create ITSRx thread
  pITS->Rx.ThreadState |= ITS_THREAD_STATE_INIT;
  Res = pthread_create(&pITS->Rx.ThreadID,
                       &pITS->Rx.ThreadAttr,
                       (void *)ITSRx_ThreadProc,
                       pITS);
  if (Res != 0)
  {
    d_error(D_ERR, 0, "pthread_create() failed\n");
    // Thread creation error
    pITS->Rx.ThreadState = ITS_THREAD_STATE_NONE;
    goto Error;
  }

  // Success!
  Res = 0;
  d_printf(D_INFO, 0, "Successfully started the its-rx\n");
  goto Success;

Error:
  d_error(D_ERR, 0, "Error!\n");
  ITSRx_Close(pITS);

Success:
  return Res;
}

/**
 * @brief Stop execution of ITS, free the thread and its associated resources
 * @param pITS ITS handle
 */
void ITSRx_Close (struct ITSCtrl *pITS)
{
  int Res;

  // Catch attempt to close invalid object pointer
  if (pITS == NULL)
  {
    Res = -EINVAL;
    goto Error;
  }

  // Signal thread to terminate
  pITS->Rx.ThreadState |= ITS_THREAD_STATE_STOP;
  // Wait for thread termination
  if (pITS->Rx.ThreadState & ITS_THREAD_STATE_INIT)
    pthread_join(pITS->Rx.ThreadID, NULL);

  // Success!
  Res = 0;

Error:
  (void)Res;    // value not currently used

  return;
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief EXT module Callback function
 * @param Event EXT event ID
 * @param pData EXT data associated with Event ID
 * @param pPriv Private data (tITSCtrl)
 *
 */
static void ITSRx_ExtCallback (tExtEventId Event,
                               tExtMessage *pData,
                               void *pPriv)
{

  struct ITSCtrl *pITS = (struct ITSCtrl *)pPriv;

  if ((Event != QSMSG_EXT_RX_ITSFL_PDU) || (pData == NULL))
    return;

  if (pData->pPDU->messageID > 0)
  {
    d_printf(D_INFO, NULL, "QSMSG_EXT_RX_ITSFL_PDU, PDU message id %d\n",
             pData->pPDU->messageID);

    // Perform quick processing in the callback
    // Any processing here is performed within the EXT notification thread's context
    switch (pData->pPDU->messageID)
    {
      case ITSItsPduHeaderMessageID_ID_denm:
      {
        const ITSDENM *pDenmPdu = pData->pDENM;
        d_printf(D_INFO, NULL,
                 "Received a decoded ITSFL DENM! StationId 0x%08x seqNo %d\n",
                 pDenmPdu->header.stationID,
                 pDenmPdu->denm.management.actionID.sequenceNumber);
         break;
      }

      case ITSItsPduHeaderMessageID_ID_cam:
      {
        const ITSCAM *pCamPdu = pData->pCAM;
        d_printf(D_INFO, NULL,
                 "Received a decoded ITSFL CAM! StationId 0x%08x dTime %d\n",
                 pCamPdu->header.stationID,
                 pCamPdu->cam.generationDeltaTime);
        break;
      }

      case ITSItsPduHeaderMessageID_ID_saem:
      {
        const ITSSAEM *pSAPdu = (const ITSSAEM *)pData->pPDU;
        d_printf(D_INFO, NULL,
                 "Received a decoded ITSFL SAEM! StationId 0x%08x, SAID %d, Change %d\n",
                 pSAPdu->header.stationID,
                 pSAPdu->sam.body.changeCount.saID,
                 pSAPdu->sam.body.changeCount.contentCount);
        break;
      }

      default:
        break;
    }

    pITS->Stats.Rx.Okay++;

    // Perform heavy processing in a dedicated worker thread
    // Ext_ForwardMsgTo() is non-blocking unless the Priority is QSPRIORITY_MAX.
    // Note that Ext_ForwardMsgTo() calls Ext_Retain() internally to increment the reference count
    // of tExtMessage.
    Ext_ForwardMsgTo(QSMSG_ITS_RX_PDU, QSQUEUE_ITS_RX, QSPRIORITY_DEFAULT, pData);
  }
}

/**
 * @brief ITS Periodic thread processing
 * @param pArg Pointer to @ref ITSCtrl object passed as generic input parameter
 *
 */
static void ITSRx_ThreadProc (void *pArg)
{
  struct ITSCtrl *pITS = (struct ITSCtrl *)pArg;

  const tQsStatus Status = Msg_QueueInit(QSQUEUE_ITS_RX);
  if (Status != QS_ERR_NONE)
  {
    d_error(D_ERR, NULL, "Unable to initialise its-rx message queue\n");
    pthread_exit(NULL);
  }

  // Register the callback with the Ext Module
  const int ExtHandle = Ext_CallbackRegister(ITSRx_ExtCallback, pITS);
  if (ExtHandle < 0)
  {
    d_error(D_ERR, NULL, "Unable to register callback with EXT module\n");
    (void)Msg_QueueDeInit(QSQUEUE_ITS_RX);
    pthread_exit(NULL);
  }

  pITS->Rx.ThreadState |= ITS_THREAD_STATE_RUN;
  // Thread loop
  while ((pITS->Rx.ThreadState & ITS_THREAD_STATE_STOP) == 0)
  {
    const struct timeval Timeout =
    {
      .tv_sec  = ITS_RX_RECV_TIMEOUT_MS / 1000,
      .tv_usec = (ITS_RX_RECV_TIMEOUT_MS % 1000) * 1000
    };
    tQsMessage Msg;

    const tQsStatus Stat = Msg_RecvTimed(QSQUEUE_ITS_RX, &Msg, &Timeout);
    if (Stat == QS_ERR_NO_QUEUE)
    {
      d_error(D_ERR, NULL, "No queue\n");
      // Don't hog the CPU
      Util_Sleep(ITS_RX_RECV_TIMEOUT_MS);
      continue;
    }
    else if (Stat == QS_ERR_TIMEOUT)
    {
      // Checking CAM info
      // Example of checking available CAM information (stationID & vehicle role)
      tCAMInfo Info = CAM_GetCurrentInfo();
      d_printf(D_INFO, NULL,
               "Local CAM StationId 0x%08x role %d\n",
               Info.stationID,
               Info.role);

      continue;
    }
    else if (Stat != QS_ERR_NONE)
    {
      d_error(D_ERR, NULL, "Failed to receive on its-rx queue\n");
      break;
    }

    switch (Msg.Id)
    {
      case QSMSG_ITS_RX_PDU:
      {
        tExtMessage * pExtMsg = Msg.Ref.pPayload;
        if (pExtMsg)
        {
          ITSRx_ProcessMessage(pExtMsg, pITS);
          Ext_Release(pExtMsg);
        }
        break;
      }
      default:
        break;
    }
  }

  d_printf(D_INFO, 0, "ITS Rx thread done\n");

  (void)Ext_CallbackDeregister(ExtHandle);
  (void)Msg_QueueDeInit(QSQUEUE_ITS_RX);
  pthread_exit(NULL);
}

/**
 * @brief Process messages received via the EXT callback, but in Rx Thread context
 * @param pData Ext Message to process
 * @param pITS pointer to ITS handle
 */
static void ITSRx_ProcessMessage (const tExtMessage *pData,
                                  struct ITSCtrl *pITS)
{
  d_assert(pData);

  (void)pITS;

  switch (pData->pPDU->messageID)
  {
    case ITSItsPduHeaderMessageID_ID_denm:
    {
      const ITSDENM *pDenmPdu = pData->pDENM;
      d_printf(D_INFO, NULL,
               "Processing a decoded ITSFL DENM! StationId 0x%08x seqNo %04x\n",
               pDenmPdu->header.stationID,
               pDenmPdu->denm.management.actionID.sequenceNumber);

      // Further example of how to access some details in the decoded DENM structure
      if (pDenmPdu->denm.situation_option)
      {
        d_printf(D_INFO, NULL,
                 "DENM has situation eventType with causeCode %d, subCauseCode %d\n",
                 pDenmPdu->denm.situation.eventType.causeCode,
                 pDenmPdu->denm.situation.eventType.subCauseCode);
      }

      // Example of avoiding unnecessary processing (e.g. when debug-level would inhibit output anyway)
      if (d_test(D_INFO))
      {
        unsigned int Len;
        uint8_t *pBuf;

        // Example of how to encode DENM to PER using the ASN utility function
        // ETSASN_EncodeToPER will create the buffer for the PER data
        pBuf = ETSASN_EncodeToPER(asn1_type_ITSDENM, pData->pPDU, &Len);
        d_printf(D_INFO, NULL, "DENM PER data is %d octets\n", Len);
        free(pBuf);

        // Example of how to encode DENM to XER using the ASN utility function
        // ETSASN_EncodeToXER will create the buffer for the XER string
        pBuf = (uint8_t *)ETSASN_EncodeToXER(asn1_type_ITSDENM, pData->pPDU, &Len);
        d_printf(D_INFO, NULL, "XER:\n%s", pBuf);
        free(pBuf);
      }

      break;
    }

    case ITSItsPduHeaderMessageID_ID_cam:
    {
      const ITSCAM *pCamPdu = pData->pCAM;
      d_printf(D_INFO, NULL,
               "Processing a decoded ITSFL CAM! StationId 0x%08x dTime %04d\n",
               pCamPdu->header.stationID,
               pCamPdu->cam.generationDeltaTime);

      // Example of avoiding unnecessary processing (e.g. when debug-level would inhibit output anyway)
      if (d_test(D_INFO))
      {
        // Example of how to encode CAM to GSER using the ASN utility function
        // ETSASN_GSERPrint will print the GSER-encoded data
        (void)ETSASN_GSERPrint(asn1_type_ITSCAM, pData->pPDU);
      }

      break;
    }

    case ITSItsPduHeaderMessageID_ID_saem:
    {
      tSAStatusCode Stat;
      const ITSSAEM *pSAPdu = (const ITSSAEM *)pData->pPDU;
      d_printf(D_INFO, NULL,
               "Processing a decoded ITSFL SAEM! StationId 0x%08x, SAID %d, Change %d\n",
               pSAPdu->header.stationID,
               pSAPdu->sam.body.changeCount.saID,
               pSAPdu->sam.body.changeCount.contentCount);

      tETSISA_Info SAInfo;

      // Get generic information
      Stat = ETSISA_UserInfoSA(pSAPdu, &SAInfo);

      if (Stat != ETSISA_SUCCESS)
      {
        break;
      }

      if (SAInfo.AdvIdLen > 0)
      {
        // Assume ASCII string for debug
        // But ensure AdvId null terminated
        SAInfo.AdvId[SAInfo.AdvIdLen] = '\0';
        d_printf(D_INFO, NULL, "AdvID %s\n", (char *)SAInfo.AdvId);
      }

      if (SAInfo.NumAID > 0)
      {
        // Demo service of interest
        uint32_t ITSAID = 0x200;

        if (SAInfo.AIDList.AID[0] == ITSAID)
        {
          tSAService Service;

          // Get service specific information
          Stat = ETSISA_UserQuerySA(pSAPdu, ITSAID, &Service);

          if (Stat == 0)
          {
            d_printf(D_INFO, NULL, "Found service %08x, PSC Len is %d, Application Data len is %d\n",
                     ITSAID, Service.PSCLen, Service.ApplicationDataLen);
          }
        }
      }
      break;
    }

    default:
    {
      d_printf(D_INFO, NULL, "Processing a decoded ITSFL with message id %d\n",
               pData->pPDU->messageID);
      break;
    }
  }
}

// Close the doxygen group
/**
 * @}
 */
