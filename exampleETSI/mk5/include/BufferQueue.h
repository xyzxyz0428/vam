/**
 * @addtogroup util_bufferqueue Non-Blocking Queue of Buffers
 * @{
 *
 * @section bufferqueue_dd What Does It Do
 *
 * Provides a single-writer/multiple-readers thread-safe queue of buffers.
 *
 * @file
 *
 * Queue of Buffers
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UTIL_BUFFER_QUEUE_H_
#define __UTIL_BUFFER_QUEUE_H_

#define UBQ_PARANOID_READER_MODE 1

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

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

// Pre-declaration so we can point to it
struct UtilBufferQueue;

/// Buffer Queue Reader (Reader Client Handle)
typedef struct UtilBufferQueueReader
{
  /// Reader in use
  volatile bool busy;
  /// Buffer queue associated with this reader
  struct UtilBufferQueue * q;
  /// Current read location
  volatile size_t readIdx;
#if UBQ_PARANOID_READER_MODE
  /// Make sure we don't have multiple threads using the same reader
  pthread_t reader;
#endif
} tUtilBufferQueueReader;

/// Buffer Queue
typedef struct UtilBufferQueue
{
  /// Maximum number of readers
  unsigned   numReaders;
  /// Size of each buffer
  unsigned   bufferSize;
  /// Number of readers per buffer
  unsigned * readCounters;
  /// mutex lock
  pthread_mutex_t lock;
  /// Readers
  tUtilBufferQueueReader * readers;
  /// Buffers
  uint8_t * buff;
  /// Index containing the latest valid data
  volatile size_t safeToReadIdx;
  /// Index of a buffer which is safe to write to
  volatile size_t safeToWriteIdx;
#if UBQ_PARANOID_READER_MODE
  /// Make sure we don't have multiple writer threads
  pthread_t writer;
#endif
} tUtilBufferQueue;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// API for Setup/Cleanup (usually done by WRITER)
tUtilBufferQueue * UBQ_Setup(unsigned numReaders, unsigned bufferSize);
bool               UBQ_Cleanup(tUtilBufferQueue * q);

// API for WRITER
void * UBQ_WriteBufferGet(tUtilBufferQueue * q);
void   UBQ_WriteBufferRevert(tUtilBufferQueue * q);
void * UBQ_WriteBufferCommit(tUtilBufferQueue * q);

// API for READERS
tUtilBufferQueueReader * UBQ_ReaderOpen(tUtilBufferQueue * q);
void                     UBQ_ReaderClose(tUtilBufferQueueReader * rdr);
const void *             UBQ_ReadBufferGet(tUtilBufferQueueReader * rdr);

#ifdef __cplusplus
}
#endif

#endif // __UTIL_BUFFER_QUEUE_H_
// Close the doxygen group
/**
 * @}
 */
