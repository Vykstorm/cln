// UDS_to_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I.h"


// Implementation.

#include "cl_DS.h"

namespace cln {

// Tabelle: enthält zu jeder Basis b (2 <= b <= 36)
// - eine Kettenbruchapproximation num/den von intDsize*log(2)/log(b)
//   (num/den >= intDsize*log(2)/log(b), mit num <= 2^10)
// - k-1 und b^k mit b^k < 2^intDsize, k maximal.
  typedef struct { /* uintW num,den; */ uintC k_1; uintD b_hoch_k; } power_table_entry;
  static power_table_entry table [36-2+1] = {
    #if (intDsize==8)
      { /*    8,  1, */ 7-1, 2*2*2*2*2*2*2},
      { /*  106, 21, */ 5-1, 3*3*3*3*3},
      { /*    4,  1, */ 3-1, 4*4*4},
      { /*  789,229, */ 3-1, 5*5*5},
      { /*  359,116, */ 3-1, 6*6*6},
      { /*  436,153, */ 2-1, 7*7},
      { /*    8,  3, */ 2-1, 8*8},
      { /*   53, 21, */ 2-1, 9*9},
      { /*  525,218, */ 2-1, 10*10},
      { /* 1006,435, */ 2-1, 11*11},
      { /*  665,298, */ 2-1, 12*12},
      { /*  988,457, */ 2-1, 13*13},
      { /*  872,415, */ 2-1, 14*14},
      { /*  987,482, */ 2-1, 15*15},
      { /*    2,  1, */ 1-1, 16},
      { /*  869,444, */ 1-1, 17},
      { /*  871,454, */ 1-1, 18},
      { /*  597,317, */ 1-1, 19},
      { /*   87, 47, */ 1-1, 20},
      { /*  989,543, */ 1-1, 21},
      { /*  949,529, */ 1-1, 22},
      { /*  191,108, */ 1-1, 23},
      { /*  930,533, */ 1-1, 24},
      { /*  789,458, */ 1-1, 25},
      { /*  691,406, */ 1-1, 26},
      { /*  461,274, */ 1-1, 27},
      { /*  218,131, */ 1-1, 28},
      { /*  690,419, */ 1-1, 29},
      { /*  494,303, */ 1-1, 30},
      { /*  633,392, */ 1-1, 31},
      { /*    8,  5, */ 1-1, 32},
      { /*  766,483, */ 1-1, 33},
      { /*  629,400, */ 1-1, 34},
      { /*  967,620, */ 1-1, 35},
      { /*  359,232, */ 1-1, 36},
    #endif
    #if (intDsize==16)
      { /*   16,  1, */ 15-1, 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2},
      { /*  212, 21, */ 10-1, 3*3*3*3*3*3*3*3*3*3},
      { /*    8,  1, */  7-1, 4*4*4*4*4*4*4},
      { /*  379, 55, */  6-1, 5*5*5*5*5*5},
      { /*  359, 58, */  6-1, 6*6*6*6*6*6},
      { /*  872,153, */  5-1, 7*7*7*7*7},
      { /*   16,  3, */  5-1, 8*8*8*8*8},
      { /*  106, 21, */  5-1, 9*9*9*9*9},
      { /*  525,109, */  4-1, 10*10*10*10},
      { /* 1013,219, */  4-1, 11*11*11*11},
      { /*  665,149, */  4-1, 12*12*12*12},
      { /*  761,176, */  4-1, 13*13*13*13},
      { /*  685,163, */  4-1, 14*14*14*14},
      { /*  987,241, */  4-1, 15*15*15*15},
      { /*    4,  1, */  3-1, 16*16*16},
      { /*  869,222, */  3-1, 17*17*17},
      { /*  871,227, */  3-1, 18*18*18},
      { /*  113, 30, */  3-1, 19*19*19},
      { /*  174, 47, */  3-1, 20*20*20},
      { /*   51, 14, */  3-1, 21*21*21},
      { /*  653,182, */  3-1, 22*22*22},
      { /*  191, 54, */  3-1, 23*23*23},
      { /*  677,194, */  3-1, 24*24*24},
      { /*  789,229, */  3-1, 25*25*25},
      { /*  691,203, */  3-1, 26*26*26},
      { /*  461,137, */  3-1, 27*27*27},
      { /*  436,131, */  3-1, 28*28*28},
      { /*  359,109, */  3-1, 29*29*29},
      { /*  988,303, */  3-1, 30*30*30},
      { /*  633,196, */  3-1, 31*31*31},
      { /*   16,  5, */  3-1, 32*32*32},
      { /*  203, 64, */  3-1, 33*33*33},
      { /*  629,200, */  3-1, 34*34*34},
      { /*  967,310, */  3-1, 35*35*35},
      { /*  359,116, */  3-1, 36*36*36},
    #endif
    #if (intDsize==32)
      { /*   32,  1, */ 31-1, 2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL*2UL},
      { /*  424, 21, */ 20-1, 3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL*3UL},
      { /*   16,  1, */ 15-1, 4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL*4UL},
      { /*  758, 55, */ 13-1, 5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL*5UL},
      { /*  359, 29, */ 12-1, 6UL*6UL*6UL*6UL*6UL*6UL*6UL*6UL*6UL*6UL*6UL*6UL},
      { /*   57,  5, */ 11-1, 7UL*7UL*7UL*7UL*7UL*7UL*7UL*7UL*7UL*7UL*7UL},
      { /*   32,  3, */ 10-1, 8UL*8UL*8UL*8UL*8UL*8UL*8UL*8UL*8UL*8UL},
      { /*  212, 21, */ 10-1, 9UL*9UL*9UL*9UL*9UL*9UL*9UL*9UL*9UL*9UL},
      { /*  289, 30, */  9-1, 10UL*10UL*10UL*10UL*10UL*10UL*10UL*10UL*10UL},
      { /*  990,107, */  9-1, 11UL*11UL*11UL*11UL*11UL*11UL*11UL*11UL*11UL},
      { /*  848, 95, */  8-1, 12UL*12UL*12UL*12UL*12UL*12UL*12UL*12UL},
      { /*  761, 88, */  8-1, 13UL*13UL*13UL*13UL*13UL*13UL*13UL*13UL},
      { /* 1017,121, */  8-1, 14UL*14UL*14UL*14UL*14UL*14UL*14UL*14UL},
      { /*  901,110, */  8-1, 15UL*15UL*15UL*15UL*15UL*15UL*15UL*15UL},
      { /*    8,  1, */  7-1, 16UL*16UL*16UL*16UL*16UL*16UL*16UL},
      { /*  869,111, */  7-1, 17UL*17UL*17UL*17UL*17UL*17UL*17UL},
      { /*  683, 89, */  7-1, 18UL*18UL*18UL*18UL*18UL*18UL*18UL},
      { /*  113, 15, */  7-1, 19UL*19UL*19UL*19UL*19UL*19UL*19UL},
      { /*  348, 47, */  7-1, 20UL*20UL*20UL*20UL*20UL*20UL*20UL},
      { /*   51,  7, */  7-1, 21UL*21UL*21UL*21UL*21UL*21UL*21UL},
      { /*  653, 91, */  7-1, 22UL*22UL*22UL*22UL*22UL*22UL*22UL},
      { /*  191, 27, */  7-1, 23UL*23UL*23UL*23UL*23UL*23UL*23UL},
      { /*  677, 97, */  6-1, 24UL*24UL*24UL*24UL*24UL*24UL},
      { /*  379, 55, */  6-1, 25UL*25UL*25UL*25UL*25UL*25UL},
      { /*  851,125, */  6-1, 26UL*26UL*26UL*26UL*26UL*26UL},
      { /*  922,137, */  6-1, 27UL*27UL*27UL*27UL*27UL*27UL},
      { /*  872,131, */  6-1, 28UL*28UL*28UL*28UL*28UL*28UL},
      { /*  718,109, */  6-1, 29UL*29UL*29UL*29UL*29UL*29UL},
      { /*  150, 23, */  6-1, 30UL*30UL*30UL*30UL*30UL*30UL},
      { /*  633, 98, */  6-1, 31UL*31UL*31UL*31UL*31UL*31UL},
      { /*   32,  5, */  6-1, 32UL*32UL*32UL*32UL*32UL*32UL},
      { /*  203, 32, */  6-1, 33UL*33UL*33UL*33UL*33UL*33UL},
      { /*  629,100, */  6-1, 34UL*34UL*34UL*34UL*34UL*34UL},
      { /*  967,155, */  6-1, 35UL*35UL*35UL*35UL*35UL*35UL},
      { /*  359, 58, */  6-1, 36UL*36UL*36UL*36UL*36UL*36UL},
    #endif
    #if (intDsize==64)
      { /*   64,  1, */ 63-1, 2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL*2ULL},
      { /*  848, 21, */ 40-1, 3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL*3ULL},
      { /*   32,  1, */ 31-1, 4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL*4ULL},
      { /*  634, 23, */ 27-1, 5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL*5ULL},
      { /*  718, 29, */ 24-1, 6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL*6ULL},
      { /*  114,  5, */ 22-1, 7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL*7ULL},
      { /*   64,  3, */ 21-1, 8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL*8ULL},
      { /*  424, 21, */ 20-1, 9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL*9ULL},
      { /*  289, 15, */ 19-1, 10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL*10ULL},
      { /* 1018, 55, */ 18-1, 11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL*11ULL},
      { /*  607, 34, */ 17-1, 12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL*12ULL},
      { /*  761, 44, */ 17-1, 13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL*13ULL},
      { /*  975, 58, */ 16-1, 14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL*14ULL},
      { /*  901, 55, */ 16-1, 15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL*15ULL},
      { /*   16,  1, */ 15-1, 16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL*16ULL},
      { /*  595, 38, */ 15-1, 17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL*17ULL},
      { /* 1013, 66, */ 15-1, 18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL*18ULL},
      { /*  226, 15, */ 15-1, 19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL*19ULL},
      { /*  696, 47, */ 14-1, 20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL*20ULL},
      { /*  102,  7, */ 14-1, 21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL*21ULL},
      { /*  775, 54, */ 14-1, 22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL*22ULL},
      { /*  382, 27, */ 14-1, 23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL*23ULL},
      { /* 1019, 73, */ 13-1, 24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL*24ULL},
      { /*  758, 55, */ 13-1, 25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL*25ULL},
      { /*  994, 73, */ 13-1, 26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL*26ULL},
      { /*  673, 50, */ 13-1, 27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL*27ULL},
      { /*  892, 67, */ 13-1, 28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL*28ULL},
      { /*  830, 63, */ 13-1, 29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL*29ULL},
      { /*  300, 23, */ 13-1, 30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL*30ULL},
      { /*  633, 49, */ 12-1, 31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL*31ULL},
      { /*   64,  5, */ 12-1, 32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL*32ULL},
      { /*  203, 16, */ 12-1, 33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL*33ULL},
      { /*  629, 50, */ 12-1, 34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL*34ULL},
      { /*  836, 67, */ 12-1, 35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL*35ULL},
      { /*  359, 29, */ 12-1, 36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL*36ULL},
    #endif
    };

// Timing für Dezimal-Umwandlung einer Zahl mit N Digits = (N*32) Bits,
// auf einem i486 33 MHz unter Linux:
//    N      standard  dnq(div)  dnq(mul)  combined
//     10     0.00031   0.00043   0.00059   0.00031
//     25     0.00103   0.00125   0.00178   0.00103
//     50     0.0030    0.0034    0.0051    0.0030
//    100     0.0100    0.0108    0.0155    0.0100
//    250     0.054     0.055     0.064     0.054
//    500     0.207     0.209     0.229     0.207
//    750     0.47      0.48      0.47      0.47
//   1000     0.81      0.81      0.86      0.81
//   1250     1.25      1.12      1.20      1.12
//   1500     1.81      1.60      1.64      1.61
//   1750     2.45      2.24      2.15      2.25
//   1940     3.01      3.03      3.12      2.80
//   2000     3.20      3.11      3.30      2.89
//   2500     5.00      4.11      4.38      3.91
//   3000     7.3       5.8       5.7       5.5
//   4000    13.0      12.4      12.9       9.7
//   5000    20.3      15.3      15.1      12.4
//  10000    81.4      57.8      56.4      32.5
//  25000                                 112
//  50000                                 265
// dnq(div) means divide-and-conquer using division by B at the topmost call,
//                threshold = 1015.
// dnq(mul) means divide-and-conquer using multiplication by 1/B at the topmost
//                call, threshold = 2050.
// combined means divide-and-conquer as long as length >= threshold.
  const unsigned int cl_digits_div_threshold = 1015;
  //#define MUL_REPLACES_DIV
  const int cl_digits_algo = 1;

// Tabelle: enthält zu jeder Basis b (2 <= b <= 36)
// NULL oder einen Vektor von lazy berechneten b^(k*2^i) und 1/b^(k*2^i).
  typedef struct cached_power_table_entry {
    ALLOCATE_ANYWHERE(cached_power_table_entry)
    cl_I base_pow; // 0 or b^(k*2^i)
    #ifdef MUL_REPLACES_DIV
    cl_I inv_base_pow; // if base_pow: floor(2^(2*integer_length(base_pow))/base_pow)
    #endif
  } cached_power_table_entry;
  struct cached_power_table {
	cached_power_table_entry element[30];
	// Constructor and destructor - nothing special.
	cached_power_table () {}
	~cached_power_table () {}
	// Allocation and deallocation.
	void* operator new (size_t size) { return malloc_hook(size); }
	void operator delete (void* ptr) { free_hook(ptr); }
  };
  static cached_power_table* ctable [36-2+1] =
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
      NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
      NULL, NULL, NULL, NULL, NULL
    };
  static const cached_power_table_entry * cached_power (uintD base, uintL i)
    { var cached_power_table* ptr;
      if (!(ptr = ctable[base-2]))
        { ctable[base-2] = ptr = new cached_power_table (); }
      var uintL j;
      for (j = 0; j <= i; j++)
        if (zerop(ptr->element[j].base_pow))
          { // Compute b^(k*2^j) and its inverse.
            cl_I x =
              (j==0 ? (cl_I)(unsigned long)(table[base-2].b_hoch_k)
                    : ptr->element[j-1].base_pow * ptr->element[j-1].base_pow
              );
            ptr->element[j].base_pow = x;
            #ifdef MUL_REPLACES_DIV
            ptr->element[j].inv_base_pow = floor1(ash(1,2*integer_length(x)),x);
            #endif
          }
      return &ptr->element[i];
    }
  AT_DESTRUCTION(cached_power)
    { for (var uintD base = 2; base <= 36; base++)
        { var cached_power_table* ptr = ctable[base-2];
          if (ptr)
            { delete ptr; ctable[base-2] = NULL; }
        }
    }

// like I_to_digits, except that the result has exactly erg_len characters.
static inline void I_to_digits_noshrink (const cl_I& X, uintD base, uintL erg_len, cl_digits* erg)
{
  I_to_digits(X,base,erg);
  if (erg->len > erg_len) cl_abort();
  var uintL count = erg_len - erg->len;
  if (count > 0)
    { var uintB* ptr = erg->MSBptr;
      do { *--ptr = '0'; } while (--count > 0);
      erg->MSBptr = ptr; erg->len = erg->len;
    }
}

void I_to_digits (const cl_I& X, uintD base, cl_digits* erg)
{
// Methode:
// Umwandlung ins Stellensystem der Basis b geht durch Umwandlung ins Stellen-
// system der Basis b^k (k>=1, b^k<2^intDsize, k maximal) vor sich.
// Aufsuchen von k und b^k aus einer Tabelle.
// Reduktion der UDS zu einer NUDS X.
// Falls X=0: die eine Ziffer 0.
// Falls X>0:
//   Dividiere X durch das Wort b^k,
//   (Single-Precision-Division, vgl. UDS_DIVIDE mit n=1:
//     r:=0, j:=m=Länge(X),
//     while j>0 do
//       j:=j-1, r:=r*beta+X[j], X[j]:=floor(r/b^k), r:=r-b^k*q[j].
//     r=Rest.)
//   zerlege den Rest (mit k-1 Divisionen durch b) in k Ziffern, wandle diese
//   Ziffern einzeln in Ascii um und lege sie an die DIGITS an.
//   Teste auf Speicherüberlauf.
//   X := Quotient.
//   Mache aus X wieder eine NUDS (maximal 1 Nulldigit streichen).
//   Dies solange bis X=0.
//   Streiche die führenden Nullen.
      // Aufsuchen von k-1 und b^k aus der Tabelle:
      var power_table_entry* tableptr = &table[base-2];
      var uintC k_1 = tableptr->k_1; // k-1
      var uintD b_hoch_k = tableptr->b_hoch_k; // b^k
      var uintB* erg_ptr = erg->LSBptr;
      #define next_digit(d)  { *--erg_ptr = (d<10 ? '0'+d : 'A'-10+d); }
      // Spezialfälle:
      if (zerop(X))
        { next_digit(0); goto fertig; } // 0 -> eine Ziffer '0'
      else if ((base & (base-1)) == 0)
        { // Schneller Algorithmus für Zweierpotenzen
          var const uintD* MSDptr;
          var uintC len;
          var const uintD* LSDptr;
          I_to_NDS_nocopy(X, MSDptr=,len=,LSDptr=,cl_false,);
          var int b = (base==2 ? 1 : base==4 ? 2 : base==8 ? 3 : base==16 ? 4 : /*base==32*/ 5);
          var uintD carry = 0;
          var int carrybits = 0;
          loop
            { if (fixnump(X) && erg->LSBptr-erg_ptr>=cl_value_len)
                break;
              if (carrybits >= b)
                { var uintD d = carry & (base-1);
                  next_digit(d);
                  carry = carry >> b; carrybits -= b;
                }
                else
                { var uintD d = carry;
                  if (LSDptr != MSDptr)
                    { carry = lsprefnext(LSDptr);
                      d |= (carry << carrybits) & (base-1);
                      next_digit(d);
                      carry = carry >> (b-carrybits); carrybits = intDsize - (b-carrybits);
                    }
                    else
                    { next_digit(d); break; }
                }
            }
        }
      else if (fixnump(X) || TheBignum(X)->length < cl_digits_div_threshold
               || !cl_digits_algo)
        { // Standard-Algorithmus
          CL_ALLOCA_STACK;
          var uintD* MSDptr;
          var uintC len;
          var uintD* LSDptr;
          I_to_NDS(X, MSDptr=,len=,LSDptr=);
          // normalisiere zu einer NUDS:
          if (mspref(MSDptr,0)==0) { msshrink(MSDptr); len--; }
          loop
            { // Noch die NUDS MSDptr/len/.. mit len>0 abzuarbeiten.
              // Single-Precision-Division durch b^k:
              var uintD rest = divu_loop_msp(b_hoch_k,MSDptr,len);
              // Zerlegen des Restes in seine k Ziffern:
              var uintC count = k_1;
	      if (fixnump(X) && count>cl_value_len-1)
		  count = cl_value_len-1;
              if ((intDsize>=11) || (count>0))
                // (Bei intDsize>=11 ist wegen b<=36 zwangsläufig
                // k = ceiling(intDsize*log(2)/log(b))-1 >= 2, also count = k_1 > 0.)
                do { var uintD d;
                     #if HAVE_DD
                       divuD((uintDD)rest,base,rest=,d=);
                     #else
                       divuD(0,rest,base,rest=,d=);
                     #endif
                     next_digit(d);
                } until (--count == 0);
              next_digit(rest); // letzte der k Ziffern ablegen
              // Quotienten normalisieren (max. 1 Digit streichen):
              if (mspref(MSDptr,0)==0) { msshrink(MSDptr); len--; if (len==0) break; }
        }   }
      else
        { // Divide-and-conquer:
          // Find largest i such that B = base^(k*2^i) satisfies B <= X.
          // Divide by B: X = X1*B + X0. Convert X0 to string, fill up
          // for k*2^i characters, convert X1 to string. (Have to convert
          // X0 first because the conversion may temporarily prepend some
          // zero characters.)
          var uintL ilen_X = integer_length(X);
          var const cached_power_table_entry * p;
          var uintL ilen_B;
          var uintL i;
          for (i = 0; ; i++)
            { p = cached_power(base,i);
              ilen_B = integer_length(p->base_pow);
              if (2*ilen_B >= ilen_X) break;
              // 2*ilen_B < ilen_X, so certainly B^2 < X, let's continue with i+1.
            }
          // 2*ilen_B >= ilen_X, implies X < 2*B^2.
          // Of course also X >= B, implies ilen_X >= ilen_B.
          #ifdef MUL_REPLACES_DIV
          // Divide by B by computing
          //   q := floor((X * floor(2^ilen_X/B)) / 2^ilen_X).
          // We have q <= floor(X/B) <= q+1, so we may have to increment q.
          // Note also that
          // floor(2^ilen_X/B) = floor(floor(2^(2*ilen_B)/B)/2^(2*ilen_B-ilen_X))
          var cl_I q = (X * (p->inv_base_pow >> (2*ilen_B-ilen_X))) >> ilen_X;
          var cl_I r = X - q * p->base_pow;
          if (r < 0) cl_abort();
          if (r >= p->base_pow)
            { q = q+1; r = r - p->base_pow;
              if (r >= p->base_pow) cl_abort();
            }
          #else
          var cl_I_div_t q_r = floor2(X,p->base_pow);
          var const cl_I& q = q_r.quotient;
          var const cl_I& r = q_r.remainder;
          #endif
          var const cl_I& X1 = q;
          var const cl_I& X0 = r;
          var uintL B_baselen = (uintL)(k_1+1)<<i;
          I_to_digits_noshrink(X0,base,B_baselen,erg);
          erg->LSBptr -= B_baselen;
          I_to_digits(X1,base,erg);
          erg->LSBptr += B_baselen;
          erg_ptr = erg->MSBptr;
        }
      #undef next_digit
      // Streiche führende Nullen:
      while (*erg_ptr == '0') { erg_ptr++; }
      fertig:
      erg->MSBptr = erg_ptr;
      erg->len = erg->LSBptr - erg_ptr;
}
// Bit complexity (N := length(X)): O(log(N)*M(N)).

}  // namespace cln
