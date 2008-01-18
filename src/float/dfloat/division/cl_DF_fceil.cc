// fceiling().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

/* For inline version of minusp */
#include "cl_inline.h"
#include "cl_DF_minusp.cc"

namespace cln {

const cl_DF CL_FLATTEN fceiling (const cl_DF& x)
{
	if (minusp_inline(x))
		return ftruncate(x);
	else
		return futruncate(x);
}

}  // namespace cln
