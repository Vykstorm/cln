// min().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

const cl_SF min (const cl_SF& x, const cl_SF& y)
{
	return (x <= y ? x : y);
}
