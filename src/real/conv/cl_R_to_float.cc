// cl_R_to_float().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cl_F.h"
#include "cln/integer.h"
#include "cln/rational.h"
#include "cln/float.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"

#if 0

namespace cln {

float float_approx (const cl_R& x)
{
	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		return float_approx(x);
	} else {
		DeclareType(cl_F,x);
		return float_approx(x);
	}
}

}  // namespace cln

#else // fully inlined, faster

#include "cl_RA.h"
#include "cl_I.h"

namespace cln {

float float_approx (const cl_R& x)
{
	realcase6(x
	,	return float_approx(x);
	,	return float_approx(x);
	,	return float_approx(x);
	,	return float_approx(x);
	,	return float_approx(x);
	,	return float_approx(x);
	);
}

}  // namespace cln

#endif
