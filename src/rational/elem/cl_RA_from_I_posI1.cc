// I_I_to_RT().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_RA.h"


// Implementation.

const cl_RA I_I_to_RT (const cl_I& a, const cl_I& b)
{
	return allocate_ratio(a,b);
}
