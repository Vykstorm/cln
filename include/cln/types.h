// Basic type definitions

#ifndef _CL_TYPES_H
#define _CL_TYPES_H

// CPU and other
#include "cln/config.h"

// char_bitsize, short_bitsize, long_bitsize, long_long_bitsize
#include "cln/intparam.h"

// Elementary arithmetic types of given width:
  // 8 bits
  #if (char_bitsize==8)
    typedef signed char    sint8;
    typedef unsigned char  uint8;
  #else
    #error "No 8 bit integer type?"
  #endif
  // 16 bits
  #if (short_bitsize==16)
    typedef short           sint16;
    typedef unsigned short  uint16;
  #else
    #error "No 16 bit integer type?"
  #endif
  // 32 bits
  #if (long_bitsize==32)
    typedef long           sint32;
    typedef unsigned long  uint32;
  #elif (int_bitsize==32)
    typedef int            sint32;
    typedef unsigned int   uint32;
  #else
    #error "No 32 bit integer type?"
  #endif
  // 64 bits
  #if (long_bitsize==64)
    typedef long           sint64;
    typedef unsigned long  uint64;
    #undef HAVE_LONGLONG
    #define HAVE_LONGLONG
  #elif defined(HAVE_LONGLONG)
   #if defined(long_long_bitsize) && (long_long_bitsize==64)
    typedef long long           sint64;
    typedef unsigned long long  uint64;
   #else // unusable type
    #undef HAVE_LONGLONG
   #endif
  #endif
  #if defined(HAVE_LONGLONG) && (defined(__alpha__) || defined(__mips64__) || defined(__sparc64__) || defined(__ia64__))
    // 64 bit registers in hardware
    #define HAVE_FAST_LONGLONG
  #endif
// Synonyms
  #define intBsize 8
  typedef sint8  sintB;
  typedef uint8  uintB;
  #define intWsize 16
  typedef sint16 sintW;
  typedef uint16 uintW;
  #define intLsize 32
  typedef sint32 sintL;
  typedef uint32 uintL;
  #ifdef HAVE_LONGLONG
    #define intQsize 64
    typedef sint64 sintQ;
    typedef uint64 uintQ;
  #endif

// Boolean type.
#if 1
  typedef enum { cl_false = 0, cl_true = 1 }
          cl_boolean;
#else
  typedef bool cl_boolean;
  #define cl_false 0
  #define cl_true  1
#endif

// Type for three values (0, +1, -1).
  typedef int  cl_signean;
  #define signean_plus  1
  #define signean_null  0
  #define signean_minus -1

// Integer type used for counters.
  #if (defined(HAVE_FAST_LONGLONG) && (defined(__alpha__) || defined(__ia64__)))
    #define intCsize long_bitsize
    typedef long           sintC;
    typedef unsigned long  uintC;
  #else
    #define intCsize int_bitsize
    typedef int           sintC;
    typedef unsigned int  uintC;
  #endif

// Integer type as large as a pointer.
// Assumption: sizeof(long) == sizeof(void*)
  #define intPsize long_bitsize
  typedef long           sintP;
  typedef unsigned long  uintP;

// Largest integer type which can be manipulated as efficiently as a pointer.
// This is normally the same as the hardware register size.
// Assumption: cl_word_size >= intPsize
  #ifdef HAVE_FAST_LONGLONG
    #define cl_word_size  64
  #else
    #define cl_word_size  32
  #endif

// Numbers in the heap are stored as "digit" sequences.
// A digit is an unsigned int with intDsize bits.
// intDsize should be 8 or 16 or 32 or 64.
  #if (defined(HAVE_FAST_LONGLONG) && (defined(__alpha__) || defined(__ia64__)))
    #define intDsize 64
    #define intDDsize 128  // = 2*intDsize
    #define log2_intDsize  6  // = log2(intDsize)
  #else
    #define intDsize 32
    #define intDDsize 64  // = 2*intDsize
    #define log2_intDsize  5  // = log2(intDsize)
  #endif
  #if (intDsize==8)
    typedef sint8  sintD;
    typedef uint8  uintD;
  #endif
  #if (intDsize==16)
    typedef sint16  sintD;
    typedef uint16  uintD;
  #endif
  #if (intDsize==32)
    typedef sint32  sintD;
    typedef uint32  uintD;
  #endif
  #if (intDsize==64)
    typedef sint64  sintD;
    typedef uint64  uintD;
  #endif
// HAVE_DD means that there are unsigned ints with 2*intDsize bits.
  #if (intDDsize <= (defined(HAVE_FAST_LONGLONG) ? 64 : 32))
    #define HAVE_DD 1
    #if (intDDsize==16)
      typedef sint16  sintDD;
      typedef uint16  uintDD;
    #endif
    #if (intDDsize==32)
      typedef sint32  sintDD;
      typedef uint32  uintDD;
    #endif
    #if (intDDsize==64)
      typedef sint64  sintDD;
      typedef uint64  uintDD;
    #endif
  #else
    #define HAVE_DD 0
  #endif

#endif /* _CL_TYPES_H */
