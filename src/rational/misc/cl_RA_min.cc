// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

const cl_RA min (const cl_RA& x, const cl_RA& y)
{
	return (x <= y ? x : y);
}
