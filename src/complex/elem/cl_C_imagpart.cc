// imagpart().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"

const cl_R imagpart (const cl_N& x)
{
	if (realp(x))
		return 0;
	else {
		DeclareType(cl_C,x);
		return imagpart(x);
	}
}
