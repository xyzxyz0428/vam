/**
 * @addtogroup can_rx_api CAN Send/Receive API
 * @{
 *
 * @section can_rx_api_dd What Does It Do
 *
 * Sets up the CAN Receiver. Packets are passed to the appropriate registered
 * handler (registered via CANRx_AddCANID()) for further processing.
 *
 * @file
 *
 * Interface message ID definitions
 *
 * Define supported messages
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __CAN_RX_IF_H_
#define __CAN_RX_IF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if (defined(__QNX__))
typedef uint32_t canid_t;
struct can_frame
{
    canid_t can_id;
    uint8_t can_dlc;
    uint8_t data[8] __attribute__((aligned(8)));
};
#else
#include <linux/can.h>
#endif


//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Promiscuous CAN handler
#define CAN_ID_PROMISCUOUS_MODE 0xffffffffUL


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Struct to read raw CAN message
typedef struct CANRxMsg
{
  union{
    /// CAN frame from linux/can.h
    struct can_frame frame;
    /// User-friendly
    struct
    {
      /// Skip over the CAN header
      uint64_t _pad;
      /// Payload as bytes, short etc.
      union
      {
        uint8_t  Byte[8];
        uint16_t Short[4];
        uint32_t Int[2];
        uint64_t Raw;
      };
    };
  };
  uint64_t timestamp_us;
} tCANRxMsg;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// CALL THIS FIRST!!
void CANRx_LibraryInit (void);

/// Start interface thread
int CANRx_ThreadInit (int SchedulerPolicy,
                      int SchedulerPriority);

/// Callback type used to handle an incoming CAN msg
typedef void (tCANRxCallback)(const tCANRxMsg *Msg,
                              void *pPriv);

/// Register to receive messages with a given CAN Id
int CANRx_AddCANID(uint32_t Id,
                   tCANRxCallback * Callback,
                   void *pPriv,
                   unsigned minInterval_ms);

/// Unregister to receive messages with a given CAN Id
int CANRx_RemoveCANID(uint32_t Id,
                      tCANRxCallback * Callback,
                      void *pPriv);

/// Send CAN (extended ID)
int CANTx_SendCANIDExt(uint32_t Id,
                       uint8_t Len,
                       const uint8_t *pData);

/// Send CAN (standard ID)
int CANTx_SendCANIDStd(uint16_t Id,
                       uint8_t Len,
                       const uint8_t *pData);

/// Inject a CAN message to be processed by the registered receivers
int CANRx_HandleRaw(const tCANRxMsg *pMsg, ssize_t NbrBytes);

/// Stop interface thread
void CANRx_ThreadDeinit (void);

/// CALL THIS LAST!!
void CANRx_LibraryDeinit( void);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_RX_IF_H_ */

/**
 * @}
 */
