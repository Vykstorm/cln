// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
cl_boolean zerop (const cl_LF& x)
{
	return (cl_boolean) (TheLfloat(x)->expo == 0);
}

}  // namespace cln
