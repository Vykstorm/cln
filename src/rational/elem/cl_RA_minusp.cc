// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#define minusp inline_minusp
#include "cl_RA.h"
#undef minusp

cl_boolean minusp (const cl_RA& x)
{
	return inline_minusp(x);
}
