/**
 * @addtogroup util_pktbuf ETSI ITS Network packet buffers
 * @{
 *
 * @section util_pktbuf_ ETSI stack zero copy packet buffers
 *
 * @subsection util_pktbuf_tx Transmit packets
 *  - Allocate with PktBuf_Alloc()
 *   - Zero sizes are recorded in each 'Len' element of tUtilPktBufEntry (except payload)
 *  - Each stack element should update their relevant element:
 *   - FAC shall populate DescNetwork and set Payload
 *   - BTP shall update DescNetwork and set HdrTransport
 *   - GN shall populate DescLink and set HdrNetworkCommon & HdrNetworkBasic
 *    - Optional Security calls will update HdrNetworkSec and TlrNetworkSec
 *   - G5 shall DescMedium(G5XTxDescriptor + EthHdr) and set HdrLLC before sending buffer
 *
 * @subsection util_pktbuf_rx Receive packets
 *  - Allocate with PktBuf_Alloc_NoHeaders()
 *   - Zero sizes are recorded in each 'Len' element of tUtilPktBufEntry (except lowest layer, e.g HdrLLC)
 *  - Each stack element should update their relevant element:
 *   - G5 shall set DescMedium (G5XRxDescriptor + EthHdr) and set HdrNetworkBasic
 *   - GN shall set DescNetwork and set HdrNetworkCommon & HdrTransport
 *    - Optional Security calls will update HdrNetworkSec and TlrNetworkSec
 *   - BTP shall set Payload
 *   - FAC shall set DescApplication (optional) & use Payload
 *
 * @note It is the responsibility of each layer to check that they don't exceed UTIL_PKTBUF_*_MAX
 *
 * @note The on-air packet data is expected to be continuous in memory, so each element's
 *       pointer and length field should be updated with this in mind as the processing proceeds
 *
 * @file
 *
 * ETSI stack zero copy packet buffer headers
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __UTIL_PACKET_BUFFER_H_
#define __UTIL_PACKET_BUFFER_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

// Keep them multiples of 4
/// Maximum size of canary marker
#define UTIL_PKTBUF_CANARY_MAX   (4)
/// Maximum size of over the air transport headers
#define UTIL_PKTBUF_HDR_TRANSPORT_MAX   (4)
/// Maximum size of over the air network common headers
#define UTIL_PKTBUF_HDR_NET_COMMON_MAX  (56)
/// Maximum size of over the air network secure headers
#define UTIL_PKTBUF_HDR_NET_SEC_MAX  (8)
/// Maximum size of over the air network secure trailer
#define UTIL_PKTBUF_TLR_NET_SEC_MAX  (512)
/// Maximum size of over the air network basic headers
#define UTIL_PKTBUF_HDR_NET_BASIC_MAX  (4)
/// Maximum size of over the air link headers
#define UTIL_PKTBUF_HDR_LINK_MAX  (72)

/// Maximum size of application descriptors
#define UTIL_PKTBUF_DESC_APP_MAX (32)
/// Maximum size of network descriptors
#define UTIL_PKTBUF_DESC_NET_MAX (144)
/// Maximum size of link descriptors
#define UTIL_PKTBUF_DESC_LINK_MAX (64)
/// Maximum size of MAC descriptors
#define UTIL_PKTBUF_DESC_MAC_MAX (48)

/// Maximum size of packet buffer memory
#define UTIL_PKTBUF_MAX  (3200)

/// Maximum size of over the air packet headers
#define UTIL_PKTBUF_HEADERS_SIZE (UTIL_PKTBUF_HDR_NET_BASIC_MAX + \
                                  UTIL_PKTBUF_HDR_NET_SEC_MAX + \
                                  UTIL_PKTBUF_HDR_NET_COMMON_MAX + \
                                  UTIL_PKTBUF_HDR_TRANSPORT_MAX + \
                                  UTIL_PKTBUF_TLR_NET_SEC_MAX)

/// Maximum size of over the air packet payload
#define UTIL_PKTBUF_PAYLOAD_MAX  (UTIL_PKTBUF_MAX - UTIL_PKTBUF_HEADERS_SIZE)

/// mask bits for obtaining packet size
#define UTIL_PKTBUF_MASK_HdrLLC           (1 << 0)
#define UTIL_PKTBUF_MASK_HdrNetworkBasic  (1 << 1)
#define UTIL_PKTBUF_MASK_HdrNetworkSec    (1 << 2)
#define UTIL_PKTBUF_MASK_HdrNetworkCommon (1 << 3)
#define UTIL_PKTBUF_MASK_HdrTransport     (1 << 4)
#define UTIL_PKTBUF_MASK_Payload          (1 << 5)
#define UTIL_PKTBUF_MASK_TlrNetworkSec    (1 << 6)

#define UTIL_PKTBUF_MASK_SignedTotal    (UTIL_PKTBUF_MASK_HdrNetworkSec + \
                                         UTIL_PKTBUF_MASK_HdrNetworkCommon + \
                                         UTIL_PKTBUF_MASK_HdrTransport + \
                                         UTIL_PKTBUF_MASK_Payload + \
                                         UTIL_PKTBUF_MASK_TlrNetworkSec)


// uint32_t canary for the start of the dynamically sized data area "<CODA>"
#define UTIL_PKTBUF_CANARY_MAGIC   0x3fc0da3e
// uint32_t canary for the start of the packet buffer data area "CODA<<"
#define UTIL_PKTBUF_CANARY_START   0xc0da3c3c
// uint32_t canary for the end of the packet buffer data area ">>CODA"
#define UTIL_PKTBUF_CANARY_END     0x3e3ec0da

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

typedef enum
{
  /// Buffer allocated, but not used
  PKTBUF_LAYER_NONE,
  /// ACCESS (G5/PC5)
  PKTBUF_LAYER_ACCESS,
  /// NETWORK (GN)
  PKTBUF_LAYER_NETWORK,
  /// NETWORK (GN) Forwarding
  PKTBUF_LAYER_NETWORK_FWD,
  /// TRANSPORT (BTP)
  PKTBUF_LAYER_TRANSPORT,
  /// FACILITIES (FAC)
  PKTBUF_LAYER_FACILITIES,
  /// CLASSIFICATION (TC)
  PKTBUF_LAYER_CLASSIFICATION,
  /// APPLICATION (APP)
  PKTBUF_LAYER_APPLICATION,
} eUtilPktBufLayer;

/// @copydoc eUtilPktBufLayer
typedef uint8_t tUtilPktBufLayer;

typedef enum
{
  /// Media unknown
  PKTBUF_MEDIA_UNKNOWN,
  /// ITS-G5
  PKTBUF_MEDIA_ITSG5,
  /// ITS-G5
  PKTBUF_MEDIA_ITSPC5,
  /// Cellular-V2X
  PKTBUF_MEDIA_CV2X,
  /// Ethernet
  PKTBUF_MEDIA_ETHERNET,
  /// File
  PKTBUF_MEDIA_FILE,
} eUtilPktBufMedia;

/// @copydoc eUtilPktBufMedia
typedef uint8_t tUtilPktBufMedia;

/// Buffer entry (pointer/length tuple)
typedef struct UtilPktBufEntry
{
  /// Buffer pointer
  uint8_t *pData;
  /// Buffer length
  size_t Len;
} tUtilPktBufEntry;

/// Canary marker
typedef struct UtilPktCanary
{
  /// Marker data
  uint32_t Marker;
} tUtilPktCanary;

/// Table of buffer entries
/// Each buffer entry must consist of 
/// - a pointer, used to access the relevant part of the packet data
/// - a size (type size_t), used to track the size of the relevant part of the packet data
/// Some items are union-ed to migrite away from the older generic access structure
/// to a more type-specific access structure
typedef struct UtilPktBufTable
{
  /// Start descriptor canary
  /// @sa tUtilPktCanary
  struct {
    struct UtilPktCanary *pCanaryDesc;
    size_t CanaryDescLen;
  };

  /// Application descriptor (APP)
  /// @sa tETSIAppDesc
  union {
    struct {
      struct ETSIAppDesc *pETSIAppDesc;
      size_t ETSIAppDescLen;
    };
    struct UtilPktBufEntry DescAppl __attribute__((deprecated));
  };

  /// Transport descriptor (FAC<->BTP)
  /// @sa tETSIGeoNetDesc
  union {
    struct {
      struct ETSIGeoNetDesc *pETSIGeoNetDesc;
      size_t ETSIGeoNetDescLen;
    };
    struct UtilPktBufEntry DescNetwork __attribute__((deprecated));
  };

  /// Link descriptor (GN<->G5)
  /// @sa tETSIG5Desc
  union {
    struct {
      struct ETSIG5Desc *pETSIG5Desc;
      size_t ETSIG5DescLen;
    };
    struct UtilPktBufEntry DescLink __attribute__((deprecated));
  };

  /// MAC descriptor (G5<->MKX/Radio)
  /// @sa tG5XTxDescriptor
  /// @sa tG5XRxDescriptor (+ struct ethhdr)
  /// @sa tPC5XTxDescriptor
  /// @sa tPC5XRxDescriptor
  union {
    struct {
      struct G5XTxDescriptor *pG5XTxDescriptor;
      size_t G5XTxDescriptorLen;
    };
    struct {
      struct G5XRxDescriptor *pG5XRxDescriptor;
      size_t G5XRxDescriptorLen;
    };
    struct {
      struct PC5XTxDescriptor *pPC5XTxDescriptor;
      size_t PC5XTxDescriptorLen;
    };
    struct {
      struct PC5XRxDescriptor *pPC5XRxDescriptor;
      size_t PC5XRxDescriptorLen;
    };
    struct UtilPktBufEntry DescMedium __attribute__((deprecated));
  };

  /// Start packet buffer canary
  /// @sa tUtilPktCanary
  struct {
    struct UtilPktCanary *pCanaryPktBufStart;
    size_t CanaryPktBufStartLen;
  };

  /// Over-the-air media-specific header (802.11/PC5)
  struct UtilPktBufEntry HdrLLC; ///< @sa tIEEE80211QoSHeader + tSNAPHeader
  /// Over-the-air network basic header (GN Basic)
  struct UtilPktBufEntry HdrNetworkBasic; ///< @sa tETSIGeoNetBasicHdr
  /// Over-the-air network secured header (GN Sec)
  struct UtilPktBufEntry HdrNetworkSec; ///<
  /// Over-the-air network basic header (GN Common)
  struct UtilPktBufEntry HdrNetworkCommon; ///< @sa tETSIGeoNetCommonHdr
  /// Over-the-air transport header (BTP)
  struct UtilPktBufEntry HdrTransport; ///< @sa tETSIBTPPktHdr
  /// Over-the-air payload data
  struct UtilPktBufEntry Payload;
  /// Over-the-air network secured trailer/signature (GN Sec)
  struct UtilPktBufEntry TlrNetworkSec; ///<

  /// End packet buffer canary
  /// @sa tUtilPktCanary
  struct {
    struct UtilPktCanary *pCanaryPktBufEnd;
    size_t CanaryPktBufEndLen;
  };

} tUtilPktBufTable;

#define NUM_PKT_BUF_ENTRIES  \
  (sizeof(tUtilPktBufTable) / sizeof(tUtilPktBufEntry))

/// Packet buffer
typedef struct UtilPacketBuffer
{
  /// Mem location to free
  void *pFree;
  /// free() function to use
  void (*pFunc)(void *);

  /// Total allocated memory
  size_t Allocated;

  union {
    /// Table of elements (to mirror Vector)
    tUtilPktBufEntry Tbl[NUM_PKT_BUF_ENTRIES];
    /// Table of user friendly elements
    tUtilPktBufTable Elem;
  };

  /// Buffer location for signing
  void *pToBeSigned;

  /// LocalIdentity
  uint32_t LocalIdentity;
  /// SourceIdentity
  uint32_t SourceIdentity;

  /// Layer status
  tUtilPktBufLayer Layer;
  /// Media status
  tUtilPktBufMedia Media;

  union {
    struct {
      /// Debug controls
               /// Drop level
               /// 1 = error, 2 += unusual, 3 += normal
      uint16_t DebugDrop :2;
               /// Dump level
               /// 1 = payload, 2 += header, 3 += descriptor
      uint16_t DebugDump :2;
               /// Send level
               /// 1 = between layer, 2 += internal
      uint16_t DebugSend :2;

               /// LocT level
               /// 1 = add/remove, 2 += periodic, 3 += update,
      uint16_t DebugLocT :2;
               /// LDM level
               /// 1 = add/remove, 2 += periodic, 3 += update,
      uint16_t DebugFacCache :2;
               /// LDM level
               /// 1 = add/remove, 2 += periodic, 3 += update,
      uint16_t DebugLDM :2;
               /// App Level
               /// 1 = error, 2 += unusual, 3 += normal
      uint16_t DebugApp :2;

               /// Console
               /// 1 = system, 2 += packet
      uint16_t DebugConsole :2;
    };

    uint16_t DebugRaw;
  };

  /// Dynamically allocated part of PacketBuffer appended to tUtilPacketBuffer struct
  /// PacketBuffer descriptors
  /// PacketBuffer packet headers & payload

} tUtilPacketBuffer;

typedef enum
{
  /// no action
  PKTBUF_FAIL_NOTHING = 0,
  /// log the error
  PKTBUF_FAIL_LOG = 1,
  /// try to do a stacktrace
  PKTBUF_FAIL_STACKTRACE = 2,
  /// abort
  PKTBUF_FAIL_ABORT = 4,
  // default action to take
  PKTBUF_FAIL_DEFAULT = PKTBUF_FAIL_LOG | PKTBUF_FAIL_STACKTRACE | PKTBUF_FAIL_ABORT,
} eUtilPktBufFailActions;

/// @copydoc eUtilPktBufFailActions
typedef uint8_t tUtilPktBufFailActions;

typedef enum
{
  /// no action
  PKTBUF_DUMP_NOTHING = 0,
  /// dump the payload
  PKTBUF_DUMP_PAYLOAD = 1,
  /// dump the payload and headers
  PKTBUF_DUMP_PL_HEADERS = 2,
  /// dump the payload, headers and descriptors
  PKTBUF_DUMP_PL_HD_DESCRIPTORS = 3,
} eUtilPktBufDumpActions;

/// @copydoc eUtilPktBufDumpActions
typedef uint8_t tUtilPktBufDumpActions;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Allocate (and setup) a packet buffer for a Transmitted packet
 *        Typically created in the FAC layer, space is automatically reserved
 *        for pre-pended headers and appended trailers applied at lower layers
 * @param Len Size of Payload to transport down the stack
 * @return A pointer to a packet buffer or NULL on error
 *
 * The Length of the payload section is set to the requested Payload size
 * Other space for headers reserved (with 'Len' set to zero), but their sizes 
 * are expected to be updated as they are determined.
 *
 * @note It is the responsibility of each layer to check that they don't
 * exceed the reserved header space for that layer (UTIL_PKTBUF_*_MAX)
 */
struct UtilPacketBuffer *PktBuf_Alloc (size_t Len);

/**
 * @brief Allocate (and setup) a packet buffer for a Received packet
 *        Typically created in the G5/PC5 layer, no additional space is
 *        reserved as packet headers are part of the received packet
 *        (the packet headers are identified at higher layers)
 * @param RxPktLen Size of received packet to transport up the stack
 * @return A pointer to a packet buffer or NULL on error
 *
 * All sections sizes are set to zero, the length of each header (and
 * ultimate Payload) are expected to be updated as determined at each layer
* 
 * @note Since access layer headers can vary in size, the V2X message
 * (GN) is expected to be aligned to HdrNetworkBasic which allows packet
 * buffers to be forwarded between different access layer technologies without
 * having to move the V2X message content
 */
struct UtilPacketBuffer *PktBuf_Alloc_NoHeaders (size_t RxPktLen);

/**
 * @brief Free a packet buffer
 * @param pPtr Pointer to a packet buffer allocated with PktBuf_Alloc()
 */
void PktBuf_Free (struct UtilPacketBuffer *pPtr);

/**
 * @brief Duplicate a packet buffer
 * @param pOrig Pointer to an original packet buffer allocated with PktBuf_Alloc()
 * @return Pointer to a duplicate packet buffer (allocated with PktBuf_Alloc())
 */
struct UtilPacketBuffer *PktBuf_Dup (const struct UtilPacketBuffer *pOrig);

/**
 * @brief Calculate the used size of a Packet Buffer
 * @param pPtr Pointer to packet buffer
 * @param mask Which parts of the packet buffer to count, see UTIL_PKTBUF_MASK_???
 * @return Total used size of all the nominated parts of the packet buffer
 */
size_t PktBuf_Size (const tUtilPacketBuffer *pPtr, uint32_t mask);

/**
 * @brief Calculate the maximum available size of a Packet Buffer
 * @param pPtr Pointer to packet buffer
 * @param mask Which parts of the packet buffer to count, see UTIL_PKTBUF_MASK_???
 * @return Total maximum available size of all the nominated parts of the packet buffer
 */
size_t PktBuf_MaxSize (const tUtilPacketBuffer *pPtr, uint32_t mask);

/**
 * @brief Check the packet buffer markers for buffer overflow
 * @param pPtr PacketBuffer to check
 * @param FailAction What to do if buffer overflow detected, @ref eUtilPktBufFailActions.
 *
 * @return true if all is OK, false pPtr is NULL or
 *         buffer overflow detected (and PKTBUF_FAIL_ABORT not set)
 */
bool PktBuf_CheckCanaries(const struct UtilPacketBuffer *pPtr, tUtilPktBufFailActions FailAction);

/**
 * @brief Set default packet debug levels
 * @param DropLevel PacketBuffer drop debug level (0-3)
 * @param DumpLevel PacketBuffer dump debug level (0-3)
 * @param SendLevel PacketBuffer send debug level (0-3)
 * @param LocTLevel PacketBuffer location table debug level (0-3)
 * @param FacCacheLevel PacketBuffer FAC message table debug level (0-3)
 * @param LDMLevel PacketBuffer LDM debug level (0-3)
 * @param AppLevel PacketBuffer App layer debug level (0-3)
 * @param Console PacketBuffer console debug level (0-3)
 * @param FailAction PacketBuffer fail action setting
 */
void PktBuf_SetDebugLevels(uint8_t DropLevel, uint8_t DumpLevel, uint8_t SendLevel,
                           uint8_t LocTLevel, uint8_t FacCacheLevel, uint8_t LDMLevel,
                           uint8_t AppLevel, uint8_t Console, tUtilPktBufFailActions FailAction);

#ifdef __cplusplus
}
#endif

#endif // __UTIL_PACKET_BUFFER_H_

// Close the doxygen group
/**
 * @}
 */
