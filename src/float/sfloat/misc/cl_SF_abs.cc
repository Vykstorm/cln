// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"

const cl_SF abs (const cl_SF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp(x)) return -x; else return x;
}
