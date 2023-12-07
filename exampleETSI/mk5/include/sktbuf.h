/**
 * @addtogroup util_sktbuf Safe Packet Buffer
 * @{
 *
 * A safe packet buffer structure that pre-allocates a continuous memory chunk
 * for message encoding or decoding.
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __PLAT_UTIL_SKTBUF_H_
#define __PLAT_UTIL_SKTBUF_H_

//------------------------------------------------------------------------------
// Included headers
//-----------------------------------------------------------------------------

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/uio.h>

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

#define SKTBUF_MAX_SECTIONS (12)
//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Forward declaration for internal structure
typedef struct SktBuf tSktBuf;

/// Custom sections for meta data stroage
typedef struct SktBufSections
{
  /// Number of sections
  size_t NumSections;
  /// Specify the length of each section
  struct iovec Sections[SKTBUF_MAX_SECTIONS];
} tSktBufSections;

/// Type of canary
typedef uint32_t tSktBufCanary;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** @brief Create a SktBuf.
 * @param Size Size of the whole buffer including payload and all the headers to be generated.
 *             For example J2735 Payload + 1609.2 Security Header and Signature + 1609.3 WSMP Header + LLC Header.
 * @param NumSections Number of sections for Meta Data.
 * @param pSectionLen Array of lengths for each section of Meta Data.
 * @return The allocated buffer on success. Otherwise NULL.
 */
tSktBuf * SktBuf_Alloc(size_t Size,
                       size_t NumSections,
                       const size_t * pSectionLen);

/** @brief Create a SktBuf.
 * @param Size Size of the whole buffer including payload and all the headers to be generated.
 *             For example J2735 Payload + 1609.2 Security Header and Signature + 1609.3 WSMP Header + LLC Header.
 * @param pSections Sections to allocate for Meta Data.
 * @return The allocated buffer on success. Otherwise NULL.
 */
tSktBuf * SktBuf_AllocV(const size_t   Size,
                        const tSktBufSections * pSections);

/**
 * @brief Deep clone a SktBuf structure.
 * @note This function does not check canaries internally. If the canaries are corrupted in the
 *       input, they will be exactly copied over.
 * @param pSktBuf SktBuf.
 * @return The cloned SktBuf structure. NULL on memory allocation errors.
 */
tSktBuf * SktBuf_Clone(const tSktBuf * pSktBuf);

/**
 * @brief Free a SktBuf structure.
 * @param[in,out] pSktBuf SktBuf to be freed.
 * @note pSktBuf will not be freed if internal canary check fails.
 */
void SktBuf_Free(tSktBuf * pSktBuf);

/**
 * @brief Get the number of sections
 * @param pSktBuf SktBuf
 * @return The number of sections
 */
size_t SktBuf_GetNumSections(const tSktBuf * pSktBuf);

/**
 * @brief Get the size of this meta data section.
 * @param pSktBuf SktBuf
 * @param SectionNum Index of the section.
 * @return Size of the specified section. 0 if the SectionNum is invalid.
 */
size_t SktBuf_GetSectionLen(const tSktBuf * pSktBuf,
                            size_t SectionNum);

/**
 * @brief Get a pointer to specified meta data section .
 * @param pSktBuf SktBuf.
 * @param SectionNum Index of the section.
 * @return Begin of the meta data section. NULL if SectionNum is invalid.
 */
void * SktBuf_GetSection(tSktBuf * pSktBuf,
                         size_t SectionNum);

/**
 * @brief Get a pointer to specified meta data section .
 * @param pSktBuf SktBuf.
 * @param SectionNum Index of the section.
 * @return Begin of the meta data section. NULL if SectionNum is invalid.
 */
const void * SktBuf_GetSectionRO(const tSktBuf * pSktBuf,
                                 size_t SectionNum);

/**
 * @brief Increase the headroom of an empty buffer by reducing the tail room.
 * @note  This is only allowed for an empty buffer.
 * @param[in, out] pSktBuf SktBuf
 * @param Len Bytes to move
 */
bool SktBuf_Reserve(tSktBuf * pSktBuf, size_t Len);

/**
 * @brief Add data to the front of a buffer
 * @param pSktBuf SktBuf
 * @param Len Number of bytes to add
 * @return Beginning of the new buffer area to wirte to. NULL if Len is invalid.
 */
uint8_t * SktBuf_Push(tSktBuf * pSktBuf, size_t Len);

/**
 * @brief Remove data to the front of a buffer
 * @param pSktBuf SktBuf
 * @param Len Number of bytes to remove
 * @return Next byte in the area to read. NULL if Len is invalid.
 */
uint8_t * SktBuf_Pull(tSktBuf * pSktBuf, size_t Len);

/**
 * @brief Add data to the tail of a buffer
 * @param pSktBuf SktBuf
 * @param Len Number of bytes to add
 * @return Beginning of the new buffer area to wirte to. NULL if Len is invalid.
 */
uint8_t * SktBuf_Put(tSktBuf * pSktBuf, size_t Len);

/**
 * @brief Remove data from the tail of a buffer
 * @param pSktBuf SktBuf
 * @param Len New length of buffer
 */
bool SktBuf_Trim(tSktBuf * pSktBuf, size_t Len);

/**
 * @brief Bytes at buffer head
 * @param pSktBuf SktBuf
 * @return The number of bytes of free space at the head.
 */
int SktBuf_Headroom(tSktBuf * pSktBuf);

/**
 * @brief Bytes at buffer end
 * @param pSktBuf SktBuf
 * @return The number of bytes of free space at the tail.
 */
int SktBuf_Tailroom(tSktBuf * pSktBuf);

/**
 * @brief Return a read-only pointer to the start of buffer. This is typically used when doing
 *        the actual IO.
 * @param pSktBuf SktBuf
 * @return Start of buffer
 */
const uint8_t * SktBuf_Data(const tSktBuf * pSktBuf);

/**
 * @brief Return the length of data stored
 * @param pSktBuf SktBuf
 * @return Number of bytes stored in data
 */
size_t SktBuf_DataLen(const tSktBuf * pSktBuf);

/**
 * @brief Check canaries
 * @param pSktBuf SktBuf to check
 * @return Whether the canary check has passed
 */
bool SktBuf_CheckCanaries(const tSktBuf * pSktBuf);

/**
 * @brief Push a new canary to the front of buffer
 * @param[in, out] pSktBuf SktBuf to check
 * @return Whether the canary check has passed
 */
bool SktBuf_PushCanary(tSktBuf * pSktBuf);

/**
 * @brief Remove all the canaries in the buffer.
 * @param[in, out] pSktBuf SktBuf
 */
void SktBuf_RemoveCanaries(tSktBuf * pSktBuf);

#ifdef __cplusplus
}
#endif

#endif /* __PLAT_UTIL_SKTBUF_H_ */

/**
 * @}
 */
