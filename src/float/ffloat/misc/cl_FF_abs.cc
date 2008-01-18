// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_inline.h"
#include "cl_FF_minusp.cc"

namespace cln {

const cl_FF CL_FLATTEN abs (const cl_FF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp_inline(x)) return -x; else return x;
}

}  // namespace cln
