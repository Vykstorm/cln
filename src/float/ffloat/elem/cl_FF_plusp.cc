// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_FF_minusp.cc"
#include "cl_FF_zerop.cc"

namespace cln {

MAYBE_INLINE2
bool plusp (const cl_FF& x)
{
	if (minusp(x))
		return false; // x<0 -> nein
	elif (zerop(x))
		return false; // x=0 -> nein
	else
		return true; // sonst ist x>0.
}

}  // namespace cln
