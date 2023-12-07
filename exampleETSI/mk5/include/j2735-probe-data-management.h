/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_pvmd Probe Data Management Description
 * ASN.1 BER encoding and decoding of J2735 Probe Data Management
 *
 *
 * @file j2735-probe-data-management.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R36_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_PROBE_DATA_MANAGEMENT_H_
#define __J2735_PROBE_DATA_MANAGEMENT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

// Don't rely on the include hierarchy as that creates portability issues.
// If your code below uses a type definition: explicitly include the header that
// defines that type

#include "j2735asn.h" // ASN.1 type

#include "j2735-common.h"

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

int J2735ProbeDataManagement_Free(SAEProbeDataManagement *pProbeDataManagement,
                                  tJ2735FreeOption FreeOption);

int J2735ProbeDataManagement_Encode(const SAEProbeDataManagement *pPDM,
                                    uint8_t *pBuf,
                                    int BufSize);

#ifdef __cplusplus
}
#endif

#endif // __J2735_PROBE_DATA_MANAGEMENT_H_
// Close the doxygen group
/**
 * @}
 */
