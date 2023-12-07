#pragma once
/**
 * @addtogroup tc_api Target Classification (TC) API
 * @{
 *
 *
 * @file
 *
 */

//-----------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

// Generated from "/opt/jenkins/workspace/Release_MK5_SDK/MK5/software/build/mk5-bin/stack/src/sensors/tc/TC_Err.txt"
#ifndef ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TC_TC_ERR_TXT__
#define ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TC_TC_ERR_TXT__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum TC_ErrCode
{
    // 0
    /// OK
    TC_ERR_NONE,
    /// TC still has clients
    TC_ERR_ACTIVE_CLIENTS,
    /// Unable to decode ASN1
    TC_ERR_ASN_DECODE_FAIL,
    /// CAM Station Type is not a vehicle
    TC_ERR_ETSI_CAM_NOT_VEHICLE,
    /// CAM without BasicVehicleContainerHighFrequency
    TC_ERR_ETSI_CAM_NO_BVHFC,
    // 5
    /// DENM does not contain exactly 1 trace
    TC_ERR_ETSI_NO_UNIQ_TRACE,
    /// Too many PH crumbs (> LPH_PH_POINTS_MAX)
    TC_ERR_ETSI_PH_EXCESS_CRUMBS,
    /// PH present, but no crumbs
    TC_ERR_ETSI_PH_NO_CRUMBS,
    /// No path history available to decode in CAM
    TC_ERR_ETSI_PH_NO_LFC,
    /// No path history available to decode in DENM
    TC_ERR_ETSI_PH_NO_LOC,
    // 10
    /// No path history available to decode
    TC_ERR_ETSI_PH_NO_PH,
    /// No event history available to decode
    TC_ERR_ETSI_PH_NO_EH,
    /// Crumbs < 0 Decode failed (don't try again)
    TC_ERR_ETSI_PH_CRUMBS_NEG,
    /// Remote is NULL (used to check)
    TC_ERR_ETSI_PH_NO_REMOTE,
    /// Unexpected low-freq container in CAM
    TC_ERR_ETSI_PH_UNK_LFC,
    // 15
    /// Unknown ETSI message type
    TC_ERR_ETSI_UNK,
    /// Unknown ETSI alacarte message
    TC_ERR_ETSI_UNK_ALACARTE,
    /// Ext Callback failed to send Message
    TC_ERR_EXT_MSGQ_SEND,
    /// NULL pointer in TDE Ext Callback
    TC_ERR_EXT_NULL,
    /// Failed to register Ext Callback
    TC_ERR_EXT_REG,
    // 20
    /// decode please
    TC_ERR_HLP_DECODE,
    /// don't want
    TC_ERR_HLP_IGNORE,
    /// don't want
    TC_ERR_HLP_UNEXPECTED,
    /// already initialised
    TC_ERR_INIT_ALREADY_DONE,
    /// not initialised yet, call TDE_Init
    TC_ERR_INIT_NOT_DONE,
    // 25
    /// Ignored J2735 message type
    TC_ERR_J2735_IGN,
    /// Invalid data in J2735 message
    TC_ERR_J2735_INVALID,
    /// No PH in lastPH packet
    TC_ERR_J2735_PH_MISSING,
    /// No path history available
    TC_ERR_J2735_PH_UNAVAIL,
    /// Unknown PH crumb type
    TC_ERR_J2735_PH_UNK,
    // 30
    /// Unsupported PH crumb type
    TC_ERR_J2735_PH_UNSUP,
    /// Unknown J2735 message type
    TC_ERR_J2735_UNK,
    /// Ignored SAEC message type
    TC_ERR_SAEC_IGN,
    /// Invalid data in SAEC message
    TC_ERR_SAEC_INVALID,
    /// No path history available
    TC_ERR_SAEC_PH_UNAVAIL,
    // 35
    /// Couldn't write to TDE log file
    TC_ERR_LOGFILE_WRITE,
    /// Call to LPH_Data failed
    TC_ERR_LPH_DATA,
    /// Call to LPH_Data returned NULL
    TC_ERR_LPH_DATA_NULL,
    /// No GPS fix
    TC_ERR_LPH_NO_FIX,
    /// Call to LPH_Predict failed
    TC_ERR_LPH_PREDICT,
    // 40
    /// Failed to register LPH reader
    TC_ERR_LPH_REG,
    /// Error creating rx message queue
    TC_ERR_MSGQ_INIT,
    /// Error sending terminate to thread (self)
    TC_ERR_MSGQ_SENDTERMINATE,
    /// Unable to initialise the client mutex
    TC_ERR_MUTEX_INIT,
    /// Unable to lock the client mutex
    TC_ERR_MUTEX_LOCK,
    // 45
    /// TDE Object pointer not allocated
    TC_ERR_NULL,
    /// RV behind HV after rotating by -HV.heading
    TC_ERR_RV_UNEXPECTEDLY_BEHIND_US,
    /// Error creating thread
    TC_ERR_THREAD_CREATE,
    /// Failed to initialise WatchDog timer
    TC_ERR_TIMER_INIT,
    /// TC_MAX_CLIENTS already registered
    TC_ERR_TOO_MANY_CLIENTS,
    // 50
    /// TC_MAX_HELPERS already registered
    TC_ERR_TOO_MANY_HELPERS,
    /// Failed to register VState reader
    TC_ERR_VSTATE_REG,
    /// TC Client is not open
    TC_ERR_CLIENT_NOT_OPEN,
    // 53
    TC_ERR_NUM_CODES
} tTC_ErrCode;

/// convert code to string
const char * TC_ErrToStr(tTC_ErrCode err);

#ifdef __cplusplus
}
#endif

#endif // ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TC_TC_ERR_TXT__

/**
 * @}
 */
