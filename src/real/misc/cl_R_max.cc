// max().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

const cl_R max (const cl_R& x, const cl_R& y)
{
	return (x >= y ? x : y);
}
