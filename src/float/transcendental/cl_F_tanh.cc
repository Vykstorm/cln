// tanh().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

MAYBE_INLINE
const cl_F tanh (const cl_F& x)
{
// Methode:
// (/ (sinh x) (cosh x))
	var cl_cosh_sinh_t hyp = cl_cosh_sinh(x);
	return The(cl_F)(hyp.sinh) / The(cl_F)(hyp.cosh);
}
