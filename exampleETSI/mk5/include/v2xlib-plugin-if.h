#pragma once
/**
 * @addtogroup v2xlib_plugin V2X plugin system
 * @{
 *
 * @file v2x-lib plugin header file
 *
 * A plugin must declare a non-static 'struct V2XLibPlugin V2XLibPlugin' data
 * structure, with V2XLIB_PLUGIN() @ref v2xlib-plugin.h in order to be included.
 *
 * This is the common interface for dynamically loaded plugins.
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_IF_H__
#define __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_IF_H__

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// A symbol name with versioing *string* in the form "V2XLibPlugin_x_y" where
///   x is the major version number,
///   y is the minor version number.
#define V2XLIB_PLUGIN_SYMBOL_NAME V2XLibPlugin_1_0

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// A plugin structure
typedef struct V2XLibPlugin
{
  /// Name of the plugin
  const char *pName;
  /// Initialization function to call once the plugin is loaded
  int (* Init) (void);
  /// De-initialization function to call before the plugin is unloaded
  void (* Exit) (void);
} tV2XLibPlugin;

/// A plugin declaration
#define V2XLIB_PLUGIN(_pName, _Init, _Exit)    \
  struct V2XLibPlugin V2XLIB_PLUGIN_SYMBOL_NAME = { \
    .pName = _pName,                           \
    .Init  = _Init,                            \
    .Exit  = _Exit,                            \
  }

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

#ifdef __cplusplus
}  // End of the 'C' block
#endif

#endif // __STACK__PLAT__PLUGIN__V2XLIB_PLUGIN_IF_H__
/**
 * @}
 */
