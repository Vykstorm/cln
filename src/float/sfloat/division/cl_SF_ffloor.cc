// ffloor().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

/* For inline version of minusp */
#include "cl_inline.h"
#include "cl_SF_minusp.cc"

namespace cln {

const cl_SF CL_FLATTEN ffloor (const cl_SF& x)
{
	if (minusp_inline(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
