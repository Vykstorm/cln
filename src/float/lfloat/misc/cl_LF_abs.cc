// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"

const cl_LF abs (const cl_LF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp(x)) return -x; else return x;
}
