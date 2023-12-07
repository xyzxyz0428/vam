/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_sd Snapshot Description
 * ASN.1 BER encoding and decoding of J2735 Snapshot.
 *
 * @file j2735-snapshot.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_SNAPSHOT_H_
#define __J2735_SNAPSHOT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

// Don't rely on the include hierarchy as that creates portability issues.
// If your code below uses a type definition: explicitly include the header that
// defines that type
#include "j2735asn.h" /* BasicSafetyMessage ASN.1 type */

#include "j2735-common.h"
#include "j2735-full-position-vector.h"
#include "j2735-vehicle-safetyextension.h"
#include "j2735-vehicle-status.h"

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

/**
 * @brief config for Optional Fields in Snapshot
 *
 * This struct captures all the optional fields in Snapshot. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 *
 * eg. VehicleSafetyExtension must be turned on (1) to
 * allow VehicleSafetyExtension (1) to be functional.
 *
 */

typedef struct SnapshotCfg
{
  // thePosition (SAEFullPositionVector) is mandatory, it has optional members
  tSAEFullPositionVectorCfg PositionConfig;

  unsigned int VehicleSafetyExt:1;
  tVehicleSafetyExtensionConfig VehicleSafetyExtConfig;

  unsigned int VehicleStatus:1;                 // VehicleStatus - supported for acceleration
  tVehicleStatusConfig VehicleStatusConfig;
} tSnapshotCfg;



//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735Snapshot_Create(SAESnapshot **ppSnapshot,
                         const tSnapshotCfg *pConfig);

int J2735Snapshot_Free(SAESnapshot *pSnapshot,
                       tJ2735FreeOption FreeOption);

// Below functions do not get used

#if 0
int J2735Snapshot_EncodeToFile(const SAESnapshot *pSnapshot,
                               const char *pFileName);

int J2735Snapshot_DecodeFromFile(SAESnapshot **ppSnapshot,
                                 const char *pFileName);

int J2735Snapshot_EncodeToFileXML(const SAESnapshot *pSnapshot,
                                  const char *pFileName);

int J2735Snapshot_DecodeFromFileXML(SAESnapshot **ppSnapshot,
                                    const char *pFileName);

#endif

#ifdef __cplusplus
}
#endif

#endif // __J2735_SNAPSHOT_H_
// Close the doxygen group
/**
 * @}
 */
