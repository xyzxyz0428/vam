#pragma once
/**
 * @addtogroup ta_api Threat Arbitrator (TA) API
 * @{
 *
 *
 * @file
 *
 */

//-----------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

// Generated from "/opt/jenkins/workspace/Release_MK5_SDK/MK5/software/build/mk5-bin/stack/src/sensors/ta/TA_Err.txt"
#ifndef ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TA_TA_ERR_TXT__
#define ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TA_TA_ERR_TXT__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum TA_ErrCode
{
    // 0
    /// OK
    TA_ERR_NONE,
    /// Threat application disabled
    TA_ERR_APP_DISABLED,
    /// Threat application NULL!
    TA_ERR_APP_NULL,
    /// Unable to open LPH
    TA_ERR_LPH_OPEN,
    /// Unable to close TC
    TA_ERR_TC_CLOSE,
    // 5
    /// Unable to open TC
    TA_ERR_TC_OPEN,
    /// Unable to start worker thread
    TA_ERR_THREAD_START,
    /// Unable to register additional threat application
    TA_ERR_TOO_MANY_APPS,
    /// Unable to open VState
    TA_ERR_VS_OPEN,
    /// Unable to init Mutex
    TA_ERR_MUTEX,
    // 10
    /// Unable to start triggering thread
    TA_ERR_TRIG_START,
    TA_ERR_NUM_CODES
} tTA_ErrCode;

/// convert code to string
const char * TA_ErrToStr(tTA_ErrCode err);

#ifdef __cplusplus
}
#endif

#endif // ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TA_TA_ERR_TXT__

/**
 * @}
 */
