/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_wdid What Does It Do
 * ASN.1 BER encoding and decoding of J2735 messages - common
 *
 * @section v2v_j2735_api_hdwui How Do We Use It
 * This module can be used directly via function calls to encode or decode
 * J2735 messages. These Functions return immediately.
 *
 * This module is used indirectly via the EXT module
 * when the decoded version of a received message is requested.
 * See the EXT module for further details.
 *
 * Commonly used functions are
 * - @ref J2735_MsgInspect
 * - @ref J2735_MsgDecode
 * - @ref J2735_MsgFree
 * - @ref J2735_MsgPERDecode
 * - @ref J2735_MsgXERDecode
 * - @ref J2735_MsgXEREncode
 *
 * @section v2v_j2735_api_bsm BSM Description
 * ASN.1 BER encoding and decoding of the J2735 basic safety messages.
 *
 * @file J2735_BSM.h J2735 Interface to the J2735 Basic Safety Message Library.
 *
 * @section v2v_j2735_desc BSM
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 * <Detailed information about this file's functionality goes here>
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_BSM_H_
#define __J2735_BSM_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

// Don't rely on the include hierarchy as that creates portability issues.
// If your code below uses a type definition: explicitly include the header that
// defines that type
#include "debug-levels.h"

#include <j2735asn.h>
#include <j2735asn_def.h>
#include "j2735-vehicle-status.h"
#include "j2735-vehicle-safetyextension.h"

#include <stdbool.h>

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

/// Error codes
typedef enum
{
  J2735_BSM_ERR_NONE       = 0,
  J2735_BSM_ERR_MALLOC,
  J2735_BSM_ERR_INVALID,
} tJ2735BSMErrorCode;

/// Lights values
typedef enum
{
//  J2735_BSM_ALLLIGHTSOFF            = SAEExteriorLights_allLightsOff, // from j2735asn.h
  J2735_BSM_LOWBEAMHEADLIGHTSON     = SAEExteriorLights_lowBeamHeadlightsOn,
  J2735_BSM_HIGHBEAMHEADLIGHTSON    = SAEExteriorLights_highBeamHeadlightsOn,
  J2735_BSM_LEFTTURNSIGNALON        = SAEExteriorLights_leftTurnSignalOn,
  J2735_BSM_RIGHTTURNSIGNALON       = SAEExteriorLights_rightTurnSignalOn,
  J2735_BSM_HAZARDSIGNALON          = SAEExteriorLights_hazardSignalOn,
  J2735_BSM_AUTOMATICLIGHTCONTROLON = SAEExteriorLights_automaticLightControlOn,
  J2735_BSM_DAYTIMERUNNINGLIGHTSON  = SAEExteriorLights_daytimeRunningLightsOn,
  J2735_BSM_FOGLIGHTON              = SAEExteriorLights_fogLightOn,
  J2735_BSM_PARKINGLIGHTSON         = SAEExteriorLights_parkingLightsOn,
} tExteriorLights;

/// Event codes
typedef enum
{
//  J2735_BSM_EVENT_NONE                      = SAEEventFlags_eventNone, // from j2735asn.h
  J2735_BSM_EVENT_HazardLights              = SAEVehicleEventFlags_eventHazardLights,
  J2735_BSM_EVENT_StopLineViolation         = SAEVehicleEventFlags_eventStopLineViolation,
  J2735_BSM_EVENT_ABSactivated              = SAEVehicleEventFlags_eventABSactivated,
  J2735_BSM_EVENT_TractionControlLoss       = SAEVehicleEventFlags_eventTractionControlLoss,
  J2735_BSM_EVENT_StabilityControlactivated = SAEVehicleEventFlags_eventStabilityControlactivated,
  J2735_BSM_EVENT_HazardousMaterials        = SAEVehicleEventFlags_eventHazardousMaterials,
  // "EmergencyResponse" changed to "Reserved1"
//  J2735_BSM_EVENT_EmergencyResponse         = SAEVehicleEventFlags_eventEmergencyResponse,
  J2735_BSM_EVENT_Reserved1                 = SAEVehicleEventFlags_eventReserved1,
  J2735_BSM_EVENT_HardBraking               = SAEVehicleEventFlags_eventHardBraking,
  J2735_BSM_EVENT_LightsChanged             = SAEVehicleEventFlags_eventLightsChanged,
  J2735_BSM_EVENT_WipersChanged             = SAEVehicleEventFlags_eventWipersChanged,
  J2735_BSM_EVENT_FlatTire                  = SAEVehicleEventFlags_eventFlatTire,
  J2735_BSM_EVENT_DisabledVehicle           = SAEVehicleEventFlags_eventDisabledVehicle,
  J2735_BSM_EVENT_AirBagDeployment          = SAEVehicleEventFlags_eventAirBagDeployment,
} tEventFlags;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// There are no doxygen comments for the functions below. They're in the .c
// files (to hopefully keep the implementation and the description in sync)

int J2735_BSMEncode(const SAEBasicSafetyMessage *pBSM, const char *pFilename);
int J2735_BSMEncode_To_Buffer(const SAEBasicSafetyMessage *pBSM,
                              int HeaderSize, uint8_t **ppBuf);
int J2735_BSMDecode(SAEBasicSafetyMessage **ppBSM,
                    const char *pBuf, size_t Size);
bool J2735_DecodeBSMLocation(const uint8_t * pData,
                             size_t Len,
                             int * pLatitude,
                             int * pLongitude,
                             int * pElevation);

void J2735_BSMFree(SAEBasicSafetyMessage *pBSM);

// create a reusable template to be used with J2735_BSMEncode_To_Buffer
int J2735_BSMCreateTemplate(SAEBasicSafetyMessage **ppBSM,
                            int MaxPH,
                            SAEBasicVehicleRole Role,
                            SAEBasicVehicleClass Class);
void J2735_BSMFreeTemplate(SAEBasicSafetyMessage    *pBSM);


// R/O access to innards of a BSM
/**
 * @brief Extract the requested parts from a BSM
 *
 * @param pBsm BSM to extract from
 * @param ppSAEVehicleSafetyExtensions Where to store pointer to VSE (or NULL if VSE not needed)
 * @param ppSAESpecialVehicleExtensions  Where to store pointer to SVE (or NULL if SVE not needed)
 * @param ppSAESupplementalVehicleExtensions  Where to store pointer to SVE (or NULL if SVE not needed)
 */
static inline void P1609_PeekExtensions(const SAEBasicSafetyMessage *pBsm,
                                        const SAEVehicleSafetyExtensions       ** ppSAEVehicleSafetyExtensions,
                                        const SAESpecialVehicleExtensions      ** ppSAESpecialVehicleExtensions,
                                        const SAESupplementalVehicleExtensions ** ppSAESupplementalVehicleExtensions)
{
  d_fnstart(D_INTERN, NULL, "(%p %p %p %p)\n",
            pBsm,
            ppSAEVehicleSafetyExtensions, ppSAESpecialVehicleExtensions,
            ppSAESupplementalVehicleExtensions);

  // clear the pointers (if provided)
  if (ppSAEVehicleSafetyExtensions != NULL)
  {
    *ppSAEVehicleSafetyExtensions = NULL;
  }
  if (ppSAESpecialVehicleExtensions != NULL)
  {
    *ppSAESpecialVehicleExtensions = NULL;
  }
  if (ppSAESupplementalVehicleExtensions != NULL)
  {
    *ppSAESupplementalVehicleExtensions = NULL;
  }

  // sanity check
  if (pBsm == NULL)
  {
    d_fnend(D_INTERN, NULL, "(%p): NULL\n", pBsm);
    return;
  }
  if (pBsm->partII_option == false)
  {
    d_fnend(D_INTERN, NULL, "(%p): No partII\n", pBsm);
    return;
  }

  size_t Idx = 0;
  for (; Idx < pBsm->partII.count; ++Idx)
  {
    // if we have found everything we're looking for then we're done!
    if ((ppSAEVehicleSafetyExtensions == NULL)
        &&
        (ppSAESpecialVehicleExtensions == NULL)
        &&
        (ppSAESupplementalVehicleExtensions == NULL))
    {
      break;
    }

    d_assert(pBsm->partII.tab != NULL);
    const SAEPartIIcontent_1 *pSAEPartIIcontent_1 = &(pBsm->partII.tab[Idx]);
    switch (pSAEPartIIcontent_1->partII_Id)
    {
      // Is it a SAEVehicleSafetyExtensions?
      case SAEPartII_Id_vehicleSafetyExt:
        {
          // Are we interested in SAEVehicleSafetyExtensions?
          if (ppSAEVehicleSafetyExtensions == NULL)
          {
            continue;
          }
          const ASN1OpenType *pValue = &(pSAEPartIIcontent_1->partII_Value);
          d_assert(pValue);
          // I'd love to d_assert(pValue->type == asn1_type_SAEVehicleSafetyExtensions) but that breaks linking
          *ppSAEVehicleSafetyExtensions = (const SAEVehicleSafetyExtensions*)(pValue->u.data);
          d_assert(*ppSAEVehicleSafetyExtensions);
          // not looking for "SAEVehicleSafetyExtensions" any more
          ppSAEVehicleSafetyExtensions = NULL;
        }
        break;

      case SAEPartII_Id_specialVehicleExt:
        {
          if (ppSAESpecialVehicleExtensions == NULL)
          {
            continue;
          }
          const ASN1OpenType *pValue = &(pSAEPartIIcontent_1->partII_Value);
          d_assert(pValue);
          *ppSAESpecialVehicleExtensions = (const SAESpecialVehicleExtensions*)(pValue->u.data);
          d_assert(*ppSAESpecialVehicleExtensions);
          ppSAESpecialVehicleExtensions = NULL;
        }
        break;

      case SAEPartII_Id_supplementalVehicleExt:
        {
          if (ppSAESupplementalVehicleExtensions == NULL) continue;
          const ASN1OpenType *pValue = &(pSAEPartIIcontent_1->partII_Value);
          d_assert(pValue);
          *ppSAESupplementalVehicleExtensions = (const SAESupplementalVehicleExtensions*)(pValue->u.data);
          d_assert(*ppSAESupplementalVehicleExtensions);
          ppSAESupplementalVehicleExtensions = NULL;
        }
        break;

      default:
        {
          // unsupported extension, ignore it
        }
        break;
    }
  }

  d_fnend(D_INTERN, NULL, "(%p %p{%p} %p{%p} %p{%p})\n",
            pBsm,
            ppSAEVehicleSafetyExtensions,
            ppSAEVehicleSafetyExtensions ? *ppSAEVehicleSafetyExtensions : NULL,
            ppSAESpecialVehicleExtensions,
            ppSAESpecialVehicleExtensions ? *ppSAESpecialVehicleExtensions : NULL,
            ppSAESupplementalVehicleExtensions,
            ppSAESupplementalVehicleExtensions? *ppSAESupplementalVehicleExtensions : NULL);

}

/**
 * @brief Peek at the SAEVehicleSafetyExtensions in a BSM
 *
 * @param pBsm BSM to examine
 *
 * @return Pointer to SAEVehicleSafetyExtensions, or NULL if unavailable.
 */
static inline const SAEVehicleSafetyExtensions *P1609_PeekSAEVehicleSafetyExtensions(const SAEBasicSafetyMessage *pBsm)
{
  const SAEVehicleSafetyExtensions * pSAEVehicleSafetyExtensions = NULL;
  P1609_PeekExtensions(pBsm, &pSAEVehicleSafetyExtensions, NULL, NULL);
  return pSAEVehicleSafetyExtensions;
}

/**
 * @brief Peek at the SAESpecialVehicleExtensions in a BSM
 *
 * @param pBsm BSM to examine
 *
 * @return Pointer to SAESpecialVehicleExtensions, or NULL if unavailable.
 */
static inline const SAESpecialVehicleExtensions *P1609_PeekSAESpecialVehicleExtensions(const SAEBasicSafetyMessage *pBsm)
{
  const SAESpecialVehicleExtensions * pSAESpecialVehicleExtensions = NULL;
  P1609_PeekExtensions(pBsm, NULL, &pSAESpecialVehicleExtensions, NULL);
  return pSAESpecialVehicleExtensions;
}

static inline const SAEPathHistory * P1609_PeekSAEPathHistory(const SAEBasicSafetyMessage *pBsm)
{
  d_fnstart(D_INTERN, NULL, "(%p)\n", pBsm);
  const SAEVehicleSafetyExtensions * pSAEVehicleSafetyExtensions = P1609_PeekSAEVehicleSafetyExtensions(pBsm);
  if (pSAEVehicleSafetyExtensions == NULL)
  {
    d_fnstart(D_INTERN, NULL, "(%p): No SAEVehicleSafetyExtensions\n", pBsm);
    return NULL;
  }
  if (pSAEVehicleSafetyExtensions->pathHistory_option == false)
  {
    d_fnend(D_INTERN, NULL, "(%p): No PH\n", pBsm);
    return NULL;
  }
  d_fnend(D_INTERN, NULL, "(%p): %p\n", pBsm, &(pSAEVehicleSafetyExtensions->pathHistory));
  return &(pSAEVehicleSafetyExtensions->pathHistory);
}

static inline const SAEPathPrediction * P1609_PeekSAEPathPrediction(const SAEBasicSafetyMessage *pBsm)
{
  d_fnstart(D_INTERN, NULL, "(%p)\n", pBsm);
  const SAEVehicleSafetyExtensions *pSAEVehicleSafetyExtensions = P1609_PeekSAEVehicleSafetyExtensions(pBsm);
  if (pSAEVehicleSafetyExtensions == NULL)
  {
    d_fnstart(D_INTERN, NULL, "(%p): No SAEVehicleSafetyExtensions\n", pBsm);
    return NULL;
  }
  if (pSAEVehicleSafetyExtensions->pathPrediction_option == false)
  {
    d_fnend(D_INTERN, NULL, "(%p): No PP\n", pBsm);
    return NULL;
  }
  d_fnend(D_INTERN, NULL, "(%p): %p\n", pBsm, &(pSAEVehicleSafetyExtensions->pathPrediction));
  return &(pSAEVehicleSafetyExtensions->pathPrediction);
}

static inline const SAEVehicleEventFlags * P1609_PeekVehicleEvents(const SAEBasicSafetyMessage *pBsm)
{
  d_fnstart(D_INTERN, NULL, "(%p)\n", pBsm);
  const SAEVehicleSafetyExtensions *pSAEVehicleSafetyExtensions = P1609_PeekSAEVehicleSafetyExtensions(pBsm);
  if (pSAEVehicleSafetyExtensions == NULL)
  {
    d_fnstart(D_INTERN, NULL, "(%p): No SAEVehicleSafetyExtensions\n", pBsm);
    return NULL;
  }
  if (pSAEVehicleSafetyExtensions->events_option == false)
  {
    d_fnend(D_INTERN, NULL, "(%p): No EV\n", pBsm);
    return NULL;
  }
  d_fnend(D_INTERN, NULL, "(%p): %p\n", pBsm, &pSAEVehicleSafetyExtensions->events);
  return &pSAEVehicleSafetyExtensions->events;
}

static inline const SAEExteriorLights * P1609_PeekSAEExteriorLights(const SAEBasicSafetyMessage *pBsm)
{
  d_fnstart(D_INTERN, NULL, "(%p)\n", pBsm);
  const SAEVehicleSafetyExtensions *pSAEVehicleSafetyExtensions = P1609_PeekSAEVehicleSafetyExtensions(pBsm);
  if (!pSAEVehicleSafetyExtensions)
  {
    d_fnstart(D_INTERN, NULL, "(%p): No SAEVehicleSafetyExtensions\n", pBsm);
    return NULL;
  }
  if (!pSAEVehicleSafetyExtensions->lights_option)
  {
    d_fnend(D_INTERN, NULL, "(%p): No LT\n", pBsm);
    return NULL;
  }
  d_fnend(D_INTERN, NULL, "(%p): %p\n", pBsm, &pSAEVehicleSafetyExtensions->lights);
  return &pSAEVehicleSafetyExtensions->lights;
}

// R/W access to innards of a BSM
static inline void P1609_ExtractExtensions(SAEBasicSafetyMessage *pBsm,
                                           SAEVehicleSafetyExtensions       ** ppSAEVehicleSafetyExtensions,
                                           SAESpecialVehicleExtensions      ** ppSAESpecialVehicleExtensions,
                                           SAESupplementalVehicleExtensions ** ppSAESupplementalVehicleExtensions)
{
  // type-cast to remove the "const" from the return type.
  // safe to do as we're passing in a non-const
  P1609_PeekExtensions(pBsm,
                       (const SAEVehicleSafetyExtensions       **) ppSAEVehicleSafetyExtensions,
                       (const SAESpecialVehicleExtensions      **) ppSAESpecialVehicleExtensions,
                       (const SAESupplementalVehicleExtensions **) ppSAESupplementalVehicleExtensions);
}


static inline SAEVehicleSafetyExtensions * P1609_ExtractSAEVehicleSafetyExtensions(SAEBasicSafetyMessage *pBsm)
{
  return (SAEVehicleSafetyExtensions *)P1609_PeekSAEVehicleSafetyExtensions(pBsm);
}
static inline SAESpecialVehicleExtensions * P1609_ExtractSAESpecialVehicleExtensions(SAEBasicSafetyMessage *pBsm)
{
  return (SAESpecialVehicleExtensions *)P1609_PeekSAESpecialVehicleExtensions(pBsm);
}
static inline SAEPathHistory * P1609_ExtractSAEPathHistory(SAEBasicSafetyMessage *pBsm)
{
  return (SAEPathHistory *)P1609_PeekSAEPathHistory(pBsm);
}

static inline SAEPathPrediction * P1609_ExtractSAEPathPrediction(SAEBasicSafetyMessage *pBsm)
{
  return (SAEPathPrediction *)P1609_PeekSAEPathPrediction(pBsm);
}

static inline SAEVehicleEventFlags * P1609_ExtractVehicleEvents(SAEBasicSafetyMessage *pBsm)
{
  return (SAEVehicleEventFlags *)P1609_PeekVehicleEvents(pBsm);
}

static inline SAEExteriorLights * P1609_ExtractSAEExteriorLights(SAEBasicSafetyMessage *pBsm)
{
  return (SAEExteriorLights *)P1609_ExtractSAEExteriorLights(pBsm);
}

#ifdef __cplusplus
}
#endif

#endif // __J2735_BSM_H_
// Close the doxygen group
/**
 * @}
 */
