// plusp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

cl_boolean plusp (const cl_R& x)
{
	if (minusp(x))
		return cl_false; // x<0 -> nein
	elif (zerop(x))
		return cl_false; // x=0 -> nein
	else
		return cl_true; // sonst ist x>0.
}
