// cl_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"

MAYBE_INLINE
const cl_F cl_float (const cl_R& x)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		return cl_float(x);
	} else {
		DeclareType(cl_F,x);
		return x;
	}
}
