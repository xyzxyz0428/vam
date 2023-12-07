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

#ifndef __HMI_H_
#define __HMI_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include "Vector.h"

#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Max length of HMI version string
#define HMI_VERSION_MAX_LEN 16


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// HMI error codes
typedef enum
{
  HMI_ERR_NONE = 0, ///< Success (no errors)
  HMI_ERR_INVALID_DEST, ///< Invalid destination address
  HMI_ERR_MEM_ALLOC, ///< Error allocating memory
  HMI_ERR_INVALID_ALERT_TYPE, ///< The alert type is not a recognised type
  HMI_ERR_INVALID_ALERT_INFO, ///< An error occurred while processing info
  HMI_ERR_INTERNAL, ///< Internal error (see debug output)
  HMI_ERR_NULL ///< A pointer is found to be NULL (invalid)
} tHMIErrCode;

/// HMI module predefines the following types of alerts - do not change any
/// values since these are the API which we communicate over UDP to the
/// UiArbitrator etc. The HMI is not limited to these values - they are just
/// defined to ensure no clashes in type values. Any (unique) value which can
/// fit in a tHMIAlertType can be used.
typedef enum
{
  HMI_ALERT_TYPE_HEARTBEAT = 0, ///< HeartBeat message to HMI
  HMI_ALERT_TYPE_FCW = 1, ///< Forward Collision Warning
  HMI_ALERT_TYPE_EEBL = 2, ///< Emergency Electronic Brake Light
  HMI_ALERT_TYPE_ICW = 3, ///< Intersection Collision Warning
  HMI_ALERT_TYPE_CSW = 4, ///< Curve Speed Warning
  HMI_ALERT_TYPE_LANECLOSED = 5, ///< Lane Closed
  HMI_ALERT_TYPE_ICE = 6, ///< Ice Road Warning
  HMI_ALERT_TYPE_ROADWORK = 7, ///< Road Work
  HMI_ALERT_TYPE_SPEEDLIMIT = 8, ///< Speed Limit
  HMI_ALERT_TYPE_RLW = 9, ///< Red Light Warning
  HMI_ALERT_TYPE_SVA = 10, ///< Stationary Vehicle Alert
  HMI_ALERT_TYPE_HLW = 11, ///< Hazard Location Warning
  HMI_ALERT_TYPE_EVW = 12, ///< Emergency Vehicle Warning
  HMI_ALERT_TYPE_GREEN_PHASE = 13, ///< GLOSA Phase
  HMI_ALERT_TYPE_YELLOW_PHASE = 14, ///< GLOSA Phase
  HMI_ALERT_TYPE_RED_PHASE = 15, ///< GLOSA Phase
  HMI_ALERT_TYPE_MAW = 16, ///< Motorcycle Approaching Warning
  HMI_ALERT_TYPE_BSW_LCW = 17, ///< Blind Spot Warning / Lane Change Warning
  HMI_ALERT_TYPE_LTA = 18, ///< Left Turn Assist
  HMI_ALERT_TYPE_DNPW = 19, ///< Do Not Pass Warning
  HMI_ALERT_TYPE_SVW = 20, ///< Stoplight Violation Warning
  HMI_ALERT_TYPE_IHW = 21, ///< Infrastructure Hazard Warning
  HMI_ALERT_TYPE_IVS = 22, ///< In-Vehicle signage
  HMI_ALERT_TYPE_TJA = 23, ///< Traffic Jam Ahead
  HMI_ALERT_TYPE_HLW_CN = 24, ///< Hazard Location Warning (CN)
  HMI_ALERT_TYPE_TJW_CN = 25, ///< Traffic Jam Warning (CN)
  HMI_ALERT_TYPE_VRUSW_CN = 26, ///< Vulnerable road user (CN)
  HMI_ALERT_TYPE_IVS_CN = 27, ///< Vulnerable road user (CN)
  HMI_ALERT_TYPE_SLW = 28, ///< Speed Limit Warning (CN)

  HMI_ALERT_TYPE_SYNC = 29, ///< Sync Application
  HMI_ALERT_TYPE_FDW = 30, ///< Following Distance Warning

  HMI_ALERT_TYPE_VRU = 31, ///< Vulnerable road user

  HMI_ALERT_TYPE_FSP = 78, ///< FSP Send request, Grant and Deny messages
  HMI_ALERT_TYPE_V2P = 79, ///< V2P Caution Vulerable User

  HMI_ALERT_TYPE_HLW_FOG = 20, /// Hazard Location Warning Fog
  HMI_ALERT_TYPE_HLW_RAIN = 21, /// Hazard Location Warning Rain
  HMI_ALERT_TYPE_HLW_TRC = 22, /// Hazard Location Warning
  HMI_ALERT_TYPE_PING = 98, ///< Ping

  //HMI_ALERT_TYPE_RESERVED > 255
} eHMIAlertType;
/// @copydoc eHMIAlertType
typedef uint32_t tHMIAlertType;

/// Specify the direction of a particular alert (e.g. ICW & CSW can be left /
/// right directional)
typedef enum
{
  HMI_ALERT_DIRECTION_UNKNOWN = 0,
  HMI_ALERT_DIRECTION_LEFT = 1,
  HMI_ALERT_DIRECTION_RIGHT = 2,
} eHMIAlertDirection;
/// @copydoc eHMIAlertDirection
typedef uint8_t tHMIAlertDirection;

#define HMI_ALERT_SEVERITY_UNKNOWN  0

/// HMI Severity Level
typedef uint8_t tHMIAlertSeverity;

/// Information sent to HMI for periodic heart-beat signal
typedef struct HMIInfoHeartBeat
{
  uint32_t Id; ///< Signal the device's ID to HMI
  char Version[HMI_VERSION_MAX_LEN]; ///< Version string to show on HMI
  uint32_t Sync;  ///< Time sync status - 1 = sync, 0 = no sync (aka say inverse
                  ///of return status of 'chronyc waitsync 1 0 0' )
  uint32_t UpdateStatus; /// Are we currently upgrading
  uint32_t LogStatus; /// Are we currently log offloading
  uint32_t Fix;   ///< Position fix quality - 3 = 3d, 2 = 2d, 1 = 1d, 0 = no fix
  uint32_t RSU;   ///< Are we in range of / connected to an RSU
  uint32_t NumTx; ///< Number of packets transmitted
  uint32_t NumRx; ///< Number of packets received
  uint32_t NumRemotes; ///< Number of remote vehicles currently being tracked
  uint32_t NumTIMs; ///< Number of unique TIM messages received
  uint32_t NumIntersections; ///< Number of unique MAP messages received
  uint32_t TxPowerdBm; ///< Current transmit power in dBm
} tHMIInfoHeartBeat;

/// Structure of HMI object
typedef struct HMI tHMI;

/// Icon, Audio and Text to show for a given alert
typedef struct HMIAlertConfig
{
  /// The type of alert
  tHMIAlertType Type;
  /// The direction of the alert
  tHMIAlertDirection Direction;
  /// The actual severity of the HMI alert
  tHMIAlertSeverity Severity;
  /// The severity is a range with Low and High bounds
  tHMIAlertSeverity SeverityLow;
  tHMIAlertSeverity SeverityHigh;
  /// The full path to the filename of the image to show
  char *pIcon;
  /// The full path to the filename of the alternate image to show - if unset
  /// will use pIcon as well
  char *pAltIcon;
  /// The full path to the filename of the audio to play
  char *pAudio;
  /// The string to show for the alert message
  char *pText;
  /// Whether this has been pushed to the UI yet
  int Pushed;
} tHMIAlertConfig;


//------------------------------------------------------------------------------
// API Function Declarations
//------------------------------------------------------------------------------

typedef tHMIErrCode (*tHMIGetHeartBeatInfoFunc)(tHMIInfoHeartBeat *pInfo,
                                                void *pGetHeartBeatInfoPriv);

tHMIErrCode HMI_Open (tHMI **ppHMI,
                      tHMIGetHeartBeatInfoFunc GetHearbeatInfo,
                      void *pGetHeartBeatInfoPriv);

tHMIErrCode HMI_AddAlertConfig(tHMI *pHMI,
                               tHMIAlertType Type,
                               tHMIAlertDirection Direction,
                               tHMIAlertSeverity SeverityLow,
                               tHMIAlertSeverity SeverityHigh,
                               const char *pIcon,
                               const char *pAudio,
                               const char *pText);

tHMIErrCode HMI_GetAlertConfig(tHMI *pHMI,
                               tHMIAlertType Type,
                               tHMIAlertDirection Direction,
                               tHMIAlertSeverity Severity,
                               tHMIAlertConfig **ppConfig);

void HMI_FreeAlertConfig(tHMIAlertConfig *pAlert);

tHMIErrCode HMI_Close (tHMI *pHMI);

tHMIErrCode HMI_Alert (tHMI *pHMI,
                       tHMIAlertType Type,
                       tHMIAlertDirection Direction,
                       tHMIAlertSeverity Severity,
                       const char *pText,
                       float Range);

tHMIErrCode HMI_CancelAlerts (tHMI *pHMI);

#ifdef __cplusplus
}
#endif

#endif // __HMI_H_
// Close the doxygen group
/**
 * @}
 */
