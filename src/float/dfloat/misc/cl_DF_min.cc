// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

const cl_DF min (const cl_DF& x, const cl_DF& y)
{
	return (x <= y ? x : y);
}
