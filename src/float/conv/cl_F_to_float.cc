// cl_F_to_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"

float cl_float_approx (const cl_F& x)
{
	floatcase(x
	,	return cl_float_approx(x);
	,	return cl_float_approx(x);
	,	return cl_float_approx(x);
	,	return cl_float_approx(x);
	);
}
