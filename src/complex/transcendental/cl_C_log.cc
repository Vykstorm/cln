// log().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/complex.h"


// Implementation.

#include "cl_C.h"
#include "cln/real.h"
#include "cl_N.h"

namespace cln {

const cl_N log (const cl_N& x)
{
// Methode:
// (complex (log (abs x)) (phase x))
	var cl_R r = abs(x);
	if (zerop(r)) // (abs x) = 0 -> Error
		{ cl_error_division_by_0(); }
	return complex(ln(r),phase(x));
}

}  // namespace cln
