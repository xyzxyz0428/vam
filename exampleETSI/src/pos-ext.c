/**
 * @addtogroup mod_pos_ext External POS Module
 * @{
 *
 * This module demonstrates the use of the external POS interface.
 *
 * Typically, this module is enabled to provide position updates
 * whilst the internal position from the 'libpos' Stack library
 * is disabled (with "Cohda_GPSRx_Source = 0".)
 *
 * This demonstration code only sets a fixed position, but of
 * course any implementation can be used to update the data that
 * is provided to LPHPosFix_Position.
 *
 * @file exampleETSI/src/pos-ext.c Example external POS interfacing module
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "util.h"
#include "lph.h"

#include "debug-levels.h"

#include "ExampleETSI_debug.h"

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_PosExt_DebugLevel

#if defined(__QNX__)
typedef union sigval sigval_t;
#endif

//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static void PosExt_Action (sigval_t SigVal);

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------

timer_t Id;

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

/**
 * @brief Initialises the external position provider
 * @return Status, 0 on success
 */
int PosExt_Init(void)
{
  struct sigevent Evt;
  struct itimerspec Spec;
  int Res = 0;

  d_printf(D_DBG, NULL, "()\n");

  memset(&Evt, 0, sizeof(Evt));
  Evt.sigev_notify = SIGEV_THREAD;
  Evt.sigev_notify_function = PosExt_Action;

  // Use a repeating timer to update position API
  Res = timer_create(CLOCK_REALTIME, &Evt, &Id);
  if (Res != 0)
  {
    d_error(D_WARN, NULL, "Timer create failed (errno %d, %s)\n",
            errno, strerror(errno));
    goto Exit;
  }

  // Timer is repeating
  Spec.it_interval.tv_sec = 1;
  Spec.it_interval.tv_nsec = 0;

  Spec.it_value.tv_sec = 1;
  Spec.it_value.tv_nsec = 0;

  Res = timer_settime(Id, 0, &Spec, NULL);
  if (Res != 0)
  {
    d_error(D_WARN, NULL, "Timer start failed (errno %d, %s)\n",
            errno, strerror(errno));
    goto Exit;
  }

Exit:
  return Res;
}

/**
 * @brief Periodic position provider action
 * @param SigVal Signal (not used)
 */
static void PosExt_Action (sigval_t SigVal)
{
  d_printf(D_DBG, NULL, "()\n");

  tLPHPosFixReturnCode Stat;
  tLPHPosFix PosFix;

  // Not required
  (void) SigVal;

  // Update position information
  struct timespec TimeUTC;
  clock_gettime(CLOCK_REALTIME, &TimeUTC);

  // Typically, for an OBU, the time, lat, long, alt, heading, speed and
  // position accuracy are the minimum data set
  PosFix.Mode = LPH_POS_FIX_MODE_3D;
  PosFix.UtcTime_s = TimeUTC.tv_sec + (TimeUTC.tv_nsec / 1000000000.0);
  PosFix.Latitude_deg = -34.0;
  PosFix.Longitude_deg = 138.1;
  PosFix.Altitude_m = 10.0;
  PosFix.Heading_deg = 45.0;
  PosFix.GroundSpeed_mps = 1.0;
  PosFix.VerticalSpeed_mps = NAN;

  PosFix.UtcTimeErr_s = NAN;
  PosFix.PosErrSemiMajorAxisLen_m = 5.0;
  PosFix.PosErrSemiMinorAxisLen_m = 2.5;
  PosFix.PosErrSemiMajorAxisOrientation_deg = 90.0;
  PosFix.AltitudeErr_m = NAN;
  PosFix.HeadingErr_deg = NAN;
  PosFix.GroundSpeedErr_mps = NAN;
  PosFix.VerticalSpeedErr_mps = NAN;

  PosFix.SatellitesVisible = LPH_POS_FIX_UNKNOWN_SATELLITES_VIS;
  PosFix.DOP = NAN;

  Stat = LPHPosFix_Position(&PosFix);

  if (Stat != LPH_POS_FIX_SUCCESS)
  {
    d_error(D_WARN, NULL, "Pos update failed %d\n", Stat);
  }
}

/**
 * @brief De-initialises the external position provider
 */
void PosExt_DeInit(void)
{
  d_printf(D_DBG, NULL, "()\n");

  timer_delete(Id);
}


// Close the Doxygen group
/**
 * @}
 */
