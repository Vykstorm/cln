// cl_F equal_hashcode().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_N.h"
#include "cl_F.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_eqhashcode.cc"
#include "cl_FF_eqhashcode.cc"
#include "cl_DF_eqhashcode.cc"
#include "cl_LF_eqhashcode.cc"

uint32 cl_equal_hashcode (const cl_F& x)
{
	floatcase(x
	,	return cl_equal_hashcode(x);
	,	return cl_equal_hashcode(x);
	,	return cl_equal_hashcode(x);
	,	return cl_equal_hashcode(x);
	);
}
