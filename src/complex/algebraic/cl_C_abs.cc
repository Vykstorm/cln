// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex.h"


// Implementation.

#include "cl_C.h"
#include "cln/real.h"

#undef MAYBE_INLINE
#define MAYBE_INLINE inline
#include "cl_C_abs_aux.cc"

namespace cln {

const cl_R abs (const cl_N& x)
{
// Methode:
// Falls x reell: klar
// Falls x=a+bi: sqrt(a^2+b^2)
	if (realp(x)) {
		DeclareType(cl_R,x);
		return abs(x);
	} else {
		DeclareType(cl_C,x);
		return abs(x);
	}
}

}  // namespace cln
