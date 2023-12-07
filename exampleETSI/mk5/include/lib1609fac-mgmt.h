/**
 * @addtogroup stack_lib1609fac_mgmt IEEE 1609 Facilities Layer Management API
 * @{
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2013 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIB1609FAC_MGMT_H_
#define __LIB1609FAC_MGMT_H_

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
typedef struct lib1609Fac_InitData_tag
{
  /// Empty
  char *pEmpty;
} tlib1609Fac_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initiate the 1609Facilities library
 * @param pData Initial parameters (if required), set to NULL if not required
 * @return Status, 0 for success
 *
 * Calls the initialisation routines and sets up the configuration
 * During the library initialisation the Modem interface is opened
 */
int lib1609Fac_Init(tlib1609Fac_InitData *pData);

/**
 * @brief Start the 1609Facilities library
 * @return Status, 0 for success
 *
 * Starts all the libraries threads
 * During the library startup the GPS and Security interfaces are opened
 * Once the library is started, the 1609 interface is available
 */
int lib1609Fac_Start(void);

/**
 * @brief Stop the 1609Facilities library
 * @return Status, 0 for success
 *
 * Stops all the libraries threads
 */
int lib1609Fac_Stop(void);

/**
 * @brief Finally exit the 1609Facilities library
 * @return Status, 0 for success
 *
 * Calls the library cleanup routines
 */
int lib1609Fac_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif // __LIB1609FAC_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
