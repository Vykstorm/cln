// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

const cl_SF recip (const cl_SF& x)
{
	return SF_1 / x;
}
