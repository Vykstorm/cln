// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_sfloat.h"


// Implementation.

#include "cl_SF.h"

MAYBE_INLINE
uintL float_digits (const cl_SF& x)
{
	unused x;
	return SF_mant_len+1; // 17
}
