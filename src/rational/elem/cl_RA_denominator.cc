// denominator().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#define denominator inline_denominator
#include "cl_RA.h"
#undef denominator

const cl_I denominator (const cl_RA& r)
{
	return inline_denominator(r);
}
