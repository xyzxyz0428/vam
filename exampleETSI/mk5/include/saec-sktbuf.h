/**
 * @addtogroup v2x_saec_sktbuf SAEC Packet Buffer
 * @{
 *
 * @section saec_sktbuf zero copy packet buffers
 *
 * @subsection saec_sktbuf_tx Transmit packets
 *  - Allocate using @ref SktBuf_AllocSAEC with Payload Length + @ref SAEC_SKTBUF_EXTRA_MAX
 *  - Reserve the headroom for headers using
 *  @code
 *  SktBuf_Reserve(pPkt, SAEC_SKTBUF_HDR_MAX);
 *  @endcode
 *  - Populate the unsecure payload using
 *  @code
 *  SktBuf_Put(pPkt, Payload Length);
 *  @endcode
 *
 * @subsection saec_sktbuf_rx Receive packets
 *  - Allocate using SktBuf_AllocSAEC() with the maximum of Payload Length
 *  - Prepare the read buffer using
 *  @code
 *  SktBuf_Put(pPkt, Max Payload Length)
 *  @endcode
 *
 * @subsection saec_sktbuf_parameters
 * - For packets received via @ref QSMSG_EXT_RX_SAECFL_PDU ,
 *   their Facility Layer Rx Parameters can extracted by @ref SktBuf_GetSAECFacDesc  .
 * - For packets received via @ref fSAECDSMP_DataInd or @ref QSMSG_EXT_RX_SAECFL_PDU ,
 *   their Network Layer Rx Parameters can extracted by @ref SktBuf_GetSAECNetDesc .
 *
 * @note The on-air packets data is expected to be continuous in memory, so each element's
 *       pointer and length field should be updated with this in mind as the processing proceeds
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __SAEC_SKTBUF_H_
#define __SAEC_SKTBUF_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "sktbuf.h"

#include <stdint.h>
#include <stdbool.h>

#include <sys/uio.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

// Keep them multiples of 8 or 16
/// Maximum size of over the air secure headers.
#define SAEC_SKTBUF_HDR_SEC_MAX  (256)
/// Maximum size of over the air secure trailer.
#define SAEC_SKTBUF_TLR_SEC_MAX  (128)
/// Maximum size of over the air network headers.
#define SAEC_SKTBUF_HDR_NET_MAX  (258)
/// Maximum size of over the air link headers.
#define SAEC_SKTBUF_HDR_MAC_MAX  (64)
/// Maximum number of canaries
#define SAEC_SKTBUF_CANARY_MAX   (4)

/// Maximum number of headers in front + canaries
#define SAEC_SKTBUF_HDR_MAX (SAEC_SKTBUF_HDR_NET_MAX + \
                             SAEC_SKTBUF_HDR_SEC_MAX + \
                             SAEC_SKTBUF_HDR_MAC_MAX + \
                             SAEC_SKTBUF_CANARY_MAX * sizeof(tSktBufCanary))

/// Maximum size of extra headers/trailers in the packet
#define SAEC_SKTBUF_EXTRA_MAX (SAEC_SKTBUF_HDR_MAX + \
                               SAEC_SKTBUF_TLR_SEC_MAX)

/// Maximum size of a valid SAEC packet with 1024 bytes of UPER encoded
#define SAEC_SKTBUF_MAX (SAEC_SKTBUF_EXTRA_MAX + 1024)

/// Maximum size of application meta data
#define SAEC_SKTBUF_SECTION_FAC_MAX   (156)
/// Maximum size of network meta data
#define SAEC_SKTBUF_SECTION_NET_MAX   (144)
/// Maximum size of debug meta data
#define SAEC_SKTBUF_SECTION_DEBUG_MAX (40)
/// Maximum size of pcap meta data
#define SAEC_SKTBUF_SECTION_PCAP_MAX  (8)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/**
 * Meta data sections used by SAEC in the @ref tSktBuf structure
 */
typedef enum SAECSktBufSection
{
  SAEC_SKTBUF_SECTION_FAC = 0,
  SAEC_SKTBUF_SECTION_NET,
  SAEC_SKTBUF_SECTION_DEBUG,
  SAEC_SKTBUF_SECTION_PCAP,
  SAEC_SKTBUF_NUM_SECTIONS,
} eSAECSktBufSection;

typedef uint8_t tSAECSktBufSection;

// Forward declaration
typedef struct SAECNetDesc tSAECNetDesc;
typedef struct SAECFacDesc tSAECFacDesc;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/**
 * @brief Allocate a @ref tSktBuf structure for SAEC.
 * @param Len Max buffer size including all headers/trailers and payload
 * @return A new tSktBuf buffer with SAEC's meta data sections.
 */
tSktBuf * SktBuf_AllocSAEC(size_t Len);

/**
 * @brief Retrieve the Network Layer Rx Parameters
 * @param pPkt Packet received by the Network Layer
 * @return Network Layer Rx Parameters
 */
const tSAECNetDesc * SktBuf_GetSAECNetDesc(const tSktBuf * pPkt);

/**
 * @brief Retrieve the Facility Layer Rx Parameters
 * @param pPkt Packet received by the Network Layer
 * @return Network Layer Rx Parameters
 */
const tSAECFacDesc * SktBuf_GetSAECFacDesc(const tSktBuf * pPkt);

#ifdef __cplusplus
}
#endif

#endif // __SAEC_SKTBUF_H_

// Close the doxygen group
/**
 * @}
 */
