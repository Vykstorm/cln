// tan().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

MAYBE_INLINE
const cl_R tan (const cl_R& x)
{
// Methode:
// (/ (sin x) (cos x))
	var cl_cos_sin_t trig = cl_cos_sin(x);
	return trig.sin / trig.cos;
}
