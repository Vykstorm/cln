// recip().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

const cl_FF recip (const cl_FF& x)
{
	return cl_FF_1 / x;
}
