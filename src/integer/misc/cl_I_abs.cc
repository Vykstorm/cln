// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_integer.h"


// Implementation.

#include "cl_I.h"

const cl_I abs (const cl_I& x)
{
	// Methode:
	// Bei x<0: (- x), sonst x.
	if (minusp(x))
		return -x;
	else
		return x;
}
