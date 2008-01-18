// abs().

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

#include "cl_inline.h"
#include "cl_SF_minusp.cc"
#include "cl_FF_minusp.cc"
#include "cl_DF_minusp.cc"
#include "cl_LF_minusp.cc"

namespace cln {

const cl_F CL_FLATTEN abs (const cl_F& x)
{
// x<0 -> (- x), x>=0 -> x
	floatcase(x
	,	if (minusp_inline(x)) return -x; else return x;
	,	if (minusp_inline(x)) return -x; else return x;
	,	if (minusp_inline(x)) return -x; else return x;
	,	if (minusp_inline(x)) return -x; else return x;
	);
}

}  // namespace cln
