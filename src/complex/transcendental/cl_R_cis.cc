// cis().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N cis (const cl_R& x)
{
// Methode:
// (complex (cos x) (sin x))
	var cl_cos_sin_t trig = cl_cos_sin(x);
	return complex(trig.cos, trig.sin);
}
