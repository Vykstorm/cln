// zerop().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

cl_boolean zerop (const cl_N& x)
{
	if (realp(x)) {
		DeclareType(cl_R,x);
		return zerop(x);
	} else {
		DeclareType(cl_C,x);
		// x komplex, teste ob Real- und Imaginärteil beide = 0 sind.
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		if (zerop(a))
			if (zerop(b))
				return cl_true;
		return cl_false;
	}
}
