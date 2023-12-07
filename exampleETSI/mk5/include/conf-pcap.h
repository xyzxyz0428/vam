/**
 * @addtogroup v2v_cfg_api Configuration service
 * @{
 *
 * @file
 *
 * CFG library API
 *
 * PCAP metadata
 *
 */
//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __CONF_CONF_PCAP_H_
#define __CONF_CONF_PCAP_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Capture metadata description length
/// TTTCDMNNNR - Test Run
/// \|/|||\++--- Number of OBEs
///  V ||\------ Message Transmit Rate
///  | |\------- Data Transmit Rate
///  | \-------- Channel
///  \---------- Test Configuration
/// Only needs 11 (10 + NULL) but 12 makes things like up nicer
#define TEST_NUM_LEN    12
/// Capture metadata description length
#define SHORT_DESC_LEN  32
/// Capture metadata notes length
#define NOTES_TEXT_LEN  1024

/// VERSION NUMBERS
#define CONF_PCAP_SW_MAJOR_VER 2
#define CONF_PCAP_SW_MINOR_VER 1


//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Metadata
typedef struct PcapMetaData
{
  /// Software version
  char swMajor, swMinor;
  /// eth0 MAC address, uniquely identifies the MK2
  unsigned char MAC[6];
  /// Experiment start time, used to create filename
  int32_t epoch;
  /// Test number array
  char testNum[TEST_NUM_LEN];
  /// Short description, used to create filename
  char shortDesc[SHORT_DESC_LEN];
  /// Notes -- do this last, everything else is fixed size
  char notes[NOTES_TEXT_LEN];
} tPcapMetaData;

#ifdef __cplusplus
}
#endif

#endif // __CONF_CONF_PCAP_H_

/**
 * @}
 */
