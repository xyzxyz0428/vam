#pragma once
/**
 * @addtogroup cohda_spat_api
 * @{
 *
 * @file
 * spat-utils.h: SPaT helper utilities
 *
 */
//==============================================================================
// Copyright (c) 2014
// Cohda Wireless PTY LTD
//==============================================================================

//------------------------------------------------------------------------------
// Module: SPaT and Map Module
// Author(s): Ayman Grais
//
// Description:
//  Reference: CWD-MKx-xxxx-SPaT_MAP_Application_Design (by Alex Murray):
//
//  Generic framework for the implementation of SAE J2735 SPaT/MAP based
//  applications within the Cohda 1609 Facilities Layer. Framework is intended
//  to allow for multiple SPaT/MAP-based applications to be easily implemented,
//  with each application only performing the specific steps required for its
//  own operation without unduly repeating calculations made by other similar
//  applications.
//
//  Objective is toWe wish to have a common framework which handles the various
//  operations required by each application – i.e. handling incoming SPaT / MAP
//  messages, processing of messages, storage of messages, geolocation of host
//  vehicle within a MAP etc. This common framework should also allow all of
//  SPaT/MAP based applications to be easily implemented using the framework as
//  a basis.
//
//  MAP messages describe the location and geometry of a given intersection.
//  Signal Phase and Timing (SPaT) messages describe the states of the signal
//  groups for a given intersection. The MAP message is static whilst the SPaT
//  message is generally updated each time it is sent. In general it is assumed
//  MAP messages are transmitted at ~1 message per second, whilst SPaT messages
//  are sent at ~0.1 message per second. This design targets the SPAT/MAP
//  message format as described in SAE J2735 2009.11
//
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

#ifndef __SPAT_UTILS_H_
#define __SPAT_UTILS_H_

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
// Type definitions
//------------------------------------------------------------------------------
// Maximum delta between two points retuned in case of error: 20 KM
#define MAX_DELTA_DIST  20000


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void SPATMAP_UtilInit(void);
float SPATMAP_UtilGetAverageBearing(const float* pArray, int Size);
float SPATMAP_UtilGetBearing(int32_t Lat1, int32_t Lng1,
                             int32_t Lat2, int32_t Lng2);
float SPATMAP_UtilGetBearingXY(float X1, float Y1, float X2, float Y2);
float SPATMAP_UtilGetDeltaX(int32_t Lat1, int32_t Lng1,
                            int32_t Lat2, int32_t Lng2);
float SPATMAP_UtilGetDeltaY(int32_t Lat1, int32_t Lng1,
                            int32_t Lat2, int32_t Lng2);
float SPATMAP_UtilGetDistance(int32_t Lat1, int32_t Lng1,
                              int32_t Lat2, int32_t Lng2);
float SPATMAP_UtilGetDistanceToSegment(float SegStartX, float SegStartY,
                                       float SegEndX, float SegEndY,
                                       float PointX, float PointY);
float SPATMAP_UtilGetDistanceXY(float X1, float Y1, float X2, float Y2);
uint32_t SPATMAP_UtilBytesToUint32(const uint8_t *pBuffer, uint8_t Size, bool IsBigE);
int32_t  SPATMAP_UtilBytesToInt32 (const uint8_t *pBuffer, uint8_t Size, bool IsBigE);
uint16_t SPATMAP_UtilBytesToUint16(const uint8_t *pBuffer, uint8_t Size, bool IsBigE);
int16_t  SPATMAP_UtilBytesToInt16 (const uint8_t *pBuffer, uint8_t Size, bool IsBigE);

#ifdef __cplusplus
}
#endif

#endif // __SPAT_UTILS_H_
// Close the doxygen group
/**
 * @}
 */
