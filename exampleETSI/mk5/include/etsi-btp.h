/**
 * @addtogroup v2x_etsi_btp ETSI ITS Network BTP API
 * @{
 *
 * This module provides an API to send/Receive BTP packets.
 *
 * The most commonly used functions are
 * - @ref ETSIBTP_Open : Open a BTP port for reception and register a callback to receive packets from BTP
 *   - This returns a @ref tETSIBTP which can then be used to later close the port
 * - @ref ETSIBTP_Close : Close the BTP port and de-register the callback
 *
 * - @ref ETSIBTP_SAPDataReq : Used to transmit generic payload via BTP
 *   - Configure the packet transport type with the @ref ETSIGeoNetDesc parameters, and send the payload
 *   - This is the primary way for an Upper Layer entity to send a BTP payload
 *
 * Function defined by BTP client
 * - @ref fETSIBTP_DataInd : function pointer type that is used to define Data Indication callback
 *   - The callback is provided with a @ref UtilPacketBuffer and the private data from @ref ETSIBTP_Open
 *   - The packet is freed with PktBuf_Free()
 *
 * Also implemented
 * - ETSIBTP_DataInd : Used by GN to deliver received GN packets (in a @ref UtilPacketBuffer)
 *   - The packet needs to be freed with PktBuf_Free()
 *
 * - @ref ETSIBTP_DataReq : Used to transmit @ref UtilPacketBuffer via BTP
 *   - A packet allocated with PktBuf_Alloc() can be transmitted
 *
 * This example shows the basics for sending and receiving BTP packets
 * @code

  // Define callback for BTP data indications
  int Demo_BtpCallback(void *pPriv, tUtilPacketBuffer *pPkt)
  {
    (void)pPriv;

    // Check ASN.1 version in PER payload
    if (pPkt->Elem.Payload.pData[0] == 1)
    {
      // Do something
    }

    // Free packet buffer structure
    PktBuf_Free(pPkt);

    return 0;
  }

  // Define BTP packet sender
  int Demo_BtpSend(void)
  {
    int Res;

    // Open user-defined BTP port 3000 for receiving
    tETSIBTP *pBTPHandle = ETSIBTP_Open(3000, NULL, Demo_BtpCallback);

    // Configure descriptor for SAP BTP Data Req
    tETSIGeoNetDesc BTPHdr = {0};

    BTPHdr.UpperEntity = ETSI_GN_NH_BTPB;
    BTPHdr.PktTransport = ETSI_GN_TRANSPORT_SHB;

    // Send on BTP port 3000
    BTPHdr.DestPort = 3000;
    BTPHdr.DestInfo = 0;

    BTPHdr.Tx.RepeatInterval = 0;
    BTPHdr.Tx.MaxTxPower = ETSI_GN_TXPWR_DEFAULT;

    // No Security...
    BTPHdr.Tx.SecControl.Profile = C2XSEC_NONE;

    // Security...
    // BTPHdr.Tx.SecControl.Profile = C2XSEC_AID_SSP;
    // BTPHdr.Tx.SecControl.AID = C2XSEC_ITS_AID_CAM;
    // BTPHdr.Tx.SecControl.SSPLen = C2XSEC_CAM_SSP_LEN;
    // BTPHdr.Tx.SecControl.SSPBits[0] = 0x01;
    // BTPHdr.Tx.SecControl.SSPBits[1] = 0xFF;
    // BTPHdr.Tx.SecControl.SSPBits[2] = 0xFF;

    BTPHdr.CommProfile = ETSI_GN_PROFILE_ITS_G5;
    BTPHdr.TrafficClass = ETSI_GN_TC_ID_DP1;
    BTPHdr.HopLimit = ETSI_GN_HOPLIMIT_DEFAULT;
    BTPHdr.MaxPktLifetime = 1000;
    BTPHdr.Length = 5;

    uint8_t pPayload[5] = {0x01,0x02,0x03,0x04,0x05};

    // Send payload with BTP parameters
    Res = ETSIBTP_SAPDataReq (&BTPHdr, pPayload);

    if (Res < 0)
    {
      // Sending failed
    }

    // Wait for some Data indications
    sleep(5);

    // Close BTP port
    ETSIBTP_Close (pBTPHandle);

    return 0;
  }

 * @endcode
 *
 * @file
 *
 * ETSI BTP interface definitions
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2018 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ETSI_BTP_H_
#define __ETSI_BTP_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>

#include "etsi-gn.h"
#include "PacketBuffer.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Well-known BTP ports

/// Default CAM BTP port
#define ETSIBTP_PORT_CA     2001

/// DENM BTP port
#define ETSIBTP_PORT_DEN    2002

/// MAPEM BTP port
#define ETSIBTP_PORT_RLT    2003

/// SPATEM BTP port
#define ETSIBTP_PORT_TLM    2004

/// SA BTP port
#define ETSIBTP_PORT_SA     2005

/// IVIM BTP port
#define ETSIBTP_PORT_IVI    2006

/// SREM BTP port
#define ETSIBTP_PORT_TLC_SR 2007

/// SSEM BTP port
#define ETSIBTP_PORT_TLC_SS 2008

/// CPS BTP port
#define ETSIBTP_PORT_CPS    2009

/// EVCSN POI BTP port
#define ETSIBTP_PORT_EVCSN  2010

/// TPG BTP port
#define ETSIBTP_PORT_TPG    2011

/// EV RSR BTP port
#define ETSIBTP_PORT_CHRG   2012

/// RTCMEM BTP port
#define ETSIBTP_PORT_GPC    2013

/// CTL BTP port
#define ETSIBTP_PORT_CTL    2014

/// CRL BTP port
#define ETSIBTP_PORT_CRL    2015

/// CERTREQ BTP port
#define ETSIBTP_PORT_CERTREQ 2016

/// MCDM BTP port
#define ETSIBTP_PORT_MCD    2017

/// VAM BTP port
#define ETSIBTP_PORT_VA     2018

/// IMZM BTP port
#define ETSIBTP_PORT_IMZ    2019

/// DSM BTP port
#define ETSIBTP_PORT_DS     2020

/// PMM BTP port
#define ETSIBTP_PORT_PMM    3005

/// PCM BTP port
#define ETSIBTP_PORT_PCM    3006

/// (Start of) Custom BTP ports
#define ETSIBTP_PORT_CUSTOM 3000

/// ETSIBTP_Open has a special port number for receiving packets for _any_ port
#define ETSIBTP_PROMISCUOUS_PORT 0xFFFF


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// BTP client handle
typedef void * tETSIBTP;

/// ETSI BTP (on-air) frame header
typedef struct ETSIBTPPktHdr
{
  /// Destination port
  uint16_t DestPort;
  union
  {
    /// Source port (for type A)
    uint16_t SrcPort;
    /// Destination info (for type B)
    uint16_t DestInfo;
  };
} __attribute__ ((packed)) tETSIBTPPktHdr;

/// Application descriptors
typedef struct ETSIAppDesc
{
  /// Some application user
  void *pAppFunc;
  /// Some application data
  void *pAppData;
} tETSIAppDesc;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// Upper layer (Facilities) API

/**
 * @brief Callback indication of a received BTP frame
 * @param pPriv The BTP handle submitted in @ref ETSIBTP_Open
 * @param pBuf The packet buffer
 *
 * This callback is invoked by the BTP to deliver received frames to the upper layers
 */
typedef int (* fETSIBTP_DataInd) (void *pPriv, tUtilPacketBuffer *pBuf);

/**
 * @brief BTP open for packet reception
 *
 * @param DestPort BTP port number to open
 * @param pPriv in caller's private data (provided to callback)
 * @param pInd in callback indication function (must be set)
 * @return a tETSIBTP* handle (NULL for error)
 */
tETSIBTP *ETSIBTP_Open (uint16_t DestPort, void *pPriv, fETSIBTP_DataInd pInd);

/**
 * @brief BTP Packet sending request (with network layer descriptor and payload)
 *
 * Upper Layers use this to send a payload to GeoNetworking layer
 * There is no action for the caller on failure status
 *
 * This creates the packet buffer, populates the descriptor fields and
 * copies the provided Payload to the packet buffer space before sending
 * to the GeoNetworking layer.
 *
 * @param pDataReq BTP descriptor
 * @param pPayload BTP payload
 * @return Status, 0 for successfully sent to GN layer (NOTE: GN messaging may later fail),
 *                 -EBUSY for GN messaging busy, either ignore or wait before re-sending,
 *                 -EPROTO for invalid BTP type,
 *                 -EFAULT for invalid BTP descriptor,
 *                 -EFBIG for invalid BTP length,
 *                 -ETIME for invalid Packet Lifetime,
 *                 -ENOMEM for Packet creation (memory) error,
 *                 -EINVAL for invalid GN parameter
 */
int ETSIBTP_SAPDataReq (const tETSIGeoNetDesc *pDataReq, const uint8_t *pPayload);

/**
 * @brief BTP Packet sending request (with Packet Buffer)
 *
 * Upper Layers use this to send a Packet Buffer to GeoNetworking layer
 * There is no action for the caller on failure status (Packet Buffer
 * will be sent or freed on error)
 *
 * @param pPkt Packet buffer for sending
 * @return Status, 0 for successfully sent to GN layer (NOTE: GN messaging may later fail),
 *                 -EBUSY for GN messaging busy, either ignore or wait before re-sending,
 *                 -EPROTO for invalid BTP type,
 *                 -EFBIG for invalid BTP length
 */
int ETSIBTP_DataReq (tUtilPacketBuffer *pPkt);

/**
 * @brief (Synchronous) verification of received BTP Packet
 *
 * The verification policy in the GN layer may mean that some packets
 * are not automatically verified. This provides a function to perform
 * that verification. Detailed verification status is available in the
 * Packet Buffer receive meta-data element.
 *
 * @param pPkt Packet buffer to verify
 * @return Status, 0 for success (of verification operation),
 *                 -EINVAL for parameter error
 *                 -ENOSYS for verification failure
 */
int ETSIBTP_DataIndVerify (tUtilPacketBuffer *pPkt);

/**
 * @brief BTP reception close
 *
 * @param pHandle in a tETSIBTP* handle to be freed
 */
void ETSIBTP_Close (tETSIBTP *pHandle);

#ifdef __cplusplus
}
#endif

#endif // __ETSI_BTP_H_

/**
 * @}
 */
