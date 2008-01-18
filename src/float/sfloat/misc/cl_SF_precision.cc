// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

#include "cl_inline.h"
#include "cl_SF_zerop.cc"

namespace cln {

CL_INLINE2 uintC CL_INLINE2_DECL(float_precision) (const cl_SF& x)
{
	if (zerop_inline(x)) return 0;
	return SF_mant_len+1; // 17
}

}  // namespace cln
