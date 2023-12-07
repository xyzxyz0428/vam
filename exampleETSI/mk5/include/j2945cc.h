#pragma once
/**
 * @addtogroup app_j2945cc J2945/1 2016 Congestion Control
 * @{
 *
 * @file
 */

//------------------------------------------------------------------------------
// Copyright (c) 2017 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __J2945CC_H__
#define __J2945CC_H__

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

#ifdef  __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Position of the host vehicle in time and space
typedef struct J2945CCPosition
{
  struct timeval Time; //!< Timestamp of this position
  int Heading;         //!< Heading of the vehicle in as per SAE J2735
  int Speed;           //!< Speed of the vehicle as per SAE J2735
  int Latitude;        //!< Latitude of the vehicle as per SAE J2735
  int Longitude;       //!< Longitude of the vehicle as per SAE J2735
} tJ2945CCPosition;

/// Opaque per-remote data
typedef struct J2945CCRemote tJ2945CCRemote;

/// Iterate over the allocated tJ2945CCRemote objects, on first call pCurrent
/// will be NULL - on subsequent calls pCurrent will be the previously returned
/// object
typedef tJ2945CCRemote *(fJ2945CCRemoteIterator)(tJ2945CCRemote *pCurrent,
                                                 void *pPriv);

//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Initialise J2945 Congestion Control library
 * @return 0 on success, negative errno on error
 */
int J2945CC_Init(void);

/**
 * @brief Create and do initial processing for a new remote vehicle
 *
 * @param Range_m Range to the remote vehicle in metres
 * @param SeqNbr The current sequence number for the remote
 * @return A newly allocated tJ2945CCRemote structure. This should be
 * provided on future calls to J2945CC_UpdateRemote() etc.
 *
 * This should be called on receipt of the first message from a remote vehicle
 * with the sequence number from that first message. It is up to the caller to
 * manage the returned tJ2945CCRemote so that it can be provided again on
 * subsequent calls to J2945CC_UpdateRemote() / J2945CC_FreeRemote()
 */
tJ2945CCRemote *J2945CC_NewRemote(double Range_m,
                                  uint8_t SeqNbr);

/**
 * @brief Process an update for an existing remote vehicle
 *
 * @param pRemote An existing tJ2945CCRemote create previously on a call to J2945CC_NewRemote()
 * @param Range_m Range to the remote vehicle in metres
 * @param SeqNbr The new sequence number for this remote
 *
 * This should be called on each subsequent message received from a remote
 * vehicle along with the new sequence number for each message.
 */
void  J2945CC_UpdateRemote(tJ2945CCRemote *pRemote,
                           double Range_m,
                           uint8_t SeqNbr);

/**
 * @brief Cleanup an existing tJ2945CCRemote
 *
 * @param pRemote the tJ2945CCRemote to cleanup
 *
 * This should be called once the remote vehicle is not being tracked /
 * received from anymore
 */
void J2945CC_FreeRemote(tJ2945CCRemote *pRemote);

/**
 * @brief Perform the periodic processing - call this every 100ms
 *
 * @param [in] RawCBP The raw channel busy percentage between 0.0 and 1.0
 * @param [in] pCurrentPos The current position of the host vehicle
 * @param [in] CriticalEvent Whether the host vehicle has a critical event
 * @param [in] pLastTxPos The position of the host vehicle at last transmit
 * @param [in] pIter  The function to call to iterate over the existing tJ2945CCRemote objects
 * @param [in] pPriv  The data to pass to pIter on each call
 * @param [in,out] pNextTxTime Time of the current scheduled next transmission
 * @param [out] pMaxITT_ms The new MaxITT value in milliseconds
 * @param [out] pTxPower The new transmit power value in dBm
 * @return Negative error code on error, zero on success but if no update to
 * the next trasmission time is required, and a positive value if the next
 * transmission time should be changed - the value of the next transmission
 * time in pNextTxTime will be updated to reflect this next time
 *
 * Performs periodic processing - should be called every 100ms
 *
 */
int J2945CC_PeriodicProcess(float RawCBP,
                            const tJ2945CCPosition *pCurrentPos,
                            bool CriticalEvent,
                            const tJ2945CCPosition *pLastTxPos,
                            fJ2945CCRemoteIterator *pIter,
                            void *pPriv,
                            struct timespec *pNextTxTime,
                            unsigned int *pMaxITT_ms,
                            int *pTxPower);

/**
 * @brief Exit the J2945 Congestion Control library
 */
void J2945CC_Exit(void);

#ifdef  __cplusplus
}
#endif

#endif // __J2945CC_H__
/**
 * @}
 */
