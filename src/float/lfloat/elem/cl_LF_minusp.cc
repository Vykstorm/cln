// minusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/lfloat.h"


// Implementation.

#include "cl_LF.h"

namespace cln {

MAYBE_INLINE
cl_boolean minusp (const cl_LF& x)
{
	return (cl_boolean) (- TheLfloat(x)->sign);
}

}  // namespace cln
