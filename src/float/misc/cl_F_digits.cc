// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_digits.cc"
#include "cl_FF_digits.cc"
#include "cl_DF_digits.cc"
#include "cl_LF_digits.cc"

uintL float_digits (const cl_F& x)
{
	floatcase(x
	,	return float_digits(x);
	,	return float_digits(x);
	,	return float_digits(x);
	,	return float_digits(x);
	);
}
