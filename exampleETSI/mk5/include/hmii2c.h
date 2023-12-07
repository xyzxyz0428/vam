/**
 * @addtogroup hmi_api Human Machine Interface (HMI) API
 * @{
 *
 * @file
 * HMI Interface Module
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2013 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __HMII2C_H_
#define __HMII2C_H_

#if !(defined(__QNX__))

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "Vector.h"

#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <inttypes.h>

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
/// HMI module predefines the following types of alerts - do not change any
/// values since these are the API which we communicate over UDP to the
/// UiArbitrator etc. The HMI is not limited to these values - they are just
/// defined to ensure no clashes in type values. Any (unique) value which can
/// fit in a tHMIAlertType can be used.
typedef enum
{
  HMII2C_ALERT_TYPE_FCW = 1,
  HMII2C_ALERT_TYPE_FDW = 2,
  HMII2C_ALERT_TYPE_FCA_ONGOING = 3,
  HMII2C_ALERT_TYPE_FCA_COMPLETE = 4,
} eHMII2CAlertType;

/// @copydoc eHMII2CAlertType
typedef uint32_t tHMII2CAlertType;

/// HMI error codes
typedef enum
{
  HMII2C_ERR_NONE = 0, ///< Success (no errors)
  HMII2C_ERR_I2COPEN,
  HMII2C_ERR_I2CCLOSE, ///< Error allocating memory
  HMII2C_ERR_I2CREAD,
  HMII2C_ERR_I2CWRITE,
  HMII2c_ERR_INVALID_ALERT_TYPE, ///< The alert type is not a recognised type
  HMIi2c_ERR_INVALID_ALERT_INFO, ///< An error occurred while processing info
  HMIi2c_ERR_INTERNAL, ///< Internal error (see debug output)
  HMIi2c_ERR_NULL ///< A pointer is found to be NULL (invalid)
} tHMII2CErrCode;

/// Structure of HMI object
typedef struct HMII2C
{
  bool Active;
  bool ThreadCreated;
  bool ThreadHalted;
  pthread_t HMII2C_ThereadID;
  int HMII2C_Fd;
  uint8_t *buff;
  uint8_t numbytes;
  uint8_t devaddr;
}tHMII2C;

/// HMI Severity Level
typedef uint8_t tHMII2CAlertSeverity;
//------------------------------------------------------------------------------
// API Function Declarations
//------------------------------------------------------------------------------

int HMII2C_Close (tHMII2C *pHMII2C);
int HMII2C_Open (tHMII2C *pHMII2C);
void HMII2C_Alert(tHMII2CAlertType Type, tHMII2CAlertSeverity Severity);

#endif //!(defined(__QNX__))

#ifdef __cplusplus
}
#endif

#endif // __HMII2C_H_
// Close the doxygen group
/**
 * @}
 */
