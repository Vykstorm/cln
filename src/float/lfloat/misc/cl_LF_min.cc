// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_lfloat.h"


// Implementation.

const cl_LF min (const cl_LF& x, const cl_LF& y)
{
	return (x <= y ? x : y);
}
