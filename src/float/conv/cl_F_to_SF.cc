// cl_F_to_SF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"

const cl_SF cl_F_to_SF (const cl_F& x)
{
	floatcase(x
	,	return x;
	,	return cl_FF_to_SF(x);
	,	return cl_DF_to_SF(x);
	,	return cl_LF_to_SF(x);
	);
}
