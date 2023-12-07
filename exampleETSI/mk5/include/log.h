/**
 * @addtogroup log_api Base Log API
 * @{
 *
 * @section log_api_dd What Does It Do
 * Basic logging library.
 *
 * @note Interface definition for the logging library.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LOG_H_
#define __LOG_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------
#include "util.h"
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
/// PATH name
#define LOG_PATH_MAX 512

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void Log_Init(void);
void Log_Deinit(void);

int Log_ThreadInit(void);
void Log_ThreadDeinit(void);

bool Log_GetLoggingEnabled(void);

const char * Log_GetBaseDir(void);
void Log_GetLogDir(char Path[LOG_PATH_MAX]);
time_t Log_GetMACandTime(uint8_t MAC[ETH_ALEN]);

void Log_GetPath(const char *pFilename,
                 char Path[LOG_PATH_MAX]);
void Log_Truncate(void);

#ifdef __cplusplus
}
#endif

#endif /* __LOG_H_ */

/**
 * @}
 */
