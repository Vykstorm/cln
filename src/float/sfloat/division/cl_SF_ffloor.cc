// ffloor().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"

const cl_SF ffloor (const cl_SF& x)
{
	if (minusp(x))
		return futruncate(x);
	else
		return ftruncate(x);
}
