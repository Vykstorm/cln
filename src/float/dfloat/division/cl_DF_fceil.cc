// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_minusp.cc"

const cl_DF fceiling (const cl_DF& x)
{
	if (minusp(x))
		return ftruncate(x);
	else
		return futruncate(x);
}
