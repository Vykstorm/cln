// abs().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

const cl_RA abs (const cl_RA& r)
{
	// Methode:
	// Bei r<0: (- r), sonst r.
	if (minusp(r))
		return -r;
	else
		return r;
}
