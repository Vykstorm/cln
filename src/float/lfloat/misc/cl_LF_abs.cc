// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_inline.h"
#include "cl_LF_minusp.cc"

namespace cln {

const cl_LF CL_FLATTEN abs (const cl_LF& x)
{
// x<0 -> (- x), x>=0 -> x
	if (minusp_inline(x)) return -x; else return x;
}

}  // namespace cln
