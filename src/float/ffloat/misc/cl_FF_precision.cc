// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_FF_zerop.cc"

namespace cln {

MAYBE_INLINE2
uintC float_precision (const cl_FF& x)
{
	if (zerop(x)) return 0;
	return FF_mant_len+1; // 24
}

}  // namespace cln
