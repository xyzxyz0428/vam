/**
 * @addtogroup persistence Persistant Storage module.
 * @{
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2016 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __APPCORE_PERSISTENCE_PERSISTENCE_H_
#define __APPCORE_PERSISTENCE_PERSISTENCE_H_


//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define PERS_MAX_KEY_LENGTH  64
#define PERS_LEGAL_KEY_CHARS "abcdefghijklmnopqrstuvwxyz" \
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                             "0123456789" \
                             "_-"

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int PERS_Init(void);

int PERS_Exit(void);

int PERS_Store(const char *pKey, const void *pData, size_t Len);

int PERS_Retrieve(const char *pKey, void *pData, size_t Len);

int PERS_StoreWithCRC32(const char *pKey, const void *pData, size_t Len);

int PERS_RetrieveWithCRC32(const char *pKey, void *pData, size_t Len);

#ifdef UNITTEST
char * PERS_FileName(const char *pKey);
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // __APPCORE_PERSISTENCE_PERSISTENCE_H_
