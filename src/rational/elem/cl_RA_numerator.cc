// numerator().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#define numerator inline_numerator
#include "cl_RA.h"
#undef numerator

const cl_I numerator (const cl_RA& r)
{
	return inline_numerator(r);
}
