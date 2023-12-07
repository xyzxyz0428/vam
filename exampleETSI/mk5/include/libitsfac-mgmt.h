/**
 * @addtogroup ets_libitsfac_mgmt ETSI ITS Facilities Layer Management API
 * @{
 *
 * Interface to manage ETSI ITS Facilities Layer
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBITSFAC_MGMT_H_
#define __LIBITSFAC_MGMT_H_

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
typedef struct libITSFac_InitData_tag
{
  /// Empty
  char *pEmpty;
} tlibITSFac_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initiate the ITSFac library
 * @return Status, 0 for success
 *
 * Calls the library initialisation routines for all components
 */
int libITSFac_Init(tlibITSFac_InitData *pData);

/**
 * @brief Start the ITSFac library
 * @return Status, 0 for success
 *
 * Starts all the libraries threads
 */
int libITSFac_Start(void);

/**
 * @brief Stop the ITSFac library
 * @return Status, 0 for success
 *
 * Calls the library's DeInit functions
 */
int libITSFac_Stop(void);

/**
 * @brief Stop the ITSFac library
 * @return Status, 0 for success
 *
 * Calls the library's DeInit functions
 */
int libITSFac_DeInit(void);

/**
 * @brief Get latest error from library
 * @return Error string
 *
 * Return latest available error status string
 */
const char *libITSFac_GetError(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBITSFAC_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
