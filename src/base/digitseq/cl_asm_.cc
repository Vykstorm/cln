// Includes the CPU specific cl_asm_*.cc file.

#include "cl_config.h"
#include "cl_DS_endian.h"

#ifdef __m68k__
  #include "cl_asm_m68k_.cc"
#endif

#if defined(__sparc__) && !defined(__sparc64__)
  #include "cl_asm_sparc_.cc"
#endif

#if defined(__sparc64__)
  #include "cl_asm_sparc64_.cc"
#endif

#ifdef __i386__
  #include "cl_asm_i386_.cc"
#endif

#ifdef __mips__
  #include "cl_asm_mips_.cc"
#endif

#ifdef __hppa__
  #include "cl_asm_hppa_.cc"
#endif

#ifdef __arm__
  #include "cl_asm_arm_.cc"
#endif

