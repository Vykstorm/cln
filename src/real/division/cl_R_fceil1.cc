// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_RA.h"
#include "cl_integer.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"

const cl_F fceiling (const cl_R& x)
{
	realcase6(x
	,	return cl_float(x);
	,	var const cl_I& a = numerator(x);
		var const cl_I& b = denominator(x);
		return cl_float(ceiling1(a,b));
	,	return fceiling(x);
	,	return fceiling(x);
	,	return fceiling(x);
	,	return fceiling(x);
	);
}
