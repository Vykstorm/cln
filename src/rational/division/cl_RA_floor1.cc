// floor1().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

const cl_I floor1 (const cl_RA& x)
{
// Methode:
// x Integer -> q := x
// x Ratio a/b -> (floor a b)
	if (integerp(x)) {
		DeclareType(cl_I,x);
		return x;
	} else {
		DeclareType(cl_RT,x);
		var const cl_I& a = numerator(x);
		var const cl_I& b = denominator(x);
		return floor1(a,b);
	}
}
