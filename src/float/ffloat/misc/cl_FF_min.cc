// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

const cl_FF min (const cl_FF& x, const cl_FF& y)
{
	return (x <= y ? x : y);
}
