// cl_F_to_double().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/float.h"


// Implementation.

#include "cl_F.h"
#include "cln/sfloat.h"
#include "cln/ffloat.h"
#include "cln/dfloat.h"
#include "cln/lfloat.h"

namespace cln {

double double_approx (const cl_F& x)
{
	floatcase(x
	,	return double_approx(x);
	,	return double_approx(x);
	,	return double_approx(x);
	,	return double_approx(x);
	);
}

}  // namespace cln
