#pragma once
/**
* @addtogroup ieee1609_net_user IEEE 1609 POSIX library (libnet1609)
* @{
*
* @file
* IEEE 1609 POSIX User space API
*
*/

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LIBNET1609__LIBNET1609_H
#define __LIBNET1609__LIBNET1609_H

#ifdef __cplusplus
extern "C"
{
#endif

  void IEEE1609Init(void);
  void IEEE1609DeInit(void);

#ifdef __cplusplus
}
#endif

#endif // __LIBNET1609__LIBNET1609_H
/**
* @}
*/
