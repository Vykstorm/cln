// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_minusp.cc"
#include "cl_DF_zerop.cc"

MAYBE_INLINE2
const cl_DF signum (const cl_DF& x)
{
	if (minusp(x)) { return cl_DF_minus1; } // x<0 -> -1.0
	elif (zerop(x)) { return cl_DF_0; } // x=0 -> 0.0
	else { return cl_DF_1; } // x>0 -> +1.0
}
