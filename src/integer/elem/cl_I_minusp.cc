// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#define minusp inline_minusp
#include "cl_I.h"
#undef minusp

cl_boolean minusp (const cl_I& x)
{
	return inline_minusp(x);
}
