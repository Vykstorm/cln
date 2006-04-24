// float_precision().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_LF_zerop.cc"

namespace cln {

MAYBE_INLINE2
uintC float_precision (const cl_LF& x)
{
	if (zerop(x)) return 0;
	return intDsize*(uintC)(TheLfloat(x)->len);
}

}  // namespace cln
