// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_dfloat.h"


// Implementation.

#include "cl_DF.h"

MAYBE_INLINE
uintL float_digits (const cl_DF& x)
{
	unused x;
	return DF_mant_len+1; // 53
}
