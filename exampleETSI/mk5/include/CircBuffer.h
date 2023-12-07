#pragma once
/**
 * @addtogroup util_circbuffer Non-Blocking Circular Buffers
 * @{
 *
 * @section util_circbuffer_dd What Does It Do
 *
 * Provides a single-writer/single-readers thread-safe circular queue.
 *
 * @file
 *
 * Circular Buffer Queue
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UTIL_CIRC_BUFFER_H_
#define __UTIL_CIRC_BUFFER_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

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

/// Bufer Queue handle
typedef struct CB_CircBuffer
{
} tCB_CircBuffer;

/// Initialise a circular buffer queue of given element size and depth.
tCB_CircBuffer * CB_Init(size_t elemSize,
                         size_t numElems);

/// Free an initialised buffer queue.
void CB_Free(tCB_CircBuffer * cb);

// WRITER API

/// Get a pointer to the safe-to-write-to element
void * CB_GetWriteBuffer(tCB_CircBuffer * cb);

/// Commit the current element and get a pointer to the next
void * CB_CommitWriteBuffer(tCB_CircBuffer * cb);

/// Is there room on the queue for another write?
bool CB_QueueFull(tCB_CircBuffer * cb);

// READER API

/// Get a pointer to the next element to read
const void * CB_GetReadBuffer(tCB_CircBuffer * cb);

/// Free the currently read element and fetch a pointer to the next element to read
const void * CB_FreeReadBuffer(tCB_CircBuffer * cb);

// Number of elements in the queue
int CB_QueuePending(tCB_CircBuffer * cb);

/// Wait for data (see sem_wait(3) )
int CB_wait(tCB_CircBuffer * cb);

/// Wait for data (see sem_trywait(3) )
int CB_trywait(tCB_CircBuffer * cb);

/// Wait for data (see sem_timedwait(3) )
int CB_timedwait(tCB_CircBuffer * cb, const struct timespec *abs_timeout);

#ifdef __cplusplus
}
#endif

#endif // __UTIL_CIRC_BUFFER_H_
/**
 * @}
 */
