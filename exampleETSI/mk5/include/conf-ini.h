/**
 * @addtogroup v2v_cfg_api Configuration service
 * @{
 *
 * @file
 * CFG library API
 *
 * Configuration file parameters
 */

//------------------------------------------------------------------------------
// Copyright (c) 2023 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#ifndef ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_PLAT_CONF_CONF_INI_H_
#define ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_PLAT_CONF_CONF_INI_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CONF_ERR_NULL    (0x01)
#define CONF_ERR_FOPEN   (0x02)
#define CONF_ERR_SCANF   (0x04)
#define CONF_ERR_MIN     (0x08)
#define CONF_ERR_MAX     (0x10)
#define CONF_ERR_NAN     (0x20)
#define CONF_ERR_UNK     (0x40)
#define CONF_ERR_OM      (0x80)

typedef enum
{
  CONF_ENFORCING,
  CONF_LIMIT,
  CONF_ALLOW
} tConfReadMode;

/// Configuration parameters for Cohda_ADR
typedef struct Cohda_ADR
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
    /// __Boolean, default: "False"__\n
  bool ENABLE;
    /// __Boolean, default: "False"__\n
  bool LogEnableFlag;
    /// __String, default: ""__\n
  const char * UDP_HOST;
    /// __Integer, default: 15000, min/max 1/65535__\n
  int32_t UDP_PORT;
    /// __String, default: ""__\n
  const char * JSON_UDP_HOST;
    /// __Integer, default: 33994, min/max 1/65535__\n
  int32_t JSON_UDP_PORT;
    /// __Integer, default: 12, min/max 1/12__\n
  int32_t RV_CNT;
} tCohda_ADR;
/// Configuration parameters for Cohda_HMI
typedef struct Cohda_HMI
{
    /// __String, default: "127.0.0.1"__\n
  const char * Destination;
    /// __String, default: "9100"__\n
  const char * Port;
    /// __String, default: "lo"__\n
  const char * Interface;
    /// __Integer, default: 10, min/max 0/65536__\n
  int32_t Timeout_ms;
    /// __Boolean, default: "False"__\n
  bool JSONOutput;
} tCohda_HMI;
/// Configuration parameters for Cohda_IVI
typedef struct Cohda_IVI
{
    /// __Boolean, default: "True"__\n
  bool Enable;
} tCohda_IVI;
/// Configuration parameters for Cohda_LTE
typedef struct Cohda_LTE
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
    /// __Boolean, default: "False"__\n
  bool ENABLE;
    /// __String, default: ""__\n
  const char * TX_HostName;
    /// __Integer, default: 30334, min/max 0/65535__\n
  int32_t TX_Port;
    /// __Boolean, default: "False"__\n
  bool BidiTxPort;
    /// __Integer, default: -1, min/max -1/65535__\n
  int32_t RX_Port1;
    /// __Integer, default: -1, min/max -1/65535__\n
  int32_t RX_Port2;
} tCohda_LTE;
/// Configuration parameters for Cohda_PC5
typedef struct Cohda_PC5
{
    /// __Integer, default: 100, min/max 0/1000__\n
  int32_t SPS_0_Interval_ms;
    /// __Integer, default: 365, min/max 0/65535__\n
  int32_t SPS_0_Size;
} tCohda_PC5;
/// Configuration parameters for Cohda_PH
typedef struct Cohda_PH
{
    /// __Integer, default: 3, min/max 1/3__\n
  int32_t Method;
    /// __Integer, default: 200, min/max 0/5000__\n
  int32_t Distance_m;
    /// __Float, default: 210.0, min/max 0.0/500.0__\n
  float ChordLength_m;
    /// __Float, default: 1.0, min/max 0.0/1.0__\n
  float AllowableError_m;
    /// __Integer, default: 15, min/max 0/40__\n
  int32_t MaxPoints;
    /// __Float, default: 0.02, min/max 0.0/1.0__\n
  float SmallDeltaPhi_r;
    /// __Hexidecimal, default: 0x7fffff, min/max 0x0/0xffffff__\n
  uint32_t MaxEstimatedRadius;
    /// __Integer, default: 60, min/max 1/100__\n
  int32_t MaxNumIntermediatePoints;
    /// __Boolean, default: "True"__\n
  bool Persistency;
    /// __Boolean, default: "True"__\n
  bool PositionLostAction;
} tCohda_PH;
/// Configuration parameters for Cohda_PP
typedef struct Cohda_PP
{
    /// __Float, default: 0.33, min/max 0.01/1.0__\n
  float CurvatureFilterCutoff_Hz;
    /// __Float, default: 1.0, min/max 0.0/2.0__\n
  float CurvatureDampFactor;
    /// __Float, default: 0.1, min/max 0.1/0.4__\n
  float CurvatureFilterSamplingTime;
    /// __Float, default: 1.0, min/max 0.0/2.0__\n
  float MinSpeed_mps;
    /// __Integer, default: 2500, min/max 1000/5000__\n
  int32_t MaximumRadius_m;
    /// __Float, default: 1.0, min/max 0.33/1.0__\n
  float ConfFilterCutoff_Hz;
    /// __Float, default: 1.0, min/max 0.0/2.0__\n
  float ConfDampFactor;
    /// __Float, default: 0.1, min/max 0.1/0.4__\n
  float ConfFilterSamplingTime;
    /// __Float, default: 25.0, min/max 0.0/400.0__\n
  float ConfLookup_0_0_Input;
    /// __Float, default: 20.0, min/max 0.0/400.0__\n
  float ConfLookup_0_1_Input;
    /// __Float, default: 15.0, min/max 0.0/400.0__\n
  float ConfLookup_0_2_Input;
    /// __Float, default: 10.0, min/max 0.0/400.0__\n
  float ConfLookup_0_3_Input;
    /// __Float, default: 5.0, min/max 0.0/400.0__\n
  float ConfLookup_0_4_Input;
    /// __Float, default: 2.5, min/max 0.0/400.0__\n
  float ConfLookup_0_5_Input;
    /// __Float, default: 2.0, min/max 0.0/400.0__\n
  float ConfLookup_0_6_Input;
    /// __Float, default: 1.5, min/max 0.0/400.0__\n
  float ConfLookup_0_7_Input;
    /// __Float, default: 1.0, min/max 0.0/400.0__\n
  float ConfLookup_0_8_Input;
    /// __Float, default: 0.5, min/max 0.0/400.0__\n
  float ConfLookup_0_9_Input;
    /// __Float, default: 0.0, min/max 0.0/400.0__\n
  float ConfLookup_0_10_Input;
    /// __Float, default: 0.0, min/max 0.0/100.0__\n
  float ConfLookup_1_0_Conf;
    /// __Float, default: 10.0, min/max 0.0/100.0__\n
  float ConfLookup_1_1_Conf;
    /// __Float, default: 20.0, min/max 0.0/100.0__\n
  float ConfLookup_1_2_Conf;
    /// __Float, default: 30.0, min/max 0.0/100.0__\n
  float ConfLookup_1_3_Conf;
    /// __Float, default: 40.0, min/max 0.0/100.0__\n
  float ConfLookup_1_4_Conf;
    /// __Float, default: 50.0, min/max 0.0/100.0__\n
  float ConfLookup_1_5_Conf;
    /// __Float, default: 60.0, min/max 0.0/100.0__\n
  float ConfLookup_1_6_Conf;
    /// __Float, default: 70.0, min/max 0.0/100.0__\n
  float ConfLookup_1_7_Conf;
    /// __Float, default: 80.0, min/max 0.0/100.0__\n
  float ConfLookup_1_8_Conf;
    /// __Float, default: 90.0, min/max 0.0/100.0__\n
  float ConfLookup_1_9_Conf;
    /// __Float, default: 100.0, min/max 0.0/100.0__\n
  float ConfLookup_1_10_Conf;
    /// __Integer, default: 100, min/max 0/100__\n
  int32_t StationaryConf;
    /// __Float, default: 0.1, min/max 0.01/1.0__\n
  float ConfAugmentFilterCutoff_Hz;
    /// __Boolean, default: "False"__\n
  bool AugmentConfidenceFilter;
    /// __Boolean, default: "False"__\n
  bool UseStrWhlAngGrad;
} tCohda_PP;
/// Configuration parameters for Cohda_QTI
typedef struct Cohda_QTI
{
    /// __String, default: "rmnet_data1"__\n
  const char * Interface;
    /// __String, default: "ff02::1"__\n
  const char * DestinationAddr;
    /// __Integer, default: 32, min/max 0/65535__\n
  int32_t SPSPort_0_V2XID;
    /// __Integer, default: 32770, min/max 0/65535__\n
  int32_t EventPort_0_V2XID;
    /// __Integer, default: 32771, min/max 0/65535__\n
  int32_t EventPort_1_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_2_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_3_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_4_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_5_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_6_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_7_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_8_V2XID;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t EventPort_9_V2XID;
} tCohda_QTI;
/// Configuration parameters for Cohda_RPS
typedef struct Cohda_RPS
{
    /// __Integer, default: 4, min/max -1/255__\n
  int32_t DebugLevel;
    /// __Boolean, default: "False"__\n
  bool RPS_AP_MODE_ENABLE;
    /// __String, default: "/mnt/ubi/locate/locate_aplist.json"__\n
  const char * RPS_AP_MODE_APLIST_FILENAME;
    /// __String, default: "locate_new_aplist.json"__\n
  const char * RPS_AP_MODE_NEW_APLIST_FILENAME;
    /// __Boolean, default: "False"__\n
  bool DUMMY_BEACON_GENERATE;
    /// __Boolean, default: "True"__\n
  bool RPS_ANNOUNCE_ENABLE;
    /// __Boolean, default: "False"__\n
  bool ENABLE;
    /// __Hexidecimal, default: 0x0, min/max 0x0/0xffffffff__\n
  uint32_t DEVICE_ID;
    /// __String, default: ""__\n
  const char * DEVICE_ID_STR;
    /// __Integer, default: 33990, min/max 0/65535__\n
  int32_t UDP_STATUS_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * UDP_STATUS_HOST;
    /// __Integer, default: 1000, min/max 50/60000__\n
  int32_t UDP_STATUS_PERIOD_ms;
    /// __Integer, default: 100, min/max 50/1000__\n
  int32_t CORE_PROCESSING_PERIOD_ms;
    /// __Boolean, default: "False"__\n
  bool RAW_RANGING_ENABLE;
    /// __Integer, default: 33991, min/max 0/65535__\n
  int32_t RAW_RANGING_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * RAW_RANGING_HOST;
    /// __Integer, default: 5, min/max 2/5__\n
  int32_t RAW_RANGING_VERSION;
    /// __Boolean, default: "True"__\n
  bool RAW_RANGING_LOG_ENABLE;
    /// __String, default: ""__\n
  const char * LOCATE_TUNNEL_MAP_FILENAME;
    /// __String, default: ""__\n
  const char * LOCATE_MAPDATA_FILENAME;
    /// __Integer, default: 3, min/max 0/3__\n
  int32_t LOCATE_TUNNEL_POSITIONING_MODE;
    /// __Integer, default: 4, min/max 0/9__\n
  int32_t LOCATE_TUNNEL_EDGE_TRACKING_MODE;
    /// __Float, default: 1.0, min/max -1.0/20.0__\n
  float LOCATE_TUNNEL_INHIBIT_IN_CLOSE_RANGE_m;
    /// __Boolean, default: "False"__\n
  bool LOCATE_TUNNEL_ZERO_UPDATE_STATIONARY;
    /// __Float, default: 20.0, min/max 0.0/100.0__\n
  float LOCATE_TUNNEL_POSITION_VARIANCE_THRESHOLD;
    /// __Float, default: 20.0, min/max 0.0/100.0__\n
  float LOCATE_TUNNEL_RANGE_INNOVATION_THRESHOLD;
    /// __Integer, default: 10, min/max 0/100__\n
  int32_t LOCATE_TUNNEL_TRACKING_MONITOR_BADSTATE_COUNT;
    /// __Integer, default: 20, min/max 0/1000__\n
  int32_t LOCATE_TUNNEL_RANGE_INNOVATION_RUN_THRESHOLD;
    /// __Float, default: 90.0, min/max 0.0/180.0__\n
  float LOCATE_TUNNEL_IMU_OFFSET_THRESHOLD_DEGS;
    /// __Integer, default: 1, min/max 0/100__\n
  int32_t LOCATE_TUNNEL_IMU_OFFSET_RUN_THRESHOLD;
    /// __Integer, default: 10, min/max 0/1000__\n
  int32_t LOCATE_TUNNEL_TRACKING_LOST_REFERENCE_TRACKING_COUNT;
    /// __Integer, default: 10, min/max 0/100__\n
  int32_t LOCATE_TUNNEL_IMU_CAL_MIN_RUN_LENGTH;
    /// __Boolean, default: "False"__\n
  bool LOCATE_TUNNEL_IMU_CONTINUOUS_CALIBRATION;
    /// __Float, default: 10.0, min/max 0.0/100.0__\n
  float LOCATE_TUNNEL_IMU_HEADING_CAL_MIN_EDGE_END_LENGTH;
    /// __Float, default: 1.0, min/max 0.0/100.0__\n
  float LOCATE_TUNNEL_IMU_HEADING_CAL_MIN_SPEED;
    /// __Float, default: 50.0, min/max 0.0/200.0__\n
  float LOCATE_TUNNEL_PORTAL_CAPTURE_RANGE_m;
    /// __Float, default: 0.5, min/max 0.0/2.0__\n
  float MAX_ACC_LONG_MPSS;
    /// __Boolean, default: "True"__\n
  bool TX_ENABLE;
    /// __Boolean, default: "True"__\n
  bool RX_ENABLE;
    /// __Integer, default: -1, min/max -10/30__\n
  int32_t TX_DEFAULT_POWER;
    /// __Integer, default: -1, min/max -1/3__\n
  int32_t TX_DEFAULT_ANTENNA;
    /// __Integer, default: 0, min/max 0/4__\n
  int32_t TX_PROBE_ANTENNA_MODE;
    /// __Integer, default: 150, min/max 0/200__\n
  int32_t DOT11_RADIO_CHANNEL;
    /// __Integer, default: 3, min/max 0/3__\n
  int32_t DOT11_RX_ANTENNA;
    /// __Integer, default: 10, min/max 0/255__\n
  int32_t DOT11_DEFAULT_MCS;
    /// __Integer, default: 3, min/max 0/255__\n
  int32_t DOT11_SHORT_RETRY_LIMIT;
    /// __Integer, default: 3, min/max 0/255__\n
  int32_t DOT11_LONG_RETRY_LIMIT;
    /// __String, default: "ff:ff:ff:ff:ff:ff"__\n
  const char * DOT11_DEFAULT_BSSID;
    /// __String, default: ""__\n
  const char * DOT11_OVERRIDE_PROBE_MAC_ADDR;
    /// __Boolean, default: "False"__\n
  bool RPS_RADIO_NUM;
    /// __Integer, default: 0, min/max 0/2__\n
  int32_t RPS_CHANNEL_NUM;
    /// __Integer, default: 10, min/max 10/20__\n
  int32_t RPS_BANDWIDTH_MODE;
    /// __Integer, default: 100, min/max 20/5000__\n
  int32_t RPS_STA_PROBE_PERIOD_ms;
    /// __Integer, default: 1000, min/max 20/5000__\n
  int32_t RPS_STA_FORCED_PROBE_PERIOD_ms;
    /// __Boolean, default: "False"__\n
  bool RPS_LOCATE_SYNC_TO_TOP;
    /// __Integer, default: 10, min/max 0/50__\n
  int32_t RPS_LOCATE_SYNC_TO_TOP_OFFSET_ms;
    /// __Integer, default: 1, min/max 1/100__\n
  int32_t RPS_STA_PROBE_BURST_COUNT;
    /// __Integer, default: 100, min/max 1/10000__\n
  int32_t RPS_STA_MONITOR_DB_MAX_ENTRIES;
    /// __Integer, default: 500, min/max 100/60000__\n
  int32_t RPS_BROADCAST_ANNOUNCE_PERIOD_ms;
    /// __Integer, default: 10, min/max 0/15__\n
  int32_t RPS_STA_PROBE_MCS;
    /// __Integer, default: 10, min/max 0/15__\n
  int32_t RPS_STA_PROBE_BROADCAST_MCS;
    /// __Boolean, default: "False"__\n
  bool RPS_STA_PROBE_USE_RTSCTS;
    /// __Integer, default: 5000, min/max 0/60000__\n
  int32_t RPS_STA_PROBE_RX_QUIET_PERIOD_ms;
    /// __Boolean, default: "False"__\n
  bool RPS_STA_PROBE_DISABLE;
    /// __Boolean, default: "True"__\n
  bool RPS_STA_PROBE_NORETRIES;
    /// __Integer, default: 4, min/max 0/4__\n
  int32_t RPS_ESTIMATION_MODE;
    /// __Float, default: 80.0, min/max 0.0/1000.0__\n
  float RPS_ESTIMATION_MEDIAN_MEAN_SPAN_ns;
    /// __Float, default: 1.0, min/max 0.0/10.0__\n
  float RPS_ESTIMATION_SLIDING_MIN_WIDTH_s;
    /// __Float, default: 1.0, min/max 0.0/10.0__\n
  float RPS_ESTIMATION_SLIDING_MEAN_WIDTH_s;
    /// __Float, default: 3.0, min/max 0.0/10.0__\n
  float RPS_ESTIMATION_LINEAR_FIT_WIDTH_s;
    /// __Float, default: 4.0, min/max 0.0/100.0__\n
  float RPS_ESTIMATION_MAXIDLE_s;
    /// __Float, default: 0.1, min/max 0.0/10.0__\n
  float RPS_ESTIMATION_UPDATE_PERIOD_s;
    /// __Boolean, default: "True"__\n
  bool RPS_ABS_POSITIONING_DISABLED;
    /// __Boolean, default: "False"__\n
  bool RPS_ABS_POS_USE_STA_ADVERTISED_POSITIONS;
    /// __Integer, default: 20, min/max 0/100__\n
  int32_t RPS_ABS_POS_RANGE_CONF_TRESHOLD;
    /// __Integer, default: -120, min/max -120/0__\n
  int32_t RPS_ABS_POS_RSSI_THRESHOLD;
    /// __Integer, default: 100, min/max 10/1000__\n
  int32_t RPS_ABS_POS_HISTORY_LENGTH;
    /// __Float, default: 25.0, min/max 0.0/200.0__\n
  float RPS_ABS_POS_DELTA_LOSS_THRESHOLD_dBm;
    /// __Float, default: 22.0, min/max 0.0/200.0__\n
  float RPS_ABS_POS_DELTA_POS_THRESHOLD_m;
    /// __Float, default: 5.0, min/max -100.0/100.0__\n
  float RPS_ABS_POS_RANGE_BIAS_m;
    /// __Float, default: 0.5, min/max 0.0/10.0__\n
  float RPS_ABS_LOW_SPEED_THRESHOLD_mps;
    /// __Boolean, default: "False"__\n
  bool LOCATE_TUNNEL_DEBUG_SOLUTION_OUTPUT_ENABLE;
    /// __Boolean, default: "False"__\n
  bool LOCATE_CLOUD_RANGING_INPUT_ENABLE;
    /// __Integer, default: 33992, min/max 0/65535__\n
  int32_t LOCATE_CLOUD_RANGING_INPUT_PORT;
    /// __Integer, default: 5555, min/max 0/65535__\n
  int32_t LOCATE_CLOUD_RANGING_INPUT_IMU_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * LOCATE_CLOUD_RANGING_FORWARD_HOST;
    /// __Integer, default: 33992, min/max 0/65535__\n
  int32_t LOCATE_CLOUD_RANGING_FORWARD_PORT;
    /// __Boolean, default: "False"__\n
  bool LOCATE_CLOUD_RANGING_INPUT_LOG_ENABLE;
    /// __String, default: "cw-llc0"__\n
  const char * LLC_DEVICE_NAME;
    /// __Boolean, default: "False"__\n
  bool LLC_LOG_ENABLE;
    /// __Boolean, default: "False"__\n
  bool LLC_LOG_ALL;
    /// __String, default: ""__\n
  const char * LLC_LOG_REPLAY_FILENAME;
    /// __Integer, default: 5000, min/max 0/5000__\n
  int32_t LLC_LOG_BUFFER_MAX;
    /// __String, default: ""__\n
  const char * LOCATE_REPLAY_RAWRANGING_FILENAME;
    /// __Integer, default: 0, min/max 0/10000000__\n
  int32_t LOCATE_REPLAY_RAWRANGING_START_PACKET_NUM;
    /// __Integer, default: 2000000000, min/max 0/2000000000__\n
  int32_t LOCATE_REPLAY_RAWRANGING_END_PACKET_NUM;
    /// __Boolean, default: "True"__\n
  bool LOCATE_REPLAY_REALTIME;
    /// __Float, default: 0.0, min/max 0.0/0.99__\n
  float LOCATE_REPLAY_INTERPACKET_DELAY_SEC;
    /// __Integer, default: 0, min/max 0/10000000__\n
  int32_t LOCATE_REPLAY_INTERPACKET_DELAY_START_PACKET_NUM;
    /// __Boolean, default: "False"__\n
  bool LLC_FORWARD_ENABLE;
    /// __String, default: "127.0.0.1"__\n
  const char * LLC_FORWARD_HOST;
    /// __Integer, default: 37009, min/max 0/65535__\n
  int32_t LLC_FORWARD_PORT;
    /// __Boolean, default: "False"__\n
  bool RPS_LOG_ENABLE;
    /// __Integer, default: 0, min/max -1000/1000__\n
  int32_t EXTERNAL_DELAY_CORRECTION_FACTOR_ns;
    /// __Boolean, default: "False"__\n
  bool SITE_POSITION_IS_FIXED;
    /// __Integer, default: 0, min/max 0/2147483647__\n
  int32_t SITE_POSITION_MAPID;
    /// __Integer, default: 0, min/max 0/2147483647__\n
  int32_t SITE_POSITION_MAPVERSION;
    /// __Integer, default: 0, min/max 0/2147483647__\n
  int32_t SITE_POSITION_EDGEID;
    /// __Float, default: 0.0, min/max 0.0/1000000.0__\n
  float SITE_POSITION_RANGE_m;
    /// __Double, default: 0.0, min/max -90.0/90.0__\n
  double SITE_POSITION_WGS84_LATITUDE;
    /// __Double, default: 0.0, min/max -180.0/180.0__\n
  double SITE_POSITION_WGS84_LONGITUDE;
    /// __Float, default: 0.0, min/max -500.0/6144.0__\n
  float SITE_POSITION_WGS84_ELEVATION;
    /// __Boolean, default: "False"__\n
  bool SITE_POSITION_WGS84_USE_GPS;
    /// __Boolean, default: "False"__\n
  bool RPS_API_TEST_ENABLED;
    /// __Integer, default: 200, min/max 100/5000__\n
  int32_t RPS_API_TEST_UPDATE_PERIOD_ms;
    /// __Integer, default: 33993, min/max 0/65535__\n
  int32_t RPS_API_TEST_STATUS_PORT;
    /// __String, default: ""__\n
  const char * RPS_API_TEST_STATUS_HOST;
    /// __Integer, default: 0, min/max 0/2__\n
  int32_t RPS_REDPINE_TAG_EXPERIMENTAL;
    /// __Float, default: -210000.0, min/max -50000000.0/50000000.0__\n
  float RM_FTM_REDPINE_TAG_DELAY_ADJUST_ps;
    /// __Boolean, default: "False"__\n
  bool RM_FTM_REDPINE_TAG_EXPERIMENTAL_CHANEST_REQUEST;
    /// __Boolean, default: "False"__\n
  bool RM_FTM_REDPINE_TAG_PROBE_FAULTY_FIRMWARE;
    /// __Boolean, default: "False"__\n
  bool RM_DR_ENABLE;
    /// __Integer, default: 100, min/max 10/10000__\n
  int32_t RM_DR_REFERENCE_FRAME_PERIOD_ms;
    /// __String, default: "/dev/ttyUSB0"__\n
  const char * BNO_DEVICE_NAME;
    /// __Boolean, default: "False"__\n
  bool UBX_ENABLE;
    /// __Boolean, default: "False"__\n
  bool UBX_PCAP_LOG_ENABLE;
    /// __String, default: ""__\n
  const char * UBX_LOG_REPLAY_FILENAME;
    /// __Float, default: 0.1, min/max 0.0/1.0__\n
  float IMU_ORIENTATION_BETA;
    /// __Float, default: 0.0, min/max -100.0/100.0__\n
  float IMU_LA_VRP_TO_SENS_X_m;
    /// __Float, default: 0.0, min/max -100.0/100.0__\n
  float IMU_LA_VRP_TO_SENS_Y_m;
    /// __Float, default: 0.0, min/max -100.0/100.0__\n
  float IMU_LA_VRP_TO_SENS_Z_m;
    /// __Float, default: 0.0, min/max -180.0/180.0__\n
  float IMU_MA_VR_TO_SENS_ROLL_X_deg;
    /// __Float, default: 0.0, min/max -180.0/180.0__\n
  float IMU_MA_VR_TO_SENS_PITCH_Y_deg;
    /// __Float, default: 0.0, min/max -180.0/180.0__\n
  float IMU_MA_VR_TO_SENS_YAW_Z_deg;
    /// __Float, default: 0.002, min/max 0.0/1e+20__\n
  float IMU_STATIONARY_GYRO_THRESHOLD;
    /// __Float, default: 1.0, min/max 0.0/1e+20__\n
  float IMU_STATIONARY_ACCEL_THRESHOLD;
    /// __Integer, default: 5, min/max 0/100__\n
  int32_t IMU_STATIONARY_VIBRATION_HARMONIC_REMOVAL_COUNT;
    /// __Integer, default: 15, min/max 0/100__\n
  int32_t IMU_STATIONARY_CALIBRATION_START_DELAY;
    /// __Integer, default: 12, min/max 0/100__\n
  int32_t IMU_STATIONARY_CALIBRATION_END_DELAY;
    /// __Boolean, default: "False"__\n
  bool IMU_ATTITUDE_ESTIMATION_ENABLE;
    /// __Boolean, default: "False"__\n
  bool GPS_OUT_ENABLE;
    /// __Integer, default: 33992, min/max 0/65535__\n
  int32_t GPS_OUT_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * GPS_OUT_HOST;
    /// __Boolean, default: "False"__\n
  bool GPS_OUT_UBX_DEBUG;
    /// __Boolean, default: "False"__\n
  bool USE_IEEE1609_WSAS;
    /// __Integer, default: 5, min/max 0/3000__\n
  int32_t TARGET_PARAM_UPDATE_TIMEOUT_s;
    /// __String, default: "/mnt/ubi/locate/locate_config.json"__\n
  const char * LOCATE_CONFIG_FILE_NAME;
    /// __String, default: "/mnt/ubi/locate/locate_config_update.json"__\n
  const char * LOCATE_CONFIG_UPDATE_FILE_NAME;
    /// __Integer, default: 1, min/max 0/255__\n
  int32_t LOCATE_RPS_MODE;
    /// __Float, default: 0.0, min/max -50000000.0/50000000.0__\n
  float LOCATE_RPS_ACK_RESPONSE_DELAY_ADJUSTMENT_ps;
    /// __Integer, default: 1, min/max 0/65535__\n
  int32_t LOCATE_RPS_ACK_RESPONSE_DELAY_VARIANCE;
    /// __String, default: "127.0.0.1"__\n
  const char * LOCATE_POSOUTPUT_HOST;
    /// __Integer, default: 33994, min/max 0/65535__\n
  int32_t LOCATE_POSOUTPUT_PORT;
    /// __Boolean, default: "False"__\n
  bool LOCATE_POSOUTPUT_ENABLE;
    /// __Boolean, default: "False"__\n
  bool LOCATE_POSOUTPUT_LOG_ENABLE;
    /// __Boolean, default: "False"__\n
  bool RPS_EXIT_SEND_NO_FIX_TO_LPH;
    /// __Boolean, default: "False"__\n
  bool EXTERNAL_INPUT_ENABLE;
    /// __Boolean, default: "False"__\n
  bool EXTERNAL_INPUT_TYPE;
    /// __Integer, default: 3232, min/max 0/65535__\n
  int32_t EXTERNAL_INPUT_PORT;
    /// __Integer, default: 200, min/max 200/2000__\n
  int32_t EXTERNAL_INPUT_TIMEOUT_ms;
    /// __Boolean, default: "False"__\n
  bool LOCATE_VEHICLE_DIRECTION_FROM_IMU;
    /// __Boolean, default: "True"__\n
  bool TM_USE_RPS_ANNOUCEMENTS;
    /// __Boolean, default: "False"__\n
  bool TM_USE_BEACONS;
    /// __Boolean, default: "True"__\n
  bool TM_USE_TAG_PROBES;
    /// __Boolean, default: "False"__\n
  bool TM_USE_IEEE1609_WSAS;
    /// __Boolean, default: "False"__\n
  bool TM_USE_ETSI_SAEM;
    /// __Boolean, default: "False"__\n
  bool ETSI_DUAL_RADIO_MODE;
    /// __Hexidecimal, default: 0xe000001f, min/max 0x0/0xefffffff__\n
  uint32_t TM_LOCATE_SERVICE_pPSID;
    /// __Hexidecimal, default: 0x20409f, min/max 0x0/0xefffffff__\n
  uint32_t TM_LOCATE_SERVICE_PSID;
    /// __Boolean, default: "True"__\n
  bool TM_TRUST_UNKNOWN_DEVICES;
    /// __Boolean, default: "False"__\n
  bool RM_TAG_RX_SYNCHRONOUS_PROBE_ENABLE;
    /// __Integer, default: 1, min/max 1/10__\n
  int32_t RM_TAG_PROBE_BURST_COUNT;
    /// __Integer, default: 500, min/max 10/10000__\n
  int32_t RM_TAG_PROBE_PERIOD_ms;
    /// __Integer, default: -100, min/max -200/100__\n
  int32_t RM_TARGET_RSSI_LIMIT_dBm;
    /// __Boolean, default: "False"__\n
  bool RM_DIRECTIONAL_ANTENNAS;
    /// __Integer, default: 0, min/max 0/360__\n
  int32_t RM_ANTENNA_1_HEADING;
    /// __Integer, default: 0, min/max 0/360__\n
  int32_t RM_ANTENNA_2_HEADING;
    /// __Integer, default: 4, min/max 1/20__\n
  int32_t RM_DIRECTIONAL_RSSI_DELTA_dBm;
    /// __Boolean, default: "False"__\n
  bool LOCATE_PROXIMITY_AWARENESS_ENABLE;
    /// __Boolean, default: "True"__\n
  bool LOCATE_PROXIMITY_DIRECTION_FILTERING;
    /// __Float, default: 0.2, min/max 0.1/100.0__\n
  float LOCATE_PROXIMITY_UPDATE_PERIOD_s;
    /// __Float, default: 5.0, min/max 0.1/100.0__\n
  float LOCATE_PROXIMITY_DEVICE_PERIOD_s;
    /// __Float, default: 0.0, min/max 0.0/1000.0__\n
  float LOCATE_PROXIMITY_BAND0_LIMIT_m;
    /// __Float, default: 30.0, min/max 0.0/1000.0__\n
  float LOCATE_PROXIMITY_BAND1_LIMIT_m;
    /// __Float, default: 60.0, min/max 0.0/1000.0__\n
  float LOCATE_PROXIMITY_BAND2_LIMIT_m;
    /// __Integer, default: 33994, min/max 0/65535__\n
  int32_t PAM_STATUS_OUTPUT_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * PAM_STATUS_OUTPUT_HOST;
    /// __Integer, default: 0, min/max 0/65535__\n
  int32_t PAM_STATUS_OUTPUT_PORT_ALT;
    /// __String, default: "127.0.0.1"__\n
  const char * PAM_STATUS_OUTPUT_HOST_ALT;
    /// __Integer, default: 16384, min/max 128/65535__\n
  int32_t PAM_STATUS_OUTPUT_MAX_MSG_SIZE_BYTES;
    /// __Integer, default: 33994, min/max 0/65535__\n
  int32_t POS_STATUS_OUTPUT_PORT;
    /// __String, default: "127.0.0.1"__\n
  const char * POS_STATUS_OUTPUT_HOST;
    /// __Integer, default: 0, min/max 0/2__\n
  int32_t MULTI_DEVICE_ROLE;
    /// __String, default: ""__\n
  const char * MULTI_DEVICE_MASTER_HOST;
    /// __Integer, default: 33991, min/max 0/65535__\n
  int32_t MULTI_DEVICE_MASTER_PORT;
    /// __String, default: ""__\n
  const char * ASSOCIATED_DEVICE_EUI_ID_0;
    /// __String, default: ""__\n
  const char * ASSOCIATED_DEVICE_EUI_ID_1;
    /// __String, default: ""__\n
  const char * ASSOCIATED_DEVICE_EUI_ID_2;
    /// __String, default: ""__\n
  const char * ASSOCIATED_DEVICE_EUI_ID_3;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t ASSOCIATED_DEVICE_ASSOCIATION_RELATIONSHIP_0;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t ASSOCIATED_DEVICE_ASSOCIATION_RELATIONSHIP_1;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t ASSOCIATED_DEVICE_ASSOCIATION_RELATIONSHIP_2;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t ASSOCIATED_DEVICE_ASSOCIATION_RELATIONSHIP_3;
    /// __Boolean, default: "False"__\n
  bool ASSOCIATED_DEVICE_ASSOCIATION_TYPE_0;
    /// __Boolean, default: "False"__\n
  bool ASSOCIATED_DEVICE_ASSOCIATION_TYPE_1;
    /// __Boolean, default: "False"__\n
  bool ASSOCIATED_DEVICE_ASSOCIATION_TYPE_2;
    /// __Boolean, default: "False"__\n
  bool ASSOCIATED_DEVICE_ASSOCIATION_TYPE_3;
} tCohda_RPS;
/// Configuration parameters for Cohda_RSICN
typedef struct Cohda_RSICN
{
    /// __Boolean, default: "True"__\n
  bool Enable;
    /// __Integer, default: 1000, min/max 0/99999__\n
  int32_t IgnoreRange_m;
    /// __Float, default: 1.5, min/max 0.0/99.9__\n
  float LocationTolerance_m;
    /// __Float, default: 8.0, min/max 0.1/99.9__\n
  float DefaultRadius_m;
} tCohda_RSICN;
/// Configuration parameters for Cohda_TIM
typedef struct Cohda_TIM
{
    /// __Boolean, default: "True"__\n
  bool Enable;
    /// __Integer, default: 1000, min/max 0/99999__\n
  int32_t IgnoreRange_m;
    /// __Float, default: 1.5, min/max 0.0/99.9__\n
  float LocationTolerance_m;
    /// __Float, default: 8.0, min/max 0.1/99.9__\n
  float DefaultLaneWidth_m;
} tCohda_TIM;
/// Configuration parameters for Cohda_TM
typedef struct Cohda_TM
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
    /// __Integer, default: 5, min/max 1/100__\n
  int32_t AlertQueueDepth;
    /// __Integer, default: 10, min/max 0/255__\n
  int32_t MinLevelDelta;
    /// __Integer, default: 3, min/max 1/10__\n
  int32_t NumParallelVerifies;
    /// __Integer, default: 1, min/max -1/2__\n
  int32_t schedulerPolicy;
    /// __Integer, default: 20, min/max 0/100__\n
  int32_t schedulerPriority_pc;
    /// __Integer, default: 0, min/max -1/255__\n
  int32_t RepeatPeriod_Seconds;
    /// __Integer, default: 1, min/max 0/255__\n
  int32_t AlertUpdate_Seconds;
    /// __Integer, default: 5, min/max 1/255__\n
  int32_t AlertExpiry_Seconds;
} tCohda_TM;
/// Configuration parameters for Cohda_UBX
typedef struct Cohda_UBX
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
    /// __String, default: "/dev/ttymxc4"__\n
  const char * DEV_FILE;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t UBX_DEVICE_TYPE;
} tCohda_UBX;
/// Configuration parameters for Cohda_VS
typedef struct Cohda_VS
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
    /// __Integer, default: 12, min/max 1/99__\n
  int32_t MaxReaders;
    /// __Integer, default: 0, min/max 0/10220__\n
  int32_t VehLength;
    /// __Integer, default: 0, min/max 0/1023__\n
  int32_t VehWidth;
    /// __Integer, default: 0, min/max 0/127__\n
  int32_t BmprHghtFnt;
    /// __Integer, default: 0, min/max 0/127__\n
  int32_t BmprHghtRear;
    /// __Integer, default: 0, min/max 0/127__\n
  int32_t VehHght;
    /// __Integer, default: 0, min/max 0/3401__\n
  int32_t VehMass;
    /// __Integer, default: 0, min/max 0/255__\n
  int32_t VehType;
    /// __Integer, default: 1, min/max 0/4__\n
  int32_t VehLayout;
    /// __Integer, default: 0, min/max 0/3__\n
  int32_t Transmission;
    /// __Integer, default: 0, min/max 0/2__\n
  int32_t DrivingSide;
    /// __Integer, default: 100, min/max 1/100__\n
  int32_t HeightLonCarrLeft_cm;
    /// __Integer, default: 100, min/max 1/100__\n
  int32_t HeightLonCarrRight_cm;
    /// __Integer, default: 127, min/max 1/127__\n
  int32_t PosLonCarrLeft_cm;
    /// __Integer, default: 127, min/max 1/127__\n
  int32_t PosLonCarrRight_cm;
    /// __Integer, default: 3, min/max 1/4__\n
  int32_t PositionOfPillars_count;
    /// __Integer, default: 300, min/max 10/300__\n
  int32_t PositionOfPillarA_cm;
    /// __Integer, default: 300, min/max 10/300__\n
  int32_t PositionOfPillarB_cm;
    /// __Integer, default: 300, min/max 10/300__\n
  int32_t PositionOfPillarC_cm;
    /// __Integer, default: 300, min/max 10/300__\n
  int32_t PositionOfPillarD_cm;
    /// __Integer, default: 630, min/max 10/630__\n
  int32_t PosCentMass_cm;
    /// __Integer, default: 1270, min/max 10/1270__\n
  int32_t WheelBaseVehicle_cm;
    /// __Integer, default: 10200, min/max 40/10200__\n
  int32_t TurningRadius_cm;
    /// __Integer, default: 200, min/max 10/200__\n
  int32_t PosFrontAx_cm;
    /// __Integer, default: 100, min/max 0/10000__\n
  int32_t EVENT_HAZARDLIGHT_DURATION;
    /// __Integer, default: 300, min/max 0/10000__\n
  int32_t EVENT_AIRBAG_DURATION;
    /// __Integer, default: 100, min/max 0/10000__\n
  int32_t EVENT_ABS_DURATION;
    /// __Integer, default: 100, min/max 0/10000__\n
  int32_t EVENT_TRACTION_DURATION;
    /// __Integer, default: 100, min/max 0/10000__\n
  int32_t EVENT_SBC_DURATION;
    /// __Integer, default: 200, min/max 0/10000__\n
  int32_t HARD_BRAKING_DURATION;
    /// __Float, default: -4.0, min/max -99.9/99.9__\n
  float HARD_BRAKING_ACCEL_SET;
    /// __Float, default: -3.5, min/max -99.9/99.9__\n
  float HARD_BRAKING_ACCEL_UNSET;
    /// __Float, default: 1.0, min/max 0.0/1.0__\n
  float GPS_LONACCEL_FILTERGAIN;
    /// __Float, default: 1.0, min/max 0.0/1.0__\n
  float GPS_LATACCEL_FILTERGAIN;
    /// __Float, default: 1.0, min/max 0.0/1.0__\n
  float GPS_YAWRATE_FILTERGAIN;
    /// __Float, default: 0.522, min/max 0.0/1.0__\n
  float GRADE_SENSORACCEL_FILTERGAIN;
    /// __Float, default: 0.85, min/max 0.0/1.0__\n
  float GRADE_WHEELACCEL_FILTERGAIN;
    /// __Float, default: 0.105, min/max 0.0/1.0__\n
  float GRADE_GRADEACCEL_FILTERGAIN;
    /// __Integer, default: 3, min/max 0/360__\n
  int32_t GRADE_LATCH_SPEED;
    /// __Integer, default: 5, min/max 0/360__\n
  int32_t GRADE_UNLATCH_SPEED;
    /// __Integer, default: 2184, min/max 0/32767__\n
  int32_t VehSpd_TIME_OLD;
    /// __Integer, default: 300, min/max 0/65535__\n
  int32_t VehSpd_VALUE_ON;
    /// __Integer, default: 273, min/max 0/65535__\n
  int32_t VehSpd_TIME_ON;
    /// __Integer, default: 50, min/max 0/65535__\n
  int32_t VehSpd_VALUE_OFF;
    /// __Integer, default: 546, min/max 0/65535__\n
  int32_t VehSpd_TIME_OFF;
    /// __Integer, default: 100, min/max 0/10000__\n
  int32_t CommitPeriod_mS;
    /// __Integer, default: 500, min/max 0/10000__\n
  int32_t PlausibilityPeriod_mS;
    /// __Integer, default: 1000, min/max 0/10000__\n
  int32_t PurgePeriod_mS;
} tCohda_VS;
/// Configuration parameters for J2945CC
typedef struct J2945CC
{
    /// __Integer, default: -1, min/max -1/255__\n
  int32_t DebugLevel;
} tJ2945CC;
/// Configuration parameters for SAEC
typedef struct SAEC
{
    /// __Boolean, default: "False"__\n
  bool Security;
    /// __Hexidecimal, default: 0x2, min/max 0x0/0xffffffff__\n
  uint32_t Security_CMH_ID;
    /// __Integer, default: 30, min/max 0/65535__\n
  int32_t Security_Acceptable_Past_Time;
    /// __Integer, default: 30, min/max 0/65535__\n
  int32_t Security_Acceptable_Future_Time;
    /// __Boolean, default: "False"__\n
  bool Security_SendUnsecuredHeader;
    /// __Integer, default: 450, min/max 0/65535__\n
  int32_t Security_Certificate_Interval;
    /// __Integer, default: 2000, min/max 0/65535__\n
  int32_t Security_IdChangeDistance_m;
    /// __Integer, default: 300, min/max 0/65535__\n
  int32_t Security_IdChangeInterval_s;
    /// __Boolean, default: "False"__\n
  bool TCIA_Enabled;
    /// __Integer, default: 182, min/max 150/184__\n
  int32_t DSMP_ChannelNumber;
    /// __Integer, default: 10, min/max 0/65535__\n
  int32_t DSMP_ChannelWidth_mhz;
    /// __Integer, default: 24, min/max 0/65535__\n
  int32_t DSMP_TxPower_dBm;
    /// __Integer, default: 1, min/max 0/5__\n
  int32_t DSMP_LLIF;
    /// __String, default: "04:e5:48:00:00:01"__\n
  const char * MACAddr;
    /// __String, default: "eth0"__\n
  const char * EthInterface;
    /// __String, default: "saec0"__\n
  const char * EthLinkName;
    /// __Hexidecimal, default: 0x8444, min/max 0x0/0xffff__\n
  uint32_t EtherType;
    /// __Integer, default: 1398, min/max 0/65535__\n
  int32_t DSMP_MaxPduSize;
    /// __Boolean, default: "True"__\n
  bool BSM_Enabled;
    /// __Integer, default: 10, min/max 0/255__\n
  int32_t BSM_BasicVehicleClass;
    /// __Integer, default: 100, min/max 50/1000__\n
  int32_t BSM_Interval;
    /// __Integer, default: 111, min/max 0/65536__\n
  int32_t BSM_NoCriticalEvent_AID;
    /// __Integer, default: 112, min/max 0/65536__\n
  int32_t BSM_CriticalEvent_AID;
    /// __Integer, default: 113, min/max 0/65536__\n
  int32_t BSM_EmergencyVehicle_NoCriticalEvent_AID;
    /// __Integer, default: 114, min/max 0/65536__\n
  int32_t BSM_EmergencyVehicle_CriticalEvent_AID;
    /// __Integer, default: 3618, min/max 0/65536__\n
  int32_t MAP_AID;
    /// __Integer, default: 3619, min/max 0/65536__\n
  int32_t SPAT_AID;
    /// __Integer, default: 3620, min/max 0/65536__\n
  int32_t RSI_Static_AID;
    /// __Integer, default: 3621, min/max 0/65536__\n
  int32_t RSI_SemiDynamic_AID;
    /// __Integer, default: 3622, min/max 0/65536__\n
  int32_t RSI_Dynamic_AID;
    /// __Integer, default: 3623, min/max 0/65536__\n
  int32_t RSM_AID;
    /// __Hexidecimal, default: 0xffffffff, min/max 0x0/0xffffffff__\n
  uint32_t FacilitiesStationID;
    /// __String, default: "00:00:00:00:00:01"__\n
  const char * LocalAddr;
    /// __Integer, default: 2, min/max 0/2__\n
  int32_t LocalAddrConfMethod;
    /// __Boolean, default: "False"__\n
  bool IMT2020_Enabled;
    /// __String, default: "NLLST426"__\n
  const char * IMT2020_StationID;
} tSAEC;
/// Configuration parameters for SAEC_TRX
typedef struct SAEC_TRX
{
    /// __Boolean, default: "True"__\n
  bool Enabled;
    /// __Boolean, default: "True"__\n
  bool PeriodicExtrapolatePosition;
    /// __Boolean, default: "False"__\n
  bool PostUnknownToExt;
} tSAEC_TRX;


typedef struct IniFile
{
  /// File that contains the pre-recorded file to play back from\n
  /// __String, default: ""__\n
  const char *   PreRecFileName;
  /// -1 = The default is deliberately invalid.\n
  /// You must override this value!\n
  /// Initialise Dual Stack with ...\n
  /// # 0 = ITS\n
  /// # 1 = 1609\n
  /// # 2 = SAEC\n
  /// __Integer, default: -1, min/max: -1/15__\n
  int32_t  ProtocolMode;
  /// # 0 = Both disabled\n
  /// # 1 = Tx only enabled\n
  /// # 2 = Rx only enabled\n
  /// # 3 = Tx and Rx enabled\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  EnableTxRx;
  /// Source MAC Address. e.g. 04:e5:48:00:00:00\n
  /// __String, default: ""__\n
  const char *   MACAddr;
  /// Valid values: -10 to 33 in increments of 1 dBm\n
  /// Default setting; may be overridden in WSMP requests\n
  /// __Integer, default: 24, min/max: -10/33__\n
  int32_t  TxPwrLevel_dBm;
  /// In units of 500 kbit/s (eg 12=6Mbps)\n
  /// Valid values:\n
  /// #  6 =   3Mbps\n
  /// #  9 = 4.5Mbps\n
  /// # 12 =   6Mbps\n
  /// # 18 =   9Mbps\n
  /// # 24 =  12Mbps\n
  /// # 36 =  18Mbps\n
  /// # 48 =  24Mbps\n
  /// # 54 =  28Mbps\n
  /// __Integer, default: 12, min/max: 6/54__\n
  int32_t  TxDataRate;
  /// CWmin = 2^4 - 1\n
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  AC_BE_CWminKVal;
  /// CWmax = 2^10 - 1\n
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  AC_BE_CWmaxKVal;
  /// __Integer, default: 6, min/max: 2/15__\n
  int32_t  AC_BE_AIFSN;
  /// CWmin = 2^4 - 1\n
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  AC_BK_CWminKVal;
  /// CWmax = 2^10 - 1\n
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  AC_BK_CWmaxKVal;
  /// __Integer, default: 9, min/max: 2/15__\n
  int32_t  AC_BK_AIFSN;
  /// CWmin = 2^4 - 1. J2945/1 2016 [6.3.4-V2V-BSMTX-UPEDCA-03]\n
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  AC_VI_CWminKVal;
  /// CWmax = 2^10 - 1\n
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  AC_VI_CWmaxKVal;
  /// __Integer, default: 4, min/max: 2/15__\n
  int32_t  AC_VI_AIFSN;
  /// CWmin = 2^2 - 1. J2945/1 2016 [6.3.4-V2V-BSMTX-UPEDCA-03]\n
  /// __Integer, default: 2, min/max: 1/10__\n
  int32_t  AC_VO_CWminKVal;
  /// CWmax = 2^3 - 1\n
  /// __Integer, default: 3, min/max: 1/10__\n
  int32_t  AC_VO_CWmaxKVal;
  /// __Integer, default: 2, min/max: 2/15__\n
  int32_t  AC_VO_AIFSN;
  /// 1609 Safety channel transmit antenna selection\n
  /// # 0 = Default\n
  /// # 1 = ANT1\n
  /// # 2 = ANT2\n
  /// # 3 = ANT1 + ANT2 (diversity)\n
  /// NOTE: In dual-radio use cases actually each radio uses\n
  /// only one antenna (e.g. for ETSI when @ref ItsG5TransceiverConfig = 2)\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  TxAntenna;
  /// 1609 Safety channel receive antenna selection\n
  /// # 0 = Default\n
  /// # 1 = ANT1\n
  /// # 2 = ANT2\n
  /// # 3 = ANT1 + ANT2 (diversity)\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  RxAntenna;
  /// Carrier Sense Threshold\n
  /// __Integer, default: -65, min/max: -95/-65__\n
  int32_t  CSThreshold_dBm;
  /// Channel Busy Ratio Threshold\n
  /// __Integer, default: -85, min/max: -95/-65__\n
  int32_t  CBRThreshold_dBm;
  /// __Integer, default: 24, min/max: -10/33__\n
  int32_t  CCH_TxPwrLevel_dBm;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  CCH_AC_BE_CWminKVal;
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  CCH_AC_BE_CWmaxKVal;
  /// __Integer, default: 6, min/max: 2/15__\n
  int32_t  CCH_AC_BE_AIFSN;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  CCH_AC_BK_CWminKVal;
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  CCH_AC_BK_CWmaxKVal;
  /// __Integer, default: 9, min/max: 2/15__\n
  int32_t  CCH_AC_BK_AIFSN;
  /// __Integer, default: 3, min/max: 1/10__\n
  int32_t  CCH_AC_VI_CWminKVal;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  CCH_AC_VI_CWmaxKVal;
  /// __Integer, default: 3, min/max: 2/15__\n
  int32_t  CCH_AC_VI_AIFSN;
  /// __Integer, default: 2, min/max: 1/10__\n
  int32_t  CCH_AC_VO_CWminKVal;
  /// __Integer, default: 3, min/max: 1/10__\n
  int32_t  CCH_AC_VO_CWmaxKVal;
  /// __Integer, default: 2, min/max: 2/15__\n
  int32_t  CCH_AC_VO_AIFSN;
  /// 1609/ETSI Control channel transmit antenna selection @sa TxAntenna\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  CCH_TxAntenna;
  /// 1609/ETSI Control channel receive antenna selection @sa RxAntenna\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  CCH_RxAntenna;
  /// Dual Tx Control, as per LLC\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  CCH_DualTxControl;
  /// __Integer, default: 24, min/max: -10/33__\n
  int32_t  SCH_TxPwrLevel_dBm;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  SCH_AC_BE_CWminKVal;
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  SCH_AC_BE_CWmaxKVal;
  /// __Integer, default: 6, min/max: 2/15__\n
  int32_t  SCH_AC_BE_AIFSN;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  SCH_AC_BK_CWminKVal;
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  SCH_AC_BK_CWmaxKVal;
  /// __Integer, default: 9, min/max: 2/15__\n
  int32_t  SCH_AC_BK_AIFSN;
  /// __Integer, default: 3, min/max: 1/10__\n
  int32_t  SCH_AC_VI_CWminKVal;
  /// __Integer, default: 4, min/max: 1/10__\n
  int32_t  SCH_AC_VI_CWmaxKVal;
  /// __Integer, default: 3, min/max: 2/15__\n
  int32_t  SCH_AC_VI_AIFSN;
  /// __Integer, default: 2, min/max: 1/10__\n
  int32_t  SCH_AC_VO_CWminKVal;
  /// __Integer, default: 3, min/max: 1/10__\n
  int32_t  SCH_AC_VO_CWmaxKVal;
  /// __Integer, default: 2, min/max: 2/15__\n
  int32_t  SCH_AC_VO_AIFSN;
  /// 1609/ETSI Service channel transmit antenna selection @sa TxAntenna\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  SCH_TxAntenna;
  /// 1609/ETSI Service channel receive antenna selection @sa RxAntenna\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  SCH_RxAntenna;
  /// Dual Tx Control, as per LLC\n
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  SCH_DualTxControl;
  /// Enables / Disables the security functionality\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     SecurityEnable;
  /// Enables / Disables transmitting BSMs with unsecured\n
  /// Dot 2 header if security is disabled\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     SendUnsecuredDot2Header;
  /// Interval in seconds for verfying security credentials\n
  /// __Integer, default: 1, min/max: 1/60__\n
  int32_t  VerificationInterval_s;
  /// This is intended to add some jitter to the verity interval such\n
  /// that messages from the same OBE are not always the ones verified.\n
  /// __Integer, default: 100, min/max: 0/1000__\n
  int32_t  VerificationJitter_ms;
  /// Indicates if message processing, parsing, and logging should continue\n
  /// if message verification fails.\n
  /// 0 = False, stop\n
  /// 1 = True, continue\n
  /// __Boolean, default: False__\n
  bool     VerFailMsgParseFlag;
  /// Randomize the radio MAC address with a certificate change.\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     RandMAC;
  /// Randomize the J2735 Temporary ID with a certificate change.\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     RandTemporaryID;
  /// Randomize the J2735 message count with a certificate change.\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     RandMsgCount;
  /// PSID for P2P certificate distribution messages\n
  /// __Hex, default: 0x8008, min/max: 0x0/0xefffffff__\n
  uint32_t P2PCertPSID;
  /// Destination MAC Address\n
  /// __String, default: "ff:ff:ff:ff:ff:ff"__\n
  const char *   WSMP_DA;
  /// Priority\n
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  WSMP_Priority;
  /// The radio channel used for the WSM, TCH on R1C\n
  /// __Integer, default: 172, min/max: 150/184__\n
  int32_t  WSMP_ChannelNumber;
  /// The data rate used for the WSM.\n
  /// __Integer, default: 12, min/max: 6/54__\n
  int32_t  WSMP_DataRate;
  /// The transmit power used for the WSM [dBm] (J2945/1 2016 Table 21)\n
  /// __Integer, default: 24, min/max: 0/33__\n
  int32_t  WSMP_TxPower;
  /// Expiry Time (I think this is the 1-byte field in Dot3WSMPHdr)\n
  /// __Hex, default: 0x0, min/max: 0x0/0xff__\n
  uint32_t WSMP_ExpiryTime;
  /// The WAVE element ID: WSMP=0x80 or WSMP-S=0x81\n
  /// __Hex, default: 0x80, min/max: 0x80/0x81__\n
  uint32_t WSMP_WAVEElementId;
  /// The MAX WSM payload length as per 1609.3 standard requirements.\n
  /// __Integer, default: 1400, min/max: 0/2302__\n
  int32_t  WSMMaxLength;
  /// PSID Length: Valid Values\n
  /// 1 byte:  00 - 7F\n
  /// 2 bytes: 8000 - BFFF\n
  /// 3 bytes: C00000 - DFFFFF\n
  /// 4 bytes: E0000000 - EFFFFFFF\n
  /// DISABLE (0xOFF) to use Cohda_Additional_Secure_PSID_# instead\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t BSMUnsecurePSID;
  /// Same valid values as for BSMUnsecurePSID\n
  /// __Hex, default: 0x20, min/max: 0x0/0xefffffff__\n
  uint32_t BSMSecurePSID;
  /// 0, 3 = AC_BE (Best Effort)\n
  /// 1, 2 = AC_BK (Bkgrnd)\n
  /// 4, 5 = AC_VI (Video)\n
  /// 6, 7 = AC_VO (Voice)\n
  /// __Integer, default: 5, min/max: 0/7__\n
  int32_t  BSMUserPriorityNoCriticalEvent;
  /// 0, 3 = AC_BE (Best Effort)\n
  /// 1, 2 = AC_BK (Bkgrnd)\n
  /// 4, 5 = AC_VI (Video)\n
  /// 6, 7 = AC_VO (Voice)\n
  /// __Integer, default: 7, min/max: 0/7__\n
  int32_t  BSMUserPriorityCriticalEvent;
  /// Enables / Disables adding the safety supplement data to the WSM header\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     WSMPSafetySuppSupport;
  /// The safety supplement data to be included in the safety supplement fields\n
  /// __Hex, default: 0x1, min/max: 0x0/0x7fffffff__\n
  uint32_t WSMPSafetySuppData;
  /// Remote host to send / receive WSMP packets over UDP to / from\n
  /// __String, default: ""__\n
  const char *   WSMPUDPBypassHost;
  /// Remote port number to send / receive WSMP packets UDP to / from\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMPUDPBypassPort;
  /// Provider WSA transmission master enable\n
  /// 0 = Disabled (will not request provider service WSA)\n
  /// 1 = Enabled\n
  /// __Boolean, default: True__\n
  bool     WSATxEnable;
  /// WSA RCPI Hysteresis Margin (in units of 0.5 dB)\n
  /// __Integer, default: 20, min/max: 10/200__\n
  int32_t  WSARCPIHysteresisMargin;
  /// Include Repeat Rate extension in WSA Tx?\n
  /// __Boolean, default: True__\n
  bool     WSAIncludeRepeatRateExt;
  /// Include 2D Location extension in WSA Tx?\n
  /// __Boolean, default: False__\n
  bool     WSAInclude2DLocationExt;
  /// Include 3D Location extension in WSA Tx?\n
  /// __Boolean, default: True__\n
  bool     WSAInclude3DLocationExt;
  /// Include Advertiser ID extension in WSA Tx?\n
  /// __Boolean, default: True__\n
  bool     WSAIncludeAdvertiserIDExt;
  /// __String, default: "Cohda"__\n
  const char *   WSAAdvertiserID;
  /// Include Channel Access extension in WSA Tx?\n
  /// __Boolean, default: True__\n
  bool     WSAIncludeChanAccExt;
  /// Include EDCA Parameters extension in WSA Tx?\n
  /// __Boolean, default: False__\n
  bool     WSAIncludeEDCAExt;
  /// __Integer, default: 60, min/max: 0/65535__\n
  int32_t  WSARouterLifetime;
  /// 0 = None (interface inactive)\n
  /// # 1 = ETH\n
  /// # 2 = LLC_DSRC (MK5)\n
  /// # 3 = ATK_DSRC\n
  /// # 4 = QTI_CV2X\n
  /// # 5 = ATK_CV2X\n
  /// # 6 = LLC_DSRC_DUAL (MK6)\n
  /// __Integer, default: 1, min/max: 0/6__\n
  int32_t  WSMP_LLIF;
  /// CCH / SCH or empty to disable sending of TAs\n
  /// __String, default: ""__\n
  const char *   WME_TA_Channel;
  /// Repeat rate of TAs per 5 seconds (0=off, 1=0.2Hz, 5=1Hz, 10=2Hz, 25=5Hz, 50=10Hz)\n
  /// __Integer, default: 50, min/max: 0/50__\n
  int32_t  WME_TA_RepeatRate;
  /// # 0 = Continuous Channel\n
  /// # 1 = Chan Switch Alternating Forced\n
  /// # 2 = Chan Switch Alternating Conditional\n
  /// # 3 = Immediate and Extended\n
  /// # 4 = Single radio\n
  /// To run in single radio mode, the following config items must\n
  /// all be set to the same channel:\n
  /// WSMP_ChannelNumber\n
  /// ContinuousChanNum\n
  /// ForcedSerChanNum\n
  /// ForcedControlChanNum\n
  /// All the WBSS_Service_[X]_PSID should also be disabled (0x0FF)\n
  /// __Integer, default: 0, min/max: 0/4__\n
  int32_t  ChannelMode;
  /// Channel number to use when 'ChannelMode' is set to '0'\n
  /// Even channel number applicable to 10 MHz channels\n
  /// Odd channel numbers applicable to 20 MHz channels\n
  /// __Integer, default: 172, min/max: 1/184__\n
  int32_t  ContinuousChanNum;
  /// Service channel number to switch to when 'ChannelMode' is set to '1'\n
  /// Channel 178 invalid\n
  /// Even channel number applicable to 10 MHz channels\n
  /// Odd channel numbers applicable to 20 MHz channels\n
  /// __Integer, default: 184, min/max: 1/184__\n
  int32_t  ForcedSerChanNum;
  /// Control Channel number\n
  /// __Integer, default: 178, min/max: 1/184__\n
  int32_t  ForcedControlChanNum;
  /// Enables / Disables support for transmitting a BSM\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     BSMEnabled;
  /// BSM Transmit interval\n
  /// Valid values: 50, 100, 200, 300, ..., 1000 ms\n
  /// __Integer, default: 100, min/max: 50/1000__\n
  int32_t  BSMPartITxInterval_ms;
  /// BSM Transmit Offset\n
  /// Valid values: 0 (SAE J3161/1 6.3.8.8), 5 (SAE J2945/1 6.3.3)\n
  /// __Integer, default: 0, min/max: 0/5__\n
  int32_t  BSMPartITxRandOffset_ms;
  /// GPS X antenna offset in meters, defined according to SAE J670\n
  /// 81.91 = Unavailable\n
  /// __Float, default: 0.0, min/max: -81.91/81.91__\n
  float    AntAdjX_m;
  /// GPS Y antenna offset in meters, defined according to SAE J670\n
  /// 2.55 = Unavailable\n
  /// __Float, default: 0.0, min/max: -2.55/2.55__\n
  float    AntAdjY_m;
  /// GPS Z antenna offset in meters, defined according to SAE J670\n
  /// 8.191 = Unavailable\n
  /// #   -1.0 = The GPS antenna is 1m above the road surface\n
  /// __Float, default: 0.0, min/max: -8.191/8.191__\n
  float    AntAdjZ_m;
  /// Speed, in kph, below which the heading will be latched.\n
  /// SAE J2945_1 2016 [6.3.6-V2V-BSMTX-DATAACC-022]\n
  /// __Float, default: 4.0, min/max: 0.0/10.0__\n
  float    HeadingLatchSpeed_kph;
  /// Speed, in kph, above which heading will be unlatched\n
  /// SAE J2945_1 2016 [6.3.6-V2V-BSMTX-DATAACC-023]\n
  /// __Float, default: 5.0, min/max: 0.0/10.0__\n
  float    HeadingUnlatchSpeed_kph;
  /// Enables / Disables C2C heading latch feature\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     HeadingLatchSpeedWithConfidence;
  /// Speed, in kph, below which the heading will be latched if\n
  /// heading confidence is acceptable.\n
  /// __Float, default: 5.04, min/max: 0.0/10.0__\n
  float    HeadingLatchHigherSpeed_kph;
  /// Heading confidence, in degrees, above which the heading will be latched\n
  /// when speed is below the 'higher' latch speed. If heading confidence is\n
  /// below this value (i.e. worse), heading will only be latched at\n
  /// the 'lower' latch speed.\n
  /// __Float, default: 12.5, min/max: 0.0/360.0__\n
  float    HeadingLatchHeadingConf_deg;
  /// Enables / Disables persistently storing the heading at shutdown\n
  /// and using on startup\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     HeadingPersistency;
  /// Enables / Disables a default heading of 0 degree when heading\n
  /// cannot be loaded from persistent memory\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     HeadingUseDefault;
  /// Configues the number of minutes that persistent heading remains valid\n
  /// #  0 = Disabled\n
  /// #  1 = 1Min\n
  /// __Integer, default: 0, min/max: 0/10080__\n
  int32_t  HeadingPersistencyTime_Mins;
  /// Enables/sets the SAE Basic Vehicle Class to be added to BSM Part II\n
  /// 255 : not set (will not be included in BSM)\n
  /// 0-254 : included in BSM, set to that value (J2735 DE_BasicVehicleClass)\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  BSM_BasicVehicleClass;
  /// nested config for Cohda_PP
  tCohda_PP Cohda_PP;
  /// nested config for Cohda_PH
  tCohda_PH Cohda_PH;
  /// nested config for J2945CC
  tJ2945CC J2945CC;
  /// Size limit [MB] of pcap logs\n
  /// #  0 = No limit\n
  /// __Integer, default: 0, min/max: 0/2000__\n
  int32_t  PcapLogSizeLimit;
  /// Support logging of the stats log data\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     StatsLogEnableFlag;
  /// Short description (<=32) for pcap metadata\n
  /// __String, default: ""__\n
  const char *   ShortDescription;
  /// Capture log writing metrics\n
  /// __Boolean, default: False__\n
  bool     PcapWriteMetrics;
  /// Capture log writing data\n
  /// __Boolean, default: False__\n
  bool     PcapWriteCounters;
  /// Support logging of the Tx log data from Radio A\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     TxALogEnableFlag;
  /// Filename to log for Tx log data for radio A\n
  /// __String, default: "tx_r1a.pcap"__\n
  const char *   TxALogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// Tx log data for radio A when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  TxALogNumFiles;
  /// Size limit [MB] of tcpdump log for Tx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  TxALogSizeLimit;
  /// Time limit [s] of tcpdump log for Tx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  TxALogTimeLimit;
  /// Time [s] before rotating of tcpdump log for Tx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  TxALogRotateTime;
  /// Support logging of the Tx log data from Radio B\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     TxBLogEnableFlag;
  /// Filename to log for Tx log data for radio B\n
  /// __String, default: "tx_r1c.pcap"__\n
  const char *   TxBLogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// Tx log data for radio B when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  TxBLogNumFiles;
  /// Size limit [MB] of tcpdump log for Tx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  TxBLogSizeLimit;
  /// Time limit [s] of tcpdump log for Tx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  TxBLogTimeLimit;
  /// Time [s] before rotating of tcpdump log for Tx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  TxBLogRotateTime;
  /// Support logging of the Rx log data from Radio A\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     RxALogEnableFlag;
  /// Filename to log for Rx log data for radio A\n
  /// __String, default: "rx_r1a.pcap"__\n
  const char *   RxALogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// Rx log data for radio A when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  RxALogNumFiles;
  /// Size limit [MB] of tcpdump log for Rx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  RxALogSizeLimit;
  /// Time limit [s] of tcpdump log for Rx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  RxALogTimeLimit;
  /// Time [s] before rotating of tcpdump log for Rx on Radio A\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  RxALogRotateTime;
  /// Support logging of the Rx log data from Radio B\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: True__\n
  bool     RxBLogEnableFlag;
  /// Filename to log for Rx log data for radio B\n
  /// __String, default: "rx_r1c.pcap"__\n
  const char *   RxBLogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// Rx log data for radio B when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  RxBLogNumFiles;
  /// Size limit [MB] of tcpdump log for Rx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  RxBLogSizeLimit;
  /// Time limit [s] of tcpdump log for Rx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  RxBLogTimeLimit;
  /// Time [s] before rotating of tcpdump log for Rx on Radio B\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  RxBLogRotateTime;
  /// Support logging of the Tx (over the air) log data\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     OTALogEnableFlag;
  /// Filename to log for Tx (over the air) log data\n
  /// __String, default: "tx_ota.pcap"__\n
  const char *   OTALogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// Tx (over the air) data when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  OTALogNumFiles;
  /// Size limit [MB] of tcpdump log for Tx (over the air) data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  OTALogSizeLimit;
  /// Time limit [s] of tcpdump log for Tx (over the air) data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  OTALogTimeLimit;
  /// Time [s] before rotating of tcpdump log for Tx (over the air) data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  OTALogRotateTime;
  /// Support pcap logging of the rsyslog data\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     SSLLogEnableFlag;
  /// Filename to log for the rsyslog data\n
  /// __String, default: "ssl.pcap"__\n
  const char *   SSLLogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// rsyslog data when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  SSLLogNumFiles;
  /// Size limit [MB] of tcpdump log for the rsyslog data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  SSLLogSizeLimit;
  /// Time limit [s] of tcpdump log for the rsyslog data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  SSLLogTimeLimit;
  /// Time [s] before rotating of tcpdump log for the rsyslog data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  SSLLogRotateTime;
  /// Support pcap logging of the modbus data\n
  /// 0 = False\n
  /// 1 = True\n
  /// __Boolean, default: False__\n
  bool     GenLogEnableFlag;
  /// Interface name\n
  /// __String, default: "eth0"__\n
  const char *   GenTcpDumpInterface;
  /// Filters\n
  /// __String, default: "port 502"__\n
  const char *   GenTcpDumpFilter;
  /// Filename to log for the modbus data\n
  /// __String, default: "modbus.pcap"__\n
  const char *   GenLogFileName;
  /// Limit the number of files created by tcpdump for\n
  /// modbus data when rotating to this\n
  /// number - when limit reached, tcpdump will reuse\n
  /// old files by overwriting in a 'rotating' buffer\n
  /// # 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  GenLogNumFiles;
  /// Size limit [MB] of tcpdump log for the modbus data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/4000__\n
  int32_t  GenLogSizeLimit;
  /// Time limit [s] of tcpdump log for the modbus data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  GenLogTimeLimit;
  /// Time [s] before rotating of tcpdump log for the modbus data\n
  /// #  0 = No limit\n
  /// 1... =\n
  /// __Integer, default: 0, min/max: 0/31622400__\n
  int32_t  GenLogRotateTime;
  /// Syslog level to capture (this and anything below)\n
  /// 1 = Emergency\n
  /// 2 = Alert\n
  /// 3 = Critical\n
  /// 4 = Error\n
  /// 5 = Warning\n
  /// 6 = Notice\n
  /// 7 = Info\n
  /// 8 = Debug\n
  /// __Integer, default: 7, min/max: 1/8__\n
  int32_t  Cohda_Syslog_DebugLevel;
  /// cron-like format time to close, and rotate syslog file\n
  /// supports a single value or * for each element only\n
  /// minute hour day-of-month month-of-year weekday\n
  /// if unset syslog is never rotated\n
  /// __String, default: ""__\n
  const char *   Cohda_Syslog_RotateTime;
  /// cron format time to purge old syslog files\n
  /// supports a single value or * for each element only\n
  /// minute hour day-of-month month-of-year weekday\n
  /// if unset syslog is never rotated\n
  /// __String, default: ""__\n
  const char *   Cohda_Syslog_PurgeTime;
  /// Maximum age of syslog files before they are eligible\n
  /// for purging in seconds - default of 4 weeks\n
  /// 0 means to never purge\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  Cohda_Syslog_PurgeAge_hours;
  /// # 0 = User\n
  /// # 1 = Provider\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_Mode;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: True__\n
  bool     WBSS_Service_0_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_0_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_0_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: "SCH"__\n
  const char *   WBSS_Service_0_ChanId;
  /// \n
  /// __Integer, default: 31, min/max: 0/31__\n
  int32_t  WBSS_Service_0_Prio;
  /// PSID valid values\n
  /// 1 byte:  00 - 7F\n
  /// DISABLED (off): 0FF\n
  /// 2 bytes: 8000 - BFFF\n
  /// 3 bytes: C00000 - DFFFFF\n
  /// 4 bytes: E0000000 - EFFFFFFF#\n
  /// __Hex, default: 0xeffffffe, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_0_PSID;
  /// __String, default: "IPv6"__\n
  const char *   WBSS_Service_0_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_0_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_0_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_0_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_0_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: True__\n
  bool     WBSS_Service_1_IPService;
  /// __String, default: "c0da::1"__\n
  const char *   WBSS_Service_1_IPAddress;
  /// __Integer, default: 16092, min/max: 0/65535__\n
  int32_t  WBSS_Service_1_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: "SCH"__\n
  const char *   WBSS_Service_1_ChanId;
  /// \n
  /// __Integer, default: 31, min/max: 0/31__\n
  int32_t  WBSS_Service_1_Prio;
  /// \n
  /// __Hex, default: 0x23, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_1_PSID;
  /// __String, default: "SCMS"__\n
  const char *   WBSS_Service_1_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_1_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_1_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_1_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_1_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_2_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_2_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_2_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_2_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_2_Prio;
  /// \n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_2_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_2_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_2_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_2_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_2_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_2_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_3_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_3_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_3_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_3_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_3_Prio;
  /// \n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_3_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_3_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_3_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_3_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_3_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_3_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_4_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_4_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_4_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_4_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_4_Prio;
  /// \n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_4_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_4_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_4_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_4_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_4_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_4_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_5_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_5_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_5_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_5_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_5_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_5_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_5_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_5_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_5_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_5_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_5_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_6_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_6_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_6_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_6_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_6_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_6_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_6_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_6_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_6_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_6_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_6_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_7_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_7_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_7_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_7_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_7_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_7_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_7_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_7_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_7_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_7_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_7_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_8_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_8_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_8_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_8_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_8_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_8_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_8_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_8_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_8_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_8_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_8_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_9_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_9_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_9_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_9_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_9_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_9_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_9_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_9_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_9_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_9_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_9_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_10_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_10_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_10_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_10_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_10_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_10_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_10_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_10_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_10_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_10_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_10_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_11_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_11_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_11_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_11_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_11_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_11_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_11_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_11_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_11_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_11_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_11_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_12_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_12_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_12_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_12_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_12_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_12_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_12_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_12_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_12_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_12_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_12_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_13_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_13_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_13_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_13_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_13_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_13_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_13_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_13_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_13_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_13_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_13_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_14_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_14_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_14_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_14_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_14_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_14_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_14_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_14_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_14_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_14_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_14_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_15_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_15_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_15_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_15_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_15_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_15_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_15_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_15_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_15_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_15_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_15_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_16_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_16_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_16_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_16_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_16_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_16_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_16_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_16_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_16_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_16_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_16_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_17_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_17_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_17_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_17_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_17_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_17_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_17_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_17_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_17_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_17_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_17_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_18_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_18_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_18_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_18_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_18_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_18_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_18_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_18_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_18_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_18_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_18_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_19_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_19_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_19_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_19_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_19_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_19_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_19_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_19_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_19_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_19_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_19_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_20_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_20_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_20_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_20_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_20_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_20_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_20_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_20_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_20_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_20_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_20_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_21_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_21_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_21_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_21_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_21_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_21_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_21_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_21_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_21_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_21_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_21_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_22_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_22_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_22_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_22_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_22_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_22_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_22_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_22_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_22_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_22_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_22_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_23_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_23_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_23_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_23_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_23_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_23_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_23_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_23_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_23_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_23_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_23_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_24_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_24_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_24_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_24_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_24_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_24_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_24_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_24_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_24_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_24_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_24_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_25_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_25_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_25_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_25_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_25_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_25_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_25_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_25_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_25_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_25_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_25_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_26_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_26_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_26_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_26_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_26_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_26_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_26_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_26_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_26_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_26_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_26_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_27_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_27_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_27_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_27_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_27_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_27_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_27_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_27_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_27_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_27_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_27_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_28_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_28_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_28_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_28_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_28_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_28_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_28_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_28_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_28_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_28_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_28_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_29_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_29_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_29_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_29_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_29_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_29_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_29_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_29_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_29_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_29_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_29_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_30_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_30_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_30_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_30_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_30_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_30_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_30_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_30_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_30_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_30_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_30_ProvMAC;
  /// 0 = False, 1 = True\n
  /// __Boolean, default: False__\n
  bool     WBSS_Service_31_IPService;
  /// __String, default: ""__\n
  const char *   WBSS_Service_31_IPAddress;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WBSS_Service_31_IPPort;
  /// SCH, CCH, LCH\n
  /// __String, default: ""__\n
  const char *   WBSS_Service_31_ChanId;
  /// \n
  /// __Integer, default: 0, min/max: 0/31__\n
  int32_t  WBSS_Service_31_Prio;
  /// Use 0x0FF to disable service\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Service_31_PSID;
  /// __String, default: ""__\n
  const char *   WBSS_Service_31_PSC;
  /// 0-220 = valid, 255 = unavailable\n
  /// __Integer, default: 255, min/max: 0/255__\n
  int32_t  WBSS_Service_31_RCPIThr;
  /// 0 = not set, 1-255 = valid count\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_31_WSACntThr;
  /// 0 = not set, 1-255 = valid [100ms units]\n
  /// __Integer, default: 0, min/max: 0/255__\n
  int32_t  WBSS_Service_31_WSACntThrI;
  /// Provider MAC (all 0: not set)\n
  /// __String, default: "00:00:00:00:00:00"__\n
  const char *   WBSS_Service_31_ProvMAC;
  /// -1 = Fail, 0 = No override, 1 = Pass\n
  /// __Integer, default: 0, min/max: -1/1__\n
  int32_t  WBSS_WSA_Verify_Override;
  /// __String, default: ""__\n
  const char *   WBSS_Event_Hook_Script;
  /// Only call hook script for this PSID\n
  /// Use 0x0FF to disable filter (call for any)\n
  /// __Hex, default: 0xff, min/max: 0x0/0xefffffff__\n
  uint32_t WBSS_Event_Hook_Script_PSID_Filter;
  /// IPv6 address, if empty it is disabled\n
  /// __String, default: ""__\n
  const char *   WBSS_WSA_OverridePrefix;
  /// __Integer, default: 52, min/max: 0/128__\n
  int32_t  WBSS_WSA_OverridePrefixLength;
  /// Specify if the gateway should be the global address or the link-local\n
  /// 0 = Link Local Address\n
  /// 1 = Global Address\n
  /// __Boolean, default: False__\n
  bool     WBSS_WSA_GatewayMode;
  /// Gateway IPv6 address override in the WRA of the WSA\n
  /// __String, default: ""__\n
  const char *   WBSS_WSA_OverrideGateway;
  /// Primary DNS IPv6 address in the WRA of the WSA\n
  /// default to hurricane electric DNS server\n
  /// __String, default: "2001:470:20::2"__\n
  const char *   WBSS_WSA_DNS;
  /// Secondary DNS IPv6 address in the WRA of the WSA\n
  /// default to :: (no secondary DNS extension will be\n
  /// included in the WRA)\n
  /// __String, default: "::"__\n
  const char *   WBSS_WSA_Secondary_DNS;
  /// Gateway MAC Address is the 48-bit MAC\n
  /// address associated with the Default Gateway,\n
  /// if different than the MAC address of the\n
  /// device transmitting the WSA.\n
  /// All zeros indicates not set (no GW MAC\n
  /// extension will be included in WRA)\n
  /// __String, default: ""__\n
  const char *   WBSS_WSA_Gateway_MAC;
  /// Validity time of WSAs in seconds - 1 second to 1 hour\n
  /// __Integer, default: 60, min/max: 1/3600__\n
  int32_t  WBSS_WSA_Validity_s;
  /// Disconnect from WBSS if channel is idle for this amount of time (milliseconds)\n
  /// __Integer, default: 5000, min/max: 1/60000__\n
  int32_t  WBSS_ChannelInactivityTimeout_ms;
  /// Repeat rate of WSAs per 5 seconds\n
  /// (0=off, 1=0.2Hz, 5=1Hz, 10=2Hz, 25=5Hz, 50=10Hz)\n
  /// __Integer, default: 50, min/max: 0/255__\n
  int32_t  WBSS_WSA_RepeatRate;
  /// __Boolean, default: False__\n
  bool     WBSS_WSA_USE_STATIC_LOCATION;
  /// __Double, default: -34.0, min/max: -90.0/90.0__\n
  double    WBSS_WSA_STATIC_LOCATION_LATITUDE;
  /// __Double, default: 138.0, min/max: -180.0/180.0__\n
  double    WBSS_WSA_STATIC_LOCATION_LONGITUDE;
  /// __Float, default: 1.0, min/max: -400.0/6000.0__\n
  float    WBSS_WSA_STATIC_LOCATION_ELEVATION;
  /// # 1 = Live Data (Vehicle data from CAN, position from GPS)\n
  /// # 2 = Replay (Test Mode, data from Prerecorded Files)\n
  /// # 3 = UDP (Test Mode, data over UDP)\n
  /// # 4 = GPS Only (Test Mode, Vehicle data faked based on GPS data)\n
  /// # 5 = Hybrid (Test Mode)\n
  /// __Integer, default: 4, min/max: 1/5__\n
  int32_t  TxDataSource;
  /// How to handle replay file EndOfFile\n
  /// # 0 = Close (close replay file)\n
  /// # 1 = Loop (loop replay file)\n
  /// Act when the first of the replay files ends:\n
  /// # 2 = Shutdown (shut down application)\n
  /// # 3 = Kill (kill(SIGTERM))\n
  /// Act when the last of the replay files ends:\n
  /// # 4 = ShutdownLast (shut down application)\n
  /// # 5 = KillLast (kill(SIGTERM))\n
  /// __Integer, default: 0, min/max: 0/5__\n
  int32_t  Cohda_ReplayFileEOF;
  /// Delay in ms between transmitting the last record from a\n
  /// pre-recorded file and the first record of the pre-recorded\n
  /// file when repeat is enabled.\n
  /// __Integer, default: 100, min/max: 50/1000__\n
  int32_t  Cohda_ReplayFileLoopDelay_ms;
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  TxNoPosAvailable;
  /// metres (zero means check is disabled)\n
  /// __Integer, default: 0, min/max: 0/1000__\n
  int32_t  TxPosAccuracyLimit;
  /// Enable/Disbale the forwarding of received WSMs\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_Enabled;
  /// Interface to bind to for forwarding received WSM OTA packets\n
  /// __String, default: "eth0"__\n
  const char *   WSMFwdRx_Interface;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_0_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_0_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_0_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_0_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_0_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_0_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_0_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_0_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_0_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_1_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_1_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_1_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_1_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_1_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_1_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_1_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_1_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_1_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_2_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_2_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_2_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_2_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_2_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_2_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_2_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_2_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_2_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_3_DestIP;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_3_TransportProto;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_3_DestPort;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_3_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_3_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_3_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_3_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_3_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_3_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_4_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_4_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_4_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_4_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_4_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_4_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_4_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_4_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_4_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_5_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_5_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_5_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_5_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_5_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_5_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_5_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_5_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_5_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_6_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_6_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_6_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_6_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_6_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_6_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_6_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_6_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_6_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_7_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_7_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_7_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_7_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_7_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_7_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_7_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_7_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_7_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_8_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_8_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_8_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_8_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_8_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_8_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_8_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_8_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_8_Enabled;
  /// IP address to forward received WSM OTA packets\n
  /// Empty means disabled\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_9_DestIP;
  /// UDP port to forward recevied WSM OTA packets\n
  /// 0 means disabled\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  WSMFwdRx_9_DestPort;
  /// Transport protocol to used\n
  /// 0x01 means TCP, 0x10 means UDP\n
  /// __Hex, default: 0x10, min/max: 0x1/0x10__\n
  uint32_t WSMFwdRx_9_TransportProto;
  /// PSID filter for messages to be forwarded\n
  /// 0x00 means all PSIDs\n
  /// __Hex, default: 0x0, min/max: 0x0/0xefffffff__\n
  uint32_t WSMFwdRx_9_PSID;
  /// RSSI filter for messages to be forwarded (dBm)\n
  /// -100 means all received messages\n
  /// __Integer, default: -100, min/max: -100/-60__\n
  int32_t  WSMFwdRx_9_RSSI;
  /// Sample rate of received messages\n
  /// 1 = forward all received messages,\n
  /// 9 = forwarded every 9th message\n
  /// __Integer, default: 1, min/max: 1/9__\n
  int32_t  WSMFwdRx_9_MsgSample;
  /// Time to start message forwarding - format mm/dd/yyyy, hh:mm\n
  /// Empty means start immediately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_9_StartTime;
  /// Time to end message forwarding   - format mm/dd/yyyy, hh:mm\n
  /// Empty means continue indefinately\n
  /// __String, default: ""__\n
  const char *   WSMFwdRx_9_EndTime;
  /// Enable/Disable this fowarding entry\n
  /// __Boolean, default: False__\n
  bool     WSMFwdRx_9_Enabled;
  /// #   0 = EMERG\n
  /// #   1 = ALERT\n
  /// #   2 = CRIT\n
  /// #   3 = ERR\n
  /// #   4 = WARN\n
  /// #   5 = NOTICE\n
  /// #   6 = API\n
  /// #   6 = INFO\n
  /// #   7 = DEBUG\n
  /// #   7 = INTERN (usually)\n
  /// #   8 = TEST\n
  /// #   9 = VERBOSE\n
  /// # 127 = IRQ\n
  /// # 255 = ALL\n
  /// # 256 = No change (if debug available)\n
  /// __Integer, default: 4, min/max: 0/256__\n
  int32_t  Cohda_DebugLevel;
  /// #   0 = None\n
  /// #   1 = UnixTime\n
  /// #   2 = UTCTime\n
  /// __Integer, default: 2, min/max: 0/2__\n
  int32_t  Cohda_DebugTimeLevel;
  /// #   0 = None\n
  /// #   1 = UnixTime\n
  /// #   2 = StartDeltaTime\n
  /// #   3 = UTCTime\n
  /// #   4 = MonotonicTime\n
  /// #   5 = ITSTime\n
  /// #   6 = ReplayUnixTime\n
  /// #   7 = ReplayUTCTime\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  Cohda_DebugExtraTimeLevel;
  /// #   0 = None\n
  /// #   1 = ThreadID\n
  /// __Boolean, default: False__\n
  bool     Cohda_DebugThreadLevel;
  /// #   0 = None\n
  /// #   1 = Level\n
  /// #   2 = ModuleLevel\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_DebugInfoLevel;
  /// #   0 = None\n
  /// #   1 = Normal\n
  /// #   2 = Wide\n
  /// __Integer, default: 2, min/max: 0/2__\n
  int32_t  Cohda_DebugDumpLevel;
  /// # 0x00=None\n
  /// # 0x01=Decode Tx\n
  /// # 0x02=Decode Rx\n
  /// # 0x03=Decode All\n
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  Cohda_DebugXER;
  /// # 0x00=None\n
  /// # 0x01=Decode Tx\n
  /// # 0x02=Decode Rx\n
  /// # 0x03=Decode All\n
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  Cohda_DebugGSER;
  /// # 0=None\n
  /// # 1=System Status\n
  /// # 2=Packet Status\n
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  Cohda_DebugConsole;
  /// 0=Normal thread start, 1=Threads started from main, 2=Normal, timestamps debug\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_DebugThreads;
  /// Whether threads can kill app (send SIGTERM)\n
  /// __Boolean, default: False__\n
  bool     Cohda_DebugThreadKill;
  /// # 0=None\n
  /// # 1=Payload\n
  /// # 2=Header\n
  /// # 3=Descriptor\n
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugDumpLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugDropLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugSendLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugLocTLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugFacCacheLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugLDMLevel;
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  PktDebugAppLevel;
  /// __Integer, default: 7, min/max: 0/7__\n
  int32_t  PktDebugFailAction;
  /// __String, default: ""__\n
  const char *   Cohda_UDPUserDebugHost;
  /// __Integer, default: 42260, min/max: 0/65535__\n
  int32_t  Cohda_UDPUserDebugPort;
  /// __String, default: ""__\n
  const char *   Cohda_UDPUserDebugMv6_Interface;
  /// __Boolean, default: False__\n
  bool     Cohda_UDPUserDebugMv6_Loopback;
  /// __String, default: "5 ; 0, 255"__\n
  const char *   Cohda_UDPUserDebugMv6_HopLimit;
  /// Create unique identifiers (e.g. message queues)\n
  /// __Boolean, default: False__\n
  bool     Cohda_MultipleInstance;
  /// Delay after application start for\n
  /// transmit thread to delay TX\n
  /// __Integer, default: 0, min/max: -9999/9999__\n
  int32_t  Cohda_TransmitDelay_s;
  /// 0=False, 1=True.\n
  /// Disable PCAP logging (other than tx_ota.pcap)\n
  /// __Boolean, default: False__\n
  bool     Cohda_PCAP_LoggingDisabled;
  /// 0=False, 1=True (Enable/Disable rx.pcap)\n
  /// __Boolean, default: False__\n
  bool     Cohda_P1609RxLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable tx.pcap)\n
  /// __Boolean, default: False__\n
  bool     Cohda_P1609TxLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable rx_pc5.pcap)\n
  /// __Boolean, default: True__\n
  bool     Cohda_P1609PC5RxLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable tx_pc5.pcap)\n
  /// __Boolean, default: True__\n
  bool     Cohda_P1609PC5TxLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable tx.pcap & rx.pcap)\n
  /// __Boolean, default: True__\n
  bool     Cohda_C2XLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable rx.pcap)\n
  /// __Boolean, default: False__\n
  bool     Cohda_SAECRxLogEnableFlag;
  /// 0=False, 1=True (Enable/Disable tx.pcap)\n
  /// __Boolean, default: False__\n
  bool     Cohda_SAECTxLogEnableFlag;
  /// 0=False, 1=True\n
  /// __Boolean, default: True__\n
  bool     Cohda_GPSLogEnableFlag;
  /// 0=False, 1=True\n
  /// __Boolean, default: False__\n
  bool     Cohda_CANLogEnableFlag;
  /// 0=False, 1=True\n
  /// __Boolean, default: False__\n
  bool     Cohda_VStateLogEnableFlag;
  /// 0=False, 1=True\n
  /// __Boolean, default: False__\n
  bool     Cohda_VStateCsvEnableFlag;
  /// __String, default: "/mnt/ubi/log"__\n
  const char *   Cohda_LogDirectoryName;
  /// __String, default: "0777"__\n
  const char *   Cohda_LogDirectoryMode;
  /// 0=Log number is process PID, 1=Log number is sequentially incrementing\n
  /// __Boolean, default: False__\n
  bool     Cohda_LogSequentialLogNumbers;
  /// Log directory polling interval in seconds (0 = disable)\n
  /// Checks periodically the free space and clears old log files\n
  /// __Integer, default: 300, min/max: 0/86400__\n
  int32_t  Cohda_LogPollingInterval;
  /// Minimum free space percentage to maintain on log file system (as percentage)\n
  /// __Integer, default: 25, min/max: 0/100__\n
  int32_t  Cohda_LogMinimumFreeSpace_pc;
  /// Level of cleanup, 0=none, 1=old log dirs, 2 += current PCAPs, 3+= current logs\n
  /// __Integer, default: 1, min/max: 0/3__\n
  int32_t  Cohda_LogCleanupLevel;
  /// setvbuf() buffer depth [kilobytes] (-1:default, 0:unbuffered, 1..2MB)\n
  /// __Integer, default: -1, min/max: -1/2048__\n
  int32_t  Cohda_LogBufferSize;
  /// 0=False, 1=True\n
  /// log system information Cohda_LogDirectoryName/info on startup\n
  /// __Boolean, default: True__\n
  bool     Cohda_LogSystemInfo;
  /// 0=False, 1=True\n
  /// redirect STDOUT to Cohda_LogDirectoryName/stdout\n
  /// > 1 = maximum capture size in MB\n
  /// __Integer, default: 0, min/max: 0/2000__\n
  int32_t  Cohda_LogCaptureSTDOUT;
  /// host to redirect STDOUT to (empty to disable)\n
  /// __String, default: ""__\n
  const char *   Cohda_LogCaptureSTDOUT_Host;
  /// UDP port to redirect STDOUT to (0 to disable)\n
  /// __Integer, default: 60501, min/max: 0/65535__\n
  int32_t  Cohda_LogCaptureSTDOUT_Port;
  /// 0=False, 1=True\n
  /// redirect STDERR to Cohda_LogDirectoryName/stderr\n
  /// > 1 = maximum capture size in MB\n
  /// __Integer, default: 1, min/max: 0/2000__\n
  int32_t  Cohda_LogCaptureSTDERR;
  /// host to redirect STDERR to (empty to disable)\n
  /// __String, default: ""__\n
  const char *   Cohda_LogCaptureSTDERR_Host;
  /// UDP port to redirect STDERR to (0 to disable)\n
  /// __Integer, default: 60500, min/max: 0/65535__\n
  int32_t  Cohda_LogCaptureSTDERR_Port;
  /// capture configuration\n
  /// # 0 = None\n
  /// # 1 = All\n
  /// # 2 = Minimal\n
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  Cohda_LogCaptureConf;
  /// 0=False, 1=True\n
  /// log syslog Cohda_LogDirectoryName/syslog\n
  /// __Boolean, default: False__\n
  bool     Cohda_LogCaptureSyslog;
  /// 0=False, 1=True\n
  /// log Aerolink configuration\n
  /// __Boolean, default: False__\n
  bool     Cohda_LogAerolinkConfig;
  /// 0=False, 1=True\n
  /// "killall -9 tcpdump" at startup\n
  /// __Boolean, default: True__\n
  bool     Cohda_KillallTcpDump;
  /// __String, default: "5 ; 0, 255"__\n
  const char *   Cohda_LogCaptureSTDERR_Mv6_HopLimit;
  /// __String, default: ""__\n
  const char *   Cohda_LogCaptureSTDERR_Mv6_Interface;
  /// __Boolean, default: False__\n
  bool     Cohda_LogCaptureSTDERR_Mv6_Loopback;
  /// __String, default: "5 ; 0, 255"__\n
  const char *   Cohda_LogCaptureSTDOUT_Mv6_HopLimit;
  /// __String, default: ""__\n
  const char *   Cohda_LogCaptureSTDOUT_Mv6_Interface;
  /// __Boolean, default: False__\n
  bool     Cohda_LogCaptureSTDOUT_Mv6_Loopback;
  /// 0=normal\n
  /// 1=fake verification by verifying last tx message\n
  /// 2=skip verification altogether\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_ReplayFakeVerification;
  /// __String, default: ""__\n
  const char *   Cohda_CANReplayFileName;
  /// __String, default: ""__\n
  const char *   Cohda_GPSReplayFileName;
  /// __String, default: ""__\n
  const char *   Cohda_PRXReplayFileName;
  /// __String, default: ""__\n
  const char *   Cohda_PTXReplayFileName;
  /// __String, default: ""__\n
  const char *   Cohda_G5MReplayFileName;
  /// Number of stations to simulate (Testing only)\n
  /// __Integer, default: 0, min/max: 0/100__\n
  int32_t  Cohda_G5SimulatedStations;
  /// pcap replays start at a multiple of this time.\n
  /// intended to allow synchronising multiple MKxs\n
  /// 0 to disable\n
  /// __Integer, default: 60, min/max: 0/900__\n
  int32_t  Cohda_ReplayDelayModulo;
  /// pcap replays start after an extra delay of this time.\n
  /// intended to shift time of replay mode\n
  /// 0 to disable\n
  /// __Integer, default: 0, min/max: 0/60__\n
  int32_t  Cohda_ReplayDelay;
  /// pcap replays at time of PCAP recording\n
  /// 0 = replay 'now', 1 = fake system time in past\n
  /// __Boolean, default: False__\n
  bool     Cohda_ReplaySimulation;
  /// longitudinal offset to apply to GPS pcap data to allow\n
  /// concurrent testing on the same RF channel\n
  /// __Float, default: 0.0, min/max: -360.0/360.0__\n
  float    Cohda_ReplayLongOffset;
  /// Older logs have no Extra field within the WSMP header - set\n
  /// to 1 when replaying using old logs which do not have the\n
  /// Extra field within the WSMP header\n
  /// __Boolean, default: False__\n
  bool     Cohda_PRXReplayHasNoWSMPExtra;
  /// Polling interval for STATS thread in milliseconds (0 to disable)\n
  /// __Integer, default: 0, min/max: 0/60000__\n
  int32_t  Cohda_STATSPollingInterval_ms;
  /// Add sysinfo(2) information to STATS log every N'th packet (0 to disable)\n
  /// __Integer, default: 5, min/max: 0/10000__\n
  int32_t  Cohda_STATSSysinfoLogInterval;
  /// Polling interval for CONF thread in seconds\n
  /// (0 for signals only, -1 to disable )\n
  /// __Integer, default: -1, min/max: -1/788400000__\n
  int32_t  Cohda_CONFPollingInterval_s;
  /// CAN interface name to listen on. Usually can0 or vcan0\n
  /// __String, default: "can0"__\n
  const char *   Cohda_CAN_InterfaceName;
  /// Take can network interface down/up on a can lockup/restart event. Robustly restores CAN I/O on failure. (0 to disable)\n
  /// __Boolean, default: False__\n
  bool     Cohda_CAN_BounceInterfaceOnRestart;
  /// attempt to dynamically restart interface on certain CAN errors\n
  /// __Boolean, default: False__\n
  bool     Cohda_CAN_RestartInterfaceHack;
  /// Flag to enable processing of short frames\n
  /// __Boolean, default: False__\n
  bool     Cohda_CAN_ProcessShortFrames;
  /// Flag to enable CAN test mode (simulates certain events during drive tests)\n
  /// __Boolean, default: False__\n
  bool     Cohda_CAN_TestMode;
  /// GPS data source\n
  /// # 0 = None\n
  /// # 1 = GPSD (see Cohda_GPSD_XXXX params for GPSD source)\n
  /// # 2 = Fake (see Cohda_GPSRx_Fake_Speed & Cohda_GPSRx_Sys_Time params)\n
  /// # 3 = Replay (see Cohda_GPSReplayFileName)\n
  /// # 4 = Fixed (see Cohda_GPSRx_FixedXXX params)\n
  /// # 5 = QTI Kinematics (see Cohda_GPSx_QTIXXX params)\n
  /// # 6 = ATK POTI (see Cohda_GPSx_ATKXXX params)\n
  /// __Integer, default: 1, min/max: 0/6__\n
  int32_t  Cohda_GPSRx_Source;
  /// hostname of instance of GPSD to connect to\n
  /// __String, default: "localhost"__\n
  const char *   Cohda_GPSD_HostName;
  /// port number of instance of GPSD to connect to\n
  /// __Integer, default: 2947, min/max: 1/65535__\n
  int32_t  Cohda_GPSD_Port;
  /// -1 = Auto detect\n
  /// 0 = NMEA - Read gps_data_t from gpsd\n
  /// 1 = UBX  - Read raw UBX output from gpsd\n
  /// __Integer, default: -1, min/max: -1/1__\n
  int32_t  Cohda_GPSD_Watch;
  /// Mode Threshold for considering position valid\n
  /// 3 = LPH_POS_FIX_MODE_3D\n
  /// __Integer, default: 3, min/max: -1/3__\n
  int32_t  Cohda_GPSThreshold_mode;
  /// Speed around circle (+ Clockwise)\n
  /// __Integer, default: 10, min/max: -100/100__\n
  int32_t  Cohda_GPSRx_Fake_Speed;
  /// whether to use system time in place of gps source time\n
  /// __Boolean, default: False__\n
  bool     Cohda_GPSRx_Sys_Time;
  /// __Double, default: -34.0, min/max: -90.0/90.0__\n
  double    Cohda_GPSRx_FixedLat;
  /// __Double, default: 138.0, min/max: -180.0/180.0__\n
  double    Cohda_GPSRx_FixedLong;
  /// __Float, default: 5.0, min/max: -1000.0/10000.0__\n
  float    Cohda_GPSRx_FixedAlt;
  /// IP address of QTI Kinematics server\n
  /// __String, default: "192.168.100.1"__\n
  const char *   Cohda_GPSRx_QTIHostAddr;
  /// QTI GNSS fix generation rate in Hz\n
  /// __Integer, default: 10, min/max: 1/10__\n
  int32_t  Cohda_GPSRx_QTIReportRate;
  /// UART device path for GNSS on craton2 boards\n
  /// __String, default: "/dev/ttyAMA1"__\n
  const char *   Cohda_GPSRx_ATKGnssUartPath;
  /// Number of successive bad position times that will cause a shutdown\n
  /// NOTE: check is run once per second\n
  /// 1..n to shutdown after this many bad position times\n
  /// 0 to disable check\n
  /// -1 to warn but not shutdown\n
  /// USE WITH CAUTION!\n
  /// __Integer, default: -1, min/max: -1/86400__\n
  int32_t  Cohda_GPSRx_max_bad_times;
  /// Minimum allowable difference that system time when GNSS message\n
  /// is processed can be ahead of timestamp in GNSS message\n
  /// Allows for fast GNSS processing and serial comms of message\n
  /// 0 to disable check\n
  /// (NOTE: on simulation platforms processing time can be very fast)\n
  /// __Float, default: -0.01, min/max: -2.0/1.0__\n
  float    Cohda_GPSRx_min_diff;
  /// Maximum allowable difference that system time when GNSS message\n
  /// is processed can be ahead of timestamp in GNSS message\n
  /// Allows for slow GNSS processing and serial comms of message\n
  /// 0 to disable check\n
  /// __Float, default: 0.25, min/max: 0.0/2.0__\n
  float    Cohda_GPSRx_max_diff;
  /// Number of consecutive bad fix modes that will be ignored before\n
  /// the fix is processed. E.g. occasionally GPSD reports a single\n
  /// bad position\n
  /// 0 to disable check\n
  /// __Integer, default: 2, min/max: 0/10__\n
  int32_t  Cohda_GPSRx_max_bad_pos;
  /// The user the application should run as after initialization.\n
  /// No change of user ID if empty\n
  /// __String, default: ""__\n
  const char *   Cohda_RunAsUser;
  /// Interpolate between GPS fixes 0=False, 1=True\n
  /// __Boolean, default: True__\n
  bool     Cohda_P1609TxPosInterpolation;
  /// Enable/disable EXT notification of LPH update\n
  /// __Boolean, default: False__\n
  bool     Cohda_LPH_Ext_Update;
  /// Enable/disable heading recalculation in LPH module\n
  /// 0 : Disable heading recalculation in LPH module. We trust heading from GPS at low speed.\n
  /// 1 : Enable heading recalculation in LPH module. We don't trust heading from GPS at low speed.\n
  /// __Boolean, default: False__\n
  bool     Cohda_LPH_Recalculate_Heading;
  /// TAI offset from UTC (2004 epoch), 255=ignore\n
  /// __Integer, default: 5, min/max: -30/255__\n
  int32_t  Cohda_LPH_TAI_Offset;
  /// Directory for plugins, BOARD maps to ${BOARD} used at build time\n
  /// __String, default: ""__\n
  const char *   Cohda_PluginDir;
  /// Name of random device file\n
  /// __String, default: "/dev/urandom"__\n
  const char *   Cohda_RandomDeviceFileName;
  /// __Float, default: -2.0, min/max: -999.0/0.0__\n
  float    Cohda_BrakesActiveAccelThreshold_mps2;
  /// __Float, default: -4.0, min/max: -999.0/0.0__\n
  float    Cohda_HeavyBrakeAccelThreshold_mps2;
  /// Use 4.17 as 15kmph limit\n
  /// __Float, default: 4.17, min/max: 0.0/999.0__\n
  float    Cohda_HeavyBrakeMinSpeedThreshold_mps;
  /// Set this <0. Expect max of 1g in dir of travel\n
  /// (otherwise assume gps error)\n
  /// __Float, default: -10.0, min/max: -999.0/0.0__\n
  float    Cohda_HeavyBrakeLonAccClipHigh_mps2;
  /// Set this >0 (Abs value). Only allow +/- 0.3g orthogonal\n
  /// (otherwise assume gps error)\n
  /// __Float, default: 3.0, min/max: -3.0/3.0__\n
  float    Cohda_HeavyBrakeLatAccClipHigh_mps2;
  /// -1 = allow threads to pick their own shceduler policy\n
  /// #  0 = SCHED_OTHER (no priorities)\n
  /// #  1 = SCHED_FIFO  (strict)\n
  /// #  2 = SCHED_RR    (FIFO + timeslice limits)\n
  /// __Integer, default: -1, min/max: -1/2__\n
  int32_t  Cohda_ForceSchedulerPolicy;
  /// Maximum WSMP Rx buffer size (including trailers)\n
  /// __Integer, default: 1408, min/max: 0/65535__\n
  int32_t  Cohda_P1609_RxBufMax;
  /// Minimum WSMP Tx buffers size\n
  /// __Integer, default: 0, min/max: 0/2500__\n
  int32_t  Cohda_P1609_TxBufMin;
  /// Maximum WSMP Tx buffer size (including security)\n
  /// __Integer, default: 1500, min/max: 0/65535__\n
  int32_t  Cohda_P1609_TxBufMax;
  /// 0 none\n
  /// 1  emergency response\n
  /// 2   speed based HLW & SVA\n
  /// 4    TBC\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  Cohda_KUC_Mode;
  /// 0: none\n
  /// 1: RSU (eth0 only)\n
  /// 2: RSU (eth0 and wave-data)\n
  /// 3: OBU slave (wave-data only)\n
  /// __Integer, default: 0, min/max: 0/3__\n
  int32_t  Cohda_PTP_Mode;
  /// 0=False, 1=True (Enable Decoding J2735 in P1609-RX)\n
  /// When disabled, the other decoder needs to be call\n
  /// P1609RX_CheckAndUpdateTempID() to check for duplicated\n
  /// temp IDs.\n
  /// __Boolean, default: True__\n
  bool     Cohda_P1609RxDecodeJ2735Enabled;
  /// __Hex, default: 0x0, min/max: 0x0/0xffff__\n
  uint32_t ModelDeploymentDeviceID;
  /// __Boolean, default: True__\n
  bool     TemporaryIDControl;
  /// __Integer, default: 0, min/max: -8191/8191__\n
  int32_t  antOffsetX;
  /// __Integer, default: 0, min/max: -255/255__\n
  int32_t  antOffsetY;
  /// __Float, default: 0.0, min/max: -819.1/819.1__\n
  float    antOffsetZ;
  /// VIN - used to populate vehicle status information if set\n
  /// __String, default: ""__\n
  const char *   VehicleVIN;
  /// Vehicle Name - used to populate vehicle status information if set\n
  /// __String, default: ""__\n
  const char *   VehicleName;
  /// Vehicle Owner Code - Used to populate vehicle status information if set\n
  /// __String, default: ""__\n
  const char *   VehicleOwnerCode;
  /// UUID of the microSD\n
  /// __String, default: ""__\n
  const char *   UUID;
  /// Filename of the SEL on the microSD\n
  /// __String, default: ""__\n
  const char *   SEL;
  /// __String, default: ""__\n
  const char *   Cohda_Crypto_AeroConfigDir;
  /// __String, default: ""__\n
  const char *   Cohda_Crypto_AeroStateDir;
  /// __String, default: "its.wsc"__\n
  const char *   Cohda_Crypto_AeroContext;
  /// __String, default: "demoLcm"__\n
  const char *   Cohda_Crypto_AeroLcm;
  /// __String, default: ""__\n
  const char *   Cohda_Crypto_AeroAltLcm;
  /// __String, default: ""__\n
  const char *   Cohda_Crypto_AeroLogging;
  /// # 0 = None\n
  /// # 1 = Check\n
  /// # 2 = Fix\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_Crypto_Config_Check;
  /// # 0 = None\n
  /// # 1 = Check\n
  /// __Boolean, default: False__\n
  bool     Cohda_Crypto_SMX_Check;
  /// # 0 = use position\n
  /// # 36 = australia\n
  /// # 156 = china\n
  /// # 276 = germany\n
  /// # 840 = usa\n
  /// __Integer, default: 0, min/max: 0/999__\n
  int32_t  Cohda_Crypto_TestCountryCode;
  /// # 0 = Asynchronous\n
  /// # 1 = Synchronous\n
  /// __Boolean, default: False__\n
  bool     Cohda_Crypto_Sign_Type;
  /// # 0 = All\n
  /// # 1 = Smart\n
  /// # 2 = OnDemand\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_Crypto_Verify_Policy;
  /// # 0 = Asynchronous\n
  /// # 1 = Synchronous\n
  /// __Boolean, default: False__\n
  bool     Cohda_Crypto_Verify_Type;
  /// # 0 = NoCollection\n
  /// # 1 = Basic\n
  /// # 2 = Detailed\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_Crypto_Verify_Stats;
  /// # 0 = None\n
  /// # 1 = SignVerify\n
  /// # 2 = EncryptDecryptSV\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_Crypto_InitSelfTest;
  /// __String, default: ""__\n
  const char *   Cohda_Crypto_SSPSA;
  /// __Hex, default: 0x0, min/max: 0x0/0xff__\n
  uint32_t Cohda_Crypto_SSPBSM;
  /// __Hex, default: 0x1, min/max: 0x0/0xff__\n
  uint32_t Cohda_Crypto_SSPEVA;
  /// __Integer, default: 2, min/max: 0/32__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetDP_0;
  /// __Integer, default: 2, min/max: 0/32__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetDP_1;
  /// __Integer, default: 4, min/max: 0/32__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetDP_2;
  /// __Integer, default: 5, min/max: 0/32__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetDP_3;
  /// __Integer, default: 1000, min/max: 0/100000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRange_0;
  /// __Integer, default: 1000, min/max: 0/100000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRange_1;
  /// __Integer, default: 1000, min/max: 0/100000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRange_2;
  /// __Integer, default: 1000, min/max: 0/100000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRange_3;
  /// __Integer, default: 50, min/max: 0/5000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRate_0;
  /// __Integer, default: 300, min/max: 0/5000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRate_1;
  /// __Integer, default: 100, min/max: 0/5000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRate_2;
  /// __Integer, default: 100, min/max: 0/5000__\n
  int32_t  Cohda_Crypto_SmartVerify_TargetRate_3;
  /// # 0 = Drop\n
  /// # 1 = Continue\n
  /// __Boolean, default: False__\n
  bool     Cohda_Crypto_SmartVerify_ContinueUnverified;
  /// __Integer, default: 5, min/max: -20/20__\n
  int32_t  Cohda_Crypto_Boost_Priority;
  /// nested config for SAEC
  tSAEC SAEC;
  /// nested config for SAEC_TRX
  tSAEC_TRX SAEC_TRX;
  /// nested config for Cohda_IVI
  tCohda_IVI Cohda_IVI;
  /// nested config for Cohda_TIM
  tCohda_TIM Cohda_TIM;
  /// nested config for Cohda_RSICN
  tCohda_RSICN Cohda_RSICN;
  /// nested config for Cohda_PC5
  tCohda_PC5 Cohda_PC5;
  /// nested config for Cohda_QTI
  tCohda_QTI Cohda_QTI;
  /// Aerolink security context for general messages\n
  /// __String, default: ""__\n
  const char *   Dot2_MessageContextName;
  /// Aerolink security Lcm name for id change - must\n
  /// be specified in the security context specified\n
  /// by Dot2_MessageContextName\n
  /// __String, default: "bsmLcm"__\n
  const char *   Dot2_IdChangeLcmName;
  /// __Integer, default: 2, min/max: 0/2__\n
  int32_t  Dot2_VerifyPolicy;
  /// # 2 = Standby\n
  /// # 4 = Operate\n
  /// __Integer, default: 4, min/max: 2/4__\n
  int32_t  RsuMode;
  /// If enabled, SCMS connection is via HTTP proxy\n
  /// __Boolean, default: False__\n
  bool     SCMSProxyEnable;
  /// Address of HTTP proxy server for SCMS connection\n
  /// __String, default: "2000::1"__\n
  const char *   SCMSProxyAddress;
  /// Port of HTTP proxy server for SCMS connection\n
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  SCMSProxyPort;
  /// If enabled, SCMS server name is included in TLS hello\n
  /// __Boolean, default: True__\n
  bool     SCMSIncludeServerName;
  /// If enabled, verify SSL certificate chain\n
  /// __Boolean, default: True__\n
  bool     SCMSSSLVerifyResult;
  /// __String, default: "/etc/ssl/certs"__\n
  const char *   SCMS_SSLCAPath;
  /// __String, default: ""__\n
  const char *   SCMS_SSLCAFile;
  /// nested config for Cohda_VS
  tCohda_VS Cohda_VS;
  /// nested config for Cohda_TM
  tCohda_TM Cohda_TM;
  /// nested config for Cohda_UBX
  tCohda_UBX Cohda_UBX;
  /// -1: Auto (prefer GNSS + UDR if available)\n
  /// 0: GNSS\n
  /// 1: GNSS + UDR\n
  /// __Integer, default: -1, min/max: -1/1__\n
  int32_t  Cohda_UBX_MODE;
  /// __Integer, default: 60000, min/max: -1/3600000__\n
  int32_t  Cohda_UBX_LEAP_SECONDS_POLL_INTERVAL_MS;
  /// nested config for Cohda_HMI
  tCohda_HMI Cohda_HMI;
  /// nested config for Cohda_ADR
  tCohda_ADR Cohda_ADR;
  /// nested config for Cohda_RPS
  tCohda_RPS Cohda_RPS;
  /// nested config for Cohda_LTE
  tCohda_LTE Cohda_LTE;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsCamEnabled;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsCamAutoStart;
  /// millisec\n
  /// __Integer, default: 100, min/max: 50/1000__\n
  int32_t  ItsCamInitInterval;
  /// millisec\n
  /// __Integer, default: 1000, min/max: 50/1000__\n
  int32_t  ItsCamSlowInterval;
  /// millisec\n
  /// __Integer, default: 100, min/max: 50/1000__\n
  int32_t  ItsCamDccInterval;
  /// count\n
  /// # "pCamGenNumber" = aka\n
  /// __Integer, default: 3, min/max: 1/9__\n
  int32_t  ItsCamNGenCam;
  /// m/s, 0 to disable\n
  /// __Float, default: 0.5, min/max: 0.0/10.0__\n
  float    ItsCamSpeedChangeTrigger;
  /// degrees, 0 to disable\n
  /// __Float, default: 4.0, min/max: 0.0/45.0__\n
  float    ItsCamHeadingChangeTrigger;
  /// meters, 0 to disable\n
  /// __Float, default: 4.0, min/max: 0.0/50.0__\n
  float    ItsCamDistanceChangeTrigger;
  /// Vehicle Role\n
  /// default(0)\n
  /// publicTransport(1)\n
  /// specialTransport(2)\n
  /// dangerousGoods(3)\n
  /// roadWork(4)\n
  /// rescue(5)\n
  /// emergency(6)\n
  /// safetyCar(7)\n
  /// agriculture(8)\n
  /// commercial(9)\n
  /// military(10)\n
  /// roadOperator(11)\n
  /// taxi(12)\n
  /// reserved1(13)\n
  /// reserved2(14)\n
  /// reserved3(15)\n
  /// __Integer, default: 0, min/max: 0/15__\n
  int32_t  ItsCamVehicleRole;
  /// 0 = not included\n
  /// 1 = included\n
  /// __Boolean, default: True__\n
  bool     ItsCamIncludeSpeed;
  /// # "pCamTraceMinLength" = aka\n
  /// __Integer, default: 200, min/max: 0/1000__\n
  int32_t  ItsCamTraceMinLength;
  /// # "pCamTraceMaxLength" = aka\n
  /// __Integer, default: 500, min/max: 0/1000__\n
  int32_t  ItsCamTraceMaxLength;
  /// # 0 = None\n
  /// # 1 = noCAM\n
  /// # 2 = noCAMwithPHReset\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  ItsCamConfidenceChecks;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsDenmEnabled;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsDenmExpiryCheck;
  /// __Boolean, default: False__\n
  bool     ItsDenmRelevanceAreaCheck;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsDenmAlwaysNotify;
  /// # "pDenmTraceMinLength" = aka\n
  /// __Integer, default: 600, min/max: 0/1000__\n
  int32_t  ItsDenmTraceMinLength;
  /// # "pDenmTraceMaxLength" = aka\n
  /// __Integer, default: 1000, min/max: 0/1000__\n
  int32_t  ItsDenmTraceMaxLength;
  /// Sec\n
  /// __Integer, default: 10, min/max: 0/3600__\n
  int32_t  DenmEventHistoryGenMaxDeltaTime;
  /// metres\n
  /// __Integer, default: 10, min/max: 0/1000__\n
  int32_t  DenmEventHistoryGenMaxDeltaDistance;
  /// degrees\n
  /// __Integer, default: 4, min/max: 0/90__\n
  int32_t  DenmEventHistoryGenMaxDeltaHeading;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsInfraEnabled;
  /// __Hex, default: 0xc70001, min/max: 0x0/0xffffff__\n
  uint32_t ItsImzmJurisdictionId;
  /// __Boolean, default: False__\n
  bool     ItsPlatoonSupport;
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  ItsSAMContentSetting;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: False__\n
  bool     ItsTRXPeriodicExtrapolatePosition;
  /// count, 0 = no limit\n
  /// __Integer, default: 0, min/max: 0/20__\n
  int32_t  ItsTRXHandleMultipleEvents;
  /// 0 = disabled, 1 = enabled\n
  /// __Boolean, default: True__\n
  bool     ItsTRXIDChangeFlushesDENM;
  /// # "pDccPToll" = aka\n
  /// __Integer, default: 10, min/max: -20/43__\n
  int32_t  ItsCenDsrcIntZonePowerdBm;
  /// Enables / Disables support Facilities CAM/DENM as a whole\n
  /// __Boolean, default: True__\n
  bool     ItsFacilitiesTRXEnabled;
  /// Enables / Disables support Facilities Shell interface\n
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesShellEnabled;
  /// Enables / Disables support Facilities Upper Tester\n
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesUpperTesterEnabled;
  /// Enables / Disables support Facilities Tx Info EXT notifications\n
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesTxInfoExtUpdate;
  /// Enables / Disables support Facilities Toll Database Query\n
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesTollDatabaseQuery;
  /// Toll database file\n
  /// __String, default: ""__\n
  const char *   ItsFacilitiesTollDatabaseFile;
  /// Start with limited max Tx Power (until tolling zone known)\n
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesTollStartLimited;
  /// Distance to consider toll stations valid (after query from toll database)\n
  /// __Integer, default: 250, min/max: 10/1000__\n
  int32_t  ItsFacilitiesTollValidDistance_m;
  /// __Hex, default: 0xfffffffe, min/max: 0x0/0xffffffff__\n
  uint32_t ItsFacilitiesStationID;
  /// # 0xFF = ignore\n
  /// __Hex, default: 0xff, min/max: 0x0/0xff__\n
  uint32_t ItsFacilitiesDefaultCommProfile;
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesSecResultHandling;
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesSecSSPVerMatch;
  /// __Integer, default: 1000, min/max: 0/5000__\n
  int32_t  ItsFacilitiesSysTimeError_ms;
  /// __Boolean, default: False__\n
  bool     ItsFacilitiesRandomiseSequenceOnATchange;
  /// __Integer, default: 0, min/max: 0/1000__\n
  int32_t  ItsFacilitiesAllowedRelevantDist_km;
  /// Control the used G5 interface module\n
  /// #   0 = None (interface inactive)\n
  /// #   1 = RAW (Raw Ethernet interface)\n
  /// #   2 = LLC (802.11p via LLC)\n
  /// #   3 = ATK (802.11p via ATK)\n
  /// __Integer, default: 2, min/max: 0/3__\n
  int32_t  ItsG5Enabled;
  /// If ItsG5Enabled == 1, then this Ethernet interface is used\n
  /// __String, default: "eth0"__\n
  const char *   ItsG5Interface;
  /// If ItsG5Enabled == 1, then this Ethernet ip link name is used\n
  /// __String, default: "g5cch"__\n
  const char *   ItsG5EthCchName;
  /// If ItsG5Enabled == 1, then this MAC address is used for the ip link\n
  /// __String, default: "04:e5:48:00:00:01"__\n
  const char *   ItsG5CchMACAddr;
  /// If ItsG5Enabled == 1, then this Ethernet ip link name is used\n
  /// __String, default: "g5sch"__\n
  const char *   ItsG5EthSchName;
  /// If ItsG5Enabled == 1, then this MAC address is used for the ip link\n
  /// __String, default: "04:e5:48:00:00:02"__\n
  const char *   ItsG5SchMACAddr;
  /// If ItsG5Enabled == 3, define which interface to use for CCH (SCH0)\n
  /// 0 = interface 0 for CCH (SCH0), interface 1 for SCHX (if configured)\n
  /// 1 = interface 1 for CCH (SCH0), interface 0 for SCHX (if configured)\n
  /// __Boolean, default: False__\n
  bool     ItsG5ATKCchIndex;
  /// Ethertype (0x8947 == GeoNetworking)\n
  /// __String, default: "0x8947; 0,0xFFFF"__\n
  const char *   ItsG5Ethertype;
  /// IEEE Channel number to use for CCH (SCH0)\n
  /// (166-170 for TEST FEATUREs)\n
  /// (184-186 for Urban Rail)\n
  /// __Integer, default: 180, min/max: 166/186__\n
  int32_t  ItsG5CchChanNum;
  /// Default transmit power for CCH (SCH0), Valid values: -10 to 33 in increments of 1 dBm\n
  /// __Integer, default: 23, min/max: -10/33__\n
  int32_t  ItsG5CchTxPwrLevel;
  /// Default data rate, parameter is twice the actual 10 MHz channel rate (i.e.,12=6Mbps)\n
  /// Valid values: 6,9,12,18,24,36,48,54\n
  /// # "pAlDataRateCch" = aka (note scaling from param to Mbps)\n
  /// pAlDataRateCchHigh and pAlDataRateCchLow are optional\n
  /// __Integer, default: 12, min/max: 6/54__\n
  int32_t  ItsG5CchTxDataRate;
  /// IEEE Channel number to use for SCHX\n
  /// __Integer, default: 176, min/max: 172/186__\n
  int32_t  ItsG5SchChanNum;
  /// Default transmit power for SCHX, Valid values: -10 to 33 in increments of 1 dBm\n
  /// __Integer, default: 23, min/max: -10/33__\n
  int32_t  ItsG5SchTxPwrLevel;
  /// Default data rate, parameter is twice the actual 10 MHz channel rate (i.e.,12=6Mbps)\n
  /// Valid values: 6,9,12,18,24,36,48,54\n
  /// __Integer, default: 12, min/max: 6/54__\n
  int32_t  ItsG5SchTxDataRate;
  /// Force 802.11 'NoAck' policy (TEST FEATURE)\n
  /// __Boolean, default: False__\n
  bool     ItsG5NoAck;
  /// Define number of transceiver devices used\n
  /// # 1 = One (e.g. SAF5100, has twin radios)\n
  /// # 2 = Two (e.g. 2xSAF5400)\n
  /// __Integer, default: 1, min/max: 1/2__\n
  int32_t  ItsG5TransceiverDevices;
  /// Define mode of operation for transceivers\n
  /// # 1 = Single (T1(SCH0) only)\n
  /// # 2 = Dual (T1(SCH0) + T2(SCHX))\n
  /// # 3 = NonSafety (T2/T3, Non-safety)\n
  /// __Integer, default: 1, min/max: 1/3__\n
  int32_t  ItsG5TransceiverConfig;
  /// Support non-QoS 802.11 frames received at G5 interface\n
  /// __Boolean, default: True__\n
  bool     ItsG5DataFrameNonQosSupport;
  /// Support LPD or EPD LLC protocol for transmit and receive\n
  /// G5 LLC transmit support of LPD (0x1X) or EPD (0x2X)\n
  /// G5 LLC receive support of LPD (0xX1) and/or EPD (0xX2)\n
  /// __Hex, default: 0x13, min/max: 0x11/0x23__\n
  uint32_t ItsG5DataFrameLPDEPDSupport;
  /// Control the used PC5 interface module\n
  /// #   0 = None (interface inactive)\n
  /// #   4 = QTI (LTE-V2X via QTI)\n
  /// #   5 = ATK (LTE-V2X via ATK)\n
  /// __Integer, default: 0, min/max: 0/5__\n
  int32_t  ItsPC5Enabled;
  /// __Integer, default: 100, min/max: 0/1000__\n
  int32_t  ItsPC5SPS0_Interval_ms;
  /// __Integer, default: 365, min/max: 0/65535__\n
  int32_t  ItsPC5SPS0_Size;
  /// __Integer, default: 4, min/max: 0/7__\n
  int32_t  ItsPC5SPS0_Priority;
  /// __Hex, default: 0x24, min/max: 0x0/0xffffffff__\n
  uint32_t ItsPC5SPS0_ITSAID;
  /// __Integer, default: 100, min/max: 0/1000__\n
  int32_t  ItsPC5SPS1_Interval_ms;
  /// __Integer, default: 500, min/max: 0/65535__\n
  int32_t  ItsPC5SPS1_Size;
  /// __Integer, default: 5, min/max: 0/7__\n
  int32_t  ItsPC5SPS1_Priority;
  /// __String, default: "0; 0x0, 0xFFFFFFFF"__\n
  const char *   ItsPC5SPS1_ITSAID;
  /// Enables / Disables support for transmitting GN messages\n
  /// __Boolean, default: True__\n
  bool     ItsGnEnabled;
  /// __String, default: "00:00:00:00:00:00:00:01"__\n
  const char *   ItsGnLocalAddr;
  /// # 0 = Auto\n
  /// # 1 = Managed\n
  /// # 2 = Anonymous\n
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  ItsGnLocalAddrConfMethod;
  /// __Integer, default: 1, min/max: 0/255__\n
  int32_t  ItsGnProtocolVersion;
  /// # 0 = Stationary\n
  /// # 1 = Mobile\n
  /// __Boolean, default: True__\n
  bool     ItsGnIsMobile;
  /// # 0 = Unspecified\n
  /// # 1 = ITS-G5\n
  /// # 2 = LTE-V2X\n
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  ItsGnIfType;
  /// __Integer, default: 1000, min/max: 100/2000__\n
  int32_t  ItsGnMinUpdateFrequencyLPV;
  /// metres\n
  /// __Integer, default: 80, min/max: -1/1000__\n
  int32_t  ItsGnPaiInterval;
  /// __Integer, default: 1398, min/max: 0/2600__\n
  int32_t  ItsGnMaxSduSize;
  /// __Integer, default: 88, min/max: 0/1024__\n
  int32_t  ItsGnMaxGeoNetworkingHeaderSize;
  /// __Integer, default: 20, min/max: 0/3600__\n
  int32_t  ItsGnLifetimeLocTE;
  /// __Integer, default: 3750, min/max: 1000/20000__\n
  int32_t  ItsGnNeighbourFlagExpiry;
  /// #  0 = Unknown\n
  /// #  1 = Pedestrian\n
  /// #  2 = Cyclist\n
  /// #  3 = Moped\n
  /// #  4 = Motorcycle\n
  /// #  5 = PassengerCar\n
  /// #  6 = Bus\n
  /// #  7 = LightTruck\n
  /// #  8 = HeavyTruck\n
  /// #  9 = Trailer\n
  /// # 10 = SpecialVehicles\n
  /// # 11 = Tram\n
  /// # 15 = RoadSideUnit\n
  /// __Integer, default: 5, min/max: 0/15__\n
  int32_t  ItsGnStationType;
  /// Formerly ItsGnCountryCode\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsGnReserved;
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsGnCompactTimeConfidence;
  /// __Integer, default: 200, min/max: 0/1000__\n
  int32_t  ItsGnMaxLocTEntries;
  /// __Boolean, default: True__\n
  bool     ItsGnAlwaysUpdateLPV;
  /// __Boolean, default: True__\n
  bool     ItsGnDestinationAreaCheck;
  /// __Boolean, default: False__\n
  bool     ItsGnFlushAllBufferedGUC;
  /// #   0 = Default (single active technology, or G5 with multi-tech operation)\n
  /// #   1 = G5 only\n
  /// #   2 = PC5 only\n
  /// #   3 = G5/PC5 layer clone (Test mode - no media specific adaptation)\n
  /// #   4 = GN layer clone (TBD - awaiting ETSI specs)\n
  /// __Integer, default: 0, min/max: 0/4__\n
  int32_t  ItsGnTxAccLayerMode;
  /// __Boolean, default: True__\n
  bool     ItsGnSecurity;
  /// # 0 = STRICT\n
  /// # 1 = NON-STRICT\n
  /// __Boolean, default: False__\n
  bool     ItsGnSnDecapResultHandling;
  /// __Boolean, default: False__\n
  bool     ItsDuplicateGNAddrCheckLSB32;
  /// __Boolean, default: False__\n
  bool     ItsGnMixedSecurityHandling;
  /// __Integer, default: 10, min/max: 0/255__\n
  int32_t  ItsGnLocationServiceMaxRetrans;
  /// __Integer, default: 1000, min/max: 0/65535__\n
  int32_t  ItsGnLocationServiceRetransmitTimer;
  /// __Integer, default: 1024, min/max: 0/65535__\n
  int32_t  ItsGnLocationServicePacketBufferSize;
  /// # 0 = DisableBeaconing\n
  /// __Integer, default: 3000, min/max: 0/65535__\n
  int32_t  ItsGnBeaconServiceRetransmitTimer;
  /// __Integer, default: 750, min/max: 0/65535__\n
  int32_t  ItsGnBeaconServiceMaxJitter;
  /// __Integer, default: 10, min/max: 0/255__\n
  int32_t  ItsGnBeaconServiceLPVInitWait;
  /// __Integer, default: 10, min/max: 0/255__\n
  int32_t  ItsGnDefaultHopLimit;
  /// __Integer, default: 8, min/max: 0/255__\n
  int32_t  ItsGnDPLLength;
  /// __Integer, default: 600, min/max: 0/6300__\n
  int32_t  ItsGnMaxPacketLifetime;
  /// __Integer, default: 60, min/max: 0/6300__\n
  int32_t  ItsGnDefaultPacketLifetime;
  /// __Integer, default: 100, min/max: 0/10000__\n
  int32_t  ItsGnMaxPacketDataRate;
  /// __Integer, default: 90, min/max: 0/100__\n
  int32_t  ItsGnMaxPacketDataRateEmaBeta;
  /// __Integer, default: 10, min/max: 0/1000__\n
  int32_t  ItsGnMaxGeoAreaSize;
  /// __Integer, default: 0, min/max: 0/1000__\n
  int32_t  ItsGnMaxDestAreaRange;
  /// __Integer, default: 0, min/max: 0/1000__\n
  int32_t  ItsGnMinCBFProgressionDist;
  /// __Integer, default: 0, min/max: 0/1000__\n
  int32_t  ItsGnMinCBFAreaCheckDist;
  /// __Integer, default: 100, min/max: 0/1000__\n
  int32_t  ItsGnMinRepetitionInterval;
  /// # 0 = Unspecified\n
  /// # 1 = Greedy\n
  /// # 2 = CBF\n
  /// __Integer, default: 1, min/max: 0/2__\n
  int32_t  ItsGnNonAreaForwardingAlgorithm;
  /// # 0 = Unspecified\n
  /// # 1 = Simple\n
  /// # 2 = CBF\n
  /// # 3 = Advanced\n
  /// __Integer, default: 2, min/max: 0/3__\n
  int32_t  ItsGnAreaForwardingAlgorithm;
  /// __Integer, default: 1, min/max: 0/65535__\n
  int32_t  ItsGnCbfMinTime;
  /// __Integer, default: 100, min/max: 0/65535__\n
  int32_t  ItsGnCbfMaxTime;
  /// __Integer, default: 1000, min/max: 0/65535__\n
  int32_t  ItsGnDefaultMaxCommunicationRange;
  /// __Integer, default: 30, min/max: 0/180__\n
  int32_t  ItsGnBroadcastCBFDefSectorAngle;
  /// __Integer, default: 256, min/max: 0/65535__\n
  int32_t  ItsGnUcForwardingPacketBufferSize;
  /// __Integer, default: 1024, min/max: 0/65535__\n
  int32_t  ItsGnBcForwardingPacketBufferSize;
  /// __Integer, default: 256, min/max: 0/65535__\n
  int32_t  ItsGnCbfPacketBufferSize;
  /// __Integer, default: 3, min/max: 1/32__\n
  int32_t  ItsGnBroadcastAdvMaxCounter;
  /// __Hex, default: 0x2, min/max: 0x0/0xff__\n
  uint32_t ItsGnDefaultTrafficClass;
  /// # "pCamTrafficClass" = aka\n
  /// __Hex, default: 0x2, min/max: 0x0/0xff__\n
  uint32_t ItsGnDefaultTrafficClassCAM;
  /// __Hex, default: 0x3, min/max: 0x0/0xff__\n
  uint32_t ItsGnDefaultTrafficClassFWD;
  /// __Integer, default: 1, min/max: 0/999__\n
  int32_t  ItsGnRegionCode;
  /// __Boolean, default: False__\n
  bool     ItsC2CGnGbcScf;
  /// __Boolean, default: False__\n
  bool     ItsC2CGnRandomiseGNSN;
  /// __Boolean, default: False__\n
  bool     ItsGn6Enabled;
  /// 0 = Disabled,1 = Enabled\n
  /// __Boolean, default: False__\n
  bool     ItsGn6aslVIResolAddr;
  /// __String, default: "EN1.2.1"__\n
  const char *   ItsGn6aslENversion;
  /// 0 for 'local position'\n
  /// __Integer, default: 0, min/max: -900000000/900000000__\n
  int32_t  ItsGn6aslGvlAreaCenterLatitude;
  /// 0 for 'local position'\n
  /// __Integer, default: 0, min/max: -1800000000/1800000000__\n
  int32_t  ItsGn6aslGvlAreaCenterLongitude;
  /// Shape: 0=circle,1=rect,2=ellipse\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  ItsGn6aslGvlAreaShape;
  /// __Integer, default: 1000, min/max: 1/65535__\n
  int32_t  ItsGn6aslGvlAreaDistA;
  /// __Integer, default: 0, min/max: 0/65535__\n
  int32_t  ItsGn6aslGvlAreaDistB;
  /// __Integer, default: 0, min/max: 0/359__\n
  int32_t  ItsGn6aslGvlAreaAngle;
  /// __Boolean, default: False__\n
  bool     ItsGn6IPv4Enabled;
  /// 0 = Disabled,1 = Enabled\n
  /// __Boolean, default: False__\n
  bool     ItsNativeIPv6Enabled;
  /// 0 = Disabled,1 = Enabled\n
  /// __Boolean, default: False__\n
  bool     ItsNativeIPv6ForceStart;
  /// __String, default: ""__\n
  const char *   ItsNativeIPv6RadioAddress;
  /// __String, default: ""__\n
  const char *   ItsNativeIPv6RadioAddressPrefix;
  /// __Integer, default: 0, min/max: 0/64__\n
  int32_t  ItsNativeIPv6RadioAddressPrefixLength;
  /// __String, default: "2001:470:20::2"__\n
  const char *   ItsNativeIPv6RadioPrimaryDNS;
  /// # "bBtpCamPort" = aka\n
  /// __Integer, default: 2001, min/max: 0/65535__\n
  int32_t  ItsBtpCAMDestPort;
  /// # "bBtpDenmPort" = aka\n
  /// __Integer, default: 2002, min/max: 0/65535__\n
  int32_t  ItsBtpDENMDestPort;
  /// __Integer, default: 65535, min/max: 0/65535__\n
  int32_t  ItsBtpShellDestPort;
  /// # 0 = None\n
  /// # 1 = Basic (satisfies EN 302 571)\n
  /// # 2 = C2C\n
  /// # 3 = ETSI Adaptive\n
  /// # 4 = ETSI Reactive\n
  /// __Integer, default: 2, min/max: 0/4__\n
  int32_t  ItsDCCEnabled;
  /// __Integer, default: -10, min/max: -20/43__\n
  int32_t  ItsDCC_CCH_TxPowerThr_minTxPower_dBm;
  /// __Integer, default: 33, min/max: -20/43__\n
  int32_t  ItsDCC_CCH_TxPowerThr_maxTxPower_dBm;
  /// __Integer, default: -10, min/max: -20/43__\n
  int32_t  ItsDCC_SCH_TxPowerThr_minTxPower_dBm;
  /// __Integer, default: 33, min/max: -20/43__\n
  int32_t  ItsDCC_SCH_TxPowerThr_maxTxPower_dBm;
  /// __Integer, default: 40, min/max: 0/40950__\n
  int32_t  ItsDCC_CCH_PktTimingThr_minPacketInterval_ms;
  /// __Integer, default: 960, min/max: 0/40950__\n
  int32_t  ItsDCC_CCH_PktTimingThr_maxPacketInterval_ms;
  /// __Integer, default: 40, min/max: 0/40950__\n
  int32_t  ItsDCC_SCH_PktTimingThr_minPacketInterval_ms;
  /// __Integer, default: 960, min/max: 0/40950__\n
  int32_t  ItsDCC_SCH_PktTimingThr_maxPacketInterval_ms;
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_PktDataRateThr_minDataRate_MCS;
  /// __Integer, default: 4, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_PktDataRateThr_maxDataRate_MCS;
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_PktDataRateThr_minDataRate_MCS;
  /// __Integer, default: 5, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_PktDataRateThr_maxDataRate_MCS;
  /// __Integer, default: 300, min/max: 0/1000__\n
  int32_t  ItsDCC_CCH_ChanLoadThr_minChannelLoad_TenthPC;
  /// __Integer, default: 650, min/max: 0/1000__\n
  int32_t  ItsDCC_CCH_ChanLoadThr_maxChannelLoad_TenthPC;
  /// __Integer, default: 300, min/max: 0/1000__\n
  int32_t  ItsDCC_SCH_ChanLoadThr_minChannelLoad_TenthPC;
  /// __Integer, default: 650, min/max: 0/1000__\n
  int32_t  ItsDCC_SCH_ChanLoadThr_maxChannelLoad_TenthPC;
  /// __Integer, default: 1000, min/max: 0/40950__\n
  int32_t  ItsDCC_CCH_General_timeUp_ms;
  /// __Integer, default: 5000, min/max: 0/40950__\n
  int32_t  ItsDCC_CCH_General_timeDown_ms;
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  ItsDCC_CCH_General_numActiveState;
  /// __Integer, default: 1000, min/max: 0/40950__\n
  int32_t  ItsDCC_SCH_General_timeUp_ms;
  /// __Integer, default: 5000, min/max: 0/40950__\n
  int32_t  ItsDCC_SCH_General_timeDown_ms;
  /// __Integer, default: 3, min/max: 0/3__\n
  int32_t  ItsDCC_SCH_General_numActiveState;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Relaxed_DCC_AC_VO;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Relaxed_DCC_AC_VI;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Relaxed_DCC_AC_BE;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Relaxed_DCC_AC_BK;
  /// __Integer, default: 400, min/max: 0/1000__\n
  int32_t  ItsDCC_CCH_ChanLoadThr_ActiveState1_ChannelLoad_TenthPC;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_ActiveState_DCC_AC_VO;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_ActiveState_DCC_AC_VI;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_ActiveState_DCC_AC_BE;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_ActiveState_DCC_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState1_TxPower_AC_VO;
  /// 25dBm\n
  /// __Integer, default: 90, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState1_TxPower_AC_VI;
  /// 20dBm\n
  /// __Integer, default: 80, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState1_TxPower_AC_BE;
  /// 15dBm\n
  /// __Integer, default: 70, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState1_TxPower_AC_BK;
  /// 90mS\n
  /// __Integer, default: 9, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState1_PktInterval_AC_VO;
  /// 90mS\n
  /// __Integer, default: 9, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState1_PktInterval_AC_VI;
  /// 90mS\n
  /// __Integer, default: 9, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState1_PktInterval_AC_BE;
  /// 90mS\n
  /// __Integer, default: 9, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState1_PktInterval_AC_BK;
  /// 6mpbs\n
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState1_DataRate_AC_VO;
  /// 6mpbs\n
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState1_DataRate_AC_VI;
  /// 6mpbs\n
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState1_DataRate_AC_BE;
  /// 6mpbs\n
  /// __Integer, default: 2, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState1_DataRate_AC_BK;
  /// __Integer, default: 500, min/max: 0/1000__\n
  int32_t  ItsDCC_CCH_ChanLoadThr_ActiveState2_ChannelLoad_TenthPC;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState2_TxPower_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState2_TxPower_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState2_TxPower_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState2_TxPower_AC_BK;
  /// 190mS\n
  /// __Integer, default: 19, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState2_PktInterval_AC_VO;
  /// 190mS\n
  /// __Integer, default: 19, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState2_PktInterval_AC_VI;
  /// 190mS\n
  /// __Integer, default: 19, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState2_PktInterval_AC_BE;
  /// 190mS\n
  /// __Integer, default: 19, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState2_PktInterval_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState2_DataRate_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState2_DataRate_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState2_DataRate_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState2_DataRate_AC_BK;
  /// __Integer, default: 650, min/max: 0/1000__\n
  int32_t  ItsDCC_CCH_ChanLoadThr_ActiveState3_ChannelLoad_TenthPC;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState3_TxPower_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState3_TxPower_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState3_TxPower_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_CCH_ActiveState3_TxPower_AC_BK;
  /// 240mS\n
  /// __Integer, default: 24, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState3_PktInterval_AC_VO;
  /// 240mS\n
  /// __Integer, default: 24, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState3_PktInterval_AC_VI;
  /// 240mS\n
  /// __Integer, default: 24, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState3_PktInterval_AC_BE;
  /// 240mS\n
  /// __Integer, default: 24, min/max: 0/1023__\n
  int32_t  ItsDCC_CCH_ActiveState3_PktInterval_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState3_DataRate_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState3_DataRate_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState3_DataRate_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_CCH_ActiveState3_DataRate_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Restrictive_DCC_AC_VO;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Restrictive_DCC_AC_VI;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Restrictive_DCC_AC_BE;
  /// TRC\n
  /// __Integer, default: 2, min/max: 0/63__\n
  int32_t  ItsDCC_CCH_Restrictive_DCC_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Relaxed_DCC_AC_VO;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Relaxed_DCC_AC_VI;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Relaxed_DCC_AC_BE;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Relaxed_DCC_AC_BK;
  /// __Integer, default: 250, min/max: 0/1000__\n
  int32_t  ItsDCC_SCH_ChanLoadThr_ActiveState1_ChannelLoad_TenthPC;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_ActiveState_DCC_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_ActiveState_DCC_AC_VI;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_ActiveState_DCC_AC_BE;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_ActiveState_DCC_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState1_TxPower_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState1_TxPower_AC_VI;
  /// 25dBm\n
  /// __Integer, default: 90, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState1_TxPower_AC_BE;
  /// 20dBm\n
  /// __Integer, default: 80, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState1_TxPower_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState1_PktInterval_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState1_PktInterval_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState1_PktInterval_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState1_PktInterval_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState1_DataRate_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState1_DataRate_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState1_DataRate_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState1_DataRate_AC_BK;
  /// __Integer, default: 300, min/max: 0/1000__\n
  int32_t  ItsDCC_SCH_ChanLoadThr_ActiveState2_ChannelLoad_TenthPC;
  /// 25dBm\n
  /// __Integer, default: 90, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState2_TxPower_AC_VO;
  /// 25dBm\n
  /// __Integer, default: 90, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState2_TxPower_AC_VI;
  /// 20dBm\n
  /// __Integer, default: 80, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState2_TxPower_AC_BE;
  /// 10dBm\n
  /// __Integer, default: 60, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState2_TxPower_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState2_PktInterval_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState2_PktInterval_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState2_PktInterval_AC_BE;
  /// 1000mS\n
  /// __Integer, default: 100, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState2_PktInterval_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState2_DataRate_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState2_DataRate_AC_VI;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState2_DataRate_AC_BE;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState2_DataRate_AC_BK;
  /// __Integer, default: 350, min/max: 0/1000__\n
  int32_t  ItsDCC_SCH_ChanLoadThr_ActiveState3_ChannelLoad_TenthPC;
  /// 15dBm\n
  /// __Integer, default: 70, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState3_TxPower_AC_VO;
  /// 15dBm\n
  /// __Integer, default: 70, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState3_TxPower_AC_VI;
  /// 10dBm\n
  /// __Integer, default: 60, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState3_TxPower_AC_BE;
  /// 5dBm\n
  /// __Integer, default: 50, min/max: 0/127__\n
  int32_t  ItsDCC_SCH_ActiveState3_TxPower_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState3_PktInterval_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState3_PktInterval_AC_VI;
  /// 1000mS\n
  /// __Integer, default: 100, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState3_PktInterval_AC_BE;
  /// 1500mS\n
  /// __Integer, default: 150, min/max: 0/1023__\n
  int32_t  ItsDCC_SCH_ActiveState3_PktInterval_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState3_DataRate_AC_VO;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState3_DataRate_AC_VI;
  /// 9Mbps\n
  /// __Integer, default: 3, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState3_DataRate_AC_BE;
  /// 9Mbps\n
  /// __Integer, default: 3, min/max: 0/7__\n
  int32_t  ItsDCC_SCH_ActiveState3_DataRate_AC_BK;
  /// Not used\n
  /// __Integer, default: 0, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Restrictive_DCC_AC_VO;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Restrictive_DCC_AC_VI;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Restrictive_DCC_AC_BE;
  /// TPC\n
  /// __Integer, default: 1, min/max: 0/63__\n
  int32_t  ItsDCC_SCH_Restrictive_DCC_AC_BK;
  /// __Integer, default: 100, min/max: 50/500__\n
  int32_t  ItsG5MonUpdateFrequency;
  /// hostname for sending BTP Data Ind to Shell\n
  /// __String, default: "127.0.0.1"__\n
  const char *   ItsUdpBtpIfHostName;
  /// port number for sending BTP Data Ind to Shell\n
  /// __Integer, default: 4400, min/max: 1/65535__\n
  int32_t  ItsUdpBtpIfIndPort;
  /// port number for receiving BTP Data Req from Shell\n
  /// __Integer, default: 4401, min/max: 1/65535__\n
  int32_t  ItsUdpBtpIfReqPort;
  /// # 0 = Disable\n
  /// # 1 = OneSecond\n
  /// __Integer, default: 1, min/max: 0/3600__\n
  int32_t  Cohda_SecIdChangeCheckInterval;
  /// __Boolean, default: False__\n
  bool     Cohda_SecIdChangeIntervalRand;
  /// # 0 = Disable\n
  /// __Integer, default: 300, min/max: 0/3600__\n
  int32_t  Cohda_SecIdChangeIntervalMin;
  /// # 0 = Disable\n
  /// __Integer, default: 300, min/max: 0/3600__\n
  int32_t  Cohda_SecIdChangeIntervalMax;
  /// __Boolean, default: False__\n
  bool     Cohda_SecIdChangeDistanceRand;
  /// # 0 = Disable\n
  /// __Integer, default: 2000, min/max: 0/100000__\n
  int32_t  Cohda_SecIdChangeDistanceMin;
  /// # 0 = Disable\n
  /// __Integer, default: 15000, min/max: 0/100000__\n
  int32_t  Cohda_SecIdChangeDistanceMax;
  /// # 0 = AllowChange\n
  /// # 1 = NoSequentialChanges\n
  /// # 2 = NoFrequentChanges\n
  /// __Integer, default: 2, min/max: 0/3__\n
  int32_t  Cohda_SecDuplicateMacHandling;
  /// # -1 = Disable\n
  /// # 0 = AlwaysChange\n
  /// __Integer, default: 1800, min/max: -1/3600__\n
  int32_t  Cohda_SecDuplicateMacInterval;
  /// # -1 = Disable\n
  /// __Integer, default: 5, min/max: -1/3600__\n
  int32_t  Cohda_SecIdChangeRetryInterval;
  /// __Boolean, default: False__\n
  bool     Cohda_SecShuffleCerts;
  /// # 0 = Cohda\n
  /// # 1 = C2C\n
  /// # 2 = EUCP\n
  /// __Integer, default: 0, min/max: 0/2__\n
  int32_t  Cohda_SecIdChangeScheme;
  /// __Boolean, default: False__\n
  bool     Cohda_SecIdChangeSchemeSchedOnly;
  /// # 0 = AbsoluteAsTheCrowFlies\n
  /// # 1 = CumulativeTravel\n
  /// __Boolean, default: False__\n
  bool     Cohda_SecIdChangeDistanceMethod;
  /// # 0 = Disable\n
  /// # 1 = OneMinute\n
  /// __Integer, default: 0, min/max: 0/30__\n
  int32_t  Cohda_SecRestartBlockingTime;
  /// # 0 = Disable\n
  /// # 1 = OneMinute\n
  /// __Integer, default: 0, min/max: 0/60__\n
  int32_t  Cohda_SecChangeBlockingMaxTime;
  /// __Integer, default: 0, min/max: 0/4__\n
  int32_t  Cohda_SecCertMinTal;
  /// # 0 = Disable\n
  /// # 1 = OneATCert\n
  /// __Integer, default: 0, min/max: 0/100__\n
  int32_t  Cohda_SecMinValidATCerts;
} tIniFile;

/// optional sanity checker passed to parsing function
typedef int(*tConfSanityChecker)(tIniFile * c) ;
/// ConfIniParse the given file
int ConfIniParseFile(const char * file, tIniFile * c, tConfReadMode mode, tConfSanityChecker sanity);
/// Parse a set of lines
int ConfIniParseLines(const char * pLines, tIniFile * pIniFile, tConfReadMode mode);
/// deep copy
void ConfIniCopy(tIniFile * dest, const tIniFile * src);
/// duplicate
tIniFile * ConfIniDup(const tIniFile * src);
/// clean up internals (you must still free(conf) if appropriate)
void ConfIniFree(tIniFile * conf);
/// dump to STDOUT
void ConfIniDump(const tIniFile * conf);
/// dump to given fd
void ConfIniDumpTo(FILE * f, const tIniFile * conf);
/// Compare two sets of config parameters for changes
int ConfIniCompare(const tIniFile * pConfA, const tIniFile * pConfB);
/// Check the numeric limits
int ConfIniCheckLimits(tIniFile * pIni, tConfReadMode mode);

#ifdef __cplusplus
}
#endif

#endif // ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_PLAT_CONF_CONF_INI_H_

/**
 * @}
 */
