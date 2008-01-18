// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#include "cl_inline.h"
#include "cl_FF_zerop.cc"

namespace cln {

CL_INLINE2 uintC CL_INLINE2_DECL(float_precision) (const cl_FF& x)
{
	if (zerop_inline(x)) return 0;
	return FF_mant_len+1; // 24
}

}  // namespace cln
