// tanh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

namespace cln {

MAYBE_INLINE
const cl_R tanh (const cl_R& x)
{
// Methode:
// (/ (sinh x) (cosh x))
	var cosh_sinh_t hyp = cosh_sinh(x);
	return hyp.sinh / hyp.cosh;
}

}  // namespace cln
