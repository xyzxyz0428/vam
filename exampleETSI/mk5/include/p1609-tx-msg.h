/**
 * @addtogroup v2x_p1609_tx_api
 * @{
 *
 * @file p1609-tx-msg.h WSM Message
 *
 * P1609-TX for WSM (WAVE Short Message)
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_TX_MSG_H_
#define __P1609_TX_MSG_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

#include "dot3-wsmp.h"

#include "j2735-vehicle-status.h"
#include "j2735-vehicle-safetyextension.h"
#include "gps-rx.h"
#include "vstate.h"
#include "lph.h"

#include "j2735asn.h"
#include "j2735asn_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// PSID used for BSM replay messages
#define REPLAY_BSM_ONLY_PSID 0xDEADBEEE

/// MAC address length in uint8_t
#define WSM_HDR_MAC_LEN 6

/// WSM header expiry time=0, never expire
#define WSM_HDR_DEFAULT_EXPIRY_TIME 0


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------


/**

All BSMs contain the BSM Part I content as specified in SAE J2735 [1]. The System shall include additional BSM
content as follows:

- The System transmitting a BSM shall include the DF_SAEVehicleSafetyExtensions data frame in Part II.
[6.3.1-V2V-BSMTX-BSMCONT-003]

- The DF_SAEVehicleSafetyExtensions data frame shall include:
 - DF_SAEPathHistory
 - DF_SAEPathPrediction
[6.3.1-V2V-BSMTX-BSMCONT-004]

The DF_SAEVehicleSafetyExtensions data frame shall include DE_SAEExteriorLights only if one or more bits in the data element are set.
[6.3.1-V2V-BSMTX-BSMCONT-005]

If one or more event conditions corresponding to an event flag is met, the BSM Part II shall include the DF_SAEVehicleSafetyExtensions data element, DE_SAEVehicleEventFlags. DE_SAEVehicleEventFlags is not included if no event flags are set.
[6.3.1-V2V-BSMTX-BSMCONT-006]

NOTE: Vehicle type (DE_VehicleType) is omitted from BSM Part II for light vehicles. However, it can be inferred for light vehicles as long as all other classes of vehicles include the field in their BSMs as defined in future revisions of this standard, or in other standards in the SAE J2945 family of standards.

 */

/// Sent with Ext event QSMSG_EXT_TX_BSM
typedef struct BSMTxData
{
  const SAEBasicSafetyMessage *pBSM;
  const unsigned char *pBER;
  unsigned int Len;
} tBSMTxData;


typedef enum {
  P1609_TX_ATTACH_DEFAULT = 0,
  P1609_TX_ATTACH_CERTIFICATE = 1,
  P1609_TX_ATTACH_DIGEST = 2,
} eP1609TxCertAttach;

typedef uint8_t tP1609TxCertAttach;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

struct Dot3WSMPHdr *P1609_CreateBSM(const tLPHPos *pLPHPos,
                                    const tVStateState *pVState,
                                    void *pLPH);

int P1609_ConstructSAEFullPositionVector(SAEFullPositionVector *pFPV,
                                         const tLPHPos      *pLPHPos,
                                         const tVStateState *pVState);

int P1609_SetVehicleSafetyExtAvailability_SAEPathHistory(bool FPVEnabled,
                                                         struct VehicleSafetyExtensionConfig *pSafetyExtConf,
                                                         const tVStateState *pVState,
                                                         const tLPHPos *pLPHPos,
                                                         const tLPHPH *pPH);

int P1609_SetVehicleSafetyExtAvailability_SAEPathPrediction(struct VehicleSafetyExtensionConfig *pSafetyExtConf,
                                                            const tVStateState *pVState,
                                                            const tLPHPos *pLPHPos,
                                                            const tLPHPP *pPP);

int P1609_SetVehicleSafetyExtAvailability_Event(struct VehicleSafetyExtensionConfig *pSafetyExtConf,
                                                const tVStateState *pVState);

int P1609_ConstructVehicleSafetyExtension(SAEVehicleSafetyExtensions *pSafetyExt,
                                          const tVStateState *pVState,
                                          const tLPHPos *pLPHPos,
                                          const tLPHPH *pPH,
                                          const tLPHPP *pPP);
int P1609_SetVehicleStatusAvailability(struct VehicleStatusConfig *pStatusConf,
                                       const tVStateState  *pVState,
                                       const tLPHPos *pLPHPos);
int P1609_ConstructVehicleStatus(SAEVehicleStatus *pStatus,
                                 const tLPHPos *pLPHPos,
                                 const tVStateState *pVState);

struct Dot3WSMPHdr *P1609_CreateBSM_Replay(const tLPHPos *pLPHPos,
                                           const tVStateState *pVState,
                                           const tLPHPH *pPH,
                                           const tLPHPP *pPP,
                                           uint8_t MsgCnt,
                                           uint32_t TempID);

// These can be called from V2X-lib clients (RSE, ASD etc.)

void P1609_CreateWSMHeader(struct Dot3WSMPHdr *pHdr,
                           int Len);

void P1609_CreateWSMHeaderPSID(struct Dot3WSMPHdr *pHdr,
                               int Len,
                               uint32_t PSID);

int P1609Tx_SendWSM(const struct Dot3WSMPHdr *pWSM,
                    bool SignMessage,
                    tP1609TxCertAttach CertAttach,
                    int LogFd);

int P1609_SendWSMfromClient(struct Dot3WSMPHdr *pWSM,
                            bool SignMessage,
                            tP1609TxCertAttach CertAttach,
                            int LogFd) __attribute__ ((deprecated));

int P1609_TxSign(uint8_t *pData,
                 size_t Len,
                 uint32_t PSID,
                 uint8_t *SSP,
                 uint32_t SSPLength,
                 tP1609TxCertAttach CertAttach,
                 size_t *pSecureLen,
                 char **ppSecureMsg);

int P1609Tx_SendWSMExtra(const struct Dot3WSMPHdr *pWSM,
                         bool SignMessage,
                         tP1609TxCertAttach CertAttach,
                         const tLPHPos *pLPHPos,
                         int LogFd);

int P1609_SendWSM(struct Dot3WSMPHdr *pWSM,
                  bool SignMessage,
                  tP1609TxCertAttach CertAttach,
                  const tLPHPos *pLPHPos, // only want pLPHPos->Fix.mode!
                  int LogFd) __attribute__ ((deprecated));

int P1609_ReplayUpdateRecMsg(struct Dot3WSMPHdr *pWSM,
                             const tLPHPos *pLPHPos);

int P1609_ReplayUpdateHybridMsg(struct Dot3WSMPHdr **ppWSM,
                                const tLPHPos *pLPHPos,
                                const tVStateState *pVState,
                                void *pLPH);

int P1609_ReplayUpdateUDPRawMsg(struct Dot3WSMPHdr *pWSM);

void P1609TX_SeedRandom(void);

void P1609TX_UpdateTempID(size_t IdLen, uint8_t *pId);

void P1609TX_UpdateMsgCnt(size_t IdLen,
                          uint8_t *pId);

void P1609TX_SetMsgCnt(uint8_t MsgCnt);

uint32_t P1609TX_GetTempID(void);

void P1609TX_SetTempID(uint32_t TempId);

int P1609TX_SendDot2Message(uint32_t PSID,
                            const uint8_t *pData,
                            uint32_t Len);
#ifdef __cplusplus
}
#endif

#endif // __P1609_TX_MSG_H_
// Close the doxygen group
/**
 * @}
 */
