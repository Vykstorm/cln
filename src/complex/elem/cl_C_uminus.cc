// unary operator -

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"

const cl_N operator- (const cl_N& x)
{
// Methode:
// x reell -> klar.
// x=a+bi -> (-a) + (-b) i
	if (realp(x)) {
		DeclareType(cl_R,x);
		return -x;
	} else {
		DeclareType(cl_C,x);
		var const cl_R& a = realpart(x);
		var const cl_R& b = imagpart(x);
		return complex_C(-a,-b);
	}
}
