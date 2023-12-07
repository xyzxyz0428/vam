/**
 * @addtogroup v2v_cfg_api Configuration service
 * @{
 *
 * @file
 *
 * Module code for ETSA SW application options
 *
 * Command-line parameters
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __CONF_CMD_H__
#define __CONF_CMD_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
// QNX puts getopt in unistd (and doesn't have getopt_long)
#if defined(__QNX__)
#include <unistd.h>
#elif MSVC
#else
#include <getopt.h>
#endif
#include <stdbool.h>

#include "conf-ini.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Maximum length of option lists
#define VSC_OPTS_MAXFILENAMELENGTH (512)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// VSCOpt Error Codes
typedef enum VSCOptsErrCode
{
  VSC_OPTS_ERR_NONE = 0,
  VSC_OPTS_ERR_HELP_ONLY = -1,
  VSC_OPTS_ERR_INVALIDOPTION = -2,
  VSC_OPTS_ERR_INVALIDOPTIONARG = -3
} eVSCOptsErrCode;

/// Option tag values (correspond with each entry in @ref tConfCmdEntry)
typedef enum VSCOptsTag
{
  // do NOT use 'W'!
  VSC_OPTS_TAG_HELP            = '?',
  VSC_OPTS_TAG_DEFAULTS_FILE   = 'd',
  VSC_OPTS_TAG_CONFIG_FILE     = 'c',
  VSC_OPTS_TAG_VERBOSE         = 'v',
  VSC_OPTS_TAG_CONF_ENFORCING  = 'e',
  VSC_OPTS_TAG_CONF_LIMIT      = 'l',
  VSC_OPTS_TAG_CONF_ALLOW      = 'a',
  VSC_OPTS_TAG_BSM_SOURCE      = 'B',
  VSC_OPTS_TAG_EXT_CONFIG_FILE = 'C',
  VSC_OPTS_TAG_CSV_REPLAY      = 'V',
  VSC_OPTS_TAG_PTX_REPLAY      = 'T',
  VSC_OPTS_TAG_CAN_REPLAY      = 'N',
  VSC_OPTS_TAG_GPS_REPLAY      = 'G',
  VSC_OPTS_TAG_PRX_REPLAY      = 'R',
  VSC_OPTS_TAG_UDP_REPLAY      = 'U',
  VSC_OPTS_TAG_DEBUG_LEVEL     = 'L',
  VSC_OPTS_TAG_DEBUG_THREADS   = 'D',
  VSC_OPTS_TAG_RADIO_DEBUG     = 'A',
  VSC_OPTS_TAG_CONVERT         = 'x',
  VSC_OPTS_TAG_NO_FL           = 'f'
} eVSCOptsTag;

/// Command line options structure
typedef struct CmdConfig
{
  /// Defaults Ini File
  char DefaultsFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// Configuration Ini File
  char ConfigIniFileName[VSC_OPTS_MAXFILENAMELENGTH];

  /// verbose mode
  bool Verbose;

  /// BSM Source override set
  bool BSMSourceArg;
  /// BSM Source override
  uint8_t BSMSource;

  /// Cohda Extended Configuration Ini File set
  bool ExtConfigIniFileNameArg;
  /// Cohda Extended Configuration Ini File
  char ExtConfigIniFileName[VSC_OPTS_MAXFILENAMELENGTH];

  /// Prerec filename set
  bool PreRecFileNameArg;
  /// Prerec filename
  char PreRecFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// P1609 TX Replay filename set
  bool PTXReplayFileNameArg;
  /// P1609 TX Replay filename
  char PTXReplayFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// CAN Replay filename set
  bool CANReplayFileNameArg;
  /// CAN Replay filename
  char CANReplayFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// GPS Replay filename set
  bool GPSReplayFileNameArg;
  /// GPS Replay filename
  char GPSReplayFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// P1609 RX Replay filename set
  bool PRXReplayFileNameArg;
  /// P1609 RX Replay filename
  char PRXReplayFileName[VSC_OPTS_MAXFILENAMELENGTH];
  /// UDP Replay filename set
  bool UDPReplayFileNameArg;
  /// UDP Replay filename
  char UDPReplayFileName[VSC_OPTS_MAXFILENAMELENGTH];

  /// Debug trace level set
  bool DebugLevelArg;
  /// Debug trace level
  uint8_t DebugLevel;

  /// Debug option to change thread startup
  bool DebugThreads;

  /// Compile-time limits handling arg set
  bool ReadConfModeArg;
  /// How to handle compile-time limits when parsing conf files
  tConfReadMode ReadConfMode;

  /// Force disabling Facilities Layer
  bool NoFacilitiesLayer;

  /// CSV File Argument Present
  bool ConversionFileNameArg;
  /// CSV File To Convert
  char ConversionFileName[VSC_OPTS_MAXFILENAMELENGTH];
} tCmdConfig;

//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

int ConfCmdParseCommandline(int Argc,
                            char **ppArgv,
                            tCmdConfig *pConfig);

void ConfCmdUsage(const char *pAppName);

void ConfCmdPrint(const tCmdConfig *pConfig);

int ConfIniCommandLineSettings(const tCmdConfig *pConfig,
                               tIniFile *pIniData);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
