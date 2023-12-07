/**
 * @addtogroup mod_its_tx ITS Tx Module
 * @{
 *
 * ITS transmitter thread
 *
 * Constructs BTPs when requested by messages sent to this thread.
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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "libconfig.h" // used to read configuration file

// v2x-lib includes
#include "etsi-fac-c2c-if.h"
#include "etsi-denm-if.h"
#include "ASNCommon.h"
#include "lph.h"
#include "ext.h"
#include "vstate.h"
#include "Vector.h"
#include "util.h"
#include "qs-lib.h"
#include "debug-levels.h"

#include "its-ctrl-thr.h"
#include "message.h"
#include "etsi-map-if.h"
#include "etsi-spat-if.h"
#include "etsi-ivi-if.h"
#include "etsi-sa-if.h"
#include "etsi-rtcm-if.h"
#include "etsi-cpm-if.h"
#include "etsi-vam-if.h"
#include "etsi-imzm-if.h"
#include "etsi-srmssm-if.h"

#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_ITSTx_DebugLevel

#define LATLON_UNITS_PER_DEGREE          (10000000)

// IVI delta validity max is 1 day
#define MAX_IVI_VALIDITY_DELTA (24 * 60 * 60 * 1000)

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static void ITSTx_ThreadProc (void *pArg);

static int DENMTx_SendDENMTrigger_RoadWorks  (struct ITSCtrl *pITS);
static int DENMTx_SendDENMTerminate_RoadWorks(struct ITSCtrl *pITS);

static int DENMTx_SendDENMTrigger_EEBL(struct ITSCtrl *pITS);
static int DENMTx_SendDENMTrigger_EVW (struct ITSCtrl *pITS);

static void ITSTx_PrepareSpat(const tITSTxSPATParams *pParams, tSPATMgmt *pMgmt, ITSSPAT *pSpat);
static void ITSTx_UpdateSpatTiming(const tITSTxSPATParams *pParams, ITSSPAT *pSpat);
static void ITSTx_PrepareMap(const tITSTxMAPParams *pParams, tMAPMgmt *pMgmt, ITSMapData *pMapData);
static void ITSTx_PrepareSrm(const tITSTxSRMParams *pParams, tSRMMgmt *pMgmt, ITSSignalRequestMessage *pSrmData);
static void ITSTx_PrepareSsm(const tITSTxSSMParams *pParams, tSSMMgmt *pMgmt, ITSSignalStatusMessage *pSsmData);
static void ITSTx_PrepareSA(const tITSTxSAParams *pParams, tSAMgmt *pMgmt, tSAMsg *pSAMsg);
static void ITSTx_PrepareRTCM(const tITSTxRTCMParams *pParams, tRTCMMgmt *pMgmt, ITSRTCMcorrections *pRTCMcorrections);
static void ITSTx_PrepareIvi(const tITSTxIVSParams *pParams, tIVIMgmt *pMgmt, ITSIviStructure *pIVI);
static void ITSTx_TerminateIvi(const tITSTxIVSParams *pParams, tIVIMgmt *pMgmt, ITSIviStructure *pIVI);
static void ITSTx_PrepareCpm(const tITSTxCPMParams *pParams, tCPMMgmt *pMgmt, ITSCollectivePerceptionMessage *pCpm);
static void ITSTx_PrepareVam(const tITSTxVAMParams *pParams, tVAMMgmt *pMgmt, ITSVruAwareness *pVam);
static void ITSTx_PrepareImzm(const tITSTxIMZMParams *pParams, tIMZMMgmt *pMgmt, ITSInterferenceManagementZoneMessage *pImzmData);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------

// Message management
tSPATMgmt SpatMgmt;
tMAPMgmt MapMgmt;
tIVIMgmt IviMgmt;
tIVIMgmt IviMgmt2;
tSRMMgmt SrmMgmt;
tSSMMgmt SsmMgmt;
tSAMgmt SAMgmt;
tRTCMMgmt RTCMMgmt;
tCPMMgmt CpmMgmt;
tVAMMgmt VamMgmt;
tIMZMMgmt IMZMMgmt;

// DENM information
tDENMActionID RWWActionId;
tDENMActionID RWWActionId2;
tDENMActionID RWWActionId3;
tDENMActionID RWWActionId4;

tDENMMgmt RWWMgmt;
tDENMMgmt RWWMgmt2;
tDENMMgmt RWWMgmt3;
tDENMMgmt RWWMgmt4;

ITSDecentralizedEnvironmentalNotificationMessage *pRWWMsg = NULL;
ITSDecentralizedEnvironmentalNotificationMessage *pRWWMsg2 = NULL;
ITSDecentralizedEnvironmentalNotificationMessage *pRWWMsg3 = NULL;
ITSDecentralizedEnvironmentalNotificationMessage *pRWWMsg4 = NULL;

static uint64_t LastRoadWorkerTime = 0;
static tVector LastRoadWorkerPos;
static tVector LastTraceRoadWorkerPos;

//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------


/**
 * @brief Allocate ITS object, Setup thread and associated data structures
 * @param pITS pointer to ITS handle
 * @return Zero for success or an negative errno
 */
int ITSTx_Open (struct ITSCtrl *pITS)
{
  int Res = -ENOSYS;

  // Create the ITSTX message queue
  tQsStatus SStat = Msg_QueueInit(QSQUEUE_ITSTX);
  if (SStat != QSSTATUS_OK)
  {
    d_error(D_WARN, NULL, "Failed to set up ITSTX message queue\n");
    goto Error;
  }

  // Init state
  pITS->Tx.pLPH_Handle = LPH_Open();

  // Assign thread attributes from input param
  pITS->Tx.ThreadAttr = pITS->Ctrl.ThreadAttr;

  // Create ITSCtrl thread
  pITS->Tx.ThreadState |= ITS_THREAD_STATE_INIT;
  Res = pthread_create(&pITS->Tx.ThreadID,
                       &pITS->Tx.ThreadAttr,
                       (void *) ITSTx_ThreadProc,
                       pITS);
  if (Res != 0)
  {
    d_error(D_ERR, 0, "pthread_create() failed\n");
    // Thread creation error
    pITS->Tx.ThreadState = ITS_THREAD_STATE_NONE;
    goto Error;
  }

  // Success!
  Res = 0;
  d_printf(D_INFO, 0, "Successfully started the its-tx\n");
  goto Success;

Error:
  d_error(D_ERR, 0, "Error!\n");
  ITSTx_Close(pITS);

Success:
  return Res;
}

/**
 * @brief Stop execution of ITS, free the thread and its associated resources
 * @param pITS pointer to ITS handle
 */
void ITSTx_Close (struct ITSCtrl *pITS)
{
  if ((pITS->Tx.RWW.Enabled) || (pITS->Tx.IVI.Enabled))
  {
    // Some time for cancel DENMs/IVIs to be processed before sending terminate message
    Util_Sleep(500);
  }

  tQsStatus SStat = Msg_SendId(QSMSG_SYS_TERMINATE, QSQUEUE_ITSTX, QSPRIORITY_MAX);

  LPH_Close(pITS->Tx.pLPH_Handle);

  if (SStat != QSSTATUS_OK)
  {
    d_printf(D_DEBUG, NULL, "ITS thread deinit:QSMSG_SYS_TERMINATE fail\n");
    pITS->Tx.ThreadState |= ITS_THREAD_STATE_STOP;
  }

  // Wait for thread termination
  if (pITS->Tx.ThreadState & ITS_THREAD_STATE_INIT)
    pthread_join(pITS->Tx.ThreadID, NULL);

  Msg_QueueDeInit(QSQUEUE_ITSTX);

  return;
}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief EXT module Callback function
 * @param Event EXT event ID
 * @param pData EXT data associated with Event ID
 * @param pPriv Private data
 *
 */
void ExtCallback(tExtEventId Event,
                 tExtMessage *pData,
                 void *pPriv)
{
  d_printf(D_DEBUG, NULL, "Event 0x%04x\n", Event);

  tITSCtrl *pITS = (tITSCtrl *)pPriv;

  switch (Event)
  {
    case QSMSG_EXT_VSTATE_EVENT:
    {
      d_assert(pData != NULL);

      tVstateEvents *pVEvent = (tVstateEvents *)pData->pPayload;

      d_printf(D_DEBUG, NULL, "Alert 0x%04x\n", pVEvent->Current);

      if (pVEvent->Current & VSTATE_ALERT_HARDBRAKING)
      {
        d_printf(D_DEBUG, NULL, "VSTATE_ALERT_HARDBRAKING\n");

        // EEBL trigger can be disabled
        // e.g. when EEBL safety app is used to trigger DENM
        if (pITS->Tx.EEBL.Enabled == true)
        {
          // Trigger EEBL
          (void)Msg_SendId(QSMSG_ITS_DENM_EEBL_TX_REQ,
                           QSQUEUE_ITSTX, QSPRIORITY_HIGH);
        }
      }
      break;
    }
  }
}

/**
 * @brief ITS Periodic thread processing - sends a ITS
 * @param pArg Pointer to ITSCtrl object passed as generic input parameter
 *
 */
static void ITSTx_ThreadProc (void *pArg)
{
  tSPATMgmt *pSpatMgmt = &SpatMgmt;
  ITSSPAT *pSpatData = NULL;
  tMAPMgmt *pMapMgmt = &MapMgmt;
  ITSMapData *pMapData = NULL;
  tIVIMgmt *pIviMgmt = &IviMgmt;
  ITSIviStructure *pIviData = NULL;
  tIVIMgmt *pIviMgmt2 = &IviMgmt2;
  ITSIviStructure *pIviData2 = NULL;
  tSRMMgmt *pSrmMgmt = &SrmMgmt;
  ITSSignalRequestMessage *pSrmData = NULL;
  tSSMMgmt *pSsmMgmt = &SsmMgmt;
  ITSSignalStatusMessage *pSsmData = NULL;
  tSAMgmt *pSAMgmt = &SAMgmt;
  tSAMsg SAMsg;
  tRTCMMgmt *pRTCMMgmt = &RTCMMgmt;
  ITSRTCMcorrections *pRtcmData = NULL;
  tCPMMgmt *pCpmMgmt = &CpmMgmt;
  ITSCollectivePerceptionMessage *pCpmData = NULL;
  tVAMMgmt *pVamMgmt = &VamMgmt;
  ITSVruAwareness *pVamData = NULL;
  tIMZMMgmt *pImzmMgmt = &IMZMMgmt;
  ITSInterferenceManagementZoneMessage *pImzmData = NULL;
  struct ITSCtrl *pITS;
  int ExtHandle;

  // pArg cast to ITStx object
  pITS = (struct ITSCtrl *) pArg;

  // Register the callback with the Ext Module
  ExtHandle = Ext_CallbackRegister(ExtCallback, pITS);

  if (ExtHandle < 0)
  {
    d_error(D_DEBUG, NULL, "Unable to register callback with EXT module\n");
    goto Error;
  }

  // "Starting ITS Periodic Thread");
  pITS->Tx.ThreadState |= ITS_THREAD_STATE_RUN;

  if (pITS->Tx.RWW.Enabled)
  {
    pRWWMsg = asn1_mallocz(sizeof(ITSDecentralizedEnvironmentalNotificationMessage));
  }

  if (pITS->Tx.RWW2.Enabled)
  {
    pRWWMsg2 = asn1_mallocz(sizeof(ITSDecentralizedEnvironmentalNotificationMessage));
  }

  if (pITS->Tx.RWW3.Enabled)
  {
    pRWWMsg3 = asn1_mallocz(sizeof(ITSDecentralizedEnvironmentalNotificationMessage));
  }

  if (pITS->Tx.RWW4.Enabled)
  {
    pRWWMsg4 = asn1_mallocz(sizeof(ITSDecentralizedEnvironmentalNotificationMessage));
  }

  // Prepare SPAT message to be updated and sent periodically
  if(pITS->Tx.SPAT.Enabled)
  {
    pSpatData = asn1_mallocz(sizeof(ITSSPAT));

    ITSTx_PrepareSpat(&pITS->Tx.SPAT, pSpatMgmt, pSpatData);
  }

  // Prepare MAP message to be sent periodically
  if(pITS->Tx.MAP.Enabled)
  {
    pMapData = asn1_mallocz(sizeof(ITSMapData));

    ITSTx_PrepareMap(&pITS->Tx.MAP, pMapMgmt, pMapData);
  }

  // Prepare SRM message to be sent periodically
  if(pITS->Tx.SRM.Enabled)
  {
    pSrmData = asn1_mallocz(sizeof(ITSSignalRequestMessage));

    ITSTx_PrepareSrm(&pITS->Tx.SRM, pSrmMgmt, pSrmData);
  }

  // Prepare SSM message to be sent periodically
  if(pITS->Tx.SSM.Enabled)
  {
    pSsmData = asn1_mallocz(sizeof(ITSSignalStatusMessage));

    ITSTx_PrepareSsm(&pITS->Tx.SSM, pSsmMgmt, pSsmData);
  }

  // Prepare IMZM message to be sent periodically
  if(pITS->Tx.IMZM.Enabled)
  {
    pImzmData = asn1_mallocz(sizeof(ITSInterferenceManagementZoneMessage));

    ITSTx_PrepareImzm(&pITS->Tx.IMZM, pImzmMgmt, pImzmData);
  }

  // Prepare SA message to be sent periodically
  if(pITS->Tx.SA.Enabled)
  {
    ITSTx_PrepareSA(&pITS->Tx.SA, &SAMgmt, &SAMsg);
  }

  // Prepare RTCM message to be sent periodically
  if(pITS->Tx.RTCM.Enabled)
  {
    pRtcmData = asn1_mallocz(sizeof(ITSRTCMcorrections));

    ITSTx_PrepareRTCM(&pITS->Tx.RTCM, pRTCMMgmt, pRtcmData);
  }

  // Prepare CPM message to be sent periodically
  if(pITS->Tx.CPM.Enabled)
  {
    pCpmData = asn1_mallocz(sizeof(ITSCollectivePerceptionMessage));

    ITSTx_PrepareCpm(&pITS->Tx.CPM, pCpmMgmt, pCpmData);
  }

  // Prepare VAM message to be sent periodically
  if(pITS->Tx.VAM.Enabled)
  {
    pVamData = asn1_mallocz(sizeof(ITSVruAwareness));

    ITSTx_PrepareVam(&pITS->Tx.VAM, pVamMgmt, pVamData);
  }

  // Prepare IVI message to be sent periodically
  if(pITS->Tx.IVI.Enabled)
  {
    if(pITS->Tx.IVS.Enabled)
    {
      pIviData = asn1_mallocz(sizeof(ITSIviStructure));

      ITSTx_PrepareIvi(&pITS->Tx.IVS, pIviMgmt, pIviData);
    }
    if(pITS->Tx.IVS2.Enabled)
    {
      pIviData2 = asn1_mallocz(sizeof(ITSIviStructure));

      ITSTx_PrepareIvi(&pITS->Tx.IVS2, pIviMgmt2, pIviData2);
    }
  }

  // Thread loop
  while ((pITS->Tx.ThreadState & ITS_THREAD_STATE_STOP) == 0)
  {
    tQsStatus RStat;
    tQsMessage RecvMsg;

    // Wait on received message
    RStat = Msg_Recv(QSQUEUE_ITSTX, &RecvMsg);

    if (RStat != QSSTATUS_OK)
    {
      d_error(D_ERR, 0, "Msg_Recv failed (%d)\n", RStat);
      continue;
    }

    d_printf(D_INFO, NULL, "ITSTx message id (0x%04x)\n", RecvMsg.Id);

    // Got a message, handle it
    switch (RecvMsg.Id)
    {
      case QSMSG_ITS_DENM_ROADWORKS_TX_REQ:
        DENMTx_SendDENMTrigger_RoadWorks(pITS);
        break;

      case QSMSG_ITS_DENM_ROADWORKS_TERMINATE_TX_REQ:
        DENMTx_SendDENMTerminate_RoadWorks(pITS);
        break;

      case QSMSG_ITS_DENM_EEBL_TX_REQ:
        DENMTx_SendDENMTrigger_EEBL(pITS);
        break;

      case QSMSG_ITS_DENM_EVW_TX_REQ:
        DENMTx_SendDENMTrigger_EVW(pITS);
        break;

      case QSMSG_ITS_SPAT_TX_REQ:
      {
        ITSTx_UpdateSpatTiming(&pITS->Tx.SPAT, pSpatData);
        ETSISPAT_SendSPAT(pSpatMgmt, pSpatData);
        break;
      }

      case QSMSG_ITS_MAP_TX_REQ:
      {
        ETSIMAP_SendMAP(pMapMgmt, pMapData, 0x1);
        break;
      }

      case QSMSG_ITS_SRM_TX_REQ:
      {
        ETSISRMSSM_SendSRM(pSrmMgmt, pSrmData, 0x1);
        break;
      }

      case QSMSG_ITS_SSM_TX_REQ:
      {
        ETSISRMSSM_SendSSM(pSsmMgmt, pSsmData, 0x1);
        break;
      }

      case QSMSG_ITS_IMZM_TX_REQ:
      {
        ETSIIMZM_SendIMZM(pImzmMgmt, pImzmData, 0x1);
        break;
      }

      case QSMSG_ITS_SA_TX_REQ:
      {
        ETSISA_ProviderUpdateSA(pSAMgmt, &SAMsg, 0x0);
        break;
      }

      case QSMSG_ITS_RTCM_TX_REQ:
      {
        ETSIRTCM_SendRTCM(pRTCMMgmt, pRtcmData);
        break;
      }

      case QSMSG_ITS_CPM_TX_REQ:
      {
        ETSICPM_SendCPM(pCpmMgmt, pCpmData);
        break;
      }

      case QSMSG_ITS_VAM_TX_REQ:
      {
        ETSIVAM_SendVAM(pVamMgmt, pVamData);
        break;
      }

      case QSMSG_ITS_IVI_TX_REQ:
      {
        if(pITS->Tx.IVI.Enabled)
        {
          tIVIStatusCode Status;

          if (pITS->Tx.IVS.Enabled)
          {
            if (pITS->Tx.IVS.IviIDAssigned == 0)
            {
              Status = ETSIIVI_SendIVINew(pIviMgmt, pIviData, ETSIIVI_NEW_ID_APPL_DEFINED);
              pITS->Tx.IVS.IviIDAssigned = 1;
            }
            else
            {
              if (pITS->Tx.IVS.ValidToTime <= MAX_IVI_VALIDITY_DELTA)
              {
                // Check Validity for update
                uint64_t refT = LPH_Leap2004Now();
                uint64_t validT = ETSASN_GetTimestamp(&pIviData->mandatory.validTo);
                if (refT > validT - (pITS->Tx.IVS.ValidToTime/2))
                {
                  d_printf(D_INFO, NULL, "ValidTo (%" PRIu64 ") updated by %" PRIu64 ")\n",
                           validT, pITS->Tx.IVS.ValidToTime);
                  ETSASN_SetTimestamp(&pIviData->mandatory.validTo, validT + pITS->Tx.IVS.ValidToTime);
                }
              }

              Status = ETSIIVI_SendIVIUpdate(pIviMgmt, pIviData, ETSIIVI_UPDATE_ID_APPL_DEFINED);
            }

            if (Status != ETSIIVI_SUCCESS)
            {
              d_printf(D_WARN, 0, "IVI 1 new/update failed (%d)\n", Status);
            }
          }

          if (pITS->Tx.IVS2.Enabled)
          {
            if (pITS->Tx.IVS2.IviIDAssigned == 0)
            {
              Status = ETSIIVI_SendIVINew(pIviMgmt2, pIviData2, ETSIIVI_NEW_ID_APPL_DEFINED);
              pITS->Tx.IVS2.IviIDAssigned = 1;
            }
            else
            {
              if (pITS->Tx.IVS2.ValidToTime <= MAX_IVI_VALIDITY_DELTA)
              {
                // Check Validity for update
                uint64_t refT = LPH_Leap2004Now();
                uint64_t validT = ETSASN_GetTimestamp(&pIviData2->mandatory.validTo);
                if (refT > (validT - (pITS->Tx.IVS2.ValidToTime/2)))
                {
                  d_printf(D_INFO, NULL, "ValidTo (%" PRIu64 ") updated by %" PRIu64 ")\n",
                           validT, pITS->Tx.IVS2.ValidToTime);
                  ETSASN_SetTimestamp(&pIviData2->mandatory.validTo, validT + pITS->Tx.IVS2.ValidToTime);
                }
              }

              Status = ETSIIVI_SendIVIUpdate(pIviMgmt2, pIviData2, ETSIIVI_UPDATE_ID_APPL_DEFINED);
            }

            if (Status != ETSIIVI_SUCCESS)
            {
              d_printf(D_WARN, 0, "IVI 2 new/update failed (%d)\n", Status);
            }
          }
        }
        break;
      }

      case QSMSG_ITS_IVI_TERMINATE_TX_REQ:
        if(pITS->Tx.IVI.Enabled)
        {
          if (pITS->Tx.IVS.Enabled)
          {
            ITSTx_TerminateIvi(&pITS->Tx.IVS, pIviMgmt, pIviData);

            if (pITS->Tx.IVS.IviIDAssigned != 0)
            {
              tIVIStatusCode Status;

              Status = ETSIIVI_SendIVITermination(pIviMgmt, pIviData, ETSIIVI_UPDATE_ID_APPL_DEFINED);

              if (Status != ETSIIVI_SUCCESS)
              {
                d_printf(D_WARN, 0, "IVI 1 termination failed (%d)\n", Status);
              }
            }
          }

          if (pITS->Tx.IVS2.Enabled)
          {
            ITSTx_TerminateIvi(&pITS->Tx.IVS2, pIviMgmt2, pIviData2);

            if (pITS->Tx.IVS2.IviIDAssigned != 0)
            {
              tIVIStatusCode Status;

              Status = ETSIIVI_SendIVITermination(pIviMgmt2, pIviData2, ETSIIVI_UPDATE_ID_APPL_DEFINED);

              if (Status != ETSIIVI_SUCCESS)
              {
                d_printf(D_WARN, 0, "IVI 2 termination failed (%d)\n", Status);
              }
            }
          }
        }
        break;

      case QSMSG_SYS_TERMINATE:
        pITS->Tx.ThreadState |= ITS_THREAD_STATE_STOP;
        break;

      default:
        d_printf(D_WARN, 0, "Unsupported message ID (%d)\n", RecvMsg.Id);
        break;
    }
  }

  d_printf(D_INFO, 0, "ITS Tx thread done\n");

  if (pRWWMsg != NULL)
  {
    asn1_free_value(asn1_type_ITSDecentralizedEnvironmentalNotificationMessage, pRWWMsg);
  }
  if (pRWWMsg2 != NULL)
  {
    asn1_free_value(asn1_type_ITSDecentralizedEnvironmentalNotificationMessage, pRWWMsg2);
  }
  if (pRWWMsg3 != NULL)
  {
    asn1_free_value(asn1_type_ITSDecentralizedEnvironmentalNotificationMessage, pRWWMsg3);
  }
  if (pRWWMsg4 != NULL)
  {
    asn1_free_value(asn1_type_ITSDecentralizedEnvironmentalNotificationMessage, pRWWMsg4);
  }
  if (pSpatData != NULL)
  {
    asn1_free_value(asn1_type_ITSSPAT, pSpatData);
  }
  if (pMapData != NULL)
  {
    asn1_free_value(asn1_type_ITSMapData, pMapData);
  }
  if (pSrmData != NULL)
  {
    asn1_free_value(asn1_type_ITSSignalRequestMessage, pSrmData);
  }
  if (pSsmData != NULL)
  {
    asn1_free_value(asn1_type_ITSSignalStatusMessage, pSsmData);
  }
  if (pImzmData != NULL)
  {
    asn1_free_value(asn1_type_ITSInterferenceManagementZoneMessage, pImzmData);
  }
  if (pIviData != NULL)
  {
    asn1_free_value(asn1_type_ITSIviStructure, pIviData);
  }
  if (pIviData2 != NULL)
  {
    asn1_free_value(asn1_type_ITSIviStructure, pIviData2);
  }
  if (pRtcmData != NULL)
  {
    asn1_free_value(asn1_type_ITSRTCMcorrections, pRtcmData);
  }
  if (pCpmData != NULL)
  {
    asn1_free_value(asn1_type_ITSCollectivePerceptionMessage, pCpmData);
  }
  if (pVamData != NULL)
  {
    asn1_free_value(asn1_type_ITSVruAwareness, pVamData);
  }

  // Deregister the Ext Callback
  Ext_CallbackDeregister(ExtHandle);

Error:
  // exit thread
  (void) pthread_exit(NULL);

}

/**
 * @brief Send DENM trigger
 * @param pITS pointer to user parameters
 * @return 0 for success
 *
 */
static int DENMTx_FillDENMRoadWorks(tITSTxRWWParams *pParams,
                                    tDENMMgmt *pMgmt,
                                    ITSDecentralizedEnvironmentalNotificationMessage *pDENM,
                                    const struct LPHData *pLPHData)
{
  d_fnstart(D_INFO, NULL, "(%p,%p)\n", pParams, pMgmt);

  int Ret = -1;

  pMgmt->detectionTime = DENM_TIMESTAMP_TAI_NOW;
  pMgmt->validityDuration = pParams->Duration; // Sec
  pMgmt->repetitionDuration = pParams->Duration; // Sec
  pMgmt->repetitionInterval = pParams->RepInterval; //mSec

  pDENM->location_option = DENM_LOC_OPTION_NONE;

  // Check if we should use the GPS or configured (hard coded) position for the event location
  if (pParams->EventPositionSource == ITS_CONFIG_VALUE_EVENTPOSITION_GPS)
  {
    // DENM API will populate event position with latest position information
    pDENM->location_option |= DENM_LOC_OPTION_EVENT;
  }
  else if (pParams->EventPositionSource == ITS_CONFIG_VALUE_EVENTPOSITION_CONFIG)
  {
    // Explicitly set DENM event position
    pDENM->management.eventPosition.latitude                    = pParams->EventLatitude;
    pDENM->management.eventPosition.longitude                   = pParams->EventLongitude;
    pDENM->management.eventPosition.altitude.altitudeValue      = pParams->EventAltitude;
    pDENM->management.eventPosition.altitude.altitudeConfidence = ITSAltitudeConfidence_unavailable;

    pDENM->management.eventPosition.positionConfidenceEllipse.semiMajorConfidence = ITSSemiAxisLength_unavailable;
    pDENM->management.eventPosition.positionConfidenceEllipse.semiMinorConfidence = ITSSemiAxisLength_unavailable;
    pDENM->management.eventPosition.positionConfidenceEllipse.semiMajorOrientation = ITSHeadingValue_unavailable;
  }
  else
  {
    d_printf(D_WARN, NULL, "pDENM->management.eventPosition undefined(%d)!\n",
             pParams->EventPositionSource);
  }

  // Only certain reasons to have location container
  // Otherwise you end up with a location container with no content
  if ((pParams->NumTraces > 0) ||
      (pParams->EventHeadingOption > 0) ||
      (pParams->SubCauseCode == ITSRoadworksSubCauseCode_slowMovingRoadMaintenance))
  {
    pDENM->location_option |= DENM_LOC_OPTION_PROVIDED;
  }

  if (pParams->RelevanceDistance <= ITSRelevanceDistance_Limit_Max)
  {
    pDENM->management.relevanceDistance_option = true;
    pDENM->management.relevanceDistance = pParams->RelevanceDistance;
  }
  if (pParams->RelevanceTrafficDirection < ITSRelevanceTrafficDirection_Limit_Max)
  {
    pDENM->management.relevanceTrafficDirection_option = true;
    pDENM->management.relevanceTrafficDirection = pParams->RelevanceTrafficDirection;
  }

  pMgmt->DestArea.Option = DENM_DEST_OPTION_IMPLIED;
  pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
  pMgmt->TrafficClass = pParams->TrafficClass;
  pMgmt->HopLimit = ETSIFAC_GN_HOP_LIMIT_DEFAULT;
  pMgmt->TransmissionInterval = TRANSMISSIONINTERVALDISABLED;

  pDENM->situation_option = true;
  if (pParams->InformationQuality <= ITSInformationQuality_Limit_Max)
  {
    pDENM->situation.informationQuality = pParams->InformationQuality;
  }
  else
  {
    pDENM->situation.informationQuality = ITSInformationQuality_lowest;
  }
  pDENM->situation.eventType.causeCode = pParams->CauseCode;
  pDENM->situation.eventType.subCauseCode = pParams->SubCauseCode;
  pDENM->situation.linkedCause_option = false;
  pDENM->situation.eventHistory_option = false;

  if (pParams->NumEventPoints > 0)
  {
    pDENM->situation.eventHistory_option = true;

    // eventHistory is simple structure, so can 'free'
    if (pDENM->situation.eventHistory.tab)
      free(pDENM->situation.eventHistory.tab);

    pDENM->situation.eventHistory.tab = (ITSEventPoint *)asn1_mallocz(sizeof(ITSEventPoint) *
                                                                 pParams->NumEventPoints);
    if (pDENM->situation.eventHistory.tab == NULL)
    {
      d_printf(D_ERR, NULL, "Error allocating memory for eventHistory defining RWW segment\n");
      goto End;
    }

    pDENM->situation.eventHistory.count = pParams->NumEventPoints;

    ITSEventPoint *pEventPoints = pDENM->situation.eventHistory.tab;
    size_t Idx = 0;
    for (Idx = 0; Idx < pDENM->situation.eventHistory.count; Idx++)
    {

      pEventPoints[Idx].eventPosition.deltaLatitude  =
        pParams->pEventPoints[Idx].DeltaLatitude;
      pEventPoints[Idx].eventPosition.deltaLongitude =
        pParams->pEventPoints[Idx].DeltaLongitude;
      pEventPoints[Idx].eventPosition.deltaAltitude  =
        pParams->pEventPoints[Idx].DeltaAltitude;
      pEventPoints[Idx].informationQuality = pParams->pEventPoints[Idx].InformationQuality;

      // Convert Event Position points to deltas w.r.t. to previous point
      if (Idx > 0)
      {
        if ((pParams->RelativeOffsetCumulative) || (pParams->EventOffsetAbsolute))
        {
          pEventPoints[Idx].eventPosition.deltaLatitude -= pParams->pEventPoints[Idx-1].DeltaLatitude;
          pEventPoints[Idx].eventPosition.deltaLongitude -= pParams->pEventPoints[Idx-1].DeltaLongitude;
          if (((pParams->EventOffsetAbsolute == 0) && (pParams->pEventPoints[Idx-1].DeltaAltitude != ITSDeltaAltitude_unavailable)) ||
              ((pParams->EventOffsetAbsolute == 1) && (pParams->pEventPoints[Idx-1].DeltaAltitude != ITSAltitudeValue_unavailable)))
            pEventPoints[Idx].eventPosition.deltaAltitude -= pParams->pEventPoints[Idx-1].DeltaAltitude;
          else
            pEventPoints[Idx].eventPosition.deltaAltitude = ITSDeltaAltitude_unavailable;
        }
      }
      // Handle absolute/relative positions
      else if (pParams->EventOffsetAbsolute)
      {
        pEventPoints[Idx].eventPosition.deltaLatitude -= pDENM->management.eventPosition.latitude;
        pEventPoints[Idx].eventPosition.deltaLongitude -= pDENM->management.eventPosition.longitude;
        if ((pDENM->management.eventPosition.altitude.altitudeValue != ITSAltitudeValue_unavailable) &&
            (pEventPoints[Idx].eventPosition.deltaAltitude != ITSAltitudeValue_unavailable))
          pEventPoints[Idx].eventPosition.deltaAltitude -= pDENM->management.eventPosition.altitude.altitudeValue;
        else
          pEventPoints[Idx].eventPosition.deltaAltitude = ITSDeltaAltitude_unavailable;
      }

      d_printf(D_DEBUG, NULL, "EventHistory [%zd]: (%d, %d, %d)\n", Idx,
               pEventPoints[Idx].eventPosition.deltaLatitude,
               pEventPoints[Idx].eventPosition.deltaLongitude,
               pEventPoints[Idx].eventPosition.deltaAltitude);

      if (abs(pEventPoints[Idx].eventPosition.deltaLatitude) >= ITSDeltaLatitude_unavailable)
      {
        d_error(D_ERR, NULL, "EventPoint index %zd deltaLatitude (%d >= %d)\n",
            Idx,
            abs(pEventPoints[Idx].eventPosition.deltaLatitude),
            ITSDeltaLatitude_unavailable);
        Ret = -E2BIG;
        goto End;
      }

      if (abs(pEventPoints[Idx].eventPosition.deltaLongitude) >= ITSDeltaLongitude_unavailable)
      {
        d_error(D_ERR, NULL, "EventPoint index %zd deltaLongitude (%d >= %d)\n",
            Idx,
            abs(pEventPoints[Idx].eventPosition.deltaLongitude),
            ITSDeltaLongitude_unavailable);
        Ret = -E2BIG;
        goto End;
      }
    }
  }

  if (pDENM->location_option)
  {
    pDENM->location.eventSpeed_option = false;

    // EventSpeed and eventHeading are typically used for mobile RWW
    if (pParams->SubCauseCode == ITSRoadworksSubCauseCode_slowMovingRoadMaintenance)
    {
      pDENM->location.eventSpeed_option = true;
      //LPH Speed units are 0.02m/s - so need to convert to 1cm/s
      pDENM->location.eventSpeed.speedValue = pLPHData->Pos.Speed*2;
      pDENM->location.eventSpeed.speedConfidence = ITSSpeedConfidence_equalOrWithinOneCentimeterPerSec;
    }

    pDENM->location.eventPositionHeading_option = false;

    if (pParams->EventHeadingOption > 0)
    {
      pDENM->location.eventPositionHeading_option = true;

      // If specified in the configuration file use it
      if (pParams->EventHeadingOption == 2)
      {
        pDENM->location.eventPositionHeading.headingValue = pParams->EventHeading;
        pDENM->location.eventPositionHeading.headingConfidence = ITSHeadingConfidence_equalOrWithinZeroPointOneDegree;
      }
      else
      {
        // otherwise use gps data
        if (pLPHData->Pos.Heading < UNAVAIL_DE_HEAD)
        {
          pDENM->location.eventPositionHeading.headingValue = pLPHData->Pos.Heading * 3600 /28800;
          pDENM->location.eventPositionHeading.headingConfidence = ITSHeadingConfidence_equalOrWithinZeroPointOneDegree;
        }
        else
        {
          pDENM->location.eventPositionHeading.headingValue = ITSHeadingValue_unavailable;
          pDENM->location.eventPositionHeading.headingConfidence = ITSHeadingConfidence_unavailable;
        }
      }
    }

    // Free the traces as they're about to be updated
    if (pDENM->location.traces.tab != NULL)
    {
      asn1_free_value_struct(asn1_type_ITSTraces, &pDENM->location.traces);
    }

    pDENM->location.traces.count = 1;
    pDENM->location.traces.tab =
      (ITSPathHistory *)asn1_mallocz(sizeof(ITSPathHistory) * pDENM->location.traces.count);

    if (pDENM->location.traces.tab == NULL)
    {
      d_printf(D_ERR, NULL, "Error allocating memory for Path History Trace to RWW\n");
      Ret = DENM_FAILURE_INVALID_PARAMS;
      goto End;
    }

    // If this is an update then check if we need to add more traces
    // This is only applicable if the RWW is mobile.
    if (pParams->SubCauseCode == ITSRoadworksSubCauseCode_slowMovingRoadMaintenance)
    {
      int DistanceFromLastTraceUpdate = 0;
      if (LastRoadWorkerTime != 0)
      {
        tVector CurrentEventPos;
        (void)Vector_Clear(&CurrentEventPos);
        CurrentEventPos.Lat_Degs = (float)pDENM->management.eventPosition.latitude  / LATLON_UNITS_PER_DEGREE;
        CurrentEventPos.Lon_Degs = (float)pDENM->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
        d_printf(D_DEBUG, NULL, "CurPos.Lat = %f\n", CurrentEventPos.Lat_Degs);
        d_printf(D_DEBUG, NULL, "CurPos.Lon = %f\n", CurrentEventPos.Lon_Degs);

        d_printf(D_DEBUG, NULL, "LastTraceUpdatePos.Lat = %f\n", LastTraceRoadWorkerPos.Lat_Degs);
        d_printf(D_DEBUG, NULL, "LastTraceUpdatePos.Lon = %f\n", LastTraceRoadWorkerPos.Lon_Degs);

        tVectorSeparation Sep;
        // Calculate the separation between the lest eventPosition the trace was
        // updated and the current position
        (void)Vector_Separation(&LastTraceRoadWorkerPos, &CurrentEventPos, &Sep);
        DistanceFromLastTraceUpdate = rintf(fabsf(Sep.r10)/1000);
      }

      d_printf(D_DEBUG, NULL, "Distance from last trace update = %d\n",
               DistanceFromLastTraceUpdate);
      if ((pParams->TraceUpdateDistance_m != -1)
          &&
          (DistanceFromLastTraceUpdate > pParams->TraceUpdateDistance_m))
      {
        // the mobile RWW has moved far enough that we should update the traces
        // maximum number of trace points is 40
        // ETSI TS 102 894-2 V1.2.1 (2014-09) - A.117 DF_PathHistory
        tDENMReferencePoint *pNewTraces = NULL;
        if (pParams->NumTraces < 40)
        {
          pParams->NumTraces++;
          pNewTraces = realloc(pParams->pTraces,
                               sizeof(tDENMReferencePoint)*pParams->NumTraces);

          if (pNewTraces == NULL)
          {
            d_error(D_ERR, NULL, "Allocating more memory to store new trace\n");
            pParams->NumTraces--;
            goto End;
          }
        }
        else
        {
          pNewTraces = pParams->pTraces;

          if (pNewTraces == NULL)
          {
            d_error(D_ERR, NULL, "pTraces is NULL\n");
            goto End;
          }
        }
        memmove(pNewTraces + 1,
                pNewTraces,
                sizeof(tDENMReferencePoint)*(pParams->NumTraces - 1));

        pNewTraces[0].DeltaLatitude  = 0;//pDENM->management.eventPosition.latitude;
        pNewTraces[0].DeltaLongitude = 0;//pDENM->management.eventPosition.longitude;
        pNewTraces[0].DeltaAltitude  = 0;//pDENM->management.eventPosition.altitude.altitudeValue;

        LastTraceRoadWorkerPos.Lat_Degs = (float)pDENM->management.eventPosition.latitude  / LATLON_UNITS_PER_DEGREE;
        LastTraceRoadWorkerPos.Lon_Degs = (float)pDENM->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
        pParams->pTraces = pNewTraces;
      }
    }

    ITSPathHistory *pPathHistory = &(pDENM->location.traces.tab[0]);
    pPathHistory->count = pParams->NumTraces;

    if (pPathHistory->tab != NULL)
    {
      free(pPathHistory->tab);
    }

    pPathHistory->tab = (ITSPathPoint *)asn1_mallocz(sizeof(ITSPathPoint) * pPathHistory->count);

    if (pPathHistory->tab == NULL)
    {
      d_error(D_ERR, NULL, "Error allocating memory for Path History to RWW\n");
      goto End;
    }

    size_t Idx = 0;
    for (Idx = 0; Idx < pPathHistory->count; Idx++)
    {
      pPathHistory->tab[Idx].pathPosition.deltaLatitude  =
        pParams->pTraces[Idx].DeltaLatitude;
      pPathHistory->tab[Idx].pathPosition.deltaLongitude =
        pParams->pTraces[Idx].DeltaLongitude;

      pPathHistory->tab[Idx].pathPosition.deltaAltitude  =
        pParams->pTraces[Idx].DeltaAltitude;

      // Convert PH points to deltas w.r.t. to previous point
      if (Idx > 0)
      {
        if ((pParams->RelativeOffsetCumulative) || (pParams->EventOffsetAbsolute))
        {
          pPathHistory->tab[Idx].pathPosition.deltaLatitude -= pParams->pTraces[Idx-1].DeltaLatitude;
          pPathHistory->tab[Idx].pathPosition.deltaLongitude -= pParams->pTraces[Idx-1].DeltaLongitude;
          if (((pParams->EventOffsetAbsolute == 0) && (pParams->pTraces[Idx-1].DeltaAltitude != ITSDeltaAltitude_unavailable)) ||
              ((pParams->EventOffsetAbsolute == 1) && (pParams->pTraces[Idx-1].DeltaAltitude != ITSAltitudeValue_unavailable)))
            pPathHistory->tab[Idx].pathPosition.deltaAltitude -= pParams->pTraces[Idx-1].DeltaAltitude;
          else
            pPathHistory->tab[Idx].pathPosition.deltaAltitude = ITSDeltaAltitude_unavailable;
        }
      }
      // Handle absolute/relative positions
      else if (pParams->EventOffsetAbsolute)
      {
        pPathHistory->tab[Idx].pathPosition.deltaLatitude -= pDENM->management.eventPosition.latitude;
        pPathHistory->tab[Idx].pathPosition.deltaLongitude -= pDENM->management.eventPosition.longitude;
        if ((pDENM->management.eventPosition.altitude.altitudeValue != ITSAltitudeValue_unavailable) &&
            (pPathHistory->tab[Idx].pathPosition.deltaAltitude != ITSAltitudeValue_unavailable))
          pPathHistory->tab[Idx].pathPosition.deltaAltitude -= pDENM->management.eventPosition.altitude.altitudeValue;
        else
          pPathHistory->tab[Idx].pathPosition.deltaAltitude = ITSDeltaAltitude_unavailable;
      }

      d_printf(D_DEBUG, NULL, "Trace [%zd]: (%d, %d, %d)\n", Idx,
               pPathHistory->tab[Idx].pathPosition.deltaLatitude,
               pPathHistory->tab[Idx].pathPosition.deltaLongitude,
               pPathHistory->tab[Idx].pathPosition.deltaAltitude);

      if (abs(pPathHistory->tab[Idx].pathPosition.deltaLatitude) >= ITSDeltaLatitude_unavailable)
      {
        d_error(D_ERR, NULL, "PathHistory index %zd deltaLatitude (%d >= %d)\n",
            Idx,
            abs(pPathHistory->tab[Idx].pathPosition.deltaLatitude),
            ITSDeltaLatitude_unavailable);
        Ret = -E2BIG;
        goto End;
      }

      if (abs(pPathHistory->tab[Idx].pathPosition.deltaLongitude) >= ITSDeltaLongitude_unavailable)
      {
        d_error(D_ERR, NULL, "PathHistory index %zd deltaLongitude (%d >= %d)\n",
            Idx,
            abs(pPathHistory->tab[Idx].pathPosition.deltaLongitude),
            ITSDeltaLongitude_unavailable);
        Ret = -E2BIG;
        goto End;
      }
    }

    pDENM->location.roadType_option = false;
  }

  // Only ITSCauseCodeType_roadworks using alacarte_option (at the moment?)
  // Unless LanePosition is explicitly required
  if ((pParams->CauseCode == ITSCauseCodeType_roadworks) ||
      (pParams->LanePositionOption))
  {
    pDENM->alacarte_option = true;
    if (pParams->LanePositionOption)
    {
      if ((pParams->LanePosition >= ITSLanePosition_ID_offTheRoad) &&
          (pParams->LanePosition <= ITSLanePosition_ID_outerHardShoulder))
      {
        pDENM->alacarte.lanePosition_option = true;
        pDENM->alacarte.lanePosition = pParams->LanePosition;
      }
    }
    pDENM->alacarte.impactReduction_option = false;
    pDENM->alacarte.externalTemperature_option = false;

    if (pParams->CauseCode == ITSCauseCodeType_roadworks)
    {
      pDENM->alacarte.roadWorks_option = true;
      pDENM->alacarte.roadWorks.lightBarSirenInUse_option = false;

      pDENM->alacarte.roadWorks.closedLanes_option = pParams->ClosedLanesOption;
      if (pParams->ClosedLanesOption)
      {
        if (pParams->OuterHardShoulderStatus <= ITSHardShoulderStatus_Limit_Max)
        {
          pDENM->alacarte.roadWorks.closedLanes.outerhardShoulderStatus_option = true;
          pDENM->alacarte.roadWorks.closedLanes.outerhardShoulderStatus = pParams->OuterHardShoulderStatus;
        }
        if (pParams->InnerHardShoulderStatus <= ITSHardShoulderStatus_Limit_Max)
        {
          pDENM->alacarte.roadWorks.closedLanes.innerhardShoulderStatus_option = true;
          pDENM->alacarte.roadWorks.closedLanes.innerhardShoulderStatus = pParams->InnerHardShoulderStatus;
        }
        if (pParams->NumClosedLanes > 0)
        {
          pDENM->alacarte.roadWorks.closedLanes.drivingLaneStatus_option = true;
          ETSASN_SetBitStringList(&pDENM->alacarte.roadWorks.closedLanes.drivingLaneStatus, pParams->NumClosedLanes, pParams->ClosedLanes);
        }
      }

      pDENM->alacarte.roadWorks.trafficFlowRule_option = pParams->TrafficFlowRuleOption;
      if (pParams->TrafficFlowRuleOption)
      {
        pDENM->alacarte.roadWorks.trafficFlowRule = pParams->TrafficFlowRule;
      }

      pDENM->alacarte.roadWorks.restriction_option = false;
      pDENM->alacarte.roadWorks.speedLimit_option = pParams->SpeedLimitOption;

      if (pParams->SpeedLimitOption)
        // SpeedLimit from the configuration file is in km/h.
        pDENM->alacarte.roadWorks.speedLimit = pParams->SpeedLimit;

      pDENM->alacarte.roadWorks.startingPointSpeedLimit_option =
        pParams->StartingPointSpeedLimitOption;
      if (pParams->StartingPointSpeedLimitOption)
      {
        pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLatitude  =
          pParams->StartingPointSpeedLimit.DeltaLatitude;
        pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLongitude =
          pParams->StartingPointSpeedLimit.DeltaLongitude;
        pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaAltitude  =
          pParams->StartingPointSpeedLimit.DeltaAltitude;

        // Handle absolute/relative positions
        if (pParams->EventOffsetAbsolute)
        {
          pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLatitude -= pDENM->management.eventPosition.latitude;
          pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLongitude -= pDENM->management.eventPosition.longitude;
          if ((pDENM->management.eventPosition.altitude.altitudeValue != ITSAltitudeValue_unavailable) &&
              (pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaAltitude != ITSAltitudeValue_unavailable))
            pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaAltitude -= pDENM->management.eventPosition.altitude.altitudeValue;
          else
            pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaAltitude = ITSDeltaAltitude_unavailable;
        }

        d_printf(D_DEBUG, NULL, "StartingPointSpeedLimit: (%d, %d, %d)\n",
                 pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLatitude,
                 pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLongitude,
                 pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaAltitude);

        if (abs(pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLatitude) >= ITSDeltaLatitude_unavailable)
        {
          d_error(D_ERR, NULL, "startingPointSpeedLimit deltaLatitude (%d >= %d)\n",
              abs(pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLatitude),
              ITSDeltaLatitude_unavailable);
          Ret = -E2BIG;
          goto End;
        }

        if (abs(pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLongitude) >= ITSDeltaLongitude_unavailable)
        {
          d_error(D_ERR, NULL, "startingPointSpeedLimit deltaLongitude (%d >= %d)\n",
              abs(pDENM->alacarte.roadWorks.startingPointSpeedLimit.deltaLongitude),
              ITSDeltaLongitude_unavailable);
          Ret = -E2BIG;
          goto End;
        }
      }

      pDENM->alacarte.roadWorks.incidentIndication_option = false;
      pDENM->alacarte.roadWorks.recommendedPath_option = false;
    }

    pDENM->alacarte.positioningSolution_option = false;
    pDENM->alacarte.stationaryVehicle_option = false;
  }

  Ret = 0;
End:
  d_fnend(D_INFO, NULL, "()=%d)\n", Ret);

  return Ret;
}

/**
 * @brief Send DENM trigger
 * @param pITS pointer to user parameters
 * @return 0 for success
 *
 */
static int DENMTx_SendDENMTrigger_RoadWorks(struct ITSCtrl *pITS)
{
  d_assert(pITS);
  d_fnstart(D_INFO, NULL, "(%p)\n", pITS);

  int Ret = -1;

  d_printf(D_INFO, NULL, "Send DENM trigger (Roadworks)\n");
  tDENMStatusCode status = DENM_FAILURE_INVALID_ACTION_ID;

  const struct LPHData * pData = 0;
  int rc = LPH_Data(pITS->Tx.pLPH_Handle, &pData);
  if (rc != 0)
  {
    d_error(D_ERR, NULL, "Could not access LPH GPS information to populate RWW DENM\n");
    goto End;
  }

  if (pData->Pos.Mode < LPH_POS_FIX_MODE_2D)
  {
    d_printf(D_WARN, NULL, "No Position: %d\n", pData->Pos.Mode);
    goto End;
  }

  int NumRWW = 0;

  // Optional initial DENM
  if (pITS->Tx.RWW.Enabled)
  {
    NumRWW++;

    RWWActionId = ETSIDENM_ACTIONID(pITS->Tx.RWW.OrigStationId, pITS->Tx.RWW.SeqNumber);

    Ret = DENMTx_FillDENMRoadWorks(&pITS->Tx.RWW, &RWWMgmt, pRWWMsg, pData);

    if (Ret)
    {
      d_printf(D_WARN, NULL, "Could not FillDENMRoadWorks RWW (%d)\n", Ret);
      goto End;
    }
  }

  // Optional second DENM
  if (pITS->Tx.RWW2.Enabled)
  {
    NumRWW++;

    RWWActionId2 = ETSIDENM_ACTIONID(pITS->Tx.RWW2.OrigStationId, pITS->Tx.RWW2.SeqNumber);

    Ret = DENMTx_FillDENMRoadWorks(&pITS->Tx.RWW2, &RWWMgmt2, pRWWMsg2, pData);

    if (Ret)
    {
      d_printf(D_WARN, NULL, "Could not FillDENMRoadWorks RWW2 (%d)\n", Ret);
      goto End;
    }
  }

  // Optional third DENM
  if (pITS->Tx.RWW3.Enabled)
  {
    NumRWW++;

    RWWActionId3 = ETSIDENM_ACTIONID(pITS->Tx.RWW3.OrigStationId, pITS->Tx.RWW3.SeqNumber);

    Ret = DENMTx_FillDENMRoadWorks(&pITS->Tx.RWW3, &RWWMgmt3, pRWWMsg3, pData);

    if (Ret)
    {
      d_printf(D_WARN, NULL, "Could not FillDENMRoadWorks RWW3 (%d)\n", Ret);
      goto End;
    }
  }

  // Optional fourth DENM
  if (pITS->Tx.RWW4.Enabled)
  {
    NumRWW++;

    RWWActionId4 = ETSIDENM_ACTIONID(pITS->Tx.RWW4.OrigStationId, pITS->Tx.RWW4.SeqNumber);

    Ret = DENMTx_FillDENMRoadWorks(&pITS->Tx.RWW4, &RWWMgmt4, pRWWMsg4, pData);

    if (Ret)
    {
      d_printf(D_WARN, NULL, "Could not FillDENMRoadWorks RWW4 (%d)\n", Ret);
      goto End;
    }
  }

  // Determine if we need to Trigger() or Update() based on time
  // If this is the first time generating the DENM - need to trigger.
  if (LastRoadWorkerTime == 0)
  {
    d_printf (D_DEBUG, NULL, "Triggering RWW DENM!\n");

    // If we have multiple RWW DENMs, set referenceDENM in each
    if ((pITS->Tx.UseRefDENMEnabled) && (NumRWW > 1))
    {
      if (pITS->Tx.RWW.Enabled)
      {
        pRWWMsg->alacarte.roadWorks.referenceDenms_option = true;
        pRWWMsg->alacarte.roadWorks.referenceDenms.count = NumRWW-1;
        pRWWMsg->alacarte.roadWorks.referenceDenms.tab = (ITSActionID *)
          asn1_mallocz(pRWWMsg->alacarte.roadWorks.referenceDenms.count * sizeof(ITSActionID));

        int Count = 0;
        if (pITS->Tx.RWW2.Enabled)
        {
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId2);
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId2);
        }
        if (pITS->Tx.RWW3.Enabled)
        {
          Count++;
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId3);
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId3);
        }
        if (pITS->Tx.RWW4.Enabled)
        {
          Count++;
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId4);
          pRWWMsg->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId4);
        }
      }

      if (pITS->Tx.RWW2.Enabled)
      {
        pRWWMsg2->alacarte.roadWorks.referenceDenms_option = true;
        pRWWMsg2->alacarte.roadWorks.referenceDenms.count = NumRWW-1;
        pRWWMsg2->alacarte.roadWorks.referenceDenms.tab = (ITSActionID *)
          asn1_mallocz(pRWWMsg2->alacarte.roadWorks.referenceDenms.count * sizeof(ITSActionID));

        int Count = 0;
        // The first RWW is not optional
        pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId);
        pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId);

        if (pITS->Tx.RWW3.Enabled)
        {
          Count++;
          pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId3);
          pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId3);
        }
        if (pITS->Tx.RWW4.Enabled)
        {
          Count++;
          pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId4);
          pRWWMsg2->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId4);
        }
      }

      if (pITS->Tx.RWW3.Enabled)
      {
        pRWWMsg3->alacarte.roadWorks.referenceDenms_option = true;
        pRWWMsg3->alacarte.roadWorks.referenceDenms.count = NumRWW-1;
        pRWWMsg3->alacarte.roadWorks.referenceDenms.tab = (ITSActionID *)
          asn1_mallocz(pRWWMsg3->alacarte.roadWorks.referenceDenms.count * sizeof(ITSActionID));

        int Count = 0;
        // The first RWW is not optional
        pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId);
        pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId);

        if (pITS->Tx.RWW2.Enabled)
        {
          Count++;
          pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId2);
          pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId2);
        }
        if (pITS->Tx.RWW4.Enabled)
        {
          Count++;
          pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId4);
          pRWWMsg3->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId4);
        }
      }

      if (pITS->Tx.RWW4.Enabled)
      {
        pRWWMsg4->alacarte.roadWorks.referenceDenms_option = true;
        pRWWMsg4->alacarte.roadWorks.referenceDenms.count = NumRWW-1;
        pRWWMsg4->alacarte.roadWorks.referenceDenms.tab = (ITSActionID *)
          asn1_mallocz(pRWWMsg4->alacarte.roadWorks.referenceDenms.count * sizeof(ITSActionID));

        int Count = 0;
        // The first RWW is not optional
        pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId);
        pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId);

        if (pITS->Tx.RWW2.Enabled)
        {
          Count++;
          pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId2);
          pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId2);
        }
        if (pITS->Tx.RWW3.Enabled)
        {
          Count++;
          pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].originatingStationID = ETSIDENM_ACTIONID_STATION(RWWActionId3);
          pRWWMsg4->alacarte.roadWorks.referenceDenms.tab[Count].sequenceNumber = ETSIDENM_ACTIONID_SEQNUM(RWWActionId3);
        }
      }
    }

    // Send Denm RWW trigger
    if (pITS->Tx.RWW.Enabled)
    {
      status = DENM_SendDENMTriggerWithId(&RWWMgmt, pRWWMsg, RWWActionId);
    }
    // Send optional second Denm RWW trigger
    if (pITS->Tx.RWW2.Enabled)
    {
      status = DENM_SendDENMTriggerWithId(&RWWMgmt2, pRWWMsg2, RWWActionId2);
    }
    // Send optional third Denm RWW trigger
    if (pITS->Tx.RWW3.Enabled)
    {
      status = DENM_SendDENMTriggerWithId(&RWWMgmt3, pRWWMsg3, RWWActionId3);
    }
    // Send optional fourth Denm RWW trigger
    if (pITS->Tx.RWW4.Enabled)
    {
      status = DENM_SendDENMTriggerWithId(&RWWMgmt4, pRWWMsg4, RWWActionId4);
    }

    if (status == DENM_SUCCESS)
    {
      // update last RWW time
      LastRoadWorkerTime = Util_Now();

      d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId);
      Ret = 0;

      // clear the vector and store the position of the RoadWorks
      (void)Vector_Clear(&LastRoadWorkerPos);
      LastRoadWorkerPos.Lat_Degs = (float)pRWWMsg->management.eventPosition.latitude  / LATLON_UNITS_PER_DEGREE;
      LastRoadWorkerPos.Lon_Degs = (float)pRWWMsg->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
      LastTraceRoadWorkerPos.Lat_Degs = (float)pRWWMsg->management.eventPosition.latitude  / LATLON_UNITS_PER_DEGREE;
      LastTraceRoadWorkerPos.Lon_Degs = (float)pRWWMsg->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
      d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lat = %f\n", LastRoadWorkerPos.Lat_Degs);
      d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lon = %f\n", LastRoadWorkerPos.Lon_Degs);
    }
    else
    {
      d_printf(D_WARN, NULL, "Triggering RWW DENM failed: %d\n", status);
      Ret = -EAGAIN;
    }
  }
  else
  {
    d_printf (D_DEBUG, NULL, "Check if the RWW DENM needs updating\n");
    // has the road works moved more than 4 metres OR has it expired.
    // If so we the DENM needs updating...
    tVector CurrentPos;
    (void)Vector_Clear(&CurrentPos);
    CurrentPos.Lat_Degs = (float)pRWWMsg->management.eventPosition.latitude  / LATLON_UNITS_PER_DEGREE;
    CurrentPos.Lon_Degs = (float)pRWWMsg->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
    d_printf(D_DEBUG, NULL, "CurPos.Lat = %f\n", CurrentPos.Lat_Degs);
    d_printf(D_DEBUG, NULL, "CurPos.Lon = %f\n", CurrentPos.Lon_Degs);

    d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lat = %f\n", LastRoadWorkerPos.Lat_Degs);
    d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lon = %f\n", LastRoadWorkerPos.Lon_Degs);

    tVectorSeparation Sep;
    // Calculate separation between last update vector and the current vector
    (void)Vector_Separation(&LastRoadWorkerPos, &CurrentPos, &Sep);

    // The absolute distance between the last position and the current position
    // r10 is in units of mm - convert to metres
    int DistanceFromLastUpdate = rintf(fabsf(Sep.r10)/1000);

    uint64_t Now = Util_Now();

    d_printf (D_DEBUG, NULL,
              "Now (%" PRId64 "), "
              "LastRoadWorkTime (%" PRId64 "), "
              "DistanceFromLastUpdate (%d), "
              "Duration (%d)\n",
              Now,
              LastRoadWorkerTime,
              DistanceFromLastUpdate,
              pITS->Tx.RWW.Duration);

    if ( ((uint64_t)(Now - LastRoadWorkerTime) >=
          pITS->Tx.RWW.UpdatePeriod) ||
         (DistanceFromLastUpdate >= 4) )
    {
      // Send Denm update (with current ActionId)
      if (pITS->Tx.RWW.Enabled)
      {
        status = DENM_SendDENMUpdate(&RWWMgmt, pRWWMsg, RWWActionId);
      }
      // Send Optional second Denm RWW update
      if (pITS->Tx.RWW2.Enabled)
      {
        status = DENM_SendDENMUpdate(&RWWMgmt2, pRWWMsg2, RWWActionId2);
      }
      // Send Option third Denm RWW trigger
      if (pITS->Tx.RWW3.Enabled)
      {
        status = DENM_SendDENMUpdate(&RWWMgmt3, pRWWMsg3, RWWActionId3);
      }
      // Send Option fourth Denm RWW trigger
      if (pITS->Tx.RWW4.Enabled)
      {
        status = DENM_SendDENMUpdate(&RWWMgmt4, pRWWMsg4, RWWActionId4);
      }

      // update last RWW position
      LastRoadWorkerPos.Lat_Degs = (float)pRWWMsg->management.eventPosition.latitude / LATLON_UNITS_PER_DEGREE;
      LastRoadWorkerPos.Lon_Degs = (float)pRWWMsg->management.eventPosition.longitude / LATLON_UNITS_PER_DEGREE;
      d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lat = %f\n", LastRoadWorkerPos.Lat_Degs);
      d_printf(D_DEBUG, NULL, "LastRoadWorkerPos.Lon = %f\n", LastRoadWorkerPos.Lon_Degs);

      if (status == DENM_SUCCESS)
      {
        // update last RWW time
        LastRoadWorkerTime = Util_Now();

        d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId);
        Ret = 0;
      }
      else
      {
        d_printf(D_WARN, NULL, "Updating RWW DENM Failed %d\n", status);
      }
    }
    else
    {
      d_printf (D_INFO, NULL, "Not updating RWW DENM\n");
      Ret = 0;
      goto End;
    }
  }

End:
  if (status == DENM_SUCCESS)
  {
    d_fnend(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId);
    Ret = 0;
  }
  else
  {
    d_fnend(D_INFO, NULL, "DENM: Status %d\n", status);
  }

  return Ret;
}


/**
 * @brief Fill the DENM termination data
 *
 * @return 0 for success
 */
void DENMTx_FillDENMTerminateRoadWorks(tITSTxRWWParams *pParams,
                                       tDENMMgmt *pMgmt,
                                       ITSDecentralizedEnvironmentalNotificationMessage *pDenm)
{
  d_fnstart(D_INFO, NULL, "(%p,%p,%p)\n", pParams, pMgmt, pDenm);

  // Same detectionTime
  pMgmt->validityDuration = 1; //Sec
  pMgmt->repetitionDuration = 1; // Sec
  pMgmt->repetitionInterval = 0; // mSec
  // Same eventPosition
  // Same DestArea
  pMgmt->TrafficClass = pParams->TrafficClass;
  pMgmt->HopLimit = ETSIFAC_GN_HOP_LIMIT_DEFAULT;
  pMgmt->TransmissionInterval = TRANSMISSIONINTERVALDISABLED;

  // Mandatory parts of DENM required for termination
  // ITSManagementContainer eventPosition still set, no need to modify here

  // Optional parts of DENM not required for termination
  // ITSLocationContainer
  pDenm->location_option = DENM_LOC_OPTION_NONE;
  // ITSSituationContainer
  pDenm->situation_option = false;
  // ITSAlacarteContainer
  pDenm->alacarte_option = false;

  // eventHistory is simple structure, so can 'free'
  if (pDenm->situation.eventHistory.tab)
  {
    free(pDenm->situation.eventHistory.tab);
  }
  pDenm->situation.eventHistory_option = false;

  // Since we're terminating, tidy up allocated traces structure
  asn1_free_value_struct(asn1_type_ITSTraces, &pDenm->location.traces);
  pDenm->location.traces.tab = NULL;
  pDenm->location.traces.count = 0;

  // Since we're terminating, tidy up allocated drivingLaneStatus structure
  free(pDenm->alacarte.roadWorks.closedLanes.drivingLaneStatus.buf);
  pDenm->alacarte.roadWorks.closedLanes_option = false;

  d_fnend(D_INFO, NULL, "(%p,%p,%p)\n", pParams, pMgmt, pDenm);
}

/**
 * @brief Send DENM terminate
 * @param pITS pointer to user parameters
 * @return 0 for success
 *
 */
int DENMTx_SendDENMTerminate_RoadWorks(struct ITSCtrl *pITS)
{

  d_printf(D_INFO, NULL, "Send DENM terminate\n");

  if (pITS->Tx.RWW.Enabled)
  {
    DENMTx_FillDENMTerminateRoadWorks(&(pITS->Tx.RWW), &RWWMgmt, pRWWMsg);

    // Send Denm
    tDENMStatusCode status = DENM_SendDENMTermination(&RWWMgmt, pRWWMsg, RWWActionId);

    if (status == DENM_SUCCESS)
    {
      d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId);
    }
    else
    {
      d_printf(D_INFO, NULL, "DENM: Failed %d\n", status);
    }
  }

  if (pITS->Tx.RWW2.Enabled)
  {
    DENMTx_FillDENMTerminateRoadWorks(&(pITS->Tx.RWW2), &RWWMgmt2, pRWWMsg2);

    // Send Denm
    tDENMStatusCode status = DENM_SendDENMTermination(&RWWMgmt2, pRWWMsg2, RWWActionId2);

    if (status == DENM_SUCCESS)
    {
      d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId2);
    }
    else
    {
      d_printf(D_INFO, NULL, "DENM: Failed %d\n", status);
    }
  }

  if (pITS->Tx.RWW3.Enabled)
  {
    DENMTx_FillDENMTerminateRoadWorks(&(pITS->Tx.RWW3), &RWWMgmt3, pRWWMsg3);

    // Send Denm
    tDENMStatusCode status = DENM_SendDENMTermination(&RWWMgmt3, pRWWMsg3, RWWActionId3);

    if (status == DENM_SUCCESS)
    {
      d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId3);
    }
    else
    {
      d_printf(D_INFO, NULL, "DENM: Failed %d\n", status);
    }
  }

  if (pITS->Tx.RWW4.Enabled)
  {
    DENMTx_FillDENMTerminateRoadWorks(&(pITS->Tx.RWW4), &RWWMgmt4, pRWWMsg4);

    // Send Denm
    tDENMStatusCode status = DENM_SendDENMTermination(&RWWMgmt4, pRWWMsg4, RWWActionId4);

    if (status == DENM_SUCCESS)
    {
      d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", RWWActionId4);
    }
    else
    {
      d_printf(D_INFO, NULL, "DENM: Failed %d\n", status);
    }
  }

  return 0;
}

/**
 * @brief Send DENM trigger for EEBL
 * @param pITS pointer to user parameters
 * @return 0 for success
 *
 */
static int DENMTx_SendDENMTrigger_EEBL(struct ITSCtrl *pITS)
{
  int Ret = -1;
  d_printf(D_INFO, NULL, "Send DENM (EEBL)\n");

  static uint64_t lastEEBL = 0;

  static tC2CMgmt C2CMgmt;
  static tC2CActionID ActionId;

  const struct LPHData * pData = 0;
  int rc = LPH_Data(pITS->Tx.pLPH_Handle, &pData);
  if ((rc)      ||
      (!pData)  ||
      (pData->Pos.Mode < LPH_POS_FIX_MODE_2D))
  {
    d_printf(D_WARN, NULL, "No Position: %d\n", pData ? pData->Pos.Mode : 0);
    goto Error;
  }

  C2CMgmt.ValidityDuration_s = 2; // Sec
  C2CMgmt.RepetitionDuration_s = 0; // No repetition
  C2CMgmt.RepetitionDurationSubSec_ms = 0; // no repetition
  C2CMgmt.RepetitionInterval_ms = 0; // no repetition

  C2CMgmt.RelevanceDistance = C2CRelevanceDistance_lessThan500m;

  C2CMgmt.RelevanceTrafficDirection = C2CRelevanceTrafficDirection_allTrafficDirections;

  C2CMgmt.InformationQuality = C2CInformationQuality_1;

  C2CMgmt.CauseCode = C2CCauseCodeType_ID_dangerousSituation;
  C2CMgmt.SubCauseCode = C2CDangerousSituationSubCauseCode_ID_emergencyElectronicBrakeEngaged;

  C2CMgmt.EventHistory_populate = false;
  C2CMgmt.EventSpeedHeading_populate = true;
  C2CMgmt.PathHistory_populate = true;

  C2CMgmt.LanePosition_populate = true;
  C2CMgmt.IRCType = C2CIRCRequestResponseIndication_doNotInclude;
  C2CMgmt.StationarySince = C2CStationarySince_doNotInclude;

  C2CMgmt.TrafficClass = C2C_GN_TC_DP0_URGENT_DENM;
  C2CMgmt.HopLimit = 2;

  tC2CStatusCode Status;

  // Determine if we need to Trigger() or Update() based on time
  if (Util_Now() > (lastEEBL + (C2CMgmt.ValidityDuration_s*1000)))
  {
    // Send Denm trigger (get new ActionId)
    Status = C2C_SendDENMTrigger(&C2CMgmt, &ActionId);
  }
  else
  {
    // Send Denm update (with current ActionId)
    Status = C2C_SendDENMUpdate(&C2CMgmt, ActionId);
  }

  if (Status == C2C_SUCCESS)
  {
    d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", ActionId);

    // update last EEBL time
    lastEEBL = Util_Now();

    Ret = 0;
  }
  else
  {
    d_printf(D_WARN, NULL, "DENM: Failed %d\n", Status);
  }

Error:
  return Ret;
}

/**
 * @brief Send DENM trigger for Emergency Vehicle Warning
 * @param pITS pointer to user parameters
 * @return 0 for success
 *
 * The Emergency vehicle warning DENM could use the C2C_SendDENMTrigger API
 * but instead is a demonstration of the DENM_SendDENMTrigger API
 *
 */
static int DENMTx_SendDENMTrigger_EVW(struct ITSCtrl *pITS)
{
  int Ret = -1;
  d_printf(D_INFO, NULL, "Send DENM (EVW)\n");

  static uint64_t lastEVW = 0;

  static tDENMActionID ActionId;
  static tDENMMgmt Mgmt;
  static ITSDecentralizedEnvironmentalNotificationMessage Denm;

  const struct LPHData * pData = 0;
  int rc = LPH_Data(pITS->Tx.pLPH_Handle, &pData);
  if ((rc)      ||
      (!pData)  ||
      (pData->Pos.Mode < LPH_POS_FIX_MODE_2D))
  {
    d_printf(D_WARN, NULL, "No Position: %d\n", pData ? pData->Pos.Mode : 0);
    goto Error;
  }

  Mgmt.detectionTime = DENM_TIMESTAMP_TAI_NOW;
  Mgmt.validityDuration = pITS->Tx.EVW.Duration; // Sec
  Mgmt.repetitionDuration = 0; // No repetition
  Mgmt.repetitionInterval = 0; // No repetition

  // Mgmt.eventPosition set from local position (DENM_LOC_OPTION_EVENT)

  Mgmt.DestArea.Option = DENM_DEST_OPTION_IMPLIED;

  Denm.management.relevanceDistance_option = true;
  Denm.management.relevanceDistance = ITSRelevanceDistance_lessThan1000m;
  // EVW DENM relevant upstream & downstream so don't include a specific direction
  Denm.management.relevanceTrafficDirection_option = false;

  Mgmt.CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
  Mgmt.TrafficClass = ETSIFAC_GN_TC_ITS_DP1;
  Mgmt.HopLimit = ETSIFAC_GN_HOP_LIMIT_DEFAULT;
  Mgmt.TransmissionInterval = TRANSMISSIONINTERVALDISABLED;

  Denm.situation_option = true;
  Denm.situation.informationQuality = ITSInformationQuality_lowest;

  if (pData->Pos.Speed > 4) // Moving (units 0.02m/s, stationary is <= 0.08m/s)
  {
    Denm.situation.eventType.causeCode = ITSCauseCodeType_emergencyVehicleApproaching;
    Denm.situation.eventType.subCauseCode =
      ITSEmergencyVehicleApproachingSubCauseCode_emergencyVehicleApproaching;
    Denm.situation.linkedCause_option = false;
  }
  else // Stopped
  {
    // NOTE: this is a very primitive implementation of Stationary Safeguarding
    // Emergency Vehicle, in reality other parameters are adapted too
    Denm.situation.eventType.causeCode = ITSCauseCodeType_rescueAndRecoveryWorkInProgress;
    Denm.situation.eventType.subCauseCode =
      ITSRescueAndRecoveryWorkInProgressSubCauseCode_emergencyVehicles;
    Denm.situation.linkedCause_option = true;
    Denm.situation.linkedCause.causeCode = ITSCauseCodeType_trafficCondition;

    Denm.alacarte_option = true;
    Denm.alacarte.stationaryVehicle_option = true;
    Denm.alacarte.stationaryVehicle.stationarySince_option = true;
    Denm.alacarte.stationaryVehicle.stationarySince = ITSStationarySince_lessThan1Minute;
  }

  Denm.location_option = DENM_LOC_OPTION_POPULATE | DENM_LOC_OPTION_EVENT;

  tDENMStatusCode Status;

  // Determine if we need to Trigger() or Update() based on time
  if (Util_Now() > (lastEVW + (Mgmt.validityDuration*1000)))
  {
    // Send Denm trigger (get new ActionId)
    Status = DENM_SendDENMTrigger(&Mgmt, &Denm, &ActionId);
  }
  else
  {
    // Send Denm update (with current ActionId)
    Status = DENM_SendDENMUpdate(&Mgmt, &Denm, ActionId);
  }

  if (Status == DENM_SUCCESS)
  {
    d_printf(D_INFO, NULL, "DENM: ActionID %08" PRIx64 "\n", ActionId);

    // update last EVW time
    lastEVW = Util_Now();

    Ret = 0;
  }
  else
  {
    d_printf(D_WARN, NULL, "DENM: Failed %d\n", Status);
  }

Error:
  return Ret;
}


//------------------------------------------------------------------------------
// MAPSPAT controls
//------------------------------------------------------------------------------

static void ITSTx_PrepareImzm(const tITSTxIMZMParams *pParams, tIMZMMgmt *pMgmt, ITSInterferenceManagementZoneMessage *pImzmData)
{
  if (pParams && pImzmData && pMgmt)
  {

    pImzmData->imzmParameters.imzmContainer.interferenceManagementZones.count = 1;
    pImzmData->imzmParameters.imzmContainer.interferenceManagementZones.tab =
      (ITSInterferenceManagementZone *)asn1_mallocz(pImzmData->imzmParameters.imzmContainer.interferenceManagementZones.count * sizeof(ITSInterferenceManagementZone));

    ITSInterferenceManagementZone *pZone = &pImzmData->imzmParameters.imzmContainer.interferenceManagementZones.tab[0];

    pZone->zoneDefinition.interferenceManagementZoneLatitude = -340000000;
    pZone->zoneDefinition.interferenceManagementZoneLongitude = 1380000000;
    pZone->zoneDefinition.interferenceManagementZoneRadius_option = true;
    pZone->zoneDefinition.interferenceManagementZoneRadius = 101;
    pZone->zoneDefinition.interferenceManagementZoneID_option = true;
    pZone->zoneDefinition.interferenceManagementZoneID = 999;

    pZone->interferenceManagementInfo.count = 1;
    pZone->interferenceManagementInfo.tab = (ITSInterferenceManagementInfoPerChannel *)asn1_mallocz(pZone->interferenceManagementInfo.count * sizeof(ITSInterferenceManagementInfoPerChannel));

    ITSInterferenceManagementInfoPerChannel *pInfo = &pZone->interferenceManagementInfo.tab[0];

    pInfo->interferenceManagementChannel.centreFrequency = 59;
    pInfo->interferenceManagementChannel.channelWidth = 20;
    pInfo->interferenceManagementChannel.exponent = 6;
    pInfo->interferenceManagementZoneType = ITSInterferenceManagementZoneType_urbanRail;

    // Management
    pMgmt->RepetitionDuration = 86400; // all day
    pMgmt->RepetitionInterval = pParams->ApplInterval;
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;

    pMgmt->PopulateBasicContainer = true;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare IMZM message. No transmission!\n");
  }

}

/**
 * @brief Allocate and initialise MAP. MAP details obtained from config file
 * @param pParams pointer to MAP config params
 * @return pointer to allocated MAP PDU, and NULL if failed
 *
 * The MAP contains only one intersection (that is why intersections.count is
 * hardcoded to 1. Make sure that IntersectionId matches SPAT IntersectionId
 */

static void ITSTx_PrepareMap(const tITSTxMAPParams *pParams, tMAPMgmt *pMgmt, ITSMapData *pMapData)
{
  if (pParams && pMapData && pMgmt)
  {
    int i, j;
    ITSIntersectionGeometry *pIntersection;
    ITSGenericLane * pLane;
    ITSNodeXY *pNode;
    ITSConnection *pConnection;

    pMapData->msgIssueRevision = 0;

    pMapData->intersections_option = true;
    // Yes, count is hardcoded as we assume MAP contains only one intersection
    pMapData->intersections.count = 1;
    pMapData->intersections.tab = (ITSIntersectionGeometry *)
      asn1_mallocz(pMapData->intersections.count * sizeof(ITSIntersectionGeometry));
    d_assert(pMapData->intersections.tab);
    pIntersection = &pMapData->intersections.tab[0];

    pIntersection->id.id = pParams->IntersectionId;
    // change of revision is required to send same intersection with new data
    pIntersection->revision = 1;
    pIntersection->refPoint.lat = pParams->Latitude;
    pIntersection->refPoint.Long = pParams->Longitude;

    pIntersection->refPoint.elevation_option = false;
    pIntersection->refPoint.regional_option = false;

    if (pParams->Altitude_cm != ITSAltitudeValue_ID_unavailable)
    {
      // Note: demonstration of regional extension
      // use extension 'Altitude' (ETSI) rather than OPTIONAL 'Elevation' (J2735)
      pIntersection->refPoint.regional_option = true;

      // Note: demonstration of regional extension
      // regional is of type ITSPosition3D_1
      // NOTE: Cohda Wireshark has been customised to decode this regional extension,
      // but typically regional extensions are only interpreted as binary blobs

      // Only one regional extension being defined
      pIntersection->refPoint.regional.count = 1;
      // ITSRegionalExtension_18 is ITSPosition3D_1 tab member
      pIntersection->refPoint.regional.tab = asn1_mallocz_value(asn1_type_ITSRegionalExtension_18);

      // Set (first) regional extension Id, type and data storage
      // region is 'addGrpC' for EU
      // type is the ASN1 type for the regional specific data, ITSPosition3D_addGrpC in this case
      pIntersection->refPoint.regional.tab[0].regionId = ITSRegionId_addGrpC;
      pIntersection->refPoint.regional.tab[0].regExtValue.type = (ASN1CType *)asn1_type_ITSPosition3D_addGrpC;
      pIntersection->refPoint.regional.tab[0].regExtValue.u.data = asn1_mallocz_value(asn1_type_ITSPosition3D_addGrpC);

      // Access regional extension data
      ITSPosition3D_addGrpC* paddGrpC = (ITSPosition3D_addGrpC *)pIntersection->refPoint.regional.tab[0].regExtValue.u.data;

      // Populate region-specific elements
      paddGrpC->altitude.altitudeValue = pParams->Altitude_cm;
      paddGrpC->altitude.altitudeConfidence = ITSAltitudeConfidence_unavailable;
    }

    pIntersection->laneSet.count = pParams->NumLanes;
    pIntersection->laneSet.tab = (ITSGenericLane *)
      asn1_mallocz(pIntersection->laneSet.count * sizeof(ITSGenericLane));
    d_assert(pIntersection->laneSet.tab);

    for (i=0; i < pParams->NumLanes; i++)
    {
      pLane = &pIntersection->laneSet.tab[i];
      pLane->laneID = pParams->pLanes[i].LaneId;

      // Hardcoded direction and lane types. Other directions and types are not
      // considered by spat/map framework
      pLane->laneAttributes.laneType.choice = ITSLaneTypeAttributes_vehicle;
      ETSASN_SetBitString(&pLane->laneAttributes.laneType.u.vehicle, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
      ETSASN_SetBitString(&pLane->laneAttributes.directionalUse, 2, pParams->pLanes[i].ingressLane, pParams->pLanes[i].egressLane);
      ETSASN_SetBitString(&pLane->laneAttributes.sharedWith, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

      pLane->nodeList.choice = ITSNodeListXY_nodes;
      pLane->nodeList.u.nodes.count = pParams->pLanes[i].NumNodes;
      pLane->nodeList.u.nodes.tab = (ITSNodeXY*)
        asn1_mallocz(pLane->nodeList.u.nodes.count * sizeof(ITSNodeXY));
      d_assert(pLane->nodeList.u.nodes.tab);

      for (j=0; j < pParams->pLanes[i].NumNodes; j++)
      {
        pNode = &pLane->nodeList.u.nodes.tab[j];
        if (pParams->pLanes[i].AbsolutePosNodes)
        {
          // Absolute position nodes
          pNode->delta.choice = ITSNodeOffsetPointXY_node_LatLon;
          pNode->delta.u.node_LatLon.lon = pParams->pLanes[i].pNodes[j].X;
          pNode->delta.u.node_LatLon.lat = pParams->pLanes[i].pNodes[j].Y;
        }
        else
        {
          // Relative position nodes
          // XY6 format supports the largest delta position (but the least efficient for MAPEM size)
          pNode->delta.choice = ITSNodeOffsetPointXY_node_XY6;
          pNode->delta.u.node_XY6.x = pParams->pLanes[i].pNodes[j].X;
          pNode->delta.u.node_XY6.y = pParams->pLanes[i].pNodes[j].Y;
        }
      }

      if (pParams->pLanes[i].NumConnections)
      {
        pLane->connectsTo_option = true;
        pLane->connectsTo.count = pParams->pLanes[i].NumConnections;
        pLane->connectsTo.tab = (ITSConnection*)
          asn1_mallocz(pLane->connectsTo.count * sizeof(ITSConnection));
        d_assert(pLane->connectsTo.tab);

        for (j=0; j < pParams->pLanes[i].NumConnections; j++)
        {
          pConnection = &pLane->connectsTo.tab[j];
          pConnection->signalGroup_option = true;
          pConnection->signalGroup = pParams->pLanes[i].pConnections[j].SignalGroup;
          pConnection->connectingLane.lane = pParams->pLanes[i].pConnections[j].ConnectsTo;

          if(pParams->pLanes[i].pConnections[j].Maneuver == 1)
          {
            // Straight maneuver: first bit of first byte only is set
            pConnection->connectingLane.maneuver_option = true;
            ETSASN_SetBitString(&pConnection->connectingLane.maneuver, 12, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          }
          else if(pParams->pLanes[i].pConnections[j].Maneuver == 2)
          {
            // Left maneuver: second bit of first byte only is set
            pConnection->connectingLane.maneuver_option = true;
            ETSASN_SetBitString(&pConnection->connectingLane.maneuver, 12, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          }
          else if(pParams->pLanes[i].pConnections[j].Maneuver == 3)
          {
            // Right maneuver: third bit of first byte only is set
            pConnection->connectingLane.maneuver_option = true;
            ETSASN_SetBitString(&pConnection->connectingLane.maneuver, 12, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          }
          else
          {
            // No maneuver
            pConnection->connectingLane.maneuver_option = false;
            ETSASN_SetBitString(&pConnection->connectingLane.maneuver, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          }
        }
      }
    }

    // Management
    pMgmt->RepetitionDuration = 86400; // all day
    pMgmt->RepetitionInterval = pParams->ApplInterval;
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare MAP message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise SRM. SRM details obtained from config file
 * @param pParams pointer to SRM config params
 * @return pointer to allocated SRM PDU, and NULL if failed
 *
 */

static void ITSTx_PrepareSrm(const tITSTxSRMParams *pParams, tSRMMgmt *pMgmt, ITSSignalRequestMessage *pSrmData)
{
  if (pParams && pSrmData && pMgmt)
  {
    // Create sample SRM content
    // NOTE: not checking for malloc failures in the example code,
    // how to handle this in application implementation is up to the developer
    pSrmData->second = Util_Now() % 60000;

    pSrmData->sequenceNumber_option = true;
    pSrmData->sequenceNumber = 1;

    pSrmData->requests_option = true;
    pSrmData->requests.count = 1;
    pSrmData->requests.tab = asn1_mallocz(sizeof(ITSSignalRequestPackage) * pSrmData->requests.count);
    pSrmData->requests.tab[0].request.id.id = pParams->IntersectionId;
    pSrmData->requests.tab[0].request.requestID = 0;
    pSrmData->requests.tab[0].request.requestType = ITSPriorityRequestType_priorityRequest;
    pSrmData->requests.tab[0].request.inBoundLane.choice = ITSIntersectionAccessPoint_lane;
    pSrmData->requests.tab[0].request.inBoundLane.u.lane = 2;

    pSrmData->requestor.id.choice = ITSVehicleID_stationID;
    pSrmData->requestor.id.u.stationID = ETSISRMSSM_STATIONID_POPULATE;

    // Management
    pMgmt->RepetitionDuration = 30;
    pMgmt->RepetitionInterval = 1000;
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare SRM message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise SSM. SSM details obtained from config file
 * @param pParams pointer to SSM config params
 * @return pointer to allocated SSM PDU, and NULL if failed
 *
 */

static void ITSTx_PrepareSsm(const tITSTxSSMParams *pParams, tSSMMgmt *pMgmt, ITSSignalStatusMessage *pSsmData)
{
  if (pParams && pSsmData && pMgmt)
  {
    // Create sample SSM content
    // NOTE: not checking for malloc failures in the example code,
    // how to handle this in application implementation is up to the developer
    pSsmData->second = Util_Now() % 60000;

    pSsmData->sequenceNumber_option = true;
    pSsmData->sequenceNumber = 1;

    pSsmData->status.count = 1;
    pSsmData->status.tab = asn1_mallocz(sizeof(ITSSignalRequestPackage) * pSsmData->status.count);
    pSsmData->status.tab[0].sequenceNumber = 1;
    pSsmData->status.tab[0].id.id = pParams->IntersectionId;
    pSsmData->status.tab[0].sigStatus.count = 1;
    pSsmData->status.tab[0].sigStatus.tab = asn1_mallocz(sizeof(ITSSignalStatusPackage) * pSsmData->status.tab[0].sigStatus.count);
    pSsmData->status.tab[0].sigStatus.tab[0].inboundOn.choice = ITSIntersectionAccessPoint_lane;
    pSsmData->status.tab[0].sigStatus.tab[0].inboundOn.u.lane = 2;
    pSsmData->status.tab[0].sigStatus.tab[0].duration = 60;
    pSsmData->status.tab[0].sigStatus.tab[0].status = ITSPrioritizationResponseStatus_granted;

    // Management
    pMgmt->RepetitionDuration = 30;
    pMgmt->RepetitionInterval = 1000;
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare SSM message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise SA. SA details obtained from config file
 * @param pParams pointer to SA config params
 * @return pointer to allocated SA PDU, and NULL if failed
 *
 */

static void ITSTx_PrepareSA(const tITSTxSAParams *pParams, tSAMgmt *pMgmt, tSAMsg *pSAMsg)
{
  (void)pParams;

  if (pMgmt && pSAMsg)
  {
    pSAMsg->ReqType = ETSISA_REQUEST_REGISTRATION;

    pSAMsg->ServiceCount = 1;
    pSAMsg->Service[0].ITSAID = pParams->ITSAID;
    strncpy((char *)pSAMsg->Service[0].PSC, "Demo", ETSISA_PSCMAX);
    pSAMsg->Service[0].PSCLen = strlen("Demo")+1;
    pSAMsg->Service[0].ProtId = pParams->Protocol;
    pSAMsg->Service[0].ChannelIndex = ITSChannelIndex_ID_notUsed;
    memcpy(pSAMsg->Service[0].ApplicationData, pParams->Data, pParams->DataLen);
    pSAMsg->Service[0].ApplicationDataLen = pParams->DataLen;
    // Not IPv6 service so skip IPv6 parameters

    pSAMsg->Inc2DLoc = false;
    pSAMsg->Inc3DLoc = false;
    pSAMsg->IncRptRate = false;
    pSAMsg->pAdvID = "Cohda";

    // Management
    pMgmt->RepetitionDuration = 86400; // all day
    pMgmt->RepetitionInterval = 1000;

    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare SA message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise RTCM. RTCM details obtained from config file
 * @param pParams pointer to RTCM config params
 * @return pointer to allocated RTCM PDU, and NULL if failed
 *
 */

static void ITSTx_PrepareRTCM(const tITSTxRTCMParams *pParams, tRTCMMgmt *pMgmt, ITSRTCMcorrections *pRTCMcorrections)
{
  (void)pParams;
  if (pRTCMcorrections && pMgmt)
  {
    pRTCMcorrections->msgCnt = 0;
    pRTCMcorrections->rev = 1;
    pRTCMcorrections->msgs.count = 1;
    pRTCMcorrections->msgs.tab = (ITSRTCMmessage *)
      asn1_mallocz(pRTCMcorrections->msgs.count * sizeof(ITSRTCMmessage));
    pRTCMcorrections->msgs.tab[0].len = pParams->DataLen;
    pRTCMcorrections->msgs.tab[0].buf = asn1_mallocz(pRTCMcorrections->msgs.tab[0].len);
    memcpy(pRTCMcorrections->msgs.tab[0].buf, pParams->Data, pRTCMcorrections->msgs.tab[0].len);

    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare RTCM message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise SPAT. SPAT details obtained from config file
 * @param pParams pointer to SPAT config params
 * @return pointer to allocated SPAT PDU, and NULL if failed
 *
 * The SPAT contains only one intersection (that is why intersections.count is
 * hardcoded to 1. Make sure that IntersectionId matches MAP IntersectionId
 */
static void ITSTx_PrepareSpat(const tITSTxSPATParams *pParams, tSPATMgmt *pMgmt, ITSSPAT *pSpat)
{
  if (pParams && pMgmt && pSpat)
  {
    int i;
    ITSIntersectionState *pIntersection;
    ITSMovementState *pState;

    // Yes, count is hardcoded as we assume SPAT contains only one intersection
    pSpat->intersections.count = 1;
    pSpat->intersections.tab = (ITSIntersectionState *)
      asn1_mallocz(pSpat->intersections.count * sizeof(ITSIntersectionState));
    d_assert(pSpat->intersections.tab);

    d_printf(D_INTERN, NULL, "Intersections %zd\n", pSpat->intersections.count);

    pIntersection = &pSpat->intersections.tab[0];

    pIntersection->id.id = pParams->IntersectionId;
    pIntersection->revision = 1;  // Not currently used in spat framework
    ETSASN_SetBitString(&pIntersection->status, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    pIntersection->states.count = pParams->NumMovements;
    pIntersection->states.tab = (ITSMovementState *)
      asn1_mallocz(pIntersection->states.count * sizeof(ITSMovementState));
    d_assert(pIntersection->states.tab);

    // Calculate current time in TimeMark format. TimeMark is defined as offset
    // to the UTC full hour with a resolution of 36000 in units of 1/10th second
    int NowTimeMark = (Util_Now() / ((int64_t)100)) % 36000;

    for(i = 0; i < pParams->NumMovements; i++)
    {
      pState = &pIntersection->states.tab[i];
      const tSPATMovementParams * pSPATMovementParams = &pParams->pMovements[i];
      pState->signalGroup = pSPATMovementParams->SignalGroup;
      // For simplicity, each movement state has only one state_time_speed object
      // (update ITSTx_UpdateSpatTiming if this is ever changed!)
      pState->state_time_speed.count = 1;
      pState->state_time_speed.tab = (ITSMovementEvent *)
        asn1_mallocz(pState->state_time_speed.count * sizeof(ITSMovementEvent));
      d_assert(pState->state_time_speed.tab);
      pState->state_time_speed.tab->eventState = pSPATMovementParams->CurrentState;
      if (pState->state_time_speed.tab->eventState != ITSMovementPhaseState_unavailable)
      {
        pState->state_time_speed.tab->timing_option = true;
        pState->state_time_speed.tab->timing.minEndTime =
          (pSPATMovementParams->TimeToChange + NowTimeMark)%36000;
        pState->state_time_speed.tab->speeds_option =
          (pSPATMovementParams->NumSpeedAdvisories > 0);

        if (pState->state_time_speed.tab->speeds_option)
        {
          pState->state_time_speed.tab->speeds.count = pSPATMovementParams->NumSpeedAdvisories;
          pState->state_time_speed.tab->speeds.tab = (ITSAdvisorySpeed *)
            asn1_mallocz(pState->state_time_speed.tab->speeds.count * sizeof(ITSAdvisorySpeed));
          d_assert(pState->state_time_speed.tab->speeds.tab);
          int j = 0;
          for (; j < pSPATMovementParams->NumSpeedAdvisories; j++)
          {
            ITSAdvisorySpeed *pAdvisorySpeed = &pState->state_time_speed.tab->speeds.tab[j];
            const tSPATSpeedAdvisory * pSPATSpeedAdvisory = &pSPATMovementParams->pSpeedAdvisories[j];
            pAdvisorySpeed->type            = pSPATSpeedAdvisory->Type;
            pAdvisorySpeed->speed_option    = true;
            pAdvisorySpeed->speed           = pSPATSpeedAdvisory->Speed_tenthmps;
            pAdvisorySpeed->distance_option = true;
            pAdvisorySpeed->distance        = pSPATSpeedAdvisory->Distance_m;
          }
        }
      }
    }
    // Management
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare SPAT message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise IVI. IVI details obtained from config file
 * @param pITS pointer to ITS handle
 * @return pointer to allocated IVI PDU, and NULL if failed
 *
 */
static void ITSTx_PrepareIvi(const tITSTxIVSParams *pParams, tIVIMgmt *pMgmt, ITSIviStructure *pIVI)
{
  if (pParams && pMgmt && pIVI)
  {
    // pIVI->mandatory...
    pIVI->mandatory.serviceProviderId.countryCode.len = 10;
    pIVI->mandatory.serviceProviderId.countryCode.buf = (uint8_t *)asn1_mallocz((pIVI->mandatory.serviceProviderId.countryCode.len + 7) / 8);
    pIVI->mandatory.serviceProviderId.countryCode.buf[0] = pParams->ServiceProviderCountryID >> 2;
    pIVI->mandatory.serviceProviderId.countryCode.buf[1] = (pParams->ServiceProviderCountryID & 0x03) << 6;
    pIVI->mandatory.serviceProviderId.providerIdentifier = pParams->ServiceProviderIssuerId;
    pIVI->mandatory.iviIdentificationNumber = pParams->IviIdentificationNumber;
    pIVI->mandatory.timeStamp_option = true;
    ETSASN_SetTimestamp(&pIVI->mandatory.timeStamp, ETSIFAC_TIMESTAMP_TAI_NOW);
    if (pParams->ValidFromTime > MAX_IVI_VALIDITY_DELTA)
    {
      // Absolute
      ETSASN_SetTimestamp(&pIVI->mandatory.validFrom, pParams->ValidFromTime);
      pIVI->mandatory.validFrom_option = true;
    }
    else if (pParams->ValidFromTime > 0)
    {
      // Delta
      ETSASN_SetTimestamp(&pIVI->mandatory.validFrom, LPH_Leap2004Now() + pParams->ValidFromTime);
      pIVI->mandatory.validFrom_option = true;
    }
    else
    {
      pIVI->mandatory.validFrom_option = false;
    }
    if (pParams->ValidToTime > MAX_IVI_VALIDITY_DELTA)
    {
      // Absolute
      ETSASN_SetTimestamp(&pIVI->mandatory.validTo, pParams->ValidToTime);
      pIVI->mandatory.validTo_option = true;
    }
    else if (pParams->ValidToTime > 0)
    {
      // Delta
      ETSASN_SetTimestamp(&pIVI->mandatory.validTo, LPH_Leap2004Now() + pParams->ValidToTime);
      pIVI->mandatory.validTo_option = true;
    }
    else
    {
      // None
      pIVI->mandatory.validTo_option = false;
    }
    pIVI->mandatory.connectedIviStructures_option = false;
    pIVI->mandatory.iviStatus = ITSIviStatus_update;
    // pIVI->optional...
    pIVI->optional_option = true;
    pIVI->optional.count = 2;
    if (pParams->RCCPartsCount > 0)
    {
      // Support one part as per in-scope examples
      pIVI->optional.count++;
    }
    if (pParams->TCPartsCount > 0)
    {
      // Support one part as per in-scope examples
      pIVI->optional.count++;
    }
    pIVI->optional.tab = (ITSIviContainer *)asn1_mallocz(pIVI->optional.count * sizeof(ITSIviContainer));
    pIVI->optional.tab[0].choice = ITSIviContainer_glc;
    pIVI->optional.tab[0].u.glc.referencePosition.latitude  = pParams->RefLatitude;
    pIVI->optional.tab[0].u.glc.referencePosition.longitude = pParams->RefLongitude;
    pIVI->optional.tab[0].u.glc.referencePosition.positionConfidenceEllipse.semiMajorConfidence  = ITSSemiAxisLength_oneCentimeter;
    pIVI->optional.tab[0].u.glc.referencePosition.positionConfidenceEllipse.semiMinorConfidence  = ITSSemiAxisLength_oneCentimeter;
    pIVI->optional.tab[0].u.glc.referencePosition.positionConfidenceEllipse.semiMajorOrientation = ITSHeadingValue_wgs84North;
    pIVI->optional.tab[0].u.glc.referencePosition.altitude.altitudeValue = pParams->RefAltitude;
    pIVI->optional.tab[0].u.glc.referencePosition.altitude.altitudeConfidence = ITSAltitudeConfidence_alt_000_01;
    pIVI->optional.tab[0].u.glc.referencePositionTime_option = false;
    pIVI->optional.tab[0].u.glc.referencePositionHeading_option = false;
    pIVI->optional.tab[0].u.glc.referencePositionSpeed_option = false;

    // Assume one detection & one relevance zone
    if (pParams->DetectionZoneOffsetCount || pParams->DetectionZoneAbsPosnCount || pParams->RelevanceZoneOffsetCount || pParams->RelevanceZoneAbsPosnCount)
    {
      pIVI->optional.tab[0].u.glc.parts.count = 2;
      pIVI->optional.tab[0].u.glc.parts.tab = (ITSGlcPart *)asn1_mallocz(pIVI->optional.tab[0].u.glc.parts.count * sizeof(ITSGlcPart));
      // Detection zone
      ITSGlcPart *pGLC = &pIVI->optional.tab[0].u.glc.parts.tab[0];
      pGLC->zoneId = 1;
      pGLC->laneNumber_option = false;
      pGLC->laneNumber = 0;
      pGLC->zoneExtension_option = false;
      pGLC->zoneExtension = 0;
      pGLC->zoneHeading_option = false;

      // Priority to delta positions...
      if (pParams->DetectionZoneOffsetCount)
      {
        if (pParams->DetectionZoneOffsetCount < 2)
        {
          d_printf(D_WARN, NULL, "Zone with 1 delta position cannot define a segment!\n");
        }
        pGLC->zone_option = true;
        pGLC->zone.choice = ITSZone_segment;
        pGLC->zone.u.segment.line.choice = ITSPolygonalLine_deltaPositions;
        pGLC->zone.u.segment.line.u.deltaPositions.count = pParams->DetectionZoneOffsetCount;
        pGLC->zone.u.segment.line.u.deltaPositions.tab = (ITSDeltaPosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.deltaPositions.count * sizeof(ITSDeltaPosition));
        int Point;
        for (Point = 0; Point < pParams->DetectionZoneOffsetCount; Point++)
        {
          pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLatitude  = pParams->DetectionZoneOffset[Point].DeltaLatitude;
          pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLongitude = pParams->DetectionZoneOffset[Point].DeltaLongitude;
        }
      }
      else if (pParams->DetectionZoneAbsPosnCount)
      {
        if (pParams->DetectionZoneAbsPosnCount < 2)
        {
          d_printf(D_WARN, NULL, "Zone with 1 absolute position cannot define a segment!\n");
        }
        pGLC->zone_option = true;
        pGLC->zone.choice = ITSZone_segment;
        pGLC->zone.u.segment.line.choice = ITSPolygonalLine_absolutePositions;
        pGLC->zone.u.segment.line.u.absolutePositions.count = pParams->DetectionZoneAbsPosnCount;
        pGLC->zone.u.segment.line.u.absolutePositions.tab = (ITSAbsolutePosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.absolutePositions.count * sizeof(ITSAbsolutePosition));
        int Point;
        for (Point = 0; Point < pParams->DetectionZoneAbsPosnCount; Point++)
        {
          pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].latitude  = pParams->DetectionZoneAbsPosn[Point].Latitude;
          pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].longitude = pParams->DetectionZoneAbsPosn[Point].Longitude;
        }
      }
      pGLC->zone.u.segment.laneWidth_option = false;
      pGLC->zone.u.segment.laneWidth = 0;
      // Relevance zone
      pGLC = &pIVI->optional.tab[0].u.glc.parts.tab[1];
      pGLC->zoneId = 2;
      pGLC->laneNumber_option = false;
      pGLC->laneNumber = 0;
      pGLC->zoneExtension_option = false;
      pGLC->zoneExtension = 0;
      pGLC->zoneHeading_option = false;

      // Priority to delta positions...
      if (pParams->RelevanceZoneOffsetCount)
      {
        pGLC->zone_option = true;
        pGLC->zone.choice = ITSZone_segment;
        pGLC->zone.u.segment.line.choice = ITSPolygonalLine_deltaPositions;
        pGLC->zone.u.segment.line.u.deltaPositions.count = pParams->RelevanceZoneOffsetCount;
        pGLC->zone.u.segment.line.u.deltaPositions.tab = (ITSDeltaPosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.deltaPositions.count * sizeof(ITSDeltaPosition));
        int Point;
        for (Point = 0; Point < pParams->RelevanceZoneOffsetCount; Point++)
        {
          pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLatitude  = pParams->RelevanceZoneOffset[Point].DeltaLatitude;
          pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLongitude = pParams->RelevanceZoneOffset[Point].DeltaLongitude;
        }
      }
      else if (pParams->RelevanceZoneAbsPosnCount)
      {
        pGLC->zone_option = true;
        pGLC->zone.choice = ITSZone_segment;
        pGLC->zone.u.segment.line.choice = ITSPolygonalLine_absolutePositions;
        pGLC->zone.u.segment.line.u.absolutePositions.count = pParams->RelevanceZoneAbsPosnCount;
        pGLC->zone.u.segment.line.u.absolutePositions.tab = (ITSAbsolutePosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.absolutePositions.count * sizeof(ITSAbsolutePosition));
        int Point;
        for (Point = 0; Point < pParams->RelevanceZoneAbsPosnCount; Point++)
        {
          pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].latitude  = pParams->RelevanceZoneAbsPosn[Point].Latitude;
          pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].longitude = pParams->RelevanceZoneAbsPosn[Point].Longitude;
        }
      }
      pGLC->zone.u.segment.laneWidth_option = false;
      pGLC->zone.u.segment.laneWidth = 0;
    }
    else
    {
      // Generic zones
      pIVI->optional.tab[0].u.glc.parts.count = pParams->GenericZoneCount;
      pIVI->optional.tab[0].u.glc.parts.tab = (ITSGlcPart *)asn1_mallocz(pIVI->optional.tab[0].u.glc.parts.count * sizeof(ITSGlcPart));

      size_t Zone;
      for (Zone = 0; Zone < pIVI->optional.tab[0].u.glc.parts.count; Zone++)
      {
        ITSGlcPart *pGLC = &pIVI->optional.tab[0].u.glc.parts.tab[Zone];
        pGLC->zoneId = pParams->GenericZone[Zone].GenericZoneId;

        if (pParams->GenericZone[Zone].GenericSegmentCount < 2)
        {
          d_printf(D_WARN, NULL, "Zone with 1 delta position cannot define a segment!\n");
        }
        pGLC->zone_option = true;
        pGLC->zone.choice = ITSZone_segment;
        if (pParams->GenericZone[Zone].IsAbsolutes)
        {
          pGLC->zone.u.segment.line.choice = ITSPolygonalLine_absolutePositions;
          pGLC->zone.u.segment.line.u.absolutePositions.count = pParams->GenericZone[Zone].GenericSegmentCount;
          pGLC->zone.u.segment.line.u.absolutePositions.tab = (ITSAbsolutePosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.absolutePositions.count * sizeof(ITSAbsolutePosition));
          int Point;
          for (Point = 0; Point < pParams->GenericZone[Zone].GenericSegmentCount; Point++)
          {
            pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].latitude  = pParams->GenericZone[Zone].GenericSegment[Point].Latitude;
            pGLC->zone.u.segment.line.u.absolutePositions.tab[Point].longitude = pParams->GenericZone[Zone].GenericSegment[Point].Longitude;
          }
        }
        else
        {
          pGLC->zone.u.segment.line.choice = ITSPolygonalLine_deltaPositions;
          pGLC->zone.u.segment.line.u.deltaPositions.count = pParams->GenericZone[Zone].GenericSegmentCount;
          pGLC->zone.u.segment.line.u.deltaPositions.tab = (ITSDeltaPosition *)asn1_mallocz(pGLC->zone.u.segment.line.u.deltaPositions.count * sizeof(ITSDeltaPosition));
          int Point;
          for (Point = 0; Point < pParams->GenericZone[Zone].GenericSegmentCount; Point++)
          {
            pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLatitude  = pParams->GenericZone[Zone].GenericSegment[Point].Latitude;
            pGLC->zone.u.segment.line.u.deltaPositions.tab[Point].deltaLongitude = pParams->GenericZone[Zone].GenericSegment[Point].Longitude;
          }
        }
      }
    }

    // road sign
    pIVI->optional.tab[1].choice = ITSIviContainer_giv;
    pIVI->optional.tab[1].u.giv.count = pParams->GICPartsCount;

    pIVI->optional.tab[1].u.giv.tab = (ITSGicPart *)asn1_mallocz(pIVI->optional.tab[1].u.giv.count * sizeof(ITSGicPart));

    size_t GicPart = 0;

    for (GicPart = 0; GicPart < pIVI->optional.tab[1].u.giv.count; GicPart++)
    {
      ITSGicPart *pGIC = &pIVI->optional.tab[1].u.giv.tab[GicPart];

      pGIC->detectionZoneIds_option = true;

      if (pParams->GICPart[GicPart].NumDetZones)
      {
        pGIC->detectionZoneIds.count = pParams->GICPart[GicPart].NumDetZones;
        pGIC->detectionZoneIds.tab = (ITSZid *)asn1_mallocz(pGIC->detectionZoneIds.count * sizeof(ITSZid));
        size_t Zone;
        for (Zone = 0; Zone < pGIC->detectionZoneIds.count; Zone++)
        {
          pGIC->detectionZoneIds.tab[Zone] = pParams->GICPart[GicPart].DetZones[Zone];
        }
      }
      else
      {
        pGIC->detectionZoneIds.count = 1;
        pGIC->detectionZoneIds.tab = (ITSZid *)asn1_mallocz(pGIC->detectionZoneIds.count * sizeof(ITSZid));
        pGIC->detectionZoneIds.tab[0] = 1;
      }

      pGIC->relevanceZoneIds_option = true;

      if (pParams->GICPart[GicPart].NumRelZones)
      {
        pGIC->relevanceZoneIds.count = pParams->GICPart[GicPart].NumRelZones;
        pGIC->relevanceZoneIds.tab = (ITSZid *)asn1_mallocz(pGIC->relevanceZoneIds.count * sizeof(ITSZid));
        size_t Zone;
        for (Zone = 0; Zone < pGIC->relevanceZoneIds.count; Zone++)
        {
          pGIC->relevanceZoneIds.tab[Zone] = pParams->GICPart[GicPart].RelZones[Zone];
        }
      }
      else
      {
        pGIC->relevanceZoneIds.count = 1;
        pGIC->relevanceZoneIds.tab = (ITSZid *)asn1_mallocz(pGIC->relevanceZoneIds.count * sizeof(ITSZid));
        pGIC->relevanceZoneIds.tab[0] = 2;
      }

      pGIC->direction_option = true;
      pGIC->direction = ITSDirection_sameDirection;
      pGIC->driverAwarenessZoneIds_option = false;
      pGIC->minimumAwarenessTime_option = true;
      pGIC->minimumAwarenessTime = pParams->GICPart[GicPart].MinimumAwarenessTime;
      if (pParams->GICPart[GicPart].NumApplicLanes)
      {
        pGIC->applicableLanes_option = true;
        pGIC->applicableLanes.count = pParams->GICPart[GicPart].NumApplicLanes;
        pGIC->applicableLanes.tab = (ITSLanePosition *)asn1_mallocz(pGIC->applicableLanes.count * sizeof(ITSLanePosition));
        size_t Lanes;
        for (Lanes = 0; Lanes < pGIC->applicableLanes.count; Lanes++)
        {
          pGIC->applicableLanes.tab[Lanes] = pParams->GICPart[GicPart].ApplicLanes[Lanes];
        }
      }
      pGIC->iviType = pParams->GICPart[GicPart].IviType;
      pGIC->vehicleCharacteristics_option = false;

      pGIC->roadSignCodes.count = pParams->GICPart[GicPart].NumRoadSigns;
      pGIC->roadSignCodes.tab = (ITSRSCode *)asn1_mallocz(pGIC->roadSignCodes.count * sizeof(ITSRSCode));
      size_t Ix;
      for (Ix = 0; Ix < pGIC->roadSignCodes.count; Ix++)
      {
        pGIC->roadSignCodes.tab[Ix].layoutComponentId_option = false;
        if (pParams->GICPart[GicPart].useITSISO14823Code)
        {
          pGIC->roadSignCodes.tab[Ix].code.u.itisCodes = pParams->GICPart[GicPart].ITSISO14823Code;
          pGIC->roadSignCodes.tab[Ix].code.choice = ITSRSCode_1_itisCodes;
        }
        else
        {
          pGIC->roadSignCodes.tab[Ix].code.choice = ITSRSCode_1_iso14823;
          pGIC->roadSignCodes.tab[Ix].code.u.iso14823.pictogramCode.countryCode_option = false;
          pGIC->roadSignCodes.tab[Ix].code.u.iso14823.pictogramCode.serviceCategoryCode.choice = pParams->GICPart[GicPart].RoadSigns[Ix].ITSISO14823Code_4;
          pGIC->roadSignCodes.tab[Ix].code.u.iso14823.pictogramCode.serviceCategoryCode.u.trafficSignPictogram = pParams->GICPart[GicPart].RoadSigns[Ix].TrafficSignPictogram;
          pGIC->roadSignCodes.tab[Ix].code.u.iso14823.pictogramCode.pictogramCategoryCode.nature = pParams->GICPart[GicPart].RoadSigns[Ix].PictogramCategoryCodeNature;
          pGIC->roadSignCodes.tab[Ix].code.u.iso14823.pictogramCode.pictogramCategoryCode.serialNumber = pParams->GICPart[GicPart].RoadSigns[Ix].PictogramCategoryCodeSerialNumber;

          // Include additional speed attributes (if set)
          if (pParams->GICPart[GicPart].RoadSigns[Ix].AttributesSPEValue != 0)
          {
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes_option = true;
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.count = 1;
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.tab = (ITSISO14823Attribute *)asn1_mallocz(pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.count * sizeof(ITSISO14823Attribute));
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.tab[0].choice = ITSISO14823Attribute_spe;
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.tab[0].u.spe.speedLimitMax_option = true;
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.tab[0].u.spe.speedLimitMax = pParams->GICPart[GicPart].RoadSigns[Ix].AttributesSPEValue;
            pGIC->roadSignCodes.tab[Ix].code.u.iso14823.attributes.tab[0].u.spe.unit = pParams->GICPart[GicPart].RoadSigns[Ix].AttributesSPEUnits;
          }
        }
      }

      // Can add some pre-defined HGV info to 'complicate' the message
      // Currently added _before_ other sign info as Wireshark decoding fails on SPE units (used in Max Speed sign)
      if (pParams->GICPart[GicPart].HGVInfo > 0)
      {
        pGIC->iviType = ITSIviType_regulatoryMessages;
        pGIC->vehicleCharacteristics_option = true;
        pGIC->vehicleCharacteristics.count = 1;
        pGIC->vehicleCharacteristics.tab = (ITSCompleteVehicleCharacteristics *)asn1_mallocz(pGIC->vehicleCharacteristics.count * sizeof(ITSCompleteVehicleCharacteristics));
        pGIC->vehicleCharacteristics.tab[0].train_option  = true;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo_option = true;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.count = 2;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab = (ITSVehicleCharacteristicsFixValues *)asn1_mallocz(pGIC->vehicleCharacteristics.tab[0].train.equalTo.count * sizeof(ITSVehicleCharacteristicsFixValues));
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[0].choice = ITSVehicleCharacteristicsFixValues_euVehicleCategoryCode;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[0].u.euVehicleCategoryCode.choice = ITSEuVehicleCategoryCode_euVehicleCategoryN;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[0].u.euVehicleCategoryCode.u.euVehicleCategoryN = ITSEuVehicleCategoryN_n2;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[1].choice = ITSVehicleCharacteristicsFixValues_euVehicleCategoryCode;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[1].u.euVehicleCategoryCode.choice = ITSEuVehicleCategoryCode_euVehicleCategoryN;
        pGIC->vehicleCharacteristics.tab[0].train.equalTo.tab[1].u.euVehicleCategoryCode.u.euVehicleCategoryN = ITSEuVehicleCategoryN_n3;
        pGIC->vehicleCharacteristics.tab[0].train.ranges_option = true;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.count = 1;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab = (ITSVehicleCharacteristicsRanges *)asn1_mallocz(pGIC->vehicleCharacteristics.tab[0].train.ranges.count * sizeof(ITSVehicleCharacteristicsRanges));
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab[0].comparisonOperator = ITSComparisonOperator_greaterThan;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab[0].limits.choice = ITSVehicleCharacteristicsRanges_1_vehicleWeightLimits;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab[0].limits.u.vehicleWeightLimits.vehicleMaxLadenWeight = 0;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab[0].limits.u.vehicleWeightLimits.vehicleTrainMaximumWeight = 750;
        pGIC->vehicleCharacteristics.tab[0].train.ranges.tab[0].limits.u.vehicleWeightLimits.vehicleWeightUnladen = 0;

        pGIC->roadSignCodes.count = 1;
        pGIC->roadSignCodes.tab = (ITSRSCode *)asn1_mallocz(pGIC->roadSignCodes.count * sizeof(ITSRSCode));
        pGIC->roadSignCodes.tab[0].layoutComponentId_option = false;
        pGIC->roadSignCodes.tab[0].code.choice = ITSRSCode_1_iso14823;
        pGIC->roadSignCodes.tab[0].code.u.iso14823.pictogramCode.countryCode_option = false;
        pGIC->roadSignCodes.tab[0].code.u.iso14823.pictogramCode.serviceCategoryCode.choice = ITSISO14823Code_4_trafficSignPictogram;
        pGIC->roadSignCodes.tab[0].code.u.iso14823.pictogramCode.serviceCategoryCode.u.trafficSignPictogram = ITSISO14823Code_1_regulatory;
        pGIC->roadSignCodes.tab[0].code.u.iso14823.pictogramCode.pictogramCategoryCode.nature = 5;
        pGIC->roadSignCodes.tab[0].code.u.iso14823.pictogramCode.pictogramCategoryCode.serialNumber = 44; // no overtaking
      }

      if (pParams->GICPart[GicPart].NumExtraText)
      {
        pGIC->extraText_option = true;
        pGIC->extraText.count = pParams->GICPart[GicPart].NumExtraText;
        pGIC->extraText.tab = (ITSText *)asn1_mallocz(pGIC->extraText.count * sizeof(ITSText));
        for (Ix = 0; Ix < pGIC->extraText.count; Ix++)
        {
          if (pParams->GICPart[GicPart].ExtraText[Ix].LayoutComponentId > 0)
          {
            pGIC->extraText.tab[Ix].layoutComponentId_option = true;
            pGIC->extraText.tab[Ix].layoutComponentId = pParams->GICPart[GicPart].ExtraText[Ix].LayoutComponentId;
          }
          pGIC->extraText.tab[Ix].language.len = 10;
          pGIC->extraText.tab[Ix].language.buf = (uint8_t *)asn1_mallocz((pGIC->extraText.tab[Ix].language.len + 7) / 8);
          pGIC->extraText.tab[Ix].language.buf[0] = pParams->GICPart[GicPart].ExtraText[Ix].LanguageBitStr[0];
          pGIC->extraText.tab[Ix].language.buf[1] = pParams->GICPart[GicPart].ExtraText[Ix].LanguageBitStr[1];
          pGIC->extraText.tab[Ix].textContent.buf = (uint8_t *)strdup(pParams->GICPart[GicPart].ExtraText[Ix].TextContent);
          pGIC->extraText.tab[Ix].textContent.len = strlen((const char *)pGIC->extraText.tab[Ix].textContent.buf)+1;
        }
      }
    }

    // Additional optional containers
    int NextContainer = 2;

    if (pParams->RCCPartsCount > 0)
    {
      // text container included in config
      pIVI->optional.tab[NextContainer].choice = ITSIviContainer_rcc;
      pIVI->optional.tab[NextContainer].u.rcc.count = pParams->RCCPartsCount;
      pIVI->optional.tab[NextContainer].u.rcc.tab = (ITSRccPart *)asn1_mallocz(pIVI->optional.tab[NextContainer].u.rcc.count * sizeof(ITSRccPart));
      size_t RccPart = 0;
      for (RccPart = 0; RccPart < pIVI->optional.tab[NextContainer].u.rcc.count; RccPart++)
      {
        ITSRccPart *pRCC = &pIVI->optional.tab[NextContainer].u.rcc.tab[RccPart];

        if (pParams->RCCPart[RccPart].NumRelZones)
        {
          pRCC->relevanceZoneIds.count = pParams->RCCPart[RccPart].NumRelZones;
          pRCC->relevanceZoneIds.tab = (ITSZid *)asn1_mallocz(pRCC->relevanceZoneIds.count * sizeof(ITSZid));
          size_t Zone;
          for (Zone = 0; Zone < pRCC->relevanceZoneIds.count; Zone++)
          {
            pRCC->relevanceZoneIds.tab[Zone] = pParams->RCCPart[RccPart].RelZones[Zone];
          }
        }

        pRCC->roadType = pParams->RCCPart[RccPart].RoadType;

        pRCC->laneConfiguration.count = pParams->RCCPart[RccPart].NumLaneConf;

        pRCC->laneConfiguration.tab = (ITSLaneInformation *)asn1_mallocz(pRCC->laneConfiguration.count * sizeof(ITSLaneInformation));
        size_t Ix;
        for (Ix = 0; Ix < pRCC->laneConfiguration.count; Ix++)
        {
          pRCC->laneConfiguration.tab[Ix].laneNumber = pParams->RCCPart[RccPart].LaneInfoNumbers[Ix];
          pRCC->laneConfiguration.tab[Ix].direction = pParams->RCCPart[RccPart].LaneInfoDirs[Ix];
        }
      }

      NextContainer++;
    }

    if (pParams->TCPartsCount > 0)
    {
      // text container included in config
      pIVI->optional.tab[NextContainer].choice = ITSIviContainer_tc;
      pIVI->optional.tab[NextContainer].u.tc.count = pParams->TCPartsCount;
      pIVI->optional.tab[NextContainer].u.tc.tab = (ITSTcPart *)asn1_mallocz(pIVI->optional.tab[NextContainer].u.tc.count * sizeof(ITSTcPart));
      size_t TcPart = 0;
      for (TcPart = 0; TcPart < pIVI->optional.tab[NextContainer].u.tc.count; TcPart++)
      {
        ITSTcPart *pTC = &pIVI->optional.tab[NextContainer].u.tc.tab[TcPart];

        pTC->detectionZoneIds_option = true;
        pTC->detectionZoneIds.count = 1;
        pTC->detectionZoneIds.tab = (ITSZid *)asn1_mallocz(pTC->detectionZoneIds.count * sizeof(ITSZid));
        pTC->detectionZoneIds.tab[0] = 1;
        pTC->relevanceZoneIds.count = 1;
        pTC->relevanceZoneIds.tab = (ITSZid *)asn1_mallocz(pTC->relevanceZoneIds.count * sizeof(ITSZid));
        pTC->relevanceZoneIds.tab[0] = 2;
        pTC->direction_option = true;
        pTC->direction = ITSDirection_sameDirection;
        pTC->driverAwarenessZoneIds_option = false;
        pTC->minimumAwarenessTime_option = true;
        pTC->minimumAwarenessTime = pParams->TCPart[TcPart].MinimumAwarenessTime;
        // N.B. applicableLanes out of scope
        // N.B. layoutId, preStoredlayoutId out of scope
        if (pParams->TCPart[TcPart].NumText)
        {
          size_t Ix;
          pTC->text_option = true;
          pTC->text.count = pParams->TCPart[TcPart].NumText;
          pTC->text.tab = (ITSText *)asn1_mallocz(pTC->text.count * sizeof(ITSText));
          for (Ix = 0; Ix < pTC->text.count; Ix++)
          {
            if (pParams->TCPart[TcPart].Text[Ix].LayoutComponentId > 0)
            {
              pTC->text.tab[Ix].layoutComponentId_option = true;
              pTC->text.tab[Ix].layoutComponentId = pParams->TCPart[TcPart].Text[Ix].LayoutComponentId;
            }
            pTC->text.tab[Ix].language.len = 10;
            pTC->text.tab[Ix].language.buf = (uint8_t *)asn1_mallocz((pTC->text.tab[Ix].language.len + 7) / 8);
            pTC->text.tab[Ix].language.buf[0] = pParams->TCPart[TcPart].Text[Ix].LanguageBitStr[0];
            pTC->text.tab[Ix].language.buf[1] = pParams->TCPart[TcPart].Text[Ix].LanguageBitStr[1];
            pTC->text.tab[Ix].textContent.buf = (uint8_t *)strdup(pParams->TCPart[TcPart].Text[Ix].TextContent);
            pTC->text.tab[Ix].textContent.len = strlen((const char *)pTC->text.tab[Ix].textContent.buf)+1;
          }
        }
      }
    }

    // Management
    pMgmt->RepetitionDuration = 86400; // all day
    pMgmt->RepetitionInterval = 1000; // 1Hz
    pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare IVI message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise CPM. CPM details obtained from config file
 * @param pParams pointer to CPM config params
 * @return pointer to allocated CPM PDU, and NULL if failed
 *
 */
static void ITSTx_PrepareCpm(const tITSTxCPMParams *pParams, tCPMMgmt *pMgmt, ITSCollectivePerceptionMessage *pCpm)
{
  if (pParams && pMgmt && pCpm)
  {
    pCpm->cpmParameters.sensorInformationContainer_option = true;
    pCpm->cpmParameters.sensorInformationContainer.count = 1;
    pCpm->cpmParameters.sensorInformationContainer.tab =
      (ITSSensorInformation *)asn1_mallocz(pCpm->cpmParameters.sensorInformationContainer.count * sizeof(ITSSensorInformation));
    pCpm->cpmParameters.sensorInformationContainer.tab[0].sensorID = 0x12;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].type = ITSSensorType_radar;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.choice = ITSDetectionArea_vehicleSensor;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.refPointId = 1;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.xSensorOffset = -2;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.ySensorOffset = 3;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.count = 1;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.tab =
      (ITSVehicleSensorProperties *)asn1_mallocz(pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.count * sizeof(ITSVehicleSensorProperties));
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.tab[0].range = 22;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.tab[0].horizontalOpeningAngleStart = 33;
    pCpm->cpmParameters.sensorInformationContainer.tab[0].detectionArea.u.vehicleSensor.vehicleSensorPropertyList.tab[0].horizontalOpeningAngleEnd = 44;

    pCpm->cpmParameters.perceivedObjectContainer_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.count = 1;
    pCpm->cpmParameters.perceivedObjectContainer.tab =
      (ITSPerceivedObject *)asn1_mallocz(pCpm->cpmParameters.perceivedObjectContainer.count * sizeof(ITSPerceivedObject));
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].objectID = 0x12;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].timeOfMeasurement = 0;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].objectConfidence = ITSObjectConfidence_unavailable;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].xDistance.value = 3200;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].xDistance.confidence = ITSDistanceConfidence_oneMeter;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].yDistance.value = 4300;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].xSpeed.value = 500;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].xSpeed.confidence = ITSSpeedConfidence_equalOrWithinOneMeterPerSec;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].ySpeed.value = 40;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].ySpeed.confidence = ITSSpeedConfidence_equalOrWithinOneMeterPerSec;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension1_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension1.value = 55;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension1.confidence = ITSObjectDimensionConfidence_zeroPointZeroOneMeter;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension2_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension2.value = 22;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].planarObjectDimension2.confidence = ITSObjectDimensionConfidence_zeroPointZeroOneMeter;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].objectRefPoint = ITSObjectRefPoint_mid;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.count = 1;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.tab =
      (ITSObjectClass *)asn1_mallocz(pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.count * sizeof(ITSObjectClass));
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.tab[0].confidence = ITSClassConfidence_oneHundredPercent;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.tab[0].Class.choice = ITSObjectClass_1_vehicle;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.tab[0].Class.u.vehicle.type = ITSVehicleSubclassType_passengerCar;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].classification.tab[0].Class.u.vehicle.confidence = ITSClassConfidence_oneHundredPercent;

    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition.laneID_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition.laneID = 2;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition.longitudinalLanePosition_option = true;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition.longitudinalLanePosition.longitudinalLanePositionValue = 450;
    pCpm->cpmParameters.perceivedObjectContainer.tab[0].matchedPosition.longitudinalLanePosition.longitudinalLanePositionConfidence = ITSLongitudinalLanePositionConfidence_oneMeter;

    pCpm->cpmParameters.stationDataContainer_option = false;
    pCpm->cpmParameters.freeSpaceAddendumContainer_option = false;

    pCpm->cpmParameters.numberOfPerceivedObjects = 1;

    // Management
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP2;
    // In some implementations CPM sent on SCH1, again with traffic class 2
    // pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP10;
    pMgmt->AutoPopulateMgmtContainer = true;
    pMgmt->AutoPopulateStationDataContainer = true;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare CPM message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise VAM. VAM details obtained from config file
 * @param pParams pointer to VAM config params
 * @return pointer to allocated VAM PDU, and NULL if failed
 *
 */
static void ITSTx_PrepareVam(const tITSTxVAMParams *pParams, tVAMMgmt *pMgmt, ITSVruAwareness *pVam)
{
  if (pParams && pMgmt && pVam)
  {
    // Management
    pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
    pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP2;

    pMgmt->PopulateDyanmicProperties = true;
    pMgmt->PopulatePastLocations = true;

    // Even though PopulateDyanmicProperties is set, the
    // vruHighFrequencyContainer must still be valid for constraint check
    pVam->vamParameters.vruHighFrequencyContainer.heading.headingConfidence = ITSHeadingConfidence_unavailable;
    pVam->vamParameters.vruHighFrequencyContainer.speed.speedConfidence = ITSSpeedConfidence_unavailable;
    pVam->vamParameters.vruHighFrequencyContainer.longitudinalAcceleration.longitudinalAccelerationConfidence = ITSAccelerationConfidence_unavailable;
  }
  else
  {
    d_printf(D_WARN, NULL, "Failed to prepare VAM message. No transmission!\n");
  }
}

/**
 * @brief Allocate and initialise IVI. IVI details obtained from config file
 * @param pITS pointer to ITS handle
 * @return pointer to allocated IVI PDU, and NULL if failed
 *
 */
static void ITSTx_TerminateIvi(const tITSTxIVSParams *pParams, tIVIMgmt *pMgmt, ITSIviStructure *pIVI)
{
  if (pIVI)
  {
    d_assert(pParams);
    // pIVI->mandatory...
    pIVI->mandatory.serviceProviderId.providerIdentifier = pParams->ServiceProviderIssuerId;
    pIVI->mandatory.iviIdentificationNumber = pParams->IviIdentificationNumber;
    pIVI->mandatory.connectedIviStructures_option = false;
    pIVI->mandatory.iviStatus = ITSIviStatus_cancellation;
  }

  // Management
  d_assert(pMgmt);
  pMgmt->RepetitionDuration = 1; // 1 sec
  pMgmt->RepetitionInterval = 500; // 2Hz
  pMgmt->PktTransport = ETSIFAC_GN_TRANSPORT_SHB;
  pMgmt->CommsProfile = ETSIFAC_GN_PROFILE_DEFAULT;
  pMgmt->TrafficClass = ETSIFAC_GN_TC_ITS_DP3;
}


/**
 * @brief Update state time to change to pre-defined SPAT message and return it
 * @param pITS pointer to user parameters
 * @param pSpat pointer to SPAT that we need to loop and update change time
 */
static void ITSTx_UpdateSpatTiming(const tITSTxSPATParams *pParams,
                                   ITSSPAT *pSpat)
{
  d_fnstart(D_INTERN, NULL, "(%p,%p)\n", pParams, pSpat);
  // For any incorrect parameter, return without updating SPAT message
  if ((!pSpat) || (!pParams))
  {
    d_fnend(D_WARN, NULL, "(%p,%p): NULL\n", pParams, pSpat);
    return;
  }

  // prepare to iterate through all the intersections
  ITSIntersectionStateList * pITSIntersectionStateList = &pSpat->intersections;

  // unless there aren't any :-)
  if(pITSIntersectionStateList->count < 1)
  {
    d_fnend(D_INFO, NULL, "(%p,%p): No intersections\n", pParams, pSpat);
    return;
  }

  // note that ITSTx_PrepareSpat currently hard-codes exactly one intersection,
  // i.e. this SPAT contains data for one MAP
  size_t i;
  for(i = 0; i < pITSIntersectionStateList->count; ++i)
  {
    ITSIntersectionState * pIntersection = &(pITSIntersectionStateList->tab[i]);
    ITSMovementList      * pITSMovementList = &pIntersection->states;

    // iterate through all the movements of each intersection (6 in the example)
    size_t j;
    for (j = 0; j < pITSMovementList->count; ++j)
    {
      const tSPATMovementParams * pSPATMovementParams = &pParams->pMovements[j];
      ITSMovementState *pITSMovementState = &pITSMovementList->tab[j];
      ITSMovementEventList * pITSMovementEventList = &pITSMovementState->state_time_speed;

      // iterate through each element of each movement
      size_t k;
      for (k = 0; k < pITSMovementEventList->count; ++k)
      {
        ITSMovementEvent *pITSMovementEvent = &(pITSMovementEventList->tab[k]);
        ITSTimeMark      *pEndTime          = &(pITSMovementEvent->timing.minEndTime);
        ITSMovementPhaseState *pPhase       = &(pITSMovementEvent->eventState);

        // Calculate current time in TimeMark format. TimeMark is defined as offset
        // to the UTC full hour with a resolution of 36000 in units of 1/10th second
        int NowTimeMark = (Util_Now() / ((int64_t)100)) % 36000;

        // if we're not doing dynamic phase then simply slip the change time
        // (this gives the effect of an infinite phase)
        if(!pParams->DynamicPhases)
        {
          (*pEndTime) = (pSPATMovementParams->TimeToChange + NowTimeMark) % 36000;
          d_printf(D_INFO, NULL, "Infinite phase time at %d, [%zd][%zd][%zd]: {%d,%d} (slip)\n",
                   NowTimeMark,
                   i,j,k, *pPhase, *pEndTime);
          continue;
        }

        // how far into the future is the next change?
        int Diff = *pEndTime - NowTimeMark;

        // if TempDiff is negative then we're over-due for a phase change. However,
        // if we seem to have missed by more than half an hour assume we've had a wrap-around
        bool PhaseChangeDue = (Diff < 0) && (Diff > -18000);
        if (!PhaseChangeDue)
        {
          d_printf(D_INFO, NULL, "Adapt phase time at %d, [%zd][%zd][%zd]: still {%d,%d} (next change in %d)\n",
                   NowTimeMark,
                   i,j,k, *pPhase, *pEndTime, Diff);
          continue;
        }
        // if we're currently "red" then the next change is to "green"
        bool ChangeToGreen = (((*pPhase) == ITSMovementPhaseState_stop_And_Remain) ||
                              ((*pPhase) == ITSMovementPhaseState_stop_Then_Proceed) ||
                              ((*pPhase) == ITSMovementPhaseState_pre_Movement));
        // if we're not changing to green we might already be "green" and changing to "yellow"
        bool ChangeToYellow = !ChangeToGreen &&
          (((*pPhase) == ITSMovementPhaseState_protected_Movement_Allowed) ||
           ((*pPhase) == ITSMovementPhaseState_permissive_Movement_Allowed));

        // if we're changing to green ...
        if(ChangeToGreen)
        {
          // then advance the phase and update the end time
          (*pPhase)    = ITSMovementPhaseState_protected_Movement_Allowed;
          (*pEndTime) += pParams->GreenPhasePeriod;
        }
        // SSDD, see above
        else if(ChangeToYellow)
        {
          (*pPhase)    = ITSMovementPhaseState_protected_clearance;
          (*pEndTime) += pParams->YellowPhasePeriod;
        }
        // not changing to green or yellow, must be potentially changing to red
        else
        {
          // Change from (hopefully) YLW to RED state:
          (*pPhase)    = ITSMovementPhaseState_stop_And_Remain;
          (*pEndTime) += pParams->RedPhasePeriod;
        }
        // wrap the end time
        (*pEndTime) %= 36000;
        d_printf(D_INFO, NULL, "Change phase at %d, [%zd][%zd][%zd]: %d: -> {%d,%d}\n",
                 NowTimeMark,
                 i,j,k,Diff, *pPhase, *pEndTime);
      }
    }
  }
  d_fnend(D_INTERN, NULL, "(%p,%p)\n", pParams, pSpat);
}
// Close the doxygen group
/**
 * @}
 */
