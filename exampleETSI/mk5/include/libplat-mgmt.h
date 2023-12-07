/**
 * @addtogroup stack_libplat_mgmt Management of base platform components
 * @{
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBPLAT_MGMT_H_
#define __LIBPLAT_MGMT_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

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

/// Struct for Init parameters
typedef struct libPlat_InitData_tag
{
  /// File location of user configuration (set to NULL for none)
  const char *pUserCfgFile;
  /// File location of defaults configuration (set to NULL for none)
  const char *pDefaultsCfgFile;
  /// Whether to allow out of spec configuration values
  bool AllowOutOfSpecValues;
  /// If AllowOutOfSpecValues == true, whether to limit values to be within spec
  /// or to leave as out of spec
  bool LimitOutOfSpecValues;
} tlibPlat_InitData;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initialise the core parts of the Cohda stack - the base platform
 * @param pData Initial parameters (if required), set to NULL if not required
 * @return Status, 0 for success, -EINVAL for Init error, -ENFILE for Conf error
 *
 * Calls the initialisation routines and sets up the configuration, creating
 * the standard message queues and initialising the PCAP logging framework.
 * In the case of Conf error, no platform was initialise so application
 * can simply exit. In the case of Init error some platform initialisation
 * has occurred and should be cleaned up with @sa libPlat_DeInit.
 */
int libPlat_Init(const tlibPlat_InitData *pData);

/**
 * @brief Start the core platform components of the stack (stats & config)
 * @return Status, 0 for success
 *
 * Starts all the core component threads (stats & config) of the base platform
 */
int libPlat_Start(void);

/**
 * @brief Indicate to the platform library that all start-up is complete
 *
 * Allows the platform library to perform some actions when start-up is complete
 */
void libPlat_Running(void);

/**
 * @brief Stop the platform library threads / components
 * @return Status, 0 for success
 *
 * Stops all the platform threads
 */
int libPlat_Stop(void);

/**
 * @brief Finally exit the platform library and cleanup
 * @return Status, 0 for success
 *
 * Calls the platform cleanup routines
 */
int libPlat_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBPLAT_MGMT_H_

// Close the Doxygen group
/**
 * @}
 */
