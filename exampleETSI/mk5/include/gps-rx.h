/**
 * @addtogroup gps_rx_api Internal Positioning
 * @{
 *
 * @section gps_rx_api_wdid What Does It Do
 *
 * Provide access to the GPS receiver
 *
 * @file
 *
 * Interface message definitions
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2013 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __GPS_RX_IF_H_
#define __GPS_RX_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "lph-pos-api.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Limit readers to GPS public buffer
#define GPSRX_MAX_READERS 5

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

// Aligns with gpsd's v3.17 gps.h
typedef struct GPSRxFix
{
  double time;
  int32_t mode;
  int32_t status;
  double ept;
  double latitude;
  double epy;
  double longitude;
  double epx;
  double altitude;
  double epv;
  double track;
  double epd;
  double speed;
  double eps;
  double climb;
  double epc;
} tGPSRxFix;

// Aligns with gpsd's v3.17 gps.h
typedef struct GPSRxGST
{
  double utctime;
  double rms_deviation;
  double smajor_deviation;
  double sminor_deviation;
  double smajor_orientation;
  double lat_err_deviation;
  double lon_err_deviation;
  double alt_err_deviation;
} tGPSRxGST;

/// GPS fix
typedef struct GPSRxInfo
{
  /// Non-zero if GPS is on line, 0 if not
  double Online;
  /// Accumulated PVT data
  tGPSRxFix Fix;
  /// GPGST data
  tGPSRxGST GST;
  /// Number of satellites used in solution
  int32_t SatellitesUsed;

  /// This field was used as Accuracy blob
  /// (DF_PositionalAccuracy (Desc Name) Record 44). This has been replaced by
  /// the structure PositionalAccuracy below for the following reasons:
  /// 1. J2735 2016 DF_PositionalAccuracy no longer has
  ///    SemiMajor/SemiMinor/SemiMajorOrientation encoded into a single
  ///    uint32_t
  /// 2. This allows internal storage of the values that are out of J2735's range,
  ///    which makes lph/gps-rx modules less dependent on J2735.
  /// @note This field is still kept because GPSRX_SizeOK() uses member offset
  ///       to determine the version of gps.pcap.
  uint32_t reserved;

  /// Number of satellites visible
  struct {
    /// Number of GPS satellites visible
    int32_t GPS;
    /// Number of gbas satellites visible
    int32_t GBAS;
    /// Number of sbas satellites visible
    int32_t SBAS;
    /// Number of gnss satellites visible
    int32_t GNSS;
  } SatellitesVisible;

  /// Leap seconds
  struct {
    /// Number of current GPS leap seconds
    int32_t CurrentNum;
    /// Time of next leap-second, if known, else 0
    int32_t Next;
  } LeapSecond;

  /// Auxilliary (fallback) PVT data
  tGPSRxFix Aux;

  struct
  {
    /// Semi-major axis accuracy with 95% confidence (two sigmas)
    /// Range: N/A Units: m
    float SemiMajorAxis_m;
    /// Semi-minor axis accuracy with 95% confidence (two sigmas)
    /// Range: N/A Units: m
    float SemiMinorAxis_m;
    /// Orientation of semi-major axis
    /// Range: N/A Units: Degree
    float SemiMajorAxisOrientation_deg;
    /// This field is to make sure tGPSRxInfo is aligned to 8 bytes on all
    /// platforms. arm gcc wants 8 bytes alignment due to the first double
    /// field - Online, while x86 only wants 4.
    uint32_t Padding;
  } PositionalAccuracy;

} tGPSRxInfo;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


void GPSRX_LibraryInit(void);

int GPSRX_ThreadInit(int SchedulerPolicy, int SchedulerPriority);

void GPSRX_ThreadDeinit(void);

void GPSRX_LibraryDeinit(void);

void GPSRX_ProcessPosition(tGPSRxInfo *pGpsInfo);

void GPSRX_UpdatePosition(const tLPHPosFix *pPosFix);

void GPSRX_LogFromLPH(void *pLPHPosFix);

#ifdef __cplusplus
}
#endif

#endif // __GPS_RX_IF_H_

// Close the doxygen group
/**
 * @}
 */
