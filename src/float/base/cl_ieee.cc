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

// Division by 0.0 should return NaN and not raise an SIGFPE.
// For this, we either have to link with -lieee or copy some
// part from libc-linux/sysdeps/linux/{i386,m68k}/ieee.c:

#include <fpu_control.h>

#if 0 // Unfortunately this gives an error if also linked with -lieee
	#if defined(HAVE_FPU_CONTROL_T)
		fpu_control_t __fpu_control = _FPU_IEEE;
	#else
		unsigned short __fpu_control = _FPU_IEEE;
	#endif
#else
AT_INITIALIZATION(ieee)
{
	#if defined(_FPU_IEEE)
		#if defined(HAVE_FPU_CONTROL_T)
			extern fpu_control_t __fpu_control;
			__fpu_control = _FPU_IEEE;
		#elif defined(HAVE_SETFPUCW)
			__setfpucw(_FPU_IEEE);
		#else
			extern unsigned short __fpu_control;
			__fpu_control = _FPU_IEEE;
		#endif
	#else
		// Nothing to do (as on some architectures):
		// probably this means that _FPU_DEFAULT is just as good as _FPU_IEEE.
	#endif
}
#endif

#endif

namespace cln {

// This dummy links in this module whenever some module needs IEEE floats.
int cl_ieee_module;

}  // namespace cln

CL_PROVIDE_END(cl_ieee)
