// tanh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

MAYBE_INLINE
const cl_R tanh (const cl_R& x)
{
// Methode:
// (/ (sinh x) (cosh x))
	var cl_cosh_sinh_t hyp = cl_cosh_sinh(x);
	return hyp.sinh / hyp.cosh;
}
