/**
 * @addtogroup stack_debugging Generic debug printing framework for stack components
 * @{
 *
 * Cohda Wireless Stack Libraries debug printing definitions
 *
 * @file
 *
 *
 */
//------------------------------------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef INLINE
#undef INLINE
#endif
#define INLINE inline

#ifndef INCLUDE__DEBUG_LEVELS_H__
#define INCLUDE__DEBUG_LEVELS_H__

// Some handy levels to consider using with the d_*() functions
#define D_EMERG                 (0)
#define D_ALERT                 (1)
#define D_CRIT                  (2)
#define D_ERR                   (3)
#define D_WARN                  (4)
#define D_NOTICE                (5)
#define D_INFO                  (6)
#define D_DEBUG                 (7)
#define D_TEST                  (8)
#define D_VERBOSE               (9)
#define D_IRQ                   (127)
#define D_ALL                   (255)

// Some other handy levels
#define D_API                   (D_INFO)
#define D_INTERN                (D_DEBUG)
#define D_DBG                   (D_DEBUG)
#define D_TST                   (D_VERBOSE)

/// Master debug switch; !0 enables, 0 disables
#ifndef D_MASTER
#define D_MASTER (!(bool)0)
#endif

#ifndef D_LOCAL
  #define D_LOCAL D_ALL
//#define D_LOCAL D_WARN
#endif

/// Default to stderr (unbuffered)
#define D_LOGFILE stderr

#undef d_printf__internal
#undef d_fnstart
#undef d_fnend
#undef d_printf
#undef d_error
#undef d_assert
#undef d_dump

// Backend stuff

/// The debug level
extern int D_LEVEL;

/**
 * @brief Declare the debug level
 */
#define D_LEVEL_DECLARE() int D_LEVEL = D_LOCAL

/**
 * @brief Initialize the debug level
 */
#define D_LEVEL_INIT() D_LEVEL = d_level__internal()

/**
 * @brief Generate a message header from a 'struct device'
 * @param pHead Buffer where to place the header
 * @param Size Length of head
 * @param pHdl Pointer to device used to generate a header from. If NULL,
 *     an empty ("") header is generated.
 */
static INLINE void d_dev_head__internal(char *pHead,
                                        size_t Size,
                                        const void *pHdl)
{
  if (pHdl == NULL)
  {
    ;
  }
  else
  {
    (void)snprintf(pHead, Size, "[%p]:", pHdl);
  }
}

/**
 * @brief Test whether to trace or not (based on D_MASTER, D_LOCAL and d_level)
 */
#define d_test(l) (((int)D_MASTER != 0) && (D_LOCAL >= (l)) && (D_LEVEL >= (l)))

#ifdef DEBUG_PRINT_TIMES

#ifdef __cplusplus
extern "C"
{
#endif

void debug_hdr(int Level, const char *pMod, char *pHdr, size_t HdrSize);
void debug_dump(int Level, const char *pMod, const char *pFunc, const void *pPtr, size_t Size);

#ifdef __cplusplus
}
#endif

// Code modules can define a 'top-level' debug group, but set a default string here
#ifndef D_MODULE
#define D_MODULE "UNK"
#endif

/**
 * @brief Log some message if debugging is enabled (with normal header)
 * @param l: intended debug level
 * @param tag: tag to prefix the message with
 * @param dev: 'struct device' associated to this message
 * @param f: printf-like format and arguments
 *
 * Note this is optimized out if it doesn't pass the compile-time
 * check; however, it is *always* compiled. This is useful to make
 * sure the printf-like formats and variables are always checked and
 * they don't get bit rot if you have all the debugging disabled.
 */
#define d_printf__internal(l, tag, dev, f, a...) \
  do { \
    if (d_test(l)) { \
      char head__internal[64] = ""; \
      debug_hdr(l, D_MODULE, head__internal, sizeof(head__internal)); \
      fprintf(D_LOGFILE, "%s%s" tag ": " f, head__internal, __func__, ## a); \
    } \
  } while ((bool)0)

/**
 * @brief Trace buffer data
 */
#define d_dump(l, dev, ptr, size) \
  do { \
    if (d_test(l)) \
      debug_dump(l, D_MODULE, __func__, ptr, size); \
  } while ((bool)0)

#else
/**
 * @brief Log some message if debugging is enabled
 * @param l: intended debug level
 * @param tag: tag to prefix the message with
 * @param dev: 'struct device' associated to this message
 * @param f: printf-like format
 * @param a: printf-like arguments
 *
 * Note this is optimized out if it doesn't pass the compile-time
 * check; however, it is *always* compiled. This is useful to make
 * sure the printf-like formats and variables are always checked and
 * they don't get bit rot if you have all the debugging disabled.
 */

#define d_printf__internal(l, tag, dev, f, a...) \
  do { \
    const void *dev_macro__internal = (const void *)(dev); \
    if (d_test(l)) { \
      char __head[64] = ""; \
      d_dev_head__internal(__head, sizeof(__head), dev_macro__internal); \
      fprintf(D_LOGFILE, "%s%s" tag ": " f, __head,    __func__, ## a); \
    } \
  } while ((bool)0)

static INLINE void d_dump__internal(int l, void *dev__internal, const void *ptr__internal, size_t size)
{
  const unsigned char *ptr = (const unsigned char *)ptr__internal;
  char str[64];
  size_t cnt = 0U;
  size_t itr = 0U;
  for (; cnt < size; cnt++)
  {
    itr += snprintf(str + itr, sizeof(str) - itr, "%02x ", (unsigned)ptr[cnt]);
    if ((cnt > 0 && (cnt + 1) % 8 == 0) || (cnt == size - 1))
    {
      d_printf__internal(l, "", dev__internal, "%s\n", str);
      itr = 0;
    }
  }
}

/**
 * @brief Trace buffer data
 */
#define d_dump(l, dev, ptr, size)   \
  do {                              \
    if (d_test(l))                  \
      d_dump__internal(l, dev, ptr, size);  \
  } while ((bool)0)

#endif // DEBUG_PRINT_TIMES

/**
 * @brief Trace a function entry
 */
#define d_fnstart(l, _dev, f, a...) d_printf__internal(l, " FNSTART", _dev, f, ## a)

/**
 * @brief Trace a function exit/return
 */
#define d_fnend(l, _dev, f, a...) d_printf__internal(l, " FNEND", _dev, f, ## a)

/**
 * @brief Trace information
 */
#define d_printf(l, _dev, f, a...) d_printf__internal(l, "", _dev, f, ## a)

/**
 * @brief Trace an error
 */
#define d_error(l, _dev, f, a...) d_printf__internal(l, " ERROR", _dev, f, ## a)

/**
 * @brief Assertion check
 * @param arg: assertion to check
 */
#define d_assert(arg) assert(arg)

/**
 * @brief Debug print with custom header
 * NOTE level check is expected to have been done earlier
 */
#define d_printf__nf(l, tag, hdr, func, f, a...) \
  do { \
      fprintf(D_LOGFILE, "%s%s" tag ": " f, hdr, func, ## a); \
  } while ((bool)0)


static INLINE int d_level__internal(void)
{
  char *pEnvString;

  // Get the controllable debug verbosity level from the environment
  pEnvString = getenv("D_LEVEL");
  if (pEnvString)
    return atoi(pEnvString);
  else
    return D_LOCAL;
}


// Custom debug
#ifndef NO_DEBUG_PRINT_USER

#define d_usertest(var, l) (var >= l)

#ifdef DEBUG_PRINT_TIMES

#ifdef __cplusplus
extern "C"
{
#endif

void debug_hdr(int Level, const char *pMod, char *pHdr, size_t HdrSize);
void debug_udpprintf(const char *pFmt, ...);

#ifdef __cplusplus
}
#endif

#define d_userprintf(var, l, f, a...) \
  do { \
    if (var >= l) { \
      char head__internal[64] = ""; \
      debug_hdr(l, "USER", head__internal, sizeof(head__internal)); \
      fprintf(D_LOGFILE, "%s%s: PktDebug: " f, head__internal, __func__, ## a); \
      debug_udpprintf(f, ## a); \
    } \
  } while ((bool)0)

#else

#define d_userprintf(var, l, f, a...) \
  do { \
    if (var >= l) \
    { \
      struct timespec _Now; \
      clock_gettime(CLOCK_REALTIME, &_Now); \
      fprintf(D_LOGFILE, "[%ld.%09lu] %s: PktDebug: " f, (long)_Now.tv_sec, _Now.tv_nsec,  __FUNCTION__, ## a); \
    } \
  } while ((bool)0)

#endif
#else
#define d_usertest(var, l) (false)
#define d_userprintf(var, l, f, a...)
#endif
// "d_userprintf(pMsg->pPkt->DebugLDM, ..." is very common and unsafe unless gated
#define d_userprintfMsg(pMsg, var, l, f, a...) \
  do \
  { \
    if ((pMsg != NULL) && (pMsg->pPkt != NULL)) \
    { \
      d_userprintf(pMsg->pPkt->var, l, f, ## a); \
    }\
  } while ((bool)0)

#endif //INCLUDE__DEBUG_LEVELS_H__

// Close the Doxygen group
/**
 * @}
 */
