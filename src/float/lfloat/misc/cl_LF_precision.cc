// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

#include "cl_inline.h"
#include "cl_LF_zerop.cc"

namespace cln {

CL_INLINE2 uintC CL_INLINE2_DECL(float_precision) (const cl_LF& x)
{
	if (zerop_inline(x)) return 0;
	return intDsize*(uintC)(TheLfloat(x)->len);
}

}  // namespace cln
