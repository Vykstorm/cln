// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"

MAYBE_INLINE
uintL float_digits (const cl_LF& x)
{
	return intDsize*(uintL)(TheLfloat(x)->len);
}
