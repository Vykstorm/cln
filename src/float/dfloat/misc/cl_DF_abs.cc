// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_minusp.cc"

const cl_DF abs (const cl_DF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp(x)) return -x; else return x;
}
