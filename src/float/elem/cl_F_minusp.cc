// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

cl_boolean minusp (const cl_F& x)
{
	floatcase(x
	,	return minusp(x);
	,	return minusp(x);
	,	return minusp(x);
	,	return minusp(x);
	);
}
