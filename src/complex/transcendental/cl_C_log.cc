// log().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"
#include "cl_N.h"

const cl_N log (const cl_N& x)
{
// Methode:
// (complex (log (abs x)) (phase x))
	var cl_R r = abs(x);
	if (zerop(r)) // (abs x) = 0 -> Error
		{ cl_error_division_by_0(); }
	return complex(ln(r),phase(x));
}
