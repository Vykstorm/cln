// Includes the CPU specific cl_asm_*.cc file.

#include "cln/config.h"

#if defined(__sparc__) || defined(__sparc64__)
  #include "cl_asm_sparc_GF2.cc"
#endif

