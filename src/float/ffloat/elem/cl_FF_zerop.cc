// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

namespace cln {

MAYBE_INLINE
cl_boolean zerop (const cl_FF& x)
{
	return (cl_boolean) (cl_ffloat_value(x) == 0);
}

}  // namespace cln
