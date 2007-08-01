// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"
#include "cl_SF_zerop.cc"

namespace cln {

MAYBE_INLINE2
bool plusp (const cl_SF& x)
{
	if (minusp(x))
		return false; // x<0 -> nein
	elif (zerop(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
