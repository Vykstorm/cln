// cl_R_to_double().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_F.h"
#include "cl_integer.h"
#include "cl_rational.h"
#include "cl_float.h"
#include "cl_sfloat.h"
#include "cl_ffloat.h"
#include "cl_dfloat.h"
#include "cl_lfloat.h"

#if 0

double cl_double_approx (const cl_R& x)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		return cl_double_approx(x);
	} else {
		DeclareType(cl_F,x);
		return cl_double_approx(x);
	}
}

#else // fully inlined, faster

#include "cl_RA.h"
#include "cl_I.h"

double cl_double_approx (const cl_R& x)
{
	realcase6(x
	,	return cl_double_approx(x);
	,	return cl_double_approx(x);
	,	return cl_double_approx(x);
	,	return cl_double_approx(x);
	,	return cl_double_approx(x);
	,	return cl_double_approx(x);
	);
}

#endif
