// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

const cl_R abs (const cl_R& x)
{
	// Methode:
	// Bei x<0: (- x), sonst x.
	if (minusp(x))
		return -x;
	else
		return x;
}
