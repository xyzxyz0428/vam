/**
 * @addtogroup cohda_ldm Local Dynamic Map (LDM)
 * @{
 *
 * @section What Does It Do
 * This library provides an API to access various information via SQL database
 *
 * This is done using the LDM module
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2015 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __LDM_H__
#define __LDM_H__

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------
#define LDM_MAX_QUERY_RESULTS   (96)
#define LDM_MAX_SIZE_OF_DATA    (4000)
#define LDM_Error               (1)
#define LDM_Success             (0)

#define LDM_MAX_ELEV            (8848)  // m, Mt Everest
#define LDM_MIN_ELEV            (-418)  // m, Dead Sea

#define LDM_MAX_VALIDITY        (2145916800)  // sec, 2038
#define LDM_MIN_VALIDITY        (1262304000)  // sec, 2010

#define LDM_MIN_BOX_LATLON      (10) // tenths-microdegrees
#define LDM_MIN_BOX_ELEV        (2) // m

/// Supported return codes from @ref fLDM_Callback
enum
{
  /// All errors are negative
  LDM_STATUS_ERROR = -1,
  /// No error
  LDM_STATUS_OK = 0,

  // LDM API return codes
  /// Error code for LDM API: lock failure
  LDM_STATUS_ELOCK = -101,
  /// Error code for LDM API: registration errors
  LDM_STATUS_EHANDLE = -102,
};

/// Message type of LDM users, e.g. IVI
typedef enum LDMMsgType
{
  LDM_MSG_IVI = 0,
  LDM_MSG_TOLL_BOOTH,
  LDM_MSG_TIM,
  LDM_MSG_DENM,
  LDM_MSG_RSICN,
  LDM_MSG_LAST
} eLDMMsgType;
/// @ref LDMMsgType
typedef uint8_t tLDMMsgType;

typedef int64_t  tLDMMsgId;

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------
struct LDM;

/// Area of interest relative to current position
typedef struct LDMAOI
{
  int32_t AoiSizeLat; ///< 10th of microdegees [degree/1e7]
  int32_t AoiSizeLon; ///< 10th of microdegees [degree/1e7]
  int32_t AoiSizeElv; ///< abs([m])
} tLDMAOI;

/// Bounding box data structure (including time)
typedef struct LDMBBox
{
  int32_t MinLat;    ///< 10th of microdegee [degree/1e7]
  int32_t MaxLat;    ///< 10th of microdegee [degree/1e7]
  int32_t MinLon;    ///< 10th of microdegee [degree/1e7]
  int32_t MaxLon;    ///< 10th of microdegee [degree/1e7]
  int32_t MinElev;   ///< [m] relative to WG84 reference ellipsoid
  int32_t MaxElev;   ///< [m] relative to WG84 reference ellipsoid
  int32_t ValidFrom; ///< Linux epoch [s]
  int32_t ValidTo;   ///< Linux epoch [s]
} tLDMBBox;

/// LDM Query structure
typedef struct LDMQuery
{
  tLDMMsgType Type;
  tLDMAOI AOI;
} tLDMQuery;

/// All the fields are the same as what have been added
typedef struct LDM_QueryResult
{
  int64_t       MsgId;
  tLDMMsgType   Type;
  tLDMBBox      Bbox;
  size_t        DataLen;
  unsigned char Data[LDM_MAX_SIZE_OF_DATA];
} tLDM_QueryResult;

/**
 * @brief Type for LDM event callback function
 * @param NumOfRecordsFound number of records found
 * @param pPriv Private pointer that was provided in LDM_SubscribeQuery()
 * @param pData point to memory holding query results (variable sized array of tLDM_QueryResult)
 */
typedef void (fLDM_Callback) (size_t NumOfRecordsFound,
                              void *pPriv,
                              const tLDM_QueryResult *pData);

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

// == Client (manager, producer  & consumer) API ==
int LDM_Init(void);
void LDM_Deinit(void);

// == LDM 'manager' API ==
int LDM_Backup(const char *pFileName);
int LDM_BackupOnline();
int LDM_Restore(const char *pFileName);

// == LDM client 'producer' API ==
int LDM_ProducerOpen(tLDMMsgType Type, const void *pHandle, struct LDM *pProducer);
int LDM_ProducerClose(tLDMMsgType Type, const void *pHandle, struct LDM *pProducer);
int LDM_CheckDuplicate(tLDMMsgType Type, int64_t MsgId, const void *pData, size_t Len);
int LDM_InsertUpdate(tLDMMsgType Type,
                     int64_t MsgId,
                     const struct LDMBBox *pBox,
                     const void *pData,
                     size_t DataLen);
int LDM_DeleteExpired(tLDMMsgType Type);
int LDM_DeleteByType(tLDMMsgType Type);
int LDM_DeleteById(tLDMMsgType Type, int64_t MsgId);

// == LDM client 'consumer' API ==
int LDM_Query(tLDMMsgType Type, const tLDMBBox *pBox, void *pQueryResults);
int LDM_SubscribeQuery(const struct LDMQuery *pQuery,
                       fLDM_Callback Callback,
                       const void *pPriv);
int LDM_UpdateQuery(const tLDMAOI *pAOI,
                    int Handle);
int LDM_UnsubscribeQuery(int Handle);
int LDM_CountRange(tLDMMsgType Type, tLDMMsgId IdStart, tLDMMsgId IdEnd);
int LDM_DeleteRange(tLDMMsgType Type, tLDMMsgId IdStart, tLDMMsgId IdEnd);

#ifdef __cplusplus
}
#endif

#endif // __LDM_H__

// Close the doxygen group
/**
 * @}
 */
