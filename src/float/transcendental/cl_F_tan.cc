// tan().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

MAYBE_INLINE
const cl_F tan (const cl_F& x)
{
// Methode:
// (/ (sin x) (cos x))
	var cl_cos_sin_t trig = cl_cos_sin(x);
	return The(cl_F)(trig.sin) / The(cl_F)(trig.cos);
}
