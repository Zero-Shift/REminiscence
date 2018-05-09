/*
 * This source code is public domain.
 *
 * Authors: Rani Assaf <rani@magic.metawire.com>,
 *          Olivier Lapicque <olivierl@jps.net>,
 *          Adam Goode       <adam@evdebs.org> (endian and char fixes for PPC)
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <stdint.h>

/* disable AGC and FILESAVE for all targets for uniformity. */
#define NO_AGC
#define MODPLUG_NO_FILESAVE

#ifdef _WIN32

#ifdef MSC_VER
#pragma warning (disable:4201)
#pragma warning (disable:4514)
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#define srandom(_seed)  srand(_seed)
#define random()        rand()

inline void ProcessPlugins(int n) {}

#undef strcasecmp
#undef strncasecmp
#define strcasecmp(a,b)     _stricmp(a,b)
#define strncasecmp(a,b,c)  _strnicmp(a,b,c)

#define HAVE_SINF 1

#ifndef isblank
#define isblank(c) ((c) == ' ' || (c) == '\t')
#endif

#else

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

typedef int8_t CHAR;
typedef uint8_t UCHAR;
typedef uint8_t* PUCHAR;
typedef uint16_t USHORT;
typedef uint32_t ULONG;
typedef uint32_t UINT;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef int64_t LONGLONG;
typedef int32_t* LPLONG;
typedef uint32_t* LPDWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;
typedef uint8_t* LPBYTE;
typedef bool BOOL;
typedef char* LPSTR;
typedef void* LPVOID;
typedef uint16_t* LPWORD;
typedef const char* LPCSTR;
typedef void* PVOID;
typedef void VOID;

inline LONG MulDiv (long a, long b, long c)
{
/*if (!c) return 0;*/
  return ((uint64_t) a * (uint64_t) b ) / c;
}

#define LPCTSTR LPCSTR
#define lstrcpyn strncpy
#define lstrcpy strcpy
#define lstrcmp strcmp
#define wsprintf sprintf

#define WAVE_FORMAT_PCM 1

#define  GHND   0
#define GlobalFreePtr(p) free((void *)(p))
inline int8_t * GlobalAllocPtr(unsigned int, size_t size)
{
  int8_t * p = (int8_t *) malloc(size);

  if (p != NULL) memset(p, 0, size);
  return p;
}

inline void ProcessPlugins(int n) {}

#ifndef FALSE
#define FALSE	false
#endif

#ifndef TRUE
#define TRUE	true
#endif

#endif /* _WIN32 */

#define MODPLUG_EXPORT

#endif
