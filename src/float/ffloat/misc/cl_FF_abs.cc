// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_FF_minusp.cc"

const cl_FF abs (const cl_FF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp(x)) return -x; else return x;
}
