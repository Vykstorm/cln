// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_ffloat.h"


// Implementation.

#include "cl_FF.h"

MAYBE_INLINE
uintL float_digits (const cl_FF& x)
{
	unused x;
	return FF_mant_len+1; // 24
}
