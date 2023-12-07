/**
 * @addtogroup v2x_etsi_dcc ETSI ITS DCC elements
 * @{
 *
 * @file
 *
 * ETSI DCC Public interface
 *
 * Provides some essential DCC information
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_DCC_IF_H_
#define __ETSI_DCC_IF_H_

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

/// Invalid value for State number
#define DCCIF_STATE_INVALID 0xFF

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

  /// Channel Load Value
typedef uint16_t tETSIDCC_channelLoad;

/// Channel access
typedef enum ETSIDCC_ChannelType
{
  /// G5 SCH0 (formerly CCH)
  ETSI_DCC_G5_SCH0 = 0,
  /// G5 SCHX (formerly SCH)
  ETSI_DCC_G5_SCHX = 1,
  /// PC5 SCH0
  ETSI_DCC_PC5_SCH0 = 2,
} tETSIDCC_ChannelType;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Get last CBR (lastChannelLoad) for the given channel
 *
 * @param ChType Access Layer channel
 * @return The last channel load measurement in deci-percent
 */
uint16_t ETSIDCC_GetLastChannelLoad(tETSIDCC_ChannelType ChType);

/**
 * @brief Get average CBR (avgChannelLoad) for the given channel
 *
 * @param ChType Access Layer channel
 * @return The average channel load measurement in deci-percent
 */
uint16_t ETSIDCC_GetAvgChannelLoad(tETSIDCC_ChannelType ChType);

/**
 * @brief Set CBR (lastChannelLoad) for the given channel
 *
 * @param ChType Access Layer channel
 * @param Load The last channel load value to set in deci-percent
 */
void ETSIDCC_SetLastChannelLoad(tETSIDCC_ChannelType ChType,
                                tETSIDCC_channelLoad Load);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_DCC_IF_H_

/**
 * @}
 */
