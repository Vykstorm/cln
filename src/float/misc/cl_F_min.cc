// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

const cl_F min (const cl_F& x, const cl_F& y)
{
	return (x <= y ? x : y);
}
