/**
 * @addtogroup saec_libcnfac_mgmt SAEC Facilities Layer Management API
 * @{
 *
 * Interface to manage SAEC Facilities Layer
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2019 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBCNFAC_MGMT_H_
#define __LIBCNFAC_MGMT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

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

/// Struct for parameters
typedef struct libCNFac_InitData_tag
{
  /// Empty
  char *pEmpty;
} tlibCNFac_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initiate the SAEC Facilities library
 * @return Status, 0 for success
 *
 * Calls the library initialisation routines for all components
 */
int libCNFac_Init(const tlibCNFac_InitData *pData);

/**
 * @brief Start the SAEC Facilities library
 * @return Status, 0 for success
 *
 * Starts all the libraries threads
 */
int libCNFac_Start();

/**
 * @brief Stop the SAEC Facilities library
 * @return Status, 0 for success
 *
 * Calls the library's DeInit functions
 */
int libCNFac_Stop();

/**
 * @brief Stop the SAEC Facilities library
 * @return Status, 0 for success
 *
 * Calls the library's DeInit functions
 */
int libCNFac_DeInit();

#ifdef __cplusplus
}
#endif

#endif // __LIBCNFAC_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
