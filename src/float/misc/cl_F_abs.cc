// abs().

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

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

const cl_F abs (const cl_F& x)
{
// x<0 -> (- x), x>=0 -> x
	floatcase(x
	,	if (minusp(x)) return -x; else return x;
	,	if (minusp(x)) return -x; else return x;
	,	if (minusp(x)) return -x; else return x;
	,	if (minusp(x)) return -x; else return x;
	);
}
