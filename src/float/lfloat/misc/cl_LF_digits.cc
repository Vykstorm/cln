// float_digits().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
uintL float_digits (const cl_LF& x)
{
	return intDsize*(uintL)(TheLfloat(x)->len);
}

}  // namespace cln
