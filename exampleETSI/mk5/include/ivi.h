/**
 * @addtogroup cohda_ivi_api In Vehicle Information (IVI) API
 * @{
 *
 * @file
 * ivi -rx.h: IVI module main function definitions
 *
 */
//==============================================================================
// Copyright (c) 2015
// Cohda Wireless PTY LTD
//==============================================================================

//------------------------------------------------------------------------------
// Module: IVI Module
//
//------------------------------------------------------------------------------

#ifndef __IVI_H_
#define __IVI_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
int IVI_Init(void);
void IVI_Deinit(void);

#ifdef __cplusplus
}
#endif

#endif // __IVI_H_
// Close the doxygen group
/**
 * @}
 */
