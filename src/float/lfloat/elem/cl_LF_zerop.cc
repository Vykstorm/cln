// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

#include "cl_LF.h"

MAYBE_INLINE
cl_boolean zerop (const cl_LF& x)
{
	return (cl_boolean) (TheLfloat(x)->expo == 0);
}
