// plusp().

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
cl_boolean plusp (const cl_DF& x)
{
	if (minusp(x))
		return cl_false; // x<0 -> nein
	elif (zerop(x))
		return cl_false; // x=0 -> nein
	else
		return cl_true; // sonst ist x>0.
}
