// signum().

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
const cl_SF signum (const cl_SF& x)
{
	if (minusp(x)) { return SF_minus1; } // x<0 -> -1.0
	elif (zerop(x)) { return SF_0; } // x=0 -> 0.0
	else { return SF_1; } // x>0 -> +1.0
}

}  // namespace cln
