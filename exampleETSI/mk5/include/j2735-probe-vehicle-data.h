/**
 * @addtogroup v2v_j2735_api
 *
 * @{
 *
 * @section v2v_j2735_api_pvdd Probe Vehicle Data Description
 * ASN.1 BER encoding and decoding of J2735 Probe Vehicle Data.
 *
 *
 * @file j2735-probe-vehicle-data.h J2735 Interface to the J2735 Library.
 *
 * These are based on header and source files generated from DSRC_R70_Source.ASN
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2735_PROBE_VEHICLE_DATA_H_
#define __J2735_PROBE_VEHICLE_DATA_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

// Don't rely on the include hierarchy as that creates portability issues.
// If your code below uses a type definition: explicitly include the header that
// defines that type
#include <j2735asn.h>

#include "j2735-common.h"
#include "j2735-full-position-vector.h"

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
 * @brief config for Optional Fields in Probe Vehicle Data
 *
 * This struct captures all the optional fields in FullPostionVector. This
 * structure is used to turn each optional field on and off.
 *
 * Note:
 * Make sure the upper level member of the structure is turned
 * on before the submember is turned on.
 *
 * eg. DDateTime must be turned on (1) to
 * allow DDateTimeConfig (1) to be functional.
 *
 */

typedef struct ProbeVehicleDataCfg
{
  // msgID is mandatory                  // DSRCmsgID_t (enum)
  unsigned int segNum:1;                 // ProbeSegmentNumber_t * (long *);

  // startVector is mandatory (SAEFullPositionVector_t) & has optional members
  struct SAEFullPositionVectorCfg startVectorConfig;

  // vehicleType is mandatory            // VehicleType_t (enum)
  unsigned int cntSnapshots:1;           // Count_t * (long *)

  // snapshots is mandatory              // struct ProbeVehicleData__snapshots

} tProbeVehicleDataCfg;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int J2735ProbeVehicleData_Create(SAEProbeVehicleData **ppProbeVehicleData,
                                 const tProbeVehicleDataCfg *pConfig);

int J2735ProbeVehicleData_AddSnapshot(SAEProbeVehicleData *pProbeVehicleData,
                                      const SAESnapshot *pSnapshot);

int J2735ProbeVehicleData_Free(SAEProbeVehicleData *pProbeVehicleData,
                               tJ2735FreeOption FreeOption);

int J2735ProbeVehicleData_Encode(const SAEProbeVehicleData *pProbeVehicleData,
                                 uint8_t **ppBuf,
                                 unsigned int HeaderSize);

#ifdef __cplusplus
}
#endif

#endif // __J2735_PROBE_VEHICLE_DATA_H_
// Close the doxygen group
/**
 * @}
 */
