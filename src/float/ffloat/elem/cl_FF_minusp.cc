// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

MAYBE_INLINE
cl_boolean minusp (const cl_FF& x)
{
	return (cl_boolean) ((sint32)cl_ffloat_value(x) < 0);
}
