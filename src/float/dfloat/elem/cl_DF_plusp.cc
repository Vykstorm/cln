// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_minusp.cc"
#include "cl_DF_zerop.cc"

namespace cln {

MAYBE_INLINE2
bool plusp (const cl_DF& x)
{
	if (minusp(x))
		return false; // x<0 -> nein
	elif (zerop(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
