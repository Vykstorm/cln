// signum().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"

MAYBE_INLINE
const cl_I signum (const cl_I& x)
{
	if (minusp(x)) { return -1; } // x<0 -> -1
	elif (zerop(x)) { return 0; } // x=0 -> 0
	else { return 1; } // x>0 -> +1
}
