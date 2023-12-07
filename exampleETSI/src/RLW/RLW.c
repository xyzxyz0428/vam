/**
 * @addtogroup app_rlw Red Light Warning app plugin
 * @{
 *
 *
 * @dontinclude RLW.c
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "RLW.h"
#include "RLW-rx.h"

#include "v2xlib-plugin-if.h"
#include "debug-levels.h"

#include <errno.h>
#include <string.h>

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL RLW_Cust_App_RLW_DebugLevel

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

/// Singleton
tRLW RLW;

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

#if defined(UNITTEST)
tRLW *RLW_Ptr(void)
{
  if (RLW.Active == true)
    return &RLW;
  else
    return NULL;
}
#endif

void RLW_PrintStats(FILE *pStream)
{
  (void)pStream;
  return;
}

/**
 * @brief Initialize RLW
 * @return Success: 0, Error: @ref TA_ErrCode or negative errno
 */
int RLW_Init(void)
{
  int Res = -ENOSYS;

  d_fnstart(D_TST, 0, "()\n");

  memset(&RLW, 0, sizeof(RLW));

  // Get the RLW specific configuration (from the .conf file)
  (void)RLW_Cust_App_RLW_Copy(&RLW.Param, NULL);

  // Initially no handle
  RLW.Rx.SPATMAP.Handle = -1;

  if (RLW.Param.ENABLE == 0)
  {
    Res = 0;
    d_printf(D_NOTICE, 0, "RLW not enabled (%d)\n", RLW.Param.ENABLE);
    goto Exit;
  }

  // Start reception
  Res = RLWRx_Init();
  if (Res != 0)
  {
    d_printf(D_WARN, 0, "RLWRx_Init() == %d\n", Res);
    RLW.Rx.Active = false;
    goto Exit;
  }
  RLW.Rx.Active = true;
  // Success
  RLW.Active = true;

Exit:
  d_fnend(D_TST, 0, "() = %d\n", Res);
  return Res;

}

/**
 * @brief De-initialize the RLW feature
 */
void RLW_Exit(void)
{
  d_fnstart(D_TST, 0, "()\n");

  if (RLW.Rx.Active)
  {
    RLWRx_Exit();
    RLW.Rx.Active = false;
  }

  RLW.Active = false;

  d_fnend(D_TST, 0, "()\n");
  return;
}


/**
 * @brief V2XLib plugin init wrapper
 */
static int RLW_PluginInit(void)
{
  return RLW_Init();
}

/**
 * @brief V2XLib plugin exit wrapper
 */
static void RLW_PluginExit (void)
{
  RLW_Exit();
}

/**
 * @brief V2XLib plugin definition
 */
V2XLIB_PLUGIN("Red Light Warning",
              RLW_PluginInit, RLW_PluginExit);

/**
 * @}
 */
