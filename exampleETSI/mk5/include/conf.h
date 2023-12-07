/**
 * @addtogroup v2v_cfg_api Configuration service
 * @{
 *
 * @file
 *
 * Conf library API
 *
 * The Conf ('first-generation') configuration control system is now
 * deprecated and superseded by conf2. Since conf and conf2 maintain separate
 * records of the configuration, dynamic modifications of configuration by
 * conf are not reflected to the newer conf2 system. Specifically, use of
 * ConfigCommit() should now be avoided.
* 
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//------------------------------------------------------------------------------

#ifndef __APPCORE_CONF_H__
#define __APPCORE_CONF_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>

#include "id-global.h"
#include "conf-pcap.h"
#include "conf-ini.h"
#include "conf-cmd.h"

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Supported messages in CONF
typedef enum
{
  /// Re-read config
  QSMSG_CONF_READ_CONFIG = QS_BASE_MSG_CONF,
} tConfMsgId;

/// Default file to override compile-time defaults
#define ETS_DEFAULTS_FILENAME  "./ets.conf"

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// VSC echo configuration (built from Cmd line opts).
typedef struct ConfigIniData
{
  /// Revision, incremented when configuration information is updated.
  int Revision;
  /// Reference Count.
  int RefCount;
  /// PCAP data
  tPcapMetaData PcapMeta;
  /// Information from the INI file.
  tIniFile IniFile;
} tConfigIniData;

typedef void (*tConfUpdatedCallback)(void *pData);

//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

/// CALL THIS FIRST!!!
int ConfInit(int Argc,
             char **ppArgv,
             tCmdConfig * CommandLine);

/// OR CALL THIS FIRST (for Library)
int ConfInitLib(const char *UserCfgFileName,
                const char *DefaultsFileName,
                tConfReadMode ReadMode,
                tConfUpdatedCallback ConfUpdatedCallback,
                void *pConfUpdatedData);

int Conf_ThreadInit(int schedulerPolicy, int schedulerPriority_pc);

void Conf_ThreadDeinit(void);

char *ConfGetFileName(void);

int ConfIniCheckForUpdates(void);

int ConfIniCheckFile(void);

void ConfDeInitLib(void);
void ConfDeInit(void);

/// Returns the initial, non-modifiable configuration structure
const tConfigIniData * ConfigInitial(void);

/// Returns the latest configuration structure - caller must release with
/// ConfigRelease() when done
const tConfigIniData * ConfigGet(void);

void ConfigRelease(const tConfigIniData *pConfig);

/// Returns the singleton configuration structure - caller must release with
/// ConfigReleaseIni() when done
const tIniFile * ConfigGetIni(void);

void ConfigReleaseIni(const tIniFile * pIni);

/// Returns the writeable configuration structure
tConfigIniData * ConfigModify(void);

/// Update with the given lines
int ConfigUpdate(const char * pLines, tConfReadMode mode);

/// Set some application-specific initial values
void ConfigPreSetDefaults(const char *pDefaults);

/// Updates the configuration with changed writeable configuration
int ConfigCommit(tConfigIniData *pConfig);

const tPcapMetaData *Conf_GetMetaData(size_t *pNotesSize);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */
