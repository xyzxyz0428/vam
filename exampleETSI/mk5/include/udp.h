/**
 * @addtogroup util
 * @{
 *
 * UDP utility functions
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UTIL_UDP_H__
#define __UTIL_UDP_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

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
struct sockaddr_in6;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int UDP_OpenPort(const char *pHost, uint16_t Port);

int UDP_OpenSrvPort(uint16_t Port);
int UDP_OpenSrvPort2(uint16_t Port, const char * pInterface);

int UDP_OpenMulticastPort(const char *pGroup,
                          uint16_t Port,
                          const char *pInterface,
                          struct sockaddr_in6 *pGroupSock,
                          bool LoopBack,
                          int HopLimit);

#ifdef __cplusplus
}
#endif

#endif //  __UTIL_UDP_H__

// Close the doxygen group
/**
 * @}
 */
