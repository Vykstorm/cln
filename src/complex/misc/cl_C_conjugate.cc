// conjugate().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N conjugate (const cl_N& x)
{
	if (realp(x))
		return x;
	else {
		DeclareType(cl_C,x);
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		// Vorzeichenwechsel beim Imaginärteil
		return complex_C(a,-b);
	}
}
