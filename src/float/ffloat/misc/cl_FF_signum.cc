// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_FF_minusp.cc"
#include "cl_FF_zerop.cc"

MAYBE_INLINE2
const cl_FF signum (const cl_FF& x)
{
	if (minusp(x)) { return cl_FF_minus1; } // x<0 -> -1.0
	elif (zerop(x)) { return cl_FF_0; } // x=0 -> 0.0
	else { return cl_FF_1; } // x>0 -> +1.0
}
