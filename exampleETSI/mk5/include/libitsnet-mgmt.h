/**
 * @addtogroup ets_libitsnet_mgmt ETSI ITS Network Layer Management API
 * @{
 *
 * Interface to manage ETSI ITS Network Layer
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBITSNET_MGMT_H_
#define __LIBITSNET_MGMT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

#include "etsi-gn-mib.h"

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

/// Struct for Init parameters
typedef struct libITSNet_InitData_tag
{
  /// MIB parameters (set to NULL to not override any compiled defaults)
  tETSIGeoNetMIBParams *pMIBParams;
} tlibITSNet_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initiate the ITSNet library
 * @param pData Initial parameters (if required), set to NULL if not required
 * @return Status, 0 for success
 *
 * Calls the initialisation routines and sets up the configuration
 * During the library initialisation the Modem interface is opened
 */
int libITSNet_Init(tlibITSNet_InitData *pData);

/**
 * @brief Start the ITSNet library
 * @return Status, 0 for success
 *
 * Starts all the libraries threads
 * During the library startup the GPS and Security interfaces are opened
 * Once the library is started, the BTP interface is available
 */
int libITSNet_Start(void);

/**
 * @brief Stop the ITSNet library
 * @return Status, 0 for success
 *
 * Stops all the libraries threads
 */
int libITSNet_Stop(void);

/**
 * @brief Finally exit the ITSNet library
 * @return Status, 0 for success
 *
 * Calls the library cleanup routines
 */
int libITSNet_DeInit(void);

/**
 * @brief Request new identity
 * @return Status, 0 for success
 *
 * Triggers creation of new identity
 */
int libITSNet_NewId(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBITSNET_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
