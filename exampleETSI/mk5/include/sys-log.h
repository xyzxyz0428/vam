/**
 * @addtogroup syslog_api Syslog logging API
 * @{
 *
 * @section syslog_api_dd What Does It Do
 * Syslog management library.
 *
 * @note Interface definition for the syslog logging library.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SYSLOG_H_
#define __SYSLOG_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------
#include <syslog.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int Syslog_Init(void);
int Syslog_Deinit(void);

/**
 * @brief Write a syslog message utilising the standard syslog library
 */
#define Syslog(Priority, pFmt, Args...)          \
  do {                                                   \
      switch(Priority)                                   \
      {                                                  \
        case LOG_EMERG:                                  \
          syslog(Priority, "EMERGENCY - " pFmt, ##Args); \
          break;                                         \
        case LOG_ALERT:                                  \
          syslog(Priority, "ALERT - " pFmt, ##Args);     \
          break;                                         \
        case LOG_CRIT:                                   \
          syslog(Priority, "CRITICAL - " pFmt, ##Args);  \
          break;                                         \
        case LOG_ERR:                                    \
          syslog(Priority, "ERROR - " pFmt, ##Args);     \
          break;                                         \
        case LOG_WARNING:                                \
          syslog(Priority, "WARNING - " pFmt, ##Args);   \
          break;                                         \
        case LOG_NOTICE:                                 \
          syslog(Priority, "NOTICE - " pFmt, ##Args);    \
          break;                                         \
        case LOG_INFO:                                   \
          syslog(Priority, "INFO - " pFmt, ##Args);      \
          break;                                         \
        case LOG_DEBUG:                                  \
          syslog(Priority, "DEBUG - " pFmt, ##Args);     \
          break;                                         \
        default:                                         \
          syslog(Priority, pFmt, ##Args);                \
      }                                                  \
  } while(0)

#ifdef __cplusplus
}
#endif

#endif /* __SYSLOG_H_ */

/**
 * @}
 */
