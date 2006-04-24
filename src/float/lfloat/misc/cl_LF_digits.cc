// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
uintC float_digits (const cl_LF& x)
{
	return intDsize*(uintC)(TheLfloat(x)->len);
}

}  // namespace cln
