// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#define zerop inline_zerop
#include "cl_I.h"
#undef zerop

cl_boolean zerop (const cl_I& x)
{
	return inline_zerop(x);
}
