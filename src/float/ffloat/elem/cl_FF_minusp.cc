// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/ffloat.h"


// Implementation.

#include "cl_FF.h"

namespace cln {

MAYBE_INLINE
cl_boolean minusp (const cl_FF& x)
{
	return (cl_boolean) ((sint32)cl_ffloat_value(x) < 0);
}

}  // namespace cln
