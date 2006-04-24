// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/dfloat.h"


// Implementation.

#include "cl_DF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_DF_zerop.cc"

namespace cln {

MAYBE_INLINE2
uintC float_precision (const cl_DF& x)
{
	if (zerop(x)) return 0;
	return DF_mant_len+1; // 53
}

}  // namespace cln
