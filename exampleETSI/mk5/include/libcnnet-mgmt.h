/**
 * @addtogroup saec_libcnnet_mgmt SAEC Network Layer Management API
 * @{
 *
 * Interface to manage SAEC Network Layer
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBCNNET_MGMT_H_
#define __LIBCNNET_MGMT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

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
typedef struct libCNNet_InitData_tag
{
} tlibCNNet_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initiate the CNNet library
 * @param pData Initial parameters (if required), set to NULL if not required
 * @return Status, 0 for success
 *
 * Calls the initialisation routines and sets up the configuration
 * During the library initialisation the Modem interface is opened
 */
int libCNNet_Init(tlibCNNet_InitData *pData);

/**
 * @brief Start the CNNet library
 * @return Status, 0 for success
 *
 * Starts all the libraries threads
 * During the library startup the GPS and Security interfaces are opened
 * Once the library is started, the DSMP interface is available
 */
int libCNNet_Start(void);

/**
 * @brief Stop the CNNet library
 * @return Status, 0 for success
 *
 * Stops all the libraries threads
 */
int libCNNet_Stop(void);

/**
 * @brief Finally exit the CNNet library
 * @return Status, 0 for success
 *
 * Calls the library cleanup routines
 */
int libCNNet_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBCNNET_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
