#pragma once
/**
 * @addtogroup v2xlib_plugin V2X plugin system
 * @{
 *
 * @file internal v2x-lib plugin header file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_H__
#define __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_H__

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
int  Plugin_Init(void);
void Plugin_Exit(void);

#ifdef __cplusplus
}  // End of the 'C' block
#endif

#endif // __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_H__
/**
 * @}
 */
