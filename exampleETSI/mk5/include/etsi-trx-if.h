/**
 * @addtogroup ets_app_facilities_trx_api ETSI ITS Facilities TRX API
 * @{
 *
 * TS 102 894-2 V1.3.1
 *
 * Interface to TRX general controls
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETS_TRX_ETS_TRX_IF_H_
#define __ETS_TRX_ETS_TRX_IF_H_

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

/// Maximum tolling zones stored
#define TRX_MAX_TOLL_ZONE_COUNT 16

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// TRX Status codes
typedef enum TRXStatusCode
{
  /// TRX success
  TRX_SUCCESS = 0x00,
  /// TRX generation failure
  TRX_FAILURE = 0x01,

} eTRXStatusCode;

/// Status code for TRX actions @ref TRXStatusCode
typedef uint8_t tTRXStatusCode;

/// Structure of FAC Tx info for EXT event
/// This is used by the EXT event @c QSMSG_EXT_FAC_TX_INFO
typedef struct TRX_TxInfo
{
  /// Tx power (@ref ETSIGeoNetMaxTxPower)
  int8_t ReqTxPower;
} tTRX_TxInfo;

/// Structure of FAC Tx Power info for queries
typedef struct TRX_TxPowerInfo
{
  /// Tx power (@ref ETSIGeoNetMaxTxPower)
  int8_t MaxTxPower;
  /// Tolling zone active
  bool TollingZoneActive;
  /// TollingDBLoaded
  bool TollingDBLoaded;
} tTRX_TxPowerInfo;

/// FAC component state
typedef struct TRX_TollingZone
{
  /// Zone Id
  uint32_t Identity;
  /// Zone Lat
  int32_t Latitude;
  /// Zone Long
  int32_t Longitude;
  /// Radius of zone (0 = use default)
  uint16_t RadiusM;
  /// Power to use in zone (0 = use default)
  int8_t PowerdBm;
} tTRX_TollingZone;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// @brief Set a group of toll station/protected communications zone
///        NOTE: this setting is valid only for a limited time (around 100sec)
///              Toll station locations are expected to be updated regularly
/// @param TollingZoneCount Number of toll stations to set
/// @param pTollingZones pointer to array of tolling zones
/// @return TRX Status Code
tTRXStatusCode TRX_SetTollingLocations(uint8_t TollingZoneCount, const tTRX_TollingZone *pTollingZones);

/// @brief Clear a protected communications zone
///        NOTE: It is not necessary to clear locations before setting new
///              location, instead simply update the locations. Also, some
///              locations may have been internally cached so will remain
///              under consideration until their expiry
/// @return TRX Status Code
tTRXStatusCode TRX_ClearTollingLocations(void);

/// @brief Indicate whether tolling locations are known
///        NOTE: Allows safer power control at startup where comms stack
///              may start before tolling database is loaded
/// @param IsKnown True if Tolling database is loaded and operational
void TRX_TollingLocationKnown(bool IsKnown);

/// @brief Get the maximum transmit power in half dBm, along with current
///        tolling zone information
///        NOTE: Changes in maximum transmit power can optionally be reported
///              via EXT interface
/// @return Structure with maximum power in half dBm units and tolling zone status
tTRX_TxPowerInfo TRX_GetMaxPower(void);

#ifdef __cplusplus
}
#endif

#endif // __ETS_TRX_ETS_TRX_IF_H_

// Close the Doxygen group
/**
 * @}
 */
