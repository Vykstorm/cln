// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"
#include "cl_LF_impl.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_minusp.cc"
#include "cl_LF_zerop.cc"

namespace cln {

MAYBE_INLINE2
cl_boolean plusp (const cl_LF& x)
{
	if (minusp(x))
		return cl_false; // x<0 -> nein
	elif (zerop(x))
		return cl_false; // x=0 -> nein
	else
		return cl_true; // sonst ist x>0.
}

}  // namespace cln
