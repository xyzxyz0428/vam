/**
 * @addtogroup QS_LIB Message Queue system
 * @{
 *
 * @section QS_LIB_dd What Does It Do
 * API for the use of the POSIX threads for inter thread messaging
 *
 * @file
 *
 * Interface and structure definitions for message passing
 *
 * To abstract some of the POSIX message queue configuration and handling
 * from user code a simple API is defined to allow user threads to send
 * and receive messages.
 *
 * Each message can contain a payload buffer that is referenced from the
 * message (as is that payloads 'free' pointer).
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __QS_LIB_H_
#define __QS_LIB_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#ifdef SYSVMSGQUEUES
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#else
#include <mqueue.h>
#endif
#include <sys/time.h>

// Queue lib users probably want the Queue IDs
#include "id-global.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#ifdef SYSVMSGQUEUES

/// Normal queue attributes
#define Q_NORMAL_ATTR        (IPC_CREAT| IPC_EXCL)
/// Create a shared queue
#define Q_SHARED_ATTR_CREATE (IPC_CREAT          )
/// Open a shared queue (must have been created by someone else)
#define Q_SHARED_ATTR_OPEN   (                  0)

/// Message queue permission
#define MSGPERM 0600

#else

/// Normal queue attributes
#define Q_NORMAL_ATTR        (O_CREAT| O_EXCL| O_RDWR)
/// Create a shared queue
#define Q_SHARED_ATTR_CREATE (O_CREAT|         O_RDWR)
/// Open a shared queue (must have been created by someone else)
#define Q_SHARED_ATTR_OPEN   (                 O_RDWR)

#endif

/// Queue name at least 2 chars (+1 for slash)
#define Q_NAME_MIN_LEN 2

/// Queue name limited to 31 chars
#define Q_NAME_MAX_LEN 32

/// Queue size limited
#define Q_SIZE_MAX_LEN 256


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Message ID is 32 bits
typedef unsigned int tQsMsgId;

/// Queue ID is 32 bits
typedef unsigned int tQsQueueId;

/// Message communication status definitions
typedef enum
{
  QS_ERR_NONE, ///< OK
  QS_ERR_FAIL, ///< Generic Failure
  QS_ERR_TIMEOUT, ///< Timeout
  QS_ERR_TOO_BIG, ///< Message is too big to send
  QS_ERR_SEND_FAIL, ///< msgsnd/msgrcv/mq_timedsend fail
  QS_ERR_NO_QUEUE, ///< Queue does not exist
  QS_ERR_INV_ID, ///< invalid queue ID
  QS_ERR_READ_FAIL, ///< mq_receive fail
  QS_ERR_OPEN_FAIL, ///< msg_get/mq_open fail
  QS_ERR_ATTRIB_GET_FAIL, ///< msgctl(IPC_STAT) fail
  QS_ERR_ATTRIB_SET_FAIL, ///< msgctl(IPC_SET) fail
  QS_ERR_LOCK_FAIL, ///< Lock fail
  QS_ERR_CLOSE_FAIL, ///< msgctl(IPC_RMID)/mq_unlink fail
  QS_ERR_TOO_MANY, ///< too many queues
  QS_ERR_INV_CONF, ///< Invalid configuration (e.g. ID mis-match)
  QS_ERR_NUM_CODES
} tQsStatus;

/// Previously (widely) used names
#define QSSTATUS_OK       QS_ERR_NONE
#define QSSTATUS_FAIL     QS_ERR_FAIL
#define QSSTATUS_TIMEOUT  QS_ERR_TIMEOUT

/// Message communication priority choices
typedef enum
{
  // Some RTOSs don't like a priority of 0
  QSPRIORITY_MIN = 1,
  QSPRIORITY_DEFAULT = 1,
  QSPRIORITY_HIGH,
  QSPRIORITY_URGENT,
  QSPRIORITY_MAX
} tQsPriority;

/// Message destructor
typedef void (*tQsFree)(void *);

/// Structure for message referring to data block
typedef struct QsMessageRef
{
  /// Payload location
  void *pPayload;
  /// Free location;
  void *pFree;
  /// Free function
  tQsFree pFunc;
} tQsMessageRef;

/// Message container size defined same size as message reference data
#define MESSAGE_CON_SIZE   sizeof(tQsMessageRef)

/// Message communication structure
typedef struct QsMessage
{
  /// Message ID
  tQsMsgId Id;
  union
  {
    /// Message with reference
    tQsMessageRef Ref;
    /// Message payload
    unsigned char Payload[MESSAGE_CON_SIZE];
  };
} tQsMessage;

/// Queue structure for storing configuration
typedef struct QsQueueConfig
{
  /// Name of queue
  const char Name[Q_NAME_MAX_LEN];
  /// Queue Id
  tQsQueueId Id;
  /// Flags for queue
  int         Flags;
  /// Mode for queue
  // Linux file access permissions, e.g. 666 for all read-write access
  // The recommended setting for Mode is 0 (for no external access)
  mode_t      Mode;
  /// Length of queue
  long        Queue_Size;
} tQsQueueConfig;

/// Queue counters
typedef struct QsQueueCounters
{
  /// label for the queue
  const char *name;
  /// number of messages successfully submitted
  unsigned numSubmitted;
  /// number of messages dropped
  unsigned numDropped;
} tQsQueueCounters;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

const tQsQueueCounters *Msg_GetCounters(tQsQueueId Id);

void Msg_ClearCounters(void);

tQsStatus Msg_SendId(tQsMsgId Id,
                     tQsQueueId Queue,
                     tQsPriority Priority);

tQsStatus Msg_SendRef(tQsMsgId Id,
                      tQsQueueId Queue,
                      tQsPriority Priority,
                      void *pPayload,
                      void *pFree);

tQsStatus Msg_SendCust(tQsMsgId Id,
                       tQsQueueId Queue,
                       tQsPriority Priority,
                       void *pPayload,
                       void (*pFunc)(void *),
                       void *pFree);

tQsStatus Msg_SendCon(tQsMsgId Id,
                      tQsQueueId Queue,
                      tQsPriority Priority,
                      const void *pPayload,
                      size_t Size);

tQsStatus Msg_Recv(tQsQueueId Queue,
                   tQsMessage *pMessage);

tQsStatus Msg_RecvTimed(tQsQueueId Queue,
                        tQsMessage *pMessage,
                        const struct timeval *pTimeout);

tQsStatus Msg_BroadcastId(tQsMsgId    Id,
                          tQsPriority Priority);

tQsStatus Msg_QueueInit(tQsQueueId Queue);

#if (!defined(SYSVMSGQUEUES))
int Msg_GetFD(tQsQueueId Queue);
#endif

tQsStatus Msg_QueueDeInit(tQsQueueId Queue);

tQsStatus Msg_QLibSetup(const tQsQueueConfig *pQueueConf,
                        unsigned int QueueCount);

tQsStatus Msg_QLibShutdown(void);


#ifdef __cplusplus
}
#endif

#endif // __QS_LIB_H_

// Close the Doxygen group
/**
 * @}
 */
