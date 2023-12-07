/**
 * @addtogroup v2x_p1609_ctrl_api
 * @{
 *
 * @file p1609-ctrl-svc.h WBSS service related functions
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2011 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __P1609_CTRL_SVC_H_
#define __P1609_CTRL_SVC_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <arpa/inet.h>
#include <linux/ieee1609/dot3/dot3-wme-api-types.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
#define WSA_PSID        (0x8007)

#define SERVICE_INFO_NUM   (32)

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
struct Dot3NetworkInfo;

/**
 * @brief Handle a WME-ServiceSelect.request message from the kernel
 * @param pReq The request to be processed
 * @param pPriv Private (context) pointer registered with Dot3_SetCallbackWMEServiceSelectReq()
 * @return 0 for success or an error code
 */
typedef int (fP1609WBSS_ServiceSelectReq)(struct Dot3WMEServiceSelectReq *pReq,
                                          void *pPriv);
//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
int P1609WBSS_ThreadInit (int SchedulerPolicy, int SchedulerPriority);
void P1609WBSS_ThreadDeinit (void);

void P1609WBSS_ProviderSetNetworkInfo (struct Dot3NetworkInfo *pNI);
int  P1609WBSS_GetIPv6AddressFromString(const char *pString,
                                        struct in6_addr *pAddress);
int  P1609WBSS_GetIfaceGlobalIPv6(const char *pInterface,
                                  struct in6_addr *pAddr);
int  P1609WBSS_GetIfaceMAC(const char *pInterface,
                           uint8_t pMAC[6]);

int P1609WBSS_SetCallbackServiceSelectReq(fP1609WBSS_ServiceSelectReq *pFunc,
                                          void *pPriv);
int P1609WBSS_ServiceSelectCnf(struct Dot3WMEServiceSelectCnf *pCnf);

#ifdef __cplusplus
}
#endif

#endif // __P1609_CTRL_SVC_H_
// Close the doxygen group
/**
 * @}
 */
