// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE2
#define MAYBE_INLINE2 inline
#include "cl_SF_precision.cc"
#include "cl_FF_precision.cc"
#include "cl_DF_precision.cc"
#include "cl_LF_precision.cc"

uintL float_precision (const cl_F& x)
{
	floatcase(x
	,	return float_precision(x);
	,	return float_precision(x);
	,	return float_precision(x);
	,	return float_precision(x);
	);
}
