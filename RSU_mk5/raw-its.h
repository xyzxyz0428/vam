/**
 * @addtogroup mod_raw_its ITS MSG Tx/Rx Module
 * @{
 *
 * @section mod_raw_its_dd What Does It Do
 *
 * This generates a custom payload for sending via the ITS MSG API.
 * The packet is sent via the defined BTP port with the required settings.
 *
 * The custom payload is PER-encoded data generated from the RAW.asn1 file.
 * This is achieved by using the ASN1C compiler to generate C code from ASN.1
 * which implements the encoders and decoders and provides the structure of
 * the message to populate.
 *
 * Any packets received on the defined BTP port are handled and PER-decoded.
 * The data is then XER-encoded to display the contents in a human-readable
 * format.
 *
 * The ASN.1 code could also be added to the Cohda Wireshark to provide
 * decoding of the Facilities Layer packet in Wireshark.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __RAW_ITS_H_
#define __RAW_ITS_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <stdint.h>
#include <pthread.h>

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Location of the RAW receiver configuration settings
#define RAWITS_CONFIG_PATH_NAME  "Example.RAWIts"

// Configuration value names
#define RAWITS_CONFIG_VALUE_NAME_BTPPORT         "BTPPort"
#define RAWITS_CONFIG_VALUE_NAME_RXINTERVAL      "RxInterval"
#define RAWITS_CONFIG_VALUE_NAME_TXINTERVAL      "TxInterval"
#define RAWITS_CONFIG_VALUE_NAME_PACKET          "Packet"
#define RAWITS_CONFIG_VALUE_NAME_DESTINFO        "DestInfo"
#define RAWITS_CONFIG_VALUE_NAME_PKTTRANSPORT    "PktTransport"
#define RAWITS_CONFIG_VALUE_NAME_LOCATION        "Location"
#define RAWITS_CONFIG_VALUE_NAME_AREALAT         "AreaLat"
#define RAWITS_CONFIG_VALUE_NAME_AREALONG        "AreaLong"
#define RAWITS_CONFIG_VALUE_NAME_AREADISTA       "AreaDistA"
#define RAWITS_CONFIG_VALUE_NAME_AREADISTB       "AreaDistB"
#define RAWITS_CONFIG_VALUE_NAME_AREAANGLE       "AreaAngle"
#define RAWITS_CONFIG_VALUE_NAME_AREASHAPE       "AreaShape"
#define RAWITS_CONFIG_VALUE_NAME_COMMPROFILE     "CommProfile"
#define RAWITS_CONFIG_VALUE_NAME_TRAFFICCLASS    "TrafficClass"
#define RAWITS_CONFIG_VALUE_NAME_MAXPKTLIFETIME  "MaxPktLifetime"
#define RAWITS_CONFIG_VALUE_NAME_SECPROFILE      "SecProfile"
#define RAWITS_CONFIG_VALUE_NAME_DATALENGTH      "DataLength"
#define RAWITS_CONFIG_VALUE_NAME_DATA            "Data"

// Configuration value defaults for mandatory items
#define RAWITS_CONFIG_VALUE_DEFAULT_BTPPORT             (3000)
#define RAWITS_CONFIG_VALUE_DEFAULT_RXINTERVAL           (500)
#define RAWITS_CONFIG_VALUE_DEFAULT_TXINTERVAL          (1000)
#define RAWITS_CONFIG_VALUE_DEFAULT_DESTINFO               (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_PKTTRANSPORT           (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_LOCATION               (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREALAT                (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREALONG               (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREADISTA              (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREADISTB              (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREAANGLE              (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_AREASHAPE              (0)
#define RAWITS_CONFIG_VALUE_DEFAULT_COMMPROFILE            (ETSIFAC_GN_PROFILE_DEFAULT)
#define RAWITS_CONFIG_VALUE_DEFAULT_TRAFFICCLASS           (ETSIFAC_GN_TC_ITS_DP2)
#define RAWITS_CONFIG_VALUE_DEFAULT_MAXPKTLIFETIME      (1000)
#define RAWITS_CONFIG_VALUE_DEFAULT_SECPROFILE             (ETSIFAC_GN_SEC_PROF_NONE)
#define RAWITS_CONFIG_VALUE_DEFAULT_DATALENGTH            (11)
#define RAWITS_CONFIG_VALUE_DEFAULT_DATA                "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

/// Maximum size of the Data
#define RAWITS_DATA_BUF_SIZE (1386)

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------


/// State IDs for RAW Its thread (bitmask)
typedef enum RAWItsThreadState
{
  /// Not initialized
  RAWITS_THREAD_STATE_NONE = 0x00,
  /// Initializing
  RAWITS_THREAD_STATE_INIT = 0x01,
  /// Running
  RAWITS_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  RAWITS_THREAD_STATE_STOP = 0x04,
  /// Stopped
  RAWITS_THREAD_STATE_END  = 0x08,
} eRAWItsThreadState;
/// @ref RAWItsThreadState
typedef int tRAWItsThreadState;

/// RAW receiver Statistics
typedef struct RAWItsStats
{
  /// Receive counters
  struct {
    uint32_t Okay;
    uint32_t Fail;
  } Rx;

} tRAWItsStats;

/// RAW receiver parameters - Stored in Config File
typedef struct RAWItsParams
{
  /// Port number
  uint16_t BTPPort;
  /// Transmit period
  uint32_t TxInterval;

  /// period
  uint32_t RxInterval; // just for the thread sleep

  uint16_t DestInfo;
  uint8_t PktTransport;
  uint64_t Location;
  int32_t AreaLat;
  int32_t AreaLong;
  uint16_t AreaDistA;
  uint16_t AreaDistB;
  uint16_t AreaAngle;
  uint8_t AreaShape;
  uint8_t CommProfile;
  uint8_t TrafficClass;
  uint8_t SecProfile;
  uint32_t MaxPktLifetime;
  uint16_t DataLength;
  uint8_t Data[RAWITS_DATA_BUF_SIZE];
} tRAWItsParams;

/// RAW receiver state
typedef struct RAWIts
{
  /// ID of RAW receiver thread
  pthread_t ThreadID;
  /// RAW receiver thread state
  tRAWItsThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;
  /// Module statistics
  struct RAWItsStats Stats;
  /// Configuration
  struct RAWItsParams Params;
} tRAWIts;

typedef struct RAWexternedata
  {  double lat;
     double lon;
	} tRAWexternedata;
//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

int RAWIts_Open (struct RAWIts *pRAW,
                pthread_attr_t *pAttr,
                char *pConfigFileName);

void RAWIts_Close (struct RAWIts *pRAW);

void RAWIts_PrintStats (struct RAWIts *pRAW);

#endif // __RAW_ITS_H_
/**
 * @}
 */
