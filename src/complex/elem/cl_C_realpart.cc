// realpart().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"

const cl_R realpart (const cl_N& x)
{
	if (realp(x)) {
		DeclareType(cl_R,x);
		return x;
	} else {
		DeclareType(cl_C,x);
		return realpart(x);
	}
}
