#pragma once

/**
 * @addtogroup TC_ETSI Helper module to process ETSI-ASN encoded messages
 * @{
 *
 * This module is used to convert received ETSI-ASN encoded data into
 * tTCRemote's for threat management.
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __TC_ETSI_H_
#define __TC_ETSI_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "TC.h"
#include "TC_Err.h"

#include "ASNCommon.h"

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

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

tTC_ErrCode TC_RegisterETSI(void);

tTC_ErrCode TC_DecodeETSIEventHist(tTCCrumb *pCrumbs,
                                   const ITSEventHistory *pITSEventHistory);

tTC_ErrCode TC_DecodeETSIPathHist(tTCRemote *pRemote,
                                  const ITSPathHistory *pITSPathHistory,
                                  uint8_t MatchMode);


tTC_ErrCode TC_ConvertETSIEventHist(tTCRemote *pRemote,
                                    const ITSReferencePosition *pRefPos,
                                    const ITSEventHistory *pEventHistory);

uint64_t TC_GetCorrespondingCAMID(uint64_t DENMID);

ITSStationID TC_GetCorrespondingStationID(uint64_t ID);

#ifdef __cplusplus
}
#endif

#endif //  __TC_ETSI_H_

// Close the doxygen group
/**
 * @}
 */
