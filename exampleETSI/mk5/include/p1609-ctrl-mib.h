/**
 * @addtogroup v2x_p1609_ctrl_api
 * @{
 *
 * @file p1609-ctrl-mib.h 1609 MIB information
 *
 * Provides information from the 1609 MIB
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_CTRL_MIB_H_
#define __P1609_CTRL_MIB_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int P1609Ctrl_MIBGetContinuousMACAddress(uint8_t MACAddress[6]);
int P1609Ctrl_MIBGetAlternatingMACAddress(uint8_t MACAddress[6]);

int P1609Ctrl_MIBGetSCH();
int P1609Ctrl_MIBGetCCH();
int P1609Ctrl_MIBGetLCH();

int P1609Ctrl_MIBGetTxPowerLCH();
int P1609Ctrl_MIBGetTxPowerCCH();
int P1609Ctrl_MIBGetTxPowerSCH();

int P1609Ctrl_MIBGetPrimaryDNS(uint8_t PrimaryDNS[16]);
int P1609Ctrl_MIBGetSecondaryDNS(uint8_t SecondaryDNS[16]);
int P1609Ctrl_MIBGetGatewayMAC(uint8_t GatewayMAC[6]);
int P1609Ctrl_MIBGetDefaultGateway(uint8_t DefaultGateway[16]);

int P1609Ctrl_MIBGetCCHUtilisation(uint8_t *pUtilisation);
int P1609Ctrl_MIBGetSCHUtilisation(uint8_t *pUtilisation);
int P1609Ctrl_MIBGetSCHBUtilisation(uint8_t *pUtilisation);

#ifdef __cplusplus
}
#endif

#endif // __P1609_CTRL_MIB_H_

// Close the doxygen group
/**
 * @}
 */

