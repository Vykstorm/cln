// ffloor().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

#include "cl_inline.h"
#include "cl_LF_minusp.cc"

namespace cln {

CL_INLINE2 const cl_LF CL_INLINE2_DECL(ffloor) (const cl_LF& x)
{
	if (minusp_inline(x))
		return futruncate(x);
	else
		return ftruncate(x);
}

}  // namespace cln
