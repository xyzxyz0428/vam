/**
 * @addtogroup util_util Utility Functions
 * @{
 *
 * @section util_dd What Does It Do
 * Provides utility functions
 *
 * @file
 *
 * Module code for utility functions
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2010 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __APPCORE_UTIL_UTIL_H_
#define __APPCORE_UTIL_UTIL_H_


//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------

#include <sys/time.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#if defined(__QNX__)
#include <gulliver.h>
#else
#include <endian.h>
#include <byteswap.h>
#endif

#ifdef __cplusplus
extern "C"
{
#else
// c++ has std::min and std::max
/// min
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

/// max
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

/// swap
#ifndef swap
#define swap(x,y) \
do  \
{   \
  typeof(x) _x = x;      \
  typeof(y) _y = y;      \
  x = _y;                \
  y = _x;                \
} while(false)
#endif

#endif // #ifdef __cplusplus

//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------


#if defined(__QNX__)
// QNX doesn't define length of a MAC address
#define ETH_ALEN     6
#define ETH_HLEN     (sizeof(struct ethhdr))
#define ETH_ZLEN     60  /* Min. octets in frame sans FCS */

// neither AT or QNX define struct ethhdr
struct ethhdr {
    unsigned char      h_dest[ETH_ALEN];   /* destination eth addr */
    unsigned char      h_source[ETH_ALEN]; /* source ether addr    */
    uint16_t/*__be16*/ h_proto;            /* packet type ID field */
} __attribute__((packed));
#else
#include <net/ethernet.h>
#endif

#if defined(__QNX__)

#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

#endif


#define STR(x)   #x
#define XSTR(x)  STR(x)

#ifndef TAG
#define TAG fputs("\t\t ### " __FILE__ " @ " XSTR(__LINE__)" ###\n", stderr)
#endif

#define SAFE(x) ((x)? (x) : "<NULL>")

#define bound(min_val, val, max_val) (max(min_val, min(val, max_val)))

#define SIGN(x) (((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))

/// Compile-time assertions
#ifndef BUILD_BUG_ON
#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))
#endif

/// Offset of a member of a struct into stat struct
#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

/// Inheritance with C structs
#ifndef container_of
#define container_of(ptr, type, member) ({                      \
      const typeof( ((type *)0)->member ) *__mptr = (ptr);      \
      (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef DO_PRAGMA
#define DO_PRAGMA(x) _Pragma (#x)
#endif
#ifndef NOTE
#define NOTE(x)  DO_PRAGMA(message ("NOTE - "  #x))
#endif
#ifndef TODO
#define TODO(x)  DO_PRAGMA(message ("TODO - "  #x))
#endif
#ifndef FIXME
#define FIXME(x) DO_PRAGMA(message ("FIXME - " #x))
#endif

  // Macro to suppress FALLTHROUGH warnings in switch statements.
#ifndef FALLTHROUGH
#  if defined(__GNUC__) && __GNUC__ >= 7
#    define FALLTHROUGH __attribute__((fallthrough));
  // At least one Clang 6 version advertises fallthrough and then chokes on it
#  elif defined(__clang__) && __clang_major__ > 6
#    ifndef __has_attribute         // For backwards compatibility
#      define __has_attribute(x) 0
#    endif
#    if __has_attribute(fallthrough)
#      define FALLTHROUGH __attribute__((fallthrough));
#    endif
#  endif
#else
#  define FALLTHROUGH
#endif

/// Allow 64-bit endian conversions
#if __BYTE_ORDER == __LITTLE_ENDIAN
# ifndef htonll
#  if defined(__QNX__)
#   define htonll(x) ENDIAN_RET64(x)
#  else // __QNX__
#   define htonll(x) __bswap_64 (x)
#  endif // __QNX__
# endif //htonll
# ifndef ntohll
#  if defined(__QNX__)
#   define ntohll(x) ENDIAN_RET64(x)
#  else // __QNX__
#   define ntohll(x) __bswap_64 (x)
#  endif // __QNX__
# endif
#else
# ifndef htonll
#  define htonll(x) x
# endif
# ifndef ntohll
#  define ntohll(x) x
# endif
#endif

/// Allow comparison of timespec values
# define timespeccmp(a, b, CMP) \
  (((a)->tv_sec == (b)->tv_sec) ? \
   ((a)->tv_nsec CMP (b)->tv_nsec) : \
   ((a)->tv_sec CMP (b)->tv_sec))

// Make sure (x) is promoted to float!
#define UTIL_NM_TO_MILLI_SECS(x)           ((x) * (60000.0 / (1<<16)))
#define UTIL_MILLI_SECS_TO_NM(x)           ((x) * ((1<<16) / 60000.0))
#define UTIL_SECS_TO_NM(x)                 ((x) * ((1<<16) / 60.0))
// don't do this, use
// VS_GetVehLength_mm(pHV->pVState, NULL)
// #define UTIL_CAR_LENGTH_TO_MM(x)           (1000 + ((x) * 5))

// Sanity check size of integer before changing byte-order
#ifndef hton_u16
#define hton_u16(x)                            \
 ({                                            \
   const uint16_t h = (x);                     \
   BUILD_BUG_ON(sizeof(x) != sizeof(h));       \
   const uint16_t n = htons(x);                \
   n;                                          \
 })
#endif

#ifndef ntoh_u16
#define ntoh_u16(x)                             \
  ({                                            \
    const uint16_t n = (x);                     \
    BUILD_BUG_ON(sizeof(x) != sizeof(n));       \
    const uint16_t h = ntohs(x);                \
    h;                                          \
  })
#endif

#ifndef hton_u32
#define hton_u32(x)                             \
  ({                                            \
    const uint32_t h = (x);                     \
    BUILD_BUG_ON(sizeof(x) != sizeof(h));       \
    const uint32_t n = htonl(x);                \
    n;                                          \
  })
#endif

#ifndef ntoh_u32
#define ntoh_u32(x)                             \
  ({                                            \
    const uint32_t n = (x);                     \
    BUILD_BUG_ON(sizeof(x) != sizeof(n));       \
    const uint32_t h = ntohl(x);                \
    h;                                          \
  })
#endif

//------------------------------------------------------------------------------
// Type definitions
//------------------------------------------------------------------------------

/// Timing Statistics
typedef struct TimingStats
{
  /// Identifier
  const char * tag;
  /// Counter
  unsigned      num;
  // times in microseconds
  // (nanoseconds are theoretically available but mostly pointless)
  /// Min value
  uint64_t       min;
  /// Max value
  uint64_t       max;
  /// Total
  uint64_t       sum;
  /// Total squared
  uint64_t       sumSQ;
} tTimingStats;
#define TIMING_STATS(x) static tTimingStats x = {#x,0,0,0,0,0}


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/// Start a thread
#define Util_StartThreadAffinity(pThread, SchedulerPolicy, SchedulerPriority_pc, \
                                 pStartRoutine, pArg, CPU_Mask) \
                                 \
                                 Util_StartThreadAffinity_(pThread, \
                                                           SchedulerPolicy, \
                                                           SchedulerPriority_pc, \
                                                           pStartRoutine, \
                                                           #pStartRoutine, \
                                                           pArg, \
                                                           CPU_Mask)
/// Start a thread
#define Util_StartThread(pThread, SchedulerPolicy, SchedulerPriority_pc, \
                         pStartRoutine, pArg) \
                         \
                         Util_StartThread_(pThread, \
                                           SchedulerPolicy, \
                                           SchedulerPriority_pc, \
                                           pStartRoutine, \
                                           #pStartRoutine, \
                                           pArg)

int Util_StartThreadAffinity_(pthread_t * pThread,
                              int   SchedulerPolicy,
                              int   SchedulerPriority_pc,
                              void *(*pStartRoutine)(void*),
                              const char * pName,
                              void *pArg,
                              const uint32_t CPU_Mask);

// pthread_create
int Util_StartThread_(pthread_t *pThread,
                      int SchedulerPolicy,
                      int SchedulerPriority_pc,
                      void *(*pStartRoutine)(void*),
                      const char *pName,
                      void *pArg);

// pthread_exit
void Util_ExitThread(void * pRet) __attribute__ ((__noreturn__));
// pthread_join
int Util_JoinThread(pthread_t Thread, void ** ppRet);

/// malloc/memcpy
void *Util_Memdup(const void *pSrc, size_t Len);

/// Sleep until the next multiple of ms
void Util_Nap(unsigned ms, struct timespec *ts);

/**
 * @brief Sleep for the next number of milliseconds
 * @param  MilliSec  Number of milliseconds
 * @return Status (from nanosleep)
 * NOTE that usleep is obsolete (POSIX.1-2001)
 */
int Util_Sleep(unsigned int MilliSec);

/// Start a timer
void Util_StartTimer(struct timespec *pBegin);

/// Return elapsed time since a timer was started (can be called multiple timer)
double Util_StopTimer(const struct timespec *pBegin);

// Current time, normalised minute (16 bit unsigned that wraps on the full minute)
uint16_t Util_NowNM(void);

// Extract the normalised minute form a UTC timestamp
uint16_t Util_UTCtoNM(const struct timeval *pUTC);

// minute-of-year
uint32_t Util_NowMoY(void);
uint32_t Util_UTCtoMoY(const struct timeval * pUTC);

// Milliseconds since the Unix epoch
uint64_t Util_Now();

uint64_t Util_StopTimerWithStats(const struct timespec *pBegin, tTimingStats *pStats);

uint64_t Util_lapWithStats( struct timespec *pBegin, tTimingStats *pStats);

void Util_printTimingStats(const char *pTag, const tTimingStats *pStats);

void Util_SetShutdownFlag(void);
void Util_SetShutdownFlagBecause(const char * pReason);

bool Util_GetShutdownFlag(void);

bool Util_Poll(unsigned Interval_ms, struct timespec * pTS, bool TerminateFlag);

uint32_t Util_BufftoPSID(uint8_t *pBuff);

uint32_t Util_PSIDfromBuff(uint8_t *pBuff, size_t Len);

size_t Util_PSIDtoBuff(uint32_t PSID, int8_t *pBuff, size_t Len);

size_t Util_VarFromBuff_PSID(uint8_t *pBuf, uint32_t *pVar);

size_t Util_OERLenPrefixValue(uint8_t *pBuf, uint32_t *pVar);

/// Borrowing timespec comparison function prototypes from:
/// http://www.daemon-systems.org/man/timeradd.3.html
/// Add 2 normalised timestamps
void timespecadd(const struct timespec *a,
                 const struct timespec *b,
                 struct timespec *res);

/// Subtract 2 normalised timestamps
void timespecsub(const struct timespec *a,
                 const struct timespec *b,
                 struct timespec *res);

/// Compare 2 timestamps
int timespec_compare(const struct timespec * a,
                     const struct timespec * b);

/// Read file (with optional extension) and return contents
void * Util_ReadBlob(const char *pStub,
                     const char *pExt,
                     int32_t *pLen,
                     bool DeleteAfterOpening);

uint32_t Util_GetIPv4(const char *pNIC); ///< defaults to "eth0"
int      Util_GetWLANMAC(unsigned char MAC[6]);
void     Util_GetMAC(const char *pMask, unsigned char MAC[6]);

/// Set replay offset (in timeval format, back to when log was captured)
int Util_SetReplayOffset(struct timeval Offset);
struct timeval Util_GetReplayOffset(void);

// the following are basically
// int asprintf(char **strp, const char *fmt, ...);
// int vasprintf(char **strp, const char *fmt, va_list ap);
// and should re removed if/when we decide all build platforms have support for those.
char *xxprintf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
char *vxprintf(const char *fmt, va_list ap);

int systemf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

/// Fill the buffer with random bytes
void Util_GetRandomBytes(void *pBuf, int NBytes);
/// Return a random integer in the indicated range (both limits included!)
uint32_t Util_RandomInRange(uint32_t IncludedMin, uint32_t IncludedMax);
/// Fill the buffer with a random but valid MAC address
void Util_GetRandomMAC(void *pMAC);

/// Increment counter pointed to by pCounter and return the new value
int Util_AtomicIncrement(int *pCounter);

/// Decrement counter pointed to by pCounter and return the new value
int Util_AtomicDecrement(int *pCounter);

/// Ensure that there is a single instance of something.
bool Util_IsUnique(const char * pTag);

/// strncpy only when buffer size allows
bool strncpy_s(char *pDst, const char *pSrc, size_t Len);

/// strncpy with the output buffer always terminated
int strncpy_t(char * pDst, const char * pSrc, size_t Len);
#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif //  __APPCORE_UTIL_UTIL_H_
