// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/sfloat.h"


// Implementation.

#include "cl_SF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_SF_zerop.cc"

namespace cln {

MAYBE_INLINE2
uintL float_precision (const cl_SF& x)
{
	if (zerop(x)) return 0;
	return SF_mant_len+1; // 17
}

}  // namespace cln
