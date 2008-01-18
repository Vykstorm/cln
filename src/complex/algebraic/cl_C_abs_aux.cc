// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_C.h"


// Implementation.

#include "cln/real.h"

namespace cln {

CL_INLINE const cl_R CL_INLINE_DECL(abs) (const cl_C& x)
{
	var const cl_R& a = realpart(x);
	var const cl_R& b = imagpart(x);
	return cl_hypot(a,b);
}

}  // namespace cln
