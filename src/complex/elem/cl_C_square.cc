// square().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N square (const cl_N& x)
{
// Methode:
// x reell -> klar.
// x=a+bi -> (a^2-b^2)+(2*a*b)i
	if (realp(x)) {
		DeclareType(cl_R,x);
		return square(x);
	} else {
		DeclareType(cl_C,x);
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		return complex_C(square(a)-square(b),2*a*b);
	}
}
