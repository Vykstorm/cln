// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
bool zerop (const cl_LF& x)
{
	return TheLfloat(x)->expo == 0;
}

}  // namespace cln
