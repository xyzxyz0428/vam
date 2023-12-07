/**
 * @addtogroup ets_app_facilities_toll ITS Facilities Toll support
 * @{
 *
 * ETSI Toll functionality
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_TOLL__ETSI_TOLL_H_
#define __ETSI_TOLL__ETSI_TOLL_H_

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

/// DB Title length
#define ETSITOLL_DBTITLE_LEN 20
/// DB Date length
#define ETSITOLL_DBDATE_LEN 8
/// DB Version length
#define ETSITOLL_DBVERSION_LEN 4
/// DB Owner length
#define ETSITOLL_DBOWNER_LEN 10

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Format for 'blob' in toll station entry, containing info on toll station
typedef struct TollLocation
{
  /// Station ID  0-60000
  uint16_t Id;
  /// Reduced Power Level [dB] (use default if 0)
  int8_t TxPower;
  /// Range to reduce power [m] (use default if 0)
  uint8_t Radius;
  /// Latitude [tenths-microdegrees]
  int32_t Latitude;
  /// Longitude [tenths-microdegrees]
  int32_t Longitude;
} __attribute__ ((packed)) tTollLocation;

// Format of toll database file header
typedef struct TollDatabaseHdr
{
  /// Title string
  char Title[ETSITOLL_DBTITLE_LEN];
  /// Release Date: 'DDMMYY'
  char Date[ETSITOLL_DBDATE_LEN];
  /// Version: 'x.y'
  char Version[ETSITOLL_DBVERSION_LEN];
  /// Owner
  char Owner[ETSITOLL_DBOWNER_LEN];
  /// Region (00=ignore database 01=Europe)
  uint8_t Region;
  /// Global Reduced Power Level (Power level to reduce to if not specified in location) [dB]
  int8_t GlobalTxPower;
  /// Global Range Range to reduce power if not specified in location [m]
  uint16_t GlobalRange;
  /// Station Count
  uint16_t TotalStations;
} __attribute__ ((packed)) tTollDatabaseHdr;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void ETSIToll_Init (void);
void ETSIToll_Deinit (void);

#ifdef __cplusplus
}
#endif

#endif//__ETSI_TOLL__ETSI_TOLL_H_

// Close the Doxygen group
/**
 * @}
 */
