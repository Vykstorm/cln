// cl_F_to_DF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

const cl_DF cl_F_to_DF (const cl_F& x)
{
	floatcase(x
	,	return cl_SF_to_DF(x);
	,	return cl_FF_to_DF(x);
	,	return x;
	,	return cl_LF_to_DF(x);
	);
}
