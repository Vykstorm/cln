// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#define zerop inline_zerop
#include "cl_RA.h"
#undef zerop

cl_boolean zerop (const cl_RA& x)
{
	return inline_zerop(x);
}
