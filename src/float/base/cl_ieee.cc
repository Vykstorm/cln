// System dependent IEEE floating-point coprocessor initialization.

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_ieee)

// Specification.
#include "cl_ieee.h"


// Implementation.

#include "cl_FF.h"
#include "cl_DF.h"
#include "cl_float_config.h"

#if (defined(linux) || defined(__linux)) && (defined(FAST_FLOAT) || defined(FAST_DOUBLE))

// Damit Division durch 0.0 ein NaN und kein SIGFPE liefert:
// Entweder mit -lieee linken,
// oder libc-linux/sysdeps/linux/{i386,m68k}/ieee.c kopieren:

#include <fpu_control.h>

#if 0 // Leider gibt das einen Error, wenn man zusätzlich mit -lieee linkt.
	#if defined(HAVE_FPU_CONTROL_T)
		fpu_control_t __fpu_control = _FPU_IEEE;
	#else
		unsigned short __fpu_control = _FPU_IEEE;
	#endif
#else
AT_INITIALIZATION(ieee)
{
	#if defined(HAVE_FPU_CONTROL_T)
		extern fpu_control_t __fpu_control;
		__fpu_control = _FPU_IEEE;
	#elif defined(HAVE_SETFPUCW)
		__setfpucw(_FPU_IEEE);
	#else
		extern unsigned short __fpu_control;
		__fpu_control = _FPU_IEEE;
	#endif
}
#endif

#endif

namespace cln {

// This dummy links in this module whenever some module needs IEEE floats.
int cl_ieee_module;

}  // namespace cln

CL_PROVIDE_END(cl_ieee)
