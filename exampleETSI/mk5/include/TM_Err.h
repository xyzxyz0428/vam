#pragma once
/**
 * @addtogroup tm_api Threat Management (TM) API
 * @{
 *
 *
 * @file
 *
 */

//-----------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

// Generated from "/opt/jenkins/workspace/Release_MK5_SDK/MK5/software/build/mk5-bin/stack/src/sensors/tm/TM_Err.txt"
#ifndef ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TM_TM_ERR_TXT__
#define ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TM_TM_ERR_TXT__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum TM_ErrCode
{
    // 0
    /// OK
    TM_ERR_NONE,
    /// Unable to initialise semaphore
    TM_ERR_INIT_SEM_INIT_FAIL,
    /// Unable to initialise mutex
    TM_ERR_INIT_SEM_MUTEX_FAIL,
    /// Unable to initialise queue
    TM_ERR_INIT_SEM_QUEUE_FAIL,
    /// Unable to start worker thread
    TM_ERR_INIT_THREAD_FAIL,
    // 5
    /// Unable to get the current callback
    TM_ERR_GET_CALLBACK_FAIL,
    /// Unable to set the current callback
    TM_ERR_SET_CALLBACK_FAIL,
    /// Unable to submit a verify request
    TM_ERR_VRFY_REQUEST_FAIL,
    /// not initialised yet, call TM_Init
    TM_ERR_INIT_NOT_DONE,
    /// Unable to initialise the client mutex
    TM_ERR_INIT_MUTEX_FAIL,
    // 10
    /// Unable to lock the client mutex
    TM_ERR_MUTEX_LOCK_FAIL,
    /// TM_MAX_CLIENTS already registered
    TM_ERR_TOO_MANY_CLIENTS,
    /// Unable to remove the specified callback
    TM_ERR_DEL_CALLBACK_FAIL,
    // 13
    TM_ERR_NUM_CODES
} tTM_ErrCode;

/// convert code to string
const char * TM_ErrToStr(tTM_ErrCode err);

#ifdef __cplusplus
}
#endif

#endif // ___OPT_JENKINS_WORKSPACE_RELEASE_MK5_SDK_MK5_SOFTWARE_BUILD_MK5_BIN_STACK_SRC_SENSORS_TM_TM_ERR_TXT__

/**
 * @}
 */
