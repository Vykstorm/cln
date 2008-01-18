// ffloor().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#include "cl_inline.h"
#include "cl_DF_minusp.cc"

namespace cln {

const cl_DF CL_FLATTEN ffloor (const cl_DF& x)
{
	if (minusp_inline(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
