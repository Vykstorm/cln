// Includes the CPU specific cl_asm_*.h file.

#include "cl_config.h"
#include "cl_DS_endian.h"

#ifdef __m68k__
  #include "cl_asm_m68k.h"
#endif

#if defined(__sparc__) && !defined(__sparc64__)
  #include "cl_asm_sparc.h"
#endif

#if defined(__sparc64__)
  #include "cl_asm_sparc64.h"
#endif

#ifdef __i386__
  #include "cl_asm_i386.h"
#endif

#ifdef __mips__
  #include "cl_asm_mips.h"
#endif

#ifdef __hppa__
  #include "cl_asm_hppa.h"
#endif

#ifdef __arm__
  #include "cl_asm_arm.h"
#endif

