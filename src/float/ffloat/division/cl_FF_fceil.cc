// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#include "cl_inline.h"
#include "cl_FF_minusp.cc"

namespace cln {

const cl_FF CL_FLATTEN fceiling (const cl_FF& x)
{
	if (minusp_inline(x))
		return ftruncate(x);
	else
		return futruncate(x);
}

}  // namespace cln
