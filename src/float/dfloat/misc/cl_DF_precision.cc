// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#include "cl_inline.h"
#include "cl_DF_zerop.cc"

namespace cln {

CL_INLINE2 uintC CL_INLINE2_DECL(float_precision) (const cl_DF& x)
{
	if (zerop_inline(x)) return 0;
	return DF_mant_len+1; // 53
}

}  // namespace cln
